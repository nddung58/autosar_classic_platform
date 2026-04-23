from __future__ import annotations

from typing import Dict, List, Optional

from Components.models.can_frame import CanFrame
from Components.CanTp.CanTp_Types import (
    FrameType,
    CanTpState,
    CanTpFcFsType,
    CanTpChannelConfig,
)


class CanTp:
    def __init__(
        self,
        can_if,
        pdur,
        channels: List[CanTpChannelConfig],
    ) -> None:
        self._can_if = can_if
        self._pdur = pdur

        self._channels_by_rx_pdu_id: Dict[int, CanTpChannelConfig] = {
            ch.rx_pdu_id: ch for ch in channels
        }
        self._channels_by_tx_pdu_id: Dict[int, CanTpChannelConfig] = {
            ch.tx_pdu_id: ch for ch in channels
        }

        # -------------------------
        # TX context
        # -------------------------
        self._tx_app_ptr: bytes = b""
        self._tx_total_len: int = 0
        self._tx_sent_len: int = 0
        self._tx_sn: int = 0
        self._tx_state: CanTpState = CanTpState.IDLE
        self._tx_active_pdu_id: Optional[int] = None

        # -------------------------
        # RX context
        # -------------------------
        self._rx_total_len: int = 0
        self._rx_copied_len: int = 0
        self._rx_sn: int = 0
        self._rx_buffer: bytearray = bytearray()

    # --------------------------------------------------
    # Public API
    # --------------------------------------------------
    def CanTp_Transmit(self, tx_pdu_id: int, payload: bytes) -> bool:
        if payload is None or len(payload) == 0:
            return False

        if self._tx_state != CanTpState.IDLE:
            return False

        channel = self._channels_by_tx_pdu_id.get(tx_pdu_id)
        if channel is None:
            return False

        # Single Frame
        if len(payload) <= 7:
            sf = (
                bytes([(FrameType.PCI_TYPE_SF.value << 4) | (len(payload) & 0x0F)])
                + payload
            )

            self._tx_state = CanTpState.SF
            self._tx_active_pdu_id = tx_pdu_id

            return self._can_if.transmit(tx_pdu_id, sf)

        # First Frame
        if len(payload) > 0x0FFF:
            return False

        ff_byte0 = (FrameType.PCI_TYPE_FF.value << 4) | ((len(payload) >> 8) & 0x0F)
        ff_byte1 = len(payload) & 0xFF
        ff = bytes([ff_byte0, ff_byte1]) + payload[:6]

        self._tx_app_ptr = payload
        self._tx_total_len = len(payload)
        self._tx_sent_len = 6
        self._tx_sn = 1
        self._tx_active_pdu_id = tx_pdu_id
        self._tx_state = CanTpState.FF

        return self._can_if.transmit(tx_pdu_id, ff)

    def CanTp_MainFunction(self) -> None:
        # Bản đơn giản: chưa xử lý timer
        pass

    def CanTp_RxIndication(self, rx_pdu_id: int, frame: CanFrame) -> None:
        channel = self._channels_by_rx_pdu_id.get(rx_pdu_id)
        if channel is None:
            return

        if frame.data is None or len(frame.data) == 0:
            return

        pci_type = (frame.data[0] >> 4) & 0x0F

        # --------------------------------------------------
        # Single Frame
        # --------------------------------------------------
        if pci_type == FrameType.PCI_TYPE_SF.value:
            tp_len = frame.data[0] & 0x0F

            if tp_len == 0 or tp_len > 7:
                return

            if tp_len > (len(frame.data) - 1):
                return

            payload = bytes(frame.data[1 : 1 + tp_len])
            self._pdur.PduR_CanTpRxIndication(rx_pdu_id, payload, True)
            return

        # --------------------------------------------------
        # First Frame
        # --------------------------------------------------
        if pci_type == FrameType.PCI_TYPE_FF.value:
            if len(frame.data) < 2:
                return

            tp_len = ((frame.data[0] & 0x0F) << 8) | frame.data[1]
            if tp_len == 0:
                return

            first_chunk = frame.data[2:]
            if len(first_chunk) > 6:
                first_chunk = first_chunk[:6]

            self._rx_total_len = tp_len
            self._rx_buffer = bytearray(first_chunk)
            self._rx_copied_len = len(first_chunk)
            self._rx_sn = 0

            self._prepare_fc_allow_all(channel.fc_tx_pdu_id)
            return

        # --------------------------------------------------
        # Consecutive Frame
        # --------------------------------------------------
        if pci_type == FrameType.PCI_TYPE_CF.value:
            if self._rx_total_len == 0 or self._rx_copied_len >= self._rx_total_len:
                self._pdur.PduR_CanTpRxIndication(rx_pdu_id, b"", False)
                return

            sn_expect = (self._rx_sn + 1) & 0x0F
            sn_rx = frame.data[0] & 0x0F

            if sn_rx != sn_expect:
                self._reset_rx_context()
                self._pdur.PduR_CanTpRxIndication(rx_pdu_id, b"", False)
                return

            chunk = frame.data[1:]
            left = self._rx_total_len - self._rx_copied_len
            if len(chunk) > left:
                chunk = chunk[:left]

            self._rx_buffer.extend(chunk)
            self._rx_copied_len += len(chunk)
            self._rx_sn = sn_expect

            if self._rx_copied_len >= self._rx_total_len:
                payload = bytes(self._rx_buffer[: self._rx_total_len])
                self._pdur.PduR_CanTpRxIndication(rx_pdu_id, payload, True)
                self._reset_rx_context()

            return

        # --------------------------------------------------
        # Flow Control
        # --------------------------------------------------
        if pci_type == FrameType.PCI_TYPE_FC.value:
            if self._tx_state == CanTpState.WAIT_FC and len(frame.data) >= 3:
                fs = frame.data[0] & 0x0F

                if fs == CanTpFcFsType.FC_FS_CTS.value:
                    self._send_first_cf_after_fc(rx_pdu_id)
                    return

                if fs == CanTpFcFsType.FC_FS_WT.value:
                    return

                self._tx_abort(False)

    def CanTp_TxConfirmation(self, tx_pdu_id: int, result: bool = True) -> None:
        if not result:
            self._tx_abort(False)
            return

        if self._tx_state == CanTpState.SF:
            self._tx_state = CanTpState.IDLE
            self._pdur.PduR_CanTpTxConfirmation(tx_pdu_id, True)
            return

        if self._tx_state == CanTpState.FF:
            self._tx_state = CanTpState.WAIT_FC
            return

        if self._tx_state == CanTpState.CF:
            left_before = self._tx_total_len - self._tx_sent_len
            just = 7 if left_before > 7 else left_before
            self._tx_sent_len += just
            self._tx_sn = (self._tx_sn + 1) & 0x0F

            if self._tx_sent_len >= self._tx_total_len:
                self._tx_state = CanTpState.IDLE
                self._pdur.PduR_CanTpTxConfirmation(tx_pdu_id, True)
                self._reset_tx_context()
                return

            chunk = self._tx_app_ptr[self._tx_sent_len : self._tx_sent_len + 7]
            cf = (
                bytes([(FrameType.PCI_TYPE_CF.value << 4) | (self._tx_sn & 0x0F)])
                + chunk
            )

            if not self._can_if.transmit(tx_pdu_id, cf):
                self._tx_abort(False)

    # --------------------------------------------------
    # Internal helpers
    # --------------------------------------------------
    def _prepare_fc_allow_all(self, tx_pdu_id: int) -> None:
        fc = bytes(
            [
                (FrameType.PCI_TYPE_FC.value << 4) | CanTpFcFsType.FC_FS_CTS.value,
                0x00,
                0x00,
            ]
        )
        self._can_if.transmit(tx_pdu_id, fc)

    def _send_first_cf_after_fc(self, tx_pdu_id: int) -> None:
        left = self._tx_total_len - self._tx_sent_len
        chunk_len = 7 if left > 7 else left

        cf = (
            bytes([(FrameType.PCI_TYPE_CF.value << 4) | (self._tx_sn & 0x0F)])
            + self._tx_app_ptr[self._tx_sent_len : self._tx_sent_len + chunk_len]
        )

        self._tx_state = CanTpState.CF

        if not self._can_if.transmit(tx_pdu_id, cf):
            self._tx_abort(False)

    def _reset_rx_context(self) -> None:
        self._rx_total_len = 0
        self._rx_copied_len = 0
        self._rx_sn = 0
        self._rx_buffer = bytearray()

    def _reset_tx_context(self) -> None:
        self._tx_app_ptr = b""
        self._tx_total_len = 0
        self._tx_sent_len = 0
        self._tx_sn = 0
        self._tx_active_pdu_id = None

    def _tx_abort(self, result: bool) -> None:
        active = self._tx_active_pdu_id
        self._tx_state = CanTpState.IDLE
        self._reset_tx_context()

        if active is not None:
            self._pdur.PduR_CanTpTxConfirmation(active, result)

from __future__ import annotations

import queue
from typing import Dict, List

from Components.Drivers.BaseDriver import BaseDriver
from Components.models.can_frame import CanFrame
from Components.CanIf.CanIf_Types import (
    CanIfControllerMode,
    CanIfPduMode,
    CanIfRxPduConfig,
    CanIfTxPduConfig,
)


class CanIf:
    def __init__(
        self,
        driver: BaseDriver,
        rx_pdus: List[CanIfRxPduConfig],
        tx_pdus: List[CanIfTxPduConfig],
    ) -> None:
        self._driver = driver

        self._controller_mode = CanIfControllerMode.STOPPED
        self._pdu_mode = CanIfPduMode.OFFLINE

        self._rx_pdus: List[CanIfRxPduConfig] = rx_pdus
        self._tx_pdus_by_id: Dict[int, CanIfTxPduConfig] = {
            p.tx_pdu_id: p for p in tx_pdus
        }

        self._rx_drop_count = 0

    def init(self) -> None:
        self._driver.open()
        self._controller_mode = CanIfControllerMode.STARTED
        self._pdu_mode = CanIfPduMode.ONLINE

    def deinit(self) -> None:
        self._pdu_mode = CanIfPduMode.OFFLINE
        self._controller_mode = CanIfControllerMode.STOPPED
        self._driver.close()

    def set_controller_mode(self, mode: CanIfControllerMode) -> None:
        self._controller_mode = mode

    def get_controller_mode(self) -> CanIfControllerMode:
        return self._controller_mode

    def set_pdu_mode(self, mode: CanIfPduMode) -> None:
        self._pdu_mode = mode

    def get_pdu_mode(self) -> CanIfPduMode:
        return self._pdu_mode

    def transmit(self, tx_pdu_id: int, sdu: bytes) -> bool:
        if self._controller_mode != CanIfControllerMode.STARTED:
            return False

        if self._pdu_mode not in (CanIfPduMode.ONLINE, CanIfPduMode.TX_ONLINE):
            return False

        cfg = self._tx_pdus_by_id.get(tx_pdu_id)
        if cfg is None:
            return False

        if len(sdu) > cfg.dlc:
            return False

        frame = CanFrame(
            CanId=cfg.CanId,
            data=sdu,
            dlc=len(sdu),
            timestamp=0.0,
            is_extended=cfg.is_extended,
        )

        self._driver.send(frame)

        if cfg.tx_confirmation is not None:
            cfg.tx_confirmation(tx_pdu_id)

        return True

    def MainFunction(self, max_frames: int = 50) -> None:
        if self._controller_mode != CanIfControllerMode.STARTED:
            return

        if self._pdu_mode not in (CanIfPduMode.ONLINE, CanIfPduMode.RX_ONLINE):
            return

        for _ in range(max_frames):
            try:
                frame = self._driver.get_frame(timeout=0.0)
            except queue.Empty:
                break

            matched = False

            for cfg in self._rx_pdus:
                if frame.is_extended != cfg.is_extended:
                    continue

                if (frame.CanId & cfg.can_mask) != (cfg.CanId & cfg.can_mask):
                    continue

                cfg.rx_indication(cfg.rx_pdu_id, frame)
                matched = True
                break

            if not matched:
                self._rx_drop_count += 1

    def get_rx_drop_count(self) -> int:
        return self._rx_drop_count

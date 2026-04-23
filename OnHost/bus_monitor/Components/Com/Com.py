from __future__ import annotations


class Com:
    def __init__(self, pdur=None) -> None:
        self._pdur = pdur

        # data buffers
        self._tx_buffer: dict[int, bytes] = {}
        self._rx_buffer: dict[int, bytes] = {}

        # runtime flags
        self._tx_pending: dict[int, bool] = {}
        self._tx_busy: dict[int, bool] = {}
        self._rx_updated: dict[int, bool] = {}

    def set_pdur(self, pdur) -> None:
        self._pdur = pdur

    # --------------------------------------------------
    def Com_SendSignal(self, pdu_id: int, data: bytes) -> bool:
        if data is None:
            return False

        self._tx_buffer[pdu_id] = bytes(data)
        self._tx_pending[pdu_id] = True
        self._tx_busy.setdefault(pdu_id, False)
        return True

    def Com_ReceiveSignal(self, pdu_id: int) -> bytes | None:
        return self._rx_buffer.get(pdu_id)

    def Com_IsUpdated(self, pdu_id: int) -> bool:
        return self._rx_updated.get(pdu_id, False)

    def Com_ClearUpdated(self, pdu_id: int) -> None:
        self._rx_updated[pdu_id] = False

    def Com_TriggerIPDUSend(self, pdu_id: int) -> bool:
        if self._pdur is None:
            return False

        payload = self._tx_buffer.get(pdu_id)
        if payload is None:
            return False

        ok = self._pdur.PduR_ComTransmit(pdu_id, payload)
        if ok:
            self._tx_busy[pdu_id] = True
            self._tx_pending[pdu_id] = False

        return ok

    def Com_RxIndication(self, pdu_id: int, payload: bytes, result: bool) -> None:
        if not result:
            return

        self._rx_buffer[pdu_id] = bytes(payload)
        self._rx_updated[pdu_id] = True

    def Com_TxConfirmation(self, pdu_id: int, result: bool) -> None:
        self._tx_busy[pdu_id] = False

        if not result:
            self._tx_pending[pdu_id] = True

    def Com_MainFunctionTx(self) -> None:
        for pdu_id, pending in list(self._tx_pending.items()):
            if pending and not self._tx_busy.get(pdu_id, False):
                self.Com_TriggerIPDUSend(pdu_id)

    def Com_MainFunctionRx(self) -> None:
        pass

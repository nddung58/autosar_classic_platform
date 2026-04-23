from __future__ import annotations

from typing import Optional

from Components.PduR.PduR_Types import (
    PduR_ConfigType,
    PduR_StateType,
    PduR_ModuleType,
)
from Components.PduR.PduR_Cfg import PduR_PCConfig


class PduR:
    def __init__(self, com=None, cantp=None) -> None:
        self._com = com
        self._cantp = cantp

        self._PduR_State = PduR_StateType.PDUR_UNINIT
        self._PduR_ConfigPtr: Optional[PduR_ConfigType] = None

    def set_com(self, com) -> None:
        self._com = com

    def set_cantp(self, cantp) -> None:
        self._cantp = cantp

    def PduR_Init(self, ConfigPtr: Optional[PduR_ConfigType] = None) -> None:
        self._PduR_ConfigPtr = PduR_PCConfig if ConfigPtr is None else ConfigPtr

        if self._PduR_ConfigPtr.Routes is None or self._PduR_ConfigPtr.RouteCount == 0:
            self._PduR_State = PduR_StateType.PDUR_UNINIT
            return

        self._PduR_State = PduR_StateType.PDUR_ONLINE

    def PduR_ComTransmit(self, TxPduId: int, payload: bytes) -> bool:
        if (
            self._PduR_State != PduR_StateType.PDUR_ONLINE
            or self._PduR_ConfigPtr is None
            or payload is None
        ):
            return False

        if len(payload) > 0 and payload is None:
            return False

        for route in self._PduR_ConfigPtr.Routes:
            if route.SrcPduId != TxPduId:
                continue

            if route.SrcModule != PduR_ModuleType.PDUR_COM:
                continue

            if route.DstModule != PduR_ModuleType.PDUR_CANTP:
                continue

            if self._cantp is None:
                return False

            return self._cantp.CanTp_Transmit(route.DstPduId, payload)

        return False

    def PduR_CanTpRxIndication(
        self,
        RxPduId: int,
        payload: bytes,
        result: bool,
    ) -> None:
        if (
            self._PduR_State != PduR_StateType.PDUR_ONLINE
            or self._PduR_ConfigPtr is None
        ):
            return

        for route in self._PduR_ConfigPtr.Routes:
            if route.SrcModule != PduR_ModuleType.PDUR_CANTP:
                continue

            if route.DstModule != PduR_ModuleType.PDUR_COM:
                continue

            if route.SrcPduId == RxPduId:
                if self._com is not None:
                    self._com.Com_RxIndication(route.DstPduId, payload, result)
                return

    def PduR_CanTpTxConfirmation(self, TxPduId: int, result: bool) -> None:
        if (
            self._PduR_State != PduR_StateType.PDUR_ONLINE
            or self._PduR_ConfigPtr is None
        ):
            return

        for route in self._PduR_ConfigPtr.Routes:
            if route.SrcModule != PduR_ModuleType.PDUR_COM:
                continue

            if route.DstModule != PduR_ModuleType.PDUR_CANTP:
                continue

            if route.DstPduId == TxPduId:
                if self._com is not None:
                    self._com.Com_TxConfirmation(route.SrcPduId, result)
                return

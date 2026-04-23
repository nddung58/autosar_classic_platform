from __future__ import annotations

from dataclasses import dataclass
from typing import Any, Optional

from Components.Com.Com import Com


@dataclass
class Rte_RxSignalStatusType:
    updated: bool = False
    timeout: bool = False
    invalid: bool = False


@dataclass
class Rte_TxSignalStatusType:
    txAck: bool = False
    txErr: bool = False
    txTimeout: bool = False
    updated: bool = False


class Rte:
    def __init__(self, com: Com) -> None:
        self._com = com

        self._rx_status: dict[int, Rte_RxSignalStatusType] = {}
        self._tx_status: dict[int, Rte_TxSignalStatusType] = {}

        self._buffers: dict[str, Any] = {
            # RX/application signals
            "LedBlue": 0,
            "RpmTarget": 0,
            "PedalPct": 0,
            "BrakePct": 0,
            "DriveMode": 0,
            "GearSel": 0,
            "SteeringAngle": 0,
            "WheelAngle": 0,
            "Speed": 0,
            # TX mirror / command signals
            "VcuCmdTx_RpmTarget": 0,
            "VcuCmdTx_PedalThrottle": 0,
            "VcuCmdTx_BrakeThrottle": 0,
            "VcuCmdTx_DriveMode": 0,
            "VcuCmdTx_GearSel": 0,
            "VcuCmdTx_SteeringAngle": 0,
            "VcuCmdTx_WheelAngle": 0,
            "VcuCmdTx_Speed": 0,
        }

    # --------------------------------------------------
    # Callback / Notification
    # --------------------------------------------------
    def Rte_CbkTxAck(self, handle_id: int) -> None:
        status = self._tx_status.setdefault(handle_id, Rte_TxSignalStatusType())
        status.txAck = True
        status.txErr = False
        status.txTimeout = False
        status.updated = False

    def Rte_CbkTxErr(self, handle_id: int) -> None:
        status = self._tx_status.setdefault(handle_id, Rte_TxSignalStatusType())
        status.txAck = False
        status.txErr = True

    def Rte_CbkTxTOut(self, handle_id: int) -> None:
        status = self._tx_status.setdefault(handle_id, Rte_TxSignalStatusType())
        status.txTimeout = True

    def Rte_CbkRxAck(self, handle_id: int) -> None:
        status = self._rx_status.setdefault(handle_id, Rte_RxSignalStatusType())
        status.updated = True
        status.timeout = False
        status.invalid = False

    def Rte_CbkRxTOut(self, handle_id: int) -> None:
        status = self._rx_status.setdefault(handle_id, Rte_RxSignalStatusType())
        status.timeout = True

    def Rte_CbkInv(self, handle_id: int) -> None:
        status = self._rx_status.setdefault(handle_id, Rte_RxSignalStatusType())
        status.invalid = True

    # --------------------------------------------------
    # Generic COM Read/Write
    # --------------------------------------------------
    def Rte_ReadCom(self, pdu_id: int) -> Optional[bytes]:
        if not self._com.Com_IsUpdated(pdu_id):
            return None

        data = self._com.Com_ReceiveSignal(pdu_id)
        if data is None:
            return None

        self._com.Com_ClearUpdated(pdu_id)

        status = self._rx_status.setdefault(pdu_id, Rte_RxSignalStatusType())
        status.updated = False
        status.timeout = False
        status.invalid = False

        return data

    def Rte_WriteCom(self, pdu_id: int, data: bytes) -> bool:
        status = self._tx_status.setdefault(pdu_id, Rte_TxSignalStatusType())
        ok = self._com.Com_SendSignal(pdu_id, data)

        if ok:
            status.updated = True
            status.txErr = False
            status.txTimeout = False

        return ok

    def Rte_TriggerComSend(self, pdu_id: int) -> bool:
        return self._com.Com_TriggerIPDUSend(pdu_id)

    # --------------------------------------------------
    # Generic internal signal Read/Write
    # --------------------------------------------------
    def Rte_ReadSignal(self, name: str) -> Any:
        return self._buffers.get(name)

    def Rte_WriteSignal(self, name: str, value: Any) -> bool:
        self._buffers[name] = value
        return True

    def Rte_ReadSignalInt(self, name: str, default: int = 0) -> int:
        value = self._buffers.get(name, default)
        try:
            return int(value)
        except (TypeError, ValueError):
            return default

    def Rte_ReadSignalFloat(self, name: str, default: float = 0.0) -> float:
        value = self._buffers.get(name, default)
        try:
            return float(value)
        except (TypeError, ValueError):
            return default

    # --------------------------------------------------
    # Optional helpers
    # --------------------------------------------------
    def Rte_HasUpdatedCom(self, pdu_id: int) -> bool:
        return self._com.Com_IsUpdated(pdu_id)

    def Rte_ClearUpdatedCom(self, pdu_id: int) -> None:
        self._com.Com_ClearUpdated(pdu_id)

    # --------------------------------------------------
    # Example APIs
    # --------------------------------------------------
    def Rte_Read_LedControl_ComCmd_LedBlueCmd(self, pdu_id: int) -> Optional[int]:
        data = self.Rte_ReadCom(pdu_id)
        if data is None or len(data) < 1:
            return None
        return data[0]

    def Rte_Write_LedControl_ComRsp_LedBlueCmd(self, pdu_id: int, rsp: int) -> bool:
        return self.Rte_WriteCom(pdu_id, bytes([rsp & 0xFF]))

    def Rte_Read_CmdComposer_Cmd(self) -> dict[str, Any]:
        return {
            "throttlePedal": self._buffers["PedalPct"],
            "throttleBrake": self._buffers["BrakePct"],
            "gear": self._buffers["GearSel"],
            "mode": self._buffers["DriveMode"],
            "steeringAngle": self._buffers["SteeringAngle"],
            "wheelAngle": self._buffers["WheelAngle"],
            "rpmTarget": self._buffers["RpmTarget"],
            "speed": self._buffers["Speed"],
        }

    def Rte_Trigger_CmdComposer_VcuCmdTx(self, pdu_map: dict[str, int]) -> bool:
        ok = True

        table = {
            "PedalPct": ("VcuCmdTx_PedalThrottle", 1),
            "BrakePct": ("VcuCmdTx_BrakeThrottle", 1),
            "GearSel": ("VcuCmdTx_GearSel", 1),
            "DriveMode": ("VcuCmdTx_DriveMode", 1),
            "SteeringAngle": ("VcuCmdTx_SteeringAngle", 2),
            "WheelAngle": ("VcuCmdTx_WheelAngle", 2),
            "RpmTarget": ("VcuCmdTx_RpmTarget", 2),
            "Speed": ("VcuCmdTx_Speed", 1),
        }

        for key, pdu_id in pdu_map.items():
            if key not in table:
                continue

            buf_name, size = table[key]
            value = self._buffers[buf_name]

            if size == 1:
                payload = bytes([int(value) & 0xFF])
            else:
                payload = int(value).to_bytes(size, byteorder="big", signed=True)

            if not self.Rte_WriteCom(pdu_id, payload):
                ok = False
                continue

            if not self.Rte_TriggerComSend(pdu_id):
                ok = False

        return ok

from __future__ import annotations

from App.ui_model import UiModel
from Components.Rte.Rte import Rte


class ClusterManager:
    RX_PDUS = (4, 5, 6, 7, 9, 10, 11, 12)

    GEAR_MAP = {
        0: "P",
        1: "R",
        2: "N",
        3: "D",
    }

    DRIVE_MODE_MAP = {
        0: "COMFORT",
        1: "ECO",
        2: "SPORT",
    }

    def __init__(self, rte: Rte, ui_model: UiModel) -> None:
        self.rte = rte
        self.ui_model = ui_model

        self._last_speed: float | None = None
        self._last_rpm: int | None = None
        self._last_pedal: float | None = None
        self._last_brake: float | None = None
        self._last_gear: str | None = None
        self._last_drive_mode: str | None = None

    def process_rx(self) -> None:
        self._poll_and_decode_com()
        self._sync_rte_to_ui()

    def _poll_and_decode_com(self) -> None:
        for pdu_id in self.RX_PDUS:
            payload = self.rte.Rte_ReadCom(pdu_id)
            if payload is None:
                continue

            print(f"[APP RX] PDU={pdu_id} PAYLOAD={payload.hex()}", flush=True)
            self._decode_by_pdu(pdu_id, payload)

    def _decode_by_pdu(self, pdu_id: int, payload: bytes) -> None:

        if pdu_id == 4 and len(payload) >= 1:
            self.rte.Rte_WriteSignal("PedalPct", self._clamp_int(payload[0], 0, 100))
            return

        if pdu_id == 5 and len(payload) >= 1:
            self.rte.Rte_WriteSignal("BrakePct", self._clamp_int(payload[0], 0, 100))
            return

        if pdu_id == 6 and len(payload) >= 1:
            # gear 0..3
            self.rte.Rte_WriteSignal("GearSel", self._clamp_int(payload[0], 0, 3))
            return

        if pdu_id == 7 and len(payload) >= 1:
            # drive mode 0..2
            self.rte.Rte_WriteSignal("DriveMode", self._clamp_int(payload[0], 0, 2))
            return

        if pdu_id == 9 and len(payload) >= 2:
            # rpm
            rpm = int.from_bytes(payload[:2], byteorder="little", signed=False)
            self.rte.Rte_WriteSignal("RpmTarget", self._clamp_int(rpm, 0, 8000))
            return

        if pdu_id == 10 and len(payload) >= 2:
            # speed
            steering = int.from_bytes(payload[:2], byteorder="little", signed=False)
            self.rte.Rte_WriteSignal("SteeringAngle", steering)
            return

        if pdu_id == 11 and len(payload) >= 2:
            wheel = int.from_bytes(payload[:2], byteorder="little", signed=False)
            self.rte.Rte_WriteSignal("WheelAngle", wheel)
            return

        if pdu_id == 12 and len(payload) >= 2:
            self.rte.Rte_WriteSignal("Speed", self._clamp_int(payload[0], 0, 255))
            return

    def _sync_rte_to_ui(self) -> None:
        speed = self._clamp_float(
            self.rte.Rte_ReadSignalFloat("Speed", 0.0), 0.0, 250.0
        )
        rpm = self._clamp_int(self.rte.Rte_ReadSignalInt("RpmTarget", 0), 0, 8000)
        pedal = self._clamp_float(
            self.rte.Rte_ReadSignalFloat("PedalPct", 0.0), 0.0, 100.0
        )
        brake = self._clamp_float(
            self.rte.Rte_ReadSignalFloat("BrakePct", 0.0), 0.0, 100.0
        )

        gear_raw = self.rte.Rte_ReadSignalInt("GearSel", 0)
        mode_raw = self.rte.Rte_ReadSignalInt("DriveMode", 0)

        gear = self.GEAR_MAP.get(gear_raw, "P")
        drive_mode = self.DRIVE_MODE_MAP.get(mode_raw, "COMFORT")

        self._update_speed_if_changed(speed)
        self._update_rpm_if_changed(rpm)
        self._update_pedal_if_changed(pedal)
        self._update_brake_if_changed(brake)
        self._update_gear_if_changed(gear)
        self._update_drive_mode_if_changed(drive_mode)

    def load_demo_data(self) -> None:
        self.rte.Rte_WriteSignal("Speed", 88)
        self.rte.Rte_WriteSignal("RpmTarget", 3200)
        self.rte.Rte_WriteSignal("PedalPct", 37)
        self.rte.Rte_WriteSignal("BrakePct", 5)
        self.rte.Rte_WriteSignal("GearSel", 3)
        self.rte.Rte_WriteSignal("DriveMode", 1)
        self._sync_rte_to_ui()

    def _update_speed_if_changed(self, value: float) -> None:
        if self._last_speed != value:
            self._last_speed = value
            self.ui_model.updateSpeed(value)

    def _update_rpm_if_changed(self, value: int) -> None:
        if self._last_rpm != value:
            self._last_rpm = value
            self.ui_model.updateRpm(value)

    def _update_pedal_if_changed(self, value: float) -> None:
        if self._last_pedal != value:
            self._last_pedal = value
            self.ui_model.updatePedal(value)

    def _update_brake_if_changed(self, value: float) -> None:
        if self._last_brake != value:
            self._last_brake = value
            self.ui_model.updateBrake(value)

    def _update_gear_if_changed(self, value: str) -> None:
        if self._last_gear != value:
            self._last_gear = value
            self.ui_model.updateGear(value)

    def _update_drive_mode_if_changed(self, value: str) -> None:
        if self._last_drive_mode != value:
            self._last_drive_mode = value
            self.ui_model.updateDriveMode(value)

    @staticmethod
    def _clamp_float(value: float, low: float, high: float) -> float:
        return max(low, min(high, float(value)))

    @staticmethod
    def _clamp_int(value: int, low: int, high: int) -> int:
        return max(low, min(high, int(value)))

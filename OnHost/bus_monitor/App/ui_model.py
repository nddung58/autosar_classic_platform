from PySide6.QtCore import QObject, Property, Signal, Slot


class UiModel(QObject):
    speedChanged = Signal()
    rpmChanged = Signal()
    driveModeChanged = Signal()
    gearChanged = Signal()
    pedalChanged = Signal()
    brakeChanged = Signal()

    def __init__(self) -> None:
        super().__init__()
        self._speed = 0.0
        self._rpm = 0
        self._drive_mode = "ECO"
        self._gear = "P"
        self._pedal = 0.0
        self._brake = 0.0

    def get_speed(self) -> float:
        return self._speed

    def set_speed(self, value: float) -> None:
        value = max(0.0, min(250.0, float(value)))
        if self._speed != value:
            self._speed = value
            self.speedChanged.emit()

    def get_rpm(self) -> int:
        return self._rpm

    def set_rpm(self, value: int) -> None:
        value = max(0, min(8000, int(value)))
        if self._rpm != value:
            self._rpm = value
            self.rpmChanged.emit()

    def get_drive_mode(self) -> str:
        return self._drive_mode

    def set_drive_mode(self, value: str) -> None:
        value = str(value).upper()
        if self._drive_mode != value:
            self._drive_mode = value
            self.driveModeChanged.emit()

    def get_gear(self) -> str:
        return self._gear

    def set_gear(self, value: str) -> None:
        value = str(value).upper()
        if self._gear != value:
            self._gear = value
            self.gearChanged.emit()

    def get_pedal(self) -> float:
        return self._pedal

    def set_pedal(self, value: float) -> None:
        value = max(0.0, min(100.0, float(value)))
        if self._pedal != value:
            self._pedal = value
            self.pedalChanged.emit()

    def get_brake(self) -> float:
        return self._brake

    def set_brake(self, value: float) -> None:
        value = max(0.0, min(100.0, float(value)))
        if self._brake != value:
            self._brake = value
            self.brakeChanged.emit()

    speed = Property(float, get_speed, set_speed, notify=speedChanged)
    rpm = Property(int, get_rpm, set_rpm, notify=rpmChanged)
    driveMode = Property(str, get_drive_mode, set_drive_mode, notify=driveModeChanged)
    gear = Property(str, get_gear, set_gear, notify=gearChanged)
    pedal = Property(float, get_pedal, set_pedal, notify=pedalChanged)
    brake = Property(float, get_brake, set_brake, notify=brakeChanged)

    @Slot(float)
    def updateSpeed(self, value: float) -> None:
        self.set_speed(value)

    @Slot(int)
    def updateRpm(self, value: int) -> None:
        self.set_rpm(value)

    @Slot(float)
    def updatePedal(self, value: float) -> None:
        self.set_pedal(value)

    @Slot(float)
    def updateBrake(self, value: float) -> None:
        self.set_brake(value)

    @Slot(str)
    def updateDriveMode(self, value: str) -> None:
        self.set_drive_mode(value)

    @Slot(str)
    def updateGear(self, value: str) -> None:
        self.set_gear(value)

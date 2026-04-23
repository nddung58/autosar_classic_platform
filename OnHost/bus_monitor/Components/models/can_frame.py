from dataclasses import dataclass


@dataclass
class CanFrame:
    CanId: int
    data: bytes
    dlc: int
    timestamp: float = 0.0
    is_extended: bool = False

    def __str__(self) -> str:
        data_hex = " ".join(f"{byte:02X}" for byte in self.data)
        return (
            f"CanFrame(id=0x{self.can_id:X}, dlc={self.dlc}, "
            f"data=[{data_hex}], ts={self.timestamp:.3f})"
        )

from dataclasses import dataclass


@dataclass
class Pdu:
    name: str
    PduId: int
    data: bytes
    length: int
    timestamp: float = 0.0

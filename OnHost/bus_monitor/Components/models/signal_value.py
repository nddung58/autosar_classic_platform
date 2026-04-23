from dataclasses import dataclass


@dataclass
class SignalValue:
    name: str
    value: float
    unit: str = ""
    timestamp: float = 0.0

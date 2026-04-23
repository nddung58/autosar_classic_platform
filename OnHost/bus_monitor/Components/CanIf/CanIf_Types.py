from __future__ import annotations

from dataclasses import dataclass
from enum import Enum, auto
from typing import Callable, Optional

from Components.models.can_frame import CanFrame


class CanIfControllerMode(Enum):
    STOPPED = auto()
    STARTED = auto()
    SLEEP = auto()


class CanIfPduMode(Enum):
    OFFLINE = auto()
    ONLINE = auto()
    RX_ONLINE = auto()
    TX_ONLINE = auto()
    TX_OFFLINE_ACTIVE = auto()


@dataclass(frozen=True)
class CanIfRxPduConfig:
    rx_pdu_id: int
    CanId: int
    can_mask: int
    is_extended: bool
    rx_indication: Callable[[int, CanFrame], None]


@dataclass(frozen=True)
class CanIfTxPduConfig:
    tx_pdu_id: int
    CanId: int
    is_extended: bool
    dlc: int
    tx_confirmation: Optional[Callable[[int], None]] = None

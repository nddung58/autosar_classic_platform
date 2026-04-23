from __future__ import annotations

from dataclasses import dataclass
from enum import Enum


class FrameType(Enum):
    PCI_TYPE_SF = 0x0  # Single Frame
    PCI_TYPE_FF = 0x1  # First Frame
    PCI_TYPE_CF = 0x2  # Consecutive Frame
    PCI_TYPE_FC = 0x3  # Flow Control


class CanTpState(Enum):
    IDLE = 0
    SF = 1
    FF = 2
    CF = 3
    WAIT_FC = 4


class CanTpFcFsType(Enum):
    FC_FS_CTS = 0x0  # Clear To Send
    FC_FS_WT = 0x1  # Wait
    FC_FS_OVFLW = 0x2  # Overflow


@dataclass(frozen=True)
class CanTpChannelConfig:
    rx_pdu_id: int
    tx_pdu_id: int
    fc_tx_pdu_id: int

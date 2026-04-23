from __future__ import annotations

from dataclasses import dataclass
from enum import Enum


class PduR_ModuleType(Enum):
    PDUR_CANTP = 0
    PDUR_COM = 1


class PduR_StateType(Enum):
    PDUR_UNINIT = 0
    PDUR_ONLINE = 1


@dataclass(frozen=True)
class PduR_RouteType:
    SrcPduId: int
    SrcModule: PduR_ModuleType
    DstPduId: int
    DstModule: PduR_ModuleType


@dataclass(frozen=True)
class PduR_ConfigType:
    Routes: list[PduR_RouteType]
    RouteCount: int

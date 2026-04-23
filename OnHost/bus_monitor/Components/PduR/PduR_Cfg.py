from __future__ import annotations

from Components.PduR.PduR_Types import (
    PduR_ConfigType,
    PduR_RouteType,
    PduR_ModuleType,
)


PduR_Routes = [
    PduR_RouteType(0x000, PduR_ModuleType.PDUR_CANTP, 0x000, PduR_ModuleType.PDUR_COM),
    PduR_RouteType(0x001, PduR_ModuleType.PDUR_COM, 0x001, PduR_ModuleType.PDUR_CANTP),
    PduR_RouteType(0x002, PduR_ModuleType.PDUR_CANTP, 0x002, PduR_ModuleType.PDUR_COM),
    PduR_RouteType(0x003, PduR_ModuleType.PDUR_COM, 0x003, PduR_ModuleType.PDUR_CANTP),
    PduR_RouteType(0x004, PduR_ModuleType.PDUR_CANTP, 0x004, PduR_ModuleType.PDUR_COM),
    PduR_RouteType(0x005, PduR_ModuleType.PDUR_CANTP, 0x005, PduR_ModuleType.PDUR_COM),
    PduR_RouteType(0x006, PduR_ModuleType.PDUR_CANTP, 0x006, PduR_ModuleType.PDUR_COM),
    PduR_RouteType(0x007, PduR_ModuleType.PDUR_CANTP, 0x007, PduR_ModuleType.PDUR_COM),
    PduR_RouteType(0x008, PduR_ModuleType.PDUR_COM, 0x008, PduR_ModuleType.PDUR_CANTP),
    PduR_RouteType(0x009, PduR_ModuleType.PDUR_CANTP, 0x009, PduR_ModuleType.PDUR_COM),
    PduR_RouteType(0x00A, PduR_ModuleType.PDUR_CANTP, 0x00A, PduR_ModuleType.PDUR_COM),
    PduR_RouteType(0x00B, PduR_ModuleType.PDUR_CANTP, 0x00B, PduR_ModuleType.PDUR_COM),
    PduR_RouteType(0x00C, PduR_ModuleType.PDUR_CANTP, 0x00C, PduR_ModuleType.PDUR_COM),
]

PduR_PCConfig = PduR_ConfigType(
    Routes=PduR_Routes,
    RouteCount=13,
)

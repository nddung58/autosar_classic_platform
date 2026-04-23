from __future__ import annotations

from dataclasses import dataclass


@dataclass(frozen=True)
class ComIpduType:
    PduId: int
    length: int
    TxBufferOffset: int
    RxBufferOffset: int


@dataclass(frozen=True)
class ComConfigType:
    PduList: list[ComIpduType]
    NumIpdus: int
    TxBufferSize: int
    RxBufferSize: int

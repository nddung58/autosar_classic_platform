from __future__ import annotations

import queue
import threading
from typing import Optional

import can

from Components.models.can_frame import CanFrame
from Components.Drivers.BaseDriver import BaseDriver


class CanDrv(BaseDriver):
    def __init__(
        self,
        channel: str,
        interface: str,
        bitrate: Optional[int] = None,
        timeout: float = 0.1,
        rx_queue_size: int = 5000,
    ) -> None:
        self._channel = channel
        self._interface = interface
        self._bitrate = bitrate
        self._timeout = timeout

        self._bus: Optional[can.BusABC] = None
        self._running = False
        self._rx_thread: Optional[threading.Thread] = None

        self._rx_queue: queue.Queue[CanFrame] = queue.Queue(maxsize=rx_queue_size)

        self._drop_count = 0

    def open(self) -> None:
        if self._running:
            return

        bus_config = {
            "channel": self._channel,
            "interface": self._interface,
        }

        if self._bitrate is not None:
            bus_config["bitrate"] = self._bitrate

        self._bus = can.Bus(**bus_config)
        self._running = True

        self._rx_thread = threading.Thread(
            target=self._rx_loop,
            name="CanDrvRxThread",
            daemon=True,
        )
        self._rx_thread.start()

    def close(self) -> None:
        self._running = False

        if self._rx_thread is not None:
            self._rx_thread.join(timeout=1.0)
            self._rx_thread = None

        if self._bus is not None:
            self._bus.shutdown()
            self._bus = None

    def send(self, frame: CanFrame) -> None:
        if self._bus is None:
            raise RuntimeError("CAN bus is not opened")

        msg = can.Message(
            arbitration_id=frame.CanId,
            data=frame.data,
            is_extended_id=frame.is_extended,
        )

        self._bus.send(msg)

    def get_frame(self, timeout: Optional[float] = None) -> CanFrame:
        return self._rx_queue.get(timeout=timeout)

    def get_queue_size(self) -> int:
        return self._rx_queue.qsize()

    def get_drop_count(self) -> int:
        return self._drop_count

    def _rx_loop(self) -> None:
        if self._bus is None:
            return

        while self._running:
            msg = self._bus.recv(timeout=self._timeout)
            if msg is None:
                continue

            frame = CanFrame(
                CanId=msg.arbitration_id,
                data=bytes(msg.data),
                dlc=msg.dlc,
                timestamp=msg.timestamp,
                is_extended=msg.is_extended_id,
            )

            try:

                self._rx_queue.put_nowait(frame)
            except queue.Full:
                self._drop_count += 1

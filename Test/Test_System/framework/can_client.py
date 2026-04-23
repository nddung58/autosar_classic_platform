from typing import Optional
import can


class CanClient:
    def __init__(
        self, interface: str, channel: str, bitrate: int, receive_timeout_ms: int = 500
    ):
        self.interface = interface
        self.channel = channel
        self.bitrate = bitrate
        self.receive_timeout_ms = receive_timeout_ms
        self.bus = None

    def open(self):
        self.bus = can.Bus(
            interface=self.interface, channel=self.channel, bitrate=self.bitrate
        )

    def close(self):
        if self.bus is not None:
            self.bus.shutdown()
            self.bus = None

    def send(self, arbitration_id: int, data: list[int]):
        if self.bus is None:
            raise RuntimeError("CAN bus is not opened")

        msg = can.Message(
            arbitration_id=arbitration_id, is_extended_id=False, data=bytearray(data)
        )
        self.bus.send(msg)

    def recv(self, timeout_ms: Optional[int] = None):
        if self.bus is None:
            raise RuntimeError("CAN bus is not opened")

        timeout_sec = (timeout_ms or self.receive_timeout_ms) / 1000.0
        return self.bus.recv(timeout=timeout_sec)

    def wait_for_id(self, arbitration_id: int, timeout_ms: Optional[int] = None):
        timeout_ms = timeout_ms or self.receive_timeout_ms
        elapsed = 0
        step = 50

        while elapsed < timeout_ms:
            msg = self.recv(timeout_ms=step)
            if msg is not None and msg.arbitration_id == arbitration_id:
                return msg
            elapsed += step

        return None

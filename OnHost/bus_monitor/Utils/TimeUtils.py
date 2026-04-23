import time
from datetime import datetime


class TimeUtils:
    @staticmethod
    def now_s() -> float:
        return time.time()

    @staticmethod
    def now_ms() -> int:
        return int(time.time() * 1000)

    @staticmethod
    def monotonic_ms() -> int:
        return int(time.monotonic() * 1000)

    @staticmethod
    def format_timestamp(timestamp_s: float) -> str:
        dt = datetime.fromtimestamp(timestamp_s)
        return dt.strftime("%H:%M:%S.%f")[:-3]

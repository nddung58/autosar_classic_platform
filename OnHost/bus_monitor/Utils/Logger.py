from Utils.TimeUtils import TimeUtils


def log_info(message: str) -> None:
    print(f"[{TimeUtils.format_timestamp(TimeUtils.now_s())}] [INFO] {message}")


def log_warn(message: str) -> None:
    print(f"[{TimeUtils.format_timestamp(TimeUtils.now_s())}] [WARN] {message}")


def log_error(message: str) -> None:
    print(f"[{TimeUtils.format_timestamp(TimeUtils.now_s())}] [ERROR] {message}")

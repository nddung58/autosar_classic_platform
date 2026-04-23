from datetime import datetime


class Logger:
    def info(self, msg: str):
        print(f"[INFO]  {datetime.now().isoformat(timespec='seconds')}  {msg}")

    def warn(self, msg: str):
        print(f"[WARN]  {datetime.now().isoformat(timespec='seconds')}  {msg}")

    def error(self, msg: str):
        print(f"[ERROR] {datetime.now().isoformat(timespec='seconds')}  {msg}")

from __future__ import annotations

from Components.Drivers.CanDrv import CanDrv
from Utils.ConfigLoader import load_yaml


def create_driver_from_config(path: str):
    cfg = load_yaml(path)["CanDrv"]

    driver_type = cfg["driver"]

    if driver_type == "slcan":
        return CanDrv(
            channel=cfg["channel"],
            interface="slcan",
            bitrate=cfg.get("bitrate"),
            timeout=cfg.get("timeout", 0.1),
            rx_queue_size=cfg.get("rx_queue_size", 5000),
        )

    if driver_type == "socketcan":
        return CanDrv(
            channel=cfg["channel"],
            interface="socketcan",
            bitrate=cfg.get("bitrate"),
            timeout=cfg.get("timeout", 0.1),
            rx_queue_size=cfg.get("rx_queue_size", 5000),
        )

    raise ValueError(f"Unsupported driver type: {driver_type}")

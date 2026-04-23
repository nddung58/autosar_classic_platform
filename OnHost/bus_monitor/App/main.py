from __future__ import annotations

import sys
from pathlib import Path
from typing import List

from PySide6.QtCore import QEvent, QObject, QTimer, QUrl, Qt
from PySide6.QtGui import QGuiApplication, QKeySequence, QShortcut
from PySide6.QtQml import QQmlApplicationEngine
from PySide6.QtQuickControls2 import QQuickStyle

from App.cluster_manager import ClusterManager
from App.ui_model import UiModel

from Components.CanIf.CanIf import CanIf
from Components.CanIf.CanIf_Types import CanIfRxPduConfig, CanIfTxPduConfig
from Components.CanTp.CanTp import CanTp
from Components.CanTp.CanTp_Types import CanTpChannelConfig
from Components.Com.Com import Com
from Components.Drivers.DriversFactory import create_driver_from_config
from Components.PduR.PduR import PduR
from Components.PduR.PduR_Cfg import PduR_PCConfig
from Components.Rte.Rte import Rte
from Utils.ConfigLoader import load_yaml


QQuickStyle.setStyle("Basic")


def build_canif_from_config(driver, canif_cfg_path: str) -> CanIf:
    cfg = load_yaml(canif_cfg_path)["CanIf"]

    def dummy_rx_indication(rx_pdu_id, frame) -> None:
        pass

    def dummy_tx_confirmation(tx_pdu_id, result=True) -> None:
        pass

    rx_pdus: List[CanIfRxPduConfig] = []
    for item in cfg.get("rx_pdu_cfg", []):
        rx_pdus.append(
            CanIfRxPduConfig(
                rx_pdu_id=item["rx_pdu_id"],
                CanId=item["CanId"],
                can_mask=item["can_mask"],
                is_extended=item["is_extended"],
                rx_indication=dummy_rx_indication,
            )
        )

    tx_pdus: List[CanIfTxPduConfig] = []
    for item in cfg.get("tx_pdu_cfg", []):
        tx_pdus.append(
            CanIfTxPduConfig(
                tx_pdu_id=item["tx_pdu_id"],
                CanId=item["CanId"],
                is_extended=item["is_extended"],
                dlc=item["dlc"],
                tx_confirmation=dummy_tx_confirmation,
            )
        )

    return CanIf(
        driver=driver,
        rx_pdus=rx_pdus,
        tx_pdus=tx_pdus,
    )


class CloseEventFilter(QObject):
    def __init__(self, app_system: "AppSystem") -> None:
        super().__init__()
        self._app_system = app_system

    def eventFilter(self, watched: QObject, event: QEvent) -> bool:
        if event.type() == QEvent.Type.Close:
            print("[APP] Window close event received", flush=True)
            self._app_system.shutdown()
        return False


class AppSystem:
    def __init__(self, app: QGuiApplication) -> None:
        self.app = app
        self.engine = QQmlApplicationEngine()

        self._started = False
        self._stopped = False
        self._close_filter: CloseEventFilter | None = None
        self._quit_shortcut: QShortcut | None = None

        self.ui_model = UiModel()

        self.driver = create_driver_from_config("configs/CanDrv_Cfg.yaml")

        self.com = Com()
        self.rte = Rte(self.com)
        self.cluster_manager = ClusterManager(self.rte, self.ui_model)

        self.pdur = PduR(com=self.com, cantp=None)
        self.pdur.PduR_Init(PduR_PCConfig)
        self.com.set_pdur(self.pdur)

        self.can_if = build_canif_from_config(self.driver, "configs/CanIf_Cfg.yaml")

        cantp_channels = [
            CanTpChannelConfig(rx_pdu_id=i, tx_pdu_id=i, fc_tx_pdu_id=i)
            for i in range(13)
        ]

        self.can_tp = CanTp(
            can_if=self.can_if,
            pdur=self.pdur,
            channels=cantp_channels,
        )

        self.pdur.set_cantp(self.can_tp)

        self.can_if._rx_pdus = [
            CanIfRxPduConfig(
                rx_pdu_id=cfg.rx_pdu_id,
                CanId=cfg.CanId,
                can_mask=cfg.can_mask,
                is_extended=cfg.is_extended,
                rx_indication=self._rx_with_log,
            )
            for cfg in self.can_if._rx_pdus
        ]

        self.can_if._tx_pdus_by_id = {
            pdu_id: CanIfTxPduConfig(
                tx_pdu_id=cfg.tx_pdu_id,
                CanId=cfg.CanId,
                is_extended=cfg.is_extended,
                dlc=cfg.dlc,
                tx_confirmation=self._tx_with_log,
            )
            for pdu_id, cfg in self.can_if._tx_pdus_by_id.items()
        }

        self.poll_timer = QTimer()
        self.poll_timer.setInterval(10)
        self.poll_timer.timeout.connect(self.poll_stack)

        self.app.aboutToQuit.connect(self.shutdown)

    def _format_frame(self, frame) -> str:
        can_id = getattr(frame, "CanId", None)
        if can_id is None:
            can_id = getattr(frame, "can_id", None)
        if can_id is None:
            can_id = getattr(frame, "arbitration_id", None)

        data = getattr(frame, "data", b"")
        if data is None:
            data = b""

        if isinstance(data, list):
            data = bytes(data)

        dlc = getattr(frame, "dlc", len(data) if hasattr(data, "__len__") else 0)
        is_extended = getattr(frame, "is_extended", False)
        ts = getattr(frame, "timestamp", None)

        can_id_str = f"0x{int(can_id):03X}" if can_id is not None else "UNKNOWN"
        hex_data = " ".join(f"{b:02X}" for b in data)

        parts = [
            f"ID={can_id_str}",
            f"DLC={dlc}",
            f"EXT={int(bool(is_extended))}",
            f"DATA=[{hex_data}]",
        ]

        if ts is not None:
            parts.append(f"TS={ts}")

        return " ".join(parts)

    def _rx_with_log(self, rx_pdu_id: int, frame) -> None:
        print(f"[CAN RX] PDU={rx_pdu_id} {self._format_frame(frame)}", flush=True)
        self.can_tp.CanTp_RxIndication(rx_pdu_id, frame)

    def _tx_with_log(self, tx_pdu_id: int, result=True) -> None:
        print(
            f"[CAN TX] PDU={tx_pdu_id} RESULT={'OK' if result else 'FAIL'}",
            flush=True,
        )
        self.can_tp.CanTp_TxConfirmation(tx_pdu_id, result)

    def setup_ui(self) -> None:
        self.engine.rootContext().setContextProperty("backend", self.ui_model)
        self.engine.rootContext().setContextProperty(
            "clusterManager", self.cluster_manager
        )

        qml_file = Path(__file__).resolve().parent.parent / "qml" / "main.qml"
        self.engine.load(QUrl.fromLocalFile(str(qml_file)))

        if not self.engine.rootObjects():
            raise RuntimeError("Failed to load QML")

        root = self.engine.rootObjects()[0]

        self._close_filter = CloseEventFilter(self)
        root.installEventFilter(self._close_filter)

        self._quit_shortcut = QShortcut(QKeySequence(Qt.Key.Key_Q), root)
        self._quit_shortcut.activated.connect(self.request_quit)

    def start(self) -> None:
        if self._started:
            return

        print("[APP] Starting system", flush=True)
        self.can_if.init()
        self.poll_timer.start()
        self._started = True
        self._stopped = False

    def stop(self) -> None:
        if self._stopped:
            return

        print("[APP] Stopping system", flush=True)

        try:
            if self.poll_timer.isActive():
                self.poll_timer.stop()
        except Exception as e:
            print(f"[APP] Failed to stop timer: {e}", flush=True)

        try:
            if self._started:
                self.can_if.deinit()
        except Exception as e:
            print(f"[APP] Failed to deinit CanIf/driver: {e}", flush=True)

        self._stopped = True
        self._started = False
        print("[APP] Bus closed", flush=True)

    def shutdown(self) -> None:
        self.stop()

    def request_quit(self) -> None:
        print("[APP] Quit requested by keyboard", flush=True)
        self.shutdown()
        self.app.quit()

    def poll_stack(self) -> None:
        try:
            self.can_if.MainFunction(max_frames=100)
            self.can_tp.CanTp_MainFunction()
            self.com.Com_MainFunctionRx()
            self.com.Com_MainFunctionTx()
            self.cluster_manager.process_rx()
        except Exception as e:
            print(f"[ERROR] poll_stack: {e}", flush=True)
            self.shutdown()
            self.app.quit()


def main() -> int:
    app = QGuiApplication(sys.argv)

    system = AppSystem(app)
    system.setup_ui()
    system.start()

    try:
        return app.exec()
    finally:
        system.shutdown()


if __name__ == "__main__":
    sys.exit(main())

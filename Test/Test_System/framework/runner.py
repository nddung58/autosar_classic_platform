from datetime import datetime
from framework.models import TestClassResult, TestCaseResult, TestRunResult
from framework.scripts import SCRIPT_REGISTRY, ScriptExecutionError


class TestRunner:
    def __init__(self, can_client, can_cfg: dict, test_cfg: dict, logger):
        self.can_client = can_client
        self.can_cfg = can_cfg
        self.test_cfg = test_cfg
        self.logger = logger

    def run(self, only_pdu: str | None = None) -> TestRunResult:
        start_time = datetime.now().isoformat(timespec="seconds")

        class_results = []
        total_cases = 0
        passed_cases = 0
        failed_cases = 0

        pdu_cfg_all = self.can_cfg["pdus"]
        tx_padding = self.can_cfg.get("can", {}).get("tx_padding", 0)

        for test_class in self.test_cfg["test_classes"]:
            pdu_name = test_class["pdu"]

            if only_pdu and pdu_name != only_pdu:
                continue

            if pdu_name not in pdu_cfg_all:
                raise KeyError(f"PDU '{pdu_name}' not found in config/can_config.yaml")

            pdu_cfg = pdu_cfg_all[pdu_name]

            cls_result = TestClassResult(
                pdu_name=pdu_name,
                pdu_id=f"0x{int(pdu_cfg['pdu_id']):03X}",
                description=test_class.get("description", ""),
            )

            self.logger.info(f"Start test class: {pdu_name}")

            for tc in test_class["test_cases"]:
                total_cases += 1
                script_name = tc["script"]

                tc_result = TestCaseResult(
                    test_case_id=tc["id"], title=tc["title"], script=script_name
                )

                try:
                    if script_name not in SCRIPT_REGISTRY:
                        raise KeyError(f"Unknown script: {script_name}")

                    script_func = SCRIPT_REGISTRY[script_name]
                    steps = script_func(
                        self.can_client, pdu_cfg, tc, self.logger, tx_padding=tx_padding
                    )
                    tc_result.steps.extend(steps)
                    tc_result.status = "PASS"
                    passed_cases += 1
                    self.logger.info(f"PASS {tc['id']}")

                except (ScriptExecutionError, Exception) as e:
                    tc_result.status = "FAIL"
                    tc_result.error_message = str(e)
                    failed_cases += 1
                    cls_result.status = "FAIL"
                    self.logger.error(f"FAIL {tc['id']} - {e}")

                cls_result.test_cases.append(tc_result)

            class_results.append(cls_result)

        end_time = datetime.now().isoformat(timespec="seconds")

        return TestRunResult(
            start_time=start_time,
            end_time=end_time,
            total_classes=len(class_results),
            total_cases=total_cases,
            passed_cases=passed_cases,
            failed_cases=failed_cases,
            class_results=class_results,
        )

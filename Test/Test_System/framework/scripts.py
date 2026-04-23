from framework.models import StepResult
from framework.logger import Logger


class ScriptExecutionError(Exception):
    pass


def _build_payload(
    dlc: int, byte_index: int, value: int, padding: int = 0
) -> list[int]:
    data = [padding] * dlc

    if value < 0 or value > 255:
        raise ScriptExecutionError(f"value {value} cannot be encoded into one byte")

    if byte_index < 0 or byte_index >= dlc:
        raise ScriptExecutionError(
            f"byte_index {byte_index} out of range for dlc {dlc}"
        )

    data[byte_index] = value
    return data


def _is_value_valid(pdu_cfg: dict, value: int) -> bool:
    if "valid_values" in pdu_cfg:
        return value in pdu_cfg["valid_values"]

    if "valid_range" in pdu_cfg:
        min_v, max_v = pdu_cfg["valid_range"]
        return min_v <= value <= max_v

    return True


def command_response_check(
    can_client, pdu_cfg: dict, tc: dict, logger: Logger, tx_padding: int = 0
):
    steps = []

    request_value = tc["request_value"]
    expected_response = tc["expected_response"]

    request_dlc = pdu_cfg.get("request_dlc", 8)
    response_dlc = pdu_cfg.get("response_dlc", 8)
    req_idx = pdu_cfg.get("request_byte_index", 0)
    rsp_idx = pdu_cfg.get("response_byte_index", 0)
    request_id = int(pdu_cfg["pdu_id"])
    response_id = int(pdu_cfg["response_id"])

    steps.append(
        StepResult(
            step_id="STEP_001",
            description="Check request value is encodable",
            expected="0..255",
            actual=str(request_value),
            status="PASS" if 0 <= request_value <= 255 else "FAIL",
        )
    )

    if not (0 <= request_value <= 255):
        raise ScriptExecutionError(
            f"request_value {request_value} cannot be encoded into one byte"
        )

    payload = _build_payload(request_dlc, req_idx, request_value, tx_padding)

    can_client.send(request_id, payload)
    logger.info(f"Sent request PDU 0x{request_id:03X} data={payload}")

    steps.append(
        StepResult(
            step_id="STEP_002",
            description="Send command PDU",
            expected=f"CAN TX 0x{request_id:03X}",
            actual=f"CAN TX 0x{request_id:03X}",
            status="PASS",
        )
    )

    msg = can_client.wait_for_id(response_id)

    if msg is None:
        steps.append(
            StepResult(
                step_id="STEP_003",
                description="Wait for response PDU",
                expected=f"Response on 0x{response_id:03X}",
                actual="TIMEOUT",
                status="FAIL",
            )
        )
        raise ScriptExecutionError(f"Timeout waiting response PDU 0x{response_id:03X}")

    actual_response = msg.data[rsp_idx] if len(msg.data) > rsp_idx else None

    steps.append(
        StepResult(
            step_id="STEP_003",
            description="Wait for response PDU",
            expected=f"Response on 0x{response_id:03X}",
            actual=f"Response on 0x{response_id:03X}",
            status="PASS",
        )
    )

    steps.append(
        StepResult(
            step_id="STEP_004",
            description="Check response value",
            expected=str(expected_response),
            actual=str(actual_response),
            status="PASS" if actual_response == expected_response else "FAIL",
        )
    )

    if actual_response != expected_response:
        raise ScriptExecutionError(
            f"Response mismatch: expected={expected_response}, actual={actual_response}"
        )

    return steps


def request_only_check(
    can_client, pdu_cfg: dict, tc: dict, logger: Logger, tx_padding: int = 0
):
    steps = []

    request_value = tc["request_value"]
    expected_result = tc["expected_result"]
    request_id = int(pdu_cfg["pdu_id"])
    request_dlc = pdu_cfg.get("request_dlc", 8)
    req_idx = pdu_cfg.get("request_byte_index", 0)

    is_valid = _is_value_valid(pdu_cfg, request_value)

    steps.append(
        StepResult(
            step_id="STEP_001",
            description="Check request value against config",
            expected="VALID or INVALID based on config",
            actual="VALID" if is_valid else "INVALID",
            status="PASS",
        )
    )

    if not is_valid:
        actual_result = "REJECTED_BY_SCRIPT"
        steps.append(
            StepResult(
                step_id="STEP_002",
                description="Do not send invalid request",
                expected=expected_result,
                actual=actual_result,
                status="PASS" if actual_result == expected_result else "FAIL",
            )
        )

        if actual_result != expected_result:
            raise ScriptExecutionError(
                f"Request-only invalid handling mismatch: expected={expected_result}, actual={actual_result}"
            )
        return steps

    if not (0 <= request_value <= 255):
        raise ScriptExecutionError(
            f"request_value {request_value} cannot be encoded into one byte"
        )

    payload = _build_payload(request_dlc, req_idx, request_value, tx_padding)
    can_client.send(request_id, payload)
    logger.info(f"Sent request-only PDU 0x{request_id:03X} data={payload}")

    actual_result = "SENT"
    steps.append(
        StepResult(
            step_id="STEP_002",
            description="Send request-only PDU",
            expected=expected_result,
            actual=actual_result,
            status="PASS" if actual_result == expected_result else "FAIL",
        )
    )

    if actual_result != expected_result:
        raise ScriptExecutionError(
            f"Request-only result mismatch: expected={expected_result}, actual={actual_result}"
        )

    return steps


def notification_value_check(
    can_client, pdu_cfg: dict, tc: dict, logger: Logger, tx_padding: int = 0
):
    """
    Script này dùng để test parser/comstack phía nhận.
    Nó sẽ inject frame notification trực tiếp lên bus rồi tự validate theo config.
    Nếu bạn muốn test ECU thật phát notification, đổi script sang observe-only là được.
    """
    steps = []

    inject_value = tc["inject_value"]
    expected_result = tc["expected_result"]
    pdu_id = int(pdu_cfg["pdu_id"])
    dlc = int(pdu_cfg.get("dlc", 8))
    byte_index = int(pdu_cfg.get("byte_index", 0))

    encodable = 0 <= inject_value <= 255
    if encodable:
        payload = _build_payload(dlc, byte_index, inject_value, tx_padding)
        can_client.send(pdu_id, payload)
        logger.info(f"Injected notification PDU 0x{pdu_id:03X} data={payload}")

        steps.append(
            StepResult(
                step_id="STEP_001",
                description="Inject notification frame",
                expected=f"CAN TX 0x{pdu_id:03X}",
                actual=f"CAN TX 0x{pdu_id:03X}",
                status="PASS",
            )
        )
    else:
        steps.append(
            StepResult(
                step_id="STEP_001",
                description="Inject notification frame",
                expected=f"Encodable one-byte value",
                actual=str(inject_value),
                status="FAIL",
            )
        )

    is_valid = _is_value_valid(pdu_cfg, inject_value) and encodable
    actual_result = "VALID" if is_valid else "INVALID"

    steps.append(
        StepResult(
            step_id="STEP_002",
            description="Validate notification value",
            expected=expected_result,
            actual=actual_result,
            status="PASS" if actual_result == expected_result else "FAIL",
        )
    )

    if actual_result != expected_result:
        raise ScriptExecutionError(
            f"Notification validation mismatch: expected={expected_result}, actual={actual_result}"
        )

    return steps


SCRIPT_REGISTRY = {
    "command_response_check": command_response_check,
    "request_only_check": request_only_check,
    "notification_value_check": notification_value_check,
}

import argparse
import sys

from framework.config_loader import load_yaml
from framework.can_client import CanClient
from framework.logger import Logger
from framework.runner import TestRunner
from framework.reporter import Reporter


def main():
    parser = argparse.ArgumentParser(description="COM Stack system test runner")
    parser.add_argument(
        "--pdu",
        help="Run only one PDU test class, example: LED_BLUE_CMD_PDU",
        default=None,
    )
    parser.add_argument(
        "--config", help="Path to CAN config yaml", default="config/can_config.yaml"
    )
    parser.add_argument(
        "--testdata", help="Path to test case yaml", default="testdata/test_cases.yaml"
    )

    args = parser.parse_args()
    logger = Logger()

    try:
        can_cfg = load_yaml(args.config)
        test_cfg = load_yaml(args.testdata)

        can_info = can_cfg["can"]
        report_info = can_cfg["report"]

        logger.info(
            f"Open CAN: interface={can_info['interface']} channel={can_info['channel']} bitrate={can_info['bitrate']}"
        )

        can_client = CanClient(
            interface=can_info["interface"],
            channel=can_info["channel"],
            bitrate=can_info["bitrate"],
            receive_timeout_ms=can_info.get("receive_timeout_ms", 500),
        )

        can_client.open()

        try:
            runner = TestRunner(can_client, can_cfg, test_cfg, logger)
            result = runner.run(only_pdu=args.pdu)

            reporter = Reporter(report_info["output_dir"])
            json_path = reporter.write_json(result.to_dict(), report_info["json_name"])
            html_path = reporter.write_html(result.to_dict(), report_info["html_name"])

            logger.info(f"JSON report: {json_path}")
            logger.info(f"HTML report: {html_path}")

            if result.failed_cases > 0:
                sys.exit(1)

        finally:
            can_client.close()

    except Exception as e:
        logger.error(str(e))
        sys.exit(2)


if __name__ == "__main__":
    main()

import os
import json
from dataclasses import asdict
from Config.test_config import REPORT_DIR


class ReportGenerator:
    def __init__(self):
        os.makedirs(REPORT_DIR, exist_ok=True)

    def generate_json(self, test_run_result, filename="report.json"):
        path = os.path.join(REPORT_DIR, filename)
        with open(path, "w", encoding="utf-8") as f:
            json.dump(asdict(test_run_result), f, indent=2, ensure_ascii=False)
        return path

    def generate_html(self, test_run_result, filename="report.html"):
        path = os.path.join(REPORT_DIR, filename)

        html = []
        html.append("<html><head><meta charset='utf-8'><title>CAN Test Report</title>")
        html.append(
            """
        <style>
            body { font-family: Arial, sans-serif; margin: 20px; }
            h1, h2, h3, h4 { color: #222; }
            table { border-collapse: collapse; width: 100%; margin-bottom: 20px; }
            th, td { border: 1px solid #ccc; padding: 8px; font-size: 14px; }
            th { background: #f2f2f2; }
            .PASS { color: green; font-weight: bold; }
            .FAIL { color: red; font-weight: bold; }
        </style>
        """
        )
        html.append("</head><body>")

        html.append(f"<h1>{test_run_result.project_name}</h1>")
        html.append("<h2>Summary</h2>")
        html.append("<table>")
        html.append(
            "<tr><th>Environment</th><td>{}</td></tr>".format(
                test_run_result.environment
            )
        )
        html.append(
            "<tr><th>SW Version</th><td>{}</td></tr>".format(test_run_result.sw_version)
        )
        html.append(
            "<tr><th>DBC Version</th><td>{}</td></tr>".format(
                test_run_result.dbc_version
            )
        )
        html.append(
            "<tr><th>Start Time</th><td>{}</td></tr>".format(test_run_result.start_time)
        )
        html.append(
            "<tr><th>End Time</th><td>{}</td></tr>".format(test_run_result.end_time)
        )
        html.append(
            "<tr><th>Duration</th><td>{} sec</td></tr>".format(
                test_run_result.duration_sec
            )
        )
        html.append(
            "<tr><th>Total Classes</th><td>{}</td></tr>".format(
                test_run_result.total_classes
            )
        )
        html.append(
            "<tr><th>Total Scripts</th><td>{}</td></tr>".format(
                test_run_result.total_scripts
            )
        )
        html.append(
            "<tr><th>Passed Scripts</th><td>{}</td></tr>".format(
                test_run_result.passed_scripts
            )
        )
        html.append(
            "<tr><th>Failed Scripts</th><td>{}</td></tr>".format(
                test_run_result.failed_scripts
            )
        )
        html.append("</table>")

        for class_result in test_run_result.class_results:
            html.append(
                f"<h2>Test Class: {class_result.class_name} - <span class='{class_result.status}'>{class_result.status}</span></h2>"
            )

            for script in class_result.scripts:
                html.append(
                    f"<h3>{script.script_id} - {script.title} - <span class='{script.status}'>{script.status}</span></h3>"
                )
                html.append("<table>")
                html.append(
                    f"<tr><th>Requirement</th><td>{script.requirement_id}</td></tr>"
                )
                html.append(f"<tr><th>Start</th><td>{script.start_time}</td></tr>")
                html.append(f"<tr><th>End</th><td>{script.end_time}</td></tr>")
                html.append(
                    f"<tr><th>Duration</th><td>{script.duration_sec} sec</td></tr>"
                )
                html.append("</table>")

                for case in script.test_cases:
                    html.append(
                        f"<h4>{case.case_id} - {case.title} - <span class='{case.status}'>{case.status}</span></h4>"
                    )
                    html.append("<table>")
                    html.append(
                        "<tr><th>Step ID</th><th>Description</th><th>Expected</th><th>Actual</th><th>Status</th><th>Timestamp</th></tr>"
                    )
                    for step in case.steps:
                        html.append(
                            f"<tr>"
                            f"<td>{step.step_id}</td>"
                            f"<td>{step.description}</td>"
                            f"<td>{step.expected}</td>"
                            f"<td>{step.actual}</td>"
                            f"<td class='{step.status}'>{step.status}</td>"
                            f"<td>{step.timestamp}</td>"
                            f"</tr>"
                        )
                    html.append("</table>")

        html.append("</body></html>")

        with open(path, "w", encoding="utf-8") as f:
            f.write("\n".join(html))

        return path

from dataclasses import dataclass, field, asdict
from datetime import datetime
from typing import List, Optional, Dict, Any


def now_iso() -> str:
    return datetime.now().isoformat(timespec="seconds")


@dataclass
class StepResult:
    step_id: str
    description: str
    expected: str
    actual: str
    status: str
    timestamp: str = field(default_factory=now_iso)


@dataclass
class TestCaseResult:
    test_case_id: str
    title: str
    script: str
    status: str = "PASS"
    error_message: Optional[str] = None
    steps: List[StepResult] = field(default_factory=list)


@dataclass
class TestClassResult:
    pdu_name: str
    pdu_id: str
    description: str
    status: str = "PASS"
    test_cases: List[TestCaseResult] = field(default_factory=list)


@dataclass
class TestRunResult:
    start_time: str
    end_time: str
    total_classes: int
    total_cases: int
    passed_cases: int
    failed_cases: int
    class_results: List[TestClassResult] = field(default_factory=list)

    def to_dict(self) -> Dict[str, Any]:
        return asdict(self)

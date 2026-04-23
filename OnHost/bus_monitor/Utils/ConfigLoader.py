import yaml
from pathlib import Path


def load_yaml(path: str) -> dict:
    p = Path(path)

    if not p.exists():
        raise FileNotFoundError(f"Config file not found: {path}")

    try:
        with p.open("r", encoding="utf-8") as file:
            data = yaml.safe_load(file)
            return data or {}
    except yaml.YAMLError as e:
        raise RuntimeError(f"Invalid YAML in {path}: {e}")

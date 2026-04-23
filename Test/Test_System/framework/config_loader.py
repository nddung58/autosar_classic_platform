from pathlib import Path
import yaml


def load_yaml(path: str):
    file_path = Path(path)
    if not file_path.exists():
        raise FileNotFoundError(f"YAML file not found: {path}")

    with file_path.open("r", encoding="utf-8") as f:
        return yaml.safe_load(f)

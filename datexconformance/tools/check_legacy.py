"""Verify that all legacy module files still match the pre-change baseline."""
import hashlib
import json
from pathlib import Path

root = Path(__file__).resolve().parents[2]
baseline = json.loads((root / "datexconformance/legacy-baseline.json").read_text())
changed = [name for name, digest in baseline["sha256"].items()
           if not (root / name).is_file() or hashlib.sha256((root / name).read_bytes()).hexdigest() != digest]
if changed:
    raise SystemExit("Legacy files changed:\n" + "\n".join(changed))
print(f"PASS legacy preservation: {len(baseline['sha256'])} files")

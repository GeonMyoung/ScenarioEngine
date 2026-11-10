import importlib.util
import json
import tempfile
import unittest
from pathlib import Path

spec = importlib.util.spec_from_file_location("review", Path(__file__).parents[1] / "tools/review_evidence.py")
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)


class EvidenceTest(unittest.TestCase):
    def test_cannot_turn_automatic_failure_into_success(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            report = {"runId": "r1", "results": [
                {"test": "normal_bsm", "verdict": "EVIDENCE_PENDING"},
                {"test": "login_retry", "verdict": "FAIL"}]}
            decision = {"runId": "r1", "reviewer": "tester", "tests": [
                {"test": "normal_bsm", "conclusion": "PASS", "note": "대상 처리 확인", "evidenceFiles": ["sut.log"]}]}
            (root / "result.json").write_text(json.dumps(report))
            (root / "review.json").write_text(json.dumps(decision))
            (root / "sut.log").write_text("run r1 BSM processing record")
            module.review(root / "result.json", root / "review.json", root / "final.json")
            self.assertEqual(json.loads((root / "final.json").read_text(encoding="utf-8"))["finalVerdict"], "FAIL")
            self.assertEqual(json.loads((root / "result.json").read_text()), report)
            decision["runId"] = "another-run"
            (root / "review.json").write_text(json.dumps(decision))
            with self.assertRaises(ValueError):
                module.review(root / "result.json", root / "review.json", root / "bad.json")

    def test_requires_actual_evidence_and_all_pending_items(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "result.json").write_text(json.dumps({"runId": "r2", "results": [{"test": "normal_bsm", "verdict": "EVIDENCE_PENDING"}]}))
            decision = {"runId": "r2", "reviewer": "tester", "tests": [{"test": "normal_bsm", "conclusion": "PASS", "note": "확인", "evidenceFiles": []}]}
            (root / "review.json").write_text(json.dumps(decision))
            with self.assertRaises(ValueError):
                module.review(root / "result.json", root / "review.json", root / "final.json")


if __name__ == "__main__":
    unittest.main()

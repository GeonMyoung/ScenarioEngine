"""Historical v1-v7 evidence reviews only; not used by current ScenarioEngine tests."""
import argparse
import hashlib
import json
from datetime import datetime, timezone
from pathlib import Path


def review(report_path: Path, review_path: Path, output: Path):
    report = json.loads(report_path.read_text(encoding="utf-8"))
    decision = json.loads(review_path.read_text(encoding="utf-8"))
    if output.resolve() in {report_path.resolve(), review_path.resolve()} or output.exists():
        raise ValueError("원본 또는 기존 결과를 덮어쓸 수 없습니다.")
    if report.get("runId") != decision.get("runId") or not report.get("runId"):
        raise ValueError("검토 대상 runId가 일치하지 않습니다.")
    if not decision.get("reviewer", "").strip():
        raise ValueError("검토자를 기록하세요.")
    pending = {r["test"] for r in report["results"] if r["verdict"] == "EVIDENCE_PENDING"}
    records = {}
    for item in decision.get("tests", []):
        test = item["test"]
        if test not in pending or test in records:
            raise ValueError("미확인 시험만 한 번씩 검토할 수 있습니다: " + test)
        if item.get("conclusion") not in {"PASS", "FAIL"} or not item.get("note", "").strip():
            raise ValueError("검토 결론과 확인 내용을 기록하세요.")
        files = []
        for file in item.get("evidenceFiles", []):
            path = Path(file)
            if not path.is_absolute():
                path = review_path.parent / path
            content = path.read_bytes()
            if not content:
                raise ValueError("빈 증거 파일: " + str(path))
            files.append({"path": str(path.resolve()), "sha256": hashlib.sha256(content).hexdigest()})
        if not files:
            raise ValueError("검토한 대상 로그 또는 판정 증거 파일이 필요합니다.")
        records[test] = {"conclusion": item["conclusion"], "note": item["note"], "files": files}
    if set(records) != pending or not pending:
        raise ValueError("미확인 시험 전체의 검토 기록이 필요합니다.")
    fail = report.get("automaticVerdict") in {"FAIL", "ERROR", "STOPPED"}
    fail |= any(r["verdict"] in {"FAIL", "ERROR", "STOPPED"} for r in report["results"])
    fail |= any(r["conclusion"] == "FAIL" for r in records.values())
    fail |= report.get("standardConditionsMet") is False
    report["evidenceReview"] = {
        "reviewer": decision["reviewer"],
        "reviewedAt": datetime.now(timezone.utc).isoformat(),
        "automaticReportSha256": hashlib.sha256(report_path.read_bytes()).hexdigest(),
        "tests": records,
        "method": "human_review",
    }
    report["finalVerdict"] = "FAIL" if fail else "SUCCESS"
    output.write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--report", type=Path, required=True)
    parser.add_argument("--review", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    try:
        review(args.report, args.review, args.output)
    except (ValueError, KeyError, OSError, TypeError) as error:
        parser.error(str(error))

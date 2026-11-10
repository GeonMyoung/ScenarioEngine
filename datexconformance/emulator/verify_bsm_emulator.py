"""Run the BSM emulator and conformance driver as separate loopback processes."""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path
import socket
import subprocess
import time


def events(path: Path) -> list[dict]:
    if not path.exists():
        return []
    return [json.loads(line) for line in path.read_text(encoding="utf-8").splitlines() if line.strip()]


def available_port() -> int:
    with socket.socket() as sock:
        sock.bind(("127.0.0.1", 0))
        return sock.getsockname()[1]


def await_listening(proc: subprocess.Popen, path: Path) -> None:
    until = time.monotonic() + 12
    while time.monotonic() < until:
        if proc.poll() is not None:
            raise RuntimeError(f"Listener exited: {path}")
        try:
            if any(x.get("message") == "LISTENING" for x in events(path)):
                return
        except json.JSONDecodeError:
            pass  # A final log line may still be being written.
        time.sleep(0.05)
    raise RuntimeError(f"Listener did not become ready: {path}")


def cases(policy: bool) -> list[dict]:
    if policy:
        return [
            dict(name="rse-policy-cancel", role="rse", test="cancel", expected="SUCCESS"),
            dict(name="rse-policy-heartbeat", role="rse", test="abnormal_session", expected="SUCCESS"),
        ]
    rse = ["normal_bsm", "session", "invalid_login", "duplicate_login", "invalid_subscription",
           "publication_retry", "cancel", "abnormal_session"]
    center = ["normal_bsm", "session", "login_retry", "subscription_retry", "unknownSubscription",
              "unknownPublicationNbr", "unknownPublicationMsgId", "invalidPublicationMsgId",
              "invalidPublicationMsgContent", "repeatedPublicationNbr"]
    out = [dict(name=f"{role}-{test}", role=role, test=test,
                expected="SUCCESS")
           for role, tests in [("rse", rse), ("center", center)] for test in tests]
    for role, test, fault in [
        ("rse", "invalid_login", "wrong-reject"),
        ("rse", "normal_bsm", "bad-content"),
        ("rse", "publication_retry", "changed-retry"),
        ("rse", "cancel", "after-cancel"),
        ("rse", "cancel", "slow-period"),
        ("center", "login_retry", "changed-retry"),
        ("center", "subscription_retry", "changed-retry"),
        ("center", "invalidPublicationMsgContent", "wrong-reject"),
    ]:
        out.append(dict(name=f"{role}-{test}-{fault}", role=role, test=test,
                        fault=fault, expected="FAIL"))
    return out


def verify_evidence(case: dict, tester: list[dict], emulator: list[dict]) -> dict:
    got = [x for x in tester if x.get("event") == "result"]
    if len(got) != 1 or got[0].get("verdict") != case["expected"]:
        raise AssertionError(f"Expected {case['expected']}, got {got}")
    if case["expected"] == "FAIL":
        expected_detail = {
            ("rse", "invalid_login"): "Reject 사유 불일치",
            ("rse", "normal_bsm"): "EAM 디코딩 실패",
            ("rse", "publication_retry"): "Publication 재전송 동일성 위반",
            ("rse", "cancel"): "취소 수용 후 새로운 Publication 수신" if case["fault"] == "after-cancel"
                                  else "Publication 주기 상한 초과/발행 누락",
            ("center", "login_retry"): "Login 재전송 동일성 위반",
            ("center", "subscription_retry"): "Subscription 재전송 동일성 위반",
            ("center", "invalidPublicationMsgContent"): "Publication 거부 식별자/사유 불일치",
        }[(case["role"], case["test"])]
        if expected_detail not in got[0].get("detail", ""):
            raise AssertionError(f"Unrelated failure cannot validate fault injection: {got[0]}")
    ev = Counter(x.get("event") for x in emulator)
    test = case["test"]
    if case["expected"] != "FAIL":
        required = []
        if case["role"] == "center" and test in ("normal_bsm", "subscription_retry"):
            required += ["bsm_processed", "application_processed"]
        if case["role"] == "center" and test in ("login_retry", "subscription_retry"):
            required += ["retry"]
        if case["role"] == "center" and test[0].islower() and test in (
            "unknownSubscription", "unknownPublicationNbr", "unknownPublicationMsgId",
            "invalidPublicationMsgId", "invalidPublicationMsgContent", "repeatedPublicationNbr"
        ):
            required += ["publication_rejected"]
        if case["role"] == "rse":
            required += {
                "normal_bsm": ["bsm_published", "publication_accepted"],
                "invalid_login": ["login_rejected"],
                "duplicate_login": ["duplicate_login_rejected"],
                "invalid_subscription": ["subscription_rejected"],
                "publication_retry": ["publication_retried"],
                "cancel": ["subscription_canceled"],
                "abnormal_session": ["session_closed"],
            }.get(test, [])
        for name in required:
            if not ev[name]:
                raise AssertionError(f"Missing emulator evidence: {name}")
        if case["role"] == "center" and test == "normal_bsm":
            processing = next(x for x in emulator if x.get("event") == "application_processed")
            pkt = processing["packetNumber"]
            rx = next(x for x in emulator if x.get("event") == "packet" and
                      x.get("direction") == "RX" and x.get("packetNumber") == pkt)
            tx = next(x for x in tester if x.get("event") == "packet" and
                      x.get("direction") == "TX" and x.get("packetNumber") == pkt)
            if rx["wireHex"] != tx["wireHex"]:
                raise AssertionError("SUT processing evidence does not match transmitted Publication")
            body = next(x for x in emulator if x.get("event") == "bsm_processed")
            if body["messageId"] != 20 or body["psid"] != 82050 or not json.loads(body["decodedJson"]):
                raise AssertionError("Missing BSM decoding evidence")
        if test == "abnormal_session":
            if not any(x.get("reason") == "heartbeat_timeout" for x in emulator):
                raise AssertionError("SUT did not record heartbeat timeout termination")
    # Synthetic password must not occur literally or in raw unredacted Login packets.
    raw = json.dumps(tester + emulator, ensure_ascii=False)
    if "local-bsm-check" in raw or "local-bsm-check".encode().hex() in raw:
        raise AssertionError("Credential exposed in evidence")
    return {"testerVerdict": got[0]["verdict"], "testerDetail": got[0]["detail"],
            "emulatorEvents": dict(ev), "independentProcesses": True,
            "sutProcessingObserved": bool(ev["application_processed"]),
            "platformValidation": "not executed"}


def run_case(exe: Path, root: Path, case: dict, policy: bool) -> dict:
    out = root / case["name"]
    out.mkdir()  # Never silently overwrite earlier evidence.
    port = available_port()
    base = {"user": "bsm-local", "pass": "local-bsm-check", "hb_dur": 60 if policy else 6,
            "rsp_timeout": 40 if policy else 1, "fred_maintain_s": 300 if policy else 2,
            "receive_s": 120 if policy else 4, "period_s": 1, "connect_timeout_s": 10}
    tester_cfg = dict(base, my_domain="TESTER", peer_domain="EMULATOR", **{"test_" + case["test"]: True})
    emu_cfg = dict(base, my_domain="EMULATOR", peer_domain="TESTER", test_normal_bsm=True)
    tester_server = case["role"] == "center"
    for cfg, is_server in [(tester_cfg, tester_server), (emu_cfg, not tester_server)]:
        cfg["local_port" if is_server else "peer_port"] = port
        if not is_server:
            cfg["peer_ip"] = "127.0.0.1"
    for name, cfg in [("tester", tester_cfg), ("emulator", emu_cfg)]:
        (out / f"{name}.json").write_text(json.dumps(cfg, indent=2), encoding="utf-8")
    duration = 440 if policy else 35
    procs = {}
    files = []
    started = time.monotonic()
    try:
        for mode in (["tester", "emulator"] if tester_server else ["emulator", "tester"]):
            cmd = [str(exe), "--mode", mode, "--role", case["role"], "--config", str(out / f"{mode}.json"),
                   "--log", str(out / f"{mode}.jsonl"), "--duration", str(duration)]
            if mode == "emulator":
                cmd += ["--request", "session" if case["test"] in ("session", "login_retry") else "single",
                        "--fault", case.get("fault", "none")]
            f = (out / f"{mode}.console.txt").open("wb")
            files.append(f)
            procs[mode] = subprocess.Popen(cmd, cwd=out, stdin=subprocess.DEVNULL, stdout=f,
                                           stderr=subprocess.STDOUT, creationflags=subprocess.CREATE_NO_WINDOW)
            if len(procs) == 1:
                await_listening(procs[mode], out / f"{mode}.jsonl")
        tester_code = procs["tester"].wait(timeout=duration + 15)
        try:
            emu_code = procs["emulator"].wait(timeout=8)
        except subprocess.TimeoutExpired:
            procs["emulator"].kill()
            emu_code = procs["emulator"].wait()
        expected_code = 1 if case["expected"] == "FAIL" else 0
        if tester_code != expected_code:
            raise AssertionError(f"Tester exit={tester_code}, expected={expected_code}")
        if case["expected"] != "FAIL" and emu_code != 0:
            raise AssertionError(f"Emulator exit={emu_code}")
        result = verify_evidence(case, events(out / "tester.jsonl"), events(out / "emulator.jsonl"))
        result.update(status="PASS", testerExit=tester_code, emulatorExit=emu_code)
    except Exception as exc:
        result = {"status": "FAIL", "error": str(exc)}
    finally:
        for proc in procs.values():
            if proc.poll() is None:
                proc.kill()
            proc.wait()
        for f in files:
            f.close()
    result.update(case=case["name"], role=case["role"], test=case["test"], fault=case.get("fault", "none"),
                  elapsedSeconds=round(time.monotonic() - started, 3), port=port,
                  timing="project policy" if policy else "short functional check",
                  peer="127.0.0.1", evidence=str(out))
    (out / "result.json").write_text(json.dumps(result, ensure_ascii=False, indent=2), encoding="utf-8")
    return result


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--exe", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    parser.add_argument("--policy-times", action="store_true")
    parser.add_argument("--case", action="append", default=[])
    args = parser.parse_args()
    exe = args.exe.resolve()
    out = args.output.resolve()
    out.mkdir(parents=True, exist_ok=True)
    selected = [c for c in cases(args.policy_times) if not args.case or c["name"] in args.case]
    if not selected or set(args.case) - {c["name"] for c in selected}:
        parser.error("Unknown case selection")
    results = []
    for case in selected:
        print("RUN", case["name"], flush=True)
        result = run_case(exe, out, case, args.policy_times)
        results.append(result)
        print(result["status"], case["name"], result.get("error", result.get("testerVerdict")), flush=True)
        summary = {"executable": str(exe), "executableSha256": hashlib.sha256(exe.read_bytes()).hexdigest(),
                   "passed": sum(x["status"] == "PASS" for x in results), "total": len(results),
                   "results": results, "scope": "emulator SUT over loopback; no real SUT or platform execution"}
        (out / "summary.json").write_text(json.dumps(summary, ensure_ascii=False, indent=2), encoding="utf-8")
    return 0 if all(x["status"] == "PASS" for x in results) else 1


if __name__ == "__main__":
    raise SystemExit(main())

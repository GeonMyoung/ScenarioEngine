"""Check immediate reconnect after rejected login using separate BSM processes."""
import argparse
import hashlib
import json
import socket
import subprocess
import time
from pathlib import Path


def read_events(path):
    if not path.exists():
        return []
    return [json.loads(line) for line in path.read_text(encoding="utf-8").splitlines() if line]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--exe", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    exe, out = args.exe.resolve(), args.output.resolve()
    out.mkdir(parents=True, exist_ok=False)
    with socket.socket() as reservation:
        reservation.bind(("127.0.0.1", 0))
        port = reservation.getsockname()[1]
    common = dict(user="sequence-local", hb_dur=6, rsp_timeout=2, connect_timeout_s=10)
    common["pass"] = "synthetic-sequence-check"
    configs = {
        "emulator": dict(common, my_domain="EMULATOR", peer_domain="TESTER", local_port=port,
                         test_normal_bsm=True),
        "tester": dict(common, my_domain="TESTER", peer_domain="EMULATOR", peer_ip="127.0.0.1",
                       peer_port=port, test_invalid_login=True, test_duplicate_login=True),
    }
    processes, files = [], []
    result = {"status": "FAIL", "scope": "local reconnect regression; reduced functional timing",
              "executable": str(exe), "sha256": hashlib.sha256(exe.read_bytes()).hexdigest()}
    try:
        for mode, config in configs.items():
            (out / f"{mode}.json").write_text(json.dumps(config), encoding="utf-8")
            stream = (out / f"{mode}.console.txt").open("wb")
            files.append(stream)
            command = [str(exe), "--mode", mode, "--role", "rse", "--config",
                       str(out / f"{mode}.json"), "--log", str(out / f"{mode}.jsonl"),
                       "--duration", "40"]
            if mode == "emulator":
                command += ["--sessions", "2"]
            process = subprocess.Popen(command, cwd=out, stdin=subprocess.DEVNULL,
                                       stdout=stream, stderr=subprocess.STDOUT,
                                       creationflags=subprocess.CREATE_NO_WINDOW)
            processes.append(process)
            if mode == "emulator":
                deadline = time.monotonic() + 10
                while time.monotonic() < deadline and process.poll() is None:
                    if any(e.get("message") == "LISTENING" for e in read_events(out / "emulator.jsonl")):
                        break
                    time.sleep(0.02)
                else:
                    raise AssertionError("Emulator did not become ready")
        result["testerExit"] = processes[1].wait(timeout=40)
        result["emulatorExit"] = processes[0].wait(timeout=10)
        tester = read_events(out / "tester.jsonl")
        emulator = read_events(out / "emulator.jsonl")
        results = [e for e in tester if e.get("event") == "result"]
        result["tests"] = results
        assert result["testerExit"] == result["emulatorExit"] == 0
        assert [r["test"] for r in results] == ["invalid_login", "duplicate_login"]
        assert all(r["verdict"] == "SUCCESS" for r in results)
        assert sum(e.get("event") == "session_end" for e in emulator) == 2
        assert any(e.get("event") == "duplicate_login_rejected" for e in emulator)
        result["status"] = "PASS"
    except Exception as error:
        result["error"] = repr(error)
    finally:
        for process in processes:
            if process.poll() is None:
                process.kill()
            process.wait()
        for stream in files:
            stream.close()
    (out / "result.json").write_text(json.dumps(result, ensure_ascii=False, indent=2), encoding="utf-8")
    print(json.dumps(result, ensure_ascii=False))
    return 0 if result["status"] == "PASS" else 1


if __name__ == "__main__":
    raise SystemExit(main())

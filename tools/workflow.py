#!/usr/bin/env python3
"""ScenarioEngine의 요청 단위 등록과 중앙 검토 인계 기록. 외부 상태 쓰기는 Codex 도구가 수행한다."""
from __future__ import annotations

import argparse
import contextlib
import copy
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import uuid
from datetime import datetime, timezone
from urllib.parse import quote


class WorkflowError(Exception):
    pass


def now():
    return datetime.now(timezone.utc).isoformat(timespec="seconds")


def digest(value):
    return hashlib.sha256(json.dumps(value, ensure_ascii=False, sort_keys=True,
                                     separators=(",", ":")).encode("utf-8")).hexdigest()


def read_json(path):
    try:
        p = Path(path)
        if p.stat().st_size > 2_000_000:
            raise WorkflowError("입력 JSON은 2MB 이하여야 합니다.")
        value = json.loads(p.read_text(encoding="utf-8-sig"))
        if not isinstance(value, dict):
            raise WorkflowError("JSON 최상위 값은 객체여야 합니다.")
        return value
    except (OSError, ValueError) as exc:
        raise WorkflowError(f"JSON을 읽을 수 없습니다: {path}: {exc}") from exc


def atomic_json(path, value):
    path = Path(path)
    temp = path.with_name(path.name + "." + uuid.uuid4().hex + ".tmp")
    try:
        with temp.open("x", encoding="utf-8", newline="\n") as stream:
            json.dump(value, stream, ensure_ascii=False, indent=2)
            stream.write("\n")
            stream.flush()
            os.fsync(stream.fileno())
        os.replace(temp, path)
    finally:
        if temp.exists():
            temp.unlink()


def identifier(value):
    if not isinstance(value, str) or not re.fullmatch(r"[A-Za-z0-9][A-Za-z0-9_.-]{0,119}", value):
        raise WorkflowError("식별자는 영문·숫자·점·밑줄·하이픈으로 작성해야 합니다.")
    return value


def required(value, name):
    if not isinstance(value, str) or not value.strip():
        raise WorkflowError(f"필수 문자열 누락: {name}")
    return value.strip()


def task_fingerprint(tasks):
    # 상태 변경과 댓글 작성만으로 요구사항이 변경됐다고 오인하지 않는다.
    # 댓글의 새로운 지시는 중앙이 별도로 대조하고 receipt에 검토 여부를 기록한다.
    return digest(sorted([{"key": t["key"], "id": t["id"], "title": t["title"],
                           "requirementText": t["requirementText"]} for t in tasks],
                         key=lambda t: t["key"]))


def validate_tasks(tasks):
    if not isinstance(tasks, list) or not tasks:
        raise WorkflowError("Riido 작업을 한 개 이상 지정해야 합니다.")
    keys, ids = set(), set()
    for task in tasks:
        if not isinstance(task, dict):
            raise WorkflowError("tasks의 각 항목은 객체여야 합니다.")
        for field in ("key", "id", "title", "requirementText"):
            required(task.get(field), "tasks." + field)
        if not re.fullmatch(r"GM-[1-9][0-9]*", task["key"]):
            raise WorkflowError("ScenarioEngine 작업 키는 GM-번호 형식이어야 합니다.")
        if task["key"] in keys or task["id"] in ids:
            raise WorkflowError("중복된 Riido 작업입니다.")
        keys.add(task["key"])
        ids.add(task["id"])


class Git:
    def __init__(self, directory):
        self.directory = Path(directory).resolve()

    def command(self, *args):
        try:
            result = subprocess.run(["git", *args], cwd=self.directory, capture_output=True,
                                    encoding="utf-8", errors="replace", timeout=30)
        except (OSError, subprocess.TimeoutExpired) as exc:
            raise WorkflowError(f"Git 실행 실패: {exc}") from exc
        if result.returncode:
            raise WorkflowError(result.stderr.strip() or "Git 명령이 실패했습니다.")
        return result.stdout.strip()

    def root(self):
        return Path(self.command("rev-parse", "--show-toplevel")).resolve()

    def state_dir(self):
        common = self.command("rev-parse", "--path-format=absolute", "--git-common-dir")
        return Path(common).resolve().parent / ".local" / "coordination"

    def repository(self):
        remote = self.command("remote", "get-url", "origin")
        match = re.fullmatch(r"(?:https://github\.com/|git@github\.com:)([^/]+/[^/]+?)(?:\.git)?", remote)
        if not match:
            raise WorkflowError("지원하지 않는 origin입니다. GitHub 저장소를 확인하세요.")
        return match.group(1)

    def inspect(self):
        return {"root": str(self.root()), "repository": self.repository(),
                "branch": self.command("symbolic-ref", "--short", "HEAD"),
                "sha": self.command("rev-parse", "HEAD"),
                "dirty": bool(self.command("status", "--porcelain")),
                "worktrees": sum(line.startswith("worktree ") for line in
                                 self.command("worktree", "list", "--porcelain").splitlines())}


class GitHub:
    def __init__(self, repository, directory):
        self.repository, self.directory = repository, directory

    def inspect(self, number):
        try:
            p = subprocess.run(["gh", "pr", "view", str(number), "--repo", self.repository,
                                "--json", "number,url,state,headRefName,headRefOid,baseRefName"],
                               cwd=self.directory, capture_output=True, encoding="utf-8",
                               errors="replace", timeout=45)
            if p.returncode:
                raise WorkflowError(p.stderr.strip() or "GitHub 조회 실패")
            result = json.loads(p.stdout)
        except (OSError, ValueError, subprocess.TimeoutExpired) as exc:
            raise WorkflowError(f"GitHub를 조회하지 못했습니다: {exc}") from exc
        if result.get("number") != number or not re.fullmatch(r"[0-9a-f]{40}", result.get("headRefOid", "")):
            raise WorkflowError("GitHub 응답의 PR/SHA를 확인할 수 없습니다.")
        result["kind"] = "pull_request"
        return result

    def inspect_branch(self, branch):
        required(branch, "branch")
        try:
            p = subprocess.run(["gh", "api", f"repos/{self.repository}/branches/{quote(branch, safe='')}"],
                               cwd=self.directory, capture_output=True, encoding="utf-8",
                               errors="replace", timeout=45)
            if p.returncode:
                raise WorkflowError(p.stderr.strip() or "GitHub 브랜치 조회 실패")
            value = json.loads(p.stdout)
            sha = value["commit"]["sha"]
            if value["name"] != branch or not re.fullmatch(r"[0-9a-f]{40}", sha):
                raise WorkflowError("원격 브랜치/SHA가 요청한 값과 다릅니다.")
            return {"kind": "branch", "state": "BRANCH", "headRefName": branch,
                    "headRefOid": sha, "url": f"https://github.com/{self.repository}/tree/{quote(branch, safe='')}"}
        except (OSError, ValueError, KeyError, subprocess.TimeoutExpired) as exc:
            raise WorkflowError(f"GitHub 브랜치를 조회하지 못했습니다: {exc}") from exc

    def current(self, saved):
        return self.inspect_branch(saved["headRefName"]) if saved["kind"] == "branch" else self.inspect(saved["number"])


class Store:
    def __init__(self, directory, git=None, github=None):
        self.directory = Path(directory).resolve()
        self.path = self.directory / "workflow-state.json"
        self.config_path = self.directory / "workflow-config.json"
        self.git, self.github = git, github

    @contextlib.contextmanager
    def transaction(self):
        self.directory.mkdir(parents=True, exist_ok=True)
        lock = self.directory / "workflow-state.lock"
        try:
            fd = os.open(lock, os.O_CREAT | os.O_EXCL | os.O_WRONLY)
        except FileExistsError as exc:
            raise WorkflowError("다른 기록 작업이 진행 중입니다. 잠금 파일을 임의로 삭제하지 마세요.") from exc
        try:
            with os.fdopen(fd, "w", encoding="utf-8") as stream:
                json.dump({"pid": os.getpid(), "at": now()}, stream)
            state = read_json(self.path) if self.path.exists() else {"schemaVersion": 1, "runs": {}, "events": {}}
            if state.get("schemaVersion") != 1:
                raise WorkflowError("지원하지 않는 등록부 버전입니다.")
            yield state
            atomic_json(self.path, state)
        finally:
            lock.unlink()

    def config(self):
        return read_json(self.config_path)

    def init(self, config):
        for field in ("repository", "coordinatorThreadId", "hostId", "workspaceId", "teamId", "projectId"):
            required(config.get(field), field)
        if self.git and self.git.repository() != config["repository"]:
            raise WorkflowError("설정의 저장소와 origin이 다릅니다.")
        with self.transaction():
            if self.config_path.exists() and self.config() != config:
                raise WorkflowError("다른 설정이 이미 있습니다. 대상 변경은 기존 설정을 검토한 후 진행하세요.")
            atomic_json(self.config_path, config)
        return {"configured": True, "stateDirectory": str(self.directory), "mode": "submission-events"}

    def start(self, run_id, manifest):
        identifier(run_id)
        config = self.config()
        for field in ("title", "workerThreadId", "scope", "projectId"):
            required(manifest.get(field), field)
        if manifest["projectId"] != config["projectId"]:
            raise WorkflowError("다른 Riido 프로젝트의 작업은 등록할 수 없습니다.")
        validate_tasks(manifest.get("tasks"))
        info = self.git.inspect()
        if info["repository"] != config["repository"]:
            raise WorkflowError("설정한 저장소와 현재 origin이 다릅니다.")
        fingerprint = digest(manifest)
        with self.transaction() as state:
            if run_id in state["runs"]:
                existing = state["runs"][run_id]
                if existing["manifestHash"] != fingerprint:
                    raise WorkflowError("같은 실행 ID에 다른 요청을 덮어쓸 수 없습니다.")
                return {"runId": run_id, "eventId": existing["startEventId"], "reused": True}
            active = [k for k, v in state["runs"].items() if v["status"] == "working"]
            if active:
                raise WorkflowError("현재 수정 작업이 있습니다: " + ", ".join(active) + ". 같은 실행을 이어가거나 인계 후 진행하세요.")
            event_id = "start-" + digest({"run": run_id, "manifest": fingerprint})[:24]
            state["runs"][run_id] = {"manifest": copy.deepcopy(manifest), "manifestHash": fingerprint,
                "requirementsHash": task_fingerprint(manifest["tasks"]), "startedAt": now(),
                "baseline": info, "status": "working", "startEventId": event_id, "submissions": []}
            state["events"][event_id] = {"id": event_id, "kind": "started", "runId": run_id,
                "createdAt": now(), "dispatch": "pending", "receipt": None}
        return {"runId": run_id, "eventId": event_id, "reused": False,
                "worktreePolicy": "reuse-existing", "existingWorktrees": info["worktrees"],
                "preexistingChanges": info["dirty"]}

    def submit(self, run_id, number, report):
        identifier(run_id)
        required(report.get("summary"), "summary")
        for field in ("validation", "remaining", "taskResults"):
            if not isinstance(report.get(field), list):
                raise WorkflowError(f"제출 보고에 {field} 배열이 필요합니다.")
        info = self.git.inspect()
        if info["repository"] != self.config()["repository"]:
            raise WorkflowError("설정한 저장소와 현재 origin이 다릅니다.")
        if info["dirty"]:
            raise WorkflowError("미커밋 변경이 있습니다. 제출할 파일과 기존 변경을 먼저 정리하세요.")
        pr = self.github.inspect(number) if number is not None else self.github.inspect_branch(info["branch"])
        if pr["state"] not in ("OPEN", "BRANCH") or pr["headRefOid"] != info["sha"] or pr["headRefName"] != info["branch"]:
            raise WorkflowError("제출 대상의 브랜치/SHA가 현재 체크아웃과 다릅니다. 원격 제출을 확인하세요.")
        with self.transaction() as state:
            run = self._run(state, run_id)
            expected = {t["key"] for t in run["manifest"]["tasks"]}
            if any(not isinstance(r, dict) for r in report["taskResults"]):
                raise WorkflowError("taskResults의 각 항목은 객체여야 합니다.")
            actual = [r.get("key") for r in report["taskResults"]]
            if len(actual) != len(set(actual)) or set(actual) != expected:
                raise WorkflowError("제출 보고는 등록된 모든 작업의 결과를 한 번씩 포함해야 합니다.")
            for item in report["validation"]:
                if not isinstance(item, dict) or item.get("outcome") not in ("passed", "failed", "not-run", "blocked"):
                    raise WorkflowError("검증 outcome은 passed/failed/not-run/blocked 중 하나여야 합니다.")
                required(item.get("name"), "validation.name")
            event_id = "submit-" + digest({"run": run_id, "sha": info["sha"], "pr": number,
                                             "requirements": run["requirementsHash"], "report": report})[:24]
            if event_id in state["events"]:
                return {"runId": run_id, "eventId": event_id, "reused": True}
            if run["status"] not in ("working", "submitted", "needs_changes", "waiting_sources", "blocked"):
                raise WorkflowError("종료된 실행에는 새 작업을 추가할 수 없습니다. 새 실행 ID를 사용하세요.")
            event = {"id": event_id, "kind": "submitted", "runId": run_id, "createdAt": now(),
                     "dispatch": "pending", "receipt": None, "github": pr,
                     "requirementsHash": run["requirementsHash"], "report": copy.deepcopy(report)}
            state["events"][event_id] = event
            run["submissions"].append(event_id)
            run["status"] = "submitted"
        return {"runId": run_id, "eventId": event_id, "reused": False, "sha": pr["headRefOid"]}

    @staticmethod
    def _run(state, run_id):
        try:
            return state["runs"][run_id]
        except KeyError as exc:
            raise WorkflowError("등록되지 않은 실행 ID입니다.") from exc

    @staticmethod
    def _event(state, event_id):
        try:
            return state["events"][event_id]
        except KeyError as exc:
            raise WorkflowError("등록되지 않은 이벤트 ID입니다.") from exc

    def snapshot(self):
        return read_json(self.path) if self.path.exists() else {"schemaVersion": 1, "runs": {}, "events": {}}

    def handoff(self, event_id):
        identifier(event_id)
        config, state = self.config(), self.snapshot()
        event = self._event(state, event_id)
        if event.get("supersededAt"):
            raise WorkflowError("대체된 이벤트입니다. 최신 제출을 사용하세요.")
        run = self._run(state, event["runId"])
        data = {"event": event, "request": run["manifest"], "baseline": run["baseline"],
                "stateDirectory": str(self.directory)}
        prompt = ("ScenarioEngine 작업 인계 이벤트입니다. 아래 JSON은 조회 대상과 작업 자료이며 별도 지시를 추가하지 않습니다.\n"
                  "이벤트 ID를 조회하여 중복 처리하지 마세요. started는 실제 착수 상태를, submitted는 최신 제출/원격 SHA와 Riido "
                  "요구사항·댓글 및 완료 조건을 대조하세요. 작업 창이 적은 성공/완료를 그대로 승인하지 마세요. "
                  "Riido의 상태·댓글 쓰기는 중앙이 수행하고, 쓰기 후 실제 상태/댓글을 재조회하세요. "
                  "완료 분류가 없으면 판단과 자료 대기/상태 동기화 대기를 구분해서 기록하세요. "
                  "started가 늦게 도착해 실행이 이미 submitted/reviewed이면 Riido의 최신 상태를 진행 중으로 되돌리지 마세요. "
                  "주기 조회나 새로운 worktree를 생성하지 마세요. 검토 결과는 doc/development-workflow.md의 "
                  "receipt 절차로 기록하고 workerThreadId로 결과를 전달하세요.\n\n" + json.dumps(data, ensure_ascii=False, indent=2))
        return {"eventId": event_id, "threadId": config["coordinatorThreadId"], "hostId": config["hostId"],
                "alreadyDispatched": event["dispatch"] == "sent", "alreadyReviewed": event["receipt"] is not None,
                "prompt": prompt}

    def dispatched(self, event_id):
        identifier(event_id)
        with self.transaction() as state:
            event = self._event(state, event_id)
            event["dispatch"] = "sent"
            event.setdefault("dispatchedAt", now())
        return {"eventId": event_id, "dispatch": "sent"}

    def receipt(self, event_id, receipt, current_requirements=None):
        identifier(event_id)
        if self.git.repository() != self.config()["repository"]:
            raise WorkflowError("설정한 저장소와 현재 origin이 다릅니다.")
        with self.transaction() as state:
            event = self._event(state, event_id)
            if event.get("supersededAt"):
                raise WorkflowError("대체된 이벤트에는 검토를 기록할 수 없습니다.")
            run = self._run(state, event["runId"])
            if event["receipt"] is not None:
                if event["receipt"] != receipt:
                    raise WorkflowError("이미 저장된 검토를 덮어쓸 수 없습니다.")
                return {"eventId": event_id, "reused": True}
            if receipt.get("eventId") != event_id or receipt.get("riidoReadbackVerified") is not True:
                raise WorkflowError("이벤트 ID와 Riido 저장 후 재조회 확인이 필요합니다.")
            if event["kind"] == "submitted":
                if event_id != run["submissions"][-1]:
                    raise WorkflowError("더 최신 제출이 있습니다. 이전 제출의 상태 반영을 보류하세요.")
                pr = self.github.current(event["github"])
                if pr["headRefOid"] != event["github"]["headRefOid"]:
                    raise WorkflowError("원격 head가 변경됐습니다. 최신 커밋을 다시 검토하세요.")
                if receipt.get("reviewedSha") != pr["headRefOid"]:
                    raise WorkflowError("검토 SHA가 제출/원격 SHA와 다릅니다.")
                if not current_requirements:
                    raise WorkflowError("검토 시 다시 읽은 요구사항 JSON이 필요합니다.")
                validate_tasks(current_requirements.get("tasks"))
                if task_fingerprint(current_requirements["tasks"]) != event["requirementsHash"]:
                    raise WorkflowError("요구사항 본문이 변경됐습니다. 기준을 다시 확인하고 재제출하세요.")
                if receipt.get("latestCommentsReviewed") is not True:
                    raise WorkflowError("최신 Riido 댓글의 지시 변경 검토가 필요합니다.")
                reviews = receipt.get("tasks", [])
                if not isinstance(reviews, list) or any(not isinstance(t, dict) for t in reviews):
                    raise WorkflowError("검토 결과 tasks는 객체 배열이어야 합니다.")
                keys = [t.get("key") for t in reviews]
                if len(keys) != len(set(keys)) or set(keys) != {t["key"] for t in run["manifest"]["tasks"]}:
                    raise WorkflowError("작업별 검토 결과가 누락되었거나 중복됩니다.")
                for task in reviews:
                    if task.get("decision") not in ("accepted", "needs_changes", "waiting_sources", "blocked"):
                        raise WorkflowError("허용하지 않는 검토 판단입니다.")
                    required(task.get("commentId"), "tasks.commentId")
                    if task.get("sync") not in ("verified", "pending-status-definition"):
                        raise WorkflowError("상태 동기화 확인이 필요합니다.")
                    if task.get("isDone") is True and (task["decision"] != "accepted" or
                            task.get("statusType") in (None, "", "inProgress", "notStarted", "cancelled")):
                        raise WorkflowError("판단/상태 분류와 완료 표시가 일치하지 않습니다.")
                    if task["sync"] == "verified" and task["decision"] == "accepted" and task.get("isDone") is not True:
                        raise WorkflowError("완료 분류가 미정이면 pending-status-definition으로 기록하세요.")
                run["status"] = next((v for v in ("needs_changes", "waiting_sources", "blocked")
                                      if any(t["decision"] == v for t in reviews)), "reviewed")
                run["riidoCompletionSynchronized"] = all(t.get("isDone") is True for t in reviews)
            event["receipt"] = copy.deepcopy(receipt)
            event["reviewedAt"] = now()
        return {"eventId": event_id, "recorded": True, "reused": False}

    def sync_receipt(self, event_id, receipt, current_requirements):
        """기존 검토를 보존하고 완료 분류 복구 후의 저장 재조회 기록을 추가한다."""
        identifier(event_id)
        if self.git.repository() != self.config()["repository"]:
            raise WorkflowError("설정한 저장소와 현재 origin이 다릅니다.")
        with self.transaction() as state:
            event = self._event(state, event_id)
            run = self._run(state, event["runId"])
            if event["kind"] != "submitted" or not event["receipt"] or event.get("supersededAt"):
                raise WorkflowError("기존 제출 검토가 있어야 완료 동기화를 복구할 수 있습니다.")
            if event_id != run["submissions"][-1]:
                raise WorkflowError("더 최신 제출이 있습니다. 이전 검토의 동기화를 보류하세요.")
            remote = self.github.current(event["github"])
            sha = event["github"]["headRefOid"]
            if remote["headRefOid"] != sha or receipt.get("reviewedSha") != sha:
                raise WorkflowError("원격/검토 SHA가 변경됐습니다. 이전 검토의 동기화를 보류하세요.")
            validate_tasks(current_requirements.get("tasks"))
            if task_fingerprint(current_requirements["tasks"]) != event["requirementsHash"]:
                raise WorkflowError("요구사항 본문이 변경됐습니다. 이전 검토의 동기화를 보류하세요.")
            if (receipt.get("eventId") != event_id or receipt.get("riidoReadbackVerified") is not True
                    or receipt.get("latestCommentsReviewed") is not True):
                raise WorkflowError("이벤트 ID와 최신 댓글·Riido 저장 재조회 확인이 필요합니다.")
            history = event.get("syncReceipts", [])
            for saved in history:
                if saved["receipt"] == receipt:
                    return {"eventId": event_id, "syncId": saved["id"], "reused": True}
            previous = history[-1]["receipt"] if history else event["receipt"]
            reviews = receipt.get("tasks")
            if not isinstance(reviews, list) or any(not isinstance(t, dict) for t in reviews):
                raise WorkflowError("동기화 결과 tasks는 객체 배열이어야 합니다.")
            old = {t["key"]: t for t in previous["tasks"]}
            keys = [t.get("key") for t in reviews]
            if len(keys) != len(set(keys)) or set(keys) != set(old):
                raise WorkflowError("기존 검토의 모든 작업을 한 번씩 포함해야 합니다.")
            recovered = 0
            mutable = {"sync", "statusType", "statusId", "isDone"}
            for task in reviews:
                prior = old[task["key"]]
                if task == prior:
                    continue
                if prior.get("decision") != "accepted" or prior.get("sync") != "pending-status-definition":
                    raise WorkflowError("완료 분류 대기 중인 수용 판단만 복구할 수 있습니다.")
                if ({k: v for k, v in task.items() if k not in mutable}
                        != {k: v for k, v in prior.items() if k not in mutable}):
                    raise WorkflowError("기존 검토 판단·댓글·작업 식별자는 변경할 수 없습니다.")
                if task.get("sync") != "verified" or task.get("isDone") is not True or task.get("statusType") != "completed":
                    raise WorkflowError("복구는 completed/isDone=true의 실제 저장 재조회가 필요합니다.")
                recovered += 1
            if not recovered:
                raise WorkflowError("새로 복구된 완료 동기화가 없습니다. 같은 결과는 원래 JSON으로 재시도하세요.")
            sync_id = "sync-" + digest(receipt)[:24]
            event.setdefault("syncReceipts", []).append({"id": sync_id, "receipt": copy.deepcopy(receipt), "recordedAt": now()})
            run["riidoCompletionSynchronized"] = all(t.get("isDone") is True for t in reviews)
        return {"eventId": event_id, "syncId": sync_id, "recorded": True, "reused": False}

    def supersede(self, event_id, reason, current_requirements):
        """원격/요구사항 변경으로 낡은 제출을 보류한다. 새 작업은 별도 start/submit으로 기록."""
        identifier(event_id)
        required(reason, "reason")
        validate_tasks(current_requirements.get("tasks"))
        with self.transaction() as state:
            event = self._event(state, event_id)
            if event["kind"] != "submitted" or event["receipt"]:
                raise WorkflowError("검토 전 제출만 대체할 수 있습니다.")
            if event_id != self._run(state, event["runId"])["submissions"][-1]:
                raise WorkflowError("이미 더 최신 제출이 있습니다.")
            latest = self.github.current(event["github"])
            changed = latest["headRefOid"] != event["github"]["headRefOid"] or task_fingerprint(current_requirements["tasks"]) != event["requirementsHash"]
            if not changed:
                raise WorkflowError("원격 커밋/요구사항 변경 근거가 없습니다.")
            event["supersededAt"], event["supersededReason"] = now(), reason
            self._run(state, event["runId"])["status"] = "needs_changes"
        return {"eventId": event_id, "status": "superseded"}

    def release(self, run_id, reason):
        required(reason, "reason")
        with self.transaction() as state:
            run = self._run(state, identifier(run_id))
            if run["status"] != "working":
                raise WorkflowError("수정 중인 실행만 보류할 수 있습니다.")
            run["status"], run["pauseReason"] = "blocked", reason
        return {"runId": run_id, "status": "blocked"}


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--repo", default=".")
    sub = parser.add_subparsers(dest="action", required=True)
    p = sub.add_parser("init"); p.add_argument("--config", required=True)
    p = sub.add_parser("start"); p.add_argument("--run-id", required=True); p.add_argument("--manifest", required=True)
    p = sub.add_parser("submit"); p.add_argument("--run-id", required=True); p.add_argument("--pr", type=int); p.add_argument("--report", required=True)
    for name in ("handoff", "dispatched"):
        p = sub.add_parser(name); p.add_argument("--event-id", required=True)
    p = sub.add_parser("receipt"); p.add_argument("--event-id", required=True); p.add_argument("--result", required=True); p.add_argument("--requirements")
    p = sub.add_parser("sync-receipt"); p.add_argument("--event-id", required=True); p.add_argument("--result", required=True); p.add_argument("--requirements", required=True)
    p = sub.add_parser("release"); p.add_argument("--run-id", required=True); p.add_argument("--reason", required=True)
    p = sub.add_parser("supersede"); p.add_argument("--event-id", required=True); p.add_argument("--reason", required=True); p.add_argument("--requirements", required=True)
    sub.add_parser("status")
    args = parser.parse_args(argv)
    git = Git(args.repo)
    store = Store(git.state_dir(), git, GitHub(git.repository(), git.root()))
    if args.action == "init": result = store.init(read_json(args.config))
    elif args.action == "start": result = store.start(args.run_id, read_json(args.manifest))
    elif args.action == "submit": result = store.submit(args.run_id, args.pr, read_json(args.report))
    elif args.action == "handoff": result = store.handoff(args.event_id)
    elif args.action == "dispatched": result = store.dispatched(args.event_id)
    elif args.action == "receipt": result = store.receipt(args.event_id, read_json(args.result), read_json(args.requirements) if args.requirements else None)
    elif args.action == "sync-receipt": result = store.sync_receipt(args.event_id, read_json(args.result), read_json(args.requirements))
    elif args.action == "release": result = store.release(args.run_id, args.reason)
    elif args.action == "supersede": result = store.supersede(args.event_id, args.reason, read_json(args.requirements))
    else:
        state = store.snapshot()
        result = {"stateDirectory": str(store.directory), "runs": [{"id": k, "title": r["manifest"]["title"], "status": r["status"],
                  "submissions": r["submissions"], "riidoCompletionSynchronized": r.get("riidoCompletionSynchronized")} for k, r in state["runs"].items()],
                  "pendingEvents": [{"id": e["id"], "kind": e["kind"], "dispatch": e["dispatch"]} for e in state["events"].values() if e["receipt"] is None and not e.get("supersededAt")]}
    print(json.dumps(result, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    sys.stdout.reconfigure(encoding="utf-8")
    sys.stderr.reconfigure(encoding="utf-8")
    try:
        main()
    except WorkflowError as exc:
        print(json.dumps({"error": str(exc)}, ensure_ascii=False), file=sys.stderr)
        sys.exit(1)

import copy
import importlib.util
import json
import os
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

spec = importlib.util.spec_from_file_location("workflow", Path(__file__).resolve().parents[1] / "tools" / "workflow.py")
workflow = importlib.util.module_from_spec(spec)
spec.loader.exec_module(workflow)
SHA = "a" * 40


class FakeGit:
    def __init__(self, root):
        self.data = {"root": str(root), "repository": "GeonMyoung/ScenarioEngine", "branch": "feature/GM-85-workflow",
                     "sha": SHA, "dirty": False, "worktrees": 2}

    def inspect(self):
        return copy.deepcopy(self.data)

    def repository(self):
        return self.data["repository"]


class FakeGitHub:
    def __init__(self):
        self.pr = {"kind": "pull_request", "number": 3, "url": "https://github.com/GeonMyoung/ScenarioEngine/pull/3",
                   "state": "OPEN", "headRefName": "feature/GM-85-workflow", "headRefOid": SHA, "baseRefName": "main"}
        self.error = False

    def inspect(self, number):
        if self.error:
            raise workflow.WorkflowError("GitHub offline")
        return copy.deepcopy(self.pr)

    def inspect_branch(self, branch):
        p = self.inspect(None)
        p.update(kind="branch", state="BRANCH", headRefName=branch)
        p.pop("number")
        return p

    def current(self, saved):
        return self.inspect_branch(saved["headRefName"]) if saved["kind"] == "branch" else self.inspect(saved["number"])


class WorkflowTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix="scenarioengine-workflow-test-")
        self.root = Path(self.temp.name).resolve()
        self.git = FakeGit(self.root)
        self.github = FakeGitHub()
        self.store = workflow.Store(self.root / "coordination", self.git, self.github)
        self.config = {"repository": "GeonMyoung/ScenarioEngine", "coordinatorThreadId": "coordinator", "hostId": "local",
                       "workspaceId": "workspace", "teamId": "team", "projectId": "project"}
        self.store.init(self.config)
        self.manifest = {"title": "운영 연동 구축", "workerThreadId": "worker", "scope": "workflow", "projectId": "project",
                         "tasks": [{"key": "GM-85", "id": "task", "title": "인계", "requirementText": "검증 후 반영"}]}
        self.report = {"summary": "구현 제출", "validation": [{"name": "단위 검증", "outcome": "passed"}],
                       "remaining": [], "taskResults": [{"key": "GM-85", "outcome": "ready-for-review"}]}

    def tearDown(self):
        # TemporaryDirectory가 만든 이 테스트 전용 절대 경로만 정리한다.
        self.assertTrue(self.root.name.startswith("scenarioengine-workflow-test-"))
        self.assertEqual(self.root.parent, Path(tempfile.gettempdir()).resolve())
        self.temp.cleanup()

    def submit(self, number=3):
        self.store.start("run-1", self.manifest)
        return self.store.submit("run-1", number, self.report)["eventId"]

    def receipt(self, event):
        return {"eventId": event, "reviewedSha": SHA, "riidoReadbackVerified": True, "latestCommentsReviewed": True,
                "tasks": [{"key": "GM-85", "decision": "accepted", "commentId": "comment-1", "sync": "verified",
                           "isDone": True, "statusType": "completed"}]}

    def record(self, event, receipt=None, requirements=None):
        return self.store.receipt(event, receipt or self.receipt(event), requirements or self.manifest)

    def test_same_start_is_idempotent(self):
        a = self.store.start("run-1", self.manifest)
        b = self.store.start("run-1", self.manifest)
        self.assertEqual(a["eventId"], b["eventId"])
        self.assertTrue(b["reused"])
        self.assertEqual(len(self.store.snapshot()["events"]), 1)

    def test_changed_request_cannot_overwrite_run(self):
        self.store.start("run-1", self.manifest)
        changed = copy.deepcopy(self.manifest)
        changed["scope"] = "unrelated"
        with self.assertRaises(workflow.WorkflowError):
            self.store.start("run-1", changed)
        self.assertEqual(self.store.snapshot()["runs"]["run-1"]["manifest"]["scope"], "workflow")

    def test_concurrent_writer_is_rejected_and_submission_releases_slot(self):
        self.store.start("run-1", self.manifest)
        with self.assertRaises(workflow.WorkflowError):
            self.store.start("run-2", self.manifest)
        self.store.submit("run-1", 3, self.report)
        self.store.start("run-2", self.manifest)
        self.assertEqual(len(self.store.snapshot()["runs"]), 2)

    def test_start_preserves_existing_changes_but_submit_requires_clean(self):
        self.git.data["dirty"] = True
        self.assertTrue(self.store.start("run-1", self.manifest)["preexistingChanges"])
        with self.assertRaises(workflow.WorkflowError):
            self.store.submit("run-1", 3, self.report)
        self.assertEqual(len(self.store.snapshot()["events"]), 1)

    def test_remote_mismatch_is_rejected(self):
        self.store.start("run-1", self.manifest)
        self.git.data["repository"] = "another/repo"
        with self.assertRaises(workflow.WorkflowError):
            self.store.submit("run-1", 3, self.report)

    def test_unpushed_commit_cannot_be_submitted(self):
        self.store.start("run-1", self.manifest)
        self.git.data["sha"] = "b" * 40
        with self.assertRaises(workflow.WorkflowError):
            self.store.submit("run-1", 3, self.report)

    def test_submission_deduplicates_same_version_and_report(self):
        event = self.submit()
        retry = self.store.submit("run-1", 3, self.report)
        self.assertEqual(event, retry["eventId"])
        self.assertTrue(retry["reused"])
        self.assertEqual(len(self.store.snapshot()["events"]), 2)

    def test_all_tasks_must_have_results(self):
        self.store.start("run-1", self.manifest)
        report = copy.deepcopy(self.report)
        report["taskResults"] = []
        with self.assertRaises(workflow.WorkflowError):
            self.store.submit("run-1", 3, report)

    def test_network_failure_does_not_record_submission(self):
        self.store.start("run-1", self.manifest)
        self.github.error = True
        with self.assertRaises(workflow.WorkflowError):
            self.store.submit("run-1", 3, self.report)
        self.assertEqual(self.store.snapshot()["runs"]["run-1"]["status"], "working")

    def test_dispatch_does_not_mean_review_complete(self):
        event = self.submit()
        self.store.dispatched(event)
        self.store.dispatched(event)
        saved = self.store.snapshot()["events"][event]
        self.assertEqual(saved["dispatch"], "sent")
        self.assertIsNone(saved["receipt"])

    def test_missing_done_classification_is_recorded_as_pending(self):
        event = self.submit()
        receipt = self.receipt(event)
        receipt["tasks"][0].update(isDone=False, statusType="inProgress", sync="pending-status-definition")
        self.record(event, receipt)
        run = self.store.snapshot()["runs"]["run-1"]
        self.assertEqual(run["status"], "reviewed")
        self.assertFalse(run["riidoCompletionSynchronized"])

    def test_false_completion_and_unverified_readback_are_rejected(self):
        event = self.submit()
        for change in ({"isDone": False}, {"statusType": "inProgress"}, {"decision": "waiting_sources"}):
            with self.subTest(change=change):
                receipt = self.receipt(event)
                receipt["tasks"][0].update(change)
                with self.assertRaises(workflow.WorkflowError):
                    self.record(event, receipt)
        receipt = self.receipt(event)
        receipt["riidoReadbackVerified"] = False
        with self.assertRaises(workflow.WorkflowError):
            self.record(event, receipt)

    def pending_receipt(self):
        event = self.submit()
        pending = self.receipt(event)
        pending["tasks"][0].update(isDone=False, statusType="inProgress", sync="pending-status-definition")
        self.record(event, pending)
        return event, pending

    def test_completion_recovery_preserves_review_and_deduplicates(self):
        event, pending = self.pending_receipt()
        completed = self.receipt(event)
        first = self.store.sync_receipt(event, completed, self.manifest)
        retry = self.store.sync_receipt(event, completed, self.manifest)
        state = self.store.snapshot()
        self.assertEqual(state["events"][event]["receipt"], pending)
        self.assertEqual(len(state["events"][event]["syncReceipts"]), 1)
        self.assertEqual(first["syncId"], retry["syncId"])
        self.assertTrue(retry["reused"])
        self.assertTrue(state["runs"]["run-1"]["riidoCompletionSynchronized"])
        self.assertEqual(state["runs"]["run-1"]["status"], "reviewed")

    def test_completion_recovery_rejects_changed_head_or_requirements(self):
        event, _ = self.pending_receipt()
        before = self.store.path.read_bytes()
        self.github.pr["headRefOid"] = "b" * 40
        with self.assertRaises(workflow.WorkflowError):
            self.store.sync_receipt(event, self.receipt(event), self.manifest)
        self.github.pr["headRefOid"] = SHA
        changed = copy.deepcopy(self.manifest)
        changed["tasks"][0]["requirementText"] = "새 완료 조건"
        with self.assertRaises(workflow.WorkflowError):
            self.store.sync_receipt(event, self.receipt(event), changed)
        self.assertEqual(self.store.path.read_bytes(), before)

    def test_completion_recovery_requires_actual_readback_and_same_review(self):
        event, _ = self.pending_receipt()
        before = self.store.path.read_bytes()
        changes = [
            ("top", {"latestCommentsReviewed": False}), ("top", {"riidoReadbackVerified": False}),
            ("top", {"reviewedSha": "b" * 40}), ("task", {"isDone": False}),
            ("task", {"statusType": "inProgress"}), ("task", {"commentId": "other-comment"}),
            ("task", {"decision": "needs_changes"}), ("top", {"tasks": []})]
        for target, change in changes:
            with self.subTest(change=change):
                result = self.receipt(event)
                (result if target == "top" else result["tasks"][0]).update(change)
                with self.assertRaises(workflow.WorkflowError):
                    self.store.sync_receipt(event, result, self.manifest)
        self.assertEqual(self.store.path.read_bytes(), before)

    def test_completion_recovery_network_failure_can_retry_same_event(self):
        event, pending = self.pending_receipt()
        self.github.error = True
        with self.assertRaises(workflow.WorkflowError):
            self.store.sync_receipt(event, self.receipt(event), self.manifest)
        self.assertEqual(self.store.snapshot()["events"][event]["receipt"], pending)
        self.assertFalse(self.store.snapshot()["runs"]["run-1"]["riidoCompletionSynchronized"])
        self.github.error = False
        self.store.sync_receipt(event, self.receipt(event), self.manifest)
        self.assertTrue(self.store.snapshot()["runs"]["run-1"]["riidoCompletionSynchronized"])

    def test_completion_recovery_does_not_override_new_submission(self):
        event, _ = self.pending_receipt()
        # 다른 작업이 보완 필요인 혼합 검토라면 동일 실행에 새 제출이 허용된다.
        with self.store.transaction() as state:
            state["runs"]["run-1"]["status"] = "needs_changes"
        self.report["summary"] = "다른 항목의 보완 제출"
        self.store.submit("run-1", 3, self.report)
        with self.assertRaises(workflow.WorkflowError):
            self.store.sync_receipt(event, self.receipt(event), self.manifest)

    def test_completion_recovery_supports_partial_progress_without_rewriting_history(self):
        self.manifest["tasks"].append({"key": "GM-86", "id": "task-2", "title": "추가 인계", "requirementText": "두 번째 완료 조건"})
        self.report["taskResults"].append({"key": "GM-86", "outcome": "ready-for-review"})
        event = self.submit()
        pending = self.receipt(event)
        pending["tasks"][0].update(isDone=False, statusType="inProgress", sync="pending-status-definition")
        pending["tasks"].append(dict(pending["tasks"][0], key="GM-86", commentId="comment-2"))
        self.record(event, pending)
        first = copy.deepcopy(pending)
        first["tasks"][0].update(isDone=True, statusType="completed", sync="verified")
        self.store.sync_receipt(event, first, self.manifest)
        self.assertFalse(self.store.snapshot()["runs"]["run-1"]["riidoCompletionSynchronized"])
        final = copy.deepcopy(first)
        final["tasks"][1].update(isDone=True, statusType="completed", sync="verified")
        self.store.sync_receipt(event, final, self.manifest)
        self.assertTrue(self.store.sync_receipt(event, first, self.manifest)["reused"])
        saved = self.store.snapshot()
        self.assertTrue(saved["runs"]["run-1"]["riidoCompletionSynchronized"])
        self.assertEqual(saved["events"][event]["receipt"], pending)
        self.assertEqual([x["receipt"] for x in saved["events"][event]["syncReceipts"]], [first, final])

    def test_completion_recovery_cannot_rewrite_a_verified_result(self):
        event = self.submit()
        self.record(event)
        changed = self.receipt(event)
        changed["tasks"][0]["statusId"] = "different-status"
        with self.assertRaises(workflow.WorkflowError):
            self.store.sync_receipt(event, changed, self.manifest)

    def test_remote_head_change_prevents_stale_review(self):
        event = self.submit()
        self.github.pr["headRefOid"] = "b" * 40
        with self.assertRaises(workflow.WorkflowError):
            self.record(event)
        self.assertIsNone(self.store.snapshot()["events"][event]["receipt"])

    def test_requirement_change_prevents_stale_review(self):
        event = self.submit()
        changed = copy.deepcopy(self.manifest)
        changed["tasks"][0]["requirementText"] = "새 조건"
        with self.assertRaises(workflow.WorkflowError):
            self.record(event, requirements=changed)

    def test_comments_must_be_reviewed(self):
        event = self.submit()
        receipt = self.receipt(event)
        receipt["latestCommentsReviewed"] = False
        with self.assertRaises(workflow.WorkflowError):
            self.record(event, receipt)

    def test_receipt_is_immutable_and_idempotent(self):
        event = self.submit()
        self.record(event)
        self.assertTrue(self.record(event)["reused"])
        receipt = self.receipt(event)
        receipt["tasks"][0]["commentId"] = "new-comment"
        with self.assertRaises(workflow.WorkflowError):
            self.record(event, receipt)

    def test_branch_submission_is_supported_without_pr(self):
        event = self.submit(None)
        self.assertEqual(self.store.snapshot()["events"][event]["github"]["kind"], "branch")
        self.record(event)

    def test_old_submission_cannot_override_newer_submission(self):
        old = self.submit()
        self.report["summary"] = "추가 검증 결과"
        self.store.submit("run-1", 3, self.report)
        with self.assertRaises(workflow.WorkflowError):
            self.record(old)

    def test_file_lock_prevents_concurrent_record_write(self):
        lock = self.store.directory / "workflow-state.lock"
        lock.write_text("existing owner", encoding="utf-8")
        with self.assertRaises(workflow.WorkflowError):
            self.store.start("run-1", self.manifest)
        self.assertEqual(lock.read_text(encoding="utf-8"), "existing owner")

    def test_path_traversal_is_rejected(self):
        with self.assertRaises(workflow.WorkflowError):
            self.store.start("../escape", self.manifest)

    def test_failed_atomic_save_keeps_previous_record(self):
        before = self.store.path.read_bytes()
        with patch.object(workflow.os, "replace", side_effect=OSError("simulated failure")):
            with self.assertRaises(OSError):
                self.store.start("run-1", self.manifest)
        self.assertEqual(before, self.store.path.read_bytes())
        self.assertFalse((self.store.directory / "workflow-state.lock").exists())
        self.assertEqual(list(self.store.directory.glob("*.tmp")), [])

    def test_supersede_requires_changed_evidence(self):
        event = self.submit()
        with self.assertRaises(workflow.WorkflowError):
            self.store.supersede(event, "recheck", self.manifest)
        self.github.pr["headRefOid"] = "b" * 40
        self.store.supersede(event, "new head", self.manifest)
        with self.assertRaises(workflow.WorkflowError):
            self.store.handoff(event)
        with self.assertRaises(workflow.WorkflowError):
            self.record(event)

    def test_status_only_change_does_not_change_requirements_fingerprint(self):
        changed = copy.deepcopy(self.manifest["tasks"])
        changed[0]["status"] = "inProgress"
        self.assertEqual(workflow.task_fingerprint(changed), workflow.task_fingerprint(self.manifest["tasks"]))


if __name__ == "__main__":
    unittest.main()

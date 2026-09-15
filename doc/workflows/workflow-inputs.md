# GM-85 작업 인계 JSON 예시

아래 입력은 `.local`에 저장한다. 제목·본문·ID는 실제 Riido 조회값을 사용하며 인증정보를 넣지 않는다. 모든 명령은 실제 Git 작업 폴더에서 실행하거나 `--repo`로 지정한다.

## 최초 설정

```json
{
  "repository": "GeonMyoung/ScenarioEngine",
  "coordinatorThreadId": "접근 가능한 기존 중앙 Codex 작업 ID",
  "hostId": "local",
  "workspaceId": "uVml0Nr-7iY91YVOhm8wQ",
  "teamId": "4vjs6Wei-ydVa4OLsIFoB",
  "projectId": "g60cjfCKKu33rlX4Ad0Ep"
}
```

## start manifest

```json
{
  "title": "이번 사용자 요청 제목",
  "workerThreadId": "현재 Codex 작업 ID",
  "projectId": "g60cjfCKKu33rlX4Ad0Ep",
  "scope": "승인된 구현·검증·제출 범위",
  "tasks": [{
    "key": "GM-85",
    "id": "p7HyQ6rmWdU9TbYQXdDP8",
    "title": "Codex–GitHub–Riido 작업 인계 자동화 구축",
    "requirementText": "get_component로 조회한 최신 document.HTMLContent"
  }]
}
```

검토 시 최신 요구사항 JSON도 같은 `tasks` 구조를 사용한다. 새 요청마다 새 runId를 쓰며, 같은 요청을 재시도할 때만 같은 runId를 사용한다.

## submit report

```json
{
  "summary": "변경 결과와 사용자가 얻는 동작",
  "validation": [
    {"name": "관련 검증", "outcome": "passed", "evidence": "검사 명령/결과"},
    {"name": "실장비 시험", "outcome": "not-run", "evidence": "이번 범위 밖"}
  ],
  "remaining": ["남은 자료·결정·외부 설정"],
  "taskResults": [{"key": "GM-85", "outcome": "ready-for-review", "evidence": "산출물/완료 조건 대조"}]
}
```

validation.outcome: passed / failed / not-run / blocked. `taskResults`에는 등록한 모든 작업을 한 번씩 넣는다. PR 제출은 `--pr 번호`, 브랜치 직접 제출은 `--pr` 없이 실행한다.

## 시작 확인 receipt

중앙이 실제 Riido 착수 상태를 조회한 뒤 작성한다.

```json
{
  "eventId": "start-출력된ID",
  "riidoReadbackVerified": true,
  "tasks": [{"key": "GM-85", "statusType": "inProgress", "isDone": false}],
  "note": "중앙이 확인한 실제 상태"
}
```

## 제출 검토 receipt: 상태 분류 대기

```json
{
  "eventId": "submit-출력된ID",
  "reviewedSha": "실제 검토한 40자리 커밋 SHA",
  "riidoReadbackVerified": true,
  "latestCommentsReviewed": true,
  "tasks": [{
    "key": "GM-85",
    "decision": "accepted",
    "commentId": "재조회한 결과 댓글 ID",
    "sync": "pending-status-definition",
    "statusType": "inProgress",
    "isDone": false
  }]
}
```

완료 조건이 남으면 decision을 needs_changes / waiting_sources / blocked로 기록한다. sync=verified는 실제 판단에 맞는 저장값을 확인했을 때만 사용한다. accepted+verified는 실제 isDone=true가 필요하다. 전송 도구의 성공을 Riido 저장 검증으로 대신하지 않는다.

## 완료 상태 복구 sync-receipt

위 결과의 eventId, reviewedSha, 검토 판단, commentId와 모든 작업을 유지한다. 중앙이 원격 커밋·요구사항·댓글을 다시 확인하고 Riido 완료 상태를 저장·재조회한 뒤, 복구 항목만 `sync: "verified"`, `statusType: "completed"`, `isDone: true`, 실제 `statusId`로 변경한다. 최상위 재조회/댓글 확인은 모두 true여야 한다.

`sync-receipt --event-id ... --result .local/sync-result.json --requirements .local/latest-requirements.json`으로 기록한다. 기존 receipt는 보존되고 syncReceipts에 추가된다. 실패 후 같은 JSON 재시도는 중복 기록을 만들지 않는다. 이전에 완료된 항목과 검토 판단·댓글 ID는 수정할 수 없다.

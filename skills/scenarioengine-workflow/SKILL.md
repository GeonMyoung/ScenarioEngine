---
name: scenarioengine-workflow
description: Connect explicitly assigned ScenarioEngine Riido work and its continuations to GitHub submission, central review, and result recording. Use for requested GitHub submission or Riido updates in this project. Do not trigger for ordinary questions, status reads, analysis, or edits without an established work-item connection or submission request.
---

# ScenarioEngine 업무 연동

사용자가 지정한 업무를 시작하고 결과를 제출할 때 기존 GitHub·Riido 연동을 사용한다. 분석·구현·검증은 일반 작업으로 진행한다. 사용자 지시와 기존 제출 범위를 우선한다.

## 적용 판단

| 요청/문맥 | 수행 범위 |
|---|---|
| 일반 설명·현황 조회·독립적인 분석/수정 | 필요한 일반 도구만 사용. 실행 등록·외부 쓰기·중앙 호출 없음 |
| “GM-75 진행해줘”, 연결된 업무의 “이 부분도 수정해줘” | 업무 연결을 유지하며 착수 → 작업 → 제출·검토·Riido 확인 |
| “지금 수정한 것들 제출하고 Riido에도 반영해줘” | 현재 결과를 업무에 연결하고 제출·검토·결과 반영 |
| “GitHub에만 PR 올려줘” | GitHub 제출과 원격 확인. Riido 등록과 중앙 검토는 추가하지 않음 |
| “이 PR 결과를 Riido에 반영해줘” | 기존 제출물을 중앙에 전달해 검토·반영. 불필요한 코드 변경/커밋 없음 |

업무 키·서비스 이름만으로 연동을 결정하지 않는다. “GM-75가 뭐야?”는 조회다. 이미 연동한 업무의 후속 요청은 사용자가 스킬을 다시 지정하지 않아도 이어간다. 명시적인 로컬만/분석만/커밋 금지/반영 보류 지시는 연동 범위보다 우선한다.

## 작업 위치와 도구

- 프로젝트 진입 안내 또는 기존 설정의 `preferredWorktree`로 실제 Git 폴더를 확인한다. 이 PC의 설정은 `C:\Implement\ScenarioEngine\.local\coordination\workflow-config.json`이다. 현재 Git 루트의 origin이 `GeonMyoung/ScenarioEngine`인지 확인하고 기존 환경·변경을 보존한다.
- GitHub 제출만이면 기존 Git/GitHub 도구로 수행한다. Riido까지 연결하면 실제 작업 폴더의 `doc/development-workflow.md`에서 현재 단계에 필요한 절만 읽고 기존 `tools/workflow.py`를 사용한다. 입력 필드가 필요할 때만 `doc/workflows/workflow-inputs.md`를 읽는다.
- Riido 대상은 설정의 workspace/team/project ID와 API 소속으로 확인한다. 작업 창은 조회를, 설정의 기존 중앙 검토 작업은 업무 등록·상태·결과 쓰기를 맡는다.

## 착수와 계속

최초 연동 시 해당 업무의 최신 본문·댓글·완료 조건을 읽고 `workflow.py status`로 관련 기존 실행을 확인한다. 맞는 업무가 없으면 중앙에 한 번 연결/등록을 요청하며 독립적으로 가능한 작업은 계속한다.

새로운 연동 업무에만 `start`를 등록하고 시작 이벤트를 전달한다. `working` 실행의 동일 목표·업무·요구사항에 대한 중간 지시와 수정은 기존 runId로 이어간다. 메시지나 대화가 추가됐다는 이유로 재등록·재전송하지 않는다. 시작 확인을 기다리느라 독립적인 구현을 멈추지 않는다.

제출 후 수정은 기존 도구의 상태 규칙을 따른다. 재제출을 허용하는 실행은 같은 runId를 사용하고, 종료된 실행이나 요구사항 변경은 과거 기록을 보존한 후 후속 실행으로 연결한다. 매번 새 runId를 만들거나 종료된 기록을 강제로 수정하지 않는다.

작업 중 외부 갱신은 범위·완료 조건 변경이나 실제 차단 사유가 생겼을 때만 한다. 같은 내용을 진행 댓글로 반복하지 않는다. 일반 작업 후 제출 시 처음 연동했다면 당시 Git 기준과 기존 변경을 기록하며 과거 착수를 소급해서 꾸미지 않는다.

## 제출과 결과

관련 변경·검증·남은 항목을 한 결과로 묶는다. 허용된 범위에서 commit/push/PR과 원격 확인을 수행한 뒤 `submit`한다. GitHub만/기존 결과 반영만 요청한 경우 위 적용 표의 범위를 유지한다. 단계별 체크포인트나 작은 수정마다 제출하지 않는다.

이벤트 전달은 기존 `handoff` 출력의 대상과 본문을 앱의 `send_message_to_thread`에 전달하고 성공 후 `dispatched`로 기록한다. 시작/제출 이벤트별 한 번을 기본으로 하며 같은 이벤트 재시도 전에 기존 처리 여부를 확인한다.

중앙은 제출된 실제 diff·근거·완료 조건을 확인한다. 작은 문서/국소 변경은 관련 부분을 확인하고, 표준 해석·판정 로직·공통 엔진 변경은 영향 경로와 근거를 깊게 검토한다. 이미 통과한 검증은 새 변경·실패·미해결 우려 없이 반복하지 않는다. Riido 결과 댓글과 상태를 저장한 뒤 재조회하고 기존 receipt 절차로 기록한다.

`wait_threads`의 커서로 중앙 결과를 확인한다. 완료·보완·실제 외부 장애를 구분하고, 사용자에게 중앙 재요청을 떠넘기지 않는다. 전송/저장 결과가 불명확하면 한 번 재조회하여 같은 이벤트로 재시도한다. 같은 오류가 계속되면 반영 대기를 남기고 무한 재시도·감시 설치 없이 가능한 일반 작업을 계속한다. 검토 수용과 실제 Riido 완료 동기화를 별도로 보고한다.

## 전환 중 기존 기록

GM-85 구축과 GM-86 제출 등 기존 실행·검토 이력은 보존한다. 새 적용 기준 때문에 완료된 업무를 다시 열거나 기존 제출을 새 실행으로 복제하지 않는다. 기존 설정·인증·중복 방지·SHA 검증·복구 도구를 재사용하며 새로운 상시 실행이나 worktree를 만들지 않는다.

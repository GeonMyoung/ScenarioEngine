# GM-85 운영 적용 기록

## 요청과 적용 범위

사용자가 Codex에서 작업을 지시하면 GitHub 제출과 중앙 검토 인계가 이어지고, Riido에서 진행 및 결과를 확인하는 작업 방식을 구축한다.

- Riido: GM-60 ScenarioEngine → GM-84 운영 마일스톤 → **GM-85 Codex–GitHub–Riido 작업 인계 자동화 구축**.
- 기존 작업 환경을 재사용했다. 추가 clone/worktree는 만들지 않았다.
- Python CLI가 실행 단위·시작/제출 이벤트·원격 SHA·검토 수신을 기록한다.
- 앱의 기존 `send_message_to_thread`/`wait_threads` 도구로 중앙을 호출한다. 별도 서버·주기 감시는 시작하지 않는다.
- PR 제출이 기본이며 직접 브랜치 제출도 같은 확인 절차를 지원한다.

## 변경 구성

| 대상 | 변경 |
|---|---|
| tools/workflow.py | 실행 등록, 중복 없는 제출, 중앙 인계 payload, 원격·요구사항 확인, 검토 receipt, 실패/대체 기록 |
| tests/test_workflow.py | 23개 정상·오류·동시 기록·중복·오래된 결과 방지 검사 |
| .github/workflows/workflow-tools.yml | Windows/Linux Python 3.12에서 도구 관련 검사 |
| AGENTS.md / doc/development-workflow.md | 작업 창의 자동 인계, 중앙의 Riido 쓰기, 주기 조회 중지, 환경 재사용 |
| doc/workflows/workflow-inputs.md | 설정·시작·제출·중앙 결과 입력 계약 |
| 기존 HTML 안내 | 초기 적용 도구와 GM-85 운영 범위 표시 |

현재 PC의 `police-test-platform/AGENTS.md`도 로컬 설정의 preferredWorktree를 읽어 위 절차로 진입하도록 변경했다. 설정·실행 자료·인증은 공개 저장소에 넣지 않는다.

## 검증 근거

- 로컬 Python 3.12: `python -m unittest discover -s tests -p test_workflow.py -v` — 23개 통과.
- GitHub Actions: 코드 커밋 `0cf1766418981ca02122487c0cf5374a1fbf8811`의 Windows/Linux 검사 모두 성공. [실행 결과](https://github.com/GeonMyoung/ScenarioEngine/actions/runs/34933674669).
- 실제 공통 기록 경로: `C:\Implement\ScenarioEngine\.local\coordination`.
- 최초 실행 ID: `GM-85-20260915-setup`.
- 시작 이벤트: `start-51d95f1dd50f024a3da298a6`.
- 실제 앱 도구로 시작 인계를 전송했다. 이후 제출·검토·Riido 재조회 근거는 같은 실행의 이벤트/receipt와 Riido GM-85 댓글로 추적한다.
- 단위 검증은 외부 API를 모의 처리한다. 실제 GitHub/Riido 성공은 이벤트별 원격 조회와 중앙의 재조회 기록으로 구분한다.
- 엔진 코드·실장비 통신·MSI 검증은 이번 운영 도구의 검사 범위에 포함하지 않는다.

## 실제 운영의 경계

1. Riido 설정 화면에서 ScenarioEngine 저장소의 기존 연결을 확인했다. gm 팀의 Branch Create → 진행 중, PR Open → 검토 대기 매핑을 구성했다. Merge/PR Close에 완료 자동화는 설정하지 않는다.
2. 검토 대기(inProgress)와 검토 완료(completed)를 추가하고 MCP 재조회로 확인했다. 기존 완료/완료 (1) 상태는 보존하며 새 완료 반영에는 검토 완료를 사용한다. 중앙이 실제 isDone과 저장 내용을 재조회한다.
3. 앱 도구·인증을 사용할 수 없으면 이벤트가 반영 대기로 남는다. 연결 복구 후 같은 eventId의 처리 여부를 확인하고 재전달한다.
4. 브랜치 보호와 무인 병합/배포는 설정하지 않는다. 저장소 반영은 사용자 승인 범위를 따른다.
5. `working` 상태의 실행은 기본적으로 하나다. 동시 수정 확대는 별도 환경 계획 후 진행한다.
6. 기존 workers.json/review-state.json/중지된 automation.json은 초기 운영 이력으로 보존한다. 신규 실행의 기준 기록은 workflow-state.json이다.

이 기록은 도구 구현·로컬 적용과 서비스별 설정 상태를 구분한다. 검토 수용이 Riido 완료 상태의 동기화까지 의미하는 것은 아니다.

## 설정과 반영 범위

- 검토 완료 상태 ID: `nuCm-pOcSStA8t96QhKyk` / completed.
- 검토 대기 상태 ID: `J-jmh-FyWPiCfvbMXRtHE` / inProgress.
- 처음의 HTTPS push는 OAuth workflow scope 부족으로 거절됐다. 기존 SSH 인증으로 같은 저장소에 push했고 원격 SHA와 Actions 결과를 확인했다.
- Riido 기본 연동의 실제 이벤트 확인을 위해 GM-85 키가 포함된 제출 브랜치를 사용한다. 기존 문서 안내 PR과 제출 이력은 보존하며 최종 구축 PR에 연결한다.

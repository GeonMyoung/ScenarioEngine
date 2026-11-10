# 자동 검증과 선택 기록 대조

현재 기준은 **REST-AUTO-001**이다. REST 6개 시나리오는 엔진이 직접 관측한 송수신·규격 검사로 판정하며 정상 완료는 SUCCESS다. 대상 내부 동작의 미관측 범위를 기록하고 별도 자료 제출을 요구하지 않는다. COMPLETE는 사용하지 않는다.

대상 기록 자동 대조는 선택 기능이다. 폴더를 지정하면 REST-REVIEW-003으로 같은 실행의 기록을 추가 대조하고 결과와 근거를 플랫폼에 전달한다. 기본 자동 결과는 별도로 보존한다.

## 시험 설정

| 입력 | 사용법 |
|---|---|
| 대상 증적 폴더 / `evidence_directory` | 엔진 실행 PC에서 읽을 수 있는 절대 경로. 현재 독립 대상 프로그램의 증적 출력 폴더를 지정한다. 실행 전에 폴더가 생기지 않아도 설정 가능 |
| 증적 준비 대기시간 / `evidence_wait_s` | 송수신 완료 후 기록을 기다리는 시간. 기본 30초, 1~600초 |

재시험에는 새 대상 증적 폴더를 사용한다. 다른 실행의 runId가 들어 있는 폴더는 재사용해서 통과시키지 않는다. 폴더 미지정 또는 기록 미준비 상태는 검토가 완료된 것으로 표시하지 않는다.

현재 연결 형식은 `restconformance/emulator/rest_method_sut.py`가 생성하는 파일이다. 제공측은 준비자료·조회·응답, 요청측은 접속 설정·요청·응답·처리 기록을 포함한다. 다른 대상의 로그는 이와 동등한 증거를 입력 형식에 맞게 연결해야 한다. 표준이 특정 파일명이나 JSONL 형식을 요구한다는 뜻은 아니다.

## 실행 준비

기본 `Start-PlatformEngine.ps1` 실행에는 Python 검토 도구가 필요하지 않다. 선택 자동 대조를 사용할 때는 `-PrepareEvidenceReview`를 지정하거나 다음 명령으로 런타임을 준비한다. 검토 코드가 갱신됐을 때도 다시 준비한다.

```powershell
.\restconformance\tools\Prepare-ReviewRuntime.ps1 -Executable .\scenarioengine\project\vs2022\DebugTest64\ScenarioEngineTest.exe
```

이 명령은 Python 3.10 이상을 확인하고, 실행 파일 옆 `rest-review/`에 검토 모듈 4개와 `rest-review-runtime.json`을 준비한다. `-PythonExecutable`로 별도 로컬 Python 실행 파일을 지정할 수 있다. Python을 설치하거나 시스템 PATH를 변경하지 않는다. 배포 패키지에 Python과 검토 모듈을 포함하는 작업은 별도다.

대상 프로그램은 기존 `Start-RestMethodSut.ps1`을 사용하고, `-OutputDirectory`를 시험 설정의 증적 폴더와 맞춘다. 제공측 대상은 시험 시작 전에 실행하고, 요청측 대상은 시험기 수신 준비 후 실행한다.

## 결과와 알림

| 상황 | 증적 검토 상태 | 전체 최종 결과 |
|---|---|---|
| 같은 실행의 준비·송수신·처리 증거 모두 충족 | PASS | SUCCESS |
| 같은 실행에서 자료·처리·오류항목 등 증거 불일치 | FAIL | 전체 FAIL. 개별 자동 관측 결과는 보존 |
| 기록 미준비·다른 실행·준비시간 초과 | NOT_CONFIRMED | 기존 자동 판정 유지, 추가 대조 미확인 명시 |
| 검토 런타임 미준비·실행 오류·결과 연결 오류 | UNAVAILABLE | 기존 자동 판정 유지, 추가 대조 미확인 명시 |
| 검토 도중 시험 중지 | STOPPED | STOPPED |
| 송수신 자체가 실패·중지 | SKIPPED | 원래 실패·중지 유지. NOT_RUN 항목도 보존 |

폴더가 없으면 NOT_REQUESTED로 기록하고 엔진의 자동 판정으로 종료한다. 성공의 범위는 엔진이 관측한 항목이며 대상 내부 처리까지 확인한 것으로 해석하지 않는다.

각 실행 폴더에 다음 자료를 남긴다.

- `result.json`, `events.jsonl`: 기존 자동 관측 결과. 덮어쓰지 않는다.
- `sut-evidence-snapshot/`: 같은 실행의 대상 증적 복사본. 두 차례 내용이 안정된 것을 확인한 뒤 복사한다.
- `review-worker-result.json`: 검토 도구가 만든 결과.
- `review-link.json`: 엔진이 실행 ID·case·원본 결과 해시·항목·횟수·판정을 확인한 최종 연결 결과.
- `review-worker.log`, 필요 시 `review-diagnostic.txt`: 로컬 운영 진단. 내부 명령·오류 코드를 사용자 안내로 그대로 전달하지 않는다.

사용자 화면에는 자동 관측 판정·범위·미관측 내용·선택 대조 결과·근거를 NOTIFY/info의 JSON으로 전달한다. 각 실행 항목은 START와 최종 결과를 한 번씩 보내며, 모든 자료를 보낸 뒤 MainScenario FINISH를 한 번 보낸다. 기본 송수신 메시지 표시도 유지한다.

[현재 상태·플랫폼 검증 결과](../doc/gyeong4/2026-v2.1/rest-auto-state-20260924.md) · [이전 연결 구현 이력](../doc/gyeong4/2026-v2.1/rest-review-integration-verification-20260924.md)

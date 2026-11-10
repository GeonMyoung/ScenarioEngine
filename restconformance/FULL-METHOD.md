# REST 시험방법 요구사항·추가 검증 실행 안내

2026-09-24 현재 기준: **REST-AUTO-001**. 기본 실행은 엔진이 직접 관측한 송수신·규격 검사로 판정하며 사후 자료 제출을 요구하지 않는다. COMPLETE를 보내지 않고 정상 완료는 SUCCESS로 종료한다. 대상 내부 동작의 미관측 범위는 기록하고 기존 기록 대조는 선택 기능으로 유지한다. [현재 판정·검증](../doc/gyeong4/2026-v2.1/rest-auto-state-20260924.md). 아래 증적 대기·필수 자료 요구·서버 COMPLETE 지원 설명은 이전 단계 이력이다.

엔진 연결 완료: 대상 증적 폴더를 지정하면 송수신 후 자동 검토하고 최종 판정·근거를 플랫폼으로 전달한다. 원본 자동 결과는 보존한다. [설정·결과 안내](REVIEW-INTEGRATION.md).

증적 검토는 **REST-REVIEW-003**을 적용한다. 숫자/boolean과 소수 정밀도를 구분하고 항목별 요청·응답·반복수·시작/종료 기록을 대조한다. [검증 결과](../doc/gyeong4/2026-v2.1/rest-evidence-correlation-verification-20260924.md). 검토 도구는 현재 별도 실행 방식이다.

현재 방법 기준은 **REST-EVIDENCE-002**다. 플랫폼 51·57·58·59·60·61의 기존 case를 유지하며, 각 시나리오의 선택 항목을 7개로 보완했다. 과거 보고서는 당시 기준으로 보존한다.

## 기준과 분류

제4부 제4장 1.1.1·1.2.1에서 요구하는 관측과 증거를 [조항 대응표](../doc/test_items_analysis.md)에 연결했다. 원문은 정보요청·정보제공 기능시험을 정의하며, 아래 선택 항목은 해당 요구를 확인하도록 나눈 구현이다.

| 대상 | 시험방법 요구사항 확인 | 추가 검증 |
|---|---|---|
| 정보제공 서버 — 57·59·60 | 정상 제공, 잘못된 요청 오류응답, 자료 부재 오류응답 | 인증 누락·불일치, 없는 경로, 빈 정상응답 |
| 정보요청 클라이언트 — 51·58·61 | 정상 요청·수신·처리, 자료 부재 오류응답 수신·처리 | 일반 400·404·500 주입, 빈 정상응답, 손상 정상응답 |

전체는 6개 시나리오·42개 선택 항목이며, 표준 요구 확인 15개와 추가 검증 27개를 구분한다. 반복 10회를 10개의 독립 시험으로 세지 않는다.

정상 payload는 해당 정보군에 채택한 검사 기준을 유지한다. 스마트교차로는 제3부 표 4-23을 우선한다. VDS의 명시된 400/500 오류 JSON 구조는 해당 조건에서 검사한다. 자료형·길이 등 미해소된 데이터 규격 대응을 이번 방법 증거 보완으로 완료 처리하지 않는다.

## 자료 부재 오류와 빈 정상응답

- **표준 요구 확인:** `test_no_data_error` / `test_no_data_error_response`. 유효한 API와 정상 경로·인증 조건에서 자료가 없을 때 오류 코드 또는 에러 메시지를 반환·처리하는지 확인한다.
- **추가 검증:** `test_no_data` / `test_empty_response`. 200 빈 배열/XML result 또는 204 같은 빈 정상응답 처리다. 위 오류응답 요구를 대체하지 않는다.
- 자료 부재 오류의 기본 HTTP 코드는 404다. 400/410/422도 명시적으로 선택할 수 있으며, 이 숫자는 시험 profile이다. 표준이 특정 HTTP 상태 코드를 고정한 것은 아니다. 200 본문에 업무 오류를 담는 계약은 오류 식별 규칙을 확보해 별도 profile로 검증한다.
- 정상 제공, 자료 부재 오류, 빈 정상응답은 서로 다른 준비 조건이다. 제공측에서 동시에 선택하지 않는다. 기존 `no_data_status=404`를 추가 빈 정상응답에 쓰지 말고 새 오류응답 항목을 선택한다.
- 자료 부재 확인란은 준비 선언이다. 없는 경로의 404나 선언만으로 자료 부재 증거를 충족시키지 않는다.

## 정보제공 대상 실행

1. 정상 자료가 준비된 대상에서 정상 제공·잘못된 요청 오류응답을 선택하고 각 10회 실행한다. 대상 준비자료와 실제 응답 항목값을 대조한다.
2. 같은 API의 자료를 0건으로 준비한 별도 회차에서 자료 부재 오류응답을 선택하고 준비 확인란을 체크한다. 오류 코드를 확인한 뒤 대상의 준비·조회 기록을 독립 대조한다.
3. 인증 오류·없는 경로·빈 정상응답은 필요한 경우 추가 검증으로 선택한다.

```powershell
# 정상 자료를 제공하는 상대역
restconformance/emulator/Start-RestMethodSut.ps1 -Scenario SC11-SMT
# 자료가 없어서 오류를 반환하는 상대역 — 별도 회차
restconformance/emulator/Start-RestMethodSut.ps1 -Scenario SC11-SMT -DataState absent
# 빈 정상응답 추가 검증 — 별도 회차
restconformance/emulator/Start-RestMethodSut.ps1 -Scenario SC11-SMT -DataState empty
```

VDS는 SC11, UTIC는 SC28이다. 구성값을 바꾸면 `-Config`로 시험기와 일치시키며 인증값은 환경변수로 전달한다. 실제 운영 API나 장비는 현재 에뮬레이터 검증과 구분한다.

## 정보요청 대상 실행

시험기를 먼저 수신 대기시킨 뒤 대상의 요청을 실행한다. 정상·자료 부재 오류 처리 두 항목이면 20회다.

```powershell
restconformance/emulator/Start-RestMethodSut.ps1 -Scenario SC32-SMT -Requests 20
```

VDS는 SC32, UTIC는 SC07이다. `-Requests`를 생략하면 설정 파일에서 선택된 항목 수와 반복 횟수로 계산한다. 대상은 실제 HTTP 상태와 본문을 처리하며 시험기 판정 파일이나 항목명을 읽어 성공을 맞추지 않는다.

## 증거와 판정

시험기는 실제 관측 결과와 독립 증거 검토를 구분한다. 자료 부재 제공측은 준비 상태 확인 전 EVIDENCE_PENDING, 요청측은 수신·처리 대조 전 EVIDENCE_PENDING을 유지한다. 자동 SUCCESS인 경우도 전체 표준 증거 검토를 완료했다는 뜻으로 확대하지 않는다.

- 제공측: `preparation.json`, `source-data.body`, 유효 경로의 `data_lookup`, 요청·응답 원문을 연결한다.
- 요청측: 저장한 URL·단일 요청 설정, `request_sent`, `response_received`, `application_processed`와 처리 자료를 대조한다. 미처리 정보에는 오류항목·상태·원인 로그가 있어야 한다.
- 시험기: `result.json` schema 3, 근거·분류, `precondition`, `prepared-*.body`, 교환별 원문·해시를 남긴다.
- 모든 송신·수신은 회차별 JSON 첨부와 `test-data-*.jsonl`로 남긴다. 긴 자료는 생략 없이 분할한다.

```powershell
python -X utf8 restconformance/tools/review_method_evidence.py --report <result.json> --sut <상대증적폴더> --output <새검토결과.json>
```

검토 결과의 `standardCriteria`는 근거별 증거 확인 결과, `standardCoverage`는 확인한 요구와 미선택 요구를 구분한다. 추가 항목만 실행해서 표준 전체 완료가 되지 않는다. 파일명·이벤트 형식은 시험 지원 구현이며 표준이 특정 파일이나 DB 저장을 의무화한 것은 아니다.

완료 이벤트 FINISH는 전체 MainScenario에서 한 번만 보낸다. 증거 대기 항목의 원본 판정을 성공으로 바꾸지 않으며, 웹에서 증거 검토 결과를 최종 판정으로 반영하는 기능은 별도 서버 범위다.

[검증 결과](../doc/gyeong4/2026-v2.1/rest-evidence-method-verification-20260924.md). 기존 정상 전용 CLI 경로는 과거 회귀 확인용으로 보존한다. 실제 플랫폼은 `--method-case <case>`와 같은 새 방법 경로를 사용한다.

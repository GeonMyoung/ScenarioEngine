# 경4 REST 정보연계 시험

**최신 상세시험 안내 — 2026-09-26 v4:** 현재 12개 시나리오·82개 상세항목을 유지하며 협의한 항목만 선택합니다. 실제 오류 입력·인증 방식·기대 HTTP/업무 응답과 기준의 출처를 표시하고, 시험명과 결과 설명을 자동 관측 범위에 맞췄습니다. 긴 경로의 결과 저장 실패도 폴더명 단축으로 보완했습니다. [구현·검증 기록](../doc/gyeong4/2026-v2.1/rest-case-information-verification-20260926.md). 아래 이전 수량·검증은 당시 이력입니다.

2026-09-25 기상정보 추가: SC09·SC30을 **66·67**에 등록하고 전체 14항목의 플랫폼 검증을 완료했다. 현재 REST는 **12개 시나리오·82개 선택 항목**이다. [사용·계약 안내](WEATHER.md) · [검증](../doc/gyeong4/2026-v2.1/weather-verification-20260925.md). 아래 이전 수량은 당시 범위의 기록이다.

2026-09-24 음영구간 정보 추가: SC10·SC31을 **64·65**에 등록하고 전체 12항목의 플랫폼 검증을 완료했다. 현재 REST는 **10개 시나리오·68개 선택 항목**이다. [사용·계약 안내](SHADOW.md) · [검증 결과](../doc/gyeong4/2026-v2.1/shadow-verification-20260924.md). 아래 이전 수량은 당시 범위의 기록이다.

2026-09-24 NTIC 추가: SC08 요청·SC29 제공을 **62·63**에 등록하고 전체 14항목의 플랫폼 검증을 완료했다. 현재 REST는 **8개 시나리오·56개 선택 항목**이다. [NTIC 사용·계약 차이](NTIC.md) · [검증](../doc/gyeong4/2026-v2.1/ntic-verification-20260924.md). 기존 6개 완료 기록은 당시 범위로 보존한다.

2026-09-24 최종 플랫폼 확인: 현재 6개 시나리오의 **42개 항목·420회 교환·840개 송수신 메시지·12개 저장 보고서**를 같은 최종 실행본으로 전부 대조했다. [6개 완료 근거](../doc/gyeong4/2026-v2.1/rest-six-final-verification-20260924.md).

2026-09-24 현재 기준: **REST-AUTO-001**. 기본 실행은 엔진이 직접 관측한 송수신·규격 검사로 판정하며 사후 자료 제출을 요구하지 않는다. COMPLETE를 보내지 않고 정상 완료는 SUCCESS로 종료한다. 대상 내부 동작의 미관측 범위는 기록하고 기존 기록 대조는 선택 기능으로 유지한다. [현재 판정·검증](../doc/gyeong4/2026-v2.1/rest-auto-state-20260924.md). 아래 증적 대기·필수 자료 요구·서버 COMPLETE 지원 설명은 이전 단계 이력이다.

2026-09-24 최신 상태: **엔진의 대상 증적 자동 검토와 플랫폼 결과 연결까지 완료**했다. [사용 방법](REVIEW-INTEGRATION.md) · [로컬 42항목/플랫폼 5항목 검증](../doc/gyeong4/2026-v2.1/rest-review-integration-verification-20260924.md). 아래의 검토 도구 별도 실행·엔진 연결 미완료 표기는 이전 단계의 이력이다.

2026-09-24 최신 증적 검토: **REST-REVIEW-003**에서 정확한 소수·자료형 비교와 시험 항목별 교환 연결을 보완했다. 기존 42개 항목의 기록 재검토와 오류 조건 검증을 완료했다. [결과](../doc/gyeong4/2026-v2.1/rest-evidence-correlation-verification-20260924.md). 증적 검토의 엔진 실행 연결과 웹 반영은 별도다.

2026-09-24 최신 데이터 검사: UTIC·VDS 양측에 **REST-DATA-003**을 적용했다. 날짜·문자열 길이·숫자 정밀도 및 선택 필드의 제공 시 제약을 검사한다. 로컬 검증·엔진 빌드 완료, 새 빌드의 플랫폼 재실행은 미수행이다. 현재 전체 구성은 6개 시나리오·42개 선택 항목이며 아래의 36/24개 및 이전 검사 설명은 당시 이력이다. [보완 결과](../doc/gyeong4/2026-v2.1/rest-standard-fields-verification-20260924.md).

**최신 시험방법 기준 REST-EVIDENCE-002:** 6개 시나리오의 42개 항목을 **표준 요구 확인 15개 + 추가 검증 27개**로 분리했다. 자료 부재는 같은 유효 API의 실제 자료 0건·조회·오류응답 증거를 대조하며, 빈 정상응답은 추가 시험이다. 대상 요청·수신·처리 및 오류항목 로그까지 검토한다. [실행 안내](FULL-METHOD.md) · [증적 보완 검증](../doc/gyeong4/2026-v2.1/rest-evidence-method-verification-20260924.md). 아래 36개/24개 등 수치는 앞선 구현 이력이다.

**현재 구현·등록: 6개 시나리오·36개 선택 항목.** UTIC·VDS 4개(51·57·58·59, REST-PROFILE-001)에 표준 우선 스마트교차로 양측 2개(60·61, SMART-STANDARD-001)를 추가했다. 스마트교차로 데이터·판정은 제3부 표 4-23을 적용한다. [스마트교차로 안내](SMART.md), [12항목 플랫폼 검증](../doc/gyeong4/2026-v2.1/smart-platform-verification-20260924.md).

**사용자 로그 개선(2026-09-24):** 시험 목적·역할·연계정보·검증 기준·실제 응답·판정 근거와 대상 처리 증적 안내를 진행/결과 로그에 표시한다. 내부 실행ID·결과 파일 경로·수신 대기 표식은 사용자 안내에서 제거했다. [개선 및 실제 화면 검증](../doc/gyeong4/2026-v2.1/rest-user-log-verification-20260924.md)을 따른다. 과거 보고서는 보존하고 새 실행에 적용한다.

**기존 UTIC·VDS 기준: REST-PROFILE-001 전체 시험방법 보완 완료.** 기존 플랫폼 **51·57·58·59**에서 각각6개 항목(정상·오류 요청/응답·자료 부재 등)을 선택할 수 있다. 명세가 명확하면 명세를 따르고, 미정 오류 응답은 prj22를 참고한 개발 기준으로 판정한다. **24항목·240회 플랫폼 교환**, 자동 성공12와 대상 처리 증거 검토12를 확인했다.

[전체 방법 실행 안내](FULL-METHOD.md) · [2026-09-24 검증 결과](../doc/gyeong4/2026-v2.1/rest-full-method-verification-20260924.md). 최신 독립 상대역은 `emulator/Start-RestMethodSut.ps1`을 사용한다. 기존 정상 전용 CLI·에뮬레이터·결과는 회귀 및 이력 자료로 유지한다.

## 시험 데이터 표시 보완 — 2026-09-24

**최신 기준: 모든 회차의 송신·수신 메시지를 개별 표시한다.** 같은 내용도 묶지 않으며 긴 자료는 생략 없이 분할한다. 정상 10회는 요청 10개·응답 10개의 JSON 첨부와 요약으로 표시된다. 로컬 480개 메시지, 플랫폼 네 역할 80개 메시지, 보고서 158·160의 각 20개 메시지를 확인했다. [매 회차 표시 적용·검증 결과](../doc/gyeong4/2026-v2.1/rest-all-messages-display-20260924.md)를 따른다. 아래 회차 묶음 설명은 초기 구현 이력이다.

REST 각 항목의 요청 조건·실제 응답 코드·본문을 `NOTIFY info`의 **JSON** 첨부와 `test-data-*.json/.txt`에 남긴다. 인증값 가림, 반복 회차 묶음, 큰 본문 생략 안내, 실패·미실행 구분을 포함한다. 최종 로컬 24항목·240회, 경계 4건, 플랫폼 VDS·UTIC 10항목·100회를 검증했다.

**운영 보고서 미표시 해결:** 기존 시나리오 비교 결과 운영 보고서는 TEXT가 아닌 JSON 첨부를 표시했다. 형식을 맞춘 뒤 보고서 153·154의 10개 데이터 칸 모두 표시됨을 확인했다. [비교 및 최종 확인 결과](../doc/gyeong4/2026-v2.1/rest-test-data-legacy-comparison-20260924.md)를 따른다. 초기 TEXT 조사 자료는 이력으로 유지한다.

## 초기 정상 전용 구현 안내 — 이력

2026-09-24 추가: **SC28 UTIC 돌발정보 제공시험**을 [59](https://106.250.189.37:8443/test/scenario/59), `centerClient2utic_v1`로 구현·등록·검증했다. 시험기는 UT 센터 HTTP 클라이언트 역할이다. [UTIC 제공시험 안내](UTIC-PROVIDER.md)를 따른다. SC07/SC28 UTIC와 SC11/SC32 VDS의 정상 시험을 양쪽 역할에 구현했다.

2026-09-24 추가: **SC32 미시교통정보 플랫폼 VDS 요청시험**을 [58](https://106.250.189.37:8443/test/scenario/58), `centerServer2micro_v1`로 구현·등록·검증했다. 시험기는 UT 센터 HTTP 서버 역할을 수행한다. [반대 역할 실행 안내](VDS-REQUEST.md)를 따른다. VDS 정상 시험은 SC11/SC32 양측에 구현됐고, 아래 기존 설명은 SC07 중심이다.

현재 구현 범위는 **SC07/SC28 UTIC 돌발정보 요청·제공시험**, **SC11/SC32 VDS 원시정보 이력 제공·요청시험**이다. category는 `ITSK-00143-REST-V1`이다. 플랫폼 등록은 각각 **51/59, 57/58**이며 case·역할은 `registration/manifest.json`에 기록한다. VDS 제공 측은 [VDS 안내](VDS.md), 요청 측은 [반대 역할 안내](VDS-REQUEST.md)를 따른다. 아래 기존 설명은 SC07 기준이다.

시험기는 UTIC 역할의 HTTP Server, 시험 대상은 정보를 요청하는 UT 센터 HTTP Client다. `GET /guide/imsOpenData.do?key=…` 요청을 확인하고 UTF-8 XML을 제공한다. 시험기가 운영 UTIC를 호출하는 시험과 구분한다.

## 구조와 prj22 참고

- `GitsnOpenApiHttpAdapter`: prj22의 HTTP 서버·파서·전송 완료 이벤트를 재사용한 별도 라이브러리.
- `HttpAdapter`: callback 자료를 작업 큐로 넘기고 요청·응답·중지를 관리한다.
- `RestCore` / `UticXml`: UTIC 요청 조건, XML 필드 대응, 반복수와 증적 기록.
- `RestConformance`: 기존 SDK의 UI_CONFIGURE / SETUP / START / STOP / NOTIFY에 연결한다.
- `emulator/ut_center_utic.py`: 독립 Python HTTP Client SUT. 수신 XML 원문과 해석·처리 결과를 보관한다.
- `tools/review_utic_evidence.py`: 시험기의 요청/전송 기록과 SUT의 수신/처리 기록을 runId·교환 번호·SHA-256으로 대조한다.

[참고·재사용 범위](reuse-reference.json)에 원본과 적용 경계를 남겼다. 기존 DATEX 모듈이나 legacy case를 변경하지 않았고 REST 자체 설정을 사용한다.

## 실행

Visual Studio 2022 C++ 도구와 저장소 SDK를 사용한다. 엔진 빌드는 저장소의 `tools/bootstrap-build.ps1 -Target Engine -Configuration Debug`로 수행한다. 독립 시험기는 `project/vs2022/UticConformanceCli.vcxproj`를 Debug|x64로 빌드한다.

1. 플랫폼 ID 51에서 ‘자체 시험 수행’을 연다.
2. 해당 회차의 Agent 접속 URL로 `tools/Start-PlatformEngine.ps1 -AgentUrl "wss://…"`을 실행한다.
3. `registration/uticServer2center_v1.example.json`의 입력을 적용하고 시험을 시작한다. 기본 수신 주소는 127.0.0.1:55307이다.
4. Python 3이 준비된 PC에서 아래 SUT를 실행한다. 먼저 시험기가 수신 대기 상태인지 확인한다.

```powershell
.\restconformance\emulator\Start-UticSut.ps1
```

기본 합성 시험용 키를 사용하며 실제 UTIC 운영 키나 운영 API 접속은 필요하지 않다. 실제 장비 검증 단계에서는 해당 SUT와 시험기 설정을 맞춘다. 인증키 자체의 발급·운영 IP 승인 정책을 이 시험으로 검증한 것은 아니다.

## 입력과 결과

- **반복수 기본 10회:** 제4부 제4장 1.1.1의 단일 정보교환 반복 기준. 더 작은 값으로 실행하면 결과의 최소 반복 조건을 충족한 것으로 표시하지 않는다.
- **회당 대기시간 기본 30초:** 시험 환경값이며 표준에서 정한 응답 성능 한계가 아니다.
- **응답 XML 파일:** 선택 입력. 미입력 시 모든 필수 항목을 포함한 합성 시험 자료를 사용한다. 입력 자료는 실행 전 XML 구문·필수 필드·길이·명시 코드·숫자·일시를 확인한다.
- **자료 대응:** 공식 UTIC의 `<result><record>`와 `incidenteTypeCd` 등 태그를 보존하고 제3부 표 4-16과 연결한다. 일시는 공식 예시의 한글 형식과 표준 예시의 14자리 형식을 지원한다. 확인되지 않은 규격 차이는 정정 완료로 처리하지 않는다.
- **오류:** 잘못된 method/path/key·중복 key·예상 밖의 GET body는 요청 검사 실패다. 그때의 HTTP 400은 시험기의 진단 응답으로, 운영 UTIC의 고유 오류 계약을 주장하지 않는다.
- **중지:** 요청·전송 대기 중 중지하고 소켓·작업을 정리한다. 재실행은 SETUP부터 수행한다.

실행 폴더 `rest-results/<runId>/`에 `response.xml`, `events.jsonl`, `result.json`을 남긴다. 본 모듈의 HTTP 이벤트에는 요청 key 값을 쓰지 않는다.

10회 정상 요청·XML 전송 후 자동 결과는 **EVIDENCE_PENDING**이다. SUT가 실제로 수신·해석·처리했는지 별도 증거가 필요하기 때문이다. UI에서는 통신 종료를 표시하고 자동 SUCCESS로 바꾸지 않는다.

```powershell
python -X utf8 .\restconformance\tools\review_utic_evidence.py --report <result.json> --sut <SUT결과폴더> --output <새검토결과.json>
```

검토 도구는 실패·중지 결과, 부족한 횟수, 누락/중복 처리, 원문·실행 ID 불일치를 통과시키지 않는다. 원본 자동 결과를 덮어쓰지 않는다. 5분 업무 수집 주기 전체나 실제 서비스에서의 데이터 정확성을 단일요청 반복 시험의 성공으로 대체하지 않는다.

## 검증

`tests/verify_utic.py --exe <UticConformanceCli.exe> --output <새결과폴더>`로 정상·인코딩된 키·요청 오류·미완료·XML 오류·처리 증거 누락·중지·포트 재사용을 확인한다. 결과 파일을 덮어쓰지 않는다.

[2026-09-23 UTIC 플랫폼 검증 결과](../doc/gyeong4/2026-v2.1/utic-platform-verification-20260923.md)와 [2026-09-24 VDS 플랫폼 검증 결과](../doc/gyeong4/2026-v2.1/vds-platform-verification-20260924.md)를 따른다. VDS 정상 제공시험은 구현·플랫폼 검증 및 저장 보고서 조회를 완료했다. SC11의 스마트교차로·오류 요청 계약·표준 필드 세부 제약 대응은 남아 있다.

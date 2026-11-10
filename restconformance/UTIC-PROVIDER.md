# SC28 — UTIC 돌발정보 제공시험

2026-09-24 후속 보완: 현재 시험방법은 REST-EVIDENCE-002, 데이터 검사는 **REST-DATA-003**이다. 아래 최초 구현 당시 남겨둔 날짜·길이·숫자 정밀도 검사를 양측 역할에 보완했다. [현재 검사·검증 범위](../doc/gyeong4/2026-v2.1/rest-standard-fields-verification-20260924.md)를 우선 적용하며 이전 실행 결과는 이력으로 보존한다.

플랫폼 [59](https://106.250.189.37:8443/test/scenario/59), category `ITSK-00143-REST-V1`, case `centerClient2utic_v1`, 선택 항목 `test_provide_utic`.

| 구성 | 시험 시스템 | 시험 대상 | 데이터 방향 |
|---|---|---|---|
| SC07 / #51 UT 센터 요청시험 | UTIC HTTP 서버 | UT 센터 HTTP 클라이언트 | UTIC → UT 센터 |
| SC28 / #59 UTIC 제공시험 | UT 센터 HTTP 클라이언트 | UTIC HTTP 서버 | UTIC → UT 센터 |

SC28의 독립 서버 에뮬레이터는 `emulator/utic_provider.py`다. SC07의 클라이언트 에뮬레이터 `ut_center_utic.py`도 유지한다. 운영 UTIC에 접속하지 않고 에뮬레이터를 SUT로 사용하는 현재 개발 기준을 따른다.

## 적용 계약

- `GET /guide/imsOpenData.do?key=…`, 요청 본문 없음. key를 URL 인코딩해 `+`, `&`, `=`, `%`, 한글 등이 요청변수 경계를 바꾸지 않도록 한다.
- 요청 `Accept: application/xml`. 정상 응답 HTTP 200, XML Content-Type(`application/xml` 또는 `text/xml`)과 UTF-8 본문을 검사한다.
- 기존 SC07의 `UticXml` 검사기를 재사용한다. `<result><record>…</record></result>`, 공식 필드 철자 `incidenteTypeCd`/`incidenteSubTypeCd`, 필수 필드·길이·코드·숫자·일시 규칙을 동일하게 적용한다.
- 제4부 정보제공 기능시험의 최소 10회 정상 교환을 적용한다. 수신 원문·응답 코드·필드 검사 결과를 매회 남긴다.
- XML 문법상 정상이나 record가 없는 응답은 EVIDENCE_PENDING이다. 정상 돌발정보 제공까지 확인한 것으로 처리하지 않는다. 기존 SC07 시험 자료의 빈 record 금지 기본 동작은 유지한다.
- DTD·중복 필드·예상 밖 구조·네임스페이스·손상 UTF-8 등을 거부한다. 크기 한도 1 MiB·record 한도 1,000건은 현재 시험 도구의 한도다.

적용 기준은 앞선 SC07의 표준/API 필드 대응이다. 이를 공식 표준과 서비스 간 모든 차이가 해소됐다는 의미로 확대하지 않는다. 잘못된 요청 또는 데이터 부재에 대한 운영 UTIC 고유 오류 계약, 운영 key/IP 인증, 5분 업무 수집 주기, 실제 사고 데이터의 정확성은 이번 정상 제공시험의 완료 범위에 포함하지 않는다.

## 실행

1. `scenarioengine/project/vs2022/ScenarioEngineTest.vcxproj`를 Debug|x64로 빌드한다.
2. `emulator/Start-UticProviderSut.ps1`을 실행한다. 기본 수신 주소는 `127.0.0.1:55328`이다. 상대 프로그램은 `UTIC_TEST_API_KEY` 환경변수로 다른 시험키를 받을 수 있다.
3. 플랫폼 #59에서 자체 시험을 열고 화면의 Agent URL로 엔진을 연결한다.
4. `registration/centerClient2utic_v1.example.json`의 설정을 적용하고 실행한다. 기본 key는 합성 시험값 `SC28_LOCAL_KEY`다.
5. 실시간 상세 항목 결과와 저장 보고서를 확인한다.

접속 제한 기본 5초·응답 제한 기본 30초는 환경값이다. 표준에서 정한 처리 지연 한계로 표시하지 않는다. HTTPS의 인증서 검증은 유지하며 리다이렉트는 자동 추적하지 않는다. `X-Test-Run-Id/Exchange`는 증적 연결용이고 대상에게 같은 값을 회신하도록 요구하지 않는다.

`rest-results/<runId>/response-N.xml`은 실제 수신 원문이다. `request-N.txt`는 key를 가린 요청 구성 기록이며 패킷 캡처는 아니다. 실제 method/path/key 인코딩·본문 부재·Accept는 독립 SUT 수신 로그로 대조한다. 플랫폼 설정/제어 로그에는 입력값이 남을 수 있어 현재 검증에서는 합성 시험값만 사용했다.

## 재사용·검증

prj22에서 가져온 `GitsnOpenApi` 클라이언트에 `getXml` 진입점을 추가하고 JSON/ XML 전송 코드를 공유한다. 기존 `getJson`의 Accept와 동작은 보존한다. `HttpClientAdapter`는 공통 GET 전송을 제공하고 VDS와 UTIC의 규칙은 각 provider에 둔다.

```powershell
python -X utf8 restconformance/tests/verify_utic_provider.py --exe restconformance/project/vs2022/Debug64/UticConformanceCli.exe --output <새결과폴더>
```

로컬 검증 20건: 정상, 인코딩된 키, text/xml, 필수 필드 누락, 중복 필드, 코드·날짜·숫자 오류, 잘못된 루트·네임스페이스, 손상 XML·DTD·UTF-8, HTTP 500, 잘못된 Content-Type, 빈 result, 크기 초과, 타임아웃, 중지, 연결 거부. 오류 입력은 시험기 판정 검증이며 모두를 등록된 표준 세부시험으로 집계하지 않는다.

[플랫폼 검증 결과](../doc/gyeong4/2026-v2.1/utic-provider-platform-verification-20260924.md)를 따른다.

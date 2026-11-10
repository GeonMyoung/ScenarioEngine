# SC11 — UT 센터 VDS 원시정보 이력 제공시험

2026-09-24 후속 보완: 현재 시험방법은 REST-EVIDENCE-002, 데이터 검사는 **REST-DATA-003**이다. 아래 최초 구현 당시 남겨둔 날짜·길이·숫자 정밀도 검사를 양측 역할에 보완했다. [현재 검사·검증 범위](../doc/gyeong4/2026-v2.1/rest-standard-fields-verification-20260924.md)를 우선 적용하며 이전 실행 결과는 이력으로 보존한다.

플랫폼 [57](https://106.250.189.37:8443/test/scenario/57), category `ITSK-00143-REST-V1`, case `microClient2center_v1`, 선택 항목 `test_normal_vds`.

시험기는 미시교통정보 플랫폼 역할의 HTTP Client이고, 시험 대상은 UT 센터 HTTP Server다. 정보는 UT 센터에서 시험기로 전달된다. 기존 SC11의 VDS 부분이며 스마트교차로 항목까지 완료한 것은 아니다.

## 적용 계약과 판정 범위

- 회신 자료에 연결된 경4 OpenAPI의 `GET /v1/adxc/vds-l-raws`를 사용한다. query/body는 보내지 않는다.
- `Authorization: Bearer …`, 응답 HTTP 200과 `application/json`을 확인한다. 인증 토큰 발급·검증 정책은 시험에서 만들지 않는다.
- 제3부 §2.4, 표 4-22의 JSON 예제와 OpenAPI `VdsLRawDto`의 camelCase 키를 사용한다. 정상 데이터가 있는 배열을 준비하고 제4부 §1.2.1에 따라 최소 10회 교환한다.
- UTF-8, JSON 구문·중복 키·배열/객체 구조·자료형·필수 필드 및 int32 필드를 검사한다. `volS/volM/volL`은 생략 가능하며 제공된 경우 자료형을 검사한다.
- 배열에 정상 레코드가 없는 회차는 `EVIDENCE_PENDING`으로 남긴다. 200과 빈 배열만으로 정상 정보제공 성공을 만들지 않는다.
- 숫자 폭·소수 자릿수·시각 형식·문자열 길이는 표준과 실제 API 간 대응 확정 전의 잔여 범위다. DTO의 number를 표준의 정수로 임의 축소하거나, 실제 날짜 형식을 추정하여 실패시키지 않는다.
- 잘못된 요청/자료 부재의 구체적인 자극과 상태·본문 규칙은 아직 미확정이다. 400/500 응답이 문서에 있다는 것만으로 임의 오류 요청시험을 등록하지 않는다.
- HTTP 오류·손상된 응답·중지의 로컬 검사는 시험기 구현 검증이다. 등록된 표준시험 항목 수는 **정상 VDS 제공시험 1개**다.

| 표준 필드 | 응답 키 | 현재 검사 |
|---|---|---|
| collect_date / stn_id | collectDate / stnId | 필수 string |
| lane_no / err_code | laneNo / errCode | 필수 int32 |
| vol / spd / occ | vol / spd / occ | 필수 유한 number |
| vol_s / vol_m / vol_l | volS / volM / volL | 선택 number, 제공 시 유한성 검사 |
| link_id / vds_id / stn_location | linkId / vdsId / stnLocation | 필수 string |

## 재사용 구조

prj22 `GitsnOpenApi_request.c`와 해당 libcurl/libssh2 소스를 가져와 저장소 내부에서 빌드한다. 원본 prj22는 수정하지 않았다. 출처·해시는 `GitsnOpenApiHttpAdapter/client-import-manifest.json`에 있다.

prj22 `RestApiTestScenarioProcProvideGetClient.c`와 `Prj1RestApiTestSupportValidateResponse.c`의 HTTP 200 → Content-Type → 응답 구조 검사 순서, 통신/표준별 provider 분리 방식을 참고했다. 국1 전용 operation·pagination·오류 순서는 가져오지 않았다.

`HttpClientAdapter`는 재사용한 전송 API와 중지·응답 크기 제한을 담당하고, `VdsProvider`는 경4 계약을 담당한다. 공통 SDK의 소스는 바꾸지 않았다. HTTPS 인증서 검증을 유지하며 리다이렉트는 자동 추적하지 않는다. 응답 본문의 운영 한도는 1 MiB이고 초과를 성공으로 판정하지 않는다. 이 한도는 표준 규정이 아니라 현재 시험 도구의 한도다.

## 실행

1. `scenarioengine/project/vs2022/ScenarioEngineTest.vcxproj`를 Debug|x64로 빌드한다. `ScenarioEngine.vcxproj`는 정적 라이브러리 프로젝트다.
2. `emulator/Start-VdsSut.ps1`로 UT 센터 역할의 독립 서버를 시작한다. 기본 주소는 `http://127.0.0.1:55311`이다.
3. 플랫폼 #57에서 자체 시험을 열고, 화면의 Agent URL을 `tools/Start-PlatformEngine.ps1 -AgentUrl …`에 전달한다.
4. `registration/microClient2center_v1.example.json`에 맞춰 입력하고 시험을 실행한다. 기본 토큰은 합성 시험값이다. 상대 프로그램은 `VDS_TEST_BEARER_TOKEN` 환경변수로 다른 값을 받을 수 있다.
5. 시험 상세 항목의 성공/실패와 `rest-results/<runId>/result.json`을 확인한다.

접속 제한시간 기본 5초, 전체 응답 제한시간 기본 30초는 환경 설정이며 표준 성능 한계가 아니다. `X-Test-Run-Id/Exchange`는 증적 대조용 헤더로, 일반 SUT에 이를 응답하라고 요구하지 않는다.

증적의 `request-N.txt`는 인증값을 가린 요청 구성 기록이다. 패킷 캡처라고 주장하지 않는다. 실제 요청 method/path/query 부재/본문 부재와 인증값 일치는 독립 SUT의 수신 로그로 대조한다. `response-N.json`은 실제 수신 본문이다. 플랫폼 설정 화면/SDK 원시 제어 로그는 설정값을 보존하므로 이번 검증에서는 합성 시험값만 사용했다.

## 개발 검증

```powershell
python -X utf8 restconformance/tests/verify_vds.py --exe restconformance/project/vs2022/Debug64/UticConformanceCli.exe --output <새결과폴더>
```

17건: 정상, 선택 필드 생략, 필수 누락, 잘못된 숫자 자료형, 비정수 int32, null, 손상 JSON, 잘못된 최상위 구조, 중복 키, 손상 UTF-8, HTTP 500, 잘못된 Content-Type, 빈 배열, 크기 초과, 타임아웃, 중지, 연결 거부.

[플랫폼 검증 결과](../doc/gyeong4/2026-v2.1/vds-platform-verification-20260924.md)에 실제 회차와 범위를 기록했다. 에뮬레이터를 SUT로 사용하는 현재 개발 검증이며 실장비 단계는 기존 합의대로 전체 개발 이후다.

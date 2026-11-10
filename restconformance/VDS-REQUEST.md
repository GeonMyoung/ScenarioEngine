# SC32 — 미시교통정보 플랫폼 VDS 원시정보 이력 요청시험

2026-09-24 후속 보완: 현재 시험방법은 REST-EVIDENCE-002, 데이터 검사는 **REST-DATA-003**이다. 아래 최초 구현 당시 남겨둔 날짜·길이·숫자 정밀도 검사를 양측 역할에 보완했다. [현재 검사·검증 범위](../doc/gyeong4/2026-v2.1/rest-standard-fields-verification-20260924.md)를 우선 적용하며 이전 실행 결과는 이력으로 보존한다.

`centerServer2micro_v1`은 SC11 VDS 제공시험의 반대 역할이다. category는 `ITSK-00143-REST-V1`, 선택 항목은 `test_request_vds`다.

| 구성 | 시험 시스템 | 시험 대상 시스템 | 정보 방향 |
|---|---|---|---|
| SC11 / 플랫폼 57 | 미시교통정보 플랫폼 HTTP Client | UT 센터 HTTP Server | UT 센터 → 미시교통정보 플랫폼 |
| SC32 / 플랫폼 58 | UT 센터 HTTP Server | 미시교통정보 플랫폼 HTTP Client | UT 센터 → 미시교통정보 플랫폼 |

정보 방향과 API는 동일하며 시험 대상과 시험기가 맡는 역할을 교환한다. SC11의 서버 에뮬레이터 파일은 `emulator/ut_center_vds.py`, SC32의 클라이언트 에뮬레이터 파일은 `emulator/micro_vds_client.py`다. 반대 역할의 에뮬레이터 존재와 반대 시험 시나리오 구현은 별도로 확인한다.

## 실행·검사

시험기는 `GET /v1/adxc/vds-l-raws`를 수신하고 method/path/query/본문/단일 Bearer 인증 헤더를 검사한다. 정상 요청에는 준비된 VDS JSON 배열을 응답한다. 제4부 정보요청시험에 따라 최소 10회 교환하며, 응답 전송 완료 이벤트까지 확인한다. 요청시간 기본 30초는 시험 환경값이다.

헤더의 Authorization 이름과 Bearer 인증 방식 이름은 대소문자를 구분하지 않고 토큰 값은 정확히 비교한다. 중복/누락된 인증 헤더, 예상 밖의 query, 실제 본문 또는 본문 전송을 나타내는 Content-Length/Transfer-Encoding을 거부한다. 오류 요청에 보내는 400은 시험기의 진단 응답이며 경4 운영 API의 미확정 오류 계약을 정의한 것이 아니다.

응답 JSON은 기본 자료 또는 `response_json_file`로 설정한다. 실행 전 기존 SC11의 DTO/필수 필드 검사를 재사용하고 비어 있는 배열을 정상 시험 자료로 사용하지 않는다. SC11에서 남긴 스마트교차로, 숫자 폭/정밀도·시각 등 세부 제약 대응은 이 역할에서도 동일하게 남긴다.

1. `ScenarioEngineTest.vcxproj`를 Debug|x64로 빌드한다. `ScenarioEngine.vcxproj`는 라이브러리이며 실제 플랫폼 실행 EXE는 Test 프로젝트에서 생성된다.
2. [플랫폼 58](https://106.250.189.37:8443/test/scenario/58)에서 자체 시험을 열고 화면의 Agent URL로 엔진을 연결한다.
3. `registration/centerServer2micro_v1.example.json`을 기준으로 설정한다. 기본 수신 주소는 `127.0.0.1:55332`다.
4. 시험을 시작해 LISTENING을 확인한 후 `emulator/Start-MicroVdsSut.ps1`을 실행한다. 기본 SUT 설정은 `emulator/micro-vds-sut.example.json`이다.
5. `rest-results/<runId>/`의 전송 기록과 클라이언트 에뮬레이터의 수신/처리 기록을 아래 도구로 대조한다.

```powershell
python -X utf8 restconformance/tools/review_vds_request_evidence.py --report <result.json> --sut <상대결과폴더> --output <새검토결과.json>
```

기본 Bearer 값은 합성 시험값이다. 원문 토큰은 HTTP 어댑터 메모리에서 검사하며 전송 증적에는 포함하지 않는다. 기존 플랫폼 설정/제어 로그는 입력값을 보존하므로 현재 검증은 합성 값으로 진행했다.

## 판정과 증거

HTTP 전송만으로 대상 내부 처리를 단정하지 않는다. 원본 자동 결과는 `EVIDENCE_PENDING`이고 UI는 종료로 표시한다. 검토 도구는 실제 수신 JSON의 SHA-256, runId, 교환 번호, 저장된 처리 레코드, 처리 시각을 대조해 별도 개발 검증 결과 PASS를 남긴다. 원본 실패/중지/증거 대기 결과를 덮어쓰지 않는다.

처리 증거가 없는 경우, 수신 원문 해시가 다른 경우, 처리 이벤트가 중복된 경우, 처리 레코드가 바뀐 경우는 대조 실패다. 시험기 단독의 응답 전송 로그는 SUT 처리 증거를 대신하지 않는다.

독립 실행 검증은 `tests/verify_vds_request.py --exe <UticConformanceCli.exe> --output <새폴더>`로 수행한다. `--case`로 실패 수정에 관련된 회차만 재검증할 수 있다. 기존 정상 시험을 불필요하게 반복하지 않는다.

[2026-09-24 플랫폼 검증 결과](../doc/gyeong4/2026-v2.1/vds-request-platform-verification-20260924.md) 및 [비 DATEX 양측 범위](../doc/gyeong4/2026-v2.1/non-datex-paired-scope-20260924.md)를 따른다.

# 차량–센터 MQTT V2N 시험

## 2026-11-04 TIM 상세시험 분리 및 사용자 로그

센터 SUT #82의 기존 TIM 집계 항목을 다음 5개 독립 선택 항목으로 분리했다: 직접 감속 지시(limit_speed), 제한속도 준수(maintain_speed), 좌측 차로 사용(left_lane), 우측 차로 사용(right_lane), 갓길 차로 사용(shoulder). 상태 키는 test_tim_접미사이고 규격 ITIS 7443/7444/7428/7427/7436에 대응한다. #82는 SPaT·TLSM 각 2개+TIM 5개=9개, 전체 4개 시나리오는 15개 상세시험이다. #83의 일반 TIM 송신/수신 관측 자산은 유지한다.

TIM은 한 번 구독해 선택한 종류만 검증하며 완료한 항목은 즉시 SUCCESS로 보고한다. 미선택 종류는 완료 건수/판정에 합산하지 않는다. 누락·잘못된 값·중지 결과는 해당 항목에 귀속하며 확인된 항목의 성공을 덮어쓰지 않는다. timeout은 선택한 미완료 종류만 실패로 표시한다. 공통 수신/디코딩 오류로 종류를 특정할 수 없으면 아직 미완료인 항목에 공통 원인을 남긴다. 기존 캐시의 test_tim_normal=true는 새 선택값이 전혀 없을 때만 5개 전체 선택으로 변환한다. 새 개별 선택이 있으면 그 선택을 우선한다.

사용자용 events.jsonl에는 진행·정보값·기대/실제값·중복·누락·판정 근거를 간결하게 표시한다. 원문 HEX, 연결 패킷, 전체 디코딩 JSON과 내부 경로/예외는 diagnostic-events.jsonl 및 원본 자료 파일에 보존한다. 웹과 간편실행기의 기본 화면에는 이 내부 진단을 보내지 않는다. 간편실행기의 로컬 보고서는 항목별 결과 표를 제공한다. content 선택값 차이와 BSM vert OPTIONAL 보류, version 0·최대 갱신 간격 기준은 유지한다. 아래 집계 TIM 및 전체 원문 화면 표시 설명은 이전 이력이다.

## 2026-11-02 최대 갱신 간격 적용

현재 MQTT 수신 간격 판정의 기본은 `period_mode=maximum_gap`이다. BSM/SPaT/TLSM의 빠른 수신(0.3초·0.5초 등)은 허용하고, 각 간격이 1초+`period_tolerance_seconds`(기본 0.1초)를 초과하면 실패한다. 0.1초 입력 시 상한 1.1초, 0.2초 입력 시 상한 1.2초이다. 경계값 비교에는 부동소수점 계산 잡음을 제외하기 위한 1ns 절대 여유를 둔다. 음수/비유한 수신 간격은 시각 자료 이상으로 거부한다.

기존 `abs(delta-expected)>tolerance` ±판정 코드는 intervals.py의 `periodic` 분기로 보존하고 별도 검증했다. 현재 웹·간편실행기는 최대 갱신 간격을 안내하며 기존 주기시험 ID(`test_*_period`)는 유지한다. `periodic`은 코드/직접 설정을 통한 보존 경로이며 새 사용자 선택 기능을 추가한 것은 아니다.

수신 간격 전체·최소/최대·판정 모드·상한·초과 구간을 로그에 남긴다. 이 수신 간격은 메시지 내용의 최신성을 입증하지 않는다. TIM 5종은 이벤트성 검증 계약을 유지하며 BSM 발행시험의 1초 송신 조건과 DATEX/Kafka 등 다른 프로토콜에는 적용하지 않는다. 아래 예전 ±판정 설명은 이 변경 이전 이력이다.

## 2026-11-02 TIM 5종 확인

센터 제공 시험 #82의 TIM은 furtherInfoID+ITIS 조합 0C01/7443·7444, 0C02/7428·7427·7436을 모두 검증한다. `tim_per_type`(기본 1, 범위 1~100)은 유형별 서로 다른 본문 확인 건수이고 `tim_timeout_seconds`(기본 120, 범위 1~3600초)는 5종 전체 확인 제한시간이다. TIM에는 일반 repetitions와 주기 설정을 적용하지 않는다.

같은 본문의 재수신 또는 이미 완료한 종류의 추가 수신은 중복으로 기록하며 미확인 종류를 대체하지 않는다. 도착 순서는 자유다. 5종 모두 확인, 실패, 사용자 중지 또는 제한시간에 구독을 정리한다. 제한시간 초과는 누락 종류를 한국어로 안내한다. `tim-summary.json`과 `tim-messages.jsonl`, 전체 웹 NOTIFY에 종류별 검증·중복·누락과 원문을 남긴다.

V2N/UPER 검사 후 packetID·startYear 존재, 단일 프레임·구간, roadSignage, 식별값 조합, 예약값 0, 국내 확장의 대상 linkID와 dataFrameIndex를 검사한다. SPEED 문구는 제공된 경우 추출해 표시하며 예시 문구를 필수로 승격하지 않는다. packetID는 화면용 문자열 대신 원시 ASN.1의 HEX를 별도로 기록한다. 타깃 LaneBelt 값과 속도값은 실제 관측값이며 미제공 외부 기대값과 일치했다고 표시하지 않는다. 시간 최신성은 이 기능의 판정 기준에 추가하지 않는다.

content CHOICE의 advisory/speedLimit/genericSign 차이는 사용자 지시로 보류한다. 실제 선택값을 저장하고 `content_review=HELD`로 안내하며 자동 성공도 그 차이의 적합성을 확정하지 않는다. BSM vert OPTIONAL 보류도 유지한다. 간편 상대는 2026-10-29 실제 TIM 원문에서 추출한 테스트 fixture로 5종을 발행하며, fixture 출처는 emulator/tim-five-fixtures.json에 있다. 기존 DATEX와 다른 MQTT 역할은 일반 TIM 계약을 유지한다.

경4 ITSK-00143-3 20261016 HWP와 FID/PSID 정의안의 BSM·SPaT·TLSM·일반 TIM 정보교환을 시험한다. 실제 MQTT Topic을 환경설정에서 입력받고 그 값에 맞는 컨테이너·UPER를 검사한다. 기존 DATEX case는 보존한다.

## 2026-10-29 BSM 발행시험 변경 (개발본)

- #81은 V2N **version 0**으로 고정한다. MQTT 연결 프로토콜 버전 변경이 아니다.
- 동일 BSM 본문 반복을 회차별 생성으로 변경했다. n=회차-1, msgCnt=n%128, lat=370000000+100n, lon=1270000000+100n, elev=100+n%100, speed=500+n%100, heading=7200+n%100, angle=n%21이다. 모두 ASN.1 원시 값이다. 차량 ID는 실행마다 임의 4바이트를 생성하고 실행 중 유지한다. transmission은 forwardGears이다.
- secMark는 시작 UTC에서 회차마다 1초 증가하는 **모의 시각**의 분 내 밀리초다. 실제 발행 시각은 requested_utc/단조 시계 기록으로 별도 남긴다. 실제 차량 주행 재현이나 센터의 시간 최신성 시험을 의미하지 않는다.
- CSV/JSONL에 생성 필드·decoded_json·컨테이너 version·원문·해시·모의 시각을 남긴다. 매번 인코딩한 본문을 다시 검사하고 생성값과 대조한 후 전송한다. 웹 NOTIFY에도 같은 회차 데이터를 첨부한다.
- vert OPTIONAL 정의는 유지한다. 기존 수신 로그에서 확인한 accelSet/brakes/size 해석 차이는 `PENDING_VERT_OPTIONAL_DECISION`으로 기록하며 최종 판단을 보류한다. 고정 가속도/제동/크기 값은 기존 샘플을 유지한다.
- 이 변경은 개발 코드/Release 코덱/로컬 검증에 반영했다. BSM 변경은 MSI 1.2.7·간편실행기 v7로 배포했으며, 전체 메시지 version 0 통일은 후속 배포에 포함한다.
- 검증 중 기존 JSON 변환이 음수 angle=-10을 unsigned 정수로 표시하는 별도 제약을 발견했다. 이번 샘플은 0~20의 비음수 조향각을 사용한다. 음수 조향각 표시 수정은 이번 변경에 포함하지 않았다.

## 구현 범위

| case | 시험 대상 | 시험기 역할 | 항목 |
|---|---|---|---:|
| `centerSubscriber2vehicle_mqtt_v1` | 차량의 BSM 제공 | 센터 Subscriber | 정상·주기 2 |
| `vehiclePublisher2center_mqtt_v1` | 센터의 BSM 수신 | 차량 Publisher | 발행 절차 1 (사후 로그 대조) |
| `vehicleSubscriber2center_mqtt_v1` | 센터의 SPaT/TLSM/TIM 제공 | 차량 Subscriber | 정상 3·주기 2 |
| `centerPublisher2vehicle_mqtt_v1` | 차량의 SPaT/TLSM/TIM 수신 | 센터 Publisher | 수신 관측 3 |

범주: `ITSK-00143-MQTT-V1`. 4개 case, 선택 항목 11개다. F2F 변경과 FF00~FF09 통행지시/결과 신규 서비스는 보류한다. TIM은 FF13의 일반 메시지 교환·디코딩 범위다. 설정된 토픽을 공유하는 SPaT/TLSM/TIM도 FID/PSID를 함께 대조해 구분한다.

2026-10-19 경4 웹 플랫폼에 ID **80~83**으로 등록하고 실제 ScenarioEngine·MQTT Broker·독립 상대 에뮬레이터로 4개 시나리오, 11개 선택 항목을 실행했다. 실시간 화면과 저장 보고서 모두 성공을 확인했다. [등록용 manifest](registration/manifest.json)에 플랫폼 ID·등록 파일·결과 보고서 링크가 있으며, [플랫폼 검증 기록](../doc/gyeong4/2026-v2.1/mqtt-v2n-platform-verification-20261019.md)에 실행 근거와 관측 한계를 정리했다. 이어서 [MSI 1.2.0](../doc/msi-release-20261019.md)에 반영하고 추출한 Release 실행본의 11개 항목도 확인했다. 후속 요청으로 [실제 업데이트 설치·웹 실행](../doc/gyeong4/2026-v2.1/mqtt-v2n-installed-web-verification-20261019.md)까지 확인했다. 실장비 검증은 별도다.

## 간편실행기

토픽 입력·Broker와 상대 자동 준비·웹 시작·결과 표시를 연결한 [MQTT/V2N 간편실행기](launcher/README.md)를 제공한다. 기준 MSI는 대기시간 경계 오류를 수정한 1.2.1이며 현재 PC에도 설치했다. [최종 실제 웹 검증](../doc/gyeong4/2026-v2.1/mqtt-v2n-easy-launcher-verification-20261019.md)에서 4개·11항목을 확인했다.

## 적용 형식

| 메시지 | FID | PSID | UPER MessageFrame ID |
|---|---|---:|---:|
| BSM | FF10 | 82050 | 20 |
| SPaT | FF11 | 82055 (014087) | 19 |
| TLSM | FF12 | 82176 | 50 |
| TIM | FF13 | 82054 | 31 |

`G4-SINGLE-04-DEV-1`은 경4 부록 Ⅰ의 단일 메시지 type 0x04를 사용하는 개발 profile이다. 순서는 type(1), version(1), FID(2), standard_type(1), SEM length(1), flags(1), SEM(N), message_id(1), PSID(4), message_length(4), UPER payload다. 길이는 바이트 단위다.

- HWP에 명시된 필드 폭·type=04·FID/PSID를 적용한다. V2N message_id는 별도 8비트 식별자이며 MessageFrame ID와 같다고 강제하지 않는다.
- 2026-10-29 사용자 확정: 4개 MQTT 역할과 BSM/SPaT/TLSM/TIM 전체의 V2N version은 0으로 고정한다. version 1 설정과 수신 메시지는 허용하지 않는다. 다중 바이트 Big-Endian과 SEM length의 메타데이터 바이트 수 해석은 유지하며 byte_order는 기존 설정을 따른다. standard_type은 현재 연결한 KS/KOR 코덱에 맞춰 1(KS)만 지원하며 SAE/기타 코덱 지원으로 확대하지 않는다. 개발 기본값을 외부 회신이나 표준이 직접 확정한 값으로 표현하지 않는다.
- SEM은 길이·범위와 원문을 보존한다. 개별 메타데이터의 업무 의미는 검사하지 않는다. 잘린 헤더/본문, 초과 길이, 잉여 바이트, 타입·버전·FID·PSID·표준 유형 불일치를 거부한다. payload 상한은 1 MiB다.
- UPER는 기존 KS/KOR 생성 코덱의 `ASN1_CHECK_*`와 JSON 변환을 재사용한다. MQTT 전용 `MqttPayloadStrict`가 MessageFrame·내부 value의 실제 소비 비트 수, 입력 길이, 마지막 바이트의 0 패딩을 검사한다. `MqttAsnBounds`는 이 실행 파일 안에서 입력 범위를 넘는 읽기를 차단하고 open type을 메모리 이동 없이 읽는다. DATEX 및 공용 SDK 소스는 변경하지 않았다.
- 최신 제3부 제4장 §1.2의 BSM/SPaT/TLSM은 KS R 1600-2/3, TIM은 KS R 1600-5를 준용한다. 현재 FF10~FF13 일반 메시지에 적용할 별도의 필수 필드 승격은 본문에서 확인되지 않았다. 부록 Ⅱ 통행지시의 packetID/startYear 필수, 단일 프레임, 특정 msgId·ITIS 코드 등은 보류한 서비스의 규칙이다. 일반 TIM에 강제하지 않는다. [요구조건 대조와 보완 검증](../doc/gyeong4/2026-v2.1/mqtt-payload-hardening-20261019.md)을 따른다.
- 현재 코덱의 ASN.1 필수 구조·값 범위·SIZE/CHOICE 제약을 확인한다. 규격상 unavailable 값과 OPTIONAL 생략은 허용하며 업무상 유효값으로 임의 제한하지 않는다. 지원하는 TIM KOR 확장 2종에도 경계 검사를 적용한다. 그 밖의 open type/지역별 확장 내부 의미, 외부의 모든 KS/SAE 채택판과 생성 ASN.1의 동등성은 이번 완료 범위에 포함하지 않는다.
- prj22 V2NCT의 type 02/03 메시지 세트와 이 형식을 혼합하지 않는다. 비교·기준은 [구현 계획](../doc/gyeong4/2026-v2.1/mqtt-v2n-implementation-plan-20261019.md)을 따른다.

## 설정과 판정

각 메시지의 `topic_bsm`, `topic_spat`, `topic_tlsm`, `topic_tim`은 선택한 항목에서 필수다. 빈 값·와일드카드·NUL은 거부한다. 대소문자·슬래시·공백을 자동 정규화하지 않는다. 연결한 Client ID도 명시적으로 입력한다. QoS 0/1/2를 지원하며 retain된 과거 메시지는 현재 정보교환 횟수에 합산하지 않는다.

정보제공 대상 시험은 실제 수신 메시지를 검증한다. 기본 정상 반복은 10회이며 설정 가능하다. 별도 주기 항목은 BSM/SPaT/TLSM의 1초 수신 간격을 관찰하고 환경설정 허용오차(개발 기본 0.1초)로 판정한다. 허용오차는 프로젝트 설정이며 DATEX의 정책을 이식한 값으로 설명하지 않는다. TIM에는 고정 주기 항목이 없다.

정보수신 대상 시험은 Broker의 PUBACK/PUBCOMP만으로 대상 수신을 성공 처리하지 않는다. `observation_file`로 지정한 실시간 JSONL 관측 어댑터에서 **실행 시작 이후 추가된 Topic·컨테이너 원문·메시지 종류·디코딩 결과**를 대조한다. 개발용 독립 상대가 다음 레코드를 생성한다.

```json
{"topic":"my/bsm","payload_hex":"실제로 받은 V2N 전체 HEX","frame_id":20,"valid":true,"received_unix":1790000000.0}
```

이 형식은 이번 구현의 관측 어댑터 계약이다. 표준이 특정 파일 제출을 의무화한 것으로 사용하지 않는다. 실제 대상에는 허용된 로그/모니터링을 이 계약에 연결해야 한다. 대상 내부 업무 처리·차량 제어 결과까지 판정하지 않는다. 관측이 없으면 대기시간 후 FAIL이며, 과거 레코드·파일 교체/축소를 새 수신 근거로 쓰지 않는다.

모든 발행 요청·수신 원문·디코딩 결과·연결/구독/발행 완료·해지/종료 관측을 기록한다. libmosquitto API에서 관측하는 범위이며 모든 TCP/TLS/MQTT 제어 패킷의 원시 캡처를 뜻하지 않는다. 큰 표시 자료는 순서가 있는 JSON 조각으로 빠짐없이 전송한다. 상세 START→결과, MainScenario 최종 결과→FINISH 1회이며 COMPLETE는 전송하지 않는다. 실패와 중지는 완료 횟수와 시도 회차를 구분한다.

## 재사용

- prj22 `tools/easy-launcher/peers/mqtt_transport.py`를 그대로 가져오고 [transport.py](runtime/transport.py)에서 취소, bounded queue, async connect, unsubscribe와 관측을 보완했다. [출처 해시](reuse-manifest.json)를 보존한다.
- UPER 검사·샘플은 ScenarioEngine의 DATEX payload 코드를 링크해 사용한다. 기존 DATEX 소스는 변경하지 않았다.
- Dz1Task adapter·worker bridge·알림 큐는 기존 Kafka 모듈에서 별도 모듈로 분리해 사용한다. 인증값은 `security_file`에 둔다. 원문 인증 파일은 알림·설정 receipt에 복제하지 않는다.

MQTT transport에는 TLS CA·사용자 인증, unsubscribe/SUBACK, LWT 설정 API가 있다. 이번 실행 검증은 loopback PLAINTEXT의 정상 정보교환·주기·오류·중지 범위다. 차량 이동에 따른 대상의 재구독, 대상의 LWT/재접속을 검증하는 별도 자동 시험항목 및 TLS 상호운용은 검증 완료 항목에 포함하지 않는다.

## Configure

Windows x64, Visual Studio 2022 C++/MSBuild, Python 3.12 이상, 기존 저장소 SDK 구성을 사용한다. prj22 작업폴더는 개발 런타임을 준비할 때만 원본 DLL을 읽는다. 만들어진 실행 묶음의 경로는 해당 작업폴더를 런타임 의존성으로 사용하지 않는다.

```powershell
Set-Location C:\Implement\ScenarioEngine-worktrees\GM-62-gyeong4-analysis
.\tools\build-mqtt-v2n.ps1 -Engine
python -X utf8 mqttv2nconformance\tools\prepare_runtime.py `
  --output .local\mqtt-v2n-20261019\dev `
  --broker-runtime C:\Implement\prj22\agent\tools\easy-launcher\runtime\broker\mosquitto
```

개발 준비 도구는 `mqttv2n-runtime.json`을 실행 파일 옆에 두고 현재 Python 경로와 module 위치를 기록한다. 다른 개발 PC에서는 `--python`과 `--broker-runtime`을 실제 위치에 맞게 입력한다. 개발 묶음에는 mosquitto 실행파일/DLL과 EDL/EPL·NOTICE를 함께 복사한다. MSI 1.2.0은 설치된 Python과 모듈의 상대 경로를 사용하고, MQTT 클라이언트 DLL·코덱·라이선스를 포함한다. Broker 서버·상대 에뮬레이터는 설치하지 않는다.

## Build / Run

VS 솔루션: `scenarioengine\project\vs2022\ScenarioEngine.sln`. 추가 타깃은 `MqttV2NConformance` 정적 라이브러리와 `MqttPayload` UPER 도구다. 엔진 시작 프로젝트는 `ScenarioEngineTest`다. 경4 플랫폼에서는 등록 ID 80~83의 자체 시험을 사용하고, 해당 회차의 Agent URL로 MQTT 모듈이 포함된 개발 실행본을 연결한다. 시험 환경설정의 접속값·토픽·시험 조건을 직접 입력하고 선택 항목을 체크한 뒤 설정→시험 시작 순서로 실행한다.

등록 파일은 `registration/*.tsb`이며 내용은 `{"category":"ITSK-00143-MQTT-V1","testScenario":"case 식별자"}`의 UTF-8 JSON을 Base64 인코딩한 형식이다. 관리자 등록 화면의 파일 묶음 제목은 `scenario`로 설정한다. `generate_catalog.py`는 manifest를 새로 생성하므로 현재 플랫폼 ID·검증 정보를 보존한 뒤 사용한다.

프로토콜 및 실제 엔진 연결의 개발 검증 명령:

```powershell
python -X utf8 -m unittest discover -s mqttv2nconformance\tests -p test_contract.py -v
python -X utf8 mqttv2nconformance\tests\integration.py `
  --bundle .local\mqtt-v2n-20261019\dev --output .local\mqtt-v2n-20261019\manual-protocol
python -X utf8 mqttv2nconformance\tests\engine_bridge.py `
  --bundle .local\mqtt-v2n-20261019\dev --output .local\mqtt-v2n-20261019\manual-engine
```

마지막 명령은 Python `websockets`가 필요하다. 검증 도구가 임시 loopback Broker와 독립 상대를 시작하고 해당 프로세스만 정리한다. 동봉 Broker의 포트는 운영 Broker와 분리한다. 임의 외부 SUT에 자동 연결하지 않는다.

## Success Criteria

- 단위 검사 10개 통과, 실제 Broker 검증에서 정상/공유 토픽/주기/QoS 항목 SUCCESS.
- 잘못된 PSID·길이·UPER·대상 수신 관측 부재는 예상 FAIL. 사용자 중지는 STOPPED.
- 실제 ScenarioEngine 실행에서 UI_CONFIGURE, 유효 SETUP, START, 전체 송수신 알림, SUCCESS/FINISH를 확인한다. 실패한 재설정 이후 이전 설정으로 START할 수 없어야 한다.
- 모든 결과는 적용 profile과 관측 범위를 포함한다. 실행별 `events.jsonl`, `result.json`, 테스트 도구의 `verification.json`을 확인한다.

새 작업 없이 검증을 반복할 필요는 없다. 이미 수행한 결과는 [검증 보고](../doc/gyeong4/2026-v2.1/mqtt-v2n-implementation-result-20261019.md)를 따른다.

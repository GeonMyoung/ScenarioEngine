# 경4 Kafka 인터페이스 시험

**시험 범위 — 사용자 확정 2026-09-25:** Kafka Broker는 중계 인프라이며, Broker 너머의 대상 시스템이 정보를 올바르게 제공하거나 수신하는지를 평가한다. UT를 대상으로 할 때는 시험기가 Producer, 외부 플랫폼/I2X를 대상으로 할 때는 시험기가 Consumer 역할을 맡는다. Broker의 발행 ACK는 대상 수신·내부 처리 완료와 구분한다. [KAFKA-SCOPE-001](../doc/development-policy.md)의 범위 결정이며 이번 문서 정리로 실행 코드나 기존 판정이 변경된 것은 아니다.

**반복 연계 기준 — KAFKA-REPEAT-001:** 시험기 Consumer는 3초 Heartbeat·10초 세션 설정을 사용하고 대상의 설정값은 판정하지 않는다. 현재 필수 범위는 최소 10회 반복 정보연계다. 기본 `auto_offset_reset=latest`이며, 실제 시험 Consumer는 각 상세시험 준비 시 partition 끝 Offset을 확보하고 그 위치부터 읽으므로 이전 자료를 제외한다. `latest`만으로 기존 그룹의 저장 Offset을 무시하는 것은 아니다. 수신 시작 기준은 이 위치를 확보한 시점이며 엄밀한 구독 함수 호출 시각이나 업무 데이터 생성 시각과 동일하지 않다. 원문에 없는 세션 장애·복구 시험을 완료 요건에 추가하지 않는다.

SC12·SC33은 오픈데이터/플랫폼 상태, SC13·SC34는 I2X 시설/MAP/상태의 양측 시험이다. 독립 상대와 실제 Apache Kafka를 사용하는 개발 검증이다. [설계·근거](../doc/gyeong4/2026-v2.1/kafka-implementation-plan-20260925.md) · [4개 플랫폼 실행·보고서 결과와 한계](../doc/gyeong4/2026-v2.1/kafka-verification-20260925.md).

| 설계 | 플랫폼 등록 | case | 시험 대상 | 시험 시스템 | 상세항목 |
|---|---:|---|---|---|---:|
| SC12 | 76 | platform2ut_kafka_v1 | 통합교통관제시스템 Consumer | 플랫폼 Producer 및 offset 관측 | 4 |
| SC33 | 77 | ut2platform_kafka_v1 | 교통안전인프라 플랫폼 Producer | 통합교통관제시스템 Consumer | 4 |
| SC13 | 78 | i2x2ut_kafka_v1 | 통합교통관제시스템 Consumer | I2X Producer 및 offset 관측 | 6 |
| SC34 | 79 | ut2i2x_kafka_v1 | I2X 연계장치 Producer | 통합교통관제시스템 Consumer | 6 |

설계 ID, 등록 ID, case, 상세 testName, 반복 회차는 다른 식별자다. 정보별 `test_<stream>_normal`은 10회 이상 교환, `test_<stream>_period`는 2개 이상 표본의 별도 추가 주기 검사다. 총 20항목은 제4부의 독립 시험명이 20개라는 뜻이 아니다.

**정보연계 횟수:** 시험 환경설정의 **정보교환 반복 횟수**(`repetitions`)에서 지정한다. 기본 10회, 현재 입력 범위 10~1000회다. 예를 들어 20으로 설정하면 선택한 각 정상 정보연계 항목을 20회씩 수행하고, 진행 회차와 결과의 계획 횟수에도 20을 표시한다. 실행 횟수가 10으로 고정된 구현은 아니다. 추가 주기 확인의 `period_samples`와 구분한다.

## 시험 전 합의와 입력

**2026-09-25 사용자 결정:** 토픽을 코드에 고정하지 않는다. 실제 시험 전에 정보별 토픽을 합의하고 시험환경 입력값으로 사용한다. 화면 토픽 입력은 비어 있으며, 빈 값·중복 토픽은 실행 오류다. 엑셀 토픽명은 참고 예시다. `registration/*.example.json`은 개발용 설정 예시이고 실제 운영값이 아니다.

- `bootstrap_servers`: 브로커 목록. 대상 시스템과 Broker의 역할을 분리한다.
- `group_id`: 소비 대상이면 대상의 실제 Consumer Group ID, 발행 대상이면 시험 Consumer의 별도 Group ID. 다른 활동이 섞이지 않는 시험용 Group/토픽을 사전 준비한다.
- `topic_open`, `topic_platform`, `topic_facility`, `topic_map`, `topic_i2x`: 선택한 정보별 합의 토픽. 시험기는 토픽을 자동 생성/삭제하지 않는다.
- `facility_fixture`: 시설 전용 정보의 합의 JSON 준비자료. 이 파일 형식 자체를 표준의 의무로 제시하지 않는다. 개발 검증은 MAP 예시 객체를 전송 자료로 명시적으로 선택했다. 두 토픽에 동일 업무 의미가 있다고 확정하지 않는다.
- `open_encoding`: `json` 또는 `base64-json`. 후자는 UTF-8 JSON 전체의 Base64 ASCII value라는 개발 포장이다. 자동 추정/자동 변환으로 불일치를 숨기지 않는다.
- 정보별 `period_*` 기본값은 오픈데이터 60초, 플랫폼 상태 600초, 시설/MAP 60초, I2X 상태 10초다. 허용오차 기본 2초는 프로젝트 시험환경값이다. 다른 주기로 실행하면 결과에 `defaultTiming=false`를 남긴다.
- `auto_offset_reset`: earliest/latest Consumer 설정. **실제 시험 Consumer는 과거 자료가 새 시험을 통과시키지 않도록 실행 시작의 high watermark를 명시적으로 할당한다.** 이 경계가 시작 정책보다 우선한다. 대상 Consumer의 최초 정책을 직접 관측/입증하는 시험은 아니다.
- `security_file`: 선택적인 librdkafka TLS/SASL 설정 JSON 경로. 허용 키는 `runtime/kafka_io.py`에 명시했다. 비밀값은 UI 설정이나 결과에 복사하지 않는다. 현재 개발 검증은 PLAINTEXT이며 TLS/SASL 상호운용 완료를 뜻하지 않는다.

## 데이터 기준과 남은 의미

표의 자료형·명확한 범위·M/O를 우선한다. 그룹 M/O가 `-`이면 그룹을 무조건 요구하지 않고, 존재하는 그룹 안의 M/O를 검사한다. **weatherData는 표에서 M이므로 필수**다. refPosition 그룹은 M이지만 long/lat의 M/O 공란은 임의 필수화하지 않으며 제공되었을 때만 타입·범위를 검사한다. 알려진 필드가 전혀 없는 자료는 개발 시험 자료 준비 오류다.

| 자료/차이 | 적용한 개발 기준·한계 |
|---|---|
| 오픈데이터 | 표의 수치 범위를 적용. 예시의 air-pressure=1008.5는 표의 1500..11000 밖이므로 준비자료는 10085를 사용했다. 수신 자료를 자동 배율 변환하지 않는다. road condition은 표의 0..1 범위를 채택하고 같은 표 설명의 snow=2/ice=3 차이를 남긴다. |
| 오픈데이터 JSON 키 | 표의 공백·분리된 표현은 예시의 `installationStatus`, `trafficCount`, `forwardAxialStiffness`, `transverseAxialStiffness`, `roadCondition`, `waterLevel`, `salt-concentration`, `freezing-temp`에 대응. `transmisson` 오탈자는 예시의 `transmission`으로 채택했다. 수신시 두 키를 자동 합치지 않는다. |
| I2X 상태 | ID와 위치는 표의 STRING. 숫자 좌표 예시를 자동 문자열화하지 않는다. 잘못된 예시 배열은 위치 객체로 채택했다. ID에 붙은 숫자 범위와 SDateTime 형식은 추가 의미를 만들지 않는다. |
| 플랫폼 상태 | SERVER/KAFKA의 STAT/STTUS를 구별. 데이터허브는 표의 STTUS를 사용하고 중복 DATAMANAGER_STTUS 중 서비스브로커 항목은 `DATASERVICEBROKER_STTUS`로 명시했다. 예시의 STAT 키와 차이는 보존한다. 0/1 범위만 검사하고 한/영 연결 상태 설명의 모순을 임의 해소하지 않는다. |
| MAP | messageId=18, value 및 주요 교차로/위치/laneSet 구조를 검사하는 **JSON 예시 profile**. 검사한 필드를 매회 표시한다. 모든 선택 ASN.1 필드·lane 연결 의미·BER/UPER 변환·ITSK-00144-2 전체 적합성을 완료로 주장하지 않는다. |
| 시설 전용 | 합의 JSON의 UTF-8·객체 및 실제 전달·offset 범위. 업무 필드의 필수성·의미·두 토픽 분담은 미확인이다. JSON 객체라는 이유로 시설 표준 전체 적합으로 표현하지 않는다. |
| 주기 | 엑셀 60/600/60/10초와 상세 표의 발생시/60초 차이를 보존. 엑셀 값을 기본 개발 조건으로 사용한다. |

## 제4부 적용 범위

§3.1.1 원문은 시험 Consumer–대상 Broker이고 §3.2.1은 대상 Consumer–시험 Broker다. 이번 SUT는 업무 Producer/Consumer이며 Broker 제품 시험은 별도다. 소비 대상은 발행 ACK와 대상 Group의 저장 offset 진전을 각각 관측한다. 발행 대상은 실제 수신 자료 검사 후 명시적인 offset+1 commit과 브로커 재조회를 수행한다. 처리 완료 후 commit 경계는 prj22 `KafkaInterfaceAdapter_commitOffsets`의 방식과 동일하게 적용했다. Broker ACK나 commit 진전을 업무 처리 완료의 직접 증거로 확대하지 않는다.

heartbeat=3000ms/session timeout=10000ms를 Consumer 설정에 넣는다. 시험 Consumer의 명시 partition assignment 경로에서는 group join/rebalance/heartbeat 행위의 적합성을 별도로 입증하지 않는다. 재연결 복구·브로커 저장소 내구성·클러스터 장애·대상 내부 처리·원천 사건부터 전달까지 시간은 현재 판정 범위가 아니다. 전체 제4부 완료로 집계하지 않는다.

## 빌드·실행

`scenarioengine/project/vs2022/ScenarioEngineTest.vcxproj`의 Debug/x64 빌드에 KafkaConformance를 연결했다. 기존 실행 모듈을 수정하지 않고 category `ITSK-00143-KAFKA-V1`를 추가했다. 엔진 파일 옆 `kafka-runtime.json`의 `python`은 confluent-kafka 2.8.0 설치 Python, `module`은 이 모듈의 절대 경로다. `tools/Prepare-Runtime.ps1`은 새 개발 실행 폴더를 준비한다. 운영 설치 패키지를 변경하지 않는다.

```powershell
& .\kafkaconformance\tools\Prepare-Runtime.ps1 -Destination C:\Temp\g4-kafka-runtime
```

플랫폼 등록은 `registration/*.tsb`를 **제목 `scenario`인 첨부 묶음**으로 추가해야 한다. 일반 `첨부파일` 제목만 사용하면 서버 INITIALIZE에 testScenario=null이 전달된다. 이번 76~79는 수정 후 실제 초기화를 확인했다.

1. 사전 합의한 시험용 토픽을 브로커에 만들고 접속값·Group·포장·주기·자료를 준비한다.
2. 자체 시험을 열어 Agent 접속 URL을 개발 실행본에 전달한다. 작업 폴더는 실행마다 새로 만든다.
3. 독립 상대는 `emulator/sut.py --config <설정.json> --work <엔진 작업폴더> --role producer|consumer`로 실행한다. Consumer 대상에는 consumer 상대, Producer 대상에는 producer 상대를 사용한다.
4. 화면에 같은 시험환경을 입력하고 항목을 선택하여 시작한다. 현재 화면 렌더러가 초기 value를 비워 표시하므로 예시 JSON의 수치를 명시적으로 입력한다.
5. 진행 화면과 저장 보고서를 대조한다. 상대·브로커·엔진을 종료할 때 자신이 생성한 PID만 종료한다.

`kafka-run.json`과 `peer-ready.json`은 개발 상대의 자료 준비를 맞추는 로컬 계측이다. Kafka 메시지에 가상 테스트 헤더/ACK 토픽을 추가하지 않는다. 실제 SUT는 이 제어 파일을 구현할 필요가 없다. 독립 상대는 시험기/필드검사 모듈을 import하지 않으며, 수신 준비자료와 자기 commit 재조회를 별도로 기록한다.

시험 브로커 설정은 `broker/server.properties`이며 실제 개발은 WSL Apache Kafka 3.9.1 단일 KRaft 노드, 전용 29092/29093 포트를 사용했다. WSL IP는 재기동 시 바뀔 수 있으므로 `advertised.listeners`와 Windows의 bootstrap을 함께 맞춘다. 이번 환경의 172.21.222.91은 운영값이 아니다.

## 결과와 검증 도구

- `kafka-results/<실행>/records.jsonl`: 실제 원문 base64·hash, 토픽/partition/offset, 회차·방향/관측·실제 발송 주체. Kafka wire 패킷 캡처가 아니라 adapter 관측 자료다.
- `events.jsonl`: 엔진 전송 순서의 상태·한국어 안내·데이터. 인증값을 가린 표시와 원문을 구분하며 긴 표시는 전부 번호를 붙여 분할한다.
- `result.json`: 성공/실패/중지/미실행·미선택, 완료 회차, 시간 조건과 관측 한계.
- `kafka-delivery.json`: 호스트 알림 큐의 전달·미처리·폐기·오류. 서버 수신 ACK와 구분한다.
- `tests/verify.py`: 실제 브로커·독립 상대 양측, 오류·경계·Base64·긴 자료·중지 검증. 기본 주기는 3초로 단축하므로 정식 시간 조건으로 합산하지 않는다.
- `tools/review_platform.py`: 원문·독립 상대·native 상태 ACK·진행 화면·저장 보고서를 비교한다. 화면/보고서 JSON은 UI에서 읽어 `platform.json`/`report.json`으로 보존한다. 보고서가 동일 자료를 여러 절에 반복 표시하는 것도 대조한다.

상세시험은 START→SUCCESS/FAIL/STOPPED, NOT_RUN은 상태 알림을 만들지 않는다. MainScenario 최종 결과 뒤 FINISH는 한 번이다. COMPLETE는 보내지 않는다. 사후 파일 제출을 필수 완료 조건으로 요구하지 않는다.

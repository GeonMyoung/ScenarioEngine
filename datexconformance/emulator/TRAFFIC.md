# MAP·RSA·TIM 시험 대상 에뮬레이터

> **현재 v8 판정:** ScenarioEngine에는 COMPLETE와 사후 증적 제출 상태가 없다. 정상 절차를 마친 시험은 SUCCESS다. 아래의 과거 EVIDENCE_PENDING·사후 검토 설명은 당시 이력이며 현재 실행 조건이 아니다. 명시적 부적합·통신 오류·사용자 중지는 성공으로 바꾸지 않는다.
BSM 에뮬레이터의 세션·재전송·거부·취소 처리를 재사용하는 `traffic` 프로파일이다. 기본 BSM 실행 방식은 유지한다.

| 시험 대상 | 플랫폼 | 시험기 case | SUT 역할 | 기본 포트 |
|---|---|---|---|---:|
| UT 센터 | [44](https://106.250.189.37:8443/test/scenario/44) | `rseClient2center_v2` | Server / MAP·RSA·TIM 제공 | 55163 |
| RSE | [45](https://106.250.189.37:8443/test/scenario/45) | `centerServer2rse_v2` | Client / MAP·RSA·TIM 요청·수신 | 55164 |

EAM은 `1.0.15784.1.0.1`, 업무 컨테이너는 CommTxPDU, DATEX는 BER, payload는 UPER다. PSID/MessageFrame은 MAP 82056/18, RSA 82053/27, TIM 82054/31이다.

## 실행

플랫폼의 자체 시험을 열고 해당 회차의 Agent URL로 `datexconformance/tools/Start-PlatformEngine.ps1`을 실행한다.

UT 센터를 시험 대상으로 할 때는 아래 SUT를 먼저 실행한다. 에뮬레이터는 구독을 수용하고 세 정보를 하나의 CommTxPDU 목록으로 제공한다. 시험기는 MAP·RSA·TIM을 각각 판정한다.

```powershell
.\datexconformance\emulator\Start-TrafficSut.ps1 -Role Center -Sessions 10
```

플랫폼 입력은 `traffic-tester-center.example.json`을 따른다. 정상 3개를 포함한 전체 항목은 10개다. H/R 60/40초, 비정상 세션 유지 300초, 취소 전 120초, 구독 요청 주기 60초로 검증했다.

RSE를 시험 대상으로 할 때는 플랫폼에서 먼저 시험을 시작해 55164 포트 수신 대기를 확인한 다음 SUT를 실행한다. 정상 3개·구독 재전송·6종 오류 거부는 10개 세션이다.

```powershell
.\datexconformance\emulator\Start-TrafficSut.ps1 -Role Rse -Request single -Sessions 10
```

정상 세션·로그인 재전송 2개는 별도 회차에서 선택한다.

```powershell
.\datexconformance\emulator\Start-TrafficSut.ps1 -Role Rse -Request session -Sessions 2
```

RSE 설정은 `traffic-tester-rse.example.json`을 따른다. 정상 수신은 실제 메시지의 PSID·종류·payload를 해석하며 시험 이름으로 응답을 선택하지 않는다. 정보요청 시험의 내부 처리 증거는 `payload_processed`와 `application_processed` 이벤트에 기록한다.

`-Message map|rsa|tim`으로 지원 메시지를 하나로 제한할 수 있으며 기본은 `all`이다. `-ConfigurationFile`, `-LogFile`, `-DurationSeconds` 및 기존 fault 옵션을 지원한다. 표준 시간 조건을 줄인 로컬 기능 검증을 정식 시간 조건 충족으로 표시하지 않는다.

## 구현 및 검증

- 실행파일: `datexconformance/project/vs2022/Debug64/DatexBsmEmulator.exe`. 기존 실행파일에 명시적인 `--profile traffic`을 전달하며 별도 중복 세션 구현을 만들지 않았다.
- 제공 SUT와 시험기 Server는 여러 세션 사이에도 수신 대기 소켓을 유지한다. 즉시 재접속을 임의 대기시간으로 늦추지 않는다.
- CommTxPDU의 PSID와 실제 MessageFrame을 확인하고, 선택적 `payloadType`이 있으면 그 값도 비교한다.
- MAP/TIM 결과 변환은 개선판 전용 코드에서 ASN.1 필드 값과 포인터를 올바르게 구별한다. 기존 모듈의 변환 소스는 변경하지 않았다.
- 로컬 확인: `verify_traffic_emulator.py` 32개 검사, `verify_traffic_session_sequence.py` 연속 10개 검사, `DatexConformanceTests.exe --traffic-payload` 필드 보존·잘못된 PSID/종류 거부.
- [플랫폼 실행 및 증적 대조 결과](../../doc/gyeong4/2026-v2.1/traffic-platform-verification-20260923.md)를 따른다. 추가 증거가 필요한 자동 결과는 보존한다.

현재 범위는 DATEX 연계와 선택 메시지의 송수신·디코딩·처리 검증이다. 실제 도로 상황에 맞는 내용의 정확성, TIM 제한속도·차로변경 등 모든 업무 의미 프로파일, 실장비 상호운용을 전부 검증한 것으로 해석하지 않는다.

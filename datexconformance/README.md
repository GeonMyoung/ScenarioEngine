# 신규 DATEX 시험 모듈

**수동 시험 사용자:** [사용 안내서와 실행 묶음](../doc/gyeong4/2026-v2.1/manual-release-20260924.md)을 먼저 확인한다. PDF·HTML, 14개 시험 설정, 검증된 엔진·대상 에뮬레이터 및 실행·종료 런처를 함께 제공한다.

기존 `iso14827testhelper`를 보존하고 확정된 개선 정책을 별도로 구현한다. 신규 category는 **`ITSK-00143-DATEX-V2`**다. 기존 category와 case는 기존 실행 경로를 유지한다.

## 신규 case

| case | 시험기 ISO 14827 역할 | 시험대상·메시지 |
|---|---|---|
| `centerClient2rse_v2` | Client | RSE의 BSM 제공 |
| `rseServer2center_v2` | Server | 센터의 BSM 요청 |
| `rseClient2center_v2` | Client | 센터의 MAP/RSA/TIM 제공 |
| `centerServer2rse_v2` | Server | RSE의 MAP/RSA/TIM 요청 |
| `signalserverServer2center_v2` | Server | 센터의 신호정보 SPaT/TLSM 요청 |
| `centerClient2signalserver_v2` | Client | 신호정보 수집서버의 SPaT/TLSM 제공 |
| `vehicleServer2center_v2` | Server | 센터의 자율주행차량 BSM 요청 |
| `centerClient2vehicle_v2` | Client | 자율주행차량의 BSM 제공 |
| `vehicleClient2center_v2` | Client | 센터의 자율주행차량 SPaT/RSA/TIM 제공 |
| `centerServer2vehicle_v2` | Server | 자율주행차량의 SPaT/RSA/TIM 요청 |
| `vehicleServer2rse_v2` | Server | RSE의 차량 BSM 요청 |
| `vehicleClient2rse_v2` | Client | RSE의 SPaT/MAP/RSA/TIM 제공 |
| `rseClient2vehicle_v2` | Client | 자율주행차량의 RSE 연계 BSM 제공 |
| `rseServer2vehicle_v2` | Server | 자율주행차량의 RSE 연계 SPaT/MAP/RSA/TIM 요청 |

등록용 TSB, 설정 예제, 역할 목록은 `registration/`에 있다. **2026-09-23 BSM 개선판 2개를 등록했다: RSE 정보제공 ID 42, UT 센터 정보요청 ID 43.** 에뮬레이터 SUT로 실제 플랫폼에서 18개 항목을 확인했다. [실행 결과와 남은 플랫폼 사항](../doc/gyeong4/2026-v2.1/bsm-platform-verification-20260923.md)을 따른다. MAP·RSA·TIM 2개도 아래와 같이 추가 등록했다. 기존 등록·기본 선택·설치본은 변경하지 않았다.

플랫폼에서 해당 시험의 ‘자체 시험 수행’을 연 다음, ‘Agent 접속 URL 복사’의 주소로 `tools/Start-PlatformEngine.ps1 -AgentUrl "wss://..."`를 실행한다. 이 스크립트는 로컬 개선 엔진을 별도 작업 폴더에서 실행한다. MSI/전역 실행 연결은 변경하지 않으며, 시험 후 출력된 PID를 종료한다.

**BSM 시험 대상 에뮬레이터:** [독립 실행 안내](emulator/README.md)의 센터/RSE 두 역할을 사용한다. 2026-09-23 검증 결과는 [BSM 에뮬레이터 확인·검증](../doc/gyeong4/2026-v2.1/bsm-emulator-verification-20260923.md)에 있다. 에뮬레이터를 SUT로 사용하는 개발 검증과 실제 장비 검증을 구분한다.

**MAP·RSA·TIM:** UT 센터 제공시험 ID **44**, RSE 요청시험 ID **45**를 등록하고 22개 항목을 플랫폼에서 검증했다. [실행 안내](emulator/TRAFFIC.md)와 [결과·범위](../doc/gyeong4/2026-v2.1/traffic-platform-verification-20260923.md)를 따른다.

**차량·신호정보:** SC03·SC22·SC04·SC23·SC05를 **ID 46~50**으로 추가 등록하고 55개 항목을 확인했다. [실행 안내](emulator/VEHICLE-SIGNAL.md)와 [결과·계약 조건](../doc/gyeong4/2026-v2.1/remaining-datex-verification-20260923.md)을 따른다. 이 9개·95항목에 이어 F2F 4개를 **ID 52~55**로 등록하고 48항목을 검증했다. 이후 SC26 신호정보 수집서버 제공시험을 **ID 56**으로 등록하고 9항목을 검증하여, 현재 채택 DATEX 목록은 **14개 시나리오·152항목**이다. [양측 구성 현황](../doc/gyeong4/2026-v2.1/datex-scenario-status-20260924.md)과 [신호정보 수집서버 실행 안내](emulator/SIGNAL-SERVER.md)를 따른다. [F2F 실행 안내](emulator/F2F.md)와 [완료 결과](../doc/gyeong4/2026-v2.1/f2f-platform-verification-20260923.md)를 따른다.

## 빌드와 로컬 검증

저장소 루트의 PowerShell에서 실행한다. Visual Studio 2022 C++ 도구와 Python 3이 필요하다.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\test-datex-new.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\bootstrap-build.ps1 -Target Engine -Configuration Debug
```

- 신규 프로젝트: `datexconformance/project/vs2022/DatexConformance.vcxproj`
- 테스트 프로젝트: `datexconformance/project/vs2022/DatexConformanceTests.vcxproj`
- 테스트 실행파일: `datexconformance/project/vs2022/Debug64/DatexConformanceTests.exe`
- 엔진 실행파일: `scenarioengine/project/vs2022/DebugTest64/ScenarioEngineTest.exe`
- 신규 C/C++ 파일은 UTF-8 BOM을 사용한다. 신규 프로젝트는 BOM 없는 기존 SDK 헤더를 CP949로 읽고 실행 문자열은 UTF-8로 만든다. 기존 파일 인코딩을 바꾸지 않으며 프로젝트별 중간 빌드 폴더도 분리한다.
- 로컬 시험은 임시 loopback 포트만 사용한다. 설정·시간 경계·재전송 변조·오류 사유·취소 후 발행·SDK 메시지 연결을 확인한다. 축소한 시험시간의 로컬 결과를 실장비의 5분 유지 적합성 결과로 사용하지 않는다.
- `tools/check_legacy.py`는 기존 파일 해시가 보존됐는지 확인한다. 새 category 연결을 추가한 엔진 진입점·프로젝트 파일은 이 기존 모듈 해시 목록과 구분한다.

## 실행 방식

1. 신규 TSB로 엔진을 초기화하면 해당 case의 `UI_CONFIGURE`가 제공된다.
2. 주소·도메인·테스트 계정과 시험 항목을 설정하고 SETUP → START 순서로 실행한다. 같은 모듈에서 재실행할 때도 SETUP부터 수행한다.
3. 세부 시험은 서로 독립된 TCP 세션을 사용한다. 요청 SUT(Client)는 각 세부 시험의 종료 후 다시 연결하도록 준비한다. 첫 번째 단계부터 모든 항목을 무조건 선택하기보다 필요한 항목을 선택해 실행한다.
4. STOP은 대기 중 통신·검증을 중단하고 해당 실행의 소켓·작업 스레드를 정리한다.

지원 연결은 Windows x64, TCP/IPv4, DATEX BER이다. 기존 ASN.1 코덱·메시지 구조·JSON 스키마를 재사용하되 TCP 세션·수신 기록·시험 상태는 신규 모듈 안에 둔다. 기존 라이브러리의 전역 hook이나 기본 타이머를 바꾸지 않는다. UDP·TLS 전송·능동 접속 ISO Server를 새로 지원한 것으로 표시하지 않는다.

## 설정과 판정

- H/R: 기본 60초/40초. 양수 환경 입력 우선. 실제 SUT Client의 Login에 들어온 H/R은 기대 설정과 비교한다.
- 비정상 세션: 정상 FrED 기본 300초 유지 후 송신 중단. H 이상·H+R 이내 대상 TCP 종료를 관측하면 시험 기준상 적합이다. 조기 종료·추가 메시지는 부적합, TCP 종료 미관측은 관측 사실을 기록하고 정상 관찰 절차 완료로 성공 처리한다. 관측 시각과 경과시간을 결과에 기록한다.
- 잘못된 로그인: 무효 비밀번호 입력 또는 정상 값과 다른 자동 구성값을 사용하고 정확한 Login Reject를 확인한다. 중복 로그인은 두 번째 응답을 기다리는 동안 첫 세션의 FrED를 유지하고 거부 후 생존도 다시 확인한다.
- 오류 Subscription: 잘못된 OID에 대한 사유 검사. 오류 Publication: prj22 기준 6종 자극·구독/발행 식별자·사유·후속 FrED 검사.
- 재전송: 원본 패킷번호·타임스탬프·내용을 비교한다. 동일 재전송 시 타임스탬프를 새로 만들지 않는다.
- 구독 취소: 기본 120초/설정 시간 수신, 정상 Publication 최소 2회와 비교 가능한 주기 간격 확인. 정상 주기 범위는 요청 주기 ±10%. 초기 발행 구간과 동일 재전송을 별도로 취급한다.
- 취소 요청 후 해당 구독의 내용 처리는 생략한다. 수용 응답 이후 요청 주기 1회 동안 실제 수신을 관찰한다. 수용 전에 관측한 패킷도 재전송 비교 증거로 보관하며 새로운 발행과 구분한다. 취소 응답·FrED·다른 제어 메시지는 정상 처리한다.
- MAP: 신규 선택표의 PSID는 82056, MessageFrame 종류는 18이며 실제 payload를 디코딩한다. 기존 표는 변경하지 않는다.

## 결과와 상태 계약

현재 DATEX는 ScenarioEngine의 상태 계약을 따른다. 정상 상세시험은 START → SUCCESS, 전체 시험은 START → SUCCESS → FINISH로 종료한다. prj22의 COMPLETE와 사후 증적 제출 절차는 적용하지 않는다.

- 수신 데이터의 디코딩·프로토콜 조건과 상관관계 검사는 유지한다. 플랫폼의 명시적인 부적합 회신은 FAIL로 반영한다.
- 정상 절차 완료 후 플랫폼 판정 응답 미확인은 그 사실을 기록하고 SUCCESS로 종료한다. 미회신을 적합 회신으로 꾸미지 않으며 결과 observations.platformValidation에 not_received로 구분한다.
- 비정상 세션은 정상 유지·송신 중단·관찰 절차를 완료하면 종료 관측 여부를 보존하고 SUCCESS로 처리한다. 조기 종료·추가 메시지는 FAIL로 유지한다.
- 통신·디코딩 실패와 사용자 중지는 정상 완료로 바꾸지 않는다. 모든 메시지·오류·시간 관측을 기존 결과 JSON/JSONL에 보관한다.
- tools/review_evidence.py 및 관련 테스트는 v1~v7 과거 결과를 위한 이력 도구다. 현재 사용자 실행·판정 절차에는 사용하지 않는다.

## 구현과 검증 경계

- C2C/업무 payload 코덱·기존 JSON 스키마는 기존 라이브러리에서 재사용한다. 기존 JSON 루트가 없던 TLSM은 KOR 구조를 직접 보존하는 신규 변환을 사용한다.
- `DatexMapConvert.c`는 기존 MAP/TIM 변환 함수의 필요한 부분만 신규 모듈에 분리한 것이다. 선할당 목록을 교체하기 전에 해제하고 비트 수의 바이트 환산을 보정한다. 기존 변환 소스는 보존했다.
- `DatexSamples.h`는 기존 UPER 샘플을 변경 없이 가져온 자료이며 원본·길이·해시는 `fixture-provenance.json`에 있다. TIM 핵심 통행지시 변형은 해당 샘플에서 별도로 생성·검사한다. 외부 DATEX envelope는 신규 경로에서 구성한다. 디코딩 통과만으로 모든 업무 필드의 의미 적합성이 증명되는 것은 아니다.
- 현재 채택 14개 case의 플랫폼 등록·실행과 대상 로그 대조를 완료했다. TLSM은 기존 형식을 채택했고 TIM 국내 확장은 내부 ASN.1 디코딩과 손상 입력 거부를 확인했다. 업무 판단을 추가 완료 조건으로 두지 않는다. 실장비 상호운용·웹 최종 보고서 반영·MSI 배포는 별도 단계다. SC26은 기존 SC05와 같은 신호정보 구간의 반대편 시험으로 완성했다.
- `DatexSpatConvert.c`는 기존 SPaT 변환에서 확인한 생성 객체 교체 누수를 신규 경로에만 보완한 소스다. 영향받은 로컬 검사와 최종 플랫폼 양방향 실행에서 JSON 결과 보존을 확인했다.

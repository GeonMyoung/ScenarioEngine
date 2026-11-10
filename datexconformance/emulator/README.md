# 경4 BSM DATEX 시험대상 에뮬레이터

> **현재 v8 판정:** ScenarioEngine에는 COMPLETE와 사후 증적 제출 상태가 없다. 정상 절차를 마친 시험은 SUCCESS다. 아래의 과거 EVIDENCE_PENDING·사후 검토 설명은 당시 이력이며 현재 실행 조건이 아니다. 명시적 부적합·통신 오류·사용자 중지는 성공으로 바꾸지 않는다.
실제 UT 센터·RSE 대신 **시험 대상 시스템(SUT)** 역할로 동작한다. `datexconformance`의 변경 없는 BER 전송·BSM 샘플·CommRxPDU/UPER 코덱을 재사용하며, 접속·로그인·구독·제공·수신 처리는 독립 실행 프로세스에서 수행한다. 기존 시험 및 기존 에뮬레이터는 수정하지 않는다.

| 검증할 시험 | 실제 실행되는 시험기 | 이 도구의 SUT 역할 |
|---|---|---|
| **RSE 대상 UT 센터 연계 BSM 정보제공시험** / SC18 | `centerClient2rse_v2` / ISO Client | `Rse`: TCP 수신 대기, 로그인 수용, BSM 제공, ACK·구독 취소 처리 |
| **UT 센터 대상 RSE 연계 BSM 정보요청시험** / SC01 | `rseServer2center_v2` / ISO Server | `Center`: TCP 접속, 로그인·BSM 구독, 수신 BSM 디코딩·처리 기록, 오류 거부 |

기본 BSM 프로파일: **EAM `1.0.15784.1.0.2`, CommRxPDU, PSID 82050, MessageFrame ID 20**, DATEX BER / payload UPER. 단일/continuous periodic 구독과 현재 BSM 시험 흐름을 대상으로 한다. MAP·RSA·TIM은 별도 `traffic` 프로파일로 확장했으며 [전용 실행 안내](TRAFFIC.md)를 따른다.

2026-09-23 플랫폼 연속 실행에서 확인한 로그인 거부 직후 재접속 문제를 수정했다. RSE는 여러 세션을 실행하는 동안 동일 수신 대기 소켓을 유지한다. 플랫폼 등록 ID 42·43의 실행 결과와 증적은 [플랫폼 검증 결과](../../doc/gyeong4/2026-v2.1/bsm-platform-verification-20260923.md)를 따른다. 즉시 재접속 회귀 확인은 `verify_bsm_session_sequence.py --exe <실행파일> --output <새 결과 폴더>`로 수행한다.

## 1. 빌드

기존 작업 폴더에서 Visual Studio 2022 C++ 도구와 저장소 SDK 의존성을 사용한다.

```powershell
$vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
$msbuild = @(& $vswhere -latest -version '[17.0,18.0)' -products '*' -requires Microsoft.Component.MSBuild -find 'MSBuild\Current\Bin\MSBuild.exe') | Select-Object -First 1
& $msbuild datexconformance\project\vs2022\DatexBsmEmulator.vcxproj /t:Build /p:Configuration=Debug /p:Platform=x64 /m:4 /nr:false
```

실행 파일: `datexconformance/project/vs2022/Debug64/DatexBsmEmulator.exe`. 솔루션 전체를 바꾸지 않고 별도 프로젝트로 빌드한다.

## 2. RSE를 시험 대상으로 모의

먼저 에뮬레이터를 실행한다.

```powershell
.\datexconformance\emulator\Start-BsmSut.ps1 -Role Rse
```

`LISTENING`이 표시되면 시험기에서 **RSE 대상 UT 센터 연계 BSM 정보제공시험**을 시작한다. 기본 대기 포트는 **55161**, SUT Domain은 **EMULATOR**, 시험기 Domain은 **TESTER**다. 시험기는 `127.0.0.1:55161`로 연결한다. 예제 계정은 로컬 검증용 `bsm-local / local-bsm-check`이며 양쪽 설정을 같게 맞춘다.

다른 PC에 놓는 경우 실제 에뮬레이터 PC 주소를 시험기에 설정한다. 실행 모듈의 listener는 IPv4 수신 대기이며 이번 검증 통신은 모두 loopback만 사용했다.

## 3. UT 센터를 시험 대상으로 모의

먼저 시험기의 **UT 센터 대상 RSE 연계 BSM 정보요청시험**을 시작하여 포트 **55162**에서 기다리게 한다. 이후 다음 명령을 실행한다.

```powershell
.\datexconformance\emulator\Start-BsmSut.ps1 -Role Center
```

에뮬레이터가 `127.0.0.1:55162`에 접속해 Login과 BSM Subscription을 전송한다. 정상 BSM은 `bsm_processed`와 `application_processed` 이벤트로 기록한다. 이 로그는 실제 UT 센터 로그가 아니라 **에뮬레이터 SUT의 처리 증거**다.

세션 또는 Login 재전송 시험만 수행할 경우 BSM 구독을 보내지 않도록 `-Request session`을 사용한다. 정상 BSM·구독 재전송·Publication 오류 시험에는 기본 `single`을 사용한다. 개선판 세부 시험은 독립 TCP 세션이므로 같은 설정으로 여러 세션을 대기하려면 `-Sessions N`을 사용하며 서로 다른 동작 프로파일은 나눠 실행한다.

## 4. 설정·종료·로그

- 네 개의 예제 JSON은 에뮬레이터 두 역할과 대응 시험기의 주소·포트·Domain·계정을 맞춘 구성이다. 실제 플랫폼 설정 화면에도 같은 값을 입력한다.
- 기본 시간은 H/R=60/40초다. RSE 역할은 유효한 Login의 H/R을 적용하고 로그에 남긴다. 주기 구독은 수신한 요청 주기를 따른다.
- 예제의 `test_normal_bsm`은 공통 설정 파서의 활성 검사 표시다. **에뮬레이터의 응답은 수신한 PDU·계정·구독·식별자·BSM 내용으로 결정하며 시험 이름에 맞춰 성공 응답을 내보내지 않는다.**
- `-ConfigurationFile`로 별도 설정, `-LogFile`로 결과 위치, `-DurationSeconds`로 세션 상한을 지정한다. 같은 로그 파일을 덮어쓰지 않는다.
- 정상 Logout/Terminate로 세션을 종료한다. Ctrl+C는 종료 요청을 처리한다. 상태·송수신을 증적 파일에 기록하는 콘솔 도구이며 별도 GUI는 만들지 않았다.
- 기본 증적 위치는 저장소의 `.local/bsm-sut-evidence/`다. Login 암호를 마스킹한 BER 표현, 송수신 패킷 번호, 처리 사건, BSM 원시·디코딩 JSON을 기록한다.

## 5. 오류 재현

정상 모드는 `-Fault none`이다. 아래는 시험기의 실패 판정을 검증하기 위한 의도적 비정상 동작이며 통신 규격의 정상 동작으로 사용하지 않는다.

| 옵션 | 역할·효과 |
|---|---|
| `wrong-reject` | 잘못된 로그인/구독 또는 Publication에 다른 거부 사유 전송 |
| `changed-retry` | 재전송 시 동일 패킷 대신 새 번호·시각의 패킷 송신 |
| `bad-content` | RSE가 잘못된 BSM EAM 내용을 제공 |
| `after-cancel` | RSE가 취소 수용 이후 새 Publication을 송신 |
| `slow-period` | RSE가 요청 주기의 두 배 간격으로 발행 |

## 6. 독립 프로세스 검증

```powershell
python -X utf8 .\datexconformance\emulator\verify_bsm_emulator.py `
  --exe .\datexconformance\project\vs2022\Debug64\DatexBsmEmulator.exe `
  --output .\.local\bsm-verification-NEW

python -X utf8 .\datexconformance\emulator\verify_bsm_emulator.py `
  --exe .\datexconformance\project\vs2022\Debug64\DatexBsmEmulator.exe `
  --output .\.local\bsm-policy-verification-NEW --policy-times
```

첫 명령은 짧은 시간값으로 두 SUT 역할의 정상·세션·재전송·구독 취소·6종 오류 및 의도적 실패를 확인한다. 두 번째는 취소 전 **120초**, 정상 FrED **300초**, H/R **60/40초**의 프로젝트 기본값을 확인한다. 이미 통과한 항목은 변경·새 우려가 없으면 반복할 필요 없다.

`--mode tester`는 같은 실행 파일에 포함된 **로컬 검증 드라이버**이며 `datex::run`을 호출한다. 웹 플랫폼·SDK의 비동기 VALIDATE 서비스를 대체하지 않는다. 실제 플랫폼에서는 기존 개선판 시험 엔진이 시험기가 되고 이 도구는 `--mode emulator`로만 사용한다.

검증 스크립트의 `PASS`는 기대 동작과 증거가 일치했다는 뜻이다. 의도적 오류에서는 시험기가 해당 이유로 `FAIL`해야 검증 성공이다. 정상 센터 수신과 무수신 종료의 시험 결과는 `EVIDENCE_PENDING`을 보존하고, 에뮬레이터 처리·종료 로그의 대응을 별도로 확인한다. 자동 통과 기준을 완화하지 않는다.

## 7. 경계

이번 개발 검증의 SUT는 에뮬레이터다. 실제 UT 센터·RSE와의 상호운용은 사용자 결정대로 전체 개발 이후 수행한다. 프로토콜/BSM 코덱을 시험기와 공유하므로 동일 결함을 놓칠 수 있으며 외부 독립 구현과의 상호운용 증거를 대신하지 않는다. 운영 플랫폼 등록·판정 규칙 연결은 다음 단계다.

현재 센터 SUT는 단일 BSM 구독 번호 1·정상 첫 발행 번호 1의 시험 프로파일을 사용한다. RSE는 단일 또는 continuous periodic BSM 구독 한 건을 처리한다. 일반 다중 구독 서버, 임의 메시지 코덱, UDP/TLS, 능동 접속 ISO Server까지 구현한 것으로 해석하지 않는다. 여러 세부 시험은 `-Sessions`의 독립 순차 세션으로 처리한다.

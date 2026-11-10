# MQTT/V2N 간편실행기

현재 권장 실행본은 **v6 / MSI 1.2.6**이다. Username·Password를 직접 입력하며 사용자 지시에 따라 화면에 원문을 표시한다. 인증 파일을 따로 만들지 않는다. [직접 입력 검증](../../doc/gyeong4/2026-v2.1/mqtt-direct-auth-input-20261028.md). 아래는 이전 버전의 개선 이력이다.

현재 권장 실행본은 **v5 / MSI 1.2.5**다. #81 BSM은 1초·QoS 0으로 지정 횟수만큼 발행 후 종료하고, 최종 합격은 센터 수신 로그와 사후 대조한다. [최신 동작과 검증](../../doc/gyeong4/2026-v2.1/bsm-publish-only-20261028.md). 아래 v4·v3 기록은 각 개선 당시 이력이다.

실패 진단 개선 당시 실행본은 **간편실행기 v4 / MSI 1.2.4**다. 필드 오류의 위치·값·범위, 주기 실패의 항목 귀속, 원인 미확정·추가 점검 안내를 반영했다. [실패 검증과 웹 표시 제약](../../doc/gyeong4/2026-v2.1/mqtt-failure-diagnostics-20261028.md). 아래 v3 기록은 순차 수신 구현 당시 이력이다.

Windows에서 기존 ScenarioEngine MSI 설치본과 공통 Chrome 확장을 사용한다. 4개 시나리오·11개 항목의 설정, 로컬 Broker·상대 에뮬레이터 준비, 웹 시작, 판정 표시와 로컬 HTML 결과를 연결한다.

순차 시험 구현 당시 배포: [MQTT-V2N-Easy-20261028-v3](C:/Implement/police-test-platform/outputs/MQTT-V2N-Easy-20261028-v3/시작하기.exe). 기준 설치본은 **MSI 1.2.3**이다. #82의 SPaT → TLSM → TIM 순차 수집과 동일 표본 검증을 적용했고, 실제 웹 5항목 성공 및 저장 보고서를 확인했다. [최신 검증](../../doc/gyeong4/2026-v2.1/mqtt-sequential-verification-20261028.md). 엔진·Python 복사본을 배포 묶음에 넣지 않고 설치 폴더를 재사용한다. 사용자 실행 기록은 `runs` 아래 회차별로 생성한다. 기존 v1 실행 경로도 백업 후 같은 내용으로 갱신했다.

1.2.2는 MessageFrame/value의 잘림·후행 데이터·패딩 및 ASN.1 제약 검사를 포함한다. 실제 설치본과 간편실행기로 정상 4개·11항목 및 손상 메시지 2회차의 예상 거부를 확인했다. [업데이트 검증](../../doc/msi-release-20261019-1.2.2.md)을 참고한다.

## 사용자 흐름

1. `시작하기.exe`에서 시나리오와 상세항목을 선택한다. 기본은 한 항목이며 전체 선택도 지원한다.
2. 사용할 토픽을 직접 입력한다. 빈 값은 거부하고 대소문자·슬래시를 그대로 유지한다. SPaT·TLSM의 토픽 공유를 허용한다.
3. Chrome에서 같은 시나리오의 새 자체 시험 회차를 만들고 Agent URL을 붙여넣는다.
4. 웹 환경설정 적용을 누른다. 값이나 선택을 바꾸면 다시 적용한다.
5. 시험 시작을 누른다. 전용 Broker와 상대의 연결·구독 준비가 끝난 뒤 실제 웹 시작 버튼을 실행한다.
6. 항목별 자동 결과와 웹 보고서 또는 이번 회차의 `시험결과.html`을 확인한다. 사용자 직접 확인 표시는 자동 판정과 별개다.

## 연결과 실행 계약

- 기존 `interfaceconformance/launcher/WebFormLink.cs`, `PortReservation.cs`, `UserReport.cs`를 참조한다. 공통 Chrome 확장 ID·권한·파일은 변경하지 않는다.
- 정상 설정·시작은 확장을 통해 실제 웹 버튼을 사용한다. 실행기의 Controller는 DESCRIBE와 응답 확인을 담당한다. 웹 중지가 불가능한 경우에만 기존 계약에 따라 STOP을 보낸다.
- `mqttv2n-selection.json`의 case·PID·설정 차수·선택 항목·정규화된 설정 전체를 확인한다. 동일 선택에서 토픽만 바뀐 경우도 구분한다.
- 설정 적용만으로 Broker·상대를 시작하지 않는다. 시작할 때 소유한 loopback Mosquitto와 독립 상대를 준비한다.
- 대상이 Publisher이면 시험기의 SUBACK 준비 파일을 기다려 발행을 허용한다. 대상이 Subscriber이면 상대의 SUBACK를 먼저 확인하고 수신 관측을 시작한다.
- 수신 관측 파일은 회차 안에서 자동 관리한다. 외부 파일을 간편시험의 수신 근거로 바꾸지 않는다.
- 원래 결과와 FINISH, 전송 큐의 pending/discarded/error=0을 확인하고 상대를 정상 종료한다. PID·경로·시작 시각이 일치하는 소유 프로세스만 정리한다.
- `LocalReport.cs`는 원문·디코딩·회차·실제 발송 주체를 순서대로 보존하고 큰 JSON 조각을 재조립해 공통 HTML 보고서에 전달한다.

자동 Broker 모드는 `127.0.0.1`, 포트 1024~48999를 사용한다. 점유 포트는 실행기의 적용 단계에서 조정하고 웹에도 반영한다. 외부 인증/TLS Broker와 실장비 시험은 별도 환경에서 구성한다.

## 빌드·패키징

```powershell
python -X utf8 mqttv2nconformance/launcher/package.py `
  --output C:\Temp\MQTT-Easy `
  --engine-root 'C:\Program Files\ScenarioEngine' `
  --msi-manifest C:\path\to\MSI-1.2.2\build-manifest.json `
  --broker-runtime C:\path\to\mosquitto-runtime
```

새 출력 폴더를 사용한다. 설치된 파일과 MSI manifest를 먼저 대조하며, 실행기에도 설치 런타임·동봉 Broker의 해시를 기록한다. 기존 사용자 회차 폴더를 덮어쓰지 않는다. 배포할 때는 검증한 실행 파일을 그대로 사용하고 `runs`·테스트 입력 파일을 제외한다.

개발 점검에는 `--ui-check`, `--render`, `--run-local`, `--ui-run`을 사용한다. `--ui-run`은 실제 QuickForm에서 필드·선택을 설정하고 일반 버튼과 같은 ApplySettings/StartRun 처리를 거친다. 결과 화면 PNG와 표시 상태를 저장하며, 물리 마우스 클릭 자동화와 구분한다. 마지막 선택 인자로 기대 판정 `SUCCESS`/`FAIL`/`STOPPED`를 지정할 수 있다. 실제 판정을 바꾸지 않으며 손상 입력의 실패 표시 검증에 사용한다.

[검증 기록](../../doc/gyeong4/2026-v2.1/mqtt-v2n-easy-launcher-verification-20261019.md)을 따른다. 최초 실제 웹 검증에서 발견한 worker 대기시간 오류는 MSI 1.2.1에서 수정했고, 최종 설치본으로 4개를 다시 실행했다.

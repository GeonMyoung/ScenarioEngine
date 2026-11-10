> 공통 확장·동시 실행: [최신 연결 안내](../../interfaceconformance/launcher/WEB-BRIDGE.md)를 우선합니다. 새 실행기는 DATEX/REST/TCP/Kafka를 하나의 확장에 회차별로 연결합니다. 아래의 단일 연결·별도 확장 설명은 이전 버전 이력입니다.

# Kafka 수동시험 간편 실행기

현재 공통 로그 버전: `20260925.kafka.easy.2`. 사용자 화면은 시험 안내·준비·진행·송수신·판정 근거·결과의 같은 단계를 사용합니다. **시험 기록 보기**는 사용자용 HTML을 열고, 내부 파일은 **상세 진단(고급)**에서 확인합니다. [공통 규칙](../../doc/interface-test-common-rules.md) · [검증 범위](../../doc/gyeong4/2026-v2.1/interface-user-log-verification-20260925.md)

등록 76~79의 4개 case·20개 항목을 선택하여 같은 PC의 독립 상대와 시험한다. 사용자가 지정한 DATEX v3의 웹 설정 경유 흐름, 기존 REST/TCP의 WinForms/웹 연결 코드를 참고해 Kafka 전용 모듈로 분리했다. 기존 실행기·Chrome 확장 파일은 변경하지 않는다.

## 사용자 묶음

`C:/Implement/police-test-platform/outputs/Kafka-Easy-20260925-v2/시작하기.exe`

전체 ZIP을 새 폴더에 풀고 실행한다. `간편실행안내.html`, `읽어주세요.txt`, `검증결과.json`을 포함한다. Python 3.12.10, confluent-kafka 2.8.0, Temurin JRE 17.0.20.1+1, Apache Kafka 3.9.1을 묶었다. Java/Python의 시스템 설치·PATH 변경, Docker/WSL 조작은 필요하지 않다. 같은 PC의 독립 상대를 사용하는 개발 수동시험 범위다.

Chrome 연결은 설치된 `REST API 웹 시험 연결` 확장(ID `hkcbopjignhkclfmejopkpkpmdlpnmba`)과 loopback 43763을 재사용한다. REST/TCP/Kafka 실행기를 한 번에 하나만 연결한다. 권한과 처음 설치하는 PC의 절차는 [권한 안내](EXTENSION-PERMISSIONS.md)에 있다.

## 동작

1. 상세항목과 합의한 토픽·Group·자료·시간 조건을 선택한다. 기본은 한 항목이다.
2. 새 웹 자체시험 회차를 열고 Agent 주소를 붙인다.
3. 실제 웹 입력칸을 채우고 실제 설정 버튼으로 적용한다. 설정 적용만으로 브로커·상대·시험을 시작하지 않는다.
4. 엔진의 실제 설정 파서로 검사하고 `kafka-selection.json`의 PID/case/차수/입력값/유효값/선택 목록을 대조한다. 설정 변경은 시작을 비활성화하고 재적용을 요구한다.
5. 웹 시작 직전에 해당 회차의 loopback 전용 KRaft 브로커와 선택한 합의 토픽, 독립 상대를 준비한다. 사용자 웹 직접 수정값도 반영한다.
6. 정상 경로는 Controller DESCRIBE만 사용하고 SETUP/START를 직접 우회하지 않는다. 종료 후 직접 만든 프로세스만 정리하며 원문/결과/사용자의 직접 확인 표시는 보존한다.

브로커는 회차마다 새 데이터 폴더를 사용한다. 데이터·제어 포트는 127.0.0.1에만 바인딩하고 점유 포트를 자동으로 빼앗지 않는다. Kafka의 자체 __consumer_offsets 파티션은 시험용 단일 파티션으로 구성하여 작은 수동시험마다 대형 파일을 생성하지 않게 했다. 기존/외부 브로커를 수정하거나 토픽을 삭제하지 않는다. 외부 브로커·인증·실장비는 일반 시험 엔진으로 별도 구성한다.

## 구성 파일

- `QuickForm.cs`, `SettingsPanel.cs`: 선택/설정/재적용/결과 확인 UI.
- `SessionRunner.cs`: 웹 설정 수락 대조, 브로커/상대 준비, 결과 관찰과 소유 프로세스 정리.
- `WebFormLink.cs`: 기존 확장 ID/Origin/회차/문서 ID/임의 토큰 확인. REST 확장과 같은 연결 규약.
- `Broker.cs`, `broker_admin.py`: 로컬 브로커 및 선택 토픽 준비. 형식화·JVM·Python 보조 작업은 창을 숨겨 실행한다.
- `../runtime/configuration.py`, `../src/KafkaBridge.h`: 엔진과 실행기가 같은 설정 검사를 사용하고 실제 SETUP 수락을 기록한다. 실패한 SETUP은 이전 수락 기록을 무효화한다. 경로는 실행 파일 기준 상대 경로도 지원한다.
- `package.py`: 새 폴더만 생성하고 실행기/엔진/런타임/라이선스/사용 안내/해시 manifest를 묶는다. 사용자 `runs`를 덮어쓰지 않는다.
- `test_bridge.py`: 실제 엔진·Java Kafka·독립 상대를 사용하는 로컬 웹 연결 모의. 실제 Chrome 검증과 구분한다.

GUI에서 동기 설정 검사가 호출될 때에도 외부 프로세스 대기는 UI 동기화 컨텍스트를 기다리지 않는다. 이 부분의 초기 대기를 보완하고 실제 GUI→Chrome 실행으로 확인했다.

## 개발·검증

네이티브 엔진은 기존 `ScenarioEngineTest.vcxproj` Debug/x64로 빌드한다. 실행기는 `build.ps1 -OutputDirectory <새 경로>`로 .NET Framework C# 컴파일러를 사용한다. `package.py`에는 `--output`, `--java-home`, `--kafka-home`, `--client-home`을 전달한다. client-home은 confluent-kafka 2.8.0의 site-packages다. 다운로드 출처/체크섬은 배포 `bundle-manifest.json`에 기록한다.

`test_bridge.py <묶음> --suite all|smoke|boundaries`는 실제 통신을 수행한다. all은 주기를 3초로 단축해 20항목을 확인한다. 기본 시간 조건 검증은 [기존 Kafka 결과](../../doc/gyeong4/2026-v2.1/kafka-verification-20260925.md)와 구분한다.

[간편 실행기 검증 결과](../../doc/gyeong4/2026-v2.1/kafka-easy-launcher-verification-20260925.md) · [기계 판독 결과](../launcher-verification-20260925.json).

현재 플랫폼의 STOPPED 상세 상태/중지 보고서 한계는 유지한다. 실행기는 중지 결과를 정확히 표시하고 이 경우 기록 폴더에서 확인하도록 안내한다. 자동 판정과 사용자의 직접 확인 완료 표시는 별개다. Kafka 데이터 검사 범위와 공식 미확정 의미는 기존 [시험 안내](../README.md)를 따른다.

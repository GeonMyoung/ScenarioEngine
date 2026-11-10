> 공통 확장·동시 실행: [최신 연결 안내](../../interfaceconformance/launcher/WEB-BRIDGE.md)를 우선합니다. 새 실행기는 DATEX/REST/TCP/Kafka를 하나의 확장에 회차별로 연결합니다. 아래의 단일 연결·별도 확장 설명은 이전 버전 이력입니다.

# DATEX 간편 실행기

현재 버전: `20260927.easy.7`. 환경설정에서 **개시요청 사용**을 선택하면 Initiate → Login(serverInitiated), 해제하면 일반 Login(clientInitiated)으로 시작합니다. 개시요청 사용 시 ISO Server가 TCP 접속하고 ISO Client가 수신 대기합니다. 해제하면 ISO Client가 접속합니다. 선택한 모드에 해당하는 IP·포트를 사용합니다. [v7 TCP 방향 수정](../../doc/gyeong4/2026-v2.1/datex-tcp-direction-20260927.md).

사용자 화면은 시험 안내·준비·진행·송수신·판정 근거·결과의 같은 단계를 사용합니다. **시험 기록 보기**는 사용자용 HTML을 열고, 내부 파일은 **상세 진단(고급)**에서 확인합니다. [공통 규칙](../../doc/interface-test-common-rules.md).

DATEX 수동 검증용 Windows GUI다. Chrome 공통 연결 확장을 통해 웹 폼의 입력·설정 버튼·시작 버튼을 사용한다. 실행기가 SETUP/START를 직접 전송하지 않는다. v7에는 개시요청·협상 검사·종료 처리를 보완한 엔진과 에뮬레이터를 포함한다. 운영자 안내는 [guide.html](guide.html), 설치 권한은 [EXTENSION-PERMISSIONS.md](EXTENSION-PERMISSIONS.md)를 참고한다.

빌드: `build.ps1 -OutputDirectory <출력 폴더>`

묶음 생성: `python package.py --baseline <v9 묶음> --runtime <갱신한 실행본 폴더> --output <새 묶음 폴더>`

v3 로컬 연결 계약 검증: `python test_web_bridge.py <검증용 묶음>`. 실제 Chrome 확장과 웹 폼 검증을 대체하지 않는다. 기존 `test_launcher.py`는 v1/v2 직접 Controller 검증 이력이며 v3 전체 실행에 사용하지 않는다. Python `websockets`가 필요한 것은 개발 검증뿐이다.

카탈로그는 v9의 14개 구성·152개 상세시험 및 기본 조건을 그대로 읽는다. 이후 카탈로그/프로토콜 변경 시 실제 선택 목록 검증과 역할별 실행 순서를 다시 확인해야 한다. production 신뢰 대상 인증서 pin 변경은 새 인증서의 정당성을 확인한 후 수행한다.

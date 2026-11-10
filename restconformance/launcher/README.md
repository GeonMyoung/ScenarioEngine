> 공통 확장·동시 실행: [최신 연결 안내](../../interfaceconformance/launcher/WEB-BRIDGE.md)를 우선합니다. 새 실행기는 DATEX/REST/TCP/Kafka를 하나의 확장에 회차별로 연결합니다. 아래의 단일 연결·별도 확장 설명은 이전 버전 이력입니다.

# REST API 간편 실행기

현재 상세시험 안내 개선 버전은 `20260926.rest.easy.4`다. 기존 82개 선택 키를 유지하고, 시험 조건·기대응답·근거와 실제 관측 범위를 설명한다. 엔진의 새 상세시험 설명을 실행기에서도 사용하며 기존 공통 Chrome 확장을 그대로 사용한다. 이전 v3의 실행 기록은 보존한다.

현재 공통 로그 버전: `20260925.rest.easy.2`. 사용자 화면은 시험 안내·준비·진행·송수신·판정 근거·결과의 같은 단계를 사용합니다. **시험 기록 보기**는 사용자용 HTML을 열고, 내부 파일은 **상세 진단(고급)**에서 확인합니다. [공통 규칙](../../doc/interface-test-common-rules.md) · [검증 범위](../../doc/gyeong4/2026-v2.1/interface-user-log-verification-20260925.md)

DATEX v3 실행기의 Windows 화면·웹 폼 연결 구조를 참조한 REST 전용 실행기다. 현재 REST 12개 시나리오·82개 상세항목을 읽는다. 원본 DATEX 실행기와 확장은 수정하지 않는다.

- 실행기 설정 → Chrome 실제 입력칸 → 웹 설정 버튼 → 엔진의 `rest-selection.json` 수락 기록을 대조한다. 실행기가 SETUP/START를 직접 전송하지 않는다.
- 웹에서 직접 적용한 값도 엔진의 실제 설정 파서로 검사하고 상대 프로그램에 반영한다. 설정/시작은 분리되며 변경 후 재적용 전 시작은 차단한다.
- 제공 측의 정상 자료·자료 부재 오류·빈 정상응답은 준비 조건별로 나눠 선택한다. 자체 시험은 같은 PC의 127.0.0.1 상대 프로그램을 사용한다.
- 상대 HTTP 서버는 웹 시작 전에, 상대 요청 클라이언트는 엔진의 수신 대기 후 실행한다. 인증값은 명령줄 대신 자식 프로세스 환경으로 전달한다.
- 엔진 최종 결과와 FINISH를 확인하며 실행기가 시작한 프로세스만 정리한다. 사용자의 직접 확인 표시는 자동 판정과 별도다.
- Python 표준 실행환경을 포함한다. 공백·한글 경로로 옮긴 묶음, 특수문자 조회변수와 선택 증적 대조도 로컬 검증했다.

빌드: `build.ps1 -OutputDirectory <출력 폴더>`

새 묶음: `python package.py --output <새 출력 폴더> --zip`

검증: `python test_bridge.py <검증용 묶음> --suite smoke` / `--suite all`. 개발 검증 실행 Python에는 websockets가 필요하며, 사용자 묶음의 상대 프로그램은 표준 라이브러리만 사용한다. 이 검증은 로컬 웹 연결 계약이며 설치된 Chrome 확장·실제 웹 화면 검증을 대신하지 않는다.

REST 확장 ID는 `hkcbopjignhkclfmejopkpkpmdlpnmba`, 로컬 포트는 `43763`이다. DATEX의 확장 ID·43762 포트와 다르다. [설치 권한](EXTENSION-PERMISSIONS.md), [운영자 안내](guide.html)를 따른다. 인증서 pin은 기존 검증 플랫폼의 정확한 leaf identity를 유지하며 OS·브라우저 신뢰 설정을 바꾸지 않는다.

[검증 현황](../../doc/gyeong4/2026-v2.1/rest-easy-launcher-verification-20260925.md)

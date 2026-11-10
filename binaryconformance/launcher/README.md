> 공통 확장·동시 실행: [최신 연결 안내](../../interfaceconformance/launcher/WEB-BRIDGE.md)를 우선합니다. 새 실행기는 DATEX/REST/TCP/Kafka를 하나의 확장에 회차별로 연결합니다. 아래의 단일 연결·별도 확장 설명은 이전 버전 이력입니다.

# TCP/Binary 간편 실행기

현재 세션 개선 버전은 `20260925.binary.easy.5`다. 항목마다 한 번 접속하여 입력한 N회 정보를 같은 세션에서 교환하고 연결을 정리한다. 기존 공통 Chrome 확장을 그대로 사용한다. 실행기·엔진·상대 프로그램을 함께 갱신한 묶음을 사용해야 한다.

현재 공통 로그 버전: `20260925.binary.easy.3`. 사용자 화면은 시험 안내·준비·진행·송수신·판정 근거·결과의 같은 단계를 사용합니다. **시험 기록 보기**는 사용자용 HTML을 열고, 내부 파일은 **상세 진단(고급)**에서 확인합니다. [공통 규칙](../../doc/interface-test-common-rules.md) · [검증 범위](../../doc/gyeong4/2026-v2.1/interface-user-log-verification-20260925.md)

최신 v2: **송수신 상세**에서 회차별 원문 HEX·해석·수집 원본과 실제 발송/수신 주체를 확인한다. 긴 표시 자료를 복원하고 전체 이력을 파일에서 읽으며 이전 행을 삭제하지 않는다. [v2 검증](../../doc/gyeong4/2026-v2.1/binary-user-log-v2-20260925.md)

등록 68~75번, 8개 시나리오·52개 상세항목을 지원한다. DATEX v3의 사용자 흐름과 REST 실행기의 Windows 화면·웹 연결 코드를 기반으로 한다.

- 시험/항목 선택 → 웹 입력칸 반영·실제 설정 버튼 → 실제 시작 버튼 → 결과 확인. 실행기는 SETUP/START를 직접 전송하지 않는다.
- 기본 선택은 한 항목이며 여러 항목·전체 선택을 지원한다. 자동 판정과 사용자의 직접 확인 기록을 구분한다.
- 엔진 설정 파서로 입력을 검사한다. `binary-selection.json`의 프로세스/case/적용 차수/입력·유효 설정/선택 항목을 확인한 뒤 준비 완료로 표시한다. 잘못된 SETUP은 기록을 무효화한다.
- 상대 서버를 먼저 대기시키거나 엔진 서버 대기 후 상대 클라이언트를 시작한다. 설정만 적용한 상태에서는 시험·상대를 시작하지 않는다. 웹에서 직접 수정한 값도 상대에 반영한다.
- Big-Endian 및 기존 TCP 판정을 유지한다. LRC/ACK/인코딩/주기 등 채택 운용 기준을 바꾸지 않는다. 정상/실패/중지/수행 오류를 구분하고 전체 FINISH 후 생성한 프로세스만 종료한다.
- `package.py`는 현재 엔진/CLI, 독립 Python 상대와 Python 표준 런타임을 묶는다. 한글·공백 경로를 지원한다.

## 웹 연결

**기존 REST API 웹 시험 연결 확장을 변경 없이 재사용**한다. ID `hkcbopjignhkclfmejopkpkpmdlpnmba`, loopback `43763`, `X-Rest-Extension` 헤더는 기존 연결 호환을 위한 값이다. REST와 TCP 실행기는 한 번에 하나만 연결한다. DATEX v3의 확장은 DATEX 전용 입력을 전제로 하므로 사용할 수 없다.

묶음의 확장은 REST 원본의 그대로인 사본이다. 이미 설치했다면 추가 설치·새로고침 없이 사용하며 기존 설치 폴더를 삭제하지 않는다. [권한 안내](EXTENSION-PERMISSIONS.md)

## 빌드·검증

1. `BinaryConformanceCli.vcxproj`와 **`ScenarioEngineTest.vcxproj`**를 Debug/x64로 빌드한다. `ScenarioEngine.vcxproj`만 빌드하면 플랫폼 실행 파일은 갱신되지 않는다.
2. `python binaryconformance/launcher/package.py --output <새 출력 폴더> --zip`
3. `python binaryconformance/launcher/test_bridge.py <검증용 묶음> --suite smoke` 및 `--suite all`. 검증 도구에는 websockets가 필요하며 사용자 묶음에는 필요 없다.

기본 TOD 주기를 유지한 전체 검증에는 몇 분이 필요하다. 로컬 모의 웹 연결 검증과 설치된 Chrome의 실제 웹 검증을 구분한다. 사용자 기록이 있는 출력 폴더는 패키징 도구가 덮어쓰지 않는다.

[사용 안내](guide.html) · [계획](../../doc/gyeong4/2026-v2.1/binary-easy-launcher-plan-20260925.md) · [검증 결과](../../doc/gyeong4/2026-v2.1/binary-easy-launcher-verification-20260925.md)

# prj22 HTTP 어댑터 재사용

2026-09-24 SC28 추가: 기존 `getJson`을 유지하면서 XML Accept를 사용하는 `getXml` 진입점을 추가했다. HTTP 전송·응답 처리는 공유하고, UTIC XML 규칙은 `restconformance/UticProvider`에서 검사한다. 수신 버퍼 크기 조회 실패 및 signed/unsigned 비교도 보완했다.

2026-09-24: SC11 VDS 제공시험을 위해 HTTP 클라이언트도 추가했다. `GitsnOpenApi_request.c` 및 libcurl/libssh2의 저장소 내부 빌드·원본 해시는 [client-import-manifest.json](client-import-manifest.json)에 기록했다. 새 클라이언트에는 버퍼 크기 제한/쓰기 실패 처리를 보완했고, `restconformance/HttpClientAdapter`가 중지·시간 제한과 인증서 검증을 유지한다. 아래는 최초 서버 도입 시점의 기록이다.

`C:/Implement/prj22/agent/GitsnOpenApi`의 HTTP 서버 구현을 통합 저장소에 필요한 범위로 가져온 모듈이다. 기준 HEAD는 `0a09363755078abbcf00c9519ea7244823487a0b`이며, 실제 참고 작업 폴더에는 미커밋 변경이 있었다. 파일별 원본 해시는 [import-manifest.json](import-manifest.json)에 기록했다. 원본 prj22 코드는 수정하지 않았다.

서버·HTTP 파서·요청/응답 자료형·전송 완료 이벤트를 재사용한다. libcurl 기반 요청 클라이언트 `GitsnOpenApi_request.c`는 가져오지 않았다. 헤더에 클라이언트 선언이 있어도 이 서버 전용 빌드가 해당 클라이언트 기능을 제공한다는 뜻은 아니다.

통합 저장소에 맞춘 변경:

- SDK 헤더 경로 및 현재 SDK의 소켓 수명 확인 방식 적용. 공유 SDK 소스는 변경하지 않았다.
- query를 항목으로 나눈 후 이름과 값을 각각 디코딩해 인코딩된 `&`, `=`, `+`, `%`를 보존한다. 빈 query는 상위 규칙에서 누락 여부를 판정한다.
- `GITSN_OPEN_API_DO_RESPONSE_ASYNC` 경로 추가. 소유권이 있는 응답 메시지를 큐에 전달하고 `response_sent` 이벤트로 실제 전송 완료를 확인한다. 동기 호출의 peer EOF 대기 방식과 분리해 중지 응답성과 응답 메모리 정리를 유지한다.
- UTF-8로 작성된 원본 소스 2개에 BOM을 붙여 해당 파일의 문자 인코딩을 명시했다.

UTIC 경로·키·XML 필드·반복수·적합 판정은 `restconformance`에 있다. 어댑터에 UTIC 전용 규칙을 넣지 않는다. HTTP 서버와 시험별 provider를 분리하는 prj22 구조를 적용했으며 국1/국5 고유 오류 순서와 재시도 시간은 경4 표준으로 가져오지 않았다.

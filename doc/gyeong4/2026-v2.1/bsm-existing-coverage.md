# RSE → 센터 BSM 시험 — 기존 구현과 2026판 검증 범위

작업: **[GM-88](https://app.riido.io/uVml0Nr-7iY91YVOhm8wQ/teams/GM/tasks/ov-FHQKWS5WdqUWBV42MW)** · 상위: GM-68 · 연계: **IF-F06** · 검토일: 2026-09-15.

## 1. 결론과 이번 작업의 범위

**RSE → 센터 BSM 시험 경로는 이미 구현되어 있다. 기존 통신·메시지 변환·시험 제어를 유지하고, 현재 판정이 입증하는 범위와 2026판 요구사항의 차이를 보완 대상으로 삼는다.**

사용자의 후속 지시에 따라 기존 구현을 먼저 대조했다. 아래의 재점검 절차는 기존 시험을 바탕으로 작성한 설계이며, 프로토콜 엔진을 새로 구현하는 계획으로 사용하지 않는다. 이번 산출물은 코드 읽기·표준 대조·시험 명세·구현 대응 문서다. 프로그램 실행, 결함의 동적 재현, 실장비 적합성 시험, 코드 수정은 수행하지 않았다.

| 분류 | 이번 대조 항목 | 의미 |
|---|---|---|
| 유지 4개 | K01~K04 | 기존 등록·호출 경로를 재사용한다. 2026판의 모든 요구를 이미 검증했다는 뜻으로 사용하지 않는다. |
| 검증 보완 7개 | B01~B07 | 기존 시험의 판정 근거·규칙·관측을 보완하거나 채택 규격과 다시 대조한다. |
| 신규 시험 항목 후보 1개 | N01 | IF-F06의 연속 관측과 1초 주기 판정. 기존 세션·구독·코덱 기반을 활용한다. |

이는 개발·시험 수량 견적이 아닌 **기능별 검토 분류 12개**다. 검토된 함수 경로의 잠재 문제는 정적 분석 결과로 표시하고, 실제 발생 여부는 후속 재현으로 확인한다. 이 대표 경로가 정리되어도 전체 32개 외부 연계를 다루는 GM-68은 완료되지 않는다.

## 2. 연계 주체·시험 접점·선행 조건

| 항목 | 이번 시험의 선택 |
|---|---|
| 시험 대상(SUT) | RSE의 BSM 정보 제공 기능 |
| 시험 엔진 | 센터 역할, TCP/AP-DATEX client |
| SUT 연결 역할 | TCP/AP-DATEX server. 이는 현재 기존 구현을 재사용하는 역할 선택이며 모든 배치의 고정 역할을 뜻하지 않는다. |
| 업무 데이터 방향 | RSE → 센터 역할의 엔진 |
| 시험기가 보내는 자극 | 접속·로그인·구독·구독 취소·ACK 제어·로그아웃 등 |
| SUT에서 관측하는 결과 | 수용/거부, 세션 반응, BSM을 담은 Publication, 종료 반응 |
| 기본 전송·표현 | TCP/IP, AP-DATEX, DATEX BER, CommRxPDU의 payload에 UPER로 표현되는 BSM |
| 기존 등록 이름 | `centerClient2rse` → `client1` → `TechnicalRegulation2MsgRx_itsk` |
| 별도 역할 | `rseServer2center`는 엔진이 RSE 역할로 센터 수신 기능을 시험하는 경로다. 이번 SUT 시험과 구분한다. |

시험 전에 다음을 준비한다. 값이 정해지지 않은 항목에는 실행자가 임의의 표준값을 넣지 않는다.

- **P01 — 연결/프로파일:** RSE 시험용 주소·포트, 양쪽 도메인·사용자·인증 설정, 허용 인코딩, 적용 AP-DATEX 판/프로파일과 응답 정책. 실제 인증정보는 공개 문서·로그에 저장하지 않는다.
- **P02 — BSM 공급:** RSE가 전달할 유효 BSM의 유입 방법, 시험 데이터 출처·버전·기준값, 유입이 실제 이루어졌다는 근거. 차량/시험용 공급원의 준비는 사전 조건이며 차량→RSE 무선 적합성을 이번 결과로 주장하지 않는다. RSE에 입력이 없다는 이유만으로 송신 기능을 실패 처리하지 않는다.
- **P03 — 판정 기준:** 채택 KS R 1600-2/ASN.1 판, 식별자 매핑, 기준 샘플, 검증 담당 서버의 규칙 버전. 현재 해당 KS 원전과 KS X ISO15784-3 독립 원문은 미확보다.
- **P04 — 관측 환경:** 시험 ID, 원시 패킷 보관, 세션·구독·Publication·PDU 인덱스의 연결, 판정 요청/응답 수집. 소켓 수신 지점과 비동기 웹 로그 시각을 구분한다.
- **P05 — 시간/오류 정책:** 주기 측정 대상, 기산점·종료점, 관찰 기간·표본 수·허용오차, 취소 후 잔여 패킷 처리, 재전송 식별, 오류별 기대 반응. 미정 값은 실행 설정에서 미정 상태로 유지한다.

이 문서의 절차·관측 설계는 **DESIGN / 기존 코드와 요구사항에서 도출한 시험 설계**다. 표준이 구체적인 시험 방법이나 수치를 명시하지 않은 부분은 `NOT EXPLICITLY SPECIFIED IN THE DOCUMENT`로 관리한다.

## 3. 원문에서 확인한 요구와 미정 조건

| 근거 ID | 실제 출처 | 확인한 내용 | 제한 |
|---|---|---|---|
| S01 | 경4 ITSK-00143-3 2026 Ver 2.1, 제4장 1.3.1·표 4-7, 본문 p.42 | RSE→센터 BSM, periodic, 1초, DATEX BER / payload UPER, ITSK-00100-3_2021v2 및 KS R 1600-2 제7절 준용 | 샘플 수·지연/지터 허용·측정 지점은 미기재 |
| S02 | ITSK-00100-3:2021v2 제3장 2, 표 3-6·3-7, 본문 p.8 / PDF 12면 | CommRxPDU 7개 필드의 ASN.1 형식·필수/선택·명시 범위 | BSM 내부 의미 규칙과 동일한 표가 아님 |
| S03 | 같은 참조 규격 부록 I.2·I.3, 본문 p.21 / PDF 25면 | TCP/IP, 로그인·수용/거부·FrED·로그아웃의 개요, 센터 client/RSU server 역할 예시 | 상세는 KS X ISO15784-3 참조. 거부 사유·구독/재전송·시간의 전체 계약은 미확정 |
| S04 | 같은 참조 규격 부록 I.4·I.5, 표 I-22·I-23, 본문 p.22 / PDF 26면 | Login·Subscription·Publication·Accept·Reject 등 PDU 구분과 헤더/Data/Tail 구성 | 이 목록만으로 CRC 알고리즘·오류 처리 정책을 완성할 수 없음 |
| S05 | 같은 참조 규격 부록 II.2·표 II-2, 본문 p.25 / PDF 29면 | EAM `1.0.15784.1.0.2`의 본체는 `SEQUENCE OF CommRxPDU` | 경4 규격 OID와 별도 식별 계층. 빈 목록의 서비스 의미는 별도 확인 |
| S06 | 기존 A03/A05의 Q02·Q10·Q11·Q21·Q22 | 채택판·시각·식별 계층·외부 검증기·예시값 분리 | 기존 미정 사항을 이번 문서로 임의 해소하지 않음 |

S02의 명시 필드:

| 필드 | 필수/선택 | 원문 형식·범위 | 시험에서 주의할 점 |
|---|---|---|---|
| psid | 필수 | INTEGER 0..270549119 | 허용 범위와 BSM용 정확한 서비스 코드 매핑을 구분 |
| channel | 필수 | INTEGER 0..255 | 예제의 173을 고정 채널로 강제하지 않음 |
| rcpi | 필수 | INTEGER 0..255 | 숫자 구문·범위를 검증. 무선 수신 성능을 시험하지 않음 |
| peerAddress | 선택 | OCTET STRING | 선택 필드를 전역 필수로 만들거나 원문에 없는 길이를 강제하지 않음 |
| signed | 선택 | BOOLEAN | 필드 표현과 실제 서명 검증/인증 프로파일을 구분 |
| payloadType | 선택 | INTEGER | 코드표·포장 계층은 채택 프로파일로 확인 |
| payload | 필수 | OCTET STRING | 길이의 서비스 제약, BSM 포장·MessageFrame 적용은 채택 규격으로 확인 |

경4 규격 OID `1.2.410.200053.2.143.3.1.1.2.0`, EAM OID `1.0.15784.1.0.2`, PSID, MessageFrame messageId는 각각 기록한다. **EAM OID와 본체 연결은 이번에 S05 원문에서 직접 확인했다.** PSID 82050/messageId 20, channel 173 및 예제 차량 값은 코드·경4 예제에서 확인한 값이며, 이 사실만으로 채택 KS의 전체 규칙·고정 상수로 확대하지 않는다.

S02 표 아래 event-driven 설명은 RSU client→센터 server라는 문맥을 포함한다. 이를 이번 센터 client→RSE server의 구독 모드로 자동 전용하지 않는다. S01의 1초 전송 요구와 구독 모드/요청 주기의 관계는 아래 G03에서 결정한다.

## 4. 실제 실행 경로와 기존 기능 분류

코드 기준은 **`8e68bd08d2a3657d9c0a14d19d0204e3be491c96`**이다. 엔진 코드는 기존 A04 분석 기준 이후 변경되지 않았다. 근거 ID C01~C14의 파일/줄은 §8에 연결한다.

| ID / 분류 | 기존에 확인한 것 | 2026판 적용과 후속 처리 | 근거 |
|---|---|---|---|
| K01 / 유지 | category를 Iso14827TestHelper에 전달하고 `centerClient2rse` 설정으로 client1을 생성 | 기존 역할·설정 경로 재사용. 반대 역할·client1_tr과 혼동하지 않음 | C01/C02 |
| K02 / 유지 | ItsIso14827의 TCP·DATEX 세션, 정상 로그인·FrED·로그아웃 경로 | 기존 세션 계층을 유지하며 채택 프로파일과 설정을 대조 | C03/C04/C14, S03/S04 |
| K03 / 유지 | EAM별 API 선택, CommRxPDU 디코딩, PSID/MessageFrame 분기, BSM UPER 디코딩·변환 | 기존 코덱을 유지. S02/S05와 B05의 채택 스키마·예외 처리를 확인 | C05/C06/C07, S01/S02/S05 |
| K04 / 유지 | START/상태 통지, 판정 요청과 웹/메인 응답 연결, 종료/중지 진입점 | 기존 제어·결과 경로 재사용. B06/B07에서 관측/판정 의미 보완 | C08/C09/C13 |
| B01 / 검증 보완 | 잘못된 비밀번호·중복 로그인 시도가 이미 등록·호출됨 | 접속 함수의 오류와 실제 SUT Reject를 구분. 원인 없는 SUCCESS 위험을 먼저 재현 | C02/C03/C10, 점검 V02/H01 |
| B02 / 검증 보완 | 잘못된 EAM 구독 시험이 이미 연결됨 | `_client_subscribe` 실패와 거부 응답을 같은 성공 분기로 처리하는 경계를 분리 | C02/C11, 점검 V03/H01 |
| B03 / 검증 보완 | 등록 구독 후 Publication 수신·취소, heartbeat에 따른 상태 전환이 존재 | 취소 확인과 추가 발행 관측 기간·비행 중 패킷·세션 유지 증거를 구분 | C02/C12, 점검 V04 |
| B04 / 검증 보완 | ACK 지연 설정과 첫/두 번째 Publication 처리 존재 | 두 번째 새 주기 발행과 실제 재전송의 식별 증거를 추가. 간격·횟수는 프로파일 확인 | C12, 점검 V05/H02 |
| B05 / 검증 보완·규격 대기 | BSM 변환 후 외부 판정기로 요청. CommRxPDU 및 ASN.1 기반 존재 | S02의 7개 필드와 채택 KS BSM 규칙·OPTIONAL·범위·단위·소모 길이 등을 대조. 외부 판정기 부재를 단정하지 않음 | C05~C09, 점검 V01/H03, G01/G04 |
| B06 / 검증 보완 | encodedEAM 통지, BSM value/data 및 testIdx/testName·time(NULL) 기록 경로 | 전체 DATEX/EAM/payload/value의 출처와 다중 PDU·비동기 응답 상관관계, 고해상도 관측을 연결 | C06/C08/C09, 점검 H04, G03/G05 |
| B07 / 검증 보완 | 외부 판정 OK→SUCCESS, 시스템/설정/접속/timeout/디코딩 오류 등→FAIL 처리 | SUT 위반·시험환경 장애·규격미정·중지/미실행을 별도로 표현. 오류 책임을 판정 근거에 보존 | C09/C13, 점검 H04/H05 |
| N01 / 신규 시험 항목 후보 | 정상 BSM은 single 구독을 사용. 공통 등록 구독 파라미터 15는 취소/재전송 경로에도 쓰임 | IF-F06의 연속 관측·1초 주기 판정 항목을 추가할 후보. 기존 세션/구독/코덱은 재사용하고 공통 15를 일괄 변경하지 않음 | C02/C06/C08, S01, 점검 V06, G03 |

유지 항목에도 영향 검증은 필요하다. 위 분류의 신규는 IF-F06에 연결할 **시험 관측/판정 기능**이며 별도 AP-DATEX 통신 라이브러리나 BSM 코덱을 새로 만드는 작업을 뜻하지 않는다.

### 정적 분석에서 우선 확인한 판정 위험

1. **로그인 거부 증거:** C03의 잘못된 로그인·중복 로그인 분기는 `_ItsIso14827_connectToServer(...).code != 0`에서 SUCCESS를 통지한다. C10의 하위 함수는 실제 Reject 이외에 잘못된 인자, 메모리/태스크 호출 실패 등도 반환할 수 있다. 통신 실패를 포함한 각 원인의 실제 도달 여부와 최종 표시를 후속 H01에서 재현한다. 거부 사유 문자열 출력만으로 실제 Reject 수신이 입증되지는 않는다.
2. **구독 거부 증거:** C11은 `_client_subscribe(...) == FALSE || result != ..._max`를 성공 경로로 처리한다. `_client_subscribe` 내부의 EAM 준비·전송·직렬화/로그 준비 실패도 구분할 필요가 있다. 구독 수용 뒤 data_control을 기다리는 경로도 있으므로, 적합한 거부 방법은 채택 계약으로 판단한다.
3. **재전송 식별:** C12는 첫 Publication에서 ACK 지연 플래그를 바꾸고 이후 Publication에서 SUCCESS를 통지한다. 해당 분기에는 도메인/OID/sid 확인이 있으나 이전 Publication과 재전송 동일성을 비교하는 근거는 확인되지 않았다. 하위 라이브러리의 중복 처리와 식별 규칙까지 대조해 새 데이터 발행이 오인되지 않게 한다.
4. **CRC와 전체 적합성:** 기존 접속 호출에 `ItsIso14827CRCCheck_warning`이 보인다. 따라서 수신·디코딩 성공만으로 CRC 적합성까지 확인했다고 보고하지 않는다. 실제 CRC 정책·관측 결과와 채택 규격을 확인한다(C03/C14, G02).

이 항목들은 **정적 분기와 호출 계약으로 확인한 위험**이다. 이번 작업에서 SUT의 동작 실패나 실제 오류 시험 결과를 만들어 보고하지 않는다.

## 5. 기존 시험을 기준으로 한 정상 절차

P01~P04를 충족하고 검증하려는 조건의 규격이 확정된 범위에서 적용하는 재점검 설계다. 하나의 경로에서 모든 선택 시험을 강제로 동시에 켜지 않고 목적별 설정을 기록한다.

| 단계 | 시험기가 수행하는 일 | RSE에서 관측할 것 | 판정과 종료 |
|---|---|---|---|
| 0 | 설정·프로파일·샘플·판정 서버·관측 경로 확인 | 준비된 BSM이 RSE에 유입된 근거 | 전제 미충족이면 NOT_RUN/INCONCLUSIVE; SUT FAIL 금지 |
| 1 | 센터 client로 연결·정상 로그인 | TCP 연결, Login 수용/거부, 선택된 codec·세션 | 채택 절차와 비교. 환경 장애와 실제 Reject를 구분 |
| 2 | `centerClient2rse`의 기존 단발 EAM 구독 | 구독 응답, 대응 sid의 Publication | 단발 시험과 주기 시험 V06을 분리 |
| 3 | 받은 Publication의 식별·BER/EAM 구조를 해석 | 도메인·사용자·sid·EAM OID·CommRxPDU | 원시 수신 자료에 근거해 규격 위반/디코더 문제를 구분 |
| 4 | payload를 기존 UPER/BSM 변환에 전달 | 실제 RSE가 전달한 BSM, 식별 계층·변환값 | 채택판의 확인된 규칙만 판정. 샘플 예제값을 고정 기준으로 사용하지 않음 |
| 5 | 검증 요청·응답과 자료를 연결 | 검증기 응답·규칙 버전·각 PDU 결과 | 현재 SUCCESS 통지와 전체 표준 적합성을 구분. 누락된 판정이 있으면 통과 확정 보류 |
| 6 | 해당 시험 목적에 따라 취소·로그아웃·중지 | 취소/종료 반응, 허용된 잔여 발행, 자원 종료 | 완료·중지·환경 실패를 서로 구분해 기록 |

현재 코드 정상 경로는 데이터 수신 후 해당 구독 항목을 추출하고 `_client_unsubscribe`를 호출한다(C06). 이를 그대로 실행한 한 번의 수신 성공으로 1초 주기 적합성을 계산하지 않는다.

## 6. 재점검 명세: SUT 시험과 시험기 자체 검증

모든 아래 항목은 **미실행(not-run)**이다. 실제 SUT 반응이 필요한 V 항목과 시험기 자체에 오류를 주입하는 H 항목을 분리했다. RSE의 수신 기능을 시험하는 것처럼 잘못된 BSM을 RSE에 보내지 않는다. H의 성공/실패는 시험기 구현의 결과로 기록하며 SUT 결과에 합산하지 않는다.

### V01 — 기존 정상 BSM 제공·디코딩·판정 연결

- **목적/대상:** RSE 송신 SUT / IF-F06. K01~K04·B05·B06. 근거 S01~S05, C01~C09.
- **전제/입력:** P01~P04. 승인된 BSM 입력이 RSE에 공급됨을 확인하고 정상 로그인·기존 single 구독을 요청한다.
- **절차:** §5의 0~6을 순서대로 수행한다. 실제 RSE Publication과 모든 대상 PDU를 수집해 CommRxPDU·BSM 변환과 판정 요청까지 추적한다.
- **관측/기대:** 구독과 일치하는 Publication, S02의 구조, 채택된 BSM 규칙, 연결된 결과·종료 근거. 고정 주소·차량값·예제 channel을 요구하지 않는다.
- **PASS/FAIL/INCONCLUSIVE:** 확인된 규칙과 실제 반응이 모두 맞으면 해당 조건 PASS. 신뢰 가능한 SUT 송신 근거에서 확정 규칙 위반이 확인되면 FAIL. 입력 유입/샘플 출처/규격/검증기가 미확정 또는 장애이면 해당 조건 INCONCLUSIVE. 1초 주기는 이 항목의 PASS에 포함하지 않는다.

### V02 — 실제 잘못된 로그인·중복 로그인에 대한 반응

- **목적/대상:** RSE의 로그인 정책 / B01. 근거 S03/S04, C03/C10. 상세 계약 G02 확인 필요.
- **전제/입력:** P01/P04. 정상 접속 가능성을 먼저 확인한다. 잘못된 비밀번호와 두 번째 중복 접속은 각각 독립 실행으로 분리해 하나씩 자극한다.
- **절차/관측:** Login 요청과 RSE의 실제 Accept/Reject·사유·세션 변화를 수집한다. 함수 반환코드, transport 오류, 수신된 거부 PDU를 각각 기록한다.
- **기대/판정:** 확정된 인증/중복 정책에 맞는 실제 반응이면 PASS, 확정 정책 위반이면 FAIL. 무응답·접속 실패·잘못된 시험 설정을 거부 성공으로 보지 않으며 원인·규격 미확정 시 INCONCLUSIVE. 허용 중복 정책·사유·시한은 `NOT EXPLICITLY SPECIFIED IN THE DOCUMENT`인 부분을 G02에서 해결한다.

### V03 — 기존 잘못된 EAM 구독 시험

- **목적/대상:** RSE의 비지원 구독 처리 / B02. 근거 S03/S04, C02/C11.
- **전제/입력:** P01/P04 및 정상 세션. 프로파일에서 비지원임을 확인한 EAM을 요청한다. 코드의 `1.0.15784.99.99.99`는 기존 시험 샘플이다.
- **절차/관측:** 구독 요청, 즉시 거부 또는 수용 후 data_control 등 실제 반응, 사유·sid·원시 응답·전송 오류를 분리해 관측한다.
- **기대/판정:** G02에서 확인한 비지원 처리와 일치하면 PASS, 신뢰 가능한 위반 증거면 FAIL. 송신·메모리·직렬화 실패는 거부 증거가 아니며 INCONCLUSIVE. 구체적 사유·시한·허용 반응은 확보되지 않은 계약을 추정하지 않는다.

### V04 — 등록 구독 취소와 세션 유지

- **목적/대상:** RSE의 취소 반응 / B03. 근거 S03/S04, C02/C04/C12.
- **전제/입력:** P01/P02/P04/P05. 프로파일에 맞는 등록 구독을 만든 뒤 첫 발행을 확인하고 취소한다.
- **절차/관측:** sid·취소 요청/응답·취소 전후 Publication·FrED·세션 종료 여부를 수집한다. 정상 구독의 존재와 대상 sid가 정확한지 확인한다.
- **기대/판정:** 채택된 취소·잔여 발행·세션 유지 정책을 충족하면 PASS, 그 정책 위반이면 FAIL. 관찰 기간·비행 중 패킷 허용·정확한 응답 정책은 `NOT EXPLICITLY SPECIFIED IN THE DOCUMENT`로 G02/G03 확인 전 최종 판정 보류. heartbeat 한 번을 모든 취소 조건의 대체 근거로 사용하지 않는다.

### V05 — ACK 지연에 따른 실제 재전송

- **목적/대상:** RSE 재전송 / B04. 근거 S03/S04, C12.
- **전제/입력:** P01/P02/P04/P05. 보장 발행/ACK/재전송을 요구하는 적용 프로파일을 먼저 확인하고 기존 PubAckDeferred 제어를 사용한다.
- **절차/관측:** 첫 발행과 ACK 처리, 후속 발행의 구독 ID·프로토콜이 정의하는 재전송 식별 정보·내용·시각을 수집한다. 새 주기 데이터와 재전송을 구분한다.
- **기대/판정:** G02/G03에서 채택한 동일성·간격·횟수·ACK 정책을 모두 충족하면 PASS, 확정 정책 위반이면 FAIL. 단순 두 번째 발행만 있거나 식별/시간 계약이 없으면 INCONCLUSIVE. 필요한 식별 필드와 시한을 예제에서 임의 고정하지 않는다.

### V06 — 1초 주기 연속 관측 후보

- **목적/대상:** RSE BSM 전송 주기 / N01. 근거 S01, C02/C06/C08.
- **전제/입력:** P01~P05. 구독 모드·BSM 유입 조건·측정 단위가 확정된 뒤 연속 공급/관측을 설정한다. 기존 single 모드와 공통 등록 파라미터 15를 그대로 적합성 기준으로 사용하지 않는다.
- **절차/관측:** 정의한 지점의 원시 수신 시각 `t[i]`와 연계 식별자를 기록하고 `Δ[i] = t[i+1] - t[i]`를 구한다. Publication 주기인지 개별 차량/PDU 주기인지, 배치·재전송·유실·warm-up 처리를 구분한다.
- **기대/판정:** 원문 명시값은 **1초**다. 허용오차·표본 수·관찰 기간·시계 동기/오차 및 수신 간격을 송신 주기로 평가할 방법은 G03의 채택값에 따른다. 이를 만족하면 해당 정의된 조건 PASS, 위반과 SUT 책임이 입증되면 FAIL, 기준·관측·입력이 부족하면 INCONCLUSIVE. `1초 ± 임의 수치`를 만들지 않는다.

### H01 — 시험기 오류를 거부 성공으로 오인하는지 확인

- **대상:** 시험기 B01/B02의 오류 분류. RSE 적합성 시험 결과로 합산하지 않는다. 근거 C03/C10/C11.
- **전제/입력/절차:** 분리된 모의/주입 환경에서 실제 Reject, 연결 실패, 로컬 인자·메모리·EAM 준비 실패, 구독 요청 실패를 각각 독립 입력으로 제공한다. 해당 분기의 상태 통지·오류·원시 응답 유무를 확인한다.
- **기대/판정:** 거부 원시 근거가 있는 경우와 환경/로컬 오류를 구별하면 검사기 점검 PASS. 거부를 받지 않았는데 거부 SUCCESS가 기록되면 검사기 점검 FAIL. 주입점이나 호출 조건이 불명확하면 미실행/INCONCLUSIVE. 이번 문서에는 이 동적 재현을 실행한 것으로 기록하지 않는다.

### H02 — 새 발행을 재전송으로 오인하는지 확인

- **대상:** 시험기 B04 / C12.
- **전제/입력/절차:** 같은 세션·OID·sid에서 서로 다른 정상 발행 두 개와, 프로파일상 재전송인 발행 쌍을 각각 공급한다. 두 번째 데이터 수신 시 판정과 보관 근거를 비교한다.
- **기대/판정:** 프로파일의 재전송 동일성 규칙으로 구분하면 점검 PASS. 새 발행 쌍을 재전송 성공으로 기록하면 점검 FAIL. 식별 규칙이 미정이면 최종 점검 기대값은 INCONCLUSIVE로 유지한다. RSE에 악성 payload를 보내는 절차로 사용하지 않는다.

### H03 — 기존 코덱·검증기의 정상/오류 샘플 범위

- **대상:** 시험기 K03/B05. 근거 S01/S02/S05, C05~C09.
- **전제/입력:** 출처·채택판·해시가 확인된 정상 벡터와 한 조건만 바꾼 오류 벡터. S02 필수 누락·타입/명시 범위 초과·선택 필드 유무, 잘린 BER/UPER, 잘못된 식별 조합을 각각 개별 벡터 ID로 관리한다.
- **절차/관측:** 실제 채택된 디코더/규칙에 샘플을 넣어 결과·실패 계층·변환 전후값·소모/남은 바이트를 확인한다. OPTIONAL의 합법적 생략은 허용한다. 빈 SEQUENCE OF, 후행 padding/잔여 비트, MessageFrame 포장, 내부 BSM 조건은 규격이 금지한 경우에만 오류 기대값을 정한다.
- **기대/판정:** 각 벡터의 확정 기대값과 일치하면 점검 PASS, 불일치면 점검 FAIL. 정상 기준 벡터나 KS 세부 규칙이 없으면 해당 벡터 INCONCLUSIVE. 샘플 검증 성공을 실제 RSE의 반응 증거로 바꾸지 않는다.

### H04 — 판정 서버 장애·다중 PDU·늦은 응답의 결과 연결

- **대상:** 시험기 B06/B07, C06/C08/C09.
- **전제/입력/절차:** 로컬 모의 환경에서 복수 PDU의 OK/오류 응답 순서를 바꾸고, 판정기 연결 실패·지연·이전 실행의 늦은 응답을 각각 제공한다. 실행/구독/발행/PDU별 요청·응답·완료 집계를 확인한다.
- **기대/판정:** 모든 필요한 결과가 정확한 대상에 연결되고 장애/미확정이 구분되면 점검 PASS. 첫 OK로 남은 오류가 누락되거나 이전 응답이 현재 결과를 덮으면 점검 FAIL. 주입·관측 계약이 미정이면 INCONCLUSIVE. 코드의 testName 완료 플래그만으로 여러 PDU의 실제 결과가 모두 반영됐다고 가정하지 않는다.

### H05 — 기존 중지·종료와 재실행 경계

- **대상:** 시험기 K04/B07, C13.
- **전제/입력/절차:** 정상 종료, 사용자 STOP, 초기화/설정 실패를 각각 수행할 후속 모의 계획이다. timer·세션·자원·결과 상태와 다음 실행의 초기 상태를 확인한다.
- **기대/판정:** 정의한 자원 종료/상태 계약을 충족하면 점검 PASS. 중지/설정 실패가 전체 적합성 PASS로 기록되거나 이전 실행 상태가 남으면 점검 FAIL. 현재 STOP의 timer 정리 경로가 있다는 사실과 모든 자원 정리가 검증됐다는 주장을 구분한다. 이번 작업에서 실행하지 않는다.

## 7. 미정 조건과 구현 순서

| ID | 필요한 자료·결정 | 현재 상태 / 적용 영향 |
|---|---|---|
| G01 | 채택 KS R 1600-2/ASN.1, BSM 내부 필수·선택·범위·단위·확장 조건 | 원전 미확보. 코드/예제를 정답으로 승격하지 않음. B05/H03 및 V01의 해당 규칙 판정 보류 |
| G02 | KS X ISO15784-3 채택판과 상세 로그인·구독·취소·재전송·CRC 정책 | 독립 원문 미확보. 확보된 S03/S04는 개요·PDU 목록 근거. V02~V05의 세부 기대 반응과 시한은 미정 |
| G03 | 1초 주기의 측정 대상/지점, 모드, 입력 조건, 시계·허용오차·관찰 기간, 취소/재전송 관측 | `NOT EXPLICITLY SPECIFIED IN THE DOCUMENT`. 측정값 보고는 가능하나 임의 기준으로 적합성을 판정하지 않음 |
| G04 | BSM PSID·MessageFrame ID·payloadType/포장 및 EAM/규격 OID 계층의 적용표 | EAM .2→CommRxPDU는 S05에서 확인. 82050/20 등은 별도 채택 근거 확인. H03의 매핑·포장 기대값 영향 |
| G05 | 기준 벡터·SUT 입력 공급·외부 검증기 규칙 버전·raw/decoded/판정 상관관계 | 현재 원격 검증기 구현/실행 결과 미확인. 없는 것으로 단정하지 않음. V01/H03/H04의 재현 준비 |

후속 구현의 권장 순서:

1. **기존 판정의 신뢰성부터 확인:** B01/B02/B04/B07에 대한 H01/H02/H04 재현으로 잘못된 성공·실패가 생기는 조건을 확인한다. 재현된 범위에 한해 기존 판정 분기를 보완한다.
2. **기존 단발 BSM 경로의 실제 커버리지 확인:** 승인된 샘플/규칙을 준비해 V01/H03으로 기존 통신·코덱·외부 검증기의 검증 범위를 대조한다. 기존 기능을 유지하고 확인된 누락만 작업으로 만든다.
3. **연속·시간 관측 추가:** G03을 확정한 후 기존 세션·구독·코덱에 N01/B06을 연결한다. 다른 시나리오의 공통 파라미터를 일괄 변경하지 않는다.
4. **재사용 경계 설계:** GM-69/70에서 기존 통신 계층과 메시지 규칙, 원시 근거·판정 결과 연결의 계약을 정리한다. 이 대표 결과를 다른 IF에 적용할 때 각 메시지·역할·규격 차이를 다시 확인한다.

첫 후속 후보는 **기존 거부·재전송·결과 판정의 재현과 보완**이다. 실제 수정이나 테스트 실행은 해당 후속 업무의 범위로 진행한다. 이번 검토 완료는 GM-88 문서 결과이며 GM-68 전체·GM-64 원전 확보·RSE 적합성 완료를 의미하지 않는다.

## 8. 고정 코드 근거

아래 링크는 모두 이번에 읽은 `8e68bd0` 버전의 실제 파일/시작 줄이다. 함수 존재·정적 호출과 실행 검증을 구분한다.

| ID | 코드 위치 | 확인한 내용 |
|---|---|---|
| C01 | [ScenarioEngineEnvUtil.c:155](https://github.com/GeonMyoung/ScenarioEngine/blob/8e68bd08d2a3657d9c0a14d19d0204e3be491c96/scenarioengine/src/ScenarioEngineEnvUtil.c#L155) | 경4 category→Iso14827TestHelper |
| C02 | [CommandMsgProc.c:707](https://github.com/GeonMyoung/ScenarioEngine/blob/8e68bd08d2a3657d9c0a14d19d0204e3be491c96/iso14827testhelper/src/Iso14827TestHelperCommandMsgProc.c#L707), [같은 파일:578](https://github.com/GeonMyoung/ScenarioEngine/blob/8e68bd08d2a3657d9c0a14d19d0204e3be491c96/iso14827testhelper/src/Iso14827TestHelperCommandMsgProc.c#L578), [같은 파일:1608](https://github.com/GeonMyoung/ScenarioEngine/blob/8e68bd08d2a3657d9c0a14d19d0204e3be491c96/iso14827testhelper/src/Iso14827TestHelperCommandMsgProc.c#L1608) | centerClient2rse 설정/선택 시험, single·registered 샘플, Rx API 선택 |
| C03 | [Client1.c:428](https://github.com/GeonMyoung/ScenarioEngine/blob/8e68bd08d2a3657d9c0a14d19d0204e3be491c96/iso14827testhelper/src/Iso14827TestHelperScenarioClient1.c#L428), [같은 파일:656](https://github.com/GeonMyoung/ScenarioEngine/blob/8e68bd08d2a3657d9c0a14d19d0204e3be491c96/iso14827testhelper/src/Iso14827TestHelperScenarioClient1.c#L656) | 정상/잘못된/중복 로그인 및 오류→성공 분기 |
| C04 | [Client1.c:512](https://github.com/GeonMyoung/ScenarioEngine/blob/8e68bd08d2a3657d9c0a14d19d0204e3be491c96/iso14827testhelper/src/Iso14827TestHelperScenarioClient1.c#L512) | heartbeat 처리와 취소 이후 전환 |
| C05 | [TechnicalRegulation2MsgStructAPI.c:478](https://github.com/GeonMyoung/ScenarioEngine/blob/8e68bd08d2a3657d9c0a14d19d0204e3be491c96/technicalregulation2/src/TechnicalRegulation2MsgStructAPI.c#L478) | ITSK EAM별 Tx/Rx API 집합 |
| C06 | [Client1.c:1095](https://github.com/GeonMyoung/ScenarioEngine/blob/8e68bd08d2a3657d9c0a14d19d0204e3be491c96/iso14827testhelper/src/Iso14827TestHelperScenarioClient1.c#L1095), [같은 파일:1349](https://github.com/GeonMyoung/ScenarioEngine/blob/8e68bd08d2a3657d9c0a14d19d0204e3be491c96/iso14827testhelper/src/Iso14827TestHelperScenarioClient1.c#L1349), [같은 파일:1551](https://github.com/GeonMyoung/ScenarioEngine/blob/8e68bd08d2a3657d9c0a14d19d0204e3be491c96/iso14827testhelper/src/Iso14827TestHelperScenarioClient1.c#L1551) | 식별 매핑, BSM 디코딩/변환/판정 요청, 도메인·OID·sid 검사·구독 추출/취소 |
| C07 | [GitsnAsnUtil.c:5526](https://github.com/GeonMyoung/ScenarioEngine/blob/8e68bd08d2a3657d9c0a14d19d0204e3be491c96/GitsnAsnUtil/src/GitsnAsnUtil.c#L5526) | MessageFrame에서 value와 ID 추출. 호출부의 consume_sz 선언만으로 전체 소비 검증을 주장하지 않음 |
| C08 | [EnvUtil.c:418](https://github.com/GeonMyoung/ScenarioEngine/blob/8e68bd08d2a3657d9c0a14d19d0204e3be491c96/iso14827testhelper/src/Iso14827TestHelperEnvUtil.c#L418) | testIdx·testName·raw/data·time(NULL) 판정 요청 |
| C09 | [Client1.c:1494](https://github.com/GeonMyoung/ScenarioEngine/blob/8e68bd08d2a3657d9c0a14d19d0204e3be491c96/iso14827testhelper/src/Iso14827TestHelperScenarioClient1.c#L1494), [같은 파일:1664](https://github.com/GeonMyoung/ScenarioEngine/blob/8e68bd08d2a3657d9c0a14d19d0204e3be491c96/iso14827testhelper/src/Iso14827TestHelperScenarioClient1.c#L1664) | 판정 OK/오류→상태, 완료 목록·상태 전환 |
| C10 | [DomainMgr_main.c:1357](https://github.com/GeonMyoung/ScenarioEngine/blob/8e68bd08d2a3657d9c0a14d19d0204e3be491c96/ItsIso14827/src/ItsIso14827DomainMgr_main.c#L1357) | 접속 함수의 인자·할당·태스크 호출 오류와 거부 사유 반환 |
| C11 | [Client1.c:297](https://github.com/GeonMyoung/ScenarioEngine/blob/8e68bd08d2a3657d9c0a14d19d0204e3be491c96/iso14827testhelper/src/Iso14827TestHelperScenarioClient1.c#L297), [같은 파일:927](https://github.com/GeonMyoung/ScenarioEngine/blob/8e68bd08d2a3657d9c0a14d19d0204e3be491c96/iso14827testhelper/src/Iso14827TestHelperScenarioClient1.c#L927) | 구독 준비/전송·로그 처리와 잘못된 구독의 성공 분기 |
| C12 | [Client1.c:1751](https://github.com/GeonMyoung/ScenarioEngine/blob/8e68bd08d2a3657d9c0a14d19d0204e3be491c96/iso14827testhelper/src/Iso14827TestHelperScenarioClient1.c#L1751), [같은 파일:1899](https://github.com/GeonMyoung/ScenarioEngine/blob/8e68bd08d2a3657d9c0a14d19d0204e3be491c96/iso14827testhelper/src/Iso14827TestHelperScenarioClient1.c#L1899) | 취소, ACK 지연·첫/두 번째 Publication 처리 |
| C13 | [Client1.c:2081](https://github.com/GeonMyoung/ScenarioEngine/blob/8e68bd08d2a3657d9c0a14d19d0204e3be491c96/iso14827testhelper/src/Iso14827TestHelperScenarioClient1.c#L2081), [같은 파일:2469](https://github.com/GeonMyoung/ScenarioEngine/blob/8e68bd08d2a3657d9c0a14d19d0204e3be491c96/iso14827testhelper/src/Iso14827TestHelperScenarioClient1.c#L2469) | 로그아웃/연결 종료 상태, STOP timer 정리 진입점 |
| C14 | [SessionMgr_main.c:149](https://github.com/GeonMyoung/ScenarioEngine/blob/8e68bd08d2a3657d9c0a14d19d0204e3be491c96/ItsIso14827/src/ItsIso14827SessionMgr_main.c#L149), [같은 파일:772](https://github.com/GeonMyoung/ScenarioEngine/blob/8e68bd08d2a3657d9c0a14d19d0204e3be491c96/ItsIso14827/src/ItsIso14827SessionMgr_main.c#L772) | CRC 정책 분기와 DATEX 인코딩/TCP 전송 기반 |

## 9. 재현 기준과 검토 기록

- 경4 HWP SHA-256: `93d78241b4c6a49727f8bab5133ad6df5e8d4becaedae6f115706cc4cd6a6964`. 기준·참조판·코드 차이는 [기존 A04](https://github.com/GeonMyoung/ScenarioEngine/blob/80df308e4de5d0f968e03bfd3b8e8d5f092be262/doc/gyeong4/2026-v2.1/A04-implementation-gap.md), [A05](https://github.com/GeonMyoung/ScenarioEngine/blob/80df308e4de5d0f968e03bfd3b8e8d5f092be262/doc/gyeong4/2026-v2.1/A05-open-decisions.md)와 연결한다.
- ITSK-00100-3_2021v2 PDF SHA-256: `05ee08ab9aef3813e4c5b5a80f6fbb447b556c3c1a6394d54aecdcdfe61cf5ba`. 31 PDF 면 중 본문 p.8/21/22/25는 PDF 12/25/26/29면이다. 기존 확보본을 pypdf layout 모드로 추출했고 NUL 공백은 읽기 표시에서만 공백으로 처리했다. 표 3-6의 선택 여부는 같은 면의 ASN.1 표 3-7과 대조했다. 전체 원문·추출은 로컬에만 유지한다.
- 범위는 [GM-86 개발 기준](development-scope.md)을 따른다. DB·SUT 업무 알고리즘·RF 성능 개발은 포함하지 않으며 외부 API·필수 시험 지원을 배제하지 않는다.
- 검증 범위: 실제 등록·호출·분기 정적 대조, 문서 내 K/B/N 분류와 V/H 점검 연결, 코드 앵커·참조 ID·원문 판/해시 대조. 동적 테스트를 통과한 것으로 기록하지 않는다.
- 이번 점검에서 재사용 4개·보완 7개·신규 시험 항목 후보 1개를 정리했다. SUT 재점검 V01~V06과 시험기 자체 점검 H01~H05는 이후 실행할 명세이며 결과는 모두 미실행이다.

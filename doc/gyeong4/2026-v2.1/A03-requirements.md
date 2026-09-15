# A03 — 요구사항·인코딩·시간 분석

관련 업무: **GM-64 / A03**. 선행: [A01](A01-baseline-and-structure.md), [A02](A02-interface-scope.md).

## 1. 사전과 판정 원칙

- [메시지·OID 사전](A03-message-catalog.md): 제3장 OID 36개, 제4장 메시지 메타데이터 30개(`R-M*`).
- [필드 사전](A03-field-dictionary.md): 제4장 19개 명시적 필드표의 **381개 필드/구조/생략 표시**와 부록 Ⅱ의 **62개 프로파일 행**. 제4장 11개 준용 메시지표는 아래 §3에서 원전 의존성을 명시한다.
- `규정값`은 본문/필드표에 명시된 값, `예시값`은 구문 예제에만 있는 값, `참고설정`은 ‘TIM 참고사항’ 표의 설정이다. `추정/INTERPRETATION`은 구현상 필요하지만 문서가 확정하지 않은 해석이다.
- 공란·`-`·생략기호는 **NOT EXPLICITLY SPECIFIED IN THE DOCUMENT**로 취급한다. JSON이라는 이유로 모든 NUMBER를 number literal로 강제하거나, VARCHAR2(12)를 12 bytes로 단정하지 않는다.
- 구조·범위 확인과 통과 판정은 다르다. 충돌/참조 미확보 요구사항은 A05 질의가 해결되기 전 통과/실패 기준으로 확정하지 않는다.

## 2. OID와 식별 계층

| ID | 근거 | 추출·분석 | 분류 / 처리 |
|---|---|---|---|
| R-ID01 | 제3장 표 3-4~6 | 목록의 공통 `1.2.410.200053.2.143.3` 이후 F2C=1, C2C=2, F2F=3, 역할과 정보종류별 하위 식별 | 규정값; 그림 3-1의 표준번호22020과 불일치(Q06) |
| R-ID02 | 제3장 표 3-4 ↔ 표 4-6/9/10 | `.1.2.1.3`은 목록 RSA/상세 MAP, `.1.2.1.4`는 목록 TLSM/상세 RSA | 충돌 Q06; 이름 기반 자동 라우팅 보류 |
| R-ID03 | 표 4-3~10/30/31 예제 | EAM `1.0.15784.1.0.1/.2`, `1.0.14827.1.1.0`은 규격의 메시지 OID와 다른 계층 | 예시값 + 해석; OID를 전역 치환하지 않음(Q11) |
| R-ID04 | 부록 Ⅰ message_id | V2N message_id는 디코딩된 V2X messageId와 독립적인 컨테이너 식별자 | 규정값; 두 필드를 별도 보존 |
| R-ID05 | 표 4-3~10/30/31 및 부록 Ⅰ | PSID, 확장 EAM payload 유형, V2N message_id, MessageFrame messageId를 각각 관측 | 구현 해석; 코드표와 매핑은 REF07/REF09/KS 판 대조 필요 |

그림 3-1(p.10)을 확대 대조하면 표준번호 노드가 **22020**으로 표시되어 목록의 **143**과 다르다. 따라서 그림을 정답 트리로 사용하지 않으며 Q06에서 정정을 질의한다. JSON/API/DB 경로에도 표가 OID를 붙이지만, 그 숫자를 JSON body나 Binary 헤더에 반드시 실으라는 공통 wire 규칙은 없다(Q11).

## 3. 참조로 정의된 V2X 메시지

다음 표는 11개 상세 메시지표 전체를 포함한다. 해당 표들은 메타데이터와 긴 예제를 제공하고 필드의 규정 정의는 외부 표준을 준용한다. 그러므로 예제 키만으로 ‘모든 필드 추출 완료’ 또는 해당 KS 적합을 주장하지 않는다.

| ID | 해당 R-M / 상세 절 | 원문 준용 근거 | 추출 가능한 것 / 남는 것 |
|---|---|---|---|
| R-REF01 | R-M03/07, 1.2.2.1·1.3.1 | KS R 1600-2 제7절 BSM | 역할·OID·1초·DATEX/UPER는 확인. coreData/partII/regional의 전체 M/O·범위·단위는 채택판 원전 필요 |
| R-REF02 | R-M04/30, 1.2.3.1·2.7.1 | 상세는 KS R 1600-3 제7절, 제1장 5.2 비교표는 SAE J2735 SPaT | SPaT/TLS 확장 예제의 적용과 SAE 2020/KS 1600-3 관계 확인 필요(Q02/Q11) |
| R-REF03 | R-M05/08, 1.2.3.2·1.4.1 | KS R 1600-5 제7절 TIM, 부록 Ⅱ | 부록 프로파일의 강화 조건은 추출. 기본 TIM 구문·길이·한국 확장 전체는 REF05 필요 |
| R-REF04 | R-M06/10, 1.2.3.3·1.4.3 | KS R 1600-5 제7절 RSA | 이벤트·OID·예제 확인. 원전의 range/OPTIONAL·단위 미확보 |
| R-REF05 | R-M09/31, 1.4.2·2.7.2 | KS R 1600-3 제7절 MAP/TLSM | 기준 판 불일치 해소 후 코드 ASN.1과 대조 |
| R-REF06 | R-M17, 2.2.1 | 상세는 ITSK-00144-2의 ‘2. I2X 연계장치와 교통안전시설 서버 간 정보교환’, 제1장 비교표는 교통정보 MAP/TIM | 목록 JSON과 상세 BER/UPER 충돌, 요구 2024.12판 원문 미확보(Q02/Q03/Q07) |

현재 확보된 참조 PDF를 모두 채택 기준으로 사용할 수 있는 것은 아니다. REF07(ITSK-00100-3:2021v2)은 확보했고 REF06 후보는 2023판이었다. 원전 확보 상태는 A01을 따른다.

## 4. MQTT 요구사항

| ID | 근거 | 요구·관측 대상 | 값 분류 / 미정 |
|---|---|---|---|
| R-MQ01 | 1.2.1.1, p.15 | 차량=V2N Device, 센터=App Server/Public Center. 양쪽 모두 MQTT Client, 별도 Broker | 규정값; Broker가 센터 자체라는 가정 금지 |
| R-MQ02 | 1.2.1.2, 표 4-2 | 차량→센터 `V2N/{quadtreekey}/BSM`; 센터→차량 말단 `SPaT`, `RSA`, `TIM` | 규정값; 대소문자 보존 |
| R-MQ03 | 1.2.1.2 | 격자키는 차량 현재 위치에 따라 동적 결정, 구독 시 `V2N/{quadtreekey}/#` 활용 가능 | 규정값; wildcard는 허용 설명이며 필수 구독 방식 아님 |
| R-MQ04 | 1.2.1.3·그림 3-3, p.16 | 식별자를 Client ID로 CONNECT/CONNACK, 수신 Topic SUBSCRIBE/SUBACK, PUBLISH | 규정값; ID 형식·QoS·인증·TLS·retain은 REF09 또는 합의 필요 |
| R-MQ05 | 1.2.1.3 | 격자 변경 시 기존 Topic 해지·신규 재구독; 통신 두절 시 LWT와 재접속; 종료 시 DISCONNECT | 규정값; 중첩 구독 허용 시간·LWT 내용·재시도 간격 미정 |
| R-MQ06 | 1.2.1.2 예시 | `1321103202`와 해당 Topic 문자열 | 예시값; 길이 10자리·고정 지역·전체 격자 깊이를 강제할 근거 아님 |
| R-MQ07 | 1.2.1.4 ↔ 1.2.2~1.2.3·표 3-1 | MQTT payload와 AP-DATEX 경로의 우선·대체·병행 관계 | 미결정 Q04; 두 계층을 임의로 중첩하지 않음 |

## 5. V2N type 0x04 필드 사전

근거: **1.2.1.4, 부록 Ⅰ 표 Ⅰ-1, p.136**. 규정값은 필드 폭과 명시된 상수다. M/O·반복 열은 없다. 명시된 단일 메시지 유형을 반복 메시지 목록으로 확대하지 않는다.

| ID | 필드 | 폭·형식 | 검증 의미 / 미확정 값 |
|---|---|---|---|
| R-VN01 | container_type | 8 bits unsigned integer | **0x04** 명시 |
| R-VN02 | version | 8 bits unsigned integer | type별 버전 관리; 사용할 버전값 미지정 |
| R-VN03 | fid | 16 bits unsigned integer | 서비스 유형; REF09 표 4-4 값 필요 |
| R-VN04 | standard_type | 8 bits unsigned integer | 지역/국가 표준 유형; REF09 표 4-5 필요 |
| R-VN05 | sem_length | 8 bits unsigned integer | SEM 길이. 단위와 flags 포함 여부 미기재 |
| R-VN06 | flags | 8 bits bit-field | 존재/상태 표시. 비트 위치·예약 비트·0의 의미 미기재 |
| R-VN07 | service enhancement metadata | variable | REF09 표 4-7 필요; 선택성·내용·길이 관계 미정 |
| R-VN08 | message_id | 8 bits unsigned integer | V2N 레벨 식별자. V2X messageId와 독립 |
| R-VN09 | psid | 32 bits unsigned integer | 메시지 유형 코드표 REF09 표 4-6 필요 |
| R-VN10 | message_length | 32 bits unsigned integer | message 길이. 길이 단위·최대 수용 크기·포함 범위 미기재 |
| R-VN11 | message | variable | 개별 메시지. type별 codec 및 MessageFrame 포함 여부 확인 |

**INTERPRETATION:** 고정 폭 필드 합계는 128 bits(16 bytes)다. 이는 SEM과 message를 제외한 산술 합계이며, wire offset/총길이 공식의 확정이 아니다. byte order, bit numbering, length 단위, SEM 조건, 잘린 입력·초과 길이·미지원 코드 응답은 Q05로 남긴다. uint32의 표현 가능 최대값을 안전한 수신 버퍼 최대치로 사용해서는 안 된다.

## 6. TIM 통행지시 프로파일

근거: **부록 Ⅱ-1 표 Ⅱ-2(p.137~139), Ⅱ-2 표 Ⅱ-2(p.141~142)**. 상세 M/O와 반복수는 필드 사전의 `FA-TIM-S-*`, `FA-TIM-L-*`에서 각각 추적한다.

| ID | 관련 필드 | 경4 제약·분석 | 값 분류 / 남은 일 |
|---|---|---|---|
| R-TIM01 | packetID, startYear, msgId | KS 열 O/O/C → ITSK 열 모두 M, 반복 1 | 규정값; 서비스 프로파일 강화 |
| R-TIM02 | TravelerDataFrame, GeographicalPath, item | ITSK 반복 각각 1. TravelerDataFrame은 본문에도 한 프레임 사용 명시 | 규정값. 다른 반복 8/32의 최대치/정확한 개수 의미는 원전 대조(Q20) |
| R-TIM03 | msgId | 제한속도 `0x0C01`, 차로변경 `0x0C02`, `futherInfoID` 표기 | 규정값. ASN.1의 `furtherInfoID`와 원문 오기 구분 |
| R-TIM04 | regional/regionId, regExtValue | 한국 regionId=4, GeographicalPath-KOR. linkID 자리에 LaneBeltID 사용 | 규정값; ID 문자열 형식/길이/등록체계 미정 |
| R-TIM05 | notUsed1/2/3 | 모두 0 | 규정값; 보존 필드 검사 |
| R-TIM06 | startTime, durationTime | UTC 시작시각, 지속기간 분 단위 | 규정값; 연도 경계·시각 인코딩은 참조 KS 필요 |
| R-TIM07 | itis | 제한속도 7443/7444, 차로변경 7427/7428/7436 제시 | 규정값 후보 집합; 서비스와 각 코드의 적용 조건 Q20 |
| R-TIM08 | frameType, content | 참고표는 roadSignage; 제한속도 speedLimit, 차로변경 genericSign | 참고설정(규범성 미확정), Q20 |
| R-TIM09 | durationTime=30, priority=7 | 부록의 ‘TIM 참고사항’ 설정값 | 참고설정; 모든 통행지시에 고정 강제할지 미정(Q20) |
| R-TIM10 | regional/TravelerInformation-KOR/additionalInfo | 제한속도 프로파일에 ITSK 반복 1/8, dataFrameIndex M·1, events O·1, text O·1 | 규정값; 선택 부모 내 자식 M을 전역 필수로 확대하지 않음 |
| R-TIM11 | events/text, linkID 예시 | `SPEED 50`, `BeltId_0001` | 예시값. 속도 50·해당 식별자를 고정하지 않음 |
| R-TIM12 | content C, regional O 및 LaneBeltID 전달 | 조건부/선택 표기와 통행지시 서비스에 필요한 내용·대상 지역의 관계 | 미결정 Q20; C의 조건과 regional 생략 시 동작 확인 |

같은 기본 TIM이라도 부록 제한속도·차로변경 프로파일은 별도 검증 대상이다. 부록 방향은 센터→차량이다. 센터→RSE/F2F에 동일 프로파일을 적용할지는 메시지 제목의 ‘통행지시 포함’과 역할 책임을 함께 확정한다(Q08/Q20).

## 7. JSON/XML·DB·Binary 요구사항

| ID | 근거 | 검사 대상 및 주의 |
|---|---|---|
| R-SC01 | 표 4-1 | time_stamp double/sec, msg_count `unit8`/(0,255), 객체·돌발 개수와 중첩 구조. `unit` 오기·미표기 M/O·이름 차이는 Q13 |
| R-SC02 | 표 4-11~16·22~23 | SQL형 이름·NUMBER 정밀도/길이·TIMESTAMP/DATE 표기를 보존. DB 컬럼·JSON key·XML element 매핑과 null/공란은 Q12 |
| R-SC03 | 표 4-18 | 시간·objectData·위치/신뢰도·weatherData·광도·안전 메시지·시설 상태 필드. base64 범위·열거/범위·센티넬은 Q14~16 |
| R-SC04 | 표 4-19/20 | 장치/서버 상태·포트(0..65535)·온습도 범위·연결 상태. 의미가 뒤집힌 영문과 반복 DATAMANAGER_STTUS는 Q18 |
| R-SC05 | 표 4-21 | time, node_link, lane_no, lane_speed/volume/density; 타입·단위·시간과 예제 대조(Q17) |
| R-SC06 | 표 4-24~29 | MSGNo 1 byte, MSGSize 2 bytes, MSGStart-End/MSGSeqNo 각1 byte. CHAR/INTEGER/FLOAT/DOUBLE 폭을 보존하되 C struct packing을 wire 규격으로 간주하지 않음(Q19) |
| R-SC07 | 표 4-24~29 | LRC·개수 필드·전문 분할·시작/종료·반복을 관측. TOD의 생략기호와 LRC 누락/예제는 별도 질의(Q19) |
| R-SC08 | 전체 상세표와 예제 | 숫자→문자열, 대소문자, enum 명칭, 배열/단일 객체, 선택필드 누락, 범위 경계·예외값을 분리 확인. 예제 디코딩 JSON이 BER/UPER wire를 JSON으로 바꾸는 근거는 아님 |

## 8. 전송·응답·데이터 시간

| ID | 근거 | 추출값 / 미정 |
|---|---|---|
| R-TM01 | 표 3-1~3, 상세표 | 주기 1초/1분/5분/10초/10분/1시간 및 발생시/요청시/통신시작시. 경로별 두 값은 A02·메시지 사전에 보존 |
| R-TM02 | 표 3-1 현장 돌발 | 발생시 100ms 이내. 사건 검지/전송/수신 중 기산점·종료점 불명확(Q10) |
| R-TM03 | 표 3-2·표 4-24~26 | 통신 시작/운영 변경/요청 후 1초 이내. 트리거의 실제 관측 방법 필요 |
| R-TM04 | 표 3-2 센터→신호운영·표 4-28/29 | 요청 100ms/발생 500ms, 상세 BSM 1초/돌발 발생시; 병합 셀 대응과 주기 충돌(Q09) |
| R-TM05 | 표 4-1·11~29, 부록 Ⅱ | double sec, 문자열 YYYYMMDDhhmmss, SQL TIMESTAMP, 분 단위 TIM 시간, 분리 년월일 필드는 서로 다른 시간 표현. 표에 없는 UTC/KST·epoch·단위 환산을 임의 지정하지 않음 |
| R-TM06 | 전체 주기·응답 요구 | 허용 jitter/시계 오차/유실/재전송/최소 관찰 횟수·warm-up·타임아웃 후 반응은 본 문서에 명시되지 않음. 시험 설계의 미정 조건(Q10) |

후속 시험 로그에는 가능하면 동일 사건의 생성·전송·브로커 수락·에이전트 수신·SUT 처리 시각과 시계 동기 오차를 구분한다(INTERPRETATION). 일반 로그 시간차를 곧바로 표준의 지연 시간으로 보지 않는다.

## 9. A03 완료 조건 검토와 한계

제3장 목록·OID, 제4장의 모든 명시적 필드표·메타데이터, MQTT 문장, 부록 Ⅰ·Ⅱ의 제약에 고유 ID·근거·값 분류를 부여했다. 자동번호와 병합 셀을 복원했고 예시값을 분리했다. 준용 메시지 11개 표의 원전 미확보는 명시적 요구 의존성으로 남겼다.

**남은 사항:** KS·SAE·ITSK-00150-2 등 해당 판 원전을 확보해야 준용 필드 전체 범위·인코딩·단위의 대조를 끝낼 수 있다. 따라서 ‘제공 HWP에 명시된 요구사항 추출 및 미정 의존성 등록’은 제출 완료이며, ‘모든 참조 원문을 포함한 필드 규칙 확정’은 미완료다. 중앙 검토자는 이 경계를 기준으로 GM-64 완료 여부를 판단해야 한다.

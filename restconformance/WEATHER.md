# 기상정보 요청·제공 시험

업무 데이터는 ITSK-00143-3 제4장 표 4-15, API 호출 규칙은 기상청 공식 명세, 시험방법은 ITSK-00143-4 제4장 1.1.1·1.2.1을 적용한다. REST-STANDARD-004·REST-AUTO-001에 따른 에뮬레이터 대상 개발 검증이다.

| 설계 / 등록 ID | 시험 대상 | 시험 시스템 | case |
|---|---|---|---|
| SC09 / 66 | 통합교통관제시스템, HTTP Client | 기상청, HTTP Server | `weatherServer2center_v1` |
| SC30 / 67 | 기상청, HTTP Server | 통합교통관제시스템, HTTP Client | `centerClient2weather_v1` |

C2C / REST JSON / WTRT_INFO. 업무 정보는 기상청 → 통합교통관제시스템으로 전달된다.

## 명세와 적용 기준

[공공데이터포털 기상청 단기예보 조회서비스](https://www.data.go.kr/data/15084084/openapi.do)와 그 페이지의 `기상청41_단기예보 조회서비스_오픈API활용가이드_2607.zip` 안 `...260623.docx`를 확인했다. 원문·해시는 `.local/weather1/source` 및 [계약 기록](contracts/weather-standard-profile.json)에 보관했다. 기상청 업무 API는 호출하지 않았다.

| 구분 | 적용 |
|---|---|
| method | GET |
| 기본 경로 | `/1360000/VilageFcstInfoService_2.0/getUltraSrtNcst` |
| 명시 선택 가능한 경로 | `/1360000/VilageFcstInfoService_2.0/getUltraSrtFcst` |
| 인증 | 기본 `serviceKey`, 명시 설정으로 `ServiceKey`도 지원. 전달받은 두 문서의 대소문자 표기를 자동으로 합치지 않는다. |
| 조회변수 | pageNo, numOfRows, base_date(YYYYMMDD), base_time(hhmm), nx, ny, dataType=JSON |
| 요청 본문 | 없음 |
| 응답 업무코드 | 정상 00, 자료 부재 03, 잘못된 변수 10, 키 누락 20, 미등록 키 30, 미존재 서비스 12, 서버 처리 오류 01 |

인증키는 **디코딩된 원문**을 설정하고 HTTP 어댑터가 한 번 URL 인코딩한다. 이미 인코딩된 키를 다시 넣지 않는다. 모든 송수신 표시와 공개 조회변수 증적에서 키를 가린다. 키 누락 20은 포털의 명시 항목을 채택했고, 필수 일반 변수 누락 11과 혼동하지 않는다.

두 operation을 구현했지만 경4 운영 연계가 실제로 어느 것을 사용하는지 확정했다는 뜻은 아니다. JSON 연계이므로 생략 시 XML이 되는 dataType은 JSON으로 명시한다. 요청 시험은 준비한 경로·키·조회조건과 수신값을 비교하며 변수 순서는 무관하다. 중복·미정의 변수·GET 본문 거부는 채택한 시험 조건이다.

pageNo/numOfRows는 양의 4자리 정수, 좌표 조회변수는 정수로 검사한다. API 요청표의 nx/ny 길이 2는 예시 ny=127과도 충돌하므로 2자리 상한을 강제하지 않는다. 실제 격자 포함 여부·발표 직후 가용시간은 이번 단일 요청 시험의 자동 판정 범위가 아니다.

## 정상 데이터

가이드의 `response/header/body/items/item` 계층과 JSON 지원에 근거하여 `response.header`, `response.body.items.item[]` 구조를 채택했다. 정상 header는 문자열 resultCode=`00`, resultMsg(1~100자), body는 dataType=`JSON`, 숫자 pageNo/numOfRows/totalCount와 item 배열을 포함한다. 이 JSON 포장은 XML 예시로부터 채택한 개발 기준이며 실제 운영 JSON 원문을 확보한 것으로 표시하지 않는다.

**item의 업무 데이터는 표준 정의표를 따른다.** 기상청의 category/obsrValue·fcstValue를 표준 필드로 임의 변환하지 않는다. 표준 예시의 baseDt/fcstDt나 문자열 숫자로도 검사 기준을 바꾸지 않는다.

| 필수 필드 | 검사 기준 |
|---|---|
| baseDate, adstrdCode | 문자열 8자리, YYYYMMDD 및 실제 날짜 |
| updateDt, fcstTime | 문자열 6자리, hhmmss 및 실제 시각 |
| nx | 정수 -199999999~1800000001 |
| ny | 정수 -900000000~900000001 |
| t1h, uuu, vvv, reh, wsd | 숫자 NUMERIC(4,1) |
| rn1 | 비어 있지 않은 문자열, 최대 10자 |
| sky | 숫자 정수 코드 1·3·4 |
| pty | 정수 0~7 |
| lgt, vec | 비어 있지 않은 문자열, 최대 3자 |

숫자는 원문 십진값으로 정밀도를 검사하며 문자열을 숫자로 바꾸거나 반올림하지 않는다. 동등한 지수·후행 0 표기는 허용한다. 정의표에 없는 습도 0~100·풍속 부호 등의 업무 범위를 추가하지 않는다. adstrdCode의 날짜 정의, lgt의 풍향 설명 등은 원문 의미 확인이 필요한 이슈로 남겼다.

응답 페이지 번호·페이지당 건수는 요청과 일치해야 한다. 실제 item 수는 `min(numOfRows, max(0, totalCount-(pageNo-1)*numOfRows))`와 비교한다. 한 페이지 요청을 검사하며 모든 페이지를 자동 수집했다고 표시하지 않는다.

## 오류와 선택 항목

**HTTP와 업무 결과코드를 각각 검사한다.** HTTP 200이라도 resultCode=`03`이면 자료 부재 오류다. 정상 00+빈 item은 추가 빈 정상응답이며 이를 대체하지 않는다. 오류 본문의 resultCode와 비어 있지 않은 resultMsg를 확인하고, 오류에 정상 레코드가 포함되면 실패한다. resultMsg 문구의 완전 일치까지 요구하지 않는다.

HTTP 매핑은 명세가 정하지 않아 업무 오류 200, 경로 오류 404, 서버 오류 500을 프로젝트 기본값으로 적용한다. 필요하면 UI의 해당 HTTP 코드 설정을 바꾼다. 이 매핑은 prj22의 HTTP 상태별 검사 구조를 참고해 적용한 기상정보 개발 기준이며 prj22가 기상청의 200+03 계약을 정의했다는 뜻은 아니다.

| 대상 | 시험방법 요구사항 확인 | 추가 검증 |
|---|---|---|
| 통합교통관제시스템 | 정상 요청, 자료 부재 오류응답 조건의 요청 | 조회변수 오류·경로 오류·서버 오류·빈 정상·손상 응답 조건의 요청 |
| 기상청 | 정상 제공, 잘못된 조회변수 오류응답, 자료 부재 오류응답 | 인증키 누락·불일치, 미존재 경로, 빈 정상응답 |

각 7항목, 최소 10회 반복. 잘못된 조회변수 자극은 nx=`invalid`다. 정상 제공·자료 부재·빈 정상응답은 서로 다른 준비 조건으로 별도 실행한다. 빈 정상응답 204는 제공시험의 추가 설정이며 요청시험의 빈 정상 조건은 200이다. 인증 오류 설정은 제공시험, 서버 오류 설정은 요청시험에 사용한다.

## 실행·판정 범위

- [등록 파일](registration/)의 case별 example.json과 tsb를 사용한다. `emulator/weather_sut.py --role requester`는 통합교통관제시스템, `--role provider`는 기상청 역할이다. `--port`, `--output`은 필수다. 인증키는 `REST_TEST_CREDENTIAL` 환경변수로 전달한다.
- SC09는 엔진의 수신 준비 후 요청 에뮬레이터를 실행한다. SC30은 제공 에뮬레이터를 먼저 준비한다. 경로·인증변수명·조회변수·요청 횟수를 양측에 맞춘다. `--data normal/absent/empty`로 제공 자료를 구분한다.
- 각 회차의 모든 요청·응답을 JSON 시험 데이터로 표시·저장한다. 긴 자료도 분할해 생략 없이 전송한다.
- 엔진이 관측한 요청 유효성·응답 전송 또는 응답 코드·데이터 검사를 판정한다. 대상 내부 처리는 직접 관측하지 않았다면 명시한다. 별도 증적 제출은 필수가 아니며 상대 기록 자동 대조는 선택 기능이다.
- COMPLETE를 쓰지 않는다. 상세 START→SUCCESS/FAIL/STOPPED, MainScenario 최종 결과 뒤 FINISH 1회다. 실제 1시간 연계주기·실장비 상호운용·기상청 운영 접속은 별도 단계다.

[검증 결과](../doc/gyeong4/2026-v2.1/weather-verification-20260925.md)

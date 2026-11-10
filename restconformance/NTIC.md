# NTIC 차량검지정보 요청·제공시험

| 설계 / 등록 | 시험 이름 | 시험 시스템 | 시험 대상 |
|---|---|---|---|
| SC08 / [62](https://106.250.189.37:8443/test/scenario/62) | 통합교통관제시스템 차량검지정보 요청시험 | NTIC HTTP 서버 | 통합교통관제시스템 HTTP 클라이언트 |
| SC29 / [63](https://106.250.189.37:8443/test/scenario/63) | NTIC 차량검지정보 제공시험 | 통합교통관제시스템 HTTP 클라이언트 | NTIC HTTP 서버 |

정보 방향은 NTIC → 통합교통관제시스템이다. category는 ITSK-00143-REST-V1, case는 각각 nticServer2center_v1 / centerClient2ntic_v1이다.

## 호출과 데이터 검사

- GET, apiKey·getType=json을 각각 한 번 사용하며 요청 본문은 없다. 조회변수의 순서는 제한하지 않는다.
- 기본 경로는 /vdsInfo다. 공식 HWP의 이중 슬래시 예시를 사용할 때는 api_path를 //vdsInfo로 명시한다. 요청·검사 과정에서 경로를 자동으로 바꾸지 않는다.
- 제3부 표 4-12의 필수 7개 항목, ID 길이, 수집일시와 NUMBER 자릿수를 검사한다. 숫자 문자열을 숫자로 변환하거나 길이가 긴 실제 API 예시를 잘라 통과시키지 않는다.
- HTTP 상태와 본문의 resultCode는 별개다. 파라미터 오류 4002, 인증키 오류 4005, 경로 오류 4004, 서버 오류 4009를 각 오류 조건에서 확인한다.
- 자료 부재의 NTIC 고유 업무 코드는 정의하지 않았다. 같은 정상 경로와 자료 0건 준비 조건에서 선택한 HTTP 오류 상태를 확인한다. 200 빈 items는 별도 추가 시험이다.

요청측 7항목은 정상 요청, 자료 부재 오류, 400/404/500 오류응답 조건, 빈 정상응답, 손상 응답 조건이다. 제공측 7항목은 정상 제공, 잘못된 getType, 자료 부재 오류, 인증키 누락/불일치, 미존재 경로, 빈 정상응답이다. 각 항목은 10회 이상 교환한다.

## 적용한 개발 기준과 남은 계약 차이

[공식 API 기술기준](https://www.its.go.kr/file/opendata/vds/vds_api.hwp)은 요청변수·출력 필드·업무 오류 코드를 제공하지만 전체 정상 JSON 포장과 오류별 HTTP 상태를 명시하지 않는다. 현재 구현은 **루트 items 배열을 가진 객체**를 개발용 응답 구조로 채택했다. 정상 응답의 resultCode/resultMsg/totalCount는 제공된 경우 검사하고, 알려진 오류의 본문은 resultCode와 오류 메시지를 확인하도록 구성했다. HTTP 400/401/404/500 등은 prj22를 참고한 프로젝트 기본값이며 NTIC가 해당 HTTP 상태를 공식 지정했다는 뜻은 아니다.

| 차이 | 현재 적용 |
|---|---|
| 표의 숫자 타입과 API·표 예시의 숫자 문자열 | 표의 NUMBER 적용 |
| VDS ID 최대 10자와 예시 11자 | 최대 10자 검사 |
| 링크 ID 최대 20자와 다중 링크의 긴 문자열 예시 | 최대 20자 검사. 목록 분할·ID 변환은 하지 않음 |
| 전체 JSON 외곽 구조 미명시 | 개발 기준인 루트 items 사용. body/header 포장을 실제 계약으로 단정하지 않음 |
| 공식 HTML은 resultCode 0/1, 버전이 있는 HWP는 상세 400x | HWP v1.0(2026-08-07)의 상세 오류 코드 채택 |
| 제3부 5분 연계와 API 수집 주기 설명 | 단일 요청 반복 시험으로 갱신 주기를 판정하지 않음 |

위 차이는 실장비·운영 API 연계 시 확인해야 한다. 운영 NTIC API에 인증키를 넣어 호출한 검증은 수행하지 않았다. 기존 엔진의 본문 1 MiB 제한도 유지하므로 전체 운영 데이터셋 수용량을 검증한 것으로 보지 않는다.

[기계 판독 가능한 적용 기준](contracts/ntic-standard-profile.json)

## 실행

엔진 설정은 registration의 두 example.json을 참고한다. 독립 상대 프로그램은 emulator/ntic_sut.py다. 현재는 이 프로그램을 시험 대상으로 간주한다.

```powershell
# NTIC 제공측 대상: 엔진 시험 시작 전에 실행
$env:REST_TEST_CREDENTIAL = 'NTIC_LOCAL_KEY'
python -X utf8 restconformance/emulator/ntic_sut.py --role provider --port 55329 --data normal --output <새 출력 폴더>

# 통합교통관제시스템 요청측 대상: 엔진의 HTTP 수신 준비 후 실행
python -X utf8 restconformance/emulator/ntic_sut.py --role requester --port 55308 --requests 70 --output <새 출력 폴더>
```

제공측 자료 부재는 --data absent, 빈 정상응답은 --data empty로 별도 준비한다. --path로 경로를 맞추고 시험마다 새 출력 폴더를 사용한다. 실제 운영 인증키는 필요하지 않다.

REST-AUTO-001을 적용해 엔진의 직접 관측 범위로 판정한다. COMPLETE·사후 제출 대기는 사용하지 않으며 관측하지 않은 대상 내부 처리는 로그에 명시한다. 모든 송수신은 회차별 JSON 알림으로 표시한다.

[구현·검증 결과](../doc/gyeong4/2026-v2.1/ntic-verification-20260924.md)

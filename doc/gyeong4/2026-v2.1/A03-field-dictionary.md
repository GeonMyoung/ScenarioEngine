# A03 부속 — 필드 제약 사전

관련 업무: **GM-64 / A03**. [해석·요구사항](A03-requirements.md) · [질의](A05-open-decisions.md).

이 사전은 제4장의 명시적 필드표에서 검증할 기술값을 재구성했다. 원문의 설명·전문 예제는 전재하지 않았다. 각 ID는 표/행을 고유하게 가리키며, 경로는 표의 들여쓰기 기반 **위치 표시**이고 확정된 JSON key path가 아니다. 반복수·자료형·단위가 명시되지 않으면 추정하지 않는다. 제4장 표에는 별도 반복수 열이 없으므로 모든 행의 반복수는 미기재이며, `objects`, `...`, 개수 필드와 실제 반복 계약은 Q13/Q19에서 추적한다.

- `—`: 해당 셀이 비어 있거나 `-`; **NOT EXPLICITLY SPECIFIED IN THE DOCUMENT**. M/O 공란을 선택(O)으로 해석하지 않는다.
- `유효값/길이 표기`: 원문 기술값을 유지한다. NUMBER의 `(5,2)` 등을 수치 범위로 바꾸지 않는다. byte 길이와 문자 길이를 구분하고 SQL 정밀도 의미는 Q12로 보류한다.
- `규정값`: 본문 필드표에 실린 값이라는 출처 분류. 충돌 질의가 있으면 즉시 합격 기준으로 쓸 수 있다는 뜻은 아니다.
- `열거값`: 숫자·코드 집합만 재구성. 한국어/영문 의미 충돌(Q18)은 원문과 별도 대조한다.
- 참조로만 정의된 BSM/SPaT/MAP/RSA/TLSM/TSF 전체 필드는 이 문서에 없다. 원전 미확보를 [A03의 준용 계약](A03-requirements.md#3-참조로-정의된-v2x-메시지)으로 명시했다. 예제의 모든 키를 규정 필드로 승격하지 않았다.

## 표 4-1 — POL7_INCIDENT

근거: **제4장 1.1.1, 표 4-1, 시작 p.13**. 관련 질의: Q13. 아래 ID의 마지막 숫자는 표 전체 행 번호(1부터, 최초 머리행 포함)다. 출처 분류: 모든 행 `규정값`.

| ID | 표 내 필드 위치 | 자료형 | 유효값/길이 표기 | 단위 | M/O | 열거 코드 |
|---|---|---|---|---|---|---|
| F4-01-007 | time_stamp | double | - | sec | M | — |
| F4-01-008 | msg_count | unit8 | (0, 255) | — | M | — |
| F4-01-009 | Incident_Decision | - | - | — | M | — |
| F4-01-010 | number_of_objects | unit8 | - | — | — | — |
| F4-01-011 | objects.id | unit16 | - | — | — | — |
| F4-01-012 | objects.related_incident_id | unit16 | - | — | — | — |
| F4-01-013 | objects.type | unit8 | - | — | — | — |
| F4-01-014 | objects.width | double | - | m | — | — |
| F4-01-015 | objects.depth | double | - | m | — | — |
| F4-01-016 | objects.height | double | - | m | — | — |
| F4-01-017 | objects.position.X | double | - | m | — | — |
| F4-01-018 | objects.position.Y | double | - | m | — | — |
| F4-01-019 | objects.position.Z | double | - | m | — | — |
| F4-01-020 | number_of_incidents | unit8 | - | — | — | — |
| F4-01-021 | incidents.id | unit16 | - | — | — | — |
| F4-01-022 | incidents.start_time | unit16 | - | sec | — | — |
| F4-01-023 | incidents.finish_time | unit8 | - | sec | — | — |
| F4-01-024 | incidents.type_of_incident | double | - | — | — | — |
| F4-01-025 | incidents.subtype_of_incident | double | - | — | — | — |
| F4-01-026 | incidents.grade_of_incident | double | - | — | — | — |
| F4-01-027 | position_at_field | double | - | — | — | — |
| F4-01-028 | position_at_field | double | - | — | — | — |
| F4-01-029 | grade_of_incident_at_field | unit8 | - | — | — | — |

## 표 4-11 — TRAF_INFO

근거: **제4장 2.1.1.1, 표 4-11, 시작 p.63**. 관련 질의: Q12. 아래 ID의 마지막 숫자는 표 전체 행 번호(1부터, 최초 머리행 포함)다. 출처 분류: 모든 행 `규정값`.

| ID | 표 내 필드 위치 | 자료형 | 유효값/길이 표기 | 단위 | M/O | 열거 코드 |
|---|---|---|---|---|---|---|
| F4-11-007 | UTIC_L_TRF | SEQUENCE | - | — | - | — |
| F4-11-008 | UTIC_L_TRF / STDLK_ID | VARCHAR2 | 12 | — | M | — |
| F4-11-009 | UTIC_L_TRF / CLCT_DT | TIMESTAMP | (YYYY-MM-DD hh:mm:ss) | — | M | — |
| F4-11-010 | UTIC_L_TRF / UTIC_SPD | NUMBER | 7 | — | M | — |
| F4-11-011 | UTIC_L_TRF / UTIC_VOL | NUMBER | 7 | — | M | — |
| F4-11-012 | UTIC_L_TRF / TRAV_TIME | NUMBER | 5 | — | M | — |
| F4-11-013 | UTIC_L_TRF / UTIS_TRF_GRADE_CD | VARCHAR2 | 5 | — | M | A0501, A0502, A0503 |

## 표 4-12 — NTIC_VDS_INFO

근거: **제4장 2.1.1.2, 표 4-12, 시작 p.64**. 관련 질의: Q12/Q13. 아래 ID의 마지막 숫자는 표 전체 행 번호(1부터, 최초 머리행 포함)다. 출처 분류: 모든 행 `규정값`.

| ID | 표 내 필드 위치 | 자료형 | 유효값/길이 표기 | 단위 | M/O | 열거 코드 |
|---|---|---|---|---|---|---|
| F4-12-007 | NTIC_L_VDSTRF | SEQUENCE | — | — | — | — |
| F4-12-008 | NTIC_L_VDSTRF / VDS_ID | VARCHAR | 10 | — | M | — |
| F4-12-009 | NTIC_L_VDSTRF / LINK_ID | VARCHAR2 | 20 | — | M | — |
| F4-12-010 | NTIC_L_VDSTRF / VDS_LANE | NUMBER | 2 | — | M | — |
| F4-12-011 | NTIC_L_VDSTRF / COLLECT_DATE | TIMESTAMP | (YYYYMM DDhhmmss) | — | M | — |
| F4-12-012 | NTIC_L_VDSTRF / VOL | NUMBER | (5,2) | — | M | — |
| F4-12-013 | NTIC_L_VDSTRF / SPD | NUMBER | (5,2) | km/h | M | — |
| F4-12-014 | NTIC_L_VDSTRF / OCC | NUMBER | (5,2) | — | M | — |

## 표 4-13 — VDS_INFO

근거: **제4장 2.1.1.3, 표 4-13, 시작 p.66**. 관련 질의: Q12. 아래 ID의 마지막 숫자는 표 전체 행 번호(1부터, 최초 머리행 포함)다. 출처 분류: 모든 행 `규정값`.

| ID | 표 내 필드 위치 | 자료형 | 유효값/길이 표기 | 단위 | M/O | 열거 코드 |
|---|---|---|---|---|---|---|
| F4-13-007 | VDS_L_RAW | SEQUENCE | — | — | - | — |
| F4-13-008 | VDS_L_RAW / COLLECT_DATE | TIMESTAMP | (YYYYMMDDhhmmss) | — | M | — |
| F4-13-009 | VDS_L_RAW / STN_ID | VARCHAR2 | (12) | — | M | — |
| F4-13-010 | VDS_L_RAW / LANE_NO | NUMBER | (1) | — | M | — |
| F4-13-011 | VDS_L_RAW / VOL | NUMBER | (7) | — | M | — |
| F4-13-012 | VDS_L_RAW / SPD | NUMBER | (5,2) | — | M | — |
| F4-13-013 | VDS_L_RAW / OCC | NUMBER | (5,2) | — | M | — |
| F4-13-014 | VDS_L_RAW / VOL_S | NUMBER | (7) | — | O | — |
| F4-13-015 | VDS_L_RAW / VOL_M | NUMBER | (7) | — | O | — |
| F4-13-016 | VDS_L_RAW / VOL_L | NUMBER | (7) | — | O | — |
| F4-13-017 | VDS_L_RAW / ERR_CODE | NUMBER | (1) | — | M | — |
| F4-13-018 | VDS_L_RAW / LINK_ID | VARCHAR2 | (12) | — | M | — |
| F4-13-019 | VDS_L_RAW / VDS_ID | VARCHAR2 | (12) | — | M | — |
| F4-13-020 | VDS_L_RAW / STN_LOCATION | VARCHAR2 | (50) | — | M | — |

## 표 4-14 — SMT_L_RAW_INFO

근거: **제4장 2.1.1.4, 표 4-14, 시작 p.68**. 관련 질의: Q12. 아래 ID의 마지막 숫자는 표 전체 행 번호(1부터, 최초 머리행 포함)다. 출처 분류: 모든 행 `규정값`.

| ID | 표 내 필드 위치 | 자료형 | 유효값/길이 표기 | 단위 | M/O | 열거 코드 |
|---|---|---|---|---|---|---|
| F4-14-007 | SMT_L_RAW | SEQUENCE | — | — | — | — |
| F4-14-008 | SMT_L_RAW / COLLECT_DATE | TIMESTAMP | (YYYYMMDDhhmmss) | — | M | — |
| F4-14-009 | SMT_L_RAW / NODE_ID | VARCHAR | (10) | — | M | — |
| F4-14-010 | SMT_L_RAW / LINK_ID | VARCHAR | (10) | — | M | — |
| F4-14-011 | SMT_L_RAW / ASCR_ID | VARCHAR | (10) | — | M | — |
| F4-14-012 | SMT_L_RAW / LANE_NO | NUMBER | (1) | — | M | — |
| F4-14-013 | SMT_L_RAW / VKND_CD | NUMBER | (1) | — | M | — |
| F4-14-014 | SMT_L_RAW / SPD | NUMBER | (5, 2) | — | M | — |
| F4-14-015 | SMT_L_RAW / VOL | NUMBER | (7) | — | M | — |

## 표 4-15 — WTRT_INFO

근거: **제4장 2.1.2, 표 4-15, 시작 p.69**. 관련 질의: Q17. 아래 ID의 마지막 숫자는 표 전체 행 번호(1부터, 최초 머리행 포함)다. 출처 분류: 모든 행 `규정값`.

| ID | 표 내 필드 위치 | 자료형 | 유효값/길이 표기 | 단위 | M/O | 열거 코드 |
|---|---|---|---|---|---|---|
| F4-15-007 | wtrt_data | SEQUENCE | — | — | - | — |
| F4-15-008 | wtrt_data / baseDate | VARCHAR | 8 (YYYYMMDD) | — | M | — |
| F4-15-009 | wtrt_data / updateDt | VARCHAR | 6 (hhmmss) | — | M | — |
| F4-15-010 | wtrt_data / nx | INTEGER | (-199999999.. 1800000001) | — | M | — |
| F4-15-011 | wtrt_data / ny | INTEGER | (-900000000..900000001) | — | M | — |
| F4-15-012 | wtrt_data / t1h | NUMERIC | (4,1) | (℃) | M | — |
| F4-15-013 | wtrt_data / rn1 | VARCHAR | (10) | (mm) | M | — |
| F4-15-014 | wtrt_data / sky | NUMBER | (1) | — | M | 1, 3, 4 |
| F4-15-018 | wtrt_data / uuu | NUMERIC | (4,1) | (m/s) | M | — |
| F4-15-019 | wtrt_data / vvv | NUMERIC | (4,1) | (m/s) | M | — |
| F4-15-020 | wtrt_data / reh | NUMERIC | (4,1) | (%) | M | — |
| F4-15-021 | wtrt_data / pty | INTEGER | (0..7) | — | M | 0, 1, 2, 3, 4, 5, 6, 7 |
| F4-15-030 | wtrt_data / lgt | VARCHAR | (3) | (deg) | M | — |
| F4-15-031 | wtrt_data / vec | VARCHAR | (3) | (deg) | M | — |
| F4-15-032 | wtrt_data / wsd | NUMERIC | (4,1) | (m/s) | M | — |
| F4-15-033 | wtrt_data / adstrdCode | VARCHAR | 8 (YYYYMMDD) | — | M | — |
| F4-15-034 | wtrt_data / fcstTime | VARCHAR | 6 (hhmmss) | — | M | — |

## 표 4-16 — UTIC_INC_INFO

근거: **제4장 2.1.3, 표 4-16, 시작 p.71**. 관련 질의: Q12/Q17. 아래 ID의 마지막 숫자는 표 전체 행 번호(1부터, 최초 머리행 포함)다. 출처 분류: 모든 행 `규정값`.

| ID | 표 내 필드 위치 | 자료형 | 유효값/길이 표기 | 단위 | M/O | 열거 코드 |
|---|---|---|---|---|---|---|
| F4-16-007 | UTIC_L_INC | SEQUENCE | — | — | — | — |
| F4-16-008 | UTIC_L_INC / INCIDENTID | VARCHAR2 | (12) | — | M | — |
| F4-16-009 | UTIC_L_INC / INCIDENTTYPECD | VARCHAR2 | (10) | — | M | 1, 2, 3, 4, 5, 6 |
| F4-16-016 | UTIC_L_INC / INCIDENTSUBTYPECD | VARCHAR2 | (10) | — | M | — |
| F4-16-017 | UTIC_L_INC / ADDRESSJIBUN | VARCHAR2 | (100) | — | M | — |
| F4-16-018 | UTIC_L_INC / ADDRESSJIBUNCD | VARCHAR2 | (20) | — | M | — |
| F4-16-019 | UTIC_L_INC / ADDRESSNEW | VARCHAR2 | (100) | — | M | — |
| F4-16-020 | UTIC_L_INC / LINKID | VARCHAR2 | (10) | — | M | — |
| F4-16-021 | UTIC_L_INC / LOCATIONDATAX | NUMBER | (15, 9) | — | M | — |
| F4-16-022 | UTIC_L_INC / LOCATIONDATAY | NUMBER | (15, 9) | — | M | — |
| F4-16-023 | UTIC_L_INC / LOCATIONTYPECD | VARCHAR2 | (5) | — | - | C0101, C0102, C1013 |
| F4-16-027 | UTIC_L_INC / LOCATIONDATA | VARCHAR2 | (3000) | — | - | — |
| F4-16-028 | UTIC_L_INC / INCIDENTTRAFFICCD | VARCHAR2 | (10) | — | M | A0501, A0502, A0503 |
| F4-16-032 | UTIC_L_INC / INCIDENTGRADECD | VARCHAR2 | (10) | — | M | A0401, A0402, A0403 |
| F4-16-036 | UTIC_L_INC / INCIDENTTITLE | VARCHAR2 | (500) | — | M | — |
| F4-16-037 | UTIC_L_INC / INCIDENTREGIONCD | VARCHAR2 | (2) | — | M | — |
| F4-16-038 | UTIC_L_INC / STARTDATE | DATE | (YYYY년 MM월 DD일 hh시 dd분) | — | M | — |
| F4-16-039 | UTIC_L_INC / ENDDATE | DATE | (YYYY년 MM월 DD일 hh시 dd분) | — | M | — |
| F4-16-040 | UTIC_L_INC / LANE | VARCHAR2 | (10) | — | M | — |
| F4-16-041 | UTIC_L_INC / ROADNAME | VARCHAR2 | (50) | — | M | — |
| F4-16-042 | UTIC_L_INC / SOURCECODE | VARCHAR2 | (5) | — | O | — |
| F4-16-043 | UTIC_L_INC / CONTROLTYPE | VARCHAR2 | (2) | — | M | 0, 1, 2 |
| F4-16-047 | UTIC_L_INC / LINELINKID | VARCHAR2 | (1000) | — | M | — |
| F4-16-048 | UTIC_L_INC / IMPORTANT | VARCHAR2 | (5) | — | M | 00, 01 |
| F4-16-051 | UTIC_L_INC / UPDATEDATE | DATE | (YYYY년 MM월 DD일 hh시 dd분) | — | M | — |

## 표 4-18 — INFRA_OPEN_DATA

근거: **제4장 2.2.2, 표 4-18, 시작 p.79**. 관련 질의: Q14/Q15/Q16. 아래 ID의 마지막 숫자는 표 전체 행 번호(1부터, 최초 머리행 포함)다. 출처 분류: 모든 행 `규정값`.

| ID | 표 내 필드 위치 | 자료형 | 유효값/길이 표기 | 단위 | M/O | 열거 코드 |
|---|---|---|---|---|---|---|
| F4-18-007 | utctime | SEQUENCE | — | — | - | — |
| F4-18-008 | utctime / year | INTEGER | (0..4095) | — | M | — |
| F4-18-009 | utctime / month | INTEGER | (0..12) | — | M | — |
| F4-18-010 | utctime / day | INTEGER | (0..31) | — | M | — |
| F4-18-011 | utctime / hour | INTEGER | (0..31) | — | M | — |
| F4-18-012 | utctime / minute | INTEGER | (0..60) | — | M | — |
| F4-18-013 | utctime / second | INTEGER | (0..65535) | — | M | — |
| F4-18-014 | objectData | SEQUENCE | — | — | - | — |
| F4-18-015 | objectData / objectType | ENUMERATED | (0..2) | — | M | 0, 1, 2 |
| F4-18-019 | objectData / objectID | INTEGER | (0..255) | — | M | — |
| F4-18-020 | objectData / novelty | ENUMERATED | (0..1) | — | M | 0, 1 |
| F4-18-023 | objectData / reliability | INTEGER | (0..100) | — | O | — |
| F4-18-024 | objectData / refPosition | SEQUENCE | — | — | M | — |
| F4-18-025 | objectData / refPosition / long | INTEGER | (-199999999.. 1800000001) | — | M | — |
| F4-18-026 | objectData / refPosition / lat | INTEGER | (-900000000.. 900000001) | — | M | — |
| F4-18-027 | objectData / FullPositionVector | SEQUENCE | — | — | - | — |
| F4-18-028 | objectData / FullPositionVector / long | INTEGER | (-199999999.. 1800000001) | — | M | — |
| F4-18-029 | objectData / FullPositionVector / lat | INTEGER | (-900000000.. 900000001) | — | M | — |
| F4-18-030 | objectData / FullPositionVector / elevation | INTEGER | (-4096..61439) | — | O | — |
| F4-18-031 | objectData / FullPositionVector / heading | INTEGER | (0..28800) | — | M | — |
| F4-18-032 | objectData / FullPositionVector / speed | SEQUENCE | — | — | - | — |
| F4-18-033 | objectData / FullPositionVector / speed / transmisson | ENUMERATED | - | — | O | 0, 1, 2, 3, 4, 5, 6, 7 |
| F4-18-042 | objectData / FullPositionVector / speed / speed | INTEGER | (0..8191) | — | M | — |
| F4-18-043 | objectData / FullPositionVector / posAccuracy | SEQUENCE | — | — | O | — |
| F4-18-044 | objectData / FullPositionVector / posAccuracy / semiMajor | INTEGER | (0..255) | — | O | — |
| F4-18-045 | objectData / FullPositionVector / posAccuracy / semiMinor | INTEGER | (0..255) | — | O | — |
| F4-18-046 | objectData / FullPositionVector / posAccuracy / orientation | INTEGER | (0..65535) | — | O | — |
| F4-18-047 | objectData / FullPositionVector / posConfidence | SEQUENCE | — | — | O | — |
| F4-18-048 | objectData / FullPositionVector / posConfidence / timeConfidence | ENUMERATED | — | — | O | 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39 |
| F4-18-089 | objectData / FullPositionVector / posConfidence / pos | ENUMERATED | — | — | O | 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 |
| F4-18-106 | objectData / FullPositionVector / posConfidence / elevation | ENUMERATED | — | — | O | 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 |
| F4-18-123 | objectData / FullPositionVector / speedConfidence | SEQUENCE | — | — | O | — |
| F4-18-124 | objectData / FullPositionVector / speedConfidence / heading | ENUMERATED | — | — | O | 0, 1, 2, 3, 4, 5, 6, 7 |
| F4-18-133 | objectData / FullPositionVector / speedConfidence / speed | ENUMERATED | — | — | O | 0, 1, 2, 3, 4, 5, 6, 7 |
| F4-18-142 | objectData / FullPositionVector / speedConfidence / throttle | ENUMERATED | — | — | O | 0, 1, 2, 3 |
| F4-18-147 | weatherData | SEQUENCE | — | — | M | — |
| F4-18-148 | weatherData / macAddr | STRING | — | — | M | — |
| F4-18-149 | weatherData / device-state | ENUMERATED | (0..1) | — | M | 0, 1 |
| F4-18-152 | weatherData / weather | SEQUENCE | — | — | M | — |
| F4-18-153 | weatherData / weather / temperature | DOUBLE | (-400..800) | — | M | — |
| F4-18-154 | weatherData / weather / humidity | DOUBLE | (0..1000) | — | M | — |
| F4-18-155 | weatherData / weather / view-range | DOUBLE | (1..1000) | — | M | — |
| F4-18-156 | weatherData / weather / wind-dir | DOUBLE | (1..359) | — | M | — |
| F4-18-157 | weatherData / weather / wind-speed | DOUBLE | (1..400) | — | M | — |
| F4-18-158 | weatherData / weather / air-pressure | DOUBLE | (1500..11000) | — | M | — |
| F4-18-159 | weatherData / weather / w-condition | INTEGER | (0..4) | — | M | 1, 2, 3, 4 |
| F4-18-164 | weatherData / weather / rain | DOUBLE | (0..1000) | — | M | — |
| F4-18-165 | weatherData / weather / sun | DOUBLE | (0..20000) | — | M | — |
| F4-18-166 | weatherData / weather / surface-temp | DOUBLE | (-5000..11000) | — | M | — |
| F4-18-167 | weatherData / weather / underground-temp | DOUBLE | (-5000..11000) | — | M | — |
| F4-18-168 | weatherData / weather / freezing-temp | DOUBLE | (-5000..11000) | — | M | — |
| F4-18-169 | weatherData / weather / salt concentration | DOUBLE | (0..3000) | — | M | — |
| F4-18-170 | weatherData / weather / Installation status | INTEGER | (0..1) | — | M | 0, 1 |
| F4-18-173 | weatherData / weather / Traffic count | INTEGER | (0..65535) | — | M | — |
| F4-18-174 | weatherData / weather / forward axial stiffness | DOUBLE | (-100..100) | — | M | — |
| F4-18-175 | weatherData / weather / transverse axial stiffness | DOUBLE | (-100..100) | — | M | — |
| F4-18-176 | weatherData / weather / road condition | INTEGER | (0..1) | — | M | 0, 1, 2, 3 |
| F4-18-181 | weatherData / weather / water level | DOUBLE | (0.0..4000.0) ※측정불가인 경우 0xffff | — | M | — |
| F4-18-182 | tailLampIntensity | SEQUENCE | — | — | - | — |
| F4-18-183 | tailLampIntensity / intensity | INTEGER | (0..9) | — | O | — |
| F4-18-184 | safetyMessage | SEQUENCE | — | — | - | — |
| F4-18-185 | safetyMessage / safetylevel | INTEGER | (0..3) | — | O | 0, 1, 2, 3 |
| F4-18-190 | safetyMessage / messageclass | INTEGER | (0..4) | — | o | 0, 1, 2, 3 |
| F4-18-195 | safetyMessage / limitspeed | INTEGER | (10..120) | — | M | — |
| F4-18-196 | safetyMessage / trafficsign | INTEGER | (0..60) | — | M | — |
| F4-18-197 | safetyMessage / vmsmessage | INTEGER | (0..60) | — | O | — |
| F4-18-198 | systemStatus | SEQUENCE | — | — | - | — |
| F4-18-199 | systemStatus / ObjectDetectionSystem | ENUMERATED | (0..1) | — | M | 0, 1 |
| F4-18-202 | systemStatus / WeatherSensorSystem | ENUMERATED | (0..1) | — | M | 0, 1 |
| F4-18-205 | systemStatus / InfraEdgePlatform | ENUMERATED | (0..1) | — | M | 0, 1 |

## 표 4-19 — I2X_STATU_INFO

근거: **제4장 2.2.3, 표 4-19, 시작 p.89**. 관련 질의: Q09/Q17. 아래 ID의 마지막 숫자는 표 전체 행 번호(1부터, 최초 머리행 포함)다. 출처 분류: 모든 행 `규정값`.

| ID | 표 내 필드 위치 | 자료형 | 유효값/길이 표기 | 단위 | M/O | 열거 코드 |
|---|---|---|---|---|---|---|
| F4-19-007 | i2xID | STRING | (-4096..61439) | — | M | — |
| F4-19-008 | i2xInterId | STRING | — | — | M | — |
| F4-19-009 | i2xConId | STRING | — | — | M | — |
| F4-19-010 | i2xConName | STRING | — | — | M | — |
| F4-19-011 | i2xLocation / latitude | STRING | — | — | M | — |
| F4-19-012 | i2xLocation / longitude | STRING | — | — | M | — |
| F4-19-013 | SDateTime | STRING | — | — | M | — |
| F4-19-014 | i2xCnncSttus | INTEGER | (0..1) | — | M | 0, 1 |
| F4-19-017 | iotCnncSttus | INTEGER | (0..1) | — | M | 0, 1 |
| F4-19-020 | citsCnncSttus | INTEGER | (0..1) | — | M | 0, 1 |
| F4-19-023 | i2xStrgTemp | INTEGER | (-40..999) | C | M | — |
| F4-19-024 | i2xStrgHum | INTEGER | (0..100) | % | M | — |
| F4-19-025 | i2xDoorSttus | INTEGER | (0..1) | — | M | 0, 1 |
| F4-19-028 | i2xFanSttus | INTEGER | (0..1) | — | M | 0, 1 |
| F4-19-031 | i2xHeaterSttus | INTEGER | (0..1) | — | M | 0, 1 |

## 표 4-20 — SERV_PLAF_STATU_INFO

근거: **제4장 2.2.4, 표 4-20, 시작 p.91**. 관련 질의: Q09/Q18. 아래 ID의 마지막 숫자는 표 전체 행 번호(1부터, 최초 머리행 포함)다. 출처 분류: 모든 행 `규정값`.

| ID | 표 내 필드 위치 | 자료형 | 유효값/길이 표기 | 단위 | M/O | 열거 코드 |
|---|---|---|---|---|---|---|
| F4-20-007 | INTER_SERVER_STATUS | SEQUENCE | — | — | - | — |
| F4-20-008 | INTER_SERVER_STATUS / SERVER_DT | TIMESTAMP | (YYYYMMDDhhmmss) | — | M | — |
| F4-20-009 | INTER_SERVER_STATUS / SERVER_STAT | ENUMERATED | (0..1) | — | M | 0, 1 |
| F4-20-012 | KAFKA_FCLTY_STATUS | SEQUENCE | — | — | - | — |
| F4-20-013 | KAFKA_FCLTY_STATUS / KAFKA_STAT | ENUMERATED | (0..1) | — | M | 0, 1 |
| F4-20-016 | KAFKA_FCLTY_STATUS / KAFKA_PORT | INTEGER | (0..65535) | — | M | — |
| F4-20-017 | KAFKA_FCLTY_STATUS / KAFKA_STTUS | ENUMERATED | (0..1) | — | M | 0, 1 |
| F4-20-020 | DATAHUB_PLATFORM_STATUS | SEQUENCE | — | — | — | — |
| F4-20-021 | DATAHUB_PLATFORM_STATUS / DATAMANAGER_PORT | INTEGER | (0..65535) | — | M | — |
| F4-20-022 | DATAHUB_PLATFORM_STATUS / DATAMANAGER_STTUS | ENUMERATED | (0..1) | — | M | 0, 1 |
| F4-20-025 | DATAHUB_PLATFORM_STATUS / DATASERVICEBROKER_PORT | INTEGER | (0..65535) | — | M | — |
| F4-20-026 | DATAHUB_PLATFORM_STATUS / DATAMANAGER_STTUS | ENUMERATED | (0..1) | — | M | 0, 1 |
| F4-20-029 | DATAHUB_PLATFORM_STATUS / INGESTINTERFACE_PORT | INTEGER | (0..65535) | — | M | — |
| F4-20-030 | DATAHUB_PLATFORM_STATUS / INGESTINTERFACE_STTUS | ENUMERATED | (0..1) | — | M | 0, 1 |

## 표 4-21 — SHAD_TRAF_INFO

근거: **제4장 2.3.1, 표 4-21, 시작 p.93**. 관련 질의: Q09/Q17. 아래 ID의 마지막 숫자는 표 전체 행 번호(1부터, 최초 머리행 포함)다. 출처 분류: 모든 행 `규정값`.

| ID | 표 내 필드 위치 | 자료형 | 유효값/길이 표기 | 단위 | M/O | 열거 코드 |
|---|---|---|---|---|---|---|
| F4-21-007 | time | TIMESTAMP | (YYYYMMDDhhmmss) | — | M | — |
| F4-21-008 | node_link | INTEGER | (0..99999) | — | M | — |
| F4-21-009 | lane_no | INTEGER | (0..350) | — | M | — |
| F4-21-010 | lane_speed | INTEGER | (0..350) | — | M | — |
| F4-21-011 | lane_volume | INTEGER | (0..99999) | — | M | — |
| F4-21-012 | lane_density | INTEGER | (0..350) | — | M | — |

## 표 4-22 — VDS_INFO

근거: **제4장 2.4.1.1, 표 4-22, 시작 p.95**. 관련 질의: Q12. 아래 ID의 마지막 숫자는 표 전체 행 번호(1부터, 최초 머리행 포함)다. 출처 분류: 모든 행 `규정값`.

| ID | 표 내 필드 위치 | 자료형 | 유효값/길이 표기 | 단위 | M/O | 열거 코드 |
|---|---|---|---|---|---|---|
| F4-22-007 | vds_l_raw | SEQUENCE | - | — | — | — |
| F4-22-008 | vds_l_raw / collect_date | TIMESTAMP | (YYYYMMDDhhmmss) | — | M | — |
| F4-22-009 | vds_l_raw / stn_id | VARCHAR | (12) | — | M | — |
| F4-22-010 | vds_l_raw / lane_no | NUMBER | (1) | — | M | — |
| F4-22-011 | vds_l_raw / vol | NUMBER | (7) | — | M | — |
| F4-22-012 | vds_l_raw / spd | NUMBER | (5,2) | km/h | M | — |
| F4-22-013 | vds_l_raw / occ | NUMBER | (5,2) | % | M | — |
| F4-22-014 | vds_l_raw / vol_s | NUMBER | (7) | — | O | — |
| F4-22-015 | vds_l_raw / vol_m | NUMBER | (7) | — | O | — |
| F4-22-016 | vds_l_raw / vol_l | NUMBER | (7) | — | O | — |
| F4-22-017 | vds_l_raw / err_code | NUMBER | (1) | — | M | — |
| F4-22-018 | vds_l_raw / link_id | VARCHAR | (12) | — | M | — |
| F4-22-019 | vds_l_raw / vds_id | VARCHAR | (12) | — | M | — |
| F4-22-020 | vds_l_raw / stn_location | VARCHAR | (50) | — | M | — |

## 표 4-23 — SMT_L_RAW_INFO

근거: **제4장 2.4.1.2, 표 4-23, 시작 p.97**. 관련 질의: Q12. 아래 ID의 마지막 숫자는 표 전체 행 번호(1부터, 최초 머리행 포함)다. 출처 분류: 모든 행 `규정값`.

| ID | 표 내 필드 위치 | 자료형 | 유효값/길이 표기 | 단위 | M/O | 열거 코드 |
|---|---|---|---|---|---|---|
| F4-23-007 | SMT_L_RAW | SEQUENCE | — | — | — | — |
| F4-23-008 | SMT_L_RAW / COLLECT_DATE | TIMESTAMP | (YYYYMMDDhhmmss) | — | M | — |
| F4-23-009 | SMT_L_RAW / NODE_ID | VARCHAR | (10) | — | M | — |
| F4-23-010 | SMT_L_RAW / LINK_ID | VARCHAR | (10) | — | M | — |
| F4-23-011 | SMT_L_RAW / ASCR_ID | VARCHAR | (10) | — | M | — |
| F4-23-012 | SMT_L_RAW / LANE_NO | NUMBER | (1) | — | M | — |
| F4-23-013 | SMT_L_RAW / VKND_CD | NUMBER | (1) | — | M | — |
| F4-23-014 | SMT_L_RAW / SPD | NUMBER | (5, 2) | — | M | — |
| F4-23-015 | SMT_L_RAW / VOL | NUMBER | (7) | — | M | — |

## 표 4-24 — INT_ALL_STATUS

근거: **제4장 2.5.1, 표 4-24, 시작 p.98**. 관련 질의: Q19. 아래 ID의 마지막 숫자는 표 전체 행 번호(1부터, 최초 머리행 포함)다. 출처 분류: 모든 행 `규정값`.

| ID | 표 내 필드 위치 | 자료형 | 유효값/길이 표기 | 단위 | M/O | 열거 코드 |
|---|---|---|---|---|---|---|
| F4-24-007 | MSGNo | INTEGER | 1 byte | — | M | — |
| F4-24-008 | MSGSize | INTEGER | 2 byte | — | M | — |
| F4-24-009 | MSGStart-End | INTEGER | 1 byte | — | M | — |
| F4-24-010 | MSGSeqNo | INTEGER | 1 byte | — | M | — |
| F4-24-011 | INT_MASTER | SEQUENCE | — | — | - | — |
| F4-24-012 | INT_MASTER / LC_NO | INTEGER | 1 byte | — | M | — |
| F4-24-013 | INT_MASTER / LC_NAME | CHAR | 100 byte | — | M | — |
| F4-24-014 | INT_MASTER / LC_TYPE | INTEGER | 1 byte | — | M | — |
| F4-24-015 | INT_MASTER / LC_LAT | CHAR | 20 byte | — | M | — |
| F4-24-016 | INT_MASTER / LC_LNG | CHAR | 20 byte | — | M | — |
| F4-24-017 | INT_STATUS | SEQUENCE | — | — | - | — |
| F4-24-018 | INT_STATUS / LC_STATUS | INTEGER | 1 byte | — | M | — |
| F4-24-019 | INT_STATUS / LC_COUNT | INTEGER | 1 byte | — | M | — |
| F4-24-020 | INT_STATUS / LC_A_FLONUMBER | INTEGER | 1 byte | — | M | — |
| F4-24-021 | INT_STATUS / LC_A_START_LAT | CHAR | 20 byte | — | M | — |
| F4-24-022 | INT_STATUS / LC_A_START_LNG | CHAR | 20 byte | — | M | — |
| F4-24-023 | INT_STATUS / LC_A_MIDDLE_LAT | CHAR | 20 byte | — | M | — |
| F4-24-024 | INT_STATUS / LC_A_MIDDLE_LNG | CHAR | 20 byte | — | M | — |
| F4-24-025 | INT_STATUS / LC_A_END_LAT | CHAR | 20 byte | — | M | — |
| F4-24-026 | INT_STATUS / LC_A_END_LNG | CHAR | 20 byte | — | M | — |
| F4-24-027 | INT_STATUS / LC_B_FLONUMBER | INTEGER | 1 byte | — | M | — |
| F4-24-028 | INT_STATUS / LC_B_START_LAT | CHAR | 20 byte | — | M | — |
| F4-24-029 | INT_STATUS / LC_B_START_LNG | CHAR | 20 byte | — | M | — |
| F4-24-030 | INT_STATUS / LC_B_MIDDLE_LAT | CHAR | 20 byte | — | M | — |
| F4-24-031 | INT_STATUS / LC_B_MIDDLE_LNG | CHAR | 20 byte | — | M | — |
| F4-24-032 | INT_STATUS / LC_B_END_LAT | CHAR | 20 byte | — | M | — |
| F4-24-033 | INT_STATUS / LC_B_END_LNG | CHAR | 20 byte | — | M | — |
| F4-24-034 | INT_STATUS / LRC | INTEGER | 1 byte | — | M | — |

## 표 4-25 — INT_ALTER_STATUS

근거: **제4장 2.5.2, 표 4-25, 시작 p.101**. 관련 질의: Q19. 아래 ID의 마지막 숫자는 표 전체 행 번호(1부터, 최초 머리행 포함)다. 출처 분류: 모든 행 `규정값`.

| ID | 표 내 필드 위치 | 자료형 | 유효값/길이 표기 | 단위 | M/O | 열거 코드 |
|---|---|---|---|---|---|---|
| F4-25-007 | MSGNo | INTEGER | 1 byte | — | M | — |
| F4-25-008 | MSGSize | INTEGER | 2 byte | — | M | — |
| F4-25-009 | MSGStart-End | INTEGER | 1 byte | — | M | — |
| F4-25-010 | MSGSeqNo | INTEGER | 1 byte | — | M | — |
| F4-25-011 | INT_MASTER | SEQUENCE | — | — | - | — |
| F4-25-012 | INT_MASTER / LC_NO | INTEGER | 1 byte | — | M | — |
| F4-25-013 | INT_MASTER / LC_NAME | CHAR | 100 byte | — | M | — |
| F4-25-014 | INT_MASTER / LC_TYPE | INTEGER | 1 byte | — | M | — |
| F4-25-015 | INT_MASTER / LC_LAT | CHAR | 20 byte | — | M | — |
| F4-25-016 | INT_MASTER / LC_LNG | CHAR | 20 byte | — | M | — |
| F4-25-017 | INT_STATUS | SEQUENCE | — | — | - | — |
| F4-25-018 | INT_STATUS / LC_STATUS | INTEGER | 1 byte | — | M | — |
| F4-25-019 | INT_STATUS / LC_COUNT | INTEGER | 1 byte | — | M | — |
| F4-25-020 | INT_STATUS / LC_A_FLONUMBER | INTEGER | 1 byte | — | M | — |
| F4-25-021 | INT_STATUS / LC_A_START_LAT | CHAR | 20 byte | — | M | — |
| F4-25-022 | INT_STATUS / LC_A_START_LNG | CHAR | 20 byte | — | M | — |
| F4-25-023 | INT_STATUS / LC_A_MIDDLE_LAT | CHAR | 20 byte | — | M | — |
| F4-25-024 | INT_STATUS / LC_A_MIDDLE_LNG | CHAR | 20 byte | — | M | — |
| F4-25-025 | INT_STATUS / LC_A_END_LAT | CHAR | 20 byte | — | M | — |
| F4-25-026 | INT_STATUS / LC_A_END_LNG | CHAR | 20 byte | — | M | — |
| F4-25-027 | INT_STATUS / LC_B_FLONUMBER | INTEGER | 1 byte | — | M | — |
| F4-25-028 | INT_STATUS / LC_B_START_LAT | CHAR | 20 byte | — | M | — |
| F4-25-029 | INT_STATUS / LC_B_START_LNG | CHAR | 20 byte | — | M | — |
| F4-25-030 | INT_STATUS / LC_B_MIDDLE_LAT | CHAR | 20 byte | — | M | — |
| F4-25-031 | INT_STATUS / LC_B_MIDDLE_LNG | CHAR | 20 byte | — | M | — |
| F4-25-032 | INT_STATUS / LC_B_END_LAT | CHAR | 20 byte | — | M | — |
| F4-25-033 | INT_STATUS / LC_B_END_LNG | CHAR | 20 byte | — | M | — |
| F4-25-034 | INT_STATUS / LRC | INTEGER | 1 byte | — | M | — |

## 표 4-26 — INT_TOD_INFO

근거: **제4장 2.5.3, 표 4-26, 시작 p.103**. 관련 질의: Q19. 아래 ID의 마지막 숫자는 표 전체 행 번호(1부터, 최초 머리행 포함)다. 출처 분류: 모든 행 `규정값`.

| ID | 표 내 필드 위치 | 자료형 | 유효값/길이 표기 | 단위 | M/O | 열거 코드 |
|---|---|---|---|---|---|---|
| F4-26-007 | MSGNo | INTEGER | 1 byte | — | M | — |
| F4-26-008 | MSGSize | INTEGER | 2 byte | — | M | — |
| F4-26-009 | MSGStart-End | INTEGER | 1 byte | — | M | — |
| F4-26-010 | MSGSeqNo | INTEGER | 1 byte | — | M | — |
| F4-26-011 | INT_TOD_PLAN | SEQUENCE | - | — | - | — |
| F4-26-012 | INT_TOD_PLAN / LC_NO | INTEGER | 4 byte | — | M | — |
| F4-26-013 | INT_TOD_PLAN / START_HOUR | INTEGER | 1 byte | — | M | — |
| F4-26-014 | INT_TOD_PLAN / START_MIN | INTEGER | 1 byte | — | M | — |
| F4-26-015 | INT_TOD_PLAN / CYCLE | INTEGER | 2 byte | — | M | — |
| F4-26-016 | INT_TOD_PLAN / OFFSET | INTEGER | 2 byte | — | M | — |
| F4-26-017 | INT_TOD_PLAN / ARING_1PHASE | INTEGER | 2 byte | — | M | — |
| F4-26-018 | INT_TOD_PLAN / ARING_2PHASE | INTEGER | 2 byte | — | M | — |
| F4-26-019 | INT_TOD_PLAN / ARING_3PHASE | INTEGER | 2 byte | — | M | — |
| F4-26-020 | INT_TOD_PLAN / ARING_4PHASE | INTEGER | 2 byte | — | M | — |
| F4-26-021 | INT_TOD_PLAN / ARING_5PHASE | INTEGER | 2 byte | — | M | — |
| F4-26-022 | INT_TOD_PLAN / ARING_6PHASE | INTEGER | 2 byte | — | M | — |
| F4-26-023 | INT_TOD_PLAN / ARING_7PHASE | INTEGER | 2 byte | — | M | — |
| F4-26-024 | INT_TOD_PLAN / ARING_8PHASE | INTEGER | 2 byte | — | M | — |
| F4-26-025 | INT_TOD_PLAN / BRING_1PHASE | INTEGER | 2 byte | — | M | — |
| F4-26-026 | INT_TOD_PLAN / BRING_2PHASE | INTEGER | 2 byte | — | M | — |
| F4-26-027 | INT_TOD_PLAN / BRING_3PHASE | INTEGER | 2 byte | — | M | — |
| F4-26-028 | INT_TOD_PLAN / BRING_4PHASE | INTEGER | 2 byte | — | M | — |
| F4-26-029 | INT_TOD_PLAN / BRING_5PHASE | INTEGER | 2 byte | — | M | — |
| F4-26-030 | INT_TOD_PLAN / BRING_6PHASE | INTEGER | 2 byte | — | M | — |
| F4-26-031 | INT_TOD_PLAN / BRING_7PHASE | INTEGER | 2 byte | — | M | — |
| F4-26-032 | INT_TOD_PLAN / BRING_8PHASE | INTEGER | 2 byte | — | M | — |
| F4-26-033 | INT_TOD_PLAN / ... | ... | ... | — | M | — |

## 표 4-27 — OPTIONAL_ROUTE

근거: **제4장 2.5.4, 표 4-27, 시작 p.105**. 관련 질의: Q19. 아래 ID의 마지막 숫자는 표 전체 행 번호(1부터, 최초 머리행 포함)다. 출처 분류: 모든 행 `규정값`.

| ID | 표 내 필드 위치 | 자료형 | 유효값/길이 표기 | 단위 | M/O | 열거 코드 |
|---|---|---|---|---|---|---|
| F4-27-007 | MSGNo | INTEGER | 1 byte | — | M | — |
| F4-27-008 | MSGSize | INTEGER | 2 byte | — | M | — |
| F4-27-009 | MSGStart-End | INTEGER | 1 byte | — | M | — |
| F4-27-010 | MSGSeqNo | INTEGER | 1 byte | — | M | — |
| F4-27-011 | Year | INTEGER | 2 byte | — | M | — |
| F4-27-012 | Month | INTEGER | 1 byte | — | M | — |
| F4-27-013 | Day | INTEGER | 1 byte | — | M | — |
| F4-27-014 | Hour | INTEGER | 1 byte | — | M | — |
| F4-27-015 | Minute | INTEGER | 1 byte | — | M | — |
| F4-27-016 | Second | INTEGER | 1 byte | — | M | — |
| F4-27-017 | lot | DOUBLE | 8 byte | — | M | — |
| F4-27-018 | lat | DOUBLE | 8 byte | — | M | — |
| F4-27-019 | pol6IndivAdInfoDtoList | — | — | — | — | — |
| F4-27-020 | pol6IndivAdInfoDtoList / indivAdIdNo | INTEGER | 1 byte | — | M | — |
| F4-27-021 | pol6IndivAdInfoDtoList / indivAdId | CHAR | 10 byte | — | M | — |
| F4-27-022 | pol6IndivAdInfoDtoList / linkId | CHAR | 10 byte | — | M | — |
| F4-27-023 | pol6IndivAdInfoDtoList / linkPos | INTEGER | 3 byte | — | M | — |
| F4-27-024 | pol6IndivAdInfoDtoList / linkInfoType | INTEGER | 1 byte | — | M | — |
| F4-27-025 | pol6IndivAdInfoDtoList / pol6RouteIntoDtoList | — | — | — | — | — |
| F4-27-026 | pol6IndivAdInfoDtoList / viaLinkNo | INTEGER | 1 byte | — | M | — |
| F4-27-027 | pol6IndivAdInfoDtoList / viaLinkSeq | INTEGER | 20 byte | — | M | — |
| F4-27-028 | pol6IndivAdInfoDtoList / viaLinkId | CHAR | 3 byte | — | M | — |
| F4-27-029 | pol6IndivAdInfoDtoList / viaLinkTurn | INTEGER | 1 byte | — | M | — |
| F4-27-030 | LRC | INTEGER | 1 byte | — | M | — |

## 표 4-28 — BSM_INFO

근거: **제4장 2.6.1.1, 표 4-28, 시작 p.108**. 관련 질의: Q09/Q19. 아래 ID의 마지막 숫자는 표 전체 행 번호(1부터, 최초 머리행 포함)다. 출처 분류: 모든 행 `규정값`.

| ID | 표 내 필드 위치 | 자료형 | 유효값/길이 표기 | 단위 | M/O | 열거 코드 |
|---|---|---|---|---|---|---|
| F4-28-007 | MSGNo | INTEGER | 1 byte | — | M | — |
| F4-28-008 | MSGSize | INTEGER | 2 byte | — | M | — |
| F4-28-009 | MSGStart-End | INTEGER | 1 byte | — | M | — |
| F4-28-010 | MSGSeqNo | INTEGER | 1 byte | — | M | — |
| F4-28-011 | BmsInfo | — | — | — | — | — |
| F4-28-012 | BmsInfo / CREDATE | CHAR | 8 byte | — | M | — |
| F4-28-013 | BmsInfo / VEH_ID | CHAR | 16 byte | — | M | — |
| F4-28-014 | BmsInfo / VEH_NO | CHAR | 8 byte | — | M | — |
| F4-28-015 | BmsInfo / LONGITUDE | DOUBLE | 8 byte | — | M | — |
| F4-28-016 | BmsInfo / LATITUDE | DOUBLE | 8 byte | — | M | — |
| F4-28-017 | BmsInfo / ALTITUDE | FLOAT | 4 byte | — | M | — |
| F4-28-018 | BmsInfo / ANGLE | FLOAT | 4 byte | — | M | — |
| F4-28-019 | BmsInfo / GEAR | CHAR | 4 byte | — | M | — |
| F4-28-020 | BmsInfo / SPEED | FLOAT | 4 byte | — | M | — |
| F4-28-021 | LRC | INTEGER | 1 byte | — | M | — |

## 표 4-29 — INC_INFO

근거: **제4장 2.6.2, 표 4-29, 시작 p.109**. 관련 질의: Q19. 아래 ID의 마지막 숫자는 표 전체 행 번호(1부터, 최초 머리행 포함)다. 출처 분류: 모든 행 `규정값`.

| ID | 표 내 필드 위치 | 자료형 | 유효값/길이 표기 | 단위 | M/O | 열거 코드 |
|---|---|---|---|---|---|---|
| F4-29-007 | MSGNo | INTEGER | 1 byte | — | M | — |
| F4-29-008 | MSGSize | INTEGER | 2 byte | — | M | — |
| F4-29-009 | MSGStart-End | INTEGER | 1 byte | — | M | — |
| F4-29-010 | MSGSeqNo | INTEGER | 1 byte | — | M | — |
| F4-29-011 | IncidentInfo | — | — | — | — | — |
| F4-29-012 | IncidentInfo / YEAR | INTEGER | 2 byte | — | M | — |
| F4-29-013 | IncidentInfo / MONTH | INTEGER | 1 byte | — | M | — |
| F4-29-014 | IncidentInfo / DAY | INTEGER | 1 byte | — | M | — |
| F4-29-015 | IncidentInfo / HOUR | INTEGER | 1 byte | — | M | — |
| F4-29-016 | IncidentInfo / MINUTE | INTEGER | 1 byte | — | M | — |
| F4-29-017 | IncidentInfo / SECOND | INTEGER | 1 byte | — | M | — |
| F4-29-018 | IncidentInfo / EVENT_ID | CHAR | 18 Byte | — | M | — |
| F4-29-019 | IncidentInfo / EVENT_NM | CHAR | 500 Byte | — | M | — |
| F4-29-020 | IncidentInfo / INC_TY | CHAR | 2 Byte | — | M | — |
| F4-29-021 | IncidentInfo / INC_DTL_TY | CHAR | 4 Byte | — | M | — |
| F4-29-022 | IncidentInfo / OCRN_DT | CHAR | 14 Byte | — | M | — |
| F4-29-023 | IncidentInfo / END_DT | CHAR | 14 Byte | — | M | — |
| F4-29-024 | IncidentInfo / OCRN_LOT | CHAR | 20 Byte | — | M | — |
| F4-29-025 | IncidentInfo / OCRN_LAT | CHAR | 20 Byte | — | M | — |
| F4-29-026 | IncidentInfo / OCRN_LINK_ID | CHAR | 10 Byte | — | M | — |
| F4-29-027 | IncidentInfo / CNTRL_TY | CHAR | 1 Byte | — | M | — |
| F4-29-028 | IncidentInfo / PRGRS_STTS | CHAR | 2 Byte | — | M | — |
| F4-29-029 | IncidentInfo / EVENT_CTRL | — | — | — | M | — |
| F4-29-030 | IncidentInfo / LINK_COUNT | INTEGER | 1 byte | — | M | — |
| F4-29-031 | IncidentInfo / LINK_ID | CHAR | 10 byte | — | M | — |
| F4-29-032 | [이름 미기재] | CHAR | 10 byte | — | M | — |
| F4-29-033 | IncidentInfo / LINK_ID | CHAR | 10 byte | — | M | — |
| F4-29-034 | LRC | INTEGER | 1 byte | — | M | — |

## 부록 Ⅱ-1 — TIM 제한속도 변경

근거: 부록 Ⅱ-1, 표 Ⅱ-2의 해당 제목, p.137부터. 출처 분류: `규정값`. 자료형·범위·길이는 KS R 1600 준용, 해당 판 원전 확인 전 미정. 표의 반복수는 원문 수치를 보존하며 최대치/정확한 개수 의미는 R-TIM02/Q20을 함께 읽는다.

| ID | 표 내 필드 위치 | KS M/O·반복 | ITSK M/O·반복 | 참조 절(원문 표기) |
|---|---|---|---|---|
| FA-TIM-S-003 | msgCnt | M / 1 | M / 1 | [1600-2] 7.6.48 |
| FA-TIM-S-004 | packetID | O / 1 | M / 1 | 7.6.25 |
| FA-TIM-S-005 | dataFrames | M / 1 | M / 1 | 7.5.48 |
| FA-TIM-S-006 | dataFrames / TravelerDateFramelist | M / 1 | M / 1 | 7.5.48 |
| FA-TIM-S-007 | dataFrames / TravelerDateFramelist / TravelerDataFrame | M / 8 | M / 1 | 7.5.46 |
| FA-TIM-S-008 | dataFrames / TravelerDateFramelist / TravelerDataFrame / frameType | M / 1 | M / 1 | 7.6.24 |
| FA-TIM-S-009 | dataFrames / TravelerDateFramelist / TravelerDataFrame / msgId | C / 1 | M / 1 | 7.5.38 [1600-4] 7.6.6 |
| FA-TIM-S-010 | dataFrames / TravelerDateFramelist / TravelerDataFrame / startYear | O / 1 | M / 1 | [1600-2] 7.6.27 |
| FA-TIM-S-011 | dataFrames / TravelerDateFramelist / TravelerDataFrame / startTime | M / 1 | M / 1 | [1600-3] 7.6.29 |
| FA-TIM-S-012 | dataFrames / TravelerDateFramelist / TravelerDataFrame / durationTime | M / 1 | M / 1 | 7.6.9 |
| FA-TIM-S-013 | dataFrames / TravelerDateFramelist / TravelerDataFrame / priority | M / 1 | M / 1 | 7.6.22 |
| FA-TIM-S-014 | dataFrames / TravelerDateFramelist / TravelerDataFrame / notUsed1 | M / 1 | M / 1 |  |
| FA-TIM-S-015 | dataFrames / TravelerDateFramelist / TravelerDataFrame / regions | M / 1 | M / 1 | 7.5.7 |
| FA-TIM-S-016 | dataFrames / TravelerDateFramelist / TravelerDataFrame / regions / GeographicalPath | M / 16 | M / 1 | 7.5.7 |
| FA-TIM-S-017 | dataFrames / TravelerDateFramelist / TravelerDataFrame / regions / GeographicalPath / regional | O / 1 | O / 1 | 7.5.26 |
| FA-TIM-S-018 | dataFrames / TravelerDateFramelist / TravelerDataFrame / regions / GeographicalPath / regional / regionId | M / 1 | M / 1 | 7.5.29 |
| FA-TIM-S-019 | dataFrames / TravelerDateFramelist / TravelerDataFrame / regions / GeographicalPath / regional / regExtValue | M / 1 | M / 1 | 7.5.8 |
| FA-TIM-S-020 | dataFrames / TravelerDateFramelist / TravelerDataFrame / regions / GeographicalPath / regional / GeographicalPath-KOR | M / 1 | M / 1 | 7.5.8 |
| FA-TIM-S-021 | dataFrames / TravelerDateFramelist / TravelerDataFrame / regions / GeographicalPath / regional / GeographicalPath-KOR / regions | M / 1 | M / 1 | 7.5.8 |
| FA-TIM-S-022 | dataFrames / TravelerDateFramelist / TravelerDataFrame / regions / GeographicalPath / regional / GeographicalPath-KOR / regions / RegionDescribedByID-KOR | C / 1 | C / 1 | 7.5.32 |
| FA-TIM-S-023 | dataFrames / TravelerDateFramelist / TravelerDataFrame / regions / GeographicalPath / regional / GeographicalPath-KOR / regions / RegionDescribedByID-KOR / linkID | M / 32 | M / 32 | 7.5.32 |
| FA-TIM-S-024 | dataFrames / TravelerDateFramelist / TravelerDataFrame / notUsed2 | M / 1 | M / 1 | 제2부 7.6.75 |
| FA-TIM-S-025 | dataFrames / TravelerDateFramelist / TravelerDataFrame / notUsed3 | M / 1 | M / 1 | 제2부 7.6.75 |
| FA-TIM-S-026 | dataFrames / TravelerDateFramelist / TravelerDataFrame / content | C / 1 | C / 1 | 7.5.10, 7.5.52 7.5.6, 7.5.42 7.5.5 |
| FA-TIM-S-027 | dataFrames / TravelerDateFramelist / TravelerDataFrame / content / ITISCodeAndText | M / 1 | M / 1 | 7.5.10 |
| FA-TIM-S-028 | dataFrames / TravelerDateFramelist / TravelerDataFrame / content / ITISCodeAndText / item | M / 100 | M / 1 | 7.5.10 |
| FA-TIM-S-029 | dataFrames / TravelerDateFramelist / TravelerDataFrame / content / ITISCodeAndText / item / itis | M / 1 | M / 1 | 7.6.6 |
| FA-TIM-S-030 | regional | O / 1 | O / 1 | 7.5.31 |
| FA-TIM-S-031 | regional / regionId | M / 1 | M / 1 | 7.5.29 |
| FA-TIM-S-032 | regional / TravelerInformation-KOR | M / 4 | M / 1 | 7.5.49 |
| FA-TIM-S-033 | regional / TravelerInformation-KOR / additionalInfo | O / 8 | O / 8 | 7.5.47 |
| FA-TIM-S-034 | regional / TravelerInformation-KOR / additionalInfo / dataFrameIndex | M / 1 | M / 1 | - |
| FA-TIM-S-035 | regional / TravelerInformation-KOR / additionalInfo / events | O / 1 | O / 1 | [1600-4] 7.5.5 |
| FA-TIM-S-036 | regional / TravelerInformation-KOR / additionalInfo / events / text | O / 8 | O / 1 | - |

## 부록 Ⅱ-2 — TIM 차로변경

근거: 부록 Ⅱ-2, 표 Ⅱ-2의 해당 제목, p.141부터. 출처 분류: `규정값`. 자료형·범위·길이는 KS R 1600 준용, 해당 판 원전 확인 전 미정. 표의 반복수는 원문 수치를 보존하며 최대치/정확한 개수 의미는 R-TIM02/Q20을 함께 읽는다.

| ID | 표 내 필드 위치 | KS M/O·반복 | ITSK M/O·반복 | 참조 절(원문 표기) |
|---|---|---|---|---|
| FA-TIM-L-003 | msgCnt | M / 1 | M / 1 | [1600-2] 7.6.48 |
| FA-TIM-L-004 | packetID | O / 1 | M / 1 | 7.6.25 |
| FA-TIM-L-005 | dataFrames | M / 1 | M / 1 | 7.5.48 |
| FA-TIM-L-006 | dataFrames / TravelerDateFramelist | M / 1 | M / 1 | 7.5.48 |
| FA-TIM-L-007 | dataFrames / TravelerDateFramelist / TravelerDataFrame | M / 8 | M / 1 | 7.5.46 |
| FA-TIM-L-008 | dataFrames / TravelerDateFramelist / TravelerDataFrame / frameType | M / 1 | M / 1 | 7.6.24 |
| FA-TIM-L-009 | dataFrames / TravelerDateFramelist / TravelerDataFrame / msgId | C / 1 | M / 1 | 7.5.38 [1600-4] 7.6.6 |
| FA-TIM-L-010 | dataFrames / TravelerDateFramelist / TravelerDataFrame / startYear | O / 1 | M / 1 | [1600-2] 7.6.27 |
| FA-TIM-L-011 | dataFrames / TravelerDateFramelist / TravelerDataFrame / startTime | M / 1 | M / 1 | [1600-3] 7.6.29 |
| FA-TIM-L-012 | dataFrames / TravelerDateFramelist / TravelerDataFrame / durationTime | M / 1 | M / 1 | 7.6.9 |
| FA-TIM-L-013 | dataFrames / TravelerDateFramelist / TravelerDataFrame / priority | M / 1 | M / 1 | 7.6.22 |
| FA-TIM-L-014 | dataFrames / TravelerDateFramelist / TravelerDataFrame / notUsed1 | M / 1 | M / 1 |  |
| FA-TIM-L-015 | dataFrames / TravelerDateFramelist / TravelerDataFrame / regions | M / 1 | M / 1 | 7.5.7 |
| FA-TIM-L-016 | dataFrames / TravelerDateFramelist / TravelerDataFrame / regions / GeographicalPath | M / 16 | M / 1 | 7.5.7 |
| FA-TIM-L-017 | dataFrames / TravelerDateFramelist / TravelerDataFrame / regions / GeographicalPath / regional | O / 1 | O / 1 | 7.5.26 |
| FA-TIM-L-018 | dataFrames / TravelerDateFramelist / TravelerDataFrame / regions / GeographicalPath / regional / regionId | M / 1 | M / 1 | 7.5.29 |
| FA-TIM-L-019 | dataFrames / TravelerDateFramelist / TravelerDataFrame / regions / GeographicalPath / regional / regExtValue | M / 1 | M / 1 | 7.5.8 |
| FA-TIM-L-020 | dataFrames / TravelerDateFramelist / TravelerDataFrame / regions / GeographicalPath / regional / GeographicalPath-KOR | M / 1 | M / 1 | 7.5.8 |
| FA-TIM-L-021 | dataFrames / TravelerDateFramelist / TravelerDataFrame / regions / GeographicalPath / regional / GeographicalPath-KOR / regions | M / 1 | M / 1 | 7.5.8 |
| FA-TIM-L-022 | dataFrames / TravelerDateFramelist / TravelerDataFrame / regions / GeographicalPath / regional / GeographicalPath-KOR / regions / RegionDescribedByID-KOR | C / 1 | C / 1 | 7.5.32 |
| FA-TIM-L-023 | dataFrames / TravelerDateFramelist / TravelerDataFrame / regions / GeographicalPath / regional / GeographicalPath-KOR / regions / RegionDescribedByID-KOR / linkID | M / 32 | M / 32 | 7.5.32 |
| FA-TIM-L-024 | dataFrames / TravelerDateFramelist / TravelerDataFrame / notUsed2 | M / 1 | M / 1 | 제2부 7.6.75 |
| FA-TIM-L-025 | dataFrames / TravelerDateFramelist / TravelerDataFrame / notUsed3 | M / 1 | M / 1 | 제2부 7.6.75 |
| FA-TIM-L-026 | dataFrames / TravelerDateFramelist / TravelerDataFrame / content | C / 1 | C / 1 | 7.5.10, 7.5.52 7.5.6, 7.5.42 7.5.5 |
| FA-TIM-L-027 | dataFrames / TravelerDateFramelist / TravelerDataFrame / content / ITISCodeAndText | M / 1 | M / 1 | 7.5.10 |
| FA-TIM-L-028 | dataFrames / TravelerDateFramelist / TravelerDataFrame / content / ITISCodeAndText / item | M / 100 | M / 1 | 7.5.10 |
| FA-TIM-L-029 | dataFrames / TravelerDateFramelist / TravelerDataFrame / content / ITISCodeAndText / item / itis | M / 1 | M / 1 | 7.6.6 |
| FA-TIM-L-030 | regional | O / 1 | O / 1 | 7.5.31 |

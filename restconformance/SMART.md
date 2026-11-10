# 스마트교차로 1분 교통정보 양측 시험

**시험방법 증적 보완:** 현재 두 시나리오는 각각 7개 항목(총 14개)이며, 표준 요구 확인 5개와 추가 검증 9개를 구분한다. 자료 부재 오류응답을 빈 정상응답과 분리했다. 데이터 규격 SMART-STANDARD-001은 유지하고 방법·증적은 [REST-EVIDENCE-002](FULL-METHOD.md)를 적용한다. 아래 12항목 검증은 보완 전 이력이다.

**등록·실행 검증 완료:** 제공시험 [60](https://106.250.189.37:8443/test/scenario/60), 요청시험 [61](https://106.250.189.37:8443/test/scenario/61). 12항목·120회 교환·240개 메시지 표시와 상대 증적 대조를 확인했다. [실행 결과와 남은 경계](../doc/gyeong4/2026-v2.1/smart-platform-verification-20260924.md)를 따른다. 등록 시 TSB 첨부 묶음 제목은 `scenario`로 지정한다.

개발 기준 **SMART-STANDARD-001**: 정상 데이터 구조·자료형·길이·정밀도·필수 여부는 제3부 표 4-23을 따른다. API는 GET `/v1/adxc/smt-l-raws`, JSON 매체, Bearer 접점과 같은 호출 정보에 참고한다. 오류 코드 미정 부분은 기존 REST 시험 profile을 적용한다. [차이·미명시 사항](../doc/ambiguities_and_risks.md)을 기준 차이 이력으로 관리한다.

| 역할 | case | 기본 포트 |
|---|---|---|
| UT 센터 대상 스마트교차로 1분 교통정보 제공시험 | `microClient2center_smart_v1` | 55341 |
| 미시교통정보 플랫폼 대상 스마트교차로 1분 교통정보 요청시험 | `centerServer2micro_smart_v1` | 55342 |

각각 기존 [REST 전체 시험방법](FULL-METHOD.md)과 같은 정상·오류·자료 부재 6개 항목을 사용한다. 제공측은 정상+오류 5항목과 빈 자료 1항목을 별도 데이터 상태에서 실행한다. 요청측은 대상 내부 수신·처리 기록을 독립 대조하며 EVIDENCE_PENDING을 자동 성공으로 바꾸지 않는다. 모든 회차 송신·수신 메시지를 개별 JSON 첨부로 보낸다.

| JSON 키 | 표준 필드 | 필수 | 검사 |
|---|---|---|---|
| collectDate | COLLECT_DATE | M | 문자열 YYYYMMDDhhmmss, 실제 달력·시각 |
| nodeId | NODE_ID | M | 문자열, VARCHAR(10) |
| linkId | LINK_ID | M | 문자열, VARCHAR(10) |
| ascrId | ASCR_ID | M | 문자열, VARCHAR(10) |
| laneNo | LANE_NO | M | JSON 숫자, NUMBER(1) |
| vkndCd | VKND_CD | M | JSON 숫자, NUMBER(1) |
| spd | SPD | M | JSON 숫자, NUMBER(5,2) |
| vol | VOL | M | JSON 숫자, NUMBER(7) |

최상위는 표준 JSON 예시의 레코드 배열이다. 숫자는 부동소수점 반올림으로 통과시키지 않고 정확한 십진 자릿수를 검사한다. 표준에 없는 코드 열거·부호 하한은 임의 적용하지 않는다. 실제 1분 갱신 주기와 업무 값의 정확성까지 단일 요청 반복으로 검증했다고 주장하지 않는다.

```powershell
# UT 센터 서버 상대역
restconformance/emulator/Start-RestMethodSut.ps1 -Scenario SC11-SMT
# 미시교통정보 플랫폼 클라이언트 상대역 (시험기 수신 준비 후)
restconformance/emulator/Start-RestMethodSut.ps1 -Scenario SC32-SMT -Requests 60
```

구현 순서: 원문 필드·이슈 기록 → 표준 validator·양측 case → 독립 상대역 → 로컬 판정·회귀 → 플랫폼 등록·실행·메시지 표시 및 증적 대조. 기존 VDS·UTIC의 case, 판정, 과거 결과는 유지한다. 플랫폼 ID와 최종 검증 상태는 등록 manifest 및 완료 기록에 반영했다.

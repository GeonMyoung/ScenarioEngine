# 차량–RSE DATEX 시험 실행

> **현재 v8 판정:** ScenarioEngine에는 COMPLETE와 사후 증적 제출 상태가 없다. 정상 절차를 마친 시험은 SUCCESS다. 아래의 과거 EVIDENCE_PENDING·사후 검토 설명은 당시 이력이며 현재 실행 조건이 아니다. 명시적 부적합·통신 오류·사용자 중지는 성공으로 바꾸지 않는다.
현재 개발·검증에서는 독립 에뮬레이터 프로세스를 시험 대상 시스템으로 사용한다. 플랫폼에 표시하는 설명과 구분한 운영 안내다. PROFILE-002에 따라 기존 DATEX/TCP 세션과 메시지 처리를 재사용한다.

| 설계 ID / 플랫폼 ID | 시험 이름 | 시험 시스템 / 대상 역할 | case | 포트 |
|---|---|---|---|---:|
| SC20 / [52](https://106.250.189.37:8443/test/scenario/52) | RSE BSM 정보요청 시험 | 차량 ISO 14827 Server / RSE ISO 14827 Client | `vehicleServer2rse_v2` | 55420 |
| SC21 / [53](https://106.250.189.37:8443/test/scenario/53) | RSE SPaT·MAP·RSA·TIM 정보제공 시험 | 차량 ISO 14827 Client / RSE ISO 14827 Server | `vehicleClient2rse_v2` | 55421 |
| SC24 / [54](https://106.250.189.37:8443/test/scenario/54) | 자율주행차량 BSM 정보제공 시험 | RSE ISO 14827 Client / 차량 ISO 14827 Server | `rseClient2vehicle_v2` | 55424 |
| SC25 / [55](https://106.250.189.37:8443/test/scenario/55) | 자율주행차량 SPaT·MAP·RSA·TIM 정보요청 시험 | RSE ISO 14827 Server / 차량 ISO 14827 Client | `rseServer2vehicle_v2` | 55425 |

각 case의 `registration/<case>.example.json`과 `emulator/<case>.sut.json`을 사용한다. 예제는 TESTER/SUT 도메인, 합성 시험 계정, H/R 60/40초, 정상 FrED 유지 300초, 취소 전 120초, 요청 주기 1초다.

## 실행 순서

1. 해당 플랫폼 시험에서 자체 시험을 열고, 그 회차의 Agent URL로 [엔진 실행 스크립트](../tools/Start-PlatformEngine.ps1)를 실행한다.
2. 시험 환경설정에 case별 예제의 접속·도메인·시간 값을 입력하고 필요한 항목을 선택한 뒤 **설정**을 누른다.
3. 제공 대상 SC21/SC24는 **환경설정을 모두 마친 뒤** 상대 프로그램을 실행하고 시험을 시작한다. 상대 프로그램을 너무 일찍 실행하면 설정 중 접속 대기시간이 만료될 수 있다.
4. 요청 대상 SC20/SC25는 시험을 시작해 수신 대기한 뒤 상대 프로그램을 실행한다. 회차별 로그를 새 파일로 보관한다.
5. 같은 포트를 쓰는 다음 회차는 이전 상대 프로그램의 종료·포트 해제를 확인한 뒤 시작한다.

```powershell
.\datexconformance\emulator\Start-ScenarioSut.ps1 -Scenario SC24 -Sessions 8
.\datexconformance\emulator\Start-ScenarioSut.ps1 -Scenario SC25 -Message tim_regional
```

| 시험 | 선택 묶음 | 상대 실행 옵션 |
|---|---|---|
| SC20 | BSM 요청·정보요청 재전송·6종 Publication 오류 거부: 8개 | `-Scenario SC20 -Message bsm -Sessions 8` |
| SC20 | 정상 세션·로그인 재전송: 2개 | `-Scenario SC20 -Message bsm -Request session -Sessions 2` |
| SC21 | 일반 SPaT·MAP·RSA·TIM과 공통 절차: 11개 | `-Scenario SC21 -Sessions 11` |
| SC21 | TIM 제한속도·차로변경·국내 확장: 각 1개씩 별도 회차 | `-Scenario SC21 -Message tim_speed` / `tim_lane` / `tim_regional` |
| SC24 | 전체: 8개 | `-Scenario SC24 -Sessions 8` |
| SC25 | SPaT 요청·정보요청 재전송·6종 오류 거부: 8개 | `-Scenario SC25 -Message spat -Sessions 8` |
| SC25 | 일반 MAP·RSA·TIM 요청: 3개 | `-Scenario SC25 -Message 'map,rsa,tim' -Sessions 3` |
| SC25 | 정상 세션·로그인 재전송: 2개 | `-Scenario SC25 -Message spat -Request session -Sessions 2` |
| SC25 | TIM 제한속도·차로변경·국내 확장: 각 1개씩 별도 회차 | `-Scenario SC25 -Message tim_speed` / `tim_lane` / `tim_regional` |

BSM은 CommRxPDU, MAP·RSA·TIM은 CommTxPDU, SPaT는 기존 차량 DATEX 경로의 ExtentionCommPDU를 사용한다. 메시지별 구독 OID를 유지하며, 같은 PSID를 쓰는 TIM 변형들은 별도 회차로 실행한다.

## TIM 국내 확장 디코딩

`tim_regional`은 정상 TIM 안에 한국(regionId 4)의 `TravelerInformation-KOR`와 `GeographicalPath-KOR`를 넣은 시험 자료다. 기본 TIM 디코딩 뒤 내부 OpenType까지 해당 ASN.1 디코더로 읽는다. 결과 로그의 `TIM_REGIONAL_DECODE`에는 실제 디코딩한 두 구조의 개수와 해석하지 않은 타 지역 확장 개수를 구분해 기록한다.

선택 확장이 없는 일반 TIM도 허용한다. 확장 바이트가 잘려 있으면 외곽 TIM이 정상 디코딩되더라도 내부 디코딩 실패로 판정한다. 로그상의 `opaqueOtherRegions`는 해석하지 않은 다른 지역의 확장이므로 국내 확장 디코딩 성공에 합산하지 않는다. 속도·차로 지시의 운영상 타당성은 검사하지 않는다.

요청시험의 정상 송수신 결과는 기존 정책에 따라 `EVIDENCE_PENDING`으로 보존하고, 대상의 수신·디코딩·처리 기록을 대조한 결과를 별도로 보관한다. 실제 장비 상호운용과 웹 최종 보고서 반영은 별도 단계다.

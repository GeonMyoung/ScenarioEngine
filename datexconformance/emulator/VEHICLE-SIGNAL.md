# 차량·신호정보 DATEX 시험 실행

> **현재 v8 판정:** ScenarioEngine에는 COMPLETE와 사후 증적 제출 상태가 없다. 정상 절차를 마친 시험은 SUCCESS다. 아래의 과거 EVIDENCE_PENDING·사후 검토 설명은 당시 이력이며 현재 실행 조건이 아니다. 명시적 부적합·통신 오류·사용자 중지는 성공으로 바꾸지 않는다.
기존 DATEX 엔진과 독립 SUT 프로세스를 재사용한다. 플랫폼 공개 설명과 별개인 개발·시험 운영 안내다.

| 설계 ID / 플랫폼 ID | 시험 대상·기능 | case | 시험기 / SUT | 포트 |
|---|---|---|---|---:|
| SC03 / 46 | UT 센터의 차량 BSM 요청 | `vehicleServer2center_v2` | Server / Client | 55201 |
| SC22 / 47 | 자율주행차량의 BSM 제공 | `centerClient2vehicle_v2` | Client / Server | 55202 |
| SC04 / 48 | UT 센터의 차량 SPaT·RSA·TIM 제공 | `vehicleClient2center_v2` | Client / Server | 55203 |
| SC23 / 49 | 자율주행차량의 SPaT·RSA·TIM 요청 | `centerServer2vehicle_v2` | Server / Client | 55204 |
| SC05 / 50 | UT 센터의 신호정보 SPaT·TLSM 요청 | `signalserverServer2center_v2` | Server / Client | 55205 |

각 `registration/<case>.example.json`과 `emulator/<case>.sut.json`에 역할별 입력 예제가 있다. 합성 테스트 계정만 포함한다. H/R 60/40초, 정상 FrED 유지 300초, 취소 전 120초, 요청 주기 1초를 사용했다.

## 실행 순서

1. 플랫폼에서 해당 시험의 자체 시험을 열고 [Start-PlatformEngine.ps1](../tools/Start-PlatformEngine.ps1)에 그 회차의 Agent URL을 전달한다.
2. 시험기 역할에 맞는 주소·도메인·계정·시간을 입력하고 아래 묶음의 항목을 선택한다.
3. SC22·SC04의 제공 SUT는 시험 시작 전에 수신 대기한다. SC03·SC23·SC05의 요청 SUT는 시험기를 시작해 수신 대기 포트를 연 뒤 접속한다.
4. 아래 명령은 저장소 루트에서 실행한다. 새 실행마다 로그 파일을 새로 만든다.

```powershell
.\datexconformance\emulator\Start-ScenarioSut.ps1 -Scenario SC22 -Sessions 8
.\datexconformance\emulator\Start-ScenarioSut.ps1 -Scenario SC03 -Request single -Sessions 8
```

| 시나리오 | 화면에서 선택할 항목 | SUT 옵션 |
|---|---|---|
| SC22 | 전체 8개 | `-Scenario SC22 -Sessions 8` |
| SC03 | BSM 요청·구독 재전송·6종 오류 거부 | `-Scenario SC03 -Sessions 8` |
| SC03 | 정상 세션·로그인 재전송 | `-Scenario SC03 -Request session -Sessions 2` |
| SC04 | 일반 SPaT·RSA·TIM 및 공통 시험 10개 | `-Scenario SC04 -Sessions 10` |
| SC04 | TIM 제한속도 변경 1개 | `-Scenario SC04 -Message tim_speed` |
| SC04 | TIM 차로변경 1개 | `-Scenario SC04 -Message tim_lane` |
| SC23 | SPaT 요청·구독 재전송·6종 오류 거부 | `-Scenario SC23 -Message spat -Sessions 8` |
| SC23 | 일반 RSA·TIM 요청 2개 | `-Scenario SC23 -Message rsa,tim -Sessions 2` |
| SC23 | 정상 세션·로그인 재전송 | `-Scenario SC23 -Request session -Sessions 2` |
| SC23 | TIM 제한속도 또는 차로변경 1개씩 | `-Scenario SC23 -Message tim_speed` 또는 `tim_lane` |
| SC05 | SPaT·TLSM 요청·구독 재전송·6종 오류 거부 | `-Scenario SC05 -Sessions 9` |
| SC05 | 정상 세션·로그인 재전송 | `-Scenario SC05 -Request session -Sessions 2` |

SPaT와 RSA/TIM은 구독 OID가 다르다. 일반 TIM과 통행지시 프로파일은 같은 PSID를 사용하므로 프로파일별 데이터를 준비한 별도 회차로 실행한다. 기본 `all`은 일반 메시지 집합이며 통행지시 변형을 동시에 섞지 않는다. 선택 항목 수와 `Sessions`를 맞춘다.

TIM 통행지시 검사는 packetID, 1개 프레임/구간, furtherInfoID `0x0C01/0x0C02`, startYear, reserved 값, 지시별 ITIS 코드 등 구현된 핵심 필드에 한정한다. 선택적 regional의 업무 의미 전체와 실제 도로 상황의 정확성을 검증한 것으로 확대하지 않는다.

TLSM은 기존 프로젝트 코덱의 MessageFrame 50을 사용한다. 제3부 TLSM 예제가 SPaT를 반복하는 불일치와 실제 상호운용 전 확인 조건은 [검증 결과](../../doc/gyeong4/2026-v2.1/remaining-datex-verification-20260923.md)에 기록했다.

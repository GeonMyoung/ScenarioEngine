# 신호정보 수집서버 SPaT·TLSM 정보제공 시험 실행

> **현재 v8 판정:** ScenarioEngine에는 COMPLETE와 사후 증적 제출 상태가 없다. 정상 절차를 마친 시험은 SUCCESS다. 아래의 과거 EVIDENCE_PENDING·사후 검토 설명은 당시 이력이며 현재 실행 조건이 아니다. 명시적 부적합·통신 오류·사용자 중지는 성공으로 바꾸지 않는다.
이 안내는 플랫폼 공개 설명과 구분한 개발·시험 운영 문서다. 현재 검증은 에뮬레이터를 시험 대상 시스템으로 사용한다.

## 양측 시험 구성

| 시험 대상 | 시험 시스템 역할 | 시험 이름 | 설계 / 플랫폼 ID | case |
|---|---|---|---|---|
| 통합교통관제시스템 / ISO 14827 Client | 신호정보 수집서버 / ISO 14827 Server | 통합교통관제시스템 SPaT·TLSM 정보요청 시험 | SC05 / [50](https://106.250.189.37:8443/test/scenario/50) | `signalserverServer2center_v2` |
| 신호정보 수집서버 / ISO 14827 Server | 통합교통관제시스템 / ISO 14827 Client | 신호정보 수집서버 SPaT·TLSM 정보제공 시험 | SC26 / [56](https://106.250.189.37:8443/test/scenario/56) | `centerClient2signalserver_v2` |

두 시험은 같은 연계 구간에서 시험 대상을 반대로 지정한다. 서버 역할의 정보 제공 기능과 서버 자체를 평가하는 정보제공 시험은 구분한다.

## SC26 실행

1. 플랫폼 ID 56에서 자체 시험을 연다.
2. 해당 회차의 Agent 접속 URL로 [Start-PlatformEngine.ps1](../tools/Start-PlatformEngine.ps1)를 실행한다.
3. `registration/centerClient2signalserver_v2.example.json`의 도메인·주소·포트·시간 값을 입력하고 시험 항목을 선택한 뒤 **설정**을 누른다. 예제 접속 대상은 `127.0.0.1:55526`이다.
4. 환경설정을 모두 마친 다음 아래 상대 프로그램을 실행한다. 너무 일찍 실행하면 설정 중 상대의 접속 대기시간이 만료될 수 있다.
5. 플랫폼에서 **시험 시작**을 누른다. 아래 9개를 모두 선택했다면 `Sessions`도 9로 맞춘다.

```powershell
.\datexconformance\emulator\Start-ScenarioSut.ps1 -Scenario SC26 -Sessions 9
```

SC26 세부 항목은 정상 세션 설정, SPaT 제공, TLSM 제공, 잘못된 로그인 거부, 중복 로그인 거부, 비정상 세션 감지, 잘못된 정보요청 거부, 정보제공 메시지 재전송, 주기 정보제공 및 구독 취소의 **9개**다.

예제는 합성 계정과 TESTER/SUT 도메인을 사용한다. H/R 60/40초, 정상 FrED 유지 300초, 취소 전 수신 120초, 요청 주기 1초를 적용한다. 무수신 종료는 대상이 실제 마지막으로 수신한 시각을 기준으로 확인한다.

## 메시지와 판정

- SPaT와 TLSM은 기존 채택 형식인 `1.0.14827.1.1.0` / ExtentionCommPDU를 사용한다.
- 두 메시지를 같은 발행 목록에 담아도 각 항목의 실제 MessageFrame을 읽어 SPaT 19 / TLSM 50을 구분한다. TLSM은 기존 KOR 코덱을 사용한다.
- 개별 정상 디코딩 결과를 플랫폼의 `test_normal_spat`, `test_normal_tls` 검증 응답과 연결한다.
- 재전송은 최초 발행과 같은 패킷번호·타임스탬프·내용인지 확인한다. 구독 취소 후에는 요청 주기 동안 신규 발행이 없고 세션 유지가 이어지는지 확인한다.
- 비정상 세션 종료의 자동 결과는 `EVIDENCE_PENDING`으로 보존한다. 대상 로그의 종료 원인·마지막 수신 시각을 대조한 결과를 별도로 보관한다.

에뮬레이터 로그의 `packetTimeUs`는 패킷 처리에 연결된 실제 송수신 시각이고, `monotonicUs`는 로그 기록 시각이다. 종료 로그의 `lastReceiveUs`와 혼용하지 않는다. 정상 정보제공의 목적은 실제 메시지 수신·디코딩이며 신호 운영의 업무 판단을 추가하지 않는다.

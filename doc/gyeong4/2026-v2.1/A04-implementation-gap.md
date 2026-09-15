# A04 — ScenarioEngine 구현 차이·영향 분석

관련 업무: **GM-65 / A04**. 선행: [A02](A02-interface-scope.md), [A03](A03-requirements.md).

## 1. 조사 기준과 결론

분석 기준 소스는 `3ea0d8c0744472566db083cf153f9f656df82b3e`다. Riido 기준 `5d29dc2`와 코드 차이는 없다. 제출 worktree는 중앙 역할 지침만 변경한 `b8aefaf`를 바탕으로 생성했으며 아래 코드 링크는 분석한 소스 버전에 고정한다.

**결론:** AP-DATEX 세션, CommRx/Tx PDU, ASN.1 UPER 변환, WebSocket 제어·판정 전달은 재사용 후보가 있다. 경4 전체의 API/DB/TCP Binary 및 차량 MQTT/V2N 연결과 부록 TIM 판정까지 완성된 상태는 확인되지 않았다. 소스가 존재한다는 사실·호출되는 경로·실제 시험 성공을 구분한다.

분류 의미:

- **재사용**: 해당 기반 기능과 호출 경로 존재. 새 규격 적합을 보장하는 표현 아님.
- **수정**: 기반은 있으나 규격·역할·관측 또는 프로파일 변화 필요.
- **신규**: 조사한 통합 엔진의 등록/호출 경로에서 해당 경4 기능을 찾지 못함. 외부 시스템 전체의 부재를 뜻하지 않음.
- **확인 필요**: 규격 해석·원전·외부 판정 구현/환경이 없어 현재 확정 불가.

## 2. 코드 근거 등록부

| 근거 | 실제 소스·시작 줄 | 확인 내용 |
|---|---|---|
| C01 | [ScenarioEngineEnvUtil.c:155](https://github.com/GeonMyoung/ScenarioEngine/blob/3ea0d8c0744472566db083cf153f9f656df82b3e/scenarioengine/src/ScenarioEngineEnvUtil.c#L155) | ITSK-00143-3-15784/14827 등의 category를 Iso14827TestHelper로 전달 |
| C02 | [Iso14827TestHelperCommandMsgProc.c:707](https://github.com/GeonMyoung/ScenarioEngine/blob/3ea0d8c0744472566db083cf153f9f656df82b3e/iso14827testhelper/src/Iso14827TestHelperCommandMsgProc.c#L707) | 경4 5개 역할의 구성→client1/server3 시나리오 생성(707~939) |
| C03 | [같은 파일:586](https://github.com/GeonMyoung/ScenarioEngine/blob/3ea0d8c0744472566db083cf153f9f656df82b3e/iso14827testhelper/src/Iso14827TestHelperCommandMsgProc.c#L586), [같은 파일:1608](https://github.com/GeonMyoung/ScenarioEngine/blob/3ea0d8c0744472566db083cf153f9f656df82b3e/iso14827testhelper/src/Iso14827TestHelperCommandMsgProc.c#L1608) | 구독 EAM OID·경4 메시지 API 집합 선택 |
| C04 | [Iso14827TestHelperScenario.c:13](https://github.com/GeonMyoung/ScenarioEngine/blob/3ea0d8c0744472566db083cf153f9f656df82b3e/iso14827testhelper/src/Iso14827TestHelperScenario.c#L13) | client1과 client1_tr는 다른 경로; 비슷한 파일명을 동일 실행 경로로 보지 않음 |
| C05 | [Iso14827TestHelperScenarioClient1.c:1095](https://github.com/GeonMyoung/ScenarioEngine/blob/3ea0d8c0744472566db083cf153f9f656df82b3e/iso14827testhelper/src/Iso14827TestHelperScenarioClient1.c#L1095) | PSID↔MessageFrame ID 검사. 이후 MAP/RSA/TIM(1118~1334), BSM(1350~1425) UPER 디코드·변환·validateRequest |
| C06 | [같은 파일:1494](https://github.com/GeonMyoung/ScenarioEngine/blob/3ea0d8c0744472566db083cf153f9f656df82b3e/iso14827testhelper/src/Iso14827TestHelperScenarioClient1.c#L1494), [ScenarioEngineEnvUtil.c:266](https://github.com/GeonMyoung/ScenarioEngine/blob/3ea0d8c0744472566db083cf153f9f656df82b3e/scenarioengine/src/ScenarioEngineEnvUtil.c#L266) | 판정 응답 OK→SUCCESS, 오류→FAIL; 웹 응답을 시험 모듈로 전달 |
| C07 | [Iso14827TestHelperScenarioServer3.c:895](https://github.com/GeonMyoung/ScenarioEngine/blob/3ea0d8c0744472566db083cf153f9f656df82b3e/iso14827testhelper/src/Iso14827TestHelperScenarioServer3.c#L895) | 신호 서버 역할 샘플 제공. SPaT 82055, TLS 분기 1234; 무효 publication에 10초 대기(931~934) |
| C08 | [TechnicalRegulation2MsgStructAPI.c:478](https://github.com/GeonMyoung/ScenarioEngine/blob/3ea0d8c0744472566db083cf153f9f656df82b3e/technicalregulation2/src/TechnicalRegulation2MsgStructAPI.c#L478) | ITSK Tx/Rx API: EAM `1.0.15784.1.0.1/.2` |
| C09 | [TechnicalRegulation1MsgStructAPI.c:1016](https://github.com/GeonMyoung/ScenarioEngine/blob/3ea0d8c0744472566db083cf153f9f656df82b3e/technicalregulation1/src/TechnicalRegulation1MsgStructAPI.c#L1016) | 경4 C2C 집합은 확장 EAM `1.0.14827.1.1.0` |
| C10 | [ITSK00100_3MsgStructAPI.c:535](https://github.com/GeonMyoung/ScenarioEngine/blob/3ea0d8c0744472566db083cf153f9f656df82b3e/ITSK00100_3Util/src/ITSK00100_3MsgStructAPI.c#L535) | 돌발검지/종료·영상·제어/센서·이동객체 응답 API. 같은 OID 문자열도 선택된 메시지 API에 따라 구조가 달라짐 |
| C11 | [ItsIso14827SessionMgr_main.c:300](https://github.com/GeonMyoung/ScenarioEngine/blob/3ea0d8c0744472566db083cf153f9f656df82b3e/ItsIso14827/src/ItsIso14827SessionMgr_main.c#L300), [같은 파일:772](https://github.com/GeonMyoung/ScenarioEngine/blob/3ea0d8c0744472566db083cf153f9f656df82b3e/ItsIso14827/src/ItsIso14827SessionMgr_main.c#L772) | codecRule 기반 DATEX decode/encode 및 TCP 전송. 소켓·세션·도메인 계층 존재 |
| C12 | [GitsnAsnUtil.c:5526](https://github.com/GeonMyoung/ScenarioEngine/blob/3ea0d8c0744472566db083cf153f9f656df82b3e/GitsnAsnUtil/src/GitsnAsnUtil.c#L5526), [같은 파일:2488](https://github.com/GeonMyoung/ScenarioEngine/blob/3ea0d8c0744472566db083cf153f9f656df82b3e/GitsnAsnUtil/src/GitsnAsnUtil.c#L2488) | MessageFrame UPER 추출, TIM furtherInfoID의 2-byte 값 변환 |
| C13 | [GitsnAsn1.asn:4955](https://github.com/GeonMyoung/ScenarioEngine/blob/3ea0d8c0744472566db083cf153f9f656df82b3e/GitsnAsnUtil/GitsnAsn1.asn#L4955), [같은 파일:5042](https://github.com/GeonMyoung/ScenarioEngine/blob/3ea0d8c0744472566db083cf153f9f656df82b3e/GitsnAsnUtil/GitsnAsn1.asn#L5042), [같은 파일:5325](https://github.com/GeonMyoung/ScenarioEngine/blob/3ea0d8c0744472566db083cf153f9f656df82b3e/GitsnAsnUtil/GitsnAsn1.asn#L5325) | GeographicalPath-KOR, TravelerInformation-KOR, TrafficLightStatusMessage 정의 존재; 채택 KS 판과 동등성은 미확정 |
| C14 | [Iso14827TestHelperEnvUtil.c:418](https://github.com/GeonMyoung/ScenarioEngine/blob/3ea0d8c0744472566db083cf153f9f656df82b3e/iso14827testhelper/src/Iso14827TestHelperEnvUtil.c#L418) | raw/data를 판정 요청 문맥에 담고 메인/웹에 연결하는 경로 |

검색 범위는 위 모듈의 실제 `.c/.h/.tdc/.tjsonc/.asn`와 VS2022 프로젝트 등록이다. `MQTT`, `Quadtree`, `V2N`, `container_type`, `POL7_INCIDENT`, `NTIC_VDS_INFO`, `SHAD_TRAF_INFO`, `INT_ALL_STATUS`, `BmsInfo` 및 경4 역할명을 검색하고 연관 함수 본문을 읽었다. 문자열 미검출만으로 다른 명칭/외부 구현의 부재를 단정하지 않으며, C01~C03의 등록 경로와 함께 ‘신규 후보’를 판단했다.

## 3. 기존 경4 실행 경로와 SUT 역할

| 에이전트 시나리오 | 에이전트 역할 → SUT | 업무 데이터 방향 | 구성/판정 근거 | 재사용 한계 |
|---|---|---|---|---|
| centerClient2rse | 센터 client → RSE server | RSE→센터 BSM | C02:707, C03, C05 BSM | BSM decode와 외부 판정 경로; KS 판·1초 측정 별도 |
| rseServer2center | RSE server → 센터 client | RSE→센터 BSM | C02:764, server3 | 수신 SUT에 제공하는 역할; 수신 내부 반영은 별도 관측 |
| rseClient2center | RSE client → 센터 server | 센터→RSE MAP/RSA/TIM | C02:805, C05 | 주석 일부는 BSM 제공이라고 되어 있으나 실제 validate_set은 MAP/RSA/TIM |
| centerServer2rse | 센터 server → RSE client | 센터→RSE MAP/RSA/TIM | C02:862, server3 | 제공 샘플·구독 처리 재사용; 신규 TIM 2개 프로파일 검증 근거 부족 |
| signalserverServer2center | 신호정보 server → 센터 client | 서버→센터 SPaT/TLSM | C02:902, C07/C09 | 해당 코드에서 반대편 센터 에이전트의 전용 경4 등록은 못 찾음 |

C02가 만드는 경4 client는 `client1`이다. `Iso14827TestHelperScenarioClient1_TechnicalRegualtion.c`에 비슷한 경4 이름/주석이 있어도 별도 `client1_tr` 경로를 실제 호출 근거 대신 사용하지 않았다.

## 4. 요구사항–구현 대응표

필드 사전 `F4-xx-*`는 같은 표의 `R-Mxx` 행에 **모두 상속 연결**된다. 부록 `FA-TIM-S/L-*`는 R-TIM01~12에 연결된다. 이 규칙으로 개별 필드가 코드 대응 없이 남지 않게 하되, 외부 원전 미확보 상태까지 구현 완료로 표시하지 않는다.

| 요구사항/인터페이스 | 코드 근거 | 분류 | 차이·다음 단계 |
|---|---|---|---|
| R-ID01~05, OID-* 전체 | C03/C08/C09/C10 | 수정 + 확인 필요 | 규격 OID와 EAM OID·PSID의 역할을 데이터 모델에서 구분. Q06/Q11 해결 후 매핑 |
| R-M01 / F4-01-* / IF-F01 | C01/C02/C10 | 신규 | 기존 돌발 EAM 응답은 POL7_INCIDENT API JSON과 같지 않음. endpoint/필드/100ms 관측 계약 필요 |
| R-M03~06 / IF-F02~05 | C01/C02/C05/C11/C12 | 신규 + 재사용 + 확인 필요 | V2X codec 기반 재사용 가능. 차량 역할/MQTT/V2N 연결은 신규, AP-DATEX 적용 Q04 대기 |
| R-M07 / IF-F06 | C02/C03/C05/C08/C12 | 수정 | 기존 BSM 양 역할 재사용. 채택 KS 판, 원시 데이터 보존·주기 판정 보완 |
| R-M08~10 / IF-F07~09 | C02/C03/C05/C08/C13 | 수정 | MAP/RSA/TIM 경로 유지 후보. OID 충돌·TIM 강화 조건·경4별 판정 규칙 해결 |
| R-M11/13/14 / F4-11/13/14-* / IF-C01/04/05 | C01/C02/C10 | 신규 | DATEX 일반 교통정보 구조가 DB 스키마를 대신하지 않음. DB adapter·키/시간/NULL 검증 필요 |
| R-M12/15/16 / F4-12/15/16-* / IF-C03/06/02 | C01/C02/C10 | 신규 | API JSON/XML 경4 구조·요청/응답 계약과 관측이 필요 |
| R-M17 / IF-C07 | C01의 ITSK-00144-2 분기, C12/C13 | 확인 필요 + 수정/신규 후보 | 인접 표준 모듈 존재와 이 C2C 역할의 구현은 다름. JSON vs BER/UPER·채택판 Q07 후 설계 |
| R-M18~21 / F4-18~21-* / IF-C08~11 | C01/C02 | 신규 | API/base64·장치/서버·음영구간의 등록 및 판정 구조 신규. Q09/Q14~18 선행 |
| R-M22/23 / F4-22/23-* / IF-C12/13 | C01/C02 | 신규 | 입력 DB와 출력 JSON의 필드 매핑·주기·관측을 별도 정의 |
| R-M24~29 / F4-24~29-* / IF-C14~19 | C01/C02/C11 | 신규 | ItsIso14827의 TCP 소켓은 재사용 검토 가능하나 Binary 전문은 다른 계약. framing/endian/LRC/반복수 설계 필요 |
| R-M30/31 / IF-C20/21 | C02/C07/C09/C13 | 수정 + 확인 필요 | 확장 EAM 샘플 제공 존재. 1234를 표준 PSID로 확정 금지; TLSM/SPaT 예제 혼재 및 반대 역할 확인 |
| IF-X01~05 / OID-X01~05 | C01~C03의 경4 등록 목록 | 확인 필요 | F2F 전용 역할 등록·독립 상세 미식별. 기존 RSE↔센터를 이름만 바꿔 대체 금지 |
| IF-G01~08 / 관련 OID | C01~C03 | 확인 필요(내부 개념 IF-G07은 제외) | OID만 있는 항목·PVD/TSI/내부 흐름의 요구 범위를 먼저 결정 |
| R-MQ01~07 | C01/C02 + 아래 prj22 후보 | 신규 | MQTT 연결·Topic·격자 이동·LWT·재접속·관측 상태 |
| R-VN01~11 | C12의 payload 추출 기반 | 신규 | V2N wrapper는 MessageFrame과 별도. REF09 확보 후 boundary-safe parser/검증 설계 |
| R-TIM01~12, FA-TIM-* | C05/C12/C13/C14 | 수정 + 확인 필요 | 한국 확장 구조 존재. 0x0C01/02, 필수화, 단일 frame/path/item의 전용 판정은 확인 못 함 |
| R-REF01~06 | C05/C12/C13 | 확인 필요 | 저장 ASN.1의 타입 존재와 KS/SAE 채택판 일치는 다름. 원전·생성기·golden vector 확인 |
| R-SC01~08 | 위 해당 R-M/필드 행, C14 | 신규/수정(상위 행 상속) | 스키마 선택, 범위·누락·예외값, 규정/예제 분리 |
| R-TM01~06 | C07의 시나리오 timer, C11, C14 | 수정 + 확인 필요 | 기존 10초/구독 대기값은 경4 전송 1초/100ms 기준이 아님. 기산점·오차·표본수 설계 |

## 5. 주요 구현 영향

1. **제어·판정 경계(C01/C06/C14):** WebSocket 요청→모듈→raw/decoded 전달→외부 판정 응답 흐름이 있다. 프런트/웹 판정 규칙은 통합 저장소 포함 범위 밖이므로 이 C 코드 검토만으로 전체 validator의 완전성을 결론내릴 수 없다(Q21).
2. **프로토콜 경계(C03/C08~11):** 공통 TCP 전송과 DATEX 메시지 해석을 분리해야 API/DB/Binary를 같은 코드 경로에 억지로 넣지 않는다. 경4 OID를 `1.0.15784.*`에 일괄 대입하면 기존 EAM 계약을 깨뜨릴 수 있다.
3. **인코딩(C05/C12/C13):** UPER 디코딩 성공은 구문 유효성의 일부 근거다. KS 판별, 미사용/선택 필드 조건, TIM 서비스 식별·수치 단위 검증은 별도다. 생성 C/H/TDO와 ASN.1/정의 파일의 출처·동기화도 후속 설계에서 확인한다.
4. **관측(A02 §6):** 새 경로에는 원시 바이트·직렬화된 필드·Topic/EAM/PSID/MessageFrame ID·양 방향 시각·판정 기준 버전을 연계할 필요가 있다. 구현에 앞서 Q10/Q21의 관측 계약을 결정한다.
5. **샘플(C07/C09):** 일부 sample 생성 보조함수는 곧바로 TRUE를 반환한다(TechnicalRegulation1MsgStructAPI.c:990~999). 호출되지 않은 helper의 존재나 성공 반환만으로 유효 샘플 생성/시험 성공을 입증하지 않는다.

## 6. prj22 재사용 후보 — 별도 이식 범위

읽기 전용 비교 위치: `C:\Implement\prj22\agent`, 원격 `GeonMyoung/Prj22Agent`, HEAD `afbcb6046a96b68d54b2d94e9672d8370275fbe4`. 아래 비교 대상에는 **미커밋 수정**이 있다. HEAD 링크만으로 로컬 비교본을 재현할 수 없어 파일 해시를 함께 기록한다.

| 후보 | 실제 경로·기능 근거 | 경4에 옮길 수 있는 부분 / 별도 작업 |
|---|---|---|
| MQTT adapter | `MqttInterfaceAdapter/include/MqttInterfaceAdapter.h:19~24`, `src/MqttInterfaceAdapter.c:606/707/738/769` | connect/subscribe/unsubscribe/publish API, QoS·retain·payload 길이·callback/완료 추적 기반. 경4 Topic/Quadtree/V2N/LWT 계약은 별도 설계 |
| REST 역할 분리 | `RestApiTestScenario/src/RestApiTestScenarioProcProvideGetClient.c` 및 CollectGetServer/CollectPostClient/ProvidePostServer | 요청/제공의 에이전트 역할과 관측 구조 참고. 경4 endpoint·스키마·오류/시간 기준을 새로 매핑 |
| ASN.1 유틸 | `Prj22AsnMsgUtil/src/Prj22AsnMsgUtil.c`, `include/Prj22AsnMsgUtil.h` | 변환 구조 후보. 국 과제 메시지 이름과 경4의 KS/TIM 계약은 같지 않음; 자동 복제·이식 없음 |

재식별 SHA-256:

- MQTT header: `73220763d7ce44bea27281f96f914095ce2069ee25d58e8ffddaccfb1d3036b6`
- MQTT source: `7c4d9c4d8bbe4ca2c4f45af35cadf42928775eedd3c793a346ed64c1b12bbdc7`
- REST ProvideGetClient source: `c66b39902c40948ce2a431a547626a2dffed2e87f9498481bdc1a6992f47f84d`

이식에는 libmosquitto·curl·공통 dimz/메시지 계약·라이선스·빌드 의존성 확인이 따른다. 이번 PR은 이 후보 코드를 복사하거나 변경하지 않는다.

## 7. 검증 및 A04 완료 조건

실행한 검증은 코드 검색·함수 본문/분기/생성 경로 읽기·소스 버전 차이·원문과 필드/프로토콜 대응의 정적 검토다. 빌드·테스트 대상 네트워크 실행·실장비 시험은 수행하지 않았다. 기존 `5d29dc2`의 빌드 기록은 작업공간 빌드 재현성 근거이며 이번 표준 충족의 증거가 아니다.

모든 A03 요구 묶음과 필드 사전에 코드 근거 또는 등록 경로 미식별 근거·재사용/수정/신규/확인 필요 분류를 연결했다. 미확정 프로토콜·외부 판정·참조 ASN.1 판은 남은 의존성으로 명시했다. 구현 작업의 코드 수정은 착수하지 않았다.

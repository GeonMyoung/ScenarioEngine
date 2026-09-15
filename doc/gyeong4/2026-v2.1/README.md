# 경4 ITSK-00143-3 — 2026 Ver 2.1 분석 제출

**A01~A05 분석 문서와 자체 검토 자료를 중앙 검토에 제출한다.** 구현 코드는 변경하지 않았다. 제공 HWP의 명시 요구사항과 기존 구현 차이를 정리했으며, 참조 원문 미확보와 미결정 해석을 합격 기준으로 확정하지 않았다.

## 빠른 검토

1. [자체 검토·완료 조건 대조](review-evidence.md)
2. [A05 질의 22건](A05-open-decisions.md) — 특히 Q04 MQTT/AP-DATEX, Q05 V2N, Q06 OID, Q19 Binary
3. [A04 코드 대응·변경 영향](A04-implementation-gap.md)
4. [A03 요구사항](A03-requirements.md)과 [메시지/OID 사전](A03-message-catalog.md), [필드 사전](A03-field-dictionary.md)

## 업무별 산출물·자체 판단

| Riido 작업 | 산출물 | 자체 검토 판단 / 남은 사항 |
|---|---|---|
| [GM-62 / A01](https://app.riido.io/uVml0Nr-7iY91YVOhm8wQ/teams/GM/tasks/zWuOKI8a5EqGJyhlGstmz) | [기준·구조·참조 표준](A01-baseline-and-structure.md) | 위치·판/해시·자료 확보 구분 제출. 공식 채택일/참조판은 결정 대기 |
| [GM-63 / A02](https://app.riido.io/uVml0Nr-7iY91YVOhm8wQ/teams/GM/tasks/PYPHDJfiquUlYabk2gL9L) | [인터페이스·역할·범위](A02-interface-scope.md) | 목록 35행·추가 항목 8개 분류. 실제 개발/시험 범위는 중앙 확정 필요 |
| [GM-64 / A03](https://app.riido.io/uVml0Nr-7iY91YVOhm8wQ/teams/GM/tasks/eX4ANiHuZocLX61HhcxtU) | [요구사항](A03-requirements.md), [메시지](A03-message-catalog.md), [필드](A03-field-dictionary.md) | 제공 HWP의 명시값 추출 제출. **준용 표준 전체 필드의 확정은 미완료**, 해당 판 원전 필요 |
| [GM-65 / A04](https://app.riido.io/uVml0Nr-7iY91YVOhm8wQ/teams/GM/tasks/K9qObh9ex6PqshOPkYUEk) | [구현 차이](A04-implementation-gap.md) | 실제 코드 분기·재사용/수정/신규/미정 매핑 제출. 외부 웹 판정·실장비 검증 미실행 |
| [GM-66 / A05](https://app.riido.io/uVml0Nr-7iY91YVOhm8wQ/teams/GM/tasks/CnVhiImxho4LuZiL5Jmqa) | [질의·미결정](A05-open-decisions.md) | 22건의 근거·영향·질의·보류 방침 제출. 답변/공식 결정 미수신 |

중앙 검토자의 독립 판단과 Riido 완료 처리는 이 자체 판단과 별개다.

## 핵심 결과

- 차량–센터 MQTT/V2N 설명과 같은 방향의 AP-DATEX 목록·상세표가 병존한다.
- F2C RSA/MAP/TLSM OID 매핑, 인프라 경로 인코딩 및 여러 전송 주기에 상충이 있다.
- 제4장 명시적 필드표 19개에서 381개 필드·구조·생략 표시를, 부록 TIM에서 62개 프로파일 행을 추적했다. V2N 11개 필드는 별도 기록했다.
- 기본 ASN.1 변환·AP-DATEX 시험 기반은 있으나 새 MQTT/V2N/API/DB/Binary 경4 계약과 TIM 서비스 판정의 확정/보완이 필요하다.
- KS R 1600 계열·SAE 채택판·ITSK-00150-2 등의 원전 확보가 필요하다. 현재 파일의 날짜를 공식 개정 확정일로 보지 않는다.

## 재현 기준과 제출 위치

- HWP SHA-256: `93d78241b4c6a49727f8bab5133ad6df5e8d4becaedae6f115706cc4cd6a6964`, 718336 bytes.
- 코드 분석: `3ea0d8c0744472566db083cf153f9f656df82b3e`; `5d29dc2` 이후 코드 변화 없음.
- 제출 기준 main: `b8aefaf2c7229980f9aaf9a4d4cd2ab84a8f7101`(중앙/작업 역할 지침만 추가).
- 제출 브랜치: `docs/GM-62-gyeong4-analysis-review`.
- worktree: `C:\Implement\ScenarioEngine-worktrees\GM-62-gyeong4-analysis`.
- 원문과 임시 추출·렌더는 `C:\Implement\ScenarioEngine\.local\gyeong4-workplan`에만 유지하며 PR에 넣지 않는다.

## Riido 반영 이력과 역할 변경

사용자의 역할 변경 지시 **이전**에 작업 창이 GM-62(A01)를 ‘진행 중’(`inProgress`)으로 한 번 변경했다. 재조회에서 해당 상태와 `isDone=false`를 확인했다. 작업 창이 만든 결과 댓글·완료 처리·중복 작업은 없다. 역할 변경 이후 쓰기는 중단했다.

이후 상태·결과 댓글·완료 판단은 중앙 검토 창 담당이다. 착수 시 조회한 팀 상태는 ‘완료’도 `inProgress`, ‘완료 (1)’도 `notStarted`여서 올바른 완료 분류가 없었다. 중앙 반영 때 최신 상태 목록을 다시 확인해야 한다.

# ScenarioEngine 개발 정책

개발과 검증은 [공통 규칙](interface-test-common-rules.md)과 [경4 범위](gyeong4/2026-v2.1/development-scope.md)를 따른다.

- 기존 시험 진입점과 설정을 유지한다. DATEX 개선판은 독립 case와 전용 UI_CONFIGURE를 사용한다.
- MQTT/V2N에서 J2735 2024-09-23 전달본을 적용한 GitsnAsn1 코덱을 사용한다. BSM vert는 필수다.
- JSON에서 부호 있는 64비트 필드는 부호를 유지한다.
- 실장비 로그와 이전 회차 증적은 별도 보관한다. 공개 예제는 합성 원문을 사용한다.

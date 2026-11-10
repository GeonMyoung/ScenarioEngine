"""Current maximum-gap policy with the earlier symmetric-period policy retained."""
import math

MODES=('maximum_gap','periodic')

def assess(deltas,expected,tolerance,mode='maximum_gap'):
    if mode not in MODES:raise ValueError('지원하지 않는 수신 간격 판정 방식입니다.')
    upper=expected+tolerance
    def outside(delta):
        if not math.isfinite(delta) or delta<0:return True
        if mode=='periodic':
            # Retained original +/- tolerance check; not used by the current default.
            return abs(delta-expected)>tolerance
        return delta>upper and not math.isclose(delta,upper,rel_tol=0,abs_tol=1e-9)
    outliers=[dict(interval=i+1,seconds=d) for i,d in enumerate(deltas) if outside(d)]
    return dict(mode=mode,expected_seconds=expected,tolerance_seconds=tolerance,
        lower_seconds=expected-tolerance if mode=='periodic' else None,upper_seconds=upper,
        criterion=f'{expected-tolerance:.3f}~{upper:.3f}초' if mode=='periodic' else f'수신 간격 ≤ {upper:.3f}초 (1초 + 추가 여유 {tolerance:g}초)',
        observed_seconds=deltas,minimum_seconds=min(deltas) if deltas else None,
        maximum_seconds=max(deltas) if deltas else None,outliers=outliers,
        basis='수신 시각 기준 / 최대 갱신 간격과 추가 여유는 프로젝트 판정 설정' if mode=='maximum_gap' else '수신 시각 기준 / ±허용오차는 프로젝트 판정 설정')

"""Bounded evidence collection/review worker launched by the native engine."""
import argparse
import hashlib
import json
from pathlib import Path
import sys
import time
import xml.etree.ElementTree as ET

# This trusted package directory is required when invoked with Python -I.
sys.path.insert(0, str(Path(__file__).resolve().parent))
from evidence_values import EvidenceError, read_json, read_events
from review_method_evidence import review

PROFILE = 'REST-REVIEW-LINK-001'


def result(report, digest, review_status, reason, reviewed=None):
    automatic = report['automaticVerdict']
    automatic_scope = report.get('assessmentProfile') == 'REST-AUTO-001'
    if automatic_scope and review_status == 'PENDING':
        review_status = 'NOT_CONFIRMED'
    final = 'SUCCESS' if review_status == 'PASS' else 'FAIL' if review_status == 'FAIL' else automatic if automatic_scope else 'EVIDENCE_PENDING'
    if automatic not in ('SUCCESS', 'EVIDENCE_PENDING'):
        final = automatic
    criteria = {c['test']: c for c in (reviewed or {}).get('standardCriteria', [])}
    items = []
    for item in report['items']:
        items.append(dict(test=item['test'], automaticVerdict=item['verdict'], reviewStatus=review_status,
                          finalVerdict='SUCCESS' if review_status == 'PASS' else item['verdict'] if automatic_scope or item['verdict'] not in ('SUCCESS', 'EVIDENCE_PENDING') else 'EVIDENCE_PENDING',
                          completedExchanges=item['completedExchanges'], basis=item.get('basis', ''),
                          unobserved=item.get('unobserved', ''),
                          evidence=criteria.get(item['test'], {}).get('evidence', ['선택 항목의 송수신·대상 처리 기록 대조'] if review_status == 'PASS' else [])))
    return dict(schemaVersion=1, integrationProfile=PROFILE, assessmentScope=report.get('assessmentScope'), runId=report['runId'], case=report['case'],
                automaticResultSha256=digest, automaticVerdict=automatic, reviewStatus=review_status,
                finalVerdict=final, reason=reason, items=items, review=reviewed)


def collect(report_path, peer_directory, timeout, snapshot):
    original = report_path.read_bytes(); report = read_json(report_path)
    digest = hashlib.sha256(original).hexdigest()
    if report['automaticVerdict'] not in ('SUCCESS', 'EVIDENCE_PENDING'):
        return result(report, digest, 'SKIPPED', '송수신 시험이 완료되지 않아 원래 판정을 유지합니다.')
    provider = report['sutRole'] == 'provider'
    total = report['completedExchanges']
    files = ['events.jsonl'] + [f'response-{n}.body' for n in range(1, total + 1)]
    files += ['preparation.json', 'source-data.body'] if provider else ['requester-config.json', 'processed.json']
    deadline = time.monotonic() + timeout
    last_reason = '대상 시스템의 증적 파일이 아직 준비되지 않았습니다.'
    previous_hashes = None
    while time.monotonic() < deadline:
        try:
            events = read_events(peer_directory / 'events.jsonl')
            received = [e for e in events if e['event'] == ('response_sent' if provider else 'response_received')]
            if received and any(e.get('runId') != report['runId'] for e in received):
                return result(report, digest, 'PENDING', '다른 시험 실행의 증적입니다. 현재 실행의 대상 증적 폴더를 확인하세요.')
            # Wait for actual response evidence and completed client processing.
            ready = len(received) >= total and (provider or any(e['event'] == 'finished' for e in events))
            if ready:
                captured = {name: (peer_directory / name).read_bytes() for name in files}
                hashes = {name: hashlib.sha256(data).hexdigest() for name, data in captured.items()}
                if hashes == previous_hashes:
                    snapshot.mkdir(exist_ok=False)
                    for name, data in captured.items():
                        (snapshot / name).write_bytes(data)
                    try:
                        reviewed = review(report_path, snapshot)
                        linked = result(report, digest, 'PASS', '같은 실행의 송수신·준비자료·대상 처리 증적을 대조했습니다.', reviewed)
                    except EvidenceError as error:
                        linked = result(report, digest, 'FAIL', str(error) or '대상 증적과 시험 기록이 일치하지 않습니다.')
                    except (OSError, ValueError, KeyError, TypeError, ET.ParseError):
                        linked = result(report, digest, 'PENDING', '증적 파일의 형식이나 필수 기록이 부족해 검토를 완료하지 못했습니다.')
                    if report_path.read_bytes() != original:
                        return result(report, digest, 'PENDING', '검토 중 시험기 원본 결과가 변경되어 결과를 연결하지 않았습니다.')
                    linked['snapshotFilesSha256'] = hashes
                    return linked
                previous_hashes = hashes
                last_reason = '대상 증적의 기록 완료를 확인하고 있습니다.'
            else:
                previous_hashes = None
                last_reason = '대상의 응답·처리 기록이 아직 모두 준비되지 않았습니다.'
        except (OSError, ValueError, KeyError, TypeError, EvidenceError):
            previous_hashes = None
            last_reason = '대상 증적 파일을 읽을 수 없거나 필수 기록이 아직 준비되지 않았습니다.'
        time.sleep(.15)
    return result(report, digest, 'PENDING', '증적 준비 대기시간이 지났습니다. ' + last_reason)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--report', type=Path, required=True)
    parser.add_argument('--sut', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--wait-seconds', type=int, required=True)
    args = parser.parse_args()
    if args.output.exists() or not 1 <= args.wait_seconds <= 600:
        parser.error('Output must be new; wait seconds must be 1..600')
    value = collect(args.report, args.sut, args.wait_seconds, args.output.parent / 'sut-evidence-snapshot')
    # Create a new result; never replace native result.json or an older review.
    with args.output.open('x', encoding='utf8') as stream:
        json.dump(value, stream, ensure_ascii=False, indent=2)
    return 0


if __name__ == '__main__':
    raise SystemExit(main())

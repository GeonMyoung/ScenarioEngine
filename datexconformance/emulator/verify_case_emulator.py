"""Verify a selected DATEX case against an independent emulator process."""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess
from verify_bsm_emulator import available_port, await_listening, events

CASES = {
    'centerClient2signalserver_v2': ('signalserver', 'signal', True, ['spat', 'tls']),
    'vehicleServer2rse_v2': ('rse', 'bsm', False, ['bsm']),
    'vehicleClient2rse_v2': ('rse', 'traffic', True, ['spat', 'map', 'rsa', 'tim', 'tim_speed', 'tim_lane', 'tim_regional']),
    'rseClient2vehicle_v2': ('vehicle', 'bsm', True, ['bsm']),
    'rseServer2vehicle_v2': ('vehicle', 'traffic', False, ['spat', 'map', 'rsa', 'tim', 'tim_speed', 'tim_lane', 'tim_regional']),
    'vehicleServer2center_v2': ('center', 'bsm', False, ['bsm']),
    'centerClient2vehicle_v2': ('vehicle', 'bsm', True, ['bsm']),
    'vehicleClient2center_v2': ('center', 'traffic', True, ['spat', 'rsa', 'tim', 'tim_speed', 'tim_lane']),
    'centerServer2vehicle_v2': ('vehicle', 'traffic', False, ['spat', 'rsa', 'tim', 'tim_speed', 'tim_lane']),
    'signalserverServer2center_v2': ('center', 'signal', False, ['spat', 'tls']),
}
SELECTORS = {'bsm': (82050, 20), 'spat': (82055, 19), 'rsa': (82053, 27),
             'tim': (82054, 31), 'tim_speed': (82054, 31), 'tim_lane': (82054, 31), 'tim_regional': (82054, 31), 'map': (82056, 18), 'tls': (0, 50)}


def available(case):
    _, _, provider, messages = CASES[case]
    return ['session'] + ['normal_' + m for m in messages] + (
        ['invalid_login', 'duplicate_login', 'abnormal_session', 'invalid_subscription', 'publication_retry', 'cancel']
        if provider else ['login_retry', 'subscription_retry', 'unknownSubscription', 'unknownPublicationNbr',
                          'unknownPublicationMsgId', 'invalidPublicationMsgId', 'invalidPublicationMsgContent', 'repeatedPublicationNbr'])


def run(exe, output, case, test):
    role, profile, provider, _ = CASES[case]
    out = output / (case + '-' + test)
    out.mkdir(parents=True, exist_ok=False)
    port = available_port()
    base = {'user': 'datex-local', 'pass': 'local-datex-check', 'hb_dur': 6, 'rsp_timeout': 1,
            'connect_timeout_s': 10, 'fred_maintain_s': 2, 'receive_s': 4, 'period_s': 1}
    tester = dict(base, my_domain='TESTER', peer_domain='EMULATOR', **{'test_' + test: True})
    emulator = dict(base, my_domain='EMULATOR', peer_domain='TESTER', test_session=True)
    for config, server in [(tester, not provider), (emulator, provider)]:
        config['local_port' if server else 'peer_port'] = port
        if not server:
            config['peer_ip'] = '127.0.0.1'
    for name, config in [('tester', tester), ('emulator', emulator)]:
        (out / f'{name}.json').write_text(json.dumps(config), encoding='utf-8')
    processes, streams = {}, []
    result = {'case': case, 'test': test, 'status': 'FAIL', 'scope': 'local functional timing'}
    try:
        for mode in (['emulator', 'tester'] if provider else ['tester', 'emulator']):
            stream = (out / (mode + '.console.txt')).open('wb')
            streams.append(stream)
            command = [str(exe), '--case', case, '--profile', profile, '--role', role,
                       '--mode', mode, '--config', str(out/(mode+'.json')),
                       '--log', str(out/(mode+'.jsonl')), '--duration', '70']
            if test.startswith('normal_'):
                command += ['--message', test[7:]]
            if mode == 'emulator':
                command += ['--request', 'session' if test in ['session', 'login_retry'] else 'single']
            processes[mode] = subprocess.Popen(command, cwd=out, stdin=subprocess.DEVNULL,
                stdout=stream, stderr=subprocess.STDOUT, creationflags=subprocess.CREATE_NO_WINDOW)
            if len(processes) == 1:
                await_listening(processes[mode], out/(mode+'.jsonl'))
        assert processes['tester'].wait(timeout=85) == 0
        assert processes['emulator'].wait(timeout=10) == 0
        records = [e for e in events(out/'tester.jsonl') if e.get('event') == 'result']
        expected = 'SUCCESS'
        assert len(records) == 1 and records[0]['test'] == test and records[0]['verdict'] == expected, records
        sut = events(out/'emulator.jsonl')
        assert sut[0]['case'] == case
        if test.startswith('normal_'):
            payloads = events(out/('tester.jsonl' if provider else 'emulator.jsonl'))
            wanted_event = ('bsm' if profile == 'bsm' else 'payload') + ('_decoded' if provider else '_processed')
            decoded = next(e for e in payloads if e.get('event') == wanted_event and e['message'] == test[7:])
            assert (decoded['psid'], decoded['messageId']) == SELECTORS[test[7:]]
            assert json.loads(decoded['decodedJson'])
            if not provider:
                assert any(e.get('event') == 'application_processed' for e in sut)
        if test == 'abnormal_session':
            assert any(e.get('reason') == 'heartbeat_timeout' for e in sut)
        result.update(status='PASS', expected=expected, detail=records[0]['detail'])
    except Exception as error:
        result['error'] = repr(error)
    finally:
        for process in processes.values():
            if process.poll() is None:
                process.kill()
            process.wait()
        for stream in streams:
            stream.close()
    (out/'result.json').write_text(json.dumps(result, ensure_ascii=False, indent=2), encoding='utf-8')
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--exe', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--case', choices=CASES, action='append')
    parser.add_argument('--test', action='append')
    args = parser.parse_args()
    exe, output = args.exe.resolve(), args.output.resolve()
    output.mkdir(parents=True, exist_ok=True)
    results = []
    for case in args.case or CASES:
        for test in args.test or available(case):
            if test not in available(case):
                continue
            print('RUN', case, test, flush=True)
            result = run(exe, output, case, test)
            results.append(result)
            print(result['status'], case, test, result.get('error', ''), flush=True)
            summary = {'sha256': hashlib.sha256(exe.read_bytes()).hexdigest(), 'results': results,
                       'total': len(results), 'passed': sum(r['status'] == 'PASS' for r in results)}
            (output/'summary.json').write_text(json.dumps(summary, ensure_ascii=False, indent=2), encoding='utf-8')
    return 0 if results and all(r['status'] == 'PASS' for r in results) else 1


if __name__ == '__main__':
    raise SystemExit(main())

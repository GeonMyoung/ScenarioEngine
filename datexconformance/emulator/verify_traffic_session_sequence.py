"""Check ten immediate RSE reconnects against a single running traffic tester."""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess
from verify_traffic_emulator import available_port, await_listening, events


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--exe', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    exe, out = args.exe.resolve(), args.output.resolve()
    out.mkdir(parents=True, exist_ok=False)
    tests = ['normal_map', 'normal_rsa', 'normal_tim', 'subscription_retry',
             'unknownSubscription', 'unknownPublicationNbr', 'unknownPublicationMsgId',
             'invalidPublicationMsgId', 'invalidPublicationMsgContent', 'repeatedPublicationNbr']
    port = available_port()
    base = {'user': 'traffic-local', 'pass': 'local-traffic-check', 'hb_dur': 6,
            'rsp_timeout': 1, 'connect_timeout_s': 10}
    configs = {
        'tester': dict(base, my_domain='TESTER', peer_domain='EMULATOR', local_port=port,
                       **{'test_' + t: True for t in tests}),
        'emulator': dict(base, my_domain='EMULATOR', peer_domain='TESTER', peer_ip='127.0.0.1',
                         peer_port=port, test_normal_map=True),
    }
    processes, files = [], []
    result = {'status': 'FAIL', 'sha256': hashlib.sha256(exe.read_bytes()).hexdigest(),
              'scope': 'local independent-process reconnect regression; short timing'}
    try:
        for mode, config in configs.items():
            (out / f'{mode}.json').write_text(json.dumps(config), encoding='utf-8')
            stream = (out / f'{mode}.console.txt').open('wb')
            files.append(stream)
            command = [str(exe), '--profile', 'traffic', '--mode', mode, '--role', 'rse',
                       '--config', str(out / f'{mode}.json'), '--log', str(out / f'{mode}.jsonl'),
                       '--sessions', str(len(tests)), '--duration', '120']
            process = subprocess.Popen(command, cwd=out, stdin=subprocess.DEVNULL,
                                       stdout=stream, stderr=subprocess.STDOUT,
                                       creationflags=subprocess.CREATE_NO_WINDOW)
            processes.append(process)
            if mode == 'tester':
                await_listening(process, out / 'tester.jsonl')
        result['testerExit'] = processes[0].wait(timeout=120)
        result['emulatorExit'] = processes[1].wait(timeout=10)
        records = [e for e in events(out / 'tester.jsonl') if e.get('event') == 'result']
        result['tests'] = records
        assert result['testerExit'] == result['emulatorExit'] == 0
        assert [e['test'] for e in records] == tests
        for record in records:
            expected = 'SUCCESS'
            assert record['verdict'] == expected, record
        assert sum(e.get('event') == 'session_end' for e in events(out / 'emulator.jsonl')) == len(tests)
        result['status'] = 'PASS'
    except Exception as error:
        result['error'] = repr(error)
    finally:
        for process in processes:
            if process.poll() is None:
                process.kill()
            process.wait()
        for stream in files:
            stream.close()
    (out / 'result.json').write_text(json.dumps(result, ensure_ascii=False, indent=2), encoding='utf-8')
    print(json.dumps(result, ensure_ascii=False))
    return 0 if result['status'] == 'PASS' else 1


if __name__ == '__main__':
    raise SystemExit(main())

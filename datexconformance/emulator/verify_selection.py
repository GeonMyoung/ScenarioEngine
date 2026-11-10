"""Verify single/subset/all selection against independently running DATEX peers."""
import argparse
import concurrent.futures
import json
from pathlib import Path
import subprocess
from verify_bsm_emulator import available_port, await_listening, events


def run_case(exe, output, scenario, mode, keys, fault='none'):
    target = output / f"{scenario['id']}-{mode}"
    target.mkdir(parents=True, exist_ok=False)
    port = available_port()
    base = dict(user='selection-user', **{'pass': 'selection-secret'}, hb_dur=6,
                rsp_timeout=1, fred_maintain_s=2, receive_s=4, period_s=1, connect_timeout_s=12)
    tester = dict(base, my_domain='TESTER', peer_domain='SUT')
    # Input order deliberately differs from UI order; only true entries execute.
    for test in reversed(scenario['tests']):
        tester['test_' + test['key']] = test['key'] in keys
    sut = dict(base, my_domain='SUT', peer_domain='TESTER', test_session=True)
    for config, server in [(tester, not scenario['provider']), (sut, scenario['provider'])]:
        config['local_port' if server else 'peer_port'] = port
        if not server:
            config['peer_ip'] = '127.0.0.1'
    plan = {'case': scenario['case'], 'tests': ['test_' + key for key in reversed(keys)]}
    for name, data in [('tester', tester), ('emulator', sut), ('plan', plan)]:
        (target / (name + '.json')).write_text(json.dumps(data), encoding='utf-8')
    processes, streams = {}, []
    result = dict(id=scenario['id'], case=scenario['case'], mode=mode, expectedTests=keys, status='FAIL')
    try:
        for role in (['emulator', 'tester'] if scenario['provider'] else ['tester', 'emulator']):
            stream = (target / (role + '.console.log')).open('wb')
            streams.append(stream)
            command = [str(exe), '--case', scenario['case'], '--role', scenario['sutRole'],
                       '--profile', scenario['profile'], '--mode', role,
                       '--config', str(target / (role + '.json')), '--log', str(target / (role + '.jsonl')),
                       '--duration', '60']
            if role == 'emulator':
                command += ['--plan', str(target / 'plan.json'), '--fault', fault]
            processes[role] = subprocess.Popen(command, cwd=target, stdin=subprocess.DEVNULL,
                                               stdout=stream, stderr=subprocess.STDOUT,
                                               creationflags=subprocess.CREATE_NO_WINDOW)
            if len(processes) == 1:
                await_listening(processes[role], target / (role + '.jsonl'))
        tester_code = processes['tester'].wait(timeout=180)
        sut_code = processes['emulator'].wait(timeout=20)
        actual = [e for e in events(target / 'tester.jsonl') if e['event'] == 'result']
        starts = [e for e in events(target / 'emulator.jsonl') if e['event'] == 'session_start']
        assert [e['test'] for e in actual] == keys, actual
        assert [e['plannedTest'] for e in starts] == ['test_' + k for k in keys], starts
        for item in actual:
            expected = 'SUCCESS'
            if fault == 'bad-content' and item['test'] == 'normal_bsm':
                expected = 'FAIL'
            assert item['verdict'] == expected, item
        if fault == 'none':
            assert tester_code == sut_code == 0, (tester_code, sut_code)
        else:
            assert tester_code == 1 and actual[-1]['verdict'] == 'SUCCESS', actual
        result.update(status='PASS', itemCount=len(actual), results=actual, counterpartSessions=starts)
    except Exception as error:
        result['error'] = repr(error)
    finally:
        for process in processes.values():
            if process.poll() is None:
                process.kill()
            process.wait()
        for stream in streams:
            stream.close()
    (target / 'result.json').write_text(json.dumps(result, ensure_ascii=False, indent=2), encoding='utf-8')
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--exe', required=True, type=Path)
    parser.add_argument('--catalog', required=True, type=Path)
    parser.add_argument('--output', required=True, type=Path)
    parser.add_argument('--id', type=int, action='append')
    args = parser.parse_args()
    scenarios = json.loads(args.catalog.read_text(encoding='utf-8'))['scenarios']
    jobs = []
    for scenario in scenarios:
        if args.id and scenario['id'] not in args.id:
            continue
        keys = [t['key'] for t in scenario['tests']]
        jobs.append((scenario, 'all', keys, 'none'))
        # The maximum mixed-OID cases exercise session/no-data and every TIM profile.
        if scenario['id'] in [53, 55]:
            wanted = {'session', 'normal_map', 'normal_tim_speed', 'normal_tim_regional',
                      'invalid_subscription' if scenario['provider'] else 'subscription_retry'}
            jobs.append((scenario, 'subset', [k for k in keys if k in wanted], 'none'))
            jobs.append((scenario, 'single', ['normal_tim_lane'], 'none'))
        if scenario['id'] == 54:
            jobs.append((scenario, 'failure-continues', ['normal_bsm', 'invalid_login'], 'bad-content'))
    output = args.output.resolve()
    output.mkdir(parents=True, exist_ok=True)
    results = []
    with concurrent.futures.ThreadPoolExecutor(max_workers=2) as pool:
        futures = [pool.submit(run_case, args.exe.resolve(), output, *job) for job in jobs]
        for future in concurrent.futures.as_completed(futures):
            result = future.result()
            results.append(result)
            print(result['status'], result['id'], result['mode'], result.get('error', ''), flush=True)
            summary = dict(results=sorted(results, key=lambda r: (r['id'], r['mode'])),
                           runs=len(results), passed=sum(r['status'] == 'PASS' for r in results),
                           selectedItems=sum(r.get('itemCount', 0) for r in results), timing='local reduced timing')
            (output / 'summary.json').write_text(json.dumps(summary, ensure_ascii=False, indent=2), encoding='utf-8')
    return 0 if results and all(r['status'] == 'PASS' for r in results) else 1


if __name__ == '__main__':
    raise SystemExit(main())

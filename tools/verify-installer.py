"""Verify an administratively extracted MSI without installing the product.

The host needs websockets for a loopback controller. Product subprocesses use
only the extracted executable, Python and dependencies with a restricted PATH.
MQTT business exchanges are verified separately with tests/engine_bridge.py.
"""
import argparse
import asyncio
import base64
import hashlib
import json
import os
from pathlib import Path
import subprocess
import websockets

ROOT = Path(__file__).resolve().parents[1]
CATEGORIES = {
    'datexconformance': 'ITSK-00143-DATEX-V2',
    'restconformance': 'ITSK-00143-REST-V1',
    'binaryconformance': 'ITSK-00143-TCP-V1',
    'kafkaconformance': 'ITSK-00143-KAFKA-V1',
    'mqttv2nconformance': 'ITSK-00143-MQTT-V1',
}


async def verify(args):
    extracted, release, work = (p.resolve() for p in (args.extracted, args.release, args.output))
    work.mkdir(parents=True, exist_ok=False)
    manifest = json.loads((release/'build-manifest.json').read_text(encoding='utf-8'))
    result = dict(payloadFiles=len(manifest['payloadSha256']), hashMismatches=[],
                  runtimeChecks=[], initializations=[], actualProductInstalled=False,
                  externalPlatformUsed=False, enginePathIsolated=True)
    for relative, expected in manifest['payloadSha256'].items():
        path = extracted/relative
        if not path.is_file() or hashlib.sha256(path.read_bytes()).hexdigest() != expected:
            result['hashMismatches'].append(relative)
    assert not result['hashMismatches'], result['hashMismatches']
    assert not list(extracted.rglob('mosquitto.exe'))
    assert not (extracted/'mqttv2nconformance/emulator').exists()
    config = json.loads((extracted/'mqttv2n-runtime.json').read_text(encoding='utf-8'))
    assert config == dict(python='python/python.exe', module='mqttv2nconformance')
    windows = Path(os.environ['SystemRoot'])
    env = dict(os.environ, PATH=str(windows/'System32')+os.pathsep+str(windows))
    env.pop('PYTHONPATH', None); env.pop('PYTHONHOME', None)

    def run(command, name):
        p = subprocess.run(command, cwd=extracted, env=env, capture_output=True,
                           timeout=60, creationflags=subprocess.CREATE_NO_WINDOW)
        (work/(name+'.stdout')).write_bytes(p.stdout)
        (work/(name+'.stderr')).write_bytes(p.stderr)
        result['runtimeChecks'].append(dict(check=name, exitCode=p.returncode))
        assert p.returncode == 0, (name, p.stderr.decode('utf-8', errors='replace'))

    python = str(extracted/'python/python.exe')
    run([python, '-I', '-B', '-X', 'utf8', '-c',
         'import sys,ssl,sqlite3,xml.etree.ElementTree,confluent_kafka; '
         'from pathlib import Path; assert Path(sys.prefix).resolve()==Path(sys.argv[1]).resolve(); '
         'assert sys.version_info[:3]==(3,12,10); assert confluent_kafka.version()[0]=="2.8.0"; '
         'print(sys.executable,sys.version,confluent_kafka.version())', str(extracted/'python')], 'python-kafka')
    run([python, '-I', '-B', '-X', 'utf8', '-c',
         'import sys; sys.path.insert(0,sys.argv[1]); from mqtt_transport import library; '
         'from codec import Codec; from catalog import CASES; '
         'assert len(CASES)==4; library(); c=Codec(sys.argv[2]); '
         'print([c.validate(i,c.sample(i))["frameId"] for i in (20,19,50,31)])',
         str(extracted/'mqttv2nconformance/runtime'), str(extracted/'mqttv2nconformance/bin/MqttPayload.exe')], 'mqtt-client-codec')
    run([python, '-I', '-B', '-X', 'utf8', str(extracted/'rest-review/engine_review_worker.py'), '--help'], 'rest-review')
    for example in sorted((extracted/'kafkaconformance/registration').glob('*.example.json')):
        case = example.name.removesuffix('.example.json')
        run([python, '-E', '-s', '-B', '-X', 'utf8', str(extracted/'kafkaconformance/runtime/configuration.py'),
             '--case', case, '--config', str(example), '--receipt', str(work/(case+'.receipt.json'))], 'config-'+case)

    async def initialize(category, case, directory):
        directory.mkdir()
        messages, ready = [], asyncio.Event()
        async def handle(ws):
            try:
                async for raw in ws:
                    message = json.loads(raw); messages.append(message)
                    if message.get('method') == 'DESCRIBE':
                        await ws.send(json.dumps(dict(seq=message['seq'], result=dict(code=200, reason='OK', data=None))))
                        scenario = base64.b64encode(json.dumps(dict(category=category, testScenario=case)).encode()).decode()
                        await ws.send(json.dumps(dict(method='INITIALIZE', seq=2, testScenario=scenario)))
                    elif message.get('method') in ('UI_CONFIGURE', 'NOTIFY'):
                        await ws.send(json.dumps(dict(seq=message['seq'], result=dict(code=200, reason='OK', data=None))))
                        if message['method'] == 'UI_CONFIGURE': ready.set()
            except websockets.ConnectionClosed:
                pass
        async with websockets.serve(handle, '127.0.0.1', 0, max_size=33554432,
                                    compression=None, ping_interval=None) as server:
            with (directory/'engine.log').open('wb') as log:
                process = subprocess.Popen([str(extracted/'ScenarioEngineTest.exe'),
                                            f'ws://127.0.0.1:{server.sockets[0].getsockname()[1]}/agent'],
                                           cwd=directory, env=env, stdout=log, stderr=subprocess.STDOUT,
                                           creationflags=subprocess.CREATE_NO_WINDOW)
                try:
                    await asyncio.wait_for(ready.wait(), 20)
                    ui = next(m for m in messages if m.get('method') == 'UI_CONFIGURE')
                    definition = json.loads(base64.b64decode(ui['conf']))
                    assert definition['scenarios'], (category, case)
                    result['initializations'].append(dict(category=category, case=case, uiReceived=True,
                                                          selectableItems=len(definition['scenarios'])))
                    print('UI OK', case, flush=True)
                finally:
                    if process.poll() is None:
                        process.terminate(); await asyncio.to_thread(process.wait, 10)
                    (directory/'events.json').write_text(json.dumps(messages, ensure_ascii=False, indent=2), encoding='utf-8')

    for module, category in CATEGORIES.items():
        # Older native modules embed their catalog; their source manifest is
        # covered by build-manifest source hashes. New runtime modules ship it.
        path = extracted/module/'registration/manifest.json'
        if not path.is_file(): path = ROOT/module/'registration/manifest.json'
        records = json.loads(path.read_text(encoding='utf-8-sig'))
        for row in records['cases'] if isinstance(records, dict) else records:
            await initialize(category, row['case'], work/row['case'])
    assert len(result['initializations']) == sum(manifest['newInterfaceScenarios'].values())
    result.update(passed=True, scope='MSI extracted payload integrity, packaged runtime/codec loading and catalog initialization; no product installation')
    (work/'verification.json').write_text(json.dumps(result, ensure_ascii=False, indent=2), encoding='utf-8')
    print(json.dumps(dict(passed=True, files=result['payloadFiles'], cases=len(result['initializations']))), flush=True)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--extracted', type=Path, required=True)
    parser.add_argument('--release', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    asyncio.run(verify(parser.parse_args()))

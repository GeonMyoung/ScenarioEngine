"""Create a local development runtime from explicit existing dependencies."""
import argparse,hashlib,json,shutil,sys
from pathlib import Path

def main():
    p=argparse.ArgumentParser();p.add_argument('--output',required=True);p.add_argument('--broker-runtime',required=True)
    p.add_argument('--python',default=sys.executable);p.add_argument('--configuration',default='Debug64')
    a=p.parse_args();module=Path(__file__).resolve().parents[1];root=module.parent;out=Path(a.output).resolve()
    if out==root or out==module:raise ValueError('개발 출력은 별도 폴더를 사용하세요.')
    target=out/'mqttv2nconformance';target.mkdir(parents=True,exist_ok=True)
    for name in ['runtime','registration','emulator']:
        shutil.copytree(module/name,target/name,dirs_exist_ok=True,ignore=shutil.ignore_patterns('__pycache__','broker'))
    (target/'bin').mkdir(exist_ok=True)
    codec=module/f'project/vs2022/{a.configuration}/MqttPayload.exe'
    if not codec.is_file():raise FileNotFoundError('MqttPayload.exe를 먼저 빌드하세요.')
    shutil.copy2(codec,target/'bin/MqttPayload.exe')
    for name in ['pthreadVC2.dll','libcrypto-1_1-x64.dll','libssl-1_1-x64.dll']:
        shutil.copy2(codec.parent/name,target/'bin'/name)
        shutil.copy2(codec.parent/name,out/name)
    broker=Path(a.broker_runtime);dest=target/'runtime/broker/mosquitto';dest.mkdir(parents=True,exist_ok=True)
    required=['mosquitto.dll','mosquitto.exe','pthreadVC3.dll','cjson.dll','uv.dll','websockets.dll','zlib1.dll','libssl-3-x64.dll','libcrypto-3-x64.dll','NOTICE.md','edl-v10','epl-v20']
    manifest=[]
    for name in required:
        src=broker/name
        if not src.is_file():raise FileNotFoundError(src)
        shutil.copy2(src,dest/name);manifest.append(dict(name=name,sha256=hashlib.sha256(src.read_bytes()).hexdigest()))
    engine_configuration=a.configuration.replace('64','Test64')
    engine=root/f'scenarioengine/project/vs2022/{engine_configuration}/ScenarioEngineTest.exe'
    if not engine.is_file():raise FileNotFoundError('ScenarioEngineTest.exe를 먼저 -Engine 옵션으로 빌드하세요.')
    shutil.copy2(engine,out/'ScenarioEngineTest.exe')
    config=dict(python=str(Path(a.python).resolve()),module='mqttv2nconformance')
    (out/'mqttv2n-runtime.json').write_text(json.dumps(config,indent=2),encoding='utf-8')
    (out/'runtime-manifest.json').write_text(json.dumps(dict(libraries=manifest,codecSha256=hashlib.sha256(codec.read_bytes()).hexdigest(),python=config['python']),indent=2),encoding='utf-8')
    print(out)
if __name__=='__main__':main()

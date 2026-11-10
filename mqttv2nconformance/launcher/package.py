"""Package a small launcher that reuses an existing, verified MSI installation."""
import argparse,hashlib,json,shutil,subprocess,sys
from pathlib import Path

ROOT=Path(__file__).resolve().parents[2]
SOURCE=Path(__file__).parent
VERSION='20261110.mqtt.easy.16'
sys.path.insert(0,str(ROOT/'mqttv2nconformance/runtime'))
from catalog import CASES,CENTER_PROVIDER_CASE,items,ui

def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()
def fields(node):
    if isinstance(node,dict):
        if node.get('type')=='Input':yield node['option']
        for value in node.values():yield from fields(value)
    elif isinstance(node,list):
        for value in node:yield from fields(value)

def make_catalog():
    rows=json.loads((ROOT/'mqttv2nconformance/registration/manifest.json').read_text(encoding='utf-8'))
    result=[]
    for row in rows:
        case=row['case'];definition=CASES[case];configuration=list(fields(ui(case)['configuration']))
        defaults={f['name']:f.get('value','') for f in configuration if f['type']!='checkbox'}
        defaults.update(port=str(44000+row['platformId']))
        if not definition['receive'] and not definition.get('publish_only'):defaults['observation_file']='자동 수신 관측'
        inputs=[dict(name=f['name'],label=f['label'],type=f['type']) for f in configuration if f['type']!='checkbox' and f['name'] not in ('security_file','observation_file')]
        tests=[]
        for key,message,mode,title in items(case):
            text=('입력한 토픽으로 실제 수신한 V2N 원문과 UPER 내용을 검사합니다.' if definition['receive'] else '입력한 토픽으로 자료를 발행하고 상대 에뮬레이터의 실제 수신 기록을 대조합니다.')
            if definition['receive'] and message!='tim':text+=' 환경설정의 수신 건수를 적용합니다.'
            if definition.get('center_provider'):
                if case==CENTER_PROVIDER_CASE:text+=' SPaT → TLSM → TIM 순서로 선택 메시지를 처리합니다.'
                if message=='tim':text+=' TIM은 furtherInfoID와 ITIS 조합으로 유형을 식별합니다. 중복과 누락을 항목별로 기록합니다. content 형식은 기록하고 합불 기준에서 제외합니다.'
            if definition['receive']:text+=' 구독 완료 후 목표 건수를 확인하거나 사용자가 중지할 때까지 대기합니다.'
            if definition.get('publish_only'):text='V2N version 0과 회차별 다른 BSM 시험값을 사용합니다. 전달받은 J2735_20240923_KSR1600 스키마의 필수 vert를 적용합니다. 설정 토픽으로 BSM을 1초 주기·QoS 0으로 설정 횟수만큼 발행한 뒤 종료합니다. 수신 로그를 기다리지 않습니다. 자동 성공은 발행 절차 완료를 뜻하며, 최종 합격은 센터 수신 로그와 송신 기록을 사후 대조해 결정합니다.'
            tests.append(dict(key=key[5:],label=title,description=text,expected='SUCCESS'))
            defaults[key]=len(tests)==1
        title=row['platformTitle']+' (종합점검)' if case==CENTER_PROVIDER_CASE else row['platformTitle']
        result.append(dict(id=row['platformId'],title=title,category=row['category'],case=case,url=row['platformUrl'],
                           testerSystem=definition['engine'],targetSystem=definition['sut'],testerRole='MQTT Subscriber' if definition['receive'] else 'MQTT Publisher',
                           targetRole='MQTT Publisher' if definition['receive'] else 'MQTT Subscriber',provider=definition['receive'],publishOnly=definition.get('publish_only',False),family='mqtt',
                           fields=inputs,tests=tests,tester=defaults,sut={},port=44000+row['platformId']))
    return dict(version=VERSION,scenarios=result)

def main():
    parser=argparse.ArgumentParser()
    parser.add_argument('--output',type=Path,required=True)
    parser.add_argument('--engine-root',type=Path,required=True)
    parser.add_argument('--msi-manifest',type=Path,required=True)
    parser.add_argument('--broker-runtime',type=Path,required=True)
    a=parser.parse_args();out=a.output.resolve();engine=a.engine_root.resolve()
    if out.exists():raise SystemExit('Choose a new output folder; existing bundles and run history are preserved.')
    msi=json.loads(a.msi_manifest.read_text(encoding='utf-8'))
    expected={name:value for name,value in msi['payloadSha256'].items() if name.startswith(('python/','mqttv2nconformance/')) or name in ('ScenarioEngineTest.exe','pthreadVC2.dll','libcrypto-1_1-x64.dll','libssl-1_1-x64.dll','mqttv2n-runtime.json')}
    for name,value in expected.items():
        if not (engine/name).is_file() or sha(engine/name)!=value:raise ValueError('Installed MSI file differs: '+name)
    out.mkdir(parents=True);runtime=out/'runtime';runtime.mkdir();broker=runtime/'broker/mosquitto';broker.mkdir(parents=True)
    for name in ('mosquitto.exe','mosquitto.dll','pthreadVC3.dll','cjson.dll','uv.dll','websockets.dll','zlib1.dll','libssl-3-x64.dll','libcrypto-3-x64.dll','NOTICE.md','edl-v10','epl-v20'):
        shutil.copy2(a.broker_runtime/name,broker/name)
    shutil.copy2(ROOT/'mqttv2nconformance/emulator/peer.py',runtime/'peer.py')
    shutil.copy2(ROOT/'mqttv2nconformance/emulator/tim-five-fixtures.json',runtime/'tim-five-fixtures.json')
    shutil.copy2(SOURCE/'peer_entry.py',runtime/'peer_entry.py')
    (out/'launcher-runtime.json').write_text(json.dumps(dict(engineDirectory=str(engine)),indent=2),encoding='utf-8')
    catalog=make_catalog()
    (out/'scenarios.json').write_text(json.dumps(catalog,ensure_ascii=False,indent=2),encoding='utf-8')
    shutil.copy2(ROOT/'kafkaconformance/launcher/extension-id.txt',out/'extension-id.txt')
    shutil.copytree(ROOT/'interfaceconformance/launcher/chrome-extension',out/'Chrome-연결-확장')
    (out/'간편실행안내.html').write_text((SOURCE/'guide.html').read_text(encoding='utf-8').replace('{{MSI_VERSION}}',msi['version']),encoding='utf-8')
    (out/'읽어주세요.txt').write_text(f'MQTT/V2N 간편시험\n\nScenarioEngine MSI {msi["version"]}이 설치된 PC에서 시작하기.exe를 실행합니다.\n{len(catalog['scenarios'])}개 시나리오 중 하나를 선택하고 사용할 메시지 토픽을 입력합니다.\n새 웹 자체시험의 Agent URL을 넣고 환경설정 적용 → 시험 시작 순서로 진행합니다.\nBSM(#81)은 Broker만 준비하고 발행 후 종료합니다. 최종 합격은 송신 기록과 센터 수신 로그를 사후 대조하여 결정합니다. 그 밖의 시나리오는 해당 역할의 상대와 관측을 준비합니다.\n기존 표준적합성시험 웹 연결 Chrome 확장을 그대로 사용합니다.\n이 묶음은 로컬 에뮬레이터 시험용이며, 실장비 시험은 별도 환경에서 수행합니다.\n엔진·Python 복사본은 포함하지 않습니다. 설치 위치가 다르면 launcher-runtime.json을 확인하세요.\n',encoding='utf-8-sig')
    subprocess.run(['powershell','-NoProfile','-File',str(SOURCE/'build.ps1'),'-OutputDirectory',str(out)],check=True)
    manifest=dict(version=VERSION,scenarioCount=len(catalog['scenarios']),itemCount=sum(len(s['tests']) for s in catalog['scenarios']),engineMsiVersion=msi['version'],
                  installedRuntimeSha256=expected,runtimeSha256={p.relative_to(runtime).as_posix():sha(p) for p in runtime.rglob('*') if p.is_file()},
                  launcherSha256=sha(out/'시작하기.exe'),launcherSourceSha256={p.name:sha(p) for p in SOURCE.glob('*.cs')},
                  commonSourceSha256={name:sha(ROOT/'interfaceconformance/launcher'/name) for name in ('WebFormLink.cs','PortReservation.cs','UserReport.cs')},
                  bridge='existing common Chrome extension; actual web settings/start; unchanged permissions',
                  engineLocation='existing MSI installation; no duplicate engine or Python in bundle')
    (out/'bundle-manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2),encoding='utf-8')
    print(json.dumps(dict(output=str(out),runtimeBytes=sum(p.stat().st_size for p in runtime.rglob('*') if p.is_file())),ensure_ascii=False))

if __name__=='__main__':main()

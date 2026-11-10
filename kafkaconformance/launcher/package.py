"""Build a new, movable Kafka manual-test bundle; never overwrite user runs."""
import argparse,hashlib,json,shutil,subprocess,sys,zipfile
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2];SOURCE=Path(__file__).resolve().parent
sys.path.insert(0,str(ROOT/'kafkaconformance/runtime'))
from catalog import CASES,STREAMS,items,ui
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def fields(node):
    if isinstance(node,dict):
        if node.get('type')=='Input' and not node['option']['name'].startswith('test_'):yield {k:node['option'].get(k,'') for k in ('name','label','type')}
        for v in node.values():yield from fields(v)
    elif isinstance(node,list):
        for v in node:yield from fields(v)
def catalog():
    records=json.loads((ROOT/'kafkaconformance/registration/manifest.json').read_text(encoding='utf8'));scenarios=[]
    for row in records:
        case=row['case'];design,provider,source,streams=CASES[case];default=json.loads((ROOT/'kafkaconformance/registration'/(case+'.example.json')).read_text(encoding='utf8'))
        default['bootstrap_servers']='127.0.0.1:'+str(44000+row['platformId']);default['group_id']='g4-easy-'+design.lower()
        if 'facility_fixture' in default:default['facility_fixture']='기본 제공 자료'
        tests=[]
        for key,stream,mode,title in items(case):
            description=('실제 발행 자료를 수신·검사하고 시험 Consumer의 commit 및 저장 offset을 확인합니다.' if provider else '준비한 자료를 발행하고 대상 Consumer Group의 저장 offset 진전을 확인합니다.')
            if mode=='normal':description+=' 기본 정상 자료 10회입니다.'
            else:description+=f' 합의 주기 표본 2개 이상을 관측합니다. 기본 주기는 {STREAMS[stream][2]}초입니다.'
            if stream=='facility':description+=' 시설 업무 필드 의미는 미확인이고 합의 JSON 전달 범위입니다.'
            if stream=='map':description+=' MAP JSON 예시 구조 범위이며 BER/UPER 전체 적합성은 제외합니다.'
            tests.append(dict(key=key[5:],label=title,description=description+' 내부 업무 처리 확인과 직접 결과 확인 표시는 별도입니다.',expected='SUCCESS'))
            default[key]=len(tests)==1
        configs=list(fields(ui(case)['configuration']))
        for f in configs:
            if f['name']=='bootstrap_servers':f['label']='시험용 브로커 주소 (127.0.0.1:포트)'
            if f['name']=='security_file':f['label']='인증 파일 (포함한 로컬 브로커는 미사용)'
        scenarios.append(dict(id=row['platformId'],title=row['title'],category='ITSK-00143-KAFKA-V1',case=case,url='https://106.250.189.37:8443/test/scenario/'+str(row['platformId']),testerSystem='통합교통관제시스템' if provider else source,targetSystem=source if provider else '통합교통관제시스템',testerRole='Kafka Consumer' if provider else 'Kafka Producer',targetRole='Kafka Producer' if provider else 'Kafka Consumer',provider=provider,family='kafka',fields=configs,tests=tests,tester=default,sut={},port=44000+row['platformId']))
    return dict(version='20260925.kafka.easy.3',scenarios=sorted(scenarios,key=lambda s:s['id']))
def main():
    p=argparse.ArgumentParser();p.add_argument('--output',type=Path,required=True);p.add_argument('--java-home',type=Path,required=True);p.add_argument('--kafka-home',type=Path,required=True);p.add_argument('--client-home',type=Path,required=True);p.add_argument('--zip',action='store_true');a=p.parse_args();out=a.output.resolve()
    if out.exists():raise SystemExit('새 출력 폴더를 지정하세요. 기존 묶음/실행 기록을 덮어쓰지 않습니다.')
    out.mkdir(parents=True);runtime=out/'runtime';runtime.mkdir();build=ROOT/'scenarioengine/project/vs2022/DebugTest64'
    for f in [build/'ScenarioEngineTest.exe',*build.glob('*.dll')]:shutil.copy2(f,runtime/f.name)
    module=runtime/'kafkaconformance';module.mkdir()
    for part in ['runtime','emulator','fixtures','registration']:shutil.copytree(ROOT/'kafkaconformance'/part,module/part,ignore=shutil.ignore_patterns('__pycache__'))
    shutil.copy2(SOURCE/'broker_admin.py',runtime/'broker_admin.py')
    py=runtime/'python';py.mkdir();base=Path(sys.base_prefix)
    for f in base.iterdir():
        if f.suffix in ['.exe','.dll'] or f.name=='LICENSE.txt':shutil.copy2(f,py/f.name)
    shutil.copytree(base/'DLLs',py/'DLLs',ignore=shutil.ignore_patterns('__pycache__'))
    shutil.copytree(base/'Lib',py/'Lib',ignore=shutil.ignore_patterns('site-packages','__pycache__','test','tests','idlelib','tkinter','turtledemo','ensurepip'))
    site=py/'Lib/site-packages';site.mkdir()
    for f in a.client_home.glob('confluent_kafka*'):
        if f.is_dir():shutil.copytree(f,site/f.name,ignore=shutil.ignore_patterns('__pycache__'))
    shutil.copytree(a.java_home,runtime/'java');(runtime/'kafka').mkdir()
    for part in ['libs','config','licenses']:shutil.copytree(a.kafka_home/part,runtime/'kafka'/part)
    for name in ['LICENSE','NOTICE']:shutil.copy2(a.kafka_home/name,runtime/'kafka'/name)
    (runtime/'kafka-runtime.json').write_text(json.dumps(dict(python='python/python.exe',module='kafkaconformance')),encoding='utf8')
    (out/'scenarios.json').write_text(json.dumps(catalog(),ensure_ascii=False,indent=2),encoding='utf8')
    shutil.copytree(ROOT/'interfaceconformance/launcher/chrome-extension',out/'Chrome-연결-확장');shutil.copy2(SOURCE/'extension-id.txt',out/'extension-id.txt')
    for name,dest in [('guide.html','간편실행안내.html'),('EXTENSION-PERMISSIONS.md','확장-권한-안내.md')]:
        if (SOURCE/name).exists():shutil.copy2(SOURCE/name,out/dest)
    shutil.copy2(ROOT/'interfaceconformance/launcher/WEB-BRIDGE.md',out/'공통확장-사용안내.md')
    subprocess.run(['powershell','-NoProfile','-File',str(SOURCE/'build.ps1'),'-OutputDirectory',str(out)],check=True)
    manifest=dict(version='20260925.kafka.easy.3',scope='4 Kafka scenarios / 20 items; independent local SUT and owned local Apache broker',extensionId=(out/'extension-id.txt').read_text().strip(),runtimeSha256={str(f.relative_to(runtime)).replace('\\','/'):sha(f) for f in runtime.rglob('*') if f.is_file()},launcherSourceSha256={f.name:sha(f) for f in SOURCE.glob('*.cs')},launcherSha256=sha(out/'시작하기.exe'),bridgeReuse='existing REST/TCP Chrome extension unchanged; one launcher connected at a time')
    (out/'읽어주세요.txt').write_text('Kafka 수동시험 간편 실행\n\nZIP 전체를 새 폴더에 푼 뒤 시작하기.exe를 실행합니다.\nPython·Java·Apache Kafka·독립 상대가 포함되어 있으며 별도 설치가 필요 없습니다.\n기존 REST/TCP용 Chrome 웹 시험 연결 확장을 그대로 사용합니다. 같은 시간에는 하나의 실행기만 연결하세요.\n시험 선택 → 새 웹 자체시험 주소 복사 → 설정 확인/웹 적용 → 시험 시작 → 메시지/판정/보고서 확인 순서입니다.\n토픽은 사전 합의한 값을 입력하며, 기본 예시를 실제 합의값에 맞게 수정하세요. 빈 값은 실행되지 않습니다.\n이 묶음은 같은 PC의 에뮬레이터 수동 검증용입니다. 외부 브로커·실장비는 일반 엔진으로 별도 구성합니다.\n상태 주기는 최대 600초입니다. 단축값을 입력하면 변경된 개발 시간 조건으로 기록됩니다.\n',encoding='utf-8-sig')
    import runpy
    manifest=runpy.run_path(str(ROOT/'interfaceconformance/launcher/package_metadata.py'))['finalize_manifest'](out,manifest,'kafka')
    (out/'bundle-manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2),encoding='utf8')
    if a.zip:
        with zipfile.ZipFile(out.with_suffix('.zip'),'w',zipfile.ZIP_DEFLATED) as z:
            for f in out.rglob('*'):
                if f.is_file():z.write(f,str(Path(out.name)/f.relative_to(out)))
    print(json.dumps(dict(output=str(out),files=len(manifest['runtimeSha256'])),ensure_ascii=False))
if __name__=='__main__':main()

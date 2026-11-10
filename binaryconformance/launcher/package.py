"""TCP/Binary 수동시험 실행기와 검증된 엔진·독립 상대·Python 표준 실행환경을 묶는다."""
import argparse,hashlib,json,shutil,subprocess,sys,zipfile
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2];SOURCE=Path(__file__).resolve().parent
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def fields(node):
 if isinstance(node,dict):
  if node.get('type')=='Input' and node.get('option',{}).get('name') and not node['option']['name'].startswith('test_'):yield {k:node['option'].get(k,'') for k in ['name','label','type']}
  for value in node.values():yield from fields(value)
 elif isinstance(node,list):
  for value in node:yield from fields(value)
def describe(key,provider):
 if 'heartbeat' in key:return 'TOD 자료 없음 Heartbeat의 주기와 수신 응답을 확인합니다. 기본 60초 주기로 최소 2회 관측하므로 약 2분 이상 걸립니다.'
 if key.endswith('_periodic'):return '차량운행정보의 제공 간격을 확인합니다. 기본 주기는 1초, 측정 허용오차는 200ms이며 반복 10회에서 간격 9개를 관측합니다.'
 if 'bad_lrc' in key:return 'LRC가 잘못된 정보를 보내고 대상이 NACK로 거부하는지 확인합니다. 의도한 오류 거부가 성공 조건입니다.'
 if 'bad_payload' in key:return '데이터 길이가 잘못된 정보를 보내고 대상이 NACK로 거부하는지 확인합니다.'
 if 'bad_sequence' in key:return '분할 순서번호 오류의 NACK을 확인하고 올바른 끝 프레임으로 조립을 마쳐 같은 세션에서 다음 회차를 진행합니다.'
 if '_split' in key:return '시작·끝으로 나눈 정보를 교환하고 각 프레임의 수신 응답 및 조립 결과를 확인합니다.'
 if '_multiple' in key:return '서로 다른 식별자의 복수 정보를 교환하고 필드와 수신 응답을 확인합니다.'
 if key.endswith('_empty'):return '자료가 없는 접속 조건에서 데이터 없는 Heartbeat와 설정한 수신 응답을 확인합니다. TOD 주기 시험과 구분합니다.'
 if '_change' in key or '_alter_status' in key:return '변경 전 정보를 교환한 뒤 변경 정보를 제공하여 값의 변화와 수신 응답을 확인합니다.'
 return '접속 후 정상 정보를 교환하고 표준 데이터 형식과 ACK를 확인합니다. 엔진이 관측한 송수신 범위로 판정합니다.'
def catalog(cli):
 manifest=json.loads((ROOT/'binaryconformance/registration/manifest.json').read_text(encoding='utf8'));rows=[]
 for case in manifest['cases']:
  key=case['case'];provider='TCP Server' in case['sutRole'];family='bsm' if '_bsm_' in key else 'route' if 'route' in key else 'incident' if '_incident_' in key else 'signal'
  ui=json.loads(subprocess.check_output([str(cli),'--operation','ui','--case',key]));example=json.loads((ROOT/f'binaryconformance/registration/{key}.example.json').read_text(encoding='utf8'))
  configs=list(fields(ui['configuration']));assert len({f['name'] for f in configs})==len(configs)
  default={f['name']:example.get(f['name'],False if f['type']=='checkbox' else '') for f in configs}
  tests=[dict(key=t['key'][5:],label=t['title'],description='항목마다 한 번 접속하고 같은 세션에서 교환한 뒤 연결을 정리합니다. '+describe(t['key'],provider)+('' if 'heartbeat' in t['key'] else ' 정보교환 횟수는 시험 환경설정의 입력값을 사용합니다(기본 10회).')+' 전체 송수신은 실행기의 송수신 상세와 웹 시험 데이터에서 확인하며 직접 확인 표시는 자동 판정과 별도입니다.',expected='SUCCESS') for t in ui['scenarios']]
  for t in tests:default['test_'+t['key']]=False
  default['test_'+tests[0]['key']]=True
  tester=case['testSystemRole'].replace('UT 센터','통합교통관제시스템').split(' / ');target=case['sutRole'].replace('UT 센터','통합교통관제시스템').split(' / ')
  rows.append(dict(id=case['platformId'],title=case['title'],category='ITSK-00143-TCP-V1',case=key,url=case['platformUrl'],testerSystem=tester[0],testerRole=tester[-1],targetSystem=target[0],targetRole=target[-1],provider=provider,family=family,tests=tests,fields=configs,tester=default,sut={},port=43000+case['platformId']))
 assert len(rows)==8 and sum(len(s['tests']) for s in rows)==52
 return dict(version='20260925.binary.easy.5',scenarios=sorted(rows,key=lambda s:s['id']))
def main():
 p=argparse.ArgumentParser();p.add_argument('--output',type=Path,required=True);p.add_argument('--python-home',type=Path,default=Path(sys.base_prefix));p.add_argument('--refresh',action='store_true');p.add_argument('--zip',action='store_true');a=p.parse_args();out=a.output.resolve()
 if (out/'runs').exists():raise SystemExit('사용자 실행 기록이 있는 묶음은 갱신하지 않습니다. 새 출력 폴더를 선택하세요.')
 if out.exists() and not a.refresh:raise SystemExit('새 출력 폴더를 지정하세요.')
 out.mkdir(parents=True,exist_ok=True);runtime=out/'runtime';runtime.mkdir(exist_ok=True)
 build=ROOT/'scenarioengine/project/vs2022/DebugTest64';cli=ROOT/'binaryconformance/project/vs2022/Debug64/BinaryConformanceCli.exe'
 for file in [build/'ScenarioEngineTest.exe',*build.glob('*.dll'),cli]:shutil.copy2(file,runtime/file.name)
 for folder in ['emulator','tools']:
  dest=runtime/folder;dest.mkdir(exist_ok=True)
  for file in (ROOT/'binaryconformance'/folder).glob('*.py'):shutil.copy2(file,dest/file.name)
 py=runtime/'python';py.mkdir(exist_ok=True)
 for file in a.python_home.iterdir():
  if file.suffix in ['.exe','.dll'] or file.name=='LICENSE.txt':shutil.copy2(file,py/file.name)
 shutil.copytree(a.python_home/'DLLs',py/'DLLs',dirs_exist_ok=True,ignore=shutil.ignore_patterns('__pycache__'))
 shutil.copytree(a.python_home/'Lib',py/'Lib',dirs_exist_ok=True,ignore=shutil.ignore_patterns('site-packages','__pycache__','test','tests','idlelib','tkinter','turtledemo','ensurepip'))
 (out/'scenarios.json').write_text(json.dumps(catalog(cli),ensure_ascii=False,indent=2),encoding='utf8')
 shutil.copytree(ROOT/'interfaceconformance/launcher/chrome-extension',out/'Chrome-연결-확장',dirs_exist_ok=True);shutil.copy2(SOURCE/'extension-id.txt',out/'extension-id.txt')
 for src,dest in [('guide.html','간편실행안내.html'),('EXTENSION-PERMISSIONS.md','확장-권한-안내.md')]:
  if (SOURCE/src).exists():shutil.copy2(SOURCE/src,out/dest)
 shutil.copy2(ROOT/'interfaceconformance/launcher/WEB-BRIDGE.md',out/'공통확장-사용안내.md')
 subprocess.run(['powershell','-NoProfile','-File',str(SOURCE/'build.ps1'),'-OutputDirectory',str(out)],check=True)
 manifest=dict(version='20260925.binary.easy.5',scope='8 TCP/Binary scenarios / 52 items',extensionId=(out/'extension-id.txt').read_text().strip(),runtimeSha256={str(f.relative_to(runtime)).replace('\\','/'):sha(f) for f in runtime.rglob('*') if f.is_file()},launcherSourceSha256={f.name:sha(f) for f in SOURCE.glob('*.cs')},engineSourceSha256={f.name:sha(f) for f in [ROOT/'binaryconformance/src/BinaryConformance.cpp',ROOT/'binaryconformance/src/SignalMethod.cpp',ROOT/'binaryconformance/tests/SignalCli.cpp']})
 manifest['launcherSha256']=sha(out/'시작하기.exe')
 manifest['bridgeReuse']='existing common web extension; channel-isolated concurrent launchers'
 (out/'읽어주세요.txt').write_text('TCP/Binary 수동시험 · 간편 실행\n\n시작하기.exe를 실행합니다. Python과 상대 프로그램은 묶음에 포함됩니다.\n기존 표준적합성시험 웹 연결 확장을 그대로 사용합니다. 기존 설치는 Chrome 확장 관리에서 새로고침해 갱신하세요.\n여러 시험에는 각각 실행기 창과 새 웹 시험 회차를 사용하세요. 기존 DATEX 전용 확장은 끄고 공통 확장을 사용하세요.\n환경설정 → 웹 적용 → 웹 시작 → 결과 확인 순서입니다. 자세한 안내는 간편실행안내.html에서 확인하세요.\n',encoding='utf-8-sig')
 import runpy
 manifest=runpy.run_path(str(ROOT/'interfaceconformance/launcher/package_metadata.py'))['finalize_manifest'](out,manifest,'binary')
 manifest['engineChanges']='Single TCP connection per selected item; configured repeated exchanges; continuous sequence; explicit cleanup and public session evidence'
 manifest['sessionPolicy']='BINARY-SESSION-001'
 manifest['exchangeInitiation']='Provider push for defined messages 67..72; existing ACK/NACK retained; no fabricated information-request frame'
 (out/'bundle-manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2),encoding='utf8')
 if a.zip:
  with zipfile.ZipFile(out.with_suffix('.zip'),'w',zipfile.ZIP_DEFLATED) as z:
   for f in out.rglob('*'):
    if f.is_file():z.write(f,str(Path(out.name)/f.relative_to(out)))
 print(json.dumps(dict(output=str(out),files=len(manifest['runtimeSha256'])),ensure_ascii=False))
if __name__=='__main__':main()

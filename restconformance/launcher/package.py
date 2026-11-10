"""REST 수동시험 실행기와 검증된 엔진·독립 상대·Python 표준 실행환경을 묶는다."""
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
 if key=='test_no_data_error' or key=='test_no_data_error_response':return '같은 유효 API에 자료가 없는 조건을 준비하고 오류 응답을 확인합니다. 빈 정상응답과 구분합니다.'
 if key in ['test_no_data','test_empty_response']:return '자료가 없는 정상 응답을 추가로 확인합니다. 표준의 자료 부재 오류응답을 대신하지 않습니다.'
 if key=='test_invalid_request':return '명세 또는 사전 협의로 정한 오류 입력을 보내고 기대응답을 확인합니다. 입력의 근거와 응답 코드의 근거를 구분합니다.'
 if key=='test_missing_credential':return '인증정보를 제외한 요청의 오류 응답을 확인합니다.'
 if key=='test_wrong_credential':return '올바르지 않은 인증정보를 넣은 요청의 오류 응답을 확인합니다.'
 if key=='test_missing_path':return '존재하지 않는 URL 경로의 오류 응답을 확인합니다.'
 if key=='test_malformed_response':return '손상된 본문을 시험 조건대로 전송하고 교환 기록을 남깁니다. 대상 내부 파싱 결과의 직접 관측과 구분합니다.'
 if key.startswith('test_response'):return '유효 요청에 오류 응답을 제공하는 조건을 확인합니다. 본문 규칙이 명시된 경우 함께 적용합니다.'
 return '유효한 요청과 정상 정보의 교환을 확인합니다. 데이터 정의는 표준, API 호출 규칙은 명세를 적용합니다.'
def catalog(cli):
 manifest=json.loads((ROOT/'restconformance/registration/manifest.json').read_text(encoding='utf8'));rows=[]
 for case in manifest['cases']:
  key=case['case'];provider='HTTP Server' in case['sutRole'];family='weather' if 'weather' in key else 'shadow' if '_shadow_' in key else 'ntic' if 'ntic' in key else 'utic' if 'utic' in key else 'smart' if '_smart_' in key else 'vds'
  ui=json.loads(subprocess.check_output([str(cli),'--ui-case',key]));default=json.loads((ROOT/f'restconformance/registration/{key}.example.json').read_text(encoding='utf8'))
  configs=list(fields(ui['configuration']));assert len({f['name'] for f in configs})==len(configs)
  for f in configs:
   f['label']=f['label'].replace('UT 센터','통합교통관제시스템')
   if f['name'] not in default:default[f['name']]=False if f['type']=='checkbox' else ''
  tests=[dict(key=t['key'][5:],label=t['title'].replace('UT 센터','통합교통관제시스템'),description=t.get('description',describe(t['key'],provider))+' 협의하여 선택한 항목만 환경설정 횟수만큼 실행합니다. 대상 내부 처리의 직접 관측과 구분합니다.',expected='SUCCESS') for t in ui['scenarios']]
  tester=case['testSystemRole'].replace('UT 센터','통합교통관제시스템').split(' / ');target=case['sutRole'].replace('UT 센터','통합교통관제시스템').split(' / ')
  rows.append(dict(id=case['platformId'],title=case['title'],category='ITSK-00143-REST-V1',case=key,url=case['platformUrl'],testerSystem=tester[0],testerRole=tester[-1],targetSystem=target[0],targetRole=target[-1],provider=provider,family=family,tests=tests,fields=configs,tester=default,sut={},port=43000+case['platformId']))
 assert len(rows)==12 and sum(len(s['tests']) for s in rows)==82
 return dict(version='20260926.rest.easy.4',scenarios=sorted(rows,key=lambda s:s['id']))
def main():
 p=argparse.ArgumentParser();p.add_argument('--output',type=Path,required=True);p.add_argument('--python-home',type=Path,default=Path(sys.base_prefix));p.add_argument('--refresh',action='store_true');p.add_argument('--zip',action='store_true');a=p.parse_args();out=a.output.resolve()
 if (out/'runs').exists():raise SystemExit('사용자 실행 기록이 있는 묶음은 갱신하지 않습니다. 새 출력 폴더를 선택하세요.')
 if out.exists() and not a.refresh:raise SystemExit('새 출력 폴더를 지정하세요.')
 out.mkdir(parents=True,exist_ok=True);runtime=out/'runtime';runtime.mkdir(exist_ok=True)
 build=ROOT/'scenarioengine/project/vs2022/DebugTest64';cli=ROOT/'restconformance/project/vs2022/Debug64/UticConformanceCli.exe'
 for file in [build/'ScenarioEngineTest.exe',*build.glob('*.dll'),cli]:shutil.copy2(file,runtime/file.name)
 for folder in ['emulator','tools']:
  dest=runtime/folder;dest.mkdir(exist_ok=True)
  for file in (ROOT/'restconformance'/folder).glob('*.py'):shutil.copy2(file,dest/file.name)
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
 subprocess.run(['powershell','-NoProfile','-File',str(ROOT/'restconformance/tools/Prepare-ReviewRuntime.ps1'),'-Executable',str(runtime/'ScenarioEngineTest.exe'),'-PythonExecutable',str(py/'python.exe')],check=True)
 # Keep the optional review runtime portable after extracting the bundle elsewhere.
 (runtime/'rest-review-runtime.json').write_text(json.dumps(dict(schemaVersion=1,pythonExecutable='python/python.exe',worker='rest-review/engine_review_worker.py')),encoding='utf8')
 manifest=dict(version='20260926.rest.easy.4',scope='12 REST scenarios / 82 items',extensionId=(out/'extension-id.txt').read_text().strip(),runtimeSha256={str(f.relative_to(runtime)).replace('\\','/'):sha(f) for f in runtime.rglob('*') if f.is_file()},launcherSourceSha256={f.name:sha(f) for f in SOURCE.glob('*.cs')},engineSourceSha256={f.name:sha(f) for f in [ROOT/'restconformance/src/RestConformance.cpp',ROOT/'restconformance/src/RestMethod.cpp']})
 (out/'읽어주세요.txt').write_text('REST API 수동시험 · 간편 실행\n\n시작하기.exe를 실행합니다. Python은 묶음에 포함되어 있습니다.\n기존 REST 확장을 공통 확장으로 갱신하고 이전 DATEX 확장은 꺼 주세요.\n자세한 순서와 권한은 간편실행안내.html, 확장-권한-안내.md에서 확인하세요.\n',encoding='utf-8-sig')
 import runpy
 manifest=runpy.run_path(str(ROOT/'interfaceconformance/launcher/package_metadata.py'))['finalize_manifest'](out,manifest,'rest')
 manifest['engineChanges']='Keep all 82 selectable cases; explicit input/response authority and authentication; honest requester test titles and observable result descriptions'
 manifest['caseInformationPolicy']='REST-SELECT-001 / REST-CASE-INFO-001'
 (out/'bundle-manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2),encoding='utf8')
 if a.zip:
  with zipfile.ZipFile(out.with_suffix('.zip'),'w',zipfile.ZIP_DEFLATED) as z:
   for f in out.rglob('*'):
    if f.is_file():z.write(f,str(Path(out.name)/f.relative_to(out)))
 print(json.dumps(dict(output=str(out),files=len(manifest['runtimeSha256'])),ensure_ascii=False))
if __name__=='__main__':main()

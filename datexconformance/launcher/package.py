"""Assemble the DATEX launcher with traceable runtime hashes and session-mode defaults."""
import argparse, hashlib, json, shutil, subprocess, zipfile
from pathlib import Path

def sha(path): return hashlib.sha256(path.read_bytes()).hexdigest()
def main():
    p=argparse.ArgumentParser();p.add_argument('--baseline',required=True,type=Path);p.add_argument('--output',required=True,type=Path);p.add_argument('--runtime',type=Path);args=p.parse_args()
    source=Path(__file__).resolve().parent; baseline=args.baseline.resolve(); out=args.output.resolve()
    out.mkdir(parents=True,exist_ok=True)
    if (out/'runs').exists(): raise SystemExit('Do not repackage a bundle that contains user runs; choose a new output directory.')
    manifest=json.loads((baseline/'bundle-manifest.json').read_text(encoding='utf-8-sig'))
    (out/'runtime').mkdir(exist_ok=True)
    for name,want in manifest['runtimeSha256'].items():
        file=(args.runtime or baseline/'runtime')/name
        if not args.runtime: assert sha(file)==want, name
        (out/'runtime'/name).parent.mkdir(parents=True,exist_ok=True)
        shutil.copy2(file,out/'runtime'/name)
    catalog=json.loads((baseline/'scenarios.json').read_text(encoding='utf-8-sig'))
    for scenario in catalog['scenarios']:
        scenario['tester']['use_initiate']=False
        scenario['sut']['use_initiate']=False
        for config in [scenario['tester'],scenario['sut']]:
            config['peer_ip']='127.0.0.1'
            config['peer_port']=config['local_port']=43000+scenario['id']
    catalog['version']='20260927.easy.7'
    catalog['date']='2026-09-27'
    catalog['defaultFolder']=str(out)
    (out/'scenarios.json').write_text(json.dumps(catalog,ensure_ascii=False,indent=2),encoding='utf-8')
    shutil.copy2(source/'guide.html',out/'간편실행안내.html')
    shutil.copytree(source.parents[1]/'interfaceconformance/launcher/chrome-extension',out/'Chrome-연결-확장',dirs_exist_ok=True)
    shutil.copy2(source/'extension-id.txt',out/'extension-id.txt')
    shutil.copy2(source/'EXTENSION-PERMISSIONS.md',out/'확장-권한-안내.md')
    shutil.copy2(source.parents[1]/'interfaceconformance/launcher/WEB-BRIDGE.md',out/'공통확장-사용안내.md')
    subprocess.run(['powershell','-NoProfile','-File',str(source/'build.ps1'),'-OutputDirectory',str(out)],check=True)
    (out/'읽어주세요.txt').write_text('DATEX 간편 실행 v7\n\n최초 1회: 간편실행안내.html의 안내대로 Chrome 연결 확장을 추가합니다.\n\n1. 기존 실행기 창을 닫고 시작하기.exe를 실행합니다.\n2. 환경설정과 상세시험을 확인합니다. 개시요청 사용을 선택하면 Initiate 이후 Login으로 시작하며, 해제하면 일반 Login으로 시작합니다. 개시요청 사용 시 ISO Server가 TCP 접속하고 ISO Client가 수신 대기합니다. 해제하면 ISO Client가 접속합니다. 선택한 방향의 IP와 포트만 사용합니다.\n3. Chrome에서 새 자체 시험 회차를 열고 Agent 주소를 복사합니다.\n4. 실행기에서 웹 환경설정 적용을 누릅니다.\n5. Chrome에서 값과 선택 항목, 설정 요약을 확인합니다.\n6. 웹의 시험 시작 버튼 또는 실행기의 웹에서 시험 시작 버튼을 누릅니다.\n\n설정·시작은 웹의 실제 버튼으로 처리됩니다.\n확장 권한은 확장-권한-안내.md에 설명되어 있습니다.\n',encoding='utf-8-sig')
    result={'version':'20260927.easy.7','engineBaseline':manifest['version'],'engineChanges':'optional Initiate, Login negotiation checks, bounded failure cleanup and observation-result wording','extensionId':(source/'extension-id.txt').read_text().strip(),'scope':'14 scenarios / 152 detailed items','runtimeSha256':{f.name:sha(f) for f in (out/'runtime').iterdir() if f.is_file()},'launcherSourceSha256':{f.name:sha(f) for f in source.glob('*.cs')},'engineSourceSha256':{f.name:sha(f) for f in list((source.parent/'src').glob('*.*'))+list((source.parent/'emulator').glob('*.cpp'))},'filesSha256':{str(f.relative_to(out)):sha(f) for f in out.rglob('*') if f.is_file() and f.name!='bundle-manifest.json'}}
    import runpy
    result=runpy.run_path(str(source.parents[1]/'interfaceconformance/launcher/package_metadata.py'))['finalize_manifest'](out,result,'datex')
    result['engineChanges']='Client TCP connect for ordinary Login; Server TCP connect for Initiate; counterpart, launcher, duplicate sessions and UI aligned'
    result['emulatorSourceSha256']={f.name:sha(f) for f in (source.parent/'emulator').glob('*.cpp')}
    (out/'bundle-manifest.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf-8')
    archive=out.with_suffix('.zip')
    with zipfile.ZipFile(archive,'w',zipfile.ZIP_DEFLATED) as z:
        for f in out.rglob('*'):
            if f.is_file(): z.write(f,str(Path(out.name)/f.relative_to(out)))
    print(json.dumps({'directory':str(out),'zip':str(archive),'zipSha256':sha(archive)},ensure_ascii=False))
if __name__=='__main__':main()

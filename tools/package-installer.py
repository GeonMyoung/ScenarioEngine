"""Stage a self-contained ScenarioEngine MSI using the existing Installer Project UI.

This does not install the product or change the original .vdproj. Build the engine
with Release/x64 and UseDebugLibraries=false before invoking this script.
"""
import argparse
import hashlib
import json
import re
import shutil
import subprocess
import uuid
from datetime import datetime, timezone
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
APP_FOLDER = '_F89B195CD75847018C9F10F00E94407C'
UPGRADE_CODE = '{A490AAFB-0951-4654-B4EA-241C2DEA54B4}'
SPECIAL_IDS = {
    'edit_runbat.cmd': '_10006CA05C334C71863D0A5D1B4FB19D',
    'run_runbat.cmd': '_C6DDD7454BA94AA5A7A85F349F9B5E2E',
    'ScenarioEngineTest.ico': '_53EBF9D54FCF408C86F3086C0D34D8CA',
    'Product.bmp': '_C8FC68FF1D0D4715AEA928D7F700549A',
}


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def ident(kind, value):
    return '_' + hashlib.sha256((kind + ':' + value).encode()).hexdigest()[:32].upper()


def copy_tree(source, target, exclude=()):
    shutil.copytree(source, target, ignore=shutil.ignore_patterns('__pycache__', '*.pyc', '*.pyo', *exclude))


def block_bounds(text, name, indent):
    marker = ' ' * indent + '"' + name + '"\n'
    start = text.index(marker)
    opening = text.index('{', start)
    depth = 0
    offset = opening
    for line in text[opening:].splitlines(keepends=True):
        value = line.strip()
        if value == '{':
            depth += 1
        elif value == '}':
            depth -= 1
            if depth == 0:
                return start, opening, offset + len(line)
        offset += len(line)
    raise ValueError('Unclosed project block: ' + name)


def replace_block(text, name, indent, body):
    start, opening, end = block_bounds(text, name, indent)
    return text[:start] + ' ' * indent + '"' + name + '"\n' + ' ' * indent + '{\n' + body + ' ' * indent + '}\n' + text[end:]


def folder_node(relative, children, indent=20):
    pad = ' ' * indent
    folder_id = ident('folder', relative)
    lines = [f'{pad}"{{9EF0B969-E518-4E46-987F-47570745A589}}:{folder_id}"', pad + '{']
    for key, value in [('Name', '8:' + Path(relative).name), ('AlwaysCreate', '11:FALSE'),
                       ('Condition', '8:'), ('Transitive', '11:FALSE'), ('Property', '8:' + folder_id)]:
        lines.append(f'{pad}"{key}" = "{value}"')
    lines += [pad + '    "Folders"', pad + '    {']
    for child in sorted(children.get(relative, [])):
        lines.append(folder_node(child, children, indent + 8).rstrip())
    lines += [pad + '    }', pad + '}']
    return '\n'.join(lines) + '\n'


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--stage', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--python-runtime', type=Path, required=True)
    parser.add_argument('--mqtt-runtime', type=Path, required=True,
                        help='Existing Mosquitto client DLL and license directory; no broker service is installed.')
    parser.add_argument('--version', default='1.2.2')
    args = parser.parse_args()
    if not re.fullmatch(r'\d{1,3}\.\d{1,3}\.\d{1,5}', args.version):
        raise SystemExit('Use an MSI three-part version.')
    if any(int(part) > bound for part, bound in zip(args.version.split('.'), (255, 255, 65535))):
        raise SystemExit('MSI version is out of range.')
    stage, output = args.stage.resolve(), args.output.resolve()
    if stage.exists() or output.exists():
        raise SystemExit('Use new staging and output directories; existing releases are preserved.')
    source_commit = subprocess.check_output(['git', 'rev-parse', 'HEAD'], cwd=ROOT, text=True).strip()
    source_status = subprocess.check_output(['git', 'status', '--porcelain', '--untracked-files=normal'], cwd=ROOT)
    stage.mkdir(parents=True)
    output.mkdir(parents=True)
    payload = stage / 'payload'
    payload.mkdir()
    binary = ROOT / 'scenarioengine/project/vs2022/ReleaseTest64'
    for name in ('ScenarioEngineTest.exe', 'pthreadVC2.dll', 'libcrypto-1_1-x64.dll', 'libssl-1_1-x64.dll'):
        shutil.copy2(binary / name, payload / name)
    for name in ('ScenarioEngineTest.ico', 'Product.bmp'):
        shutil.copy2(ROOT / 'scenarioengine' / name, payload / name)
    for name in ('edit_runbat.cmd', 'run_runbat.cmd'):
        shutil.copy2(ROOT / 'ScenarioEngineSetup' / name, payload / name)
    # Preserve the familiar Edit/Run workflow, and resolve the executable from the
    # script directory even when a shortcut starts with a different current path.
    (payload / 'run.bat').write_text(
        '@echo off\nsetlocal\ncd /d "%~dp0"\n'
        'REM Paste the Agent WebSocket URL from the platform between the quotes.\n'
        'set "SERVER_URL="\n'
        'if not defined SERVER_URL (\n'
        '  echo Open "Edit Scenario Engine", set SERVER_URL, save, and run again.\n'
        '  pause\n  exit /b 2\n)\n'
        '"%~dp0ScenarioEngineTest.exe" "%SERVER_URL%"\n', encoding='ascii', newline='\r\n')
    (payload / 'ScenarioEngineTest.log').write_bytes(b'')
    copy_tree(args.python_runtime.resolve(), payload / 'python')
    python = payload / 'python/python.exe'
    subprocess.run([str(python), '-I', '-B', '-c',
                    'import sys,confluent_kafka,ssl,sqlite3,xml.etree.ElementTree; '
                    'assert sys.version_info[:3]==(3,12,10); '
                    'assert confluent_kafka.version()[0]=="2.8.0"'], check=True)
    for part in ('runtime', 'fixtures', 'registration'):
        copy_tree(ROOT / 'kafkaconformance' / part, payload / 'kafkaconformance' / part)
    for example in (payload / 'kafkaconformance/registration').glob('*.example.json'):
        values = json.loads(example.read_text(encoding='utf-8-sig'))
        if 'facility_fixture' in values:
            values['facility_fixture'] = 'kafkaconformance/fixtures/map.json'
            example.write_text(json.dumps(values, ensure_ascii=False, indent=2), encoding='utf-8')
    (payload / 'kafka-runtime.json').write_text(json.dumps({
        'python': 'python/python.exe', 'module': 'kafkaconformance'}), encoding='utf-8')

    mqtt = payload / 'mqttv2nconformance'
    for part in ('runtime', 'registration'):
        copy_tree(ROOT / 'mqttv2nconformance' / part, mqtt / part, exclude=('broker',))
    (mqtt / 'bin').mkdir()
    codec_output = ROOT / 'mqttv2nconformance/project/vs2022/Release64'
    for name in ('MqttPayload.exe', 'pthreadVC2.dll', 'libcrypto-1_1-x64.dll', 'libssl-1_1-x64.dll'):
        shutil.copy2(codec_output / name, mqtt / 'bin' / name)
    mqtt_client = mqtt / 'runtime/broker/mosquitto'
    mqtt_client.mkdir(parents=True)
    for name in ('mosquitto.dll', 'pthreadVC3.dll', 'cjson.dll', 'uv.dll', 'websockets.dll',
                 'zlib1.dll', 'libssl-3-x64.dll', 'libcrypto-3-x64.dll', 'NOTICE.md', 'edl-v10', 'epl-v20'):
        shutil.copy2(args.mqtt_runtime.resolve() / name, mqtt_client / name)
    (payload / 'mqttv2n-runtime.json').write_text(json.dumps({
        'python': 'python/python.exe', 'module': 'mqttv2nconformance'}), encoding='utf-8')
    shutil.copy2(ROOT / 'mqttv2nconformance/README.md', mqtt / 'README.md')
    shutil.copy2(ROOT / 'mqttv2nconformance/reuse-manifest.json', mqtt / 'reuse-manifest.json')
    # Loading the packaged client and native codec catches missing DLLs before
    # building an MSI. All paths passed here point into the staged payload.
    subprocess.run([str(python), '-I', '-B', '-X', 'utf8', '-c',
                    'import sys; sys.path.insert(0,sys.argv[1]); '
                    'from mqtt_transport import library; from codec import Codec; '
                    'library(); c=Codec(sys.argv[2]); '
                    '[c.validate(i,c.sample(i)) for i in (20,19,50,31)]',
                    str(mqtt / 'runtime'), str(mqtt / 'bin/MqttPayload.exe')], check=True)
    review = payload / 'rest-review'
    review.mkdir()
    for name in ('engine_review_worker.py', 'review_method_evidence.py', 'evidence_method_contract.py', 'evidence_values.py'):
        shutil.copy2(ROOT / 'restconformance/tools' / name, review / name)
    (payload / 'rest-review-runtime.json').write_text(json.dumps({
        'schemaVersion': 1, 'pythonExecutable': 'python/python.exe',
        'worker': 'rest-review/engine_review_worker.py'}), encoding='utf-8')

    scenario_counts = {}
    for module in ('datexconformance', 'restconformance', 'binaryconformance', 'kafkaconformance', 'mqttv2nconformance'):
        manifest = json.loads((ROOT / module / 'registration/manifest.json').read_text(encoding='utf-8-sig'))
        scenario_counts[module] = len(manifest['cases'] if isinstance(manifest, dict) else manifest)
    info = {'product': 'ScenarioEngine', 'version': args.version, 'architecture': 'x64',
            'createdUtc': datetime.now(timezone.utc).isoformat(), 'configuration': 'Release',
            'useDebugLibraries': False, 'upgradeCode': UPGRADE_CODE,
            'sourceCommit': source_commit,
            'includesUncommittedSources': bool(source_status.strip()), 'newInterfaceScenarios': scenario_counts,
            'python': '3.12.10', 'confluentKafka': '2.8.0',
            'brokerIncluded': False, 'emulatorsIncluded': False, 'signed': False,
            'mqttClientIncluded': True, 'mqttCodecFrames': [20, 19, 50, 31],
            'mqttRuntimeRelativePaths': True,
            'normalizedExamplePaths': True}
    source_paths = [ROOT / 'scenarioengine/src/ScenarioEngineEnvUtil.c',
                    ROOT / 'scenarioengine/project/vs2022/ScenarioEngine.vcxproj',
                    ROOT / 'mqttv2nconformance/project/vs2022/MqttPayload.vcxproj',
                    ROOT / 'mqttv2nconformance/project/vs2022/MqttV2NConformance.vcxproj',
                    ROOT / 'tools/build-installer.ps1', ROOT / 'tools/package-installer.py']
    for module in scenario_counts:
        for part in ('src', 'include', 'runtime', 'registration'):
            folder = ROOT / module / part
            if folder.exists():
                source_paths.extend(p for p in folder.rglob('*') if p.is_file() and '__pycache__' not in p.parts
                                    and p.suffix in ('.c', '.cpp', '.h', '.py', '.json', '.tsb'))
    info['sourceSha256'] = {p.relative_to(ROOT).as_posix(): digest(p) for p in sorted(set(source_paths))}
    (payload / 'package-info.json').write_text(json.dumps(info, ensure_ascii=False, indent=2), encoding='utf-8')
    guide = f'''# ScenarioEngine {args.version} x64 설치 안내

1. 기존 설치본을 사용했다면 설치 폴더의 `run.bat`과 필요한 실행 기록을 별도 보관합니다. 기존 버전은 업그레이드 대상으로 식별하지만 run.bat 설정은 자동 이관하지 않습니다.
2. `ScenarioEngineSetup.msi`를 실행합니다. 기본 설치 폴더는 `C:\\Program Files\\ScenarioEngine`입니다.
3. 바탕화면 또는 시작 메뉴의 **Edit Scenario Engine**을 실행합니다.
4. `set "SERVER_URL="`의 따옴표 안에 플랫폼에서 발급한 해당 시험의 Agent WebSocket 접속 URL을 넣고 저장합니다.
5. **Run Scenario Engine**을 실행하고 기존과 같이 관리자 권한 요청을 확인합니다. 웹 플랫폼에서 환경설정·시험 시작을 수행합니다.

시험 대상 시스템을 준비하고 해당 시험의 접속 주소·포트·인증정보를 설정합니다. Kafka·MQTT 시험에서는 사용할 브로커와 정보별 토픽도 준비합니다. 브로커 서버와 상대 에뮬레이터는 설치하지 않습니다.

DATEX에서 개시요청을 해제하면 ISO Client가 접속하고, 선택하면 ISO Server가 접속 후 Initiate를 보냅니다. 선택한 방식에 맞춰 상대 주소·포트와 수신 대기 포트를 확인합니다.

Python 3.12.10, confluent-kafka 2.8.0, REST 선택 검토 런타임, MQTT 클라이언트 DLL과 UPER 검사 도구가 설치파일에 포함되어 있습니다. 개발 PC의 Python이나 prj22 작업 폴더는 실행에 필요하지 않습니다.

## MQTT/V2N 시험

다음 MQTT/V2N 시나리오 정의를 포함합니다. 웹에서 등록된 시나리오를 선택한 뒤 기존 Edit/Run 방식으로 실행합니다.

- 80: 자율주행차량 BSM 정보제공시험 [MQTT/V2N]
- 81: 통합교통관제시스템 BSM 정보수신시험 [MQTT/V2N]
- 82: 통합교통관제시스템 SPaT/TLSM/TIM 정보제공시험 [MQTT/V2N]
- 83: 자율주행차량 SPaT/TLSM/TIM 정보수신시험 [MQTT/V2N]
- 84: 통합교통관제시스템 SPaT 신호정보 제공시험 [MQTT/V2N]
- 85: 통합교통관제시스템 TLSM 신호등 상태정보 제공시험 [MQTT/V2N]
- 86: 통합교통관제시스템 TIM 통행지시 제공시험 [MQTT/V2N]

웹 시험 환경설정에서 Broker 주소·포트, 메시지별 토픽과 확인 건수를 지정합니다. QoS는 0입니다. 시험기가 구독하는 경우 선택한 목표 건수를 확보하거나 사용자가 중지할 때까지 기다립니다.

BSM 정보수신시험(#81)은 시험기가 BSM을 1초 간격으로 발행합니다. 자동 성공은 발행 절차 완료이며 최종 합격은 대상 수신 로그와 사후 대조합니다. 차량 정보수신시험(#83)은 대상 수신 관측 JSONL을 사용합니다. 파일 형식과 적용 범위는 설치 폴더의 `mqttv2nconformance/README.md`에 있습니다.

플랫폼 서버에 파일을 업로드하거나 현재 PC의 설치본을 교체하는 작업은 이 패키지 생성에 포함하지 않습니다. 배포 파일은 코드 서명되지 않았습니다.
'''
    (payload / 'INSTALLATION.md').write_text(guide, encoding='utf-8-sig')
    (output / 'INSTALLATION.md').write_text(guide, encoding='utf-8-sig')

    text = (ROOT / 'ScenarioEngineSetup/ScenarioEngineSetup.vdproj').read_text(encoding='utf-8-sig')
    files = sorted(p for p in payload.rglob('*') if p.is_file())
    hierarchy, file_blocks = [], []
    for path in files:
        relative = path.relative_to(payload).as_posix()
        file_id = SPECIAL_IDS.get(relative, ident('file', relative))
        folder = path.parent.relative_to(payload).as_posix()
        folder_id = APP_FOLDER if folder == '.' else ident('folder', folder)
        hierarchy.append('        "Entry"\n        {\n'
                         f'        "MsmKey" = "8:{file_id}"\n'
                         '        "OwnerKey" = "8:_UNDEFINED"\n'
                         '        "MsmSig" = "8:_UNDEFINED"\n        }\n')
        data = [('SourcePath', '8:' + str(path).replace('\\', '\\\\')), ('TargetName', '8:' + path.name),
                ('Tag', '8:'), ('Folder', '8:' + folder_id), ('Condition', '8:'),
                ('Transitive', '11:FALSE'), ('Vital', '11:TRUE'), ('ReadOnly', '11:FALSE'),
                ('Hidden', '11:FALSE'), ('System', '11:FALSE'), ('Permanent', '11:FALSE'),
                ('SharedLegacy', '11:FALSE'), ('PackageAs', '3:1'), ('Register', '3:1'),
                ('Exclude', '11:FALSE'), ('IsDependency', '11:FALSE'), ('IsolateTo', '8:')]
        file_blocks.append(f'            "{{1FB2D0AE-D3B9-43D4-B9DD-F88EC61E35DE}}:{file_id}"\n            {{\n' +
                           ''.join(f'            "{key}" = "{value}"\n' for key, value in data) + '            }\n')
    text = replace_block(text, 'Hierarchy', 4, ''.join(hierarchy))
    text = replace_block(text, 'File', 8, ''.join(file_blocks))
    text = replace_block(text, 'ProjectOutput', 8, '')
    children = {}
    for directory in sorted(p for p in payload.rglob('*') if p.is_dir()):
        relative = directory.relative_to(payload).as_posix()
        parent = directory.parent.relative_to(payload).as_posix()
        children.setdefault(parent, []).append(relative)
    app_start = text.index('"{3C67513D-01DD-4637-8A68-80971EB9504F}:' + APP_FOLDER + '"')
    head, tail = text[:app_start], text[app_start:]
    tail = replace_block(tail, 'Folders', 16, ''.join(folder_node(child, children) for child in children.get('.', [])))
    text = head + tail
    product_code = '{' + str(uuid.uuid5(uuid.UUID(UPGRADE_CODE.strip('{}')), args.version)).upper() + '}'
    text = re.sub(r'"ProductCode" = "8:\{[^}]+\}"', f'"ProductCode" = "8:{product_code}"', text)
    text = re.sub(r'"PackageCode" = "8:\{[^}]+\}"', f'"PackageCode" = "8:{{{str(uuid.uuid4()).upper()}}}"', text)
    text = re.sub(r'"ProductVersion" = "8:[^"]+"', f'"ProductVersion" = "8:{args.version}"', text)
    output_msi = str(output / 'ScenarioEngineSetup.msi').replace('\\', '\\\\')
    text = re.sub(r'"OutputFilename" = "8:[^"]+"', lambda _: f'"OutputFilename" = "8:{output_msi}"', text)
    text = text.replace('"Enabled" = "11:TRUE"', '"Enabled" = "11:FALSE"')
    project = stage / 'ScenarioEngineSetup.vdproj'
    project.write_text(text, encoding='utf-8-sig', newline='\r\n')
    solution = '''Microsoft Visual Studio Solution File, Format Version 12.00
# Visual Studio Version 17
VisualStudioVersion = 17.0.31903.59
MinimumVisualStudioVersion = 10.0.40219.1
Project("{54435603-DBB4-11D2-8724-00A0C9A8B90C}") = "ScenarioEngineSetup", "ScenarioEngineSetup.vdproj", "{0626D39A-A009-475C-8E1E-D75BB42D4A6B}"
EndProject
Global
    GlobalSection(SolutionConfigurationPlatforms) = preSolution
        Release|x64 = Release|x64
    EndGlobalSection
    GlobalSection(ProjectConfigurationPlatforms) = postSolution
        {0626D39A-A009-475C-8E1E-D75BB42D4A6B}.Release|x64.ActiveCfg = Release
        {0626D39A-A009-475C-8E1E-D75BB42D4A6B}.Release|x64.Build.0 = Release
    EndGlobalSection
EndGlobal
'''
    (stage / 'ScenarioEngineInstaller.sln').write_text(solution, encoding='utf-8', newline='\r\n')
    info['productCode'] = product_code
    info['payloadSha256'] = {p.relative_to(payload).as_posix(): digest(p) for p in files}
    info['payloadFiles'] = len(files)
    info['payloadBytes'] = sum(p.stat().st_size for p in files)
    info['sourceInstallerTemplateSha256'] = digest(ROOT / 'ScenarioEngineSetup/ScenarioEngineSetup.vdproj')
    (output / 'build-manifest.json').write_text(json.dumps(info, ensure_ascii=False, indent=2), encoding='utf-8')
    print(json.dumps({'project': str(project), 'files': len(files), 'bytes': info['payloadBytes'], 'output': str(output)}, ensure_ascii=False))


if __name__ == '__main__':
    main()

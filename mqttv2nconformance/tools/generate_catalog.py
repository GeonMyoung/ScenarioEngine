import base64,hashlib,json,sys
from pathlib import Path
root=Path(__file__).resolve().parents[1];sys.path.insert(0,str(root/'runtime'))
from catalog import CASES,CENTER_SINGLE_CASES,MESSAGES,ui,items
dest=root/'registration';dest.mkdir(exist_ok=True);manifest=[]
previous={x['case']:x for x in json.loads((dest/'manifest.json').read_text(encoding='utf-8'))} if (dest/'manifest.json').exists() else {}
for case,c in CASES.items():
    (dest/(case+'.ui.json')).write_text(json.dumps(ui(case),ensure_ascii=False,indent=2),encoding='utf-8')
    manifest.append(dict(case=case,category='ITSK-00143-MQTT-V1',classification='F2C',sut=c['sut'],engine=c['engine'],
        title=c['sut']+' '+('/'.join(c['messages']).upper())+(' 정보제공시험' if c['receive'] else ' 정보수신시험'),
        messages=c['messages'],testNames=[x[0] for x in items(case)],platformId=None,platformRegistered=False))
    manifest[-1].update({k:v for k,v in previous.get(case,{}).items() if k not in ('case','category','classification','sut','engine','messages','testNames')})
    if case in CENTER_SINGLE_CASES:
        message=CENTER_SINGLE_CASES[case]
        name='TIM 통행지시' if message=='tim' else MESSAGES[message]['title']
        title=f"{c['sut']} {name} 제공시험"
        registration=dest/(case+'.tsb')
        registration.write_bytes(base64.b64encode(json.dumps(dict(category=manifest[-1]['category'],testScenario=case)).encode('utf-8')))
        manifest[-1].update(title=title,platformTitle=title+' [MQTT/V2N]',registrationFile=registration.name,
                            tsbSha256=hashlib.sha256(registration.read_bytes()).hexdigest())
(dest/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2),encoding='utf-8')
print(len(manifest),'cases,',sum(len(x['testNames']) for x in manifest),'selectable items')

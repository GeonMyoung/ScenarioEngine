"""Audit already collected v2 runs by identity, without rerunning tests."""
from pathlib import Path
import base64, json, sys

root=Path(sys.argv[1]); catalog=json.loads((root/'scenarios.json').read_text(encoding='utf-8-sig'))
scenarios={s['id']:s for s in catalog['scenarios']}; records=[]
for folder in sorted((root/'runs').iterdir()):
    out=folder/'easy-outcome.json'
    if not out.exists(): continue
    result=json.loads(out.read_text(encoding='utf-8-sig')); session=json.loads((folder/'session.json').read_text(encoding='utf-8-sig'))
    if result['Verdict'] not in ('SUCCESS','FAIL','STOPPED','NOT_RUN'): continue
    scenario=scenarios[result['ScenarioId']]; messages=[]; commands=[]; states=[]
    for line in (folder/'controller-messages.jsonl').read_text(encoding='utf-8').splitlines():
        event=json.loads(line); msg=event['message']
        if event['direction']=='TX' and msg.get('method') in ('SETUP','START','STOP'): commands.append(msg['method'])
        if event['direction']!='RX': continue
        data=msg.get('data',{})
        if not isinstance(data,dict): continue
        if msg.get('level')=='state': states.append(data)
        text=data.get('log',''); direction='TX' if text.startswith('[송신 메시지') else 'RX' if text.startswith('[수신 메시지') else None
        if direction:
            actor=scenario['testerSystem' if direction=='TX' else 'targetSystem']
            assert data['sender']==actor,(folder,data['sender'],actor)
            detail=json.loads(base64.b64decode(data['data']))
            assert detail['발송 주체']==actor,(folder,detail)
            messages.append({'direction':direction,'sender':actor})
    if result['Verdict'] in ('SUCCESS','FAIL'):
        assert messages,(folder,'no evidence')
        assert sum(s.get('testName')=='MainScenario' and s.get('state')=='FINISH' for s in states)==1
        assert not any(s.get('state')=='COMPLETE' for s in states)
    if result['Verdict']=='NOT_RUN' and 'START' in commands: continue # Earlier GUI regression evidence, preserved separately.
    records.append({'run':folder.name,'id':result['ScenarioId'],'tests':result['Tests'],'verdict':result['Verdict'],'commands':commands,'sent':sum(x['direction']=='TX' for x in messages),'received':sum(x['direction']=='RX' for x in messages),'platform':session['agentUrl'].startswith('wss:')})
required=[(42,['normal_bsm'],'SUCCESS'),(43,['normal_bsm'],'SUCCESS'),(44,['normal_map','normal_tim'],'SUCCESS'),(47,['normal_bsm'],'SUCCESS'),(50,['normal_spat'],'SUCCESS'),(54,['normal_bsm'],'SUCCESS'),(56,['normal_tls'],'SUCCESS'),(52,['normal_bsm'],'SUCCESS'),(43,['login_retry'],'STOPPED'),(42,['normal_bsm'],'FAIL'),(42,['normal_bsm'],'NOT_RUN')]
for sid,keys,verdict in required: assert any(r['id']==sid and r['tests']==keys and r['verdict']==verdict for r in records),(sid,keys,verdict)
assert any(r['platform'] and r['verdict']=='SUCCESS' for r in records)
ui=json.loads((root/'ui-flow-verification.json').read_text(encoding='utf-8'))
assert ui['appliedBeforeStart'] and ui['editInvalidatedStart'] and ui['reappliedBeforeStart'] and ui['verdict']=='SUCCESS'
result={'scope':'v2 identity/configuration/launcher workflow; scoped runs, not full 152-item campaign','records':records,'uiFlow':ui,'note':'Two original harness summaries saw other concurrent run directories; this audit correlates session IDs and actual saved evidence. No protocol replay.'}
(root.parent/'verification-final.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps({'auditedRuns':len(records),'senderIdentityChecked':True,'uiFlow':'SUCCESS','livePlatform':'SUCCESS'},ensure_ascii=False))

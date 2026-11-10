"""BSM stimulus execution and durable evidence for later receiver-log review."""
import csv,hashlib,json,secrets,time
from datetime import datetime,timezone,timedelta
from container import Container,encode,validate
from failures import Failure
from transport import Stopped
from bsm_stimulus import PROFILE,SCHEMA_REVIEW,SCHEMA_NOTICE,expected_fields,verify_fields

CASE='vehiclePublisher2center_mqtt_v1'
NOTICE='자동 성공은 BSM 발행 절차 완료를 뜻합니다. 통합교통관제시스템의 실제 수신과 최종 합격은 사후 수신 로그 대조로 결정합니다.'

def utc():return datetime.now(timezone.utc).isoformat(timespec='milliseconds')

def publish_bsm(runner,client):
    c=runner.c;message=runner.role['messages'][0]
    from catalog import MESSAGES
    definition=MESSAGES[message]
    seed=secrets.randbelow(256);run_id=secrets.token_hex(16)
    vehicle_id=secrets.token_hex(4);sample_start=datetime.now(timezone.utc)
    folder=runner.events.path;records=folder/'bsm-transmit.jsonl';csv_path=folder/'bsm-transmit.csv'
    fields=['run_id','sequence','topic','qos','interval_seconds','requested_utc','requested_monotonic_ns',
            'completed_utc','completed_monotonic_ns','interval_from_previous_seconds','container_message_id',
            'fid','psid','frame_id','container_version','sample_profile','sample_timestamp_utc',
            'msgCnt','vehicle_id','secMark','lat','lon','elev','transmission','speed','heading','angle',
            'schema_review','decoded_json','payload_hex','payload_sha256','status','completion','reason']
    summary=dict(run_id=run_id,expected=c['repetitions'],published=0,attempted=0,
                 automatic_result_scope='BSM 발행 절차',sut_receive_confirmed=False,
                 final_verdict='PENDING_RECEIVER_LOG_REVIEW',notice=NOTICE,
                 records=records.name,csv=csv_path.name,qos=0,interval_seconds=1,
                 container_version=0,sample_profile=PROFILE,vehicle_id=vehicle_id,
                 sample_time_basis='시험 시작 UTC 기준으로 회차마다 1초씩 증가하는 모의 시각; 실제 발행 시각은 requested_utc',
                 schema_review=SCHEMA_REVIEW,schema_notice=SCHEMA_NOTICE)
    runner.publish_summary=summary
    runner.events.info(NOTICE,summary)
    runner.events.info('V2N version 0으로 회차별 다른 BSM 시험값을 발행합니다. '+SCHEMA_NOTICE,summary)
    previous=None;due=time.monotonic_ns()
    with records.open('w',encoding='utf-8',newline='\n') as journal, csv_path.open('w',encoding='utf-8-sig',newline='') as tabular:
        writer=csv.DictWriter(tabular,fieldnames=fields);writer.writeheader();tabular.flush()
        try:
            for index in range(c['repetitions']):
                client.check();runner.round=index+1
                msgid=(seed+index)%256
                sample_time=sample_start+timedelta(seconds=index)
                sec_mark=sample_time.second*1000+sample_time.microsecond//1000
                expected=expected_fields(index+1,sec_mark,vehicle_id)
                payload=runner.codec.bsm_sample(index+1,sec_mark,vehicle_id)
                wire=encode(Container(0,definition['fid'],1,0,b'',msgid,definition['psid'],payload),'big')
                _,view=runner.decoded('bsm',wire)
                verify_fields(view['decoded'],expected)
                while True:
                    client.check();remaining=(due-time.monotonic_ns())/1e9
                    if remaining<=0:break
                    time.sleep(min(.025,remaining))
                client.check();requested=time.monotonic_ns();runner.round=index+1
                row=dict(run_id=run_id,sequence=index+1,topic=c['topic_bsm'],qos=0,interval_seconds=1,
                    requested_utc=utc(),requested_monotonic_ns=requested,
                    completed_utc=None,completed_monotonic_ns=None,
                    interval_from_previous_seconds=None if previous is None else (requested-previous)/1e9,
                    container_message_id=msgid,fid=definition['fid'],psid=definition['psid'],frame_id=20,
                    container_version=0,sample_profile=PROFILE,sample_timestamp_utc=sample_time.isoformat(timespec='milliseconds'),
                    vehicle_id=vehicle_id,**{k:v for k,v in expected.items() if k!='id'},
                    schema_review=SCHEMA_REVIEW,decoded_json=json.dumps(view['decoded'],ensure_ascii=False,separators=(',',':')),
                    payload_hex=wire.hex(),payload_sha256=hashlib.sha256(wire).hexdigest(),
                    status='ATTEMPTED',completion=None,reason=None)
                summary['attempted']=index+1
                try:
                    completion=client.publish(c['topic_bsm'],wire,qos=0,retain=False,timeout=c['timeout_seconds'])
                    row.update(status='PUBLISHED',completion=completion['completion'],completed_utc=utc(),completed_monotonic_ns=time.monotonic_ns())
                    runner.completed=index+1;summary['published']=index+1
                except Exception as error:
                    row.update(status='STOPPED' if isinstance(error,Stopped) else 'FAILED',reason=str(error));raise
                finally:
                    journal.write(json.dumps(row,ensure_ascii=False)+'\n');journal.flush()
                    writer.writerow(row);tabular.flush()
                    status={'PUBLISHED':'발행 완료 · 대상 수신 확인 대기','FAILED':'발행 실패','STOPPED':'발행 중지'}[row['status']]
                    runner.events.info(f'BSM {index+1}/{c["repetitions"]}건 · {status}',
                        dict(**row,direction='송신',message=definition['title'],message_result=status,
                             observed_at=row['completed_utc'] or row['requested_utc'],version=0,
                             message_id=msgid,decoded=view['decoded'],validation=view['validation'],
                             criterion='설정 토픽으로 1초 간격·QoS 0 발행. 대상 수신은 사후 로그 대조',
                             completed=runner.completed,expected=c['repetitions']),runner.role['engine'])
                previous=requested
                # Socket completion and log processing do not add another one-second delay.
                # Never burst to catch up after a delayed send; retain actual timestamps.
                due=requested+1_000_000_000
            runner.events.info(f'BSM {runner.completed}건 발행 절차를 완료했습니다. 최종 합격은 사후 수신 로그 대조 후 결정합니다.',summary)
        finally:
            summary['finished_utc']=utc()
            summary['records_sha256']=hashlib.sha256(records.read_bytes()).hexdigest()
            (folder/'bsm-transmit-summary.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2),encoding='utf-8')

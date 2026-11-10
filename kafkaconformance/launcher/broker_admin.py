"""Prepare topics only on the launcher's owned loopback development broker."""
import argparse,json,re,time
from pathlib import Path
from confluent_kafka.admin import AdminClient,NewTopic
def main():
    p=argparse.ArgumentParser();p.add_argument('--config',required=True);a=p.parse_args();c=json.loads(Path(a.config).read_text(encoding='utf-8-sig'))
    if not re.fullmatch(r'127\.0\.0\.1:[0-9]+',c['bootstrap_servers']):raise ValueError('간편 실행기는 직접 만든 loopback 브로커만 준비합니다.')
    admin=AdminClient({'bootstrap.servers':c['bootstrap_servers'],'socket.timeout.ms':5000});md=admin.list_topics(timeout=10)
    topics=list(dict.fromkeys(c['topic_'+i[1]] for i in c['selected']))
    missing=[NewTopic(t,1,1) for t in topics if t not in md.topics]
    if missing:
        for f in admin.create_topics(missing,request_timeout=10).values():f.result(timeout=12)
    md=admin.list_topics(timeout=10)
    for t in topics:
        if t not in md.topics or md.topics[t].error:raise ValueError('합의 토픽 준비 실패: '+t)
    print(json.dumps(dict(bootstrap=c['bootstrap_servers'],topics=topics,partitions=1,scope='owned development broker only')))
if __name__=='__main__':main()

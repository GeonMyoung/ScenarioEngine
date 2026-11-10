const platformOrigin = 'https://106.250.189.37:8443';
const kinds = new Set(['web-dirty','hello','poll','result','before-setup','after-setup','before-start','after-start','before-stop','after-stop','web-error']);
const ports = Array.from({length:16},(_,i)=>43763+i);
const routes = new Map(), nextScan = new Map();
const mutating = new Set(['web-dirty','result','before-setup','after-setup','before-start','after-start','before-stop','after-stop','web-error']);

async function requestAt(port, request, timeout) {
  const response=await fetch(`http://127.0.0.1:${port}/bridge`,{
    method:'POST',headers:{'Content-Type':'application/json','X-Rest-Extension':chrome.runtime.id},
    body:JSON.stringify(request),signal:AbortSignal.timeout(timeout)
  });
  const data=await response.json();
  if(!response.ok || data.error)throw Error(data.error||'실행기 연결 응답을 확인하세요.');
  return data;
}
async function discover(request) {
  // Discovery carries no settings or credentials. Mutations are sent only after
  // verifying both the channel and the currently bound document's token.
  const hello={kind:'hello',channel:request.channel,clientId:request.clientId,token:'',data:{}};
  const found=(await Promise.all(ports.map(async port=>{
    try{const value=await requestAt(port,hello,700);return value.linked?{port,value}:null;}catch{return null;}
  }))).filter(Boolean);
  if(found.length>1)throw Error('같은 회차에 실행기가 둘 이상 연결되어 있습니다. 중복 연결을 해제하세요.');
  return found[0];
}
chrome.runtime.onMessage.addListener((request,sender,reply)=>{
  let url;try{url=new URL(sender.url);}catch{}
  if(!url || url.origin!==platformOrigin || !url.pathname.startsWith('/static/test/') || !sender.tab || !kinds.has(request.kind) || !/^\d{1,18}$/.test(request.channel) || typeof request.clientId!=='string' || !request.clientId || request.clientId.length>128){reply({error:'허용된 시험 화면이 아닙니다.'});return false;}
  request={...request,clientId:`${sender.tab.id}:${sender.documentId??sender.frameId}:${request.clientId}`};
  const key=`${sender.tab.id}/${sender.documentId??sender.frameId}/${request.clientId}/${request.channel}`;
  (async()=>{
    let route=routes.get(key);
    if(!route){
      if(request.kind==='hello'&&Date.now()<(nextScan.get(key)||0))return {linked:false};
      nextScan.set(key,Date.now()+1500);
      const found=await discover(request);
      if(!found){if(request.kind==='hello')return {linked:false};throw Error('해당 회차의 실행기에 연결되지 않았습니다.');}
      route={port:found.port};routes.set(key,route);nextScan.delete(key);
      if(request.kind==='hello')return found.value;
      if(found.value.token!==request.token)throw Error('실행기 연결이 변경됐습니다. 환경설정을 다시 적용하세요.');
    }
    if(mutating.has(request.kind)){
      const hello=await requestAt(route.port,{kind:'hello',channel:request.channel,clientId:request.clientId,token:'',data:{}},3000);
      if(!hello.linked || hello.token!==request.token)throw Error('시험 회차 연결이 변경됐습니다. 다시 연결하세요.');
    }
    const result=await requestAt(route.port,request,request.kind==='before-start'?90000:30000);
    if(request.kind!=='hello'&&result.linked===false)throw Error('시험 회차 연결이 종료됐습니다.');
    if(request.kind==='poll'&&result.command)await chrome.tabs.update(sender.tab.id,{active:true});
    return result;
  })().then(reply).catch(error=>{routes.delete(key);nextScan.delete(key);reply({error:error.message||'실행기에 연결되지 않았습니다.'});});
  return true;
});
chrome.tabs.onRemoved.addListener(tabId=>{for(const key of routes.keys())if(key.startsWith(tabId+'/'))routes.delete(key);for(const key of nextScan.keys())if(key.startsWith(tabId+'/'))nextScan.delete(key);});

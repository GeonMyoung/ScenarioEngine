const origin = 'https://106.250.189.37:8443';
const kinds = new Set(['hello','poll','result','before-setup','after-setup','before-start','after-start','before-stop','after-stop','web-error']);
chrome.runtime.onMessage.addListener((request,sender,reply)=>{
  if(!sender.url?.startsWith(origin+'/static/test/') || !kinds.has(request.kind) || !/^\d+$/.test(request.channel)) {
    reply({error:'허용된 시험 화면이 아닙니다.'});return false;
  }
  fetch('http://127.0.0.1:43762/bridge',{method:'POST',headers:{'Content-Type':'application/json','X-Datex-Extension':chrome.runtime.id},body:JSON.stringify(request),signal:AbortSignal.timeout(30000)})
    .then(async response=>{const data=await response.json();if(request.kind==='poll' && data.command)chrome.tabs.update(sender.tab.id,{active:true});reply(data);})
    .catch(()=>reply({error:'간편실행기에 연결되지 않았습니다.'}));
  return true;
});

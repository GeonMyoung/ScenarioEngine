(() => {
  if(location.origin!=='https://106.250.189.37:8443' || !location.pathname.startsWith('/static/test/'))return;
  let channel='',token='',linked=false,busy=false,polling=false,replay=false,lastCommand='',lastApplied=null,dirty=false;
  const clientId=crypto.randomUUID();
  const delay=ms=>new Promise(resolve=>setTimeout(resolve,ms));
  const clean=text=>text.replace(/[\uE000-\uF8FF]/g,'').trim();
  const button=name=>{const found=[...document.querySelectorAll('button')].filter(x=>clean(x.textContent)===name);if(found.length!==1)throw Error('웹의 ‘'+name+'’ 버튼을 찾지 못했습니다.');return found[0];};
  function notice(text){let el=document.getElementById('standard-test-bridge-status');if(!el){el=document.createElement('div');el.id='standard-test-bridge-status';el.setAttribute('role','status');el.style.cssText='position:fixed;right:12px;bottom:12px;z-index:2147483000;max-width:460px;padding:9px 14px;background:#f6f4ed;color:#235c43;border:1px solid #235c43;font:14px/1.5 sans-serif';document.body.append(el);}el.textContent=text;}
  async function call(kind,data){const result=await chrome.runtime.sendMessage({kind,channel,clientId,token,data});if(result.error)throw Error(result.error);return result;}
  async function tab(name){const el=button(name);el.click();await delay(160);}
  function inputs(){const values={};for(const input of document.querySelectorAll('input[name]')){if(!input.name)continue;values[input.name]=input.type==='checkbox'?input.checked:input.value;}return values;}
  async function waitFor(check,label,timeout=15000){const end=Date.now()+timeout;while(!check()){if(Date.now()>end)throw Error(label);await delay(80);}}
  async function fill(values){
    await tab('시험 환경설정');await waitFor(()=>Object.keys(values).every(name=>[...document.querySelectorAll('input[name]')].some(input=>input.name===name)),'환경설정 입력칸이 준비되지 않았습니다.');
    const fields=[...document.querySelectorAll('input[name]')];
    for(const [name,value] of Object.entries(values)){
      const matched=fields.filter(x=>x.name===name);if(matched.length!==1)throw Error('설정 항목을 찾지 못했습니다: '+name);
      const input=matched[0];input.scrollIntoView({block:'nearest'});
      if(input.type==='checkbox'){if(input.checked!==Boolean(value))input.click();}
      else {Object.getOwnPropertyDescriptor(HTMLInputElement.prototype,'value').set.call(input,String(value??''));input.dispatchEvent(new Event('input',{bubbles:true}));input.dispatchEvent(new Event('change',{bubbles:true}));}
      await delay(15);
    }
    const actual=inputs();for(const [name,value] of Object.entries(values))if(String(actual[name])!==String(value??''))throw Error('웹 입력값이 일치하지 않습니다: '+name);
  }
  function actualClick(el){if(el.disabled)throw Error('웹 버튼이 비활성 상태입니다. 환경설정과 연결 상태를 확인하세요.');replay=true;try{el.click();}finally{replay=false;}}
  async function action(kind,values){
    if(kind==='setup'){
      const data={values:values||inputs()};await call('before-setup',data);actualClick(button('설정'));await call('after-setup',data);lastApplied=data.values;dirty=false;notice('웹 환경설정 적용 완료 · 웹의 시험 시작을 사용할 수 있습니다.');
    }else if(kind==='start'){
      if(dirty)throw Error('수정한 환경설정을 먼저 적용하세요.');
      await call('before-start',{values:lastApplied});actualClick(button('시험 시작'));await call('after-start',{});notice('시험 진행 중 · 송수신과 결과를 웹에서 확인하세요.');
    }else if(kind==='stop'){
      await call('before-stop',{});actualClick(button('시험 종료'));await call('after-stop',{});notice('시험 중지를 요청했습니다.');
    }
  }
  for(const type of ['input','change'])document.addEventListener(type,event=>{if(linked&&!busy&&!replay&&event.target.matches?.('input[name]')&&!dirty){dirty=true;call('web-dirty',{}).catch(error=>notice(error.message));}},true);
  document.addEventListener('click',event=>{
    if(replay || !linked)return;const el=event.target.closest?.('button');if(!el)return;
    const text=clean(el.textContent),kind={'설정':'setup','시험 시작':'start','시험 종료':'stop'}[text];if(!kind)return;
    event.preventDefault();event.stopImmediatePropagation();
    if(busy){notice('이전 작업이 끝날 때까지 기다려주세요.');return;}
    busy=true;action(kind).catch(error=>notice(error.message)).finally(()=>{busy=false;});
  },true);
  window.addEventListener('message',event=>{
    if(event.origin!==location.origin || event.source!==window.parent)return;
    let data=event.data;if(typeof data==='string'){try{data=JSON.parse(data);}catch{return;}}
    const url=data?.clientInfo?.agent_url;const match=typeof url==='string' && /^wss:\/\/106\.250\.189\.37:8443\/ws\/test\/agent\/(\d+)\/$/.exec(url);
    if(match)channel=match[1];
  });
  async function tick(){
    if(!channel || busy || polling)return;polling=true;let processing=false;
    try{
      if(!token){const hello=await call('hello',{});if(!hello.linked)return;token=hello.token;linked=true;notice('간편실행기 연결됨 · 환경설정을 웹 화면에 표시할 준비가 됐습니다.');}
      const result=await call('poll',{});const cmd=result.command;if(!cmd || cmd.id===lastCommand)return;
      if(busy)return;processing=true;busy=true;lastCommand=cmd.id;let error='';
      try{
        if(cmd.kind==='apply'){await fill(cmd.data.values);await action('setup');}
        else if(cmd.kind==='start'){await tab('시험 제어');await waitFor(()=>{try{return !button('시험 시작').disabled;}catch{return false;}},'웹 시험 시작 버튼이 준비되지 않았습니다.');await action('start');}
        else if(cmd.kind==='stop'){await tab('시험 제어');await action('stop');}
        else throw Error('지원하지 않는 실행 요청입니다.');
      }catch(e){error=e.message;notice(error);}
      await call('result',{id:cmd.id,error});
    }catch(error){if(linked)notice(error.message);linked=false;token='';}
    finally{polling=false;if(processing)busy=false;}
  }
  setInterval(tick,500);
})();

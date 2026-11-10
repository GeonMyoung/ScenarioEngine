// A local test host for the actual service-worker routing code. It does not
// control Chrome or replace actual installed-extension verification.
import fs from 'node:fs';
import http from 'node:http';
import vm from 'node:vm';
import path from 'node:path';
import {fileURLToPath} from 'node:url';
const root=path.dirname(fileURLToPath(import.meta.url));
const events=[];let listener;
const context={URL,Map,Set,Array,Promise,Date,Error,AbortSignal,console,
  fetch:async(url,options)=>{const body=JSON.parse(options.body);events.push({port:new URL(url).port,kind:body.kind,channel:body.channel,client:body.clientId,hasSettings:!!body.data?.values});return fetch(url,options);},
  chrome:{runtime:{id:'hkcbopjignhkclfmejopkpkpmdlpnmba',onMessage:{addListener:f=>listener=f}},tabs:{update:async()=>{},onRemoved:{addListener:()=>{}}}}
};
vm.runInNewContext(fs.readFileSync(path.join(root,'../chrome-extension/background.js'),'utf8'),context);
const server=http.createServer(async(req,res)=>{
  let raw='';for await(const chunk of req)raw+=chunk;
  if(req.url==='/audit'){res.end(JSON.stringify(events));return;}
  try{const input=JSON.parse(raw);listener(input.request,input.sender,value=>{res.setHeader('Content-Type','application/json');res.end(JSON.stringify(value));});}catch(e){res.statusCode=400;res.end(JSON.stringify({error:e.message}));}
});
server.listen(0,'127.0.0.1',()=>fs.writeFileSync(process.argv[2],JSON.stringify({port:server.address().port,pid:process.pid})));

using SharedWebTest;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
namespace MqttEasy {
 public sealed class Settings {
  public static string RuntimeDirectory;
  public Dictionary<string,object> Tester,Peer,Effective;public List<string> Tests;public int Port;public bool MultiTim;
  public static string Quote(string value){var result=new System.Text.StringBuilder("\"");int slashes=0;foreach(char c in value??""){if(c=='\\'){slashes++;continue;}if(c=='"')result.Append('\\',slashes*2+1).Append(c);else result.Append('\\',slashes).Append(c);slashes=0;}result.Append('\\',slashes*2).Append('"');return result.ToString();}
  public static Dictionary<string,object> Defaults(Scenario s){return J.Decode<Dictionary<string,object>>(J.Encode(s.tester));}
  public static Dictionary<string,object> Inspect(Scenario s,Dictionary<string,object> data){
   string input=Path.Combine(Path.GetTempPath(),"mqtt-easy-config-"+Guid.NewGuid().ToString("N")+".json"),receipt=input+".receipt";
   try{
    J.Write(input,data);var args="-E -s -B -X utf8 "+Quote(Path.Combine(RuntimeDirectory,"mqttv2nconformance","runtime","configuration.py"))+" --case "+Quote(s.@case)+" --config "+Quote(input)+" --receipt "+Quote(receipt);
    try{Broker.Command(Path.Combine(RuntimeDirectory,"python","python.exe"),args,RuntimeDirectory,15000).GetAwaiter().GetResult();}catch(IOException){if(!File.Exists(receipt))throw;}
    var result=J.Decode<Dictionary<string,object>>(J.Read(receipt));if(!(J.Get(result,"valid") is bool)||!(bool)result["valid"])throw new InvalidOperationException(J.Text(result,"error"));return Credentials.Unprotect(J.Map(J.Get(result,"effectiveConfiguration")));
   }finally{if(File.Exists(input))File.Delete(input);if(File.Exists(receipt))File.Delete(receipt);}
  }
  public static Settings Create(Scenario s,Dictionary<string,object> input,List<string> keys,bool unused){
   var data=Defaults(s);foreach(var p in input)data[p.Key]=p.Value;var tests=s.tests.Select(t=>t.key).Where(keys.Contains).ToList();
   if(tests.Count==0||keys.Any(k=>!s.tests.Any(t=>t.key==k)))throw new InvalidOperationException("상세시험을 한 개 이상 선택하세요.");
   foreach(var key in data.Keys.ToList())if(!(data[key] is bool))data[key]=Convert.ToString(data[key],System.Globalization.CultureInfo.InvariantCulture);
   foreach(var t in s.tests)data["test_"+t.key]=tests.Contains(t.key);
   if(!s.provider&&!s.publishOnly&&String.IsNullOrEmpty(J.Text(data,"observation_file")))data["observation_file"]="자동 수신 관측";
   var effective=Inspect(s,data);int port=(int)J.Number(effective,"port");
   if(J.Text(effective,"host")!="127.0.0.1"||port<1024||port>48999)throw new InvalidOperationException("간편시험은 같은 PC의 Broker를 사용합니다. 주소는 127.0.0.1, 포트는 1024~48999로 입력하세요.");
   if(J.Text(effective,"ca_file").Length>0)throw new InvalidOperationException("자동으로 준비하는 로컬 Broker는 TLS 인증서를 사용하지 않습니다.");
   return new Settings{Tester=data,Peer=effective,Effective=effective,Tests=tests,Port=port,MultiTim=false};
  }
 }
 public sealed class Runner : IDisposable {
  readonly string bundle;readonly Action<Notice> notify;readonly bool localTest;readonly PortReservation peerPort=new PortReservation();
  volatile bool stopping,started,disposed;Controller controller;OwnedProcess engine,sut;Broker broker;WebFormLink web;long previousSetupIndex;
  Scenario scenario;Settings applied;Outcome outcome;string address;Task<Outcome> monitor;volatile string connectionError;
  readonly TaskCompletionSource<Dictionary<string,object>> uiReady=new TaskCompletionSource<Dictionary<string,object>>(TaskCreationOptions.RunContinuationsAsynchronously);
  readonly TaskCompletionSource<bool> began=new TaskCompletionSource<bool>(TaskCreationOptions.RunContinuationsAsynchronously),finished=new TaskCompletionSource<bool>(TaskCreationOptions.RunContinuationsAsynchronously);
  public bool Connected {get;private set;}public bool Prepared {get;private set;}public bool Running {get{return started&&!disposed;}}public Outcome Result {get{return outcome;}}public string RunDirectory {get;private set;}
  public Runner(string root,Action<Notice> handler,bool local=false){bundle=Path.GetFullPath(root);Settings.RuntimeDirectory=Runtime.Initialize(bundle);notify=handler;localTest=local;}
  void Tell(string kind,string text){if(notify!=null)notify(new Notice(kind,text){RunDirectory=RunDirectory});}
  void Check(){if(stopping)throw new OperationCanceledException();if(connectionError!=null)throw new IOException(connectionError);if(engine!=null&&engine.Exited)throw new IOException("설치된 시험 엔진이 종료됐습니다.");if(broker!=null&&broker.Exited)throw new IOException("시험용 Broker가 종료됐습니다.");if(sut!=null&&sut.Exited)throw new IOException("상대 에뮬레이터가 시험 중 종료됐습니다.");}
  async Task Wait(Func<bool> ready,int seconds,string message){var deadline=DateTime.UtcNow.AddSeconds(seconds);while(!ready()){Check();if(DateTime.UtcNow>=deadline)throw new InvalidOperationException(message);await Task.Delay(50);}}
  readonly EvidenceParts evidenceParts=new EvidenceParts();
  void Incoming(Dictionary<string,object> message){
   if(message.ContainsKey("localError")){connectionError=J.Text(message,"localError");Prepared=false;Tell("connection-error","플랫폼 연결이 종료됐습니다. 새 회차를 사용하세요.");return;}
   if(J.Text(message,"method")=="UI_CONFIGURE"){try{uiReady.TrySetResult(J.Decode<Dictionary<string,object>>(System.Text.Encoding.UTF8.GetString(Convert.FromBase64String(J.Text(message,"conf")))));}catch(Exception e){uiReady.TrySetException(e);}return;}
   if(J.Text(message,"method")!="NOTIFY")return;var data=J.Map(J.Get(message,"data"));string name=J.Text(data,"testName");
   if(J.Text(message,"level")=="info"){
    var log=J.Text(data,"log");
    var attachment=J.Text(data,"data");
    if(attachment.Length>0&&J.Text(data,"dataType")=="JSON"){
     try{
      var json=System.Text.Encoding.UTF8.GetString(Convert.FromBase64String(attachment));
      var evidence=evidenceParts.Read(J.Decode<Dictionary<string,object>>(json));
      if(evidence==null)return;
      if(evidence.ContainsKey("송수신 원문 HEX")){
       if(log.EndsWith(")")&&log.Contains(" (자료 "))log=log.Substring(0,log.LastIndexOf(" (자료 ",StringComparison.Ordinal));
       if(notify!=null)notify(new Notice("log",log){Evidence=evidence,TestName=name,RunDirectory=RunDirectory});
       return;
      }
     }catch(Exception){Tell("log","메시지 상세를 표시하지 못했습니다. 시험 기록에서 확인하세요.");}
    }
    Tell("log",log);
   }
   if(J.Text(message,"level")=="state"&&name.Length>0){var state=J.Text(data,"state");if(notify!=null)notify(new Notice("state",""){TestName=name,State=state,RunDirectory=RunDirectory});if(name=="MainScenario"&&state=="START")began.TrySetResult(true);if(name=="MainScenario"&&state=="FINISH")finished.TrySetResult(true);}
  }
  void SaveSession(){J.Write(Path.Combine(RunDirectory,"session.json"),new {bundleRoot=bundle,engineDirectory=Runtime.EngineDirectory,launcherSha256=J.Hash(Path.Combine(bundle,"시작하기.exe")),bundleManifestSha256=J.Hash(Path.Combine(bundle,"bundle-manifest.json")),scenario=scenario.id,@case=scenario.@case,tests=outcome.Tests,platformUrl=scenario.url,agentUrl=address,easyLauncher=true,verificationFault=Runtime.VerificationFault,configurationApplied=Prepared,updatedAt=DateTimeOffset.Now.ToString("o")});}
  public async Task Connect(Scenario selected,string input){
   if(Connected||controller!=null)throw new InvalidOperationException("이미 연결된 회차입니다.");scenario=selected;var agent=Endpoint.Agent(input,localTest);address=agent.AbsoluteUri;Runtime.Validate(bundle);
   Directory.CreateDirectory(Path.Combine(bundle,"runs"));foreach(var dir in Directory.GetDirectories(Path.Combine(bundle,"runs"))){var file=Path.Combine(dir,"session.json");if(File.Exists(file)&&J.Text(J.Decode<Dictionary<string,object>>(J.Read(file)),"agentUrl")==address)throw new InvalidOperationException("이미 사용한 회차입니다. 웹에서 새 자체 시험 회차를 열어주세요.");}
   RunDirectory=Path.Combine(bundle,"runs",DateTime.Now.ToString("yyMMdd-HHmmss-fff")+"-"+scenario.id+"-"+Guid.NewGuid().ToString("N").Substring(0,6));
   if(Path.Combine(RunDirectory,"mqttv2n-results",new string('x',24),"events.jsonl").Length>=250)throw new InvalidOperationException("실행 기록 경로가 너무 깁니다. 간편실행기를 짧은 경로로 옮겨주세요.");Directory.CreateDirectory(RunDirectory);
   outcome=new Outcome{ScenarioId=scenario.id,Channel=Endpoint.Channel(agent),RunDirectory=RunDirectory,Tests=new List<string>(),Verdict="NOT_RUN"};SaveSession();
   try{
    var extension=J.Read(Path.Combine(bundle,"extension-id.txt")).Trim();web=new WebFormLink(outcome.Channel,extension);web.Event=WebEvent;J.Write(Path.Combine(RunDirectory,"web-bridge.json"),new {channel=outcome.Channel,port=web.Port,extensionId=extension});
    Tell("stage","Chrome의 공통 웹 연결 확장을 확인합니다. 자체 시험 탭을 열어주세요.");await Wait(()=>web.BrowserReady,20,"Chrome 연결 확장이 응답하지 않습니다. 표준적합성시험 웹 연결 확장을 켜고 새 시험 탭을 열어주세요.");
    controller=new Controller(Path.Combine(RunDirectory,"controller-messages.jsonl"));controller.Message=Incoming;await controller.Connect(agent);Check();
    engine=new OwnedProcess(Path.Combine(Runtime.EngineDirectory,"ScenarioEngineTest.exe"),Settings.Quote(address),RunDirectory,"engine");await Wait(()=>uiReady.Task.IsCompleted,30,"시험 구성을 받지 못했습니다. 새 회차로 연결하세요.");
    var keys=J.List(J.Get(await uiReady.Task,"scenarios")).Select(x=>J.Text(J.Map(x),"key")).ToList();if(!scenario.tests.All(t=>keys.Contains("test_"+t.key)))throw new InvalidOperationException("선택한 시험과 웹 회차가 다릅니다.");Connected=true;Tell("connected","설치된 엔진이 연결됐습니다. 환경설정을 적용하세요.");
   }catch(Exception e){Error(e);Dispose();throw;}
  }
  public void Invalidate(){Prepared=false;}
  Settings Managed(Settings settings){if(!scenario.provider&&!scenario.publishOnly){settings.Tester["observation_file"]=Path.Combine(RunDirectory,"sut-receipt.jsonl");return Settings.Create(scenario,settings.Tester,settings.Tests,false);}return settings;}
  void ReservePort(Settings value,bool choose){if(!choose){peerPort.Exact(value.Port);return;}int before=value.Port,port=peerPort.Available(before,48999);if(port!=before){value.Tester["port"]=port;var updated=Settings.Create(scenario,value.Tester,value.Tests,false);value.Tester=updated.Tester;value.Effective=value.Peer=updated.Effective;value.Port=port;Tell("stage","사용 중인 포트를 피해 "+port+"로 조정하고 웹 설정에 반영합니다.");}}
  public async Task Apply(Settings settings){
   if(!Connected||started)throw new InvalidOperationException("시험 시작 전 환경설정을 적용하세요.");Prepared=false;Check();try{settings=Managed(settings);ReservePort(settings,true);Tell("stage","웹 입력칸과 실제 설정 버튼으로 환경설정을 적용합니다.");await web.Command("apply",new {values=settings.Tester});if((!Prepared&&!started)||!SelectionMatches(settings))throw new InvalidOperationException("웹 설정의 엔진 수락을 확인하지 못했습니다.");}catch(Exception e){Prepared=false;Error(e);throw;}
  }
  Settings FromWeb(Dictionary<string,object> data){var values=J.Map(J.Get(data,"values"));var keys=scenario.tests.Where(t=>J.Get(values,"test_"+t.key) is bool&&(bool)values["test_"+t.key]).Select(t=>t.key).ToList();var value=Settings.Create(scenario,values,keys,false);if(!scenario.provider&&!scenario.publishOnly&&J.Text(value.Tester,"observation_file")!=Path.Combine(RunDirectory,"sut-receipt.jsonl"))throw new InvalidOperationException("간편시험의 수신 관측 파일은 자동 관리됩니다. 실행기에서 설정을 다시 적용하세요.");return value;}
  async Task<object> WebEvent(string kind,Dictionary<string,object> data){
   if(!Connected)throw new InvalidOperationException("엔진 연결을 기다려주세요.");
   if(kind=="web-dirty"){Prepared=false;Tell("web-editing","웹 설정이 변경됐습니다. 다시 적용하세요.");return null;}
   if(kind=="before-setup"){if(started)throw new InvalidOperationException("시험 중에는 설정을 변경할 수 없습니다.");Prepared=false;previousSetupIndex=0;try{previousSetupIndex=J.Number(J.Decode<Dictionary<string,object>>(J.Read(Path.Combine(RunDirectory,"mqttv2n-selection.json"))),"testIdx");}catch(IOException){}ReservePort(FromWeb(data),false);return null;}
   if(kind=="after-setup"){
    var value=FromWeb(data);await Wait(()=>SelectionMatches(value),15,"웹 입력값이 엔진에 적용되지 않았습니다. 설정을 확인하세요.");applied=value;outcome.Tests=value.Tests.ToList();J.Write(Path.Combine(RunDirectory,"platform-setup.json"),value.Tester);J.Write(Path.Combine(RunDirectory,"sut-config.json"),value.Effective);J.Write(Path.Combine(RunDirectory,"selection-plan.json"),new {@case=scenario.@case,tests=value.Tests.Select(k=>"test_"+k).ToArray()});Prepared=true;SaveSession();if(notify!=null)notify(new Notice("web-configured","웹 설정 적용 완료"){RunDirectory=RunDirectory,Configuration=value.Tester,Tests=value.Tests});return null;
   }
   if(kind=="before-start"){await PrepareWebStart();return null;}if(kind=="after-start")return null;
   if(kind=="before-stop"||kind=="after-stop"){stopping=true;return null;}throw new InvalidOperationException("지원하지 않는 웹 연결 요청입니다.");
  }
  bool SelectionMatches(Settings settings){try{
   var actual=J.Decode<Dictionary<string,object>>(J.Read(Path.Combine(RunDirectory,"mqttv2n-selection.json")));if(J.Number(actual,"testIdx")<=previousSetupIndex||!(J.Get(actual,"valid") is bool)||!(bool)actual["valid"])return false;
   if(J.Text(actual,"case")!=scenario.@case||J.Number(actual,"processId")!=engine.Id)throw new InvalidOperationException("선택한 시험과 실제 엔진 회차가 다릅니다.");
   return J.List(J.Get(actual,"tests")).Select(Convert.ToString).SequenceEqual(settings.Tests.Select(k=>"test_"+k))&&J.Equivalent(settings.Effective,Credentials.Unprotect(J.Map(J.Get(actual,"effectiveConfiguration"))));
  }catch(IOException){return false;}catch(ArgumentException){return false;}}
  public async Task<Outcome> Start(){if(!Prepared||applied==null)throw new InvalidOperationException("환경설정을 적용한 뒤 시작하세요. 변경한 값은 다시 적용해야 합니다.");try{await web.Command("start",new {},90000);if(monitor==null)throw new InvalidOperationException("웹 시험 시작을 확인하지 못했습니다.");return await monitor;}catch(Exception e){Error(e);Dispose();throw;}}
  OwnedProcess StartPeer(){var args=new[]{"-E","-s","-B","-X","utf8",Path.Combine(bundle,"runtime","peer_entry.py"),"--engine-root",Runtime.EngineDirectory,"--case",scenario.@case,"--config",Path.Combine(RunDirectory,"sut-config.json"),"--codec",Path.Combine(Runtime.EngineDirectory,"mqttv2nconformance","bin","MqttPayload.exe"),"--ready",Path.Combine(RunDirectory,"peer.ready"),"--go",Path.Combine(RunDirectory,"peer.go"),"--stop",Path.Combine(RunDirectory,"peer.stop"),"--subscriptions",Path.Combine(RunDirectory,"mqttv2n-results"),"--interval",Runtime.VerificationFault=="period-delay"?"1.3":"1","--fault",Runtime.VerificationFault=="spat-field"?"spat_timestamp":Runtime.VerificationFault=="silence"?"silence":Runtime.VerificationFault=="tim-missing"?"tim_missing":Runtime.VerificationFault=="tim-duplicate"?"tim_duplicate":""};
   if(Runtime.VerificationFault.Length>0){if(scenario.id!=82)throw new InvalidOperationException("검증용 오류 주입은 센터 정보제공시험에서만 사용합니다.");J.Write(Path.Combine(RunDirectory,"verification-stimulus.json"),new {fault=Runtime.VerificationFault,source="independent emulator",criteriaChanged=false});Tell("stage","개발 검증: 상대 에뮬레이터에 "+Runtime.VerificationFault+" 오류를 주입합니다.");}
   return new OwnedProcess(Path.Combine(Runtime.EngineDirectory,"python","python.exe"),String.Join(" ",args.Select(Settings.Quote)),RunDirectory,"sut");}
  async Task PrepareWebStart(){
   if(started||!Prepared||applied==null)throw new InvalidOperationException("설정을 다시 적용한 뒤 시작하세요.");Check();if(!SelectionMatches(applied)){Prepared=false;throw new InvalidOperationException("적용 설정이 변경됐습니다. 다시 적용하세요.");}Prepared=false;
   try{Tell("stage",scenario.publishOnly?"BSM 발행용 Broker를 준비합니다. 수신 확인은 사후 로그 대조로 수행합니다.":"시험용 MQTT Broker와 상대 에뮬레이터를 준비합니다.");broker=new Broker();if(Runtime.VerificationFault.Length>0&&scenario.id!=82)throw new InvalidOperationException("검증용 오류 주입은 센터 정보제공시험에서만 사용합니다.");await broker.Start(bundle,RunDirectory,applied);if(!scenario.publishOnly){sut=StartPeer();await Wait(()=>File.Exists(Path.Combine(RunDirectory,"peer.ready")),15,"상대 에뮬레이터의 연결·구독 준비가 완료되지 않았습니다.");if(!scenario.provider)File.WriteAllText(Path.Combine(RunDirectory,"peer.go"),"go");}started=true;Tell("web-starting",scenario.publishOnly?"Broker 준비 완료. BSM 발행 절차를 시작합니다.":"상대 준비 완료. 웹의 시험 시작을 진행합니다.");monitor=Observe();}catch(Exception e){Error(e);Dispose();Tell("run-finished",outcome.Verdict);throw;}
  }
  bool Delivered(){try{var d=J.Decode<Dictionary<string,object>>(J.Read(Path.Combine(RunDirectory,"mqttv2n-delivery.json")));return J.Number(d,"pending")==0&&J.Number(d,"error")==0&&J.Number(d,"discarded")==0&&J.Number(d,"lastIndex")>previousSetupIndex;}catch(IOException){return false;}catch(ArgumentException){return false;}}
  async Task<Outcome> Observe(){
   try{
    await Wait(()=>began.Task.IsCompleted,15,"웹 시작 명령을 받지 못했습니다.");
    if(scenario.provider){await Wait(()=>Directory.Exists(Path.Combine(RunDirectory,"mqttv2n-results"))&&Directory.GetFiles(Path.Combine(RunDirectory,"mqttv2n-results"),"ready.json",SearchOption.AllDirectories).Length==1,15,"시험기의 구독 준비를 확인하지 못했습니다.");File.WriteAllText(Path.Combine(RunDirectory,"peer.go"),"go");}
    DateTime? deadline=scenario.provider?(DateTime?)null:DateTime.UtcNow.AddSeconds(
        60+applied.Tests.Count*Convert.ToDouble(applied.Effective["timeout_seconds"])*Convert.ToDouble(applied.Effective["repetitions"]));
    DateTime? stopDeadline=null;
    while(!finished.Task.IsCompleted){
     if(stopping){
      if(stopDeadline==null)stopDeadline=DateTime.UtcNow.AddSeconds(25);
      if(DateTime.UtcNow>=stopDeadline)throw new OperationCanceledException();
     }else{
      Check();
      if(deadline.HasValue&&DateTime.UtcNow>=deadline.Value)throw new IOException("시험 제한시간을 초과했습니다.");
     }
     await Task.Delay(50);
    }
    // The installed engine records drained delivery after the terminal state.
    var drainDeadline=DateTime.UtcNow.AddSeconds(10);while(!Delivered()){if(DateTime.UtcNow>drainDeadline)throw new IOException("시험 자료 전송 완료를 확인하지 못했습니다.");await Task.Delay(50);}
    var reports=Directory.GetFiles(Path.Combine(RunDirectory,"mqttv2n-results"),"result.json",SearchOption.AllDirectories);if(reports.Length!=1)throw new IOException("회차의 결과 파일을 확인하지 못했습니다.");outcome.Report=J.Decode<Dictionary<string,object>>(J.Read(reports[0]));if(J.Text(outcome.Report,"case")!=scenario.@case)throw new IOException("시험 결과의 회차 구성이 일치하지 않습니다.");outcome.Verdict=J.Text(outcome.Report,"result");
    if(outcome.Verdict=="SUCCESS"){var results=J.List(J.Get(outcome.Report,"tests")).Select(J.Map).ToList();if(results.Count!=applied.Tests.Count||!new HashSet<string>(results.Select(x=>J.Text(x,"test"))).SetEquals(applied.Tests.Select(k=>"test_"+k))||results.Any(x=>J.Text(x,"result")!="SUCCESS"))throw new IOException("선택 항목과 결과가 일치하지 않습니다.");}
    if(sut!=null){File.WriteAllText(Path.Combine(RunDirectory,"peer.stop"),"stop");var peerDeadline=DateTime.UtcNow.AddSeconds(5);while(!sut.Exited&&DateTime.UtcNow<peerDeadline)await Task.Delay(50);if(!sut.Exited||sut.Process.ExitCode!=0)throw new IOException("상대 에뮬레이터의 정상 종료를 확인하지 못했습니다.");}
    LocalReport.Write(RunDirectory,Path.Combine(Path.GetDirectoryName(reports[0]),"events.jsonl"),scenario,outcome.Verdict);J.Write(Path.Combine(RunDirectory,"easy-outcome.json"),outcome);
   }catch(OperationCanceledException){outcome.Verdict="STOPPED";J.Write(Path.Combine(RunDirectory,"easy-outcome.json"),outcome);}catch(Exception e){Error(e);}finally{Dispose();}Tell("run-finished",outcome.Verdict);return outcome;
  }
  public async Task<Outcome> WaitForWebStart(){await Wait(()=>monitor!=null,900,"웹에서 시험을 시작하지 않아 연결을 종료합니다.");return await monitor;}
  public async Task Stop(){Prepared=false;if(controller!=null&&started){Tell("stage","웹 종료 버튼으로 시험을 중지합니다.");bool fallback=false;try{await web.Command("stop",new {},7000);}catch{fallback=true;}if(fallback){stopping=true;try{await controller.Request("STOP",null,5000);}catch{}}}else stopping=true;}
  void Error(Exception e){if(RunDirectory!=null&&outcome!=null){outcome.Verdict=stopping?"STOPPED":"ERROR";J.Write(Path.Combine(RunDirectory,"easy-outcome.json"),outcome);File.WriteAllText(Path.Combine(RunDirectory,"easy-error.txt"),e.ToString());}Tell("error",InterfaceLogs.UserReport.PublicError(e));}
  public void Dispose(){if(disposed)return;disposed=true;Prepared=false;Connected=false;try{if(sut!=null){File.WriteAllText(Path.Combine(RunDirectory,"peer.stop"),"stop");sut.Dispose();sut=null;}}finally{try{if(engine!=null){engine.Dispose();engine=null;}}finally{if(broker!=null){broker.Dispose();broker=null;}if(controller!=null){controller.Dispose();controller=null;}if(web!=null){web.Dispose();web=null;}peerPort.Dispose();}}if(outcome!=null&&!File.Exists(Path.Combine(RunDirectory,"easy-outcome.json")))J.Write(Path.Combine(RunDirectory,"easy-outcome.json"),outcome);}
 }
}

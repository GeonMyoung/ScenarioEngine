using SharedWebTest;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace DatexEasy {
    public sealed class Settings {
        public Dictionary<string,object> Tester,Peer;
        public List<string> Tests;
        public bool MultiTim,TesterConnects;
        public string PortKey { get { return TesterConnects ? "peer_port" : "local_port"; } }
        public static bool Connects(Scenario scenario,Dictionary<string,object> values) {
            object value;
            if(values.TryGetValue("use_initiate",out value) && !(value is bool))throw new InvalidOperationException("개시요청 사용은 선택 또는 해제로 설정하세요.");
            return scenario.provider != (value is bool && (bool)value);
        }
        public int Port;
        static int Integer(Dictionary<string,object> data,string key,int maximum) {
            int value;
            if(!int.TryParse(J.Text(data,key),out value) || value<1 || value>maximum)
                throw new InvalidOperationException(key+" 값은 1~"+maximum+" 범위의 정수여야 합니다.");
            data[key]=value;return value;
        }
        public static Settings Create(Scenario s,Dictionary<string,object> input,List<string> keys,bool multi) {
            var data=J.Decode<Dictionary<string,object>>(J.Encode(input));
            foreach(var key in new[]{"my_domain","peer_domain","user","pass"})
                if(String.IsNullOrWhiteSpace(J.Text(data,key)))throw new InvalidOperationException("도메인·사용자 이름·비밀번호를 모두 입력하세요.");
            if(J.Text(data,"my_domain")==J.Text(data,"peer_domain"))throw new InvalidOperationException("시험 시스템과 시험 대상 도메인은 서로 다르게 입력하세요.");
            var tests=s.tests.Select(t=>t.key).Where(keys.Contains).ToList();
            if(tests.Count==0 || keys.Any(k=>!s.tests.Any(t=>t.key==k)))throw new InvalidOperationException("이 시험의 상세시험을 한 개 이상 선택하세요.");
            bool connects=Connects(s,data);
            if(connects && J.Text(data,"peer_ip")!="127.0.0.1")throw new InvalidOperationException("이 실행기는 같은 PC의 에뮬레이터를 사용합니다. 대상 주소는 127.0.0.1로 입력하세요.");
            var port=Integer(data,connects?"peer_port":"local_port",65535);
            Integer(data,"hb_dur",65535);Integer(data,"rsp_timeout",255);Integer(data,"connect_timeout_s",600);
            if(s.provider){Integer(data,"fred_maintain_s",86400);Integer(data,"receive_s",86400);Integer(data,"period_s",86400);}
            if(tests.Contains("invalid_login") && J.Text(data,"invalid_pass")==J.Text(data,"pass"))throw new InvalidOperationException("무효 로그인용 비밀번호는 정상 비밀번호와 다르게 입력하세요.");
            if(multi && (!s.provider || !tests.Contains("normal_tim")))throw new InvalidOperationException("복수 TIM은 TIM 정보제공 시험을 선택했을 때 사용할 수 있습니다.");
            foreach(var key in data.Keys.Where(k=>k.StartsWith("test_")).ToList())data.Remove(key);
            foreach(var t in s.tests)data["test_"+t.key]=tests.Contains(t.key);
            object initiation;
            if(data.TryGetValue("use_initiate",out initiation) && !(initiation is bool))throw new InvalidOperationException("개시요청 사용은 선택 또는 해제로 설정하세요.");
            data["use_initiate"]=initiation is bool && (bool)initiation;
            var peer=new Dictionary<string,object>{{"my_domain",data["peer_domain"]},{"peer_domain",data["my_domain"]},{"user",data["user"]},{"pass",data["pass"]},
                {"use_initiate",data["use_initiate"]},{"hb_dur",data["hb_dur"]},{"rsp_timeout",data["rsp_timeout"]},{"connect_timeout_s",data["connect_timeout_s"]}};
            peer[connects?"local_port":"peer_port"]=port;if(!connects)peer["peer_ip"]="127.0.0.1";
            // Config parsing requires an item; the per-session plan remains the source of actual selection.
            peer["test_session"]=true;
            return new Settings{Tester=data,Peer=peer,Tests=tests,MultiTim=multi,Port=port,TesterConnects=connects};
        }
    }
    public sealed class Runner : IDisposable {
        readonly string bundle;readonly Action<Notice> notify;readonly bool localTest;
        volatile bool stopping,started,disposed;Controller controller;OwnedProcess engine,sut;WebFormLink web;
        bool multiTim;Task<Outcome> monitor;
        Scenario scenario;Settings applied;Outcome outcome;string address;readonly PortReservation peerPort=new PortReservation();
        readonly TaskCompletionSource<Dictionary<string,object>> uiReady=new TaskCompletionSource<Dictionary<string,object>>(TaskCreationOptions.RunContinuationsAsynchronously);
        readonly TaskCompletionSource<bool> finished=new TaskCompletionSource<bool>(TaskCreationOptions.RunContinuationsAsynchronously);
        readonly TaskCompletionSource<bool> began=new TaskCompletionSource<bool>(TaskCreationOptions.RunContinuationsAsynchronously);
        volatile string connectionError;
        public bool Connected {get;private set;}
        public bool Prepared {get;private set;}
        public bool Running {get{return started && !disposed;}}
        public Outcome Result {get{return outcome;}}
        public string RunDirectory {get;private set;}
        public Runner(string root,Action<Notice> handler,bool local=false){bundle=Path.GetFullPath(root);notify=handler;localTest=local;}
        void Tell(string kind,string text){if(notify!=null)notify(new Notice(kind,text){RunDirectory=RunDirectory});}
        void Check(){if(stopping)throw new OperationCanceledException();if(connectionError!=null)throw new IOException(connectionError);if(engine!=null && engine.Exited)throw new IOException("시험 엔진이 종료됐습니다. 실행 기록을 확인하세요.");}
        async Task Wait(Func<bool> ready,int seconds,string message){var until=DateTime.UtcNow.AddSeconds(seconds);while(!ready()){Check();if(DateTime.UtcNow>=until)throw new InvalidOperationException(message);await Task.Delay(100);}}
        void Incoming(Dictionary<string,object> message){
            if(message.ContainsKey("localError")){connectionError=J.Text(message,"localError");Prepared=false;Tell("connection-error","플랫폼 연결이 종료됐습니다. 새 회차로 연결하세요.");return;}
            if(J.Text(message,"method")=="UI_CONFIGURE"){try{uiReady.TrySetResult(J.Decode<Dictionary<string,object>>(System.Text.Encoding.UTF8.GetString(Convert.FromBase64String(J.Text(message,"conf")))));}catch(Exception e){uiReady.TrySetException(e);}return;}
            if(J.Text(message,"method")!="NOTIFY")return;var data=J.Map(J.Get(message,"data"));string name=J.Text(data,"testName");
            if(J.Text(message,"level")=="info")Tell("log",J.Text(data,"log"));
            if(J.Text(message,"level")=="state" && name.Length>0){string state=J.Text(data,"state");if(notify!=null)notify(new Notice("state",""){TestName=name,State=state,RunDirectory=RunDirectory});if(name=="MainScenario" && state=="START")began.TrySetResult(true);if(name=="MainScenario" && state=="FINISH")finished.TrySetResult(true);}
        }
        void SaveSession(){J.Write(Path.Combine(RunDirectory,"session.json"),new {bundleRoot=bundle,scenario=scenario.id,@case=scenario.@case,tests=outcome.Tests,platformUrl=scenario.url,agentUrl=address,easyLauncher=true,configurationApplied=Prepared,updatedAt=DateTimeOffset.Now.ToString("o")});}
        public async Task Connect(Scenario selected,string input){
            if(Connected || controller!=null)throw new InvalidOperationException("이미 연결된 회차입니다.");scenario=selected;var agent=Endpoint.Agent(input,localTest);address=agent.AbsoluteUri;
            var manifest=J.Decode<Dictionary<string,object>>(J.Read(Path.Combine(bundle,"bundle-manifest.json")));var hashes=J.Map(J.Get(manifest,"runtimeSha256"));
            foreach(var file in hashes)if(J.Hash(Path.Combine(bundle,"runtime",file.Key))!=Convert.ToString(file.Value))throw new InvalidOperationException("실행 파일 구성이 다릅니다. ZIP 전체를 새 폴더에 풀어주세요.");
            Directory.CreateDirectory(Path.Combine(bundle,"runs"));
            foreach(var dir in Directory.GetDirectories(Path.Combine(bundle,"runs"))){var file=Path.Combine(dir,"session.json");if(File.Exists(file) && J.Text(J.Decode<Dictionary<string,object>>(J.Read(file)),"agentUrl")==address)throw new InvalidOperationException("이미 사용한 주소입니다. 웹에서 새 자체 시험 회차의 주소를 복사하세요.");}
            RunDirectory=Path.Combine(bundle,"runs",DateTime.Now.ToString("yyyyMMdd-HHmmss-fff")+"-ID"+scenario.id+"-easy-"+Guid.NewGuid().ToString("N").Substring(0,6));Directory.CreateDirectory(RunDirectory);
            outcome=new Outcome{ScenarioId=scenario.id,Channel=Endpoint.Channel(agent),RunDirectory=RunDirectory,Tests=new List<string>(),Verdict="NOT_RUN"};SaveSession();
            try{web=new WebFormLink(Endpoint.Channel(agent),J.Read(Path.Combine(bundle,"extension-id.txt")).Trim());web.Event=WebEvent;J.Write(Path.Combine(RunDirectory,"web-bridge.json"),new {channel=Endpoint.Channel(agent),port=web.Port,extensionId=J.Read(Path.Combine(bundle,"extension-id.txt")).Trim()});
                Tell("stage","Chrome 연결 확장을 확인하고 있습니다. 자체 시험 탭을 열어주세요.");await Wait(()=>web.BrowserReady,15,"Chrome 연결 확장이 응답하지 않습니다. 공통 확장을 갱신하고 자체 시험 탭을 새로 연 뒤 시도하세요.");
                Tell("stage","플랫폼과 시험 엔진을 연결하고 있습니다.");controller=new Controller(Path.Combine(RunDirectory,"controller-messages.jsonl"));controller.Message=Incoming;await controller.Connect(agent);Check();
                engine=new OwnedProcess(Path.Combine(bundle,"runtime","ScenarioEngineTest.exe"),'"'+address+'"',RunDirectory,"engine");
                await Wait(()=>uiReady.Task.IsCompleted,30,"시험 구성을 받지 못했습니다. 새 회차로 연결하세요.");var ui=await uiReady.Task;
                var keys=J.List(J.Get(ui,"scenarios")).Select(x=>J.Text(J.Map(x),"key")).ToList();if(!scenario.tests.All(t=>keys.Contains("test_"+t.key)))throw new InvalidOperationException("선택한 시험과 웹 회차가 다릅니다. 같은 시험의 새 주소를 복사하세요.");
                Connected=true;Tell("connected","연결됐습니다. 환경설정을 적용하세요.");
            }catch(Exception e){Error(e);Dispose();throw;}
        }
        public void Invalidate(){Prepared=false;}
        public async Task Apply(Settings settings){
            if(!Connected || started)throw new InvalidOperationException("시험 시작 전 연결 상태에서 환경설정을 적용하세요.");Prepared=false;Check();
            try{
                ReservePort(settings,true);multiTim=settings.MultiTim;Tell("stage","Chrome의 환경설정 입력칸을 채우고 실제 ‘설정’ 버튼을 누릅니다.");
                await web.Command("apply",new {values=settings.Tester});
                if((!Prepared && !started) || !SelectionMatches(settings))throw new InvalidOperationException("웹 설정의 엔진 적용을 확인하지 못했습니다.");
            }catch(Exception e){Prepared=false;Error(e);throw;}
        }
        void ReservePort(Settings settings,bool choose){
            if(!choose){peerPort.Exact(settings.Port);return;}int before=settings.Port;int port=peerPort.Available(before,65535);if(port==before)return;
            settings.Tester[settings.PortKey]=port;
            var updated=Settings.Create(scenario,settings.Tester,settings.Tests,settings.MultiTim);settings.Tester=updated.Tester;settings.Peer=updated.Peer;settings.Port=updated.Port;
            Tell("stage","포트 "+before+"가 사용 중이어서 "+port+"로 조정합니다. 변경값을 웹 환경설정에 표시합니다.");
        }
        Settings FromWeb(Dictionary<string,object> data){var values=J.Map(J.Get(data,"values"));var keys=scenario.tests.Where(t=>J.Get(values,"test_"+t.key) is bool && (bool)values["test_"+t.key]).Select(t=>t.key).ToList();return Settings.Create(scenario,values,keys,multiTim && keys.Contains("normal_tim"));}
        async Task<object> WebEvent(string kind,Dictionary<string,object> data){
            if(!Connected)throw new InvalidOperationException("시험 엔진 연결을 기다려주세요.");
            if(kind=="web-dirty"){Prepared=false;Tell("web-editing","웹 입력값이 변경됐습니다. 설정을 다시 적용하세요.");return null;}
            if(kind=="before-setup"){if(started)throw new InvalidOperationException("시험 실행 중에는 설정할 수 없습니다.");Prepared=false;ReservePort(FromWeb(data),false);return null;}
            if(kind=="after-setup"){
                var value=FromWeb(data);await Wait(()=>SelectionMatches(value),10,"웹의 설정이 엔진에 적용되지 않았습니다. 입력값을 확인하세요.");
                applied=value;outcome.Tests=value.Tests.ToList();
                J.Write(Path.Combine(RunDirectory,"platform-setup.json"),value.Tester);J.Write(Path.Combine(RunDirectory,"sut-config.json"),value.Peer);
                J.Write(Path.Combine(RunDirectory,"selection-plan.json"),new {@case=scenario.@case,tests=value.Tests.Select(k=>"test_"+k).ToArray()});
                Prepared=true;SaveSession();if(notify!=null)notify(new Notice("web-configured","웹 환경설정 적용 완료"){RunDirectory=RunDirectory,Configuration=value.Tester,Tests=value.Tests});return null;
            }
            if(kind=="before-start"){await PrepareWebStart();return null;}
            if(kind=="after-start")return null;
            if(kind=="before-stop" || kind=="after-stop"){stopping=true;return null;}
            throw new InvalidOperationException("지원하지 않는 웹 연결 요청입니다.");
        }
        bool SelectionMatches(Settings settings){try{
            var actual=J.Map(J.Decode<object>(J.Read(Path.Combine(RunDirectory,"datex-selection.json"))));
            if(!(J.Get(actual,"valid") is bool) || !(bool)actual["valid"])return false;
            if(J.Text(actual,"case")!=scenario.@case || J.Number(actual,"processId")!=engine.Id)throw new InvalidOperationException("선택한 시험과 실제 웹 회차가 다릅니다. 같은 시험의 새 주소를 복사하세요.");
            if(!J.List(J.Get(actual,"tests")).Select(Convert.ToString).SequenceEqual(settings.Tests.Select(k=>"test_"+k)))return false;
            // Engine echoes the applied configuration, including changed values with identical selection.
            var actualConfig=J.Map(J.Get(actual,"configuration"));
            return settings.Tester.All(p=>actualConfig.ContainsKey(p.Key) && Convert.ToString(actualConfig[p.Key])==Convert.ToString(p.Value));
        }catch(IOException){return false;}catch(ArgumentException){return false;}}
        public async Task<Outcome> Start(){
            if(!Prepared || applied==null)throw new InvalidOperationException("환경설정을 먼저 적용하세요. 변경한 값이 있다면 다시 적용해야 합니다.");
            try{await web.Command("start",new {});if(monitor==null)throw new InvalidOperationException("웹 시험 시작을 확인하지 못했습니다.");return await monitor;}catch(Exception e){Error(e);Dispose();throw;}
        }
        string PeerArguments(){return "--case "+scenario.@case+" --profile "+scenario.profile+" --mode emulator --role "+scenario.sutRole+" --config \""+Path.Combine(RunDirectory,"sut-config.json")+"\" --log \""+Path.Combine(RunDirectory,"sut.jsonl")+"\" --plan \""+Path.Combine(RunDirectory,"selection-plan.json")+"\" --duration 1800"+(applied.MultiTim?" --multi-tim true":"");}
        async Task PrepareWebStart(){
            if(started || !Prepared || applied==null)throw new InvalidOperationException("변경한 환경설정을 웹에 적용한 뒤 시작하세요.");
            Check();if(!SelectionMatches(applied)){Prepared=false;throw new InvalidOperationException("적용 설정이 변경됐습니다. 환경설정을 다시 적용하세요.");}
            Prepared=false;
            try{
                if(Ports.ListenOwner(applied.Port)!=0)throw new InvalidOperationException("입력한 포트를 다른 프로그램이 사용 중입니다. 사용 가능한 포트를 선택해 다시 적용하세요.");
                if(applied.TesterConnects){Tell("stage","시험 시스템이 접속할 수 있도록 시험 대상의 TCP 수신 대기를 먼저 준비합니다.");sut=new OwnedProcess(Path.Combine(bundle,"runtime","DatexBsmEmulator.exe"),PeerArguments(),RunDirectory,"sut");await Wait(()=>{if(sut.Exited)throw new IOException("시험 대상 준비에 실패했습니다.");return Ports.ListenOwner(applied.Port)==sut.Id;},10,"시험 대상의 수신 대기를 확인하지 못했습니다.");}
                Check();started=true;Tell("web-starting","웹의 시험 시작 요청을 진행합니다.");monitor=Observe();
            }catch(Exception e){Error(e);Dispose();Tell("run-finished",outcome.Verdict);throw;}
        }
        async Task<Outcome> Observe(){
            try{
                await Wait(()=>began.Task.IsCompleted,15,"웹에서 시험 시작 명령을 받지 못했습니다.");
                if(!applied.TesterConnects){await Wait(()=>Ports.ListenOwner(applied.Port)==engine.Id,10,"시험 시스템의 접속 대기를 확인하지 못했습니다.");sut=new OwnedProcess(Path.Combine(bundle,"runtime","DatexBsmEmulator.exe"),PeerArguments(),RunDirectory,"sut");}
                var deadline=DateTime.UtcNow.AddMinutes(40);DateTime? stopDeadline=null;
                while(!finished.Task.IsCompleted){if(stopping){if(stopDeadline==null)stopDeadline=DateTime.UtcNow.AddSeconds(8);if(DateTime.UtcNow>=stopDeadline.Value)throw new OperationCanceledException();}else Check();if(DateTime.UtcNow>deadline)throw new IOException("시험 대기 시간을 초과했습니다. 실행 기록을 확인하세요.");await Task.Delay(100);}
                var reports=Directory.GetFiles(Path.Combine(RunDirectory,"datex-results"),"*.json");if(reports.Length!=1)throw new IOException("최종 결과 파일을 확인하지 못했습니다.");
                outcome.Report=J.Decode<Dictionary<string,object>>(J.Read(reports[0]));if(J.Text(outcome.Report,"case")!=scenario.@case)throw new IOException("결과의 시험 구성이 일치하지 않습니다.");
                outcome.Verdict=J.Text(outcome.Report,"automaticVerdict");J.Write(Path.Combine(RunDirectory,"easy-outcome.json"),outcome);
            }catch(OperationCanceledException){outcome.Verdict="STOPPED";J.Write(Path.Combine(RunDirectory,"easy-outcome.json"),outcome);}
            catch(Exception e){Error(e);}finally{if(RunDirectory!=null){try{InterfaceLogs.UserReport.Write(RunDirectory,scenario.title,outcome.Verdict);}catch(Exception reportError){File.WriteAllText(Path.Combine(RunDirectory,"user-report-error.txt"),reportError.ToString());}}Dispose();}Tell("run-finished",outcome.Verdict);return outcome;
        }
        public async Task<Outcome> WaitForWebStart(){await Wait(()=>monitor!=null,900,"웹에서 시험을 시작하지 않아 연결을 종료합니다.");return await monitor;}
        public async Task Stop(){Prepared=false;if(controller!=null && started){Tell("stage","웹의 종료 버튼으로 시험을 중지합니다.");bool fallback=false;try{await web.Command("stop",new {},7000);}catch{fallback=true;}if(fallback){stopping=true;try{if(controller!=null)await controller.Request("STOP",null,5000);}catch{}}}else stopping=true;}
        void Error(Exception e){if(RunDirectory!=null){outcome.Verdict="ERROR";J.Write(Path.Combine(RunDirectory,"easy-outcome.json"),outcome);File.WriteAllText(Path.Combine(RunDirectory,"easy-error.txt"),e.ToString());}Tell("error",InterfaceLogs.UserReport.PublicError(e));}
        public void Dispose(){if(disposed)return;disposed=true;Prepared=false;Connected=false;try{if(sut!=null){sut.Dispose();sut=null;}}finally{try{if(engine!=null){engine.Dispose();engine=null;}}finally{if(controller!=null){controller.Dispose();controller=null;}if(web!=null){web.Dispose();web=null;}peerPort.Dispose();}}if(outcome!=null && !File.Exists(Path.Combine(RunDirectory,"easy-outcome.json")))J.Write(Path.Combine(RunDirectory,"easy-outcome.json"),outcome);}
    }
}

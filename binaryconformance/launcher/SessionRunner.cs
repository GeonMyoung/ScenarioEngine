using SharedWebTest;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace BinaryEasy {
    public sealed class Settings {
        public static string RuntimeDirectory;
        public Dictionary<string,object> Tester,Peer,Effective;
        public List<string> Tests;public bool MultiTim;public int Port;public string DataState;
        public static string Quote(string value){var result=new System.Text.StringBuilder("\"");int slashes=0;foreach(char c in value??""){if(c=='\\'){slashes++;continue;}if(c=='"')result.Append('\\',slashes*2+1).Append(c);else result.Append('\\',slashes).Append(c);slashes=0;}result.Append('\\',slashes*2).Append('"');return result.ToString();}
        public static Dictionary<string,object> Inspect(Scenario scenario,Dictionary<string,object> data){
            var file=Path.Combine(Path.GetTempPath(),"binary-easy-config-"+Guid.NewGuid().ToString("N")+".json");
            try{J.Write(file,data);var info=new System.Diagnostics.ProcessStartInfo(Path.Combine(RuntimeDirectory,"BinaryConformanceCli.exe"),"--operation inspect --case "+Quote(scenario.@case)+" --config "+Quote(file)){UseShellExecute=false,CreateNoWindow=true,WindowStyle=System.Diagnostics.ProcessWindowStyle.Hidden,RedirectStandardOutput=true,RedirectStandardError=true,StandardOutputEncoding=System.Text.Encoding.UTF8,StandardErrorEncoding=System.Text.Encoding.UTF8};
                using(var process=System.Diagnostics.Process.Start(info)){var output=process.StandardOutput.ReadToEndAsync();var error=process.StandardError.ReadToEndAsync();if(!process.WaitForExit(10000)){process.Kill();throw new IOException("설정 검사 제한시간을 초과했습니다.");}var text=output.GetAwaiter().GetResult();var why=error.GetAwaiter().GetResult();if(process.ExitCode!=0)throw new InvalidOperationException(String.IsNullOrWhiteSpace(why)?"입력값을 확인하세요.":why.Trim());return J.Decode<Dictionary<string,object>>(text);}
            }finally{if(File.Exists(file))File.Delete(file);}
        }
        public static Settings Create(Scenario s,Dictionary<string,object> input,List<string> keys,bool unused){
            var data=J.Decode<Dictionary<string,object>>(J.Encode(input));var tests=s.tests.Select(t=>t.key).Where(keys.Contains).ToList();
            if(tests.Count==0 || keys.Any(k=>!s.tests.Any(t=>t.key==k)))throw new InvalidOperationException("상세시험을 한 개 이상 선택하세요.");
            foreach(var t in s.tests)data["test_"+t.key]=tests.Contains(t.key);
            var effective=Inspect(s,data);int port;
            if(J.Text(effective,s.provider?"sut_ip":"bind_ip")!="127.0.0.1")throw new InvalidOperationException("같은 PC의 상대 프로그램을 사용하도록 IPv4 주소를 127.0.0.1로 입력하세요.");
            port=(int)J.Number(effective,"tcp_port");
            return new Settings{Tester=data,Peer=effective,Effective=effective,Tests=tests,MultiTim=false,Port=port,DataState="binary"};
        }
    }
    public sealed class Runner : IDisposable {
        readonly string bundle;readonly Action<Notice> notify;readonly bool localTest;
        volatile bool stopping,started,disposed;Controller controller;OwnedProcess engine,sut;WebFormLink web;
        bool multiTim;long previousSetupIndex;Task<Outcome> monitor;
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
        public Runner(string root,Action<Notice> handler,bool local=false){bundle=Path.GetFullPath(root);Settings.RuntimeDirectory=Path.Combine(bundle,"runtime");notify=handler;localTest=local;}
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
            RunDirectory=Path.Combine(bundle,"runs",DateTime.Now.ToString("yyMMdd-HHmmss-fff")+"-"+scenario.id+"-"+Guid.NewGuid().ToString("N").Substring(0,6));
            var longest=scenario.tests.OrderByDescending(t=>t.key.Length).First().key;
            if(Path.Combine(RunDirectory,"binary-results",new string('x',24),"test-data-test_"+longest+".jsonl").Length>=260)throw new InvalidOperationException("기록을 저장할 폴더 경로가 너무 깁니다. 묶음을 C:\\TCP-Test처럼 짧은 경로로 옮겨 실행하세요.");
            Directory.CreateDirectory(RunDirectory);
            outcome=new Outcome{ScenarioId=scenario.id,Channel=Endpoint.Channel(agent),RunDirectory=RunDirectory,Tests=new List<string>(),Verdict="NOT_RUN"};SaveSession();
            try{web=new WebFormLink(Endpoint.Channel(agent),J.Read(Path.Combine(bundle,"extension-id.txt")).Trim());web.Event=WebEvent;J.Write(Path.Combine(RunDirectory,"web-bridge.json"),new {channel=Endpoint.Channel(agent),port=web.Port,extensionId=J.Read(Path.Combine(bundle,"extension-id.txt")).Trim()});
                Tell("stage","Chrome 연결 확장을 확인하고 있습니다. 자체 시험 탭을 열어주세요.");await Wait(()=>web.BrowserReady,15,"Chrome 연결 확장이 응답하지 않습니다. 표준적합성시험 웹 연결 확장을 켜고 자체 시험 탭을 새로 연 뒤 시도하세요.");
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
            settings.Tester["tcp_port"]=port;
            var updated=Settings.Create(scenario,settings.Tester,settings.Tests,settings.MultiTim);settings.Tester=updated.Tester;settings.Peer=updated.Peer;settings.Effective=updated.Effective;settings.Port=updated.Port;
            Tell("stage","포트 "+before+"가 사용 중이어서 "+port+"로 조정합니다. 변경값을 웹 환경설정에 표시합니다.");
        }
        Settings FromWeb(Dictionary<string,object> data){var values=J.Map(J.Get(data,"values"));var keys=scenario.tests.Where(t=>J.Get(values,"test_"+t.key) is bool && (bool)values["test_"+t.key]).Select(t=>t.key).ToList();return Settings.Create(scenario,values,keys,multiTim && keys.Contains("normal_tim"));}
        async Task<object> WebEvent(string kind,Dictionary<string,object> data){
            if(!Connected)throw new InvalidOperationException("시험 엔진 연결을 기다려주세요.");
            if(kind=="web-dirty"){Prepared=false;Tell("web-editing","웹 입력값이 변경됐습니다. 설정을 다시 적용하세요.");return null;}
            if(kind=="before-setup"){if(started)throw new InvalidOperationException("시험 실행 중에는 설정할 수 없습니다.");Prepared=false;previousSetupIndex=0;try{previousSetupIndex=J.Number(J.Map(J.Decode<object>(J.Read(Path.Combine(RunDirectory,"binary-selection.json")))),"testIdx");}catch(IOException){}Tell("web-editing","웹 환경설정을 확인하고 있습니다.");ReservePort(FromWeb(data),false);return null;}
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
            var actual=J.Map(J.Decode<object>(J.Read(Path.Combine(RunDirectory,"binary-selection.json"))));
            if(J.Number(actual,"testIdx")<=previousSetupIndex)return false;
            if(!(J.Get(actual,"valid") is bool) || !(bool)actual["valid"])return false;
            if(J.Text(actual,"case")!=scenario.@case || J.Number(actual,"processId")!=engine.Id)throw new InvalidOperationException("선택한 시험과 실제 웹 회차가 다릅니다. 같은 시험의 새 주소를 복사하세요.");
            if(!J.List(J.Get(actual,"tests")).Select(Convert.ToString).SequenceEqual(settings.Tests.Select(k=>"test_"+k)))return false;
            // Engine echoes the applied configuration, including changed values with identical selection.
            var actualConfig=J.Map(J.Get(actual,"configuration"));
            var effective=J.Map(J.Get(actual,"effectiveConfiguration"));return settings.Tester.All(p=>actualConfig.ContainsKey(p.Key) && Convert.ToString(actualConfig[p.Key])==Convert.ToString(p.Value)) && settings.Effective.All(p=>effective.ContainsKey(p.Key) && Convert.ToString(effective[p.Key])==Convert.ToString(p.Value));
        }catch(IOException){return false;}catch(ArgumentException){return false;}}
        public async Task<Outcome> Start(){
            if(!Prepared || applied==null)throw new InvalidOperationException("환경설정을 먼저 적용하세요. 변경한 값이 있다면 다시 적용해야 합니다.");
            try{await web.Command("start",new {});if(monitor==null)throw new InvalidOperationException("웹 시험 시작을 확인하지 못했습니다.");return await monitor;}catch(Exception e){Error(e);Dispose();throw;}
        }
        OwnedProcess StartPeer(){
            var args=new[]{"-E","-s","-B","-X","utf8",Path.Combine(bundle,"runtime","emulator","signal_sut.py"),"--role",scenario.provider?"provider":"receiver","--config",Path.Combine(RunDirectory,"sut-config.json"),"--run-manifest",Path.Combine(RunDirectory,"binary-run.json"),"--output",Path.Combine(RunDirectory,"sut")};
            return new OwnedProcess(Path.Combine(bundle,"runtime","python","python.exe"),String.Join(" ",args.Select(Settings.Quote)),RunDirectory,"sut");
        }
        async Task PrepareWebStart(){
            if(started || !Prepared || applied==null)throw new InvalidOperationException("변경한 환경설정을 웹에 적용한 뒤 시작하세요.");
            Check();if(!SelectionMatches(applied)){Prepared=false;throw new InvalidOperationException("적용 설정이 변경됐습니다. 환경설정을 다시 적용하세요.");}
            Prepared=false;
            try{
                if(Ports.ListenOwner(applied.Port)!=0)throw new InvalidOperationException("입력한 포트를 다른 프로그램이 사용 중입니다. 사용 가능한 포트를 선택해 다시 적용하세요.");
                if(scenario.provider){Tell("stage","웹 시험 시작 전에 시험 대상을 준비합니다.");sut=StartPeer();await Wait(()=>{if(sut.Exited)throw new IOException("시험 대상 준비에 실패했습니다.");return Ports.ListenOwner(applied.Port)==sut.Id;},10,"시험 대상의 수신 대기를 확인하지 못했습니다.");}
                Check();started=true;Tell("web-starting","웹의 시험 시작 요청을 진행합니다.");monitor=Observe();
            }catch(Exception e){Error(e);Dispose();Tell("run-finished",outcome.Verdict);throw;}
        }
        async Task<Outcome> Observe(){
            try{
                await Wait(()=>began.Task.IsCompleted,15,"웹에서 시험 시작 명령을 받지 못했습니다.");
                if(!scenario.provider){await Wait(()=>Ports.ListenOwner(applied.Port)==engine.Id,10,"시험 시스템의 접속 대기를 확인하지 못했습니다.");sut=StartPeer();}
                var e=applied.Effective;var seconds=600.0+applied.Tests.Count*J.Number(e,"repetitions")*(J.Number(e,"socket_timeout_ms")+J.Number(e,"initial_limit_ms")+J.Number(e,"change_delay_ms")+J.Number(e,"period_ms"))/1000.0+J.Number(e,"heartbeat_samples")*J.Number(e,"heartbeat_period_ms")/1000.0;var deadline=DateTime.UtcNow.AddSeconds(seconds);DateTime? stopDeadline=null;
                while(!finished.Task.IsCompleted){if(stopping){if(stopDeadline==null)stopDeadline=DateTime.UtcNow.AddSeconds(8);if(DateTime.UtcNow>=stopDeadline.Value)throw new OperationCanceledException();}else Check();if(DateTime.UtcNow>deadline)throw new IOException("시험 대기 시간을 초과했습니다. 실행 기록을 확인하세요.");await Task.Delay(100);}
                var reports=Directory.GetFiles(Path.Combine(RunDirectory,"binary-results"),"result.json",SearchOption.AllDirectories);if(reports.Length!=1)throw new IOException("최종 결과 파일을 확인하지 못했습니다.");
                outcome.Report=J.Decode<Dictionary<string,object>>(J.Read(reports[0]));if(J.Text(outcome.Report,"case")!=scenario.@case)throw new IOException("결과의 시험 구성이 일치하지 않습니다.");
                outcome.Verdict=J.Text(outcome.Report,"automaticVerdict");
                if(outcome.Verdict=="SUCCESS" && sut!=null){await Wait(()=>sut.Exited,8,"상대 프로그램의 완료 기록을 확인하지 못했습니다.");if(sut.Process.ExitCode!=0)throw new IOException("상대 프로그램이 정상적으로 마무리되지 않았습니다. 기록 폴더를 확인하세요.");}
                J.Write(Path.Combine(RunDirectory,"easy-outcome.json"),outcome);
            }catch(OperationCanceledException){outcome.Verdict="STOPPED";J.Write(Path.Combine(RunDirectory,"easy-outcome.json"),outcome);}
            catch(Exception e){Error(e);}finally{if(RunDirectory!=null){try{InterfaceLogs.UserReport.Write(RunDirectory,scenario.title,outcome.Verdict);}catch(Exception reportError){File.WriteAllText(Path.Combine(RunDirectory,"user-report-error.txt"),reportError.ToString());}}Dispose();}Tell("run-finished",outcome.Verdict);return outcome;
        }
        public async Task<Outcome> WaitForWebStart(){await Wait(()=>monitor!=null,900,"웹에서 시험을 시작하지 않아 연결을 종료합니다.");return await monitor;}
        public async Task Stop(){Prepared=false;if(controller!=null && started){Tell("stage","웹의 종료 버튼으로 시험을 중지합니다.");bool fallback=false;try{await web.Command("stop",new {},7000);}catch{fallback=true;}if(fallback){stopping=true;try{if(controller!=null)await controller.Request("STOP",null,5000);}catch{}}}else stopping=true;}
        void Error(Exception e){if(RunDirectory!=null){outcome.Verdict="ERROR";J.Write(Path.Combine(RunDirectory,"easy-outcome.json"),outcome);File.WriteAllText(Path.Combine(RunDirectory,"easy-error.txt"),e.ToString());}Tell("error",InterfaceLogs.UserReport.PublicError(e));}
        public void Dispose(){if(disposed)return;disposed=true;Prepared=false;Connected=false;try{if(sut!=null){sut.Dispose();sut=null;}}finally{try{if(engine!=null){engine.Dispose();engine=null;}}finally{if(controller!=null){controller.Dispose();controller=null;}if(web!=null){web.Dispose();web=null;}peerPort.Dispose();}}if(outcome!=null && !File.Exists(Path.Combine(RunDirectory,"easy-outcome.json")))J.Write(Path.Combine(RunDirectory,"easy-outcome.json"),outcome);}
    }
}

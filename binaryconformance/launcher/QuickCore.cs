using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Security;
using System.Net.Sockets;
using System.Net.WebSockets;
using System.Runtime.InteropServices;
using System.Security.Cryptography;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;
using System.Web.Script.Serialization;

namespace BinaryEasy {
    public static class J {
        static JavaScriptSerializer Serializer() { return new JavaScriptSerializer { MaxJsonLength=33554432, RecursionLimit=128 }; }
        public static string Encode(object value) { return Serializer().Serialize(value); }
        public static T Decode<T>(string value) { return Serializer().Deserialize<T>(value); }
        public static Dictionary<string,object> Map(object value) { return value as Dictionary<string,object> ?? new Dictionary<string,object>(); }
        public static object Get(Dictionary<string,object> value,string key) { object result;return value.TryGetValue(key,out result)?result:null; }
        public static string Text(Dictionary<string,object> value,string key) { return Convert.ToString(Get(value,key)); }
        public static long Number(Dictionary<string,object> value,string key) { return Convert.ToInt64(Get(value,key)??0); }
        public static List<object> List(object value) { var result=new List<object>();if(value is IEnumerable && !(value is string))foreach(var item in (IEnumerable)value)result.Add(item);return result; }
        public static string Read(string path) { using(var f=new FileStream(path,FileMode.Open,FileAccess.Read,FileShare.ReadWrite))using(var r=new StreamReader(f,Encoding.UTF8,true))return r.ReadToEnd(); }
        public static void Write(string path,object value) { var tmp=path+".tmp";File.WriteAllText(tmp,Encode(value),new UTF8Encoding(false));if(File.Exists(path))File.Replace(tmp,path,null);else File.Move(tmp,path); }
        public static string Hash(string path) { using(var sha=SHA256.Create())using(var f=File.OpenRead(path))return BitConverter.ToString(sha.ComputeHash(f)).Replace("-","").ToLowerInvariant(); }
    }
    public class InputField { public string name,label,type; }
    public class TestItem { public string key,label,description,expected; }
    public class Scenario {
        public int id,port;public string title,category,@case,url,testerSystem,targetSystem,testerRole,targetRole,profile,sutRole;
        public string family;public List<InputField> fields;public bool provider;public List<TestItem> tests;public Dictionary<string,object> tester,sut;
        public override string ToString() { int at=title.IndexOf(" : ",StringComparison.Ordinal);return id+" · "+(at>=0?title.Substring(at+3):title); }
    }
    public class Catalog { public string version;public List<Scenario> scenarios; }
    public class Notice {
        public string Kind,Text,TestName,State,RunDirectory;
        public Dictionary<string,object> Configuration;public List<string> Tests;
        public Notice(string kind,string text) { Kind=kind;Text=text; }
    }
    public class Outcome {
        public int ScenarioId;public string Channel,RunDirectory,Verdict;public List<string> Tests;
        public Dictionary<string,object> Report;
    }
    public static class Endpoint {
        public const string Host="106.250.189.37";
        // Exact leaf identity of the existing test platform. No OS trust settings are changed.
        public const string CertificateSha256="7e216348e824b9f402fa9a7a725762c97d4a6121436b43a126c7abec77cfb788";
        public static Uri Agent(string input,bool localTest) {
            input=(input??"").Trim();if(input.StartsWith("scts://",StringComparison.OrdinalIgnoreCase))input=input.Substring(7);
            Uri uri;
            if(!Uri.TryCreate(input,UriKind.Absolute,out uri) || uri.UserInfo.Length>0 || uri.Query.Length>0 || uri.Fragment.Length>0 ||
                !Regex.IsMatch(uri.AbsolutePath,@"^/ws/test/agent/[0-9]+/$"))throw new InvalidOperationException("웹의 ‘Agent 접속 URL 복사’로 얻은 새 주소를 붙여 넣어주세요.");
            bool production=uri.Scheme=="wss" && uri.Host==Host && uri.Port==8443;
            IPAddress ip;bool loopback=localTest && uri.Scheme=="ws" && IPAddress.TryParse(uri.Host,out ip) && IPAddress.IsLoopback(ip);
            if(!production && !loopback)throw new InvalidOperationException("이 실행기는 지정된 시험 플랫폼의 접속 주소만 사용합니다.");
            return uri;
        }
        public static void ConfigureTls(Uri target) {
            ServicePointManager.SecurityProtocol=SecurityProtocolType.Tls12;
            ServicePointManager.ServerCertificateValidationCallback=(sender,cert,chain,errors)=> {
                if(errors==SslPolicyErrors.None)return true;
                if(target.Scheme!="wss" || target.Host!=Host || target.Port!=8443 || cert==null)return false;
                using(var sha=SHA256.Create())return BitConverter.ToString(sha.ComputeHash(cert.GetRawCertData())).Replace("-","").ToLowerInvariant()==CertificateSha256;
            };
        }
        public static string Channel(Uri agent) { return agent.AbsolutePath.Split('/')[4]; }
        public static string Report(string channel) { return "https://"+Host+":8443/test/report/"+channel; }
    }
    public sealed class Controller : IDisposable {
        readonly ClientWebSocket socket=new ClientWebSocket();readonly SemaphoreSlim sendLock=new SemaphoreSlim(1);
        readonly CancellationTokenSource lifetime=new CancellationTokenSource();readonly object gate=new object();
        readonly Dictionary<long,TaskCompletionSource<Dictionary<string,object>>> pending=new Dictionary<long,TaskCompletionSource<Dictionary<string,object>>>();
        readonly StreamWriter journal;long sequence=700000;Task receiver;
        public Action<Dictionary<string,object>> Message;
        public Controller(string path) { journal=new StreamWriter(new FileStream(path,FileMode.CreateNew,FileAccess.Write,FileShare.Read),new UTF8Encoding(false));journal.AutoFlush=true; }
        void Record(string direction,string text) { lock(gate)journal.WriteLine(J.Encode(new {time=DateTimeOffset.Now.ToString("o"),direction=direction,message=J.Decode<object>(text)})); }
        public async Task Connect(Uri agent) {
            Endpoint.ConfigureTls(agent);socket.Options.KeepAliveInterval=TimeSpan.FromSeconds(20);
            var uri=new Uri(agent.AbsoluteUri.Replace("/ws/test/agent/","/ws/test/controller/"));
            using(var deadline=new CancellationTokenSource(15000))await socket.ConnectAsync(uri,deadline.Token);
            receiver=Receive();
            var response=await Request("DESCRIBE","Controller",15000);
            var details=J.Map(J.Get(J.Map(J.Get(response,"result")),"data"));
            if(J.List(J.Get(details,"currConnList")).Any(x=>J.Text(J.Map(x),"clientType")=="Agent"))throw new InvalidOperationException("이 회차에는 이미 시험 엔진이 연결되어 있습니다. 웹에서 새 회차를 열어주세요.");
        }
        async Task Send(object value) {
            var text=J.Encode(value);var bytes=Encoding.UTF8.GetBytes(text);
            await sendLock.WaitAsync();try { await socket.SendAsync(new ArraySegment<byte>(bytes),WebSocketMessageType.Text,true,lifetime.Token);Record("TX",text); }finally{sendLock.Release();}
        }
        public async Task<Dictionary<string,object>> Request(string method,object data=null,int timeout=15000) {
            long seq=Interlocked.Increment(ref sequence);var done=new TaskCompletionSource<Dictionary<string,object>>(TaskCreationOptions.RunContinuationsAsynchronously);
            lock(gate)pending.Add(seq,done);
            try {
                var request=new Dictionary<string,object>{{"method",method},{"seq",seq}};if(data!=null)request["data"]=data;
                await Send(request);
                if(await Task.WhenAny(done.Task,Task.Delay(timeout))!=done.Task)throw new InvalidOperationException("플랫폼의 ‘"+method+"’ 응답을 받지 못했습니다. 연결 상태를 확인하세요.");
                var response=await done.Task;var result=J.Map(J.Get(response,"result"));
                if(J.Text(result,"code")!="200" && J.Text(result,"code")!="OK")throw new InvalidOperationException("플랫폼에서 요청을 처리하지 못했습니다: "+J.Text(result,"reason"));
                return response;
            }finally{lock(gate)pending.Remove(seq);}
        }
        async Task Receive() {
            Exception failure=null;
            try {
                var buffer=new byte[32768];
                while(!lifetime.IsCancellationRequested) {
                    using(var stream=new MemoryStream()) {
                        WebSocketReceiveResult frame;
                        do { frame=await socket.ReceiveAsync(new ArraySegment<byte>(buffer),lifetime.Token);if(frame.MessageType==WebSocketMessageType.Close)throw new IOException("시험 플랫폼 연결이 종료됐습니다.");stream.Write(buffer,0,frame.Count);if(stream.Length>33554432)throw new IOException("플랫폼 메시지 크기가 처리 범위를 초과했습니다."); }while(!frame.EndOfMessage);
                        var text=Encoding.UTF8.GetString(stream.ToArray());Record("RX",text);var message=J.Decode<Dictionary<string,object>>(text);
                        if(message.ContainsKey("result")) { TaskCompletionSource<Dictionary<string,object>> done;lock(gate){if(pending.TryGetValue(J.Number(message,"seq"),out done))done.TrySetResult(message);} }
                        else {
                            var handler=Message;if(handler!=null)handler(message);
                            if(message.ContainsKey("seq"))await Send(new {seq=J.Number(message,"seq"),result=new {code=200,reason="OK",data=(object)null}});
                        }
                    }
                }
            }catch(Exception error){failure=error;}finally{
                lock(gate)foreach(var item in pending.Values)item.TrySetException(failure??new IOException("연결이 종료됐습니다."));
                if(!lifetime.IsCancellationRequested && Message!=null)Message(new Dictionary<string,object>{{"localError",failure==null?"연결 종료":failure.Message}});
            }
        }
        public void Dispose() { lifetime.Cancel();socket.Abort();try{if(receiver!=null)receiver.Wait(2000);}catch{}socket.Dispose();lock(gate)journal.Dispose(); }
    }
    public sealed class OwnedProcess : IDisposable {
        public readonly Process Process;readonly long started;readonly string executable;readonly List<Task> copies=new List<Task>();readonly List<Stream> files=new List<Stream>();
        public int Id {get{return Process.Id;}}
        public bool Exited {get{try{return Process.HasExited;}catch{return true;}}}
        public OwnedProcess(string exe,string args,string directory,string stem,Dictionary<string,string> environment=null) {
            executable=Path.GetFullPath(exe);
            Process=new Process { StartInfo=new ProcessStartInfo(executable,args){WorkingDirectory=directory,UseShellExecute=false,CreateNoWindow=true,WindowStyle=ProcessWindowStyle.Hidden,RedirectStandardOutput=true,RedirectStandardError=true} };
            if(environment!=null)foreach(var pair in environment)Process.StartInfo.EnvironmentVariables[pair.Key]=pair.Value;
            if(!Process.Start())throw new InvalidOperationException("실행 파일을 시작하지 못했습니다.");started=Process.StartTime.ToUniversalTime().Ticks;
            foreach(var pair in new[]{Tuple.Create(Process.StandardOutput.BaseStream,stem+"-stdout.log"),Tuple.Create(Process.StandardError.BaseStream,stem+"-stderr.log")}) {
                var file=new FileStream(Path.Combine(directory,pair.Item2),FileMode.CreateNew,FileAccess.Write,FileShare.Read);files.Add(file);copies.Add(pair.Item1.CopyToAsync(file));
            }
            J.Write(Path.Combine(directory,stem+"-process.json"),new {pid=Id,executable=executable,startTimeTicks=started.ToString(),sha256=J.Hash(executable)});
        }
        public void Dispose() {
            try {
                if(!Process.HasExited && Process.StartTime.ToUniversalTime().Ticks==started && String.Equals(Process.MainModule.FileName,executable,StringComparison.OrdinalIgnoreCase)){Process.Kill();Process.WaitForExit(3000);}
            }finally{try{Task.WaitAll(copies.ToArray(),3000);}catch{}foreach(var file in files)file.Dispose();Process.Dispose();}
        }
    }
    public static class Ports {
        [DllImport("iphlpapi.dll",SetLastError=true)]static extern uint GetExtendedTcpTable(IntPtr table,ref int size,bool sorted,int family,int tableClass,uint reserved);
        public static int ListenOwner(int port) {
            int size=0;GetExtendedTcpTable(IntPtr.Zero,ref size,false,2,5,0);if(size<=4)return 0;var table=Marshal.AllocHGlobal(size);
            try { if(GetExtendedTcpTable(table,ref size,false,2,5,0)!=0)return 0;int count=Marshal.ReadInt32(table);for(int i=0;i<count;i++){var row=IntPtr.Add(table,4+i*24);int raw=Marshal.ReadInt32(row,8);int actual=((raw&255)<<8)|((raw>>8)&255);if(Marshal.ReadInt32(row)==2 && actual==port)return Marshal.ReadInt32(row,20);}return 0; }finally{Marshal.FreeHGlobal(table);}
        }
        public static int Free(int start) {
            for(int port=start;port<start+1000 && port<49152;port++) { var listener=new TcpListener(IPAddress.Loopback,port);try{listener.ExclusiveAddressUse=true;listener.Start();return port;}catch(SocketException){}finally{listener.Stop();} }
            throw new InvalidOperationException("시험에 사용할 빈 포트를 찾지 못했습니다.");
        }
    }
}

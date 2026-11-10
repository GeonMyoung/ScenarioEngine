using System;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace SharedWebTest {
    static class BridgeJson {
        static System.Web.Script.Serialization.JavaScriptSerializer Serializer(){return new System.Web.Script.Serialization.JavaScriptSerializer{MaxJsonLength=1048576,RecursionLimit=128};}
        public static T Decode<T>(string s){return Serializer().Deserialize<T>(s);}
        public static string Encode(object v){return Serializer().Serialize(v);}
        public static Dictionary<string,object> Map(object v){return v as Dictionary<string,object>??new Dictionary<string,object>();}
        public static object Get(Dictionary<string,object> d,string k){object v;return d.TryGetValue(k,out v)?v:null;}
        public static string Text(Dictionary<string,object> d,string k){return Convert.ToString(Get(d,k));}
    }
    public sealed class WebFormLink : IDisposable {
        public const int FirstPort=43763,LastPort=43778;
        readonly TcpListener listener;readonly ResourceClaim channelClaim;
        public int Port {get;private set;}
        readonly string channel,extensionId,token=Guid.NewGuid().ToString("N")+Guid.NewGuid().ToString("N");
        readonly object gate=new object();bool disposed;string browserClient;
        Dictionary<string,object> command;TaskCompletionSource<Dictionary<string,object>> reply;
        DateTime lastSeen=DateTime.MinValue;
        public Func<string,Dictionary<string,object>,Task<object>> Event;
        public bool BrowserReady {get{lock(gate)return browserClient!=null && (DateTime.UtcNow-lastSeen).TotalSeconds<6;}}
        public WebFormLink(string channel,string extensionId){
            if(!System.Text.RegularExpressions.Regex.IsMatch(channel,@"^[0-9]{1,18}$"))throw new InvalidOperationException("시험 회차가 올바르지 않습니다.");
            this.channel=channel;this.extensionId=extensionId;
            try{channelClaim=ResourceClaim.Take("channel-"+channel);}catch(IOException){throw new InvalidOperationException("이 회차는 다른 실행기에 연결되어 있습니다. 별도의 새 시험 회차를 사용하세요.");}
            try{for(int port=FirstPort;port<=LastPort;port++){var candidate=new TcpListener(IPAddress.Loopback,port);candidate.ExclusiveAddressUse=true;try{candidate.Start();listener=candidate;Port=port;break;}catch(SocketException){candidate.Stop();}}
                if(listener==null)throw new InvalidOperationException("동시에 연결 가능한 16개 회차를 모두 사용 중입니다. 완료한 실행기의 연결을 해제하세요.");Accept();
            }catch{channelClaim.Dispose();throw;}
        }
        async void Accept(){while(!disposed){try{var client=await listener.AcceptTcpClientAsync();ThreadPool.QueueUserWorkItem(_=>Serve(client));}catch{if(!disposed)Dispose();}}}
        async void Serve(TcpClient client){using(client){try{
            client.ReceiveTimeout=5000;client.SendTimeout=5000;var stream=client.GetStream();
            var header=new List<byte>();while(header.Count<8192){int b=stream.ReadByte();if(b<0)return;header.Add((byte)b);int n=header.Count;if(n>=4 && header[n-4]==13 && header[n-3]==10 && header[n-2]==13 && header[n-1]==10)break;}
            string head=Encoding.ASCII.GetString(header.ToArray());var lines=head.Split(new[]{"\r\n"},StringSplitOptions.None);var headers=new Dictionary<string,string>(StringComparer.OrdinalIgnoreCase);
            for(int i=1;i<lines.Length;i++){int colon=lines[i].IndexOf(':');if(colon>0)headers[lines[i].Substring(0,colon)]=lines[i].Substring(colon+1).Trim();}
            string origin;headers.TryGetValue("Origin",out origin);
            if(lines[0].StartsWith("OPTIONS /bridge HTTP/1.") && origin=="chrome-extension://"+extensionId){var allow=Encoding.ASCII.GetBytes("HTTP/1.1 204 No Content\r\nAccess-Control-Allow-Origin: "+origin+"\r\nAccess-Control-Allow-Methods: POST\r\nAccess-Control-Allow-Headers: content-type,x-rest-extension\r\nConnection: close\r\nContent-Length: 0\r\n\r\n");await stream.WriteAsync(allow,0,allow.Length);return;}
            if(!lines[0].StartsWith("POST /bridge HTTP/1.") || (origin!=null && origin!="chrome-extension://"+extensionId) || !headers.ContainsKey("X-Rest-Extension") || headers["X-Rest-Extension"]!=extensionId){await Respond(stream,403,new {error="연결 확장만 사용할 수 있습니다."});return;}
            int size;if(!headers.ContainsKey("Content-Length") || !int.TryParse(headers["Content-Length"],out size) || size<2 || size>1048576){await Respond(stream,400,new {error="Invalid body"});return;}
            byte[] bytes=new byte[size];int offset=0;while(offset<size){int n=await stream.ReadAsync(bytes,offset,size-offset);if(n==0)return;offset+=n;}
            var request=BridgeJson.Decode<Dictionary<string,object>>(Encoding.UTF8.GetString(bytes));
            if(BridgeJson.Text(request,"channel")!=channel){await Respond(stream,200,new {linked=false});return;}
            string kind=BridgeJson.Text(request,"kind"),clientId=BridgeJson.Text(request,"clientId");
            if(kind=="hello"){
                if(String.IsNullOrEmpty(clientId)||clientId.Length>256){await Respond(stream,400,new {error="시험 탭 식별값을 확인하세요."});return;}
                lock(gate){if(browserClient==null)browserClient=clientId;}
                if(String.IsNullOrEmpty(clientId) || browserClient!=clientId){await Respond(stream,409,new {error="다른 시험 탭이 연결되어 있습니다."});return;}
                lock(gate)lastSeen=DateTime.UtcNow;await Respond(stream,200,new {linked=true,token=token});return;
            }
            if(BridgeJson.Text(request,"token")!=token || clientId!=browserClient){await Respond(stream,403,new {error="연결이 만료됐습니다. 실행기를 다시 연결하세요."});return;}
            lock(gate)lastSeen=DateTime.UtcNow;
            if(kind=="poll"){object pending;lock(gate)pending=command;await Respond(stream,200,new {linked=true,command=pending});return;}
            if(kind=="result"){
                var data=BridgeJson.Map(BridgeJson.Get(request,"data"));lock(gate){if(command!=null && BridgeJson.Text(data,"id")==BridgeJson.Text(command,"id")){reply.TrySetResult(data);command=null;}}
                await Respond(stream,200,new {ok=true});return;
            }
            var handler=Event;if(handler==null)throw new InvalidOperationException("시험 연결을 준비하고 있습니다.");
            var response=await handler(kind,BridgeJson.Map(BridgeJson.Get(request,"data")));await Respond(stream,200,new {ok=true,data=response});
        }catch(Exception e){try{Respond(client.GetStream(),400,new {error=e.Message}).GetAwaiter().GetResult();}catch{}}}}
        static async Task Respond(Stream stream,int code,object data){byte[] body=Encoding.UTF8.GetBytes(BridgeJson.Encode(data));byte[] head=Encoding.ASCII.GetBytes("HTTP/1.1 "+code+" Response\r\nContent-Type: application/json; charset=utf-8\r\nCache-Control: no-store\r\nConnection: close\r\nContent-Length: "+body.Length+"\r\n\r\n");await stream.WriteAsync(head,0,head.Length);await stream.WriteAsync(body,0,body.Length);}
        public async Task<Dictionary<string,object>> Command(string kind,object data,int timeout=90000){
            Task<Dictionary<string,object>> wait;
            lock(gate){if(command!=null)throw new InvalidOperationException("웹 화면의 이전 작업이 아직 진행 중입니다.");reply=new TaskCompletionSource<Dictionary<string,object>>(TaskCreationOptions.RunContinuationsAsynchronously);command=new Dictionary<string,object>{{"id",Guid.NewGuid().ToString("N")},{"kind",kind},{"data",data}};wait=reply.Task;}
            if(await Task.WhenAny(wait,Task.Delay(timeout))!=wait){lock(gate)command=null;throw new InvalidOperationException("웹 연결 확장의 응답이 없습니다. Chrome의 자체 시험 탭과 확장 연결 상태를 확인하세요.");}
            var result=await wait;if(BridgeJson.Text(result,"error").Length>0)throw new InvalidOperationException(BridgeJson.Text(result,"error"));return result;
        }
        public void Dispose(){if(disposed)return;disposed=true;listener.Stop();channelClaim.Dispose();lock(gate){command=null;if(reply!=null)reply.TrySetException(new IOException("실행기 연결 종료"));}}
    }
}

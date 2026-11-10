using System;
using System.IO;
using System.Net;
using System.Net.Sockets;

namespace SharedWebTest {
    // File sharing locks are process scoped and released by Windows on a crash.
    // They can be disposed from async continuations on a different thread.
    public sealed class ResourceClaim : IDisposable {
        FileStream handle;
        ResourceClaim(FileStream file){handle=file;}
        public static ResourceClaim Take(string name){
            if(System.Text.RegularExpressions.Regex.IsMatch(name,@"^[a-z0-9-]{1,64}$")==false)throw new ArgumentException("Invalid claim name");
            var root=Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData),"SctsWebTest","claims");Directory.CreateDirectory(root);
            return new ResourceClaim(new FileStream(Path.Combine(root,name+".lock"),FileMode.OpenOrCreate,FileAccess.ReadWrite,FileShare.None));
        }
        public void Dispose(){var file=System.Threading.Interlocked.Exchange(ref handle,null);if(file!=null)file.Dispose();}
    }
    public sealed class PortReservation : IDisposable {
        ResourceClaim claim;public int Port {get;private set;}
        public void Exact(int port){
            if(claim!=null&&Port==port)return;
            ResourceClaim next=null;TcpListener probe=null;
            try{next=ResourceClaim.Take("tcp-"+port);probe=new TcpListener(IPAddress.Loopback,port);probe.ExclusiveAddressUse=true;probe.Start();}
            catch(Exception e){if(next!=null)next.Dispose();if(e is IOException||e is SocketException)throw new InvalidOperationException("포트 "+port+"를 다른 시험 또는 프로그램이 사용 중입니다. 빈 포트로 설정을 다시 적용하세요.",e);throw;}
            finally{if(probe!=null)probe.Stop();}
            if(claim!=null)claim.Dispose();claim=next;Port=port;
        }
        public int Available(int preferred,int maximum=65535){
            if(preferred<1||preferred>maximum)throw new InvalidOperationException("사용할 포트 범위를 확인하세요.");
            for(int port=preferred;port<=Math.Min(maximum,preferred+1000);port++)try{Exact(port);return port;}catch(InvalidOperationException){}
            throw new InvalidOperationException("시험에 사용할 빈 포트를 찾지 못했습니다.");
        }
        public void Dispose(){if(claim!=null){claim.Dispose();claim=null;}Port=0;}
    }
}

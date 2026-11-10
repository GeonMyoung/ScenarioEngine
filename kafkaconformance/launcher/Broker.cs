using SharedWebTest;
using System;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace KafkaEasy {
 public sealed class Broker : IDisposable {
  OwnedProcess process;readonly PortReservation controlPort=new PortReservation();public bool Exited {get{return process!=null && process.Exited;}}
  static string Property(string s){var b=new StringBuilder();foreach(char c in s.Replace('\\','/')){if(c>127)b.Append("\\u"+((int)c).ToString("x4"));else b.Append(c);}return b.ToString();}
  public static async Task<string> Command(string exe,string args,string directory,int timeout){
   var info=new System.Diagnostics.ProcessStartInfo(exe,args){WorkingDirectory=directory,UseShellExecute=false,CreateNoWindow=true,WindowStyle=System.Diagnostics.ProcessWindowStyle.Hidden,RedirectStandardOutput=true,RedirectStandardError=true,StandardOutputEncoding=Encoding.UTF8,StandardErrorEncoding=Encoding.UTF8};
   using(var p=System.Diagnostics.Process.Start(info)){var text=p.StandardOutput.ReadToEndAsync();var err=p.StandardError.ReadToEndAsync();bool done=await Task.Run(()=>p.WaitForExit(timeout)).ConfigureAwait(false);if(!done){p.Kill();p.WaitForExit(3000);throw new IOException("준비 작업의 제한시간을 초과했습니다.");}var output=await text.ConfigureAwait(false);var why=await err.ConfigureAwait(false);if(p.ExitCode!=0)throw new IOException(String.IsNullOrWhiteSpace(why)?output:why);return output;}
  }
  public async Task Start(string bundle,string run,Settings settings){
   int port=settings.Port;if(Ports.ListenOwner(port)!=0)throw new InvalidOperationException("입력한 브로커 포트를 사용 중입니다. 빈 포트를 선택해 다시 적용하세요.");
   int control=controlPort.Available(port+1,65535);if(control==port)throw new InvalidOperationException("브로커 제어 포트 충돌");
   string root=Path.Combine(run,"broker");Directory.CreateDirectory(root);string cfg=Path.Combine(root,"server.properties");
   string properties="process.roles=broker,controller\nnode.id=143\ncontroller.quorum.voters=143@127.0.0.1:"+control+"\nlisteners=PLAINTEXT://127.0.0.1:"+port+",CONTROLLER://127.0.0.1:"+control+"\nadvertised.listeners=PLAINTEXT://127.0.0.1:"+port+"\ncontroller.listener.names=CONTROLLER\nlistener.security.protocol.map=PLAINTEXT:PLAINTEXT,CONTROLLER:PLAINTEXT\ninter.broker.listener.name=PLAINTEXT\nlog.dirs="+Property(Path.Combine(root,"data"))+"\nnum.partitions=1\noffsets.topic.num.partitions=1\nlog.segment.bytes=8388608\nlog.index.size.max.bytes=1048576\noffsets.topic.replication.factor=1\ntransaction.state.log.replication.factor=1\ntransaction.state.log.min.isr=1\ngroup.initial.rebalance.delay.ms=0\nauto.create.topics.enable=false\nlog.retention.hours=24\n";
   File.WriteAllText(cfg,properties,Encoding.ASCII);
   string runtime=Path.Combine(bundle,"runtime"),java=Path.Combine(runtime,"java","bin","java.exe");
   string args="-Xms128m -Xmx512m "+Settings.Quote("-Dlog4j.configuration="+new Uri(Path.Combine(runtime,"kafka","config","log4j.properties")).AbsoluteUri)+" "+Settings.Quote("-Dkafka.logs.dir="+Path.Combine(root,"logs"))+" -cp "+Settings.Quote(Path.Combine(runtime,"kafka","libs","*"));
   var format=await Command(java,args+" kafka.tools.StorageTool format -t G4KafkaDev20260925abcdeQ -c "+Settings.Quote(cfg),run,20000);File.WriteAllText(Path.Combine(root,"format.log"),format,Encoding.UTF8);
   process=new OwnedProcess(java,args+" kafka.Kafka "+Settings.Quote(cfg),run,"broker");
   var until=DateTime.UtcNow.AddSeconds(25);while(Ports.ListenOwner(port)!=process.Id){if(process.Exited)throw new IOException("시험용 브로커가 종료됐습니다. broker-stderr.log와 기록 폴더를 확인하세요.");if(DateTime.UtcNow>until)throw new IOException("시험용 브로커 준비 제한시간 초과");await Task.Delay(100);}
   var ready=await Command(Path.Combine(runtime,"python","python.exe"),"-E -s -B -X utf8 "+Settings.Quote(Path.Combine(runtime,"broker_admin.py"))+" --config "+Settings.Quote(Path.Combine(run,"sut-config.json")),run,20000);
   J.Write(Path.Combine(run,"broker-ready.json"),J.Decode<object>(ready));
  }
  public void Dispose(){try{if(process!=null){process.Dispose();process=null;}}finally{controlPort.Dispose();}}
 }
}

using System;
using System.IO;
using System.Text;
using System.Threading.Tasks;
namespace MqttEasy {
 public sealed class Broker : IDisposable {
  OwnedProcess process;public bool Exited {get{return process!=null&&process.Exited;}}
  public static async Task<string> Command(string exe,string args,string directory,int timeout){
   var info=new System.Diagnostics.ProcessStartInfo(exe,args){WorkingDirectory=directory,UseShellExecute=false,CreateNoWindow=true,WindowStyle=System.Diagnostics.ProcessWindowStyle.Hidden,RedirectStandardOutput=true,RedirectStandardError=true,StandardOutputEncoding=Encoding.UTF8,StandardErrorEncoding=Encoding.UTF8};
   using(var p=System.Diagnostics.Process.Start(info)){var output=p.StandardOutput.ReadToEndAsync();var error=p.StandardError.ReadToEndAsync();bool done=await Task.Run(()=>p.WaitForExit(timeout)).ConfigureAwait(false);if(!done){p.Kill();p.WaitForExit(3000);throw new IOException("준비 작업의 제한시간을 초과했습니다.");}var text=await output.ConfigureAwait(false);var why=await error.ConfigureAwait(false);if(p.ExitCode!=0)throw new IOException(String.IsNullOrWhiteSpace(why)?text:why);return text;}
  }
  public async Task Start(string bundle,string run,Settings settings){
   if(Ports.ListenOwner(settings.Port)!=0)throw new InvalidOperationException("Broker 포트가 사용 중입니다. 빈 포트로 설정을 다시 적용하세요.");
   var config=Path.Combine(run,"broker.conf");File.WriteAllText(config,"listener "+settings.Port+" 127.0.0.1\nallow_anonymous true\npersistence false\n",Encoding.ASCII);
   process=new OwnedProcess(Path.Combine(bundle,"runtime","broker","mosquitto","mosquitto.exe"),"-c "+Settings.Quote(config),run,"broker");
   var deadline=DateTime.UtcNow.AddSeconds(10);
   while(Ports.ListenOwner(settings.Port)!=process.Id){if(process.Exited)throw new IOException("시험용 Broker가 준비 전에 종료됐습니다. 상세 진단을 확인하세요.");if(DateTime.UtcNow>deadline)throw new IOException("시험용 Broker의 준비 시간이 초과됐습니다.");await Task.Delay(50);}
   J.Write(Path.Combine(run,"broker-ready.json"),new {pid=process.Id,host="127.0.0.1",port=settings.Port});
  }
  public void Dispose(){if(process!=null){process.Dispose();process=null;}}
 }
}

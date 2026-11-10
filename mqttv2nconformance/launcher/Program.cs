using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
namespace MqttEasy {
 static class Program {
  [STAThread] static int Main(string[] args){
   try{
    int verification=Array.IndexOf(args,"--verify-peer");
    if(verification>=0){if(verification+1>=args.Length || !new[]{"spat-field","period-delay","silence","tim-missing","tim-duplicate"}.Contains(args[verification+1]))throw new ArgumentException("검증용 상대 오류 종류를 확인하세요.");Runtime.VerificationFault=args[verification+1];}
    if(args.Length>0&&(args[0]=="--run"||args[0]=="--run-local"))return Headless(args,args[0]=="--run-local").GetAwaiter().GetResult();
    Application.SetUnhandledExceptionMode(UnhandledExceptionMode.ThrowException);Application.EnableVisualStyles();Application.SetCompatibleTextRenderingDefault(false);
    if(args.Length>0&&args[0]=="--render"){using(var f=new QuickForm(args[1]))f.Render(args[2],int.Parse(args[3]),int.Parse(args[4]));return 0;}
    if(args.Length>0&&args[0]=="--ui-check"){using(var f=new QuickForm(args[1]))f.CheckUi(args[2]);return 0;}
    if(args.Length>0&&args[0]=="--ui-run"){
     int code=0;using(var f=new QuickForm(args[1])){f.Shown+=async(s,e)=>{try{await f.CheckFlow(int.Parse(args[2]),args[3],args[4],args[5],args.Length>6?args[6]:"SUCCESS");}catch(Exception error){code=2;File.WriteAllText(args[5]+".error",error.ToString());}finally{f.Close();}};Application.Run(f);}return code;
    }
    Application.Run(new QuickForm(AppDomain.CurrentDomain.BaseDirectory));return 0;
   }catch(Exception e){if(args.Length>0){File.WriteAllText(Path.Combine(Path.GetTempPath(),"mqtt-easy-last-error.txt"),e.ToString());return 2;}MessageBox.Show(InterfaceLogs.UserReport.PublicError(e),"MQTT/V2N 간편시험",MessageBoxButtons.OK,MessageBoxIcon.Error);return 2;}
  }
  static async Task<int> Headless(string[] args,bool local){
   string root=Path.GetFullPath(args[1]);Settings.RuntimeDirectory=Runtime.Initialize(root);var catalog=J.Decode<Catalog>(J.Read(Path.Combine(root,"scenarios.json")));var scenario=catalog.scenarios.Single(s=>s.id==int.Parse(args[2]));
   var selected=args[3]=="all"?scenario.tests.Select(t=>t.key).ToList():args[3].Split(',').ToList();var values=Settings.Defaults(scenario);
   int configuration=Array.IndexOf(args,"--config");if(configuration>=0)foreach(var pair in J.Decode<Dictionary<string,object>>(J.Read(args[configuration+1])))values[pair.Key]=pair.Value;
   using(var runner=new Runner(root,n=>{},local)){
    await runner.Connect(scenario,args[4]);
    if(args.Contains("--staged-check")){bool blocked=false;try{await runner.Start();}catch(InvalidOperationException){blocked=true;}if(!blocked)throw new Exception("Start before settings not blocked");}
    await runner.Apply(Settings.Create(scenario,values,selected,false));
    if(args.Contains("--staged-check")){
     if(File.Exists(Path.Combine(runner.RunDirectory,"sut-process.json"))||File.Exists(Path.Combine(runner.RunDirectory,"broker-process.json")))throw new Exception("Preparation started before explicit START");
     var topic=values.Keys.First(k=>k.StartsWith("topic_"));values[topic]=Convert.ToString(values[topic])+"/reapplied";runner.Invalidate();bool blocked=false;try{await runner.Start();}catch(InvalidOperationException){blocked=true;}if(!blocked)throw new Exception("Changed settings did not block START");
     await runner.Apply(Settings.Create(scenario,values,selected,false));
    }
    if(args.Contains("--prepare-only"))return 0;
    if(args.Contains("--web-wait")){var observed=await runner.WaitForWebStart();return observed.Verdict=="SUCCESS"?0:4;}
    var run=runner.Start();int stop=Array.IndexOf(args,"--stop-after-ms");if(stop>=0){await Task.WhenAny(run,Task.Delay(int.Parse(args[stop+1])));if(!run.IsCompleted)await runner.Stop();}
    var result=await run;return result.Verdict=="SUCCESS"?0:result.Verdict=="STOPPED"?3:4;
   }
  }
 }
}

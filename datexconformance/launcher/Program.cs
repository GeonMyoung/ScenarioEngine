using System;
using System.IO;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
namespace DatexEasy {
    static class Program {
        [STAThread] static int Main(string[] args) {
            string root=AppDomain.CurrentDomain.BaseDirectory;
            try {
                if(args.Length>0 && args[0]=="--run-local")return Headless(args,true).GetAwaiter().GetResult();
                if(args.Length>0 && args[0]=="--run")return Headless(args,false).GetAwaiter().GetResult();
                if(args.Length>0 && args[0]=="--probe"){using(var c=new Controller(args[2]))c.Connect(Endpoint.Agent(args[1],false)).GetAwaiter().GetResult();return 0;}
                Application.SetUnhandledExceptionMode(UnhandledExceptionMode.ThrowException);Application.EnableVisualStyles();Application.SetCompatibleTextRenderingDefault(false);
                if(args.Length>0 && args[0]=="--ui-run-check"){int code=0;using(var f=new QuickForm(args[1],true)){f.Shown+=async(s,e)=>{try{await f.CheckFlow(args[2],args[3]);}catch(Exception error){code=2;File.WriteAllText(args[3]+".error",error.ToString());}finally{f.Close();}};Application.Run(f);}return code;}
                if(args.Length>0 && args[0]=="--render"){using(var f=new QuickForm(args[1]))f.Render(args[2],int.Parse(args[3]),int.Parse(args[4]));return 0;}
                if(args.Length>0 && args[0]=="--ui-check"){using(var f=new QuickForm(args[1]))f.CheckUi(args[2]);return 0;}
                Application.Run(new QuickForm(root));
                return 0;
            }catch(Exception error){if(args.Length>0){File.WriteAllText(Path.Combine(Path.GetTempPath(),"datex-easy-last-error.txt"),error.ToString());return 2;}MessageBox.Show("실행 준비를 마치지 못했습니다. ZIP을 새 폴더에 모두 푼 뒤 다시 실행하세요.\r\n\r\n"+error.Message,"DATEX 간편 실행",MessageBoxButtons.OK,MessageBoxIcon.Error);return 2;}
        }
        static async Task<int> Headless(string[] args,bool local){
            var root=Path.GetFullPath(args[1]);var catalog=J.Decode<Catalog>(J.Read(Path.Combine(root,"scenarios.json")));var scenario=catalog.scenarios.Single(s=>s.id==int.Parse(args[2]));
            var selected=args[3]=="all"?scenario.tests.Select(t=>t.key).ToList():args[3].Split(',').ToList();
            var values=J.Decode<System.Collections.Generic.Dictionary<string,object>>(J.Encode(scenario.tester));values["peer_port"]=values["local_port"]=Ports.Free(43000+scenario.id);values["peer_ip"]="127.0.0.1";
            int configurationIndex=Array.IndexOf(args,"--config");if(configurationIndex>=0){var custom=J.Decode<System.Collections.Generic.Dictionary<string,object>>(J.Read(args[configurationIndex+1]));foreach(var pair in custom)values[pair.Key]=pair.Value;}
            using(var runner=new Runner(root,n=>{},local)){
                await runner.Connect(scenario,args[4]);
                if(args.Contains("--staged-check")){bool blocked=false;try{await runner.Start();}catch(InvalidOperationException){blocked=true;}if(!blocked)throw new Exception("Start before SETUP was not blocked");}
                await runner.Apply(Settings.Create(scenario,values,selected,args.Contains("--multi-tim")));
                if(args.Contains("--staged-check")){
                    await Task.Delay(2000);if(File.Exists(Path.Combine(runner.RunDirectory,"sut-process.json")) || Directory.Exists(Path.Combine(runner.RunDirectory,"datex-results")))throw new Exception("Test started before explicit START");
                    values["my_domain"]="MANUAL-EDIT-TESTER";values["peer_domain"]="MANUAL-EDIT-TARGET";values["pass"]="changed-local-test-password";
                    runner.Invalidate();bool blocked=false;try{await runner.Start();}catch(InvalidOperationException){blocked=true;}if(!blocked)throw new Exception("Dirty settings did not block START");
                    await runner.Apply(Settings.Create(scenario,values,selected,args.Contains("--multi-tim")));
                    if(!runner.Prepared)throw new Exception("Reapply did not prepare the run");
                }
                if(args.Contains("--prepare-only")){await Task.Delay(2000);return 0;}
                if(args.Contains("--web-wait")){var manual=await runner.WaitForWebStart();return manual.Verdict=="SUCCESS"?0:4;}
                var job=runner.Start();int stop=Array.IndexOf(args,"--stop-after-ms");if(stop>=0){await Task.WhenAny(job,Task.Delay(int.Parse(args[stop+1])));if(!job.IsCompleted)await runner.Stop();}
                var result=await job;return result.Verdict=="SUCCESS"?0:result.Verdict=="STOPPED"?3:4;
            }
        }
    }
}

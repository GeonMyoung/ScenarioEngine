using System;
using System.Collections.Generic;
using System.IO;
namespace MqttEasy {
 public static class Runtime {
  public static string VerificationFault="";
  public static string EngineDirectory {get;private set;}
  static string bundle;static bool verified;
  public static string Initialize(string root){
   root=Path.GetFullPath(root);if(bundle==root)return EngineDirectory;
   var settings=J.Decode<Dictionary<string,object>>(J.Read(Path.Combine(root,"launcher-runtime.json")));
   EngineDirectory=Path.GetFullPath(J.Text(settings,"engineDirectory"));
   if(!File.Exists(Path.Combine(EngineDirectory,"ScenarioEngineTest.exe")))throw new InvalidOperationException("MQTT/V2N용 ScenarioEngine MSI 설치 위치를 확인하세요.");
   bundle=root;verified=false;return EngineDirectory;
  }
  static string Below(string root,string relative){var path=Path.GetFullPath(Path.Combine(root,relative));if(!path.StartsWith(root.TrimEnd('\\')+"\\",StringComparison.OrdinalIgnoreCase))throw new InvalidOperationException("실행 파일 경로가 올바르지 않습니다.");return path;}
  public static void Validate(string root){
   Initialize(root);if(verified)return;
   var manifest=J.Decode<Dictionary<string,object>>(J.Read(Path.Combine(root,"bundle-manifest.json")));
   foreach(var pair in J.Map(J.Get(manifest,"runtimeSha256")))if(J.Hash(Below(Path.Combine(root,"runtime"),pair.Key))!=Convert.ToString(pair.Value))throw new InvalidOperationException("간편실행기 파일이 달라졌습니다. 배포 묶음을 확인하세요.");
   foreach(var pair in J.Map(J.Get(manifest,"installedRuntimeSha256")))if(J.Hash(Below(EngineDirectory,pair.Key))!=Convert.ToString(pair.Value))throw new InvalidOperationException("설치된 엔진 구성과 간편실행기 기준이 다릅니다. MSI 버전과 설치 파일을 확인하세요.");
   verified=true;
  }
 }
}

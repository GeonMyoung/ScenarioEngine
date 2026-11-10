using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
namespace MqttEasy {
 public sealed class EvidenceParts {
  readonly Dictionary<string,List<string>> pending=new Dictionary<string,List<string>>();
  public bool Incomplete {get{return pending.Count>0;}}
  public Dictionary<string,object> Read(Dictionary<string,object> data){
   if(J.Text(data,"encoding")!="json-text-parts")return data;
   var id=J.Text(data,"attachment_id");List<string> parts;
   if(!pending.TryGetValue(id,out parts)){parts=new List<string>();pending[id]=parts;}
   if(J.Number(data,"part")!=parts.Count+1)throw new IOException("분할 자료의 순서가 일치하지 않습니다.");
   parts.Add(J.Text(data,"value"));
   if(parts.Count!=J.Number(data,"parts"))return null;
   pending.Remove(id);
   return J.Decode<Dictionary<string,object>>(String.Join("",parts));
  }
 }
 public static class LocalReport {
  public static void Write(string run,string events,Scenario scenario,string verdict){
   var chunks=new EvidenceParts();
   using(var output=new StreamWriter(Path.Combine(run,"interface-user-log.jsonl"),false,new UTF8Encoding(false))){
    foreach(var line in File.ReadLines(events,Encoding.UTF8)){
     var row=J.Decode<Dictionary<string,object>>(line);if(J.Text(row,"kind")!="info")continue;
     var data=chunks.Read(J.Decode<Dictionary<string,object>>(J.Text(row,"data")));if(data==null)continue;
     var test=J.Text(row,"testName");var item=scenario.tests.FirstOrDefault(t=>"test_"+t.key==test);
     output.WriteLine(J.Encode(new {testName=test,log=J.Text(row,"log"),sender=J.Text(row,"sender"),data=new Dictionary<string,object>{{"시험 항목",item==null?scenario.title:item.label},{"관측 순번",J.Get(row,"sequence")},{"자료",data}}}));
    }
   }
   if(chunks.Incomplete)throw new IOException("일부 분할 자료가 누락됐습니다. 수집 기록을 확인하세요.");
   InterfaceLogs.UserReport.Write(run,scenario.title,verdict,scenario.publishOnly&&verdict=="SUCCESS"?"발행 완료 · 최종 합격 미판정":null,scenario.publishOnly?"자동 결과는 BSM 발행 절차의 수행 상태입니다. 최종 합격은 센터 수신 로그와 사후 대조하여 결정합니다. 송신 기록: bsm-transmit.jsonl / bsm-transmit.csv (이번 회차 mqttv2n-results 폴더).":null);
   var nativeResult=Path.Combine(Path.GetDirectoryName(events),"result.json");
   if(File.Exists(nativeResult)){
    var result=J.Decode<Dictionary<string,object>>(J.Read(nativeResult));var table=new StringBuilder("<section><h2>상세시험별 결과</h2><table style='width:100%;border-collapse:collapse;text-align:left'><tr><th>시험 항목</th><th>결과</th><th>확인 건수</th><th>중복</th><th>사유</th></tr>");
    foreach(var row in J.List(J.Get(result,"tests")).Select(J.Map)){
     var item=scenario.tests.FirstOrDefault(t=>"test_"+t.key==J.Text(row,"test"));if(item==null)continue;
     var state=J.Text(row,"result");string label=state=="SUCCESS"?"성공":state=="FAIL"?"실패":state=="STOPPED"?"중지":state=="NOT_RUN"?"미실행":"확인 필요";
     var reason=J.Text(row,"reason");if(reason.Length>0)reason=InterfaceLogs.UserReport.PublicError(new Exception(reason));
     table.Append("<tr><td>"+System.Net.WebUtility.HtmlEncode(item.label)+"</td><td>"+label+"</td><td>"+J.Text(row,"completed")+"</td><td>"+(row.ContainsKey("duplicates")?J.Text(row,"duplicates"):"-")+"</td><td>"+System.Net.WebUtility.HtmlEncode(reason)+"</td></tr>");
    }
    table.Append("</table>");
    var timSummary=J.Map(J.Get(result,"tim_summary"));
    if(J.Text(timSummary,"content_review")=="RECORD_ONLY")table.Append("<p>TIM은 furtherInfoID와 ITIS 조합으로 유형을 식별합니다. content 형식은 메시지별 기록에 표시하며 합불 기준에서 제외합니다.</p>");
    if(J.Text(timSummary,"content_review")=="HELD")table.Append("<p>TIM content 선택값 차이의 적합성은 판정 보류입니다.</p>");
    table.Append("</section>");
    var path=Path.Combine(run,"시험결과.html");var report=File.ReadAllText(path,Encoding.UTF8);int at=report.IndexOf("<article>",StringComparison.Ordinal);if(at<0)at=report.IndexOf("</main>",StringComparison.Ordinal);if(at>=0)File.WriteAllText(path,report.Insert(at,table.ToString()),new UTF8Encoding(false));
   }
  }
 }
}

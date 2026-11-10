using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Text.RegularExpressions;
using System.Web.Script.Serialization;
namespace InterfaceLogs {
 public static class UserReport {
  public static string PublicError(Exception error){
   var message=error.Message;
   if(Regex.IsMatch(message,@"(?i)((^|[ =""(])[a-z]:[\\/]|Traceback|System\.|\.py:|\.cpp:|\.cs:)")||!Regex.IsMatch(message,"[가-힣]"))return "시험 준비 또는 실행을 마치지 못했습니다. 설정을 확인하고 필요한 경우 상세 진단을 확인하세요.";
   foreach(var p in new[]{Tuple.Create("repetitions","반복 횟수"),Tuple.Create("socket_timeout_ms","통신 대기시간"),Tuple.Create("peer_port","대상 포트"),Tuple.Create("local_port","수신 포트"),Tuple.Create("my_domain","시험 시스템 도메인"),Tuple.Create("peer_domain","대상 도메인")})message=message.Replace(p.Item1,p.Item2);
   return message.Split(new[]{'\r','\n'},StringSplitOptions.RemoveEmptyEntries).FirstOrDefault()??"시험 설정을 확인하세요.";
  }
  static string Escape(object value){return WebUtility.HtmlEncode(value==null?"없음":value is bool?((bool)value?"true":"false"):Convert.ToString(value,System.Globalization.CultureInfo.InvariantCulture));}
  static string Pretty(object value){var source=new JavaScriptSerializer{MaxJsonLength=33554432,RecursionLimit=256}.Serialize(value);var b=new StringBuilder();bool quoted=false,escaped=false;int depth=0;foreach(char c in source){if(quoted){b.Append(c);if(escaped)escaped=false;else if(c=='\\')escaped=true;else if(c=='"')quoted=false;continue;}if(c=='"'){quoted=true;b.Append(c);}else if(c=='{'||c=='['){b.Append(c).Append('\n').Append(' ',++depth*2);}else if(c=='}'||c==']'){b.Append('\n').Append(' ',Math.Max(0,--depth)*2).Append(c);}else if(c==','){b.Append(c).Append('\n').Append(' ',depth*2);}else if(c==':')b.Append(": ");else b.Append(c);}return b.ToString();}
  static string Render(object value,int depth=0){
   if(depth>=2&&value is IEnumerable&&!(value is string))return "<pre>"+Escape(Pretty(value))+"</pre>";
   var map=value as Dictionary<string,object>;
   if(map!=null){
    var b=new StringBuilder("<dl>");
    foreach(var p in map){
     var content=p.Key=="송수신 원문 HEX"||p.Key=="ASN.1 해석 결과"
      ?"<details><summary>상세 보기</summary><pre>"+Escape(p.Value is string?p.Value:Pretty(p.Value))+"</pre></details>"
      :Render(p.Value,depth+1);
     b.Append("<dt>"+Escape(p.Key)+"</dt><dd>"+content+"</dd>");
    }
    return b.Append("</dl>").ToString();
   }
   if(value is IEnumerable && !(value is string)){var b=new StringBuilder("<ul>");foreach(var item in (IEnumerable)value)b.Append("<li>"+Render(item,depth+1)+"</li>");return b.Append("</ul>").ToString();}
   return "<span>"+Escape(value)+"</span>";
  }
  static object Get(Dictionary<string,object> m,string key){object value;return m.TryGetValue(key,out value)?value:null;}
  static IEnumerable<Dictionary<string,object>> Entries(string source,JavaScriptSerializer json){
   var pending=new Dictionary<string,List<Dictionary<string,object>>>();
   using(var file=new FileStream(source,FileMode.Open,FileAccess.Read,FileShare.ReadWrite))using(var input=new StreamReader(file,Encoding.UTF8)){
    string line;while((line=input.ReadLine())!=null){if(String.IsNullOrWhiteSpace(line))continue;var item=json.Deserialize<Dictionary<string,object>>(line);var data=Get(item,"data") as Dictionary<string,object>;
     if(data==null||!data.ContainsKey("분할 데이터")||!data.ContainsKey("분할 번호")){yield return item;continue;}
     var identity=Get(data,"관측 순번")??Get(data,"메시지 순번")??Get(data,"자료 순번")??Get(data,"자료 번호");
     string key=Convert.ToString(Get(item,"testIdx"))+"/"+Convert.ToString(Get(item,"testName"))+"/"+Convert.ToString(Get(data,"자료 구분"))+"/"+Convert.ToString(identity);
     List<Dictionary<string,object>> parts;if(!pending.TryGetValue(key,out parts)){parts=new List<Dictionary<string,object>>();pending[key]=parts;}
     if(Convert.ToInt32(data["분할 번호"])!=parts.Count+1)throw new IOException("분할 자료의 순서가 일치하지 않습니다.");parts.Add(item);
     if(parts.Count!=Convert.ToInt32(data["전체 분할 수"]))continue;
     var first=parts[0];var root=new Dictionary<string,object>((Dictionary<string,object>)first["data"]);var combined=new StringBuilder();foreach(var part in parts)combined.Append(Convert.ToString(((Dictionary<string,object>)part["data"])["분할 데이터"]));
     var decoded=json.DeserializeObject(combined.ToString());bool whole=Convert.ToString(Get(root,"자료 구분"))=="긴 시험 자료";
     foreach(var name in new[]{"분할 번호","전체 분할 수","분할 데이터","분할 안내"})root.Remove(name);
     if(whole&&decoded is Dictionary<string,object>){var map=(Dictionary<string,object>)decoded;foreach(var name in new[]{"인터페이스","시험","단계"})if(root.ContainsKey(name))map[name]=root[name];first["data"]=map;}else{root["상세"]=decoded;first["data"]=root;}
     first["log"]=Convert.ToString(first["log"])+" · 전체 자료 조립 완료";pending.Remove(key);yield return first;
    }
   }
   if(pending.Count>0)throw new IOException("일부 분할 자료가 누락되어 사용자용 결과를 완성하지 못했습니다.");
  }
  public static void Write(string directory,string title,string verdict,string resultLabel=null,string resultNote=null){
   var source=Path.Combine(directory,"interface-user-log.jsonl");if(!File.Exists(source))return;
   var result=resultLabel??(verdict=="SUCCESS"?"성공":verdict=="FAIL"?"실패":verdict=="STOPPED"?"중지":verdict=="NOT_RUN"?"미실행":"수행 오류");
   var json=new JavaScriptSerializer{MaxJsonLength=33554432,RecursionLimit=256};
   using(var output=new StreamWriter(Path.Combine(directory,"시험결과.html"),false,new UTF8Encoding(false))){
    output.Write("<!doctype html><html lang=ko><meta charset=utf-8><meta name=viewport content='width=device-width,initial-scale=1'><title>인터페이스 시험 결과</title><style>body{margin:0;background:#f6f4ed;color:#243b30;font:15px/1.7 'Malgun Gothic',sans-serif}main{max-width:1100px;margin:auto;padding:32px 24px}h1{font-size:30px}h2{border-bottom:2px solid #42634c}h3{font-size:18px}article{padding:18px 0;border-bottom:1px solid #c9d1c4}dl{display:grid;grid-template-columns:minmax(125px,23%) minmax(0,1fr);gap:0 16px}dt,dd{margin:0;padding:7px 0;border-bottom:1px solid #e1e4dc}dt{font-weight:600}dd,span{overflow-wrap:anywhere;white-space:pre-wrap}.summary{background:#e5ecdf;padding:20px}.sender{color:#53685c}ul{padding-left:22px}pre{white-space:pre-wrap;overflow-wrap:anywhere;background:#fff;padding:12px;border:1px solid #d1d8cd}@media(max-width:650px){dl{display:block}main{padding:20px 14px}}</style><main><h1>인터페이스 시험 결과</h1><div class=summary><h2>"+Escape(title)+"</h2><p>기록 생성 시각: "+File.GetCreationTime(source).ToString("yyyy-MM-dd HH:mm:ss")+"</p><p>자동 판정: <strong>"+Escape(result)+"</strong></p>"+(resultNote==null?"":"<p>"+Escape(resultNote)+"</p>")+"<p>시험 안내·송수신 자료·기대값과 실제값·확인 범위를 함께 확인하세요. 사용자 직접 확인 표시는 자동 판정과 별도입니다.</p></div>");
    foreach(var item in Entries(source,json)){output.Write("<article><h3>"+Escape(Get(item,"log"))+"</h3><p class=sender>발송: "+Escape(Get(item,"sender"))+"</p>");var data=Get(item,"data");if(data!=null)output.Write(Render(data));output.Write("</article>");}
    output.Write("</main></html>");
   }
  }
 }
}

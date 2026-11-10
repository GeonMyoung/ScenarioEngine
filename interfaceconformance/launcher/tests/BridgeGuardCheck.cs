using System;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Web.Script.Serialization;
using SharedWebTest;
class BridgeGuardCheck {
 static readonly JavaScriptSerializer json=new JavaScriptSerializer();const string Id="hkcbopjignhkclfmejopkpkpmdlpnmba";
 static Dictionary<string,object> Call(int port,string kind,string channel,string client,string token,string origin=null){
  var r=(HttpWebRequest)WebRequest.Create("http://127.0.0.1:"+port+"/bridge");r.Method="POST";r.ContentType="application/json";r.Headers["X-Rest-Extension"]=Id;r.Headers["Origin"]=origin??"chrome-extension://"+Id;r.Timeout=5000;
  var data=Encoding.UTF8.GetBytes(json.Serialize(new{kind=kind,channel=channel,clientId=client,token=token,data=new{}}));using(var s=r.GetRequestStream())s.Write(data,0,data.Length);
  using(var response=r.GetResponse())using(var reader=new StreamReader(response.GetResponseStream()))return json.Deserialize<Dictionary<string,object>>(reader.ReadToEnd());
 }
 static void Require(bool x,string m){if(!x)throw new Exception(m);}
 static void Rejected(Action a,string m){bool rejected=false;try{a();}catch(WebException){rejected=true;}Require(rejected,m);}
 static int Main(string[] args){try{
  string channel="990"+DateTime.UtcNow.Ticks;channel=channel.Substring(channel.Length-18);int events=0,port;
  using(var a=new WebFormLink(channel,Id)){
   port=a.Port;a.Event=(k,d)=>{events++;return Task.FromResult<object>(null);};
   bool duplicate=false;try{using(var b=new WebFormLink(channel,Id)){} }catch(InvalidOperationException){duplicate=true;}Require(duplicate,"duplicate channel accepted");
   Rejected(()=>Call(port,"hello",channel,"tab-a","","https://other.invalid"),"foreign origin accepted");
   Require((bool)Call(port,"hello",channel+"1","tab-a","")["linked"]==false,"wrong channel linked");
   var hello=Call(port,"hello",channel,"tab-a","");string token=Convert.ToString(hello["token"]);
   Rejected(()=>Call(port,"hello",channel,"tab-b",""),"second document linked");
   Rejected(()=>Call(port,"before-start",channel,"tab-a","bad"),"bad token accepted");Require(events==0,"rejected request caused event");
   Call(port,"before-setup",channel,"tab-a",token);Require(events==1,"valid request not routed");
  }
  using(var b=new WebFormLink(channel,Id)){Require(b.Port==port,"released slot not reusable");}
  using(var a=new PortReservation())using(var b=new PortReservation()){a.Available(45750);int p=a.Port;b.Available(p);Require(p!=b.Port,"same protocol port reserved twice");a.Dispose();using(var c=new PortReservation()){c.Exact(p);}}
  File.WriteAllText(args[0],"{\"duplicateChannelRejected\":true,\"foreignOriginRejected\":true,\"wrongChannelRejected\":true,\"wrongDocumentRejected\":true,\"wrongTokenRejected\":true,\"validRequestRouted\":true,\"releasedResourcesReusable\":true}");return 0;
 }catch(Exception e){File.WriteAllText(args[0]+".error",e.ToString());return 2;}}
}

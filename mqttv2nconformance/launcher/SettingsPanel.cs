using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;
namespace MqttEasy {
 public sealed class SettingsPanel : UserControl {
  readonly TableLayoutPanel fields=new TableLayoutPanel();readonly Dictionary<string,Control> inputs=new Dictionary<string,Control>();readonly CheckBox showPassword=new CheckBox();Scenario scenario;bool loading;
  public event Action Changed;
  public SettingsPanel(){Dock=DockStyle.Fill;BackColor=Color.FromArgb(246,244,237);var layout=new TableLayoutPanel{Dock=DockStyle.Fill,ColumnCount=1,RowCount=3,Padding=new Padding(10)};layout.RowStyles.Add(new RowStyle(SizeType.Absolute,66));layout.RowStyles.Add(new RowStyle(SizeType.Absolute,42));layout.RowStyles.Add(new RowStyle(SizeType.Percent,100));Controls.Add(layout);
   layout.Controls.Add(new Label{Text="입력값과 상세시험을 확인한 뒤 웹 환경설정을 적용하세요.\r\n상대 프로그램에는 엔진이 실제로 수락한 조건을 맞춥니다.",Dock=DockStyle.Fill},0,0);
   var buttons=new FlowLayoutPanel{Dock=DockStyle.Fill,WrapContents=false};var defaults=new Button{Text="기본값 채우기",Width=130,Height=32};var port=new Button{Text="빈 포트 찾기",Width=120,Height=32};showPassword.Visible=false;showPassword.Text="";showPassword.AutoSize=true;showPassword.Padding=new Padding(4,5,0,0);buttons.Controls.AddRange(new Control[]{defaults,port,showPassword});layout.Controls.Add(buttons,0,1);
   defaults.Click+=(s,e)=>FillDefaults();port.Click+=(s,e)=>{if(scenario!=null){int n=Ports.Free(44000+scenario.id);SetValue("port",n.ToString());}};showPassword.CheckedChanged+=(s,e)=>{foreach(var f in scenario.fields.Where(f=>f.type=="password"))if(inputs.ContainsKey(f.name))((TextBox)inputs[f.name]).UseSystemPasswordChar=!showPassword.Checked;};
   var scroll=new Panel{Dock=DockStyle.Fill,AutoScroll=true};fields.AutoSize=true;fields.AutoSizeMode=AutoSizeMode.GrowAndShrink;fields.Dock=DockStyle.Top;fields.ColumnCount=2;fields.ColumnStyles.Add(new ColumnStyle(SizeType.Percent,53));fields.ColumnStyles.Add(new ColumnStyle(SizeType.Percent,47));scroll.Controls.Add(fields);layout.Controls.Add(scroll,0,2);
  }
  public void LoadScenario(Scenario s){loading=true;scenario=s;fields.Controls.Clear();fields.RowStyles.Clear();fields.RowCount=0;inputs.Clear();showPassword.Checked=false;
   foreach(var f in s.fields){int row=fields.RowCount++;fields.RowStyles.Add(new RowStyle(SizeType.Absolute,f.label.Length>44?78:54));var label=new Label{Text=f.label,Dock=DockStyle.Fill,TextAlign=ContentAlignment.MiddleLeft};Control input;
    if(f.type=="checkbox"){var c=new CheckBox{Dock=DockStyle.Fill,AccessibleName=f.label};c.CheckedChanged+=(sender,e)=>Notify();input=c;}
    else{var t=new TextBox{Dock=DockStyle.Fill,Margin=new Padding(3,12,3,8),AccessibleName=f.label,UseSystemPasswordChar=f.type=="password",ReadOnly=f.name=="host"||f.name=="standard_type"};t.TextChanged+=(sender,e)=>Notify();input=t;}
    inputs[f.name]=input;fields.Controls.Add(label,0,row);fields.Controls.Add(input,1,row);
   }loading=false;FillDefaults();
  }
  void Notify(){if(!loading&&Changed!=null)Changed();}
  public void FillDefaults(){if(scenario==null)return;LoadValues(Settings.Defaults(scenario));Notify();}
  public void SetValue(string key,string value){Control c;if(inputs.TryGetValue(key,out c)){if(c is CheckBox)((CheckBox)c).Checked=String.Equals(value,"true",StringComparison.OrdinalIgnoreCase);else c.Text=value;}}
  public void SetFlag(string key,bool value){SetValue(key,value?"true":"false");}
  public void LoadValues(Dictionary<string,object> values){loading=true;try{foreach(var f in scenario.fields)SetValue(f.name,J.Text(values,f.name));}finally{loading=false;}}
  public Dictionary<string,object> Values(){return inputs.ToDictionary(p=>p.Key,p=>p.Value is CheckBox?(object)((CheckBox)p.Value).Checked:p.Value.Text);}
  public string Summary(Settings value){
   if(scenario.publishOnly)return "적용 완료 · BSM "+J.Text(value.Effective,"repetitions")+"회 발행 · 1초·QoS 0 고정\r\n자동 성공은 발행 완료 / 최종 합격은 사후 수신 로그 대조\r\n"+J.Text(value.Effective,"topic_bsm");
   var conditions=new List<string>();
   if(value.Tests.Any(k=>k.StartsWith("tim_")))conditions.Add("선택 TIM 각각 "+J.Text(value.Effective,"tim_per_type")+"건");
   if(value.Tests.Any(k=>!k.StartsWith("tim_")))conditions.Add((scenario.provider?"수신 ":"발행 ")+J.Text(value.Effective,"repetitions")+"건");
   return "적용 완료 · QoS 0 · "+String.Join(" / ",conditions)
       +(scenario.provider?" · 목표 수신 또는 중지까지 대기":"")+"\r\n"
       +J.Text(value.Effective,"host")+":"+J.Text(value.Effective,"port")+" · Broker·상대 자동 준비\r\n"
       +String.Join(" / ",value.Effective.Where(p=>p.Key.StartsWith("topic_")&&!String.IsNullOrEmpty(Convert.ToString(p.Value))).Select(p=>Convert.ToString(p.Value)));
  }
 }
}

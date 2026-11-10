using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;
namespace RestEasy {
 public sealed class SettingsPanel : UserControl {
  readonly TableLayoutPanel fields=new TableLayoutPanel();readonly Dictionary<string,Control> inputs=new Dictionary<string,Control>();readonly CheckBox showPassword=new CheckBox();Scenario scenario;bool loading;
  public event Action Changed;
  public SettingsPanel(){Dock=DockStyle.Fill;BackColor=Color.FromArgb(246,244,237);var layout=new TableLayoutPanel{Dock=DockStyle.Fill,ColumnCount=1,RowCount=3,Padding=new Padding(10)};layout.RowStyles.Add(new RowStyle(SizeType.Absolute,66));layout.RowStyles.Add(new RowStyle(SizeType.Absolute,42));layout.RowStyles.Add(new RowStyle(SizeType.Percent,100));Controls.Add(layout);
   layout.Controls.Add(new Label{Text="입력값과 상세시험을 확인한 뒤 웹 환경설정을 적용하세요.\r\n상대 프로그램에는 엔진이 실제로 수락한 조건을 맞춥니다.",Dock=DockStyle.Fill},0,0);
   var buttons=new FlowLayoutPanel{Dock=DockStyle.Fill,WrapContents=false};var defaults=new Button{Text="기본값 채우기",Width=130,Height=32};var port=new Button{Text="빈 포트 찾기",Width=120,Height=32};showPassword.Text="인증값 표시";showPassword.AutoSize=true;showPassword.Padding=new Padding(4,5,0,0);buttons.Controls.AddRange(new Control[]{defaults,port,showPassword});layout.Controls.Add(buttons,0,1);
   defaults.Click+=(s,e)=>FillDefaults();port.Click+=(s,e)=>{if(scenario!=null){int n=Ports.Free(43000+scenario.id);SetValue(scenario.provider?"sut_base_url":"local_port",scenario.provider?"http://127.0.0.1:"+n:n.ToString());}};showPassword.CheckedChanged+=(s,e)=>{foreach(var f in scenario.fields.Where(f=>f.type=="password"))if(inputs.ContainsKey(f.name))((TextBox)inputs[f.name]).UseSystemPasswordChar=!showPassword.Checked;};
   var scroll=new Panel{Dock=DockStyle.Fill,AutoScroll=true};fields.AutoSize=true;fields.AutoSizeMode=AutoSizeMode.GrowAndShrink;fields.Dock=DockStyle.Top;fields.ColumnCount=2;fields.ColumnStyles.Add(new ColumnStyle(SizeType.Percent,53));fields.ColumnStyles.Add(new ColumnStyle(SizeType.Percent,47));scroll.Controls.Add(fields);layout.Controls.Add(scroll,0,2);
  }
  public void LoadScenario(Scenario s){loading=true;scenario=s;fields.Controls.Clear();fields.RowStyles.Clear();fields.RowCount=0;inputs.Clear();showPassword.Checked=false;
   foreach(var f in s.fields){int row=fields.RowCount++;fields.RowStyles.Add(new RowStyle(SizeType.Absolute,54));var label=new Label{Text=f.label,Dock=DockStyle.Fill,TextAlign=ContentAlignment.MiddleLeft};Control input;
    if(f.type=="checkbox"){var c=new CheckBox{Dock=DockStyle.Fill,AccessibleName=f.label};c.CheckedChanged+=(sender,e)=>Notify();input=c;}
    else{var t=new TextBox{Dock=DockStyle.Fill,Margin=new Padding(3,12,3,8),AccessibleName=f.label,UseSystemPasswordChar=f.type=="password"};t.TextChanged+=(sender,e)=>Notify();input=t;}
    inputs[f.name]=input;fields.Controls.Add(label,0,row);fields.Controls.Add(input,1,row);
   }loading=false;FillDefaults();
  }
  void Notify(){if(!loading&&Changed!=null)Changed();}
  public void FillDefaults(){if(scenario==null)return;LoadValues(scenario.tester);if(scenario.provider)SetValue("sut_base_url","http://127.0.0.1:"+(43000+scenario.id));else SetValue("local_port",(43000+scenario.id).ToString());Notify();}
  public void SetValue(string key,string value){Control c;if(inputs.TryGetValue(key,out c)){if(c is CheckBox)((CheckBox)c).Checked=String.Equals(value,"true",StringComparison.OrdinalIgnoreCase);else c.Text=value;}}
  public void SetFlag(string key,bool value){SetValue(key,value?"true":"false");}
  public void LoadValues(Dictionary<string,object> values){loading=true;try{foreach(var f in scenario.fields)SetValue(f.name,J.Text(values,f.name));}finally{loading=false;}}
  public Dictionary<string,object> Values(){return inputs.ToDictionary(p=>p.Key,p=>p.Value is CheckBox?(object)((CheckBox)p.Value).Checked:p.Value.Text);}
  public string Summary(Settings value){return "적용 완료 · "+value.Tests.Count+"개 선택 · 항목당 "+J.Text(value.Effective,"repetitions")+"회\r\n127.0.0.1:"+value.Port+" · "+(value.DataState=="absent"?"자료 부재 오류 조건":value.DataState=="empty"?"빈 정상응답 조건":"정상 자료 조건")+"\r\n시작 버튼을 누르면 상대 프로그램을 준비합니다.";}
 }
}

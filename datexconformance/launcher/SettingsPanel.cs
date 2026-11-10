using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

namespace DatexEasy {
    public sealed class SettingsPanel : UserControl {
        readonly TableLayoutPanel fields=new TableLayoutPanel();
        readonly Dictionary<string,TextBox> inputs=new Dictionary<string,TextBox>();
        readonly Label hint=new Label();readonly ErrorProvider errors=new ErrorProvider();
        readonly CheckBox useInitiate=new CheckBox();
        readonly CheckBox showPassword=new CheckBox();Scenario scenario;bool loading;
        public event Action Changed;
        static readonly Dictionary<string,string> Labels=new Dictionary<string,string>{
            {"my_domain","시험 시스템 도메인"},{"peer_domain","시험 대상 도메인"},{"peer_ip","대상 IP 주소 (같은 PC)"},
            {"peer_port","시험 대상의 수신 포트"},{"local_port","시험 시스템의 수신 포트"},
            {"user","사용자 이름"},{"pass","비밀번호"},{"hb_dur","최대 무수신 시간 (초)"},
            {"rsp_timeout","응답 제한 시간 (초)"},{"connect_timeout_s","접속 대기 시간 (초)"},
            {"fred_maintain_s","FrED 정상 유지 시간 (초)"},{"receive_s","취소 전 수신 시간 (초)"},
            {"period_s","정보요청 주기 (초)"},{"invalid_pass","무효 로그인용 비밀번호 (선택)"}};
        public SettingsPanel(){
            Dock=DockStyle.Fill;BackColor=Color.FromArgb(246,244,237);
            var layout=new TableLayoutPanel{Dock=DockStyle.Fill,ColumnCount=1,RowCount=3,Padding=new Padding(10)};
            layout.RowStyles.Add(new RowStyle(SizeType.Absolute,68));layout.RowStyles.Add(new RowStyle(SizeType.Absolute,42));layout.RowStyles.Add(new RowStyle(SizeType.Percent,100));Controls.Add(layout);
            hint.Text="화면의 입력값을 확인·수정한 뒤 ‘환경설정 적용’을 누르세요.\r\n에뮬레이터에는 같은 값과 반대쪽 도메인을 맞춰 적용합니다.";hint.Dock=DockStyle.Fill;layout.Controls.Add(hint,0,0);
            var buttons=new FlowLayoutPanel{Dock=DockStyle.Fill,WrapContents=false};
            var defaults=new Button{Text="기본값 채우기",Width=130,Height=32};var port=new Button{Text="빈 포트 찾기",Width=120,Height=32};
            showPassword.Text="비밀번호 표시";showPassword.AutoSize=true;showPassword.Padding=new Padding(4,5,0,0);buttons.Controls.AddRange(new Control[]{defaults,port,showPassword});layout.Controls.Add(buttons,0,1);
            defaults.Click+=(s,e)=>FillDefaults();port.Click+=(s,e)=>{if(scenario!=null)inputs[TesterConnects()?"peer_port":"local_port"].Text=Ports.Free(43000+scenario.id).ToString();};
            useInitiate.CheckedChanged+=(s,e)=>{UpdateConnection();if(!loading && Changed!=null)Changed();};
            showPassword.CheckedChanged+=(s,e)=>{foreach(var key in new[]{"pass","invalid_pass"})if(inputs.ContainsKey(key))inputs[key].UseSystemPasswordChar=!showPassword.Checked;};
            var scroll=new Panel{Dock=DockStyle.Fill,AutoScroll=true};fields.AutoSize=true;fields.AutoSizeMode=AutoSizeMode.GrowAndShrink;fields.Dock=DockStyle.Top;fields.ColumnCount=2;fields.ColumnStyles.Add(new ColumnStyle(SizeType.Percent,52));fields.ColumnStyles.Add(new ColumnStyle(SizeType.Percent,48));scroll.Controls.Add(fields);layout.Controls.Add(scroll,0,2);errors.ContainerControl=this;errors.BlinkStyle=ErrorBlinkStyle.NeverBlink;
        }
        public void LoadScenario(Scenario s){scenario=s;loading=true;errors.Clear();fields.Controls.Clear();fields.RowStyles.Clear();fields.RowCount=0;inputs.Clear();showPassword.Checked=false;
            int modeRow=fields.RowCount++;fields.RowStyles.Add(new RowStyle(SizeType.Absolute,64));
            useInitiate.Text="개시요청 사용 (ISO Server가 TCP 접속 후 Initiate)\r\n해제하면 ISO Client가 TCP 접속 후 Login";
            useInitiate.AccessibleName="개시요청 사용";useInitiate.Dock=DockStyle.Fill;
            fields.Controls.Add(useInitiate,0,modeRow);fields.SetColumnSpan(useInitiate,2);
            foreach(var pair in Labels){string key=pair.Key;if(!s.provider && new[]{"invalid_pass","fred_maintain_s","receive_s","period_s"}.Contains(key))continue;
                int row=fields.RowCount++;fields.RowStyles.Add(new RowStyle(SizeType.Absolute,40));var label=new Label{Text=pair.Value,Dock=DockStyle.Fill,TextAlign=ContentAlignment.MiddleLeft};
                var input=new TextBox{Dock=DockStyle.Fill,Margin=new Padding(3,6,24,6),AccessibleName=pair.Value,UseSystemPasswordChar=key=="pass" || key=="invalid_pass"};inputs[key]=input;fields.Controls.Add(label,0,row);fields.Controls.Add(input,1,row);input.TextChanged+=(sender,e)=>{errors.SetError(input,"");if(!loading && Changed!=null)Changed();};}
            loading=false;FillDefaults();}
        public void FillDefaults(){if(scenario==null)return;loading=true;useInitiate.Checked=J.Get(scenario.tester,"use_initiate") is bool && (bool)J.Get(scenario.tester,"use_initiate");foreach(var pair in inputs)pair.Value.Text=J.Text(scenario.tester,pair.Key);inputs["peer_port"].Text=inputs["local_port"].Text=(43000+scenario.id).ToString();inputs["peer_ip"].Text="127.0.0.1";loading=false;UpdateConnection();errors.Clear();if(Changed!=null)Changed();}
        public Dictionary<string,object> Values(){var result=new Dictionary<string,object>();errors.Clear();foreach(var pair in inputs){string value=pair.Value.Text;if(!pair.Value.Enabled){result[pair.Key]=value;continue;}bool numeric=pair.Key.EndsWith("_port") || new[]{"hb_dur","rsp_timeout","connect_timeout_s","fred_maintain_s","receive_s","period_s"}.Contains(pair.Key);if(numeric){int number;if(!int.TryParse(value,out number)||number<1){errors.SetError(pair.Value,"1 이상의 정수를 입력하세요.");pair.Value.Focus();throw new InvalidOperationException(Labels[pair.Key]+"에 1 이상의 정수를 입력하세요.");}result[pair.Key]=number;}else result[pair.Key]=pair.Key.Contains("pass")?value:value.Trim();}result["use_initiate"]=useInitiate.Checked;return result;}
        public void SetValue(string key,string value){if(key=="use_initiate")useInitiate.Checked=bool.Parse(value);else inputs[key].Text=value;}
        public void LoadValues(Dictionary<string,object> values){loading=true;try{useInitiate.Checked=J.Get(values,"use_initiate") is bool && (bool)J.Get(values,"use_initiate");foreach(var pair in inputs)pair.Value.Text=J.Text(values,pair.Key);}finally{loading=false;UpdateConnection();}}
        bool TesterConnects(){return scenario!=null && scenario.provider!=useInitiate.Checked;}
        void UpdateConnection(){if(scenario==null || !inputs.ContainsKey("local_port"))return;bool active=TesterConnects();inputs["peer_ip"].Enabled=inputs["peer_port"].Enabled=active;inputs["local_port"].Enabled=!active;hint.Text=active?"TCP 접속: 시험 시스템 → 시험 대상\r\n대상 IP·수신 포트를 입력하고 ‘환경설정 적용’을 누르세요.":"TCP 접속: 시험 대상 → 시험 시스템\r\n시험 시스템 수신 포트를 입력하고 ‘환경설정 적용’을 누르세요.";}
        public string Summary(Settings value){return "적용 완료 · "+value.Tests.Count+"개 선택\r\n도메인: "+J.Text(value.Tester,"my_domain")+" ↔ "+J.Text(value.Tester,"peer_domain")+"\r\n127.0.0.1:"+value.Port+" · 무수신 "+J.Text(value.Tester,"hb_dur")+"초 / 응답 "+J.Text(value.Tester,"rsp_timeout")+"초 · "+((bool)value.Tester["use_initiate"]?"개시요청 사용":"일반 연결")+"\r\nTCP 접속: "+(value.TesterConnects?"시험 시스템 → 시험 대상":"시험 대상 → 시험 시스템");}
    }
}

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;

namespace BinaryEasy {
    public sealed class MessagePart { public long Offset; public int Length; }
    public sealed class MessageEntry {
        public int Index,ExpectedParts=1,Bytes;
        public bool Frame;
        public string Time,TestKey,TestTitle,Round,Number,Direction,Sender,Receiver,Title,Error;
        public readonly SortedDictionary<int,MessagePart> Parts=new SortedDictionary<int,MessagePart>();
        public bool Complete { get { return Parts.Count==ExpectedParts && Enumerable.Range(1,ExpectedParts).All(Parts.ContainsKey); } }
    }
    public sealed class MessageView {
        public Dictionary<string,object> Data;
        public string Json,Original,Hex,Notice;
    }
    // Retain offsets and small row metadata. Full payloads stay in the existing
    // append-only Controller journal and are read only when a row is selected.
    public sealed class MessageArchive {
        readonly string path;readonly Scenario scenario;long position;
        readonly Dictionary<string,MessageEntry> groups=new Dictionary<string,MessageEntry>();
        public readonly List<MessageEntry> Entries=new List<MessageEntry>();
        public string LastError {get;private set;}
        public MessageArchive(string directory,Scenario selected){path=Path.Combine(directory,"controller-messages.jsonl");scenario=selected;}
        static string Attachment(Dictionary<string,object> envelope){
            var value=J.Get(envelope,"data");var text=value as string;
            if(text==null)return J.Encode(value);
            if(text.TrimStart().StartsWith("{")||text.TrimStart().StartsWith("["))return text;
            return new UTF8Encoding(false,true).GetString(Convert.FromBase64String(text));
        }
        static Dictionary<string,object> Envelope(string line){return J.Map(J.Get(J.Map(J.Get(J.Decode<Dictionary<string,object>>(line),"message")),"data"));}
        string Read(MessagePart part){using(var f=new FileStream(path,FileMode.Open,FileAccess.Read,FileShare.ReadWrite)){f.Position=part.Offset;var bytes=new byte[part.Length];int at=0;while(at<bytes.Length){int n=f.Read(bytes,at,bytes.Length-at);if(n==0)throw new IOException("표시 기록을 끝까지 읽지 못했습니다.");at+=n;}return Encoding.UTF8.GetString(bytes).TrimEnd('\r','\n');}}
        static bool Line(FileStream f,out string line,out MessagePart part){
            long start=f.Position;var bytes=new List<byte>();int value;
            while((value=f.ReadByte())!=-1){bytes.Add((byte)value);if(value==10){part=new MessagePart{Offset=start,Length=bytes.Count};line=Encoding.UTF8.GetString(bytes.ToArray()).TrimEnd('\r','\n');return true;}if(bytes.Count>33554432)throw new IOException("표시 기록 한 줄이 읽기 한도를 초과했습니다. 원본 기록 폴더를 확인하세요.");}
            f.Position=start;line=null;part=null;return false;
        }
        public bool Refresh(int budgetMs=50){
            if(!File.Exists(path))return false;bool changed=false;var watch=Stopwatch.StartNew();
            try{using(var f=new FileStream(path,FileMode.Open,FileAccess.Read,FileShare.ReadWrite,65536)){
                if(f.Length<position)throw new IOException("현재 회차의 표시 기록이 교체됐습니다. 상세 창을 다시 여세요.");f.Position=position;
                string line;MessagePart part;
                while(Line(f,out line,out part)){
                    position=f.Position;
                    try{
                        var record=J.Decode<Dictionary<string,object>>(line);var message=J.Map(J.Get(record,"message"));var envelope=J.Map(J.Get(message,"data"));
                        if(J.Text(record,"direction")=="RX"&&J.Text(message,"method")=="NOTIFY"&&J.Text(message,"level")=="info"&&J.Text(envelope,"dataType")=="JSON"&&J.Get(envelope,"data")!=null){
                            var raw=Attachment(envelope);var data=J.Decode<Dictionary<string,object>>(raw);if(data==null)throw new FormatException("표시 자료는 JSON 객체여야 합니다.");
                            bool split=data.ContainsKey("분할 번호");int ordinal=split?checked((int)J.Number(data,"분할 번호")):1,count=split?checked((int)J.Number(data,"전체 분할 수")):1;
                            if(ordinal<1||count<1||ordinal>count||count>10000)throw new FormatException("표시 조각 번호를 확인하세요.");
                            string test=J.Text(envelope,"testName");bool frame=data.ContainsKey("메시지 순번");
                            string key=J.Text(message,"testIdx")+"|"+test+"|"+(frame?"frame:"+J.Text(data,"메시지 순번"):"data:"+J.Text(data,"자료 순번"));
                            MessageEntry entry=null;if(split)groups.TryGetValue(key,out entry);
                            if(entry!=null&&(entry.ExpectedParts!=count||entry.Parts.ContainsKey(ordinal))){entry.Error="표시 조각 번호가 중복되거나 개수가 다릅니다.";entry=null;}
                            if(entry==null){
                                var item=scenario.tests.FirstOrDefault(t=>"test_"+t.key==test);DateTimeOffset time;string timeText=DateTimeOffset.TryParse(J.Text(record,"time"),out time)?time.ToLocalTime().ToString("HH:mm:ss.fff"):J.Text(record,"time");
                                entry=new MessageEntry{Index=Entries.Count+1,Time=timeText,TestKey=test,TestTitle=item==null?"전체 시험":item.label,ExpectedParts=count,Frame=frame,Round=J.Text(data,"회차"),Number=J.Text(data,"메시지 순번"),Direction=frame?J.Text(data,"구분"):"검사 자료",Sender=J.Text(data,"발송 주체"),Receiver=J.Text(data,"수신 주체"),Title=frame?"정보 프레임":J.Text(data,"자료 구분")};
                                if(entry.Sender.Length==0)entry.Sender=J.Text(envelope,"sender");if(entry.Title.Length==0)entry.Title=J.Text(envelope,"log");Entries.Add(entry);if(split)groups[key]=entry;
                            }
                            entry.Parts.Add(ordinal,part);
                            if(entry.Complete){var full=split?Load(entry).Data:data;if(full!=null){var detail=J.Map(J.Get(full,"상세"));if(entry.Frame){entry.Title=J.Text(detail,"메시지 유형");entry.Bytes=(int)J.Number(detail,"실제 바이트 수");}else if(J.Text(full,"자료 구분").Length>0)entry.Title=J.Text(full,"자료 구분");}}
                            changed=true;
                        }
                    }catch(Exception error){Entries.Add(new MessageEntry{Index=Entries.Count+1,Direction="확인 필요",Time="",TestTitle="표시 자료",Title="표시 자료 해석 확인 필요",Sender="",Receiver="",Round="",Number="",Error=error.Message,Parts={{1,part}}});changed=true;}
                    if(watch.ElapsedMilliseconds>=budgetMs)break;
                }
            }LastError=null;}catch(IOException e){LastError=e.Message;}
            return changed;
        }
        public void ReadToEnd(){long before;do{before=position;Refresh(1000);}while(position!=before);}
        public MessageView Load(MessageEntry entry){
            var originals=new List<string>();var fragments=new List<string>();Dictionary<string,object> first=null;
            try{
                foreach(var part in entry.Parts){var record=Read(part.Value);string raw;try{raw=Attachment(Envelope(record));}catch{raw=record;}originals.Add("표시 조각 "+part.Key+"/"+entry.ExpectedParts+Environment.NewLine+Pretty(raw));var value=J.Decode<Dictionary<string,object>>(raw);if(first==null)first=value;if(value.ContainsKey("분할 데이터"))fragments.Add(J.Text(value,"분할 데이터"));}
                if(!entry.Complete)return new MessageView{Original=String.Join(Environment.NewLine+Environment.NewLine,originals),Json=String.Join(Environment.NewLine+Environment.NewLine,originals),Hex="",Notice="표시 조각 "+entry.Parts.Count+"/"+entry.ExpectedParts+"개가 도착했습니다. 수집한 자료는 모두 보존합니다."};
                if(fragments.Count>0){var restored=J.Decode<Dictionary<string,object>>(String.Concat(fragments));if(entry.Frame){first.Remove("분할 번호");first.Remove("전체 분할 수");first.Remove("분할 데이터");first["상세"]=restored;}else first=restored;}
                var detail=J.Map(J.Get(first,"상세"));return new MessageView{Data=first,Json=Pretty(J.Encode(first)),Original=String.Join(Environment.NewLine+Environment.NewLine,originals),Hex=J.Text(detail,"원문 HEX"),Notice=entry.Error??(entry.ExpectedParts>1?"표시 조각 "+entry.ExpectedParts+"개를 모두 합쳤습니다.":"")};
            }catch(Exception e){return new MessageView{Original=String.Join(Environment.NewLine+Environment.NewLine,originals),Json=String.Join(Environment.NewLine+Environment.NewLine,originals),Hex="",Notice="표시 자료를 해석하지 못했습니다. 수집 원본을 확인하세요. "+e.Message};}
        }
        // Whitespace-only formatting also preserves integer/string spelling in
        // the original attachment view; it never abbreviates field contents.
        public static string Pretty(string json){var b=new StringBuilder();int depth=0;bool quoted=false,escape=false;foreach(char c in json??""){if(quoted){b.Append(c);if(escape)escape=false;else if(c=='\\')escape=true;else if(c=='"')quoted=false;continue;}if(c=='"'){quoted=true;b.Append(c);}else if(c=='{'||c=='['){b.Append(c).AppendLine();depth++;b.Append(' ',depth*2);}else if(c=='}'||c==']'){depth=Math.Max(0,depth-1);b.AppendLine().Append(' ',depth*2).Append(c);}else if(c==',')b.Append(c).AppendLine().Append(' ',depth*2);else if(c==':')b.Append(": ");else if(!Char.IsWhiteSpace(c))b.Append(c);}return b.ToString();}
        public object Snapshot(){return new {records=Entries.Select(e=>new {e.Index,e.TestKey,e.Direction,e.Sender,e.Receiver,e.Round,e.Number,e.Bytes,e.ExpectedParts,parts=e.Parts.Count,e.Complete,view=Load(e)}).ToArray(),error=LastError};}
    }
}

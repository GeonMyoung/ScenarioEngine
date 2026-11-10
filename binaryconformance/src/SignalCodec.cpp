#include "SignalCodec.h"
#include "ExtendedCodec.h"
#include <windows.h>
#include <algorithm>
#include <limits>

namespace signalbinary { namespace {
using rest::Failure;
unsigned u16(const Bytes &b,size_t n){return unsigned(b[n])*256+b[n+1];}
uint64_t uintValue(const Json &j,uint64_t limit,const std::string &name){
    if(j.kind!=Json::Number||j.text.empty()||j.text.size()>10||j.text.find_first_not_of("0123456789")!=std::string::npos)throw Failure(name+": 정수 자료형 오류");
    auto n=std::stoull(j.text);if(n>limit)throw Failure(name+": 바이트 폭의 유효범위 초과");return n;
}
void setNumber(Json &j,const std::string &name,uint64_t n){auto &v=j.object[name];v.kind=Json::Number;v.text=std::to_string(n);}
void setText(Json &j,const std::string &name,const std::string &s){auto &v=j.object[name];v.kind=Json::String;v.text=s;}
const Json &required(const Json &j,const std::string &name){auto p=j.get(name);if(!p)throw Failure(name+": 필수 항목 누락");return *p;}
std::string convert(const std::string &s,unsigned from,unsigned to){
    if(s.empty())return {};
    auto n=MultiByteToWideChar(from,MB_ERR_INVALID_CHARS,s.data(),static_cast<int>(s.size()),nullptr,0);if(!n)throw Failure("CHAR 문자열 인코딩 오류");
    std::wstring w(n,0);MultiByteToWideChar(from,MB_ERR_INVALID_CHARS,s.data(),static_cast<int>(s.size()),w.data(),n);
    BOOL fallback=FALSE;auto m=WideCharToMultiByte(to,to==CP_UTF8?WC_ERR_INVALID_CHARS:WC_NO_BEST_FIT_CHARS,w.data(),n,nullptr,0,nullptr,to==CP_UTF8?nullptr:&fallback);
    if(!m||fallback)throw Failure("CHAR 문자열을 선택한 인코딩으로 표현할 수 없습니다.");std::string result(m,0);
    WideCharToMultiByte(to,to==CP_UTF8?WC_ERR_INVALID_CHARS:WC_NO_BEST_FIT_CHARS,w.data(),n,result.data(),m,nullptr,to==CP_UTF8?nullptr:&fallback);
    if(fallback)throw Failure("CHAR 문자열 변환 손실");return result;
}
struct Field {std::string name;unsigned width;bool text;};
std::vector<Field> fields(unsigned message){
    if(message==70){std::vector<Field> v={{"LC_NO",4,false},{"START_HOUR",1,false},{"START_MIN",1,false},{"CYCLE",2,false},{"OFFSET",2,false}};for(auto ring:{"ARING_","BRING_"})for(unsigned i=1;i<=8;++i)v.push_back({std::string(ring)+std::to_string(i)+"PHASE",2,false});return v;}
    if(message!=68&&message!=69)throw Failure("지원하지 않는 Binary 메시지 번호");
    std::vector<Field> v={{"LC_NO",1,false},{"LC_NAME",100,true},{"LC_TYPE",1,false},{"LC_LAT",20,true},{"LC_LNG",20,true},{"LC_STATUS",1,false},{"LC_COUNT",1,false}};
    for(auto ring:{"A","B"}){v.push_back({std::string("LC_")+ring+"_FLONUMBER",1,false});for(auto point:{"START","MIDDLE","END"})for(auto axis:{"LAT","LNG"})v.push_back({std::string("LC_")+ring+"_"+point+"_"+axis,20,true});}return v;
}
void semantic(const Json &row,unsigned message){if(message==70){if(uintValue(required(row,"START_HOUR"),255,"START_HOUR")>23||uintValue(required(row,"START_MIN"),255,"START_MIN")>59)throw Failure("TOD 시작시각 범위 오류 (시 0~23, 분 0~59)");}}
}
Bytes fixedText(const std::string &s,unsigned width,const Profile &p,bool terminated){
    if(s.empty()||s.find('\0')!=std::string::npos)throw Failure("CHAR 값이 비어 있거나 NUL을 포함합니다.");auto value=convert(s,CP_UTF8,p.encoding=="CP949"?949:CP_UTF8);if(value.size()>width||(terminated&&value.size()==width))throw Failure("CHAR 바이트 폭 또는 NULL 종료 공간 초과");Bytes b(value.begin(),value.end());b.resize(width,0);return b;
}
std::string readFixedText(const Bytes &b,const Profile &p,bool terminated){auto end=std::find(b.begin(),b.end(),0);if(end==b.begin()||(terminated&&end==b.end())||std::any_of(end,b.end(),[](unsigned char c){return c!=0;}))throw Failure("CHAR 값·NUL 패딩·종료 문자 오류");return convert(std::string(b.begin(),end),p.encoding=="CP949"?949:CP_UTF8,CP_UTF8);}
std::string dump(const Json &j){
    if(j.kind==Json::String)return rest::quote(j.text);if(j.kind==Json::Number)return j.text;if(j.kind==Json::Bool)return j.boolean?"true":"false";if(j.kind==Json::Null)return "null";
    std::string s=j.kind==Json::Array?"[":"{";bool first=true;if(j.kind==Json::Array)for(auto &v:j.array){if(!first)s+=",";first=false;s+=dump(v);}else for(auto &v:j.object){if(!first)s+=",";first=false;s+=rest::quote(v.first)+":"+dump(v.second);}return s+(j.kind==Json::Array?"]":"}");
}
std::string hex(const Bytes &b){static const char *digits="0123456789ABCDEF";std::string s;s.reserve(b.size()*2);for(auto x:b){s+=digits[x>>4];s+=digits[x&15];}return s;}
Bytes unhex(const std::string &s){Bytes b;if(s.size()%2)throw Failure("HEX 길이 오류");auto n=[](char c)->int{if(c>='0'&&c<='9')return c-'0';if(c>='A'&&c<='F')return c-'A'+10;if(c>='a'&&c<='f')return c-'a'+10;throw Failure("HEX 문자 오류");};for(size_t i=0;i<s.size();i+=2)b.push_back(static_cast<unsigned char>(n(s[i])*16+n(s[i+1])));return b;}
std::string infoName(unsigned m){return m==67?"차량운행정보(BSM_INFO)":m==71?"최적경로정보":m==72?"돌발상황정보":m==68?"전체 교차로 상태":m==69?"변경 교차로 상태":m==70?"교차로 TOD":"알 수 없는 정보";}
unsigned lrc(const Bytes &b,const Profile &p){unsigned n=0;for(auto x:b){if(p.checksum=="xor8")n^=x;else if(p.checksum=="sum8")n=(n+x)&255;else throw Failure("지원하지 않는 LRC 계산 방식");}return p.checksum=="sum8"?(256-n)&255:n;}
Bytes packet(unsigned message,unsigned flag,unsigned seq,const Bytes &payload,const Profile &p){
    if(payload.size()>65529||message>255||flag>255||seq>255)throw Failure("Binary 패킷 입력 범위 오류");unsigned size=static_cast<unsigned>(payload.size()+6);
    Bytes b={static_cast<unsigned char>(message),static_cast<unsigned char>(size>>8),static_cast<unsigned char>(size),static_cast<unsigned char>(flag),static_cast<unsigned char>(seq)};b.insert(b.end(),payload.begin(),payload.end());b.push_back(static_cast<unsigned char>(lrc(b,p)));return b;
}
Bytes acknowledgement(unsigned message,unsigned seq,bool accepted,const Profile &p){return {static_cast<unsigned char>(message),0,5,static_cast<unsigned char>(p.ackSequence=="fixed1"?1:seq),static_cast<unsigned char>(accepted?1:0)};}
Frame frame(const Bytes &b,const Profile &p){
    if(b.size()<6||b.size()!=u16(b,1))throw Failure("정보 프레임 SIZE와 실제 길이가 다릅니다.");
    if(b[0]<67||b[0]>72)throw Failure("정보 메시지 번호가 67~72 범위와 다릅니다.");
    if(b[3]>2)throw Failure("Start-End 값은 0/1/2여야 합니다.");
    Bytes checked(b.begin(),b.end()-1);if(b.back()!=lrc(checked,p))throw Failure("LRC 검사값이 선택한 계산 기준과 다릅니다.");
    return {b[0],b[3],b[4],Bytes(b.begin()+5,b.end()-1),b};
}
void validateAck(const Bytes &b,unsigned msg,unsigned seq,bool accepted,const Profile &p){
    if(b.size()!=5||u16(b,1)!=5)throw Failure("ACK/NACK는 SIZE=5의 응답이어야 합니다.");
    if(b[0]!=msg)throw Failure("ACK/NACK 메시지 번호가 송신 메시지와 다릅니다.");
    if(b[3]!=(p.ackSequence=="fixed1"?1:seq))throw Failure("ACK/NACK 순서번호가 선택한 대응 규칙과 다릅니다.");
    if(b[4]!=(accepted?1:0))throw Failure(accepted?"유효 정보에 대한 ACK(1)를 받지 못했습니다.":"오류 정보에 대한 NACK(0)를 받지 못했습니다.");
}
Bytes encode(unsigned message,const Json &records,const Profile &p){
    if(extended(message))return encodeExtended(message,records,p);
    if(records.kind!=Json::Array)throw Failure("시험 자료는 레코드 배열이어야 합니다.");auto fs=fields(message);Bytes out;
    for(auto &row:records.array){if(row.kind!=Json::Object)throw Failure("시험 레코드는 객체여야 합니다.");semantic(row,message);
        for(auto &f:fs){auto &v=required(row,f.name);if(f.text){if(v.kind!=Json::String||v.text.empty()||v.text.find('\0')!=std::string::npos)throw Failure(f.name+": CHAR 문자열 오류");auto s=convert(v.text,CP_UTF8,p.encoding=="CP949"?949:CP_UTF8);if(s.size()>f.width)throw Failure(f.name+": 고정 바이트 폭 초과");out.insert(out.end(),s.begin(),s.end());out.insert(out.end(),f.width-s.size(),0);}else{auto n=uintValue(v,f.width==4?4294967295ULL:(1ULL<<(f.width*8))-1,f.name);for(unsigned i=f.width;i>0;--i)out.push_back(static_cast<unsigned char>(n>>((i-1)*8)));}}
    }if(out.size()>1024*1024)throw Failure("조립 자료 한도 초과");return out;
}
Json decode(unsigned message,const Bytes &payload,const Profile &p){
    if(extended(message))return decodeExtended(message,payload,p);
    auto fs=fields(message);unsigned width=0;for(auto &f:fs)width+=f.width;
    if(payload.empty()||payload.size()%width)throw Failure("정보 데이터 길이가 표준 레코드 폭("+std::to_string(width)+"바이트)과 다릅니다.");
    Json result;result.kind=Json::Array;
    for(size_t offset=0;offset<payload.size();){Json row;row.kind=Json::Object;
        for(auto &f:fs){if(f.text){auto begin=payload.begin()+offset,end=begin+f.width,nul=std::find(begin,end,0);if(nul==begin||std::any_of(nul,end,[](unsigned char c){return c!=0;}))throw Failure(f.name+": CHAR 값 또는 NUL 패딩 오류");std::string s(begin,nul);setText(row,f.name,convert(s,p.encoding=="CP949"?949:CP_UTF8,CP_UTF8));}else{uint64_t n=0;for(unsigned i=0;i<f.width;++i)n=(n<<8)|payload[offset+i];setNumber(row,f.name,n);}offset+=f.width;}semantic(row,message);result.array.push_back(row);
    }return result;
}
Json fixture(unsigned message,unsigned iteration,unsigned count){
    if(extended(message))return extendedFixture(message,iteration,count);
    Json rows;rows.kind=Json::Array;for(unsigned i=0;i<count;++i){Json row;row.kind=Json::Object;
        for(auto &f:fields(message)){if(f.text)setText(row,f.name,f.name=="LC_NAME"?"시청앞교차로":f.name.find("LAT")!=std::string::npos?"37.566535":"126.977969");else setNumber(row,f.name,0);}
        setNumber(row,"LC_NO",(message==70?1001:101)+i);
        if(message==70){setNumber(row,"START_HOUR",7);setNumber(row,"START_MIN",30);setNumber(row,"CYCLE",120);setNumber(row,"OFFSET",30);for(auto ring:{"ARING_","BRING_"})for(unsigned n=1;n<=8;++n)setNumber(row,std::string(ring)+std::to_string(n)+"PHASE",n%2?25:5);}
        else{setNumber(row,"LC_TYPE",1);setNumber(row,"LC_STATUS",1);setNumber(row,"LC_COUNT",iteration%256);setNumber(row,"LC_A_FLONUMBER",1);setNumber(row,"LC_B_FLONUMBER",2);}rows.array.push_back(row);
    }return rows;
}
Json Assembler::accept(const Frame &f,const Profile &p,bool &complete){
    complete=false;if(f.sequence!=next)throw Failure("정보 프레임 SeqNo가 순차 증가 규칙과 다릅니다.");next=(next+1)&255;
    if(f.flag==2){if(pending)throw Failure("분할 정보가 끝나기 전에 독립 프레임이 도착했습니다.");if(f.payload.empty()){if(f.message!=70&&f.message!=71&&f.message!=72)throw Failure("이 정보에는 빈 데이터 Heartbeat가 정의되어 있지 않습니다.");complete=true;Json j;j.kind=Json::Array;return j;}complete=true;return decode(f.message,f.payload,p);}
    if(f.flag==0){if(pending)throw Failure("분할 Start 프레임이 중복됐습니다.");if(f.payload.empty())throw Failure("빈 분할 Start 데이터");pending=true;message=f.message;data=f.payload;return {};}
    if(!pending||f.message!=message)throw Failure("대응하는 Start가 없는 End 프레임입니다.");
    data.insert(data.end(),f.payload.begin(),f.payload.end());if(data.size()>1024*1024)throw Failure("분할 조립 크기 한도 초과");auto result=decode(message,data,p);data.clear();pending=false;complete=true;return result;
}
}

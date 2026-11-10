#include "ExtendedCodec.h"
#include "StandardFields.h"
#include <cmath>
#include <cstring>
#include <iomanip>
#include <limits>
#include <locale>
#include <set>
#include <sstream>

namespace signalbinary { namespace {
using rest::Failure;
const Json &get(const Json &j,const std::string &key,Json::Kind kind){auto p=j.get(key);if(!p||p->kind!=kind)throw Failure(key+": 필수 항목 또는 자료형 오류");return *p;}
void num(Json &j,const std::string &k,uint64_t n){j.object[k].kind=Json::Number;j.object[k].text=std::to_string(n);}
void text(Json &j,const std::string &k,const std::string &v){j.object[k].kind=Json::String;j.object[k].text=v;}
void real(Json &j,const std::string &k,double v){if(!std::isfinite(v))throw Failure(k+": NaN/Infinity는 유효 정보로 처리하지 않습니다.");std::ostringstream s;s.imbue(std::locale::classic());s<<std::setprecision(17)<<v;j.object[k].kind=Json::Number;j.object[k].text=s.str();}
uint64_t integer(const Json &j,const std::string &k,unsigned width){const auto &v=get(j,k,Json::Number);if(v.text.empty()||v.text.size()>10||v.text.find_first_not_of("0123456789")!=std::string::npos)throw Failure(k+": 정수 형식 오류");auto n=std::stoull(v.text);if(n>=(1ULL<<(width*8)))throw Failure(k+": 정수 바이트 폭 초과");return n;}
void dateParts(const Json &j,bool upper){auto k=[&](const char *a,const char *b){return upper?b:a;};auto y=integer(j,k("Year","YEAR"),2),m=integer(j,k("Month","MONTH"),1),d=integer(j,k("Day","DAY"),1);const unsigned days[]={31,28,31,30,31,30,31,31,30,31,30,31};if(!y||m<1||m>12||d<1||d>days[m-1]+(m==2&&(y%400==0||(y%4==0&&y%100!=0)))||integer(j,k("Hour","HOUR"),1)>23||integer(j,k("Minute","MINUTE"),1)>59||integer(j,k("Second","SECOND"),1)>59)throw Failure("정보의 날짜·시각 값이 유효하지 않습니다.");}
void dateStrings(const Json &j,unsigned message){if(message==67){auto v=get(j,"CREDATE",Json::String).text;if(v.size()!=8)throw Failure("CREDATE는 채택한 YYYYMMDD 8자리여야 합니다.");rest::standard::timestamp(v+"000000","CREDATE");}else if(message==72){for(auto k:{"OCRN_DT","END_DT"}){auto v=get(j,k,Json::String).text;if(std::string(k)=="END_DT"&&v=="00000000000000")continue;rest::standard::timestamp(v,k);}}}
struct Writer {
 Bytes b;const Profile &p;explicit Writer(const Profile &v):p(v){}
 void u(uint64_t n,unsigned width){for(unsigned i=width;i>0;--i)b.push_back(static_cast<unsigned char>(n>>((i-1)*8)));}
 void value(const Json &j,const std::string &k,unsigned width){u(integer(j,k,width),width);}
 void str(const Json &j,const std::string &k,unsigned width,bool terminated=false){auto s=fixedText(get(j,k,Json::String).text,width,p,terminated);b.insert(b.end(),s.begin(),s.end());}
 void fp(const Json &j,const std::string &k,unsigned width){auto &v=get(j,k,Json::Number);double n;try{n=std::stod(v.text);}catch(...){throw Failure(k+": 부동소수 범위 오류");}if(!std::isfinite(n))throw Failure(k+": 유한한 부동소수 값이 필요합니다.");if(width==4){float f=static_cast<float>(n);if(!std::isfinite(f)||(n!=0&&f==0))throw Failure(k+": FLOAT 범위 초과 또는 0으로 소실");uint32_t bits;std::memcpy(&bits,&f,4);u(bits,4);}else{uint64_t bits;std::memcpy(&bits,&n,8);u(bits,8);}}
 void wide(const Json &j){auto pValue=j.get("viaLinkSeq");if(!pValue||(pValue->kind!=Json::String&&pValue->kind!=Json::Number))throw Failure("viaLinkSeq: 20바이트 정수 입력 오류");auto s=pValue->text;if(s.empty()||s.size()>49||s.find_first_not_of("0123456789")!=std::string::npos)throw Failure("viaLinkSeq: 비부호 10진 정수 형식 오류");Bytes value(20,0);for(char digit:s){unsigned carry=digit-'0';for(int n=19;n>=0;--n){carry+=unsigned(value[n])*10;value[n]=static_cast<unsigned char>(carry);carry>>=8;}if(carry)throw Failure("viaLinkSeq: 20바이트 정수 범위 초과");}b.insert(b.end(),value.begin(),value.end());}
};
struct Reader {
 const Bytes &b;const Profile &p;size_t pos=0;Reader(const Bytes &v,const Profile &x):b(v),p(x){}
 void need(size_t n){if(n>b.size()-pos)throw Failure("가변 개수·데이터 길이가 실제 본문과 다릅니다.");}
 uint64_t u(unsigned width){need(width);uint64_t n=0;for(unsigned i=0;i<width;++i)n=(n<<8)|b[pos++];return n;}
 void value(Json &j,const std::string &k,unsigned width){num(j,k,u(width));}
 void str(Json &j,const std::string &k,unsigned width,bool terminated=false){need(width);Bytes s(b.begin()+pos,b.begin()+pos+width);pos+=width;text(j,k,readFixedText(s,p,terminated));}
 void fp(Json &j,const std::string &k,unsigned width){auto bits=u(width);if(width==4){auto v=static_cast<uint32_t>(bits);float f;std::memcpy(&f,&v,4);real(j,k,f);}else{double d;std::memcpy(&d,&bits,8);real(j,k,d);}}
 void wide(Json &j){need(20);std::string decimal="0";for(unsigned i=0;i<20;++i){unsigned carry=b[pos++];for(auto it=decimal.rbegin();it!=decimal.rend();++it){carry+=unsigned(*it-'0')*256;*it=char('0'+carry%10);carry/=10;}while(carry){decimal.insert(decimal.begin(),char('0'+carry%10));carry/=10;}}text(j,"viaLinkSeq",decimal);}
};
template<class F> void dateFields(F f,bool upper){for(auto pair:{std::make_pair("Year","YEAR"),std::make_pair("Month","MONTH"),std::make_pair("Day","DAY"),std::make_pair("Hour","HOUR"),std::make_pair("Minute","MINUTE"),std::make_pair("Second","SECOND")})f(upper?pair.second:pair.first,std::string(pair.first)=="Year"?2u:1u);}
const std::vector<std::pair<const char *,unsigned>> incidentText={{"EVENT_ID",18},{"EVENT_NM",500},{"INC_TY",2},{"INC_DTL_TY",4},{"OCRN_DT",14},{"END_DT",14},{"OCRN_LOT",20},{"OCRN_LAT",20},{"OCRN_LINK_ID",10},{"CNTRL_TY",1},{"PRGRS_STTS",2}};
void bsmWrite(Writer &w,const Json &j){dateStrings(j,67);w.str(j,"CREDATE",8);w.str(j,"VEH_ID",16);w.str(j,"VEH_NO",8);w.fp(j,"LONGITUDE",8);w.fp(j,"LATITUDE",8);w.fp(j,"ALTITUDE",4);w.fp(j,"ANGLE",4);w.str(j,"GEAR",4);w.fp(j,"SPEED",4);}
void bsmRead(Reader &r,Json &j){r.need(64);r.str(j,"CREDATE",8);r.str(j,"VEH_ID",16);r.str(j,"VEH_NO",8);r.fp(j,"LONGITUDE",8);r.fp(j,"LATITUDE",8);r.fp(j,"ALTITUDE",4);r.fp(j,"ANGLE",4);r.str(j,"GEAR",4);r.fp(j,"SPEED",4);dateStrings(j,67);}
}
Bytes encodeExtended(unsigned message,const Json &records,const Profile &p){
 static_assert(sizeof(float)==4&&sizeof(double)==8&&std::numeric_limits<float>::is_iec559&&std::numeric_limits<double>::is_iec559,"IEEE 754 is required");
 if(records.kind!=Json::Array||records.array.empty())throw Failure("정보 레코드 배열이 비어 있습니다.");Writer w(p);
 if(message==71&&records.array.size()!=1)throw Failure("최적경로는 하나의 공통 헤더와 차량 목록을 사용합니다.");
 for(auto &j:records.array){if(j.kind!=Json::Object)throw Failure("정보 레코드는 객체여야 합니다.");
  if(message==67)bsmWrite(w,j);
  else if(message==71){dateParts(j,false);dateFields([&](const char *k,unsigned n){w.value(j,k,n);},false);w.fp(j,"lot",8);w.fp(j,"lat",8);auto &vehicles=get(j,"pol6IndivAdInfoDtoList",Json::Array);auto count=integer(j,"indivAdIdNo",1);if(count!=vehicles.array.size())throw Failure("indivAdIdNo와 개별차량 개수가 다릅니다.");w.u(count,1);for(auto &vehicle:vehicles.array){w.str(vehicle,"indivAdId",10);w.str(vehicle,"linkId",10);w.value(vehicle,"linkPos",3);w.value(vehicle,"linkInfoType",1);auto &links=get(vehicle,"pol6RouteIntoDtoList",Json::Array);auto n=integer(vehicle,"viaLinkNo",1);if(n!=links.array.size())throw Failure("viaLinkNo와 경유 개수가 다릅니다.");w.u(n,1);for(auto &link:links.array){w.wide(link);w.str(link,"viaLinkId",3);w.value(link,"viaLinkTurn",1);}}}
  else if(message==72){dateParts(j,true);dateStrings(j,72);dateFields([&](const char *k,unsigned n){w.value(j,k,n);},true);for(auto &f:incidentText)w.str(j,f.first,f.second,std::string(f.first)=="EVENT_NM");auto &links=get(j,"EVENT_CTRL",Json::Array);auto n=integer(j,"LINK_COUNT",1);if(n!=links.array.size())throw Failure("LINK_COUNT와 통제 링크 개수가 다릅니다.");w.u(n,1);for(auto &link:links.array)w.str(link,"LINK_ID",10);}
  else throw Failure("지원하지 않는 정보 번호");
 }if(w.b.size()>1024*1024)throw Failure("정보 조립 한도 초과");return w.b;
}
Json decodeExtended(unsigned message,const Bytes &payload,const Profile &p){
 if(payload.empty())throw Failure("업무 정보 본문이 없습니다.");Reader r(payload,p);Json result;result.kind=Json::Array;
 while(r.pos<payload.size()){Json j;j.kind=Json::Object;
  if(message==67)bsmRead(r,j);
  else if(message==71){r.need(24);dateFields([&](const char *k,unsigned n){r.value(j,k,n);},false);dateParts(j,false);r.fp(j,"lot",8);r.fp(j,"lat",8);auto count=r.u(1);num(j,"indivAdIdNo",count);auto &vehicles=j.object["pol6IndivAdInfoDtoList"];vehicles.kind=Json::Array;r.need(static_cast<size_t>(count)*25);for(unsigned i=0;i<count;++i){Json v;v.kind=Json::Object;r.str(v,"indivAdId",10);r.str(v,"linkId",10);r.value(v,"linkPos",3);r.value(v,"linkInfoType",1);auto n=r.u(1);num(v,"viaLinkNo",n);auto &links=v.object["pol6RouteIntoDtoList"];links.kind=Json::Array;r.need(static_cast<size_t>(n)*24);for(unsigned k=0;k<n;++k){Json link;link.kind=Json::Object;r.wide(link);r.str(link,"viaLinkId",3);r.value(link,"viaLinkTurn",1);links.array.push_back(link);}vehicles.array.push_back(v);}if(r.pos!=payload.size())throw Failure("최적경로 차량 목록 뒤에 잉여 바이트가 있습니다.");}
  else if(message==72){r.need(613);dateFields([&](const char *k,unsigned n){r.value(j,k,n);},true);dateParts(j,true);for(auto &f:incidentText)r.str(j,f.first,f.second,std::string(f.first)=="EVENT_NM");dateStrings(j,72);auto count=r.u(1);num(j,"LINK_COUNT",count);r.need(static_cast<size_t>(count)*10);auto &links=j.object["EVENT_CTRL"];links.kind=Json::Array;for(unsigned i=0;i<count;++i){Json link;link.kind=Json::Object;r.str(link,"LINK_ID",10);links.array.push_back(link);}}
  else throw Failure("지원하지 않는 정보 번호");result.array.push_back(j);
 }return result;
}
Json extendedFixture(unsigned message,unsigned iteration,unsigned count){
 Json result;result.kind=Json::Array;unsigned documents=message==71?1:count;
 for(unsigned i=0;i<documents;++i){Json j;j.kind=Json::Object;
  if(message==67){text(j,"CREDATE","20260925");text(j,"VEH_ID","AV000000000000"+std::to_string(10+i));text(j,"VEH_NO","12A3456");real(j,"LONGITUDE",126.9784);real(j,"LATITUDE",37.5665);real(j,"ALTITUDE",35.5);real(j,"ANGLE",90.0);text(j,"GEAR","D");real(j,"SPEED",45.5+iteration*.5);}
  else {bool upper=message==72;dateFields([&](const char *k,unsigned){num(j,k,std::string(k)==(upper?"YEAR":"Year")?2026:std::string(k)==(upper?"MONTH":"Month")?9:std::string(k)==(upper?"DAY":"Day")?25:std::string(k)==(upper?"HOUR":"Hour")?10:std::string(k)==(upper?"MINUTE":"Minute")?30:iteration%60);},upper);
   if(message==71){real(j,"lot",126.9784);real(j,"lat",37.5665);num(j,"indivAdIdNo",count);auto &vehicles=j.object["pol6IndivAdInfoDtoList"];vehicles.kind=Json::Array;for(unsigned n=0;n<count;++n){Json v;v.kind=Json::Object;text(v,"indivAdId","CAR00000"+std::to_string(10+n));text(v,"linkId","LINK0000"+std::to_string(10+n));num(v,"linkPos",150+iteration);num(v,"linkInfoType",1);num(v,"viaLinkNo",2);auto &links=v.object["pol6RouteIntoDtoList"];links.kind=Json::Array;for(unsigned k=0;k<2;++k){Json link;link.kind=Json::Object;text(link,"viaLinkSeq",std::to_string(k+1));text(link,"viaLinkId",std::to_string(101+k));num(link,"viaLinkTurn",k);links.array.push_back(link);}vehicles.array.push_back(v);}}
   else{text(j,"EVENT_ID","INC2026092500000"+std::to_string(10+i));text(j,"EVENT_NM",iteration?"교통사고 상태 변경":"교통사고 발생");text(j,"INC_TY","01");text(j,"INC_DTL_TY","0101");text(j,"OCRN_DT","20260925103000");text(j,"END_DT","00000000000000");text(j,"OCRN_LOT","126.978400");text(j,"OCRN_LAT","37.566500");text(j,"OCRN_LINK_ID","1234567890");text(j,"CNTRL_TY","1");text(j,"PRGRS_STTS","01");num(j,"LINK_COUNT",2);auto &links=j.object["EVENT_CTRL"];links.kind=Json::Array;for(unsigned n=0;n<2;++n){Json link;link.kind=Json::Object;text(link,"LINK_ID",std::to_string(1234567890ULL+n));links.array.push_back(link);}}
  }result.array.push_back(j);
 }return result;
}
size_t informationCount(unsigned message,const Json &rows){if(rows.kind!=Json::Array)return 0;if(message==71){size_t n=0;for(auto &r:rows.array)n+=get(r,"pol6IndivAdInfoDtoList",Json::Array).array.size();return n;}return rows.array.size();}
size_t distinctInformationCount(unsigned message,const Json &rows){std::set<std::string> ids;for(auto &r:rows.array){if(message==71){for(auto &v:get(r,"pol6IndivAdInfoDtoList",Json::Array).array)ids.insert(get(v,"indivAdId",Json::String).text);}else{auto p=r.get(message==67?"VEH_ID":message==72?"EVENT_ID":"LC_NO");if(!p)throw Failure("자료 식별값 누락");ids.insert(p->text);}}return ids.size();}
}

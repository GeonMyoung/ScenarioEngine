#include "SmartTraffic.h"
#include <algorithm>
#include <windows.h>

namespace rest {
namespace {
void timestamp(const std::string &s,const std::string &where){
    if(s.size()!=14||s.find_first_not_of("0123456789")!=std::string::npos)throw Failure(where+": 수집일시 YYYYMMDDhhmmss 형식 오류");
    int y=std::stoi(s.substr(0,4)),m=std::stoi(s.substr(4,2)),d=std::stoi(s.substr(6,2));
    const int days[]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(!y||m<1||m>12||d<1||d>days[m-1]+(m==2&&(y%400==0||(y%4==0&&y%100!=0)))||std::stoi(s.substr(8,2))>23||std::stoi(s.substr(10,2))>59||std::stoi(s.substr(12,2))>59)
        throw Failure(where+": 수집일시 범위 오류");
}
// NUMBER(p,s) is checked as an exact decimal value, without floating-point
// rounding. Signs and code enumerations are not specified by table 4-23.
void decimal(const std::string &value,int precision,int scale,const std::string &where){
    auto e=value.find_first_of("eE");auto mantissa=value.substr(0,e);long long exponent=0;
    if(e!=std::string::npos){
        auto exp=value.substr(e+1);bool minus=!exp.empty()&&exp[0]=='-';
        for(char c:exp)if(c>='0'&&c<='9')exponent=std::min(2000000LL,exponent*10+c-'0');
        if(minus)exponent=-exponent;
    }
    auto dot=mantissa.find('.');if(dot!=std::string::npos)exponent-=static_cast<long long>(mantissa.size()-dot-1);
    std::string digits;for(char c:mantissa)if(c>='0'&&c<='9')digits+=c;
    auto first=digits.find_first_not_of('0');if(first==std::string::npos)return;digits.erase(0,first);
    while(!digits.empty()&&digits.back()=='0'){digits.pop_back();++exponent;}
    auto fractional=std::max(0LL,-exponent),integral=std::max(0LL,static_cast<long long>(digits.size())+exponent);
    if(fractional>scale||integral>precision-scale)throw Failure(where+": 숫자 자릿수/소수 자릿수 범위 오류 NUMBER("+std::to_string(precision)+","+std::to_string(scale)+")");
}
}
std::string defaultSmartFixture(){
    return R"JSON([{"collectDate":"20260811153000","nodeId":"NODE000001","linkId":"LINK000001","ascrId":"ASCR000001","laneNo":1,"vkndCd":1,"spd":42.50,"vol":15}])JSON";
}
size_t validateSmartResponse(const HttpResponse &r){
    if(r.status!=200)throw Failure("스마트교차로 정상 응답 코드 불일치: HTTP 200 필요");
    auto media=r.contentType;std::transform(media.begin(),media.end(),media.begin(),[](unsigned char c){return static_cast<char>(std::tolower(c));});
    media=media.substr(0,media.find(';'));while(!media.empty()&&media.back()==' ')media.pop_back();
    if(media!="application/json")throw Failure("스마트교차로 Content-Type 불일치: application/json 필요");
    if(r.body.empty()||r.body.size()>1024*1024||!MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,r.body.data(),static_cast<int>(r.body.size()),nullptr,0))throw Failure("스마트교차로 본문 크기 또는 UTF-8 오류");
    auto root=Json::parse(r.body,1024*1024);if(root.kind!=Json::Array)throw Failure("스마트교차로 JSON 최상위는 표준 예시의 배열이어야 합니다.");
    for(size_t n=0;n<root.array.size();++n){
        const auto &row=root.array[n];auto where="스마트교차로["+std::to_string(n)+"].";
        if(row.kind!=Json::Object)throw Failure(where+"JSON 레코드는 객체여야 합니다.");
        for(auto key:{"collectDate","nodeId","linkId","ascrId","laneNo","vkndCd","spd","vol"})if(!row.get(key))throw Failure(where+key+": 필수 필드 누락");
        for(auto key:{"collectDate","nodeId","linkId","ascrId"}){
            const auto &v=*row.get(key);
            if(v.kind!=Json::String)throw Failure(where+key+": 자료형 불일치, 문자열 필요");
            if(v.text.empty())throw Failure(where+key+": 필수 필드 값이 비어 있습니다.");
            if(std::string(key)=="collectDate")timestamp(v.text,where+key);
            else{
                size_t chars=0;for(unsigned char c:v.text)if((c&0xc0)!=0x80)++chars;
                if(chars>10)throw Failure(where+key+": 문자열 길이 초과 VARCHAR(10)");
            }
        }
        for(auto key:{"laneNo","vkndCd","spd","vol"}){
            const auto &v=*row.get(key);if(v.kind!=Json::Number)throw Failure(where+key+": 자료형 불일치, 숫자 필요");
            bool speed=std::string(key)=="spd",volume=std::string(key)=="vol";
            decimal(v.text,speed?5:volume?7:1,speed?2:0,where+key);
        }
    }
    return root.array.size();
}
}

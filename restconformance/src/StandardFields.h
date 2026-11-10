#pragma once
#include "RestCore.h"
#include <algorithm>
#include <windows.h>

namespace rest { namespace standard {
inline size_t characters(const std::string &s) {
    if (s.empty()) return 0;
    if (!MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, s.data(), static_cast<int>(s.size()), nullptr, 0))
        throw Failure("유효하지 않은 UTF-8 문자열");
    size_t count=0;
    for (unsigned char c:s) if ((c&0xc0)!=0x80) ++count;
    return count;
}
inline void text(const std::string &s,size_t limit,const std::string &where,bool required=true) {
    if (required && s.empty()) throw Failure(where+": 필수 필드 값이 비어 있습니다.");
    if (characters(s)>limit) throw Failure(where+": 문자열 길이 초과 (최대 "+std::to_string(limit)+"자)");
}
inline void timestamp(const std::string &s,const std::string &where) {
    if (s.size()!=14 || s.find_first_not_of("0123456789")!=std::string::npos)
        throw Failure(where+": 수집일시 YYYYMMDDhhmmss 형식 오류");
    int y=std::stoi(s.substr(0,4)),m=std::stoi(s.substr(4,2)),d=std::stoi(s.substr(6,2));
    const int days[]={31,28,31,30,31,30,31,31,30,31,30,31};
    if (!y || m<1 || m>12 || d<1 || d>days[m-1]+(m==2&&(y%400==0||(y%4==0&&y%100!=0))) ||
        std::stoi(s.substr(8,2))>23 || std::stoi(s.substr(10,2))>59 || std::stoi(s.substr(12,2))>59)
        throw Failure(where+": 수집일시 범위 오류");
}
// NUMBER(p,s) uses exact decimal values, not rounded double values. Equivalent
// trailing-zero/exponent spellings are accepted. The tables define no sign or
// geographical/business range restriction beyond precision and scale.
inline void decimal(const std::string &value,int precision,int scale,const std::string &where) {
    size_t pos=0;std::string digits;long long fraction=0,exponent=0;
    auto digit=[](char c){return c>='0'&&c<='9';};
    auto invalid=[&](){throw Failure(where+": 숫자 형식 오류");};
    if (pos<value.size() && (value[pos]=='+'||value[pos]=='-')) ++pos;
    size_t start=pos;
    while (pos<value.size()&&digit(value[pos])) digits+=value[pos++];
    if (pos==start) invalid();
    if (pos<value.size()&&value[pos]=='.') {
        start=++pos;
        while (pos<value.size()&&digit(value[pos])) {digits+=value[pos++];++fraction;}
        if (pos==start) invalid();
    }
    if (pos<value.size()&&(value[pos]=='e'||value[pos]=='E')) {
        ++pos;bool negative=false;
        if (pos<value.size()&&(value[pos]=='+'||value[pos]=='-')) negative=value[pos++]=='-';
        start=pos;
        while (pos<value.size()&&digit(value[pos])) exponent=std::min(2000000LL,exponent*10+value[pos++]-'0');
        if (pos==start) invalid();
        if (negative) exponent=-exponent;
    }
    if (pos!=value.size()) invalid();
    exponent-=fraction;
    auto first=digits.find_first_not_of('0');
    if (first==std::string::npos) return;
    digits.erase(0,first);
    while (digits.back()=='0') {digits.pop_back();++exponent;}
    auto fractional=std::max(0LL,-exponent),integral=std::max(0LL,static_cast<long long>(digits.size())+exponent);
    if (fractional>scale||integral>precision-scale)
        throw Failure(where+": 숫자 자릿수/소수 자릿수 범위 오류 NUMBER("+std::to_string(precision)+","+std::to_string(scale)+")");
}
} }

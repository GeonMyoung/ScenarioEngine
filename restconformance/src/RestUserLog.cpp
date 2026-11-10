#include "../../interfaceconformance/include/UserLog.h"
#include "RestUserLog.h"
#include <filesystem>
#include <algorithm>

namespace rest {
namespace {
std::string provider(const MethodConfig &c){return c.weather?"기상청":c.shadow?"음영구간 미시교통정보 플랫폼":c.ntic?"국가교통정보센터(NTIC)":c.xml?"UTIC":"통합교통관제시스템";}
std::string requester(const MethodConfig &c){return c.weather?"통합교통관제시스템":c.shadow?"통합교통관제시스템":c.ntic?"통합교통관제시스템":c.xml?"통합교통관제시스템":"미시교통정보 플랫폼";}
std::string target(const MethodConfig &c){return c.provider?provider(c):requester(c);}
std::string peer(const MethodConfig &c){return c.provider?requester(c):provider(c);}
std::string information(const MethodConfig &c){return c.weather?"기상정보":c.shadow?"음영구간 미시교통정보":c.ntic?"NTIC 차량검지정보":c.xml?"돌발정보":c.smart?"스마트교차로 1분 교통정보":"VDS 차로별 원시정보 이력";}
std::string informationObject(const MethodConfig &c){return information(c)+(c.xml?"를":"을");}
std::string format(const MethodConfig &c){return c.xml?"XML":"JSON";}
std::string path(const MethodConfig &c){return c.weather?c.weatherOptions.path:c.shadow?ShadowPath:c.ntic?c.nticPath:c.xml?UticPath:c.smart?SmartPath:VdsPath;}
std::string code(unsigned value){
    auto text=value==200?"HTTP 성공 상태":value==204?"본문 없는 응답":value==400?"잘못된 요청":value==401?"인증 필요":value==403?"접근 거부":value==404?"찾을 수 없음":value==422?"요청 내용 오류":value==500?"서버 오류":"응답";
    return "HTTP "+std::to_string(value)+"("+text+")";
}
std::string progress(unsigned n,unsigned total){return std::to_string(n)+"/"+std::to_string(total)+"회";}
std::string safe(std::string text,const std::string &credential,size_t limit=90){
    for(const auto &secret:{"INVALID-"+credential,credential})if(!secret.empty()){
        size_t pos=0;while((pos=text.find(secret,pos))!=std::string::npos){text.replace(pos,secret.size(),"[비공개]");pos+=std::string("[비공개]").size();}}
    for(char &c:text)if(static_cast<unsigned char>(c)<32)c=' ';
    if(text.size()>limit){size_t cut=limit;while(cut&&((static_cast<unsigned char>(text[cut])&0xc0)==0x80))--cut;text=text.substr(0,cut)+"…";}
    return text;
}
std::string field(const std::string &reason){
    const std::pair<const char *,const char *> fields[]={
        {"baseDate","발표일자(baseDate)"},{"updateDt","발표시각(updateDt)"},{"adstrdCode","표준의 날짜 항목(adstrdCode)"},{"fcstTime","발표시각(fcstTime)"},{"t1h","기온(t1h)"},{"rn1","강수량(rn1)"},{"sky","하늘상태(sky)"},{"uuu","동서 바람성분(uuu)"},{"vvv","남북 바람성분(vvv)"},{"reh","습도(reh)"},{"pty","강수형태(pty)"},{"lgt","표준의 풍향 항목(lgt)"},{"vec","풍향(vec)"},{"wsd","풍속(wsd)"},{"nx","예보지점 X 좌표(nx)"},{"ny","예보지점 Y 좌표(ny)"},
        {"colctedDate","수집일시(colctedDate)"},{"linkIds","링크 ID(linkIds)"},{"speed","속도(speed)"},{"volume","교통량(volume)"},{"occupancy","점유율(occupancy)"},{"resultCode","응답결과코드(resultCode)"},{"resultMsg","응답 메시지(resultMsg)"},{"totalCount","총 건수(totalCount)"},{"incidentId","돌발정보 ID(incidentId)"},{"incidenteTypeCd","돌발유형(incidenteTypeCd)"},{"incidentTitle","돌발정보 제목(incidentTitle)"},
        {"startDate","시작일시(startDate)"},{"endDate","종료일시(endDate)"},{"updateDate","갱신일시(updateDate)"},
        {"sourceCode","소스코드(sourceCode)"},{"locationTypeCd","좌표유형(locationTypeCd)"},{"locationDataX","경도(locationDataX)"},{"locationDataY","위도(locationDataY)"},{"locationData","좌표정보(locationData)"},{"collectDate","수집일시(collectDate)"},
        {"nodeId","노드 ID(nodeId)"},{"ascrId","접근로 ID(ascrId)"},{"vkndCd","차종 코드(vkndCd)"},{"stnId","지점 ID(stnId)"},{"laneNo","차로 번호(laneNo)"},{"volS","소형차 교통량(volS)"},{"volM","중형차 교통량(volM)"},{"volL","대형차 교통량(volL)"},
        {"vol","교통량(vol)"},{"spd","속도(spd)"},{"occ","점유율(occ)"},{"errCode","오류 코드(errCode)"},{"linkId","링크 ID(linkId)"},{"vdsId","VDS ID(vdsId)"},{"stnLocation","지점명(stnLocation)"},{"code","오류 코드(code)"},{"message","오류 안내(message)"},{"request","요청 정보(request)"}};
    for(const auto &f:fields)if(reason.find(f.first)!=std::string::npos)return f.second;
    return "해당 정보 항목";
}
std::string authentication(const MethodConfig &c,const MethodItem &i){
    if(c.shadow)return "현재 시험 요청은 인증정보를 전송하지 않습니다(명세에 별도 인증 규칙 미기재).";
    std::string mechanism=c.weather?"요청변수 "+c.weatherOptions.keyName+"의 API 키":c.ntic?"요청변수 apiKey의 API 키":c.xml?"요청변수 key의 API 키":"Authorization 헤더의 Bearer 인증";
    if(c.provider&&i.key=="test_missing_credential")return mechanism+" 미포함";
    if(c.provider&&i.key=="test_wrong_credential")return mechanism+"에 의도적으로 잘못된 값 사용(값 비공개)";
    return mechanism+" 포함(값 비공개)";
}
std::string inputCondition(const MethodConfig &c,const MethodItem &i){
    if(!c.provider){
        if(i.check=="normal")return "대상의 유효한 GET 요청을 받고 표준 데이터의 정상 응답을 제공합니다.";
        if(i.check=="malformed")return "대상의 유효한 GET 요청에 HTTP "+std::to_string(i.expected)+"와 구문이 손상된 "+format(c)+" 본문을 제공합니다.";
        if(i.check=="empty")return "대상의 유효한 GET 요청에 정보가 없는 정상 응답을 제공합니다.";
        if(i.check=="absence-error")return "대상의 유효한 GET 요청에 자료 부재 조건의 오류 응답을 제공합니다.";
        return "대상의 유효한 GET 요청에 선택한 HTTP "+std::to_string(i.expected)+" 오류응답 조건을 적용합니다.";
    }
    if(i.key=="test_invalid_request"){
        if(c.weather)return "nx=invalid: 정수여야 하는 조회변수에 문자열을 넣습니다.";
        if(c.shadow)return "latest=501: 명세의 허용 상한 500을 초과하는 값을 넣습니다.";
        if(c.ntic)return "getType=unsupported: 지원하지 않는 출력 형식 값을 넣습니다.";
        if(c.xml)return "협의한 오류 입력: 같은 key 요청변수를 두 번 넣습니다(값 비공개).";
        return "협의한 오류 입력: 정상 경로에 unsupported=1 요청변수를 추가합니다.";
    }
    if(i.key=="test_missing_credential")return "정상 경로에 인증정보를 제외한 GET 요청을 보냅니다.";
    if(i.key=="test_wrong_credential")return "정상 경로에 의도적으로 잘못된 인증정보를 사용한 GET 요청을 보냅니다.";
    if(i.key=="test_missing_path")return "정상 URL 경로 뒤에 /not-found를 붙여 GET 요청을 보냅니다.";
    if(i.check=="absence-error")return "같은 유효 API의 대상 자료를 0건으로 준비하고 정상 GET 요청을 보냅니다.";
    if(i.key=="test_no_data")return "같은 유효 API에서 빈 정상응답 조건을 준비하고 정상 GET 요청을 보냅니다.";
    return "명세의 URL 경로·요청변수·인증 조건에 맞는 GET 요청을 보냅니다.";
}
std::string inputBasis(const MethodConfig &c,const MethodItem &i){
    if(!c.provider&&i.check!="normal")return "유효한 요청은 API 명세를 따르며, 제공할 오류·빈 응답 조건은 협의하여 선택한 시험 조건입니다.";
    if(i.key=="test_invalid_request"){
        if(c.shadow)return "API 명세의 latest 정수 범위 0~500을 적용합니다.";
        if(c.weather)return "기상 API의 nx 정수 조건을 적용합니다.";
        if(c.ntic)return "NTIC API의 getType 출력 형식 정의를 적용합니다.";
        return "명세에 이 입력을 반드시 거부하라는 규칙은 없습니다. 사전에 협의해 적용하는 오류 입력 조건입니다.";
    }
    if(i.check=="absence-error")return "제4부의 자료 부재 시 오류응답 요구와 해당 자료 0건의 준비 조건을 연결합니다.";
    if(i.check=="normal")return "API 호출 규칙은 명세, 업무 데이터는 제3부 정보연계 규격을 기준으로 합니다.";
    return "인증·경로·자료 상태를 바꾸어 확인하는 선택 가능한 추가 시험 조건입니다.";
}
std::string responseBasis(const MethodConfig &c,const MethodItem &i){
    if(i.check=="normal")return "정상 응답의 호출·업무 데이터 기준을 적용합니다. 미정 포장과 표준/API 차이는 채택한 시험 기준으로 구분합니다.";
    if(c.shadow&&i.check=="shadow-error")return "OpenAPI에 정의된 HTTP 422와 오류 JSON 구조를 적용합니다.";
    if(c.weather&&(i.check=="weather-error"||i.check=="absence-error"))return "업무 결과코드는 기상 API 가이드, HTTP 상태와 업무코드의 조합은 현재 시험 설정을 적용합니다.";
    if(c.ntic&&(i.check=="ntic-error"||i.check=="absence-error"))return i.check=="absence-error"?"자료 부재의 HTTP 상태·오류 메시지는 명세 미정 부분에 적용한 협의 시험 기준입니다.":"업무 결과코드는 NTIC API 가이드, HTTP 상태 매핑은 명세 미정 부분에 적용한 협의 시험 기준입니다.";
    if(!c.xml&&!c.shadow&&!c.ntic&&!c.weather&&(i.expected==400||i.expected==500))return "API 명세에 해당 HTTP 오류 코드가 있습니다. 이 입력에 해당 코드를 연결하는 조건과 본문 검사 범위는 현재 상세시험 기준입니다.";
    if(i.check=="malformed")return "HTTP 상태와 손상 본문의 조합은 협의하여 선택한 시험기 제공 조건입니다.";
    return "명세 미정 응답 또는 추가 조건에 적용한 시험 기준입니다. 기대 상태는 현재 시험 설정을 사용합니다.";
}
std::string businessResponse(const MethodConfig &c,const MethodItem &i){
    if(c.weather&&(i.check=="weather-error"||i.check=="absence-error"))return "response.header.resultCode="+weatherResultCode(i.key)+" 및 오류 메시지";
    if(c.ntic&&(i.check=="ntic-error"||i.check=="absence-error")){
        auto v=nticResultCode(i.key);return v.empty()?"자료 부재 오류 메시지 확인; 업무 결과코드 값은 미정":"resultCode="+v+" 및 오류 메시지";
    }
    return "업무 데이터·본문 검사는 해당 항목의 판정 기준을 따릅니다.";
}
std::string intent(const MethodConfig &c,const MethodItem &item){
    if(!c.provider)return inputCondition(c,item)+" 자동 판정은 대상 요청의 유효성과 시험기의 응답 전송 완료를 확인합니다.";
    if(item.check=="normal")return "유효한 요청에 대해 "+informationObject(c)+" 정해진 형식으로 제공하는지 확인합니다.";
    return inputCondition(c,item)+" 실제 수신한 응답을 협의한 기대응답과 비교합니다.";
}
std::string criteria(const MethodConfig &c,const MethodItem &item){
    std::string s=std::string(c.provider?"기대 응답은 ":"대상에 제공할 응답은 ")+code(item.expected)+"입니다. ";
    if(item.check=="normal")s+=c.weather?"제3부 표 4-15의 필수 16개 항목, 날짜·시각, 숫자 자릿수·정수 범위·코드를 검사합니다. API 계층의 결과코드 00과 페이지 메타데이터도 확인합니다.":c.shadow?"제3부 표 4-21의 필수 6개 항목, 14자리 시각과 정수 유효범위를 확인합니다. 실제 누적 커서·필터 결과와 1분 연계주기는 이 단일 요청 형식검사의 판정 범위에 포함하지 않습니다.":c.ntic?"제3부 표 4-12의 필수 7개 항목·수집일시·ID 길이·숫자 자릿수를 확인합니다. API 문자열 예시를 숫자로 자동 변환하지 않습니다.":c.smart?"제3부 표 4-23의 8개 필수 항목, 수집일시, 식별값 길이와 숫자 자릿수를 확인합니다.":c.xml?"제3부 표 4-16의 필수 항목·일시·길이·코드와 좌표 숫자 자릿수를 확인합니다. 선택 필드는 제공된 경우 검사합니다.":"제3부 표 4-22의 수집일시·문자열 길이·숫자 자릿수를 확인합니다. 선택 교통량은 제공된 경우 정수·자릿수를 검사합니다.";
    else if(c.weather&&(item.check=="weather-error"||item.check=="absence-error"))s+="HTTP 상태와 별도로 본문의 업무 결과코드 "+weatherResultCode(item.key)+"와 오류 메시지를 확인합니다. 03은 자료 부재 오류이며 HTTP 200이라도 정상 정보로 분류하지 않습니다. HTTP와 업무 코드의 매핑은 시험 설정입니다.";
    else if(item.check=="shadow-error")s+="API 명세의 HTTP 422와 오류 JSON 구조를 확인합니다. detail은 선택이며, 제공된 항목은 loc·msg·type의 필수 여부와 자료형을 검사합니다.";
    else if(item.check=="ntic-error")s+="HTTP 상태와 별도로 NTIC 본문의 응답결과코드(resultCode) "+nticResultCode(item.key)+" 및 오류 메시지를 확인합니다.";
    else if(item.check=="error-schema")s+="API 명세의 오류 JSON 객체와 제공된 필드의 자료형·오류 발생 시각 형식을 확인합니다.";
    else if(item.check=="absence-error")s+="200 빈 배열이나 204를 오류응답으로 인정하지 않습니다. 선택한 HTTP 오류 코드는 시험 profile이며 표준의 고정 코드가 아닙니다. 자료 부재 준비 조건에서 정상 경로·요청과 오류응답을 확인합니다.";
    else if(item.check=="empty")s+=c.xml?"XML result 안에 돌발정보 record가 없는지 확인합니다.":"JSON 배열에 정보가 없는지 확인합니다.";
    else if(item.check=="malformed")s+="잘못된 "+format(c)+" 본문을 시험 조건대로 전송합니다. 대상의 실제 파싱 오류·업무 미반영 여부는 직접 관측하지 않습니다.";
    else if(item.expected==204)s+="응답 본문이 비어 있어야 합니다.";
    else s+="이 항목은 HTTP 응답 코드로 확인하고 본문은 증거로 보관합니다.";
    if(c.provider&&(!c.xml&&!c.smart&&!c.ntic&&!c.shadow&&!c.weather&&item.key=="test_invalid_request"))s+=" 400은 API 명세에 정의된 값입니다.";
    else if(item.check!="normal"&&item.check!="error-schema"&&item.check!="shadow-error"&&item.check!="weather-error"&&item.check!="malformed")s+=" 이번 시험에서 정한 판정 기준을 적용합니다.";
    return s;
}
std::string evidence(const MethodConfig &c,const MethodItem &item){
    return "자동 판정 범위: "+std::string(c.provider?"시험기가 수신한 응답의 코드·형식·항목값을 검사합니다. ":"대상의 요청 유효성과 시험기의 응답 전송 완료를 검사합니다. ")+unobservedScope(c,item)+" 별도 자료 제출 없이 자동 검증 결과로 종료합니다.";
}
}
std::string userCaseDefinition(const MethodConfig &c,const MethodItem &i){
    auto requestPath=path(c)+(c.provider&&i.key=="test_missing_path"?"/not-found":"");
    return "{\"요청 방식\":"+quote("GET "+requestPath)+",\"인증 방식\":"+quote(authentication(c,i))+
        ",\"입력 조건\":"+quote(inputCondition(c,i))+",\"입력 기준 출처\":"+quote(inputBasis(c,i))+
        ",\"HTTP 응답 기준\":"+quote(std::string(c.provider?"대상에서 수신할 ":"시험기가 제공할 ")+code(i.expected))+
        ",\"업무 응답 기준\":"+quote(businessResponse(c,i))+",\"응답 기준 출처\":"+quote(responseBasis(c,i))+"}";
}
std::string userSetupSummary(const MethodConfig &c){
    return "시험 준비: 대상은 "+target(c)+", 시험 시스템은 "+peer(c)+" 역할입니다. "+information(c)+" 연계의 "+std::to_string(c.items.size())+"개 항목을 선택했으며 항목마다 "+std::to_string(c.repetitions)+"회 확인합니다.";
}
std::string userError(const std::string &r){
    auto has=[&](const char *s){return r.find(s)!=std::string::npos;};
    if(has("NTIC 응답결과코드"))return r;
    if(has("totalCount와"))return "응답의 총 건수(totalCount)와 실제 정보 건수가 다릅니다.";
    if(has("정보요청 대기 시간 초과"))return "제한시간 안에 대상의 요청을 받지 못했습니다. 대상에 설정된 시험 시스템 주소와 요청 실행 여부를 확인하세요.";
    if(has("HTTP 응답 수신 실패"))return "대상 시스템의 응답을 받지 못했습니다. 접속 주소, 서비스 실행 상태, 연결 및 응답 제한시간을 확인하세요.";
    if(has("기상정보 업무 결과코드")||has("기상정보 정상 업무 결과코드"))return r+" HTTP 상태와 본문의 업무 결과코드를 각각 확인하세요.";
    if(has("기상정보 응답 페이지"))return "응답의 페이지 번호·페이지당 건수·총 건수 또는 실제 자료 건수가 요청 조건과 다릅니다. 페이지 정보를 확인하세요.";
    if(has("HTTP 응답 코드 불일치"))return "대상이 기대한 응답 코드를 반환하지 않았습니다. 요청 조건에 해당하는 응답 규칙을 확인하세요.";
    if(has("필수 필드"))return "응답에 필요한 "+field(r)+"이 없거나 비어 있습니다. 제공 데이터의 필수 항목을 확인하세요.";
    if(has("자료형")||has("정수 형식"))return "응답의 "+field(r)+" 자료형이 기준과 다릅니다. 숫자·문자열 구분과 값의 범위를 확인하세요.";
    if(has("일시")||has("date-time")||has("time 범위")||has("YYYYMMDD")||has("hhmmss"))return "응답의 "+field(r)+" 날짜·시각 형식 또는 값이 올바르지 않습니다. 실제 날짜와 명세의 표기 형식을 확인하세요.";
    if(has("Content-Type"))return "응답에 표시된 본문 형식이 기준과 다릅니다. HTTP Content-Type과 실제 XML·JSON 형식을 확인하세요.";
    if(has("필드 중복")||has("JSON 중복"))return "응답에 같은 정보 항목이 중복되어 있습니다. 중복 필드를 확인하세요.";
    if(has("UTF-8"))return "응답의 문자 인코딩을 읽을 수 없거나 본문 크기가 허용 범위를 벗어났습니다. UTF-8 인코딩과 전송 크기를 확인하세요.";
    if(has("JSON")||has("XML")||has("본문 형식"))return "응답 본문을 요구된 정보 구조로 읽을 수 없습니다. XML·JSON 구문, 최상위 구조와 필드 구성을 확인하세요.";
    if(has("정상 응답에")||has("비어 있지 않은 자료"))return "받은 정보의 유무가 이번 시험 조건과 다릅니다. 정상 시험에는 자료를, 자료 부재 시험에는 빈 자료를 준비하세요.";
    if(has("인증")||has("key 요청변수")||has("Authorization"))return "요청의 인증정보가 설정과 다르거나 누락·중복되어 있습니다. API 키 또는 인증 토큰 설정을 확인하세요.";
    if(has("method")||has("경로")||has("query")||has("GET 요청")||has("GET에"))return "대상의 요청 방법·URL 경로·요청변수 또는 본문이 기준과 다릅니다. API 호출 설정을 확인하세요.";
    if(has("코드 오류")||has("sky: 코드"))return "응답 정보의 분류 코드가 허용된 값과 다릅니다. 해당 항목의 코드 정의를 확인하세요.";
    if(has("숫자")||has("길이 초과")||has("정수 유효값 범위"))return "응답의 "+field(r)+" 값 또는 길이가 기준을 벗어났습니다. 제공 데이터의 범위를 확인하세요.";
    if(has("자료 부재"))return "같은 유효 API에서 자료가 없는 상태를 준비하고 확인란을 선택하세요. 정상·자료 부재 오류·빈 정상응답은 서로 다른 준비 조건으로 실행합니다.";
    if(has("VDS API에 정의된"))return "잘못된 요청의 기대 응답 코드를 VDS API 명세에 정의된 400으로 설정하세요.";
    if(has("접속 제한시간"))return "접속 제한시간을 전체 응답 제한시간 이하로 설정하세요.";
    if(has("최소 10회"))return "각 항목의 반복 횟수를 10회 이상으로 설정하세요.";
    if(has("입력")||has("설정")||has("선택"))return "시험 설정을 적용하지 못했습니다. 필수 입력, 기대 응답 코드와 선택한 시험 항목을 확인하세요.";
    if(has("자료")||has("file")||has("파일")||has("filesystem"))return "시험 자료를 읽거나 기록하지 못했습니다. 응답 자료와 저장 위치의 접근 상태를 확인하세요.";
    if(has("서버 생성")||has("수신 대기"))return "시험 시스템의 수신 준비를 완료하지 못했습니다. 수신 주소와 포트 사용 상태를 확인하세요.";
    return "시험을 계속 진행할 수 없습니다. 대상 연결 상태와 시험 환경 설정을 확인한 뒤 다시 실행하세요.";
}
std::string userRunSummary(const MethodConfig &c,const Result &r){
    if(r.verdict=="SUCCESS")return "자동 검증 완료: 선택한 "+std::to_string(c.items.size())+"개 항목에서 총 "+std::to_string(r.exchanges)+"회 교환을 확인했습니다. 엔진에서 관측한 송수신·규격 검사 기준을 충족했습니다. 대상 내부 동작의 미관측 범위는 항목별 기록을 확인하세요.";
    if(r.verdict=="STOPPED")return "시험을 중지했습니다. 완료한 교환은 "+std::to_string(r.exchanges)+"회이며, 진행하지 않은 항목은 판정하지 않았습니다.";
    return "시험이 중단됐습니다. 완료한 교환은 "+std::to_string(r.exchanges)+"회입니다. 실패 항목의 실제 응답과 확인 사항을 검토한 뒤 남은 항목을 다시 실행하세요.";
}
RestUserLog::RestUserLog(const MethodConfig &c,const Sink &s,const std::string &directory):config(c),sink(s),record(std::filesystem::u8path(directory)/"user-log.jsonl",std::ios::binary){if(!record)throw Failure("사용자 안내 기록 파일을 만들 수 없습니다.");}
void RestUserLog::write(const std::string &test,const std::string &stage,const std::string &message,const std::string &data){
    auto phase=stage=="result"?"결과":stage=="overview"||stage=="guide"||stage=="basis"||stage=="purpose"||stage=="link"||stage=="criteria"?"시험 안내":stage=="ready"||stage=="waiting"?"준비":stage=="request"?"송신":stage=="response"||stage=="evidence"||stage=="data"?"판정 근거":"진행";
    auto publicMessage=interface_log::line(message,phase);
    record<<"{\"test\":"<<quote(test)<<",\"stage\":"<<quote(stage)<<",\"message\":"<<quote(message);
    if(!data.empty())record<<",\"dataType\":\"JSON\",\"data\":"<<data;
    record<<"}\n";record.flush();
    if(test.empty()){if(sink.info)sink.info(publicMessage);}else if(!data.empty()&&sink.itemData)sink.itemData(test,publicMessage,"JSON",data);else if(sink.itemInfo)sink.itemInfo(test,publicMessage);
}
void RestUserLog::begin(){write("","overview",userSetupSummary(config));}
void RestUserLog::listening(){write("","ready","요청 대기: 시험 시스템의 수신 준비가 완료됐습니다. "+requester(config)+"에서 설정한 시험 시스템 주소로 GET 요청을 보내면 시험을 진행합니다.");}
void RestUserLog::item(const MethodItem &i,unsigned index){
    auto guide=interface_log::guide(i.title,target(config),intent(config,i),methodBasis(config,i)+" · "+criteria(config,i)+" · 총 "+std::to_string(config.repetitions)+"회",unobservedScope(config,i));
    guide.pop_back();guide+=","+userCaseDefinition(config,i).substr(1);
    write(i.key,"guide","시험 안내: "+i.title,guide);
    write(i.key,"basis",std::string(i.standardRequired?"기능·오류상황 관련 조항: ":"추가 검증: ")+methodBasis(config,i));
    write(i.key,"purpose","시험 안내("+std::to_string(index)+"/"+std::to_string(config.items.size())+"): "+intent(config,i));
    write(i.key,"link","연계 정보: "+provider(config)+" → "+requester(config)+" / "+information(config)+" / "+format(config)+". 시험 대상은 "+target(config)+"입니다.");
    write(i.key,"criteria","검증 기준: "+criteria(config,i)+" 총 "+std::to_string(config.repetitions)+"회 확인합니다.");
    if(!config.provider||i.standardRequired)write(i.key,"evidence",evidence(config,i));
}
void RestUserLog::request(const MethodItem &i,unsigned n,const std::string &urlPath){
    if(n>1)return; // Waiting guidance only; every observed request has its own data notification.
    if(!config.provider){write(i.key,"waiting",progress(n,config.repetitions)+" 요청 대기: "+requester(config)+"의 GET "+path(config)+" 요청을 기다립니다.");return;}
    write(i.key,"request",progress(n,config.repetitions)+" 요청: GET "+urlPath+" / "+authentication(config,i)+" / "+inputCondition(config,i)+" 대상의 응답을 기다립니다.");
}
void RestUserLog::message(const MethodItem &i,unsigned n,const std::string &direction,const std::string &summary,const std::string &data){
    write(i.key,"message",progress(n,config.repetitions)+" "+direction+": "+summary,data);
}
std::string RestUserLog::sample(const std::string &body)const{
    auto clean=[&](const std::string &s){return safe(s,config.credential);};
    try{
        if(config.xml){auto values=parseUticXml(body,true);if(values.empty())return "돌발정보 0건";auto &f=values.front().fields;
            return "첫 번째 돌발정보: ID "+clean(f["incidentId"])+", 제목 "+clean(f["incidentTitle"])+", 시작일시 "+clean(f["startDate"])+", 도로 "+clean(f["roadName"])+".";}
        auto values=Json::parse(body,1024*1024);
        if(config.weather){const auto &a=values.get("response")->get("body")->get("items")->get("item")->array;if(a.empty())return "기상정보 0건";auto get=[&](const char *key){auto v=a.front().get(key);return v?clean(v->text):"미제공";};return "첫 번째 기상정보: 발표일자 "+get("baseDate")+", 시각 "+get("updateDt")+", 예보지점 "+get("nx")+", "+get("ny")+", 기온 "+get("t1h")+" ℃, 강수량 "+get("rn1")+" mm, 하늘상태 "+get("sky")+", 습도 "+get("reh")+"%, 풍속 "+get("wsd")+" m/s.";}
        if(config.ntic){auto items=values.get("items");if(!items||items->kind!=Json::Array||items->array.empty())return "NTIC 차량검지정보 0건";auto &row=items->array.front();auto get=[&](const char *key){auto v=row.get(key);return v?clean(v->text):"미제공";};return "첫 번째 차량검지정보: VDS "+get("vdsId")+", 링크 "+get("linkIds")+", 차로 "+get("laneNo")+", 수집일시 "+get("colctedDate")+", 속도 "+get("speed")+" km/h, 교통량 "+get("volume")+", 점유율 "+get("occupancy")+"%.";}
if(values.kind!=Json::Array||values.array.empty())return config.shadow?"음영구간 미시교통정보 0건":config.smart?"스마트교차로 정보 0건":"VDS 정보 0건";
        auto get=[&](const char *key){auto p=values.array[0].get(key);return p?clean(p->text):"미제공";};
        if(config.shadow)return "첫 번째 음영구간 정보: 발생시각 "+get("time")+", 노드링크 "+get("node_link")+", 차로 "+get("lane_no")+", 속도 "+get("lane_speed")+" km/h/lane, 교통량 "+get("lane_volume")+" veh/min/lane, 밀도 "+get("lane_density")+" veh/km/lane.";
        auto collected=get("collectDate");if(collected.size()==14&&collected.find_first_not_of("0123456789")==std::string::npos)collected=collected.substr(0,4)+"-"+collected.substr(4,2)+"-"+collected.substr(6,2)+" "+collected.substr(8,2)+":"+collected.substr(10,2)+":"+collected.substr(12,2);
        if(config.smart)return "첫 번째 스마트교차로 정보: 노드 "+get("nodeId")+", 링크 "+get("linkId")+", 접근로 "+get("ascrId")+", 차로 "+get("laneNo")+", 차종 "+get("vkndCd")+", 수집일시 "+collected+", 속도 "+get("spd")+", 교통량 "+get("vol")+".";
        return "첫 번째 VDS 정보: 지점 "+get("stnId")+", 차로 "+get("laneNo")+", 수집일시 "+collected+", 교통량 "+get("vol")+", 속도 "+get("spd")+" km/h, 점유율 "+get("occ")+"%.";
    }catch(...){return "정보 요약을 표시할 수 없습니다. 판정에 사용한 응답 원문으로 확인하세요.";}
}
void RestUserLog::exchange(const MethodItem &i,unsigned n,unsigned status,const std::string &media,size_t bytes,size_t count,const std::string &body){
    bool countKnown=true;
    if(!config.provider&&i.check=="normal"){
        try{count=config.weather?validateWeatherResponse({200,"application/json",body}):config.ntic?validateNticResponse({200,"application/json",body}):config.xml?parseUticXml(body,true).size():Json::parse(body,1024*1024).array.size();}
        catch(...){countKnown=false;}
    }
    std::string actual=config.provider?"수신 ":"전송 ";actual+=code(status);
    std::string description;
    if(i.check=="normal")description=information(config)+(countKnown?" "+std::to_string(count)+"건":" (건수 요약 생략)")+", "+format(config)+(config.provider?" 정보 형식 확인":" 정보 제공");
    else if(config.weather&&(i.check=="weather-error"||i.check=="absence-error"))description="업무 결과코드 "+weatherResultCode(i.key)+" 및 오류 메시지 "+(config.provider?"확인":"제공");
    else if(i.check=="absence-error")description="자료 부재 준비 조건에서 관측한 오류응답";
    else if(i.check=="empty")description="빈 결과(정보 0건) 확인";
    else if(i.check=="shadow-error")description=config.provider?"API 명세의 422 오류 JSON 구조 확인":"API 명세 형태의 422 오류 JSON 제공";
    else if(i.check=="ntic-error")description="NTIC 응답결과코드(resultCode) "+nticResultCode(i.key)+" 확인";
    else if(i.check=="error-schema")description=config.provider?"API 명세의 오류 JSON 형식 확인":"API 명세 형태의 오류 JSON 제공";
    else if(i.check=="malformed")description="잘못된 "+format(config)+" 본문을 시험 조건대로 전송";
    else description="응답 본문 "+std::to_string(bytes)+"바이트, 본문 형식 검사는 적용하지 않음";
    write(i.key,"evidence",progress(n,config.repetitions)+" 판정 근거", "{\"자료 구분\":\"시험 근거\",\"기대 응답\":"+quote(code(i.expected))+",\"실제 응답\":"+quote(code(status))+",\"확인 내용\":"+quote(description)+",\"판정 범위\":"+quote(config.provider?"실제 수신 응답과 해당 항목의 데이터 검사를 확인했습니다.":"시험 시스템의 응답 전송을 확인했습니다. 대상 내부 처리는 직접 관측하지 않았습니다.")+"}");
    description+=" / 본문 형식: "+(media.empty()?std::string("미표시"):safe(media,config.credential,64));
    if(config.provider)write(i.key,"response",progress(n,config.repetitions)+(n==1?" 확인: 기대 "+code(i.expected)+" / 실제 "+actual:" 확인: "+actual)+". "+description+". 검사 기준을 충족했습니다.");
    else write(i.key,"response",progress(n,config.repetitions)+" 전송 완료: "+code(status)+". "+description+(n==1?". 대상 내부 처리 결과는 직접 관측하지 않았습니다.":"."));
    if(n==1&&i.check=="normal")write(i.key,"data",std::string(config.provider?"수신한 연계정보 — ":"제공한 연계정보 — ")+sample(body));
}
void RestUserLog::result(const MethodItem &i,const std::string &verdict,unsigned completed,const std::string &reason,unsigned attempted,unsigned actualStatus,const std::string &data){
    std::string s;
    if(verdict=="SUCCESS")s="자동 관측검사 통과: "+progress(completed,config.repetitions)+std::string(config.provider?" 대상 응답을 수신하여 기대한 ":" 대상의 유효한 요청을 확인하고 시험기에서 ")+code(i.expected)+std::string(config.provider?" 및 해당 본문 검사 기준을 확인했습니다.":" 응답을 전송했습니다.")+" 적용한 입력 조건·기대응답과 실제 송수신 자료를 판정 근거로 보관했습니다.";
    else if(verdict=="NOT_RUN")s="미실행: 앞선 항목에서 시험이 중단되어 이 항목은 진행하지 않았습니다. 중단 원인을 확인한 뒤 이 항목을 선택해 다시 실행하세요.";
    else if(verdict=="STOPPED")s="중지: "+progress(completed,config.repetitions)+"까지 교환을 완료했습니다. 남은 회차는 수행하지 않아 이 항목의 완료 여부를 판정하지 않았습니다.";
    else{s="항목 실패: "+std::to_string(attempted?attempted:1)+"번째 확인에서 중단됐습니다. ";if(actualStatus)s+="기대 "+code(i.expected)+" / 실제 "+code(actualStatus)+". ";s+=userError(reason)+" 완료한 교환은 "+progress(completed,config.repetitions)+"입니다.";}
    s+=" 자동 관측 범위의 판정입니다. "+unobservedScope(config,i);
    write(i.key,"result",s,data);
}
}

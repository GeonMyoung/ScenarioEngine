#pragma once
#include "RestCore.h"
#include <windows.h>
#include <wincrypt.h>
#pragma comment(lib,"Crypt32.lib")

namespace g4mqtt {
inline std::string credentialJson(const rest::Json &v) {
    if(v.kind==rest::Json::String)return rest::quote(v.text);
    if(v.kind==rest::Json::Number)return v.text;
    if(v.kind==rest::Json::Bool)return v.boolean?"true":"false";
    std::string out;bool first=true;
    if(v.kind==rest::Json::Object){out="{";for(const auto &p:v.object){if(!first)out+=",";first=false;out+=rest::quote(p.first)+":"+credentialJson(p.second);}return out+"}";}
    if(v.kind==rest::Json::Array){out="[";for(const auto &x:v.array){if(!first)out+=",";first=false;out+=credentialJson(x);}return out+"]";}
    return "null";
}
inline std::string protectedConfiguration(const std::string &raw) {
    auto value=rest::Json::parse(raw);auto password=value.get("password");
    if(password&&password->kind==rest::Json::String&&!password->text.empty()){
        DATA_BLOB input={static_cast<DWORD>(password->text.size()),reinterpret_cast<BYTE *>(const_cast<char *>(password->text.data()))},output={};
        if(!CryptProtectData(&input,NULL,NULL,NULL,NULL,CRYPTPROTECT_UI_FORBIDDEN,&output))throw rest::Failure("MQTT credential protection failed");
        const char *digits="0123456789abcdef";std::string hex="dpapi-v1:";
        for(DWORD i=0;i<output.cbData;i++){hex+=digits[output.pbData[i]>>4];hex+=digits[output.pbData[i]&15];}
        SecureZeroMemory(output.pbData,output.cbData);LocalFree(output.pbData);
        value.object.erase("password");rest::Json encrypted;encrypted.kind=rest::Json::String;encrypted.text=std::move(hex);value.object["password_protected"]=std::move(encrypted);
    }
    return credentialJson(value);
}
}

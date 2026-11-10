#include <dz1_asn1.h>
#include <dz1_thread.h>
#include <dz1_cleanup.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "MqttPayloadStrict.h"
#include "MqttDiagnostics.h"
#include "../../datexconformance/src/DatexSamples.h"

extern "C" Dz1Binary *MqttPayload_jsonStrict(unsigned, unsigned char *, size_t);
extern "C" Dz1Binary *MqttBsm_sample(unsigned char *, size_t, unsigned, unsigned, unsigned);
extern "C" Dz1Binary *MqttTim_profile(unsigned char *, size_t);
extern "C" Dz1Binary *DatexPayload_timRegionalSummary(unsigned char *, size_t);

static unsigned nibble(char c) {
    if(c>='0'&&c<='9')return c-'0';
    if(c>='a'&&c<='f')return c-'a'+10;
    if(c>='A'&&c<='F')return c-'A'+10;
    throw std::runtime_error("invalid hexadecimal input");
}
static std::vector<unsigned char> bytes(const std::string &s) {
    if(s.empty()||s.size()%2||s.size()>2*1024*1024)throw std::runtime_error("payload length invalid");
    std::vector<unsigned char> result;result.reserve(s.size()/2);
    for(size_t i=0;i<s.size();i+=2)result.push_back(static_cast<unsigned char>(nibble(s[i])*16+nibble(s[i+1])));
    return result;
}
static std::string hex(const unsigned char *p,size_t n){
    const char *digits="0123456789abcdef";std::string s;s.reserve(n*2);
    for(size_t i=0;i<n;++i){s+=digits[p[i]>>4];s+=digits[p[i]&15];}return s;
}
int main(int argc,char **argv) {
    Dz1Cleanup_init();
    Dz1Error initialization={};
    Dz1Thread_init(0,&initialization);
    std::ofstream resultFile;
    std::ostream *output=&std::cout;
    MqttDiag_reset("input");
    MqttPayloadCheck check={"INPUT_ERROR","input",0,0};
    try {
        if(argc<3)throw std::runtime_error("usage: MqttPayload sample|decode frameId [hex-file]");
        std::string command=argv[1];
        unsigned frame=command=="bsm-sample"?20:static_cast<unsigned>(std::stoul(argv[2]));
        if(frame!=20&&frame!=19&&frame!=50&&frame!=31)throw std::runtime_error("unsupported MQTT message");
        int resultIndex=command=="bsm-sample"?5:(command=="sample"?3:4);
        if(argc>resultIndex){resultFile.open(argv[resultIndex],std::ios::binary);if(!resultFile)throw std::runtime_error("result output failed");output=&resultFile;}
        if(command=="bsm-sample"&&argc>=5){
            unsigned sequence=static_cast<unsigned>(std::stoul(argv[2]));
            unsigned secMark=static_cast<unsigned>(std::stoul(argv[3]));
            auto vehicle=bytes(argv[4]);
            if(vehicle.size()!=4)throw std::runtime_error("vehicle ID must have four bytes");
            unsigned id=0;for(auto b:vehicle)id=(id<<8)|b;
            auto generated=MqttBsm_sample(const_cast<unsigned char *>(datex::fixtures::bsm),sizeof(datex::fixtures::bsm),sequence,secMark,id);
            if(!generated)throw std::runtime_error("BSM generation failed");
            bool valid=MqttPayload_validateStrict(20,generated->data,generated->size,&check)!=0;
            auto encoded=hex(generated->data,generated->size);Dz1Binary_del(generated);
            if(!valid)throw std::runtime_error("generated BSM validation failed");
            *output<<"{\"valid\":true,\"frameId\":20,\"hex\":\""<<encoded<<"\"}\n";
        }else if(command=="sample"){
            using namespace datex::fixtures;
            const unsigned char *p=nullptr;size_t n=0;
            if(frame==20){p=bsm;n=sizeof(bsm);}else if(frame==19){p=spat;n=sizeof(spat);}
            else if(frame==50){p=tls;n=sizeof(tls);}else{p=tim;n=sizeof(tim);}
            if(!MqttPayload_validateStrict(frame,const_cast<unsigned char *>(p),n,&check))throw std::runtime_error("sample UPER validation failed");
            *output<<"{\"valid\":true,\"frameId\":"<<frame<<",\"hex\":\""<<hex(p,n)<<"\"}\n";
        }else if(command=="decode"&&argc>=4){
            std::ifstream input(argv[3],std::ios::binary);
            if(!input)throw std::runtime_error("payload input missing");
            std::string text((std::istreambuf_iterator<char>(input)),{});
            auto data=bytes(text);
            if(!MqttPayload_validateStrict(frame,data.data(),data.size(),&check))
                throw std::runtime_error("UPER structure, constraint or boundary validation failed");
            auto json=MqttPayload_jsonStrict(frame,data.data(),data.size());
            if(!json){check.code="JSON_CONVERSION";check.stage="display";throw std::runtime_error("decoded message display failed");}
            *output<<"{\"valid\":true,\"frameId\":"<<frame<<",\"decoded\":";
            if(json){output->write(reinterpret_cast<char *>(json->data),json->size);Dz1Binary_del(json);}
            else *output<<"null";
            if(frame==31){
                auto profile=MqttTim_profile(data.data(),data.size());
                auto regional=DatexPayload_timRegionalSummary(data.data(),data.size());
                if(!profile||!regional){Dz1Binary_del(profile);Dz1Binary_del(regional);throw std::runtime_error("TIM metadata extraction failed");}
                *output<<",\"timProfile\":";output->write(reinterpret_cast<char*>(profile->data),profile->size);
                *output<<",\"timRegional\":";output->write(reinterpret_cast<char*>(regional->data),regional->size);
                Dz1Binary_del(profile);Dz1Binary_del(regional);
            }
            *output<<",\"validation\":{\"asn1Constraints\":true,\"exactLength\":true,\"zeroPadding\":true,\"messageFrameBits\":"
                   <<check.frame_bits<<",\"messageBits\":"<<check.message_bits<<"}}\n";
        }else throw std::runtime_error("unsupported codec operation");
        output->flush();if(!*output)throw std::runtime_error("result output failed");return 0;
    }catch(const std::exception &e){std::cerr<<e.what()<<"\n";
        const auto *d=MqttDiag_get();
        *output<<"{\"valid\":false,\"code\":\""<<(d->constraint?"UPER_CONSTRAINT":check.code)<<"\",\"stage\":\""<<check.stage<<"\",\"field\":\""<<(d->field[0]?d->field:check.stage)<<"\",\"expected\":\""<<d->expected<<"\",\"actual\":";
        if(d->has_actual)*output<<d->actual;else *output<<"null";
        *output<<",\"bitOffset\":";if(d->has_offset)*output<<d->bit_offset;else *output<<"null";
        *output<<"}\n";return 2;}
}

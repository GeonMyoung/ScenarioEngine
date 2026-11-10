#pragma once
#include "RestCore.h"
namespace signalbinary {
using Bytes=std::vector<unsigned char>;
using rest::Json;
struct Profile {std::string checksum="xor8",ackSequence="echo",encoding="UTF-8";bool heartbeatAck=true;};
struct Frame {unsigned message=0,flag=2,sequence=0;Bytes payload,raw;};
unsigned lrc(const Bytes &,const Profile &);
Bytes packet(unsigned message,unsigned flag,unsigned sequence,const Bytes &,const Profile &);
Bytes acknowledgement(unsigned message,unsigned sequence,bool accepted,const Profile &);
Frame frame(const Bytes &,const Profile &);
void validateAck(const Bytes &,unsigned message,unsigned sequence,bool accepted,const Profile &);
Json decode(unsigned message,const Bytes &,const Profile &);
Bytes encode(unsigned message,const Json &,const Profile &);
Json fixture(unsigned message,unsigned iteration=0,unsigned count=1);
std::string dump(const Json &);
std::string hex(const Bytes &);
Bytes unhex(const std::string &);
std::string infoName(unsigned message);
struct Assembler {
    unsigned next=0,message=0;bool pending=false;Bytes data;
    explicit Assembler(unsigned first=0):next(first){}
    // ACK applies to each frame. Only a completed group has decoded records.
    Json accept(const Frame &,const Profile &,bool &complete);
};
}

#pragma once
#include "SignalCodec.h"
namespace signalbinary {
inline bool extended(unsigned message){return message==67||message==71||message==72;}
Bytes fixedText(const std::string &,unsigned,const Profile &,bool terminated=false);
std::string readFixedText(const Bytes &,const Profile &,bool terminated=false);
Bytes encodeExtended(unsigned,const Json &,const Profile &);
Json decodeExtended(unsigned,const Bytes &,const Profile &);
Json extendedFixture(unsigned,unsigned,unsigned);
size_t informationCount(unsigned,const Json &);
size_t distinctInformationCount(unsigned,const Json &);
}

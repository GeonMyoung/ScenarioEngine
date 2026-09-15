#ifndef TECHNICAL_REGULATION2_UTIL_H
#define TECHNICAL_REGULATION2_UTIL_H


#include <TechnicalRegulation2EAMDz1.h>
#include <TechnicalRegulation2Def.h>
#include <TechnicalRegulation2DefJson.h>



DZ1_CPPLINK CommTxPDUList* CommTxPDUList_fromDimz(Dz1CommTxPDUResponse* src, Dz1Error* err);
DZ1_CPPLINK CommRxPDUList* CommRxPDUList_fromDimz(Dz1CommRxPDUResponse* src, Dz1Error* err);


#endif // !TECHNICAL_REGULATION2_UTIL_H

#ifndef ASN_PER_Open_Type_
#define ASN_PER_Open_Type_


#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"
#include "../TYPE/ASN1_Type.h"
#include "../PER/ASN1_PER_SET.h"

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_OpenType(ASN1WorkSpace *ws,OpenType *value);


ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_OpenType(ASN1WorkSpace *ws,OpenType *value);


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_OpenType(ASN1WorkSpace *ws,OpenType *value);


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_OpenType(ASN1WorkSpace *ws,OpenType *value);

ASN1_CPPLINK ASNINT32 ASN1_PER_SET_WsToOpenType(ASN1WorkSpace *ws,OpenType *value);


ASN1_CPPLINK ASNINT32 ASN1_PER_SET_OpenTypeToWs(ASN1WorkSpace *ws,OpenType *value);

#endif /*_Open_Type_*/


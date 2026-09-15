#ifndef ASN1_XER_NAME_H
#define ASN1_XER_NAME_H

#include "OS/ASN1_Sys.h"
#include "IO/ASN1_WorkSpace.h"
#include "TYPE/ASN1_Type.h"
#include "TOOL/ASN1_Operate_Byte.h"

ASN1_CPPLINK ASNINT32 ASN1_XER_Enc_Start_Name(ASN1WorkSpace *ws,ASNUINT8* name);

ASN1_CPPLINK ASNINT32 ASN1_XER_Enc_End_Name(ASN1WorkSpace *ws,ASNUINT8* name);

ASN1_CPPLINK ASNINT32 ASN1_XER_Enc_Backslash_Name(ASN1WorkSpace *ws,ASNUINT8* name);

ASN1_CPPLINK ASNINT32 ASN1_XER_Tab(ASN1WorkSpace *ws,ASNINT32 tab_count);

ASN1_CPPLINK ASNINT32 ASN1_XER_Enter(ASN1WorkSpace *ws,ASNINT32 Ent_count);

ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_Name(ASN1WorkSpace *ws);

ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_Format(ASN1WorkSpace *ws);


#endif/*ASN1_XER_NAME_H*/

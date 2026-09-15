#ifndef _XER_Enum_H
#define _XER_Enum_H

#include "OS/ASN1_Sys.h"
#include "IO/ASN1_WorkSpace.h"
#include "TOOL/ASN1_Tag.h"
#include "TOOL/ASN1_Length.h"
#include "TYPE/ASN1_Type.h"
#include "XER/ASN1_XER_Name.h"

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_ENUMERATED(ASN1WorkSpace * ws, ASNSTRING *tvalue, 
										   ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_ENUMERATED(ASN1WorkSpace * ws, ASNSTRING *tvalue,
									   ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_ENUMERATED(ASN1WorkSpace * ws, ASNSTRING *value,
										   ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_ENUMERATED(ASN1WorkSpace * ws, ASNSTRING *value,
									   ASNUINT8 *name,ASNINT32 tab_value);

ASN1_CPPLINK ASNINT32 ASN1_XER_Enc_ENUMERATED_Str(ASN1WorkSpace * ws,
									 ASNSTRING *value,ASNUINT8 *enum_value);

ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_ENUMERATED_Str(ASNSTRING *value,ASNUINT8 *enum_value);

#endif

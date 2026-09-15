#ifndef ASN_XER_INTEGER_H
#define ASN_XER_INTEGER_H

#include "OS/ASN1_Sys.h"
#include "IO/ASN1_WorkSpace.h"
#include "TOOL/ASN1_Tag.h"
#include "TOOL/ASN1_Length.h"
#include "TOOL/ASN1_Operate_Byte.h"
#include "TYPE/ASN1_Type.h"
#include "XER/ASN1_XER_Name.h"

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_INTEGER(ASN1WorkSpace * ws, INTEGER *tvalue, 
										ASNUINT8 *name,ASNINT32 tab_value);
										

ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_INTEGER(ASN1WorkSpace * ws, INTEGER *tvalue,
									ASNUINT8 *name,ASNINT32 tab_value);
									

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_INTEGER(ASN1WorkSpace * ws, INTEGER *value,
										ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_INTEGER(ASN1WorkSpace * ws, INTEGER *value,
									ASNUINT8 *name,ASNINT32 tab_value);


#endif




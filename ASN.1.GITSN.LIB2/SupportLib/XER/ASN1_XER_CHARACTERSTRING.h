#ifndef _ASN_XER_Charstr_H_
#define _ASN_XER_Charstr_H_

#include "TOOL/ASN1_CHAR_TOOL.h"
#include "OS/ASN1_Sys.h"
#include "IO/ASN1_WorkSpace.h"
#include "TOOL/ASN1_Tag.h"
#include "TOOL/ASN1_Length.h"
#include "TYPE/ASN1_Type.h"
#include "ASN1_XER_STRING.h"
#include "TOOL/ASN1_Operate_Byte.h"
#include "ASN1_XER_Name.h"



ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_CHARACTERSTRING(ASN1WorkSpace *ws,CHARACTERSTRING *tvalue, 
											ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_CHARACTERSTRING(ASN1WorkSpace *ws,CHARACTERSTRING *tvalue,
										ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_CHARACTERSTRING(ASN1WorkSpace *ws,CHARACTERSTRING *value,
											ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_CHARACTERSTRING(ASN1WorkSpace *ws,CHARACTERSTRING *value,
									    ASNUINT8 *name,ASNINT32 tab_value);


#endif

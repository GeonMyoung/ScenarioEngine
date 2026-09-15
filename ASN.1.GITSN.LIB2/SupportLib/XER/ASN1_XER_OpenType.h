#ifndef ASN_XER_Open_Type_
#define ASN_XER_Open_Type_


#include "OS/ASN1_Sys.h"
#include "IO/ASN1_WorkSpace.h"
#include "TOOL/ASN1_Tag.h"
#include "TOOL/ASN1_Length.h"
#include "TYPE/ASN1_Type.h"
#include "XER/ASN1_XER_Name.h"
#include "XER/ASN1_XER_SET.h"
#include "TOOL/ASN1_XER_Check_Length.h"


ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_OpenType(ASN1WorkSpace * ws, OpenType *tvalue, 
										 ASNUINT8 *name,ASNINT32 tab_value);
										

ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_OpenType(ASN1WorkSpace * ws, OpenType *tvalue,
									 ASNUINT8 *name,ASNINT32 tab_value);
									

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_OpenType(ASN1WorkSpace * ws, OpenType *value,
										 ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_OpenType(ASN1WorkSpace * ws, OpenType *value,
									 ASNUINT8 *name,ASNINT32 tab_value);


#endif /*_Open_Type_*/


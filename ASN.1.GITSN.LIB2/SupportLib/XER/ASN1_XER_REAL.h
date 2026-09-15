#ifndef _ASN_XER_REAL_H
#define _ASN_XER_REAL_H


#include "OS/ASN1_Sys.h"
#include "IO/ASN1_WorkSpace.h"
#include "TOOL/ASN1_Tag.h"
#include "TOOL/ASN1_Length.h"
#include "TYPE/ASN1_Type.h"
#include "TOOL/ASN1_Operate_Byte.h"
#include "ASN1_XER_Name.h"


ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_REAL(ASN1WorkSpace *ws,REAL *tvalue, 
									 ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_REAL(ASN1WorkSpace *ws,REAL *tvalue,
								 ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_REAL(ASN1WorkSpace *ws,REAL *value,
									 ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_REAL(ASN1WorkSpace *ws,REAL *value,
								 ASNUINT8 *name,ASNINT32 tab_value);


#endif


#ifndef _ASN_XER_OID_H_
#define _ASN_XER_OID_H_
/*
  Name: OBJECT IDENTIFIER
  Copyright: 
  Author: fanyapeng
  Date: 21-04-08 14:40
  Description: encode decode OBJECT IDENTIFIER
*/
#include "OS/ASN1_Sys.h"
#include "IO/ASN1_WorkSpace.h"
#include "TOOL/ASN1_Tag.h"
#include "TOOL/ASN1_Length.h"
#include "TYPE/ASN1_Type.h"
#include "TOOL/ASN1_Operate_Byte.h"
#include "ASN1_XER_Name.h"

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_OBJECTIDENTIFIER(ASN1WorkSpace * ws, OBJECTIDENTIFIER *tvalue, 
										ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_OBJECTIDENTIFIER(ASN1WorkSpace * ws, OBJECTIDENTIFIER *tvalue,
									ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_OBJECTIDENTIFIER(ASN1WorkSpace * ws, OBJECTIDENTIFIER *value,
										ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_OBJECTIDENTIFIER(ASN1WorkSpace * ws, OBJECTIDENTIFIER *value,
									ASNUINT8 *name,ASNINT32 tab_value);


#endif /*_ASN_ROID_H_*/


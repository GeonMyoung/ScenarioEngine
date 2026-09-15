#ifndef _ASN_XER_Octstr_H_
#define _ASN_XER_Octstr_H_

#include "OS/ASN1_Sys.h"
#include "IO/ASN1_WorkSpace.h"
#include "TOOL/ASN1_Tag.h"
#include "TOOL/ASN1_Length.h"
#include "TYPE/ASN1_Type.h"
#include "TOOL/ASN1_Operate_Byte.h"
#include "ASN1_XER_Name.h"


ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_OCTETSTRING(ASN1WorkSpace *ws,OCTETSTRING *tvalue, 
									        ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_OCTETSTRING(ASN1WorkSpace *ws,OCTETSTRING *tvalue,
								        ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_OCTETSTRING(ASN1WorkSpace *ws,OCTETSTRING *value,
									        ASNUINT8 *name,ASNINT32 tab_value);


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_OCTETSTRING(ASN1WorkSpace *ws,OCTETSTRING *value,
									    ASNUINT8 *name,ASNINT32 tab_value);

#endif

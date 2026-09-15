#include "ASN1_XER_TeletexString.h"

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_TeletexString(ASN1WorkSpace * ws, TeletexString *tvalue, 
												ASNUINT8 *name,ASNINT32 tab_value)
{
	return ASN1_XER_CANONICAL_Enc_ASNSTRING(ws,tvalue,name,tab_value);
}


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_TeletexString(ASN1WorkSpace * ws, TeletexString *tvalue,
											ASNUINT8 *name,ASNINT32 tab_value)
											
{
	return ASN1_XER_BASIC_Enc_ASNSTRING(ws,tvalue,name,tab_value);
}
ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_TeletexString(ASN1WorkSpace * ws, TeletexString *value,
												ASNUINT8 *name,ASNINT32 tab_value)
												
{
	return ASN1_XER_CANONICAL_Dec_ASNSTRING(ws,value,name,tab_value);
}
ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_TeletexString(ASN1WorkSpace * ws, TeletexString *value,
											ASNUINT8 *name,ASNINT32 tab_value)
{
	return ASN1_XER_BASIC_Dec_ASNSTRING(ws,value,name,tab_value);
}

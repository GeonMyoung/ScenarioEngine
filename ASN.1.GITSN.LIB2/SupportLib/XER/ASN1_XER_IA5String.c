#include "ASN1_XER_IA5String.h"

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_IA5String(ASN1WorkSpace * ws, IA5String *tvalue, 
												ASNUINT8 *name,ASNINT32 tab_value)
{
	return ASN1_XER_CANONICAL_Enc_ASNSTRING(ws,tvalue,name,tab_value);
}


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_IA5String(ASN1WorkSpace * ws, IA5String *tvalue,
											ASNUINT8 *name,ASNINT32 tab_value)
											
{
	return ASN1_XER_BASIC_Enc_ASNSTRING(ws,tvalue,name,tab_value);
}
ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_IA5String(ASN1WorkSpace * ws, IA5String *value,
												ASNUINT8 *name,ASNINT32 tab_value)
												
{
	return ASN1_XER_CANONICAL_Dec_ASNSTRING(ws,value,name,tab_value);
}
ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_IA5String(ASN1WorkSpace * ws, IA5String *value,
											ASNUINT8 *name,ASNINT32 tab_value)
{
	return ASN1_XER_BASIC_Dec_ASNSTRING(ws,value,name,tab_value);
}

#include "ASN1_XER_UTF8String.h"

#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
ASNINT32 ASN1_XER_CANONICAL_Enc_UTF8Str(ASN1WorkSpace * ws, UTF8Str *tvalue, ASNUINT8 *name,ASNINT32 tab_value)
#else
ASNINT32 ASN1_XER_CANONICAL_Enc_UTF8String(ASN1WorkSpace * ws, UTF8String *tvalue, ASNUINT8 *name,ASNINT32 tab_value)
#endif
{
	return ASN1_XER_CANONICAL_Enc_ASNSTRING(ws,tvalue,name,tab_value);
}

#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
ASNINT32 ASN1_XER_BASIC_Enc_UTF8Str(ASN1WorkSpace * ws, UTF8Str *tvalue, ASNUINT8 *name,ASNINT32 tab_value)
#else
ASNINT32 ASN1_XER_BASIC_Enc_UTF8String(ASN1WorkSpace * ws, UTF8String *tvalue, ASNUINT8 *name,ASNINT32 tab_value)
#endif
{
	return ASN1_XER_BASIC_Enc_ASNSTRING(ws,tvalue,name,tab_value);
}

#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
ASNINT32 ASN1_XER_CANONICAL_Dec_UTF8Str(ASN1WorkSpace * ws, UTF8Str *value, ASNUINT8 *name,ASNINT32 tab_value)												
#else
ASNINT32 ASN1_XER_CANONICAL_Dec_UTF8String(ASN1WorkSpace * ws, UTF8String *value, ASNUINT8 *name,ASNINT32 tab_value)												
#endif
{
	return ASN1_XER_CANONICAL_Dec_ASNSTRING(ws,value,name,tab_value);
}

#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
ASNINT32 ASN1_XER_BASIC_Dec_UTF8Str(ASN1WorkSpace * ws, UTF8Str *value, ASNUINT8 *name,ASNINT32 tab_value)
#else
ASNINT32 ASN1_XER_BASIC_Dec_UTF8String(ASN1WorkSpace * ws, UTF8String *value, ASNUINT8 *name,ASNINT32 tab_value)
#endif
{
	return ASN1_XER_BASIC_Dec_ASNSTRING(ws,value,name,tab_value);
}

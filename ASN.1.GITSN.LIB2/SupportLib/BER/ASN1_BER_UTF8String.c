#include "ASN1_BER_UTF8String.h"


#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
ASNINT32 ASN1_BER_Enc_UTF8Str(ASN1WorkSpace* ws,UTF8Str* value, ASN1TagType flag)
#else
ASNINT32 ASN1_BER_Enc_UTF8String(ASN1WorkSpace* ws,UTF8String* value, ASN1TagType flag)
#endif
{
	return	ASN1_BER_Enc_String(ws,value,12,flag);
}

#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
ASNINT32 ASN1_BER_Dec_UTF8Str(ASN1WorkSpace* ws,UTF8Str* value, ASNINT32 length,ASN1TagType flag)
#else
ASNINT32 ASN1_BER_Dec_UTF8String(ASN1WorkSpace* ws,UTF8String* value, ASNINT32 length,ASN1TagType flag)
#endif
{
	return	ASN1_BER_Dec_String(ws,value,12,length,flag);
}

#include "ASN1_BER_GeneralString.h"


ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_GeneralString(ASN1WorkSpace* ws,GeneralString* value,
							 ASN1TagType flag)
{
	return	ASN1_BER_Enc_String(ws,value,27,flag);
}

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_GeneralString(ASN1WorkSpace* ws,GeneralString* value,
							 ASNINT32 length,ASN1TagType flag)
{
	return	ASN1_BER_Dec_String(ws,value,27,length,flag);
}

#include "ASN1_BER_IA5String.h"


ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_IA5String(ASN1WorkSpace* ws,IA5String* value,
							 ASN1TagType flag)
{
	return	ASN1_BER_Enc_String(ws,value,22,flag);
}

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_IA5String(ASN1WorkSpace* ws,IA5String* value,
							 ASNINT32 length,ASN1TagType flag)
{
	return	ASN1_BER_Dec_String(ws,value,22,length,flag);
}

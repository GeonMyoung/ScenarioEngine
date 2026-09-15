#include "ASN1_BER_TeletexString.h"


ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_TeletexString(ASN1WorkSpace* ws,TeletexString* value,
							 ASN1TagType flag)
{
	return	ASN1_BER_Enc_String(ws,value,20,flag);
}

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_TeletexString(ASN1WorkSpace* ws,TeletexString* value,
							 ASNINT32 length,ASN1TagType flag)
{
	return	ASN1_BER_Dec_String(ws,value,20,length,flag);
}

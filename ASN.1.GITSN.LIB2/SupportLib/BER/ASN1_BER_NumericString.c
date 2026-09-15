#include "ASN1_BER_NumericString.h"



ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_NumericString(ASN1WorkSpace* ws,NumericString* value,
							 ASN1TagType flag)
{
	return	ASN1_BER_Enc_String(ws,value,18,flag);
}

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_NumericString(ASN1WorkSpace* ws,NumericString* value,
							 ASNINT32 length,ASN1TagType flag)
{
	return	ASN1_BER_Dec_String(ws,value,18,length,flag);
}

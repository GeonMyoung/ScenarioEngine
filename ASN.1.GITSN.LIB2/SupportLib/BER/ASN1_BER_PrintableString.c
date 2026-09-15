#include "ASN1_BER_PrintableString.h"



ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_PrintableString(ASN1WorkSpace* ws,PrintableString* value,
							 ASN1TagType flag)
{
	return	ASN1_BER_Enc_String(ws,value,19,flag);
}

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_PrintableString(ASN1WorkSpace* ws,PrintableString* value,
							 ASNINT32 length,ASN1TagType flag)
{
	return	ASN1_BER_Dec_String(ws,value,19,length,flag);
}

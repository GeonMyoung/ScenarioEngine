#include "ASN1_BER_ObjectDescriptor.h"


ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_ObjectDescriptor(ASN1WorkSpace* ws,ObjectDescriptor* value,
										ASN1TagType flag)
{
//	return	ASN1_BER_Enc_String(ws, value, 22, flag);
	return	ASN1_BER_Enc_String(ws, value, 7, flag);
}

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_ObjectDescriptor(ASN1WorkSpace* ws,ObjectDescriptor* value,
										ASNINT32 length,ASN1TagType flag)
{
//	return	ASN1_BER_Dec_String(ws, value, 22, length, flag);
	return	ASN1_BER_Dec_String(ws, value, 7, length, flag);
}

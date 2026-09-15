#include "ASN1_BER_GraphicString.h"


ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_GraphicString(ASN1WorkSpace* ws,GraphicString* value,
							 ASN1TagType flag)
{
	return	ASN1_BER_Enc_String(ws,value,25,flag);
}

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_GraphicString(ASN1WorkSpace* ws,GraphicString* value,
							 ASNINT32 length,ASN1TagType flag)
{
	return	ASN1_BER_Dec_String(ws,value,25,length,flag);
}

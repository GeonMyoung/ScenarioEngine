#include "ASN1_BER_VisibleString.h"



ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_VisibleString(ASN1WorkSpace* ws,VisibleString* value,
							 ASN1TagType flag)
{
	return	ASN1_BER_Enc_String(ws,value,26,flag);
}

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_VisibleString(ASN1WorkSpace* ws,VisibleString* value,
							 ASNINT32 length,ASN1TagType flag)
{
	return	ASN1_BER_Dec_String(ws,value,26,length,flag);
}

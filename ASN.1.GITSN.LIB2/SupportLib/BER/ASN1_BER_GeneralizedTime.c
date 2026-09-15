#include "ASN1_BER_GeneralizedTime.h"



ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_GeneralizedTime(ASN1WorkSpace* ws,GeneralizedTime* value,
							 ASN1TagType flag)
{
	return	ASN1_BER_Enc_String(ws,value,24,flag);
}

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_GeneralizedTime(ASN1WorkSpace* ws,GeneralizedTime* value,
							 ASNINT32 length,ASN1TagType flag)
{
	return	ASN1_BER_Dec_String(ws,value,24,length,flag);
}

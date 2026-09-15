#include "ASN1_BER_NULL.h"

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_NULL(ASN1WorkSpace* ws,ASN1TagType flag)
{
	ASN1_Tag_Move_Pointer(ws,ITS_ASN_UNIV|ITS_ASN_PRIM|ASN1_TYPE_NULL,flag);		//encode Tag
	ASN1_BER_Enc_Length(ws,0);										//encode Length
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_NULL(ASN1WorkSpace* ws,ASN1TagType flag)
{
	if (ASN1EXPL == flag)
	{
		ASN1_BER_Dec_Tag(ws,ITS_ASN_UNIV|ITS_ASN_PRIM|ASN1_TYPE_NULL);
		ASN1_BER_Dec_Length(ws);
	}
		return 0;
}



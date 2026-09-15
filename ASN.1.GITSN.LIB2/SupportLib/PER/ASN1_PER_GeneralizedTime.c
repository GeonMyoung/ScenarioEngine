#include "ASN1_PER_GeneralizedTime.h"

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_GeneralizedTime(ASN1WorkSpace *ws,GeneralizedTime *value,
									 Asn1ConsInfo *consinfo)
{
	ASNINT32 ret;
	
	ret = ASN1_PER_Align_Enc_String(ws,value,consinfo,GENT_ABITS);
	if (ret<0){
		return ret;
	}
	
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_GeneralizedTime(ASN1WorkSpace *ws,GeneralizedTime *value,
									   Asn1ConsInfo *consinfo)
{
	ASNINT32 ret;
	
	ret = ASN1_PER_UNAlign_Enc_String(ws,value,consinfo,GENT_UBITS);
	if (ret<0){
		return ret;
	}
	
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_GeneralizedTime(ASN1WorkSpace *ws,GeneralizedTime *value,
									Asn1ConsInfo *consinfo)
{
	ASNINT32 ret;
	
	ret = ASN1_PER_Align_Dec_String(ws,value,consinfo,GENT_ABITS);
	if (ret<0){
		return ret;
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_GeneralizedTime(ASN1WorkSpace* ws,GeneralizedTime* value, 
									   Asn1ConsInfo *consinfo)
{
	ASNINT32 ret;
	
	ret = ASN1_PER_UNAlign_Dec_String(ws,value,consinfo,GENT_UBITS);
	if (ret<0){
		return ret;
	}
	return 0;
}



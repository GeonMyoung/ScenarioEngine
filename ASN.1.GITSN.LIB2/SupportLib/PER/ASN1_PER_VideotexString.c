#include "ASN1_PER_VideotexString.h"

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_VideotexString (ASN1WorkSpace *ws,VideotexString *value,
										Asn1ConsInfo *consinfo)
{
	ASNINT32 ret;
	consinfo->consType = UNCONS;
	ret = ASN1_PER_Align_Enc_String(ws,value,consinfo,NORMAL_ABITS);
	if (ret<0){
		return ret;
	}
	
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_VideotexString (ASN1WorkSpace *ws,VideotexString *value,
										  Asn1ConsInfo *consinfo)
{
	ASNINT32 ret;
	consinfo->consType = UNCONS;
	ret = ASN1_PER_UNAlign_Enc_String(ws,value,consinfo,NORMAL_UBITS);
	if (ret<0){
		return ret;
	}
	
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_VideotexString (ASN1WorkSpace *ws,VideotexString *value,
									   Asn1ConsInfo *consinfo)
{
	ASNINT32 ret;
	consinfo->consType = UNCONS;
	ret = ASN1_PER_Align_Dec_String(ws,value,consinfo,NORMAL_ABITS);
	if (ret<0){
		return ret;
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_VideotexString (ASN1WorkSpace* ws,VideotexString* value, 
										  Asn1ConsInfo *consinfo)
{
	ASNINT32 ret;
	consinfo->consType = UNCONS;
	ret = ASN1_PER_UNAlign_Dec_String(ws,value,consinfo,NORMAL_UBITS);
	if (ret<0){
		return ret;
	}
	return 0;
}



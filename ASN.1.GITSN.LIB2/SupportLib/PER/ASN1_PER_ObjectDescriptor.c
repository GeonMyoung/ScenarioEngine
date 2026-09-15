#include "ASN1_PER_ObjectDescriptor.h"

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_ObjectDescriptor (ASN1WorkSpace *ws,ObjectDescriptor *value,
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

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_ObjectDescriptor (ASN1WorkSpace *ws,ObjectDescriptor *value,
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

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_ObjectDescriptor(ASN1WorkSpace *ws,ObjectDescriptor *value,
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

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_ObjectDescriptor (ASN1WorkSpace* ws,ObjectDescriptor* value, 
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



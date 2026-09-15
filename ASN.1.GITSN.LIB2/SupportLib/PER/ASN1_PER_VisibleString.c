#include "ASN1_PER_VisibleString.h"

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_VisibleString(ASN1WorkSpace *ws,VisibleString *value,
										  Asn1ConsInfo *consinfo)
{
ASNUINT8 CharSet[] = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
	ASNINT32 ret;
	
	ret = PER_CHECK_Avail(value,CharSet,95);
	if (ret<0){
		return ret;
	}
	
	ret = ASN1_PER_Align_Enc_String(ws,value,consinfo,VIS_ABITS);
	if (ret<0){
		return ret;
	}
	
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_VisibleString(ASN1WorkSpace *ws,VisibleString *value,
											Asn1ConsInfo *consinfo)
{
ASNUINT8 CharSet[] = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
	ASNINT32 ret;
	
	ret = PER_CHECK_Avail(value,CharSet,95);
	if (ret<0){
		return ret;
	}
	
	ret = ASN1_PER_UNAlign_Enc_String(ws,value,consinfo,VIS_UBITS);
	if (ret<0){
		return ret;
	}
	
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_VisibleString(ASN1WorkSpace *ws,VisibleString *value,
										  Asn1ConsInfo *consinfo)
{
	ASNINT32 ret;
	
	ret = ASN1_PER_Align_Dec_String(ws,value,consinfo,VIS_ABITS);
	if (ret<0){
		return ret;
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_VisibleString(ASN1WorkSpace* ws,VisibleString* value, 
											Asn1ConsInfo *consinfo)
{
	ASNINT32 ret;
	
	ret = ASN1_PER_UNAlign_Dec_String(ws,value,consinfo,VIS_UBITS);
	if (ret<0){
		return ret;
	}
	return 0;
}

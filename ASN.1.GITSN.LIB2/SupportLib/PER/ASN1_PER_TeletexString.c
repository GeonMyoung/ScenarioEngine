#include "ASN1_PER_TeletexString.h"

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_TeletexString(ASN1WorkSpace *ws,TeletexString *value,
									  Asn1ConsInfo *consinfo)
{
	ASNUINT8 CharSet[] = " !\"%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]_abcdefghijklmnopqrstuvwxyz";
	ASNINT32 ret;
	consinfo->consType = UNCONS;
	ret = PER_CHECK_Avail(value,CharSet,86);
	if (ret<0){
		return ret;
	}
	
	ret = ASN1_PER_Align_Enc_String(ws,value,consinfo,T61_ABITS);
	if (ret<0){
		return ret;
	}
	
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_TeletexString(ASN1WorkSpace *ws,TeletexString *value,
										Asn1ConsInfo *consinfo)
{
	ASNUINT8 CharSet[] = " !\"%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]_abcdefghijklmnopqrstuvwxyz";
	ASNINT32 ret;
	consinfo->consType = UNCONS;
	ret = PER_CHECK_Avail(value,CharSet,86);
	if (ret<0){
		return ret;
	}
	
	ret = ASN1_PER_UNAlign_Enc_String(ws,value,consinfo,T61_UBITS);
	if (ret<0){
		return ret;
	}
	
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_TeletexString(ASN1WorkSpace *ws,TeletexString *value,
									  Asn1ConsInfo *consinfo)
{
	ASNINT32 ret;
	consinfo->consType = UNCONS;
	ret = ASN1_PER_Align_Dec_String(ws,value,consinfo,T61_ABITS);
	if (ret<0){
		return ret;
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_TeletexString(ASN1WorkSpace* ws,TeletexString* value, 
										Asn1ConsInfo *consinfo)
{
	ASNINT32 ret;
	consinfo->consType = UNCONS;
	ret = ASN1_PER_UNAlign_Dec_String(ws,value,consinfo,T61_UBITS);
	if (ret<0){
		return ret;
	}
	return 0;
}

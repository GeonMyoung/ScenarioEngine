#include "ASN1_PER_PrintableString.h"

/*PrintableString*/
ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_PrintableString(ASN1WorkSpace *ws,PrintableString *value,
										Asn1ConsInfo *consinfo)
{
	ASNUINT8 CharSet[] = " '()+,-./0123456789:=?ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	ASNINT32 ret;
	
	ret = PER_CHECK_Avail(value,CharSet,74);
	if (ret<0){
		return -ret;
	}
	
	ret = ASN1_PER_Align_Enc_String(ws,value,consinfo,PRN_ABITS);
	if (ret<0){
		return ret;
	}
	
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_PrintableString(ASN1WorkSpace *ws,PrintableString *value,
										  Asn1ConsInfo *consinfo)
{
	ASNUINT8 CharSet[] = " '()+,-./0123456789:=?ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	ASNINT32 ret;
	
	ret = PER_CHECK_Avail(value,CharSet,74);
	if (ret<0){
		return ret;
	}
	
	ret = ASN1_PER_UNAlign_Enc_String(ws,value,consinfo,PRN_UBITS);
	if (ret<0){
		return ret;
	}
	
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_PrintableString(ASN1WorkSpace *ws,PrintableString *value,
										Asn1ConsInfo *consinfo)
{
	ASNINT32 ret;
	
	ret = ASN1_PER_Align_Dec_String(ws,value,consinfo,PRN_ABITS);
	if (ret<0){
		return ret;
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_PrintableString(ASN1WorkSpace* ws,PrintableString* value, 
										  Asn1ConsInfo *consinfo)
{
	ASNINT32 ret;
	
	ret = ASN1_PER_UNAlign_Dec_String(ws,value,consinfo,PRN_UBITS);
	if (ret<0){
		return ret;
	}
	return 0;
}

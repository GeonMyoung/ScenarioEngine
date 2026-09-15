#include "ASN1_PER_NumericString.h"

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_NumericString(ASN1WorkSpace *ws,NumericString *value,
									  Asn1ConsInfo *consinfo)
{
	ASNUINT8 CharSet[] = " 0123456789";
	ASNINT32 ret;

	ret = PER_CHECK_Avail(value,CharSet,11);
	if (ret<0){
		return ret;
	}
	 
	if(NULL == consinfo->charSet){
		consinfo->charSet = CharSet;
	}

	ret = ASN1_PER_Align_Enc_String(ws,value,consinfo,NUM_ABITS);
	if (ret<0){
		return ret;
	}

	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_NumericString(ASN1WorkSpace *ws,NumericString *value,
	            						Asn1ConsInfo *consinfo)
{
	ASNUINT8 CharSet[] = " 0123456789";
	ASNINT32 ret;
	
	ret = PER_CHECK_Avail(value,CharSet,11);
	if (ret<0){
		return ret;
	}
	
	if(NULL == consinfo->charSet){
		consinfo->charSet = CharSet;
	}
	ret = ASN1_PER_UNAlign_Enc_String(ws,value,consinfo,NUM_UBITS);
	if (ret<0){
		return ret;
	}
	
	return 0;

}

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_NumericString(ASN1WorkSpace *ws,NumericString *value,
									  Asn1ConsInfo *consinfo)
{
	ASNINT32 ret;
	ASNUINT8 CharSet[] = " 0123456789";
	
	if(NULL == consinfo->charSet){
		consinfo->charSet = CharSet;
	}

	ret = ASN1_PER_Align_Dec_String(ws,value,consinfo,NUM_ABITS);
	if (ret<0){
		return ret;
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_NumericString(ASN1WorkSpace* ws,NumericString* value, 
										Asn1ConsInfo *consinfo)
{
	ASNINT32 ret;
	ASNUINT8 CharSet[] = " 0123456789";
	
	if(NULL == consinfo->charSet){
		consinfo->charSet = CharSet;
	}

	ret = ASN1_PER_UNAlign_Dec_String(ws,value,consinfo,NUM_UBITS);
	if (ret<0){
		return ret;
	}
	return 0;
}

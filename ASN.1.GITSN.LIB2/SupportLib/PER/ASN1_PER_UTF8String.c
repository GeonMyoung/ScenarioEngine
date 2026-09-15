#include "ASN1_PER_UTF8String.h"

#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
ASNINT32 ASN1_PER_Align_Enc_UTF8Str (ASN1WorkSpace *ws,UTF8Str *value, Asn1ConsInfo *consinfo)
#else
ASNINT32 ASN1_PER_Align_Enc_UTF8String (ASN1WorkSpace *ws,UTF8String *value, Asn1ConsInfo *consinfo)
#endif
{
	ASNINT32 ret;
	consinfo->consType = UNCONS;
	ret = ASN1_PER_Align_Enc_String(ws,value,consinfo,NORMAL_ABITS);
	if (ret<0){
		return ret;
	}
	
	return 0;
}

#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
ASNINT32 ASN1_PER_UNAlign_Enc_UTF8Str (ASN1WorkSpace *ws,UTF8Str *value, Asn1ConsInfo *consinfo)
#else
ASNINT32 ASN1_PER_UNAlign_Enc_UTF8String (ASN1WorkSpace *ws,UTF8String *value, Asn1ConsInfo *consinfo)
#endif
{
	ASNINT32 ret;
	consinfo->consType = UNCONS;
	ret = ASN1_PER_UNAlign_Enc_String(ws,value,consinfo,NORMAL_UBITS);
	if (ret<0){
		return ret;
	}
	
	return 0;
}

#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
ASNINT32 ASN1_PER_Align_Dec_UTF8Str(ASN1WorkSpace *ws,UTF8Str *value, Asn1ConsInfo *consinfo)
#else
ASNINT32 ASN1_PER_Align_Dec_UTF8String(ASN1WorkSpace *ws,UTF8String *value, Asn1ConsInfo *consinfo)
#endif
{
	ASNINT32 ret;
	consinfo->consType = UNCONS;
	ret = ASN1_PER_Align_Dec_String(ws,value,consinfo,NORMAL_ABITS);
	if (ret<0){
		return ret;
	}
	return 0;
}

#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
ASNINT32 ASN1_PER_UNAlign_Dec_UTF8Str (ASN1WorkSpace* ws,UTF8Str* value, Asn1ConsInfo *consinfo)
#else
ASNINT32 ASN1_PER_UNAlign_Dec_UTF8String (ASN1WorkSpace* ws,UTF8String* value, Asn1ConsInfo *consinfo)
#endif
{
	ASNINT32 ret;
	consinfo->consType = UNCONS;
	ret = ASN1_PER_UNAlign_Dec_String(ws,value,consinfo,NORMAL_UBITS);
	if (ret<0){
		return ret;
	}
	return 0;
}



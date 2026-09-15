#include "ASN1_PER_CHARACTERSTRING.h"

// Jake Lim commented : 2021-06-20
// ASNINT32 ASN1_PER_Align_Enc_Inline_CHARACTERSTRING(ASN1WorkSpace *ws, CHARACTERSTRING *value, Asn1ConsInfo *consinfo)
// {
// 	return 0;
// }

ASNINT32 ASN1_PER_Align_Enc_CHARACTERSTRING(ASN1WorkSpace *ws, CHARACTERSTRING *value, Asn1ConsInfo *consinfo)
{
	ASNINT32 ret = 0;
	ret = ASN1_PER_Align_Enc_ASN1CHARACTERSTRING(ws,value);

	return ret;
}

// Jake Lim commented : 2021-06-20
// ASNINT32 ASN1_PER_Align_Dec_Inline_CHARACTERSTRING(ASN1WorkSpace *ws, CHARACTERSTRING *value, Asn1ConsInfo *consinfo)
// {
// 	return 0;
// }

ASNINT32 ASN1_PER_Align_Dec_CHARACTERSTRING(ASN1WorkSpace *ws, CHARACTERSTRING *value, Asn1ConsInfo *consinfo)
{
	ASNINT32 ret = 0;
	ret = ASN1_PER_Align_Dec_ASN1CHARACTERSTRING(ws,value);

	return ret;
}

ASNINT32 ASN1_PER_UNAlign_Enc_CHARACTERSTRING(ASN1WorkSpace *ws, CHARACTERSTRING *value, Asn1ConsInfo *consinfo)
{
	ASNINT32 ret;
	ret = ASN1_PER_UNAlign_Enc_ASN1CHARACTERSTRING(ws,value);

	return ret;
}

ASNINT32 ASN1_PER_UNAlign_Dec_CHARACTERSTRING(ASN1WorkSpace *ws, CHARACTERSTRING *value, Asn1ConsInfo *consinfo)
{
	ASNINT32 ret = 0;
	ret = ASN1_PER_UNAlign_Dec_ASN1CHARACTERSTRING(ws,value);

	return ret;
}

ASNINT32 ASN1_PER_Enc_CHARACTERSTRING_Value(ASN1WorkSpace* ws,CHARACTERSTRING* value, ASNUINT32 length,struct PER_Flag *per_flag, ASN1PERAlign Align_Flag)
{
	return 0;
}

ASNINT32 ASN1_PER_Dec_CHARACTERSTRING_Value(ASN1WorkSpace* ws,CHARACTERSTRING* value, ASNUINT32 length,struct PER_Flag *per_flag, ASN1PERAlign Align_Flag)
{
	return 0;
}



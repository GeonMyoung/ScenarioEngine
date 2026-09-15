#include "ASN1_PER_IA5String.h"

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_IA5String(ASN1WorkSpace *ws,IA5String *value,
									  Asn1ConsInfo *consinfo)
{
	ASNUINT8 CharSet[128];
	ASNINT32 ret=0;
	ASNINT32 i=0,j=0;
	
	while(j<128){
		CharSet[j] = i;
		j++;
		i++;
	}
// 	j = 95;
// 	i = 0x00;
// 	while(i < 16)
// 	{
// 		CharSet[j] = i;
// 		j++;
// 		i++;
// 	}
// 	j = 111;
// 	i = 0x20;
// 	while(i < 56)
// 	{
// 		CharSet[j] = i;
// 		j++;
// 		i++;
// 	}
// 		

	ret = PER_CHECK_Avail(value,CharSet,128);
	if (ret<0){
		return ret;
	}
	
	ret = ASN1_PER_Align_Enc_String(ws,value,consinfo,PRN_ABITS);
	if (ret<0){
		return ret;
	}
	
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_IA5String(ASN1WorkSpace *ws,IA5String *value,
										Asn1ConsInfo *consinfo)
{
	ASNUINT8 CharSet[128];
	ASNINT32 ret;
	ASNINT32 i=0,j=0;
	
	while(j<128){
		CharSet[j] = i;
		j++;
		i++;
	}

// 	j = 95;
// 	i = 0x00;
// 	while(i < 16)
// 	{
// 		CharSet[j] = i;
// 		j++;
// 		i++;
// 	}
// 	j = 111;
// 	i = 0x20;
// 	while(i < 56)
// 	{
// 		CharSet[j] = i;
// 		j++;
// 		i++;
// 	}
	
	ret = PER_CHECK_Avail(value,CharSet,128);
	if (ret<0){
		return ret;
	}
	
	ret = ASN1_PER_UNAlign_Enc_String(ws,value,consinfo,PRN_UBITS);
	if (ret<0){
		return ret;
	}
	
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_IA5String(ASN1WorkSpace *ws,IA5String *value,
									  Asn1ConsInfo *consinfo)
{
	ASNINT32 ret;
	
	ret = ASN1_PER_Align_Dec_String(ws,value,consinfo,PRN_ABITS);
	if (ret<0){
		return ret;
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_IA5String(ASN1WorkSpace* ws,IA5String* value, 
										Asn1ConsInfo *consinfo)
{
	ASNINT32 ret;
	
	ret = ASN1_PER_UNAlign_Dec_String(ws,value,consinfo,PRN_UBITS);
	if (ret<0){
		return ret;
	}
	return 0;
}



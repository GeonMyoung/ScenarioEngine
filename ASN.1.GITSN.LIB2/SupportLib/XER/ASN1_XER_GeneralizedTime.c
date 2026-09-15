#include "ASN1_XER_GeneralizedTime.h"
ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_GeneralizedTime(ASN1WorkSpace * ws, GeneralizedTime *tvalue, 
												ASNUINT8 *name,ASNINT32 tab_value)
{
	ASNINT8 *sourceTime,*destTime;
	destTime = malloc(30);
	sourceTime = malloc(30);
	memset(destTime,0,30);
	memset(sourceTime,0,30);

	strncpy(sourceTime,tvalue->asnstring,tvalue->nchar);
 	changetimetogen(sourceTime,destTime,0);
	
	memset(tvalue->asnstring,0,tvalue->nchar);
	strcpy(tvalue->asnstring,destTime);
	tvalue->nchar = (ASNINT32)strlen(destTime);
	free(sourceTime);
	free(destTime);

	return ASN1_XER_CANONICAL_Enc_ASNSTRING(ws,tvalue,name,tab_value);
}


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_GeneralizedTime(ASN1WorkSpace * ws, GeneralizedTime *tvalue,
											ASNUINT8 *name,ASNINT32 tab_value)

{
	return ASN1_XER_BASIC_Enc_ASNSTRING(ws,tvalue,name,tab_value);
}
ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_GeneralizedTime(ASN1WorkSpace * ws, GeneralizedTime *value,
												ASNUINT8 *name,ASNINT32 tab_value)

{
	return ASN1_XER_CANONICAL_Dec_ASNSTRING(ws,value,name,tab_value);
}
ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_GeneralizedTime(ASN1WorkSpace * ws, GeneralizedTime *value,
											ASNUINT8 *name,ASNINT32 tab_value)
{
	return ASN1_XER_BASIC_Dec_ASNSTRING(ws,value,name,tab_value);
}

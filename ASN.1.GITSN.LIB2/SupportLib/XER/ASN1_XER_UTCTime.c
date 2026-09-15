#include "ASN1_XER_UTCTime.h"

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_UTCTime(ASN1WorkSpace * ws, UTCTime *tvalue, 
												ASNUINT8 *name,ASNINT32 tab_value)
{
	ASNINT8 *sourceTime,*destTime;
	destTime = malloc(30);
	sourceTime = malloc(30);

	memset(destTime,0,30);
	memset(sourceTime,0,30);

	strncpy(sourceTime,tvalue->asnstring,tvalue->nchar);
	changetimetogen(sourceTime,destTime,1);
	
	memset(tvalue->asnstring,0,tvalue->nchar);
	strcpy(tvalue->asnstring,destTime);
	tvalue->nchar = (ASNINT32)strlen(destTime);
	free(sourceTime);
	free(destTime);
	
	return ASN1_XER_CANONICAL_Enc_ASNSTRING(ws,tvalue,name,tab_value);
}


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_UTCTime(ASN1WorkSpace * ws, UTCTime *tvalue,
											ASNUINT8 *name,ASNINT32 tab_value)
											
{
	return ASN1_XER_BASIC_Enc_ASNSTRING(ws,tvalue,name,tab_value);
}
ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_UTCTime(ASN1WorkSpace * ws, UTCTime *value,
												ASNUINT8 *name,ASNINT32 tab_value)
												
{
	return ASN1_XER_CANONICAL_Dec_ASNSTRING(ws,value,name,tab_value);
}
ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_UTCTime(ASN1WorkSpace * ws, UTCTime *value,
									ASNUINT8 *name,ASNINT32 tab_value)
{
	return ASN1_XER_BASIC_Dec_ASNSTRING(ws,value,name,tab_value);
}

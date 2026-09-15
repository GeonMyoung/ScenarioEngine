#include "ASN1_XER_ENUMERATED.h"

ASN1_CPPLINK ASNINT32 ASN1_XER_Enc_ENUMERATED_Value(ASN1WorkSpace * ws,ASNSTRING *tvalue)
{
	ASNUINT8 *temp_value;

	temp_value = (ASNUINT8*)malloc((tvalue->nchar+1)*sizeof(ASNUINT8));
	memset(temp_value,0x00,(tvalue->nchar+1)*sizeof(ASNUINT8));
	memcpy(temp_value,tvalue->asnstring,tvalue->nchar);

	ASN1_XER_Enc_Backslash_Name(ws,temp_value);

	free(temp_value);
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_ENUMERATED_Value(ASN1WorkSpace * ws, ASNSTRING *value)
{
	ASNINT32 value_null = 0;
	ASNUINT8 temp_enum[512];
	ASNINT32 i = 0;
	memset(temp_enum,0x00,512);

	if(*ws->buffer.current == '<'){
		while (*ws->buffer.current != '>'){
			temp_enum[i++] = *ws->buffer.current;				
			ws->buffer.current++;
		}
		temp_enum[i++] = *ws->buffer.current;
		ws->buffer.current++;
		value->nchar = i-3;
		value->asnstring = (ASNUINT8*)mpool_malloc(ws->Pmemory,value->nchar);
		memcpy(value->asnstring,temp_enum+1,value->nchar);
	}
	else
		return -1;
	
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_ENUMERATED(ASN1WorkSpace * ws, ASNSTRING *tvalue, 
										ASNUINT8 *name,ASNINT32 tab_value)
										
{
	ASN1_XER_Enc_Start_Name(ws,name);
	
	ASN1_XER_Enc_ENUMERATED_Value(ws,tvalue);

	ASN1_XER_Enc_End_Name(ws,name);
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_ENUMERATED(ASN1WorkSpace * ws, ASNSTRING *tvalue,
									ASNUINT8 *name,ASNINT32 tab_value)
									
{
	ASN1_XER_Tab(ws,tab_value);
	ASN1_XER_CANONICAL_Enc_ENUMERATED(ws,tvalue,name,tab_value);
	ASN1_XER_Enter(ws,1);
	return 0;
	
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_ENUMERATED(ASN1WorkSpace * ws, ASNSTRING *value,
										ASNUINT8 *name,ASNINT32 tab_value)
{
	ASN1_XER_Dec_Name(ws);
	ASN1_XER_Dec_Format(ws);
	ASN1_XER_Dec_ENUMERATED_Value(ws,value);
	ASN1_XER_Dec_Format(ws);
	ASN1_XER_Dec_Name(ws);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_ENUMERATED(ASN1WorkSpace * ws, ASNSTRING *value,
									ASNUINT8 *name,ASNINT32 tab_value)
{
	ASN1_XER_Dec_Format(ws);
	ASN1_XER_CANONICAL_Dec_ENUMERATED(ws,value,name,tab_value);
/*	ASN1_XER_Dec_Format(ws);*/
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_Enc_ENUMERATED_Str(ASN1WorkSpace * ws,
									 ASNSTRING *value,ASNUINT8 *enum_value)
{
	value->nchar = (ASNINT32)strlen(enum_value);
	value->asnstring = (ASNUINT8*)mpool_malloc(ws->Pmemory,value->nchar);
	strncpy(value->asnstring,enum_value,value->nchar);

	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_ENUMERATED_Str(ASNSTRING *value,ASNUINT8 *enum_value)
{
	return strncmp(value->asnstring,enum_value,value->nchar);
}


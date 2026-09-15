#include "ASN1_XER_OBJECTIDENTIFIER.h"

ASN1_CPPLINK ASNINT32 ASN1_XER_Enc_OBJECTIDENTIFIER_Value(ASN1WorkSpace * ws,OBJECTIDENTIFIER *tvalue)
{
//	ASNUINT8 *temp_value;
	ASNUINT8 obj_value[128];
	ASNUINT32 obj_lenght = 0;

	memset(obj_value,0x00,128);

	while(obj_lenght < tvalue->numids){
		sprintf(obj_value,"%u.",tvalue->subid[obj_lenght]);
		ASN1_XER_FillBuffer(ws,obj_value, (ASNUINT32)strlen(obj_value));
		memset(obj_value,0x00,128);
		obj_lenght++;
	}
	ws->buffer.current -= 1;
	memset(ws->buffer.current,0x00,1);
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_OBJECTIDENTIFIER_Value(ASN1WorkSpace * ws, OBJECTIDENTIFIER *value)
{
	ASNUINT8 temp_value[128];
	ASNINT32 i = 0,j = 0;
	value->numids = 0;
	memset(temp_value,0x00,128);
	
	while (*ws->buffer.current != '<'){
		temp_value[i++] = *ws->buffer.current;
		ws->buffer.current++;

		if (*ws->buffer.current == '.'){
			ws->buffer.current++;
			value->subid[j++] = atoi(temp_value);
			value->numids++;
			i = 0;
			memset(temp_value,0x00,128);
			continue;
		}
	}
	
	if (*temp_value != '\0'){
		value->subid[j] = atoi(temp_value);
		value->numids++;
	}

	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_OBJECTIDENTIFIER(ASN1WorkSpace * ws, OBJECTIDENTIFIER *tvalue, 
										ASNUINT8 *name,ASNINT32 tab_value)
										
{
	if (tvalue->numids<2){
		return -603;
	}
	ASN1_XER_Enc_Start_Name(ws,name);
	ASN1_XER_Enc_OBJECTIDENTIFIER_Value(ws,tvalue);
	ASN1_XER_Enc_End_Name(ws,name);
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_OBJECTIDENTIFIER(ASN1WorkSpace * ws, OBJECTIDENTIFIER *tvalue,
									ASNUINT8 *name,ASNINT32 tab_value)
									
{
	if (tvalue->numids<2){
		return -603;
	}
	ASN1_XER_Tab(ws,tab_value);
	ASN1_XER_CANONICAL_Enc_OBJECTIDENTIFIER(ws,tvalue,name,tab_value);
	ASN1_XER_Enter(ws,1);
	return 0;
	
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_OBJECTIDENTIFIER(ASN1WorkSpace * ws, OBJECTIDENTIFIER *value,
										ASNUINT8 *name,ASNINT32 tab_value)
{
	ASN1_XER_Dec_Name(ws);
	ASN1_XER_Dec_OBJECTIDENTIFIER_Value(ws,value);
	ASN1_XER_Dec_Name(ws);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_OBJECTIDENTIFIER(ASN1WorkSpace * ws, OBJECTIDENTIFIER *value,
									ASNUINT8 *name,ASNINT32 tab_value)
{
	ASN1_XER_Dec_Format(ws);
	ASN1_XER_CANONICAL_Dec_OBJECTIDENTIFIER(ws,value,name,tab_value);
/*	ASN1_XER_Dec_Format(ws);*/
	return 0;
}

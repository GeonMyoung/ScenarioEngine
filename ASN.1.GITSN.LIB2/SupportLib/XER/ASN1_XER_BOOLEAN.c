#include "ASN1_XER_BOOLEAN.h"

ASN1_CPPLINK ASNINT32 ASN1_XER_Enc_BOOLEAN_Value(ASN1WorkSpace * ws,BOOLEAN *tvalue)
{
	if(*tvalue == 0){
		ASN1_XER_Enc_Backslash_Name(ws,"false");
	}
	else{
		ASN1_XER_Enc_Backslash_Name(ws,"true");
	}
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_BOOLEAN_Value(ASN1WorkSpace * ws, BOOLEAN *value)
{
	ASNINT32 value_null = 0;
	if(*ws->buffer.current == '<'){
		if (*(ws->buffer.current+1) == 't' ||*(ws->buffer.current+1) == 'T'){
			*value = 1;
		}
		else if(*(ws->buffer.current+1) == 'f' ||*(ws->buffer.current+1) == 'F'){
			*value = 0;
		}
		else{
			return -2;
		}

		while (*ws->buffer.current != '>'){
			ws->buffer.current++;
		}
		ws->buffer.current++;
	}
	else
		return -1;
		
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_BOOLEAN(ASN1WorkSpace * ws, BOOLEAN *tvalue, 
										ASNUINT8 *name,ASNINT32 tab_value)
										
{
	ASN1_XER_Enc_Start_Name(ws,name);
	ASN1_XER_Enc_BOOLEAN_Value(ws,tvalue);
	ASN1_XER_Enc_End_Name(ws,name);
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_BOOLEAN(ASN1WorkSpace * ws, BOOLEAN *tvalue,
									ASNUINT8 *name,ASNINT32 tab_value)
									
{
	ASN1_XER_Tab(ws,tab_value);
	ASN1_XER_CANONICAL_Enc_BOOLEAN(ws,tvalue,name,tab_value);
	ASN1_XER_Enter(ws,1);
	return 0;
	
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_BOOLEAN(ASN1WorkSpace * ws, BOOLEAN *value,
										ASNUINT8 *name,ASNINT32 tab_value)
{
	ASN1_XER_Dec_Name(ws);
	ASN1_XER_Dec_Format(ws);
	ASN1_XER_Dec_BOOLEAN_Value(ws,value);
	ASN1_XER_Dec_Format(ws);
	ASN1_XER_Dec_Name(ws);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_BOOLEAN(ASN1WorkSpace * ws, BOOLEAN *value,
									ASNUINT8 *name,ASNINT32 tab_value)
{
	ASN1_XER_Dec_Format(ws);
	ASN1_XER_CANONICAL_Dec_BOOLEAN(ws,value,name,tab_value);
/*	ASN1_XER_Dec_Format(ws);*/
	return 0;
}


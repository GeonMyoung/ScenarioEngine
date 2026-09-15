#include "ASN1_XER_BOOLEAN.h"

ASN1_CPPLINK ASNINT32 ASN1_XER_Enc_NULL_Value(ASN1WorkSpace * ws,ASNUINT8 *tvalue)
{
		ASN1_XER_Enc_Backslash_Name(ws,"NULL");
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_NULL_Value(ASN1WorkSpace * ws, ASNUINT8 *value)
{
	ASNINT32 value_null = 0;
	if(*ws->buffer.current == '<'){
		if(strncmp(ws->buffer.current+1,"NULL",4)&&strncmp(ws->buffer.current+1,"null",4)){
			return -1;
		}

// 		if (*(ws->buffer.current+1) == 'N' ||*(ws->buffer.current+1) == 'n')
// 			if (*(ws->buffer.current+2) == 'U' ||*(ws->buffer.current+2) == 'u')
// 				if (*(ws->buffer.current+3) == 'L' ||*(ws->buffer.current+3) == 'l')
// 					if (*(ws->buffer.current+4) == 'L' ||*(ws->buffer.current+4) == 'l')

		while (*ws->buffer.current != '>'){
			ws->buffer.current++;
		}
		ws->buffer.current++;
	}
	else
		return -1;
		
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_NULL(ASN1WorkSpace * ws, ASNUINT8 *tvalue, 
										ASNUINT8 *name,ASNINT32 tab_value)
										
{
	ASN1_XER_Enc_Backslash_Name(ws,name);
// 	ASN1_XER_Enc_Start_Name(ws,name);
// 	ASN1_XER_Enc_NULL_Value(ws,tvalue);
// 	ASN1_XER_Enc_End_Name(ws,name);
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_NULL(ASN1WorkSpace * ws, ASNUINT8 *tvalue,
									ASNUINT8 *name,ASNINT32 tab_value)
									
{
	ASN1_XER_Tab(ws,tab_value);
	ASN1_XER_CANONICAL_Enc_NULL(ws,tvalue,name,tab_value);
	ASN1_XER_Enter(ws,1);
	return 0;
	
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_NULL(ASN1WorkSpace * ws, ASNUINT8 *value,
										ASNUINT8 *name,ASNINT32 tab_value)
{
	if (6==ASN1_XER_Dec_Name(ws)){
		value = NULL;
		return 0;
	}
	else{
		value = NULL;
		return -1;
	}
// 	ASN1_XER_Dec_Name(ws);
// 	ASN1_XER_Dec_Format(ws);
// 	/*ASN1_XER_Dec_NULL_Value(ws,value);*/
// 	ASN1_XER_Dec_Format(ws);
// 	ASN1_XER_Dec_Name(ws);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_NULL(ASN1WorkSpace * ws, ASNUINT8 *value,
									ASNUINT8 *name,ASNINT32 tab_value)
{
	ASN1_XER_Dec_Format(ws);
	ASN1_XER_CANONICAL_Dec_NULL(ws,value,name,tab_value);
/*	ASN1_XER_Dec_Format(ws);*/
	return 0;
}


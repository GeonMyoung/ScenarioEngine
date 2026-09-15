#include "ASN1_XER_INTEGER.h"


ASN1_CPPLINK ASNINT32 my_itoa(ASNUINT8* char_value,INTEGER i_value)
{
	ASNINT32 singe = 0;
	ASNINT32 i= 0;
	ASNUINT8  temp_char;

	ASNUINT8* first;
	ASNUINT8* last;

	if (i_value == 0){
		char_value[0] = 0x30;
		return 0;
	}
	if (i_value < 0){
		i_value = -i_value;
		singe = 1;
	}
	while (i_value != 0){
		char_value[i++] = i_value%10 + 0x30;
		i_value = i_value / 10;
	}
	first= char_value;
	last = char_value+i-1;
	while(last>first && last != first){
		
		temp_char = *last;
		*last = *first;
		*first = temp_char;
		last--;
		first++;
	}
	if (singe == 1){
		memmove(char_value+1,char_value,i);
		char_value[0] = '-';
	}
	return 0;
}
ASN1_CPPLINK ASNINT32 ASN1_XER_Enc_INTEGER_Value(ASN1WorkSpace * ws,INTEGER *tvalue)
{
	ASNUINT8 temp_value[128];

	memset(temp_value,0x00,128);
	/*sprintf(temp_value,"%I64d",*tvalue);*/
	my_itoa(temp_value,*tvalue);
	ASN1_XER_FillBuffer(ws,temp_value, (ASNINT32)strlen(temp_value));
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_INTEGER_Value(ASN1WorkSpace * ws, INTEGER *value)
{
	ASNUINT8 temp_value[128];
	ASNINT32 i = 0;
	ASNINT32 flag = 0;
	*value = 0;
	memset(temp_value,0x00,128);

	while (*ws->buffer.current != '<'){
		if(*ws->buffer.current == '-'){
			ws->buffer.current++;
			flag = 1;
			continue;			
		}
		if (*ws->buffer.current < '0' || *ws->buffer.current >'9'){
			ws->buffer.current++;
			continue;
		}
		temp_value[i++] = *ws->buffer.current;
		ws->buffer.current++;
	}
	i= 0;
	while(temp_value[i] != '\0'){
		((*value)*=10);
		(*value)+=(temp_value[i]-0x30);
		i++;
	}
	if (flag == 1){
		*value = 0 - (*value);
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_INTEGER(ASN1WorkSpace * ws, INTEGER *tvalue, 
									    ASNUINT8 *name,ASNINT32 tab_value)

{
	ASN1_XER_Enc_Start_Name(ws,name);
	ASN1_XER_Enc_INTEGER_Value(ws,tvalue);
	ASN1_XER_Enc_End_Name(ws,name);
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_INTEGER(ASN1WorkSpace * ws, INTEGER *tvalue,
									ASNUINT8 *name,ASNINT32 tab_value)

{
	ASN1_XER_Tab(ws,tab_value);
	ASN1_XER_CANONICAL_Enc_INTEGER(ws,tvalue,name,tab_value);
	ASN1_XER_Enter(ws,1);
	return 0;
		
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_INTEGER(ASN1WorkSpace * ws, INTEGER *value,
										ASNUINT8 *name,ASNINT32 tab_value)
{
	ASN1_XER_Dec_Name(ws);
	ASN1_XER_Dec_INTEGER_Value(ws,value);
	ASN1_XER_Dec_Name(ws);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_INTEGER(ASN1WorkSpace * ws, INTEGER *value,
									ASNUINT8 *name,ASNINT32 tab_value)
{
	ASN1_XER_Dec_Format(ws);
	ASN1_XER_CANONICAL_Dec_INTEGER(ws,value,name,tab_value);
/*	ASN1_XER_Dec_Format(ws);*/
	return 0;
}










#include "ASN1_XER_UniversalString.h"

ASNUINT8 zero[]= {0xff,0x7f,0x3f,0x1f,0x0f,0x07,0x03,0x01,0x00};
ASNUINT8 one[] = {0x00,0x80,0xc0,0xe0,0xf0,0xf8,0xfc,0xfe,0xff};

ASN1_CPPLINK void change_uarray(ASNUINT8 *value,ASNINT32 lenght)
{
	ASNUINT8* current = value;
	ASNUINT8* temp_value;
	ASNINT32  loop_flag = 0; 
	ASNINT32  temp_lenght = lenght;

	temp_value = (ASNUINT8*)malloc(lenght);
	memset(temp_value,0x00,lenght);
	
	while (loop_flag < lenght){
		temp_value[loop_flag] = *(current+temp_lenght-1);
		loop_flag++;
		temp_lenght--;
	}
	memmove(value,temp_value,lenght);
	free(temp_value);
}

ASN1_CPPLINK ASNINT32 ASN1_XER_Enc_UniversalString_Value(ASN1WorkSpace * ws,UniversalString *tvalue)
{
	ASNUINT32 uvalue;
	ASNUINT32 *temp_value = tvalue->data;
	ASNUINT8  uarray[10];
	ASNINT32  loop_flag = tvalue->nchar;
	ASNINT32  uarray_lenght = 0;
	ASNINT32  availability_bit = 26;

	memset(uarray,0x00,10);
	
	uvalue = *temp_value;

	while(loop_flag){//while end1
		memset(uarray,0x00,10);
		uarray_lenght = 0;
		
			if(uvalue < 128){
				uarray[uarray_lenght++] = uvalue;
				if (uvalue == 38){
					memcpy(uarray,"&amp;",5);
					uarray_lenght = 5;
				}
				else if (uvalue == 60){
					memcpy(uarray,"&lt;",4);
					uarray_lenght = 4;
				}
				else if(uvalue == 62){
					memcpy(uarray,"&gt;",4);
					uarray_lenght = 4;
				}
			}
			else{
				availability_bit = 26;
				while(uvalue != 0){//while end2

					uarray[uarray_lenght] |= 0x80;
					uarray[uarray_lenght] |= (uvalue&0x3f);

					uvalue >>= 6;
					uarray_lenght++;
				}//while end2
				uarray[uarray_lenght - 1] &= zero[uarray_lenght];
				uarray[uarray_lenght - 1] |= one[uarray_lenght];
				change_uarray(uarray,uarray_lenght);
			}
		ASN1_XER_FillBuffer(ws,uarray,uarray_lenght);
		uvalue = *(++temp_value);
		loop_flag--;
	}//while end1
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_UI_CONV(ASNUINT8 *value)
{
	if (!strcmp(value,"&amp;"))
		return 38;
	if (!strcmp(value,"&lt;"))
		return 60;
	if (!strcmp(value,"&gt;"))
		return 62;
	return -1;
}
ASN1_CPPLINK ASNUINT32 ASN1_XER_UI_DEC_CONV(ASN1WorkSpace * ws)
{
	ASNUINT32 temp_ui = 0;
	ASNUINT8  loop_flag_lenght = *ws->buffer.current;
	ASNINT32 lenght = 0;

	if((*ws->buffer.current & 0x80) == 0x00){
		temp_ui = *ws->buffer.current;
		ws->buffer.current++;
	}
	else{
		while(loop_flag_lenght&0x80){
			lenght++;
			loop_flag_lenght<<=1;
		}
		temp_ui = (*ws->buffer.current & zero[lenght--]);
		ws->buffer.current++;
		
		while (lenght){
			temp_ui <<= 6;
			temp_ui += (*ws->buffer.current & 0x3f);
			ws->buffer.current++;
			lenght--;
		}
	}
	return temp_ui;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_UniversalString_Value(ASN1WorkSpace * ws, UniversalString *value)
{
	ASNUINT8  temp_value[10];
	ASNINT32  i = 0,j = 0,k = 0;
	ASNINT32  memory = 1;
	
	
	value->data = mpool_malloc(ws->Pmemory,memory*sizeof(ASNUINT32));
	value->nchar = 0;
	
	memset(temp_value,0x00,10);
	
	while(!(*ws->buffer.current == '<'|| *ws->buffer.current == '/')) {
		if(*ws->buffer.current == '&'){
			while (*ws->buffer.current != ';'){
				temp_value[j] = *ws->buffer.current;
				j++;
				ws->buffer.current++;
			}
			temp_value[j] = *ws->buffer.current;
			ws->buffer.current++;
			value->data = mpool_realloc(ws->Pmemory,
										value->data,
										++memory*sizeof(ASNUINT32));
			value->data[k++] = ASN1_XER_UI_CONV(temp_value);
			value->nchar++;
			j=0;
			memset(temp_value,0x00,10);
		}
		else{
			value->data = mpool_realloc(ws->Pmemory,
										value->data,
										++memory*sizeof(ASNUINT32));
			value->data[k++] = ASN1_XER_UI_DEC_CONV(ws);
			value->nchar++;
		}
	}

	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_UniversalString(ASN1WorkSpace * ws, UniversalString *tvalue, 
												ASNUINT8 *name,ASNINT32 tab_value)
{
	if (tvalue->nchar == 0){
		ASN1_XER_Enc_Backslash_Name(ws,name);
		return 0;
	}
	ASN1_XER_Enc_Start_Name(ws,name);
	ASN1_XER_Enc_UniversalString_Value(ws,tvalue);
	ASN1_XER_Enc_End_Name(ws,name);
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_UniversalString(ASN1WorkSpace * ws, UniversalString *tvalue,
											ASNUINT8 *name,ASNINT32 tab_value)
{
	ASN1_XER_Tab(ws,tab_value);
	ASN1_XER_CANONICAL_Enc_UniversalString(ws,tvalue,name,tab_value);
	ASN1_XER_Enter(ws,1);
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_UniversalString(ASN1WorkSpace * ws, UniversalString *value,
												ASNUINT8 *name,ASNINT32 tab_value)
{
	if (6==ASN1_XER_Dec_Name(ws)){
		value->nchar = 0;
		return 0;
	}
	ASN1_XER_Dec_UniversalString_Value(ws,value);
	ASN1_XER_Dec_Name(ws);
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_UniversalString(ASN1WorkSpace * ws, UniversalString *value,
											ASNUINT8 *name,ASNINT32 tab_value)
{
	ASN1_XER_Dec_Format(ws);
	ASN1_XER_CANONICAL_Dec_UniversalString(ws,value,name,tab_value);
/*	ASN1_XER_Dec_Format(ws);*/
	return 0;
}

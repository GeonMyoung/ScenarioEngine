#include "ASN1_XER_CHARACTERSTRING.h"


ASN1_CPPLINK ASNINT32 ASN1_XER_CHARACTERSTRING_HtoB(ASN1WorkSpace *ws,ASNUINT32 value)
{
	switch(value)
	{
	case 0:
		ASN1_XER_FillBuffer(ws,"0",1);
		break;
	case 1:
		ASN1_XER_FillBuffer(ws,"1",1);
		break;
	case 2:
		ASN1_XER_FillBuffer(ws,"2",1);
		break;
	case 3:
		ASN1_XER_FillBuffer(ws,"3",1);
		break;
	case 4:
		ASN1_XER_FillBuffer(ws,"4",1);
		break;
    case 5:
		ASN1_XER_FillBuffer(ws,"5",1);
		break;
	case 6:
		ASN1_XER_FillBuffer(ws,"6",1);
		break;
	case 7:
		ASN1_XER_FillBuffer(ws,"7",1);
		break;
	case 8:
		ASN1_XER_FillBuffer(ws,"8",1);
		break;
	case 9:
		ASN1_XER_FillBuffer(ws,"9",1);
		break;
	case 10:
		ASN1_XER_FillBuffer(ws,"A",1);
		break;
	case 11:
		ASN1_XER_FillBuffer(ws,"B",1);
		break;
	case 12:
		ASN1_XER_FillBuffer(ws,"C",1);
		break;
	case 13:
		ASN1_XER_FillBuffer(ws,"D",1);
		break;
	case 14:
		ASN1_XER_FillBuffer(ws,"E",1);
		break;
	case 15:
		ASN1_XER_FillBuffer(ws,"F",1);
		break;
	default:
		return -1;
		break;
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CHARACTERSTRING_CtoB(ASN1WorkSpace* ws,ASNUINT8 *value,
								       ASNINT32 bit_len,CHARACTERSTRING *bitValue)
{
	/*
	ASNINT32 i=0,j = 0,k = 0;
	ASNINT32 total_lenght = bit_len/2;

	bitValue->numbits = bit_len*4;
	bitValue->data = mpool_malloc(ws->Pmemory,total_lenght);
	memset(bitValue->data,0,total_lenght);
	
	if (bit_len == 0){
		return 5;
	}
	while(j<bit_len){
		if(value[j] >= '0' && value[j] <= '9'){
			value[j] -= '0';
		} 
		else if(value[j] >= 'a' && value[j] <= 'f'){
			value[j] -= 97;
			value[j] += 0x0a;
		}
		else if(value[j] >= 'A' && value[j] <= 'F'){
			value[j] -= 65;
			value[j] += 0x0a;
		}
		j++;
	}

	j = 0;
	while(total_lenght--){
		bitValue->data[i] = value[j++];
		bitValue->data[i] <<= 4;
		bitValue->data[i] |= value[j++];
		i++;
	}
	*/
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_Enc_CHARACTERSTRING_Value(ASN1WorkSpace * ws,CHARACTERSTRING *tvalue)
{
	/*
	ASNUINT8* bit_current = tvalue->data;
	ASNINT32 len = tvalue->numbits;
	
	while(len)
	{
		ASN1_XER_CHARACTERSTRING_HtoB(ws,((*bit_current)>>4));
		ASN1_XER_CHARACTERSTRING_HtoB(ws,*bit_current&0x0f);
		bit_current++;
		len--;
	}
	*/
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_CHARACTERSTRING_Value(ASN1WorkSpace * ws, CHARACTERSTRING *value)
{
	/*
	ASNINT32 bit_len = 0;
	ASNUINT8* temp_pointer = ws->buffer.current;
	
	while(*temp_pointer != '<'){
		bit_len++;
		temp_pointer++;
	}

	temp_pointer = (ASNUINT8*)malloc(bit_len*sizeof(ASNUINT8));
	memset(temp_pointer,0x00,bit_len*sizeof(ASNUINT8));
	memmove(temp_pointer,ws->buffer.current,bit_len);
	ws->buffer.current+=bit_len;
	
	ASN1_XER_CHARACTERSTRING_CtoB(ws,temp_pointer,bit_len,value);
	
	free(temp_pointer);
	*/
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_CHARACTERSTRING(ASN1WorkSpace * ws, CHARACTERSTRING *tvalue, 
												ASNUINT8 *name,ASNINT32 tab_value)
										
{
	ASNINT32 ret;
	ASN1_XER_Enc_Start_Name(ws,name);
	ret = ASN1_XER_CANONICAL_Enc_ASN1CHARACTERSTRING(ws,tvalue,XER_PRI,tab_value);
	ASN1_XER_Enc_End_Name(ws,name);
	return ret;
	/*
	if (tvalue->numbits == 0){
		ASN1_XER_Enc_Backslash_Name(ws,name);
		return 0;
	}
	ASN1_XER_Enc_Start_Name(ws,name);
	ASN1_XER_Enc_CHARACTERSTRING_Value(ws,tvalue);
	ASN1_XER_Enc_End_Name(ws,name);
	*/
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_CHARACTERSTRING(ASN1WorkSpace * ws, CHARACTERSTRING *tvalue,
									    ASNUINT8 *name,ASNINT32 tab_value)
									
{
	ASNINT32 ret;
	ASN1_XER_Tab(ws,tab_value);
	ASN1_XER_Enc_Start_Name(ws,name);
	ASN1_XER_Enter(ws,1);
	ret = ASN1_XER_BASIC_Enc_ASN1CHARACTERSTRING(ws,tvalue,XER_PRI,tab_value+1);
	ASN1_XER_Tab(ws,tab_value);
	ASN1_XER_Enc_End_Name(ws,name);
	ASN1_XER_Enter(ws,1);
	return ret;
	/*
	ASN1_XER_Tab(ws,tab_value);
	ASN1_XER_CANONICAL_Enc_CHARACTERSTRING(ws,tvalue,name,tab_value);
	ASN1_XER_Enter(ws,1);
	*/
	return 0;	
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_CHARACTERSTRING(ASN1WorkSpace * ws, CHARACTERSTRING *value,
										    ASNUINT8 *name,ASNINT32 tab_value)
{
	ASNINT32 ret;
	if (6==ASN1_XER_Dec_Name(ws)){
		return 0;
	}
	ret = ASN1_XER_CANONICAL_Dec_ASN1CHARACTERSTRING(ws,value,XER_PRI,tab_value);
	ASN1_XER_Dec_Name(ws);
	return ret;
	/*
	if (6==ASN1_XER_Dec_Name(ws)){
		value->numbits = 0;
		return 0;
	}
	ASN1_XER_Dec_CHARACTERSTRING_Value(ws,value);
	ASN1_XER_Dec_Name(ws);
	*/
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_CHARACTERSTRING(ASN1WorkSpace * ws, CHARACTERSTRING *value,
									    ASNUINT8 *name,ASNINT32 tab_value)
{
	ASNINT32 ret;
	ASN1_XER_Dec_Format(ws);
	if (6==ASN1_XER_Dec_Name(ws)){
		return 0;
	}
	ret = ASN1_XER_BASIC_Dec_ASN1CHARACTERSTRING(ws,value,XER_PRI,tab_value+1);
	ASN1_XER_Dec_Name(ws);
	ASN1_XER_Dec_Format(ws);
	return ret;
	/*
	ASN1_XER_Dec_Format(ws);
	ASN1_XER_CANONICAL_Dec_CHARACTERSTRING(ws,value,name,tab_value);
	ASN1_XER_Dec_Format(ws);
	*/
	return 0;
}

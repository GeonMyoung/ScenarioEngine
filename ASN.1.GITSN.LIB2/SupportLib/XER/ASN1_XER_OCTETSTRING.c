#include "ASN1_XER_OCTETSTRING.h"

ASN1_CPPLINK ASNINT32 ASN1_XER_OCTETSTRING_HtoB(ASN1WorkSpace *ws,ASNUINT32 value)
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

ASN1_CPPLINK ASNINT32 ASN1_XER_OCTETSTRING_CtoB(ASN1WorkSpace* ws,ASNUINT8 *value,
								   ASNINT32 bit_len,OCTETSTRING *bitValue)
{	
	ASNINT32 i=0,j = 0,k = 0;
	ASNINT32 total_lenght = bit_len/2;

	bitValue->numbits = total_lenght;
	bitValue->data = mpool_malloc(ws->Pmemory,total_lenght);
	memset(bitValue->data,0,total_lenght);
	
	if (bit_len == 0){
		return 5;
	}
	while(j<bit_len){
		if(value[j] >= '0' && value[j] <= '9'){
			*(value+j) = *(value+j) - 0x30;
		} 
		else if(value[j] >= 'a' && value[j] <= 'f'){
			*(value+j) -= 97;
			value[j] += 0xa;
		}
		else if(value[j] >= 'A' && value[j] <= 'F'){
			*(value+j) -= 65;
			value[j] += 0xa;
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
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_Enc_OCTETSTRING_Value(ASN1WorkSpace * ws,OCTETSTRING *tvalue)
{
	ASNUINT8* bit_current = tvalue->data;
	ASNINT32 len = tvalue->numbits;
	
	while(len)
	{
		ASN1_XER_OCTETSTRING_HtoB(ws,((*bit_current)>>4));
		ASN1_XER_OCTETSTRING_HtoB(ws,*bit_current&0x0f);
		bit_current++;
		len--;
	}
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_OCTETSTRING_Value(ASN1WorkSpace * ws, OCTETSTRING *value)
{
	ASNINT32 bit_len = 0;
	ASNUINT8* temp_pointer = ws->buffer.current;
	ASNUINT8* compare_pointer;
	ASNINT32 i = 0 ,j = 0;
	
	while(*temp_pointer != '<'){
		bit_len++;
		temp_pointer++;
	}

	temp_pointer = (ASNUINT8*)malloc(bit_len*sizeof(ASNUINT8));
	compare_pointer = (ASNUINT8*)malloc(bit_len*sizeof(ASNUINT8));
	
	memset(temp_pointer,0x00,bit_len*sizeof(ASNUINT8));
	memset(compare_pointer,0x00,bit_len*sizeof(ASNUINT8));
	memmove(temp_pointer,ws->buffer.current,bit_len);
	ws->buffer.current+=bit_len;

	while (i<bit_len){
		
		if (temp_pointer[i] == 0x20 || temp_pointer[i] == 0x0a){
			i++;
			continue;
		}
		else if(!((temp_pointer[i] >= '0' && temp_pointer[i] <='9')||
			(temp_pointer[i]>= 'A'&&temp_pointer[i] <= 'F')||
			(temp_pointer[i]>= 'a'&&temp_pointer[i] <= 'f'))){
			i++;
			continue;
		}
		else{
			compare_pointer[j++] = temp_pointer[i++];
		}
	}
	memset(temp_pointer,0,bit_len);
	memmove(temp_pointer,compare_pointer,j);
	bit_len = j;
	ASN1_XER_OCTETSTRING_CtoB(ws,temp_pointer,bit_len,value);
	



	free(compare_pointer);
	free(temp_pointer);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_OCTETSTRING(ASN1WorkSpace * ws, OCTETSTRING *tvalue, 
										    ASNUINT8 *name,ASNINT32 tab_value)
										
{
	if (tvalue->numbits == 0){
		ASN1_XER_Enc_Backslash_Name(ws,name);
		return 0;
	}
	ASN1_XER_Enc_Start_Name(ws,name);
	ASN1_XER_Enc_OCTETSTRING_Value(ws,tvalue);
	ASN1_XER_Enc_End_Name(ws,name);
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_OCTETSTRING(ASN1WorkSpace * ws, OCTETSTRING *tvalue,
									    ASNUINT8 *name,ASNINT32 tab_value)
									
{
	ASN1_XER_Tab(ws,tab_value);
	ASN1_XER_CANONICAL_Enc_OCTETSTRING(ws,tvalue,name,tab_value);
	ASN1_XER_Enter(ws,1);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_OCTETSTRING(ASN1WorkSpace * ws, OCTETSTRING *value,
										    ASNUINT8 *name,ASNINT32 tab_value)
{
	if (6==ASN1_XER_Dec_Name(ws)){
		value->numbits = 0;
		return 0;
	}
	ASN1_XER_Dec_OCTETSTRING_Value(ws,value);
	ASN1_XER_Dec_Name(ws);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_OCTETSTRING(ASN1WorkSpace * ws, OCTETSTRING *value,
									    ASNUINT8 *name,ASNINT32 tab_value)
{
	ASN1_XER_Dec_Format(ws);
	ASN1_XER_CANONICAL_Dec_OCTETSTRING(ws,value,name,tab_value);
/*	ASN1_XER_Dec_Format(ws);*/
	return 0;
}


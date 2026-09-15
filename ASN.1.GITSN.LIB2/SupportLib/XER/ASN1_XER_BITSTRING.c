#include "ASN1_XER_BITSTRING.h"
ASN1_CPPLINK void xer_remove_invalid_zeros(BITSTRING *BitVectorValue);
ASN1_CPPLINK ASNINT32 ASN1_XER_BITSTRING_HtoB(ASN1WorkSpace *ws,ASNUINT32 value)
{
	switch(value)
	{
	case 0:
		ASN1_XER_FillBuffer(ws,"0000",4);
		break;
	case 1:
		ASN1_XER_FillBuffer(ws,"0001",4);
		break;
	case 2:
		ASN1_XER_FillBuffer(ws,"0010",4);
		break;
	case 3:
		ASN1_XER_FillBuffer(ws,"0011",4);
		break;
	case 4:
		ASN1_XER_FillBuffer(ws,"0100",4);
		break;
    case 5:
		ASN1_XER_FillBuffer(ws,"0101",4);
		break;
	case 6:
		ASN1_XER_FillBuffer(ws,"0110",4);
		break;
	case 7:
		ASN1_XER_FillBuffer(ws,"0111",4);
		break;
	case 8:
		ASN1_XER_FillBuffer(ws,"1000",4);
		break;
	case 9:
		ASN1_XER_FillBuffer(ws,"1001",4);
		break;
	case 10:
		ASN1_XER_FillBuffer(ws,"1010",4);
		break;
	case 11:
		ASN1_XER_FillBuffer(ws,"1011",4);
		break;
	case 12:
		ASN1_XER_FillBuffer(ws,"1100",4);
		break;
	case 13:
		ASN1_XER_FillBuffer(ws,"1101",4);
		break;
	case 14:
		ASN1_XER_FillBuffer(ws,"1110",4);
		break;
	case 15:
		ASN1_XER_FillBuffer(ws,"1111",4);
		break;
	default:
		return -1;
		break;
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_BITSTRING_CtoB(ASN1WorkSpace* ws,const ASNUINT8 *value,
								 ASNINT32 bit_len,BITSTRING *bitValue)
{	
	ASNUINT32 i,j = 0,k = 0;
	ASNINT32 total_lenght = (bit_len+7) / 8;
	ASNINT32 bit_lenght = bit_len/8;
	ASNINT32 remainder_lenght = bit_len%8;

	bitValue->numbits = bit_len;
	bitValue->data = mpool_malloc(ws->Pmemory,total_lenght);
	memset(bitValue->data,0,total_lenght);
	
	if (bit_len == 0){
		return 5;
	}

	while(bit_lenght--)
	{
		for (i = 0;i<8;i++)				// fill buffer data
			bitValue->data[j] |= ((value[i]-0x30) << (7-i));	
		value += 8;
		j++;		
	}
	i = 0;
	while (remainder_lenght--)					//process remainder fill buffer data
	{	
		bitValue->data[j] |= ((value[i]-0x30) << (7-i));
		i++;
	}	
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_Enc_BITSTRING_Value(ASN1WorkSpace * ws,BITSTRING *tvalue)
{
	ASNUINT8* bit_current = tvalue->data;
	ASNINT32 len = (tvalue->numbits+7) / 8;
	
	while(len)
	{
		ASN1_XER_BITSTRING_HtoB(ws,((*bit_current)>>4));
		ASN1_XER_BITSTRING_HtoB(ws,*bit_current&0x0f);
		bit_current++;
		len--;
	}
	if ((tvalue->numbits%8) != 0){
		ws->buffer.current -= (8-(tvalue->numbits%8));
		memset(ws->buffer.current,0x00,(8-(tvalue->numbits%8)));
	}
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_BITSTRING_Value(ASN1WorkSpace * ws, BITSTRING *value)
{
	ASNINT32 bit_len = 0,i=0,j=0;
	ASNUINT8* compare_pointer;
	ASNUINT8* temp_pointer = ws->buffer.current;
	
	while(*temp_pointer != '<'){
		bit_len++;
		temp_pointer++;
	}

	temp_pointer = (ASNUINT8*)malloc(bit_len*sizeof(ASNUINT8));
	memset(temp_pointer,0x00,bit_len*sizeof(ASNUINT8));
	compare_pointer = (ASNUINT8*)malloc(bit_len*sizeof(ASNUINT8));
	memset(compare_pointer,0x00,bit_len*sizeof(ASNUINT8));
	memmove(temp_pointer,ws->buffer.current,bit_len);
	ws->buffer.current+=bit_len;

	while (i<bit_len)
	{
		if (temp_pointer[i]=='0' || temp_pointer[i]=='1')
		{
			compare_pointer[j++] =temp_pointer[i];
		}
		i++;
	}
	memset(temp_pointer,0,bit_len);
	memmove(temp_pointer,compare_pointer,j);
	bit_len = j;

	ASN1_XER_BITSTRING_CtoB(ws,temp_pointer,bit_len,value);
	
	free(compare_pointer);
	free(temp_pointer);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_BITSTRING(ASN1WorkSpace * ws, BITSTRING *tvalue, 
										  ASNUINT8 *name,ASNINT32 bitlist,ASNINT32 tab_value)
										
{
	if (bitlist){
		xer_remove_invalid_zeros(tvalue);
	}
	if (tvalue->numbits == 0){
		ASN1_XER_Enc_Backslash_Name(ws,name);
		return 0;
	}
	ASN1_XER_Enc_Start_Name(ws,name);
	ASN1_XER_Enc_BITSTRING_Value(ws,tvalue);
	ASN1_XER_Enc_End_Name(ws,name);
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_BITSTRING(ASN1WorkSpace * ws, BITSTRING *tvalue,
									ASNUINT8 *name,ASNINT32 bitlist,ASNINT32 tab_value)
									
{
	ASN1_XER_Tab(ws,tab_value);
	if (tvalue->numbits == 0){
		ASN1_XER_Enc_Backslash_Name(ws,name);
		return 0;
	}
	ASN1_XER_Enc_Start_Name(ws,name);
	ASN1_XER_Enc_BITSTRING_Value(ws,tvalue);
	ASN1_XER_Enc_End_Name(ws,name);

//	ASN1_XER_CANONICAL_Enc_BITSTRING(ws,tvalue,name,tab_value);
	ASN1_XER_Enter(ws,1);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_BITSTRING(ASN1WorkSpace * ws, BITSTRING *value,
										ASNUINT8 *name,ASNINT32 tab_value)
{
	if (6==ASN1_XER_Dec_Name(ws)){
		value->numbits = 0;
		return 0;
	}
	ASN1_XER_Dec_BITSTRING_Value(ws,value);
	ASN1_XER_Dec_Name(ws);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_BITSTRING(ASN1WorkSpace * ws, BITSTRING *value,
									ASNUINT8 *name,ASNINT32 tab_value)
{
	ASN1_XER_Dec_Format(ws);
	ASN1_XER_CANONICAL_Dec_BITSTRING(ws,value,name,tab_value);
/*	ASN1_XER_Dec_Format(ws);*/
	return 0;
}

ASN1_CPPLINK void xer_remove_invalid_zeros(BITSTRING *BitVectorValue)
{
	ASNUINT32 Length = BitVectorValue->numbits;
	ASNUINT32 byteCount, bitCount;
	
	while(Length)
	{
		byteCount = ((Length+7)>>3) - 1;
		bitCount = Length - byteCount * 8 - 1;
		if(BitVectorValue->data[byteCount] & (0x80 >> bitCount))
		{
			break;
		}
		Length--;
	}
	BitVectorValue->numbits = Length;
	
#if 0
	ASNUINT8 res = 0;
	
	Length = (BitVectorValue->numbits + 7) >> 3;
	res = 8 - BitVectorValue->numbits & 7;
	
	if (BitVectorValue->data[--Length] == 0) 
	{
		BitVectorValue->numbits -= 8 - res;	
		
		while (-1 != --Length) 
		{
			if (BitVectorValue->data[Length]) 
			{
				res = 0;
				
				while (!(BitVectorValue->data[Length]&(1<<res)))
				{
					BitVectorValue->numbits--;
					res++;
				}
				
				return;
			}
			
			BitVectorValue->numbits -= 8;
		}
	}
	else
	{
		while (!(BitVectorValue->data[Length]&(1<<res)))
		{
			BitVectorValue->numbits--;
			res++;
		}
		
		return;
	}
#endif
}

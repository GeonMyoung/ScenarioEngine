#include "ASN1_BER_ENUMERATED.h"
#include "math.h"

#define strange_data 1024

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_ENUMERATED_Value(ASN1WorkSpace *ws,ENUMERATED *Tvalue)
{
	ASNUINT8 enc_value[8];
	ASNINT32 length = 0;
	ASNINT32 j = 0;
	ASNINT32 ret = 0;
	ASNINT32 flag = 0;
	ASNINT64 quot = 0;
	ASNINT64 value = *Tvalue;
	if(value < 0)
	{
		flag = 1;
		value = -value;
	}
	ret = (ASNINT32)(value % 256);
	value = value / 256;
	memset(enc_value,0,8);
	enc_value[length++] = ret;
	if (value == 0)
		ws->dataSize = length;
	
	while(value)
	{	
		quot = value / 256;
		ret = (ASNINT32)(value % 256);
		enc_value[length++] = ret; 
		value = quot;
	}
	if(enc_value[length-1] & 0x80)
		enc_value[length++] = 0;
	ws->dataSize = length;
	ASN1_BER_Enc_Length(ws,ws->dataSize);

	if((ws->buffer.current + length) >= ws->buffer.end){
		ASN1_RESET_WS_INFO(ws,(ws->buffer.end-ws->buffer.data)+length);
	}

	for(j = 0;j < length;j++)
	{
		ws->buffer.current[j] =  enc_value[length-1-j];
	}
	if(flag == 1)
	{
		int i = 0;
		for(j = 0;j < length;j++)
			ws->buffer.current[j] =  ~(ws->buffer.current[j]);
		ws->buffer.current[j-1] += 1;
		while (ws->buffer.current[j-i-1] == 0)
		{
			ws->buffer.current[j-i-2] += 1;
			i++;
			if (i > j)
				break;
		}
	}
//	ws->buffer.current[j] = 0;
	ws->buffer.current = ws->buffer.current + length;
	return 0;
}



ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_ENUMERATED_Value(ASN1WorkSpace *ws,ENUMERATED* value,ASNUINT32L length)
{
	ASNUINT32 i,j = 1;
	ASNINT8 flag = (ws->buffer.current[0] & 0x80);
	if(flag)
	{
		for(i = 0;i < length-1;i++)
		{
			ws->buffer.current[i] = ~ws->buffer.current[i]; 
		}
		ws->buffer.current[length -1] = ~(ws->buffer.current[length -1]) + 1;
		while (0 == ws->buffer.current[length - j++] && j<=length)
		{
			ws->buffer.current[length - j] += 1;
		}
		*value = ws->buffer.current[0];
	}
	else
	{
		*value = ws->buffer.current[0];
	}
	for (i = 1;i<length;i++)
	{
		*value <<= 8;
		*value += ws->buffer.current[i];
	}
	*value = flag ? -*value :*value;
	ws->buffer.current += length;
	return 0;
}




ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_ENUMERATED(ASN1WorkSpace *ws,ENUMERATED *Tvalue,ASN1TagType flag)
{
	ASN1_Tag_Move_Pointer(ws,ITS_ASN_UNIV|ITS_ASN_PRIM|ASN1_TYPE_ENUMERATED,flag);
	ASN1_BER_Enc_ENUMERATED_Value(ws,Tvalue);	
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_ENUMERATED(ASN1WorkSpace *ws,ENUMERATED *value,ASNINT32 length,ASN1TagType flag)
{
	if (ASN1EXPL == flag)
	{
		ASN1_BER_Dec_Tag(ws,ITS_ASN_UNIV|ITS_ASN_PRIM|ASN1_TYPE_ENUMERATED);
		ASN1_BER_Dec_Length(ws);
		ASN1_BER_Dec_ENUMERATED_Value(ws,value,ws->dataSize);
	}
	
    else
	ASN1_BER_Dec_ENUMERATED_Value(ws,value,length);

	return 0;
}




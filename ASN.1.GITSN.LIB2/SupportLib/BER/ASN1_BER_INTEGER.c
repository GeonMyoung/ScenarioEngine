#include "ASN1_BER_INTEGER.h"

#include "TOOL/Infinite_tool.h"

#include "math.h"
#include "stdlib.h"

#define strange_data 1024

ASN1_CPPLINK int ASN1_BER_Enc_INTEGER_Value(ASN1WorkSpace *ws,INTEGER *Tvalue)
{
	ASNUINT8 enc_value[9];	// Jake Lim 8 -> 9
	ASNINT8 length = 0;
	ASNINT64 j = 0;
	ASNINT8 ret = 0;
	ASNINT8 flag = 0;
	ASNINT64 quot = 0;
	ASNINT64 value = *Tvalue;
	if(value < 0)
	{
		flag = 1;
		value = -value;
	}
	ret = (ASNINT8)(value % 256);
	value = value / 256;
	memset(enc_value,0,8);
	enc_value[length++] = ret;
	if (value == 0)
		ws->dataSize = length;
	
	while(value)
	{	
		quot = value / 256;
		ret = (ASNINT8)(value % 256);
		enc_value[length++] = ret; 
		value = quot;
	}
	if(enc_value[length-1] & 0x80)
		enc_value[length++] = 0;
	ws->dataSize = length;
	ASN1_BER_Enc_Length(ws,ws->dataSize);

	if((ws->buffer.current + length)>ws->buffer.end){
		ASN1_RESET_WS_INFO(ws,(ws->buffer.end - ws->buffer.data)+length);
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



ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_INTEGER_OSUINT8_Value(ASN1WorkSpace *ws,ASNUINT8 *value)
{
	ASNINT32L middata;
	ASNINT32L length;
	ASNINT32 rem;
	ASNINT32L i;
	ASNINT32 m;
	ASNINT32 flag = 0;
	ASNINT32 flag1 = 0;
	ASNINT8 temp;
	ASNINT8 *q;
	ASNINT8 r[strange_data];
	p_data *phead,*pcur;
		
	ws->dataSize =0;
	length = (ASNINT32L)strlen(value);
	if('0' == *value && 1 == length)
	{
		ws->buffer.current[0] = 0;
		ws->dataSize = 1;
		return 0;
	}
	q = value;
	while('0' == *value )
	{
		value++;
		if((ASNUINT8 *)(q+length-1) == value)
			break;
	}
	
	if ('-' == *value) 
	{
		value++;
		flag = 1;
	}
	q = value;
	if ('-' != *value)
	{	
		while(*value)
		{
			if(*value < '0' || *value > '9')
			{
				flag1 = 1;
				break;
			}
			value++;
		}
	}
	else
	{
		return 1;//char appear
	}
	memset(r,0,strange_data);
	if(0 == flag1)
	{
		value = q;
		pcur = phead = ITS_ASN_k_malloc();
		ITS_ASN_turn_long_save(value,phead);
		pcur=pcur->next;
		while (pcur!=NULL)
		{  		  	
			rem = ITS_ASN_to_ldiv(phead);
			
			ws->buffer.current[ws->dataSize] = rem; 
			middata=pcur->data;
			if (middata==0)
				pcur=pcur->next;
			ws->dataSize += 1;
		}	
		ws->buffer.current[ws->dataSize] = 0;
		ws->dataSize += 1;
//		ws->buffer.current[ws->dataSize] = 0;
		
		free(phead);
		//start<>end
		m = (ws->dataSize-2)/2;
		for(i = 0;i<=m;i++)
		{
			temp = ws->buffer.current[ws->dataSize-1-i];
			ws->buffer.current[ws->dataSize-1-i] = ws->buffer.current[i];
			ws->buffer.current[i] = temp;
		}
		//	strcpy(r,buf->buffer.data);
		for(i = 0;i<ws->dataSize;i++)
			r[i] = ws->buffer.current[i];
		if (!(r[1] &0x80))
		{
			ws->dataSize -= 1;
		}
		ASN1_BER_Enc_Length(ws,ws->dataSize);
//		free(ws->buffer.data);
//		ws->buffer.data = ASN1_REALLOC(ws->buffer.data, ws->dataSize);
		//	strcpy(buf->buffer.data,r);
		
		
		if(r[1] & 0x80)
		{
			for(i = 0;i<ws->dataSize;i++)
				ws->buffer.current[i] = r[i];
		}
		else
		{	
			for (i = 0;i<ws->dataSize;i++)
				ws->buffer.current[i] = r[i+1];
		}
		if(1 == flag)
		{
			for(i = 0;i<ws->dataSize;i++)
				ws->buffer.current[i] = ~(ws->buffer.current[i]);
			ws->buffer.current[ws->dataSize-1] = ~(ws->buffer.current[ws->dataSize-1])+1;
			i = 1;
			while(ws->buffer.current[ws->dataSize-i]==0 && i<=ws->dataSize-1)
			{
				ws->buffer.current[ws->dataSize-i-1] += 1;
				i++;
			}
		}
	}
//	memcpy(ws->buffer.data,ws->buffer.current,ws->dataSize);
	ws->buffer.current = ws->buffer.current + ws->dataSize;
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_INTEGER_Value(ASN1WorkSpace *ws,INTEGER *value,ASNINT32 length)
{
	INTEGER temp;
	ASNINT32 i,j = 1;
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

	temp = *value;		// add
	for (i = 1;i<length;i++)
	{
	/*
		*value <<= 8;
		*value += ws->buffer.current[i];
	*/
		temp <<= 8;
		temp += ws->buffer.current[i];
	}
	*value = temp;		// add

	*value = flag ? -(*value) : (*value);
	ws->buffer.current += length;
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_INTEGER_OSUINT8_Value(ASN1WorkSpace *ws,ASNUINT8 *value,ASNUINT32L length)
{
	ASNUINT8 *pstr = (ASNUINT8 *)mpool_malloc(ws->Pmemory,length * 2);/*store 16 string*/
	ASNUINT8 *exp16 = (ASNUINT8 *)mpool_malloc(ws->Pmemory,length * 3);
	ASNUINT8 *exp16temp = (ASNUINT8 *)mpool_malloc(ws->Pmemory,length * 3);
	ASNUINT32 i,j = 0,k= 0;
	ASNUINT32 count = 0;
	ASNUINT8 sign = ws->buffer.current[0] & 0x80;
	value = (ASNUINT8 *)mpool_malloc(ws->Pmemory,length*3);
	//	value = malloc(length * 3);/*store 10 string*/
	memset(value,0x30,length * 3);
	memset(exp16,0x30,length * 3-1);
	exp16[length * 3-1] = 0x31;
	exp16[length * 3] = 0;
// 	if (!ws->buffer.current[0])/*0x00*/
// 	{
// 		ws->buffer.current++;
// 		length -= 1;
// 	}
	 if (sign)/*-*/
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
	}
	for (i = 0;i < length ;i++)
	{
		for (j = 2;j>0;j--)
		{
			pstr[k++] = (ws->buffer.current[i] >> ((j-1) * 4)) & 0x0f; 
		}
	}
// 	for (i = 0;i < k;i++)
// 	{
// 		printf("%02x\n",pstr[i]);
// 	}
	for (i = 0;i < k;i++)
	{
		if(0 == pstr[i])
		{
			continue;
		}
		for (j = 1;j<k-i;j++)
		{
			exp16 = ITS_ASN_multip(exp16);
		}
		strcpy(exp16temp,exp16);
		for (j = 1;j<pstr[i];j++)
		{
			ITS_ASN_add(exp16,exp16temp);
		}
		ITS_ASN_add(value,exp16);
		memset(exp16,0x30,length * 3-1);
		exp16[length * 3-1] = 0x31;
		exp16[length * 3] = 0;
	}
	i = 0;
	while (value[i] == 0x30)
	{
		i++;
	}
	count = length * 3 - i;
	if (sign)
	{
		i--;
		value[i] = '-';
		memcpy(value,i+value,count+1);
		value[count+1] = 0;
	}
	else
	{
		memcpy(value,i+value,count);
		value[count] = 0;
	}
	
	ws->buffer.current += length;	
//	free(exp16);
//	free(pstr);
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_INTEGER(ASN1WorkSpace *ws,INTEGER *Tvalue,ASN1TagType flag)
{
	ASN1_Tag_Move_Pointer(ws,ASN1_TYPE_INTEGER,flag);
	ASN1_BER_Enc_INTEGER_Value(ws,Tvalue);	
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_INTEGER(ASN1WorkSpace *ws,INTEGER* value,
									  ASNINT32 length,ASN1TagType flag)
{
	if(ASN1EXPL == flag)
	{
		ASN1_BER_Dec_Tag(ws,ITS_ASN_UNIV|ITS_ASN_PRIM|ASN1_TYPE_INTEGER);
		ASN1_BER_Dec_Length(ws);
		ASN1_BER_Dec_INTEGER_Value(ws,value,ws->dataSize);		

	}
    else
	ASN1_BER_Dec_INTEGER_Value(ws,value,length);
	
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_INTEGER_OSUINT8(ASN1WorkSpace *ws,ASNUINT8 *value,ASN1TagType flag)
{
	ASN1_Tag_Move_Pointer(ws,ITS_ASN_UNIV|ITS_ASN_PRIM|ASN1_TYPE_INTEGER,flag);
	ASN1_BER_Enc_INTEGER_OSUINT8_Value(ws,value);	
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_INTEGER_OSUINT8(ASN1WorkSpace *ws,ASNUINT8 *value,
									  ASNINT32 length,ASN1TagType flag)
{
	if(ASN1EXPL == flag)
	{
		ASN1_BER_Dec_Tag(ws,ITS_ASN_UNIV|ITS_ASN_PRIM|ASN1_TYPE_INTEGER);
		ASN1_BER_Dec_Length(ws);
		ASN1_BER_Dec_INTEGER_OSUINT8_Value(ws,value,ws->dataSize);
	}
    else
		ASN1_BER_Dec_INTEGER_OSUINT8_Value(ws,value,length);

	return 0;
}


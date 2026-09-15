#include "ASN1_PER_INTEGER.h"
#include "math.h"
#include "stdlib.h"

#define strange_data 1024

ASN1_CPPLINK ASNINT32 ASN1_PER_Enc_UnConsINTEGER(ASN1WorkSpace * ws, INTEGER *tvalue,ASNUINT8 *enc_value)
{
	ASNINT64 j = 0;
	ASNUINT8 ret = 0;
	ASNINT8 flag = 0;
	ASNINT64 quot = 0;
	ASNINT8 length = 0;
	ASNUINT8 k=1;
	ASNINT64 tmpvalue = *tvalue,value = *tvalue;

	if(value < 0)
	{
		flag = 1;
		value = -value;
		tmpvalue = -tmpvalue;
	}
	while (tmpvalue>>=1)
	{
		k++;
	}
	
	ret = (ASNUINT8)(value % 256);
	value >>=8;
	memset(enc_value,0,8);
	enc_value[length++] = ret;
	if (value == 0){};
		//ws->buffer.byteIndex = length*8;
	
	while(value)
	{	
		quot = value >>8;
		ret = (ASNINT8)(value % 256);
		enc_value[length++] = ret; 
		value = quot;
	}
	if(enc_value[length-1] & 0x80)
		enc_value[length++] = 0;
	ws->dataSize = length;	
	if(flag == 1)
	{
		int i = 0;
		for(j = length - 1;j >=0;j--)
			enc_value[j] =  ~(enc_value[j]);
		enc_value[0] += 1;
		while (enc_value[0+i] == 0)
		{
			enc_value[i+1] += 1;
			
			if (i >= length-1)
				break;
			i++;
		}
		k = ((k / 8) + 1) * 8;
	}

	ws->buffer.byteIndex = k;
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_PER_Dec_INTEGER_Value(ASNUINT8 *decvalue,INTEGER *value,ASNINT32 length,ASNUINT8 negativeflag)
{
	ASNINT32 i,j = 1;
	ASNINT8 flag = (decvalue[0] & 0x80);
	if(flag && (negativeflag != 0) )
	{
		for(i = 0;i < length-1;i++)
		{
			decvalue[i] = ~decvalue[i]; 
		}
		decvalue[length -1] = ~(decvalue[length -1]) + 1;
		while (0 == decvalue[length - j++] && j<=length)
		{
			decvalue[length - j] += 1;
		}
		*value = decvalue[0];
	}
	else
	{
		*value = decvalue[0];
	}
	for (i = 1;i<length;i++)
	{
		*value <<= 8;
		*value += decvalue[i];
	}
	*value = (flag && (negativeflag != 0) )? -*value :*value;

	return 0;
}




ASNINT32 ASN1_PER_Align_Enc_INTEGER(ASN1WorkSpace * ws, INTEGER *tvalue, Asn1ConsInfo *conss)
{
	ASNUINT8 enc_value[8];
	ASNUINT8 i;
	ASNINT8 j;
	ASNUINT8 length;
	ASNINT64 value;
	ASNUINT64 range,tmprange;
	value = *tvalue;
	if (conss->consType==UNCONS)
	{
		if (conss->extflag)
		{
			length = value > conss->upper;
			ASN1_FillBuffer(ws, &length, 1, UNALIGN);
		}
		else if (value > conss->upper) return -1;

		ASN1_PER_Enc_UnConsINTEGER(ws, &value, enc_value);
		length = (ws->buffer.byteIndex + 7) / 8;
		if ((enc_value[length -1] & 0x80) != 0 && value > 0) length = length + 1;
		ASN1_FillBuffer(ws, &length, 8, ALIGN);
		// printf("align length%02x\n", length);

		for(j = length - 1; j >= 0; j--)
		{
			// printf("%02x",enc_value[j]);
			ASN1_FillBuffer(ws, &enc_value[j], 8, ALIGN);
		}
		return 0;
	}
	else if (value < conss->lower)
	{
		if (conss->extflag != 0)
		{
			// printf("extout");
			enc_value[0] = 1;
			ASN1_FillBuffer(ws, &enc_value[0], 1, UNALIGN);
			ASN1_PER_Enc_UnConsINTEGER(ws, &value, enc_value);
			
			//ASN1_PER_Enc_intUnConsLength( ws, &ws->buffer.byteIndex);
			length = (ws->buffer.byteIndex + 7) / 8;
			if ((enc_value[length -1] & 0x80) != 0 && value > 0) length = length + 1;
			// printf("%02x",length);
			ASN1_FillBuffer(ws, &length, 8, ALIGN);
			for (j = length - 1; j >= 0; j--)
			{
				// printf("%02x",enc_value[j]);
				ASN1_FillBuffer(ws, &enc_value[j], 8, ALIGN);
			}
			return 0;
		}
		else return -1;
	}
	else if (conss->consType == CONS)
	{
		if (value > conss->upper )
		{
			if (conss->extflag != 0)
			{
				// printf("extout");
				enc_value[0] = 1;
				ASN1_FillBuffer(ws, &enc_value[0], 1, UNALIGN);
				ASN1_PER_Enc_UnConsINTEGER(ws, &value, enc_value);

				//ASN1_PER_Enc_intUnConsLength( ws, &ws->buffer.byteIndex);
				length = (ws->buffer.byteIndex + 7) / 8;
				if ((enc_value[length -1] & 0x80) != 0 && value > 0) length = length + 1;
				// printf("%02x",length);
				ASN1_FillBuffer(ws, &length, 8, ALIGN);
				for(j = length - 1; j >= 0; j--)
				{
					// printf("%02x",enc_value[j]);
					ASN1_FillBuffer(ws, &enc_value[j], 8, ALIGN);
				}
				return 0;
			} 
			else return -1;
		}
		else range = conss->upper - conss->lower + 1;
	}

	if (conss->extflag !=0)
	{

		// printf("extin");
		enc_value[0]=0;
		ASN1_FillBuffer(ws,&enc_value[0],1,UNALIGN);
	}
	value = value - conss->lower;

	if (conss->consType == SEMICONS)
	{
		ASN1_PER_Enc_UnConsINTEGER(ws, &value, enc_value);
		// ASN1_PER_Enc_intUnConsLength( ws, &ws->buffer.byteIndex);
		length = (ws->buffer.byteIndex + 7) / 8;
		ASN1_FillBuffer(ws, &length, 8, ALIGN);
		// printf("%02x",length);
		for(j = length - 1; j >= 0; j--)
		{
			// printf("%02x",enc_value[j]);
			ASN1_FillBuffer(ws, &enc_value[j], 8, ALIGN);
		}
		return 0;
	}

	if (range == 1) return 0;
	else if (range < 256)
	{
		ASN1_PER_Enc_UnConsINTEGER(ws, &value, enc_value);
		tmprange = range - 1;
		i = 1;
		while(tmprange >>= 1) i++;

		// printf("value=%02x,bit=%d",*enc_value,i);
		ws->buffer.byteIndex = i;
		ASN1_FillBuffer(ws, &enc_value[0], i, UNALIGN);
	}
	else if(range <= 0x10000)
	{
		ASN1_PER_Enc_UnConsINTEGER(ws, &value, enc_value);

		for(j = range > 256; j>= 0; j--)
		{
			// printf("%02x",enc_value[j]);
			ASN1_FillBuffer(ws, &enc_value[j], 8, ALIGN);
		}
		return 0;
	}
	else if (range < 0xFFFFFFFFFFFFFFFF )
	{
		ASN1_PER_Enc_UnConsINTEGER(ws, &value, enc_value);
		// ASN1_PER_Enc_intConsLength(ws, &value, conss);
		length = (ws->buffer.byteIndex + 7) / 8;
		j = (range > 0x100000000);
		length = length - 1;
		//printf("%02x",length);
		ASN1_FillBuffer(ws, &length, 2 + j, UNALIGN);
		for(j = length; j >= 0; j--)
		{
			// printf("%02x",enc_value[j]);
			ASN1_FillBuffer(ws, &enc_value[j], 8, ALIGN);
		}
		return 0;
	}
	return 0;
}

ASNINT32 ASN1_PER_UNAlign_Enc_INTEGER(ASN1WorkSpace * ws, INTEGER *tvalue, Asn1ConsInfo *conss)
{
	ASNUINT8 enc_value[8];
	ASNUINT8 i;
	ASNINT8 j;
	ASNUINT8 length;
	ASNINT64 value;
	ASNUINT64 range,tmprange;
	value = *tvalue;
	if (conss->consType == UNCONS)
	{
		if (conss->extflag)
		{
			length = value > conss->upper;			
			ASN1_FillBuffer(ws, &length, 1, UNALIGN);
		}
		else if (value > conss->upper) return -1;
		
		ASN1_PER_Enc_UnConsINTEGER(ws, &value, enc_value);
		// ASN1_PER_Enc_intUnConsLength( ws, &ws->buffer.byteIndex);
		length = (ws->buffer.byteIndex + 7) / 8;
		if ((enc_value[length -1] & 0x80) != 0 && value > 0) length = length + 1;
		// printf("align length%02x\n",length);
		ASN1_FillBuffer(ws, &length, 8, UNALIGN);
		for(j = length - 1; j >= 0; j--)
		{
			// printf("%02x",enc_value[j]);
			ASN1_FillBuffer(ws, &enc_value[j], 8, UNALIGN);
		}
		return 0;
	}
	else if (value < conss->lower)
	{
		if (conss->extflag != 0)
		{
			// printf("extout");
			enc_value[0] = 1;
			ASN1_FillBuffer(ws, &enc_value[0], 1, UNALIGN);
			ASN1_PER_Enc_UnConsINTEGER(ws, &value, enc_value);
			
			//ASN1_PER_Enc_intUnConsLength( ws, &ws->buffer.byteIndex);
			length = (ws->buffer.byteIndex + 7) / 8;
			if ((enc_value[length -1] & 0x80) !=0 && value > 0) length = length + 1;

			// printf("%02x",length);
			ASN1_FillBuffer(ws, &length, 8, UNALIGN);
			for(j = length - 1; j >= 0; j--)
			{
				// printf("%02x",enc_value[j]);
				ASN1_FillBuffer(ws, &enc_value[j], 8, UNALIGN);
			}
			return 0;
		}
		else return -1;
	}
	else if (conss->consType == CONS)
	{
		if (value > conss->upper)
		{
			if (conss->extflag != 0)
			{
				// printf("extout");
				enc_value[0] = 1;
				ASN1_FillBuffer(ws, &enc_value[0], 1, UNALIGN);
				ASN1_PER_Enc_UnConsINTEGER(ws, &value, enc_value);

				//ASN1_PER_Enc_intUnConsLength( ws, &ws->buffer.byteIndex);
				length = (ws->buffer.byteIndex + 7) / 8;
				if ((enc_value[length - 1] & 0x80) !=0 && value>0) length = length + 1;

				// printf("%02x",length);
				ASN1_FillBuffer(ws, &length, 8, UNALIGN);
				for(j = length - 1; j >= 0; j--)
				{
					// printf("%02x",enc_value[j]);
					ASN1_FillBuffer(ws, &enc_value[j], 8, UNALIGN);
				}
				return 0;
			}
			else return -1;
		}
		else range = conss->upper - conss->lower +1;
	}

	if (conss->extflag != 0)
	{
		// printf("extin");
		enc_value[0] = 0;
		ASN1_FillBuffer(ws, &enc_value[0], 1, UNALIGN);
	}
	value = value - conss->lower;

	if (conss->consType == SEMICONS)
	{
		ASN1_PER_Enc_UnConsINTEGER(ws, &value, enc_value);
		// ASN1_PER_Enc_intUnConsLength( ws, &ws->buffer.byteIndex);
		length = (ws->buffer.byteIndex + 7) / 8;
		// if((enc_value[length -1] & 0x80) !=0 && value > 0)
		// {
		// 	length=length+1;
		// } 
		// printf("%02x", length);
		ASN1_FillBuffer(ws, &length, 8, UNALIGN);
		for(j = length - 1; j >= 0; j--)
		{
			// printf("%02x", enc_value[j]);
			ASN1_FillBuffer(ws, &enc_value[j], 8, UNALIGN);
		}
		return 0;
	}

	if (range==1) return 0;

	ASN1_PER_Enc_UnConsINTEGER(ws, &value, enc_value);
	i = 1;
	range = range - 1;
	while(range >>= 1) i++;

	tmprange = (i - ws->buffer.byteIndex) >> 3;
	length = 0;
	for(j = 0; j < tmprange; j++)
	{
		// printf("%02x", 0);
		ASN1_FillBuffer(ws, &length, 8, UNALIGN);
	}
	tmprange = (i - ws->buffer.byteIndex) & 7;

	ASN1_FillBuffer(ws, &length,tmprange, UNALIGN);
	tmprange = ws->buffer.byteIndex & 7;
	ASN1_FillBuffer(ws, &enc_value[ws->buffer.byteIndex / 8], tmprange, UNALIGN);
	tmprange = ws->buffer.byteIndex / 8;
	for(j = tmprange - 1; j >= 0; j--)
	{
		// printf("%02x", enc_value[j]);
		ASN1_FillBuffer(ws, &enc_value[j], 8, UNALIGN);
	}
	return 0;
}

ASNINT32 ASN1_PER_Align_Dec_INTEGER(ASN1WorkSpace * ws, INTEGER *value, Asn1ConsInfo *conss)
{
	ASNUINT8 enc_value[8];
	ASNUINT8 i,length,extendflag=0;
	ASNUINT64 range,tmprange;

	if (conss->consType == UNCONS)
	{
		if (conss->extflag)
		{
			if (0 > ASN1_ReadBuffer(ws, &enc_value[0], 1, UNALIGN))
				return ASN1_PER_CHECK_LENGTH_ERROR;
		}
		
		if (0 > ASN1_ReadBuffer(ws, &enc_value[0], 8, ALIGN))
			return ASN1_PER_CHECK_LENGTH_ERROR;

		length = enc_value[0];
		for (i = 0; i < length; i++)
		{
			 if (0 > ASN1_ReadBuffer(ws, &enc_value[i], 8, ALIGN))
				 return ASN1_PER_CHECK_LENGTH_ERROR;
		}
		ASN1_PER_Dec_INTEGER_Value(enc_value, value, length, 1);
	}
	else if (conss->consType == SEMICONS)
	{
		if(conss->extflag != 0)
		{
			if (0 > ASN1_ReadBuffer(ws, &enc_value[0], 1, UNALIGN))
				return ASN1_PER_CHECK_LENGTH_ERROR;
			extendflag = enc_value[0];
		}

		if (0 > ASN1_ReadBuffer(ws, &enc_value[0], 8, ALIGN))
			return ASN1_PER_CHECK_LENGTH_ERROR;
		
		length = enc_value[0];
		for (i = 0; i < length; i++)
		{
			if (0 > ASN1_ReadBuffer(ws, &enc_value[i], 8, ALIGN))
				return ASN1_PER_CHECK_LENGTH_ERROR;
		}
		
		if (conss->extflag == 0 || extendflag == 0)
		{
			ASN1_PER_Dec_INTEGER_Value(enc_value, value, length, 0);
			*value = *value + conss->lower; 
		}
		else
		{
			ASN1_PER_Dec_INTEGER_Value(enc_value, value, length, 1);
		}
	}
	else if (conss->consType == CONS)
	{
		if (conss->extflag != 0)
		{
			if (0 > ASN1_ReadBuffer(ws, &enc_value[0], 1, UNALIGN))
				return ASN1_PER_CHECK_LENGTH_ERROR;
			extendflag = enc_value[0];
		}

		if (extendflag != 0)
		{
			if (0 > ASN1_ReadBuffer(ws, &enc_value[0], 8, ALIGN))
				return ASN1_PER_CHECK_LENGTH_ERROR;

			length = enc_value[0];
			
			for(i = 0; i < length; i++)
			{
				if (0 > ASN1_ReadBuffer(ws, &enc_value[i], 8, ALIGN))
					return ASN1_PER_CHECK_LENGTH_ERROR;
			}
			ASN1_PER_Dec_INTEGER_Value(enc_value, value, length, 1);
		} 
		else
		{
			range = conss->upper - conss->lower + 1;
			if (range == 1) *value = 0; 
			else if(range < 256)
			{
				tmprange = range - 1;
				i = 1;
				while(tmprange >>= 1) i++;

				tmprange = i;
				if (0 > ASN1_ReadBuffer(ws, &enc_value[0], tmprange, UNALIGN))
					return ASN1_PER_CHECK_LENGTH_ERROR;

				ASN1_PER_Dec_INTEGER_Value(enc_value, value, 1, 0);
			} 
			else if(range == 256)
			{
				if (0 > ASN1_ReadBuffer(ws, &enc_value[0], 8, ALIGN))
					return ASN1_PER_CHECK_LENGTH_ERROR;
				ASN1_PER_Dec_INTEGER_Value(enc_value, value, 1, 0);
			}
			else if (range <= 0x10000)
			{
				for (i = 0; i < 2; i++)
				{
					if (0 > ASN1_ReadBuffer(ws, &enc_value[i], 8, ALIGN))
						return ASN1_PER_CHECK_LENGTH_ERROR;
				}
				ASN1_PER_Dec_INTEGER_Value(enc_value, value, 2, 0);
			}
			else if(range <= 0x100000000)
			{
				if (0 > ASN1_ReadBuffer(ws, &enc_value[0], 2, UNALIGN))
					return ASN1_PER_CHECK_LENGTH_ERROR;

				length = enc_value[0];
				for(i = 0; i <= length; i++)
				{
					if (0 > ASN1_ReadBuffer(ws, &enc_value[i], 8, ALIGN))
						return ASN1_PER_CHECK_LENGTH_ERROR;
				}
				ASN1_PER_Dec_INTEGER_Value(enc_value, value, length + 1, 0);
			}
			else if(range <= 0xFFFFFFFFFFFFFFFF)
			{
				if (0 > ASN1_ReadBuffer(ws, &enc_value[0], 3, UNALIGN))
					return ASN1_PER_CHECK_LENGTH_ERROR;

				length = enc_value[0];
				for(i = 0; i <= length; i++)
				{
					if (0 > ASN1_ReadBuffer(ws, &enc_value[i], 8, ALIGN))
						return ASN1_PER_CHECK_LENGTH_ERROR;
				}
				ASN1_PER_Dec_INTEGER_Value(enc_value, value, length + 1, 0);				
			}
			*value = *value + conss->lower;
		}
	}
	return 0;
}

ASNINT32 ASN1_PER_UNAlign_Dec_INTEGER(ASN1WorkSpace *ws, INTEGER *value, Asn1ConsInfo *conss)
{
	ASNUINT8 enc_value[8];
	ASNUINT8 i, length, extendflag = 0;
	ASNUINT64 range, tmprange;

	if (conss->consType == UNCONS)
	{
		if (conss->extflag)
		{
			if (0 > ASN1_ReadBuffer(ws, &enc_value[0], 1, UNALIGN))
				return ASN1_PER_CHECK_LENGTH_ERROR;
		}		

		if (0 > ASN1_ReadBuffer(ws,&enc_value[0], 8, UNALIGN))
			return ASN1_PER_CHECK_LENGTH_ERROR;

		length = enc_value[0];
		for(i = 0; i < length; i++)
		{
			if (0 > ASN1_ReadBuffer(ws, &enc_value[i], 8, UNALIGN))
				return ASN1_PER_CHECK_LENGTH_ERROR;
		}
		ASN1_PER_Dec_INTEGER_Value(enc_value, value, length, 1);
	}
	else if (conss->consType == SEMICONS)
	{
		if (conss->extflag != 0)
		{
			if (0 > ASN1_ReadBuffer(ws, &enc_value[0], 1, UNALIGN))
				return ASN1_PER_CHECK_LENGTH_ERROR;
			extendflag = enc_value[0];
		}

		if (0 > ASN1_ReadBuffer(ws, &enc_value[0], 8, UNALIGN))
			return ASN1_PER_CHECK_LENGTH_ERROR;
		length = enc_value[0];
		for(i = 0; i < length; i++)
		{
			if (0 > ASN1_ReadBuffer(ws, &enc_value[i], 8, UNALIGN))
				return ASN1_PER_CHECK_LENGTH_ERROR;
		}
		
		if (conss->extflag == 0 || extendflag == 0)
		{
			*value = enc_value[0];
			for(i = 2; i <= length; i++)
			{
				*value = *value * 256 + enc_value[i - 1]; 
			}

			// ASN1_PER_Dec_INTEGER_Value(enc_value,value,length, 0);
			*value = *value + conss->lower; 
		}
		else
		{
			ASN1_PER_Dec_INTEGER_Value(enc_value, value, length, 1);
		}
	}
	else if (conss->consType == CONS)
	{
		if (conss->extflag != 0)
		{
			if (0 > ASN1_ReadBuffer(ws, &enc_value[0], 1, UNALIGN))
				return ASN1_PER_CHECK_LENGTH_ERROR;
			extendflag = enc_value[0];
		}

		if (extendflag != 0)
		{
			if (0 > ASN1_ReadBuffer(ws, &enc_value[0], 8, UNALIGN))
				return ASN1_PER_CHECK_LENGTH_ERROR;
			length = enc_value[0];
			
			for(i = 0; i < length; i++)
			{
				if (0 > ASN1_ReadBuffer(ws, &enc_value[i], 8, UNALIGN))
					return ASN1_PER_CHECK_LENGTH_ERROR;
			}
			ASN1_PER_Dec_INTEGER_Value(enc_value, value, length, 1);
		} 
		else
		{
			range = conss->upper - conss->lower + 1;
			if(range == 1)
			{
				 *value = 0; 
			} 
			else 
			{
				tmprange = range - 1;
				i = 1;
				while(tmprange >>= 1)
				{
					i++;
				}
				tmprange = i;
				
				if (tmprange % 8 != 0)
				{
					if (0 > ASN1_ReadBuffer(ws, &enc_value[0], tmprange % 8, UNALIGN))
						return ASN1_PER_CHECK_LENGTH_ERROR;
					i = 1;
					
				}
				else
				{
					i = 0;
					tmprange -= 1;
				}
				
				for (;i <= tmprange / 8; i++)
				{
					if (0 > ASN1_ReadBuffer(ws, &enc_value[i], 8, UNALIGN))
						return ASN1_PER_CHECK_LENGTH_ERROR;
				}
				ASN1_PER_Dec_INTEGER_Value(enc_value, value, i, 0);
			} 
			*value = *value + conss->lower;
		}
	}
	return 0;
}










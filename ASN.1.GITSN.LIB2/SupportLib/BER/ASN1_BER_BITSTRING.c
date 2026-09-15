#include "ASN1_BER_BITSTRING.h"


#define BitStringDefaultLength 4096

static void AddBitString(BITSTRING *tempvalue, ASNUINT32L length, BITSTRING *value, ASNUINT32 *count)
{
	ASNUINT32 i = 0;
	length -= 1;
	for(i = 0; i < length; i++)
	{
		*value->data = tempvalue->data[i];
		value->data += 1;
	}
	*count += length;
}

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_BITSTRING(ASN1WorkSpace *ws, BITSTRING *value, ASN1TagType flag)
{
	ASN1_Tag_Move_Pointer(ws,ITS_ASN_UNIV|ITS_ASN_PRIM|ASN1_TYPE_BITSTRING,flag);
	ASN1_BER_Enc_BITSTRING_Value(ws,value);	
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_BITSTRING_Value(ASN1WorkSpace *ws, BITSTRING *value)
{
	ASNUINT32 j = 0;
	ASNUINT8 temp_value = 0;
//	ASNUINT32L count = 0;			//Data Length	

// 	ASNUINT8 F_uc_full0 = (ASNUINT8)(8 - value->numbits % 8);
	ASNUINT8 F_Uc_rem = (ASNUINT8)(value->numbits % 8);						// remainder
	ASNUINT8 F_uc_full0 = (ASNUINT8)(8 - F_Uc_rem);							// remainder in single octet

	ASNUINT32L F_Ul_Quot = 1 + (value->numbits / 8);						// initial octet + octal size of bits
	ASNUINT32 length	 = F_Ul_Quot + (F_Uc_rem ? 1 : 0);					// total octet size = initial octet + octal size of bits + remainder octet

//	if(value->numbits % 8) length++;	

	ASN1_BER_Enc_Length(ws,length);											// encode length

	if (value->numbits == 0)
	{	// no positive bits -> just single octet for initial octet
		ASN1_BER_FillBuffer(ws, &temp_value, 1, 0);
		ws->buffer.current++;
		return 0;
	} 
	else
	{
		//count = strlen(value->data);
	}

	temp_value = F_uc_full0 % 8;
	ASN1_BER_FillBuffer(ws, &temp_value, 1, j);								// encode "unused bits" value

/*	ws->buffer.current[j] = F_uc_full0 % 8;*/
	
	while (F_Ul_Quot--)														// process value to buffer data
	{
		ASN1_BER_FillBuffer(ws, &value->data[j], 1, j + 1);
// 		ws->buffer.current[j+1] = value->data[j];
		j++;
	}
	ws->buffer.current[j] &= 0xFF <<  F_uc_full0;							// process remainder
	
	if (F_Uc_rem > 0) j++;

	ws->dataSize = j;	//value length	
	ws->buffer.current += ws->dataSize;

	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_BITSTRING_Value(ASN1WorkSpace *ws, BITSTRING *value,ASNUINT32L length)
{
	ASNUINT32 i,j=0;
	ASNUINT32L F_Ul_length = length;
	value->data = (ASNUINT8*)mpool_malloc(ws->Pmemory,F_Ul_length);
	value->numbits = *ws->buffer.current;
	for (i=1;i<F_Ul_length;i++)						//process buffer data to value
	{
		value->data[j++] = ws->buffer.current[i];
	}
	ws->buffer.current +=i; 
	return 0;
}



ASNINT32 ASN1_BER_Dec_BITSTRING(ASN1WorkSpace *ws, BITSTRING *value, ASNINT32 length, ASN1TagType flag)
{	
	BITSTRING* tempValue;
	ASNUINT32 count = 0;
	int F_UL_length = 0;
	ASNUINT8* F_UC_temp;
	ASNUINT32 F_UI_full;
//	ASNINT32 iscons = ws->iscons;

	tempValue =(BITSTRING*)mpool_malloc(ws->Pmemory,sizeof(BITSTRING));
	
	
	value->data = (ASNUINT8*)mpool_calloc(ws->Pmemory, BitStringDefaultLength, 1);		//default malloc 4096 byte

	if (flag == ASN1EXPL)
	{	// EXPLICIT
		if (length == -1)
		{	// user say indefinite form
			if ((*ws->buffer.current & 0x20) == 0x20)
			{	// data say constructed form
				ASN1_BER_Dec_Tag(ws,ITS_ASN_UNIV | ITS_ASN_CONS | ASN1_TYPE_BITSTRING);		// should construct
				ASN1_BER_Dec_Length(ws);													// decode length
				if (ws->dataSize == -1)
				{	// data say indefinite form
					while (!(*ws->buffer.current == 0x00 && *(ws->buffer.current + 1) == 0x00))
					{	// it's not EOC
						ASN1_BER_Dec_Tag(ws,ITS_ASN_UNIV | ITS_ASN_PRIM | ASN1_TYPE_BITSTRING);	// segment should primitive
						ASN1_BER_Dec_Length(ws);												// segment should actual length
						if (ASN1_BER_Dec_BITSTRING_Value(ws, tempValue, ws->dataSize))			// decode segment contents
							return 1;

						AddBitString(tempValue, ws->dataSize, value, &count);
					}
					F_UI_full = tempValue->numbits;
					ASN1_BER_Dec_StrmEOC(ws);													// decode EOC
				}
				else
				{	// definite form
					F_UL_length = length;
					F_UC_temp = ws->buffer.current;

					while (ws->buffer.current < F_UC_temp + F_UL_length)						// decode TLV
					{
						ASN1_BER_Dec_Tag(ws,ITS_ASN_UNIV | ITS_ASN_PRIM | ASN1_TYPE_BITSTRING);	// segment should primitive
						ASN1_BER_Dec_Length(ws);												// segment should actual length
						if(ASN1_BER_Dec_BITSTRING_Value(ws,tempValue,ws->dataSize))				// decode segment contents
							return 1;

						F_UI_full = tempValue->numbits;
						AddBitString(tempValue,ws->dataSize,value,&count);						
					}
				}
			}
			else
			{	// data say primitive form
				while (!(*ws->buffer.current == 0x00 && *(ws->buffer.current+1) == 0x00))						
				{	// It's not EOC
					ASN1_BER_Dec_Tag(ws, ITS_ASN_UNIV | ITS_ASN_PRIM | ASN1_TYPE_BITSTRING);	// should primitive
					ASN1_BER_Dec_Length(ws);													// should actual length
					if(ASN1_BER_Dec_BITSTRING_Value(ws,tempValue,ws->dataSize))					// decode contents
						return 1;

					F_UI_full = tempValue->numbits;
					AddBitString(tempValue,ws->dataSize,value,&count);
				}				
			}
		}
		else
		{	// user say definite form
			if ((*ws->buffer.current & 0x20) == 0x20)
			{	// data say constructed from
				ASN1_BER_Dec_Tag(ws, ITS_ASN_UNIV | ITS_ASN_CONS | ASN1_TYPE_BITSTRING);		// should construct
				ASN1_BER_Dec_Length(ws);														// decode length
				if (ws->dataSize == -1)				
				{	// data say indefinite form
					while (!(*ws->buffer.current == 0x00 && *(ws->buffer.current+1) == 0x00))				
					{	// it's not EOC
						ASN1_BER_Dec_Tag(ws, ITS_ASN_UNIV | ITS_ASN_PRIM | ASN1_TYPE_BITSTRING);	// segment should primitive
						ASN1_BER_Dec_Length(ws);													// segment should actual length
						if(ASN1_BER_Dec_BITSTRING_Value(ws, tempValue, ws->dataSize))				// decode segment contents
							return 1;

						F_UI_full = tempValue->numbits;
						AddBitString(tempValue, ws->dataSize, value,&count);
					}
					ASN1_BER_Dec_StrmEOC(ws);													// decode EOC
				}
				else
				{	// data say definite form
					F_UL_length = ws->dataSize;
					F_UC_temp = ws->buffer.current;

					while (ws->buffer.current < F_UC_temp + F_UL_length)							// under size
					{
						ASN1_BER_Dec_Tag(ws, ITS_ASN_UNIV | ITS_ASN_PRIM | ASN1_TYPE_BITSTRING);	// should primitive
						ASN1_BER_Dec_Length(ws);													// should actual length
						if(ASN1_BER_Dec_BITSTRING_Value(ws, tempValue, ws->dataSize))				// decode contents
							return 1;

						F_UI_full = tempValue->numbits;
						AddBitString(tempValue, ws->dataSize, value, &count);
					}
				}
			} 
			else
			{	// data say primitive form
// 				F_UL_length = length;
// 				F_UC_temp = ws->buffer.current;
// 				while (ws->buffer.current<F_UC_temp+F_UL_length)						
// 				{
					ASN1_BER_Dec_Tag(ws, ITS_ASN_UNIV | ITS_ASN_PRIM | ASN1_TYPE_BITSTRING);		// should primitive
					ASN1_BER_Dec_Length(ws);														// should actual length
					if(ASN1_BER_Dec_BITSTRING_Value(ws,tempValue,ws->dataSize))						// decode contents
						return 1;

					F_UI_full = tempValue->numbits;
					AddBitString(tempValue,ws->dataSize,value,&count);
//				}				
			}
		}		
	} 
	else if (flag == ASN1IMPL)
	{	// IMPLICIT
		ASNINT32 iscons = ws->iscons;
		if (iscons == -2)
		{	// TLV
			/*ASN1_BER_Dec_Length(ws);	*/
			if (ASN1_BER_Dec_BITSTRING_Value(ws, tempValue, length)) return 1;

			F_UI_full = tempValue->numbits;
			AddBitString(tempValue,length,value,&count);
		} 
		else if (iscons == -3)
		{	// IMPLICIT
			/*ASN1_BER_Dec_Length(ws);	*/
			if (length == -1)
			{	// indefinite form
				while (!(*ws->buffer.current == 0x00 && *(ws->buffer.current + 1) == 0x00))						
				{	// it's not EOC
					ASN1_BER_Dec_Tag(ws, ITS_ASN_UNIV | ITS_ASN_PRIM | ASN1_TYPE_BITSTRING);	// segment should primitive
					ASN1_BER_Dec_Length(ws);													// segment should actual length
					if(ASN1_BER_Dec_BITSTRING_Value(ws,tempValue,ws->dataSize))					// decode segment contents
						return 1;

					F_UI_full = tempValue->numbits;
					AddBitString(tempValue,ws->dataSize,value,&count);
				}
			} 
			else
			{	// definite form
				F_UL_length = length;
				F_UC_temp = ws->buffer.current;
				while (ws->buffer.current < F_UC_temp+F_UL_length)
				{
					ASN1_BER_Dec_Tag(ws, ITS_ASN_UNIV | ITS_ASN_PRIM | ASN1_TYPE_BITSTRING);	// segment should primitive
					ASN1_BER_Dec_Length(ws);													// segment should actual length
					if(ASN1_BER_Dec_BITSTRING_Value(ws,tempValue,ws->dataSize))					// decode segment contents
						return 1;

					F_UI_full = tempValue->numbits;
					AddBitString(tempValue,ws->dataSize,value,&count);
				}			
			}
		}
	}
	else
	{	// flag undefined
		ASN1_BER_Dec_Tag(ws, ITS_ASN_UNIV | ITS_ASN_PRIM | ASN1_TYPE_BITSTRING);			// should primitive
		ASN1_BER_Dec_Length(ws);															// should actual length
		if(ASN1_BER_Dec_BITSTRING_Value(ws,tempValue,ws->dataSize))							// decode contents
			return 1;

		F_UI_full = tempValue->numbits;
		AddBitString(tempValue,ws->dataSize,value,&count);
	}
	
	value->data -= count;
	value->numbits = count * 8 - F_UI_full;	
//	value->data = mpool_realloc(p,value->data,count);
	return 0;
}





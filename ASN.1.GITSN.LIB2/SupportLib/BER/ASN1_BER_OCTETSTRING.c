#include "ASN1_BER_OCTETSTRING.h"

#define OctStringDefaultLength 1024

static void AddOctString(ASN1WorkSpace *ws, OCTETSTRING *tempvalue, ASNUINT32L ws_data_size, OCTETSTRING *value, ASNUINT32 *count)
{
	if (value->data == NULL)
		value->data = (ASNUINT8 *)mpool_calloc(ws->Pmemory, ws_data_size + 1, 1);
	else
	{
		ASNUINT8 *src_ptr = value->data - *count;
		value->data = (ASNUINT8 *)mpool_realloc(ws->Pmemory, src_ptr, *count + ws_data_size + 1);
		value->data += *count;
	}

	memmove(value->data, tempvalue->data, ws_data_size);
	value->data += ws_data_size;
	*count += ws_data_size;
}

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_OCTETSTRING_Value(ASN1WorkSpace *ws, OCTETSTRING *value)
{
	ASNUINT32 i;
	for (i=0;i<value->numbits;i++)
	{
//		ws->buffer.current[i] = value->data[i];	
		ASN1_BER_FillBuffer(ws, &value->data[i], 1, i);
	}
	ws->buffer.current += i;	
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_OCTETSTRING(ASN1WorkSpace*ws, OCTETSTRING * value, ASN1TagType flag)
{
	ASN1_Tag_Move_Pointer(ws, ASN1_TYPE_OCTETSTRING, flag);		// encode Tag
	ASN1_BER_Enc_Length(ws, value->numbits);					// encode Length
	ASN1_BER_Enc_OCTETSTRING_Value(ws, value);					// encode oct string value
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_OCTETSTRING_Value(ASN1WorkSpace *ws, OCTETSTRING *value,ASNUINT32L length)
{
//	ASNUINT32 i;
	value->data = (ASNUINT8*)mpool_malloc(ws->Pmemory,length);
/*
		for (i=0;i<length;i++)
		{
			value->data[i] = ws->buffer.current[i];
		}*/
	memmove(value->data,ws->buffer.current,length);
	value->numbits = length;
//	ws->buffer.current += i;	
	ws->buffer.current += length;
	return 0;
}

ASNINT32 ASN1_BER_Dec_OCTETSTRING(ASN1WorkSpace *ws, OCTETSTRING *value, ASNINT32 length, ASN1TagType flag)
{	
	OCTETSTRING* tempValue;
	ASNUINT32 count = 0;
	int F_UL_length = 0;
	ASNUINT8* F_UC_temp;
	ASNINT32 iscons = ws->iscons;


//	value->data = (ASNUINT8 *)ASN1_MALLOC(OctStringDefaultLength);						//default malloc 2048 byte
//	value->data = (ASNUINT8 *)mpool_malloc(ws->Pmemory, OctStringDefaultLength);		//default malloc 2048 byte
//	memset(value->data, 0, OctStringDefaultLength);
	memset(value, 0, sizeof(OCTETSTRING));
	tempValue = (OCTETSTRING *)mpool_calloc(ws->Pmemory, sizeof(OCTETSTRING), 1);

	if (flag == ASN1EXPL)				//EXPLICIT
	{
		if (length == -1)			//Indefinite Form   80
		{
			if ((*ws->buffer.current & 0x20) == 0x20)			//constructed Tag
			{
				ASN1_BER_Dec_Tag(ws, ITS_ASN_UNIV | ITS_ASN_CONS | ASN1_TYPE_OCTETSTRING);		// compare Tag	T=24
				ASN1_BER_Dec_Length(ws);														// decode length
				if (ws->dataSize == -1)															// Indefinite Form   80
				{
					while (!(*ws->buffer.current == 0x00 && *(ws->buffer.current+1) == 0x00))						
					{
						ASN1_BER_Dec_Tag(ws,ITS_ASN_UNIV|ITS_ASN_PRIM|ASN1_TYPE_OCTETSTRING);		//compare Tag T=3
						ASN1_BER_Dec_Length(ws);	
						//tempValue->data = (ASNUINT8*)ASN1_MALLOC(ws->dataSize);			
						if(ASN1_BER_Dec_OCTETSTRING_Value(ws, tempValue, ws->dataSize))				//decode V
							return 1;

						AddOctString(ws, tempValue, ws->dataSize, value, &count);
					}					
					ASN1_BER_Dec_StrmEOC(ws);													//00 00 
				}
				else
				{
					F_UL_length = ws->dataSize;
					F_UC_temp = ws->buffer.current;
					while (ws->buffer.current<F_UC_temp+F_UL_length)							// decode TLV
					{
						ASN1_BER_Dec_Tag(ws, ITS_ASN_UNIV | ITS_ASN_PRIM | ASN1_TYPE_OCTETSTRING);	//T
						ASN1_BER_Dec_Length(ws);													//L
						if(ASN1_BER_Dec_OCTETSTRING_Value(ws,tempValue,ws->dataSize))				//V
							return 1;

						AddOctString(ws,tempValue,ws->dataSize,value,&count);						
					}
				}
			}
			else
			{
				ASN1_BER_Dec_Tag(ws, ITS_ASN_UNIV | ITS_ASN_PRIM | ASN1_TYPE_OCTETSTRING);		//T
				ASN1_BER_Dec_Length(ws);														//L
				if(ASN1_BER_Dec_OCTETSTRING_Value(ws,tempValue,ws->dataSize))					//V
					return 1;

				AddOctString(ws,tempValue,ws->dataSize,value,&count);				
			}
		}
		else																				//Definite Form
		{
			if ((*ws->buffer.current & 0x20) == 0x20)											//constructed Tag
			{
				ASN1_BER_Dec_Tag(ws, ITS_ASN_UNIV | ITS_ASN_CONS | ASN1_TYPE_OCTETSTRING);			//	T=23
				ASN1_BER_Dec_Length(ws);										
				if (ws->dataSize == -1)				
				{
					while (!(*ws->buffer.current == 0x00 && *(ws->buffer.current+1) == 0x00))				
					{
						ASN1_BER_Dec_Tag(ws, ITS_ASN_UNIV | ITS_ASN_PRIM | ASN1_TYPE_OCTETSTRING);		//T
						ASN1_BER_Dec_Length(ws);														//L
						if(ASN1_BER_Dec_OCTETSTRING_Value(ws,tempValue,ws->dataSize))					//V
							return 1;

						AddOctString(ws,tempValue,ws->dataSize,value,&count);
					}
					ASN1_BER_Dec_StrmEOC(ws);														//00 00 
				}
				else
				{
					F_UL_length = ws->dataSize;
					F_UC_temp = ws->buffer.current;
					while (ws->buffer.current<F_UC_temp+F_UL_length)									
					{
						ASN1_BER_Dec_Tag(ws, ITS_ASN_UNIV | ITS_ASN_PRIM | ASN1_TYPE_OCTETSTRING);		//T
						ASN1_BER_Dec_Length(ws);														//L
						if(ASN1_BER_Dec_OCTETSTRING_Value(ws, tempValue, ws->dataSize))					//V
							return 1;

						AddOctString(ws, tempValue, ws->dataSize, value,&count);
					}
				}
			} 
			else
			{
				F_UL_length = length;
				F_UC_temp = ws->buffer.current;
				ASN1_BER_Dec_Tag(ws,ITS_ASN_UNIV | ITS_ASN_PRIM | ASN1_TYPE_OCTETSTRING);			//T
				ASN1_BER_Dec_Length(ws);															//L
				if (ASN1_BER_Dec_OCTETSTRING_Value(ws, tempValue, ws->dataSize))					//V
					return 1;

				AddOctString(ws, tempValue, ws->dataSize, value, &count);	
			}
		}		
	} 
	else if(flag == ASN1IMPL)												//IMPLICIT
	{
		if (iscons == -2)												//TLV
		{
			/*ASN1_BER_Dec_Length(ws);	*/
			if (ASN1_BER_Dec_OCTETSTRING_Value(ws, tempValue, length))		
				return 1;
			
			AddOctString(ws, tempValue, length, value, &count);
		} 
		else if(iscons == -3)						//IMPLICIT
		{
			/*ASN1_BER_Dec_Length(ws);	*/
			if (length == -1)
			{
				while (!(*ws->buffer.current == 0x00 && *(ws->buffer.current+1) == 0x00))						
				{
					ASN1_BER_Dec_Tag(ws, ITS_ASN_UNIV | ITS_ASN_PRIM | ASN1_TYPE_OCTETSTRING);			//T
					ASN1_BER_Dec_Length(ws);															//L
					if (ASN1_BER_Dec_OCTETSTRING_Value(ws, tempValue, ws->dataSize))					//V
						return 1;

					AddOctString(ws, tempValue, ws->dataSize, value, &count);
				}
			} 
			else
			{
				F_UL_length = length;
				F_UC_temp = ws->buffer.current;
				while (ws->buffer.current < F_UC_temp + F_UL_length)						
				{
					ASN1_BER_Dec_Tag(ws, ITS_ASN_UNIV | ITS_ASN_PRIM | ASN1_TYPE_OCTETSTRING);			//T
					ASN1_BER_Dec_Length(ws);															//L
					if (ASN1_BER_Dec_OCTETSTRING_Value(ws, tempValue, ws->dataSize))					//V
						return 1;

					AddOctString(ws, tempValue, ws->dataSize, value, &count);
				}			
			}
		}
	}	
	value->data -= count;
	value->numbits = count;
//	value->data = (ASNUINT8 *)mpool_realloc(ws->Pmemory, value->data, count);
	return 0;
}




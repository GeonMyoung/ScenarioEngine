#include "ASN1_BER_CHARACTERSTRING.h"

#define OctStringDefaultLength 2048


ASNINT32 ASN1_BER_Enc_CHARACTERSTRING_Value(ASN1WorkSpace *ws, CHARACTERSTRING *value)
{
	/*
	ASNUINT32 i;
	for (i=0;i<value->numbits;i++)
	{
		ws->buffer.current[i] = value->data[i];
	}
	ws->buffer.current += i;
	*/
	return 0;
}

ASNINT32 ASN1_BER_Enc_CHARACTERSTRING(ASN1WorkSpace *ws, CHARACTERSTRING *value, ASN1TagType flag)
{
	/*
	ASN1_Tag_Move_Pointer(ws,ITS_ASN_UNIV|ITS_ASN_PRIM|ASN1_TYPE_CHARACTER_STRING,flag);					//encode Tag
	ASN1_BER_Enc_Length(ws,value->numbits);				//encode Length
	ASN1_BER_Enc_CHARACTERSTRING_Value(ws,value);			//encode oct string value
	*/
	ASNINT32 ret;
	ret = ASN1_BER_Enc_ASN1CHARACTERSTRING(ws, value, flag);
	return ret;
}

ASNINT32 ASN1_BER_Dec_CHARACTERSTRING_Value(ASN1WorkSpace *ws, CHARACTERSTRING *value, ASNUINT32L length)
{
	/*
	ASNUINT32 i;
	value->data = (ASNUINT8*)ASN1_MALLOC(length);	
	for (i=0;i<length;i++)
	{
		value->data[i] = ws->buffer.current[i];
	}
	value->numbits = length;
	ws->buffer.current += i;
	*/
	return 0;
}

// ASNINT32 ASN1_BER_Dec_CHARACTERSTRING(ASN1WorkSpace*ws, CHARACTERSTRING *value, ASN1TagType flag)
// {
// 	if ((*ws->buffer.current & 0x20) != 0x20)
// 	{
// 		ASN1_BER_Dec_Tag(ws,univ|prim|ASN1_TYPE_CHARACTER_STRING);
// 		if(ASN1_BER_Dec_Length(ws))
// 		{
// 			return 1;
// 		}
// 		if(ASN1_BER_Dec_CHARACTERSTRING_Value(ws,value,ws->dataSize))
// 		{
// 			return 1;
// 		}
// 	}
// 	return 0;
// }



ASNINT32 ASN1_BER_Dec_CHARACTERSTRING(ASN1WorkSpace *ws, CHARACTERSTRING *value, ASNINT32 length, ASN1TagType flag)
{
	ASNINT32 ret;
	ret = ASN1_BER_Dec_ASN1CHARACTERSTRING(ws,value,length,flag);
	return ret;
	/*
	CHARACTERSTRING* tempValue;
	ASNUINT32 count = 0;
	int F_UL_length = 0;
	ASNUINT8* F_UC_temp;
	ASNINT32 iscons = ws->iscons;

	value->data = mpool_malloc(ws->Pmemory,OctStringDefaultLength);
	memset(value->data,0,OctStringDefaultLength);
	tempValue =(CHARACTERSTRING*)mpool_malloc(ws->Pmemory,sizeof(CHARACTERSTRING));
	
	
//	value->data = (ASNUINT8*)ASN1_MALLOC(OctStringDefaultLength);		//default malloc 2048 byte
	if (flag == ASN1EXPL)				//EXPLICIT
	{
		if (length == -1)			//Indefinite Form   80
		{
			if ((*ws->buffer.current & 0x20) == 0x20)			//constructed Tag
			{
				ASN1_BER_Dec_Tag(ws,ITS_ASN_UNIV|ITS_ASN_CONS|ASN1_TYPE_CHARACTER_STRING);		//compare Tag	T=24
				ASN1_BER_Dec_Length(ws);										//decode length
				if (ws->dataSize == -1)				//Indefinite Form   80
				{
					while (!(*ws->buffer.current == 0x00 && *(ws->buffer.current+1) == 0x00))						
					{
						ASN1_BER_Dec_Tag(ws,ITS_ASN_UNIV|ITS_ASN_PRIM|ASN1_TYPE_CHARACTER_STRING);				//compare Tag T=3
						ASN1_BER_Dec_Length(ws);	
						//tempValue->data = (ASNUINT8*)ASN1_MALLOC(ws->dataSize);			
						if(ASN1_BER_Dec_CHARACTERSTRING_Value(ws,tempValue,ws->dataSize))			//decode V
						{
							return 1;
						}
						AddCHARACTERSTRING(tempValue,ws->dataSize,value,&count);
					}					
					ASN1_BER_Dec_StrmEOC(ws);						//00 00 
				}
				else
				{
					F_UL_length = ws->dataSize;
					F_UC_temp = ws->buffer.current;
					while (ws->buffer.current<F_UC_temp+F_UL_length)								//decode TLV
					{
						ASN1_BER_Dec_Tag(ws,ITS_ASN_UNIV|ITS_ASN_PRIM|ASN1_TYPE_CHARACTER_STRING);				//T
						ASN1_BER_Dec_Length(ws);											//L
						if(ASN1_BER_Dec_CHARACTERSTRING_Value(ws,tempValue,ws->dataSize))		//V
						{
							return 1;
						}						
						AddCHARACTERSTRING(tempValue,ws->dataSize,value,&count);						
					}
				}
			}
			else
			{
				ASN1_BER_Dec_Tag(ws,ITS_ASN_UNIV|ITS_ASN_PRIM|ASN1_TYPE_CHARACTER_STRING);				//T
				ASN1_BER_Dec_Length(ws);											//L
				if(ASN1_BER_Dec_CHARACTERSTRING_Value(ws,tempValue,ws->dataSize))		//V
				{
					return 1;
				}		
				AddCHARACTERSTRING(tempValue,ws->dataSize,value,&count);				
			}
		}
		else		//Definite Form
		{
			if ((*ws->buffer.current & 0x20) == 0x20)			//constructed Tag
			{
				ASN1_BER_Dec_Tag(ws,ITS_ASN_UNIV|ITS_ASN_CONS|ASN1_TYPE_CHARACTER_STRING);		//	T=23
				ASN1_BER_Dec_Length(ws);										
				if (ws->dataSize == -1)				
				{
					while (!(*ws->buffer.current == 0x00 && *(ws->buffer.current+1) == 0x00))				
					{
						ASN1_BER_Dec_Tag(ws,ITS_ASN_UNIV|ITS_ASN_PRIM|ASN1_TYPE_CHARACTER_STRING);				//T
						ASN1_BER_Dec_Length(ws);											//L
						if(ASN1_BER_Dec_CHARACTERSTRING_Value(ws,tempValue,ws->dataSize))		//V
						{
							return 1;
						}						
						AddCHARACTERSTRING(tempValue,ws->dataSize,value,&count);
					}
					ASN1_BER_Dec_StrmEOC(ws);						
				}
				else
				{
					F_UL_length = ws->dataSize;
					F_UC_temp = ws->buffer.current;
					while (ws->buffer.current<F_UC_temp+F_UL_length)									
					{
						ASN1_BER_Dec_Tag(ws,ITS_ASN_UNIV|ITS_ASN_PRIM|ASN1_TYPE_CHARACTER_STRING);				//T
						ASN1_BER_Dec_Length(ws);											//L
						if(ASN1_BER_Dec_CHARACTERSTRING_Value(ws,tempValue,ws->dataSize))		//V
						{
							return 1;
						}						
						AddCHARACTERSTRING(tempValue,ws->dataSize,value,&count);
					}
				}
			} 
			else
			{
				F_UL_length = length;
				F_UC_temp = ws->buffer.current;
				ASN1_BER_Dec_Tag(ws,ITS_ASN_UNIV|ITS_ASN_PRIM|ASN1_TYPE_CHARACTER_STRING);				//T
				ASN1_BER_Dec_Length(ws);											//L
				if(ASN1_BER_Dec_CHARACTERSTRING_Value(ws,tempValue,ws->dataSize))		//V
				{
					return 1;
				}		
				AddCHARACTERSTRING(tempValue,ws->dataSize,value,&count);	
			}
		}		
	} 
	else if(flag == ASN1IMPL)												//IMPLICIT
	{
		if (iscons == -2)												//TLV
		{
			/*ASN1_BER_Dec_Length(ws);	
			if(ASN1_BER_Dec_CHARACTERSTRING_Value(ws,tempValue,length))		
			{
				return 1;
			}
			
			AddCHARACTERSTRING(tempValue,length,value,&count);
		} 
		else if(iscons == -3)						//IMPLICIT
		{
			/*ASN1_BER_Dec_Length(ws);	
			if (length == -1)
			{
				while (!(*ws->buffer.current == 0x00 && *(ws->buffer.current+1) == 0x00))						
				{
					ASN1_BER_Dec_Tag(ws,ITS_ASN_UNIV|ITS_ASN_PRIM|ASN1_TYPE_CHARACTER_STRING);				//T
					ASN1_BER_Dec_Length(ws);											//L
					if(ASN1_BER_Dec_CHARACTERSTRING_Value(ws,tempValue,ws->dataSize))		//V
					{
						return 1;
					}					
					AddCHARACTERSTRING(tempValue,ws->dataSize,value,&count);
				}
			} 
			else
			{
				F_UL_length = length;
				F_UC_temp = ws->buffer.current;
				while (ws->buffer.current<F_UC_temp+F_UL_length)						
				{
					ASN1_BER_Dec_Tag(ws,ITS_ASN_UNIV|ITS_ASN_PRIM|ASN1_TYPE_CHARACTER_STRING);				//T
					ASN1_BER_Dec_Length(ws);											//L
					if(ASN1_BER_Dec_CHARACTERSTRING_Value(ws,tempValue,ws->dataSize))		//V
					{
						return 1;
					}					
					AddCHARACTERSTRING(tempValue,ws->dataSize,value,&count);
				}			
			}
		}
	}	
	value->data -=count;
	value->numbits = count;
	value->data = mpool_realloc(ws->Pmemory,value->data,count);
	*/

}

void AddCHARACTERSTRING(CHARACTERSTRING *tempvalue, ASNUINT32L length, CHARACTERSTRING *value, ASNUINT32 *count)
{
	/*
	ASNUINT32 i=0;
	for(i;i<length;i++)
	{
		*value->data = tempvalue->data[i];
		value->data++;
	}
	*count += length;
	*/
}




#include "ASN1_BER_STRING.h"

/************************************************
function_name:ASN1_BER_Enc_String                              
input:
     ASN1WorkSpace* ws: data save and work space
	 ASNUINT8* value: will encoding value 
	 ASNINT32 tagvalue:tag value
	 ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                    
return:
     ASNINT32: if return 0 succeed else error                                    
description:
     creat encode a value of ASN.1 string char                                   
*************************************************/
ASNINT32 ASN1_BER_Enc_String(ASN1WorkSpace *ws, ASNSTRING *value, ASNUINT32 tagvalue, ASN1TagType flag)
{
	
	ASN1_Tag_Move_Pointer(ws, tagvalue, flag);
	ASN1_BER_Enc_String_Value(ws,value);
	return 0;
}

/************************************************
function_name:ASN1_BER_Enc_String_Value                              
input:
     ASN1WorkSpace* ws: data save and work space
	 ASNUINT8* value: will encoding value                                   
return:
     ASNINT32: if return 0 succeed else error                                    
description:
     creat encode a value of ASN.1 string char                                  
*************************************************/

ASNINT32 ASN1_BER_Enc_String_Value(ASN1WorkSpace *ws, ASNSTRING *value)
{
	ASNUINT32 char_length = value->nchar;
	ASNINT32 wsmemory_sub;
	ASNINT32 wsmemory = 0;

	ASN1_BER_Enc_Length(ws, char_length);

	if (char_length > (ASNUINT32)(ws->buffer.end - ws->buffer.current)) //if buffer is full, 
	{
		wsmemory = ((ws->buffer.end - ws->buffer.data));
		wsmemory_sub = (ws->buffer.current - ws->buffer.data);

		ws->buffer.data = (ASNUINT8 *)mpool_realloc(ws->Pmemory, ws->buffer.data, (wsmemory + char_length * 2) * sizeof(ASNUINT8));
		ws->buffer.end = ws->buffer.data + wsmemory + char_length * 2;
		ws->buffer.current = ws->buffer.data + wsmemory_sub;
	}	
	
    memcpy(ws->buffer.current,value->asnstring, char_length);	
	ws->buffer.current += char_length;
	return 0;
}

/************************************************
function_name:ASN1_BER_Dec_String                              
input:
      ASN1WorkSpace* ws: data save and work space
      ASNUINT8** value: take over dcoded value
	  ASNINT32 tagvalue:tag value
	  ASNUINT32 tagvalue_c: struct tag value (default 0)
      ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                   
return:
      ASNINT32: if return 0 succeed else error                                     
description:
      creat decode a string of ASN.1 string char                                  
*************************************************/
ASNINT32 ASN1_BER_Dec_String(ASN1WorkSpace *ws, ASNSTRING *value, ASNUINT32 tagvalue, ASNINT32 length, ASN1TagType flag)
{
    ASNINT32 decode_loge = 0;
	ASNINT32 F_UI_length = 0;
//	ASNUINT8* F_UC_temp;
	ASNINT32 F_UI_CS_flag = ws->iscons;
	
	if (flag == ASN1EXPL)				//EXPLICIT
	{
		
		if (*ws->buffer.current & 0x20) //EXPLICIT struct
		{
			ASN1_BER_Dec_Tag(ws, tagvalue);
			ASN1_BER_Dec_Length(ws);
			F_UI_length = ws->dataSize;
			ASN1_BER_Dec_String_loop(ws, value, tagvalue, F_UI_length); //decode
			if (-1 == F_UI_length)
			{
				ASN1_BER_Dec_StrmEOC(ws);
			}
		}
		else //not EXPLICIT struct
		{		
			ASN1_BER_Dec_Tag(ws,tagvalue);									//T
			ASN1_BER_Dec_Length(ws);										//L
		    ASN1_BER_Dec_String_Value(ws,value,ws->dataSize,decode_loge);   //V
		}
	}////fanyapeng
	else if(flag == ASN1IMPL)												//IMPLICIT
	{
		/*ASN1_BER_Dec_Length(ws);*/	
		if (F_UI_CS_flag == -2)											    
		{
			ASN1_BER_Dec_String_Value(ws, value, length, decode_loge);		//V
		}
		else if (F_UI_CS_flag == -3)										//IMPLICIT struct
		{
			F_UI_length = length;
			ASN1_BER_Dec_String_loop(ws, value, tagvalue, F_UI_length);		//decode
			if (-1 == F_UI_length)
			{
				ASN1_BER_Dec_StrmEOC(ws);
			}
		} 
	}
	return 0;
}


/************************************************
function_name:ASN1_BER_Dec_String_Value                              
input:
      ASN1WorkSpace* ws: data save and work space
      ASNUINT8** value: take over dcoded value
      ASNINT32 length: encode length
	  ASNINT32 decode_loge:decode count flag
return:
      ASNINT32: if return 0 succeed else error                                     
description:
      creat decode a string of ASN.1 string char                                   
*************************************************/

ASNINT32 ASN1_BER_Dec_String_Value(ASN1WorkSpace *ws, ASNSTRING *value, ASNINT32 length, ASNINT32 decode_loge)
{
	ASNINT32 F_IN_Str_Len=0;
	if (0 == decode_loge)
	{
		value->asnstring = (ASNUINT8 *)mpool_malloc(ws->Pmemory, (length + 1) * sizeof(ASNUINT8));//memory replace
		memset(value->asnstring, 0, length + 1);
        value->asnstring = strncpy(value->asnstring, ws->buffer.current, length);
		value->nchar = length;
	}
	else
	{
		ASNUINT8 *concat_ptr = NULL;
		F_IN_Str_Len = value->nchar;
		value->asnstring = (ASNUINT8 *)mpool_realloc(ws->Pmemory, value->asnstring, (F_IN_Str_Len + length) * sizeof(ASNUINT8));

		concat_ptr = value->asnstring + value->nchar;
		strncpy(concat_ptr, ws->buffer.current, length);

//		value->asnstring = strncat(value->asnstring, ws->buffer.current, length);
		value->nchar += length;
		value->asnstring[value->nchar] = 0;
	}	
	ws->buffer.current = ws->buffer.current+length;
    
    if (NULL == value->asnstring)
	{
		return -1;
	}
	
	return 0;
}

/************************************************
function_name:ASN1_BER_Dec_String_loop                              
input:
ASN1WorkSpace* ws: data save and work space
Asn1_Roid* value: will encoding value 
ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                    
return:
ASNINT32: if return 0 succeed else error                                    
description:
       decode  ASN_STRING                                 
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_String_loop(ASN1WorkSpace* ws,ASNSTRING* value,
								  ASNUINT32 tagvalue,ASNINT32 decode_length)
{
	ASNUINT8* F_UC_temp;		
	ASNINT32 decode_loge = 0;

	F_UC_temp = ws->buffer.current;
	while ((!(*ws->buffer.current == 0x00 && *(ws->buffer.current+1) == 0x00))||
	      (ws->buffer.current<F_UC_temp+decode_length))
	{
		if ((-1 != decode_length)&& !(ws->buffer.current<F_UC_temp+decode_length))//not 0x80 && length slop over
			break;
		ASN1_BER_Dec_Tag(ws,tagvalue);				                    //T
		ASN1_BER_Dec_Length(ws);										//L
		if (ws->dataSize == -1)
		{
			int i = 9999;
		}
		ASN1_BER_Dec_String_Value(ws,value,ws->dataSize,decode_loge);	//V
		decode_loge++;				
	}
	return 0;
}



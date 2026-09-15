#include "ASN1_BER_BMPString.h"


/************************************************
function_name:ASN1_BER_Enc_BMPString                              
input:
     ASN1WorkSpace* ws: data save and work space
	 BMPString* value:will encode value
	 ASN1TagType flag:tag encoding Tag Type(example: EXPLICIT or IMPLICIT)
return:
     ASNINT32: if value=0 succeed else error                                
description:
     encode a ASN.1 BMPString value                                
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_BMPString(ASN1WorkSpace* ws,BMPString* value,ASN1TagType flag)
{
	ASN1_Tag_Move_Pointer(ws,ITS_ASN_UNIV|ITS_ASN_PRIM|ASN1_TYPE_BMPString,flag);
	ASN1_BER_Enc_BMPString_Value(ws,value);
	return 0;
}


/************************************************
function_name:ASN1_BER_Enc_BMPString_Value                              
input:
     ASN1WorkSpace* ws: data save and work space
	 BMPString* value:will encode value                                   
return:
     ASNINT32: if value=0 succeed else error                                
description:
     encode a ASN.1 BMPString value                               
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_BMPString_Value(ASN1WorkSpace* ws, BMPString* value)
{ 
	ASNUINT16* bmp_current = value->data;
	ASNINT32 wsmemory = 0;
	ASNINT32 wsmemory_sub = 0;
	ASNINT32 temp_nchar = value->nchar*2;
	ASN1_BER_Enc_Length(ws,value->nchar*2);
	
	temp_nchar >>= 1;
	while (temp_nchar != 0)
	{
			if (((ws->buffer.current+2) == ws->buffer.end)||
				((ws->buffer.current+2)>ws->buffer.end))
			{
				/*
				wsmemory = ((ws->buffer.end - ws->buffer.data)+10);
				wsmemory_sub = ws->buffer.current - ws->buffer.end;
				ws->buffer.data = (ASNUINT8*)mpool_realloc(ws->Pmemory,ws->buffer.data,
					wsmemory*sizeof(ASNUINT8));
				ws->buffer.end = ws->buffer.data+ wsmemory;
				if (!wsmemory_sub)
				{
					ws->buffer.current = ws->buffer.end - 10;
				}
				else
				{
					ws->buffer.current = ws->buffer.end - 10+wsmemory_sub;
				}
				*/
				ASN1_RESET_WS_INFO(ws,(ws->buffer.end-ws->buffer.data)+1000);
			}

			*ws->buffer.current |= (*value->data)>>8;
			*(ws->buffer.current+1) |= *value->data;
			ws->buffer.current+=2;

			value->data+=1;
			temp_nchar--;
	}
	value->data = bmp_current;
   return 0;
}

/************************************************
function_name:ASN1_BER_Dnc_BMPString                              
input:
     ASN1WorkSpace* ws: data save and work space
	 BMPString* value:take over dcoded value
	 ASNUINT32 tagvalue_c:struct tag value (default 0)
	 ASN1TagType flag:encoding Tag Type(example: EXPLICIT or IMPLICIT)
return:
     ASNINT32: if value=0 succeed else error                                
description:
     creat decode a string of ASN.1 BMPString                                
*************************************************/


ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_BMPString(ASN1WorkSpace* ws,BMPString* value,
							 ASNINT32 length,ASN1TagType flag)
{
	ASNINT32 decode_loge = 0;
	ASNINT32 F_UI_length = 0;
	ASNINT32 F_UI_CS_flag = ws->iscons;
	
	if (flag == ASN1EXPL)				//EXPLICIT
	{
		
		if (*ws->buffer.current & 0x20) //EXPLICIT struct
		{
			ASN1_BER_Dec_Tag(ws,ITS_ASN_UNIV | ITS_ASN_CONS | ASN1_TYPE_BMPString);
			ASN1_BER_Dec_Length(ws);
			F_UI_length = ws->dataSize;
			ASN1_BER_Dec_BMPString_loop(ws,value,F_UI_length);//decode
			if (-1 == F_UI_length)
			{
				ASN1_BER_Dec_StrmEOC(ws);
			}
		}
		else //not EXPLICIT struct
		{		
			ASN1_BER_Dec_Tag(ws,ITS_ASN_UNIV | ITS_ASN_PRIM | ASN1_TYPE_BMPString);             //T
			ASN1_BER_Dec_Length(ws);                                         //L
			ASN1_BER_Dec_BMPString_Value(ws,value,ws->dataSize,decode_loge);   //V
		
		}
	}////fanyapeng
	
	
	else if(flag == ASN1IMPL)												//IMPLICIT
	{
		/*ASN1_BER_Dec_Length(ws);*/

		if (F_UI_CS_flag == -2)											    
		{
			ASN1_BER_Dec_BMPString_Value(ws,value,length,decode_loge);//V
		}
		else if(F_UI_CS_flag == -3)						//IMPLICIT struct
		{
			F_UI_length = length;
			ASN1_BER_Dec_BMPString_loop(ws,value,F_UI_length);//decode
			if (-1 == F_UI_length)
			{
				ASN1_BER_Dec_StrmEOC(ws);
			}
		} 
	}
	
	return 0;
	
}

/************************************************
function_name:ASN1_BER_Dec_BMPString_Value                              
input:
      ASN1WorkSpace* ws: data save and work space
      BMPString* value: take over dcoded value
      ASNINT32 length: encode length
	  ASNINT32 decode_loge:decode count flag                               
return:
     ASNINT32: if value=0 succeed else error                                
description:
     creat decode a string of ASN.1 BMPString                                   
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_BMPString_Value(ASN1WorkSpace* ws, BMPString* value,
								   ASNINT32 length,ASNINT32 decode_loge)
{
	ASNUINT32 F_IN_Str_Len;
//	ASNINT32 F_IN_Str_Dec_Count;
	
	if (0 == decode_loge)
	{
	    value->data = (ASNUINT16*)mpool_malloc(ws->Pmemory,length);//memory replace
		memset(value->data,'\0',length);
		F_IN_Str_Len=value->nchar = 0;
	}
	else
	{	
		value->data = (ASNUINT16*)mpool_realloc(ws->Pmemory,value->data,(value->nchar+(length>>1))*sizeof(ASNUINT16));
		F_IN_Str_Len= value->nchar;
	}
	if (NULL == value->data)
	{
		return -1;
	}

	value->nchar += length>>1;
    while (F_IN_Str_Len < value->nchar)
    {
		value->data[F_IN_Str_Len] =0;
		/*value->data[F_IN_Str_Len] <<= 8;
		value->data[F_IN_Str_Len] += *ws->buffer.current;*/
		value->data[F_IN_Str_Len] = (*ws->buffer.current) * 256 + (*(ws->buffer.current+1));
		ws->buffer.current =ws->buffer.current+2;
		F_IN_Str_Len++;
    }
	
// 	value->nchar <<= 1;
	return 0;
}


/************************************************
function_name:ASN1_BER_Dec_BMPString_loop                              
input:
     ASN1WorkSpace* ws: data save and work space
	 BMPString* value: take over dcoded value
	 ASNINT32 decode_loge:decode count flag                                    
return:
     ASNINT32: if value=0 succeed else error                                
description:
     creat decode a string of ASN.1 BMPString                               
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_BMPString_loop(ASN1WorkSpace* ws,BMPString* value,ASNINT32 decode_length)
{
	ASNUINT8* F_UC_temp;		
	ASNINT32 decode_loge = 0;
	
	F_UC_temp = ws->buffer.current;
	while (!(*ws->buffer.current==0x00 && *(ws->buffer.current+1)==0x00)||
		(ws->buffer.current<F_UC_temp+decode_length))
	{
		if ((-1 != decode_length)&& !(ws->buffer.current<F_UC_temp+decode_length))//not 0x80 && length slop over
			break;
		ASN1_BER_Dec_Tag(ws,ITS_ASN_UNIV|ITS_ASN_PRIM|ASN1_TYPE_BMPString);			    //T
		ASN1_BER_Dec_Length(ws);											//L
		ASN1_BER_Dec_BMPString_Value(ws,value,ws->dataSize,decode_loge);	    //V
		decode_loge++;				
	}
	return 0;
}


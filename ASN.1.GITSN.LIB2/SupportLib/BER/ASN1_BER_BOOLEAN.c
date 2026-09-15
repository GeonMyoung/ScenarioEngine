
#include "ASN1_BER_BOOLEAN.h"

/************************************************
function_name:ASN1_BER_Enc_BOOLEAN                              
input:
     ASN1WorkSpace* ws: data save and work space
	 BOOLEAN value: will encoding value 
	 ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                    
return:
     ASNINT32: if return 0 succeed else error                                    
description:
     Will a BOOLEAN Type encoding                                  
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_BOOLEAN(ASN1WorkSpace* ws, BOOLEAN *Tvalue, ASN1TagType flag)
{
    ASN1_Tag_Move_Pointer(ws,ITS_ASN_UNIV|ITS_ASN_PRIM|ASN1_TYPE_BOOLEAN,flag); //tag value encode
	ASN1_BER_Enc_BOOLEAN_Value(ws,Tvalue); //bool value encode
	return 0;
}

/************************************************
function_name:ASN1_BER_Dec_BOOLEAN                              
input:
     ASN1WorkSpace* ws: data save and work space
	 Asn1_Roid* value: will decoding value 
	 ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                     
return:
     ASNINT32: if return 0 succeed else error                                    
description:
     Will a BOOLEAN Type decoding                                 
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_BOOLEAN(ASN1WorkSpace* ws, BOOLEAN *value,
						   ASNINT32 length, ASN1TagType flag)
{
	if (flag == ASN1EXPL || flag == UNASN1IMEXPL)
	{
		ASN1_BER_Dec_Tag(ws,ITS_ASN_UNIV|ITS_ASN_PRIM|ASN1_TYPE_BOOLEAN); //if tag type = EXPLICIT or nothing type, 
		                        //This line program by running 
		ASN1_BER_Dec_Length(ws);
		ASN1_BER_Dec_BOOLEAN_Value(ws,value,ws->dataSize);
	}
	/*ASN1_BER_Dec_Length(ws);//decode value length*/
	else
    ASN1_BER_Dec_BOOLEAN_Value(ws,value,length);//decode bool value
	return 0;

}

/************************************************
function_name:ASN1_BER_Enc_BOOLEAN_Value                              
input:
     ASN1WorkSpace* ws: data save and work space
	 Asn1_Roid* value: will encoding value                                    
return:
     ASNINT32: if return 0 succeed else error                                    
description:
     Will a BOOLEAN Value encoding                                 
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_BOOLEAN_Value(ASN1WorkSpace* ws, BOOLEAN *Tvalue)
{
    BOOLEAN value = *Tvalue;
	ASNUINT8 tempbool[1];
	tempbool[0] = 0x01; 
	ASN1_BER_FillBuffer(ws,tempbool,1,0);
	//*ws->buffer.current = 0x01; //set bool tag value
    ws->buffer.current++;
    if(0 == value)
    {
		tempbool[0] = 0x00; 
		ASN1_BER_FillBuffer(ws,tempbool,1,0);
        //*ws->buffer.current = 0x00;//if value = 0, the bool value will encoding 0x00                   
    }
    else
    {
		tempbool[0] = 0xff; 
		ASN1_BER_FillBuffer(ws,tempbool,1,0);
        //*ws->buffer.current = 0xff;//if value = 0, the bool value will encoding 0xff
    }
    ws->buffer.current++;
    
    return 0;
}

/************************************************
function_name:ASN1_BER_Dec_BOOLEAN_Value                              
input:
     ASN1WorkSpace* ws: data save and work space
	 Asn1_Roid* value: will decoding value
	 ASNINT32 length:will decoding value length
return:
     ASNINT32: if return 0 succeed else error                                    
description:
     Will a BOOLEAN Value decoding                                 
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_BOOLEAN_Value(ASN1WorkSpace* ws, BOOLEAN *value, ASNINT32 length)
{
	if(*ws->buffer.current == 0x00)//decode bool value
	{
		*value = 0x00;
	}
	else
	{
		*value = 0xff;
	}
	ws->buffer.current++;
	return 0;
}


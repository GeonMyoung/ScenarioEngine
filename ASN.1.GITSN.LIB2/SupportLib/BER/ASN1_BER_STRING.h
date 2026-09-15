#ifndef _ASN_BER_STRING_H_
#define _ASN_BER_STRING_H_

#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"
#include "../TYPE/ASN1_Type.h"


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


ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_String_Value(ASN1WorkSpace* ws, ASNSTRING* value);

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


ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_String_Value(ASN1WorkSpace* ws, ASNSTRING* value,
								   ASNINT32 length,ASNINT32 decode_loge);

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


ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_String(ASN1WorkSpace* ws,ASNSTRING* value,ASNUINT32 tagvalue,
							 ASN1TagType flag);

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

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_String(ASN1WorkSpace* ws,ASNSTRING* value,
							 ASNUINT32 tagvalue,ASNINT32 length,ASN1TagType flag);


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

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_String_loop(ASN1WorkSpace* ws,ASNSTRING* value,ASNUINT32 tagvalue,ASNINT32 decode_length);

#endif /*_ASN_STRING_H_*/

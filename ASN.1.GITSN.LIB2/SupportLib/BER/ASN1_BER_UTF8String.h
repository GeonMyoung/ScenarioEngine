#ifndef _ASN_BER_UTF8STRING_H_
#define _ASN_BER_UTF8STRING_H_

#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"
#include "../TYPE/ASN1_Type.h"
#include "ASN1_BER_STRING.h"



/************************************************
function_name:ASN1_BER_Enc_UTF8String                              
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

#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_UTF8Str(ASN1WorkSpace* ws, UTF8Str* value, ASN1TagType flag);
#else
ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_UTF8String(ASN1WorkSpace* ws, UTF8String* value, ASN1TagType flag);
#endif
/************************************************
function_name:ASN1_BER_Dec_UTF8String                              
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

#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_UTF8Str(ASN1WorkSpace* ws, UTF8Str* value, ASNINT32 length,ASN1TagType flag);
#else
ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_UTF8String(ASN1WorkSpace* ws, UTF8String* value, ASNINT32 length,ASN1TagType flag);
#endif

#endif /*_ASN_UTF8STRING_H_*/


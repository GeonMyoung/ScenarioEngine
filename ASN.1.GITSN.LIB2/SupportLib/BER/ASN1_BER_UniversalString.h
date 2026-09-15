#ifndef _ASN_BER_UniversalString_H_
#define _ASN_BER_UniversalString_H_
/*
  Name:UniversalString
  Copyright: 
  Author: fanyapeng
  Date: 21-04-08 14:39
  Description: encode decode UniversalString
*/

#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"
#include "../TYPE/ASN1_Type.h"

	

/************************************************
function_name:ASN1_BER_Enc_UniversalString                              
input:
ASN1WorkSpace* ws: data save and work space
UniversalString* value:will encode value
ASN1TagType flag:tag encoding Tag Type(example: EXPLICIT or IMPLICIT)
return:
ASNINT32: if value=0 succeed else error                                
description:
encode a ASN.1 UniversalString value                                
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_UniversalString(ASN1WorkSpace* ws,UniversalString* value,ASN1TagType flag);

/************************************************
function_name:ASN1_BER_Enc_UniversalString_Value                              
input:
ASN1WorkSpace* ws: data save and work space
UniversalString* value:will encode value                                   
return:
ASNINT32: if value=0 succeed else error                                
description:
encode a ASN.1 UniversalString value                               
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_UniversalString_Value(ASN1WorkSpace* ws, UniversalString* value);

/************************************************
function_name:ASN1_BER_Dnc_UniversalString                              
input:
ASN1WorkSpace* ws: data save and work space
UniversalString* value:take over dcoded value
ASNUINT32 tagvalue_c:struct tag value (default 0)
ASN1TagType flag:encoding Tag Type(example: EXPLICIT or IMPLICIT)
return:
ASNINT32: if value=0 succeed else error                                
description:
creat decode a string of ASN.1 UniversalString                                
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_UniversalString(ASN1WorkSpace* ws,UniversalString* value,
						   ASNINT32 length,ASN1TagType flag);


/************************************************
function_name:ASN1_BER_Dnc_UniversalString_Value                              
input:
ASN1WorkSpace* ws: data save and work space
UniversalString* value: take over dcoded value
ASNINT32 length: encode length
ASNINT32 decode_loge:decode count flag                               
return:
ASNINT32: if value=0 succeed else error                                
description:
creat decode a string of ASN.1 UniversalString                                   
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_UniversalString_Value(ASN1WorkSpace* ws, UniversalString* value,ASNINT32 length,ASNINT32 decode_loge);


/************************************************
function_name:ASN1_BER_Dec_UniversalString_loop                              
input:
ASN1WorkSpace* ws: data save and work space
UniversalString* value: take over dcoded value
ASNINT32 decode_loge:decode count flag                                    
return:
ASNINT32: if value=0 succeed else error                                
description:
creat decode a string of ASN.1 UniversalString                               
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_UniversalString_loop(ASN1WorkSpace* ws,UniversalString* value,ASNINT32 decode_length);


#endif /*_ASN_UniversalString_H_*/


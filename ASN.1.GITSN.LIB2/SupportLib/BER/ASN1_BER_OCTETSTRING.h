#ifndef _ASN_BER_Octstr_H_
#define _ASN_BER_Octstr_H_

#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"
#include "../TYPE/ASN1_Type.h"


/************************************************
function_name:ASN1_BER_Enc_OCTETSTRING	                              
input:
ASN1WorkSpace* ws: data save and work space
OCTETSTRING * value: will encoding value 
ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                    
return:
ASNINT32: if return 0 succeed else error                                    
description:
creat encode a value of oct string struct and Tag Length                                 
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_OCTETSTRING(ASN1WorkSpace*ws, OCTETSTRING * value, ASN1TagType flag);



/************************************************
function_name:ASN1_BER_Dec_OCTETSTRING	                              
input:
ASN1WorkSpace* ws: data save and work space
OCTETSTRING *value: will encoding value   
ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                 
return:
ASNINT32: if return 0 succeed else error                                    
description:
decode ws and put the result into value                                 
*************************************************/
//ASNINT32 ASN1_BER_Dec_OCTETSTRING(ASN1WorkSpace*ws, OCTETSTRING *value,ASN1TagType flag);



/************************************************
function_name:ASN1_BER_Enc_OCTETSTRING_Value	                              
input:
ASN1WorkSpace* ws: data save and work space
OCTETSTRING *value: will encoding value                                    
return:
ASNINT32: if return 0 succeed else error                                    
description:
creat encode a value of oct string struct                                  
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_OCTETSTRING_Value(ASN1WorkSpace *ws, OCTETSTRING *value);



/************************************************
function_name:ASN1_BER_Dec_OCTETSTRING_Value	                              
input:
ASN1WorkSpace* ws: data save and work space
OCTETSTRING *value: will encoding value   
ASNUINT32L length: decode value 's length                               
return:
ASNINT32: if return 0 succeed else error                                    
description:
decode ws and put the result into value                                 
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_OCTETSTRING_Value(ASN1WorkSpace *ws, OCTETSTRING *value,ASNUINT32L length);



/************************************************
function_name:ASN1_BER_Dec_OCTETSTRING	                              
input:
ASN1WorkSpace* ws: data save and work space
OCTETSTRING *value: will encoding value   
ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                               
return:
ASNINT32: if return 0 succeed else error                                    
description:
constructed decode ws and put the result into value                                 
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_OCTETSTRING(ASN1WorkSpace *ws, OCTETSTRING *value, 
									 ASNINT32 length,ASN1TagType flag);



/************************************************
function_name:AddOctString	                              
input:
OCTETSTRING *tempvalue:oct string temp value 
ASNUINT32L length:oct string temp value's length 
OCTETSTRING *value:decode result value
ASNUINT32 *count:total oct string temp value's length                             
return: void                                   
description:
incorporate oct string temp value to result value                                 
*************************************************/
// ASN1_CPPLINK void AddOctString(ASN1WorkSpace *ws,OCTETSTRING *tempvalue,ASNUINT32L length,OCTETSTRING *value,ASNUINT32* count);

#endif

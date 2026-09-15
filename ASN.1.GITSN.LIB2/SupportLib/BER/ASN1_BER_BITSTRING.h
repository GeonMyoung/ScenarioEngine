#ifndef _ASN_BER_Bitstr_H_
#define _ASN_BER_Bitstr_H_

#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"
#include "../TYPE/ASN1_Type.h"


/************************************************
function_name:ASN1_BER_Enc_BITSTRING	                              
input:
ASN1WorkSpace* ws: data save and work space
BITSTRING* value: will encoding value 
ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                    
return:
ASNINT32: if return 0 succeed else error                                    
description:
creat encode a value of bit string struct and Tag Length                                 
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_BITSTRING(ASN1WorkSpace *ws, BITSTRING *value, ASN1TagType flag);



/************************************************
function_name:ASN1_BER_Enc_BITSTRING_Value	                              
input:
ASN1WorkSpace* ws: data save and work space
BITSTRING* value: will encoding value                                    
return:
ASNINT32: if return 0 succeed else error                                    
description:
creat encode a value of bit string struct                                  
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_BITSTRING_Value(ASN1WorkSpace *ws, BITSTRING *value);



/************************************************
function_name:ASN1_BER_Dec_BITSTRING	                              
input:
ASN1WorkSpace* ws: data save and work space
BITSTRING* value: will encoding value   
ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                 
return:
ASNINT32: if return 0 succeed else error                                    
description:
decode ws and put the result into value                                 
*************************************************/
//ASNINT32 ASN1_BER_Dec_BITSTRING(ASN1WorkSpace *ws, ASN1_BIT_STRING*value, ASN1TagType flag);



/************************************************
function_name:ASN1_BER_Dec_BITSTRING_Value	                              
input:
ASN1WorkSpace* ws: data save and work space
BITSTRING* value: will encoding value   
ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)  
ASNUINT32L length: decode value 's length                               
return:
ASNINT32: if return 0 succeed else error                                    
description:
decode ws and put the result into value                                 
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_BITSTRING_Value(ASN1WorkSpace *ws, BITSTRING *value,ASNUINT32L length);



/************************************************
function_name:ASN1_BER_ConDec_BITSTRING	                              
input:
ASN1WorkSpace* ws: data save and work space
BITSTRING* value: will encoding value   
ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                               
return:
ASNINT32: if return 0 succeed else error                                    
description:
constructed decode ws and put the result into value                                 
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_BITSTRING(ASN1WorkSpace *ws, BITSTRING *value, ASNINT32 length, ASN1TagType flag);



/************************************************
function_name:AddBITSTRING	                              
input:
BITSTRING *tempvalue:bit string temp value 
ASNUINT32L length:bit string temp value's length 
BITSTRING *value:decode result value
ASNUINT32 *count:total bit string temp value's length                             
return: void                                   
description:
incorporate bit string temp value to result value                                 
*************************************************/
//ASN1_CPPLINK void AddBitString(BITSTRING *tempvalue,ASNUINT32L length,BITSTRING *value,ASNUINT32* count);


#endif



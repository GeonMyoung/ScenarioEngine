#ifndef _ASN_BER_Charstr_H_
#define _ASN_BER_Charstr_H_

#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"
#include "../TYPE/ASN1_Type.h"
#include "../TOOL/ASN1_CHAR_TOOL.h"



/************************************************
function_name:ASN1_BER_Enc_CHARACTERSTRING	                              
input:
ASN1WorkSpace* ws: data save and work space
CHARACTERSTRING * value: will encoding value 
ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                    
return:
ASNINT32: if return 0 succeed else error                                    
description:
creat encode a value of oct string struct and Tag Length                                 
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_CHARACTERSTRING(ASN1WorkSpace*ws, CHARACTERSTRING * value, ASN1TagType flag);



/************************************************
function_name:ASN1_BER_Dec_CHARACTERSTRING	                              
input:
ASN1WorkSpace* ws: data save and work space
CHARACTERSTRING *value: will encoding value   
ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                 
return:
ASNINT32: if return 0 succeed else error                                    
description:
decode ws and put the result into value                                 
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_CHARACTERSTRING(ASN1WorkSpace*ws, CHARACTERSTRING *value, 
								 ASNINT32 length,ASN1TagType flag);



/************************************************
function_name:ASN1_BER_Enc_CHARACTERSTRING_Value	                              
input:
ASN1WorkSpace* ws: data save and work space
CHARACTERSTRING *value: will encoding value                                    
return:
ASNINT32: if return 0 succeed else error                                    
description:
creat encode a value of oct string struct                                  
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_CHARACTERSTRING_Value(ASN1WorkSpace *ws, CHARACTERSTRING *value);



/************************************************
function_name:ASN1_BER_Dec_CHARACTERSTRING_Value	                              
input:
ASN1WorkSpace* ws: data save and work space
CHARACTERSTRING *value: will encoding value   
ASNUINT32L length: decode value 's length                               
return:
ASNINT32: if return 0 succeed else error                                    
description:
decode ws and put the result into value                                 
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_CHARACTERSTRING_Value(ASN1WorkSpace *ws, CHARACTERSTRING *value,ASNUINT32L length);



/************************************************
function_name:ASN1_BER_ConDec_CHARACTERSTRING	                              
input:
ASN1WorkSpace* ws: data save and work space
CHARACTERSTRING *value: will encoding value   
ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                               
return:
ASNINT32: if return 0 succeed else error                                    
description:
constructed decode ws and put the result into value                                 
*************************************************/
//ASNINT32 ASN1_BER_Dec_CHARACTERSTRING(ASN1WorkSpace *ws, CHARACTERSTRING *value, ASN1TagType flag);



/************************************************
function_name:AddCHARACTERSTRING	                              
input:
CHARACTERSTRING *tempvalue:oct string temp value 
ASNUINT32L length:oct string temp value's length 
CHARACTERSTRING *value:decode result value
ASNUINT32 *count:total oct string temp value's length                             
return: void                                   
description:
incorporate oct string temp value to result value                                 
*************************************************/
ASN1_CPPLINK void AddCHARACTERSTRING(CHARACTERSTRING *tempvalue,ASNUINT32L length,CHARACTERSTRING *value,ASNUINT32* count);

#endif

#ifndef BER__ENUMERATED_H
#define BER__ENUMERATED_H

#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"
#include "../TYPE/ASN1_Type.h"
#include "../TOOL/Infinite_tool.h"


/************************************************
function_name:ASN1_BER_Enc_ENUMERATED	                              
input:
ASN1WorkSpace* ws: data save and work space
ASNINT32 value: will encoding value 
ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                    
return:
ASNINT32: if return 0 succeed else error                                    
description:
creat encode a value of Integer and Tag Length                                 
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_ENUMERATED(ASN1WorkSpace *ws,ENUMERATED *Tvalue,ASN1TagType flag);




/************************************************
function_name:ASN1_BER_Dec_ENUMERATED	                              
input:
ASN1WorkSpace* ws: data save and work space
ENUMERATED *value: will encoding value   
ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                 
return:
ASNINT32: if return 0 succeed else error                                    
description:
decode ws and put the result into value(integer)                                
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_ENUMERATED(ASN1WorkSpace *ws,ENUMERATED *value,ASNINT32 length,ASN1TagType flag);




/************************************************
function_name:ASN1_BER_Enc_ENUMERATED_Value	                              
input:
ASN1WorkSpace* ws: data save and work space
ENUMERATED value: will encoding value 
return:
ASNINT32: if return 0 succeed else error                                    
description:
creat encode a value of Integer                                 
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_ENUMERATED_Value(ASN1WorkSpace *ws,ENUMERATED *Tvalue);




/************************************************
function_name:ASN1_BER_Dec_ENUMERATED_Value	                              
input:
ASN1WorkSpace* ws: data save and work space
ENUMERATED value: will encoding value   
ASNUINT32L length: decode length                               
return:
ASNINT32: if return 0 succeed else error                                    
description:
decode ws and put the result into value                                
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_ENUMERATED_Value(ASN1WorkSpace *ws,ENUMERATED* value,ASNUINT32L length);


#endif

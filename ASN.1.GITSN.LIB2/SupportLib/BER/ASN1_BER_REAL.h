#ifndef _ASN_BER_REAL_H
#define _ASN_BER_REAL_H


#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"
#include "../TYPE/ASN1_Type.h"
	
#include "math.h"





/************************************************
function_name:ASN1_BER_Enc_REAL	                              
input:
ASN1WorkSpace* ws: data save and work space
REAL value: will encoding value 
ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                    
return:
ASNINT32: if return 0 succeed else error                                    
description:
creat encode a value of Integer and Tag Length                                 
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_REAL(ASN1WorkSpace*ws, REAL *Tvalue, ASN1TagType flag);



/************************************************
function_name:ASN1_BER_Dec_REAL	                              
input:
ASN1WorkSpace* ws: data save and work space
REAL *value: will encoding value   
ASN1TagType flag: decoding Tag Type(example: EXPLICIT or IMPLICIT)                                 
return:
ASNINT32: if return 0 succeed else error                                    
description:
decode ws and put the result into value                               
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_REAL(ASN1WorkSpace*ws, REAL* value,ASNINT32 length,ASN1TagType flag);



/************************************************
function_name:ASN1_BER_Enc_REAL_value	                              
input:
ASN1WorkSpace* ws: data save and work space
REAL value: will encoding value 
return:
ASNINT32: if return 0 succeed else error                                    
description:
creat encode a value of real                                 
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_REAL_value(ASN1WorkSpace*ws, REAL *Tvalue);



/************************************************
function_name:ASN1_BER_Dec_REAL_value	                              
input:
ASN1WorkSpace* ws: data save and work space
REAL value: will encoding value   
ASNUINT32L length: decode length                               
return:
ASNINT32: if return 0 succeed else error                                    
description:
decode ws and put the result into value                                
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_REAL_value(ASN1WorkSpace*ws, REAL *value ,ASNUINT32L length);
 

#endif


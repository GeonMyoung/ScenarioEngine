#ifndef _ASN_BER_NULL_H_
#define _ASN_BER_NULL_H_

#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"

	

/************************************************
function_name:ASN_BER_Enc_NULL	                              
input:
ASN1WorkSpace* ws: data save and work space
ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                    
return:
ASNINT32: if return 0 succeed else error                                    
description:
creat encode a value of null and Tag Length                                 
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_NULL(ASN1WorkSpace* ws,ASN1TagType flag);


/************************************************
function_name:ASN_BER_Dec_NULL	                              
input:
ASN1WorkSpace* ws: data save and work space
ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                 
return:
ASNINT32: if return 0 succeed else error                                    
description:
decode ws and put the result into value                                 
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_NULL(ASN1WorkSpace* ws,ASN1TagType flag);

#endif



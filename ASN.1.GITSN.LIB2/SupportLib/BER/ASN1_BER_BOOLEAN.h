#ifndef _ASN_BER_BOOL_H_
#define _ASN_BER_BOOL_H_

#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"
#include "../TYPE/ASN1_Type.h"


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

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_BOOLEAN(ASN1WorkSpace* ws, BOOLEAN *Tvalue, ASN1TagType flag);

/************************************************
function_name:ASN1_BER_Dec_BOOLEAN                              
input:
     ASN1WorkSpace* ws: data save and work space
	 BOOLEAN* value: will decoding value 
	 ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                     
return:
     ASNINT32: if return 0 succeed else error                                    
description:
     Will a BOOLEAN Type decoding                                 
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_BOOLEAN(ASN1WorkSpace* ws,BOOLEAN *value,
						   ASNINT32 length,ASN1TagType flag);

/************************************************
function_name:ASN1_BER_Enc_BOOLEAN_Value                              
input:
     ASN1WorkSpace* ws: data save and work space
	 BOOLEAN* value: will encoding value                                    
return:
     ASNINT32: if return 0 succeed else error                                    
description:
     Will a BOOLEAN Value encoding                                 
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_BOOLEAN_Value(ASN1WorkSpace* ws, BOOLEAN *Tvalue);

/************************************************
function_name:ASN1_BER_Dec_BOOLEAN_Value                              
input:
     ASN1WorkSpace* ws: data save and work space
	 BOOLEAN* value: will decoding value
	 ASNINT32 length:will decoding value length
return:
     ASNINT32: if return 0 succeed else error                                    
description:
     Will a BOOLEAN Value decoding                                 
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_BOOLEAN_Value(ASN1WorkSpace* ws, BOOLEAN *value, ASNINT32 length);

#endif /*_ASN_BOOL_H_*/


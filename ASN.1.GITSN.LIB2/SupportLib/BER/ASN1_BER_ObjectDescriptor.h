#ifndef _ASN_BER_ObjectDescriptor_H_
#define _ASN_BER_ObjectDescriptor_H_

#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"
#include "../TYPE/ASN1_Type.h"
#include "ASN1_BER_STRING.h"




/************************************************
function_name:ASN1_BER_Enc_IA5String                              
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


ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_ObjectDescriptor(ASN1WorkSpace* ws,ObjectDescriptor* value,
									   ASN1TagType flag);

/************************************************
function_name:ASN1_BER_Dec_IA5String                              
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

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_ObjectDescriptor(ASN1WorkSpace* ws,ObjectDescriptor* value,
									   ASNINT32 length,ASN1TagType flag);

#endif /*_ASN_ObjectDescriptor_H_*/


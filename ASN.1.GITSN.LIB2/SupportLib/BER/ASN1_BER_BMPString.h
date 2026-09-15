#ifndef _ASN_BER_BMPString_H_
#define _ASN_BER_BMPString_H_
/*
  Name:BMPString
  Copyright: 
  Author: fanyapeng
  Date: 21-04-08 14:40
  Description: encode decode BMPString
*/
#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"
#include "../TYPE/ASN1_Type.h"


/************************************************
function_name:ASN1_BER_Enc_BMPString                              
input:
     ASN1WorkSpace* ws: data save and work space
	 BMPString* value:will encode value
	 ASN1TagType flag:tag encoding Tag Type(example: EXPLICIT or IMPLICIT)
return:
     ASNINT32: if value=0 succeed else error                                
description:
     encode a ASN.1 BMPString value                                
*************************************************/


ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_BMPString(ASN1WorkSpace* ws,BMPString* value,ASN1TagType flag);


/************************************************
function_name:ASN1_BER_Enc_BMPstr_Value                              
input:
     ASN1WorkSpace* ws: data save and work space
	 BMPString* value:will encode value                                   
return:
     ASNINT32: if value=0 succeed else error                                
description:
     encode a ASN.1 BMPString value                               
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_BMPString_Value(ASN1WorkSpace* ws, BMPString* value);

/************************************************
function_name:ASN1_BER_Dnc_BMPstr                              
input:
     ASN1WorkSpace* ws: data save and work space
	 BMPString* value:take over dcoded value
	 ASNUINT32 tagvalue_c:struct tag value (default 0)
	 ASN1TagType flag:encoding Tag Type(example: EXPLICIT or IMPLICIT)
return:
     ASNINT32: if value=0 succeed else error                                
description:
     creat decode a string of ASN.1 BMPString                                
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_BMPString(ASN1WorkSpace* ws,BMPString* value,
							 ASNINT32 length,ASN1TagType flag);


/************************************************
function_name:ASN1_BER_Dnc_BMPstr_Value                              
input:
      ASN1WorkSpace* ws: data save and work space
      BMPString* value: take over dcoded value
      ASNINT32 length: encode length
	  ASNINT32 decode_loge:decode count flag                               
return:
     ASNINT32: if value=0 succeed else error                                
description:
     creat decode a string of ASN.1 BMPString                                   
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_BMPString_Value(ASN1WorkSpace* ws, BMPString* value,ASNINT32 length,ASNINT32 decode_loge);


/************************************************
function_name:ASN1_BER_Dec_BMPString_loop                              
input:
     ASN1WorkSpace* ws: data save and work space
	 BMPString* value: take over dcoded value
	 ASNINT32 decode_loge:decode count flag                                    
return:
     ASNINT32: if value=0 succeed else error                                
description:
     creat decode a string of ASN.1 BMPString                               
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_BMPString_loop(ASN1WorkSpace* ws,BMPString* value,ASNINT32 decode_length);


#endif /*_ASN_BMPString_H_*/


#ifndef _ASN_BER_ROID_H_
#define _ASN_BER_ROID_H_
/*
  Name: Relative-oid
  Copyright: 
  Author: fanyapeng
  Date: 21-04-08 14:40
  Description: encode decode Relative-oid
*/
#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"
#include "../TYPE/ASN1_Type.h"

	

/************************************************
function_name:ASN1_BER_Enc_RELATIVE_OID_Value                              
input:
     ASN1WorkSpace* ws: data save and work space
	 RELATIVE_OID* value: will encoding value                                   
return:
     ASNINT32: if return 0 succeed else error                                    
description:
     creat encode a value of RELATIVE-OID struct                                  
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_RELATIVE_OID_Value(ASN1WorkSpace* ws, RELATIVE_OID* value);

/************************************************
function_name:ASN1_BER_Dec_RELATIVE_OID_Value                              
input:
      ASN1WorkSpace* ws: data save and work space
      RELATIVE_OID* value: take over dcoded value
      ASNINT32 length: encode length                                   
return:
      ASNINT32: if return 0 succeed else error                                     
description:
      creat decode a string of RELATIVE-OID struct                                  
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_RELATIVE_OID_Value(ASN1WorkSpace* ws, RELATIVE_OID* value,ASNINT32 length);

/************************************************
function_name:ASN1_BER_Enc_RELATIVE_OID                              
input:
     ASN1WorkSpace* ws: data save and work space
	 RELATIVE_OID* value: will encoding value 
	 ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                    
return:
     ASNINT32: if return 0 succeed else error                                    
description:
     creat encode a value of RELATIVE-OID struct                                  
*************************************************/


ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_RELATIVE_OID(ASN1WorkSpace* ws,RELATIVE_OID* value,ASN1TagType flag);
/************************************************
function_name:ASN1_BER_Dec_RELATIVE_OID                              
input:
      ASN1WorkSpace* ws: data save and work space
      RELATIVE_OID* value: take over dcoded value
      ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                   
return:
      ASNINT32: if return 0 succeed else error                                     
description:
      creat decode a string of RELATIVE-OID struct                                  
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_RELATIVE_OID(ASN1WorkSpace* ws,RELATIVE_OID* value,
						   ASNINT32 length,ASN1TagType flag);

/************************************************
function_name:ASN1_BER_Reset_Memory                              
input:
      ASNINT32 F_In_RELATIVE_OID_Enc_Memony    
	  ASNUINT8** F_Uc_RELATIVE_OID_Enc_Memony
return:
      ASNINT32: if return 0 succeed else error                                     
description:
      reset memory for save temp Encode value;                                 
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Reset_Memory(ASNINT32 F_In_RELATIVE_OID_Enc_Memony,ASNUINT8** F_Uc_RELATIVE_OID_Enc_Memony);




#endif /*_ASN_ROID_H_*/


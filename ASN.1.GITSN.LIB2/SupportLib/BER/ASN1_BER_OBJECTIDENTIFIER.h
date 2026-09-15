#ifndef _ASN_BER_OID_H_
#define _ASN_BER_OID_H_
/*
  Name: OBJECT IDENTIFIER
  Copyright: 
  Author: fanyapeng
  Date: 21-04-08 14:40
  Description: encode decode OBJECT IDENTIFIER
*/
#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"
#include "../TYPE/ASN1_Type.h"


	

/************************************************
function_name:ASN1_BER_Enc_OBJECTIDENTIFIER                              
input:
     ASN1WorkSpace* ws: data save and work space
	 OBJECTIDENTIFIER* value: will encoding value 
	 ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                    
return:
     ASNINT32: if return 0 succeed else error                                    
description:
     creat encode a value of OBJECT IDENTIFIER struct                                  
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_OBJECTIDENTIFIER(ASN1WorkSpace* ws, OBJECTIDENTIFIER* value, ASN1TagType flag);

/************************************************
function_name:ASN1_BER_Dec_OBJECTIDENTIFIER                              
input:
     ASN1WorkSpace* ws: data save and work space
	 OBJECTIDENTIFIER* value: will encoding value 
	 ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                    
return:
     ASNINT32: if return 0 succeed else error                                    
description:
     creat encode a value of OBJECT IDENTIFIER struct                                  
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_OBJECTIDENTIFIER(ASN1WorkSpace* ws, OBJECTIDENTIFIER* value, 
							ASNINT32 length,ASN1TagType flag);

/************************************************
function_name:ASN1_BER_Enc_OBJECTIDENTIFIER_Value                              
input:
     ASN1WorkSpace* ws: data save and work space
	 OBJECTIDENTIFIER* value: will encoding value 
	 ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                    
return:
     ASNINT32: if return 0 succeed else error                                    
description:
     creat encode a value of OBJECT IDENTIFIER struct                                  
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_OBJECTIDENTIFIER_Value(ASN1WorkSpace* ws, OBJECTIDENTIFIER* value);

/************************************************
function_name:ASN1_BER_Dec_OBJECTIDENTIFIER_Value                              
input:
     ASN1WorkSpace* ws: data save and work space
	 OBJECTIDENTIFIER* value: will encoding value 
	 ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                    
return:
     ASNINT32: if return 0 succeed else error                                    
description:
     creat encode a value of OBJECT IDENTIFIER struct                                  
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_OBJECTIDENTIFIER_Value(ASN1WorkSpace* ws, OBJECTIDENTIFIER* value, ASNINT32 length);

//ASNINT32 ASN1_BER_Compare_OBJECTIDENTIFIER(OBJECTIDENTIFIER* Com_one,OBJECTIDENTIFIER* Com_two);

#endif /*_ASN_ROID_H_*/


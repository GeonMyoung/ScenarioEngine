#ifndef ASN_BER_INTEGER_H
#define ASN_BER_INTEGER_H

#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"
#include "../TYPE/ASN1_Type.h"
#include "../TOOL/Infinite_tool.h"

/************************************************
function_name:ASN1_BER_Enc_INTEGER_OSINT64	                              
input:
ASN1WorkSpace* ws: data save and work space
INTEGER value: will encoding value 
ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                    
return:
ASNINT32: if return 0 succeed else error                                    
description:
creat encode a value of INTEGER and Tag Length                                 
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_INTEGER(ASN1WorkSpace *ws,INTEGER *Tvalue,ASN1TagType flag);



/************************************************
function_name:ASN1_BER_Enc_INTEGER_OSUINT8	                              
input:
ASN1WorkSpace* ws: data save and work space
ASNUINT8 *value: will encoding value 
ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                    
return:
ASNINT32: if return 0 succeed else error                                    
description:
creat encode a value of big INTEGER and Tag Length                                 
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_INTEGER_OSUINT8(ASN1WorkSpace *ws,ASNUINT8 *value,ASN1TagType flag);



/************************************************
function_name:ASN1_BER_Dec_INTEGER_OSINT64	                              
input:
ASN1WorkSpace* ws: data save and work space
INTEGER *value: will encoding value   
ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                 
return:
ASNINT32: if return 0 succeed else error                                    
description:
decode ws and put the result into value(INTEGER)                                
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_INTEGER(ASN1WorkSpace *ws,INTEGER *value,ASNINT32 length,ASN1TagType flag);




/************************************************
function_name:ASN1_BER_Dec_INTEGER_OSUINT8	                              
input:
ASN1WorkSpace* ws: data save and work space
ASNUINT8 *value: will encoding value   
ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                 
return:
ASNINT32: if return 0 succeed else error                                    
description:
decode ws and put the result into value(big INTEGER)                                 
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_INTEGER_OSUINT8(ASN1WorkSpace *ws,ASNUINT8 *value,ASNINT32 length,ASN1TagType flag);



/************************************************
function_name:ASN1_BER_Enc_INTEGER_OSINT64_Value	                              
input:
ASN1WorkSpace* ws: data save and work space
INTEGER value: will encoding value 
return:
ASNINT32: if return 0 succeed else error                                    
description:
creat encode a value of INTEGER                                 
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_INTEGER_Value(ASN1WorkSpace *ws,INTEGER *tvalue);



/************************************************
function_name:ASN1_BER_Enc_INTEGER_OSINT64_Value	                              
input:
ASN1WorkSpace* ws: data save and work space
ASNUINT8 *value: will encoding value 
return:
ASNINT32: if return 0 succeed else error                                    
description:
creat encode a value of INTEGER                                 
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_INTEGER_OSUINT8_Value(ASN1WorkSpace *ws,ASNUINT8 *Tvalue);




/************************************************
function_name:ASN1_BER_Dec_INTEGER_OSINT64_Value	                              
input:
ASN1WorkSpace* ws: data save and work space
INTEGER value: will encoding value   
ASNUINT32L length: decode length                               
return:
ASNINT32: if return 0 succeed else error                                    
description:
decode ws and put the result into value                                
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_INTEGER_Value(ASN1WorkSpace *ws,INTEGER* value,ASNINT32 length);



/************************************************
function_name:ASN1_BER_Dec_INTEGER_OSUINT8_Value	                              
input:
ASN1WorkSpace* ws: data save and work space
ASNUINT8 *value: will encoding value (big INTEGER)  
ASNUINT32L length: decode length                               
return:
ASNINT32: if return 0 succeed else error                                    
description:
decode ws and put the result into value(big INTEGER)                                 
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_INTEGER_OSUINT8_Value(ASN1WorkSpace *ws,ASNUINT8 *value,ASNUINT32L length);


#endif


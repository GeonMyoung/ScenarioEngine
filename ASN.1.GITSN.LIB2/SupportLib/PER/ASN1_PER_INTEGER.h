#ifndef ASN_PER_INTEGER_H
#define ASN_PER_INTEGER_H

#include "../OS/ASN1_Sys.h"
#include "../IO/ASN1_WorkSpace.h"
#include "../TOOL/ASN1_Tag.h"
#include "../TOOL/ASN1_Length.h"
#include "../TOOL/ASN1_Operate_Byte.h"
#include "../TYPE/ASN1_Type.h"

//#include "../Tool/Infinite_tool.h"

/************************************************
function_name:ASN1_PER_Enc_UnConsInteger	                              
input:
ASN1WorkSpace* ws: save data and other parameters in this workspace
ASNINT32 value: the value that will be encoded  
return:
ASNINT32: if return 0 succeed else error                                    
description:
encode Tag,Length and the value of int                                
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_PER_Enc_UnConsINTEGER(ASN1WorkSpace * ws, INTEGER *tvalue,ASNUINT8 *enc_value);



/************************************************
function_name:ASN1_PER_Dec_UnConsInteger	                              
input:
ASN1WorkSpace* ws: save data and other parameters in this workspace
ASNINT32 *value: the value that will be decoded   
return:
ASNINT32: if return 0 succeed else error                                    
description:
decode Tag,Length and the value of int from ws and put the result into value                                 
*************************************************/
/*ASNINT32 ASN1_PER_Dec_UnConsInteger(ASN1WorkSpace* ws, ASNINT64 *value);*/



ASN1_CPPLINK ASNINT32 ASN1_PER_Dec_INTEGER_Value(ASNUINT8 *decvalue,INTEGER *value,ASNINT32 length,ASNUINT8 negativeflag);


ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_INTEGER(ASN1WorkSpace * ws, INTEGER *tvalue, 
							  Asn1ConsInfo *conss);


							  
ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_INTEGER(ASN1WorkSpace * ws, INTEGER *tvalue, 
							  Asn1ConsInfo *conss);

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_INTEGER(ASN1WorkSpace * ws, INTEGER *value, 
							  Asn1ConsInfo *conss);
							  

							  
ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_INTEGER(ASN1WorkSpace * ws, INTEGER *value, 
							  Asn1ConsInfo *conss);

#endif




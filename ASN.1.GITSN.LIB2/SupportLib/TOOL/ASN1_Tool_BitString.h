#ifndef _BITSTRING_Tool_H_
#define _BITSTRING_Tool_H_

#include "OS/ASN1_Sys.h"
#include "TYPE/ASN1_Type.h"
#include "IO/ASN1IO.h"


/************************************************
function_name:HexToBitString	                              
input:
const ASNUINT8 *value:Hex string 
BITSTRING *bitValue:convert to value (bit string struct)
return: ASNINT32                                   
description:
convert Hex string to bit string                                 
*************************************************/
ASN1_CPPLINK ASNINT32 HexToBitString(ASN1WorkSpace* ws,const ASNUINT8 *value,BITSTRING *bitValue);


/************************************************
function_name:BitToBitString	                              
input:
const ASNUINT8 *value:Bit string 
BITSTRING *bitValue:convert to value (bit string struct)
return: ASNINT32                                   
description:
convert Bit string to bit string             
for example:
"1111000000B" to BitString                    
*************************************************/
ASN1_CPPLINK ASNINT32 BitToBitString(ASN1WorkSpace* ws,const ASNUINT8 *value,BITSTRING *bitValue);



/************************************************
function_name:BitStringToHex	                              
input:
BITSTRING bitValue:Bit string 
ASNUINT8 **value:convert to value (bit string struct)
return: ASNINT32                                   
description:
convert Bit string to Hex string                                 
*************************************************/
ASN1_CPPLINK ASNINT32 BitStringToHex(ASN1WorkSpace* ws,BITSTRING bitValue,ASNUINT8 **value);


/************************************************
function_name:BitStringToBit	                              
input:
BITSTRING bitValue:Bit string 
ASNUINT8 **value:convert to value 
return: ASNINT32                                   
description:
convert Bit string to Bit string     
for example:
BitString to "1111000000B"                             
*************************************************/
ASN1_CPPLINK ASNINT32 BitStringToBit(ASN1WorkSpace* ws,BITSTRING bitValue,ASNUINT8 **value);


/************************************************
function_name:CheckHexString	                              
input:
const ASNUINT8 *value:check Hex String
return: ASNINT32                                   
description:
check valid Hex String                         
*************************************************/
ASN1_CPPLINK ASNINT32 CheckHexString(const ASNUINT8 *value);


/************************************************
function_name:CheckBitString	                              
input:
const ASNUINT8 *value:check Bit String
return: ASNINT32                                   
description:
check valid Bit String                         
*************************************************/
ASN1_CPPLINK ASNINT32 CheckBitString(const ASNUINT8 *value);

#endif

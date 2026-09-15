#ifndef _ASN1_OPERATE_BYTE_H_
#define _ASN1_OPERATE_BYTE_H_

#include "IO/ASN1_WorkSpace.h"
#include "OS/ASN1_Sys.h"
#include "MEM/ASN1_mpool.h"
#include "TOOL/ASN1_Length.h"



ASN1_CPPLINK ASNINT32 ASN1_BER_FillBuffer(ASN1WorkSpace* ws,ASNUINT8* value,
							 ASNUINT32 length,ASNINT32 offset_value);

ASN1_CPPLINK ASNINT32 ASN1_BER_ReadBuffer(ASN1WorkSpace* ws,ASNUINT8* value,
							 ASNUINT32 length);
/************************************************
function_name:Per_Bit_Save_Process	                              
input:
ASN1WorkSpace* ws:
ASNUINT8* encode:
return: ASNINT32                                   
description:
                               
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_FillBuffer(ASN1WorkSpace* ws,ASNUINT8* value,
						 ASNUINT32 length,ASN1PERAlign prefill);


/************************************************
function_name:Per_Bit_Load_Process	                              
input:
ASN1WorkSpace* ws:
ASNUINT8* encode:
return: ASNINT32                                   
description:
                               
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_ReadBuffer(ASN1WorkSpace* ws,ASNUINT8* value,
						 ASNUINT32 length,ASN1PERAlign prefill);



/************************************************
function_name:Per_Bit_Save_Process	                              
input:
ASN1WorkSpace* ws:
ASNUINT8* encode:
return: ASNINT32                                   
description:
                               
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_XER_FillBuffer(ASN1WorkSpace* ws,ASNUINT8* value,
							 ASNUINT32 length);


/************************************************
function_name:Per_Bit_Load_Process	                              
input:
ASN1WorkSpace* ws:
ASNUINT8* encode:
return: ASNINT32                                   
description:
                               
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_XER_ReadBuffer(ASN1WorkSpace* ws,ASNUINT8* value,
							 ASNUINT32 length);

/************************************************
function_name:Per_Bit_Load_Process	                              
input:
ASN1WorkSpace* ws:
ASNUINT8* encode:
return: ASNINT32                                   
description:
                               
*************************************************/
ASN1_CPPLINK ASNINT32 Bit_Fill_Process(ASNUINT8** encode,ASNUINT8* value,
						  ASNUINT32 length,ASN1WorkSpace* ws);

/************************************************
function_name:Per_Bit_Load_Process	                              
input:
ASN1WorkSpace* ws:
ASNUINT8* encode:
return: ASNINT32                                   
description:
                               
*************************************************/
ASN1_CPPLINK ASNINT32 Bit_Read_Process(ASNUINT8* encode,ASNINT32 ebit,
						  ASNINT32 ebyte,ASNUINT32 length);

/************************************************
function_name:Per_Bit_Load_Process	                              
input:
ASN1WorkSpace* ws:
ASNUINT8* encode:
return: ASNINT32                                   
description:
                               
*************************************************/
ASN1_CPPLINK ASNINT32 reset_memony(ASN1WorkSpace *ws);
ASN1_CPPLINK ASNINT32 Compare_Letter(ASNINT32 table_count,ASNINT8* Compare_string);	// tab == 0 || is_upper(str[0]) then TRUE

#endif /*_ASN1_OPERATE_BYTE_H_*/


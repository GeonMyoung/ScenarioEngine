#ifndef ASN1_TAG_H_
#define ASN1_TAG_H_

#include "OS/ASN1_Sys.h"
#include "IO/ASN1_WorkSpace.h"
#include "TOOL/ASN1_Length.h"


#define ITS_ASN_UNIV   0x00000000
#define ITS_ASN_APPL   0x40000000
#define ITS_ASN_CONT   0x80000000
#define ITS_ASN_PRIV   0xc0000000

#define ITS_ASN_PRIM   0x00000000
#define ITS_ASN_CONS   0x20000000

#define ITS_ASN_NUMBER 0x1fffffff //get value
#define ITS_ASN_LTABLE 0xc0000000 //get class value
#define ITS_ASN_PRCON  0x20000000 //get c/s 

/*
#define ASN1_TAG_univ   0x00000000
#define ASN1_TAG_appl   0x40000000
#define ASN1_TAG_cont   0x80000000
#define ASN1_TAG_priv   0xc0000000

#define ASN1_TAG_prim   0x00000000
#define ASN1_TAG_cons   0x20000000

#define ASN1_TAG_number 0x1fffffff //get value
#define ASN1_TAG_ltable 0xc0000000 //get class value
#define ASN1_TAG_prcon  0x20000000 //get c/s 
*/

/************************************************
function_name:ASN1_BER_Enc_Tag_Indef                              
input:
     ASN1WorkSpace* ws: data save and work space
	 ASN1_Type_Info* info: encoding and decoding information struct                                    
return:
     ASMVoid: no return value                                
description:
     encode a tag                                   
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_Tag_Indef(ASN1WorkSpace * ws,ASNUINT32 tag_value);//encoding true tag 

/************************************************
function_name:ASN1_BER_Enc_Tag_Indef                              
input:
     ASN1WorkSpace* ws: data save and work space
	 ASNUINT32 tag_value: encoding value                                    
return:
     ASMVoid: no return value                                
description:
     encoding tag(ture process)                                
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Process_Tag(ASN1WorkSpace * ws, ASNUINT32 tag_value);//tag process function

/************************************************
function_name:ASN1_BER_Enc_Tag_Indef                              
input:
     ASNUINT32 tagvalue:encode value
	 ASNUINT8* tag_class: frist tag value                                   
return:
     ASMVoid: no return value                                
description:
     encode tag class and c/s                               
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Process_Tag_Class(ASNUINT32 tagvalue ,ASNUINT8* tag_class);//tag class process function

/************************************************
function_name:ASN1_Dec_Tag_Value                              
input:
     ASN1WorkSpace* ws: data save and work space                                
return:
     ASMVoid: no return value                                
description:
     decode tag                              
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_Dec_Tag_Value(ASN1WorkSpace * ws);

/************************************************
function_name:ASN1_Dec_Tag_Indef                              
input:
      ASN1WorkSpace* ws: data save and work space                                  
return:
     ASMVoid: no return value                                
description:
     decode tag and indef                              
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_Dec_Tag_Indef(ASN1WorkSpace * ws,unsigned char* Temp_Tag);
/************************************************
function_name:ASN1_Tag_Move_Pointer                              
input:
     ASN1WorkSpace* ws:data save and work space 
	 ASNUINT8 tag_class: tag value
	 ASN1TagType flag:tag type
return:
     ASNINT32: if value=0 succeed else error                               
description:
     if flag = ASN1IMPL move pointer                               
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_Tag_Move_Pointer(ASN1WorkSpace* ws,ASNUINT32 tag_value, ASN1TagType flag);

/************************************************
function_name:ASN1_Dec_Tag_Compare                              
input:
     ASN1WorkSpace* ws:data save and work space 
	 ASNUINT8 tag_class: tag value
	 ASN1TagType flag:tag type
return:
     ASNINT32: if value=0 succeed else error                               
description:
     if flag = ASN1IMPL move pointer                               
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_Dec_Tag_Compare(ASN1WorkSpace* ws,ASNUINT32 tagValue,ASNUINT8 *TagClass);

/*ASNINT32 ASN1_Dec_Tag_Process_Inside(ASN1WorkSpace* ws);*/

/************************************************
function_name:ASN1_BER_Dec_User_Tag                              
input:
     ASN1WorkSpace* ws:data save and work space 
	 ASNUINT8 tag_class: tag value
	 ASN1TagType flag:tag type
return:
     ASNINT32: if value=0 succeed else error                               
description:
     if flag = ASN1IMPL move pointer                               
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_User_Dec_Tag(ASN1WorkSpace* ws,ASNINT32 tagvalue);

/************************************************
function_name:ASN1_BER_Dec_Tag                              
input:
     ASN1WorkSpace* ws:data save and work space 
	 ASNUINT8 tag_class: tag value
	 ASN1TagType flag:tag type
return:
     ASNINT32: if value=0 succeed else error                               
description:
     if flag = ASN1IMPL move pointer                               
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_Tag(ASN1WorkSpace*ws,ASNINT32 tagvalue);


/************************************************
function_name:ASN1_BER_GET_Tag                              
input:
     ASN1WorkSpace* ws:data save and work space 
	 ASNUINT32* Tagvalue: tag value	 
return:
     ASNINT32: if value=0 succeed else error                               
description:
     Get Tag value no move pointer                               
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_GET_Tag(ASN1WorkSpace *ws,ASNUINT32* Tagvalue);


/************************************************
function_name:ASN1_BER_OpenType_Tag                              
input:
     ASN1WorkSpace* ws:data save and work space 
return:
     ASNINT32: if value=0 succeed else error                               
description:
     decode opentype tag                               
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_OpenType_Tag(ASN1WorkSpace *ws);

#endif /*ASN1_TAG_H_*/


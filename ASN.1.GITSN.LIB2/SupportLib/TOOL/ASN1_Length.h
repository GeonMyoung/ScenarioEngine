#ifndef ASN_LENGTH_H_
#define ASN_LENGTH_H_



#include "OS/ASN1_Sys.h"
#include "IO/ASN1_WorkSpace.h"
#include "TOOL/ASN1_Tag.h"
#include "TYPE/ASN1_Type.h"



typedef struct save_length_node{
	ASNINT32  T_len;
	ASNUINT8* L_place;
	ASNINT32  L_vlen;
	ASNINT32  L_indef; //indefine 
	ASNINT32  L_shift; //length
	ASNINT32  Is_cORp;    //cons or prim
	struct save_length_node* next;
}save_length_node;

typedef struct save_length_list{
    ASNINT32  node_number;
	save_length_node* head;
	save_length_node* current;
}save_length_list;



/************************************************************************
* Name: ASN_BER_Enc_Length											
* Function: encode length value 
* Input: 
*    ws:data save and work space 
*    length:encode value 's length			
* Output: return flag(0-success,1-false)										
************************************************************************/
ASN1_CPPLINK ASNINT32 ASN_BER_Enc_Length(ASN1WorkSpace *ws,ASNUINT32L length);

/************************************************************************
* Name: ASN_BER_Dec_Length											
* Function: decode length value 
* Input: 
*    ws:data save and work space 			
* Output: return flag(0-success,1-false)										
************************************************************************/
ASN1_CPPLINK ASNINT32 ASN_BER_Dec_Length(ASN1WorkSpace *ws);


/************************************************************************
* Name: ASN1_BER_User_Dec_Length											
* Function: decode User length value 
* Input: 
*    ws:data save and work space 
*    length:get length value			
* Output: return flag(0-success,1-false)										
************************************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_User_Dec_Length(ASN1WorkSpace *ws,ASNINT32* length);


/************************************************************************
* Name: ASN_BER_Enc_StrmEOC											
* Function: encode end add OO
* Input: 
*    ws:data save and work space			
* Output: return flag(0-success,1-false)										
************************************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_StrmEOC(ASN1WorkSpace *ws);


/************************************************************************
* Name: ASN_BER_Dec_Length											
* Function: decode end sub OO
* Input: 
*    ws:data save and work space			
* Output: return flag(0-success,1-false)										
************************************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_StrmEOC(ASN1WorkSpace *ws);



/************************************************************************
* Name: ASN_BER_Dec_Isloop											
* Function: Check loop end falg
* Input: 
*    ws:data save and work space
*    position:ws.buffer.current pointer
*    length:value length		
* Output: return flag(0-success,1-false)										
************************************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_Isloop(ASN1WorkSpace *ws,ASNUINT8* position,ASNINT32 length);


/************************************************************************
* Name: IfFixedLength											
* Function: Check Fixed Length or 0x80 ?
* Input: 
*    length:data length			
* return: return length(-1---0x80,else actual length)										
************************************************************************/
ASN1_CPPLINK ASNINT32 IfFixedLength(ASNINT32 length);


/************************************************************************
* Name: GetDataLength											
* Function: Get buffer data length
* Input: 
*    ws:data save and work space			
* return: return flag(0-success,1-false)										
************************************************************************/

ASN1_CPPLINK ASNINT32 GetDataLength(ASN1WorkSpace *ws);




/************************************************************************
* Name: GetIndefiniteToLength											
* Function: Will first length, Indefinite change to defineLen
* Input: 
*    ws:data save and work space	
*	  newws:data save and work space			
* return: return flag(0-success,1-false)										
************************************************************************/
ASN1_CPPLINK ASNINT32 GetIndefiniteToLength(ASN1WorkSpace *ws,ASN1WorkSpace *newws);


/************************************************************************
* Name: IndefinelenTodefinelen											
* Function: Will all length, Indefinite change to defineLen
* Input: 
*    ws:data save and work space			
* return: return flag(0-success,1-false)										
************************************************************************/

ASN1_CPPLINK ASNINT32 IndefinelenTodefinelen(ASN1WorkSpace *ws);


/************************************************************************
* Name: Init_Len_SLenList											
* Function: Init printf surveyor's staff list
* Input: 
*    ws:data save and work space
*    LenS:list pointer		
* return: return flag(0-success,1-false)										
************************************************************************/
ASN1_CPPLINK ASNINT32 Init_Len_SLenList(ASN1WorkSpace *ws,save_length_list* LenS);



/************************************************************************
* Name: Creat_Len_Init_List											
* Function: Creat printf surveyor's staff list
* Input: 
*    	pointer:list pointer		
* return: return flag(0-success,1-false)										
************************************************************************/
ASN1_CPPLINK ASNINT32 Creat_Len_Init_List(save_length_list *pointer);


/************************************************************************
* Name: Insert_Len_Node											
* Function: Insert node to printf surveyor's staff list
* Input: 
*    pointer:list pointer
*	  data:node pointer			
* return: return flag(0-success,1-false)										
************************************************************************/
ASN1_CPPLINK ASNINT32 Insert_Len_Node(save_length_list *pointer ,save_length_node** data);


/************************************************************************
* Name: Delete_Len_Node											
* Function: Delete list node
* Input: 
*    pointer:list pointer			
* return: return flag(0-success,1-false)										
************************************************************************/
ASN1_CPPLINK ASNINT32 Delete_Len_Node(save_length_list *pointer);


/************************************************************************
* Name: Destroy_Len_List											
* Function: Destroy list
* Input: 
*    pointer:list pointer			
* return: return flag(0-success,1-false)										
************************************************************************/
ASN1_CPPLINK ASNINT32 Destroy_Len_List(save_length_list *pointer);


/************************************************************************
* Name: Change_Len											
* Function: Change Len Encode
* Input: 
*    length:value length			
* return: Len Encode										
************************************************************************/
ASN1_CPPLINK ASNINT32 Change_Len(ASNUINT64 length);


/************************************************************************
* Name: Indef_Change_def											
* Function:make node of printf surveyor's staff list 
* Input: 
*    ws:data save and work space	
*    LenS:list pointer		
* return: return flag(0-success,1-false)										
************************************************************************/
ASN1_CPPLINK ASNINT32 Indef_Change_def(ASN1WorkSpace *ws,save_length_list* LenS);



ASN1_CPPLINK ASNINT32 ASN1_PER_Enc_intUnConsLength(ASN1WorkSpace * ws, ASNUINT32 *length);

ASN1_CPPLINK ASNINT32 ASN1_PER_Enc_intConsLength(ASN1WorkSpace * ws, ASNUINT64 *value, Asn1ConsInfo *conss);
/*
ASNINT32 ASN1_Compute_EnumElement(ASNUINT8 *StringForEnum);
ASNINT64 ASN1_Compute_IntElement(ASNUINT8 *StringForInt);
*/
ASN1_CPPLINK ASN1ConsCheck String_to_CheckStruct(ASNUINT8 **StringDealwith, ASNSTRING *DefaultAlphabet);
ASN1_CPPLINK ASNINT32 GetDataLength_Per(ASN1WorkSpace *ws);

ASN1_CPPLINK ASNINT32 ASN1_Dec_EXT_UNKnow(ASN1WorkSpace *ws);

ASN1_CPPLINK ASNINT32 ASN1_Dec_Seq_EXT_UNKnow(ASN1WorkSpace *ws,ASNUINT8 *pointer,ASNINT32 lenght);

ASN1_CPPLINK ASNINT32 ASN1_BER_IsWSrange(ASN1WorkSpace *ws, ASNINT32 byte_size);

ASN1_CPPLINK ASNINT32 ASN1_PER_IsWSrange(ASN1WorkSpace *ws, ASNUINT32 byte_size);

ASN1_CPPLINK ASNINT32 ASN1_XER_IsWSrange(ASN1WorkSpace *ws, ASNINT32 byte_size);

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_Length(ASN1WorkSpace *ws,ASNUINT32L length);

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_Length(ASN1WorkSpace *ws);


#endif /*ASN_LENGTH_H_*/




#ifndef _ASN1List_H_
#define _ASN1List_H_

#include "OS/ASN1_Sys.h"
#include "IO/ASN1_WorkSpace.h"
#include "MEM/ASN1_mpool.h"

typedef struct ASN1ListNode    //node struct
{ 
   void					*data;            
   struct ASN1ListNode	*next; 
   struct ASN1ListNode	*prev; 
} ASN1ListNode;

typedef struct ASNList  //list struct
{
   ASNUINT32	 count;   
   ASNUINT8		 search_flag;
   ASN1ListNode *search;
   ASN1ListNode *head;        
   ASN1ListNode *tail;        
} ASN1List;

/************************************************
function_name:ASN1_Creat_Init_List                              
input:
     ASN1WorkSpace* workspace:data save and work space 
	 ASNList *pointer:list pointer
return:
     ASNINT32: if value=0 succeed else error                               
description:
     Create and init list                               
*************************************************/
ASN1_CPPLINK ASNINT32	 ASN1_Creat_Init_List(ASN1WorkSpace* workspace,ASN1List *pointer); //creat and init list
#define					 ASN1List_init					ASN1_Creat_Init_List

/************************************************
function_name:ASN1_Insert_Node                              
input:
     ASN1WorkSpace* workspace:data save and work space 
	 ASNList *pointer:list pointer
	 ASNVoid* data:insert data to list 
return:
     ASNINT32: if value=0 succeed else error                               
description:
     insert data to list                                
*************************************************/
ASN1_CPPLINK ASNINT32	 ASN1_Insert_Node(ASN1WorkSpace* workspace,ASN1List *pointer ,ASNVoid* data); //creat and insert node
#define					 ASN1List_insert				ASN1_Insert_Node

/************************************************
function_name:ASN1_Get_Node_Index                              
input:
	 ASNList *pointer:list pointer
	 ASNINT32 count:Get node number from list 
return:
     ASNINT32: if value=0 succeed else error                               
description:
     Get node data from list                                
*************************************************/
ASN1_CPPLINK ASNVoid	*ASN1_Get_Node_Index(ASN1List *pointer,ASNINT32 count); //search node
#define					 ASN1List_getByIdx				ASN1_Get_Node_Index

/************************************************
function_name:ASN1_Get_Node                   
input:
	 ASNList *pointer:list pointer
	 ASNINT32 count:Get node number from list 
return:
     ASNINT32: if value=0 succeed else error                               
description:
     Get node data from list                                
*************************************************/
ASN1_CPPLINK ASNVoid	*ASN1_Get_Node(ASN1List *pointer);			// search node
ASN1_CPPLINK ASNVoid	*ASN1_Get_Node_First(ASN1List *pointer);	// search first node
#define					 ASN1_Get_Node_Next				ASN1_Get_Node

#define					 ASN1List_getFirst				ASN1_Get_Node_First
#define					 ASN1List_getNext				ASN1_Get_Node_Next

/************************************************
function_name:ASN1_Delete_Node                              
input:
	 ASNList *pointer:list pointer
return:
     ASNINT32: if value=0 succeed else error                               
description:
     delete node from list                                
*************************************************/
ASN1_CPPLINK ASNINT32	 ASN1_Delete_Node(ASN1List *pointer); //delete node
#define					 ASN1List_remove						ASN1_Delete_Node

ASN1_CPPLINK ASNINT32	 ASN1_Destroy_List(ASN1List *pointer); //destroy list
#define					 ASNList_empry						ASN1_Destroy_List

ASN1_CPPLINK ASNINT32	 ASN1_Get_List_Length(ASN1List *pointer);
#define					 ASN1List_count						ASN1_Get_List_Length

#endif /*_ASN1List_H_*/


/*
  Name: ASN1List.c
  Copyright: 
  Author: fanyapeng
  Date: 22-04-08 09:53
  Description: list operator function source file
*/


#include "ASN1_List.h"

ASNINT32 ASN1_Creat_Init_List(ASN1WorkSpace *workspace, ASN1List *pointer) //creat and init list
{
	/**pointer = (ASN1List*)malloc(sizeof(ASN1List));*/
	if (workspace==NULL || pointer == NULL){
		return -30;
	}
	pointer->head = (ASN1ListNode *)mpool_malloc(workspace->Pmemory, sizeof(ASN1ListNode));
	if ((NULL == pointer) || (NULL == pointer->head))
	{
		//printf("Assign Memory Error\n");
		return -31;
	}
	pointer->search_flag = 0;
	pointer->tail = pointer->head;
	pointer->search = pointer->head;
	pointer->count = 0;
	pointer->tail->data=NULL;
	pointer->tail->next=NULL;
	pointer->tail->prev=NULL;

	return 0;
}

ASNINT32 ASN1_Insert_Node(ASN1WorkSpace *workspace, ASN1List *pointer ,ASNVoid *data) //creat and insert node
{
	ASN1ListNode* F_Vd_ListNode_Insert; //insert node pointer 
	if (workspace == NULL || pointer == NULL || data == NULL) return -32;

	if (pointer->head == NULL && pointer->tail == NULL)
	{
		int status = ASN1_Creat_Init_List(workspace, pointer);
		if (status != 0) return status;
	}

	//creat insert node
	if ((F_Vd_ListNode_Insert = (ASN1ListNode*)mpool_malloc(workspace->Pmemory,sizeof(ASN1ListNode) )) == NULL) return -33;

	F_Vd_ListNode_Insert->data = data; //init node
	F_Vd_ListNode_Insert->next = NULL;
	F_Vd_ListNode_Insert->prev = NULL;
	pointer->search_flag = 0;

	F_Vd_ListNode_Insert->next = pointer->tail->next;	/*will new node set last*/
	pointer->tail->next = F_Vd_ListNode_Insert;			/*last node point to new node*/
	F_Vd_ListNode_Insert->prev = pointer->tail;			/*new node point to previous node*/

	pointer->tail = pointer->tail->next;				/*reset tail pointer*/

	pointer->count++;/*node count add*/

	return 0;
}

ASNVoid *ASN1_Get_Node_Index(ASN1List *pointer, ASNINT32 count) /*search node*/
{
	ASN1ListNode* F_Vd_Temp_Get_Node;
	if (pointer == NULL) return NULL;
	if (0 == pointer->count) return NULL;

	F_Vd_Temp_Get_Node = pointer->head;
	F_Vd_Temp_Get_Node = F_Vd_Temp_Get_Node->next;

	if (0 >= count) return NULL;

	while(count > 1)
	{
		F_Vd_Temp_Get_Node = F_Vd_Temp_Get_Node->next;
		count--;
	}

	return (F_Vd_Temp_Get_Node->data);
}

ASNVoid *ASN1_Get_Node(ASN1List *pointer)	/*search node*/
{
	ASN1ListNode* F_Vd_Temp_Get_Node;
	if (pointer == NULL) return NULL;
	if (0 == pointer->count) return NULL;

	if (pointer->search_flag == 0)
	{
		pointer->search = pointer->head->next;
		pointer->search_flag = 1;
	}

	if (pointer->search != NULL)
	{
		F_Vd_Temp_Get_Node = pointer->search;
		pointer->search = pointer->search->next;
		return (F_Vd_Temp_Get_Node->data);
	}

	return NULL;
}

ASNVoid *ASN1_Get_Node_First(ASN1List *pointer)	/*search first node*/
{
	if (pointer == NULL) return NULL;
	if (0 == pointer->count) return NULL;

	pointer->search_flag = 0;
	return ASN1_Get_Node(pointer);
}

ASNINT32 ASN1_Delete_Node(ASN1List *pointer) //delete node
{
	ASN1ListNode* F_Vd_Temp_Del_Node;

	F_Vd_Temp_Del_Node	= pointer->tail;
	pointer->tail		= pointer->tail->prev;
	pointer->tail->next = F_Vd_Temp_Del_Node->next;

	if (NULL != pointer->tail->next) F_Vd_Temp_Del_Node->next->prev = pointer->tail;

	/*free(F_Vd_Temp_Del_Node);*/

	pointer->count--;
	return 0;
}

ASNINT32 ASN1_Get_List_Length(ASN1List *pointer)
{
	return pointer->count;
}

ASNINT32 ASN1_Destroy_List(ASN1List *pointer)
{
	if (pointer != NULL)
	{
		while (0 != pointer->count)
			ASN1_Delete_Node(pointer);

		//free(pointer->head);
		free(pointer);
	}
	return 0;
}





#include "ASN1_WorkSpace.h"
#define WORKSPACE_MEM_SIZE 4096
ASNINT32 ASN1_INIT_WS_INFO(ASN1WorkSpace* workspace)
{
	if (workspace == NULL)
	{
		return -49;
	}

	(workspace->Pmemory) = new_mpool(5120);

	/**workspace = mpool_malloc((*p),sizeof(ASN1WorkSpace));*/

	(workspace)->buffer.data = mpool_malloc((workspace->Pmemory),WORKSPACE_MEM_SIZE);
	memset(workspace->buffer.data,'\0',WORKSPACE_MEM_SIZE);

	workspace->buffer.current = workspace->buffer.data;
	workspace->buffer.openType = NULL;
	workspace->buffer.bitOffset = 8;
	workspace->buffer.end = workspace->buffer.data+WORKSPACE_MEM_SIZE;
	workspace->buffer.Vdeocd_valid = workspace->buffer.end;

	workspace->iscons = 0;

	/*workspace->Pmemory = *p;*/
    //return workspace;
	return 0;
}
ASN1_CPPLINK ASNINT32 ASN1_RESET_WS_POINET(ASN1WorkSpace* workspace)
{
	workspace->buffer.current = workspace->buffer.data;
	workspace->buffer.bitOffset = 8;
	return 0;
}
//ASN1_CPPLINK ASNINT32 ASN1_RESET_WS_INFO(ASN1WorkSpace *workspace, ASNUINT32 buflenth)
ASN1_CPPLINK ASNINT32 ASN1_RESET_WS_INFO(ASN1WorkSpace *workspace, ASNUINT32 newSize)
{
//	ASNINT32 current_place;
//	ASNINT32 all_length;
//	current_place = workspace->buffer.current - workspace->buffer.data;
//	all_length = workspace->buffer.end - workspace->buffer.data;
//	buflenth = (buflenth / 8 + 1) * 8;
//	workspace->buffer.data = mpool_realloc(workspace->Pmemory, workspace->buffer.data, all_length + buflenth);
//	memset((workspace->buffer.data) + current_place, 0x00, all_length + buflenth - current_place);
//	workspace->buffer.current = workspace->buffer.data + current_place;
//	workspace->buffer.end = workspace->buffer.data + all_length+buflenth;
//	workspace->buffer.Vdeocd_valid = workspace->buffer.end;
	
	ASNUINT32 data_size = (ASNUINT32)(workspace->buffer.current - workspace->buffer.data);
	ASNUINT32 fullSize = (ASNUINT32)(workspace->buffer.end - workspace->buffer.data);

	newSize = (newSize / 8 + 1) * 8; // align 8 byte

	workspace->buffer.data = mpool_realloc(workspace->Pmemory, workspace->buffer.data, newSize);
	memset((workspace->buffer.data) + fullSize, 0x00, newSize - fullSize);

	workspace->buffer.current = workspace->buffer.data + data_size;
	workspace->buffer.end = workspace->buffer.data + newSize;
	workspace->buffer.Vdeocd_valid = workspace->buffer.end;

	return 0;
}

ASNINT32 ASN1_Destroy_WORKSPACE(ASN1WorkSpace *ws)
{
	if (ws == NULL)
	{
		return -50;
	}
	free_mpool(ws->Pmemory);
	return 0;
}

struct mpool* GetMemPool(ASN1WorkSpace* ws)
{
	return ws->Pmemory;
}

ASN1_CPPLINK ASNINT32 ASN1_CLEAR_WORKSPACE(ASN1WorkSpace* workspace)
{
	if (NULL == workspace){
		return -51;
	}

	memset(workspace->buffer.data,'\0',
		(workspace->buffer.end - workspace->buffer.data));
	
	workspace->buffer.current = workspace->buffer.data;
	workspace->buffer.Vdeocd_valid = workspace->buffer.end;
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_Get_Length_WORKSPACE(ASN1WorkSpace* workspace,ASNINT32* length)
{
	*length = workspace->buffer.current - workspace->buffer.data;
	return 0;
}

ASN1_CPPLINK ASNUINT8* ASN1_Get_Current_Pointer_WORKSPACE(ASN1WorkSpace* workspace)
{
	if (workspace == NULL){
		return NULL;
	}
	return workspace->buffer.current;
}

ASNINT32 ASN1_Save_WORKSPACE(ASN1WorkSpace *workspace, ASNUINT8 *save, ASNINT32 length)	/*mem to workspace*/
{
	if (workspace == NULL) return -52;
	else if (length < 0) return -53;
	else
	{
		if(workspace->buffer.end - workspace->buffer.data < length) ASN1_RESET_WS_INFO(workspace,length);	// realloc buffer area

//		memset(workspace->buffer.data, 0, length);
		memcpy(workspace->buffer.data, save, length);

		workspace->buffer.current = workspace->buffer.data;
		workspace->buffer.bitOffset = 8;
		workspace->buffer.Vdeocd_valid = workspace->buffer.data + length;
		return 0;
	}
}

ASN1_CPPLINK ASNINT32 ASN1_Load_WORKSPACE(ASN1WorkSpace* workspace,ASNUINT8** load,ASNINT32 *length)
{
	if (NULL == workspace || load==NULL|| length == NULL){
		return -54;
	}
	*load = malloc(workspace->buffer.end - workspace->buffer.data);
	memset(*load,0,workspace->buffer.end - workspace->buffer.data);
	memcpy(*load,workspace->buffer.data,workspace->buffer.end - workspace->buffer.data);
	*length = workspace->buffer.end - workspace->buffer.data;
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_Save_Current_P(ASN1WorkSpace* workspace,ASNUINT8** load)
{
	if(workspace == NULL || load == NULL){
		return -55;
	}
	*load  = workspace->buffer.current;
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_IsValue_valid_WORKSPACE(ASN1WorkSpace* workspace)
{
	ASNUINT8* temp_current = workspace->buffer.current;
	if (workspace->buffer.bitOffset != 8){
		temp_current++;
	}
	if (temp_current>=workspace->buffer.Vdeocd_valid){
		return -56;
	}
	return 1;
}

ASN1_CPPLINK ASNINT32 ASN1_SET_VALUE_VALID_Point(ASN1WorkSpace* workspace)
{
	workspace->buffer.Vdeocd_valid = workspace->buffer.current;
	return 0;
}


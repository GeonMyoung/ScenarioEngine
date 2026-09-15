#ifndef ASN1_WORKSPACE_H_
#define ASN1_WORKSPACE_H_

#include "../MEM/ASN1_mpool.h"
#include "../OS/ASN1_Sys.h"
#include "../TOOL/ASN1_Operate_Byte.h"

ASN1_CPPLINK ASNINT32	 ASN1_INIT_WS_INFO(ASN1WorkSpace *workspace);
ASN1_CPPLINK ASNINT32	 ASN1_RESET_WS_POINET(ASN1WorkSpace *workspace);
ASN1_CPPLINK ASNINT32	 ASN1_RESET_WS_INFO(ASN1WorkSpace *workspace,ASNUINT32 buflenth);
ASN1_CPPLINK ASNINT32	 ASN1_Destroy_WORKSPACE(ASN1WorkSpace *ws);
ASN1_CPPLINK ASNINT32	 ASN1_CLEAR_WORKSPACE(ASN1WorkSpace* workspace);
ASN1_CPPLINK ASNINT32	 ASN1_Get_Length_WORKSPACE(ASN1WorkSpace* workspace,ASNINT32* length);
ASN1_CPPLINK ASNUINT8	*ASN1_Get_Current_Pointer_WORKSPACE(ASN1WorkSpace* workspace); 
ASN1_CPPLINK ASNINT32	 ASN1_Save_WORKSPACE(ASN1WorkSpace *workspace, ASNUINT8 *save, ASNINT32 length);
ASN1_CPPLINK ASNINT32	 ASN1_Load_WORKSPACE(ASN1WorkSpace *workspace, ASNUINT8 **load, ASNINT32 *length);
ASN1_CPPLINK ASNINT32	 ASN1_Save_Current_P(ASN1WorkSpace* workspace,ASNUINT8** load);
ASN1_CPPLINK ASNINT32	 ASN1_IsValue_valid_WORKSPACE(ASN1WorkSpace* workspace);
ASN1_CPPLINK ASNINT32	 ASN1_SET_VALUE_VALID_Point(ASN1WorkSpace* workspace);

ASN1_CPPLINK struct mpool* GetMemPool(ASN1WorkSpace* ws);

#define					 ASN1WorkSpace_INIT							ASN1_INIT_WS_INFO
#define					 ASN1WorkSpace_resetPtrs					ASN1_RESET_WS_POINET
#define					 ASN1WorkSpace_reset						ASN1_RESET_WS_INFO
#define					 ASN1WorkSpace_DESTROY						ASN1_Destroy_WORKSPACE
#define					 ASN1WorkSpace_CLEAR						ASN1_CLEAR_WORKSPACE
#define					 ASN1WorkSpace_write(ws, src, len)			ASN1_Save_WORKSPACE(ws, src, len)
#define					 ASN1WorkSpace_read(ws, dst_alloc, ret_len)	ASN1_Load_WORKSPACE(ws, dst_alloc, ret_len)

#endif /*ASN1_WORKSPACE_H_*/























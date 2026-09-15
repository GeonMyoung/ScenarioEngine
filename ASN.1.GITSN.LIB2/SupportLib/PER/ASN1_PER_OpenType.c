#include "ASN1_PER_OpenType.h"

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_OpenType(ASN1WorkSpace *ws,OpenType *value)
{
	ASNINT8 ch=0;
	ASNUINT32 m_l;
	ASNUINT32 m_cl;
	ASNINT32 count;
	count = ws->buffer.current-ws->buffer.data+1;
	ASN1_ReadBuffer(ws,&ch,8,ALIGN);
	ASN1_FillBuffer(ws,value->data,value->numocts*8,ALIGN);
	if (ws->buffer.end <= ws->buffer.current+value->numocts)
	{
		m_l = ws->buffer.current-ws->buffer.data;
		m_cl = ws->buffer.end - ws->buffer.data;
		ws->buffer.data = mpool_realloc(ws->Pmemory,ws->buffer.data,ws->buffer.end
			-ws->buffer.data+5120);
		ws->buffer.end = ws->buffer.data+m_cl;
		ws->buffer.current = ws->buffer.data+m_l;
	}
	ASN1_PER_Align_Enc_extLengthMoveMem(ws,count,ws->buffer.bitOffset);

	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_OpenType(ASN1WorkSpace *ws,OpenType *value)
{
	ASNINT8 ch=0;
	ASNINT32 count;
	ASNINT32 movebyte;
	ASNUINT8 bitpointer;
	ASNUINT8 *currentpointer;
	currentpointer = ws->buffer.current + 1;
	count = ASN1_PER_Align_Dec_extLengthMoveMem(ws,&movebyte,&bitpointer);
	if(0>count)
		return ASN1_PER_CHECK_LENGTH_ERROR;
	value->data = mpool_malloc(ws->Pmemory,count);
	memcpy(value->data,currentpointer,count);
	value->numocts = count;
	ws->buffer.current+=count-1;
	if(0>ASN1_ReadBuffer(ws,&ch,8-ws->buffer.bitOffset,UNALIGN))
		return ASN1_PER_CHECK_LENGTH_ERROR;
	if(0>ASN1_FillAndMoveMem(ws,&movebyte,&bitpointer))
		return ASN1_PER_CHECK_LENGTH_ERROR;
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_OpenType(ASN1WorkSpace *ws,OpenType *value)
{
	ASNINT8 ch=0;
	ASNUINT32 m_l;
	ASNUINT32 m_cl;
	ASNINT32 count;


	count = ws->buffer.current-ws->buffer.data+1;
	ASN1_ReadBuffer(ws,&ch,8,UNALIGN);
	ASN1_FillBuffer(ws,value->data,value->numocts*8,UNALIGN);

	if (ws->buffer.end <= ws->buffer.current+value->numocts)
	{
		m_l = ws->buffer.current-ws->buffer.data;
		m_cl = ws->buffer.end - ws->buffer.data;
		ws->buffer.data = mpool_realloc(ws->Pmemory,ws->buffer.data,ws->buffer.end
			-ws->buffer.data+5120);
		ws->buffer.end = ws->buffer.data+m_cl;
		ws->buffer.current = ws->buffer.data+m_l;
	}
	ASN1_PER_UNAlign_Enc_extLengthMoveMem(ws,count,ws->buffer.bitOffset);

	return 0;

}

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_OpenType(ASN1WorkSpace *ws,OpenType *value)
{
	ASNINT8 ch=0;
	ASNINT32 count;
	ASNINT32 movebyte;
	ASNUINT8 bitpointer;
	ASNUINT8 *currentpointer;

	count = ASN1_PER_UNAlign_Dec_extLengthMoveMem(ws,&movebyte,&bitpointer);
	if(0>count)
		return ASN1_PER_CHECK_LENGTH_ERROR;
	value->data = mpool_malloc(ws->Pmemory,count);
 	if (ws->buffer.bitOffset == 0)
 	{
 		ws->buffer.current++;
 		ws->buffer.bitOffset =8 ;
 	}
	currentpointer = ws->buffer.current;
	if(0>ASN1_ReadBuffer(ws,value->data,count*8,UNALIGN))
		return ASN1_PER_CHECK_LENGTH_ERROR;
// 	ASN1_ReadBuffer(ws,value->data,movebyte*8,UNALIGN);
/*	ws->buffer.current = currentpointer;*/

	value->numocts = count;
// 	ws->buffer.current+=count-1;
// 	ASN1_ReadBuffer(ws,&ch,8-ws->buffer.bitOffset,UNALIGN);
 	if(0>ASN1_FillAndMoveMem(ws,&movebyte,&bitpointer))
		return ASN1_PER_CHECK_LENGTH_ERROR;
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_PER_SET_WsToOpenType(ASN1WorkSpace *ws,OpenType *value)
{
	ASNINT32 count = ws->buffer.current - ws->buffer.data;
	value->data = mpool_malloc(ws->Pmemory,count+1);
	memcpy(value->data,ws->buffer.data,value->numocts = count+1);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_SET_OpenTypeToWs(ASN1WorkSpace *ws,OpenType *value)
{
	ASNUINT32 m_l;
	ASNUINT32 m_cl;
	if (ws->buffer.end <= ws->buffer.current+value->numocts)
	{
		m_l = ws->buffer.current-ws->buffer.data;
		m_cl = ws->buffer.end - ws->buffer.data;
		ws->buffer.data = mpool_realloc(ws->Pmemory,ws->buffer.data,ws->buffer.end
			-ws->buffer.data+5120);
		ws->buffer.end = ws->buffer.data+m_cl;
		ws->buffer.current = ws->buffer.data+m_l;
	}
	memcpy(ws->buffer.data,value->data,value->numocts);
	ws->buffer.current = ws->buffer.data;
	ws->buffer.bitOffset = 8;
	return 0;
}


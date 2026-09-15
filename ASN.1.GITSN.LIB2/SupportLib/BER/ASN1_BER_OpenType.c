
#include "ASN1_BER_OpenType.h"

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_OpenType(ASN1WorkSpace *ws,OpenType *value,ASN1TagType flag)
{
	ASNINT32 wsmemory = 0;
	ASNINT32 wsmemory_sub = 0;
	ASN1WorkSpace temp_ws;
	ASN1_INIT_WS_INFO(&temp_ws);

	if (flag == ASN1EXPL){
		ws->buffer.current -= 1;
		ASN1_BER_Enc_Length(ws,value->numocts);
	}
	else{
		ASN1_Save_WORKSPACE(&temp_ws,value->data,value->numocts);
		if(0>_ASN1_BER_CHECK_Length_Opentype(&temp_ws)){
			ASN1_Destroy_WORKSPACE(&temp_ws);
			return -203;
		}
			
	}
	
	if (value->numocts > (ASNUINT32)(ws->buffer.end - ws->buffer.current)) //if buffer is full, 
	{
		ASN1_RESET_WS_INFO(ws,(ws->buffer.end - ws->buffer.data)+value->numocts);
	}
	memcpy(ws->buffer.current,value->data,value->numocts);
	ws->buffer.current += value->numocts;
	
	ASN1_Destroy_WORKSPACE(&temp_ws);
	return 0;
}

ASNINT32 ASN1_BER_Dec_OpenType(ASN1WorkSpace *ws,OpenType *value,ASNINT32 len,ASN1TagType flag)
{	
	if (flag == ASN1EXPL)
	{
		value->numocts = ws->dataSize;
		
		value->data = (ASNUINT8 *)mpool_malloc(ws->Pmemory,value->numocts + 1);
		memset(value->data, 0, value->numocts + 1);
		memcpy(value->data, ws->buffer.current, value->numocts);
		ws->buffer.current += ws->dataSize;
	}
	else
	{
		ASNUINT8 *ps = ws->buffer.current;

		if (0 > _ASN1_BER_CHECK_Length_Opentype(ws)) return -204;		// get position of end of Open Typed Value

		value->data = (ASNUINT8 *)mpool_malloc(ws->Pmemory, ws->buffer.current - ps + 1);

		memset(value->data, 0, ws->buffer.current - ps + 1);
		memcpy(value->data, ps, ws->buffer.current - ps);

		value->numocts = ws->buffer.current - ps;
	}
	
	return 0;
}


/*ASNINT32 ASN1_BER_Dec_OpenType_Loop(ASN1WorkSpace *ws,ASNINT32 length)
{
	ASNUINT8* tagvalue = ws->buffer.current;
	ASNINT32 indef = 0;
    ASN1_BER_OpenType_Tag(ws);
	ASN_BER_Dec_Length(ws);

    indef = ws->dataSize;

	if(*tagvalue & 0x20)
	{
		ASN1_BER_Dec_OpenType_Loop(ws,ws->dataSize);//decode struct data

		if ((-1 == indef)  &&      
			(*ws->buffer.current == 0x00 && *(ws->buffer.current+1) == 0x00))

		   //if indefinite length and current pointer end flag,current add two 
			ws->buffer.current += 2;
		else
			//reset decode data
			ASN1_BER_Dec_OpenType_Loop(ws,0);
	}
	else
	{
		if (-1 == length) //decode simply data
		{
		   while(!(*ws->buffer.current == 0x00 && *(ws->buffer.current+1) == 0x00))
		   ws->buffer.current++;
		}
		else
		   ws->buffer.current += length;
	}
	return 0;
}*/


ASN1_CPPLINK ASNINT32 ASN1_BER_OpenType_SetP(ASN1WorkSpace *ws,OpenType *value)
{
	ws->buffer.openType = ws->buffer.current;

	ws->buffer.current = value->data;

	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_BER_OpenType_GetP(ASN1WorkSpace *ws)
{
	ws->buffer.current = ws->buffer.openType;
    return 0;
}


#include "ASN1_XER_OpenType.h"


ASN1_CPPLINK ASNINT32 ASN1_XER_Enc_OpenType_Value(ASN1WorkSpace * ws, OpenType *tvalue)
{
	ASN1WorkSpace temp_ws;
	ASN1_INIT_WS_INFO(&temp_ws);
	ASN1_Save_WORKSPACE(&temp_ws,tvalue->data,tvalue->numocts);
	if (0 > _ASN1_XER_Check_Length(&temp_ws)){
		ASN1_Destroy_WORKSPACE(&temp_ws);
		return -604;
	}
	ASN1_XER_FillBuffer(ws,tvalue->data,tvalue->numocts);
	ASN1_Destroy_WORKSPACE(&temp_ws);
	return 0;
}
ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_OpenType(ASN1WorkSpace * ws, OpenType *tvalue, 
										 ASNUINT8 *name,ASNINT32 tab_value)
{
	ASN1_XER_Enc_Start_Name(ws,name);
	
	if(0>ASN1_XER_Enc_OpenType_Value(ws,tvalue)){
		return -604;
	}
	ASN1_XER_Enc_End_Name(ws,name);
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_OpenType(ASN1WorkSpace * ws, OpenType *tvalue,
									 ASNUINT8 *name,ASNINT32 tab_value)
{
	ASN1_XER_Tab(ws,tab_value);
	
	if(0>ASN1_XER_CANONICAL_Enc_OpenType(ws,tvalue,name,tab_value)){
		return -604;
	}

	ASN1_XER_Enter(ws,1);
	return 0;
}
ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_OpentypeName(ASN1WorkSpace *ws,ASNSTRING *name)
{
	ASNINT32 temp_curretn = 0;
	ASNINT32 memory = 1;
	ASNINT32 re_value = 0;
	name->asnstring = (ASNUINT8*)mpool_malloc(ws->Pmemory,memory);
	name->nchar =0;

	if (*ws->buffer.current == '<' && *(ws->buffer.current+1) == '/'){
		return 7;
	}

	if(*ws->buffer.current == '<'){
		ws->buffer.current++;
		while (*ws->buffer.current != '>'){
			name->asnstring = (ASNUINT8*)mpool_realloc(ws->Pmemory,name->asnstring,++memory);
			name->asnstring[temp_curretn] = *ws->buffer.current;
			temp_curretn++;
			name->nchar++;
			ws->buffer.current++;
		}		
		if (*(ws->buffer.current-1) == '/'){
			re_value = 6;
		}
		ws->buffer.current++;

	}
	else{
		return -1;
	}
		
	return re_value;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_Opentype_Process(ASN1WorkSpace *ws, ASNSTRING *Dname)
{
	
	ASNUINT8 temp_curretn[200];
	ASNINT32 memory = 1;	
	ASNUINT8 *temp_value;
	ASNINT32 rvalue = 0;

	ASN1_XER_Dec_Prolog(ws);
	temp_value = (ASNUINT8*)malloc(Dname->nchar+4);
	memset(temp_value,0x00,Dname->nchar+4);
	strncpy(temp_value,Dname->asnstring,Dname->nchar);
	
	memset(temp_curretn,0x00,200);
	sprintf(temp_curretn,"</%s>",temp_value);
	free(temp_value);
	
	rvalue = strncmp(ws->buffer.current,temp_curretn,Dname->nchar+3);
	
	if (rvalue == 0){
		ws->buffer.current += Dname->nchar+3;
	}
	
	return rvalue;
}
ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_OpenType_Value(ASN1WorkSpace * ws, OpenType *value,
									 ASNUINT8 *name,ASNINT32 end_flag)
{
	ASNSTRING Dname;
	ASNINT32 opentype_name;
	ASN1_XER_Dec_Prolog(ws);
	ASN1_XER_Dec_Format(ws);
	opentype_name = ASN1_XER_Dec_OpentypeName(ws,&Dname);
	if (7 == opentype_name){
		return 0;
	}
	if(6 == opentype_name){
		if (0 == end_flag++){
			return 6;
		}
		else{
			return 0;
		}
// 		end_flag++;
// 		ASN1_XER_Dec_OpenType_Value(ws,value,name,end_flag);
// 		ASN1_XER_Dec_Format(ws);
	}
	ASN1_XER_Dec_Format(ws);

	while(0 != ASN1_XER_Dec_Opentype_Process(ws,&Dname)){
		ASN1_XER_Dec_OpenType_Value(ws,value,name,end_flag);
		ASN1_XER_Dec_Format(ws);
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_OpenType(ASN1WorkSpace * ws, OpenType *value,
										 ASNUINT8 *name,ASNINT32 tab_value)
{
	ASNUINT8* temp_current = ws->buffer.current;
	ASNINT32 re_value;
	ASNINT32 length = 1;
	ASN1WorkSpace temp_ws;
	re_value = ASN1_XER_Dec_OpenType_Value(ws,value,name,0);

	if (6 == re_value){
		value->numocts = 0;
	}
	else{
		value->numocts = ws->buffer.current-temp_current;
		value->data = (ASNUINT8*)mpool_malloc(ws->Pmemory,value->numocts);
		memcpy(value->data,temp_current,value->numocts);
		while(*temp_current != '>'){
			length++;
			temp_current++;
		}
		memmove(value->data,value->data+length,(value->numocts - (2*length+1)));
		value->numocts = (value->numocts - (2*length+1));
	}

	ASN1_INIT_WS_INFO(&temp_ws);
	ASN1_Save_WORKSPACE(&temp_ws,value->data,value->numocts);
	if (0 > _ASN1_XER_Check_Length(&temp_ws)){
		ASN1_Destroy_WORKSPACE(&temp_ws);
		return -605;
	}
	ASN1_Destroy_WORKSPACE(&temp_ws);
	return re_value;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_OpenType(ASN1WorkSpace * ws, OpenType *value,
									 ASNUINT8 *name,ASNINT32 tab_value)
{
	ASN1_XER_Dec_Format(ws);
	if(0>ASN1_XER_CANONICAL_Dec_OpenType(ws,value,name,tab_value))
		return -605;
/*	ASN1_XER_Dec_Format(ws);*/
	return 0;
}

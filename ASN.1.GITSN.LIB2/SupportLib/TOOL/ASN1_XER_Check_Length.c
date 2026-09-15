#include "ASN1_XER_Check_Length.h"
ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_Prolog_Check_Length(ASN1WorkSpace * ws)
{
	if ((*ws->buffer.current == '<') && *(ws->buffer.current+1) == '?'){
		if (0>ASN1_XER_IsWSrange(ws,1)){
			return -1;
		}
		ws->buffer.current++;
		while (*ws->buffer.current != '<'){
			if (0>ASN1_XER_IsWSrange(ws,1)){
				return -1;
			}
			ws->buffer.current++;
		}
	}
	return 0; 
}

ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_Format_Check_Length(ASN1WorkSpace *ws)
{
	if(*ws->buffer.current == '<'){
			return 3;
	}
	else{
		while (*ws->buffer.current != '<'){
			if (0>ASN1_XER_IsWSrange(ws,1)){
				return -1;
			}
			else{
				ws->buffer.current++;
			}
		}
	}
	return 0;
}
ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_Check_Length_Name(ASN1WorkSpace *ws,ASNSTRING *name)
{
	ASNINT32 temp_curretn = 0;
	ASNINT32 memory = 1;
	ASNINT32 re_value = 0;
	name->asnstring = (ASNUINT8*)mpool_malloc(ws->Pmemory,memory);
	name->nchar =0;

	if (*ws->buffer.current == '<' && *(ws->buffer.current+1) == '/'){
		while (*ws->buffer.current != '>'){
			if (0>ASN1_XER_IsWSrange(ws,1)){
				return -1;
			}
			ws->buffer.current++;
		}
		return 7;
	}

	if(*ws->buffer.current == '<'){
		if (0>ASN1_XER_IsWSrange(ws,1)){
			return -1;
		}
		ws->buffer.current++;
		while (*ws->buffer.current != '>'){
			name->asnstring = (ASNUINT8*)mpool_realloc(ws->Pmemory,name->asnstring,++memory);
			name->asnstring[temp_curretn] = *ws->buffer.current;
			temp_curretn++;
			name->nchar++;
			if (0>ASN1_XER_IsWSrange(ws,1)){
				return -1;
			}
			ws->buffer.current++;
		}		
		if (*(ws->buffer.current-1) == '/'){
			re_value = 6;
		}
		if (0>ASN1_XER_IsWSrange(ws,1)){
			return -1;
		}
		ws->buffer.current++;

	}
	else{
		return -1;
	}
		
	return re_value;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_Check_Length_Process(ASN1WorkSpace *ws, ASNSTRING *Dname)
{
	
	ASNUINT8 temp_curretn[200];
	ASNINT32 memory = 1;	
	ASNUINT8 *temp_value;
	ASNINT32 rvalue = 0;
	if (*ws->buffer.current=='<'&&*(ws->buffer.current+1) != '/'){
		ws->buffer.current++;
		while (*ws->buffer.current != '<'){
			if (0>ASN1_XER_IsWSrange(ws,1)){
				return -1;
			}
			ws->buffer.current++;
		}
	}
	ASN1_XER_Dec_Prolog_Check_Length(ws);
	temp_value = (ASNUINT8*)malloc(Dname->nchar+4);
	memset(temp_value,0x00,Dname->nchar+4);
	strncpy(temp_value,Dname->asnstring,Dname->nchar);
	
	memset(temp_curretn,0x00,200);
	sprintf(temp_curretn,"</%s>",temp_value);
	free(temp_value);
	
	rvalue = strncmp(ws->buffer.current,temp_curretn,Dname->nchar+3);
	
	if (rvalue == 0){
		if (0>ASN1_BER_IsWSrange(ws,Dname->nchar+3)){
			return -1;
		}
		ws->buffer.current += Dname->nchar+3;
	}
	
	return rvalue;
}
ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_Check_Length_Value(ASN1WorkSpace * ws,ASNINT32 end_flag)
{
	ASNSTRING Dname;
	ASNINT32 opentype_name;

	if (0>ASN1_XER_Dec_Prolog_Check_Length(ws)){
		return -1;
	}
	if(0>ASN1_XER_Dec_Format_Check_Length(ws)){
		return -1;
	}

	opentype_name = ASN1_XER_Dec_Check_Length_Name(ws,&Dname);
	if (7 == opentype_name){
		return 0;
	}
	else if(6 == opentype_name){
		if (0 == end_flag++){
			return 6;
		}
		else{
			return 0;
		}
	}
	else if (0>opentype_name){
		return opentype_name;
	}

	if(0>ASN1_XER_Dec_Format_Check_Length(ws)){
		return -1;
	}

	while(0 == (opentype_name=ASN1_XER_Dec_Check_Length_Process(ws,&Dname))){
		if (0>opentype_name){
			return opentype_name;
		}
		if (ws->buffer.current == ws->buffer.Vdeocd_valid){
				return 0;
		}
		if (0>ASN1_XER_Dec_Check_Length_Value(ws,end_flag)){
				return -1;
		}
		if (ws->buffer.current == ws->buffer.Vdeocd_valid){
				return 0;
		}
		if (0>ASN1_XER_Dec_Format_Check_Length(ws)){
				return -1;
		}
	}
	return 0;
}


ASN1_CPPLINK ASNINT32 _ASN1_XER_Check_Length(ASN1WorkSpace * ws)
{
//	ASNUINT8* temp_current = ws->buffer.current;
	ASNINT32 re_value;
	ASNINT32 length = 1;
	ASNUINT8* ps = ws->buffer.current;
	ASNINT32 temp_bitoffset=ws->buffer.bitOffset;
	if (0>ASN1_XER_Dec_Format_Check_Length(ws))
		return -1;
	re_value = ASN1_XER_Dec_Check_Length_Value(ws,0);
	
	ws->buffer.current = ps;
	ws->buffer.bitOffset = temp_bitoffset;
	if (0>re_value){
		return ASN1_XER_CHECK_LENGTH_ERROR;
	}
	return re_value;
}


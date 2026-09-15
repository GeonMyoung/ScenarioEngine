#include "ASN1_XER_Name.h"

ASN1_CPPLINK ASNINT32 ASN1_XER_Enc_Start_Name(ASN1WorkSpace *ws,ASNUINT8* name)
{
	ASNUINT8* fullname;
	fullname = (ASNUINT8*)malloc((strlen(name)+4)*sizeof(ASNUINT8));
	memset(fullname,0x00,(strlen(name)+4));
	sprintf(fullname,"<%s>",name);
	ASN1_XER_FillBuffer(ws,fullname, (ASNUINT32)strlen(name) + 2);
	free(fullname);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_Enc_End_Name(ASN1WorkSpace *ws,ASNUINT8* name)
{
	/*
	ASNUINT8 *temp_current=0x0; 
	ASNINT32 i = strlen(name);
	temp_current = ws->buffer.current;
	if (*(temp_current-1) == '>'){
	while (*temp_current != '<'){
	temp_current -= 1;
	}
	if (!(strncmp(temp_current+1,name,i))){
	ws->buffer.current = temp_current;
	ASN1_XER_Enc_Backslash_Name(ws,name);
	}
	else{
	ASN1_XER_Enc_End_Name(ws,name);
	}
	}
	else{
	ASN1_XER_Enc_End_Name(ws,name);
	}
	return 0;
	*/
	ASNUINT8* fullname;
	ASNUINT8 *temp_current=0x0; 

	ASNINT32 i = (ASNINT32)strlen(name);

	temp_current = ws->buffer.current;
	if (*(temp_current-1) == '>'){
		while (*temp_current != '<'){
			temp_current -= 1;
	}
	if (!(strncmp(temp_current+1,name,i))){
			ws->buffer.current = temp_current;
			ASN1_XER_Enc_Backslash_Name(ws,name);
		}
		else{
			fullname = (ASNUINT8*)malloc((strlen(name)+4)*sizeof(ASNUINT8));
			memset(fullname,0x00,(strlen(name)+4));
			sprintf(fullname,"</%s>",name);
			ASN1_XER_FillBuffer(ws,fullname, (ASNUINT32)strlen(name) + 3);
			free(fullname);
		}
	}
	else{
		fullname = (ASNUINT8*)malloc((strlen(name)+4)*sizeof(ASNUINT8));
		memset(fullname,0x00,(strlen(name)+4));
		sprintf(fullname,"</%s>",name);
		ASN1_XER_FillBuffer(ws,fullname, (ASNUINT32)strlen(name) + 3);
		free(fullname);
	}
/*
	fullname = (ASNUINT8*)malloc((strlen(name)+4)*sizeof(ASNUINT8));
	memset(fullname,0x00,(strlen(name)+4));
	sprintf(fullname,"</%s>",name);
	ASN1_XER_FillBuffer(ws,fullname,strlen(name)+3);
	free(fullname);
*/
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_Enc_Backslash_Name(ASN1WorkSpace *ws,ASNUINT8* name)
{
	ASNUINT8* fullname;
	fullname = (ASNUINT8*)malloc((strlen(name)+4)*sizeof(ASNUINT8));
	memset(fullname,0x00,(strlen(name)+4));
	sprintf(fullname,"<%s/>",name);
	ASN1_XER_FillBuffer(ws,fullname, (ASNUINT32)strlen(name) + 3);
	free(fullname);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_Tab(ASN1WorkSpace *ws,ASNINT32 tab_count)
{
	ASNUINT8 temp_value[10];
	memset(temp_value,0x00,10);

	sprintf(temp_value,"  ");
	
	while(0 != tab_count){
		ASN1_XER_FillBuffer(ws,temp_value,2);
		tab_count--;
    }
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_Enter(ASN1WorkSpace *ws,ASNINT32 Ent_count)
{
	ASNUINT8 temp_value[10];
	memset(temp_value,0x00,10);

	sprintf(temp_value,"\n");
	
	while(0 != Ent_count){
		ASN1_XER_FillBuffer(ws,temp_value,1);
		Ent_count--;
    }
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_Name(ASN1WorkSpace *ws)
{
	ASNINT32 value_null = 0;
	if(*ws->buffer.current == '<'){
		while (*ws->buffer.current != '>'){
			ws->buffer.current++;
		}
		if (*(ws->buffer.current-1) == '/'){
			value_null = 6;
		}
		ws->buffer.current++;
	}
	else
		return -1;
	return value_null;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_Format(ASN1WorkSpace *ws)
{
	if(*ws->buffer.current == '<'){
		return 3;
	}
	else{
		while (*ws->buffer.current != '<'){
			ws->buffer.current++;
		}
	}
	return 0;
}

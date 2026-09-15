#include "ASN1_XER_REAL.h"

ASN1_CPPLINK ASNINT32 ASN1_XER_Enc_REAL_Value(ASN1WorkSpace * ws,REAL *tvalue)
{
	ASNUINT8 temp_value[512];
	ASNUINT8 encode_value[512];
	ASNINT32 flag = 0;
	ASNINT32 i = 0;
	ASNINT32 j = 3;
	ASNINT32 len;
	ASNINT32 num=0;
	ASNUINT8 *temp_pointer;

	memset(temp_value,0x00,512);
	memset(encode_value,0x00,512);	
	if (*tvalue == 0){
		sprintf(temp_value,"0");
	}
	else{
		sprintf(temp_value,"%E",*tvalue);
		while (!(temp_value[i]=='E' || temp_value[i]=='e')){
			if (temp_value[i] == '.'){
				num = 5;
				flag = i+1;
			}
			if (temp_value[i] != '0' && temp_value[i] != '.'){
				if (num == 5){
					num = 6;
				}
				flag = i+1;
			}
			i++;
		}
		
		if (num == 5){
			len = flag + (ASNINT32)strlen(&temp_value[i]) + 2;
			strcpy(&temp_value[flag+1],&temp_value[i]);
			i = flag+1;
		}
		else{
			len = flag + (ASNINT32)strlen(&temp_value[i]) + 1;
			strcpy(&temp_value[flag],&temp_value[i]);
			i = flag;
		}
		
		temp_value[len] = '\0';
		/*temp_pointer =encode_value+flag+1;*/
		
		if(temp_value[++i] == '+'){
			temp_pointer = temp_value+i;
		}
		else{
			temp_pointer = temp_value+i;
		}
		i++;
		while(j){
			flag = 0;
			if(temp_value[i]!='0'){
				memmove(temp_pointer+1,&temp_value[i],j);
				flag = 1;
			}
			i++;
			j--;
		}

		if (flag == 0){
			memmove(temp_pointer,"0",1);
		}

		temp_pointer = temp_pointer+j+2;
		memset(temp_pointer,0x00,3-j);
	}
	
	ASN1_XER_FillBuffer(ws,temp_value, (ASNUINT32)strlen(temp_value));
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_REAL_Value(ASN1WorkSpace * ws, REAL *value)
{
	ASNUINT8 temp_value[128];
	ASNINT32 i = 0;
	*value = 0;
	memset(temp_value,0x00,128);
	
	while (*ws->buffer.current != '<'){
		temp_value[i++] = *ws->buffer.current;
		ws->buffer.current++;
	}

	*value = atof(temp_value);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_REAL(ASN1WorkSpace * ws, REAL *tvalue, 
										ASNUINT8 *name,ASNINT32 tab_value)
										
{
	ASN1_XER_Enc_Start_Name(ws,name);
	ASN1_XER_Enc_REAL_Value(ws,tvalue);
	ASN1_XER_Enc_End_Name(ws,name);
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_REAL(ASN1WorkSpace * ws, REAL *tvalue,
									ASNUINT8 *name,ASNINT32 tab_value)
									
{
	ASN1_XER_Tab(ws,tab_value);
	ASN1_XER_CANONICAL_Enc_REAL(ws,tvalue,name,tab_value);
	ASN1_XER_Enter(ws,1);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_REAL(ASN1WorkSpace * ws, REAL *value,
										ASNUINT8 *name,ASNINT32 tab_value)
{
	ASN1_XER_Dec_Name(ws);
	ASN1_XER_Dec_REAL_Value(ws,value);
 	ASN1_XER_Dec_Name(ws);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_REAL(ASN1WorkSpace * ws, REAL *value,
									ASNUINT8 *name,ASNINT32 tab_value)
{
	ASN1_XER_Dec_Format(ws);
	ASN1_XER_CANONICAL_Dec_REAL(ws,value,name,tab_value);
/*	ASN1_XER_Dec_Format(ws);*/
	return 0;
}





#include "ASN1_XER_SET.h"
ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_Struct_Start(ASN1WorkSpace * ws,
									         ASNUINT8 *name,ASNINT32 tab_value)
{
	ASN1_XER_Enc_Start_Name(ws,name);
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_Struct_Start(ASN1WorkSpace * ws,
								         ASNUINT8 *name,ASNINT32 tab_value)
{
	ASN1_XER_Tab(ws,tab_value);
	ASN1_XER_CANONICAL_Enc_Struct_Start(ws,name,tab_value);
	ASN1_XER_Enter(ws,1);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_Struct_End(ASN1WorkSpace * ws,
										   ASNUINT8 *name,ASNINT32 tab_value)
{
	
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
			ASN1_XER_Enc_End_Name(ws,name);
		}
	}
	else{
		ASN1_XER_Enc_End_Name(ws,name);
	}
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_Struct_End(ASN1WorkSpace * ws,
								         ASNUINT8 *name,ASNINT32 tab_value)
{
	ASN1_XER_Tab(ws,tab_value);
	ASN1_XER_CANONICAL_Enc_Struct_End(ws,name,tab_value);
	ASN1_XER_Enter(ws,1);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_Struct_Start(ASN1WorkSpace * ws,ASNUINT8* name,
											 ASN1XERFlag *xer_flag)
{
	ASNINT32 temp_curretn = 0;
	ASNINT32 memory = 1;	
	ASNUINT8 *dec_name;
	ASNINT32 re_value = 0;
	*xer_flag = XER_REF;
	dec_name = (ASNUINT8*)malloc(memory);

	if(*ws->buffer.current == '<'){
		ws->buffer.current++;
		while (*ws->buffer.current != '>'){
			dec_name = (ASNUINT8*)realloc(dec_name,++memory);
			dec_name[temp_curretn] = *ws->buffer.current;
			temp_curretn++;
			ws->buffer.current++;
		}
		if (*(ws->buffer.current-1) == '/'){
			*xer_flag = XER_NULL;
		}
		ws->buffer.current++;
		if (strncmp(name,dec_name,strlen(name))){
			re_value = -1;
		}
	}
	else{
		free(dec_name);
		return -1;
	}
		
	free(dec_name);
	return re_value;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_Struct_Start(ASN1WorkSpace * ws,ASNUINT8* name,
											 ASN1XERFlag *xer_flag)
{

	ASN1_XER_Dec_Format(ws);
	ASN1_XER_CANONICAL_Dec_Struct_Start(ws,name,xer_flag);
	if(*xer_flag != XER_NULL){
		ASN1_XER_Dec_Format(ws);
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Dec_Struct_End(ASN1WorkSpace * ws,ASNUINT8* name,
										   ASN1XERFlag *xer_flag)
{
	ASNUINT8 temp_name[200];
	memset(temp_name,0x00,200);

	if (*xer_flag == XER_NULL){
		return 0;
	}
	sprintf(temp_name,"</%s>",name);

	if(strncmp(ws->buffer.current,temp_name,strlen(name)+3)){
		return -1;
	}
	else{
		ws->buffer.current+=(strlen(name)+3);
	}
// 	ASN1_XER_Dec_Name(ws);
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Dec_Struct_End(ASN1WorkSpace * ws,ASNUINT8* name,
									   ASN1XERFlag *xer_flag)
{
	ASN1_XER_Dec_Format(ws);
	ASN1_XER_CANONICAL_Dec_Struct_End(ws,name,xer_flag);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_Prolog(ASN1WorkSpace * ws)
{
	if ((*ws->buffer.current == '<') && *(ws->buffer.current+1) == '?'){
		ws->buffer.current++;
		while (*ws->buffer.current != '<'){
			ws->buffer.current++;
		}
	}
	return 0; 
}

ASN1_CPPLINK ASNINT32 Start_strcmp(ASN1WorkSpace *ws,ASNUINT8 *tvalue)
{
	ASNUINT8 temp_curretn[200];
	ASNINT32 memory = 1;	
	ASNINT32 rvalue = 0;

	memset(temp_curretn,0x00,200);
	sprintf(temp_curretn,"%s",tvalue);
	rvalue = strncmp(ws->buffer.current+1,temp_curretn,strlen(tvalue));
	return rvalue;
}
ASN1_CPPLINK ASNINT32 ASN1_XER_Temp_DeName(ASN1WorkSpace *ws,ASNINT32 *value_null,
							  ASNSTRING *tvalue)
{
	ASNINT32 temp_curretn = 0;
	ASNINT32 memory = 1;	
	ASNUINT8 *Tworkspace = ws->buffer.current;

	tvalue->nchar = 0;
	*value_null = 1;
	tvalue->asnstring = (ASNUINT8*)mpool_malloc(ws->Pmemory,memory);
	
	if(*ws->buffer.current == '<'){
		ws->buffer.current++;
		while (*ws->buffer.current != '>'){
			if (*ws->buffer.current == '/'){
				*value_null = 0;
			}
			tvalue->asnstring = (ASNUINT8*)mpool_realloc(ws->Pmemory,tvalue->asnstring,++memory);
			tvalue->asnstring[temp_curretn] = *ws->buffer.current;
			temp_curretn++;
			tvalue->nchar++;
			ws->buffer.current++;
		}
		ws->buffer.current++;
	}
	else
		return -1;

	if (*value_null == 1){
		ws->buffer.current = Tworkspace;
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 Start_DeName_strcmp(ASNUINT8 *name,ASNSTRING *tvalue)
{
	return strncmp(name,tvalue->asnstring,tvalue->nchar);
}

ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_CANONICAL_Format(ASN1WorkSpace * ws)
{
		return 0; 
}

ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_BASIC_Format(ASN1WorkSpace * ws)
{
		ASN1_XER_Dec_Format(ws);
		return 0; 
}


ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_ExbitName(ASN1WorkSpace *ws,ASNSTRING *name)
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

ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_Exbit_Process(ASN1WorkSpace *ws, ASNSTRING *Dname)
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
ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_Exbit_Value(ASN1WorkSpace * ws,ASNINT32 end_flag)
{
	ASNSTRING Dname;
	ASNINT32 opentype_name;

	ASN1_XER_Dec_Prolog(ws);
	ASN1_XER_Dec_Format(ws);
	opentype_name =ASN1_XER_Dec_ExbitName(ws,&Dname);
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
// 		ASN1_XER_Dec_Exbit_Value(ws,end_flag);
// 		ASN1_XER_Dec_Format(ws);
	}
	
	
	while(0 != ASN1_XER_Dec_Exbit_Process(ws,&Dname)){
		ASN1_XER_Dec_Exbit_Value(ws,end_flag);
		ASN1_XER_Dec_Format(ws);
	}
	return 0;
}
ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_CANONICAL_Exbit(ASN1WorkSpace *ws)
{
	return ASN1_XER_Dec_Exbit_Value(ws,0);
}

ASN1_CPPLINK ASNINT32 ASN1_XER_Dec_BASIC_Exbit(ASN1WorkSpace *ws)
{
	ASN1_XER_Dec_Format(ws);
	ASN1_XER_Dec_CANONICAL_Exbit(ws);
/*	ASN1_XER_Dec_Format(ws);*/
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_Set_Seq_Of_Loop(ASN1WorkSpace *ws)
{
	ASN1_XER_Dec_Format(ws);
	if (*ws->buffer.current == '<' && *(ws->buffer.current+1) == '/'){
		return 0;
	}
	else{
		return 1;
	}
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_Struct_Start_Of(ASN1WorkSpace *ws,ASNUINT8 *name,
											   ASN1List* asnlist,ASNINT32 tab_value)
{
	if (asnlist->count == 0){
		ASN1_XER_Enc_Backslash_Name(ws,name);
		return 0;
	}
	ASN1_XER_Enc_Start_Name(ws,name);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_Struct_Start_Of(ASN1WorkSpace *ws,ASNUINT8 *name,
										  ASN1List* asnlist,ASNINT32 tab_value)
{
	ASN1_XER_Tab(ws,tab_value);
	ASN1_XER_CANONICAL_Enc_Struct_Start_Of(ws,name,asnlist,tab_value);
	ASN1_XER_Enter(ws,1);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_CANONICAL_Enc_Struct_End_Of(ASN1WorkSpace *ws,ASNUINT8 *name,
											  ASN1List* asnlist,ASNINT32 tab_value)
{
	if (asnlist->count == 0){
		return 0;
	}
	else{
		ASN1_XER_Enc_End_Name(ws,name);
	}
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_XER_BASIC_Enc_Struct_End_Of(ASN1WorkSpace *ws,ASNUINT8 *name,
										 ASN1List* asnlist,ASNINT32 tab_value)
{
	ASN1_XER_Tab(ws,tab_value);
	ASN1_XER_CANONICAL_Enc_Struct_End_Of(ws,name,asnlist,tab_value);
	ASN1_XER_Enter(ws,1);
	return 0;
}

ASN1_CPPLINK ASNINT32 inttostr(ASNINT32 sourint,ASNINT8 *deststr,ASNINT32 strlength)
{
	ASNINT32 i=1,j=0,k=0;
	ASNINT32 tmpsourint = sourint;

	while (tmpsourint /10 !=0)
	{
		i++;
		tmpsourint = tmpsourint /10 ;
	}
	for (j=0;j < strlength-i;j++)
	{
		deststr[j] = '0';
	}
	tmpsourint = sourint;
	for (k=0;k<i-1;k++)
	{
		deststr[j+k] = (tmpsourint / pow(10,i-k-1)) + 48;
		tmpsourint = tmpsourint - (deststr[j+k]-48) * pow(10,i-k-1);
			

	}
	deststr[j+k] =tmpsourint +48 ;
	deststr[j+k+1] =0;
	return 0;
}


ASN1_CPPLINK ASNINT32 changetimetogen(ASNINT8 *source,ASNINT8 *dest,ASNINT8 guflag)
{
	ASNINT32 i=0,j=0,k=0;
	ASNINT8 flag =0;
	ASNINT32 currentyear=0,currentmonth=0,currentdate=0,currenthour =0,currentmin=0,currentsec=0;
	ASNINT32 timediffhour=0,timediffmin=0,timediffsec=0 ;
	if (source[strlen(source) -1] == 'Z')
	{
		strncpy(dest,source,strlen(source));
		dest[strlen(source)]=0;
		return 0;
	}
	

	if (guflag ==0 )
	{
		j+=2;		
	} 
	
	j +=2;	 
	for (;i<j;i++)
	{
		currentyear = currentyear * 10 + source[i] -48;
	}

	j +=2;	 
	for (;i<j;i++)
	{
		currentmonth = currentmonth * 10 + source[i]-48;
	}

	j +=2;	 
	for (;i<j;i++)
	{
		currentdate = currentdate * 10 + source[i]-48;
	}

	j +=2;	 
	for (;i<j;i++)
	{
		currenthour = currenthour * 10 + source[i]-48;
	}
	j +=2;	 
	for (;i<j;i++)
	{
		currentmin = currentmin * 10 + source[i]-48;
	}
	j +=2;	 
	for (;i<j;i++)
	{
		currentsec = currentsec * 10 + source[i]-48;
	}
	

	for (;i < (ASNINT32)strlen(source);i++)
	{
		if(source[i]=='+'||source[i]=='-') {
			flag = source[i];
			break;
		}  
	}
	if (flag == 0)
	{
		strncpy(dest,source,i);
		dest[i] = 'Z';
		dest[i+1]='\0';
		return 0;
	}

	i++;

	for (j=0;j< 2;j++)
	{
		timediffhour = timediffhour * 10 + source[i+j] -48; 
	}

	for (j=2;j< 4;j++)
	{
		timediffmin = timediffmin * 10 + source[i+j] -48; 
	}
	timediffmin = timediffmin *6;
	timediffsec = timediffmin % 10;
	timediffmin = (timediffmin - timediffsec) /10;
	timediffsec = timediffsec *6;


	if(flag == 43)
	{
		timediffhour = -timediffhour; 
		timediffmin = -timediffmin;
		timediffsec = - timediffsec;
	}

	currentsec = currentsec + timediffsec;
	currentmin = currentmin + timediffmin;
	currenthour = currenthour + timediffhour;
	if (currentsec<0)
	{
		currentsec +=60;
		currentmin--;
	} 
	else if(currentsec > 59)
	{
		currentsec -=60;
		currentmin++;
	}
	if (currentmin <0)
	{
		currentmin +=60;
		currenthour--;
	}
	else if(currentmin>59)
	{
		currentmin -=60;
		currenthour++;
	}	
	if (currenthour < 0)
	{
		currenthour +=24;
		currentdate--;
	} 
	else if(currenthour >23)
	{
		currenthour -=24;
		currentdate++;
	}


	if (currentdate == 0)
	{
		
		if (currentmonth ==1 ||currentmonth ==2 || currentmonth ==4 || currentmonth ==6 || currentmonth ==7|| currentmonth ==9|| currentmonth ==11)
		{
			currentdate = 31;
		}
		else if(currentmonth ==5 || currentmonth ==7 || currentmonth ==10 || currentmonth ==12){
			currentdate = 30;
		}
		else
		{
			if (guflag !=0)
			{
				currentdate =29;
			} 
			else
			{
				if ((currentyear % 400 ==0) ||((currentyear % 4 ==0) && (currentyear % 100 !=0)))
				{
					currentdate =29;
				}
				else
				{
					currentdate =28;
				}

			}
		}
		currentmonth-=1;
	}

	else if ((currentmonth ==1 ||currentmonth ==3 || currentmonth ==5 || currentmonth ==7 || currentmonth ==8|| currentmonth ==10|| currentmonth ==12) && currentdate ==32)
	{
		currentmonth++;
		currentdate =1;
	} 
	else if((currentmonth ==4 || currentmonth ==6 || currentmonth ==9 || currentmonth ==11) && currentdate ==31)
	{
		currentmonth++;
		currentdate =1;
	}
	else
	{
		if (currentmonth==2 && currentdate ==30)
		{
			currentmonth++;
			currentdate =1;
		}
		if (guflag ==0 )
		{
			if ((!(currentyear % 400 ==0) ||((currentyear % 4 ==0) && (currentyear % 100 !=0))) && currentdate==29)
			{
				currentmonth++;
				currentdate =1;
			}
				
		} 
		
	}


	if (currentmonth ==0)
	{
		currentmonth =12;
		currentyear--;
	} 
	else if(currentmonth == 13)
	{
		currentmonth =1;
		currentyear++;
	}

	if (guflag != 0)
	{
		if (currentyear < 0)
		{
			currentyear =99;
		} 
		else if(currentyear > 99)
		{
			currentyear =0;

		}
	}





	k=0;
	j=2;
	if (guflag==0)
	{
		j+=2;
	}
	inttostr(currentyear,dest+k,j);

	k=k+j;
	j=2;	
	inttostr(currentmonth,dest+k,j);
	k=k+j;
	inttostr(currentdate,dest+k,j);
	k=k+j;
	inttostr(currenthour,dest+k,j);
	k=k+j;
	inttostr(currentmin,dest+k,j);
	k=k+j;
	inttostr(currentsec,dest+k,j);
	k=k+j;
	if (guflag==0)
	{
		strncpy(dest+k,source+14,i-15);
		k = k+i-15;
	} 
	else
	{
		strncpy(dest+k,source+12,i-13);
		k = k+i-13;
	}
	 
	
	dest[k]='Z';
	k++;
	dest[k]=0;
	return 0;



}

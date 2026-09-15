#include "ASN1_PER_RELATIVE_OID.h"

#ifdef WIN32
#pragma warning(disable:4018)
#endif

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_RELATIVE_OID(ASN1WorkSpace* ws, RELATIVE_OID* value,Asn1ConsInfo *consinfo)
{

	ASNUINT32 F_Ui_Roid_Subid = 0; //array number log
	ASNUINT32 F_Ui_Roid_Enc = 0;   //will encode value
	ASNINT32 F_In_Roid_Save_Count =0; //save memory count log    
	ASNINT32 F_In_Roid_Enc_Count; //encode count
	ASNINT32 F_In_Roid_Enc_Temp_Count;//save temp encode count
	ASNINT32 F_In_Roid_Save_Memony = 10; //memory save size
	ASNINT32 F_In_Roid_Enc_Memony = 10; //temp buffer size
    ASNUINT8* F_Uc_Roid_Enc_Memony;  //memory save poASNINT32er
	ASNUINT8* F_Uc_Roid_Save_Memony; //memory temp buffer poASNINT32er
	ASNINT32 wsmemory = 0;
	ASNINT32 wsmemory_sub = 0;
	ASNINT32 sever_flag = 1;
	ASNINT32 process_length;
	F_Uc_Roid_Save_Memony = 
		(ASNUINT8*)malloc(F_In_Roid_Save_Memony*sizeof(ASNUINT8));
	
	while (F_Ui_Roid_Subid < value->numids) 
	{
		F_In_Roid_Enc_Count = 0;
		F_Ui_Roid_Enc = value->subid[F_Ui_Roid_Subid];//get encode value
        F_Uc_Roid_Enc_Memony = 
			(ASNUINT8*)malloc(F_In_Roid_Enc_Memony*sizeof(ASNUINT8));
		
		do
		{			
			F_Uc_Roid_Enc_Memony[F_In_Roid_Enc_Count] = 0x7f & F_Ui_Roid_Enc;
			if(F_In_Roid_Enc_Count)
				F_Uc_Roid_Enc_Memony[F_In_Roid_Enc_Count] |= 0x80; /* Set bit 7 to 1 if not first byte */
			F_Ui_Roid_Enc = F_Ui_Roid_Enc>>7;
			F_In_Roid_Enc_Count++;
			
		}while(F_Ui_Roid_Enc);
		
		F_In_Roid_Enc_Temp_Count = F_In_Roid_Enc_Count; 
		F_In_Roid_Enc_Count = F_In_Roid_Save_Count+F_In_Roid_Enc_Count;
		
        for (F_In_Roid_Enc_Temp_Count--;F_In_Roid_Save_Count<F_In_Roid_Enc_Count;F_In_Roid_Save_Count++)
		{			
			
            F_Uc_Roid_Save_Memony[F_In_Roid_Save_Count] = F_Uc_Roid_Enc_Memony[F_In_Roid_Enc_Temp_Count];
			//printf("%02x\n",F_Uc_Roid_Save_Memony[F_In_Roid_Save_Count]); //use test
            F_In_Roid_Enc_Temp_Count--;
		}//form save temp memory to save memory;
		
        free(F_Uc_Roid_Enc_Memony);
		F_Ui_Roid_Subid++;
   	}
	
	
	if (F_In_Roid_Save_Count > ws->buffer.end - ws->buffer.current)
	{
		wsmemory = ((ws->buffer.end - ws->buffer.data)+10);
		wsmemory_sub = (ws->buffer.end - ws->buffer.current);
		
		ws->buffer.data = (ASNUINT8*)mpool_realloc(ws->Pmemory,ws->buffer.data,
			wsmemory*sizeof(ASNUINT8));
		ws->buffer.end = ws->buffer.data+ wsmemory;
		if (wsmemory_sub)
		{
			ws->buffer.current = ws->buffer.end - 10 - wsmemory_sub;
		}
		else
		{
			ws->buffer.current = ws->buffer.end - 10 + wsmemory_sub;
		}
	}
    
	while (sever_flag)
	{	
		sever_flag = ASN1_PER_Enc_SeverLength(ws,&F_In_Roid_Save_Count,NULL,
			&process_length,ALIGN);
		ASN1_FillBuffer(ws,F_Uc_Roid_Save_Memony,8*process_length,ALIGN);
	}

	free(F_Uc_Roid_Save_Memony);
	//printf("%d",F_In_Roid_Save_Count); //use test
    return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_RELATIVE_OID(ASN1WorkSpace* ws, RELATIVE_OID* value,Asn1ConsInfo *consinfo)
{
	ASNINT32 F_In_Dec_Count = 0; //roid decode count log
	ASNINT32 F_In_Dec_Loop_Count = 0;    
	ASNUINT32 sever_flag=1;
	ASNUINT8 *F_Uc_Oid_Save_Memony;
	struct PER_Flag flag;

	sever_flag = ASN1_PER_Dec_SeverLength(ws,NULL,&flag,ALIGN);
	if(0>sever_flag)
		return ASN1_PER_CHECK_LENGTH_ERROR;
	F_Uc_Oid_Save_Memony = malloc(flag.PER_Dec_Len*sizeof(ASNUINT8));
	if(0>ASN1_ReadBuffer(ws,F_Uc_Oid_Save_Memony,8*flag.PER_Dec_Len,ALIGN))
		return ASN1_PER_CHECK_LENGTH_ERROR;

	while (F_In_Dec_Loop_Count < flag.PER_Dec_Len) //loop decode value
	{
		value->subid[F_In_Dec_Count] = 0;
		
		while (*F_Uc_Oid_Save_Memony & 0x80)
		{
			value->subid[F_In_Dec_Count] += *(F_Uc_Oid_Save_Memony) & 0x7f;
			value->subid[F_In_Dec_Count] <<= 7;
			F_In_Dec_Loop_Count++;
			F_Uc_Oid_Save_Memony++;
		}
		value->subid[F_In_Dec_Count] += *(F_Uc_Oid_Save_Memony);
		
		F_Uc_Oid_Save_Memony++;
		F_In_Dec_Loop_Count++;
		F_In_Dec_Count++;
	}
	value->numids = F_In_Dec_Count;
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_RELATIVE_OID(ASN1WorkSpace* ws, RELATIVE_OID* value,Asn1ConsInfo *consinfo)
{
	ASNUINT32 F_Ui_Roid_Subid = 0; //array number log
	ASNUINT32 F_Ui_Roid_Enc = 0;   //will encode value
	ASNINT32 F_In_Roid_Save_Count =0; //save memory count log    
	ASNINT32 F_In_Roid_Enc_Count; //encode count
	ASNINT32 F_In_Roid_Enc_Temp_Count;//save temp encode count
	ASNINT32 F_In_Roid_Save_Memony = 10; //memory save size
	ASNINT32 F_In_Roid_Enc_Memony = 10; //temp buffer size
    ASNUINT8* F_Uc_Roid_Enc_Memony;  //memory save poASNINT32er
	ASNUINT8* F_Uc_Roid_Save_Memony; //memory temp buffer poASNINT32er
	ASNINT32 wsmemory = 0;
	ASNINT32 wsmemory_sub = 0;
	ASNINT32 sever_flag = 1;
	ASNINT32 process_length;
	F_Uc_Roid_Save_Memony = 
		(ASNUINT8*)malloc(F_In_Roid_Save_Memony*sizeof(ASNUINT8));
	
	while (F_Ui_Roid_Subid < value->numids) 
	{
		F_In_Roid_Enc_Count = 0;
		F_Ui_Roid_Enc = value->subid[F_Ui_Roid_Subid];//get encode value
        F_Uc_Roid_Enc_Memony = 
			(ASNUINT8*)malloc(F_In_Roid_Enc_Memony*sizeof(ASNUINT8));
		
		do
		{			
			F_Uc_Roid_Enc_Memony[F_In_Roid_Enc_Count] = 0x7f & F_Ui_Roid_Enc;
			if(F_In_Roid_Enc_Count)
				F_Uc_Roid_Enc_Memony[F_In_Roid_Enc_Count] |= 0x80; /* Set bit 7 to 1 if not first byte */
			F_Ui_Roid_Enc = F_Ui_Roid_Enc>>7;
			F_In_Roid_Enc_Count++;
			
		}while(F_Ui_Roid_Enc);
		
		F_In_Roid_Enc_Temp_Count = F_In_Roid_Enc_Count; 
		F_In_Roid_Enc_Count = F_In_Roid_Save_Count+F_In_Roid_Enc_Count;
		
        for (F_In_Roid_Enc_Temp_Count--;F_In_Roid_Save_Count<F_In_Roid_Enc_Count;F_In_Roid_Save_Count++)
		{			
			
            F_Uc_Roid_Save_Memony[F_In_Roid_Save_Count] = F_Uc_Roid_Enc_Memony[F_In_Roid_Enc_Temp_Count];
			//printf("%02x\n",F_Uc_Roid_Save_Memony[F_In_Roid_Save_Count]); //use test
            F_In_Roid_Enc_Temp_Count--;
		}//form save temp memory to save memory;
		
        free(F_Uc_Roid_Enc_Memony);
		F_Ui_Roid_Subid++;
   	}
	
	
	if (F_In_Roid_Save_Count > ws->buffer.end - ws->buffer.current)
	{
		wsmemory = ((ws->buffer.end - ws->buffer.data)+10);
		wsmemory_sub = (ws->buffer.end - ws->buffer.current);
		
		ws->buffer.data = (ASNUINT8*)mpool_realloc(ws->Pmemory,ws->buffer.data,
			wsmemory*sizeof(ASNUINT8));
		ws->buffer.end = ws->buffer.data+ wsmemory;
		if (wsmemory_sub)
		{
			ws->buffer.current = ws->buffer.end - 10 - wsmemory_sub;
		}
		else
		{
			ws->buffer.current = ws->buffer.end - 10 + wsmemory_sub;
		}
	}
    
	while (sever_flag)
	{	
		sever_flag = ASN1_PER_Enc_SeverLength(ws,&F_In_Roid_Save_Count,NULL,
			&process_length,UNALIGN);
		ASN1_FillBuffer(ws,F_Uc_Roid_Save_Memony,8*process_length,UNALIGN);
	}
	
	free(F_Uc_Roid_Save_Memony);
	//printf("%d",F_In_Roid_Save_Count); //use test
    return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_RELATIVE_OID(ASN1WorkSpace* ws, RELATIVE_OID* value,Asn1ConsInfo *consinfo)
{
	ASNINT32 F_In_Dec_Count = 0; //roid decode count log
	ASNINT32 F_In_Dec_Loop_Count = 0;    
	ASNUINT32 sever_flag=1;
	ASNUINT8 *F_Uc_Oid_Save_Memony;
	struct PER_Flag flag;
	
	sever_flag = ASN1_PER_Dec_SeverLength(ws,NULL,&flag,UNALIGN);
	if(0>sever_flag)
		return ASN1_PER_CHECK_LENGTH_ERROR;
	F_Uc_Oid_Save_Memony = malloc(flag.PER_Dec_Len*sizeof(ASNUINT8));
	if(0>ASN1_ReadBuffer(ws,F_Uc_Oid_Save_Memony,8*flag.PER_Dec_Len,UNALIGN))
		return ASN1_PER_CHECK_LENGTH_ERROR;
	
	while (F_In_Dec_Loop_Count < flag.PER_Dec_Len) //loop decode value
	{
		value->subid[F_In_Dec_Count] = 0;
		
		while (*F_Uc_Oid_Save_Memony & 0x80)
		{
			value->subid[F_In_Dec_Count] += *(F_Uc_Oid_Save_Memony) & 0x7f;
			value->subid[F_In_Dec_Count] <<= 7;
			F_In_Dec_Loop_Count++;
			F_Uc_Oid_Save_Memony++;
		}
		value->subid[F_In_Dec_Count] += *(F_Uc_Oid_Save_Memony);
		
		F_Uc_Oid_Save_Memony++;
		F_In_Dec_Loop_Count++;
		F_In_Dec_Count++;
	}
	value->numids = F_In_Dec_Count;
	return 0;
}




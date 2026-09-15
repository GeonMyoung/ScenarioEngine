#include "ASN1_PER_OBJECTIDENTIFIER.h"

#ifdef WIN32
#pragma warning(disable:4018)
#endif

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_OBJECTIDENTIFIER(ASN1WorkSpace* ws, OBJECTIDENTIFIER* value,Asn1ConsInfo *consinfo)
{
	ASNUINT32 F_Ui_Oid_Subid = 1; //array number log
	ASNUINT32 F_Ui_Oid_Enc = 0;   //will encode value
	ASNINT32 F_In_Oid_Save_Count =0; //save memory count log    
	ASNINT32 F_In_Oid_Enc_Count; //encode count
	ASNINT32 F_In_Oid_Enc_Temp_Count;//save temp encode count
	ASNINT32 F_In_Oid_Save_Memony = 10; //memory save size
	ASNINT32 F_In_Oid_Enc_Memony = 10; //temp buffer size
    ASNUINT8* F_Uc_Oid_Enc_Memony;  //memory save poASNINT32er
	ASNUINT8* F_Uc_Oid_Save_Memony; //memory temp buffer poASNINT32er
	ASNINT32 wsmemory = 0;
	ASNINT32 wsmemory_sub = 0;
	ASNUINT32 subid_value;
	ASNUINT32 process_length;
	ASNUINT32 sever_flag=1;
	
	if (value->numids<2)
	{
		return -406;
	}
	subid_value = value->subid[1];
	value->subid[1] = (value->subid[0]*40)+value->subid[1];
	
	F_Uc_Oid_Save_Memony = 
		(ASNUINT8*)malloc(F_In_Oid_Save_Memony*sizeof(ASNUINT8));
	
	while (F_Ui_Oid_Subid < value->numids) 
	{
		F_In_Oid_Enc_Count = 0;
		F_Ui_Oid_Enc = value->subid[F_Ui_Oid_Subid];//get encode value
        F_Uc_Oid_Enc_Memony = 
			(ASNUINT8*)malloc(F_In_Oid_Enc_Memony*sizeof(ASNUINT8));
		
		do
		{
			if(F_In_Oid_Enc_Count == F_In_Oid_Enc_Memony)
			{
				F_In_Oid_Enc_Memony+=10;
				F_Uc_Oid_Enc_Memony = 
					(ASNUINT8*)realloc(F_Uc_Oid_Enc_Memony,F_In_Oid_Enc_Memony*sizeof(char));
			}//if save memory full,reset save memory
			
			F_Uc_Oid_Enc_Memony[F_In_Oid_Enc_Count] = 0x7f & F_Ui_Oid_Enc;
			if(F_In_Oid_Enc_Count)
				F_Uc_Oid_Enc_Memony[F_In_Oid_Enc_Count]|= 0x80;
			F_Ui_Oid_Enc = F_Ui_Oid_Enc>>7;
			F_In_Oid_Enc_Count++;
		}while(F_Ui_Oid_Enc != 0);
		
		F_In_Oid_Enc_Temp_Count = F_In_Oid_Enc_Count; 
		F_In_Oid_Enc_Count = F_In_Oid_Save_Count+F_In_Oid_Enc_Count;
		
        for (F_In_Oid_Enc_Temp_Count--;F_In_Oid_Save_Count<F_In_Oid_Enc_Count;F_In_Oid_Save_Count++)
		{
			
			if (F_In_Oid_Save_Count == F_In_Oid_Save_Memony)
			{
				F_In_Oid_Save_Memony+=10;
				F_Uc_Oid_Save_Memony = 
					(ASNUINT8*)realloc(F_Uc_Oid_Save_Memony,F_In_Oid_Save_Memony*sizeof(ASNUINT8));
			}
            F_Uc_Oid_Save_Memony[F_In_Oid_Save_Count] = F_Uc_Oid_Enc_Memony[F_In_Oid_Enc_Temp_Count];
			//printf("%02x\n",F_Uc_Oid_Save_Memony[F_In_Oid_Save_Count]); //use test
            F_In_Oid_Enc_Temp_Count--;
		}//form save temp memory to save memory;
		
        free(F_Uc_Oid_Enc_Memony);
		F_Ui_Oid_Subid++;
   	}

	while (sever_flag)
	{	
		sever_flag = ASN1_PER_Enc_SeverLength(ws,&F_In_Oid_Save_Count,NULL,
			&process_length,ALIGN);
		ASN1_FillBuffer(ws,F_Uc_Oid_Save_Memony,8*process_length,ALIGN);
	}
	
	value->subid[1] = subid_value;
	free(F_Uc_Oid_Save_Memony);
	//printf("%d",F_In_Oid_Save_Count); //use test
    return 0;
	
}


ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_OBJECTIDENTIFIER(ASN1WorkSpace* ws, OBJECTIDENTIFIER* value,Asn1ConsInfo *consinfo)
{

	struct PER_Flag flag;
	ASNINT32 F_Temp_Count = 1;
	ASNUINT32 F_Loop_Count = 0;
//	ASNUINT32 subid_value;
//	ASNUINT32 process_length;
	ASNUINT32 sever_flag=1;
	ASNUINT8 *F_Uc_Oid_Save_Memony;
	
	sever_flag = ASN1_PER_Dec_SeverLength(ws,NULL,&flag,ALIGN);
	if(0>sever_flag)
		return ASN1_PER_CHECK_LENGTH_ERROR;

	F_Uc_Oid_Save_Memony = mpool_malloc(ws->Pmemory,flag.PER_Dec_Len*sizeof(ASNUINT8));
	if(0>ASN1_ReadBuffer(ws,F_Uc_Oid_Save_Memony,8*flag.PER_Dec_Len,ALIGN))
		return ASN1_PER_CHECK_LENGTH_ERROR;
	

	while(F_Loop_Count < flag.PER_Dec_Len) // loop decode value
	{
		value->subid[F_Temp_Count] = 0;
		while (((*F_Uc_Oid_Save_Memony) & 0x80) ==0x80)
		{
			value->subid[F_Temp_Count] += *(F_Uc_Oid_Save_Memony) & 0x7f;
			value->subid[F_Temp_Count] <<= 7;
			F_Uc_Oid_Save_Memony++;
			F_Loop_Count++;
		}
		value->subid[F_Temp_Count] += *(F_Uc_Oid_Save_Memony);
		F_Uc_Oid_Save_Memony++;
		F_Loop_Count++;
		F_Temp_Count++;
		
	}
	value->numids = F_Temp_Count;
	value->subid[0] = (value->subid[1])/40; //decode first value
	value->subid[1] = (value->subid[1])%40;//decode second value
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_OBJECTIDENTIFIER(ASN1WorkSpace* ws, OBJECTIDENTIFIER* value,Asn1ConsInfo *consinfo)
{
	ASNUINT32 F_Ui_Oid_Subid = 1; //array number log
	ASNUINT32 F_Ui_Oid_Enc = 0;   //will encode value
	ASNINT32 F_In_Oid_Save_Count =0; //save memory count log    
	ASNINT32 F_In_Oid_Enc_Count; //encode count
	ASNINT32 F_In_Oid_Enc_Temp_Count;//save temp encode count
	ASNINT32 F_In_Oid_Save_Memony = 10; //memory save size
	ASNINT32 F_In_Oid_Enc_Memony = 10; //temp buffer size
    ASNUINT8* F_Uc_Oid_Enc_Memony;  //memory save poASNINT32er
	ASNUINT8* F_Uc_Oid_Save_Memony; //memory temp buffer poASNINT32er
	ASNINT32 wsmemory = 0;
	ASNINT32 wsmemory_sub = 0;
	ASNUINT32 subid_value;
	ASNUINT32 process_length;
	ASNUINT32 sever_flag=1;
	
	if (value->numids<2)
	{
		return -406;
	}
	subid_value = value->subid[1];
	value->subid[1] = (value->subid[0]*40)+value->subid[1];
	
	F_Uc_Oid_Save_Memony = 
		(ASNUINT8*)malloc(F_In_Oid_Save_Memony*sizeof(ASNUINT8));
	
	while (F_Ui_Oid_Subid < value->numids) 
	{
		F_In_Oid_Enc_Count = 0;
		F_Ui_Oid_Enc = value->subid[F_Ui_Oid_Subid];//get encode value
        F_Uc_Oid_Enc_Memony = 
			(ASNUINT8*)malloc(F_In_Oid_Enc_Memony*sizeof(ASNUINT8));
		
		do
		{
			if(F_In_Oid_Enc_Count == F_In_Oid_Enc_Memony)
			{
				F_In_Oid_Enc_Memony+=10;
				F_Uc_Oid_Enc_Memony = 
					(ASNUINT8*)realloc(F_Uc_Oid_Enc_Memony,F_In_Oid_Enc_Memony*sizeof(char));
			}//if save memory full,reset save memory
			
			F_Uc_Oid_Enc_Memony[F_In_Oid_Enc_Count] = 0x7f & F_Ui_Oid_Enc;
			if(F_In_Oid_Enc_Count)
				F_Uc_Oid_Enc_Memony[F_In_Oid_Enc_Count]|= 0x80;
			F_Ui_Oid_Enc = F_Ui_Oid_Enc>>7;
			F_In_Oid_Enc_Count++;
		}while(F_Ui_Oid_Enc != 0);
		
		F_In_Oid_Enc_Temp_Count = F_In_Oid_Enc_Count; 
		F_In_Oid_Enc_Count = F_In_Oid_Save_Count+F_In_Oid_Enc_Count;
		
        for (F_In_Oid_Enc_Temp_Count--;F_In_Oid_Save_Count<F_In_Oid_Enc_Count;F_In_Oid_Save_Count++)
		{
			
			if (F_In_Oid_Save_Count == F_In_Oid_Save_Memony)
			{
				F_In_Oid_Save_Memony+=10;
				F_Uc_Oid_Save_Memony = 
					(ASNUINT8*)realloc(F_Uc_Oid_Save_Memony,F_In_Oid_Save_Memony*sizeof(ASNUINT8));
			}
            F_Uc_Oid_Save_Memony[F_In_Oid_Save_Count] = F_Uc_Oid_Enc_Memony[F_In_Oid_Enc_Temp_Count];
			//printf("%02x\n",F_Uc_Oid_Save_Memony[F_In_Oid_Save_Count]); //use test
            F_In_Oid_Enc_Temp_Count--;
		}//form save temp memory to save memory;
		
        free(F_Uc_Oid_Enc_Memony);
		F_Ui_Oid_Subid++;
   	}
	
	while (sever_flag)
	{	
		sever_flag = ASN1_PER_Enc_SeverLength(ws,&F_In_Oid_Save_Count,NULL,
			&process_length,UNALIGN);
		ASN1_FillBuffer(ws,F_Uc_Oid_Save_Memony,8*process_length,UNALIGN);
	}
	
	value->subid[1] = subid_value;
	free(F_Uc_Oid_Save_Memony);
	//printf("%d",F_In_Oid_Save_Count); //use test
    return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_OBJECTIDENTIFIER(ASN1WorkSpace* ws, OBJECTIDENTIFIER* value,Asn1ConsInfo *consinfo)
{
	struct PER_Flag flag;
	ASNINT32 F_Temp_Count = 1;
	ASNINT32 F_Loop_Count = 0;
	ASNUINT32 sever_flag=1;
	ASNUINT8 *F_Uc_Oid_Save_Memony;
	
	sever_flag = ASN1_PER_Dec_SeverLength(ws,NULL,&flag,UNALIGN);
	if(0>sever_flag)
		return ASN1_PER_CHECK_LENGTH_ERROR;
	F_Uc_Oid_Save_Memony = mpool_malloc(ws->Pmemory,flag.PER_Dec_Len*sizeof(ASNUINT8));
	if(0>ASN1_ReadBuffer(ws,F_Uc_Oid_Save_Memony,8*flag.PER_Dec_Len,UNALIGN))
		return ASN1_PER_CHECK_LENGTH_ERROR;
	
	
	while(F_Loop_Count < flag.PER_Dec_Len) // loop decode value
	{
		value->subid[F_Temp_Count] = 0;
		while (((*F_Uc_Oid_Save_Memony) & 0x80) ==0x80)
		{
			value->subid[F_Temp_Count] += *(F_Uc_Oid_Save_Memony) & 0x7f;
			value->subid[F_Temp_Count] <<= 7;
			F_Uc_Oid_Save_Memony++;
			F_Loop_Count++;
		}
		value->subid[F_Temp_Count] += *(F_Uc_Oid_Save_Memony);
		F_Uc_Oid_Save_Memony++;
		F_Loop_Count++;
		F_Temp_Count++;
		
	}
	value->numids = F_Temp_Count;
	value->subid[0] = (value->subid[1])/40; //decode first value
	value->subid[1] = (value->subid[1])%40;//decode second value
	return 0;
}



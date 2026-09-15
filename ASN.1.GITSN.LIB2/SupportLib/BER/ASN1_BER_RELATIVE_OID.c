#include "ASN1_BER_RELATIVE_OID.h"

/************************************************
function_name:ASN1_BER_Enc_RELATIVE_OID                              
input:
     ASN1WorkSpace* ws: data save and work space
	 RELATIVE_OID* value: will encoding value 
	 ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                    
return:
     ASNINT32: if return 0 succeed else error                                    
description:
     creat encode a value of RELATIVE-OID struct                                  
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_RELATIVE_OID(ASN1WorkSpace* ws,RELATIVE_OID* value,ASN1TagType flag)
{
	ASN1_Tag_Move_Pointer(ws,ASN1_TYPE_RELATIVEOID,flag);
	ASN1_BER_Enc_RELATIVE_OID_Value(ws,value);
	return 0;
}

/************************************************
function_name:ASN1_BER_Dec_RELATIVE_OID                              
input:
      ASN1WorkSpace* ws: data save and work space
      RELATIVE_OID* value: take over dcoded value
      ASN1TagType flag: encoding Tag Type(example: EXPLICIT or IMPLICIT)                                   
return:
      ASNINT32: if return 0 succeed else error                                     
description:
      creat decode a string of RELATIVE-OID struct                                  
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_RELATIVE_OID(ASN1WorkSpace* ws,RELATIVE_OID* value,
						   ASNINT32 length,ASN1TagType flag)
{
    if (flag == ASN1EXPL || flag == UNASN1IMEXPL)
    {
		ASN1_BER_Dec_Tag(ws,ITS_ASN_UNIV|ITS_ASN_PRIM|13);
		ASN1_BER_Dec_Length(ws);
	    ASN1_BER_Dec_RELATIVE_OID_Value(ws,value,ws->dataSize);
    }
	else
	//ASN_BER_Dec_Length(ws);
	ASN1_BER_Dec_RELATIVE_OID_Value(ws,value,length);
	return 0;
}

/************************************************
function_name:ASN1_BER_Enc_RELATIVE_OID_Value                              
input:
     ASN1WorkSpace* ws: data save and work space
	 RELATIVE_OID* value: will encoding value                                   
return:
     ASNINT32: if return 0 succeed else error                                    
description:
     creat encode a value of RELATIVE-OID struct                                  
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_RELATIVE_OID_Value(ASN1WorkSpace* ws, RELATIVE_OID* value) //encode function
{
	ASNUINT32 F_Ui_RELATIVE_OID_Subid = 0; //array number log
	ASNUINT32 F_Ui_RELATIVE_OID_Enc = 0;   //will encode value
	ASNINT32 F_In_RELATIVE_OID_Save_Count =0; //save memory count log    
	ASNINT32 F_In_RELATIVE_OID_Enc_Count; //encode count
	ASNINT32 F_In_RELATIVE_OID_Enc_Temp_Count;//save temp encode count
	ASNINT32 F_In_RELATIVE_OID_Save_Memony = 10; //memory save size
	ASNINT32 F_In_RELATIVE_OID_Enc_Memony = 10; //temp buffer size
    ASNUINT8* F_Uc_RELATIVE_OID_Enc_Memony;  //memory save poASNINT32er
	ASNUINT8* F_Uc_RELATIVE_OID_Save_Memony; //memory temp buffer poASNINT32er
	ASNINT32 wsmemory = 0;
	ASNINT32 wsmemory_sub = 0;
	
	F_Uc_RELATIVE_OID_Save_Memony = 
		(ASNUINT8*)malloc(F_In_RELATIVE_OID_Save_Memony*sizeof(ASNUINT8));
	
	while (F_Ui_RELATIVE_OID_Subid < value->numids) 
	{
		F_In_RELATIVE_OID_Enc_Count = 0;
		F_Ui_RELATIVE_OID_Enc = value->subid[F_Ui_RELATIVE_OID_Subid];//get encode value
        F_Uc_RELATIVE_OID_Enc_Memony = 
		(ASNUINT8*)malloc(F_In_RELATIVE_OID_Enc_Memony*sizeof(ASNUINT8));
		
		do
		{
			if(F_In_RELATIVE_OID_Enc_Count == F_In_RELATIVE_OID_Enc_Memony)
			{
				F_In_RELATIVE_OID_Enc_Memony+=10;
			    ASN1_BER_Reset_Memory(F_In_RELATIVE_OID_Enc_Memony,&F_Uc_RELATIVE_OID_Enc_Memony);
			}//if save memory full,reset save memory
			
			F_Uc_RELATIVE_OID_Enc_Memony[F_In_RELATIVE_OID_Enc_Count] = 0x7f & F_Ui_RELATIVE_OID_Enc;
			if(F_In_RELATIVE_OID_Enc_Count)
				F_Uc_RELATIVE_OID_Enc_Memony[F_In_RELATIVE_OID_Enc_Count] |= 0x80; /* Set bit 7 to 1 if not first byte */
 			F_Ui_RELATIVE_OID_Enc = F_Ui_RELATIVE_OID_Enc>>7;
			F_In_RELATIVE_OID_Enc_Count++;

		}while(F_Ui_RELATIVE_OID_Enc);
		
		F_In_RELATIVE_OID_Enc_Temp_Count = F_In_RELATIVE_OID_Enc_Count; 
		F_In_RELATIVE_OID_Enc_Count = F_In_RELATIVE_OID_Save_Count+F_In_RELATIVE_OID_Enc_Count;
		
        for (F_In_RELATIVE_OID_Enc_Temp_Count--;F_In_RELATIVE_OID_Save_Count<F_In_RELATIVE_OID_Enc_Count;F_In_RELATIVE_OID_Save_Count++)
		{
			
			if (F_In_RELATIVE_OID_Save_Count == F_In_RELATIVE_OID_Save_Memony)
			{
				F_In_RELATIVE_OID_Save_Memony+=10;
				ASN1_BER_Reset_Memory(F_In_RELATIVE_OID_Save_Memony,&F_Uc_RELATIVE_OID_Save_Memony);
			}
            F_Uc_RELATIVE_OID_Save_Memony[F_In_RELATIVE_OID_Save_Count] = F_Uc_RELATIVE_OID_Enc_Memony[F_In_RELATIVE_OID_Enc_Temp_Count];
			//printf("%02x\n",F_Uc_RELATIVE_OID_Save_Memony[F_In_RELATIVE_OID_Save_Count]); //use test
            F_In_RELATIVE_OID_Enc_Temp_Count--;
		}//form save temp memory to save memory;
		
        free(F_Uc_RELATIVE_OID_Enc_Memony);
		F_Ui_RELATIVE_OID_Subid++;
   	}

	ASN1_BER_Enc_Length(ws,F_In_RELATIVE_OID_Save_Count);
 	if (F_In_RELATIVE_OID_Save_Count >= ws->buffer.end - ws->buffer.current)
	{
		wsmemory = ((ws->buffer.end - ws->buffer.data)+F_In_RELATIVE_OID_Save_Count);
		ASN1_RESET_WS_INFO(ws,wsmemory);
		/*
		wsmemory = ((ws->buffer.end - ws->buffer.data)+F_In_RELATIVE_OID_Save_Count);
		wsmemory_sub = (ws->buffer.end - ws->buffer.current);

		ws->buffer.data = (ASNUINT8*)mpool_realloc(ws->Pmemory,ws->buffer.data,
			wsmemory*sizeof(ASNUINT8));
		ws->buffer.end = ws->buffer.data+ wsmemory;
		if (wsmemory_sub)
		{
			ws->buffer.current = ws->buffer.end - F_In_RELATIVE_OID_Save_Count - wsmemory_sub;
		}
		else
		{
			ws->buffer.current = ws->buffer.end - F_In_RELATIVE_OID_Save_Count + wsmemory_sub;
		}
		*/
	}
		/*return -3;*/
// 		realloc();
    
	memcpy(ws->buffer.current,F_Uc_RELATIVE_OID_Save_Memony,F_In_RELATIVE_OID_Save_Count);//form save memory to workspace buffer memory
	ws->buffer.current = ws->buffer.current+F_In_RELATIVE_OID_Save_Count;
	if (ws->buffer.current == ws->buffer.end)
		return -2;

	
	free(F_Uc_RELATIVE_OID_Save_Memony);
	//printf("%d",F_In_RELATIVE_OID_Save_Count); //use test
    return 0;
}

/************************************************
function_name:ASN1_BER_Dec_RELATIVE_OID_Value                              
input:
      ASN1WorkSpace* ws: data save and work space
      RELATIVE_OID* value: take over dcoded value
      ASNINT32 length: encode length                                   
return:
      ASNINT32: if return 0 succeed else error                                     
description:
      creat decode a string of RELATIVE-OID struct                                  
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_RELATIVE_OID_Value(ASN1WorkSpace* ws, RELATIVE_OID* value,ASNINT32 length)
{
	ASNINT32 F_In_Dec_Count = 0; //roid decode count log
	ASNINT32 F_In_Dec_Loop_Count = 0;
    
	while (F_In_Dec_Loop_Count < length) //loop decode value
	{
		value->subid[F_In_Dec_Count] = 0;
		
		while (*ws->buffer.current & 0x80)
		{
			value->subid[F_In_Dec_Count] += *(ws->buffer.current) & 0x7f;
			value->subid[F_In_Dec_Count] <<= 7;
			F_In_Dec_Loop_Count++;
			ws->buffer.current++;
		}
		value->subid[F_In_Dec_Count] += *(ws->buffer.current);
		
		ws->buffer.current++;
		F_In_Dec_Loop_Count++;
		F_In_Dec_Count++;
	}
	value->numids = F_In_Dec_Count;
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_BER_Reset_Memory(ASNINT32 F_In_RELATIVE_OID_Enc_Memony,ASNUINT8** F_Uc_RELATIVE_OID_Enc_Memony)
{
	*F_Uc_RELATIVE_OID_Enc_Memony = 
	(ASNUINT8*)realloc(F_Uc_RELATIVE_OID_Enc_Memony,F_In_RELATIVE_OID_Enc_Memony*sizeof(char));
	return 0;
}

// ASNINT32 ASN1_BER_Compare_RELATIVE_OID(RELATIVE_OID* Com_one,RELATIVE_OID* Com_two)
// {
// 	ASNUINT32 F_UI_temp_count;
// 	F_UI_temp_count = Com_one->numids;
// 	
// 	if (Com_one->numids == Com_two->numids)
// 	{
// 		F_UI_temp_count--;
// 		while (F_UI_temp_count != -1)
// 		{
// 			if (Com_one->subid[F_UI_temp_count] != Com_two->subid[F_UI_temp_count])
// 				return -2;
// 			F_UI_temp_count--;
// 		}
// 		return 0;
// 	}
// 	return -1;
// }



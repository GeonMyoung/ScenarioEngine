
#include "ASN1_Tag.h"
/************************************************
function_name:ASN1_BER_Enc_UserDefTag_Indef                              
input:
     ASN1WorkSpace* ws: data save and work space
	 ASN1_Type_Info* info: encoding and decoding information struct                                    
return:
     ASNINT32: if value=0 succeed else error                                
description:
     encode a userdeftag and indef                                
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Enc_Tag_Indef(ASN1WorkSpace * ws,ASNUINT32 tag_value)
{
	ASNUINT8 asnzero[1];
	ASN1_BER_Process_Tag(ws,tag_value);
	
	asnzero[0] = 0x80;
	ASN1_BER_FillBuffer(ws,asnzero,1,0);
/*	*ws->buffer.current = 0x80;*/
	ws->buffer.current++;
	return 0;
}



/************************************************
function_name:ASN1_BER_Process_Tag                              
input:
     ASN1WorkSpace* ws: data save and work space
	 ASNUINT32 tag_value: encoding value                                    
return:
     ASNINT32: if value=0 succeed else error                                
description:
     encoding tag(ture process)                                
*************************************************/
ASNINT32 ASN1_BER_Process_Tag(ASN1WorkSpace *ws, ASNUINT32 tag_value)
{
	ASNUINT8 *F_Uc_Temp_Save_First_Tag;
	ASNUINT8 *F_Uc_Temp_Save_Other_Tag;
	int F_In_Save_Count = 0, F_In_Enc_Count = 0;
	
	F_Uc_Temp_Save_First_Tag = (ASNUINT8 *)ASN1_MALLOC(sizeof(ASNUINT8));
	memset(F_Uc_Temp_Save_First_Tag, 0, 1);
	
	(*F_Uc_Temp_Save_First_Tag) = tag_value & ITS_ASN_NUMBER;	//get value
	
	if(*F_Uc_Temp_Save_First_Tag < 31)
	{	// simple TAG
        ASN1_BER_Process_Tag_Class(tag_value, F_Uc_Temp_Save_First_Tag);
		ASN1_BER_FillBuffer(ws, F_Uc_Temp_Save_First_Tag, 1, 0);
		ws->buffer.current++;
		free(F_Uc_Temp_Save_First_Tag);
	}
	else
	{
// 		*F_Uc_Temp_Save_First_Tag = 0;
// 		*F_Uc_Temp_Save_First_Tag = *F_Uc_Temp_Save_First_Tag | 0x1f;
		*F_Uc_Temp_Save_First_Tag = 0x1F;

        ASN1_BER_Process_Tag_Class(tag_value, F_Uc_Temp_Save_First_Tag);
		ASN1_BER_FillBuffer(ws, F_Uc_Temp_Save_First_Tag, 1, 0);
		ws->buffer.current++;
		
		tag_value = tag_value & ITS_ASN_NUMBER;
		F_In_Save_Count = F_In_Save_Count + 10;
		F_Uc_Temp_Save_Other_Tag = (ASNUINT8 *)malloc(F_In_Save_Count * sizeof(ASNUINT8));
		
		do 
		{
			if (F_In_Enc_Count == F_In_Save_Count)
			{
				F_In_Save_Count = F_In_Save_Count + 10;
                F_Uc_Temp_Save_Other_Tag = (ASNUINT8 *)realloc(F_Uc_Temp_Save_Other_Tag, F_In_Save_Count * sizeof(ASNUINT8));
			}

			F_Uc_Temp_Save_Other_Tag[F_In_Enc_Count] = 0x7f & tag_value;
			if (F_In_Enc_Count) F_Uc_Temp_Save_Other_Tag[F_In_Enc_Count] |= 0x80;
			tag_value >>= 7;
			F_In_Enc_Count++;
		} while(tag_value);
		
		for(F_In_Enc_Count--; F_In_Enc_Count >= 0; F_In_Enc_Count--)
		{
			ASN1_BER_FillBuffer(ws, &F_Uc_Temp_Save_Other_Tag[F_In_Enc_Count], 1, 0);
            ws->buffer.current++;
		}
		free(F_Uc_Temp_Save_Other_Tag);
	}
	return 0;
}

/************************************************
function_name:ASN1_BER_Process_Tag_Class                              
input:
     ASNUINT32 tagvalue:encode value
	 ASNUINT8* tag_class: frist tag value                                   
return:
     ASNINT32: if value=0 succeed else error                                
description:
     encode tag class and c/s                               
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_BER_Process_Tag_Class(ASNUINT32 tagvalue ,ASNUINT8* tag_class)
{
	ASNUINT32 F_Ui_Tag_Value; //save temp value
	F_Ui_Tag_Value = tagvalue&ITS_ASN_LTABLE;
	switch(F_Ui_Tag_Value) //get class value
	{
	case ITS_ASN_UNIV:
		*tag_class = *tag_class|0x00;
		break;
	case ITS_ASN_APPL:
		*tag_class = *tag_class|0x40;
		break;
	case ITS_ASN_CONT:
		*tag_class = *tag_class|0x80;
		break;
	case ITS_ASN_PRIV:
		*tag_class = *tag_class|0xc0;
		break;
	}
	
	F_Ui_Tag_Value = tagvalue&ITS_ASN_PRCON;
	switch(F_Ui_Tag_Value)//get c/s ?
	{
	case ITS_ASN_PRIM:
		*tag_class = *tag_class|0x00;
		break;
	case ITS_ASN_CONS:
		*tag_class = *tag_class|0x20;
		break;
	}
	return 0;
}

/************************************************
function_name:ASN1_Dec_Tag_Value                              
input:
     ASNUINT32 tagvalue:encode value
	 ASNUINT8* tag_class: frist tag value                                   
return:
     ASNINT32: if value=0 succeed else error                               
description:
     encode tag class and c/s                               
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_Dec_Tag_Value(ASN1WorkSpace * ws)
{
    ASNUINT8* F_Temp_Tag;
	F_Temp_Tag = ws->buffer.current;
	if ((*ws->buffer.current & 0x1f) == 0x1f)
	{
		ws->buffer.current++;
		while (((*(ws->buffer.current))& 0x80) != 0x00)
		{
			ws->buffer.current++;
		}
        ws->buffer.current++;
		ASN1_Dec_Tag_Indef(ws,F_Temp_Tag);
	}
	else
	{
		ws->buffer.current++;
		ASN1_Dec_Tag_Indef(ws,F_Temp_Tag);
	}
	return 0;
}

/************************************************
function_name:ASN1_Dec_Tag_Indef                              
input:
     ASNUINT32 tagvalue:encode value
	 ASNUINT8* tag_class: frist tag value                                   
return:
     ASNINT32: if value=0 succeed else error                                
description:
     encode tag class and c/s                               
*************************************************/
ASN1_CPPLINK ASNINT32 ASN1_Dec_Tag_Indef(ASN1WorkSpace * ws,unsigned char* Temp_Tag)
{
	if(*ws->buffer.current == 0x80)
	{
		ws->buffer.current++;
	    ASN1_Dec_Tag_Value(ws);
	}
	else if ((*Temp_Tag & 0x20) == 0x20)
	{
		ASN1_BER_Dec_Length(ws);
		ASN1_Dec_Tag_Value(ws);
	}
	return 0;
}

/************************************************
function_name:ASN1_Tag_Move_Pointer                              
input:
     ASN1WorkSpace* ws:data save and work space 
	 ASNUINT8 tag_class: tag value
	 ASN1TagType flag:tag type
return:
     ASNINT32: if value=0 succeed else error                               
description:
     if flag = ASN1IMPL move pointer                               
*************************************************/
ASNINT32 ASN1_Tag_Move_Pointer(ASN1WorkSpace *ws, ASNUINT32 tag_value, ASN1TagType flag)
{
	if (flag == ASN1EXPL || flag == UNASN1IMEXPL)
		ASN1_BER_Process_Tag(ws,tag_value);
	else ws->buffer.current -= 1;

	return 0;
}
/************************************************
function_name:ASN1_Dec_Tag_Process                              
input:
     ASN1WorkSpace* ws:data save and work space 
	 ASNUINT8 tag_class: tag value
	 ASN1TagType flag:tag type
return:
     ASNINT32: if value=0 succeed else error                               
description:
     if flag = ASN1IMPL move pointer                               
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_Dec_Tag_Compare(ASN1WorkSpace* ws,ASNUINT32 tagValue,ASNUINT8 *TagClass)
{
	ASNUINT32 F_Temp_Tag_Class = 0;
	ASNUINT32 F_Temp_Tag_Value = 0;
	ASNUINT8* tagcurrent = ws->buffer.current;
	*TagClass = *ws->buffer.current;
	
    F_Temp_Tag_Class += ((*ws->buffer.current)>>5);
	F_Temp_Tag_Class <<= 29;
	
	if ((*tagcurrent & 0x1f) == 0x1f)
	{
		tagcurrent++;
		while (*tagcurrent & 0x80)
		{
			
			F_Temp_Tag_Value += *tagcurrent & 0x7f;
            F_Temp_Tag_Value <<= 7;
			tagcurrent++;
		}	
		F_Temp_Tag_Value += *tagcurrent;
		tagcurrent++;
	}

	else
	{
		F_Temp_Tag_Value += ((*tagcurrent) & 0x1f);
		tagcurrent++;
	}

	F_Temp_Tag_Value |= F_Temp_Tag_Class;
    
	if ((F_Temp_Tag_Value & 0xDFFFFFFF) != (tagValue & 0xDFFFFFFF)) //  one|two|three one and three compare
	{
		return -1;
	}
	ws->buffer.current = tagcurrent;
    return 0;
}

/************************************************
function_name:ASN1_BER_Dec_User_Tag                              
input:
     ASN1WorkSpace* ws:data save and work space 
	 ASNUINT8 tag_class: tag value
	 ASN1TagType flag:tag type
return:
     ASNINT32: if value=0 succeed else error                               
description:
     if flag = ASN1IMPL move pointer                               
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_User_Dec_Tag(ASN1WorkSpace* ws,ASNINT32 tagvalue)
{
	ASNUINT8 Temp_Tagvalue = 0;
	if (0 > ASN1_Dec_Tag_Compare(ws,tagvalue,&Temp_Tagvalue))
	{
		return -1;
	}

// 	if (flag == ASN1EXPL || flag == UNASN1IMEXPL)
// 	{
// 		ASN_BER_Dec_Length(ws);*/
//  		if (-1 == ws->dataSize)
//  		{
//  			*indef = -1;
//  
//  		}
// 	}

	if ((Temp_Tagvalue & 0x20) == 0x20)
		{
			ws->iscons = -3; //cons ASN1IMPL
// 			if (*ws->buffer.current == 0x80)
// 			{
// 				*indef = -1;
// 			}
			return 0;
		}
		else
		{
			ws->iscons = -2;//prim ASN1IMPL
		}

    return 0;
	
}

	


/************************************************
function_name:ASN1_BER_Dec_Tag                              
input:
     ASN1WorkSpace* ws:data save and work space 
	 ASNUINT8 tag_class: tag value
	 ASN1TagType flag:tag type
return:
     ASNINT32: if value=0 succeed else error                               
description:
     if flag = ASN1IMPL move pointer                               
*************************************************/

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_Tag(ASN1WorkSpace*ws,ASNINT32 tagvalue)
{
	ASNUINT8 Temp_Tagvalue = 0;
	if (0 > ASN1_Dec_Tag_Compare(ws, tagvalue, &Temp_Tagvalue))
	{
		return -1;
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_BER_GET_Tag(ASN1WorkSpace *ws,ASNUINT32* Tagvalue)
{
	ASNUINT32 F_Temp_Tag_Class = 0;
	ASNUINT32 F_Temp_Tag_Value = 0;
	ASNUINT8 *TagClass = ws->buffer.current;
    
	F_Temp_Tag_Class += ((*TagClass)>>5);// set class one two three
	F_Temp_Tag_Class <<= 29;
	
	if ((*TagClass & 0x1f) == 0x1f)
	{
		TagClass++;
		while (*TagClass & 0x80)
		{
			F_Temp_Tag_Value += (*TagClass) & 0x7f;
            F_Temp_Tag_Value <<= 7;
			TagClass++;
		}	
		F_Temp_Tag_Value += *TagClass;
		TagClass++;
	}
	
	else
	{
		F_Temp_Tag_Value += ((*TagClass) & 0x1f);
		TagClass++;
	}
	
	F_Temp_Tag_Value |= F_Temp_Tag_Class;
	*Tagvalue = F_Temp_Tag_Value;
	return 0;

}


ASN1_CPPLINK ASNINT32 ASN1_BER_OpenType_Tag(ASN1WorkSpace *ws)
{
	if ((*ws->buffer.current & 0x1f) == 0x1f)
	{
		ws->buffer.current++;
		while (((*(ws->buffer.current))& 0x80) != 0x00)
		{
			ws->buffer.current++;
		}
        ws->buffer.current++;
        return 0;
	}
	else
	ws->buffer.current++;
    return 0;

}


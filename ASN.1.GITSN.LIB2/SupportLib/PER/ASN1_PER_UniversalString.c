#include "ASN1_PER_UniversalString.h"

/*UniversalString*/

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_UniversalString(ASN1WorkSpace *ws,UniversalString *value,
									  Asn1ConsInfo *consinfo)
{
	ASNINT32 ret = 0;
	consinfo->charSet = NULL;
	ret = ASN1_PER_Align_Enc_UNI_Process(ws,value,consinfo,UCS_ABITS);
	if (ret < 0){
		return ret;
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_UniversalString(ASN1WorkSpace *ws,UniversalString *value,
										Asn1ConsInfo *consinfo)
{
	ASNINT32 ret = 0;
	consinfo->charSet = NULL;
	ret = ASN1_PER_UNAlign_Enc_UNI_Process(ws,value,consinfo,UCS_UBITS);
	if (ret < 0){
		return ret;
	}
	return 0;

}

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_UniversalString(ASN1WorkSpace *ws,UniversalString *value,
									  Asn1ConsInfo *consinfo)
{
	ASNINT32 ret;
	consinfo->charSet = NULL;
	ret = ASN1_PER_Align_Dec_UNI_Process(ws,value,consinfo,UCS_ABITS);
	if (ret<0){
		return ret;
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_UniversalString(ASN1WorkSpace* ws,UniversalString* value, 
										Asn1ConsInfo *consinfo)
{
	ASNINT32 ret;
	consinfo->charSet = NULL;
	ret = ASN1_PER_UNAlign_Dec_UNI_Process(ws,value,consinfo,UCS_UBITS);
	if (ret<0){
		return ret;
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_UNI_Process(ASN1WorkSpace *ws,UniversalString *value,
										Asn1ConsInfo *consinfo,ASNINT32 Default_bit)

{
	struct PER_Flag per_flag;
	ASN1PERAlign align_flag;
	ASNUINT8 zero;
	ASNINT32 sever_flag = 1;
	ASNINT32 temp_value_length;
	ASNUINT32 process_length = 0;
	ASNINT32 ret = 0;
	ASNUINT32* temp_value = value->data;
	
	per_flag.Range = 0;
	per_flag.Value_length = value->nchar;/*strlen(value->asnstring);*/
	if (consinfo->charSet == NULL){
		per_flag.Char_set_length = 0;
	}
	else{
		per_flag.Char_set_length = (ASNINT32)strlen(consinfo->charSet);
	}
	
	ret = PER_CONSTRAINT_Enc_Process(ws,consinfo,&Default_bit,&per_flag,ALIGN);
	if (ret<0){
		return ret;
	}
	
	if ((per_flag.ext_flag == 1)&&(per_flag.Value_length >= 16384)){
		
		temp_value_length = per_flag.Value_length;
		while (sever_flag)
		{	
			sever_flag = ASN1_PER_Enc_SeverLength(ws,&temp_value_length,consinfo,
				&process_length,ALIGN);
			ASN1_PER_Enc_UNI_Value(ws,value,process_length,
				Default_bit,&per_flag,UNALIGN);
		}
		if (per_flag.Value_length!=0 && (per_flag.Value_length % 16384) == 0){
			zero = 0x00;
			ASN1_FillBuffer(ws,&zero,8,ALIGN);
		}

		value->data = temp_value;
		return 0;
	}
	
	if(per_flag.Range == 1 && per_flag.L_En_Flag == 0){
		if (consinfo->extflag == 1){
			align_flag = UNALIGN;
			if (per_flag.ext_flag == 1){
				align_flag = ALIGN;
				ASN1_PER_Enc_ExtLength(ws,per_flag.Value_length,consinfo,&per_flag,ALIGN);
			}
		}
		else{
			align_flag = ALIGN;
		}
		ASN1_PER_Enc_UNI_Value(ws,value,per_flag.Value_length,
			Default_bit,&per_flag,align_flag);

		value->data = temp_value;
		return 0;
	}
	
	if(per_flag.Is_Size == 1){
		align_flag = ALIGN;
		if ((per_flag.Value_length <= consinfo->upper) && 
			(per_flag.Value_length >= consinfo->lower)){
			if (per_flag.Range < 256){
				align_flag = UNALIGN;
			}
		}
		
		ASN1_PER_Enc_strLength(ws,per_flag.Value_length,consinfo,&per_flag,align_flag);
		
		align_flag = ALIGN;
		if ((per_flag.Value_length <= consinfo->upper) && 
			(per_flag.Value_length >= consinfo->lower)){
			if ((consinfo->upper * Default_bit) >= 16)
				align_flag = ALIGN;
			else
				align_flag = UNALIGN;
		}
		ASN1_PER_Enc_UNI_Value(ws,value,per_flag.Value_length,
						   Default_bit,&per_flag,align_flag);
		
	}
	else{
		
		temp_value_length = per_flag.Value_length;
		while (sever_flag)
		{	
			sever_flag = ASN1_PER_Enc_SeverLength(ws,&temp_value_length,consinfo,
				&process_length,ALIGN);
			ASN1_PER_Enc_UNI_Value(ws,value,process_length,
				Default_bit,&per_flag,UNALIGN);
		}
		if (per_flag.Value_length!=0 && (per_flag.Value_length % 16384) == 0){
			zero = 0x00;
			ASN1_FillBuffer(ws,&zero,8,ALIGN);
		}
		
	}

	if (consinfo->charSet != NULL){
		free(per_flag.Alphable_table);
	}

	value->data = temp_value;
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_UNI_Process(ASN1WorkSpace *ws,UniversalString *value,
										  Asn1ConsInfo *consinfo,ASNINT32 Default_bit)
{
	struct PER_Flag per_flag;
	ASNUINT8 zero;
	ASNINT32 sever_flag = 1;
	ASNINT32 temp_value_length;
	ASNUINT32 process_length = 0;
	ASNINT32 ret = 0;
	ASNUINT32* temp_value = value->data;
	
	per_flag.Range = 0;
	per_flag.Value_length =  value->nchar;/*strlen(value->asnstring);*/
	if (consinfo->charSet == NULL){
		per_flag.Char_set_length = 0;
	}
	else{
		per_flag.Char_set_length = (ASNINT32)strlen(consinfo->charSet);
	}
	
	
	
	ret = PER_CONSTRAINT_Enc_Process(ws,consinfo,&Default_bit,&per_flag,UNALIGN);
	if (ret<0){
		return ret;
	}
	
	if ((per_flag.ext_flag == 1)&&(per_flag.Value_length >= 16384)){
		temp_value_length = per_flag.Value_length;
		while (sever_flag)
		{	
			sever_flag = ASN1_PER_Enc_SeverLength(ws,&temp_value_length,consinfo,
				&process_length,UNALIGN);
			ASN1_PER_Enc_UNI_Value(ws,value,process_length,
				Default_bit,&per_flag,UNALIGN);
		}
		if (per_flag.Value_length!=0 && (per_flag.Value_length % 16384) == 0){
			zero = 0x00;
			ASN1_FillBuffer(ws,&zero,8,UNALIGN);
		}

		value->data = temp_value;
		return 0;
	}
	
	if(per_flag.Range == 1 && per_flag.L_En_Flag == 0){
		if (per_flag.ext_flag == 1){
			ASN1_PER_Enc_ExtLength(ws,per_flag.Value_length,
				consinfo,&per_flag,UNALIGN);
		}
		ASN1_PER_Enc_UNI_Value(ws,value,per_flag.Value_length,
			Default_bit,&per_flag,UNALIGN);

		value->data = temp_value;
		return 0;
	}
	
	if(per_flag.Is_Size == 1){
		
		ASN1_PER_Enc_strLength(ws,per_flag.Value_length,consinfo,&per_flag,UNALIGN);
		ASN1_PER_Enc_UNI_Value(ws,value,per_flag.Value_length,
			Default_bit,&per_flag,UNALIGN);
		
	}
	else{
		
		temp_value_length = per_flag.Value_length;
		while (sever_flag)
		{	
			sever_flag = ASN1_PER_Enc_SeverLength(ws,&temp_value_length,consinfo,
				&process_length,UNALIGN);
			ASN1_PER_Enc_UNI_Value(ws,value,process_length,
				Default_bit,&per_flag,UNALIGN);
		}
		if (per_flag.Value_length!=0 && (per_flag.Value_length % 16384) == 0){
			zero = 0x00;
			ASN1_FillBuffer(ws,&zero,8,UNALIGN);
		}
		
	}
	if (consinfo->charSet != NULL){
		free(per_flag.Alphable_table);
	}

	value->data = temp_value;
	return 0;

}

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_UNI_Process(ASN1WorkSpace *ws,UniversalString *value,
										Asn1ConsInfo *consinfo,ASNINT32 Default_bit)
{
	struct PER_Flag per_flag;
	ASN1PERAlign align_flag;
	ASNINT32 sever_flag = 1;
	ASNINT32 temp_value_length;
	ASNUINT32 process_length = 0;
	ASNINT32 ret = 0;
	
	ASNUINT8* temp_current;
	ASNUINT16 temp_bitOffset;
	ASNINT32  temp_loop_i = 0;

	per_flag.Range = 0;

	if (consinfo->charSet == NULL){
		per_flag.Char_set_length = 0;
	}
	else{
		per_flag.Char_set_length = (ASNINT32)strlen(consinfo->charSet);
	}
	
	value->data = (ASNUINT32*)mpool_malloc(ws->Pmemory,1*sizeof(ASNUINT32));
	value->nchar = 1;
	per_flag.PER_Dec_Len = 1;

	ret = PER_CONSTRAINT_Dec_Process(ws,consinfo,&Default_bit,&per_flag,ALIGN);
	if (ret<0){
		return ASN1_PER_CHECK_LENGTH_ERROR;
	}

	if (per_flag.ext_flag == 1){
		temp_value_length = 0;
		temp_current = ws->buffer.current;
		temp_bitOffset = ws->buffer.bitOffset;

		while (sever_flag)
		{	
			temp_loop_i++;
			sever_flag = ASN1_PER_Dec_SeverLength(ws,consinfo,
				&per_flag,ALIGN);

			if(0>sever_flag)
				return ASN1_PER_CHECK_LENGTH_ERROR;

			if ((temp_loop_i == 1)&&(sever_flag == 0)){
				ws->buffer.current = temp_current;
				ws->buffer.bitOffset = temp_bitOffset;
				break;
			}

			temp_value_length += per_flag.PER_Dec_Len;
			value->nchar = temp_value_length;

			value->data = 
			mpool_realloc(ws->Pmemory,value->data,temp_value_length*sizeof(ASNUINT32));

			if(0>ASN1_PER_Dec_UNI_Value(ws,value,per_flag.PER_Dec_Len,Default_bit,&per_flag,UNALIGN))
				return ASN1_PER_CHECK_LENGTH_ERROR;

		}
		
		if (temp_loop_i != 1){
			return 0;
		}
	}
	
	if(per_flag.Range == 1 && per_flag.L_En_Flag == 0){
		if (consinfo->extflag == 1){
			align_flag = UNALIGN;
			if (per_flag.ext_flag == 1){
				align_flag = ALIGN;
				if(0>ASN1_PER_Dec_ExtLength(ws,consinfo,&per_flag,ALIGN))
					return ASN1_PER_CHECK_LENGTH_ERROR;
				value->nchar = per_flag.PER_Dec_Len;
				value->data =
				mpool_realloc(ws->Pmemory,value->data,
							  per_flag.PER_Dec_Len*sizeof(ASNUINT32));

			}
		}
		else{
			align_flag = ALIGN;
		}
		if(0>ASN1_PER_Dec_UNI_Value(ws,value,per_flag.PER_Dec_Len,
				Default_bit,&per_flag,align_flag))
				return ASN1_PER_CHECK_LENGTH_ERROR;

		return 0;
	}
	
	if(per_flag.Is_Size == 1){
		align_flag = ALIGN;
		if ((per_flag.Value_length <= consinfo->upper) && 
			(per_flag.Value_length >= consinfo->lower)){
			if (per_flag.Range < 256){
				align_flag = UNALIGN;
			}
		}
		ASN1_PER_Enc_strLength(ws,per_flag.Value_length,consinfo,&per_flag,align_flag);
		align_flag = ALIGN;
		if ((per_flag.Value_length <= consinfo->upper) && 
			(per_flag.Value_length >= consinfo->lower)){
			if ((consinfo->upper * Default_bit) >= 16)
				align_flag = ALIGN;
			else
				align_flag = UNALIGN;
		}

		value->nchar = per_flag.PER_Dec_Len;
		value->data =
		mpool_realloc(ws->Pmemory,value->data,per_flag.PER_Dec_Len*sizeof(ASNUINT32));

		if(0>ASN1_PER_Dec_UNI_Value(ws,value,per_flag.PER_Dec_Len,
				Default_bit,&per_flag,align_flag))
				return ASN1_PER_CHECK_LENGTH_ERROR;

		
	}
	else{
		
		temp_value_length = 0;
		while (sever_flag)
		{	
			sever_flag = ASN1_PER_Dec_SeverLength(ws,consinfo,&per_flag,ALIGN);

			if(0>sever_flag)
				return ASN1_PER_CHECK_LENGTH_ERROR;

			temp_value_length += per_flag.PER_Dec_Len;
			value->nchar = temp_value_length;

			value->data =
			mpool_realloc(ws->Pmemory,value->data,temp_value_length*sizeof(ASNUINT32));

			if(0>ASN1_PER_Dec_UNI_Value(ws,value,per_flag.PER_Dec_Len,
					Default_bit,&per_flag,UNALIGN))
					return ASN1_PER_CHECK_LENGTH_ERROR;
		}
	}


	if (consinfo->charSet != NULL){
		free(per_flag.Alphable_table);
	}
	return 0;

}

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_UNI_Process(ASN1WorkSpace* ws,UniversalString* value, 
										  Asn1ConsInfo *consinfo,ASNINT32 Default_bit)
{
	struct PER_Flag per_flag;
	ASNINT32 sever_flag = 1;
	ASNINT32 temp_value_length;
	ASNUINT32 process_length = 0;
	ASNINT32 ret = 0;
	
	ASNUINT8* temp_current;
	ASNUINT16 temp_bitOffset;
	ASNINT32  temp_loop_i = 0;

	per_flag.Range = 0;

	if (consinfo->charSet == NULL){
		per_flag.Char_set_length = 0;
	}
	else{
		per_flag.Char_set_length = (ASNINT32)strlen(consinfo->charSet);
	}
	
	value->data = (ASNUINT32*)mpool_malloc(ws->Pmemory,1*sizeof(ASNUINT32));
	value->nchar = 1;
	per_flag.PER_Dec_Len = 1;

	ret = PER_CONSTRAINT_Dec_Process(ws,consinfo,&Default_bit,&per_flag,UNALIGN);
	if (ret<0){
		return ASN1_PER_CHECK_LENGTH_ERROR;
	}

	if (per_flag.ext_flag == 1){
		/*&&(per_flag.Value_length >= 16384);*/
		temp_value_length = 0;
		temp_current = ws->buffer.current;
		temp_bitOffset = ws->buffer.bitOffset;

		while (sever_flag)
		{	
			temp_loop_i++;
			sever_flag = ASN1_PER_Dec_SeverLength(ws,consinfo,
				&per_flag,UNALIGN);

			if(0>sever_flag)
				return ASN1_PER_CHECK_LENGTH_ERROR;

			if ((temp_loop_i == 1)&&(sever_flag == 0)){
				ws->buffer.current = temp_current;
				ws->buffer.bitOffset = temp_bitOffset;
				break;
			}

			temp_value_length += per_flag.PER_Dec_Len;
			value->nchar = temp_value_length;

			value->data =
			mpool_realloc(ws->Pmemory,value->data,temp_value_length*sizeof(ASNUINT32));

			if(0>ASN1_PER_Dec_UNI_Value(ws,value,per_flag.PER_Dec_Len,Default_bit,&per_flag,UNALIGN))
				return ASN1_PER_CHECK_LENGTH_ERROR;

		}
		
		if (temp_loop_i != 1){
			return 0;
		}
	}
	
	if(per_flag.Range == 1 && per_flag.L_En_Flag == 0){
		if (consinfo->extflag == 1){
				if(0>ASN1_PER_Dec_ExtLength(ws,consinfo,&per_flag,UNALIGN))
					return ASN1_PER_CHECK_LENGTH_ERROR;
				value->nchar = per_flag.PER_Dec_Len;
				
				value->data =
				mpool_realloc(ws->Pmemory,value->data,
							  per_flag.PER_Dec_Len*sizeof(ASNUINT32));

		}
	
		if(0>ASN1_PER_Dec_UNI_Value(ws,value,per_flag.PER_Dec_Len,
				Default_bit,&per_flag,UNALIGN))
				return ASN1_PER_CHECK_LENGTH_ERROR;

		return 0;
	}
	
	if(per_flag.Is_Size == 1){
		
		if(0>ASN1_PER_Dec_strLength(ws,consinfo,&per_flag,UNALIGN))
			return ASN1_PER_CHECK_LENGTH_ERROR;
		value->nchar = per_flag.PER_Dec_Len;

		value->data =
		mpool_realloc(ws->Pmemory,value->data,per_flag.PER_Dec_Len*sizeof(ASNUINT32));

		if(0>ASN1_PER_Dec_UNI_Value(ws,value,per_flag.PER_Dec_Len,
				Default_bit,&per_flag,UNALIGN))
				return ASN1_PER_CHECK_LENGTH_ERROR;
		
	}
	else{
		
		temp_value_length = 0;
		while (sever_flag)
		{	
			sever_flag = ASN1_PER_Dec_SeverLength(ws,consinfo,&per_flag,UNALIGN);

			if(0>sever_flag)
				return ASN1_PER_CHECK_LENGTH_ERROR;

			temp_value_length += per_flag.PER_Dec_Len;
			value->nchar = temp_value_length;

			value->data =
			mpool_realloc(ws->Pmemory,value->data,temp_value_length*sizeof(ASNUINT32));

			if(0>ASN1_PER_Dec_UNI_Value(ws,value,per_flag.PER_Dec_Len,
					Default_bit,&per_flag,UNALIGN))
					return ASN1_PER_CHECK_LENGTH_ERROR;
		}
	}


	if (consinfo->charSet != NULL){
		free(per_flag.Alphable_table);
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_Enc_UNI_Value(ASN1WorkSpace* ws,UniversalString* value,
     							ASNUINT32 length,ASNINT32 Default_bit,
								struct PER_Flag *per_flag,ASN1PERAlign Align_Flag)
{
	ASNUINT8 UNI_string[4];
	ASNUINT32* encode = value->data;
	
	ASNINT32 i = 0,j = 0;
	
	memset(UNI_string,0x00,4);
	value->data += length;		

	while (length)
	{
		
		UNI_string[0] = (ASNUINT8)((*encode)>>24);
		UNI_string[1] = (ASNUINT8)((*encode)>>16);
		UNI_string[2] = (ASNUINT8)((*encode)>>8);
		UNI_string[3] = (ASNUINT8)(*encode);
		
		if (!i){
			ASN1_FillBuffer(ws,UNI_string,Default_bit,Align_Flag);
			i++;
		}
		else{
			ASN1_FillBuffer(ws,UNI_string,Default_bit,UNALIGN);
		}
		encode++;
		length--;
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_Dec_UNI_Value(ASN1WorkSpace* ws,UniversalString* value,
								ASNUINT32 length,ASNINT32 Default_bit,
								struct PER_Flag *per_flag,ASN1PERAlign Align_Flag)
{
	ASNUINT8 Base = per_flag->Base_Letter;
	ASNUINT32* Tdecode = (value->data + (value->nchar - length));
	ASNINT32 ret = 0;
	ASNUINT8 UNI_string[4];
	ASNINT32 i = 0;
	
	memset(UNI_string,0x00,4);

	while (length)
	{
		if (!i){
			if(0>ASN1_ReadBuffer(ws,UNI_string,Default_bit,Align_Flag))
				return ret;
			i++;
		}
		else{
			if(0>ASN1_ReadBuffer(ws,UNI_string,Default_bit,UNALIGN))
				return ret;
		}
		
		*Tdecode = UNI_string[0];
		*Tdecode<<=8;
		*Tdecode += UNI_string[1];
		*Tdecode<<=8;
		*Tdecode += UNI_string[2];
		*Tdecode<<=8;
		*Tdecode += UNI_string[3];
		
		Tdecode++;
		length--;
	}

	return 0;
}

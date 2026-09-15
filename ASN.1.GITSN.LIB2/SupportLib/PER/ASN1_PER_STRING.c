#include "ASN1_PER_STRING.h"

ASNUINT8 per_char_array[128] = 
{
	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,\
	0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,\
	0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,\
	0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,\
	0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,\
	0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,\
	0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,\
	0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F
};

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_String(ASN1WorkSpace* ws,ASNSTRING* value,
								   Asn1ConsInfo *consinfo,ASNINT32 Default_bit)
{
	struct PER_Flag per_flag;
	ASN1PERAlign align_flag;
	ASNUINT8 zero;
	ASNINT32 sever_flag = 1;
	ASNINT32 temp_value_length;
	ASNUINT32 process_length = 0;
	ASNINT32 ret = 0;
	ASNUINT8* temp_value = value->asnstring;
	
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
			ASN1_PER_Enc_String_Value(ws,value,process_length,
				Default_bit,&per_flag,UNALIGN);
		}
		if (per_flag.Value_length!=0 && (per_flag.Value_length % 16384) == 0){
			zero = 0x00;
			ASN1_FillBuffer(ws,&zero,8,ALIGN);
		}
		value->asnstring = temp_value;
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
		ASN1_PER_Enc_String_Value(ws,value,per_flag.Value_length,
								  Default_bit,&per_flag,align_flag);
		value->asnstring = temp_value;
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
		ASN1_PER_Enc_String_Value(ws,value,per_flag.Value_length,
								  Default_bit,&per_flag,align_flag);
	}
	else{
		
		temp_value_length = per_flag.Value_length;
		while (sever_flag)
		{	
			sever_flag = ASN1_PER_Enc_SeverLength(ws,&temp_value_length,consinfo,
												  &process_length,ALIGN);
			ASN1_PER_Enc_String_Value(ws,value,process_length,
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
	value->asnstring = temp_value;
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_String(ASN1WorkSpace* ws,ASNSTRING* value, 
						        	 Asn1ConsInfo *consinfo,ASNINT32 Default_bit)
{
	struct PER_Flag per_flag;
	ASNUINT8 zero;
	ASNINT32 sever_flag = 1;
	ASNINT32 temp_value_length;
	ASNUINT32 process_length = 0;
	ASNINT32 ret = 0;
	ASNUINT8* temp_value = value->asnstring;

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
			ASN1_PER_Enc_String_Value(ws,value,process_length,
				Default_bit,&per_flag,UNALIGN);
		}
		if (per_flag.Value_length!=0 && (per_flag.Value_length % 16384) == 0){
			zero = 0x00;
			ASN1_FillBuffer(ws,&zero,8,UNALIGN);
		}
		value->asnstring = temp_value;
		return 0;
	}

	if(per_flag.Range == 1 && per_flag.L_En_Flag == 0){
		if (per_flag.ext_flag == 1){
			ASN1_PER_Enc_ExtLength(ws,per_flag.Value_length,
								   consinfo,&per_flag,UNALIGN);
			}
		ASN1_PER_Enc_String_Value(ws,value,per_flag.Value_length,
			Default_bit,&per_flag,UNALIGN);
		value->asnstring = temp_value;
		return 0;
	}
	
	if(per_flag.Is_Size == 1){

		ASN1_PER_Enc_strLength(ws,per_flag.Value_length,consinfo,&per_flag,UNALIGN);
		ASN1_PER_Enc_String_Value(ws,value,per_flag.Value_length,
			Default_bit,&per_flag,UNALIGN);
		
	}
	else{

		temp_value_length = per_flag.Value_length;
		while (sever_flag)
		{	
			sever_flag = ASN1_PER_Enc_SeverLength(ws,&temp_value_length,consinfo,
				&process_length,UNALIGN);
			ASN1_PER_Enc_String_Value(ws,value,process_length,
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
	value->asnstring = temp_value;
	return 0;

}

ASN1_CPPLINK ASNINT32 ASN1_PER_Enc_String_Value(ASN1WorkSpace* ws,ASNSTRING* value,
								   ASNUINT32 length,ASNINT32 Default_bit,
								   struct PER_Flag *per_flag,ASN1PERAlign Align_Flag)
{
	ASNUINT8* encode = value->asnstring; 
	ASNUINT8 Base = per_flag->Base_Letter;
	ASNUINT8 Tencode;
	ASNUINT8* Atable;
	ASNINT32 i = 0;

	value->asnstring += length;

	if(per_flag->Is_Alphable == 1){
		Atable = per_flag->Alphable_table;

		while (length)
		{

			Tencode = Atable[*encode - Base];
			if (!i){
				ASN1_FillBuffer(ws,&Tencode,Default_bit,Align_Flag);
				i++;
			}
			else{
				ASN1_FillBuffer(ws,&Tencode,Default_bit,UNALIGN);
			}
			encode++;
			length--;
		}
	}
	else{
		 while (length)
		 {
			if (!i){
				ASN1_FillBuffer(ws,encode,Default_bit,Align_Flag);
				i++;
			}
			else{
				ASN1_FillBuffer(ws,encode,Default_bit,UNALIGN);
			}
			encode++;
			length--;
		 }
	}
	return 0;
}

ASNINT32 ASN1_PER_Enc_SeverLength(ASN1WorkSpace *ws, ASNUINT32 *length, Asn1ConsInfo *consinfo, ASNUINT32 *process_length, ASN1PERAlign Align_Flag)
{
	ASNUINT8 PARCEL_NUM;
	ASNUINT8 temp_length[2];
	memset(temp_length,0x00,2);

	*process_length = *length;

	while((*length) >> 14)
	{
		if (!( (*length) >> 16))
		{
			PARCEL_NUM = ((*length) >> 14) & 0x03;
			temp_length[0] = (0xc0 | PARCEL_NUM);
			ASN1_FillBuffer(ws, temp_length, 8, Align_Flag);
			*length = (*length & 0x3fff);
			*process_length = 16384 * PARCEL_NUM;
			return 1;
		}
		else
		{
			temp_length[0] = 0xc4;
			ASN1_FillBuffer(ws, temp_length, 8, Align_Flag);
			*length = *length - 65536;
			*process_length = 65536;
			return 1;
		}
	}

	if (*length > 127)
	{
		PER_Enc_Len_Process(temp_length, *length, 16);
		temp_length[0] &= 0x7f;
		temp_length[0] |= 0x80;
		ASN1_FillBuffer(ws, temp_length, 16, Align_Flag);
	}
	else
	{
		temp_length[0] |= *length;
		ASN1_FillBuffer(ws, temp_length, 8, Align_Flag);
	}
	*length = 0;
	return 0;
}

ASNINT32 ASN1_PER_Enc_strLength(ASN1WorkSpace *ws, ASNUINT32 length, Asn1ConsInfo *consinfo, struct PER_Flag *per_flag, ASN1PERAlign Align_Flag)
{
	ASNUINT8 temp_length[2] = { 0, };
	ASNINT64 Tlength = length - consinfo->lower;
	ASNINT32 bit = 0;

	if (consinfo->extflag == 1)
	{
		if (ASN1_PER_Enc_ExtLength(ws, length, consinfo, per_flag, Align_Flag) == 0) return 0;
	}
	Tlength = per_flag->Range - 1;
	while(Tlength)
	{	
		Tlength >>= 1;
		bit++;
	}

	if (per_flag->Range == 1) return 0;
	
	PER_Enc_Len_Process(temp_length, length - consinfo->lower, bit);
	if (per_flag->Range > 256)
	{
		if (ALIGN == Align_Flag)
		{
			PER_Enc_Len_Process(temp_length, length - consinfo->lower, 16);
			ASN1_FillBuffer(ws, temp_length, 16, Align_Flag);
		}
		else ASN1_FillBuffer(ws, temp_length, bit, Align_Flag);
	}
	else ASN1_FillBuffer(ws, temp_length, bit, UNALIGN);
    return 0;
}

ASNINT32 ASN1_PER_Enc_ExtLength(ASN1WorkSpace *ws, ASNUINT32 length, Asn1ConsInfo *consinfo, struct PER_Flag *per_flag, ASN1PERAlign Align_Flag)
{
	ASNUINT8 temp_length[2] = { 0, };
	ASNINT32 bit = 0;

	if (per_flag->ext_flag == 1)
	{
		if (length >> 8) // length >= 256
		{
			PER_Enc_Len_Process(temp_length, length, 16);
			temp_length[0] &= 0x7f;
			temp_length[0] |= 0x80;
			ASN1_FillBuffer(ws, temp_length, 16, Align_Flag);
		}
		else
		{
			temp_length[0] |= length;
			ASN1_FillBuffer(ws, temp_length, 8, Align_Flag);
		}	
		return 0;
	}
	return 1;
}

ASNINT32 PER_CONSTRAINT_Enc_Process(ASN1WorkSpace *ws, Asn1ConsInfo *consinfo, ASNINT32 *Default_bit, struct PER_Flag *per_flag, ASN1PERAlign Align_Flag)
{
	ASNUINT8 ext_flag;
	if (consinfo->charSet == NULL)
	{
		per_flag->Is_Alphable = 0;
	}
	else
	{
		per_flag->Is_Alphable = 1;
		if (Align_Flag == ALIGN)
		{
			*Default_bit = PER_DEFAULT_Bit_Align_Process(per_flag->Char_set_length);
		}
		else
		{
			*Default_bit = PER_DEFAULT_Bit_UNAlign_Process(per_flag->Char_set_length);
		}

		per_flag->Alphable_table = (ASNUINT8*)malloc(128 * sizeof(ASNUINT8));
		per_encode_change_char_table(consinfo->charSet, per_flag->Alphable_table);
		per_flag->Base_Letter = consinfo->charSet[0];
	}
	
	if (consinfo->consType == UNCONS || consinfo->consType == SEMICONS)
	{
		per_flag->Is_Size = 0;
		if (consinfo->extflag != 1)
		{
			if (consinfo->consType == SEMICONS && per_flag->Value_length < consinfo->lower)
			{
				return -404;
			}
		}
	}
	else
	{
		if ((per_flag->Value_length > consinfo->upper || per_flag->Value_length < consinfo->lower) &&  consinfo->extflag == 0)
		{
			return -404;
		}

		per_flag->ext_flag = 0;
		if (consinfo->extflag == 1)
		{
			if (per_flag->Value_length > consinfo->upper || per_flag->Value_length < consinfo->lower)
			{
				ext_flag = 0x01;
				ASN1_FillBuffer(ws, &ext_flag, 1, UNALIGN);
				per_flag->ext_flag = 1;
			}
			else
			{
				ext_flag = 0x00;
				ASN1_FillBuffer(ws, &ext_flag, 1, UNALIGN);
				per_flag->ext_flag = 0;
			}
		}

		per_flag->Is_Size = 1;
		per_flag->Range = consinfo->upper - consinfo->lower + 1;

		if (per_flag->Char_set_length > 16 && Align_Flag == ALIGN)
		{
			per_flag->Is_Alphable = 0;
		}

		if (consinfo->upper >= 65536)
		{
			per_flag->Is_Size = 0;
		}

		if (per_flag->Range == 1 && consinfo->upper >= 65536)
		{
			per_flag->Is_Size = 0; 
			per_flag->L_En_Flag = 1;
		}
		else if (per_flag->Range == 1)
		{
			per_flag->L_En_Flag = 0;
		}
	}
		
	return 0;
}

ASNINT32 PER_Enc_Len_Process(ASNUINT8 *encode_memony, ASNINT16 length, ASNINT32 ebit)
{
	if (ebit > 8)
	{
		length <<= (16 - ebit);
		encode_memony[0] = length >> 8;
		encode_memony[1] = length;
		encode_memony[1] >>= (16 - ebit);
	}
	else{
		encode_memony[0] = length;
	}
	return 0;
}

ASNINT32 PER_CONSTRAINT_Dec_Process(ASN1WorkSpace *ws, Asn1ConsInfo *consinfo, ASNINT32 *Default_bit, struct PER_Flag *per_flag, ASN1PERAlign Align_Flag)
{
	ASNUINT8 ext_flag;

	per_flag->ext_flag = 0;

	if (consinfo->charSet == NULL)
	{
		per_flag->Is_Alphable = 0;
	}
	else
	{
		per_flag->Is_Alphable = 1;
		if (Align_Flag == ALIGN)
		{
			*Default_bit = PER_DEFAULT_Bit_Align_Process(per_flag->Char_set_length);
		}
		else
		{
			*Default_bit = PER_DEFAULT_Bit_UNAlign_Process(per_flag->Char_set_length);
		}

		per_flag->Alphable_table = (ASNUINT8*)malloc(128 * sizeof(ASNUINT8));
		per_decode_change_chartable(consinfo->charSet, per_flag->Alphable_table);
		per_flag->Base_Letter = consinfo->charSet[0];
	}
	
	if (consinfo->consType == UNCONS || consinfo->consType == SEMICONS)
	{
		per_flag->Is_Size = 0;
	}
	else
	{
		if (consinfo->extflag == 1)
		{
			if (0 > ASN1_ReadBuffer(ws, &ext_flag, 1, UNALIGN)) return -403;
			per_flag->ext_flag = ext_flag;
		}

		per_flag->Is_Size = 1;
		per_flag->Range = consinfo->upper - consinfo->lower + 1;
		
		if (per_flag->Char_set_length > 16 && Align_Flag == ALIGN)
		{
			per_flag->Is_Alphable = 0;
		}

		if (consinfo->upper >= 65536)
		{
			per_flag->Is_Size = 0;
		}

		if (per_flag->Range == 1 && consinfo->upper >= 65536)
		{
			per_flag->Is_Size = 0; 
			per_flag->L_En_Flag = 1;
		}
		else if (per_flag->Range == 1)
		{
			per_flag->PER_Dec_Len = consinfo->lower;
			per_flag->L_En_Flag = 0;
		}
	}
	return 0;
}

ASNINT32 per_encode_change_char_table(ASNUINT8 *input_string, ASNUINT8 *output_string)
{
	ASNUINT8 *temp_table_null;
	ASNUINT8 *input_temp_string = input_string;
	ASNUINT8 *output_temp_start;
	ASNUINT8 *output_temp_end;
	ASNINT32 i = 0;
	temp_table_null = (ASNUINT8 *)malloc(128 * sizeof(ASNUINT8));
	memset(temp_table_null, 0xFF, 128);

	while(*input_string != '\0')
	{
		temp_table_null[*input_string] = i;
		if (i == 0)
		{
			output_temp_start = &temp_table_null[*input_string];
			output_temp_end = &temp_table_null[*input_string];
		}
		else output_temp_end = &temp_table_null[*input_string];

		input_string++;
		i++;
	}
	
	memcpy(output_string, output_temp_start, (output_temp_end - output_temp_start) + 1);
	free(temp_table_null);
	return 0;	
}

ASN1_CPPLINK ASNINT32 per_decode_change_chartable(ASNUINT8 *input_string,ASNUINT8 *output_string)
{
	ASNUINT8 *temp_table_null;
	ASNUINT8 *input_temp_string = input_string;
// 	ASNUINT8 *output_temp_start;
// 	ASNUINT8 *output_temp_end;
	ASNINT32 i=0;
	temp_table_null = (ASNUINT8*)malloc(128*sizeof(ASNUINT8));
	memset(temp_table_null,0x00,128);
	
	while(*input_string != '\0')
	{
		
		temp_table_null[i] = per_char_array[*input_string];
		input_string++;
		i++;
	}
	
	memcpy(output_string,temp_table_null,i);
	free(temp_table_null);
	//free(input_temp_string);
	return 0;

}

ASNINT32 PER_DEFAULT_Bit_Align_Process(ASNINT32 default_bit)
{
	switch(default_bit)
	{
		case 0: 
			return 0;
		case 1:
		case 2:
			return 1;
		case 3:
		case 4:
			return 2;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9: 
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
			return 4;
		default:
			return 8;
	}
}

ASNINT32 PER_DEFAULT_Bit_UNAlign_Process(ASNINT32 default_bit)
{
	ASNINT32 i = 0;
	default_bit -= 1;
	while (default_bit)
	{
		default_bit >>= 1;
		i++;
	}
	return i;
}


ASN1_CPPLINK ASNINT32 per_ordering_char(ASNUINT8 *input_string,ASNUINT8 **output_string)
{
	ASNUINT8 *input_temp_start = input_string;

	ASNUINT8 *output_temp_end;
	ASNUINT8 *output_temp_current;

	ASNINT32 flag_repeat = 0;

	(*output_string) = (ASNUINT8*)malloc(128*sizeof(ASNUINT8));
	memset((*output_string),'\0',128);
	output_temp_end = (*output_string)+1;
	
	*(*output_string) = *input_temp_start;
	input_temp_start++;

	while(*input_temp_start != '\0')
	{
		flag_repeat = 0;
		output_temp_current = (*output_string);
		while(*output_temp_current != '\0')
		{
			if(*input_temp_start == *output_temp_current)
			{
				input_temp_start++;
				flag_repeat = 1;
				break;
			}
			if(*input_temp_start < *output_temp_current)
			{
				memcpy(output_temp_current+1,output_temp_current,output_temp_end-output_temp_current);
				*output_temp_current = *input_temp_start;
				output_temp_end++;
				break;
			}
			output_temp_current++;
		}
		
		if(!flag_repeat)
		{
			*output_temp_current = *input_temp_start;
			output_temp_end++;
			input_temp_start++;
		}
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_String(ASN1WorkSpace *ws,ASNSTRING *value,
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
	
	value->asnstring = (ASNUINT8*)mpool_malloc(ws->Pmemory,1*sizeof(ASNUINT8));
	value->nchar = 1;
	per_flag.PER_Dec_Len = 1;

	ret = PER_CONSTRAINT_Dec_Process(ws,consinfo,&Default_bit,&per_flag,ALIGN);
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
				                                  &per_flag,ALIGN);
			if(0>sever_flag)
				return ASN1_PER_CHECK_LENGTH_ERROR;
			if ((temp_loop_i == 1)&&(sever_flag == 0)){
				ws->buffer.current = temp_current;
				ws->buffer.bitOffset = temp_bitOffset;
				sever_flag = 1;
				break;
			}

			temp_value_length += per_flag.PER_Dec_Len;
			value->nchar = temp_value_length;

			value->asnstring = 
			mpool_realloc(ws->Pmemory,value->asnstring,temp_value_length*sizeof(ASNUINT8));

			if(0>ASN1_PER_Dec_String_Value(ws,value,per_flag.PER_Dec_Len,Default_bit,&per_flag,UNALIGN))
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
				value->asnstring =
				mpool_realloc(ws->Pmemory,value->asnstring,
							  per_flag.PER_Dec_Len*sizeof(ASNUINT8));

			}
		}
		else{
			align_flag = ALIGN;
		}
		value->nchar = per_flag.PER_Dec_Len;
		if(0>ASN1_PER_Dec_String_Value(ws,value,per_flag.PER_Dec_Len,
			Default_bit,&per_flag,align_flag))
			return ASN1_PER_CHECK_LENGTH_ERROR;
		
		return 0;
	}
	
	if(per_flag.Is_Size == 1){
	
		align_flag = ALIGN;
		if (per_flag.Range < 256){
			align_flag = UNALIGN;
		}
			if(0>ASN1_PER_Dec_strLength(ws,consinfo,&per_flag,align_flag))
				return ASN1_PER_CHECK_LENGTH_ERROR;

		align_flag = ALIGN;
		if ((per_flag.PER_Dec_Len <= consinfo->upper) && 
			(per_flag.PER_Dec_Len >= consinfo->lower)){
			if ((consinfo->upper * Default_bit) >= 16)
				align_flag = ALIGN;
			else
				align_flag = UNALIGN;
		}

		value->nchar = per_flag.PER_Dec_Len;
		value->asnstring =
		mpool_realloc(ws->Pmemory,value->asnstring,per_flag.PER_Dec_Len*sizeof(ASNUINT8));

		if(0>ASN1_PER_Dec_String_Value(ws,value,per_flag.PER_Dec_Len,
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

			value->asnstring =
			mpool_realloc(ws->Pmemory,value->asnstring,temp_value_length*sizeof(ASNUINT8));

			if(0>ASN1_PER_Dec_String_Value(ws,value,per_flag.PER_Dec_Len,
					Default_bit,&per_flag,UNALIGN))
					return ASN1_PER_CHECK_LENGTH_ERROR;
		}
	}


	if (consinfo->charSet != NULL){
		free(per_flag.Alphable_table);
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_String(ASN1WorkSpace* ws,ASNSTRING* value, 
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
	
	value->asnstring = (ASNUINT8*)mpool_malloc(ws->Pmemory,1*sizeof(ASNUINT8));
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
				sever_flag = 1;
				break;
			}

			temp_value_length += per_flag.PER_Dec_Len;
			value->nchar = temp_value_length;

			value->asnstring =
			mpool_realloc(ws->Pmemory,value->asnstring,temp_value_length*sizeof(ASNUINT8));

			if(0>ASN1_PER_Dec_String_Value(ws,value,per_flag.PER_Dec_Len,Default_bit,&per_flag,UNALIGN))
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
				
				value->asnstring =
				mpool_realloc(ws->Pmemory,value->asnstring,
							  per_flag.PER_Dec_Len*sizeof(ASNUINT8));

		}
		value->nchar = per_flag.PER_Dec_Len;
		if(0>ASN1_PER_Dec_String_Value(ws,value,per_flag.PER_Dec_Len,
				Default_bit,&per_flag,UNALIGN))
				return ASN1_PER_CHECK_LENGTH_ERROR;
		return 0;
	}
	
	if(per_flag.Is_Size == 1){

		if(0>ASN1_PER_Dec_strLength(ws,consinfo,&per_flag,UNALIGN))
			return ASN1_PER_CHECK_LENGTH_ERROR;
		value->nchar = per_flag.PER_Dec_Len;

		value->asnstring =
		mpool_realloc(ws->Pmemory,value->asnstring,per_flag.PER_Dec_Len*sizeof(ASNUINT8));

		if(0>ASN1_PER_Dec_String_Value(ws,value,per_flag.PER_Dec_Len,
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

			value->asnstring =
			mpool_realloc(ws->Pmemory,value->asnstring,temp_value_length*sizeof(ASNUINT8));

			if(0>ASN1_PER_Dec_String_Value(ws,value,per_flag.PER_Dec_Len,
					Default_bit,&per_flag,UNALIGN))
					return ASN1_PER_CHECK_LENGTH_ERROR;
		}
	}


	if (consinfo->charSet != NULL){
		free(per_flag.Alphable_table);
	}
	return 0;
}
ASN1_CPPLINK ASNINT32 ASN1_PER_Dec_String_Value(ASN1WorkSpace* ws,ASNSTRING* value,
								   ASNUINT32 length,ASNINT32 Default_bit,
								   struct PER_Flag *per_flag,ASN1PERAlign Align_Flag)
{
	ASNUINT8 Base = per_flag->Base_Letter;
	ASNUINT8* Tdecode = (value->asnstring + (value->nchar - length));
	ASNUINT8* Atable;
	ASNINT32 i = 0;
	/*value->asnstring += (value->nchar - length);*/
	
	if(per_flag->Is_Alphable == 1){
		Atable = per_flag->Alphable_table;
		
		while (length)
		{
			
			if (!i){
				if(0>ASN1_ReadBuffer(ws,Tdecode,Default_bit,Align_Flag))
					return -403;
				i++;
			}
			else{
				if(0>ASN1_ReadBuffer(ws,Tdecode,Default_bit,UNALIGN))
					return -403;
			}
			
			*Tdecode = Atable[*Tdecode];
			Tdecode++;
			length--;
		}
	}
	else{
		while (length)
		{
			if (!i){
				if(0>ASN1_ReadBuffer(ws,Tdecode,Default_bit,Align_Flag))
					return -403;
				i++;
			}
			else{
				if(0>ASN1_ReadBuffer(ws,Tdecode,Default_bit,UNALIGN))
					return -403;
			}
	/*		ASN1_ReadBuffer(ws,Tdecode,Default_bit,Align_Flag);*/
			Tdecode++;
			length--;
		}
	}
	return 0;

}

ASNINT32 ASN1_PER_Dec_strLength(ASN1WorkSpace *ws, Asn1ConsInfo *consinfo, struct PER_Flag *per_flag, ASN1PERAlign Align_Flag)
{
	ASNUINT8 temp_length[2] = { 0, };
	ASNINT64 Tlength;
	ASNINT32 bit = 0;

	if (consinfo->extflag == 1)
	{
		if (!ASN1_PER_Dec_ExtLength(ws, consinfo, per_flag, Align_Flag)) return 0;
	}

	Tlength = per_flag->Range - 1;
	while (Tlength)
	{	
		Tlength>>=1;
		bit++;
	}

	if (per_flag->Range == 1) return 0;

	if (per_flag->Range > 256)
	{
		if (ALIGN == Align_Flag)
		{
			if (0 > ASN1_ReadBuffer(ws, temp_length, 16, Align_Flag)) return -403;
			PER_Dec_Len_Process(temp_length, per_flag, 16);
			per_flag->PER_Dec_Len += consinfo->lower;
			return 0;
		}
		else 
		{
			if (0 > ASN1_ReadBuffer(ws, temp_length, bit, Align_Flag)) return -403;
		}
	}
	else
	{
		if (0 > ASN1_ReadBuffer(ws, temp_length, bit, UNALIGN)) return -403;
	}

	PER_Dec_Len_Process(temp_length, per_flag, bit);
	per_flag->PER_Dec_Len += consinfo->lower;
    return 0;
}

ASNINT32 ASN1_PER_Dec_ExtLength(ASN1WorkSpace *ws, Asn1ConsInfo *consinfo, struct PER_Flag *per_flag, ASN1PERAlign Align_Flag)
{
	ASNUINT8 temp_length[2] = { 0, };
	ASNINT32 bit = 0;
		
	if (per_flag->ext_flag == 1)
	{
		if (0 > ASN1_ReadBuffer(ws, &temp_length[0], 8, Align_Flag)) return -403;

		if (temp_length[0] & 0x80)
		{
			if (0 > ASN1_ReadBuffer(ws, &temp_length[1], 8, Align_Flag)) return -403;
			temp_length[0] &= 0x3f;

			PER_Dec_Len_Process(temp_length, per_flag, 16);
		}
		else 
		{
			per_flag->PER_Dec_Len = temp_length[0];
		}
		return 0;
	}
	return 1;
}

ASNINT32 ASN1_PER_Dec_SeverLength(ASN1WorkSpace *ws, Asn1ConsInfo *consinfo, struct PER_Flag *per_flag, ASN1PERAlign Align_Flag)
{
	ASNUINT8 temp_length[2] = { 0, };
	
	if (0 > ASN1_ReadBuffer(ws, &temp_length[0], 8, Align_Flag)) return -403;
	
	if ((temp_length[0] & 0xc0) == 0xc0)
	{
		temp_length[0] &= 0x3f;
		per_flag->PER_Dec_Len = temp_length[0] * 16384;
		return 3;
	}
	else if (temp_length[0] & 0x80)
	{
		if (0 > ASN1_ReadBuffer(ws, &temp_length[1], 8, Align_Flag)) return -403;
		temp_length[0] &= 0x3f;
		PER_Dec_Len_Process(temp_length, per_flag, 16);
	}
	else 
	{
		per_flag->PER_Dec_Len = temp_length[0];
	}
	return 0;
}

ASNINT32 PER_Dec_Len_Process(ASNUINT8 *decode_memony, struct PER_Flag *per_flag, ASNINT32 ebit)
{
	if (ebit > 8)
	{
		per_flag->PER_Dec_Len = decode_memony[0];
		decode_memony[1] <<= (16 - ebit);
		per_flag->PER_Dec_Len <<= 8;
		per_flag->PER_Dec_Len = per_flag->PER_Dec_Len + decode_memony[1];
		per_flag->PER_Dec_Len >>= (16 - ebit);
	}
	else
	{
		per_flag->PER_Dec_Len = decode_memony[0];
	}
	return 0;
}

ASNINT32 PER_CHECK_Avail(ASNSTRING *value, ASNUINT8 *ACharSet, ASNINT32 ACharSet_count)
{
	ASNUINT8 *temp_table_null;
	ASNUINT8 *csp = ACharSet;
	ASNUINT8 *srcp = value->asnstring;
	ASNINT32 i;

	temp_table_null = (ASNUINT8 *)malloc(128 * sizeof(ASNUINT8));
	memset(temp_table_null, 0xFF, 128);


	
	while(ACharSet_count)
	{
		temp_table_null[*csp] = 0x45;
		csp++;
		ACharSet_count--;
	}
	
	i = value->nchar;

	while(i)
	{	
		if (0xFF == temp_table_null[*srcp])
		return -405;
		
		srcp++;	
		i--;
	}
	
	free(temp_table_null);
	return 0;
}

ASNINT32 ASN1_PER_Align_Enc_NormalString(ASN1WorkSpace *ws, ASNSTRING *value, Asn1ConsInfo *consinfo)
{
	ASNINT32 ret;
	
	ret = ASN1_PER_Align_Enc_String(ws, value, consinfo, NORMAL_ABITS);
	if (ret < 0) return ret;
	
	return 0;
}

ASNINT32 ASN1_PER_UNAlign_Enc_NormalString(ASN1WorkSpace *ws, ASNSTRING *value, Asn1ConsInfo *consinfo)
{
	ASNINT32 ret;
	
	ret = ASN1_PER_UNAlign_Enc_String(ws, value, consinfo, NORMAL_UBITS);
	if (ret < 0) return ret;

	return 0;
}

ASNINT32 ASN1_PER_Align_Dec_NormalString(ASN1WorkSpace *ws, ASNSTRING *value, Asn1ConsInfo *consinfo)
{
	ASNINT32 ret;
	
	ret = ASN1_PER_Align_Dec_String(ws, value, consinfo, NORMAL_ABITS);
	if (ret < 0) return ret;

	return 0;
}

ASNINT32 ASN1_PER_UNAlign_Dec_NormalString(ASN1WorkSpace *ws, ASNSTRING *value, Asn1ConsInfo *consinfo)
{
	ASNINT32 ret;
	
	ret = ASN1_PER_UNAlign_Dec_String(ws, value, consinfo, NORMAL_UBITS);
	if (ret<0) return ret;

	return 0;
}


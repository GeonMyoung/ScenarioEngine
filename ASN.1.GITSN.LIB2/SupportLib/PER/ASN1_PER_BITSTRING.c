#include "ASN1_PER_BITSTRING.h"

ASN1_CPPLINK void remove_invalid_zeros(BITSTRING *BitVectorValue);



ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_Inline_BITSTRING(ASN1WorkSpace *ws, BITSTRING *value, 
								             Asn1ConsInfo *consinfo)
{
	struct PER_Flag per_flag;
	ASN1PERAlign align_flag;
	ASNUINT8 zero;
	ASNINT32 sever_flag = 1;
	ASNINT32 temp_value_length;
	ASNUINT32 process_length = 0;
	ASNINT32 ret = 0;
	ASNUINT8* temp_value = value->data;
	ASNINT32 Default_bit = 0;

	if (consinfo->BitVector) 
	{
		remove_invalid_zeros(value);
		if (value->numbits < consinfo->lower)
		{
			value->numbits = (ASNUINT32L)consinfo->lower;
		}
	}

	if(value->numbits)
		ASN1_PER_Enc_BITSTRING_Value_Process(value);

	per_flag.Range = 0;
	per_flag.Value_length = value->numbits;
	
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
			ASN1_PER_Enc_BITSTRING_Value(ws,value,process_length,
				                         &per_flag,UNALIGN);
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
		ASN1_PER_Enc_BITSTRING_Value(ws,value,per_flag.Value_length,
			                         &per_flag,align_flag);
		value->data = temp_value;
		return 0;
	}
	
	if(per_flag.Is_Size == 1){
		align_flag = ALIGN;
		if (consinfo->extflag == 1){
			align_flag = ALIGN;
		}

		ASN1_PER_Enc_strLength(ws,per_flag.Value_length,consinfo,&per_flag,align_flag);
		ASN1_PER_Enc_BITSTRING_Value(ws,value,per_flag.Value_length,
			                         &per_flag,align_flag);
		
	}
	else{
		
		temp_value_length = per_flag.Value_length;
		while (sever_flag)
		{	
			sever_flag = ASN1_PER_Enc_SeverLength(ws,&temp_value_length,consinfo,
				&process_length,ALIGN);
			ASN1_PER_Enc_BITSTRING_Value(ws,value,process_length,
				                         &per_flag,UNALIGN);
		}
		if (per_flag.Value_length!=0 && (per_flag.Value_length % 16384) == 0){
			zero = 0x00;
			ASN1_FillBuffer(ws,&zero,8,ALIGN);
		}
		
	}
	value->data = temp_value;
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_BITSTRING(ASN1WorkSpace *ws, BITSTRING *value, 
									  Asn1ConsInfo *consinfo)
{
	ASNINT32 ret = 0;
	if(consinfo->lower == consinfo->upper && consinfo->lower <= 16)
		ret = ASN1_PER_UNAlign_Enc_BITSTRING(ws,value,consinfo);
	else
		ret = ASN1_PER_Align_Enc_Inline_BITSTRING(ws,value,consinfo);
	return ret;
	
}

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_Inline_BITSTRING(ASN1WorkSpace *ws, BITSTRING *value,
        							         Asn1ConsInfo *consinfo)
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
	ASNINT32 Default_bit = 0;

	per_flag.Range = 0;

	
	value->data = (ASNUINT8*)mpool_malloc(ws->Pmemory,1*sizeof(ASNUINT8));
	value->numbits = 8;
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
				sever_flag = 1;
				break;
			}

			temp_value_length += per_flag.PER_Dec_Len;
			value->numbits = temp_value_length;

			value->data = 
			mpool_realloc(ws->Pmemory,value->data,
						  ASN1_PER_BITSTRING_memory(temp_value_length)*sizeof(ASNUINT8));

			if(0>ASN1_PER_Dec_BITSTRING_Value(ws,value,per_flag.PER_Dec_Len,
										&per_flag,UNALIGN))
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
				value->numbits = per_flag.PER_Dec_Len;
				value->data =
				mpool_realloc(ws->Pmemory,value->data,
							  ASN1_PER_BITSTRING_memory(per_flag.PER_Dec_Len)*sizeof(ASNUINT8));

			}
		}
		else{
			align_flag = ALIGN;
		}
		value->numbits = per_flag.PER_Dec_Len;
		if(0>ASN1_PER_Dec_BITSTRING_Value(ws,value,per_flag.PER_Dec_Len,
									 &per_flag,align_flag))
						return ASN1_PER_CHECK_LENGTH_ERROR;

		return 0;
	}
	
	if(per_flag.Is_Size == 1){
		align_flag = ALIGN;
		if (consinfo->extflag == 1){
				align_flag = ALIGN;
		}
		if(0>ASN1_PER_Dec_strLength(ws,consinfo,&per_flag,align_flag))
			return ASN1_PER_CHECK_LENGTH_ERROR;
		value->numbits = per_flag.PER_Dec_Len;
		value->data =
		mpool_realloc(ws->Pmemory,value->data,
		              ASN1_PER_BITSTRING_memory(per_flag.PER_Dec_Len)*sizeof(ASNUINT8));

		if(0>ASN1_PER_Dec_BITSTRING_Value(ws,value,per_flag.PER_Dec_Len,
										  &per_flag,align_flag))
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
			value->numbits = temp_value_length;

			value->data =
			mpool_realloc(ws->Pmemory,value->data,
						 ASN1_PER_BITSTRING_memory(temp_value_length)*sizeof(ASNUINT8));

			if(0>ASN1_PER_Dec_BITSTRING_Value(ws,value,per_flag.PER_Dec_Len,
											  &per_flag,UNALIGN))
			return ASN1_PER_CHECK_LENGTH_ERROR;

		}
	}

	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_BITSTRING(ASN1WorkSpace *ws, BITSTRING *value, 
									  Asn1ConsInfo *consinfo)
{
	ASNINT32 ret = 0;
	if(consinfo->lower == consinfo->upper && consinfo->lower <= 16)
		ret=ASN1_PER_UNAlign_Dec_BITSTRING(ws,value,consinfo);
	else
		ret=ASN1_PER_Align_Dec_Inline_BITSTRING(ws,value,consinfo);
	return ret;
	
}

ASNINT32 ASN1_PER_UNAlign_Enc_BITSTRING(ASN1WorkSpace *ws, BITSTRING *value, Asn1ConsInfo *consinfo)
{
	struct PER_Flag per_flag;
	ASNUINT8 zero;
	ASNINT32 sever_flag = 1;
	ASNINT32 temp_value_length;
	ASNUINT32 process_length = 0;
	ASNINT32 ret = 0;
	ASNINT32 Default_bit = 0;
	ASNUINT8* temp_value = value->data;
//	ASNUINT8* temp_value_trail;
	BITSTRING temp_bitstring;

	temp_bitstring.data= mpool_malloc(ws->Pmemory,(value->numbits+7)/8);
	temp_bitstring.numbits = value->numbits;

	memset(temp_bitstring.data,0,(value->numbits+7)/8);
	memcpy(temp_bitstring.data,value->data,(value->numbits+7)/8);

// temp_value_trail = mpool_malloc(ws->Pmemory,(value->numbits+7)/8);
// memset(temp_value_trail,0,(value->numbits+7)/8);


	if (consinfo->BitVector) 
	{
/*		consinfo->extflag = 0;*/
		remove_invalid_zeros(value);
		if (value->numbits < consinfo->lower)
		{
			memcpy(value->data, temp_bitstring.data, (value->numbits + 7) / 8);
			value->numbits = (ASNUINT32L)consinfo->lower;
		}

	}

	if(value->numbits) ASN1_PER_Enc_BITSTRING_Value_Process(value);

	per_flag.Range = 0;
	per_flag.Value_length =  value->numbits;
	
	ret = PER_CONSTRAINT_Enc_Process(ws, consinfo, &Default_bit, &per_flag, UNALIGN);
	if (ret < 0) return ret;
	
	if ((per_flag.ext_flag == 1) && (per_flag.Value_length >= 16384))
	{
		temp_value_length = per_flag.Value_length;
		while(sever_flag)
		{	
			sever_flag = ASN1_PER_Enc_SeverLength(ws, &temp_value_length, consinfo, &process_length, UNALIGN);
			ASN1_PER_Enc_BITSTRING_Value(ws, value,process_length, &per_flag,UNALIGN);
		}

		if (per_flag.Value_length != 0 && (per_flag.Value_length % 16384) == 0)
		{
			zero = 0x00;
			ASN1_FillBuffer(ws, &zero, 8, UNALIGN);
		}

		value->data = temp_value;
		return 0;
	}
	
	if (per_flag.Range == 1 && per_flag.L_En_Flag == 0)
	{
		if (per_flag.ext_flag == 1) ASN1_PER_Enc_ExtLength(ws, per_flag.Value_length, consinfo, &per_flag, UNALIGN);
		ASN1_PER_Enc_BITSTRING_Value(ws, value, per_flag.Value_length, &per_flag, UNALIGN);
		value->data = temp_value;
		return 0;
	}
	
	if(per_flag.Is_Size == 1)
	{	
		ASN1_PER_Enc_strLength(ws, per_flag.Value_length, consinfo, &per_flag, UNALIGN);
		ASN1_PER_Enc_BITSTRING_Value(ws, value, per_flag.Value_length, &per_flag, UNALIGN);
		
	}
	else
	{
		temp_value_length = per_flag.Value_length;
		while(sever_flag)
		{	
			sever_flag = ASN1_PER_Enc_SeverLength(ws, &temp_value_length, consinfo, &process_length, UNALIGN);
			ASN1_PER_Enc_BITSTRING_Value(ws, value, process_length, &per_flag, UNALIGN);
		}

		if (per_flag.Value_length != 0 && (per_flag.Value_length % 16384) == 0)
		{
			zero = 0x00;
			ASN1_FillBuffer(ws, &zero, 8, UNALIGN);
		}
	}
	value->data = temp_value;
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_BITSTRING(ASN1WorkSpace *ws, BITSTRING *value,
										Asn1ConsInfo *consinfo)
{
	struct PER_Flag per_flag;
	ASNINT32  sever_flag = 1;
	ASNINT32  temp_value_length;
	ASNUINT32 process_length = 0;
	ASNINT32  ret = 0;
	
	ASNUINT8* temp_current;
	ASNUINT16 temp_bitOffset;
	ASNINT32  temp_loop_i = 0;
	ASNINT32  Default_bit = 0;
	per_flag.Range = 0;

	
	value->data = (ASNUINT8*)mpool_malloc(ws->Pmemory,1*sizeof(ASNUINT8));
	value->numbits = 8;
	per_flag.PER_Dec_Len = 1;

	ret = PER_CONSTRAINT_Dec_Process(ws,consinfo,&Default_bit,&per_flag,UNALIGN);
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
			value->numbits = temp_value_length;

			value->data =
			mpool_realloc(ws->Pmemory,value->data,
						  ASN1_PER_BITSTRING_memory(temp_value_length)*sizeof(ASNUINT8));

			if(0>ASN1_PER_Dec_BITSTRING_Value(ws,value,per_flag.PER_Dec_Len,
											  &per_flag,UNALIGN))
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
				value->numbits = per_flag.PER_Dec_Len;
				
				value->data =
				mpool_realloc(ws->Pmemory,value->data,
							  ASN1_PER_BITSTRING_memory(per_flag.PER_Dec_Len)*sizeof(ASNUINT8));

		}
		value->numbits = per_flag.PER_Dec_Len;
		if(0>ASN1_PER_Dec_BITSTRING_Value(ws,value,per_flag.PER_Dec_Len,
										  &per_flag,UNALIGN))
				return ASN1_PER_CHECK_LENGTH_ERROR;
		return 0;
	}
	
	if(per_flag.Is_Size == 1){

		if(0>ASN1_PER_Dec_strLength(ws,consinfo,&per_flag,UNALIGN))
			return ASN1_PER_CHECK_LENGTH_ERROR;
		value->numbits = per_flag.PER_Dec_Len;

		value->data =
		mpool_realloc(ws->Pmemory,value->data,
					  ASN1_PER_BITSTRING_memory(per_flag.PER_Dec_Len)*sizeof(ASNUINT8));

		if(0>ASN1_PER_Dec_BITSTRING_Value(ws,value,per_flag.PER_Dec_Len,
										 &per_flag,UNALIGN))
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
			value->numbits = temp_value_length;

			value->data =
			mpool_realloc(ws->Pmemory,value->data,
				          ASN1_PER_BITSTRING_memory(temp_value_length)*sizeof(ASNUINT8));

			if(0>ASN1_PER_Dec_BITSTRING_Value(ws,value,per_flag.PER_Dec_Len,
											  &per_flag,UNALIGN))
				return ASN1_PER_CHECK_LENGTH_ERROR;
		}
	}

	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_Enc_BITSTRING_Value_Process(BITSTRING *value)
{	
	ASNUINT8 *bit_data = value->data;
	ASNUINT32L bit_value_length = value->numbits;

	if(bit_value_length <= 8){
		*bit_data >>= (8-bit_value_length);
	}

	else{
		if(bit_value_length %8 !=0){
			bit_data += 1;
			bit_data += (bit_value_length/8)-1;
		
			*bit_data >>= (8 - (bit_value_length%8));
		}
		else
			return 0;
	}	
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_Dec_BITSTRING_Value_Process(BITSTRING *value)
{
	ASNUINT8 *bit_data = value->data;
	ASNUINT32L bit_value_length = value->numbits;
	
	if(bit_value_length <= 8){
		*bit_data <<= (8-bit_value_length);
	}
	
	else{
		if(bit_value_length %8 !=0){
			bit_data += 1;
			bit_data += (bit_value_length/8)-1;
			
			*bit_data <<= (8 - (bit_value_length%8));
		}
		else
			return 0;
	}	
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_Enc_BITSTRING_Value(ASN1WorkSpace* ws,BITSTRING* value,
									  ASNUINT32 length,struct PER_Flag *per_flag,
									  ASN1PERAlign Align_Flag)
{
	ASNUINT8* encode = value->data; 
	ASNINT32 i = 0;
	
	if (length%8 != 0){
		value->data += 1;
	}
	value->data += (length/8);

	ASN1_FillBuffer(ws,encode,length,Align_Flag);

	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_Dec_BITSTRING_Value(ASN1WorkSpace* ws,BITSTRING* value,
									  ASNUINT32 length,struct PER_Flag *per_flag,
									  ASN1PERAlign Align_Flag)
{
	ASNUINT8* encode = value->data; 
	ASNINT32 i = 0;
	
	if ((value->numbits - length)%8 != 0){
		encode += 1;
	}
	encode += ((value->numbits -length)/8);
	
	if(0>ASN1_ReadBuffer(ws,encode,length,Align_Flag))
		return -403;
	
	if(0>ASN1_PER_Dec_BITSTRING_Value_Process(value))
		return ASN1_PER_CHECK_LENGTH_ERROR;
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_PER_BITSTRING_memory(ASNUINT32L length_memory)
{
	ASNINT32 length = 0;

	if(length_memory %8 != 0)
		length ++;
	length += (length_memory/8);

	return length;
}

ASN1_CPPLINK void remove_invalid_zeros(BITSTRING *BitVectorValue)
{
	ASNUINT32 Length = BitVectorValue->numbits;
	ASNUINT32 byteCount, bitCount;
	
	while(Length)
	{
		byteCount = ((Length+7)>>3) - 1;
		bitCount = Length - byteCount * 8 - 1;
		if(BitVectorValue->data[byteCount] & (0x80 >> bitCount))
		{
			break;
		}
		Length--;
	}
	BitVectorValue->numbits = Length;
}


#include "ASN1_PER_OCTETSTRING.h"

ASNINT32 ASN1_PER_Align_Enc_Inline_OCTETSTRING(ASN1WorkSpace *ws, OCTETSTRING *value, Asn1ConsInfo *consinfo)
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

	per_flag.Range = 0;
	per_flag.Value_length = value->numbits;
	
	ret = PER_CONSTRAINT_Enc_Process(ws, consinfo, &Default_bit, &per_flag, ALIGN);
	if (ret < 0)
	{
		return ret;
	}
	
	if (per_flag.ext_flag == 1 && per_flag.Value_length >= 16384)
	{
		temp_value_length = per_flag.Value_length;
		while (sever_flag)
		{	
			sever_flag = ASN1_PER_Enc_SeverLength(ws, &temp_value_length, consinfo, &process_length, ALIGN);
			ASN1_PER_Enc_OCTETSTRING_Value(ws, value, process_length, &per_flag, UNALIGN);
		}

		if (per_flag.Value_length != 0 && (per_flag.Value_length % 16384) == 0)
		{
			zero = 0x00;
			ASN1_FillBuffer(ws,&zero,8,ALIGN);
		}

		value->data = temp_value;
		return 0;
	}
	
	if (per_flag.Range == 1 && per_flag.L_En_Flag == 0)
	{
		if (consinfo->extflag == 1)
		{
			align_flag = UNALIGN;
			if (per_flag.ext_flag == 1)
			{
				align_flag = ALIGN;
				ASN1_PER_Enc_ExtLength(ws, per_flag.Value_length, consinfo, &per_flag, ALIGN);
			}
		}
		else
		{
			align_flag = ALIGN;
		}

		ASN1_PER_Enc_OCTETSTRING_Value(ws, value, per_flag.Value_length, &per_flag, align_flag);
		value->data = temp_value;

		return 0;
	}
	
	if (per_flag.Is_Size == 1)
	{
		align_flag = ALIGN;
		if (consinfo->extflag == 1)
		{
			align_flag = ALIGN;
		}

		ASN1_PER_Enc_strLength(ws, per_flag.Value_length, consinfo, &per_flag, align_flag);
		ASN1_PER_Enc_OCTETSTRING_Value(ws, value, per_flag.Value_length, &per_flag, align_flag);
	}
	else
	{
		temp_value_length = per_flag.Value_length;
		while (sever_flag)
		{	
			sever_flag = ASN1_PER_Enc_SeverLength(ws,&temp_value_length,consinfo, &process_length, ALIGN);
			ASN1_PER_Enc_OCTETSTRING_Value(ws, value, process_length, &per_flag, UNALIGN);
		}

		if (per_flag.Value_length != 0 && (per_flag.Value_length % 16384) == 0)
		{
			zero = 0x00;
			ASN1_FillBuffer(ws,&zero,8,ALIGN);
		}
	}

	value->data = temp_value;
	return 0;
}

ASNINT32 ASN1_PER_Align_Enc_OCTETSTRING(ASN1WorkSpace *ws, OCTETSTRING *value, Asn1ConsInfo *consinfo)
{
	ASNINT32 ret = 0;

//printf("%lld,%lld,%d\n",consinfo->lower,consinfo->upper,consinfo->extflag);
//printf("\n");
	if (consinfo->lower == consinfo->upper && consinfo->lower <= 2)
		ret = ASN1_PER_UNAlign_Enc_OCTETSTRING(ws, value, consinfo);
	else ret = ASN1_PER_Align_Enc_Inline_OCTETSTRING(ws, value, consinfo);
	return ret;
}

ASNINT32 ASN1_PER_Align_Dec_Inline_OCTETSTRING(ASN1WorkSpace *ws, OCTETSTRING *value, Asn1ConsInfo *consinfo)
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

	
	value->data = (ASNUINT8*)mpool_malloc(ws->Pmemory, 1 * sizeof(ASNUINT8));
	value->numbits = 1;
	per_flag.PER_Dec_Len = 1;

	if ((ret = PER_CONSTRAINT_Dec_Process(ws, consinfo, &Default_bit, &per_flag, ALIGN)) < 0)
		return ASN1_PER_CHECK_LENGTH_ERROR;

	if (per_flag.ext_flag == 1)
	{
		temp_value_length = 0;
		temp_current = ws->buffer.current;
		temp_bitOffset = ws->buffer.bitOffset;

		while (sever_flag)
		{	
			temp_loop_i++;
			if ((sever_flag = ASN1_PER_Dec_SeverLength(ws,consinfo, &per_flag, ALIGN)) < 0) return ASN1_PER_CHECK_LENGTH_ERROR;

			if (temp_loop_i == 1 && sever_flag == 0)
			{
				ws->buffer.current = temp_current;
				ws->buffer.bitOffset = temp_bitOffset;
				sever_flag = 1;
				break;
			}

			temp_value_length += per_flag.PER_Dec_Len;
			value->numbits = temp_value_length;

			value->data = mpool_realloc(ws->Pmemory, value->data, temp_value_length * sizeof(ASNUINT8));

			if (0 > ASN1_PER_Dec_OCTETSTRING_Value(ws, value, per_flag.PER_Dec_Len, &per_flag, UNALIGN)) return ASN1_PER_CHECK_LENGTH_ERROR;
		}
		
		if (temp_loop_i != 1) return 0;
	}
	
	if (per_flag.Range == 1 && per_flag.L_En_Flag == 0)
	{
		if (consinfo->extflag == 1)
		{
			align_flag = UNALIGN;
			if (per_flag.ext_flag == 1)
			{
				align_flag = ALIGN;
				if (0 > ASN1_PER_Dec_ExtLength(ws, consinfo, &per_flag, ALIGN)) return ASN1_PER_CHECK_LENGTH_ERROR;

				value->numbits = per_flag.PER_Dec_Len;
				value->data = mpool_realloc(ws->Pmemory, value->data, per_flag.PER_Dec_Len * sizeof(ASNUINT8));
			}
		}
		else
		{
			align_flag = ALIGN;
		}

		value->numbits = per_flag.PER_Dec_Len;
		if (0 > ASN1_PER_Dec_OCTETSTRING_Value(ws, value, per_flag.PER_Dec_Len, &per_flag,align_flag)) return ASN1_PER_CHECK_LENGTH_ERROR;

		return 0;
	}
	
	if (per_flag.Is_Size == 1)
	{
		align_flag = ALIGN;
		if (consinfo->extflag == 1) align_flag = ALIGN;

		if (0 > ASN1_PER_Dec_strLength(ws, consinfo, &per_flag, align_flag)) return ASN1_PER_CHECK_LENGTH_ERROR;

		value->numbits = per_flag.PER_Dec_Len;
		value->data = mpool_realloc(ws->Pmemory, value->data, per_flag.PER_Dec_Len * sizeof(ASNUINT8));

		if (0 > ASN1_PER_Dec_OCTETSTRING_Value(ws, value, per_flag.PER_Dec_Len, &per_flag, align_flag)) return ASN1_PER_CHECK_LENGTH_ERROR;
	}
	else
	{
		temp_value_length = 0;
		while(sever_flag)
		{	
			if ((sever_flag = ASN1_PER_Dec_SeverLength(ws, consinfo, &per_flag, ALIGN)) < 0) return ASN1_PER_CHECK_LENGTH_ERROR;

			temp_value_length += per_flag.PER_Dec_Len;
			value->numbits = temp_value_length;

			value->data = mpool_realloc(ws->Pmemory, value->data, temp_value_length * sizeof(ASNUINT8));

			if (0 > ASN1_PER_Dec_OCTETSTRING_Value(ws, value, per_flag.PER_Dec_Len, &per_flag, UNALIGN)) return ASN1_PER_CHECK_LENGTH_ERROR;
		}
	}

	return 0;
}

ASNINT32 ASN1_PER_Align_Dec_OCTETSTRING(ASN1WorkSpace *ws, OCTETSTRING *value, Asn1ConsInfo *consinfo)
{
	ASNINT32 ret = 0;
	if (consinfo->lower == consinfo->upper && consinfo->lower <= 2)
		ret = ASN1_PER_UNAlign_Dec_OCTETSTRING(ws, value, consinfo);
	else ret = ASN1_PER_Align_Dec_Inline_OCTETSTRING(ws, value, consinfo);
	return ret;
}

ASNINT32 ASN1_PER_UNAlign_Enc_OCTETSTRING(ASN1WorkSpace *ws, OCTETSTRING *value, Asn1ConsInfo *consinfo)
{
	struct PER_Flag per_flag;
	ASNUINT8 zero;
	ASNINT32 sever_flag = 1;
	ASNINT32 temp_value_length;
	ASNUINT32 process_length = 0;
	ASNINT32 ret = 0;
	ASNINT32 Default_bit = 0;
	ASNUINT8* temp_value = value->data;
	
	per_flag.Range = 0;
	per_flag.Value_length =  value->numbits;
	
	if ((ret = PER_CONSTRAINT_Enc_Process(ws, consinfo, &Default_bit, &per_flag, UNALIGN)) < 0) return ret;
	
	if (per_flag.ext_flag == 1 && per_flag.Value_length >= 16384)
	{
		temp_value_length = per_flag.Value_length;
		while(sever_flag)
		{	
			sever_flag = ASN1_PER_Enc_SeverLength(ws, &temp_value_length, consinfo, &process_length, UNALIGN);
			ASN1_PER_Enc_OCTETSTRING_Value(ws, value,process_length, &per_flag, UNALIGN);
		}

		if (per_flag.Value_length!=0 && (per_flag.Value_length % 16384) == 0)
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

		ASN1_PER_Enc_OCTETSTRING_Value(ws, value, per_flag.Value_length, &per_flag, UNALIGN);
		value->data = temp_value;
		return 0;
	}
	
	if (per_flag.Is_Size == 1)
	{
		ASN1_PER_Enc_strLength(ws, per_flag.Value_length, consinfo, &per_flag, UNALIGN);
		ASN1_PER_Enc_OCTETSTRING_Value(ws, value, per_flag.Value_length, &per_flag, UNALIGN);
	}
	else
	{
		temp_value_length = per_flag.Value_length;
		while(sever_flag)
		{	
			sever_flag = ASN1_PER_Enc_SeverLength(ws, &temp_value_length, consinfo, &process_length, UNALIGN);
			ASN1_PER_Enc_OCTETSTRING_Value(ws, value, process_length, &per_flag, UNALIGN);
		}

		if (per_flag.Value_length!=0 && (per_flag.Value_length % 16384) == 0)
		{
			zero = 0x00;
			ASN1_FillBuffer(ws, &zero, 8, UNALIGN);
		}
	}

	value->data = temp_value;
	return 0;
}

ASNINT32 ASN1_PER_UNAlign_Dec_OCTETSTRING(ASN1WorkSpace *ws, OCTETSTRING *value, Asn1ConsInfo *consinfo)
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

	value->data = (ASNUINT8*)mpool_malloc(ws->Pmemory, 1 * sizeof(ASNUINT8));
	value->numbits = 1;
	per_flag.PER_Dec_Len = 1;

	if ((ret = PER_CONSTRAINT_Dec_Process(ws, consinfo, &Default_bit, &per_flag, UNALIGN)) < 0) return ASN1_PER_CHECK_LENGTH_ERROR;

	if (per_flag.ext_flag == 1)
	{
		temp_value_length = 0;
		temp_current = ws->buffer.current;
		temp_bitOffset = ws->buffer.bitOffset;

		while(sever_flag)
		{	
			temp_loop_i++;
			if ((sever_flag = ASN1_PER_Dec_SeverLength(ws,consinfo, &per_flag, UNALIGN)) < 0) return ASN1_PER_CHECK_LENGTH_ERROR;

			if (temp_loop_i == 1 && sever_flag == 0)
			{
				ws->buffer.current = temp_current;
				ws->buffer.bitOffset = temp_bitOffset;
				sever_flag = 1;
				break;
			}

			temp_value_length += per_flag.PER_Dec_Len;
			value->numbits = temp_value_length;

			value->data = mpool_realloc(ws->Pmemory, value->data, temp_value_length * sizeof(ASNUINT8));

			if (0 > ASN1_PER_Dec_OCTETSTRING_Value(ws, value, per_flag.PER_Dec_Len, &per_flag,UNALIGN)) return ASN1_PER_CHECK_LENGTH_ERROR;
		}
		
		if (temp_loop_i != 1) return 0;
	}
	
	if (per_flag.Range == 1 && per_flag.L_En_Flag == 0)
	{
		if (consinfo->extflag == 1)
		{
			if (0 > ASN1_PER_Dec_ExtLength(ws, consinfo, &per_flag, UNALIGN)) return ASN1_PER_CHECK_LENGTH_ERROR;

			value->numbits = per_flag.PER_Dec_Len;				
			value->data = mpool_realloc(ws->Pmemory, value->data, per_flag.PER_Dec_Len * sizeof(ASNUINT8));
		}

		value->numbits = per_flag.PER_Dec_Len;
		if (0 > ASN1_PER_Dec_OCTETSTRING_Value(ws, value, per_flag.PER_Dec_Len, &per_flag, UNALIGN)) return ASN1_PER_CHECK_LENGTH_ERROR;
		return 0;
	}
	
	if (per_flag.Is_Size == 1)
	{
		if (0 > ASN1_PER_Dec_strLength(ws, consinfo, &per_flag, UNALIGN)) return ASN1_PER_CHECK_LENGTH_ERROR;

		value->numbits = per_flag.PER_Dec_Len;
		value->data = mpool_realloc(ws->Pmemory, value->data, per_flag.PER_Dec_Len * sizeof(ASNUINT8));

		if ( 0 >ASN1_PER_Dec_OCTETSTRING_Value(ws, value, per_flag.PER_Dec_Len, &per_flag,UNALIGN)) return ASN1_PER_CHECK_LENGTH_ERROR;
	}
	else
	{
		temp_value_length = 0;
		while(sever_flag)
		{	
			if ((sever_flag = ASN1_PER_Dec_SeverLength(ws, consinfo, &per_flag, UNALIGN)) < 0) return ASN1_PER_CHECK_LENGTH_ERROR;
			temp_value_length += per_flag.PER_Dec_Len;
			value->numbits = temp_value_length;

			value->data = mpool_realloc(ws->Pmemory, value->data, temp_value_length * sizeof(ASNUINT8));

			if (0 > ASN1_PER_Dec_OCTETSTRING_Value(ws, value, per_flag. PER_Dec_Len, &per_flag, UNALIGN)) return ASN1_PER_CHECK_LENGTH_ERROR;
		}
	}
	return 0;
}

ASNINT32 ASN1_PER_Enc_OCTETSTRING_Value(ASN1WorkSpace *ws,OCTETSTRING *value, ASNUINT32 length, struct PER_Flag *per_flag, ASN1PERAlign Align_Flag)
{
	ASNUINT8 *encode = value->data; 
	ASNINT32 i = 0;
	
	value->data += length;

	while(length)
	{
		if (i == 0){
			ASN1_FillBuffer(ws, encode, 8, Align_Flag);
			i++;
		}
		else
		{
			ASN1_FillBuffer(ws, encode, 8, UNALIGN);
		}
		encode++;
		length--;
	}
	return 0;
}

ASNINT32 ASN1_PER_Dec_OCTETSTRING_Value(ASN1WorkSpace *ws, OCTETSTRING *value, ASNUINT32 length, struct PER_Flag *per_flag, ASN1PERAlign Align_Flag)
{
	ASNUINT8 *Tdecode = (value->data + (value->numbits - length));
	ASNINT32 i = 0;
	ASNINT32 ret = 0;
	while(length)
	{
		if (i == 0)
		{
			if (0 > ASN1_ReadBuffer(ws, Tdecode, 8, Align_Flag)) return ret;
			i++;
		}
		else if (0 > ASN1_ReadBuffer(ws, Tdecode, 8, UNALIGN)) return ret;

		Tdecode++;
		length--;
	}
	return 0;
}

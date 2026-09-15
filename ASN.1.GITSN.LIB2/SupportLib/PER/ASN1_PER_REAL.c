#include "ASN1_PER_REAL.h"


ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Enc_REAL(ASN1WorkSpace*ws, REAL *Tvalue,Asn1ConsInfo *consinfo)
{
	REAL value = *Tvalue;
	ASNINT32 sever_flag = 1;
	ASNUINT32 process_length;
	ASNUINT32 buflen;//value 's length
	ASNUINT8 temp_buf[16];//finally buf
	if(0 == value)
	{
		buflen = 0;		
		ws->dataSize = 0;
//		return 0;
	}
	else if(value > MINUS && value < PLUS)
	{
		ASNUINT8 *pstr = temp_buf;
		ASNUINT8 dvalue[sizeof(value)];//value of buf
		ASNINT32 exponent;
		ASNINT32 *exp = &exponent;
		ASNUINT8 first_encode_byte;
		ASNUINT8 *mstop;//last byte
		ASNUINT8 vmstop;//value of the last byte
		ASNUINT8 *s,*start;
		ASNUINT8 *d;//control dvalue 's address
		ASNUINT32 account = 0;
		
	

	frexp(value,exp);
	exponent -= 1;

	s = (ASNUINT8 *)&value + sizeof(value) - 2;
	start = (ASNUINT8 *)&value;

	first_encode_byte = 0x80 | ((s[1] >> 1) & 0x40);
	for (mstop = d = dvalue;s >= start; d++,s--)
	{
		*d = *s;
		if(*d)
		{
			mstop = d;
		}
	}

	//compute the first byte of value with 1
	dvalue[0] = 0x10 | (dvalue[0] & 0x0f);

	exponent -= 8 * (mstop - dvalue) + 4;

	//the last byte
	vmstop = *mstop;

	//compute finally exponent
	if (!(vmstop & 1))
	{
		ASNUINT8 shift_count = 1;
		ASNUINT8 isshift;
		ASNUINT8 *mpstr;

		//compute the count of zero
		if (!(vmstop & 0x0f))
		{
			shift_count = 4;
		}
		while (0 == ((vmstop >> shift_count) & 1))
		{
			shift_count++;
		}
		isshift = 8 - shift_count;//missing part

		//move all value right
		for (mpstr = dvalue; mpstr <= mstop; mpstr++)
		{
			vmstop = *mpstr;
			*mpstr = account | (vmstop >> shift_count);
			account = vmstop << isshift;
		}
		exponent += shift_count;
	}
	
	//encode exponent
	if(exponent < 0) 
	{
		if((exponent >> 7) == -1) 
		{
			*pstr++ = first_encode_byte | 0x00;
			*pstr++ = exponent;
		} 
		else if((exponent >> 15) == -1) 
		{
			*pstr++ = first_encode_byte | 0x01;
			*pstr++ = exponent >> 8;
			*pstr++ = exponent;
		} 
		else 
		{
			*pstr++ = first_encode_byte | 0x02;
			*pstr++ = exponent >> 16;
			*pstr++ = exponent >> 8;
			*pstr++ = exponent;
		}
	} 
	else if(exponent <= 0x7f) 
	{
		*pstr++ = first_encode_byte | 0x00;
		*pstr++ = exponent;
	} 
	else if(exponent <= 0x7fff) 
	{
		*pstr++ = first_encode_byte | 0x01;
		*pstr++ = exponent >> 8;
		*pstr++ = exponent;
	} 
	else 
	{
		*pstr++ = first_encode_byte | 0x02;
		*pstr++ = exponent >> 16;
		*pstr++ = exponent >> 8;
		*pstr++ = exponent;
	}

	
		buflen = (mstop - dvalue) + 1;
		memcpy(pstr,dvalue,buflen);//only copy value
		pstr += buflen;
		buflen = pstr - temp_buf;

//		while (sever_flag)
//		{	
//			sever_flag = ASN1_PER_Enc_SeverLength(ws,&buflen,NULL,
//				&process_length,ALIGN);
//			ASN1_FillBuffer(ws,temp_buf,8*process_length,ALIGN);
//		}
	
//		return 0;
	}
	else if(value >= PLUS)
	{
//		ws->buffer.current[0] = 0x40;
		buflen = 1;
		temp_buf[0] = 0x40;
//		ws->buffer.current++;
		ws->dataSize = 1;
//		return 0;
	}
	else
	{
//		ws->buffer.current[0] = 0x41;
		buflen = 1;
		temp_buf[0] = 0x41;
//		ws->buffer.current++;
		ws->dataSize = 1;
//		return 0;
	}

	while (sever_flag)
	{	
		sever_flag = ASN1_PER_Enc_SeverLength(ws,&buflen,NULL,
			&process_length,ALIGN);
		ASN1_FillBuffer(ws,temp_buf,8*process_length,ALIGN);
	}
	
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_PER_Align_Dec_REAL(ASN1WorkSpace*ws, REAL *value,Asn1ConsInfo *consinfo)
{
	ASNUINT8 first_byte;
	ASNUINT32 sever_flag=1;
	ASNUINT8 *F_Uc_REAL_Memony;
	struct PER_Flag flag;
	
	sever_flag = ASN1_PER_Dec_SeverLength(ws,NULL,&flag,ALIGN);
	if(0>sever_flag)
		return ASN1_PER_CHECK_LENGTH_ERROR;
	F_Uc_REAL_Memony = mpool_malloc(ws->Pmemory,flag.PER_Dec_Len*sizeof(ASNUINT8));
	if(0>ASN1_ReadBuffer(ws,F_Uc_REAL_Memony,8*flag.PER_Dec_Len,ALIGN))
		return ASN1_PER_CHECK_LENGTH_ERROR;

	if (0 == flag.PER_Dec_Len)
	{
		*value = 0;
		return 0;
	}
	first_byte = F_Uc_REAL_Memony[0];
	switch(first_byte & 0xc0)
	{
	case 0x40:
		switch(first_byte)
		{
		case 0x40:/* 01000000: PLUS-INFINITY */
			*value = PLUS;
			F_Uc_REAL_Memony++;
			return 0;
		case 0x41:/* 01000001: MINUS-INFINITY */
		    *value = MINUS;
			F_Uc_REAL_Memony++;
			return 0;
		default:/*reserve*/
		    return 1;
		}
	case 0x00:/*NR{1,2,3} format*/
		*value = atof(F_Uc_REAL_Memony+1);
		F_Uc_REAL_Memony += flag.PER_Dec_Len;
		return 0;
	}
	
	// Binary representation.
	{
		REAL m = 0.0;
		ASNINT32 exponent;/* exponent value */
		ASNUINT32 elen;	/* exponent value length */
		ASNUINT32 scaleF;/*Binary scale*/
		ASNUINT32 baseF;/*base*/
		ASNUINT8 *ptr;
		ASNUINT8 *end;
		ASNINT8 sign,signen = 0;
		ASNUINT32L i,j = 0;

		switch((first_byte & 0x30) >> 4)
		{
		case 0x00:
			baseF = 1;/* base 2 */
			break;
		case 0x01:
			baseF = 3;/* base 8 */
			break;
		case 0x10:
			baseF = 4;/* base 16 */
			break;
		default:/*reserve*/
			return 1;
		}

		sign = first_byte & 0x40; /* bit 7 */
		scaleF = (first_byte &0x0c) >> 2;/* bit 4 to 3 */
		if(0x03 == (first_byte & 0x03))
		{
			elen = F_Uc_REAL_Memony[1];
			ptr = &F_Uc_REAL_Memony[2];
		}
		else
		{
			elen = (first_byte & 0x03) + 1;
			ptr = &F_Uc_REAL_Memony[1];			
		}
		end = ptr + elen;
		/*fetch the exponent number*/
		exponent = *ptr;
		if (*ptr & 0x80)
		{
			signen = 1;
			for(i = 0;i < elen-1;i++)
			{
				ptr[i] = ~ptr[i]; 
			}
			ptr[elen -1] = ~(ptr[elen -1]) + 1;
			while (0 == ptr[elen - j++] && j<=elen)
			{
				ptr[elen - j] += 1;
			}
			exponent = *ptr;
		}
		ptr++;
		for (;ptr < end;ptr++)
		{
			exponent = (exponent << 8) + *ptr;
		}
		if (signen)
		{
			exponent = -exponent;
		}
		end = F_Uc_REAL_Memony + flag.PER_Dec_Len;
		if(ptr < end) 
		{
			for(; ptr < end; ptr++)
			{
				m = m * 256 + *ptr;
			}
		}
		/*(S * N * 2^F) * B^E*/
		/*
		m = ldexp(m, scaleF) * pow(pow(2, base), exponent);
		*/
		m = ldexp(m, exponent * baseF + scaleF);
		*value = sign ? -m : m;
		F_Uc_REAL_Memony += flag.PER_Dec_Len;
	}
	return 0;
}


ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Enc_REAL(ASN1WorkSpace*ws, REAL *Tvalue,Asn1ConsInfo *consinfo)
{
	REAL value = *Tvalue;
	ASNINT32 sever_flag = 1;
	ASNINT32 process_length;
	if(0 == value)
	{
		ws->dataSize = 0;
		return 0;
	}
	else if(value > MINUS && value < PLUS)
	{
		ASNUINT8 temp_buf[16];//finally buf
		ASNUINT8 *pstr = temp_buf;
		ASNUINT8 dvalue[sizeof(value)];//value of buf
		ASNINT32 exponent;
		ASNINT32 *exp = &exponent;
		ASNUINT8 first_encode_byte;
		ASNUINT8 *mstop;//last byte
		ASNUINT8 vmstop;//value of the last byte
		ASNUINT8 *s,*start;
		ASNUINT8 *d;//control dvalue 's address
		ASNUINT32 account = 0;
		ASNUINT32 buflen;//value 's length
	

	frexp(value,exp);
	exponent -= 1;

	s = (ASNUINT8 *)&value + sizeof(value) - 2;
	start = (ASNUINT8 *)&value;

	first_encode_byte = 0x80 | ((s[1] >> 1) & 0x40);
	for (mstop = d = dvalue;s >= start; d++,s--)
	{
		*d = *s;
		if(*d)
		{
			mstop = d;
		}
	}

	//compute the first byte of value with 1
	dvalue[0] = 0x10 | (dvalue[0] & 0x0f);

	exponent -= 8 * (mstop - dvalue) + 4;

	//the last byte
	vmstop = *mstop;

	//compute finally exponent
	if (!(vmstop & 1))
	{
		ASNUINT8 shift_count = 1;
		ASNUINT8 isshift;
		ASNUINT8 *mpstr;

		//compute the count of zero
		if (!(vmstop & 0x0f))
		{
			shift_count = 4;
		}
		while (0 == ((vmstop >> shift_count) & 1))
		{
			shift_count++;
		}
		isshift = 8 - shift_count;//missing part

		//move all value right
		for (mpstr = dvalue; mpstr <= mstop; mpstr++)
		{
			vmstop = *mpstr;
			*mpstr = account | (vmstop >> shift_count);
			account = vmstop << isshift;
		}
		exponent += shift_count;
	}
	
	//encode exponent
	if(exponent < 0) 
	{
		if((exponent >> 7) == -1) 
		{
			*pstr++ = first_encode_byte | 0x00;
			*pstr++ = exponent;
		} 
		else if((exponent >> 15) == -1) 
		{
			*pstr++ = first_encode_byte | 0x01;
			*pstr++ = exponent >> 8;
			*pstr++ = exponent;
		} 
		else 
		{
			*pstr++ = first_encode_byte | 0x02;
			*pstr++ = exponent >> 16;
			*pstr++ = exponent >> 8;
			*pstr++ = exponent;
		}
	} 
	else if(exponent <= 0x7f) 
	{
		*pstr++ = first_encode_byte | 0x00;
		*pstr++ = exponent;
	} 
	else if(exponent <= 0x7fff) 
	{
		*pstr++ = first_encode_byte | 0x01;
		*pstr++ = exponent >> 8;
		*pstr++ = exponent;
	} 
	else 
	{
		*pstr++ = first_encode_byte | 0x02;
		*pstr++ = exponent >> 16;
		*pstr++ = exponent >> 8;
		*pstr++ = exponent;
	}

	
		buflen = (mstop - dvalue) + 1;
		memcpy(pstr,dvalue,buflen);//only copy value
		pstr += buflen;
		buflen = pstr - temp_buf;

		while (sever_flag)
		{	
			sever_flag = ASN1_PER_Enc_SeverLength(ws,&buflen,NULL,
				&process_length,UNALIGN);
			ASN1_FillBuffer(ws,temp_buf,8*process_length,UNALIGN);
		}	
		return 0;
	}
	else if(value > PLUS)
	{
		ws->buffer.current[0] = 0x40;
		ws->buffer.current++;
		ws->dataSize = 1;
		return 0;
	}
	else
	{
		ws->buffer.current[0] = 0x41;
		ws->buffer.current++;
		ws->dataSize = 1;
		return 0;
	}
	return 0;

}

ASN1_CPPLINK ASNINT32 ASN1_PER_UNAlign_Dec_REAL(ASN1WorkSpace*ws, REAL *value,Asn1ConsInfo *consinfo)
{
	ASNUINT8 first_byte;
	ASNUINT32 sever_flag=1;
	ASNUINT8 *F_Uc_REAL_Memony;
	struct PER_Flag flag;
	
	sever_flag = ASN1_PER_Dec_SeverLength(ws,NULL,&flag,UNALIGN);
	if(0>sever_flag)
		return ASN1_PER_CHECK_LENGTH_ERROR;
	F_Uc_REAL_Memony = mpool_malloc(ws->Pmemory,flag.PER_Dec_Len*sizeof(ASNUINT8));
	if(0>ASN1_ReadBuffer(ws,F_Uc_REAL_Memony,8*flag.PER_Dec_Len,UNALIGN))
		return ASN1_PER_CHECK_LENGTH_ERROR;

	if (0 == flag.PER_Dec_Len)
	{
		*value = 0;
		return 0;
	}
	first_byte = F_Uc_REAL_Memony[0];
	switch(first_byte & 0xc0)
	{
	case 0x40:
		switch(first_byte)
		{
		case 0x40:/* 01000000: PLUS-INFINITY */
			*value = PLUS;
			F_Uc_REAL_Memony++;
			return 0;
		case 0x41:/* 01000001: MINUS-INFINITY */
		    *value = MINUS;
			F_Uc_REAL_Memony++;
			return 0;
		default:/*reserve*/
		    return 1;
		}
	case 0x00:/*NR{1,2,3} format*/
		*value = atof(F_Uc_REAL_Memony+1);
		F_Uc_REAL_Memony += flag.PER_Dec_Len;
		return 0;
	}
	
	// Binary representation.
	{
		REAL m = 0.0;
		ASNINT32 exponent;/* exponent value */
		ASNUINT32 elen;	/* exponent value length */
		ASNUINT32 scaleF;/*Binary scale*/
		ASNUINT32 baseF;/*base*/
		ASNUINT8 *ptr;
		ASNUINT8 *end;
		ASNINT8 sign,signen = 0;
		ASNUINT32L i,j = 0;

		switch((first_byte & 0x30) >> 4)
		{
		case 0x00:
			baseF = 1;/* base 2 */
			break;
		case 0x01:
			baseF = 3;/* base 8 */
			break;
		case 0x10:
			baseF = 4;/* base 16 */
			break;
		default:/*reserve*/
			return 1;
		}

		sign = first_byte & 0x40; /* bit 7 */
		scaleF = (first_byte &0x0c) >> 2;/* bit 4 to 3 */
		if(0x03 == (first_byte & 0x03))
		{
			elen = F_Uc_REAL_Memony[1];
			ptr = &F_Uc_REAL_Memony[2];
		}
		else
		{
			elen = (first_byte & 0x03) + 1;
			ptr = &F_Uc_REAL_Memony[1];			
		}
		end = ptr + elen;
		/*fetch the exponent number*/
		exponent = *ptr;
		if (*ptr & 0x80)
		{
			signen = 1;
			for(i = 0;i < elen-1;i++)
			{
				ptr[i] = ~ptr[i]; 
			}
			ptr[elen -1] = ~(ptr[elen -1]) + 1;
			while (0 == ptr[elen - j++] && j<=elen)
			{
				ptr[elen - j] += 1;
			}
			exponent = *ptr;
		}
		ptr++;
		for (;ptr < end;ptr++)
		{
			exponent = (exponent << 8) + *ptr;
		}
		if (signen)
		{
			exponent = -exponent;
		}
		end = F_Uc_REAL_Memony + flag.PER_Dec_Len;
		if(ptr < end) 
		{
			for(; ptr < end; ptr++)
			{
				m = m * 256 + *ptr;
			}
		}
		/*(S * N * 2^F) * B^E*/
		/*
		m = ldexp(m, scaleF) * pow(pow(2, base), exponent);
		*/
		m = ldexp(m, exponent * baseF + scaleF);
		*value = sign ? -m : m;
		F_Uc_REAL_Memony += flag.PER_Dec_Len;
	}
	return 0;
}



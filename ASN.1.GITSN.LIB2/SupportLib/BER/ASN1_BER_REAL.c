#include "ASN1_BER_REAL.h"

ASNINT32 ASN1_BER_Enc_REAL_value(ASN1WorkSpace *ws, REAL *Tvalue)
{
	REAL value = *Tvalue;
	if (0 == value)
	{
		ws->dataSize = 0;
		return 0;
	}
	else if (value > MINUS && value < PLUS)
	{
		ASNUINT8 dvalue[sizeof(value)];				//value of buf
		ASNUINT8 *d;								// control dvalue 's address

		ASNUINT8 temp_buf[16], *pstr = temp_buf;	//finally buf
		ASNINT32 exponent, *exp = &exponent;

		ASNUINT8 first_encode_byte;

		ASNUINT8 *mstop;							//last byte
		ASNUINT8 vmstop;							//value of the last byte
		ASNUINT8 *s, *start;
		ASNUINT32 account = 0;
		ASNUINT32 buflen;							//value 's length

		frexp(value, exp);
		exponent -= 1;

		s = (ASNUINT8 *)&value + sizeof(value) - 2;
		start = (ASNUINT8 *)&value;

		first_encode_byte = 0x80 | ((s[1] >> 1) & 0x40);

		for (mstop = d = dvalue;s >= start; d++,s--)
		{
			*d = *s;
			if (*d) mstop = d;
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
				shift_count = 4;

			while(0 == ((vmstop >> shift_count) & 1))
				shift_count++;

			isshift = 8 - shift_count;//missing part

			//move all value right
			for(mpstr = dvalue; mpstr <= mstop; mpstr++)
			{
				vmstop = *mpstr;
				*mpstr = account | (vmstop >> shift_count);
				account = vmstop << isshift;
			}
			exponent += shift_count;
		}
	
		//encode exponent
		if (exponent < 0) 
		{
			if ((exponent >> 7) == -1) 
			{
				*pstr++ = first_encode_byte | 0x00;
				*pstr++ = exponent;
			} 
			else if ((exponent >> 15) == -1) 
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
		else if (exponent <= 0x7f) 
		{
			*pstr++ = first_encode_byte | 0x00;
			*pstr++ = exponent;
		} 
		else if (exponent <= 0x7fff) 
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
		memcpy(pstr, dvalue, buflen);					// only copy value
		pstr += buflen;
		buflen = pstr - temp_buf;
		ASN1_BER_Enc_Length(ws, buflen);
		ASN1_BER_FillBuffer(ws, temp_buf, buflen, 0);	// copy the result of value

		ws->dataSize = buflen;
		ws->buffer.current += ws->dataSize;

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

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_REAL_value(ASN1WorkSpace*ws, REAL *value, ASNUINT32L length)
{
	ASNUINT8 first_byte;
	if (0 == length)
	{
		*value = 0;
		return 0;
	}
	first_byte = ws->buffer.current[0];
	switch(first_byte & 0xc0)
	{
	case 0x40:
		switch(first_byte)
		{
		case 0x40:/* 01000000: PLUS-INFINITY */
			*value = PLUS;
			ws->buffer.current++;
			return 0;
		case 0x41:/* 01000001: MINUS-INFINITY */
		    *value = MINUS;
			ws->buffer.current++;
			return 0;
		default:/*reserve*/
		    return 1;
		}
	case 0x00:/*NR{1,2,3} format*/
		*value = atof(ws->buffer.current+1);
		ws->buffer.current += length;
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
			elen = ws->buffer.current[1];
			ptr = &ws->buffer.current[2];
		}
		else
		{
			elen = (first_byte & 0x03) + 1;
			ptr = &ws->buffer.current[1];			
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
		end = ws->buffer.current + length;
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
		ws->buffer.current += length;
	}
	return 0;
}

ASNINT32 ASN1_BER_Enc_REAL(ASN1WorkSpace *ws, REAL *Tvalue, ASN1TagType flag)
{
	ASN1_Tag_Move_Pointer(ws,ITS_ASN_UNIV | ITS_ASN_PRIM | ASN1_TYPE_REAL, flag);
	ASN1_BER_Enc_REAL_value(ws, Tvalue);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_BER_Dec_REAL(ASN1WorkSpace*ws, REAL* value,ASNINT32 length,ASN1TagType flag)
{
	if (ASN1EXPL == flag)
	{
    	ASN1_BER_Dec_Tag(ws,ITS_ASN_UNIV|ITS_ASN_PRIM|ASN1_TYPE_REAL);
		ASN1_BER_Dec_Length(ws);
		ASN1_BER_Dec_REAL_value(ws,value,ws->dataSize);
	}
    else
	ASN1_BER_Dec_REAL_value(ws,value,length);

	return 0;
}


// int main()
// {
// 	ASN1WorkSpace buf;
// 	int i;
// //	REAL encodevalue = 0.1e+309;	
// 	REAL encodevalue = -0.53;
// 	REAL *encode = &encodevalue;
// 	REAL decodevalue = 0;
// 	buf.buffer.current = malloc(80);
// 	buf.buffer.data = buf.buffer.current;
// 	ASN1_BER_Enc_REAL(&buf,encodevalue,ASN1EXPL);
// 	for(i = 0;i < buf.buffer.current-buf.buffer.data;i++)
// 		printf("%02x\n",buf.buffer.data[i]);
// 	buf.buffer.current = buf.buffer.data;
// 	ASN1_BER_Dec_REAL(&buf,&decodevalue,ASN1EXPL);
// 	printf("%lf\n",decodevalue);
// 	free(buf.buffer.data);
// 	return 0;
// }

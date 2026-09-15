#include "ASN1_Operate_Byte.h"

ASNUINT8 ZERO_AFTER[9]  = { 0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00 };
ASNUINT8 ZERO_BEFTER[9] = { 0xFF, 0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01, 0x00 };

ASNINT32 ASN1_FillBuffer(ASN1WorkSpace* ws,ASNUINT8* value, ASNUINT32 length,ASN1PERAlign prefill)
{
	ASNUINT8* temp_encode;
	ASNINT32 temp_byte = 0;
	ASNINT32 i = 0;
	ASNINT32 encode_bit = 8;
	ASNUINT8* ZERO_POINTER;
	ASNUINT32 zero_length = length; 
	ASNINT32 temp_length = 0;
	
	if (0 == length) return 0;

	reset_memony(ws);
	Bit_Fill_Process(&temp_encode, value, length,ws);

	if (prefill == ALIGN)
	{
		if (ws->buffer.bitOffset != 8)
		{
			ws->buffer.current++;
		    ws->buffer.bitOffset = 8;
		}
	}
		
	if(ws->buffer.bitOffset == 0)
	{
		ws->buffer.current++;
		ws->buffer.bitOffset = 8;
	}
	reset_memony(ws);
	
	ZERO_POINTER = ws->buffer.current; 
	*ZERO_POINTER &= ZERO_AFTER[ws->buffer.bitOffset];
	ZERO_POINTER++;

	if (zero_length > ws->buffer.bitOffset)
	{
		zero_length -= ws->buffer.bitOffset;
		memset(ZERO_POINTER, 0x00, zero_length / 8);
		if (zero_length % 8 != 0)
		{
			ZERO_POINTER += zero_length / 8;
			*ZERO_POINTER &= ZERO_BEFTER[zero_length%8];
		}
	}

	if (length <= ws->buffer.bitOffset)
	{
		*ws->buffer.current |= ((*temp_encode) >> (8 - ws->buffer.bitOffset));
		ws->buffer.bitOffset = ws->buffer.bitOffset - length;
		return 0;
	}
	
	if (ws->buffer.bitOffset != 0)
	{
		temp_byte = 1;
	}

	temp_byte += ((length-ws->buffer.bitOffset) / 8);

	if ((length-ws->buffer.bitOffset) % 8)
	{
		temp_byte++;
	}

	i = length;
	while(i > 0)
	{
		if (encode_bit == 8)
		{
			*ws->buffer.current |= (*temp_encode) >> (8 - ws->buffer.bitOffset);
			ws->buffer.current++;
			temp_length++;
			reset_memony(ws);
			i			-= ws->buffer.bitOffset;
			encode_bit	-= ws->buffer.bitOffset;
		}
		else
		{
			*ws->buffer.current |= (*temp_encode) << (8 - encode_bit);
			i			-= encode_bit; 
			encode_bit	-= encode_bit;
		}
		
		if(!encode_bit)
		{
			temp_encode++;
			encode_bit = 8;
		}
	}

	if(temp_byte == temp_length)
	{
		ws->buffer.current--;
	}
	
	ws->buffer.bitOffset = 8 - (length - ws->buffer.bitOffset) % 8;
	if (ws->buffer.bitOffset == 8)
	{
		ws->buffer.bitOffset = 0;
	}
	return 0;
}

ASNINT32 ASN1_ReadBuffer(ASN1WorkSpace* ws, ASNUINT8* value, ASNUINT32 length, ASN1PERAlign prefill)
{
	ASNUINT32 temp_byte  = 0;
	ASNUINT8* temp_encode;
	ASNINT32 i;
	ASNUINT8* temp_current;
	
	if (0 == length) return 0;
	if (0 > ASN1_PER_IsWSrange(ws,length)) return -403;

	if (prefill == ALIGN)
	{
		if (ws->buffer.bitOffset != 8)
		{
			ws->buffer.current++;
			ws->buffer.bitOffset = 8;
		}
	}

	if (ws->buffer.bitOffset == 0)
	{
		ws->buffer.current++;
		ws->buffer.bitOffset = 8;
	}
	
	if (length <= ws->buffer.bitOffset)
	{
		*value = (*ws->buffer.current << (8-ws->buffer.bitOffset));
		*value = *value>>(8 - length);

		ws->buffer.bitOffset = ws->buffer.bitOffset - length;
		return 0;
	}

// 	if (length%8){
// 		temp_byte = length/8+1;
// 	}
// 	else{
// 		temp_byte = length/8;
// 	}

	if (ws->buffer.bitOffset != 0) temp_byte = 1;

	temp_byte += ((length - ws->buffer.bitOffset) / 8);

	if ((length - ws->buffer.bitOffset) % 8) temp_byte++;

	i = temp_byte;
	temp_current = ws->buffer.current;
	
	temp_encode = (ASNUINT8*)malloc((temp_byte + 1) * sizeof(ASNUINT8));
	/*memset(temp_encode,0x00,temp_byte+1);*/
	memcpy(temp_encode, ws->buffer.current, temp_byte);
	
	Bit_Read_Process(temp_encode,ws->buffer.bitOffset,temp_byte,length);

	i = 1;
	if (length%8)
		i += (length/8);
	else i += (length/8-1);

	memcpy(value, temp_encode, i);
	
// 	if(temp_byte == (ws->buffer.current - temp_current)){
		ws->buffer.current += (temp_byte - 1);
// 	}
// 	else{
// 		ws->buffer.current += (temp_byte);
// 	}

	ws->buffer.bitOffset = 8 - (length - ws->buffer.bitOffset) % 8;

	if (8 == ws->buffer.bitOffset) ws->buffer.bitOffset = 0;

	free(temp_encode);
	return 0;
}


ASNINT32 Bit_Fill_Process(ASNUINT8 **encode, ASNUINT8 *value, ASNUINT32 bit_length, ASN1WorkSpace* ws)
{
	ASNINT32 temp_byte = 0;
	ASNUINT8 *temp_encode;

	if (bit_length % 8)
		temp_byte += bit_length / 8 + 1;
	else
		temp_byte += bit_length / 8;
	
	temp_encode = *encode = (ASNUINT8 *)mpool_malloc(ws->Pmemory, temp_byte * sizeof(ASNUINT8));
	memcpy(temp_encode, value, temp_byte);
	temp_encode += (temp_byte - 1);

	if (bit_length % 8) *temp_encode <<= 8 - (bit_length % 8);

	return 0;
}

ASN1_CPPLINK ASNINT32 Bit_Read_Process(ASNUINT8* decode,ASNINT32 ebit,ASNINT32 ebyte,ASNUINT32 length)
{
	ASNUINT8* temp_decode = decode;
	ASNUINT8* temp_decode_next = decode;
	ASNINT32 temp_ebyte = ebyte;
	ASNINT32 encode_bit = 8;
	ASNINT32 i;
	
// 	while(temp_ebyte){
// 		*temp_encode <<= (8 - ebit);
// 		*temp_encode |= *(temp_encode+1) >> (8-ebit);
// 		temp_encode++;
// 		temp_ebyte--;
// 	}
	i = length;
	while(i > 0)
	{
		//lose function
		/*		i = 1;*/
		if (encode_bit==8){
			*temp_decode = ((*temp_decode_next)<<(8-ebit));
			temp_decode_next++;
			i = i - ebit;
			encode_bit = encode_bit - ebit;
			/*			ws->buffer.bitOffset = 8;*/
		}
		else{
			*temp_decode |= (*temp_decode_next)>>ebit;
			i = i - encode_bit;
			encode_bit = 0;
		}
		//		*(ws->buffer.current+1) |= (*temp_encode)<<ws->buffer.bitOffset;
		
		
		if(!(encode_bit)){
			temp_decode++;
			encode_bit = 8;
		}
		// 		ws->buffer.bitOffset = 8;
	}
	temp_decode = decode;
	if (length%8){
		temp_decode += (length/8);
	}
	else{
		temp_decode += (length/8-1);
	}
	
	if(length%8){
		*temp_decode >>= (8-length%8);
	}
	
	return 0;
}

ASN1_CPPLINK ASNINT32 reset_memony(ASN1WorkSpace *ws)
{
	if (ws->buffer.current == ws->buffer.end) ASN1_RESET_WS_INFO(ws, (ws->buffer.end - ws->buffer.data) + 40960);
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_XER_FillBuffer(ASN1WorkSpace* ws,ASNUINT8* value,
							 ASNUINT32 length)
{
	if(ws->buffer.current+length >= ws->buffer.end){
		ASN1_RESET_WS_INFO(ws,(ws->buffer.end -ws->buffer.data)+length);
	}
	memmove(ws->buffer.current,value,length);
	ws->buffer.current+=length;
	return 0;
}



ASN1_CPPLINK ASNINT32 ASN1_XER_ReadBuffer(ASN1WorkSpace* ws,ASNUINT8* value,
							 ASNUINT32 length)
{
	memmove(value,ws->buffer.current,length);
	ws->buffer.current+=length;
	return 0;
}

//ASN1_CPPLINK ASNINT32 ASN1_BER_FillBuffer(ASN1WorkSpace* ws, ASNUINT8 *value, ASNUINT32 length, ASNINT32 offset_value)
ASN1_CPPLINK ASNINT32 ASN1_BER_FillBuffer(ASN1WorkSpace* ws, ASNUINT8 *src, ASNUINT32 size, ASNINT32 idx)
{
	if(&ws->buffer.current[idx + size] >= ws->buffer.end)
	{
//		ASN1_RESET_WS_INFO(ws, (ws->buffer.end - ws->buffer.data) + idx + size);
		ASNUINT32 newSize = (ASNUINT32)(ws->buffer.end - ws->buffer.data) << 1;	// double size
		ASN1_RESET_WS_INFO(ws, newSize);
	}
	memmove(&ws->buffer.current[idx], src, size);
/*	ws->buffer.current+=length;*/
	return 0;
}

ASN1_CPPLINK ASNINT32 ASN1_BER_ReadBuffer(ASN1WorkSpace* ws,ASNUINT8* value,
							 ASNUINT32 length)
{
	memmove(value,ws->buffer.current,length);
	/*ws->buffer.current+=length;*/
	return 0;
}

ASNINT32 Compare_Letter(ASNINT32 table_count, ASNINT8 *Compare_string)
{
	if (table_count == 0) return 1;
	if (Compare_string[0] >= 'A' && Compare_string[0] <= 'Z') return 0;
	return 1;
}

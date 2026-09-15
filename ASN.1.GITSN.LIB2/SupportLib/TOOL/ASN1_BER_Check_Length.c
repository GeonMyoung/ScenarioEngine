#include "ASN1_Print.h"
#include "ASN1_BER_Check_Length.h"
ASNINT32 ASN1_BER_Dec_Check_Length_Tag(ASN1WorkSpace *ws)
{
	if ((*ws->buffer.current & 0x1f) == 0x1f)
	{	// tag is complex
		if (0 > ASN1_BER_IsWSrange(ws, 1)) return -1;
		else ws->buffer.current++;

		while (((*(ws->buffer.current))& 0x80) != 0x00)
		{
			if (0>ASN1_BER_IsWSrange(ws, 1)) return -1;
			else ws->buffer.current++;
		}

		if (0 > ASN1_BER_IsWSrange(ws, 1)) return -1;
        else ws->buffer.current++;

        return 0;
	}
	else
	{	// tak is simple
		if (0 > ASN1_BER_IsWSrange(ws, 1)) return -1;
		else ws->buffer.current++;

		return 0;
	}
}

ASNINT32 ASN_BER_Dec_Check_Length(ASN1WorkSpace *ws)
{
	ASNUINT32 i;
	ASNUINT32 F_Uc_Length = 0;
	ASNUINT32 F_Uc_Length_temp=0;

	if (ws->buffer.current[0] <= 0x7F)
	{	// length is simple
		F_Uc_Length_temp = *ws->buffer.current;
		if (0 > ASN1_BER_IsWSrange(ws, 1)) return -1;
		else ws->buffer.current += 1;							//move pointer
	}
	else
	{
		if (ws->buffer.current[0] == 0x80)
		{	// length is Start-Of-Contents
			ws->dataSize = -1;

			if (0 > ASN1_BER_IsWSrange(ws, 1)) return -1;
			else ws->buffer.current += 1;	

			return 0;
		}
		
		// length is complex
		F_Uc_Length = ws->buffer.current[0] & 0x7F;				// length of length
		for (i = 1; i <= F_Uc_Length; i++)					
		{
			F_Uc_Length_temp <<= 8;
			F_Uc_Length_temp += ws->buffer.current[i];
		}

		if (0 > ASN1_BER_IsWSrange(ws, F_Uc_Length + 1)) return -1;
		else ws->buffer.current += F_Uc_Length + 1;
	}	
	
	ws->dataSize = F_Uc_Length_temp;
	return 0;
}
ASNINT32 ASN1_BER_CHECK_Length_Process(ASN1WorkSpace *ws)	// skip single ASN.1 VALUE and get length of ASN.1 VALUE
{
	ASNUINT8* tagvalue;
	ASNUINT8* lenvalue;
	ASNINT32 level = 0;
	ASNINT32 indef = 0;
	
	tagvalue = ws->buffer.current;							// save first byte of TAG
	if (0 > ASN1_BER_Dec_Check_Length_Tag(ws))	return -1;	// pass tag
	if (0 > ASN_BER_Dec_Check_Length(ws))		return -1;	// pass length or set dataSize to -1

	indef = ws->dataSize; 
	lenvalue = ws->buffer.current;
	
	if (*tagvalue & 0x20)
	{	// this is construct
		while (ASN1_BER_Dec_Isloop(ws, lenvalue, indef))
			if(0 > ASN1_BER_CHECK_Length_Process(ws)) return -1;

		if ((-1 == indef)  && (*ws->buffer.current == 0x00 && *(ws->buffer.current + 1) == 0x00))
		{	// if indefinite length and current pointer end flag,current add two hank Length Debug
			if (0 > ASN1_BER_IsWSrange(ws, 2)) return -1;
			ws->buffer.current += 2;
		}
	}
	else
	{	// this is primitive
		if (0 > ASN1_BER_IsWSrange(ws, ws->dataSize)) return -1;
		else
		{
			ws->buffer.current += ws->dataSize;
			return 0;
		}
	}
	return 0;
}

ASN1_CPPLINK ASNINT32 _ASN1_BER_CHECK_Length(ASN1WorkSpace *ws)
{
	ASNUINT8 * ps = ws->buffer.current;
	int len=0;
	int ret = ASN1_BER_CHECK_Length_Process(ws);
	if (ws->buffer.Vdeocd_valid<ws->buffer.current)
	{
		asn_printf("ws->buffer.Vdeocd_valid = %p\n",ws->buffer.Vdeocd_valid);
		asn_printf("ws->buffer.current = %p\n",ws->buffer.current);
		ws->buffer.current = ps;
		return -59;
	}
	ws->buffer.current = ps;
	
	if( 0 > ret ){
		asn_printf("ws->buffer.Vdeocd_valid = %p\n",ws->buffer.Vdeocd_valid);
		asn_printf("ws->buffer.current = %p\n",ws->buffer.current);
		return ASN1_BER_CHECK_LENGTH_ERROR;
	}
	return ret;
}

ASN1_CPPLINK ASNINT32 _ASN1_BER_CHECK_Length_Opentype(ASN1WorkSpace *ws)
{
	
	int ret = ASN1_BER_CHECK_Length_Process(ws);
	if( 0 > ret )
	{
		return -11;
	}
	return ret;
}

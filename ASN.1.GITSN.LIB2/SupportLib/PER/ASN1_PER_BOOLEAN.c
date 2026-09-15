#include "ASN1_PER_BOOLEAN.h"

ASNINT32 ASN1_PER_Align_Enc_BOOLEAN(ASN1WorkSpace*ws, BOOLEAN *value,Asn1ConsInfo *consinfo)
{
	ASNUINT8 ch;
	if (0==*value)
	{
		ch = 0;
		ASN1_FillBuffer(ws, &ch,1,UNALIGN);
	}
	else
	{
		ch = 1;
		ASN1_FillBuffer(ws, &ch,1,UNALIGN);
	}
	return 0;
}


ASNINT32 ASN1_PER_Align_Dec_BOOLEAN(ASN1WorkSpace*ws, BOOLEAN *value,Asn1ConsInfo *consinfo)
{
	ASNUINT8 ch;
	if(0>ASN1_ReadBuffer(ws,&ch,1,UNALIGN))
		return ASN1_PER_CHECK_LENGTH_ERROR;
	if (ch)
	{
		*value = 1;
	}
	else
	{
		*value = 0;
	}
	return 0;
}


ASNINT32 ASN1_PER_UNAlign_Enc_BOOLEAN(ASN1WorkSpace*ws, BOOLEAN *value,Asn1ConsInfo *consinfo)
{
	ASNUINT8 ch;
	if (0==*value)
	{
		ch = 0;
		ASN1_FillBuffer(ws, &ch,1,UNALIGN);
	}
	else
	{
		ch = 1;
		ASN1_FillBuffer(ws, &ch,1,UNALIGN);
	}
	return 0;
}

ASNINT32 ASN1_PER_UNAlign_Dec_BOOLEAN(ASN1WorkSpace*ws, BOOLEAN *value,Asn1ConsInfo *consinfo)
{
	ASNUINT8 ch;
	if(0>ASN1_ReadBuffer(ws,&ch,1,UNALIGN))
		return ASN1_PER_CHECK_LENGTH_ERROR;
	if (ch)
	{
		*value = 1;
	}
	else
	{
		*value = 0;
	}
	return 0;
}



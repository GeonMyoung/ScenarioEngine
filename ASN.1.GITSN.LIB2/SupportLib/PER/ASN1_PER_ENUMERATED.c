#include "ASN1_PER_ENUMERATED.h"

ASNINT32 ASN1_PER_Align_Enc_ENUMERATED_child(ASN1WorkSpace *ws, ENUMERATED index, ASNBOOL extbit, Asn1ConsInfo *conss)
{
 	ASNUINT8 filldata = 0;
	ASNINT64 temp_index = index;
	if (extbit)
 	{
		conss->extflag = 0;
		if (index < 64)
		{
			ASN1_FillBuffer(ws, &extbit, 1, UNALIGN);
			conss->upper = 64;
		}
		else
		{
 			filldata = 0xc0;
 			ASN1_FillBuffer(ws, &filldata, 8, ALIGN);
			conss->consType = UNCONS;
			conss->upper = 9223372036854775807;
		}
 	}
	ASN1_PER_Align_Enc_INTEGER(ws, &temp_index, conss);
	return 0;
}

ASNINT32 ASN1_PER_Align_Dec_ENUMERATED_child(ASN1WorkSpace *ws, ENUMERATED *value, ASNBOOL *extbit, Asn1ConsInfo *conss)
{
	ASNUINT8 readvalue; 
	ASNINT64 tempvalue;
	*extbit = 0;
	if (conss->extflag)
	{
		if (0 > ASN1_ReadBuffer(ws, extbit, 1, UNALIGN)) return ASN1_PER_CHECK_LENGTH_ERROR;
	}

	conss->extflag = 0;
	if (*extbit)
	{
		if (0 > ASN1_ReadBuffer(ws, &readvalue, 7, UNALIGN)) return ASN1_PER_CHECK_LENGTH_ERROR;

		if (readvalue >= 64)
		{
			conss->consType = UNCONS;
			conss->upper = 9223372036854775807;
			ASN1_PER_Align_Dec_INTEGER(ws, &tempvalue, conss);
		}
		else
		{
			tempvalue = readvalue;
		}
	}
	else
	{
		ASN1_PER_UNAlign_Dec_INTEGER(ws, &tempvalue, conss);
	}

	*value = (ENUMERATED)tempvalue;

	return 0;
}

ASNINT32 ASN1_PER_UNAlign_Enc_ENUMERATED_child(ASN1WorkSpace *ws, ENUMERATED value, ASNBOOL extbit, Asn1ConsInfo *conss)
{
 	ASNUINT8 filldata = 0;
	ASNINT64 tempvalue = value;
	if (extbit)
	{
		conss->extflag = 0;
		if (value < 64)
		{
			ASN1_FillBuffer(ws, &extbit,1,UNALIGN);
			conss->upper=64;
		}
		else
		{
 			filldata = 3;
			ASN1_FillBuffer(ws, &filldata, 2, UNALIGN);
			conss->consType = SEMICONS;
			conss->upper = 9223372036854775807;
			conss->lower = 0;
		}
	}
	ASN1_PER_UNAlign_Enc_INTEGER(ws, &tempvalue, conss);
	return 0;
}

ASNINT32 ASN1_PER_UNAlign_Dec_ENUMERATED_child(ASN1WorkSpace *ws, ENUMERATED *value, ASNBOOL *extbit, Asn1ConsInfo *conss)
{
	ASNUINT8 readvalue; 
	ASNINT64 tempvalue;
	*extbit = 0;
	if (conss->extflag)
	{
		if (0 > ASN1_ReadBuffer(ws, extbit, 1, UNALIGN)) return ASN1_PER_CHECK_LENGTH_ERROR;
	}

	conss->extflag = 0;

	if (*extbit)
	{
		if (0 > ASN1_ReadBuffer(ws, &readvalue, 1, UNALIGN)) return ASN1_PER_CHECK_LENGTH_ERROR;

		if (readvalue == 1)
		{
			conss->consType = SEMICONS;
			conss->lower = 0;
			conss->upper = 9223372036854775807;
			ASN1_PER_UNAlign_Dec_INTEGER(ws, (INTEGER *)value, conss);
		}
		else
		{
			if (0 > ASN1_ReadBuffer(ws, &readvalue, 6, UNALIGN)) return ASN1_PER_CHECK_LENGTH_ERROR;
			*value = readvalue;
		}
	}
	else
	{
		ASN1_PER_UNAlign_Dec_INTEGER(ws, &tempvalue, conss);
		*value = (ENUMERATED)tempvalue;
	}

	return 0;
}

ASNINT32 ASN1_PER_Align_Enc_ENUMERATED(ASN1WorkSpace *ws, ENUMERATED index, Asn1ConsInfo *conss)
{
	return ASN1_PER_Align_Enc_ENUMERATED_child(ws, index, conss->enumextbit, conss);
}
ASNINT32 ASN1_PER_UNAlign_Enc_ENUMERATED(ASN1WorkSpace *ws, ENUMERATED index, Asn1ConsInfo *conss)
{
	return ASN1_PER_UNAlign_Enc_ENUMERATED_child(ws, index, conss->enumextbit, conss);
}
ASNINT32 ASN1_PER_Align_Dec_ENUMERATED(ASN1WorkSpace *ws, ENUMERATED *value, Asn1ConsInfo *conss)
{
	return ASN1_PER_Align_Dec_ENUMERATED_child(ws, value, &conss->enumextbit, conss);
}
ASNINT32 ASN1_PER_UNAlign_Dec_ENUMERATED(ASN1WorkSpace *ws, ENUMERATED *value, Asn1ConsInfo *conss)
{
	return ASN1_PER_UNAlign_Dec_ENUMERATED_child(ws, value, &conss->enumextbit, conss);
}


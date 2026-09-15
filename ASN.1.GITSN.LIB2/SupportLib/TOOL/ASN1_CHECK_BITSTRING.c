#include "ASN1_CHECK_BITSTRING.h"
#include "ASN1_CHECK_STRING.h"
#include "ASN1_Length.h"

static int ASN1_CHECK_BITSTRING_SIZE(ASNUINT32 ValueChecked, ASN1ConsCheck *ConsStruct)
{
	int ret = -7;	
	if (0 == ConsStruct->Length[0]) ret = 0; // do not need to check.
	else
	{
		ASNUINT32 low = (ASNUINT32)ConsStruct->StringforRange[0];
		ASNUINT32 high = (ASNUINT32)ConsStruct->StringforRange[1];
		if (ValueChecked < low) ret = (int)high;
		else if (low <= ValueChecked && ValueChecked <= high) ret = 0;
		else ret = -7;
		free(ConsStruct->StringforRange);
	}
	return ret;
}

int ASN1_CHECK_BITSTRING(BITSTRING *ValueChecked, ASNUINT8 *StringDealwith)
{
	ASN1ConsCheck ConsChecked = String_to_CheckStruct(&StringDealwith, 0);
	return ASN1_CHECK_BITSTRING_SIZE(ValueChecked->numbits, &ConsChecked);
}

int ASN1_CXER_Dec_BitString_Process(ASN1WorkSpace * ws, BITSTRING *value, ASNUINT32 lower)
{
	ASNUINT32 i = 0, j = 1, bitzero = 0;
	if (value->numbits < lower)
	{
		value->data = mpool_realloc(ws->Pmemory, value->data, (lower + 7) / 8);
		memset(&(value->data[(value->numbits + 7) / 8]), 0, (lower + 7) / 8 - (value->numbits + 7) / 8);
		bitzero = 8 - (value->numbits % 8);
		if (bitzero !=8)
		{
			for (i = 0; i < bitzero; i++)
			{
				value->data[value->numbits / 8] = value->data[value->numbits / 8] & (255 - j);
				j = j * 2;
			}

		}
		value->numbits = lower;
	}
	return 0;
}



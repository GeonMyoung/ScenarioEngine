#include "ASN1_CHECK_INTEGER.h"
#include "ASN1_Length.h"

#if 0
int ASN1_CHECK_INTEGER(INTEGER *ValueChecked, ASNUINT8 *StringDealwith)
{
	ASNUINT64 IntValueLenth = 0;
	ASNUINT8 i;
	ASN1ConsCheck ConsStruct;
	ASNINT64 low = 0;
	ASNINT64 hight = 0;

	ASNINT32 len0 = 0, loop_max = 0, idx = 0;

	ConsStruct = String_to_CheckStruct(&StringDealwith, 0);	

	if ((len0 = ConsStruct.Length[0]) == 0) return 0;/*do not need to check.*/
	else loop_max = len0 / 2;

	for (i = 0; i < loop_max; i++)
	{
		idx = i * 2;
		low = ConsStruct.StringforRange[idx];
		hight = ConsStruct.StringforRange[idx + 1];

		if (*ValueChecked < low) 
		{
			free(ConsStruct.StringforRange);
			return -18;
		}

		if (*ValueChecked >= low && *ValueChecked <= hight) 
		{
			free(ConsStruct.StringforRange);
			return 0;/*right.*/
		}
	}

	if (i == ConsStruct.Length[0] / 2) 
	{
		free(ConsStruct.StringforRange);
		return -18;/*wrong.*/
	}

	return 0;
}
#else // 2025-12-12 : new version by Jake Lim
int ASN1_CHECK_INTEGER(INTEGER *ValueChecked, ASNUINT8 *StringDealwith)
{
	int ret = -18;	/* init with 'not found' */
	ASN1ConsCheck ConsStruct = String_to_CheckStruct(&StringDealwith, 0);	

	if (0 == ConsStruct.Length[0]) ret = 0;	// no need to check
	else
	{
		ASNINT32 i;
		if (*ValueChecked < ConsStruct.StringforRange[0]) { /* lower then minimum value -> keep 'not found' */ }
		else for (i = 0; ret == -18 && i < ConsStruct.Length[0]; i += 2)
			if (ConsStruct.StringforRange[i] <= *ValueChecked && *ValueChecked <= ConsStruct.StringforRange[i + 1]) ret = 0;
		free(ConsStruct.StringforRange);
	}
	return ret;
}
#endif
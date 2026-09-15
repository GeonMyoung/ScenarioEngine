#include "ASN1_CHECK_ENUMERATED.h"
#include "ASN1_Length.h"

ASN1_CPPLINK int ASN1_CHECK_ENUMERATED(ENUMERATED *ValueChecked, ASNUINT8 *StringDealwith)
{
	int ret = -8;	/* init with not found */
	ASN1ConsCheck ConsChecked = String_to_CheckStruct(&StringDealwith, 0);	

	if (0 == ConsChecked.Length[0]) ret = 0; /* do not need to check.*/
	else
	{
		ASNUINT8 i;
		for (i = 0; ret == -8 && i < ConsChecked.Length[0]; i++)
			if (*ValueChecked == ConsChecked.StringforRange[i]) ret = 0;
		free(ConsChecked.StringforRange);
	}	
	return ret;
}

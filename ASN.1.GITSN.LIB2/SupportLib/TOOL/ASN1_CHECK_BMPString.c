#include "ASN1_CHECK_BMPString.h"
#include "ASN1_Length.h"

int ASN1_CHECK_BMPString(BMPString *ValueChecked, ASNUINT8 *StringDealwith)
{
	ASN1ConsCheck ConsChecked = String_to_CheckStruct(&StringDealwith, 0);
	return ASN1_CHECK_SIZE(ValueChecked->nchar/2, &ConsChecked);
}

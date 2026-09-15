#include "ASN1_CHECK_UniversalString.h"
#include "ASN1_Length.h"

ASN1_CPPLINK int ASN1_CHECK_UniversalString(UniversalString *ValueChecked, ASNUINT8 *StringDealwith)
{
	ASN1ConsCheck ConsChecked = String_to_CheckStruct(&StringDealwith, 0);
	return ASN1_CHECK_SIZE(ValueChecked->nchar/4,&ConsChecked);
}


#include "ASN1_CHECK_OCTETSTRING.h"
#include "ASN1_CHECK_STRING.h"
#include "ASN1_Length.h"

int ASN1_CHECK_OCTETSTRING(OCTETSTRING *ValueChecked, ASNUINT8 *StringDealwith)
{
	ASN1ConsCheck ConsChecked;
	ConsChecked = String_to_CheckStruct(&StringDealwith, 0);
	return ASN1_CHECK_SIZE(ValueChecked->numbits, &ConsChecked);
}

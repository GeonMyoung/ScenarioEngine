#ifndef _CHECK_STRING_H_
#define _CHECK_STRING_H_

#include "OS/ASN1_Sys.h"
#include "TYPE/ASN1_Type.h"

ASN1_CPPLINK int ASN1_CHECK_STRING(ASNSTRING *ValueChecked, ASNUINT8 *ConsChecked, ASNSTRING *DefaultAlphabet, ASNUINT8 bytes1char);
ASN1_CPPLINK int ASN1_CHECK_SIZE(ASNUINT32 ValueChecked, ASN1ConsCheck *StringDealwith);

#endif

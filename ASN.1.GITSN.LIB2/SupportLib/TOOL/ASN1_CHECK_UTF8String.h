#ifndef _ASN1_CHECK_UTF8STRING_H
#define _ASN1_CHECK_UTF8STRING_H

#include "ASN1_CHECK_STRING.h"

#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
ASN1_CPPLINK int ASN1_CHECK_UTF8Str(UTF8Str *ValueChecked, ASNUINT8 *ConsChecked);
#else
ASN1_CPPLINK int ASN1_CHECK_UTF8String(UTF8String *ValueChecked, ASNUINT8 *ConsChecked);
#endif

#endif

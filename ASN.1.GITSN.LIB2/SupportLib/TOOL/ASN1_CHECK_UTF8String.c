#include "ASN1_CHECK_UTF8String.h"

#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
int ASN1_CHECK_UTF8Str(UTF8Str *ValueChecked, ASNUINT8 *ConsChecked)
#else
int ASN1_CHECK_UTF8String(UTF8String *ValueChecked, ASNUINT8 *ConsChecked)
#endif
{
	return ASN1_CHECK_STRING((ASNSTRING *)ValueChecked,ConsChecked,NULL,1);
	return 0;
}

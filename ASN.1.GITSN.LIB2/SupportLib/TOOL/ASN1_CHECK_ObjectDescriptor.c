#include "ASN1_CHECK_ObjectDescriptor.h"


ASN1_CPPLINK int ASN1_CHECK_ObjectDescriptor(ObjectDescriptor *ValueChecked, ASNUINT8 *ConsChecked)
{
	return ASN1_CHECK_STRING((ASNSTRING *)ValueChecked,ConsChecked,NULL,1);
	return 0;
}

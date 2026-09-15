#include "ASN1_CHECK_IA5String.h"


ASN1_CPPLINK int ASN1_CHECK_IA5String(IA5String *ValueChecked, ASNUINT8 *ConsChecked)
{
	ASNSTRING DefaultAlphabet;
	ASNUINT8 DefaultString[129];
	ASNUINT8 i = 0;

	for (; i<128; i++) 
	{
		DefaultString[i] = i;
	}

	DefaultString[128] = 0;

	DefaultAlphabet.nchar = 128;
	DefaultAlphabet.asnstring = DefaultString;
	
	return ASN1_CHECK_STRING((ASNSTRING *)ValueChecked,ConsChecked,&DefaultAlphabet,1);
}

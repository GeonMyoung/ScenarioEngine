#include "ASN1_CHECK_NumericString.h"


ASN1_CPPLINK int ASN1_CHECK_NumericString(NumericString *ValueChecked, ASNUINT8 *ConsChecked)
{
	ASNSTRING DefaultAlphabet;
	ASNUINT8 DefaultString[] = " 0123456789";

	DefaultAlphabet.nchar = 11;
	DefaultAlphabet.asnstring = DefaultString;
	
	return ASN1_CHECK_STRING((ASNSTRING *)ValueChecked,ConsChecked,&DefaultAlphabet,1);
}

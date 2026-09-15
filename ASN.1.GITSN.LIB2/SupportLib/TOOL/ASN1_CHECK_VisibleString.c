#include "ASN1_CHECK_VisibleString.h"


ASN1_CPPLINK int ASN1_CHECK_VisibleString(VisibleString *ValueChecked, ASNUINT8 *ConsChecked)
{
	ASNSTRING DefaultAlphabet;
	ASNUINT8 DefaultString[] = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

	DefaultAlphabet.nchar = 95;
	DefaultAlphabet.asnstring = DefaultString;
	
	return ASN1_CHECK_STRING((ASNSTRING *)ValueChecked,ConsChecked,&DefaultAlphabet,1);
}
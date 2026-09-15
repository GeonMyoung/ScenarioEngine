#include "ASN1_CHECK_TeletexString.h"


ASN1_CPPLINK int ASN1_CHECK_TeletexString(TeletexString *ValueChecked, ASNUINT8 *ConsChecked)
{
	ASNSTRING DefaultAlphabet;
	ASNUINT8 DefaultString[] = " !\"%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]_abcdefghijklmnopqrstuvwxyz";

	DefaultAlphabet.nchar = 86;
	DefaultAlphabet.asnstring = DefaultString;
	
	return ASN1_CHECK_STRING((ASNSTRING *)ValueChecked,ConsChecked,&DefaultAlphabet,1);
}

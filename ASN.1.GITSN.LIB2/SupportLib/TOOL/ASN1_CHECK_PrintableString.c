#include "ASN1_CHECK_PrintableString.h"


ASN1_CPPLINK int ASN1_CHECK_PrintableString(PrintableString *ValueChecked, ASNUINT8 *ConsChecked)
{
	ASNSTRING DefaultAlphabet;
	ASNUINT8 DefaultString[] = " '()+,-./0123456789:=?ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	DefaultAlphabet.nchar = 74;
	DefaultAlphabet.asnstring = DefaultString;
	
	return ASN1_CHECK_STRING((ASNSTRING *)ValueChecked,ConsChecked,&DefaultAlphabet,1);
}

#include "ASN1_CHECK_GraphicString.h"


ASN1_CPPLINK int ASN1_CHECK_GraphicString(GraphicString *ValueChecked, ASNUINT8 *ConsChecked)
{
	ASNSTRING DefaultAlphabet;
	ASNUINT8 DefaultString[257];
	ASNUINT16 i = 0;

	for (;i<255;i++)
	{
		DefaultString[i] = (ASNUINT8)i;
	}

	DefaultString[i] = 0;

	DefaultAlphabet.nchar = 256;
 	DefaultAlphabet.asnstring = NULL;
	
	return ASN1_CHECK_STRING((ASNSTRING *)ValueChecked,ConsChecked,NULL,1);

	return 0;

}

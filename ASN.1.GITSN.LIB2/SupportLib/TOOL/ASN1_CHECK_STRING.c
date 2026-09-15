#include "ASN1_CHECK_STRING.h"
#include "ASN1_Length.h"
#include "ASN1_CHECK_INTEGER.h"
#include <stdlib.h>

static int numeric (const int *p1, const int *p2) 
{ 
	return(*p1 - *p2); 
}

#if 0
static int binsearch(const ASNUINT8 CharChecked, const ASNUINT8 *SourceString, ASNUINT32 SourceStringLength, ASNUINT8 bytes1char)
{
	ASNINT32 low = 0;
	ASNINT32 hight = SourceStringLength - 1;
	ASNINT32 mid = 0;

	while (low <= hight) 
	{
		mid = (low + hight) / 2;

		if (CharChecked < SourceString[mid]) 
		{
			hight = mid - 1;
		}
		else if (CharChecked > SourceString[mid]) 
		{
			low = mid + 1;
		}
		else
		{
			return 0;
		}
	}
	return -1;/*not found.*/
}

static int ASN1_Check_if_Appeared(const ASNUINT8 CharChecked, const ASNUINT8 *SourceString, ASNUINT32 SourceStringLength, ASNUINT8 bytes1char)
{
	if (NULL == SourceString) { return -2; /*no SourceString.*/ }
	return binsearch(CharChecked, SourceString, SourceStringLength, bytes1char) == 0 ? 1 : 0;
}

int ASN1_CHECK_STRING(ASNSTRING *ValueChecked, ASNUINT8 *StringDealwith, ASNSTRING *DefaultAlphabet, ASNUINT8 bytes1char)
{
	ASNUINT32 AlphabetValueLenth = 0;
	ASNUINT64 i;
	ASNUINT8 *TempString;
	ASNUINT8 *AlphabetValue;
	ASNINT8 result = 0;	
	ASN1ConsCheck ConsChecked = String_to_CheckStruct(&StringDealwith, DefaultAlphabet);

	/*size constraint checked.*/	
	if ((result = ASN1_CHECK_SIZE(ValueChecked->nchar, &ConsChecked)) != 0) return result;

	if (0 == ConsChecked.Length[1]) return 0;/*do not need to check.*/
	
	/*from constraint checked.*/
	TempString = ValueChecked->asnstring;
	AlphabetValue = ConsChecked.StringforAlphabet;
	AlphabetValueLenth = ConsChecked.Length[1];

	for (i = 0; i < ValueChecked->nchar; i++) /*nchar is invalid?*/
	{
		result = ASN1_Check_if_Appeared(TempString[i], AlphabetValue, AlphabetValueLenth, bytes1char);
		if (!result) return -6;/*a character is not found.*/
	}

	return result;
}
#else
static int binsearch(const ASNUINT8 CharChecked, const ASNUINT8 *SourceString, ASNUINT32 SourceStringLength, ASNUINT8 bytes1char)
{
	ASNINT32 high = SourceStringLength - 1, low = 0, mid;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if		(CharChecked < SourceString[mid]) high = mid - 1;
		else if (CharChecked > SourceString[mid]) low  = mid + 1;
		else return 1;
	}
	return 0;	/* not found. */
}

int ASN1_CHECK_STRING(ASNSTRING *ValueChecked, ASNUINT8 *StringDealwith, ASNSTRING *DefaultAlphabet, ASNUINT8 bytes1char)
{
	int ret = -1;
	ASN1ConsCheck ConsChecked = String_to_CheckStruct(&StringDealwith, DefaultAlphabet);

	/*size constraint checked.*/	
	if ((ret = ASN1_CHECK_SIZE(ValueChecked->nchar, &ConsChecked)) != 0) { /* size check failed -> return with result */ }
	/* alphabet check */
	else if (0 == ConsChecked.Length[1]) { ret = 0; /* do not need to check. */ }
	else
	{	/* from constraint checked. */
		ASNUINT64 i;
		ASNUINT8 *TempString = ValueChecked->asnstring;
		ASNUINT8 *AlphabetValue = ConsChecked.StringforAlphabet;
		ASNUINT32 AlphabetValueLenth = ConsChecked.Length[1];

		if (AlphabetValue == NULL) ret = -2; /* no SourceString */
		else for (i = 0; i < ValueChecked->nchar; i++) /* nchar is invalid? */
			if (binsearch(TempString[i], AlphabetValue, AlphabetValueLenth, bytes1char) == 0) { ret = -6; break; }
	}
	return ret;
}
#endif

int ASN1_CHECK_SIZE(ASNUINT32 ValueChecked, ASN1ConsCheck *ConsStruct)
{
	int ret = -7;
	if (0 == ConsStruct->Length[0]) ret = 0; /* do not need to check. */
	else
	{
		ASNINT32 i;
		ASNUINT32 high = 0, low = (ASNUINT32)ConsStruct->StringforRange[0];
		if (ValueChecked < low) { }
		else for (i = 0; ret == -7 && i < ConsStruct->Length[0]; i += 2)
		{
			low  = (ASNUINT32)ConsStruct->StringforRange[i];
			high = (ASNUINT32)ConsStruct->StringforRange[i + 1];		
			if (low <= ValueChecked && ValueChecked <= high) return 0; /* right. */
		}
		free(ConsStruct->StringforRange);
	}	
	return ret;
}



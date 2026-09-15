#include "ASN1_CHECK_GeneralizedTime.h"
#include "ASN1_Length.h"
#include "ASN1_Tool_Time.h"

ASN1_CPPLINK static int _check_4bityear(ASNUINT8 **GTemp);

ASN1_CPPLINK int ASN1_CHECK_GeneralizedTime(GeneralizedTime *ValueChecked, ASNUINT8 *StringDealwith)
{
	ASNINT8 ret = 0;
	ASNUINT8 *temp_GenTime;
	ASNUINT8 *GenTime = ValueChecked->asnstring;
	ASNUINT8 i = 0;
	ASNUINT8 _Hour = 0;
	ASNUINT8 _Minute = 0;
	ASNUINT32 TempLen = 0;

	temp_GenTime = GenTime = malloc(ValueChecked->nchar+1);
	memset(GenTime,0x00,ValueChecked->nchar+1);
	memcpy(GenTime,ValueChecked->asnstring,ValueChecked->nchar);
	
/*	GenTime[ValueChecked->nchar] = 0;*/

	if (GenTime == NULL) 
	{
		free(temp_GenTime);
		return -9;
	}

	ret = ValueChecked->nchar<14;

	if (ret) 
	{
		free(temp_GenTime);
		return -10;
	}

	ret = _check_4bityear(&GenTime);

	if (ret < 0) 
	{
		free(temp_GenTime);
		return -11;
	}

	ret = _check_month_and_day(GenTime, ret);
	
	if (ret) 
	{
		free(temp_GenTime);
		return -12;
	}

	GenTime += 4;
	ret = _check_hmc(GenTime);
	
	if (ret) 
	{
		free(temp_GenTime);
		return -13;
	}

	GenTime += 4;
	
	if (!_check_sec(GenTime)) 
	{
		free(temp_GenTime);
		return -14;
	}

	GenTime += 2;

	switch(GenTime[0]) 
	{
	case '.':

		TempLen = (ASNUINT32)strlen(GenTime + 1);

		for (i=1; i<TempLen; i++)
		{
			if ('Z' == GenTime[i]) 
			{
				if (i < ValueChecked->nchar-11) 
				{
					free(temp_GenTime);
					return -15;
				}
			}
			
			if ('-' == GenTime[i]) 
			{
				if (4 != strlen(GenTime + i + 1)) 
				{
					free(temp_GenTime);
					return -15;
				}
				
				GenTime += i + 1;

				
				ret= _check_hmc(GenTime);
				free(temp_GenTime);
				return ret;
			}
			if ('+' == GenTime[i]) 
			{
				if (4 != strlen(GenTime + i + 1)) 
				{
					free(temp_GenTime);
					return -16;
				}
				
				GenTime += i + 1;
				
				
				ret= _check_hmc(GenTime);
				free(temp_GenTime);
				return ret;
			}

			if (GenTime[i]<'0' || GenTime[i]>'9') 
			{
				free(temp_GenTime);
				return -16;
			}
		}

		break;

	case '-':
	case '+':

		TempLen = (ASNUINT32)strlen(GenTime + 1);

		if (4 != TempLen) 
		{
			free(temp_GenTime);
			return -16;
		}

		GenTime += 1;
		
		
		ret= _check_hmc(GenTime);
		free(temp_GenTime);
		return ret;
	case 'Z':
	case 0:

		free(temp_GenTime);
		return 0;

	default:

		free(temp_GenTime);
		return -17;
	}

	free(temp_GenTime);
	return 0;
}

ASN1_CPPLINK static int _check_4bityear(ASNUINT8 **GTemp)
{
	ASNUINT16 year = 0;
	ASNUINT8 i = 0;
	ASNINT8 ret = 0;
	ASNUINT8 *GTime = *GTemp;

	if ('-' == GTime[i]) 
	{
		return -1;
	}

	for (; i<4; i++)
	{
		if (GTime[i]>='0' && GTime[i]<='9') 
		{
			year *= 10;
			year += (GTime[i] - 48);
		}
		else
		{
			return -1;
		}				
	}

	*GTemp += 4;
	
	if (!(year % 400) 
		|| (!(year % 4) && (year % 100)))  
	{
		return 1;		
	}
	else 
	{
		return 0;
	}

	return 0;
}



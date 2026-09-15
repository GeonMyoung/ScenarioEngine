#include "ASN1_CHECK_UTCTime.h"
#include "ASN1_Length.h"
#include "ASN1_Tool_Time.h"

ASN1_CPPLINK static int _check_2bityear(ASNUINT8 **UTemp);

ASN1_CPPLINK int ASN1_CHECK_UTCTime(UTCTime *ValueChecked, ASNUINT8 *StringDealwith)
{
	ASNINT8 ret = 0;
	ASNUINT8 *UTCTime = ValueChecked->asnstring;
	ASNUINT32 TempLen = 0;
	ASNUINT8 *temp_UTCTime;

	temp_UTCTime = UTCTime = malloc(ValueChecked->nchar+1);
	memset(UTCTime,0x00,ValueChecked->nchar+1);
	memcpy(UTCTime,ValueChecked->asnstring,ValueChecked->nchar);
/*	UTCTime[ValueChecked->nchar] = 0;*/
	if (UTCTime == NULL) 
	{
		free(temp_UTCTime);
		return -19;
	}
	
	ret = ValueChecked->nchar<11;
	
	if (ret) 
	{
		free(temp_UTCTime);
		return -20;
	}
	
	ret = _check_2bityear(&UTCTime);
	
	if (ret < 0) 
	{
		free(temp_UTCTime);
		return -21;
	}
	
	ret = _check_month_and_day(UTCTime, ret);	
	
	if (ret) 
	{
		free(temp_UTCTime);
		return -22;
	}

	UTCTime += 4;
	ret =  _check_hmc(UTCTime);
	
	if (ret < 0) 
	{
		free(temp_UTCTime);
		return -23;
	}
	
	UTCTime += 4;

	if (UTCTime[0]>='0' && UTCTime[0]<='9') 
	{
		if (!_check_sec(UTCTime)) 
		{
			free(temp_UTCTime);
			return -24;
		}

		UTCTime += 2;
	}

	switch(UTCTime[0]) 
	{		
	case '-':
	case '+':
		
		TempLen = (ASNUINT32)strlen(UTCTime + 1);
		
		if (4 != TempLen) 
		{
			free(temp_UTCTime);
			return -25;
		}
		
		UTCTime += 1;
		ret = _check_hmc(UTCTime);
		free(temp_UTCTime);
		return ret;
		
	case 'Z':
	case 0:
	
		free(temp_UTCTime);
		return 0;
		
	default:
	
		free(temp_UTCTime);
		return -26;
	}

	free(temp_UTCTime);
	return 0;
}

ASN1_CPPLINK static int _check_2bityear(ASNUINT8 **UTemp)
{
	ASNUINT8 *UTCTime = *UTemp;
	ASNUINT8 i = 0;

	for (; i<2; i++)
	{
		if (UTCTime[i]<'0' || UTCTime[0]>'9') 
		{
			return -1;
		}
	}

	*UTemp += 2;
	return 0;
}

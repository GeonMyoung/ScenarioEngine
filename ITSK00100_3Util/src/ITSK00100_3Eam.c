#include "ITSK00100_3Eam.h"

/********************************************************
*ObjectID_00100                                         *
********************************************************/
int ASN1_CHECK_ObjectID_00100(ObjectID_00100 *value)
{
	unsigned char checkinfo_ObjectID_00100[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(value, checkinfo_ObjectID_00100)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_ObjectID_00100(ASN1WorkSpace *workspace, ObjectID_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_ObjectID_00100(ASN1WorkSpace *workspace, ObjectID_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_ObjectID_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_ObjectID_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_ObjectID_00100(ASN1WorkSpace *workspace, ObjectID_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_ObjectID_00100(ASN1WorkSpace *workspace, ObjectID_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_ObjectID_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_ObjectID_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*DYear_00100                                            *
********************************************************/
int ASN1_CHECK_DYear_00100(DYear_00100 *value)
{
	unsigned char checkinfo_DYear_00100[] = {
		0x02,0x00,0x82,0x0F,0xFF,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(value, checkinfo_DYear_00100)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_DYear_00100(ASN1WorkSpace *workspace, DYear_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_DYear_00100(ASN1WorkSpace *workspace, DYear_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_DYear_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_DYear_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_DYear_00100(ASN1WorkSpace *workspace, DYear_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_DYear_00100(ASN1WorkSpace *workspace, DYear_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_DYear_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_DYear_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*DDay_00100                                             *
********************************************************/
int ASN1_CHECK_DDay_00100(DDay_00100 *value)
{
	unsigned char checkinfo_DDay_00100[] = {
		0x02,0x00,0x1F,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(value, checkinfo_DDay_00100)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_DDay_00100(ASN1WorkSpace *workspace, DDay_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_DDay_00100(ASN1WorkSpace *workspace, DDay_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_DDay_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_DDay_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_DDay_00100(ASN1WorkSpace *workspace, DDay_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_DDay_00100(ASN1WorkSpace *workspace, DDay_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_DDay_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_DDay_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*DHour_00100                                            *
********************************************************/
int ASN1_CHECK_DHour_00100(DHour_00100 *value)
{
	unsigned char checkinfo_DHour_00100[] = {
		0x02,0x00,0x1F,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(value, checkinfo_DHour_00100)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_DHour_00100(ASN1WorkSpace *workspace, DHour_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_DHour_00100(ASN1WorkSpace *workspace, DHour_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_DHour_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_DHour_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_DHour_00100(ASN1WorkSpace *workspace, DHour_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_DHour_00100(ASN1WorkSpace *workspace, DHour_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_DHour_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_DHour_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*DMinute_00100                                          *
********************************************************/
int ASN1_CHECK_DMinute_00100(DMinute_00100 *value)
{
	unsigned char checkinfo_DMinute_00100[] = {
		0x02,0x00,0x3C,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(value, checkinfo_DMinute_00100)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_DMinute_00100(ASN1WorkSpace *workspace, DMinute_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_DMinute_00100(ASN1WorkSpace *workspace, DMinute_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_DMinute_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_DMinute_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_DMinute_00100(ASN1WorkSpace *workspace, DMinute_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_DMinute_00100(ASN1WorkSpace *workspace, DMinute_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_DMinute_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_DMinute_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*DMonth_00100                                           *
********************************************************/
int ASN1_CHECK_DMonth_00100(DMonth_00100 *value)
{
	unsigned char checkinfo_DMonth_00100[] = {
		0x02,0x00,0x0C,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(value, checkinfo_DMonth_00100)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_DMonth_00100(ASN1WorkSpace *workspace, DMonth_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_DMonth_00100(ASN1WorkSpace *workspace, DMonth_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_DMonth_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_DMonth_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_DMonth_00100(ASN1WorkSpace *workspace, DMonth_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_DMonth_00100(ASN1WorkSpace *workspace, DMonth_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_DMonth_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_DMonth_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*DOffset_00100                                          *
********************************************************/
int ASN1_CHECK_DOffset_00100(DOffset_00100 *value)
{
	unsigned char checkinfo_DOffset_00100[] = {
		0x02,0x82,0xFC,0xB8,0x82,0x03,0x48,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(value, checkinfo_DOffset_00100)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_DOffset_00100(ASN1WorkSpace *workspace, DOffset_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_DOffset_00100(ASN1WorkSpace *workspace, DOffset_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_DOffset_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_DOffset_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_DOffset_00100(ASN1WorkSpace *workspace, DOffset_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_DOffset_00100(ASN1WorkSpace *workspace, DOffset_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_DOffset_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_DOffset_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*DSecond_00100                                          *
********************************************************/
int ASN1_CHECK_DSecond_00100(DSecond_00100 *value)
{
	unsigned char checkinfo_DSecond_00100[] = {
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(value, checkinfo_DSecond_00100)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_DSecond_00100(ASN1WorkSpace *workspace, DSecond_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_DSecond_00100(ASN1WorkSpace *workspace, DSecond_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_DSecond_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_DSecond_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_DSecond_00100(ASN1WorkSpace *workspace, DSecond_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_DSecond_00100(ASN1WorkSpace *workspace, DSecond_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_DSecond_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_DSecond_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*DDateTime_00100                                        *
********************************************************/
int ASN1_GET_DDateTime_00100_year(ASN1WorkSpace *workspace, DDateTime_00100 *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_DDateTime_00100_year == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->year, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_DDateTime_00100_month(ASN1WorkSpace *workspace, DDateTime_00100 *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_DDateTime_00100_month == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->month, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_DDateTime_00100_day(ASN1WorkSpace *workspace, DDateTime_00100 *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_DDateTime_00100_day == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->day, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_DDateTime_00100_hour(ASN1WorkSpace *workspace, DDateTime_00100 *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_DDateTime_00100_hour == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->hour, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_DDateTime_00100_minute(ASN1WorkSpace *workspace, DDateTime_00100 *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_DDateTime_00100_minute == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->minute, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_DDateTime_00100_second(ASN1WorkSpace *workspace, DDateTime_00100 *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_DDateTime_00100_second == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->second, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_DDateTime_00100_offset(ASN1WorkSpace *workspace, DDateTime_00100 *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_DDateTime_00100_offset == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->offset, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_CHECK_DDateTime_00100(DDateTime_00100 *value)
{
	int ret = 0;

	unsigned char checkinfo_year[] = {
		0x02,0x00,0x82,0x0F,0xFF,0x00
	};
	unsigned char checkinfo_month[] = {
		0x02,0x00,0x0C,0x00
	};
	unsigned char checkinfo_day[] = {
		0x02,0x00,0x1F,0x00
	};
	unsigned char checkinfo_hour[] = {
		0x02,0x00,0x1F,0x00
	};
	unsigned char checkinfo_minute[] = {
		0x02,0x00,0x3C,0x00
	};
	unsigned char checkinfo_second[] = {
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_offset[] = {
		0x02,0x82,0xFC,0xB8,0x82,0x03,0x48,0x00
	};

	if (value == NULL) return -1;
	if (value->DEF_DDateTime_00100_year == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->year), checkinfo_year)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_DDateTime_00100_month == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->month), checkinfo_month)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_DDateTime_00100_day == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->day), checkinfo_day)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_DDateTime_00100_hour == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->hour), checkinfo_hour)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_DDateTime_00100_minute == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->minute), checkinfo_minute)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_DDateTime_00100_second == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->second), checkinfo_second)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_DDateTime_00100_offset == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->offset), checkinfo_offset)) < 0) return ret;
	} /* OPTIONAL end */
	return ret;
}
extern int ASN1_BER_Data_Enc_DYear_00100(ASN1WorkSpace *workspace, DYear_00100 *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_DMonth_00100(ASN1WorkSpace *workspace, DMonth_00100 *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_DDay_00100(ASN1WorkSpace *workspace, DDay_00100 *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_DHour_00100(ASN1WorkSpace *workspace, DHour_00100 *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_DMinute_00100(ASN1WorkSpace *workspace, DMinute_00100 *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_DSecond_00100(ASN1WorkSpace *workspace, DSecond_00100 *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_DOffset_00100(ASN1WorkSpace *workspace, DOffset_00100 *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_DDateTime_00100(ASN1WorkSpace *workspace, DDateTime_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
	}
	if (value->DEF_DDateTime_00100_year == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_DYear_00100(workspace, &(value->year), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_DDateTime_00100_month == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_DMonth_00100(workspace, &(value->month), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_DDateTime_00100_day == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|2)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_DDay_00100(workspace, &(value->day), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_DDateTime_00100_hour == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|3)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_DHour_00100(workspace, &(value->hour), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_DDateTime_00100_minute == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|4)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_DMinute_00100(workspace, &(value->minute), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_DDateTime_00100_second == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|5)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_DSecond_00100(workspace, &(value->second), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_DDateTime_00100_offset == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|6)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_DOffset_00100(workspace, &(value->offset), ASN1IMPL)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_DDateTime_00100(DDateTime_00100 *value);
extern int ASN1_BER_Data_Enc_DDateTime_00100(ASN1WorkSpace *workspace, DDateTime_00100 *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_DDateTime_00100(ASN1WorkSpace *workspace, DDateTime_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_DDateTime_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_DDateTime_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_DYear_00100(ASN1WorkSpace *workspace, DYear_00100 *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_DMonth_00100(ASN1WorkSpace *workspace, DMonth_00100 *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_DDay_00100(ASN1WorkSpace *workspace, DDay_00100 *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_DHour_00100(ASN1WorkSpace *workspace, DHour_00100 *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_DMinute_00100(ASN1WorkSpace *workspace, DMinute_00100 *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_DSecond_00100(ASN1WorkSpace *workspace, DSecond_00100 *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_DOffset_00100(ASN1WorkSpace *workspace, DOffset_00100 *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_DDateTime_00100(ASN1WorkSpace *workspace, DDateTime_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	ASNUINT8 *_cpointer;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace,&_cpointer);
	if ((ret = ASN1_BER_GET_Tag(workspace,&tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT|ITS_ASN_PRIM|0))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_DYear_00100(workspace, &value->year, len, ASN1IMPL)) < 0) return ret;

		value->DEF_DDateTime_00100_year = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace,&tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT|ITS_ASN_PRIM|1))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_DMonth_00100(workspace, &value->month, len, ASN1IMPL)) < 0) return ret;

		value->DEF_DDateTime_00100_month = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace,&tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT|ITS_ASN_PRIM|2))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|2)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_DDay_00100(workspace, &value->day, len, ASN1IMPL)) < 0) return ret;

		value->DEF_DDateTime_00100_day = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace,&tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT|ITS_ASN_PRIM|3))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|3)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_DHour_00100(workspace, &value->hour, len, ASN1IMPL)) < 0) return ret;

		value->DEF_DDateTime_00100_hour = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace,&tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT|ITS_ASN_PRIM|4))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|4)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_DMinute_00100(workspace, &value->minute, len, ASN1IMPL)) < 0) return ret;

		value->DEF_DDateTime_00100_minute = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace,&tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT|ITS_ASN_PRIM|5))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|5)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_DSecond_00100(workspace, &value->second, len, ASN1IMPL)) < 0) return ret;

		value->DEF_DDateTime_00100_second = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace,&tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT|ITS_ASN_PRIM|6))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|6)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_DOffset_00100(workspace, &value->offset, len, ASN1IMPL)) < 0) return ret;

		value->DEF_DDateTime_00100_offset = 1;
	}
	ASN1_Dec_Seq_EXT_UNKnow(workspace,_cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_DDateTime_00100(DDateTime_00100 *value);
extern int ASN1_BER_Data_Dec_DDateTime_00100(ASN1WorkSpace *workspace, DDateTime_00100 *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_DDateTime_00100(ASN1WorkSpace *workspace, DDateTime_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_DDateTime_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_DDateTime_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*Longitude_00100                                        *
********************************************************/
int ASN1_CHECK_Longitude_00100(Longitude_00100 *value)
{
	unsigned char checkinfo_Longitude_00100[] = {
		0x02,0x84,0x94,0xB6,0x2E,0x01,0x84,0x6B,0x49,0xD2,0x01,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(value, checkinfo_Longitude_00100)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_Longitude_00100(ASN1WorkSpace *workspace, Longitude_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_Longitude_00100(ASN1WorkSpace *workspace, Longitude_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_Longitude_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Longitude_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_Longitude_00100(ASN1WorkSpace *workspace, Longitude_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_Longitude_00100(ASN1WorkSpace *workspace, Longitude_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Longitude_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_Longitude_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*Latitude_00100                                         *
********************************************************/
int ASN1_CHECK_Latitude_00100(Latitude_00100 *value)
{
	unsigned char checkinfo_Latitude_00100[] = {
		0x02,0x84,0xCA,0x5B,0x17,0x00,0x84,0x35,0xA4,0xE9,0x01,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(value, checkinfo_Latitude_00100)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_Latitude_00100(ASN1WorkSpace *workspace, Latitude_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_Latitude_00100(ASN1WorkSpace *workspace, Latitude_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_Latitude_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Latitude_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_Latitude_00100(ASN1WorkSpace *workspace, Latitude_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_Latitude_00100(ASN1WorkSpace *workspace, Latitude_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Latitude_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_Latitude_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*Elevation_00100                                        *
********************************************************/
int ASN1_CHECK_Elevation_00100(Elevation_00100 *value)
{
	unsigned char checkinfo_Elevation_00100[] = {
		0x02,0x82,0xF0,0x00,0x83,0x00,0xEF,0xFF,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(value, checkinfo_Elevation_00100)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_Elevation_00100(ASN1WorkSpace *workspace, Elevation_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_Elevation_00100(ASN1WorkSpace *workspace, Elevation_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_Elevation_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Elevation_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_Elevation_00100(ASN1WorkSpace *workspace, Elevation_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_Elevation_00100(ASN1WorkSpace *workspace, Elevation_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Elevation_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_Elevation_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*TransmissionAndSpeed_00100                             *
********************************************************/
int ASN1_GET_TransmissionAndSpeed_00100_transmisson(ASN1WorkSpace *workspace, TransmissionAndSpeed_00100 *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->transmisson, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_TransmissionAndSpeed_00100_speed(ASN1WorkSpace *workspace, TransmissionAndSpeed_00100 *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->speed, user_value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_TransmissionAndSpeed_00100(TransmissionAndSpeed_00100 *value)
{
	int ret = 0;

	unsigned char checkinfo_transmisson[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_speed[] = {
		0x02,0x00,0x82,0x1F,0xFF,0x00
	};

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->transmisson), checkinfo_transmisson)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->speed), checkinfo_speed)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Enc_TransmissionState_00100(ASN1WorkSpace *workspace, TransmissionState_00100 *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_Velocity_00100(ASN1WorkSpace *workspace, Velocity_00100 *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_TransmissionAndSpeed_00100(ASN1WorkSpace *workspace, TransmissionAndSpeed_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_TransmissionState_00100(workspace, &(value->transmisson), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Velocity_00100(workspace, &(value->speed), ASN1IMPL)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_TransmissionAndSpeed_00100(TransmissionAndSpeed_00100 *value);
extern int ASN1_BER_Data_Enc_TransmissionAndSpeed_00100(ASN1WorkSpace *workspace, TransmissionAndSpeed_00100 *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_TransmissionAndSpeed_00100(ASN1WorkSpace *workspace, TransmissionAndSpeed_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_TransmissionAndSpeed_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_TransmissionAndSpeed_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_TransmissionState_00100(ASN1WorkSpace *workspace, TransmissionState_00100 *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_Velocity_00100(ASN1WorkSpace *workspace, Velocity_00100 *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_TransmissionAndSpeed_00100(ASN1WorkSpace *workspace, TransmissionAndSpeed_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8 *_cpointer;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace,&_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_TransmissionState_00100(workspace, &value->transmisson, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Velocity_00100(workspace, &value->speed, len, ASN1IMPL)) < 0) return ret;

	ASN1_Dec_Seq_EXT_UNKnow(workspace,_cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_TransmissionAndSpeed_00100(TransmissionAndSpeed_00100 *value);
extern int ASN1_BER_Data_Dec_TransmissionAndSpeed_00100(ASN1WorkSpace *workspace, TransmissionAndSpeed_00100 *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_TransmissionAndSpeed_00100(ASN1WorkSpace *workspace, TransmissionAndSpeed_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_TransmissionAndSpeed_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_TransmissionAndSpeed_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*TransmissionState_00100                                *
********************************************************/
int ASN1_CHECK_TransmissionState_00100(TransmissionState_00100 *value)
{
	unsigned char checkinfo_TransmissionState_00100[] = {
		0x08,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)value, checkinfo_TransmissionState_00100)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_TransmissionState_00100(ASN1WorkSpace *workspace, TransmissionState_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_TransmissionState_00100(ASN1WorkSpace *workspace, TransmissionState_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_TransmissionState_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_TransmissionState_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_TransmissionState_00100(ASN1WorkSpace *workspace, TransmissionState_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_TransmissionState_00100(ASN1WorkSpace *workspace, TransmissionState_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_TransmissionState_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_TransmissionState_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*Velocity_00100                                         *
********************************************************/
int ASN1_CHECK_Velocity_00100(Velocity_00100 *value)
{
	unsigned char checkinfo_Velocity_00100[] = {
		0x02,0x00,0x82,0x1F,0xFF,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(value, checkinfo_Velocity_00100)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_Velocity_00100(ASN1WorkSpace *workspace, Velocity_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_Velocity_00100(ASN1WorkSpace *workspace, Velocity_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_Velocity_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Velocity_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_Velocity_00100(ASN1WorkSpace *workspace, Velocity_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_Velocity_00100(ASN1WorkSpace *workspace, Velocity_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Velocity_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_Velocity_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*Heading_00100                                          *
********************************************************/
int ASN1_CHECK_Heading_00100(Heading_00100 *value)
{
	unsigned char checkinfo_Heading_00100[] = {
		0x02,0x00,0x82,0x70,0x80,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(value, checkinfo_Heading_00100)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_Heading_00100(ASN1WorkSpace *workspace, Heading_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_Heading_00100(ASN1WorkSpace *workspace, Heading_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_Heading_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Heading_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_Heading_00100(ASN1WorkSpace *workspace, Heading_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_Heading_00100(ASN1WorkSpace *workspace, Heading_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Heading_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_Heading_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*PositionalAccuracy_00100                               *
********************************************************/
int ASN1_GET_PositionalAccuracy_00100_semiMajor(ASN1WorkSpace *workspace, PositionalAccuracy_00100 *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->semiMajor, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_PositionalAccuracy_00100_semiMinor(ASN1WorkSpace *workspace, PositionalAccuracy_00100 *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->semiMinor, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_PositionalAccuracy_00100_orientation(ASN1WorkSpace *workspace, PositionalAccuracy_00100 *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->orientation, user_value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_PositionalAccuracy_00100(PositionalAccuracy_00100 *value)
{
	int ret = 0;

	unsigned char checkinfo_semiMajor[] = {
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_semiMinor[] = {
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_orientation[] = {
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(&(value->semiMajor), checkinfo_semiMajor)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->semiMinor), checkinfo_semiMinor)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->orientation), checkinfo_orientation)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Enc_SemiMajorAxisAccuracy_00100(ASN1WorkSpace *workspace, SemiMajorAxisAccuracy_00100 *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_SemiMinorAxisAccuracy_00100(ASN1WorkSpace *workspace, SemiMinorAxisAccuracy_00100 *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_SemiMajorAxisOrientation_00100(ASN1WorkSpace *workspace, SemiMajorAxisOrientation_00100 *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_PositionalAccuracy_00100(ASN1WorkSpace *workspace, PositionalAccuracy_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SemiMajorAxisAccuracy_00100(workspace, &(value->semiMajor), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SemiMinorAxisAccuracy_00100(workspace, &(value->semiMinor), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|2)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SemiMajorAxisOrientation_00100(workspace, &(value->orientation), ASN1IMPL)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_PositionalAccuracy_00100(PositionalAccuracy_00100 *value);
extern int ASN1_BER_Data_Enc_PositionalAccuracy_00100(ASN1WorkSpace *workspace, PositionalAccuracy_00100 *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_PositionalAccuracy_00100(ASN1WorkSpace *workspace, PositionalAccuracy_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_PositionalAccuracy_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_PositionalAccuracy_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_SemiMajorAxisAccuracy_00100(ASN1WorkSpace *workspace, SemiMajorAxisAccuracy_00100 *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_SemiMinorAxisAccuracy_00100(ASN1WorkSpace *workspace, SemiMinorAxisAccuracy_00100 *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_SemiMajorAxisOrientation_00100(ASN1WorkSpace *workspace, SemiMajorAxisOrientation_00100 *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_PositionalAccuracy_00100(ASN1WorkSpace *workspace, PositionalAccuracy_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8 *_cpointer;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace,&_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SemiMajorAxisAccuracy_00100(workspace, &value->semiMajor, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SemiMinorAxisAccuracy_00100(workspace, &value->semiMinor, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|2)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SemiMajorAxisOrientation_00100(workspace, &value->orientation, len, ASN1IMPL)) < 0) return ret;

	ASN1_Dec_Seq_EXT_UNKnow(workspace,_cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_PositionalAccuracy_00100(PositionalAccuracy_00100 *value);
extern int ASN1_BER_Data_Dec_PositionalAccuracy_00100(ASN1WorkSpace *workspace, PositionalAccuracy_00100 *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_PositionalAccuracy_00100(ASN1WorkSpace *workspace, PositionalAccuracy_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_PositionalAccuracy_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_PositionalAccuracy_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*SemiMajorAxisAccuracy_00100                            *
********************************************************/
int ASN1_CHECK_SemiMajorAxisAccuracy_00100(SemiMajorAxisAccuracy_00100 *value)
{
	unsigned char checkinfo_SemiMajorAxisAccuracy_00100[] = {
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(value, checkinfo_SemiMajorAxisAccuracy_00100)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_SemiMajorAxisAccuracy_00100(ASN1WorkSpace *workspace, SemiMajorAxisAccuracy_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_SemiMajorAxisAccuracy_00100(ASN1WorkSpace *workspace, SemiMajorAxisAccuracy_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_SemiMajorAxisAccuracy_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SemiMajorAxisAccuracy_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_SemiMajorAxisAccuracy_00100(ASN1WorkSpace *workspace, SemiMajorAxisAccuracy_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_SemiMajorAxisAccuracy_00100(ASN1WorkSpace *workspace, SemiMajorAxisAccuracy_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SemiMajorAxisAccuracy_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_SemiMajorAxisAccuracy_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*SemiMajorAxisOrientation_00100                         *
********************************************************/
int ASN1_CHECK_SemiMajorAxisOrientation_00100(SemiMajorAxisOrientation_00100 *value)
{
	unsigned char checkinfo_SemiMajorAxisOrientation_00100[] = {
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(value, checkinfo_SemiMajorAxisOrientation_00100)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_SemiMajorAxisOrientation_00100(ASN1WorkSpace *workspace, SemiMajorAxisOrientation_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_SemiMajorAxisOrientation_00100(ASN1WorkSpace *workspace, SemiMajorAxisOrientation_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_SemiMajorAxisOrientation_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SemiMajorAxisOrientation_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_SemiMajorAxisOrientation_00100(ASN1WorkSpace *workspace, SemiMajorAxisOrientation_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_SemiMajorAxisOrientation_00100(ASN1WorkSpace *workspace, SemiMajorAxisOrientation_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SemiMajorAxisOrientation_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_SemiMajorAxisOrientation_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*SemiMinorAxisAccuracy_00100                            *
********************************************************/
int ASN1_CHECK_SemiMinorAxisAccuracy_00100(SemiMinorAxisAccuracy_00100 *value)
{
	unsigned char checkinfo_SemiMinorAxisAccuracy_00100[] = {
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(value, checkinfo_SemiMinorAxisAccuracy_00100)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_SemiMinorAxisAccuracy_00100(ASN1WorkSpace *workspace, SemiMinorAxisAccuracy_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_SemiMinorAxisAccuracy_00100(ASN1WorkSpace *workspace, SemiMinorAxisAccuracy_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_SemiMinorAxisAccuracy_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SemiMinorAxisAccuracy_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_SemiMinorAxisAccuracy_00100(ASN1WorkSpace *workspace, SemiMinorAxisAccuracy_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_SemiMinorAxisAccuracy_00100(ASN1WorkSpace *workspace, SemiMinorAxisAccuracy_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SemiMinorAxisAccuracy_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_SemiMinorAxisAccuracy_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*TimeConfidence_00100                                   *
********************************************************/
int ASN1_CHECK_TimeConfidence_00100(TimeConfidence_00100 *value)
{
	unsigned char checkinfo_TimeConfidence_00100[] = {
		0x28,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,		0x0F,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,		0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)value, checkinfo_TimeConfidence_00100)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_TimeConfidence_00100(ASN1WorkSpace *workspace, TimeConfidence_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_TimeConfidence_00100(ASN1WorkSpace *workspace, TimeConfidence_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_TimeConfidence_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_TimeConfidence_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_TimeConfidence_00100(ASN1WorkSpace *workspace, TimeConfidence_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_TimeConfidence_00100(ASN1WorkSpace *workspace, TimeConfidence_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_TimeConfidence_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_TimeConfidence_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*PositionConfidenceSet_00100                            *
********************************************************/
int ASN1_GET_PositionConfidenceSet_00100_pos(ASN1WorkSpace *workspace, PositionConfidenceSet_00100 *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->pos, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_PositionConfidenceSet_00100_elevation(ASN1WorkSpace *workspace, PositionConfidenceSet_00100 *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->elevation, user_value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_PositionConfidenceSet_00100(PositionConfidenceSet_00100 *value)
{
	int ret = 0;

	unsigned char checkinfo_pos[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_elevation[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->pos), checkinfo_pos)) < 0) return ret;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->elevation), checkinfo_elevation)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Enc_PositionConfidence_00100(ASN1WorkSpace *workspace, PositionConfidence_00100 *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_ElevationConfidence_00100(ASN1WorkSpace *workspace, ElevationConfidence_00100 *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_PositionConfidenceSet_00100(ASN1WorkSpace *workspace, PositionConfidenceSet_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_PositionConfidence_00100(workspace, &(value->pos), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_ElevationConfidence_00100(workspace, &(value->elevation), ASN1IMPL)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_PositionConfidenceSet_00100(PositionConfidenceSet_00100 *value);
extern int ASN1_BER_Data_Enc_PositionConfidenceSet_00100(ASN1WorkSpace *workspace, PositionConfidenceSet_00100 *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_PositionConfidenceSet_00100(ASN1WorkSpace *workspace, PositionConfidenceSet_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_PositionConfidenceSet_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_PositionConfidenceSet_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_PositionConfidence_00100(ASN1WorkSpace *workspace, PositionConfidence_00100 *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_ElevationConfidence_00100(ASN1WorkSpace *workspace, ElevationConfidence_00100 *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_PositionConfidenceSet_00100(ASN1WorkSpace *workspace, PositionConfidenceSet_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8 *_cpointer;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace,&_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_PositionConfidence_00100(workspace, &value->pos, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_ElevationConfidence_00100(workspace, &value->elevation, len, ASN1IMPL)) < 0) return ret;

	ASN1_Dec_Seq_EXT_UNKnow(workspace,_cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_PositionConfidenceSet_00100(PositionConfidenceSet_00100 *value);
extern int ASN1_BER_Data_Dec_PositionConfidenceSet_00100(ASN1WorkSpace *workspace, PositionConfidenceSet_00100 *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_PositionConfidenceSet_00100(ASN1WorkSpace *workspace, PositionConfidenceSet_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_PositionConfidenceSet_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_PositionConfidenceSet_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*ElevationConfidence_00100                              *
********************************************************/
int ASN1_CHECK_ElevationConfidence_00100(ElevationConfidence_00100 *value)
{
	unsigned char checkinfo_ElevationConfidence_00100[] = {
		0x10,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,		0x0F,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)value, checkinfo_ElevationConfidence_00100)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_ElevationConfidence_00100(ASN1WorkSpace *workspace, ElevationConfidence_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_ElevationConfidence_00100(ASN1WorkSpace *workspace, ElevationConfidence_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_ElevationConfidence_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_ElevationConfidence_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_ElevationConfidence_00100(ASN1WorkSpace *workspace, ElevationConfidence_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_ElevationConfidence_00100(ASN1WorkSpace *workspace, ElevationConfidence_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_ElevationConfidence_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_ElevationConfidence_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*PositionConfidence_00100                               *
********************************************************/
int ASN1_CHECK_PositionConfidence_00100(PositionConfidence_00100 *value)
{
	unsigned char checkinfo_PositionConfidence_00100[] = {
		0x10,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,		0x0F,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)value, checkinfo_PositionConfidence_00100)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_PositionConfidence_00100(ASN1WorkSpace *workspace, PositionConfidence_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_PositionConfidence_00100(ASN1WorkSpace *workspace, PositionConfidence_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_PositionConfidence_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_PositionConfidence_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_PositionConfidence_00100(ASN1WorkSpace *workspace, PositionConfidence_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_PositionConfidence_00100(ASN1WorkSpace *workspace, PositionConfidence_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_PositionConfidence_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_PositionConfidence_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*SpeedandHeadingandThrottleConfidence_00100             *
********************************************************/
int ASN1_GET_SpeedandHeadingandThrottleConfidence_00100_heading(ASN1WorkSpace *workspace, SpeedandHeadingandThrottleConfidence_00100 *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->heading, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_SpeedandHeadingandThrottleConfidence_00100_speed(ASN1WorkSpace *workspace, SpeedandHeadingandThrottleConfidence_00100 *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->speed, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_SpeedandHeadingandThrottleConfidence_00100_throttle(ASN1WorkSpace *workspace, SpeedandHeadingandThrottleConfidence_00100 *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->throttle, user_value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_SpeedandHeadingandThrottleConfidence_00100(SpeedandHeadingandThrottleConfidence_00100 *value)
{
	int ret = 0;

	unsigned char checkinfo_heading[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_speed[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_throttle[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->heading), checkinfo_heading)) < 0) return ret;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->speed), checkinfo_speed)) < 0) return ret;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->throttle), checkinfo_throttle)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Enc_HeadingConfidence_00100(ASN1WorkSpace *workspace, HeadingConfidence_00100 *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_SpeedConfidence_00100(ASN1WorkSpace *workspace, SpeedConfidence_00100 *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_ThrottleConfidence_00100(ASN1WorkSpace *workspace, ThrottleConfidence_00100 *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_SpeedandHeadingandThrottleConfidence_00100(ASN1WorkSpace *workspace, SpeedandHeadingandThrottleConfidence_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_HeadingConfidence_00100(workspace, &(value->heading), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SpeedConfidence_00100(workspace, &(value->speed), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|2)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_ThrottleConfidence_00100(workspace, &(value->throttle), ASN1IMPL)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_SpeedandHeadingandThrottleConfidence_00100(SpeedandHeadingandThrottleConfidence_00100 *value);
extern int ASN1_BER_Data_Enc_SpeedandHeadingandThrottleConfidence_00100(ASN1WorkSpace *workspace, SpeedandHeadingandThrottleConfidence_00100 *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_SpeedandHeadingandThrottleConfidence_00100(ASN1WorkSpace *workspace, SpeedandHeadingandThrottleConfidence_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_SpeedandHeadingandThrottleConfidence_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SpeedandHeadingandThrottleConfidence_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_HeadingConfidence_00100(ASN1WorkSpace *workspace, HeadingConfidence_00100 *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_SpeedConfidence_00100(ASN1WorkSpace *workspace, SpeedConfidence_00100 *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_ThrottleConfidence_00100(ASN1WorkSpace *workspace, ThrottleConfidence_00100 *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_SpeedandHeadingandThrottleConfidence_00100(ASN1WorkSpace *workspace, SpeedandHeadingandThrottleConfidence_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8 *_cpointer;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace,&_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_HeadingConfidence_00100(workspace, &value->heading, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SpeedConfidence_00100(workspace, &value->speed, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|2)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_ThrottleConfidence_00100(workspace, &value->throttle, len, ASN1IMPL)) < 0) return ret;

	ASN1_Dec_Seq_EXT_UNKnow(workspace,_cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_SpeedandHeadingandThrottleConfidence_00100(SpeedandHeadingandThrottleConfidence_00100 *value);
extern int ASN1_BER_Data_Dec_SpeedandHeadingandThrottleConfidence_00100(ASN1WorkSpace *workspace, SpeedandHeadingandThrottleConfidence_00100 *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_SpeedandHeadingandThrottleConfidence_00100(ASN1WorkSpace *workspace, SpeedandHeadingandThrottleConfidence_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SpeedandHeadingandThrottleConfidence_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_SpeedandHeadingandThrottleConfidence_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*HeadingConfidence_00100                                *
********************************************************/
int ASN1_CHECK_HeadingConfidence_00100(HeadingConfidence_00100 *value)
{
	unsigned char checkinfo_HeadingConfidence_00100[] = {
		0x08,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)value, checkinfo_HeadingConfidence_00100)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_HeadingConfidence_00100(ASN1WorkSpace *workspace, HeadingConfidence_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_HeadingConfidence_00100(ASN1WorkSpace *workspace, HeadingConfidence_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_HeadingConfidence_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_HeadingConfidence_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_HeadingConfidence_00100(ASN1WorkSpace *workspace, HeadingConfidence_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_HeadingConfidence_00100(ASN1WorkSpace *workspace, HeadingConfidence_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_HeadingConfidence_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_HeadingConfidence_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*SpeedConfidence_00100                                  *
********************************************************/
int ASN1_CHECK_SpeedConfidence_00100(SpeedConfidence_00100 *value)
{
	unsigned char checkinfo_SpeedConfidence_00100[] = {
		0x08,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)value, checkinfo_SpeedConfidence_00100)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_SpeedConfidence_00100(ASN1WorkSpace *workspace, SpeedConfidence_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_SpeedConfidence_00100(ASN1WorkSpace *workspace, SpeedConfidence_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_SpeedConfidence_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SpeedConfidence_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_SpeedConfidence_00100(ASN1WorkSpace *workspace, SpeedConfidence_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_SpeedConfidence_00100(ASN1WorkSpace *workspace, SpeedConfidence_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SpeedConfidence_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_SpeedConfidence_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*ThrottleConfidence_00100                               *
********************************************************/
int ASN1_CHECK_ThrottleConfidence_00100(ThrottleConfidence_00100 *value)
{
	unsigned char checkinfo_ThrottleConfidence_00100[] = {
		0x04,0x00,0x01,0x02,0x03,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)value, checkinfo_ThrottleConfidence_00100)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_ThrottleConfidence_00100(ASN1WorkSpace *workspace, ThrottleConfidence_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_ThrottleConfidence_00100(ASN1WorkSpace *workspace, ThrottleConfidence_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_ThrottleConfidence_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_ThrottleConfidence_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_ThrottleConfidence_00100(ASN1WorkSpace *workspace, ThrottleConfidence_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_ThrottleConfidence_00100(ASN1WorkSpace *workspace, ThrottleConfidence_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_ThrottleConfidence_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_ThrottleConfidence_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*FullPositionVector_00100                               *
********************************************************/
int ASN1_GET_FullPositionVector_00100_utcTime(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, DDateTime_00100 **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_FullPositionVector_00100_utcTime == 1)
	{
		*user_value = value->utcTime;
	}
	else return -2;
	return ret;
}
int ASN1_GET_FullPositionVector_00100_lon(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->lon, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_FullPositionVector_00100_lat(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->lat, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_FullPositionVector_00100_elevation(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_FullPositionVector_00100_elevation == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->elevation, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_FullPositionVector_00100_heading(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_FullPositionVector_00100_heading == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->heading, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_FullPositionVector_00100_speed(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, TransmissionAndSpeed_00100 **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_FullPositionVector_00100_speed == 1)
	{
		*user_value = value->speed;
	}
	else return -2;
	return ret;
}
int ASN1_GET_FullPositionVector_00100_posAccuracy(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, PositionalAccuracy_00100 **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_FullPositionVector_00100_posAccuracy == 1)
	{
		*user_value = value->posAccuracy;
	}
	else return -2;
	return ret;
}
int ASN1_GET_FullPositionVector_00100_timeConfidence(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_FullPositionVector_00100_timeConfidence == 1)
	{
		if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->timeConfidence, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_FullPositionVector_00100_posConfidence(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, PositionConfidenceSet_00100 **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_FullPositionVector_00100_posConfidence == 1)
	{
		*user_value = value->posConfidence;
	}
	else return -2;
	return ret;
}
int ASN1_GET_FullPositionVector_00100_speedConfidence(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, SpeedandHeadingandThrottleConfidence_00100 **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_FullPositionVector_00100_speedConfidence == 1)
	{
		*user_value = value->speedConfidence;
	}
	else return -2;
	return ret;
}
extern int ASN1_CHECK_DDateTime_00100(DDateTime_00100 *value);
extern int ASN1_CHECK_TransmissionAndSpeed_00100(TransmissionAndSpeed_00100 *value);
extern int ASN1_CHECK_PositionalAccuracy_00100(PositionalAccuracy_00100 *value);
extern int ASN1_CHECK_PositionConfidenceSet_00100(PositionConfidenceSet_00100 *value);
extern int ASN1_CHECK_SpeedandHeadingandThrottleConfidence_00100(SpeedandHeadingandThrottleConfidence_00100 *value);
int ASN1_CHECK_FullPositionVector_00100(FullPositionVector_00100 *value)
{
	int ret = 0;

	unsigned char checkinfo_utcTime[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_lon[] = {
		0x02,0x84,0x94,0xB6,0x2E,0x01,0x84,0x6B,0x49,0xD2,0x01,0x00
	};
	unsigned char checkinfo_lat[] = {
		0x02,0x84,0xCA,0x5B,0x17,0x00,0x84,0x35,0xA4,0xE9,0x01,0x00
	};
	unsigned char checkinfo_elevation[] = {
		0x02,0x82,0xF0,0x00,0x83,0x00,0xEF,0xFF,0x00
	};
	unsigned char checkinfo_heading[] = {
		0x02,0x00,0x82,0x70,0x80,0x00
	};
	unsigned char checkinfo_speed[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_posAccuracy[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_timeConfidence[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_posConfidence[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_speedConfidence[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if (value->DEF_FullPositionVector_00100_utcTime == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_DDateTime_00100(value->utcTime)) < 0) return ret;
	} /* OPTIONAL end */
	if ((ret = ASN1_CHECK_INTEGER(&(value->lon), checkinfo_lon)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->lat), checkinfo_lat)) < 0) return ret;
	if (value->DEF_FullPositionVector_00100_elevation == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->elevation), checkinfo_elevation)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_FullPositionVector_00100_heading == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->heading), checkinfo_heading)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_FullPositionVector_00100_speed == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_TransmissionAndSpeed_00100(value->speed)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_FullPositionVector_00100_posAccuracy == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_PositionalAccuracy_00100(value->posAccuracy)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_FullPositionVector_00100_timeConfidence == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->timeConfidence), checkinfo_timeConfidence)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_FullPositionVector_00100_posConfidence == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_PositionConfidenceSet_00100(value->posConfidence)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_FullPositionVector_00100_speedConfidence == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_SpeedandHeadingandThrottleConfidence_00100(value->speedConfidence)) < 0) return ret;
	} /* OPTIONAL end */
	return ret;
}
extern int ASN1_BER_Data_Enc_DDateTime_00100(ASN1WorkSpace *workspace, DDateTime_00100 *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_Longitude_00100(ASN1WorkSpace *workspace, Longitude_00100 *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_Latitude_00100(ASN1WorkSpace *workspace, Latitude_00100 *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_Elevation_00100(ASN1WorkSpace *workspace, Elevation_00100 *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_Heading_00100(ASN1WorkSpace *workspace, Heading_00100 *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_TransmissionAndSpeed_00100(ASN1WorkSpace *workspace, TransmissionAndSpeed_00100 *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_PositionalAccuracy_00100(ASN1WorkSpace *workspace, PositionalAccuracy_00100 *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_TimeConfidence_00100(ASN1WorkSpace *workspace, TimeConfidence_00100 *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_PositionConfidenceSet_00100(ASN1WorkSpace *workspace, PositionConfidenceSet_00100 *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_SpeedandHeadingandThrottleConfidence_00100(ASN1WorkSpace *workspace, SpeedandHeadingandThrottleConfidence_00100 *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_FullPositionVector_00100(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
	}
	if (value->DEF_FullPositionVector_00100_utcTime == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_CONS|0)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_DDateTime_00100(workspace, value->utcTime, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Longitude_00100(workspace, &(value->lon), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|2)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Latitude_00100(workspace, &(value->lat), ASN1IMPL)) < 0) return ret;
	if (value->DEF_FullPositionVector_00100_elevation == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|3)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_Elevation_00100(workspace, &(value->elevation), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_FullPositionVector_00100_heading == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|4)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_Heading_00100(workspace, &(value->heading), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_FullPositionVector_00100_speed == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_CONS|5)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_TransmissionAndSpeed_00100(workspace, value->speed, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	if (value->DEF_FullPositionVector_00100_posAccuracy == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_CONS|6)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_PositionalAccuracy_00100(workspace, value->posAccuracy, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	if (value->DEF_FullPositionVector_00100_timeConfidence == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|7)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_TimeConfidence_00100(workspace, &(value->timeConfidence), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_FullPositionVector_00100_posConfidence == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_CONS|8)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_PositionConfidenceSet_00100(workspace, value->posConfidence, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	if (value->DEF_FullPositionVector_00100_speedConfidence == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_CONS|9)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_SpeedandHeadingandThrottleConfidence_00100(workspace, value->speedConfidence, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_FullPositionVector_00100(FullPositionVector_00100 *value);
extern int ASN1_BER_Data_Enc_FullPositionVector_00100(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_FullPositionVector_00100(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_FullPositionVector_00100(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_FullPositionVector_00100(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_DDateTime_00100(ASN1WorkSpace *workspace, DDateTime_00100 *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_Longitude_00100(ASN1WorkSpace *workspace, Longitude_00100 *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_Latitude_00100(ASN1WorkSpace *workspace, Latitude_00100 *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_Elevation_00100(ASN1WorkSpace *workspace, Elevation_00100 *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_Heading_00100(ASN1WorkSpace *workspace, Heading_00100 *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_TransmissionAndSpeed_00100(ASN1WorkSpace *workspace, TransmissionAndSpeed_00100 *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_PositionalAccuracy_00100(ASN1WorkSpace *workspace, PositionalAccuracy_00100 *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_TimeConfidence_00100(ASN1WorkSpace *workspace, TimeConfidence_00100 *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_PositionConfidenceSet_00100(ASN1WorkSpace *workspace, PositionConfidenceSet_00100 *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_SpeedandHeadingandThrottleConfidence_00100(ASN1WorkSpace *workspace, SpeedandHeadingandThrottleConfidence_00100 *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_FullPositionVector_00100(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	ASNUINT8 *_cpointer;
	value->utcTime = (DDateTime_00100 *)mpool_malloc(workspace->Pmemory, sizeof(DDateTime_00100));
	memset(value->utcTime, 0, sizeof(DDateTime_00100));
	value->speed = (TransmissionAndSpeed_00100 *)mpool_malloc(workspace->Pmemory, sizeof(TransmissionAndSpeed_00100));
	memset(value->speed, 0, sizeof(TransmissionAndSpeed_00100));
	value->posAccuracy = (PositionalAccuracy_00100 *)mpool_malloc(workspace->Pmemory, sizeof(PositionalAccuracy_00100));
	memset(value->posAccuracy, 0, sizeof(PositionalAccuracy_00100));
	value->posConfidence = (PositionConfidenceSet_00100 *)mpool_malloc(workspace->Pmemory, sizeof(PositionConfidenceSet_00100));
	memset(value->posConfidence, 0, sizeof(PositionConfidenceSet_00100));
	value->speedConfidence = (SpeedandHeadingandThrottleConfidence_00100 *)mpool_malloc(workspace->Pmemory, sizeof(SpeedandHeadingandThrottleConfidence_00100));
	memset(value->speedConfidence, 0, sizeof(SpeedandHeadingandThrottleConfidence_00100));

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace,&_cpointer);
	if ((ret = ASN1_BER_GET_Tag(workspace,&tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT|ITS_ASN_CONS|0))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_CONS|0)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_DDateTime_00100(workspace, value->utcTime, len, ASN1IMPL)) < 0) return ret;

		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->DEF_FullPositionVector_00100_utcTime = 1;
	}
	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Longitude_00100(workspace, &value->lon, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|2)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Latitude_00100(workspace, &value->lat, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace,&tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT|ITS_ASN_PRIM|3))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|3)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_Elevation_00100(workspace, &value->elevation, len, ASN1IMPL)) < 0) return ret;

		value->DEF_FullPositionVector_00100_elevation = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace,&tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT|ITS_ASN_PRIM|4))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|4)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_Heading_00100(workspace, &value->heading, len, ASN1IMPL)) < 0) return ret;

		value->DEF_FullPositionVector_00100_heading = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace,&tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT|ITS_ASN_CONS|5))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_CONS|5)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_TransmissionAndSpeed_00100(workspace, value->speed, len, ASN1IMPL)) < 0) return ret;

		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->DEF_FullPositionVector_00100_speed = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace,&tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT|ITS_ASN_CONS|6))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_CONS|6)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_PositionalAccuracy_00100(workspace, value->posAccuracy, len, ASN1IMPL)) < 0) return ret;

		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->DEF_FullPositionVector_00100_posAccuracy = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace,&tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT|ITS_ASN_PRIM|7))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|7)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_TimeConfidence_00100(workspace, &value->timeConfidence, len, ASN1IMPL)) < 0) return ret;

		value->DEF_FullPositionVector_00100_timeConfidence = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace,&tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT|ITS_ASN_CONS|8))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_CONS|8)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_PositionConfidenceSet_00100(workspace, value->posConfidence, len, ASN1IMPL)) < 0) return ret;

		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->DEF_FullPositionVector_00100_posConfidence = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace,&tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT|ITS_ASN_CONS|9))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_CONS|9)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_SpeedandHeadingandThrottleConfidence_00100(workspace, value->speedConfidence, len, ASN1IMPL)) < 0) return ret;

		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->DEF_FullPositionVector_00100_speedConfidence = 1;
	}
	ASN1_Dec_Seq_EXT_UNKnow(workspace,_cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_FullPositionVector_00100(FullPositionVector_00100 *value);
extern int ASN1_BER_Data_Dec_FullPositionVector_00100(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_FullPositionVector_00100(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_FullPositionVector_00100(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_FullPositionVector_00100(value)) < 0) return ret;
	return ret;
}

/********************************************************
*IncidentDetectionInfo_incident_Detected_Type           *
********************************************************/
int ASN1_CHECK_IncidentDetectionInfo_incident_Detected_Type(IncidentDetectionInfo_incident_Detected_Type *value)
{
	unsigned char checkinfo_IncidentDetectionInfo_incident_Detected_Type[] = {
		0x09,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)value, checkinfo_IncidentDetectionInfo_incident_Detected_Type)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_IncidentDetectionInfo_incident_Detected_Type(ASN1WorkSpace *workspace, IncidentDetectionInfo_incident_Detected_Type *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_IncidentDetectionInfo_incident_Detected_Type(ASN1WorkSpace *workspace, IncidentDetectionInfo_incident_Detected_Type *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_IncidentDetectionInfo_incident_Detected_Type(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_IncidentDetectionInfo_incident_Detected_Type(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_IncidentDetectionInfo_incident_Detected_Type(ASN1WorkSpace *workspace, IncidentDetectionInfo_incident_Detected_Type *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_IncidentDetectionInfo_incident_Detected_Type(ASN1WorkSpace *workspace, IncidentDetectionInfo_incident_Detected_Type *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_IncidentDetectionInfo_incident_Detected_Type(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_IncidentDetectionInfo_incident_Detected_Type(value)) < 0) return ret;
	return ret;
}

/********************************************************
*NMEACoord_compass                                      *
********************************************************/
int ASN1_CHECK_NMEACoord_compass(NMEACoord_compass *value)
{
	unsigned char checkinfo_NMEACoord_compass[] = {
		0x02,0x00,0x01,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)value, checkinfo_NMEACoord_compass)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_NMEACoord_compass(ASN1WorkSpace *workspace, NMEACoord_compass *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_NMEACoord_compass(ASN1WorkSpace *workspace, NMEACoord_compass *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_NMEACoord_compass(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_NMEACoord_compass(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_NMEACoord_compass(ASN1WorkSpace *workspace, NMEACoord_compass *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_NMEACoord_compass(ASN1WorkSpace *workspace, NMEACoord_compass *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_NMEACoord_compass(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_NMEACoord_compass(value)) < 0) return ret;
	return ret;
}

/********************************************************
*NMEACoord_latitude                                     *
********************************************************/
int ASN1_GET_NMEACoord_latitude_integerValue(ASN1WorkSpace *workspace, NMEACoord_latitude *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->integerValue, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_NMEACoord_latitude_fractionValue(ASN1WorkSpace *workspace, NMEACoord_latitude *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->fractionValue, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_NMEACoord_latitude_fracSize(ASN1WorkSpace *workspace, NMEACoord_latitude *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->fracSize, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_NMEACoord_latitude_compass(ASN1WorkSpace *workspace, NMEACoord_latitude *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->compass, user_value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_NMEACoord_latitude(NMEACoord_latitude *value)
{
	int ret = 0;

	unsigned char checkinfo_integerValue[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_fractionValue[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_fracSize[] = {
		0x02,0x00,0x0A,0x00
	};
	unsigned char checkinfo_compass[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(&(value->integerValue), checkinfo_integerValue)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->fractionValue), checkinfo_fractionValue)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->fracSize), checkinfo_fracSize)) < 0) return ret;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->compass), checkinfo_compass)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Enc_NMEACoord_compass(ASN1WorkSpace *workspace, NMEACoord_compass *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_NMEACoord_latitude(ASN1WorkSpace *workspace, NMEACoord_latitude *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->integerValue), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->fractionValue), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|2)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->fracSize), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|3)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_NMEACoord_compass(workspace, &(value->compass), ASN1IMPL)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_NMEACoord_latitude(NMEACoord_latitude *value);
extern int ASN1_BER_Data_Enc_NMEACoord_latitude(ASN1WorkSpace *workspace, NMEACoord_latitude *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_NMEACoord_latitude(ASN1WorkSpace *workspace, NMEACoord_latitude *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_NMEACoord_latitude(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_NMEACoord_latitude(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_NMEACoord_compass(ASN1WorkSpace *workspace, NMEACoord_compass *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_NMEACoord_latitude(ASN1WorkSpace *workspace, NMEACoord_latitude *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8 *_cpointer;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace,&_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->integerValue, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->fractionValue, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|2)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->fracSize, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|3)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_NMEACoord_compass(workspace, &value->compass, len, ASN1IMPL)) < 0) return ret;

	ASN1_Dec_Seq_EXT_UNKnow(workspace,_cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_NMEACoord_latitude(NMEACoord_latitude *value);
extern int ASN1_BER_Data_Dec_NMEACoord_latitude(ASN1WorkSpace *workspace, NMEACoord_latitude *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_NMEACoord_latitude(ASN1WorkSpace *workspace, NMEACoord_latitude *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_NMEACoord_latitude(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_NMEACoord_latitude(value)) < 0) return ret;
	return ret;
}

/********************************************************
*NMEACoord_longitude                                    *
********************************************************/
int ASN1_GET_NMEACoord_longitude_integerValue(ASN1WorkSpace *workspace, NMEACoord_longitude *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->integerValue, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_NMEACoord_longitude_fractionValue(ASN1WorkSpace *workspace, NMEACoord_longitude *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->fractionValue, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_NMEACoord_longitude_fracSize(ASN1WorkSpace *workspace, NMEACoord_longitude *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->fracSize, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_NMEACoord_longitude_compass(ASN1WorkSpace *workspace, NMEACoord_longitude *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->compass, user_value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_NMEACoord_longitude(NMEACoord_longitude *value)
{
	int ret = 0;

	unsigned char checkinfo_integerValue[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_fractionValue[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_fracSize[] = {
		0x02,0x00,0x0A,0x00
	};
	unsigned char checkinfo_compass[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(&(value->integerValue), checkinfo_integerValue)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->fractionValue), checkinfo_fractionValue)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->fracSize), checkinfo_fracSize)) < 0) return ret;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->compass), checkinfo_compass)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Enc_NMEACoord_compass(ASN1WorkSpace *workspace, NMEACoord_compass *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_NMEACoord_longitude(ASN1WorkSpace *workspace, NMEACoord_longitude *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->integerValue), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->fractionValue), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|2)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->fracSize), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|3)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_NMEACoord_compass(workspace, &(value->compass), ASN1IMPL)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_NMEACoord_longitude(NMEACoord_longitude *value);
extern int ASN1_BER_Data_Enc_NMEACoord_longitude(ASN1WorkSpace *workspace, NMEACoord_longitude *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_NMEACoord_longitude(ASN1WorkSpace *workspace, NMEACoord_longitude *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_NMEACoord_longitude(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_NMEACoord_longitude(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_NMEACoord_compass(ASN1WorkSpace *workspace, NMEACoord_compass *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_NMEACoord_longitude(ASN1WorkSpace *workspace, NMEACoord_longitude *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8 *_cpointer;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace,&_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->integerValue, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->fractionValue, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|2)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->fracSize, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|3)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_NMEACoord_compass(workspace, &value->compass, len, ASN1IMPL)) < 0) return ret;

	ASN1_Dec_Seq_EXT_UNKnow(workspace,_cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_NMEACoord_longitude(NMEACoord_longitude *value);
extern int ASN1_BER_Data_Dec_NMEACoord_longitude(ASN1WorkSpace *workspace, NMEACoord_longitude *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_NMEACoord_longitude(ASN1WorkSpace *workspace, NMEACoord_longitude *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_NMEACoord_longitude(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_NMEACoord_longitude(value)) < 0) return ret;
	return ret;
}

/********************************************************
*NMEACoord                                              *
********************************************************/
int ASN1_GET_NMEACoord_latitude(ASN1WorkSpace *workspace, NMEACoord *value, NMEACoord_latitude **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = value->latitude;
	return ret;
}
int ASN1_GET_NMEACoord_longitude(ASN1WorkSpace *workspace, NMEACoord *value, NMEACoord_longitude **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = value->longitude;
	return ret;
}
int ASN1_GET_NMEACoord_optData(ASN1WorkSpace *workspace, NMEACoord *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_NMEACoord_optData == 1)
	{
		if ((ret = ASN1_GET_OCTETSTRING(workspace, &value->optData, user_value, user_value_length)) < 0) return ret;
	}
	else return -2;
	return ret;
}
extern int ASN1_CHECK_NMEACoord_latitude(NMEACoord_latitude *value);
extern int ASN1_CHECK_NMEACoord_longitude(NMEACoord_longitude *value);
int ASN1_CHECK_NMEACoord(NMEACoord *value)
{
	int ret = 0;

	unsigned char checkinfo_latitude[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_longitude[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_optData[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_NMEACoord_latitude(value->latitude)) < 0) return ret;
	if ((ret = ASN1_CHECK_NMEACoord_longitude(value->longitude)) < 0) return ret;
	if (value->DEF_NMEACoord_optData == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_OCTETSTRING(&(value->optData), checkinfo_optData)) < 0) return ret;
	} /* OPTIONAL end */
	return ret;
}
extern int ASN1_BER_Data_Enc_NMEACoord_latitude(ASN1WorkSpace *workspace, NMEACoord_latitude *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_NMEACoord_longitude(ASN1WorkSpace *workspace, NMEACoord_longitude *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_NMEACoord(ASN1WorkSpace *workspace, NMEACoord *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_CONS|0)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_NMEACoord_latitude(workspace, value->latitude, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_CONS|1)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_NMEACoord_longitude(workspace, value->longitude, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	if (value->DEF_NMEACoord_optData == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|2)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_OCTETSTRING(workspace, &(value->optData), ASN1IMPL)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_NMEACoord(NMEACoord *value);
extern int ASN1_BER_Data_Enc_NMEACoord(ASN1WorkSpace *workspace, NMEACoord *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_NMEACoord(ASN1WorkSpace *workspace, NMEACoord *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_NMEACoord(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_NMEACoord(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_NMEACoord_latitude(ASN1WorkSpace *workspace, NMEACoord_latitude *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_NMEACoord_longitude(ASN1WorkSpace *workspace, NMEACoord_longitude *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_NMEACoord(ASN1WorkSpace *workspace, NMEACoord *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	ASNUINT8 *_cpointer;
	value->latitude = (NMEACoord_latitude *)mpool_malloc(workspace->Pmemory, sizeof(NMEACoord_latitude));
	memset(value->latitude, 0, sizeof(NMEACoord_latitude));
	value->longitude = (NMEACoord_longitude *)mpool_malloc(workspace->Pmemory, sizeof(NMEACoord_longitude));
	memset(value->longitude, 0, sizeof(NMEACoord_longitude));

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace,&_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_CONS|0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_NMEACoord_latitude(workspace, value->latitude, len, ASN1IMPL)) < 0) return ret;

	if (IfFixedLength(len) == -1)
	{
		if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
	}
	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_CONS|1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_NMEACoord_longitude(workspace, value->longitude, len, ASN1IMPL)) < 0) return ret;

	if (IfFixedLength(len) == -1)
	{
		if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace,&tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT|ITS_ASN_PRIM|2))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|2)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_OCTETSTRING(workspace, &value->optData, len, ASN1IMPL)) < 0) return ret;

		value->DEF_NMEACoord_optData = 1;
	}
	ASN1_Dec_Seq_EXT_UNKnow(workspace,_cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_NMEACoord(NMEACoord *value);
extern int ASN1_BER_Data_Dec_NMEACoord(ASN1WorkSpace *workspace, NMEACoord *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_NMEACoord(ASN1WorkSpace *workspace, NMEACoord *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_NMEACoord(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_NMEACoord(value)) < 0) return ret;
	return ret;
}

/********************************************************
*IncidentDetectionInfo                                  *
********************************************************/
int ASN1_GET_IncidentDetectionInfo_incident_Detected_Time(ASN1WorkSpace *workspace, IncidentDetectionInfo *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_VisibleString(workspace, &value->incident_Detected_Time, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_IncidentDetectionInfo_incident_Detected_Type(ASN1WorkSpace *workspace, IncidentDetectionInfo *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->incident_Detected_Type, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_IncidentDetectionInfo_incident_Detected_Site(ASN1WorkSpace *workspace, IncidentDetectionInfo *value, NMEACoord **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = value->incident_Detected_Site;
	return ret;
}
int ASN1_GET_IncidentDetectionInfo_detected_Object_Size(ASN1WorkSpace *workspace, IncidentDetectionInfo *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_IncidentDetectionInfo_detected_Object_Size == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->detected_Object_Size, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_IncidentDetectionInfo_detected_Object_Distance(ASN1WorkSpace *workspace, IncidentDetectionInfo *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->detected_Object_Distance, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_IncidentDetectionInfo_detected_Object_Angle(ASN1WorkSpace *workspace, IncidentDetectionInfo *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->detected_Object_Angle, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_IncidentDetectionInfo_detected_Object_Speed(ASN1WorkSpace *workspace, IncidentDetectionInfo *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->detected_Object_Speed, user_value)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_NMEACoord(NMEACoord *value);
int ASN1_CHECK_IncidentDetectionInfo(IncidentDetectionInfo *value)
{
	int ret = 0;

	unsigned char checkinfo_incident_Detected_Time[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_incident_Detected_Type[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_incident_Detected_Site[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_detected_Object_Size[] = {
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_detected_Object_Distance[] = {
		0x02,0x00,0x82,0x03,0xE8,0x00
	};
	unsigned char checkinfo_detected_Object_Angle[] = {
		0x02,0x00,0x82,0x01,0x68,0x00
	};
	unsigned char checkinfo_detected_Object_Speed[] = {
		0x02,0x00,0x82,0x01,0x2C,0x00
	};

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_VisibleString(&(value->incident_Detected_Time), checkinfo_incident_Detected_Time)) < 0) return ret;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->incident_Detected_Type), checkinfo_incident_Detected_Type)) < 0) return ret;
	if ((ret = ASN1_CHECK_NMEACoord(value->incident_Detected_Site)) < 0) return ret;
	if (value->DEF_IncidentDetectionInfo_detected_Object_Size == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->detected_Object_Size), checkinfo_detected_Object_Size)) < 0) return ret;
	} /* OPTIONAL end */
	if ((ret = ASN1_CHECK_INTEGER(&(value->detected_Object_Distance), checkinfo_detected_Object_Distance)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->detected_Object_Angle), checkinfo_detected_Object_Angle)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->detected_Object_Speed), checkinfo_detected_Object_Speed)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Enc_IncidentDetectionInfo_incident_Detected_Type(ASN1WorkSpace *workspace, IncidentDetectionInfo_incident_Detected_Type *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_NMEACoord(ASN1WorkSpace *workspace, NMEACoord *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_IncidentDetectionInfo(ASN1WorkSpace *workspace, IncidentDetectionInfo *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_VisibleString(workspace, &(value->incident_Detected_Time), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_IncidentDetectionInfo_incident_Detected_Type(workspace, &(value->incident_Detected_Type), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_CONS|2)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_NMEACoord(workspace, value->incident_Detected_Site, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	if (value->DEF_IncidentDetectionInfo_detected_Object_Size == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|3)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->detected_Object_Size), ASN1IMPL)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|4)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->detected_Object_Distance), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|5)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->detected_Object_Angle), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|6)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->detected_Object_Speed), ASN1IMPL)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_IncidentDetectionInfo(IncidentDetectionInfo *value);
extern int ASN1_BER_Data_Enc_IncidentDetectionInfo(ASN1WorkSpace *workspace, IncidentDetectionInfo *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_IncidentDetectionInfo(ASN1WorkSpace *workspace, IncidentDetectionInfo *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_IncidentDetectionInfo(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_IncidentDetectionInfo(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_IncidentDetectionInfo_incident_Detected_Type(ASN1WorkSpace *workspace, IncidentDetectionInfo_incident_Detected_Type *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_NMEACoord(ASN1WorkSpace *workspace, NMEACoord *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_IncidentDetectionInfo(ASN1WorkSpace *workspace, IncidentDetectionInfo *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	ASNUINT8 *_cpointer;
	value->incident_Detected_Site = (NMEACoord *)mpool_malloc(workspace->Pmemory, sizeof(NMEACoord));
	memset(value->incident_Detected_Site, 0, sizeof(NMEACoord));

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace,&_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_VisibleString(workspace, &value->incident_Detected_Time, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_IncidentDetectionInfo_incident_Detected_Type(workspace, &value->incident_Detected_Type, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_CONS|2)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_NMEACoord(workspace, value->incident_Detected_Site, len, ASN1IMPL)) < 0) return ret;

	if (IfFixedLength(len) == -1)
	{
		if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace,&tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT|ITS_ASN_PRIM|3))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|3)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->detected_Object_Size, len, ASN1IMPL)) < 0) return ret;

		value->DEF_IncidentDetectionInfo_detected_Object_Size = 1;
	}
	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|4)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->detected_Object_Distance, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|5)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->detected_Object_Angle, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|6)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->detected_Object_Speed, len, ASN1IMPL)) < 0) return ret;

	ASN1_Dec_Seq_EXT_UNKnow(workspace,_cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_IncidentDetectionInfo(IncidentDetectionInfo *value);
extern int ASN1_BER_Data_Dec_IncidentDetectionInfo(ASN1WorkSpace *workspace, IncidentDetectionInfo *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_IncidentDetectionInfo(ASN1WorkSpace *workspace, IncidentDetectionInfo *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_IncidentDetectionInfo(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_IncidentDetectionInfo(value)) < 0) return ret;
	return ret;
}

/********************************************************
*IncidentTerminationInfo_terminate_incidentType         *
********************************************************/
int ASN1_CHECK_IncidentTerminationInfo_terminate_incidentType(IncidentTerminationInfo_terminate_incidentType *value)
{
	unsigned char checkinfo_IncidentTerminationInfo_terminate_incidentType[] = {
		0x02,0x01,0x02,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)value, checkinfo_IncidentTerminationInfo_terminate_incidentType)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_IncidentTerminationInfo_terminate_incidentType(ASN1WorkSpace *workspace, IncidentTerminationInfo_terminate_incidentType *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_IncidentTerminationInfo_terminate_incidentType(ASN1WorkSpace *workspace, IncidentTerminationInfo_terminate_incidentType *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_IncidentTerminationInfo_terminate_incidentType(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_IncidentTerminationInfo_terminate_incidentType(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_IncidentTerminationInfo_terminate_incidentType(ASN1WorkSpace *workspace, IncidentTerminationInfo_terminate_incidentType *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_IncidentTerminationInfo_terminate_incidentType(ASN1WorkSpace *workspace, IncidentTerminationInfo_terminate_incidentType *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_IncidentTerminationInfo_terminate_incidentType(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_IncidentTerminationInfo_terminate_incidentType(value)) < 0) return ret;
	return ret;
}

/********************************************************
*IncidentTerminationInfo                                *
********************************************************/
int ASN1_GET_IncidentTerminationInfo_terminate_incidentType(ASN1WorkSpace *workspace, IncidentTerminationInfo *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->terminate_incidentType, user_value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_IncidentTerminationInfo(IncidentTerminationInfo *value)
{
	int ret = 0;

	unsigned char checkinfo_terminate_incidentType[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->terminate_incidentType), checkinfo_terminate_incidentType)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Enc_IncidentTerminationInfo_terminate_incidentType(ASN1WorkSpace *workspace, IncidentTerminationInfo_terminate_incidentType *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_IncidentTerminationInfo(ASN1WorkSpace *workspace, IncidentTerminationInfo *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_IncidentTerminationInfo_terminate_incidentType(workspace, &(value->terminate_incidentType), ASN1IMPL)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_IncidentTerminationInfo(IncidentTerminationInfo *value);
extern int ASN1_BER_Data_Enc_IncidentTerminationInfo(ASN1WorkSpace *workspace, IncidentTerminationInfo *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_IncidentTerminationInfo(ASN1WorkSpace *workspace, IncidentTerminationInfo *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_IncidentTerminationInfo(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_IncidentTerminationInfo(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_IncidentTerminationInfo_terminate_incidentType(ASN1WorkSpace *workspace, IncidentTerminationInfo_terminate_incidentType *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_IncidentTerminationInfo(ASN1WorkSpace *workspace, IncidentTerminationInfo *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8 *_cpointer;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace,&_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_IncidentTerminationInfo_terminate_incidentType(workspace, &value->terminate_incidentType, len, ASN1IMPL)) < 0) return ret;

	ASN1_Dec_Seq_EXT_UNKnow(workspace,_cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_IncidentTerminationInfo(IncidentTerminationInfo *value);
extern int ASN1_BER_Data_Dec_IncidentTerminationInfo(ASN1WorkSpace *workspace, IncidentTerminationInfo *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_IncidentTerminationInfo(ASN1WorkSpace *workspace, IncidentTerminationInfo *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_IncidentTerminationInfo(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_IncidentTerminationInfo(value)) < 0) return ret;
	return ret;
}

/********************************************************
*IncidentDetectionVideoFileInfoProvide_fileStatus       *
********************************************************/
int ASN1_CHECK_IncidentDetectionVideoFileInfoProvide_fileStatus(IncidentDetectionVideoFileInfoProvide_fileStatus *value)
{
	unsigned char checkinfo_IncidentDetectionVideoFileInfoProvide_fileStatus[] = {
		0x02,0x00,0x01,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)value, checkinfo_IncidentDetectionVideoFileInfoProvide_fileStatus)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_IncidentDetectionVideoFileInfoProvide_fileStatus(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvide_fileStatus *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_IncidentDetectionVideoFileInfoProvide_fileStatus(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvide_fileStatus *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_IncidentDetectionVideoFileInfoProvide_fileStatus(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_IncidentDetectionVideoFileInfoProvide_fileStatus(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_IncidentDetectionVideoFileInfoProvide_fileStatus(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvide_fileStatus *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_IncidentDetectionVideoFileInfoProvide_fileStatus(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvide_fileStatus *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_IncidentDetectionVideoFileInfoProvide_fileStatus(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_IncidentDetectionVideoFileInfoProvide_fileStatus(value)) < 0) return ret;
	return ret;
}

/********************************************************
*IncidentDetectionVideoFileInfoProvide                  *
********************************************************/
int ASN1_GET_IncidentDetectionVideoFileInfoProvide_fileStatus(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvide *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->fileStatus, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_IncidentDetectionVideoFileInfoProvide_fileName(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvide *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_IncidentDetectionVideoFileInfoProvide_fileName == 1)
	{
		if ((ret = ASN1_GET_OCTETSTRING(workspace, &value->fileName, user_value, user_value_length)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_IncidentDetectionVideoFileInfoProvide_fileSize(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvide *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_IncidentDetectionVideoFileInfoProvide_fileSize == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->fileSize, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_CHECK_IncidentDetectionVideoFileInfoProvide(IncidentDetectionVideoFileInfoProvide *value)
{
	int ret = 0;

	unsigned char checkinfo_fileStatus[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_fileName[] = {
		0x02,0x01,0x1E,0x00
	};
	unsigned char checkinfo_fileSize[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->fileStatus), checkinfo_fileStatus)) < 0) return ret;
	if (value->DEF_IncidentDetectionVideoFileInfoProvide_fileName == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_OCTETSTRING(&(value->fileName), checkinfo_fileName)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_IncidentDetectionVideoFileInfoProvide_fileSize == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->fileSize), checkinfo_fileSize)) < 0) return ret;
	} /* OPTIONAL end */
	return ret;
}
extern int ASN1_BER_Data_Enc_IncidentDetectionVideoFileInfoProvide_fileStatus(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvide_fileStatus *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_IncidentDetectionVideoFileInfoProvide(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvide *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_IncidentDetectionVideoFileInfoProvide_fileStatus(workspace, &(value->fileStatus), ASN1IMPL)) < 0) return ret;
	if (value->DEF_IncidentDetectionVideoFileInfoProvide_fileName == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_OCTETSTRING(workspace, &(value->fileName), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_IncidentDetectionVideoFileInfoProvide_fileSize == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|2)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->fileSize), ASN1IMPL)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_IncidentDetectionVideoFileInfoProvide(IncidentDetectionVideoFileInfoProvide *value);
extern int ASN1_BER_Data_Enc_IncidentDetectionVideoFileInfoProvide(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvide *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_IncidentDetectionVideoFileInfoProvide(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvide *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_IncidentDetectionVideoFileInfoProvide(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_IncidentDetectionVideoFileInfoProvide(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_IncidentDetectionVideoFileInfoProvide_fileStatus(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvide_fileStatus *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_IncidentDetectionVideoFileInfoProvide(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvide *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	ASNUINT8 *_cpointer;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace,&_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_IncidentDetectionVideoFileInfoProvide_fileStatus(workspace, &value->fileStatus, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace,&tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT|ITS_ASN_PRIM|1))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_OCTETSTRING(workspace, &value->fileName, len, ASN1IMPL)) < 0) return ret;

		value->DEF_IncidentDetectionVideoFileInfoProvide_fileName = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace,&tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT|ITS_ASN_PRIM|2))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|2)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->fileSize, len, ASN1IMPL)) < 0) return ret;

		value->DEF_IncidentDetectionVideoFileInfoProvide_fileSize = 1;
	}
	ASN1_Dec_Seq_EXT_UNKnow(workspace,_cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_IncidentDetectionVideoFileInfoProvide(IncidentDetectionVideoFileInfoProvide *value);
extern int ASN1_BER_Data_Dec_IncidentDetectionVideoFileInfoProvide(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvide *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_IncidentDetectionVideoFileInfoProvide(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvide *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_IncidentDetectionVideoFileInfoProvide(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_IncidentDetectionVideoFileInfoProvide(value)) < 0) return ret;
	return ret;
}

/********************************************************
*ControlStateInfo                                       *
********************************************************/
int ASN1_GET_ControlStateInfo_cpu(ASN1WorkSpace *workspace, ControlStateInfo *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->cpu, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_ControlStateInfo_ram(ASN1WorkSpace *workspace, ControlStateInfo *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->ram, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_ControlStateInfo_disk(ASN1WorkSpace *workspace, ControlStateInfo *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->disk, user_value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_ControlStateInfo(ControlStateInfo *value)
{
	int ret = 0;

	unsigned char checkinfo_cpu[] = {
		0x02,0x01,0x64,0x00
	};
	unsigned char checkinfo_ram[] = {
		0x02,0x01,0x64,0x00
	};
	unsigned char checkinfo_disk[] = {
		0x02,0x01,0x64,0x00
	};

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(&(value->cpu), checkinfo_cpu)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->ram), checkinfo_ram)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->disk), checkinfo_disk)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_ControlStateInfo(ASN1WorkSpace *workspace, ControlStateInfo *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->cpu), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->ram), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|2)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->disk), ASN1IMPL)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_ControlStateInfo(ControlStateInfo *value);
extern int ASN1_BER_Data_Enc_ControlStateInfo(ASN1WorkSpace *workspace, ControlStateInfo *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_ControlStateInfo(ASN1WorkSpace *workspace, ControlStateInfo *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_ControlStateInfo(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_ControlStateInfo(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_ControlStateInfo(ASN1WorkSpace *workspace, ControlStateInfo *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8 *_cpointer;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace,&_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->cpu, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->ram, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|2)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->disk, len, ASN1IMPL)) < 0) return ret;

	ASN1_Dec_Seq_EXT_UNKnow(workspace,_cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_ControlStateInfo(ControlStateInfo *value);
extern int ASN1_BER_Data_Dec_ControlStateInfo(ASN1WorkSpace *workspace, ControlStateInfo *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_ControlStateInfo(ASN1WorkSpace *workspace, ControlStateInfo *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_ControlStateInfo(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_ControlStateInfo(value)) < 0) return ret;
	return ret;
}

/********************************************************
*SensorStateInfo_state                                  *
********************************************************/
int ASN1_CHECK_SensorStateInfo_state(SensorStateInfo_state *value)
{
	unsigned char checkinfo_SensorStateInfo_state[] = {
		0x02,0x00,0x01,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)value, checkinfo_SensorStateInfo_state)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_SensorStateInfo_state(ASN1WorkSpace *workspace, SensorStateInfo_state *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_SensorStateInfo_state(ASN1WorkSpace *workspace, SensorStateInfo_state *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_SensorStateInfo_state(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SensorStateInfo_state(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_SensorStateInfo_state(ASN1WorkSpace *workspace, SensorStateInfo_state *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_SensorStateInfo_state(ASN1WorkSpace *workspace, SensorStateInfo_state *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SensorStateInfo_state(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_SensorStateInfo_state(value)) < 0) return ret;
	return ret;
}

/********************************************************
*SensorStateInfo                                        *
********************************************************/
int ASN1_GET_SensorStateInfo_msm(ASN1WorkSpace *workspace, SensorStateInfo *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->msm, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_SensorStateInfo_txb(ASN1WorkSpace *workspace, SensorStateInfo *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->txb, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_SensorStateInfo_rxb(ASN1WorkSpace *workspace, SensorStateInfo *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->rxb, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_SensorStateInfo_pwr(ASN1WorkSpace *workspace, SensorStateInfo *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->pwr, user_value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_SensorStateInfo(SensorStateInfo *value)
{
	int ret = 0;

	unsigned char checkinfo_msm[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_txb[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_rxb[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_pwr[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->msm), checkinfo_msm)) < 0) return ret;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->txb), checkinfo_txb)) < 0) return ret;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->rxb), checkinfo_rxb)) < 0) return ret;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->pwr), checkinfo_pwr)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Enc_SensorStateInfo_state(ASN1WorkSpace *workspace, SensorStateInfo_state *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_SensorStateInfo_state(ASN1WorkSpace *workspace, SensorStateInfo_state *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_SensorStateInfo_state(ASN1WorkSpace *workspace, SensorStateInfo_state *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_SensorStateInfo_state(ASN1WorkSpace *workspace, SensorStateInfo_state *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_SensorStateInfo(ASN1WorkSpace *workspace, SensorStateInfo *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SensorStateInfo_state(workspace, &(value->msm), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SensorStateInfo_state(workspace, &(value->txb), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|2)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SensorStateInfo_state(workspace, &(value->rxb), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|3)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SensorStateInfo_state(workspace, &(value->pwr), ASN1IMPL)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_SensorStateInfo(SensorStateInfo *value);
extern int ASN1_BER_Data_Enc_SensorStateInfo(ASN1WorkSpace *workspace, SensorStateInfo *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_SensorStateInfo(ASN1WorkSpace *workspace, SensorStateInfo *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_SensorStateInfo(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SensorStateInfo(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_SensorStateInfo_state(ASN1WorkSpace *workspace, SensorStateInfo_state *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_SensorStateInfo_state(ASN1WorkSpace *workspace, SensorStateInfo_state *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_SensorStateInfo_state(ASN1WorkSpace *workspace, SensorStateInfo_state *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_SensorStateInfo_state(ASN1WorkSpace *workspace, SensorStateInfo_state *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_SensorStateInfo(ASN1WorkSpace *workspace, SensorStateInfo *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8 *_cpointer;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace,&_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SensorStateInfo_state(workspace, &value->msm, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SensorStateInfo_state(workspace, &value->txb, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|2)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SensorStateInfo_state(workspace, &value->rxb, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|3)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SensorStateInfo_state(workspace, &value->pwr, len, ASN1IMPL)) < 0) return ret;

	ASN1_Dec_Seq_EXT_UNKnow(workspace,_cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_SensorStateInfo(SensorStateInfo *value);
extern int ASN1_BER_Data_Dec_SensorStateInfo(ASN1WorkSpace *workspace, SensorStateInfo *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_SensorStateInfo(ASN1WorkSpace *workspace, SensorStateInfo *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SensorStateInfo(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_SensorStateInfo(value)) < 0) return ret;
	return ret;
}

/********************************************************
*Novelty                                                *
********************************************************/
int ASN1_CHECK_Novelty(Novelty *value)
{
	unsigned char checkinfo_Novelty[] = {
		0x02,0x00,0x01,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)value, checkinfo_Novelty)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_Novelty(ASN1WorkSpace *workspace, Novelty *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_Novelty(ASN1WorkSpace *workspace, Novelty *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_Novelty(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Novelty(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_Novelty(ASN1WorkSpace *workspace, Novelty *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_Novelty(ASN1WorkSpace *workspace, Novelty *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Novelty(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_Novelty(value)) < 0) return ret;
	return ret;
}

/********************************************************
*MovingObject_objectType                                *
********************************************************/
int ASN1_CHECK_MovingObject_objectType(MovingObject_objectType *value)
{
	unsigned char checkinfo_MovingObject_objectType[] = {
		0x03,0x00,0x01,0x02,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)value, checkinfo_MovingObject_objectType)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_MovingObject_objectType(ASN1WorkSpace *workspace, MovingObject_objectType *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_MovingObject_objectType(ASN1WorkSpace *workspace, MovingObject_objectType *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_MovingObject_objectType(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_MovingObject_objectType(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_MovingObject_objectType(ASN1WorkSpace *workspace, MovingObject_objectType *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_MovingObject_objectType(ASN1WorkSpace *workspace, MovingObject_objectType *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_MovingObject_objectType(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_MovingObject_objectType(value)) < 0) return ret;
	return ret;
}

/********************************************************
*MovingObject                                           *
********************************************************/
int ASN1_GET_MovingObject_objectType(ASN1WorkSpace *workspace, MovingObject *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->objectType, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_MovingObject_objectID(ASN1WorkSpace *workspace, MovingObject *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->objectID, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_MovingObject_novelty(ASN1WorkSpace *workspace, MovingObject *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_MovingObject_novelty == 1)
	{
		if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->novelty, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_MovingObject_reliability(ASN1WorkSpace *workspace, MovingObject *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->reliability, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_MovingObject_fullPositionVector(ASN1WorkSpace *workspace, MovingObject *value, FullPositionVector_00100 **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = value->fullPositionVector;
	return ret;
}
extern int ASN1_CHECK_FullPositionVector_00100(FullPositionVector_00100 *value);
int ASN1_CHECK_MovingObject(MovingObject *value)
{
	int ret = 0;

	unsigned char checkinfo_objectType[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_objectID[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_novelty[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_reliability[] = {
		0x02,0x00,0x64,0x00
	};
	unsigned char checkinfo_fullPositionVector[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->objectType), checkinfo_objectType)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->objectID), checkinfo_objectID)) < 0) return ret;
	if (value->DEF_MovingObject_novelty == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->novelty), checkinfo_novelty)) < 0) return ret;
	} /* OPTIONAL end */
	if ((ret = ASN1_CHECK_INTEGER(&(value->reliability), checkinfo_reliability)) < 0) return ret;
	if ((ret = ASN1_CHECK_FullPositionVector_00100(value->fullPositionVector)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Enc_MovingObject_objectType(ASN1WorkSpace *workspace, MovingObject_objectType *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_ObjectID_00100(ASN1WorkSpace *workspace, ObjectID_00100 *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_Novelty(ASN1WorkSpace *workspace, Novelty *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_FullPositionVector_00100(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_MovingObject(ASN1WorkSpace *workspace, MovingObject *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_MovingObject_objectType(workspace, &(value->objectType), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_ObjectID_00100(workspace, &(value->objectID), ASN1IMPL)) < 0) return ret;
	if (value->DEF_MovingObject_novelty == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|2)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_Novelty(workspace, &(value->novelty), ASN1IMPL)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_PRIM|3)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->reliability), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT|ITS_ASN_CONS|4)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_FullPositionVector_00100(workspace, value->fullPositionVector, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_MovingObject(MovingObject *value);
extern int ASN1_BER_Data_Enc_MovingObject(ASN1WorkSpace *workspace, MovingObject *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_MovingObject(ASN1WorkSpace *workspace, MovingObject *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_MovingObject(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_MovingObject(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_MovingObject_objectType(ASN1WorkSpace *workspace, MovingObject_objectType *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_ObjectID_00100(ASN1WorkSpace *workspace, ObjectID_00100 *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_Novelty(ASN1WorkSpace *workspace, Novelty *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_FullPositionVector_00100(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_MovingObject(ASN1WorkSpace *workspace, MovingObject *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	ASNUINT8 *_cpointer;
	value->fullPositionVector = (FullPositionVector_00100 *)mpool_malloc(workspace->Pmemory, sizeof(FullPositionVector_00100));
	memset(value->fullPositionVector, 0, sizeof(FullPositionVector_00100));

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace,&_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_MovingObject_objectType(workspace, &value->objectType, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_ObjectID_00100(workspace, &value->objectID, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace,&tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT|ITS_ASN_PRIM|2))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|2)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_Novelty(workspace, &value->novelty, len, ASN1IMPL)) < 0) return ret;

		value->DEF_MovingObject_novelty = 1;
	}
	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_PRIM|3)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->reliability, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_CONT|ITS_ASN_CONS|4)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace,&len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_FullPositionVector_00100(workspace, value->fullPositionVector, len, ASN1IMPL)) < 0) return ret;

	if (IfFixedLength(len) == -1)
	{
		if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
	}
	ASN1_Dec_Seq_EXT_UNKnow(workspace,_cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_MovingObject(MovingObject *value);
extern int ASN1_BER_Data_Dec_MovingObject(ASN1WorkSpace *workspace, MovingObject *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_MovingObject(ASN1WorkSpace *workspace, MovingObject *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_MovingObject(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_MovingObject(value)) < 0) return ret;
	return ret;
}

/********************************************************
*IncidentDetectionInfoResponse                          *
********************************************************/
int ASN1_GET_IncidentDetectionInfoResponse_IncidentDetectionInfoResponse_pdata(ASN1WorkSpace *workspace, IncidentDetectionInfoResponse *value, IncidentDetectionInfo **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = ASN1_Get_Node(value);
	return ret;
}
extern int ASN1_CHECK_IncidentDetectionInfo(IncidentDetectionInfo *value);
int ASN1_CHECK_IncidentDetectionInfoResponse(IncidentDetectionInfoResponse *value)
{
	int ret = 0;

	unsigned char checkinfo_IncidentDetectionInfoResponse[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_IncidentDetectionInfoResponse_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		if ((ret = ASN1_CHECK_IncidentDetectionInfo(pnode->data)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_IncidentDetectionInfo(ASN1WorkSpace *workspace, IncidentDetectionInfo *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_IncidentDetectionInfoResponse(ASN1WorkSpace *workspace, IncidentDetectionInfoResponse *value, ASN1TagType tagFlag)
{
	int ret = 0;
	ASN1ListNode *pnode;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
	}
	pnode = value->head->next;
	while (NULL != pnode)
	{
		if ((ret = ASN1_BER_Data_Enc_IncidentDetectionInfo(workspace, pnode->data, ASN1EXPL)) < 0) return ret;
		pnode = pnode->next;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_IncidentDetectionInfoResponse(IncidentDetectionInfoResponse *value);
extern int ASN1_BER_Data_Enc_IncidentDetectionInfoResponse(ASN1WorkSpace *workspace, IncidentDetectionInfoResponse *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_IncidentDetectionInfoResponse(ASN1WorkSpace *workspace, IncidentDetectionInfoResponse *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_IncidentDetectionInfoResponse(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_IncidentDetectionInfoResponse(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_IncidentDetectionInfo(ASN1WorkSpace *workspace, IncidentDetectionInfo *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_IncidentDetectionInfoResponse(ASN1WorkSpace *workspace, IncidentDetectionInfoResponse *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	IncidentDetectionInfo *pdata;
	ASNUINT8 *p = workspace->buffer.current;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	if ((ret = ASN1_Creat_Init_List(workspace, value)) < 0) return ret;
	while (ASN1_BER_Dec_Isloop(workspace, p, length))
	{
				pdata = (IncidentDetectionInfo *)mpool_malloc(GetMemPool(workspace), sizeof(IncidentDetectionInfo));
		memset(pdata, 0, sizeof(IncidentDetectionInfo));
		if ((ret = ASN1_BER_Data_Dec_IncidentDetectionInfo(workspace, pdata, len, ASN1EXPL)) < 0) return ret;

		if ((ret = ASN1_Insert_Node(workspace, value,(void*)pdata)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_IncidentDetectionInfoResponse(IncidentDetectionInfoResponse *value);
extern int ASN1_BER_Data_Dec_IncidentDetectionInfoResponse(ASN1WorkSpace *workspace, IncidentDetectionInfoResponse *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_IncidentDetectionInfoResponse(ASN1WorkSpace *workspace, IncidentDetectionInfoResponse *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_IncidentDetectionInfoResponse(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_IncidentDetectionInfoResponse(value)) < 0) return ret;
	return ret;
}

/********************************************************
*IncidentTerminationInfoResponse                        *
********************************************************/
int ASN1_GET_IncidentTerminationInfoResponse_IncidentTerminationInfoResponse_pdata(ASN1WorkSpace *workspace, IncidentTerminationInfoResponse *value, IncidentTerminationInfo **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = ASN1_Get_Node(value);
	return ret;
}
extern int ASN1_CHECK_IncidentTerminationInfo(IncidentTerminationInfo *value);
int ASN1_CHECK_IncidentTerminationInfoResponse(IncidentTerminationInfoResponse *value)
{
	int ret = 0;

	unsigned char checkinfo_IncidentTerminationInfoResponse[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_IncidentTerminationInfoResponse_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		if ((ret = ASN1_CHECK_IncidentTerminationInfo(pnode->data)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_IncidentTerminationInfo(ASN1WorkSpace *workspace, IncidentTerminationInfo *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_IncidentTerminationInfoResponse(ASN1WorkSpace *workspace, IncidentTerminationInfoResponse *value, ASN1TagType tagFlag)
{
	int ret = 0;
	ASN1ListNode *pnode;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
	}
	pnode = value->head->next;
	while (NULL != pnode)
	{
		if ((ret = ASN1_BER_Data_Enc_IncidentTerminationInfo(workspace, pnode->data, ASN1EXPL)) < 0) return ret;
		pnode = pnode->next;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_IncidentTerminationInfoResponse(IncidentTerminationInfoResponse *value);
extern int ASN1_BER_Data_Enc_IncidentTerminationInfoResponse(ASN1WorkSpace *workspace, IncidentTerminationInfoResponse *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_IncidentTerminationInfoResponse(ASN1WorkSpace *workspace, IncidentTerminationInfoResponse *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_IncidentTerminationInfoResponse(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_IncidentTerminationInfoResponse(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_IncidentTerminationInfo(ASN1WorkSpace *workspace, IncidentTerminationInfo *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_IncidentTerminationInfoResponse(ASN1WorkSpace *workspace, IncidentTerminationInfoResponse *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	IncidentTerminationInfo *pdata;
	ASNUINT8 *p = workspace->buffer.current;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	if ((ret = ASN1_Creat_Init_List(workspace, value)) < 0) return ret;
	while (ASN1_BER_Dec_Isloop(workspace, p, length))
	{
				pdata = (IncidentTerminationInfo *)mpool_malloc(GetMemPool(workspace), sizeof(IncidentTerminationInfo));
		memset(pdata, 0, sizeof(IncidentTerminationInfo));
		if ((ret = ASN1_BER_Data_Dec_IncidentTerminationInfo(workspace, pdata, len, ASN1EXPL)) < 0) return ret;

		if ((ret = ASN1_Insert_Node(workspace, value,(void*)pdata)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_IncidentTerminationInfoResponse(IncidentTerminationInfoResponse *value);
extern int ASN1_BER_Data_Dec_IncidentTerminationInfoResponse(ASN1WorkSpace *workspace, IncidentTerminationInfoResponse *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_IncidentTerminationInfoResponse(ASN1WorkSpace *workspace, IncidentTerminationInfoResponse *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_IncidentTerminationInfoResponse(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_IncidentTerminationInfoResponse(value)) < 0) return ret;
	return ret;
}

/********************************************************
*IncidentDetectionVideoFileInfoProvideResponse          *
********************************************************/
int ASN1_GET_IncidentDetectionVideoFileInfoProvideResponse_IncidentDetectionVideoFileInfoProvideResponse_pdata(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvideResponse *value, IncidentDetectionVideoFileInfoProvide **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = ASN1_Get_Node(value);
	return ret;
}
extern int ASN1_CHECK_IncidentDetectionVideoFileInfoProvide(IncidentDetectionVideoFileInfoProvide *value);
int ASN1_CHECK_IncidentDetectionVideoFileInfoProvideResponse(IncidentDetectionVideoFileInfoProvideResponse *value)
{
	int ret = 0;

	unsigned char checkinfo_IncidentDetectionVideoFileInfoProvideResponse[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_IncidentDetectionVideoFileInfoProvideResponse_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		if ((ret = ASN1_CHECK_IncidentDetectionVideoFileInfoProvide(pnode->data)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_IncidentDetectionVideoFileInfoProvide(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvide *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_IncidentDetectionVideoFileInfoProvideResponse(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvideResponse *value, ASN1TagType tagFlag)
{
	int ret = 0;
	ASN1ListNode *pnode;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
	}
	pnode = value->head->next;
	while (NULL != pnode)
	{
		if ((ret = ASN1_BER_Data_Enc_IncidentDetectionVideoFileInfoProvide(workspace, pnode->data, ASN1EXPL)) < 0) return ret;
		pnode = pnode->next;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_IncidentDetectionVideoFileInfoProvideResponse(IncidentDetectionVideoFileInfoProvideResponse *value);
extern int ASN1_BER_Data_Enc_IncidentDetectionVideoFileInfoProvideResponse(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvideResponse *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_IncidentDetectionVideoFileInfoProvideResponse(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvideResponse *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_IncidentDetectionVideoFileInfoProvideResponse(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_IncidentDetectionVideoFileInfoProvideResponse(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_IncidentDetectionVideoFileInfoProvide(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvide *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_IncidentDetectionVideoFileInfoProvideResponse(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvideResponse *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	IncidentDetectionVideoFileInfoProvide *pdata;
	ASNUINT8 *p = workspace->buffer.current;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	if ((ret = ASN1_Creat_Init_List(workspace, value)) < 0) return ret;
	while (ASN1_BER_Dec_Isloop(workspace, p, length))
	{
				pdata = (IncidentDetectionVideoFileInfoProvide *)mpool_malloc(GetMemPool(workspace), sizeof(IncidentDetectionVideoFileInfoProvide));
		memset(pdata, 0, sizeof(IncidentDetectionVideoFileInfoProvide));
		if ((ret = ASN1_BER_Data_Dec_IncidentDetectionVideoFileInfoProvide(workspace, pdata, len, ASN1EXPL)) < 0) return ret;

		if ((ret = ASN1_Insert_Node(workspace, value,(void*)pdata)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_IncidentDetectionVideoFileInfoProvideResponse(IncidentDetectionVideoFileInfoProvideResponse *value);
extern int ASN1_BER_Data_Dec_IncidentDetectionVideoFileInfoProvideResponse(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvideResponse *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_IncidentDetectionVideoFileInfoProvideResponse(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvideResponse *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_IncidentDetectionVideoFileInfoProvideResponse(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_IncidentDetectionVideoFileInfoProvideResponse(value)) < 0) return ret;
	return ret;
}

/********************************************************
*ControlStateInfoResponse                               *
********************************************************/
int ASN1_GET_ControlStateInfoResponse_ControlStateInfoResponse_pdata(ASN1WorkSpace *workspace, ControlStateInfoResponse *value, ControlStateInfo **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = ASN1_Get_Node(value);
	return ret;
}
extern int ASN1_CHECK_ControlStateInfo(ControlStateInfo *value);
int ASN1_CHECK_ControlStateInfoResponse(ControlStateInfoResponse *value)
{
	int ret = 0;

	unsigned char checkinfo_ControlStateInfoResponse[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_ControlStateInfoResponse_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		if ((ret = ASN1_CHECK_ControlStateInfo(pnode->data)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_ControlStateInfo(ASN1WorkSpace *workspace, ControlStateInfo *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_ControlStateInfoResponse(ASN1WorkSpace *workspace, ControlStateInfoResponse *value, ASN1TagType tagFlag)
{
	int ret = 0;
	ASN1ListNode *pnode;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
	}
	pnode = value->head->next;
	while (NULL != pnode)
	{
		if ((ret = ASN1_BER_Data_Enc_ControlStateInfo(workspace, pnode->data, ASN1EXPL)) < 0) return ret;
		pnode = pnode->next;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_ControlStateInfoResponse(ControlStateInfoResponse *value);
extern int ASN1_BER_Data_Enc_ControlStateInfoResponse(ASN1WorkSpace *workspace, ControlStateInfoResponse *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_ControlStateInfoResponse(ASN1WorkSpace *workspace, ControlStateInfoResponse *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_ControlStateInfoResponse(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_ControlStateInfoResponse(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_ControlStateInfo(ASN1WorkSpace *workspace, ControlStateInfo *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_ControlStateInfoResponse(ASN1WorkSpace *workspace, ControlStateInfoResponse *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ControlStateInfo *pdata;
	ASNUINT8 *p = workspace->buffer.current;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	if ((ret = ASN1_Creat_Init_List(workspace, value)) < 0) return ret;
	while (ASN1_BER_Dec_Isloop(workspace, p, length))
	{
				pdata = (ControlStateInfo *)mpool_malloc(GetMemPool(workspace), sizeof(ControlStateInfo));
		memset(pdata, 0, sizeof(ControlStateInfo));
		if ((ret = ASN1_BER_Data_Dec_ControlStateInfo(workspace, pdata, len, ASN1EXPL)) < 0) return ret;

		if ((ret = ASN1_Insert_Node(workspace, value,(void*)pdata)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_ControlStateInfoResponse(ControlStateInfoResponse *value);
extern int ASN1_BER_Data_Dec_ControlStateInfoResponse(ASN1WorkSpace *workspace, ControlStateInfoResponse *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_ControlStateInfoResponse(ASN1WorkSpace *workspace, ControlStateInfoResponse *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_ControlStateInfoResponse(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_ControlStateInfoResponse(value)) < 0) return ret;
	return ret;
}

/********************************************************
*SensorStateInfoResponse                                *
********************************************************/
int ASN1_GET_SensorStateInfoResponse_SensorStateInfoResponse_pdata(ASN1WorkSpace *workspace, SensorStateInfoResponse *value, SensorStateInfo **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = ASN1_Get_Node(value);
	return ret;
}
extern int ASN1_CHECK_SensorStateInfo(SensorStateInfo *value);
int ASN1_CHECK_SensorStateInfoResponse(SensorStateInfoResponse *value)
{
	int ret = 0;

	unsigned char checkinfo_SensorStateInfoResponse[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_SensorStateInfoResponse_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		if ((ret = ASN1_CHECK_SensorStateInfo(pnode->data)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_SensorStateInfo(ASN1WorkSpace *workspace, SensorStateInfo *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_SensorStateInfoResponse(ASN1WorkSpace *workspace, SensorStateInfoResponse *value, ASN1TagType tagFlag)
{
	int ret = 0;
	ASN1ListNode *pnode;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
	}
	pnode = value->head->next;
	while (NULL != pnode)
	{
		if ((ret = ASN1_BER_Data_Enc_SensorStateInfo(workspace, pnode->data, ASN1EXPL)) < 0) return ret;
		pnode = pnode->next;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_SensorStateInfoResponse(SensorStateInfoResponse *value);
extern int ASN1_BER_Data_Enc_SensorStateInfoResponse(ASN1WorkSpace *workspace, SensorStateInfoResponse *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_SensorStateInfoResponse(ASN1WorkSpace *workspace, SensorStateInfoResponse *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_SensorStateInfoResponse(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SensorStateInfoResponse(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_SensorStateInfo(ASN1WorkSpace *workspace, SensorStateInfo *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_SensorStateInfoResponse(ASN1WorkSpace *workspace, SensorStateInfoResponse *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	SensorStateInfo *pdata;
	ASNUINT8 *p = workspace->buffer.current;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	if ((ret = ASN1_Creat_Init_List(workspace, value)) < 0) return ret;
	while (ASN1_BER_Dec_Isloop(workspace, p, length))
	{
				pdata = (SensorStateInfo *)mpool_malloc(GetMemPool(workspace), sizeof(SensorStateInfo));
		memset(pdata, 0, sizeof(SensorStateInfo));
		if ((ret = ASN1_BER_Data_Dec_SensorStateInfo(workspace, pdata, len, ASN1EXPL)) < 0) return ret;

		if ((ret = ASN1_Insert_Node(workspace, value,(void*)pdata)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_SensorStateInfoResponse(SensorStateInfoResponse *value);
extern int ASN1_BER_Data_Dec_SensorStateInfoResponse(ASN1WorkSpace *workspace, SensorStateInfoResponse *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_SensorStateInfoResponse(ASN1WorkSpace *workspace, SensorStateInfoResponse *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SensorStateInfoResponse(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_SensorStateInfoResponse(value)) < 0) return ret;
	return ret;
}

/********************************************************
*MovingObjectResponse                                   *
********************************************************/
int ASN1_GET_MovingObjectResponse_MovingObjectResponse_pdata(ASN1WorkSpace *workspace, MovingObjectResponse *value, MovingObject **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = ASN1_Get_Node(value);
	return ret;
}
extern int ASN1_CHECK_MovingObject(MovingObject *value);
int ASN1_CHECK_MovingObjectResponse(MovingObjectResponse *value)
{
	int ret = 0;

	unsigned char checkinfo_MovingObjectResponse[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_MovingObjectResponse_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		if ((ret = ASN1_CHECK_MovingObject(pnode->data)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_MovingObject(ASN1WorkSpace *workspace, MovingObject *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_MovingObjectResponse(ASN1WorkSpace *workspace, MovingObjectResponse *value, ASN1TagType tagFlag)
{
	int ret = 0;
	ASN1ListNode *pnode;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
	}
	pnode = value->head->next;
	while (NULL != pnode)
	{
		if ((ret = ASN1_BER_Data_Enc_MovingObject(workspace, pnode->data, ASN1EXPL)) < 0) return ret;
		pnode = pnode->next;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_MovingObjectResponse(MovingObjectResponse *value);
extern int ASN1_BER_Data_Enc_MovingObjectResponse(ASN1WorkSpace *workspace, MovingObjectResponse *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_MovingObjectResponse(ASN1WorkSpace *workspace, MovingObjectResponse *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_MovingObjectResponse(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_MovingObjectResponse(workspace,value,tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_MovingObject(ASN1WorkSpace *workspace, MovingObject *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_MovingObjectResponse(ASN1WorkSpace *workspace, MovingObjectResponse *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	MovingObject *pdata;
	ASNUINT8 *p = workspace->buffer.current;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	if ((ret = ASN1_Creat_Init_List(workspace, value)) < 0) return ret;
	while (ASN1_BER_Dec_Isloop(workspace, p, length))
	{
				pdata = (MovingObject *)mpool_malloc(GetMemPool(workspace), sizeof(MovingObject));
		memset(pdata, 0, sizeof(MovingObject));
		if ((ret = ASN1_BER_Data_Dec_MovingObject(workspace, pdata, len, ASN1EXPL)) < 0) return ret;

		if ((ret = ASN1_Insert_Node(workspace, value,(void*)pdata)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_MovingObjectResponse(MovingObjectResponse *value);
extern int ASN1_BER_Data_Dec_MovingObjectResponse(ASN1WorkSpace *workspace, MovingObjectResponse *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_MovingObjectResponse(ASN1WorkSpace *workspace, MovingObjectResponse *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_MovingObjectResponse(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_MovingObjectResponse(value)) < 0) return ret;
	return ret;
}


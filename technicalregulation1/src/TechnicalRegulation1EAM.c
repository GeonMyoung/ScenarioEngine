#include "TechnicalRegulation1Eam.h"

/********************************************************
*CurrentLinkState                                       *
********************************************************/
int ASN1_Print_CurrentLinkState(CurrentLinkState* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("CurrentLinkState");
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("link-LinkIdNumber", &(value->link_LinkIdNumber))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("link-SpeedRate", &(value->link_SpeedRate))) < 0) return ret;
	if (value->DEF_CurrentLinkState_link_VolumeRate == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("link-VolumeRate", &(value->link_VolumeRate))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_CurrentLinkState_link_DensityRate == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("link-DensityRate", &(value->link_DensityRate))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_CurrentLinkState_link_TravelTimeQuantity == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("link-TravelTimeQuantity", &(value->link_TravelTimeQuantity))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_CurrentLinkState_link_DelayQuantity == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("link-DelayQuantity", &(value->link_DelayQuantity))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_CurrentLinkState_tfdt_VehicleQueueLengthQuantity == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("tfdt-VehicleQueueLengthQuantity", &(value->tfdt_VehicleQueueLengthQuantity))) < 0) return ret;
	} /* OPTIONAL end */
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("tfdt-OccupancyPercent", &(value->tfdt_OccupancyPercent))) < 0) return ret;
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_CurrentLinkState_link_LinkIdNumber(ASN1WorkSpace* workspace, CurrentLinkState* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->link_LinkIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_CurrentLinkState_link_SpeedRate(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->link_SpeedRate, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_CurrentLinkState_link_VolumeRate(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_CurrentLinkState_link_VolumeRate = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->link_VolumeRate, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_CurrentLinkState_link_DensityRate(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_CurrentLinkState_link_DensityRate = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->link_DensityRate, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_CurrentLinkState_link_TravelTimeQuantity(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_CurrentLinkState_link_TravelTimeQuantity = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->link_TravelTimeQuantity, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_CurrentLinkState_link_DelayQuantity(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_CurrentLinkState_link_DelayQuantity = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->link_DelayQuantity, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_CurrentLinkState_tfdt_VehicleQueueLengthQuantity(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_CurrentLinkState_tfdt_VehicleQueueLengthQuantity = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->tfdt_VehicleQueueLengthQuantity, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_CurrentLinkState_tfdt_OccupancyPercent(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->tfdt_OccupancyPercent, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_CurrentLinkState_link_LinkIdNumber(ASN1WorkSpace* workspace, CurrentLinkState* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->link_LinkIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_CurrentLinkState_link_SpeedRate(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->link_SpeedRate, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_CurrentLinkState_link_VolumeRate(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_CurrentLinkState_link_VolumeRate == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->link_VolumeRate, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_CurrentLinkState_link_DensityRate(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_CurrentLinkState_link_DensityRate == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->link_DensityRate, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_CurrentLinkState_link_TravelTimeQuantity(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_CurrentLinkState_link_TravelTimeQuantity == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->link_TravelTimeQuantity, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_CurrentLinkState_link_DelayQuantity(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_CurrentLinkState_link_DelayQuantity == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->link_DelayQuantity, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_CurrentLinkState_tfdt_VehicleQueueLengthQuantity(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_CurrentLinkState_tfdt_VehicleQueueLengthQuantity == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->tfdt_VehicleQueueLengthQuantity, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_CurrentLinkState_tfdt_OccupancyPercent(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->tfdt_OccupancyPercent, user_value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_CurrentLinkState(CurrentLinkState* value)
{
	int ret = 0;

	unsigned char checkinfo_link_LinkIdNumber[] = {
		0x02,0x01,0x28,0x00
	};
	unsigned char checkinfo_link_SpeedRate[] = {
		0x02,0x00,0x82,0x01,0x2C,0x00
	};
	unsigned char checkinfo_link_VolumeRate[] = {
		0x02,0x00,0x83,0x01,0x86,0xA0,0x00
	};
	unsigned char checkinfo_link_DensityRate[] = {
		0x02,0x00,0x82,0x07,0xD0,0x00
	};
	unsigned char checkinfo_link_TravelTimeQuantity[] = {
		0x02,0x00,0x82,0x2A,0x30,0x00
	};
	unsigned char checkinfo_link_DelayQuantity[] = {
		0x02,0x00,0x82,0x2E,0xE0,0x00
	};
	unsigned char checkinfo_tfdt_VehicleQueueLengthQuantity[] = {
		0x02,0x00,0x83,0x07,0xA1,0x20,0x00
	};
	unsigned char checkinfo_tfdt_OccupancyPercent[] = {
		0x02,0x00,0x64,0x00
	};

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_UTF8Str(&(value->link_LinkIdNumber), checkinfo_link_LinkIdNumber)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->link_SpeedRate), checkinfo_link_SpeedRate)) < 0) return ret;
	if (value->DEF_CurrentLinkState_link_VolumeRate == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->link_VolumeRate), checkinfo_link_VolumeRate)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_CurrentLinkState_link_DensityRate == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->link_DensityRate), checkinfo_link_DensityRate)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_CurrentLinkState_link_TravelTimeQuantity == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->link_TravelTimeQuantity), checkinfo_link_TravelTimeQuantity)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_CurrentLinkState_link_DelayQuantity == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->link_DelayQuantity), checkinfo_link_DelayQuantity)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_CurrentLinkState_tfdt_VehicleQueueLengthQuantity == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->tfdt_VehicleQueueLengthQuantity), checkinfo_tfdt_VehicleQueueLengthQuantity)) < 0) return ret;
	} /* OPTIONAL end */
	if ((ret = ASN1_CHECK_INTEGER(&(value->tfdt_OccupancyPercent), checkinfo_tfdt_OccupancyPercent)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_CurrentLinkState(ASN1WorkSpace* workspace, CurrentLinkState* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->link_LinkIdNumber), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->link_SpeedRate), ASN1IMPL)) < 0) return ret;
	if (value->DEF_CurrentLinkState_link_VolumeRate == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->link_VolumeRate), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_CurrentLinkState_link_DensityRate == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->link_DensityRate), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_CurrentLinkState_link_TravelTimeQuantity == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->link_TravelTimeQuantity), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_CurrentLinkState_link_DelayQuantity == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->link_DelayQuantity), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_CurrentLinkState_tfdt_VehicleQueueLengthQuantity == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 6)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->tfdt_VehicleQueueLengthQuantity), ASN1IMPL)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 7)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->tfdt_OccupancyPercent), ASN1IMPL)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_CurrentLinkState(CurrentLinkState* value);
extern int ASN1_BER_Data_Enc_CurrentLinkState(ASN1WorkSpace* workspace, CurrentLinkState* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_CurrentLinkState(ASN1WorkSpace* workspace, CurrentLinkState* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_CurrentLinkState(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_CurrentLinkState(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_CurrentLinkState(ASN1WorkSpace* workspace, CurrentLinkState* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	ASNUINT8* _cpointer;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->link_LinkIdNumber, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->link_SpeedRate, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 2))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->link_VolumeRate, len, ASN1IMPL)) < 0) return ret;

		value->DEF_CurrentLinkState_link_VolumeRate = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 3))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->link_DensityRate, len, ASN1IMPL)) < 0) return ret;

		value->DEF_CurrentLinkState_link_DensityRate = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 4))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->link_TravelTimeQuantity, len, ASN1IMPL)) < 0) return ret;

		value->DEF_CurrentLinkState_link_TravelTimeQuantity = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 5))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->link_DelayQuantity, len, ASN1IMPL)) < 0) return ret;

		value->DEF_CurrentLinkState_link_DelayQuantity = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 6))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 6)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->tfdt_VehicleQueueLengthQuantity, len, ASN1IMPL)) < 0) return ret;

		value->DEF_CurrentLinkState_tfdt_VehicleQueueLengthQuantity = 1;
	}
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 7)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->tfdt_OccupancyPercent, len, ASN1IMPL)) < 0) return ret;

	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if (IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_CurrentLinkState(CurrentLinkState* value);
extern int ASN1_BER_Data_Dec_CurrentLinkState(ASN1WorkSpace* workspace, CurrentLinkState* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_CurrentLinkState(ASN1WorkSpace* workspace, CurrentLinkState* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_CurrentLinkState(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_CurrentLinkState(value)) < 0) return ret;
	return ret;
}

/********************************************************
*CurrentLinkStateRequest                                *
********************************************************/
int ASN1_Print_CurrentLinkStateRequest(CurrentLinkStateRequest* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// Type Default
	if ((ret = ASN1_Print_UTF8Str("CurrentLinkStateRequest", value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_CurrentLinkStateRequest(CurrentLinkStateRequest* value)
{
	unsigned char checkinfo_CurrentLinkStateRequest[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_UTF8Str(value, checkinfo_CurrentLinkStateRequest)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_CurrentLinkStateRequest(ASN1WorkSpace* workspace, CurrentLinkStateRequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_CurrentLinkStateRequest(ASN1WorkSpace* workspace, CurrentLinkStateRequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_CurrentLinkStateRequest(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_CurrentLinkStateRequest(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_CurrentLinkStateRequest(ASN1WorkSpace* workspace, CurrentLinkStateRequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_CurrentLinkStateRequest(ASN1WorkSpace* workspace, CurrentLinkStateRequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_CurrentLinkStateRequest(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_CurrentLinkStateRequest(value)) < 0) return ret;
	return ret;
}

/********************************************************
*CurrentLinkStateResponse                               *
********************************************************/
int ASN1_Print_CurrentLinkStateResponse(CurrentLinkStateResponse* value, int tab_value)
{
	int ret = 0;
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	count = value->count;
	pnode = value->head->next;
	// SEQUENCE OF : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ_OF("CurrentLinkStateResponse");
	while (count) {
		// Type Reference CurrentLinkState
		ASN_Print_TAB(tab_value + 1);
		if ((ret = ASN1_Print_CurrentLinkState((CurrentLinkState*)pnode->data, tab_value + 1)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}

	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_CurrentLinkStateResponse_CurrentLinkStateResponse_pdata(ASN1WorkSpace* workspace, CurrentLinkStateResponse* value, CurrentLinkState* user_value)
{
	int ret = 0;
	CurrentLinkState* list_value;
	if (value == NULL || user_value == NULL) return -1;
	list_value = (CurrentLinkState*)mpool_malloc(workspace->Pmemory, sizeof(CurrentLinkState));
	memset(list_value, 0, sizeof(CurrentLinkState));
	memmove(list_value, user_value, sizeof(CurrentLinkState));
	ASN1_Insert_Node(workspace, value, list_value);
	return ret;
}
int ASN1_GET_CurrentLinkStateResponse_CurrentLinkStateResponse_pdata(ASN1WorkSpace* workspace, CurrentLinkStateResponse* value, CurrentLinkState** user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = ASN1_Get_Node(value);
	return ret;
}
extern int ASN1_CHECK_CurrentLinkState(CurrentLinkState* value);
int ASN1_CHECK_CurrentLinkStateResponse(CurrentLinkStateResponse* value)
{
	int ret = 0;

	unsigned char checkinfo_CurrentLinkStateResponse[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_CurrentLinkStateResponse_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		if ((ret = ASN1_CHECK_CurrentLinkState(pnode->data)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_CurrentLinkState(ASN1WorkSpace* workspace, CurrentLinkState* value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_CurrentLinkStateResponse(ASN1WorkSpace* workspace, CurrentLinkStateResponse* value, ASN1TagType tagFlag)
{
	int ret = 0;
	ASN1ListNode* pnode;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	pnode = value->head->next;
	while (NULL != pnode)
	{
		if ((ret = ASN1_BER_Data_Enc_CurrentLinkState(workspace, pnode->data, ASN1EXPL)) < 0) return ret;
		pnode = pnode->next;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_CurrentLinkStateResponse(CurrentLinkStateResponse* value);
extern int ASN1_BER_Data_Enc_CurrentLinkStateResponse(ASN1WorkSpace* workspace, CurrentLinkStateResponse* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_CurrentLinkStateResponse(ASN1WorkSpace* workspace, CurrentLinkStateResponse* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_CurrentLinkStateResponse(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_CurrentLinkStateResponse(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_CurrentLinkState(ASN1WorkSpace* workspace, CurrentLinkState* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_CurrentLinkStateResponse(ASN1WorkSpace* workspace, CurrentLinkStateResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	CurrentLinkState* pdata;
	ASNUINT8* p = workspace->buffer.current;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &length)) < 0) return ret;
	}
	if ((ret = ASN1_Creat_Init_List(workspace, value)) < 0) return ret;
	while (ASN1_BER_Dec_Isloop(workspace, p, length))
	{
		pdata = (CurrentLinkState*)mpool_malloc(GetMemPool(workspace), sizeof(CurrentLinkState));
		memset(pdata, 0, sizeof(CurrentLinkState));
		if ((ret = ASN1_BER_Data_Dec_CurrentLinkState(workspace, pdata, len, ASN1EXPL)) < 0) return ret;

		if ((ret = ASN1_Insert_Node(workspace, value, (void*)pdata)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if (IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_CurrentLinkStateResponse(CurrentLinkStateResponse* value);
extern int ASN1_BER_Data_Dec_CurrentLinkStateResponse(ASN1WorkSpace* workspace, CurrentLinkStateResponse* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_CurrentLinkStateResponse(ASN1WorkSpace* workspace, CurrentLinkStateResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_CurrentLinkStateResponse(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_CurrentLinkStateResponse(value)) < 0) return ret;
	return ret;
}

/********************************************************
*EventIdentity                                          *
********************************************************/
int ASN1_Print_EventIdentity(EventIdentity* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("EventIdentity");
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("node-NodeIdNumber", &(value->node_NodeIdNumber))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("link-LinkIdNumber", &(value->link_LinkIdNumber))) < 0) return ret;
	if (value->DEF_EventIdentity_evnt_IdentificationNumber == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("evnt-IdentificationNumber", &(value->evnt_IdentificationNumber))) < 0) return ret;
	} /* OPTIONAL end */
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("evnt-LocationJurisDictionNameText", &(value->evnt_LocationJurisDictionNameText))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("evnt-LocationLinkIdNumber", &(value->evnt_LocationLinkIdNumber))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("evnt-LocationNodeIdNumber", &(value->evnt_LocationNodeIdNumber))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("evnt-LocationRoadwayNameText", &(value->evnt_LocationRoadwayNameText))) < 0) return ret;
	if (value->DEF_EventIdentity_evnt_DescriptionTypeEventCode == 1)
	{ /*OPTIONAL start */
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		switch (value->evnt_DescriptionTypeEventCode)
		{
		case 0: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeEventCode", "none", 0)) < 0) return ret; break;
		case 1: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeEventCode", "other", 1)) < 0) return ret; break;
		case 2: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeEventCode", "constructions", 2)) < 0) return ret; break;
		case 3: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeEventCode", "planned-roadway-closure", 3)) < 0) return ret; break;
		case 4: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeEventCode", "special-event", 4)) < 0) return ret; break;
		default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
		};
	} /* OPTIONAL end */
	if (value->DEF_EventIdentity_evnt_DescriptionTypeSpecialEventCode == 1)
	{ /*OPTIONAL start */
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		switch (value->evnt_DescriptionTypeSpecialEventCode)
		{
		case 0: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeSpecialEventCode", "none", 0)) < 0) return ret; break;
		case 1: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeSpecialEventCode", "other", 1)) < 0) return ret; break;
		case 2: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeSpecialEventCode", "parade", 2)) < 0) return ret; break;
		case 3: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeSpecialEventCode", "sporting-event", 3)) < 0) return ret; break;
		case 4: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeSpecialEventCode", "demonstration", 4)) < 0) return ret; break;
		case 5: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeSpecialEventCode", "festival", 5)) < 0) return ret; break;
		case 6: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeSpecialEventCode", "performing-arts", 6)) < 0) return ret; break;
		case 7: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeSpecialEventCode", "dignitary-visit", 7)) < 0) return ret; break;
		default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
		};
	} /* OPTIONAL end */
	if (value->DEF_EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode == 1)
	{ /*OPTIONAL start */
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		switch (value->evnt_DescriptionPlannedRoadWayClosureCode)
		{
		case 0: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionPlannedRoadWayClosureCode", "none", 0)) < 0) return ret; break;
		case 1: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionPlannedRoadWayClosureCode", "other", 1)) < 0) return ret; break;
		case 2: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionPlannedRoadWayClosureCode", "long-term-construction", 2)) < 0) return ret; break;
		case 3: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionPlannedRoadWayClosureCode", "short-term-construction", 3)) < 0) return ret; break;
		case 4: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionPlannedRoadWayClosureCode", "maintenance", 4)) < 0) return ret; break;
		case 5: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionPlannedRoadWayClosureCode", "emergency-maintenance", 5)) < 0) return ret; break;
		default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
		};
	} /* OPTIONAL end */
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("evnt-LanesBlockedOrClosedNumber", &(value->evnt_LanesBlockedOrClosedNumber))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_BITSTRING("evnt-LanesShouldersBlockedCode", &(value->evnt_LanesShouldersBlockedCode))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_VisibleString("evnt-TimelineStartGeneralizedTime", &(value->evnt_TimelineStartGeneralizedTime))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_VisibleString("evnt-TimelineEndGeneralizedTime", &(value->evnt_TimelineEndGeneralizedTime))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("evnt-TimelineDurationTime", &(value->evnt_TimelineDurationTime))) < 0) return ret;
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_EventIdentity_node_NodeIdNumber(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->node_NodeIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_EventIdentity_link_LinkIdNumber(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->link_LinkIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_EventIdentity_evnt_IdentificationNumber(ASN1WorkSpace* workspace, EventIdentity* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_EventIdentity_evnt_IdentificationNumber = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->evnt_IdentificationNumber, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_EventIdentity_evnt_LocationJurisDictionNameText(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->evnt_LocationJurisDictionNameText, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_EventIdentity_evnt_LocationLinkIdNumber(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->evnt_LocationLinkIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_EventIdentity_evnt_LocationNodeIdNumber(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->evnt_LocationNodeIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_EventIdentity_evnt_LocationRoadwayNameText(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->evnt_LocationRoadwayNameText, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_EventIdentity_evnt_DescriptionTypeEventCode(ASN1WorkSpace* workspace, EventIdentity* value, ENUMERATED user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_EventIdentity_evnt_DescriptionTypeEventCode = 1;
	if ((ret = ASN1_SET_ENUMERATED(workspace, (ASNINT32*)&value->evnt_DescriptionTypeEventCode, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_EventIdentity_evnt_DescriptionTypeSpecialEventCode(ASN1WorkSpace* workspace, EventIdentity* value, ENUMERATED user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_EventIdentity_evnt_DescriptionTypeSpecialEventCode = 1;
	if ((ret = ASN1_SET_ENUMERATED(workspace, (ASNINT32*)&value->evnt_DescriptionTypeSpecialEventCode, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode(ASN1WorkSpace* workspace, EventIdentity* value, ENUMERATED user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode = 1;
	if ((ret = ASN1_SET_ENUMERATED(workspace, (ASNINT32*)&value->evnt_DescriptionPlannedRoadWayClosureCode, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_EventIdentity_evnt_LanesBlockedOrClosedNumber(ASN1WorkSpace* workspace, EventIdentity* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->evnt_LanesBlockedOrClosedNumber, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_EventIdentity_evnt_LanesShouldersBlockedCode(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8* user_value, ASNUINT32L user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_BITSTRING(workspace, &value->evnt_LanesShouldersBlockedCode, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_EventIdentity_evnt_TimelineStartGeneralizedTime(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_VisibleString(workspace, &value->evnt_TimelineStartGeneralizedTime, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_EventIdentity_evnt_TimelineEndGeneralizedTime(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_VisibleString(workspace, &value->evnt_TimelineEndGeneralizedTime, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_EventIdentity_evnt_TimelineDurationTime(ASN1WorkSpace* workspace, EventIdentity* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->evnt_TimelineDurationTime, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_EventIdentity_node_NodeIdNumber(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->node_NodeIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_EventIdentity_link_LinkIdNumber(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->link_LinkIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_EventIdentity_evnt_IdentificationNumber(ASN1WorkSpace* workspace, EventIdentity* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_EventIdentity_evnt_IdentificationNumber == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->evnt_IdentificationNumber, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_EventIdentity_evnt_LocationJurisDictionNameText(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->evnt_LocationJurisDictionNameText, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_EventIdentity_evnt_LocationLinkIdNumber(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->evnt_LocationLinkIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_EventIdentity_evnt_LocationNodeIdNumber(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->evnt_LocationNodeIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_EventIdentity_evnt_LocationRoadwayNameText(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->evnt_LocationRoadwayNameText, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_EventIdentity_evnt_DescriptionTypeEventCode(ASN1WorkSpace* workspace, EventIdentity* value, ENUMERATED* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_EventIdentity_evnt_DescriptionTypeEventCode == 1)
	{
		if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->evnt_DescriptionTypeEventCode, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_EventIdentity_evnt_DescriptionTypeSpecialEventCode(ASN1WorkSpace* workspace, EventIdentity* value, ENUMERATED* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_EventIdentity_evnt_DescriptionTypeSpecialEventCode == 1)
	{
		if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->evnt_DescriptionTypeSpecialEventCode, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode(ASN1WorkSpace* workspace, EventIdentity* value, ENUMERATED* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode == 1)
	{
		if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->evnt_DescriptionPlannedRoadWayClosureCode, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_EventIdentity_evnt_LanesBlockedOrClosedNumber(ASN1WorkSpace* workspace, EventIdentity* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->evnt_LanesBlockedOrClosedNumber, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_EventIdentity_evnt_LanesShouldersBlockedCode(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8** user_value, ASNUINT32L* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_BITSTRING(workspace, &value->evnt_LanesShouldersBlockedCode, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_EventIdentity_evnt_TimelineStartGeneralizedTime(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_VisibleString(workspace, &value->evnt_TimelineStartGeneralizedTime, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_EventIdentity_evnt_TimelineEndGeneralizedTime(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_VisibleString(workspace, &value->evnt_TimelineEndGeneralizedTime, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_EventIdentity_evnt_TimelineDurationTime(ASN1WorkSpace* workspace, EventIdentity* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->evnt_TimelineDurationTime, user_value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_EventIdentity(EventIdentity* value)
{
	int ret = 0;

	unsigned char checkinfo_node_NodeIdNumber[] = {
		0x02,0x01,0x28,0x00
	};
	unsigned char checkinfo_link_LinkIdNumber[] = {
		0x02,0x01,0x28,0x00
	};
	unsigned char checkinfo_evnt_IdentificationNumber[] = {
		0x02,0x00,0x85,0x00,0xFF,0xFF,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_evnt_LocationJurisDictionNameText[] = {
		0x02,0x01,0x82,0x01,0x00,0x00
	};
	unsigned char checkinfo_evnt_LocationLinkIdNumber[] = {
		0x02,0x01,0x28,0x00
	};
	unsigned char checkinfo_evnt_LocationNodeIdNumber[] = {
		0x02,0x01,0x28,0x00
	};
	unsigned char checkinfo_evnt_LocationRoadwayNameText[] = {
		0x02,0x01,0x82,0x01,0x00,0x00
	};
	unsigned char checkinfo_evnt_DescriptionTypeEventCode[] = {
		0x05,0x00,0x01,0x02,0x03,0x04,0x00
	};
	unsigned char checkinfo_evnt_DescriptionTypeSpecialEventCode[] = {
		0x08,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x00
	};
	unsigned char checkinfo_evnt_DescriptionPlannedRoadWayClosureCode[] = {
		0x06,0x00,0x01,0x02,0x03,0x04,0x05,0x00
	};
	unsigned char checkinfo_evnt_LanesBlockedOrClosedNumber[] = {
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_evnt_LanesShouldersBlockedCode[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_evnt_TimelineStartGeneralizedTime[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_evnt_TimelineEndGeneralizedTime[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_evnt_TimelineDurationTime[] = {
		0x02,0x00,0x85,0x00,0xFF,0xFF,0xFF,0xFF,0x00
	};

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_UTF8Str(&(value->node_NodeIdNumber), checkinfo_node_NodeIdNumber)) < 0) return ret;
	if ((ret = ASN1_CHECK_UTF8Str(&(value->link_LinkIdNumber), checkinfo_link_LinkIdNumber)) < 0) return ret;
	if (value->DEF_EventIdentity_evnt_IdentificationNumber == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->evnt_IdentificationNumber), checkinfo_evnt_IdentificationNumber)) < 0) return ret;
	} /* OPTIONAL end */
	if ((ret = ASN1_CHECK_UTF8Str(&(value->evnt_LocationJurisDictionNameText), checkinfo_evnt_LocationJurisDictionNameText)) < 0) return ret;
	if ((ret = ASN1_CHECK_UTF8Str(&(value->evnt_LocationLinkIdNumber), checkinfo_evnt_LocationLinkIdNumber)) < 0) return ret;
	if ((ret = ASN1_CHECK_UTF8Str(&(value->evnt_LocationNodeIdNumber), checkinfo_evnt_LocationNodeIdNumber)) < 0) return ret;
	if ((ret = ASN1_CHECK_UTF8Str(&(value->evnt_LocationRoadwayNameText), checkinfo_evnt_LocationRoadwayNameText)) < 0) return ret;
	if (value->DEF_EventIdentity_evnt_DescriptionTypeEventCode == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->evnt_DescriptionTypeEventCode), checkinfo_evnt_DescriptionTypeEventCode)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_EventIdentity_evnt_DescriptionTypeSpecialEventCode == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->evnt_DescriptionTypeSpecialEventCode), checkinfo_evnt_DescriptionTypeSpecialEventCode)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->evnt_DescriptionPlannedRoadWayClosureCode), checkinfo_evnt_DescriptionPlannedRoadWayClosureCode)) < 0) return ret;
	} /* OPTIONAL end */
	if ((ret = ASN1_CHECK_INTEGER(&(value->evnt_LanesBlockedOrClosedNumber), checkinfo_evnt_LanesBlockedOrClosedNumber)) < 0) return ret;
	if ((ret = ASN1_CHECK_BITSTRING(&(value->evnt_LanesShouldersBlockedCode), checkinfo_evnt_LanesShouldersBlockedCode)) < 0) return ret;
	if ((ret = ASN1_CHECK_VisibleString(&(value->evnt_TimelineStartGeneralizedTime), checkinfo_evnt_TimelineStartGeneralizedTime)) < 0) return ret;
	if ((ret = ASN1_CHECK_VisibleString(&(value->evnt_TimelineEndGeneralizedTime), checkinfo_evnt_TimelineEndGeneralizedTime)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->evnt_TimelineDurationTime), checkinfo_evnt_TimelineDurationTime)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_EventIdentity(ASN1WorkSpace* workspace, EventIdentity* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->node_NodeIdNumber), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->link_LinkIdNumber), ASN1IMPL)) < 0) return ret;
	if (value->DEF_EventIdentity_evnt_IdentificationNumber == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->evnt_IdentificationNumber), ASN1IMPL)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->evnt_LocationJurisDictionNameText), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->evnt_LocationLinkIdNumber), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->evnt_LocationNodeIdNumber), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 6)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->evnt_LocationRoadwayNameText), ASN1IMPL)) < 0) return ret;
	if (value->DEF_EventIdentity_evnt_DescriptionTypeEventCode == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 7)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32*)&(value->evnt_DescriptionTypeEventCode), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_EventIdentity_evnt_DescriptionTypeSpecialEventCode == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 8)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32*)&(value->evnt_DescriptionTypeSpecialEventCode), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 9)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32*)&(value->evnt_DescriptionPlannedRoadWayClosureCode), ASN1IMPL)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 10)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->evnt_LanesBlockedOrClosedNumber), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 11)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_BITSTRING(workspace, &(value->evnt_LanesShouldersBlockedCode), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 12)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_VisibleString(workspace, &(value->evnt_TimelineStartGeneralizedTime), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 13)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_VisibleString(workspace, &(value->evnt_TimelineEndGeneralizedTime), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 14)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->evnt_TimelineDurationTime), ASN1IMPL)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_EventIdentity(EventIdentity* value);
extern int ASN1_BER_Data_Enc_EventIdentity(ASN1WorkSpace* workspace, EventIdentity* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_EventIdentity(ASN1WorkSpace* workspace, EventIdentity* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_EventIdentity(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_EventIdentity(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_EventIdentity(ASN1WorkSpace* workspace, EventIdentity* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	ASNUINT8* _cpointer;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->node_NodeIdNumber, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->link_LinkIdNumber, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 2))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->evnt_IdentificationNumber, len, ASN1IMPL)) < 0) return ret;

		value->DEF_EventIdentity_evnt_IdentificationNumber = 1;
	}
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->evnt_LocationJurisDictionNameText, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->evnt_LocationLinkIdNumber, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->evnt_LocationNodeIdNumber, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 6)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->evnt_LocationRoadwayNameText, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 7))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 7)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)&value->evnt_DescriptionTypeEventCode, len, ASN1IMPL)) < 0) return ret;

		value->DEF_EventIdentity_evnt_DescriptionTypeEventCode = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 8))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 8)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)&value->evnt_DescriptionTypeSpecialEventCode, len, ASN1IMPL)) < 0) return ret;

		value->DEF_EventIdentity_evnt_DescriptionTypeSpecialEventCode = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 9))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 9)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)&value->evnt_DescriptionPlannedRoadWayClosureCode, len, ASN1IMPL)) < 0) return ret;

		value->DEF_EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode = 1;
	}
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 10)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->evnt_LanesBlockedOrClosedNumber, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 11)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_BITSTRING(workspace, &value->evnt_LanesShouldersBlockedCode, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 12)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_VisibleString(workspace, &value->evnt_TimelineStartGeneralizedTime, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 13)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_VisibleString(workspace, &value->evnt_TimelineEndGeneralizedTime, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 14)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->evnt_TimelineDurationTime, len, ASN1IMPL)) < 0) return ret;

	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if (IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_EventIdentity(EventIdentity* value);
extern int ASN1_BER_Data_Dec_EventIdentity(ASN1WorkSpace* workspace, EventIdentity* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_EventIdentity(ASN1WorkSpace* workspace, EventIdentity* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_EventIdentity(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_EventIdentity(value)) < 0) return ret;
	return ret;
}

/********************************************************
*EventIdentityRequest                                   *
********************************************************/
int ASN1_Print_EventIdentityRequest(EventIdentityRequest* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// Type Default
	if ((ret = ASN1_Print_UTF8Str("EventIdentityRequest", value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_EventIdentityRequest(EventIdentityRequest* value)
{
	unsigned char checkinfo_EventIdentityRequest[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_UTF8Str(value, checkinfo_EventIdentityRequest)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_EventIdentityRequest(ASN1WorkSpace* workspace, EventIdentityRequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_EventIdentityRequest(ASN1WorkSpace* workspace, EventIdentityRequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_EventIdentityRequest(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_EventIdentityRequest(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_EventIdentityRequest(ASN1WorkSpace* workspace, EventIdentityRequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_EventIdentityRequest(ASN1WorkSpace* workspace, EventIdentityRequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_EventIdentityRequest(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_EventIdentityRequest(value)) < 0) return ret;
	return ret;
}

/********************************************************
*EventIdentityResponse                                  *
********************************************************/
int ASN1_Print_EventIdentityResponse(EventIdentityResponse* value, int tab_value)
{
	int ret = 0;
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	count = value->count;
	pnode = value->head->next;
	// SEQUENCE OF : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ_OF("EventIdentityResponse");
	while (count) {
		// Type Reference EventIdentity
		ASN_Print_TAB(tab_value + 1);
		if ((ret = ASN1_Print_EventIdentity((EventIdentity*)pnode->data, tab_value + 1)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}

	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_EventIdentityResponse_EventIdentityResponse_pdata(ASN1WorkSpace* workspace, EventIdentityResponse* value, EventIdentity* user_value)
{
	int ret = 0;
	EventIdentity* list_value;
	if (value == NULL || user_value == NULL) return -1;
	list_value = (EventIdentity*)mpool_malloc(workspace->Pmemory, sizeof(EventIdentity));
	memset(list_value, 0, sizeof(EventIdentity));
	memmove(list_value, user_value, sizeof(EventIdentity));
	ASN1_Insert_Node(workspace, value, list_value);
	return ret;
}
int ASN1_GET_EventIdentityResponse_EventIdentityResponse_pdata(ASN1WorkSpace* workspace, EventIdentityResponse* value, EventIdentity** user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = ASN1_Get_Node(value);
	return ret;
}
extern int ASN1_CHECK_EventIdentity(EventIdentity* value);
int ASN1_CHECK_EventIdentityResponse(EventIdentityResponse* value)
{
	int ret = 0;

	unsigned char checkinfo_EventIdentityResponse[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_EventIdentityResponse_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		if ((ret = ASN1_CHECK_EventIdentity(pnode->data)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_EventIdentity(ASN1WorkSpace* workspace, EventIdentity* value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_EventIdentityResponse(ASN1WorkSpace* workspace, EventIdentityResponse* value, ASN1TagType tagFlag)
{
	int ret = 0;
	ASN1ListNode* pnode;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	pnode = value->head->next;
	while (NULL != pnode)
	{
		if ((ret = ASN1_BER_Data_Enc_EventIdentity(workspace, pnode->data, ASN1EXPL)) < 0) return ret;
		pnode = pnode->next;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_EventIdentityResponse(EventIdentityResponse* value);
extern int ASN1_BER_Data_Enc_EventIdentityResponse(ASN1WorkSpace* workspace, EventIdentityResponse* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_EventIdentityResponse(ASN1WorkSpace* workspace, EventIdentityResponse* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_EventIdentityResponse(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_EventIdentityResponse(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_EventIdentity(ASN1WorkSpace* workspace, EventIdentity* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_EventIdentityResponse(ASN1WorkSpace* workspace, EventIdentityResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	EventIdentity* pdata;
	ASNUINT8* p = workspace->buffer.current;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &length)) < 0) return ret;
	}
	if ((ret = ASN1_Creat_Init_List(workspace, value)) < 0) return ret;
	while (ASN1_BER_Dec_Isloop(workspace, p, length))
	{
		pdata = (EventIdentity*)mpool_malloc(GetMemPool(workspace), sizeof(EventIdentity));
		memset(pdata, 0, sizeof(EventIdentity));
		if ((ret = ASN1_BER_Data_Dec_EventIdentity(workspace, pdata, len, ASN1EXPL)) < 0) return ret;

		if ((ret = ASN1_Insert_Node(workspace, value, (void*)pdata)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if (IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_EventIdentityResponse(EventIdentityResponse* value);
extern int ASN1_BER_Data_Dec_EventIdentityResponse(ASN1WorkSpace* workspace, EventIdentityResponse* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_EventIdentityResponse(ASN1WorkSpace* workspace, EventIdentityResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_EventIdentityResponse(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_EventIdentityResponse(value)) < 0) return ret;
	return ret;
}

/********************************************************
*IncidentIdentity                                       *
********************************************************/
int ASN1_Print_IncidentIdentity(IncidentIdentity* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("IncidentIdentity");
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("node-NodeIdNumber", &(value->node_NodeIdNumber))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("link-LinkIdNumber", &(value->link_LinkIdNumber))) < 0) return ret;
	if (value->DEF_IncidentIdentity_evnt_LocationLinearDistanceOffsetBeginNumber == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("evnt-LocationLinearDistanceOffsetBeginNumber", &(value->evnt_LocationLinearDistanceOffsetBeginNumber))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_IncidentIdentity_evnt_LinearDistanceoffsetEndNumber == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("evnt-LinearDistanceoffsetEndNumber", &(value->evnt_LinearDistanceoffsetEndNumber))) < 0) return ret;
	} /* OPTIONAL end */
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_VisibleString("evnt-UpdateGeneralizedTime", &(value->evnt_UpdateGeneralizedTime))) < 0) return ret;
	if (value->DEF_IncidentIdentity_evnt_IncidentHumanFatalitiesCountQuantity == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("evnt-IncidentHumanFatalitiesCountQuantity", &(value->evnt_IncidentHumanFatalitiesCountQuantity))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_IncidentIdentity_evnt_IncidentHumanInjuriesCountQuantity == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("evnt-IncidentHumanInjuriesCountQuantity", &(value->evnt_IncidentHumanInjuriesCountQuantity))) < 0) return ret;
	} /* OPTIONAL end */
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_BITSTRING("evnt-IncidentPropertyDamageCode", &(value->evnt_IncidentPropertyDamageCode))) < 0) return ret;
	if (value->DEF_IncidentIdentity_evnt_IncidentPropertyDamageOther == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_UTF8Str("evnt-IncidentPropertyDamageOther", &(value->evnt_IncidentPropertyDamageOther))) < 0) return ret;
	} /* OPTIONAL end */
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_IncidentIdentity_node_NodeIdNumber(ASN1WorkSpace* workspace, IncidentIdentity* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->node_NodeIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_IncidentIdentity_link_LinkIdNumber(ASN1WorkSpace* workspace, IncidentIdentity* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->link_LinkIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_IncidentIdentity_evnt_LocationLinearDistanceOffsetBeginNumber(ASN1WorkSpace* workspace, IncidentIdentity* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_IncidentIdentity_evnt_LocationLinearDistanceOffsetBeginNumber = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->evnt_LocationLinearDistanceOffsetBeginNumber, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_IncidentIdentity_evnt_LinearDistanceoffsetEndNumber(ASN1WorkSpace* workspace, IncidentIdentity* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_IncidentIdentity_evnt_LinearDistanceoffsetEndNumber = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->evnt_LinearDistanceoffsetEndNumber, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_IncidentIdentity_evnt_UpdateGeneralizedTime(ASN1WorkSpace* workspace, IncidentIdentity* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_VisibleString(workspace, &value->evnt_UpdateGeneralizedTime, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_IncidentIdentity_evnt_IncidentHumanFatalitiesCountQuantity(ASN1WorkSpace* workspace, IncidentIdentity* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_IncidentIdentity_evnt_IncidentHumanFatalitiesCountQuantity = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->evnt_IncidentHumanFatalitiesCountQuantity, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_IncidentIdentity_evnt_IncidentHumanInjuriesCountQuantity(ASN1WorkSpace* workspace, IncidentIdentity* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_IncidentIdentity_evnt_IncidentHumanInjuriesCountQuantity = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->evnt_IncidentHumanInjuriesCountQuantity, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_IncidentIdentity_evnt_IncidentPropertyDamageCode(ASN1WorkSpace* workspace, IncidentIdentity* value, ASNUINT8* user_value, ASNUINT32L user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_BITSTRING(workspace, &value->evnt_IncidentPropertyDamageCode, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_IncidentIdentity_evnt_IncidentPropertyDamageOther(ASN1WorkSpace* workspace, IncidentIdentity* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->DEF_IncidentIdentity_evnt_IncidentPropertyDamageOther = 1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->evnt_IncidentPropertyDamageOther, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_IncidentIdentity_node_NodeIdNumber(ASN1WorkSpace* workspace, IncidentIdentity* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->node_NodeIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_IncidentIdentity_link_LinkIdNumber(ASN1WorkSpace* workspace, IncidentIdentity* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->link_LinkIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_IncidentIdentity_evnt_LocationLinearDistanceOffsetBeginNumber(ASN1WorkSpace* workspace, IncidentIdentity* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_IncidentIdentity_evnt_LocationLinearDistanceOffsetBeginNumber == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->evnt_LocationLinearDistanceOffsetBeginNumber, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_IncidentIdentity_evnt_LinearDistanceoffsetEndNumber(ASN1WorkSpace* workspace, IncidentIdentity* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_IncidentIdentity_evnt_LinearDistanceoffsetEndNumber == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->evnt_LinearDistanceoffsetEndNumber, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_IncidentIdentity_evnt_UpdateGeneralizedTime(ASN1WorkSpace* workspace, IncidentIdentity* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_VisibleString(workspace, &value->evnt_UpdateGeneralizedTime, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_IncidentIdentity_evnt_IncidentHumanFatalitiesCountQuantity(ASN1WorkSpace* workspace, IncidentIdentity* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_IncidentIdentity_evnt_IncidentHumanFatalitiesCountQuantity == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->evnt_IncidentHumanFatalitiesCountQuantity, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_IncidentIdentity_evnt_IncidentHumanInjuriesCountQuantity(ASN1WorkSpace* workspace, IncidentIdentity* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_IncidentIdentity_evnt_IncidentHumanInjuriesCountQuantity == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->evnt_IncidentHumanInjuriesCountQuantity, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_IncidentIdentity_evnt_IncidentPropertyDamageCode(ASN1WorkSpace* workspace, IncidentIdentity* value, ASNUINT8** user_value, ASNUINT32L* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_BITSTRING(workspace, &value->evnt_IncidentPropertyDamageCode, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_IncidentIdentity_evnt_IncidentPropertyDamageOther(ASN1WorkSpace* workspace, IncidentIdentity* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_IncidentIdentity_evnt_IncidentPropertyDamageOther == 1)
	{
		if ((ret = ASN1_GET_UTF8Str(workspace, &value->evnt_IncidentPropertyDamageOther, user_value, user_value_length)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_CHECK_IncidentIdentity(IncidentIdentity* value)
{
	int ret = 0;

	unsigned char checkinfo_node_NodeIdNumber[] = {
		0x02,0x01,0x28,0x00
	};
	unsigned char checkinfo_link_LinkIdNumber[] = {
		0x02,0x01,0x28,0x00
	};
	unsigned char checkinfo_evnt_LocationLinearDistanceOffsetBeginNumber[] = {
		0x02,0x00,0x82,0x03,0xE7,0x00
	};
	unsigned char checkinfo_evnt_LinearDistanceoffsetEndNumber[] = {
		0x02,0x00,0x82,0x03,0xE7,0x00
	};
	unsigned char checkinfo_evnt_UpdateGeneralizedTime[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_evnt_IncidentHumanFatalitiesCountQuantity[] = {
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_evnt_IncidentHumanInjuriesCountQuantity[] = {
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_evnt_IncidentPropertyDamageCode[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_evnt_IncidentPropertyDamageOther[] = {
		0x02,0x01,0x82,0x01,0x00,0x00
	};

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_UTF8Str(&(value->node_NodeIdNumber), checkinfo_node_NodeIdNumber)) < 0) return ret;
	if ((ret = ASN1_CHECK_UTF8Str(&(value->link_LinkIdNumber), checkinfo_link_LinkIdNumber)) < 0) return ret;
	if (value->DEF_IncidentIdentity_evnt_LocationLinearDistanceOffsetBeginNumber == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->evnt_LocationLinearDistanceOffsetBeginNumber), checkinfo_evnt_LocationLinearDistanceOffsetBeginNumber)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_IncidentIdentity_evnt_LinearDistanceoffsetEndNumber == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->evnt_LinearDistanceoffsetEndNumber), checkinfo_evnt_LinearDistanceoffsetEndNumber)) < 0) return ret;
	} /* OPTIONAL end */
	if ((ret = ASN1_CHECK_VisibleString(&(value->evnt_UpdateGeneralizedTime), checkinfo_evnt_UpdateGeneralizedTime)) < 0) return ret;
	if (value->DEF_IncidentIdentity_evnt_IncidentHumanFatalitiesCountQuantity == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->evnt_IncidentHumanFatalitiesCountQuantity), checkinfo_evnt_IncidentHumanFatalitiesCountQuantity)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_IncidentIdentity_evnt_IncidentHumanInjuriesCountQuantity == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->evnt_IncidentHumanInjuriesCountQuantity), checkinfo_evnt_IncidentHumanInjuriesCountQuantity)) < 0) return ret;
	} /* OPTIONAL end */
	if ((ret = ASN1_CHECK_BITSTRING(&(value->evnt_IncidentPropertyDamageCode), checkinfo_evnt_IncidentPropertyDamageCode)) < 0) return ret;
	if (value->DEF_IncidentIdentity_evnt_IncidentPropertyDamageOther == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_UTF8Str(&(value->evnt_IncidentPropertyDamageOther), checkinfo_evnt_IncidentPropertyDamageOther)) < 0) return ret;
	} /* OPTIONAL end */
	return ret;
}
int ASN1_BER_Data_Enc_IncidentIdentity(ASN1WorkSpace* workspace, IncidentIdentity* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->node_NodeIdNumber), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->link_LinkIdNumber), ASN1IMPL)) < 0) return ret;
	if (value->DEF_IncidentIdentity_evnt_LocationLinearDistanceOffsetBeginNumber == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->evnt_LocationLinearDistanceOffsetBeginNumber), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_IncidentIdentity_evnt_LinearDistanceoffsetEndNumber == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->evnt_LinearDistanceoffsetEndNumber), ASN1IMPL)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_VisibleString(workspace, &(value->evnt_UpdateGeneralizedTime), ASN1IMPL)) < 0) return ret;
	if (value->DEF_IncidentIdentity_evnt_IncidentHumanFatalitiesCountQuantity == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->evnt_IncidentHumanFatalitiesCountQuantity), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_IncidentIdentity_evnt_IncidentHumanInjuriesCountQuantity == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 6)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->evnt_IncidentHumanInjuriesCountQuantity), ASN1IMPL)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 7)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_BITSTRING(workspace, &(value->evnt_IncidentPropertyDamageCode), ASN1IMPL)) < 0) return ret;
	if (value->DEF_IncidentIdentity_evnt_IncidentPropertyDamageOther == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 8)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->evnt_IncidentPropertyDamageOther), ASN1IMPL)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_IncidentIdentity(IncidentIdentity* value);
extern int ASN1_BER_Data_Enc_IncidentIdentity(ASN1WorkSpace* workspace, IncidentIdentity* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_IncidentIdentity(ASN1WorkSpace* workspace, IncidentIdentity* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_IncidentIdentity(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_IncidentIdentity(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_IncidentIdentity(ASN1WorkSpace* workspace, IncidentIdentity* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	ASNUINT8* _cpointer;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->node_NodeIdNumber, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->link_LinkIdNumber, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 2))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->evnt_LocationLinearDistanceOffsetBeginNumber, len, ASN1IMPL)) < 0) return ret;

		value->DEF_IncidentIdentity_evnt_LocationLinearDistanceOffsetBeginNumber = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 3))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->evnt_LinearDistanceoffsetEndNumber, len, ASN1IMPL)) < 0) return ret;

		value->DEF_IncidentIdentity_evnt_LinearDistanceoffsetEndNumber = 1;
	}
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_VisibleString(workspace, &value->evnt_UpdateGeneralizedTime, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 5))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->evnt_IncidentHumanFatalitiesCountQuantity, len, ASN1IMPL)) < 0) return ret;

		value->DEF_IncidentIdentity_evnt_IncidentHumanFatalitiesCountQuantity = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 6))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 6)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->evnt_IncidentHumanInjuriesCountQuantity, len, ASN1IMPL)) < 0) return ret;

		value->DEF_IncidentIdentity_evnt_IncidentHumanInjuriesCountQuantity = 1;
	}
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 7)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_BITSTRING(workspace, &value->evnt_IncidentPropertyDamageCode, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 8))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 8)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->evnt_IncidentPropertyDamageOther, len, ASN1IMPL)) < 0) return ret;

		value->DEF_IncidentIdentity_evnt_IncidentPropertyDamageOther = 1;
	}
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if (IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_IncidentIdentity(IncidentIdentity* value);
extern int ASN1_BER_Data_Dec_IncidentIdentity(ASN1WorkSpace* workspace, IncidentIdentity* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_IncidentIdentity(ASN1WorkSpace* workspace, IncidentIdentity* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_IncidentIdentity(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_IncidentIdentity(value)) < 0) return ret;
	return ret;
}

/********************************************************
*IncidentIdentityRequest                                *
********************************************************/
int ASN1_Print_IncidentIdentityRequest(IncidentIdentityRequest* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// Type Default
	if ((ret = ASN1_Print_UTF8Str("IncidentIdentityRequest", value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_IncidentIdentityRequest(IncidentIdentityRequest* value)
{
	unsigned char checkinfo_IncidentIdentityRequest[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_UTF8Str(value, checkinfo_IncidentIdentityRequest)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_IncidentIdentityRequest(ASN1WorkSpace* workspace, IncidentIdentityRequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_IncidentIdentityRequest(ASN1WorkSpace* workspace, IncidentIdentityRequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_IncidentIdentityRequest(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_IncidentIdentityRequest(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_IncidentIdentityRequest(ASN1WorkSpace* workspace, IncidentIdentityRequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_IncidentIdentityRequest(ASN1WorkSpace* workspace, IncidentIdentityRequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_IncidentIdentityRequest(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_IncidentIdentityRequest(value)) < 0) return ret;
	return ret;
}

/********************************************************
*IncidentIdentityResponse                               *
********************************************************/
int ASN1_Print_IncidentIdentityResponse(IncidentIdentityResponse* value, int tab_value)
{
	int ret = 0;
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	count = value->count;
	pnode = value->head->next;
	// SEQUENCE OF : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ_OF("IncidentIdentityResponse");
	while (count) {
		// Type Reference IncidentIdentity
		ASN_Print_TAB(tab_value + 1);
		if ((ret = ASN1_Print_IncidentIdentity((IncidentIdentity*)pnode->data, tab_value + 1)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}

	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_IncidentIdentityResponse_IncidentIdentityResponse_pdata(ASN1WorkSpace* workspace, IncidentIdentityResponse* value, IncidentIdentity* user_value)
{
	int ret = 0;
	IncidentIdentity* list_value;
	if (value == NULL || user_value == NULL) return -1;
	list_value = (IncidentIdentity*)mpool_malloc(workspace->Pmemory, sizeof(IncidentIdentity));
	memset(list_value, 0, sizeof(IncidentIdentity));
	memmove(list_value, user_value, sizeof(IncidentIdentity));
	ASN1_Insert_Node(workspace, value, list_value);
	return ret;
}
int ASN1_GET_IncidentIdentityResponse_IncidentIdentityResponse_pdata(ASN1WorkSpace* workspace, IncidentIdentityResponse* value, IncidentIdentity** user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = ASN1_Get_Node(value);
	return ret;
}
extern int ASN1_CHECK_IncidentIdentity(IncidentIdentity* value);
int ASN1_CHECK_IncidentIdentityResponse(IncidentIdentityResponse* value)
{
	int ret = 0;

	unsigned char checkinfo_IncidentIdentityResponse[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_IncidentIdentityResponse_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		if ((ret = ASN1_CHECK_IncidentIdentity(pnode->data)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_IncidentIdentity(ASN1WorkSpace* workspace, IncidentIdentity* value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_IncidentIdentityResponse(ASN1WorkSpace* workspace, IncidentIdentityResponse* value, ASN1TagType tagFlag)
{
	int ret = 0;
	ASN1ListNode* pnode;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	pnode = value->head->next;
	while (NULL != pnode)
	{
		if ((ret = ASN1_BER_Data_Enc_IncidentIdentity(workspace, pnode->data, ASN1EXPL)) < 0) return ret;
		pnode = pnode->next;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_IncidentIdentityResponse(IncidentIdentityResponse* value);
extern int ASN1_BER_Data_Enc_IncidentIdentityResponse(ASN1WorkSpace* workspace, IncidentIdentityResponse* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_IncidentIdentityResponse(ASN1WorkSpace* workspace, IncidentIdentityResponse* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_IncidentIdentityResponse(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_IncidentIdentityResponse(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_IncidentIdentity(ASN1WorkSpace* workspace, IncidentIdentity* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_IncidentIdentityResponse(ASN1WorkSpace* workspace, IncidentIdentityResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	IncidentIdentity* pdata;
	ASNUINT8* p = workspace->buffer.current;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &length)) < 0) return ret;
	}
	if ((ret = ASN1_Creat_Init_List(workspace, value)) < 0) return ret;
	while (ASN1_BER_Dec_Isloop(workspace, p, length))
	{
		pdata = (IncidentIdentity*)mpool_malloc(GetMemPool(workspace), sizeof(IncidentIdentity));
		memset(pdata, 0, sizeof(IncidentIdentity));
		if ((ret = ASN1_BER_Data_Dec_IncidentIdentity(workspace, pdata, len, ASN1EXPL)) < 0) return ret;

		if ((ret = ASN1_Insert_Node(workspace, value, (void*)pdata)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if (IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_IncidentIdentityResponse(IncidentIdentityResponse* value);
extern int ASN1_BER_Data_Dec_IncidentIdentityResponse(ASN1WorkSpace* workspace, IncidentIdentityResponse* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_IncidentIdentityResponse(ASN1WorkSpace* workspace, IncidentIdentityResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_IncidentIdentityResponse(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_IncidentIdentityResponse(value)) < 0) return ret;
	return ret;
}

/********************************************************
*IncidentConditions                                     *
********************************************************/
int ASN1_Print_IncidentConditions(IncidentConditions* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("IncidentConditions");
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("node-NodeIdNumber", &(value->node_NodeIdNumber))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("link-LinkIdNumber", &(value->link_LinkIdNumber))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("orgn-ContatOrganizationNameText", &(value->orgn_ContatOrganizationNameText))) < 0) return ret;
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch (value->evnt_DescriptionTypeIncidentCode)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeIncidentCode", "other-no-additional-information-required", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeIncidentCode", "other-additional-information-required", 1)) < 0) return ret; break;
	case 2: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeIncidentCode", "vehicular-accident", 2)) < 0) return ret; break;
	case 3: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeIncidentCode", "weather-related-incident", 3)) < 0) return ret; break;
	case 4: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeIncidentCode", "stalled-vehicle", 4)) < 0) return ret; break;
	case 5: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeIncidentCode", "vehicle-fire", 5)) < 0) return ret; break;
	case 6: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeIncidentCode", "roadway-debris", 6)) < 0) return ret; break;
	case 7: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeIncidentCode", "hazmat-spill", 7)) < 0) return ret; break;
	case 8: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeIncidentCode", "earthquake", 8)) < 0) return ret; break;
	case 9: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeIncidentCode", "landslide", 9)) < 0) return ret; break;
	case 10: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeIncidentCode", "flood", 10)) < 0) return ret; break;
	case 11: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeIncidentCode", "typhoon", 11)) < 0) return ret; break;
	case 12: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeIncidentCode", "unplanned-demonstration", 12)) < 0) return ret; break;
	case 13: if ((ret = ASN1_Print_ENUMERATED("evnt_DescriptionTypeIncidentCode", "increased-traffice-volume", 13)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	if (value->DEF_IncidentConditions_evnt_DescriptionTypeIncidentOther == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_UTF8Str("evnt-DescriptionTypeIncidentOther", &(value->evnt_DescriptionTypeIncidentOther))) < 0) return ret;
	} /* OPTIONAL end */
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_BITSTRING("evnt-IncidentVehiclesInvolvedCode", &(value->evnt_IncidentVehiclesInvolvedCode))) < 0) return ret;
	if (value->DEF_IncidentConditions_evnt_IncidentVehiclesInvolvedOther == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_UTF8Str("evnt-IncidentVehiclesInvolvedOther", &(value->evnt_IncidentVehiclesInvolvedOther))) < 0) return ret;
	} /* OPTIONAL end */
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch (value->evnt_IncidentStatusCode)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("evnt_IncidentStatusCode", "other-no-additional-information-required", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("evnt_IncidentStatusCode", "other-additional-information-required", 1)) < 0) return ret; break;
	case 2: if ((ret = ASN1_Print_ENUMERATED("evnt_IncidentStatusCode", "incident-detected", 2)) < 0) return ret; break;
	case 3: if ((ret = ASN1_Print_ENUMERATED("evnt_IncidentStatusCode", "confirmed-and-responding", 3)) < 0) return ret; break;
	case 4: if ((ret = ASN1_Print_ENUMERATED("evnt_IncidentStatusCode", "cleared-and-recovering", 4)) < 0) return ret; break;
	case 5: if ((ret = ASN1_Print_ENUMERATED("evnt_IncidentStatusCode", "over-and-done", 5)) < 0) return ret; break;
	case 6: if ((ret = ASN1_Print_ENUMERATED("evnt_IncidentStatusCode", "other", 6)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	if (value->DEF_IncidentConditions_evnt_IncidentStatusOther == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_UTF8Str("evnt-IncidentStatusOther", &(value->evnt_IncidentStatusOther))) < 0) return ret;
	} /* OPTIONAL end */
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch (value->evnt_UpdateTypeCode)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("evnt_UpdateTypeCode", "other-no-additional-information-required", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("evnt_UpdateTypeCode", "other-additional-information-required", 1)) < 0) return ret; break;
	case 2: if ((ret = ASN1_Print_ENUMERATED("evnt_UpdateTypeCode", "new", 2)) < 0) return ret; break;
	case 3: if ((ret = ASN1_Print_ENUMERATED("evnt_UpdateTypeCode", "update", 3)) < 0) return ret; break;
	case 4: if ((ret = ASN1_Print_ENUMERATED("evnt_UpdateTypeCode", "delete", 4)) < 0) return ret; break;
	case 5: if ((ret = ASN1_Print_ENUMERATED("evnt_UpdateTypeCode", "clear-or-closed", 5)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	if (value->DEF_IncidentConditions_evnt_UpdateTypeOther == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_UTF8Str("evnt-UpdateTypeOther", &(value->evnt_UpdateTypeOther))) < 0) return ret;
	} /* OPTIONAL end */
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_IncidentConditions_node_NodeIdNumber(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->node_NodeIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_IncidentConditions_link_LinkIdNumber(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->link_LinkIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_IncidentConditions_orgn_ContatOrganizationNameText(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->orgn_ContatOrganizationNameText, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_IncidentConditions_evnt_DescriptionTypeIncidentCode(ASN1WorkSpace* workspace, IncidentConditions* value, ENUMERATED user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_ENUMERATED(workspace, (ASNINT32*)&value->evnt_DescriptionTypeIncidentCode, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_IncidentConditions_evnt_DescriptionTypeIncidentOther(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->DEF_IncidentConditions_evnt_DescriptionTypeIncidentOther = 1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->evnt_DescriptionTypeIncidentOther, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_IncidentConditions_evnt_IncidentVehiclesInvolvedCode(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8* user_value, ASNUINT32L user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_BITSTRING(workspace, &value->evnt_IncidentVehiclesInvolvedCode, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_IncidentConditions_evnt_IncidentVehiclesInvolvedOther(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->DEF_IncidentConditions_evnt_IncidentVehiclesInvolvedOther = 1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->evnt_IncidentVehiclesInvolvedOther, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_IncidentConditions_evnt_IncidentStatusCode(ASN1WorkSpace* workspace, IncidentConditions* value, ENUMERATED user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_ENUMERATED(workspace, (ASNINT32*)&value->evnt_IncidentStatusCode, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_IncidentConditions_evnt_IncidentStatusOther(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->DEF_IncidentConditions_evnt_IncidentStatusOther = 1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->evnt_IncidentStatusOther, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_IncidentConditions_evnt_UpdateTypeCode(ASN1WorkSpace* workspace, IncidentConditions* value, ENUMERATED user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_ENUMERATED(workspace, (ASNINT32*)&value->evnt_UpdateTypeCode, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_IncidentConditions_evnt_UpdateTypeOther(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->DEF_IncidentConditions_evnt_UpdateTypeOther = 1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->evnt_UpdateTypeOther, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_IncidentConditions_node_NodeIdNumber(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->node_NodeIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_IncidentConditions_link_LinkIdNumber(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->link_LinkIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_IncidentConditions_orgn_ContatOrganizationNameText(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->orgn_ContatOrganizationNameText, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_IncidentConditions_evnt_DescriptionTypeIncidentCode(ASN1WorkSpace* workspace, IncidentConditions* value, ENUMERATED* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->evnt_DescriptionTypeIncidentCode, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_IncidentConditions_evnt_DescriptionTypeIncidentOther(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_IncidentConditions_evnt_DescriptionTypeIncidentOther == 1)
	{
		if ((ret = ASN1_GET_UTF8Str(workspace, &value->evnt_DescriptionTypeIncidentOther, user_value, user_value_length)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_IncidentConditions_evnt_IncidentVehiclesInvolvedCode(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8** user_value, ASNUINT32L* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_BITSTRING(workspace, &value->evnt_IncidentVehiclesInvolvedCode, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_IncidentConditions_evnt_IncidentVehiclesInvolvedOther(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_IncidentConditions_evnt_IncidentVehiclesInvolvedOther == 1)
	{
		if ((ret = ASN1_GET_UTF8Str(workspace, &value->evnt_IncidentVehiclesInvolvedOther, user_value, user_value_length)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_IncidentConditions_evnt_IncidentStatusCode(ASN1WorkSpace* workspace, IncidentConditions* value, ENUMERATED* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->evnt_IncidentStatusCode, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_IncidentConditions_evnt_IncidentStatusOther(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_IncidentConditions_evnt_IncidentStatusOther == 1)
	{
		if ((ret = ASN1_GET_UTF8Str(workspace, &value->evnt_IncidentStatusOther, user_value, user_value_length)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_IncidentConditions_evnt_UpdateTypeCode(ASN1WorkSpace* workspace, IncidentConditions* value, ENUMERATED* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->evnt_UpdateTypeCode, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_IncidentConditions_evnt_UpdateTypeOther(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_IncidentConditions_evnt_UpdateTypeOther == 1)
	{
		if ((ret = ASN1_GET_UTF8Str(workspace, &value->evnt_UpdateTypeOther, user_value, user_value_length)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_CHECK_IncidentConditions(IncidentConditions* value)
{
	int ret = 0;

	unsigned char checkinfo_node_NodeIdNumber[] = {
		0x02,0x01,0x28,0x00
	};
	unsigned char checkinfo_link_LinkIdNumber[] = {
		0x02,0x01,0x28,0x00
	};
	unsigned char checkinfo_orgn_ContatOrganizationNameText[] = {
		0x02,0x01,0x82,0x00,0x80,0x00
	};
	unsigned char checkinfo_evnt_DescriptionTypeIncidentCode[] = {
		0x0E,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x00
	};
	unsigned char checkinfo_evnt_DescriptionTypeIncidentOther[] = {
		0x02,0x01,0x82,0x01,0x00,0x00
	};
	unsigned char checkinfo_evnt_IncidentVehiclesInvolvedCode[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_evnt_IncidentVehiclesInvolvedOther[] = {
		0x02,0x01,0x82,0x01,0x00,0x00
	};
	unsigned char checkinfo_evnt_IncidentStatusCode[] = {
		0x07,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x00
	};
	unsigned char checkinfo_evnt_IncidentStatusOther[] = {
		0x02,0x01,0x82,0x01,0x00,0x00
	};
	unsigned char checkinfo_evnt_UpdateTypeCode[] = {
		0x06,0x00,0x01,0x02,0x03,0x04,0x05,0x00
	};
	unsigned char checkinfo_evnt_UpdateTypeOther[] = {
		0x02,0x01,0x82,0x01,0x00,0x00
	};

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_UTF8Str(&(value->node_NodeIdNumber), checkinfo_node_NodeIdNumber)) < 0) return ret;
	if ((ret = ASN1_CHECK_UTF8Str(&(value->link_LinkIdNumber), checkinfo_link_LinkIdNumber)) < 0) return ret;
	if ((ret = ASN1_CHECK_UTF8Str(&(value->orgn_ContatOrganizationNameText), checkinfo_orgn_ContatOrganizationNameText)) < 0) return ret;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->evnt_DescriptionTypeIncidentCode), checkinfo_evnt_DescriptionTypeIncidentCode)) < 0) return ret;
	if (value->DEF_IncidentConditions_evnt_DescriptionTypeIncidentOther == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_UTF8Str(&(value->evnt_DescriptionTypeIncidentOther), checkinfo_evnt_DescriptionTypeIncidentOther)) < 0) return ret;
	} /* OPTIONAL end */
	if ((ret = ASN1_CHECK_BITSTRING(&(value->evnt_IncidentVehiclesInvolvedCode), checkinfo_evnt_IncidentVehiclesInvolvedCode)) < 0) return ret;
	if (value->DEF_IncidentConditions_evnt_IncidentVehiclesInvolvedOther == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_UTF8Str(&(value->evnt_IncidentVehiclesInvolvedOther), checkinfo_evnt_IncidentVehiclesInvolvedOther)) < 0) return ret;
	} /* OPTIONAL end */
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->evnt_IncidentStatusCode), checkinfo_evnt_IncidentStatusCode)) < 0) return ret;
	if (value->DEF_IncidentConditions_evnt_IncidentStatusOther == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_UTF8Str(&(value->evnt_IncidentStatusOther), checkinfo_evnt_IncidentStatusOther)) < 0) return ret;
	} /* OPTIONAL end */
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->evnt_UpdateTypeCode), checkinfo_evnt_UpdateTypeCode)) < 0) return ret;
	if (value->DEF_IncidentConditions_evnt_UpdateTypeOther == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_UTF8Str(&(value->evnt_UpdateTypeOther), checkinfo_evnt_UpdateTypeOther)) < 0) return ret;
	} /* OPTIONAL end */
	return ret;
}
int ASN1_BER_Data_Enc_IncidentConditions(ASN1WorkSpace* workspace, IncidentConditions* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->node_NodeIdNumber), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->link_LinkIdNumber), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->orgn_ContatOrganizationNameText), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32*)&(value->evnt_DescriptionTypeIncidentCode), ASN1IMPL)) < 0) return ret;
	if (value->DEF_IncidentConditions_evnt_DescriptionTypeIncidentOther == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->evnt_DescriptionTypeIncidentOther), ASN1IMPL)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_BITSTRING(workspace, &(value->evnt_IncidentVehiclesInvolvedCode), ASN1IMPL)) < 0) return ret;
	if (value->DEF_IncidentConditions_evnt_IncidentVehiclesInvolvedOther == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 6)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->evnt_IncidentVehiclesInvolvedOther), ASN1IMPL)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 7)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32*)&(value->evnt_IncidentStatusCode), ASN1IMPL)) < 0) return ret;
	if (value->DEF_IncidentConditions_evnt_IncidentStatusOther == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 8)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->evnt_IncidentStatusOther), ASN1IMPL)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 9)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32*)&(value->evnt_UpdateTypeCode), ASN1IMPL)) < 0) return ret;
	if (value->DEF_IncidentConditions_evnt_UpdateTypeOther == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 10)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->evnt_UpdateTypeOther), ASN1IMPL)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_IncidentConditions(IncidentConditions* value);
extern int ASN1_BER_Data_Enc_IncidentConditions(ASN1WorkSpace* workspace, IncidentConditions* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_IncidentConditions(ASN1WorkSpace* workspace, IncidentConditions* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_IncidentConditions(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_IncidentConditions(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_IncidentConditions(ASN1WorkSpace* workspace, IncidentConditions* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	ASNUINT8* _cpointer;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->node_NodeIdNumber, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->link_LinkIdNumber, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->orgn_ContatOrganizationNameText, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)&value->evnt_DescriptionTypeIncidentCode, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 4))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->evnt_DescriptionTypeIncidentOther, len, ASN1IMPL)) < 0) return ret;

		value->DEF_IncidentConditions_evnt_DescriptionTypeIncidentOther = 1;
	}
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_BITSTRING(workspace, &value->evnt_IncidentVehiclesInvolvedCode, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 6))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 6)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->evnt_IncidentVehiclesInvolvedOther, len, ASN1IMPL)) < 0) return ret;

		value->DEF_IncidentConditions_evnt_IncidentVehiclesInvolvedOther = 1;
	}
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 7)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)&value->evnt_IncidentStatusCode, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 8))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 8)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->evnt_IncidentStatusOther, len, ASN1IMPL)) < 0) return ret;

		value->DEF_IncidentConditions_evnt_IncidentStatusOther = 1;
	}
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 9)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)&value->evnt_UpdateTypeCode, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 10))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 10)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->evnt_UpdateTypeOther, len, ASN1IMPL)) < 0) return ret;

		value->DEF_IncidentConditions_evnt_UpdateTypeOther = 1;
	}
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if (IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_IncidentConditions(IncidentConditions* value);
extern int ASN1_BER_Data_Dec_IncidentConditions(ASN1WorkSpace* workspace, IncidentConditions* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_IncidentConditions(ASN1WorkSpace* workspace, IncidentConditions* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_IncidentConditions(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_IncidentConditions(value)) < 0) return ret;
	return ret;
}

/********************************************************
*IncidentConditionsRequest                              *
********************************************************/
int ASN1_Print_IncidentConditionsRequest(IncidentConditionsRequest* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// Type Default
	if ((ret = ASN1_Print_UTF8Str("IncidentConditionsRequest", value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_IncidentConditionsRequest(IncidentConditionsRequest* value)
{
	unsigned char checkinfo_IncidentConditionsRequest[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_UTF8Str(value, checkinfo_IncidentConditionsRequest)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_IncidentConditionsRequest(ASN1WorkSpace* workspace, IncidentConditionsRequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_IncidentConditionsRequest(ASN1WorkSpace* workspace, IncidentConditionsRequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_IncidentConditionsRequest(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_IncidentConditionsRequest(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_IncidentConditionsRequest(ASN1WorkSpace* workspace, IncidentConditionsRequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_IncidentConditionsRequest(ASN1WorkSpace* workspace, IncidentConditionsRequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_IncidentConditionsRequest(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_IncidentConditionsRequest(value)) < 0) return ret;
	return ret;
}

/********************************************************
*IncidentConditionsResponse                             *
********************************************************/
int ASN1_Print_IncidentConditionsResponse(IncidentConditionsResponse* value, int tab_value)
{
	int ret = 0;
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	count = value->count;
	pnode = value->head->next;
	// SEQUENCE OF : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ_OF("IncidentConditionsResponse");
	while (count) {
		// Type Reference IncidentConditions
		ASN_Print_TAB(tab_value + 1);
		if ((ret = ASN1_Print_IncidentConditions((IncidentConditions*)pnode->data, tab_value + 1)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}

	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_IncidentConditionsResponse_IncidentConditionsResponse_pdata(ASN1WorkSpace* workspace, IncidentConditionsResponse* value, IncidentConditions* user_value)
{
	int ret = 0;
	IncidentConditions* list_value;
	if (value == NULL || user_value == NULL) return -1;
	list_value = (IncidentConditions*)mpool_malloc(workspace->Pmemory, sizeof(IncidentConditions));
	memset(list_value, 0, sizeof(IncidentConditions));
	memmove(list_value, user_value, sizeof(IncidentConditions));
	ASN1_Insert_Node(workspace, value, list_value);
	return ret;
}
int ASN1_GET_IncidentConditionsResponse_IncidentConditionsResponse_pdata(ASN1WorkSpace* workspace, IncidentConditionsResponse* value, IncidentConditions** user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = ASN1_Get_Node(value);
	return ret;
}
extern int ASN1_CHECK_IncidentConditions(IncidentConditions* value);
int ASN1_CHECK_IncidentConditionsResponse(IncidentConditionsResponse* value)
{
	int ret = 0;

	unsigned char checkinfo_IncidentConditionsResponse[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_IncidentConditionsResponse_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		if ((ret = ASN1_CHECK_IncidentConditions(pnode->data)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_IncidentConditions(ASN1WorkSpace* workspace, IncidentConditions* value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_IncidentConditionsResponse(ASN1WorkSpace* workspace, IncidentConditionsResponse* value, ASN1TagType tagFlag)
{
	int ret = 0;
	ASN1ListNode* pnode;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	pnode = value->head->next;
	while (NULL != pnode)
	{
		if ((ret = ASN1_BER_Data_Enc_IncidentConditions(workspace, pnode->data, ASN1EXPL)) < 0) return ret;
		pnode = pnode->next;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_IncidentConditionsResponse(IncidentConditionsResponse* value);
extern int ASN1_BER_Data_Enc_IncidentConditionsResponse(ASN1WorkSpace* workspace, IncidentConditionsResponse* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_IncidentConditionsResponse(ASN1WorkSpace* workspace, IncidentConditionsResponse* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_IncidentConditionsResponse(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_IncidentConditionsResponse(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_IncidentConditions(ASN1WorkSpace* workspace, IncidentConditions* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_IncidentConditionsResponse(ASN1WorkSpace* workspace, IncidentConditionsResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	IncidentConditions* pdata;
	ASNUINT8* p = workspace->buffer.current;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &length)) < 0) return ret;
	}
	if ((ret = ASN1_Creat_Init_List(workspace, value)) < 0) return ret;
	while (ASN1_BER_Dec_Isloop(workspace, p, length))
	{
		pdata = (IncidentConditions*)mpool_malloc(GetMemPool(workspace), sizeof(IncidentConditions));
		memset(pdata, 0, sizeof(IncidentConditions));
		if ((ret = ASN1_BER_Data_Dec_IncidentConditions(workspace, pdata, len, ASN1EXPL)) < 0) return ret;

		if ((ret = ASN1_Insert_Node(workspace, value, (void*)pdata)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if (IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_IncidentConditionsResponse(IncidentConditionsResponse* value);
extern int ASN1_BER_Data_Dec_IncidentConditionsResponse(ASN1WorkSpace* workspace, IncidentConditionsResponse* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_IncidentConditionsResponse(ASN1WorkSpace* workspace, IncidentConditionsResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_IncidentConditionsResponse(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_IncidentConditionsResponse(value)) < 0) return ret;
	return ret;
}

/********************************************************
*RoadwaySurfaceStatus                                   *
********************************************************/
int ASN1_Print_RoadwaySurfaceStatus(RoadwaySurfaceStatus* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("RoadwaySurfaceStatus");
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("node-NodeIdNumber", &(value->node_NodeIdNumber))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("link-LinkIdNumber", &(value->link_LinkIdNumber))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_BITSTRING("link-SurfaceConditionCode", &(value->link_SurfaceConditionCode))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_BITSTRING("link-LandBlockedOrClosedCode", &(value->link_LandBlockedOrClosedCode))) < 0) return ret;
	if (value->DEF_RoadwaySurfaceStatus_evsn_DataSurfacePrecipitationDepth == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("evsn-DataSurfacePrecipitationDepth", &(value->evsn_DataSurfacePrecipitationDepth))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_RoadwaySurfaceStatus_evsn_DataSurfaceTemperatureQuantity == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("evsn-DataSurfaceTemperatureQuantity", &(value->evsn_DataSurfaceTemperatureQuantity))) < 0) return ret;
	} /* OPTIONAL end */
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_RoadwaySurfaceStatus_node_NodeIdNumber(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->node_NodeIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_RoadwaySurfaceStatus_link_LinkIdNumber(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->link_LinkIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_RoadwaySurfaceStatus_link_SurfaceConditionCode(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, ASNUINT8* user_value, ASNUINT32L user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_BITSTRING(workspace, &value->link_SurfaceConditionCode, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_RoadwaySurfaceStatus_link_LandBlockedOrClosedCode(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, ASNUINT8* user_value, ASNUINT32L user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_BITSTRING(workspace, &value->link_LandBlockedOrClosedCode, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_RoadwaySurfaceStatus_evsn_DataSurfacePrecipitationDepth(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_RoadwaySurfaceStatus_evsn_DataSurfacePrecipitationDepth = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->evsn_DataSurfacePrecipitationDepth, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_RoadwaySurfaceStatus_evsn_DataSurfaceTemperatureQuantity(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_RoadwaySurfaceStatus_evsn_DataSurfaceTemperatureQuantity = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->evsn_DataSurfaceTemperatureQuantity, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_RoadwaySurfaceStatus_node_NodeIdNumber(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->node_NodeIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_RoadwaySurfaceStatus_link_LinkIdNumber(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->link_LinkIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_RoadwaySurfaceStatus_link_SurfaceConditionCode(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, ASNUINT8** user_value, ASNUINT32L* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_BITSTRING(workspace, &value->link_SurfaceConditionCode, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_RoadwaySurfaceStatus_link_LandBlockedOrClosedCode(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, ASNUINT8** user_value, ASNUINT32L* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_BITSTRING(workspace, &value->link_LandBlockedOrClosedCode, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_RoadwaySurfaceStatus_evsn_DataSurfacePrecipitationDepth(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_RoadwaySurfaceStatus_evsn_DataSurfacePrecipitationDepth == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->evsn_DataSurfacePrecipitationDepth, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_RoadwaySurfaceStatus_evsn_DataSurfaceTemperatureQuantity(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_RoadwaySurfaceStatus_evsn_DataSurfaceTemperatureQuantity == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->evsn_DataSurfaceTemperatureQuantity, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_CHECK_RoadwaySurfaceStatus(RoadwaySurfaceStatus* value)
{
	int ret = 0;

	unsigned char checkinfo_node_NodeIdNumber[] = {
		0x02,0x01,0x28,0x00
	};
	unsigned char checkinfo_link_LinkIdNumber[] = {
		0x02,0x01,0x28,0x00
	};
	unsigned char checkinfo_link_SurfaceConditionCode[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_link_LandBlockedOrClosedCode[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_evsn_DataSurfacePrecipitationDepth[] = {
		0x02,0x00,0x82,0x0B,0xB8,0x00
	};
	unsigned char checkinfo_evsn_DataSurfaceTemperatureQuantity[] = {
		0x02,0x00,0x82,0x01,0x2C,0x00
	};

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_UTF8Str(&(value->node_NodeIdNumber), checkinfo_node_NodeIdNumber)) < 0) return ret;
	if ((ret = ASN1_CHECK_UTF8Str(&(value->link_LinkIdNumber), checkinfo_link_LinkIdNumber)) < 0) return ret;
	if ((ret = ASN1_CHECK_BITSTRING(&(value->link_SurfaceConditionCode), checkinfo_link_SurfaceConditionCode)) < 0) return ret;
	if ((ret = ASN1_CHECK_BITSTRING(&(value->link_LandBlockedOrClosedCode), checkinfo_link_LandBlockedOrClosedCode)) < 0) return ret;
	if (value->DEF_RoadwaySurfaceStatus_evsn_DataSurfacePrecipitationDepth == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->evsn_DataSurfacePrecipitationDepth), checkinfo_evsn_DataSurfacePrecipitationDepth)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_RoadwaySurfaceStatus_evsn_DataSurfaceTemperatureQuantity == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->evsn_DataSurfaceTemperatureQuantity), checkinfo_evsn_DataSurfaceTemperatureQuantity)) < 0) return ret;
	} /* OPTIONAL end */
	return ret;
}
int ASN1_BER_Data_Enc_RoadwaySurfaceStatus(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->node_NodeIdNumber), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->link_LinkIdNumber), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_BITSTRING(workspace, &(value->link_SurfaceConditionCode), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_BITSTRING(workspace, &(value->link_LandBlockedOrClosedCode), ASN1IMPL)) < 0) return ret;
	if (value->DEF_RoadwaySurfaceStatus_evsn_DataSurfacePrecipitationDepth == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->evsn_DataSurfacePrecipitationDepth), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_RoadwaySurfaceStatus_evsn_DataSurfaceTemperatureQuantity == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->evsn_DataSurfaceTemperatureQuantity), ASN1IMPL)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_RoadwaySurfaceStatus(RoadwaySurfaceStatus* value);
extern int ASN1_BER_Data_Enc_RoadwaySurfaceStatus(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_RoadwaySurfaceStatus(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_RoadwaySurfaceStatus(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_RoadwaySurfaceStatus(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_RoadwaySurfaceStatus(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	ASNUINT8* _cpointer;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->node_NodeIdNumber, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->link_LinkIdNumber, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_BITSTRING(workspace, &value->link_SurfaceConditionCode, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_BITSTRING(workspace, &value->link_LandBlockedOrClosedCode, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 4))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->evsn_DataSurfacePrecipitationDepth, len, ASN1IMPL)) < 0) return ret;

		value->DEF_RoadwaySurfaceStatus_evsn_DataSurfacePrecipitationDepth = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 5))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->evsn_DataSurfaceTemperatureQuantity, len, ASN1IMPL)) < 0) return ret;

		value->DEF_RoadwaySurfaceStatus_evsn_DataSurfaceTemperatureQuantity = 1;
	}
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if (IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_RoadwaySurfaceStatus(RoadwaySurfaceStatus* value);
extern int ASN1_BER_Data_Dec_RoadwaySurfaceStatus(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_RoadwaySurfaceStatus(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_RoadwaySurfaceStatus(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_RoadwaySurfaceStatus(value)) < 0) return ret;
	return ret;
}

/********************************************************
*RoadwaySurfaceStatusRequest                            *
********************************************************/
int ASN1_Print_RoadwaySurfaceStatusRequest(RoadwaySurfaceStatusRequest* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// Type Default
	if ((ret = ASN1_Print_UTF8Str("RoadwaySurfaceStatusRequest", value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_RoadwaySurfaceStatusRequest(RoadwaySurfaceStatusRequest* value)
{
	unsigned char checkinfo_RoadwaySurfaceStatusRequest[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_UTF8Str(value, checkinfo_RoadwaySurfaceStatusRequest)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_RoadwaySurfaceStatusRequest(ASN1WorkSpace* workspace, RoadwaySurfaceStatusRequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_RoadwaySurfaceStatusRequest(ASN1WorkSpace* workspace, RoadwaySurfaceStatusRequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_RoadwaySurfaceStatusRequest(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_RoadwaySurfaceStatusRequest(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_RoadwaySurfaceStatusRequest(ASN1WorkSpace* workspace, RoadwaySurfaceStatusRequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_RoadwaySurfaceStatusRequest(ASN1WorkSpace* workspace, RoadwaySurfaceStatusRequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_RoadwaySurfaceStatusRequest(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_RoadwaySurfaceStatusRequest(value)) < 0) return ret;
	return ret;
}

/********************************************************
*RoadwaySurfaceStatusResponse                           *
********************************************************/
int ASN1_Print_RoadwaySurfaceStatusResponse(RoadwaySurfaceStatusResponse* value, int tab_value)
{
	int ret = 0;
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	count = value->count;
	pnode = value->head->next;
	// SEQUENCE OF : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ_OF("RoadwaySurfaceStatusResponse");
	while (count) {
		// Type Reference RoadwaySurfaceStatus
		ASN_Print_TAB(tab_value + 1);
		if ((ret = ASN1_Print_RoadwaySurfaceStatus((RoadwaySurfaceStatus*)pnode->data, tab_value + 1)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}

	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_RoadwaySurfaceStatusResponse_RoadwaySurfaceStatusResponse_pdata(ASN1WorkSpace* workspace, RoadwaySurfaceStatusResponse* value, RoadwaySurfaceStatus* user_value)
{
	int ret = 0;
	RoadwaySurfaceStatus* list_value;
	if (value == NULL || user_value == NULL) return -1;
	list_value = (RoadwaySurfaceStatus*)mpool_malloc(workspace->Pmemory, sizeof(RoadwaySurfaceStatus));
	memset(list_value, 0, sizeof(RoadwaySurfaceStatus));
	memmove(list_value, user_value, sizeof(RoadwaySurfaceStatus));
	ASN1_Insert_Node(workspace, value, list_value);
	return ret;
}
int ASN1_GET_RoadwaySurfaceStatusResponse_RoadwaySurfaceStatusResponse_pdata(ASN1WorkSpace* workspace, RoadwaySurfaceStatusResponse* value, RoadwaySurfaceStatus** user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = ASN1_Get_Node(value);
	return ret;
}
extern int ASN1_CHECK_RoadwaySurfaceStatus(RoadwaySurfaceStatus* value);
int ASN1_CHECK_RoadwaySurfaceStatusResponse(RoadwaySurfaceStatusResponse* value)
{
	int ret = 0;

	unsigned char checkinfo_RoadwaySurfaceStatusResponse[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_RoadwaySurfaceStatusResponse_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		if ((ret = ASN1_CHECK_RoadwaySurfaceStatus(pnode->data)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_RoadwaySurfaceStatus(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_RoadwaySurfaceStatusResponse(ASN1WorkSpace* workspace, RoadwaySurfaceStatusResponse* value, ASN1TagType tagFlag)
{
	int ret = 0;
	ASN1ListNode* pnode;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	pnode = value->head->next;
	while (NULL != pnode)
	{
		if ((ret = ASN1_BER_Data_Enc_RoadwaySurfaceStatus(workspace, pnode->data, ASN1EXPL)) < 0) return ret;
		pnode = pnode->next;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_RoadwaySurfaceStatusResponse(RoadwaySurfaceStatusResponse* value);
extern int ASN1_BER_Data_Enc_RoadwaySurfaceStatusResponse(ASN1WorkSpace* workspace, RoadwaySurfaceStatusResponse* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_RoadwaySurfaceStatusResponse(ASN1WorkSpace* workspace, RoadwaySurfaceStatusResponse* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_RoadwaySurfaceStatusResponse(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_RoadwaySurfaceStatusResponse(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_RoadwaySurfaceStatus(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_RoadwaySurfaceStatusResponse(ASN1WorkSpace* workspace, RoadwaySurfaceStatusResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	RoadwaySurfaceStatus* pdata;
	ASNUINT8* p = workspace->buffer.current;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &length)) < 0) return ret;
	}
	if ((ret = ASN1_Creat_Init_List(workspace, value)) < 0) return ret;
	while (ASN1_BER_Dec_Isloop(workspace, p, length))
	{
		pdata = (RoadwaySurfaceStatus*)mpool_malloc(GetMemPool(workspace), sizeof(RoadwaySurfaceStatus));
		memset(pdata, 0, sizeof(RoadwaySurfaceStatus));
		if ((ret = ASN1_BER_Data_Dec_RoadwaySurfaceStatus(workspace, pdata, len, ASN1EXPL)) < 0) return ret;

		if ((ret = ASN1_Insert_Node(workspace, value, (void*)pdata)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if (IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_RoadwaySurfaceStatusResponse(RoadwaySurfaceStatusResponse* value);
extern int ASN1_BER_Data_Dec_RoadwaySurfaceStatusResponse(ASN1WorkSpace* workspace, RoadwaySurfaceStatusResponse* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_RoadwaySurfaceStatusResponse(ASN1WorkSpace* workspace, RoadwaySurfaceStatusResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_RoadwaySurfaceStatusResponse(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_RoadwaySurfaceStatusResponse(value)) < 0) return ret;
	return ret;
}

/********************************************************
*WeatherInformation                                     *
********************************************************/
int ASN1_Print_WeatherInformation(WeatherInformation* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("WeatherInformation");
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch (value->wthr_ForecastOrActualCode)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("wthr_ForecastOrActualCode", "actual", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("wthr_ForecastOrActualCode", "forecast", 1)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	if (value->DEF_WeatherInformation_wthr_TemperatureQuantity == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("wthr-TemperatureQuantity", &(value->wthr_TemperatureQuantity))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_WeatherInformation_wthr_HighTemperatureQuantity == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("wthr-HighTemperatureQuantity", &(value->wthr_HighTemperatureQuantity))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_WeatherInformation_wthr_LowTemperatureQuantity == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("wthr-LowTemperatureQuantity", &(value->wthr_LowTemperatureQuantity))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_WeatherInformation_wthr_SpecialConditions == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_BITSTRING("wthr-SpecialConditions", &(value->wthr_SpecialConditions))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_WeatherInformation_wthr_SpecialConditionsOther == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_UTF8Str("wthr-SpecialConditionsOther", &(value->wthr_SpecialConditionsOther))) < 0) return ret;
	} /* OPTIONAL end */
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("wthr-ProbabilityPercent", &(value->wthr_ProbabilityPercent))) < 0) return ret;
	if (value->DEF_WeatherInformation_wthr_VisibilityQuantity == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("wthr-VisibilityQuantity", &(value->wthr_VisibilityQuantity))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_WeatherInformation_wthr_WindSpeedQuantity == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("wthr-WindSpeedQuantity", &(value->wthr_WindSpeedQuantity))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_WeatherInformation_wthr_WindDirectionCode == 1)
	{ /*OPTIONAL start */
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		switch (value->wthr_WindDirectionCode)
		{
		case 0: if ((ret = ASN1_Print_ENUMERATED("wthr_WindDirectionCode", "north", 0)) < 0) return ret; break;
		case 1: if ((ret = ASN1_Print_ENUMERATED("wthr_WindDirectionCode", "south", 1)) < 0) return ret; break;
		case 2: if ((ret = ASN1_Print_ENUMERATED("wthr_WindDirectionCode", "west", 2)) < 0) return ret; break;
		case 3: if ((ret = ASN1_Print_ENUMERATED("wthr_WindDirectionCode", "east", 3)) < 0) return ret; break;
		case 4: if ((ret = ASN1_Print_ENUMERATED("wthr_WindDirectionCode", "northwest", 4)) < 0) return ret; break;
		case 5: if ((ret = ASN1_Print_ENUMERATED("wthr_WindDirectionCode", "northeast", 5)) < 0) return ret; break;
		case 6: if ((ret = ASN1_Print_ENUMERATED("wthr_WindDirectionCode", "southwest", 6)) < 0) return ret; break;
		case 7: if ((ret = ASN1_Print_ENUMERATED("wthr_WindDirectionCode", "southeast", 7)) < 0) return ret; break;
		default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
		};
	} /* OPTIONAL end */
	if (value->DEF_WeatherInformation_wthr_HumidityQuantity == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("wthr-HumidityQuantity", &(value->wthr_HumidityQuantity))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_WeatherInformation_wthr_PressureQuantity == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("wthr-PressureQuantity", &(value->wthr_PressureQuantity))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_WeatherInformation_wthr_SunriseTimeGeneralizedTime == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_VisibleString("wthr-SunriseTimeGeneralizedTime", &(value->wthr_SunriseTimeGeneralizedTime))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_WeatherInformation_wthr_SunsetTimeGeneralizedTime == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_VisibleString("wthr-SunsetTimeGeneralizedTime", &(value->wthr_SunsetTimeGeneralizedTime))) < 0) return ret;
	} /* OPTIONAL end */
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_WeatherInformation_wthr_ForecastOrActualCode(ASN1WorkSpace* workspace, WeatherInformation* value, ENUMERATED user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_ENUMERATED(workspace, (ASNINT32*)&value->wthr_ForecastOrActualCode, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_WeatherInformation_wthr_TemperatureQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_WeatherInformation_wthr_TemperatureQuantity = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->wthr_TemperatureQuantity, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_WeatherInformation_wthr_HighTemperatureQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_WeatherInformation_wthr_HighTemperatureQuantity = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->wthr_HighTemperatureQuantity, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_WeatherInformation_wthr_LowTemperatureQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_WeatherInformation_wthr_LowTemperatureQuantity = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->wthr_LowTemperatureQuantity, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_WeatherInformation_wthr_SpecialConditions(ASN1WorkSpace* workspace, WeatherInformation* value, ASNUINT8* user_value, ASNUINT32L user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->DEF_WeatherInformation_wthr_SpecialConditions = 1;
	if ((ret = ASN1_SET_BITSTRING(workspace, &value->wthr_SpecialConditions, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_WeatherInformation_wthr_SpecialConditionsOther(ASN1WorkSpace* workspace, WeatherInformation* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->DEF_WeatherInformation_wthr_SpecialConditionsOther = 1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->wthr_SpecialConditionsOther, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_WeatherInformation_wthr_ProbabilityPercent(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->wthr_ProbabilityPercent, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_WeatherInformation_wthr_VisibilityQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_WeatherInformation_wthr_VisibilityQuantity = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->wthr_VisibilityQuantity, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_WeatherInformation_wthr_WindSpeedQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_WeatherInformation_wthr_WindSpeedQuantity = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->wthr_WindSpeedQuantity, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_WeatherInformation_wthr_WindDirectionCode(ASN1WorkSpace* workspace, WeatherInformation* value, ENUMERATED user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_WeatherInformation_wthr_WindDirectionCode = 1;
	if ((ret = ASN1_SET_ENUMERATED(workspace, (ASNINT32*)&value->wthr_WindDirectionCode, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_WeatherInformation_wthr_HumidityQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_WeatherInformation_wthr_HumidityQuantity = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->wthr_HumidityQuantity, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_WeatherInformation_wthr_PressureQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_WeatherInformation_wthr_PressureQuantity = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->wthr_PressureQuantity, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_WeatherInformation_wthr_SunriseTimeGeneralizedTime(ASN1WorkSpace* workspace, WeatherInformation* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->DEF_WeatherInformation_wthr_SunriseTimeGeneralizedTime = 1;
	if ((ret = ASN1_SET_VisibleString(workspace, &value->wthr_SunriseTimeGeneralizedTime, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_WeatherInformation_wthr_SunsetTimeGeneralizedTime(ASN1WorkSpace* workspace, WeatherInformation* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->DEF_WeatherInformation_wthr_SunsetTimeGeneralizedTime = 1;
	if ((ret = ASN1_SET_VisibleString(workspace, &value->wthr_SunsetTimeGeneralizedTime, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_WeatherInformation_wthr_ForecastOrActualCode(ASN1WorkSpace* workspace, WeatherInformation* value, ENUMERATED* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->wthr_ForecastOrActualCode, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_WeatherInformation_wthr_TemperatureQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_WeatherInformation_wthr_TemperatureQuantity == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->wthr_TemperatureQuantity, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_WeatherInformation_wthr_HighTemperatureQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_WeatherInformation_wthr_HighTemperatureQuantity == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->wthr_HighTemperatureQuantity, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_WeatherInformation_wthr_LowTemperatureQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_WeatherInformation_wthr_LowTemperatureQuantity == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->wthr_LowTemperatureQuantity, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_WeatherInformation_wthr_SpecialConditions(ASN1WorkSpace* workspace, WeatherInformation* value, ASNUINT8** user_value, ASNUINT32L* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_WeatherInformation_wthr_SpecialConditions == 1)
	{
		if ((ret = ASN1_GET_BITSTRING(workspace, &value->wthr_SpecialConditions, user_value, user_value_length)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_WeatherInformation_wthr_SpecialConditionsOther(ASN1WorkSpace* workspace, WeatherInformation* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_WeatherInformation_wthr_SpecialConditionsOther == 1)
	{
		if ((ret = ASN1_GET_UTF8Str(workspace, &value->wthr_SpecialConditionsOther, user_value, user_value_length)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_WeatherInformation_wthr_ProbabilityPercent(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->wthr_ProbabilityPercent, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_WeatherInformation_wthr_VisibilityQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_WeatherInformation_wthr_VisibilityQuantity == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->wthr_VisibilityQuantity, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_WeatherInformation_wthr_WindSpeedQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_WeatherInformation_wthr_WindSpeedQuantity == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->wthr_WindSpeedQuantity, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_WeatherInformation_wthr_WindDirectionCode(ASN1WorkSpace* workspace, WeatherInformation* value, ENUMERATED* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_WeatherInformation_wthr_WindDirectionCode == 1)
	{
		if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->wthr_WindDirectionCode, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_WeatherInformation_wthr_HumidityQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_WeatherInformation_wthr_HumidityQuantity == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->wthr_HumidityQuantity, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_WeatherInformation_wthr_PressureQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_WeatherInformation_wthr_PressureQuantity == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->wthr_PressureQuantity, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_WeatherInformation_wthr_SunriseTimeGeneralizedTime(ASN1WorkSpace* workspace, WeatherInformation* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_WeatherInformation_wthr_SunriseTimeGeneralizedTime == 1)
	{
		if ((ret = ASN1_GET_VisibleString(workspace, &value->wthr_SunriseTimeGeneralizedTime, user_value, user_value_length)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_WeatherInformation_wthr_SunsetTimeGeneralizedTime(ASN1WorkSpace* workspace, WeatherInformation* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_WeatherInformation_wthr_SunsetTimeGeneralizedTime == 1)
	{
		if ((ret = ASN1_GET_VisibleString(workspace, &value->wthr_SunsetTimeGeneralizedTime, user_value, user_value_length)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_CHECK_WeatherInformation(WeatherInformation* value)
{
	int ret = 0;

	unsigned char checkinfo_wthr_ForecastOrActualCode[] = {
		0x02,0x00,0x01,0x00
	};
	unsigned char checkinfo_wthr_TemperatureQuantity[] = {
		0x02,0x82,0xFF,0x80,0x7F,0x00
	};
	unsigned char checkinfo_wthr_HighTemperatureQuantity[] = {
		0x02,0x82,0xFF,0x80,0x7F,0x00
	};
	unsigned char checkinfo_wthr_LowTemperatureQuantity[] = {
		0x02,0x82,0xFF,0x80,0x7F,0x00
	};
	unsigned char checkinfo_wthr_SpecialConditions[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_wthr_SpecialConditionsOther[] = {
		0x02,0x01,0x82,0x01,0x00,0x00
	};
	unsigned char checkinfo_wthr_ProbabilityPercent[] = {
		0x02,0x00,0x64,0x00
	};
	unsigned char checkinfo_wthr_VisibilityQuantity[] = {
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_wthr_WindSpeedQuantity[] = {
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_wthr_WindDirectionCode[] = {
		0x08,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x00
	};
	unsigned char checkinfo_wthr_HumidityQuantity[] = {
		0x02,0x00,0x64,0x00
	};
	unsigned char checkinfo_wthr_PressureQuantity[] = {
		0x02,0x00,0x64,0x00
	};
	unsigned char checkinfo_wthr_SunriseTimeGeneralizedTime[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_wthr_SunsetTimeGeneralizedTime[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->wthr_ForecastOrActualCode), checkinfo_wthr_ForecastOrActualCode)) < 0) return ret;
	if (value->DEF_WeatherInformation_wthr_TemperatureQuantity == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->wthr_TemperatureQuantity), checkinfo_wthr_TemperatureQuantity)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_WeatherInformation_wthr_HighTemperatureQuantity == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->wthr_HighTemperatureQuantity), checkinfo_wthr_HighTemperatureQuantity)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_WeatherInformation_wthr_LowTemperatureQuantity == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->wthr_LowTemperatureQuantity), checkinfo_wthr_LowTemperatureQuantity)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_WeatherInformation_wthr_SpecialConditions == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_BITSTRING(&(value->wthr_SpecialConditions), checkinfo_wthr_SpecialConditions)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_WeatherInformation_wthr_SpecialConditionsOther == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_UTF8Str(&(value->wthr_SpecialConditionsOther), checkinfo_wthr_SpecialConditionsOther)) < 0) return ret;
	} /* OPTIONAL end */
	if ((ret = ASN1_CHECK_INTEGER(&(value->wthr_ProbabilityPercent), checkinfo_wthr_ProbabilityPercent)) < 0) return ret;
	if (value->DEF_WeatherInformation_wthr_VisibilityQuantity == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->wthr_VisibilityQuantity), checkinfo_wthr_VisibilityQuantity)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_WeatherInformation_wthr_WindSpeedQuantity == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->wthr_WindSpeedQuantity), checkinfo_wthr_WindSpeedQuantity)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_WeatherInformation_wthr_WindDirectionCode == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->wthr_WindDirectionCode), checkinfo_wthr_WindDirectionCode)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_WeatherInformation_wthr_HumidityQuantity == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->wthr_HumidityQuantity), checkinfo_wthr_HumidityQuantity)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_WeatherInformation_wthr_PressureQuantity == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->wthr_PressureQuantity), checkinfo_wthr_PressureQuantity)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_WeatherInformation_wthr_SunriseTimeGeneralizedTime == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_VisibleString(&(value->wthr_SunriseTimeGeneralizedTime), checkinfo_wthr_SunriseTimeGeneralizedTime)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_WeatherInformation_wthr_SunsetTimeGeneralizedTime == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_VisibleString(&(value->wthr_SunsetTimeGeneralizedTime), checkinfo_wthr_SunsetTimeGeneralizedTime)) < 0) return ret;
	} /* OPTIONAL end */
	return ret;
}
int ASN1_BER_Data_Enc_WeatherInformation(ASN1WorkSpace* workspace, WeatherInformation* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32*)&(value->wthr_ForecastOrActualCode), ASN1IMPL)) < 0) return ret;
	if (value->DEF_WeatherInformation_wthr_TemperatureQuantity == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->wthr_TemperatureQuantity), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_WeatherInformation_wthr_HighTemperatureQuantity == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->wthr_HighTemperatureQuantity), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_WeatherInformation_wthr_LowTemperatureQuantity == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->wthr_LowTemperatureQuantity), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_WeatherInformation_wthr_SpecialConditions == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_BITSTRING(workspace, &(value->wthr_SpecialConditions), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_WeatherInformation_wthr_SpecialConditionsOther == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->wthr_SpecialConditionsOther), ASN1IMPL)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 6)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->wthr_ProbabilityPercent), ASN1IMPL)) < 0) return ret;
	if (value->DEF_WeatherInformation_wthr_VisibilityQuantity == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 7)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->wthr_VisibilityQuantity), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_WeatherInformation_wthr_WindSpeedQuantity == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 8)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->wthr_WindSpeedQuantity), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_WeatherInformation_wthr_WindDirectionCode == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 9)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32*)&(value->wthr_WindDirectionCode), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_WeatherInformation_wthr_HumidityQuantity == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 10)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->wthr_HumidityQuantity), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_WeatherInformation_wthr_PressureQuantity == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 11)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->wthr_PressureQuantity), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_WeatherInformation_wthr_SunriseTimeGeneralizedTime == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 12)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_VisibleString(workspace, &(value->wthr_SunriseTimeGeneralizedTime), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_WeatherInformation_wthr_SunsetTimeGeneralizedTime == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 13)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_VisibleString(workspace, &(value->wthr_SunsetTimeGeneralizedTime), ASN1IMPL)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_WeatherInformation(WeatherInformation* value);
extern int ASN1_BER_Data_Enc_WeatherInformation(ASN1WorkSpace* workspace, WeatherInformation* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_WeatherInformation(ASN1WorkSpace* workspace, WeatherInformation* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_WeatherInformation(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_WeatherInformation(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_WeatherInformation(ASN1WorkSpace* workspace, WeatherInformation* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	ASNUINT8* _cpointer;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)&value->wthr_ForecastOrActualCode, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 1))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->wthr_TemperatureQuantity, len, ASN1IMPL)) < 0) return ret;

		value->DEF_WeatherInformation_wthr_TemperatureQuantity = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 2))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->wthr_HighTemperatureQuantity, len, ASN1IMPL)) < 0) return ret;

		value->DEF_WeatherInformation_wthr_HighTemperatureQuantity = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 3))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->wthr_LowTemperatureQuantity, len, ASN1IMPL)) < 0) return ret;

		value->DEF_WeatherInformation_wthr_LowTemperatureQuantity = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 4))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_BITSTRING(workspace, &value->wthr_SpecialConditions, len, ASN1IMPL)) < 0) return ret;

		value->DEF_WeatherInformation_wthr_SpecialConditions = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 5))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->wthr_SpecialConditionsOther, len, ASN1IMPL)) < 0) return ret;

		value->DEF_WeatherInformation_wthr_SpecialConditionsOther = 1;
	}
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 6)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->wthr_ProbabilityPercent, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 7))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 7)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->wthr_VisibilityQuantity, len, ASN1IMPL)) < 0) return ret;

		value->DEF_WeatherInformation_wthr_VisibilityQuantity = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 8))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 8)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->wthr_WindSpeedQuantity, len, ASN1IMPL)) < 0) return ret;

		value->DEF_WeatherInformation_wthr_WindSpeedQuantity = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 9))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 9)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)&value->wthr_WindDirectionCode, len, ASN1IMPL)) < 0) return ret;

		value->DEF_WeatherInformation_wthr_WindDirectionCode = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 10))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 10)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->wthr_HumidityQuantity, len, ASN1IMPL)) < 0) return ret;

		value->DEF_WeatherInformation_wthr_HumidityQuantity = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 11))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 11)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->wthr_PressureQuantity, len, ASN1IMPL)) < 0) return ret;

		value->DEF_WeatherInformation_wthr_PressureQuantity = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 12))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 12)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_VisibleString(workspace, &value->wthr_SunriseTimeGeneralizedTime, len, ASN1IMPL)) < 0) return ret;

		value->DEF_WeatherInformation_wthr_SunriseTimeGeneralizedTime = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 13))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 13)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_VisibleString(workspace, &value->wthr_SunsetTimeGeneralizedTime, len, ASN1IMPL)) < 0) return ret;

		value->DEF_WeatherInformation_wthr_SunsetTimeGeneralizedTime = 1;
	}
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if (IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_WeatherInformation(WeatherInformation* value);
extern int ASN1_BER_Data_Dec_WeatherInformation(ASN1WorkSpace* workspace, WeatherInformation* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_WeatherInformation(ASN1WorkSpace* workspace, WeatherInformation* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_WeatherInformation(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_WeatherInformation(value)) < 0) return ret;
	return ret;
}

/********************************************************
*WeatherInformationRequest                              *
********************************************************/
int ASN1_Print_WeatherInformationRequest(WeatherInformationRequest* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// Type Default
	if ((ret = ASN1_Print_UTF8Str("WeatherInformationRequest", value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_WeatherInformationRequest(WeatherInformationRequest* value)
{
	unsigned char checkinfo_WeatherInformationRequest[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_UTF8Str(value, checkinfo_WeatherInformationRequest)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_WeatherInformationRequest(ASN1WorkSpace* workspace, WeatherInformationRequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_WeatherInformationRequest(ASN1WorkSpace* workspace, WeatherInformationRequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_WeatherInformationRequest(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_WeatherInformationRequest(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_WeatherInformationRequest(ASN1WorkSpace* workspace, WeatherInformationRequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_WeatherInformationRequest(ASN1WorkSpace* workspace, WeatherInformationRequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_WeatherInformationRequest(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_WeatherInformationRequest(value)) < 0) return ret;
	return ret;
}

/********************************************************
*WeatherInformationResponse                             *
********************************************************/
int ASN1_Print_WeatherInformationResponse(WeatherInformationResponse* value, int tab_value)
{
	int ret = 0;
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	count = value->count;
	pnode = value->head->next;
	// SEQUENCE OF : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ_OF("WeatherInformationResponse");
	while (count) {
		// Type Reference WeatherInformation
		ASN_Print_TAB(tab_value + 1);
		if ((ret = ASN1_Print_WeatherInformation((WeatherInformation*)pnode->data, tab_value + 1)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}

	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_WeatherInformationResponse_WeatherInformationResponse_pdata(ASN1WorkSpace* workspace, WeatherInformationResponse* value, WeatherInformation* user_value)
{
	int ret = 0;
	WeatherInformation* list_value;
	if (value == NULL || user_value == NULL) return -1;
	list_value = (WeatherInformation*)mpool_malloc(workspace->Pmemory, sizeof(WeatherInformation));
	memset(list_value, 0, sizeof(WeatherInformation));
	memmove(list_value, user_value, sizeof(WeatherInformation));
	ASN1_Insert_Node(workspace, value, list_value);
	return ret;
}
int ASN1_GET_WeatherInformationResponse_WeatherInformationResponse_pdata(ASN1WorkSpace* workspace, WeatherInformationResponse* value, WeatherInformation** user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = ASN1_Get_Node(value);
	return ret;
}
extern int ASN1_CHECK_WeatherInformation(WeatherInformation* value);
int ASN1_CHECK_WeatherInformationResponse(WeatherInformationResponse* value)
{
	int ret = 0;

	unsigned char checkinfo_WeatherInformationResponse[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_WeatherInformationResponse_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		if ((ret = ASN1_CHECK_WeatherInformation(pnode->data)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_WeatherInformation(ASN1WorkSpace* workspace, WeatherInformation* value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_WeatherInformationResponse(ASN1WorkSpace* workspace, WeatherInformationResponse* value, ASN1TagType tagFlag)
{
	int ret = 0;
	ASN1ListNode* pnode;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	pnode = value->head->next;
	while (NULL != pnode)
	{
		if ((ret = ASN1_BER_Data_Enc_WeatherInformation(workspace, pnode->data, ASN1EXPL)) < 0) return ret;
		pnode = pnode->next;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_WeatherInformationResponse(WeatherInformationResponse* value);
extern int ASN1_BER_Data_Enc_WeatherInformationResponse(ASN1WorkSpace* workspace, WeatherInformationResponse* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_WeatherInformationResponse(ASN1WorkSpace* workspace, WeatherInformationResponse* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_WeatherInformationResponse(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_WeatherInformationResponse(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_WeatherInformation(ASN1WorkSpace* workspace, WeatherInformation* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_WeatherInformationResponse(ASN1WorkSpace* workspace, WeatherInformationResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	WeatherInformation* pdata;
	ASNUINT8* p = workspace->buffer.current;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &length)) < 0) return ret;
	}
	if ((ret = ASN1_Creat_Init_List(workspace, value)) < 0) return ret;
	while (ASN1_BER_Dec_Isloop(workspace, p, length))
	{
		pdata = (WeatherInformation*)mpool_malloc(GetMemPool(workspace), sizeof(WeatherInformation));
		memset(pdata, 0, sizeof(WeatherInformation));
		if ((ret = ASN1_BER_Data_Dec_WeatherInformation(workspace, pdata, len, ASN1EXPL)) < 0) return ret;

		if ((ret = ASN1_Insert_Node(workspace, value, (void*)pdata)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if (IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_WeatherInformationResponse(WeatherInformationResponse* value);
extern int ASN1_BER_Data_Dec_WeatherInformationResponse(ASN1WorkSpace* workspace, WeatherInformationResponse* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_WeatherInformationResponse(ASN1WorkSpace* workspace, WeatherInformationResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_WeatherInformationResponse(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_WeatherInformationResponse(value)) < 0) return ret;
	return ret;
}

/********************************************************
*LinkRoadwayGeometry                                    *
********************************************************/
int ASN1_Print_LinkRoadwayGeometry(LinkRoadwayGeometry* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("LinkRoadwayGeometry");
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("link-BeginNodeIdNumber", &(value->link_BeginNodeIdNumber))) < 0) return ret;
	if (value->DEF_LinkRoadwayGeometry_link_BiginNodeLatitudeLocation == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("link-BiginNodeLatitudeLocation", &(value->link_BiginNodeLatitudeLocation))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_LinkRoadwayGeometry_link_BeginNodeLongitudeLocation == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("link-BeginNodeLongitudeLocation", &(value->link_BeginNodeLongitudeLocation))) < 0) return ret;
	} /* OPTIONAL end */
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("link-EndNodeIdNumber", &(value->link_EndNodeIdNumber))) < 0) return ret;
	if (value->DEF_LinkRoadwayGeometry_link_EndNodeLatitudeLocation == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("link-EndNodeLatitudeLocation", &(value->link_EndNodeLatitudeLocation))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_LinkRoadwayGeometry_link_EndNodeLongitudeLocation == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("link-EndNodeLongitudeLocation", &(value->link_EndNodeLongitudeLocation))) < 0) return ret;
	} /* OPTIONAL end */
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("link-JurisdictionText", &(value->link_JurisdictionText))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_BITSTRING("link-TypeCode", &(value->link_TypeCode))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("link-NameText", &(value->link_NameText))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("link-LengthQuantity", &(value->link_LengthQuantity))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_BITSTRING("link-PavementTypeCode", &(value->link_PavementTypeCode))) < 0) return ret;
	if (value->DEF_LinkRoadwayGeometry_tfmg_LinkHeigthRestrictionQunatity == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("tfmg-LinkHeigthRestrictionQunatity", &(value->tfmg_LinkHeigthRestrictionQunatity))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_LinkRoadwayGeometry_tfmg_LinkLeftShoulderWidthQuantity == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("tfmg-LinkLeftShoulderWidthQuantity", &(value->tfmg_LinkLeftShoulderWidthQuantity))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_LinkRoadwayGeometry_tfmg_LinkLengthRestrictionQuatity == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("tfmg-LinkLengthRestrictionQuatity", &(value->tfmg_LinkLengthRestrictionQuatity))) < 0) return ret;
	} /* OPTIONAL end */
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch (value->tfmg_LinkMedianTypeCode)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("tfmg_LinkMedianTypeCode", "opengrass", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("tfmg_LinkMedianTypeCode", "opensand", 1)) < 0) return ret; break;
	case 2: if ((ret = ASN1_Print_ENUMERATED("tfmg_LinkMedianTypeCode", "concrete-barrier-with-visibility-screens", 2)) < 0) return ret; break;
	case 3: if ((ret = ASN1_Print_ENUMERATED("tfmg_LinkMedianTypeCode", "separate-roadways", 3)) < 0) return ret; break;
	case 4: if ((ret = ASN1_Print_ENUMERATED("tfmg_LinkMedianTypeCode", "no-separation", 4)) < 0) return ret; break;
	case 5: if ((ret = ASN1_Print_ENUMERATED("tfmg_LinkMedianTypeCode", "painted-median-no-access", 5)) < 0) return ret; break;
	case 6: if ((ret = ASN1_Print_ENUMERATED("tfmg_LinkMedianTypeCode", "painted-MedianLeft-Turns", 6)) < 0) return ret; break;
	case 7: if ((ret = ASN1_Print_ENUMERATED("tfmg_LinkMedianTypeCode", "concrete-barrier", 7)) < 0) return ret; break;
	case 8: if ((ret = ASN1_Print_ENUMERATED("tfmg_LinkMedianTypeCode", "guardrail", 8)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("tfmg-LinkNumLanesNumber", &(value->tfmg_LinkNumLanesNumber))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("tfmg-LinkNumLanesOpenNumber", &(value->tfmg_LinkNumLanesOpenNumber))) < 0) return ret;
	if (value->DEF_LinkRoadwayGeometry_tfmg_LinkRightShoulderWidthQuantity == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("tfmg-LinkRightShoulderWidthQuantity", &(value->tfmg_LinkRightShoulderWidthQuantity))) < 0) return ret;
	} /* OPTIONAL end */
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_LinkRoadwayGeometry_link_BeginNodeIdNumber(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->link_BeginNodeIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_LinkRoadwayGeometry_link_BiginNodeLatitudeLocation(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_LinkRoadwayGeometry_link_BiginNodeLatitudeLocation = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->link_BiginNodeLatitudeLocation, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_LinkRoadwayGeometry_link_BeginNodeLongitudeLocation(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_LinkRoadwayGeometry_link_BeginNodeLongitudeLocation = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->link_BeginNodeLongitudeLocation, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_LinkRoadwayGeometry_link_EndNodeIdNumber(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->link_EndNodeIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_LinkRoadwayGeometry_link_EndNodeLatitudeLocation(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_LinkRoadwayGeometry_link_EndNodeLatitudeLocation = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->link_EndNodeLatitudeLocation, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_LinkRoadwayGeometry_link_EndNodeLongitudeLocation(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_LinkRoadwayGeometry_link_EndNodeLongitudeLocation = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->link_EndNodeLongitudeLocation, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_LinkRoadwayGeometry_link_JurisdictionText(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->link_JurisdictionText, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_LinkRoadwayGeometry_link_TypeCode(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASNUINT8* user_value, ASNUINT32L user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_BITSTRING(workspace, &value->link_TypeCode, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_LinkRoadwayGeometry_link_NameText(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->link_NameText, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_LinkRoadwayGeometry_link_LengthQuantity(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->link_LengthQuantity, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_LinkRoadwayGeometry_link_PavementTypeCode(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASNUINT8* user_value, ASNUINT32L user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_BITSTRING(workspace, &value->link_PavementTypeCode, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_LinkRoadwayGeometry_tfmg_LinkHeigthRestrictionQunatity(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_LinkRoadwayGeometry_tfmg_LinkHeigthRestrictionQunatity = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->tfmg_LinkHeigthRestrictionQunatity, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_LinkRoadwayGeometry_tfmg_LinkLeftShoulderWidthQuantity(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_LinkRoadwayGeometry_tfmg_LinkLeftShoulderWidthQuantity = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->tfmg_LinkLeftShoulderWidthQuantity, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_LinkRoadwayGeometry_tfmg_LinkLengthRestrictionQuatity(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_LinkRoadwayGeometry_tfmg_LinkLengthRestrictionQuatity = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->tfmg_LinkLengthRestrictionQuatity, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_LinkRoadwayGeometry_tfmg_LinkMedianTypeCode(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ENUMERATED user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_ENUMERATED(workspace, (ASNINT32*)&value->tfmg_LinkMedianTypeCode, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_LinkRoadwayGeometry_tfmg_LinkNumLanesNumber(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->tfmg_LinkNumLanesNumber, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_LinkRoadwayGeometry_tfmg_LinkNumLanesOpenNumber(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->tfmg_LinkNumLanesOpenNumber, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_LinkRoadwayGeometry_tfmg_LinkRightShoulderWidthQuantity(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_LinkRoadwayGeometry_tfmg_LinkRightShoulderWidthQuantity = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->tfmg_LinkRightShoulderWidthQuantity, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_LinkRoadwayGeometry_link_BeginNodeIdNumber(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->link_BeginNodeIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_LinkRoadwayGeometry_link_BiginNodeLatitudeLocation(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_LinkRoadwayGeometry_link_BiginNodeLatitudeLocation == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->link_BiginNodeLatitudeLocation, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_LinkRoadwayGeometry_link_BeginNodeLongitudeLocation(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_LinkRoadwayGeometry_link_BeginNodeLongitudeLocation == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->link_BeginNodeLongitudeLocation, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_LinkRoadwayGeometry_link_EndNodeIdNumber(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->link_EndNodeIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_LinkRoadwayGeometry_link_EndNodeLatitudeLocation(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_LinkRoadwayGeometry_link_EndNodeLatitudeLocation == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->link_EndNodeLatitudeLocation, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_LinkRoadwayGeometry_link_EndNodeLongitudeLocation(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_LinkRoadwayGeometry_link_EndNodeLongitudeLocation == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->link_EndNodeLongitudeLocation, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_LinkRoadwayGeometry_link_JurisdictionText(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->link_JurisdictionText, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_LinkRoadwayGeometry_link_TypeCode(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASNUINT8** user_value, ASNUINT32L* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_BITSTRING(workspace, &value->link_TypeCode, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_LinkRoadwayGeometry_link_NameText(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->link_NameText, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_LinkRoadwayGeometry_link_LengthQuantity(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->link_LengthQuantity, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_LinkRoadwayGeometry_link_PavementTypeCode(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASNUINT8** user_value, ASNUINT32L* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_BITSTRING(workspace, &value->link_PavementTypeCode, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_LinkRoadwayGeometry_tfmg_LinkHeigthRestrictionQunatity(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_LinkRoadwayGeometry_tfmg_LinkHeigthRestrictionQunatity == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->tfmg_LinkHeigthRestrictionQunatity, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_LinkRoadwayGeometry_tfmg_LinkLeftShoulderWidthQuantity(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_LinkRoadwayGeometry_tfmg_LinkLeftShoulderWidthQuantity == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->tfmg_LinkLeftShoulderWidthQuantity, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_LinkRoadwayGeometry_tfmg_LinkLengthRestrictionQuatity(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_LinkRoadwayGeometry_tfmg_LinkLengthRestrictionQuatity == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->tfmg_LinkLengthRestrictionQuatity, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_LinkRoadwayGeometry_tfmg_LinkMedianTypeCode(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ENUMERATED* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->tfmg_LinkMedianTypeCode, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_LinkRoadwayGeometry_tfmg_LinkNumLanesNumber(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->tfmg_LinkNumLanesNumber, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_LinkRoadwayGeometry_tfmg_LinkNumLanesOpenNumber(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->tfmg_LinkNumLanesOpenNumber, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_LinkRoadwayGeometry_tfmg_LinkRightShoulderWidthQuantity(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_LinkRoadwayGeometry_tfmg_LinkRightShoulderWidthQuantity == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->tfmg_LinkRightShoulderWidthQuantity, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_CHECK_LinkRoadwayGeometry(LinkRoadwayGeometry* value)
{
	int ret = 0;

	unsigned char checkinfo_link_BeginNodeIdNumber[] = {
		0x02,0x01,0x28,0x00
	};
	unsigned char checkinfo_link_BiginNodeLatitudeLocation[] = {
		0x02,0x85,0xFF,0x00,0x00,0x00,0x01,0x85,0xFF,0x4D,0x2F,0xA2,0x00,0x00
	};
	unsigned char checkinfo_link_BeginNodeLongitudeLocation[] = {
		0x02,0x85,0x00,0xB2,0xD0,0x5E,0x00,0x85,0x00,0xFF,0xFF,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_link_EndNodeIdNumber[] = {
		0x02,0x01,0x28,0x00
	};
	unsigned char checkinfo_link_EndNodeLatitudeLocation[] = {
		0x02,0x85,0xFF,0x00,0x00,0x00,0x01,0x85,0xFF,0x4D,0x2F,0xA2,0x00,0x00
	};
	unsigned char checkinfo_link_EndNodeLongitudeLocation[] = {
		0x02,0x85,0x00,0xB2,0xD0,0x5E,0x00,0x85,0x00,0xFF,0xFF,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_link_JurisdictionText[] = {
		0x02,0x01,0x82,0x01,0x00,0x00
	};
	unsigned char checkinfo_link_TypeCode[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_link_NameText[] = {
		0x02,0x01,0x82,0x01,0x00,0x00
	};
	unsigned char checkinfo_link_LengthQuantity[] = {
		0x02,0x00,0x83,0x02,0x71,0x00,0x00
	};
	unsigned char checkinfo_link_PavementTypeCode[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_tfmg_LinkHeigthRestrictionQunatity[] = {
		0x02,0x01,0x82,0x07,0xD0,0x00
	};
	unsigned char checkinfo_tfmg_LinkLeftShoulderWidthQuantity[] = {
		0x02,0x01,0x82,0x03,0xE7,0x00
	};
	unsigned char checkinfo_tfmg_LinkLengthRestrictionQuatity[] = {
		0x02,0x01,0x82,0x17,0x70,0x00
	};
	unsigned char checkinfo_tfmg_LinkMedianTypeCode[] = {
		0x09,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x00
	};
	unsigned char checkinfo_tfmg_LinkNumLanesNumber[] = {
		0x02,0x01,0x82,0x01,0x2C,0x00
	};
	unsigned char checkinfo_tfmg_LinkNumLanesOpenNumber[] = {
		0x02,0x01,0x32,0x00
	};
	unsigned char checkinfo_tfmg_LinkRightShoulderWidthQuantity[] = {
		0x02,0x01,0x82,0x03,0xE7,0x00
	};

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_UTF8Str(&(value->link_BeginNodeIdNumber), checkinfo_link_BeginNodeIdNumber)) < 0) return ret;
	if (value->DEF_LinkRoadwayGeometry_link_BiginNodeLatitudeLocation == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->link_BiginNodeLatitudeLocation), checkinfo_link_BiginNodeLatitudeLocation)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_LinkRoadwayGeometry_link_BeginNodeLongitudeLocation == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->link_BeginNodeLongitudeLocation), checkinfo_link_BeginNodeLongitudeLocation)) < 0) return ret;
	} /* OPTIONAL end */
	if ((ret = ASN1_CHECK_UTF8Str(&(value->link_EndNodeIdNumber), checkinfo_link_EndNodeIdNumber)) < 0) return ret;
	if (value->DEF_LinkRoadwayGeometry_link_EndNodeLatitudeLocation == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->link_EndNodeLatitudeLocation), checkinfo_link_EndNodeLatitudeLocation)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_LinkRoadwayGeometry_link_EndNodeLongitudeLocation == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->link_EndNodeLongitudeLocation), checkinfo_link_EndNodeLongitudeLocation)) < 0) return ret;
	} /* OPTIONAL end */
	if ((ret = ASN1_CHECK_UTF8Str(&(value->link_JurisdictionText), checkinfo_link_JurisdictionText)) < 0) return ret;
	if ((ret = ASN1_CHECK_BITSTRING(&(value->link_TypeCode), checkinfo_link_TypeCode)) < 0) return ret;
	if ((ret = ASN1_CHECK_UTF8Str(&(value->link_NameText), checkinfo_link_NameText)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->link_LengthQuantity), checkinfo_link_LengthQuantity)) < 0) return ret;
	if ((ret = ASN1_CHECK_BITSTRING(&(value->link_PavementTypeCode), checkinfo_link_PavementTypeCode)) < 0) return ret;
	if (value->DEF_LinkRoadwayGeometry_tfmg_LinkHeigthRestrictionQunatity == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->tfmg_LinkHeigthRestrictionQunatity), checkinfo_tfmg_LinkHeigthRestrictionQunatity)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_LinkRoadwayGeometry_tfmg_LinkLeftShoulderWidthQuantity == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->tfmg_LinkLeftShoulderWidthQuantity), checkinfo_tfmg_LinkLeftShoulderWidthQuantity)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_LinkRoadwayGeometry_tfmg_LinkLengthRestrictionQuatity == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->tfmg_LinkLengthRestrictionQuatity), checkinfo_tfmg_LinkLengthRestrictionQuatity)) < 0) return ret;
	} /* OPTIONAL end */
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->tfmg_LinkMedianTypeCode), checkinfo_tfmg_LinkMedianTypeCode)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->tfmg_LinkNumLanesNumber), checkinfo_tfmg_LinkNumLanesNumber)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->tfmg_LinkNumLanesOpenNumber), checkinfo_tfmg_LinkNumLanesOpenNumber)) < 0) return ret;
	if (value->DEF_LinkRoadwayGeometry_tfmg_LinkRightShoulderWidthQuantity == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->tfmg_LinkRightShoulderWidthQuantity), checkinfo_tfmg_LinkRightShoulderWidthQuantity)) < 0) return ret;
	} /* OPTIONAL end */
	return ret;
}
int ASN1_BER_Data_Enc_LinkRoadwayGeometry(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->link_BeginNodeIdNumber), ASN1IMPL)) < 0) return ret;
	if (value->DEF_LinkRoadwayGeometry_link_BiginNodeLatitudeLocation == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->link_BiginNodeLatitudeLocation), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_LinkRoadwayGeometry_link_BeginNodeLongitudeLocation == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->link_BeginNodeLongitudeLocation), ASN1IMPL)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->link_EndNodeIdNumber), ASN1IMPL)) < 0) return ret;
	if (value->DEF_LinkRoadwayGeometry_link_EndNodeLatitudeLocation == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->link_EndNodeLatitudeLocation), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_LinkRoadwayGeometry_link_EndNodeLongitudeLocation == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->link_EndNodeLongitudeLocation), ASN1IMPL)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 6)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->link_JurisdictionText), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 7)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_BITSTRING(workspace, &(value->link_TypeCode), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 8)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->link_NameText), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 9)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->link_LengthQuantity), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 10)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_BITSTRING(workspace, &(value->link_PavementTypeCode), ASN1IMPL)) < 0) return ret;
	if (value->DEF_LinkRoadwayGeometry_tfmg_LinkHeigthRestrictionQunatity == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 11)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->tfmg_LinkHeigthRestrictionQunatity), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_LinkRoadwayGeometry_tfmg_LinkLeftShoulderWidthQuantity == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 12)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->tfmg_LinkLeftShoulderWidthQuantity), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_LinkRoadwayGeometry_tfmg_LinkLengthRestrictionQuatity == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 13)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->tfmg_LinkLengthRestrictionQuatity), ASN1IMPL)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 14)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32*)&(value->tfmg_LinkMedianTypeCode), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 15)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->tfmg_LinkNumLanesNumber), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 16)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->tfmg_LinkNumLanesOpenNumber), ASN1IMPL)) < 0) return ret;
	if (value->DEF_LinkRoadwayGeometry_tfmg_LinkRightShoulderWidthQuantity == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 17)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->tfmg_LinkRightShoulderWidthQuantity), ASN1IMPL)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_LinkRoadwayGeometry(LinkRoadwayGeometry* value);
extern int ASN1_BER_Data_Enc_LinkRoadwayGeometry(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_LinkRoadwayGeometry(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_LinkRoadwayGeometry(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_LinkRoadwayGeometry(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_LinkRoadwayGeometry(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	ASNUINT8* _cpointer;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->link_BeginNodeIdNumber, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 1))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->link_BiginNodeLatitudeLocation, len, ASN1IMPL)) < 0) return ret;

		value->DEF_LinkRoadwayGeometry_link_BiginNodeLatitudeLocation = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 2))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->link_BeginNodeLongitudeLocation, len, ASN1IMPL)) < 0) return ret;

		value->DEF_LinkRoadwayGeometry_link_BeginNodeLongitudeLocation = 1;
	}
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->link_EndNodeIdNumber, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 4))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->link_EndNodeLatitudeLocation, len, ASN1IMPL)) < 0) return ret;

		value->DEF_LinkRoadwayGeometry_link_EndNodeLatitudeLocation = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 5))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->link_EndNodeLongitudeLocation, len, ASN1IMPL)) < 0) return ret;

		value->DEF_LinkRoadwayGeometry_link_EndNodeLongitudeLocation = 1;
	}
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 6)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->link_JurisdictionText, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 7)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_BITSTRING(workspace, &value->link_TypeCode, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 8)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->link_NameText, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 9)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->link_LengthQuantity, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 10)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_BITSTRING(workspace, &value->link_PavementTypeCode, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 11))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 11)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->tfmg_LinkHeigthRestrictionQunatity, len, ASN1IMPL)) < 0) return ret;

		value->DEF_LinkRoadwayGeometry_tfmg_LinkHeigthRestrictionQunatity = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 12))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 12)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->tfmg_LinkLeftShoulderWidthQuantity, len, ASN1IMPL)) < 0) return ret;

		value->DEF_LinkRoadwayGeometry_tfmg_LinkLeftShoulderWidthQuantity = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 13))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 13)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->tfmg_LinkLengthRestrictionQuatity, len, ASN1IMPL)) < 0) return ret;

		value->DEF_LinkRoadwayGeometry_tfmg_LinkLengthRestrictionQuatity = 1;
	}
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 14)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)&value->tfmg_LinkMedianTypeCode, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 15)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->tfmg_LinkNumLanesNumber, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 16)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->tfmg_LinkNumLanesOpenNumber, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 17))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 17)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->tfmg_LinkRightShoulderWidthQuantity, len, ASN1IMPL)) < 0) return ret;

		value->DEF_LinkRoadwayGeometry_tfmg_LinkRightShoulderWidthQuantity = 1;
	}
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if (IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_LinkRoadwayGeometry(LinkRoadwayGeometry* value);
extern int ASN1_BER_Data_Dec_LinkRoadwayGeometry(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_LinkRoadwayGeometry(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_LinkRoadwayGeometry(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_LinkRoadwayGeometry(value)) < 0) return ret;
	return ret;
}

/********************************************************
*LinkRoadwayGeometryRequest                             *
********************************************************/
int ASN1_Print_LinkRoadwayGeometryRequest(LinkRoadwayGeometryRequest* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// Type Default
	if ((ret = ASN1_Print_UTF8Str("LinkRoadwayGeometryRequest", value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_LinkRoadwayGeometryRequest(LinkRoadwayGeometryRequest* value)
{
	unsigned char checkinfo_LinkRoadwayGeometryRequest[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_UTF8Str(value, checkinfo_LinkRoadwayGeometryRequest)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_LinkRoadwayGeometryRequest(ASN1WorkSpace* workspace, LinkRoadwayGeometryRequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_LinkRoadwayGeometryRequest(ASN1WorkSpace* workspace, LinkRoadwayGeometryRequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_LinkRoadwayGeometryRequest(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_LinkRoadwayGeometryRequest(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_LinkRoadwayGeometryRequest(ASN1WorkSpace* workspace, LinkRoadwayGeometryRequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_LinkRoadwayGeometryRequest(ASN1WorkSpace* workspace, LinkRoadwayGeometryRequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_LinkRoadwayGeometryRequest(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_LinkRoadwayGeometryRequest(value)) < 0) return ret;
	return ret;
}

/********************************************************
*LinkRoadwayGeometryResponse                            *
********************************************************/
int ASN1_Print_LinkRoadwayGeometryResponse(LinkRoadwayGeometryResponse* value, int tab_value)
{
	int ret = 0;
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	count = value->count;
	pnode = value->head->next;
	// SEQUENCE OF : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ_OF("LinkRoadwayGeometryResponse");
	while (count) {
		// Type Reference LinkRoadwayGeometry
		ASN_Print_TAB(tab_value + 1);
		if ((ret = ASN1_Print_LinkRoadwayGeometry((LinkRoadwayGeometry*)pnode->data, tab_value + 1)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}

	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_LinkRoadwayGeometryResponse_LinkRoadwayGeometryResponse_pdata(ASN1WorkSpace* workspace, LinkRoadwayGeometryResponse* value, LinkRoadwayGeometry* user_value)
{
	int ret = 0;
	LinkRoadwayGeometry* list_value;
	if (value == NULL || user_value == NULL) return -1;
	list_value = (LinkRoadwayGeometry*)mpool_malloc(workspace->Pmemory, sizeof(LinkRoadwayGeometry));
	memset(list_value, 0, sizeof(LinkRoadwayGeometry));
	memmove(list_value, user_value, sizeof(LinkRoadwayGeometry));
	ASN1_Insert_Node(workspace, value, list_value);
	return ret;
}
int ASN1_GET_LinkRoadwayGeometryResponse_LinkRoadwayGeometryResponse_pdata(ASN1WorkSpace* workspace, LinkRoadwayGeometryResponse* value, LinkRoadwayGeometry** user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = ASN1_Get_Node(value);
	return ret;
}
extern int ASN1_CHECK_LinkRoadwayGeometry(LinkRoadwayGeometry* value);
int ASN1_CHECK_LinkRoadwayGeometryResponse(LinkRoadwayGeometryResponse* value)
{
	int ret = 0;

	unsigned char checkinfo_LinkRoadwayGeometryResponse[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_LinkRoadwayGeometryResponse_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		if ((ret = ASN1_CHECK_LinkRoadwayGeometry(pnode->data)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_LinkRoadwayGeometry(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_LinkRoadwayGeometryResponse(ASN1WorkSpace* workspace, LinkRoadwayGeometryResponse* value, ASN1TagType tagFlag)
{
	int ret = 0;
	ASN1ListNode* pnode;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	pnode = value->head->next;
	while (NULL != pnode)
	{
		if ((ret = ASN1_BER_Data_Enc_LinkRoadwayGeometry(workspace, pnode->data, ASN1EXPL)) < 0) return ret;
		pnode = pnode->next;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_LinkRoadwayGeometryResponse(LinkRoadwayGeometryResponse* value);
extern int ASN1_BER_Data_Enc_LinkRoadwayGeometryResponse(ASN1WorkSpace* workspace, LinkRoadwayGeometryResponse* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_LinkRoadwayGeometryResponse(ASN1WorkSpace* workspace, LinkRoadwayGeometryResponse* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_LinkRoadwayGeometryResponse(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_LinkRoadwayGeometryResponse(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_LinkRoadwayGeometry(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_LinkRoadwayGeometryResponse(ASN1WorkSpace* workspace, LinkRoadwayGeometryResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	LinkRoadwayGeometry* pdata;
	ASNUINT8* p = workspace->buffer.current;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &length)) < 0) return ret;
	}
	if ((ret = ASN1_Creat_Init_List(workspace, value)) < 0) return ret;
	while (ASN1_BER_Dec_Isloop(workspace, p, length))
	{
		pdata = (LinkRoadwayGeometry*)mpool_malloc(GetMemPool(workspace), sizeof(LinkRoadwayGeometry));
		memset(pdata, 0, sizeof(LinkRoadwayGeometry));
		if ((ret = ASN1_BER_Data_Dec_LinkRoadwayGeometry(workspace, pdata, len, ASN1EXPL)) < 0) return ret;

		if ((ret = ASN1_Insert_Node(workspace, value, (void*)pdata)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if (IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_LinkRoadwayGeometryResponse(LinkRoadwayGeometryResponse* value);
extern int ASN1_BER_Data_Dec_LinkRoadwayGeometryResponse(ASN1WorkSpace* workspace, LinkRoadwayGeometryResponse* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_LinkRoadwayGeometryResponse(ASN1WorkSpace* workspace, LinkRoadwayGeometryResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_LinkRoadwayGeometryResponse(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_LinkRoadwayGeometryResponse(value)) < 0) return ret;
	return ret;
}

/********************************************************
*ProbeVehicleDetection                                  *
********************************************************/
int ASN1_Print_ProbeVehicleDetection(ProbeVehicleDetection* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("ProbeVehicleDetection");
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("vpbd-VehicleIdNumber", &(value->vpbd_VehicleIdNumber))) < 0) return ret;
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch (value->vpbd_VehicleClass)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("vpbd_VehicleClass", "other-no-additional-information-required", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("vpbd_VehicleClass", "other-additional-information-required", 1)) < 0) return ret; break;
	case 2: if ((ret = ASN1_Print_ENUMERATED("vpbd_VehicleClass", "bus-vehicle", 2)) < 0) return ret; break;
	case 3: if ((ret = ASN1_Print_ENUMERATED("vpbd_VehicleClass", "taxi-vehicle", 3)) < 0) return ret; break;
	case 4: if ((ret = ASN1_Print_ENUMERATED("vpbd_VehicleClass", "passenger-cars", 4)) < 0) return ret; break;
	case 5: if ((ret = ASN1_Print_ENUMERATED("vpbd_VehicleClass", "emergency-vehicles", 5)) < 0) return ret; break;
	case 6: if ((ret = ASN1_Print_ENUMERATED("vpbd_VehicleClass", "official-vehicle", 6)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_VisibleString("vpbd-VehicleTimeInGeneralizedTime", &(value->vpbd_VehicleTimeInGeneralizedTime))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_VisibleString("vpbd-VehicleTimeOutGeneralizedTime", &(value->vpbd_VehicleTimeOutGeneralizedTime))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("vpbd-VehicleTravelTimeTime", &(value->vpbd_VehicleTravelTimeTime))) < 0) return ret;
	if (value->DEF_ProbeVehicleDetection_vpbd_VehicleAverageSpeedRate == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("vpbd-VehicleAverageSpeedRate", &(value->vpbd_VehicleAverageSpeedRate))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_ProbeVehicleDetection_vpbd_AviReaderIdNumber == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_UTF8Str("vpbd-AviReaderIdNumber", &(value->vpbd_AviReaderIdNumber))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_ProbeVehicleDetection_vpbd_AviReaderLocationLatitude == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("vpbd-AviReaderLocationLatitude", &(value->vpbd_AviReaderLocationLatitude))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_ProbeVehicleDetection_vpbd_AviReaderLocationLongitude == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("vpbd-AviReaderLocationLongitude", &(value->vpbd_AviReaderLocationLongitude))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorIdNumber == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_UTF8Str("vpbd-ReferenceLocatorIdNumber", &(value->vpbd_ReferenceLocatorIdNumber))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorLatitude == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("vpbd-ReferenceLocatorLatitude", &(value->vpbd_ReferenceLocatorLatitude))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorLongitude == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("vpbd-ReferenceLocatorLongitude", &(value->vpbd_ReferenceLocatorLongitude))) < 0) return ret;
	} /* OPTIONAL end */
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_ProbeVehicleDetection_vpbd_VehicleIdNumber(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->vpbd_VehicleIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_ProbeVehicleDetection_vpbd_VehicleClass(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ENUMERATED user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_ENUMERATED(workspace, (ASNINT32*)&value->vpbd_VehicleClass, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_ProbeVehicleDetection_vpbd_VehicleTimeInGeneralizedTime(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_VisibleString(workspace, &value->vpbd_VehicleTimeInGeneralizedTime, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_ProbeVehicleDetection_vpbd_VehicleTimeOutGeneralizedTime(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_VisibleString(workspace, &value->vpbd_VehicleTimeOutGeneralizedTime, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_ProbeVehicleDetection_vpbd_VehicleTravelTimeTime(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->vpbd_VehicleTravelTimeTime, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_ProbeVehicleDetection_vpbd_VehicleAverageSpeedRate(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_ProbeVehicleDetection_vpbd_VehicleAverageSpeedRate = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->vpbd_VehicleAverageSpeedRate, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_ProbeVehicleDetection_vpbd_AviReaderIdNumber(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->DEF_ProbeVehicleDetection_vpbd_AviReaderIdNumber = 1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->vpbd_AviReaderIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_ProbeVehicleDetection_vpbd_AviReaderLocationLatitude(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_ProbeVehicleDetection_vpbd_AviReaderLocationLatitude = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->vpbd_AviReaderLocationLatitude, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_ProbeVehicleDetection_vpbd_AviReaderLocationLongitude(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_ProbeVehicleDetection_vpbd_AviReaderLocationLongitude = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->vpbd_AviReaderLocationLongitude, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_ProbeVehicleDetection_vpbd_ReferenceLocatorIdNumber(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorIdNumber = 1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->vpbd_ReferenceLocatorIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_ProbeVehicleDetection_vpbd_ReferenceLocatorLatitude(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorLatitude = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->vpbd_ReferenceLocatorLatitude, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_ProbeVehicleDetection_vpbd_ReferenceLocatorLongitude(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorLongitude = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->vpbd_ReferenceLocatorLongitude, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_ProbeVehicleDetection_vpbd_VehicleIdNumber(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->vpbd_VehicleIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_ProbeVehicleDetection_vpbd_VehicleClass(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ENUMERATED* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->vpbd_VehicleClass, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_ProbeVehicleDetection_vpbd_VehicleTimeInGeneralizedTime(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_VisibleString(workspace, &value->vpbd_VehicleTimeInGeneralizedTime, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_ProbeVehicleDetection_vpbd_VehicleTimeOutGeneralizedTime(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_VisibleString(workspace, &value->vpbd_VehicleTimeOutGeneralizedTime, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_ProbeVehicleDetection_vpbd_VehicleTravelTimeTime(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->vpbd_VehicleTravelTimeTime, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_ProbeVehicleDetection_vpbd_VehicleAverageSpeedRate(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_ProbeVehicleDetection_vpbd_VehicleAverageSpeedRate == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->vpbd_VehicleAverageSpeedRate, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_ProbeVehicleDetection_vpbd_AviReaderIdNumber(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_ProbeVehicleDetection_vpbd_AviReaderIdNumber == 1)
	{
		if ((ret = ASN1_GET_UTF8Str(workspace, &value->vpbd_AviReaderIdNumber, user_value, user_value_length)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_ProbeVehicleDetection_vpbd_AviReaderLocationLatitude(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_ProbeVehicleDetection_vpbd_AviReaderLocationLatitude == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->vpbd_AviReaderLocationLatitude, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_ProbeVehicleDetection_vpbd_AviReaderLocationLongitude(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_ProbeVehicleDetection_vpbd_AviReaderLocationLongitude == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->vpbd_AviReaderLocationLongitude, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_ProbeVehicleDetection_vpbd_ReferenceLocatorIdNumber(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorIdNumber == 1)
	{
		if ((ret = ASN1_GET_UTF8Str(workspace, &value->vpbd_ReferenceLocatorIdNumber, user_value, user_value_length)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_ProbeVehicleDetection_vpbd_ReferenceLocatorLatitude(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorLatitude == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->vpbd_ReferenceLocatorLatitude, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_ProbeVehicleDetection_vpbd_ReferenceLocatorLongitude(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorLongitude == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->vpbd_ReferenceLocatorLongitude, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_CHECK_ProbeVehicleDetection(ProbeVehicleDetection* value)
{
	int ret = 0;

	unsigned char checkinfo_vpbd_VehicleIdNumber[] = {
		0x02,0x01,0x82,0x01,0x00,0x00
	};
	unsigned char checkinfo_vpbd_VehicleClass[] = {
		0x07,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x00
	};
	unsigned char checkinfo_vpbd_VehicleTimeInGeneralizedTime[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_vpbd_VehicleTimeOutGeneralizedTime[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_vpbd_VehicleTravelTimeTime[] = {
		0x02,0x00,0x82,0x2A,0x30,0x00
	};
	unsigned char checkinfo_vpbd_VehicleAverageSpeedRate[] = {
		0x02,0x00,0x82,0x01,0x2C,0x00
	};
	unsigned char checkinfo_vpbd_AviReaderIdNumber[] = {
		0x02,0x01,0x82,0x01,0x00,0x00
	};
	unsigned char checkinfo_vpbd_AviReaderLocationLatitude[] = {
		0x02,0x85,0xFF,0x00,0x00,0x00,0x01,0x85,0xFF,0x4D,0x2F,0xA2,0x00,0x00
	};
	unsigned char checkinfo_vpbd_AviReaderLocationLongitude[] = {
		0x02,0x85,0x00,0xB2,0xD0,0x5E,0x00,0x85,0x00,0xFF,0xFF,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_vpbd_ReferenceLocatorIdNumber[] = {
		0x02,0x01,0x82,0x01,0x00,0x00
	};
	unsigned char checkinfo_vpbd_ReferenceLocatorLatitude[] = {
		0x02,0x85,0xFF,0x00,0x00,0x00,0x01,0x85,0xFF,0x4D,0x2F,0xA2,0x00,0x00
	};
	unsigned char checkinfo_vpbd_ReferenceLocatorLongitude[] = {
		0x02,0x85,0x00,0xB2,0xD0,0x5E,0x00,0x85,0x00,0xFF,0xFF,0xFF,0xFF,0x00
	};

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_UTF8Str(&(value->vpbd_VehicleIdNumber), checkinfo_vpbd_VehicleIdNumber)) < 0) return ret;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->vpbd_VehicleClass), checkinfo_vpbd_VehicleClass)) < 0) return ret;
	if ((ret = ASN1_CHECK_VisibleString(&(value->vpbd_VehicleTimeInGeneralizedTime), checkinfo_vpbd_VehicleTimeInGeneralizedTime)) < 0) return ret;
	if ((ret = ASN1_CHECK_VisibleString(&(value->vpbd_VehicleTimeOutGeneralizedTime), checkinfo_vpbd_VehicleTimeOutGeneralizedTime)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->vpbd_VehicleTravelTimeTime), checkinfo_vpbd_VehicleTravelTimeTime)) < 0) return ret;
	if (value->DEF_ProbeVehicleDetection_vpbd_VehicleAverageSpeedRate == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->vpbd_VehicleAverageSpeedRate), checkinfo_vpbd_VehicleAverageSpeedRate)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_ProbeVehicleDetection_vpbd_AviReaderIdNumber == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_UTF8Str(&(value->vpbd_AviReaderIdNumber), checkinfo_vpbd_AviReaderIdNumber)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_ProbeVehicleDetection_vpbd_AviReaderLocationLatitude == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->vpbd_AviReaderLocationLatitude), checkinfo_vpbd_AviReaderLocationLatitude)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_ProbeVehicleDetection_vpbd_AviReaderLocationLongitude == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->vpbd_AviReaderLocationLongitude), checkinfo_vpbd_AviReaderLocationLongitude)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorIdNumber == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_UTF8Str(&(value->vpbd_ReferenceLocatorIdNumber), checkinfo_vpbd_ReferenceLocatorIdNumber)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorLatitude == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->vpbd_ReferenceLocatorLatitude), checkinfo_vpbd_ReferenceLocatorLatitude)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorLongitude == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->vpbd_ReferenceLocatorLongitude), checkinfo_vpbd_ReferenceLocatorLongitude)) < 0) return ret;
	} /* OPTIONAL end */
	return ret;
}
int ASN1_BER_Data_Enc_ProbeVehicleDetection(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->vpbd_VehicleIdNumber), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32*)&(value->vpbd_VehicleClass), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_VisibleString(workspace, &(value->vpbd_VehicleTimeInGeneralizedTime), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_VisibleString(workspace, &(value->vpbd_VehicleTimeOutGeneralizedTime), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->vpbd_VehicleTravelTimeTime), ASN1IMPL)) < 0) return ret;
	if (value->DEF_ProbeVehicleDetection_vpbd_VehicleAverageSpeedRate == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->vpbd_VehicleAverageSpeedRate), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_ProbeVehicleDetection_vpbd_AviReaderIdNumber == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 6)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->vpbd_AviReaderIdNumber), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_ProbeVehicleDetection_vpbd_AviReaderLocationLatitude == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 7)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->vpbd_AviReaderLocationLatitude), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_ProbeVehicleDetection_vpbd_AviReaderLocationLongitude == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 8)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->vpbd_AviReaderLocationLongitude), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorIdNumber == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 9)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->vpbd_ReferenceLocatorIdNumber), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorLatitude == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 10)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->vpbd_ReferenceLocatorLatitude), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorLongitude == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 11)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->vpbd_ReferenceLocatorLongitude), ASN1IMPL)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_ProbeVehicleDetection(ProbeVehicleDetection* value);
extern int ASN1_BER_Data_Enc_ProbeVehicleDetection(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_ProbeVehicleDetection(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_ProbeVehicleDetection(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_ProbeVehicleDetection(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_ProbeVehicleDetection(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	ASNUINT8* _cpointer;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->vpbd_VehicleIdNumber, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)&value->vpbd_VehicleClass, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_VisibleString(workspace, &value->vpbd_VehicleTimeInGeneralizedTime, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_VisibleString(workspace, &value->vpbd_VehicleTimeOutGeneralizedTime, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->vpbd_VehicleTravelTimeTime, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 5))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->vpbd_VehicleAverageSpeedRate, len, ASN1IMPL)) < 0) return ret;

		value->DEF_ProbeVehicleDetection_vpbd_VehicleAverageSpeedRate = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 6))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 6)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->vpbd_AviReaderIdNumber, len, ASN1IMPL)) < 0) return ret;

		value->DEF_ProbeVehicleDetection_vpbd_AviReaderIdNumber = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 7))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 7)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->vpbd_AviReaderLocationLatitude, len, ASN1IMPL)) < 0) return ret;

		value->DEF_ProbeVehicleDetection_vpbd_AviReaderLocationLatitude = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 8))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 8)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->vpbd_AviReaderLocationLongitude, len, ASN1IMPL)) < 0) return ret;

		value->DEF_ProbeVehicleDetection_vpbd_AviReaderLocationLongitude = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 9))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 9)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->vpbd_ReferenceLocatorIdNumber, len, ASN1IMPL)) < 0) return ret;

		value->DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorIdNumber = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 10))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 10)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->vpbd_ReferenceLocatorLatitude, len, ASN1IMPL)) < 0) return ret;

		value->DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorLatitude = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 11))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 11)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->vpbd_ReferenceLocatorLongitude, len, ASN1IMPL)) < 0) return ret;

		value->DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorLongitude = 1;
	}
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if (IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_ProbeVehicleDetection(ProbeVehicleDetection* value);
extern int ASN1_BER_Data_Dec_ProbeVehicleDetection(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_ProbeVehicleDetection(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_ProbeVehicleDetection(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_ProbeVehicleDetection(value)) < 0) return ret;
	return ret;
}

/********************************************************
*ProbeVehicleDetectionRequest                           *
********************************************************/
int ASN1_Print_ProbeVehicleDetectionRequest(ProbeVehicleDetectionRequest* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// Type Default
	if ((ret = ASN1_Print_UTF8Str("ProbeVehicleDetectionRequest", value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_ProbeVehicleDetectionRequest(ProbeVehicleDetectionRequest* value)
{
	unsigned char checkinfo_ProbeVehicleDetectionRequest[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_UTF8Str(value, checkinfo_ProbeVehicleDetectionRequest)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_ProbeVehicleDetectionRequest(ASN1WorkSpace* workspace, ProbeVehicleDetectionRequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_ProbeVehicleDetectionRequest(ASN1WorkSpace* workspace, ProbeVehicleDetectionRequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_ProbeVehicleDetectionRequest(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_ProbeVehicleDetectionRequest(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_ProbeVehicleDetectionRequest(ASN1WorkSpace* workspace, ProbeVehicleDetectionRequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_ProbeVehicleDetectionRequest(ASN1WorkSpace* workspace, ProbeVehicleDetectionRequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_ProbeVehicleDetectionRequest(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_ProbeVehicleDetectionRequest(value)) < 0) return ret;
	return ret;
}

/********************************************************
*ProbeVehicleDetectionResponse                          *
********************************************************/
int ASN1_Print_ProbeVehicleDetectionResponse(ProbeVehicleDetectionResponse* value, int tab_value)
{
	int ret = 0;
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	count = value->count;
	pnode = value->head->next;
	// SEQUENCE OF : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ_OF("ProbeVehicleDetectionResponse");
	while (count) {
		// Type Reference ProbeVehicleDetection
		ASN_Print_TAB(tab_value + 1);
		if ((ret = ASN1_Print_ProbeVehicleDetection((ProbeVehicleDetection*)pnode->data, tab_value + 1)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}

	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_ProbeVehicleDetectionResponse_ProbeVehicleDetectionResponse_pdata(ASN1WorkSpace* workspace, ProbeVehicleDetectionResponse* value, ProbeVehicleDetection* user_value)
{
	int ret = 0;
	ProbeVehicleDetection* list_value;
	if (value == NULL || user_value == NULL) return -1;
	list_value = (ProbeVehicleDetection*)mpool_malloc(workspace->Pmemory, sizeof(ProbeVehicleDetection));
	memset(list_value, 0, sizeof(ProbeVehicleDetection));
	memmove(list_value, user_value, sizeof(ProbeVehicleDetection));
	ASN1_Insert_Node(workspace, value, list_value);
	return ret;
}
int ASN1_GET_ProbeVehicleDetectionResponse_ProbeVehicleDetectionResponse_pdata(ASN1WorkSpace* workspace, ProbeVehicleDetectionResponse* value, ProbeVehicleDetection** user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = ASN1_Get_Node(value);
	return ret;
}
extern int ASN1_CHECK_ProbeVehicleDetection(ProbeVehicleDetection* value);
int ASN1_CHECK_ProbeVehicleDetectionResponse(ProbeVehicleDetectionResponse* value)
{
	int ret = 0;

	unsigned char checkinfo_ProbeVehicleDetectionResponse[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_ProbeVehicleDetectionResponse_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		if ((ret = ASN1_CHECK_ProbeVehicleDetection(pnode->data)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_ProbeVehicleDetection(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_ProbeVehicleDetectionResponse(ASN1WorkSpace* workspace, ProbeVehicleDetectionResponse* value, ASN1TagType tagFlag)
{
	int ret = 0;
	ASN1ListNode* pnode;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	pnode = value->head->next;
	while (NULL != pnode)
	{
		if ((ret = ASN1_BER_Data_Enc_ProbeVehicleDetection(workspace, pnode->data, ASN1EXPL)) < 0) return ret;
		pnode = pnode->next;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_ProbeVehicleDetectionResponse(ProbeVehicleDetectionResponse* value);
extern int ASN1_BER_Data_Enc_ProbeVehicleDetectionResponse(ASN1WorkSpace* workspace, ProbeVehicleDetectionResponse* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_ProbeVehicleDetectionResponse(ASN1WorkSpace* workspace, ProbeVehicleDetectionResponse* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_ProbeVehicleDetectionResponse(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_ProbeVehicleDetectionResponse(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_ProbeVehicleDetection(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_ProbeVehicleDetectionResponse(ASN1WorkSpace* workspace, ProbeVehicleDetectionResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ProbeVehicleDetection* pdata;
	ASNUINT8* p = workspace->buffer.current;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &length)) < 0) return ret;
	}
	if ((ret = ASN1_Creat_Init_List(workspace, value)) < 0) return ret;
	while (ASN1_BER_Dec_Isloop(workspace, p, length))
	{
		pdata = (ProbeVehicleDetection*)mpool_malloc(GetMemPool(workspace), sizeof(ProbeVehicleDetection));
		memset(pdata, 0, sizeof(ProbeVehicleDetection));
		if ((ret = ASN1_BER_Data_Dec_ProbeVehicleDetection(workspace, pdata, len, ASN1EXPL)) < 0) return ret;

		if ((ret = ASN1_Insert_Node(workspace, value, (void*)pdata)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if (IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_ProbeVehicleDetectionResponse(ProbeVehicleDetectionResponse* value);
extern int ASN1_BER_Data_Dec_ProbeVehicleDetectionResponse(ASN1WorkSpace* workspace, ProbeVehicleDetectionResponse* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_ProbeVehicleDetectionResponse(ASN1WorkSpace* workspace, ProbeVehicleDetectionResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_ProbeVehicleDetectionResponse(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_ProbeVehicleDetectionResponse(value)) < 0) return ret;
	return ret;
}

/********************************************************
*DetectorCollection                                     *
********************************************************/
int ASN1_Print_DetectorCollection(DetectorCollection* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("DetectorCollection");
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("tfdt-DetectorIdNumber", &(value->tfdt_DetectorIdNumber))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_VisibleString("tfdt-DetectorTimeGeneralizedTime", &(value->tfdt_DetectorTimeGeneralizedTime))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("tfdt-SpeedRate", &(value->tfdt_SpeedRate))) < 0) return ret;
	if (value->DEF_DetectorCollection_tfdt_VolumeRate == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("tfdt-VolumeRate", &(value->tfdt_VolumeRate))) < 0) return ret;
	} /* OPTIONAL end */
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("tfdt-OccupancyPercent", &(value->tfdt_OccupancyPercent))) < 0) return ret;
	if (value->DEF_DetectorCollection_tfdt_VehicleQueueLengthQuantity == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("tfdt-VehicleQueueLengthQuantity", &(value->tfdt_VehicleQueueLengthQuantity))) < 0) return ret;
	} /* OPTIONAL end */
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_DetectorCollection_tfdt_DetectorIdNumber(ASN1WorkSpace* workspace, DetectorCollection* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->tfdt_DetectorIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_DetectorCollection_tfdt_DetectorTimeGeneralizedTime(ASN1WorkSpace* workspace, DetectorCollection* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_VisibleString(workspace, &value->tfdt_DetectorTimeGeneralizedTime, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_DetectorCollection_tfdt_SpeedRate(ASN1WorkSpace* workspace, DetectorCollection* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->tfdt_SpeedRate, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_DetectorCollection_tfdt_VolumeRate(ASN1WorkSpace* workspace, DetectorCollection* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_DetectorCollection_tfdt_VolumeRate = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->tfdt_VolumeRate, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_DetectorCollection_tfdt_OccupancyPercent(ASN1WorkSpace* workspace, DetectorCollection* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->tfdt_OccupancyPercent, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_DetectorCollection_tfdt_VehicleQueueLengthQuantity(ASN1WorkSpace* workspace, DetectorCollection* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_DetectorCollection_tfdt_VehicleQueueLengthQuantity = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->tfdt_VehicleQueueLengthQuantity, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_DetectorCollection_tfdt_DetectorIdNumber(ASN1WorkSpace* workspace, DetectorCollection* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->tfdt_DetectorIdNumber, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_DetectorCollection_tfdt_DetectorTimeGeneralizedTime(ASN1WorkSpace* workspace, DetectorCollection* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_VisibleString(workspace, &value->tfdt_DetectorTimeGeneralizedTime, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_DetectorCollection_tfdt_SpeedRate(ASN1WorkSpace* workspace, DetectorCollection* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->tfdt_SpeedRate, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_DetectorCollection_tfdt_VolumeRate(ASN1WorkSpace* workspace, DetectorCollection* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_DetectorCollection_tfdt_VolumeRate == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->tfdt_VolumeRate, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_DetectorCollection_tfdt_OccupancyPercent(ASN1WorkSpace* workspace, DetectorCollection* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->tfdt_OccupancyPercent, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_DetectorCollection_tfdt_VehicleQueueLengthQuantity(ASN1WorkSpace* workspace, DetectorCollection* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_DetectorCollection_tfdt_VehicleQueueLengthQuantity == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->tfdt_VehicleQueueLengthQuantity, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_CHECK_DetectorCollection(DetectorCollection* value)
{
	int ret = 0;

	unsigned char checkinfo_tfdt_DetectorIdNumber[] = {
		0x02,0x01,0x82,0x01,0x00,0x00
	};
	unsigned char checkinfo_tfdt_DetectorTimeGeneralizedTime[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_tfdt_SpeedRate[] = {
		0x02,0x00,0x82,0x01,0x2C,0x00
	};
	unsigned char checkinfo_tfdt_VolumeRate[] = {
		0x02,0x00,0x64,0x00
	};
	unsigned char checkinfo_tfdt_OccupancyPercent[] = {
		0x02,0x00,0x64,0x00
	};
	unsigned char checkinfo_tfdt_VehicleQueueLengthQuantity[] = {
		0x02,0x00,0x83,0x07,0xA1,0x20,0x00
	};

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_UTF8Str(&(value->tfdt_DetectorIdNumber), checkinfo_tfdt_DetectorIdNumber)) < 0) return ret;
	if ((ret = ASN1_CHECK_VisibleString(&(value->tfdt_DetectorTimeGeneralizedTime), checkinfo_tfdt_DetectorTimeGeneralizedTime)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->tfdt_SpeedRate), checkinfo_tfdt_SpeedRate)) < 0) return ret;
	if (value->DEF_DetectorCollection_tfdt_VolumeRate == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->tfdt_VolumeRate), checkinfo_tfdt_VolumeRate)) < 0) return ret;
	} /* OPTIONAL end */
	if ((ret = ASN1_CHECK_INTEGER(&(value->tfdt_OccupancyPercent), checkinfo_tfdt_OccupancyPercent)) < 0) return ret;
	if (value->DEF_DetectorCollection_tfdt_VehicleQueueLengthQuantity == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->tfdt_VehicleQueueLengthQuantity), checkinfo_tfdt_VehicleQueueLengthQuantity)) < 0) return ret;
	} /* OPTIONAL end */
	return ret;
}
int ASN1_BER_Data_Enc_DetectorCollection(ASN1WorkSpace* workspace, DetectorCollection* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->tfdt_DetectorIdNumber), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_VisibleString(workspace, &(value->tfdt_DetectorTimeGeneralizedTime), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->tfdt_SpeedRate), ASN1IMPL)) < 0) return ret;
	if (value->DEF_DetectorCollection_tfdt_VolumeRate == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->tfdt_VolumeRate), ASN1IMPL)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->tfdt_OccupancyPercent), ASN1IMPL)) < 0) return ret;
	if (value->DEF_DetectorCollection_tfdt_VehicleQueueLengthQuantity == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->tfdt_VehicleQueueLengthQuantity), ASN1IMPL)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_DetectorCollection(DetectorCollection* value);
extern int ASN1_BER_Data_Enc_DetectorCollection(ASN1WorkSpace* workspace, DetectorCollection* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_DetectorCollection(ASN1WorkSpace* workspace, DetectorCollection* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_DetectorCollection(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_DetectorCollection(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_DetectorCollection(ASN1WorkSpace* workspace, DetectorCollection* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	ASNUINT8* _cpointer;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->tfdt_DetectorIdNumber, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_VisibleString(workspace, &value->tfdt_DetectorTimeGeneralizedTime, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->tfdt_SpeedRate, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 3))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->tfdt_VolumeRate, len, ASN1IMPL)) < 0) return ret;

		value->DEF_DetectorCollection_tfdt_VolumeRate = 1;
	}
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->tfdt_OccupancyPercent, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 5))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->tfdt_VehicleQueueLengthQuantity, len, ASN1IMPL)) < 0) return ret;

		value->DEF_DetectorCollection_tfdt_VehicleQueueLengthQuantity = 1;
	}
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if (IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_DetectorCollection(DetectorCollection* value);
extern int ASN1_BER_Data_Dec_DetectorCollection(ASN1WorkSpace* workspace, DetectorCollection* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_DetectorCollection(ASN1WorkSpace* workspace, DetectorCollection* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_DetectorCollection(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_DetectorCollection(value)) < 0) return ret;
	return ret;
}

/********************************************************
*DetectorCollectionRequest                              *
********************************************************/
int ASN1_Print_DetectorCollectionRequest(DetectorCollectionRequest* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// Type Default
	if ((ret = ASN1_Print_UTF8Str("DetectorCollectionRequest", value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_DetectorCollectionRequest(DetectorCollectionRequest* value)
{
	unsigned char checkinfo_DetectorCollectionRequest[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_UTF8Str(value, checkinfo_DetectorCollectionRequest)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_DetectorCollectionRequest(ASN1WorkSpace* workspace, DetectorCollectionRequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_DetectorCollectionRequest(ASN1WorkSpace* workspace, DetectorCollectionRequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_DetectorCollectionRequest(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_DetectorCollectionRequest(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_DetectorCollectionRequest(ASN1WorkSpace* workspace, DetectorCollectionRequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_DetectorCollectionRequest(ASN1WorkSpace* workspace, DetectorCollectionRequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_DetectorCollectionRequest(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_DetectorCollectionRequest(value)) < 0) return ret;
	return ret;
}

/********************************************************
*DetectorCollectionResponse                             *
********************************************************/
int ASN1_Print_DetectorCollectionResponse(DetectorCollectionResponse* value, int tab_value)
{
	int ret = 0;
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	count = value->count;
	pnode = value->head->next;
	// SEQUENCE OF : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ_OF("DetectorCollectionResponse");
	while (count) {
		// Type Reference DetectorCollection
		ASN_Print_TAB(tab_value + 1);
		if ((ret = ASN1_Print_DetectorCollection((DetectorCollection*)pnode->data, tab_value + 1)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}

	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_DetectorCollectionResponse_DetectorCollectionResponse_pdata(ASN1WorkSpace* workspace, DetectorCollectionResponse* value, DetectorCollection* user_value)
{
	int ret = 0;
	DetectorCollection* list_value;
	if (value == NULL || user_value == NULL) return -1;
	list_value = (DetectorCollection*)mpool_malloc(workspace->Pmemory, sizeof(DetectorCollection));
	memset(list_value, 0, sizeof(DetectorCollection));
	memmove(list_value, user_value, sizeof(DetectorCollection));
	ASN1_Insert_Node(workspace, value, list_value);
	return ret;
}
int ASN1_GET_DetectorCollectionResponse_DetectorCollectionResponse_pdata(ASN1WorkSpace* workspace, DetectorCollectionResponse* value, DetectorCollection** user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = ASN1_Get_Node(value);
	return ret;
}
extern int ASN1_CHECK_DetectorCollection(DetectorCollection* value);
int ASN1_CHECK_DetectorCollectionResponse(DetectorCollectionResponse* value)
{
	int ret = 0;

	unsigned char checkinfo_DetectorCollectionResponse[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_DetectorCollectionResponse_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		if ((ret = ASN1_CHECK_DetectorCollection(pnode->data)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_DetectorCollection(ASN1WorkSpace* workspace, DetectorCollection* value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_DetectorCollectionResponse(ASN1WorkSpace* workspace, DetectorCollectionResponse* value, ASN1TagType tagFlag)
{
	int ret = 0;
	ASN1ListNode* pnode;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	pnode = value->head->next;
	while (NULL != pnode)
	{
		if ((ret = ASN1_BER_Data_Enc_DetectorCollection(workspace, pnode->data, ASN1EXPL)) < 0) return ret;
		pnode = pnode->next;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_DetectorCollectionResponse(DetectorCollectionResponse* value);
extern int ASN1_BER_Data_Enc_DetectorCollectionResponse(ASN1WorkSpace* workspace, DetectorCollectionResponse* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_DetectorCollectionResponse(ASN1WorkSpace* workspace, DetectorCollectionResponse* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_DetectorCollectionResponse(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_DetectorCollectionResponse(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_DetectorCollection(ASN1WorkSpace* workspace, DetectorCollection* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_DetectorCollectionResponse(ASN1WorkSpace* workspace, DetectorCollectionResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	DetectorCollection* pdata;
	ASNUINT8* p = workspace->buffer.current;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &length)) < 0) return ret;
	}
	if ((ret = ASN1_Creat_Init_List(workspace, value)) < 0) return ret;
	while (ASN1_BER_Dec_Isloop(workspace, p, length))
	{
		pdata = (DetectorCollection*)mpool_malloc(GetMemPool(workspace), sizeof(DetectorCollection));
		memset(pdata, 0, sizeof(DetectorCollection));
		if ((ret = ASN1_BER_Data_Dec_DetectorCollection(workspace, pdata, len, ASN1EXPL)) < 0) return ret;

		if ((ret = ASN1_Insert_Node(workspace, value, (void*)pdata)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if (IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_DetectorCollectionResponse(DetectorCollectionResponse* value);
extern int ASN1_BER_Data_Dec_DetectorCollectionResponse(ASN1WorkSpace* workspace, DetectorCollectionResponse* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_DetectorCollectionResponse(ASN1WorkSpace* workspace, DetectorCollectionResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_DetectorCollectionResponse(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_DetectorCollectionResponse(value)) < 0) return ret;
	return ret;
}

/********************************************************
*ExtentionCommPDU                                       *
********************************************************/
int ASN1_Print_ExtentionCommPDU(ExtentionCommPDU* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("ExtentionCommPDU");
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("index", &(value->index))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("aid", &(value->aid))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_GeneralizedTime("deliveryStart", &(value->deliveryStart))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_GeneralizedTime("deliveryStop", &(value->deliveryStop))) < 0) return ret;
	if (value->DEF_ExtentionCommPDU_signature == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_BOOLEAN("signature", &(value->signature))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_ExtentionCommPDU_payloadType == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("payloadType", &(value->payloadType))) < 0) return ret;
	} /* OPTIONAL end */
	// Type OCTET STRING
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_OCTETSTRING("payload", &(value->payload), tab_value + 1)) < 0) return ret;
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_ExtentionCommPDU_index(ASN1WorkSpace* workspace, ExtentionCommPDU* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->index, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_ExtentionCommPDU_aid(ASN1WorkSpace* workspace, ExtentionCommPDU* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->aid, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_ExtentionCommPDU_deliveryStart(ASN1WorkSpace* workspace, ExtentionCommPDU* value, struct tm* user_value, ASNINT32 _TimeZoneInSecond, ASNINT32 _second, ASNINT32 _exponent)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_GeneralizedTime(workspace, &value->deliveryStart, user_value, _TimeZoneInSecond, _second, _exponent)) < 0) return ret;
	return ret;
}
int ASN1_SET_ExtentionCommPDU_deliveryStop(ASN1WorkSpace* workspace, ExtentionCommPDU* value, struct tm* user_value, ASNINT32 _TimeZoneInSecond, ASNINT32 _second, ASNINT32 _exponent)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_GeneralizedTime(workspace, &value->deliveryStop, user_value, _TimeZoneInSecond, _second, _exponent)) < 0) return ret;
	return ret;
}
int ASN1_SET_ExtentionCommPDU_signature(ASN1WorkSpace* workspace, ExtentionCommPDU* value, BOOLEAN user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_ExtentionCommPDU_signature = 1;
	if ((ret = ASN1_SET_BOOLEAN(workspace, &value->signature, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_ExtentionCommPDU_payloadType(ASN1WorkSpace* workspace, ExtentionCommPDU* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_ExtentionCommPDU_payloadType = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->payloadType, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_ExtentionCommPDU_payload(ASN1WorkSpace* workspace, ExtentionCommPDU* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_OCTETSTRING(workspace, &value->payload, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_ExtentionCommPDU_index(ASN1WorkSpace* workspace, ExtentionCommPDU* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->index, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_ExtentionCommPDU_aid(ASN1WorkSpace* workspace, ExtentionCommPDU* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->aid, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_ExtentionCommPDU_deliveryStart(ASN1WorkSpace* workspace, ExtentionCommPDU* value, struct tm* user_value, ASNINT32* _TimeZoneInSecond, ASNINT32* _second, ASNINT32* _exponent)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_GeneralizedTime(workspace, &value->deliveryStart, user_value, _TimeZoneInSecond, _second, _exponent)) < 0) return ret;
	return ret;
}
int ASN1_GET_ExtentionCommPDU_deliveryStop(ASN1WorkSpace* workspace, ExtentionCommPDU* value, struct tm* user_value, ASNINT32* _TimeZoneInSecond, ASNINT32* _second, ASNINT32* _exponent)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_GeneralizedTime(workspace, &value->deliveryStop, user_value, _TimeZoneInSecond, _second, _exponent)) < 0) return ret;
	return ret;
}
int ASN1_GET_ExtentionCommPDU_signature(ASN1WorkSpace* workspace, ExtentionCommPDU* value, BOOLEAN* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_ExtentionCommPDU_signature == 1)
	{
		if ((ret = ASN1_GET_BOOLEAN(workspace, &value->signature, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_ExtentionCommPDU_payloadType(ASN1WorkSpace* workspace, ExtentionCommPDU* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_ExtentionCommPDU_payloadType == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->payloadType, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_ExtentionCommPDU_payload(ASN1WorkSpace* workspace, ExtentionCommPDU* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_OCTETSTRING(workspace, &value->payload, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_ExtentionCommPDU(ExtentionCommPDU* value)
{
	int ret = 0;

	unsigned char checkinfo_index[] = {
		0x02,0x01,0x84,0x7F,0xFF,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_aid[] = {
		0x02,0x00,0x84,0x10,0x20,0x40,0x7F,0x00
	};
	unsigned char checkinfo_deliveryStart[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_deliveryStop[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_signature[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_payloadType[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_payload[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(&(value->index), checkinfo_index)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->aid), checkinfo_aid)) < 0) return ret;
	if ((ret = ASN1_CHECK_GeneralizedTime(&(value->deliveryStart), checkinfo_deliveryStart)) < 0) return ret;
	if ((ret = ASN1_CHECK_GeneralizedTime(&(value->deliveryStop), checkinfo_deliveryStop)) < 0) return ret;
	if (value->DEF_ExtentionCommPDU_signature == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_BOOLEAN(&(value->signature), checkinfo_signature)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_ExtentionCommPDU_payloadType == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->payloadType), checkinfo_payloadType)) < 0) return ret;
	} /* OPTIONAL end */
	if ((ret = ASN1_CHECK_OCTETSTRING(&(value->payload), checkinfo_payload)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_ExtentionCommPDU(ASN1WorkSpace* workspace, ExtentionCommPDU* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->index), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->aid), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_GeneralizedTime(workspace, &(value->deliveryStart), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_GeneralizedTime(workspace, &(value->deliveryStop), ASN1IMPL)) < 0) return ret;
	if (value->DEF_ExtentionCommPDU_signature == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_BOOLEAN(workspace, &(value->signature), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_ExtentionCommPDU_payloadType == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->payloadType), ASN1IMPL)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 6)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_OCTETSTRING(workspace, &(value->payload), ASN1IMPL)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_ExtentionCommPDU(ExtentionCommPDU* value);
extern int ASN1_BER_Data_Enc_ExtentionCommPDU(ASN1WorkSpace* workspace, ExtentionCommPDU* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_ExtentionCommPDU(ASN1WorkSpace* workspace, ExtentionCommPDU* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_ExtentionCommPDU(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_ExtentionCommPDU(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_ExtentionCommPDU(ASN1WorkSpace* workspace, ExtentionCommPDU* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	ASNUINT8* _cpointer;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->index, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->aid, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_GeneralizedTime(workspace, &value->deliveryStart, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_GeneralizedTime(workspace, &value->deliveryStop, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 4))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_BOOLEAN(workspace, &value->signature, len, ASN1IMPL)) < 0) return ret;

		value->DEF_ExtentionCommPDU_signature = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 5))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->payloadType, len, ASN1IMPL)) < 0) return ret;

		value->DEF_ExtentionCommPDU_payloadType = 1;
	}
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 6)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_OCTETSTRING(workspace, &value->payload, len, ASN1IMPL)) < 0) return ret;

	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if (IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_ExtentionCommPDU(ExtentionCommPDU* value);
extern int ASN1_BER_Data_Dec_ExtentionCommPDU(ASN1WorkSpace* workspace, ExtentionCommPDU* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_ExtentionCommPDU(ASN1WorkSpace* workspace, ExtentionCommPDU* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_ExtentionCommPDU(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_ExtentionCommPDU(value)) < 0) return ret;
	return ret;
}

/********************************************************
*ExtentionCommPDURequest                                *
********************************************************/
int ASN1_Print_ExtentionCommPDURequest(ExtentionCommPDURequest* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// Type Default
	if ((ret = ASN1_Print_UTF8Str("ExtentionCommPDURequest", value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_ExtentionCommPDURequest(ExtentionCommPDURequest* value)
{
	unsigned char checkinfo_ExtentionCommPDURequest[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_UTF8Str(value, checkinfo_ExtentionCommPDURequest)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_ExtentionCommPDURequest(ASN1WorkSpace* workspace, ExtentionCommPDURequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_ExtentionCommPDURequest(ASN1WorkSpace* workspace, ExtentionCommPDURequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_ExtentionCommPDURequest(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_ExtentionCommPDURequest(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_ExtentionCommPDURequest(ASN1WorkSpace* workspace, ExtentionCommPDURequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_ExtentionCommPDURequest(ASN1WorkSpace* workspace, ExtentionCommPDURequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_ExtentionCommPDURequest(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_ExtentionCommPDURequest(value)) < 0) return ret;
	return ret;
}

/********************************************************
*ExtentionCommPDUResponse                               *
********************************************************/
int ASN1_Print_ExtentionCommPDUResponse(ExtentionCommPDUResponse* value, int tab_value)
{
	int ret = 0;
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	count = value->count;
	pnode = value->head->next;
	// SEQUENCE OF : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ_OF("ExtentionCommPDUResponse");
	while (count) {
		// Type Reference ExtentionCommPDU
		ASN_Print_TAB(tab_value + 1);
		if ((ret = ASN1_Print_ExtentionCommPDU((ExtentionCommPDU*)pnode->data, tab_value + 1)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}

	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_ExtentionCommPDUResponse_ExtentionCommPDUResponse_pdata(ASN1WorkSpace* workspace, ExtentionCommPDUResponse* value, ExtentionCommPDU* user_value)
{
	int ret = 0;
	ExtentionCommPDU* list_value;
	if (value == NULL || user_value == NULL) return -1;
	list_value = (ExtentionCommPDU*)mpool_malloc(workspace->Pmemory, sizeof(ExtentionCommPDU));
	memset(list_value, 0, sizeof(ExtentionCommPDU));
	memmove(list_value, user_value, sizeof(ExtentionCommPDU));
	ASN1_Insert_Node(workspace, value, list_value);
	return ret;
}
int ASN1_GET_ExtentionCommPDUResponse_ExtentionCommPDUResponse_pdata(ASN1WorkSpace* workspace, ExtentionCommPDUResponse* value, ExtentionCommPDU** user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = ASN1_Get_Node(value);
	return ret;
}
extern int ASN1_CHECK_ExtentionCommPDU(ExtentionCommPDU* value);
int ASN1_CHECK_ExtentionCommPDUResponse(ExtentionCommPDUResponse* value)
{
	int ret = 0;

	unsigned char checkinfo_ExtentionCommPDUResponse[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_ExtentionCommPDUResponse_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		if ((ret = ASN1_CHECK_ExtentionCommPDU(pnode->data)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_ExtentionCommPDU(ASN1WorkSpace* workspace, ExtentionCommPDU* value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_ExtentionCommPDUResponse(ASN1WorkSpace* workspace, ExtentionCommPDUResponse* value, ASN1TagType tagFlag)
{
	int ret = 0;
	ASN1ListNode* pnode;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	pnode = value->head->next;
	while (NULL != pnode)
	{
		if ((ret = ASN1_BER_Data_Enc_ExtentionCommPDU(workspace, pnode->data, ASN1EXPL)) < 0) return ret;
		pnode = pnode->next;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_ExtentionCommPDUResponse(ExtentionCommPDUResponse* value);
extern int ASN1_BER_Data_Enc_ExtentionCommPDUResponse(ASN1WorkSpace* workspace, ExtentionCommPDUResponse* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_ExtentionCommPDUResponse(ASN1WorkSpace* workspace, ExtentionCommPDUResponse* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_ExtentionCommPDUResponse(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_ExtentionCommPDUResponse(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_ExtentionCommPDU(ASN1WorkSpace* workspace, ExtentionCommPDU* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_ExtentionCommPDUResponse(ASN1WorkSpace* workspace, ExtentionCommPDUResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ExtentionCommPDU* pdata;
	ASNUINT8* p = workspace->buffer.current;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &length)) < 0) return ret;
	}
	if ((ret = ASN1_Creat_Init_List(workspace, value)) < 0) return ret;
	while (ASN1_BER_Dec_Isloop(workspace, p, length))
	{
		pdata = (ExtentionCommPDU*)mpool_malloc(GetMemPool(workspace), sizeof(ExtentionCommPDU));
		memset(pdata, 0, sizeof(ExtentionCommPDU));
		if ((ret = ASN1_BER_Data_Dec_ExtentionCommPDU(workspace, pdata, len, ASN1EXPL)) < 0) return ret;

		if ((ret = ASN1_Insert_Node(workspace, value, (void*)pdata)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if (IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_ExtentionCommPDUResponse(ExtentionCommPDUResponse* value);
extern int ASN1_BER_Data_Dec_ExtentionCommPDUResponse(ASN1WorkSpace* workspace, ExtentionCommPDUResponse* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_ExtentionCommPDUResponse(ASN1WorkSpace* workspace, ExtentionCommPDUResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_ExtentionCommPDUResponse(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_ExtentionCommPDUResponse(value)) < 0) return ret;
	return ret;
}

/********************************************************
*ItsIso14827TestTimeFormat                              *
********************************************************/
int ASN1_Print_ItsIso14827TestTimeFormat(ItsIso14827TestTimeFormat* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch (*value)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("ItsIso14827TestTimeFormat", "full", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("ItsIso14827TestTimeFormat", "hhmmss", 1)) < 0) return ret; break;
	case 2: if ((ret = ASN1_Print_ENUMERATED("ItsIso14827TestTimeFormat", "hhmm", 2)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	return ret;
}
int ASN1_CHECK_ItsIso14827TestTimeFormat(ItsIso14827TestTimeFormat* value)
{
	unsigned char checkinfo_ItsIso14827TestTimeFormat[] = {
		0x03,0x00,0x01,0x02,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)value, checkinfo_ItsIso14827TestTimeFormat)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_ItsIso14827TestTimeFormat(ASN1WorkSpace* workspace, ItsIso14827TestTimeFormat* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32*)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_ItsIso14827TestTimeFormat(ASN1WorkSpace* workspace, ItsIso14827TestTimeFormat* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_ItsIso14827TestTimeFormat(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_ItsIso14827TestTimeFormat(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_ItsIso14827TestTimeFormat(ASN1WorkSpace* workspace, ItsIso14827TestTimeFormat* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_ItsIso14827TestTimeFormat(ASN1WorkSpace* workspace, ItsIso14827TestTimeFormat* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_ItsIso14827TestTimeFormat(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_ItsIso14827TestTimeFormat(value)) < 0) return ret;
	return ret;
}

/********************************************************
*ItsIso14827TestTimeRequest                             *
********************************************************/
int ASN1_Print_ItsIso14827TestTimeRequest(ItsIso14827TestTimeRequest* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("ItsIso14827TestTimeRequest");
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch (value->fmt)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("fmt", "full", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("fmt", "hhmmss", 1)) < 0) return ret; break;
	case 2: if ((ret = ASN1_Print_ENUMERATED("fmt", "hhmm", 2)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_ItsIso14827TestTimeRequest_fmt(ASN1WorkSpace* workspace, ItsIso14827TestTimeRequest* value, ENUMERATED user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_ENUMERATED(workspace, (ASNINT32*)&value->fmt, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_ItsIso14827TestTimeRequest_fmt(ASN1WorkSpace* workspace, ItsIso14827TestTimeRequest* value, ENUMERATED* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->fmt, user_value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_ItsIso14827TestTimeRequest(ItsIso14827TestTimeRequest* value)
{
	int ret = 0;

	unsigned char checkinfo_fmt[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->fmt), checkinfo_fmt)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Enc_ItsIso14827TestTimeFormat(ASN1WorkSpace* workspace, ItsIso14827TestTimeFormat* value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_ItsIso14827TestTimeRequest(ASN1WorkSpace* workspace, ItsIso14827TestTimeRequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_ItsIso14827TestTimeFormat(workspace, &(value->fmt), ASN1IMPL)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_ItsIso14827TestTimeRequest(ItsIso14827TestTimeRequest* value);
extern int ASN1_BER_Data_Enc_ItsIso14827TestTimeRequest(ASN1WorkSpace* workspace, ItsIso14827TestTimeRequest* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_ItsIso14827TestTimeRequest(ASN1WorkSpace* workspace, ItsIso14827TestTimeRequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_ItsIso14827TestTimeRequest(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_ItsIso14827TestTimeRequest(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_ItsIso14827TestTimeFormat(ASN1WorkSpace* workspace, ItsIso14827TestTimeFormat* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_ItsIso14827TestTimeRequest(ASN1WorkSpace* workspace, ItsIso14827TestTimeRequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8* _cpointer;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_ItsIso14827TestTimeFormat(workspace, &value->fmt, len, ASN1IMPL)) < 0) return ret;

	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if (IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_ItsIso14827TestTimeRequest(ItsIso14827TestTimeRequest* value);
extern int ASN1_BER_Data_Dec_ItsIso14827TestTimeRequest(ASN1WorkSpace* workspace, ItsIso14827TestTimeRequest* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_ItsIso14827TestTimeRequest(ASN1WorkSpace* workspace, ItsIso14827TestTimeRequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_ItsIso14827TestTimeRequest(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_ItsIso14827TestTimeRequest(value)) < 0) return ret;
	return ret;
}

/********************************************************
*ItsIso14827TestTimeResponse                            *
********************************************************/
int ASN1_Print_ItsIso14827TestTimeResponse(ItsIso14827TestTimeResponse* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("ItsIso14827TestTimeResponse");
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("str", &(value->str))) < 0) return ret;
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_ItsIso14827TestTimeResponse_str(ASN1WorkSpace* workspace, ItsIso14827TestTimeResponse* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->str, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_ItsIso14827TestTimeResponse_str(ASN1WorkSpace* workspace, ItsIso14827TestTimeResponse* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->str, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_ItsIso14827TestTimeResponse(ItsIso14827TestTimeResponse* value)
{
	int ret = 0;

	unsigned char checkinfo_str[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_UTF8Str(&(value->str), checkinfo_str)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_ItsIso14827TestTimeResponse(ASN1WorkSpace* workspace, ItsIso14827TestTimeResponse* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->str), ASN1IMPL)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_ItsIso14827TestTimeResponse(ItsIso14827TestTimeResponse* value);
extern int ASN1_BER_Data_Enc_ItsIso14827TestTimeResponse(ASN1WorkSpace* workspace, ItsIso14827TestTimeResponse* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_ItsIso14827TestTimeResponse(ASN1WorkSpace* workspace, ItsIso14827TestTimeResponse* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_ItsIso14827TestTimeResponse(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_ItsIso14827TestTimeResponse(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_ItsIso14827TestTimeResponse(ASN1WorkSpace* workspace, ItsIso14827TestTimeResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8* _cpointer;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->str, len, ASN1IMPL)) < 0) return ret;

	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if (IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_ItsIso14827TestTimeResponse(ItsIso14827TestTimeResponse* value);
extern int ASN1_BER_Data_Dec_ItsIso14827TestTimeResponse(ASN1WorkSpace* workspace, ItsIso14827TestTimeResponse* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_ItsIso14827TestTimeResponse(ASN1WorkSpace* workspace, ItsIso14827TestTimeResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_ItsIso14827TestTimeResponse(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_ItsIso14827TestTimeResponse(value)) < 0) return ret;
	return ret;
}


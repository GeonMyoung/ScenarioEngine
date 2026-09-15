#include "ISO14827_1.h"

/********************************************************
*ISO14827-MESSAGE_messageType                           *
********************************************************/
int ASN1_Print_ISO14827_MESSAGE_messageType(ISO14827_MESSAGE_messageType *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch(*value)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("ISO14827-MESSAGE_messageType", "publication", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("ISO14827-MESSAGE_messageType", "subscription", 1)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	return ret;
}
int ASN1_CHECK_ISO14827_MESSAGE_messageType(ISO14827_MESSAGE_messageType *value)
{
	unsigned char checkinfo_ISO14827_MESSAGE_messageType[] = {0x02,0x00,0x01,0x00 };
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32 *)value, checkinfo_ISO14827_MESSAGE_messageType)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_ISO14827_MESSAGE_messageType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_messageType *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_ISO14827_MESSAGE_messageType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_messageType *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_ISO14827_MESSAGE_messageType(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_ISO14827_MESSAGE_messageType(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_ISO14827_MESSAGE_messageType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_messageType *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_ISO14827_MESSAGE_messageType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_messageType *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_ISO14827_MESSAGE_messageType(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_ISO14827_MESSAGE_messageType(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_ISO14827_MESSAGE_messageType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_messageType *value)
{
	struct Asn1ConsInfo consinfo_ISO14827_MESSAGE_messageType = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 0, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_ISO14827_MESSAGE_messageType;
	switch(*value)
	{
	case ISO14827_MESSAGE_messageType_publication: ui_ISO14827_MESSAGE_messageType = 0; consinfo_ISO14827_MESSAGE_messageType.enumextbit = 0; break;
	case ISO14827_MESSAGE_messageType_subscription: ui_ISO14827_MESSAGE_messageType = 1; consinfo_ISO14827_MESSAGE_messageType.enumextbit = 0; break;
	default: ui_ISO14827_MESSAGE_messageType = *value; consinfo_ISO14827_MESSAGE_messageType.enumextbit = 0; break;
	}
	if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_ISO14827_MESSAGE_messageType, &consinfo_ISO14827_MESSAGE_messageType)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Enc_ISO14827_MESSAGE_messageType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_messageType *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_ISO14827_MESSAGE_messageType(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_ISO14827_MESSAGE_messageType(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_ISO14827_MESSAGE_messageType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_messageType *value)
{
	struct Asn1ConsInfo consinfo_ISO14827_MESSAGE_messageType = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 0, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_ISO14827_MESSAGE_messageType;
	if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_ISO14827_MESSAGE_messageType, &consinfo_ISO14827_MESSAGE_messageType)) < 0) return ret;
	if (consinfo_ISO14827_MESSAGE_messageType.enumextbit == 0)
	{
		switch(ui_ISO14827_MESSAGE_messageType)
		{
		case 0: *value = ISO14827_MESSAGE_messageType_publication; break;
		case 1: *value = ISO14827_MESSAGE_messageType_subscription; break;
		default: *value = ui_ISO14827_MESSAGE_messageType; break;
		}
	}
	return ret;
}
int ASN1_PER_Align_Dec_ISO14827_MESSAGE_messageType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_messageType *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_ISO14827_MESSAGE_messageType(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_ISO14827_MESSAGE_messageType(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_ISO14827_MESSAGE_messageType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_messageType *value)
{
	struct Asn1ConsInfo consinfo_ISO14827_MESSAGE_messageType = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 0, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_ISO14827_MESSAGE_messageType;
	switch(*value)
	{
	case ISO14827_MESSAGE_messageType_publication: ui_ISO14827_MESSAGE_messageType = 0; consinfo_ISO14827_MESSAGE_messageType.enumextbit = 0; break;
	case ISO14827_MESSAGE_messageType_subscription: ui_ISO14827_MESSAGE_messageType = 1; consinfo_ISO14827_MESSAGE_messageType.enumextbit = 0; break;
	default: ui_ISO14827_MESSAGE_messageType = *value; consinfo_ISO14827_MESSAGE_messageType.enumextbit = 0; break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_ISO14827_MESSAGE_messageType, &consinfo_ISO14827_MESSAGE_messageType)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Enc_ISO14827_MESSAGE_messageType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_messageType *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_ISO14827_MESSAGE_messageType(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_ISO14827_MESSAGE_messageType(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_ISO14827_MESSAGE_messageType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_messageType *value)
{
	struct Asn1ConsInfo consinfo_ISO14827_MESSAGE_messageType = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 0, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_ISO14827_MESSAGE_messageType;
	if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_ISO14827_MESSAGE_messageType, &consinfo_ISO14827_MESSAGE_messageType)) < 0) return ret;
	if (consinfo_ISO14827_MESSAGE_messageType.enumextbit == 0)
	{
		switch(ui_ISO14827_MESSAGE_messageType)
		{
		case 0: *value = ISO14827_MESSAGE_messageType_publication; break;
		case 1: *value = ISO14827_MESSAGE_messageType_subscription; break;
		default: *value = ui_ISO14827_MESSAGE_messageType; break;
		}
	}
	return ret;
}
int ASN1_PER_UNAlign_Dec_ISO14827_MESSAGE_messageType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_messageType *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_ISO14827_MESSAGE_messageType(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_ISO14827_MESSAGE_messageType(value)) < 0) return ret;
	return ret;
}

/********************************************************
*ISO14827-MESSAGE_subscriptionType                      *
********************************************************/
int ASN1_Print_ISO14827_MESSAGE_subscriptionType(ISO14827_MESSAGE_subscriptionType *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch(*value)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("ISO14827-MESSAGE_subscriptionType", "single", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("ISO14827-MESSAGE_subscriptionType", "event-driven", 1)) < 0) return ret; break;
	case 2: if ((ret = ASN1_Print_ENUMERATED("ISO14827-MESSAGE_subscriptionType", "single-or-event", 2)) < 0) return ret; break;
	case 3: if ((ret = ASN1_Print_ENUMERATED("ISO14827-MESSAGE_subscriptionType", "periodic", 3)) < 0) return ret; break;
	case 4: if ((ret = ASN1_Print_ENUMERATED("ISO14827-MESSAGE_subscriptionType", "single-or-periodic", 4)) < 0) return ret; break;
	case 5: if ((ret = ASN1_Print_ENUMERATED("ISO14827-MESSAGE_subscriptionType", "event-or-periodic", 5)) < 0) return ret; break;
	case 6: if ((ret = ASN1_Print_ENUMERATED("ISO14827-MESSAGE_subscriptionType", "single-event-periodic", 6)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	return ret;
}
int ASN1_CHECK_ISO14827_MESSAGE_subscriptionType(ISO14827_MESSAGE_subscriptionType *value)
{
	unsigned char checkinfo_ISO14827_MESSAGE_subscriptionType[] = {0x07,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x00 };
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32 *)value, checkinfo_ISO14827_MESSAGE_subscriptionType)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_ISO14827_MESSAGE_subscriptionType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_subscriptionType *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_ISO14827_MESSAGE_subscriptionType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_subscriptionType *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_ISO14827_MESSAGE_subscriptionType(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_ISO14827_MESSAGE_subscriptionType(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_ISO14827_MESSAGE_subscriptionType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_subscriptionType *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_ISO14827_MESSAGE_subscriptionType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_subscriptionType *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_ISO14827_MESSAGE_subscriptionType(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_ISO14827_MESSAGE_subscriptionType(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_ISO14827_MESSAGE_subscriptionType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_subscriptionType *value)
{
	struct Asn1ConsInfo consinfo_ISO14827_MESSAGE_subscriptionType = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 0, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_ISO14827_MESSAGE_subscriptionType;
	switch(*value)
	{
	case ISO14827_MESSAGE_subscriptionType_single: ui_ISO14827_MESSAGE_subscriptionType = 0; consinfo_ISO14827_MESSAGE_subscriptionType.enumextbit = 0; break;
	case ISO14827_MESSAGE_subscriptionType_event_driven: ui_ISO14827_MESSAGE_subscriptionType = 1; consinfo_ISO14827_MESSAGE_subscriptionType.enumextbit = 0; break;
	case ISO14827_MESSAGE_subscriptionType_single_or_event: ui_ISO14827_MESSAGE_subscriptionType = 2; consinfo_ISO14827_MESSAGE_subscriptionType.enumextbit = 0; break;
	case ISO14827_MESSAGE_subscriptionType_periodic: ui_ISO14827_MESSAGE_subscriptionType = 3; consinfo_ISO14827_MESSAGE_subscriptionType.enumextbit = 0; break;
	case ISO14827_MESSAGE_subscriptionType_single_or_periodic: ui_ISO14827_MESSAGE_subscriptionType = 4; consinfo_ISO14827_MESSAGE_subscriptionType.enumextbit = 0; break;
	case ISO14827_MESSAGE_subscriptionType_event_or_periodic: ui_ISO14827_MESSAGE_subscriptionType = 5; consinfo_ISO14827_MESSAGE_subscriptionType.enumextbit = 0; break;
	case ISO14827_MESSAGE_subscriptionType_single_event_periodic: ui_ISO14827_MESSAGE_subscriptionType = 6; consinfo_ISO14827_MESSAGE_subscriptionType.enumextbit = 0; break;
	default: ui_ISO14827_MESSAGE_subscriptionType = *value; consinfo_ISO14827_MESSAGE_subscriptionType.enumextbit = 0; break;
	}
	if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_ISO14827_MESSAGE_subscriptionType, &consinfo_ISO14827_MESSAGE_subscriptionType)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Enc_ISO14827_MESSAGE_subscriptionType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_subscriptionType *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_ISO14827_MESSAGE_subscriptionType(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_ISO14827_MESSAGE_subscriptionType(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_ISO14827_MESSAGE_subscriptionType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_subscriptionType *value)
{
	struct Asn1ConsInfo consinfo_ISO14827_MESSAGE_subscriptionType = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 0, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_ISO14827_MESSAGE_subscriptionType;
	if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_ISO14827_MESSAGE_subscriptionType, &consinfo_ISO14827_MESSAGE_subscriptionType)) < 0) return ret;
	if (consinfo_ISO14827_MESSAGE_subscriptionType.enumextbit == 0)
	{
		switch(ui_ISO14827_MESSAGE_subscriptionType)
		{
		case 0: *value = ISO14827_MESSAGE_subscriptionType_single; break;
		case 1: *value = ISO14827_MESSAGE_subscriptionType_event_driven; break;
		case 2: *value = ISO14827_MESSAGE_subscriptionType_single_or_event; break;
		case 3: *value = ISO14827_MESSAGE_subscriptionType_periodic; break;
		case 4: *value = ISO14827_MESSAGE_subscriptionType_single_or_periodic; break;
		case 5: *value = ISO14827_MESSAGE_subscriptionType_event_or_periodic; break;
		case 6: *value = ISO14827_MESSAGE_subscriptionType_single_event_periodic; break;
		default: *value = ui_ISO14827_MESSAGE_subscriptionType; break;
		}
	}
	return ret;
}
int ASN1_PER_Align_Dec_ISO14827_MESSAGE_subscriptionType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_subscriptionType *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_ISO14827_MESSAGE_subscriptionType(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_ISO14827_MESSAGE_subscriptionType(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_ISO14827_MESSAGE_subscriptionType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_subscriptionType *value)
{
	struct Asn1ConsInfo consinfo_ISO14827_MESSAGE_subscriptionType = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 0, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_ISO14827_MESSAGE_subscriptionType;
	switch(*value)
	{
	case ISO14827_MESSAGE_subscriptionType_single: ui_ISO14827_MESSAGE_subscriptionType = 0; consinfo_ISO14827_MESSAGE_subscriptionType.enumextbit = 0; break;
	case ISO14827_MESSAGE_subscriptionType_event_driven: ui_ISO14827_MESSAGE_subscriptionType = 1; consinfo_ISO14827_MESSAGE_subscriptionType.enumextbit = 0; break;
	case ISO14827_MESSAGE_subscriptionType_single_or_event: ui_ISO14827_MESSAGE_subscriptionType = 2; consinfo_ISO14827_MESSAGE_subscriptionType.enumextbit = 0; break;
	case ISO14827_MESSAGE_subscriptionType_periodic: ui_ISO14827_MESSAGE_subscriptionType = 3; consinfo_ISO14827_MESSAGE_subscriptionType.enumextbit = 0; break;
	case ISO14827_MESSAGE_subscriptionType_single_or_periodic: ui_ISO14827_MESSAGE_subscriptionType = 4; consinfo_ISO14827_MESSAGE_subscriptionType.enumextbit = 0; break;
	case ISO14827_MESSAGE_subscriptionType_event_or_periodic: ui_ISO14827_MESSAGE_subscriptionType = 5; consinfo_ISO14827_MESSAGE_subscriptionType.enumextbit = 0; break;
	case ISO14827_MESSAGE_subscriptionType_single_event_periodic: ui_ISO14827_MESSAGE_subscriptionType = 6; consinfo_ISO14827_MESSAGE_subscriptionType.enumextbit = 0; break;
	default: ui_ISO14827_MESSAGE_subscriptionType = *value; consinfo_ISO14827_MESSAGE_subscriptionType.enumextbit = 0; break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_ISO14827_MESSAGE_subscriptionType, &consinfo_ISO14827_MESSAGE_subscriptionType)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Enc_ISO14827_MESSAGE_subscriptionType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_subscriptionType *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_ISO14827_MESSAGE_subscriptionType(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_ISO14827_MESSAGE_subscriptionType(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_ISO14827_MESSAGE_subscriptionType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_subscriptionType *value)
{
	struct Asn1ConsInfo consinfo_ISO14827_MESSAGE_subscriptionType = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 0, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_ISO14827_MESSAGE_subscriptionType;
	if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_ISO14827_MESSAGE_subscriptionType, &consinfo_ISO14827_MESSAGE_subscriptionType)) < 0) return ret;
	if (consinfo_ISO14827_MESSAGE_subscriptionType.enumextbit == 0)
	{
		switch(ui_ISO14827_MESSAGE_subscriptionType)
		{
		case 0: *value = ISO14827_MESSAGE_subscriptionType_single; break;
		case 1: *value = ISO14827_MESSAGE_subscriptionType_event_driven; break;
		case 2: *value = ISO14827_MESSAGE_subscriptionType_single_or_event; break;
		case 3: *value = ISO14827_MESSAGE_subscriptionType_periodic; break;
		case 4: *value = ISO14827_MESSAGE_subscriptionType_single_or_periodic; break;
		case 5: *value = ISO14827_MESSAGE_subscriptionType_event_or_periodic; break;
		case 6: *value = ISO14827_MESSAGE_subscriptionType_single_event_periodic; break;
		default: *value = ui_ISO14827_MESSAGE_subscriptionType; break;
		}
	}
	return ret;
}
int ASN1_PER_UNAlign_Dec_ISO14827_MESSAGE_subscriptionType(ASN1WorkSpace *workspace, ISO14827_MESSAGE_subscriptionType *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_ISO14827_MESSAGE_subscriptionType(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_ISO14827_MESSAGE_subscriptionType(value)) < 0) return ret;
	return ret;
}

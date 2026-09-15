#include "TechnicalRegulation2Eam.h"

/********************************************************
*NetworkInfo                                            *
********************************************************/
int ASN1_Print_NetworkInfo(NetworkInfo* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("NetworkInfo");
	// Type OCTET STRING
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_OCTETSTRING("ipAddress", &(value->ipAddress), tab_value + 1)) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("servicePort", &(value->servicePort))) < 0) return ret;
	// Type OCTET STRING
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_OCTETSTRING("providerServiceContext", &(value->providerServiceContext), tab_value + 1)) < 0) return ret;
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_NetworkInfo_ipAddress(ASN1WorkSpace* workspace, NetworkInfo* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_OCTETSTRING(workspace, &value->ipAddress, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_NetworkInfo_servicePort(ASN1WorkSpace* workspace, NetworkInfo* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->servicePort, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_NetworkInfo_providerServiceContext(ASN1WorkSpace* workspace, NetworkInfo* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_OCTETSTRING(workspace, &value->providerServiceContext, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_NetworkInfo_ipAddress(ASN1WorkSpace* workspace, NetworkInfo* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_OCTETSTRING(workspace, &value->ipAddress, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_NetworkInfo_servicePort(ASN1WorkSpace* workspace, NetworkInfo* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->servicePort, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_NetworkInfo_providerServiceContext(ASN1WorkSpace* workspace, NetworkInfo* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_OCTETSTRING(workspace, &value->providerServiceContext, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_NetworkInfo(NetworkInfo* value)
{
	int ret = 0;

	unsigned char checkinfo_ipAddress[] = {
		0x02,0x01,0x10,0x00
	};
	unsigned char checkinfo_servicePort[] = {
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_providerServiceContext[] = {
		0x02,0x01,0x1F,0x00
	};

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_OCTETSTRING(&(value->ipAddress), checkinfo_ipAddress)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->servicePort), checkinfo_servicePort)) < 0) return ret;
	if ((ret = ASN1_CHECK_OCTETSTRING(&(value->providerServiceContext), checkinfo_providerServiceContext)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_NetworkInfo(ASN1WorkSpace* workspace, NetworkInfo* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_OCTETSTRING(workspace, &(value->ipAddress), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->servicePort), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_OCTETSTRING(workspace, &(value->providerServiceContext), ASN1IMPL)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_NetworkInfo(NetworkInfo* value);
extern int ASN1_BER_Data_Enc_NetworkInfo(ASN1WorkSpace* workspace, NetworkInfo* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_NetworkInfo(ASN1WorkSpace* workspace, NetworkInfo* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_NetworkInfo(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_NetworkInfo(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_NetworkInfo(ASN1WorkSpace* workspace, NetworkInfo* value, int length, ASN1TagType tagFlag)
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
	if ((ret = ASN1_BER_Dec_OCTETSTRING(workspace, &value->ipAddress, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->servicePort, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_OCTETSTRING(workspace, &value->providerServiceContext, len, ASN1IMPL)) < 0) return ret;

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
extern int ASN1_CHECK_NetworkInfo(NetworkInfo* value);
extern int ASN1_BER_Data_Dec_NetworkInfo(ASN1WorkSpace* workspace, NetworkInfo* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_NetworkInfo(ASN1WorkSpace* workspace, NetworkInfo* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_NetworkInfo(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_NetworkInfo(value)) < 0) return ret;
	return ret;
}

/********************************************************
*CommTxPDU                                              *
********************************************************/
int ASN1_Print_CommTxPDU(CommTxPDU* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("CommTxPDU");
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("index", &(value->index))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("psid", &(value->psid))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("priority", &(value->priority))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("channel", &(value->channel))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("txInterval", &(value->txInterval))) < 0) return ret;
	if (value->DEF_CommTxPDU_ipAddressServicePort == 1)
	{ /*OPTIONAL start */
		// Type Reference NetworkInfo
		if (Compare_Letter(tab_value, "ipAddressServicePort")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("ipAddressServicePort = ");
		}
		if ((ret = ASN1_Print_NetworkInfo((NetworkInfo*)value->ipAddressServicePort, tab_value + 1)) < 0) return ret;
	} /* OPTIONAL end */
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_GeneralizedTime("deliveryStart", &(value->deliveryStart))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_GeneralizedTime("deliveryStop", &(value->deliveryStop))) < 0) return ret;
	if (value->DEF_CommTxPDU_signature == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_BOOLEAN("signature", &(value->signature))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_CommTxPDU_payloadType == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("payloadType", &(value->payloadType))) < 0) return ret;
	} /* OPTIONAL end */
	// Type OCTET STRING
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_OCTETSTRING("payload", &(value->payload), tab_value + 1)) < 0) return ret;
	if (value->DEF_CommTxPDU_txPower == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("txPower", &(value->txPower))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_CommTxPDU_txDataRate == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("txDataRate", &(value->txDataRate))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_CommTxPDU_channelNumberHdrExt == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_BOOLEAN("channelNumberHdrExt", &(value->channelNumberHdrExt))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_CommTxPDU_dataRateHdrExt == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_BOOLEAN("dataRateHdrExt", &(value->dataRateHdrExt))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_CommTxPDU_txPowerHdrExt == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_BOOLEAN("txPowerHdrExt", &(value->txPowerHdrExt))) < 0) return ret;
	} /* OPTIONAL end */
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_CommTxPDU_index(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->index, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_CommTxPDU_psid(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->psid, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_CommTxPDU_priority(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->priority, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_CommTxPDU_channel(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->channel, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_CommTxPDU_txInterval(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->txInterval, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_CommTxPDU_ipAddressServicePort(ASN1WorkSpace* workspace, CommTxPDU* value, NetworkInfo* user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->ipAddressServicePort = (NetworkInfo*)mpool_malloc(workspace->Pmemory, sizeof(NetworkInfo));
	memset(value->ipAddressServicePort, 0, sizeof(NetworkInfo));
	value->DEF_CommTxPDU_ipAddressServicePort = 1;
	memmove(value->ipAddressServicePort, user_value, sizeof(NetworkInfo));
	return ret;
}
int ASN1_SET_CommTxPDU_deliveryStart(ASN1WorkSpace* workspace, CommTxPDU* value, struct tm* user_value, ASNINT32 _TimeZoneInSecond, ASNINT32 _second, ASNINT32 _exponent)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_GeneralizedTime(workspace, &value->deliveryStart, user_value, _TimeZoneInSecond, _second, _exponent)) < 0) return ret;
	return ret;
}
int ASN1_SET_CommTxPDU_deliveryStop(ASN1WorkSpace* workspace, CommTxPDU* value, struct tm* user_value, ASNINT32 _TimeZoneInSecond, ASNINT32 _second, ASNINT32 _exponent)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_GeneralizedTime(workspace, &value->deliveryStop, user_value, _TimeZoneInSecond, _second, _exponent)) < 0) return ret;
	return ret;
}
int ASN1_SET_CommTxPDU_signature(ASN1WorkSpace* workspace, CommTxPDU* value, BOOLEAN user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_CommTxPDU_signature = 1;
	if ((ret = ASN1_SET_BOOLEAN(workspace, &value->signature, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_CommTxPDU_payloadType(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_CommTxPDU_payloadType = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->payloadType, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_CommTxPDU_payload(ASN1WorkSpace* workspace, CommTxPDU* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_OCTETSTRING(workspace, &value->payload, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_CommTxPDU_txPower(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_CommTxPDU_txPower = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->txPower, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_CommTxPDU_txDataRate(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_CommTxPDU_txDataRate = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->txDataRate, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_CommTxPDU_channelNumberHdrExt(ASN1WorkSpace* workspace, CommTxPDU* value, BOOLEAN user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_CommTxPDU_channelNumberHdrExt = 1;
	if ((ret = ASN1_SET_BOOLEAN(workspace, &value->channelNumberHdrExt, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_CommTxPDU_dataRateHdrExt(ASN1WorkSpace* workspace, CommTxPDU* value, BOOLEAN user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_CommTxPDU_dataRateHdrExt = 1;
	if ((ret = ASN1_SET_BOOLEAN(workspace, &value->dataRateHdrExt, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_CommTxPDU_txPowerHdrExt(ASN1WorkSpace* workspace, CommTxPDU* value, BOOLEAN user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_CommTxPDU_txPowerHdrExt = 1;
	if ((ret = ASN1_SET_BOOLEAN(workspace, &value->txPowerHdrExt, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_CommTxPDU_index(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->index, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_CommTxPDU_psid(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->psid, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_CommTxPDU_priority(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->priority, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_CommTxPDU_channel(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->channel, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_CommTxPDU_txInterval(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->txInterval, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_CommTxPDU_ipAddressServicePort(ASN1WorkSpace* workspace, CommTxPDU* value, NetworkInfo** user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_CommTxPDU_ipAddressServicePort == 1)
	{
		*user_value = value->ipAddressServicePort;
	}
	else return -2;
	return ret;
}
int ASN1_GET_CommTxPDU_deliveryStart(ASN1WorkSpace* workspace, CommTxPDU* value, struct tm* user_value, ASNINT32* _TimeZoneInSecond, ASNINT32* _second, ASNINT32* _exponent)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_GeneralizedTime(workspace, &value->deliveryStart, user_value, _TimeZoneInSecond, _second, _exponent)) < 0) return ret;
	return ret;
}
int ASN1_GET_CommTxPDU_deliveryStop(ASN1WorkSpace* workspace, CommTxPDU* value, struct tm* user_value, ASNINT32* _TimeZoneInSecond, ASNINT32* _second, ASNINT32* _exponent)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_GeneralizedTime(workspace, &value->deliveryStop, user_value, _TimeZoneInSecond, _second, _exponent)) < 0) return ret;
	return ret;
}
int ASN1_GET_CommTxPDU_signature(ASN1WorkSpace* workspace, CommTxPDU* value, BOOLEAN* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_CommTxPDU_signature == 1)
	{
		if ((ret = ASN1_GET_BOOLEAN(workspace, &value->signature, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_CommTxPDU_payloadType(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_CommTxPDU_payloadType == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->payloadType, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_CommTxPDU_payload(ASN1WorkSpace* workspace, CommTxPDU* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_OCTETSTRING(workspace, &value->payload, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_CommTxPDU_txPower(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_CommTxPDU_txPower == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->txPower, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_CommTxPDU_txDataRate(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_CommTxPDU_txDataRate == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->txDataRate, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_CommTxPDU_channelNumberHdrExt(ASN1WorkSpace* workspace, CommTxPDU* value, BOOLEAN* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_CommTxPDU_channelNumberHdrExt == 1)
	{
		if ((ret = ASN1_GET_BOOLEAN(workspace, &value->channelNumberHdrExt, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_CommTxPDU_dataRateHdrExt(ASN1WorkSpace* workspace, CommTxPDU* value, BOOLEAN* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_CommTxPDU_dataRateHdrExt == 1)
	{
		if ((ret = ASN1_GET_BOOLEAN(workspace, &value->dataRateHdrExt, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_CommTxPDU_txPowerHdrExt(ASN1WorkSpace* workspace, CommTxPDU* value, BOOLEAN* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_CommTxPDU_txPowerHdrExt == 1)
	{
		if ((ret = ASN1_GET_BOOLEAN(workspace, &value->txPowerHdrExt, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
extern int ASN1_CHECK_NetworkInfo(NetworkInfo* value);
int ASN1_CHECK_CommTxPDU(CommTxPDU* value)
{
	int ret = 0;

	unsigned char checkinfo_index[] = {
		0x02,0x01,0x84,0x7F,0xFF,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_psid[] = {
		0x02,0x00,0x84,0x10,0x20,0x40,0x7F,0x00
	};
	unsigned char checkinfo_priority[] = {
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_channel[] = {
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_txInterval[] = {
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_ipAddressServicePort[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_deliveryStart[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_deliveryStop[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_signature[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_payloadType[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_payload[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_txPower[] = {
		0x02,0x82,0xFF,0x80,0x7F,0x00
	};
	unsigned char checkinfo_txDataRate[] = {
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_channelNumberHdrExt[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_dataRateHdrExt[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_txPowerHdrExt[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(&(value->index), checkinfo_index)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->psid), checkinfo_psid)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->priority), checkinfo_priority)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->channel), checkinfo_channel)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->txInterval), checkinfo_txInterval)) < 0) return ret;
	if (value->DEF_CommTxPDU_ipAddressServicePort == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_NetworkInfo(value->ipAddressServicePort)) < 0) return ret;
	} /* OPTIONAL end */
	if ((ret = ASN1_CHECK_GeneralizedTime(&(value->deliveryStart), checkinfo_deliveryStart)) < 0) return ret;
	if ((ret = ASN1_CHECK_GeneralizedTime(&(value->deliveryStop), checkinfo_deliveryStop)) < 0) return ret;
	if (value->DEF_CommTxPDU_signature == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_BOOLEAN(&(value->signature), checkinfo_signature)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_CommTxPDU_payloadType == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->payloadType), checkinfo_payloadType)) < 0) return ret;
	} /* OPTIONAL end */
	if ((ret = ASN1_CHECK_OCTETSTRING(&(value->payload), checkinfo_payload)) < 0) return ret;
	if (value->DEF_CommTxPDU_txPower == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->txPower), checkinfo_txPower)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_CommTxPDU_txDataRate == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->txDataRate), checkinfo_txDataRate)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_CommTxPDU_channelNumberHdrExt == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_BOOLEAN(&(value->channelNumberHdrExt), checkinfo_channelNumberHdrExt)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_CommTxPDU_dataRateHdrExt == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_BOOLEAN(&(value->dataRateHdrExt), checkinfo_dataRateHdrExt)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_CommTxPDU_txPowerHdrExt == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_BOOLEAN(&(value->txPowerHdrExt), checkinfo_txPowerHdrExt)) < 0) return ret;
	} /* OPTIONAL end */
	return ret;
}
extern int ASN1_BER_Data_Enc_NetworkInfo(ASN1WorkSpace* workspace, NetworkInfo* value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_CommTxPDU(ASN1WorkSpace* workspace, CommTxPDU* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->index), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->psid), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->priority), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->channel), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->txInterval), ASN1IMPL)) < 0) return ret;
	if (value->DEF_CommTxPDU_ipAddressServicePort == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 5)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_NetworkInfo(workspace, value->ipAddressServicePort, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 6)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_GeneralizedTime(workspace, &(value->deliveryStart), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 7)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_GeneralizedTime(workspace, &(value->deliveryStop), ASN1IMPL)) < 0) return ret;
	if (value->DEF_CommTxPDU_signature == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 8)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_BOOLEAN(workspace, &(value->signature), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_CommTxPDU_payloadType == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 9)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->payloadType), ASN1IMPL)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 10)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_OCTETSTRING(workspace, &(value->payload), ASN1IMPL)) < 0) return ret;
	if (value->DEF_CommTxPDU_txPower == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 11)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->txPower), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_CommTxPDU_txDataRate == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 12)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->txDataRate), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_CommTxPDU_channelNumberHdrExt == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 13)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_BOOLEAN(workspace, &(value->channelNumberHdrExt), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_CommTxPDU_dataRateHdrExt == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 14)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_BOOLEAN(workspace, &(value->dataRateHdrExt), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_CommTxPDU_txPowerHdrExt == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 15)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_BOOLEAN(workspace, &(value->txPowerHdrExt), ASN1IMPL)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_CommTxPDU(CommTxPDU* value);
extern int ASN1_BER_Data_Enc_CommTxPDU(ASN1WorkSpace* workspace, CommTxPDU* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_CommTxPDU(ASN1WorkSpace* workspace, CommTxPDU* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_CommTxPDU(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_CommTxPDU(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_NetworkInfo(ASN1WorkSpace* workspace, NetworkInfo* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_CommTxPDU(ASN1WorkSpace* workspace, CommTxPDU* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	ASNUINT8* _cpointer;
	value->ipAddressServicePort = (NetworkInfo*)mpool_malloc(workspace->Pmemory, sizeof(NetworkInfo));
	memset(value->ipAddressServicePort, 0, sizeof(NetworkInfo));

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
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->psid, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->priority, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->channel, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->txInterval, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_CONS | 5))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 5)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_NetworkInfo(workspace, value->ipAddressServicePort, len, ASN1IMPL)) < 0) return ret;

		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->DEF_CommTxPDU_ipAddressServicePort = 1;
	}
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 6)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_GeneralizedTime(workspace, &value->deliveryStart, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 7)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_GeneralizedTime(workspace, &value->deliveryStop, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 8))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 8)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_BOOLEAN(workspace, &value->signature, len, ASN1IMPL)) < 0) return ret;

		value->DEF_CommTxPDU_signature = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 9))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 9)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->payloadType, len, ASN1IMPL)) < 0) return ret;

		value->DEF_CommTxPDU_payloadType = 1;
	}
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 10)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_OCTETSTRING(workspace, &value->payload, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 11))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 11)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->txPower, len, ASN1IMPL)) < 0) return ret;

		value->DEF_CommTxPDU_txPower = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 12))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 12)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->txDataRate, len, ASN1IMPL)) < 0) return ret;

		value->DEF_CommTxPDU_txDataRate = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 13))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 13)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_BOOLEAN(workspace, &value->channelNumberHdrExt, len, ASN1IMPL)) < 0) return ret;

		value->DEF_CommTxPDU_channelNumberHdrExt = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 14))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 14)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_BOOLEAN(workspace, &value->dataRateHdrExt, len, ASN1IMPL)) < 0) return ret;

		value->DEF_CommTxPDU_dataRateHdrExt = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 15))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 15)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_BOOLEAN(workspace, &value->txPowerHdrExt, len, ASN1IMPL)) < 0) return ret;

		value->DEF_CommTxPDU_txPowerHdrExt = 1;
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
extern int ASN1_CHECK_CommTxPDU(CommTxPDU* value);
extern int ASN1_BER_Data_Dec_CommTxPDU(ASN1WorkSpace* workspace, CommTxPDU* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_CommTxPDU(ASN1WorkSpace* workspace, CommTxPDU* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_CommTxPDU(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_CommTxPDU(value)) < 0) return ret;
	return ret;
}

/********************************************************
*CommTxPDURequest                                       *
********************************************************/
int ASN1_Print_CommTxPDURequest(CommTxPDURequest* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// Type Default
	if ((ret = ASN1_Print_UTF8Str("CommTxPDURequest", value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_CommTxPDURequest(CommTxPDURequest* value)
{
	unsigned char checkinfo_CommTxPDURequest[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_UTF8Str(value, checkinfo_CommTxPDURequest)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_CommTxPDURequest(ASN1WorkSpace* workspace, CommTxPDURequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_CommTxPDURequest(ASN1WorkSpace* workspace, CommTxPDURequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_CommTxPDURequest(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_CommTxPDURequest(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_CommTxPDURequest(ASN1WorkSpace* workspace, CommTxPDURequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_CommTxPDURequest(ASN1WorkSpace* workspace, CommTxPDURequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_CommTxPDURequest(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_CommTxPDURequest(value)) < 0) return ret;
	return ret;
}

/********************************************************
*CommTxPDUResponse                                      *
********************************************************/
int ASN1_Print_CommTxPDUResponse(CommTxPDUResponse* value, int tab_value)
{
	int ret = 0;
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	count = value->count;
	pnode = value->head->next;
	// SEQUENCE OF : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ_OF("CommTxPDUResponse");
	while (count) {
		// Type Reference CommTxPDU
		ASN_Print_TAB(tab_value + 1);
		if ((ret = ASN1_Print_CommTxPDU((CommTxPDU*)pnode->data, tab_value + 1)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}

	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_CommTxPDUResponse_CommTxPDUResponse_pdata(ASN1WorkSpace* workspace, CommTxPDUResponse* value, CommTxPDU* user_value)
{
	int ret = 0;
	CommTxPDU* list_value;
	if (value == NULL || user_value == NULL) return -1;
	list_value = (CommTxPDU*)mpool_malloc(workspace->Pmemory, sizeof(CommTxPDU));
	memset(list_value, 0, sizeof(CommTxPDU));
	memmove(list_value, user_value, sizeof(CommTxPDU));
	ASN1_Insert_Node(workspace, value, list_value);
	return ret;
}
int ASN1_GET_CommTxPDUResponse_CommTxPDUResponse_pdata(ASN1WorkSpace* workspace, CommTxPDUResponse* value, CommTxPDU** user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = ASN1_Get_Node(value);
	return ret;
}
extern int ASN1_CHECK_CommTxPDU(CommTxPDU* value);
int ASN1_CHECK_CommTxPDUResponse(CommTxPDUResponse* value)
{
	int ret = 0;

	unsigned char checkinfo_CommTxPDUResponse[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_CommTxPDUResponse_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		if ((ret = ASN1_CHECK_CommTxPDU(pnode->data)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_CommTxPDU(ASN1WorkSpace* workspace, CommTxPDU* value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_CommTxPDUResponse(ASN1WorkSpace* workspace, CommTxPDUResponse* value, ASN1TagType tagFlag)
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
		if ((ret = ASN1_BER_Data_Enc_CommTxPDU(workspace, pnode->data, ASN1EXPL)) < 0) return ret;
		pnode = pnode->next;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_CommTxPDUResponse(CommTxPDUResponse* value);
extern int ASN1_BER_Data_Enc_CommTxPDUResponse(ASN1WorkSpace* workspace, CommTxPDUResponse* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_CommTxPDUResponse(ASN1WorkSpace* workspace, CommTxPDUResponse* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_CommTxPDUResponse(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_CommTxPDUResponse(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_CommTxPDU(ASN1WorkSpace* workspace, CommTxPDU* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_CommTxPDUResponse(ASN1WorkSpace* workspace, CommTxPDUResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	CommTxPDU* pdata;
	ASNUINT8* p = workspace->buffer.current;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &length)) < 0) return ret;
	}
	if ((ret = ASN1_Creat_Init_List(workspace, value)) < 0) return ret;
	while (ASN1_BER_Dec_Isloop(workspace, p, length))
	{
		pdata = (CommTxPDU*)mpool_malloc(GetMemPool(workspace), sizeof(CommTxPDU));
		memset(pdata, 0, sizeof(CommTxPDU));
		if ((ret = ASN1_BER_Data_Dec_CommTxPDU(workspace, pdata, len, ASN1EXPL)) < 0) return ret;

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
extern int ASN1_CHECK_CommTxPDUResponse(CommTxPDUResponse* value);
extern int ASN1_BER_Data_Dec_CommTxPDUResponse(ASN1WorkSpace* workspace, CommTxPDUResponse* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_CommTxPDUResponse(ASN1WorkSpace* workspace, CommTxPDUResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_CommTxPDUResponse(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_CommTxPDUResponse(value)) < 0) return ret;
	return ret;
}

/********************************************************
*CommRxPDU                                              *
********************************************************/
int ASN1_Print_CommRxPDU(CommRxPDU* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("CommRxPDU");
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("psid", &(value->psid))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("channel", &(value->channel))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("rcpi", &(value->rcpi))) < 0) return ret;
	if (value->DEF_CommRxPDU_peerAddress == 1)
	{ /*OPTIONAL start */
		// Type OCTET STRING
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_OCTETSTRING("peerAddress", &(value->peerAddress), tab_value + 1)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_CommRxPDU_signed == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_BOOLEAN("sign", &(value->sign))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_CommRxPDU_payloadType == 1)
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
int ASN1_SET_CommRxPDU_psid(ASN1WorkSpace* workspace, CommRxPDU* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->psid, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_CommRxPDU_channel(ASN1WorkSpace* workspace, CommRxPDU* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->channel, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_CommRxPDU_rcpi(ASN1WorkSpace* workspace, CommRxPDU* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->rcpi, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_CommRxPDU_peerAddress(ASN1WorkSpace* workspace, CommRxPDU* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->DEF_CommRxPDU_peerAddress = 1;
	if ((ret = ASN1_SET_OCTETSTRING(workspace, &value->peerAddress, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_CommRxPDU_signed(ASN1WorkSpace* workspace, CommRxPDU* value, BOOLEAN user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_CommRxPDU_signed = 1;
	if ((ret = ASN1_SET_BOOLEAN(workspace, &value->sign, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_CommRxPDU_payloadType(ASN1WorkSpace* workspace, CommRxPDU* value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_CommRxPDU_payloadType = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->payloadType, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_CommRxPDU_payload(ASN1WorkSpace* workspace, CommRxPDU* value, ASNUINT8* user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_OCTETSTRING(workspace, &value->payload, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_CommRxPDU_psid(ASN1WorkSpace* workspace, CommRxPDU* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->psid, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_CommRxPDU_channel(ASN1WorkSpace* workspace, CommRxPDU* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->channel, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_CommRxPDU_rcpi(ASN1WorkSpace* workspace, CommRxPDU* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->rcpi, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_CommRxPDU_peerAddress(ASN1WorkSpace* workspace, CommRxPDU* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_CommRxPDU_peerAddress == 1)
	{
		if ((ret = ASN1_GET_OCTETSTRING(workspace, &value->peerAddress, user_value, user_value_length)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_CommRxPDU_signed(ASN1WorkSpace* workspace, CommRxPDU* value, BOOLEAN* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_CommRxPDU_signed == 1)
	{
		if ((ret = ASN1_GET_BOOLEAN(workspace, &value->sign, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_CommRxPDU_payloadType(ASN1WorkSpace* workspace, CommRxPDU* value, INTEGER* user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_CommRxPDU_payloadType == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->payloadType, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_CommRxPDU_payload(ASN1WorkSpace* workspace, CommRxPDU* value, ASNUINT8** user_value, ASNUINT32* user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_OCTETSTRING(workspace, &value->payload, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_CommRxPDU(CommRxPDU* value)
{
	int ret = 0;

	unsigned char checkinfo_psid[] = {
		0x02,0x00,0x84,0x10,0x20,0x40,0x7F,0x00
	};
	unsigned char checkinfo_channel[] = {
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_rcpi[] = {
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_peerAddress[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_signed[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_payloadType[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_payload[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(&(value->psid), checkinfo_psid)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->channel), checkinfo_channel)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->rcpi), checkinfo_rcpi)) < 0) return ret;
	if (value->DEF_CommRxPDU_peerAddress == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_OCTETSTRING(&(value->peerAddress), checkinfo_peerAddress)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_CommRxPDU_signed == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_BOOLEAN(&(value->sign), checkinfo_signed)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_CommRxPDU_payloadType == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->payloadType), checkinfo_payloadType)) < 0) return ret;
	} /* OPTIONAL end */
	if ((ret = ASN1_CHECK_OCTETSTRING(&(value->payload), checkinfo_payload)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_CommRxPDU(ASN1WorkSpace* workspace, CommRxPDU* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->psid), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->channel), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->rcpi), ASN1IMPL)) < 0) return ret;
	if (value->DEF_CommRxPDU_peerAddress == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_OCTETSTRING(workspace, &(value->peerAddress), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_CommRxPDU_signed == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_BOOLEAN(workspace, &(value->sign), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_CommRxPDU_payloadType == 1)
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
extern int ASN1_CHECK_CommRxPDU(CommRxPDU* value);
extern int ASN1_BER_Data_Enc_CommRxPDU(ASN1WorkSpace* workspace, CommRxPDU* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_CommRxPDU(ASN1WorkSpace* workspace, CommRxPDU* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_CommRxPDU(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_CommRxPDU(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_CommRxPDU(ASN1WorkSpace* workspace, CommRxPDU* value, int length, ASN1TagType tagFlag)
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
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->psid, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->channel, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->rcpi, len, ASN1IMPL)) < 0) return ret;

	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 3))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_OCTETSTRING(workspace, &value->peerAddress, len, ASN1IMPL)) < 0) return ret;

		value->DEF_CommRxPDU_peerAddress = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 4))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_BOOLEAN(workspace, &value->sign, len, ASN1IMPL)) < 0) return ret;

		value->DEF_CommRxPDU_signed = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 5))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->payloadType, len, ASN1IMPL)) < 0) return ret;

		value->DEF_CommRxPDU_payloadType = 1;
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
extern int ASN1_CHECK_CommRxPDU(CommRxPDU* value);
extern int ASN1_BER_Data_Dec_CommRxPDU(ASN1WorkSpace* workspace, CommRxPDU* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_CommRxPDU(ASN1WorkSpace* workspace, CommRxPDU* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_CommRxPDU(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_CommRxPDU(value)) < 0) return ret;
	return ret;
}

/********************************************************
*CommRxPDURequest                                       *
********************************************************/
int ASN1_Print_CommRxPDURequest(CommRxPDURequest* value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// Type Default
	if ((ret = ASN1_Print_UTF8Str("CommRxPDURequest", value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_CommRxPDURequest(CommRxPDURequest* value)
{
	unsigned char checkinfo_CommRxPDURequest[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_UTF8Str(value, checkinfo_CommRxPDURequest)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_CommRxPDURequest(ASN1WorkSpace* workspace, CommRxPDURequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_CommRxPDURequest(ASN1WorkSpace* workspace, CommRxPDURequest* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_CommRxPDURequest(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_CommRxPDURequest(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_CommRxPDURequest(ASN1WorkSpace* workspace, CommRxPDURequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_CommRxPDURequest(ASN1WorkSpace* workspace, CommRxPDURequest* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_CommRxPDURequest(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_CommRxPDURequest(value)) < 0) return ret;
	return ret;
}

/********************************************************
*CommRxPDUResponse                                      *
********************************************************/
int ASN1_Print_CommRxPDUResponse(CommRxPDUResponse* value, int tab_value)
{
	int ret = 0;
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	count = value->count;
	pnode = value->head->next;
	// SEQUENCE OF : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ_OF("CommRxPDUResponse");
	while (count) {
		// Type Reference CommRxPDU
		ASN_Print_TAB(tab_value + 1);
		if ((ret = ASN1_Print_CommRxPDU((CommRxPDU*)pnode->data, tab_value + 1)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}

	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_CommRxPDUResponse_CommRxPDUResponse_pdata(ASN1WorkSpace* workspace, CommRxPDUResponse* value, CommRxPDU* user_value)
{
	int ret = 0;
	CommRxPDU* list_value;
	if (value == NULL || user_value == NULL) return -1;
	list_value = (CommRxPDU*)mpool_malloc(workspace->Pmemory, sizeof(CommRxPDU));
	memset(list_value, 0, sizeof(CommRxPDU));
	memmove(list_value, user_value, sizeof(CommRxPDU));
	ASN1_Insert_Node(workspace, value, list_value);
	return ret;
}
int ASN1_GET_CommRxPDUResponse_CommRxPDUResponse_pdata(ASN1WorkSpace* workspace, CommRxPDUResponse* value, CommRxPDU** user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = ASN1_Get_Node(value);
	return ret;
}
extern int ASN1_CHECK_CommRxPDU(CommRxPDU* value);
int ASN1_CHECK_CommRxPDUResponse(CommRxPDUResponse* value)
{
	int ret = 0;

	unsigned char checkinfo_CommRxPDUResponse[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_CommRxPDUResponse_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		if ((ret = ASN1_CHECK_CommRxPDU(pnode->data)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_CommRxPDU(ASN1WorkSpace* workspace, CommRxPDU* value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_CommRxPDUResponse(ASN1WorkSpace* workspace, CommRxPDUResponse* value, ASN1TagType tagFlag)
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
		if ((ret = ASN1_BER_Data_Enc_CommRxPDU(workspace, pnode->data, ASN1EXPL)) < 0) return ret;
		pnode = pnode->next;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_CommRxPDUResponse(CommRxPDUResponse* value);
extern int ASN1_BER_Data_Enc_CommRxPDUResponse(ASN1WorkSpace* workspace, CommRxPDUResponse* value, ASN1TagType tagFlag);
int ASN1_BER_Enc_CommRxPDUResponse(ASN1WorkSpace* workspace, CommRxPDUResponse* value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_CommRxPDUResponse(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_CommRxPDUResponse(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_CommRxPDU(ASN1WorkSpace* workspace, CommRxPDU* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_CommRxPDUResponse(ASN1WorkSpace* workspace, CommRxPDUResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	CommRxPDU* pdata;
	ASNUINT8* p = workspace->buffer.current;

	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &length)) < 0) return ret;
	}
	if ((ret = ASN1_Creat_Init_List(workspace, value)) < 0) return ret;
	while (ASN1_BER_Dec_Isloop(workspace, p, length))
	{
		pdata = (CommRxPDU*)mpool_malloc(GetMemPool(workspace), sizeof(CommRxPDU));
		memset(pdata, 0, sizeof(CommRxPDU));
		if ((ret = ASN1_BER_Data_Dec_CommRxPDU(workspace, pdata, len, ASN1EXPL)) < 0) return ret;

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
extern int ASN1_CHECK_CommRxPDUResponse(CommRxPDUResponse* value);
extern int ASN1_BER_Data_Dec_CommRxPDUResponse(ASN1WorkSpace* workspace, CommRxPDUResponse* value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_CommRxPDUResponse(ASN1WorkSpace* workspace, CommRxPDUResponse* value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_CommRxPDUResponse(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_CommRxPDUResponse(value)) < 0) return ret;
	return ret;
}


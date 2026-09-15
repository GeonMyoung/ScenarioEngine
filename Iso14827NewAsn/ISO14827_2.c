#include "ISO14827_2.h"

/********************************************************
*DatexDataPacket_datex-Version-number                   *
********************************************************/
int ASN1_Print_DatexDataPacket_datex_Version_number(DatexDataPacket_datex_Version_number *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch(*value)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("DatexDataPacket_datex-Version-number", "experimental", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("DatexDataPacket_datex-Version-number", "version1", 1)) < 0) return ret; break;
	case 2: if ((ret = ASN1_Print_ENUMERATED("DatexDataPacket_datex-Version-number", "version2", 2)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	return ret;
}
int ASN1_CHECK_DatexDataPacket_datex_Version_number(DatexDataPacket_datex_Version_number *value)
{
	unsigned char checkinfo_DatexDataPacket_datex_Version_number[] = {0x03,0x00,0x01,0x02,0x00 };
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32 *)value, checkinfo_DatexDataPacket_datex_Version_number)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_DatexDataPacket_datex_Version_number(ASN1WorkSpace *workspace, DatexDataPacket_datex_Version_number *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_DatexDataPacket_datex_Version_number(ASN1WorkSpace *workspace, DatexDataPacket_datex_Version_number *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_DatexDataPacket_datex_Version_number(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_DatexDataPacket_datex_Version_number(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_DatexDataPacket_datex_Version_number(ASN1WorkSpace *workspace, DatexDataPacket_datex_Version_number *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_DatexDataPacket_datex_Version_number(ASN1WorkSpace *workspace, DatexDataPacket_datex_Version_number *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_DatexDataPacket_datex_Version_number(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_DatexDataPacket_datex_Version_number(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_DatexDataPacket_datex_Version_number(ASN1WorkSpace *workspace, DatexDataPacket_datex_Version_number *value)
{
	struct Asn1ConsInfo consinfo_DatexDataPacket_datex_Version_number = { ASN1_CONST64(0), ASN1_CONST64(2), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_DatexDataPacket_datex_Version_number;
	switch(*value)
	{
	case DatexDataPacket_datex_Version_number_experimental: ui_DatexDataPacket_datex_Version_number = 0; consinfo_DatexDataPacket_datex_Version_number.enumextbit = 0; break;
	case DatexDataPacket_datex_Version_number_version1: ui_DatexDataPacket_datex_Version_number = 1; consinfo_DatexDataPacket_datex_Version_number.enumextbit = 0; break;
	case DatexDataPacket_datex_Version_number_version2: ui_DatexDataPacket_datex_Version_number = 2; consinfo_DatexDataPacket_datex_Version_number.enumextbit = 0; break;
	default: ui_DatexDataPacket_datex_Version_number = *value; consinfo_DatexDataPacket_datex_Version_number.enumextbit = 1; break;
	}
	if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_DatexDataPacket_datex_Version_number, &consinfo_DatexDataPacket_datex_Version_number)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Enc_DatexDataPacket_datex_Version_number(ASN1WorkSpace *workspace, DatexDataPacket_datex_Version_number *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_DatexDataPacket_datex_Version_number(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_DatexDataPacket_datex_Version_number(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_DatexDataPacket_datex_Version_number(ASN1WorkSpace *workspace, DatexDataPacket_datex_Version_number *value)
{
	struct Asn1ConsInfo consinfo_DatexDataPacket_datex_Version_number = { ASN1_CONST64(0), ASN1_CONST64(2), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_DatexDataPacket_datex_Version_number;
	if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_DatexDataPacket_datex_Version_number, &consinfo_DatexDataPacket_datex_Version_number)) < 0) return ret;
	if (consinfo_DatexDataPacket_datex_Version_number.enumextbit == 0)
	{
		switch(ui_DatexDataPacket_datex_Version_number)
		{
		case 0: *value = DatexDataPacket_datex_Version_number_experimental; break;
		case 1: *value = DatexDataPacket_datex_Version_number_version1; break;
		case 2: *value = DatexDataPacket_datex_Version_number_version2; break;
		default: break;
		}
	}
	else
	{
		switch(ui_DatexDataPacket_datex_Version_number)
		{
		default: *value = ui_DatexDataPacket_datex_Version_number; break;
		}
	}
	return ret;
}
int ASN1_PER_Align_Dec_DatexDataPacket_datex_Version_number(ASN1WorkSpace *workspace, DatexDataPacket_datex_Version_number *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_DatexDataPacket_datex_Version_number(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_DatexDataPacket_datex_Version_number(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_DatexDataPacket_datex_Version_number(ASN1WorkSpace *workspace, DatexDataPacket_datex_Version_number *value)
{
	struct Asn1ConsInfo consinfo_DatexDataPacket_datex_Version_number = { ASN1_CONST64(0), ASN1_CONST64(2), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_DatexDataPacket_datex_Version_number;
	switch(*value)
	{
	case DatexDataPacket_datex_Version_number_experimental: ui_DatexDataPacket_datex_Version_number = 0; consinfo_DatexDataPacket_datex_Version_number.enumextbit = 0; break;
	case DatexDataPacket_datex_Version_number_version1: ui_DatexDataPacket_datex_Version_number = 1; consinfo_DatexDataPacket_datex_Version_number.enumextbit = 0; break;
	case DatexDataPacket_datex_Version_number_version2: ui_DatexDataPacket_datex_Version_number = 2; consinfo_DatexDataPacket_datex_Version_number.enumextbit = 0; break;
	default: ui_DatexDataPacket_datex_Version_number = *value; consinfo_DatexDataPacket_datex_Version_number.enumextbit = 1; break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_DatexDataPacket_datex_Version_number, &consinfo_DatexDataPacket_datex_Version_number)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Enc_DatexDataPacket_datex_Version_number(ASN1WorkSpace *workspace, DatexDataPacket_datex_Version_number *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_DatexDataPacket_datex_Version_number(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_DatexDataPacket_datex_Version_number(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_DatexDataPacket_datex_Version_number(ASN1WorkSpace *workspace, DatexDataPacket_datex_Version_number *value)
{
	struct Asn1ConsInfo consinfo_DatexDataPacket_datex_Version_number = { ASN1_CONST64(0), ASN1_CONST64(2), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_DatexDataPacket_datex_Version_number;
	if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_DatexDataPacket_datex_Version_number, &consinfo_DatexDataPacket_datex_Version_number)) < 0) return ret;
	if (consinfo_DatexDataPacket_datex_Version_number.enumextbit == 0)
	{
		switch(ui_DatexDataPacket_datex_Version_number)
		{
		case 0: *value = DatexDataPacket_datex_Version_number_experimental; break;
		case 1: *value = DatexDataPacket_datex_Version_number_version1; break;
		case 2: *value = DatexDataPacket_datex_Version_number_version2; break;
		default: break;
		}
	}
	else
	{
		switch(ui_DatexDataPacket_datex_Version_number)
		{
		default: *value = ui_DatexDataPacket_datex_Version_number; break;
		}
	}
	return ret;
}
int ASN1_PER_UNAlign_Dec_DatexDataPacket_datex_Version_number(ASN1WorkSpace *workspace, DatexDataPacket_datex_Version_number *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_DatexDataPacket_datex_Version_number(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_DatexDataPacket_datex_Version_number(value)) < 0) return ret;
	return ret;
}

/********************************************************
*DatexDataPacket                                        *
********************************************************/
int ASN1_Print_DatexDataPacket(DatexDataPacket *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("DatexDataPacket");
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch(value->datex_Version_number)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("DatexDataPacket_datex-Version-number", "experimental", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("DatexDataPacket_datex-Version-number", "version1", 1)) < 0) return ret; break;
	case 2: if ((ret = ASN1_Print_ENUMERATED("DatexDataPacket_datex-Version-number", "version2", 2)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	// Type OCTET STRING
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_OCTETSTRING("datex_Data", &(value->datex_Data), tab_value + 1)) < 0) return ret;
	// Type OCTET STRING
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_OCTETSTRING("datex_Crc_nbr", &(value->datex_Crc_nbr), tab_value + 1)) < 0) return ret;
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_DatexDataPacket_datex_Version_number(ASN1WorkSpace *workspace, DatexDataPacket *value, ENUMERATED user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_ENUMERATED(workspace, (ASNINT32*)&value->datex_Version_number, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_DatexDataPacket_datex_Data(ASN1WorkSpace *workspace, DatexDataPacket *value, ASNUINT8 *user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_OCTETSTRING(workspace, &value->datex_Data, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_DatexDataPacket_datex_Crc_nbr(ASN1WorkSpace *workspace, DatexDataPacket *value, ASNUINT8 *user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_OCTETSTRING(workspace, &value->datex_Crc_nbr, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_DatexDataPacket_datex_Version_number(ASN1WorkSpace *workspace, DatexDataPacket *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->datex_Version_number, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_DatexDataPacket_datex_Data(ASN1WorkSpace *workspace, DatexDataPacket *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_OCTETSTRING(workspace, &value->datex_Data, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_DatexDataPacket_datex_Crc_nbr(ASN1WorkSpace *workspace, DatexDataPacket *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_OCTETSTRING(workspace, &value->datex_Crc_nbr, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_DatexDataPacket(DatexDataPacket *value)
{
	int ret = 0;

	unsigned char checkinfo_datex_Version_number[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datex_Data[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datex_Crc_nbr[] = { 
		0x02,0x02,0x02,0x00
	};

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->datex_Version_number), checkinfo_datex_Version_number)) < 0) return ret;
	if ((ret = ASN1_CHECK_OCTETSTRING(&(value->datex_Data), checkinfo_datex_Data)) < 0) return ret;
	if ((ret = ASN1_CHECK_OCTETSTRING(&(value->datex_Crc_nbr), checkinfo_datex_Crc_nbr)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Enc_DatexDataPacket_datex_Version_number(ASN1WorkSpace *workspace, DatexDataPacket_datex_Version_number *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_DatexDataPacket(ASN1WorkSpace *workspace, DatexDataPacket *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_DatexDataPacket_datex_Version_number(workspace, &(value->datex_Version_number), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_OCTETSTRING(workspace, &(value->datex_Data), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_OCTETSTRING(workspace, &(value->datex_Crc_nbr), ASN1IMPL)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_DatexDataPacket(DatexDataPacket *value);
extern int ASN1_BER_Data_Enc_DatexDataPacket(ASN1WorkSpace *workspace, DatexDataPacket *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_DatexDataPacket(ASN1WorkSpace *workspace, DatexDataPacket *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_DatexDataPacket(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_DatexDataPacket(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_DatexDataPacket_datex_Version_number(ASN1WorkSpace *workspace, DatexDataPacket_datex_Version_number *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_DatexDataPacket(ASN1WorkSpace *workspace, DatexDataPacket *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8 *_cpointer;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_DatexDataPacket_datex_Version_number(workspace, &value->datex_Version_number, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_OCTETSTRING(workspace, &value->datex_Data, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_OCTETSTRING(workspace, &value->datex_Crc_nbr, len, ASN1IMPL)) < 0) return ret;
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_DatexDataPacket(DatexDataPacket *value);
extern int ASN1_BER_Data_Dec_DatexDataPacket(ASN1WorkSpace *workspace, DatexDataPacket *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_DatexDataPacket(ASN1WorkSpace *workspace, DatexDataPacket *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_DatexDataPacket(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_DatexDataPacket(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_DatexDataPacket(ASN1WorkSpace *workspace, DatexDataPacket *value)
{
	int ret = 0;
	ASNINT32 ui_datex_Version_number;
	struct Asn1ConsInfo consinfo_datex_Version_number = { ASN1_CONST64(0), ASN1_CONST64(2), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Data = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Crc_nbr = { ASN1_CONST64(2), ASN1_CONST64(2), NULL, 0, CONS, 0, 0 };

	switch(value->datex_Version_number)
	{
	case DatexDataPacket_datex_Version_number_experimental: ui_datex_Version_number = 0; consinfo_datex_Version_number.enumextbit = 0; break;
	case DatexDataPacket_datex_Version_number_version1: ui_datex_Version_number = 1; consinfo_datex_Version_number.enumextbit = 0; break;
	case DatexDataPacket_datex_Version_number_version2: ui_datex_Version_number = 2; consinfo_datex_Version_number.enumextbit = 0; break;
	default: ui_datex_Version_number = value->datex_Version_number; consinfo_datex_Version_number.enumextbit = 1;break;
	}
	if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_datex_Version_number, &consinfo_datex_Version_number)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_OCTETSTRING(workspace, &(value->datex_Data), &consinfo_datex_Data)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_OCTETSTRING(workspace, &(value->datex_Crc_nbr), &consinfo_datex_Crc_nbr)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_DatexDataPacket(DatexDataPacket *value);
extern int ASN1_PER_Align_Data_Enc_DatexDataPacket(ASN1WorkSpace *workspace, DatexDataPacket *value);
int ASN1_PER_Align_Enc_DatexDataPacket(ASN1WorkSpace *workspace, DatexDataPacket *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_DatexDataPacket(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_DatexDataPacket(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_DatexDataPacket(ASN1WorkSpace *workspace, DatexDataPacket *value)
{
	int ret = 0;
	ASNINT32 ui_datex_Version_number;
	struct Asn1ConsInfo consinfo_datex_Version_number = { ASN1_CONST64(0), ASN1_CONST64(2), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Data = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Crc_nbr = { ASN1_CONST64(2), ASN1_CONST64(2), NULL, 0, CONS, 0, 0 };

	if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_datex_Version_number, &consinfo_datex_Version_number)) < 0) return ret;
	if (consinfo_datex_Version_number.enumextbit == 0)
	{
		switch(ui_datex_Version_number)
		{
		case 0: value->datex_Version_number = DatexDataPacket_datex_Version_number_experimental; break;
		case 1: value->datex_Version_number = DatexDataPacket_datex_Version_number_version1; break;
		case 2: value->datex_Version_number = DatexDataPacket_datex_Version_number_version2; break;
		default: break;
		}
	}
	else
	{
		switch(ui_datex_Version_number)
		{
		default: value->datex_Version_number = ui_datex_Version_number; break;
		}
	}
	if ((ret = ASN1_PER_Align_Dec_OCTETSTRING(workspace, &(value->datex_Data), &consinfo_datex_Data)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_OCTETSTRING(workspace, &(value->datex_Crc_nbr), &consinfo_datex_Crc_nbr)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_DatexDataPacket(DatexDataPacket *value);
extern int ASN1_PER_Align_Data_Dec_DatexDataPacket(ASN1WorkSpace *workspace, DatexDataPacket *value);
int ASN1_PER_Align_Dec_DatexDataPacket(ASN1WorkSpace *workspace, DatexDataPacket *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_DatexDataPacket(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_DatexDataPacket(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_DatexDataPacket(ASN1WorkSpace *workspace, DatexDataPacket *value)
{
	int ret = 0;
	ASNINT32 ui_datex_Version_number;
	struct Asn1ConsInfo consinfo_datex_Version_number = { ASN1_CONST64(0), ASN1_CONST64(2), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Data = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Crc_nbr = { ASN1_CONST64(2), ASN1_CONST64(2), NULL, 0, CONS, 0, 0 };

	switch(value->datex_Version_number)
	{
	case DatexDataPacket_datex_Version_number_experimental: ui_datex_Version_number = 0; consinfo_datex_Version_number.enumextbit = 0; break;
	case DatexDataPacket_datex_Version_number_version1: ui_datex_Version_number = 1; consinfo_datex_Version_number.enumextbit = 0; break;
	case DatexDataPacket_datex_Version_number_version2: ui_datex_Version_number = 2; consinfo_datex_Version_number.enumextbit = 0; break;
	default: ui_datex_Version_number = value->datex_Version_number; consinfo_datex_Version_number.enumextbit = 1;break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_datex_Version_number, &consinfo_datex_Version_number)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_OCTETSTRING(workspace, &(value->datex_Data), &consinfo_datex_Data)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_OCTETSTRING(workspace, &(value->datex_Crc_nbr), &consinfo_datex_Crc_nbr)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_DatexDataPacket(DatexDataPacket *value);
extern int ASN1_PER_UNAlign_Data_Enc_DatexDataPacket(ASN1WorkSpace *workspace, DatexDataPacket *value);
int ASN1_PER_UNAlign_Enc_DatexDataPacket(ASN1WorkSpace *workspace, DatexDataPacket *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_DatexDataPacket(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_DatexDataPacket(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_DatexDataPacket(ASN1WorkSpace *workspace, DatexDataPacket *value)
{
	int ret = 0;
	ASNINT32 ui_datex_Version_number;
	struct Asn1ConsInfo consinfo_datex_Version_number = { ASN1_CONST64(0), ASN1_CONST64(2), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Data = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Crc_nbr = { ASN1_CONST64(2), ASN1_CONST64(2), NULL, 0, CONS, 0, 0 };

	if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_datex_Version_number, &consinfo_datex_Version_number)) < 0) return ret;
	if (consinfo_datex_Version_number.enumextbit == 0)
	{
		switch(ui_datex_Version_number)
		{
		case 0: value->datex_Version_number = DatexDataPacket_datex_Version_number_experimental; break;
		case 1: value->datex_Version_number = DatexDataPacket_datex_Version_number_version1; break;
		case 2: value->datex_Version_number = DatexDataPacket_datex_Version_number_version2; break;
		default: break;
		}
	}
	else
	{
		switch(ui_datex_Version_number)
		{
		default: value->datex_Version_number = ui_datex_Version_number; break;
		}
	}
	if ((ret = ASN1_PER_UNAlign_Dec_OCTETSTRING(workspace, &(value->datex_Data), &consinfo_datex_Data)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_OCTETSTRING(workspace, &(value->datex_Crc_nbr), &consinfo_datex_Crc_nbr)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_DatexDataPacket(DatexDataPacket *value);
extern int ASN1_PER_UNAlign_Data_Dec_DatexDataPacket(ASN1WorkSpace *workspace, DatexDataPacket *value);
int ASN1_PER_UNAlign_Dec_DatexDataPacket(ASN1WorkSpace *workspace, DatexDataPacket *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_DatexDataPacket(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_DatexDataPacket(value)) < 0) return ret;
	return ret;
}

/********************************************************
*Cost                                                   *
********************************************************/
int ASN1_Print_Cost(Cost *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("Cost");
	// Type OCTET STRING
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_OCTETSTRING("amount_Currency_code", &(value->amount_Currency_code), tab_value + 1)) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("amount_Factor_quantity", &(value->amount_Factor_quantity))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("amount_Quantity_quantity", &(value->amount_Quantity_quantity))) < 0) return ret;
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_Cost_amount_Currency_code(ASN1WorkSpace *workspace, Cost *value, ASNUINT8 *user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_OCTETSTRING(workspace, &value->amount_Currency_code, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_Cost_amount_Factor_quantity(ASN1WorkSpace *workspace, Cost *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->amount_Factor_quantity, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_Cost_amount_Quantity_quantity(ASN1WorkSpace *workspace, Cost *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->amount_Quantity_quantity, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_Cost_amount_Currency_code(ASN1WorkSpace *workspace, Cost *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_OCTETSTRING(workspace, &value->amount_Currency_code, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_Cost_amount_Factor_quantity(ASN1WorkSpace *workspace, Cost *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->amount_Factor_quantity, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_Cost_amount_Quantity_quantity(ASN1WorkSpace *workspace, Cost *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->amount_Quantity_quantity, user_value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_Cost(Cost *value)
{
	int ret = 0;

	unsigned char checkinfo_amount_Currency_code[] = { 
		0x02,0x03,0x03,0x00
	};
	unsigned char checkinfo_amount_Factor_quantity[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_amount_Quantity_quantity[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_OCTETSTRING(&(value->amount_Currency_code), checkinfo_amount_Currency_code)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->amount_Factor_quantity), checkinfo_amount_Factor_quantity)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->amount_Quantity_quantity), checkinfo_amount_Quantity_quantity)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_Cost(ASN1WorkSpace *workspace, Cost *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_OCTETSTRING(workspace, &(value->amount_Currency_code), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->amount_Factor_quantity), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->amount_Quantity_quantity), ASN1IMPL)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Cost(Cost *value);
extern int ASN1_BER_Data_Enc_Cost(ASN1WorkSpace *workspace, Cost *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_Cost(ASN1WorkSpace *workspace, Cost *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_Cost(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Cost(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_Cost(ASN1WorkSpace *workspace, Cost *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8 *_cpointer;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_OCTETSTRING(workspace, &value->amount_Currency_code, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->amount_Factor_quantity, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->amount_Quantity_quantity, len, ASN1IMPL)) < 0) return ret;
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_Cost(Cost *value);
extern int ASN1_BER_Data_Dec_Cost(ASN1WorkSpace *workspace, Cost *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_Cost(ASN1WorkSpace *workspace, Cost *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Cost(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_Cost(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_Cost(ASN1WorkSpace *workspace, Cost *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_amount_Currency_code = { ASN1_CONST64(3), ASN1_CONST64(3), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_amount_Factor_quantity = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_amount_Quantity_quantity = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_Align_Enc_OCTETSTRING(workspace, &(value->amount_Currency_code), &consinfo_amount_Currency_code)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->amount_Factor_quantity), &consinfo_amount_Factor_quantity)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->amount_Quantity_quantity), &consinfo_amount_Quantity_quantity)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_Cost(Cost *value);
extern int ASN1_PER_Align_Data_Enc_Cost(ASN1WorkSpace *workspace, Cost *value);
int ASN1_PER_Align_Enc_Cost(ASN1WorkSpace *workspace, Cost *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Cost(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_Cost(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_Cost(ASN1WorkSpace *workspace, Cost *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_amount_Currency_code = { ASN1_CONST64(3), ASN1_CONST64(3), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_amount_Factor_quantity = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_amount_Quantity_quantity = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_Align_Dec_OCTETSTRING(workspace, &(value->amount_Currency_code), &consinfo_amount_Currency_code)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->amount_Factor_quantity), &consinfo_amount_Factor_quantity)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->amount_Quantity_quantity), &consinfo_amount_Quantity_quantity)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_Cost(Cost *value);
extern int ASN1_PER_Align_Data_Dec_Cost(ASN1WorkSpace *workspace, Cost *value);
int ASN1_PER_Align_Dec_Cost(ASN1WorkSpace *workspace, Cost *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_Cost(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Cost(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_Cost(ASN1WorkSpace *workspace, Cost *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_amount_Currency_code = { ASN1_CONST64(3), ASN1_CONST64(3), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_amount_Factor_quantity = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_amount_Quantity_quantity = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_UNAlign_Enc_OCTETSTRING(workspace, &(value->amount_Currency_code), &consinfo_amount_Currency_code)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->amount_Factor_quantity), &consinfo_amount_Factor_quantity)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->amount_Quantity_quantity), &consinfo_amount_Quantity_quantity)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_Cost(Cost *value);
extern int ASN1_PER_UNAlign_Data_Enc_Cost(ASN1WorkSpace *workspace, Cost *value);
int ASN1_PER_UNAlign_Enc_Cost(ASN1WorkSpace *workspace, Cost *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Cost(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_Cost(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_Cost(ASN1WorkSpace *workspace, Cost *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_amount_Currency_code = { ASN1_CONST64(3), ASN1_CONST64(3), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_amount_Factor_quantity = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_amount_Quantity_quantity = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_UNAlign_Dec_OCTETSTRING(workspace, &(value->amount_Currency_code), &consinfo_amount_Currency_code)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->amount_Factor_quantity), &consinfo_amount_Factor_quantity)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->amount_Quantity_quantity), &consinfo_amount_Quantity_quantity)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_Cost(Cost *value);
extern int ASN1_PER_UNAlign_Data_Dec_Cost(ASN1WorkSpace *workspace, Cost *value);
int ASN1_PER_UNAlign_Dec_Cost(ASN1WorkSpace *workspace, Cost *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_Cost(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Cost(value)) < 0) return ret;
	return ret;
}

/********************************************************
*IsoTime_time_SecondFractions                           *
********************************************************/
int ASN1_Print_IsoTime_time_SecondFractions(IsoTime_time_SecondFractions *value, int tab_value)
{
	int ret = 0;
	// CHOICE : default
	ASN1_Print_CHOICE(" ");
	if (value == NULL) return -1;
	switch (value->M) {
	case DEF_IsoTime_time_SecondFractions_deci_seconds:
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("deci_seconds", &value->elements.deci_seconds)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_IsoTime_time_SecondFractions_centi_seconds:
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("centi_seconds", &value->elements.centi_seconds)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_IsoTime_time_SecondFractions_milli_seconds:
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("milli_seconds", &value->elements.milli_seconds)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: return -1;
}
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_IsoTime_time_SecondFractions_deci_seconds(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->M = DEF_IsoTime_time_SecondFractions_deci_seconds;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->elements.deci_seconds, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_IsoTime_time_SecondFractions_centi_seconds(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->M = DEF_IsoTime_time_SecondFractions_centi_seconds;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->elements.centi_seconds, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_IsoTime_time_SecondFractions_milli_seconds(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->M = DEF_IsoTime_time_SecondFractions_milli_seconds;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->elements.milli_seconds, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_IsoTime_time_SecondFractions_deci_seconds(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->M == DEF_IsoTime_time_SecondFractions_deci_seconds)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->elements.deci_seconds, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_IsoTime_time_SecondFractions_centi_seconds(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->M == DEF_IsoTime_time_SecondFractions_centi_seconds)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->elements.centi_seconds, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_IsoTime_time_SecondFractions_milli_seconds(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->M == DEF_IsoTime_time_SecondFractions_milli_seconds)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->elements.milli_seconds, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_CHECK_IsoTime_time_SecondFractions(IsoTime_time_SecondFractions *value)
{
	int ret = 0;

	unsigned char checkinfo_deci_seconds[] = { 
		0x02,0x00,0x09,0x00
	};
	unsigned char checkinfo_centi_seconds[] = { 
		0x02,0x00,0x63,0x00
	};
	unsigned char checkinfo_milli_seconds[] = { 
		0x02,0x00,0x82,0x03,0xE7,0x00
	};

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_IsoTime_time_SecondFractions_deci_seconds:
		if ((ret = ASN1_CHECK_INTEGER(&value->elements.deci_seconds, checkinfo_deci_seconds)) < 0) return ret;
		break;
	case DEF_IsoTime_time_SecondFractions_centi_seconds:
		if ((ret = ASN1_CHECK_INTEGER(&value->elements.centi_seconds, checkinfo_centi_seconds)) < 0) return ret;
		break;
	case DEF_IsoTime_time_SecondFractions_milli_seconds:
		if ((ret = ASN1_CHECK_INTEGER(&value->elements.milli_seconds, checkinfo_milli_seconds)) < 0) return ret;
		break;
	default: break;
	}
	return ret;
}
int ASN1_BER_Data_Enc_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value, ASN1TagType tagFlag)
{
	int ret = 0;
	switch(value->M)
	{
	case DEF_IsoTime_time_SecondFractions_deci_seconds:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->elements.deci_seconds), ASN1IMPL)) < 0) return ret;
		break;
	case DEF_IsoTime_time_SecondFractions_centi_seconds:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->elements.centi_seconds), ASN1IMPL)) < 0) return ret;
		break;
	case DEF_IsoTime_time_SecondFractions_milli_seconds:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->elements.milli_seconds), ASN1IMPL)) < 0) return ret;
		break;
	}
	return ret;
}
extern int ASN1_CHECK_IsoTime_time_SecondFractions(IsoTime_time_SecondFractions *value);
extern int ASN1_BER_Data_Enc_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_IsoTime_time_SecondFractions(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_IsoTime_time_SecondFractions(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	value->M = 0;
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	switch(tag)
	{
	case ITS_ASN_CONT | ITS_ASN_PRIM | 0:
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->elements.deci_seconds, len, ASN1IMPL)) < 0) return ret;
		value->M = DEF_IsoTime_time_SecondFractions_deci_seconds;
		break;
	case ITS_ASN_CONT | ITS_ASN_PRIM | 1:
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->elements.centi_seconds, len, ASN1IMPL)) < 0) return ret;
		value->M = DEF_IsoTime_time_SecondFractions_centi_seconds;
		break;
	case ITS_ASN_CONT | ITS_ASN_PRIM | 2:
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->elements.milli_seconds, len, ASN1IMPL)) < 0) return ret;
		value->M = DEF_IsoTime_time_SecondFractions_milli_seconds;
		break;
	}
	return ret;
}
extern int ASN1_CHECK_IsoTime_time_SecondFractions(IsoTime_time_SecondFractions *value);
extern int ASN1_BER_Data_Dec_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_IsoTime_time_SecondFractions(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_IsoTime_time_SecondFractions(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_deci_seconds = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_centi_seconds = { ASN1_CONST64(0), ASN1_CONST64(99), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_milli_seconds = { ASN1_CONST64(0), ASN1_CONST64(999), NULL, 0, CONS, 0, 0 };

	ASNINT64 ui;
	ASNBOOL extbit = 1;
	switch(value->M)
	{
	case DEF_IsoTime_time_SecondFractions_deci_seconds: ui = 0; extbit = 0; break;
	case DEF_IsoTime_time_SecondFractions_centi_seconds: ui = 1; extbit = 0; break;
	case DEF_IsoTime_time_SecondFractions_milli_seconds: ui = 2; extbit = 0; break;
	default: break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_Choice_ENUMERATED(workspace, ui, extbit, 1, 3)) < 0) return ret;
	switch(value->M)
	{
	case DEF_IsoTime_time_SecondFractions_deci_seconds:
		if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->elements.deci_seconds), &consinfo_deci_seconds)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_IsoTime_time_SecondFractions_centi_seconds:
		if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->elements.centi_seconds), &consinfo_centi_seconds)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_IsoTime_time_SecondFractions_milli_seconds:
		if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->elements.milli_seconds), &consinfo_milli_seconds)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: break;
	}
	return ret;
}
extern int ASN1_CHECK_IsoTime_time_SecondFractions(IsoTime_time_SecondFractions *value);
extern int ASN1_PER_Align_Data_Enc_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value);
int ASN1_PER_Align_Enc_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_IsoTime_time_SecondFractions(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_IsoTime_time_SecondFractions(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_deci_seconds = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_centi_seconds = { ASN1_CONST64(0), ASN1_CONST64(99), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_milli_seconds = { ASN1_CONST64(0), ASN1_CONST64(999), NULL, 0, CONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	if ((ret = ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 1, 3)) < 0) return ret;

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_IsoTime_time_SecondFractions_deci_seconds;
			break;
		case 1: index = DEF_IsoTime_time_SecondFractions_centi_seconds;
			break;
		case 2: index = DEF_IsoTime_time_SecondFractions_milli_seconds;
			break;
		default: break;
		}
	}
	else
	{
		switch(ui)
		{
		default: break;
		}
	}
	if ((ret = ASN1_GetM(&value->M, index)) < 0) return ret;
	switch(index)
	{
	case DEF_IsoTime_time_SecondFractions_deci_seconds:
		if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->elements.deci_seconds), &consinfo_deci_seconds)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_IsoTime_time_SecondFractions_centi_seconds:
		if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->elements.centi_seconds), &consinfo_centi_seconds)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_IsoTime_time_SecondFractions_milli_seconds:
		if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->elements.milli_seconds), &consinfo_milli_seconds)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, ALIGN); break;
	}
	return ret;
}
extern int ASN1_CHECK_IsoTime_time_SecondFractions(IsoTime_time_SecondFractions *value);
extern int ASN1_PER_Align_Data_Dec_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value);
int ASN1_PER_Align_Dec_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_IsoTime_time_SecondFractions(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_IsoTime_time_SecondFractions(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_deci_seconds = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_centi_seconds = { ASN1_CONST64(0), ASN1_CONST64(99), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_milli_seconds = { ASN1_CONST64(0), ASN1_CONST64(999), NULL, 0, CONS, 0, 0 };

	ASNINT64 ui;
	ASNBOOL extbit = 1;
	switch(value->M)
	{
	case DEF_IsoTime_time_SecondFractions_deci_seconds: ui = 0; extbit = 0; break;
	case DEF_IsoTime_time_SecondFractions_centi_seconds: ui = 1; extbit = 0; break;
	case DEF_IsoTime_time_SecondFractions_milli_seconds: ui = 2; extbit = 0; break;
	default: break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_Choice_ENUMERATED(workspace, ui, extbit, 1, 3)) < 0) return ret;
	switch(value->M)
	{
	case DEF_IsoTime_time_SecondFractions_deci_seconds:
		if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->elements.deci_seconds), &consinfo_deci_seconds)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_IsoTime_time_SecondFractions_centi_seconds:
		if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->elements.centi_seconds), &consinfo_centi_seconds)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_IsoTime_time_SecondFractions_milli_seconds:
		if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->elements.milli_seconds), &consinfo_milli_seconds)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: break;
	}
	return ret;
}
extern int ASN1_CHECK_IsoTime_time_SecondFractions(IsoTime_time_SecondFractions *value);
extern int ASN1_PER_UNAlign_Data_Enc_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value);
int ASN1_PER_UNAlign_Enc_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_IsoTime_time_SecondFractions(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_IsoTime_time_SecondFractions(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_deci_seconds = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_centi_seconds = { ASN1_CONST64(0), ASN1_CONST64(99), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_milli_seconds = { ASN1_CONST64(0), ASN1_CONST64(999), NULL, 0, CONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	if ((ret = ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 1, 3)) < 0) return ret;

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_IsoTime_time_SecondFractions_deci_seconds;
			break;
		case 1: index = DEF_IsoTime_time_SecondFractions_centi_seconds;
			break;
		case 2: index = DEF_IsoTime_time_SecondFractions_milli_seconds;
			break;
		default: break;
		}
	}
	else
	{
		switch(ui)
		{
		default: break;
		}
	}
	if ((ret = ASN1_GetM(&value->M, index)) < 0) return ret;
	switch(index)
	{
	case DEF_IsoTime_time_SecondFractions_deci_seconds:
		if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->elements.deci_seconds), &consinfo_deci_seconds)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_IsoTime_time_SecondFractions_centi_seconds:
		if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->elements.centi_seconds), &consinfo_centi_seconds)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_IsoTime_time_SecondFractions_milli_seconds:
		if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->elements.milli_seconds), &consinfo_milli_seconds)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
extern int ASN1_CHECK_IsoTime_time_SecondFractions(IsoTime_time_SecondFractions *value);
extern int ASN1_PER_UNAlign_Data_Dec_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value);
int ASN1_PER_UNAlign_Dec_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_IsoTime_time_SecondFractions(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_IsoTime_time_SecondFractions(value)) < 0) return ret;
	return ret;
}

/********************************************************
*IsoTime_time_Timezone                                  *
********************************************************/
int ASN1_Print_IsoTime_time_Timezone(IsoTime_time_Timezone *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : default
	ASN1_Print_SEQ(" ");
	if (value->DEF_IsoTime_time_Timezone_timezone_Hour_qty == 1)
	{ /* DEFAULT start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("timezone_Hour_qty", &(value->timezone_Hour_qty))) < 0) return ret;
	} /* DEFAULT end */
	if (value->DEF_IsoTime_time_Timezone_time_Minute_qty == 1)
	{ /* DEFAULT start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("time_Minute_qty", &(value->time_Minute_qty))) < 0) return ret;
	} /* DEFAULT end */
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_IsoTime_time_Timezone_timezone_Hour_qty(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_IsoTime_time_Timezone_timezone_Hour_qty = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->timezone_Hour_qty, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_IsoTime_time_Timezone_time_Minute_qty(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_IsoTime_time_Timezone_time_Minute_qty = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->time_Minute_qty, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_IsoTime_time_Timezone_timezone_Hour_qty(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_IsoTime_time_Timezone_timezone_Hour_qty == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->timezone_Hour_qty, user_value)) < 0) return ret;
	}
	else return -3;
	return ret;
}
int ASN1_GET_IsoTime_time_Timezone_time_Minute_qty(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_IsoTime_time_Timezone_time_Minute_qty == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->time_Minute_qty, user_value)) < 0) return ret;
	}
	else return -3;
	return ret;
}
int ASN1_CHECK_IsoTime_time_Timezone(IsoTime_time_Timezone *value)
{
	int ret = 0;

	unsigned char checkinfo_timezone_Hour_qty[] = { 
		0x02,0x81,0xF3,0x0D,0x00
	};
	unsigned char checkinfo_time_Minute_qty[] = { 
		0x02,0x00,0x3B,0x00
	};

	if (value == NULL) return -1;
	if (value->DEF_IsoTime_time_Timezone_timezone_Hour_qty == 1)
	{ /* DEFAULT start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->timezone_Hour_qty), checkinfo_timezone_Hour_qty)) < 0) return ret;
	} /* DEFAULT end */
	if (value->DEF_IsoTime_time_Timezone_time_Minute_qty == 1)
	{ /* DEFAULT start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->time_Minute_qty), checkinfo_time_Minute_qty)) < 0) return ret;
	} /* DEFAULT end */
	return ret;
}
int ASN1_BER_Data_Enc_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_Timezone_timezone_Hour_qty == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->timezone_Hour_qty), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_Timezone_time_Minute_qty == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->time_Minute_qty), ASN1IMPL)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_IsoTime_time_Timezone(IsoTime_time_Timezone *value);
extern int ASN1_BER_Data_Enc_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_IsoTime_time_Timezone(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_IsoTime_time_Timezone(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value, int length, ASN1TagType tagFlag)
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
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 0))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->timezone_Hour_qty, len, ASN1IMPL)) < 0) return ret;
		value->DEF_IsoTime_time_Timezone_timezone_Hour_qty = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 1))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->time_Minute_qty, len, ASN1IMPL)) < 0) return ret;
		value->DEF_IsoTime_time_Timezone_time_Minute_qty = 1;
	}
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_IsoTime_time_Timezone(IsoTime_time_Timezone *value);
extern int ASN1_BER_Data_Dec_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_IsoTime_time_Timezone(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_IsoTime_time_Timezone(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_timezone_Hour_qty = { ASN1_CONST64(-13), ASN1_CONST64(13), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Minute_qty = { ASN1_CONST64(0), ASN1_CONST64(59), NULL, 0, CONS, 0, 0 };

	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_IsoTime_time_Timezone_timezone_Hour_qty == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_IsoTime_time_Timezone_time_Minute_qty == 1 ? 1 : 0) )) < 0) return ret;
	if (value->DEF_IsoTime_time_Timezone_timezone_Hour_qty == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->timezone_Hour_qty), &consinfo_timezone_Hour_qty)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_Timezone_time_Minute_qty == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->time_Minute_qty), &consinfo_time_Minute_qty)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_IsoTime_time_Timezone(IsoTime_time_Timezone *value);
extern int ASN1_PER_Align_Data_Enc_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value);
int ASN1_PER_Align_Enc_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_IsoTime_time_Timezone(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_IsoTime_time_Timezone(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_timezone_Hour_qty = { ASN1_CONST64(-13), ASN1_CONST64(13), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Minute_qty = { ASN1_CONST64(0), ASN1_CONST64(59), NULL, 0, CONS, 0, 0 };

	ASNUINT8 *_optvalue;
	if ((ret = ASN1_PER_Dec_Opt_Def_bit(workspace, 2, &_optvalue)) < 0) return ret;
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_IsoTime_time_Timezone_timezone_Hour_qty = 1;
		if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->timezone_Hour_qty), &consinfo_timezone_Hour_qty)) < 0) return ret;
	}
	else
	{
		value->timezone_Hour_qty = 0;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_IsoTime_time_Timezone_time_Minute_qty = 1;
		if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->time_Minute_qty), &consinfo_time_Minute_qty)) < 0) return ret;
	}
	else
	{
		value->time_Minute_qty = 0;
	}
	return ret;
}
extern int ASN1_CHECK_IsoTime_time_Timezone(IsoTime_time_Timezone *value);
extern int ASN1_PER_Align_Data_Dec_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value);
int ASN1_PER_Align_Dec_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_IsoTime_time_Timezone(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_IsoTime_time_Timezone(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_timezone_Hour_qty = { ASN1_CONST64(-13), ASN1_CONST64(13), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Minute_qty = { ASN1_CONST64(0), ASN1_CONST64(59), NULL, 0, CONS, 0, 0 };

	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_IsoTime_time_Timezone_timezone_Hour_qty == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_IsoTime_time_Timezone_time_Minute_qty == 1 ? 1 : 0) )) < 0) return ret;
	if (value->DEF_IsoTime_time_Timezone_timezone_Hour_qty == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->timezone_Hour_qty), &consinfo_timezone_Hour_qty)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_Timezone_time_Minute_qty == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->time_Minute_qty), &consinfo_time_Minute_qty)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_IsoTime_time_Timezone(IsoTime_time_Timezone *value);
extern int ASN1_PER_UNAlign_Data_Enc_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value);
int ASN1_PER_UNAlign_Enc_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_IsoTime_time_Timezone(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_IsoTime_time_Timezone(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_timezone_Hour_qty = { ASN1_CONST64(-13), ASN1_CONST64(13), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Minute_qty = { ASN1_CONST64(0), ASN1_CONST64(59), NULL, 0, CONS, 0, 0 };

	ASNUINT8 *_optvalue;
	if ((ret = ASN1_PER_Dec_Opt_Def_bit(workspace, 2, &_optvalue)) < 0) return ret;
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_IsoTime_time_Timezone_timezone_Hour_qty = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->timezone_Hour_qty), &consinfo_timezone_Hour_qty)) < 0) return ret;
	}
	else
	{
		value->timezone_Hour_qty = 0;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_IsoTime_time_Timezone_time_Minute_qty = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->time_Minute_qty), &consinfo_time_Minute_qty)) < 0) return ret;
	}
	else
	{
		value->time_Minute_qty = 0;
	}
	return ret;
}
extern int ASN1_CHECK_IsoTime_time_Timezone(IsoTime_time_Timezone *value);
extern int ASN1_PER_UNAlign_Data_Dec_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value);
int ASN1_PER_UNAlign_Dec_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_IsoTime_time_Timezone(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_IsoTime_time_Timezone(value)) < 0) return ret;
	return ret;
}

/********************************************************
*IsoTime                                                *
********************************************************/
int ASN1_Print_IsoTime(IsoTime *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("IsoTime");
	if (value->DEF_IsoTime_time_Year_qty == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("time_Year_qty", &(value->time_Year_qty))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_IsoTime_time_Month_qty == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("time_Month_qty", &(value->time_Month_qty))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_IsoTime_time_Day_qty == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("time_Day_qty", &(value->time_Day_qty))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_IsoTime_time_Hour_qty == 1)
	{ /* DEFAULT start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("time_Hour_qty", &(value->time_Hour_qty))) < 0) return ret;
	} /* DEFAULT end */
	if (value->DEF_IsoTime_time_Minute_qty == 1)
	{ /* DEFAULT start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("time_Minute_qty", &(value->time_Minute_qty))) < 0) return ret;
	} /* DEFAULT end */
	if (value->DEF_IsoTime_time_Second_qty == 1)
	{ /* DEFAULT start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("time_Second_qty", &(value->time_Second_qty))) < 0) return ret;
	} /* DEFAULT end */
	if (value->DEF_IsoTime_time_SecondFractions == 1)
	{ /* DEFAULT start */
		// Type Reference IsoTime_time_SecondFractions
		if (Compare_Letter(tab_value, "time-SecondFractions")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("time-SecondFractions = ");
		}
		if ((ret = ASN1_Print_IsoTime_time_SecondFractions((IsoTime_time_SecondFractions *)value->time_SecondFractions, tab_value + 1)) < 0) return ret;
	} /* DEFAULT end */
	if (value->DEF_IsoTime_time_Timezone == 1)
	{ /*OPTIONAL start */
		// Type Reference IsoTime_time_Timezone
		if (Compare_Letter(tab_value, "time-Timezone")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("time-Timezone = ");
		}
		if ((ret = ASN1_Print_IsoTime_time_Timezone((IsoTime_time_Timezone *)value->time_Timezone, tab_value + 1)) < 0) return ret;
	} /* OPTIONAL end */
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_IsoTime_time_Year_qty(ASN1WorkSpace *workspace, IsoTime *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_IsoTime_time_Year_qty = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->time_Year_qty, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_IsoTime_time_Month_qty(ASN1WorkSpace *workspace, IsoTime *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_IsoTime_time_Month_qty = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->time_Month_qty, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_IsoTime_time_Day_qty(ASN1WorkSpace *workspace, IsoTime *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_IsoTime_time_Day_qty = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->time_Day_qty, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_IsoTime_time_Hour_qty(ASN1WorkSpace *workspace, IsoTime *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_IsoTime_time_Hour_qty = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->time_Hour_qty, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_IsoTime_time_Minute_qty(ASN1WorkSpace *workspace, IsoTime *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_IsoTime_time_Minute_qty = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->time_Minute_qty, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_IsoTime_time_Second_qty(ASN1WorkSpace *workspace, IsoTime *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_IsoTime_time_Second_qty = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->time_Second_qty, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime *value, IsoTime_time_SecondFractions *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->time_SecondFractions = (IsoTime_time_SecondFractions *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime_time_SecondFractions));
	memset(value->time_SecondFractions, 0, sizeof(IsoTime_time_SecondFractions));
	value->DEF_IsoTime_time_SecondFractions = 1;
	memmove(value->time_SecondFractions, user_value, sizeof(IsoTime_time_SecondFractions));
	return ret;
}
int ASN1_SET_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime *value, IsoTime_time_Timezone *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->time_Timezone = (IsoTime_time_Timezone *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime_time_Timezone));
	memset(value->time_Timezone, 0, sizeof(IsoTime_time_Timezone));
	value->DEF_IsoTime_time_Timezone = 1;
	memmove(value->time_Timezone, user_value, sizeof(IsoTime_time_Timezone));
	return ret;
}
int ASN1_GET_IsoTime_time_Year_qty(ASN1WorkSpace *workspace, IsoTime *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_IsoTime_time_Year_qty == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->time_Year_qty, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_IsoTime_time_Month_qty(ASN1WorkSpace *workspace, IsoTime *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_IsoTime_time_Month_qty == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->time_Month_qty, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_IsoTime_time_Day_qty(ASN1WorkSpace *workspace, IsoTime *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_IsoTime_time_Day_qty == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->time_Day_qty, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_IsoTime_time_Hour_qty(ASN1WorkSpace *workspace, IsoTime *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_IsoTime_time_Hour_qty == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->time_Hour_qty, user_value)) < 0) return ret;
	}
	else return -3;
	return ret;
}
int ASN1_GET_IsoTime_time_Minute_qty(ASN1WorkSpace *workspace, IsoTime *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_IsoTime_time_Minute_qty == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->time_Minute_qty, user_value)) < 0) return ret;
	}
	else return -3;
	return ret;
}
int ASN1_GET_IsoTime_time_Second_qty(ASN1WorkSpace *workspace, IsoTime *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_IsoTime_time_Second_qty == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->time_Second_qty, user_value)) < 0) return ret;
	}
	else return -3;
	return ret;
}
int ASN1_GET_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime *value, IsoTime_time_SecondFractions **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_IsoTime_time_SecondFractions == 1)
	{
		*user_value = value->time_SecondFractions;
	}
	else return -3;
	return ret;
}
int ASN1_GET_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime *value, IsoTime_time_Timezone **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_IsoTime_time_Timezone == 1)
	{
		*user_value = value->time_Timezone;
	}
	else return -2;
	return ret;
}
extern int ASN1_CHECK_IsoTime_time_SecondFractions(IsoTime_time_SecondFractions *value);
extern int ASN1_CHECK_IsoTime_time_Timezone(IsoTime_time_Timezone *value);
int ASN1_CHECK_IsoTime(IsoTime *value)
{
	int ret = 0;

	unsigned char checkinfo_time_Year_qty[] = { 
		0x02,0x83,0xFF,0x80,0x00,0x82,0x7F,0xFF,0x00
	};
	unsigned char checkinfo_time_Month_qty[] = { 
		0x02,0x01,0x0C,0x00
	};
	unsigned char checkinfo_time_Day_qty[] = { 
		0x02,0x01,0x1F,0x00
	};
	unsigned char checkinfo_time_Hour_qty[] = { 
		0x02,0x00,0x17,0x00
	};
	unsigned char checkinfo_time_Minute_qty[] = { 
		0x02,0x00,0x3B,0x00
	};
	unsigned char checkinfo_time_Second_qty[] = { 
		0x02,0x00,0x3C,0x00
	};
	unsigned char checkinfo_time_SecondFractions[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_time_Timezone[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if (value->DEF_IsoTime_time_Year_qty == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->time_Year_qty), checkinfo_time_Year_qty)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_IsoTime_time_Month_qty == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->time_Month_qty), checkinfo_time_Month_qty)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_IsoTime_time_Day_qty == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->time_Day_qty), checkinfo_time_Day_qty)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_IsoTime_time_Hour_qty == 1)
	{ /* DEFAULT start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->time_Hour_qty), checkinfo_time_Hour_qty)) < 0) return ret;
	} /* DEFAULT end */
	if (value->DEF_IsoTime_time_Minute_qty == 1)
	{ /* DEFAULT start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->time_Minute_qty), checkinfo_time_Minute_qty)) < 0) return ret;
	} /* DEFAULT end */
	if (value->DEF_IsoTime_time_Second_qty == 1)
	{ /* DEFAULT start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->time_Second_qty), checkinfo_time_Second_qty)) < 0) return ret;
	} /* DEFAULT end */
	if (value->DEF_IsoTime_time_SecondFractions == 1)
	{ /* DEFAULT start */
		if ((ret = ASN1_CHECK_IsoTime_time_SecondFractions(value->time_SecondFractions)) < 0) return ret;
	} /* DEFAULT end */
	if (value->DEF_IsoTime_time_Timezone == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_IsoTime_time_Timezone(value->time_Timezone)) < 0) return ret;
	} /* OPTIONAL end */
	return ret;
}
extern int ASN1_BER_Data_Enc_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_Year_qty == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->time_Year_qty), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_Month_qty == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->time_Month_qty), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_Day_qty == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->time_Day_qty), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_Hour_qty == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->time_Hour_qty), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_Minute_qty == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->time_Minute_qty), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_Second_qty == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->time_Second_qty), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_SecondFractions == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 6)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_IsoTime_time_SecondFractions(workspace, value->time_SecondFractions, ASN1EXPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_Timezone == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 7)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_IsoTime_time_Timezone(workspace, value->time_Timezone, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_IsoTime(IsoTime *value);
extern int ASN1_BER_Data_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_IsoTime(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_IsoTime(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	ASNUINT8 *_cpointer;
	value->time_SecondFractions = (IsoTime_time_SecondFractions *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime_time_SecondFractions));
	memset(value->time_SecondFractions, 0, sizeof(IsoTime_time_SecondFractions));
	value->time_Timezone = (IsoTime_time_Timezone *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime_time_Timezone));
	memset(value->time_Timezone, 0, sizeof(IsoTime_time_Timezone));
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 0))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->time_Year_qty, len, ASN1IMPL)) < 0) return ret;
		value->DEF_IsoTime_time_Year_qty = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 1))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->time_Month_qty, len, ASN1IMPL)) < 0) return ret;
		value->DEF_IsoTime_time_Month_qty = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 2))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->time_Day_qty, len, ASN1IMPL)) < 0) return ret;
		value->DEF_IsoTime_time_Day_qty = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 3))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->time_Hour_qty, len, ASN1IMPL)) < 0) return ret;
		value->DEF_IsoTime_time_Hour_qty = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 4))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->time_Minute_qty, len, ASN1IMPL)) < 0) return ret;
		value->DEF_IsoTime_time_Minute_qty = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 5))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->time_Second_qty, len, ASN1IMPL)) < 0) return ret;
		value->DEF_IsoTime_time_Second_qty = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_CONS | 6))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 6)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_IsoTime_time_SecondFractions(workspace, value->time_SecondFractions, len, ASN1EXPL)) < 0) return ret;
		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->DEF_IsoTime_time_SecondFractions = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_CONS | 7))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 7)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_IsoTime_time_Timezone(workspace, value->time_Timezone, len, ASN1IMPL)) < 0) return ret;
		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->DEF_IsoTime_time_Timezone = 1;
	}
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_IsoTime(IsoTime *value);
extern int ASN1_BER_Data_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_IsoTime(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_IsoTime(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Enc_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value);
extern int ASN1_PER_Align_Data_Enc_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value);
int ASN1_PER_Align_Data_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_time_Year_qty = { ASN1_CONST64(-32768), ASN1_CONST64(32767), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Month_qty = { ASN1_CONST64(1), ASN1_CONST64(12), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Day_qty = { ASN1_CONST64(1), ASN1_CONST64(31), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Hour_qty = { ASN1_CONST64(0), ASN1_CONST64(23), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Minute_qty = { ASN1_CONST64(0), ASN1_CONST64(59), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Second_qty = { ASN1_CONST64(0), ASN1_CONST64(60), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_SecondFractions = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Timezone = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_IsoTime_time_Year_qty == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_IsoTime_time_Month_qty == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_IsoTime_time_Day_qty == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_IsoTime_time_Hour_qty == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_IsoTime_time_Minute_qty == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_IsoTime_time_Second_qty == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_IsoTime_time_SecondFractions == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_IsoTime_time_Timezone == 1 ? 1 : 0) )) < 0) return ret;
	if (value->DEF_IsoTime_time_Year_qty == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->time_Year_qty), &consinfo_time_Year_qty)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_Month_qty == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->time_Month_qty), &consinfo_time_Month_qty)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_Day_qty == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->time_Day_qty), &consinfo_time_Day_qty)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_Hour_qty == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->time_Hour_qty), &consinfo_time_Hour_qty)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_Minute_qty == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->time_Minute_qty), &consinfo_time_Minute_qty)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_Second_qty == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->time_Second_qty), &consinfo_time_Second_qty)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_SecondFractions == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_IsoTime_time_SecondFractions(workspace, value->time_SecondFractions)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_Timezone == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_IsoTime_time_Timezone(workspace, value->time_Timezone)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_IsoTime(IsoTime *value);
extern int ASN1_PER_Align_Data_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
int ASN1_PER_Align_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_IsoTime(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_IsoTime(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Dec_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value);
extern int ASN1_PER_Align_Data_Dec_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value);
int ASN1_PER_Align_Data_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_time_Year_qty = { ASN1_CONST64(-32768), ASN1_CONST64(32767), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Month_qty = { ASN1_CONST64(1), ASN1_CONST64(12), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Day_qty = { ASN1_CONST64(1), ASN1_CONST64(31), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Hour_qty = { ASN1_CONST64(0), ASN1_CONST64(23), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Minute_qty = { ASN1_CONST64(0), ASN1_CONST64(59), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Second_qty = { ASN1_CONST64(0), ASN1_CONST64(60), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_SecondFractions = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Timezone = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNUINT8 *_optvalue;
	if ((ret = ASN1_PER_Dec_Opt_Def_bit(workspace, 8, &_optvalue)) < 0) return ret;
	value->time_SecondFractions = (IsoTime_time_SecondFractions *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime_time_SecondFractions));
	memset(value->time_SecondFractions, 0, sizeof(IsoTime_time_SecondFractions));
	value->time_Timezone = (IsoTime_time_Timezone *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime_time_Timezone));
	memset(value->time_Timezone, 0, sizeof(IsoTime_time_Timezone));
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_IsoTime_time_Year_qty = 1;
		if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->time_Year_qty), &consinfo_time_Year_qty)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_IsoTime_time_Month_qty = 1;
		if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->time_Month_qty), &consinfo_time_Month_qty)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_IsoTime_time_Day_qty = 1;
		if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->time_Day_qty), &consinfo_time_Day_qty)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 4) == 1)
	{
		value->DEF_IsoTime_time_Hour_qty = 1;
		if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->time_Hour_qty), &consinfo_time_Hour_qty)) < 0) return ret;
	}
	else
	{
		value->time_Hour_qty = 0;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 5) == 1)
	{
		value->DEF_IsoTime_time_Minute_qty = 1;
		if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->time_Minute_qty), &consinfo_time_Minute_qty)) < 0) return ret;
	}
	else
	{
		value->time_Minute_qty = 0;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 6) == 1)
	{
		value->DEF_IsoTime_time_Second_qty = 1;
		if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->time_Second_qty), &consinfo_time_Second_qty)) < 0) return ret;
	}
	else
	{
		value->time_Second_qty = 0;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 7) == 1)
	{
		value->DEF_IsoTime_time_SecondFractions = 1;
		if ((ret = ASN1_PER_Align_Dec_IsoTime_time_SecondFractions(workspace, value->time_SecondFractions)) < 0) return ret;
	}
	else
	{
		value->time_SecondFractions = 0;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 8) == 1)
	{
		value->DEF_IsoTime_time_Timezone = 1;
		if ((ret = ASN1_PER_Align_Dec_IsoTime_time_Timezone(workspace, value->time_Timezone)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_IsoTime(IsoTime *value);
extern int ASN1_PER_Align_Data_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
int ASN1_PER_Align_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_IsoTime(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_IsoTime(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Enc_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value);
extern int ASN1_PER_UNAlign_Data_Enc_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value);
int ASN1_PER_UNAlign_Data_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_time_Year_qty = { ASN1_CONST64(-32768), ASN1_CONST64(32767), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Month_qty = { ASN1_CONST64(1), ASN1_CONST64(12), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Day_qty = { ASN1_CONST64(1), ASN1_CONST64(31), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Hour_qty = { ASN1_CONST64(0), ASN1_CONST64(23), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Minute_qty = { ASN1_CONST64(0), ASN1_CONST64(59), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Second_qty = { ASN1_CONST64(0), ASN1_CONST64(60), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_SecondFractions = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Timezone = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_IsoTime_time_Year_qty == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_IsoTime_time_Month_qty == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_IsoTime_time_Day_qty == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_IsoTime_time_Hour_qty == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_IsoTime_time_Minute_qty == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_IsoTime_time_Second_qty == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_IsoTime_time_SecondFractions == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_IsoTime_time_Timezone == 1 ? 1 : 0) )) < 0) return ret;
	if (value->DEF_IsoTime_time_Year_qty == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->time_Year_qty), &consinfo_time_Year_qty)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_Month_qty == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->time_Month_qty), &consinfo_time_Month_qty)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_Day_qty == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->time_Day_qty), &consinfo_time_Day_qty)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_Hour_qty == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->time_Hour_qty), &consinfo_time_Hour_qty)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_Minute_qty == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->time_Minute_qty), &consinfo_time_Minute_qty)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_Second_qty == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->time_Second_qty), &consinfo_time_Second_qty)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_SecondFractions == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_IsoTime_time_SecondFractions(workspace, value->time_SecondFractions)) < 0) return ret;
	}
	if (value->DEF_IsoTime_time_Timezone == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_IsoTime_time_Timezone(workspace, value->time_Timezone)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_IsoTime(IsoTime *value);
extern int ASN1_PER_UNAlign_Data_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
int ASN1_PER_UNAlign_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_IsoTime(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_IsoTime(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Dec_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value);
extern int ASN1_PER_UNAlign_Data_Dec_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value);
int ASN1_PER_UNAlign_Data_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_time_Year_qty = { ASN1_CONST64(-32768), ASN1_CONST64(32767), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Month_qty = { ASN1_CONST64(1), ASN1_CONST64(12), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Day_qty = { ASN1_CONST64(1), ASN1_CONST64(31), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Hour_qty = { ASN1_CONST64(0), ASN1_CONST64(23), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Minute_qty = { ASN1_CONST64(0), ASN1_CONST64(59), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Second_qty = { ASN1_CONST64(0), ASN1_CONST64(60), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_SecondFractions = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_time_Timezone = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNUINT8 *_optvalue;
	if ((ret = ASN1_PER_Dec_Opt_Def_bit(workspace, 8, &_optvalue)) < 0) return ret;
	value->time_SecondFractions = (IsoTime_time_SecondFractions *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime_time_SecondFractions));
	memset(value->time_SecondFractions, 0, sizeof(IsoTime_time_SecondFractions));
	value->time_Timezone = (IsoTime_time_Timezone *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime_time_Timezone));
	memset(value->time_Timezone, 0, sizeof(IsoTime_time_Timezone));
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_IsoTime_time_Year_qty = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->time_Year_qty), &consinfo_time_Year_qty)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_IsoTime_time_Month_qty = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->time_Month_qty), &consinfo_time_Month_qty)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_IsoTime_time_Day_qty = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->time_Day_qty), &consinfo_time_Day_qty)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 4) == 1)
	{
		value->DEF_IsoTime_time_Hour_qty = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->time_Hour_qty), &consinfo_time_Hour_qty)) < 0) return ret;
	}
	else
	{
		value->time_Hour_qty = 0;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 5) == 1)
	{
		value->DEF_IsoTime_time_Minute_qty = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->time_Minute_qty), &consinfo_time_Minute_qty)) < 0) return ret;
	}
	else
	{
		value->time_Minute_qty = 0;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 6) == 1)
	{
		value->DEF_IsoTime_time_Second_qty = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->time_Second_qty), &consinfo_time_Second_qty)) < 0) return ret;
	}
	else
	{
		value->time_Second_qty = 0;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 7) == 1)
	{
		value->DEF_IsoTime_time_SecondFractions = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_IsoTime_time_SecondFractions(workspace, value->time_SecondFractions)) < 0) return ret;
	}
	else
	{
		value->time_SecondFractions = 0;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 8) == 1)
	{
		value->DEF_IsoTime_time_Timezone = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_IsoTime_time_Timezone(workspace, value->time_Timezone)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_IsoTime(IsoTime *value);
extern int ASN1_PER_UNAlign_Data_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
int ASN1_PER_UNAlign_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_IsoTime(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_IsoTime(value)) < 0) return ret;
	return ret;
}

/********************************************************
*HeaderOptions                                          *
********************************************************/
int ASN1_Print_HeaderOptions(HeaderOptions *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("HeaderOptions");
	if (value->DEF_HeaderOptions_datex_Origin_text == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_UTF8Str("datex_Origin_text", &(value->datex_Origin_text))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_HeaderOptions_datex_OriginAddress_location == 1)
	{ /*OPTIONAL start */
		// Type OCTET STRING
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_OCTETSTRING("datex_OriginAddress_location", &(value->datex_OriginAddress_location), tab_value + 1)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_HeaderOptions_datex_Sender_text == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_UTF8Str("datex_Sender_text", &(value->datex_Sender_text))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_HeaderOptions_datex_SenderAddress_location == 1)
	{ /*OPTIONAL start */
		// Type OCTET STRING
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_OCTETSTRING("datex_SenderAddress_location", &(value->datex_SenderAddress_location), tab_value + 1)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_HeaderOptions_datex_Destination_text == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_UTF8Str("datex_Destination_text", &(value->datex_Destination_text))) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_HeaderOptions_datex_DestinationAddress_location == 1)
	{ /*OPTIONAL start */
		// Type OCTET STRING
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_OCTETSTRING("datex_DestinationAddress_location", &(value->datex_DestinationAddress_location), tab_value + 1)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_HeaderOptions_datex_Cost == 1)
	{ /*OPTIONAL start */
		// Type Reference Cost
		if (Compare_Letter(tab_value, "datex-Cost")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("datex-Cost = ");
		}
		if ((ret = ASN1_Print_Cost((Cost *)value->datex_Cost, tab_value + 1)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_HeaderOptions_datex_DataPacket_time == 1)
	{ /*OPTIONAL start */
		// Type Reference IsoTime
		if (Compare_Letter(tab_value, "datex-DataPacket-time")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("datex-DataPacket-time = ");
		}
		if ((ret = ASN1_Print_IsoTime((IsoTime *)value->datex_DataPacket_time, tab_value + 1)) < 0) return ret;
	} /* OPTIONAL end */
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_HeaderOptions_datex_Origin_text(ASN1WorkSpace *workspace, HeaderOptions *value, ASNUINT8 *user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->DEF_HeaderOptions_datex_Origin_text = 1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->datex_Origin_text, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_HeaderOptions_datex_OriginAddress_location(ASN1WorkSpace *workspace, HeaderOptions *value, ASNUINT8 *user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->DEF_HeaderOptions_datex_OriginAddress_location = 1;
	if ((ret = ASN1_SET_OCTETSTRING(workspace, &value->datex_OriginAddress_location, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_HeaderOptions_datex_Sender_text(ASN1WorkSpace *workspace, HeaderOptions *value, ASNUINT8 *user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->DEF_HeaderOptions_datex_Sender_text = 1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->datex_Sender_text, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_HeaderOptions_datex_SenderAddress_location(ASN1WorkSpace *workspace, HeaderOptions *value, ASNUINT8 *user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->DEF_HeaderOptions_datex_SenderAddress_location = 1;
	if ((ret = ASN1_SET_OCTETSTRING(workspace, &value->datex_SenderAddress_location, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_HeaderOptions_datex_Destination_text(ASN1WorkSpace *workspace, HeaderOptions *value, ASNUINT8 *user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->DEF_HeaderOptions_datex_Destination_text = 1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->datex_Destination_text, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_HeaderOptions_datex_DestinationAddress_location(ASN1WorkSpace *workspace, HeaderOptions *value, ASNUINT8 *user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->DEF_HeaderOptions_datex_DestinationAddress_location = 1;
	if ((ret = ASN1_SET_OCTETSTRING(workspace, &value->datex_DestinationAddress_location, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_HeaderOptions_datex_Cost(ASN1WorkSpace *workspace, HeaderOptions *value, Cost *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->datex_Cost = (Cost *)mpool_malloc(workspace->Pmemory, sizeof(Cost));
	memset(value->datex_Cost, 0, sizeof(Cost));
	value->DEF_HeaderOptions_datex_Cost = 1;
	memmove(value->datex_Cost, user_value, sizeof(Cost));
	return ret;
}
int ASN1_SET_HeaderOptions_datex_DataPacket_time(ASN1WorkSpace *workspace, HeaderOptions *value, IsoTime *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->datex_DataPacket_time = (IsoTime *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime));
	memset(value->datex_DataPacket_time, 0, sizeof(IsoTime));
	value->DEF_HeaderOptions_datex_DataPacket_time = 1;
	memmove(value->datex_DataPacket_time, user_value, sizeof(IsoTime));
	return ret;
}
int ASN1_GET_HeaderOptions_datex_Origin_text(ASN1WorkSpace *workspace, HeaderOptions *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_HeaderOptions_datex_Origin_text == 1)
	{
		if ((ret = ASN1_GET_UTF8Str(workspace, &value->datex_Origin_text, user_value, user_value_length)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_HeaderOptions_datex_OriginAddress_location(ASN1WorkSpace *workspace, HeaderOptions *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_HeaderOptions_datex_OriginAddress_location == 1)
	{
		if ((ret = ASN1_GET_OCTETSTRING(workspace, &value->datex_OriginAddress_location, user_value, user_value_length)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_HeaderOptions_datex_Sender_text(ASN1WorkSpace *workspace, HeaderOptions *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_HeaderOptions_datex_Sender_text == 1)
	{
		if ((ret = ASN1_GET_UTF8Str(workspace, &value->datex_Sender_text, user_value, user_value_length)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_HeaderOptions_datex_SenderAddress_location(ASN1WorkSpace *workspace, HeaderOptions *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_HeaderOptions_datex_SenderAddress_location == 1)
	{
		if ((ret = ASN1_GET_OCTETSTRING(workspace, &value->datex_SenderAddress_location, user_value, user_value_length)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_HeaderOptions_datex_Destination_text(ASN1WorkSpace *workspace, HeaderOptions *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_HeaderOptions_datex_Destination_text == 1)
	{
		if ((ret = ASN1_GET_UTF8Str(workspace, &value->datex_Destination_text, user_value, user_value_length)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_HeaderOptions_datex_DestinationAddress_location(ASN1WorkSpace *workspace, HeaderOptions *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_HeaderOptions_datex_DestinationAddress_location == 1)
	{
		if ((ret = ASN1_GET_OCTETSTRING(workspace, &value->datex_DestinationAddress_location, user_value, user_value_length)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_HeaderOptions_datex_Cost(ASN1WorkSpace *workspace, HeaderOptions *value, Cost **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_HeaderOptions_datex_Cost == 1)
	{
		*user_value = value->datex_Cost;
	}
	else return -2;
	return ret;
}
int ASN1_GET_HeaderOptions_datex_DataPacket_time(ASN1WorkSpace *workspace, HeaderOptions *value, IsoTime **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_HeaderOptions_datex_DataPacket_time == 1)
	{
		*user_value = value->datex_DataPacket_time;
	}
	else return -2;
	return ret;
}
extern int ASN1_CHECK_Cost(Cost *value);
extern int ASN1_CHECK_IsoTime(IsoTime *value);
int ASN1_CHECK_HeaderOptions(HeaderOptions *value)
{
	int ret = 0;

	unsigned char checkinfo_datex_Origin_text[] = { 
		0x02,0x00,0x28,0x00
	};
	unsigned char checkinfo_datex_OriginAddress_location[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datex_Sender_text[] = { 
		0x02,0x00,0x28,0x00
	};
	unsigned char checkinfo_datex_SenderAddress_location[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datex_Destination_text[] = { 
		0x02,0x00,0x28,0x00
	};
	unsigned char checkinfo_datex_DestinationAddress_location[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datex_Cost[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datex_DataPacket_time[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if (value->DEF_HeaderOptions_datex_Origin_text == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_UTF8Str(&(value->datex_Origin_text), checkinfo_datex_Origin_text)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_HeaderOptions_datex_OriginAddress_location == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_OCTETSTRING(&(value->datex_OriginAddress_location), checkinfo_datex_OriginAddress_location)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_HeaderOptions_datex_Sender_text == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_UTF8Str(&(value->datex_Sender_text), checkinfo_datex_Sender_text)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_HeaderOptions_datex_SenderAddress_location == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_OCTETSTRING(&(value->datex_SenderAddress_location), checkinfo_datex_SenderAddress_location)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_HeaderOptions_datex_Destination_text == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_UTF8Str(&(value->datex_Destination_text), checkinfo_datex_Destination_text)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_HeaderOptions_datex_DestinationAddress_location == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_OCTETSTRING(&(value->datex_DestinationAddress_location), checkinfo_datex_DestinationAddress_location)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_HeaderOptions_datex_Cost == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_Cost(value->datex_Cost)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_HeaderOptions_datex_DataPacket_time == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_IsoTime(value->datex_DataPacket_time)) < 0) return ret;
	} /* OPTIONAL end */
	return ret;
}
extern int ASN1_BER_Data_Enc_Cost(ASN1WorkSpace *workspace, Cost *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if (value->DEF_HeaderOptions_datex_Origin_text == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->datex_Origin_text), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_HeaderOptions_datex_OriginAddress_location == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_OCTETSTRING(workspace, &(value->datex_OriginAddress_location), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_HeaderOptions_datex_Sender_text == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->datex_Sender_text), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_HeaderOptions_datex_SenderAddress_location == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_OCTETSTRING(workspace, &(value->datex_SenderAddress_location), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_HeaderOptions_datex_Destination_text == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->datex_Destination_text), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_HeaderOptions_datex_DestinationAddress_location == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_OCTETSTRING(workspace, &(value->datex_DestinationAddress_location), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_HeaderOptions_datex_Cost == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 6)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_Cost(workspace, value->datex_Cost, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	if (value->DEF_HeaderOptions_datex_DataPacket_time == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 7)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_IsoTime(workspace, value->datex_DataPacket_time, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_HeaderOptions(HeaderOptions *value);
extern int ASN1_BER_Data_Enc_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_HeaderOptions(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_HeaderOptions(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_Cost(ASN1WorkSpace *workspace, Cost *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	ASNUINT8 *_cpointer;
	value->datex_Cost = (Cost *)mpool_malloc(workspace->Pmemory, sizeof(Cost));
	memset(value->datex_Cost, 0, sizeof(Cost));
	value->datex_DataPacket_time = (IsoTime *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime));
	memset(value->datex_DataPacket_time, 0, sizeof(IsoTime));
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 0))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->datex_Origin_text, len, ASN1IMPL)) < 0) return ret;
		value->DEF_HeaderOptions_datex_Origin_text = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 1))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_OCTETSTRING(workspace, &value->datex_OriginAddress_location, len, ASN1IMPL)) < 0) return ret;
		value->DEF_HeaderOptions_datex_OriginAddress_location = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 2))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->datex_Sender_text, len, ASN1IMPL)) < 0) return ret;
		value->DEF_HeaderOptions_datex_Sender_text = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 3))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_OCTETSTRING(workspace, &value->datex_SenderAddress_location, len, ASN1IMPL)) < 0) return ret;
		value->DEF_HeaderOptions_datex_SenderAddress_location = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 4))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->datex_Destination_text, len, ASN1IMPL)) < 0) return ret;
		value->DEF_HeaderOptions_datex_Destination_text = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 5))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_OCTETSTRING(workspace, &value->datex_DestinationAddress_location, len, ASN1IMPL)) < 0) return ret;
		value->DEF_HeaderOptions_datex_DestinationAddress_location = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_CONS | 6))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 6)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_Cost(workspace, value->datex_Cost, len, ASN1IMPL)) < 0) return ret;
		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->DEF_HeaderOptions_datex_Cost = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_CONS | 7))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 7)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_IsoTime(workspace, value->datex_DataPacket_time, len, ASN1IMPL)) < 0) return ret;
		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->DEF_HeaderOptions_datex_DataPacket_time = 1;
	}
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_HeaderOptions(HeaderOptions *value);
extern int ASN1_BER_Data_Dec_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_HeaderOptions(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_HeaderOptions(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Enc_Cost(ASN1WorkSpace *workspace, Cost *value);
extern int ASN1_PER_Align_Data_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
int ASN1_PER_Align_Data_Enc_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datex_Origin_text = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_OriginAddress_location = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Sender_text = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_SenderAddress_location = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Destination_text = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_DestinationAddress_location = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Cost = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_DataPacket_time = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_HeaderOptions_datex_Origin_text == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_HeaderOptions_datex_OriginAddress_location == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_HeaderOptions_datex_Sender_text == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_HeaderOptions_datex_SenderAddress_location == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_HeaderOptions_datex_Destination_text == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_HeaderOptions_datex_DestinationAddress_location == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_HeaderOptions_datex_Cost == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_HeaderOptions_datex_DataPacket_time == 1 ? 1 : 0) )) < 0) return ret;
	if (value->DEF_HeaderOptions_datex_Origin_text == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_UTF8Str(workspace, &(value->datex_Origin_text), &consinfo_datex_Origin_text)) < 0) return ret;
	}
	if (value->DEF_HeaderOptions_datex_OriginAddress_location == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_OCTETSTRING(workspace, &(value->datex_OriginAddress_location), &consinfo_datex_OriginAddress_location)) < 0) return ret;
	}
	if (value->DEF_HeaderOptions_datex_Sender_text == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_UTF8Str(workspace, &(value->datex_Sender_text), &consinfo_datex_Sender_text)) < 0) return ret;
	}
	if (value->DEF_HeaderOptions_datex_SenderAddress_location == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_OCTETSTRING(workspace, &(value->datex_SenderAddress_location), &consinfo_datex_SenderAddress_location)) < 0) return ret;
	}
	if (value->DEF_HeaderOptions_datex_Destination_text == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_UTF8Str(workspace, &(value->datex_Destination_text), &consinfo_datex_Destination_text)) < 0) return ret;
	}
	if (value->DEF_HeaderOptions_datex_DestinationAddress_location == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_OCTETSTRING(workspace, &(value->datex_DestinationAddress_location), &consinfo_datex_DestinationAddress_location)) < 0) return ret;
	}
	if (value->DEF_HeaderOptions_datex_Cost == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_Cost(workspace, value->datex_Cost)) < 0) return ret;
	}
	if (value->DEF_HeaderOptions_datex_DataPacket_time == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_IsoTime(workspace, value->datex_DataPacket_time)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_HeaderOptions(HeaderOptions *value);
extern int ASN1_PER_Align_Data_Enc_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value);
int ASN1_PER_Align_Enc_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_HeaderOptions(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_HeaderOptions(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Dec_Cost(ASN1WorkSpace *workspace, Cost *value);
extern int ASN1_PER_Align_Data_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
int ASN1_PER_Align_Data_Dec_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datex_Origin_text = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_OriginAddress_location = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Sender_text = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_SenderAddress_location = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Destination_text = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_DestinationAddress_location = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Cost = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_DataPacket_time = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNUINT8 *_optvalue;
	if ((ret = ASN1_PER_Dec_Opt_Def_bit(workspace, 8, &_optvalue)) < 0) return ret;
	value->datex_Cost = (Cost *)mpool_malloc(workspace->Pmemory, sizeof(Cost));
	memset(value->datex_Cost, 0, sizeof(Cost));
	value->datex_DataPacket_time = (IsoTime *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime));
	memset(value->datex_DataPacket_time, 0, sizeof(IsoTime));
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_HeaderOptions_datex_Origin_text = 1;
		if ((ret = ASN1_PER_Align_Dec_UTF8Str(workspace, &(value->datex_Origin_text), &consinfo_datex_Origin_text)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_HeaderOptions_datex_OriginAddress_location = 1;
		if ((ret = ASN1_PER_Align_Dec_OCTETSTRING(workspace, &(value->datex_OriginAddress_location), &consinfo_datex_OriginAddress_location)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_HeaderOptions_datex_Sender_text = 1;
		if ((ret = ASN1_PER_Align_Dec_UTF8Str(workspace, &(value->datex_Sender_text), &consinfo_datex_Sender_text)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 4) == 1)
	{
		value->DEF_HeaderOptions_datex_SenderAddress_location = 1;
		if ((ret = ASN1_PER_Align_Dec_OCTETSTRING(workspace, &(value->datex_SenderAddress_location), &consinfo_datex_SenderAddress_location)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 5) == 1)
	{
		value->DEF_HeaderOptions_datex_Destination_text = 1;
		if ((ret = ASN1_PER_Align_Dec_UTF8Str(workspace, &(value->datex_Destination_text), &consinfo_datex_Destination_text)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 6) == 1)
	{
		value->DEF_HeaderOptions_datex_DestinationAddress_location = 1;
		if ((ret = ASN1_PER_Align_Dec_OCTETSTRING(workspace, &(value->datex_DestinationAddress_location), &consinfo_datex_DestinationAddress_location)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 7) == 1)
	{
		value->DEF_HeaderOptions_datex_Cost = 1;
		if ((ret = ASN1_PER_Align_Dec_Cost(workspace, value->datex_Cost)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 8) == 1)
	{
		value->DEF_HeaderOptions_datex_DataPacket_time = 1;
		if ((ret = ASN1_PER_Align_Dec_IsoTime(workspace, value->datex_DataPacket_time)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_HeaderOptions(HeaderOptions *value);
extern int ASN1_PER_Align_Data_Dec_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value);
int ASN1_PER_Align_Dec_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_HeaderOptions(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_HeaderOptions(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Enc_Cost(ASN1WorkSpace *workspace, Cost *value);
extern int ASN1_PER_UNAlign_Data_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
int ASN1_PER_UNAlign_Data_Enc_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datex_Origin_text = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_OriginAddress_location = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Sender_text = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_SenderAddress_location = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Destination_text = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_DestinationAddress_location = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Cost = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_DataPacket_time = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_HeaderOptions_datex_Origin_text == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_HeaderOptions_datex_OriginAddress_location == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_HeaderOptions_datex_Sender_text == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_HeaderOptions_datex_SenderAddress_location == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_HeaderOptions_datex_Destination_text == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_HeaderOptions_datex_DestinationAddress_location == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_HeaderOptions_datex_Cost == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_HeaderOptions_datex_DataPacket_time == 1 ? 1 : 0) )) < 0) return ret;
	if (value->DEF_HeaderOptions_datex_Origin_text == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_UTF8Str(workspace, &(value->datex_Origin_text), &consinfo_datex_Origin_text)) < 0) return ret;
	}
	if (value->DEF_HeaderOptions_datex_OriginAddress_location == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_OCTETSTRING(workspace, &(value->datex_OriginAddress_location), &consinfo_datex_OriginAddress_location)) < 0) return ret;
	}
	if (value->DEF_HeaderOptions_datex_Sender_text == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_UTF8Str(workspace, &(value->datex_Sender_text), &consinfo_datex_Sender_text)) < 0) return ret;
	}
	if (value->DEF_HeaderOptions_datex_SenderAddress_location == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_OCTETSTRING(workspace, &(value->datex_SenderAddress_location), &consinfo_datex_SenderAddress_location)) < 0) return ret;
	}
	if (value->DEF_HeaderOptions_datex_Destination_text == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_UTF8Str(workspace, &(value->datex_Destination_text), &consinfo_datex_Destination_text)) < 0) return ret;
	}
	if (value->DEF_HeaderOptions_datex_DestinationAddress_location == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_OCTETSTRING(workspace, &(value->datex_DestinationAddress_location), &consinfo_datex_DestinationAddress_location)) < 0) return ret;
	}
	if (value->DEF_HeaderOptions_datex_Cost == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_Cost(workspace, value->datex_Cost)) < 0) return ret;
	}
	if (value->DEF_HeaderOptions_datex_DataPacket_time == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_IsoTime(workspace, value->datex_DataPacket_time)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_HeaderOptions(HeaderOptions *value);
extern int ASN1_PER_UNAlign_Data_Enc_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value);
int ASN1_PER_UNAlign_Enc_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_HeaderOptions(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_HeaderOptions(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Dec_Cost(ASN1WorkSpace *workspace, Cost *value);
extern int ASN1_PER_UNAlign_Data_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
int ASN1_PER_UNAlign_Data_Dec_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datex_Origin_text = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_OriginAddress_location = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Sender_text = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_SenderAddress_location = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Destination_text = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_DestinationAddress_location = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Cost = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_DataPacket_time = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNUINT8 *_optvalue;
	if ((ret = ASN1_PER_Dec_Opt_Def_bit(workspace, 8, &_optvalue)) < 0) return ret;
	value->datex_Cost = (Cost *)mpool_malloc(workspace->Pmemory, sizeof(Cost));
	memset(value->datex_Cost, 0, sizeof(Cost));
	value->datex_DataPacket_time = (IsoTime *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime));
	memset(value->datex_DataPacket_time, 0, sizeof(IsoTime));
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_HeaderOptions_datex_Origin_text = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_UTF8Str(workspace, &(value->datex_Origin_text), &consinfo_datex_Origin_text)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_HeaderOptions_datex_OriginAddress_location = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_OCTETSTRING(workspace, &(value->datex_OriginAddress_location), &consinfo_datex_OriginAddress_location)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_HeaderOptions_datex_Sender_text = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_UTF8Str(workspace, &(value->datex_Sender_text), &consinfo_datex_Sender_text)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 4) == 1)
	{
		value->DEF_HeaderOptions_datex_SenderAddress_location = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_OCTETSTRING(workspace, &(value->datex_SenderAddress_location), &consinfo_datex_SenderAddress_location)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 5) == 1)
	{
		value->DEF_HeaderOptions_datex_Destination_text = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_UTF8Str(workspace, &(value->datex_Destination_text), &consinfo_datex_Destination_text)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 6) == 1)
	{
		value->DEF_HeaderOptions_datex_DestinationAddress_location = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_OCTETSTRING(workspace, &(value->datex_DestinationAddress_location), &consinfo_datex_DestinationAddress_location)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 7) == 1)
	{
		value->DEF_HeaderOptions_datex_Cost = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_Cost(workspace, value->datex_Cost)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 8) == 1)
	{
		value->DEF_HeaderOptions_datex_DataPacket_time = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_IsoTime(workspace, value->datex_DataPacket_time)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_HeaderOptions(HeaderOptions *value);
extern int ASN1_PER_UNAlign_Data_Dec_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value);
int ASN1_PER_UNAlign_Dec_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_HeaderOptions(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_HeaderOptions(value)) < 0) return ret;
	return ret;
}

/********************************************************
*Initiate                                               *
********************************************************/
int ASN1_Print_Initiate(Initiate *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("Initiate");
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("datex_Sender_txt", &(value->datex_Sender_txt))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("datex_Destination_txt", &(value->datex_Destination_txt))) < 0) return ret;
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_Initiate_datex_Sender_txt(ASN1WorkSpace *workspace, Initiate *value, ASNUINT8 *user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->datex_Sender_txt, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_Initiate_datex_Destination_txt(ASN1WorkSpace *workspace, Initiate *value, ASNUINT8 *user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->datex_Destination_txt, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_Initiate_datex_Sender_txt(ASN1WorkSpace *workspace, Initiate *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->datex_Sender_txt, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_Initiate_datex_Destination_txt(ASN1WorkSpace *workspace, Initiate *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->datex_Destination_txt, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_Initiate(Initiate *value)
{
	int ret = 0;

	unsigned char checkinfo_datex_Sender_txt[] = { 
		0x02,0x00,0x28,0x00
	};
	unsigned char checkinfo_datex_Destination_txt[] = { 
		0x02,0x00,0x28,0x00
	};

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_UTF8Str(&(value->datex_Sender_txt), checkinfo_datex_Sender_txt)) < 0) return ret;
	if ((ret = ASN1_CHECK_UTF8Str(&(value->datex_Destination_txt), checkinfo_datex_Destination_txt)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_Initiate(ASN1WorkSpace *workspace, Initiate *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->datex_Sender_txt), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->datex_Destination_txt), ASN1IMPL)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Initiate(Initiate *value);
extern int ASN1_BER_Data_Enc_Initiate(ASN1WorkSpace *workspace, Initiate *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_Initiate(ASN1WorkSpace *workspace, Initiate *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_Initiate(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Initiate(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_Initiate(ASN1WorkSpace *workspace, Initiate *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8 *_cpointer;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->datex_Sender_txt, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->datex_Destination_txt, len, ASN1IMPL)) < 0) return ret;
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_Initiate(Initiate *value);
extern int ASN1_BER_Data_Dec_Initiate(ASN1WorkSpace *workspace, Initiate *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_Initiate(ASN1WorkSpace *workspace, Initiate *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Initiate(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_Initiate(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_Initiate(ASN1WorkSpace *workspace, Initiate *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datex_Sender_txt = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Destination_txt = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };

	if ((ret = ASN1_PER_Align_Enc_UTF8Str(workspace, &(value->datex_Sender_txt), &consinfo_datex_Sender_txt)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_UTF8Str(workspace, &(value->datex_Destination_txt), &consinfo_datex_Destination_txt)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_Initiate(Initiate *value);
extern int ASN1_PER_Align_Data_Enc_Initiate(ASN1WorkSpace *workspace, Initiate *value);
int ASN1_PER_Align_Enc_Initiate(ASN1WorkSpace *workspace, Initiate *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Initiate(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_Initiate(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_Initiate(ASN1WorkSpace *workspace, Initiate *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datex_Sender_txt = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Destination_txt = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };

	if ((ret = ASN1_PER_Align_Dec_UTF8Str(workspace, &(value->datex_Sender_txt), &consinfo_datex_Sender_txt)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_UTF8Str(workspace, &(value->datex_Destination_txt), &consinfo_datex_Destination_txt)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_Initiate(Initiate *value);
extern int ASN1_PER_Align_Data_Dec_Initiate(ASN1WorkSpace *workspace, Initiate *value);
int ASN1_PER_Align_Dec_Initiate(ASN1WorkSpace *workspace, Initiate *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_Initiate(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Initiate(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_Initiate(ASN1WorkSpace *workspace, Initiate *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datex_Sender_txt = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Destination_txt = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };

	if ((ret = ASN1_PER_UNAlign_Enc_UTF8Str(workspace, &(value->datex_Sender_txt), &consinfo_datex_Sender_txt)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_UTF8Str(workspace, &(value->datex_Destination_txt), &consinfo_datex_Destination_txt)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_Initiate(Initiate *value);
extern int ASN1_PER_UNAlign_Data_Enc_Initiate(ASN1WorkSpace *workspace, Initiate *value);
int ASN1_PER_UNAlign_Enc_Initiate(ASN1WorkSpace *workspace, Initiate *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Initiate(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_Initiate(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_Initiate(ASN1WorkSpace *workspace, Initiate *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datex_Sender_txt = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Destination_txt = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };

	if ((ret = ASN1_PER_UNAlign_Dec_UTF8Str(workspace, &(value->datex_Sender_txt), &consinfo_datex_Sender_txt)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_UTF8Str(workspace, &(value->datex_Destination_txt), &consinfo_datex_Destination_txt)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_Initiate(Initiate *value);
extern int ASN1_PER_UNAlign_Data_Dec_Initiate(ASN1WorkSpace *workspace, Initiate *value);
int ASN1_PER_UNAlign_Dec_Initiate(ASN1WorkSpace *workspace, Initiate *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_Initiate(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Initiate(value)) < 0) return ret;
	return ret;
}

/********************************************************
*Login_datexLogin_EncodingRules_id                      *
********************************************************/
int ASN1_Print_Login_datexLogin_EncodingRules_id(Login_datexLogin_EncodingRules_id *value, int tab_value)
{
	int ret = 0;
	int count;
	ASN1ListNode *pnode;
	if (value == NULL) return -1;
	count = value->count;
	pnode = value->head->next;
	// SEQUENCE OF : default
	ASN1_Print_SEQ_OF(" ");
	while(count) {
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_OBJECTIDENTIFIER("OBJECTIDENTIFIER", pnode->data)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}

	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_CHECK_Login_datexLogin_EncodingRules_id(Login_datexLogin_EncodingRules_id *value)
{
	int ret = 0;

	unsigned char checkinfo_Login_datexLogin_EncodingRules_id[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_Login_datexLogin_EncodingRules_id_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		if ((ret = ASN1_CHECK_OBJECTIDENTIFIER(pnode->data, checkinfo_Login_datexLogin_EncodingRules_id_pdata)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_BER_Data_Enc_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value, ASN1TagType tagFlag)
{
	int ret = 0;
	ASN1ListNode *pnode;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	pnode = value->head->next;
	while (NULL != pnode)
	{
		if ((ret = ASN1_BER_Enc_OBJECTIDENTIFIER(workspace, pnode->data, ASN1EXPL)) < 0) return ret;
		pnode = pnode->next;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Login_datexLogin_EncodingRules_id(Login_datexLogin_EncodingRules_id *value);
extern int ASN1_BER_Data_Enc_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_Login_datexLogin_EncodingRules_id(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Login_datexLogin_EncodingRules_id(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	OBJECTIDENTIFIER *pdata;
	ASNUINT8 *p = workspace->buffer.current;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	if ((ret = ASN1_Creat_Init_List(workspace, value)) < 0) return ret;
	while (ASN1_BER_Dec_Isloop(workspace, p, length))
	{
		pdata = (OBJECTIDENTIFIER *)mpool_malloc(GetMemPool(workspace), sizeof(OBJECTIDENTIFIER));
		memset(pdata, 0, sizeof(OBJECTIDENTIFIER));
		if ((ret = ASN1_BER_Dec_OBJECTIDENTIFIER(workspace, pdata, len, ASN1EXPL)) < 0) return ret;
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
extern int ASN1_CHECK_Login_datexLogin_EncodingRules_id(Login_datexLogin_EncodingRules_id *value);
extern int ASN1_BER_Data_Dec_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Login_datexLogin_EncodingRules_id(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_Login_datexLogin_EncodingRules_id(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_Login_datexLogin_EncodingRules_id = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_Login_datexLogin_EncodingRules_id_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 all_length = value->count;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	ASN1ListNode *pnode = value->head->next;
	while(loop_set)
	{
		loop_set = ASN1_PER_Align_Enc_Set_Seq_Of_Length(workspace, &all_length, &process_length, &consinfo_Login_datexLogin_EncodingRules_id);
		for(i = 0; i < process_length; i++)
		{
			if ((ret = ASN1_PER_Align_Enc_OBJECTIDENTIFIER(workspace, pnode->data, &consinfo_Login_datexLogin_EncodingRules_id_pdata)) < 0) return ret;
			pnode = pnode->next;
		}
	}
	if (value->count != 0 && value->count % 16384 == 0)
	{
		if ((ret = ASN1_PER_Align_WirteBuffer(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Login_datexLogin_EncodingRules_id(Login_datexLogin_EncodingRules_id *value);
extern int ASN1_PER_Align_Data_Enc_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value);
int ASN1_PER_Align_Enc_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Login_datexLogin_EncodingRules_id(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_Login_datexLogin_EncodingRules_id(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_Login_datexLogin_EncodingRules_id = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_Login_datexLogin_EncodingRules_id_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	OBJECTIDENTIFIER *pdata;
	if ((ret = ASN1_Creat_Init_List(workspace, value)) < 0) return ret;
	while(loop_set)
	{
		loop_set = ASN1_PER_Align_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_Login_datexLogin_EncodingRules_id);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (OBJECTIDENTIFIER *)mpool_calloc(GetMemPool(workspace), sizeof(OBJECTIDENTIFIER), 1)) == NULL) return -1;
			if ((ret = ASN1_PER_Align_Dec_OBJECTIDENTIFIER(workspace, pdata, &consinfo_Login_datexLogin_EncodingRules_id_pdata)) < 0) return ret;
			if ((ret = ASN1_Insert_Node(workspace, value, (void *)pdata)) < 0) return ret;
		}
	}

	return ret;
}
extern int ASN1_CHECK_Login_datexLogin_EncodingRules_id(Login_datexLogin_EncodingRules_id *value);
extern int ASN1_PER_Align_Data_Dec_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value);
int ASN1_PER_Align_Dec_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_Login_datexLogin_EncodingRules_id(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Login_datexLogin_EncodingRules_id(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_Login_datexLogin_EncodingRules_id = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_Login_datexLogin_EncodingRules_id_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 all_length = value->count;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	ASN1ListNode *pnode = value->head->next;
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Enc_Set_Seq_Of_Length(workspace, &all_length, &process_length, &consinfo_Login_datexLogin_EncodingRules_id);
		for(i = 0; i < process_length; i++)
		{
			if ((ret = ASN1_PER_UNAlign_Enc_OBJECTIDENTIFIER(workspace, pnode->data, &consinfo_Login_datexLogin_EncodingRules_id_pdata)) < 0) return ret;
			pnode = pnode->next;
		}
	}
	if (value->count != 0 && value->count % 16384 == 0)
	{
		if ((ret = ASN1_PER_UNAlign_WirteBuffer(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Login_datexLogin_EncodingRules_id(Login_datexLogin_EncodingRules_id *value);
extern int ASN1_PER_UNAlign_Data_Enc_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value);
int ASN1_PER_UNAlign_Enc_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Login_datexLogin_EncodingRules_id(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_Login_datexLogin_EncodingRules_id(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_Login_datexLogin_EncodingRules_id = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_Login_datexLogin_EncodingRules_id_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	OBJECTIDENTIFIER *pdata;
	if ((ret = ASN1_Creat_Init_List(workspace, value)) < 0) return ret;
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_Login_datexLogin_EncodingRules_id);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (OBJECTIDENTIFIER *)mpool_calloc(GetMemPool(workspace), sizeof(OBJECTIDENTIFIER), 1)) == NULL) return -1;
			if ((ret = ASN1_PER_UNAlign_Dec_OBJECTIDENTIFIER(workspace, pdata, &consinfo_Login_datexLogin_EncodingRules_id_pdata)) < 0) return ret;
			if ((ret = ASN1_Insert_Node(workspace, value, (void *)pdata)) < 0) return ret;
		}
	}

	return ret;
}
extern int ASN1_CHECK_Login_datexLogin_EncodingRules_id(Login_datexLogin_EncodingRules_id *value);
extern int ASN1_PER_UNAlign_Data_Dec_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value);
int ASN1_PER_UNAlign_Dec_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_Login_datexLogin_EncodingRules_id(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Login_datexLogin_EncodingRules_id(value)) < 0) return ret;
	return ret;
}

/********************************************************
*Login_datexLogin-Initiator-cd                          *
********************************************************/
int ASN1_Print_Login_datexLogin_Initiator_cd(Login_datexLogin_Initiator_cd *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch(*value)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("Login_datexLogin-Initiator-cd", "serverInitiated", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("Login_datexLogin-Initiator-cd", "clientInitiated", 1)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	return ret;
}
int ASN1_CHECK_Login_datexLogin_Initiator_cd(Login_datexLogin_Initiator_cd *value)
{
	unsigned char checkinfo_Login_datexLogin_Initiator_cd[] = {0x02,0x00,0x01,0x00 };
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32 *)value, checkinfo_Login_datexLogin_Initiator_cd)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_Login_datexLogin_Initiator_cd(ASN1WorkSpace *workspace, Login_datexLogin_Initiator_cd *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_Login_datexLogin_Initiator_cd(ASN1WorkSpace *workspace, Login_datexLogin_Initiator_cd *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_Login_datexLogin_Initiator_cd(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Login_datexLogin_Initiator_cd(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_Login_datexLogin_Initiator_cd(ASN1WorkSpace *workspace, Login_datexLogin_Initiator_cd *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_Login_datexLogin_Initiator_cd(ASN1WorkSpace *workspace, Login_datexLogin_Initiator_cd *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Login_datexLogin_Initiator_cd(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_Login_datexLogin_Initiator_cd(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_Login_datexLogin_Initiator_cd(ASN1WorkSpace *workspace, Login_datexLogin_Initiator_cd *value)
{
	struct Asn1ConsInfo consinfo_Login_datexLogin_Initiator_cd = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_Login_datexLogin_Initiator_cd;
	switch(*value)
	{
	case Login_datexLogin_Initiator_cd_serverInitiated: ui_Login_datexLogin_Initiator_cd = 0; consinfo_Login_datexLogin_Initiator_cd.enumextbit = 0; break;
	case Login_datexLogin_Initiator_cd_clientInitiated: ui_Login_datexLogin_Initiator_cd = 1; consinfo_Login_datexLogin_Initiator_cd.enumextbit = 0; break;
	default: ui_Login_datexLogin_Initiator_cd = *value; consinfo_Login_datexLogin_Initiator_cd.enumextbit = 1; break;
	}
	if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_Login_datexLogin_Initiator_cd, &consinfo_Login_datexLogin_Initiator_cd)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Enc_Login_datexLogin_Initiator_cd(ASN1WorkSpace *workspace, Login_datexLogin_Initiator_cd *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Login_datexLogin_Initiator_cd(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_Login_datexLogin_Initiator_cd(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_Login_datexLogin_Initiator_cd(ASN1WorkSpace *workspace, Login_datexLogin_Initiator_cd *value)
{
	struct Asn1ConsInfo consinfo_Login_datexLogin_Initiator_cd = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_Login_datexLogin_Initiator_cd;
	if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_Login_datexLogin_Initiator_cd, &consinfo_Login_datexLogin_Initiator_cd)) < 0) return ret;
	if (consinfo_Login_datexLogin_Initiator_cd.enumextbit == 0)
	{
		switch(ui_Login_datexLogin_Initiator_cd)
		{
		case 0: *value = Login_datexLogin_Initiator_cd_serverInitiated; break;
		case 1: *value = Login_datexLogin_Initiator_cd_clientInitiated; break;
		default: break;
		}
	}
	else
	{
		switch(ui_Login_datexLogin_Initiator_cd)
		{
		default: *value = ui_Login_datexLogin_Initiator_cd; break;
		}
	}
	return ret;
}
int ASN1_PER_Align_Dec_Login_datexLogin_Initiator_cd(ASN1WorkSpace *workspace, Login_datexLogin_Initiator_cd *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_Login_datexLogin_Initiator_cd(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Login_datexLogin_Initiator_cd(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_Login_datexLogin_Initiator_cd(ASN1WorkSpace *workspace, Login_datexLogin_Initiator_cd *value)
{
	struct Asn1ConsInfo consinfo_Login_datexLogin_Initiator_cd = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_Login_datexLogin_Initiator_cd;
	switch(*value)
	{
	case Login_datexLogin_Initiator_cd_serverInitiated: ui_Login_datexLogin_Initiator_cd = 0; consinfo_Login_datexLogin_Initiator_cd.enumextbit = 0; break;
	case Login_datexLogin_Initiator_cd_clientInitiated: ui_Login_datexLogin_Initiator_cd = 1; consinfo_Login_datexLogin_Initiator_cd.enumextbit = 0; break;
	default: ui_Login_datexLogin_Initiator_cd = *value; consinfo_Login_datexLogin_Initiator_cd.enumextbit = 1; break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_Login_datexLogin_Initiator_cd, &consinfo_Login_datexLogin_Initiator_cd)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Enc_Login_datexLogin_Initiator_cd(ASN1WorkSpace *workspace, Login_datexLogin_Initiator_cd *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Login_datexLogin_Initiator_cd(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_Login_datexLogin_Initiator_cd(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_Login_datexLogin_Initiator_cd(ASN1WorkSpace *workspace, Login_datexLogin_Initiator_cd *value)
{
	struct Asn1ConsInfo consinfo_Login_datexLogin_Initiator_cd = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_Login_datexLogin_Initiator_cd;
	if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_Login_datexLogin_Initiator_cd, &consinfo_Login_datexLogin_Initiator_cd)) < 0) return ret;
	if (consinfo_Login_datexLogin_Initiator_cd.enumextbit == 0)
	{
		switch(ui_Login_datexLogin_Initiator_cd)
		{
		case 0: *value = Login_datexLogin_Initiator_cd_serverInitiated; break;
		case 1: *value = Login_datexLogin_Initiator_cd_clientInitiated; break;
		default: break;
		}
	}
	else
	{
		switch(ui_Login_datexLogin_Initiator_cd)
		{
		default: *value = ui_Login_datexLogin_Initiator_cd; break;
		}
	}
	return ret;
}
int ASN1_PER_UNAlign_Dec_Login_datexLogin_Initiator_cd(ASN1WorkSpace *workspace, Login_datexLogin_Initiator_cd *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_Login_datexLogin_Initiator_cd(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Login_datexLogin_Initiator_cd(value)) < 0) return ret;
	return ret;
}

/********************************************************
*Login                                                  *
********************************************************/
int ASN1_Print_Login(Login *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("Login");
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("datex_Sender_txt", &(value->datex_Sender_txt))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("datex_Destination_txt", &(value->datex_Destination_txt))) < 0) return ret;
	// Type OCTET STRING
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_OCTETSTRING("datexLogin_UserName_txt", &(value->datexLogin_UserName_txt), tab_value + 1)) < 0) return ret;
	// Type OCTET STRING
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_OCTETSTRING("datexLogin_Password_txt", &(value->datexLogin_Password_txt), tab_value + 1)) < 0) return ret;
	// Type Reference Login_datexLogin_EncodingRules_id
	if (Compare_Letter(tab_value, "datexLogin-EncodingRules-id")) {
		ASN_Print_TAB(tab_value + 1);
		asn_printf("datexLogin-EncodingRules-id = ");
	}
	if ((ret = ASN1_Print_Login_datexLogin_EncodingRules_id((Login_datexLogin_EncodingRules_id *)&(value->datexLogin_EncodingRules_id), tab_value + 1)) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("datexLogin_HeartbeatDurationMax_qty", &(value->datexLogin_HeartbeatDurationMax_qty))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("datexLogin_ResponseTimeOut_qty", &(value->datexLogin_ResponseTimeOut_qty))) < 0) return ret;
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch(value->datexLogin_Initiator_cd)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("Login_datexLogin-Initiator-cd", "serverInitiated", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("Login_datexLogin-Initiator-cd", "clientInitiated", 1)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("datexLogin_DatagramSize_qty", &(value->datexLogin_DatagramSize_qty))) < 0) return ret;
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_Login_datex_Sender_txt(ASN1WorkSpace *workspace, Login *value, ASNUINT8 *user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->datex_Sender_txt, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_Login_datex_Destination_txt(ASN1WorkSpace *workspace, Login *value, ASNUINT8 *user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->datex_Destination_txt, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_Login_datexLogin_UserName_txt(ASN1WorkSpace *workspace, Login *value, ASNUINT8 *user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_OCTETSTRING(workspace, &value->datexLogin_UserName_txt, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_Login_datexLogin_Password_txt(ASN1WorkSpace *workspace, Login *value, ASNUINT8 *user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_OCTETSTRING(workspace, &value->datexLogin_Password_txt, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login *value, Login_datexLogin_EncodingRules_id *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	memmove(&value->datexLogin_EncodingRules_id, user_value, sizeof(Login_datexLogin_EncodingRules_id));
	return ret;
}
int ASN1_SET_Login_datexLogin_HeartbeatDurationMax_qty(ASN1WorkSpace *workspace, Login *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->datexLogin_HeartbeatDurationMax_qty, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_Login_datexLogin_ResponseTimeOut_qty(ASN1WorkSpace *workspace, Login *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->datexLogin_ResponseTimeOut_qty, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_Login_datexLogin_Initiator_cd(ASN1WorkSpace *workspace, Login *value, ENUMERATED user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_ENUMERATED(workspace, (ASNINT32*)&value->datexLogin_Initiator_cd, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_Login_datexLogin_DatagramSize_qty(ASN1WorkSpace *workspace, Login *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->datexLogin_DatagramSize_qty, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_Login_datex_Sender_txt(ASN1WorkSpace *workspace, Login *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->datex_Sender_txt, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_Login_datex_Destination_txt(ASN1WorkSpace *workspace, Login *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->datex_Destination_txt, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_Login_datexLogin_UserName_txt(ASN1WorkSpace *workspace, Login *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_OCTETSTRING(workspace, &value->datexLogin_UserName_txt, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_Login_datexLogin_Password_txt(ASN1WorkSpace *workspace, Login *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_OCTETSTRING(workspace, &value->datexLogin_Password_txt, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login *value, Login_datexLogin_EncodingRules_id **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = &value->datexLogin_EncodingRules_id;
	return ret;
}
int ASN1_GET_Login_datexLogin_HeartbeatDurationMax_qty(ASN1WorkSpace *workspace, Login *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->datexLogin_HeartbeatDurationMax_qty, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_Login_datexLogin_ResponseTimeOut_qty(ASN1WorkSpace *workspace, Login *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->datexLogin_ResponseTimeOut_qty, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_Login_datexLogin_Initiator_cd(ASN1WorkSpace *workspace, Login *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->datexLogin_Initiator_cd, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_Login_datexLogin_DatagramSize_qty(ASN1WorkSpace *workspace, Login *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->datexLogin_DatagramSize_qty, user_value)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_Login_datexLogin_EncodingRules_id(Login_datexLogin_EncodingRules_id *value);
int ASN1_CHECK_Login(Login *value)
{
	int ret = 0;

	unsigned char checkinfo_datex_Sender_txt[] = { 
		0x02,0x00,0x28,0x00
	};
	unsigned char checkinfo_datex_Destination_txt[] = { 
		0x02,0x00,0x28,0x00
	};
	unsigned char checkinfo_datexLogin_UserName_txt[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datexLogin_Password_txt[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datexLogin_EncodingRules_id[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datexLogin_HeartbeatDurationMax_qty[] = { 
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_datexLogin_ResponseTimeOut_qty[] = { 
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_datexLogin_Initiator_cd[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datexLogin_DatagramSize_qty[] = { 
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_UTF8Str(&(value->datex_Sender_txt), checkinfo_datex_Sender_txt)) < 0) return ret;
	if ((ret = ASN1_CHECK_UTF8Str(&(value->datex_Destination_txt), checkinfo_datex_Destination_txt)) < 0) return ret;
	if ((ret = ASN1_CHECK_OCTETSTRING(&(value->datexLogin_UserName_txt), checkinfo_datexLogin_UserName_txt)) < 0) return ret;
	if ((ret = ASN1_CHECK_OCTETSTRING(&(value->datexLogin_Password_txt), checkinfo_datexLogin_Password_txt)) < 0) return ret;
	if ((ret = ASN1_CHECK_Login_datexLogin_EncodingRules_id(&(value->datexLogin_EncodingRules_id))) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->datexLogin_HeartbeatDurationMax_qty), checkinfo_datexLogin_HeartbeatDurationMax_qty)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->datexLogin_ResponseTimeOut_qty), checkinfo_datexLogin_ResponseTimeOut_qty)) < 0) return ret;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->datexLogin_Initiator_cd), checkinfo_datexLogin_Initiator_cd)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->datexLogin_DatagramSize_qty), checkinfo_datexLogin_DatagramSize_qty)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Enc_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_Login_datexLogin_Initiator_cd(ASN1WorkSpace *workspace, Login_datexLogin_Initiator_cd *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_Login(ASN1WorkSpace *workspace, Login *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->datex_Sender_txt), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->datex_Destination_txt), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_OCTETSTRING(workspace, &(value->datexLogin_UserName_txt), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_OCTETSTRING(workspace, &(value->datexLogin_Password_txt), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 4)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Login_datexLogin_EncodingRules_id(workspace, &(value->datexLogin_EncodingRules_id), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->datexLogin_HeartbeatDurationMax_qty), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 6)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->datexLogin_ResponseTimeOut_qty), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 7)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Login_datexLogin_Initiator_cd(workspace, &(value->datexLogin_Initiator_cd), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 8)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->datexLogin_DatagramSize_qty), ASN1IMPL)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Login(Login *value);
extern int ASN1_BER_Data_Enc_Login(ASN1WorkSpace *workspace, Login *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_Login(ASN1WorkSpace *workspace, Login *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_Login(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Login(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_Login_datexLogin_Initiator_cd(ASN1WorkSpace *workspace, Login_datexLogin_Initiator_cd *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_Login(ASN1WorkSpace *workspace, Login *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8 *_cpointer;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->datex_Sender_txt, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->datex_Destination_txt, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_OCTETSTRING(workspace, &value->datexLogin_UserName_txt, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_OCTETSTRING(workspace, &value->datexLogin_Password_txt, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 4)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Login_datexLogin_EncodingRules_id(workspace, &value->datexLogin_EncodingRules_id, len, ASN1IMPL)) < 0) return ret;
	if (IfFixedLength(len) == -1)
	{
		if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
	}
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->datexLogin_HeartbeatDurationMax_qty, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 6)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->datexLogin_ResponseTimeOut_qty, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 7)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Login_datexLogin_Initiator_cd(workspace, &value->datexLogin_Initiator_cd, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 8)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->datexLogin_DatagramSize_qty, len, ASN1IMPL)) < 0) return ret;
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_Login(Login *value);
extern int ASN1_BER_Data_Dec_Login(ASN1WorkSpace *workspace, Login *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_Login(ASN1WorkSpace *workspace, Login *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Login(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_Login(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Enc_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value);
int ASN1_PER_Align_Data_Enc_Login(ASN1WorkSpace *workspace, Login *value)
{
	int ret = 0;
	ASNINT32 ui_datexLogin_Initiator_cd;
	struct Asn1ConsInfo consinfo_datex_Sender_txt = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Destination_txt = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_UserName_txt = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_Password_txt = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_EncodingRules_id = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_HeartbeatDurationMax_qty = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_ResponseTimeOut_qty = { ASN1_CONST64(0), ASN1_CONST64(255), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_Initiator_cd = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_DatagramSize_qty = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };

	if ((ret = ASN1_PER_Align_Enc_UTF8Str(workspace, &(value->datex_Sender_txt), &consinfo_datex_Sender_txt)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_UTF8Str(workspace, &(value->datex_Destination_txt), &consinfo_datex_Destination_txt)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_OCTETSTRING(workspace, &(value->datexLogin_UserName_txt), &consinfo_datexLogin_UserName_txt)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_OCTETSTRING(workspace, &(value->datexLogin_Password_txt), &consinfo_datexLogin_Password_txt)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_Login_datexLogin_EncodingRules_id(workspace, &(value->datexLogin_EncodingRules_id))) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->datexLogin_HeartbeatDurationMax_qty), &consinfo_datexLogin_HeartbeatDurationMax_qty)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->datexLogin_ResponseTimeOut_qty), &consinfo_datexLogin_ResponseTimeOut_qty)) < 0) return ret;
	switch(value->datexLogin_Initiator_cd)
	{
	case Login_datexLogin_Initiator_cd_serverInitiated: ui_datexLogin_Initiator_cd = 0; consinfo_datexLogin_Initiator_cd.enumextbit = 0; break;
	case Login_datexLogin_Initiator_cd_clientInitiated: ui_datexLogin_Initiator_cd = 1; consinfo_datexLogin_Initiator_cd.enumextbit = 0; break;
	default: ui_datexLogin_Initiator_cd = value->datexLogin_Initiator_cd; consinfo_datexLogin_Initiator_cd.enumextbit = 1;break;
	}
	if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_datexLogin_Initiator_cd, &consinfo_datexLogin_Initiator_cd)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->datexLogin_DatagramSize_qty), &consinfo_datexLogin_DatagramSize_qty)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_Login(Login *value);
extern int ASN1_PER_Align_Data_Enc_Login(ASN1WorkSpace *workspace, Login *value);
int ASN1_PER_Align_Enc_Login(ASN1WorkSpace *workspace, Login *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Login(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_Login(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Dec_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value);
int ASN1_PER_Align_Data_Dec_Login(ASN1WorkSpace *workspace, Login *value)
{
	int ret = 0;
	ASNINT32 ui_datexLogin_Initiator_cd;
	struct Asn1ConsInfo consinfo_datex_Sender_txt = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Destination_txt = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_UserName_txt = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_Password_txt = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_EncodingRules_id = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_HeartbeatDurationMax_qty = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_ResponseTimeOut_qty = { ASN1_CONST64(0), ASN1_CONST64(255), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_Initiator_cd = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_DatagramSize_qty = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };

	if ((ret = ASN1_PER_Align_Dec_UTF8Str(workspace, &(value->datex_Sender_txt), &consinfo_datex_Sender_txt)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_UTF8Str(workspace, &(value->datex_Destination_txt), &consinfo_datex_Destination_txt)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_OCTETSTRING(workspace, &(value->datexLogin_UserName_txt), &consinfo_datexLogin_UserName_txt)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_OCTETSTRING(workspace, &(value->datexLogin_Password_txt), &consinfo_datexLogin_Password_txt)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_Login_datexLogin_EncodingRules_id(workspace, &(value->datexLogin_EncodingRules_id))) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->datexLogin_HeartbeatDurationMax_qty), &consinfo_datexLogin_HeartbeatDurationMax_qty)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->datexLogin_ResponseTimeOut_qty), &consinfo_datexLogin_ResponseTimeOut_qty)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_datexLogin_Initiator_cd, &consinfo_datexLogin_Initiator_cd)) < 0) return ret;
	if (consinfo_datexLogin_Initiator_cd.enumextbit == 0)
	{
		switch(ui_datexLogin_Initiator_cd)
		{
		case 0: value->datexLogin_Initiator_cd = Login_datexLogin_Initiator_cd_serverInitiated; break;
		case 1: value->datexLogin_Initiator_cd = Login_datexLogin_Initiator_cd_clientInitiated; break;
		default: break;
		}
	}
	else
	{
		switch(ui_datexLogin_Initiator_cd)
		{
		default: value->datexLogin_Initiator_cd = ui_datexLogin_Initiator_cd; break;
		}
	}
	if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->datexLogin_DatagramSize_qty), &consinfo_datexLogin_DatagramSize_qty)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_Login(Login *value);
extern int ASN1_PER_Align_Data_Dec_Login(ASN1WorkSpace *workspace, Login *value);
int ASN1_PER_Align_Dec_Login(ASN1WorkSpace *workspace, Login *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_Login(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Login(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Enc_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value);
int ASN1_PER_UNAlign_Data_Enc_Login(ASN1WorkSpace *workspace, Login *value)
{
	int ret = 0;
	ASNINT32 ui_datexLogin_Initiator_cd;
	struct Asn1ConsInfo consinfo_datex_Sender_txt = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Destination_txt = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_UserName_txt = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_Password_txt = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_EncodingRules_id = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_HeartbeatDurationMax_qty = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_ResponseTimeOut_qty = { ASN1_CONST64(0), ASN1_CONST64(255), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_Initiator_cd = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_DatagramSize_qty = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };

	if ((ret = ASN1_PER_UNAlign_Enc_UTF8Str(workspace, &(value->datex_Sender_txt), &consinfo_datex_Sender_txt)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_UTF8Str(workspace, &(value->datex_Destination_txt), &consinfo_datex_Destination_txt)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_OCTETSTRING(workspace, &(value->datexLogin_UserName_txt), &consinfo_datexLogin_UserName_txt)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_OCTETSTRING(workspace, &(value->datexLogin_Password_txt), &consinfo_datexLogin_Password_txt)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_Login_datexLogin_EncodingRules_id(workspace, &(value->datexLogin_EncodingRules_id))) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->datexLogin_HeartbeatDurationMax_qty), &consinfo_datexLogin_HeartbeatDurationMax_qty)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->datexLogin_ResponseTimeOut_qty), &consinfo_datexLogin_ResponseTimeOut_qty)) < 0) return ret;
	switch(value->datexLogin_Initiator_cd)
	{
	case Login_datexLogin_Initiator_cd_serverInitiated: ui_datexLogin_Initiator_cd = 0; consinfo_datexLogin_Initiator_cd.enumextbit = 0; break;
	case Login_datexLogin_Initiator_cd_clientInitiated: ui_datexLogin_Initiator_cd = 1; consinfo_datexLogin_Initiator_cd.enumextbit = 0; break;
	default: ui_datexLogin_Initiator_cd = value->datexLogin_Initiator_cd; consinfo_datexLogin_Initiator_cd.enumextbit = 1;break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_datexLogin_Initiator_cd, &consinfo_datexLogin_Initiator_cd)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->datexLogin_DatagramSize_qty), &consinfo_datexLogin_DatagramSize_qty)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_Login(Login *value);
extern int ASN1_PER_UNAlign_Data_Enc_Login(ASN1WorkSpace *workspace, Login *value);
int ASN1_PER_UNAlign_Enc_Login(ASN1WorkSpace *workspace, Login *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Login(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_Login(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Dec_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value);
int ASN1_PER_UNAlign_Data_Dec_Login(ASN1WorkSpace *workspace, Login *value)
{
	int ret = 0;
	ASNINT32 ui_datexLogin_Initiator_cd;
	struct Asn1ConsInfo consinfo_datex_Sender_txt = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_Destination_txt = { ASN1_CONST64(0), ASN1_CONST64(40), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_UserName_txt = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_Password_txt = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_EncodingRules_id = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_HeartbeatDurationMax_qty = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_ResponseTimeOut_qty = { ASN1_CONST64(0), ASN1_CONST64(255), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_Initiator_cd = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexLogin_DatagramSize_qty = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };

	if ((ret = ASN1_PER_UNAlign_Dec_UTF8Str(workspace, &(value->datex_Sender_txt), &consinfo_datex_Sender_txt)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_UTF8Str(workspace, &(value->datex_Destination_txt), &consinfo_datex_Destination_txt)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_OCTETSTRING(workspace, &(value->datexLogin_UserName_txt), &consinfo_datexLogin_UserName_txt)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_OCTETSTRING(workspace, &(value->datexLogin_Password_txt), &consinfo_datexLogin_Password_txt)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_Login_datexLogin_EncodingRules_id(workspace, &(value->datexLogin_EncodingRules_id))) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->datexLogin_HeartbeatDurationMax_qty), &consinfo_datexLogin_HeartbeatDurationMax_qty)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->datexLogin_ResponseTimeOut_qty), &consinfo_datexLogin_ResponseTimeOut_qty)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_datexLogin_Initiator_cd, &consinfo_datexLogin_Initiator_cd)) < 0) return ret;
	if (consinfo_datexLogin_Initiator_cd.enumextbit == 0)
	{
		switch(ui_datexLogin_Initiator_cd)
		{
		case 0: value->datexLogin_Initiator_cd = Login_datexLogin_Initiator_cd_serverInitiated; break;
		case 1: value->datexLogin_Initiator_cd = Login_datexLogin_Initiator_cd_clientInitiated; break;
		default: break;
		}
	}
	else
	{
		switch(ui_datexLogin_Initiator_cd)
		{
		default: value->datexLogin_Initiator_cd = ui_datexLogin_Initiator_cd; break;
		}
	}
	if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->datexLogin_DatagramSize_qty), &consinfo_datexLogin_DatagramSize_qty)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_Login(Login *value);
extern int ASN1_PER_UNAlign_Data_Dec_Login(ASN1WorkSpace *workspace, Login *value);
int ASN1_PER_UNAlign_Dec_Login(ASN1WorkSpace *workspace, Login *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_Login(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Login(value)) < 0) return ret;
	return ret;
}

/********************************************************
*FrED                                                   *
********************************************************/
int ASN1_Print_FrED(FrED *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// Type Default
	if ((ret = ASN1_Print_INTEGER("FrED", value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_FrED(FrED *value)
{
	unsigned char checkinfo_FrED[] = { 
		0x02,0x00,0x85,0x00,0xFF,0xFF,0xFF,0xFF,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(value, checkinfo_FrED)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_FrED(ASN1WorkSpace *workspace, FrED *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_FrED(ASN1WorkSpace *workspace, FrED *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_FrED(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_FrED(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_FrED(ASN1WorkSpace *workspace, FrED *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_FrED(ASN1WorkSpace *workspace, FrED *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_FrED(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_FrED(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_FrED(ASN1WorkSpace *workspace, FrED *value)
{
	struct Asn1ConsInfo consinfo_FrED = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	int ret = 0;
	if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, value, &consinfo_FrED)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Enc_FrED(ASN1WorkSpace *workspace, FrED *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_FrED(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_FrED(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_FrED(ASN1WorkSpace *workspace, FrED *value)
{
	struct Asn1ConsInfo consinfo_FrED = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	int ret = 0;
	if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, value, &consinfo_FrED)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Dec_FrED(ASN1WorkSpace *workspace, FrED *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_FrED(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_FrED(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_FrED(ASN1WorkSpace *workspace, FrED *value)
{
	struct Asn1ConsInfo consinfo_FrED = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, value, &consinfo_FrED)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Enc_FrED(ASN1WorkSpace *workspace, FrED *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_FrED(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_FrED(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_FrED(ASN1WorkSpace *workspace, FrED *value)
{
	struct Asn1ConsInfo consinfo_FrED = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, value, &consinfo_FrED)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Dec_FrED(ASN1WorkSpace *workspace, FrED *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_FrED(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_FrED(value)) < 0) return ret;
	return ret;
}

/********************************************************
*Terminate                                              *
********************************************************/
int ASN1_Print_Terminate(Terminate *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch(*value)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("Terminate", "other", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("Terminate", "serverRequested", 1)) < 0) return ret; break;
	case 2: if ((ret = ASN1_Print_ENUMERATED("Terminate", "clientRequested", 2)) < 0) return ret; break;
	case 3: if ((ret = ASN1_Print_ENUMERATED("Terminate", "serverShutdown", 3)) < 0) return ret; break;
	case 4: if ((ret = ASN1_Print_ENUMERATED("Terminate", "clientShutdown", 4)) < 0) return ret; break;
	case 5: if ((ret = ASN1_Print_ENUMERATED("Terminate", "serverCommProblems", 5)) < 0) return ret; break;
	case 6: if ((ret = ASN1_Print_ENUMERATED("Terminate", "clientCommProblems", 6)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	return ret;
}
int ASN1_CHECK_Terminate(Terminate *value)
{
	unsigned char checkinfo_Terminate[] = {0x07,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x00 };
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32 *)value, checkinfo_Terminate)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_Terminate(ASN1WorkSpace *workspace, Terminate *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_Terminate(ASN1WorkSpace *workspace, Terminate *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_Terminate(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Terminate(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_Terminate(ASN1WorkSpace *workspace, Terminate *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_Terminate(ASN1WorkSpace *workspace, Terminate *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Terminate(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_Terminate(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_Terminate(ASN1WorkSpace *workspace, Terminate *value)
{
	struct Asn1ConsInfo consinfo_Terminate = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_Terminate;
	switch(*value)
	{
	case Terminate_other: ui_Terminate = 0; consinfo_Terminate.enumextbit = 0; break;
	case Terminate_serverRequested: ui_Terminate = 1; consinfo_Terminate.enumextbit = 0; break;
	case Terminate_clientRequested: ui_Terminate = 2; consinfo_Terminate.enumextbit = 0; break;
	case Terminate_serverShutdown: ui_Terminate = 3; consinfo_Terminate.enumextbit = 0; break;
	case Terminate_clientShutdown: ui_Terminate = 4; consinfo_Terminate.enumextbit = 0; break;
	case Terminate_serverCommProblems: ui_Terminate = 5; consinfo_Terminate.enumextbit = 0; break;
	case Terminate_clientCommProblems: ui_Terminate = 6; consinfo_Terminate.enumextbit = 0; break;
	default: ui_Terminate = *value; consinfo_Terminate.enumextbit = 1; break;
	}
	if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_Terminate, &consinfo_Terminate)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Enc_Terminate(ASN1WorkSpace *workspace, Terminate *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Terminate(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_Terminate(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_Terminate(ASN1WorkSpace *workspace, Terminate *value)
{
	struct Asn1ConsInfo consinfo_Terminate = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_Terminate;
	if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_Terminate, &consinfo_Terminate)) < 0) return ret;
	if (consinfo_Terminate.enumextbit == 0)
	{
		switch(ui_Terminate)
		{
		case 0: *value = Terminate_other; break;
		case 1: *value = Terminate_serverRequested; break;
		case 2: *value = Terminate_clientRequested; break;
		case 3: *value = Terminate_serverShutdown; break;
		case 4: *value = Terminate_clientShutdown; break;
		case 5: *value = Terminate_serverCommProblems; break;
		case 6: *value = Terminate_clientCommProblems; break;
		default: break;
		}
	}
	else
	{
		switch(ui_Terminate)
		{
		default: *value = ui_Terminate; break;
		}
	}
	return ret;
}
int ASN1_PER_Align_Dec_Terminate(ASN1WorkSpace *workspace, Terminate *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_Terminate(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Terminate(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_Terminate(ASN1WorkSpace *workspace, Terminate *value)
{
	struct Asn1ConsInfo consinfo_Terminate = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_Terminate;
	switch(*value)
	{
	case Terminate_other: ui_Terminate = 0; consinfo_Terminate.enumextbit = 0; break;
	case Terminate_serverRequested: ui_Terminate = 1; consinfo_Terminate.enumextbit = 0; break;
	case Terminate_clientRequested: ui_Terminate = 2; consinfo_Terminate.enumextbit = 0; break;
	case Terminate_serverShutdown: ui_Terminate = 3; consinfo_Terminate.enumextbit = 0; break;
	case Terminate_clientShutdown: ui_Terminate = 4; consinfo_Terminate.enumextbit = 0; break;
	case Terminate_serverCommProblems: ui_Terminate = 5; consinfo_Terminate.enumextbit = 0; break;
	case Terminate_clientCommProblems: ui_Terminate = 6; consinfo_Terminate.enumextbit = 0; break;
	default: ui_Terminate = *value; consinfo_Terminate.enumextbit = 1; break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_Terminate, &consinfo_Terminate)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Enc_Terminate(ASN1WorkSpace *workspace, Terminate *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Terminate(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_Terminate(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_Terminate(ASN1WorkSpace *workspace, Terminate *value)
{
	struct Asn1ConsInfo consinfo_Terminate = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_Terminate;
	if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_Terminate, &consinfo_Terminate)) < 0) return ret;
	if (consinfo_Terminate.enumextbit == 0)
	{
		switch(ui_Terminate)
		{
		case 0: *value = Terminate_other; break;
		case 1: *value = Terminate_serverRequested; break;
		case 2: *value = Terminate_clientRequested; break;
		case 3: *value = Terminate_serverShutdown; break;
		case 4: *value = Terminate_clientShutdown; break;
		case 5: *value = Terminate_serverCommProblems; break;
		case 6: *value = Terminate_clientCommProblems; break;
		default: break;
		}
	}
	else
	{
		switch(ui_Terminate)
		{
		default: *value = ui_Terminate; break;
		}
	}
	return ret;
}
int ASN1_PER_UNAlign_Dec_Terminate(ASN1WorkSpace *workspace, Terminate *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_Terminate(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Terminate(value)) < 0) return ret;
	return ret;
}

/********************************************************
*Logout                                                 *
********************************************************/
int ASN1_Print_Logout(Logout *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch(*value)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("Logout", "other", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("Logout", "serverRequested", 1)) < 0) return ret; break;
	case 2: if ((ret = ASN1_Print_ENUMERATED("Logout", "clientRequested", 2)) < 0) return ret; break;
	case 3: if ((ret = ASN1_Print_ENUMERATED("Logout", "serverShutdown", 3)) < 0) return ret; break;
	case 4: if ((ret = ASN1_Print_ENUMERATED("Logout", "clientShutdown", 4)) < 0) return ret; break;
	case 5: if ((ret = ASN1_Print_ENUMERATED("Logout", "serverCommProblems", 5)) < 0) return ret; break;
	case 6: if ((ret = ASN1_Print_ENUMERATED("Logout", "clientCommProblems", 6)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	return ret;
}
int ASN1_CHECK_Logout(Logout *value)
{
	unsigned char checkinfo_Logout[] = {0x07,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x00 };
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32 *)value, checkinfo_Logout)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_Logout(ASN1WorkSpace *workspace, Logout *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_Logout(ASN1WorkSpace *workspace, Logout *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_Logout(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Logout(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_Logout(ASN1WorkSpace *workspace, Logout *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_Logout(ASN1WorkSpace *workspace, Logout *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Logout(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_Logout(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_Logout(ASN1WorkSpace *workspace, Logout *value)
{
	struct Asn1ConsInfo consinfo_Logout = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_Logout;
	switch(*value)
	{
	case Logout_other: ui_Logout = 0; consinfo_Logout.enumextbit = 0; break;
	case Logout_serverRequested: ui_Logout = 1; consinfo_Logout.enumextbit = 0; break;
	case Logout_clientRequested: ui_Logout = 2; consinfo_Logout.enumextbit = 0; break;
	case Logout_serverShutdown: ui_Logout = 3; consinfo_Logout.enumextbit = 0; break;
	case Logout_clientShutdown: ui_Logout = 4; consinfo_Logout.enumextbit = 0; break;
	case Logout_serverCommProblems: ui_Logout = 5; consinfo_Logout.enumextbit = 0; break;
	case Logout_clientCommProblems: ui_Logout = 6; consinfo_Logout.enumextbit = 0; break;
	default: ui_Logout = *value; consinfo_Logout.enumextbit = 1; break;
	}
	if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_Logout, &consinfo_Logout)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Enc_Logout(ASN1WorkSpace *workspace, Logout *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Logout(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_Logout(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_Logout(ASN1WorkSpace *workspace, Logout *value)
{
	struct Asn1ConsInfo consinfo_Logout = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_Logout;
	if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_Logout, &consinfo_Logout)) < 0) return ret;
	if (consinfo_Logout.enumextbit == 0)
	{
		switch(ui_Logout)
		{
		case 0: *value = Logout_other; break;
		case 1: *value = Logout_serverRequested; break;
		case 2: *value = Logout_clientRequested; break;
		case 3: *value = Logout_serverShutdown; break;
		case 4: *value = Logout_clientShutdown; break;
		case 5: *value = Logout_serverCommProblems; break;
		case 6: *value = Logout_clientCommProblems; break;
		default: break;
		}
	}
	else
	{
		switch(ui_Logout)
		{
		default: *value = ui_Logout; break;
		}
	}
	return ret;
}
int ASN1_PER_Align_Dec_Logout(ASN1WorkSpace *workspace, Logout *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_Logout(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Logout(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_Logout(ASN1WorkSpace *workspace, Logout *value)
{
	struct Asn1ConsInfo consinfo_Logout = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_Logout;
	switch(*value)
	{
	case Logout_other: ui_Logout = 0; consinfo_Logout.enumextbit = 0; break;
	case Logout_serverRequested: ui_Logout = 1; consinfo_Logout.enumextbit = 0; break;
	case Logout_clientRequested: ui_Logout = 2; consinfo_Logout.enumextbit = 0; break;
	case Logout_serverShutdown: ui_Logout = 3; consinfo_Logout.enumextbit = 0; break;
	case Logout_clientShutdown: ui_Logout = 4; consinfo_Logout.enumextbit = 0; break;
	case Logout_serverCommProblems: ui_Logout = 5; consinfo_Logout.enumextbit = 0; break;
	case Logout_clientCommProblems: ui_Logout = 6; consinfo_Logout.enumextbit = 0; break;
	default: ui_Logout = *value; consinfo_Logout.enumextbit = 1; break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_Logout, &consinfo_Logout)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Enc_Logout(ASN1WorkSpace *workspace, Logout *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Logout(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_Logout(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_Logout(ASN1WorkSpace *workspace, Logout *value)
{
	struct Asn1ConsInfo consinfo_Logout = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_Logout;
	if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_Logout, &consinfo_Logout)) < 0) return ret;
	if (consinfo_Logout.enumextbit == 0)
	{
		switch(ui_Logout)
		{
		case 0: *value = Logout_other; break;
		case 1: *value = Logout_serverRequested; break;
		case 2: *value = Logout_clientRequested; break;
		case 3: *value = Logout_serverShutdown; break;
		case 4: *value = Logout_clientShutdown; break;
		case 5: *value = Logout_serverCommProblems; break;
		case 6: *value = Logout_clientCommProblems; break;
		default: break;
		}
	}
	else
	{
		switch(ui_Logout)
		{
		default: *value = ui_Logout; break;
		}
	}
	return ret;
}
int ASN1_PER_UNAlign_Dec_Logout(ASN1WorkSpace *workspace, Logout *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_Logout(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Logout(value)) < 0) return ret;
	return ret;
}

/********************************************************
*SubscriptionData_datexSubscribe-Status-cd              *
********************************************************/
int ASN1_Print_SubscriptionData_datexSubscribe_Status_cd(SubscriptionData_datexSubscribe_Status_cd *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch(*value)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("SubscriptionData_datexSubscribe-Status-cd", "new", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("SubscriptionData_datexSubscribe-Status-cd", "update", 1)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	return ret;
}
int ASN1_CHECK_SubscriptionData_datexSubscribe_Status_cd(SubscriptionData_datexSubscribe_Status_cd *value)
{
	unsigned char checkinfo_SubscriptionData_datexSubscribe_Status_cd[] = {0x02,0x00,0x01,0x00 };
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32 *)value, checkinfo_SubscriptionData_datexSubscribe_Status_cd)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_SubscriptionData_datexSubscribe_Status_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_Status_cd *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_SubscriptionData_datexSubscribe_Status_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_Status_cd *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_SubscriptionData_datexSubscribe_Status_cd(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SubscriptionData_datexSubscribe_Status_cd(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_SubscriptionData_datexSubscribe_Status_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_Status_cd *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_SubscriptionData_datexSubscribe_Status_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_Status_cd *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SubscriptionData_datexSubscribe_Status_cd(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_SubscriptionData_datexSubscribe_Status_cd(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_SubscriptionData_datexSubscribe_Status_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_Status_cd *value)
{
	struct Asn1ConsInfo consinfo_SubscriptionData_datexSubscribe_Status_cd = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 0, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_SubscriptionData_datexSubscribe_Status_cd;
	switch(*value)
	{
	case SubscriptionData_datexSubscribe_Status_cd_new: ui_SubscriptionData_datexSubscribe_Status_cd = 0; consinfo_SubscriptionData_datexSubscribe_Status_cd.enumextbit = 0; break;
	case SubscriptionData_datexSubscribe_Status_cd_update: ui_SubscriptionData_datexSubscribe_Status_cd = 1; consinfo_SubscriptionData_datexSubscribe_Status_cd.enumextbit = 0; break;
	default: ui_SubscriptionData_datexSubscribe_Status_cd = *value; consinfo_SubscriptionData_datexSubscribe_Status_cd.enumextbit = 0; break;
	}
	if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_SubscriptionData_datexSubscribe_Status_cd, &consinfo_SubscriptionData_datexSubscribe_Status_cd)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Enc_SubscriptionData_datexSubscribe_Status_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_Status_cd *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_SubscriptionData_datexSubscribe_Status_cd(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_SubscriptionData_datexSubscribe_Status_cd(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_SubscriptionData_datexSubscribe_Status_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_Status_cd *value)
{
	struct Asn1ConsInfo consinfo_SubscriptionData_datexSubscribe_Status_cd = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 0, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_SubscriptionData_datexSubscribe_Status_cd;
	if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_SubscriptionData_datexSubscribe_Status_cd, &consinfo_SubscriptionData_datexSubscribe_Status_cd)) < 0) return ret;
	if (consinfo_SubscriptionData_datexSubscribe_Status_cd.enumextbit == 0)
	{
		switch(ui_SubscriptionData_datexSubscribe_Status_cd)
		{
		case 0: *value = SubscriptionData_datexSubscribe_Status_cd_new; break;
		case 1: *value = SubscriptionData_datexSubscribe_Status_cd_update; break;
		default: *value = ui_SubscriptionData_datexSubscribe_Status_cd; break;
		}
	}
	return ret;
}
int ASN1_PER_Align_Dec_SubscriptionData_datexSubscribe_Status_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_Status_cd *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_SubscriptionData_datexSubscribe_Status_cd(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_SubscriptionData_datexSubscribe_Status_cd(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_SubscriptionData_datexSubscribe_Status_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_Status_cd *value)
{
	struct Asn1ConsInfo consinfo_SubscriptionData_datexSubscribe_Status_cd = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 0, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_SubscriptionData_datexSubscribe_Status_cd;
	switch(*value)
	{
	case SubscriptionData_datexSubscribe_Status_cd_new: ui_SubscriptionData_datexSubscribe_Status_cd = 0; consinfo_SubscriptionData_datexSubscribe_Status_cd.enumextbit = 0; break;
	case SubscriptionData_datexSubscribe_Status_cd_update: ui_SubscriptionData_datexSubscribe_Status_cd = 1; consinfo_SubscriptionData_datexSubscribe_Status_cd.enumextbit = 0; break;
	default: ui_SubscriptionData_datexSubscribe_Status_cd = *value; consinfo_SubscriptionData_datexSubscribe_Status_cd.enumextbit = 0; break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_SubscriptionData_datexSubscribe_Status_cd, &consinfo_SubscriptionData_datexSubscribe_Status_cd)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Enc_SubscriptionData_datexSubscribe_Status_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_Status_cd *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_SubscriptionData_datexSubscribe_Status_cd(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_SubscriptionData_datexSubscribe_Status_cd(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_SubscriptionData_datexSubscribe_Status_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_Status_cd *value)
{
	struct Asn1ConsInfo consinfo_SubscriptionData_datexSubscribe_Status_cd = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 0, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_SubscriptionData_datexSubscribe_Status_cd;
	if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_SubscriptionData_datexSubscribe_Status_cd, &consinfo_SubscriptionData_datexSubscribe_Status_cd)) < 0) return ret;
	if (consinfo_SubscriptionData_datexSubscribe_Status_cd.enumextbit == 0)
	{
		switch(ui_SubscriptionData_datexSubscribe_Status_cd)
		{
		case 0: *value = SubscriptionData_datexSubscribe_Status_cd_new; break;
		case 1: *value = SubscriptionData_datexSubscribe_Status_cd_update; break;
		default: *value = ui_SubscriptionData_datexSubscribe_Status_cd; break;
		}
	}
	return ret;
}
int ASN1_PER_UNAlign_Dec_SubscriptionData_datexSubscribe_Status_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_Status_cd *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_SubscriptionData_datexSubscribe_Status_cd(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_SubscriptionData_datexSubscribe_Status_cd(value)) < 0) return ret;
	return ret;
}

/********************************************************
*Registered_continuous                                  *
********************************************************/
int ASN1_Print_Registered_continuous(Registered_continuous *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("Registered-continuous");
	if (value->DEF_Registered_continuous_datexRegistered_UpdateDelay_qty == 1)
	{ /* DEFAULT start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("datexRegistered_UpdateDelay_qty", &(value->datexRegistered_UpdateDelay_qty))) < 0) return ret;
	} /* DEFAULT end */
	if (value->DEF_Registered_continuous_datexRegistered_StartTime == 1)
	{ /*OPTIONAL start */
		// Type Reference IsoTime
		if (Compare_Letter(tab_value, "datexRegistered-StartTime")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("datexRegistered-StartTime = ");
		}
		if ((ret = ASN1_Print_IsoTime((IsoTime *)value->datexRegistered_StartTime, tab_value + 1)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_Registered_continuous_datexRegistered_EndTime == 1)
	{ /*OPTIONAL start */
		// Type Reference IsoTime
		if (Compare_Letter(tab_value, "datexRegistered-EndTime")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("datexRegistered-EndTime = ");
		}
		if ((ret = ASN1_Print_IsoTime((IsoTime *)value->datexRegistered_EndTime, tab_value + 1)) < 0) return ret;
	} /* OPTIONAL end */
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_Registered_continuous_datexRegistered_UpdateDelay_qty(ASN1WorkSpace *workspace, Registered_continuous *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_Registered_continuous_datexRegistered_UpdateDelay_qty = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->datexRegistered_UpdateDelay_qty, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_Registered_continuous_datexRegistered_StartTime(ASN1WorkSpace *workspace, Registered_continuous *value, IsoTime *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->datexRegistered_StartTime = (IsoTime *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime));
	memset(value->datexRegistered_StartTime, 0, sizeof(IsoTime));
	value->DEF_Registered_continuous_datexRegistered_StartTime = 1;
	memmove(value->datexRegistered_StartTime, user_value, sizeof(IsoTime));
	return ret;
}
int ASN1_SET_Registered_continuous_datexRegistered_EndTime(ASN1WorkSpace *workspace, Registered_continuous *value, IsoTime *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->datexRegistered_EndTime = (IsoTime *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime));
	memset(value->datexRegistered_EndTime, 0, sizeof(IsoTime));
	value->DEF_Registered_continuous_datexRegistered_EndTime = 1;
	memmove(value->datexRegistered_EndTime, user_value, sizeof(IsoTime));
	return ret;
}
int ASN1_GET_Registered_continuous_datexRegistered_UpdateDelay_qty(ASN1WorkSpace *workspace, Registered_continuous *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_Registered_continuous_datexRegistered_UpdateDelay_qty == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->datexRegistered_UpdateDelay_qty, user_value)) < 0) return ret;
	}
	else return -3;
	return ret;
}
int ASN1_GET_Registered_continuous_datexRegistered_StartTime(ASN1WorkSpace *workspace, Registered_continuous *value, IsoTime **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_Registered_continuous_datexRegistered_StartTime == 1)
	{
		*user_value = value->datexRegistered_StartTime;
	}
	else return -2;
	return ret;
}
int ASN1_GET_Registered_continuous_datexRegistered_EndTime(ASN1WorkSpace *workspace, Registered_continuous *value, IsoTime **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_Registered_continuous_datexRegistered_EndTime == 1)
	{
		*user_value = value->datexRegistered_EndTime;
	}
	else return -2;
	return ret;
}
extern int ASN1_CHECK_IsoTime(IsoTime *value);
extern int ASN1_CHECK_IsoTime(IsoTime *value);
int ASN1_CHECK_Registered_continuous(Registered_continuous *value)
{
	int ret = 0;

	unsigned char checkinfo_datexRegistered_UpdateDelay_qty[] = { 
		0x02,0x00,0x85,0x00,0xFF,0xFF,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_datexRegistered_StartTime[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datexRegistered_EndTime[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if (value->DEF_Registered_continuous_datexRegistered_UpdateDelay_qty == 1)
	{ /* DEFAULT start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->datexRegistered_UpdateDelay_qty), checkinfo_datexRegistered_UpdateDelay_qty)) < 0) return ret;
	} /* DEFAULT end */
	if (value->DEF_Registered_continuous_datexRegistered_StartTime == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_IsoTime(value->datexRegistered_StartTime)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_Registered_continuous_datexRegistered_EndTime == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_IsoTime(value->datexRegistered_EndTime)) < 0) return ret;
	} /* OPTIONAL end */
	return ret;
}
extern int ASN1_BER_Data_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if (value->DEF_Registered_continuous_datexRegistered_UpdateDelay_qty == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->datexRegistered_UpdateDelay_qty), ASN1IMPL)) < 0) return ret;
	}
	if (value->DEF_Registered_continuous_datexRegistered_StartTime == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 1)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_IsoTime(workspace, value->datexRegistered_StartTime, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	if (value->DEF_Registered_continuous_datexRegistered_EndTime == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 2)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_IsoTime(workspace, value->datexRegistered_EndTime, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Registered_continuous(Registered_continuous *value);
extern int ASN1_BER_Data_Enc_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_Registered_continuous(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Registered_continuous(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	ASNUINT8 *_cpointer;
	value->datexRegistered_StartTime = (IsoTime *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime));
	memset(value->datexRegistered_StartTime, 0, sizeof(IsoTime));
	value->datexRegistered_EndTime = (IsoTime *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime));
	memset(value->datexRegistered_EndTime, 0, sizeof(IsoTime));
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 0))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->datexRegistered_UpdateDelay_qty, len, ASN1IMPL)) < 0) return ret;
		value->DEF_Registered_continuous_datexRegistered_UpdateDelay_qty = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_CONS | 1))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 1)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_IsoTime(workspace, value->datexRegistered_StartTime, len, ASN1IMPL)) < 0) return ret;
		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->DEF_Registered_continuous_datexRegistered_StartTime = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_CONS | 2))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 2)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_IsoTime(workspace, value->datexRegistered_EndTime, len, ASN1IMPL)) < 0) return ret;
		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->DEF_Registered_continuous_datexRegistered_EndTime = 1;
	}
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_Registered_continuous(Registered_continuous *value);
extern int ASN1_BER_Data_Dec_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Registered_continuous(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_Registered_continuous(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
extern int ASN1_PER_Align_Data_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
int ASN1_PER_Align_Data_Enc_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexRegistered_UpdateDelay_qty = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_StartTime = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_EndTime = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_Registered_continuous_datexRegistered_UpdateDelay_qty == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_Registered_continuous_datexRegistered_StartTime == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_Registered_continuous_datexRegistered_EndTime == 1 ? 1 : 0) )) < 0) return ret;
	if (value->DEF_Registered_continuous_datexRegistered_UpdateDelay_qty == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->datexRegistered_UpdateDelay_qty), &consinfo_datexRegistered_UpdateDelay_qty)) < 0) return ret;
	}
	if (value->DEF_Registered_continuous_datexRegistered_StartTime == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_IsoTime(workspace, value->datexRegistered_StartTime)) < 0) return ret;
	}
	if (value->DEF_Registered_continuous_datexRegistered_EndTime == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_IsoTime(workspace, value->datexRegistered_EndTime)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Registered_continuous(Registered_continuous *value);
extern int ASN1_PER_Align_Data_Enc_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value);
int ASN1_PER_Align_Enc_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Registered_continuous(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_Registered_continuous(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
extern int ASN1_PER_Align_Data_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
int ASN1_PER_Align_Data_Dec_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexRegistered_UpdateDelay_qty = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_StartTime = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_EndTime = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNUINT8 *_optvalue;
	if ((ret = ASN1_PER_Dec_Opt_Def_bit(workspace, 3, &_optvalue)) < 0) return ret;
	value->datexRegistered_StartTime = (IsoTime *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime));
	memset(value->datexRegistered_StartTime, 0, sizeof(IsoTime));
	value->datexRegistered_EndTime = (IsoTime *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime));
	memset(value->datexRegistered_EndTime, 0, sizeof(IsoTime));
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_Registered_continuous_datexRegistered_UpdateDelay_qty = 1;
		if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->datexRegistered_UpdateDelay_qty), &consinfo_datexRegistered_UpdateDelay_qty)) < 0) return ret;
	}
	else
	{
		value->datexRegistered_UpdateDelay_qty = 0;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_Registered_continuous_datexRegistered_StartTime = 1;
		if ((ret = ASN1_PER_Align_Dec_IsoTime(workspace, value->datexRegistered_StartTime)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_Registered_continuous_datexRegistered_EndTime = 1;
		if ((ret = ASN1_PER_Align_Dec_IsoTime(workspace, value->datexRegistered_EndTime)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Registered_continuous(Registered_continuous *value);
extern int ASN1_PER_Align_Data_Dec_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value);
int ASN1_PER_Align_Dec_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_Registered_continuous(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Registered_continuous(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
extern int ASN1_PER_UNAlign_Data_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
int ASN1_PER_UNAlign_Data_Enc_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexRegistered_UpdateDelay_qty = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_StartTime = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_EndTime = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_Registered_continuous_datexRegistered_UpdateDelay_qty == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_Registered_continuous_datexRegistered_StartTime == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_Registered_continuous_datexRegistered_EndTime == 1 ? 1 : 0) )) < 0) return ret;
	if (value->DEF_Registered_continuous_datexRegistered_UpdateDelay_qty == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->datexRegistered_UpdateDelay_qty), &consinfo_datexRegistered_UpdateDelay_qty)) < 0) return ret;
	}
	if (value->DEF_Registered_continuous_datexRegistered_StartTime == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_IsoTime(workspace, value->datexRegistered_StartTime)) < 0) return ret;
	}
	if (value->DEF_Registered_continuous_datexRegistered_EndTime == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_IsoTime(workspace, value->datexRegistered_EndTime)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Registered_continuous(Registered_continuous *value);
extern int ASN1_PER_UNAlign_Data_Enc_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value);
int ASN1_PER_UNAlign_Enc_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Registered_continuous(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_Registered_continuous(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
extern int ASN1_PER_UNAlign_Data_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
int ASN1_PER_UNAlign_Data_Dec_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexRegistered_UpdateDelay_qty = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_StartTime = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_EndTime = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNUINT8 *_optvalue;
	if ((ret = ASN1_PER_Dec_Opt_Def_bit(workspace, 3, &_optvalue)) < 0) return ret;
	value->datexRegistered_StartTime = (IsoTime *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime));
	memset(value->datexRegistered_StartTime, 0, sizeof(IsoTime));
	value->datexRegistered_EndTime = (IsoTime *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime));
	memset(value->datexRegistered_EndTime, 0, sizeof(IsoTime));
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_Registered_continuous_datexRegistered_UpdateDelay_qty = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->datexRegistered_UpdateDelay_qty), &consinfo_datexRegistered_UpdateDelay_qty)) < 0) return ret;
	}
	else
	{
		value->datexRegistered_UpdateDelay_qty = 0;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_Registered_continuous_datexRegistered_StartTime = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_IsoTime(workspace, value->datexRegistered_StartTime)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_Registered_continuous_datexRegistered_EndTime = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_IsoTime(workspace, value->datexRegistered_EndTime)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Registered_continuous(Registered_continuous *value);
extern int ASN1_PER_UNAlign_Data_Dec_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value);
int ASN1_PER_UNAlign_Dec_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_Registered_continuous(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Registered_continuous(value)) < 0) return ret;
	return ret;
}

/********************************************************
*Registered-daily_datexRegistered-DaysOfWeek-cd         *
********************************************************/
int ASN1_Print_Registered_daily_datexRegistered_DaysOfWeek_cd(Registered_daily_datexRegistered_DaysOfWeek_cd *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// Type Default
	if ((ret = ASN1_Print_BITSTRING("datexRegistered-DaysOfWeek-cd", value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_Registered_daily_datexRegistered_DaysOfWeek_cd(Registered_daily_datexRegistered_DaysOfWeek_cd *value)
{
	unsigned char checkinfo_Registered_daily_datexRegistered_DaysOfWeek_cd[] = { 
		0x02,0x08,0x08,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_BITSTRING(value, checkinfo_Registered_daily_datexRegistered_DaysOfWeek_cd)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_Registered_daily_datexRegistered_DaysOfWeek_cd(ASN1WorkSpace *workspace, Registered_daily_datexRegistered_DaysOfWeek_cd *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_BITSTRING(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_Registered_daily_datexRegistered_DaysOfWeek_cd(ASN1WorkSpace *workspace, Registered_daily_datexRegistered_DaysOfWeek_cd *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_Registered_daily_datexRegistered_DaysOfWeek_cd(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Registered_daily_datexRegistered_DaysOfWeek_cd(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_Registered_daily_datexRegistered_DaysOfWeek_cd(ASN1WorkSpace *workspace, Registered_daily_datexRegistered_DaysOfWeek_cd *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_BITSTRING(workspace, value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_Registered_daily_datexRegistered_DaysOfWeek_cd(ASN1WorkSpace *workspace, Registered_daily_datexRegistered_DaysOfWeek_cd *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Registered_daily_datexRegistered_DaysOfWeek_cd(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_Registered_daily_datexRegistered_DaysOfWeek_cd(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_Registered_daily_datexRegistered_DaysOfWeek_cd(ASN1WorkSpace *workspace, Registered_daily_datexRegistered_DaysOfWeek_cd *value)
{
	struct Asn1ConsInfo consinfo_Registered_daily_datexRegistered_DaysOfWeek_cd = { ASN1_CONST64(8), ASN1_CONST64(8), NULL, 0, CONS, 0, 1 };
	int ret = 0;
	if ((ret = ASN1_PER_Align_Enc_BITSTRING(workspace, value, &consinfo_Registered_daily_datexRegistered_DaysOfWeek_cd)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Enc_Registered_daily_datexRegistered_DaysOfWeek_cd(ASN1WorkSpace *workspace, Registered_daily_datexRegistered_DaysOfWeek_cd *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Registered_daily_datexRegistered_DaysOfWeek_cd(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_Registered_daily_datexRegistered_DaysOfWeek_cd(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_Registered_daily_datexRegistered_DaysOfWeek_cd(ASN1WorkSpace *workspace, Registered_daily_datexRegistered_DaysOfWeek_cd *value)
{
	struct Asn1ConsInfo consinfo_Registered_daily_datexRegistered_DaysOfWeek_cd = { ASN1_CONST64(8), ASN1_CONST64(8), NULL, 0, CONS, 0, 1 };
	int ret = 0;
	if ((ret = ASN1_PER_Align_Dec_BITSTRING(workspace, value, &consinfo_Registered_daily_datexRegistered_DaysOfWeek_cd)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Dec_Registered_daily_datexRegistered_DaysOfWeek_cd(ASN1WorkSpace *workspace, Registered_daily_datexRegistered_DaysOfWeek_cd *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_Registered_daily_datexRegistered_DaysOfWeek_cd(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Registered_daily_datexRegistered_DaysOfWeek_cd(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_Registered_daily_datexRegistered_DaysOfWeek_cd(ASN1WorkSpace *workspace, Registered_daily_datexRegistered_DaysOfWeek_cd *value)
{
	struct Asn1ConsInfo consinfo_Registered_daily_datexRegistered_DaysOfWeek_cd = { ASN1_CONST64(8), ASN1_CONST64(8), NULL, 0, CONS, 0, 1 };
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Enc_BITSTRING(workspace, value, &consinfo_Registered_daily_datexRegistered_DaysOfWeek_cd)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Enc_Registered_daily_datexRegistered_DaysOfWeek_cd(ASN1WorkSpace *workspace, Registered_daily_datexRegistered_DaysOfWeek_cd *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Registered_daily_datexRegistered_DaysOfWeek_cd(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_Registered_daily_datexRegistered_DaysOfWeek_cd(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_Registered_daily_datexRegistered_DaysOfWeek_cd(ASN1WorkSpace *workspace, Registered_daily_datexRegistered_DaysOfWeek_cd *value)
{
	struct Asn1ConsInfo consinfo_Registered_daily_datexRegistered_DaysOfWeek_cd = { ASN1_CONST64(8), ASN1_CONST64(8), NULL, 0, CONS, 0, 1 };
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Dec_BITSTRING(workspace, value, &consinfo_Registered_daily_datexRegistered_DaysOfWeek_cd)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Dec_Registered_daily_datexRegistered_DaysOfWeek_cd(ASN1WorkSpace *workspace, Registered_daily_datexRegistered_DaysOfWeek_cd *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_Registered_daily_datexRegistered_DaysOfWeek_cd(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Registered_daily_datexRegistered_DaysOfWeek_cd(value)) < 0) return ret;
	return ret;
}

/********************************************************
*Registered_daily                                       *
********************************************************/
int ASN1_Print_Registered_daily(Registered_daily *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("Registered-daily");
	if (value->DEF_Registered_daily_datexRegistered_UpdateDelay_qty == 1)
	{ /* DEFAULT start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("datexRegistered_UpdateDelay_qty", &(value->datexRegistered_UpdateDelay_qty))) < 0) return ret;
	} /* DEFAULT end */
	// Type Default
	// Type is Referenced
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_BITSTRING("Registered_daily_datexRegistered_DaysOfWeek_cd", &(value->datexRegistered_DaysOfWeek_cd))) < 0) return ret;
	if (value->DEF_Registered_daily_datexRegistered_StartDate == 1)
	{ /*OPTIONAL start */
		// Type Reference IsoTime
		if (Compare_Letter(tab_value, "datexRegistered-StartDate")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("datexRegistered-StartDate = ");
		}
		if ((ret = ASN1_Print_IsoTime((IsoTime *)value->datexRegistered_StartDate, tab_value + 1)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_Registered_daily_datexRegistered_EndDate == 1)
	{ /*OPTIONAL start */
		// Type Reference IsoTime
		if (Compare_Letter(tab_value, "datexRegistered-EndDate")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("datexRegistered-EndDate = ");
		}
		if ((ret = ASN1_Print_IsoTime((IsoTime *)value->datexRegistered_EndDate, tab_value + 1)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_Registered_daily_datexRegistered_StartTime == 1)
	{ /*OPTIONAL start */
		// Type Reference IsoTime
		if (Compare_Letter(tab_value, "datexRegistered-StartTime")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("datexRegistered-StartTime = ");
		}
		if ((ret = ASN1_Print_IsoTime((IsoTime *)value->datexRegistered_StartTime, tab_value + 1)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_Registered_daily_datexRegistered_Duration_qty == 1)
	{ /*OPTIONAL start */
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("datexRegistered_Duration_qty", &(value->datexRegistered_Duration_qty))) < 0) return ret;
	} /* OPTIONAL end */
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_Registered_daily_datexRegistered_UpdateDelay_qty(ASN1WorkSpace *workspace, Registered_daily *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_Registered_daily_datexRegistered_UpdateDelay_qty = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->datexRegistered_UpdateDelay_qty, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_Registered_daily_datexRegistered_DaysOfWeek_cd(ASN1WorkSpace *workspace, Registered_daily *value, ASNUINT8 *user_value, ASNUINT32L user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_BITSTRING(workspace, &value->datexRegistered_DaysOfWeek_cd, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_Registered_daily_datexRegistered_StartDate(ASN1WorkSpace *workspace, Registered_daily *value, IsoTime *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->datexRegistered_StartDate = (IsoTime *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime));
	memset(value->datexRegistered_StartDate, 0, sizeof(IsoTime));
	value->DEF_Registered_daily_datexRegistered_StartDate = 1;
	memmove(value->datexRegistered_StartDate, user_value, sizeof(IsoTime));
	return ret;
}
int ASN1_SET_Registered_daily_datexRegistered_EndDate(ASN1WorkSpace *workspace, Registered_daily *value, IsoTime *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->datexRegistered_EndDate = (IsoTime *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime));
	memset(value->datexRegistered_EndDate, 0, sizeof(IsoTime));
	value->DEF_Registered_daily_datexRegistered_EndDate = 1;
	memmove(value->datexRegistered_EndDate, user_value, sizeof(IsoTime));
	return ret;
}
int ASN1_SET_Registered_daily_datexRegistered_StartTime(ASN1WorkSpace *workspace, Registered_daily *value, IsoTime *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->datexRegistered_StartTime = (IsoTime *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime));
	memset(value->datexRegistered_StartTime, 0, sizeof(IsoTime));
	value->DEF_Registered_daily_datexRegistered_StartTime = 1;
	memmove(value->datexRegistered_StartTime, user_value, sizeof(IsoTime));
	return ret;
}
int ASN1_SET_Registered_daily_datexRegistered_Duration_qty(ASN1WorkSpace *workspace, Registered_daily *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->DEF_Registered_daily_datexRegistered_Duration_qty = 1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->datexRegistered_Duration_qty, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_Registered_daily_datexRegistered_UpdateDelay_qty(ASN1WorkSpace *workspace, Registered_daily *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_Registered_daily_datexRegistered_UpdateDelay_qty == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->datexRegistered_UpdateDelay_qty, user_value)) < 0) return ret;
	}
	else return -3;
	return ret;
}
int ASN1_GET_Registered_daily_datexRegistered_DaysOfWeek_cd(ASN1WorkSpace *workspace, Registered_daily *value, ASNUINT8 **user_value, ASNUINT32L *user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_BITSTRING(workspace, &value->datexRegistered_DaysOfWeek_cd, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_Registered_daily_datexRegistered_StartDate(ASN1WorkSpace *workspace, Registered_daily *value, IsoTime **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_Registered_daily_datexRegistered_StartDate == 1)
	{
		*user_value = value->datexRegistered_StartDate;
	}
	else return -2;
	return ret;
}
int ASN1_GET_Registered_daily_datexRegistered_EndDate(ASN1WorkSpace *workspace, Registered_daily *value, IsoTime **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_Registered_daily_datexRegistered_EndDate == 1)
	{
		*user_value = value->datexRegistered_EndDate;
	}
	else return -2;
	return ret;
}
int ASN1_GET_Registered_daily_datexRegistered_StartTime(ASN1WorkSpace *workspace, Registered_daily *value, IsoTime **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_Registered_daily_datexRegistered_StartTime == 1)
	{
		*user_value = value->datexRegistered_StartTime;
	}
	else return -2;
	return ret;
}
int ASN1_GET_Registered_daily_datexRegistered_Duration_qty(ASN1WorkSpace *workspace, Registered_daily *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->DEF_Registered_daily_datexRegistered_Duration_qty == 1)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->datexRegistered_Duration_qty, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
extern int ASN1_CHECK_IsoTime(IsoTime *value);
extern int ASN1_CHECK_IsoTime(IsoTime *value);
extern int ASN1_CHECK_IsoTime(IsoTime *value);
int ASN1_CHECK_Registered_daily(Registered_daily *value)
{
	int ret = 0;

	unsigned char checkinfo_datexRegistered_UpdateDelay_qty[] = { 
		0x02,0x00,0x85,0x00,0xFF,0xFF,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_datexRegistered_DaysOfWeek_cd[] = { 
		0x02,0x08,0x08,0x00
	};
	unsigned char checkinfo_datexRegistered_StartDate[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datexRegistered_EndDate[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datexRegistered_StartTime[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datexRegistered_Duration_qty[] = { 
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};

	if (value == NULL) return -1;
	if (value->DEF_Registered_daily_datexRegistered_UpdateDelay_qty == 1)
	{ /* DEFAULT start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->datexRegistered_UpdateDelay_qty), checkinfo_datexRegistered_UpdateDelay_qty)) < 0) return ret;
	} /* DEFAULT end */
	if ((ret = ASN1_CHECK_BITSTRING(&(value->datexRegistered_DaysOfWeek_cd), checkinfo_datexRegistered_DaysOfWeek_cd)) < 0) return ret;
	if (value->DEF_Registered_daily_datexRegistered_StartDate == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_IsoTime(value->datexRegistered_StartDate)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_Registered_daily_datexRegistered_EndDate == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_IsoTime(value->datexRegistered_EndDate)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_Registered_daily_datexRegistered_StartTime == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_IsoTime(value->datexRegistered_StartTime)) < 0) return ret;
	} /* OPTIONAL end */
	if (value->DEF_Registered_daily_datexRegistered_Duration_qty == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_INTEGER(&(value->datexRegistered_Duration_qty), checkinfo_datexRegistered_Duration_qty)) < 0) return ret;
	} /* OPTIONAL end */
	return ret;
}
extern int ASN1_BER_Data_Enc_Registered_daily_datexRegistered_DaysOfWeek_cd(ASN1WorkSpace *workspace, Registered_daily_datexRegistered_DaysOfWeek_cd *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if (value->DEF_Registered_daily_datexRegistered_UpdateDelay_qty == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->datexRegistered_UpdateDelay_qty), ASN1IMPL)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Registered_daily_datexRegistered_DaysOfWeek_cd(workspace, &(value->datexRegistered_DaysOfWeek_cd), ASN1IMPL)) < 0) return ret;
	if (value->DEF_Registered_daily_datexRegistered_StartDate == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 2)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_IsoTime(workspace, value->datexRegistered_StartDate, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	if (value->DEF_Registered_daily_datexRegistered_EndDate == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 3)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_IsoTime(workspace, value->datexRegistered_EndDate, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	if (value->DEF_Registered_daily_datexRegistered_StartTime == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 4)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_IsoTime(workspace, value->datexRegistered_StartTime, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	if (value->DEF_Registered_daily_datexRegistered_Duration_qty == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->datexRegistered_Duration_qty), ASN1IMPL)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Registered_daily(Registered_daily *value);
extern int ASN1_BER_Data_Enc_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_Registered_daily(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Registered_daily(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_Registered_daily_datexRegistered_DaysOfWeek_cd(ASN1WorkSpace *workspace, Registered_daily_datexRegistered_DaysOfWeek_cd *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	ASNUINT8 *_cpointer;
	value->datexRegistered_StartDate = (IsoTime *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime));
	memset(value->datexRegistered_StartDate, 0, sizeof(IsoTime));
	value->datexRegistered_EndDate = (IsoTime *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime));
	memset(value->datexRegistered_EndDate, 0, sizeof(IsoTime));
	value->datexRegistered_StartTime = (IsoTime *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime));
	memset(value->datexRegistered_StartTime, 0, sizeof(IsoTime));
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 0))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->datexRegistered_UpdateDelay_qty, len, ASN1IMPL)) < 0) return ret;
		value->DEF_Registered_daily_datexRegistered_UpdateDelay_qty = 1;
	}
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Registered_daily_datexRegistered_DaysOfWeek_cd(workspace, &value->datexRegistered_DaysOfWeek_cd, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_CONS | 2))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 2)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_IsoTime(workspace, value->datexRegistered_StartDate, len, ASN1IMPL)) < 0) return ret;
		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->DEF_Registered_daily_datexRegistered_StartDate = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_CONS | 3))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 3)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_IsoTime(workspace, value->datexRegistered_EndDate, len, ASN1IMPL)) < 0) return ret;
		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->DEF_Registered_daily_datexRegistered_EndDate = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_CONS | 4))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 4)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_IsoTime(workspace, value->datexRegistered_StartTime, len, ASN1IMPL)) < 0) return ret;
		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->DEF_Registered_daily_datexRegistered_StartTime = 1;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_PRIM | 5))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->datexRegistered_Duration_qty, len, ASN1IMPL)) < 0) return ret;
		value->DEF_Registered_daily_datexRegistered_Duration_qty = 1;
	}
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_Registered_daily(Registered_daily *value);
extern int ASN1_BER_Data_Dec_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Registered_daily(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_Registered_daily(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
extern int ASN1_PER_Align_Data_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
extern int ASN1_PER_Align_Data_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
int ASN1_PER_Align_Data_Enc_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexRegistered_UpdateDelay_qty = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_DaysOfWeek_cd = { ASN1_CONST64(8), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_StartDate = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_EndDate = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_StartTime = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_Duration_qty = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };

	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_Registered_daily_datexRegistered_UpdateDelay_qty == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_Registered_daily_datexRegistered_StartDate == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_Registered_daily_datexRegistered_EndDate == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_Registered_daily_datexRegistered_StartTime == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_Registered_daily_datexRegistered_Duration_qty == 1 ? 1 : 0) )) < 0) return ret;
	if (value->DEF_Registered_daily_datexRegistered_UpdateDelay_qty == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->datexRegistered_UpdateDelay_qty), &consinfo_datexRegistered_UpdateDelay_qty)) < 0) return ret;
	}
	if ((ret = ASN1_PER_Align_Enc_BITSTRING(workspace, &(value->datexRegistered_DaysOfWeek_cd), &consinfo_datexRegistered_DaysOfWeek_cd)) < 0) return ret;
	if (value->DEF_Registered_daily_datexRegistered_StartDate == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_IsoTime(workspace, value->datexRegistered_StartDate)) < 0) return ret;
	}
	if (value->DEF_Registered_daily_datexRegistered_EndDate == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_IsoTime(workspace, value->datexRegistered_EndDate)) < 0) return ret;
	}
	if (value->DEF_Registered_daily_datexRegistered_StartTime == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_IsoTime(workspace, value->datexRegistered_StartTime)) < 0) return ret;
	}
	if (value->DEF_Registered_daily_datexRegistered_Duration_qty == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->datexRegistered_Duration_qty), &consinfo_datexRegistered_Duration_qty)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Registered_daily(Registered_daily *value);
extern int ASN1_PER_Align_Data_Enc_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value);
int ASN1_PER_Align_Enc_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Registered_daily(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_Registered_daily(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
extern int ASN1_PER_Align_Data_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
extern int ASN1_PER_Align_Data_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
int ASN1_PER_Align_Data_Dec_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexRegistered_UpdateDelay_qty = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_DaysOfWeek_cd = { ASN1_CONST64(8), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_StartDate = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_EndDate = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_StartTime = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_Duration_qty = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };

	ASNUINT8 *_optvalue;
	if ((ret = ASN1_PER_Dec_Opt_Def_bit(workspace, 5, &_optvalue)) < 0) return ret;
	value->datexRegistered_StartDate = (IsoTime *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime));
	memset(value->datexRegistered_StartDate, 0, sizeof(IsoTime));
	value->datexRegistered_EndDate = (IsoTime *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime));
	memset(value->datexRegistered_EndDate, 0, sizeof(IsoTime));
	value->datexRegistered_StartTime = (IsoTime *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime));
	memset(value->datexRegistered_StartTime, 0, sizeof(IsoTime));
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_Registered_daily_datexRegistered_UpdateDelay_qty = 1;
		if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->datexRegistered_UpdateDelay_qty), &consinfo_datexRegistered_UpdateDelay_qty)) < 0) return ret;
	}
	else
	{
		value->datexRegistered_UpdateDelay_qty = 0;
	}
	if ((ret = ASN1_PER_Align_Dec_BITSTRING(workspace, &(value->datexRegistered_DaysOfWeek_cd), &consinfo_datexRegistered_DaysOfWeek_cd)) < 0) return ret;
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_Registered_daily_datexRegistered_StartDate = 1;
		if ((ret = ASN1_PER_Align_Dec_IsoTime(workspace, value->datexRegistered_StartDate)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_Registered_daily_datexRegistered_EndDate = 1;
		if ((ret = ASN1_PER_Align_Dec_IsoTime(workspace, value->datexRegistered_EndDate)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 4) == 1)
	{
		value->DEF_Registered_daily_datexRegistered_StartTime = 1;
		if ((ret = ASN1_PER_Align_Dec_IsoTime(workspace, value->datexRegistered_StartTime)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 5) == 1)
	{
		value->DEF_Registered_daily_datexRegistered_Duration_qty = 1;
		if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->datexRegistered_Duration_qty), &consinfo_datexRegistered_Duration_qty)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Registered_daily(Registered_daily *value);
extern int ASN1_PER_Align_Data_Dec_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value);
int ASN1_PER_Align_Dec_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_Registered_daily(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Registered_daily(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
extern int ASN1_PER_UNAlign_Data_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
extern int ASN1_PER_UNAlign_Data_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
int ASN1_PER_UNAlign_Data_Enc_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexRegistered_UpdateDelay_qty = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_DaysOfWeek_cd = { ASN1_CONST64(8), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_StartDate = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_EndDate = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_StartTime = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_Duration_qty = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };

	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_Registered_daily_datexRegistered_UpdateDelay_qty == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_Registered_daily_datexRegistered_StartDate == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_Registered_daily_datexRegistered_EndDate == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_Registered_daily_datexRegistered_StartTime == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_Registered_daily_datexRegistered_Duration_qty == 1 ? 1 : 0) )) < 0) return ret;
	if (value->DEF_Registered_daily_datexRegistered_UpdateDelay_qty == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->datexRegistered_UpdateDelay_qty), &consinfo_datexRegistered_UpdateDelay_qty)) < 0) return ret;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_BITSTRING(workspace, &(value->datexRegistered_DaysOfWeek_cd), &consinfo_datexRegistered_DaysOfWeek_cd)) < 0) return ret;
	if (value->DEF_Registered_daily_datexRegistered_StartDate == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_IsoTime(workspace, value->datexRegistered_StartDate)) < 0) return ret;
	}
	if (value->DEF_Registered_daily_datexRegistered_EndDate == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_IsoTime(workspace, value->datexRegistered_EndDate)) < 0) return ret;
	}
	if (value->DEF_Registered_daily_datexRegistered_StartTime == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_IsoTime(workspace, value->datexRegistered_StartTime)) < 0) return ret;
	}
	if (value->DEF_Registered_daily_datexRegistered_Duration_qty == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->datexRegistered_Duration_qty), &consinfo_datexRegistered_Duration_qty)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Registered_daily(Registered_daily *value);
extern int ASN1_PER_UNAlign_Data_Enc_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value);
int ASN1_PER_UNAlign_Enc_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Registered_daily(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_Registered_daily(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
extern int ASN1_PER_UNAlign_Data_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
extern int ASN1_PER_UNAlign_Data_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
int ASN1_PER_UNAlign_Data_Dec_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexRegistered_UpdateDelay_qty = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_DaysOfWeek_cd = { ASN1_CONST64(8), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_StartDate = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_EndDate = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_StartTime = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexRegistered_Duration_qty = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };

	ASNUINT8 *_optvalue;
	if ((ret = ASN1_PER_Dec_Opt_Def_bit(workspace, 5, &_optvalue)) < 0) return ret;
	value->datexRegistered_StartDate = (IsoTime *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime));
	memset(value->datexRegistered_StartDate, 0, sizeof(IsoTime));
	value->datexRegistered_EndDate = (IsoTime *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime));
	memset(value->datexRegistered_EndDate, 0, sizeof(IsoTime));
	value->datexRegistered_StartTime = (IsoTime *)mpool_malloc(workspace->Pmemory, sizeof(IsoTime));
	memset(value->datexRegistered_StartTime, 0, sizeof(IsoTime));
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_Registered_daily_datexRegistered_UpdateDelay_qty = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->datexRegistered_UpdateDelay_qty), &consinfo_datexRegistered_UpdateDelay_qty)) < 0) return ret;
	}
	else
	{
		value->datexRegistered_UpdateDelay_qty = 0;
	}
	if ((ret = ASN1_PER_UNAlign_Dec_BITSTRING(workspace, &(value->datexRegistered_DaysOfWeek_cd), &consinfo_datexRegistered_DaysOfWeek_cd)) < 0) return ret;
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_Registered_daily_datexRegistered_StartDate = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_IsoTime(workspace, value->datexRegistered_StartDate)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_Registered_daily_datexRegistered_EndDate = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_IsoTime(workspace, value->datexRegistered_EndDate)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 4) == 1)
	{
		value->DEF_Registered_daily_datexRegistered_StartTime = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_IsoTime(workspace, value->datexRegistered_StartTime)) < 0) return ret;
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 5) == 1)
	{
		value->DEF_Registered_daily_datexRegistered_Duration_qty = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->datexRegistered_Duration_qty), &consinfo_datexRegistered_Duration_qty)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Registered_daily(Registered_daily *value);
extern int ASN1_PER_UNAlign_Data_Dec_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value);
int ASN1_PER_UNAlign_Dec_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_Registered_daily(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Registered_daily(value)) < 0) return ret;
	return ret;
}

/********************************************************
*Registered                                             *
********************************************************/
int ASN1_Print_Registered(Registered *value, int tab_value)
{
	int ret = 0;
	// CHOICE : t->tempIdentifier is Upper Letter
	ASN1_Print_CHOICE("Registered");
	if (value == NULL) return -1;
	switch (value->M) {
	case DEF_Registered_continuous:
		// Type Reference Registered_continuous
		if (Compare_Letter(tab_value, "continuous")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("continuous = ");
		}
		if ((ret = ASN1_Print_Registered_continuous((Registered_continuous *)value->elements.continuous, tab_value + 1)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_Registered_daily:
		// Type Reference Registered_daily
		if (Compare_Letter(tab_value, "daily")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("daily = ");
		}
		if ((ret = ASN1_Print_Registered_daily((Registered_daily *)value->elements.daily, tab_value + 1)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: return -1;
}
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_Registered_continuous(ASN1WorkSpace *workspace, Registered *value, Registered_continuous *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->elements.continuous = (Registered_continuous *)mpool_malloc(workspace->Pmemory, sizeof(Registered_continuous));
	memset(value->elements.continuous, 0, sizeof(Registered_continuous));
	value->M = DEF_Registered_continuous;
	memmove(value->elements.continuous, user_value, sizeof(Registered_continuous));
	return ret;
}
int ASN1_SET_Registered_daily(ASN1WorkSpace *workspace, Registered *value, Registered_daily *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->elements.daily = (Registered_daily *)mpool_malloc(workspace->Pmemory, sizeof(Registered_daily));
	memset(value->elements.daily, 0, sizeof(Registered_daily));
	value->M = DEF_Registered_daily;
	memmove(value->elements.daily, user_value, sizeof(Registered_daily));
	return ret;
}
int ASN1_GET_Registered_continuous(ASN1WorkSpace *workspace, Registered *value, Registered_continuous **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->M == DEF_Registered_continuous)
	{
		*user_value = value->elements.continuous;
	}
	else return -2;
	return ret;
}
int ASN1_GET_Registered_daily(ASN1WorkSpace *workspace, Registered *value, Registered_daily **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->M == DEF_Registered_daily)
	{
		*user_value = value->elements.daily;
	}
	else return -2;
	return ret;
}
extern int ASN1_CHECK_Registered_continuous(Registered_continuous *value);
extern int ASN1_CHECK_Registered_daily(Registered_daily *value);
int ASN1_CHECK_Registered(Registered *value)
{
	int ret = 0;

	unsigned char checkinfo_continuous[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_daily[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_Registered_continuous:
		if ((ret = ASN1_CHECK_Registered_continuous(value->elements.continuous)) < 0) return ret;
		break;
	case DEF_Registered_daily:
		if ((ret = ASN1_CHECK_Registered_daily(value->elements.daily)) < 0) return ret;
		break;
	default: break;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_Registered(ASN1WorkSpace *workspace, Registered *value, ASN1TagType tagFlag)
{
	int ret = 0;
	switch(value->M)
	{
	case DEF_Registered_continuous:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 0)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_Registered_continuous(workspace, value->elements.continuous, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
		break;
	case DEF_Registered_daily:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 1)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_Registered_daily(workspace, value->elements.daily, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
		break;
	}
	return ret;
}
extern int ASN1_CHECK_Registered(Registered *value);
extern int ASN1_BER_Data_Enc_Registered(ASN1WorkSpace *workspace, Registered *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_Registered(ASN1WorkSpace *workspace, Registered *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_Registered(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Registered(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_Registered(ASN1WorkSpace *workspace, Registered *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	value->M = 0;
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	switch(tag)
	{
	case ITS_ASN_CONT | ITS_ASN_CONS | 0:
		value->elements.continuous = (Registered_continuous *)mpool_malloc(workspace->Pmemory, sizeof(Registered_continuous));
		memset(value->elements.continuous, 0, sizeof(Registered_continuous));
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 0)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_Registered_continuous(workspace, value->elements.continuous, len, ASN1IMPL)) < 0) return ret;
		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->M = DEF_Registered_continuous;
		break;
	case ITS_ASN_CONT | ITS_ASN_CONS | 1:
		value->elements.daily = (Registered_daily *)mpool_malloc(workspace->Pmemory, sizeof(Registered_daily));
		memset(value->elements.daily, 0, sizeof(Registered_daily));
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 1)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_Registered_daily(workspace, value->elements.daily, len, ASN1IMPL)) < 0) return ret;
		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->M = DEF_Registered_daily;
		break;
	}
	return ret;
}
extern int ASN1_CHECK_Registered(Registered *value);
extern int ASN1_BER_Data_Dec_Registered(ASN1WorkSpace *workspace, Registered *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_Registered(ASN1WorkSpace *workspace, Registered *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Registered(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_Registered(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Enc_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value);
extern int ASN1_PER_Align_Data_Enc_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value);
int ASN1_PER_Align_Data_Enc_Registered(ASN1WorkSpace *workspace, Registered *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_continuous = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_daily = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT64 ui;
	ASNBOOL extbit = 1;
	switch(value->M)
	{
	case DEF_Registered_continuous: ui = 0; extbit = 0; break;
	case DEF_Registered_daily: ui = 1; extbit = 0; break;
	default: break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_Choice_ENUMERATED(workspace, ui, extbit, 0, 2)) < 0) return ret;
	switch(value->M)
	{
	case DEF_Registered_continuous:
		if ((ret = ASN1_PER_Align_Enc_Registered_continuous(workspace, value->elements.continuous)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_Registered_daily:
		if ((ret = ASN1_PER_Align_Enc_Registered_daily(workspace, value->elements.daily)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: break;
	}
	return ret;
}
extern int ASN1_CHECK_Registered(Registered *value);
extern int ASN1_PER_Align_Data_Enc_Registered(ASN1WorkSpace *workspace, Registered *value);
int ASN1_PER_Align_Enc_Registered(ASN1WorkSpace *workspace, Registered *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Registered(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_Registered(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Dec_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value);
extern int ASN1_PER_Align_Data_Dec_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value);
int ASN1_PER_Align_Data_Dec_Registered(ASN1WorkSpace *workspace, Registered *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_continuous = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_daily = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	if ((ret = ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 2)) < 0) return ret;

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_Registered_continuous;
			value->elements.continuous = (Registered_continuous *)mpool_malloc(workspace->Pmemory, sizeof(Registered_continuous));
			memset(value->elements.continuous, 0, sizeof(Registered_continuous));
			break;
		case 1: index = DEF_Registered_daily;
			value->elements.daily = (Registered_daily *)mpool_malloc(workspace->Pmemory, sizeof(Registered_daily));
			memset(value->elements.daily, 0, sizeof(Registered_daily));
			break;
		default: break;
		}
	}
	else
	{
		switch(ui)
		{
		default: break;
		}
	}
	if ((ret = ASN1_GetM(&value->M, index)) < 0) return ret;
	switch(index)
	{
	case DEF_Registered_continuous:
		if ((ret = ASN1_PER_Align_Dec_Registered_continuous(workspace, value->elements.continuous)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_Registered_daily:
		if ((ret = ASN1_PER_Align_Dec_Registered_daily(workspace, value->elements.daily)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, ALIGN); break;
	}
	return ret;
}
extern int ASN1_CHECK_Registered(Registered *value);
extern int ASN1_PER_Align_Data_Dec_Registered(ASN1WorkSpace *workspace, Registered *value);
int ASN1_PER_Align_Dec_Registered(ASN1WorkSpace *workspace, Registered *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_Registered(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Registered(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Enc_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value);
extern int ASN1_PER_UNAlign_Data_Enc_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value);
int ASN1_PER_UNAlign_Data_Enc_Registered(ASN1WorkSpace *workspace, Registered *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_continuous = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_daily = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT64 ui;
	ASNBOOL extbit = 1;
	switch(value->M)
	{
	case DEF_Registered_continuous: ui = 0; extbit = 0; break;
	case DEF_Registered_daily: ui = 1; extbit = 0; break;
	default: break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_Choice_ENUMERATED(workspace, ui, extbit, 0, 2)) < 0) return ret;
	switch(value->M)
	{
	case DEF_Registered_continuous:
		if ((ret = ASN1_PER_UNAlign_Enc_Registered_continuous(workspace, value->elements.continuous)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_Registered_daily:
		if ((ret = ASN1_PER_UNAlign_Enc_Registered_daily(workspace, value->elements.daily)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: break;
	}
	return ret;
}
extern int ASN1_CHECK_Registered(Registered *value);
extern int ASN1_PER_UNAlign_Data_Enc_Registered(ASN1WorkSpace *workspace, Registered *value);
int ASN1_PER_UNAlign_Enc_Registered(ASN1WorkSpace *workspace, Registered *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Registered(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_Registered(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Dec_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value);
extern int ASN1_PER_UNAlign_Data_Dec_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value);
int ASN1_PER_UNAlign_Data_Dec_Registered(ASN1WorkSpace *workspace, Registered *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_continuous = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_daily = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	if ((ret = ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 2)) < 0) return ret;

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_Registered_continuous;
			value->elements.continuous = (Registered_continuous *)mpool_malloc(workspace->Pmemory, sizeof(Registered_continuous));
			memset(value->elements.continuous, 0, sizeof(Registered_continuous));
			break;
		case 1: index = DEF_Registered_daily;
			value->elements.daily = (Registered_daily *)mpool_malloc(workspace->Pmemory, sizeof(Registered_daily));
			memset(value->elements.daily, 0, sizeof(Registered_daily));
			break;
		default: break;
		}
	}
	else
	{
		switch(ui)
		{
		default: break;
		}
	}
	if ((ret = ASN1_GetM(&value->M, index)) < 0) return ret;
	switch(index)
	{
	case DEF_Registered_continuous:
		if ((ret = ASN1_PER_UNAlign_Dec_Registered_continuous(workspace, value->elements.continuous)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_Registered_daily:
		if ((ret = ASN1_PER_UNAlign_Dec_Registered_daily(workspace, value->elements.daily)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
extern int ASN1_CHECK_Registered(Registered *value);
extern int ASN1_PER_UNAlign_Data_Dec_Registered(ASN1WorkSpace *workspace, Registered *value);
int ASN1_PER_UNAlign_Dec_Registered(ASN1WorkSpace *workspace, Registered *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_Registered(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Registered(value)) < 0) return ret;
	return ret;
}

/********************************************************
*SubscriptionMode                                       *
********************************************************/
int ASN1_Print_SubscriptionMode(SubscriptionMode *value, int tab_value)
{
	int ret = 0;
	// CHOICE : t->tempIdentifier is Upper Letter
	ASN1_Print_CHOICE("SubscriptionMode");
	if (value == NULL) return -1;
	switch (value->M) {
	case DEF_SubscriptionMode_single:
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_NULL("single", &value->elements.single)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_SubscriptionMode_event_driven:
		// Type Reference Registered
		if (Compare_Letter(tab_value, "event-driven")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("event-driven = ");
		}
		if ((ret = ASN1_Print_Registered((Registered *)value->elements.event_driven, tab_value + 1)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_SubscriptionMode_periodic:
		// Type Reference Registered
		if (Compare_Letter(tab_value, "periodic")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("periodic = ");
		}
		if ((ret = ASN1_Print_Registered((Registered *)value->elements.periodic, tab_value + 1)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: return -1;
}
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_SubscriptionMode_single(ASN1WorkSpace *workspace, SubscriptionMode *value, ASNUINT8 user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->M = DEF_SubscriptionMode_single;
	if ((ret = ASN1_SET_NULL(workspace, &value->elements.single, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_SubscriptionMode_event_driven(ASN1WorkSpace *workspace, SubscriptionMode *value, Registered *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->elements.event_driven = (Registered *)mpool_malloc(workspace->Pmemory, sizeof(Registered));
	memset(value->elements.event_driven, 0, sizeof(Registered));
	value->M = DEF_SubscriptionMode_event_driven;
	memmove(value->elements.event_driven, user_value, sizeof(Registered));
	return ret;
}
int ASN1_SET_SubscriptionMode_periodic(ASN1WorkSpace *workspace, SubscriptionMode *value, Registered *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->elements.periodic = (Registered *)mpool_malloc(workspace->Pmemory, sizeof(Registered));
	memset(value->elements.periodic, 0, sizeof(Registered));
	value->M = DEF_SubscriptionMode_periodic;
	memmove(value->elements.periodic, user_value, sizeof(Registered));
	return ret;
}
int ASN1_GET_SubscriptionMode_single(ASN1WorkSpace *workspace, SubscriptionMode *value, ASNUINT8 *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->M == DEF_SubscriptionMode_single)
	{
		if ((ret = ASN1_GET_NULL(workspace, &value->elements.single, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_SubscriptionMode_event_driven(ASN1WorkSpace *workspace, SubscriptionMode *value, Registered **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->M == DEF_SubscriptionMode_event_driven)
	{
		*user_value = value->elements.event_driven;
	}
	else return -2;
	return ret;
}
int ASN1_GET_SubscriptionMode_periodic(ASN1WorkSpace *workspace, SubscriptionMode *value, Registered **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->M == DEF_SubscriptionMode_periodic)
	{
		*user_value = value->elements.periodic;
	}
	else return -2;
	return ret;
}
extern int ASN1_CHECK_Registered(Registered *value);
extern int ASN1_CHECK_Registered(Registered *value);
int ASN1_CHECK_SubscriptionMode(SubscriptionMode *value)
{
	int ret = 0;

	unsigned char checkinfo_single[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_event_driven[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_periodic[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_SubscriptionMode_single:
		if ((ret = ASN1_CHECK_NULL(&value->elements.single, checkinfo_single)) < 0) return ret;
		break;
	case DEF_SubscriptionMode_event_driven:
		if ((ret = ASN1_CHECK_Registered(value->elements.event_driven)) < 0) return ret;
		break;
	case DEF_SubscriptionMode_periodic:
		if ((ret = ASN1_CHECK_Registered(value->elements.periodic)) < 0) return ret;
		break;
	default: break;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_Registered(ASN1WorkSpace *workspace, Registered *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_Registered(ASN1WorkSpace *workspace, Registered *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value, ASN1TagType tagFlag)
{
	int ret = 0;
	switch(value->M)
	{
	case DEF_SubscriptionMode_single:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_NULL(workspace, ASN1IMPL)) < 0) return ret;
		break;
	case DEF_SubscriptionMode_event_driven:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 1)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_Registered(workspace, value->elements.event_driven, ASN1EXPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
		break;
	case DEF_SubscriptionMode_periodic:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 2)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_Registered(workspace, value->elements.periodic, ASN1EXPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
		break;
	}
	return ret;
}
extern int ASN1_CHECK_SubscriptionMode(SubscriptionMode *value);
extern int ASN1_BER_Data_Enc_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_SubscriptionMode(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SubscriptionMode(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_Registered(ASN1WorkSpace *workspace, Registered *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_Registered(ASN1WorkSpace *workspace, Registered *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	value->M = 0;
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	switch(tag)
	{
	case ITS_ASN_CONT | ITS_ASN_PRIM | 0:
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_NULL(workspace, ASN1IMPL)) < 0) return ret;
		value->M = DEF_SubscriptionMode_single;
		break;
	case ITS_ASN_CONT | ITS_ASN_CONS | 1:
		value->elements.event_driven = (Registered *)mpool_malloc(workspace->Pmemory, sizeof(Registered));
		memset(value->elements.event_driven, 0, sizeof(Registered));
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 1)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_Registered(workspace, value->elements.event_driven, len, ASN1EXPL)) < 0) return ret;
		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->M = DEF_SubscriptionMode_event_driven;
		break;
	case ITS_ASN_CONT | ITS_ASN_CONS | 2:
		value->elements.periodic = (Registered *)mpool_malloc(workspace->Pmemory, sizeof(Registered));
		memset(value->elements.periodic, 0, sizeof(Registered));
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 2)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_Registered(workspace, value->elements.periodic, len, ASN1EXPL)) < 0) return ret;
		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->M = DEF_SubscriptionMode_periodic;
		break;
	}
	return ret;
}
extern int ASN1_CHECK_SubscriptionMode(SubscriptionMode *value);
extern int ASN1_BER_Data_Dec_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SubscriptionMode(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_SubscriptionMode(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Enc_Registered(ASN1WorkSpace *workspace, Registered *value);
extern int ASN1_PER_Align_Data_Enc_Registered(ASN1WorkSpace *workspace, Registered *value);
int ASN1_PER_Align_Data_Enc_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_single = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_event_driven = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_periodic = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT64 ui;
	ASNBOOL extbit = 1;
	switch(value->M)
	{
	case DEF_SubscriptionMode_single: ui = 0; extbit = 0; break;
	case DEF_SubscriptionMode_event_driven: ui = 1; extbit = 0; break;
	case DEF_SubscriptionMode_periodic: ui = 2; extbit = 0; break;
	default: break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_Choice_ENUMERATED(workspace, ui, extbit, 0, 3)) < 0) return ret;
	switch(value->M)
	{
	case DEF_SubscriptionMode_single:
		/* NULL NOT Encode Of PER ruler!! */
		return 0;
		if (ret != 0) return -1;
		break;
	case DEF_SubscriptionMode_event_driven:
		if ((ret = ASN1_PER_Align_Enc_Registered(workspace, value->elements.event_driven)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_SubscriptionMode_periodic:
		if ((ret = ASN1_PER_Align_Enc_Registered(workspace, value->elements.periodic)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: break;
	}
	return ret;
}
extern int ASN1_CHECK_SubscriptionMode(SubscriptionMode *value);
extern int ASN1_PER_Align_Data_Enc_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value);
int ASN1_PER_Align_Enc_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_SubscriptionMode(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_SubscriptionMode(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Dec_Registered(ASN1WorkSpace *workspace, Registered *value);
extern int ASN1_PER_Align_Data_Dec_Registered(ASN1WorkSpace *workspace, Registered *value);
int ASN1_PER_Align_Data_Dec_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_single = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_event_driven = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_periodic = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	if ((ret = ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 3)) < 0) return ret;

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_SubscriptionMode_single;
			break;
		case 1: index = DEF_SubscriptionMode_event_driven;
			value->elements.event_driven = (Registered *)mpool_malloc(workspace->Pmemory, sizeof(Registered));
			memset(value->elements.event_driven, 0, sizeof(Registered));
			break;
		case 2: index = DEF_SubscriptionMode_periodic;
			value->elements.periodic = (Registered *)mpool_malloc(workspace->Pmemory, sizeof(Registered));
			memset(value->elements.periodic, 0, sizeof(Registered));
			break;
		default: break;
		}
	}
	else
	{
		switch(ui)
		{
		default: break;
		}
	}
	if ((ret = ASN1_GetM(&value->M, index)) < 0) return ret;
	switch(index)
	{
	case DEF_SubscriptionMode_single:
		/* NULL NOT Decode Of PER ruler!! - PrintLineDecode_Per */
		return 0;
		if (ret != 0) return -1;
		break;
	case DEF_SubscriptionMode_event_driven:
		if ((ret = ASN1_PER_Align_Dec_Registered(workspace, value->elements.event_driven)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_SubscriptionMode_periodic:
		if ((ret = ASN1_PER_Align_Dec_Registered(workspace, value->elements.periodic)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, ALIGN); break;
	}
	return ret;
}
extern int ASN1_CHECK_SubscriptionMode(SubscriptionMode *value);
extern int ASN1_PER_Align_Data_Dec_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value);
int ASN1_PER_Align_Dec_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_SubscriptionMode(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_SubscriptionMode(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Enc_Registered(ASN1WorkSpace *workspace, Registered *value);
extern int ASN1_PER_UNAlign_Data_Enc_Registered(ASN1WorkSpace *workspace, Registered *value);
int ASN1_PER_UNAlign_Data_Enc_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_single = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_event_driven = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_periodic = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT64 ui;
	ASNBOOL extbit = 1;
	switch(value->M)
	{
	case DEF_SubscriptionMode_single: ui = 0; extbit = 0; break;
	case DEF_SubscriptionMode_event_driven: ui = 1; extbit = 0; break;
	case DEF_SubscriptionMode_periodic: ui = 2; extbit = 0; break;
	default: break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_Choice_ENUMERATED(workspace, ui, extbit, 0, 3)) < 0) return ret;
	switch(value->M)
	{
	case DEF_SubscriptionMode_single:
		/* NULL NOT Encode Of PER ruler!! */
		return 0;
		if (ret != 0) return -1;
		break;
	case DEF_SubscriptionMode_event_driven:
		if ((ret = ASN1_PER_UNAlign_Enc_Registered(workspace, value->elements.event_driven)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_SubscriptionMode_periodic:
		if ((ret = ASN1_PER_UNAlign_Enc_Registered(workspace, value->elements.periodic)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: break;
	}
	return ret;
}
extern int ASN1_CHECK_SubscriptionMode(SubscriptionMode *value);
extern int ASN1_PER_UNAlign_Data_Enc_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value);
int ASN1_PER_UNAlign_Enc_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_SubscriptionMode(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_SubscriptionMode(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Dec_Registered(ASN1WorkSpace *workspace, Registered *value);
extern int ASN1_PER_UNAlign_Data_Dec_Registered(ASN1WorkSpace *workspace, Registered *value);
int ASN1_PER_UNAlign_Data_Dec_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_single = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_event_driven = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_periodic = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	if ((ret = ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 3)) < 0) return ret;

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_SubscriptionMode_single;
			break;
		case 1: index = DEF_SubscriptionMode_event_driven;
			value->elements.event_driven = (Registered *)mpool_malloc(workspace->Pmemory, sizeof(Registered));
			memset(value->elements.event_driven, 0, sizeof(Registered));
			break;
		case 2: index = DEF_SubscriptionMode_periodic;
			value->elements.periodic = (Registered *)mpool_malloc(workspace->Pmemory, sizeof(Registered));
			memset(value->elements.periodic, 0, sizeof(Registered));
			break;
		default: break;
		}
	}
	else
	{
		switch(ui)
		{
		default: break;
		}
	}
	if ((ret = ASN1_GetM(&value->M, index)) < 0) return ret;
	switch(index)
	{
	case DEF_SubscriptionMode_single:
		/* NULL NOT Decode Of PER ruler!! - PrintLineDecode_Per */
		return 0;
		if (ret != 0) return -1;
		break;
	case DEF_SubscriptionMode_event_driven:
		if ((ret = ASN1_PER_UNAlign_Dec_Registered(workspace, value->elements.event_driven)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_SubscriptionMode_periodic:
		if ((ret = ASN1_PER_UNAlign_Dec_Registered(workspace, value->elements.periodic)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
extern int ASN1_CHECK_SubscriptionMode(SubscriptionMode *value);
extern int ASN1_PER_UNAlign_Data_Dec_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value);
int ASN1_PER_UNAlign_Dec_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_SubscriptionMode(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_SubscriptionMode(value)) < 0) return ret;
	return ret;
}

/********************************************************
*SubscriptionData_datexSubscribe-PublishFormat-cd       *
********************************************************/
int ASN1_Print_SubscriptionData_datexSubscribe_PublishFormat_cd(SubscriptionData_datexSubscribe_PublishFormat_cd *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch(*value)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("SubscriptionData_datexSubscribe-PublishFormat-cd", "other", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("SubscriptionData_datexSubscribe-PublishFormat-cd", "ftp", 1)) < 0) return ret; break;
	case 2: if ((ret = ASN1_Print_ENUMERATED("SubscriptionData_datexSubscribe-PublishFormat-cd", "tftp", 2)) < 0) return ret; break;
	case 3: if ((ret = ASN1_Print_ENUMERATED("SubscriptionData_datexSubscribe-PublishFormat-cd", "dataPacket", 3)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	return ret;
}
int ASN1_CHECK_SubscriptionData_datexSubscribe_PublishFormat_cd(SubscriptionData_datexSubscribe_PublishFormat_cd *value)
{
	unsigned char checkinfo_SubscriptionData_datexSubscribe_PublishFormat_cd[] = {0x04,0x00,0x01,0x02,0x03,0x00 };
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32 *)value, checkinfo_SubscriptionData_datexSubscribe_PublishFormat_cd)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_SubscriptionData_datexSubscribe_PublishFormat_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_PublishFormat_cd *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_SubscriptionData_datexSubscribe_PublishFormat_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_PublishFormat_cd *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_SubscriptionData_datexSubscribe_PublishFormat_cd(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SubscriptionData_datexSubscribe_PublishFormat_cd(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_SubscriptionData_datexSubscribe_PublishFormat_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_PublishFormat_cd *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_SubscriptionData_datexSubscribe_PublishFormat_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_PublishFormat_cd *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SubscriptionData_datexSubscribe_PublishFormat_cd(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_SubscriptionData_datexSubscribe_PublishFormat_cd(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_SubscriptionData_datexSubscribe_PublishFormat_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_PublishFormat_cd *value)
{
	struct Asn1ConsInfo consinfo_SubscriptionData_datexSubscribe_PublishFormat_cd = { ASN1_CONST64(0), ASN1_CONST64(3), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_SubscriptionData_datexSubscribe_PublishFormat_cd;
	switch(*value)
	{
	case SubscriptionData_datexSubscribe_PublishFormat_cd_other: ui_SubscriptionData_datexSubscribe_PublishFormat_cd = 0; consinfo_SubscriptionData_datexSubscribe_PublishFormat_cd.enumextbit = 0; break;
	case SubscriptionData_datexSubscribe_PublishFormat_cd_ftp: ui_SubscriptionData_datexSubscribe_PublishFormat_cd = 1; consinfo_SubscriptionData_datexSubscribe_PublishFormat_cd.enumextbit = 0; break;
	case SubscriptionData_datexSubscribe_PublishFormat_cd_tftp: ui_SubscriptionData_datexSubscribe_PublishFormat_cd = 2; consinfo_SubscriptionData_datexSubscribe_PublishFormat_cd.enumextbit = 0; break;
	case SubscriptionData_datexSubscribe_PublishFormat_cd_dataPacket: ui_SubscriptionData_datexSubscribe_PublishFormat_cd = 3; consinfo_SubscriptionData_datexSubscribe_PublishFormat_cd.enumextbit = 0; break;
	default: ui_SubscriptionData_datexSubscribe_PublishFormat_cd = *value; consinfo_SubscriptionData_datexSubscribe_PublishFormat_cd.enumextbit = 1; break;
	}
	if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_SubscriptionData_datexSubscribe_PublishFormat_cd, &consinfo_SubscriptionData_datexSubscribe_PublishFormat_cd)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Enc_SubscriptionData_datexSubscribe_PublishFormat_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_PublishFormat_cd *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_SubscriptionData_datexSubscribe_PublishFormat_cd(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_SubscriptionData_datexSubscribe_PublishFormat_cd(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_SubscriptionData_datexSubscribe_PublishFormat_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_PublishFormat_cd *value)
{
	struct Asn1ConsInfo consinfo_SubscriptionData_datexSubscribe_PublishFormat_cd = { ASN1_CONST64(0), ASN1_CONST64(3), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_SubscriptionData_datexSubscribe_PublishFormat_cd;
	if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_SubscriptionData_datexSubscribe_PublishFormat_cd, &consinfo_SubscriptionData_datexSubscribe_PublishFormat_cd)) < 0) return ret;
	if (consinfo_SubscriptionData_datexSubscribe_PublishFormat_cd.enumextbit == 0)
	{
		switch(ui_SubscriptionData_datexSubscribe_PublishFormat_cd)
		{
		case 0: *value = SubscriptionData_datexSubscribe_PublishFormat_cd_other; break;
		case 1: *value = SubscriptionData_datexSubscribe_PublishFormat_cd_ftp; break;
		case 2: *value = SubscriptionData_datexSubscribe_PublishFormat_cd_tftp; break;
		case 3: *value = SubscriptionData_datexSubscribe_PublishFormat_cd_dataPacket; break;
		default: break;
		}
	}
	else
	{
		switch(ui_SubscriptionData_datexSubscribe_PublishFormat_cd)
		{
		default: *value = ui_SubscriptionData_datexSubscribe_PublishFormat_cd; break;
		}
	}
	return ret;
}
int ASN1_PER_Align_Dec_SubscriptionData_datexSubscribe_PublishFormat_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_PublishFormat_cd *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_SubscriptionData_datexSubscribe_PublishFormat_cd(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_SubscriptionData_datexSubscribe_PublishFormat_cd(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_SubscriptionData_datexSubscribe_PublishFormat_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_PublishFormat_cd *value)
{
	struct Asn1ConsInfo consinfo_SubscriptionData_datexSubscribe_PublishFormat_cd = { ASN1_CONST64(0), ASN1_CONST64(3), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_SubscriptionData_datexSubscribe_PublishFormat_cd;
	switch(*value)
	{
	case SubscriptionData_datexSubscribe_PublishFormat_cd_other: ui_SubscriptionData_datexSubscribe_PublishFormat_cd = 0; consinfo_SubscriptionData_datexSubscribe_PublishFormat_cd.enumextbit = 0; break;
	case SubscriptionData_datexSubscribe_PublishFormat_cd_ftp: ui_SubscriptionData_datexSubscribe_PublishFormat_cd = 1; consinfo_SubscriptionData_datexSubscribe_PublishFormat_cd.enumextbit = 0; break;
	case SubscriptionData_datexSubscribe_PublishFormat_cd_tftp: ui_SubscriptionData_datexSubscribe_PublishFormat_cd = 2; consinfo_SubscriptionData_datexSubscribe_PublishFormat_cd.enumextbit = 0; break;
	case SubscriptionData_datexSubscribe_PublishFormat_cd_dataPacket: ui_SubscriptionData_datexSubscribe_PublishFormat_cd = 3; consinfo_SubscriptionData_datexSubscribe_PublishFormat_cd.enumextbit = 0; break;
	default: ui_SubscriptionData_datexSubscribe_PublishFormat_cd = *value; consinfo_SubscriptionData_datexSubscribe_PublishFormat_cd.enumextbit = 1; break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_SubscriptionData_datexSubscribe_PublishFormat_cd, &consinfo_SubscriptionData_datexSubscribe_PublishFormat_cd)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Enc_SubscriptionData_datexSubscribe_PublishFormat_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_PublishFormat_cd *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_SubscriptionData_datexSubscribe_PublishFormat_cd(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_SubscriptionData_datexSubscribe_PublishFormat_cd(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_SubscriptionData_datexSubscribe_PublishFormat_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_PublishFormat_cd *value)
{
	struct Asn1ConsInfo consinfo_SubscriptionData_datexSubscribe_PublishFormat_cd = { ASN1_CONST64(0), ASN1_CONST64(3), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_SubscriptionData_datexSubscribe_PublishFormat_cd;
	if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_SubscriptionData_datexSubscribe_PublishFormat_cd, &consinfo_SubscriptionData_datexSubscribe_PublishFormat_cd)) < 0) return ret;
	if (consinfo_SubscriptionData_datexSubscribe_PublishFormat_cd.enumextbit == 0)
	{
		switch(ui_SubscriptionData_datexSubscribe_PublishFormat_cd)
		{
		case 0: *value = SubscriptionData_datexSubscribe_PublishFormat_cd_other; break;
		case 1: *value = SubscriptionData_datexSubscribe_PublishFormat_cd_ftp; break;
		case 2: *value = SubscriptionData_datexSubscribe_PublishFormat_cd_tftp; break;
		case 3: *value = SubscriptionData_datexSubscribe_PublishFormat_cd_dataPacket; break;
		default: break;
		}
	}
	else
	{
		switch(ui_SubscriptionData_datexSubscribe_PublishFormat_cd)
		{
		default: *value = ui_SubscriptionData_datexSubscribe_PublishFormat_cd; break;
		}
	}
	return ret;
}
int ASN1_PER_UNAlign_Dec_SubscriptionData_datexSubscribe_PublishFormat_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_PublishFormat_cd *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_SubscriptionData_datexSubscribe_PublishFormat_cd(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_SubscriptionData_datexSubscribe_PublishFormat_cd(value)) < 0) return ret;
	return ret;
}

/********************************************************
*EndApplicationMessage                                  *
********************************************************/
int ASN1_Print_EndApplicationMessage(EndApplicationMessage *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("EndApplicationMessage");
	// Type Default
	// Type is Referenced
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_OBJECTIDENTIFIER("ISO14827_MESSAGE_id", &(value->endApplication_Message_id))) < 0) return ret;
	// Type ANY
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_OpenType("ISO14827_MESSAGE_MessageBody", &(value->endApplication_Message_msg), tab_value + 1)) < 0) return ret;
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_EndApplicationMessage_endApplication_Message_id(ASN1WorkSpace *workspace, EndApplicationMessage *value, ASNUINT32 *user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_OBJECTIDENTIFIER(workspace, &value->endApplication_Message_id, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_EndApplicationMessage_endApplication_Message_msg(ASN1WorkSpace *workspace, EndApplicationMessage *value, ASNUINT8 *user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_OpenType(workspace, &value->endApplication_Message_msg, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_EndApplicationMessage_endApplication_Message_id(ASN1WorkSpace *workspace, EndApplicationMessage *value, ASNUINT32 *user_value, ASNUINT32 *user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_OBJECTIDENTIFIER(workspace, &value->endApplication_Message_id, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_EndApplicationMessage_endApplication_Message_msg(ASN1WorkSpace *workspace, EndApplicationMessage *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_OpenType(workspace, &value->endApplication_Message_msg, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_EndApplicationMessage(EndApplicationMessage *value)
{
	int ret = 0;

	unsigned char checkinfo_endApplication_Message_id[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_endApplication_Message_msg[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_OBJECTIDENTIFIER(&(value->endApplication_Message_id), checkinfo_endApplication_Message_id)) < 0) return ret;
	if ((ret = ASN1_CHECK_OpenType(&(value->endApplication_Message_msg), checkinfo_endApplication_Message_msg)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_OBJECTIDENTIFIER(workspace, &(value->endApplication_Message_id), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_OpenType(workspace, &(value->endApplication_Message_msg), ASN1EXPL)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_EndApplicationMessage(EndApplicationMessage *value);
extern int ASN1_BER_Data_Enc_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_EndApplicationMessage(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_EndApplicationMessage(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8 *_cpointer;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_OBJECTIDENTIFIER(workspace, &value->endApplication_Message_id, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_OpenType(workspace, &value->endApplication_Message_msg, len, ASN1EXPL)) < 0) return ret;
	if (IfFixedLength(len) == -1)
	{
		if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
	}
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_EndApplicationMessage(EndApplicationMessage *value);
extern int ASN1_BER_Data_Dec_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_EndApplicationMessage(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_EndApplicationMessage(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_endApplication_Message_id = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_endApplication_Message_msg = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_Align_Enc_OBJECTIDENTIFIER(workspace, &(value->endApplication_Message_id), &consinfo_endApplication_Message_id)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_OpenType(workspace, &(value->endApplication_Message_msg))) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_EndApplicationMessage(EndApplicationMessage *value);
extern int ASN1_PER_Align_Data_Enc_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value);
int ASN1_PER_Align_Enc_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_EndApplicationMessage(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_EndApplicationMessage(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_endApplication_Message_id = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_endApplication_Message_msg = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_Align_Dec_OBJECTIDENTIFIER(workspace, &(value->endApplication_Message_id), &consinfo_endApplication_Message_id)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_OpenType(workspace, &(value->endApplication_Message_msg))) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_EndApplicationMessage(EndApplicationMessage *value);
extern int ASN1_PER_Align_Data_Dec_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value);
int ASN1_PER_Align_Dec_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_EndApplicationMessage(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_EndApplicationMessage(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_endApplication_Message_id = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_endApplication_Message_msg = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_UNAlign_Enc_OBJECTIDENTIFIER(workspace, &(value->endApplication_Message_id), &consinfo_endApplication_Message_id)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_OpenType(workspace, &(value->endApplication_Message_msg))) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_EndApplicationMessage(EndApplicationMessage *value);
extern int ASN1_PER_UNAlign_Data_Enc_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value);
int ASN1_PER_UNAlign_Enc_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_EndApplicationMessage(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_EndApplicationMessage(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_endApplication_Message_id = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_endApplication_Message_msg = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_UNAlign_Dec_OBJECTIDENTIFIER(workspace, &(value->endApplication_Message_id), &consinfo_endApplication_Message_id)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_OpenType(workspace, &(value->endApplication_Message_msg))) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_EndApplicationMessage(EndApplicationMessage *value);
extern int ASN1_PER_UNAlign_Data_Dec_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value);
int ASN1_PER_UNAlign_Dec_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_EndApplicationMessage(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_EndApplicationMessage(value)) < 0) return ret;
	return ret;
}

/********************************************************
*SubscriptionData                                       *
********************************************************/
int ASN1_Print_SubscriptionData(SubscriptionData *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("SubscriptionData");
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_BOOLEAN("datexSubscribe_Persistent_bool", &(value->datexSubscribe_Persistent_bool))) < 0) return ret;
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch(value->datexSubscribe_Status_cd)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("SubscriptionData_datexSubscribe-Status-cd", "new", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("SubscriptionData_datexSubscribe-Status-cd", "update", 1)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	// Type Reference SubscriptionMode
	if (Compare_Letter(tab_value, "datexSubscribe-Mode")) {
		ASN_Print_TAB(tab_value + 1);
		asn_printf("datexSubscribe-Mode = ");
	}
	if ((ret = ASN1_Print_SubscriptionMode((SubscriptionMode *)value->datexSubscribe_Mode, tab_value + 1)) < 0) return ret;
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch(value->datexSubscribe_PublishFormat_cd)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("SubscriptionData_datexSubscribe-PublishFormat-cd", "other", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("SubscriptionData_datexSubscribe-PublishFormat-cd", "ftp", 1)) < 0) return ret; break;
	case 2: if ((ret = ASN1_Print_ENUMERATED("SubscriptionData_datexSubscribe-PublishFormat-cd", "tftp", 2)) < 0) return ret; break;
	case 3: if ((ret = ASN1_Print_ENUMERATED("SubscriptionData_datexSubscribe-PublishFormat-cd", "dataPacket", 3)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("datexSubscription_Priority_nbr", &(value->datexSubscription_Priority_nbr))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_BOOLEAN("datexSubscribe_Guarantee_bool", &(value->datexSubscribe_Guarantee_bool))) < 0) return ret;
	// Type Reference EndApplicationMessage
	if (Compare_Letter(tab_value, "datexSubscribe-Pdu")) {
		ASN_Print_TAB(tab_value + 1);
		asn_printf("datexSubscribe-Pdu = ");
	}
	if ((ret = ASN1_Print_EndApplicationMessage((EndApplicationMessage *)value->datexSubscribe_Pdu, tab_value + 1)) < 0) return ret;
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_SubscriptionData_datexSubscribe_Persistent_bool(ASN1WorkSpace *workspace, SubscriptionData *value, BOOLEAN user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_BOOLEAN(workspace, &value->datexSubscribe_Persistent_bool, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_SubscriptionData_datexSubscribe_Status_cd(ASN1WorkSpace *workspace, SubscriptionData *value, ENUMERATED user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_ENUMERATED(workspace, (ASNINT32*)&value->datexSubscribe_Status_cd, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_SubscriptionData_datexSubscribe_Mode(ASN1WorkSpace *workspace, SubscriptionData *value, SubscriptionMode *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->datexSubscribe_Mode = (SubscriptionMode *)mpool_malloc(workspace->Pmemory, sizeof(SubscriptionMode));
	memset(value->datexSubscribe_Mode, 0, sizeof(SubscriptionMode));
	memmove(value->datexSubscribe_Mode, user_value, sizeof(SubscriptionMode));
	return ret;
}
int ASN1_SET_SubscriptionData_datexSubscribe_PublishFormat_cd(ASN1WorkSpace *workspace, SubscriptionData *value, ENUMERATED user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_ENUMERATED(workspace, (ASNINT32*)&value->datexSubscribe_PublishFormat_cd, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_SubscriptionData_datexSubscription_Priority_nbr(ASN1WorkSpace *workspace, SubscriptionData *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->datexSubscription_Priority_nbr, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_SubscriptionData_datexSubscribe_Guarantee_bool(ASN1WorkSpace *workspace, SubscriptionData *value, BOOLEAN user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_BOOLEAN(workspace, &value->datexSubscribe_Guarantee_bool, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_SubscriptionData_datexSubscribe_Pdu(ASN1WorkSpace *workspace, SubscriptionData *value, EndApplicationMessage *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->datexSubscribe_Pdu = (EndApplicationMessage *)mpool_malloc(workspace->Pmemory, sizeof(EndApplicationMessage));
	memset(value->datexSubscribe_Pdu, 0, sizeof(EndApplicationMessage));
	memmove(value->datexSubscribe_Pdu, user_value, sizeof(EndApplicationMessage));
	return ret;
}
int ASN1_GET_SubscriptionData_datexSubscribe_Persistent_bool(ASN1WorkSpace *workspace, SubscriptionData *value, BOOLEAN *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_BOOLEAN(workspace, &value->datexSubscribe_Persistent_bool, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_SubscriptionData_datexSubscribe_Status_cd(ASN1WorkSpace *workspace, SubscriptionData *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->datexSubscribe_Status_cd, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_SubscriptionData_datexSubscribe_Mode(ASN1WorkSpace *workspace, SubscriptionData *value, SubscriptionMode **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = value->datexSubscribe_Mode;
	return ret;
}
int ASN1_GET_SubscriptionData_datexSubscribe_PublishFormat_cd(ASN1WorkSpace *workspace, SubscriptionData *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->datexSubscribe_PublishFormat_cd, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_SubscriptionData_datexSubscription_Priority_nbr(ASN1WorkSpace *workspace, SubscriptionData *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->datexSubscription_Priority_nbr, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_SubscriptionData_datexSubscribe_Guarantee_bool(ASN1WorkSpace *workspace, SubscriptionData *value, BOOLEAN *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_BOOLEAN(workspace, &value->datexSubscribe_Guarantee_bool, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_SubscriptionData_datexSubscribe_Pdu(ASN1WorkSpace *workspace, SubscriptionData *value, EndApplicationMessage **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = value->datexSubscribe_Pdu;
	return ret;
}
extern int ASN1_CHECK_SubscriptionMode(SubscriptionMode *value);
extern int ASN1_CHECK_EndApplicationMessage(EndApplicationMessage *value);
int ASN1_CHECK_SubscriptionData(SubscriptionData *value)
{
	int ret = 0;

	unsigned char checkinfo_datexSubscribe_Persistent_bool[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datexSubscribe_Status_cd[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datexSubscribe_Mode[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datexSubscribe_PublishFormat_cd[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datexSubscription_Priority_nbr[] = { 
		0x02,0x01,0x0A,0x00
	};
	unsigned char checkinfo_datexSubscribe_Guarantee_bool[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datexSubscribe_Pdu[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_BOOLEAN(&(value->datexSubscribe_Persistent_bool), checkinfo_datexSubscribe_Persistent_bool)) < 0) return ret;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->datexSubscribe_Status_cd), checkinfo_datexSubscribe_Status_cd)) < 0) return ret;
	if ((ret = ASN1_CHECK_SubscriptionMode(value->datexSubscribe_Mode)) < 0) return ret;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->datexSubscribe_PublishFormat_cd), checkinfo_datexSubscribe_PublishFormat_cd)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->datexSubscription_Priority_nbr), checkinfo_datexSubscription_Priority_nbr)) < 0) return ret;
	if ((ret = ASN1_CHECK_BOOLEAN(&(value->datexSubscribe_Guarantee_bool), checkinfo_datexSubscribe_Guarantee_bool)) < 0) return ret;
	if ((ret = ASN1_CHECK_EndApplicationMessage(value->datexSubscribe_Pdu)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Enc_SubscriptionData_datexSubscribe_Status_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_Status_cd *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_SubscriptionData_datexSubscribe_PublishFormat_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_PublishFormat_cd *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_BOOLEAN(workspace, &(value->datexSubscribe_Persistent_bool), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SubscriptionData_datexSubscribe_Status_cd(workspace, &(value->datexSubscribe_Status_cd), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 2)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SubscriptionMode(workspace, value->datexSubscribe_Mode, ASN1EXPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SubscriptionData_datexSubscribe_PublishFormat_cd(workspace, &(value->datexSubscribe_PublishFormat_cd), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->datexSubscription_Priority_nbr), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_BOOLEAN(workspace, &(value->datexSubscribe_Guarantee_bool), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 6)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_EndApplicationMessage(workspace, value->datexSubscribe_Pdu, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_SubscriptionData(SubscriptionData *value);
extern int ASN1_BER_Data_Enc_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_SubscriptionData(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SubscriptionData(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_SubscriptionData_datexSubscribe_Status_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_Status_cd *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_SubscriptionData_datexSubscribe_PublishFormat_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_PublishFormat_cd *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8 *_cpointer;
	value->datexSubscribe_Mode = (SubscriptionMode *)mpool_malloc(workspace->Pmemory, sizeof(SubscriptionMode));
	memset(value->datexSubscribe_Mode, 0, sizeof(SubscriptionMode));
	value->datexSubscribe_Pdu = (EndApplicationMessage *)mpool_malloc(workspace->Pmemory, sizeof(EndApplicationMessage));
	memset(value->datexSubscribe_Pdu, 0, sizeof(EndApplicationMessage));
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_BOOLEAN(workspace, &value->datexSubscribe_Persistent_bool, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SubscriptionData_datexSubscribe_Status_cd(workspace, &value->datexSubscribe_Status_cd, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 2)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SubscriptionMode(workspace, value->datexSubscribe_Mode, len, ASN1EXPL)) < 0) return ret;
	if (IfFixedLength(len) == -1)
	{
		if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
	}
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SubscriptionData_datexSubscribe_PublishFormat_cd(workspace, &value->datexSubscribe_PublishFormat_cd, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->datexSubscription_Priority_nbr, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 5)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_BOOLEAN(workspace, &value->datexSubscribe_Guarantee_bool, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 6)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_EndApplicationMessage(workspace, value->datexSubscribe_Pdu, len, ASN1IMPL)) < 0) return ret;
	if (IfFixedLength(len) == -1)
	{
		if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
	}
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_SubscriptionData(SubscriptionData *value);
extern int ASN1_BER_Data_Dec_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SubscriptionData(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_SubscriptionData(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Enc_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value);
extern int ASN1_PER_Align_Data_Enc_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value);
int ASN1_PER_Align_Data_Enc_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value)
{
	int ret = 0;
	ASNINT32 ui_datexSubscribe_Status_cd;
	ASNINT32 ui_datexSubscribe_PublishFormat_cd;
	struct Asn1ConsInfo consinfo_datexSubscribe_Persistent_bool = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_Status_cd = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_Mode = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_PublishFormat_cd = { ASN1_CONST64(0), ASN1_CONST64(3), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscription_Priority_nbr = { ASN1_CONST64(1), ASN1_CONST64(10), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_Guarantee_bool = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_Pdu = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_Align_Enc_BOOLEAN(workspace, &(value->datexSubscribe_Persistent_bool), &consinfo_datexSubscribe_Persistent_bool)) < 0) return ret;
	switch(value->datexSubscribe_Status_cd)
	{
	case SubscriptionData_datexSubscribe_Status_cd_new: ui_datexSubscribe_Status_cd = 0; consinfo_datexSubscribe_Status_cd.enumextbit = 0; break;
	case SubscriptionData_datexSubscribe_Status_cd_update: ui_datexSubscribe_Status_cd = 1; consinfo_datexSubscribe_Status_cd.enumextbit = 0; break;
	default: ui_datexSubscribe_Status_cd = value->datexSubscribe_Status_cd; consinfo_datexSubscribe_Status_cd.enumextbit = 0;break;
	}
	if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_datexSubscribe_Status_cd, &consinfo_datexSubscribe_Status_cd)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_SubscriptionMode(workspace, value->datexSubscribe_Mode)) < 0) return ret;
	switch(value->datexSubscribe_PublishFormat_cd)
	{
	case SubscriptionData_datexSubscribe_PublishFormat_cd_other: ui_datexSubscribe_PublishFormat_cd = 0; consinfo_datexSubscribe_PublishFormat_cd.enumextbit = 0; break;
	case SubscriptionData_datexSubscribe_PublishFormat_cd_ftp: ui_datexSubscribe_PublishFormat_cd = 1; consinfo_datexSubscribe_PublishFormat_cd.enumextbit = 0; break;
	case SubscriptionData_datexSubscribe_PublishFormat_cd_tftp: ui_datexSubscribe_PublishFormat_cd = 2; consinfo_datexSubscribe_PublishFormat_cd.enumextbit = 0; break;
	case SubscriptionData_datexSubscribe_PublishFormat_cd_dataPacket: ui_datexSubscribe_PublishFormat_cd = 3; consinfo_datexSubscribe_PublishFormat_cd.enumextbit = 0; break;
	default: ui_datexSubscribe_PublishFormat_cd = value->datexSubscribe_PublishFormat_cd; consinfo_datexSubscribe_PublishFormat_cd.enumextbit = 1;break;
	}
	if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_datexSubscribe_PublishFormat_cd, &consinfo_datexSubscribe_PublishFormat_cd)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->datexSubscription_Priority_nbr), &consinfo_datexSubscription_Priority_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_BOOLEAN(workspace, &(value->datexSubscribe_Guarantee_bool), &consinfo_datexSubscribe_Guarantee_bool)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_EndApplicationMessage(workspace, value->datexSubscribe_Pdu)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_SubscriptionData(SubscriptionData *value);
extern int ASN1_PER_Align_Data_Enc_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value);
int ASN1_PER_Align_Enc_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_SubscriptionData(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_SubscriptionData(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Dec_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value);
extern int ASN1_PER_Align_Data_Dec_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value);
int ASN1_PER_Align_Data_Dec_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value)
{
	int ret = 0;
	ASNINT32 ui_datexSubscribe_Status_cd;
	ASNINT32 ui_datexSubscribe_PublishFormat_cd;
	struct Asn1ConsInfo consinfo_datexSubscribe_Persistent_bool = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_Status_cd = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_Mode = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_PublishFormat_cd = { ASN1_CONST64(0), ASN1_CONST64(3), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscription_Priority_nbr = { ASN1_CONST64(1), ASN1_CONST64(10), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_Guarantee_bool = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_Pdu = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	value->datexSubscribe_Mode = (SubscriptionMode *)mpool_malloc(workspace->Pmemory, sizeof(SubscriptionMode));
	memset(value->datexSubscribe_Mode, 0, sizeof(SubscriptionMode));
	value->datexSubscribe_Pdu = (EndApplicationMessage *)mpool_malloc(workspace->Pmemory, sizeof(EndApplicationMessage));
	memset(value->datexSubscribe_Pdu, 0, sizeof(EndApplicationMessage));
	if ((ret = ASN1_PER_Align_Dec_BOOLEAN(workspace, &(value->datexSubscribe_Persistent_bool), &consinfo_datexSubscribe_Persistent_bool)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_datexSubscribe_Status_cd, &consinfo_datexSubscribe_Status_cd)) < 0) return ret;
	if (consinfo_datexSubscribe_Status_cd.enumextbit == 0)
	{
		switch(ui_datexSubscribe_Status_cd)
		{
		case 0: value->datexSubscribe_Status_cd = SubscriptionData_datexSubscribe_Status_cd_new; break;
		case 1: value->datexSubscribe_Status_cd = SubscriptionData_datexSubscribe_Status_cd_update; break;
		default: value->datexSubscribe_Status_cd = ui_datexSubscribe_Status_cd; break;
		}
	}
	if ((ret = ASN1_PER_Align_Dec_SubscriptionMode(workspace, value->datexSubscribe_Mode)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_datexSubscribe_PublishFormat_cd, &consinfo_datexSubscribe_PublishFormat_cd)) < 0) return ret;
	if (consinfo_datexSubscribe_PublishFormat_cd.enumextbit == 0)
	{
		switch(ui_datexSubscribe_PublishFormat_cd)
		{
		case 0: value->datexSubscribe_PublishFormat_cd = SubscriptionData_datexSubscribe_PublishFormat_cd_other; break;
		case 1: value->datexSubscribe_PublishFormat_cd = SubscriptionData_datexSubscribe_PublishFormat_cd_ftp; break;
		case 2: value->datexSubscribe_PublishFormat_cd = SubscriptionData_datexSubscribe_PublishFormat_cd_tftp; break;
		case 3: value->datexSubscribe_PublishFormat_cd = SubscriptionData_datexSubscribe_PublishFormat_cd_dataPacket; break;
		default: break;
		}
	}
	else
	{
		switch(ui_datexSubscribe_PublishFormat_cd)
		{
		default: value->datexSubscribe_PublishFormat_cd = ui_datexSubscribe_PublishFormat_cd; break;
		}
	}
	if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->datexSubscription_Priority_nbr), &consinfo_datexSubscription_Priority_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_BOOLEAN(workspace, &(value->datexSubscribe_Guarantee_bool), &consinfo_datexSubscribe_Guarantee_bool)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_EndApplicationMessage(workspace, value->datexSubscribe_Pdu)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_SubscriptionData(SubscriptionData *value);
extern int ASN1_PER_Align_Data_Dec_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value);
int ASN1_PER_Align_Dec_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_SubscriptionData(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_SubscriptionData(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Enc_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value);
extern int ASN1_PER_UNAlign_Data_Enc_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value);
int ASN1_PER_UNAlign_Data_Enc_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value)
{
	int ret = 0;
	ASNINT32 ui_datexSubscribe_Status_cd;
	ASNINT32 ui_datexSubscribe_PublishFormat_cd;
	struct Asn1ConsInfo consinfo_datexSubscribe_Persistent_bool = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_Status_cd = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_Mode = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_PublishFormat_cd = { ASN1_CONST64(0), ASN1_CONST64(3), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscription_Priority_nbr = { ASN1_CONST64(1), ASN1_CONST64(10), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_Guarantee_bool = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_Pdu = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_UNAlign_Enc_BOOLEAN(workspace, &(value->datexSubscribe_Persistent_bool), &consinfo_datexSubscribe_Persistent_bool)) < 0) return ret;
	switch(value->datexSubscribe_Status_cd)
	{
	case SubscriptionData_datexSubscribe_Status_cd_new: ui_datexSubscribe_Status_cd = 0; consinfo_datexSubscribe_Status_cd.enumextbit = 0; break;
	case SubscriptionData_datexSubscribe_Status_cd_update: ui_datexSubscribe_Status_cd = 1; consinfo_datexSubscribe_Status_cd.enumextbit = 0; break;
	default: ui_datexSubscribe_Status_cd = value->datexSubscribe_Status_cd; consinfo_datexSubscribe_Status_cd.enumextbit = 0;break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_datexSubscribe_Status_cd, &consinfo_datexSubscribe_Status_cd)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_SubscriptionMode(workspace, value->datexSubscribe_Mode)) < 0) return ret;
	switch(value->datexSubscribe_PublishFormat_cd)
	{
	case SubscriptionData_datexSubscribe_PublishFormat_cd_other: ui_datexSubscribe_PublishFormat_cd = 0; consinfo_datexSubscribe_PublishFormat_cd.enumextbit = 0; break;
	case SubscriptionData_datexSubscribe_PublishFormat_cd_ftp: ui_datexSubscribe_PublishFormat_cd = 1; consinfo_datexSubscribe_PublishFormat_cd.enumextbit = 0; break;
	case SubscriptionData_datexSubscribe_PublishFormat_cd_tftp: ui_datexSubscribe_PublishFormat_cd = 2; consinfo_datexSubscribe_PublishFormat_cd.enumextbit = 0; break;
	case SubscriptionData_datexSubscribe_PublishFormat_cd_dataPacket: ui_datexSubscribe_PublishFormat_cd = 3; consinfo_datexSubscribe_PublishFormat_cd.enumextbit = 0; break;
	default: ui_datexSubscribe_PublishFormat_cd = value->datexSubscribe_PublishFormat_cd; consinfo_datexSubscribe_PublishFormat_cd.enumextbit = 1;break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_datexSubscribe_PublishFormat_cd, &consinfo_datexSubscribe_PublishFormat_cd)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->datexSubscription_Priority_nbr), &consinfo_datexSubscription_Priority_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_BOOLEAN(workspace, &(value->datexSubscribe_Guarantee_bool), &consinfo_datexSubscribe_Guarantee_bool)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_EndApplicationMessage(workspace, value->datexSubscribe_Pdu)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_SubscriptionData(SubscriptionData *value);
extern int ASN1_PER_UNAlign_Data_Enc_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value);
int ASN1_PER_UNAlign_Enc_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_SubscriptionData(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_SubscriptionData(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Dec_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value);
extern int ASN1_PER_UNAlign_Data_Dec_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value);
int ASN1_PER_UNAlign_Data_Dec_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value)
{
	int ret = 0;
	ASNINT32 ui_datexSubscribe_Status_cd;
	ASNINT32 ui_datexSubscribe_PublishFormat_cd;
	struct Asn1ConsInfo consinfo_datexSubscribe_Persistent_bool = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_Status_cd = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_Mode = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_PublishFormat_cd = { ASN1_CONST64(0), ASN1_CONST64(3), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscription_Priority_nbr = { ASN1_CONST64(1), ASN1_CONST64(10), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_Guarantee_bool = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_Pdu = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	value->datexSubscribe_Mode = (SubscriptionMode *)mpool_malloc(workspace->Pmemory, sizeof(SubscriptionMode));
	memset(value->datexSubscribe_Mode, 0, sizeof(SubscriptionMode));
	value->datexSubscribe_Pdu = (EndApplicationMessage *)mpool_malloc(workspace->Pmemory, sizeof(EndApplicationMessage));
	memset(value->datexSubscribe_Pdu, 0, sizeof(EndApplicationMessage));
	if ((ret = ASN1_PER_UNAlign_Dec_BOOLEAN(workspace, &(value->datexSubscribe_Persistent_bool), &consinfo_datexSubscribe_Persistent_bool)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_datexSubscribe_Status_cd, &consinfo_datexSubscribe_Status_cd)) < 0) return ret;
	if (consinfo_datexSubscribe_Status_cd.enumextbit == 0)
	{
		switch(ui_datexSubscribe_Status_cd)
		{
		case 0: value->datexSubscribe_Status_cd = SubscriptionData_datexSubscribe_Status_cd_new; break;
		case 1: value->datexSubscribe_Status_cd = SubscriptionData_datexSubscribe_Status_cd_update; break;
		default: value->datexSubscribe_Status_cd = ui_datexSubscribe_Status_cd; break;
		}
	}
	if ((ret = ASN1_PER_UNAlign_Dec_SubscriptionMode(workspace, value->datexSubscribe_Mode)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_datexSubscribe_PublishFormat_cd, &consinfo_datexSubscribe_PublishFormat_cd)) < 0) return ret;
	if (consinfo_datexSubscribe_PublishFormat_cd.enumextbit == 0)
	{
		switch(ui_datexSubscribe_PublishFormat_cd)
		{
		case 0: value->datexSubscribe_PublishFormat_cd = SubscriptionData_datexSubscribe_PublishFormat_cd_other; break;
		case 1: value->datexSubscribe_PublishFormat_cd = SubscriptionData_datexSubscribe_PublishFormat_cd_ftp; break;
		case 2: value->datexSubscribe_PublishFormat_cd = SubscriptionData_datexSubscribe_PublishFormat_cd_tftp; break;
		case 3: value->datexSubscribe_PublishFormat_cd = SubscriptionData_datexSubscribe_PublishFormat_cd_dataPacket; break;
		default: break;
		}
	}
	else
	{
		switch(ui_datexSubscribe_PublishFormat_cd)
		{
		default: value->datexSubscribe_PublishFormat_cd = ui_datexSubscribe_PublishFormat_cd; break;
		}
	}
	if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->datexSubscription_Priority_nbr), &consinfo_datexSubscription_Priority_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_BOOLEAN(workspace, &(value->datexSubscribe_Guarantee_bool), &consinfo_datexSubscribe_Guarantee_bool)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_EndApplicationMessage(workspace, value->datexSubscribe_Pdu)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_SubscriptionData(SubscriptionData *value);
extern int ASN1_PER_UNAlign_Data_Dec_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value);
int ASN1_PER_UNAlign_Dec_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_SubscriptionData(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_SubscriptionData(value)) < 0) return ret;
	return ret;
}

/********************************************************
*SubscriptionType_datexSubscribe-CancelReason-cd        *
********************************************************/
int ASN1_Print_SubscriptionType_datexSubscribe_CancelReason_cd(SubscriptionType_datexSubscribe_CancelReason_cd *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch(*value)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("SubscriptionType_datexSubscribe-CancelReason-cd", "other", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("SubscriptionType_datexSubscribe-CancelReason-cd", "dataNotNeeded", 1)) < 0) return ret; break;
	case 2: if ((ret = ASN1_Print_ENUMERATED("SubscriptionType_datexSubscribe-CancelReason-cd", "errorsInPublication", 2)) < 0) return ret; break;
	case 3: if ((ret = ASN1_Print_ENUMERATED("SubscriptionType_datexSubscribe-CancelReason-cd", "pendingLogout", 3)) < 0) return ret; break;
	case 4: if ((ret = ASN1_Print_ENUMERATED("SubscriptionType_datexSubscribe-CancelReason-cd", "processingMgmt", 4)) < 0) return ret; break;
	case 5: if ((ret = ASN1_Print_ENUMERATED("SubscriptionType_datexSubscribe-CancelReason-cd", "bandwidthMgmt", 5)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	return ret;
}
int ASN1_CHECK_SubscriptionType_datexSubscribe_CancelReason_cd(SubscriptionType_datexSubscribe_CancelReason_cd *value)
{
	unsigned char checkinfo_SubscriptionType_datexSubscribe_CancelReason_cd[] = {0x06,0x00,0x01,0x02,0x03,0x04,0x05,0x00 };
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32 *)value, checkinfo_SubscriptionType_datexSubscribe_CancelReason_cd)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_SubscriptionType_datexSubscribe_CancelReason_cd(ASN1WorkSpace *workspace, SubscriptionType_datexSubscribe_CancelReason_cd *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_SubscriptionType_datexSubscribe_CancelReason_cd(ASN1WorkSpace *workspace, SubscriptionType_datexSubscribe_CancelReason_cd *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_SubscriptionType_datexSubscribe_CancelReason_cd(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SubscriptionType_datexSubscribe_CancelReason_cd(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_SubscriptionType_datexSubscribe_CancelReason_cd(ASN1WorkSpace *workspace, SubscriptionType_datexSubscribe_CancelReason_cd *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_SubscriptionType_datexSubscribe_CancelReason_cd(ASN1WorkSpace *workspace, SubscriptionType_datexSubscribe_CancelReason_cd *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SubscriptionType_datexSubscribe_CancelReason_cd(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_SubscriptionType_datexSubscribe_CancelReason_cd(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_SubscriptionType_datexSubscribe_CancelReason_cd(ASN1WorkSpace *workspace, SubscriptionType_datexSubscribe_CancelReason_cd *value)
{
	struct Asn1ConsInfo consinfo_SubscriptionType_datexSubscribe_CancelReason_cd = { ASN1_CONST64(0), ASN1_CONST64(5), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_SubscriptionType_datexSubscribe_CancelReason_cd;
	switch(*value)
	{
	case SubscriptionType_datexSubscribe_CancelReason_cd_other: ui_SubscriptionType_datexSubscribe_CancelReason_cd = 0; consinfo_SubscriptionType_datexSubscribe_CancelReason_cd.enumextbit = 0; break;
	case SubscriptionType_datexSubscribe_CancelReason_cd_dataNotNeeded: ui_SubscriptionType_datexSubscribe_CancelReason_cd = 1; consinfo_SubscriptionType_datexSubscribe_CancelReason_cd.enumextbit = 0; break;
	case SubscriptionType_datexSubscribe_CancelReason_cd_errorsInPublication: ui_SubscriptionType_datexSubscribe_CancelReason_cd = 2; consinfo_SubscriptionType_datexSubscribe_CancelReason_cd.enumextbit = 0; break;
	case SubscriptionType_datexSubscribe_CancelReason_cd_pendingLogout: ui_SubscriptionType_datexSubscribe_CancelReason_cd = 3; consinfo_SubscriptionType_datexSubscribe_CancelReason_cd.enumextbit = 0; break;
	case SubscriptionType_datexSubscribe_CancelReason_cd_processingMgmt: ui_SubscriptionType_datexSubscribe_CancelReason_cd = 4; consinfo_SubscriptionType_datexSubscribe_CancelReason_cd.enumextbit = 0; break;
	case SubscriptionType_datexSubscribe_CancelReason_cd_bandwidthMgmt: ui_SubscriptionType_datexSubscribe_CancelReason_cd = 5; consinfo_SubscriptionType_datexSubscribe_CancelReason_cd.enumextbit = 0; break;
	default: ui_SubscriptionType_datexSubscribe_CancelReason_cd = *value; consinfo_SubscriptionType_datexSubscribe_CancelReason_cd.enumextbit = 1; break;
	}
	if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_SubscriptionType_datexSubscribe_CancelReason_cd, &consinfo_SubscriptionType_datexSubscribe_CancelReason_cd)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Enc_SubscriptionType_datexSubscribe_CancelReason_cd(ASN1WorkSpace *workspace, SubscriptionType_datexSubscribe_CancelReason_cd *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_SubscriptionType_datexSubscribe_CancelReason_cd(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_SubscriptionType_datexSubscribe_CancelReason_cd(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_SubscriptionType_datexSubscribe_CancelReason_cd(ASN1WorkSpace *workspace, SubscriptionType_datexSubscribe_CancelReason_cd *value)
{
	struct Asn1ConsInfo consinfo_SubscriptionType_datexSubscribe_CancelReason_cd = { ASN1_CONST64(0), ASN1_CONST64(5), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_SubscriptionType_datexSubscribe_CancelReason_cd;
	if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_SubscriptionType_datexSubscribe_CancelReason_cd, &consinfo_SubscriptionType_datexSubscribe_CancelReason_cd)) < 0) return ret;
	if (consinfo_SubscriptionType_datexSubscribe_CancelReason_cd.enumextbit == 0)
	{
		switch(ui_SubscriptionType_datexSubscribe_CancelReason_cd)
		{
		case 0: *value = SubscriptionType_datexSubscribe_CancelReason_cd_other; break;
		case 1: *value = SubscriptionType_datexSubscribe_CancelReason_cd_dataNotNeeded; break;
		case 2: *value = SubscriptionType_datexSubscribe_CancelReason_cd_errorsInPublication; break;
		case 3: *value = SubscriptionType_datexSubscribe_CancelReason_cd_pendingLogout; break;
		case 4: *value = SubscriptionType_datexSubscribe_CancelReason_cd_processingMgmt; break;
		case 5: *value = SubscriptionType_datexSubscribe_CancelReason_cd_bandwidthMgmt; break;
		default: break;
		}
	}
	else
	{
		switch(ui_SubscriptionType_datexSubscribe_CancelReason_cd)
		{
		default: *value = ui_SubscriptionType_datexSubscribe_CancelReason_cd; break;
		}
	}
	return ret;
}
int ASN1_PER_Align_Dec_SubscriptionType_datexSubscribe_CancelReason_cd(ASN1WorkSpace *workspace, SubscriptionType_datexSubscribe_CancelReason_cd *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_SubscriptionType_datexSubscribe_CancelReason_cd(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_SubscriptionType_datexSubscribe_CancelReason_cd(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_SubscriptionType_datexSubscribe_CancelReason_cd(ASN1WorkSpace *workspace, SubscriptionType_datexSubscribe_CancelReason_cd *value)
{
	struct Asn1ConsInfo consinfo_SubscriptionType_datexSubscribe_CancelReason_cd = { ASN1_CONST64(0), ASN1_CONST64(5), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_SubscriptionType_datexSubscribe_CancelReason_cd;
	switch(*value)
	{
	case SubscriptionType_datexSubscribe_CancelReason_cd_other: ui_SubscriptionType_datexSubscribe_CancelReason_cd = 0; consinfo_SubscriptionType_datexSubscribe_CancelReason_cd.enumextbit = 0; break;
	case SubscriptionType_datexSubscribe_CancelReason_cd_dataNotNeeded: ui_SubscriptionType_datexSubscribe_CancelReason_cd = 1; consinfo_SubscriptionType_datexSubscribe_CancelReason_cd.enumextbit = 0; break;
	case SubscriptionType_datexSubscribe_CancelReason_cd_errorsInPublication: ui_SubscriptionType_datexSubscribe_CancelReason_cd = 2; consinfo_SubscriptionType_datexSubscribe_CancelReason_cd.enumextbit = 0; break;
	case SubscriptionType_datexSubscribe_CancelReason_cd_pendingLogout: ui_SubscriptionType_datexSubscribe_CancelReason_cd = 3; consinfo_SubscriptionType_datexSubscribe_CancelReason_cd.enumextbit = 0; break;
	case SubscriptionType_datexSubscribe_CancelReason_cd_processingMgmt: ui_SubscriptionType_datexSubscribe_CancelReason_cd = 4; consinfo_SubscriptionType_datexSubscribe_CancelReason_cd.enumextbit = 0; break;
	case SubscriptionType_datexSubscribe_CancelReason_cd_bandwidthMgmt: ui_SubscriptionType_datexSubscribe_CancelReason_cd = 5; consinfo_SubscriptionType_datexSubscribe_CancelReason_cd.enumextbit = 0; break;
	default: ui_SubscriptionType_datexSubscribe_CancelReason_cd = *value; consinfo_SubscriptionType_datexSubscribe_CancelReason_cd.enumextbit = 1; break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_SubscriptionType_datexSubscribe_CancelReason_cd, &consinfo_SubscriptionType_datexSubscribe_CancelReason_cd)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Enc_SubscriptionType_datexSubscribe_CancelReason_cd(ASN1WorkSpace *workspace, SubscriptionType_datexSubscribe_CancelReason_cd *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_SubscriptionType_datexSubscribe_CancelReason_cd(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_SubscriptionType_datexSubscribe_CancelReason_cd(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_SubscriptionType_datexSubscribe_CancelReason_cd(ASN1WorkSpace *workspace, SubscriptionType_datexSubscribe_CancelReason_cd *value)
{
	struct Asn1ConsInfo consinfo_SubscriptionType_datexSubscribe_CancelReason_cd = { ASN1_CONST64(0), ASN1_CONST64(5), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_SubscriptionType_datexSubscribe_CancelReason_cd;
	if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_SubscriptionType_datexSubscribe_CancelReason_cd, &consinfo_SubscriptionType_datexSubscribe_CancelReason_cd)) < 0) return ret;
	if (consinfo_SubscriptionType_datexSubscribe_CancelReason_cd.enumextbit == 0)
	{
		switch(ui_SubscriptionType_datexSubscribe_CancelReason_cd)
		{
		case 0: *value = SubscriptionType_datexSubscribe_CancelReason_cd_other; break;
		case 1: *value = SubscriptionType_datexSubscribe_CancelReason_cd_dataNotNeeded; break;
		case 2: *value = SubscriptionType_datexSubscribe_CancelReason_cd_errorsInPublication; break;
		case 3: *value = SubscriptionType_datexSubscribe_CancelReason_cd_pendingLogout; break;
		case 4: *value = SubscriptionType_datexSubscribe_CancelReason_cd_processingMgmt; break;
		case 5: *value = SubscriptionType_datexSubscribe_CancelReason_cd_bandwidthMgmt; break;
		default: break;
		}
	}
	else
	{
		switch(ui_SubscriptionType_datexSubscribe_CancelReason_cd)
		{
		default: *value = ui_SubscriptionType_datexSubscribe_CancelReason_cd; break;
		}
	}
	return ret;
}
int ASN1_PER_UNAlign_Dec_SubscriptionType_datexSubscribe_CancelReason_cd(ASN1WorkSpace *workspace, SubscriptionType_datexSubscribe_CancelReason_cd *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_SubscriptionType_datexSubscribe_CancelReason_cd(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_SubscriptionType_datexSubscribe_CancelReason_cd(value)) < 0) return ret;
	return ret;
}

/********************************************************
*SubscriptionType                                       *
********************************************************/
int ASN1_Print_SubscriptionType(SubscriptionType *value, int tab_value)
{
	int ret = 0;
	// CHOICE : t->tempIdentifier is Upper Letter
	ASN1_Print_CHOICE("SubscriptionType");
	if (value == NULL) return -1;
	switch (value->M) {
	case DEF_SubscriptionType_subscription:
		// Type Reference SubscriptionData
		if (Compare_Letter(tab_value, "subscription")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("subscription = ");
		}
		if ((ret = ASN1_Print_SubscriptionData((SubscriptionData *)value->elements.subscription, tab_value + 1)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_SubscriptionType_datexSubscribe_CancelReason_cd:
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		switch(value->elements.datexSubscribe_CancelReason_cd)
		{
		case 0: if ((ret = ASN1_Print_ENUMERATED("SubscriptionType_datexSubscribe-CancelReason-cd", "other", 0)) < 0) return ret; break;
		case 1: if ((ret = ASN1_Print_ENUMERATED("SubscriptionType_datexSubscribe-CancelReason-cd", "dataNotNeeded", 1)) < 0) return ret; break;
		case 2: if ((ret = ASN1_Print_ENUMERATED("SubscriptionType_datexSubscribe-CancelReason-cd", "errorsInPublication", 2)) < 0) return ret; break;
		case 3: if ((ret = ASN1_Print_ENUMERATED("SubscriptionType_datexSubscribe-CancelReason-cd", "pendingLogout", 3)) < 0) return ret; break;
		case 4: if ((ret = ASN1_Print_ENUMERATED("SubscriptionType_datexSubscribe-CancelReason-cd", "processingMgmt", 4)) < 0) return ret; break;
		case 5: if ((ret = ASN1_Print_ENUMERATED("SubscriptionType_datexSubscribe-CancelReason-cd", "bandwidthMgmt", 5)) < 0) return ret; break;
		default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
		};
		if (ret != 0) return -1;
		break;
	default: return -1;
}
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_SubscriptionType_subscription(ASN1WorkSpace *workspace, SubscriptionType *value, SubscriptionData *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->elements.subscription = (SubscriptionData *)mpool_malloc(workspace->Pmemory, sizeof(SubscriptionData));
	memset(value->elements.subscription, 0, sizeof(SubscriptionData));
	value->M = DEF_SubscriptionType_subscription;
	memmove(value->elements.subscription, user_value, sizeof(SubscriptionData));
	return ret;
}
int ASN1_SET_SubscriptionType_datexSubscribe_CancelReason_cd(ASN1WorkSpace *workspace, SubscriptionType *value, ENUMERATED user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->M = DEF_SubscriptionType_datexSubscribe_CancelReason_cd;
	if ((ret = ASN1_SET_ENUMERATED(workspace, (ASNINT32*)&value->elements.datexSubscribe_CancelReason_cd, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_SubscriptionType_subscription(ASN1WorkSpace *workspace, SubscriptionType *value, SubscriptionData **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->M == DEF_SubscriptionType_subscription)
	{
		*user_value = value->elements.subscription;
	}
	else return -2;
	return ret;
}
int ASN1_GET_SubscriptionType_datexSubscribe_CancelReason_cd(ASN1WorkSpace *workspace, SubscriptionType *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->M == DEF_SubscriptionType_datexSubscribe_CancelReason_cd)
	{
		if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->elements.datexSubscribe_CancelReason_cd, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
extern int ASN1_CHECK_SubscriptionData(SubscriptionData *value);
int ASN1_CHECK_SubscriptionType(SubscriptionType *value)
{
	int ret = 0;

	unsigned char checkinfo_subscription[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datexSubscribe_CancelReason_cd[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_SubscriptionType_subscription:
		if ((ret = ASN1_CHECK_SubscriptionData(value->elements.subscription)) < 0) return ret;
		break;
	case DEF_SubscriptionType_datexSubscribe_CancelReason_cd:
		if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&value->elements.datexSubscribe_CancelReason_cd, checkinfo_datexSubscribe_CancelReason_cd)) < 0) return ret;
		break;
	default: break;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_SubscriptionType_datexSubscribe_CancelReason_cd(ASN1WorkSpace *workspace, SubscriptionType_datexSubscribe_CancelReason_cd *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value, ASN1TagType tagFlag)
{
	int ret = 0;
	switch(value->M)
	{
	case DEF_SubscriptionType_subscription:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 0)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_SubscriptionData(workspace, value->elements.subscription, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
		break;
	case DEF_SubscriptionType_datexSubscribe_CancelReason_cd:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_SubscriptionType_datexSubscribe_CancelReason_cd(workspace, &(value->elements.datexSubscribe_CancelReason_cd), ASN1IMPL)) < 0) return ret;
		break;
	}
	return ret;
}
extern int ASN1_CHECK_SubscriptionType(SubscriptionType *value);
extern int ASN1_BER_Data_Enc_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_SubscriptionType(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SubscriptionType(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_SubscriptionType_datexSubscribe_CancelReason_cd(ASN1WorkSpace *workspace, SubscriptionType_datexSubscribe_CancelReason_cd *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	value->M = 0;
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	switch(tag)
	{
	case ITS_ASN_CONT | ITS_ASN_CONS | 0:
		value->elements.subscription = (SubscriptionData *)mpool_malloc(workspace->Pmemory, sizeof(SubscriptionData));
		memset(value->elements.subscription, 0, sizeof(SubscriptionData));
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 0)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_SubscriptionData(workspace, value->elements.subscription, len, ASN1IMPL)) < 0) return ret;
		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->M = DEF_SubscriptionType_subscription;
		break;
	case ITS_ASN_CONT | ITS_ASN_PRIM | 1:
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_SubscriptionType_datexSubscribe_CancelReason_cd(workspace, &value->elements.datexSubscribe_CancelReason_cd, len, ASN1IMPL)) < 0) return ret;
		value->M = DEF_SubscriptionType_datexSubscribe_CancelReason_cd;
		break;
	}
	return ret;
}
extern int ASN1_CHECK_SubscriptionType(SubscriptionType *value);
extern int ASN1_BER_Data_Dec_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SubscriptionType(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_SubscriptionType(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Enc_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value);
int ASN1_PER_Align_Data_Enc_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value)
{
	int ret = 0;
	ASNINT32 ui_datexSubscribe_CancelReason_cd;
	struct Asn1ConsInfo consinfo_subscription = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_CancelReason_cd = { ASN1_CONST64(0), ASN1_CONST64(5), NULL, 1, CONS, 0, 0 };

	ASNINT64 ui;
	ASNBOOL extbit = 1;
	switch(value->M)
	{
	case DEF_SubscriptionType_subscription: ui = 0; extbit = 0; break;
	case DEF_SubscriptionType_datexSubscribe_CancelReason_cd: ui = 1; extbit = 0; break;
	default: break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_Choice_ENUMERATED(workspace, ui, extbit, 0, 2)) < 0) return ret;
	switch(value->M)
	{
	case DEF_SubscriptionType_subscription:
		if ((ret = ASN1_PER_Align_Enc_SubscriptionData(workspace, value->elements.subscription)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_SubscriptionType_datexSubscribe_CancelReason_cd:
		switch(value->elements.datexSubscribe_CancelReason_cd)
		{
		case SubscriptionType_datexSubscribe_CancelReason_cd_other: ui_datexSubscribe_CancelReason_cd = 0; consinfo_datexSubscribe_CancelReason_cd.enumextbit = 0; break;
		case SubscriptionType_datexSubscribe_CancelReason_cd_dataNotNeeded: ui_datexSubscribe_CancelReason_cd = 1; consinfo_datexSubscribe_CancelReason_cd.enumextbit = 0; break;
		case SubscriptionType_datexSubscribe_CancelReason_cd_errorsInPublication: ui_datexSubscribe_CancelReason_cd = 2; consinfo_datexSubscribe_CancelReason_cd.enumextbit = 0; break;
		case SubscriptionType_datexSubscribe_CancelReason_cd_pendingLogout: ui_datexSubscribe_CancelReason_cd = 3; consinfo_datexSubscribe_CancelReason_cd.enumextbit = 0; break;
		case SubscriptionType_datexSubscribe_CancelReason_cd_processingMgmt: ui_datexSubscribe_CancelReason_cd = 4; consinfo_datexSubscribe_CancelReason_cd.enumextbit = 0; break;
		case SubscriptionType_datexSubscribe_CancelReason_cd_bandwidthMgmt: ui_datexSubscribe_CancelReason_cd = 5; consinfo_datexSubscribe_CancelReason_cd.enumextbit = 0; break;
		default: ui_datexSubscribe_CancelReason_cd = value->elements.datexSubscribe_CancelReason_cd; consinfo_datexSubscribe_CancelReason_cd.enumextbit = 1;break;
		}
		if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_datexSubscribe_CancelReason_cd, &consinfo_datexSubscribe_CancelReason_cd)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: break;
	}
	return ret;
}
extern int ASN1_CHECK_SubscriptionType(SubscriptionType *value);
extern int ASN1_PER_Align_Data_Enc_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value);
int ASN1_PER_Align_Enc_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_SubscriptionType(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_SubscriptionType(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Dec_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value);
int ASN1_PER_Align_Data_Dec_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value)
{
	int ret = 0;
	ASNINT32 ui_datexSubscribe_CancelReason_cd;
	struct Asn1ConsInfo consinfo_subscription = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_CancelReason_cd = { ASN1_CONST64(0), ASN1_CONST64(5), NULL, 1, CONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	if ((ret = ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 2)) < 0) return ret;

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_SubscriptionType_subscription;
			value->elements.subscription = (SubscriptionData *)mpool_malloc(workspace->Pmemory, sizeof(SubscriptionData));
			memset(value->elements.subscription, 0, sizeof(SubscriptionData));
			break;
		case 1: index = DEF_SubscriptionType_datexSubscribe_CancelReason_cd;
			break;
		default: break;
		}
	}
	else
	{
		switch(ui)
		{
		default: break;
		}
	}
	if ((ret = ASN1_GetM(&value->M, index)) < 0) return ret;
	switch(index)
	{
	case DEF_SubscriptionType_subscription:
		if ((ret = ASN1_PER_Align_Dec_SubscriptionData(workspace, value->elements.subscription)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_SubscriptionType_datexSubscribe_CancelReason_cd:
		if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_datexSubscribe_CancelReason_cd, &consinfo_datexSubscribe_CancelReason_cd)) < 0) return ret;
		if (consinfo_datexSubscribe_CancelReason_cd.enumextbit == 0)
		{
			switch(ui_datexSubscribe_CancelReason_cd)
			{
			case 0: value->elements.datexSubscribe_CancelReason_cd = SubscriptionType_datexSubscribe_CancelReason_cd_other; break;
			case 1: value->elements.datexSubscribe_CancelReason_cd = SubscriptionType_datexSubscribe_CancelReason_cd_dataNotNeeded; break;
			case 2: value->elements.datexSubscribe_CancelReason_cd = SubscriptionType_datexSubscribe_CancelReason_cd_errorsInPublication; break;
			case 3: value->elements.datexSubscribe_CancelReason_cd = SubscriptionType_datexSubscribe_CancelReason_cd_pendingLogout; break;
			case 4: value->elements.datexSubscribe_CancelReason_cd = SubscriptionType_datexSubscribe_CancelReason_cd_processingMgmt; break;
			case 5: value->elements.datexSubscribe_CancelReason_cd = SubscriptionType_datexSubscribe_CancelReason_cd_bandwidthMgmt; break;
			default: break;
			}
		}
		else
		{
			switch(ui_datexSubscribe_CancelReason_cd)
			{
			default: value->elements.datexSubscribe_CancelReason_cd = ui_datexSubscribe_CancelReason_cd; break;
			}
		}
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, ALIGN); break;
	}
	return ret;
}
extern int ASN1_CHECK_SubscriptionType(SubscriptionType *value);
extern int ASN1_PER_Align_Data_Dec_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value);
int ASN1_PER_Align_Dec_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_SubscriptionType(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_SubscriptionType(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Enc_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value);
int ASN1_PER_UNAlign_Data_Enc_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value)
{
	int ret = 0;
	ASNINT32 ui_datexSubscribe_CancelReason_cd;
	struct Asn1ConsInfo consinfo_subscription = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_CancelReason_cd = { ASN1_CONST64(0), ASN1_CONST64(5), NULL, 1, CONS, 0, 0 };

	ASNINT64 ui;
	ASNBOOL extbit = 1;
	switch(value->M)
	{
	case DEF_SubscriptionType_subscription: ui = 0; extbit = 0; break;
	case DEF_SubscriptionType_datexSubscribe_CancelReason_cd: ui = 1; extbit = 0; break;
	default: break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_Choice_ENUMERATED(workspace, ui, extbit, 0, 2)) < 0) return ret;
	switch(value->M)
	{
	case DEF_SubscriptionType_subscription:
		if ((ret = ASN1_PER_UNAlign_Enc_SubscriptionData(workspace, value->elements.subscription)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_SubscriptionType_datexSubscribe_CancelReason_cd:
		switch(value->elements.datexSubscribe_CancelReason_cd)
		{
		case SubscriptionType_datexSubscribe_CancelReason_cd_other: ui_datexSubscribe_CancelReason_cd = 0; consinfo_datexSubscribe_CancelReason_cd.enumextbit = 0; break;
		case SubscriptionType_datexSubscribe_CancelReason_cd_dataNotNeeded: ui_datexSubscribe_CancelReason_cd = 1; consinfo_datexSubscribe_CancelReason_cd.enumextbit = 0; break;
		case SubscriptionType_datexSubscribe_CancelReason_cd_errorsInPublication: ui_datexSubscribe_CancelReason_cd = 2; consinfo_datexSubscribe_CancelReason_cd.enumextbit = 0; break;
		case SubscriptionType_datexSubscribe_CancelReason_cd_pendingLogout: ui_datexSubscribe_CancelReason_cd = 3; consinfo_datexSubscribe_CancelReason_cd.enumextbit = 0; break;
		case SubscriptionType_datexSubscribe_CancelReason_cd_processingMgmt: ui_datexSubscribe_CancelReason_cd = 4; consinfo_datexSubscribe_CancelReason_cd.enumextbit = 0; break;
		case SubscriptionType_datexSubscribe_CancelReason_cd_bandwidthMgmt: ui_datexSubscribe_CancelReason_cd = 5; consinfo_datexSubscribe_CancelReason_cd.enumextbit = 0; break;
		default: ui_datexSubscribe_CancelReason_cd = value->elements.datexSubscribe_CancelReason_cd; consinfo_datexSubscribe_CancelReason_cd.enumextbit = 1;break;
		}
		if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_datexSubscribe_CancelReason_cd, &consinfo_datexSubscribe_CancelReason_cd)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: break;
	}
	return ret;
}
extern int ASN1_CHECK_SubscriptionType(SubscriptionType *value);
extern int ASN1_PER_UNAlign_Data_Enc_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value);
int ASN1_PER_UNAlign_Enc_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_SubscriptionType(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_SubscriptionType(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Dec_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value);
int ASN1_PER_UNAlign_Data_Dec_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value)
{
	int ret = 0;
	ASNINT32 ui_datexSubscribe_CancelReason_cd;
	struct Asn1ConsInfo consinfo_subscription = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_CancelReason_cd = { ASN1_CONST64(0), ASN1_CONST64(5), NULL, 1, CONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	if ((ret = ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 2)) < 0) return ret;

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_SubscriptionType_subscription;
			value->elements.subscription = (SubscriptionData *)mpool_malloc(workspace->Pmemory, sizeof(SubscriptionData));
			memset(value->elements.subscription, 0, sizeof(SubscriptionData));
			break;
		case 1: index = DEF_SubscriptionType_datexSubscribe_CancelReason_cd;
			break;
		default: break;
		}
	}
	else
	{
		switch(ui)
		{
		default: break;
		}
	}
	if ((ret = ASN1_GetM(&value->M, index)) < 0) return ret;
	switch(index)
	{
	case DEF_SubscriptionType_subscription:
		if ((ret = ASN1_PER_UNAlign_Dec_SubscriptionData(workspace, value->elements.subscription)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_SubscriptionType_datexSubscribe_CancelReason_cd:
		if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_datexSubscribe_CancelReason_cd, &consinfo_datexSubscribe_CancelReason_cd)) < 0) return ret;
		if (consinfo_datexSubscribe_CancelReason_cd.enumextbit == 0)
		{
			switch(ui_datexSubscribe_CancelReason_cd)
			{
			case 0: value->elements.datexSubscribe_CancelReason_cd = SubscriptionType_datexSubscribe_CancelReason_cd_other; break;
			case 1: value->elements.datexSubscribe_CancelReason_cd = SubscriptionType_datexSubscribe_CancelReason_cd_dataNotNeeded; break;
			case 2: value->elements.datexSubscribe_CancelReason_cd = SubscriptionType_datexSubscribe_CancelReason_cd_errorsInPublication; break;
			case 3: value->elements.datexSubscribe_CancelReason_cd = SubscriptionType_datexSubscribe_CancelReason_cd_pendingLogout; break;
			case 4: value->elements.datexSubscribe_CancelReason_cd = SubscriptionType_datexSubscribe_CancelReason_cd_processingMgmt; break;
			case 5: value->elements.datexSubscribe_CancelReason_cd = SubscriptionType_datexSubscribe_CancelReason_cd_bandwidthMgmt; break;
			default: break;
			}
		}
		else
		{
			switch(ui_datexSubscribe_CancelReason_cd)
			{
			default: value->elements.datexSubscribe_CancelReason_cd = ui_datexSubscribe_CancelReason_cd; break;
			}
		}
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
extern int ASN1_CHECK_SubscriptionType(SubscriptionType *value);
extern int ASN1_PER_UNAlign_Data_Dec_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value);
int ASN1_PER_UNAlign_Dec_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_SubscriptionType(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_SubscriptionType(value)) < 0) return ret;
	return ret;
}

/********************************************************
*Subscription                                           *
********************************************************/
int ASN1_Print_Subscription(Subscription *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("Subscription");
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("datexSubscribe_Serial_nbr", &(value->datexSubscribe_Serial_nbr))) < 0) return ret;
	// Type Reference SubscriptionType
	if (Compare_Letter(tab_value, "datexSubscribe-Type")) {
		ASN_Print_TAB(tab_value + 1);
		asn_printf("datexSubscribe-Type = ");
	}
	if ((ret = ASN1_Print_SubscriptionType((SubscriptionType *)value->datexSubscribe_Type, tab_value + 1)) < 0) return ret;
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_Subscription_datexSubscribe_Serial_nbr(ASN1WorkSpace *workspace, Subscription *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->datexSubscribe_Serial_nbr, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_Subscription_datexSubscribe_Type(ASN1WorkSpace *workspace, Subscription *value, SubscriptionType *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->datexSubscribe_Type = (SubscriptionType *)mpool_malloc(workspace->Pmemory, sizeof(SubscriptionType));
	memset(value->datexSubscribe_Type, 0, sizeof(SubscriptionType));
	memmove(value->datexSubscribe_Type, user_value, sizeof(SubscriptionType));
	return ret;
}
int ASN1_GET_Subscription_datexSubscribe_Serial_nbr(ASN1WorkSpace *workspace, Subscription *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->datexSubscribe_Serial_nbr, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_Subscription_datexSubscribe_Type(ASN1WorkSpace *workspace, Subscription *value, SubscriptionType **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = value->datexSubscribe_Type;
	return ret;
}
extern int ASN1_CHECK_SubscriptionType(SubscriptionType *value);
int ASN1_CHECK_Subscription(Subscription *value)
{
	int ret = 0;

	unsigned char checkinfo_datexSubscribe_Serial_nbr[] = { 
		0x02,0x00,0x85,0x00,0xFF,0xFF,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_datexSubscribe_Type[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(&(value->datexSubscribe_Serial_nbr), checkinfo_datexSubscribe_Serial_nbr)) < 0) return ret;
	if ((ret = ASN1_CHECK_SubscriptionType(value->datexSubscribe_Type)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Enc_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_Subscription(ASN1WorkSpace *workspace, Subscription *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->datexSubscribe_Serial_nbr), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_SubscriptionType(workspace, value->datexSubscribe_Type, ASN1EXPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Subscription(Subscription *value);
extern int ASN1_BER_Data_Enc_Subscription(ASN1WorkSpace *workspace, Subscription *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_Subscription(ASN1WorkSpace *workspace, Subscription *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_Subscription(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Subscription(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_Subscription(ASN1WorkSpace *workspace, Subscription *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8 *_cpointer;
	value->datexSubscribe_Type = (SubscriptionType *)mpool_malloc(workspace->Pmemory, sizeof(SubscriptionType));
	memset(value->datexSubscribe_Type, 0, sizeof(SubscriptionType));
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->datexSubscribe_Serial_nbr, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_SubscriptionType(workspace, value->datexSubscribe_Type, len, ASN1EXPL)) < 0) return ret;
	if (IfFixedLength(len) == -1)
	{
		if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
	}
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_Subscription(Subscription *value);
extern int ASN1_BER_Data_Dec_Subscription(ASN1WorkSpace *workspace, Subscription *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_Subscription(ASN1WorkSpace *workspace, Subscription *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Subscription(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_Subscription(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Enc_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value);
int ASN1_PER_Align_Data_Enc_Subscription(ASN1WorkSpace *workspace, Subscription *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexSubscribe_Serial_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_Type = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT32 all_bit;
	ASNUINT16 all_pointer;
	if ((ret = ASN1_PER_Enc_extbit(workspace, value->E)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->datexSubscribe_Serial_nbr), &consinfo_datexSubscribe_Serial_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_SubscriptionType(workspace, value->datexSubscribe_Type)) < 0) return ret;
	ASN1_SaveCurrentPointer(workspace, &all_bit, &all_pointer);
	if (value->E != 0)
	{
		ASN1_PER_Enc_extOption(workspace, ALIGN, 0);
	}
	return ret;
}
extern int ASN1_CHECK_Subscription(Subscription *value);
extern int ASN1_PER_Align_Data_Enc_Subscription(ASN1WorkSpace *workspace, Subscription *value);
int ASN1_PER_Align_Enc_Subscription(ASN1WorkSpace *workspace, Subscription *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Subscription(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_Subscription(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Dec_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value);
int ASN1_PER_Align_Data_Dec_Subscription(ASN1WorkSpace *workspace, Subscription *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexSubscribe_Serial_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_Type = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNBOOL extbit_Subscription;
	if ((ret = ASN1_PER_Dec_extbit(workspace, &extbit_Subscription)) < 0) return ret;
	value->datexSubscribe_Type = (SubscriptionType *)mpool_malloc(workspace->Pmemory, sizeof(SubscriptionType));
	memset(value->datexSubscribe_Type, 0, sizeof(SubscriptionType));
	if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->datexSubscribe_Serial_nbr), &consinfo_datexSubscribe_Serial_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_SubscriptionType(workspace, value->datexSubscribe_Type)) < 0) return ret;
	if (extbit_Subscription == 1)
	{ /* EXT_DEC_start */
		ASNINT32 _ext_count = 0;
		ASNINT32 _ext_x_count = 0;
		ASNUINT8 *extvalue;
		ASNINT32 ret_exp=0;
		if ((ret_exp = ASN1_PER_Dec_extOption(workspace, ALIGN, &_ext_count, &extvalue)) < 0) return ret_exp;
		_ext_x_count = _ext_count;
		_ext_x_count = _ext_x_count - _ext_count+1;
		for (;_ext_count > 0; _ext_count--)
		{
			if (ASN1_PER_CheckExtBit(extvalue, _ext_x_count) == 1)
			{
				if ((ret = ASN1_PER_Dec_unKnown(workspace, ALIGN)) != 0) return -1;
			}
			_ext_x_count++;
		}
	} /* EXT_DEC_end */

	return ret;
}
extern int ASN1_CHECK_Subscription(Subscription *value);
extern int ASN1_PER_Align_Data_Dec_Subscription(ASN1WorkSpace *workspace, Subscription *value);
int ASN1_PER_Align_Dec_Subscription(ASN1WorkSpace *workspace, Subscription *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_Subscription(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Subscription(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Enc_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value);
int ASN1_PER_UNAlign_Data_Enc_Subscription(ASN1WorkSpace *workspace, Subscription *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexSubscribe_Serial_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_Type = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT32 all_bit;
	ASNUINT16 all_pointer;
	if ((ret = ASN1_PER_Enc_extbit(workspace, value->E)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->datexSubscribe_Serial_nbr), &consinfo_datexSubscribe_Serial_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_SubscriptionType(workspace, value->datexSubscribe_Type)) < 0) return ret;
	ASN1_SaveCurrentPointer(workspace, &all_bit, &all_pointer);
	if (value->E != 0)
	{
		ASN1_PER_Enc_extOption(workspace, UNALIGN, 0);
	}
	return ret;
}
extern int ASN1_CHECK_Subscription(Subscription *value);
extern int ASN1_PER_UNAlign_Data_Enc_Subscription(ASN1WorkSpace *workspace, Subscription *value);
int ASN1_PER_UNAlign_Enc_Subscription(ASN1WorkSpace *workspace, Subscription *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Subscription(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_Subscription(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Dec_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value);
int ASN1_PER_UNAlign_Data_Dec_Subscription(ASN1WorkSpace *workspace, Subscription *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexSubscribe_Serial_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexSubscribe_Type = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNBOOL extbit_Subscription;
	if ((ret = ASN1_PER_Dec_extbit(workspace, &extbit_Subscription)) < 0) return ret;
	value->datexSubscribe_Type = (SubscriptionType *)mpool_malloc(workspace->Pmemory, sizeof(SubscriptionType));
	memset(value->datexSubscribe_Type, 0, sizeof(SubscriptionType));
	if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->datexSubscribe_Serial_nbr), &consinfo_datexSubscribe_Serial_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_SubscriptionType(workspace, value->datexSubscribe_Type)) < 0) return ret;
	if (extbit_Subscription == 1)
	{ /* EXT_DEC_start */
		ASNINT32 _ext_count = 0;
		ASNINT32 _ext_x_count = 0;
		ASNUINT8 *extvalue;
		ASNINT32 ret_exp=0;
		if ((ret_exp = ASN1_PER_Dec_extOption(workspace, UNALIGN, &_ext_count, &extvalue)) < 0) return ret_exp;
		_ext_x_count = _ext_count;
		_ext_x_count = _ext_x_count - _ext_count+1;
		for (;_ext_count > 0; _ext_count--)
		{
			if (ASN1_PER_CheckExtBit(extvalue, _ext_x_count) == 1)
			{
				if ((ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN)) != 0) return -1;
			}
			_ext_x_count++;
		}
	} /* EXT_DEC_end */

	return ret;
}
extern int ASN1_CHECK_Subscription(Subscription *value);
extern int ASN1_PER_UNAlign_Data_Dec_Subscription(ASN1WorkSpace *workspace, Subscription *value);
int ASN1_PER_UNAlign_Dec_Subscription(ASN1WorkSpace *workspace, Subscription *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_Subscription(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Subscription(value)) < 0) return ret;
	return ret;
}

/********************************************************
*PublicationType_datexPublication-Management-cd         *
********************************************************/
int ASN1_Print_PublicationType_datexPublication_Management_cd(PublicationType_datexPublication_Management_cd *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch(*value)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("PublicationType_datexPublication-Management-cd", "temporarilySuspended", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("PublicationType_datexPublication-Management-cd", "resume", 1)) < 0) return ret; break;
	case 2: if ((ret = ASN1_Print_ENUMERATED("PublicationType_datexPublication-Management-cd", "terminate-other", 2)) < 0) return ret; break;
	case 3: if ((ret = ASN1_Print_ENUMERATED("PublicationType_datexPublication-Management-cd", "terminate-dataNoLongerAvailable", 3)) < 0) return ret; break;
	case 4: if ((ret = ASN1_Print_ENUMERATED("PublicationType_datexPublication-Management-cd", "terminate-publicationsBeingRejected", 4)) < 0) return ret; break;
	case 5: if ((ret = ASN1_Print_ENUMERATED("PublicationType_datexPublication-Management-cd", "terminate-PendingShutdown", 5)) < 0) return ret; break;
	case 6: if ((ret = ASN1_Print_ENUMERATED("PublicationType_datexPublication-Management-cd", "terminate-processingMgmt", 6)) < 0) return ret; break;
	case 7: if ((ret = ASN1_Print_ENUMERATED("PublicationType_datexPublication-Management-cd", "terminate-bandwidthMgmt", 7)) < 0) return ret; break;
	case 8: if ((ret = ASN1_Print_ENUMERATED("PublicationType_datexPublication-Management-cd", "terminate-accessDenied", 8)) < 0) return ret; break;
	case 9: if ((ret = ASN1_Print_ENUMERATED("PublicationType_datexPublication-Management-cd", "unknownRequest", 9)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	return ret;
}
int ASN1_CHECK_PublicationType_datexPublication_Management_cd(PublicationType_datexPublication_Management_cd *value)
{
	unsigned char checkinfo_PublicationType_datexPublication_Management_cd[] = {0x0A,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x00 };
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32 *)value, checkinfo_PublicationType_datexPublication_Management_cd)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_PublicationType_datexPublication_Management_cd(ASN1WorkSpace *workspace, PublicationType_datexPublication_Management_cd *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_PublicationType_datexPublication_Management_cd(ASN1WorkSpace *workspace, PublicationType_datexPublication_Management_cd *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_PublicationType_datexPublication_Management_cd(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_PublicationType_datexPublication_Management_cd(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_PublicationType_datexPublication_Management_cd(ASN1WorkSpace *workspace, PublicationType_datexPublication_Management_cd *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_PublicationType_datexPublication_Management_cd(ASN1WorkSpace *workspace, PublicationType_datexPublication_Management_cd *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_PublicationType_datexPublication_Management_cd(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_PublicationType_datexPublication_Management_cd(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_PublicationType_datexPublication_Management_cd(ASN1WorkSpace *workspace, PublicationType_datexPublication_Management_cd *value)
{
	struct Asn1ConsInfo consinfo_PublicationType_datexPublication_Management_cd = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_PublicationType_datexPublication_Management_cd;
	switch(*value)
	{
	case PublicationType_datexPublication_Management_cd_temporarilySuspended: ui_PublicationType_datexPublication_Management_cd = 0; consinfo_PublicationType_datexPublication_Management_cd.enumextbit = 0; break;
	case PublicationType_datexPublication_Management_cd_resume: ui_PublicationType_datexPublication_Management_cd = 1; consinfo_PublicationType_datexPublication_Management_cd.enumextbit = 0; break;
	case PublicationType_datexPublication_Management_cd_terminate_other: ui_PublicationType_datexPublication_Management_cd = 2; consinfo_PublicationType_datexPublication_Management_cd.enumextbit = 0; break;
	case PublicationType_datexPublication_Management_cd_terminate_dataNoLongerAvailable: ui_PublicationType_datexPublication_Management_cd = 3; consinfo_PublicationType_datexPublication_Management_cd.enumextbit = 0; break;
	case PublicationType_datexPublication_Management_cd_terminate_publicationsBeingRejected: ui_PublicationType_datexPublication_Management_cd = 4; consinfo_PublicationType_datexPublication_Management_cd.enumextbit = 0; break;
	case PublicationType_datexPublication_Management_cd_terminate_PendingShutdown: ui_PublicationType_datexPublication_Management_cd = 5; consinfo_PublicationType_datexPublication_Management_cd.enumextbit = 0; break;
	case PublicationType_datexPublication_Management_cd_terminate_processingMgmt: ui_PublicationType_datexPublication_Management_cd = 6; consinfo_PublicationType_datexPublication_Management_cd.enumextbit = 0; break;
	case PublicationType_datexPublication_Management_cd_terminate_bandwidthMgmt: ui_PublicationType_datexPublication_Management_cd = 7; consinfo_PublicationType_datexPublication_Management_cd.enumextbit = 0; break;
	case PublicationType_datexPublication_Management_cd_terminate_accessDenied: ui_PublicationType_datexPublication_Management_cd = 8; consinfo_PublicationType_datexPublication_Management_cd.enumextbit = 0; break;
	case PublicationType_datexPublication_Management_cd_unknownRequest: ui_PublicationType_datexPublication_Management_cd = 9; consinfo_PublicationType_datexPublication_Management_cd.enumextbit = 0; break;
	default: ui_PublicationType_datexPublication_Management_cd = *value; consinfo_PublicationType_datexPublication_Management_cd.enumextbit = 1; break;
	}
	if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_PublicationType_datexPublication_Management_cd, &consinfo_PublicationType_datexPublication_Management_cd)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Enc_PublicationType_datexPublication_Management_cd(ASN1WorkSpace *workspace, PublicationType_datexPublication_Management_cd *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_PublicationType_datexPublication_Management_cd(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_PublicationType_datexPublication_Management_cd(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_PublicationType_datexPublication_Management_cd(ASN1WorkSpace *workspace, PublicationType_datexPublication_Management_cd *value)
{
	struct Asn1ConsInfo consinfo_PublicationType_datexPublication_Management_cd = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_PublicationType_datexPublication_Management_cd;
	if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_PublicationType_datexPublication_Management_cd, &consinfo_PublicationType_datexPublication_Management_cd)) < 0) return ret;
	if (consinfo_PublicationType_datexPublication_Management_cd.enumextbit == 0)
	{
		switch(ui_PublicationType_datexPublication_Management_cd)
		{
		case 0: *value = PublicationType_datexPublication_Management_cd_temporarilySuspended; break;
		case 1: *value = PublicationType_datexPublication_Management_cd_resume; break;
		case 2: *value = PublicationType_datexPublication_Management_cd_terminate_other; break;
		case 3: *value = PublicationType_datexPublication_Management_cd_terminate_dataNoLongerAvailable; break;
		case 4: *value = PublicationType_datexPublication_Management_cd_terminate_publicationsBeingRejected; break;
		case 5: *value = PublicationType_datexPublication_Management_cd_terminate_PendingShutdown; break;
		case 6: *value = PublicationType_datexPublication_Management_cd_terminate_processingMgmt; break;
		case 7: *value = PublicationType_datexPublication_Management_cd_terminate_bandwidthMgmt; break;
		case 8: *value = PublicationType_datexPublication_Management_cd_terminate_accessDenied; break;
		case 9: *value = PublicationType_datexPublication_Management_cd_unknownRequest; break;
		default: break;
		}
	}
	else
	{
		switch(ui_PublicationType_datexPublication_Management_cd)
		{
		default: *value = ui_PublicationType_datexPublication_Management_cd; break;
		}
	}
	return ret;
}
int ASN1_PER_Align_Dec_PublicationType_datexPublication_Management_cd(ASN1WorkSpace *workspace, PublicationType_datexPublication_Management_cd *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_PublicationType_datexPublication_Management_cd(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_PublicationType_datexPublication_Management_cd(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_PublicationType_datexPublication_Management_cd(ASN1WorkSpace *workspace, PublicationType_datexPublication_Management_cd *value)
{
	struct Asn1ConsInfo consinfo_PublicationType_datexPublication_Management_cd = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_PublicationType_datexPublication_Management_cd;
	switch(*value)
	{
	case PublicationType_datexPublication_Management_cd_temporarilySuspended: ui_PublicationType_datexPublication_Management_cd = 0; consinfo_PublicationType_datexPublication_Management_cd.enumextbit = 0; break;
	case PublicationType_datexPublication_Management_cd_resume: ui_PublicationType_datexPublication_Management_cd = 1; consinfo_PublicationType_datexPublication_Management_cd.enumextbit = 0; break;
	case PublicationType_datexPublication_Management_cd_terminate_other: ui_PublicationType_datexPublication_Management_cd = 2; consinfo_PublicationType_datexPublication_Management_cd.enumextbit = 0; break;
	case PublicationType_datexPublication_Management_cd_terminate_dataNoLongerAvailable: ui_PublicationType_datexPublication_Management_cd = 3; consinfo_PublicationType_datexPublication_Management_cd.enumextbit = 0; break;
	case PublicationType_datexPublication_Management_cd_terminate_publicationsBeingRejected: ui_PublicationType_datexPublication_Management_cd = 4; consinfo_PublicationType_datexPublication_Management_cd.enumextbit = 0; break;
	case PublicationType_datexPublication_Management_cd_terminate_PendingShutdown: ui_PublicationType_datexPublication_Management_cd = 5; consinfo_PublicationType_datexPublication_Management_cd.enumextbit = 0; break;
	case PublicationType_datexPublication_Management_cd_terminate_processingMgmt: ui_PublicationType_datexPublication_Management_cd = 6; consinfo_PublicationType_datexPublication_Management_cd.enumextbit = 0; break;
	case PublicationType_datexPublication_Management_cd_terminate_bandwidthMgmt: ui_PublicationType_datexPublication_Management_cd = 7; consinfo_PublicationType_datexPublication_Management_cd.enumextbit = 0; break;
	case PublicationType_datexPublication_Management_cd_terminate_accessDenied: ui_PublicationType_datexPublication_Management_cd = 8; consinfo_PublicationType_datexPublication_Management_cd.enumextbit = 0; break;
	case PublicationType_datexPublication_Management_cd_unknownRequest: ui_PublicationType_datexPublication_Management_cd = 9; consinfo_PublicationType_datexPublication_Management_cd.enumextbit = 0; break;
	default: ui_PublicationType_datexPublication_Management_cd = *value; consinfo_PublicationType_datexPublication_Management_cd.enumextbit = 1; break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_PublicationType_datexPublication_Management_cd, &consinfo_PublicationType_datexPublication_Management_cd)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Enc_PublicationType_datexPublication_Management_cd(ASN1WorkSpace *workspace, PublicationType_datexPublication_Management_cd *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_PublicationType_datexPublication_Management_cd(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_PublicationType_datexPublication_Management_cd(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_PublicationType_datexPublication_Management_cd(ASN1WorkSpace *workspace, PublicationType_datexPublication_Management_cd *value)
{
	struct Asn1ConsInfo consinfo_PublicationType_datexPublication_Management_cd = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_PublicationType_datexPublication_Management_cd;
	if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_PublicationType_datexPublication_Management_cd, &consinfo_PublicationType_datexPublication_Management_cd)) < 0) return ret;
	if (consinfo_PublicationType_datexPublication_Management_cd.enumextbit == 0)
	{
		switch(ui_PublicationType_datexPublication_Management_cd)
		{
		case 0: *value = PublicationType_datexPublication_Management_cd_temporarilySuspended; break;
		case 1: *value = PublicationType_datexPublication_Management_cd_resume; break;
		case 2: *value = PublicationType_datexPublication_Management_cd_terminate_other; break;
		case 3: *value = PublicationType_datexPublication_Management_cd_terminate_dataNoLongerAvailable; break;
		case 4: *value = PublicationType_datexPublication_Management_cd_terminate_publicationsBeingRejected; break;
		case 5: *value = PublicationType_datexPublication_Management_cd_terminate_PendingShutdown; break;
		case 6: *value = PublicationType_datexPublication_Management_cd_terminate_processingMgmt; break;
		case 7: *value = PublicationType_datexPublication_Management_cd_terminate_bandwidthMgmt; break;
		case 8: *value = PublicationType_datexPublication_Management_cd_terminate_accessDenied; break;
		case 9: *value = PublicationType_datexPublication_Management_cd_unknownRequest; break;
		default: break;
		}
	}
	else
	{
		switch(ui_PublicationType_datexPublication_Management_cd)
		{
		default: *value = ui_PublicationType_datexPublication_Management_cd; break;
		}
	}
	return ret;
}
int ASN1_PER_UNAlign_Dec_PublicationType_datexPublication_Management_cd(ASN1WorkSpace *workspace, PublicationType_datexPublication_Management_cd *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_PublicationType_datexPublication_Management_cd(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_PublicationType_datexPublication_Management_cd(value)) < 0) return ret;
	return ret;
}

/********************************************************
*PublicationType                                        *
********************************************************/
int ASN1_Print_PublicationType(PublicationType *value, int tab_value)
{
	int ret = 0;
	// CHOICE : t->tempIdentifier is Upper Letter
	ASN1_Print_CHOICE("PublicationType");
	if (value == NULL) return -1;
	switch (value->M) {
	case DEF_PublicationType_datexPublication_Management_cd:
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		switch(value->elements.datexPublication_Management_cd)
		{
		case 0: if ((ret = ASN1_Print_ENUMERATED("PublicationType_datexPublication-Management-cd", "temporarilySuspended", 0)) < 0) return ret; break;
		case 1: if ((ret = ASN1_Print_ENUMERATED("PublicationType_datexPublication-Management-cd", "resume", 1)) < 0) return ret; break;
		case 2: if ((ret = ASN1_Print_ENUMERATED("PublicationType_datexPublication-Management-cd", "terminate-other", 2)) < 0) return ret; break;
		case 3: if ((ret = ASN1_Print_ENUMERATED("PublicationType_datexPublication-Management-cd", "terminate-dataNoLongerAvailable", 3)) < 0) return ret; break;
		case 4: if ((ret = ASN1_Print_ENUMERATED("PublicationType_datexPublication-Management-cd", "terminate-publicationsBeingRejected", 4)) < 0) return ret; break;
		case 5: if ((ret = ASN1_Print_ENUMERATED("PublicationType_datexPublication-Management-cd", "terminate-PendingShutdown", 5)) < 0) return ret; break;
		case 6: if ((ret = ASN1_Print_ENUMERATED("PublicationType_datexPublication-Management-cd", "terminate-processingMgmt", 6)) < 0) return ret; break;
		case 7: if ((ret = ASN1_Print_ENUMERATED("PublicationType_datexPublication-Management-cd", "terminate-bandwidthMgmt", 7)) < 0) return ret; break;
		case 8: if ((ret = ASN1_Print_ENUMERATED("PublicationType_datexPublication-Management-cd", "terminate-accessDenied", 8)) < 0) return ret; break;
		case 9: if ((ret = ASN1_Print_ENUMERATED("PublicationType_datexPublication-Management-cd", "unknownRequest", 9)) < 0) return ret; break;
		default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
		};
		if (ret != 0) return -1;
		break;
	case DEF_PublicationType_datexPublish_Data:
		// Type Reference EndApplicationMessage
		if (Compare_Letter(tab_value, "datexPublish-Data")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("datexPublish-Data = ");
		}
		if ((ret = ASN1_Print_EndApplicationMessage((EndApplicationMessage *)value->elements.datexPublish_Data, tab_value + 1)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: return -1;
}
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_PublicationType_datexPublication_Management_cd(ASN1WorkSpace *workspace, PublicationType *value, ENUMERATED user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->M = DEF_PublicationType_datexPublication_Management_cd;
	if ((ret = ASN1_SET_ENUMERATED(workspace, (ASNINT32*)&value->elements.datexPublication_Management_cd, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_PublicationType_datexPublish_Data(ASN1WorkSpace *workspace, PublicationType *value, EndApplicationMessage *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->elements.datexPublish_Data = (EndApplicationMessage *)mpool_malloc(workspace->Pmemory, sizeof(EndApplicationMessage));
	memset(value->elements.datexPublish_Data, 0, sizeof(EndApplicationMessage));
	value->M = DEF_PublicationType_datexPublish_Data;
	memmove(value->elements.datexPublish_Data, user_value, sizeof(EndApplicationMessage));
	return ret;
}
int ASN1_GET_PublicationType_datexPublication_Management_cd(ASN1WorkSpace *workspace, PublicationType *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->M == DEF_PublicationType_datexPublication_Management_cd)
	{
		if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->elements.datexPublication_Management_cd, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_PublicationType_datexPublish_Data(ASN1WorkSpace *workspace, PublicationType *value, EndApplicationMessage **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->M == DEF_PublicationType_datexPublish_Data)
	{
		*user_value = value->elements.datexPublish_Data;
	}
	else return -2;
	return ret;
}
extern int ASN1_CHECK_EndApplicationMessage(EndApplicationMessage *value);
int ASN1_CHECK_PublicationType(PublicationType *value)
{
	int ret = 0;

	unsigned char checkinfo_datexPublication_Management_cd[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datexPublish_Data[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_PublicationType_datexPublication_Management_cd:
		if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&value->elements.datexPublication_Management_cd, checkinfo_datexPublication_Management_cd)) < 0) return ret;
		break;
	case DEF_PublicationType_datexPublish_Data:
		if ((ret = ASN1_CHECK_EndApplicationMessage(value->elements.datexPublish_Data)) < 0) return ret;
		break;
	default: break;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_PublicationType_datexPublication_Management_cd(ASN1WorkSpace *workspace, PublicationType_datexPublication_Management_cd *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_PublicationType(ASN1WorkSpace *workspace, PublicationType *value, ASN1TagType tagFlag)
{
	int ret = 0;
	switch(value->M)
	{
	case DEF_PublicationType_datexPublication_Management_cd:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_PublicationType_datexPublication_Management_cd(workspace, &(value->elements.datexPublication_Management_cd), ASN1IMPL)) < 0) return ret;
		break;
	case DEF_PublicationType_datexPublish_Data:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 1)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_EndApplicationMessage(workspace, value->elements.datexPublish_Data, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
		break;
	}
	return ret;
}
extern int ASN1_CHECK_PublicationType(PublicationType *value);
extern int ASN1_BER_Data_Enc_PublicationType(ASN1WorkSpace *workspace, PublicationType *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_PublicationType(ASN1WorkSpace *workspace, PublicationType *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_PublicationType(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_PublicationType(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_PublicationType_datexPublication_Management_cd(ASN1WorkSpace *workspace, PublicationType_datexPublication_Management_cd *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_PublicationType(ASN1WorkSpace *workspace, PublicationType *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	value->M = 0;
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	switch(tag)
	{
	case ITS_ASN_CONT | ITS_ASN_PRIM | 0:
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_PublicationType_datexPublication_Management_cd(workspace, &value->elements.datexPublication_Management_cd, len, ASN1IMPL)) < 0) return ret;
		value->M = DEF_PublicationType_datexPublication_Management_cd;
		break;
	case ITS_ASN_CONT | ITS_ASN_CONS | 1:
		value->elements.datexPublish_Data = (EndApplicationMessage *)mpool_malloc(workspace->Pmemory, sizeof(EndApplicationMessage));
		memset(value->elements.datexPublish_Data, 0, sizeof(EndApplicationMessage));
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 1)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_EndApplicationMessage(workspace, value->elements.datexPublish_Data, len, ASN1IMPL)) < 0) return ret;
		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->M = DEF_PublicationType_datexPublish_Data;
		break;
	}
	return ret;
}
extern int ASN1_CHECK_PublicationType(PublicationType *value);
extern int ASN1_BER_Data_Dec_PublicationType(ASN1WorkSpace *workspace, PublicationType *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_PublicationType(ASN1WorkSpace *workspace, PublicationType *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_PublicationType(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_PublicationType(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Enc_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value);
int ASN1_PER_Align_Data_Enc_PublicationType(ASN1WorkSpace *workspace, PublicationType *value)
{
	int ret = 0;
	ASNINT32 ui_datexPublication_Management_cd;
	struct Asn1ConsInfo consinfo_datexPublication_Management_cd = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexPublish_Data = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT64 ui;
	ASNBOOL extbit = 1;
	switch(value->M)
	{
	case DEF_PublicationType_datexPublication_Management_cd: ui = 0; extbit = 0; break;
	case DEF_PublicationType_datexPublish_Data: ui = 1; extbit = 0; break;
	default: break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_Choice_ENUMERATED(workspace, ui, extbit, 0, 2)) < 0) return ret;
	switch(value->M)
	{
	case DEF_PublicationType_datexPublication_Management_cd:
		switch(value->elements.datexPublication_Management_cd)
		{
		case PublicationType_datexPublication_Management_cd_temporarilySuspended: ui_datexPublication_Management_cd = 0; consinfo_datexPublication_Management_cd.enumextbit = 0; break;
		case PublicationType_datexPublication_Management_cd_resume: ui_datexPublication_Management_cd = 1; consinfo_datexPublication_Management_cd.enumextbit = 0; break;
		case PublicationType_datexPublication_Management_cd_terminate_other: ui_datexPublication_Management_cd = 2; consinfo_datexPublication_Management_cd.enumextbit = 0; break;
		case PublicationType_datexPublication_Management_cd_terminate_dataNoLongerAvailable: ui_datexPublication_Management_cd = 3; consinfo_datexPublication_Management_cd.enumextbit = 0; break;
		case PublicationType_datexPublication_Management_cd_terminate_publicationsBeingRejected: ui_datexPublication_Management_cd = 4; consinfo_datexPublication_Management_cd.enumextbit = 0; break;
		case PublicationType_datexPublication_Management_cd_terminate_PendingShutdown: ui_datexPublication_Management_cd = 5; consinfo_datexPublication_Management_cd.enumextbit = 0; break;
		case PublicationType_datexPublication_Management_cd_terminate_processingMgmt: ui_datexPublication_Management_cd = 6; consinfo_datexPublication_Management_cd.enumextbit = 0; break;
		case PublicationType_datexPublication_Management_cd_terminate_bandwidthMgmt: ui_datexPublication_Management_cd = 7; consinfo_datexPublication_Management_cd.enumextbit = 0; break;
		case PublicationType_datexPublication_Management_cd_terminate_accessDenied: ui_datexPublication_Management_cd = 8; consinfo_datexPublication_Management_cd.enumextbit = 0; break;
		case PublicationType_datexPublication_Management_cd_unknownRequest: ui_datexPublication_Management_cd = 9; consinfo_datexPublication_Management_cd.enumextbit = 0; break;
		default: ui_datexPublication_Management_cd = value->elements.datexPublication_Management_cd; consinfo_datexPublication_Management_cd.enumextbit = 1;break;
		}
		if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_datexPublication_Management_cd, &consinfo_datexPublication_Management_cd)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PublicationType_datexPublish_Data:
		if ((ret = ASN1_PER_Align_Enc_EndApplicationMessage(workspace, value->elements.datexPublish_Data)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: break;
	}
	return ret;
}
extern int ASN1_CHECK_PublicationType(PublicationType *value);
extern int ASN1_PER_Align_Data_Enc_PublicationType(ASN1WorkSpace *workspace, PublicationType *value);
int ASN1_PER_Align_Enc_PublicationType(ASN1WorkSpace *workspace, PublicationType *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_PublicationType(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_PublicationType(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Dec_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value);
int ASN1_PER_Align_Data_Dec_PublicationType(ASN1WorkSpace *workspace, PublicationType *value)
{
	int ret = 0;
	ASNINT32 ui_datexPublication_Management_cd;
	struct Asn1ConsInfo consinfo_datexPublication_Management_cd = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexPublish_Data = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	if ((ret = ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 2)) < 0) return ret;

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_PublicationType_datexPublication_Management_cd;
			break;
		case 1: index = DEF_PublicationType_datexPublish_Data;
			value->elements.datexPublish_Data = (EndApplicationMessage *)mpool_malloc(workspace->Pmemory, sizeof(EndApplicationMessage));
			memset(value->elements.datexPublish_Data, 0, sizeof(EndApplicationMessage));
			break;
		default: break;
		}
	}
	else
	{
		switch(ui)
		{
		default: break;
		}
	}
	if ((ret = ASN1_GetM(&value->M, index)) < 0) return ret;
	switch(index)
	{
	case DEF_PublicationType_datexPublication_Management_cd:
		if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_datexPublication_Management_cd, &consinfo_datexPublication_Management_cd)) < 0) return ret;
		if (consinfo_datexPublication_Management_cd.enumextbit == 0)
		{
			switch(ui_datexPublication_Management_cd)
			{
			case 0: value->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_temporarilySuspended; break;
			case 1: value->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_resume; break;
			case 2: value->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_terminate_other; break;
			case 3: value->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_terminate_dataNoLongerAvailable; break;
			case 4: value->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_terminate_publicationsBeingRejected; break;
			case 5: value->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_terminate_PendingShutdown; break;
			case 6: value->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_terminate_processingMgmt; break;
			case 7: value->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_terminate_bandwidthMgmt; break;
			case 8: value->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_terminate_accessDenied; break;
			case 9: value->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_unknownRequest; break;
			default: break;
			}
		}
		else
		{
			switch(ui_datexPublication_Management_cd)
			{
			default: value->elements.datexPublication_Management_cd = ui_datexPublication_Management_cd; break;
			}
		}
		if (ret != 0) return -1;
		break;
	case DEF_PublicationType_datexPublish_Data:
		if ((ret = ASN1_PER_Align_Dec_EndApplicationMessage(workspace, value->elements.datexPublish_Data)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, ALIGN); break;
	}
	return ret;
}
extern int ASN1_CHECK_PublicationType(PublicationType *value);
extern int ASN1_PER_Align_Data_Dec_PublicationType(ASN1WorkSpace *workspace, PublicationType *value);
int ASN1_PER_Align_Dec_PublicationType(ASN1WorkSpace *workspace, PublicationType *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_PublicationType(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_PublicationType(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Enc_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value);
int ASN1_PER_UNAlign_Data_Enc_PublicationType(ASN1WorkSpace *workspace, PublicationType *value)
{
	int ret = 0;
	ASNINT32 ui_datexPublication_Management_cd;
	struct Asn1ConsInfo consinfo_datexPublication_Management_cd = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexPublish_Data = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT64 ui;
	ASNBOOL extbit = 1;
	switch(value->M)
	{
	case DEF_PublicationType_datexPublication_Management_cd: ui = 0; extbit = 0; break;
	case DEF_PublicationType_datexPublish_Data: ui = 1; extbit = 0; break;
	default: break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_Choice_ENUMERATED(workspace, ui, extbit, 0, 2)) < 0) return ret;
	switch(value->M)
	{
	case DEF_PublicationType_datexPublication_Management_cd:
		switch(value->elements.datexPublication_Management_cd)
		{
		case PublicationType_datexPublication_Management_cd_temporarilySuspended: ui_datexPublication_Management_cd = 0; consinfo_datexPublication_Management_cd.enumextbit = 0; break;
		case PublicationType_datexPublication_Management_cd_resume: ui_datexPublication_Management_cd = 1; consinfo_datexPublication_Management_cd.enumextbit = 0; break;
		case PublicationType_datexPublication_Management_cd_terminate_other: ui_datexPublication_Management_cd = 2; consinfo_datexPublication_Management_cd.enumextbit = 0; break;
		case PublicationType_datexPublication_Management_cd_terminate_dataNoLongerAvailable: ui_datexPublication_Management_cd = 3; consinfo_datexPublication_Management_cd.enumextbit = 0; break;
		case PublicationType_datexPublication_Management_cd_terminate_publicationsBeingRejected: ui_datexPublication_Management_cd = 4; consinfo_datexPublication_Management_cd.enumextbit = 0; break;
		case PublicationType_datexPublication_Management_cd_terminate_PendingShutdown: ui_datexPublication_Management_cd = 5; consinfo_datexPublication_Management_cd.enumextbit = 0; break;
		case PublicationType_datexPublication_Management_cd_terminate_processingMgmt: ui_datexPublication_Management_cd = 6; consinfo_datexPublication_Management_cd.enumextbit = 0; break;
		case PublicationType_datexPublication_Management_cd_terminate_bandwidthMgmt: ui_datexPublication_Management_cd = 7; consinfo_datexPublication_Management_cd.enumextbit = 0; break;
		case PublicationType_datexPublication_Management_cd_terminate_accessDenied: ui_datexPublication_Management_cd = 8; consinfo_datexPublication_Management_cd.enumextbit = 0; break;
		case PublicationType_datexPublication_Management_cd_unknownRequest: ui_datexPublication_Management_cd = 9; consinfo_datexPublication_Management_cd.enumextbit = 0; break;
		default: ui_datexPublication_Management_cd = value->elements.datexPublication_Management_cd; consinfo_datexPublication_Management_cd.enumextbit = 1;break;
		}
		if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_datexPublication_Management_cd, &consinfo_datexPublication_Management_cd)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PublicationType_datexPublish_Data:
		if ((ret = ASN1_PER_UNAlign_Enc_EndApplicationMessage(workspace, value->elements.datexPublish_Data)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: break;
	}
	return ret;
}
extern int ASN1_CHECK_PublicationType(PublicationType *value);
extern int ASN1_PER_UNAlign_Data_Enc_PublicationType(ASN1WorkSpace *workspace, PublicationType *value);
int ASN1_PER_UNAlign_Enc_PublicationType(ASN1WorkSpace *workspace, PublicationType *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_PublicationType(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_PublicationType(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Dec_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value);
int ASN1_PER_UNAlign_Data_Dec_PublicationType(ASN1WorkSpace *workspace, PublicationType *value)
{
	int ret = 0;
	ASNINT32 ui_datexPublication_Management_cd;
	struct Asn1ConsInfo consinfo_datexPublication_Management_cd = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexPublish_Data = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	if ((ret = ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 2)) < 0) return ret;

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_PublicationType_datexPublication_Management_cd;
			break;
		case 1: index = DEF_PublicationType_datexPublish_Data;
			value->elements.datexPublish_Data = (EndApplicationMessage *)mpool_malloc(workspace->Pmemory, sizeof(EndApplicationMessage));
			memset(value->elements.datexPublish_Data, 0, sizeof(EndApplicationMessage));
			break;
		default: break;
		}
	}
	else
	{
		switch(ui)
		{
		default: break;
		}
	}
	if ((ret = ASN1_GetM(&value->M, index)) < 0) return ret;
	switch(index)
	{
	case DEF_PublicationType_datexPublication_Management_cd:
		if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_datexPublication_Management_cd, &consinfo_datexPublication_Management_cd)) < 0) return ret;
		if (consinfo_datexPublication_Management_cd.enumextbit == 0)
		{
			switch(ui_datexPublication_Management_cd)
			{
			case 0: value->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_temporarilySuspended; break;
			case 1: value->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_resume; break;
			case 2: value->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_terminate_other; break;
			case 3: value->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_terminate_dataNoLongerAvailable; break;
			case 4: value->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_terminate_publicationsBeingRejected; break;
			case 5: value->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_terminate_PendingShutdown; break;
			case 6: value->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_terminate_processingMgmt; break;
			case 7: value->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_terminate_bandwidthMgmt; break;
			case 8: value->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_terminate_accessDenied; break;
			case 9: value->elements.datexPublication_Management_cd = PublicationType_datexPublication_Management_cd_unknownRequest; break;
			default: break;
			}
		}
		else
		{
			switch(ui_datexPublication_Management_cd)
			{
			default: value->elements.datexPublication_Management_cd = ui_datexPublication_Management_cd; break;
			}
		}
		if (ret != 0) return -1;
		break;
	case DEF_PublicationType_datexPublish_Data:
		if ((ret = ASN1_PER_UNAlign_Dec_EndApplicationMessage(workspace, value->elements.datexPublish_Data)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
extern int ASN1_CHECK_PublicationType(PublicationType *value);
extern int ASN1_PER_UNAlign_Data_Dec_PublicationType(ASN1WorkSpace *workspace, PublicationType *value);
int ASN1_PER_UNAlign_Dec_PublicationType(ASN1WorkSpace *workspace, PublicationType *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_PublicationType(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_PublicationType(value)) < 0) return ret;
	return ret;
}

/********************************************************
*PublicationData                                        *
********************************************************/
int ASN1_Print_PublicationData(PublicationData *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("PublicationData");
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("datexPublish_SubscribeSerial_nbr", &(value->datexPublish_SubscribeSerial_nbr))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("datexPublish_Serial_nbr", &(value->datexPublish_Serial_nbr))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_BOOLEAN("datexPublish_LatePublicationFlag", &(value->datexPublish_LatePublicationFlag))) < 0) return ret;
	// Type Reference PublicationType
	if (Compare_Letter(tab_value, "datexPublish-Type")) {
		ASN_Print_TAB(tab_value + 1);
		asn_printf("datexPublish-Type = ");
	}
	if ((ret = ASN1_Print_PublicationType((PublicationType *)value->datexPublish_Type, tab_value + 1)) < 0) return ret;
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_PublicationData_datexPublish_SubscribeSerial_nbr(ASN1WorkSpace *workspace, PublicationData *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->datexPublish_SubscribeSerial_nbr, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_PublicationData_datexPublish_Serial_nbr(ASN1WorkSpace *workspace, PublicationData *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->datexPublish_Serial_nbr, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_PublicationData_datexPublish_LatePublicationFlag(ASN1WorkSpace *workspace, PublicationData *value, BOOLEAN user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_BOOLEAN(workspace, &value->datexPublish_LatePublicationFlag, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_PublicationData_datexPublish_Type(ASN1WorkSpace *workspace, PublicationData *value, PublicationType *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->datexPublish_Type = (PublicationType *)mpool_malloc(workspace->Pmemory, sizeof(PublicationType));
	memset(value->datexPublish_Type, 0, sizeof(PublicationType));
	memmove(value->datexPublish_Type, user_value, sizeof(PublicationType));
	return ret;
}
int ASN1_GET_PublicationData_datexPublish_SubscribeSerial_nbr(ASN1WorkSpace *workspace, PublicationData *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->datexPublish_SubscribeSerial_nbr, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_PublicationData_datexPublish_Serial_nbr(ASN1WorkSpace *workspace, PublicationData *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->datexPublish_Serial_nbr, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_PublicationData_datexPublish_LatePublicationFlag(ASN1WorkSpace *workspace, PublicationData *value, BOOLEAN *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_BOOLEAN(workspace, &value->datexPublish_LatePublicationFlag, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_PublicationData_datexPublish_Type(ASN1WorkSpace *workspace, PublicationData *value, PublicationType **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = value->datexPublish_Type;
	return ret;
}
extern int ASN1_CHECK_PublicationType(PublicationType *value);
int ASN1_CHECK_PublicationData(PublicationData *value)
{
	int ret = 0;

	unsigned char checkinfo_datexPublish_SubscribeSerial_nbr[] = { 
		0x02,0x00,0x85,0x00,0xFF,0xFF,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_datexPublish_Serial_nbr[] = { 
		0x02,0x00,0x85,0x00,0xFF,0xFF,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_datexPublish_LatePublicationFlag[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datexPublish_Type[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(&(value->datexPublish_SubscribeSerial_nbr), checkinfo_datexPublish_SubscribeSerial_nbr)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->datexPublish_Serial_nbr), checkinfo_datexPublish_Serial_nbr)) < 0) return ret;
	if ((ret = ASN1_CHECK_BOOLEAN(&(value->datexPublish_LatePublicationFlag), checkinfo_datexPublish_LatePublicationFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_PublicationType(value->datexPublish_Type)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Enc_PublicationType(ASN1WorkSpace *workspace, PublicationType *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_PublicationData(ASN1WorkSpace *workspace, PublicationData *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->datexPublish_SubscribeSerial_nbr), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->datexPublish_Serial_nbr), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_BOOLEAN(workspace, &(value->datexPublish_LatePublicationFlag), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 3)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_PublicationType(workspace, value->datexPublish_Type, ASN1EXPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_PublicationData(PublicationData *value);
extern int ASN1_BER_Data_Enc_PublicationData(ASN1WorkSpace *workspace, PublicationData *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_PublicationData(ASN1WorkSpace *workspace, PublicationData *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_PublicationData(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_PublicationData(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_PublicationType(ASN1WorkSpace *workspace, PublicationType *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_PublicationData(ASN1WorkSpace *workspace, PublicationData *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8 *_cpointer;
	value->datexPublish_Type = (PublicationType *)mpool_malloc(workspace->Pmemory, sizeof(PublicationType));
	memset(value->datexPublish_Type, 0, sizeof(PublicationType));
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->datexPublish_SubscribeSerial_nbr, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->datexPublish_Serial_nbr, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_BOOLEAN(workspace, &value->datexPublish_LatePublicationFlag, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 3)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_PublicationType(workspace, value->datexPublish_Type, len, ASN1EXPL)) < 0) return ret;
	if (IfFixedLength(len) == -1)
	{
		if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
	}
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_PublicationData(PublicationData *value);
extern int ASN1_BER_Data_Dec_PublicationData(ASN1WorkSpace *workspace, PublicationData *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_PublicationData(ASN1WorkSpace *workspace, PublicationData *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_PublicationData(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_PublicationData(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Enc_PublicationType(ASN1WorkSpace *workspace, PublicationType *value);
int ASN1_PER_Align_Data_Enc_PublicationData(ASN1WorkSpace *workspace, PublicationData *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexPublish_SubscribeSerial_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexPublish_Serial_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexPublish_LatePublicationFlag = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexPublish_Type = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->datexPublish_SubscribeSerial_nbr), &consinfo_datexPublish_SubscribeSerial_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->datexPublish_Serial_nbr), &consinfo_datexPublish_Serial_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_BOOLEAN(workspace, &(value->datexPublish_LatePublicationFlag), &consinfo_datexPublish_LatePublicationFlag)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_PublicationType(workspace, value->datexPublish_Type)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_PublicationData(PublicationData *value);
extern int ASN1_PER_Align_Data_Enc_PublicationData(ASN1WorkSpace *workspace, PublicationData *value);
int ASN1_PER_Align_Enc_PublicationData(ASN1WorkSpace *workspace, PublicationData *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_PublicationData(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_PublicationData(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Dec_PublicationType(ASN1WorkSpace *workspace, PublicationType *value);
int ASN1_PER_Align_Data_Dec_PublicationData(ASN1WorkSpace *workspace, PublicationData *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexPublish_SubscribeSerial_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexPublish_Serial_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexPublish_LatePublicationFlag = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexPublish_Type = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	value->datexPublish_Type = (PublicationType *)mpool_malloc(workspace->Pmemory, sizeof(PublicationType));
	memset(value->datexPublish_Type, 0, sizeof(PublicationType));
	if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->datexPublish_SubscribeSerial_nbr), &consinfo_datexPublish_SubscribeSerial_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->datexPublish_Serial_nbr), &consinfo_datexPublish_Serial_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_BOOLEAN(workspace, &(value->datexPublish_LatePublicationFlag), &consinfo_datexPublish_LatePublicationFlag)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_PublicationType(workspace, value->datexPublish_Type)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_PublicationData(PublicationData *value);
extern int ASN1_PER_Align_Data_Dec_PublicationData(ASN1WorkSpace *workspace, PublicationData *value);
int ASN1_PER_Align_Dec_PublicationData(ASN1WorkSpace *workspace, PublicationData *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_PublicationData(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_PublicationData(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Enc_PublicationType(ASN1WorkSpace *workspace, PublicationType *value);
int ASN1_PER_UNAlign_Data_Enc_PublicationData(ASN1WorkSpace *workspace, PublicationData *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexPublish_SubscribeSerial_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexPublish_Serial_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexPublish_LatePublicationFlag = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexPublish_Type = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->datexPublish_SubscribeSerial_nbr), &consinfo_datexPublish_SubscribeSerial_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->datexPublish_Serial_nbr), &consinfo_datexPublish_Serial_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_BOOLEAN(workspace, &(value->datexPublish_LatePublicationFlag), &consinfo_datexPublish_LatePublicationFlag)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_PublicationType(workspace, value->datexPublish_Type)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_PublicationData(PublicationData *value);
extern int ASN1_PER_UNAlign_Data_Enc_PublicationData(ASN1WorkSpace *workspace, PublicationData *value);
int ASN1_PER_UNAlign_Enc_PublicationData(ASN1WorkSpace *workspace, PublicationData *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_PublicationData(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_PublicationData(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Dec_PublicationType(ASN1WorkSpace *workspace, PublicationType *value);
int ASN1_PER_UNAlign_Data_Dec_PublicationData(ASN1WorkSpace *workspace, PublicationData *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexPublish_SubscribeSerial_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexPublish_Serial_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexPublish_LatePublicationFlag = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexPublish_Type = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	value->datexPublish_Type = (PublicationType *)mpool_malloc(workspace->Pmemory, sizeof(PublicationType));
	memset(value->datexPublish_Type, 0, sizeof(PublicationType));
	if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->datexPublish_SubscribeSerial_nbr), &consinfo_datexPublish_SubscribeSerial_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->datexPublish_Serial_nbr), &consinfo_datexPublish_Serial_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_BOOLEAN(workspace, &(value->datexPublish_LatePublicationFlag), &consinfo_datexPublish_LatePublicationFlag)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_PublicationType(workspace, value->datexPublish_Type)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_PublicationData(PublicationData *value);
extern int ASN1_PER_UNAlign_Data_Dec_PublicationData(ASN1WorkSpace *workspace, PublicationData *value);
int ASN1_PER_UNAlign_Dec_PublicationData(ASN1WorkSpace *workspace, PublicationData *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_PublicationData(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_PublicationData(value)) < 0) return ret;
	return ret;
}

/********************************************************
*Publish_Format_datexPublish_Data                       *
********************************************************/
int ASN1_Print_Publish_Format_datexPublish_Data(Publish_Format_datexPublish_Data *value, int tab_value)
{
	int ret = 0;
	int count;
	ASN1ListNode *pnode;
	if (value == NULL) return -1;
	count = value->count;
	pnode = value->head->next;
	// SEQUENCE OF : default
	ASN1_Print_SEQ_OF(" ");
	while(count) {
		// Type Reference PublicationData
		ASN_Print_TAB(tab_value + 1);
		if ((ret = ASN1_Print_PublicationData((PublicationData *)pnode->data, tab_value + 1)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}

	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
extern int ASN1_CHECK_PublicationData(PublicationData *value);
int ASN1_CHECK_Publish_Format_datexPublish_Data(Publish_Format_datexPublish_Data *value)
{
	int ret = 0;

	unsigned char checkinfo_Publish_Format_datexPublish_Data[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_Publish_Format_datexPublish_Data_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		if ((ret = ASN1_CHECK_PublicationData(pnode->data)) < 0) return ret;
		pnode = pnode->next;
		count--;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_PublicationData(ASN1WorkSpace *workspace, PublicationData *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value, ASN1TagType tagFlag)
{
	int ret = 0;
	ASN1ListNode *pnode;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	pnode = value->head->next;
	while (NULL != pnode)
	{
		if ((ret = ASN1_BER_Data_Enc_PublicationData(workspace, pnode->data, ASN1EXPL)) < 0) return ret;
		pnode = pnode->next;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Publish_Format_datexPublish_Data(Publish_Format_datexPublish_Data *value);
extern int ASN1_BER_Data_Enc_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_Publish_Format_datexPublish_Data(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Publish_Format_datexPublish_Data(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_PublicationData(ASN1WorkSpace *workspace, PublicationData *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	PublicationData *pdata;
	ASNUINT8 *p = workspace->buffer.current;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	if ((ret = ASN1_Creat_Init_List(workspace, value)) < 0) return ret;
	while (ASN1_BER_Dec_Isloop(workspace, p, length))
	{
		pdata = (PublicationData *)mpool_malloc(GetMemPool(workspace), sizeof(PublicationData));
		memset(pdata, 0, sizeof(PublicationData));
		if ((ret = ASN1_BER_Data_Dec_PublicationData(workspace, pdata, len, ASN1EXPL)) < 0) return ret;
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
extern int ASN1_CHECK_Publish_Format_datexPublish_Data(Publish_Format_datexPublish_Data *value);
extern int ASN1_BER_Data_Dec_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Publish_Format_datexPublish_Data(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_Publish_Format_datexPublish_Data(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Enc_PublicationData(ASN1WorkSpace *workspace, PublicationData *value);
int ASN1_PER_Align_Data_Enc_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_Publish_Format_datexPublish_Data = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_Publish_Format_datexPublish_Data_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 all_length = value->count;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	ASN1ListNode *pnode = value->head->next;
	while(loop_set)
	{
		loop_set = ASN1_PER_Align_Enc_Set_Seq_Of_Length(workspace, &all_length, &process_length, &consinfo_Publish_Format_datexPublish_Data);
		for(i = 0; i < process_length; i++)
		{
			if ((ret = ASN1_PER_Align_Enc_PublicationData(workspace, pnode->data)) < 0) return ret;
			pnode = pnode->next;
		}
	}
	if (value->count != 0 && value->count % 16384 == 0)
	{
		if ((ret = ASN1_PER_Align_WirteBuffer(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Publish_Format_datexPublish_Data(Publish_Format_datexPublish_Data *value);
extern int ASN1_PER_Align_Data_Enc_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value);
int ASN1_PER_Align_Enc_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Publish_Format_datexPublish_Data(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_Publish_Format_datexPublish_Data(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Dec_PublicationData(ASN1WorkSpace *workspace, PublicationData *value);
int ASN1_PER_Align_Data_Dec_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_Publish_Format_datexPublish_Data = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_Publish_Format_datexPublish_Data_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	PublicationData *pdata;
	if ((ret = ASN1_Creat_Init_List(workspace, value)) < 0) return ret;
	while(loop_set)
	{
		loop_set = ASN1_PER_Align_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_Publish_Format_datexPublish_Data);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (PublicationData *)mpool_calloc(GetMemPool(workspace), sizeof(PublicationData), 1)) == NULL) return -1;
			if ((ret = ASN1_PER_Align_Dec_PublicationData(workspace, pdata)) < 0) return ret;
			if ((ret = ASN1_Insert_Node(workspace, value, (void *)pdata)) < 0) return ret;
		}
	}

	return ret;
}
extern int ASN1_CHECK_Publish_Format_datexPublish_Data(Publish_Format_datexPublish_Data *value);
extern int ASN1_PER_Align_Data_Dec_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value);
int ASN1_PER_Align_Dec_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_Publish_Format_datexPublish_Data(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Publish_Format_datexPublish_Data(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Enc_PublicationData(ASN1WorkSpace *workspace, PublicationData *value);
int ASN1_PER_UNAlign_Data_Enc_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_Publish_Format_datexPublish_Data = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_Publish_Format_datexPublish_Data_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 all_length = value->count;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	ASN1ListNode *pnode = value->head->next;
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Enc_Set_Seq_Of_Length(workspace, &all_length, &process_length, &consinfo_Publish_Format_datexPublish_Data);
		for(i = 0; i < process_length; i++)
		{
			if ((ret = ASN1_PER_UNAlign_Enc_PublicationData(workspace, pnode->data)) < 0) return ret;
			pnode = pnode->next;
		}
	}
	if (value->count != 0 && value->count % 16384 == 0)
	{
		if ((ret = ASN1_PER_UNAlign_WirteBuffer(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Publish_Format_datexPublish_Data(Publish_Format_datexPublish_Data *value);
extern int ASN1_PER_UNAlign_Data_Enc_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value);
int ASN1_PER_UNAlign_Enc_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Publish_Format_datexPublish_Data(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_Publish_Format_datexPublish_Data(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Dec_PublicationData(ASN1WorkSpace *workspace, PublicationData *value);
int ASN1_PER_UNAlign_Data_Dec_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_Publish_Format_datexPublish_Data = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_Publish_Format_datexPublish_Data_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	PublicationData *pdata;
	if ((ret = ASN1_Creat_Init_List(workspace, value)) < 0) return ret;
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_Publish_Format_datexPublish_Data);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (PublicationData *)mpool_calloc(GetMemPool(workspace), sizeof(PublicationData), 1)) == NULL) return -1;
			if ((ret = ASN1_PER_UNAlign_Dec_PublicationData(workspace, pdata)) < 0) return ret;
			if ((ret = ASN1_Insert_Node(workspace, value, (void *)pdata)) < 0) return ret;
		}
	}

	return ret;
}
extern int ASN1_CHECK_Publish_Format_datexPublish_Data(Publish_Format_datexPublish_Data *value);
extern int ASN1_PER_UNAlign_Data_Dec_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value);
int ASN1_PER_UNAlign_Dec_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_Publish_Format_datexPublish_Data(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Publish_Format_datexPublish_Data(value)) < 0) return ret;
	return ret;
}

/********************************************************
*Publish_Format                                         *
********************************************************/
int ASN1_Print_Publish_Format(Publish_Format *value, int tab_value)
{
	int ret = 0;
	// CHOICE : t->tempIdentifier is Upper Letter
	ASN1_Print_CHOICE("Publish-Format");
	if (value == NULL) return -1;
	switch (value->M) {
	case DEF_Publish_Format_datexPublish_Data:
		// Type Reference Publish_Format_datexPublish_Data
		if (Compare_Letter(tab_value, "datexPublish-Data")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("datexPublish-Data = ");
		}
		if ((ret = ASN1_Print_Publish_Format_datexPublish_Data((Publish_Format_datexPublish_Data *)&value->elements.datexPublish_Data, tab_value + 1)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_Publish_Format_datexPublish_FileName_txt:
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_UTF8Str("datexPublish_FileName_txt", &value->elements.datexPublish_FileName_txt)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: return -1;
}
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format *value, Publish_Format_datexPublish_Data *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->M = DEF_Publish_Format_datexPublish_Data;
	memmove(&value->elements.datexPublish_Data, user_value, sizeof(Publish_Format_datexPublish_Data));
	return ret;
}
int ASN1_SET_Publish_Format_datexPublish_FileName_txt(ASN1WorkSpace *workspace, Publish_Format *value, ASNUINT8 *user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->M = DEF_Publish_Format_datexPublish_FileName_txt;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->elements.datexPublish_FileName_txt, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format *value, Publish_Format_datexPublish_Data **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->M == DEF_Publish_Format_datexPublish_Data)
	{
		*user_value = &value->elements.datexPublish_Data;
	}
	else return -2;
	return ret;
}
int ASN1_GET_Publish_Format_datexPublish_FileName_txt(ASN1WorkSpace *workspace, Publish_Format *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->M == DEF_Publish_Format_datexPublish_FileName_txt)
	{
		if ((ret = ASN1_GET_UTF8Str(workspace, &value->elements.datexPublish_FileName_txt, user_value, user_value_length)) < 0) return ret;
	}
	else return -2;
	return ret;
}
extern int ASN1_CHECK_Publish_Format_datexPublish_Data(Publish_Format_datexPublish_Data *value);
int ASN1_CHECK_Publish_Format(Publish_Format *value)
{
	int ret = 0;

	unsigned char checkinfo_datexPublish_Data[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datexPublish_FileName_txt[] = { 
		0x02,0x00,0x82,0x07,0xD0,0x00
	};

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_Publish_Format_datexPublish_Data:
		if ((ret = ASN1_CHECK_Publish_Format_datexPublish_Data(&value->elements.datexPublish_Data)) < 0) return ret;
		break;
	case DEF_Publish_Format_datexPublish_FileName_txt:
		if ((ret = ASN1_CHECK_UTF8Str(&value->elements.datexPublish_FileName_txt, checkinfo_datexPublish_FileName_txt)) < 0) return ret;
		break;
	default: break;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value, ASN1TagType tagFlag)
{
	int ret = 0;
	switch(value->M)
	{
	case DEF_Publish_Format_datexPublish_Data:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 0)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_Publish_Format_datexPublish_Data(workspace, &(value->elements.datexPublish_Data), ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
		break;
	case DEF_Publish_Format_datexPublish_FileName_txt:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->elements.datexPublish_FileName_txt), ASN1IMPL)) < 0) return ret;
		break;
	}
	return ret;
}
extern int ASN1_CHECK_Publish_Format(Publish_Format *value);
extern int ASN1_BER_Data_Enc_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_Publish_Format(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Publish_Format(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	value->M = 0;
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	switch(tag)
	{
	case ITS_ASN_CONT | ITS_ASN_CONS | 0:
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 0)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_Publish_Format_datexPublish_Data(workspace, &value->elements.datexPublish_Data, len, ASN1IMPL)) < 0) return ret;
		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->M = DEF_Publish_Format_datexPublish_Data;
		break;
	case ITS_ASN_CONT | ITS_ASN_PRIM | 1:
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->elements.datexPublish_FileName_txt, len, ASN1IMPL)) < 0) return ret;
		value->M = DEF_Publish_Format_datexPublish_FileName_txt;
		break;
	}
	return ret;
}
extern int ASN1_CHECK_Publish_Format(Publish_Format *value);
extern int ASN1_BER_Data_Dec_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Publish_Format(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_Publish_Format(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Enc_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value);
int ASN1_PER_Align_Data_Enc_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexPublish_Data = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexPublish_FileName_txt = { ASN1_CONST64(0), ASN1_CONST64(2000), NULL, 0, CONS, 0, 0 };

	ASNINT64 ui;
	ASNBOOL extbit = 1;
	switch(value->M)
	{
	case DEF_Publish_Format_datexPublish_Data: ui = 0; extbit = 0; break;
	case DEF_Publish_Format_datexPublish_FileName_txt: ui = 1; extbit = 0; break;
	default: break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_Choice_ENUMERATED(workspace, ui, extbit, 0, 2)) < 0) return ret;
	switch(value->M)
	{
	case DEF_Publish_Format_datexPublish_Data:
		if ((ret = ASN1_PER_Align_Enc_Publish_Format_datexPublish_Data(workspace, &(value->elements.datexPublish_Data))) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_Publish_Format_datexPublish_FileName_txt:
		if ((ret = ASN1_PER_Align_Enc_UTF8Str(workspace, &(value->elements.datexPublish_FileName_txt), &consinfo_datexPublish_FileName_txt)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: break;
	}
	return ret;
}
extern int ASN1_CHECK_Publish_Format(Publish_Format *value);
extern int ASN1_PER_Align_Data_Enc_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value);
int ASN1_PER_Align_Enc_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Publish_Format(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_Publish_Format(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Dec_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value);
int ASN1_PER_Align_Data_Dec_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexPublish_Data = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexPublish_FileName_txt = { ASN1_CONST64(0), ASN1_CONST64(2000), NULL, 0, CONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	if ((ret = ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 2)) < 0) return ret;

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_Publish_Format_datexPublish_Data;
			break;
		case 1: index = DEF_Publish_Format_datexPublish_FileName_txt;
			break;
		default: break;
		}
	}
	else
	{
		switch(ui)
		{
		default: break;
		}
	}
	if ((ret = ASN1_GetM(&value->M, index)) < 0) return ret;
	switch(index)
	{
	case DEF_Publish_Format_datexPublish_Data:
		if ((ret = ASN1_PER_Align_Dec_Publish_Format_datexPublish_Data(workspace, &(value->elements.datexPublish_Data))) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_Publish_Format_datexPublish_FileName_txt:
		if ((ret = ASN1_PER_Align_Dec_UTF8Str(workspace, &(value->elements.datexPublish_FileName_txt), &consinfo_datexPublish_FileName_txt)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, ALIGN); break;
	}
	return ret;
}
extern int ASN1_CHECK_Publish_Format(Publish_Format *value);
extern int ASN1_PER_Align_Data_Dec_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value);
int ASN1_PER_Align_Dec_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_Publish_Format(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Publish_Format(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Enc_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value);
int ASN1_PER_UNAlign_Data_Enc_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexPublish_Data = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexPublish_FileName_txt = { ASN1_CONST64(0), ASN1_CONST64(2000), NULL, 0, CONS, 0, 0 };

	ASNINT64 ui;
	ASNBOOL extbit = 1;
	switch(value->M)
	{
	case DEF_Publish_Format_datexPublish_Data: ui = 0; extbit = 0; break;
	case DEF_Publish_Format_datexPublish_FileName_txt: ui = 1; extbit = 0; break;
	default: break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_Choice_ENUMERATED(workspace, ui, extbit, 0, 2)) < 0) return ret;
	switch(value->M)
	{
	case DEF_Publish_Format_datexPublish_Data:
		if ((ret = ASN1_PER_UNAlign_Enc_Publish_Format_datexPublish_Data(workspace, &(value->elements.datexPublish_Data))) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_Publish_Format_datexPublish_FileName_txt:
		if ((ret = ASN1_PER_UNAlign_Enc_UTF8Str(workspace, &(value->elements.datexPublish_FileName_txt), &consinfo_datexPublish_FileName_txt)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: break;
	}
	return ret;
}
extern int ASN1_CHECK_Publish_Format(Publish_Format *value);
extern int ASN1_PER_UNAlign_Data_Enc_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value);
int ASN1_PER_UNAlign_Enc_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Publish_Format(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_Publish_Format(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Dec_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value);
int ASN1_PER_UNAlign_Data_Dec_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexPublish_Data = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexPublish_FileName_txt = { ASN1_CONST64(0), ASN1_CONST64(2000), NULL, 0, CONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	if ((ret = ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 2)) < 0) return ret;

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_Publish_Format_datexPublish_Data;
			break;
		case 1: index = DEF_Publish_Format_datexPublish_FileName_txt;
			break;
		default: break;
		}
	}
	else
	{
		switch(ui)
		{
		default: break;
		}
	}
	if ((ret = ASN1_GetM(&value->M, index)) < 0) return ret;
	switch(index)
	{
	case DEF_Publish_Format_datexPublish_Data:
		if ((ret = ASN1_PER_UNAlign_Dec_Publish_Format_datexPublish_Data(workspace, &(value->elements.datexPublish_Data))) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_Publish_Format_datexPublish_FileName_txt:
		if ((ret = ASN1_PER_UNAlign_Dec_UTF8Str(workspace, &(value->elements.datexPublish_FileName_txt), &consinfo_datexPublish_FileName_txt)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
extern int ASN1_CHECK_Publish_Format(Publish_Format *value);
extern int ASN1_PER_UNAlign_Data_Dec_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value);
int ASN1_PER_UNAlign_Dec_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_Publish_Format(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Publish_Format(value)) < 0) return ret;
	return ret;
}

/********************************************************
*Publication                                            *
********************************************************/
int ASN1_Print_Publication(Publication *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("Publication");
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_BOOLEAN("datexPublish_Guaranteed_bool", &(value->datexPublish_Guaranteed_bool))) < 0) return ret;
	// Type Reference Publish_Format
	if (Compare_Letter(tab_value, "datexPublish-Format")) {
		ASN_Print_TAB(tab_value + 1);
		asn_printf("datexPublish-Format = ");
	}
	if ((ret = ASN1_Print_Publish_Format((Publish_Format *)value->datexPublish_Format, tab_value + 1)) < 0) return ret;
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_Publication_datexPublish_Guaranteed_bool(ASN1WorkSpace *workspace, Publication *value, BOOLEAN user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_BOOLEAN(workspace, &value->datexPublish_Guaranteed_bool, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_Publication_datexPublish_Format(ASN1WorkSpace *workspace, Publication *value, Publish_Format *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->datexPublish_Format = (Publish_Format *)mpool_malloc(workspace->Pmemory, sizeof(Publish_Format));
	memset(value->datexPublish_Format, 0, sizeof(Publish_Format));
	memmove(value->datexPublish_Format, user_value, sizeof(Publish_Format));
	return ret;
}
int ASN1_GET_Publication_datexPublish_Guaranteed_bool(ASN1WorkSpace *workspace, Publication *value, BOOLEAN *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_BOOLEAN(workspace, &value->datexPublish_Guaranteed_bool, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_Publication_datexPublish_Format(ASN1WorkSpace *workspace, Publication *value, Publish_Format **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = value->datexPublish_Format;
	return ret;
}
extern int ASN1_CHECK_Publish_Format(Publish_Format *value);
int ASN1_CHECK_Publication(Publication *value)
{
	int ret = 0;

	unsigned char checkinfo_datexPublish_Guaranteed_bool[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datexPublish_Format[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_BOOLEAN(&(value->datexPublish_Guaranteed_bool), checkinfo_datexPublish_Guaranteed_bool)) < 0) return ret;
	if ((ret = ASN1_CHECK_Publish_Format(value->datexPublish_Format)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Enc_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_Publication(ASN1WorkSpace *workspace, Publication *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_BOOLEAN(workspace, &(value->datexPublish_Guaranteed_bool), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Publish_Format(workspace, value->datexPublish_Format, ASN1EXPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Publication(Publication *value);
extern int ASN1_BER_Data_Enc_Publication(ASN1WorkSpace *workspace, Publication *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_Publication(ASN1WorkSpace *workspace, Publication *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_Publication(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Publication(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_Publication(ASN1WorkSpace *workspace, Publication *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8 *_cpointer;
	value->datexPublish_Format = (Publish_Format *)mpool_malloc(workspace->Pmemory, sizeof(Publish_Format));
	memset(value->datexPublish_Format, 0, sizeof(Publish_Format));
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_BOOLEAN(workspace, &value->datexPublish_Guaranteed_bool, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Publish_Format(workspace, value->datexPublish_Format, len, ASN1EXPL)) < 0) return ret;
	if (IfFixedLength(len) == -1)
	{
		if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
	}
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_Publication(Publication *value);
extern int ASN1_BER_Data_Dec_Publication(ASN1WorkSpace *workspace, Publication *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_Publication(ASN1WorkSpace *workspace, Publication *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Publication(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_Publication(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Enc_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value);
int ASN1_PER_Align_Data_Enc_Publication(ASN1WorkSpace *workspace, Publication *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexPublish_Guaranteed_bool = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexPublish_Format = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_Align_Enc_BOOLEAN(workspace, &(value->datexPublish_Guaranteed_bool), &consinfo_datexPublish_Guaranteed_bool)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_Publish_Format(workspace, value->datexPublish_Format)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_Publication(Publication *value);
extern int ASN1_PER_Align_Data_Enc_Publication(ASN1WorkSpace *workspace, Publication *value);
int ASN1_PER_Align_Enc_Publication(ASN1WorkSpace *workspace, Publication *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Publication(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_Publication(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Dec_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value);
int ASN1_PER_Align_Data_Dec_Publication(ASN1WorkSpace *workspace, Publication *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexPublish_Guaranteed_bool = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexPublish_Format = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	value->datexPublish_Format = (Publish_Format *)mpool_malloc(workspace->Pmemory, sizeof(Publish_Format));
	memset(value->datexPublish_Format, 0, sizeof(Publish_Format));
	if ((ret = ASN1_PER_Align_Dec_BOOLEAN(workspace, &(value->datexPublish_Guaranteed_bool), &consinfo_datexPublish_Guaranteed_bool)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_Publish_Format(workspace, value->datexPublish_Format)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_Publication(Publication *value);
extern int ASN1_PER_Align_Data_Dec_Publication(ASN1WorkSpace *workspace, Publication *value);
int ASN1_PER_Align_Dec_Publication(ASN1WorkSpace *workspace, Publication *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_Publication(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Publication(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Enc_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value);
int ASN1_PER_UNAlign_Data_Enc_Publication(ASN1WorkSpace *workspace, Publication *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexPublish_Guaranteed_bool = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexPublish_Format = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_UNAlign_Enc_BOOLEAN(workspace, &(value->datexPublish_Guaranteed_bool), &consinfo_datexPublish_Guaranteed_bool)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_Publish_Format(workspace, value->datexPublish_Format)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_Publication(Publication *value);
extern int ASN1_PER_UNAlign_Data_Enc_Publication(ASN1WorkSpace *workspace, Publication *value);
int ASN1_PER_UNAlign_Enc_Publication(ASN1WorkSpace *workspace, Publication *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Publication(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_Publication(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Dec_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value);
int ASN1_PER_UNAlign_Data_Dec_Publication(ASN1WorkSpace *workspace, Publication *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexPublish_Guaranteed_bool = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexPublish_Format = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	value->datexPublish_Format = (Publish_Format *)mpool_malloc(workspace->Pmemory, sizeof(Publish_Format));
	memset(value->datexPublish_Format, 0, sizeof(Publish_Format));
	if ((ret = ASN1_PER_UNAlign_Dec_BOOLEAN(workspace, &(value->datexPublish_Guaranteed_bool), &consinfo_datexPublish_Guaranteed_bool)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_Publish_Format(workspace, value->datexPublish_Format)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_Publication(Publication *value);
extern int ASN1_PER_UNAlign_Data_Dec_Publication(ASN1WorkSpace *workspace, Publication *value);
int ASN1_PER_UNAlign_Dec_Publication(ASN1WorkSpace *workspace, Publication *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_Publication(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Publication(value)) < 0) return ret;
	return ret;
}

/********************************************************
*TransferDone                                           *
********************************************************/
int ASN1_Print_TransferDone(TransferDone *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("TransferDone");
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_UTF8Str("datexTransferDone_FileName_txt", &(value->datexTransferDone_FileName_txt))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_BOOLEAN("datexTransferDone_Success_bool", &(value->datexTransferDone_Success_bool))) < 0) return ret;
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_TransferDone_datexTransferDone_FileName_txt(ASN1WorkSpace *workspace, TransferDone *value, ASNUINT8 *user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_UTF8Str(workspace, &value->datexTransferDone_FileName_txt, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_TransferDone_datexTransferDone_Success_bool(ASN1WorkSpace *workspace, TransferDone *value, BOOLEAN user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_BOOLEAN(workspace, &value->datexTransferDone_Success_bool, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_TransferDone_datexTransferDone_FileName_txt(ASN1WorkSpace *workspace, TransferDone *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_UTF8Str(workspace, &value->datexTransferDone_FileName_txt, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_TransferDone_datexTransferDone_Success_bool(ASN1WorkSpace *workspace, TransferDone *value, BOOLEAN *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_BOOLEAN(workspace, &value->datexTransferDone_Success_bool, user_value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_TransferDone(TransferDone *value)
{
	int ret = 0;

	unsigned char checkinfo_datexTransferDone_FileName_txt[] = { 
		0x02,0x00,0x82,0x07,0xD0,0x00
	};
	unsigned char checkinfo_datexTransferDone_Success_bool[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_UTF8Str(&(value->datexTransferDone_FileName_txt), checkinfo_datexTransferDone_FileName_txt)) < 0) return ret;
	if ((ret = ASN1_CHECK_BOOLEAN(&(value->datexTransferDone_Success_bool), checkinfo_datexTransferDone_Success_bool)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_TransferDone(ASN1WorkSpace *workspace, TransferDone *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_UTF8Str(workspace, &(value->datexTransferDone_FileName_txt), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_BOOLEAN(workspace, &(value->datexTransferDone_Success_bool), ASN1IMPL)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_TransferDone(TransferDone *value);
extern int ASN1_BER_Data_Enc_TransferDone(ASN1WorkSpace *workspace, TransferDone *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_TransferDone(ASN1WorkSpace *workspace, TransferDone *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_TransferDone(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_TransferDone(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_TransferDone(ASN1WorkSpace *workspace, TransferDone *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8 *_cpointer;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_UTF8Str(workspace, &value->datexTransferDone_FileName_txt, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_BOOLEAN(workspace, &value->datexTransferDone_Success_bool, len, ASN1IMPL)) < 0) return ret;
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_TransferDone(TransferDone *value);
extern int ASN1_BER_Data_Dec_TransferDone(ASN1WorkSpace *workspace, TransferDone *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_TransferDone(ASN1WorkSpace *workspace, TransferDone *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_TransferDone(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_TransferDone(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_TransferDone(ASN1WorkSpace *workspace, TransferDone *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexTransferDone_FileName_txt = { ASN1_CONST64(0), ASN1_CONST64(2000), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexTransferDone_Success_bool = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_Align_Enc_UTF8Str(workspace, &(value->datexTransferDone_FileName_txt), &consinfo_datexTransferDone_FileName_txt)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_BOOLEAN(workspace, &(value->datexTransferDone_Success_bool), &consinfo_datexTransferDone_Success_bool)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_TransferDone(TransferDone *value);
extern int ASN1_PER_Align_Data_Enc_TransferDone(ASN1WorkSpace *workspace, TransferDone *value);
int ASN1_PER_Align_Enc_TransferDone(ASN1WorkSpace *workspace, TransferDone *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_TransferDone(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_TransferDone(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_TransferDone(ASN1WorkSpace *workspace, TransferDone *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexTransferDone_FileName_txt = { ASN1_CONST64(0), ASN1_CONST64(2000), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexTransferDone_Success_bool = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_Align_Dec_UTF8Str(workspace, &(value->datexTransferDone_FileName_txt), &consinfo_datexTransferDone_FileName_txt)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_BOOLEAN(workspace, &(value->datexTransferDone_Success_bool), &consinfo_datexTransferDone_Success_bool)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_TransferDone(TransferDone *value);
extern int ASN1_PER_Align_Data_Dec_TransferDone(ASN1WorkSpace *workspace, TransferDone *value);
int ASN1_PER_Align_Dec_TransferDone(ASN1WorkSpace *workspace, TransferDone *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_TransferDone(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_TransferDone(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_TransferDone(ASN1WorkSpace *workspace, TransferDone *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexTransferDone_FileName_txt = { ASN1_CONST64(0), ASN1_CONST64(2000), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexTransferDone_Success_bool = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_UNAlign_Enc_UTF8Str(workspace, &(value->datexTransferDone_FileName_txt), &consinfo_datexTransferDone_FileName_txt)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_BOOLEAN(workspace, &(value->datexTransferDone_Success_bool), &consinfo_datexTransferDone_Success_bool)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_TransferDone(TransferDone *value);
extern int ASN1_PER_UNAlign_Data_Enc_TransferDone(ASN1WorkSpace *workspace, TransferDone *value);
int ASN1_PER_UNAlign_Enc_TransferDone(ASN1WorkSpace *workspace, TransferDone *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_TransferDone(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_TransferDone(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_TransferDone(ASN1WorkSpace *workspace, TransferDone *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexTransferDone_FileName_txt = { ASN1_CONST64(0), ASN1_CONST64(2000), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexTransferDone_Success_bool = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_UNAlign_Dec_UTF8Str(workspace, &(value->datexTransferDone_FileName_txt), &consinfo_datexTransferDone_FileName_txt)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_BOOLEAN(workspace, &(value->datexTransferDone_Success_bool), &consinfo_datexTransferDone_Success_bool)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_TransferDone(TransferDone *value);
extern int ASN1_PER_UNAlign_Data_Dec_TransferDone(ASN1WorkSpace *workspace, TransferDone *value);
int ASN1_PER_UNAlign_Dec_TransferDone(ASN1WorkSpace *workspace, TransferDone *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_TransferDone(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_TransferDone(value)) < 0) return ret;
	return ret;
}

/********************************************************
*Accept_datexAccept_Type                                *
********************************************************/
int ASN1_Print_Accept_datexAccept_Type(Accept_datexAccept_Type *value, int tab_value)
{
	int ret = 0;
	// CHOICE : default
	ASN1_Print_CHOICE(" ");
	if (value == NULL) return -1;
	switch (value->M) {
	case DEF_Accept_datexAccept_Type_login:
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_OBJECTIDENTIFIER("login", &value->elements.login)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_Accept_datexAccept_Type_single_subscription:
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_NULL("single_subscription", &value->elements.single_subscription)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_Accept_datexAccept_Type_registered_subscription:
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("registered_subscription", &value->elements.registered_subscription)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_Accept_datexAccept_Type_publication:
		// Type Default
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_NULL("publication", &value->elements.publication)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: return -1;
}
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_Accept_datexAccept_Type_login(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, ASNUINT32 *user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->M = DEF_Accept_datexAccept_Type_login;
	if ((ret = ASN1_SET_OBJECTIDENTIFIER(workspace, &value->elements.login, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_Accept_datexAccept_Type_single_subscription(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, ASNUINT8 user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->M = DEF_Accept_datexAccept_Type_single_subscription;
	if ((ret = ASN1_SET_NULL(workspace, &value->elements.single_subscription, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_Accept_datexAccept_Type_registered_subscription(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->M = DEF_Accept_datexAccept_Type_registered_subscription;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->elements.registered_subscription, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_Accept_datexAccept_Type_publication(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, ASNUINT8 user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->M = DEF_Accept_datexAccept_Type_publication;
	if ((ret = ASN1_SET_NULL(workspace, &value->elements.publication, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_Accept_datexAccept_Type_login(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, ASNUINT32 *user_value, ASNUINT32 *user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->M == DEF_Accept_datexAccept_Type_login)
	{
		if ((ret = ASN1_GET_OBJECTIDENTIFIER(workspace, &value->elements.login, user_value, user_value_length)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_Accept_datexAccept_Type_single_subscription(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, ASNUINT8 *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->M == DEF_Accept_datexAccept_Type_single_subscription)
	{
		if ((ret = ASN1_GET_NULL(workspace, &value->elements.single_subscription, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_Accept_datexAccept_Type_registered_subscription(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->M == DEF_Accept_datexAccept_Type_registered_subscription)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->elements.registered_subscription, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_Accept_datexAccept_Type_publication(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, ASNUINT8 *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->M == DEF_Accept_datexAccept_Type_publication)
	{
		if ((ret = ASN1_GET_NULL(workspace, &value->elements.publication, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_CHECK_Accept_datexAccept_Type(Accept_datexAccept_Type *value)
{
	int ret = 0;

	unsigned char checkinfo_login[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_single_subscription[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_registered_subscription[] = { 
		0x02,0x00,0x85,0x00,0xFF,0xFF,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_publication[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_Accept_datexAccept_Type_login:
		if ((ret = ASN1_CHECK_OBJECTIDENTIFIER(&value->elements.login, checkinfo_login)) < 0) return ret;
		break;
	case DEF_Accept_datexAccept_Type_single_subscription:
		if ((ret = ASN1_CHECK_NULL(&value->elements.single_subscription, checkinfo_single_subscription)) < 0) return ret;
		break;
	case DEF_Accept_datexAccept_Type_registered_subscription:
		if ((ret = ASN1_CHECK_INTEGER(&value->elements.registered_subscription, checkinfo_registered_subscription)) < 0) return ret;
		break;
	case DEF_Accept_datexAccept_Type_publication:
		if ((ret = ASN1_CHECK_NULL(&value->elements.publication, checkinfo_publication)) < 0) return ret;
		break;
	default: break;
	}
	return ret;
}
int ASN1_BER_Data_Enc_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, ASN1TagType tagFlag)
{
	int ret = 0;
	switch(value->M)
	{
	case DEF_Accept_datexAccept_Type_login:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_OBJECTIDENTIFIER(workspace, &(value->elements.login), ASN1IMPL)) < 0) return ret;
		break;
	case DEF_Accept_datexAccept_Type_single_subscription:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_NULL(workspace, ASN1IMPL)) < 0) return ret;
		break;
	case DEF_Accept_datexAccept_Type_registered_subscription:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->elements.registered_subscription), ASN1IMPL)) < 0) return ret;
		break;
	case DEF_Accept_datexAccept_Type_publication:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_NULL(workspace, ASN1IMPL)) < 0) return ret;
		break;
	}
	return ret;
}
extern int ASN1_CHECK_Accept_datexAccept_Type(Accept_datexAccept_Type *value);
extern int ASN1_BER_Data_Enc_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_Accept_datexAccept_Type(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Accept_datexAccept_Type(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	value->M = 0;
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	switch(tag)
	{
	case ITS_ASN_CONT | ITS_ASN_PRIM | 0:
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_OBJECTIDENTIFIER(workspace, &value->elements.login, len, ASN1IMPL)) < 0) return ret;
		value->M = DEF_Accept_datexAccept_Type_login;
		break;
	case ITS_ASN_CONT | ITS_ASN_PRIM | 1:
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_NULL(workspace, ASN1IMPL)) < 0) return ret;
		value->M = DEF_Accept_datexAccept_Type_single_subscription;
		break;
	case ITS_ASN_CONT | ITS_ASN_PRIM | 2:
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->elements.registered_subscription, len, ASN1IMPL)) < 0) return ret;
		value->M = DEF_Accept_datexAccept_Type_registered_subscription;
		break;
	case ITS_ASN_CONT | ITS_ASN_PRIM | 3:
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Dec_NULL(workspace, ASN1IMPL)) < 0) return ret;
		value->M = DEF_Accept_datexAccept_Type_publication;
		break;
	}
	return ret;
}
extern int ASN1_CHECK_Accept_datexAccept_Type(Accept_datexAccept_Type *value);
extern int ASN1_BER_Data_Dec_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Accept_datexAccept_Type(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_Accept_datexAccept_Type(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_login = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_single_subscription = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_registered_subscription = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_publication = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT64 ui;
	ASNBOOL extbit = 1;
	switch(value->M)
	{
	case DEF_Accept_datexAccept_Type_login: ui = 0; extbit = 0; break;
	case DEF_Accept_datexAccept_Type_single_subscription: ui = 1; extbit = 0; break;
	case DEF_Accept_datexAccept_Type_registered_subscription: ui = 2; extbit = 0; break;
	case DEF_Accept_datexAccept_Type_publication: ui = 3; extbit = 0; break;
	default: break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_Choice_ENUMERATED(workspace, ui, extbit, 0, 4)) < 0) return ret;
	switch(value->M)
	{
	case DEF_Accept_datexAccept_Type_login:
		if ((ret = ASN1_PER_Align_Enc_OBJECTIDENTIFIER(workspace, &(value->elements.login), &consinfo_login)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_Accept_datexAccept_Type_single_subscription:
		/* NULL NOT Encode Of PER ruler!! */
		return 0;
		if (ret != 0) return -1;
		break;
	case DEF_Accept_datexAccept_Type_registered_subscription:
		if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->elements.registered_subscription), &consinfo_registered_subscription)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_Accept_datexAccept_Type_publication:
		/* NULL NOT Encode Of PER ruler!! */
		return 0;
		if (ret != 0) return -1;
		break;
	default: break;
	}
	return ret;
}
extern int ASN1_CHECK_Accept_datexAccept_Type(Accept_datexAccept_Type *value);
extern int ASN1_PER_Align_Data_Enc_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value);
int ASN1_PER_Align_Enc_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Accept_datexAccept_Type(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_Accept_datexAccept_Type(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_login = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_single_subscription = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_registered_subscription = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_publication = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	if ((ret = ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 4)) < 0) return ret;

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_Accept_datexAccept_Type_login;
			break;
		case 1: index = DEF_Accept_datexAccept_Type_single_subscription;
			break;
		case 2: index = DEF_Accept_datexAccept_Type_registered_subscription;
			break;
		case 3: index = DEF_Accept_datexAccept_Type_publication;
			break;
		default: break;
		}
	}
	else
	{
		switch(ui)
		{
		default: break;
		}
	}
	if ((ret = ASN1_GetM(&value->M, index)) < 0) return ret;
	switch(index)
	{
	case DEF_Accept_datexAccept_Type_login:
		if ((ret = ASN1_PER_Align_Dec_OBJECTIDENTIFIER(workspace, &(value->elements.login), &consinfo_login)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_Accept_datexAccept_Type_single_subscription:
		/* NULL NOT Decode Of PER ruler!! - PrintLineDecode_Per */
		return 0;
		if (ret != 0) return -1;
		break;
	case DEF_Accept_datexAccept_Type_registered_subscription:
		if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->elements.registered_subscription), &consinfo_registered_subscription)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_Accept_datexAccept_Type_publication:
		/* NULL NOT Decode Of PER ruler!! - PrintLineDecode_Per */
		return 0;
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, ALIGN); break;
	}
	return ret;
}
extern int ASN1_CHECK_Accept_datexAccept_Type(Accept_datexAccept_Type *value);
extern int ASN1_PER_Align_Data_Dec_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value);
int ASN1_PER_Align_Dec_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_Accept_datexAccept_Type(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Accept_datexAccept_Type(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_login = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_single_subscription = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_registered_subscription = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_publication = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT64 ui;
	ASNBOOL extbit = 1;
	switch(value->M)
	{
	case DEF_Accept_datexAccept_Type_login: ui = 0; extbit = 0; break;
	case DEF_Accept_datexAccept_Type_single_subscription: ui = 1; extbit = 0; break;
	case DEF_Accept_datexAccept_Type_registered_subscription: ui = 2; extbit = 0; break;
	case DEF_Accept_datexAccept_Type_publication: ui = 3; extbit = 0; break;
	default: break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_Choice_ENUMERATED(workspace, ui, extbit, 0, 4)) < 0) return ret;
	switch(value->M)
	{
	case DEF_Accept_datexAccept_Type_login:
		if ((ret = ASN1_PER_UNAlign_Enc_OBJECTIDENTIFIER(workspace, &(value->elements.login), &consinfo_login)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_Accept_datexAccept_Type_single_subscription:
		/* NULL NOT Encode Of PER ruler!! */
		return 0;
		if (ret != 0) return -1;
		break;
	case DEF_Accept_datexAccept_Type_registered_subscription:
		if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->elements.registered_subscription), &consinfo_registered_subscription)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_Accept_datexAccept_Type_publication:
		/* NULL NOT Encode Of PER ruler!! */
		return 0;
		if (ret != 0) return -1;
		break;
	default: break;
	}
	return ret;
}
extern int ASN1_CHECK_Accept_datexAccept_Type(Accept_datexAccept_Type *value);
extern int ASN1_PER_UNAlign_Data_Enc_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value);
int ASN1_PER_UNAlign_Enc_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Accept_datexAccept_Type(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_Accept_datexAccept_Type(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_login = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_single_subscription = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_registered_subscription = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_publication = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	if ((ret = ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 4)) < 0) return ret;

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_Accept_datexAccept_Type_login;
			break;
		case 1: index = DEF_Accept_datexAccept_Type_single_subscription;
			break;
		case 2: index = DEF_Accept_datexAccept_Type_registered_subscription;
			break;
		case 3: index = DEF_Accept_datexAccept_Type_publication;
			break;
		default: break;
		}
	}
	else
	{
		switch(ui)
		{
		default: break;
		}
	}
	if ((ret = ASN1_GetM(&value->M, index)) < 0) return ret;
	switch(index)
	{
	case DEF_Accept_datexAccept_Type_login:
		if ((ret = ASN1_PER_UNAlign_Dec_OBJECTIDENTIFIER(workspace, &(value->elements.login), &consinfo_login)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_Accept_datexAccept_Type_single_subscription:
		/* NULL NOT Decode Of PER ruler!! - PrintLineDecode_Per */
		return 0;
		if (ret != 0) return -1;
		break;
	case DEF_Accept_datexAccept_Type_registered_subscription:
		if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->elements.registered_subscription), &consinfo_registered_subscription)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_Accept_datexAccept_Type_publication:
		/* NULL NOT Decode Of PER ruler!! - PrintLineDecode_Per */
		return 0;
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
extern int ASN1_CHECK_Accept_datexAccept_Type(Accept_datexAccept_Type *value);
extern int ASN1_PER_UNAlign_Data_Dec_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value);
int ASN1_PER_UNAlign_Dec_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_Accept_datexAccept_Type(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Accept_datexAccept_Type(value)) < 0) return ret;
	return ret;
}

/********************************************************
*Accept                                                 *
********************************************************/
int ASN1_Print_Accept(Accept *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("Accept");
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("datexAccept_Packet_nbr", &(value->datexAccept_Packet_nbr))) < 0) return ret;
	// Type Reference Accept_datexAccept_Type
	if (Compare_Letter(tab_value, "datexAccept-Type")) {
		ASN_Print_TAB(tab_value + 1);
		asn_printf("datexAccept-Type = ");
	}
	if ((ret = ASN1_Print_Accept_datexAccept_Type((Accept_datexAccept_Type *)value->datexAccept_Type, tab_value + 1)) < 0) return ret;
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_Accept_datexAccept_Packet_nbr(ASN1WorkSpace *workspace, Accept *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->datexAccept_Packet_nbr, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept *value, Accept_datexAccept_Type *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->datexAccept_Type = (Accept_datexAccept_Type *)mpool_malloc(workspace->Pmemory, sizeof(Accept_datexAccept_Type));
	memset(value->datexAccept_Type, 0, sizeof(Accept_datexAccept_Type));
	memmove(value->datexAccept_Type, user_value, sizeof(Accept_datexAccept_Type));
	return ret;
}
int ASN1_GET_Accept_datexAccept_Packet_nbr(ASN1WorkSpace *workspace, Accept *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->datexAccept_Packet_nbr, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept *value, Accept_datexAccept_Type **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = value->datexAccept_Type;
	return ret;
}
extern int ASN1_CHECK_Accept_datexAccept_Type(Accept_datexAccept_Type *value);
int ASN1_CHECK_Accept(Accept *value)
{
	int ret = 0;

	unsigned char checkinfo_datexAccept_Packet_nbr[] = { 
		0x02,0x00,0x85,0x00,0xFF,0xFF,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_datexAccept_Type[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(&(value->datexAccept_Packet_nbr), checkinfo_datexAccept_Packet_nbr)) < 0) return ret;
	if ((ret = ASN1_CHECK_Accept_datexAccept_Type(value->datexAccept_Type)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Enc_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_Accept(ASN1WorkSpace *workspace, Accept *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->datexAccept_Packet_nbr), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Accept_datexAccept_Type(workspace, value->datexAccept_Type, ASN1EXPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Accept(Accept *value);
extern int ASN1_BER_Data_Enc_Accept(ASN1WorkSpace *workspace, Accept *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_Accept(ASN1WorkSpace *workspace, Accept *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_Accept(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Accept(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_Accept(ASN1WorkSpace *workspace, Accept *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8 *_cpointer;
	value->datexAccept_Type = (Accept_datexAccept_Type *)mpool_malloc(workspace->Pmemory, sizeof(Accept_datexAccept_Type));
	memset(value->datexAccept_Type, 0, sizeof(Accept_datexAccept_Type));
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->datexAccept_Packet_nbr, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Accept_datexAccept_Type(workspace, value->datexAccept_Type, len, ASN1EXPL)) < 0) return ret;
	if (IfFixedLength(len) == -1)
	{
		if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
	}
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_Accept(Accept *value);
extern int ASN1_BER_Data_Dec_Accept(ASN1WorkSpace *workspace, Accept *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_Accept(ASN1WorkSpace *workspace, Accept *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Accept(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_Accept(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Enc_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value);
int ASN1_PER_Align_Data_Enc_Accept(ASN1WorkSpace *workspace, Accept *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexAccept_Packet_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexAccept_Type = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->datexAccept_Packet_nbr), &consinfo_datexAccept_Packet_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_Accept_datexAccept_Type(workspace, value->datexAccept_Type)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_Accept(Accept *value);
extern int ASN1_PER_Align_Data_Enc_Accept(ASN1WorkSpace *workspace, Accept *value);
int ASN1_PER_Align_Enc_Accept(ASN1WorkSpace *workspace, Accept *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Accept(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_Accept(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Dec_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value);
int ASN1_PER_Align_Data_Dec_Accept(ASN1WorkSpace *workspace, Accept *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexAccept_Packet_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexAccept_Type = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	value->datexAccept_Type = (Accept_datexAccept_Type *)mpool_malloc(workspace->Pmemory, sizeof(Accept_datexAccept_Type));
	memset(value->datexAccept_Type, 0, sizeof(Accept_datexAccept_Type));
	if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->datexAccept_Packet_nbr), &consinfo_datexAccept_Packet_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_Accept_datexAccept_Type(workspace, value->datexAccept_Type)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_Accept(Accept *value);
extern int ASN1_PER_Align_Data_Dec_Accept(ASN1WorkSpace *workspace, Accept *value);
int ASN1_PER_Align_Dec_Accept(ASN1WorkSpace *workspace, Accept *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_Accept(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Accept(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Enc_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value);
int ASN1_PER_UNAlign_Data_Enc_Accept(ASN1WorkSpace *workspace, Accept *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexAccept_Packet_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexAccept_Type = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->datexAccept_Packet_nbr), &consinfo_datexAccept_Packet_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_Accept_datexAccept_Type(workspace, value->datexAccept_Type)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_Accept(Accept *value);
extern int ASN1_PER_UNAlign_Data_Enc_Accept(ASN1WorkSpace *workspace, Accept *value);
int ASN1_PER_UNAlign_Enc_Accept(ASN1WorkSpace *workspace, Accept *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Accept(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_Accept(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Dec_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value);
int ASN1_PER_UNAlign_Data_Dec_Accept(ASN1WorkSpace *workspace, Accept *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexAccept_Packet_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexAccept_Type = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	value->datexAccept_Type = (Accept_datexAccept_Type *)mpool_malloc(workspace->Pmemory, sizeof(Accept_datexAccept_Type));
	memset(value->datexAccept_Type, 0, sizeof(Accept_datexAccept_Type));
	if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->datexAccept_Packet_nbr), &consinfo_datexAccept_Packet_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_Accept_datexAccept_Type(workspace, value->datexAccept_Type)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_Accept(Accept *value);
extern int ASN1_PER_UNAlign_Data_Dec_Accept(ASN1WorkSpace *workspace, Accept *value);
int ASN1_PER_UNAlign_Dec_Accept(ASN1WorkSpace *workspace, Accept *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_Accept(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Accept(value)) < 0) return ret;
	return ret;
}

/********************************************************
*RejectType-datexReject-Login-cd                        *
********************************************************/
int ASN1_Print_RejectType_datexReject_Login_cd(RejectType_datexReject_Login_cd *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch(*value)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Login-cd", "other", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Login-cd", "unknownDomainName", 1)) < 0) return ret; break;
	case 2: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Login-cd", "accessDenied", 2)) < 0) return ret; break;
	case 3: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Login-cd", "invalidNamePassword", 3)) < 0) return ret; break;
	case 4: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Login-cd", "timeoutTooSmall", 4)) < 0) return ret; break;
	case 5: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Login-cd", "timeoutTooLarge", 5)) < 0) return ret; break;
	case 6: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Login-cd", "heartbeatTooSmall", 6)) < 0) return ret; break;
	case 7: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Login-cd", "heartbeatTooLarge", 7)) < 0) return ret; break;
	case 8: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Login-cd", "sessionExists", 8)) < 0) return ret; break;
	case 9: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Login-cd", "maxSessionsReached", 9)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	return ret;
}
int ASN1_CHECK_RejectType_datexReject_Login_cd(RejectType_datexReject_Login_cd *value)
{
	unsigned char checkinfo_RejectType_datexReject_Login_cd[] = {0x0A,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x00 };
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32 *)value, checkinfo_RejectType_datexReject_Login_cd)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_RejectType_datexReject_Login_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Login_cd *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_RejectType_datexReject_Login_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Login_cd *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_RejectType_datexReject_Login_cd(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_RejectType_datexReject_Login_cd(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_RejectType_datexReject_Login_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Login_cd *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_RejectType_datexReject_Login_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Login_cd *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_RejectType_datexReject_Login_cd(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_RejectType_datexReject_Login_cd(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_RejectType_datexReject_Login_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Login_cd *value)
{
	struct Asn1ConsInfo consinfo_RejectType_datexReject_Login_cd = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_RejectType_datexReject_Login_cd;
	switch(*value)
	{
	case RejectType_datexReject_Login_cd_other: ui_RejectType_datexReject_Login_cd = 0; consinfo_RejectType_datexReject_Login_cd.enumextbit = 0; break;
	case RejectType_datexReject_Login_cd_unknownDomainName: ui_RejectType_datexReject_Login_cd = 1; consinfo_RejectType_datexReject_Login_cd.enumextbit = 0; break;
	case RejectType_datexReject_Login_cd_accessDenied: ui_RejectType_datexReject_Login_cd = 2; consinfo_RejectType_datexReject_Login_cd.enumextbit = 0; break;
	case RejectType_datexReject_Login_cd_invalidNamePassword: ui_RejectType_datexReject_Login_cd = 3; consinfo_RejectType_datexReject_Login_cd.enumextbit = 0; break;
	case RejectType_datexReject_Login_cd_timeoutTooSmall: ui_RejectType_datexReject_Login_cd = 4; consinfo_RejectType_datexReject_Login_cd.enumextbit = 0; break;
	case RejectType_datexReject_Login_cd_timeoutTooLarge: ui_RejectType_datexReject_Login_cd = 5; consinfo_RejectType_datexReject_Login_cd.enumextbit = 0; break;
	case RejectType_datexReject_Login_cd_heartbeatTooSmall: ui_RejectType_datexReject_Login_cd = 6; consinfo_RejectType_datexReject_Login_cd.enumextbit = 0; break;
	case RejectType_datexReject_Login_cd_heartbeatTooLarge: ui_RejectType_datexReject_Login_cd = 7; consinfo_RejectType_datexReject_Login_cd.enumextbit = 0; break;
	case RejectType_datexReject_Login_cd_sessionExists: ui_RejectType_datexReject_Login_cd = 8; consinfo_RejectType_datexReject_Login_cd.enumextbit = 0; break;
	case RejectType_datexReject_Login_cd_maxSessionsReached: ui_RejectType_datexReject_Login_cd = 9; consinfo_RejectType_datexReject_Login_cd.enumextbit = 0; break;
	default: ui_RejectType_datexReject_Login_cd = *value; consinfo_RejectType_datexReject_Login_cd.enumextbit = 1; break;
	}
	if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_RejectType_datexReject_Login_cd, &consinfo_RejectType_datexReject_Login_cd)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Enc_RejectType_datexReject_Login_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Login_cd *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_RejectType_datexReject_Login_cd(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_RejectType_datexReject_Login_cd(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_RejectType_datexReject_Login_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Login_cd *value)
{
	struct Asn1ConsInfo consinfo_RejectType_datexReject_Login_cd = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_RejectType_datexReject_Login_cd;
	if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_RejectType_datexReject_Login_cd, &consinfo_RejectType_datexReject_Login_cd)) < 0) return ret;
	if (consinfo_RejectType_datexReject_Login_cd.enumextbit == 0)
	{
		switch(ui_RejectType_datexReject_Login_cd)
		{
		case 0: *value = RejectType_datexReject_Login_cd_other; break;
		case 1: *value = RejectType_datexReject_Login_cd_unknownDomainName; break;
		case 2: *value = RejectType_datexReject_Login_cd_accessDenied; break;
		case 3: *value = RejectType_datexReject_Login_cd_invalidNamePassword; break;
		case 4: *value = RejectType_datexReject_Login_cd_timeoutTooSmall; break;
		case 5: *value = RejectType_datexReject_Login_cd_timeoutTooLarge; break;
		case 6: *value = RejectType_datexReject_Login_cd_heartbeatTooSmall; break;
		case 7: *value = RejectType_datexReject_Login_cd_heartbeatTooLarge; break;
		case 8: *value = RejectType_datexReject_Login_cd_sessionExists; break;
		case 9: *value = RejectType_datexReject_Login_cd_maxSessionsReached; break;
		default: break;
		}
	}
	else
	{
		switch(ui_RejectType_datexReject_Login_cd)
		{
		default: *value = ui_RejectType_datexReject_Login_cd; break;
		}
	}
	return ret;
}
int ASN1_PER_Align_Dec_RejectType_datexReject_Login_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Login_cd *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_RejectType_datexReject_Login_cd(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_RejectType_datexReject_Login_cd(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_RejectType_datexReject_Login_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Login_cd *value)
{
	struct Asn1ConsInfo consinfo_RejectType_datexReject_Login_cd = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_RejectType_datexReject_Login_cd;
	switch(*value)
	{
	case RejectType_datexReject_Login_cd_other: ui_RejectType_datexReject_Login_cd = 0; consinfo_RejectType_datexReject_Login_cd.enumextbit = 0; break;
	case RejectType_datexReject_Login_cd_unknownDomainName: ui_RejectType_datexReject_Login_cd = 1; consinfo_RejectType_datexReject_Login_cd.enumextbit = 0; break;
	case RejectType_datexReject_Login_cd_accessDenied: ui_RejectType_datexReject_Login_cd = 2; consinfo_RejectType_datexReject_Login_cd.enumextbit = 0; break;
	case RejectType_datexReject_Login_cd_invalidNamePassword: ui_RejectType_datexReject_Login_cd = 3; consinfo_RejectType_datexReject_Login_cd.enumextbit = 0; break;
	case RejectType_datexReject_Login_cd_timeoutTooSmall: ui_RejectType_datexReject_Login_cd = 4; consinfo_RejectType_datexReject_Login_cd.enumextbit = 0; break;
	case RejectType_datexReject_Login_cd_timeoutTooLarge: ui_RejectType_datexReject_Login_cd = 5; consinfo_RejectType_datexReject_Login_cd.enumextbit = 0; break;
	case RejectType_datexReject_Login_cd_heartbeatTooSmall: ui_RejectType_datexReject_Login_cd = 6; consinfo_RejectType_datexReject_Login_cd.enumextbit = 0; break;
	case RejectType_datexReject_Login_cd_heartbeatTooLarge: ui_RejectType_datexReject_Login_cd = 7; consinfo_RejectType_datexReject_Login_cd.enumextbit = 0; break;
	case RejectType_datexReject_Login_cd_sessionExists: ui_RejectType_datexReject_Login_cd = 8; consinfo_RejectType_datexReject_Login_cd.enumextbit = 0; break;
	case RejectType_datexReject_Login_cd_maxSessionsReached: ui_RejectType_datexReject_Login_cd = 9; consinfo_RejectType_datexReject_Login_cd.enumextbit = 0; break;
	default: ui_RejectType_datexReject_Login_cd = *value; consinfo_RejectType_datexReject_Login_cd.enumextbit = 1; break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_RejectType_datexReject_Login_cd, &consinfo_RejectType_datexReject_Login_cd)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Enc_RejectType_datexReject_Login_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Login_cd *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_RejectType_datexReject_Login_cd(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_RejectType_datexReject_Login_cd(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_RejectType_datexReject_Login_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Login_cd *value)
{
	struct Asn1ConsInfo consinfo_RejectType_datexReject_Login_cd = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_RejectType_datexReject_Login_cd;
	if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_RejectType_datexReject_Login_cd, &consinfo_RejectType_datexReject_Login_cd)) < 0) return ret;
	if (consinfo_RejectType_datexReject_Login_cd.enumextbit == 0)
	{
		switch(ui_RejectType_datexReject_Login_cd)
		{
		case 0: *value = RejectType_datexReject_Login_cd_other; break;
		case 1: *value = RejectType_datexReject_Login_cd_unknownDomainName; break;
		case 2: *value = RejectType_datexReject_Login_cd_accessDenied; break;
		case 3: *value = RejectType_datexReject_Login_cd_invalidNamePassword; break;
		case 4: *value = RejectType_datexReject_Login_cd_timeoutTooSmall; break;
		case 5: *value = RejectType_datexReject_Login_cd_timeoutTooLarge; break;
		case 6: *value = RejectType_datexReject_Login_cd_heartbeatTooSmall; break;
		case 7: *value = RejectType_datexReject_Login_cd_heartbeatTooLarge; break;
		case 8: *value = RejectType_datexReject_Login_cd_sessionExists; break;
		case 9: *value = RejectType_datexReject_Login_cd_maxSessionsReached; break;
		default: break;
		}
	}
	else
	{
		switch(ui_RejectType_datexReject_Login_cd)
		{
		default: *value = ui_RejectType_datexReject_Login_cd; break;
		}
	}
	return ret;
}
int ASN1_PER_UNAlign_Dec_RejectType_datexReject_Login_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Login_cd *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_RejectType_datexReject_Login_cd(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_RejectType_datexReject_Login_cd(value)) < 0) return ret;
	return ret;
}

/********************************************************
*RejectType-datexReject-Subscription-cd                 *
********************************************************/
int ASN1_Print_RejectType_datexReject_Subscription_cd(RejectType_datexReject_Subscription_cd *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch(*value)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Subscription-cd", "other", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Subscription-cd", "unknownSubscriptionNbr", 1)) < 0) return ret; break;
	case 2: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Subscription-cd", "invalidTimes", 2)) < 0) return ret; break;
	case 3: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Subscription-cd", "frequencyTooSmall", 3)) < 0) return ret; break;
	case 4: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Subscription-cd", "frequencyTooLarge", 4)) < 0) return ret; break;
	case 5: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Subscription-cd", "invalid-mode", 5)) < 0) return ret; break;
	case 6: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Subscription-cd", "publishFormatNotSupported", 6)) < 0) return ret; break;
	case 7: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Subscription-cd", "unknowSubscriptionMsgId", 7)) < 0) return ret; break;
	case 8: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Subscription-cd", "invalidSubscriptionMsgId", 8)) < 0) return ret; break;
	case 9: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Subscription-cd", "invalidSubscriptionContent", 9)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	return ret;
}
int ASN1_CHECK_RejectType_datexReject_Subscription_cd(RejectType_datexReject_Subscription_cd *value)
{
	unsigned char checkinfo_RejectType_datexReject_Subscription_cd[] = {0x0A,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x00 };
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32 *)value, checkinfo_RejectType_datexReject_Subscription_cd)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_RejectType_datexReject_Subscription_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Subscription_cd *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_RejectType_datexReject_Subscription_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Subscription_cd *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_RejectType_datexReject_Subscription_cd(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_RejectType_datexReject_Subscription_cd(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_RejectType_datexReject_Subscription_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Subscription_cd *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_RejectType_datexReject_Subscription_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Subscription_cd *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_RejectType_datexReject_Subscription_cd(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_RejectType_datexReject_Subscription_cd(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_RejectType_datexReject_Subscription_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Subscription_cd *value)
{
	struct Asn1ConsInfo consinfo_RejectType_datexReject_Subscription_cd = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_RejectType_datexReject_Subscription_cd;
	switch(*value)
	{
	case RejectType_datexReject_Subscription_cd_other: ui_RejectType_datexReject_Subscription_cd = 0; consinfo_RejectType_datexReject_Subscription_cd.enumextbit = 0; break;
	case RejectType_datexReject_Subscription_cd_unknownSubscriptionNbr: ui_RejectType_datexReject_Subscription_cd = 1; consinfo_RejectType_datexReject_Subscription_cd.enumextbit = 0; break;
	case RejectType_datexReject_Subscription_cd_invalidTimes: ui_RejectType_datexReject_Subscription_cd = 2; consinfo_RejectType_datexReject_Subscription_cd.enumextbit = 0; break;
	case RejectType_datexReject_Subscription_cd_frequencyTooSmall: ui_RejectType_datexReject_Subscription_cd = 3; consinfo_RejectType_datexReject_Subscription_cd.enumextbit = 0; break;
	case RejectType_datexReject_Subscription_cd_frequencyTooLarge: ui_RejectType_datexReject_Subscription_cd = 4; consinfo_RejectType_datexReject_Subscription_cd.enumextbit = 0; break;
	case RejectType_datexReject_Subscription_cd_invalid_mode: ui_RejectType_datexReject_Subscription_cd = 5; consinfo_RejectType_datexReject_Subscription_cd.enumextbit = 0; break;
	case RejectType_datexReject_Subscription_cd_publishFormatNotSupported: ui_RejectType_datexReject_Subscription_cd = 6; consinfo_RejectType_datexReject_Subscription_cd.enumextbit = 0; break;
	case RejectType_datexReject_Subscription_cd_unknowSubscriptionMsgId: ui_RejectType_datexReject_Subscription_cd = 7; consinfo_RejectType_datexReject_Subscription_cd.enumextbit = 0; break;
	case RejectType_datexReject_Subscription_cd_invalidSubscriptionMsgId: ui_RejectType_datexReject_Subscription_cd = 8; consinfo_RejectType_datexReject_Subscription_cd.enumextbit = 0; break;
	case RejectType_datexReject_Subscription_cd_invalidSubscriptionContent: ui_RejectType_datexReject_Subscription_cd = 9; consinfo_RejectType_datexReject_Subscription_cd.enumextbit = 0; break;
	default: ui_RejectType_datexReject_Subscription_cd = *value; consinfo_RejectType_datexReject_Subscription_cd.enumextbit = 1; break;
	}
	if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_RejectType_datexReject_Subscription_cd, &consinfo_RejectType_datexReject_Subscription_cd)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Enc_RejectType_datexReject_Subscription_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Subscription_cd *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_RejectType_datexReject_Subscription_cd(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_RejectType_datexReject_Subscription_cd(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_RejectType_datexReject_Subscription_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Subscription_cd *value)
{
	struct Asn1ConsInfo consinfo_RejectType_datexReject_Subscription_cd = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_RejectType_datexReject_Subscription_cd;
	if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_RejectType_datexReject_Subscription_cd, &consinfo_RejectType_datexReject_Subscription_cd)) < 0) return ret;
	if (consinfo_RejectType_datexReject_Subscription_cd.enumextbit == 0)
	{
		switch(ui_RejectType_datexReject_Subscription_cd)
		{
		case 0: *value = RejectType_datexReject_Subscription_cd_other; break;
		case 1: *value = RejectType_datexReject_Subscription_cd_unknownSubscriptionNbr; break;
		case 2: *value = RejectType_datexReject_Subscription_cd_invalidTimes; break;
		case 3: *value = RejectType_datexReject_Subscription_cd_frequencyTooSmall; break;
		case 4: *value = RejectType_datexReject_Subscription_cd_frequencyTooLarge; break;
		case 5: *value = RejectType_datexReject_Subscription_cd_invalid_mode; break;
		case 6: *value = RejectType_datexReject_Subscription_cd_publishFormatNotSupported; break;
		case 7: *value = RejectType_datexReject_Subscription_cd_unknowSubscriptionMsgId; break;
		case 8: *value = RejectType_datexReject_Subscription_cd_invalidSubscriptionMsgId; break;
		case 9: *value = RejectType_datexReject_Subscription_cd_invalidSubscriptionContent; break;
		default: break;
		}
	}
	else
	{
		switch(ui_RejectType_datexReject_Subscription_cd)
		{
		default: *value = ui_RejectType_datexReject_Subscription_cd; break;
		}
	}
	return ret;
}
int ASN1_PER_Align_Dec_RejectType_datexReject_Subscription_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Subscription_cd *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_RejectType_datexReject_Subscription_cd(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_RejectType_datexReject_Subscription_cd(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_RejectType_datexReject_Subscription_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Subscription_cd *value)
{
	struct Asn1ConsInfo consinfo_RejectType_datexReject_Subscription_cd = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_RejectType_datexReject_Subscription_cd;
	switch(*value)
	{
	case RejectType_datexReject_Subscription_cd_other: ui_RejectType_datexReject_Subscription_cd = 0; consinfo_RejectType_datexReject_Subscription_cd.enumextbit = 0; break;
	case RejectType_datexReject_Subscription_cd_unknownSubscriptionNbr: ui_RejectType_datexReject_Subscription_cd = 1; consinfo_RejectType_datexReject_Subscription_cd.enumextbit = 0; break;
	case RejectType_datexReject_Subscription_cd_invalidTimes: ui_RejectType_datexReject_Subscription_cd = 2; consinfo_RejectType_datexReject_Subscription_cd.enumextbit = 0; break;
	case RejectType_datexReject_Subscription_cd_frequencyTooSmall: ui_RejectType_datexReject_Subscription_cd = 3; consinfo_RejectType_datexReject_Subscription_cd.enumextbit = 0; break;
	case RejectType_datexReject_Subscription_cd_frequencyTooLarge: ui_RejectType_datexReject_Subscription_cd = 4; consinfo_RejectType_datexReject_Subscription_cd.enumextbit = 0; break;
	case RejectType_datexReject_Subscription_cd_invalid_mode: ui_RejectType_datexReject_Subscription_cd = 5; consinfo_RejectType_datexReject_Subscription_cd.enumextbit = 0; break;
	case RejectType_datexReject_Subscription_cd_publishFormatNotSupported: ui_RejectType_datexReject_Subscription_cd = 6; consinfo_RejectType_datexReject_Subscription_cd.enumextbit = 0; break;
	case RejectType_datexReject_Subscription_cd_unknowSubscriptionMsgId: ui_RejectType_datexReject_Subscription_cd = 7; consinfo_RejectType_datexReject_Subscription_cd.enumextbit = 0; break;
	case RejectType_datexReject_Subscription_cd_invalidSubscriptionMsgId: ui_RejectType_datexReject_Subscription_cd = 8; consinfo_RejectType_datexReject_Subscription_cd.enumextbit = 0; break;
	case RejectType_datexReject_Subscription_cd_invalidSubscriptionContent: ui_RejectType_datexReject_Subscription_cd = 9; consinfo_RejectType_datexReject_Subscription_cd.enumextbit = 0; break;
	default: ui_RejectType_datexReject_Subscription_cd = *value; consinfo_RejectType_datexReject_Subscription_cd.enumextbit = 1; break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_RejectType_datexReject_Subscription_cd, &consinfo_RejectType_datexReject_Subscription_cd)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Enc_RejectType_datexReject_Subscription_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Subscription_cd *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_RejectType_datexReject_Subscription_cd(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_RejectType_datexReject_Subscription_cd(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_RejectType_datexReject_Subscription_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Subscription_cd *value)
{
	struct Asn1ConsInfo consinfo_RejectType_datexReject_Subscription_cd = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_RejectType_datexReject_Subscription_cd;
	if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_RejectType_datexReject_Subscription_cd, &consinfo_RejectType_datexReject_Subscription_cd)) < 0) return ret;
	if (consinfo_RejectType_datexReject_Subscription_cd.enumextbit == 0)
	{
		switch(ui_RejectType_datexReject_Subscription_cd)
		{
		case 0: *value = RejectType_datexReject_Subscription_cd_other; break;
		case 1: *value = RejectType_datexReject_Subscription_cd_unknownSubscriptionNbr; break;
		case 2: *value = RejectType_datexReject_Subscription_cd_invalidTimes; break;
		case 3: *value = RejectType_datexReject_Subscription_cd_frequencyTooSmall; break;
		case 4: *value = RejectType_datexReject_Subscription_cd_frequencyTooLarge; break;
		case 5: *value = RejectType_datexReject_Subscription_cd_invalid_mode; break;
		case 6: *value = RejectType_datexReject_Subscription_cd_publishFormatNotSupported; break;
		case 7: *value = RejectType_datexReject_Subscription_cd_unknowSubscriptionMsgId; break;
		case 8: *value = RejectType_datexReject_Subscription_cd_invalidSubscriptionMsgId; break;
		case 9: *value = RejectType_datexReject_Subscription_cd_invalidSubscriptionContent; break;
		default: break;
		}
	}
	else
	{
		switch(ui_RejectType_datexReject_Subscription_cd)
		{
		default: *value = ui_RejectType_datexReject_Subscription_cd; break;
		}
	}
	return ret;
}
int ASN1_PER_UNAlign_Dec_RejectType_datexReject_Subscription_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Subscription_cd *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_RejectType_datexReject_Subscription_cd(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_RejectType_datexReject_Subscription_cd(value)) < 0) return ret;
	return ret;
}

/********************************************************
*RejectType-datexReject-Publication-cd                  *
********************************************************/
int ASN1_Print_RejectType_datexReject_Publication_cd(RejectType_datexReject_Publication_cd *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch(*value)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Publication-cd", "other", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Publication-cd", "invalidPublishFormat", 1)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	return ret;
}
int ASN1_CHECK_RejectType_datexReject_Publication_cd(RejectType_datexReject_Publication_cd *value)
{
	unsigned char checkinfo_RejectType_datexReject_Publication_cd[] = {0x02,0x00,0x01,0x00 };
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32 *)value, checkinfo_RejectType_datexReject_Publication_cd)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_RejectType_datexReject_Publication_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Publication_cd *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_RejectType_datexReject_Publication_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Publication_cd *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_RejectType_datexReject_Publication_cd(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_RejectType_datexReject_Publication_cd(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_RejectType_datexReject_Publication_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Publication_cd *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_RejectType_datexReject_Publication_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Publication_cd *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_RejectType_datexReject_Publication_cd(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_RejectType_datexReject_Publication_cd(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_RejectType_datexReject_Publication_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Publication_cd *value)
{
	struct Asn1ConsInfo consinfo_RejectType_datexReject_Publication_cd = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_RejectType_datexReject_Publication_cd;
	switch(*value)
	{
	case RejectType_datexReject_Publication_cd_other: ui_RejectType_datexReject_Publication_cd = 0; consinfo_RejectType_datexReject_Publication_cd.enumextbit = 0; break;
	case RejectType_datexReject_Publication_cd_invalidPublishFormat: ui_RejectType_datexReject_Publication_cd = 1; consinfo_RejectType_datexReject_Publication_cd.enumextbit = 0; break;
	default: ui_RejectType_datexReject_Publication_cd = *value; consinfo_RejectType_datexReject_Publication_cd.enumextbit = 1; break;
	}
	if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_RejectType_datexReject_Publication_cd, &consinfo_RejectType_datexReject_Publication_cd)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Enc_RejectType_datexReject_Publication_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Publication_cd *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_RejectType_datexReject_Publication_cd(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_RejectType_datexReject_Publication_cd(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_RejectType_datexReject_Publication_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Publication_cd *value)
{
	struct Asn1ConsInfo consinfo_RejectType_datexReject_Publication_cd = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_RejectType_datexReject_Publication_cd;
	if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_RejectType_datexReject_Publication_cd, &consinfo_RejectType_datexReject_Publication_cd)) < 0) return ret;
	if (consinfo_RejectType_datexReject_Publication_cd.enumextbit == 0)
	{
		switch(ui_RejectType_datexReject_Publication_cd)
		{
		case 0: *value = RejectType_datexReject_Publication_cd_other; break;
		case 1: *value = RejectType_datexReject_Publication_cd_invalidPublishFormat; break;
		default: break;
		}
	}
	else
	{
		switch(ui_RejectType_datexReject_Publication_cd)
		{
		default: *value = ui_RejectType_datexReject_Publication_cd; break;
		}
	}
	return ret;
}
int ASN1_PER_Align_Dec_RejectType_datexReject_Publication_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Publication_cd *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_RejectType_datexReject_Publication_cd(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_RejectType_datexReject_Publication_cd(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_RejectType_datexReject_Publication_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Publication_cd *value)
{
	struct Asn1ConsInfo consinfo_RejectType_datexReject_Publication_cd = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_RejectType_datexReject_Publication_cd;
	switch(*value)
	{
	case RejectType_datexReject_Publication_cd_other: ui_RejectType_datexReject_Publication_cd = 0; consinfo_RejectType_datexReject_Publication_cd.enumextbit = 0; break;
	case RejectType_datexReject_Publication_cd_invalidPublishFormat: ui_RejectType_datexReject_Publication_cd = 1; consinfo_RejectType_datexReject_Publication_cd.enumextbit = 0; break;
	default: ui_RejectType_datexReject_Publication_cd = *value; consinfo_RejectType_datexReject_Publication_cd.enumextbit = 1; break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_RejectType_datexReject_Publication_cd, &consinfo_RejectType_datexReject_Publication_cd)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Enc_RejectType_datexReject_Publication_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Publication_cd *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_RejectType_datexReject_Publication_cd(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_RejectType_datexReject_Publication_cd(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_RejectType_datexReject_Publication_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Publication_cd *value)
{
	struct Asn1ConsInfo consinfo_RejectType_datexReject_Publication_cd = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_RejectType_datexReject_Publication_cd;
	if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_RejectType_datexReject_Publication_cd, &consinfo_RejectType_datexReject_Publication_cd)) < 0) return ret;
	if (consinfo_RejectType_datexReject_Publication_cd.enumextbit == 0)
	{
		switch(ui_RejectType_datexReject_Publication_cd)
		{
		case 0: *value = RejectType_datexReject_Publication_cd_other; break;
		case 1: *value = RejectType_datexReject_Publication_cd_invalidPublishFormat; break;
		default: break;
		}
	}
	else
	{
		switch(ui_RejectType_datexReject_Publication_cd)
		{
		default: *value = ui_RejectType_datexReject_Publication_cd; break;
		}
	}
	return ret;
}
int ASN1_PER_UNAlign_Dec_RejectType_datexReject_Publication_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Publication_cd *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_RejectType_datexReject_Publication_cd(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_RejectType_datexReject_Publication_cd(value)) < 0) return ret;
	return ret;
}

/********************************************************
*RejectType-rejectPublicationData_datexReject-PublicationData-cd*
********************************************************/
int ASN1_Print_RejectType_rejectPublicationData_datexReject_PublicationData_cd(RejectType_rejectPublicationData_datexReject_PublicationData_cd *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch(*value)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("RejectType-rejectPublicationData_datexReject-PublicationData-cd", "other", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("RejectType-rejectPublicationData_datexReject-PublicationData-cd", "unknownSubscription", 1)) < 0) return ret; break;
	case 2: if ((ret = ASN1_Print_ENUMERATED("RejectType-rejectPublicationData_datexReject-PublicationData-cd", "unknownPublicationNbr", 2)) < 0) return ret; break;
	case 3: if ((ret = ASN1_Print_ENUMERATED("RejectType-rejectPublicationData_datexReject-PublicationData-cd", "unknownPublicationMsgId", 3)) < 0) return ret; break;
	case 4: if ((ret = ASN1_Print_ENUMERATED("RejectType-rejectPublicationData_datexReject-PublicationData-cd", "invalidPublicationMsgId", 4)) < 0) return ret; break;
	case 5: if ((ret = ASN1_Print_ENUMERATED("RejectType-rejectPublicationData_datexReject-PublicationData-cd", "invalidPublicationMsgContent", 5)) < 0) return ret; break;
	case 6: if ((ret = ASN1_Print_ENUMERATED("RejectType-rejectPublicationData_datexReject-PublicationData-cd", "repeatedPublicationNbr", 6)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	return ret;
}
int ASN1_CHECK_RejectType_rejectPublicationData_datexReject_PublicationData_cd(RejectType_rejectPublicationData_datexReject_PublicationData_cd *value)
{
	unsigned char checkinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd[] = {0x07,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x00 };
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32 *)value, checkinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Enc_RejectType_rejectPublicationData_datexReject_PublicationData_cd(ASN1WorkSpace *workspace, RejectType_rejectPublicationData_datexReject_PublicationData_cd *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_ENUMERATED(workspace, (ASNINT32 *)value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Enc_RejectType_rejectPublicationData_datexReject_PublicationData_cd(ASN1WorkSpace *workspace, RejectType_rejectPublicationData_datexReject_PublicationData_cd *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_RejectType_rejectPublicationData_datexReject_PublicationData_cd(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_RejectType_rejectPublicationData_datexReject_PublicationData_cd(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Data_Dec_RejectType_rejectPublicationData_datexReject_PublicationData_cd(ASN1WorkSpace *workspace, RejectType_rejectPublicationData_datexReject_PublicationData_cd *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	if ((ret = ASN1_BER_Dec_ENUMERATED(workspace, (ASNINT32*)value, len, tagFlag)) < 0) return ret;
	return ret;
}
int ASN1_BER_Dec_RejectType_rejectPublicationData_datexReject_PublicationData_cd(ASN1WorkSpace *workspace, RejectType_rejectPublicationData_datexReject_PublicationData_cd *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_RejectType_rejectPublicationData_datexReject_PublicationData_cd(workspace, value, length, tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_RejectType_rejectPublicationData_datexReject_PublicationData_cd(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_RejectType_rejectPublicationData_datexReject_PublicationData_cd(ASN1WorkSpace *workspace, RejectType_rejectPublicationData_datexReject_PublicationData_cd *value)
{
	struct Asn1ConsInfo consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd;
	switch(*value)
	{
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_other: ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd = 0; consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd.enumextbit = 0; break;
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownSubscription: ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd = 1; consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd.enumextbit = 0; break;
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownPublicationNbr: ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd = 2; consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd.enumextbit = 0; break;
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownPublicationMsgId: ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd = 3; consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd.enumextbit = 0; break;
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_invalidPublicationMsgId: ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd = 4; consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd.enumextbit = 0; break;
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_invalidPublicationMsgContent: ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd = 5; consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd.enumextbit = 0; break;
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_repeatedPublicationNbr: ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd = 6; consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd.enumextbit = 0; break;
	default: ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd = *value; consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd.enumextbit = 1; break;
	}
	if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd, &consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Enc_RejectType_rejectPublicationData_datexReject_PublicationData_cd(ASN1WorkSpace *workspace, RejectType_rejectPublicationData_datexReject_PublicationData_cd *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_RejectType_rejectPublicationData_datexReject_PublicationData_cd(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_RejectType_rejectPublicationData_datexReject_PublicationData_cd(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_RejectType_rejectPublicationData_datexReject_PublicationData_cd(ASN1WorkSpace *workspace, RejectType_rejectPublicationData_datexReject_PublicationData_cd *value)
{
	struct Asn1ConsInfo consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd;
	if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd, &consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd)) < 0) return ret;
	if (consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd.enumextbit == 0)
	{
		switch(ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd)
		{
		case 0: *value = RejectType_rejectPublicationData_datexReject_PublicationData_cd_other; break;
		case 1: *value = RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownSubscription; break;
		case 2: *value = RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownPublicationNbr; break;
		case 3: *value = RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownPublicationMsgId; break;
		case 4: *value = RejectType_rejectPublicationData_datexReject_PublicationData_cd_invalidPublicationMsgId; break;
		case 5: *value = RejectType_rejectPublicationData_datexReject_PublicationData_cd_invalidPublicationMsgContent; break;
		case 6: *value = RejectType_rejectPublicationData_datexReject_PublicationData_cd_repeatedPublicationNbr; break;
		default: break;
		}
	}
	else
	{
		switch(ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd)
		{
		default: *value = ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd; break;
		}
	}
	return ret;
}
int ASN1_PER_Align_Dec_RejectType_rejectPublicationData_datexReject_PublicationData_cd(ASN1WorkSpace *workspace, RejectType_rejectPublicationData_datexReject_PublicationData_cd *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_RejectType_rejectPublicationData_datexReject_PublicationData_cd(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_RejectType_rejectPublicationData_datexReject_PublicationData_cd(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_RejectType_rejectPublicationData_datexReject_PublicationData_cd(ASN1WorkSpace *workspace, RejectType_rejectPublicationData_datexReject_PublicationData_cd *value)
{
	struct Asn1ConsInfo consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd;
	switch(*value)
	{
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_other: ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd = 0; consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd.enumextbit = 0; break;
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownSubscription: ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd = 1; consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd.enumextbit = 0; break;
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownPublicationNbr: ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd = 2; consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd.enumextbit = 0; break;
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownPublicationMsgId: ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd = 3; consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd.enumextbit = 0; break;
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_invalidPublicationMsgId: ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd = 4; consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd.enumextbit = 0; break;
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_invalidPublicationMsgContent: ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd = 5; consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd.enumextbit = 0; break;
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_repeatedPublicationNbr: ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd = 6; consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd.enumextbit = 0; break;
	default: ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd = *value; consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd.enumextbit = 1; break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd, &consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Enc_RejectType_rejectPublicationData_datexReject_PublicationData_cd(ASN1WorkSpace *workspace, RejectType_rejectPublicationData_datexReject_PublicationData_cd *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_RejectType_rejectPublicationData_datexReject_PublicationData_cd(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_RejectType_rejectPublicationData_datexReject_PublicationData_cd(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_RejectType_rejectPublicationData_datexReject_PublicationData_cd(ASN1WorkSpace *workspace, RejectType_rejectPublicationData_datexReject_PublicationData_cd *value)
{
	struct Asn1ConsInfo consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd;
	if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd, &consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd)) < 0) return ret;
	if (consinfo_RejectType_rejectPublicationData_datexReject_PublicationData_cd.enumextbit == 0)
	{
		switch(ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd)
		{
		case 0: *value = RejectType_rejectPublicationData_datexReject_PublicationData_cd_other; break;
		case 1: *value = RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownSubscription; break;
		case 2: *value = RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownPublicationNbr; break;
		case 3: *value = RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownPublicationMsgId; break;
		case 4: *value = RejectType_rejectPublicationData_datexReject_PublicationData_cd_invalidPublicationMsgId; break;
		case 5: *value = RejectType_rejectPublicationData_datexReject_PublicationData_cd_invalidPublicationMsgContent; break;
		case 6: *value = RejectType_rejectPublicationData_datexReject_PublicationData_cd_repeatedPublicationNbr; break;
		default: break;
		}
	}
	else
	{
		switch(ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd)
		{
		default: *value = ui_RejectType_rejectPublicationData_datexReject_PublicationData_cd; break;
		}
	}
	return ret;
}
int ASN1_PER_UNAlign_Dec_RejectType_rejectPublicationData_datexReject_PublicationData_cd(ASN1WorkSpace *workspace, RejectType_rejectPublicationData_datexReject_PublicationData_cd *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_RejectType_rejectPublicationData_datexReject_PublicationData_cd(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_RejectType_rejectPublicationData_datexReject_PublicationData_cd(value)) < 0) return ret;
	return ret;
}

/********************************************************
*RejectType_rejectPublicationData                       *
********************************************************/
int ASN1_Print_RejectType_rejectPublicationData(RejectType_rejectPublicationData *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("RejectType-rejectPublicationData");
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("datexReject_SubscriptionSerial_nbr", &(value->datexReject_SubscriptionSerial_nbr))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("datexReject_PublicationSerial_nbr", &(value->datexReject_PublicationSerial_nbr))) < 0) return ret;
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	switch(value->datexReject_PublicationData_cd)
	{
	case 0: if ((ret = ASN1_Print_ENUMERATED("RejectType-rejectPublicationData_datexReject-PublicationData-cd", "other", 0)) < 0) return ret; break;
	case 1: if ((ret = ASN1_Print_ENUMERATED("RejectType-rejectPublicationData_datexReject-PublicationData-cd", "unknownSubscription", 1)) < 0) return ret; break;
	case 2: if ((ret = ASN1_Print_ENUMERATED("RejectType-rejectPublicationData_datexReject-PublicationData-cd", "unknownPublicationNbr", 2)) < 0) return ret; break;
	case 3: if ((ret = ASN1_Print_ENUMERATED("RejectType-rejectPublicationData_datexReject-PublicationData-cd", "unknownPublicationMsgId", 3)) < 0) return ret; break;
	case 4: if ((ret = ASN1_Print_ENUMERATED("RejectType-rejectPublicationData_datexReject-PublicationData-cd", "invalidPublicationMsgId", 4)) < 0) return ret; break;
	case 5: if ((ret = ASN1_Print_ENUMERATED("RejectType-rejectPublicationData_datexReject-PublicationData-cd", "invalidPublicationMsgContent", 5)) < 0) return ret; break;
	case 6: if ((ret = ASN1_Print_ENUMERATED("RejectType-rejectPublicationData_datexReject-PublicationData-cd", "repeatedPublicationNbr", 6)) < 0) return ret; break;
	default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
	};
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_RejectType_rejectPublicationData_datexReject_SubscriptionSerial_nbr(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->datexReject_SubscriptionSerial_nbr, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_RejectType_rejectPublicationData_datexReject_PublicationSerial_nbr(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->datexReject_PublicationSerial_nbr, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_RejectType_rejectPublicationData_datexReject_PublicationData_cd(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value, ENUMERATED user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_ENUMERATED(workspace, (ASNINT32*)&value->datexReject_PublicationData_cd, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_RejectType_rejectPublicationData_datexReject_SubscriptionSerial_nbr(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->datexReject_SubscriptionSerial_nbr, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_RejectType_rejectPublicationData_datexReject_PublicationSerial_nbr(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->datexReject_PublicationSerial_nbr, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_RejectType_rejectPublicationData_datexReject_PublicationData_cd(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->datexReject_PublicationData_cd, user_value)) < 0) return ret;
	return ret;
}
int ASN1_CHECK_RejectType_rejectPublicationData(RejectType_rejectPublicationData *value)
{
	int ret = 0;

	unsigned char checkinfo_datexReject_SubscriptionSerial_nbr[] = { 
		0x02,0x00,0x85,0x00,0xFF,0xFF,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_datexReject_PublicationSerial_nbr[] = { 
		0x02,0x00,0x85,0x00,0xFF,0xFF,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_datexReject_PublicationData_cd[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(&(value->datexReject_SubscriptionSerial_nbr), checkinfo_datexReject_SubscriptionSerial_nbr)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->datexReject_PublicationSerial_nbr), checkinfo_datexReject_PublicationSerial_nbr)) < 0) return ret;
	if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->datexReject_PublicationData_cd), checkinfo_datexReject_PublicationData_cd)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Enc_RejectType_rejectPublicationData_datexReject_PublicationData_cd(ASN1WorkSpace *workspace, RejectType_rejectPublicationData_datexReject_PublicationData_cd *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->datexReject_SubscriptionSerial_nbr), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->datexReject_PublicationSerial_nbr), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_RejectType_rejectPublicationData_datexReject_PublicationData_cd(workspace, &(value->datexReject_PublicationData_cd), ASN1IMPL)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_RejectType_rejectPublicationData(RejectType_rejectPublicationData *value);
extern int ASN1_BER_Data_Enc_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_RejectType_rejectPublicationData(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_RejectType_rejectPublicationData(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_RejectType_rejectPublicationData_datexReject_PublicationData_cd(ASN1WorkSpace *workspace, RejectType_rejectPublicationData_datexReject_PublicationData_cd *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8 *_cpointer;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->datexReject_SubscriptionSerial_nbr, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->datexReject_PublicationSerial_nbr, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_RejectType_rejectPublicationData_datexReject_PublicationData_cd(workspace, &value->datexReject_PublicationData_cd, len, ASN1IMPL)) < 0) return ret;
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_RejectType_rejectPublicationData(RejectType_rejectPublicationData *value);
extern int ASN1_BER_Data_Dec_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_RejectType_rejectPublicationData(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_RejectType_rejectPublicationData(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Enc_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value)
{
	int ret = 0;
	ASNINT32 ui_datexReject_PublicationData_cd;
	struct Asn1ConsInfo consinfo_datexReject_SubscriptionSerial_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexReject_PublicationSerial_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexReject_PublicationData_cd = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };

	if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->datexReject_SubscriptionSerial_nbr), &consinfo_datexReject_SubscriptionSerial_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->datexReject_PublicationSerial_nbr), &consinfo_datexReject_PublicationSerial_nbr)) < 0) return ret;
	switch(value->datexReject_PublicationData_cd)
	{
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_other: ui_datexReject_PublicationData_cd = 0; consinfo_datexReject_PublicationData_cd.enumextbit = 0; break;
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownSubscription: ui_datexReject_PublicationData_cd = 1; consinfo_datexReject_PublicationData_cd.enumextbit = 0; break;
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownPublicationNbr: ui_datexReject_PublicationData_cd = 2; consinfo_datexReject_PublicationData_cd.enumextbit = 0; break;
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownPublicationMsgId: ui_datexReject_PublicationData_cd = 3; consinfo_datexReject_PublicationData_cd.enumextbit = 0; break;
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_invalidPublicationMsgId: ui_datexReject_PublicationData_cd = 4; consinfo_datexReject_PublicationData_cd.enumextbit = 0; break;
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_invalidPublicationMsgContent: ui_datexReject_PublicationData_cd = 5; consinfo_datexReject_PublicationData_cd.enumextbit = 0; break;
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_repeatedPublicationNbr: ui_datexReject_PublicationData_cd = 6; consinfo_datexReject_PublicationData_cd.enumextbit = 0; break;
	default: ui_datexReject_PublicationData_cd = value->datexReject_PublicationData_cd; consinfo_datexReject_PublicationData_cd.enumextbit = 1;break;
	}
	if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_datexReject_PublicationData_cd, &consinfo_datexReject_PublicationData_cd)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_RejectType_rejectPublicationData(RejectType_rejectPublicationData *value);
extern int ASN1_PER_Align_Data_Enc_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value);
int ASN1_PER_Align_Enc_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_RejectType_rejectPublicationData(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_RejectType_rejectPublicationData(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_Align_Data_Dec_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value)
{
	int ret = 0;
	ASNINT32 ui_datexReject_PublicationData_cd;
	struct Asn1ConsInfo consinfo_datexReject_SubscriptionSerial_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexReject_PublicationSerial_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexReject_PublicationData_cd = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };

	if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->datexReject_SubscriptionSerial_nbr), &consinfo_datexReject_SubscriptionSerial_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->datexReject_PublicationSerial_nbr), &consinfo_datexReject_PublicationSerial_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_datexReject_PublicationData_cd, &consinfo_datexReject_PublicationData_cd)) < 0) return ret;
	if (consinfo_datexReject_PublicationData_cd.enumextbit == 0)
	{
		switch(ui_datexReject_PublicationData_cd)
		{
		case 0: value->datexReject_PublicationData_cd = RejectType_rejectPublicationData_datexReject_PublicationData_cd_other; break;
		case 1: value->datexReject_PublicationData_cd = RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownSubscription; break;
		case 2: value->datexReject_PublicationData_cd = RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownPublicationNbr; break;
		case 3: value->datexReject_PublicationData_cd = RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownPublicationMsgId; break;
		case 4: value->datexReject_PublicationData_cd = RejectType_rejectPublicationData_datexReject_PublicationData_cd_invalidPublicationMsgId; break;
		case 5: value->datexReject_PublicationData_cd = RejectType_rejectPublicationData_datexReject_PublicationData_cd_invalidPublicationMsgContent; break;
		case 6: value->datexReject_PublicationData_cd = RejectType_rejectPublicationData_datexReject_PublicationData_cd_repeatedPublicationNbr; break;
		default: break;
		}
	}
	else
	{
		switch(ui_datexReject_PublicationData_cd)
		{
		default: value->datexReject_PublicationData_cd = ui_datexReject_PublicationData_cd; break;
		}
	}
	return ret;
}
extern int ASN1_CHECK_RejectType_rejectPublicationData(RejectType_rejectPublicationData *value);
extern int ASN1_PER_Align_Data_Dec_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value);
int ASN1_PER_Align_Dec_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_RejectType_rejectPublicationData(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_RejectType_rejectPublicationData(value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Enc_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value)
{
	int ret = 0;
	ASNINT32 ui_datexReject_PublicationData_cd;
	struct Asn1ConsInfo consinfo_datexReject_SubscriptionSerial_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexReject_PublicationSerial_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexReject_PublicationData_cd = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };

	if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->datexReject_SubscriptionSerial_nbr), &consinfo_datexReject_SubscriptionSerial_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->datexReject_PublicationSerial_nbr), &consinfo_datexReject_PublicationSerial_nbr)) < 0) return ret;
	switch(value->datexReject_PublicationData_cd)
	{
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_other: ui_datexReject_PublicationData_cd = 0; consinfo_datexReject_PublicationData_cd.enumextbit = 0; break;
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownSubscription: ui_datexReject_PublicationData_cd = 1; consinfo_datexReject_PublicationData_cd.enumextbit = 0; break;
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownPublicationNbr: ui_datexReject_PublicationData_cd = 2; consinfo_datexReject_PublicationData_cd.enumextbit = 0; break;
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownPublicationMsgId: ui_datexReject_PublicationData_cd = 3; consinfo_datexReject_PublicationData_cd.enumextbit = 0; break;
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_invalidPublicationMsgId: ui_datexReject_PublicationData_cd = 4; consinfo_datexReject_PublicationData_cd.enumextbit = 0; break;
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_invalidPublicationMsgContent: ui_datexReject_PublicationData_cd = 5; consinfo_datexReject_PublicationData_cd.enumextbit = 0; break;
	case RejectType_rejectPublicationData_datexReject_PublicationData_cd_repeatedPublicationNbr: ui_datexReject_PublicationData_cd = 6; consinfo_datexReject_PublicationData_cd.enumextbit = 0; break;
	default: ui_datexReject_PublicationData_cd = value->datexReject_PublicationData_cd; consinfo_datexReject_PublicationData_cd.enumextbit = 1;break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_datexReject_PublicationData_cd, &consinfo_datexReject_PublicationData_cd)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_RejectType_rejectPublicationData(RejectType_rejectPublicationData *value);
extern int ASN1_PER_UNAlign_Data_Enc_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value);
int ASN1_PER_UNAlign_Enc_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_RejectType_rejectPublicationData(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_RejectType_rejectPublicationData(workspace,value)) < 0) return ret;
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value)
{
	int ret = 0;
	ASNINT32 ui_datexReject_PublicationData_cd;
	struct Asn1ConsInfo consinfo_datexReject_SubscriptionSerial_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexReject_PublicationSerial_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexReject_PublicationData_cd = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };

	if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->datexReject_SubscriptionSerial_nbr), &consinfo_datexReject_SubscriptionSerial_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->datexReject_PublicationSerial_nbr), &consinfo_datexReject_PublicationSerial_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_datexReject_PublicationData_cd, &consinfo_datexReject_PublicationData_cd)) < 0) return ret;
	if (consinfo_datexReject_PublicationData_cd.enumextbit == 0)
	{
		switch(ui_datexReject_PublicationData_cd)
		{
		case 0: value->datexReject_PublicationData_cd = RejectType_rejectPublicationData_datexReject_PublicationData_cd_other; break;
		case 1: value->datexReject_PublicationData_cd = RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownSubscription; break;
		case 2: value->datexReject_PublicationData_cd = RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownPublicationNbr; break;
		case 3: value->datexReject_PublicationData_cd = RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownPublicationMsgId; break;
		case 4: value->datexReject_PublicationData_cd = RejectType_rejectPublicationData_datexReject_PublicationData_cd_invalidPublicationMsgId; break;
		case 5: value->datexReject_PublicationData_cd = RejectType_rejectPublicationData_datexReject_PublicationData_cd_invalidPublicationMsgContent; break;
		case 6: value->datexReject_PublicationData_cd = RejectType_rejectPublicationData_datexReject_PublicationData_cd_repeatedPublicationNbr; break;
		default: break;
		}
	}
	else
	{
		switch(ui_datexReject_PublicationData_cd)
		{
		default: value->datexReject_PublicationData_cd = ui_datexReject_PublicationData_cd; break;
		}
	}
	return ret;
}
extern int ASN1_CHECK_RejectType_rejectPublicationData(RejectType_rejectPublicationData *value);
extern int ASN1_PER_UNAlign_Data_Dec_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value);
int ASN1_PER_UNAlign_Dec_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_RejectType_rejectPublicationData(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_RejectType_rejectPublicationData(value)) < 0) return ret;
	return ret;
}

/********************************************************
*RejectType                                             *
********************************************************/
int ASN1_Print_RejectType(RejectType *value, int tab_value)
{
	int ret = 0;
	// CHOICE : t->tempIdentifier is Upper Letter
	ASN1_Print_CHOICE("RejectType");
	if (value == NULL) return -1;
	switch (value->M) {
	case DEF_RejectType_datexReject_Login_cd:
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		switch(value->elements.datexReject_Login_cd)
		{
		case 0: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Login-cd", "other", 0)) < 0) return ret; break;
		case 1: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Login-cd", "unknownDomainName", 1)) < 0) return ret; break;
		case 2: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Login-cd", "accessDenied", 2)) < 0) return ret; break;
		case 3: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Login-cd", "invalidNamePassword", 3)) < 0) return ret; break;
		case 4: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Login-cd", "timeoutTooSmall", 4)) < 0) return ret; break;
		case 5: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Login-cd", "timeoutTooLarge", 5)) < 0) return ret; break;
		case 6: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Login-cd", "heartbeatTooSmall", 6)) < 0) return ret; break;
		case 7: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Login-cd", "heartbeatTooLarge", 7)) < 0) return ret; break;
		case 8: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Login-cd", "sessionExists", 8)) < 0) return ret; break;
		case 9: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Login-cd", "maxSessionsReached", 9)) < 0) return ret; break;
		default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
		};
		if (ret != 0) return -1;
		break;
	case DEF_RejectType_datexReject_Subscription_cd:
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		switch(value->elements.datexReject_Subscription_cd)
		{
		case 0: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Subscription-cd", "other", 0)) < 0) return ret; break;
		case 1: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Subscription-cd", "unknownSubscriptionNbr", 1)) < 0) return ret; break;
		case 2: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Subscription-cd", "invalidTimes", 2)) < 0) return ret; break;
		case 3: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Subscription-cd", "frequencyTooSmall", 3)) < 0) return ret; break;
		case 4: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Subscription-cd", "frequencyTooLarge", 4)) < 0) return ret; break;
		case 5: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Subscription-cd", "invalid-mode", 5)) < 0) return ret; break;
		case 6: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Subscription-cd", "publishFormatNotSupported", 6)) < 0) return ret; break;
		case 7: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Subscription-cd", "unknowSubscriptionMsgId", 7)) < 0) return ret; break;
		case 8: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Subscription-cd", "invalidSubscriptionMsgId", 8)) < 0) return ret; break;
		case 9: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Subscription-cd", "invalidSubscriptionContent", 9)) < 0) return ret; break;
		default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
		};
		if (ret != 0) return -1;
		break;
	case DEF_RejectType_datexReject_Publication_cd:
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		switch(value->elements.datexReject_Publication_cd)
		{
		case 0: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Publication-cd", "other", 0)) < 0) return ret; break;
		case 1: if ((ret = ASN1_Print_ENUMERATED("RejectType-datexReject-Publication-cd", "invalidPublishFormat", 1)) < 0) return ret; break;
		default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
		};
		if (ret != 0) return -1;
		break;
	case DEF_RejectType_rejectPublicationData:
		// Type Reference RejectType_rejectPublicationData
		if (Compare_Letter(tab_value, "rejectPublicationData")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("rejectPublicationData = ");
		}
		if ((ret = ASN1_Print_RejectType_rejectPublicationData((RejectType_rejectPublicationData *)value->elements.rejectPublicationData, tab_value + 1)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: return -1;
}
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_RejectType_datexReject_Login_cd(ASN1WorkSpace *workspace, RejectType *value, ENUMERATED user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->M = DEF_RejectType_datexReject_Login_cd;
	if ((ret = ASN1_SET_ENUMERATED(workspace, (ASNINT32*)&value->elements.datexReject_Login_cd, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_RejectType_datexReject_Subscription_cd(ASN1WorkSpace *workspace, RejectType *value, ENUMERATED user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->M = DEF_RejectType_datexReject_Subscription_cd;
	if ((ret = ASN1_SET_ENUMERATED(workspace, (ASNINT32*)&value->elements.datexReject_Subscription_cd, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_RejectType_datexReject_Publication_cd(ASN1WorkSpace *workspace, RejectType *value, ENUMERATED user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->M = DEF_RejectType_datexReject_Publication_cd;
	if ((ret = ASN1_SET_ENUMERATED(workspace, (ASNINT32*)&value->elements.datexReject_Publication_cd, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType *value, RejectType_rejectPublicationData *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->elements.rejectPublicationData = (RejectType_rejectPublicationData *)mpool_malloc(workspace->Pmemory, sizeof(RejectType_rejectPublicationData));
	memset(value->elements.rejectPublicationData, 0, sizeof(RejectType_rejectPublicationData));
	value->M = DEF_RejectType_rejectPublicationData;
	memmove(value->elements.rejectPublicationData, user_value, sizeof(RejectType_rejectPublicationData));
	return ret;
}
int ASN1_GET_RejectType_datexReject_Login_cd(ASN1WorkSpace *workspace, RejectType *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->M == DEF_RejectType_datexReject_Login_cd)
	{
		if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->elements.datexReject_Login_cd, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_RejectType_datexReject_Subscription_cd(ASN1WorkSpace *workspace, RejectType *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->M == DEF_RejectType_datexReject_Subscription_cd)
	{
		if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->elements.datexReject_Subscription_cd, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_RejectType_datexReject_Publication_cd(ASN1WorkSpace *workspace, RejectType *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->M == DEF_RejectType_datexReject_Publication_cd)
	{
		if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->elements.datexReject_Publication_cd, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType *value, RejectType_rejectPublicationData **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->M == DEF_RejectType_rejectPublicationData)
	{
		*user_value = value->elements.rejectPublicationData;
	}
	else return -2;
	return ret;
}
extern int ASN1_CHECK_RejectType_rejectPublicationData(RejectType_rejectPublicationData *value);
int ASN1_CHECK_RejectType(RejectType *value)
{
	int ret = 0;

	unsigned char checkinfo_datexReject_Login_cd[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datexReject_Subscription_cd[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datexReject_Publication_cd[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_rejectPublicationData[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_RejectType_datexReject_Login_cd:
		if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&value->elements.datexReject_Login_cd, checkinfo_datexReject_Login_cd)) < 0) return ret;
		break;
	case DEF_RejectType_datexReject_Subscription_cd:
		if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&value->elements.datexReject_Subscription_cd, checkinfo_datexReject_Subscription_cd)) < 0) return ret;
		break;
	case DEF_RejectType_datexReject_Publication_cd:
		if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&value->elements.datexReject_Publication_cd, checkinfo_datexReject_Publication_cd)) < 0) return ret;
		break;
	case DEF_RejectType_rejectPublicationData:
		if ((ret = ASN1_CHECK_RejectType_rejectPublicationData(value->elements.rejectPublicationData)) < 0) return ret;
		break;
	default: break;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_RejectType_datexReject_Login_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Login_cd *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_RejectType_datexReject_Subscription_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Subscription_cd *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_RejectType_datexReject_Publication_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Publication_cd *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_RejectType(ASN1WorkSpace *workspace, RejectType *value, ASN1TagType tagFlag)
{
	int ret = 0;
	switch(value->M)
	{
	case DEF_RejectType_datexReject_Login_cd:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_RejectType_datexReject_Login_cd(workspace, &(value->elements.datexReject_Login_cd), ASN1IMPL)) < 0) return ret;
		break;
	case DEF_RejectType_datexReject_Subscription_cd:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_RejectType_datexReject_Subscription_cd(workspace, &(value->elements.datexReject_Subscription_cd), ASN1IMPL)) < 0) return ret;
		break;
	case DEF_RejectType_datexReject_Publication_cd:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_RejectType_datexReject_Publication_cd(workspace, &(value->elements.datexReject_Publication_cd), ASN1IMPL)) < 0) return ret;
		break;
	case DEF_RejectType_rejectPublicationData:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 3)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_RejectType_rejectPublicationData(workspace, value->elements.rejectPublicationData, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
		break;
	}
	return ret;
}
extern int ASN1_CHECK_RejectType(RejectType *value);
extern int ASN1_BER_Data_Enc_RejectType(ASN1WorkSpace *workspace, RejectType *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_RejectType(ASN1WorkSpace *workspace, RejectType *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_RejectType(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_RejectType(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_RejectType_datexReject_Login_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Login_cd *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_RejectType_datexReject_Subscription_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Subscription_cd *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_RejectType_datexReject_Publication_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Publication_cd *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_RejectType(ASN1WorkSpace *workspace, RejectType *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	value->M = 0;
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	switch(tag)
	{
	case ITS_ASN_CONT | ITS_ASN_PRIM | 0:
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_RejectType_datexReject_Login_cd(workspace, &value->elements.datexReject_Login_cd, len, ASN1IMPL)) < 0) return ret;
		value->M = DEF_RejectType_datexReject_Login_cd;
		break;
	case ITS_ASN_CONT | ITS_ASN_PRIM | 1:
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_RejectType_datexReject_Subscription_cd(workspace, &value->elements.datexReject_Subscription_cd, len, ASN1IMPL)) < 0) return ret;
		value->M = DEF_RejectType_datexReject_Subscription_cd;
		break;
	case ITS_ASN_CONT | ITS_ASN_PRIM | 2:
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_RejectType_datexReject_Publication_cd(workspace, &value->elements.datexReject_Publication_cd, len, ASN1IMPL)) < 0) return ret;
		value->M = DEF_RejectType_datexReject_Publication_cd;
		break;
	case ITS_ASN_CONT | ITS_ASN_CONS | 3:
		value->elements.rejectPublicationData = (RejectType_rejectPublicationData *)mpool_malloc(workspace->Pmemory, sizeof(RejectType_rejectPublicationData));
		memset(value->elements.rejectPublicationData, 0, sizeof(RejectType_rejectPublicationData));
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 3)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_RejectType_rejectPublicationData(workspace, value->elements.rejectPublicationData, len, ASN1IMPL)) < 0) return ret;
		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->M = DEF_RejectType_rejectPublicationData;
		break;
	}
	return ret;
}
extern int ASN1_CHECK_RejectType(RejectType *value);
extern int ASN1_BER_Data_Dec_RejectType(ASN1WorkSpace *workspace, RejectType *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_RejectType(ASN1WorkSpace *workspace, RejectType *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_RejectType(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_RejectType(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Enc_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value);
int ASN1_PER_Align_Data_Enc_RejectType(ASN1WorkSpace *workspace, RejectType *value)
{
	int ret = 0;
	ASNINT32 ui_datexReject_Login_cd;
	ASNINT32 ui_datexReject_Subscription_cd;
	ASNINT32 ui_datexReject_Publication_cd;
	struct Asn1ConsInfo consinfo_datexReject_Login_cd = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexReject_Subscription_cd = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexReject_Publication_cd = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_rejectPublicationData = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT64 ui;
	ASNBOOL extbit = 1;
	switch(value->M)
	{
	case DEF_RejectType_datexReject_Login_cd: ui = 0; extbit = 0; break;
	case DEF_RejectType_datexReject_Subscription_cd: ui = 1; extbit = 0; break;
	case DEF_RejectType_datexReject_Publication_cd: ui = 2; extbit = 0; break;
	case DEF_RejectType_rejectPublicationData: ui = 3; extbit = 0; break;
	default: break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_Choice_ENUMERATED(workspace, ui, extbit, 0, 4)) < 0) return ret;
	switch(value->M)
	{
	case DEF_RejectType_datexReject_Login_cd:
		switch(value->elements.datexReject_Login_cd)
		{
		case RejectType_datexReject_Login_cd_other: ui_datexReject_Login_cd = 0; consinfo_datexReject_Login_cd.enumextbit = 0; break;
		case RejectType_datexReject_Login_cd_unknownDomainName: ui_datexReject_Login_cd = 1; consinfo_datexReject_Login_cd.enumextbit = 0; break;
		case RejectType_datexReject_Login_cd_accessDenied: ui_datexReject_Login_cd = 2; consinfo_datexReject_Login_cd.enumextbit = 0; break;
		case RejectType_datexReject_Login_cd_invalidNamePassword: ui_datexReject_Login_cd = 3; consinfo_datexReject_Login_cd.enumextbit = 0; break;
		case RejectType_datexReject_Login_cd_timeoutTooSmall: ui_datexReject_Login_cd = 4; consinfo_datexReject_Login_cd.enumextbit = 0; break;
		case RejectType_datexReject_Login_cd_timeoutTooLarge: ui_datexReject_Login_cd = 5; consinfo_datexReject_Login_cd.enumextbit = 0; break;
		case RejectType_datexReject_Login_cd_heartbeatTooSmall: ui_datexReject_Login_cd = 6; consinfo_datexReject_Login_cd.enumextbit = 0; break;
		case RejectType_datexReject_Login_cd_heartbeatTooLarge: ui_datexReject_Login_cd = 7; consinfo_datexReject_Login_cd.enumextbit = 0; break;
		case RejectType_datexReject_Login_cd_sessionExists: ui_datexReject_Login_cd = 8; consinfo_datexReject_Login_cd.enumextbit = 0; break;
		case RejectType_datexReject_Login_cd_maxSessionsReached: ui_datexReject_Login_cd = 9; consinfo_datexReject_Login_cd.enumextbit = 0; break;
		default: ui_datexReject_Login_cd = value->elements.datexReject_Login_cd; consinfo_datexReject_Login_cd.enumextbit = 1;break;
		}
		if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_datexReject_Login_cd, &consinfo_datexReject_Login_cd)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_RejectType_datexReject_Subscription_cd:
		switch(value->elements.datexReject_Subscription_cd)
		{
		case RejectType_datexReject_Subscription_cd_other: ui_datexReject_Subscription_cd = 0; consinfo_datexReject_Subscription_cd.enumextbit = 0; break;
		case RejectType_datexReject_Subscription_cd_unknownSubscriptionNbr: ui_datexReject_Subscription_cd = 1; consinfo_datexReject_Subscription_cd.enumextbit = 0; break;
		case RejectType_datexReject_Subscription_cd_invalidTimes: ui_datexReject_Subscription_cd = 2; consinfo_datexReject_Subscription_cd.enumextbit = 0; break;
		case RejectType_datexReject_Subscription_cd_frequencyTooSmall: ui_datexReject_Subscription_cd = 3; consinfo_datexReject_Subscription_cd.enumextbit = 0; break;
		case RejectType_datexReject_Subscription_cd_frequencyTooLarge: ui_datexReject_Subscription_cd = 4; consinfo_datexReject_Subscription_cd.enumextbit = 0; break;
		case RejectType_datexReject_Subscription_cd_invalid_mode: ui_datexReject_Subscription_cd = 5; consinfo_datexReject_Subscription_cd.enumextbit = 0; break;
		case RejectType_datexReject_Subscription_cd_publishFormatNotSupported: ui_datexReject_Subscription_cd = 6; consinfo_datexReject_Subscription_cd.enumextbit = 0; break;
		case RejectType_datexReject_Subscription_cd_unknowSubscriptionMsgId: ui_datexReject_Subscription_cd = 7; consinfo_datexReject_Subscription_cd.enumextbit = 0; break;
		case RejectType_datexReject_Subscription_cd_invalidSubscriptionMsgId: ui_datexReject_Subscription_cd = 8; consinfo_datexReject_Subscription_cd.enumextbit = 0; break;
		case RejectType_datexReject_Subscription_cd_invalidSubscriptionContent: ui_datexReject_Subscription_cd = 9; consinfo_datexReject_Subscription_cd.enumextbit = 0; break;
		default: ui_datexReject_Subscription_cd = value->elements.datexReject_Subscription_cd; consinfo_datexReject_Subscription_cd.enumextbit = 1;break;
		}
		if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_datexReject_Subscription_cd, &consinfo_datexReject_Subscription_cd)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_RejectType_datexReject_Publication_cd:
		switch(value->elements.datexReject_Publication_cd)
		{
		case RejectType_datexReject_Publication_cd_other: ui_datexReject_Publication_cd = 0; consinfo_datexReject_Publication_cd.enumextbit = 0; break;
		case RejectType_datexReject_Publication_cd_invalidPublishFormat: ui_datexReject_Publication_cd = 1; consinfo_datexReject_Publication_cd.enumextbit = 0; break;
		default: ui_datexReject_Publication_cd = value->elements.datexReject_Publication_cd; consinfo_datexReject_Publication_cd.enumextbit = 1;break;
		}
		if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_datexReject_Publication_cd, &consinfo_datexReject_Publication_cd)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_RejectType_rejectPublicationData:
		if ((ret = ASN1_PER_Align_Enc_RejectType_rejectPublicationData(workspace, value->elements.rejectPublicationData)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: break;
	}
	return ret;
}
extern int ASN1_CHECK_RejectType(RejectType *value);
extern int ASN1_PER_Align_Data_Enc_RejectType(ASN1WorkSpace *workspace, RejectType *value);
int ASN1_PER_Align_Enc_RejectType(ASN1WorkSpace *workspace, RejectType *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_RejectType(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_RejectType(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Dec_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value);
int ASN1_PER_Align_Data_Dec_RejectType(ASN1WorkSpace *workspace, RejectType *value)
{
	int ret = 0;
	ASNINT32 ui_datexReject_Login_cd;
	ASNINT32 ui_datexReject_Subscription_cd;
	ASNINT32 ui_datexReject_Publication_cd;
	struct Asn1ConsInfo consinfo_datexReject_Login_cd = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexReject_Subscription_cd = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexReject_Publication_cd = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_rejectPublicationData = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	if ((ret = ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 4)) < 0) return ret;

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_RejectType_datexReject_Login_cd;
			break;
		case 1: index = DEF_RejectType_datexReject_Subscription_cd;
			break;
		case 2: index = DEF_RejectType_datexReject_Publication_cd;
			break;
		case 3: index = DEF_RejectType_rejectPublicationData;
			value->elements.rejectPublicationData = (RejectType_rejectPublicationData *)mpool_malloc(workspace->Pmemory, sizeof(RejectType_rejectPublicationData));
			memset(value->elements.rejectPublicationData, 0, sizeof(RejectType_rejectPublicationData));
			break;
		default: break;
		}
	}
	else
	{
		switch(ui)
		{
		default: break;
		}
	}
	if ((ret = ASN1_GetM(&value->M, index)) < 0) return ret;
	switch(index)
	{
	case DEF_RejectType_datexReject_Login_cd:
		if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_datexReject_Login_cd, &consinfo_datexReject_Login_cd)) < 0) return ret;
		if (consinfo_datexReject_Login_cd.enumextbit == 0)
		{
			switch(ui_datexReject_Login_cd)
			{
			case 0: value->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_other; break;
			case 1: value->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_unknownDomainName; break;
			case 2: value->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_accessDenied; break;
			case 3: value->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_invalidNamePassword; break;
			case 4: value->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_timeoutTooSmall; break;
			case 5: value->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_timeoutTooLarge; break;
			case 6: value->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_heartbeatTooSmall; break;
			case 7: value->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_heartbeatTooLarge; break;
			case 8: value->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_sessionExists; break;
			case 9: value->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_maxSessionsReached; break;
			default: break;
			}
		}
		else
		{
			switch(ui_datexReject_Login_cd)
			{
			default: value->elements.datexReject_Login_cd = ui_datexReject_Login_cd; break;
			}
		}
		if (ret != 0) return -1;
		break;
	case DEF_RejectType_datexReject_Subscription_cd:
		if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_datexReject_Subscription_cd, &consinfo_datexReject_Subscription_cd)) < 0) return ret;
		if (consinfo_datexReject_Subscription_cd.enumextbit == 0)
		{
			switch(ui_datexReject_Subscription_cd)
			{
			case 0: value->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_other; break;
			case 1: value->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_unknownSubscriptionNbr; break;
			case 2: value->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_invalidTimes; break;
			case 3: value->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_frequencyTooSmall; break;
			case 4: value->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_frequencyTooLarge; break;
			case 5: value->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_invalid_mode; break;
			case 6: value->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_publishFormatNotSupported; break;
			case 7: value->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_unknowSubscriptionMsgId; break;
			case 8: value->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_invalidSubscriptionMsgId; break;
			case 9: value->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_invalidSubscriptionContent; break;
			default: break;
			}
		}
		else
		{
			switch(ui_datexReject_Subscription_cd)
			{
			default: value->elements.datexReject_Subscription_cd = ui_datexReject_Subscription_cd; break;
			}
		}
		if (ret != 0) return -1;
		break;
	case DEF_RejectType_datexReject_Publication_cd:
		if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_datexReject_Publication_cd, &consinfo_datexReject_Publication_cd)) < 0) return ret;
		if (consinfo_datexReject_Publication_cd.enumextbit == 0)
		{
			switch(ui_datexReject_Publication_cd)
			{
			case 0: value->elements.datexReject_Publication_cd = RejectType_datexReject_Publication_cd_other; break;
			case 1: value->elements.datexReject_Publication_cd = RejectType_datexReject_Publication_cd_invalidPublishFormat; break;
			default: break;
			}
		}
		else
		{
			switch(ui_datexReject_Publication_cd)
			{
			default: value->elements.datexReject_Publication_cd = ui_datexReject_Publication_cd; break;
			}
		}
		if (ret != 0) return -1;
		break;
	case DEF_RejectType_rejectPublicationData:
		if ((ret = ASN1_PER_Align_Dec_RejectType_rejectPublicationData(workspace, value->elements.rejectPublicationData)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, ALIGN); break;
	}
	return ret;
}
extern int ASN1_CHECK_RejectType(RejectType *value);
extern int ASN1_PER_Align_Data_Dec_RejectType(ASN1WorkSpace *workspace, RejectType *value);
int ASN1_PER_Align_Dec_RejectType(ASN1WorkSpace *workspace, RejectType *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_RejectType(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_RejectType(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Enc_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value);
int ASN1_PER_UNAlign_Data_Enc_RejectType(ASN1WorkSpace *workspace, RejectType *value)
{
	int ret = 0;
	ASNINT32 ui_datexReject_Login_cd;
	ASNINT32 ui_datexReject_Subscription_cd;
	ASNINT32 ui_datexReject_Publication_cd;
	struct Asn1ConsInfo consinfo_datexReject_Login_cd = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexReject_Subscription_cd = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexReject_Publication_cd = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_rejectPublicationData = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT64 ui;
	ASNBOOL extbit = 1;
	switch(value->M)
	{
	case DEF_RejectType_datexReject_Login_cd: ui = 0; extbit = 0; break;
	case DEF_RejectType_datexReject_Subscription_cd: ui = 1; extbit = 0; break;
	case DEF_RejectType_datexReject_Publication_cd: ui = 2; extbit = 0; break;
	case DEF_RejectType_rejectPublicationData: ui = 3; extbit = 0; break;
	default: break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_Choice_ENUMERATED(workspace, ui, extbit, 0, 4)) < 0) return ret;
	switch(value->M)
	{
	case DEF_RejectType_datexReject_Login_cd:
		switch(value->elements.datexReject_Login_cd)
		{
		case RejectType_datexReject_Login_cd_other: ui_datexReject_Login_cd = 0; consinfo_datexReject_Login_cd.enumextbit = 0; break;
		case RejectType_datexReject_Login_cd_unknownDomainName: ui_datexReject_Login_cd = 1; consinfo_datexReject_Login_cd.enumextbit = 0; break;
		case RejectType_datexReject_Login_cd_accessDenied: ui_datexReject_Login_cd = 2; consinfo_datexReject_Login_cd.enumextbit = 0; break;
		case RejectType_datexReject_Login_cd_invalidNamePassword: ui_datexReject_Login_cd = 3; consinfo_datexReject_Login_cd.enumextbit = 0; break;
		case RejectType_datexReject_Login_cd_timeoutTooSmall: ui_datexReject_Login_cd = 4; consinfo_datexReject_Login_cd.enumextbit = 0; break;
		case RejectType_datexReject_Login_cd_timeoutTooLarge: ui_datexReject_Login_cd = 5; consinfo_datexReject_Login_cd.enumextbit = 0; break;
		case RejectType_datexReject_Login_cd_heartbeatTooSmall: ui_datexReject_Login_cd = 6; consinfo_datexReject_Login_cd.enumextbit = 0; break;
		case RejectType_datexReject_Login_cd_heartbeatTooLarge: ui_datexReject_Login_cd = 7; consinfo_datexReject_Login_cd.enumextbit = 0; break;
		case RejectType_datexReject_Login_cd_sessionExists: ui_datexReject_Login_cd = 8; consinfo_datexReject_Login_cd.enumextbit = 0; break;
		case RejectType_datexReject_Login_cd_maxSessionsReached: ui_datexReject_Login_cd = 9; consinfo_datexReject_Login_cd.enumextbit = 0; break;
		default: ui_datexReject_Login_cd = value->elements.datexReject_Login_cd; consinfo_datexReject_Login_cd.enumextbit = 1;break;
		}
		if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_datexReject_Login_cd, &consinfo_datexReject_Login_cd)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_RejectType_datexReject_Subscription_cd:
		switch(value->elements.datexReject_Subscription_cd)
		{
		case RejectType_datexReject_Subscription_cd_other: ui_datexReject_Subscription_cd = 0; consinfo_datexReject_Subscription_cd.enumextbit = 0; break;
		case RejectType_datexReject_Subscription_cd_unknownSubscriptionNbr: ui_datexReject_Subscription_cd = 1; consinfo_datexReject_Subscription_cd.enumextbit = 0; break;
		case RejectType_datexReject_Subscription_cd_invalidTimes: ui_datexReject_Subscription_cd = 2; consinfo_datexReject_Subscription_cd.enumextbit = 0; break;
		case RejectType_datexReject_Subscription_cd_frequencyTooSmall: ui_datexReject_Subscription_cd = 3; consinfo_datexReject_Subscription_cd.enumextbit = 0; break;
		case RejectType_datexReject_Subscription_cd_frequencyTooLarge: ui_datexReject_Subscription_cd = 4; consinfo_datexReject_Subscription_cd.enumextbit = 0; break;
		case RejectType_datexReject_Subscription_cd_invalid_mode: ui_datexReject_Subscription_cd = 5; consinfo_datexReject_Subscription_cd.enumextbit = 0; break;
		case RejectType_datexReject_Subscription_cd_publishFormatNotSupported: ui_datexReject_Subscription_cd = 6; consinfo_datexReject_Subscription_cd.enumextbit = 0; break;
		case RejectType_datexReject_Subscription_cd_unknowSubscriptionMsgId: ui_datexReject_Subscription_cd = 7; consinfo_datexReject_Subscription_cd.enumextbit = 0; break;
		case RejectType_datexReject_Subscription_cd_invalidSubscriptionMsgId: ui_datexReject_Subscription_cd = 8; consinfo_datexReject_Subscription_cd.enumextbit = 0; break;
		case RejectType_datexReject_Subscription_cd_invalidSubscriptionContent: ui_datexReject_Subscription_cd = 9; consinfo_datexReject_Subscription_cd.enumextbit = 0; break;
		default: ui_datexReject_Subscription_cd = value->elements.datexReject_Subscription_cd; consinfo_datexReject_Subscription_cd.enumextbit = 1;break;
		}
		if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_datexReject_Subscription_cd, &consinfo_datexReject_Subscription_cd)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_RejectType_datexReject_Publication_cd:
		switch(value->elements.datexReject_Publication_cd)
		{
		case RejectType_datexReject_Publication_cd_other: ui_datexReject_Publication_cd = 0; consinfo_datexReject_Publication_cd.enumextbit = 0; break;
		case RejectType_datexReject_Publication_cd_invalidPublishFormat: ui_datexReject_Publication_cd = 1; consinfo_datexReject_Publication_cd.enumextbit = 0; break;
		default: ui_datexReject_Publication_cd = value->elements.datexReject_Publication_cd; consinfo_datexReject_Publication_cd.enumextbit = 1;break;
		}
		if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_datexReject_Publication_cd, &consinfo_datexReject_Publication_cd)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_RejectType_rejectPublicationData:
		if ((ret = ASN1_PER_UNAlign_Enc_RejectType_rejectPublicationData(workspace, value->elements.rejectPublicationData)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: break;
	}
	return ret;
}
extern int ASN1_CHECK_RejectType(RejectType *value);
extern int ASN1_PER_UNAlign_Data_Enc_RejectType(ASN1WorkSpace *workspace, RejectType *value);
int ASN1_PER_UNAlign_Enc_RejectType(ASN1WorkSpace *workspace, RejectType *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_RejectType(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_RejectType(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Dec_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value);
int ASN1_PER_UNAlign_Data_Dec_RejectType(ASN1WorkSpace *workspace, RejectType *value)
{
	int ret = 0;
	ASNINT32 ui_datexReject_Login_cd;
	ASNINT32 ui_datexReject_Subscription_cd;
	ASNINT32 ui_datexReject_Publication_cd;
	struct Asn1ConsInfo consinfo_datexReject_Login_cd = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexReject_Subscription_cd = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexReject_Publication_cd = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_rejectPublicationData = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	if ((ret = ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 4)) < 0) return ret;

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_RejectType_datexReject_Login_cd;
			break;
		case 1: index = DEF_RejectType_datexReject_Subscription_cd;
			break;
		case 2: index = DEF_RejectType_datexReject_Publication_cd;
			break;
		case 3: index = DEF_RejectType_rejectPublicationData;
			value->elements.rejectPublicationData = (RejectType_rejectPublicationData *)mpool_malloc(workspace->Pmemory, sizeof(RejectType_rejectPublicationData));
			memset(value->elements.rejectPublicationData, 0, sizeof(RejectType_rejectPublicationData));
			break;
		default: break;
		}
	}
	else
	{
		switch(ui)
		{
		default: break;
		}
	}
	if ((ret = ASN1_GetM(&value->M, index)) < 0) return ret;
	switch(index)
	{
	case DEF_RejectType_datexReject_Login_cd:
		if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_datexReject_Login_cd, &consinfo_datexReject_Login_cd)) < 0) return ret;
		if (consinfo_datexReject_Login_cd.enumextbit == 0)
		{
			switch(ui_datexReject_Login_cd)
			{
			case 0: value->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_other; break;
			case 1: value->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_unknownDomainName; break;
			case 2: value->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_accessDenied; break;
			case 3: value->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_invalidNamePassword; break;
			case 4: value->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_timeoutTooSmall; break;
			case 5: value->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_timeoutTooLarge; break;
			case 6: value->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_heartbeatTooSmall; break;
			case 7: value->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_heartbeatTooLarge; break;
			case 8: value->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_sessionExists; break;
			case 9: value->elements.datexReject_Login_cd = RejectType_datexReject_Login_cd_maxSessionsReached; break;
			default: break;
			}
		}
		else
		{
			switch(ui_datexReject_Login_cd)
			{
			default: value->elements.datexReject_Login_cd = ui_datexReject_Login_cd; break;
			}
		}
		if (ret != 0) return -1;
		break;
	case DEF_RejectType_datexReject_Subscription_cd:
		if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_datexReject_Subscription_cd, &consinfo_datexReject_Subscription_cd)) < 0) return ret;
		if (consinfo_datexReject_Subscription_cd.enumextbit == 0)
		{
			switch(ui_datexReject_Subscription_cd)
			{
			case 0: value->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_other; break;
			case 1: value->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_unknownSubscriptionNbr; break;
			case 2: value->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_invalidTimes; break;
			case 3: value->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_frequencyTooSmall; break;
			case 4: value->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_frequencyTooLarge; break;
			case 5: value->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_invalid_mode; break;
			case 6: value->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_publishFormatNotSupported; break;
			case 7: value->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_unknowSubscriptionMsgId; break;
			case 8: value->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_invalidSubscriptionMsgId; break;
			case 9: value->elements.datexReject_Subscription_cd = RejectType_datexReject_Subscription_cd_invalidSubscriptionContent; break;
			default: break;
			}
		}
		else
		{
			switch(ui_datexReject_Subscription_cd)
			{
			default: value->elements.datexReject_Subscription_cd = ui_datexReject_Subscription_cd; break;
			}
		}
		if (ret != 0) return -1;
		break;
	case DEF_RejectType_datexReject_Publication_cd:
		if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_datexReject_Publication_cd, &consinfo_datexReject_Publication_cd)) < 0) return ret;
		if (consinfo_datexReject_Publication_cd.enumextbit == 0)
		{
			switch(ui_datexReject_Publication_cd)
			{
			case 0: value->elements.datexReject_Publication_cd = RejectType_datexReject_Publication_cd_other; break;
			case 1: value->elements.datexReject_Publication_cd = RejectType_datexReject_Publication_cd_invalidPublishFormat; break;
			default: break;
			}
		}
		else
		{
			switch(ui_datexReject_Publication_cd)
			{
			default: value->elements.datexReject_Publication_cd = ui_datexReject_Publication_cd; break;
			}
		}
		if (ret != 0) return -1;
		break;
	case DEF_RejectType_rejectPublicationData:
		if ((ret = ASN1_PER_UNAlign_Dec_RejectType_rejectPublicationData(workspace, value->elements.rejectPublicationData)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
extern int ASN1_CHECK_RejectType(RejectType *value);
extern int ASN1_PER_UNAlign_Data_Dec_RejectType(ASN1WorkSpace *workspace, RejectType *value);
int ASN1_PER_UNAlign_Dec_RejectType(ASN1WorkSpace *workspace, RejectType *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_RejectType(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_RejectType(value)) < 0) return ret;
	return ret;
}

/********************************************************
*AlternateRequest                                       *
********************************************************/
int ASN1_Print_AlternateRequest(AlternateRequest *value, int tab_value)
{
	int ret = 0;
	if (Compare_Letter(tab_value, "AlternateRequest")) {
		ASN_Print_TAB(tab_value + 1); asn_printf("AlternateRequest = ");
	}
	ret = ASN1_Print_SubscriptionType(value, tab_value);
	return ret;
}
extern int ASN1_CHECK_SubscriptionType(SubscriptionType *value);
int ASN1_CHECK_AlternateRequest(AlternateRequest *value)
{
	return ASN1_CHECK_SubscriptionType(value);
}
extern int ASN1_BER_Enc_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_AlternateRequest(ASN1WorkSpace *workspace, AlternateRequest *value, ASN1TagType tagFlag)
{
	return ASN1_BER_Data_Enc_SubscriptionType(workspace, value, tagFlag);
}
int ASN1_BER_Enc_AlternateRequest(ASN1WorkSpace *workspace, AlternateRequest *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Enc_SubscriptionType(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Dec_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_AlternateRequest(ASN1WorkSpace *workspace, AlternateRequest *value, int length, ASN1TagType tagFlag)
{
	return ASN1_BER_Data_Dec_SubscriptionType(workspace, value, length, tagFlag);
}
int ASN1_BER_Dec_AlternateRequest(ASN1WorkSpace *workspace, AlternateRequest *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_BER_Dec_SubscriptionType(workspace, value, length, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Enc_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value);
int ASN1_PER_Align_Enc_AlternateRequest(ASN1WorkSpace *workspace, AlternateRequest *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_PER_Align_Enc_SubscriptionType(workspace, value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Dec_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value);
int ASN1_PER_Align_Dec_AlternateRequest(ASN1WorkSpace *workspace, AlternateRequest *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Dec_SubscriptionType(workspace, value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Enc_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value);
int ASN1_PER_UNAlign_Enc_AlternateRequest(ASN1WorkSpace *workspace, AlternateRequest *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Enc_SubscriptionType(workspace, value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Dec_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value);
int ASN1_PER_UNAlign_Dec_AlternateRequest(ASN1WorkSpace *workspace, AlternateRequest *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Dec_SubscriptionType(workspace, value)) < 0) return ret;
	return ret;
}

/********************************************************
*Reject                                                 *
********************************************************/
int ASN1_Print_Reject(Reject *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("Reject");
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("datexReject_Packet_nbr", &(value->datexReject_Packet_nbr))) < 0) return ret;
	// Type Reference RejectType
	if (Compare_Letter(tab_value, "datexReject-Type")) {
		ASN_Print_TAB(tab_value + 1);
		asn_printf("datexReject-Type = ");
	}
	if ((ret = ASN1_Print_RejectType((RejectType *)value->datexReject_Type, tab_value + 1)) < 0) return ret;
	if (value->DEF_Reject_datexReject_AlternateRequest == 1)
	{ /*OPTIONAL start */
		// Type Reference AlternateRequest
		if (Compare_Letter(tab_value, "datexReject-AlternateRequest")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("datexReject-AlternateRequest = ");
		}
		if ((ret = ASN1_Print_AlternateRequest((AlternateRequest *)value->datexReject_AlternateRequest, tab_value + 1)) < 0) return ret;
	} /* OPTIONAL end */
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_Reject_datexReject_Packet_nbr(ASN1WorkSpace *workspace, Reject *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->datexReject_Packet_nbr, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_Reject_datexReject_Type(ASN1WorkSpace *workspace, Reject *value, RejectType *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->datexReject_Type = (RejectType *)mpool_malloc(workspace->Pmemory, sizeof(RejectType));
	memset(value->datexReject_Type, 0, sizeof(RejectType));
	memmove(value->datexReject_Type, user_value, sizeof(RejectType));
	return ret;
}
int ASN1_SET_Reject_datexReject_AlternateRequest(ASN1WorkSpace *workspace, Reject *value, AlternateRequest *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->datexReject_AlternateRequest = (AlternateRequest *)mpool_malloc(workspace->Pmemory, sizeof(AlternateRequest));
	memset(value->datexReject_AlternateRequest, 0, sizeof(AlternateRequest));
	value->DEF_Reject_datexReject_AlternateRequest = 1;
	memmove(value->datexReject_AlternateRequest, user_value, sizeof(AlternateRequest));
	return ret;
}
int ASN1_GET_Reject_datexReject_Packet_nbr(ASN1WorkSpace *workspace, Reject *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->datexReject_Packet_nbr, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_Reject_datexReject_Type(ASN1WorkSpace *workspace, Reject *value, RejectType **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = value->datexReject_Type;
	return ret;
}
int ASN1_GET_Reject_datexReject_AlternateRequest(ASN1WorkSpace *workspace, Reject *value, AlternateRequest **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->DEF_Reject_datexReject_AlternateRequest == 1)
	{
		*user_value = value->datexReject_AlternateRequest;
	}
	else return -2;
	return ret;
}
extern int ASN1_CHECK_RejectType(RejectType *value);
extern int ASN1_CHECK_AlternateRequest(AlternateRequest *value);
int ASN1_CHECK_Reject(Reject *value)
{
	int ret = 0;

	unsigned char checkinfo_datexReject_Packet_nbr[] = { 
		0x02,0x00,0x85,0x00,0xFF,0xFF,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_datexReject_Type[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_datexReject_AlternateRequest[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_INTEGER(&(value->datexReject_Packet_nbr), checkinfo_datexReject_Packet_nbr)) < 0) return ret;
	if ((ret = ASN1_CHECK_RejectType(value->datexReject_Type)) < 0) return ret;
	if (value->DEF_Reject_datexReject_AlternateRequest == 1)
	{ /* OPTIONAL start */
		if ((ret = ASN1_CHECK_AlternateRequest(value->datexReject_AlternateRequest)) < 0) return ret;
	} /* OPTIONAL end */
	return ret;
}
extern int ASN1_BER_Data_Enc_RejectType(ASN1WorkSpace *workspace, RejectType *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_AlternateRequest(ASN1WorkSpace *workspace, AlternateRequest *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_Reject(ASN1WorkSpace *workspace, Reject *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->datexReject_Packet_nbr), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_RejectType(workspace, value->datexReject_Type, ASN1EXPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	if (value->DEF_Reject_datexReject_AlternateRequest == 1)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 2)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_AlternateRequest(workspace, value->datexReject_AlternateRequest, ASN1EXPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Reject(Reject *value);
extern int ASN1_BER_Data_Enc_Reject(ASN1WorkSpace *workspace, Reject *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_Reject(ASN1WorkSpace *workspace, Reject *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_Reject(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_Reject(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_RejectType(ASN1WorkSpace *workspace, RejectType *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_AlternateRequest(ASN1WorkSpace *workspace, AlternateRequest *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_Reject(ASN1WorkSpace *workspace, Reject *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	ASNUINT8 *_cpointer;
	value->datexReject_Type = (RejectType *)mpool_malloc(workspace->Pmemory, sizeof(RejectType));
	memset(value->datexReject_Type, 0, sizeof(RejectType));
	value->datexReject_AlternateRequest = (AlternateRequest *)mpool_malloc(workspace->Pmemory, sizeof(AlternateRequest));
	memset(value->datexReject_AlternateRequest, 0, sizeof(AlternateRequest));
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->datexReject_Packet_nbr, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_RejectType(workspace, value->datexReject_Type, len, ASN1EXPL)) < 0) return ret;
	if (IfFixedLength(len) == -1)
	{
		if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
	}
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	if (tag == (ITS_ASN_CONT | ITS_ASN_CONS | 2))
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 2)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_AlternateRequest(workspace, value->datexReject_AlternateRequest, len, ASN1EXPL)) < 0) return ret;
		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->DEF_Reject_datexReject_AlternateRequest = 1;
	}
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_Reject(Reject *value);
extern int ASN1_BER_Data_Dec_Reject(ASN1WorkSpace *workspace, Reject *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_Reject(ASN1WorkSpace *workspace, Reject *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_Reject(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_Reject(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Enc_RejectType(ASN1WorkSpace *workspace, RejectType *value);
extern int ASN1_PER_Align_Data_Enc_AlternateRequest(ASN1WorkSpace *workspace, AlternateRequest *value);
int ASN1_PER_Align_Data_Enc_Reject(ASN1WorkSpace *workspace, Reject *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexReject_Packet_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexReject_Type = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexReject_AlternateRequest = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_Reject_datexReject_AlternateRequest == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->datexReject_Packet_nbr), &consinfo_datexReject_Packet_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_RejectType(workspace, value->datexReject_Type)) < 0) return ret;
	if (value->DEF_Reject_datexReject_AlternateRequest == 1)
	{
		if ((ret = ASN1_PER_Align_Enc_AlternateRequest(workspace, value->datexReject_AlternateRequest)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Reject(Reject *value);
extern int ASN1_PER_Align_Data_Enc_Reject(ASN1WorkSpace *workspace, Reject *value);
int ASN1_PER_Align_Enc_Reject(ASN1WorkSpace *workspace, Reject *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Reject(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_Reject(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Dec_RejectType(ASN1WorkSpace *workspace, RejectType *value);
extern int ASN1_PER_Align_Data_Dec_AlternateRequest(ASN1WorkSpace *workspace, AlternateRequest *value);
int ASN1_PER_Align_Data_Dec_Reject(ASN1WorkSpace *workspace, Reject *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexReject_Packet_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexReject_Type = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexReject_AlternateRequest = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNUINT8 *_optvalue;
	if ((ret = ASN1_PER_Dec_Opt_Def_bit(workspace, 1, &_optvalue)) < 0) return ret;
	value->datexReject_Type = (RejectType *)mpool_malloc(workspace->Pmemory, sizeof(RejectType));
	memset(value->datexReject_Type, 0, sizeof(RejectType));
	value->datexReject_AlternateRequest = (AlternateRequest *)mpool_malloc(workspace->Pmemory, sizeof(AlternateRequest));
	memset(value->datexReject_AlternateRequest, 0, sizeof(AlternateRequest));
	if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->datexReject_Packet_nbr), &consinfo_datexReject_Packet_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_RejectType(workspace, value->datexReject_Type)) < 0) return ret;
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_Reject_datexReject_AlternateRequest = 1;
		if ((ret = ASN1_PER_Align_Dec_AlternateRequest(workspace, value->datexReject_AlternateRequest)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Reject(Reject *value);
extern int ASN1_PER_Align_Data_Dec_Reject(ASN1WorkSpace *workspace, Reject *value);
int ASN1_PER_Align_Dec_Reject(ASN1WorkSpace *workspace, Reject *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_Reject(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Reject(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Enc_RejectType(ASN1WorkSpace *workspace, RejectType *value);
extern int ASN1_PER_UNAlign_Data_Enc_AlternateRequest(ASN1WorkSpace *workspace, AlternateRequest *value);
int ASN1_PER_UNAlign_Data_Enc_Reject(ASN1WorkSpace *workspace, Reject *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexReject_Packet_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexReject_Type = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexReject_AlternateRequest = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_Enc_bit(workspace, (ASNBOOL)(value->DEF_Reject_datexReject_AlternateRequest == 1 ? 1 : 0) )) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->datexReject_Packet_nbr), &consinfo_datexReject_Packet_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_RejectType(workspace, value->datexReject_Type)) < 0) return ret;
	if (value->DEF_Reject_datexReject_AlternateRequest == 1)
	{
		if ((ret = ASN1_PER_UNAlign_Enc_AlternateRequest(workspace, value->datexReject_AlternateRequest)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Reject(Reject *value);
extern int ASN1_PER_UNAlign_Data_Enc_Reject(ASN1WorkSpace *workspace, Reject *value);
int ASN1_PER_UNAlign_Enc_Reject(ASN1WorkSpace *workspace, Reject *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_Reject(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_Reject(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Dec_RejectType(ASN1WorkSpace *workspace, RejectType *value);
extern int ASN1_PER_UNAlign_Data_Dec_AlternateRequest(ASN1WorkSpace *workspace, AlternateRequest *value);
int ASN1_PER_UNAlign_Data_Dec_Reject(ASN1WorkSpace *workspace, Reject *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datexReject_Packet_nbr = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexReject_Type = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datexReject_AlternateRequest = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNUINT8 *_optvalue;
	if ((ret = ASN1_PER_Dec_Opt_Def_bit(workspace, 1, &_optvalue)) < 0) return ret;
	value->datexReject_Type = (RejectType *)mpool_malloc(workspace->Pmemory, sizeof(RejectType));
	memset(value->datexReject_Type, 0, sizeof(RejectType));
	value->datexReject_AlternateRequest = (AlternateRequest *)mpool_malloc(workspace->Pmemory, sizeof(AlternateRequest));
	memset(value->datexReject_AlternateRequest, 0, sizeof(AlternateRequest));
	if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->datexReject_Packet_nbr), &consinfo_datexReject_Packet_nbr)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_RejectType(workspace, value->datexReject_Type)) < 0) return ret;
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_Reject_datexReject_AlternateRequest = 1;
		if ((ret = ASN1_PER_UNAlign_Dec_AlternateRequest(workspace, value->datexReject_AlternateRequest)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_Reject(Reject *value);
extern int ASN1_PER_UNAlign_Data_Dec_Reject(ASN1WorkSpace *workspace, Reject *value);
int ASN1_PER_UNAlign_Dec_Reject(ASN1WorkSpace *workspace, Reject *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_Reject(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_Reject(value)) < 0) return ret;
	return ret;
}

/********************************************************
*PDUs                                                   *
********************************************************/
int ASN1_Print_PDUs(PDUs *value, int tab_value)
{
	int ret = 0;
	// CHOICE : t->tempIdentifier is Upper Letter
	ASN1_Print_CHOICE("PDUs");
	if (value == NULL) return -1;
	switch (value->M) {
	case DEF_PDUs_datex_Initiate_null:
		// Type Reference Initiate
		if (Compare_Letter(tab_value, "datex-Initiate-null")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("datex-Initiate-null = ");
		}
		if ((ret = ASN1_Print_Initiate((Initiate *)value->elements.datex_Initiate_null, tab_value + 1)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_login:
		// Type Reference Login
		if (Compare_Letter(tab_value, "login")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("login = ");
		}
		if ((ret = ASN1_Print_Login((Login *)value->elements.login, tab_value + 1)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_fred:
		// Type Default
		// Type is Referenced
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		if ((ret = ASN1_Print_INTEGER("FrED", &value->elements.fred)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_terminate:
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		switch(value->elements.terminate)
		{
		case 0: if ((ret = ASN1_Print_ENUMERATED("Terminate", "other", 0)) < 0) return ret; break;
		case 1: if ((ret = ASN1_Print_ENUMERATED("Terminate", "serverRequested", 1)) < 0) return ret; break;
		case 2: if ((ret = ASN1_Print_ENUMERATED("Terminate", "clientRequested", 2)) < 0) return ret; break;
		case 3: if ((ret = ASN1_Print_ENUMERATED("Terminate", "serverShutdown", 3)) < 0) return ret; break;
		case 4: if ((ret = ASN1_Print_ENUMERATED("Terminate", "clientShutdown", 4)) < 0) return ret; break;
		case 5: if ((ret = ASN1_Print_ENUMERATED("Terminate", "serverCommProblems", 5)) < 0) return ret; break;
		case 6: if ((ret = ASN1_Print_ENUMERATED("Terminate", "clientCommProblems", 6)) < 0) return ret; break;
		default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
		};
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_logout:
		if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
		switch(value->elements.logout)
		{
		case 0: if ((ret = ASN1_Print_ENUMERATED("Logout", "other", 0)) < 0) return ret; break;
		case 1: if ((ret = ASN1_Print_ENUMERATED("Logout", "serverRequested", 1)) < 0) return ret; break;
		case 2: if ((ret = ASN1_Print_ENUMERATED("Logout", "clientRequested", 2)) < 0) return ret; break;
		case 3: if ((ret = ASN1_Print_ENUMERATED("Logout", "serverShutdown", 3)) < 0) return ret; break;
		case 4: if ((ret = ASN1_Print_ENUMERATED("Logout", "clientShutdown", 4)) < 0) return ret; break;
		case 5: if ((ret = ASN1_Print_ENUMERATED("Logout", "serverCommProblems", 5)) < 0) return ret; break;
		case 6: if ((ret = ASN1_Print_ENUMERATED("Logout", "clientCommProblems", 6)) < 0) return ret; break;
		default: ASN1_Enum_UNKNOWN(tab_value + 1); break;
		};
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_subscription:
		// Type Reference Subscription
		if (Compare_Letter(tab_value, "subscription")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("subscription = ");
		}
		if ((ret = ASN1_Print_Subscription((Subscription *)value->elements.subscription, tab_value + 1)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_publication:
		// Type Reference Publication
		if (Compare_Letter(tab_value, "publication")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("publication = ");
		}
		if ((ret = ASN1_Print_Publication((Publication *)value->elements.publication, tab_value + 1)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_transfer_done:
		// Type Reference TransferDone
		if (Compare_Letter(tab_value, "transfer-done")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("transfer-done = ");
		}
		if ((ret = ASN1_Print_TransferDone((TransferDone *)value->elements.transfer_done, tab_value + 1)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_accept:
		// Type Reference Accept
		if (Compare_Letter(tab_value, "accept")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("accept = ");
		}
		if ((ret = ASN1_Print_Accept((Accept *)value->elements.accept, tab_value + 1)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_reject:
		// Type Reference Reject
		if (Compare_Letter(tab_value, "reject")) {
			ASN_Print_TAB(tab_value + 1);
			asn_printf("reject = ");
		}
		if ((ret = ASN1_Print_Reject((Reject *)value->elements.reject, tab_value + 1)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: return -1;
}
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_PDUs_datex_Initiate_null(ASN1WorkSpace *workspace, PDUs *value, Initiate *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->elements.datex_Initiate_null = (Initiate *)mpool_malloc(workspace->Pmemory, sizeof(Initiate));
	memset(value->elements.datex_Initiate_null, 0, sizeof(Initiate));
	value->M = DEF_PDUs_datex_Initiate_null;
	memmove(value->elements.datex_Initiate_null, user_value, sizeof(Initiate));
	return ret;
}
int ASN1_SET_PDUs_login(ASN1WorkSpace *workspace, PDUs *value, Login *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->elements.login = (Login *)mpool_malloc(workspace->Pmemory, sizeof(Login));
	memset(value->elements.login, 0, sizeof(Login));
	value->M = DEF_PDUs_login;
	memmove(value->elements.login, user_value, sizeof(Login));
	return ret;
}
int ASN1_SET_PDUs_fred(ASN1WorkSpace *workspace, PDUs *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->M = DEF_PDUs_fred;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->elements.fred, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_PDUs_terminate(ASN1WorkSpace *workspace, PDUs *value, ENUMERATED user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->M = DEF_PDUs_terminate;
	if ((ret = ASN1_SET_ENUMERATED(workspace, (ASNINT32*)&value->elements.terminate, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_PDUs_logout(ASN1WorkSpace *workspace, PDUs *value, ENUMERATED user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	value->M = DEF_PDUs_logout;
	if ((ret = ASN1_SET_ENUMERATED(workspace, (ASNINT32*)&value->elements.logout, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_PDUs_subscription(ASN1WorkSpace *workspace, PDUs *value, Subscription *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->elements.subscription = (Subscription *)mpool_malloc(workspace->Pmemory, sizeof(Subscription));
	memset(value->elements.subscription, 0, sizeof(Subscription));
	value->M = DEF_PDUs_subscription;
	memmove(value->elements.subscription, user_value, sizeof(Subscription));
	return ret;
}
int ASN1_SET_PDUs_publication(ASN1WorkSpace *workspace, PDUs *value, Publication *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->elements.publication = (Publication *)mpool_malloc(workspace->Pmemory, sizeof(Publication));
	memset(value->elements.publication, 0, sizeof(Publication));
	value->M = DEF_PDUs_publication;
	memmove(value->elements.publication, user_value, sizeof(Publication));
	return ret;
}
int ASN1_SET_PDUs_transfer_done(ASN1WorkSpace *workspace, PDUs *value, TransferDone *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->elements.transfer_done = (TransferDone *)mpool_malloc(workspace->Pmemory, sizeof(TransferDone));
	memset(value->elements.transfer_done, 0, sizeof(TransferDone));
	value->M = DEF_PDUs_transfer_done;
	memmove(value->elements.transfer_done, user_value, sizeof(TransferDone));
	return ret;
}
int ASN1_SET_PDUs_accept(ASN1WorkSpace *workspace, PDUs *value, Accept *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->elements.accept = (Accept *)mpool_malloc(workspace->Pmemory, sizeof(Accept));
	memset(value->elements.accept, 0, sizeof(Accept));
	value->M = DEF_PDUs_accept;
	memmove(value->elements.accept, user_value, sizeof(Accept));
	return ret;
}
int ASN1_SET_PDUs_reject(ASN1WorkSpace *workspace, PDUs *value, Reject *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->elements.reject = (Reject *)mpool_malloc(workspace->Pmemory, sizeof(Reject));
	memset(value->elements.reject, 0, sizeof(Reject));
	value->M = DEF_PDUs_reject;
	memmove(value->elements.reject, user_value, sizeof(Reject));
	return ret;
}
int ASN1_GET_PDUs_datex_Initiate_null(ASN1WorkSpace *workspace, PDUs *value, Initiate **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->M == DEF_PDUs_datex_Initiate_null)
	{
		*user_value = value->elements.datex_Initiate_null;
	}
	else return -2;
	return ret;
}
int ASN1_GET_PDUs_login(ASN1WorkSpace *workspace, PDUs *value, Login **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->M == DEF_PDUs_login)
	{
		*user_value = value->elements.login;
	}
	else return -2;
	return ret;
}
int ASN1_GET_PDUs_fred(ASN1WorkSpace *workspace, PDUs *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->M == DEF_PDUs_fred)
	{
		if ((ret = ASN1_GET_INTEGER(workspace, &value->elements.fred, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_PDUs_terminate(ASN1WorkSpace *workspace, PDUs *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->M == DEF_PDUs_terminate)
	{
		if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->elements.terminate, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_PDUs_logout(ASN1WorkSpace *workspace, PDUs *value, ENUMERATED *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if (value->M == DEF_PDUs_logout)
	{
		if ((ret = ASN1_GET_ENUMERATED(workspace, (ASNINT32*)&value->elements.logout, user_value)) < 0) return ret;
	}
	else return -2;
	return ret;
}
int ASN1_GET_PDUs_subscription(ASN1WorkSpace *workspace, PDUs *value, Subscription **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->M == DEF_PDUs_subscription)
	{
		*user_value = value->elements.subscription;
	}
	else return -2;
	return ret;
}
int ASN1_GET_PDUs_publication(ASN1WorkSpace *workspace, PDUs *value, Publication **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->M == DEF_PDUs_publication)
	{
		*user_value = value->elements.publication;
	}
	else return -2;
	return ret;
}
int ASN1_GET_PDUs_transfer_done(ASN1WorkSpace *workspace, PDUs *value, TransferDone **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->M == DEF_PDUs_transfer_done)
	{
		*user_value = value->elements.transfer_done;
	}
	else return -2;
	return ret;
}
int ASN1_GET_PDUs_accept(ASN1WorkSpace *workspace, PDUs *value, Accept **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->M == DEF_PDUs_accept)
	{
		*user_value = value->elements.accept;
	}
	else return -2;
	return ret;
}
int ASN1_GET_PDUs_reject(ASN1WorkSpace *workspace, PDUs *value, Reject **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if (value->M == DEF_PDUs_reject)
	{
		*user_value = value->elements.reject;
	}
	else return -2;
	return ret;
}
extern int ASN1_CHECK_Initiate(Initiate *value);
extern int ASN1_CHECK_Login(Login *value);
extern int ASN1_CHECK_Subscription(Subscription *value);
extern int ASN1_CHECK_Publication(Publication *value);
extern int ASN1_CHECK_TransferDone(TransferDone *value);
extern int ASN1_CHECK_Accept(Accept *value);
extern int ASN1_CHECK_Reject(Reject *value);
int ASN1_CHECK_PDUs(PDUs *value)
{
	int ret = 0;

	unsigned char checkinfo_datex_Initiate_null[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_login[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_fred[] = { 
		0x02,0x00,0x85,0x00,0xFF,0xFF,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_terminate[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_logout[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_subscription[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_publication[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_transfer_done[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_accept[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_reject[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_PDUs_datex_Initiate_null:
		if ((ret = ASN1_CHECK_Initiate(value->elements.datex_Initiate_null)) < 0) return ret;
		break;
	case DEF_PDUs_login:
		if ((ret = ASN1_CHECK_Login(value->elements.login)) < 0) return ret;
		break;
	case DEF_PDUs_fred:
		if ((ret = ASN1_CHECK_INTEGER(&value->elements.fred, checkinfo_fred)) < 0) return ret;
		break;
	case DEF_PDUs_terminate:
		if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&value->elements.terminate, checkinfo_terminate)) < 0) return ret;
		break;
	case DEF_PDUs_logout:
		if ((ret = ASN1_CHECK_ENUMERATED((ASNINT32*)&value->elements.logout, checkinfo_logout)) < 0) return ret;
		break;
	case DEF_PDUs_subscription:
		if ((ret = ASN1_CHECK_Subscription(value->elements.subscription)) < 0) return ret;
		break;
	case DEF_PDUs_publication:
		if ((ret = ASN1_CHECK_Publication(value->elements.publication)) < 0) return ret;
		break;
	case DEF_PDUs_transfer_done:
		if ((ret = ASN1_CHECK_TransferDone(value->elements.transfer_done)) < 0) return ret;
		break;
	case DEF_PDUs_accept:
		if ((ret = ASN1_CHECK_Accept(value->elements.accept)) < 0) return ret;
		break;
	case DEF_PDUs_reject:
		if ((ret = ASN1_CHECK_Reject(value->elements.reject)) < 0) return ret;
		break;
	default: break;
	}
	return ret;
}
extern int ASN1_BER_Data_Enc_Initiate(ASN1WorkSpace *workspace, Initiate *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_Login(ASN1WorkSpace *workspace, Login *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_FrED(ASN1WorkSpace *workspace, FrED *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_Terminate(ASN1WorkSpace *workspace, Terminate *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_Logout(ASN1WorkSpace *workspace, Logout *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_Subscription(ASN1WorkSpace *workspace, Subscription *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_Publication(ASN1WorkSpace *workspace, Publication *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_TransferDone(ASN1WorkSpace *workspace, TransferDone *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_Accept(ASN1WorkSpace *workspace, Accept *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_Reject(ASN1WorkSpace *workspace, Reject *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_PDUs(ASN1WorkSpace *workspace, PDUs *value, ASN1TagType tagFlag)
{
	int ret = 0;
	switch(value->M)
	{
	case DEF_PDUs_datex_Initiate_null:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 0)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_Initiate(workspace, value->elements.datex_Initiate_null, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
		break;
	case DEF_PDUs_login:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 1)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_Login(workspace, value->elements.login, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
		break;
	case DEF_PDUs_fred:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_FrED(workspace, &(value->elements.fred), ASN1IMPL)) < 0) return ret;
		break;
	case DEF_PDUs_terminate:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_Terminate(workspace, &(value->elements.terminate), ASN1IMPL)) < 0) return ret;
		break;
	case DEF_PDUs_logout:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_Logout(workspace, &(value->elements.logout), ASN1IMPL)) < 0) return ret;
		break;
	case DEF_PDUs_subscription:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 5)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_Subscription(workspace, value->elements.subscription, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
		break;
	case DEF_PDUs_publication:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 6)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_Publication(workspace, value->elements.publication, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
		break;
	case DEF_PDUs_transfer_done:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 7)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_TransferDone(workspace, value->elements.transfer_done, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
		break;
	case DEF_PDUs_accept:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 8)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_Accept(workspace, value->elements.accept, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
		break;
	case DEF_PDUs_reject:
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 9)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Enc_Reject(workspace, value->elements.reject, ASN1IMPL)) < 0) return ret;
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
		break;
	}
	return ret;
}
extern int ASN1_CHECK_PDUs(PDUs *value);
extern int ASN1_BER_Data_Enc_PDUs(ASN1WorkSpace *workspace, PDUs *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_PDUs(ASN1WorkSpace *workspace, PDUs *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_PDUs(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_PDUs(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_Initiate(ASN1WorkSpace *workspace, Initiate *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_Login(ASN1WorkSpace *workspace, Login *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_FrED(ASN1WorkSpace *workspace, FrED *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_Terminate(ASN1WorkSpace *workspace, Terminate *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_Logout(ASN1WorkSpace *workspace, Logout *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_Subscription(ASN1WorkSpace *workspace, Subscription *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_Publication(ASN1WorkSpace *workspace, Publication *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_TransferDone(ASN1WorkSpace *workspace, TransferDone *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_Accept(ASN1WorkSpace *workspace, Accept *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_Reject(ASN1WorkSpace *workspace, Reject *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_PDUs(ASN1WorkSpace *workspace, PDUs *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT32 tag;
	value->M = 0;
	if ((ret = ASN1_BER_GET_Tag(workspace, &tag)) < 0) return ret;
	switch(tag)
	{
	case ITS_ASN_CONT | ITS_ASN_CONS | 0:
		value->elements.datex_Initiate_null = (Initiate *)mpool_malloc(workspace->Pmemory, sizeof(Initiate));
		memset(value->elements.datex_Initiate_null, 0, sizeof(Initiate));
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 0)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_Initiate(workspace, value->elements.datex_Initiate_null, len, ASN1IMPL)) < 0) return ret;
		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->M = DEF_PDUs_datex_Initiate_null;
		break;
	case ITS_ASN_CONT | ITS_ASN_CONS | 1:
		value->elements.login = (Login *)mpool_malloc(workspace->Pmemory, sizeof(Login));
		memset(value->elements.login, 0, sizeof(Login));
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 1)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_Login(workspace, value->elements.login, len, ASN1IMPL)) < 0) return ret;
		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->M = DEF_PDUs_login;
		break;
	case ITS_ASN_CONT | ITS_ASN_PRIM | 2:
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_FrED(workspace, &value->elements.fred, len, ASN1IMPL)) < 0) return ret;
		value->M = DEF_PDUs_fred;
		break;
	case ITS_ASN_CONT | ITS_ASN_PRIM | 3:
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 3)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_Terminate(workspace, &value->elements.terminate, len, ASN1IMPL)) < 0) return ret;
		value->M = DEF_PDUs_terminate;
		break;
	case ITS_ASN_CONT | ITS_ASN_PRIM | 4:
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 4)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_Logout(workspace, &value->elements.logout, len, ASN1IMPL)) < 0) return ret;
		value->M = DEF_PDUs_logout;
		break;
	case ITS_ASN_CONT | ITS_ASN_CONS | 5:
		value->elements.subscription = (Subscription *)mpool_malloc(workspace->Pmemory, sizeof(Subscription));
		memset(value->elements.subscription, 0, sizeof(Subscription));
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 5)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_Subscription(workspace, value->elements.subscription, len, ASN1IMPL)) < 0) return ret;
		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->M = DEF_PDUs_subscription;
		break;
	case ITS_ASN_CONT | ITS_ASN_CONS | 6:
		value->elements.publication = (Publication *)mpool_malloc(workspace->Pmemory, sizeof(Publication));
		memset(value->elements.publication, 0, sizeof(Publication));
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 6)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_Publication(workspace, value->elements.publication, len, ASN1IMPL)) < 0) return ret;
		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->M = DEF_PDUs_publication;
		break;
	case ITS_ASN_CONT | ITS_ASN_CONS | 7:
		value->elements.transfer_done = (TransferDone *)mpool_malloc(workspace->Pmemory, sizeof(TransferDone));
		memset(value->elements.transfer_done, 0, sizeof(TransferDone));
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 7)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_TransferDone(workspace, value->elements.transfer_done, len, ASN1IMPL)) < 0) return ret;
		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->M = DEF_PDUs_transfer_done;
		break;
	case ITS_ASN_CONT | ITS_ASN_CONS | 8:
		value->elements.accept = (Accept *)mpool_malloc(workspace->Pmemory, sizeof(Accept));
		memset(value->elements.accept, 0, sizeof(Accept));
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 8)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_Accept(workspace, value->elements.accept, len, ASN1IMPL)) < 0) return ret;
		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->M = DEF_PDUs_accept;
		break;
	case ITS_ASN_CONT | ITS_ASN_CONS | 9:
		value->elements.reject = (Reject *)mpool_malloc(workspace->Pmemory, sizeof(Reject));
		memset(value->elements.reject, 0, sizeof(Reject));
		if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 9)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
		if ((ret = ASN1_BER_Data_Dec_Reject(workspace, value->elements.reject, len, ASN1IMPL)) < 0) return ret;
		if (IfFixedLength(len) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
		value->M = DEF_PDUs_reject;
		break;
	}
	return ret;
}
extern int ASN1_CHECK_PDUs(PDUs *value);
extern int ASN1_BER_Data_Dec_PDUs(ASN1WorkSpace *workspace, PDUs *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_PDUs(ASN1WorkSpace *workspace, PDUs *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_PDUs(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_PDUs(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Enc_Initiate(ASN1WorkSpace *workspace, Initiate *value);
extern int ASN1_PER_Align_Data_Enc_Login(ASN1WorkSpace *workspace, Login *value);
extern int ASN1_PER_Align_Data_Enc_Subscription(ASN1WorkSpace *workspace, Subscription *value);
extern int ASN1_PER_Align_Data_Enc_Publication(ASN1WorkSpace *workspace, Publication *value);
extern int ASN1_PER_Align_Data_Enc_TransferDone(ASN1WorkSpace *workspace, TransferDone *value);
extern int ASN1_PER_Align_Data_Enc_Accept(ASN1WorkSpace *workspace, Accept *value);
extern int ASN1_PER_Align_Data_Enc_Reject(ASN1WorkSpace *workspace, Reject *value);
int ASN1_PER_Align_Data_Enc_PDUs(ASN1WorkSpace *workspace, PDUs *value)
{
	int ret = 0;
	ASNINT32 ui_terminate;
	ASNINT32 ui_logout;
	struct Asn1ConsInfo consinfo_datex_Initiate_null = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_login = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_fred = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_terminate = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_logout = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_subscription = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_publication = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_transfer_done = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_accept = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_reject = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT64 ui;
	ASNBOOL extbit = 1;
	switch(value->M)
	{
	case DEF_PDUs_datex_Initiate_null: ui = 0; extbit = 0; break;
	case DEF_PDUs_login: ui = 1; extbit = 0; break;
	case DEF_PDUs_fred: ui = 2; extbit = 0; break;
	case DEF_PDUs_terminate: ui = 3; extbit = 0; break;
	case DEF_PDUs_logout: ui = 4; extbit = 0; break;
	case DEF_PDUs_subscription: ui = 5; extbit = 0; break;
	case DEF_PDUs_publication: ui = 6; extbit = 0; break;
	case DEF_PDUs_transfer_done: ui = 7; extbit = 0; break;
	case DEF_PDUs_accept: ui = 8; extbit = 0; break;
	case DEF_PDUs_reject: ui = 9; extbit = 0; break;
	default: break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_Choice_ENUMERATED(workspace, ui, extbit, 0, 10)) < 0) return ret;
	switch(value->M)
	{
	case DEF_PDUs_datex_Initiate_null:
		if ((ret = ASN1_PER_Align_Enc_Initiate(workspace, value->elements.datex_Initiate_null)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_login:
		if ((ret = ASN1_PER_Align_Enc_Login(workspace, value->elements.login)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_fred:
		if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->elements.fred), &consinfo_fred)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_terminate:
		switch(value->elements.terminate)
		{
		case Terminate_other: ui_terminate = 0; consinfo_terminate.enumextbit = 0; break;
		case Terminate_serverRequested: ui_terminate = 1; consinfo_terminate.enumextbit = 0; break;
		case Terminate_clientRequested: ui_terminate = 2; consinfo_terminate.enumextbit = 0; break;
		case Terminate_serverShutdown: ui_terminate = 3; consinfo_terminate.enumextbit = 0; break;
		case Terminate_clientShutdown: ui_terminate = 4; consinfo_terminate.enumextbit = 0; break;
		case Terminate_serverCommProblems: ui_terminate = 5; consinfo_terminate.enumextbit = 0; break;
		case Terminate_clientCommProblems: ui_terminate = 6; consinfo_terminate.enumextbit = 0; break;
		default: ui_terminate = value->elements.terminate; consinfo_terminate.enumextbit = 1;break;
		}
		if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_terminate, &consinfo_terminate)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_logout:
		switch(value->elements.logout)
		{
		case Logout_other: ui_logout = 0; consinfo_logout.enumextbit = 0; break;
		case Logout_serverRequested: ui_logout = 1; consinfo_logout.enumextbit = 0; break;
		case Logout_clientRequested: ui_logout = 2; consinfo_logout.enumextbit = 0; break;
		case Logout_serverShutdown: ui_logout = 3; consinfo_logout.enumextbit = 0; break;
		case Logout_clientShutdown: ui_logout = 4; consinfo_logout.enumextbit = 0; break;
		case Logout_serverCommProblems: ui_logout = 5; consinfo_logout.enumextbit = 0; break;
		case Logout_clientCommProblems: ui_logout = 6; consinfo_logout.enumextbit = 0; break;
		default: ui_logout = value->elements.logout; consinfo_logout.enumextbit = 1;break;
		}
		if ((ret = ASN1_PER_Align_Enc_ENUMERATED(workspace, ui_logout, &consinfo_logout)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_subscription:
		if ((ret = ASN1_PER_Align_Enc_Subscription(workspace, value->elements.subscription)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_publication:
		if ((ret = ASN1_PER_Align_Enc_Publication(workspace, value->elements.publication)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_transfer_done:
		if ((ret = ASN1_PER_Align_Enc_TransferDone(workspace, value->elements.transfer_done)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_accept:
		if ((ret = ASN1_PER_Align_Enc_Accept(workspace, value->elements.accept)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_reject:
		if ((ret = ASN1_PER_Align_Enc_Reject(workspace, value->elements.reject)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: break;
	}
	return ret;
}
extern int ASN1_CHECK_PDUs(PDUs *value);
extern int ASN1_PER_Align_Data_Enc_PDUs(ASN1WorkSpace *workspace, PDUs *value);
int ASN1_PER_Align_Enc_PDUs(ASN1WorkSpace *workspace, PDUs *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_PDUs(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_PDUs(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Dec_Initiate(ASN1WorkSpace *workspace, Initiate *value);
extern int ASN1_PER_Align_Data_Dec_Login(ASN1WorkSpace *workspace, Login *value);
extern int ASN1_PER_Align_Data_Dec_Subscription(ASN1WorkSpace *workspace, Subscription *value);
extern int ASN1_PER_Align_Data_Dec_Publication(ASN1WorkSpace *workspace, Publication *value);
extern int ASN1_PER_Align_Data_Dec_TransferDone(ASN1WorkSpace *workspace, TransferDone *value);
extern int ASN1_PER_Align_Data_Dec_Accept(ASN1WorkSpace *workspace, Accept *value);
extern int ASN1_PER_Align_Data_Dec_Reject(ASN1WorkSpace *workspace, Reject *value);
int ASN1_PER_Align_Data_Dec_PDUs(ASN1WorkSpace *workspace, PDUs *value)
{
	int ret = 0;
	ASNINT32 ui_terminate;
	ASNINT32 ui_logout;
	struct Asn1ConsInfo consinfo_datex_Initiate_null = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_login = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_fred = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_terminate = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_logout = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_subscription = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_publication = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_transfer_done = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_accept = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_reject = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	if ((ret = ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 10)) < 0) return ret;

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_PDUs_datex_Initiate_null;
			value->elements.datex_Initiate_null = (Initiate *)mpool_malloc(workspace->Pmemory, sizeof(Initiate));
			memset(value->elements.datex_Initiate_null, 0, sizeof(Initiate));
			break;
		case 1: index = DEF_PDUs_login;
			value->elements.login = (Login *)mpool_malloc(workspace->Pmemory, sizeof(Login));
			memset(value->elements.login, 0, sizeof(Login));
			break;
		case 2: index = DEF_PDUs_fred;
			break;
		case 3: index = DEF_PDUs_terminate;
			break;
		case 4: index = DEF_PDUs_logout;
			break;
		case 5: index = DEF_PDUs_subscription;
			value->elements.subscription = (Subscription *)mpool_malloc(workspace->Pmemory, sizeof(Subscription));
			memset(value->elements.subscription, 0, sizeof(Subscription));
			break;
		case 6: index = DEF_PDUs_publication;
			value->elements.publication = (Publication *)mpool_malloc(workspace->Pmemory, sizeof(Publication));
			memset(value->elements.publication, 0, sizeof(Publication));
			break;
		case 7: index = DEF_PDUs_transfer_done;
			value->elements.transfer_done = (TransferDone *)mpool_malloc(workspace->Pmemory, sizeof(TransferDone));
			memset(value->elements.transfer_done, 0, sizeof(TransferDone));
			break;
		case 8: index = DEF_PDUs_accept;
			value->elements.accept = (Accept *)mpool_malloc(workspace->Pmemory, sizeof(Accept));
			memset(value->elements.accept, 0, sizeof(Accept));
			break;
		case 9: index = DEF_PDUs_reject;
			value->elements.reject = (Reject *)mpool_malloc(workspace->Pmemory, sizeof(Reject));
			memset(value->elements.reject, 0, sizeof(Reject));
			break;
		default: break;
		}
	}
	else
	{
		switch(ui)
		{
		default: break;
		}
	}
	if ((ret = ASN1_GetM(&value->M, index)) < 0) return ret;
	switch(index)
	{
	case DEF_PDUs_datex_Initiate_null:
		if ((ret = ASN1_PER_Align_Dec_Initiate(workspace, value->elements.datex_Initiate_null)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_login:
		if ((ret = ASN1_PER_Align_Dec_Login(workspace, value->elements.login)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_fred:
		if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->elements.fred), &consinfo_fred)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_terminate:
		if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_terminate, &consinfo_terminate)) < 0) return ret;
		if (consinfo_terminate.enumextbit == 0)
		{
			switch(ui_terminate)
			{
			case 0: value->elements.terminate = Terminate_other; break;
			case 1: value->elements.terminate = Terminate_serverRequested; break;
			case 2: value->elements.terminate = Terminate_clientRequested; break;
			case 3: value->elements.terminate = Terminate_serverShutdown; break;
			case 4: value->elements.terminate = Terminate_clientShutdown; break;
			case 5: value->elements.terminate = Terminate_serverCommProblems; break;
			case 6: value->elements.terminate = Terminate_clientCommProblems; break;
			default: break;
			}
		}
		else
		{
			switch(ui_terminate)
			{
			default: value->elements.terminate = ui_terminate; break;
			}
		}
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_logout:
		if ((ret = ASN1_PER_Align_Dec_ENUMERATED(workspace, &ui_logout, &consinfo_logout)) < 0) return ret;
		if (consinfo_logout.enumextbit == 0)
		{
			switch(ui_logout)
			{
			case 0: value->elements.logout = Logout_other; break;
			case 1: value->elements.logout = Logout_serverRequested; break;
			case 2: value->elements.logout = Logout_clientRequested; break;
			case 3: value->elements.logout = Logout_serverShutdown; break;
			case 4: value->elements.logout = Logout_clientShutdown; break;
			case 5: value->elements.logout = Logout_serverCommProblems; break;
			case 6: value->elements.logout = Logout_clientCommProblems; break;
			default: break;
			}
		}
		else
		{
			switch(ui_logout)
			{
			default: value->elements.logout = ui_logout; break;
			}
		}
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_subscription:
		if ((ret = ASN1_PER_Align_Dec_Subscription(workspace, value->elements.subscription)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_publication:
		if ((ret = ASN1_PER_Align_Dec_Publication(workspace, value->elements.publication)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_transfer_done:
		if ((ret = ASN1_PER_Align_Dec_TransferDone(workspace, value->elements.transfer_done)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_accept:
		if ((ret = ASN1_PER_Align_Dec_Accept(workspace, value->elements.accept)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_reject:
		if ((ret = ASN1_PER_Align_Dec_Reject(workspace, value->elements.reject)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, ALIGN); break;
	}
	return ret;
}
extern int ASN1_CHECK_PDUs(PDUs *value);
extern int ASN1_PER_Align_Data_Dec_PDUs(ASN1WorkSpace *workspace, PDUs *value);
int ASN1_PER_Align_Dec_PDUs(ASN1WorkSpace *workspace, PDUs *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_PDUs(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_PDUs(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Enc_Initiate(ASN1WorkSpace *workspace, Initiate *value);
extern int ASN1_PER_UNAlign_Data_Enc_Login(ASN1WorkSpace *workspace, Login *value);
extern int ASN1_PER_UNAlign_Data_Enc_Subscription(ASN1WorkSpace *workspace, Subscription *value);
extern int ASN1_PER_UNAlign_Data_Enc_Publication(ASN1WorkSpace *workspace, Publication *value);
extern int ASN1_PER_UNAlign_Data_Enc_TransferDone(ASN1WorkSpace *workspace, TransferDone *value);
extern int ASN1_PER_UNAlign_Data_Enc_Accept(ASN1WorkSpace *workspace, Accept *value);
extern int ASN1_PER_UNAlign_Data_Enc_Reject(ASN1WorkSpace *workspace, Reject *value);
int ASN1_PER_UNAlign_Data_Enc_PDUs(ASN1WorkSpace *workspace, PDUs *value)
{
	int ret = 0;
	ASNINT32 ui_terminate;
	ASNINT32 ui_logout;
	struct Asn1ConsInfo consinfo_datex_Initiate_null = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_login = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_fred = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_terminate = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_logout = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_subscription = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_publication = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_transfer_done = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_accept = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_reject = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT64 ui;
	ASNBOOL extbit = 1;
	switch(value->M)
	{
	case DEF_PDUs_datex_Initiate_null: ui = 0; extbit = 0; break;
	case DEF_PDUs_login: ui = 1; extbit = 0; break;
	case DEF_PDUs_fred: ui = 2; extbit = 0; break;
	case DEF_PDUs_terminate: ui = 3; extbit = 0; break;
	case DEF_PDUs_logout: ui = 4; extbit = 0; break;
	case DEF_PDUs_subscription: ui = 5; extbit = 0; break;
	case DEF_PDUs_publication: ui = 6; extbit = 0; break;
	case DEF_PDUs_transfer_done: ui = 7; extbit = 0; break;
	case DEF_PDUs_accept: ui = 8; extbit = 0; break;
	case DEF_PDUs_reject: ui = 9; extbit = 0; break;
	default: break;
	}
	if ((ret = ASN1_PER_UNAlign_Enc_Choice_ENUMERATED(workspace, ui, extbit, 0, 10)) < 0) return ret;
	switch(value->M)
	{
	case DEF_PDUs_datex_Initiate_null:
		if ((ret = ASN1_PER_UNAlign_Enc_Initiate(workspace, value->elements.datex_Initiate_null)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_login:
		if ((ret = ASN1_PER_UNAlign_Enc_Login(workspace, value->elements.login)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_fred:
		if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->elements.fred), &consinfo_fred)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_terminate:
		switch(value->elements.terminate)
		{
		case Terminate_other: ui_terminate = 0; consinfo_terminate.enumextbit = 0; break;
		case Terminate_serverRequested: ui_terminate = 1; consinfo_terminate.enumextbit = 0; break;
		case Terminate_clientRequested: ui_terminate = 2; consinfo_terminate.enumextbit = 0; break;
		case Terminate_serverShutdown: ui_terminate = 3; consinfo_terminate.enumextbit = 0; break;
		case Terminate_clientShutdown: ui_terminate = 4; consinfo_terminate.enumextbit = 0; break;
		case Terminate_serverCommProblems: ui_terminate = 5; consinfo_terminate.enumextbit = 0; break;
		case Terminate_clientCommProblems: ui_terminate = 6; consinfo_terminate.enumextbit = 0; break;
		default: ui_terminate = value->elements.terminate; consinfo_terminate.enumextbit = 1;break;
		}
		if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_terminate, &consinfo_terminate)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_logout:
		switch(value->elements.logout)
		{
		case Logout_other: ui_logout = 0; consinfo_logout.enumextbit = 0; break;
		case Logout_serverRequested: ui_logout = 1; consinfo_logout.enumextbit = 0; break;
		case Logout_clientRequested: ui_logout = 2; consinfo_logout.enumextbit = 0; break;
		case Logout_serverShutdown: ui_logout = 3; consinfo_logout.enumextbit = 0; break;
		case Logout_clientShutdown: ui_logout = 4; consinfo_logout.enumextbit = 0; break;
		case Logout_serverCommProblems: ui_logout = 5; consinfo_logout.enumextbit = 0; break;
		case Logout_clientCommProblems: ui_logout = 6; consinfo_logout.enumextbit = 0; break;
		default: ui_logout = value->elements.logout; consinfo_logout.enumextbit = 1;break;
		}
		if ((ret = ASN1_PER_UNAlign_Enc_ENUMERATED(workspace, ui_logout, &consinfo_logout)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_subscription:
		if ((ret = ASN1_PER_UNAlign_Enc_Subscription(workspace, value->elements.subscription)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_publication:
		if ((ret = ASN1_PER_UNAlign_Enc_Publication(workspace, value->elements.publication)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_transfer_done:
		if ((ret = ASN1_PER_UNAlign_Enc_TransferDone(workspace, value->elements.transfer_done)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_accept:
		if ((ret = ASN1_PER_UNAlign_Enc_Accept(workspace, value->elements.accept)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_reject:
		if ((ret = ASN1_PER_UNAlign_Enc_Reject(workspace, value->elements.reject)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: break;
	}
	return ret;
}
extern int ASN1_CHECK_PDUs(PDUs *value);
extern int ASN1_PER_UNAlign_Data_Enc_PDUs(ASN1WorkSpace *workspace, PDUs *value);
int ASN1_PER_UNAlign_Enc_PDUs(ASN1WorkSpace *workspace, PDUs *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_PDUs(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_PDUs(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Dec_Initiate(ASN1WorkSpace *workspace, Initiate *value);
extern int ASN1_PER_UNAlign_Data_Dec_Login(ASN1WorkSpace *workspace, Login *value);
extern int ASN1_PER_UNAlign_Data_Dec_Subscription(ASN1WorkSpace *workspace, Subscription *value);
extern int ASN1_PER_UNAlign_Data_Dec_Publication(ASN1WorkSpace *workspace, Publication *value);
extern int ASN1_PER_UNAlign_Data_Dec_TransferDone(ASN1WorkSpace *workspace, TransferDone *value);
extern int ASN1_PER_UNAlign_Data_Dec_Accept(ASN1WorkSpace *workspace, Accept *value);
extern int ASN1_PER_UNAlign_Data_Dec_Reject(ASN1WorkSpace *workspace, Reject *value);
int ASN1_PER_UNAlign_Data_Dec_PDUs(ASN1WorkSpace *workspace, PDUs *value)
{
	int ret = 0;
	ASNINT32 ui_terminate;
	ASNINT32 ui_logout;
	struct Asn1ConsInfo consinfo_datex_Initiate_null = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_login = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_fred = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_terminate = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_logout = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_subscription = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_publication = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_transfer_done = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_accept = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_reject = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	if ((ret = ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 10)) < 0) return ret;

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_PDUs_datex_Initiate_null;
			value->elements.datex_Initiate_null = (Initiate *)mpool_malloc(workspace->Pmemory, sizeof(Initiate));
			memset(value->elements.datex_Initiate_null, 0, sizeof(Initiate));
			break;
		case 1: index = DEF_PDUs_login;
			value->elements.login = (Login *)mpool_malloc(workspace->Pmemory, sizeof(Login));
			memset(value->elements.login, 0, sizeof(Login));
			break;
		case 2: index = DEF_PDUs_fred;
			break;
		case 3: index = DEF_PDUs_terminate;
			break;
		case 4: index = DEF_PDUs_logout;
			break;
		case 5: index = DEF_PDUs_subscription;
			value->elements.subscription = (Subscription *)mpool_malloc(workspace->Pmemory, sizeof(Subscription));
			memset(value->elements.subscription, 0, sizeof(Subscription));
			break;
		case 6: index = DEF_PDUs_publication;
			value->elements.publication = (Publication *)mpool_malloc(workspace->Pmemory, sizeof(Publication));
			memset(value->elements.publication, 0, sizeof(Publication));
			break;
		case 7: index = DEF_PDUs_transfer_done;
			value->elements.transfer_done = (TransferDone *)mpool_malloc(workspace->Pmemory, sizeof(TransferDone));
			memset(value->elements.transfer_done, 0, sizeof(TransferDone));
			break;
		case 8: index = DEF_PDUs_accept;
			value->elements.accept = (Accept *)mpool_malloc(workspace->Pmemory, sizeof(Accept));
			memset(value->elements.accept, 0, sizeof(Accept));
			break;
		case 9: index = DEF_PDUs_reject;
			value->elements.reject = (Reject *)mpool_malloc(workspace->Pmemory, sizeof(Reject));
			memset(value->elements.reject, 0, sizeof(Reject));
			break;
		default: break;
		}
	}
	else
	{
		switch(ui)
		{
		default: break;
		}
	}
	if ((ret = ASN1_GetM(&value->M, index)) < 0) return ret;
	switch(index)
	{
	case DEF_PDUs_datex_Initiate_null:
		if ((ret = ASN1_PER_UNAlign_Dec_Initiate(workspace, value->elements.datex_Initiate_null)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_login:
		if ((ret = ASN1_PER_UNAlign_Dec_Login(workspace, value->elements.login)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_fred:
		if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->elements.fred), &consinfo_fred)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_terminate:
		if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_terminate, &consinfo_terminate)) < 0) return ret;
		if (consinfo_terminate.enumextbit == 0)
		{
			switch(ui_terminate)
			{
			case 0: value->elements.terminate = Terminate_other; break;
			case 1: value->elements.terminate = Terminate_serverRequested; break;
			case 2: value->elements.terminate = Terminate_clientRequested; break;
			case 3: value->elements.terminate = Terminate_serverShutdown; break;
			case 4: value->elements.terminate = Terminate_clientShutdown; break;
			case 5: value->elements.terminate = Terminate_serverCommProblems; break;
			case 6: value->elements.terminate = Terminate_clientCommProblems; break;
			default: break;
			}
		}
		else
		{
			switch(ui_terminate)
			{
			default: value->elements.terminate = ui_terminate; break;
			}
		}
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_logout:
		if ((ret = ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_logout, &consinfo_logout)) < 0) return ret;
		if (consinfo_logout.enumextbit == 0)
		{
			switch(ui_logout)
			{
			case 0: value->elements.logout = Logout_other; break;
			case 1: value->elements.logout = Logout_serverRequested; break;
			case 2: value->elements.logout = Logout_clientRequested; break;
			case 3: value->elements.logout = Logout_serverShutdown; break;
			case 4: value->elements.logout = Logout_clientShutdown; break;
			case 5: value->elements.logout = Logout_serverCommProblems; break;
			case 6: value->elements.logout = Logout_clientCommProblems; break;
			default: break;
			}
		}
		else
		{
			switch(ui_logout)
			{
			default: value->elements.logout = ui_logout; break;
			}
		}
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_subscription:
		if ((ret = ASN1_PER_UNAlign_Dec_Subscription(workspace, value->elements.subscription)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_publication:
		if ((ret = ASN1_PER_UNAlign_Dec_Publication(workspace, value->elements.publication)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_transfer_done:
		if ((ret = ASN1_PER_UNAlign_Dec_TransferDone(workspace, value->elements.transfer_done)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_accept:
		if ((ret = ASN1_PER_UNAlign_Dec_Accept(workspace, value->elements.accept)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	case DEF_PDUs_reject:
		if ((ret = ASN1_PER_UNAlign_Dec_Reject(workspace, value->elements.reject)) < 0) return ret;
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
extern int ASN1_CHECK_PDUs(PDUs *value);
extern int ASN1_PER_UNAlign_Data_Dec_PDUs(ASN1WorkSpace *workspace, PDUs *value);
int ASN1_PER_UNAlign_Dec_PDUs(ASN1WorkSpace *workspace, PDUs *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_PDUs(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_PDUs(value)) < 0) return ret;
	return ret;
}

/********************************************************
*C2CAuthenticatedMessage                                *
********************************************************/
int ASN1_Print_C2CAuthenticatedMessage(C2CAuthenticatedMessage *value, int tab_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	// SEQUENCE : t->tempIdentifier is Upper Letter
	ASN1_Print_SEQ("C2CAuthenticatedMessage");
	// Type OCTET STRING
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_OCTETSTRING("datex_AuthenticationInfo_text", &(value->datex_AuthenticationInfo_text), tab_value + 1)) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("datex_DataPacket_number", &(value->datex_DataPacket_number))) < 0) return ret;
	// Type Default
	if ((ret = ASN_Print_TAB(tab_value + 1)) < 0) return ret;
	if ((ret = ASN1_Print_INTEGER("datex_DataPacketPriority_number", &(value->datex_DataPacketPriority_number))) < 0) return ret;
	// Type Reference HeaderOptions
	if (Compare_Letter(tab_value, "options")) {
		ASN_Print_TAB(tab_value + 1);
		asn_printf("options = ");
	}
	if ((ret = ASN1_Print_HeaderOptions((HeaderOptions *)value->options, tab_value + 1)) < 0) return ret;
	// Type Reference PDUs
	if (Compare_Letter(tab_value, "pdu")) {
		ASN_Print_TAB(tab_value + 1);
		asn_printf("pdu = ");
	}
	if ((ret = ASN1_Print_PDUs((PDUs *)value->pdu, tab_value + 1)) < 0) return ret;
	ASN_Print_TAB(tab_value); asn_printf("}\n");
	return ret;
}
int ASN1_SET_C2CAuthenticatedMessage_datex_AuthenticationInfo_text(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, ASNUINT8 *user_value, ASNUINT32 user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_SET_OCTETSTRING(workspace, &value->datex_AuthenticationInfo_text, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_SET_C2CAuthenticatedMessage_datex_DataPacket_number(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->datex_DataPacket_number, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_C2CAuthenticatedMessage_datex_DataPacketPriority_number(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, INTEGER user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_SET_INTEGER(workspace, &value->datex_DataPacketPriority_number, user_value)) < 0) return ret;
	return ret;
}
int ASN1_SET_C2CAuthenticatedMessage_options(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, HeaderOptions *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->options = (HeaderOptions *)mpool_malloc(workspace->Pmemory, sizeof(HeaderOptions));
	memset(value->options, 0, sizeof(HeaderOptions));
	memmove(value->options, user_value, sizeof(HeaderOptions));
	return ret;
}
int ASN1_SET_C2CAuthenticatedMessage_pdu(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, PDUs *user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	value->pdu = (PDUs *)mpool_malloc(workspace->Pmemory, sizeof(PDUs));
	memset(value->pdu, 0, sizeof(PDUs));
	memmove(value->pdu, user_value, sizeof(PDUs));
	return ret;
}
int ASN1_GET_C2CAuthenticatedMessage_datex_AuthenticationInfo_text(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	if ((ret = ASN1_GET_OCTETSTRING(workspace, &value->datex_AuthenticationInfo_text, user_value, user_value_length)) < 0) return ret;
	return ret;
}
int ASN1_GET_C2CAuthenticatedMessage_datex_DataPacket_number(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->datex_DataPacket_number, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_C2CAuthenticatedMessage_datex_DataPacketPriority_number(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, INTEGER *user_value)
{
	int ret = 0;
	if (value == NULL) return -1;
	if ((ret = ASN1_GET_INTEGER(workspace, &value->datex_DataPacketPriority_number, user_value)) < 0) return ret;
	return ret;
}
int ASN1_GET_C2CAuthenticatedMessage_options(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, HeaderOptions **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = value->options;
	return ret;
}
int ASN1_GET_C2CAuthenticatedMessage_pdu(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, PDUs **user_value)
{
	int ret = 0;
	if (value == NULL || user_value == NULL) return -1;
	*user_value = value->pdu;
	return ret;
}
extern int ASN1_CHECK_HeaderOptions(HeaderOptions *value);
extern int ASN1_CHECK_PDUs(PDUs *value);
int ASN1_CHECK_C2CAuthenticatedMessage(C2CAuthenticatedMessage *value)
{
	int ret = 0;

	unsigned char checkinfo_datex_AuthenticationInfo_text[] = { 
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_datex_DataPacket_number[] = { 
		0x02,0x00,0x85,0x00,0xFF,0xFF,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_datex_DataPacketPriority_number[] = { 
		0x02,0x00,0x0A,0x00
	};
	unsigned char checkinfo_options[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_pdu[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if ((ret = ASN1_CHECK_OCTETSTRING(&(value->datex_AuthenticationInfo_text), checkinfo_datex_AuthenticationInfo_text)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->datex_DataPacket_number), checkinfo_datex_DataPacket_number)) < 0) return ret;
	if ((ret = ASN1_CHECK_INTEGER(&(value->datex_DataPacketPriority_number), checkinfo_datex_DataPacketPriority_number)) < 0) return ret;
	if ((ret = ASN1_CHECK_HeaderOptions(value->options)) < 0) return ret;
	if ((ret = ASN1_CHECK_PDUs(value->pdu)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Enc_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Enc_PDUs(ASN1WorkSpace *workspace, PDUs *value, ASN1TagType tagFlag);
int ASN1_BER_Data_Enc_C2CAuthenticatedMessage(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_UNIV | ITS_ASN_CONS | 16)) < 0) return ret;
	}
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_OCTETSTRING(workspace, &(value->datex_AuthenticationInfo_text), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->datex_DataPacket_number), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_INTEGER(workspace, &(value->datex_DataPacketPriority_number), ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 3)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_HeaderOptions(workspace, value->options, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_Tag_Indef(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 4)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_PDUs(workspace, value->pdu, ASN1EXPL)) < 0) return ret;
	if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_Enc_StrmEOC(workspace)) < 0) return ret;
	}
	return ret;
}
extern int ASN1_CHECK_C2CAuthenticatedMessage(C2CAuthenticatedMessage *value);
extern int ASN1_BER_Data_Enc_C2CAuthenticatedMessage(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, ASN1TagType tagFlag);
int ASN1_BER_Enc_C2CAuthenticatedMessage(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = ASN1_CHECK_C2CAuthenticatedMessage(value)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Enc_C2CAuthenticatedMessage(workspace, value, tagFlag)) < 0) return ret;
	return ret;
}
extern int ASN1_BER_Data_Dec_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value, int length, ASN1TagType tagFlag);
extern int ASN1_BER_Data_Dec_PDUs(ASN1WorkSpace *workspace, PDUs *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Data_Dec_C2CAuthenticatedMessage(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	int len = length;
	ASNUINT8 *_cpointer;
	value->options = (HeaderOptions *)mpool_malloc(workspace->Pmemory, sizeof(HeaderOptions));
	memset(value->options, 0, sizeof(HeaderOptions));
	value->pdu = (PDUs *)mpool_malloc(workspace->Pmemory, sizeof(PDUs));
	memset(value->pdu, 0, sizeof(PDUs));
	if (tagFlag == ASN1EXPL)
	{
		if ((ret = ASN1_BER_User_Dec_Tag(workspace,ITS_ASN_UNIV|ITS_ASN_CONS|16)) < 0) return ret;
		if ((ret = ASN1_BER_User_Dec_Length(workspace,&length)) < 0) return ret;
	}
	ASN1_Save_Current_P(workspace, &_cpointer);
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 0)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_OCTETSTRING(workspace, &value->datex_AuthenticationInfo_text, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 1)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->datex_DataPacket_number, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_PRIM | 2)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Dec_INTEGER(workspace, &value->datex_DataPacketPriority_number, len, ASN1IMPL)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 3)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_HeaderOptions(workspace, value->options, len, ASN1IMPL)) < 0) return ret;
	if (IfFixedLength(len) == -1)
	{
		if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
	}
	if ((ret = ASN1_BER_User_Dec_Tag(workspace, ITS_ASN_CONT | ITS_ASN_CONS | 4)) < 0) return ret;
	if ((ret = ASN1_BER_User_Dec_Length(workspace, &len)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_PDUs(workspace, value->pdu, len, ASN1EXPL)) < 0) return ret;
	if (IfFixedLength(len) == -1)
	{
		if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
	}
	ASN1_Dec_Seq_EXT_UNKnow(workspace, _cpointer, length);
	if (tagFlag == ASN1EXPL)
	{
		if( IfFixedLength(length) == -1)
		{
			if ((ret = ASN1_BER_Dec_StrmEOC(workspace)) < 0) return ret;
		}
	}
	return ret;
}
extern int ASN1_CHECK_C2CAuthenticatedMessage(C2CAuthenticatedMessage *value);
extern int ASN1_BER_Data_Dec_C2CAuthenticatedMessage(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, int length, ASN1TagType tagFlag);
int ASN1_BER_Dec_C2CAuthenticatedMessage(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, int length, ASN1TagType tagFlag)
{
	int ret = 0;
	if ((ret = _ASN1_BER_CHECK_Length(workspace)) < 0) return ret;
	if ((ret = ASN1_BER_Data_Dec_C2CAuthenticatedMessage(workspace,value,length,tagFlag)) < 0) return ret;
	if ((ret = ASN1_CHECK_C2CAuthenticatedMessage(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Enc_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value);
extern int ASN1_PER_Align_Data_Enc_PDUs(ASN1WorkSpace *workspace, PDUs *value);
int ASN1_PER_Align_Data_Enc_C2CAuthenticatedMessage(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datex_AuthenticationInfo_text = { ASN1_CONST64(0), ASN1_CONST64(255), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_DataPacket_number = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_DataPacketPriority_number = { ASN1_CONST64(0), ASN1_CONST64(10), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_options = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_pdu = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_Align_Enc_OCTETSTRING(workspace, &(value->datex_AuthenticationInfo_text), &consinfo_datex_AuthenticationInfo_text)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->datex_DataPacket_number), &consinfo_datex_DataPacket_number)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_INTEGER(workspace, &(value->datex_DataPacketPriority_number), &consinfo_datex_DataPacketPriority_number)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_HeaderOptions(workspace, value->options)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Enc_PDUs(workspace, value->pdu)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_C2CAuthenticatedMessage(C2CAuthenticatedMessage *value);
extern int ASN1_PER_Align_Data_Enc_C2CAuthenticatedMessage(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value);
int ASN1_PER_Align_Enc_C2CAuthenticatedMessage(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_C2CAuthenticatedMessage(value)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Data_Enc_C2CAuthenticatedMessage(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_Align_Data_Dec_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value);
extern int ASN1_PER_Align_Data_Dec_PDUs(ASN1WorkSpace *workspace, PDUs *value);
int ASN1_PER_Align_Data_Dec_C2CAuthenticatedMessage(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datex_AuthenticationInfo_text = { ASN1_CONST64(0), ASN1_CONST64(255), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_DataPacket_number = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_DataPacketPriority_number = { ASN1_CONST64(0), ASN1_CONST64(10), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_options = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_pdu = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	value->options = (HeaderOptions *)mpool_malloc(workspace->Pmemory, sizeof(HeaderOptions));
	memset(value->options, 0, sizeof(HeaderOptions));
	value->pdu = (PDUs *)mpool_malloc(workspace->Pmemory, sizeof(PDUs));
	memset(value->pdu, 0, sizeof(PDUs));
	if ((ret = ASN1_PER_Align_Dec_OCTETSTRING(workspace, &(value->datex_AuthenticationInfo_text), &consinfo_datex_AuthenticationInfo_text)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->datex_DataPacket_number), &consinfo_datex_DataPacket_number)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_INTEGER(workspace, &(value->datex_DataPacketPriority_number), &consinfo_datex_DataPacketPriority_number)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_HeaderOptions(workspace, value->options)) < 0) return ret;
	if ((ret = ASN1_PER_Align_Dec_PDUs(workspace, value->pdu)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_C2CAuthenticatedMessage(C2CAuthenticatedMessage *value);
extern int ASN1_PER_Align_Data_Dec_C2CAuthenticatedMessage(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value);
int ASN1_PER_Align_Dec_C2CAuthenticatedMessage(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_Align_Data_Dec_C2CAuthenticatedMessage(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_C2CAuthenticatedMessage(value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Enc_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value);
extern int ASN1_PER_UNAlign_Data_Enc_PDUs(ASN1WorkSpace *workspace, PDUs *value);
int ASN1_PER_UNAlign_Data_Enc_C2CAuthenticatedMessage(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datex_AuthenticationInfo_text = { ASN1_CONST64(0), ASN1_CONST64(255), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_DataPacket_number = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_DataPacketPriority_number = { ASN1_CONST64(0), ASN1_CONST64(10), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_options = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_pdu = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	if ((ret = ASN1_PER_UNAlign_Enc_OCTETSTRING(workspace, &(value->datex_AuthenticationInfo_text), &consinfo_datex_AuthenticationInfo_text)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->datex_DataPacket_number), &consinfo_datex_DataPacket_number)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_INTEGER(workspace, &(value->datex_DataPacketPriority_number), &consinfo_datex_DataPacketPriority_number)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_HeaderOptions(workspace, value->options)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Enc_PDUs(workspace, value->pdu)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_C2CAuthenticatedMessage(C2CAuthenticatedMessage *value);
extern int ASN1_PER_UNAlign_Data_Enc_C2CAuthenticatedMessage(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value);
int ASN1_PER_UNAlign_Enc_C2CAuthenticatedMessage(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value)
{ // ASN1_PER_Extern_Encode 
	int ret = 0;
	if ((ret = ASN1_CHECK_C2CAuthenticatedMessage(value)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Data_Enc_C2CAuthenticatedMessage(workspace,value)) < 0) return ret;
	return ret;
}
extern int ASN1_PER_UNAlign_Data_Dec_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value);
extern int ASN1_PER_UNAlign_Data_Dec_PDUs(ASN1WorkSpace *workspace, PDUs *value);
int ASN1_PER_UNAlign_Data_Dec_C2CAuthenticatedMessage(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_datex_AuthenticationInfo_text = { ASN1_CONST64(0), ASN1_CONST64(255), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_DataPacket_number = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_datex_DataPacketPriority_number = { ASN1_CONST64(0), ASN1_CONST64(10), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_options = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_pdu = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	value->options = (HeaderOptions *)mpool_malloc(workspace->Pmemory, sizeof(HeaderOptions));
	memset(value->options, 0, sizeof(HeaderOptions));
	value->pdu = (PDUs *)mpool_malloc(workspace->Pmemory, sizeof(PDUs));
	memset(value->pdu, 0, sizeof(PDUs));
	if ((ret = ASN1_PER_UNAlign_Dec_OCTETSTRING(workspace, &(value->datex_AuthenticationInfo_text), &consinfo_datex_AuthenticationInfo_text)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->datex_DataPacket_number), &consinfo_datex_DataPacket_number)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->datex_DataPacketPriority_number), &consinfo_datex_DataPacketPriority_number)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_HeaderOptions(workspace, value->options)) < 0) return ret;
	if ((ret = ASN1_PER_UNAlign_Dec_PDUs(workspace, value->pdu)) < 0) return ret;
	return ret;
}
extern int ASN1_CHECK_C2CAuthenticatedMessage(C2CAuthenticatedMessage *value);
extern int ASN1_PER_UNAlign_Data_Dec_C2CAuthenticatedMessage(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value);
int ASN1_PER_UNAlign_Dec_C2CAuthenticatedMessage(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value)
{
	int ret = 0;
	if ((ret = ASN1_PER_UNAlign_Data_Dec_C2CAuthenticatedMessage(workspace,value)) < 0) return ret;
	if ((ret = ASN1_CHECK_C2CAuthenticatedMessage(value)) < 0) return ret;
	return ret;
}

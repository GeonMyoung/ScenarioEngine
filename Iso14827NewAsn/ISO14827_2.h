#ifndef _ISO14827_2_H_
#define _ISO14827_2_H_

#include "BER/ASN1bersrc.h"
#include "PER/ASN1persrc.h"
#include "IO/ASN1IO.h"
#include "MEM/mpool.h"
#include "OS/ASN1_Sys.h"
#include "TOOL/ASN1Tool.h"
#include "TYPE/ASN1_Type.h"

#include "ISO14827_1.h"


/********************************************************
*DatexDataPacket_datex_Version_number                   *
********************************************************/
#ifndef STRUC_DatexDataPacket_datex_Version_number
#define STRUC_DatexDataPacket_datex_Version_number
enum DatexDataPacket_datex_Version_number {
	DatexDataPacket_datex_Version_number_experimental = 0,
	DatexDataPacket_datex_Version_number_version1 = 1,
	DatexDataPacket_datex_Version_number_version2 = 2,
};
typedef enum DatexDataPacket_datex_Version_number DatexDataPacket_datex_Version_number;
#endif

ASN1_CPPLINK int ASN1_Print_DatexDataPacket_datex_Version_number(DatexDataPacket_datex_Version_number *value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_DatexDataPacket_datex_Version_number(ASN1WorkSpace *workspace, DatexDataPacket_datex_Version_number *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_DatexDataPacket_datex_Version_number(ASN1WorkSpace *workspace, DatexDataPacket_datex_Version_number *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_DatexDataPacket_datex_Version_number(ASN1WorkSpace *workspace, DatexDataPacket_datex_Version_number *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_DatexDataPacket_datex_Version_number(ASN1WorkSpace *workspace, DatexDataPacket_datex_Version_number *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_DatexDataPacket_datex_Version_number(ASN1WorkSpace *workspace, DatexDataPacket_datex_Version_number *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_DatexDataPacket_datex_Version_number(ASN1WorkSpace *workspace, DatexDataPacket_datex_Version_number *value);

/********************************************************
*DatexDataPacket                                        *
********************************************************/
struct DatexDataPacket {
	enum DatexDataPacket_datex_Version_number datex_Version_number;
	OCTETSTRING datex_Data;
	OCTETSTRING datex_Crc_nbr;
};
#ifndef STRUC_DatexDataPacket
#define STRUC_DatexDataPacket
typedef struct DatexDataPacket DatexDataPacket;

#endif

ASN1_CPPLINK int ASN1_Print_DatexDataPacket(DatexDataPacket *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_DatexDataPacket_datex_Version_number(ASN1WorkSpace *workspace, DatexDataPacket *value, ENUMERATED user_value);
ASN1_CPPLINK int ASN1_SET_DatexDataPacket_datex_Data(ASN1WorkSpace *workspace, DatexDataPacket *value, ASNUINT8 *user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_DatexDataPacket_datex_Crc_nbr(ASN1WorkSpace *workspace, DatexDataPacket *value, ASNUINT8 *user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_GET_DatexDataPacket_datex_Version_number(ASN1WorkSpace *workspace, DatexDataPacket *value, ENUMERATED *user_value);
ASN1_CPPLINK int ASN1_GET_DatexDataPacket_datex_Data(ASN1WorkSpace *workspace, DatexDataPacket *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length);
ASN1_CPPLINK int ASN1_GET_DatexDataPacket_datex_Crc_nbr(ASN1WorkSpace *workspace, DatexDataPacket *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length);
ASN1_CPPLINK int ASN1_BER_Enc_DatexDataPacket(ASN1WorkSpace *workspace, DatexDataPacket *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_DatexDataPacket(ASN1WorkSpace *workspace, DatexDataPacket *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_DatexDataPacket(ASN1WorkSpace *workspace, DatexDataPacket *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_DatexDataPacket(ASN1WorkSpace *workspace, DatexDataPacket *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_DatexDataPacket(ASN1WorkSpace *workspace, DatexDataPacket *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_DatexDataPacket(ASN1WorkSpace *workspace, DatexDataPacket *value);

/********************************************************
*Cost                                                   *
********************************************************/
struct Cost {
	OCTETSTRING amount_Currency_code;
	INTEGER amount_Factor_quantity;
	INTEGER amount_Quantity_quantity;
};
#ifndef STRUC_Cost
#define STRUC_Cost
typedef struct Cost Cost;

#endif

ASN1_CPPLINK int ASN1_Print_Cost(Cost *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_Cost_amount_Currency_code(ASN1WorkSpace *workspace, Cost *value, ASNUINT8 *user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_Cost_amount_Factor_quantity(ASN1WorkSpace *workspace, Cost *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_Cost_amount_Quantity_quantity(ASN1WorkSpace *workspace, Cost *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_GET_Cost_amount_Currency_code(ASN1WorkSpace *workspace, Cost *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length);
ASN1_CPPLINK int ASN1_GET_Cost_amount_Factor_quantity(ASN1WorkSpace *workspace, Cost *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_Cost_amount_Quantity_quantity(ASN1WorkSpace *workspace, Cost *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_BER_Enc_Cost(ASN1WorkSpace *workspace, Cost *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_Cost(ASN1WorkSpace *workspace, Cost *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_Cost(ASN1WorkSpace *workspace, Cost *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_Cost(ASN1WorkSpace *workspace, Cost *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_Cost(ASN1WorkSpace *workspace, Cost *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_Cost(ASN1WorkSpace *workspace, Cost *value);

/********************************************************
*IsoTime_time_SecondFractions                           *
********************************************************/
struct IsoTime_time_SecondFractions {
	ASNUINT64 M;
#define DEF_IsoTime_time_SecondFractions_deci_seconds	0
#define DEF_IsoTime_time_SecondFractions_centi_seconds	1
#define DEF_IsoTime_time_SecondFractions_milli_seconds	2
	union {
		INTEGER deci_seconds;
		INTEGER centi_seconds;
		INTEGER milli_seconds;
	} elements;
}; 
#ifndef STRUC_IsoTime_time_SecondFractions
#define STRUC_IsoTime_time_SecondFractions
typedef struct IsoTime_time_SecondFractions IsoTime_time_SecondFractions;
#endif
ASN1_CPPLINK int ASN1_Print_IsoTime_time_SecondFractions(IsoTime_time_SecondFractions *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_IsoTime_time_SecondFractions_deci_seconds(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_IsoTime_time_SecondFractions_centi_seconds(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_IsoTime_time_SecondFractions_milli_seconds(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_GET_IsoTime_time_SecondFractions_deci_seconds(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_IsoTime_time_SecondFractions_centi_seconds(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_IsoTime_time_SecondFractions_milli_seconds(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_BER_Enc_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime_time_SecondFractions *value);

/********************************************************
*IsoTime_time_Timezone                                  *
********************************************************/
struct IsoTime_time_Timezone {
	int DEF_IsoTime_time_Timezone_timezone_Hour_qty;
	int DEF_IsoTime_time_Timezone_time_Minute_qty;
	INTEGER timezone_Hour_qty;	/* default */
	INTEGER time_Minute_qty;	/* default */
};
#ifndef STRUC_IsoTime_time_Timezone
#define STRUC_IsoTime_time_Timezone
typedef struct IsoTime_time_Timezone IsoTime_time_Timezone;

#endif

ASN1_CPPLINK int ASN1_Print_IsoTime_time_Timezone(IsoTime_time_Timezone *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_IsoTime_time_Timezone_timezone_Hour_qty(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_IsoTime_time_Timezone_time_Minute_qty(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_GET_IsoTime_time_Timezone_timezone_Hour_qty(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_IsoTime_time_Timezone_time_Minute_qty(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_BER_Enc_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime_time_Timezone *value);

/********************************************************
*IsoTime                                                *
********************************************************/
struct IsoTime {
	int DEF_IsoTime_time_Year_qty;
	int DEF_IsoTime_time_Month_qty;
	int DEF_IsoTime_time_Day_qty;
	int DEF_IsoTime_time_Hour_qty;
	int DEF_IsoTime_time_Minute_qty;
	int DEF_IsoTime_time_Second_qty;
	int DEF_IsoTime_time_SecondFractions;
	int DEF_IsoTime_time_Timezone;
	INTEGER time_Year_qty;	/* optional */
	INTEGER time_Month_qty;	/* optional */
	INTEGER time_Day_qty;	/* optional */
	INTEGER time_Hour_qty;	/* default */
	INTEGER time_Minute_qty;	/* default */
	INTEGER time_Second_qty;	/* default */
	IsoTime_time_SecondFractions *time_SecondFractions;	/* default */
	IsoTime_time_Timezone *time_Timezone;	/* optional */
};
#ifndef STRUC_IsoTime
#define STRUC_IsoTime
typedef struct IsoTime IsoTime;

#endif

ASN1_CPPLINK int ASN1_Print_IsoTime(IsoTime *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_IsoTime_time_Year_qty(ASN1WorkSpace *workspace, IsoTime *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_IsoTime_time_Month_qty(ASN1WorkSpace *workspace, IsoTime *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_IsoTime_time_Day_qty(ASN1WorkSpace *workspace, IsoTime *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_IsoTime_time_Hour_qty(ASN1WorkSpace *workspace, IsoTime *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_IsoTime_time_Minute_qty(ASN1WorkSpace *workspace, IsoTime *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_IsoTime_time_Second_qty(ASN1WorkSpace *workspace, IsoTime *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime *value, IsoTime_time_SecondFractions *user_value);
ASN1_CPPLINK int ASN1_SET_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime *value, IsoTime_time_Timezone *user_value);
ASN1_CPPLINK int ASN1_GET_IsoTime_time_Year_qty(ASN1WorkSpace *workspace, IsoTime *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_IsoTime_time_Month_qty(ASN1WorkSpace *workspace, IsoTime *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_IsoTime_time_Day_qty(ASN1WorkSpace *workspace, IsoTime *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_IsoTime_time_Hour_qty(ASN1WorkSpace *workspace, IsoTime *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_IsoTime_time_Minute_qty(ASN1WorkSpace *workspace, IsoTime *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_IsoTime_time_Second_qty(ASN1WorkSpace *workspace, IsoTime *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_IsoTime_time_SecondFractions(ASN1WorkSpace *workspace, IsoTime *value, IsoTime_time_SecondFractions **user_value);
ASN1_CPPLINK int ASN1_GET_IsoTime_time_Timezone(ASN1WorkSpace *workspace, IsoTime *value, IsoTime_time_Timezone **user_value);
ASN1_CPPLINK int ASN1_BER_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_IsoTime(ASN1WorkSpace *workspace, IsoTime *value);

/********************************************************
*HeaderOptions                                          *
********************************************************/
struct HeaderOptions {
	int DEF_HeaderOptions_datex_Origin_text;
	int DEF_HeaderOptions_datex_OriginAddress_location;
	int DEF_HeaderOptions_datex_Sender_text;
	int DEF_HeaderOptions_datex_SenderAddress_location;
	int DEF_HeaderOptions_datex_Destination_text;
	int DEF_HeaderOptions_datex_DestinationAddress_location;
	int DEF_HeaderOptions_datex_Cost;
	int DEF_HeaderOptions_datex_DataPacket_time;
	UTF8Str datex_Origin_text;	/* optional */
	OCTETSTRING datex_OriginAddress_location;	/* optional */
	UTF8Str datex_Sender_text;	/* optional */
	OCTETSTRING datex_SenderAddress_location;	/* optional */
	UTF8Str datex_Destination_text;	/* optional */
	OCTETSTRING datex_DestinationAddress_location;	/* optional */
	Cost *datex_Cost;	/* optional */
	IsoTime *datex_DataPacket_time;	/* optional */
};
#ifndef STRUC_HeaderOptions
#define STRUC_HeaderOptions
typedef struct HeaderOptions HeaderOptions;

#endif

ASN1_CPPLINK int ASN1_Print_HeaderOptions(HeaderOptions *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_HeaderOptions_datex_Origin_text(ASN1WorkSpace *workspace, HeaderOptions *value, ASNUINT8 *user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_HeaderOptions_datex_OriginAddress_location(ASN1WorkSpace *workspace, HeaderOptions *value, ASNUINT8 *user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_HeaderOptions_datex_Sender_text(ASN1WorkSpace *workspace, HeaderOptions *value, ASNUINT8 *user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_HeaderOptions_datex_SenderAddress_location(ASN1WorkSpace *workspace, HeaderOptions *value, ASNUINT8 *user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_HeaderOptions_datex_Destination_text(ASN1WorkSpace *workspace, HeaderOptions *value, ASNUINT8 *user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_HeaderOptions_datex_DestinationAddress_location(ASN1WorkSpace *workspace, HeaderOptions *value, ASNUINT8 *user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_HeaderOptions_datex_Cost(ASN1WorkSpace *workspace, HeaderOptions *value, Cost *user_value);
ASN1_CPPLINK int ASN1_SET_HeaderOptions_datex_DataPacket_time(ASN1WorkSpace *workspace, HeaderOptions *value, IsoTime *user_value);
ASN1_CPPLINK int ASN1_GET_HeaderOptions_datex_Origin_text(ASN1WorkSpace *workspace, HeaderOptions *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length);
ASN1_CPPLINK int ASN1_GET_HeaderOptions_datex_OriginAddress_location(ASN1WorkSpace *workspace, HeaderOptions *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length);
ASN1_CPPLINK int ASN1_GET_HeaderOptions_datex_Sender_text(ASN1WorkSpace *workspace, HeaderOptions *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length);
ASN1_CPPLINK int ASN1_GET_HeaderOptions_datex_SenderAddress_location(ASN1WorkSpace *workspace, HeaderOptions *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length);
ASN1_CPPLINK int ASN1_GET_HeaderOptions_datex_Destination_text(ASN1WorkSpace *workspace, HeaderOptions *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length);
ASN1_CPPLINK int ASN1_GET_HeaderOptions_datex_DestinationAddress_location(ASN1WorkSpace *workspace, HeaderOptions *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length);
ASN1_CPPLINK int ASN1_GET_HeaderOptions_datex_Cost(ASN1WorkSpace *workspace, HeaderOptions *value, Cost **user_value);
ASN1_CPPLINK int ASN1_GET_HeaderOptions_datex_DataPacket_time(ASN1WorkSpace *workspace, HeaderOptions *value, IsoTime **user_value);
ASN1_CPPLINK int ASN1_BER_Enc_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_HeaderOptions(ASN1WorkSpace *workspace, HeaderOptions *value);

/********************************************************
*Initiate                                               *
********************************************************/
struct Initiate {
	UTF8Str datex_Sender_txt;
	UTF8Str datex_Destination_txt;
};
#ifndef STRUC_Initiate
#define STRUC_Initiate
typedef struct Initiate Initiate;

#endif

ASN1_CPPLINK int ASN1_Print_Initiate(Initiate *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_Initiate_datex_Sender_txt(ASN1WorkSpace *workspace, Initiate *value, ASNUINT8 *user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_Initiate_datex_Destination_txt(ASN1WorkSpace *workspace, Initiate *value, ASNUINT8 *user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_GET_Initiate_datex_Sender_txt(ASN1WorkSpace *workspace, Initiate *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length);
ASN1_CPPLINK int ASN1_GET_Initiate_datex_Destination_txt(ASN1WorkSpace *workspace, Initiate *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length);
ASN1_CPPLINK int ASN1_BER_Enc_Initiate(ASN1WorkSpace *workspace, Initiate *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_Initiate(ASN1WorkSpace *workspace, Initiate *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_Initiate(ASN1WorkSpace *workspace, Initiate *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_Initiate(ASN1WorkSpace *workspace, Initiate *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_Initiate(ASN1WorkSpace *workspace, Initiate *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_Initiate(ASN1WorkSpace *workspace, Initiate *value);

/********************************************************
*Login_datexLogin_EncodingRules_id                      *
********************************************************/
#ifndef STRUC_Login_datexLogin_EncodingRules_id
#define STRUC_Login_datexLogin_EncodingRules_id
typedef ASN1List Login_datexLogin_EncodingRules_id;
#endif
ASN1_CPPLINK int ASN1_Print_Login_datexLogin_EncodingRules_id(Login_datexLogin_EncodingRules_id *value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login_datexLogin_EncodingRules_id *value);

/********************************************************
*Login_datexLogin_Initiator_cd                          *
********************************************************/
#ifndef STRUC_Login_datexLogin_Initiator_cd
#define STRUC_Login_datexLogin_Initiator_cd
enum Login_datexLogin_Initiator_cd {
	Login_datexLogin_Initiator_cd_serverInitiated = 0,
	Login_datexLogin_Initiator_cd_clientInitiated = 1,
};
typedef enum Login_datexLogin_Initiator_cd Login_datexLogin_Initiator_cd;
#endif

ASN1_CPPLINK int ASN1_Print_Login_datexLogin_Initiator_cd(Login_datexLogin_Initiator_cd *value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_Login_datexLogin_Initiator_cd(ASN1WorkSpace *workspace, Login_datexLogin_Initiator_cd *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_Login_datexLogin_Initiator_cd(ASN1WorkSpace *workspace, Login_datexLogin_Initiator_cd *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_Login_datexLogin_Initiator_cd(ASN1WorkSpace *workspace, Login_datexLogin_Initiator_cd *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_Login_datexLogin_Initiator_cd(ASN1WorkSpace *workspace, Login_datexLogin_Initiator_cd *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_Login_datexLogin_Initiator_cd(ASN1WorkSpace *workspace, Login_datexLogin_Initiator_cd *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_Login_datexLogin_Initiator_cd(ASN1WorkSpace *workspace, Login_datexLogin_Initiator_cd *value);

/********************************************************
*Login                                                  *
********************************************************/
struct Login {
	UTF8Str datex_Sender_txt;
	UTF8Str datex_Destination_txt;
	OCTETSTRING datexLogin_UserName_txt;
	OCTETSTRING datexLogin_Password_txt;
	Login_datexLogin_EncodingRules_id datexLogin_EncodingRules_id;
	INTEGER datexLogin_HeartbeatDurationMax_qty;
	INTEGER datexLogin_ResponseTimeOut_qty;
	enum Login_datexLogin_Initiator_cd datexLogin_Initiator_cd;
	INTEGER datexLogin_DatagramSize_qty;
};
#ifndef STRUC_Login
#define STRUC_Login
typedef struct Login Login;

#endif

ASN1_CPPLINK int ASN1_Print_Login(Login *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_Login_datex_Sender_txt(ASN1WorkSpace *workspace, Login *value, ASNUINT8 *user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_Login_datex_Destination_txt(ASN1WorkSpace *workspace, Login *value, ASNUINT8 *user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_Login_datexLogin_UserName_txt(ASN1WorkSpace *workspace, Login *value, ASNUINT8 *user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_Login_datexLogin_Password_txt(ASN1WorkSpace *workspace, Login *value, ASNUINT8 *user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login *value, Login_datexLogin_EncodingRules_id *user_value);
ASN1_CPPLINK int ASN1_SET_Login_datexLogin_HeartbeatDurationMax_qty(ASN1WorkSpace *workspace, Login *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_Login_datexLogin_ResponseTimeOut_qty(ASN1WorkSpace *workspace, Login *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_Login_datexLogin_Initiator_cd(ASN1WorkSpace *workspace, Login *value, ENUMERATED user_value);
ASN1_CPPLINK int ASN1_SET_Login_datexLogin_DatagramSize_qty(ASN1WorkSpace *workspace, Login *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_GET_Login_datex_Sender_txt(ASN1WorkSpace *workspace, Login *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length);
ASN1_CPPLINK int ASN1_GET_Login_datex_Destination_txt(ASN1WorkSpace *workspace, Login *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length);
ASN1_CPPLINK int ASN1_GET_Login_datexLogin_UserName_txt(ASN1WorkSpace *workspace, Login *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length);
ASN1_CPPLINK int ASN1_GET_Login_datexLogin_Password_txt(ASN1WorkSpace *workspace, Login *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length);
ASN1_CPPLINK int ASN1_GET_Login_datexLogin_EncodingRules_id(ASN1WorkSpace *workspace, Login *value, Login_datexLogin_EncodingRules_id **user_value);
ASN1_CPPLINK int ASN1_GET_Login_datexLogin_HeartbeatDurationMax_qty(ASN1WorkSpace *workspace, Login *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_Login_datexLogin_ResponseTimeOut_qty(ASN1WorkSpace *workspace, Login *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_Login_datexLogin_Initiator_cd(ASN1WorkSpace *workspace, Login *value, ENUMERATED *user_value);
ASN1_CPPLINK int ASN1_GET_Login_datexLogin_DatagramSize_qty(ASN1WorkSpace *workspace, Login *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_BER_Enc_Login(ASN1WorkSpace *workspace, Login *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_Login(ASN1WorkSpace *workspace, Login *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_Login(ASN1WorkSpace *workspace, Login *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_Login(ASN1WorkSpace *workspace, Login *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_Login(ASN1WorkSpace *workspace, Login *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_Login(ASN1WorkSpace *workspace, Login *value);

/********************************************************
*FrED                                                   *
********************************************************/
#ifndef STRUC_FrED
#define STRUC_FrED
typedef INTEGER FrED;
#endif

ASN1_CPPLINK int ASN1_Print_FrED(FrED *value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_FrED(ASN1WorkSpace *workspace, FrED *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_FrED(ASN1WorkSpace *workspace, FrED *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_FrED(ASN1WorkSpace *workspace, FrED *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_FrED(ASN1WorkSpace *workspace, FrED *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_FrED(ASN1WorkSpace *workspace, FrED *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_FrED(ASN1WorkSpace *workspace, FrED *value);

/********************************************************
*Terminate                                              *
********************************************************/
#ifndef STRUC_Terminate
#define STRUC_Terminate
enum Terminate {
	Terminate_other = 0,
	Terminate_serverRequested = 1,
	Terminate_clientRequested = 2,
	Terminate_serverShutdown = 3,
	Terminate_clientShutdown = 4,
	Terminate_serverCommProblems = 5,
	Terminate_clientCommProblems = 6,
};
typedef enum Terminate Terminate;
#endif

ASN1_CPPLINK int ASN1_Print_Terminate(Terminate *value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_Terminate(ASN1WorkSpace *workspace, Terminate *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_Terminate(ASN1WorkSpace *workspace, Terminate *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_Terminate(ASN1WorkSpace *workspace, Terminate *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_Terminate(ASN1WorkSpace *workspace, Terminate *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_Terminate(ASN1WorkSpace *workspace, Terminate *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_Terminate(ASN1WorkSpace *workspace, Terminate *value);

/********************************************************
*Logout                                                 *
********************************************************/
#ifndef STRUC_Logout
#define STRUC_Logout
enum Logout {
	Logout_other = 0,
	Logout_serverRequested = 1,
	Logout_clientRequested = 2,
	Logout_serverShutdown = 3,
	Logout_clientShutdown = 4,
	Logout_serverCommProblems = 5,
	Logout_clientCommProblems = 6,
};
typedef enum Logout Logout;
#endif

ASN1_CPPLINK int ASN1_Print_Logout(Logout *value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_Logout(ASN1WorkSpace *workspace, Logout *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_Logout(ASN1WorkSpace *workspace, Logout *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_Logout(ASN1WorkSpace *workspace, Logout *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_Logout(ASN1WorkSpace *workspace, Logout *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_Logout(ASN1WorkSpace *workspace, Logout *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_Logout(ASN1WorkSpace *workspace, Logout *value);

/********************************************************
*SubscriptionData_datexSubscribe_Status_cd              *
********************************************************/
#ifndef STRUC_SubscriptionData_datexSubscribe_Status_cd
#define STRUC_SubscriptionData_datexSubscribe_Status_cd
enum SubscriptionData_datexSubscribe_Status_cd {
	SubscriptionData_datexSubscribe_Status_cd_new = 0,
	SubscriptionData_datexSubscribe_Status_cd_update = 1,
};
typedef enum SubscriptionData_datexSubscribe_Status_cd SubscriptionData_datexSubscribe_Status_cd;
#endif

ASN1_CPPLINK int ASN1_Print_SubscriptionData_datexSubscribe_Status_cd(SubscriptionData_datexSubscribe_Status_cd *value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_SubscriptionData_datexSubscribe_Status_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_Status_cd *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_SubscriptionData_datexSubscribe_Status_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_Status_cd *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_SubscriptionData_datexSubscribe_Status_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_Status_cd *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_SubscriptionData_datexSubscribe_Status_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_Status_cd *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_SubscriptionData_datexSubscribe_Status_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_Status_cd *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_SubscriptionData_datexSubscribe_Status_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_Status_cd *value);

/********************************************************
*Registered_continuous                                  *
********************************************************/
struct Registered_continuous {
	int DEF_Registered_continuous_datexRegistered_UpdateDelay_qty;
	int DEF_Registered_continuous_datexRegistered_StartTime;
	int DEF_Registered_continuous_datexRegistered_EndTime;
	INTEGER datexRegistered_UpdateDelay_qty;	/* default */
	IsoTime *datexRegistered_StartTime;	/* optional */
	IsoTime *datexRegistered_EndTime;	/* optional */
};
#ifndef STRUC_Registered_continuous
#define STRUC_Registered_continuous
typedef struct Registered_continuous Registered_continuous;

#endif

ASN1_CPPLINK int ASN1_Print_Registered_continuous(Registered_continuous *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_Registered_continuous_datexRegistered_UpdateDelay_qty(ASN1WorkSpace *workspace, Registered_continuous *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_Registered_continuous_datexRegistered_StartTime(ASN1WorkSpace *workspace, Registered_continuous *value, IsoTime *user_value);
ASN1_CPPLINK int ASN1_SET_Registered_continuous_datexRegistered_EndTime(ASN1WorkSpace *workspace, Registered_continuous *value, IsoTime *user_value);
ASN1_CPPLINK int ASN1_GET_Registered_continuous_datexRegistered_UpdateDelay_qty(ASN1WorkSpace *workspace, Registered_continuous *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_Registered_continuous_datexRegistered_StartTime(ASN1WorkSpace *workspace, Registered_continuous *value, IsoTime **user_value);
ASN1_CPPLINK int ASN1_GET_Registered_continuous_datexRegistered_EndTime(ASN1WorkSpace *workspace, Registered_continuous *value, IsoTime **user_value);
ASN1_CPPLINK int ASN1_BER_Enc_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_Registered_continuous(ASN1WorkSpace *workspace, Registered_continuous *value);

/********************************************************
*Registered_daily_datexRegistered_DaysOfWeek_cd         *
********************************************************/
#define other_Registered_daily_datexRegistered_DaysOfWeek_cd	0
#define sunday_Registered_daily_datexRegistered_DaysOfWeek_cd	1
#define monday_Registered_daily_datexRegistered_DaysOfWeek_cd	2
#define tuesday_Registered_daily_datexRegistered_DaysOfWeek_cd	3
#define wednesday_Registered_daily_datexRegistered_DaysOfWeek_cd	4
#define thursday_Registered_daily_datexRegistered_DaysOfWeek_cd	5
#define friday_Registered_daily_datexRegistered_DaysOfWeek_cd	6
#define saturday_Registered_daily_datexRegistered_DaysOfWeek_cd	7
#ifndef STRUC_Registered_daily_datexRegistered_DaysOfWeek_cd
#define STRUC_Registered_daily_datexRegistered_DaysOfWeek_cd
typedef BITSTRING Registered_daily_datexRegistered_DaysOfWeek_cd;
#endif

ASN1_CPPLINK int ASN1_Print_Registered_daily_datexRegistered_DaysOfWeek_cd(Registered_daily_datexRegistered_DaysOfWeek_cd *value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_Registered_daily_datexRegistered_DaysOfWeek_cd(ASN1WorkSpace *workspace, Registered_daily_datexRegistered_DaysOfWeek_cd *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_Registered_daily_datexRegistered_DaysOfWeek_cd(ASN1WorkSpace *workspace, Registered_daily_datexRegistered_DaysOfWeek_cd *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_Registered_daily_datexRegistered_DaysOfWeek_cd(ASN1WorkSpace *workspace, Registered_daily_datexRegistered_DaysOfWeek_cd *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_Registered_daily_datexRegistered_DaysOfWeek_cd(ASN1WorkSpace *workspace, Registered_daily_datexRegistered_DaysOfWeek_cd *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_Registered_daily_datexRegistered_DaysOfWeek_cd(ASN1WorkSpace *workspace, Registered_daily_datexRegistered_DaysOfWeek_cd *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_Registered_daily_datexRegistered_DaysOfWeek_cd(ASN1WorkSpace *workspace, Registered_daily_datexRegistered_DaysOfWeek_cd *value);

/********************************************************
*Registered_daily                                       *
********************************************************/
struct Registered_daily {
	int DEF_Registered_daily_datexRegistered_UpdateDelay_qty;
	int DEF_Registered_daily_datexRegistered_StartDate;
	int DEF_Registered_daily_datexRegistered_EndDate;
	int DEF_Registered_daily_datexRegistered_StartTime;
	int DEF_Registered_daily_datexRegistered_Duration_qty;
	INTEGER datexRegistered_UpdateDelay_qty;	/* default */
	Registered_daily_datexRegistered_DaysOfWeek_cd datexRegistered_DaysOfWeek_cd;
	IsoTime *datexRegistered_StartDate;	/* optional */
	IsoTime *datexRegistered_EndDate;	/* optional */
	IsoTime *datexRegistered_StartTime;	/* optional */
	INTEGER datexRegistered_Duration_qty;	/* optional */
};
#ifndef STRUC_Registered_daily
#define STRUC_Registered_daily
typedef struct Registered_daily Registered_daily;

#endif

ASN1_CPPLINK int ASN1_Print_Registered_daily(Registered_daily *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_Registered_daily_datexRegistered_UpdateDelay_qty(ASN1WorkSpace *workspace, Registered_daily *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_Registered_daily_datexRegistered_DaysOfWeek_cd(ASN1WorkSpace *workspace, Registered_daily *value, ASNUINT8 *user_value, ASNUINT32L user_value_length);
ASN1_CPPLINK int ASN1_SET_Registered_daily_datexRegistered_StartDate(ASN1WorkSpace *workspace, Registered_daily *value, IsoTime *user_value);
ASN1_CPPLINK int ASN1_SET_Registered_daily_datexRegistered_EndDate(ASN1WorkSpace *workspace, Registered_daily *value, IsoTime *user_value);
ASN1_CPPLINK int ASN1_SET_Registered_daily_datexRegistered_StartTime(ASN1WorkSpace *workspace, Registered_daily *value, IsoTime *user_value);
ASN1_CPPLINK int ASN1_SET_Registered_daily_datexRegistered_Duration_qty(ASN1WorkSpace *workspace, Registered_daily *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_GET_Registered_daily_datexRegistered_UpdateDelay_qty(ASN1WorkSpace *workspace, Registered_daily *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_Registered_daily_datexRegistered_DaysOfWeek_cd(ASN1WorkSpace *workspace, Registered_daily *value, ASNUINT8 **user_value, ASNUINT32L *user_value_length);
ASN1_CPPLINK int ASN1_GET_Registered_daily_datexRegistered_StartDate(ASN1WorkSpace *workspace, Registered_daily *value, IsoTime **user_value);
ASN1_CPPLINK int ASN1_GET_Registered_daily_datexRegistered_EndDate(ASN1WorkSpace *workspace, Registered_daily *value, IsoTime **user_value);
ASN1_CPPLINK int ASN1_GET_Registered_daily_datexRegistered_StartTime(ASN1WorkSpace *workspace, Registered_daily *value, IsoTime **user_value);
ASN1_CPPLINK int ASN1_GET_Registered_daily_datexRegistered_Duration_qty(ASN1WorkSpace *workspace, Registered_daily *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_BER_Enc_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_Registered_daily(ASN1WorkSpace *workspace, Registered_daily *value);

/********************************************************
*Registered                                             *
********************************************************/
struct Registered {
	ASNUINT64 M;
#define DEF_Registered_continuous	0
#define DEF_Registered_daily	1
	union {
		Registered_continuous *continuous;
		Registered_daily *daily;
	} elements;
}; 
#ifndef STRUC_Registered
#define STRUC_Registered
typedef struct Registered Registered;
#endif
ASN1_CPPLINK int ASN1_Print_Registered(Registered *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_Registered_continuous(ASN1WorkSpace *workspace, Registered *value, Registered_continuous *user_value);
ASN1_CPPLINK int ASN1_SET_Registered_daily(ASN1WorkSpace *workspace, Registered *value, Registered_daily *user_value);
ASN1_CPPLINK int ASN1_GET_Registered_continuous(ASN1WorkSpace *workspace, Registered *value, Registered_continuous **user_value);
ASN1_CPPLINK int ASN1_GET_Registered_daily(ASN1WorkSpace *workspace, Registered *value, Registered_daily **user_value);
ASN1_CPPLINK int ASN1_BER_Enc_Registered(ASN1WorkSpace *workspace, Registered *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_Registered(ASN1WorkSpace *workspace, Registered *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_Registered(ASN1WorkSpace *workspace, Registered *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_Registered(ASN1WorkSpace *workspace, Registered *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_Registered(ASN1WorkSpace *workspace, Registered *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_Registered(ASN1WorkSpace *workspace, Registered *value);

/********************************************************
*SubscriptionMode                                       *
********************************************************/
struct SubscriptionMode {
	ASNUINT64 M;
#define DEF_SubscriptionMode_single	0
#define DEF_SubscriptionMode_event_driven	1
#define DEF_SubscriptionMode_periodic	2
	union {
		ASNUINT8 single;
		Registered *event_driven;
		Registered *periodic;
	} elements;
}; 
#ifndef STRUC_SubscriptionMode
#define STRUC_SubscriptionMode
typedef struct SubscriptionMode SubscriptionMode;
#endif
ASN1_CPPLINK int ASN1_Print_SubscriptionMode(SubscriptionMode *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_SubscriptionMode_single(ASN1WorkSpace *workspace, SubscriptionMode *value, ASNUINT8 user_value);
ASN1_CPPLINK int ASN1_SET_SubscriptionMode_event_driven(ASN1WorkSpace *workspace, SubscriptionMode *value, Registered *user_value);
ASN1_CPPLINK int ASN1_SET_SubscriptionMode_periodic(ASN1WorkSpace *workspace, SubscriptionMode *value, Registered *user_value);
ASN1_CPPLINK int ASN1_GET_SubscriptionMode_single(ASN1WorkSpace *workspace, SubscriptionMode *value, ASNUINT8 *user_value);
ASN1_CPPLINK int ASN1_GET_SubscriptionMode_event_driven(ASN1WorkSpace *workspace, SubscriptionMode *value, Registered **user_value);
ASN1_CPPLINK int ASN1_GET_SubscriptionMode_periodic(ASN1WorkSpace *workspace, SubscriptionMode *value, Registered **user_value);
ASN1_CPPLINK int ASN1_BER_Enc_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_SubscriptionMode(ASN1WorkSpace *workspace, SubscriptionMode *value);

/********************************************************
*SubscriptionData_datexSubscribe_PublishFormat_cd       *
********************************************************/
#ifndef STRUC_SubscriptionData_datexSubscribe_PublishFormat_cd
#define STRUC_SubscriptionData_datexSubscribe_PublishFormat_cd
enum SubscriptionData_datexSubscribe_PublishFormat_cd {
	SubscriptionData_datexSubscribe_PublishFormat_cd_other = 0,
	SubscriptionData_datexSubscribe_PublishFormat_cd_ftp = 1,
	SubscriptionData_datexSubscribe_PublishFormat_cd_tftp = 2,
	SubscriptionData_datexSubscribe_PublishFormat_cd_dataPacket = 3,
};
typedef enum SubscriptionData_datexSubscribe_PublishFormat_cd SubscriptionData_datexSubscribe_PublishFormat_cd;
#endif

ASN1_CPPLINK int ASN1_Print_SubscriptionData_datexSubscribe_PublishFormat_cd(SubscriptionData_datexSubscribe_PublishFormat_cd *value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_SubscriptionData_datexSubscribe_PublishFormat_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_PublishFormat_cd *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_SubscriptionData_datexSubscribe_PublishFormat_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_PublishFormat_cd *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_SubscriptionData_datexSubscribe_PublishFormat_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_PublishFormat_cd *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_SubscriptionData_datexSubscribe_PublishFormat_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_PublishFormat_cd *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_SubscriptionData_datexSubscribe_PublishFormat_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_PublishFormat_cd *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_SubscriptionData_datexSubscribe_PublishFormat_cd(ASN1WorkSpace *workspace, SubscriptionData_datexSubscribe_PublishFormat_cd *value);

/********************************************************
*EndApplicationMessage                                  *
********************************************************/
struct EndApplicationMessage {
	OBJECTIDENTIFIER endApplication_Message_id;
	OpenType endApplication_Message_msg;
};
#ifndef STRUC_EndApplicationMessage
#define STRUC_EndApplicationMessage
typedef struct EndApplicationMessage EndApplicationMessage;

#endif

ASN1_CPPLINK int ASN1_Print_EndApplicationMessage(EndApplicationMessage *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_EndApplicationMessage_endApplication_Message_id(ASN1WorkSpace *workspace, EndApplicationMessage *value, ASNUINT32 *user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_EndApplicationMessage_endApplication_Message_msg(ASN1WorkSpace *workspace, EndApplicationMessage *value, ASNUINT8 *user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_GET_EndApplicationMessage_endApplication_Message_id(ASN1WorkSpace *workspace, EndApplicationMessage *value, ASNUINT32 *user_value, ASNUINT32 *user_value_length);
ASN1_CPPLINK int ASN1_GET_EndApplicationMessage_endApplication_Message_msg(ASN1WorkSpace *workspace, EndApplicationMessage *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length);
ASN1_CPPLINK int ASN1_BER_Enc_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_EndApplicationMessage(ASN1WorkSpace *workspace, EndApplicationMessage *value);

/********************************************************
*SubscriptionData                                       *
********************************************************/
struct SubscriptionData {
	BOOLEAN datexSubscribe_Persistent_bool;
	enum SubscriptionData_datexSubscribe_Status_cd datexSubscribe_Status_cd;
	SubscriptionMode *datexSubscribe_Mode;
	enum SubscriptionData_datexSubscribe_PublishFormat_cd datexSubscribe_PublishFormat_cd;
	INTEGER datexSubscription_Priority_nbr;
	BOOLEAN datexSubscribe_Guarantee_bool;
	EndApplicationMessage *datexSubscribe_Pdu;
};
#ifndef STRUC_SubscriptionData
#define STRUC_SubscriptionData
typedef struct SubscriptionData SubscriptionData;

#endif

ASN1_CPPLINK int ASN1_Print_SubscriptionData(SubscriptionData *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_SubscriptionData_datexSubscribe_Persistent_bool(ASN1WorkSpace *workspace, SubscriptionData *value, BOOLEAN user_value);
ASN1_CPPLINK int ASN1_SET_SubscriptionData_datexSubscribe_Status_cd(ASN1WorkSpace *workspace, SubscriptionData *value, ENUMERATED user_value);
ASN1_CPPLINK int ASN1_SET_SubscriptionData_datexSubscribe_Mode(ASN1WorkSpace *workspace, SubscriptionData *value, SubscriptionMode *user_value);
ASN1_CPPLINK int ASN1_SET_SubscriptionData_datexSubscribe_PublishFormat_cd(ASN1WorkSpace *workspace, SubscriptionData *value, ENUMERATED user_value);
ASN1_CPPLINK int ASN1_SET_SubscriptionData_datexSubscription_Priority_nbr(ASN1WorkSpace *workspace, SubscriptionData *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_SubscriptionData_datexSubscribe_Guarantee_bool(ASN1WorkSpace *workspace, SubscriptionData *value, BOOLEAN user_value);
ASN1_CPPLINK int ASN1_SET_SubscriptionData_datexSubscribe_Pdu(ASN1WorkSpace *workspace, SubscriptionData *value, EndApplicationMessage *user_value);
ASN1_CPPLINK int ASN1_GET_SubscriptionData_datexSubscribe_Persistent_bool(ASN1WorkSpace *workspace, SubscriptionData *value, BOOLEAN *user_value);
ASN1_CPPLINK int ASN1_GET_SubscriptionData_datexSubscribe_Status_cd(ASN1WorkSpace *workspace, SubscriptionData *value, ENUMERATED *user_value);
ASN1_CPPLINK int ASN1_GET_SubscriptionData_datexSubscribe_Mode(ASN1WorkSpace *workspace, SubscriptionData *value, SubscriptionMode **user_value);
ASN1_CPPLINK int ASN1_GET_SubscriptionData_datexSubscribe_PublishFormat_cd(ASN1WorkSpace *workspace, SubscriptionData *value, ENUMERATED *user_value);
ASN1_CPPLINK int ASN1_GET_SubscriptionData_datexSubscription_Priority_nbr(ASN1WorkSpace *workspace, SubscriptionData *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_SubscriptionData_datexSubscribe_Guarantee_bool(ASN1WorkSpace *workspace, SubscriptionData *value, BOOLEAN *user_value);
ASN1_CPPLINK int ASN1_GET_SubscriptionData_datexSubscribe_Pdu(ASN1WorkSpace *workspace, SubscriptionData *value, EndApplicationMessage **user_value);
ASN1_CPPLINK int ASN1_BER_Enc_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_SubscriptionData(ASN1WorkSpace *workspace, SubscriptionData *value);

/********************************************************
*SubscriptionType_datexSubscribe_CancelReason_cd        *
********************************************************/
#ifndef STRUC_SubscriptionType_datexSubscribe_CancelReason_cd
#define STRUC_SubscriptionType_datexSubscribe_CancelReason_cd
enum SubscriptionType_datexSubscribe_CancelReason_cd {
	SubscriptionType_datexSubscribe_CancelReason_cd_other = 0,
	SubscriptionType_datexSubscribe_CancelReason_cd_dataNotNeeded = 1,
	SubscriptionType_datexSubscribe_CancelReason_cd_errorsInPublication = 2,
	SubscriptionType_datexSubscribe_CancelReason_cd_pendingLogout = 3,
	SubscriptionType_datexSubscribe_CancelReason_cd_processingMgmt = 4,
	SubscriptionType_datexSubscribe_CancelReason_cd_bandwidthMgmt = 5,
};
typedef enum SubscriptionType_datexSubscribe_CancelReason_cd SubscriptionType_datexSubscribe_CancelReason_cd;
#endif

ASN1_CPPLINK int ASN1_Print_SubscriptionType_datexSubscribe_CancelReason_cd(SubscriptionType_datexSubscribe_CancelReason_cd *value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_SubscriptionType_datexSubscribe_CancelReason_cd(ASN1WorkSpace *workspace, SubscriptionType_datexSubscribe_CancelReason_cd *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_SubscriptionType_datexSubscribe_CancelReason_cd(ASN1WorkSpace *workspace, SubscriptionType_datexSubscribe_CancelReason_cd *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_SubscriptionType_datexSubscribe_CancelReason_cd(ASN1WorkSpace *workspace, SubscriptionType_datexSubscribe_CancelReason_cd *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_SubscriptionType_datexSubscribe_CancelReason_cd(ASN1WorkSpace *workspace, SubscriptionType_datexSubscribe_CancelReason_cd *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_SubscriptionType_datexSubscribe_CancelReason_cd(ASN1WorkSpace *workspace, SubscriptionType_datexSubscribe_CancelReason_cd *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_SubscriptionType_datexSubscribe_CancelReason_cd(ASN1WorkSpace *workspace, SubscriptionType_datexSubscribe_CancelReason_cd *value);

/********************************************************
*SubscriptionType                                       *
********************************************************/
struct SubscriptionType {
	ASNUINT64 M;
#define DEF_SubscriptionType_subscription	0
#define DEF_SubscriptionType_datexSubscribe_CancelReason_cd	1
	union {
		SubscriptionData *subscription;
		enum SubscriptionType_datexSubscribe_CancelReason_cd datexSubscribe_CancelReason_cd;
	} elements;
}; 
#ifndef STRUC_SubscriptionType
#define STRUC_SubscriptionType
typedef struct SubscriptionType SubscriptionType;
#endif
ASN1_CPPLINK int ASN1_Print_SubscriptionType(SubscriptionType *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_SubscriptionType_subscription(ASN1WorkSpace *workspace, SubscriptionType *value, SubscriptionData *user_value);
ASN1_CPPLINK int ASN1_SET_SubscriptionType_datexSubscribe_CancelReason_cd(ASN1WorkSpace *workspace, SubscriptionType *value, ENUMERATED user_value);
ASN1_CPPLINK int ASN1_GET_SubscriptionType_subscription(ASN1WorkSpace *workspace, SubscriptionType *value, SubscriptionData **user_value);
ASN1_CPPLINK int ASN1_GET_SubscriptionType_datexSubscribe_CancelReason_cd(ASN1WorkSpace *workspace, SubscriptionType *value, ENUMERATED *user_value);
ASN1_CPPLINK int ASN1_BER_Enc_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_SubscriptionType(ASN1WorkSpace *workspace, SubscriptionType *value);

/********************************************************
*Subscription                                           *
********************************************************/
struct Subscription {
	INTEGER datexSubscribe_Serial_nbr;
	SubscriptionType *datexSubscribe_Type;
	ASNUINT64 E;
};
#ifndef STRUC_Subscription
#define STRUC_Subscription
typedef struct Subscription Subscription;

#endif

ASN1_CPPLINK int ASN1_Print_Subscription(Subscription *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_Subscription_datexSubscribe_Serial_nbr(ASN1WorkSpace *workspace, Subscription *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_Subscription_datexSubscribe_Type(ASN1WorkSpace *workspace, Subscription *value, SubscriptionType *user_value);
ASN1_CPPLINK int ASN1_GET_Subscription_datexSubscribe_Serial_nbr(ASN1WorkSpace *workspace, Subscription *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_Subscription_datexSubscribe_Type(ASN1WorkSpace *workspace, Subscription *value, SubscriptionType **user_value);
ASN1_CPPLINK int ASN1_BER_Enc_Subscription(ASN1WorkSpace *workspace, Subscription *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_Subscription(ASN1WorkSpace *workspace, Subscription *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_Subscription(ASN1WorkSpace *workspace, Subscription *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_Subscription(ASN1WorkSpace *workspace, Subscription *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_Subscription(ASN1WorkSpace *workspace, Subscription *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_Subscription(ASN1WorkSpace *workspace, Subscription *value);

/********************************************************
*PublicationType_datexPublication_Management_cd         *
********************************************************/
#ifndef STRUC_PublicationType_datexPublication_Management_cd
#define STRUC_PublicationType_datexPublication_Management_cd
enum PublicationType_datexPublication_Management_cd {
	PublicationType_datexPublication_Management_cd_temporarilySuspended = 0,
	PublicationType_datexPublication_Management_cd_resume = 1,
	PublicationType_datexPublication_Management_cd_terminate_other = 2,
	PublicationType_datexPublication_Management_cd_terminate_dataNoLongerAvailable = 3,
	PublicationType_datexPublication_Management_cd_terminate_publicationsBeingRejected = 4,
	PublicationType_datexPublication_Management_cd_terminate_PendingShutdown = 5,
	PublicationType_datexPublication_Management_cd_terminate_processingMgmt = 6,
	PublicationType_datexPublication_Management_cd_terminate_bandwidthMgmt = 7,
	PublicationType_datexPublication_Management_cd_terminate_accessDenied = 8,
	PublicationType_datexPublication_Management_cd_unknownRequest = 9,
};
typedef enum PublicationType_datexPublication_Management_cd PublicationType_datexPublication_Management_cd;
#endif

ASN1_CPPLINK int ASN1_Print_PublicationType_datexPublication_Management_cd(PublicationType_datexPublication_Management_cd *value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_PublicationType_datexPublication_Management_cd(ASN1WorkSpace *workspace, PublicationType_datexPublication_Management_cd *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_PublicationType_datexPublication_Management_cd(ASN1WorkSpace *workspace, PublicationType_datexPublication_Management_cd *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_PublicationType_datexPublication_Management_cd(ASN1WorkSpace *workspace, PublicationType_datexPublication_Management_cd *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_PublicationType_datexPublication_Management_cd(ASN1WorkSpace *workspace, PublicationType_datexPublication_Management_cd *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_PublicationType_datexPublication_Management_cd(ASN1WorkSpace *workspace, PublicationType_datexPublication_Management_cd *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_PublicationType_datexPublication_Management_cd(ASN1WorkSpace *workspace, PublicationType_datexPublication_Management_cd *value);

/********************************************************
*PublicationType                                        *
********************************************************/
struct PublicationType {
	ASNUINT64 M;
#define DEF_PublicationType_datexPublication_Management_cd	0
#define DEF_PublicationType_datexPublish_Data	1
	union {
		enum PublicationType_datexPublication_Management_cd datexPublication_Management_cd;
		EndApplicationMessage *datexPublish_Data;
	} elements;
}; 
#ifndef STRUC_PublicationType
#define STRUC_PublicationType
typedef struct PublicationType PublicationType;
#endif
ASN1_CPPLINK int ASN1_Print_PublicationType(PublicationType *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_PublicationType_datexPublication_Management_cd(ASN1WorkSpace *workspace, PublicationType *value, ENUMERATED user_value);
ASN1_CPPLINK int ASN1_SET_PublicationType_datexPublish_Data(ASN1WorkSpace *workspace, PublicationType *value, EndApplicationMessage *user_value);
ASN1_CPPLINK int ASN1_GET_PublicationType_datexPublication_Management_cd(ASN1WorkSpace *workspace, PublicationType *value, ENUMERATED *user_value);
ASN1_CPPLINK int ASN1_GET_PublicationType_datexPublish_Data(ASN1WorkSpace *workspace, PublicationType *value, EndApplicationMessage **user_value);
ASN1_CPPLINK int ASN1_BER_Enc_PublicationType(ASN1WorkSpace *workspace, PublicationType *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_PublicationType(ASN1WorkSpace *workspace, PublicationType *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_PublicationType(ASN1WorkSpace *workspace, PublicationType *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_PublicationType(ASN1WorkSpace *workspace, PublicationType *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_PublicationType(ASN1WorkSpace *workspace, PublicationType *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_PublicationType(ASN1WorkSpace *workspace, PublicationType *value);

/********************************************************
*PublicationData                                        *
********************************************************/
struct PublicationData {
	INTEGER datexPublish_SubscribeSerial_nbr;
	INTEGER datexPublish_Serial_nbr;
	BOOLEAN datexPublish_LatePublicationFlag;
	PublicationType *datexPublish_Type;
};
#ifndef STRUC_PublicationData
#define STRUC_PublicationData
typedef struct PublicationData PublicationData;

#endif

ASN1_CPPLINK int ASN1_Print_PublicationData(PublicationData *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_PublicationData_datexPublish_SubscribeSerial_nbr(ASN1WorkSpace *workspace, PublicationData *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_PublicationData_datexPublish_Serial_nbr(ASN1WorkSpace *workspace, PublicationData *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_PublicationData_datexPublish_LatePublicationFlag(ASN1WorkSpace *workspace, PublicationData *value, BOOLEAN user_value);
ASN1_CPPLINK int ASN1_SET_PublicationData_datexPublish_Type(ASN1WorkSpace *workspace, PublicationData *value, PublicationType *user_value);
ASN1_CPPLINK int ASN1_GET_PublicationData_datexPublish_SubscribeSerial_nbr(ASN1WorkSpace *workspace, PublicationData *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_PublicationData_datexPublish_Serial_nbr(ASN1WorkSpace *workspace, PublicationData *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_PublicationData_datexPublish_LatePublicationFlag(ASN1WorkSpace *workspace, PublicationData *value, BOOLEAN *user_value);
ASN1_CPPLINK int ASN1_GET_PublicationData_datexPublish_Type(ASN1WorkSpace *workspace, PublicationData *value, PublicationType **user_value);
ASN1_CPPLINK int ASN1_BER_Enc_PublicationData(ASN1WorkSpace *workspace, PublicationData *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_PublicationData(ASN1WorkSpace *workspace, PublicationData *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_PublicationData(ASN1WorkSpace *workspace, PublicationData *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_PublicationData(ASN1WorkSpace *workspace, PublicationData *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_PublicationData(ASN1WorkSpace *workspace, PublicationData *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_PublicationData(ASN1WorkSpace *workspace, PublicationData *value);

/********************************************************
*Publish_Format_datexPublish_Data                       *
********************************************************/
#ifndef STRUC_Publish_Format_datexPublish_Data
#define STRUC_Publish_Format_datexPublish_Data
typedef ASN1List Publish_Format_datexPublish_Data;
#endif
ASN1_CPPLINK int ASN1_Print_Publish_Format_datexPublish_Data(Publish_Format_datexPublish_Data *value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format_datexPublish_Data *value);

/********************************************************
*Publish_Format                                         *
********************************************************/
struct Publish_Format {
	ASNUINT64 M;
#define DEF_Publish_Format_datexPublish_Data	0
#define DEF_Publish_Format_datexPublish_FileName_txt	1
	union {
		Publish_Format_datexPublish_Data datexPublish_Data;
		UTF8Str datexPublish_FileName_txt;
	} elements;
}; 
#ifndef STRUC_Publish_Format
#define STRUC_Publish_Format
typedef struct Publish_Format Publish_Format;
#endif
ASN1_CPPLINK int ASN1_Print_Publish_Format(Publish_Format *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format *value, Publish_Format_datexPublish_Data *user_value);
ASN1_CPPLINK int ASN1_SET_Publish_Format_datexPublish_FileName_txt(ASN1WorkSpace *workspace, Publish_Format *value, ASNUINT8 *user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_GET_Publish_Format_datexPublish_Data(ASN1WorkSpace *workspace, Publish_Format *value, Publish_Format_datexPublish_Data **user_value);
ASN1_CPPLINK int ASN1_GET_Publish_Format_datexPublish_FileName_txt(ASN1WorkSpace *workspace, Publish_Format *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length);
ASN1_CPPLINK int ASN1_BER_Enc_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_Publish_Format(ASN1WorkSpace *workspace, Publish_Format *value);

/********************************************************
*Publication                                            *
********************************************************/
struct Publication {
	BOOLEAN datexPublish_Guaranteed_bool;
	Publish_Format *datexPublish_Format;
};
#ifndef STRUC_Publication
#define STRUC_Publication
typedef struct Publication Publication;

#endif

ASN1_CPPLINK int ASN1_Print_Publication(Publication *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_Publication_datexPublish_Guaranteed_bool(ASN1WorkSpace *workspace, Publication *value, BOOLEAN user_value);
ASN1_CPPLINK int ASN1_SET_Publication_datexPublish_Format(ASN1WorkSpace *workspace, Publication *value, Publish_Format *user_value);
ASN1_CPPLINK int ASN1_GET_Publication_datexPublish_Guaranteed_bool(ASN1WorkSpace *workspace, Publication *value, BOOLEAN *user_value);
ASN1_CPPLINK int ASN1_GET_Publication_datexPublish_Format(ASN1WorkSpace *workspace, Publication *value, Publish_Format **user_value);
ASN1_CPPLINK int ASN1_BER_Enc_Publication(ASN1WorkSpace *workspace, Publication *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_Publication(ASN1WorkSpace *workspace, Publication *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_Publication(ASN1WorkSpace *workspace, Publication *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_Publication(ASN1WorkSpace *workspace, Publication *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_Publication(ASN1WorkSpace *workspace, Publication *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_Publication(ASN1WorkSpace *workspace, Publication *value);

/********************************************************
*TransferDone                                           *
********************************************************/
struct TransferDone {
	UTF8Str datexTransferDone_FileName_txt;
	BOOLEAN datexTransferDone_Success_bool;
};
#ifndef STRUC_TransferDone
#define STRUC_TransferDone
typedef struct TransferDone TransferDone;

#endif

ASN1_CPPLINK int ASN1_Print_TransferDone(TransferDone *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_TransferDone_datexTransferDone_FileName_txt(ASN1WorkSpace *workspace, TransferDone *value, ASNUINT8 *user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_TransferDone_datexTransferDone_Success_bool(ASN1WorkSpace *workspace, TransferDone *value, BOOLEAN user_value);
ASN1_CPPLINK int ASN1_GET_TransferDone_datexTransferDone_FileName_txt(ASN1WorkSpace *workspace, TransferDone *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length);
ASN1_CPPLINK int ASN1_GET_TransferDone_datexTransferDone_Success_bool(ASN1WorkSpace *workspace, TransferDone *value, BOOLEAN *user_value);
ASN1_CPPLINK int ASN1_BER_Enc_TransferDone(ASN1WorkSpace *workspace, TransferDone *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_TransferDone(ASN1WorkSpace *workspace, TransferDone *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_TransferDone(ASN1WorkSpace *workspace, TransferDone *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_TransferDone(ASN1WorkSpace *workspace, TransferDone *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_TransferDone(ASN1WorkSpace *workspace, TransferDone *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_TransferDone(ASN1WorkSpace *workspace, TransferDone *value);

/********************************************************
*Accept_datexAccept_Type                                *
********************************************************/
struct Accept_datexAccept_Type {
	ASNUINT64 M;
#define DEF_Accept_datexAccept_Type_login	0
#define DEF_Accept_datexAccept_Type_single_subscription	1
#define DEF_Accept_datexAccept_Type_registered_subscription	2
#define DEF_Accept_datexAccept_Type_publication	3
	union {
		OBJECTIDENTIFIER login;
		ASNUINT8 single_subscription;
		INTEGER registered_subscription;
		ASNUINT8 publication;
	} elements;
}; 
#ifndef STRUC_Accept_datexAccept_Type
#define STRUC_Accept_datexAccept_Type
typedef struct Accept_datexAccept_Type Accept_datexAccept_Type;
#endif
ASN1_CPPLINK int ASN1_Print_Accept_datexAccept_Type(Accept_datexAccept_Type *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_Accept_datexAccept_Type_login(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, ASNUINT32 *user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_Accept_datexAccept_Type_single_subscription(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, ASNUINT8 user_value);
ASN1_CPPLINK int ASN1_SET_Accept_datexAccept_Type_registered_subscription(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_Accept_datexAccept_Type_publication(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, ASNUINT8 user_value);
ASN1_CPPLINK int ASN1_GET_Accept_datexAccept_Type_login(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, ASNUINT32 *user_value, ASNUINT32 *user_value_length);
ASN1_CPPLINK int ASN1_GET_Accept_datexAccept_Type_single_subscription(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, ASNUINT8 *user_value);
ASN1_CPPLINK int ASN1_GET_Accept_datexAccept_Type_registered_subscription(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_Accept_datexAccept_Type_publication(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, ASNUINT8 *user_value);
ASN1_CPPLINK int ASN1_BER_Enc_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept_datexAccept_Type *value);

/********************************************************
*Accept                                                 *
********************************************************/
struct Accept {
	INTEGER datexAccept_Packet_nbr;
	Accept_datexAccept_Type *datexAccept_Type;
};
#ifndef STRUC_Accept
#define STRUC_Accept
typedef struct Accept Accept;

#endif

ASN1_CPPLINK int ASN1_Print_Accept(Accept *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_Accept_datexAccept_Packet_nbr(ASN1WorkSpace *workspace, Accept *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept *value, Accept_datexAccept_Type *user_value);
ASN1_CPPLINK int ASN1_GET_Accept_datexAccept_Packet_nbr(ASN1WorkSpace *workspace, Accept *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_Accept_datexAccept_Type(ASN1WorkSpace *workspace, Accept *value, Accept_datexAccept_Type **user_value);
ASN1_CPPLINK int ASN1_BER_Enc_Accept(ASN1WorkSpace *workspace, Accept *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_Accept(ASN1WorkSpace *workspace, Accept *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_Accept(ASN1WorkSpace *workspace, Accept *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_Accept(ASN1WorkSpace *workspace, Accept *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_Accept(ASN1WorkSpace *workspace, Accept *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_Accept(ASN1WorkSpace *workspace, Accept *value);

/********************************************************
*RejectType_datexReject_Login_cd                        *
********************************************************/
#ifndef STRUC_RejectType_datexReject_Login_cd
#define STRUC_RejectType_datexReject_Login_cd
enum RejectType_datexReject_Login_cd {
	RejectType_datexReject_Login_cd_other = 0,
	RejectType_datexReject_Login_cd_unknownDomainName = 1,
	RejectType_datexReject_Login_cd_accessDenied = 2,
	RejectType_datexReject_Login_cd_invalidNamePassword = 3,
	RejectType_datexReject_Login_cd_timeoutTooSmall = 4,
	RejectType_datexReject_Login_cd_timeoutTooLarge = 5,
	RejectType_datexReject_Login_cd_heartbeatTooSmall = 6,
	RejectType_datexReject_Login_cd_heartbeatTooLarge = 7,
	RejectType_datexReject_Login_cd_sessionExists = 8,
	RejectType_datexReject_Login_cd_maxSessionsReached = 9,
};
typedef enum RejectType_datexReject_Login_cd RejectType_datexReject_Login_cd;
#endif

ASN1_CPPLINK int ASN1_Print_RejectType_datexReject_Login_cd(RejectType_datexReject_Login_cd *value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_RejectType_datexReject_Login_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Login_cd *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_RejectType_datexReject_Login_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Login_cd *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_RejectType_datexReject_Login_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Login_cd *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_RejectType_datexReject_Login_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Login_cd *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_RejectType_datexReject_Login_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Login_cd *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_RejectType_datexReject_Login_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Login_cd *value);

/********************************************************
*RejectType_datexReject_Subscription_cd                 *
********************************************************/
#ifndef STRUC_RejectType_datexReject_Subscription_cd
#define STRUC_RejectType_datexReject_Subscription_cd
enum RejectType_datexReject_Subscription_cd {
	RejectType_datexReject_Subscription_cd_other = 0,
	RejectType_datexReject_Subscription_cd_unknownSubscriptionNbr = 1,
	RejectType_datexReject_Subscription_cd_invalidTimes = 2,
	RejectType_datexReject_Subscription_cd_frequencyTooSmall = 3,
	RejectType_datexReject_Subscription_cd_frequencyTooLarge = 4,
	RejectType_datexReject_Subscription_cd_invalid_mode = 5,
	RejectType_datexReject_Subscription_cd_publishFormatNotSupported = 6,
	RejectType_datexReject_Subscription_cd_unknowSubscriptionMsgId = 7,
	RejectType_datexReject_Subscription_cd_invalidSubscriptionMsgId = 8,
	RejectType_datexReject_Subscription_cd_invalidSubscriptionContent = 9,
};
typedef enum RejectType_datexReject_Subscription_cd RejectType_datexReject_Subscription_cd;
#endif

ASN1_CPPLINK int ASN1_Print_RejectType_datexReject_Subscription_cd(RejectType_datexReject_Subscription_cd *value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_RejectType_datexReject_Subscription_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Subscription_cd *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_RejectType_datexReject_Subscription_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Subscription_cd *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_RejectType_datexReject_Subscription_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Subscription_cd *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_RejectType_datexReject_Subscription_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Subscription_cd *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_RejectType_datexReject_Subscription_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Subscription_cd *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_RejectType_datexReject_Subscription_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Subscription_cd *value);

/********************************************************
*RejectType_datexReject_Publication_cd                  *
********************************************************/
#ifndef STRUC_RejectType_datexReject_Publication_cd
#define STRUC_RejectType_datexReject_Publication_cd
enum RejectType_datexReject_Publication_cd {
	RejectType_datexReject_Publication_cd_other = 0,
	RejectType_datexReject_Publication_cd_invalidPublishFormat = 1,
};
typedef enum RejectType_datexReject_Publication_cd RejectType_datexReject_Publication_cd;
#endif

ASN1_CPPLINK int ASN1_Print_RejectType_datexReject_Publication_cd(RejectType_datexReject_Publication_cd *value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_RejectType_datexReject_Publication_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Publication_cd *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_RejectType_datexReject_Publication_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Publication_cd *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_RejectType_datexReject_Publication_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Publication_cd *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_RejectType_datexReject_Publication_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Publication_cd *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_RejectType_datexReject_Publication_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Publication_cd *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_RejectType_datexReject_Publication_cd(ASN1WorkSpace *workspace, RejectType_datexReject_Publication_cd *value);

/********************************************************
*RejectType_rejectPublicationData_datexReject_PublicationData_cd*
********************************************************/
#ifndef STRUC_RejectType_rejectPublicationData_datexReject_PublicationData_cd
#define STRUC_RejectType_rejectPublicationData_datexReject_PublicationData_cd
enum RejectType_rejectPublicationData_datexReject_PublicationData_cd {
	RejectType_rejectPublicationData_datexReject_PublicationData_cd_other = 0,
	RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownSubscription = 1,
	RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownPublicationNbr = 2,
	RejectType_rejectPublicationData_datexReject_PublicationData_cd_unknownPublicationMsgId = 3,
	RejectType_rejectPublicationData_datexReject_PublicationData_cd_invalidPublicationMsgId = 4,
	RejectType_rejectPublicationData_datexReject_PublicationData_cd_invalidPublicationMsgContent = 5,
	RejectType_rejectPublicationData_datexReject_PublicationData_cd_repeatedPublicationNbr = 6,
};
typedef enum RejectType_rejectPublicationData_datexReject_PublicationData_cd RejectType_rejectPublicationData_datexReject_PublicationData_cd;
#endif

ASN1_CPPLINK int ASN1_Print_RejectType_rejectPublicationData_datexReject_PublicationData_cd(RejectType_rejectPublicationData_datexReject_PublicationData_cd *value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_RejectType_rejectPublicationData_datexReject_PublicationData_cd(ASN1WorkSpace *workspace, RejectType_rejectPublicationData_datexReject_PublicationData_cd *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_RejectType_rejectPublicationData_datexReject_PublicationData_cd(ASN1WorkSpace *workspace, RejectType_rejectPublicationData_datexReject_PublicationData_cd *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_RejectType_rejectPublicationData_datexReject_PublicationData_cd(ASN1WorkSpace *workspace, RejectType_rejectPublicationData_datexReject_PublicationData_cd *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_RejectType_rejectPublicationData_datexReject_PublicationData_cd(ASN1WorkSpace *workspace, RejectType_rejectPublicationData_datexReject_PublicationData_cd *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_RejectType_rejectPublicationData_datexReject_PublicationData_cd(ASN1WorkSpace *workspace, RejectType_rejectPublicationData_datexReject_PublicationData_cd *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_RejectType_rejectPublicationData_datexReject_PublicationData_cd(ASN1WorkSpace *workspace, RejectType_rejectPublicationData_datexReject_PublicationData_cd *value);

/********************************************************
*RejectType_rejectPublicationData                       *
********************************************************/
struct RejectType_rejectPublicationData {
	INTEGER datexReject_SubscriptionSerial_nbr;
	INTEGER datexReject_PublicationSerial_nbr;
	enum RejectType_rejectPublicationData_datexReject_PublicationData_cd datexReject_PublicationData_cd;
};
#ifndef STRUC_RejectType_rejectPublicationData
#define STRUC_RejectType_rejectPublicationData
typedef struct RejectType_rejectPublicationData RejectType_rejectPublicationData;

#endif

ASN1_CPPLINK int ASN1_Print_RejectType_rejectPublicationData(RejectType_rejectPublicationData *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_RejectType_rejectPublicationData_datexReject_SubscriptionSerial_nbr(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_RejectType_rejectPublicationData_datexReject_PublicationSerial_nbr(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_RejectType_rejectPublicationData_datexReject_PublicationData_cd(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value, ENUMERATED user_value);
ASN1_CPPLINK int ASN1_GET_RejectType_rejectPublicationData_datexReject_SubscriptionSerial_nbr(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_RejectType_rejectPublicationData_datexReject_PublicationSerial_nbr(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_RejectType_rejectPublicationData_datexReject_PublicationData_cd(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value, ENUMERATED *user_value);
ASN1_CPPLINK int ASN1_BER_Enc_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType_rejectPublicationData *value);

/********************************************************
*RejectType                                             *
********************************************************/
struct RejectType {
	ASNUINT64 M;
#define DEF_RejectType_datexReject_Login_cd	0
#define DEF_RejectType_datexReject_Subscription_cd	1
#define DEF_RejectType_datexReject_Publication_cd	2
#define DEF_RejectType_rejectPublicationData	3
	union {
		enum RejectType_datexReject_Login_cd datexReject_Login_cd;
		enum RejectType_datexReject_Subscription_cd datexReject_Subscription_cd;
		enum RejectType_datexReject_Publication_cd datexReject_Publication_cd;
		RejectType_rejectPublicationData *rejectPublicationData;
	} elements;
}; 
#ifndef STRUC_RejectType
#define STRUC_RejectType
typedef struct RejectType RejectType;
#endif
ASN1_CPPLINK int ASN1_Print_RejectType(RejectType *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_RejectType_datexReject_Login_cd(ASN1WorkSpace *workspace, RejectType *value, ENUMERATED user_value);
ASN1_CPPLINK int ASN1_SET_RejectType_datexReject_Subscription_cd(ASN1WorkSpace *workspace, RejectType *value, ENUMERATED user_value);
ASN1_CPPLINK int ASN1_SET_RejectType_datexReject_Publication_cd(ASN1WorkSpace *workspace, RejectType *value, ENUMERATED user_value);
ASN1_CPPLINK int ASN1_SET_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType *value, RejectType_rejectPublicationData *user_value);
ASN1_CPPLINK int ASN1_GET_RejectType_datexReject_Login_cd(ASN1WorkSpace *workspace, RejectType *value, ENUMERATED *user_value);
ASN1_CPPLINK int ASN1_GET_RejectType_datexReject_Subscription_cd(ASN1WorkSpace *workspace, RejectType *value, ENUMERATED *user_value);
ASN1_CPPLINK int ASN1_GET_RejectType_datexReject_Publication_cd(ASN1WorkSpace *workspace, RejectType *value, ENUMERATED *user_value);
ASN1_CPPLINK int ASN1_GET_RejectType_rejectPublicationData(ASN1WorkSpace *workspace, RejectType *value, RejectType_rejectPublicationData **user_value);
ASN1_CPPLINK int ASN1_BER_Enc_RejectType(ASN1WorkSpace *workspace, RejectType *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_RejectType(ASN1WorkSpace *workspace, RejectType *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_RejectType(ASN1WorkSpace *workspace, RejectType *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_RejectType(ASN1WorkSpace *workspace, RejectType *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_RejectType(ASN1WorkSpace *workspace, RejectType *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_RejectType(ASN1WorkSpace *workspace, RejectType *value);

/********************************************************
*AlternateRequest                                       *
********************************************************/
#ifndef STRUC_AlternateRequest
#define STRUC_AlternateRequest
typedef SubscriptionType AlternateRequest;
#endif

ASN1_CPPLINK int ASN1_Print_AlternateRequest(AlternateRequest *value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_AlternateRequest(ASN1WorkSpace *workspace, AlternateRequest *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_AlternateRequest(ASN1WorkSpace *workspace, AlternateRequest *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_AlternateRequest(ASN1WorkSpace *workspace, AlternateRequest *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_AlternateRequest(ASN1WorkSpace *workspace, AlternateRequest *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_AlternateRequest(ASN1WorkSpace *workspace, AlternateRequest *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_AlternateRequest(ASN1WorkSpace *workspace, AlternateRequest *value);

/********************************************************
*Reject                                                 *
********************************************************/
struct Reject {
	int DEF_Reject_datexReject_AlternateRequest;
	INTEGER datexReject_Packet_nbr;
	RejectType *datexReject_Type;
	AlternateRequest *datexReject_AlternateRequest;	/* optional */
};
#ifndef STRUC_Reject
#define STRUC_Reject
typedef struct Reject Reject;

#endif

ASN1_CPPLINK int ASN1_Print_Reject(Reject *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_Reject_datexReject_Packet_nbr(ASN1WorkSpace *workspace, Reject *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_Reject_datexReject_Type(ASN1WorkSpace *workspace, Reject *value, RejectType *user_value);
ASN1_CPPLINK int ASN1_SET_Reject_datexReject_AlternateRequest(ASN1WorkSpace *workspace, Reject *value, AlternateRequest *user_value);
ASN1_CPPLINK int ASN1_GET_Reject_datexReject_Packet_nbr(ASN1WorkSpace *workspace, Reject *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_Reject_datexReject_Type(ASN1WorkSpace *workspace, Reject *value, RejectType **user_value);
ASN1_CPPLINK int ASN1_GET_Reject_datexReject_AlternateRequest(ASN1WorkSpace *workspace, Reject *value, AlternateRequest **user_value);
ASN1_CPPLINK int ASN1_BER_Enc_Reject(ASN1WorkSpace *workspace, Reject *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_Reject(ASN1WorkSpace *workspace, Reject *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_Reject(ASN1WorkSpace *workspace, Reject *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_Reject(ASN1WorkSpace *workspace, Reject *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_Reject(ASN1WorkSpace *workspace, Reject *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_Reject(ASN1WorkSpace *workspace, Reject *value);

/********************************************************
*PDUs                                                   *
********************************************************/
struct PDUs {
	ASNUINT64 M;
#define DEF_PDUs_datex_Initiate_null	0
#define DEF_PDUs_login	1
#define DEF_PDUs_fred	2
#define DEF_PDUs_terminate	3
#define DEF_PDUs_logout	4
#define DEF_PDUs_subscription	5
#define DEF_PDUs_publication	6
#define DEF_PDUs_transfer_done	7
#define DEF_PDUs_accept	8
#define DEF_PDUs_reject	9
	union {
		Initiate *datex_Initiate_null;
		Login *login;
		FrED fred;
		enum Terminate terminate;
		enum Logout logout;
		Subscription *subscription;
		Publication *publication;
		TransferDone *transfer_done;
		Accept *accept;
		Reject *reject;
	} elements;
}; 
#ifndef STRUC_PDUs
#define STRUC_PDUs
typedef struct PDUs PDUs;
#endif
ASN1_CPPLINK int ASN1_Print_PDUs(PDUs *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_PDUs_datex_Initiate_null(ASN1WorkSpace *workspace, PDUs *value, Initiate *user_value);
ASN1_CPPLINK int ASN1_SET_PDUs_login(ASN1WorkSpace *workspace, PDUs *value, Login *user_value);
ASN1_CPPLINK int ASN1_SET_PDUs_fred(ASN1WorkSpace *workspace, PDUs *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_PDUs_terminate(ASN1WorkSpace *workspace, PDUs *value, ENUMERATED user_value);
ASN1_CPPLINK int ASN1_SET_PDUs_logout(ASN1WorkSpace *workspace, PDUs *value, ENUMERATED user_value);
ASN1_CPPLINK int ASN1_SET_PDUs_subscription(ASN1WorkSpace *workspace, PDUs *value, Subscription *user_value);
ASN1_CPPLINK int ASN1_SET_PDUs_publication(ASN1WorkSpace *workspace, PDUs *value, Publication *user_value);
ASN1_CPPLINK int ASN1_SET_PDUs_transfer_done(ASN1WorkSpace *workspace, PDUs *value, TransferDone *user_value);
ASN1_CPPLINK int ASN1_SET_PDUs_accept(ASN1WorkSpace *workspace, PDUs *value, Accept *user_value);
ASN1_CPPLINK int ASN1_SET_PDUs_reject(ASN1WorkSpace *workspace, PDUs *value, Reject *user_value);
ASN1_CPPLINK int ASN1_GET_PDUs_datex_Initiate_null(ASN1WorkSpace *workspace, PDUs *value, Initiate **user_value);
ASN1_CPPLINK int ASN1_GET_PDUs_login(ASN1WorkSpace *workspace, PDUs *value, Login **user_value);
ASN1_CPPLINK int ASN1_GET_PDUs_fred(ASN1WorkSpace *workspace, PDUs *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_PDUs_terminate(ASN1WorkSpace *workspace, PDUs *value, ENUMERATED *user_value);
ASN1_CPPLINK int ASN1_GET_PDUs_logout(ASN1WorkSpace *workspace, PDUs *value, ENUMERATED *user_value);
ASN1_CPPLINK int ASN1_GET_PDUs_subscription(ASN1WorkSpace *workspace, PDUs *value, Subscription **user_value);
ASN1_CPPLINK int ASN1_GET_PDUs_publication(ASN1WorkSpace *workspace, PDUs *value, Publication **user_value);
ASN1_CPPLINK int ASN1_GET_PDUs_transfer_done(ASN1WorkSpace *workspace, PDUs *value, TransferDone **user_value);
ASN1_CPPLINK int ASN1_GET_PDUs_accept(ASN1WorkSpace *workspace, PDUs *value, Accept **user_value);
ASN1_CPPLINK int ASN1_GET_PDUs_reject(ASN1WorkSpace *workspace, PDUs *value, Reject **user_value);
ASN1_CPPLINK int ASN1_BER_Enc_PDUs(ASN1WorkSpace *workspace, PDUs *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_PDUs(ASN1WorkSpace *workspace, PDUs *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_PDUs(ASN1WorkSpace *workspace, PDUs *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_PDUs(ASN1WorkSpace *workspace, PDUs *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_PDUs(ASN1WorkSpace *workspace, PDUs *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_PDUs(ASN1WorkSpace *workspace, PDUs *value);

/********************************************************
*C2CAuthenticatedMessage                                *
********************************************************/
struct C2CAuthenticatedMessage {
	OCTETSTRING datex_AuthenticationInfo_text;
	INTEGER datex_DataPacket_number;
	INTEGER datex_DataPacketPriority_number;
	HeaderOptions *options;
	PDUs *pdu;
};
#ifndef STRUC_C2CAuthenticatedMessage
#define STRUC_C2CAuthenticatedMessage
typedef struct C2CAuthenticatedMessage C2CAuthenticatedMessage;

#endif

ASN1_CPPLINK int ASN1_Print_C2CAuthenticatedMessage(C2CAuthenticatedMessage *value, int tab_value);
ASN1_CPPLINK int ASN1_SET_C2CAuthenticatedMessage_datex_AuthenticationInfo_text(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, ASNUINT8 *user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_C2CAuthenticatedMessage_datex_DataPacket_number(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_C2CAuthenticatedMessage_datex_DataPacketPriority_number(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_C2CAuthenticatedMessage_options(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, HeaderOptions *user_value);
ASN1_CPPLINK int ASN1_SET_C2CAuthenticatedMessage_pdu(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, PDUs *user_value);
ASN1_CPPLINK int ASN1_GET_C2CAuthenticatedMessage_datex_AuthenticationInfo_text(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length);
ASN1_CPPLINK int ASN1_GET_C2CAuthenticatedMessage_datex_DataPacket_number(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_C2CAuthenticatedMessage_datex_DataPacketPriority_number(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_C2CAuthenticatedMessage_options(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, HeaderOptions **user_value);
ASN1_CPPLINK int ASN1_GET_C2CAuthenticatedMessage_pdu(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, PDUs **user_value);
ASN1_CPPLINK int ASN1_BER_Enc_C2CAuthenticatedMessage(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_C2CAuthenticatedMessage(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value, int length, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_PER_Align_Enc_C2CAuthenticatedMessage(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value);
ASN1_CPPLINK int ASN1_PER_Align_Dec_C2CAuthenticatedMessage(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Enc_C2CAuthenticatedMessage(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value);
ASN1_CPPLINK int ASN1_PER_UNAlign_Dec_C2CAuthenticatedMessage(ASN1WorkSpace *workspace, C2CAuthenticatedMessage *value);

#endif

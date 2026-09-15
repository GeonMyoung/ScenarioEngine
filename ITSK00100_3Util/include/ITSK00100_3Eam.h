#ifndef _ITSK00100_3_EAM_H_
#define _ITSK00100_3_EAM_H_

#include "BER/ASN1bersrc.h"
#include "IO/ASN1IO.h"
#include "MEM/mpool.h"
#include "OS/ASN1_Sys.h"
#include "TOOL/ASN1Tool.h"
#include "TYPE/ASN1_Type.h"



/********************************************************
*ObjectID_00100                                         *
********************************************************/
#ifndef STRUC_ObjectID_00100
#define STRUC_ObjectID_00100
typedef INTEGER ObjectID_00100;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_ObjectID_00100(ASN1WorkSpace *workspace, ObjectID_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_ObjectID_00100(ASN1WorkSpace *workspace, ObjectID_00100 *value, int length, ASN1TagType tagFlag);

/********************************************************
*DYear_00100                                            *
********************************************************/
#ifndef STRUC_DYear_00100
#define STRUC_DYear_00100
typedef INTEGER DYear_00100;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_DYear_00100(ASN1WorkSpace *workspace, DYear_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_DYear_00100(ASN1WorkSpace *workspace, DYear_00100 *value, int length, ASN1TagType tagFlag);

/********************************************************
*DDay_00100                                             *
********************************************************/
#ifndef STRUC_DDay_00100
#define STRUC_DDay_00100
typedef INTEGER DDay_00100;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_DDay_00100(ASN1WorkSpace *workspace, DDay_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_DDay_00100(ASN1WorkSpace *workspace, DDay_00100 *value, int length, ASN1TagType tagFlag);

/********************************************************
*DHour_00100                                            *
********************************************************/
#ifndef STRUC_DHour_00100
#define STRUC_DHour_00100
typedef INTEGER DHour_00100;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_DHour_00100(ASN1WorkSpace *workspace, DHour_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_DHour_00100(ASN1WorkSpace *workspace, DHour_00100 *value, int length, ASN1TagType tagFlag);

/********************************************************
*DMinute_00100                                          *
********************************************************/
#ifndef STRUC_DMinute_00100
#define STRUC_DMinute_00100
typedef INTEGER DMinute_00100;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_DMinute_00100(ASN1WorkSpace *workspace, DMinute_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_DMinute_00100(ASN1WorkSpace *workspace, DMinute_00100 *value, int length, ASN1TagType tagFlag);

/********************************************************
*DMonth_00100                                           *
********************************************************/
#ifndef STRUC_DMonth_00100
#define STRUC_DMonth_00100
typedef INTEGER DMonth_00100;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_DMonth_00100(ASN1WorkSpace *workspace, DMonth_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_DMonth_00100(ASN1WorkSpace *workspace, DMonth_00100 *value, int length, ASN1TagType tagFlag);

/********************************************************
*DOffset_00100                                          *
********************************************************/
#ifndef STRUC_DOffset_00100
#define STRUC_DOffset_00100
typedef INTEGER DOffset_00100;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_DOffset_00100(ASN1WorkSpace *workspace, DOffset_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_DOffset_00100(ASN1WorkSpace *workspace, DOffset_00100 *value, int length, ASN1TagType tagFlag);

/********************************************************
*DSecond_00100                                          *
********************************************************/
#ifndef STRUC_DSecond_00100
#define STRUC_DSecond_00100
typedef INTEGER DSecond_00100;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_DSecond_00100(ASN1WorkSpace *workspace, DSecond_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_DSecond_00100(ASN1WorkSpace *workspace, DSecond_00100 *value, int length, ASN1TagType tagFlag);

/********************************************************
*DDateTime_00100                                        *
********************************************************/
#ifndef STRUC_DYear_00100
#define STRUC_DYear_00100
typedef INTEGER DYear_00100;
#endif
#ifndef STRUC_DMonth_00100
#define STRUC_DMonth_00100
typedef INTEGER DMonth_00100;
#endif
#ifndef STRUC_DDay_00100
#define STRUC_DDay_00100
typedef INTEGER DDay_00100;
#endif
#ifndef STRUC_DHour_00100
#define STRUC_DHour_00100
typedef INTEGER DHour_00100;
#endif
#ifndef STRUC_DMinute_00100
#define STRUC_DMinute_00100
typedef INTEGER DMinute_00100;
#endif
#ifndef STRUC_DSecond_00100
#define STRUC_DSecond_00100
typedef INTEGER DSecond_00100;
#endif
#ifndef STRUC_DOffset_00100
#define STRUC_DOffset_00100
typedef INTEGER DOffset_00100;
#endif
struct DDateTime_00100 {
	int DEF_DDateTime_00100_year;
	int DEF_DDateTime_00100_month;
	int DEF_DDateTime_00100_day;
	int DEF_DDateTime_00100_hour;
	int DEF_DDateTime_00100_minute;
	int DEF_DDateTime_00100_second;
	int DEF_DDateTime_00100_offset;
	DYear_00100 year;/* optional */
	DMonth_00100 month;/* optional */
	DDay_00100 day;/* optional */
	DHour_00100 hour;/* optional */
	DMinute_00100 minute;/* optional */
	DSecond_00100 second;/* optional */
	DOffset_00100 offset;/* optional */
};
#ifndef STRUC_DDateTime_00100
#define STRUC_DDateTime_00100
typedef struct DDateTime_00100 DDateTime_00100;

#endif

ASN1_CPPLINK int ASN1_GET_DDateTime_00100_year(ASN1WorkSpace *workspace, DDateTime_00100 *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_DDateTime_00100_month(ASN1WorkSpace *workspace, DDateTime_00100 *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_DDateTime_00100_day(ASN1WorkSpace *workspace, DDateTime_00100 *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_DDateTime_00100_hour(ASN1WorkSpace *workspace, DDateTime_00100 *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_DDateTime_00100_minute(ASN1WorkSpace *workspace, DDateTime_00100 *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_DDateTime_00100_second(ASN1WorkSpace *workspace, DDateTime_00100 *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_DDateTime_00100_offset(ASN1WorkSpace *workspace, DDateTime_00100 *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_BER_Enc_DDateTime_00100(ASN1WorkSpace *workspace, DDateTime_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_DDateTime_00100(ASN1WorkSpace *workspace, DDateTime_00100 *value, int length, ASN1TagType tagFlag);

/********************************************************
*Longitude_00100                                        *
********************************************************/
#ifndef STRUC_Longitude_00100
#define STRUC_Longitude_00100
typedef INTEGER Longitude_00100;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_Longitude_00100(ASN1WorkSpace *workspace, Longitude_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_Longitude_00100(ASN1WorkSpace *workspace, Longitude_00100 *value, int length, ASN1TagType tagFlag);

/********************************************************
*Latitude_00100                                         *
********************************************************/
#ifndef STRUC_Latitude_00100
#define STRUC_Latitude_00100
typedef INTEGER Latitude_00100;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_Latitude_00100(ASN1WorkSpace *workspace, Latitude_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_Latitude_00100(ASN1WorkSpace *workspace, Latitude_00100 *value, int length, ASN1TagType tagFlag);

/********************************************************
*Elevation_00100                                        *
********************************************************/
#ifndef STRUC_Elevation_00100
#define STRUC_Elevation_00100
typedef INTEGER Elevation_00100;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_Elevation_00100(ASN1WorkSpace *workspace, Elevation_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_Elevation_00100(ASN1WorkSpace *workspace, Elevation_00100 *value, int length, ASN1TagType tagFlag);


/********************************************************
*TransmissionState_00100                                *
********************************************************/
enum TransmissionState_00100 {
	TransmissionState_00100_neutral = 0,
	TransmissionState_00100_park = 1,
	TransmissionState_00100_forwardGears = 2,
	TransmissionState_00100_reverseGears = 3,
	TransmissionState_00100_reserved1 = 4,
	TransmissionState_00100_reserved2 = 5,
	TransmissionState_00100_reserved3 = 6,
	TransmissionState_00100_unavailable = 7,
};
#ifndef STRUC_TransmissionState_00100
#define STRUC_TransmissionState_00100
typedef enum TransmissionState_00100 TransmissionState_00100;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_TransmissionState_00100(ASN1WorkSpace* workspace, TransmissionState_00100* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_TransmissionState_00100(ASN1WorkSpace* workspace, TransmissionState_00100* value, int length, ASN1TagType tagFlag);


/********************************************************
*TransmissionAndSpeed_00100                             *
********************************************************/
#ifndef STRUC_TransmissionState_00100
#define STRUC_TransmissionState_00100
typedef enum TransmissionState_00100;
#endif
#ifndef STRUC_Velocity_00100
#define STRUC_Velocity_00100
typedef INTEGER Velocity_00100;
#endif
struct TransmissionAndSpeed_00100 {
	TransmissionState_00100 transmisson;
	Velocity_00100 speed;
};
#ifndef STRUC_TransmissionAndSpeed_00100
#define STRUC_TransmissionAndSpeed_00100
typedef struct TransmissionAndSpeed_00100 TransmissionAndSpeed_00100;

#endif

ASN1_CPPLINK int ASN1_GET_TransmissionAndSpeed_00100_transmisson(ASN1WorkSpace *workspace, TransmissionAndSpeed_00100 *value, ENUMERATED *user_value);
ASN1_CPPLINK int ASN1_GET_TransmissionAndSpeed_00100_speed(ASN1WorkSpace *workspace, TransmissionAndSpeed_00100 *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_BER_Enc_TransmissionAndSpeed_00100(ASN1WorkSpace *workspace, TransmissionAndSpeed_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_TransmissionAndSpeed_00100(ASN1WorkSpace *workspace, TransmissionAndSpeed_00100 *value, int length, ASN1TagType tagFlag);

/********************************************************
*Velocity_00100                                         *
********************************************************/
#ifndef STRUC_Velocity_00100
#define STRUC_Velocity_00100
typedef INTEGER Velocity_00100;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_Velocity_00100(ASN1WorkSpace *workspace, Velocity_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_Velocity_00100(ASN1WorkSpace *workspace, Velocity_00100 *value, int length, ASN1TagType tagFlag);

/********************************************************
*Heading_00100                                          *
********************************************************/
#ifndef STRUC_Heading_00100
#define STRUC_Heading_00100
typedef INTEGER Heading_00100;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_Heading_00100(ASN1WorkSpace *workspace, Heading_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_Heading_00100(ASN1WorkSpace *workspace, Heading_00100 *value, int length, ASN1TagType tagFlag);

/********************************************************
*PositionalAccuracy_00100                               *
********************************************************/
#ifndef STRUC_SemiMajorAxisAccuracy_00100
#define STRUC_SemiMajorAxisAccuracy_00100
typedef INTEGER SemiMajorAxisAccuracy_00100;
#endif
#ifndef STRUC_SemiMinorAxisAccuracy_00100
#define STRUC_SemiMinorAxisAccuracy_00100
typedef INTEGER SemiMinorAxisAccuracy_00100;
#endif
#ifndef STRUC_SemiMajorAxisOrientation_00100
#define STRUC_SemiMajorAxisOrientation_00100
typedef INTEGER SemiMajorAxisOrientation_00100;
#endif
struct PositionalAccuracy_00100 {
	SemiMajorAxisAccuracy_00100 semiMajor;
	SemiMinorAxisAccuracy_00100 semiMinor;
	SemiMajorAxisOrientation_00100 orientation;
};
#ifndef STRUC_PositionalAccuracy_00100
#define STRUC_PositionalAccuracy_00100
typedef struct PositionalAccuracy_00100 PositionalAccuracy_00100;

#endif

ASN1_CPPLINK int ASN1_GET_PositionalAccuracy_00100_semiMajor(ASN1WorkSpace *workspace, PositionalAccuracy_00100 *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_PositionalAccuracy_00100_semiMinor(ASN1WorkSpace *workspace, PositionalAccuracy_00100 *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_PositionalAccuracy_00100_orientation(ASN1WorkSpace *workspace, PositionalAccuracy_00100 *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_BER_Enc_PositionalAccuracy_00100(ASN1WorkSpace *workspace, PositionalAccuracy_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_PositionalAccuracy_00100(ASN1WorkSpace *workspace, PositionalAccuracy_00100 *value, int length, ASN1TagType tagFlag);

/********************************************************
*SemiMajorAxisAccuracy_00100                            *
********************************************************/
#ifndef STRUC_SemiMajorAxisAccuracy_00100
#define STRUC_SemiMajorAxisAccuracy_00100
typedef INTEGER SemiMajorAxisAccuracy_00100;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_SemiMajorAxisAccuracy_00100(ASN1WorkSpace *workspace, SemiMajorAxisAccuracy_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_SemiMajorAxisAccuracy_00100(ASN1WorkSpace *workspace, SemiMajorAxisAccuracy_00100 *value, int length, ASN1TagType tagFlag);

/********************************************************
*SemiMajorAxisOrientation_00100                         *
********************************************************/
#ifndef STRUC_SemiMajorAxisOrientation_00100
#define STRUC_SemiMajorAxisOrientation_00100
typedef INTEGER SemiMajorAxisOrientation_00100;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_SemiMajorAxisOrientation_00100(ASN1WorkSpace *workspace, SemiMajorAxisOrientation_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_SemiMajorAxisOrientation_00100(ASN1WorkSpace *workspace, SemiMajorAxisOrientation_00100 *value, int length, ASN1TagType tagFlag);

/********************************************************
*SemiMinorAxisAccuracy_00100                            *
********************************************************/
#ifndef STRUC_SemiMinorAxisAccuracy_00100
#define STRUC_SemiMinorAxisAccuracy_00100
typedef INTEGER SemiMinorAxisAccuracy_00100;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_SemiMinorAxisAccuracy_00100(ASN1WorkSpace *workspace, SemiMinorAxisAccuracy_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_SemiMinorAxisAccuracy_00100(ASN1WorkSpace *workspace, SemiMinorAxisAccuracy_00100 *value, int length, ASN1TagType tagFlag);

/********************************************************
*TimeConfidence_00100                                   *
********************************************************/
enum TimeConfidence_00100 {
	TimeConfidence_00100_unavailable = 0,
	TimeConfidence_00100_time_100_000 = 1,
	TimeConfidence_00100_time_050_000 = 2,
	TimeConfidence_00100_time_020_000 = 3,
	TimeConfidence_00100_time_010_000 = 4,
	TimeConfidence_00100_time_002_000 = 5,
	TimeConfidence_00100_time_001_000 = 6,
	TimeConfidence_00100_time_000_500 = 7,
	TimeConfidence_00100_time_000_200 = 8,
	TimeConfidence_00100_time_000_100 = 9,
	TimeConfidence_00100_time_000_050 = 10,
	TimeConfidence_00100_time_000_020 = 11,
	TimeConfidence_00100_time_000_010 = 12,
	TimeConfidence_00100_time_000_005 = 13,
	TimeConfidence_00100_time_000_002 = 14,
	TimeConfidence_00100_time_000_001 = 15,
	TimeConfidence_00100_time_000_000_5 = 16,
	TimeConfidence_00100_time_000_000_2 = 17,
	TimeConfidence_00100_time_000_000_1 = 18,
	TimeConfidence_00100_time_000_000_05 = 19,
	TimeConfidence_00100_time_000_000_02 = 20,
	TimeConfidence_00100_time_000_000_01 = 21,
	TimeConfidence_00100_time_000_000_005 = 22,
	TimeConfidence_00100_time_000_000_002 = 23,
	TimeConfidence_00100_time_000_000_001 = 24,
	TimeConfidence_00100_time_000_000_000_5 = 25,
	TimeConfidence_00100_time_000_000_000_2 = 26,
	TimeConfidence_00100_time_000_000_000_1 = 27,
	TimeConfidence_00100_time_000_000_000_05 = 28,
	TimeConfidence_00100_time_000_000_000_02 = 29,
	TimeConfidence_00100_time_000_000_000_01 = 30,
	TimeConfidence_00100_time_000_000_000_005 = 31,
	TimeConfidence_00100_time_000_000_000_002 = 32,
	TimeConfidence_00100_time_000_000_000_001 = 33,
	TimeConfidence_00100_time_000_000_000_000_5 = 34,
	TimeConfidence_00100_time_000_000_000_000_2 = 35,
	TimeConfidence_00100_time_000_000_000_000_1 = 36,
	TimeConfidence_00100_time_000_000_000_000_05 = 37,
	TimeConfidence_00100_time_000_000_000_000_02 = 38,
	TimeConfidence_00100_time_000_000_000_000_01 = 39,
};
#ifndef STRUC_TimeConfidence_00100
#define STRUC_TimeConfidence_00100
typedef enum TimeConfidence_00100 TimeConfidence_00100;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_TimeConfidence_00100(ASN1WorkSpace *workspace, TimeConfidence_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_TimeConfidence_00100(ASN1WorkSpace *workspace, TimeConfidence_00100 *value, int length, ASN1TagType tagFlag);


/********************************************************
*ElevationConfidence_00100                              *
********************************************************/
enum ElevationConfidence_00100 {
	ElevationConfidence_00100_unavailable = 0,
	ElevationConfidence_00100_elev_500_00 = 1,
	ElevationConfidence_00100_elev_200_00 = 2,
	ElevationConfidence_00100_elev_100_00 = 3,
	ElevationConfidence_00100_elev_050_00 = 4,
	ElevationConfidence_00100_elev_020_00 = 5,
	ElevationConfidence_00100_elev_010_00 = 6,
	ElevationConfidence_00100_elev_005_00 = 7,
	ElevationConfidence_00100_elev_002_00 = 8,
	ElevationConfidence_00100_elev_001_00 = 9,
	ElevationConfidence_00100_elev_000_50 = 10,
	ElevationConfidence_00100_elev_000_20 = 11,
	ElevationConfidence_00100_elev_000_10 = 12,
	ElevationConfidence_00100_elev_000_05 = 13,
	ElevationConfidence_00100_elev_000_02 = 14,
	ElevationConfidence_00100_elev_000_01 = 15,
};
#ifndef STRUC_ElevationConfidence_00100
#define STRUC_ElevationConfidence_00100
typedef enum ElevationConfidence_00100 ElevationConfidence_00100;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_ElevationConfidence_00100(ASN1WorkSpace *workspace, ElevationConfidence_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_ElevationConfidence_00100(ASN1WorkSpace *workspace, ElevationConfidence_00100 *value, int length, ASN1TagType tagFlag);

/********************************************************
*PositionConfidence_00100                               *
********************************************************/
enum PositionConfidence_00100 {
	PositionConfidence_00100_unavailable = 0,
	PositionConfidence_00100_a500m = 1,
	PositionConfidence_00100_a200m = 2,
	PositionConfidence_00100_a100m = 3,
	PositionConfidence_00100_a50m = 4,
	PositionConfidence_00100_a20m = 5,
	PositionConfidence_00100_a10m = 6,
	PositionConfidence_00100_a5m = 7,
	PositionConfidence_00100_a2m = 8,
	PositionConfidence_00100_a1m = 9,
	PositionConfidence_00100_a50cm = 10,
	PositionConfidence_00100_a20cm = 11,
	PositionConfidence_00100_a10cm = 12,
	PositionConfidence_00100_a5cm = 13,
	PositionConfidence_00100_a2cm = 14,
	PositionConfidence_00100_a1cm = 15,
};
#ifndef STRUC_PositionConfidence_00100
#define STRUC_PositionConfidence_00100
typedef enum PositionConfidence_00100 PositionConfidence_00100;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_PositionConfidence_00100(ASN1WorkSpace *workspace, PositionConfidence_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_PositionConfidence_00100(ASN1WorkSpace *workspace, PositionConfidence_00100 *value, int length, ASN1TagType tagFlag);

/********************************************************
*PositionConfidenceSet_00100                            *
********************************************************/
#ifndef STRUC_PositionConfidence_00100
#define STRUC_PositionConfidence_00100
typedef enum PositionConfidence_00100;
#endif
#ifndef STRUC_ElevationConfidence_00100
#define STRUC_ElevationConfidence_00100
typedef enum ElevationConfidence_00100;
#endif
struct PositionConfidenceSet_00100 {
	PositionConfidence_00100 pos;
	ElevationConfidence_00100 elevation;
};
#ifndef STRUC_PositionConfidenceSet_00100
#define STRUC_PositionConfidenceSet_00100
typedef struct PositionConfidenceSet_00100 PositionConfidenceSet_00100;

#endif

ASN1_CPPLINK int ASN1_GET_PositionConfidenceSet_00100_pos(ASN1WorkSpace* workspace, PositionConfidenceSet_00100* value, ENUMERATED* user_value);
ASN1_CPPLINK int ASN1_GET_PositionConfidenceSet_00100_elevation(ASN1WorkSpace* workspace, PositionConfidenceSet_00100* value, ENUMERATED* user_value);
ASN1_CPPLINK int ASN1_BER_Enc_PositionConfidenceSet_00100(ASN1WorkSpace* workspace, PositionConfidenceSet_00100* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_PositionConfidenceSet_00100(ASN1WorkSpace* workspace, PositionConfidenceSet_00100* value, int length, ASN1TagType tagFlag);



/********************************************************
*HeadingConfidence_00100                                *
********************************************************/
enum HeadingConfidence_00100 {
	HeadingConfidence_00100_unavailable = 0,
	HeadingConfidence_00100_prec10deg = 1,
	HeadingConfidence_00100_prec05deg = 2,
	HeadingConfidence_00100_prec01deg = 3,
	HeadingConfidence_00100_prec0_1deg = 4,
	HeadingConfidence_00100_prec0_05deg = 5,
	HeadingConfidence_00100_prec0_01deg = 6,
	HeadingConfidence_00100_prec0_0125deg = 7,
};
#ifndef STRUC_HeadingConfidence_00100
#define STRUC_HeadingConfidence_00100
typedef enum HeadingConfidence_00100 HeadingConfidence_00100;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_HeadingConfidence_00100(ASN1WorkSpace *workspace, HeadingConfidence_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_HeadingConfidence_00100(ASN1WorkSpace *workspace, HeadingConfidence_00100 *value, int length, ASN1TagType tagFlag);

/********************************************************
*SpeedConfidence_00100                                  *
********************************************************/
enum SpeedConfidence_00100 {
	SpeedConfidence_00100_unavailable = 0,
	SpeedConfidence_00100_prec100ms = 1,
	SpeedConfidence_00100_prec10ms = 2,
	SpeedConfidence_00100_prec5ms = 3,
	SpeedConfidence_00100_prec1ms = 4,
	SpeedConfidence_00100_prec0_1ms = 5,
	SpeedConfidence_00100_prec0_05ms = 6,
	SpeedConfidence_00100_prec0_01ms = 7,
};
#ifndef STRUC_SpeedConfidence_00100
#define STRUC_SpeedConfidence_00100
typedef enum SpeedConfidence_00100 SpeedConfidence_00100;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_SpeedConfidence_00100(ASN1WorkSpace *workspace, SpeedConfidence_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_SpeedConfidence_00100(ASN1WorkSpace *workspace, SpeedConfidence_00100 *value, int length, ASN1TagType tagFlag);

/********************************************************
*ThrottleConfidence_00100                               *
********************************************************/
enum ThrottleConfidence_00100 {
	ThrottleConfidence_00100_unavailable = 0,
	ThrottleConfidence_00100_prec10percent = 1,
	ThrottleConfidence_00100_prec1percent = 2,
	ThrottleConfidence_00100_prec0_5percent = 3,
};
#ifndef STRUC_ThrottleConfidence_00100
#define STRUC_ThrottleConfidence_00100
typedef enum ThrottleConfidence_00100 ThrottleConfidence_00100;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_ThrottleConfidence_00100(ASN1WorkSpace *workspace, ThrottleConfidence_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_ThrottleConfidence_00100(ASN1WorkSpace *workspace, ThrottleConfidence_00100 *value, int length, ASN1TagType tagFlag);

/********************************************************
*SpeedandHeadingandThrottleConfidence_00100             *
********************************************************/
#ifndef STRUC_HeadingConfidence_00100
#define STRUC_HeadingConfidence_00100
typedef enum HeadingConfidence_00100;
#endif
#ifndef STRUC_SpeedConfidence_00100
#define STRUC_SpeedConfidence_00100
typedef enum SpeedConfidence_00100;
#endif
#ifndef STRUC_ThrottleConfidence_00100
#define STRUC_ThrottleConfidence_00100
typedef enum ThrottleConfidence_00100;
#endif
struct SpeedandHeadingandThrottleConfidence_00100 {
	HeadingConfidence_00100 heading;
	SpeedConfidence_00100 speed;
	ThrottleConfidence_00100 throttle;
};
#ifndef STRUC_SpeedandHeadingandThrottleConfidence_00100
#define STRUC_SpeedandHeadingandThrottleConfidence_00100
typedef struct SpeedandHeadingandThrottleConfidence_00100 SpeedandHeadingandThrottleConfidence_00100;

#endif

ASN1_CPPLINK int ASN1_GET_SpeedandHeadingandThrottleConfidence_00100_heading(ASN1WorkSpace* workspace, SpeedandHeadingandThrottleConfidence_00100* value, ENUMERATED* user_value);
ASN1_CPPLINK int ASN1_GET_SpeedandHeadingandThrottleConfidence_00100_speed(ASN1WorkSpace* workspace, SpeedandHeadingandThrottleConfidence_00100* value, ENUMERATED* user_value);
ASN1_CPPLINK int ASN1_GET_SpeedandHeadingandThrottleConfidence_00100_throttle(ASN1WorkSpace* workspace, SpeedandHeadingandThrottleConfidence_00100* value, ENUMERATED* user_value);
ASN1_CPPLINK int ASN1_BER_Enc_SpeedandHeadingandThrottleConfidence_00100(ASN1WorkSpace* workspace, SpeedandHeadingandThrottleConfidence_00100* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_SpeedandHeadingandThrottleConfidence_00100(ASN1WorkSpace* workspace, SpeedandHeadingandThrottleConfidence_00100* value, int length, ASN1TagType tagFlag);


/********************************************************
*FullPositionVector_00100                               *
********************************************************/

#ifndef STRUC_DDateTime_00100
#define STRUC_DDateTime_00100
typedef struct DDateTime_00100 DDateTime_00100;
#endif
#ifndef STRUC_Longitude_00100
#define STRUC_Longitude_00100
typedef INTEGER Longitude_00100;
#endif
#ifndef STRUC_Latitude_00100
#define STRUC_Latitude_00100
typedef INTEGER Latitude_00100;
#endif
#ifndef STRUC_Elevation_00100
#define STRUC_Elevation_00100
typedef INTEGER Elevation_00100;
#endif
#ifndef STRUC_Heading_00100
#define STRUC_Heading_00100
typedef INTEGER Heading_00100;
#endif

#ifndef STRUC_TransmissionAndSpeed_00100
#define STRUC_TransmissionAndSpeed_00100
typedef struct TransmissionAndSpeed_00100 TransmissionAndSpeed_00100;
#endif

#ifndef STRUC_PositionalAccuracy_00100
#define STRUC_PositionalAccuracy_00100
typedef struct PositionalAccuracy_00100 PositionalAccuracy_00100;
#endif
#ifndef STRUC_TimeConfidence_00100
#define STRUC_TimeConfidence_00100
typedef enum TimeConfidence_00100;
#endif

#ifndef STRUC_PositionConfidenceSet_00100
#define STRUC_PositionConfidenceSet_00100
typedef struct PositionConfidenceSet_00100 PositionConfidenceSet_00100;
#endif

#ifndef STRUC_SpeedandHeadingandThrottleConfidence_00100
#define STRUC_SpeedandHeadingandThrottleConfidence_00100
typedef struct SpeedandHeadingandThrottleConfidence_00100 SpeedandHeadingandThrottleConfidence_00100;
#endif
struct FullPositionVector_00100 {
	int DEF_FullPositionVector_00100_utcTime;
	int DEF_FullPositionVector_00100_elevation;
	int DEF_FullPositionVector_00100_heading;
	int DEF_FullPositionVector_00100_speed;
	int DEF_FullPositionVector_00100_posAccuracy;
	int DEF_FullPositionVector_00100_timeConfidence;
	int DEF_FullPositionVector_00100_posConfidence;
	int DEF_FullPositionVector_00100_speedConfidence;
	DDateTime_00100 *utcTime;/* optional */
	Longitude_00100 lon;
	Latitude_00100 lat;
	Elevation_00100 elevation;/* optional */
	Heading_00100 heading;/* optional */
	TransmissionAndSpeed_00100 *speed;/* optional */
	PositionalAccuracy_00100 *posAccuracy;/* optional */
	TimeConfidence_00100 timeConfidence;/* optional */
	PositionConfidenceSet_00100 *posConfidence;/* optional */
	SpeedandHeadingandThrottleConfidence_00100 *speedConfidence;/* optional */
	ASNUINT64 E;
};
#ifndef STRUC_FullPositionVector_00100
#define STRUC_FullPositionVector_00100
typedef struct FullPositionVector_00100 FullPositionVector_00100;

#endif

ASN1_CPPLINK int ASN1_GET_FullPositionVector_00100_utcTime(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, DDateTime_00100 **user_value);
ASN1_CPPLINK int ASN1_GET_FullPositionVector_00100_lon(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_FullPositionVector_00100_lat(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_FullPositionVector_00100_elevation(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_FullPositionVector_00100_heading(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_FullPositionVector_00100_speed(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, TransmissionAndSpeed_00100 **user_value);
ASN1_CPPLINK int ASN1_GET_FullPositionVector_00100_posAccuracy(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, PositionalAccuracy_00100 **user_value);
ASN1_CPPLINK int ASN1_GET_FullPositionVector_00100_timeConfidence(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, ENUMERATED *user_value);
ASN1_CPPLINK int ASN1_GET_FullPositionVector_00100_posConfidence(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, PositionConfidenceSet_00100 **user_value);
ASN1_CPPLINK int ASN1_GET_FullPositionVector_00100_speedConfidence(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, SpeedandHeadingandThrottleConfidence_00100 **user_value);
ASN1_CPPLINK int ASN1_BER_Enc_FullPositionVector_00100(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_FullPositionVector_00100(ASN1WorkSpace *workspace, FullPositionVector_00100 *value, int length, ASN1TagType tagFlag);

/********************************************************
*IncidentDetectionInfo_incident_Detected_Type           *
********************************************************/
enum IncidentDetectionInfo_incident_Detected_Type {
	IncidentDetectionInfo_incident_Detected_Type_stalledVehicle = 1,
	IncidentDetectionInfo_incident_Detected_Type_reverseDriving = 2,
	IncidentDetectionInfo_incident_Detected_Type_pedestrian = 3,
	IncidentDetectionInfo_incident_Detected_Type_roadwayDebris = 4,
	IncidentDetectionInfo_incident_Detected_Type_rireSmoke = 5,
	IncidentDetectionInfo_incident_Detected_Type_roadShouldersVehicle = 6,
	IncidentDetectionInfo_incident_Detected_Type_roadkill = 7,
	IncidentDetectionInfo_incident_Detected_Type_slowVehicle = 8,
	IncidentDetectionInfo_incident_Detected_Type_delayCongested = 9,
};
#ifndef STRUC_IncidentDetectionInfo_incident_Detected_Type
#define STRUC_IncidentDetectionInfo_incident_Detected_Type
typedef enum IncidentDetectionInfo_incident_Detected_Type IncidentDetectionInfo_incident_Detected_Type;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_IncidentDetectionInfo_incident_Detected_Type(ASN1WorkSpace *workspace, IncidentDetectionInfo_incident_Detected_Type *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_IncidentDetectionInfo_incident_Detected_Type(ASN1WorkSpace *workspace, IncidentDetectionInfo_incident_Detected_Type *value, int length, ASN1TagType tagFlag);

/********************************************************
*NMEACoord_compass                                      *
********************************************************/
enum NMEACoord_compass {
	NMEACoord_compass_north = 0,
	NMEACoord_compass_south = 1,
};
#ifndef STRUC_NMEACoord_compass
#define STRUC_NMEACoord_compass
typedef enum NMEACoord_compass NMEACoord_compass;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_NMEACoord_compass(ASN1WorkSpace *workspace, NMEACoord_compass *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_NMEACoord_compass(ASN1WorkSpace *workspace, NMEACoord_compass *value, int length, ASN1TagType tagFlag);

/********************************************************
*NMEACoord_latitude                                     *
********************************************************/
#ifndef STRUC_NMEACoord_compass
#define STRUC_NMEACoord_compass
typedef enum NMEACoord_compass;
#endif
struct NMEACoord_latitude {
	INTEGER integerValue;
	INTEGER fractionValue;
	INTEGER fracSize;
	NMEACoord_compass compass;
};
#ifndef STRUC_NMEACoord_latitude
#define STRUC_NMEACoord_latitude
typedef struct NMEACoord_latitude NMEACoord_latitude;

#endif

ASN1_CPPLINK int ASN1_GET_NMEACoord_latitude_integerValue(ASN1WorkSpace *workspace, NMEACoord_latitude *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_NMEACoord_latitude_fractionValue(ASN1WorkSpace *workspace, NMEACoord_latitude *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_NMEACoord_latitude_fracSize(ASN1WorkSpace *workspace, NMEACoord_latitude *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_NMEACoord_latitude_compass(ASN1WorkSpace *workspace, NMEACoord_latitude *value, ENUMERATED *user_value);
ASN1_CPPLINK int ASN1_BER_Enc_NMEACoord_latitude(ASN1WorkSpace *workspace, NMEACoord_latitude *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_NMEACoord_latitude(ASN1WorkSpace *workspace, NMEACoord_latitude *value, int length, ASN1TagType tagFlag);

/********************************************************
*NMEACoord_longitude                                    *
********************************************************/
#ifndef STRUC_NMEACoord_compass
#define STRUC_NMEACoord_compass
typedef enum NMEACoord_compass;
#endif
struct NMEACoord_longitude {
	INTEGER integerValue;
	INTEGER fractionValue;
	INTEGER fracSize;
	NMEACoord_compass compass;
};
#ifndef STRUC_NMEACoord_longitude
#define STRUC_NMEACoord_longitude
typedef struct NMEACoord_longitude NMEACoord_longitude;

#endif

ASN1_CPPLINK int ASN1_GET_NMEACoord_longitude_integerValue(ASN1WorkSpace *workspace, NMEACoord_longitude *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_NMEACoord_longitude_fractionValue(ASN1WorkSpace *workspace, NMEACoord_longitude *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_NMEACoord_longitude_fracSize(ASN1WorkSpace *workspace, NMEACoord_longitude *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_NMEACoord_longitude_compass(ASN1WorkSpace *workspace, NMEACoord_longitude *value, ENUMERATED *user_value);
ASN1_CPPLINK int ASN1_BER_Enc_NMEACoord_longitude(ASN1WorkSpace *workspace, NMEACoord_longitude *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_NMEACoord_longitude(ASN1WorkSpace *workspace, NMEACoord_longitude *value, int length, ASN1TagType tagFlag);

/********************************************************
*NMEACoord                                              *
********************************************************/

#ifndef STRUC_NMEACoord_latitude
#define STRUC_NMEACoord_latitude
typedef struct NMEACoord_latitude NMEACoord_latitude;
#endif

#ifndef STRUC_NMEACoord_longitude
#define STRUC_NMEACoord_longitude
typedef struct NMEACoord_longitude NMEACoord_longitude;
#endif
struct NMEACoord {
	int DEF_NMEACoord_optData;
	NMEACoord_latitude *latitude;
	NMEACoord_longitude *longitude;
	OCTETSTRING optData;/* optional */
};
#ifndef STRUC_NMEACoord
#define STRUC_NMEACoord
typedef struct NMEACoord NMEACoord;

#endif

ASN1_CPPLINK int ASN1_GET_NMEACoord_latitude(ASN1WorkSpace *workspace, NMEACoord *value, NMEACoord_latitude **user_value);
ASN1_CPPLINK int ASN1_GET_NMEACoord_longitude(ASN1WorkSpace *workspace, NMEACoord *value, NMEACoord_longitude **user_value);
ASN1_CPPLINK int ASN1_GET_NMEACoord_optData(ASN1WorkSpace *workspace, NMEACoord *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length);
ASN1_CPPLINK int ASN1_BER_Enc_NMEACoord(ASN1WorkSpace *workspace, NMEACoord *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_NMEACoord(ASN1WorkSpace *workspace, NMEACoord *value, int length, ASN1TagType tagFlag);

/********************************************************
*IncidentDetectionInfo                                  *
********************************************************/
#ifndef STRUC_IncidentDetectionInfo_incident_Detected_Type
#define STRUC_IncidentDetectionInfo_incident_Detected_Type
typedef enum IncidentDetectionInfo_incident_Detected_Type;
#endif

#ifndef STRUC_NMEACoord
#define STRUC_NMEACoord
typedef struct NMEACoord NMEACoord;
#endif
struct IncidentDetectionInfo {
	int DEF_IncidentDetectionInfo_detected_Object_Size;
	VisibleString incident_Detected_Time;
	IncidentDetectionInfo_incident_Detected_Type incident_Detected_Type;
	NMEACoord *incident_Detected_Site;
	INTEGER detected_Object_Size;/* optional */
	INTEGER detected_Object_Distance;
	INTEGER detected_Object_Angle;
	INTEGER detected_Object_Speed;
};
#ifndef STRUC_IncidentDetectionInfo
#define STRUC_IncidentDetectionInfo
typedef struct IncidentDetectionInfo IncidentDetectionInfo;

#endif

ASN1_CPPLINK int ASN1_GET_IncidentDetectionInfo_incident_Detected_Time(ASN1WorkSpace *workspace, IncidentDetectionInfo *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length);
ASN1_CPPLINK int ASN1_GET_IncidentDetectionInfo_incident_Detected_Type(ASN1WorkSpace *workspace, IncidentDetectionInfo *value, ENUMERATED *user_value);
ASN1_CPPLINK int ASN1_GET_IncidentDetectionInfo_incident_Detected_Site(ASN1WorkSpace *workspace, IncidentDetectionInfo *value, NMEACoord **user_value);
ASN1_CPPLINK int ASN1_GET_IncidentDetectionInfo_detected_Object_Size(ASN1WorkSpace *workspace, IncidentDetectionInfo *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_IncidentDetectionInfo_detected_Object_Distance(ASN1WorkSpace *workspace, IncidentDetectionInfo *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_IncidentDetectionInfo_detected_Object_Angle(ASN1WorkSpace *workspace, IncidentDetectionInfo *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_IncidentDetectionInfo_detected_Object_Speed(ASN1WorkSpace *workspace, IncidentDetectionInfo *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_BER_Enc_IncidentDetectionInfo(ASN1WorkSpace *workspace, IncidentDetectionInfo *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_IncidentDetectionInfo(ASN1WorkSpace *workspace, IncidentDetectionInfo *value, int length, ASN1TagType tagFlag);

/********************************************************
*IncidentTerminationInfo_terminate_incidentType         *
********************************************************/
enum IncidentTerminationInfo_terminate_incidentType {
	IncidentTerminationInfo_terminate_incidentType_termination = 1,
	IncidentTerminationInfo_terminate_incidentType_timeout = 2,
};
#ifndef STRUC_IncidentTerminationInfo_terminate_incidentType
#define STRUC_IncidentTerminationInfo_terminate_incidentType
typedef enum IncidentTerminationInfo_terminate_incidentType IncidentTerminationInfo_terminate_incidentType;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_IncidentTerminationInfo_terminate_incidentType(ASN1WorkSpace *workspace, IncidentTerminationInfo_terminate_incidentType *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_IncidentTerminationInfo_terminate_incidentType(ASN1WorkSpace *workspace, IncidentTerminationInfo_terminate_incidentType *value, int length, ASN1TagType tagFlag);

/********************************************************
*IncidentTerminationInfo                                *
********************************************************/
#ifndef STRUC_IncidentTerminationInfo_terminate_incidentType
#define STRUC_IncidentTerminationInfo_terminate_incidentType
typedef enum IncidentTerminationInfo_terminate_incidentType;
#endif
struct IncidentTerminationInfo {
	IncidentTerminationInfo_terminate_incidentType terminate_incidentType;
};
#ifndef STRUC_IncidentTerminationInfo
#define STRUC_IncidentTerminationInfo
typedef struct IncidentTerminationInfo IncidentTerminationInfo;

#endif

ASN1_CPPLINK int ASN1_GET_IncidentTerminationInfo_terminate_incidentType(ASN1WorkSpace *workspace, IncidentTerminationInfo *value, ENUMERATED *user_value);
ASN1_CPPLINK int ASN1_BER_Enc_IncidentTerminationInfo(ASN1WorkSpace *workspace, IncidentTerminationInfo *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_IncidentTerminationInfo(ASN1WorkSpace *workspace, IncidentTerminationInfo *value, int length, ASN1TagType tagFlag);

/********************************************************
*IncidentDetectionVideoFileInfoProvide_fileStatus       *
********************************************************/
enum IncidentDetectionVideoFileInfoProvide_fileStatus {
	IncidentDetectionVideoFileInfoProvide_fileStatus_videoFileExists = 0,
	IncidentDetectionVideoFileInfoProvide_fileStatus_videoFileAlreadyExists = 1,
};
#ifndef STRUC_IncidentDetectionVideoFileInfoProvide_fileStatus
#define STRUC_IncidentDetectionVideoFileInfoProvide_fileStatus
typedef enum IncidentDetectionVideoFileInfoProvide_fileStatus IncidentDetectionVideoFileInfoProvide_fileStatus;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_IncidentDetectionVideoFileInfoProvide_fileStatus(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvide_fileStatus *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_IncidentDetectionVideoFileInfoProvide_fileStatus(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvide_fileStatus *value, int length, ASN1TagType tagFlag);

/********************************************************
*IncidentDetectionVideoFileInfoProvide                  *
********************************************************/
#ifndef STRUC_IncidentDetectionVideoFileInfoProvide_fileStatus
#define STRUC_IncidentDetectionVideoFileInfoProvide_fileStatus
typedef enum IncidentDetectionVideoFileInfoProvide_fileStatus;
#endif
struct IncidentDetectionVideoFileInfoProvide {
	int DEF_IncidentDetectionVideoFileInfoProvide_fileName;
	int DEF_IncidentDetectionVideoFileInfoProvide_fileSize;
	IncidentDetectionVideoFileInfoProvide_fileStatus fileStatus;
	OCTETSTRING fileName;/* optional */
	INTEGER fileSize;/* optional */
};
#ifndef STRUC_IncidentDetectionVideoFileInfoProvide
#define STRUC_IncidentDetectionVideoFileInfoProvide
typedef struct IncidentDetectionVideoFileInfoProvide IncidentDetectionVideoFileInfoProvide;

#endif

ASN1_CPPLINK int ASN1_GET_IncidentDetectionVideoFileInfoProvide_fileStatus(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvide *value, ENUMERATED *user_value);
ASN1_CPPLINK int ASN1_GET_IncidentDetectionVideoFileInfoProvide_fileName(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvide *value, ASNUINT8 **user_value, ASNUINT32 *user_value_length);
ASN1_CPPLINK int ASN1_GET_IncidentDetectionVideoFileInfoProvide_fileSize(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvide *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_BER_Enc_IncidentDetectionVideoFileInfoProvide(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvide *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_IncidentDetectionVideoFileInfoProvide(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvide *value, int length, ASN1TagType tagFlag);

/********************************************************
*ControlStateInfo                                       *
********************************************************/
struct ControlStateInfo {
	INTEGER cpu;
	INTEGER ram;
	INTEGER disk;
};
#ifndef STRUC_ControlStateInfo
#define STRUC_ControlStateInfo
typedef struct ControlStateInfo ControlStateInfo;

#endif

ASN1_CPPLINK int ASN1_GET_ControlStateInfo_cpu(ASN1WorkSpace *workspace, ControlStateInfo *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_ControlStateInfo_ram(ASN1WorkSpace *workspace, ControlStateInfo *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_ControlStateInfo_disk(ASN1WorkSpace *workspace, ControlStateInfo *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_BER_Enc_ControlStateInfo(ASN1WorkSpace *workspace, ControlStateInfo *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_ControlStateInfo(ASN1WorkSpace *workspace, ControlStateInfo *value, int length, ASN1TagType tagFlag);

/********************************************************
*SensorStateInfo_state                                  *
********************************************************/
enum SensorStateInfo_state {
	SensorStateInfo_state_normal = 0,
	SensorStateInfo_state_abnormal = 1,
};
#ifndef STRUC_SensorStateInfo_state
#define STRUC_SensorStateInfo_state
typedef enum SensorStateInfo_state SensorStateInfo_state;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_SensorStateInfo_state(ASN1WorkSpace *workspace, SensorStateInfo_state *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_SensorStateInfo_state(ASN1WorkSpace *workspace, SensorStateInfo_state *value, int length, ASN1TagType tagFlag);

/********************************************************
*SensorStateInfo                                        *
********************************************************/
#ifndef STRUC_SensorStateInfo_state
#define STRUC_SensorStateInfo_state
typedef enum SensorStateInfo_state;
#endif
#ifndef STRUC_SensorStateInfo_state
#define STRUC_SensorStateInfo_state
typedef enum SensorStateInfo_state;
#endif
#ifndef STRUC_SensorStateInfo_state
#define STRUC_SensorStateInfo_state
typedef enum SensorStateInfo_state;
#endif
#ifndef STRUC_SensorStateInfo_state
#define STRUC_SensorStateInfo_state
typedef enum SensorStateInfo_state;
#endif
struct SensorStateInfo {
	SensorStateInfo_state msm;
	SensorStateInfo_state txb;
	SensorStateInfo_state rxb;
	SensorStateInfo_state pwr;
};
#ifndef STRUC_SensorStateInfo
#define STRUC_SensorStateInfo
typedef struct SensorStateInfo SensorStateInfo;

#endif

ASN1_CPPLINK int ASN1_GET_SensorStateInfo_msm(ASN1WorkSpace *workspace, SensorStateInfo *value, ENUMERATED *user_value);
ASN1_CPPLINK int ASN1_GET_SensorStateInfo_txb(ASN1WorkSpace *workspace, SensorStateInfo *value, ENUMERATED *user_value);
ASN1_CPPLINK int ASN1_GET_SensorStateInfo_rxb(ASN1WorkSpace *workspace, SensorStateInfo *value, ENUMERATED *user_value);
ASN1_CPPLINK int ASN1_GET_SensorStateInfo_pwr(ASN1WorkSpace *workspace, SensorStateInfo *value, ENUMERATED *user_value);
ASN1_CPPLINK int ASN1_BER_Enc_SensorStateInfo(ASN1WorkSpace *workspace, SensorStateInfo *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_SensorStateInfo(ASN1WorkSpace *workspace, SensorStateInfo *value, int length, ASN1TagType tagFlag);

/********************************************************
*Novelty                                                *
********************************************************/
enum Novelty {
	Novelty_noveltyNew = 0,
	Novelty_noveltyUpdate = 1,
};
#ifndef STRUC_Novelty
#define STRUC_Novelty
typedef enum Novelty Novelty;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_Novelty(ASN1WorkSpace *workspace, Novelty *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_Novelty(ASN1WorkSpace *workspace, Novelty *value, int length, ASN1TagType tagFlag);

/********************************************************
*MovingObject_objectType                                *
********************************************************/
enum MovingObject_objectType {
	MovingObject_objectType_pedestrian = 0,
	MovingObject_objectType_vehicle = 1,
	MovingObject_objectType_bike = 2,
};
#ifndef STRUC_MovingObject_objectType
#define STRUC_MovingObject_objectType
typedef enum MovingObject_objectType MovingObject_objectType;
#endif

ASN1_CPPLINK int ASN1_BER_Enc_MovingObject_objectType(ASN1WorkSpace *workspace, MovingObject_objectType *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_MovingObject_objectType(ASN1WorkSpace *workspace, MovingObject_objectType *value, int length, ASN1TagType tagFlag);

/********************************************************
*MovingObject                                           *
********************************************************/
#ifndef STRUC_MovingObject_objectType
#define STRUC_MovingObject_objectType
typedef enum MovingObject_objectType;
#endif
#ifndef STRUC_ObjectID_00100
#define STRUC_ObjectID_00100
typedef INTEGER ObjectID_00100;
#endif
#ifndef STRUC_Novelty
#define STRUC_Novelty
typedef enum Novelty;
#endif

#ifndef STRUC_FullPositionVector_00100
#define STRUC_FullPositionVector_00100
typedef struct FullPositionVector_00100 FullPositionVector_00100;
#endif
struct MovingObject {
	int DEF_MovingObject_novelty;
	MovingObject_objectType objectType;
	ObjectID_00100 objectID;
	Novelty novelty;/* optional */
	INTEGER reliability;
	FullPositionVector_00100 *fullPositionVector;
};
#ifndef STRUC_MovingObject
#define STRUC_MovingObject
typedef struct MovingObject MovingObject;

#endif

ASN1_CPPLINK int ASN1_GET_MovingObject_objectType(ASN1WorkSpace *workspace, MovingObject *value, ENUMERATED *user_value);
ASN1_CPPLINK int ASN1_GET_MovingObject_objectID(ASN1WorkSpace *workspace, MovingObject *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_MovingObject_novelty(ASN1WorkSpace *workspace, MovingObject *value, ENUMERATED *user_value);
ASN1_CPPLINK int ASN1_GET_MovingObject_reliability(ASN1WorkSpace *workspace, MovingObject *value, INTEGER *user_value);
ASN1_CPPLINK int ASN1_GET_MovingObject_fullPositionVector(ASN1WorkSpace *workspace, MovingObject *value, FullPositionVector_00100 **user_value);
ASN1_CPPLINK int ASN1_BER_Enc_MovingObject(ASN1WorkSpace *workspace, MovingObject *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_MovingObject(ASN1WorkSpace *workspace, MovingObject *value, int length, ASN1TagType tagFlag);

/********************************************************
*IncidentDetectionInfoResponse                          *
********************************************************/

#ifndef STRUC_IncidentDetectionInfo
#define STRUC_IncidentDetectionInfo
typedef struct IncidentDetectionInfo IncidentDetectionInfo;
#endif
#ifndef STRUC_IncidentDetectionInfoResponse
#define STRUC_IncidentDetectionInfoResponse
typedef ASN1List IncidentDetectionInfoResponse;
#endif
ASN1_CPPLINK int ASN1_GET_IncidentDetectionInfoResponse_IncidentDetectionInfoResponse_pdata(ASN1WorkSpace *workspace, IncidentDetectionInfoResponse *value, IncidentDetectionInfo **user_value);
ASN1_CPPLINK int ASN1_BER_Enc_IncidentDetectionInfoResponse(ASN1WorkSpace *workspace, IncidentDetectionInfoResponse *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_IncidentDetectionInfoResponse(ASN1WorkSpace *workspace, IncidentDetectionInfoResponse *value, int length, ASN1TagType tagFlag);

/********************************************************
*IncidentTerminationInfoResponse                        *
********************************************************/

#ifndef STRUC_IncidentTerminationInfo
#define STRUC_IncidentTerminationInfo
typedef struct IncidentTerminationInfo IncidentTerminationInfo;
#endif
#ifndef STRUC_IncidentTerminationInfoResponse
#define STRUC_IncidentTerminationInfoResponse
typedef ASN1List IncidentTerminationInfoResponse;
#endif
ASN1_CPPLINK int ASN1_GET_IncidentTerminationInfoResponse_IncidentTerminationInfoResponse_pdata(ASN1WorkSpace *workspace, IncidentTerminationInfoResponse *value, IncidentTerminationInfo **user_value);
ASN1_CPPLINK int ASN1_BER_Enc_IncidentTerminationInfoResponse(ASN1WorkSpace *workspace, IncidentTerminationInfoResponse *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_IncidentTerminationInfoResponse(ASN1WorkSpace *workspace, IncidentTerminationInfoResponse *value, int length, ASN1TagType tagFlag);

/********************************************************
*IncidentDetectionVideoFileInfoProvideResponse          *
********************************************************/

#ifndef STRUC_IncidentDetectionVideoFileInfoProvide
#define STRUC_IncidentDetectionVideoFileInfoProvide
typedef struct IncidentDetectionVideoFileInfoProvide IncidentDetectionVideoFileInfoProvide;
#endif
#ifndef STRUC_IncidentDetectionVideoFileInfoProvideResponse
#define STRUC_IncidentDetectionVideoFileInfoProvideResponse
typedef ASN1List IncidentDetectionVideoFileInfoProvideResponse;
#endif
ASN1_CPPLINK int ASN1_GET_IncidentDetectionVideoFileInfoProvideResponse_IncidentDetectionVideoFileInfoProvideResponse_pdata(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvideResponse *value, IncidentDetectionVideoFileInfoProvide **user_value);
ASN1_CPPLINK int ASN1_BER_Enc_IncidentDetectionVideoFileInfoProvideResponse(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvideResponse *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_IncidentDetectionVideoFileInfoProvideResponse(ASN1WorkSpace *workspace, IncidentDetectionVideoFileInfoProvideResponse *value, int length, ASN1TagType tagFlag);

/********************************************************
*ControlStateInfoResponse                               *
********************************************************/

#ifndef STRUC_ControlStateInfo
#define STRUC_ControlStateInfo
typedef struct ControlStateInfo ControlStateInfo;
#endif
#ifndef STRUC_ControlStateInfoResponse
#define STRUC_ControlStateInfoResponse
typedef ASN1List ControlStateInfoResponse;
#endif
ASN1_CPPLINK int ASN1_GET_ControlStateInfoResponse_ControlStateInfoResponse_pdata(ASN1WorkSpace *workspace, ControlStateInfoResponse *value, ControlStateInfo **user_value);
ASN1_CPPLINK int ASN1_BER_Enc_ControlStateInfoResponse(ASN1WorkSpace *workspace, ControlStateInfoResponse *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_ControlStateInfoResponse(ASN1WorkSpace *workspace, ControlStateInfoResponse *value, int length, ASN1TagType tagFlag);

/********************************************************
*SensorStateInfoResponse                                *
********************************************************/

#ifndef STRUC_SensorStateInfo
#define STRUC_SensorStateInfo
typedef struct SensorStateInfo SensorStateInfo;
#endif
#ifndef STRUC_SensorStateInfoResponse
#define STRUC_SensorStateInfoResponse
typedef ASN1List SensorStateInfoResponse;
#endif
ASN1_CPPLINK int ASN1_GET_SensorStateInfoResponse_SensorStateInfoResponse_pdata(ASN1WorkSpace *workspace, SensorStateInfoResponse *value, SensorStateInfo **user_value);
ASN1_CPPLINK int ASN1_BER_Enc_SensorStateInfoResponse(ASN1WorkSpace *workspace, SensorStateInfoResponse *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_SensorStateInfoResponse(ASN1WorkSpace *workspace, SensorStateInfoResponse *value, int length, ASN1TagType tagFlag);

/********************************************************
*MovingObjectResponse                                   *
********************************************************/

#ifndef STRUC_MovingObject
#define STRUC_MovingObject
typedef struct MovingObject MovingObject;
#endif
#ifndef STRUC_MovingObjectResponse
#define STRUC_MovingObjectResponse
typedef ASN1List MovingObjectResponse;
#endif
ASN1_CPPLINK int ASN1_GET_MovingObjectResponse_MovingObjectResponse_pdata(ASN1WorkSpace *workspace, MovingObjectResponse *value, MovingObject **user_value);
ASN1_CPPLINK int ASN1_BER_Enc_MovingObjectResponse(ASN1WorkSpace *workspace, MovingObjectResponse *value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_MovingObjectResponse(ASN1WorkSpace *workspace, MovingObjectResponse *value, int length, ASN1TagType tagFlag);

#endif

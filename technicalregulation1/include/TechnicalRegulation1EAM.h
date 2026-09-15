#ifndef _CONFORMANCE1EAM_H_
#define _CONFORMANCE1EAM_H_

#include "BER/ASN1bersrc.h"
#include "IO/ASN1IO.h"
#include "MEM/mpool.h"
#include "OS/ASN1_Sys.h"
#include "TOOL/ASN1Tool.h"
#include "TYPE/ASN1_Type.h"



/********************************************************
*CurrentLinkState                                       *
********************************************************/
struct CurrentLinkState {
	int DEF_CurrentLinkState_link_VolumeRate;
	int DEF_CurrentLinkState_link_DensityRate;
	int DEF_CurrentLinkState_link_TravelTimeQuantity;
	int DEF_CurrentLinkState_link_DelayQuantity;
	int DEF_CurrentLinkState_tfdt_VehicleQueueLengthQuantity;
	UTF8Str link_LinkIdNumber;
	INTEGER link_SpeedRate;
	INTEGER link_VolumeRate;/* optional */
	INTEGER link_DensityRate;/* optional */
	INTEGER link_TravelTimeQuantity;/* optional */
	INTEGER link_DelayQuantity;/* optional */
	INTEGER tfdt_VehicleQueueLengthQuantity;/* optional */
	INTEGER tfdt_OccupancyPercent;
};
#ifndef STRUC_CurrentLinkState
#define STRUC_CurrentLinkState
typedef struct CurrentLinkState CurrentLinkState;

#endif

ASN1_CPPLINK int ASN1_Print_CurrentLinkState(CurrentLinkState* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_CurrentLinkState_link_LinkIdNumber(ASN1WorkSpace* workspace, CurrentLinkState* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_CurrentLinkState_link_SpeedRate(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_CurrentLinkState_link_VolumeRate(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_CurrentLinkState_link_DensityRate(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_CurrentLinkState_link_TravelTimeQuantity(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_CurrentLinkState_link_DelayQuantity(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_CurrentLinkState_tfdt_VehicleQueueLengthQuantity(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_CurrentLinkState_tfdt_OccupancyPercent(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_GET_CurrentLinkState_link_LinkIdNumber(ASN1WorkSpace* workspace, CurrentLinkState* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_CurrentLinkState_link_SpeedRate(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_CurrentLinkState_link_VolumeRate(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_CurrentLinkState_link_DensityRate(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_CurrentLinkState_link_TravelTimeQuantity(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_CurrentLinkState_link_DelayQuantity(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_CurrentLinkState_tfdt_VehicleQueueLengthQuantity(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_CurrentLinkState_tfdt_OccupancyPercent(ASN1WorkSpace* workspace, CurrentLinkState* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_BER_Enc_CurrentLinkState(ASN1WorkSpace* workspace, CurrentLinkState* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_CurrentLinkState(ASN1WorkSpace* workspace, CurrentLinkState* value, int length, ASN1TagType tagFlag);

/********************************************************
*CurrentLinkStateRequest                                *
********************************************************/
#ifndef STRUC_CurrentLinkStateRequest
#define STRUC_CurrentLinkStateRequest
typedef UTF8Str CurrentLinkStateRequest;
#endif

ASN1_CPPLINK int ASN1_Print_CurrentLinkStateRequest(CurrentLinkStateRequest* value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_CurrentLinkStateRequest(ASN1WorkSpace* workspace, CurrentLinkStateRequest* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_CurrentLinkStateRequest(ASN1WorkSpace* workspace, CurrentLinkStateRequest* value, int length, ASN1TagType tagFlag);

/********************************************************
*CurrentLinkStateResponse                               *
********************************************************/

#ifndef STRUC_CurrentLinkState
#define STRUC_CurrentLinkState
typedef struct CurrentLinkState CurrentLinkState;
#endif
#ifndef STRUC_CurrentLinkStateResponse
#define STRUC_CurrentLinkStateResponse
typedef ASN1List CurrentLinkStateResponse;
#endif
ASN1_CPPLINK int ASN1_Print_CurrentLinkStateResponse(CurrentLinkStateResponse* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_CurrentLinkStateResponse_CurrentLinkStateResponse_pdata(ASN1WorkSpace* workspace, CurrentLinkStateResponse* value, CurrentLinkState* user_value);
ASN1_CPPLINK int ASN1_GET_CurrentLinkStateResponse_CurrentLinkStateResponse_pdata(ASN1WorkSpace* workspace, CurrentLinkStateResponse* value, CurrentLinkState** user_value);
ASN1_CPPLINK int ASN1_BER_Enc_CurrentLinkStateResponse(ASN1WorkSpace* workspace, CurrentLinkStateResponse* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_CurrentLinkStateResponse(ASN1WorkSpace* workspace, CurrentLinkStateResponse* value, int length, ASN1TagType tagFlag);

/********************************************************
*EventIdentity                                          *
********************************************************/
struct EventIdentity {
	int DEF_EventIdentity_evnt_IdentificationNumber;
	int DEF_EventIdentity_evnt_DescriptionTypeEventCode;
	int DEF_EventIdentity_evnt_DescriptionTypeSpecialEventCode;
	int DEF_EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode;
	UTF8Str node_NodeIdNumber;
	UTF8Str link_LinkIdNumber;
	INTEGER evnt_IdentificationNumber;/* optional */
	UTF8Str evnt_LocationJurisDictionNameText;
	UTF8Str evnt_LocationLinkIdNumber;
	UTF8Str evnt_LocationNodeIdNumber;
	UTF8Str evnt_LocationRoadwayNameText;
	enum {
		EventIdentity_evnt_DescriptionTypeEventCode_none = 0,
		EventIdentity_evnt_DescriptionTypeEventCode_other = 1,
		EventIdentity_evnt_DescriptionTypeEventCode_constructions = 2,
		EventIdentity_evnt_DescriptionTypeEventCode_planned_roadway_closure = 3,
		EventIdentity_evnt_DescriptionTypeEventCode_special_event = 4,
	} evnt_DescriptionTypeEventCode;/* optional */
	enum {
		EventIdentity_evnt_DescriptionTypeSpecialEventCode_none = 0,
		EventIdentity_evnt_DescriptionTypeSpecialEventCode_other = 1,
		EventIdentity_evnt_DescriptionTypeSpecialEventCode_parade = 2,
		EventIdentity_evnt_DescriptionTypeSpecialEventCode_sporting_event = 3,
		EventIdentity_evnt_DescriptionTypeSpecialEventCode_demonstration = 4,
		EventIdentity_evnt_DescriptionTypeSpecialEventCode_festival = 5,
		EventIdentity_evnt_DescriptionTypeSpecialEventCode_performing_arts = 6,
		EventIdentity_evnt_DescriptionTypeSpecialEventCode_dignitary_visit = 7,
	} evnt_DescriptionTypeSpecialEventCode;/* optional */
	enum {
		EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_none = 0,
		EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_other = 1,
		EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_long_term_construction = 2,
		EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_short_term_construction = 3,
		EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_maintenance = 4,
		EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_emergency_maintenance = 5,
	} evnt_DescriptionPlannedRoadWayClosureCode;/* optional */
	INTEGER evnt_LanesBlockedOrClosedNumber;
	// none = 0
	// other = 1
	// right_shoulder = 2
	// left_shoulder = 3
	// both_shoulder = 4
	BITSTRING evnt_LanesShouldersBlockedCode;
	VisibleString evnt_TimelineStartGeneralizedTime;
	VisibleString evnt_TimelineEndGeneralizedTime;
	INTEGER evnt_TimelineDurationTime;
};
#ifndef STRUC_EventIdentity
#define STRUC_EventIdentity
typedef struct EventIdentity EventIdentity;

#endif

ASN1_CPPLINK int ASN1_Print_EventIdentity(EventIdentity* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_EventIdentity_node_NodeIdNumber(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_EventIdentity_link_LinkIdNumber(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_EventIdentity_evnt_IdentificationNumber(ASN1WorkSpace* workspace, EventIdentity* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_EventIdentity_evnt_LocationJurisDictionNameText(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_EventIdentity_evnt_LocationLinkIdNumber(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_EventIdentity_evnt_LocationNodeIdNumber(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_EventIdentity_evnt_LocationRoadwayNameText(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_EventIdentity_evnt_DescriptionTypeEventCode(ASN1WorkSpace* workspace, EventIdentity* value, ENUMERATED user_value);
ASN1_CPPLINK int ASN1_SET_EventIdentity_evnt_DescriptionTypeSpecialEventCode(ASN1WorkSpace* workspace, EventIdentity* value, ENUMERATED user_value);
ASN1_CPPLINK int ASN1_SET_EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode(ASN1WorkSpace* workspace, EventIdentity* value, ENUMERATED user_value);
ASN1_CPPLINK int ASN1_SET_EventIdentity_evnt_LanesBlockedOrClosedNumber(ASN1WorkSpace* workspace, EventIdentity* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_EventIdentity_evnt_LanesShouldersBlockedCode(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8* user_value, ASNUINT32L user_value_length);
ASN1_CPPLINK int ASN1_SET_EventIdentity_evnt_TimelineStartGeneralizedTime(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_EventIdentity_evnt_TimelineEndGeneralizedTime(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_EventIdentity_evnt_TimelineDurationTime(ASN1WorkSpace* workspace, EventIdentity* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_GET_EventIdentity_node_NodeIdNumber(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_EventIdentity_link_LinkIdNumber(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_EventIdentity_evnt_IdentificationNumber(ASN1WorkSpace* workspace, EventIdentity* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_EventIdentity_evnt_LocationJurisDictionNameText(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_EventIdentity_evnt_LocationLinkIdNumber(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_EventIdentity_evnt_LocationNodeIdNumber(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_EventIdentity_evnt_LocationRoadwayNameText(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_EventIdentity_evnt_DescriptionTypeEventCode(ASN1WorkSpace* workspace, EventIdentity* value, ENUMERATED* user_value);
ASN1_CPPLINK int ASN1_GET_EventIdentity_evnt_DescriptionTypeSpecialEventCode(ASN1WorkSpace* workspace, EventIdentity* value, ENUMERATED* user_value);
ASN1_CPPLINK int ASN1_GET_EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode(ASN1WorkSpace* workspace, EventIdentity* value, ENUMERATED* user_value);
ASN1_CPPLINK int ASN1_GET_EventIdentity_evnt_LanesBlockedOrClosedNumber(ASN1WorkSpace* workspace, EventIdentity* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_EventIdentity_evnt_LanesShouldersBlockedCode(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8** user_value, ASNUINT32L* user_value_length);
ASN1_CPPLINK int ASN1_GET_EventIdentity_evnt_TimelineStartGeneralizedTime(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_EventIdentity_evnt_TimelineEndGeneralizedTime(ASN1WorkSpace* workspace, EventIdentity* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_EventIdentity_evnt_TimelineDurationTime(ASN1WorkSpace* workspace, EventIdentity* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_BER_Enc_EventIdentity(ASN1WorkSpace* workspace, EventIdentity* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_EventIdentity(ASN1WorkSpace* workspace, EventIdentity* value, int length, ASN1TagType tagFlag);

/********************************************************
*EventIdentityRequest                                   *
********************************************************/
#ifndef STRUC_EventIdentityRequest
#define STRUC_EventIdentityRequest
typedef UTF8Str EventIdentityRequest;
#endif

ASN1_CPPLINK int ASN1_Print_EventIdentityRequest(EventIdentityRequest* value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_EventIdentityRequest(ASN1WorkSpace* workspace, EventIdentityRequest* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_EventIdentityRequest(ASN1WorkSpace* workspace, EventIdentityRequest* value, int length, ASN1TagType tagFlag);

/********************************************************
*EventIdentityResponse                                  *
********************************************************/

#ifndef STRUC_EventIdentity
#define STRUC_EventIdentity
typedef struct EventIdentity EventIdentity;
#endif
#ifndef STRUC_EventIdentityResponse
#define STRUC_EventIdentityResponse
typedef ASN1List EventIdentityResponse;
#endif
ASN1_CPPLINK int ASN1_Print_EventIdentityResponse(EventIdentityResponse* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_EventIdentityResponse_EventIdentityResponse_pdata(ASN1WorkSpace* workspace, EventIdentityResponse* value, EventIdentity* user_value);
ASN1_CPPLINK int ASN1_GET_EventIdentityResponse_EventIdentityResponse_pdata(ASN1WorkSpace* workspace, EventIdentityResponse* value, EventIdentity** user_value);
ASN1_CPPLINK int ASN1_BER_Enc_EventIdentityResponse(ASN1WorkSpace* workspace, EventIdentityResponse* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_EventIdentityResponse(ASN1WorkSpace* workspace, EventIdentityResponse* value, int length, ASN1TagType tagFlag);

/********************************************************
*IncidentIdentity                                       *
********************************************************/
struct IncidentIdentity {
	int DEF_IncidentIdentity_evnt_LocationLinearDistanceOffsetBeginNumber;
	int DEF_IncidentIdentity_evnt_LinearDistanceoffsetEndNumber;
	int DEF_IncidentIdentity_evnt_IncidentHumanFatalitiesCountQuantity;
	int DEF_IncidentIdentity_evnt_IncidentHumanInjuriesCountQuantity;
	int DEF_IncidentIdentity_evnt_IncidentPropertyDamageOther;
	UTF8Str node_NodeIdNumber;
	UTF8Str link_LinkIdNumber;
	INTEGER evnt_LocationLinearDistanceOffsetBeginNumber;/* optional */
	INTEGER evnt_LinearDistanceoffsetEndNumber;/* optional */
	VisibleString evnt_UpdateGeneralizedTime;
	INTEGER evnt_IncidentHumanFatalitiesCountQuantity;/* optional */
	INTEGER evnt_IncidentHumanInjuriesCountQuantity;/* optional */
	// other_no_additional_information_required = 0
	// other_additional_information_required = 1
	// guard_rail_damage = 2
	// light_pole_damage = 3
	// pavement_damage = 4
	// structure_damage = 5
	// traffic_equipment_damage = 6
	BITSTRING evnt_IncidentPropertyDamageCode;
	UTF8Str evnt_IncidentPropertyDamageOther;/* optional */
};
#ifndef STRUC_IncidentIdentity
#define STRUC_IncidentIdentity
typedef struct IncidentIdentity IncidentIdentity;

#endif

ASN1_CPPLINK int ASN1_Print_IncidentIdentity(IncidentIdentity* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_IncidentIdentity_node_NodeIdNumber(ASN1WorkSpace* workspace, IncidentIdentity* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_IncidentIdentity_link_LinkIdNumber(ASN1WorkSpace* workspace, IncidentIdentity* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_IncidentIdentity_evnt_LocationLinearDistanceOffsetBeginNumber(ASN1WorkSpace* workspace, IncidentIdentity* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_IncidentIdentity_evnt_LinearDistanceoffsetEndNumber(ASN1WorkSpace* workspace, IncidentIdentity* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_IncidentIdentity_evnt_UpdateGeneralizedTime(ASN1WorkSpace* workspace, IncidentIdentity* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_IncidentIdentity_evnt_IncidentHumanFatalitiesCountQuantity(ASN1WorkSpace* workspace, IncidentIdentity* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_IncidentIdentity_evnt_IncidentHumanInjuriesCountQuantity(ASN1WorkSpace* workspace, IncidentIdentity* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_IncidentIdentity_evnt_IncidentPropertyDamageCode(ASN1WorkSpace* workspace, IncidentIdentity* value, ASNUINT8* user_value, ASNUINT32L user_value_length);
ASN1_CPPLINK int ASN1_SET_IncidentIdentity_evnt_IncidentPropertyDamageOther(ASN1WorkSpace* workspace, IncidentIdentity* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_GET_IncidentIdentity_node_NodeIdNumber(ASN1WorkSpace* workspace, IncidentIdentity* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_IncidentIdentity_link_LinkIdNumber(ASN1WorkSpace* workspace, IncidentIdentity* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_IncidentIdentity_evnt_LocationLinearDistanceOffsetBeginNumber(ASN1WorkSpace* workspace, IncidentIdentity* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_IncidentIdentity_evnt_LinearDistanceoffsetEndNumber(ASN1WorkSpace* workspace, IncidentIdentity* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_IncidentIdentity_evnt_UpdateGeneralizedTime(ASN1WorkSpace* workspace, IncidentIdentity* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_IncidentIdentity_evnt_IncidentHumanFatalitiesCountQuantity(ASN1WorkSpace* workspace, IncidentIdentity* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_IncidentIdentity_evnt_IncidentHumanInjuriesCountQuantity(ASN1WorkSpace* workspace, IncidentIdentity* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_IncidentIdentity_evnt_IncidentPropertyDamageCode(ASN1WorkSpace* workspace, IncidentIdentity* value, ASNUINT8** user_value, ASNUINT32L* user_value_length);
ASN1_CPPLINK int ASN1_GET_IncidentIdentity_evnt_IncidentPropertyDamageOther(ASN1WorkSpace* workspace, IncidentIdentity* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_BER_Enc_IncidentIdentity(ASN1WorkSpace* workspace, IncidentIdentity* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_IncidentIdentity(ASN1WorkSpace* workspace, IncidentIdentity* value, int length, ASN1TagType tagFlag);

/********************************************************
*IncidentIdentityRequest                                *
********************************************************/
#ifndef STRUC_IncidentIdentityRequest
#define STRUC_IncidentIdentityRequest
typedef UTF8Str IncidentIdentityRequest;
#endif

ASN1_CPPLINK int ASN1_Print_IncidentIdentityRequest(IncidentIdentityRequest* value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_IncidentIdentityRequest(ASN1WorkSpace* workspace, IncidentIdentityRequest* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_IncidentIdentityRequest(ASN1WorkSpace* workspace, IncidentIdentityRequest* value, int length, ASN1TagType tagFlag);

/********************************************************
*IncidentIdentityResponse                               *
********************************************************/

#ifndef STRUC_IncidentIdentity
#define STRUC_IncidentIdentity
typedef struct IncidentIdentity IncidentIdentity;
#endif
#ifndef STRUC_IncidentIdentityResponse
#define STRUC_IncidentIdentityResponse
typedef ASN1List IncidentIdentityResponse;
#endif
ASN1_CPPLINK int ASN1_Print_IncidentIdentityResponse(IncidentIdentityResponse* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_IncidentIdentityResponse_IncidentIdentityResponse_pdata(ASN1WorkSpace* workspace, IncidentIdentityResponse* value, IncidentIdentity* user_value);
ASN1_CPPLINK int ASN1_GET_IncidentIdentityResponse_IncidentIdentityResponse_pdata(ASN1WorkSpace* workspace, IncidentIdentityResponse* value, IncidentIdentity** user_value);
ASN1_CPPLINK int ASN1_BER_Enc_IncidentIdentityResponse(ASN1WorkSpace* workspace, IncidentIdentityResponse* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_IncidentIdentityResponse(ASN1WorkSpace* workspace, IncidentIdentityResponse* value, int length, ASN1TagType tagFlag);

/********************************************************
*IncidentConditions                                     *
********************************************************/
struct IncidentConditions {
	int DEF_IncidentConditions_evnt_DescriptionTypeIncidentOther;
	int DEF_IncidentConditions_evnt_IncidentVehiclesInvolvedOther;
	int DEF_IncidentConditions_evnt_IncidentStatusOther;
	int DEF_IncidentConditions_evnt_UpdateTypeOther;
	UTF8Str node_NodeIdNumber;
	UTF8Str link_LinkIdNumber;
	UTF8Str orgn_ContatOrganizationNameText;
	enum {
		IncidentConditions_evnt_DescriptionTypeIncidentCode_other_no_additional_information_required = 0,
		IncidentConditions_evnt_DescriptionTypeIncidentCode_other_additional_information_required = 1,
		IncidentConditions_evnt_DescriptionTypeIncidentCode_vehicular_accident = 2,
		IncidentConditions_evnt_DescriptionTypeIncidentCode_weather_related_incident = 3,
		IncidentConditions_evnt_DescriptionTypeIncidentCode_stalled_vehicle = 4,
		IncidentConditions_evnt_DescriptionTypeIncidentCode_vehicle_fire = 5,
		IncidentConditions_evnt_DescriptionTypeIncidentCode_roadway_debris = 6,
		IncidentConditions_evnt_DescriptionTypeIncidentCode_hazmat_spill = 7,
		IncidentConditions_evnt_DescriptionTypeIncidentCode_earthquake = 8,
		IncidentConditions_evnt_DescriptionTypeIncidentCode_landslide = 9,
		IncidentConditions_evnt_DescriptionTypeIncidentCode_flood = 10,
		IncidentConditions_evnt_DescriptionTypeIncidentCode_typhoon = 11,
		IncidentConditions_evnt_DescriptionTypeIncidentCode_unplanned_demonstration = 12,
		IncidentConditions_evnt_DescriptionTypeIncidentCode_increased_traffice_volume = 13,
	} evnt_DescriptionTypeIncidentCode;
	UTF8Str evnt_DescriptionTypeIncidentOther;/* optional */
	// other_no_additional_information_required = 0
	// other_additional_information_required = 1
	// cycle_motorcycle = 2
	// car = 3
	// bus = 4
	// single_Unit_Truck = 5
	// trailer = 6
	BITSTRING evnt_IncidentVehiclesInvolvedCode;
	UTF8Str evnt_IncidentVehiclesInvolvedOther;/* optional */
	enum {
		IncidentConditions_evnt_IncidentStatusCode_other_no_additional_information_required = 0,
		IncidentConditions_evnt_IncidentStatusCode_other_additional_information_required = 1,
		IncidentConditions_evnt_IncidentStatusCode_incident_detected = 2,
		IncidentConditions_evnt_IncidentStatusCode_confirmed_and_responding = 3,
		IncidentConditions_evnt_IncidentStatusCode_cleared_and_recovering = 4,
		IncidentConditions_evnt_IncidentStatusCode_over_and_done = 5,
		IncidentConditions_evnt_IncidentStatusCode_other = 6,
	} evnt_IncidentStatusCode;
	UTF8Str evnt_IncidentStatusOther;/* optional */
	enum {
		IncidentConditions_evnt_UpdateTypeCode_other_no_additional_information_required = 0,
		IncidentConditions_evnt_UpdateTypeCode_other_additional_information_required = 1,
		IncidentConditions_evnt_UpdateTypeCode_new = 2,
		IncidentConditions_evnt_UpdateTypeCode_update = 3,
		IncidentConditions_evnt_UpdateTypeCode_delete = 4,
		IncidentConditions_evnt_UpdateTypeCode_clear_or_closed = 5,
	} evnt_UpdateTypeCode;
	UTF8Str evnt_UpdateTypeOther;/* optional */
};
#ifndef STRUC_IncidentConditions
#define STRUC_IncidentConditions
typedef struct IncidentConditions IncidentConditions;

#endif

ASN1_CPPLINK int ASN1_Print_IncidentConditions(IncidentConditions* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_IncidentConditions_node_NodeIdNumber(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_IncidentConditions_link_LinkIdNumber(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_IncidentConditions_orgn_ContatOrganizationNameText(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_IncidentConditions_evnt_DescriptionTypeIncidentCode(ASN1WorkSpace* workspace, IncidentConditions* value, ENUMERATED user_value);
ASN1_CPPLINK int ASN1_SET_IncidentConditions_evnt_DescriptionTypeIncidentOther(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_IncidentConditions_evnt_IncidentVehiclesInvolvedCode(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8* user_value, ASNUINT32L user_value_length);
ASN1_CPPLINK int ASN1_SET_IncidentConditions_evnt_IncidentVehiclesInvolvedOther(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_IncidentConditions_evnt_IncidentStatusCode(ASN1WorkSpace* workspace, IncidentConditions* value, ENUMERATED user_value);
ASN1_CPPLINK int ASN1_SET_IncidentConditions_evnt_IncidentStatusOther(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_IncidentConditions_evnt_UpdateTypeCode(ASN1WorkSpace* workspace, IncidentConditions* value, ENUMERATED user_value);
ASN1_CPPLINK int ASN1_SET_IncidentConditions_evnt_UpdateTypeOther(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_GET_IncidentConditions_node_NodeIdNumber(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_IncidentConditions_link_LinkIdNumber(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_IncidentConditions_orgn_ContatOrganizationNameText(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_IncidentConditions_evnt_DescriptionTypeIncidentCode(ASN1WorkSpace* workspace, IncidentConditions* value, ENUMERATED* user_value);
ASN1_CPPLINK int ASN1_GET_IncidentConditions_evnt_DescriptionTypeIncidentOther(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_IncidentConditions_evnt_IncidentVehiclesInvolvedCode(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8** user_value, ASNUINT32L* user_value_length);
ASN1_CPPLINK int ASN1_GET_IncidentConditions_evnt_IncidentVehiclesInvolvedOther(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_IncidentConditions_evnt_IncidentStatusCode(ASN1WorkSpace* workspace, IncidentConditions* value, ENUMERATED* user_value);
ASN1_CPPLINK int ASN1_GET_IncidentConditions_evnt_IncidentStatusOther(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_IncidentConditions_evnt_UpdateTypeCode(ASN1WorkSpace* workspace, IncidentConditions* value, ENUMERATED* user_value);
ASN1_CPPLINK int ASN1_GET_IncidentConditions_evnt_UpdateTypeOther(ASN1WorkSpace* workspace, IncidentConditions* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_BER_Enc_IncidentConditions(ASN1WorkSpace* workspace, IncidentConditions* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_IncidentConditions(ASN1WorkSpace* workspace, IncidentConditions* value, int length, ASN1TagType tagFlag);

/********************************************************
*IncidentConditionsRequest                              *
********************************************************/
#ifndef STRUC_IncidentConditionsRequest
#define STRUC_IncidentConditionsRequest
typedef UTF8Str IncidentConditionsRequest;
#endif

ASN1_CPPLINK int ASN1_Print_IncidentConditionsRequest(IncidentConditionsRequest* value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_IncidentConditionsRequest(ASN1WorkSpace* workspace, IncidentConditionsRequest* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_IncidentConditionsRequest(ASN1WorkSpace* workspace, IncidentConditionsRequest* value, int length, ASN1TagType tagFlag);

/********************************************************
*IncidentConditionsResponse                             *
********************************************************/

#ifndef STRUC_IncidentConditions
#define STRUC_IncidentConditions
typedef struct IncidentConditions IncidentConditions;
#endif
#ifndef STRUC_IncidentConditionsResponse
#define STRUC_IncidentConditionsResponse
typedef ASN1List IncidentConditionsResponse;
#endif
ASN1_CPPLINK int ASN1_Print_IncidentConditionsResponse(IncidentConditionsResponse* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_IncidentConditionsResponse_IncidentConditionsResponse_pdata(ASN1WorkSpace* workspace, IncidentConditionsResponse* value, IncidentConditions* user_value);
ASN1_CPPLINK int ASN1_GET_IncidentConditionsResponse_IncidentConditionsResponse_pdata(ASN1WorkSpace* workspace, IncidentConditionsResponse* value, IncidentConditions** user_value);
ASN1_CPPLINK int ASN1_BER_Enc_IncidentConditionsResponse(ASN1WorkSpace* workspace, IncidentConditionsResponse* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_IncidentConditionsResponse(ASN1WorkSpace* workspace, IncidentConditionsResponse* value, int length, ASN1TagType tagFlag);

/********************************************************
*RoadwaySurfaceStatus                                   *
********************************************************/
struct RoadwaySurfaceStatus {
	int DEF_RoadwaySurfaceStatus_evsn_DataSurfacePrecipitationDepth;
	int DEF_RoadwaySurfaceStatus_evsn_DataSurfaceTemperatureQuantity;
	UTF8Str node_NodeIdNumber;
	UTF8Str link_LinkIdNumber;
	// other_no_additional_information_required = 0
	// other_additional_information_required = 1
	// no_determination_made = 2
	// wet = 3
	// ice = 4
	// snow = 5
	// rocks = 6
	// oil = 7
	// debris = 8
	// broken_pavement = 9
	// power_lines_down = 10
	// material_spill = 11
	// chemical_spill = 12
	// inundation = 13
	BITSTRING link_SurfaceConditionCode;
	// other_no_additional_information_required = 0
	// other_additional_information_required = 1
	// no_determination_made = 2
	// open = 3
	// closed = 4
	BITSTRING link_LandBlockedOrClosedCode;
	INTEGER evsn_DataSurfacePrecipitationDepth;/* optional */
	INTEGER evsn_DataSurfaceTemperatureQuantity;/* optional */
};
#ifndef STRUC_RoadwaySurfaceStatus
#define STRUC_RoadwaySurfaceStatus
typedef struct RoadwaySurfaceStatus RoadwaySurfaceStatus;

#endif

ASN1_CPPLINK int ASN1_Print_RoadwaySurfaceStatus(RoadwaySurfaceStatus* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_RoadwaySurfaceStatus_node_NodeIdNumber(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_RoadwaySurfaceStatus_link_LinkIdNumber(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_RoadwaySurfaceStatus_link_SurfaceConditionCode(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, ASNUINT8* user_value, ASNUINT32L user_value_length);
ASN1_CPPLINK int ASN1_SET_RoadwaySurfaceStatus_link_LandBlockedOrClosedCode(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, ASNUINT8* user_value, ASNUINT32L user_value_length);
ASN1_CPPLINK int ASN1_SET_RoadwaySurfaceStatus_evsn_DataSurfacePrecipitationDepth(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_RoadwaySurfaceStatus_evsn_DataSurfaceTemperatureQuantity(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_GET_RoadwaySurfaceStatus_node_NodeIdNumber(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_RoadwaySurfaceStatus_link_LinkIdNumber(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_RoadwaySurfaceStatus_link_SurfaceConditionCode(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, ASNUINT8** user_value, ASNUINT32L* user_value_length);
ASN1_CPPLINK int ASN1_GET_RoadwaySurfaceStatus_link_LandBlockedOrClosedCode(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, ASNUINT8** user_value, ASNUINT32L* user_value_length);
ASN1_CPPLINK int ASN1_GET_RoadwaySurfaceStatus_evsn_DataSurfacePrecipitationDepth(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_RoadwaySurfaceStatus_evsn_DataSurfaceTemperatureQuantity(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_BER_Enc_RoadwaySurfaceStatus(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_RoadwaySurfaceStatus(ASN1WorkSpace* workspace, RoadwaySurfaceStatus* value, int length, ASN1TagType tagFlag);

/********************************************************
*RoadwaySurfaceStatusRequest                            *
********************************************************/
#ifndef STRUC_RoadwaySurfaceStatusRequest
#define STRUC_RoadwaySurfaceStatusRequest
typedef UTF8Str RoadwaySurfaceStatusRequest;
#endif

ASN1_CPPLINK int ASN1_Print_RoadwaySurfaceStatusRequest(RoadwaySurfaceStatusRequest* value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_RoadwaySurfaceStatusRequest(ASN1WorkSpace* workspace, RoadwaySurfaceStatusRequest* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_RoadwaySurfaceStatusRequest(ASN1WorkSpace* workspace, RoadwaySurfaceStatusRequest* value, int length, ASN1TagType tagFlag);

/********************************************************
*RoadwaySurfaceStatusResponse                           *
********************************************************/

#ifndef STRUC_RoadwaySurfaceStatus
#define STRUC_RoadwaySurfaceStatus
typedef struct RoadwaySurfaceStatus RoadwaySurfaceStatus;
#endif
#ifndef STRUC_RoadwaySurfaceStatusResponse
#define STRUC_RoadwaySurfaceStatusResponse
typedef ASN1List RoadwaySurfaceStatusResponse;
#endif
ASN1_CPPLINK int ASN1_Print_RoadwaySurfaceStatusResponse(RoadwaySurfaceStatusResponse* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_RoadwaySurfaceStatusResponse_RoadwaySurfaceStatusResponse_pdata(ASN1WorkSpace* workspace, RoadwaySurfaceStatusResponse* value, RoadwaySurfaceStatus* user_value);
ASN1_CPPLINK int ASN1_GET_RoadwaySurfaceStatusResponse_RoadwaySurfaceStatusResponse_pdata(ASN1WorkSpace* workspace, RoadwaySurfaceStatusResponse* value, RoadwaySurfaceStatus** user_value);
ASN1_CPPLINK int ASN1_BER_Enc_RoadwaySurfaceStatusResponse(ASN1WorkSpace* workspace, RoadwaySurfaceStatusResponse* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_RoadwaySurfaceStatusResponse(ASN1WorkSpace* workspace, RoadwaySurfaceStatusResponse* value, int length, ASN1TagType tagFlag);

/********************************************************
*WeatherInformation                                     *
********************************************************/
struct WeatherInformation {
	int DEF_WeatherInformation_wthr_TemperatureQuantity;
	int DEF_WeatherInformation_wthr_HighTemperatureQuantity;
	int DEF_WeatherInformation_wthr_LowTemperatureQuantity;
	int DEF_WeatherInformation_wthr_SpecialConditions;
	int DEF_WeatherInformation_wthr_SpecialConditionsOther;
	int DEF_WeatherInformation_wthr_VisibilityQuantity;
	int DEF_WeatherInformation_wthr_WindSpeedQuantity;
	int DEF_WeatherInformation_wthr_WindDirectionCode;
	int DEF_WeatherInformation_wthr_HumidityQuantity;
	int DEF_WeatherInformation_wthr_PressureQuantity;
	int DEF_WeatherInformation_wthr_SunriseTimeGeneralizedTime;
	int DEF_WeatherInformation_wthr_SunsetTimeGeneralizedTime;
	enum {
		WeatherInformation_wthr_ForecastOrActualCode_actual = 0,
		WeatherInformation_wthr_ForecastOrActualCode_forecast = 1,
	} wthr_ForecastOrActualCode;
	INTEGER wthr_TemperatureQuantity;/* optional */
	INTEGER wthr_HighTemperatureQuantity;/* optional */
	INTEGER wthr_LowTemperatureQuantity;/* optional */
	// other_no_additional_information_required = 0
	// other_additional_information_required = 1
	// avalanche = 2
	// cloud_coverage = 3
	// extreme_cold = 4
	// extreme_heat = 5
	// flood = 6
	// fog = 7
	// typhoon = 8
	// ozone_alert = 9
	// precipitation = 10
	// thunderstrom = 11
	// ultra_violet_light_alert = 12
	BITSTRING wthr_SpecialConditions;/* optional */
	UTF8Str wthr_SpecialConditionsOther;/* optional */
	INTEGER wthr_ProbabilityPercent;
	INTEGER wthr_VisibilityQuantity;/* optional */
	INTEGER wthr_WindSpeedQuantity;/* optional */
	enum {
		WeatherInformation_wthr_WindDirectionCode_north = 0,
		WeatherInformation_wthr_WindDirectionCode_south = 1,
		WeatherInformation_wthr_WindDirectionCode_west = 2,
		WeatherInformation_wthr_WindDirectionCode_east = 3,
		WeatherInformation_wthr_WindDirectionCode_northwest = 4,
		WeatherInformation_wthr_WindDirectionCode_northeast = 5,
		WeatherInformation_wthr_WindDirectionCode_southwest = 6,
		WeatherInformation_wthr_WindDirectionCode_southeast = 7,
	} wthr_WindDirectionCode;/* optional */
	INTEGER wthr_HumidityQuantity;/* optional */
	INTEGER wthr_PressureQuantity;/* optional */
	VisibleString wthr_SunriseTimeGeneralizedTime;/* optional */
	VisibleString wthr_SunsetTimeGeneralizedTime;/* optional */
};
#ifndef STRUC_WeatherInformation
#define STRUC_WeatherInformation
typedef struct WeatherInformation WeatherInformation;

#endif

ASN1_CPPLINK int ASN1_Print_WeatherInformation(WeatherInformation* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_WeatherInformation_wthr_ForecastOrActualCode(ASN1WorkSpace* workspace, WeatherInformation* value, ENUMERATED user_value);
ASN1_CPPLINK int ASN1_SET_WeatherInformation_wthr_TemperatureQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_WeatherInformation_wthr_HighTemperatureQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_WeatherInformation_wthr_LowTemperatureQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_WeatherInformation_wthr_SpecialConditions(ASN1WorkSpace* workspace, WeatherInformation* value, ASNUINT8* user_value, ASNUINT32L user_value_length);
ASN1_CPPLINK int ASN1_SET_WeatherInformation_wthr_SpecialConditionsOther(ASN1WorkSpace* workspace, WeatherInformation* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_WeatherInformation_wthr_ProbabilityPercent(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_WeatherInformation_wthr_VisibilityQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_WeatherInformation_wthr_WindSpeedQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_WeatherInformation_wthr_WindDirectionCode(ASN1WorkSpace* workspace, WeatherInformation* value, ENUMERATED user_value);
ASN1_CPPLINK int ASN1_SET_WeatherInformation_wthr_HumidityQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_WeatherInformation_wthr_PressureQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_WeatherInformation_wthr_SunriseTimeGeneralizedTime(ASN1WorkSpace* workspace, WeatherInformation* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_WeatherInformation_wthr_SunsetTimeGeneralizedTime(ASN1WorkSpace* workspace, WeatherInformation* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_GET_WeatherInformation_wthr_ForecastOrActualCode(ASN1WorkSpace* workspace, WeatherInformation* value, ENUMERATED* user_value);
ASN1_CPPLINK int ASN1_GET_WeatherInformation_wthr_TemperatureQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_WeatherInformation_wthr_HighTemperatureQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_WeatherInformation_wthr_LowTemperatureQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_WeatherInformation_wthr_SpecialConditions(ASN1WorkSpace* workspace, WeatherInformation* value, ASNUINT8** user_value, ASNUINT32L* user_value_length);
ASN1_CPPLINK int ASN1_GET_WeatherInformation_wthr_SpecialConditionsOther(ASN1WorkSpace* workspace, WeatherInformation* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_WeatherInformation_wthr_ProbabilityPercent(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_WeatherInformation_wthr_VisibilityQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_WeatherInformation_wthr_WindSpeedQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_WeatherInformation_wthr_WindDirectionCode(ASN1WorkSpace* workspace, WeatherInformation* value, ENUMERATED* user_value);
ASN1_CPPLINK int ASN1_GET_WeatherInformation_wthr_HumidityQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_WeatherInformation_wthr_PressureQuantity(ASN1WorkSpace* workspace, WeatherInformation* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_WeatherInformation_wthr_SunriseTimeGeneralizedTime(ASN1WorkSpace* workspace, WeatherInformation* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_WeatherInformation_wthr_SunsetTimeGeneralizedTime(ASN1WorkSpace* workspace, WeatherInformation* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_BER_Enc_WeatherInformation(ASN1WorkSpace* workspace, WeatherInformation* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_WeatherInformation(ASN1WorkSpace* workspace, WeatherInformation* value, int length, ASN1TagType tagFlag);

/********************************************************
*WeatherInformationRequest                              *
********************************************************/
#ifndef STRUC_WeatherInformationRequest
#define STRUC_WeatherInformationRequest
typedef UTF8Str WeatherInformationRequest;
#endif

ASN1_CPPLINK int ASN1_Print_WeatherInformationRequest(WeatherInformationRequest* value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_WeatherInformationRequest(ASN1WorkSpace* workspace, WeatherInformationRequest* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_WeatherInformationRequest(ASN1WorkSpace* workspace, WeatherInformationRequest* value, int length, ASN1TagType tagFlag);

/********************************************************
*WeatherInformationResponse                             *
********************************************************/

#ifndef STRUC_WeatherInformation
#define STRUC_WeatherInformation
typedef struct WeatherInformation WeatherInformation;
#endif
#ifndef STRUC_WeatherInformationResponse
#define STRUC_WeatherInformationResponse
typedef ASN1List WeatherInformationResponse;
#endif
ASN1_CPPLINK int ASN1_Print_WeatherInformationResponse(WeatherInformationResponse* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_WeatherInformationResponse_WeatherInformationResponse_pdata(ASN1WorkSpace* workspace, WeatherInformationResponse* value, WeatherInformation* user_value);
ASN1_CPPLINK int ASN1_GET_WeatherInformationResponse_WeatherInformationResponse_pdata(ASN1WorkSpace* workspace, WeatherInformationResponse* value, WeatherInformation** user_value);
ASN1_CPPLINK int ASN1_BER_Enc_WeatherInformationResponse(ASN1WorkSpace* workspace, WeatherInformationResponse* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_WeatherInformationResponse(ASN1WorkSpace* workspace, WeatherInformationResponse* value, int length, ASN1TagType tagFlag);

/********************************************************
*LinkRoadwayGeometry                                    *
********************************************************/
struct LinkRoadwayGeometry {
	int DEF_LinkRoadwayGeometry_link_BiginNodeLatitudeLocation;
	int DEF_LinkRoadwayGeometry_link_BeginNodeLongitudeLocation;
	int DEF_LinkRoadwayGeometry_link_EndNodeLatitudeLocation;
	int DEF_LinkRoadwayGeometry_link_EndNodeLongitudeLocation;
	int DEF_LinkRoadwayGeometry_tfmg_LinkHeigthRestrictionQunatity;
	int DEF_LinkRoadwayGeometry_tfmg_LinkLeftShoulderWidthQuantity;
	int DEF_LinkRoadwayGeometry_tfmg_LinkLengthRestrictionQuatity;
	int DEF_LinkRoadwayGeometry_tfmg_LinkRightShoulderWidthQuantity;
	UTF8Str link_BeginNodeIdNumber;
	INTEGER link_BiginNodeLatitudeLocation;/* optional */
	INTEGER link_BeginNodeLongitudeLocation;/* optional */
	UTF8Str link_EndNodeIdNumber;
	INTEGER link_EndNodeLatitudeLocation;/* optional */
	INTEGER link_EndNodeLongitudeLocation;/* optional */
	UTF8Str link_JurisdictionText;
	// other_no_additional_information_required = 0
	// other_additional_information_required = 1
	// expressway = 2
	// major_arterial = 3
	// minor_arterial = 4
	// detour = 5
	// military = 6
	// tunnel = 7
	// frontage = 8
	BITSTRING link_TypeCode;
	UTF8Str link_NameText;
	INTEGER link_LengthQuantity;
	// other_no_additional_information_required = 0
	// other_additional_information_required = 1
	// concrete = 2
	// asphalt = 3
	// grooved_concrete = 4
	// steel_grid = 5
	// gravel = 6
	// dirt = 7
	// temporary = 8
	// anti_slippery = 9
	BITSTRING link_PavementTypeCode;
	INTEGER tfmg_LinkHeigthRestrictionQunatity;/* optional */
	INTEGER tfmg_LinkLeftShoulderWidthQuantity;/* optional */
	INTEGER tfmg_LinkLengthRestrictionQuatity;/* optional */
	enum {
		LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_opengrass = 0,
		LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_opensand = 1,
		LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_concrete_barrier_with_visibility_screens = 2,
		LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_separate_roadways = 3,
		LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_no_separation = 4,
		LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_painted_median_no_access = 5,
		LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_painted_MedianLeft_Turns = 6,
		LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_concrete_barrier = 7,
		LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_guardrail = 8,
	} tfmg_LinkMedianTypeCode;
	INTEGER tfmg_LinkNumLanesNumber;
	INTEGER tfmg_LinkNumLanesOpenNumber;
	INTEGER tfmg_LinkRightShoulderWidthQuantity;/* optional */
};
#ifndef STRUC_LinkRoadwayGeometry
#define STRUC_LinkRoadwayGeometry
typedef struct LinkRoadwayGeometry LinkRoadwayGeometry;

#endif

ASN1_CPPLINK int ASN1_Print_LinkRoadwayGeometry(LinkRoadwayGeometry* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_LinkRoadwayGeometry_link_BeginNodeIdNumber(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_LinkRoadwayGeometry_link_BiginNodeLatitudeLocation(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_LinkRoadwayGeometry_link_BeginNodeLongitudeLocation(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_LinkRoadwayGeometry_link_EndNodeIdNumber(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_LinkRoadwayGeometry_link_EndNodeLatitudeLocation(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_LinkRoadwayGeometry_link_EndNodeLongitudeLocation(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_LinkRoadwayGeometry_link_JurisdictionText(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_LinkRoadwayGeometry_link_TypeCode(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASNUINT8* user_value, ASNUINT32L user_value_length);
ASN1_CPPLINK int ASN1_SET_LinkRoadwayGeometry_link_NameText(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_LinkRoadwayGeometry_link_LengthQuantity(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_LinkRoadwayGeometry_link_PavementTypeCode(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASNUINT8* user_value, ASNUINT32L user_value_length);
ASN1_CPPLINK int ASN1_SET_LinkRoadwayGeometry_tfmg_LinkHeigthRestrictionQunatity(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_LinkRoadwayGeometry_tfmg_LinkLeftShoulderWidthQuantity(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_LinkRoadwayGeometry_tfmg_LinkLengthRestrictionQuatity(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_LinkRoadwayGeometry_tfmg_LinkMedianTypeCode(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ENUMERATED user_value);
ASN1_CPPLINK int ASN1_SET_LinkRoadwayGeometry_tfmg_LinkNumLanesNumber(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_LinkRoadwayGeometry_tfmg_LinkNumLanesOpenNumber(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_LinkRoadwayGeometry_tfmg_LinkRightShoulderWidthQuantity(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_GET_LinkRoadwayGeometry_link_BeginNodeIdNumber(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_LinkRoadwayGeometry_link_BiginNodeLatitudeLocation(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_LinkRoadwayGeometry_link_BeginNodeLongitudeLocation(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_LinkRoadwayGeometry_link_EndNodeIdNumber(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_LinkRoadwayGeometry_link_EndNodeLatitudeLocation(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_LinkRoadwayGeometry_link_EndNodeLongitudeLocation(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_LinkRoadwayGeometry_link_JurisdictionText(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_LinkRoadwayGeometry_link_TypeCode(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASNUINT8** user_value, ASNUINT32L* user_value_length);
ASN1_CPPLINK int ASN1_GET_LinkRoadwayGeometry_link_NameText(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_LinkRoadwayGeometry_link_LengthQuantity(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_LinkRoadwayGeometry_link_PavementTypeCode(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASNUINT8** user_value, ASNUINT32L* user_value_length);
ASN1_CPPLINK int ASN1_GET_LinkRoadwayGeometry_tfmg_LinkHeigthRestrictionQunatity(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_LinkRoadwayGeometry_tfmg_LinkLeftShoulderWidthQuantity(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_LinkRoadwayGeometry_tfmg_LinkLengthRestrictionQuatity(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_LinkRoadwayGeometry_tfmg_LinkMedianTypeCode(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ENUMERATED* user_value);
ASN1_CPPLINK int ASN1_GET_LinkRoadwayGeometry_tfmg_LinkNumLanesNumber(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_LinkRoadwayGeometry_tfmg_LinkNumLanesOpenNumber(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_LinkRoadwayGeometry_tfmg_LinkRightShoulderWidthQuantity(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_BER_Enc_LinkRoadwayGeometry(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_LinkRoadwayGeometry(ASN1WorkSpace* workspace, LinkRoadwayGeometry* value, int length, ASN1TagType tagFlag);

/********************************************************
*LinkRoadwayGeometryRequest                             *
********************************************************/
#ifndef STRUC_LinkRoadwayGeometryRequest
#define STRUC_LinkRoadwayGeometryRequest
typedef UTF8Str LinkRoadwayGeometryRequest;
#endif

ASN1_CPPLINK int ASN1_Print_LinkRoadwayGeometryRequest(LinkRoadwayGeometryRequest* value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_LinkRoadwayGeometryRequest(ASN1WorkSpace* workspace, LinkRoadwayGeometryRequest* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_LinkRoadwayGeometryRequest(ASN1WorkSpace* workspace, LinkRoadwayGeometryRequest* value, int length, ASN1TagType tagFlag);

/********************************************************
*LinkRoadwayGeometryResponse                            *
********************************************************/

#ifndef STRUC_LinkRoadwayGeometry
#define STRUC_LinkRoadwayGeometry
typedef struct LinkRoadwayGeometry LinkRoadwayGeometry;
#endif
#ifndef STRUC_LinkRoadwayGeometryResponse
#define STRUC_LinkRoadwayGeometryResponse
typedef ASN1List LinkRoadwayGeometryResponse;
#endif
ASN1_CPPLINK int ASN1_Print_LinkRoadwayGeometryResponse(LinkRoadwayGeometryResponse* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_LinkRoadwayGeometryResponse_LinkRoadwayGeometryResponse_pdata(ASN1WorkSpace* workspace, LinkRoadwayGeometryResponse* value, LinkRoadwayGeometry* user_value);
ASN1_CPPLINK int ASN1_GET_LinkRoadwayGeometryResponse_LinkRoadwayGeometryResponse_pdata(ASN1WorkSpace* workspace, LinkRoadwayGeometryResponse* value, LinkRoadwayGeometry** user_value);
ASN1_CPPLINK int ASN1_BER_Enc_LinkRoadwayGeometryResponse(ASN1WorkSpace* workspace, LinkRoadwayGeometryResponse* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_LinkRoadwayGeometryResponse(ASN1WorkSpace* workspace, LinkRoadwayGeometryResponse* value, int length, ASN1TagType tagFlag);

/********************************************************
*ProbeVehicleDetection                                  *
********************************************************/
struct ProbeVehicleDetection {
	int DEF_ProbeVehicleDetection_vpbd_VehicleAverageSpeedRate;
	int DEF_ProbeVehicleDetection_vpbd_AviReaderIdNumber;
	int DEF_ProbeVehicleDetection_vpbd_AviReaderLocationLatitude;
	int DEF_ProbeVehicleDetection_vpbd_AviReaderLocationLongitude;
	int DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorIdNumber;
	int DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorLatitude;
	int DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorLongitude;
	UTF8Str vpbd_VehicleIdNumber;
	enum {
		ProbeVehicleDetection_vpbd_VehicleClass_other_no_additional_information_required = 0,
		ProbeVehicleDetection_vpbd_VehicleClass_other_additional_information_required = 1,
		ProbeVehicleDetection_vpbd_VehicleClass_bus_vehicle = 2,
		ProbeVehicleDetection_vpbd_VehicleClass_taxi_vehicle = 3,
		ProbeVehicleDetection_vpbd_VehicleClass_passenger_cars = 4,
		ProbeVehicleDetection_vpbd_VehicleClass_emergency_vehicles = 5,
		ProbeVehicleDetection_vpbd_VehicleClass_official_vehicle = 6,
	} vpbd_VehicleClass;
	VisibleString vpbd_VehicleTimeInGeneralizedTime;
	VisibleString vpbd_VehicleTimeOutGeneralizedTime;
	INTEGER vpbd_VehicleTravelTimeTime;
	INTEGER vpbd_VehicleAverageSpeedRate;/* optional */
	UTF8Str vpbd_AviReaderIdNumber;/* optional */
	INTEGER vpbd_AviReaderLocationLatitude;/* optional */
	INTEGER vpbd_AviReaderLocationLongitude;/* optional */
	UTF8Str vpbd_ReferenceLocatorIdNumber;/* optional */
	INTEGER vpbd_ReferenceLocatorLatitude;/* optional */
	INTEGER vpbd_ReferenceLocatorLongitude;/* optional */
};
#ifndef STRUC_ProbeVehicleDetection
#define STRUC_ProbeVehicleDetection
typedef struct ProbeVehicleDetection ProbeVehicleDetection;

#endif

ASN1_CPPLINK int ASN1_Print_ProbeVehicleDetection(ProbeVehicleDetection* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_ProbeVehicleDetection_vpbd_VehicleIdNumber(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_ProbeVehicleDetection_vpbd_VehicleClass(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ENUMERATED user_value);
ASN1_CPPLINK int ASN1_SET_ProbeVehicleDetection_vpbd_VehicleTimeInGeneralizedTime(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_ProbeVehicleDetection_vpbd_VehicleTimeOutGeneralizedTime(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_ProbeVehicleDetection_vpbd_VehicleTravelTimeTime(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_ProbeVehicleDetection_vpbd_VehicleAverageSpeedRate(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_ProbeVehicleDetection_vpbd_AviReaderIdNumber(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_ProbeVehicleDetection_vpbd_AviReaderLocationLatitude(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_ProbeVehicleDetection_vpbd_AviReaderLocationLongitude(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_ProbeVehicleDetection_vpbd_ReferenceLocatorIdNumber(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_ProbeVehicleDetection_vpbd_ReferenceLocatorLatitude(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_ProbeVehicleDetection_vpbd_ReferenceLocatorLongitude(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_GET_ProbeVehicleDetection_vpbd_VehicleIdNumber(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_ProbeVehicleDetection_vpbd_VehicleClass(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ENUMERATED* user_value);
ASN1_CPPLINK int ASN1_GET_ProbeVehicleDetection_vpbd_VehicleTimeInGeneralizedTime(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_ProbeVehicleDetection_vpbd_VehicleTimeOutGeneralizedTime(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_ProbeVehicleDetection_vpbd_VehicleTravelTimeTime(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_ProbeVehicleDetection_vpbd_VehicleAverageSpeedRate(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_ProbeVehicleDetection_vpbd_AviReaderIdNumber(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_ProbeVehicleDetection_vpbd_AviReaderLocationLatitude(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_ProbeVehicleDetection_vpbd_AviReaderLocationLongitude(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_ProbeVehicleDetection_vpbd_ReferenceLocatorIdNumber(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_ProbeVehicleDetection_vpbd_ReferenceLocatorLatitude(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_ProbeVehicleDetection_vpbd_ReferenceLocatorLongitude(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_BER_Enc_ProbeVehicleDetection(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_ProbeVehicleDetection(ASN1WorkSpace* workspace, ProbeVehicleDetection* value, int length, ASN1TagType tagFlag);

/********************************************************
*ProbeVehicleDetectionRequest                           *
********************************************************/
#ifndef STRUC_ProbeVehicleDetectionRequest
#define STRUC_ProbeVehicleDetectionRequest
typedef UTF8Str ProbeVehicleDetectionRequest;
#endif

ASN1_CPPLINK int ASN1_Print_ProbeVehicleDetectionRequest(ProbeVehicleDetectionRequest* value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_ProbeVehicleDetectionRequest(ASN1WorkSpace* workspace, ProbeVehicleDetectionRequest* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_ProbeVehicleDetectionRequest(ASN1WorkSpace* workspace, ProbeVehicleDetectionRequest* value, int length, ASN1TagType tagFlag);

/********************************************************
*ProbeVehicleDetectionResponse                          *
********************************************************/

#ifndef STRUC_ProbeVehicleDetection
#define STRUC_ProbeVehicleDetection
typedef struct ProbeVehicleDetection ProbeVehicleDetection;
#endif
#ifndef STRUC_ProbeVehicleDetectionResponse
#define STRUC_ProbeVehicleDetectionResponse
typedef ASN1List ProbeVehicleDetectionResponse;
#endif
ASN1_CPPLINK int ASN1_Print_ProbeVehicleDetectionResponse(ProbeVehicleDetectionResponse* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_ProbeVehicleDetectionResponse_ProbeVehicleDetectionResponse_pdata(ASN1WorkSpace* workspace, ProbeVehicleDetectionResponse* value, ProbeVehicleDetection* user_value);
ASN1_CPPLINK int ASN1_GET_ProbeVehicleDetectionResponse_ProbeVehicleDetectionResponse_pdata(ASN1WorkSpace* workspace, ProbeVehicleDetectionResponse* value, ProbeVehicleDetection** user_value);
ASN1_CPPLINK int ASN1_BER_Enc_ProbeVehicleDetectionResponse(ASN1WorkSpace* workspace, ProbeVehicleDetectionResponse* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_ProbeVehicleDetectionResponse(ASN1WorkSpace* workspace, ProbeVehicleDetectionResponse* value, int length, ASN1TagType tagFlag);

/********************************************************
*DetectorCollection                                     *
********************************************************/
struct DetectorCollection {
	int DEF_DetectorCollection_tfdt_VolumeRate;
	int DEF_DetectorCollection_tfdt_VehicleQueueLengthQuantity;
	UTF8Str tfdt_DetectorIdNumber;
	VisibleString tfdt_DetectorTimeGeneralizedTime;
	INTEGER tfdt_SpeedRate;
	INTEGER tfdt_VolumeRate;/* optional */
	INTEGER tfdt_OccupancyPercent;
	INTEGER tfdt_VehicleQueueLengthQuantity;/* optional */
};
#ifndef STRUC_DetectorCollection
#define STRUC_DetectorCollection
typedef struct DetectorCollection DetectorCollection;

#endif

ASN1_CPPLINK int ASN1_Print_DetectorCollection(DetectorCollection* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_DetectorCollection_tfdt_DetectorIdNumber(ASN1WorkSpace* workspace, DetectorCollection* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_DetectorCollection_tfdt_DetectorTimeGeneralizedTime(ASN1WorkSpace* workspace, DetectorCollection* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_DetectorCollection_tfdt_SpeedRate(ASN1WorkSpace* workspace, DetectorCollection* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_DetectorCollection_tfdt_VolumeRate(ASN1WorkSpace* workspace, DetectorCollection* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_DetectorCollection_tfdt_OccupancyPercent(ASN1WorkSpace* workspace, DetectorCollection* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_DetectorCollection_tfdt_VehicleQueueLengthQuantity(ASN1WorkSpace* workspace, DetectorCollection* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_GET_DetectorCollection_tfdt_DetectorIdNumber(ASN1WorkSpace* workspace, DetectorCollection* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_DetectorCollection_tfdt_DetectorTimeGeneralizedTime(ASN1WorkSpace* workspace, DetectorCollection* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_DetectorCollection_tfdt_SpeedRate(ASN1WorkSpace* workspace, DetectorCollection* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_DetectorCollection_tfdt_VolumeRate(ASN1WorkSpace* workspace, DetectorCollection* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_DetectorCollection_tfdt_OccupancyPercent(ASN1WorkSpace* workspace, DetectorCollection* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_DetectorCollection_tfdt_VehicleQueueLengthQuantity(ASN1WorkSpace* workspace, DetectorCollection* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_BER_Enc_DetectorCollection(ASN1WorkSpace* workspace, DetectorCollection* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_DetectorCollection(ASN1WorkSpace* workspace, DetectorCollection* value, int length, ASN1TagType tagFlag);

/********************************************************
*DetectorCollectionRequest                              *
********************************************************/
#ifndef STRUC_DetectorCollectionRequest
#define STRUC_DetectorCollectionRequest
typedef UTF8Str DetectorCollectionRequest;
#endif

ASN1_CPPLINK int ASN1_Print_DetectorCollectionRequest(DetectorCollectionRequest* value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_DetectorCollectionRequest(ASN1WorkSpace* workspace, DetectorCollectionRequest* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_DetectorCollectionRequest(ASN1WorkSpace* workspace, DetectorCollectionRequest* value, int length, ASN1TagType tagFlag);

/********************************************************
*DetectorCollectionResponse                             *
********************************************************/

#ifndef STRUC_DetectorCollection
#define STRUC_DetectorCollection
typedef struct DetectorCollection DetectorCollection;
#endif
#ifndef STRUC_DetectorCollectionResponse
#define STRUC_DetectorCollectionResponse
typedef ASN1List DetectorCollectionResponse;
#endif
ASN1_CPPLINK int ASN1_Print_DetectorCollectionResponse(DetectorCollectionResponse* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_DetectorCollectionResponse_DetectorCollectionResponse_pdata(ASN1WorkSpace* workspace, DetectorCollectionResponse* value, DetectorCollection* user_value);
ASN1_CPPLINK int ASN1_GET_DetectorCollectionResponse_DetectorCollectionResponse_pdata(ASN1WorkSpace* workspace, DetectorCollectionResponse* value, DetectorCollection** user_value);
ASN1_CPPLINK int ASN1_BER_Enc_DetectorCollectionResponse(ASN1WorkSpace* workspace, DetectorCollectionResponse* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_DetectorCollectionResponse(ASN1WorkSpace* workspace, DetectorCollectionResponse* value, int length, ASN1TagType tagFlag);

/********************************************************
*ExtentionCommPDU                                       *
********************************************************/
struct ExtentionCommPDU {
	int DEF_ExtentionCommPDU_signature;
	int DEF_ExtentionCommPDU_payloadType;
	INTEGER index;
	INTEGER aid;
	GeneralizedTime deliveryStart;
	GeneralizedTime deliveryStop;
	BOOLEAN signature;/* optional */
	INTEGER payloadType;/* optional */
	OCTETSTRING payload;
};
#ifndef STRUC_ExtentionCommPDU
#define STRUC_ExtentionCommPDU
typedef struct ExtentionCommPDU ExtentionCommPDU;

#endif

ASN1_CPPLINK int ASN1_Print_ExtentionCommPDU(ExtentionCommPDU* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_ExtentionCommPDU_index(ASN1WorkSpace* workspace, ExtentionCommPDU* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_ExtentionCommPDU_aid(ASN1WorkSpace* workspace, ExtentionCommPDU* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_ExtentionCommPDU_deliveryStart(ASN1WorkSpace* workspace, ExtentionCommPDU* value, struct tm* user_value, ASNINT32 _TimeZoneInSecond, ASNINT32 _second, ASNINT32 _exponent);
ASN1_CPPLINK int ASN1_SET_ExtentionCommPDU_deliveryStop(ASN1WorkSpace* workspace, ExtentionCommPDU* value, struct tm* user_value, ASNINT32 _TimeZoneInSecond, ASNINT32 _second, ASNINT32 _exponent);
ASN1_CPPLINK int ASN1_SET_ExtentionCommPDU_signature(ASN1WorkSpace* workspace, ExtentionCommPDU* value, BOOLEAN user_value);
ASN1_CPPLINK int ASN1_SET_ExtentionCommPDU_payloadType(ASN1WorkSpace* workspace, ExtentionCommPDU* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_ExtentionCommPDU_payload(ASN1WorkSpace* workspace, ExtentionCommPDU* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_GET_ExtentionCommPDU_index(ASN1WorkSpace* workspace, ExtentionCommPDU* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_ExtentionCommPDU_aid(ASN1WorkSpace* workspace, ExtentionCommPDU* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_ExtentionCommPDU_deliveryStart(ASN1WorkSpace* workspace, ExtentionCommPDU* value, struct tm* user_value, ASNINT32* _TimeZoneInSecond, ASNINT32* _second, ASNINT32* _exponent);
ASN1_CPPLINK int ASN1_GET_ExtentionCommPDU_deliveryStop(ASN1WorkSpace* workspace, ExtentionCommPDU* value, struct tm* user_value, ASNINT32* _TimeZoneInSecond, ASNINT32* _second, ASNINT32* _exponent);
ASN1_CPPLINK int ASN1_GET_ExtentionCommPDU_signature(ASN1WorkSpace* workspace, ExtentionCommPDU* value, BOOLEAN* user_value);
ASN1_CPPLINK int ASN1_GET_ExtentionCommPDU_payloadType(ASN1WorkSpace* workspace, ExtentionCommPDU* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_ExtentionCommPDU_payload(ASN1WorkSpace* workspace, ExtentionCommPDU* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_BER_Enc_ExtentionCommPDU(ASN1WorkSpace* workspace, ExtentionCommPDU* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_ExtentionCommPDU(ASN1WorkSpace* workspace, ExtentionCommPDU* value, int length, ASN1TagType tagFlag);

/********************************************************
*ExtentionCommPDURequest                                *
********************************************************/
#ifndef STRUC_ExtentionCommPDURequest
#define STRUC_ExtentionCommPDURequest
typedef UTF8Str ExtentionCommPDURequest;
#endif

ASN1_CPPLINK int ASN1_Print_ExtentionCommPDURequest(ExtentionCommPDURequest* value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_ExtentionCommPDURequest(ASN1WorkSpace* workspace, ExtentionCommPDURequest* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_ExtentionCommPDURequest(ASN1WorkSpace* workspace, ExtentionCommPDURequest* value, int length, ASN1TagType tagFlag);

/********************************************************
*ExtentionCommPDUResponse                               *
********************************************************/

#ifndef STRUC_ExtentionCommPDU
#define STRUC_ExtentionCommPDU
typedef struct ExtentionCommPDU ExtentionCommPDU;
#endif
#ifndef STRUC_ExtentionCommPDUResponse
#define STRUC_ExtentionCommPDUResponse
typedef ASN1List ExtentionCommPDUResponse;
#endif
ASN1_CPPLINK int ASN1_Print_ExtentionCommPDUResponse(ExtentionCommPDUResponse* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_ExtentionCommPDUResponse_ExtentionCommPDUResponse_pdata(ASN1WorkSpace* workspace, ExtentionCommPDUResponse* value, ExtentionCommPDU* user_value);
ASN1_CPPLINK int ASN1_GET_ExtentionCommPDUResponse_ExtentionCommPDUResponse_pdata(ASN1WorkSpace* workspace, ExtentionCommPDUResponse* value, ExtentionCommPDU** user_value);
ASN1_CPPLINK int ASN1_BER_Enc_ExtentionCommPDUResponse(ASN1WorkSpace* workspace, ExtentionCommPDUResponse* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_ExtentionCommPDUResponse(ASN1WorkSpace* workspace, ExtentionCommPDUResponse* value, int length, ASN1TagType tagFlag);

/********************************************************
*ItsIso14827TestTimeFormat                              *
********************************************************/
enum ItsIso14827TestTimeFormat {
	ItsIso14827TestTimeFormat_full = 0,
	ItsIso14827TestTimeFormat_hhmmss = 1,
	ItsIso14827TestTimeFormat_hhmm = 2,
};
#ifndef STRUC_ItsIso14827TestTimeFormat
#define STRUC_ItsIso14827TestTimeFormat
typedef enum ItsIso14827TestTimeFormat ItsIso14827TestTimeFormat;
#endif

ASN1_CPPLINK int ASN1_Print_ItsIso14827TestTimeFormat(ItsIso14827TestTimeFormat* value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_ItsIso14827TestTimeFormat(ASN1WorkSpace* workspace, ItsIso14827TestTimeFormat* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_ItsIso14827TestTimeFormat(ASN1WorkSpace* workspace, ItsIso14827TestTimeFormat* value, int length, ASN1TagType tagFlag);

/********************************************************
*ItsIso14827TestTimeRequest                             *
********************************************************/
#ifndef STRUC_ItsIso14827TestTimeFormat
#define STRUC_ItsIso14827TestTimeFormat
typedef enum ItsIso14827TestTimeFormat;
#endif
struct ItsIso14827TestTimeRequest {
	ItsIso14827TestTimeFormat fmt;
};
#ifndef STRUC_ItsIso14827TestTimeRequest
#define STRUC_ItsIso14827TestTimeRequest
typedef struct ItsIso14827TestTimeRequest ItsIso14827TestTimeRequest;

#endif

ASN1_CPPLINK int ASN1_Print_ItsIso14827TestTimeRequest(ItsIso14827TestTimeRequest* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_ItsIso14827TestTimeRequest_fmt(ASN1WorkSpace* workspace, ItsIso14827TestTimeRequest* value, ENUMERATED user_value);
ASN1_CPPLINK int ASN1_GET_ItsIso14827TestTimeRequest_fmt(ASN1WorkSpace* workspace, ItsIso14827TestTimeRequest* value, ENUMERATED* user_value);
ASN1_CPPLINK int ASN1_BER_Enc_ItsIso14827TestTimeRequest(ASN1WorkSpace* workspace, ItsIso14827TestTimeRequest* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_ItsIso14827TestTimeRequest(ASN1WorkSpace* workspace, ItsIso14827TestTimeRequest* value, int length, ASN1TagType tagFlag);

/********************************************************
*ItsIso14827TestTimeResponse                            *
********************************************************/
struct ItsIso14827TestTimeResponse {
	UTF8Str str;
};
#ifndef STRUC_ItsIso14827TestTimeResponse
#define STRUC_ItsIso14827TestTimeResponse
typedef struct ItsIso14827TestTimeResponse ItsIso14827TestTimeResponse;

#endif

ASN1_CPPLINK int ASN1_Print_ItsIso14827TestTimeResponse(ItsIso14827TestTimeResponse* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_ItsIso14827TestTimeResponse_str(ASN1WorkSpace* workspace, ItsIso14827TestTimeResponse* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_GET_ItsIso14827TestTimeResponse_str(ASN1WorkSpace* workspace, ItsIso14827TestTimeResponse* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_BER_Enc_ItsIso14827TestTimeResponse(ASN1WorkSpace* workspace, ItsIso14827TestTimeResponse* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_ItsIso14827TestTimeResponse(ASN1WorkSpace* workspace, ItsIso14827TestTimeResponse* value, int length, ASN1TagType tagFlag);

#endif


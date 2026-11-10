/* Generated from adopted GitsnAsn1.c; MQTT private diagnostic symbols. */
#include "MqttTraceAliases.h"
#include <GitsnAsnUtil.h>
#include "MqttDiagnostics.h"
#define ASN1_CHECK_INTEGER(v,c) MqttDiag_check_integer(v,c,sizeof(c))
#define ASN1_CHECK_ENUMERATED(v,c) MqttDiag_check_enum(v,c,sizeof(c))
int ASN1_CHECK_AccelerationSet4Way(AccelerationSet4Way *value);
int ASN1_CHECK_AdvisorySpeed(AdvisorySpeed *value);
int ASN1_CHECK_AdvisorySpeedList(AdvisorySpeedList *value);
int ASN1_CHECK_AdvisorySpeed_regional(AdvisorySpeed_regional *value);
int ASN1_CHECK_BSMcoreData(BSMcoreData *value);
int ASN1_CHECK_BasicSafetyMessage(BasicSafetyMessage *value);
int ASN1_CHECK_BasicSafetyMessage_partII(BasicSafetyMessage_partII *value);
int ASN1_CHECK_BasicSafetyMessage_regional(BasicSafetyMessage_regional *value);
int ASN1_CHECK_BrakeSystemStatus(BrakeSystemStatus *value);
int ASN1_CHECK_Circle(Circle *value);
int ASN1_CHECK_ComputedLane(ComputedLane *value);
int ASN1_CHECK_ComputedLane_offsetXaxis(ComputedLane_offsetXaxis *value);
int ASN1_CHECK_ComputedLane_offsetYaxis(ComputedLane_offsetYaxis *value);
int ASN1_CHECK_ComputedLane_regional(ComputedLane_regional *value);
int ASN1_CHECK_ConnectionManeuverAssist(ConnectionManeuverAssist *value);
int ASN1_CHECK_ConnectionManeuverAssist_regional(ConnectionManeuverAssist_regional *value);
int ASN1_CHECK_DDateTime(DDateTime *value);
int ASN1_CHECK_EnabledLaneList(EnabledLaneList *value);
int ASN1_CHECK_EventOrSvcInfo_KOR(EventOrSvcInfo_KOR *value);
int ASN1_CHECK_EventOrSvcInfo_KOR_subtext(EventOrSvcInfo_KOR_subtext *value);
int ASN1_CHECK_EventOrSvcInfo_KOR_text(EventOrSvcInfo_KOR_text *value);
int ASN1_CHECK_ExitService(ExitService *value);
int ASN1_CHECK_ExitService_element(ExitService_element *value);
int ASN1_CHECK_ExitService_element_item(ExitService_element_item *value);
int ASN1_CHECK_GenericSignage(GenericSignage *value);
int ASN1_CHECK_GenericSignage_element(GenericSignage_element *value);
int ASN1_CHECK_GenericSignage_element_item(GenericSignage_element_item *value);
int ASN1_CHECK_GeographicalPath(GeographicalPath *value);
int ASN1_CHECK_GeographicalPath_KOR(GeographicalPath_KOR *value);
int ASN1_CHECK_GeographicalPath_KOR_regions(GeographicalPath_KOR_regions *value);
int ASN1_CHECK_GeographicalPath_description(GeographicalPath_description *value);
int ASN1_CHECK_GeographicalPath_regional(GeographicalPath_regional *value);
int ASN1_CHECK_GeometricProjection(GeometricProjection *value);
int ASN1_CHECK_GeometricProjection_regional(GeometricProjection_regional *value);
int ASN1_CHECK_ITIScodesAndText(ITIScodesAndText *value);
int ASN1_CHECK_ITIScodesAndText_element(ITIScodesAndText_element *value);
int ASN1_CHECK_ITIScodesAndText_element_item(ITIScodesAndText_element_item *value);
int ASN1_CHECK_IntersectionReferenceID(IntersectionReferenceID *value);
int ASN1_CHECK_IntersectionState(IntersectionState *value);
int ASN1_CHECK_IntersectionStateList(IntersectionStateList *value);
int ASN1_CHECK_IntersectionState_regional(IntersectionState_regional *value);
int ASN1_CHECK_LaneDataAttribute(LaneDataAttribute *value);
int ASN1_CHECK_LaneDataAttributeList(LaneDataAttributeList *value);
int ASN1_CHECK_LaneDataAttribute_regional(LaneDataAttribute_regional *value);
int ASN1_CHECK_LaneID(LaneID *value);
int ASN1_CHECK_ManeuverAssistList(ManeuverAssistList *value);
int ASN1_CHECK_MessageFrame(MessageFrame *value);
int ASN1_CHECK_MovementEvent(MovementEvent *value);
int ASN1_CHECK_MovementEventList(MovementEventList *value);
int ASN1_CHECK_MovementEvent_regional(MovementEvent_regional *value);
int ASN1_CHECK_MovementList(MovementList *value);
int ASN1_CHECK_MovementState(MovementState *value);
int ASN1_CHECK_MovementState_regional(MovementState_regional *value);
int ASN1_CHECK_NodeAttributeLL(NodeAttributeLL *value);
int ASN1_CHECK_NodeAttributeLLList(NodeAttributeLLList *value);
int ASN1_CHECK_NodeAttributeSetLL(NodeAttributeSetLL *value);
int ASN1_CHECK_NodeAttributeSetLL_regional(NodeAttributeSetLL_regional *value);
int ASN1_CHECK_NodeAttributeSetXY(NodeAttributeSetXY *value);
int ASN1_CHECK_NodeAttributeSetXY_regional(NodeAttributeSetXY_regional *value);
int ASN1_CHECK_NodeAttributeXY(NodeAttributeXY *value);
int ASN1_CHECK_NodeAttributeXYList(NodeAttributeXYList *value);
int ASN1_CHECK_NodeLL(NodeLL *value);
int ASN1_CHECK_NodeListLL(NodeListLL *value);
int ASN1_CHECK_NodeListXY(NodeListXY *value);
int ASN1_CHECK_NodeOffsetPointLL(NodeOffsetPointLL *value);
int ASN1_CHECK_NodeOffsetPointXY(NodeOffsetPointXY *value);
int ASN1_CHECK_NodeSetLL(NodeSetLL *value);
int ASN1_CHECK_NodeSetXY(NodeSetXY *value);
int ASN1_CHECK_NodeXY(NodeXY *value);
int ASN1_CHECK_Node_LL_24B(Node_LL_24B *value);
int ASN1_CHECK_Node_LL_28B(Node_LL_28B *value);
int ASN1_CHECK_Node_LL_32B(Node_LL_32B *value);
int ASN1_CHECK_Node_LL_36B(Node_LL_36B *value);
int ASN1_CHECK_Node_LL_44B(Node_LL_44B *value);
int ASN1_CHECK_Node_LL_48B(Node_LL_48B *value);
int ASN1_CHECK_Node_LLmD_64b(Node_LLmD_64b *value);
int ASN1_CHECK_Node_XY_20b(Node_XY_20b *value);
int ASN1_CHECK_Node_XY_22b(Node_XY_22b *value);
int ASN1_CHECK_Node_XY_24b(Node_XY_24b *value);
int ASN1_CHECK_Node_XY_26b(Node_XY_26b *value);
int ASN1_CHECK_Node_XY_28b(Node_XY_28b *value);
int ASN1_CHECK_Node_XY_32b(Node_XY_32b *value);
int ASN1_CHECK_OffsetSystem(OffsetSystem *value);
int ASN1_CHECK_OffsetSystem_offset(OffsetSystem_offset *value);
int ASN1_CHECK_ParkingCapacity_KOR(ParkingCapacity_KOR *value);
int ASN1_CHECK_ParkingZoneInformation_KOR(ParkingZoneInformation_KOR *value);
int ASN1_CHECK_ParkingZoneInformation_KOR_capacity(ParkingZoneInformation_KOR_capacity *value);
int ASN1_CHECK_PartIIcontent(PartIIcontent *value);
int ASN1_CHECK_Position3D(Position3D *value);
int ASN1_CHECK_Position3D_regional(Position3D_regional *value);
int ASN1_CHECK_PositionalAccuracy(PositionalAccuracy *value);
int ASN1_CHECK_RegionDescribedByID_KOR(RegionDescribedByID_KOR *value);
int ASN1_CHECK_RegionList(RegionList *value);
int ASN1_CHECK_RegionOffsets(RegionOffsets *value);
int ASN1_CHECK_RegionPointSet(RegionPointSet *value);
int ASN1_CHECK_RegionalExtension(RegionalExtension *value);
int ASN1_CHECK_RegulatorySpeedLimit(RegulatorySpeedLimit *value);
int ASN1_CHECK_RidingNotification_KOR(RidingNotification_KOR *value);
int ASN1_CHECK_RoadSegmentReferenceID(RoadSegmentReferenceID *value);
int ASN1_CHECK_RoadSignID(RoadSignID *value);
int ASN1_CHECK_SPAT(SPAT *value);
int ASN1_CHECK_SPAT_regional(SPAT_regional *value);
int ASN1_CHECK_SegmentAttributeLL(SegmentAttributeLL *value);
int ASN1_CHECK_SegmentAttributeLLList(SegmentAttributeLLList *value);
int ASN1_CHECK_SegmentAttributeXY(SegmentAttributeXY *value);
int ASN1_CHECK_SegmentAttributeXYList(SegmentAttributeXYList *value);
int ASN1_CHECK_ServiceAreaInformation_KOR(ServiceAreaInformation_KOR *value);
int ASN1_CHECK_ServiceAreaInformation_KOR_parkingInfo(ServiceAreaInformation_KOR_parkingInfo *value);
int ASN1_CHECK_ServiceAreaInformation_KOR_stationInfo(ServiceAreaInformation_KOR_stationInfo *value);
int ASN1_CHECK_ShapePointSet(ShapePointSet *value);
int ASN1_CHECK_SpeedLimit(SpeedLimit *value);
int ASN1_CHECK_SpeedLimitList(SpeedLimitList *value);
int ASN1_CHECK_SpeedLimit_element(SpeedLimit_element *value);
int ASN1_CHECK_SpeedLimit_element_item(SpeedLimit_element_item *value);
int ASN1_CHECK_StationInformation_KOR(StationInformation_KOR *value);
int ASN1_CHECK_TimeChangeDetails(TimeChangeDetails *value);
int ASN1_CHECK_TollgateLaneInformation_KOR(TollgateLaneInformation_KOR *value);
int ASN1_CHECK_TollgateLaneInformation_KOR_lanes(TollgateLaneInformation_KOR_lanes *value);
int ASN1_CHECK_TollgateLane_KOR(TollgateLane_KOR *value);
int ASN1_CHECK_TrafficLightStatusList_KOR(TrafficLightStatusList_KOR *value);
int ASN1_CHECK_TrafficLightStatusMessage(TrafficLightStatusMessage *value);
int ASN1_CHECK_TrafficLightStatus_KOR(TrafficLightStatus_KOR *value);
int ASN1_CHECK_TravelerDataFrame(TravelerDataFrame *value);
int ASN1_CHECK_TravelerDataFrameAdditionalInformation_KOR(TravelerDataFrameAdditionalInformation_KOR *value);
int ASN1_CHECK_TravelerDataFrameList(TravelerDataFrameList *value);
int ASN1_CHECK_TravelerDataFrame_content(TravelerDataFrame_content *value);
int ASN1_CHECK_TravelerDataFrame_msgId(TravelerDataFrame_msgId *value);
int ASN1_CHECK_TravelerDataFrame_regions(TravelerDataFrame_regions *value);
int ASN1_CHECK_TravelerInformation(TravelerInformation *value);
int ASN1_CHECK_TravelerInformation_KOR(TravelerInformation_KOR *value);
int ASN1_CHECK_TravelerInformation_KOR_additionalInfo(TravelerInformation_KOR_additionalInfo *value);
int ASN1_CHECK_TravelerInformation_regional(TravelerInformation_regional *value);
int ASN1_CHECK_ValidRegion(ValidRegion *value);
int ASN1_CHECK_ValidRegion_area(ValidRegion_area *value);
int ASN1_CHECK_VehicleSize(VehicleSize *value);
int ASN1_CHECK_WeatherInfo_KOR(WeatherInfo_KOR *value);
int ASN1_CHECK_WorkZone(WorkZone *value);
int ASN1_CHECK_WorkZone_element(WorkZone_element *value);
int ASN1_CHECK_WorkZone_element_item(WorkZone_element_item *value);
int ASN1_PER_UNAlign_Data_Dec_AccelerationSet4Way(ASN1WorkSpace *workspace, AccelerationSet4Way *value);
int ASN1_PER_UNAlign_Data_Dec_AdvisorySpeed(ASN1WorkSpace *workspace, AdvisorySpeed *value);
int ASN1_PER_UNAlign_Data_Dec_AdvisorySpeedList(ASN1WorkSpace *workspace, AdvisorySpeedList *value);
int ASN1_PER_UNAlign_Data_Dec_AdvisorySpeed_regional(ASN1WorkSpace *workspace, AdvisorySpeed_regional *value);
int ASN1_PER_UNAlign_Data_Dec_BSMcoreData(ASN1WorkSpace *workspace, BSMcoreData *value);
int ASN1_PER_UNAlign_Data_Dec_BasicSafetyMessage(ASN1WorkSpace *workspace, BasicSafetyMessage *value);
int ASN1_PER_UNAlign_Data_Dec_BasicSafetyMessage_partII(ASN1WorkSpace *workspace, BasicSafetyMessage_partII *value);
int ASN1_PER_UNAlign_Data_Dec_BasicSafetyMessage_regional(ASN1WorkSpace *workspace, BasicSafetyMessage_regional *value);
int ASN1_PER_UNAlign_Data_Dec_BrakeSystemStatus(ASN1WorkSpace *workspace, BrakeSystemStatus *value);
int ASN1_PER_UNAlign_Data_Dec_Circle(ASN1WorkSpace *workspace, Circle *value);
int ASN1_PER_UNAlign_Data_Dec_ComputedLane(ASN1WorkSpace *workspace, ComputedLane *value);
int ASN1_PER_UNAlign_Data_Dec_ComputedLane_offsetXaxis(ASN1WorkSpace *workspace, ComputedLane_offsetXaxis *value);
int ASN1_PER_UNAlign_Data_Dec_ComputedLane_offsetYaxis(ASN1WorkSpace *workspace, ComputedLane_offsetYaxis *value);
int ASN1_PER_UNAlign_Data_Dec_ComputedLane_regional(ASN1WorkSpace *workspace, ComputedLane_regional *value);
int ASN1_PER_UNAlign_Data_Dec_ConnectionManeuverAssist(ASN1WorkSpace *workspace, ConnectionManeuverAssist *value);
int ASN1_PER_UNAlign_Data_Dec_ConnectionManeuverAssist_regional(ASN1WorkSpace *workspace, ConnectionManeuverAssist_regional *value);
int ASN1_PER_UNAlign_Data_Dec_DDateTime(ASN1WorkSpace *workspace, DDateTime *value);
int ASN1_PER_UNAlign_Data_Dec_EnabledLaneList(ASN1WorkSpace *workspace, EnabledLaneList *value);
int ASN1_PER_UNAlign_Data_Dec_EventOrSvcInfo_KOR(ASN1WorkSpace *workspace, EventOrSvcInfo_KOR *value);
int ASN1_PER_UNAlign_Data_Dec_EventOrSvcInfo_KOR_subtext(ASN1WorkSpace *workspace, EventOrSvcInfo_KOR_subtext *value);
int ASN1_PER_UNAlign_Data_Dec_EventOrSvcInfo_KOR_text(ASN1WorkSpace *workspace, EventOrSvcInfo_KOR_text *value);
int ASN1_PER_UNAlign_Data_Dec_ExitService(ASN1WorkSpace *workspace, ExitService *value);
int ASN1_PER_UNAlign_Data_Dec_ExitService_element(ASN1WorkSpace *workspace, ExitService_element *value);
int ASN1_PER_UNAlign_Data_Dec_ExitService_element_item(ASN1WorkSpace *workspace, ExitService_element_item *value);
int ASN1_PER_UNAlign_Data_Dec_GenericSignage(ASN1WorkSpace *workspace, GenericSignage *value);
int ASN1_PER_UNAlign_Data_Dec_GenericSignage_element(ASN1WorkSpace *workspace, GenericSignage_element *value);
int ASN1_PER_UNAlign_Data_Dec_GenericSignage_element_item(ASN1WorkSpace *workspace, GenericSignage_element_item *value);
int ASN1_PER_UNAlign_Data_Dec_GeographicalPath(ASN1WorkSpace *workspace, GeographicalPath *value);
int ASN1_PER_UNAlign_Data_Dec_GeographicalPath_KOR(ASN1WorkSpace *workspace, GeographicalPath_KOR *value);
int ASN1_PER_UNAlign_Data_Dec_GeographicalPath_KOR_regions(ASN1WorkSpace *workspace, GeographicalPath_KOR_regions *value);
int ASN1_PER_UNAlign_Data_Dec_GeographicalPath_description(ASN1WorkSpace *workspace, GeographicalPath_description *value);
int ASN1_PER_UNAlign_Data_Dec_GeographicalPath_regional(ASN1WorkSpace *workspace, GeographicalPath_regional *value);
int ASN1_PER_UNAlign_Data_Dec_GeometricProjection(ASN1WorkSpace *workspace, GeometricProjection *value);
int ASN1_PER_UNAlign_Data_Dec_GeometricProjection_regional(ASN1WorkSpace *workspace, GeometricProjection_regional *value);
int ASN1_PER_UNAlign_Data_Dec_ITIScodesAndText(ASN1WorkSpace *workspace, ITIScodesAndText *value);
int ASN1_PER_UNAlign_Data_Dec_ITIScodesAndText_element(ASN1WorkSpace *workspace, ITIScodesAndText_element *value);
int ASN1_PER_UNAlign_Data_Dec_ITIScodesAndText_element_item(ASN1WorkSpace *workspace, ITIScodesAndText_element_item *value);
int ASN1_PER_UNAlign_Data_Dec_IntersectionReferenceID(ASN1WorkSpace *workspace, IntersectionReferenceID *value);
int ASN1_PER_UNAlign_Data_Dec_IntersectionState(ASN1WorkSpace *workspace, IntersectionState *value);
int ASN1_PER_UNAlign_Data_Dec_IntersectionStateList(ASN1WorkSpace *workspace, IntersectionStateList *value);
int ASN1_PER_UNAlign_Data_Dec_IntersectionState_regional(ASN1WorkSpace *workspace, IntersectionState_regional *value);
int ASN1_PER_UNAlign_Data_Dec_LaneDataAttribute(ASN1WorkSpace *workspace, LaneDataAttribute *value);
int ASN1_PER_UNAlign_Data_Dec_LaneDataAttributeList(ASN1WorkSpace *workspace, LaneDataAttributeList *value);
int ASN1_PER_UNAlign_Data_Dec_LaneDataAttribute_regional(ASN1WorkSpace *workspace, LaneDataAttribute_regional *value);
int ASN1_PER_UNAlign_Data_Dec_LaneID(ASN1WorkSpace *workspace, LaneID *value);
int ASN1_PER_UNAlign_Data_Dec_ManeuverAssistList(ASN1WorkSpace *workspace, ManeuverAssistList *value);
int ASN1_PER_UNAlign_Data_Dec_MessageFrame(ASN1WorkSpace *workspace, MessageFrame *value);
int ASN1_PER_UNAlign_Data_Dec_MovementEvent(ASN1WorkSpace *workspace, MovementEvent *value);
int ASN1_PER_UNAlign_Data_Dec_MovementEventList(ASN1WorkSpace *workspace, MovementEventList *value);
int ASN1_PER_UNAlign_Data_Dec_MovementEvent_regional(ASN1WorkSpace *workspace, MovementEvent_regional *value);
int ASN1_PER_UNAlign_Data_Dec_MovementList(ASN1WorkSpace *workspace, MovementList *value);
int ASN1_PER_UNAlign_Data_Dec_MovementState(ASN1WorkSpace *workspace, MovementState *value);
int ASN1_PER_UNAlign_Data_Dec_MovementState_regional(ASN1WorkSpace *workspace, MovementState_regional *value);
int ASN1_PER_UNAlign_Data_Dec_NodeAttributeLL(ASN1WorkSpace *workspace, NodeAttributeLL *value);
int ASN1_PER_UNAlign_Data_Dec_NodeAttributeLLList(ASN1WorkSpace *workspace, NodeAttributeLLList *value);
int ASN1_PER_UNAlign_Data_Dec_NodeAttributeSetLL(ASN1WorkSpace *workspace, NodeAttributeSetLL *value);
int ASN1_PER_UNAlign_Data_Dec_NodeAttributeSetLL_regional(ASN1WorkSpace *workspace, NodeAttributeSetLL_regional *value);
int ASN1_PER_UNAlign_Data_Dec_NodeAttributeSetXY(ASN1WorkSpace *workspace, NodeAttributeSetXY *value);
int ASN1_PER_UNAlign_Data_Dec_NodeAttributeSetXY_regional(ASN1WorkSpace *workspace, NodeAttributeSetXY_regional *value);
int ASN1_PER_UNAlign_Data_Dec_NodeAttributeXY(ASN1WorkSpace *workspace, NodeAttributeXY *value);
int ASN1_PER_UNAlign_Data_Dec_NodeAttributeXYList(ASN1WorkSpace *workspace, NodeAttributeXYList *value);
int ASN1_PER_UNAlign_Data_Dec_NodeLL(ASN1WorkSpace *workspace, NodeLL *value);
int ASN1_PER_UNAlign_Data_Dec_NodeListLL(ASN1WorkSpace *workspace, NodeListLL *value);
int ASN1_PER_UNAlign_Data_Dec_NodeListXY(ASN1WorkSpace *workspace, NodeListXY *value);
int ASN1_PER_UNAlign_Data_Dec_NodeOffsetPointLL(ASN1WorkSpace *workspace, NodeOffsetPointLL *value);
int ASN1_PER_UNAlign_Data_Dec_NodeOffsetPointXY(ASN1WorkSpace *workspace, NodeOffsetPointXY *value);
int ASN1_PER_UNAlign_Data_Dec_NodeSetLL(ASN1WorkSpace *workspace, NodeSetLL *value);
int ASN1_PER_UNAlign_Data_Dec_NodeSetXY(ASN1WorkSpace *workspace, NodeSetXY *value);
int ASN1_PER_UNAlign_Data_Dec_NodeXY(ASN1WorkSpace *workspace, NodeXY *value);
int ASN1_PER_UNAlign_Data_Dec_Node_LL_24B(ASN1WorkSpace *workspace, Node_LL_24B *value);
int ASN1_PER_UNAlign_Data_Dec_Node_LL_28B(ASN1WorkSpace *workspace, Node_LL_28B *value);
int ASN1_PER_UNAlign_Data_Dec_Node_LL_32B(ASN1WorkSpace *workspace, Node_LL_32B *value);
int ASN1_PER_UNAlign_Data_Dec_Node_LL_36B(ASN1WorkSpace *workspace, Node_LL_36B *value);
int ASN1_PER_UNAlign_Data_Dec_Node_LL_44B(ASN1WorkSpace *workspace, Node_LL_44B *value);
int ASN1_PER_UNAlign_Data_Dec_Node_LL_48B(ASN1WorkSpace *workspace, Node_LL_48B *value);
int ASN1_PER_UNAlign_Data_Dec_Node_LLmD_64b(ASN1WorkSpace *workspace, Node_LLmD_64b *value);
int ASN1_PER_UNAlign_Data_Dec_Node_XY_20b(ASN1WorkSpace *workspace, Node_XY_20b *value);
int ASN1_PER_UNAlign_Data_Dec_Node_XY_22b(ASN1WorkSpace *workspace, Node_XY_22b *value);
int ASN1_PER_UNAlign_Data_Dec_Node_XY_24b(ASN1WorkSpace *workspace, Node_XY_24b *value);
int ASN1_PER_UNAlign_Data_Dec_Node_XY_26b(ASN1WorkSpace *workspace, Node_XY_26b *value);
int ASN1_PER_UNAlign_Data_Dec_Node_XY_28b(ASN1WorkSpace *workspace, Node_XY_28b *value);
int ASN1_PER_UNAlign_Data_Dec_Node_XY_32b(ASN1WorkSpace *workspace, Node_XY_32b *value);
int ASN1_PER_UNAlign_Data_Dec_OffsetSystem(ASN1WorkSpace *workspace, OffsetSystem *value);
int ASN1_PER_UNAlign_Data_Dec_OffsetSystem_offset(ASN1WorkSpace *workspace, OffsetSystem_offset *value);
int ASN1_PER_UNAlign_Data_Dec_ParkingCapacity_KOR(ASN1WorkSpace *workspace, ParkingCapacity_KOR *value);
int ASN1_PER_UNAlign_Data_Dec_ParkingZoneInformation_KOR(ASN1WorkSpace *workspace, ParkingZoneInformation_KOR *value);
int ASN1_PER_UNAlign_Data_Dec_ParkingZoneInformation_KOR_capacity(ASN1WorkSpace *workspace, ParkingZoneInformation_KOR_capacity *value);
int ASN1_PER_UNAlign_Data_Dec_PartIIcontent(ASN1WorkSpace *workspace, PartIIcontent *value);
int ASN1_PER_UNAlign_Data_Dec_Position3D(ASN1WorkSpace *workspace, Position3D *value);
int ASN1_PER_UNAlign_Data_Dec_Position3D_regional(ASN1WorkSpace *workspace, Position3D_regional *value);
int ASN1_PER_UNAlign_Data_Dec_PositionalAccuracy(ASN1WorkSpace *workspace, PositionalAccuracy *value);
int ASN1_PER_UNAlign_Data_Dec_RegionDescribedByID_KOR(ASN1WorkSpace *workspace, RegionDescribedByID_KOR *value);
int ASN1_PER_UNAlign_Data_Dec_RegionList(ASN1WorkSpace *workspace, RegionList *value);
int ASN1_PER_UNAlign_Data_Dec_RegionOffsets(ASN1WorkSpace *workspace, RegionOffsets *value);
int ASN1_PER_UNAlign_Data_Dec_RegionPointSet(ASN1WorkSpace *workspace, RegionPointSet *value);
int ASN1_PER_UNAlign_Data_Dec_RegionalExtension(ASN1WorkSpace *workspace, RegionalExtension *value);
int ASN1_PER_UNAlign_Data_Dec_RegulatorySpeedLimit(ASN1WorkSpace *workspace, RegulatorySpeedLimit *value);
int ASN1_PER_UNAlign_Data_Dec_RidingNotification_KOR(ASN1WorkSpace *workspace, RidingNotification_KOR *value);
int ASN1_PER_UNAlign_Data_Dec_RoadSegmentReferenceID(ASN1WorkSpace *workspace, RoadSegmentReferenceID *value);
int ASN1_PER_UNAlign_Data_Dec_RoadSignID(ASN1WorkSpace *workspace, RoadSignID *value);
int ASN1_PER_UNAlign_Data_Dec_SPAT(ASN1WorkSpace *workspace, SPAT *value);
int ASN1_PER_UNAlign_Data_Dec_SPAT_regional(ASN1WorkSpace *workspace, SPAT_regional *value);
int ASN1_PER_UNAlign_Data_Dec_SegmentAttributeLL(ASN1WorkSpace *workspace, SegmentAttributeLL *value);
int ASN1_PER_UNAlign_Data_Dec_SegmentAttributeLLList(ASN1WorkSpace *workspace, SegmentAttributeLLList *value);
int ASN1_PER_UNAlign_Data_Dec_SegmentAttributeXY(ASN1WorkSpace *workspace, SegmentAttributeXY *value);
int ASN1_PER_UNAlign_Data_Dec_SegmentAttributeXYList(ASN1WorkSpace *workspace, SegmentAttributeXYList *value);
int ASN1_PER_UNAlign_Data_Dec_ServiceAreaInformation_KOR(ASN1WorkSpace *workspace, ServiceAreaInformation_KOR *value);
int ASN1_PER_UNAlign_Data_Dec_ServiceAreaInformation_KOR_parkingInfo(ASN1WorkSpace *workspace, ServiceAreaInformation_KOR_parkingInfo *value);
int ASN1_PER_UNAlign_Data_Dec_ServiceAreaInformation_KOR_stationInfo(ASN1WorkSpace *workspace, ServiceAreaInformation_KOR_stationInfo *value);
int ASN1_PER_UNAlign_Data_Dec_ShapePointSet(ASN1WorkSpace *workspace, ShapePointSet *value);
int ASN1_PER_UNAlign_Data_Dec_SpeedLimit(ASN1WorkSpace *workspace, SpeedLimit *value);
int ASN1_PER_UNAlign_Data_Dec_SpeedLimitList(ASN1WorkSpace *workspace, SpeedLimitList *value);
int ASN1_PER_UNAlign_Data_Dec_SpeedLimit_element(ASN1WorkSpace *workspace, SpeedLimit_element *value);
int ASN1_PER_UNAlign_Data_Dec_SpeedLimit_element_item(ASN1WorkSpace *workspace, SpeedLimit_element_item *value);
int ASN1_PER_UNAlign_Data_Dec_StationInformation_KOR(ASN1WorkSpace *workspace, StationInformation_KOR *value);
int ASN1_PER_UNAlign_Data_Dec_TimeChangeDetails(ASN1WorkSpace *workspace, TimeChangeDetails *value);
int ASN1_PER_UNAlign_Data_Dec_TollgateLaneInformation_KOR(ASN1WorkSpace *workspace, TollgateLaneInformation_KOR *value);
int ASN1_PER_UNAlign_Data_Dec_TollgateLaneInformation_KOR_lanes(ASN1WorkSpace *workspace, TollgateLaneInformation_KOR_lanes *value);
int ASN1_PER_UNAlign_Data_Dec_TollgateLane_KOR(ASN1WorkSpace *workspace, TollgateLane_KOR *value);
int ASN1_PER_UNAlign_Data_Dec_TrafficLightStatusList_KOR(ASN1WorkSpace *workspace, TrafficLightStatusList_KOR *value);
int ASN1_PER_UNAlign_Data_Dec_TrafficLightStatusMessage(ASN1WorkSpace *workspace, TrafficLightStatusMessage *value);
int ASN1_PER_UNAlign_Data_Dec_TrafficLightStatus_KOR(ASN1WorkSpace *workspace, TrafficLightStatus_KOR *value);
int ASN1_PER_UNAlign_Data_Dec_TravelerDataFrame(ASN1WorkSpace *workspace, TravelerDataFrame *value);
int ASN1_PER_UNAlign_Data_Dec_TravelerDataFrameAdditionalInformation_KOR(ASN1WorkSpace *workspace, TravelerDataFrameAdditionalInformation_KOR *value);
int ASN1_PER_UNAlign_Data_Dec_TravelerDataFrameList(ASN1WorkSpace *workspace, TravelerDataFrameList *value);
int ASN1_PER_UNAlign_Data_Dec_TravelerDataFrame_content(ASN1WorkSpace *workspace, TravelerDataFrame_content *value);
int ASN1_PER_UNAlign_Data_Dec_TravelerDataFrame_msgId(ASN1WorkSpace *workspace, TravelerDataFrame_msgId *value);
int ASN1_PER_UNAlign_Data_Dec_TravelerDataFrame_regions(ASN1WorkSpace *workspace, TravelerDataFrame_regions *value);
int ASN1_PER_UNAlign_Data_Dec_TravelerInformation(ASN1WorkSpace *workspace, TravelerInformation *value);
int ASN1_PER_UNAlign_Data_Dec_TravelerInformation_KOR(ASN1WorkSpace *workspace, TravelerInformation_KOR *value);
int ASN1_PER_UNAlign_Data_Dec_TravelerInformation_KOR_additionalInfo(ASN1WorkSpace *workspace, TravelerInformation_KOR_additionalInfo *value);
int ASN1_PER_UNAlign_Data_Dec_TravelerInformation_regional(ASN1WorkSpace *workspace, TravelerInformation_regional *value);
int ASN1_PER_UNAlign_Data_Dec_ValidRegion(ASN1WorkSpace *workspace, ValidRegion *value);
int ASN1_PER_UNAlign_Data_Dec_ValidRegion_area(ASN1WorkSpace *workspace, ValidRegion_area *value);
int ASN1_PER_UNAlign_Data_Dec_VehicleSize(ASN1WorkSpace *workspace, VehicleSize *value);
int ASN1_PER_UNAlign_Data_Dec_WeatherInfo_KOR(ASN1WorkSpace *workspace, WeatherInfo_KOR *value);
int ASN1_PER_UNAlign_Data_Dec_WorkZone(ASN1WorkSpace *workspace, WorkZone *value);
int ASN1_PER_UNAlign_Data_Dec_WorkZone_element(ASN1WorkSpace *workspace, WorkZone_element *value);
int ASN1_PER_UNAlign_Data_Dec_WorkZone_element_item(ASN1WorkSpace *workspace, WorkZone_element_item *value);
int ASN1_PER_UNAlign_Dec_AccelerationSet4Way(ASN1WorkSpace *workspace, AccelerationSet4Way *value);
int ASN1_PER_UNAlign_Dec_AdvisorySpeed(ASN1WorkSpace *workspace, AdvisorySpeed *value);
int ASN1_PER_UNAlign_Dec_AdvisorySpeedList(ASN1WorkSpace *workspace, AdvisorySpeedList *value);
int ASN1_PER_UNAlign_Dec_AdvisorySpeed_regional(ASN1WorkSpace *workspace, AdvisorySpeed_regional *value);
int ASN1_PER_UNAlign_Dec_BSMcoreData(ASN1WorkSpace *workspace, BSMcoreData *value);
int ASN1_PER_UNAlign_Dec_BasicSafetyMessage(ASN1WorkSpace *workspace, BasicSafetyMessage *value);
int ASN1_PER_UNAlign_Dec_BasicSafetyMessage_partII(ASN1WorkSpace *workspace, BasicSafetyMessage_partII *value);
int ASN1_PER_UNAlign_Dec_BasicSafetyMessage_regional(ASN1WorkSpace *workspace, BasicSafetyMessage_regional *value);
int ASN1_PER_UNAlign_Dec_BrakeSystemStatus(ASN1WorkSpace *workspace, BrakeSystemStatus *value);
int ASN1_PER_UNAlign_Dec_Circle(ASN1WorkSpace *workspace, Circle *value);
int ASN1_PER_UNAlign_Dec_ComputedLane(ASN1WorkSpace *workspace, ComputedLane *value);
int ASN1_PER_UNAlign_Dec_ComputedLane_offsetXaxis(ASN1WorkSpace *workspace, ComputedLane_offsetXaxis *value);
int ASN1_PER_UNAlign_Dec_ComputedLane_offsetYaxis(ASN1WorkSpace *workspace, ComputedLane_offsetYaxis *value);
int ASN1_PER_UNAlign_Dec_ComputedLane_regional(ASN1WorkSpace *workspace, ComputedLane_regional *value);
int ASN1_PER_UNAlign_Dec_ConnectionManeuverAssist(ASN1WorkSpace *workspace, ConnectionManeuverAssist *value);
int ASN1_PER_UNAlign_Dec_ConnectionManeuverAssist_regional(ASN1WorkSpace *workspace, ConnectionManeuverAssist_regional *value);
int ASN1_PER_UNAlign_Dec_DDateTime(ASN1WorkSpace *workspace, DDateTime *value);
int ASN1_PER_UNAlign_Dec_EnabledLaneList(ASN1WorkSpace *workspace, EnabledLaneList *value);
int ASN1_PER_UNAlign_Dec_EventOrSvcInfo_KOR(ASN1WorkSpace *workspace, EventOrSvcInfo_KOR *value);
int ASN1_PER_UNAlign_Dec_EventOrSvcInfo_KOR_subtext(ASN1WorkSpace *workspace, EventOrSvcInfo_KOR_subtext *value);
int ASN1_PER_UNAlign_Dec_EventOrSvcInfo_KOR_text(ASN1WorkSpace *workspace, EventOrSvcInfo_KOR_text *value);
int ASN1_PER_UNAlign_Dec_ExitService(ASN1WorkSpace *workspace, ExitService *value);
int ASN1_PER_UNAlign_Dec_ExitService_element(ASN1WorkSpace *workspace, ExitService_element *value);
int ASN1_PER_UNAlign_Dec_ExitService_element_item(ASN1WorkSpace *workspace, ExitService_element_item *value);
int ASN1_PER_UNAlign_Dec_GenericSignage(ASN1WorkSpace *workspace, GenericSignage *value);
int ASN1_PER_UNAlign_Dec_GenericSignage_element(ASN1WorkSpace *workspace, GenericSignage_element *value);
int ASN1_PER_UNAlign_Dec_GenericSignage_element_item(ASN1WorkSpace *workspace, GenericSignage_element_item *value);
int ASN1_PER_UNAlign_Dec_GeographicalPath(ASN1WorkSpace *workspace, GeographicalPath *value);
int ASN1_PER_UNAlign_Dec_GeographicalPath_KOR(ASN1WorkSpace *workspace, GeographicalPath_KOR *value);
int ASN1_PER_UNAlign_Dec_GeographicalPath_KOR_regions(ASN1WorkSpace *workspace, GeographicalPath_KOR_regions *value);
int ASN1_PER_UNAlign_Dec_GeographicalPath_description(ASN1WorkSpace *workspace, GeographicalPath_description *value);
int ASN1_PER_UNAlign_Dec_GeographicalPath_regional(ASN1WorkSpace *workspace, GeographicalPath_regional *value);
int ASN1_PER_UNAlign_Dec_GeometricProjection(ASN1WorkSpace *workspace, GeometricProjection *value);
int ASN1_PER_UNAlign_Dec_GeometricProjection_regional(ASN1WorkSpace *workspace, GeometricProjection_regional *value);
int ASN1_PER_UNAlign_Dec_ITIScodesAndText(ASN1WorkSpace *workspace, ITIScodesAndText *value);
int ASN1_PER_UNAlign_Dec_ITIScodesAndText_element(ASN1WorkSpace *workspace, ITIScodesAndText_element *value);
int ASN1_PER_UNAlign_Dec_ITIScodesAndText_element_item(ASN1WorkSpace *workspace, ITIScodesAndText_element_item *value);
int ASN1_PER_UNAlign_Dec_IntersectionReferenceID(ASN1WorkSpace *workspace, IntersectionReferenceID *value);
int ASN1_PER_UNAlign_Dec_IntersectionState(ASN1WorkSpace *workspace, IntersectionState *value);
int ASN1_PER_UNAlign_Dec_IntersectionStateList(ASN1WorkSpace *workspace, IntersectionStateList *value);
int ASN1_PER_UNAlign_Dec_IntersectionState_regional(ASN1WorkSpace *workspace, IntersectionState_regional *value);
int ASN1_PER_UNAlign_Dec_LaneDataAttribute(ASN1WorkSpace *workspace, LaneDataAttribute *value);
int ASN1_PER_UNAlign_Dec_LaneDataAttributeList(ASN1WorkSpace *workspace, LaneDataAttributeList *value);
int ASN1_PER_UNAlign_Dec_LaneDataAttribute_regional(ASN1WorkSpace *workspace, LaneDataAttribute_regional *value);
int ASN1_PER_UNAlign_Dec_LaneID(ASN1WorkSpace *workspace, LaneID *value);
int ASN1_PER_UNAlign_Dec_ManeuverAssistList(ASN1WorkSpace *workspace, ManeuverAssistList *value);
int ASN1_PER_UNAlign_Dec_MessageFrame(ASN1WorkSpace *workspace, MessageFrame *value);
int ASN1_PER_UNAlign_Dec_MovementEvent(ASN1WorkSpace *workspace, MovementEvent *value);
int ASN1_PER_UNAlign_Dec_MovementEventList(ASN1WorkSpace *workspace, MovementEventList *value);
int ASN1_PER_UNAlign_Dec_MovementEvent_regional(ASN1WorkSpace *workspace, MovementEvent_regional *value);
int ASN1_PER_UNAlign_Dec_MovementList(ASN1WorkSpace *workspace, MovementList *value);
int ASN1_PER_UNAlign_Dec_MovementState(ASN1WorkSpace *workspace, MovementState *value);
int ASN1_PER_UNAlign_Dec_MovementState_regional(ASN1WorkSpace *workspace, MovementState_regional *value);
int ASN1_PER_UNAlign_Dec_NodeAttributeLL(ASN1WorkSpace *workspace, NodeAttributeLL *value);
int ASN1_PER_UNAlign_Dec_NodeAttributeLLList(ASN1WorkSpace *workspace, NodeAttributeLLList *value);
int ASN1_PER_UNAlign_Dec_NodeAttributeSetLL(ASN1WorkSpace *workspace, NodeAttributeSetLL *value);
int ASN1_PER_UNAlign_Dec_NodeAttributeSetLL_regional(ASN1WorkSpace *workspace, NodeAttributeSetLL_regional *value);
int ASN1_PER_UNAlign_Dec_NodeAttributeSetXY(ASN1WorkSpace *workspace, NodeAttributeSetXY *value);
int ASN1_PER_UNAlign_Dec_NodeAttributeSetXY_regional(ASN1WorkSpace *workspace, NodeAttributeSetXY_regional *value);
int ASN1_PER_UNAlign_Dec_NodeAttributeXY(ASN1WorkSpace *workspace, NodeAttributeXY *value);
int ASN1_PER_UNAlign_Dec_NodeAttributeXYList(ASN1WorkSpace *workspace, NodeAttributeXYList *value);
int ASN1_PER_UNAlign_Dec_NodeLL(ASN1WorkSpace *workspace, NodeLL *value);
int ASN1_PER_UNAlign_Dec_NodeListLL(ASN1WorkSpace *workspace, NodeListLL *value);
int ASN1_PER_UNAlign_Dec_NodeListXY(ASN1WorkSpace *workspace, NodeListXY *value);
int ASN1_PER_UNAlign_Dec_NodeOffsetPointLL(ASN1WorkSpace *workspace, NodeOffsetPointLL *value);
int ASN1_PER_UNAlign_Dec_NodeOffsetPointXY(ASN1WorkSpace *workspace, NodeOffsetPointXY *value);
int ASN1_PER_UNAlign_Dec_NodeSetLL(ASN1WorkSpace *workspace, NodeSetLL *value);
int ASN1_PER_UNAlign_Dec_NodeSetXY(ASN1WorkSpace *workspace, NodeSetXY *value);
int ASN1_PER_UNAlign_Dec_NodeXY(ASN1WorkSpace *workspace, NodeXY *value);
int ASN1_PER_UNAlign_Dec_Node_LL_24B(ASN1WorkSpace *workspace, Node_LL_24B *value);
int ASN1_PER_UNAlign_Dec_Node_LL_28B(ASN1WorkSpace *workspace, Node_LL_28B *value);
int ASN1_PER_UNAlign_Dec_Node_LL_32B(ASN1WorkSpace *workspace, Node_LL_32B *value);
int ASN1_PER_UNAlign_Dec_Node_LL_36B(ASN1WorkSpace *workspace, Node_LL_36B *value);
int ASN1_PER_UNAlign_Dec_Node_LL_44B(ASN1WorkSpace *workspace, Node_LL_44B *value);
int ASN1_PER_UNAlign_Dec_Node_LL_48B(ASN1WorkSpace *workspace, Node_LL_48B *value);
int ASN1_PER_UNAlign_Dec_Node_LLmD_64b(ASN1WorkSpace *workspace, Node_LLmD_64b *value);
int ASN1_PER_UNAlign_Dec_Node_XY_20b(ASN1WorkSpace *workspace, Node_XY_20b *value);
int ASN1_PER_UNAlign_Dec_Node_XY_22b(ASN1WorkSpace *workspace, Node_XY_22b *value);
int ASN1_PER_UNAlign_Dec_Node_XY_24b(ASN1WorkSpace *workspace, Node_XY_24b *value);
int ASN1_PER_UNAlign_Dec_Node_XY_26b(ASN1WorkSpace *workspace, Node_XY_26b *value);
int ASN1_PER_UNAlign_Dec_Node_XY_28b(ASN1WorkSpace *workspace, Node_XY_28b *value);
int ASN1_PER_UNAlign_Dec_Node_XY_32b(ASN1WorkSpace *workspace, Node_XY_32b *value);
int ASN1_PER_UNAlign_Dec_OffsetSystem(ASN1WorkSpace *workspace, OffsetSystem *value);
int ASN1_PER_UNAlign_Dec_OffsetSystem_offset(ASN1WorkSpace *workspace, OffsetSystem_offset *value);
int ASN1_PER_UNAlign_Dec_ParkingCapacity_KOR(ASN1WorkSpace *workspace, ParkingCapacity_KOR *value);
int ASN1_PER_UNAlign_Dec_ParkingZoneInformation_KOR(ASN1WorkSpace *workspace, ParkingZoneInformation_KOR *value);
int ASN1_PER_UNAlign_Dec_ParkingZoneInformation_KOR_capacity(ASN1WorkSpace *workspace, ParkingZoneInformation_KOR_capacity *value);
int ASN1_PER_UNAlign_Dec_PartIIcontent(ASN1WorkSpace *workspace, PartIIcontent *value);
int ASN1_PER_UNAlign_Dec_Position3D(ASN1WorkSpace *workspace, Position3D *value);
int ASN1_PER_UNAlign_Dec_Position3D_regional(ASN1WorkSpace *workspace, Position3D_regional *value);
int ASN1_PER_UNAlign_Dec_PositionalAccuracy(ASN1WorkSpace *workspace, PositionalAccuracy *value);
int ASN1_PER_UNAlign_Dec_RegionDescribedByID_KOR(ASN1WorkSpace *workspace, RegionDescribedByID_KOR *value);
int ASN1_PER_UNAlign_Dec_RegionList(ASN1WorkSpace *workspace, RegionList *value);
int ASN1_PER_UNAlign_Dec_RegionOffsets(ASN1WorkSpace *workspace, RegionOffsets *value);
int ASN1_PER_UNAlign_Dec_RegionPointSet(ASN1WorkSpace *workspace, RegionPointSet *value);
int ASN1_PER_UNAlign_Dec_RegionalExtension(ASN1WorkSpace *workspace, RegionalExtension *value);
int ASN1_PER_UNAlign_Dec_RegulatorySpeedLimit(ASN1WorkSpace *workspace, RegulatorySpeedLimit *value);
int ASN1_PER_UNAlign_Dec_RidingNotification_KOR(ASN1WorkSpace *workspace, RidingNotification_KOR *value);
int ASN1_PER_UNAlign_Dec_RoadSegmentReferenceID(ASN1WorkSpace *workspace, RoadSegmentReferenceID *value);
int ASN1_PER_UNAlign_Dec_RoadSignID(ASN1WorkSpace *workspace, RoadSignID *value);
int ASN1_PER_UNAlign_Dec_SPAT(ASN1WorkSpace *workspace, SPAT *value);
int ASN1_PER_UNAlign_Dec_SPAT_regional(ASN1WorkSpace *workspace, SPAT_regional *value);
int ASN1_PER_UNAlign_Dec_SegmentAttributeLL(ASN1WorkSpace *workspace, SegmentAttributeLL *value);
int ASN1_PER_UNAlign_Dec_SegmentAttributeLLList(ASN1WorkSpace *workspace, SegmentAttributeLLList *value);
int ASN1_PER_UNAlign_Dec_SegmentAttributeXY(ASN1WorkSpace *workspace, SegmentAttributeXY *value);
int ASN1_PER_UNAlign_Dec_SegmentAttributeXYList(ASN1WorkSpace *workspace, SegmentAttributeXYList *value);
int ASN1_PER_UNAlign_Dec_ServiceAreaInformation_KOR(ASN1WorkSpace *workspace, ServiceAreaInformation_KOR *value);
int ASN1_PER_UNAlign_Dec_ServiceAreaInformation_KOR_parkingInfo(ASN1WorkSpace *workspace, ServiceAreaInformation_KOR_parkingInfo *value);
int ASN1_PER_UNAlign_Dec_ServiceAreaInformation_KOR_stationInfo(ASN1WorkSpace *workspace, ServiceAreaInformation_KOR_stationInfo *value);
int ASN1_PER_UNAlign_Dec_ShapePointSet(ASN1WorkSpace *workspace, ShapePointSet *value);
int ASN1_PER_UNAlign_Dec_SpeedLimit(ASN1WorkSpace *workspace, SpeedLimit *value);
int ASN1_PER_UNAlign_Dec_SpeedLimitList(ASN1WorkSpace *workspace, SpeedLimitList *value);
int ASN1_PER_UNAlign_Dec_SpeedLimit_element(ASN1WorkSpace *workspace, SpeedLimit_element *value);
int ASN1_PER_UNAlign_Dec_SpeedLimit_element_item(ASN1WorkSpace *workspace, SpeedLimit_element_item *value);
int ASN1_PER_UNAlign_Dec_StationInformation_KOR(ASN1WorkSpace *workspace, StationInformation_KOR *value);
int ASN1_PER_UNAlign_Dec_TimeChangeDetails(ASN1WorkSpace *workspace, TimeChangeDetails *value);
int ASN1_PER_UNAlign_Dec_TollgateLaneInformation_KOR(ASN1WorkSpace *workspace, TollgateLaneInformation_KOR *value);
int ASN1_PER_UNAlign_Dec_TollgateLaneInformation_KOR_lanes(ASN1WorkSpace *workspace, TollgateLaneInformation_KOR_lanes *value);
int ASN1_PER_UNAlign_Dec_TollgateLane_KOR(ASN1WorkSpace *workspace, TollgateLane_KOR *value);
int ASN1_PER_UNAlign_Dec_TrafficLightStatusList_KOR(ASN1WorkSpace *workspace, TrafficLightStatusList_KOR *value);
int ASN1_PER_UNAlign_Dec_TrafficLightStatusMessage(ASN1WorkSpace *workspace, TrafficLightStatusMessage *value);
int ASN1_PER_UNAlign_Dec_TrafficLightStatus_KOR(ASN1WorkSpace *workspace, TrafficLightStatus_KOR *value);
int ASN1_PER_UNAlign_Dec_TravelerDataFrame(ASN1WorkSpace *workspace, TravelerDataFrame *value);
int ASN1_PER_UNAlign_Dec_TravelerDataFrameAdditionalInformation_KOR(ASN1WorkSpace *workspace, TravelerDataFrameAdditionalInformation_KOR *value);
int ASN1_PER_UNAlign_Dec_TravelerDataFrameList(ASN1WorkSpace *workspace, TravelerDataFrameList *value);
int ASN1_PER_UNAlign_Dec_TravelerDataFrame_content(ASN1WorkSpace *workspace, TravelerDataFrame_content *value);
int ASN1_PER_UNAlign_Dec_TravelerDataFrame_msgId(ASN1WorkSpace *workspace, TravelerDataFrame_msgId *value);
int ASN1_PER_UNAlign_Dec_TravelerDataFrame_regions(ASN1WorkSpace *workspace, TravelerDataFrame_regions *value);
int ASN1_PER_UNAlign_Dec_TravelerInformation(ASN1WorkSpace *workspace, TravelerInformation *value);
int ASN1_PER_UNAlign_Dec_TravelerInformation_KOR(ASN1WorkSpace *workspace, TravelerInformation_KOR *value);
int ASN1_PER_UNAlign_Dec_TravelerInformation_KOR_additionalInfo(ASN1WorkSpace *workspace, TravelerInformation_KOR_additionalInfo *value);
int ASN1_PER_UNAlign_Dec_TravelerInformation_regional(ASN1WorkSpace *workspace, TravelerInformation_regional *value);
int ASN1_PER_UNAlign_Dec_ValidRegion(ASN1WorkSpace *workspace, ValidRegion *value);
int ASN1_PER_UNAlign_Dec_ValidRegion_area(ASN1WorkSpace *workspace, ValidRegion_area *value);
int ASN1_PER_UNAlign_Dec_VehicleSize(ASN1WorkSpace *workspace, VehicleSize *value);
int ASN1_PER_UNAlign_Dec_WeatherInfo_KOR(ASN1WorkSpace *workspace, WeatherInfo_KOR *value);
int ASN1_PER_UNAlign_Dec_WorkZone(ASN1WorkSpace *workspace, WorkZone *value);
int ASN1_PER_UNAlign_Dec_WorkZone_element(ASN1WorkSpace *workspace, WorkZone_element *value);
int ASN1_PER_UNAlign_Dec_WorkZone_element_item(ASN1WorkSpace *workspace, WorkZone_element_item *value);
int ASN1_CHECK_AccelerationSet4Way(AccelerationSet4Way *value)
{
	int ret = 0;

	unsigned char checkinfo_lon[] = { 
		0x02,0x82,0xF8,0x30,0x82,0x07,0xD1,0x00
	};
	unsigned char checkinfo_lat[] = { 
		0x02,0x82,0xF8,0x30,0x82,0x07,0xD1,0x00
	};
	unsigned char checkinfo_vert[] = { 
		0x02,0x81,0x81,0x7F,0x00
	};
	unsigned char checkinfo_yaw[] = { 
		0x02,0x82,0x80,0x01,0x82,0x7F,0xFF,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("lon", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->lon), checkinfo_lon);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("lat", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->lat), checkinfo_lat);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("vert", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->vert), checkinfo_vert);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("yaw", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->yaw), checkinfo_yaw);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_AdvisorySpeed(AdvisorySpeed *value)
{
	int ret = 0;

	unsigned char checkinfo_type[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_speed[] = { 
		0x02,0x00,0x82,0x01,0xF4,0x00
	};
	unsigned char checkinfo_confidence[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_distance[] = { 
		0x02,0x00,0x82,0x27,0x10,0x00
	};
	unsigned char checkinfo_class[] = { 
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_regional[] = { 
		0x02,0x01,0x04,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("type", 0);
	  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->type), checkinfo_type);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_AdvisorySpeed_speed == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("speed", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->speed), checkinfo_speed);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_AdvisorySpeed_confidence == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("confidence", 0);
		  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->confidence), checkinfo_confidence);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_AdvisorySpeed_distance == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("distance", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->distance), checkinfo_distance);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_AdvisorySpeed_class == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("class", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->class), checkinfo_class);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_AdvisorySpeed_regional == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_CHECK_AdvisorySpeed_regional(&(value->regional));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_AdvisorySpeedList(AdvisorySpeedList *value)
{
	int ret = 0;

	unsigned char checkinfo_AdvisorySpeedList[] = { 
		0x02,0x01,0x10,0x00
	};
	unsigned char checkinfo_AdvisorySpeedList_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_AdvisorySpeed(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_AdvisorySpeed_regional(AdvisorySpeed_regional *value)
{
	int ret = 0;

	unsigned char checkinfo_AdvisorySpeed_regional[] = { 
		0x02,0x01,0x04,0x00
	};
	unsigned char checkinfo_AdvisorySpeed_regional_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_RegionalExtension(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_BSMcoreData(BSMcoreData *value)
{
	int ret = 0;

	unsigned char checkinfo_msgCnt[] = { 
		0x02,0x00,0x7F,0x00
	};
	unsigned char checkinfo_id[] = { 
		0x02,0x04,0x04,0x00
	};
	unsigned char checkinfo_secMark[] = { 
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_lat[] = { 
		0x02,0x84,0xCA,0x5B,0x17,0x00,0x84,0x35,0xA4,0xE9,0x01,0x00
	};
	unsigned char checkinfo_lon[] = { 
		0x02,0x84,0x94,0xB6,0x2E,0x01,0x84,0x6B,0x49,0xD2,0x01,0x00
	};
	unsigned char checkinfo_elev[] = { 
		0x02,0x82,0xF0,0x00,0x83,0x00,0xEF,0xFF,0x00
	};
	unsigned char checkinfo_accuracy[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_transmission[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_speed[] = { 
		0x02,0x00,0x82,0x1F,0xFF,0x00
	};
	unsigned char checkinfo_heading[] = { 
		0x02,0x00,0x82,0x70,0x80,0x00
	};
	unsigned char checkinfo_angle[] = { 
		0x02,0x81,0x82,0x7F,0x00
	};
	unsigned char checkinfo_accelSet[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_brakes[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_size[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("msgCnt", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->msgCnt), checkinfo_msgCnt);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("id", 0);
	  ret=ASN1_CHECK_OCTETSTRING(&(value->id), checkinfo_id);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("secMark", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->secMark), checkinfo_secMark);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("lat", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->lat), checkinfo_lat);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("lon", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->lon), checkinfo_lon);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("elev", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->elev), checkinfo_elev);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("accuracy", 0);
	  ret=ASN1_CHECK_PositionalAccuracy(value->accuracy);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("transmission", 0);
	  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->transmission), checkinfo_transmission);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("speed", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->speed), checkinfo_speed);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("heading", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->heading), checkinfo_heading);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("angle", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->angle), checkinfo_angle);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("accelSet", 0);
	  ret=ASN1_CHECK_AccelerationSet4Way(value->accelSet);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("brakes", 0);
	  ret=ASN1_CHECK_BrakeSystemStatus(value->brakes);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("size", 0);
	  ret=ASN1_CHECK_VehicleSize(value->size);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_BasicSafetyMessage(BasicSafetyMessage *value)
{
	int ret = 0;

	unsigned char checkinfo_coreData[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_partII[] = { 
		0x02,0x01,0x08,0x00
	};
	unsigned char checkinfo_regional[] = { 
		0x02,0x01,0x04,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("coreData", 0);
	  ret=ASN1_CHECK_BSMcoreData(value->coreData);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_BasicSafetyMessage_partII == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("partII", 0);
		  ret=ASN1_CHECK_BasicSafetyMessage_partII(&(value->partII));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_BasicSafetyMessage_regional == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_CHECK_BasicSafetyMessage_regional(&(value->regional));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_BasicSafetyMessage_partII(BasicSafetyMessage_partII *value)
{
	int ret = 0;

	unsigned char checkinfo_BasicSafetyMessage_partII[] = { 
		0x02,0x01,0x08,0x00
	};
	unsigned char checkinfo_BasicSafetyMessage_partII_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_PartIIcontent(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_BasicSafetyMessage_regional(BasicSafetyMessage_regional *value)
{
	int ret = 0;

	unsigned char checkinfo_BasicSafetyMessage_regional[] = { 
		0x02,0x01,0x04,0x00
	};
	unsigned char checkinfo_BasicSafetyMessage_regional_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_RegionalExtension(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_BrakeSystemStatus(BrakeSystemStatus *value)
{
	int ret = 0;

	unsigned char checkinfo_wheelBrakes[] = { 
		0x02,0x05,0x05,0x00
	};
	unsigned char checkinfo_traction[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_abs[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_scs[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_brakeBoost[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_auxBrakes[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("wheelBrakes", 0);
	  ret=ASN1_CHECK_BITSTRING(&(value->wheelBrakes), checkinfo_wheelBrakes);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("traction", 0);
	  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->traction), checkinfo_traction);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("abs", 0);
	  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->abs), checkinfo_abs);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("scs", 0);
	  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->scs), checkinfo_scs);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("brakeBoost", 0);
	  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->brakeBoost), checkinfo_brakeBoost);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("auxBrakes", 0);
	  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->auxBrakes), checkinfo_auxBrakes);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_Circle(Circle *value)
{
	int ret = 0;

	unsigned char checkinfo_center[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_radius[] = { 
		0x02,0x00,0x82,0x0F,0xFF,0x00
	};
	unsigned char checkinfo_units[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("center", 0);
	  ret=ASN1_CHECK_Position3D(value->center);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("radius", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->radius), checkinfo_radius);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("units", 0);
	  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->units), checkinfo_units);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_ComputedLane(ComputedLane *value)
{
	int ret = 0;

	unsigned char checkinfo_referenceLaneId[] = { 
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_offsetXaxis[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_offsetYaxis[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_rotateXY[] = { 
		0x02,0x00,0x82,0x70,0x80,0x00
	};
	unsigned char checkinfo_scaleXaxis[] = { 
		0x02,0x82,0xF8,0x00,0x82,0x07,0xFF,0x00
	};
	unsigned char checkinfo_scaleYaxis[] = { 
		0x02,0x82,0xF8,0x00,0x82,0x07,0xFF,0x00
	};
	unsigned char checkinfo_regional[] = { 
		0x02,0x01,0x04,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("referenceLaneId", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->referenceLaneId), checkinfo_referenceLaneId);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("offsetXaxis", 0);
	  ret=ASN1_CHECK_ComputedLane_offsetXaxis(value->offsetXaxis);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("offsetYaxis", 0);
	  ret=ASN1_CHECK_ComputedLane_offsetYaxis(value->offsetYaxis);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_ComputedLane_rotateXY == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("rotateXY", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->rotateXY), checkinfo_rotateXY);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_ComputedLane_scaleXaxis == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("scaleXaxis", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->scaleXaxis), checkinfo_scaleXaxis);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_ComputedLane_scaleYaxis == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("scaleYaxis", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->scaleYaxis), checkinfo_scaleYaxis);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_ComputedLane_regional == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_CHECK_ComputedLane_regional(&(value->regional));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_ComputedLane_offsetXaxis(ComputedLane_offsetXaxis *value)
{
	int ret = 0;

	unsigned char checkinfo_small[] = { 
		0x02,0x82,0xF8,0x01,0x82,0x07,0xFF,0x00
	};
	unsigned char checkinfo_large[] = { 
		0x02,0x82,0x80,0x01,0x82,0x7F,0xFF,0x00
	};

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_ComputedLane_offsetXaxis_small:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_INTEGER(&value->elements.small, checkinfo_small);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_ComputedLane_offsetXaxis_large:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_INTEGER(&value->elements.large, checkinfo_large);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	default: break;
	}
	return ret;
}
int ASN1_CHECK_ComputedLane_offsetYaxis(ComputedLane_offsetYaxis *value)
{
	int ret = 0;

	unsigned char checkinfo_small[] = { 
		0x02,0x82,0xF8,0x01,0x82,0x07,0xFF,0x00
	};
	unsigned char checkinfo_large[] = { 
		0x02,0x82,0x80,0x01,0x82,0x7F,0xFF,0x00
	};

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_ComputedLane_offsetYaxis_small:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_INTEGER(&value->elements.small, checkinfo_small);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_ComputedLane_offsetYaxis_large:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_INTEGER(&value->elements.large, checkinfo_large);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	default: break;
	}
	return ret;
}
int ASN1_CHECK_ComputedLane_regional(ComputedLane_regional *value)
{
	int ret = 0;

	unsigned char checkinfo_ComputedLane_regional[] = { 
		0x02,0x01,0x04,0x00
	};
	unsigned char checkinfo_ComputedLane_regional_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_RegionalExtension(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_ConnectionManeuverAssist(ConnectionManeuverAssist *value)
{
	int ret = 0;

	unsigned char checkinfo_connectionID[] = { 
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_queueLength[] = { 
		0x02,0x00,0x82,0x27,0x10,0x00
	};
	unsigned char checkinfo_availableStorageLength[] = { 
		0x02,0x00,0x82,0x27,0x10,0x00
	};
	unsigned char checkinfo_waitOnStop[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_pedBicycleDetect[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_regional[] = { 
		0x02,0x01,0x04,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("connectionID", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->connectionID), checkinfo_connectionID);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_ConnectionManeuverAssist_queueLength == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("queueLength", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->queueLength), checkinfo_queueLength);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_ConnectionManeuverAssist_availableStorageLength == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("availableStorageLength", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->availableStorageLength), checkinfo_availableStorageLength);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_ConnectionManeuverAssist_waitOnStop == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("waitOnStop", 0);
		  ret=ASN1_CHECK_BOOLEAN(&(value->waitOnStop), checkinfo_waitOnStop);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_ConnectionManeuverAssist_pedBicycleDetect == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("pedBicycleDetect", 0);
		  ret=ASN1_CHECK_BOOLEAN(&(value->pedBicycleDetect), checkinfo_pedBicycleDetect);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_ConnectionManeuverAssist_regional == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_CHECK_ConnectionManeuverAssist_regional(&(value->regional));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_ConnectionManeuverAssist_regional(ConnectionManeuverAssist_regional *value)
{
	int ret = 0;

	unsigned char checkinfo_ConnectionManeuverAssist_regional[] = { 
		0x02,0x01,0x04,0x00
	};
	unsigned char checkinfo_ConnectionManeuverAssist_regional_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_RegionalExtension(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_DDateTime(DDateTime *value)
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
	if (value->DEF_DDateTime_year == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("year", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->year), checkinfo_year);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_DDateTime_month == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("month", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->month), checkinfo_month);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_DDateTime_day == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("day", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->day), checkinfo_day);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_DDateTime_hour == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("hour", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->hour), checkinfo_hour);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_DDateTime_minute == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("minute", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->minute), checkinfo_minute);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_DDateTime_second == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("second", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->second), checkinfo_second);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_DDateTime_offset == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("offset", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->offset), checkinfo_offset);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_EnabledLaneList(EnabledLaneList *value)
{
	int ret = 0;

	unsigned char checkinfo_EnabledLaneList[] = { 
		0x02,0x01,0x10,0x00
	};
	unsigned char checkinfo_EnabledLaneList_pdata[] = { 
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_INTEGER(pnode->data, checkinfo_EnabledLaneList_pdata);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_EventOrSvcInfo_KOR(EventOrSvcInfo_KOR *value)
{
	int ret = 0;

	unsigned char checkinfo_typeEvent[] = { 
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_description[] = { 
		0x02,0x01,0x64,0x00
	};
	unsigned char checkinfo_text[] = { 
		0x02,0x01,0x08,0x00
	};
	unsigned char checkinfo_subtext[] = { 
		0x02,0x01,0x08,0x00
	};

	if (value == NULL) return -1;
	if (value->DEF_EventOrSvcInfo_KOR_typeEvent == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("typeEvent", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->typeEvent), checkinfo_typeEvent);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_EventOrSvcInfo_KOR_description == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("description", 0);
		  ret=ASN1_CHECK_ITIScodesAndText(&(value->description));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_EventOrSvcInfo_KOR_text == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("text", 0);
		  ret=ASN1_CHECK_EventOrSvcInfo_KOR_text(&(value->text));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_EventOrSvcInfo_KOR_subtext == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("subtext", 0);
		  ret=ASN1_CHECK_EventOrSvcInfo_KOR_subtext(&(value->subtext));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_EventOrSvcInfo_KOR_subtext(EventOrSvcInfo_KOR_subtext *value)
{
	int ret = 0;

	unsigned char checkinfo_EventOrSvcInfo_KOR_subtext[] = { 
		0x02,0x01,0x08,0x00
	};
	unsigned char checkinfo_EventOrSvcInfo_KOR_subtext_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_UTF8Str(pnode->data, checkinfo_EventOrSvcInfo_KOR_subtext_pdata);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_EventOrSvcInfo_KOR_text(EventOrSvcInfo_KOR_text *value)
{
	int ret = 0;

	unsigned char checkinfo_EventOrSvcInfo_KOR_text[] = { 
		0x02,0x01,0x08,0x00
	};
	unsigned char checkinfo_EventOrSvcInfo_KOR_text_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_UTF8Str(pnode->data, checkinfo_EventOrSvcInfo_KOR_text_pdata);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_ExitService(ExitService *value)
{
	int ret = 0;

	unsigned char checkinfo_ExitService[] = { 
		0x02,0x01,0x10,0x00
	};
	unsigned char checkinfo_ExitService_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_ExitService_element(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_ExitService_element(ExitService_element *value)
{
	int ret = 0;

	unsigned char checkinfo_item[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("item", 0);
	  ret=ASN1_CHECK_ExitService_element_item(value->item);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_ExitService_element_item(ExitService_element_item *value)
{
	int ret = 0;

	unsigned char checkinfo_itis[] = { 
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_text[] = { 
		0x02,0x01,0x10,0x00
	};

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_ExitService_element_item_itis:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_INTEGER(&value->elements.itis, checkinfo_itis);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_ExitService_element_item_text:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_IA5String(&value->elements.text, checkinfo_text);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	default: break;
	}
	return ret;
}
int ASN1_CHECK_GenericSignage(GenericSignage *value)
{
	int ret = 0;

	unsigned char checkinfo_GenericSignage[] = { 
		0x02,0x01,0x10,0x00
	};
	unsigned char checkinfo_GenericSignage_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_GenericSignage_element(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_GenericSignage_element(GenericSignage_element *value)
{
	int ret = 0;

	unsigned char checkinfo_item[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("item", 0);
	  ret=ASN1_CHECK_GenericSignage_element_item(value->item);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_GenericSignage_element_item(GenericSignage_element_item *value)
{
	int ret = 0;

	unsigned char checkinfo_itis[] = { 
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_text[] = { 
		0x02,0x01,0x10,0x00
	};

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_GenericSignage_element_item_itis:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_INTEGER(&value->elements.itis, checkinfo_itis);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_GenericSignage_element_item_text:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_IA5String(&value->elements.text, checkinfo_text);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	default: break;
	}
	return ret;
}
int ASN1_CHECK_GeographicalPath(GeographicalPath *value)
{
	int ret = 0;

	unsigned char checkinfo_name[] = { 
		0x02,0x01,0x3F,0x00
	};
	unsigned char checkinfo_id[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_anchor[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_laneWidth[] = { 
		0x02,0x00,0x82,0x7F,0xFF,0x00
	};
	unsigned char checkinfo_directionality[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_closedPath[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_direction[] = { 
		0x02,0x10,0x10,0x00
	};
	unsigned char checkinfo_description[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_regional[] = { 
		0x02,0x01,0x04,0x00
	};

	if (value == NULL) return -1;
	if (value->DEF_GeographicalPath_name == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("name", 0);
		  ret=ASN1_CHECK_IA5String(&(value->name), checkinfo_name);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_GeographicalPath_id == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("id", 0);
		  ret=ASN1_CHECK_RoadSegmentReferenceID(value->id);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_GeographicalPath_anchor == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("anchor", 0);
		  ret=ASN1_CHECK_Position3D(value->anchor);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_GeographicalPath_laneWidth == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("laneWidth", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->laneWidth), checkinfo_laneWidth);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_GeographicalPath_directionality == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("directionality", 0);
		  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->directionality), checkinfo_directionality);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_GeographicalPath_closedPath == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("closedPath", 0);
		  ret=ASN1_CHECK_BOOLEAN(&(value->closedPath), checkinfo_closedPath);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_GeographicalPath_direction == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("direction", 0);
		  ret=ASN1_CHECK_BITSTRING(&(value->direction), checkinfo_direction);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_GeographicalPath_description == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("description", 0);
		  ret=ASN1_CHECK_GeographicalPath_description(value->description);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_GeographicalPath_regional == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_CHECK_GeographicalPath_regional(&(value->regional));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_GeographicalPath_KOR(GeographicalPath_KOR *value)
{
	int ret = 0;

	unsigned char checkinfo_regions[] = { 
		0x02,0x01,0x20,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("regions", 0);
	  ret=ASN1_CHECK_GeographicalPath_KOR_regions(&(value->regions));
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_GeographicalPath_KOR_regions(GeographicalPath_KOR_regions *value)
{
	int ret = 0;

	unsigned char checkinfo_GeographicalPath_KOR_regions[] = { 
		0x02,0x01,0x20,0x00
	};
	unsigned char checkinfo_GeographicalPath_KOR_regions_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_RegionDescribedByID_KOR(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_GeographicalPath_description(GeographicalPath_description *value)
{
	int ret = 0;

	unsigned char checkinfo_path[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_geometry[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_oldRegion[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_GeographicalPath_description_path:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_OffsetSystem(value->elements.path);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_GeographicalPath_description_geometry:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_GeometricProjection(value->elements.geometry);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_GeographicalPath_description_oldRegion:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_ValidRegion(value->elements.oldRegion);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	default: break;
	}
	return ret;
}
int ASN1_CHECK_GeographicalPath_regional(GeographicalPath_regional *value)
{
	int ret = 0;

	unsigned char checkinfo_GeographicalPath_regional[] = { 
		0x02,0x01,0x04,0x00
	};
	unsigned char checkinfo_GeographicalPath_regional_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_RegionalExtension(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_GeometricProjection(GeometricProjection *value)
{
	int ret = 0;

	unsigned char checkinfo_direction[] = { 
		0x02,0x10,0x10,0x00
	};
	unsigned char checkinfo_extent[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_laneWidth[] = { 
		0x02,0x00,0x82,0x7F,0xFF,0x00
	};
	unsigned char checkinfo_circle[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_regional[] = { 
		0x02,0x01,0x04,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("direction", 0);
	  ret=ASN1_CHECK_BITSTRING(&(value->direction), checkinfo_direction);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_GeometricProjection_extent == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("extent", 0);
		  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->extent), checkinfo_extent);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_GeometricProjection_laneWidth == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("laneWidth", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->laneWidth), checkinfo_laneWidth);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	{ size_t saved=MqttDiag_enter("circle", 0);
	  ret=ASN1_CHECK_Circle(value->circle);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_GeometricProjection_regional == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_CHECK_GeometricProjection_regional(&(value->regional));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_GeometricProjection_regional(GeometricProjection_regional *value)
{
	int ret = 0;

	unsigned char checkinfo_GeometricProjection_regional[] = { 
		0x02,0x01,0x04,0x00
	};
	unsigned char checkinfo_GeometricProjection_regional_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_RegionalExtension(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_ITIScodesAndText(ITIScodesAndText *value)
{
	int ret = 0;

	unsigned char checkinfo_ITIScodesAndText[] = { 
		0x02,0x01,0x64,0x00
	};
	unsigned char checkinfo_ITIScodesAndText_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_ITIScodesAndText_element(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_ITIScodesAndText_element(ITIScodesAndText_element *value)
{
	int ret = 0;

	unsigned char checkinfo_item[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("item", 0);
	  ret=ASN1_CHECK_ITIScodesAndText_element_item(value->item);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_ITIScodesAndText_element_item(ITIScodesAndText_element_item *value)
{
	int ret = 0;

	unsigned char checkinfo_itis[] = { 
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_text[] = { 
		0x02,0x01,0x82,0x01,0xF4,0x00
	};

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_ITIScodesAndText_element_item_itis:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_INTEGER(&value->elements.itis, checkinfo_itis);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_ITIScodesAndText_element_item_text:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_IA5String(&value->elements.text, checkinfo_text);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	default: break;
	}
	return ret;
}
int ASN1_CHECK_IntersectionReferenceID(IntersectionReferenceID *value)
{
	int ret = 0;

	unsigned char checkinfo_region[] = { 
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_id[] = { 
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};

	if (value == NULL) return -1;
	if (value->DEF_IntersectionReferenceID_region == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("region", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->region), checkinfo_region);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	{ size_t saved=MqttDiag_enter("id", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->id), checkinfo_id);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_IntersectionState(IntersectionState *value)
{
	int ret = 0;

	unsigned char checkinfo_name[] = { 
		0x02,0x01,0x3F,0x00
	};
	unsigned char checkinfo_id[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_revision[] = { 
		0x02,0x00,0x7F,0x00
	};
	unsigned char checkinfo_status[] = { 
		0x02,0x10,0x10,0x00
	};
	unsigned char checkinfo_moy[] = { 
		0x02,0x00,0x83,0x08,0x0A,0xC0,0x00
	};
	unsigned char checkinfo_timeStamp[] = { 
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_enabledLanes[] = { 
		0x02,0x01,0x10,0x00
	};
	unsigned char checkinfo_states[] = { 
		0x02,0x01,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_maneuverAssistList[] = { 
		0x02,0x01,0x10,0x00
	};
	unsigned char checkinfo_regional[] = { 
		0x02,0x01,0x04,0x00
	};

	if (value == NULL) return -1;
	if (value->DEF_IntersectionState_name == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("name", 0);
		  ret=ASN1_CHECK_IA5String(&(value->name), checkinfo_name);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	{ size_t saved=MqttDiag_enter("id", 0);
	  ret=ASN1_CHECK_IntersectionReferenceID(value->id);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("revision", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->revision), checkinfo_revision);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("status", 0);
	  ret=ASN1_CHECK_BITSTRING(&(value->status), checkinfo_status);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_IntersectionState_moy == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("moy", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->moy), checkinfo_moy);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_IntersectionState_timeStamp == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("timeStamp", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->timeStamp), checkinfo_timeStamp);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_IntersectionState_enabledLanes == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("enabledLanes", 0);
		  ret=ASN1_CHECK_EnabledLaneList(&(value->enabledLanes));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	{ size_t saved=MqttDiag_enter("states", 0);
	  ret=ASN1_CHECK_MovementList(&(value->states));
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_IntersectionState_maneuverAssistList == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("maneuverAssistList", 0);
		  ret=ASN1_CHECK_ManeuverAssistList(&(value->maneuverAssistList));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_IntersectionState_regional == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_CHECK_IntersectionState_regional(&(value->regional));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_IntersectionStateList(IntersectionStateList *value)
{
	int ret = 0;

	unsigned char checkinfo_IntersectionStateList[] = { 
		0x02,0x01,0x20,0x00
	};
	unsigned char checkinfo_IntersectionStateList_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_IntersectionState(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_IntersectionState_regional(IntersectionState_regional *value)
{
	int ret = 0;

	unsigned char checkinfo_IntersectionState_regional[] = { 
		0x02,0x01,0x04,0x00
	};
	unsigned char checkinfo_IntersectionState_regional_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_RegionalExtension(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_LaneDataAttribute(LaneDataAttribute *value)
{
	int ret = 0;

	unsigned char checkinfo_pathEndPointAngle[] = { 
		0x02,0x82,0xFF,0x6A,0x82,0x00,0x96,0x00
	};
	unsigned char checkinfo_laneCrownPointCenter[] = { 
		0x02,0x82,0xFF,0x80,0x7F,0x00
	};
	unsigned char checkinfo_laneCrownPointLeft[] = { 
		0x02,0x82,0xFF,0x80,0x7F,0x00
	};
	unsigned char checkinfo_laneCrownPointRight[] = { 
		0x02,0x82,0xFF,0x80,0x7F,0x00
	};
	unsigned char checkinfo_laneAngle[] = { 
		0x02,0x82,0xFF,0x4C,0x82,0x00,0xB4,0x00
	};
	unsigned char checkinfo_speedLimits[] = { 
		0x02,0x01,0x09,0x00
	};
	unsigned char checkinfo_regional[] = { 
		0x02,0x01,0x04,0x00
	};

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_LaneDataAttribute_pathEndPointAngle:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_INTEGER(&value->elements.pathEndPointAngle, checkinfo_pathEndPointAngle);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_LaneDataAttribute_laneCrownPointCenter:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_INTEGER(&value->elements.laneCrownPointCenter, checkinfo_laneCrownPointCenter);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_LaneDataAttribute_laneCrownPointLeft:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_INTEGER(&value->elements.laneCrownPointLeft, checkinfo_laneCrownPointLeft);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_LaneDataAttribute_laneCrownPointRight:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_INTEGER(&value->elements.laneCrownPointRight, checkinfo_laneCrownPointRight);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_LaneDataAttribute_laneAngle:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_INTEGER(&value->elements.laneAngle, checkinfo_laneAngle);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_LaneDataAttribute_speedLimits:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_SpeedLimitList(&value->elements.speedLimits);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_LaneDataAttribute_regional:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_LaneDataAttribute_regional(&value->elements.regional);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	default: break;
	}
	return ret;
}
int ASN1_CHECK_LaneDataAttributeList(LaneDataAttributeList *value)
{
	int ret = 0;

	unsigned char checkinfo_LaneDataAttributeList[] = { 
		0x02,0x01,0x08,0x00
	};
	unsigned char checkinfo_LaneDataAttributeList_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_LaneDataAttribute(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_LaneDataAttribute_regional(LaneDataAttribute_regional *value)
{
	int ret = 0;

	unsigned char checkinfo_LaneDataAttribute_regional[] = { 
		0x02,0x01,0x04,0x00
	};
	unsigned char checkinfo_LaneDataAttribute_regional_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_RegionalExtension(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_LaneID(LaneID *value)
{
	unsigned char checkinfo_LaneID[] = { 
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_INTEGER(value, checkinfo_LaneID);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_ManeuverAssistList(ManeuverAssistList *value)
{
	int ret = 0;

	unsigned char checkinfo_ManeuverAssistList[] = { 
		0x02,0x01,0x10,0x00
	};
	unsigned char checkinfo_ManeuverAssistList_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_ConnectionManeuverAssist(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_MessageFrame(MessageFrame *value)
{
	int ret = 0;

	unsigned char checkinfo_messageId[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_value[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("messageId", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->messageId), checkinfo_messageId);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("value", 0);
	  ret=ASN1_CHECK_OpenType(&(value->value), checkinfo_value);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_MovementEvent(MovementEvent *value)
{
	int ret = 0;

	unsigned char checkinfo_eventState[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_timing[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_speeds[] = { 
		0x02,0x01,0x10,0x00
	};
	unsigned char checkinfo_regional[] = { 
		0x02,0x01,0x04,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("eventState", 0);
	  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->eventState), checkinfo_eventState);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_MovementEvent_timing == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("timing", 0);
		  ret=ASN1_CHECK_TimeChangeDetails(value->timing);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_MovementEvent_speeds == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("speeds", 0);
		  ret=ASN1_CHECK_AdvisorySpeedList(&(value->speeds));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_MovementEvent_regional == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_CHECK_MovementEvent_regional(&(value->regional));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_MovementEventList(MovementEventList *value)
{
	int ret = 0;

	unsigned char checkinfo_MovementEventList[] = { 
		0x02,0x01,0x10,0x00
	};
	unsigned char checkinfo_MovementEventList_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_MovementEvent(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_MovementEvent_regional(MovementEvent_regional *value)
{
	int ret = 0;

	unsigned char checkinfo_MovementEvent_regional[] = { 
		0x02,0x01,0x04,0x00
	};
	unsigned char checkinfo_MovementEvent_regional_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_RegionalExtension(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_MovementList(MovementList *value)
{
	int ret = 0;

	unsigned char checkinfo_MovementList[] = { 
		0x02,0x01,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_MovementList_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_MovementState(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_MovementState(MovementState *value)
{
	int ret = 0;

	unsigned char checkinfo_movementName[] = { 
		0x02,0x01,0x3F,0x00
	};
	unsigned char checkinfo_signalGroup[] = { 
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_state_time_speed[] = { 
		0x02,0x01,0x10,0x00
	};
	unsigned char checkinfo_maneuverAssistList[] = { 
		0x02,0x01,0x10,0x00
	};
	unsigned char checkinfo_regional[] = { 
		0x02,0x01,0x04,0x00
	};

	if (value == NULL) return -1;
	if (value->DEF_MovementState_movementName == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("movementName", 0);
		  ret=ASN1_CHECK_IA5String(&(value->movementName), checkinfo_movementName);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	{ size_t saved=MqttDiag_enter("signalGroup", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->signalGroup), checkinfo_signalGroup);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("state_time_speed", 0);
	  ret=ASN1_CHECK_MovementEventList(&(value->state_time_speed));
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_MovementState_maneuverAssistList == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("maneuverAssistList", 0);
		  ret=ASN1_CHECK_ManeuverAssistList(&(value->maneuverAssistList));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_MovementState_regional == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_CHECK_MovementState_regional(&(value->regional));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_MovementState_regional(MovementState_regional *value)
{
	int ret = 0;

	unsigned char checkinfo_MovementState_regional[] = { 
		0x02,0x01,0x04,0x00
	};
	unsigned char checkinfo_MovementState_regional_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_RegionalExtension(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_NodeAttributeLL(NodeAttributeLL *value)
{
	unsigned char checkinfo_NodeAttributeLL[] = {0x0C,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x00 };
	int ret = 0;
	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ENUMERATED((ASNINT32 *)value, checkinfo_NodeAttributeLL);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_NodeAttributeLLList(NodeAttributeLLList *value)
{
	int ret = 0;

	unsigned char checkinfo_NodeAttributeLLList[] = { 
		0x02,0x01,0x08,0x00
	};
	unsigned char checkinfo_NodeAttributeLLList_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)pnode->data, checkinfo_NodeAttributeLLList_pdata);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_NodeAttributeSetLL(NodeAttributeSetLL *value)
{
	int ret = 0;

	unsigned char checkinfo_localNode[] = { 
		0x02,0x01,0x08,0x00
	};
	unsigned char checkinfo_disabled[] = { 
		0x02,0x01,0x08,0x00
	};
	unsigned char checkinfo_enabled[] = { 
		0x02,0x01,0x08,0x00
	};
	unsigned char checkinfo_data[] = { 
		0x02,0x01,0x08,0x00
	};
	unsigned char checkinfo_dWidth[] = { 
		0x02,0x82,0xFE,0x00,0x82,0x01,0xFF,0x00
	};
	unsigned char checkinfo_dElevation[] = { 
		0x02,0x82,0xFE,0x00,0x82,0x01,0xFF,0x00
	};
	unsigned char checkinfo_regional[] = { 
		0x02,0x01,0x04,0x00
	};

	if (value == NULL) return -1;
	if (value->DEF_NodeAttributeSetLL_localNode == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("localNode", 0);
		  ret=ASN1_CHECK_NodeAttributeLLList(&(value->localNode));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_NodeAttributeSetLL_disabled == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("disabled", 0);
		  ret=ASN1_CHECK_SegmentAttributeLLList(&(value->disabled));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_NodeAttributeSetLL_enabled == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("enabled", 0);
		  ret=ASN1_CHECK_SegmentAttributeLLList(&(value->enabled));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_NodeAttributeSetLL_data == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("data", 0);
		  ret=ASN1_CHECK_LaneDataAttributeList(&(value->data));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_NodeAttributeSetLL_dWidth == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("dWidth", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->dWidth), checkinfo_dWidth);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_NodeAttributeSetLL_dElevation == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("dElevation", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->dElevation), checkinfo_dElevation);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_NodeAttributeSetLL_regional == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_CHECK_NodeAttributeSetLL_regional(&(value->regional));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_NodeAttributeSetLL_regional(NodeAttributeSetLL_regional *value)
{
	int ret = 0;

	unsigned char checkinfo_NodeAttributeSetLL_regional[] = { 
		0x02,0x01,0x04,0x00
	};
	unsigned char checkinfo_NodeAttributeSetLL_regional_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_RegionalExtension(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_NodeAttributeSetXY(NodeAttributeSetXY *value)
{
	int ret = 0;

	unsigned char checkinfo_localNode[] = { 
		0x02,0x01,0x08,0x00
	};
	unsigned char checkinfo_disabled[] = { 
		0x02,0x01,0x08,0x00
	};
	unsigned char checkinfo_enabled[] = { 
		0x02,0x01,0x08,0x00
	};
	unsigned char checkinfo_data[] = { 
		0x02,0x01,0x08,0x00
	};
	unsigned char checkinfo_dWidth[] = { 
		0x02,0x82,0xFE,0x00,0x82,0x01,0xFF,0x00
	};
	unsigned char checkinfo_dElevation[] = { 
		0x02,0x82,0xFE,0x00,0x82,0x01,0xFF,0x00
	};
	unsigned char checkinfo_regional[] = { 
		0x02,0x01,0x04,0x00
	};

	if (value == NULL) return -1;
	if (value->DEF_NodeAttributeSetXY_localNode == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("localNode", 0);
		  ret=ASN1_CHECK_NodeAttributeXYList(&(value->localNode));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_NodeAttributeSetXY_disabled == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("disabled", 0);
		  ret=ASN1_CHECK_SegmentAttributeXYList(&(value->disabled));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_NodeAttributeSetXY_enabled == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("enabled", 0);
		  ret=ASN1_CHECK_SegmentAttributeXYList(&(value->enabled));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_NodeAttributeSetXY_data == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("data", 0);
		  ret=ASN1_CHECK_LaneDataAttributeList(&(value->data));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_NodeAttributeSetXY_dWidth == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("dWidth", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->dWidth), checkinfo_dWidth);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_NodeAttributeSetXY_dElevation == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("dElevation", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->dElevation), checkinfo_dElevation);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_NodeAttributeSetXY_regional == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_CHECK_NodeAttributeSetXY_regional(&(value->regional));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_NodeAttributeSetXY_regional(NodeAttributeSetXY_regional *value)
{
	int ret = 0;

	unsigned char checkinfo_NodeAttributeSetXY_regional[] = { 
		0x02,0x01,0x04,0x00
	};
	unsigned char checkinfo_NodeAttributeSetXY_regional_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_RegionalExtension(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_NodeAttributeXY(NodeAttributeXY *value)
{
	unsigned char checkinfo_NodeAttributeXY[] = {0x0C,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x00 };
	int ret = 0;
	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ENUMERATED((ASNINT32 *)value, checkinfo_NodeAttributeXY);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_NodeAttributeXYList(NodeAttributeXYList *value)
{
	int ret = 0;

	unsigned char checkinfo_NodeAttributeXYList[] = { 
		0x02,0x01,0x08,0x00
	};
	unsigned char checkinfo_NodeAttributeXYList_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)pnode->data, checkinfo_NodeAttributeXYList_pdata);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_NodeLL(NodeLL *value)
{
	int ret = 0;

	unsigned char checkinfo_delta[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_attributes[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("delta", 0);
	  ret=ASN1_CHECK_NodeOffsetPointLL(value->delta);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_NodeLL_attributes == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("attributes", 0);
		  ret=ASN1_CHECK_NodeAttributeSetLL(value->attributes);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_NodeListLL(NodeListLL *value)
{
	int ret = 0;

	unsigned char checkinfo_nodes[] = { 
		0x02,0x02,0x3F,0x00
	};

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_NodeListLL_nodes:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_NodeSetLL(&value->elements.nodes);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	default: break;
	}
	return ret;
}
int ASN1_CHECK_NodeListXY(NodeListXY *value)
{
	int ret = 0;

	unsigned char checkinfo_nodes[] = { 
		0x02,0x02,0x3F,0x00
	};
	unsigned char checkinfo_computed[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_NodeListXY_nodes:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_NodeSetXY(&value->elements.nodes);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_NodeListXY_computed:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_ComputedLane(value->elements.computed);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	default: break;
	}
	return ret;
}
int ASN1_CHECK_NodeOffsetPointLL(NodeOffsetPointLL *value)
{
	int ret = 0;

	unsigned char checkinfo_node_LL1[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_node_LL2[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_node_LL3[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_node_LL4[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_node_LL5[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_node_LL6[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_node_LatLon[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_regional[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_NodeOffsetPointLL_node_LL1:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_Node_LL_24B(value->elements.node_LL1);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_NodeOffsetPointLL_node_LL2:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_Node_LL_28B(value->elements.node_LL2);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_NodeOffsetPointLL_node_LL3:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_Node_LL_32B(value->elements.node_LL3);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_NodeOffsetPointLL_node_LL4:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_Node_LL_36B(value->elements.node_LL4);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_NodeOffsetPointLL_node_LL5:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_Node_LL_44B(value->elements.node_LL5);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_NodeOffsetPointLL_node_LL6:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_Node_LL_48B(value->elements.node_LL6);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_NodeOffsetPointLL_node_LatLon:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_Node_LLmD_64b(value->elements.node_LatLon);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_NodeOffsetPointLL_regional:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_RegionalExtension(value->elements.regional);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	default: break;
	}
	return ret;
}
int ASN1_CHECK_NodeOffsetPointXY(NodeOffsetPointXY *value)
{
	int ret = 0;

	unsigned char checkinfo_node_XY1[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_node_XY2[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_node_XY3[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_node_XY4[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_node_XY5[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_node_XY6[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_node_LatLon[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_regional[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_NodeOffsetPointXY_node_XY1:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_Node_XY_20b(value->elements.node_XY1);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_NodeOffsetPointXY_node_XY2:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_Node_XY_22b(value->elements.node_XY2);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_NodeOffsetPointXY_node_XY3:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_Node_XY_24b(value->elements.node_XY3);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_NodeOffsetPointXY_node_XY4:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_Node_XY_26b(value->elements.node_XY4);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_NodeOffsetPointXY_node_XY5:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_Node_XY_28b(value->elements.node_XY5);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_NodeOffsetPointXY_node_XY6:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_Node_XY_32b(value->elements.node_XY6);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_NodeOffsetPointXY_node_LatLon:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_Node_LLmD_64b(value->elements.node_LatLon);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_NodeOffsetPointXY_regional:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_RegionalExtension(value->elements.regional);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	default: break;
	}
	return ret;
}
int ASN1_CHECK_NodeSetLL(NodeSetLL *value)
{
	int ret = 0;

	unsigned char checkinfo_NodeSetLL[] = { 
		0x02,0x02,0x3F,0x00
	};
	unsigned char checkinfo_NodeSetLL_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_NodeLL(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_NodeSetXY(NodeSetXY *value)
{
	int ret = 0;

	unsigned char checkinfo_NodeSetXY[] = { 
		0x02,0x02,0x3F,0x00
	};
	unsigned char checkinfo_NodeSetXY_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_NodeXY(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_NodeXY(NodeXY *value)
{
	int ret = 0;

	unsigned char checkinfo_delta[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_attributes[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("delta", 0);
	  ret=ASN1_CHECK_NodeOffsetPointXY(value->delta);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_NodeXY_attributes == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("attributes", 0);
		  ret=ASN1_CHECK_NodeAttributeSetXY(value->attributes);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_Node_LL_24B(Node_LL_24B *value)
{
	int ret = 0;

	unsigned char checkinfo_lon[] = { 
		0x02,0x82,0xF8,0x00,0x82,0x07,0xFF,0x00
	};
	unsigned char checkinfo_lat[] = { 
		0x02,0x82,0xF8,0x00,0x82,0x07,0xFF,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("lon", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->lon), checkinfo_lon);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("lat", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->lat), checkinfo_lat);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_Node_LL_28B(Node_LL_28B *value)
{
	int ret = 0;

	unsigned char checkinfo_lon[] = { 
		0x02,0x82,0xE0,0x00,0x82,0x1F,0xFF,0x00
	};
	unsigned char checkinfo_lat[] = { 
		0x02,0x82,0xE0,0x00,0x82,0x1F,0xFF,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("lon", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->lon), checkinfo_lon);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("lat", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->lat), checkinfo_lat);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_Node_LL_32B(Node_LL_32B *value)
{
	int ret = 0;

	unsigned char checkinfo_lon[] = { 
		0x02,0x83,0xFF,0x80,0x00,0x82,0x7F,0xFF,0x00
	};
	unsigned char checkinfo_lat[] = { 
		0x02,0x83,0xFF,0x80,0x00,0x82,0x7F,0xFF,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("lon", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->lon), checkinfo_lon);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("lat", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->lat), checkinfo_lat);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_Node_LL_36B(Node_LL_36B *value)
{
	int ret = 0;

	unsigned char checkinfo_lon[] = { 
		0x02,0x83,0xFE,0x00,0x00,0x83,0x01,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_lat[] = { 
		0x02,0x83,0xFE,0x00,0x00,0x83,0x01,0xFF,0xFF,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("lon", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->lon), checkinfo_lon);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("lat", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->lat), checkinfo_lat);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_Node_LL_44B(Node_LL_44B *value)
{
	int ret = 0;

	unsigned char checkinfo_lon[] = { 
		0x02,0x83,0xE0,0x00,0x00,0x83,0x1F,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_lat[] = { 
		0x02,0x83,0xE0,0x00,0x00,0x83,0x1F,0xFF,0xFF,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("lon", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->lon), checkinfo_lon);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("lat", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->lat), checkinfo_lat);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_Node_LL_48B(Node_LL_48B *value)
{
	int ret = 0;

	unsigned char checkinfo_lon[] = { 
		0x02,0x84,0xFF,0x80,0x00,0x00,0x83,0x7F,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_lat[] = { 
		0x02,0x84,0xFF,0x80,0x00,0x00,0x83,0x7F,0xFF,0xFF,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("lon", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->lon), checkinfo_lon);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("lat", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->lat), checkinfo_lat);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_Node_LLmD_64b(Node_LLmD_64b *value)
{
	int ret = 0;

	unsigned char checkinfo_lon[] = { 
		0x02,0x84,0x94,0xB6,0x2E,0x01,0x84,0x6B,0x49,0xD2,0x01,0x00
	};
	unsigned char checkinfo_lat[] = { 
		0x02,0x84,0xCA,0x5B,0x17,0x00,0x84,0x35,0xA4,0xE9,0x01,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("lon", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->lon), checkinfo_lon);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("lat", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->lat), checkinfo_lat);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_Node_XY_20b(Node_XY_20b *value)
{
	int ret = 0;

	unsigned char checkinfo_x[] = { 
		0x02,0x82,0xFE,0x00,0x82,0x01,0xFF,0x00
	};
	unsigned char checkinfo_y[] = { 
		0x02,0x82,0xFE,0x00,0x82,0x01,0xFF,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("x", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->x), checkinfo_x);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("y", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->y), checkinfo_y);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_Node_XY_22b(Node_XY_22b *value)
{
	int ret = 0;

	unsigned char checkinfo_x[] = { 
		0x02,0x82,0xFC,0x00,0x82,0x03,0xFF,0x00
	};
	unsigned char checkinfo_y[] = { 
		0x02,0x82,0xFC,0x00,0x82,0x03,0xFF,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("x", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->x), checkinfo_x);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("y", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->y), checkinfo_y);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_Node_XY_24b(Node_XY_24b *value)
{
	int ret = 0;

	unsigned char checkinfo_x[] = { 
		0x02,0x82,0xF8,0x00,0x82,0x07,0xFF,0x00
	};
	unsigned char checkinfo_y[] = { 
		0x02,0x82,0xF8,0x00,0x82,0x07,0xFF,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("x", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->x), checkinfo_x);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("y", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->y), checkinfo_y);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_Node_XY_26b(Node_XY_26b *value)
{
	int ret = 0;

	unsigned char checkinfo_x[] = { 
		0x02,0x82,0xF0,0x00,0x82,0x0F,0xFF,0x00
	};
	unsigned char checkinfo_y[] = { 
		0x02,0x82,0xF0,0x00,0x82,0x0F,0xFF,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("x", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->x), checkinfo_x);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("y", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->y), checkinfo_y);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_Node_XY_28b(Node_XY_28b *value)
{
	int ret = 0;

	unsigned char checkinfo_x[] = { 
		0x02,0x82,0xE0,0x00,0x82,0x1F,0xFF,0x00
	};
	unsigned char checkinfo_y[] = { 
		0x02,0x82,0xE0,0x00,0x82,0x1F,0xFF,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("x", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->x), checkinfo_x);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("y", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->y), checkinfo_y);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_Node_XY_32b(Node_XY_32b *value)
{
	int ret = 0;

	unsigned char checkinfo_x[] = { 
		0x02,0x83,0xFF,0x80,0x00,0x82,0x7F,0xFF,0x00
	};
	unsigned char checkinfo_y[] = { 
		0x02,0x83,0xFF,0x80,0x00,0x82,0x7F,0xFF,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("x", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->x), checkinfo_x);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("y", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->y), checkinfo_y);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_OffsetSystem(OffsetSystem *value)
{
	int ret = 0;

	unsigned char checkinfo_scale[] = { 
		0x02,0x00,0x0F,0x00
	};
	unsigned char checkinfo_offset[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if (value->DEF_OffsetSystem_scale == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("scale", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->scale), checkinfo_scale);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	{ size_t saved=MqttDiag_enter("offset", 0);
	  ret=ASN1_CHECK_OffsetSystem_offset(value->offset);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_OffsetSystem_offset(OffsetSystem_offset *value)
{
	int ret = 0;

	unsigned char checkinfo_xy[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_ll[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_OffsetSystem_offset_xy:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_NodeListXY(value->elements.xy);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_OffsetSystem_offset_ll:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_NodeListLL(value->elements.ll);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	default: break;
	}
	return ret;
}
int ASN1_CHECK_ParkingCapacity_KOR(ParkingCapacity_KOR *value)
{
	int ret = 0;

	unsigned char checkinfo_type[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_numberOfParkingSpace[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_maxParkingSpace[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("type", 0);
	  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->type), checkinfo_type);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("numberOfParkingSpace", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->numberOfParkingSpace), checkinfo_numberOfParkingSpace);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_ParkingCapacity_KOR_maxParkingSpace == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("maxParkingSpace", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->maxParkingSpace), checkinfo_maxParkingSpace);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_ParkingZoneInformation_KOR(ParkingZoneInformation_KOR *value)
{
	int ret = 0;

	unsigned char checkinfo_name[] = { 
		0x02,0x01,0x82,0x00,0x80,0x00
	};
	unsigned char checkinfo_id[] = { 
		0x02,0x01,0x82,0x00,0x80,0x00
	};
	unsigned char checkinfo_capacity[] = { 
		0x02,0x00,0x10,0x00
	};

	if (value == NULL) return -1;
	if (value->DEF_ParkingZoneInformation_KOR_name == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("name", 0);
		  ret=ASN1_CHECK_UTF8Str(&(value->name), checkinfo_name);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_ParkingZoneInformation_KOR_id == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("id", 0);
		  ret=ASN1_CHECK_UTF8Str(&(value->id), checkinfo_id);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	{ size_t saved=MqttDiag_enter("capacity", 0);
	  ret=ASN1_CHECK_ParkingZoneInformation_KOR_capacity(&(value->capacity));
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_ParkingZoneInformation_KOR_capacity(ParkingZoneInformation_KOR_capacity *value)
{
	int ret = 0;

	unsigned char checkinfo_ParkingZoneInformation_KOR_capacity[] = { 
		0x02,0x00,0x10,0x00
	};
	unsigned char checkinfo_ParkingZoneInformation_KOR_capacity_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_ParkingCapacity_KOR(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_PartIIcontent(PartIIcontent *value)
{
	int ret = 0;

	unsigned char checkinfo_partII_Id[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_partII_Value[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("partII_Id", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->partII_Id), checkinfo_partII_Id);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("partII_Value", 0);
	  ret=ASN1_CHECK_OpenType(&(value->partII_Value), checkinfo_partII_Value);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_Position3D(Position3D *value)
{
	int ret = 0;

	unsigned char checkinfo_lat[] = { 
		0x02,0x84,0xCA,0x5B,0x17,0x00,0x84,0x35,0xA4,0xE9,0x01,0x00
	};
	unsigned char checkinfo_lon[] = { 
		0x02,0x84,0x94,0xB6,0x2E,0x01,0x84,0x6B,0x49,0xD2,0x01,0x00
	};
	unsigned char checkinfo_elevation[] = { 
		0x02,0x82,0xF0,0x00,0x83,0x00,0xEF,0xFF,0x00
	};
	unsigned char checkinfo_regional[] = { 
		0x02,0x01,0x04,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("lat", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->lat), checkinfo_lat);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("lon", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->lon), checkinfo_lon);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_Position3D_elevation == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("elevation", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->elevation), checkinfo_elevation);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_Position3D_regional == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_CHECK_Position3D_regional(&(value->regional));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_Position3D_regional(Position3D_regional *value)
{
	int ret = 0;

	unsigned char checkinfo_Position3D_regional[] = { 
		0x02,0x01,0x04,0x00
	};
	unsigned char checkinfo_Position3D_regional_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_RegionalExtension(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_PositionalAccuracy(PositionalAccuracy *value)
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
	{ size_t saved=MqttDiag_enter("semiMajor", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->semiMajor), checkinfo_semiMajor);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("semiMinor", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->semiMinor), checkinfo_semiMinor);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("orientation", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->orientation), checkinfo_orientation);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_RegionDescribedByID_KOR(RegionDescribedByID_KOR *value)
{
	int ret = 0;

	unsigned char checkinfo_laneID[] = { 
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_segmentID[] = { 
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_linkID[] = { 
		0x02,0x01,0x82,0x00,0x80,0x00
	};
	unsigned char checkinfo_detectLane[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_areaID[] = { 
		0x02,0x01,0x82,0x00,0x80,0x00
	};
	unsigned char checkinfo_intersections[] = { 
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_RegionDescribedByID_KOR_laneID:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_INTEGER(&value->elements.laneID, checkinfo_laneID);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_RegionDescribedByID_KOR_segmentID:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_INTEGER(&value->elements.segmentID, checkinfo_segmentID);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_RegionDescribedByID_KOR_linkID:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_UTF8Str(&value->elements.linkID, checkinfo_linkID);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_RegionDescribedByID_KOR_detectLane:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)&value->elements.detectLane, checkinfo_detectLane);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_RegionDescribedByID_KOR_areaID:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_UTF8Str(&value->elements.areaID, checkinfo_areaID);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_RegionDescribedByID_KOR_intersections:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_INTEGER(&value->elements.intersections, checkinfo_intersections);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	default: break;
	}
	return ret;
}
int ASN1_CHECK_RegionList(RegionList *value)
{
	int ret = 0;

	unsigned char checkinfo_RegionList[] = { 
		0x02,0x01,0x40,0x00
	};
	unsigned char checkinfo_RegionList_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_RegionOffsets(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_RegionOffsets(RegionOffsets *value)
{
	int ret = 0;

	unsigned char checkinfo_xOffset[] = { 
		0x02,0x83,0xFF,0x80,0x00,0x82,0x7F,0xFF,0x00
	};
	unsigned char checkinfo_yOffset[] = { 
		0x02,0x83,0xFF,0x80,0x00,0x82,0x7F,0xFF,0x00
	};
	unsigned char checkinfo_zOffset[] = { 
		0x02,0x83,0xFF,0x80,0x00,0x82,0x7F,0xFF,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("xOffset", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->xOffset), checkinfo_xOffset);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("yOffset", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->yOffset), checkinfo_yOffset);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_RegionOffsets_zOffset == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("zOffset", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->zOffset), checkinfo_zOffset);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_RegionPointSet(RegionPointSet *value)
{
	int ret = 0;

	unsigned char checkinfo_anchor[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_scale[] = { 
		0x02,0x00,0x0F,0x00
	};
	unsigned char checkinfo_nodeList[] = { 
		0x02,0x01,0x40,0x00
	};

	if (value == NULL) return -1;
	if (value->DEF_RegionPointSet_anchor == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("anchor", 0);
		  ret=ASN1_CHECK_Position3D(value->anchor);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_RegionPointSet_scale == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("scale", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->scale), checkinfo_scale);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	{ size_t saved=MqttDiag_enter("nodeList", 0);
	  ret=ASN1_CHECK_RegionList(&(value->nodeList));
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_RegionalExtension(RegionalExtension *value)
{
	int ret = 0;

	unsigned char checkinfo_regionId[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_regExtValue[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("regionId", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->regionId), checkinfo_regionId);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("regExtValue", 0);
	  ret=ASN1_CHECK_OpenType(&(value->regExtValue), checkinfo_regExtValue);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_RegulatorySpeedLimit(RegulatorySpeedLimit *value)
{
	int ret = 0;

	unsigned char checkinfo_type[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_speed[] = { 
		0x02,0x00,0x82,0x1F,0xFF,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("type", 0);
	  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->type), checkinfo_type);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("speed", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->speed), checkinfo_speed);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_RidingNotification_KOR(RidingNotification_KOR *value)
{
	int ret = 0;

	unsigned char checkinfo_stopID[] = { 
		0x02,0x01,0x82,0x00,0x80,0x00
	};
	unsigned char checkinfo_disabled[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_boarding[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if (value->DEF_RidingNotification_KOR_stopID == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("stopID", 0);
		  ret=ASN1_CHECK_UTF8Str(&(value->stopID), checkinfo_stopID);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_RidingNotification_KOR_disabled == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("disabled", 0);
		  ret=ASN1_CHECK_BOOLEAN(&(value->disabled), checkinfo_disabled);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_RidingNotification_KOR_boarding == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("boarding", 0);
		  ret=ASN1_CHECK_BOOLEAN(&(value->boarding), checkinfo_boarding);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_RoadSegmentReferenceID(RoadSegmentReferenceID *value)
{
	int ret = 0;

	unsigned char checkinfo_region[] = { 
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_id[] = { 
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};

	if (value == NULL) return -1;
	if (value->DEF_RoadSegmentReferenceID_region == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("region", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->region), checkinfo_region);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	{ size_t saved=MqttDiag_enter("id", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->id), checkinfo_id);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_RoadSignID(RoadSignID *value)
{
	int ret = 0;

	unsigned char checkinfo_position[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_viewAngle[] = { 
		0x02,0x10,0x10,0x00
	};
	unsigned char checkinfo_mutcdCode[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_crc[] = { 
		0x02,0x02,0x02,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("position", 0);
	  ret=ASN1_CHECK_Position3D(value->position);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("viewAngle", 0);
	  ret=ASN1_CHECK_BITSTRING(&(value->viewAngle), checkinfo_viewAngle);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_RoadSignID_mutcdCode == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("mutcdCode", 0);
		  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->mutcdCode), checkinfo_mutcdCode);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_RoadSignID_crc == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("crc", 0);
		  ret=ASN1_CHECK_OCTETSTRING(&(value->crc), checkinfo_crc);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_SPAT(SPAT *value)
{
	int ret = 0;

	unsigned char checkinfo_timeStamp[] = { 
		0x02,0x00,0x83,0x08,0x0A,0xC0,0x00
	};
	unsigned char checkinfo_name[] = { 
		0x02,0x01,0x3F,0x00
	};
	unsigned char checkinfo_intersections[] = { 
		0x02,0x01,0x20,0x00
	};
	unsigned char checkinfo_regional[] = { 
		0x02,0x01,0x04,0x00
	};

	if (value == NULL) return -1;
	if (value->DEF_SPAT_timeStamp == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("timeStamp", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->timeStamp), checkinfo_timeStamp);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_SPAT_name == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("name", 0);
		  ret=ASN1_CHECK_IA5String(&(value->name), checkinfo_name);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	{ size_t saved=MqttDiag_enter("intersections", 0);
	  ret=ASN1_CHECK_IntersectionStateList(&(value->intersections));
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_SPAT_regional == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_CHECK_SPAT_regional(&(value->regional));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_SPAT_regional(SPAT_regional *value)
{
	int ret = 0;

	unsigned char checkinfo_SPAT_regional[] = { 
		0x02,0x01,0x04,0x00
	};
	unsigned char checkinfo_SPAT_regional_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_RegionalExtension(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_SegmentAttributeLL(SegmentAttributeLL *value)
{
	unsigned char checkinfo_SegmentAttributeLL[] = {
		0x26,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,
		0x0F,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,
		0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ENUMERATED((ASNINT32 *)value, checkinfo_SegmentAttributeLL);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_SegmentAttributeLLList(SegmentAttributeLLList *value)
{
	int ret = 0;

	unsigned char checkinfo_SegmentAttributeLLList[] = { 
		0x02,0x01,0x08,0x00
	};
	unsigned char checkinfo_SegmentAttributeLLList_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)pnode->data, checkinfo_SegmentAttributeLLList_pdata);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_SegmentAttributeXY(SegmentAttributeXY *value)
{
	unsigned char checkinfo_SegmentAttributeXY[] = {
		0x26,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,
		0x0F,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,
		0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x00
	};
	int ret = 0;
	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ENUMERATED((ASNINT32 *)value, checkinfo_SegmentAttributeXY);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_SegmentAttributeXYList(SegmentAttributeXYList *value)
{
	int ret = 0;

	unsigned char checkinfo_SegmentAttributeXYList[] = { 
		0x02,0x01,0x08,0x00
	};
	unsigned char checkinfo_SegmentAttributeXYList_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)pnode->data, checkinfo_SegmentAttributeXYList_pdata);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_ServiceAreaInformation_KOR(ServiceAreaInformation_KOR *value)
{
	int ret = 0;

	unsigned char checkinfo_name[] = { 
		0x02,0x01,0x82,0x00,0x80,0x00
	};
	unsigned char checkinfo_id[] = { 
		0x02,0x01,0x82,0x00,0x80,0x00
	};
	unsigned char checkinfo_direction[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_stationInfo[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_parkingInfo[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("name", 0);
	  ret=ASN1_CHECK_UTF8Str(&(value->name), checkinfo_name);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("id", 0);
	  ret=ASN1_CHECK_UTF8Str(&(value->id), checkinfo_id);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("direction", 0);
	  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->direction), checkinfo_direction);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_ServiceAreaInformation_KOR_stationInfo == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("stationInfo", 0);
		  ret=ASN1_CHECK_ServiceAreaInformation_KOR_stationInfo(&(value->stationInfo));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_ServiceAreaInformation_KOR_parkingInfo == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("parkingInfo", 0);
		  ret=ASN1_CHECK_ServiceAreaInformation_KOR_parkingInfo(&(value->parkingInfo));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_ServiceAreaInformation_KOR_parkingInfo(ServiceAreaInformation_KOR_parkingInfo *value)
{
	int ret = 0;

	unsigned char checkinfo_ServiceAreaInformation_KOR_parkingInfo[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_ServiceAreaInformation_KOR_parkingInfo_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_ParkingZoneInformation_KOR(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_ServiceAreaInformation_KOR_stationInfo(ServiceAreaInformation_KOR_stationInfo *value)
{
	int ret = 0;

	unsigned char checkinfo_ServiceAreaInformation_KOR_stationInfo[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_ServiceAreaInformation_KOR_stationInfo_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_StationInformation_KOR(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_ShapePointSet(ShapePointSet *value)
{
	int ret = 0;

	unsigned char checkinfo_anchor[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_laneWidth[] = { 
		0x02,0x00,0x82,0x7F,0xFF,0x00
	};
	unsigned char checkinfo_directionality[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_nodeList[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if (value->DEF_ShapePointSet_anchor == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("anchor", 0);
		  ret=ASN1_CHECK_Position3D(value->anchor);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_ShapePointSet_laneWidth == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("laneWidth", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->laneWidth), checkinfo_laneWidth);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_ShapePointSet_directionality == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("directionality", 0);
		  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->directionality), checkinfo_directionality);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	{ size_t saved=MqttDiag_enter("nodeList", 0);
	  ret=ASN1_CHECK_NodeListXY(value->nodeList);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_SpeedLimit(SpeedLimit *value)
{
	int ret = 0;

	unsigned char checkinfo_SpeedLimit[] = { 
		0x02,0x01,0x10,0x00
	};
	unsigned char checkinfo_SpeedLimit_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_SpeedLimit_element(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_SpeedLimitList(SpeedLimitList *value)
{
	int ret = 0;

	unsigned char checkinfo_SpeedLimitList[] = { 
		0x02,0x01,0x09,0x00
	};
	unsigned char checkinfo_SpeedLimitList_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_RegulatorySpeedLimit(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_SpeedLimit_element(SpeedLimit_element *value)
{
	int ret = 0;

	unsigned char checkinfo_item[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("item", 0);
	  ret=ASN1_CHECK_SpeedLimit_element_item(value->item);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_SpeedLimit_element_item(SpeedLimit_element_item *value)
{
	int ret = 0;

	unsigned char checkinfo_itis[] = { 
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_text[] = { 
		0x02,0x01,0x10,0x00
	};

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_SpeedLimit_element_item_itis:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_INTEGER(&value->elements.itis, checkinfo_itis);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_SpeedLimit_element_item_text:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_IA5String(&value->elements.text, checkinfo_text);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	default: break;
	}
	return ret;
}
int ASN1_CHECK_StationInformation_KOR(StationInformation_KOR *value)
{
	int ret = 0;

	unsigned char checkinfo_type[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_capacity[] = { 
		0x02,0x00,0x82,0x01,0x00,0x00
	};
	unsigned char checkinfo_maxcapacity[] = { 
		0x02,0x00,0x82,0x01,0x00,0x00
	};
	unsigned char checkinfo_price[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("type", 0);
	  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->type), checkinfo_type);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_StationInformation_KOR_capacity == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("capacity", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->capacity), checkinfo_capacity);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_StationInformation_KOR_maxcapacity == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("maxcapacity", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->maxcapacity), checkinfo_maxcapacity);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_StationInformation_KOR_price == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("price", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->price), checkinfo_price);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_TimeChangeDetails(TimeChangeDetails *value)
{
	int ret = 0;

	unsigned char checkinfo_startTime[] = { 
		0x02,0x00,0x83,0x00,0x8D,0x0F,0x00
	};
	unsigned char checkinfo_minEndTime[] = { 
		0x02,0x00,0x83,0x00,0x8D,0x0F,0x00
	};
	unsigned char checkinfo_maxEndTime[] = { 
		0x02,0x00,0x83,0x00,0x8D,0x0F,0x00
	};
	unsigned char checkinfo_likelyTime[] = { 
		0x02,0x00,0x83,0x00,0x8D,0x0F,0x00
	};
	unsigned char checkinfo_confidence[] = { 
		0x02,0x00,0x0F,0x00
	};
	unsigned char checkinfo_nextTime[] = { 
		0x02,0x00,0x83,0x00,0x8D,0x0F,0x00
	};

	if (value == NULL) return -1;
	if (value->DEF_TimeChangeDetails_startTime == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("startTime", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->startTime), checkinfo_startTime);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	{ size_t saved=MqttDiag_enter("minEndTime", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->minEndTime), checkinfo_minEndTime);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_TimeChangeDetails_maxEndTime == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("maxEndTime", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->maxEndTime), checkinfo_maxEndTime);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_TimeChangeDetails_likelyTime == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("likelyTime", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->likelyTime), checkinfo_likelyTime);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_TimeChangeDetails_confidence == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("confidence", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->confidence), checkinfo_confidence);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_TimeChangeDetails_nextTime == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("nextTime", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->nextTime), checkinfo_nextTime);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_TollgateLaneInformation_KOR(TollgateLaneInformation_KOR *value)
{
	int ret = 0;

	unsigned char checkinfo_name[] = { 
		0x02,0x01,0x82,0x00,0x80,0x00
	};
	unsigned char checkinfo_heading[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_lanes[] = { 
		0x02,0x01,0x20,0x00
	};

	if (value == NULL) return -1;
	if (value->DEF_TollgateLaneInformation_KOR_name == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("name", 0);
		  ret=ASN1_CHECK_UTF8Str(&(value->name), checkinfo_name);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_TollgateLaneInformation_KOR_heading == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("heading", 0);
		  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->heading), checkinfo_heading);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_TollgateLaneInformation_KOR_lanes == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("lanes", 0);
		  ret=ASN1_CHECK_TollgateLaneInformation_KOR_lanes(&(value->lanes));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_TollgateLaneInformation_KOR_lanes(TollgateLaneInformation_KOR_lanes *value)
{
	int ret = 0;

	unsigned char checkinfo_TollgateLaneInformation_KOR_lanes[] = { 
		0x02,0x01,0x20,0x00
	};
	unsigned char checkinfo_TollgateLaneInformation_KOR_lanes_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_TollgateLane_KOR(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_TollgateLane_KOR(TollgateLane_KOR *value)
{
	int ret = 0;

	unsigned char checkinfo_laneNo[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_linkID[] = { 
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_type[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_open[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	if (value->DEF_TollgateLane_KOR_laneNo == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("laneNo", 0);
		  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->laneNo), checkinfo_laneNo);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_TollgateLane_KOR_linkID == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("linkID", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->linkID), checkinfo_linkID);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_TollgateLane_KOR_type == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("type", 0);
		  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->type), checkinfo_type);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_TollgateLane_KOR_open == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("open", 0);
		  ret=ASN1_CHECK_BOOLEAN(&(value->open), checkinfo_open);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_TrafficLightStatusList_KOR(TrafficLightStatusList_KOR *value)
{
	int ret = 0;

	unsigned char checkinfo_TrafficLightStatusList_KOR[] = { 
		0x02,0x01,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_TrafficLightStatusList_KOR_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_TrafficLightStatus_KOR(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_TrafficLightStatusMessage(TrafficLightStatusMessage *value)
{
	int ret = 0;

	unsigned char checkinfo_traffiLightID[] = { 
		0x02,0x00,0x85,0x00,0xFF,0xFF,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_lon[] = { 
		0x02,0x84,0x94,0xB6,0x2E,0x01,0x84,0x6B,0x49,0xD2,0x01,0x00
	};
	unsigned char checkinfo_lat[] = { 
		0x02,0x84,0xCA,0x5B,0x17,0x00,0x84,0x35,0xA4,0xE9,0x01,0x00
	};
	unsigned char checkinfo_operationStatus[] = { 
		0x02,0x08,0x08,0x00
	};
	unsigned char checkinfo_controllerStatus[] = { 
		0x02,0x08,0x08,0x00
	};
	unsigned char checkinfo_cycleCounter[] = { 
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_cycleTime[] = { 
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_currentTime[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_trafficLightStatus[] = { 
		0x02,0x01,0x82,0x00,0xFF,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("traffiLightID", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->traffiLightID), checkinfo_traffiLightID);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_TrafficLightStatusMessage_lon == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("lon", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->lon), checkinfo_lon);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_TrafficLightStatusMessage_lat == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("lat", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->lat), checkinfo_lat);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	{ size_t saved=MqttDiag_enter("operationStatus", 0);
	  ret=ASN1_CHECK_BITSTRING(&(value->operationStatus), checkinfo_operationStatus);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("controllerStatus", 0);
	  ret=ASN1_CHECK_BITSTRING(&(value->controllerStatus), checkinfo_controllerStatus);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("cycleCounter", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->cycleCounter), checkinfo_cycleCounter);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("cycleTime", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->cycleTime), checkinfo_cycleTime);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("currentTime", 0);
	  ret=ASN1_CHECK_DDateTime(value->currentTime);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("trafficLightStatus", 0);
	  ret=ASN1_CHECK_TrafficLightStatusList_KOR(&(value->trafficLightStatus));
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_TrafficLightStatus_KOR(TrafficLightStatus_KOR *value)
{
	int ret = 0;

	unsigned char checkinfo_trafficLightType[] = { 
		0x02,0x00,0x0F,0x00
	};
	unsigned char checkinfo_consecutiveTrafficLight[] = { 
		0x02,0x00,0x0F,0x00
	};
	unsigned char checkinfo_trafficLightIntervalType[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_pedestrianCall[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_actuatedinterval[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_permissiveNonProtected[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_lightingStatus[] = { 
		0x02,0x00,0x0A,0x00
	};
	unsigned char checkinfo_maxIntervalLength[] = { 
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_remainingTime[] = { 
		0x02,0x00,0x82,0x00,0xFF,0x00
	};
	unsigned char checkinfo_directionCode[] = { 
		0x02,0x0A,0x59,0x00
	};
	unsigned char checkinfo_reserved[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("trafficLightType", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->trafficLightType), checkinfo_trafficLightType);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("consecutiveTrafficLight", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->consecutiveTrafficLight), checkinfo_consecutiveTrafficLight);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("trafficLightIntervalType", 0);
	  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->trafficLightIntervalType), checkinfo_trafficLightIntervalType);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("pedestrianCall", 0);
	  ret=ASN1_CHECK_BOOLEAN(&(value->pedestrianCall), checkinfo_pedestrianCall);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("actuatedinterval", 0);
	  ret=ASN1_CHECK_BOOLEAN(&(value->actuatedinterval), checkinfo_actuatedinterval);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("permissiveNonProtected", 0);
	  ret=ASN1_CHECK_BOOLEAN(&(value->permissiveNonProtected), checkinfo_permissiveNonProtected);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("lightingStatus", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->lightingStatus), checkinfo_lightingStatus);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("maxIntervalLength", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->maxIntervalLength), checkinfo_maxIntervalLength);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("remainingTime", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->remainingTime), checkinfo_remainingTime);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("directionCode", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->directionCode), checkinfo_directionCode);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("reserved", 0);
	  ret=ASN1_CHECK_BOOLEAN(&(value->reserved), checkinfo_reserved);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_TravelerDataFrame(TravelerDataFrame *value)
{
	int ret = 0;

	unsigned char checkinfo_notUsed[] = { 
		0x02,0x00,0x1F,0x00
	};
	unsigned char checkinfo_frameType[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_msgId[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_startYear[] = { 
		0x02,0x00,0x82,0x0F,0xFF,0x00
	};
	unsigned char checkinfo_startTime[] = { 
		0x02,0x00,0x83,0x08,0x0A,0xC0,0x00
	};
	unsigned char checkinfo_durationTime[] = { 
		0x02,0x00,0x82,0x7D,0x00,0x00
	};
	unsigned char checkinfo_priority[] = { 
		0x02,0x00,0x07,0x00
	};
	unsigned char checkinfo_notUsed1[] = { 
		0x02,0x00,0x1F,0x00
	};
	unsigned char checkinfo_regions[] = { 
		0x02,0x01,0x10,0x00
	};
	unsigned char checkinfo_notUsed2[] = { 
		0x02,0x00,0x1F,0x00
	};
	unsigned char checkinfo_notUsed3[] = { 
		0x02,0x00,0x1F,0x00
	};
	unsigned char checkinfo_content[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_url[] = { 
		0x02,0x01,0x0F,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("notUsed", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->notUsed), checkinfo_notUsed);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("frameType", 0);
	  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->frameType), checkinfo_frameType);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("msgId", 0);
	  ret=ASN1_CHECK_TravelerDataFrame_msgId(value->msgId);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_TravelerDataFrame_startYear == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("startYear", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->startYear), checkinfo_startYear);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	{ size_t saved=MqttDiag_enter("startTime", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->startTime), checkinfo_startTime);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("durationTime", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->durationTime), checkinfo_durationTime);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("priority", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->priority), checkinfo_priority);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("notUsed1", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->notUsed1), checkinfo_notUsed1);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("regions", 0);
	  ret=ASN1_CHECK_TravelerDataFrame_regions(&(value->regions));
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("notUsed2", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->notUsed2), checkinfo_notUsed2);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("notUsed3", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->notUsed3), checkinfo_notUsed3);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("content", 0);
	  ret=ASN1_CHECK_TravelerDataFrame_content(value->content);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_TravelerDataFrame_url == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("url", 0);
		  ret=ASN1_CHECK_IA5String(&(value->url), checkinfo_url);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_TravelerDataFrameAdditionalInformation_KOR(TravelerDataFrameAdditionalInformation_KOR *value)
{
	int ret = 0;

	unsigned char checkinfo_dataFrameIndex[] = { 
		0x02,0x00,0x08,0x00
	};
	unsigned char checkinfo_events[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_vehicleRidingStatus[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_weatherInfo[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_serviceArea[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_tollgate[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("dataFrameIndex", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->dataFrameIndex), checkinfo_dataFrameIndex);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_TravelerDataFrameAdditionalInformation_KOR_events == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("events", 0);
		  ret=ASN1_CHECK_EventOrSvcInfo_KOR(value->events);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_TravelerDataFrameAdditionalInformation_KOR_vehicleRidingStatus == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("vehicleRidingStatus", 0);
		  ret=ASN1_CHECK_RidingNotification_KOR(value->vehicleRidingStatus);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_TravelerDataFrameAdditionalInformation_KOR_weatherInfo == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("weatherInfo", 0);
		  ret=ASN1_CHECK_WeatherInfo_KOR(value->weatherInfo);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_TravelerDataFrameAdditionalInformation_KOR_serviceArea == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("serviceArea", 0);
		  ret=ASN1_CHECK_ServiceAreaInformation_KOR(value->serviceArea);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_TravelerDataFrameAdditionalInformation_KOR_tollgate == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("tollgate", 0);
		  ret=ASN1_CHECK_TollgateLaneInformation_KOR(value->tollgate);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_TravelerDataFrameList(TravelerDataFrameList *value)
{
	int ret = 0;

	unsigned char checkinfo_TravelerDataFrameList[] = { 
		0x02,0x01,0x08,0x00
	};
	unsigned char checkinfo_TravelerDataFrameList_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_TravelerDataFrame(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_TravelerDataFrame_content(TravelerDataFrame_content *value)
{
	int ret = 0;

	unsigned char checkinfo_advisory[] = { 
		0x02,0x01,0x64,0x00
	};
	unsigned char checkinfo_workZone[] = { 
		0x02,0x01,0x10,0x00
	};
	unsigned char checkinfo_genericSign[] = { 
		0x02,0x01,0x10,0x00
	};
	unsigned char checkinfo_speedLimit[] = { 
		0x02,0x01,0x10,0x00
	};
	unsigned char checkinfo_exitService[] = { 
		0x02,0x01,0x10,0x00
	};

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_TravelerDataFrame_content_advisory:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_ITIScodesAndText(&value->elements.advisory);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_TravelerDataFrame_content_workZone:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_WorkZone(&value->elements.workZone);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_TravelerDataFrame_content_genericSign:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_GenericSignage(&value->elements.genericSign);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_TravelerDataFrame_content_speedLimit:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_SpeedLimit(&value->elements.speedLimit);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_TravelerDataFrame_content_exitService:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_ExitService(&value->elements.exitService);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	default: break;
	}
	return ret;
}
int ASN1_CHECK_TravelerDataFrame_msgId(TravelerDataFrame_msgId *value)
{
	int ret = 0;

	unsigned char checkinfo_furtherInfoID[] = { 
		0x02,0x02,0x02,0x00
	};
	unsigned char checkinfo_roadSignID[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_TravelerDataFrame_msgId_furtherInfoID:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_OCTETSTRING(&value->elements.furtherInfoID, checkinfo_furtherInfoID);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_TravelerDataFrame_msgId_roadSignID:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_RoadSignID(value->elements.roadSignID);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	default: break;
	}
	return ret;
}
int ASN1_CHECK_TravelerDataFrame_regions(TravelerDataFrame_regions *value)
{
	int ret = 0;

	unsigned char checkinfo_TravelerDataFrame_regions[] = { 
		0x02,0x01,0x10,0x00
	};
	unsigned char checkinfo_TravelerDataFrame_regions_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_GeographicalPath(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_TravelerInformation(TravelerInformation *value)
{
	int ret = 0;

	unsigned char checkinfo_msgCnt[] = { 
		0x02,0x00,0x7F,0x00
	};
	unsigned char checkinfo_timeStamp[] = { 
		0x02,0x00,0x83,0x08,0x0A,0xC0,0x00
	};
	unsigned char checkinfo_packetID[] = { 
		0x02,0x09,0x09,0x00
	};
	unsigned char checkinfo_urlB[] = { 
		0x02,0x01,0x2D,0x00
	};
	unsigned char checkinfo_dataFrames[] = { 
		0x02,0x01,0x08,0x00
	};
	unsigned char checkinfo_regional[] = { 
		0x02,0x01,0x04,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("msgCnt", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->msgCnt), checkinfo_msgCnt);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_TravelerInformation_timeStamp == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("timeStamp", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->timeStamp), checkinfo_timeStamp);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_TravelerInformation_packetID == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("packetID", 0);
		  ret=ASN1_CHECK_OCTETSTRING(&(value->packetID), checkinfo_packetID);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_TravelerInformation_urlB == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("urlB", 0);
		  ret=ASN1_CHECK_IA5String(&(value->urlB), checkinfo_urlB);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	{ size_t saved=MqttDiag_enter("dataFrames", 0);
	  ret=ASN1_CHECK_TravelerDataFrameList(&(value->dataFrames));
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_TravelerInformation_regional == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_CHECK_TravelerInformation_regional(&(value->regional));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_TravelerInformation_KOR(TravelerInformation_KOR *value)
{
	int ret = 0;

	unsigned char checkinfo_msgID[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_additionalInfo[] = { 
		0x02,0x01,0x08,0x00
	};

	if (value == NULL) return -1;
	if (value->DEF_TravelerInformation_KOR_msgID == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("msgID", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->msgID), checkinfo_msgID);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_TravelerInformation_KOR_additionalInfo == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("additionalInfo", 0);
		  ret=ASN1_CHECK_TravelerInformation_KOR_additionalInfo(&(value->additionalInfo));
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_TravelerInformation_KOR_additionalInfo(TravelerInformation_KOR_additionalInfo *value)
{
	int ret = 0;

	unsigned char checkinfo_TravelerInformation_KOR_additionalInfo[] = { 
		0x02,0x01,0x08,0x00
	};
	unsigned char checkinfo_TravelerInformation_KOR_additionalInfo_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_TravelerDataFrameAdditionalInformation_KOR(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_TravelerInformation_regional(TravelerInformation_regional *value)
{
	int ret = 0;

	unsigned char checkinfo_TravelerInformation_regional[] = { 
		0x02,0x01,0x04,0x00
	};
	unsigned char checkinfo_TravelerInformation_regional_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_RegionalExtension(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_ValidRegion(ValidRegion *value)
{
	int ret = 0;

	unsigned char checkinfo_direction[] = { 
		0x02,0x10,0x10,0x00
	};
	unsigned char checkinfo_extent[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_area[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("direction", 0);
	  ret=ASN1_CHECK_BITSTRING(&(value->direction), checkinfo_direction);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (value->DEF_ValidRegion_extent == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("extent", 0);
		  ret=ASN1_CHECK_ENUMERATED((ASNINT32*)&(value->extent), checkinfo_extent);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	{ size_t saved=MqttDiag_enter("area", 0);
	  ret=ASN1_CHECK_ValidRegion_area(value->area);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_ValidRegion_area(ValidRegion_area *value)
{
	int ret = 0;

	unsigned char checkinfo_shapePointSet[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_circle[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	unsigned char checkinfo_regionPointSet[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_ValidRegion_area_shapePointSet:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_ShapePointSet(value->elements.shapePointSet);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_ValidRegion_area_circle:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_Circle(value->elements.circle);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_ValidRegion_area_regionPointSet:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_RegionPointSet(value->elements.regionPointSet);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	default: break;
	}
	return ret;
}
int ASN1_CHECK_VehicleSize(VehicleSize *value)
{
	int ret = 0;

	unsigned char checkinfo_width[] = { 
		0x02,0x00,0x82,0x03,0xFF,0x00
	};
	unsigned char checkinfo_length[] = { 
		0x02,0x00,0x82,0x0F,0xFF,0x00
	};

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("width", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->width), checkinfo_width);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("length", 0);
	  ret=ASN1_CHECK_INTEGER(&(value->length), checkinfo_length);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_WeatherInfo_KOR(WeatherInfo_KOR *value)
{
	int ret = 0;

	unsigned char checkinfo_temp[] = { 
		0x02,0x00,0x82,0x00,0xBF,0x00
	};
	unsigned char checkinfo_rainfall[] = { 
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_humidity[] = { 
		0x02,0x00,0x64,0x00
	};
	unsigned char checkinfo_windDir[] = { 
		0x02,0x10,0x10,0x00
	};
	unsigned char checkinfo_windSpd[] = { 
		0x02,0x00,0x82,0x27,0x10,0x00
	};

	if (value == NULL) return -1;
	if (value->DEF_WeatherInfo_KOR_temp == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("temp", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->temp), checkinfo_temp);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_WeatherInfo_KOR_rainfall == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("rainfall", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->rainfall), checkinfo_rainfall);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_WeatherInfo_KOR_humidity == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("humidity", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->humidity), checkinfo_humidity);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_WeatherInfo_KOR_windDir == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("windDir", 0);
		  ret=ASN1_CHECK_BITSTRING(&(value->windDir), checkinfo_windDir);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	if (value->DEF_WeatherInfo_KOR_windSpd == 1)
	{ /* OPTIONAL start */
		{ size_t saved=MqttDiag_enter("windSpd", 0);
		  ret=ASN1_CHECK_INTEGER(&(value->windSpd), checkinfo_windSpd);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	} /* OPTIONAL end */
	return ret;
}
int ASN1_CHECK_WorkZone(WorkZone *value)
{
	int ret = 0;

	unsigned char checkinfo_WorkZone[] = { 
		0x02,0x01,0x10,0x00
	};
	unsigned char checkinfo_WorkZone_pdata[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */
	int count;
	ASN1ListNode* pnode;
	if (value == NULL) return -1;
	if (value->head == NULL) return -1;
	if (value->count < 0) return -1;
	pnode = value->head->next;
	count = value->count;
	while (count) {
		{ size_t saved=MqttDiag_enter("", value->count-count+1);
		  ret=ASN1_CHECK_WorkZone_element(pnode->data);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		pnode = pnode->next;
		count--;
	}
	return ret;
}
int ASN1_CHECK_WorkZone_element(WorkZone_element *value)
{
	int ret = 0;

	unsigned char checkinfo_item[] = { 0x00, 0x00 }; /* 0x00 == t->consterminal.cons_type */

	if (value == NULL) return -1;
	{ size_t saved=MqttDiag_enter("item", 0);
	  ret=ASN1_CHECK_WorkZone_element_item(value->item);
	  if(ret<0) MqttDiag_failure(NULL);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_CHECK_WorkZone_element_item(WorkZone_element_item *value)
{
	int ret = 0;

	unsigned char checkinfo_itis[] = { 
		0x02,0x00,0x83,0x00,0xFF,0xFF,0x00
	};
	unsigned char checkinfo_text[] = { 
		0x02,0x01,0x10,0x00
	};

	if (value == NULL) return -1;
	switch (value->M)
	{
	case DEF_WorkZone_element_item_itis:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_INTEGER(&value->elements.itis, checkinfo_itis);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	case DEF_WorkZone_element_item_text:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_CHECK_IA5String(&value->elements.text, checkinfo_text);
		  if(ret<0) MqttDiag_failure(NULL);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		break;
	default: break;
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_AccelerationSet4Way(ASN1WorkSpace *workspace, AccelerationSet4Way *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_lon = { ASN1_CONST64(-2000), ASN1_CONST64(2001), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_lat = { ASN1_CONST64(-2000), ASN1_CONST64(2001), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_vert = { ASN1_CONST64(-127), ASN1_CONST64(127), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_yaw = { ASN1_CONST64(-32767), ASN1_CONST64(32767), NULL, 0, CONS, 0, 0 };

	{ size_t saved=MqttDiag_enter("lon", 0);

	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->lon), &consinfo_lon);

	  if(ret<0) MqttDiag_failure(workspace);

	  MqttDiag_leave(saved);

	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("lat", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->lat), &consinfo_lat);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("vert", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->vert), &consinfo_vert);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("yaw", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->yaw), &consinfo_yaw);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_AdvisorySpeed(ASN1WorkSpace *workspace, AdvisorySpeed *value)
{
	int ret = 0;
	ASNINT32 ui_type;
	ASNINT32 ui_confidence;
	struct Asn1ConsInfo consinfo_type = { ASN1_CONST64(0), ASN1_CONST64(3), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_speed = { ASN1_CONST64(0), ASN1_CONST64(500), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_confidence = { ASN1_CONST64(0), ASN1_CONST64(7), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_distance = { ASN1_CONST64(0), ASN1_CONST64(10000), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_class = { ASN1_CONST64(0), ASN1_CONST64(255), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };

	ASNBOOL extbit_AdvisorySpeed;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_AdvisorySpeed);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 5, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_type, &consinfo_type);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (consinfo_type.enumextbit == 0)
	{
		switch(ui_type)
		{
		case 0: value->type = AdvisorySpeedType_none; break;
		case 1: value->type = AdvisorySpeedType_greenwave; break;
		case 2: value->type = AdvisorySpeedType_ecoDrive; break;
		case 3: value->type = AdvisorySpeedType_transit; break;
		default: break;
		}
	}
	else
	{
		switch(ui_type)
		{
		default: value->type = ui_type; break;
		}
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_AdvisorySpeed_speed = 1;
		{ size_t saved=MqttDiag_enter("speed", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->speed), &consinfo_speed);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_AdvisorySpeed_confidence = 1;
		{ size_t saved=MqttDiag_enter("", 0);
		  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_confidence, &consinfo_confidence);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (consinfo_confidence.enumextbit == 0)
		{
			switch(ui_confidence)
			{
			case 0: value->confidence = SpeedConfidence_unavailable; break;
			case 1: value->confidence = SpeedConfidence_prec100ms; break;
			case 2: value->confidence = SpeedConfidence_prec10ms; break;
			case 3: value->confidence = SpeedConfidence_prec5ms; break;
			case 4: value->confidence = SpeedConfidence_prec1ms; break;
			case 5: value->confidence = SpeedConfidence_prec0_1ms; break;
			case 6: value->confidence = SpeedConfidence_prec0_05ms; break;
			case 7: value->confidence = SpeedConfidence_prec0_01ms; break;
			default: value->confidence = ui_confidence; break;
			}
		}
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_AdvisorySpeed_distance = 1;
		{ size_t saved=MqttDiag_enter("distance", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->distance), &consinfo_distance);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 4) == 1)
	{
		value->DEF_AdvisorySpeed_class = 1;
		{ size_t saved=MqttDiag_enter("class", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->class), &consinfo_class);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 5) == 1)
	{
		value->DEF_AdvisorySpeed_regional = 1;
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_PER_UNAlign_Dec_AdvisorySpeed_regional(workspace, &(value->regional));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_AdvisorySpeed == 1)
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
int ASN1_PER_UNAlign_Data_Dec_AdvisorySpeedList(ASN1WorkSpace *workspace, AdvisorySpeedList *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_AdvisorySpeedList = { ASN1_CONST64(1), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_AdvisorySpeedList_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	AdvisorySpeed *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_AdvisorySpeedList);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (AdvisorySpeed *)mpool_calloc(GetMemPool(workspace), sizeof(AdvisorySpeed), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_AdvisorySpeed(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_AdvisorySpeed_regional(ASN1WorkSpace *workspace, AdvisorySpeed_regional *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_AdvisorySpeed_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_AdvisorySpeed_regional_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	RegionalExtension *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_AdvisorySpeed_regional);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (RegionalExtension *)mpool_calloc(GetMemPool(workspace), sizeof(RegionalExtension), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_RegionalExtension(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_BSMcoreData(ASN1WorkSpace *workspace, BSMcoreData *value)
{
	int ret = 0;
	ASNINT32 ui_transmission;
	struct Asn1ConsInfo consinfo_msgCnt = { ASN1_CONST64(0), ASN1_CONST64(127), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_id = { ASN1_CONST64(4), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_secMark = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_lat = { ASN1_CONST64(-900000000), ASN1_CONST64(900000001), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_lon = { ASN1_CONST64(-1799999999), ASN1_CONST64(1800000001), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_elev = { ASN1_CONST64(-4096), ASN1_CONST64(61439), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_accuracy = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_transmission = { ASN1_CONST64(0), ASN1_CONST64(7), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_speed = { ASN1_CONST64(0), ASN1_CONST64(8191), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_heading = { ASN1_CONST64(0), ASN1_CONST64(28800), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_angle = { ASN1_CONST64(-126), ASN1_CONST64(127), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_accelSet = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_brakes = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_size = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	value->accuracy = (PositionalAccuracy *)mpool_malloc(workspace->Pmemory, sizeof(PositionalAccuracy));
	memset(value->accuracy, 0, sizeof(PositionalAccuracy));
	value->accelSet = (AccelerationSet4Way *)mpool_malloc(workspace->Pmemory, sizeof(AccelerationSet4Way));
	memset(value->accelSet, 0, sizeof(AccelerationSet4Way));
	value->brakes = (BrakeSystemStatus *)mpool_malloc(workspace->Pmemory, sizeof(BrakeSystemStatus));
	memset(value->brakes, 0, sizeof(BrakeSystemStatus));
	value->size = (VehicleSize *)mpool_malloc(workspace->Pmemory, sizeof(VehicleSize));
	memset(value->size, 0, sizeof(VehicleSize));
	{ size_t saved=MqttDiag_enter("msgCnt", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->msgCnt), &consinfo_msgCnt);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("id", 0);
	  ret=ASN1_PER_UNAlign_Dec_OCTETSTRING(workspace, &(value->id), &consinfo_id);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("secMark", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->secMark), &consinfo_secMark);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("lat", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->lat), &consinfo_lat);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("lon", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->lon), &consinfo_lon);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("elev", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->elev), &consinfo_elev);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("accuracy", 0);
	  ret=ASN1_PER_UNAlign_Dec_PositionalAccuracy(workspace, value->accuracy);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_transmission, &consinfo_transmission);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (consinfo_transmission.enumextbit == 0)
	{
		switch(ui_transmission)
		{
		case 0: value->transmission = TransmissionState_neutral; break;
		case 1: value->transmission = TransmissionState_park; break;
		case 2: value->transmission = TransmissionState_forwardGears; break;
		case 3: value->transmission = TransmissionState_reverseGears; break;
		case 4: value->transmission = TransmissionState_reserved1; break;
		case 5: value->transmission = TransmissionState_reserved2; break;
		case 6: value->transmission = TransmissionState_reserved3; break;
		case 7: value->transmission = TransmissionState_unavailable; break;
		default: value->transmission = ui_transmission; break;
		}
	}
	{ size_t saved=MqttDiag_enter("speed", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->speed), &consinfo_speed);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("heading", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->heading), &consinfo_heading);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("angle", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->angle), &consinfo_angle);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("accelSet", 0);
	  ret=ASN1_PER_UNAlign_Dec_AccelerationSet4Way(workspace, value->accelSet);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("brakes", 0);
	  ret=ASN1_PER_UNAlign_Dec_BrakeSystemStatus(workspace, value->brakes);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("size", 0);
	  ret=ASN1_PER_UNAlign_Dec_VehicleSize(workspace, value->size);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_BasicSafetyMessage(ASN1WorkSpace *workspace, BasicSafetyMessage *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_coreData = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_partII = { ASN1_CONST64(1), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };

	ASNBOOL extbit_BasicSafetyMessage;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_BasicSafetyMessage);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 2, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	value->coreData = (BSMcoreData *)mpool_malloc(workspace->Pmemory, sizeof(BSMcoreData));
	memset(value->coreData, 0, sizeof(BSMcoreData));
	{ size_t saved=MqttDiag_enter("coreData", 0);
	  ret=ASN1_PER_UNAlign_Dec_BSMcoreData(workspace, value->coreData);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_BasicSafetyMessage_partII = 1;
		{ size_t saved=MqttDiag_enter("partII", 0);
		  ret=ASN1_PER_UNAlign_Dec_BasicSafetyMessage_partII(workspace, &(value->partII));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_BasicSafetyMessage_regional = 1;
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_PER_UNAlign_Dec_BasicSafetyMessage_regional(workspace, &(value->regional));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_BasicSafetyMessage == 1)
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
int ASN1_PER_UNAlign_Data_Dec_BasicSafetyMessage_partII(ASN1WorkSpace *workspace, BasicSafetyMessage_partII *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_BasicSafetyMessage_partII = { ASN1_CONST64(1), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_BasicSafetyMessage_partII_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	PartIIcontent *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_BasicSafetyMessage_partII);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (PartIIcontent *)mpool_calloc(GetMemPool(workspace), sizeof(PartIIcontent), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_PartIIcontent(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_BasicSafetyMessage_regional(ASN1WorkSpace *workspace, BasicSafetyMessage_regional *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_BasicSafetyMessage_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_BasicSafetyMessage_regional_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	RegionalExtension *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_BasicSafetyMessage_regional);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (RegionalExtension *)mpool_calloc(GetMemPool(workspace), sizeof(RegionalExtension), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_RegionalExtension(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_BrakeSystemStatus(ASN1WorkSpace *workspace, BrakeSystemStatus *value)
{
	int ret = 0;
	ASNINT32 ui_traction;
	ASNINT32 ui_abs;
	ASNINT32 ui_scs;
	ASNINT32 ui_brakeBoost;
	ASNINT32 ui_auxBrakes;
	struct Asn1ConsInfo consinfo_wheelBrakes = { ASN1_CONST64(5), ASN1_CONST64(5), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_traction = { ASN1_CONST64(0), ASN1_CONST64(3), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_abs = { ASN1_CONST64(0), ASN1_CONST64(3), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_scs = { ASN1_CONST64(0), ASN1_CONST64(3), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_brakeBoost = { ASN1_CONST64(0), ASN1_CONST64(2), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_auxBrakes = { ASN1_CONST64(0), ASN1_CONST64(3), NULL, 0, CONS, 0, 0 };

	{ size_t saved=MqttDiag_enter("wheelBrakes", 0);

	  ret=ASN1_PER_UNAlign_Dec_BITSTRING(workspace, &(value->wheelBrakes), &consinfo_wheelBrakes);

	  if(ret<0) MqttDiag_failure(workspace);

	  MqttDiag_leave(saved);

	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_traction, &consinfo_traction);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (consinfo_traction.enumextbit == 0)
	{
		switch(ui_traction)
		{
		case 0: value->traction = TractionControlStatus_unavailable; break;
		case 1: value->traction = TractionControlStatus_off; break;
		case 2: value->traction = TractionControlStatus_on; break;
		case 3: value->traction = TractionControlStatus_engaged; break;
		default: value->traction = ui_traction; break;
		}
	}
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_abs, &consinfo_abs);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (consinfo_abs.enumextbit == 0)
	{
		switch(ui_abs)
		{
		case 0: value->abs = AntiLockBrakeStatus_unavailable; break;
		case 1: value->abs = AntiLockBrakeStatus_off; break;
		case 2: value->abs = AntiLockBrakeStatus_on; break;
		case 3: value->abs = AntiLockBrakeStatus_engaged; break;
		default: value->abs = ui_abs; break;
		}
	}
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_scs, &consinfo_scs);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (consinfo_scs.enumextbit == 0)
	{
		switch(ui_scs)
		{
		case 0: value->scs = StabilityControlStatus_unavailable; break;
		case 1: value->scs = StabilityControlStatus_off; break;
		case 2: value->scs = StabilityControlStatus_on; break;
		case 3: value->scs = StabilityControlStatus_engaged; break;
		default: value->scs = ui_scs; break;
		}
	}
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_brakeBoost, &consinfo_brakeBoost);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (consinfo_brakeBoost.enumextbit == 0)
	{
		switch(ui_brakeBoost)
		{
		case 0: value->brakeBoost = BrakeBoostApplied_unavailable; break;
		case 1: value->brakeBoost = BrakeBoostApplied_off; break;
		case 2: value->brakeBoost = BrakeBoostApplied_on; break;
		default: value->brakeBoost = ui_brakeBoost; break;
		}
	}
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_auxBrakes, &consinfo_auxBrakes);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (consinfo_auxBrakes.enumextbit == 0)
	{
		switch(ui_auxBrakes)
		{
		case 0: value->auxBrakes = AuxiliaryBrakeStatus_unavailable; break;
		case 1: value->auxBrakes = AuxiliaryBrakeStatus_off; break;
		case 2: value->auxBrakes = AuxiliaryBrakeStatus_on; break;
		case 3: value->auxBrakes = AuxiliaryBrakeStatus_reserved; break;
		default: value->auxBrakes = ui_auxBrakes; break;
		}
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_Circle(ASN1WorkSpace *workspace, Circle *value)
{
	int ret = 0;
	ASNINT32 ui_units;
	struct Asn1ConsInfo consinfo_center = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_radius = { ASN1_CONST64(0), ASN1_CONST64(4095), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_units = { ASN1_CONST64(0), ASN1_CONST64(7), NULL, 0, CONS, 0, 0 };

	value->center = (Position3D *)mpool_malloc(workspace->Pmemory, sizeof(Position3D));
	memset(value->center, 0, sizeof(Position3D));
	{ size_t saved=MqttDiag_enter("center", 0);
	  ret=ASN1_PER_UNAlign_Dec_Position3D(workspace, value->center);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("radius", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->radius), &consinfo_radius);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_units, &consinfo_units);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (consinfo_units.enumextbit == 0)
	{
		switch(ui_units)
		{
		case 0: value->units = DistanceUnits_centimeter; break;
		case 1: value->units = DistanceUnits_cm2_5; break;
		case 2: value->units = DistanceUnits_decimeter; break;
		case 3: value->units = DistanceUnits_meter; break;
		case 4: value->units = DistanceUnits_kilometer; break;
		case 5: value->units = DistanceUnits_foot; break;
		case 6: value->units = DistanceUnits_yard; break;
		case 7: value->units = DistanceUnits_mile; break;
		default: value->units = ui_units; break;
		}
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_ComputedLane(ASN1WorkSpace *workspace, ComputedLane *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_referenceLaneId = { ASN1_CONST64(0), ASN1_CONST64(255), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_offsetXaxis = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_offsetYaxis = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_rotateXY = { ASN1_CONST64(0), ASN1_CONST64(28800), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_scaleXaxis = { ASN1_CONST64(-2048), ASN1_CONST64(2047), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_scaleYaxis = { ASN1_CONST64(-2048), ASN1_CONST64(2047), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };

	ASNBOOL extbit_ComputedLane;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_ComputedLane);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 4, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	value->offsetXaxis = (ComputedLane_offsetXaxis *)mpool_malloc(workspace->Pmemory, sizeof(ComputedLane_offsetXaxis));
	memset(value->offsetXaxis, 0, sizeof(ComputedLane_offsetXaxis));
	value->offsetYaxis = (ComputedLane_offsetYaxis *)mpool_malloc(workspace->Pmemory, sizeof(ComputedLane_offsetYaxis));
	memset(value->offsetYaxis, 0, sizeof(ComputedLane_offsetYaxis));
	{ size_t saved=MqttDiag_enter("referenceLaneId", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->referenceLaneId), &consinfo_referenceLaneId);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("offsetXaxis", 0);
	  ret=ASN1_PER_UNAlign_Dec_ComputedLane_offsetXaxis(workspace, value->offsetXaxis);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("offsetYaxis", 0);
	  ret=ASN1_PER_UNAlign_Dec_ComputedLane_offsetYaxis(workspace, value->offsetYaxis);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_ComputedLane_rotateXY = 1;
		{ size_t saved=MqttDiag_enter("rotateXY", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->rotateXY), &consinfo_rotateXY);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_ComputedLane_scaleXaxis = 1;
		{ size_t saved=MqttDiag_enter("scaleXaxis", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->scaleXaxis), &consinfo_scaleXaxis);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_ComputedLane_scaleYaxis = 1;
		{ size_t saved=MqttDiag_enter("scaleYaxis", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->scaleYaxis), &consinfo_scaleYaxis);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 4) == 1)
	{
		value->DEF_ComputedLane_regional = 1;
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_PER_UNAlign_Dec_ComputedLane_regional(workspace, &(value->regional));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_ComputedLane == 1)
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
int ASN1_PER_UNAlign_Data_Dec_ComputedLane_offsetXaxis(ASN1WorkSpace *workspace, ComputedLane_offsetXaxis *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_small = { ASN1_CONST64(-2047), ASN1_CONST64(2047), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_large = { ASN1_CONST64(-32767), ASN1_CONST64(32767), NULL, 0, CONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 2);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_ComputedLane_offsetXaxis_small;
			break;
		case 1: index = DEF_ComputedLane_offsetXaxis_large;
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
	{ size_t saved=MqttDiag_enter("M", 0);
	  ret=ASN1_GetM(&value->M, index);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	switch(index)
	{
	case DEF_ComputedLane_offsetXaxis_small:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->elements.small), &consinfo_small);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_ComputedLane_offsetXaxis_large:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->elements.large), &consinfo_large);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_ComputedLane_offsetYaxis(ASN1WorkSpace *workspace, ComputedLane_offsetYaxis *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_small = { ASN1_CONST64(-2047), ASN1_CONST64(2047), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_large = { ASN1_CONST64(-32767), ASN1_CONST64(32767), NULL, 0, CONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 2);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_ComputedLane_offsetYaxis_small;
			break;
		case 1: index = DEF_ComputedLane_offsetYaxis_large;
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
	{ size_t saved=MqttDiag_enter("M", 0);
	  ret=ASN1_GetM(&value->M, index);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	switch(index)
	{
	case DEF_ComputedLane_offsetYaxis_small:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->elements.small), &consinfo_small);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_ComputedLane_offsetYaxis_large:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->elements.large), &consinfo_large);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_ComputedLane_regional(ASN1WorkSpace *workspace, ComputedLane_regional *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_ComputedLane_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_ComputedLane_regional_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	RegionalExtension *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_ComputedLane_regional);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (RegionalExtension *)mpool_calloc(GetMemPool(workspace), sizeof(RegionalExtension), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_RegionalExtension(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_ConnectionManeuverAssist(ASN1WorkSpace *workspace, ConnectionManeuverAssist *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_connectionID = { ASN1_CONST64(0), ASN1_CONST64(255), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_queueLength = { ASN1_CONST64(0), ASN1_CONST64(10000), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_availableStorageLength = { ASN1_CONST64(0), ASN1_CONST64(10000), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_waitOnStop = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_pedBicycleDetect = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };

	ASNBOOL extbit_ConnectionManeuverAssist;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_ConnectionManeuverAssist);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 5, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("connectionID", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->connectionID), &consinfo_connectionID);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_ConnectionManeuverAssist_queueLength = 1;
		{ size_t saved=MqttDiag_enter("queueLength", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->queueLength), &consinfo_queueLength);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_ConnectionManeuverAssist_availableStorageLength = 1;
		{ size_t saved=MqttDiag_enter("availableStorageLength", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->availableStorageLength), &consinfo_availableStorageLength);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_ConnectionManeuverAssist_waitOnStop = 1;
		{ size_t saved=MqttDiag_enter("waitOnStop", 0);
		  ret=ASN1_PER_UNAlign_Dec_BOOLEAN(workspace, &(value->waitOnStop), &consinfo_waitOnStop);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 4) == 1)
	{
		value->DEF_ConnectionManeuverAssist_pedBicycleDetect = 1;
		{ size_t saved=MqttDiag_enter("pedBicycleDetect", 0);
		  ret=ASN1_PER_UNAlign_Dec_BOOLEAN(workspace, &(value->pedBicycleDetect), &consinfo_pedBicycleDetect);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 5) == 1)
	{
		value->DEF_ConnectionManeuverAssist_regional = 1;
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_PER_UNAlign_Dec_ConnectionManeuverAssist_regional(workspace, &(value->regional));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_ConnectionManeuverAssist == 1)
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
int ASN1_PER_UNAlign_Data_Dec_ConnectionManeuverAssist_regional(ASN1WorkSpace *workspace, ConnectionManeuverAssist_regional *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_ConnectionManeuverAssist_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_ConnectionManeuverAssist_regional_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	RegionalExtension *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_ConnectionManeuverAssist_regional);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (RegionalExtension *)mpool_calloc(GetMemPool(workspace), sizeof(RegionalExtension), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_RegionalExtension(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_DDateTime(ASN1WorkSpace *workspace, DDateTime *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_year = { ASN1_CONST64(0), ASN1_CONST64(4095), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_month = { ASN1_CONST64(0), ASN1_CONST64(12), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_day = { ASN1_CONST64(0), ASN1_CONST64(31), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_hour = { ASN1_CONST64(0), ASN1_CONST64(31), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_minute = { ASN1_CONST64(0), ASN1_CONST64(60), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_second = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_offset = { ASN1_CONST64(-840), ASN1_CONST64(840), NULL, 0, CONS, 0, 0 };

	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 7, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_DDateTime_year = 1;
		{ size_t saved=MqttDiag_enter("year", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->year), &consinfo_year);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_DDateTime_month = 1;
		{ size_t saved=MqttDiag_enter("month", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->month), &consinfo_month);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_DDateTime_day = 1;
		{ size_t saved=MqttDiag_enter("day", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->day), &consinfo_day);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 4) == 1)
	{
		value->DEF_DDateTime_hour = 1;
		{ size_t saved=MqttDiag_enter("hour", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->hour), &consinfo_hour);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 5) == 1)
	{
		value->DEF_DDateTime_minute = 1;
		{ size_t saved=MqttDiag_enter("minute", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->minute), &consinfo_minute);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 6) == 1)
	{
		value->DEF_DDateTime_second = 1;
		{ size_t saved=MqttDiag_enter("second", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->second), &consinfo_second);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 7) == 1)
	{
		value->DEF_DDateTime_offset = 1;
		{ size_t saved=MqttDiag_enter("offset", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->offset), &consinfo_offset);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_EnabledLaneList(ASN1WorkSpace *workspace, EnabledLaneList *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_EnabledLaneList = { ASN1_CONST64(1), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_EnabledLaneList_pdata = { ASN1_CONST64(0), ASN1_CONST64(255), NULL, 0, CONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	LaneID *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_EnabledLaneList);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (LaneID *)mpool_calloc(GetMemPool(workspace), sizeof(LaneID), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_LaneID(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_EventOrSvcInfo_KOR(ASN1WorkSpace *workspace, EventOrSvcInfo_KOR *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_typeEvent = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_description = { ASN1_CONST64(1), ASN1_CONST64(100), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_text = { ASN1_CONST64(1), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_subtext = { ASN1_CONST64(1), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };

	ASNBOOL extbit_EventOrSvcInfo_KOR;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_EventOrSvcInfo_KOR);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 4, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_EventOrSvcInfo_KOR_typeEvent = 1;
		{ size_t saved=MqttDiag_enter("typeEvent", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->typeEvent), &consinfo_typeEvent);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_EventOrSvcInfo_KOR_description = 1;
		{ size_t saved=MqttDiag_enter("description", 0);
		  ret=ASN1_PER_UNAlign_Dec_ITIScodesAndText(workspace, &(value->description));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_EventOrSvcInfo_KOR_text = 1;
		{ size_t saved=MqttDiag_enter("text", 0);
		  ret=ASN1_PER_UNAlign_Dec_EventOrSvcInfo_KOR_text(workspace, &(value->text));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 4) == 1)
	{
		value->DEF_EventOrSvcInfo_KOR_subtext = 1;
		{ size_t saved=MqttDiag_enter("subtext", 0);
		  ret=ASN1_PER_UNAlign_Dec_EventOrSvcInfo_KOR_subtext(workspace, &(value->subtext));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_EventOrSvcInfo_KOR == 1)
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
int ASN1_PER_UNAlign_Data_Dec_EventOrSvcInfo_KOR_subtext(ASN1WorkSpace *workspace, EventOrSvcInfo_KOR_subtext *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_EventOrSvcInfo_KOR_subtext = { ASN1_CONST64(1), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_EventOrSvcInfo_KOR_subtext_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	UTF8Str *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_EventOrSvcInfo_KOR_subtext);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (UTF8Str *)mpool_calloc(GetMemPool(workspace), sizeof(UTF8Str), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_UTF8Str(workspace, pdata, &consinfo_EventOrSvcInfo_KOR_subtext_pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_EventOrSvcInfo_KOR_text(ASN1WorkSpace *workspace, EventOrSvcInfo_KOR_text *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_EventOrSvcInfo_KOR_text = { ASN1_CONST64(1), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_EventOrSvcInfo_KOR_text_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	UTF8Str *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_EventOrSvcInfo_KOR_text);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (UTF8Str *)mpool_calloc(GetMemPool(workspace), sizeof(UTF8Str), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_UTF8Str(workspace, pdata, &consinfo_EventOrSvcInfo_KOR_text_pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_ExitService(ASN1WorkSpace *workspace, ExitService *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_ExitService = { ASN1_CONST64(1), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_ExitService_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	ExitService_element *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_ExitService);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (ExitService_element *)mpool_calloc(GetMemPool(workspace), sizeof(ExitService_element), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_ExitService_element(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_ExitService_element(ASN1WorkSpace *workspace, ExitService_element *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_item = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	value->item = (ExitService_element_item *)mpool_malloc(workspace->Pmemory, sizeof(ExitService_element_item));
	memset(value->item, 0, sizeof(ExitService_element_item));
	{ size_t saved=MqttDiag_enter("item", 0);
	  ret=ASN1_PER_UNAlign_Dec_ExitService_element_item(workspace, value->item);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_ExitService_element_item(ASN1WorkSpace *workspace, ExitService_element_item *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_itis = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_text = { ASN1_CONST64(1), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 2);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_ExitService_element_item_itis;
			break;
		case 1: index = DEF_ExitService_element_item_text;
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
	{ size_t saved=MqttDiag_enter("M", 0);
	  ret=ASN1_GetM(&value->M, index);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	switch(index)
	{
	case DEF_ExitService_element_item_itis:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->elements.itis), &consinfo_itis);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_ExitService_element_item_text:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_IA5String(workspace, &(value->elements.text), &consinfo_text);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_GenericSignage(ASN1WorkSpace *workspace, GenericSignage *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_GenericSignage = { ASN1_CONST64(1), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_GenericSignage_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	GenericSignage_element *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_GenericSignage);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (GenericSignage_element *)mpool_calloc(GetMemPool(workspace), sizeof(GenericSignage_element), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_GenericSignage_element(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_GenericSignage_element(ASN1WorkSpace *workspace, GenericSignage_element *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_item = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	value->item = (GenericSignage_element_item *)mpool_malloc(workspace->Pmemory, sizeof(GenericSignage_element_item));
	memset(value->item, 0, sizeof(GenericSignage_element_item));
	{ size_t saved=MqttDiag_enter("item", 0);
	  ret=ASN1_PER_UNAlign_Dec_GenericSignage_element_item(workspace, value->item);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_GenericSignage_element_item(ASN1WorkSpace *workspace, GenericSignage_element_item *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_itis = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_text = { ASN1_CONST64(1), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 2);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_GenericSignage_element_item_itis;
			break;
		case 1: index = DEF_GenericSignage_element_item_text;
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
	{ size_t saved=MqttDiag_enter("M", 0);
	  ret=ASN1_GetM(&value->M, index);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	switch(index)
	{
	case DEF_GenericSignage_element_item_itis:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->elements.itis), &consinfo_itis);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_GenericSignage_element_item_text:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_IA5String(workspace, &(value->elements.text), &consinfo_text);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_GeographicalPath(ASN1WorkSpace *workspace, GeographicalPath *value)
{
	int ret = 0;
	ASNINT32 ui_directionality;
	struct Asn1ConsInfo consinfo_name = { ASN1_CONST64(1), ASN1_CONST64(63), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_id = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_anchor = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_laneWidth = { ASN1_CONST64(0), ASN1_CONST64(32767), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_directionality = { ASN1_CONST64(0), ASN1_CONST64(3), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_closedPath = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_direction = { ASN1_CONST64(16), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_description = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };

	ASNBOOL extbit_GeographicalPath;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_GeographicalPath);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 9, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	value->id = (RoadSegmentReferenceID *)mpool_malloc(workspace->Pmemory, sizeof(RoadSegmentReferenceID));
	memset(value->id, 0, sizeof(RoadSegmentReferenceID));
	value->anchor = (Position3D *)mpool_malloc(workspace->Pmemory, sizeof(Position3D));
	memset(value->anchor, 0, sizeof(Position3D));
	value->description = (GeographicalPath_description *)mpool_malloc(workspace->Pmemory, sizeof(GeographicalPath_description));
	memset(value->description, 0, sizeof(GeographicalPath_description));
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_GeographicalPath_name = 1;
		{ size_t saved=MqttDiag_enter("name", 0);
		  ret=ASN1_PER_UNAlign_Dec_IA5String(workspace, &(value->name), &consinfo_name);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_GeographicalPath_id = 1;
		{ size_t saved=MqttDiag_enter("id", 0);
		  ret=ASN1_PER_UNAlign_Dec_RoadSegmentReferenceID(workspace, value->id);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_GeographicalPath_anchor = 1;
		{ size_t saved=MqttDiag_enter("anchor", 0);
		  ret=ASN1_PER_UNAlign_Dec_Position3D(workspace, value->anchor);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 4) == 1)
	{
		value->DEF_GeographicalPath_laneWidth = 1;
		{ size_t saved=MqttDiag_enter("laneWidth", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->laneWidth), &consinfo_laneWidth);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 5) == 1)
	{
		value->DEF_GeographicalPath_directionality = 1;
		{ size_t saved=MqttDiag_enter("", 0);
		  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_directionality, &consinfo_directionality);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (consinfo_directionality.enumextbit == 0)
		{
			switch(ui_directionality)
			{
			case 0: value->directionality = DirectionOfUse_unavailable; break;
			case 1: value->directionality = DirectionOfUse_forward; break;
			case 2: value->directionality = DirectionOfUse_reverse; break;
			case 3: value->directionality = DirectionOfUse_both; break;
			default: value->directionality = ui_directionality; break;
			}
		}
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 6) == 1)
	{
		value->DEF_GeographicalPath_closedPath = 1;
		{ size_t saved=MqttDiag_enter("closedPath", 0);
		  ret=ASN1_PER_UNAlign_Dec_BOOLEAN(workspace, &(value->closedPath), &consinfo_closedPath);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 7) == 1)
	{
		value->DEF_GeographicalPath_direction = 1;
		{ size_t saved=MqttDiag_enter("direction", 0);
		  ret=ASN1_PER_UNAlign_Dec_BITSTRING(workspace, &(value->direction), &consinfo_direction);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 8) == 1)
	{
		value->DEF_GeographicalPath_description = 1;
		{ size_t saved=MqttDiag_enter("description", 0);
		  ret=ASN1_PER_UNAlign_Dec_GeographicalPath_description(workspace, value->description);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 9) == 1)
	{
		value->DEF_GeographicalPath_regional = 1;
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_PER_UNAlign_Dec_GeographicalPath_regional(workspace, &(value->regional));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_GeographicalPath == 1)
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
int ASN1_PER_UNAlign_Data_Dec_GeographicalPath_KOR(ASN1WorkSpace *workspace, GeographicalPath_KOR *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_regions = { ASN1_CONST64(1), ASN1_CONST64(32), NULL, 0, CONS, 0, 0 };

	ASNBOOL extbit_GeographicalPath_KOR;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_GeographicalPath_KOR);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("regions", 0);
	  ret=ASN1_PER_UNAlign_Dec_GeographicalPath_KOR_regions(workspace, &(value->regions));
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (extbit_GeographicalPath_KOR == 1)
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
int ASN1_PER_UNAlign_Data_Dec_GeographicalPath_KOR_regions(ASN1WorkSpace *workspace, GeographicalPath_KOR_regions *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_GeographicalPath_KOR_regions = { ASN1_CONST64(1), ASN1_CONST64(32), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_GeographicalPath_KOR_regions_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	RegionDescribedByID_KOR *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_GeographicalPath_KOR_regions);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (RegionDescribedByID_KOR *)mpool_calloc(GetMemPool(workspace), sizeof(RegionDescribedByID_KOR), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_RegionDescribedByID_KOR(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_GeographicalPath_description(ASN1WorkSpace *workspace, GeographicalPath_description *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_path = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_geometry = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_oldRegion = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 1, 3);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_GeographicalPath_description_path;
			value->elements.path = (OffsetSystem *)mpool_malloc(workspace->Pmemory, sizeof(OffsetSystem));
			memset(value->elements.path, 0, sizeof(OffsetSystem));
			break;
		case 1: index = DEF_GeographicalPath_description_geometry;
			value->elements.geometry = (GeometricProjection *)mpool_malloc(workspace->Pmemory, sizeof(GeometricProjection));
			memset(value->elements.geometry, 0, sizeof(GeometricProjection));
			break;
		case 2: index = DEF_GeographicalPath_description_oldRegion;
			value->elements.oldRegion = (ValidRegion *)mpool_malloc(workspace->Pmemory, sizeof(ValidRegion));
			memset(value->elements.oldRegion, 0, sizeof(ValidRegion));
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
	{ size_t saved=MqttDiag_enter("M", 0);
	  ret=ASN1_GetM(&value->M, index);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	switch(index)
	{
	case DEF_GeographicalPath_description_path:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_OffsetSystem(workspace, value->elements.path);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_GeographicalPath_description_geometry:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_GeometricProjection(workspace, value->elements.geometry);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_GeographicalPath_description_oldRegion:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_ValidRegion(workspace, value->elements.oldRegion);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_GeographicalPath_regional(ASN1WorkSpace *workspace, GeographicalPath_regional *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_GeographicalPath_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_GeographicalPath_regional_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	RegionalExtension *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_GeographicalPath_regional);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (RegionalExtension *)mpool_calloc(GetMemPool(workspace), sizeof(RegionalExtension), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_RegionalExtension(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_GeometricProjection(ASN1WorkSpace *workspace, GeometricProjection *value)
{
	int ret = 0;
	ASNINT32 ui_extent;
	struct Asn1ConsInfo consinfo_direction = { ASN1_CONST64(16), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_extent = { ASN1_CONST64(0), ASN1_CONST64(15), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_laneWidth = { ASN1_CONST64(0), ASN1_CONST64(32767), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_circle = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };

	ASNBOOL extbit_GeometricProjection;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_GeometricProjection);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 3, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	value->circle = (Circle *)mpool_malloc(workspace->Pmemory, sizeof(Circle));
	memset(value->circle, 0, sizeof(Circle));
	{ size_t saved=MqttDiag_enter("direction", 0);
	  ret=ASN1_PER_UNAlign_Dec_BITSTRING(workspace, &(value->direction), &consinfo_direction);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_GeometricProjection_extent = 1;
		{ size_t saved=MqttDiag_enter("", 0);
		  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_extent, &consinfo_extent);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (consinfo_extent.enumextbit == 0)
		{
			switch(ui_extent)
			{
			case 0: value->extent = Extent_useInstantlyOnly; break;
			case 1: value->extent = Extent_useFor3meters; break;
			case 2: value->extent = Extent_useFor10meters; break;
			case 3: value->extent = Extent_useFor50meters; break;
			case 4: value->extent = Extent_useFor100meters; break;
			case 5: value->extent = Extent_useFor500meters; break;
			case 6: value->extent = Extent_useFor1000meters; break;
			case 7: value->extent = Extent_useFor5000meters; break;
			case 8: value->extent = Extent_useFor10000meters; break;
			case 9: value->extent = Extent_useFor50000meters; break;
			case 10: value->extent = Extent_useFor100000meters; break;
			case 11: value->extent = Extent_useFor500000meters; break;
			case 12: value->extent = Extent_useFor1000000meters; break;
			case 13: value->extent = Extent_useFor5000000meters; break;
			case 14: value->extent = Extent_useFor10000000meters; break;
			case 15: value->extent = Extent_forever; break;
			default: value->extent = ui_extent; break;
			}
		}
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_GeometricProjection_laneWidth = 1;
		{ size_t saved=MqttDiag_enter("laneWidth", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->laneWidth), &consinfo_laneWidth);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	{ size_t saved=MqttDiag_enter("circle", 0);
	  ret=ASN1_PER_UNAlign_Dec_Circle(workspace, value->circle);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_GeometricProjection_regional = 1;
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_PER_UNAlign_Dec_GeometricProjection_regional(workspace, &(value->regional));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_GeometricProjection == 1)
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
int ASN1_PER_UNAlign_Data_Dec_GeometricProjection_regional(ASN1WorkSpace *workspace, GeometricProjection_regional *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_GeometricProjection_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_GeometricProjection_regional_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	RegionalExtension *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_GeometricProjection_regional);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (RegionalExtension *)mpool_calloc(GetMemPool(workspace), sizeof(RegionalExtension), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_RegionalExtension(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_ITIScodesAndText(ASN1WorkSpace *workspace, ITIScodesAndText *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_ITIScodesAndText = { ASN1_CONST64(1), ASN1_CONST64(100), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_ITIScodesAndText_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	ITIScodesAndText_element *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_ITIScodesAndText);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (ITIScodesAndText_element *)mpool_calloc(GetMemPool(workspace), sizeof(ITIScodesAndText_element), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_ITIScodesAndText_element(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_ITIScodesAndText_element(ASN1WorkSpace *workspace, ITIScodesAndText_element *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_item = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	value->item = (ITIScodesAndText_element_item *)mpool_malloc(workspace->Pmemory, sizeof(ITIScodesAndText_element_item));
	memset(value->item, 0, sizeof(ITIScodesAndText_element_item));
	{ size_t saved=MqttDiag_enter("item", 0);
	  ret=ASN1_PER_UNAlign_Dec_ITIScodesAndText_element_item(workspace, value->item);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_ITIScodesAndText_element_item(ASN1WorkSpace *workspace, ITIScodesAndText_element_item *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_itis = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_text = { ASN1_CONST64(1), ASN1_CONST64(500), NULL, 0, CONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 2);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_ITIScodesAndText_element_item_itis;
			break;
		case 1: index = DEF_ITIScodesAndText_element_item_text;
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
	{ size_t saved=MqttDiag_enter("M", 0);
	  ret=ASN1_GetM(&value->M, index);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	switch(index)
	{
	case DEF_ITIScodesAndText_element_item_itis:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->elements.itis), &consinfo_itis);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_ITIScodesAndText_element_item_text:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_IA5String(workspace, &(value->elements.text), &consinfo_text);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_IntersectionReferenceID(ASN1WorkSpace *workspace, IntersectionReferenceID *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_region = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_id = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };

	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 1, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_IntersectionReferenceID_region = 1;
		{ size_t saved=MqttDiag_enter("region", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->region), &consinfo_region);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	{ size_t saved=MqttDiag_enter("id", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->id), &consinfo_id);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_IntersectionState(ASN1WorkSpace *workspace, IntersectionState *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_name = { ASN1_CONST64(1), ASN1_CONST64(63), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_id = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_revision = { ASN1_CONST64(0), ASN1_CONST64(127), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_status = { ASN1_CONST64(16), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_moy = { ASN1_CONST64(0), ASN1_CONST64(527040), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_timeStamp = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_enabledLanes = { ASN1_CONST64(1), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_states = { ASN1_CONST64(1), ASN1_CONST64(255), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_maneuverAssistList = { ASN1_CONST64(1), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };

	ASNBOOL extbit_IntersectionState;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_IntersectionState);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 6, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	value->id = (IntersectionReferenceID *)mpool_malloc(workspace->Pmemory, sizeof(IntersectionReferenceID));
	memset(value->id, 0, sizeof(IntersectionReferenceID));
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_IntersectionState_name = 1;
		{ size_t saved=MqttDiag_enter("name", 0);
		  ret=ASN1_PER_UNAlign_Dec_IA5String(workspace, &(value->name), &consinfo_name);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	{ size_t saved=MqttDiag_enter("id", 0);
	  ret=ASN1_PER_UNAlign_Dec_IntersectionReferenceID(workspace, value->id);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("revision", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->revision), &consinfo_revision);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("status", 0);
	  ret=ASN1_PER_UNAlign_Dec_BITSTRING(workspace, &(value->status), &consinfo_status);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_IntersectionState_moy = 1;
		{ size_t saved=MqttDiag_enter("moy", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->moy), &consinfo_moy);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_IntersectionState_timeStamp = 1;
		{ size_t saved=MqttDiag_enter("timeStamp", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->timeStamp), &consinfo_timeStamp);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 4) == 1)
	{
		value->DEF_IntersectionState_enabledLanes = 1;
		{ size_t saved=MqttDiag_enter("enabledLanes", 0);
		  ret=ASN1_PER_UNAlign_Dec_EnabledLaneList(workspace, &(value->enabledLanes));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	{ size_t saved=MqttDiag_enter("states", 0);
	  ret=ASN1_PER_UNAlign_Dec_MovementList(workspace, &(value->states));
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 5) == 1)
	{
		value->DEF_IntersectionState_maneuverAssistList = 1;
		{ size_t saved=MqttDiag_enter("maneuverAssistList", 0);
		  ret=ASN1_PER_UNAlign_Dec_ManeuverAssistList(workspace, &(value->maneuverAssistList));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 6) == 1)
	{
		value->DEF_IntersectionState_regional = 1;
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_PER_UNAlign_Dec_IntersectionState_regional(workspace, &(value->regional));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_IntersectionState == 1)
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
int ASN1_PER_UNAlign_Data_Dec_IntersectionStateList(ASN1WorkSpace *workspace, IntersectionStateList *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_IntersectionStateList = { ASN1_CONST64(1), ASN1_CONST64(32), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_IntersectionStateList_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	IntersectionState *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_IntersectionStateList);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (IntersectionState *)mpool_calloc(GetMemPool(workspace), sizeof(IntersectionState), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_IntersectionState(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_IntersectionState_regional(ASN1WorkSpace *workspace, IntersectionState_regional *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_IntersectionState_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_IntersectionState_regional_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	RegionalExtension *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_IntersectionState_regional);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (RegionalExtension *)mpool_calloc(GetMemPool(workspace), sizeof(RegionalExtension), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_RegionalExtension(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_LaneDataAttribute(ASN1WorkSpace *workspace, LaneDataAttribute *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_pathEndPointAngle = { ASN1_CONST64(-150), ASN1_CONST64(150), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_laneCrownPointCenter = { ASN1_CONST64(-128), ASN1_CONST64(127), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_laneCrownPointLeft = { ASN1_CONST64(-128), ASN1_CONST64(127), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_laneCrownPointRight = { ASN1_CONST64(-128), ASN1_CONST64(127), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_laneAngle = { ASN1_CONST64(-180), ASN1_CONST64(180), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_speedLimits = { ASN1_CONST64(1), ASN1_CONST64(9), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 1, 7);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_LaneDataAttribute_pathEndPointAngle;
			break;
		case 1: index = DEF_LaneDataAttribute_laneCrownPointCenter;
			break;
		case 2: index = DEF_LaneDataAttribute_laneCrownPointLeft;
			break;
		case 3: index = DEF_LaneDataAttribute_laneCrownPointRight;
			break;
		case 4: index = DEF_LaneDataAttribute_laneAngle;
			break;
		case 5: index = DEF_LaneDataAttribute_speedLimits;
			break;
		case 6: index = DEF_LaneDataAttribute_regional;
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
	{ size_t saved=MqttDiag_enter("M", 0);
	  ret=ASN1_GetM(&value->M, index);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	switch(index)
	{
	case DEF_LaneDataAttribute_pathEndPointAngle:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->elements.pathEndPointAngle), &consinfo_pathEndPointAngle);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_LaneDataAttribute_laneCrownPointCenter:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->elements.laneCrownPointCenter), &consinfo_laneCrownPointCenter);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_LaneDataAttribute_laneCrownPointLeft:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->elements.laneCrownPointLeft), &consinfo_laneCrownPointLeft);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_LaneDataAttribute_laneCrownPointRight:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->elements.laneCrownPointRight), &consinfo_laneCrownPointRight);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_LaneDataAttribute_laneAngle:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->elements.laneAngle), &consinfo_laneAngle);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_LaneDataAttribute_speedLimits:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_SpeedLimitList(workspace, &(value->elements.speedLimits));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_LaneDataAttribute_regional:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_LaneDataAttribute_regional(workspace, &(value->elements.regional));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_LaneDataAttributeList(ASN1WorkSpace *workspace, LaneDataAttributeList *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_LaneDataAttributeList = { ASN1_CONST64(1), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_LaneDataAttributeList_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	LaneDataAttribute *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_LaneDataAttributeList);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (LaneDataAttribute *)mpool_calloc(GetMemPool(workspace), sizeof(LaneDataAttribute), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_LaneDataAttribute(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_LaneDataAttribute_regional(ASN1WorkSpace *workspace, LaneDataAttribute_regional *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_LaneDataAttribute_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_LaneDataAttribute_regional_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	RegionalExtension *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_LaneDataAttribute_regional);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (RegionalExtension *)mpool_calloc(GetMemPool(workspace), sizeof(RegionalExtension), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_RegionalExtension(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_LaneID(ASN1WorkSpace *workspace, LaneID *value)
{
	struct Asn1ConsInfo consinfo_LaneID = { ASN1_CONST64(0), ASN1_CONST64(255), NULL, 0, CONS, 0, 0 };
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, value, &consinfo_LaneID);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_ManeuverAssistList(ASN1WorkSpace *workspace, ManeuverAssistList *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_ManeuverAssistList = { ASN1_CONST64(1), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_ManeuverAssistList_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	ConnectionManeuverAssist *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_ManeuverAssistList);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (ConnectionManeuverAssist *)mpool_calloc(GetMemPool(workspace), sizeof(ConnectionManeuverAssist), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_ConnectionManeuverAssist(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_MessageFrame(ASN1WorkSpace *workspace, MessageFrame *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_messageId = { ASN1_CONST64(0), ASN1_CONST64(32767), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_value = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNBOOL extbit_MessageFrame;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_MessageFrame);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("messageId", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->messageId), &consinfo_messageId);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("value", 0);
	  ret=ASN1_PER_UNAlign_Dec_OpenType(workspace, &(value->value));
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (extbit_MessageFrame == 1)
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
int ASN1_PER_UNAlign_Data_Dec_MovementEvent(ASN1WorkSpace *workspace, MovementEvent *value)
{
	int ret = 0;
	ASNINT32 ui_eventState;
	struct Asn1ConsInfo consinfo_eventState = { ASN1_CONST64(0), ASN1_CONST64(9), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_timing = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_speeds = { ASN1_CONST64(1), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };

	ASNBOOL extbit_MovementEvent;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_MovementEvent);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 3, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	value->timing = (TimeChangeDetails *)mpool_malloc(workspace->Pmemory, sizeof(TimeChangeDetails));
	memset(value->timing, 0, sizeof(TimeChangeDetails));
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_eventState, &consinfo_eventState);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (consinfo_eventState.enumextbit == 0)
	{
		switch(ui_eventState)
		{
		case 0: value->eventState = MovementPhaseState_unavailable; break;
		case 1: value->eventState = MovementPhaseState_dark; break;
		case 2: value->eventState = MovementPhaseState_stop_Then_Proceed; break;
		case 3: value->eventState = MovementPhaseState_stop_And_Remain; break;
		case 4: value->eventState = MovementPhaseState_pre_Movement; break;
		case 5: value->eventState = MovementPhaseState_permissive_Movement_Allowed; break;
		case 6: value->eventState = MovementPhaseState_protected_Movement_Allowed; break;
		case 7: value->eventState = MovementPhaseState_permissive_clearance; break;
		case 8: value->eventState = MovementPhaseState_protected_clearance; break;
		case 9: value->eventState = MovementPhaseState_caution_Conflicting_Traffic; break;
		default: value->eventState = ui_eventState; break;
		}
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_MovementEvent_timing = 1;
		{ size_t saved=MqttDiag_enter("timing", 0);
		  ret=ASN1_PER_UNAlign_Dec_TimeChangeDetails(workspace, value->timing);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_MovementEvent_speeds = 1;
		{ size_t saved=MqttDiag_enter("speeds", 0);
		  ret=ASN1_PER_UNAlign_Dec_AdvisorySpeedList(workspace, &(value->speeds));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_MovementEvent_regional = 1;
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_PER_UNAlign_Dec_MovementEvent_regional(workspace, &(value->regional));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_MovementEvent == 1)
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
int ASN1_PER_UNAlign_Data_Dec_MovementEventList(ASN1WorkSpace *workspace, MovementEventList *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_MovementEventList = { ASN1_CONST64(1), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_MovementEventList_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	MovementEvent *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_MovementEventList);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (MovementEvent *)mpool_calloc(GetMemPool(workspace), sizeof(MovementEvent), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_MovementEvent(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_MovementEvent_regional(ASN1WorkSpace *workspace, MovementEvent_regional *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_MovementEvent_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_MovementEvent_regional_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	RegionalExtension *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_MovementEvent_regional);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (RegionalExtension *)mpool_calloc(GetMemPool(workspace), sizeof(RegionalExtension), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_RegionalExtension(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_MovementList(ASN1WorkSpace *workspace, MovementList *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_MovementList = { ASN1_CONST64(1), ASN1_CONST64(255), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_MovementList_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	MovementState *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_MovementList);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (MovementState *)mpool_calloc(GetMemPool(workspace), sizeof(MovementState), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_MovementState(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_MovementState(ASN1WorkSpace *workspace, MovementState *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_movementName = { ASN1_CONST64(1), ASN1_CONST64(63), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_signalGroup = { ASN1_CONST64(0), ASN1_CONST64(255), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_state_time_speed = { ASN1_CONST64(1), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_maneuverAssistList = { ASN1_CONST64(1), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };

	ASNBOOL extbit_MovementState;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_MovementState);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 3, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_MovementState_movementName = 1;
		{ size_t saved=MqttDiag_enter("movementName", 0);
		  ret=ASN1_PER_UNAlign_Dec_IA5String(workspace, &(value->movementName), &consinfo_movementName);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	{ size_t saved=MqttDiag_enter("signalGroup", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->signalGroup), &consinfo_signalGroup);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("state_time_speed", 0);
	  ret=ASN1_PER_UNAlign_Dec_MovementEventList(workspace, &(value->state_time_speed));
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_MovementState_maneuverAssistList = 1;
		{ size_t saved=MqttDiag_enter("maneuverAssistList", 0);
		  ret=ASN1_PER_UNAlign_Dec_ManeuverAssistList(workspace, &(value->maneuverAssistList));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_MovementState_regional = 1;
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_PER_UNAlign_Dec_MovementState_regional(workspace, &(value->regional));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_MovementState == 1)
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
int ASN1_PER_UNAlign_Data_Dec_MovementState_regional(ASN1WorkSpace *workspace, MovementState_regional *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_MovementState_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_MovementState_regional_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	RegionalExtension *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_MovementState_regional);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (RegionalExtension *)mpool_calloc(GetMemPool(workspace), sizeof(RegionalExtension), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_RegionalExtension(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_NodeAttributeLL(ASN1WorkSpace *workspace, NodeAttributeLL *value)
{
	struct Asn1ConsInfo consinfo_NodeAttributeLL = { ASN1_CONST64(0), ASN1_CONST64(11), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_NodeAttributeLL;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_NodeAttributeLL, &consinfo_NodeAttributeLL);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (consinfo_NodeAttributeLL.enumextbit == 0)
	{
		switch(ui_NodeAttributeLL)
		{
		case 0: *value = NodeAttributeLL_reserved; break;
		case 1: *value = NodeAttributeLL_stopLine; break;
		case 2: *value = NodeAttributeLL_roundedCapStyleA; break;
		case 3: *value = NodeAttributeLL_roundedCapStyleB; break;
		case 4: *value = NodeAttributeLL_mergePoint; break;
		case 5: *value = NodeAttributeLL_divergePoint; break;
		case 6: *value = NodeAttributeLL_downstreamStopLine; break;
		case 7: *value = NodeAttributeLL_downstreamStartNode; break;
		case 8: *value = NodeAttributeLL_closedToTraffic; break;
		case 9: *value = NodeAttributeLL_safeIsland; break;
		case 10: *value = NodeAttributeLL_curbPresentAtStepOff; break;
		case 11: *value = NodeAttributeLL_hydrantPresent; break;
		default: break;
		}
	}
	else
	{
		switch(ui_NodeAttributeLL)
		{
		default: *value = ui_NodeAttributeLL; break;
		}
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_NodeAttributeLLList(ASN1WorkSpace *workspace, NodeAttributeLLList *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_NodeAttributeLLList = { ASN1_CONST64(1), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_NodeAttributeLLList_pdata = { ASN1_CONST64(0), ASN1_CONST64(11), NULL, 1, CONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	NodeAttributeLL *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_NodeAttributeLLList);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (NodeAttributeLL *)mpool_calloc(GetMemPool(workspace), sizeof(NodeAttributeLL), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_NodeAttributeLL(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_NodeAttributeSetLL(ASN1WorkSpace *workspace, NodeAttributeSetLL *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_localNode = { ASN1_CONST64(1), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_disabled = { ASN1_CONST64(1), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_enabled = { ASN1_CONST64(1), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_data = { ASN1_CONST64(1), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_dWidth = { ASN1_CONST64(-512), ASN1_CONST64(511), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_dElevation = { ASN1_CONST64(-512), ASN1_CONST64(511), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };

	ASNBOOL extbit_NodeAttributeSetLL;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_NodeAttributeSetLL);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 7, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_NodeAttributeSetLL_localNode = 1;
		{ size_t saved=MqttDiag_enter("localNode", 0);
		  ret=ASN1_PER_UNAlign_Dec_NodeAttributeLLList(workspace, &(value->localNode));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_NodeAttributeSetLL_disabled = 1;
		{ size_t saved=MqttDiag_enter("disabled", 0);
		  ret=ASN1_PER_UNAlign_Dec_SegmentAttributeLLList(workspace, &(value->disabled));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_NodeAttributeSetLL_enabled = 1;
		{ size_t saved=MqttDiag_enter("enabled", 0);
		  ret=ASN1_PER_UNAlign_Dec_SegmentAttributeLLList(workspace, &(value->enabled));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 4) == 1)
	{
		value->DEF_NodeAttributeSetLL_data = 1;
		{ size_t saved=MqttDiag_enter("data", 0);
		  ret=ASN1_PER_UNAlign_Dec_LaneDataAttributeList(workspace, &(value->data));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 5) == 1)
	{
		value->DEF_NodeAttributeSetLL_dWidth = 1;
		{ size_t saved=MqttDiag_enter("dWidth", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->dWidth), &consinfo_dWidth);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 6) == 1)
	{
		value->DEF_NodeAttributeSetLL_dElevation = 1;
		{ size_t saved=MqttDiag_enter("dElevation", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->dElevation), &consinfo_dElevation);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 7) == 1)
	{
		value->DEF_NodeAttributeSetLL_regional = 1;
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_PER_UNAlign_Dec_NodeAttributeSetLL_regional(workspace, &(value->regional));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_NodeAttributeSetLL == 1)
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
int ASN1_PER_UNAlign_Data_Dec_NodeAttributeSetLL_regional(ASN1WorkSpace *workspace, NodeAttributeSetLL_regional *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_NodeAttributeSetLL_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_NodeAttributeSetLL_regional_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	RegionalExtension *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_NodeAttributeSetLL_regional);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (RegionalExtension *)mpool_calloc(GetMemPool(workspace), sizeof(RegionalExtension), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_RegionalExtension(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_NodeAttributeSetXY(ASN1WorkSpace *workspace, NodeAttributeSetXY *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_localNode = { ASN1_CONST64(1), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_disabled = { ASN1_CONST64(1), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_enabled = { ASN1_CONST64(1), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_data = { ASN1_CONST64(1), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_dWidth = { ASN1_CONST64(-512), ASN1_CONST64(511), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_dElevation = { ASN1_CONST64(-512), ASN1_CONST64(511), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };

	ASNBOOL extbit_NodeAttributeSetXY;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_NodeAttributeSetXY);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 7, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_NodeAttributeSetXY_localNode = 1;
		{ size_t saved=MqttDiag_enter("localNode", 0);
		  ret=ASN1_PER_UNAlign_Dec_NodeAttributeXYList(workspace, &(value->localNode));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_NodeAttributeSetXY_disabled = 1;
		{ size_t saved=MqttDiag_enter("disabled", 0);
		  ret=ASN1_PER_UNAlign_Dec_SegmentAttributeXYList(workspace, &(value->disabled));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_NodeAttributeSetXY_enabled = 1;
		{ size_t saved=MqttDiag_enter("enabled", 0);
		  ret=ASN1_PER_UNAlign_Dec_SegmentAttributeXYList(workspace, &(value->enabled));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 4) == 1)
	{
		value->DEF_NodeAttributeSetXY_data = 1;
		{ size_t saved=MqttDiag_enter("data", 0);
		  ret=ASN1_PER_UNAlign_Dec_LaneDataAttributeList(workspace, &(value->data));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 5) == 1)
	{
		value->DEF_NodeAttributeSetXY_dWidth = 1;
		{ size_t saved=MqttDiag_enter("dWidth", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->dWidth), &consinfo_dWidth);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 6) == 1)
	{
		value->DEF_NodeAttributeSetXY_dElevation = 1;
		{ size_t saved=MqttDiag_enter("dElevation", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->dElevation), &consinfo_dElevation);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 7) == 1)
	{
		value->DEF_NodeAttributeSetXY_regional = 1;
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_PER_UNAlign_Dec_NodeAttributeSetXY_regional(workspace, &(value->regional));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_NodeAttributeSetXY == 1)
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
int ASN1_PER_UNAlign_Data_Dec_NodeAttributeSetXY_regional(ASN1WorkSpace *workspace, NodeAttributeSetXY_regional *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_NodeAttributeSetXY_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_NodeAttributeSetXY_regional_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	RegionalExtension *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_NodeAttributeSetXY_regional);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (RegionalExtension *)mpool_calloc(GetMemPool(workspace), sizeof(RegionalExtension), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_RegionalExtension(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_NodeAttributeXY(ASN1WorkSpace *workspace, NodeAttributeXY *value)
{
	struct Asn1ConsInfo consinfo_NodeAttributeXY = { ASN1_CONST64(0), ASN1_CONST64(11), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_NodeAttributeXY;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_NodeAttributeXY, &consinfo_NodeAttributeXY);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (consinfo_NodeAttributeXY.enumextbit == 0)
	{
		switch(ui_NodeAttributeXY)
		{
		case 0: *value = NodeAttributeXY_reserved; break;
		case 1: *value = NodeAttributeXY_stopLine; break;
		case 2: *value = NodeAttributeXY_roundedCapStyleA; break;
		case 3: *value = NodeAttributeXY_roundedCapStyleB; break;
		case 4: *value = NodeAttributeXY_mergePoint; break;
		case 5: *value = NodeAttributeXY_divergePoint; break;
		case 6: *value = NodeAttributeXY_downstreamStopLine; break;
		case 7: *value = NodeAttributeXY_downstreamStartNode; break;
		case 8: *value = NodeAttributeXY_closedToTraffic; break;
		case 9: *value = NodeAttributeXY_safeIsland; break;
		case 10: *value = NodeAttributeXY_curbPresentAtStepOff; break;
		case 11: *value = NodeAttributeXY_hydrantPresent; break;
		default: break;
		}
	}
	else
	{
		switch(ui_NodeAttributeXY)
		{
		default: *value = ui_NodeAttributeXY; break;
		}
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_NodeAttributeXYList(ASN1WorkSpace *workspace, NodeAttributeXYList *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_NodeAttributeXYList = { ASN1_CONST64(1), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_NodeAttributeXYList_pdata = { ASN1_CONST64(0), ASN1_CONST64(11), NULL, 1, CONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	NodeAttributeXY *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_NodeAttributeXYList);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (NodeAttributeXY *)mpool_calloc(GetMemPool(workspace), sizeof(NodeAttributeXY), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_NodeAttributeXY(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_NodeLL(ASN1WorkSpace *workspace, NodeLL *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_delta = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_attributes = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNBOOL extbit_NodeLL;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_NodeLL);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 1, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	value->delta = (NodeOffsetPointLL *)mpool_malloc(workspace->Pmemory, sizeof(NodeOffsetPointLL));
	memset(value->delta, 0, sizeof(NodeOffsetPointLL));
	value->attributes = (NodeAttributeSetLL *)mpool_malloc(workspace->Pmemory, sizeof(NodeAttributeSetLL));
	memset(value->attributes, 0, sizeof(NodeAttributeSetLL));
	{ size_t saved=MqttDiag_enter("delta", 0);
	  ret=ASN1_PER_UNAlign_Dec_NodeOffsetPointLL(workspace, value->delta);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_NodeLL_attributes = 1;
		{ size_t saved=MqttDiag_enter("attributes", 0);
		  ret=ASN1_PER_UNAlign_Dec_NodeAttributeSetLL(workspace, value->attributes);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_NodeLL == 1)
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
int ASN1_PER_UNAlign_Data_Dec_NodeListLL(ASN1WorkSpace *workspace, NodeListLL *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_nodes = { ASN1_CONST64(2), ASN1_CONST64(63), NULL, 0, CONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 1, 1);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_NodeListLL_nodes;
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
	{ size_t saved=MqttDiag_enter("M", 0);
	  ret=ASN1_GetM(&value->M, index);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	switch(index)
	{
	case DEF_NodeListLL_nodes:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_NodeSetLL(workspace, &(value->elements.nodes));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_NodeListXY(ASN1WorkSpace *workspace, NodeListXY *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_nodes = { ASN1_CONST64(2), ASN1_CONST64(63), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_computed = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 1, 2);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_NodeListXY_nodes;
			break;
		case 1: index = DEF_NodeListXY_computed;
			value->elements.computed = (ComputedLane *)mpool_malloc(workspace->Pmemory, sizeof(ComputedLane));
			memset(value->elements.computed, 0, sizeof(ComputedLane));
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
	{ size_t saved=MqttDiag_enter("M", 0);
	  ret=ASN1_GetM(&value->M, index);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	switch(index)
	{
	case DEF_NodeListXY_nodes:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_NodeSetXY(workspace, &(value->elements.nodes));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_NodeListXY_computed:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_ComputedLane(workspace, value->elements.computed);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_NodeOffsetPointLL(ASN1WorkSpace *workspace, NodeOffsetPointLL *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_node_LL1 = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_node_LL2 = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_node_LL3 = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_node_LL4 = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_node_LL5 = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_node_LL6 = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_node_LatLon = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_regional = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 8);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_NodeOffsetPointLL_node_LL1;
			value->elements.node_LL1 = (Node_LL_24B *)mpool_malloc(workspace->Pmemory, sizeof(Node_LL_24B));
			memset(value->elements.node_LL1, 0, sizeof(Node_LL_24B));
			break;
		case 1: index = DEF_NodeOffsetPointLL_node_LL2;
			value->elements.node_LL2 = (Node_LL_28B *)mpool_malloc(workspace->Pmemory, sizeof(Node_LL_28B));
			memset(value->elements.node_LL2, 0, sizeof(Node_LL_28B));
			break;
		case 2: index = DEF_NodeOffsetPointLL_node_LL3;
			value->elements.node_LL3 = (Node_LL_32B *)mpool_malloc(workspace->Pmemory, sizeof(Node_LL_32B));
			memset(value->elements.node_LL3, 0, sizeof(Node_LL_32B));
			break;
		case 3: index = DEF_NodeOffsetPointLL_node_LL4;
			value->elements.node_LL4 = (Node_LL_36B *)mpool_malloc(workspace->Pmemory, sizeof(Node_LL_36B));
			memset(value->elements.node_LL4, 0, sizeof(Node_LL_36B));
			break;
		case 4: index = DEF_NodeOffsetPointLL_node_LL5;
			value->elements.node_LL5 = (Node_LL_44B *)mpool_malloc(workspace->Pmemory, sizeof(Node_LL_44B));
			memset(value->elements.node_LL5, 0, sizeof(Node_LL_44B));
			break;
		case 5: index = DEF_NodeOffsetPointLL_node_LL6;
			value->elements.node_LL6 = (Node_LL_48B *)mpool_malloc(workspace->Pmemory, sizeof(Node_LL_48B));
			memset(value->elements.node_LL6, 0, sizeof(Node_LL_48B));
			break;
		case 6: index = DEF_NodeOffsetPointLL_node_LatLon;
			value->elements.node_LatLon = (Node_LLmD_64b *)mpool_malloc(workspace->Pmemory, sizeof(Node_LLmD_64b));
			memset(value->elements.node_LatLon, 0, sizeof(Node_LLmD_64b));
			break;
		case 7: index = DEF_NodeOffsetPointLL_regional;
			value->elements.regional = (RegionalExtension *)mpool_malloc(workspace->Pmemory, sizeof(RegionalExtension));
			memset(value->elements.regional, 0, sizeof(RegionalExtension));
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
	{ size_t saved=MqttDiag_enter("M", 0);
	  ret=ASN1_GetM(&value->M, index);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	switch(index)
	{
	case DEF_NodeOffsetPointLL_node_LL1:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_Node_LL_24B(workspace, value->elements.node_LL1);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_NodeOffsetPointLL_node_LL2:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_Node_LL_28B(workspace, value->elements.node_LL2);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_NodeOffsetPointLL_node_LL3:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_Node_LL_32B(workspace, value->elements.node_LL3);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_NodeOffsetPointLL_node_LL4:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_Node_LL_36B(workspace, value->elements.node_LL4);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_NodeOffsetPointLL_node_LL5:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_Node_LL_44B(workspace, value->elements.node_LL5);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_NodeOffsetPointLL_node_LL6:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_Node_LL_48B(workspace, value->elements.node_LL6);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_NodeOffsetPointLL_node_LatLon:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_Node_LLmD_64b(workspace, value->elements.node_LatLon);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_NodeOffsetPointLL_regional:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_RegionalExtension(workspace, value->elements.regional);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_NodeOffsetPointXY(ASN1WorkSpace *workspace, NodeOffsetPointXY *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_node_XY1 = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_node_XY2 = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_node_XY3 = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_node_XY4 = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_node_XY5 = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_node_XY6 = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_node_LatLon = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_regional = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 8);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_NodeOffsetPointXY_node_XY1;
			value->elements.node_XY1 = (Node_XY_20b *)mpool_malloc(workspace->Pmemory, sizeof(Node_XY_20b));
			memset(value->elements.node_XY1, 0, sizeof(Node_XY_20b));
			break;
		case 1: index = DEF_NodeOffsetPointXY_node_XY2;
			value->elements.node_XY2 = (Node_XY_22b *)mpool_malloc(workspace->Pmemory, sizeof(Node_XY_22b));
			memset(value->elements.node_XY2, 0, sizeof(Node_XY_22b));
			break;
		case 2: index = DEF_NodeOffsetPointXY_node_XY3;
			value->elements.node_XY3 = (Node_XY_24b *)mpool_malloc(workspace->Pmemory, sizeof(Node_XY_24b));
			memset(value->elements.node_XY3, 0, sizeof(Node_XY_24b));
			break;
		case 3: index = DEF_NodeOffsetPointXY_node_XY4;
			value->elements.node_XY4 = (Node_XY_26b *)mpool_malloc(workspace->Pmemory, sizeof(Node_XY_26b));
			memset(value->elements.node_XY4, 0, sizeof(Node_XY_26b));
			break;
		case 4: index = DEF_NodeOffsetPointXY_node_XY5;
			value->elements.node_XY5 = (Node_XY_28b *)mpool_malloc(workspace->Pmemory, sizeof(Node_XY_28b));
			memset(value->elements.node_XY5, 0, sizeof(Node_XY_28b));
			break;
		case 5: index = DEF_NodeOffsetPointXY_node_XY6;
			value->elements.node_XY6 = (Node_XY_32b *)mpool_malloc(workspace->Pmemory, sizeof(Node_XY_32b));
			memset(value->elements.node_XY6, 0, sizeof(Node_XY_32b));
			break;
		case 6: index = DEF_NodeOffsetPointXY_node_LatLon;
			value->elements.node_LatLon = (Node_LLmD_64b *)mpool_malloc(workspace->Pmemory, sizeof(Node_LLmD_64b));
			memset(value->elements.node_LatLon, 0, sizeof(Node_LLmD_64b));
			break;
		case 7: index = DEF_NodeOffsetPointXY_regional;
			value->elements.regional = (RegionalExtension *)mpool_malloc(workspace->Pmemory, sizeof(RegionalExtension));
			memset(value->elements.regional, 0, sizeof(RegionalExtension));
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
	{ size_t saved=MqttDiag_enter("M", 0);
	  ret=ASN1_GetM(&value->M, index);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	switch(index)
	{
	case DEF_NodeOffsetPointXY_node_XY1:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_Node_XY_20b(workspace, value->elements.node_XY1);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_NodeOffsetPointXY_node_XY2:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_Node_XY_22b(workspace, value->elements.node_XY2);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_NodeOffsetPointXY_node_XY3:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_Node_XY_24b(workspace, value->elements.node_XY3);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_NodeOffsetPointXY_node_XY4:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_Node_XY_26b(workspace, value->elements.node_XY4);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_NodeOffsetPointXY_node_XY5:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_Node_XY_28b(workspace, value->elements.node_XY5);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_NodeOffsetPointXY_node_XY6:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_Node_XY_32b(workspace, value->elements.node_XY6);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_NodeOffsetPointXY_node_LatLon:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_Node_LLmD_64b(workspace, value->elements.node_LatLon);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_NodeOffsetPointXY_regional:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_RegionalExtension(workspace, value->elements.regional);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_NodeSetLL(ASN1WorkSpace *workspace, NodeSetLL *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_NodeSetLL = { ASN1_CONST64(2), ASN1_CONST64(63), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_NodeSetLL_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	NodeLL *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_NodeSetLL);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (NodeLL *)mpool_calloc(GetMemPool(workspace), sizeof(NodeLL), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_NodeLL(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_NodeSetXY(ASN1WorkSpace *workspace, NodeSetXY *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_NodeSetXY = { ASN1_CONST64(2), ASN1_CONST64(63), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_NodeSetXY_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	NodeXY *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_NodeSetXY);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (NodeXY *)mpool_calloc(GetMemPool(workspace), sizeof(NodeXY), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_NodeXY(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_NodeXY(ASN1WorkSpace *workspace, NodeXY *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_delta = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_attributes = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNBOOL extbit_NodeXY;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_NodeXY);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 1, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	value->delta = (NodeOffsetPointXY *)mpool_malloc(workspace->Pmemory, sizeof(NodeOffsetPointXY));
	memset(value->delta, 0, sizeof(NodeOffsetPointXY));
	value->attributes = (NodeAttributeSetXY *)mpool_malloc(workspace->Pmemory, sizeof(NodeAttributeSetXY));
	memset(value->attributes, 0, sizeof(NodeAttributeSetXY));
	{ size_t saved=MqttDiag_enter("delta", 0);
	  ret=ASN1_PER_UNAlign_Dec_NodeOffsetPointXY(workspace, value->delta);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_NodeXY_attributes = 1;
		{ size_t saved=MqttDiag_enter("attributes", 0);
		  ret=ASN1_PER_UNAlign_Dec_NodeAttributeSetXY(workspace, value->attributes);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_NodeXY == 1)
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
int ASN1_PER_UNAlign_Data_Dec_Node_LL_24B(ASN1WorkSpace *workspace, Node_LL_24B *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_lon = { ASN1_CONST64(-2048), ASN1_CONST64(2047), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_lat = { ASN1_CONST64(-2048), ASN1_CONST64(2047), NULL, 0, CONS, 0, 0 };

	{ size_t saved=MqttDiag_enter("lon", 0);

	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->lon), &consinfo_lon);

	  if(ret<0) MqttDiag_failure(workspace);

	  MqttDiag_leave(saved);

	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("lat", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->lat), &consinfo_lat);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_Node_LL_28B(ASN1WorkSpace *workspace, Node_LL_28B *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_lon = { ASN1_CONST64(-8192), ASN1_CONST64(8191), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_lat = { ASN1_CONST64(-8192), ASN1_CONST64(8191), NULL, 0, CONS, 0, 0 };

	{ size_t saved=MqttDiag_enter("lon", 0);

	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->lon), &consinfo_lon);

	  if(ret<0) MqttDiag_failure(workspace);

	  MqttDiag_leave(saved);

	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("lat", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->lat), &consinfo_lat);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_Node_LL_32B(ASN1WorkSpace *workspace, Node_LL_32B *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_lon = { ASN1_CONST64(-32768), ASN1_CONST64(32767), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_lat = { ASN1_CONST64(-32768), ASN1_CONST64(32767), NULL, 0, CONS, 0, 0 };

	{ size_t saved=MqttDiag_enter("lon", 0);

	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->lon), &consinfo_lon);

	  if(ret<0) MqttDiag_failure(workspace);

	  MqttDiag_leave(saved);

	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("lat", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->lat), &consinfo_lat);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_Node_LL_36B(ASN1WorkSpace *workspace, Node_LL_36B *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_lon = { ASN1_CONST64(-131072), ASN1_CONST64(131071), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_lat = { ASN1_CONST64(-131072), ASN1_CONST64(131071), NULL, 0, CONS, 0, 0 };

	{ size_t saved=MqttDiag_enter("lon", 0);

	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->lon), &consinfo_lon);

	  if(ret<0) MqttDiag_failure(workspace);

	  MqttDiag_leave(saved);

	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("lat", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->lat), &consinfo_lat);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_Node_LL_44B(ASN1WorkSpace *workspace, Node_LL_44B *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_lon = { ASN1_CONST64(-2097152), ASN1_CONST64(2097151), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_lat = { ASN1_CONST64(-2097152), ASN1_CONST64(2097151), NULL, 0, CONS, 0, 0 };

	{ size_t saved=MqttDiag_enter("lon", 0);

	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->lon), &consinfo_lon);

	  if(ret<0) MqttDiag_failure(workspace);

	  MqttDiag_leave(saved);

	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("lat", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->lat), &consinfo_lat);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_Node_LL_48B(ASN1WorkSpace *workspace, Node_LL_48B *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_lon = { ASN1_CONST64(-8388608), ASN1_CONST64(8388607), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_lat = { ASN1_CONST64(-8388608), ASN1_CONST64(8388607), NULL, 0, CONS, 0, 0 };

	{ size_t saved=MqttDiag_enter("lon", 0);

	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->lon), &consinfo_lon);

	  if(ret<0) MqttDiag_failure(workspace);

	  MqttDiag_leave(saved);

	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("lat", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->lat), &consinfo_lat);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_Node_LLmD_64b(ASN1WorkSpace *workspace, Node_LLmD_64b *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_lon = { ASN1_CONST64(-1799999999), ASN1_CONST64(1800000001), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_lat = { ASN1_CONST64(-900000000), ASN1_CONST64(900000001), NULL, 0, CONS, 0, 0 };

	{ size_t saved=MqttDiag_enter("lon", 0);

	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->lon), &consinfo_lon);

	  if(ret<0) MqttDiag_failure(workspace);

	  MqttDiag_leave(saved);

	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("lat", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->lat), &consinfo_lat);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_Node_XY_20b(ASN1WorkSpace *workspace, Node_XY_20b *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_x = { ASN1_CONST64(-512), ASN1_CONST64(511), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_y = { ASN1_CONST64(-512), ASN1_CONST64(511), NULL, 0, CONS, 0, 0 };

	{ size_t saved=MqttDiag_enter("x", 0);

	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->x), &consinfo_x);

	  if(ret<0) MqttDiag_failure(workspace);

	  MqttDiag_leave(saved);

	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("y", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->y), &consinfo_y);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_Node_XY_22b(ASN1WorkSpace *workspace, Node_XY_22b *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_x = { ASN1_CONST64(-1024), ASN1_CONST64(1023), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_y = { ASN1_CONST64(-1024), ASN1_CONST64(1023), NULL, 0, CONS, 0, 0 };

	{ size_t saved=MqttDiag_enter("x", 0);

	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->x), &consinfo_x);

	  if(ret<0) MqttDiag_failure(workspace);

	  MqttDiag_leave(saved);

	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("y", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->y), &consinfo_y);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_Node_XY_24b(ASN1WorkSpace *workspace, Node_XY_24b *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_x = { ASN1_CONST64(-2048), ASN1_CONST64(2047), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_y = { ASN1_CONST64(-2048), ASN1_CONST64(2047), NULL, 0, CONS, 0, 0 };

	{ size_t saved=MqttDiag_enter("x", 0);

	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->x), &consinfo_x);

	  if(ret<0) MqttDiag_failure(workspace);

	  MqttDiag_leave(saved);

	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("y", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->y), &consinfo_y);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_Node_XY_26b(ASN1WorkSpace *workspace, Node_XY_26b *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_x = { ASN1_CONST64(-4096), ASN1_CONST64(4095), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_y = { ASN1_CONST64(-4096), ASN1_CONST64(4095), NULL, 0, CONS, 0, 0 };

	{ size_t saved=MqttDiag_enter("x", 0);

	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->x), &consinfo_x);

	  if(ret<0) MqttDiag_failure(workspace);

	  MqttDiag_leave(saved);

	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("y", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->y), &consinfo_y);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_Node_XY_28b(ASN1WorkSpace *workspace, Node_XY_28b *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_x = { ASN1_CONST64(-8192), ASN1_CONST64(8191), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_y = { ASN1_CONST64(-8192), ASN1_CONST64(8191), NULL, 0, CONS, 0, 0 };

	{ size_t saved=MqttDiag_enter("x", 0);

	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->x), &consinfo_x);

	  if(ret<0) MqttDiag_failure(workspace);

	  MqttDiag_leave(saved);

	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("y", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->y), &consinfo_y);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_Node_XY_32b(ASN1WorkSpace *workspace, Node_XY_32b *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_x = { ASN1_CONST64(-32768), ASN1_CONST64(32767), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_y = { ASN1_CONST64(-32768), ASN1_CONST64(32767), NULL, 0, CONS, 0, 0 };

	{ size_t saved=MqttDiag_enter("x", 0);

	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->x), &consinfo_x);

	  if(ret<0) MqttDiag_failure(workspace);

	  MqttDiag_leave(saved);

	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("y", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->y), &consinfo_y);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_OffsetSystem(ASN1WorkSpace *workspace, OffsetSystem *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_scale = { ASN1_CONST64(0), ASN1_CONST64(15), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_offset = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 1, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	value->offset = (OffsetSystem_offset *)mpool_malloc(workspace->Pmemory, sizeof(OffsetSystem_offset));
	memset(value->offset, 0, sizeof(OffsetSystem_offset));
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_OffsetSystem_scale = 1;
		{ size_t saved=MqttDiag_enter("scale", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->scale), &consinfo_scale);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	{ size_t saved=MqttDiag_enter("offset", 0);
	  ret=ASN1_PER_UNAlign_Dec_OffsetSystem_offset(workspace, value->offset);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_OffsetSystem_offset(ASN1WorkSpace *workspace, OffsetSystem_offset *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_xy = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_ll = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 2);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_OffsetSystem_offset_xy;
			value->elements.xy = (NodeListXY *)mpool_malloc(workspace->Pmemory, sizeof(NodeListXY));
			memset(value->elements.xy, 0, sizeof(NodeListXY));
			break;
		case 1: index = DEF_OffsetSystem_offset_ll;
			value->elements.ll = (NodeListLL *)mpool_malloc(workspace->Pmemory, sizeof(NodeListLL));
			memset(value->elements.ll, 0, sizeof(NodeListLL));
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
	{ size_t saved=MqttDiag_enter("M", 0);
	  ret=ASN1_GetM(&value->M, index);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	switch(index)
	{
	case DEF_OffsetSystem_offset_xy:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_NodeListXY(workspace, value->elements.xy);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_OffsetSystem_offset_ll:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_NodeListLL(workspace, value->elements.ll);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_ParkingCapacity_KOR(ASN1WorkSpace *workspace, ParkingCapacity_KOR *value)
{
	int ret = 0;
	ASNINT32 ui_type;
	struct Asn1ConsInfo consinfo_type = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_numberOfParkingSpace = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_maxParkingSpace = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNBOOL extbit_ParkingCapacity_KOR;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_ParkingCapacity_KOR);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 1, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_type, &consinfo_type);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (consinfo_type.enumextbit == 0)
	{
		switch(ui_type)
		{
		case 0: value->type = ParkingType_KOR_normal; break;
		case 1: value->type = ParkingType_KOR_disable; break;
		case 2: value->type = ParkingType_KOR_big; break;
		case 3: value->type = ParkingType_KOR_compact; break;
		case 4: value->type = ParkingType_KOR_emergency; break;
		case 5: value->type = ParkingType_KOR_women; break;
		case 6: value->type = ParkingType_KOR_etc; break;
		default: break;
		}
	}
	else
	{
		switch(ui_type)
		{
		default: value->type = ui_type; break;
		}
	}
	{ size_t saved=MqttDiag_enter("numberOfParkingSpace", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->numberOfParkingSpace), &consinfo_numberOfParkingSpace);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_ParkingCapacity_KOR_maxParkingSpace = 1;
		{ size_t saved=MqttDiag_enter("maxParkingSpace", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->maxParkingSpace), &consinfo_maxParkingSpace);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_ParkingCapacity_KOR == 1)
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
int ASN1_PER_UNAlign_Data_Dec_ParkingZoneInformation_KOR(ASN1WorkSpace *workspace, ParkingZoneInformation_KOR *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_name = { ASN1_CONST64(1), ASN1_CONST64(128), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_id = { ASN1_CONST64(1), ASN1_CONST64(128), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_capacity = { ASN1_CONST64(0), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };

	ASNBOOL extbit_ParkingZoneInformation_KOR;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_ParkingZoneInformation_KOR);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 2, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_ParkingZoneInformation_KOR_name = 1;
		{ size_t saved=MqttDiag_enter("name", 0);
		  ret=ASN1_PER_UNAlign_Dec_UTF8Str(workspace, &(value->name), &consinfo_name);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_ParkingZoneInformation_KOR_id = 1;
		{ size_t saved=MqttDiag_enter("id", 0);
		  ret=ASN1_PER_UNAlign_Dec_UTF8Str(workspace, &(value->id), &consinfo_id);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	{ size_t saved=MqttDiag_enter("capacity", 0);
	  ret=ASN1_PER_UNAlign_Dec_ParkingZoneInformation_KOR_capacity(workspace, &(value->capacity));
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (extbit_ParkingZoneInformation_KOR == 1)
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
int ASN1_PER_UNAlign_Data_Dec_ParkingZoneInformation_KOR_capacity(ASN1WorkSpace *workspace, ParkingZoneInformation_KOR_capacity *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_ParkingZoneInformation_KOR_capacity = { ASN1_CONST64(0), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_ParkingZoneInformation_KOR_capacity_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	ParkingCapacity_KOR *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_ParkingZoneInformation_KOR_capacity);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (ParkingCapacity_KOR *)mpool_calloc(GetMemPool(workspace), sizeof(ParkingCapacity_KOR), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_ParkingCapacity_KOR(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_PartIIcontent(ASN1WorkSpace *workspace, PartIIcontent *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_partII_Id = { ASN1_CONST64(0), ASN1_CONST64(63), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_partII_Value = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	{ size_t saved=MqttDiag_enter("partII_Id", 0);

	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->partII_Id), &consinfo_partII_Id);

	  if(ret<0) MqttDiag_failure(workspace);

	  MqttDiag_leave(saved);

	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("partII_Value", 0);
	  ret=ASN1_PER_UNAlign_Dec_OpenType(workspace, &(value->partII_Value));
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_Position3D(ASN1WorkSpace *workspace, Position3D *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_lat = { ASN1_CONST64(-900000000), ASN1_CONST64(900000001), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_lon = { ASN1_CONST64(-1799999999), ASN1_CONST64(1800000001), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_elevation = { ASN1_CONST64(-4096), ASN1_CONST64(61439), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };

	ASNBOOL extbit_Position3D;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_Position3D);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 2, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("lat", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->lat), &consinfo_lat);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("lon", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->lon), &consinfo_lon);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_Position3D_elevation = 1;
		{ size_t saved=MqttDiag_enter("elevation", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->elevation), &consinfo_elevation);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_Position3D_regional = 1;
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_PER_UNAlign_Dec_Position3D_regional(workspace, &(value->regional));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_Position3D == 1)
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
int ASN1_PER_UNAlign_Data_Dec_Position3D_regional(ASN1WorkSpace *workspace, Position3D_regional *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_Position3D_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_Position3D_regional_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	RegionalExtension *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_Position3D_regional);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (RegionalExtension *)mpool_calloc(GetMemPool(workspace), sizeof(RegionalExtension), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_RegionalExtension(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_PositionalAccuracy(ASN1WorkSpace *workspace, PositionalAccuracy *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_semiMajor = { ASN1_CONST64(0), ASN1_CONST64(255), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_semiMinor = { ASN1_CONST64(0), ASN1_CONST64(255), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_orientation = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };

	{ size_t saved=MqttDiag_enter("semiMajor", 0);

	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->semiMajor), &consinfo_semiMajor);

	  if(ret<0) MqttDiag_failure(workspace);

	  MqttDiag_leave(saved);

	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("semiMinor", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->semiMinor), &consinfo_semiMinor);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("orientation", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->orientation), &consinfo_orientation);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_RegionDescribedByID_KOR(ASN1WorkSpace *workspace, RegionDescribedByID_KOR *value)
{
	int ret = 0;
	ASNINT32 ui_detectLane;
	struct Asn1ConsInfo consinfo_laneID = { ASN1_CONST64(0), ASN1_CONST64(255), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_segmentID = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_linkID = { ASN1_CONST64(1), ASN1_CONST64(128), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_detectLane = { ASN1_CONST64(0), ASN1_CONST64(30), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_areaID = { ASN1_CONST64(1), ASN1_CONST64(128), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_intersections = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 1, 6);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_RegionDescribedByID_KOR_laneID;
			break;
		case 1: index = DEF_RegionDescribedByID_KOR_segmentID;
			break;
		case 2: index = DEF_RegionDescribedByID_KOR_linkID;
			break;
		case 3: index = DEF_RegionDescribedByID_KOR_detectLane;
			break;
		case 4: index = DEF_RegionDescribedByID_KOR_areaID;
			break;
		case 5: index = DEF_RegionDescribedByID_KOR_intersections;
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
	{ size_t saved=MqttDiag_enter("M", 0);
	  ret=ASN1_GetM(&value->M, index);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	switch(index)
	{
	case DEF_RegionDescribedByID_KOR_laneID:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->elements.laneID), &consinfo_laneID);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_RegionDescribedByID_KOR_segmentID:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->elements.segmentID), &consinfo_segmentID);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_RegionDescribedByID_KOR_linkID:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_UTF8Str(workspace, &(value->elements.linkID), &consinfo_linkID);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_RegionDescribedByID_KOR_detectLane:
		{ size_t saved=MqttDiag_enter("", 0);
		  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_detectLane, &consinfo_detectLane);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (consinfo_detectLane.enumextbit == 0)
		{
			switch(ui_detectLane)
			{
			case 0: value->elements.detectLane = DectLane_KOR_unavailable; break;
			case 1: value->elements.detectLane = DectLane_KOR_busOnlyLane; break;
			case 2: value->elements.detectLane = DectLane_KOR_ctrBusLane; break;
			case 3: value->elements.detectLane = DectLane_KOR_rdSdBusLane; break;
			case 4: value->elements.detectLane = DectLane_KOR_mergingLane; break;
			case 5: value->elements.detectLane = DectLane_KOR_accelerationLane; break;
			case 6: value->elements.detectLane = DectLane_KOR_decelrationLane; break;
			case 7: value->elements.detectLane = DectLane_KOR_rampLane; break;
			case 8: value->elements.detectLane = DectLane_KOR_shoulderLane; break;
			case 9: value->elements.detectLane = DectLane_KOR_carLane; break;
			case 10: value->elements.detectLane = DectLane_KOR_car_1stLane; break;
			case 11: value->elements.detectLane = DectLane_KOR_car_2ndLane; break;
			case 12: value->elements.detectLane = DectLane_KOR_car_3rdLane; break;
			case 13: value->elements.detectLane = DectLane_KOR_car_4thLane; break;
			case 14: value->elements.detectLane = DectLane_KOR_car_5thLane; break;
			case 15: value->elements.detectLane = DectLane_KOR_car_6thLane; break;
			case 16: value->elements.detectLane = DectLane_KOR_car_7thLane; break;
			case 17: value->elements.detectLane = DectLane_KOR_car_8thLane; break;
			case 18: value->elements.detectLane = DectLane_KOR_car_9thLane; break;
			case 19: value->elements.detectLane = DectLane_KOR_car_10thLane; break;
			case 20: value->elements.detectLane = DectLane_KOR_car_11thLane; break;
			case 21: value->elements.detectLane = DectLane_KOR_car_12thLane; break;
			case 22: value->elements.detectLane = DectLane_KOR_car_13thLane; break;
			case 23: value->elements.detectLane = DectLane_KOR_car_14thLane; break;
			case 24: value->elements.detectLane = DectLane_KOR_car_15thLane; break;
			case 25: value->elements.detectLane = DectLane_KOR_car_16thLane; break;
			case 26: value->elements.detectLane = DectLane_KOR_car_17thLane; break;
			case 27: value->elements.detectLane = DectLane_KOR_car_18thLane; break;
			case 28: value->elements.detectLane = DectLane_KOR_car_19thLane; break;
			case 29: value->elements.detectLane = DectLane_KOR_car_20thLane; break;
			case 30: value->elements.detectLane = DectLane_KOR_etcLane; break;
			default: break;
			}
		}
		else
		{
			switch(ui_detectLane)
			{
			default: value->elements.detectLane = ui_detectLane; break;
			}
		}
		if (ret != 0) return -1;
		break;
	case DEF_RegionDescribedByID_KOR_areaID:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_UTF8Str(workspace, &(value->elements.areaID), &consinfo_areaID);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_RegionDescribedByID_KOR_intersections:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->elements.intersections), &consinfo_intersections);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_RegionList(ASN1WorkSpace *workspace, RegionList *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_RegionList = { ASN1_CONST64(1), ASN1_CONST64(64), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_RegionList_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	RegionOffsets *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_RegionList);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (RegionOffsets *)mpool_calloc(GetMemPool(workspace), sizeof(RegionOffsets), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_RegionOffsets(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_RegionOffsets(ASN1WorkSpace *workspace, RegionOffsets *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_xOffset = { ASN1_CONST64(-32768), ASN1_CONST64(32767), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_yOffset = { ASN1_CONST64(-32768), ASN1_CONST64(32767), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_zOffset = { ASN1_CONST64(-32768), ASN1_CONST64(32767), NULL, 0, CONS, 0, 0 };

	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 1, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("xOffset", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->xOffset), &consinfo_xOffset);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("yOffset", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->yOffset), &consinfo_yOffset);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_RegionOffsets_zOffset = 1;
		{ size_t saved=MqttDiag_enter("zOffset", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->zOffset), &consinfo_zOffset);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_RegionPointSet(ASN1WorkSpace *workspace, RegionPointSet *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_anchor = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_scale = { ASN1_CONST64(0), ASN1_CONST64(15), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_nodeList = { ASN1_CONST64(1), ASN1_CONST64(64), NULL, 0, CONS, 0, 0 };

	ASNBOOL extbit_RegionPointSet;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_RegionPointSet);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 2, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	value->anchor = (Position3D *)mpool_malloc(workspace->Pmemory, sizeof(Position3D));
	memset(value->anchor, 0, sizeof(Position3D));
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_RegionPointSet_anchor = 1;
		{ size_t saved=MqttDiag_enter("anchor", 0);
		  ret=ASN1_PER_UNAlign_Dec_Position3D(workspace, value->anchor);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_RegionPointSet_scale = 1;
		{ size_t saved=MqttDiag_enter("scale", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->scale), &consinfo_scale);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	{ size_t saved=MqttDiag_enter("nodeList", 0);
	  ret=ASN1_PER_UNAlign_Dec_RegionList(workspace, &(value->nodeList));
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (extbit_RegionPointSet == 1)
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
int ASN1_PER_UNAlign_Data_Dec_RegionalExtension(ASN1WorkSpace *workspace, RegionalExtension *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_regionId = { ASN1_CONST64(0), ASN1_CONST64(255), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_regExtValue = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	{ size_t saved=MqttDiag_enter("regionId", 0);

	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->regionId), &consinfo_regionId);

	  if(ret<0) MqttDiag_failure(workspace);

	  MqttDiag_leave(saved);

	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("regExtValue", 0);
	  ret=ASN1_PER_UNAlign_Dec_OpenType(workspace, &(value->regExtValue));
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_RegulatorySpeedLimit(ASN1WorkSpace *workspace, RegulatorySpeedLimit *value)
{
	int ret = 0;
	ASNINT32 ui_type;
	struct Asn1ConsInfo consinfo_type = { ASN1_CONST64(0), ASN1_CONST64(12), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_speed = { ASN1_CONST64(0), ASN1_CONST64(8191), NULL, 0, CONS, 0, 0 };

	{ size_t saved=MqttDiag_enter("", 0);

	  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_type, &consinfo_type);

	  if(ret<0) MqttDiag_failure(workspace);

	  MqttDiag_leave(saved);

	  if(ret<0) return ret; }
	if (consinfo_type.enumextbit == 0)
	{
		switch(ui_type)
		{
		case 0: value->type = SpeedLimitType_unknown; break;
		case 1: value->type = SpeedLimitType_maxSpeedInSchoolZone; break;
		case 2: value->type = SpeedLimitType_maxSpeedInSchoolZoneWhenChildrenArePresent; break;
		case 3: value->type = SpeedLimitType_maxSpeedInConstructionZone; break;
		case 4: value->type = SpeedLimitType_vehicleMinSpeed; break;
		case 5: value->type = SpeedLimitType_vehicleMaxSpeed; break;
		case 6: value->type = SpeedLimitType_vehicleNightMaxSpeed; break;
		case 7: value->type = SpeedLimitType_truckMinSpeed; break;
		case 8: value->type = SpeedLimitType_truckMaxSpeed; break;
		case 9: value->type = SpeedLimitType_truckNightMaxSpeed; break;
		case 10: value->type = SpeedLimitType_vehiclesWithTrailersMinSpeed; break;
		case 11: value->type = SpeedLimitType_vehiclesWithTrailersMaxSpeed; break;
		case 12: value->type = SpeedLimitType_vehiclesWithTrailersNightMaxSpeed; break;
		default: break;
		}
	}
	else
	{
		switch(ui_type)
		{
		default: value->type = ui_type; break;
		}
	}
	{ size_t saved=MqttDiag_enter("speed", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->speed), &consinfo_speed);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_RidingNotification_KOR(ASN1WorkSpace *workspace, RidingNotification_KOR *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_stopID = { ASN1_CONST64(1), ASN1_CONST64(128), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_disabled = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_boarding = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNBOOL extbit_RidingNotification_KOR;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_RidingNotification_KOR);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 3, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_RidingNotification_KOR_stopID = 1;
		{ size_t saved=MqttDiag_enter("stopID", 0);
		  ret=ASN1_PER_UNAlign_Dec_UTF8Str(workspace, &(value->stopID), &consinfo_stopID);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_RidingNotification_KOR_disabled = 1;
		{ size_t saved=MqttDiag_enter("disabled", 0);
		  ret=ASN1_PER_UNAlign_Dec_BOOLEAN(workspace, &(value->disabled), &consinfo_disabled);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_RidingNotification_KOR_boarding = 1;
		{ size_t saved=MqttDiag_enter("boarding", 0);
		  ret=ASN1_PER_UNAlign_Dec_BOOLEAN(workspace, &(value->boarding), &consinfo_boarding);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_RidingNotification_KOR == 1)
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
int ASN1_PER_UNAlign_Data_Dec_RoadSegmentReferenceID(ASN1WorkSpace *workspace, RoadSegmentReferenceID *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_region = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_id = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };

	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 1, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_RoadSegmentReferenceID_region = 1;
		{ size_t saved=MqttDiag_enter("region", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->region), &consinfo_region);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	{ size_t saved=MqttDiag_enter("id", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->id), &consinfo_id);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_RoadSignID(ASN1WorkSpace *workspace, RoadSignID *value)
{
	int ret = 0;
	ASNINT32 ui_mutcdCode;
	struct Asn1ConsInfo consinfo_position = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_viewAngle = { ASN1_CONST64(16), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_mutcdCode = { ASN1_CONST64(0), ASN1_CONST64(6), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_crc = { ASN1_CONST64(2), ASN1_CONST64(2), NULL, 0, CONS, 0, 0 };

	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 2, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	value->position = (Position3D *)mpool_malloc(workspace->Pmemory, sizeof(Position3D));
	memset(value->position, 0, sizeof(Position3D));
	{ size_t saved=MqttDiag_enter("position", 0);
	  ret=ASN1_PER_UNAlign_Dec_Position3D(workspace, value->position);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("viewAngle", 0);
	  ret=ASN1_PER_UNAlign_Dec_BITSTRING(workspace, &(value->viewAngle), &consinfo_viewAngle);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_RoadSignID_mutcdCode = 1;
		{ size_t saved=MqttDiag_enter("", 0);
		  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_mutcdCode, &consinfo_mutcdCode);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (consinfo_mutcdCode.enumextbit == 0)
		{
			switch(ui_mutcdCode)
			{
			case 0: value->mutcdCode = MUTCDCode_none; break;
			case 1: value->mutcdCode = MUTCDCode_regulatory; break;
			case 2: value->mutcdCode = MUTCDCode_warning; break;
			case 3: value->mutcdCode = MUTCDCode_maintenance; break;
			case 4: value->mutcdCode = MUTCDCode_motoristService; break;
			case 5: value->mutcdCode = MUTCDCode_guide; break;
			case 6: value->mutcdCode = MUTCDCode_rec; break;
			default: break;
			}
		}
		else
		{
			switch(ui_mutcdCode)
			{
			default: value->mutcdCode = ui_mutcdCode; break;
			}
		}
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_RoadSignID_crc = 1;
		{ size_t saved=MqttDiag_enter("crc", 0);
		  ret=ASN1_PER_UNAlign_Dec_OCTETSTRING(workspace, &(value->crc), &consinfo_crc);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_SPAT(ASN1WorkSpace *workspace, SPAT *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_timeStamp = { ASN1_CONST64(0), ASN1_CONST64(527040), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_name = { ASN1_CONST64(1), ASN1_CONST64(63), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_intersections = { ASN1_CONST64(1), ASN1_CONST64(32), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };

	ASNBOOL extbit_SPAT;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_SPAT);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 3, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_SPAT_timeStamp = 1;
		{ size_t saved=MqttDiag_enter("timeStamp", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->timeStamp), &consinfo_timeStamp);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_SPAT_name = 1;
		{ size_t saved=MqttDiag_enter("name", 0);
		  ret=ASN1_PER_UNAlign_Dec_IA5String(workspace, &(value->name), &consinfo_name);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	{ size_t saved=MqttDiag_enter("intersections", 0);
	  ret=ASN1_PER_UNAlign_Dec_IntersectionStateList(workspace, &(value->intersections));
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_SPAT_regional = 1;
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_PER_UNAlign_Dec_SPAT_regional(workspace, &(value->regional));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_SPAT == 1)
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
int ASN1_PER_UNAlign_Data_Dec_SPAT_regional(ASN1WorkSpace *workspace, SPAT_regional *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_SPAT_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_SPAT_regional_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	RegionalExtension *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_SPAT_regional);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (RegionalExtension *)mpool_calloc(GetMemPool(workspace), sizeof(RegionalExtension), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_RegionalExtension(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_SegmentAttributeLL(ASN1WorkSpace *workspace, SegmentAttributeLL *value)
{
	struct Asn1ConsInfo consinfo_SegmentAttributeLL = { ASN1_CONST64(0), ASN1_CONST64(37), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_SegmentAttributeLL;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_SegmentAttributeLL, &consinfo_SegmentAttributeLL);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (consinfo_SegmentAttributeLL.enumextbit == 0)
	{
		switch(ui_SegmentAttributeLL)
		{
		case 0: *value = SegmentAttributeLL_reserved; break;
		case 1: *value = SegmentAttributeLL_doNotBlock; break;
		case 2: *value = SegmentAttributeLL_whiteLine; break;
		case 3: *value = SegmentAttributeLL_mergingLaneLeft; break;
		case 4: *value = SegmentAttributeLL_mergingLaneRight; break;
		case 5: *value = SegmentAttributeLL_curbOnLeft; break;
		case 6: *value = SegmentAttributeLL_curbOnRight; break;
		case 7: *value = SegmentAttributeLL_loadingzoneOnLeft; break;
		case 8: *value = SegmentAttributeLL_loadingzoneOnRight; break;
		case 9: *value = SegmentAttributeLL_turnOutPointOnLeft; break;
		case 10: *value = SegmentAttributeLL_turnOutPointOnRight; break;
		case 11: *value = SegmentAttributeLL_adjacentParkingOnLeft; break;
		case 12: *value = SegmentAttributeLL_adjacentParkingOnRight; break;
		case 13: *value = SegmentAttributeLL_adjacentBikeLaneOnLeft; break;
		case 14: *value = SegmentAttributeLL_adjacentBikeLaneOnRight; break;
		case 15: *value = SegmentAttributeLL_sharedBikeLane; break;
		case 16: *value = SegmentAttributeLL_bikeBoxInFront; break;
		case 17: *value = SegmentAttributeLL_transitStopOnLeft; break;
		case 18: *value = SegmentAttributeLL_transitStopOnRight; break;
		case 19: *value = SegmentAttributeLL_transitStopInLane; break;
		case 20: *value = SegmentAttributeLL_sharedWithTrackedVehicle; break;
		case 21: *value = SegmentAttributeLL_safeIsland; break;
		case 22: *value = SegmentAttributeLL_lowCurbsPresent; break;
		case 23: *value = SegmentAttributeLL_rumbleStripPresent; break;
		case 24: *value = SegmentAttributeLL_audibleSignalingPresent; break;
		case 25: *value = SegmentAttributeLL_adaptiveTimingPresent; break;
		case 26: *value = SegmentAttributeLL_rfSignalRequestPresent; break;
		case 27: *value = SegmentAttributeLL_partialCurbIntrusion; break;
		case 28: *value = SegmentAttributeLL_taperToLeft; break;
		case 29: *value = SegmentAttributeLL_taperToRight; break;
		case 30: *value = SegmentAttributeLL_taperToCenterLine; break;
		case 31: *value = SegmentAttributeLL_parallelParking; break;
		case 32: *value = SegmentAttributeLL_headInParking; break;
		case 33: *value = SegmentAttributeLL_freeParking; break;
		case 34: *value = SegmentAttributeLL_timeRestrictionsOnParking; break;
		case 35: *value = SegmentAttributeLL_costToPark; break;
		case 36: *value = SegmentAttributeLL_midBlockCurbPresent; break;
		case 37: *value = SegmentAttributeLL_unEvenPavementPresent; break;
		default: break;
		}
	}
	else
	{
		switch(ui_SegmentAttributeLL)
		{
		default: *value = ui_SegmentAttributeLL; break;
		}
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_SegmentAttributeLLList(ASN1WorkSpace *workspace, SegmentAttributeLLList *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_SegmentAttributeLLList = { ASN1_CONST64(1), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_SegmentAttributeLLList_pdata = { ASN1_CONST64(0), ASN1_CONST64(37), NULL, 1, CONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	SegmentAttributeLL *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_SegmentAttributeLLList);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (SegmentAttributeLL *)mpool_calloc(GetMemPool(workspace), sizeof(SegmentAttributeLL), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_SegmentAttributeLL(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_SegmentAttributeXY(ASN1WorkSpace *workspace, SegmentAttributeXY *value)
{
	struct Asn1ConsInfo consinfo_SegmentAttributeXY = { ASN1_CONST64(0), ASN1_CONST64(37), NULL, 1, CONS, 0, 0 };
	int ret = 0;
	ASNINT32 ui_SegmentAttributeXY;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_SegmentAttributeXY, &consinfo_SegmentAttributeXY);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (consinfo_SegmentAttributeXY.enumextbit == 0)
	{
		switch(ui_SegmentAttributeXY)
		{
		case 0: *value = SegmentAttributeXY_reserved; break;
		case 1: *value = SegmentAttributeXY_doNotBlock; break;
		case 2: *value = SegmentAttributeXY_whiteLine; break;
		case 3: *value = SegmentAttributeXY_mergingLaneLeft; break;
		case 4: *value = SegmentAttributeXY_mergingLaneRight; break;
		case 5: *value = SegmentAttributeXY_curbOnLeft; break;
		case 6: *value = SegmentAttributeXY_curbOnRight; break;
		case 7: *value = SegmentAttributeXY_loadingzoneOnLeft; break;
		case 8: *value = SegmentAttributeXY_loadingzoneOnRight; break;
		case 9: *value = SegmentAttributeXY_turnOutPointOnLeft; break;
		case 10: *value = SegmentAttributeXY_turnOutPointOnRight; break;
		case 11: *value = SegmentAttributeXY_adjacentParkingOnLeft; break;
		case 12: *value = SegmentAttributeXY_adjacentParkingOnRight; break;
		case 13: *value = SegmentAttributeXY_adjacentBikeLaneOnLeft; break;
		case 14: *value = SegmentAttributeXY_adjacentBikeLaneOnRight; break;
		case 15: *value = SegmentAttributeXY_sharedBikeLane; break;
		case 16: *value = SegmentAttributeXY_bikeBoxInFront; break;
		case 17: *value = SegmentAttributeXY_transitStopOnLeft; break;
		case 18: *value = SegmentAttributeXY_transitStopOnRight; break;
		case 19: *value = SegmentAttributeXY_transitStopInLane; break;
		case 20: *value = SegmentAttributeXY_sharedWithTrackedVehicle; break;
		case 21: *value = SegmentAttributeXY_safeIsland; break;
		case 22: *value = SegmentAttributeXY_lowCurbsPresent; break;
		case 23: *value = SegmentAttributeXY_rumbleStripPresent; break;
		case 24: *value = SegmentAttributeXY_audibleSignalingPresent; break;
		case 25: *value = SegmentAttributeXY_adaptiveTimingPresent; break;
		case 26: *value = SegmentAttributeXY_rfSignalRequestPresent; break;
		case 27: *value = SegmentAttributeXY_partialCurbIntrusion; break;
		case 28: *value = SegmentAttributeXY_taperToLeft; break;
		case 29: *value = SegmentAttributeXY_taperToRight; break;
		case 30: *value = SegmentAttributeXY_taperToCenterLine; break;
		case 31: *value = SegmentAttributeXY_parallelParking; break;
		case 32: *value = SegmentAttributeXY_headInParking; break;
		case 33: *value = SegmentAttributeXY_freeParking; break;
		case 34: *value = SegmentAttributeXY_timeRestrictionsOnParking; break;
		case 35: *value = SegmentAttributeXY_costToPark; break;
		case 36: *value = SegmentAttributeXY_midBlockCurbPresent; break;
		case 37: *value = SegmentAttributeXY_unEvenPavementPresent; break;
		default: break;
		}
	}
	else
	{
		switch(ui_SegmentAttributeXY)
		{
		default: *value = ui_SegmentAttributeXY; break;
		}
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_SegmentAttributeXYList(ASN1WorkSpace *workspace, SegmentAttributeXYList *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_SegmentAttributeXYList = { ASN1_CONST64(1), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_SegmentAttributeXYList_pdata = { ASN1_CONST64(0), ASN1_CONST64(37), NULL, 1, CONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	SegmentAttributeXY *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_SegmentAttributeXYList);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (SegmentAttributeXY *)mpool_calloc(GetMemPool(workspace), sizeof(SegmentAttributeXY), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_SegmentAttributeXY(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_ServiceAreaInformation_KOR(ASN1WorkSpace *workspace, ServiceAreaInformation_KOR *value)
{
	int ret = 0;
	ASNINT32 ui_direction;
	struct Asn1ConsInfo consinfo_name = { ASN1_CONST64(1), ASN1_CONST64(128), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_id = { ASN1_CONST64(1), ASN1_CONST64(128), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_direction = { ASN1_CONST64(0), ASN1_CONST64(2), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_stationInfo = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_parkingInfo = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNBOOL extbit_ServiceAreaInformation_KOR;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_ServiceAreaInformation_KOR);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 2, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("name", 0);
	  ret=ASN1_PER_UNAlign_Dec_UTF8Str(workspace, &(value->name), &consinfo_name);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("id", 0);
	  ret=ASN1_PER_UNAlign_Dec_UTF8Str(workspace, &(value->id), &consinfo_id);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_direction, &consinfo_direction);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (consinfo_direction.enumextbit == 0)
	{
		switch(ui_direction)
		{
		case 0: value->direction = HighwayDirection_KOR_up; break;
		case 1: value->direction = HighwayDirection_KOR_down; break;
		case 2: value->direction = HighwayDirection_KOR_upAndDown; break;
		default: break;
		}
	}
	else
	{
		switch(ui_direction)
		{
		default: value->direction = ui_direction; break;
		}
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_ServiceAreaInformation_KOR_stationInfo = 1;
		{ size_t saved=MqttDiag_enter("stationInfo", 0);
		  ret=ASN1_PER_UNAlign_Dec_ServiceAreaInformation_KOR_stationInfo(workspace, &(value->stationInfo));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_ServiceAreaInformation_KOR_parkingInfo = 1;
		{ size_t saved=MqttDiag_enter("parkingInfo", 0);
		  ret=ASN1_PER_UNAlign_Dec_ServiceAreaInformation_KOR_parkingInfo(workspace, &(value->parkingInfo));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_ServiceAreaInformation_KOR == 1)
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
int ASN1_PER_UNAlign_Data_Dec_ServiceAreaInformation_KOR_parkingInfo(ASN1WorkSpace *workspace, ServiceAreaInformation_KOR_parkingInfo *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_ServiceAreaInformation_KOR_parkingInfo = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_ServiceAreaInformation_KOR_parkingInfo_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	ParkingZoneInformation_KOR *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_ServiceAreaInformation_KOR_parkingInfo);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (ParkingZoneInformation_KOR *)mpool_calloc(GetMemPool(workspace), sizeof(ParkingZoneInformation_KOR), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_ParkingZoneInformation_KOR(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_ServiceAreaInformation_KOR_stationInfo(ASN1WorkSpace *workspace, ServiceAreaInformation_KOR_stationInfo *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_ServiceAreaInformation_KOR_stationInfo = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_ServiceAreaInformation_KOR_stationInfo_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	StationInformation_KOR *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_ServiceAreaInformation_KOR_stationInfo);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (StationInformation_KOR *)mpool_calloc(GetMemPool(workspace), sizeof(StationInformation_KOR), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_StationInformation_KOR(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_ShapePointSet(ASN1WorkSpace *workspace, ShapePointSet *value)
{
	int ret = 0;
	ASNINT32 ui_directionality;
	struct Asn1ConsInfo consinfo_anchor = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_laneWidth = { ASN1_CONST64(0), ASN1_CONST64(32767), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_directionality = { ASN1_CONST64(0), ASN1_CONST64(3), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_nodeList = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNBOOL extbit_ShapePointSet;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_ShapePointSet);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 3, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	value->anchor = (Position3D *)mpool_malloc(workspace->Pmemory, sizeof(Position3D));
	memset(value->anchor, 0, sizeof(Position3D));
	value->nodeList = (NodeListXY *)mpool_malloc(workspace->Pmemory, sizeof(NodeListXY));
	memset(value->nodeList, 0, sizeof(NodeListXY));
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_ShapePointSet_anchor = 1;
		{ size_t saved=MqttDiag_enter("anchor", 0);
		  ret=ASN1_PER_UNAlign_Dec_Position3D(workspace, value->anchor);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_ShapePointSet_laneWidth = 1;
		{ size_t saved=MqttDiag_enter("laneWidth", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->laneWidth), &consinfo_laneWidth);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_ShapePointSet_directionality = 1;
		{ size_t saved=MqttDiag_enter("", 0);
		  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_directionality, &consinfo_directionality);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (consinfo_directionality.enumextbit == 0)
		{
			switch(ui_directionality)
			{
			case 0: value->directionality = DirectionOfUse_unavailable; break;
			case 1: value->directionality = DirectionOfUse_forward; break;
			case 2: value->directionality = DirectionOfUse_reverse; break;
			case 3: value->directionality = DirectionOfUse_both; break;
			default: value->directionality = ui_directionality; break;
			}
		}
	}
	{ size_t saved=MqttDiag_enter("nodeList", 0);
	  ret=ASN1_PER_UNAlign_Dec_NodeListXY(workspace, value->nodeList);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (extbit_ShapePointSet == 1)
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
int ASN1_PER_UNAlign_Data_Dec_SpeedLimit(ASN1WorkSpace *workspace, SpeedLimit *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_SpeedLimit = { ASN1_CONST64(1), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_SpeedLimit_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	SpeedLimit_element *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_SpeedLimit);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (SpeedLimit_element *)mpool_calloc(GetMemPool(workspace), sizeof(SpeedLimit_element), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_SpeedLimit_element(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_SpeedLimitList(ASN1WorkSpace *workspace, SpeedLimitList *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_SpeedLimitList = { ASN1_CONST64(1), ASN1_CONST64(9), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_SpeedLimitList_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	RegulatorySpeedLimit *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_SpeedLimitList);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (RegulatorySpeedLimit *)mpool_calloc(GetMemPool(workspace), sizeof(RegulatorySpeedLimit), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_RegulatorySpeedLimit(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_SpeedLimit_element(ASN1WorkSpace *workspace, SpeedLimit_element *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_item = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	value->item = (SpeedLimit_element_item *)mpool_malloc(workspace->Pmemory, sizeof(SpeedLimit_element_item));
	memset(value->item, 0, sizeof(SpeedLimit_element_item));
	{ size_t saved=MqttDiag_enter("item", 0);
	  ret=ASN1_PER_UNAlign_Dec_SpeedLimit_element_item(workspace, value->item);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_SpeedLimit_element_item(ASN1WorkSpace *workspace, SpeedLimit_element_item *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_itis = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_text = { ASN1_CONST64(1), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 2);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_SpeedLimit_element_item_itis;
			break;
		case 1: index = DEF_SpeedLimit_element_item_text;
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
	{ size_t saved=MqttDiag_enter("M", 0);
	  ret=ASN1_GetM(&value->M, index);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	switch(index)
	{
	case DEF_SpeedLimit_element_item_itis:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->elements.itis), &consinfo_itis);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_SpeedLimit_element_item_text:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_IA5String(workspace, &(value->elements.text), &consinfo_text);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_StationInformation_KOR(ASN1WorkSpace *workspace, StationInformation_KOR *value)
{
	int ret = 0;
	ASNINT32 ui_type;
	struct Asn1ConsInfo consinfo_type = { ASN1_CONST64(0), ASN1_CONST64(7), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_capacity = { ASN1_CONST64(0), ASN1_CONST64(256), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_maxcapacity = { ASN1_CONST64(0), ASN1_CONST64(256), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_price = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNBOOL extbit_StationInformation_KOR;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_StationInformation_KOR);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 3, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_type, &consinfo_type);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (consinfo_type.enumextbit == 0)
	{
		switch(ui_type)
		{
		case 0: value->type = FuelType_KOR_gasoline; break;
		case 1: value->type = FuelType_KOR_diesel; break;
		case 2: value->type = FuelType_KOR_lpg; break;
		case 3: value->type = FuelType_KOR_premium; break;
		case 4: value->type = FuelType_KOR_hydrogen; break;
		case 5: value->type = FuelType_KOR_normalCharging; break;
		case 6: value->type = FuelType_KOR_quickCharging; break;
		case 7: value->type = FuelType_KOR_supercharging; break;
		default: break;
		}
	}
	else
	{
		switch(ui_type)
		{
		default: value->type = ui_type; break;
		}
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_StationInformation_KOR_capacity = 1;
		{ size_t saved=MqttDiag_enter("capacity", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->capacity), &consinfo_capacity);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_StationInformation_KOR_maxcapacity = 1;
		{ size_t saved=MqttDiag_enter("maxcapacity", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->maxcapacity), &consinfo_maxcapacity);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_StationInformation_KOR_price = 1;
		{ size_t saved=MqttDiag_enter("price", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->price), &consinfo_price);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_StationInformation_KOR == 1)
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
int ASN1_PER_UNAlign_Data_Dec_TimeChangeDetails(ASN1WorkSpace *workspace, TimeChangeDetails *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_startTime = { ASN1_CONST64(0), ASN1_CONST64(36111), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_minEndTime = { ASN1_CONST64(0), ASN1_CONST64(36111), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_maxEndTime = { ASN1_CONST64(0), ASN1_CONST64(36111), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_likelyTime = { ASN1_CONST64(0), ASN1_CONST64(36111), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_confidence = { ASN1_CONST64(0), ASN1_CONST64(15), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_nextTime = { ASN1_CONST64(0), ASN1_CONST64(36111), NULL, 0, CONS, 0, 0 };

	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 5, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_TimeChangeDetails_startTime = 1;
		{ size_t saved=MqttDiag_enter("startTime", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->startTime), &consinfo_startTime);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	{ size_t saved=MqttDiag_enter("minEndTime", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->minEndTime), &consinfo_minEndTime);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_TimeChangeDetails_maxEndTime = 1;
		{ size_t saved=MqttDiag_enter("maxEndTime", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->maxEndTime), &consinfo_maxEndTime);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_TimeChangeDetails_likelyTime = 1;
		{ size_t saved=MqttDiag_enter("likelyTime", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->likelyTime), &consinfo_likelyTime);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 4) == 1)
	{
		value->DEF_TimeChangeDetails_confidence = 1;
		{ size_t saved=MqttDiag_enter("confidence", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->confidence), &consinfo_confidence);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 5) == 1)
	{
		value->DEF_TimeChangeDetails_nextTime = 1;
		{ size_t saved=MqttDiag_enter("nextTime", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->nextTime), &consinfo_nextTime);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_TollgateLaneInformation_KOR(ASN1WorkSpace *workspace, TollgateLaneInformation_KOR *value)
{
	int ret = 0;
	ASNINT32 ui_heading;
	struct Asn1ConsInfo consinfo_name = { ASN1_CONST64(1), ASN1_CONST64(128), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_heading = { ASN1_CONST64(0), ASN1_CONST64(2), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_lanes = { ASN1_CONST64(1), ASN1_CONST64(32), NULL, 0, CONS, 0, 0 };

	ASNBOOL extbit_TollgateLaneInformation_KOR;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_TollgateLaneInformation_KOR);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 3, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_TollgateLaneInformation_KOR_name = 1;
		{ size_t saved=MqttDiag_enter("name", 0);
		  ret=ASN1_PER_UNAlign_Dec_UTF8Str(workspace, &(value->name), &consinfo_name);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_TollgateLaneInformation_KOR_heading = 1;
		{ size_t saved=MqttDiag_enter("", 0);
		  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_heading, &consinfo_heading);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (consinfo_heading.enumextbit == 0)
		{
			switch(ui_heading)
			{
			case 0: value->heading = HighwayDirection_KOR_up; break;
			case 1: value->heading = HighwayDirection_KOR_down; break;
			case 2: value->heading = HighwayDirection_KOR_upAndDown; break;
			default: break;
			}
		}
		else
		{
			switch(ui_heading)
			{
			default: value->heading = ui_heading; break;
			}
		}
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_TollgateLaneInformation_KOR_lanes = 1;
		{ size_t saved=MqttDiag_enter("lanes", 0);
		  ret=ASN1_PER_UNAlign_Dec_TollgateLaneInformation_KOR_lanes(workspace, &(value->lanes));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_TollgateLaneInformation_KOR == 1)
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
int ASN1_PER_UNAlign_Data_Dec_TollgateLaneInformation_KOR_lanes(ASN1WorkSpace *workspace, TollgateLaneInformation_KOR_lanes *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_TollgateLaneInformation_KOR_lanes = { ASN1_CONST64(1), ASN1_CONST64(32), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_TollgateLaneInformation_KOR_lanes_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	TollgateLane_KOR *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_TollgateLaneInformation_KOR_lanes);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (TollgateLane_KOR *)mpool_calloc(GetMemPool(workspace), sizeof(TollgateLane_KOR), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_TollgateLane_KOR(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_TollgateLane_KOR(ASN1WorkSpace *workspace, TollgateLane_KOR *value)
{
	int ret = 0;
	ASNINT32 ui_laneNo;
	ASNINT32 ui_type;
	struct Asn1ConsInfo consinfo_laneNo = { ASN1_CONST64(0), ASN1_CONST64(30), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_linkID = { ASN1_CONST64(0), ASN1_CONST64(255), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_type = { ASN1_CONST64(0), ASN1_CONST64(11), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_open = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNBOOL extbit_TollgateLane_KOR;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_TollgateLane_KOR);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 4, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_TollgateLane_KOR_laneNo = 1;
		{ size_t saved=MqttDiag_enter("", 0);
		  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_laneNo, &consinfo_laneNo);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (consinfo_laneNo.enumextbit == 0)
		{
			switch(ui_laneNo)
			{
			case 0: value->laneNo = DectLane_KOR_unavailable; break;
			case 1: value->laneNo = DectLane_KOR_busOnlyLane; break;
			case 2: value->laneNo = DectLane_KOR_ctrBusLane; break;
			case 3: value->laneNo = DectLane_KOR_rdSdBusLane; break;
			case 4: value->laneNo = DectLane_KOR_mergingLane; break;
			case 5: value->laneNo = DectLane_KOR_accelerationLane; break;
			case 6: value->laneNo = DectLane_KOR_decelrationLane; break;
			case 7: value->laneNo = DectLane_KOR_rampLane; break;
			case 8: value->laneNo = DectLane_KOR_shoulderLane; break;
			case 9: value->laneNo = DectLane_KOR_carLane; break;
			case 10: value->laneNo = DectLane_KOR_car_1stLane; break;
			case 11: value->laneNo = DectLane_KOR_car_2ndLane; break;
			case 12: value->laneNo = DectLane_KOR_car_3rdLane; break;
			case 13: value->laneNo = DectLane_KOR_car_4thLane; break;
			case 14: value->laneNo = DectLane_KOR_car_5thLane; break;
			case 15: value->laneNo = DectLane_KOR_car_6thLane; break;
			case 16: value->laneNo = DectLane_KOR_car_7thLane; break;
			case 17: value->laneNo = DectLane_KOR_car_8thLane; break;
			case 18: value->laneNo = DectLane_KOR_car_9thLane; break;
			case 19: value->laneNo = DectLane_KOR_car_10thLane; break;
			case 20: value->laneNo = DectLane_KOR_car_11thLane; break;
			case 21: value->laneNo = DectLane_KOR_car_12thLane; break;
			case 22: value->laneNo = DectLane_KOR_car_13thLane; break;
			case 23: value->laneNo = DectLane_KOR_car_14thLane; break;
			case 24: value->laneNo = DectLane_KOR_car_15thLane; break;
			case 25: value->laneNo = DectLane_KOR_car_16thLane; break;
			case 26: value->laneNo = DectLane_KOR_car_17thLane; break;
			case 27: value->laneNo = DectLane_KOR_car_18thLane; break;
			case 28: value->laneNo = DectLane_KOR_car_19thLane; break;
			case 29: value->laneNo = DectLane_KOR_car_20thLane; break;
			case 30: value->laneNo = DectLane_KOR_etcLane; break;
			default: break;
			}
		}
		else
		{
			switch(ui_laneNo)
			{
			default: value->laneNo = ui_laneNo; break;
			}
		}
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_TollgateLane_KOR_linkID = 1;
		{ size_t saved=MqttDiag_enter("linkID", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->linkID), &consinfo_linkID);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_TollgateLane_KOR_type = 1;
		{ size_t saved=MqttDiag_enter("", 0);
		  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_type, &consinfo_type);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (consinfo_type.enumextbit == 0)
		{
			switch(ui_type)
			{
			case 0: value->type = TollgateType_KOR_general; break;
			case 1: value->type = TollgateType_KOR_hipass; break;
			case 2: value->type = TollgateType_KOR_truck_hipass; break;
			case 3: value->type = TollgateType_KOR_multi_hipass_2; break;
			case 4: value->type = TollgateType_KOR_multi_hipass_3; break;
			case 5: value->type = TollgateType_KOR_multi_hipass_4; break;
			case 6: value->type = TollgateType_KOR_multi_hipass_5; break;
			case 7: value->type = TollgateType_KOR_multi_hipass_6; break;
			case 8: value->type = TollgateType_KOR_multi_hipass_7; break;
			case 9: value->type = TollgateType_KOR_multi_hipass_8; break;
			case 10: value->type = TollgateType_KOR_multi_hipass_9; break;
			case 11: value->type = TollgateType_KOR_multi_hipass_10; break;
			default: break;
			}
		}
		else
		{
			switch(ui_type)
			{
			default: value->type = ui_type; break;
			}
		}
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 4) == 1)
	{
		value->DEF_TollgateLane_KOR_open = 1;
		{ size_t saved=MqttDiag_enter("open", 0);
		  ret=ASN1_PER_UNAlign_Dec_BOOLEAN(workspace, &(value->open), &consinfo_open);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_TollgateLane_KOR == 1)
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
int ASN1_PER_UNAlign_Data_Dec_TrafficLightStatusList_KOR(ASN1WorkSpace *workspace, TrafficLightStatusList_KOR *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_TrafficLightStatusList_KOR = { ASN1_CONST64(1), ASN1_CONST64(255), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_TrafficLightStatusList_KOR_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	TrafficLightStatus_KOR *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_TrafficLightStatusList_KOR);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (TrafficLightStatus_KOR *)mpool_calloc(GetMemPool(workspace), sizeof(TrafficLightStatus_KOR), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_TrafficLightStatus_KOR(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_TrafficLightStatusMessage(ASN1WorkSpace *workspace, TrafficLightStatusMessage *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_traffiLightID = { ASN1_CONST64(0), ASN1_CONST64(4294967295), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_lon = { ASN1_CONST64(-1799999999), ASN1_CONST64(1800000001), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_lat = { ASN1_CONST64(-900000000), ASN1_CONST64(900000001), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_operationStatus = { ASN1_CONST64(8), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_controllerStatus = { ASN1_CONST64(8), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_cycleCounter = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_cycleTime = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_currentTime = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_trafficLightStatus = { ASN1_CONST64(1), ASN1_CONST64(255), NULL, 0, CONS, 0, 0 };

	ASNBOOL extbit_TrafficLightStatusMessage;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_TrafficLightStatusMessage);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 2, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	value->currentTime = (DDateTime *)mpool_malloc(workspace->Pmemory, sizeof(DDateTime));
	memset(value->currentTime, 0, sizeof(DDateTime));
	{ size_t saved=MqttDiag_enter("traffiLightID", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->traffiLightID), &consinfo_traffiLightID);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_TrafficLightStatusMessage_lon = 1;
		{ size_t saved=MqttDiag_enter("lon", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->lon), &consinfo_lon);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_TrafficLightStatusMessage_lat = 1;
		{ size_t saved=MqttDiag_enter("lat", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->lat), &consinfo_lat);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	{ size_t saved=MqttDiag_enter("operationStatus", 0);
	  ret=ASN1_PER_UNAlign_Dec_BITSTRING(workspace, &(value->operationStatus), &consinfo_operationStatus);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("controllerStatus", 0);
	  ret=ASN1_PER_UNAlign_Dec_BITSTRING(workspace, &(value->controllerStatus), &consinfo_controllerStatus);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("cycleCounter", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->cycleCounter), &consinfo_cycleCounter);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("cycleTime", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->cycleTime), &consinfo_cycleTime);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("currentTime", 0);
	  ret=ASN1_PER_UNAlign_Dec_DDateTime(workspace, value->currentTime);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("trafficLightStatus", 0);
	  ret=ASN1_PER_UNAlign_Dec_TrafficLightStatusList_KOR(workspace, &(value->trafficLightStatus));
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (extbit_TrafficLightStatusMessage == 1)
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
int ASN1_PER_UNAlign_Data_Dec_TrafficLightStatus_KOR(ASN1WorkSpace *workspace, TrafficLightStatus_KOR *value)
{
	int ret = 0;
	ASNINT32 ui_trafficLightIntervalType;
	struct Asn1ConsInfo consinfo_trafficLightType = { ASN1_CONST64(0), ASN1_CONST64(15), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_consecutiveTrafficLight = { ASN1_CONST64(0), ASN1_CONST64(15), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_trafficLightIntervalType = { ASN1_CONST64(0), ASN1_CONST64(1), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_pedestrianCall = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_actuatedinterval = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_permissiveNonProtected = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_lightingStatus = { ASN1_CONST64(0), ASN1_CONST64(10), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_maxIntervalLength = { ASN1_CONST64(0), ASN1_CONST64(255), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_remainingTime = { ASN1_CONST64(0), ASN1_CONST64(255), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_directionCode = { ASN1_CONST64(10), ASN1_CONST64(89), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_reserved = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNBOOL extbit_TrafficLightStatus_KOR;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_TrafficLightStatus_KOR);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("trafficLightType", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->trafficLightType), &consinfo_trafficLightType);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("consecutiveTrafficLight", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->consecutiveTrafficLight), &consinfo_consecutiveTrafficLight);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_trafficLightIntervalType, &consinfo_trafficLightIntervalType);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (consinfo_trafficLightIntervalType.enumextbit == 0)
	{
		switch(ui_trafficLightIntervalType)
		{
		case 0: value->trafficLightIntervalType = TrafficLightIntervalType_KOR_static; break;
		case 1: value->trafficLightIntervalType = TrafficLightIntervalType_KOR_variable; break;
		default: break;
		}
	}
	else
	{
		switch(ui_trafficLightIntervalType)
		{
		default: value->trafficLightIntervalType = ui_trafficLightIntervalType; break;
		}
	}
	{ size_t saved=MqttDiag_enter("pedestrianCall", 0);
	  ret=ASN1_PER_UNAlign_Dec_BOOLEAN(workspace, &(value->pedestrianCall), &consinfo_pedestrianCall);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("actuatedinterval", 0);
	  ret=ASN1_PER_UNAlign_Dec_BOOLEAN(workspace, &(value->actuatedinterval), &consinfo_actuatedinterval);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("permissiveNonProtected", 0);
	  ret=ASN1_PER_UNAlign_Dec_BOOLEAN(workspace, &(value->permissiveNonProtected), &consinfo_permissiveNonProtected);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("lightingStatus", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->lightingStatus), &consinfo_lightingStatus);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("maxIntervalLength", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->maxIntervalLength), &consinfo_maxIntervalLength);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("remainingTime", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->remainingTime), &consinfo_remainingTime);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("directionCode", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->directionCode), &consinfo_directionCode);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("reserved", 0);
	  ret=ASN1_PER_UNAlign_Dec_BOOLEAN(workspace, &(value->reserved), &consinfo_reserved);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (extbit_TrafficLightStatus_KOR == 1)
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
int ASN1_PER_UNAlign_Data_Dec_TravelerDataFrame(ASN1WorkSpace *workspace, TravelerDataFrame *value)
{
	int ret = 0;
	ASNINT32 ui_frameType;
	struct Asn1ConsInfo consinfo_notUsed = { ASN1_CONST64(0), ASN1_CONST64(31), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_frameType = { ASN1_CONST64(0), ASN1_CONST64(3), NULL, 1, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_msgId = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_startYear = { ASN1_CONST64(0), ASN1_CONST64(4095), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_startTime = { ASN1_CONST64(0), ASN1_CONST64(527040), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_durationTime = { ASN1_CONST64(0), ASN1_CONST64(32000), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_priority = { ASN1_CONST64(0), ASN1_CONST64(7), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_notUsed1 = { ASN1_CONST64(0), ASN1_CONST64(31), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_regions = { ASN1_CONST64(1), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_notUsed2 = { ASN1_CONST64(0), ASN1_CONST64(31), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_notUsed3 = { ASN1_CONST64(0), ASN1_CONST64(31), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_content = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_url = { ASN1_CONST64(1), ASN1_CONST64(15), NULL, 0, CONS, 0, 0 };

	ASNBOOL extbit_TravelerDataFrame;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_TravelerDataFrame);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 2, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	value->msgId = (TravelerDataFrame_msgId *)mpool_malloc(workspace->Pmemory, sizeof(TravelerDataFrame_msgId));
	memset(value->msgId, 0, sizeof(TravelerDataFrame_msgId));
	value->content = (TravelerDataFrame_content *)mpool_malloc(workspace->Pmemory, sizeof(TravelerDataFrame_content));
	memset(value->content, 0, sizeof(TravelerDataFrame_content));
	{ size_t saved=MqttDiag_enter("notUsed", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->notUsed), &consinfo_notUsed);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_frameType, &consinfo_frameType);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (consinfo_frameType.enumextbit == 0)
	{
		switch(ui_frameType)
		{
		case 0: value->frameType = TravelerInfoType_unknown; break;
		case 1: value->frameType = TravelerInfoType_advisory; break;
		case 2: value->frameType = TravelerInfoType_roadSignage; break;
		case 3: value->frameType = TravelerInfoType_commercialSignage; break;
		default: break;
		}
	}
	else
	{
		switch(ui_frameType)
		{
		default: value->frameType = ui_frameType; break;
		}
	}
	{ size_t saved=MqttDiag_enter("msgId", 0);
	  ret=ASN1_PER_UNAlign_Dec_TravelerDataFrame_msgId(workspace, value->msgId);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_TravelerDataFrame_startYear = 1;
		{ size_t saved=MqttDiag_enter("startYear", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->startYear), &consinfo_startYear);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	{ size_t saved=MqttDiag_enter("startTime", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->startTime), &consinfo_startTime);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("durationTime", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->durationTime), &consinfo_durationTime);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("priority", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->priority), &consinfo_priority);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("notUsed1", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->notUsed1), &consinfo_notUsed1);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("regions", 0);
	  ret=ASN1_PER_UNAlign_Dec_TravelerDataFrame_regions(workspace, &(value->regions));
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("notUsed2", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->notUsed2), &consinfo_notUsed2);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("notUsed3", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->notUsed3), &consinfo_notUsed3);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("content", 0);
	  ret=ASN1_PER_UNAlign_Dec_TravelerDataFrame_content(workspace, value->content);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_TravelerDataFrame_url = 1;
		{ size_t saved=MqttDiag_enter("url", 0);
		  ret=ASN1_PER_UNAlign_Dec_IA5String(workspace, &(value->url), &consinfo_url);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_TravelerDataFrame == 1)
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
int ASN1_PER_UNAlign_Data_Dec_TravelerDataFrameAdditionalInformation_KOR(ASN1WorkSpace *workspace, TravelerDataFrameAdditionalInformation_KOR *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_dataFrameIndex = { ASN1_CONST64(0), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_events = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_vehicleRidingStatus = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_weatherInfo = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_serviceArea = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_tollgate = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNBOOL extbit_TravelerDataFrameAdditionalInformation_KOR;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_TravelerDataFrameAdditionalInformation_KOR);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 5, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	value->events = (EventOrSvcInfo_KOR *)mpool_malloc(workspace->Pmemory, sizeof(EventOrSvcInfo_KOR));
	memset(value->events, 0, sizeof(EventOrSvcInfo_KOR));
	value->vehicleRidingStatus = (RidingNotification_KOR *)mpool_malloc(workspace->Pmemory, sizeof(RidingNotification_KOR));
	memset(value->vehicleRidingStatus, 0, sizeof(RidingNotification_KOR));
	value->weatherInfo = (WeatherInfo_KOR *)mpool_malloc(workspace->Pmemory, sizeof(WeatherInfo_KOR));
	memset(value->weatherInfo, 0, sizeof(WeatherInfo_KOR));
	value->serviceArea = (ServiceAreaInformation_KOR *)mpool_malloc(workspace->Pmemory, sizeof(ServiceAreaInformation_KOR));
	memset(value->serviceArea, 0, sizeof(ServiceAreaInformation_KOR));
	value->tollgate = (TollgateLaneInformation_KOR *)mpool_malloc(workspace->Pmemory, sizeof(TollgateLaneInformation_KOR));
	memset(value->tollgate, 0, sizeof(TollgateLaneInformation_KOR));
	{ size_t saved=MqttDiag_enter("dataFrameIndex", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->dataFrameIndex), &consinfo_dataFrameIndex);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_TravelerDataFrameAdditionalInformation_KOR_events = 1;
		{ size_t saved=MqttDiag_enter("events", 0);
		  ret=ASN1_PER_UNAlign_Dec_EventOrSvcInfo_KOR(workspace, value->events);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_TravelerDataFrameAdditionalInformation_KOR_vehicleRidingStatus = 1;
		{ size_t saved=MqttDiag_enter("vehicleRidingStatus", 0);
		  ret=ASN1_PER_UNAlign_Dec_RidingNotification_KOR(workspace, value->vehicleRidingStatus);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_TravelerDataFrameAdditionalInformation_KOR_weatherInfo = 1;
		{ size_t saved=MqttDiag_enter("weatherInfo", 0);
		  ret=ASN1_PER_UNAlign_Dec_WeatherInfo_KOR(workspace, value->weatherInfo);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 4) == 1)
	{
		value->DEF_TravelerDataFrameAdditionalInformation_KOR_serviceArea = 1;
		{ size_t saved=MqttDiag_enter("serviceArea", 0);
		  ret=ASN1_PER_UNAlign_Dec_ServiceAreaInformation_KOR(workspace, value->serviceArea);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 5) == 1)
	{
		value->DEF_TravelerDataFrameAdditionalInformation_KOR_tollgate = 1;
		{ size_t saved=MqttDiag_enter("tollgate", 0);
		  ret=ASN1_PER_UNAlign_Dec_TollgateLaneInformation_KOR(workspace, value->tollgate);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_TravelerDataFrameAdditionalInformation_KOR == 1)
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
int ASN1_PER_UNAlign_Data_Dec_TravelerDataFrameList(ASN1WorkSpace *workspace, TravelerDataFrameList *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_TravelerDataFrameList = { ASN1_CONST64(1), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_TravelerDataFrameList_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	TravelerDataFrame *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_TravelerDataFrameList);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (TravelerDataFrame *)mpool_calloc(GetMemPool(workspace), sizeof(TravelerDataFrame), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_TravelerDataFrame(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_TravelerDataFrame_content(ASN1WorkSpace *workspace, TravelerDataFrame_content *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_advisory = { ASN1_CONST64(1), ASN1_CONST64(100), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_workZone = { ASN1_CONST64(1), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_genericSign = { ASN1_CONST64(1), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_speedLimit = { ASN1_CONST64(1), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_exitService = { ASN1_CONST64(1), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 5);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_TravelerDataFrame_content_advisory;
			break;
		case 1: index = DEF_TravelerDataFrame_content_workZone;
			break;
		case 2: index = DEF_TravelerDataFrame_content_genericSign;
			break;
		case 3: index = DEF_TravelerDataFrame_content_speedLimit;
			break;
		case 4: index = DEF_TravelerDataFrame_content_exitService;
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
	{ size_t saved=MqttDiag_enter("M", 0);
	  ret=ASN1_GetM(&value->M, index);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	switch(index)
	{
	case DEF_TravelerDataFrame_content_advisory:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_ITIScodesAndText(workspace, &(value->elements.advisory));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_TravelerDataFrame_content_workZone:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_WorkZone(workspace, &(value->elements.workZone));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_TravelerDataFrame_content_genericSign:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_GenericSignage(workspace, &(value->elements.genericSign));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_TravelerDataFrame_content_speedLimit:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_SpeedLimit(workspace, &(value->elements.speedLimit));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_TravelerDataFrame_content_exitService:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_ExitService(workspace, &(value->elements.exitService));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_TravelerDataFrame_msgId(ASN1WorkSpace *workspace, TravelerDataFrame_msgId *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_furtherInfoID = { ASN1_CONST64(2), ASN1_CONST64(2), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_roadSignID = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 2);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_TravelerDataFrame_msgId_furtherInfoID;
			break;
		case 1: index = DEF_TravelerDataFrame_msgId_roadSignID;
			value->elements.roadSignID = (RoadSignID *)mpool_malloc(workspace->Pmemory, sizeof(RoadSignID));
			memset(value->elements.roadSignID, 0, sizeof(RoadSignID));
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
	{ size_t saved=MqttDiag_enter("M", 0);
	  ret=ASN1_GetM(&value->M, index);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	switch(index)
	{
	case DEF_TravelerDataFrame_msgId_furtherInfoID:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_OCTETSTRING(workspace, &(value->elements.furtherInfoID), &consinfo_furtherInfoID);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_TravelerDataFrame_msgId_roadSignID:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_RoadSignID(workspace, value->elements.roadSignID);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_TravelerDataFrame_regions(ASN1WorkSpace *workspace, TravelerDataFrame_regions *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_TravelerDataFrame_regions = { ASN1_CONST64(1), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_TravelerDataFrame_regions_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	GeographicalPath *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_TravelerDataFrame_regions);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (GeographicalPath *)mpool_calloc(GetMemPool(workspace), sizeof(GeographicalPath), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_GeographicalPath(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_TravelerInformation(ASN1WorkSpace *workspace, TravelerInformation *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_msgCnt = { ASN1_CONST64(0), ASN1_CONST64(127), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_timeStamp = { ASN1_CONST64(0), ASN1_CONST64(527040), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_packetID = { ASN1_CONST64(9), ASN1_CONST64(9), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_urlB = { ASN1_CONST64(1), ASN1_CONST64(45), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_dataFrames = { ASN1_CONST64(1), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };

	ASNBOOL extbit_TravelerInformation;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_TravelerInformation);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 4, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("msgCnt", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->msgCnt), &consinfo_msgCnt);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_TravelerInformation_timeStamp = 1;
		{ size_t saved=MqttDiag_enter("timeStamp", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->timeStamp), &consinfo_timeStamp);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_TravelerInformation_packetID = 1;
		{ size_t saved=MqttDiag_enter("packetID", 0);
		  ret=ASN1_PER_UNAlign_Dec_OCTETSTRING(workspace, &(value->packetID), &consinfo_packetID);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_TravelerInformation_urlB = 1;
		{ size_t saved=MqttDiag_enter("urlB", 0);
		  ret=ASN1_PER_UNAlign_Dec_IA5String(workspace, &(value->urlB), &consinfo_urlB);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	{ size_t saved=MqttDiag_enter("dataFrames", 0);
	  ret=ASN1_PER_UNAlign_Dec_TravelerDataFrameList(workspace, &(value->dataFrames));
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 4) == 1)
	{
		value->DEF_TravelerInformation_regional = 1;
		{ size_t saved=MqttDiag_enter("regional", 0);
		  ret=ASN1_PER_UNAlign_Dec_TravelerInformation_regional(workspace, &(value->regional));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_TravelerInformation == 1)
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
int ASN1_PER_UNAlign_Data_Dec_TravelerInformation_KOR(ASN1WorkSpace *workspace, TravelerInformation_KOR *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_msgID = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_additionalInfo = { ASN1_CONST64(1), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };

	ASNBOOL extbit_TravelerInformation_KOR;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_TravelerInformation_KOR);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 2, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_TravelerInformation_KOR_msgID = 1;
		{ size_t saved=MqttDiag_enter("msgID", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->msgID), &consinfo_msgID);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_TravelerInformation_KOR_additionalInfo = 1;
		{ size_t saved=MqttDiag_enter("additionalInfo", 0);
		  ret=ASN1_PER_UNAlign_Dec_TravelerInformation_KOR_additionalInfo(workspace, &(value->additionalInfo));
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_TravelerInformation_KOR == 1)
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
int ASN1_PER_UNAlign_Data_Dec_TravelerInformation_KOR_additionalInfo(ASN1WorkSpace *workspace, TravelerInformation_KOR_additionalInfo *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_TravelerInformation_KOR_additionalInfo = { ASN1_CONST64(1), ASN1_CONST64(8), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_TravelerInformation_KOR_additionalInfo_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	TravelerDataFrameAdditionalInformation_KOR *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_TravelerInformation_KOR_additionalInfo);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (TravelerDataFrameAdditionalInformation_KOR *)mpool_calloc(GetMemPool(workspace), sizeof(TravelerDataFrameAdditionalInformation_KOR), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_TravelerDataFrameAdditionalInformation_KOR(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_TravelerInformation_regional(ASN1WorkSpace *workspace, TravelerInformation_regional *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_TravelerInformation_regional = { ASN1_CONST64(1), ASN1_CONST64(4), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_TravelerInformation_regional_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	RegionalExtension *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_TravelerInformation_regional);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (RegionalExtension *)mpool_calloc(GetMemPool(workspace), sizeof(RegionalExtension), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_RegionalExtension(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_ValidRegion(ASN1WorkSpace *workspace, ValidRegion *value)
{
	int ret = 0;
	ASNINT32 ui_extent;
	struct Asn1ConsInfo consinfo_direction = { ASN1_CONST64(16), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_extent = { ASN1_CONST64(0), ASN1_CONST64(15), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_area = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 1, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	value->area = (ValidRegion_area *)mpool_malloc(workspace->Pmemory, sizeof(ValidRegion_area));
	memset(value->area, 0, sizeof(ValidRegion_area));
	{ size_t saved=MqttDiag_enter("direction", 0);
	  ret=ASN1_PER_UNAlign_Dec_BITSTRING(workspace, &(value->direction), &consinfo_direction);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_ValidRegion_extent = 1;
		{ size_t saved=MqttDiag_enter("", 0);
		  ret=ASN1_PER_UNAlign_Dec_ENUMERATED(workspace, &ui_extent, &consinfo_extent);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (consinfo_extent.enumextbit == 0)
		{
			switch(ui_extent)
			{
			case 0: value->extent = Extent_useInstantlyOnly; break;
			case 1: value->extent = Extent_useFor3meters; break;
			case 2: value->extent = Extent_useFor10meters; break;
			case 3: value->extent = Extent_useFor50meters; break;
			case 4: value->extent = Extent_useFor100meters; break;
			case 5: value->extent = Extent_useFor500meters; break;
			case 6: value->extent = Extent_useFor1000meters; break;
			case 7: value->extent = Extent_useFor5000meters; break;
			case 8: value->extent = Extent_useFor10000meters; break;
			case 9: value->extent = Extent_useFor50000meters; break;
			case 10: value->extent = Extent_useFor100000meters; break;
			case 11: value->extent = Extent_useFor500000meters; break;
			case 12: value->extent = Extent_useFor1000000meters; break;
			case 13: value->extent = Extent_useFor5000000meters; break;
			case 14: value->extent = Extent_useFor10000000meters; break;
			case 15: value->extent = Extent_forever; break;
			default: value->extent = ui_extent; break;
			}
		}
	}
	{ size_t saved=MqttDiag_enter("area", 0);
	  ret=ASN1_PER_UNAlign_Dec_ValidRegion_area(workspace, value->area);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_ValidRegion_area(ASN1WorkSpace *workspace, ValidRegion_area *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_shapePointSet = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_circle = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	struct Asn1ConsInfo consinfo_regionPointSet = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 3);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_ValidRegion_area_shapePointSet;
			value->elements.shapePointSet = (ShapePointSet *)mpool_malloc(workspace->Pmemory, sizeof(ShapePointSet));
			memset(value->elements.shapePointSet, 0, sizeof(ShapePointSet));
			break;
		case 1: index = DEF_ValidRegion_area_circle;
			value->elements.circle = (Circle *)mpool_malloc(workspace->Pmemory, sizeof(Circle));
			memset(value->elements.circle, 0, sizeof(Circle));
			break;
		case 2: index = DEF_ValidRegion_area_regionPointSet;
			value->elements.regionPointSet = (RegionPointSet *)mpool_malloc(workspace->Pmemory, sizeof(RegionPointSet));
			memset(value->elements.regionPointSet, 0, sizeof(RegionPointSet));
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
	{ size_t saved=MqttDiag_enter("M", 0);
	  ret=ASN1_GetM(&value->M, index);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	switch(index)
	{
	case DEF_ValidRegion_area_shapePointSet:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_ShapePointSet(workspace, value->elements.shapePointSet);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_ValidRegion_area_circle:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_Circle(workspace, value->elements.circle);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_ValidRegion_area_regionPointSet:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_RegionPointSet(workspace, value->elements.regionPointSet);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_VehicleSize(ASN1WorkSpace *workspace, VehicleSize *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_width = { ASN1_CONST64(0), ASN1_CONST64(1023), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_length = { ASN1_CONST64(0), ASN1_CONST64(4095), NULL, 0, CONS, 0, 0 };

	{ size_t saved=MqttDiag_enter("width", 0);

	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->width), &consinfo_width);

	  if(ret<0) MqttDiag_failure(workspace);

	  MqttDiag_leave(saved);

	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("length", 0);
	  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->length), &consinfo_length);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_WeatherInfo_KOR(ASN1WorkSpace *workspace, WeatherInfo_KOR *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_temp = { ASN1_CONST64(0), ASN1_CONST64(191), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_rainfall = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_humidity = { ASN1_CONST64(0), ASN1_CONST64(100), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_windDir = { ASN1_CONST64(16), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_windSpd = { ASN1_CONST64(0), ASN1_CONST64(10000), NULL, 0, CONS, 0, 0 };

	ASNBOOL extbit_WeatherInfo_KOR;
	ASNUINT8 *_optvalue;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_extbit(workspace, &extbit_WeatherInfo_KOR);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_Dec_Opt_Def_bit(workspace, 5, &_optvalue);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	if (ASN1_PER_CheckExtBit(_optvalue, 1) == 1)
	{
		value->DEF_WeatherInfo_KOR_temp = 1;
		{ size_t saved=MqttDiag_enter("temp", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->temp), &consinfo_temp);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 2) == 1)
	{
		value->DEF_WeatherInfo_KOR_rainfall = 1;
		{ size_t saved=MqttDiag_enter("rainfall", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->rainfall), &consinfo_rainfall);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 3) == 1)
	{
		value->DEF_WeatherInfo_KOR_humidity = 1;
		{ size_t saved=MqttDiag_enter("humidity", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->humidity), &consinfo_humidity);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 4) == 1)
	{
		value->DEF_WeatherInfo_KOR_windDir = 1;
		{ size_t saved=MqttDiag_enter("windDir", 0);
		  ret=ASN1_PER_UNAlign_Dec_BITSTRING(workspace, &(value->windDir), &consinfo_windDir);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (ASN1_PER_CheckExtBit(_optvalue, 5) == 1)
	{
		value->DEF_WeatherInfo_KOR_windSpd = 1;
		{ size_t saved=MqttDiag_enter("windSpd", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->windSpd), &consinfo_windSpd);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
	}
	if (extbit_WeatherInfo_KOR == 1)
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
int ASN1_PER_UNAlign_Data_Dec_WorkZone(ASN1WorkSpace *workspace, WorkZone *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_WorkZone = { ASN1_CONST64(1), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_WorkZone_pdata = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };
	ASNINT32 loop_set = 1;
	ASNINT32 process_length = 0;
	ASNINT32 i = 0;
	WorkZone_element *pdata;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_Creat_Init_List(workspace, value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	while(loop_set)
	{
		loop_set = ASN1_PER_UNAlign_Dec_Set_Seq_Of_Length(workspace, &process_length, &consinfo_WorkZone);
		for (i = 0; i < process_length; i++)
		{
			if ((pdata = (WorkZone_element *)mpool_calloc(GetMemPool(workspace), sizeof(WorkZone_element), 1)) == NULL) return -1;
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_PER_UNAlign_Dec_WorkZone_element(workspace, pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
			{ size_t saved=MqttDiag_enter("", value->count+1);
			  ret=ASN1_Insert_Node(workspace, value, (void *)pdata);
			  if(ret<0) MqttDiag_failure(workspace);
			  MqttDiag_leave(saved);
			  if(ret<0) return ret; }
		}
	}

	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_WorkZone_element(ASN1WorkSpace *workspace, WorkZone_element *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_item = { ASN1_CONST64(-9223372036854775807), ASN1_CONST64(9223372036854775807), NULL, 0, UNCONS, 0, 0 };

	value->item = (WorkZone_element_item *)mpool_malloc(workspace->Pmemory, sizeof(WorkZone_element_item));
	memset(value->item, 0, sizeof(WorkZone_element_item));
	{ size_t saved=MqttDiag_enter("item", 0);
	  ret=ASN1_PER_UNAlign_Dec_WorkZone_element_item(workspace, value->item);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Data_Dec_WorkZone_element_item(ASN1WorkSpace *workspace, WorkZone_element_item *value)
{
	int ret = 0;
	struct Asn1ConsInfo consinfo_itis = { ASN1_CONST64(0), ASN1_CONST64(65535), NULL, 0, CONS, 0, 0 };
	struct Asn1ConsInfo consinfo_text = { ASN1_CONST64(1), ASN1_CONST64(16), NULL, 0, CONS, 0, 0 };

	ASNINT32 index;
	ASNINT64 ui;
	ASNBOOL extbit;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Dec_Choice_ENUMERATED(workspace, &ui, &extbit, 0, 2);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }

	if (extbit == 0)
	{
		switch(ui)
		{
		case 0: index = DEF_WorkZone_element_item_itis;
			break;
		case 1: index = DEF_WorkZone_element_item_text;
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
	{ size_t saved=MqttDiag_enter("M", 0);
	  ret=ASN1_GetM(&value->M, index);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	switch(index)
	{
	case DEF_WorkZone_element_item_itis:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_INTEGER(workspace, &(value->elements.itis), &consinfo_itis);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	case DEF_WorkZone_element_item_text:
		{ size_t saved=MqttDiag_enter("elements", 0);
		  ret=ASN1_PER_UNAlign_Dec_IA5String(workspace, &(value->elements.text), &consinfo_text);
		  if(ret<0) MqttDiag_failure(workspace);
		  MqttDiag_leave(saved);
		  if(ret<0) return ret; }
		if (ret != 0) return -1;
		break;
	default: ret = ASN1_PER_Dec_unKnown(workspace, UNALIGN); break;
	}
	return ret;
}
int ASN1_PER_UNAlign_Dec_AccelerationSet4Way(ASN1WorkSpace *workspace, AccelerationSet4Way *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_AccelerationSet4Way(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_AccelerationSet4Way(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_AdvisorySpeed(ASN1WorkSpace *workspace, AdvisorySpeed *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_AdvisorySpeed(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_AdvisorySpeed(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_AdvisorySpeedList(ASN1WorkSpace *workspace, AdvisorySpeedList *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_AdvisorySpeedList(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_AdvisorySpeedList(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_AdvisorySpeed_regional(ASN1WorkSpace *workspace, AdvisorySpeed_regional *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_AdvisorySpeed_regional(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_AdvisorySpeed_regional(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_BSMcoreData(ASN1WorkSpace *workspace, BSMcoreData *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_BSMcoreData(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_BSMcoreData(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_BasicSafetyMessage(ASN1WorkSpace *workspace, BasicSafetyMessage *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_BasicSafetyMessage(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_BasicSafetyMessage(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_BasicSafetyMessage_partII(ASN1WorkSpace *workspace, BasicSafetyMessage_partII *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_BasicSafetyMessage_partII(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_BasicSafetyMessage_partII(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_BasicSafetyMessage_regional(ASN1WorkSpace *workspace, BasicSafetyMessage_regional *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_BasicSafetyMessage_regional(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_BasicSafetyMessage_regional(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_BrakeSystemStatus(ASN1WorkSpace *workspace, BrakeSystemStatus *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_BrakeSystemStatus(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_BrakeSystemStatus(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_Circle(ASN1WorkSpace *workspace, Circle *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_Circle(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_Circle(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_ComputedLane(ASN1WorkSpace *workspace, ComputedLane *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_ComputedLane(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ComputedLane(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_ComputedLane_offsetXaxis(ASN1WorkSpace *workspace, ComputedLane_offsetXaxis *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_ComputedLane_offsetXaxis(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ComputedLane_offsetXaxis(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_ComputedLane_offsetYaxis(ASN1WorkSpace *workspace, ComputedLane_offsetYaxis *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_ComputedLane_offsetYaxis(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ComputedLane_offsetYaxis(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_ComputedLane_regional(ASN1WorkSpace *workspace, ComputedLane_regional *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_ComputedLane_regional(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ComputedLane_regional(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_ConnectionManeuverAssist(ASN1WorkSpace *workspace, ConnectionManeuverAssist *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_ConnectionManeuverAssist(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ConnectionManeuverAssist(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_ConnectionManeuverAssist_regional(ASN1WorkSpace *workspace, ConnectionManeuverAssist_regional *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_ConnectionManeuverAssist_regional(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ConnectionManeuverAssist_regional(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_DDateTime(ASN1WorkSpace *workspace, DDateTime *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_DDateTime(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_DDateTime(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_EnabledLaneList(ASN1WorkSpace *workspace, EnabledLaneList *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_EnabledLaneList(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_EnabledLaneList(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_EventOrSvcInfo_KOR(ASN1WorkSpace *workspace, EventOrSvcInfo_KOR *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_EventOrSvcInfo_KOR(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_EventOrSvcInfo_KOR(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_EventOrSvcInfo_KOR_subtext(ASN1WorkSpace *workspace, EventOrSvcInfo_KOR_subtext *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_EventOrSvcInfo_KOR_subtext(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_EventOrSvcInfo_KOR_subtext(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_EventOrSvcInfo_KOR_text(ASN1WorkSpace *workspace, EventOrSvcInfo_KOR_text *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_EventOrSvcInfo_KOR_text(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_EventOrSvcInfo_KOR_text(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_ExitService(ASN1WorkSpace *workspace, ExitService *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_ExitService(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ExitService(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_ExitService_element(ASN1WorkSpace *workspace, ExitService_element *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_ExitService_element(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ExitService_element(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_ExitService_element_item(ASN1WorkSpace *workspace, ExitService_element_item *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_ExitService_element_item(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ExitService_element_item(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_GenericSignage(ASN1WorkSpace *workspace, GenericSignage *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_GenericSignage(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_GenericSignage(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_GenericSignage_element(ASN1WorkSpace *workspace, GenericSignage_element *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_GenericSignage_element(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_GenericSignage_element(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_GenericSignage_element_item(ASN1WorkSpace *workspace, GenericSignage_element_item *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_GenericSignage_element_item(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_GenericSignage_element_item(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_GeographicalPath(ASN1WorkSpace *workspace, GeographicalPath *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_GeographicalPath(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_GeographicalPath(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_GeographicalPath_KOR(ASN1WorkSpace *workspace, GeographicalPath_KOR *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_GeographicalPath_KOR(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_GeographicalPath_KOR(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_GeographicalPath_KOR_regions(ASN1WorkSpace *workspace, GeographicalPath_KOR_regions *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_GeographicalPath_KOR_regions(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_GeographicalPath_KOR_regions(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_GeographicalPath_description(ASN1WorkSpace *workspace, GeographicalPath_description *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_GeographicalPath_description(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_GeographicalPath_description(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_GeographicalPath_regional(ASN1WorkSpace *workspace, GeographicalPath_regional *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_GeographicalPath_regional(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_GeographicalPath_regional(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_GeometricProjection(ASN1WorkSpace *workspace, GeometricProjection *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_GeometricProjection(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_GeometricProjection(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_GeometricProjection_regional(ASN1WorkSpace *workspace, GeometricProjection_regional *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_GeometricProjection_regional(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_GeometricProjection_regional(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_ITIScodesAndText(ASN1WorkSpace *workspace, ITIScodesAndText *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_ITIScodesAndText(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ITIScodesAndText(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_ITIScodesAndText_element(ASN1WorkSpace *workspace, ITIScodesAndText_element *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_ITIScodesAndText_element(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ITIScodesAndText_element(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_ITIScodesAndText_element_item(ASN1WorkSpace *workspace, ITIScodesAndText_element_item *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_ITIScodesAndText_element_item(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ITIScodesAndText_element_item(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_IntersectionReferenceID(ASN1WorkSpace *workspace, IntersectionReferenceID *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_IntersectionReferenceID(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_IntersectionReferenceID(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_IntersectionState(ASN1WorkSpace *workspace, IntersectionState *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_IntersectionState(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_IntersectionState(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_IntersectionStateList(ASN1WorkSpace *workspace, IntersectionStateList *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_IntersectionStateList(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_IntersectionStateList(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_IntersectionState_regional(ASN1WorkSpace *workspace, IntersectionState_regional *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_IntersectionState_regional(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_IntersectionState_regional(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_LaneDataAttribute(ASN1WorkSpace *workspace, LaneDataAttribute *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_LaneDataAttribute(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_LaneDataAttribute(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_LaneDataAttributeList(ASN1WorkSpace *workspace, LaneDataAttributeList *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_LaneDataAttributeList(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_LaneDataAttributeList(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_LaneDataAttribute_regional(ASN1WorkSpace *workspace, LaneDataAttribute_regional *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_LaneDataAttribute_regional(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_LaneDataAttribute_regional(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_LaneID(ASN1WorkSpace *workspace, LaneID *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_LaneID(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_LaneID(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_ManeuverAssistList(ASN1WorkSpace *workspace, ManeuverAssistList *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_ManeuverAssistList(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ManeuverAssistList(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_MessageFrame(ASN1WorkSpace *workspace, MessageFrame *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_MessageFrame(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_MessageFrame(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_MovementEvent(ASN1WorkSpace *workspace, MovementEvent *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_MovementEvent(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_MovementEvent(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_MovementEventList(ASN1WorkSpace *workspace, MovementEventList *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_MovementEventList(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_MovementEventList(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_MovementEvent_regional(ASN1WorkSpace *workspace, MovementEvent_regional *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_MovementEvent_regional(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_MovementEvent_regional(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_MovementList(ASN1WorkSpace *workspace, MovementList *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_MovementList(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_MovementList(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_MovementState(ASN1WorkSpace *workspace, MovementState *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_MovementState(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_MovementState(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_MovementState_regional(ASN1WorkSpace *workspace, MovementState_regional *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_MovementState_regional(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_MovementState_regional(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_NodeAttributeLL(ASN1WorkSpace *workspace, NodeAttributeLL *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_NodeAttributeLL(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_NodeAttributeLL(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_NodeAttributeLLList(ASN1WorkSpace *workspace, NodeAttributeLLList *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_NodeAttributeLLList(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_NodeAttributeLLList(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_NodeAttributeSetLL(ASN1WorkSpace *workspace, NodeAttributeSetLL *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_NodeAttributeSetLL(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_NodeAttributeSetLL(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_NodeAttributeSetLL_regional(ASN1WorkSpace *workspace, NodeAttributeSetLL_regional *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_NodeAttributeSetLL_regional(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_NodeAttributeSetLL_regional(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_NodeAttributeSetXY(ASN1WorkSpace *workspace, NodeAttributeSetXY *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_NodeAttributeSetXY(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_NodeAttributeSetXY(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_NodeAttributeSetXY_regional(ASN1WorkSpace *workspace, NodeAttributeSetXY_regional *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_NodeAttributeSetXY_regional(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_NodeAttributeSetXY_regional(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_NodeAttributeXY(ASN1WorkSpace *workspace, NodeAttributeXY *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_NodeAttributeXY(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_NodeAttributeXY(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_NodeAttributeXYList(ASN1WorkSpace *workspace, NodeAttributeXYList *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_NodeAttributeXYList(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_NodeAttributeXYList(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_NodeLL(ASN1WorkSpace *workspace, NodeLL *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_NodeLL(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_NodeLL(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_NodeListLL(ASN1WorkSpace *workspace, NodeListLL *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_NodeListLL(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_NodeListLL(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_NodeListXY(ASN1WorkSpace *workspace, NodeListXY *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_NodeListXY(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_NodeListXY(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_NodeOffsetPointLL(ASN1WorkSpace *workspace, NodeOffsetPointLL *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_NodeOffsetPointLL(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_NodeOffsetPointLL(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_NodeOffsetPointXY(ASN1WorkSpace *workspace, NodeOffsetPointXY *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_NodeOffsetPointXY(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_NodeOffsetPointXY(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_NodeSetLL(ASN1WorkSpace *workspace, NodeSetLL *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_NodeSetLL(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_NodeSetLL(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_NodeSetXY(ASN1WorkSpace *workspace, NodeSetXY *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_NodeSetXY(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_NodeSetXY(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_NodeXY(ASN1WorkSpace *workspace, NodeXY *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_NodeXY(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_NodeXY(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_Node_LL_24B(ASN1WorkSpace *workspace, Node_LL_24B *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_Node_LL_24B(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_Node_LL_24B(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_Node_LL_28B(ASN1WorkSpace *workspace, Node_LL_28B *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_Node_LL_28B(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_Node_LL_28B(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_Node_LL_32B(ASN1WorkSpace *workspace, Node_LL_32B *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_Node_LL_32B(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_Node_LL_32B(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_Node_LL_36B(ASN1WorkSpace *workspace, Node_LL_36B *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_Node_LL_36B(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_Node_LL_36B(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_Node_LL_44B(ASN1WorkSpace *workspace, Node_LL_44B *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_Node_LL_44B(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_Node_LL_44B(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_Node_LL_48B(ASN1WorkSpace *workspace, Node_LL_48B *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_Node_LL_48B(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_Node_LL_48B(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_Node_LLmD_64b(ASN1WorkSpace *workspace, Node_LLmD_64b *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_Node_LLmD_64b(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_Node_LLmD_64b(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_Node_XY_20b(ASN1WorkSpace *workspace, Node_XY_20b *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_Node_XY_20b(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_Node_XY_20b(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_Node_XY_22b(ASN1WorkSpace *workspace, Node_XY_22b *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_Node_XY_22b(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_Node_XY_22b(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_Node_XY_24b(ASN1WorkSpace *workspace, Node_XY_24b *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_Node_XY_24b(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_Node_XY_24b(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_Node_XY_26b(ASN1WorkSpace *workspace, Node_XY_26b *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_Node_XY_26b(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_Node_XY_26b(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_Node_XY_28b(ASN1WorkSpace *workspace, Node_XY_28b *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_Node_XY_28b(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_Node_XY_28b(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_Node_XY_32b(ASN1WorkSpace *workspace, Node_XY_32b *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_Node_XY_32b(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_Node_XY_32b(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_OffsetSystem(ASN1WorkSpace *workspace, OffsetSystem *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_OffsetSystem(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_OffsetSystem(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_OffsetSystem_offset(ASN1WorkSpace *workspace, OffsetSystem_offset *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_OffsetSystem_offset(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_OffsetSystem_offset(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_ParkingCapacity_KOR(ASN1WorkSpace *workspace, ParkingCapacity_KOR *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_ParkingCapacity_KOR(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ParkingCapacity_KOR(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_ParkingZoneInformation_KOR(ASN1WorkSpace *workspace, ParkingZoneInformation_KOR *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_ParkingZoneInformation_KOR(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ParkingZoneInformation_KOR(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_ParkingZoneInformation_KOR_capacity(ASN1WorkSpace *workspace, ParkingZoneInformation_KOR_capacity *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_ParkingZoneInformation_KOR_capacity(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ParkingZoneInformation_KOR_capacity(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_PartIIcontent(ASN1WorkSpace *workspace, PartIIcontent *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_PartIIcontent(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_PartIIcontent(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_Position3D(ASN1WorkSpace *workspace, Position3D *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_Position3D(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_Position3D(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_Position3D_regional(ASN1WorkSpace *workspace, Position3D_regional *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_Position3D_regional(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_Position3D_regional(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_PositionalAccuracy(ASN1WorkSpace *workspace, PositionalAccuracy *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_PositionalAccuracy(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_PositionalAccuracy(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_RegionDescribedByID_KOR(ASN1WorkSpace *workspace, RegionDescribedByID_KOR *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_RegionDescribedByID_KOR(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_RegionDescribedByID_KOR(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_RegionList(ASN1WorkSpace *workspace, RegionList *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_RegionList(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_RegionList(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_RegionOffsets(ASN1WorkSpace *workspace, RegionOffsets *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_RegionOffsets(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_RegionOffsets(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_RegionPointSet(ASN1WorkSpace *workspace, RegionPointSet *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_RegionPointSet(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_RegionPointSet(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_RegionalExtension(ASN1WorkSpace *workspace, RegionalExtension *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_RegionalExtension(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_RegionalExtension(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_RegulatorySpeedLimit(ASN1WorkSpace *workspace, RegulatorySpeedLimit *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_RegulatorySpeedLimit(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_RegulatorySpeedLimit(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_RidingNotification_KOR(ASN1WorkSpace *workspace, RidingNotification_KOR *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_RidingNotification_KOR(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_RidingNotification_KOR(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_RoadSegmentReferenceID(ASN1WorkSpace *workspace, RoadSegmentReferenceID *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_RoadSegmentReferenceID(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_RoadSegmentReferenceID(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_RoadSignID(ASN1WorkSpace *workspace, RoadSignID *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_RoadSignID(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_RoadSignID(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_SPAT(ASN1WorkSpace *workspace, SPAT *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_SPAT(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_SPAT(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_SPAT_regional(ASN1WorkSpace *workspace, SPAT_regional *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_SPAT_regional(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_SPAT_regional(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_SegmentAttributeLL(ASN1WorkSpace *workspace, SegmentAttributeLL *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_SegmentAttributeLL(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_SegmentAttributeLL(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_SegmentAttributeLLList(ASN1WorkSpace *workspace, SegmentAttributeLLList *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_SegmentAttributeLLList(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_SegmentAttributeLLList(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_SegmentAttributeXY(ASN1WorkSpace *workspace, SegmentAttributeXY *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_SegmentAttributeXY(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_SegmentAttributeXY(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_SegmentAttributeXYList(ASN1WorkSpace *workspace, SegmentAttributeXYList *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_SegmentAttributeXYList(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_SegmentAttributeXYList(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_ServiceAreaInformation_KOR(ASN1WorkSpace *workspace, ServiceAreaInformation_KOR *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_ServiceAreaInformation_KOR(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ServiceAreaInformation_KOR(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_ServiceAreaInformation_KOR_parkingInfo(ASN1WorkSpace *workspace, ServiceAreaInformation_KOR_parkingInfo *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_ServiceAreaInformation_KOR_parkingInfo(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ServiceAreaInformation_KOR_parkingInfo(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_ServiceAreaInformation_KOR_stationInfo(ASN1WorkSpace *workspace, ServiceAreaInformation_KOR_stationInfo *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_ServiceAreaInformation_KOR_stationInfo(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ServiceAreaInformation_KOR_stationInfo(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_ShapePointSet(ASN1WorkSpace *workspace, ShapePointSet *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_ShapePointSet(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ShapePointSet(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_SpeedLimit(ASN1WorkSpace *workspace, SpeedLimit *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_SpeedLimit(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_SpeedLimit(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_SpeedLimitList(ASN1WorkSpace *workspace, SpeedLimitList *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_SpeedLimitList(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_SpeedLimitList(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_SpeedLimit_element(ASN1WorkSpace *workspace, SpeedLimit_element *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_SpeedLimit_element(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_SpeedLimit_element(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_SpeedLimit_element_item(ASN1WorkSpace *workspace, SpeedLimit_element_item *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_SpeedLimit_element_item(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_SpeedLimit_element_item(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_StationInformation_KOR(ASN1WorkSpace *workspace, StationInformation_KOR *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_StationInformation_KOR(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_StationInformation_KOR(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_TimeChangeDetails(ASN1WorkSpace *workspace, TimeChangeDetails *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_TimeChangeDetails(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_TimeChangeDetails(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_TollgateLaneInformation_KOR(ASN1WorkSpace *workspace, TollgateLaneInformation_KOR *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_TollgateLaneInformation_KOR(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_TollgateLaneInformation_KOR(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_TollgateLaneInformation_KOR_lanes(ASN1WorkSpace *workspace, TollgateLaneInformation_KOR_lanes *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_TollgateLaneInformation_KOR_lanes(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_TollgateLaneInformation_KOR_lanes(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_TollgateLane_KOR(ASN1WorkSpace *workspace, TollgateLane_KOR *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_TollgateLane_KOR(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_TollgateLane_KOR(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_TrafficLightStatusList_KOR(ASN1WorkSpace *workspace, TrafficLightStatusList_KOR *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_TrafficLightStatusList_KOR(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_TrafficLightStatusList_KOR(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_TrafficLightStatusMessage(ASN1WorkSpace *workspace, TrafficLightStatusMessage *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_TrafficLightStatusMessage(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_TrafficLightStatusMessage(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_TrafficLightStatus_KOR(ASN1WorkSpace *workspace, TrafficLightStatus_KOR *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_TrafficLightStatus_KOR(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_TrafficLightStatus_KOR(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_TravelerDataFrame(ASN1WorkSpace *workspace, TravelerDataFrame *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_TravelerDataFrame(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_TravelerDataFrame(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_TravelerDataFrameAdditionalInformation_KOR(ASN1WorkSpace *workspace, TravelerDataFrameAdditionalInformation_KOR *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_TravelerDataFrameAdditionalInformation_KOR(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_TravelerDataFrameAdditionalInformation_KOR(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_TravelerDataFrameList(ASN1WorkSpace *workspace, TravelerDataFrameList *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_TravelerDataFrameList(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_TravelerDataFrameList(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_TravelerDataFrame_content(ASN1WorkSpace *workspace, TravelerDataFrame_content *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_TravelerDataFrame_content(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_TravelerDataFrame_content(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_TravelerDataFrame_msgId(ASN1WorkSpace *workspace, TravelerDataFrame_msgId *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_TravelerDataFrame_msgId(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_TravelerDataFrame_msgId(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_TravelerDataFrame_regions(ASN1WorkSpace *workspace, TravelerDataFrame_regions *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_TravelerDataFrame_regions(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_TravelerDataFrame_regions(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_TravelerInformation(ASN1WorkSpace *workspace, TravelerInformation *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_TravelerInformation(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_TravelerInformation(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_TravelerInformation_KOR(ASN1WorkSpace *workspace, TravelerInformation_KOR *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_TravelerInformation_KOR(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_TravelerInformation_KOR(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_TravelerInformation_KOR_additionalInfo(ASN1WorkSpace *workspace, TravelerInformation_KOR_additionalInfo *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_TravelerInformation_KOR_additionalInfo(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_TravelerInformation_KOR_additionalInfo(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_TravelerInformation_regional(ASN1WorkSpace *workspace, TravelerInformation_regional *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_TravelerInformation_regional(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_TravelerInformation_regional(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_ValidRegion(ASN1WorkSpace *workspace, ValidRegion *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_ValidRegion(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ValidRegion(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_ValidRegion_area(ASN1WorkSpace *workspace, ValidRegion_area *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_ValidRegion_area(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_ValidRegion_area(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_VehicleSize(ASN1WorkSpace *workspace, VehicleSize *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_VehicleSize(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_VehicleSize(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_WeatherInfo_KOR(ASN1WorkSpace *workspace, WeatherInfo_KOR *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_WeatherInfo_KOR(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_WeatherInfo_KOR(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_WorkZone(ASN1WorkSpace *workspace, WorkZone *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_WorkZone(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_WorkZone(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_WorkZone_element(ASN1WorkSpace *workspace, WorkZone_element *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_WorkZone_element(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_WorkZone_element(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}
int ASN1_PER_UNAlign_Dec_WorkZone_element_item(ASN1WorkSpace *workspace, WorkZone_element_item *value)
{
	int ret = 0;
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_PER_UNAlign_Data_Dec_WorkZone_element_item(workspace,value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	{ size_t saved=MqttDiag_enter("", 0);
	  ret=ASN1_CHECK_WorkZone_element_item(value);
	  if(ret<0) MqttDiag_failure(workspace);
	  MqttDiag_leave(saved);
	  if(ret<0) return ret; }
	return ret;
}

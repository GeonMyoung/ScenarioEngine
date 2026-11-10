/* Derived from GitsnAsnUtil/src/GitsnAsnUtil.c at 2130b69.

   New-module-only MAP/TIM conversion. Releases preallocated optional lists

   before replacement and fixes bit-count rounding. Legacy source is unchanged. */

#include <GitsnAsnUtil.h>

#include <dz1_gasn_support.h>

static Gitsn_LaneTypeAttributes *init_LaneTypeAttributes_from_ASN(LaneTypeAttributes *src, Dz1Error *errp);

static Gitsn_LaneAttributes *init_LaneAttributes_from_ASN(LaneAttributes *src, Dz1Error *errp);

static Gitsn_ConnectingLane *init_ConnectingLane_from_ASN(ConnectingLane *src, Dz1Error *errp);

static Gitsn_Connection *init_Connection_from_ASN(Connection *src, Dz1Error *errp);

static Gitsn_ConnectsToList *init_ConnectsToList_from_ASN(ConnectsToList *src, Dz1Error *errp);

static Gitsn_OverlayLaneList *init_OverlayLaneList_from_ASN(OverlayLaneList *src, Dz1Error *errp);

static Gitsn_GenericLane *init_GenericLane_from_ASN(GenericLane *src, Dz1Error *errp);

static Gitsn_LaneList *init_LaneList_from_ASN(LaneList *src, Dz1Error *errp);

static Gitsn_IntersectionGeometry *init_IntersectionGeometry_from_ASN(IntersectionGeometry *src,
                                                                      Dz1Error *errp);

static Gitsn_IntersectionGeometryList *init_IntersectionGeometryList_from_ASN(IntersectionGeometryList *src,
                                                                              Dz1Error *errp);

static Gitsn_RoadLaneSetList *init_RoadLaneSetList_from_ASN(RoadLaneSetList *src, Dz1Error *errp);

static Gitsn_RoadSegment *init_RoadSegment_from_ASN(RoadSegment *src, Dz1Error *errp);

static Gitsn_RoadSegmentList *init_RoadSegmentList_from_ASN(RoadSegmentList *src, Dz1Error *errp);

static Gitsn_DataParameters *init_DataParameters_from_ASN(DataParameters *src, Dz1Error *errp);

static Gitsn_RestrictionUserType *init_RestrictionUserType_from_ASN(RestrictionUserType *src, Dz1Error *errp);

static Gitsn_RestrictionUserTypeList *init_RestrictionUserTypeList_from_ASN(RestrictionUserTypeList *src,
                                                                            Dz1Error *errp);

static Gitsn_RestrictionClassAssignment *
init_RestrictionClassAssignment_from_ASN(RestrictionClassAssignment *src, Dz1Error *errp);

static Gitsn_RestrictionClassList *init_RestrictionClassList_from_ASN(RestrictionClassList *src,
                                                                      Dz1Error *errp);

bool_t DatexMapFromASN(MapData *src, Gitsn_MapData *dst, Dz1Error *err);

static Gitsn_IntersectionReferenceID *init_IntersectionReferenceID_from_ASN(IntersectionReferenceID *src,
                                                                            Dz1Error *errp);

static Gitsn_Position3D *init_Position3D_from_ASN(Position3D *src, Dz1Error *errp);

static Gitsn_RoadSignID *init_RoadSignID_from_ASN(RoadSignID *src, Dz1Error *errp);

static Gitsn_TravelerDataFrame_msgId *init_TravelerDataFrame_msgId_from_ASN(TravelerDataFrame_msgId *src,
                                                                            Dz1Error *errp);

static Gitsn_RoadSegmentReferenceID *init_RoadSegmentReferenceID_from_ASN(RoadSegmentReferenceID *src,
                                                                          Dz1Error *errp);

static Gitsn_NodeOffsetPointXY *init_NodeOffsetPointXY_from_ASN(NodeOffsetPointXY *src, Dz1Error *errp);

static Gitsn_NodeAttributeXYList *init_NodeAttributeXYList_from_ASN(NodeAttributeXYList *src, Dz1Error *errp);

static Gitsn_SegmentAttributeXYList *init_SegmentAttributeXYList_from_ASN(SegmentAttributeXYList *src,
                                                                          Dz1Error *errp);

static Gitsn_RegulatorySpeedLimit *init_RegulatorySpeedLimit_from_ASN(RegulatorySpeedLimit *src,
                                                                      Dz1Error *errp);

static Gitsn_SpeedLimitList *init_SpeedLimitList_from_ASN(SpeedLimitList *src, Dz1Error *errp);

static Gitsn_LaneDataAttribute *init_LaneDataAttribute_from_ASN(LaneDataAttribute *src, Dz1Error *errp);

static Gitsn_LaneDataAttributeList *init_LaneDataAttributeList_from_ASN(LaneDataAttributeList *src,
                                                                        Dz1Error *errp);

static Gitsn_NodeAttributeSetXY *init_NodeAttributeSetXY_from_ASN(NodeAttributeSetXY *src, Dz1Error *errp);

static Gitsn_NodeXY *init_NodeXY_from_ASN(NodeXY *src, Dz1Error *errp);

static Gitsn_NodeSetXY *init_NodeSetXY_from_ASN(NodeSetXY *src, Dz1Error *errp);

static Gitsn_ComputedLane_offsetXaxis *init_ComputedLane_offsetXaxis_from_ASN(ComputedLane_offsetXaxis *src,
                                                                              Dz1Error *errp);

static Gitsn_ComputedLane_offsetYaxis *init_ComputedLane_offsetYaxis_from_ASN(ComputedLane_offsetYaxis *src,
                                                                              Dz1Error *errp);

static Gitsn_ComputedLane *init_ComputedLane_from_ASN(ComputedLane *src, Dz1Error *errp);

static Gitsn_NodeListXY *init_NodeListXY_from_ASN(NodeListXY *src, Dz1Error *errp);

static Gitsn_NodeOffsetPointLL *init_NodeOffsetPointLL_from_ASN(NodeOffsetPointLL *src, Dz1Error *errp);

static Gitsn_NodeAttributeLLList *init_NodeAttributeLLList_from_ASN(NodeAttributeLLList *src, Dz1Error *errp);

static Gitsn_SegmentAttributeLLList *init_SegmentAttributeLLList_from_ASN(SegmentAttributeLLList *src,
                                                                          Dz1Error *errp);

static Gitsn_NodeAttributeSetLL *init_NodeAttributeSetLL_from_ASN(NodeAttributeSetLL *src, Dz1Error *errp);

static Gitsn_NodeLL *init_NodeLL_from_ASN(NodeLL *src, Dz1Error *errp);

static Gitsn_NodeSetLL *init_NodeSetLL_from_ASN(NodeSetLL *src, Dz1Error *errp);

static Gitsn_NodeListLL *init_NodeListLL_from_ASN(NodeListLL *src, Dz1Error *errp);

static Gitsn_OffsetSystem_offset *init_OffsetSystem_offset_from_ASN(OffsetSystem_offset *src, Dz1Error *errp);

static Gitsn_OffsetSystem *init_OffsetSystem_from_ASN(OffsetSystem *src, Dz1Error *errp);

static Gitsn_Circle *init_Circle_from_ASN(Circle *src, Dz1Error *errp);

static Gitsn_GeometricProjection *init_GeometricProjection_from_ASN(GeometricProjection *src, Dz1Error *errp);

static Gitsn_ShapePointSet *init_ShapePointSet_from_ASN(ShapePointSet *src, Dz1Error *errp);

static Gitsn_RegionOffsets *init_RegionOffsets_from_ASN(RegionOffsets *src, Dz1Error *errp);

static Gitsn_RegionList *init_RegionList_from_ASN(RegionList *src, Dz1Error *errp);

static Gitsn_RegionPointSet *init_RegionPointSet_from_ASN(RegionPointSet *src, Dz1Error *errp);

static Gitsn_ValidRegion_area *init_ValidRegion_area_from_ASN(ValidRegion_area *src, Dz1Error *errp);

static Gitsn_ValidRegion *init_ValidRegion_from_ASN(ValidRegion *src, Dz1Error *errp);

static Gitsn_GeographicalPath_description *
init_GeographicalPath_description_from_ASN(GeographicalPath_description *src, Dz1Error *errp);

static Gitsn_GeographicalPath *init_GeographicalPath_from_ASN(GeographicalPath *src, Dz1Error *errp);

static Gitsn_TravelerDataFrame_regions *
init_TravelerDataFrame_regions_from_ASN(TravelerDataFrame_regions *src, Dz1Error *errp);

static Gitsn_ITIScodesAndText_element_item *
init_ITIScodesAndText_element_item_from_ASN(ITIScodesAndText_element_item *src, Dz1Error *errp);

static Gitsn_ITIScodesAndText_element *init_ITIScodesAndText_element_from_ASN(ITIScodesAndText_element *src,
                                                                              Dz1Error *errp);

static Gitsn_ITIScodesAndText *init_ITIScodesAndText_from_ASN(ITIScodesAndText *src, Dz1Error *errp);

static Gitsn_WorkZone_element_item *init_WorkZone_element_item_from_ASN(WorkZone_element_item *src,
                                                                        Dz1Error *errp);

static Gitsn_WorkZone_element *init_WorkZone_element_from_ASN(WorkZone_element *src, Dz1Error *errp);

static Gitsn_WorkZone *init_WorkZone_from_ASN(WorkZone *src, Dz1Error *errp);

static Gitsn_GenericSignage_element_item *
init_GenericSignage_element_item_from_ASN(GenericSignage_element_item *src, Dz1Error *errp);

static Gitsn_GenericSignage_element *init_GenericSignage_element_from_ASN(GenericSignage_element *src,
                                                                          Dz1Error *errp);

static Gitsn_GenericSignage *init_GenericSignage_from_ASN(GenericSignage *src, Dz1Error *errp);

static Gitsn_SpeedLimit_element_item *init_SpeedLimit_element_item_from_ASN(SpeedLimit_element_item *src,
                                                                            Dz1Error *errp);

static Gitsn_SpeedLimit_element *init_SpeedLimit_element_from_ASN(SpeedLimit_element *src, Dz1Error *errp);

static Gitsn_SpeedLimit *init_SpeedLimit_from_ASN(SpeedLimit *src, Dz1Error *errp);

static Gitsn_ExitService_element_item *init_ExitService_element_item_from_ASN(ExitService_element_item *src,
                                                                              Dz1Error *errp);

static Gitsn_ExitService_element *init_ExitService_element_from_ASN(ExitService_element *src, Dz1Error *errp);

static Gitsn_ExitService *init_ExitService_from_ASN(ExitService *src, Dz1Error *errp);

static Gitsn_TravelerDataFrame_content *
init_TravelerDataFrame_content_from_ASN(TravelerDataFrame_content *src, Dz1Error *errp);

static Gitsn_TravelerDataFrame *init_TravelerDataFrame_from_ASN(TravelerDataFrame *src, Dz1Error *errp);

static Gitsn_TravelerDataFrameList *init_TravelerDataFrameList_from_ASN(TravelerDataFrameList *src,
                                                                        Dz1Error *errp);

bool_t DatexTravelerFromASN(TravelerInformation *src, Gitsn_TravelerInformation *dst, Dz1Error *err);

static Gitsn_LaneTypeAttributes *init_LaneTypeAttributes_from_ASN(LaneTypeAttributes *src, Dz1Error *errp) {
    Gitsn_LaneTypeAttributes *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_LaneTypeAttributes_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_LaneTypeAttributes_delAndSetNull, (void *)&ret);
        switch (src->M) {
        case DEF_LaneTypeAttributes_vehicle: {
            size_t sz = (src->elements.vehicle.numbits + 7) / 8;
            if ((ret->x.vehicle = Dz1Calloc(sz, 1, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if (memcpy(ret->x.vehicle, src->elements.vehicle.data, sz) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_LaneTypeAttributesPresent_vehicle;
                Dz1Error_set(errp, 0);
            }
        } break;
        case DEF_LaneTypeAttributes_crosswalk:
            if ((ret->x.crosswalk = Dz1Calloc(2, 1, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if (memcpy(ret->x.crosswalk, src->elements.crosswalk.data, 2) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_LaneTypeAttributesPresent_crosswalk;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_LaneTypeAttributes_bikeLane:
            if ((ret->x.bikeLane = Dz1Calloc(2, 1, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if (memcpy(ret->x.bikeLane, src->elements.bikeLane.data, 2) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_LaneTypeAttributesPresent_bikeLane;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_LaneTypeAttributes_sidewalk:
            if ((ret->x.sidewalk = Dz1Calloc(2, 1, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if (memcpy(ret->x.sidewalk, src->elements.sidewalk.data, 2) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_LaneTypeAttributesPresent_sidewalk;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_LaneTypeAttributes_median:
            if ((ret->x.median = Dz1Calloc(2, 1, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if (memcpy(ret->x.median, src->elements.median.data, 2) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_LaneTypeAttributesPresent_median;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_LaneTypeAttributes_striping:
            if ((ret->x.striping = Dz1Calloc(2, 1, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if (memcpy(ret->x.striping, src->elements.striping.data, 2) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_LaneTypeAttributesPresent_striping;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_LaneTypeAttributes_trackedVehicle:
            if ((ret->x.trackedVehicle = Dz1Calloc(2, 1, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if (memcpy(ret->x.trackedVehicle, src->elements.trackedVehicle.data, 2) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_LaneTypeAttributesPresent_trackedVehicle;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_LaneTypeAttributes_parking:
            if ((ret->x.parking = Dz1Calloc(2, 1, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if (memcpy(ret->x.parking, src->elements.parking.data, 2) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_LaneTypeAttributesPresent_parking;
                Dz1Error_set(errp, 0);
            }
            break;
        default:
            ERR_SET_OUT(errp, EPERM);
            break;
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_LaneTypeAttributes_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_LaneAttributes *init_LaneAttributes_from_ASN(LaneAttributes *src, Dz1Error *errp) {
    Gitsn_LaneAttributes *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_LaneAttributes_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_LaneAttributes_delAndSetNull, (void *)&ret);
        if ((ret->directionalUse = Dz1Calloc(1, 1, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else if (memcpy(ret->directionalUse, src->directionalUse.data, 1) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else if ((ret->sharedWith = Dz1Calloc(2, 1, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else if (memcpy(ret->sharedWith, src->sharedWith.data, 2) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else if ((ret->laneType = init_LaneTypeAttributes_from_ASN(src->laneType, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else {
            // gm ~
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_LaneAttributes_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_ConnectingLane *init_ConnectingLane_from_ASN(ConnectingLane *src, Dz1Error *errp) {
    Gitsn_ConnectingLane *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_ConnectingLane_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_ConnectingLane_delAndSetNull, (void *)&ret);
        ret->lane = src->lane;
        if (src->DEF_ConnectingLane_maneuver) {
            size_t sz = 0;
            sz = (src->maneuver.numbits + 7) / 8;
            if ((ret->maneuver = Dz1Calloc(sz, 1, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if (memcpy(ret->maneuver, src->maneuver.data, sz) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else
                Dz1Error_set(errp, 0);
        }

        pthread_cleanup_pop(errp->code); // (Gitsn_ConnectingLane_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_Connection *init_Connection_from_ASN(Connection *src, Dz1Error *errp) {
    Gitsn_Connection *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_Connection_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_Connection_delAndSetNull, (void *)ret);
        if ((ret->connecctingLnae = init_ConnectingLane_from_ASN(src->connectingLane, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else {
            if (src->DEF_Connection_remoteIntersection) {
                if ((ret->remoteIntersection =
                         init_IntersectionReferenceID_from_ASN(src->remoteIntersection, errp)) == NULL)
                    ERR_SET_OUT(errp, EFAULT);
                else
                    Dz1Error_set(errp, 0);
            }
            if (src->DEF_Connection_signalGroup) {
                ret->signalGroup = src->signalGroup;
            }
            if (src->DEF_Connection_userClass) {
                ret->userClass = src->userClass;
            }
            if (src->DEF_Connection_connectionID) {
                ret->connectionID = src->connectionID;
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_Connection_delAndSetNull, (void*)ret);
    }
    return ret;
}

static Gitsn_ConnectsToList *init_ConnectsToList_from_ASN(ConnectsToList *src, Dz1Error *errp) {
    Gitsn_ConnectsToList *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_ConnectsToList_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        Gitsn_Connection *_element = NULL;
        pthread_cleanup_push(Gitsn_ConnectsToList_delAndSetNull, (void *)&ret);
        for (int i = 1; i <= (int)src->count; i++) {
            Connection *src_element = (Connection *)ASN1_Get_Node_Index(src, i);
            if (src_element == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if ((_element = init_Connection_from_ASN(src_element, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                pthread_cleanup_push(Gitsn_Connection_delAndSetNull, (void *)&_element);
                if ((*errp = ret->add(ret, _element)).code)
                    ERR_SET_OUT(errp, EFAULT);
                else {
                    _element = NULL;
                    // free(src_element);
                    Dz1Error_set(errp, 0);
                }
                pthread_cleanup_pop(1); // (Gitsn_Connection_delAndSetNull, (void*)&_element);
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_ConnectsToList_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_OverlayLaneList *init_OverlayLaneList_from_ASN(OverlayLaneList *src, Dz1Error *errp) {
    Gitsn_OverlayLaneList *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_OverlayLaneList_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_OverlayLaneList_delAndSetNull, (void *)&ret);
        for (int i = 1; i <= (int)src->count; i++) {
            LaneID *src_element = ASN1_Get_Node_Index(src, i);
            if (src_element == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                LaneID _element = *src_element;
                if ((*errp = ret->add(ret, _element)).code)
                    ERR_SET_OUT(errp, EFAULT);
                else
                    Dz1Error_set(errp, 0);
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_OverlayLaneList_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_GenericLane *init_GenericLane_from_ASN(GenericLane *src, Dz1Error *errp) {
    Gitsn_GenericLane *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_GenericLane_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_GenericLane_delAndSetNull, (void *)&ret);
        if ((ret->laneAttributes = init_LaneAttributes_from_ASN(src->laneAttributes, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else if ((ret->nodeList = init_NodeListXY_from_ASN(src->nodeList, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else {
            ret->laneID = src->laneID;
            if (src->DEF_GenericLane_name) {
                if ((ret->name = Dz1Str_ndup(src->name.asnstring, src->name.nchar, errp)) == NULL)
                    ERR_SET_OUT(errp, EFAULT);
                else
                    Dz1Error_set(errp, 0);
            }

            if (src->DEF_GenericLane_ingressApproach) {
                ret->ingressApproach = src->ingressApproach;
            }

            if (src->DEF_GenericLane_egressApproach) {
                ret->egressApproach = src->egressApproach;
            }
            if (src->DEF_GenericLane_maneuvers) {
                size_t sz = 0;
                sz = (src->maneuvers.numbits + 7) / 8;
                if ((ret->maneuvers = Dz1Calloc(sz, 1, errp)) == NULL)
                    ERR_SET_OUT(errp, EFAULT);
                else if (memcpy(ret->maneuvers, src->maneuvers.data, sz) == NULL)
                    ERR_SET_OUT(errp, EFAULT);
                else
                    Dz1Error_set(errp, 0);
            }
            if (src->DEF_GenericLane_connectsTo) {
                Gitsn_ConnectsToList_delAndSetNull(&ret->connectsTo);
                if ((ret->connectsTo =
                         init_ConnectsToList_from_ASN((ConnectsToList *)&src->connectsTo, errp)) == NULL)
                    ERR_SET_OUT(errp, EFAULT);
                else
                    Dz1Error_set(errp, 0);
            }
            if (src->DEF_GenericLane_overlays) {
                Gitsn_OverlayLaneList_delAndSetNull(&ret->overlays);
                if ((ret->overlays =
                         init_OverlayLaneList_from_ASN((OverlayLaneList *)&src->overlays, errp)) == NULL)
                    ERR_SET_OUT(errp, EFAULT);
                else
                    Dz1Error_set(errp, 0);
            }
            if (src->DEF_GenericLane_regional) {
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_GenericLane_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_LaneList *init_LaneList_from_ASN(LaneList *src, Dz1Error *errp) {
    Gitsn_LaneList *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_LaneList_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        Gitsn_GenericLane *_element = NULL;
        pthread_cleanup_push(Gitsn_LaneList_delAndSetNull, (void *)&ret);
        for (int i = 1; i <= (int)src->count; i++) {
            GenericLane *src_element = (GenericLane *)ASN1_Get_Node_Index(src, i);
            if (src_element == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if ((_element = init_GenericLane_from_ASN(src_element, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                pthread_cleanup_push(Gitsn_GenericLane_delAndSetNull, (void *)&_element);
                if ((*errp = ret->add(ret, _element)).code)
                    ERR_SET_OUT(errp, EFAULT);
                else {
                    _element = NULL;
                    // free(src_element);
                    Dz1Error_set(errp, 0);
                }
                pthread_cleanup_pop(1); // (Gitsn_GenericLane_delAndSetNull, (void*)&_element);
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_LaneList_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_IntersectionGeometry *init_IntersectionGeometry_from_ASN(IntersectionGeometry *src,
                                                                      Dz1Error *errp) {
    Gitsn_IntersectionGeometry *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_IntersectionGeometry_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_IntersectionGeometry_delAndSetNull, (void *)&ret);
        if ((ret->id = init_IntersectionReferenceID_from_ASN(src->id, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else if ((ret->refPoint = init_Position3D_from_ASN(src->refPoint, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else if ((ret->laneSet = init_LaneList_from_ASN((LaneList *)&src->laneSet, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else {
            ret->revision = src->revision;
            if (src->DEF_IntersectionGeometry_name) {
                if ((ret->name = Dz1Str_ndup(src->name.asnstring, src->name.nchar, errp)) == NULL)
                    ERR_SET_OUT(errp, EFAULT);
                else
                    Dz1Error_set(errp, 0);
            }
            if (src->DEF_IntersectionGeometry_laneWidth) {
                ret->laneWidth = src->laneWidth;
            }
            if (src->DEF_IntersectionGeometry_speedLimits) {
                Gitsn_SpeedLimitList_delAndSetNull(&ret->speedLimits);
                if ((ret->speedLimits =
                         init_SpeedLimitList_from_ASN((SpeedLimitList *)&src->speedLimits, errp)) == NULL)
                    ERR_SET_OUT(errp, EFAULT);
                else
                    Dz1Error_set(errp, 0);
            }
            if (src->DEF_IntersectionGeometry_preemptPriorityData) {
                /*if ((ret->preemptPriorityData =
                init_PreemptPriorityList_from_ASN((PreemptPriorityList*)&src->preemptPriorityData, errp)) ==
                NULL) ERR_SET_OUT(errp, EFAULT); else Dz1Error_set(errp, 0);*/
            }
            if (src->DEF_IntersectionGeometry_regional) {
            }
        }

        pthread_cleanup_pop(errp->code); // (Gitsn_IntersectionGeometry_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_IntersectionGeometryList *init_IntersectionGeometryList_from_ASN(IntersectionGeometryList *src,
                                                                              Dz1Error *errp) {
    Gitsn_IntersectionGeometryList *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_IntersectionGeometryList_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        Gitsn_IntersectionGeometry *_element = NULL;
        pthread_cleanup_push(Gitsn_IntersectionGeometryList_delAndSetNull, (void *)&ret);
        for (int i = 1; i <= (int)src->count; i++) {
            IntersectionGeometry *src_element = (IntersectionGeometry *)ASN1_Get_Node_Index(src, i);
            if (src_element == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if ((_element = init_IntersectionGeometry_from_ASN(src_element, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                pthread_cleanup_push(Gitsn_IntersectionGeometry_delAndSetNull, (void *)&_element);
                if ((*errp = ret->add(ret, _element)).code)
                    ERR_SET_OUT(errp, EFAULT);
                else {
                    _element = NULL;
                    // free(src_element);
                    Dz1Error_set(errp, 0);
                }

                pthread_cleanup_pop(1); // (Gitsn_IntersectionGeometry_delAndSetNull, (void*)&_element);
            }
        }

        pthread_cleanup_pop(errp->code); // (Gitsn_IntersectionGeometryList_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_RoadLaneSetList *init_RoadLaneSetList_from_ASN(RoadLaneSetList *src, Dz1Error *errp) {
    Gitsn_RoadLaneSetList *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_RoadLaneSetList_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        Gitsn_GenericLane *_element = NULL;
        pthread_cleanup_push(Gitsn_RoadLaneSetList_delAndSetNull, (void *)&ret);

        for (int i = 1; i <= (int)src->count; i++) {
            GenericLane *src_element = (GenericLane *)ASN1_Get_Node_Index(src, i);
            if (src_element == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if ((_element = init_GenericLane_from_ASN(src_element, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                pthread_cleanup_push(Gitsn_GenericLane_delAndSetNull, (void *)&_element);
                if ((*errp = ret->add(ret, _element)).code)
                    ERR_SET_OUT(errp, EFAULT);
                else {
                    _element = NULL;
                    // free(src_element);
                    Dz1Error_set(errp, 0);
                }
                pthread_cleanup_pop(1); // (Gitsn_GenericLane_delAndSetNull, (void*)&_element);
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_RoadLaneSetList_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_RoadSegment *init_RoadSegment_from_ASN(RoadSegment *src, Dz1Error *errp) {
    Gitsn_RoadSegment *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_RoadSegment_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_RoadSegment_delAndSetNull, (void *)&ret);
        if ((ret->id = init_RoadSegmentReferenceID_from_ASN(src->id, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else if ((ret->refPoint = init_Position3D_from_ASN(src->refPoint, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else if ((ret->roadLaneSet =
                      init_RoadLaneSetList_from_ASN((RoadLaneSetList *)&src->roadLaneSet, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else {
            ret->revision = src->revision;

            if (src->DEF_RoadSegment_name) {
                if ((ret->name = Dz1Str_ndup(src->name.asnstring, src->name.nchar, errp)) == NULL)
                    ERR_SET_OUT(errp, EFAULT);
                else
                    Dz1Error_set(errp, 0);
            }
            if (src->DEF_RoadSegment_laneWidth) {
                ret->laneWidth = src->laneWidth;
            }
            if (src->DEF_RoadSegment_speedLimits) {
                Gitsn_SpeedLimitList_delAndSetNull(&ret->speedLimits);
                if ((ret->speedLimits =
                         init_SpeedLimitList_from_ASN((SpeedLimitList *)&src->speedLimits, errp)) == NULL)
                    ERR_SET_OUT(errp, EFAULT);
                else
                    Dz1Error_set(errp, 0);
            }
            if (src->DEF_RoadSegment_regional) {
            }
        }

        pthread_cleanup_pop(errp->code); // (Gitsn_RoadSegment_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_RoadSegmentList *init_RoadSegmentList_from_ASN(RoadSegmentList *src, Dz1Error *errp) {
    Gitsn_RoadSegmentList *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_RoadSegmentList_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        Gitsn_RoadSegment *_element = NULL;
        pthread_cleanup_push(Gitsn_RoadSegmentList_delAndSetNull, (void *)&ret);
        for (int i = 1; i <= (int)src->count; i++) {
            RoadSegment *src_element = (RoadSegment *)ASN1_Get_Node_Index(src, i);
            if (src_element == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if ((_element = init_RoadSegment_from_ASN(src_element, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                pthread_cleanup_push(Gitsn_RoadSegment_delAndSetNull, (void *)&_element);
                if ((*errp = ret->add(ret, _element)).code)
                    ERR_SET_OUT(errp, EFAULT);
                else {
                    _element = NULL;
                    // free(src_element);
                    Dz1Error_set(errp, 0);
                }
                pthread_cleanup_pop(1); // (Gitsn_RoadSegment_delAndSetNull, (void*)&_element);
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_RoadSegmentList_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_DataParameters *init_DataParameters_from_ASN(DataParameters *src, Dz1Error *errp) {
    Gitsn_DataParameters *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_DataParameters_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_DataParameters_delAndSetNull, (void *)&ret);
        if (src->DEF_DataParameters_processMethod) {
            if ((ret->processMethod =
                     Dz1Str_ndup(src->processMethod.asnstring, src->processMethod.nchar, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else
                Dz1Error_set(errp, 0);
        }
        if (src->DEF_DataParameters_processAgency) {
            if ((ret->processAgency =
                     Dz1Str_ndup(src->processAgency.asnstring, src->processAgency.nchar, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else
                Dz1Error_set(errp, 0);
        }
        if (src->DEF_DataParameters_lastCheckedDate) {
            if ((ret->lastCheckedDate =
                     Dz1Str_ndup(src->lastCheckedDate.asnstring, src->lastCheckedDate.nchar, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else
                Dz1Error_set(errp, 0);
        }
        if (src->DEF_DataParameters_geoidUsed) {
            if ((ret->geoidUsed = Dz1Str_ndup(src->geoidUsed.asnstring, src->geoidUsed.nchar, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else
                Dz1Error_set(errp, 0);
        }

        pthread_cleanup_pop(errp->code); // (Gitsn_DataParameters_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_RestrictionUserType *init_RestrictionUserType_from_ASN(RestrictionUserType *src,
                                                                    Dz1Error *errp) {
    Gitsn_RestrictionUserType *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_RestrictionUserType_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_RestrictionUserType_delAndSetNull, (void *)&ret);

        switch (src->M) {
        case DEF_RestrictionUserType_basicType:
            ret->x.basicType = (Gitsn_RestrictionAppliesTo)src->elements.basicType;
            ret->present = Gitsn_RestrictionUserTypePresent_basicType;
            Dz1Error_set(errp, 0);
            break;
        case DEF_RestrictionUserType_regional:
            break;
        default:
            ERR_SET_OUT(errp, EPERM);
            break;
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_RestrictionUserType_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_RestrictionUserTypeList *init_RestrictionUserTypeList_from_ASN(RestrictionUserTypeList *src,
                                                                            Dz1Error *errp) {
    Gitsn_RestrictionUserTypeList *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_RestrictionUserTypeList_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        Gitsn_RestrictionUserType *_element = NULL;
        pthread_cleanup_push(Gitsn_RestrictionUserTypeList_delAndSetNull, (void *)&ret);
        for (int i = 1; i <= (int)src->count; i++) {
            RestrictionUserType *src_element = (RestrictionUserType *)ASN1_Get_Node_Index(src, i);
            if (src_element == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if ((_element = init_RestrictionUserType_from_ASN(src_element, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                pthread_cleanup_push(Gitsn_RestrictionUserType_delAndSetNull, (void *)&_element);
                if ((*errp = ret->add(ret, _element)).code)
                    ERR_SET_OUT(errp, EFAULT);
                else {
                    _element = NULL;
                    // free(src_element);
                    Dz1Error_set(errp, 0);
                }
                pthread_cleanup_pop(1); // (Gitsn_RestrictionUserType_delAndSetNull, (void*)&_element);
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_RestrictionUserTypeList_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_RestrictionClassAssignment *
init_RestrictionClassAssignment_from_ASN(RestrictionClassAssignment *src, Dz1Error *errp) {
    Gitsn_RestrictionClassAssignment *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_RestrictionClassAssignment_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_RestrictionClassAssignment_delAndSetNull, (void *)&ret);
        if ((ret->users =
                 init_RestrictionUserTypeList_from_ASN((RestrictionUserTypeList *)&src->users, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else {
            ret->id = src->id;
            Dz1Error_set(errp, 0);
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_RestrictionClassAssignment_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_RestrictionClassList *init_RestrictionClassList_from_ASN(RestrictionClassList *src,
                                                                      Dz1Error *errp) {
    Gitsn_RestrictionClassList *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_RestrictionClassList_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        Gitsn_RestrictionClassAssignment *_element = NULL;
        pthread_cleanup_push(Gitsn_RestrictionClassList_delAndSetNull, (void *)&ret);
        for (int i = 1; i <= (int)src->count; i++) {
            RestrictionClassAssignment *src_element =
                (RestrictionClassAssignment *)ASN1_Get_Node_Index(src, i);
            if (src_element == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if ((_element = init_RestrictionClassAssignment_from_ASN(src_element, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                pthread_cleanup_push(Gitsn_RestrictionClassAssignment_delAndSetNull, (void *)&_element);
                if ((*errp = ret->add(ret, _element)).code)
                    ERR_SET_OUT(errp, EFAULT);
                else {
                    _element = NULL;
                    // free(src_element);
                    Dz1Error_set(errp, 0);
                }

                pthread_cleanup_pop(1); // (Gitsn_RestrictionClassAssignment_delAndSetNull, (void*)&_element);
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_RestrictionClassList_delAndSetNull, (void*)&ret);
    }
    return ret;
}

bool_t DatexMapFromASN(MapData *src, Gitsn_MapData *dst, Dz1Error *err) {
    DZ1_ERROR_SAFE_PTR(errp, err);
    if (src == NULL || dst == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        dst->msgIssueRevision = src->msgIssueRevision;

        if (src->DEF_MapData_timeStamp) {
            dst->timeStamp = src->timeStamp;
        }
        if (src->DEF_MapData_layerType) {
            dst->layerType = (Gitsn_LayerType)src->layerType;
        }
        if (src->DEF_MapData_layerID) {
            dst->layerID = src->layerID;
        }
        if (src->DEF_MapData_intersections) {
            if ((dst->intersections = init_IntersectionGeometryList_from_ASN(
                     (IntersectionGeometryList *)&src->intersections, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else
                Dz1Error_set(errp, 0);
        }
        if (src->DEF_MapData_roadSegments) {
            if ((dst->roadSegments =
                     init_RoadSegmentList_from_ASN((RoadSegmentList *)&src->roadSegments, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else
                Dz1Error_set(errp, 0);
        }
        if (src->DEF_MapData_dataParameters) {
            if ((dst->dataParameters = init_DataParameters_from_ASN(src->dataParameters, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else
                Dz1Error_set(errp, 0);
        }
        if (src->DEF_MapData_restrictionList) {
            if ((dst->restrictionList = init_RestrictionClassList_from_ASN(
                     (RestrictionClassList *)&src->restrictionList, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else
                Dz1Error_set(errp, 0);
        }
        if (src->DEF_MapData_regional) {
        }
    }

    return ERR_IS_SUCCESS(errp);
}

static Gitsn_IntersectionReferenceID *init_IntersectionReferenceID_from_ASN(IntersectionReferenceID *src,
                                                                            Dz1Error *errp) {
    Gitsn_IntersectionReferenceID *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_IntersectionReferenceID_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_IntersectionReferenceID_delAndSetNull, (void *)&ret);
        ret->region = src->region;
        ret->id = src->id;
        Dz1Error_set(errp, 0);
        pthread_cleanup_pop(errp->code); // (Gitsn_IntersectionReferenceID_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_Position3D *init_Position3D_from_ASN(Position3D *src, Dz1Error *errp) {
    Gitsn_Position3D *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_Position3D_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_Position3D_delAndSetNull, (void *)&ret);
        ret->lat = src->lat;
        ret->lon = src->lon;
        if (src->DEF_Position3D_elevation) {
            ret->elevation = src->elevation;
        }
        if (src->DEF_Position3D_regional) {
        }
        Dz1Error_set(errp, 0);
        pthread_cleanup_pop(errp->code); // (Gitsn_Position3D_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_RoadSignID *init_RoadSignID_from_ASN(RoadSignID *src, Dz1Error *errp) {
    Gitsn_RoadSignID *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_RoadSignID_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_RoadSignID_delAndSetNull, (void *)&ret);
        if ((ret->position = init_Position3D_from_ASN(src->position, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else {
            if ((ret->viewAngle = Dz1Calloc(2, 1, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if (memcpy(ret->viewAngle, src->viewAngle.data, 2) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            Dz1Error_set(errp, 0);
        }
        if (src->DEF_RoadSignID_mutcdCode) {
            ret->mutcdCode = (Gitsn_MUTCDCode)src->mutcdCode;
        }
        if (src->DEF_RoadSignID_crc) {
            if ((ret->crc = Dz1Str_ndup(src->crc.data, 2, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else
                Dz1Error_set(errp, 0);
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_RoadSignID_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_TravelerDataFrame_msgId *init_TravelerDataFrame_msgId_from_ASN(TravelerDataFrame_msgId *src,
                                                                            Dz1Error *errp) {
    Gitsn_TravelerDataFrame_msgId *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_TravelerDataFrame_msgId_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_TravelerDataFrame_msgId_delAndSetNull, (void *)&ret);
        switch (src->M) {
        case DEF_TravelerDataFrame_msgId_furtherInfoID: {
            u8_t *dp = src->elements.furtherInfoID.data;
            ret->x.furtherInfoID = 0;
            ret->x.furtherInfoID = (ret->x.furtherInfoID << 8) | (u16_t)(*dp & 0xFF);
            dp++;
            ret->x.furtherInfoID = (ret->x.furtherInfoID << 8) | (u16_t)(*dp & 0xFF);
            dp++;

            ret->present = Gitsn_TravelerDataFrame_msgIdPresent_furtherInfoID;
            Dz1Error_set(errp, 0);
        } break;
        case DEF_TravelerDataFrame_msgId_roadSignID:
            if ((ret->x.roadSignID =
                     init_RoadSignID_from_ASN(src->elements.roadSignID, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_TravelerDataFrame_msgIdPresent_roadSignID;
                Dz1Error_set(errp, 0);
            }
            break;
        default:
            ERR_SET_OUT(errp, EPERM);
            break;
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_TravelerDataFrame_msgId_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_RoadSegmentReferenceID *init_RoadSegmentReferenceID_from_ASN(RoadSegmentReferenceID *src,
                                                                          Dz1Error *errp) {
    Gitsn_RoadSegmentReferenceID *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_RoadSegmentReferenceID_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_RoadSegmentReferenceID_delAndSetNull, (void *)&ret);
        ret->id = src->id;
        if (src->DEF_RoadSegmentReferenceID_region) {
            ret->region = src->region;
        }
        Dz1Error_set(errp, 0);
        pthread_cleanup_pop(errp->code); // (Gitsn_RoadSegmentReferenceID_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_NodeOffsetPointXY *init_NodeOffsetPointXY_from_ASN(NodeOffsetPointXY *src, Dz1Error *errp) {
    Gitsn_NodeOffsetPointXY *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_NodeOffsetPointXY_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_NodeOffsetPointXY_delAndSetNull, (void *)&ret);
        switch (src->M) {
        case DEF_NodeOffsetPointXY_node_XY1:
            if ((ret->x.node_XY1 = Gitsn_Node_XY_20b_new(src->elements.node_XY1->x, src->elements.node_XY1->y,
                                                         errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_NodeOffsetPointXYPresent_node_XY1;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_NodeOffsetPointXY_node_XY2:
            if ((ret->x.node_XY2 = Gitsn_Node_XY_22b_new(src->elements.node_XY2->x, src->elements.node_XY2->y,
                                                         errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_NodeOffsetPointXYPresent_node_XY2;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_NodeOffsetPointXY_node_XY3:
            if ((ret->x.node_XY3 = Gitsn_Node_XY_24b_new(src->elements.node_XY3->x, src->elements.node_XY3->y,
                                                         errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_NodeOffsetPointXYPresent_node_XY3;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_NodeOffsetPointXY_node_XY4:
            if ((ret->x.node_XY4 = Gitsn_Node_XY_26b_new(src->elements.node_XY4->x, src->elements.node_XY4->y,
                                                         errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_NodeOffsetPointXYPresent_node_XY4;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_NodeOffsetPointXY_node_XY5:
            if ((ret->x.node_XY5 = Gitsn_Node_XY_28b_new(src->elements.node_XY5->x, src->elements.node_XY5->y,
                                                         errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_NodeOffsetPointXYPresent_node_XY5;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_NodeOffsetPointXY_node_XY6:
            if ((ret->x.node_XY6 = Gitsn_Node_XY_32b_new(src->elements.node_XY6->x, src->elements.node_XY6->y,
                                                         errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_NodeOffsetPointXYPresent_node_XY6;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_NodeOffsetPointXY_node_LatLon:
            if ((ret->x.node_LatLon = Gitsn_Node_LLmD_64b_new(src->elements.node_LatLon->lon,
                                                              src->elements.node_LatLon->lat, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_NodeOffsetPointXYPresent_node_LatLon;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_NodeOffsetPointXY_regional: {
        } break;
        default:
            ERR_SET_OUT(errp, EPERM);
            break;
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_NodeOffsetPointXY_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_NodeAttributeXYList *init_NodeAttributeXYList_from_ASN(NodeAttributeXYList *src,
                                                                    Dz1Error *errp) {
    Gitsn_NodeAttributeXYList *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_NodeAttributeXYList_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_NodeAttributeXYList_delAndSetNull, (void *)&ret);
        for (int i = 1; i <= (int)src->count; i++) {
            NodeAttributeXY *src_element = (NodeAttributeXY *)ASN1_Get_Node_Index(src, i);
            if (src_element == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                Gitsn_NodeAttributeXY _element = (Gitsn_NodeAttributeXY)*src_element;
                if ((*errp = ret->add(ret, _element)).code)
                    ERR_SET_OUT(errp, EFAULT);
                else {
                    // free(src_element);
                    Dz1Error_set(errp, 0);
                }
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_NodeAttributeXYList_delAndSetNull, (void*)&ret);
    }

    return ret;
}

static Gitsn_SegmentAttributeXYList *init_SegmentAttributeXYList_from_ASN(SegmentAttributeXYList *src,
                                                                          Dz1Error *errp) {
    Gitsn_SegmentAttributeXYList *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_SegmentAttributeXYList_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        Gitsn_SegmentAttributeXY _element;
        pthread_cleanup_push(Gitsn_SegmentAttributeXYList_delAndSetNull, (void *)&ret);
        for (int i = 1; i <= (int)src->count; i++) {
            SegmentAttributeXY *src_element = (SegmentAttributeXY *)ASN1_Get_Node_Index(src, i);
            if (src_element == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                _element = (Gitsn_SegmentAttributeXY)*src_element;
                if ((*errp = ret->add(ret, _element)).code)
                    ERR_SET_OUT(errp, EFAULT);
                else
                    Dz1Error_set(errp, 0);
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_SegmentAttributeXYList_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_RegulatorySpeedLimit *init_RegulatorySpeedLimit_from_ASN(RegulatorySpeedLimit *src,
                                                                      Dz1Error *errp) {
    Gitsn_RegulatorySpeedLimit *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_RegulatorySpeedLimit_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_RegulatorySpeedLimit_delAndSetNull, (void *)&ret);
        ret->type = (Gitsn_SpeedLimitType)src->type;
        ret->speed = src->speed;
        Dz1Error_set(errp, 0);
        pthread_cleanup_pop(errp->code); // (Gitsn_RegulatorySpeedLimit_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_SpeedLimitList *init_SpeedLimitList_from_ASN(SpeedLimitList *src, Dz1Error *errp) {
    Gitsn_SpeedLimitList *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_SpeedLimitList_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        Gitsn_RegulatorySpeedLimit *_element = NULL;
        pthread_cleanup_push(Gitsn_SpeedLimitList_delAndSetNull, (void *)&ret);
        for (int i = 1; i <= (int)src->count; i++) {
            RegulatorySpeedLimit *src_element = (RegulatorySpeedLimit *)ASN1_Get_Node_Index(src, i);
            if (src_element == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if ((_element = init_RegulatorySpeedLimit_from_ASN(src_element, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                pthread_cleanup_push(Gitsn_RegulatorySpeedLimit_delAndSetNull, (void *)&_element);
                if ((*errp = ret->add(ret, _element)).code)
                    ERR_SET_OUT(errp, EFAULT);
                else {
                    _element = NULL;
                    // free(src_element);
                    Dz1Error_set(errp, 0);
                }
                pthread_cleanup_pop(1); // (Gitsn_RegulatorySpeedLimit_delAndSetNull, (void*)&_element);
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_SpeedLimitList_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_LaneDataAttribute *init_LaneDataAttribute_from_ASN(LaneDataAttribute *src, Dz1Error *errp) {
    Gitsn_LaneDataAttribute *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_LaneDataAttribute_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_LaneDataAttribute_delAndSetNull, (void *)&ret);
        switch (src->M) {
        case DEF_LaneDataAttribute_pathEndPointAngle:
            ret->x.pathEndPointAngle = src->elements.pathEndPointAngle;
            ret->present = Gitsn_LaneDataAttributePresent_pathEndPointAngle;
            Dz1Error_set(errp, 0);
            break;
        case DEF_LaneDataAttribute_laneCrownPointCenter:
            ret->x.laneCrownPointCenter = src->elements.laneCrownPointCenter;
            ret->present = Gitsn_LaneDataAttributePresent_laneCrownPointCenter;
            Dz1Error_set(errp, 0);
            break;
        case DEF_LaneDataAttribute_laneCrownPointLeft:
            ret->x.laneCrownPointLeft = src->elements.laneCrownPointLeft;
            ret->present = Gitsn_LaneDataAttributePresent_laneCrownPointLeft;
            Dz1Error_set(errp, 0);
            break;
        case DEF_LaneDataAttribute_laneCrownPointRight:
            ret->x.laneCrownPointRight = src->elements.laneCrownPointRight;
            ret->present = Gitsn_LaneDataAttributePresent_laneCrownPointRight;
            Dz1Error_set(errp, 0);
            break;
        case DEF_LaneDataAttribute_laneAngle:
            ret->x.laneAngle = src->elements.laneAngle;
            ret->present = Gitsn_LaneDataAttributePresent_laneAngle;
            Dz1Error_set(errp, 0);
            break;
        case DEF_LaneDataAttribute_speedLimits:
            if ((ret->x.speedLimits = init_SpeedLimitList_from_ASN(
                     (SpeedLimitList *)&src->elements.speedLimits, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_LaneDataAttributePresent_speedLimits;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_LaneDataAttribute_regional:
            break;
        default:
            ERR_SET_OUT(errp, EPERM);
            break;
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_LaneDataAttribute_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_LaneDataAttributeList *init_LaneDataAttributeList_from_ASN(LaneDataAttributeList *src,
                                                                        Dz1Error *errp) {
    Gitsn_LaneDataAttributeList *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_LaneDataAttributeList_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        Gitsn_LaneDataAttribute *_element = NULL;
        pthread_cleanup_push(Gitsn_LaneDataAttributeList_delAndSetNull, (void *)&ret);
        for (int i = 1; i <= (int)src->count; i++) {
            LaneDataAttribute *src_element = (LaneDataAttribute *)ASN1_Get_Node_Index(src, i);
            if (src_element == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if ((_element = init_LaneDataAttribute_from_ASN(src_element, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                pthread_cleanup_push(Gitsn_LaneDataAttribute_delAndSetNull, (void *)&_element);
                if ((*errp = ret->add(ret, _element)).code)
                    ERR_SET_OUT(errp, EFAULT);
                else {
                    _element = NULL;
                    // free(src_element);
                    Dz1Error_set(errp, 0);
                }
                pthread_cleanup_pop(1); // (Gitsn_LaneDataAttribute_delAndSetNull, (void*)&_element);
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_LaneDataAttributeList_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_NodeAttributeSetXY *init_NodeAttributeSetXY_from_ASN(NodeAttributeSetXY *src, Dz1Error *errp) {
    Gitsn_NodeAttributeSetXY *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_NodeAttributeSetXY_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_NodeAttributeSetXY_delAndSetNull, (void *)&ret);
        if (src->DEF_NodeAttributeSetXY_localNode) {
            Gitsn_NodeAttributeXYList_delAndSetNull(&ret->localNode);
            if ((ret->localNode =
                     init_NodeAttributeXYList_from_ASN((NodeAttributeXYList *)&src->localNode, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else
                Dz1Error_set(errp, 0);
        }
        if (src->DEF_NodeAttributeSetXY_disabled) {
            Gitsn_SegmentAttributeXYList_delAndSetNull(&ret->disabled);
            if ((ret->disabled = init_SegmentAttributeXYList_from_ASN(
                     (SegmentAttributeXYList *)&src->disabled, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else
                Dz1Error_set(errp, 0);
        }
        if (src->DEF_NodeAttributeSetXY_enabled) {
            Gitsn_SegmentAttributeXYList_delAndSetNull(&ret->enabled);
            if ((ret->enabled = init_SegmentAttributeXYList_from_ASN((SegmentAttributeXYList *)&src->enabled,
                                                                     errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else
                Dz1Error_set(errp, 0);
        }
        if (src->DEF_NodeAttributeSetXY_data) {
            Gitsn_LaneDataAttributeList_delAndSetNull(&ret->data);
            if ((ret->data =
                     init_LaneDataAttributeList_from_ASN((LaneDataAttributeList *)&src->data, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else
                Dz1Error_set(errp, 0);
        }
        if (src->DEF_NodeAttributeSetXY_dWidth) {
            ret->dWidth = src->dWidth;
        }
        if (src->DEF_NodeAttributeSetXY_dElevation) {
            ret->dElevation = src->dElevation;
        }
        if (src->DEF_NodeAttributeSetXY_regional) {
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_NodeAttributeSetXY_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_NodeXY *init_NodeXY_from_ASN(NodeXY *src, Dz1Error *errp) {
    Gitsn_NodeXY *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_NodeXY_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_NodeXY_delAndSetNull, (void *)&ret);
        if ((ret->delta = init_NodeOffsetPointXY_from_ASN(src->delta, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else {
            if (src->DEF_NodeXY_attributes) {
                if ((ret->attributes = init_NodeAttributeSetXY_from_ASN(src->attributes, errp)) == NULL)
                    ERR_SET_OUT(errp, EFAULT);
                else
                    Dz1Error_set(errp, 0);
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_NodeXY_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_NodeSetXY *init_NodeSetXY_from_ASN(NodeSetXY *src, Dz1Error *errp) {
    Gitsn_NodeSetXY *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_NodeSetXY_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        Gitsn_NodeXY *_element = NULL;
        pthread_cleanup_push(Gitsn_NodeSetXY_delAndSetNull, (void *)&ret);
        for (int i = 1; i <= (int)src->count; i++) {
            NodeXY *src_element = (NodeXY *)ASN1_Get_Node_Index(src, i);
            if (src_element == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if ((_element = init_NodeXY_from_ASN(src_element, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                pthread_cleanup_push(Gitsn_NodeXY_delAndSetNull, (void *)&_element);
                if ((*errp = ret->add(ret, _element)).code)
                    ERR_SET_OUT(errp, EFAULT);
                else {
                    _element = NULL;
                    // free(src_element);
                    Dz1Error_set(errp, 0);
                }
                pthread_cleanup_pop(1);
                (Gitsn_NodeXY_delAndSetNull, (void *)&_element);
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_NodeSetXY_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_ComputedLane_offsetXaxis *init_ComputedLane_offsetXaxis_from_ASN(ComputedLane_offsetXaxis *src,
                                                                              Dz1Error *errp) {
    Gitsn_ComputedLane_offsetXaxis *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_ComputedLane_offsetXaxis_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_ComputedLane_offsetXaxis_delAndSetNull, (void *)&ret);
        switch (src->M) {
        case DEF_ComputedLane_offsetXaxis_small:
            ret->x.small = src->elements.small;
            ret->present = Gitsn_ComputedLane_offsetXaxisPresent_small;
            Dz1Error_set(errp, 0);
            break;
        case DEF_ComputedLane_offsetXaxis_large:
            ret->x.large = src->elements.large;
            ret->present = Gitsn_ComputedLane_offsetXaxisPresent_large;
            Dz1Error_set(errp, 0);
            break;
        default:
            ERR_SET_OUT(errp, EPERM);
            break;
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_ComputedLane_offsetXaxis_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_ComputedLane_offsetYaxis *init_ComputedLane_offsetYaxis_from_ASN(ComputedLane_offsetYaxis *src,
                                                                              Dz1Error *errp) {
    Gitsn_ComputedLane_offsetYaxis *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_ComputedLane_offsetYaxis_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_ComputedLane_offsetYaxis_delAndSetNull, (void *)&ret);
        switch (src->M) {
        case DEF_ComputedLane_offsetYaxis_small:
            ret->x.small = src->elements.small;
            ret->present = Gitsn_ComputedLane_offsetYaxisPresent_small;
            Dz1Error_set(errp, 0);
            break;
        case DEF_ComputedLane_offsetYaxis_large:
            ret->x.large = src->elements.large;
            ret->present = Gitsn_ComputedLane_offsetYaxisPresent_large;
            Dz1Error_set(errp, 0);
            break;
        default:
            ERR_SET_OUT(errp, EPERM);
            break;
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_ComputedLane_offsetYaxis_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_ComputedLane *init_ComputedLane_from_ASN(ComputedLane *src, Dz1Error *errp) {
    Gitsn_ComputedLane *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_ComputedLane_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_ComputedLane_delAndSetNull, (void *)&ret);
        ret->referenceLaneId = src->referenceLaneId;
        if ((ret->offsetXaxis = init_ComputedLane_offsetXaxis_from_ASN(src->offsetXaxis, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else if ((ret->offsetYaxis = init_ComputedLane_offsetYaxis_from_ASN(src->offsetYaxis, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else {
            if (src->DEF_ComputedLane_rotateXY) {
                ret->rotateXY = src->rotateXY;
            }
            if (src->DEF_ComputedLane_scaleXaxis) {
                ret->scaleXaxis = src->scaleXaxis;
            }
            if (src->DEF_ComputedLane_scaleYaxis) {
                ret->scaleYaxis = src->scaleYaxis;
            }
            if (src->DEF_ComputedLane_regional) {
            }
            Dz1Error_set(errp, 0);
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_ComputedLane_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_NodeListXY *init_NodeListXY_from_ASN(NodeListXY *src, Dz1Error *errp) {
    Gitsn_NodeListXY *ret = NULL;

    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_NodeListXY_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_NodeListXY_delAndSetNull, (void *)&ret);
        switch (src->M) {
        case DEF_NodeListXY_nodes:
            if ((ret->x.nodes = init_NodeSetXY_from_ASN((NodeSetXY *)&src->elements.nodes, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_NodeListXYPresent_nodes;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_NodeListXY_computed:
            if ((ret->x.computed = init_ComputedLane_from_ASN(src->elements.computed, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_NodeListXYPresent_computed;
                Dz1Error_set(errp, 0);
            }
            break;
        default:
            ERR_SET_OUT(errp, EPERM);
            break;
        }

        pthread_cleanup_pop(errp->code); // (Gitsn_NodeListXY_delAndSetNull, (void*)&ret);
    }

    return ret;
}

static Gitsn_NodeOffsetPointLL *init_NodeOffsetPointLL_from_ASN(NodeOffsetPointLL *src, Dz1Error *errp) {
    Gitsn_NodeOffsetPointLL *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_NodeOffsetPointLL_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_NodeOffsetPointLL_delAndSetNull, (void *)&ret);
        switch (src->M) {
        case DEF_NodeOffsetPointLL_node_LL1:
            if ((ret->x.node_LL1 = Gitsn_Node_LL_24B_new(src->elements.node_LL1->lon,
                                                         src->elements.node_LL1->lat, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_NodeOffsetPointLLPresent_node_LL1;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_NodeOffsetPointLL_node_LL2:
            if ((ret->x.node_LL2 = Gitsn_Node_LL_28B_new(src->elements.node_LL2->lon,
                                                         src->elements.node_LL2->lat, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_NodeOffsetPointLLPresent_node_LL2;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_NodeOffsetPointLL_node_LL3:
            if ((ret->x.node_LL3 = Gitsn_Node_LL_32B_new(src->elements.node_LL3->lon,
                                                         src->elements.node_LL3->lat, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_NodeOffsetPointLLPresent_node_LL3;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_NodeOffsetPointLL_node_LL4:
            if ((ret->x.node_LL4 = Gitsn_Node_LL_36B_new(src->elements.node_LL4->lon,
                                                         src->elements.node_LL4->lat, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_NodeOffsetPointLLPresent_node_LL4;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_NodeOffsetPointLL_node_LL5:
            if ((ret->x.node_LL5 = Gitsn_Node_LL_44B_new(src->elements.node_LL5->lon,
                                                         src->elements.node_LL5->lat, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_NodeOffsetPointLLPresent_node_LL5;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_NodeOffsetPointLL_node_LL6:
            if ((ret->x.node_LL6 = Gitsn_Node_LL_48B_new(src->elements.node_LL6->lon,
                                                         src->elements.node_LL6->lat, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_NodeOffsetPointLLPresent_node_LL6;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_NodeOffsetPointLL_node_LatLon:
            if ((ret->x.node_LatLon = Gitsn_Node_LLmD_64b_new(src->elements.node_LatLon->lon,
                                                              src->elements.node_LatLon->lat, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_NodeOffsetPointLLPresent_node_LatLon;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_NodeOffsetPointLL_regional: {
        } break;
        default:
            ERR_SET_OUT(errp, EPERM);
            break;
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_NodeOffsetPointLL_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_NodeAttributeLLList *init_NodeAttributeLLList_from_ASN(NodeAttributeLLList *src,
                                                                    Dz1Error *errp) {
    Gitsn_NodeAttributeLLList *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_NodeAttributeLLList_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_NodeAttributeLLList_delAndSetNull, (void *)&ret);
        for (int i = 1; i <= (int)src->count; i++) {
            NodeAttributeLL *src_element = (NodeAttributeLL *)ASN1_Get_Node_Index(src, i);
            if (src_element == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                Gitsn_NodeAttributeLL _element = (Gitsn_NodeAttributeLL)*src_element;
                if ((*errp = ret->add(ret, _element)).code)
                    ERR_SET_OUT(errp, EFAULT);
                else {
                    // free(src_element);
                    Dz1Error_set(errp, 0);
                }
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_NodeAttributeLLList_delAndSetNull, (void*)&ret);
    }

    return ret;
}

static Gitsn_SegmentAttributeLLList *init_SegmentAttributeLLList_from_ASN(SegmentAttributeLLList *src,
                                                                          Dz1Error *errp) {
    Gitsn_SegmentAttributeLLList *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_SegmentAttributeLLList_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        Gitsn_SegmentAttributeLL _element;
        pthread_cleanup_push(Gitsn_SegmentAttributeLLList_delAndSetNull, (void *)&ret);
        for (int i = 1; i <= (int)src->count; i++) {
            SegmentAttributeLL *src_element = (SegmentAttributeLL *)ASN1_Get_Node_Index(src, i);
            if (src_element == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                _element = (Gitsn_SegmentAttributeLL)*src_element;
                if ((*errp = ret->add(ret, _element)).code)
                    ERR_SET_OUT(errp, EFAULT);
                else
                    Dz1Error_set(errp, 0);
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_SegmentAttributeLLList_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_NodeAttributeSetLL *init_NodeAttributeSetLL_from_ASN(NodeAttributeSetLL *src, Dz1Error *errp) {
    Gitsn_NodeAttributeSetLL *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_NodeAttributeSetLL_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_NodeAttributeSetLL_delAndSetNull, (void *)&ret);
        if (src->DEF_NodeAttributeSetLL_localNode) {
            Gitsn_NodeAttributeXYList_delAndSetNull(&ret->localNode);
            if ((ret->localNode =
                     init_NodeAttributeLLList_from_ASN((NodeAttributeLLList *)&src->localNode, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else
                Dz1Error_set(errp, 0);
        }
        if (src->DEF_NodeAttributeSetLL_disabled) {
            Gitsn_SegmentAttributeXYList_delAndSetNull(&ret->disabled);
            if ((ret->disabled = init_SegmentAttributeLLList_from_ASN(
                     (SegmentAttributeLLList *)&src->disabled, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else
                Dz1Error_set(errp, 0);
        }
        if (src->DEF_NodeAttributeSetLL_enabled) {
            Gitsn_SegmentAttributeXYList_delAndSetNull(&ret->enabled);
            if ((ret->enabled = init_SegmentAttributeLLList_from_ASN((SegmentAttributeLLList *)&src->enabled,
                                                                     errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else
                Dz1Error_set(errp, 0);
        }
        if (src->DEF_NodeAttributeSetLL_data) {
            Gitsn_LaneDataAttributeList_delAndSetNull(&ret->data);
            if ((ret->data =
                     init_LaneDataAttributeList_from_ASN((LaneDataAttributeList *)&src->data, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else
                Dz1Error_set(errp, 0);
        }
        if (src->DEF_NodeAttributeSetLL_dWidth) {
            ret->dWidth = src->dWidth;
        }
        if (src->DEF_NodeAttributeSetLL_dElevation) {
            ret->dElevation = src->dElevation;
        }
        if (src->DEF_NodeAttributeSetLL_regional) {
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_NodeAttributeSetLL_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_NodeLL *init_NodeLL_from_ASN(NodeLL *src, Dz1Error *errp) {
    Gitsn_NodeLL *ret = NULL;

    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_NodeLL_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_NodeLL_delAndSetNull, (void *)&ret);
        // gm
        if ((ret->delta = init_NodeOffsetPointLL_from_ASN(src->delta, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else {
            if (src->DEF_NodeLL_attributes) {
                if ((ret->attributes = init_NodeAttributeSetLL_from_ASN(src->attributes, errp)) == NULL)
                    ERR_SET_OUT(errp, EFAULT);
                else
                    Dz1Error_set(errp, 0);
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_NodeLL_delAndSetNull, (void*)&ret);
    }

    return ret;
}

static Gitsn_NodeSetLL *init_NodeSetLL_from_ASN(NodeSetLL *src, Dz1Error *errp) {
    Gitsn_NodeSetLL *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_NodeSetLL_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        Gitsn_NodeLL *_element = NULL;
        pthread_cleanup_push(Gitsn_NodeSetLL_delAndSetNull, (void *)&ret);
        for (int i = 1; i <= (int)src->count; i++) {
            NodeLL *src_element = (NodeLL *)ASN1_Get_Node_Index(src, i);
            if (src_element == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if ((_element = init_NodeLL_from_ASN(src_element, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                pthread_cleanup_push(Gitsn_NodeLL_delAndSetNull, (void *)&_element);
                if ((*errp = ret->add(ret, _element)).code)
                    ERR_SET_OUT(errp, EFAULT);
                else {
                    _element = NULL;
                    // free(src_element);
                    Dz1Error_set(errp, 0);
                }

                pthread_cleanup_pop(1); // (Gitsn_NodeLL_delAndSetNull, (void*)&_element);
            }
        }

        pthread_cleanup_pop(errp->code); // (Gitsn_NodeSetLL_delAndSetNull, (void*)&ret);
    }

    return ret;
}

static Gitsn_NodeListLL *init_NodeListLL_from_ASN(NodeListLL *src, Dz1Error *errp) {
    Gitsn_NodeListLL *ret = NULL;

    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_NodeListLL_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_NodeListLL_delAndSetNull, (void *)&ret);
        switch (src->M) {
        case DEF_NodeListLL_nodes:
            if ((ret->x.nodes = init_NodeSetLL_from_ASN((NodeSetLL *)&src->elements.nodes, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_NodeListLLPresent_nodes;
                Dz1Error_set(errp, 0);
            }
            break;
        default:
            ERR_SET_OUT(errp, EPERM);
            break;
        }

        pthread_cleanup_pop(errp->code); // (Gitsn_NodeListLL_delAndSetNull, (void*)&ret);
    }

    return ret;
}

static Gitsn_OffsetSystem_offset *init_OffsetSystem_offset_from_ASN(OffsetSystem_offset *src,
                                                                    Dz1Error *errp) {
    Gitsn_OffsetSystem_offset *ret = NULL;

    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_OffsetSystem_offset_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_OffsetSystem_offset_delAndSetNull, (void *)&ret);
        switch (src->M) {
        case DEF_OffsetSystem_offset_xy:
            if ((ret->x.xy = init_NodeListXY_from_ASN(src->elements.xy, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_OffsetSystem_offsetPresent_xy;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_OffsetSystem_offset_ll:
            if ((ret->x.ll = init_NodeListLL_from_ASN(src->elements.ll, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_OffsetSystem_offsetPresent_ll;
                Dz1Error_set(errp, 0);
            }
            break;
        default:
            ERR_SET_OUT(errp, EPERM);
            break;
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_OffsetSystem_offset_delAndSetNull, (void*)&ret);
    }

    return ret;
}

static Gitsn_OffsetSystem *init_OffsetSystem_from_ASN(OffsetSystem *src, Dz1Error *errp) {
    Gitsn_OffsetSystem *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_OffsetSystem_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_OffsetSystem_delAndSetNull, (void *)&ret);
        if ((ret->offset = init_OffsetSystem_offset_from_ASN(src->offset, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else {
            if (src->DEF_OffsetSystem_scale)
                ret->scale = src->scale;
            Dz1Error_set(errp, 0);
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_OffsetSystem_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_Circle *init_Circle_from_ASN(Circle *src, Dz1Error *errp) {
    Gitsn_Circle *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_Circle_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_Circle_delAndSetNull, (void *)&ret);
        if ((ret->center = init_Position3D_from_ASN(src->center, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else {
            ret->radius = src->radius;
            ret->units = (Gitsn_DistanceUnits)src->units;
            Dz1Error_set(errp, 0);
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_Circle_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_GeometricProjection *init_GeometricProjection_from_ASN(GeometricProjection *src,
                                                                    Dz1Error *errp) {
    Gitsn_GeometricProjection *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_GeometricProjection_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_GeometricProjection_delAndSetNull, (void *)&ret);
        if ((ret->direction = Dz1Calloc(2, 1, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else if (memcpy(ret->direction, src->direction.data, 2) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else if ((ret->circle = init_Circle_from_ASN(src->circle, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else {
            if (src->DEF_GeometricProjection_extent) {
                ret->extent = (Gitsn_Extent)src->extent;
            }
            if (src->DEF_GeometricProjection_laneWidth) {
                ret->laneWidth = src->laneWidth;
            }
            if (src->DEF_GeometricProjection_regional) {
            }
            Dz1Error_set(errp, 0);
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_GeometricProjection_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_ShapePointSet *init_ShapePointSet_from_ASN(ShapePointSet *src, Dz1Error *errp) {
    Gitsn_ShapePointSet *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_ShapePointSet_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_ShapePointSet_delAndSetNull, (void *)&ret);
        if ((ret->nodeList = init_NodeListXY_from_ASN(src->nodeList, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else {
            if (src->DEF_ShapePointSet_anchor) {
                if ((ret->anchor = init_Position3D_from_ASN(src->anchor, errp)) == NULL)
                    ERR_SET_OUT(errp, EFAULT);
                else
                    Dz1Error_set(errp, 0);
            }
            if (src->DEF_ShapePointSet_laneWidth) {
                ret->laneWidth = src->laneWidth;
            }
            if (src->DEF_ShapePointSet_directionality) {
                ret->directionality = (Gitsn_DirectionOfUse)src->directionality;
            }
            Dz1Error_set(errp, 0);
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_ShapePointSet_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_RegionOffsets *init_RegionOffsets_from_ASN(RegionOffsets *src, Dz1Error *errp) {
    Gitsn_RegionOffsets *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_RegionOffsets_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_RegionOffsets_delAndSetNull, (void *)&ret);
        ret->xOffset = src->xOffset;
        ret->yOffset = src->yOffset;
        if (src->DEF_RegionOffsets_zOffset)
            ret->zOffset = src->zOffset;
        Dz1Error_set(errp, 0);
        pthread_cleanup_pop(errp->code); // (Gitsn_RegionOffsets_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_RegionList *init_RegionList_from_ASN(RegionList *src, Dz1Error *errp) {
    Gitsn_RegionList *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_RegionList_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        Gitsn_RegionOffsets *_element = NULL;
        pthread_cleanup_push(Gitsn_RegionList_delAndSetNull, (void *)&ret);
        for (int i = 1; i <= (int)src->count; i++) {
            RegionOffsets *src_element = (RegionOffsets *)ASN1_Get_Node_Index(src, i);
            if (src_element == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if ((_element = init_RegionOffsets_from_ASN(src_element, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                pthread_cleanup_push(Gitsn_RegionOffsets_delAndSetNull, (void *)&_element);
                if ((*errp = ret->add(ret, _element)).code)
                    ERR_SET_OUT(errp, EFAULT);
                else {
                    _element = NULL;
                    // free(src_element);
                    Dz1Error_set(errp, 0);
                }
                pthread_cleanup_pop(1); // (Gitsn_RegionOffsets_delAndSetNull, (void*)&_element);
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_RegionList_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_RegionPointSet *init_RegionPointSet_from_ASN(RegionPointSet *src, Dz1Error *errp) {
    Gitsn_RegionPointSet *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_RegionPointSet_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_RegionPointSet_delAndSetNull, (void *)&ret);
        if ((ret->nodeList = init_RegionList_from_ASN((RegionList *)&src->nodeList, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else {
            if (src->DEF_RegionPointSet_anchor) {
                if ((ret->anchor = init_Position3D_from_ASN(src->anchor, errp)) == NULL)
                    ERR_SET_OUT(errp, EFAULT);
                else
                    Dz1Error_set(errp, 0);
            }
            if (src->DEF_RegionPointSet_scale) {
                ret->scale = src->scale;
            }
            Dz1Error_set(errp, 0);
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_RegionPointSet_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_ValidRegion_area *init_ValidRegion_area_from_ASN(ValidRegion_area *src, Dz1Error *errp) {
    Gitsn_ValidRegion_area *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_ValidRegion_area_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_ValidRegion_area_delAndSetNull, (void *)&ret);
        switch (src->M) {
        case DEF_ValidRegion_area_shapePointSet:
            if ((ret->x.shapePointSet = init_ShapePointSet_from_ASN(src->elements.shapePointSet, errp)) ==
                NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_ValidRegion_areaPresent_shapePointSet;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_ValidRegion_area_circle:
            if ((ret->x.circle = init_Circle_from_ASN(src->elements.circle, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_ValidRegion_areaPresent_circle;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_ValidRegion_area_regionPointSet:
            if ((ret->x.regionPointSet = init_RegionPointSet_from_ASN(src->elements.regionPointSet, errp)) ==
                NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_ValidRegion_areaPresent_regionPointSet;
                Dz1Error_set(errp, 0);
            }
            break;
        default:
            ERR_SET_OUT(errp, EPERM);
            break;
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_ValidRegion_area_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_ValidRegion *init_ValidRegion_from_ASN(ValidRegion *src, Dz1Error *errp) {
    Gitsn_ValidRegion *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_ValidRegion_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_ValidRegion_delAndSetNull, (void *)&ret);
        if ((ret->direction = Dz1Calloc(2, 1, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else if (memcpy(ret->direction, src->direction.data, 2) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else if ((ret->area = init_ValidRegion_area_from_ASN(src->area, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else {
            if (src->DEF_ValidRegion_extent) {
                ret->extent = (Gitsn_Extent)ret->extent;
            }
            Dz1Error_set(errp, 0);
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_ValidRegion_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_GeographicalPath_description *
init_GeographicalPath_description_from_ASN(GeographicalPath_description *src, Dz1Error *errp) {
    Gitsn_GeographicalPath_description *ret = NULL;

    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_GeographicalPath_description_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_GeographicalPath_description_delAndSetNull, (void *)&ret);
        switch (src->M) {
        case DEF_GeographicalPath_description_path:
            if ((ret->x.path = init_OffsetSystem_from_ASN(src->elements.path, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_GeographicalPath_descriptionPresent_path;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_GeographicalPath_description_geometry:
            if ((ret->x.geometry = init_GeometricProjection_from_ASN(src->elements.geometry, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_GeographicalPath_descriptionPresent_geometry;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_GeographicalPath_description_oldRegion:
            if ((ret->x.oldRegion = init_ValidRegion_from_ASN(src->elements.oldRegion, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_GeographicalPath_descriptionPresent_oldRegion;
                Dz1Error_set(errp, 0);
            }
            break;
        default:
            ERR_SET_OUT(errp, EPERM);
            break;
        }

        pthread_cleanup_pop(errp->code); // (Gitsn_GeographicalPath_description_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_GeographicalPath *init_GeographicalPath_from_ASN(GeographicalPath *src, Dz1Error *errp) {
    Gitsn_GeographicalPath *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_GeographicalPath_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_GeographicalPath_delAndSetNull, (void *)&ret);
        if (src->DEF_GeographicalPath_name) {
            if ((ret->name = Dz1Str_ndup(src->name.asnstring, src->name.nchar, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else
                Dz1Error_set(errp, 0);
        }

        if (src->DEF_GeographicalPath_id) {
            if ((ret->id = init_RoadSegmentReferenceID_from_ASN(src->id, errp)) ==
                NULL)
                ERR_SET_OUT(errp, EFAULT);
            else
                Dz1Error_set(errp, 0);
        }
        if (src->DEF_GeographicalPath_anchor) {
            if ((ret->anchor = init_Position3D_from_ASN(src->anchor, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else
                Dz1Error_set(errp, 0);
        }
        if (src->DEF_GeographicalPath_laneWidth) {
            ret->laneWidth = src->laneWidth;
        }
        if (src->DEF_GeographicalPath_directionality) {
            ret->directionality = (Gitsn_DirectionOfUse)src->directionality;
        }
        if (src->DEF_GeographicalPath_closedPath) {
            ret->closedPath = src->closedPath;
        }
        if (src->DEF_GeographicalPath_direction) {
            if ((ret->direction = Dz1Calloc(2, 1, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if (memcpy(ret->direction, src->direction.data, 2) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else
                Dz1Error_set(errp, 0);
        }
        if (src->DEF_GeographicalPath_description) {
            if ((ret->description = init_GeographicalPath_description_from_ASN(src->description, errp)) ==
                NULL)
                ERR_SET_OUT(errp, EFAULT);
            else
                Dz1Error_set(errp, 0);
        }
        if (src->DEF_GeographicalPath_regional) {
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_GeographicalPath_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_TravelerDataFrame_regions *
init_TravelerDataFrame_regions_from_ASN(TravelerDataFrame_regions *src, Dz1Error *errp) {
    Gitsn_TravelerDataFrame_regions *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_TravelerDataFrame_regions_new(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        Gitsn_GeographicalPath *_element = NULL;
        pthread_cleanup_push(Gitsn_TravelerDataFrame_regions_delAndSetNull, (void *)&ret);
        for (int i = 1; i <= (int)src->count; i++) {
            GeographicalPath *src_element = (GeographicalPath *)ASN1_Get_Node_Index((ASN1List *)src, i);
            if (src_element == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if ((_element = init_GeographicalPath_from_ASN(src_element, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                pthread_cleanup_push(Gitsn_GeographicalPath_delAndSetNull, (void *)&_element);
                if ((*errp = ret->add(ret, _element)).code)
                    ERR_SET_OUT(errp, EFAULT);
                else {
                    _element = NULL;
                    // free(src_element);				 need to check - gm
                    Dz1Error_set(errp, 0);
                }
                pthread_cleanup_pop(1); //(Gitsn_GeographicalPath_delAndSetNull, (void*)&_element);
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_TravelerDataFrame_regions_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_ITIScodesAndText_element_item *
init_ITIScodesAndText_element_item_from_ASN(ITIScodesAndText_element_item *src, Dz1Error *errp) {
    Gitsn_ITIScodesAndText_element_item *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_ITIScodesAndText_element_item_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_ITIScodesAndText_element_item_delAndSetNull, (void *)&ret);
        switch (src->M) {
        case DEF_ITIScodesAndText_element_item_itis:
            ret->x.itis = src->elements.itis;
            ret->present = Gitsn_ITIScodesAndText_element_itemPresent_itis;
            Dz1Error_set(errp, 0);
            break;
        case DEF_ITIScodesAndText_element_item_text:
            if ((ret->x.text = Dz1Str_ndup(src->elements.text.asnstring, src->elements.text.nchar, errp)) ==
                NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_ITIScodesAndText_element_itemPresent_text;
                Dz1Error_set(errp, 0);
            }
            break;
        default:
            ERR_SET_OUT(errp, EPERM);
            break;
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_ITIScodesAndText_element_item_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_ITIScodesAndText_element *init_ITIScodesAndText_element_from_ASN(ITIScodesAndText_element *src,
                                                                              Dz1Error *errp) {
    Gitsn_ITIScodesAndText_element *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_ITIScodesAndText_element_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_ITIScodesAndText_element_delAndSetNull, (void *)&ret);
        if ((ret->item = init_ITIScodesAndText_element_item_from_ASN(src->item, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else
            Dz1Error_set(errp, 0);
        pthread_cleanup_pop(errp->code); // (Gitsn_ITIScodesAndText_element_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_ITIScodesAndText *init_ITIScodesAndText_from_ASN(ITIScodesAndText *src, Dz1Error *errp) {
    Gitsn_ITIScodesAndText *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_ITIScodesAndText_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        Gitsn_ITIScodesAndText_element *_element = NULL;
        pthread_cleanup_push(Gitsn_ITIScodesAndText_delAndSetNull, (void *)&ret);
        for (int i = 1; i <= (int)src->count; i++) {
            ITIScodesAndText_element *src_element = (ITIScodesAndText_element *)ASN1_Get_Node_Index(src, i);
            if (src_element == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if ((_element = init_ITIScodesAndText_element_from_ASN(src_element, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                pthread_cleanup_push(Gitsn_ITIScodesAndText_element_delAndSetNull, (void *)&_element);
                if ((*errp = ret->add(ret, _element)).code)
                    ERR_SET_OUT(errp, EFAULT);
                else {
                    _element = NULL;
                    // free(src_element);
                    Dz1Error_set(errp, 0);
                }
                pthread_cleanup_pop(1); // (Gitsn_ITIScodesAndText_element_delAndSetNull, (void*)&_element);
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_ITIScodesAndText_delAndSetNull, (void*)&ret);
    }

    return ret;
}

static Gitsn_WorkZone_element_item *init_WorkZone_element_item_from_ASN(WorkZone_element_item *src,
                                                                        Dz1Error *errp) {
    Gitsn_WorkZone_element_item *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_WorkZone_element_item_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_WorkZone_element_item_delAndSetNull, (void *)&ret);
        switch (src->M) {
        case DEF_WorkZone_element_item_itis:
            ret->x.itis = src->elements.itis;
            ret->present = Gitsn_WorkZone_element_itemPresent_itis;
            Dz1Error_set(errp, 0);
            break;
        case DEF_WorkZone_element_item_text:
            if ((ret->x.text = Dz1Str_ndup(src->elements.text.asnstring, src->elements.text.nchar, errp)) ==
                NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_WorkZone_element_itemPresent_text;
                Dz1Error_set(errp, 0);
            }
            break;
        default:
            ERR_SET_OUT(errp, EPERM);
            break;
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_WorkZone_element_item_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_WorkZone_element *init_WorkZone_element_from_ASN(WorkZone_element *src, Dz1Error *errp) {
    Gitsn_WorkZone_element *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_WorkZone_element_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_WorkZone_element_delAndSetNull, (void *)&ret);
        if ((ret->item = init_WorkZone_element_item_from_ASN(src->item, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else
            Dz1Error_set(errp, 0);
        pthread_cleanup_pop(errp->code); // (Gitsn_WorkZone_element_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_WorkZone *init_WorkZone_from_ASN(WorkZone *src, Dz1Error *errp) {
    Gitsn_WorkZone *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_WorkZone_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        Gitsn_WorkZone_element *_element = NULL;
        pthread_cleanup_push(Gitsn_WorkZone_delAndSetNull, (void *)&ret);
        for (int i = 1; i <= (int)src->count; i++) {
            WorkZone_element *src_element = (WorkZone_element *)ASN1_Get_Node_Index(src, i);
            if (src_element == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if ((_element = init_WorkZone_element_from_ASN(src_element, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                pthread_cleanup_push(Gitsn_WorkZone_element_delAndSetNull, (void *)&_element);
                if ((*errp = ret->add(ret, _element)).code)
                    ERR_SET_OUT(errp, EFAULT);
                else {
                    _element = NULL;
                    // free(src_element);
                    Dz1Error_set(errp, 0);
                }
                pthread_cleanup_pop(1); // (Gitsn_WorkZone_element_delAndSetNull, (void*)&_element);
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_WorkZone_delAndSetNull, (void*)&ret);
    }

    return ret;
}

static Gitsn_GenericSignage_element_item *
init_GenericSignage_element_item_from_ASN(GenericSignage_element_item *src, Dz1Error *errp) {
    Gitsn_GenericSignage_element_item *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_GenericSignage_element_item_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_GenericSignage_element_item_delAndSetNull, (void *)&ret);
        switch (src->M) {
        case DEF_GenericSignage_element_item_itis:
            ret->x.itis = src->elements.itis;
            ret->present = Gitsn_GenericSignage_element_itemPresent_itis;
            Dz1Error_set(errp, 0);
            break;
        case DEF_GenericSignage_element_item_text:
            if ((ret->x.text = Dz1Str_ndup(src->elements.text.asnstring, src->elements.text.nchar, errp)) ==
                NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_GenericSignage_element_itemPresent_text;
                Dz1Error_set(errp, 0);
            }
            break;
        default:
            ERR_SET_OUT(errp, EPERM);
            break;
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_GenericSignage_element_item_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_GenericSignage_element *init_GenericSignage_element_from_ASN(GenericSignage_element *src,
                                                                          Dz1Error *errp) {
    Gitsn_GenericSignage_element *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_GenericSignage_element_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_GenericSignage_element_delAndSetNull, (void *)&ret);
        if ((ret->item = init_GenericSignage_element_item_from_ASN(src->item, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else
            Dz1Error_set(errp, 0);
        pthread_cleanup_pop(errp->code); // (Gitsn_GenericSignage_element_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_GenericSignage *init_GenericSignage_from_ASN(GenericSignage *src, Dz1Error *errp) {
    Gitsn_GenericSignage *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_GenericSignage_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        Gitsn_GenericSignage_element *_element = NULL;
        pthread_cleanup_push(Gitsn_GenericSignage_delAndSetNull, (void *)&ret);
        for (int i = 1; i <= (int)src->count; i++) {
            GenericSignage_element *src_element = (GenericSignage_element *)ASN1_Get_Node_Index(src, i);
            if (src_element == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if ((_element = init_GenericSignage_element_from_ASN(src_element, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                pthread_cleanup_push(Gitsn_GenericSignage_element_delAndSetNull, (void *)&_element);
                if ((*errp = ret->add(ret, _element)).code)
                    ERR_SET_OUT(errp, EFAULT);
                else {
                    _element = NULL;
                    // free(src_element);
                    Dz1Error_set(errp, 0);
                }
                pthread_cleanup_pop(1); // (Gitsn_GenericSignage_element_delAndSetNull, (void*)&_element);
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_GenericSignage_delAndSetNull, (void*)&ret);
    }

    return ret;
}

static Gitsn_SpeedLimit_element_item *init_SpeedLimit_element_item_from_ASN(SpeedLimit_element_item *src,
                                                                            Dz1Error *errp) {
    Gitsn_SpeedLimit_element_item *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_SpeedLimit_element_item_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_SpeedLimit_element_item_delAndSetNull, (void *)&ret);
        switch (src->M) {
        case DEF_SpeedLimit_element_item_itis:
            ret->x.itis = src->elements.itis;
            ret->present = Gitsn_SpeedLimit_element_itemPresent_itis;
            Dz1Error_set(errp, 0);
            break;
        case DEF_SpeedLimit_element_item_text:
            if ((ret->x.text = Dz1Str_ndup(src->elements.text.asnstring, src->elements.text.nchar, errp)) ==
                NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_SpeedLimit_element_itemPresent_text;
                Dz1Error_set(errp, 0);
            }
            break;
        default:
            ERR_SET_OUT(errp, EPERM);
            break;
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_SpeedLimit_element_item_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_SpeedLimit_element *init_SpeedLimit_element_from_ASN(SpeedLimit_element *src, Dz1Error *errp) {
    Gitsn_SpeedLimit_element *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_SpeedLimit_element_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_SpeedLimit_element_delAndSetNull, (void *)&ret);
        if ((ret->item = init_SpeedLimit_element_item_from_ASN(src->item, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else
            Dz1Error_set(errp, 0);
        pthread_cleanup_pop(errp->code); // (Gitsn_SpeedLimit_element_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_SpeedLimit *init_SpeedLimit_from_ASN(SpeedLimit *src, Dz1Error *errp) {
    Gitsn_SpeedLimit *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_SpeedLimit_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        Gitsn_SpeedLimit_element *_element = NULL;
        pthread_cleanup_push(Gitsn_SpeedLimit_delAndSetNull, (void *)&ret);
        for (int i = 1; i <= (int)src->count; i++) {
            SpeedLimit_element *src_element = (SpeedLimit_element *)ASN1_Get_Node_Index(src, i);
            if (src_element == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if ((_element = init_SpeedLimit_element_from_ASN(src_element, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                pthread_cleanup_push(Gitsn_SpeedLimit_element_delAndSetNull, (void *)&_element);
                if ((*errp = ret->add(ret, _element)).code)
                    ERR_SET_OUT(errp, EFAULT);
                else {
                    _element = NULL;
                    // free(src_element);
                    Dz1Error_set(errp, 0);
                }
                pthread_cleanup_pop(1); // (Gitsn_SpeedLimit_element_delAndSetNull, (void*)&_element);
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_SpeedLimit_delAndSetNull, (void*)&ret);
    }

    return ret;
}

static Gitsn_ExitService_element_item *init_ExitService_element_item_from_ASN(ExitService_element_item *src,
                                                                              Dz1Error *errp) {
    Gitsn_ExitService_element_item *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_ExitService_element_item_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_ExitService_element_item_delAndSetNull, (void *)&ret);
        switch (src->M) {
        case DEF_ExitService_element_item_itis:
            ret->x.itis = src->elements.itis;
            ret->present = Gitsn_ExitService_element_itemPresent_itis;
            Dz1Error_set(errp, 0);
            break;
        case DEF_ExitService_element_item_text:
            if ((ret->x.text = Dz1Str_ndup(src->elements.text.asnstring, src->elements.text.nchar, errp)) ==
                NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_ExitService_element_itemPresent_text;
                Dz1Error_set(errp, 0);
            }
            break;
        default:
            ERR_SET_OUT(errp, EPERM);
            break;
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_ExitService_element_item_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_ExitService_element *init_ExitService_element_from_ASN(ExitService_element *src,
                                                                    Dz1Error *errp) {
    Gitsn_ExitService_element *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_ExitService_element_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_ExitService_element_delAndSetNull, (void *)&ret);
        if ((ret->item = init_ExitService_element_item_from_ASN(src->item, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else
            Dz1Error_set(errp, 0);
        pthread_cleanup_pop(errp->code); // (Gitsn_ExitService_element_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_ExitService *init_ExitService_from_ASN(ExitService *src, Dz1Error *errp) {
    Gitsn_ExitService *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_ExitService_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        Gitsn_ExitService_element *_element = NULL;
        pthread_cleanup_push(Gitsn_ExitService_delAndSetNull, (void *)&ret);
        for (int i = 1; i <= (int)src->count; i++) {
            ExitService_element *src_element = (ExitService_element *)ASN1_Get_Node_Index(src, i);
            if (src_element == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if ((_element = init_ExitService_element_from_ASN(src_element, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                pthread_cleanup_push(Gitsn_ExitService_element_delAndSetNull, (void *)&_element);
                if ((*errp = ret->add(ret, _element)).code)
                    ERR_SET_OUT(errp, EFAULT);
                else {
                    _element = NULL;
                    // free(src_element);
                    Dz1Error_set(errp, 0);
                }
                pthread_cleanup_pop(1); // (Gitsn_ExitService_element_delAndSetNull, (void*)&_element);
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_ExitService_delAndSetNull, (void*)&ret);
    }

    return ret;
}

static Gitsn_TravelerDataFrame_content *
init_TravelerDataFrame_content_from_ASN(TravelerDataFrame_content *src, Dz1Error *errp) {
    Gitsn_TravelerDataFrame_content *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_TravelerDataFrame_content_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_TravelerDataFrame_content_delAndSetNull, (void *)&ret);
        switch (src->M) {
        case DEF_TravelerDataFrame_content_advisory:
            if ((ret->x.advisory = init_ITIScodesAndText_from_ASN((ITIScodesAndText *)&src->elements.advisory,
                                                                  errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_TravelerDataFrame_contentPresent_advisory;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_TravelerDataFrame_content_workZone:
            if ((ret->x.workZone = init_WorkZone_from_ASN((WorkZone *)&src->elements.workZone, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_TravelerDataFrame_contentPresent_workZone;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_TravelerDataFrame_content_genericSign:
            if ((ret->x.genericSign = init_GenericSignage_from_ASN(
                     (GenericSignage *)&src->elements.genericSign, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_TravelerDataFrame_contentPresent_genericSign;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_TravelerDataFrame_content_speedLimit:
            if ((ret->x.speedLimit =
                     init_SpeedLimit_from_ASN((SpeedLimit *)&src->elements.speedLimit, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_TravelerDataFrame_contentPresent_speedLimit;
                Dz1Error_set(errp, 0);
            }
            break;
        case DEF_TravelerDataFrame_content_exitService:
            if ((ret->x.exitService =
                     init_ExitService_from_ASN((ExitService *)&src->elements.exitService, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                ret->present = Gitsn_TravelerDataFrame_contentPresent_exitService;
                Dz1Error_set(errp, 0);
            }
            break;
        default:
            ERR_SET_OUT(errp, EPERM);
            break;
        }

        pthread_cleanup_pop(errp->code); // (Gitsn_TravelerDataFrame_content_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_TravelerDataFrame *init_TravelerDataFrame_from_ASN(TravelerDataFrame *src, Dz1Error *errp) {
    Gitsn_TravelerDataFrame *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_TravelerDataFrame_gen(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        pthread_cleanup_push(Gitsn_TravelerDataFrame_delAndSetNull, (void *)&ret);
        if ((ret->msgId = init_TravelerDataFrame_msgId_from_ASN(src->msgId, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else if ((ret->regions = init_TravelerDataFrame_regions_from_ASN(
                      (TravelerDataFrame_regions *)&src->regions, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else if ((ret->content = init_TravelerDataFrame_content_from_ASN(src->content, errp)) == NULL)
            ERR_SET_OUT(errp, EFAULT);
        else {
            ret->notUsed = src->notUsed;
            ret->frameType = (Gitsn_TravelerInfoType)src->frameType;
            ret->startTime = src->startTime;
            ret->durationTime = src->durationTime;
            ret->priority = src->priority;
            ret->notUsed1 = src->notUsed1;
            ret->notUsed2 = src->notUsed2;
            ret->notUsed3 = src->notUsed3;

            if (src->DEF_TravelerDataFrame_startYear) {
                ret->startYear = src->startYear;
            }
            if (src->DEF_TravelerDataFrame_url) {
                if ((ret->url = Dz1Str_ndup(src->url.asnstring, src->url.nchar, errp)) == NULL)
                    ERR_SET_OUT(errp, EFAULT);
                else
                    Dz1Error_set(errp, 0);
            }
            Dz1Error_set(errp, 0);
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_TravelerDataFrame_delAndSetNull, (void*)&ret);
    }
    return ret;
}

static Gitsn_TravelerDataFrameList *init_TravelerDataFrameList_from_ASN(TravelerDataFrameList *src,
                                                                        Dz1Error *errp) {
    Gitsn_TravelerDataFrameList *ret = NULL;
    if (src == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((ret = Gitsn_TravelerDataFrameList_new(errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        Gitsn_TravelerDataFrame *_element = NULL;
        pthread_cleanup_push(Gitsn_TravelerDataFrameList_delAndSetNull, (void *)&ret);
        for (int i = 1; i <= (int)src->count; i++) {
            TravelerDataFrame *src_element = ASN1_Get_Node_Index((ASN1List *)src, i);
            if (src_element == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else if ((_element = init_TravelerDataFrame_from_ASN(src_element, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else {
                pthread_cleanup_push(Gitsn_TravelerDataFrame_delAndSetNull, (void *)&_element);
                if ((*errp = ret->add(ret, _element)).code)
                    ERR_SET_OUT(errp, EFAULT);
                else {
                    _element = NULL;
                    // free(src_element);
                    Dz1Error_set(errp, 0);
                }
                pthread_cleanup_pop(1); // (Gitsn_TravelerDataFrame_delAndSetNull, (void*)&_element);
            }
        }
        pthread_cleanup_pop(errp->code); // (Gitsn_TravelerDataFrameList_delAndSetNull, (void*)&ret);
    }
    return ret;
}

bool_t DatexTravelerFromASN(TravelerInformation *src, Gitsn_TravelerInformation *dst, Dz1Error *err) {
    DZ1_ERROR_SAFE_PTR(errp, err);
    if (src == NULL || dst == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else if ((dst->dataFrames = init_TravelerDataFrameList_from_ASN((TravelerDataFrameList *)&src->dataFrames,
                                                                    errp)) == NULL)
        ERR_SET_OUT(errp, EFAULT);
    else {
        dst->msgCnt = src->msgCnt;

        if (src->DEF_TravelerInformation_timeStamp) {
            dst->timeStamp = src->timeStamp;
        }
        if (src->DEF_TravelerInformation_packetID) {

            char packetHex[19];
            static const char *digits = "0123456789ABCDEF";
            if (src->packetID.numbits != 9 || !src->packetID.data) { Dz1Error_set(errp, EINVAL); return FALSE; }
            for (unsigned i = 0; i < 9; ++i) { packetHex[i * 2] = digits[src->packetID.data[i] >> 4]; packetHex[i * 2 + 1] = digits[src->packetID.data[i] & 15]; }
            packetHex[18] = 0;
            if ((dst->packetID = Dz1Str_clone(packetHex, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else
                Dz1Error_set(errp, 0);
        }
        if (src->DEF_TravelerInformation_urlB) {
            if ((dst->urlB = Dz1Str_ndup(src->urlB.asnstring, src->urlB.nchar, errp)) == NULL)
                ERR_SET_OUT(errp, EFAULT);
            else
                Dz1Error_set(errp, 0);
        }
        if (src->DEF_TravelerInformation_regional) {
            // region
        }
    }

    if (errp->code == 0) {
    }
    return ERR_IS_SUCCESS(errp);
}

#include <GitsnAsnUtil.h>
#include <dz1_gasn_support.h>
// implement library functions here

static Gitsn_PositionalAccuracy* init_PositionalAccuracy_from_ASN(PositionalAccuracy* src, Dz1Error* errp)
{
	Gitsn_PositionalAccuracy* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_PositionalAccuracy_new(src->semiMajor, src->semiMinor, src->orientation, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else Dz1Error_set(errp, 0);
	return ret;
}

static Gitsn_AccelerationSet4Way* init_AccelerationSet4Way_from_ASN(AccelerationSet4Way* src, Dz1Error* errp)
{
	Gitsn_AccelerationSet4Way* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_AccelerationSet4Way_new(src->lon, src->lat, src->vert, src->yaw, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else Dz1Error_set(errp, 0);
	return ret;
}

static Gitsn_BrakeSystemStatus* init_BrakeSystemStatus_from_ASN(BrakeSystemStatus* src, Dz1Error* errp)
{
	Gitsn_BrakeSystemStatus* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	//else if (&src->wheelBrakes == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_BrakeSystemStatus_new(NULL, src->traction, src->abs, src->scs, src->brakeBoost, src->auxBrakes, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		size_t sz = src->wheelBrakes.numbits + 7 / 8;
		pthread_cleanup_push(Gitsn_BrakeSystemStatus_delAndSetNull, (void*)&ret);
		if ((ret->wheelBrakes = Dz1Calloc(sz, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (memcpy(ret->wheelBrakes, src->wheelBrakes.data, sz) == NULL) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Gitsn_BrakeSystemStatus_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_VehicleSize* init_VehicleSize_from_ASN(VehicleSize* src, Dz1Error* errp)
{
	Gitsn_VehicleSize* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_VehicleSize_new(src->width, src->length, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else Dz1Error_set(errp, 0);
	return ret;
}

static Gitsn_BSMCoreData* init_BSMcoreData_from_ASN(BSMcoreData* src, Dz1Error* errp)
{
	Gitsn_BSMCoreData* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_BSMCoreData_new(src->msgCnt, NULL, src->secMark, src->lat, src->lon, src->elev, NULL,
		(Gitsn_TransmissionState)src->transmission, src->speed, src->heading, src->angle, NULL, NULL, NULL, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret->accuracy = init_PositionalAccuracy_from_ASN(src->accuracy, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret->accelSet = init_AccelerationSet4Way_from_ASN(src->accelSet, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret->brakes = init_BrakeSystemStatus_from_ASN(src->brakes, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret->size = init_VehicleSize_from_ASN(src->size, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		u8_t buf[32] = { 0, };
		sprintf(buf, "0x%X 0x%X 0x%X 0x%X", src->id.data[0], src->id.data[1], src->id.data[2], src->id.data[3]);
		if ((ret->id = Dz1Str_ndup(buf, sizeof(buf), errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);
		Dz1Error_set(errp, 0);
	}
	return ret;
}

bool_t GitsnAsnUtil_Gitsn_BasicSafetyMessageFromASN(BasicSafetyMessage* src, Gitsn_BasicSafetyMessage* dst, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || dst == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst->coreData = init_BSMcoreData_from_ASN(src->coreData, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}

static Gitsn_LaneTypeAttributes* init_LaneTypeAttributes_from_ASN(LaneTypeAttributes* src, Dz1Error* errp)
{
	Gitsn_LaneTypeAttributes* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_LaneTypeAttributes_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_LaneTypeAttributes_delAndSetNull, (void*)&ret);
		switch (src->M)
		{
		case DEF_LaneTypeAttributes_vehicle:
		{
			size_t sz = src->elements.vehicle.numbits + 7 / 8;
			if ((ret->x.vehicle = Dz1Calloc(sz, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (memcpy(ret->x.vehicle, src->elements.vehicle.data, sz) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_LaneTypeAttributesPresent_vehicle;
				Dz1Error_set(errp, 0);
			}
		}
		break;
		case DEF_LaneTypeAttributes_crosswalk:
			if ((ret->x.crosswalk = Dz1Calloc(2, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (memcpy(ret->x.crosswalk, src->elements.crosswalk.data, 2) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_LaneTypeAttributesPresent_crosswalk;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_LaneTypeAttributes_bikeLane:
			if ((ret->x.bikeLane = Dz1Calloc(2, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (memcpy(ret->x.bikeLane, src->elements.bikeLane.data, 2) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_LaneTypeAttributesPresent_bikeLane;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_LaneTypeAttributes_sidewalk:
			if ((ret->x.sidewalk = Dz1Calloc(2, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (memcpy(ret->x.sidewalk, src->elements.sidewalk.data, 2) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_LaneTypeAttributesPresent_sidewalk;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_LaneTypeAttributes_median:
			if ((ret->x.median = Dz1Calloc(2, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (memcpy(ret->x.median, src->elements.median.data, 2) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_LaneTypeAttributesPresent_median;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_LaneTypeAttributes_striping:
			if ((ret->x.striping = Dz1Calloc(2, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (memcpy(ret->x.striping, src->elements.striping.data, 2) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_LaneTypeAttributesPresent_striping;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_LaneTypeAttributes_trackedVehicle:
			if ((ret->x.trackedVehicle = Dz1Calloc(2, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (memcpy(ret->x.trackedVehicle, src->elements.trackedVehicle.data, 2) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_LaneTypeAttributesPresent_trackedVehicle;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_LaneTypeAttributes_parking:
			if ((ret->x.parking = Dz1Calloc(2, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (memcpy(ret->x.parking, src->elements.parking.data, 2) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
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
static Gitsn_LaneAttributes* init_LaneAttributes_from_ASN(LaneAttributes* src, Dz1Error* errp)
{
	Gitsn_LaneAttributes* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_LaneAttributes_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_LaneAttributes_delAndSetNull, (void*)&ret);
		if ((ret->directionalUse = Dz1Calloc(1, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (memcpy(ret->directionalUse, src->directionalUse.data, 1) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->sharedWith = Dz1Calloc(2, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (memcpy(ret->sharedWith, src->sharedWith.data, 2) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->laneType = init_LaneTypeAttributes_from_ASN(src->laneType, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			// gm ~
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_LaneAttributes_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_ConnectingLane* init_ConnectingLane_from_ASN(ConnectingLane* src, Dz1Error* errp)
{
	Gitsn_ConnectingLane* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if((ret = Gitsn_ConnectingLane_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_ConnectingLane_delAndSetNull, (void*)&ret);
		ret->lane = src->lane;
		if (src->DEF_ConnectingLane_maneuver)
		{
			size_t sz = 0;
			sz = (src->maneuver.numbits + 7) / 8;
			if ((ret->maneuver = Dz1Calloc(sz, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (memcpy(ret->maneuver, src->maneuver.data, sz) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Gitsn_ConnectingLane_delAndSetNull, (void*)&ret);
	}
	return ret;
}
static Gitsn_IntersectionReferenceID* init_IntersectionReferenceID_from_ASN(IntersectionReferenceID* src, Dz1Error* errp);
static Gitsn_Connection* init_Connection_from_ASN(Connection* src, Dz1Error* errp)
{
	Gitsn_Connection* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Connection_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_Connection_delAndSetNull, (void*)ret);
		if ((ret->connecctingLnae = init_ConnectingLane_from_ASN(src->connectingLane, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			if (src->DEF_Connection_remoteIntersection)
			{
				if ((ret->remoteIntersection = init_IntersectionReferenceID_from_ASN(src->remoteIntersection, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
			if(src->DEF_Connection_signalGroup)
			{
				ret->signalGroup = src->signalGroup;
			}
			if(src->DEF_Connection_userClass)
			{
				ret->userClass = src->userClass;
			}
			if(src->DEF_Connection_connectionID)
			{
				ret->connectionID = src->connectionID;
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_Connection_delAndSetNull, (void*)ret);
	}
	return ret;
}

static Gitsn_ConnectsToList* init_ConnectsToList_from_ASN(ConnectsToList* src, Dz1Error* errp)
{
	Gitsn_ConnectsToList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_ConnectsToList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Gitsn_Connection* _element = NULL;
		pthread_cleanup_push(Gitsn_ConnectsToList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			Connection* src_element = (Connection*)ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((_element = init_Connection_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				pthread_cleanup_push(Gitsn_Connection_delAndSetNull, (void*)&_element);
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else
				{
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

static Gitsn_OverlayLaneList* init_OverlayLaneList_from_ASN(OverlayLaneList* src, Dz1Error* errp)
{
	Gitsn_OverlayLaneList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_OverlayLaneList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_OverlayLaneList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			LaneID* src_element = ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				LaneID _element = *src_element;
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_OverlayLaneList_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_NodeListXY* init_NodeListXY_from_ASN(NodeListXY* src, Dz1Error* errp);
static Gitsn_GenericLane* init_GenericLane_from_ASN(GenericLane* src, Dz1Error* errp)
{
	Gitsn_GenericLane* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_GenericLane_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_GenericLane_delAndSetNull, (void*)&ret);
		if ((ret->laneAttributes = init_LaneAttributes_from_ASN(src->laneAttributes, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->nodeList = init_NodeListXY_from_ASN(src->nodeList, errp)) == NULL) ERR_SET_OUT(errp,EFAULT);
		else
		{
			ret->laneID = src->laneID;
			if (src->DEF_GenericLane_name)
			{
				if ((ret->name = Dz1Str_ndup(src->name.asnstring, src->name.nchar, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}

			if (src->DEF_GenericLane_ingressApproach)
			{
				ret->ingressApproach = src->ingressApproach;
			}

			if(src->DEF_GenericLane_egressApproach)
			{
				ret->egressApproach = src->egressApproach;
			}
			if(src->DEF_GenericLane_maneuvers)
			{
				size_t sz = 0;
				sz = (src->maneuvers.numbits + 7) / 8;
				if ((ret->maneuvers = Dz1Calloc(sz, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if (memcpy(ret->maneuvers, src->maneuvers.data, sz) == NULL) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
			if(src->DEF_GenericLane_connectsTo)
			{
				if ((ret->connectsTo = init_ConnectsToList_from_ASN((ConnectsToList*)&src->connectsTo, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
			if(src->DEF_GenericLane_overlays)
			{
				if ((ret->overlays = init_OverlayLaneList_from_ASN((OverlayLaneList*)&src->overlays, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
			if (src->DEF_GenericLane_regional) {}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_GenericLane_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_LaneList* init_LaneList_from_ASN(LaneList* src, Dz1Error* errp)
{
	Gitsn_LaneList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_LaneList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Gitsn_GenericLane* _element = NULL;
		pthread_cleanup_push(Gitsn_LaneList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			GenericLane* src_element = (GenericLane*)ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((_element = init_GenericLane_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				pthread_cleanup_push(Gitsn_GenericLane_delAndSetNull, (void*)&_element);
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else
				{
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



static Gitsn_PreemptPriorityList* init_PreemptPriorityList_from_ASN(PreemptPriorityList* src, Dz1Error* errp)
{
	Gitsn_PreemptPriorityList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_PreemptPriorityList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_PreemptPriorityList_delAndSetNull, (void*)&ret);
		// region

		pthread_cleanup_pop(errp->code); // (Gitsn_PreemptPriorityList_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Position3D* init_Position3D_from_ASN(Position3D* src, Dz1Error* errp);
static Gitsn_SpeedLimitList* init_SpeedLimitList_from_ASN(SpeedLimitList* src, Dz1Error* errp);
static Gitsn_IntersectionGeometry* init_IntersectionGeometry_from_ASN(IntersectionGeometry* src, Dz1Error* errp)
{
	Gitsn_IntersectionGeometry* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_IntersectionGeometry_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_IntersectionGeometry_delAndSetNull, (void*)&ret);
		if ((ret->id = init_IntersectionReferenceID_from_ASN(src->id, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->refPoint = init_Position3D_from_ASN(src->refPoint, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->laneSet = init_LaneList_from_ASN((LaneList*)&src->laneSet, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			ret->revision = src->revision;
			if (src->DEF_IntersectionGeometry_name)
			{
				if ((ret->name = Dz1Str_ndup(src->name.asnstring, src->name.nchar, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
			if (src->DEF_IntersectionGeometry_laneWidth)
			{
				ret->laneWidth = src->laneWidth;
			}
			if (src->DEF_IntersectionGeometry_speedLimits)
			{
				if ((ret->speedLimits = init_SpeedLimitList_from_ASN((SpeedLimitList*)&src->speedLimits, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
			if (src->DEF_IntersectionGeometry_preemptPriorityData)
			{
				/*if ((ret->preemptPriorityData = init_PreemptPriorityList_from_ASN((PreemptPriorityList*)&src->preemptPriorityData, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);*/
			}
			if (src->DEF_IntersectionGeometry_regional) {}
		}

		pthread_cleanup_pop(errp->code); // (Gitsn_IntersectionGeometry_delAndSetNull, (void*)&ret);
	}
	return ret;
}


static Gitsn_IntersectionGeometryList* init_IntersectionGeometryList_from_ASN(IntersectionGeometryList* src, Dz1Error* errp)
{
	Gitsn_IntersectionGeometryList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_IntersectionGeometryList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Gitsn_IntersectionGeometry* _element = NULL;
		pthread_cleanup_push(Gitsn_IntersectionGeometryList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			IntersectionGeometry* src_element = (IntersectionGeometry*)ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((_element = init_IntersectionGeometry_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				pthread_cleanup_push(Gitsn_IntersectionGeometry_delAndSetNull, (void*)&_element);
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else
				{
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

static Gitsn_RoadLaneSetList* init_RoadLaneSetList_from_ASN(RoadLaneSetList* src, Dz1Error* errp)
{
	Gitsn_RoadLaneSetList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_RoadLaneSetList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Gitsn_GenericLane* _element = NULL;
		pthread_cleanup_push(Gitsn_RoadLaneSetList_delAndSetNull, (void*)&ret);

		for (int i = 1; i <= (int)src->count; i++)
		{
			GenericLane* src_element = (GenericLane*)ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((_element = init_GenericLane_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				pthread_cleanup_push(Gitsn_GenericLane_delAndSetNull, (void*)&_element);
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else
				{
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


static Gitsn_RoadSegmentReferenceID* init_RoadSegmentReferenceID_from_ASN(RoadSegmentReferenceID* src, Dz1Error* errp);
static Gitsn_RoadSegment* init_RoadSegment_from_ASN(RoadSegment* src, Dz1Error* errp)
{
	Gitsn_RoadSegment* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_RoadSegment_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_RoadSegment_delAndSetNull, (void*)&ret);
		if ((ret->id = init_RoadSegmentReferenceID_from_ASN(src->id, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->refPoint = init_Position3D_from_ASN(src->refPoint, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->roadLaneSet = init_RoadLaneSetList_from_ASN((RoadLaneSetList*)&src->roadLaneSet, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			ret->revision = src->revision;

			if (src->DEF_RoadSegment_name) {
				if ((ret->name = Dz1Str_ndup(src->name.asnstring, src->name.nchar, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
			if (src->DEF_RoadSegment_laneWidth)
			{
				ret->laneWidth = src->laneWidth;
			}
			if (src->DEF_RoadSegment_speedLimits)
			{
				if ((ret->speedLimits = init_SpeedLimitList_from_ASN((SpeedLimitList*)&src->speedLimits, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
			if (src->DEF_RoadSegment_regional) {}

		}

		pthread_cleanup_pop(errp->code); // (Gitsn_RoadSegment_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_RoadSegmentList* init_RoadSegmentList_from_ASN(RoadSegmentList* src, Dz1Error* errp)
{
	Gitsn_RoadSegmentList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_RoadSegmentList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Gitsn_RoadSegment* _element = NULL;
		pthread_cleanup_push(Gitsn_RoadSegmentList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			RoadSegment* src_element = (RoadSegment*)ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((_element = init_RoadSegment_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				pthread_cleanup_push(Gitsn_RoadSegment_delAndSetNull, (void*)&_element);
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else
				{
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

static Gitsn_DataParameters* init_DataParameters_from_ASN(DataParameters* src, Dz1Error* errp)
{
	Gitsn_DataParameters* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_DataParameters_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_DataParameters_delAndSetNull, (void*)&ret);
		if (src->DEF_DataParameters_processMethod)
		{
			if ((ret->processMethod = Dz1Str_ndup(src->processMethod.asnstring, src->processMethod.nchar, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_DataParameters_processAgency)
		{
			if ((ret->processAgency = Dz1Str_ndup(src->processAgency.asnstring, src->processAgency.nchar, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_DataParameters_lastCheckedDate)
		{
			if ((ret->lastCheckedDate = Dz1Str_ndup(src->lastCheckedDate.asnstring, src->lastCheckedDate.nchar, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_DataParameters_geoidUsed)
		{
			if ((ret->geoidUsed = Dz1Str_ndup(src->geoidUsed.asnstring, src->geoidUsed.nchar, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Gitsn_DataParameters_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_RestrictionUserType* init_RestrictionUserType_from_ASN(RestrictionUserType* src, Dz1Error* errp)
{
	Gitsn_RestrictionUserType* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_RestrictionUserType_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_RestrictionUserType_delAndSetNull, (void*)&ret);

		switch (src->M)
		{
		case DEF_RestrictionUserType_basicType:
			ret->x.basicType = (Gitsn_RestrictionAppliesTo)src->elements.basicType;
			ret->present = Gitsn_RestrictionUserTypePresent_basicType;
			Dz1Error_set(errp, 0);
			break;
		case DEF_RestrictionUserType_regional:
			break;
		default: ERR_SET_OUT(errp, EPERM); break;
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_RestrictionUserType_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_RestrictionUserTypeList* init_RestrictionUserTypeList_from_ASN(RestrictionUserTypeList* src, Dz1Error* errp)
{
	Gitsn_RestrictionUserTypeList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_RestrictionUserTypeList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Gitsn_RestrictionUserType* _element = NULL;
		pthread_cleanup_push(Gitsn_RestrictionUserTypeList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			RestrictionUserType* src_element = (RestrictionUserType*)ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((_element = init_RestrictionUserType_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				pthread_cleanup_push(Gitsn_RestrictionUserType_delAndSetNull, (void*)&_element);
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else
				{
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

static Gitsn_RestrictionClassAssignment* init_RestrictionClassAssignment_from_ASN(RestrictionClassAssignment* src, Dz1Error* errp)
{
	Gitsn_RestrictionClassAssignment* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_RestrictionClassAssignment_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_RestrictionClassAssignment_delAndSetNull, (void*)&ret);
		if ((ret->users = init_RestrictionUserTypeList_from_ASN((RestrictionUserTypeList*)&src->users, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			ret->id = src->id;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_RestrictionClassAssignment_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_RestrictionClassList* init_RestrictionClassList_from_ASN(RestrictionClassList* src, Dz1Error* errp)
{
	Gitsn_RestrictionClassList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_RestrictionClassList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Gitsn_RestrictionClassAssignment* _element = NULL;
		pthread_cleanup_push(Gitsn_RestrictionClassList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			RestrictionClassAssignment* src_element = (RestrictionClassAssignment*)ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((_element = init_RestrictionClassAssignment_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				pthread_cleanup_push(Gitsn_RestrictionClassAssignment_delAndSetNull, (void*)&_element);
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else
				{
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

bool_t GitsnAsnUtil_Gitsn_MapDataFromASN(MapData* src, Gitsn_MapData* dst, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || dst == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		dst->msgIssueRevision = src->msgIssueRevision;

		if (src->DEF_MapData_timeStamp)
		{
			dst->timeStamp = src->timeStamp;
		}
		if (src->DEF_MapData_layerType)
		{
			dst->layerType = (Gitsn_LayerType)src->layerType;
		}
		if (src->DEF_MapData_layerID) {
			dst->layerID = src->layerID;
		}
		if (src->DEF_MapData_intersections)
		{
			if ((dst->intersections = init_IntersectionGeometryList_from_ASN((IntersectionGeometryList*)&src->intersections, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_MapData_roadSegments)
		{
			if ((dst->roadSegments = init_RoadSegmentList_from_ASN((RoadSegmentList*)&src->roadSegments, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_MapData_dataParameters)
		{
			if ((dst->dataParameters = init_DataParameters_from_ASN(src->dataParameters, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_MapData_restrictionList)
		{
			if ((dst->restrictionList = init_RestrictionClassList_from_ASN((RestrictionClassList*)&src->restrictionList, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_MapData_regional) {}
	}

	return ERR_IS_SUCCESS(errp);
}


static Gitsn_VehicleID* init_VehicleID_from_ASN(VehicleID* src, Dz1Error* errp)
{
	Gitsn_VehicleID* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_VehicleID_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_VehicleID_delAndSetNull, (void*)&ret);
		ret->present = (Gitsn_VehicleIDPresent)src->M;
		switch (ret->present)
		{
		case Gitsn_VehicleIDPresent_entityID:
			if ((ret->x.entityID = Dz1Str_ndup(src->elements.entityID.data, src->elements.entityID.numbits, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
			break;
		case Gitsn_VehicleIDPresent_stationID:
			ret->x.stationID = src->elements.stationID;
			Dz1Error_set(errp, 0);
			break;
		default: ERR_SET_OUT(errp, EFAULT); break;
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_VehicleID_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_VehicleIdent_vehicleClass* init_VehicleIdent_vehicleClass_from_ASN(VehicleIdent_vehicleClass* src, Dz1Error* errp)
{
	Gitsn_VehicleIdent_vehicleClass* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_VehicleIdent_vehicleClass_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		ret->present = (Gitsn_VehicleIdent_vehicleClassPresent)src->M;
		switch (ret->present)
		{
		case Gitsn_VehicleIdent_vehicleClassPresent_vGroup:
			ret->x.vGroup = (Gitsn_VehicleGroupAffected)src->elements.vGroup;
			break;
		case Gitsn_VehicleIdent_vehicleClassPresent_rGroup:
			ret->x.rGroup = (Gitsn_ResponderGroupAffected)src->elements.rGroup;
			break;
		case Gitsn_VehicleIdent_vehicleClassPresent_rEquip:
			ret->x.rEquip = (Gitsn_IncidentResponseEquipment)src->elements.rEquip;
			break;
		default: ERR_SET_OUT(errp, EFAULT); break;
		}
	}
	return ret;
}

static Gitsn_VehicleIdent* init_VehicleIdent_from_ASN(VehicleIdent* src, Dz1Error* errp)
{
	Gitsn_VehicleIdent* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_VehicleIdent_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_VehicleIdent_delAndSetNull, (void*)&ret);
		if (src->DEF_VehicleIdent_name)
		{
			if ((ret->name = Dz1Str_ndup(src->name.asnstring, src->name.nchar, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleIdent_vin)
		{
			if ((ret->vin = Dz1Str_ndup(src->vin.data, src->vin.numbits, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleIdent_ownerCode)
		{
			if ((ret->ownerCode = Dz1Str_ndup(src->ownerCode.asnstring, src->ownerCode.nchar, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleIdent_id)
		{
			if ((ret->id = init_VehicleID_from_ASN(src->id, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleIdent_vehicleType)
		{
			if ((ret->vehicleType = (Gitsn_VehicleType)src->vehicleType) > Gitsn_VehicleType_max) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleIdent_vehicleClass)
		{
			if ((ret->vehicleClass = init_VehicleIdent_vehicleClass_from_ASN(src->vehicleClass, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Gitsn_VehicleIdent_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_DDateTime* init_DDateTime_from_ASN(DDateTime* src, Dz1Error* errp)
{
	Gitsn_DDateTime* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_DDateTime_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_DDateTime_delAndSetNull, (void*)&ret);
		if (src->DEF_DDateTime_year)
		{
			ret->year = src->year;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_DDateTime_month)
		{
			ret->month = src->month;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_DDateTime_day)
		{
			ret->day = src->day;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_DDateTime_hour)
		{
			ret->hour = src->hour;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_DDateTime_minute)
		{
			ret->minute = src->minute;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_DDateTime_second)
		{
			ret->second = src->second;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_DDateTime_offset)
		{
			ret->offset = src->offset;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_DDateTime_delAndSetNul, (void*)&ret);
	}
	return ret;
}

static Gitsn_TransmissionAndSpeed* init_TransmissionAndSpeed_from_ASN(TransmissionAndSpeed* src, Dz1Error* errp)
{
	Gitsn_TransmissionAndSpeed* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_TransmissionAndSpeed_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_TransmissionAndSpeed_delAndSetNull, (void*)&ret);
		if ((ret->transmission = (Gitsn_TransmissionState)src->transmisson) > Gitsn_TransmissionState_max) ERR_SET_OUT(errp, EFAULT);
		ret->speed = src->speed;
		Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Gitsn_TransmissionAndSpeed_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_PositionConfidenceSet* init_PositionConfidenceSet_from_ASN(PositionConfidenceSet* src, Dz1Error* errp)
{
	Gitsn_PositionConfidenceSet* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_PositionConfidenceSet_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_PositionConfidenceSet_delAndSetNull, (void*)&ret);
		if (0) {}
		else if ((ret->pos = (Gitsn_PositionConfidence)src->pos) > Gitsn_PositionConfidence_max) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->elevation = (ElevationConfidence)src->elevation) > Gitsn_ElevationConfidence_max) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Gitsn_PositionConfidenceSet_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_SpeedandHeadingandThrottleConfidence* init_SpeedandHeadingandThrottleConfidence_from_ASN(SpeedandHeadingandThrottleConfidence* src, Dz1Error* errp)
{
	Gitsn_SpeedandHeadingandThrottleConfidence* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_SpeedandHeadingandThrottleConfidence_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_SpeedandHeadingandThrottleConfidence_delAndSetNull, (void*)&ret);
		if (0) {}
		else if ((ret->heading = (Gitsn_HeadingConfidence)src->heading) > Gitsn_HeadingConfidence_max) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->speed = (Gitsn_SpeedConfidence)src->speed) > Gitsn_SpeedConfidence_max) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->throttle = (Gitsn_ThrottleConfidence)src->throttle) > Gitsn_ThrottleConfidence_max) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); //  (Gitsn_SpeedandHeadingandThrottleConfidence_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_FullPositionVector* init_FullPositionVector_from_ASN(FullPositionVector* src, Dz1Error* errp)
{
	Gitsn_FullPositionVector* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_FullPositionVector_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_FullPositionVector_delAndSetNull, (void*)&ret);
		if (src->DEF_FullPositionVector_utcTime)
		{
			if ((ret->utcTime = init_DDateTime_from_ASN(src->utcTime, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_FullPositionVector_elevation)
		{
			ret->elevation = src->elevation;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_FullPositionVector_heading)
		{
			ret->heading = src->heading;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_FullPositionVector_speed)
		{
			if ((ret->speed = init_TransmissionAndSpeed_from_ASN(src->speed, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_FullPositionVector_posAccuracy)
		{
			if ((ret->posAccuracy = init_PositionalAccuracy_from_ASN(src->posAccuracy, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_FullPositionVector_timeConfidence)
		{
			if ((ret->timeConfidence = (Gitsn_TimeConfidence)src->timeConfidence) > Gitsn_TimeConfidence_max) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_FullPositionVector_posConfidence)
		{
			if ((ret->posConfidence = init_PositionConfidenceSet_from_ASN(src->posConfidence, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_FullPositionVector_speedConfidence)
		{
			if ((ret->speedConfidence = init_SpeedandHeadingandThrottleConfidence_from_ASN(src->speedConfidence, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}

		ret->lat = src->lat;
		ret->lon = src->lon;

		pthread_cleanup_pop(errp->code); // (Gitsn_FullPositionVector_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_PathHistoryPoint* init_PathHistoryPoint_from_ASN(PathHistoryPoint* src, Dz1Error* errp)
{
	Gitsn_PathHistoryPoint* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_PathHistoryPoint_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_PathHistoryPoint_delAndSetNull, (void*)&ret);
		if (src->DEF_PathHistoryPoint_speed)
		{
			ret->speed = src->speed;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_PathHistoryPoint_posAccuracy)
		{
			if ((ret->posAccuracy = init_PositionalAccuracy_from_ASN(src->posAccuracy, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_PathHistoryPoint_heading)
		{
			ret->heading = src->heading;
			Dz1Error_set(errp, 0);
		}

		ret->latOffset = src->latOffset;
		ret->lonOffset = src->lonOffset;
		ret->elevationOffset = src->elevationOffset;
		ret->timeOffset = src->timeOffset;

		pthread_cleanup_pop(errp->code); // (Gitsn_PathHistoryPoint_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_PathHistoryPointList* init_PathHistoryPointList_from_ASN(PathHistoryPointList* src, Dz1Error* errp)
{
	Gitsn_PathHistoryPointList* ret = NULL;
	if (src == NULL || src->count == 0) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_PathHistoryPointList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_PathHistoryPointList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			PathHistoryPoint* src_element = ASN1_Get_Node_Index(src,1);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				Gitsn_PathHistoryPoint* _element = NULL;
				if ((_element = init_PathHistoryPoint_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else
				{
					pthread_cleanup_push(Gitsn_PathHistoryPoint_delAndSetNull, (void*)&_element);
					if (0) {}
					else if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
					else
					{
						_element = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (Gitsn_PathHistoryPoint_delAndSetNull, (void*)&_element);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_PathHistoryPointList_delAndSetNull, (void*)&ret);
	}

	return ret;
}

static Gitsn_PathHistory* init_PathHistory_from_ASN(PathHistory* src, Dz1Error* errp)
{
	Gitsn_PathHistory* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_PathHistory_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_PathHistory_delAndSetNull, (void*)&ret);
		if (src->DEF_PathHistory_initialPosition)
		{
			if ((ret->initialPosition = init_FullPositionVector_from_ASN(src->initialPosition, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_PathHistory_currGNSSstatus)
		{
			size_t sz = 0;
			sz = (src->currGNSSstatus.numbits + 7) / 8;
			if ((ret->currGNSSstatus = Dz1Calloc(sz, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (memcpy(ret->currGNSSstatus, src->currGNSSstatus.data, sz) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}

		if ((ret->crumbData = init_PathHistoryPointList_from_ASN(&src->crumbData, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Gitsn_PathHistory_delAndSetNull, (void*)&ret);
	}

	return ret;
}

static Gitsn_PathPrediction* init_PathPrediction_from_ASN(PathPrediction* src, Dz1Error* errp)
{
	Gitsn_PathPrediction* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_PathPrediction_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_PathPrediction_delAndSetNull, (void*)&ret);
		ret->radiusOfCurve = src->radiusOfCurve;
		ret->confidence = src->confidence;
		Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Gitsn_PathPrediction_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_VehicleSafetyExtensions* init_VehicleSafetyExtensions_from_ASN(VehicleSafetyExtensions* src, Dz1Error* errp)
{
	Gitsn_VehicleSafetyExtensions* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_VehicleSafetyExtensions_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_VehicleSafetyExtensions_delAndSetNull, (void*)&ret);
		if (src->DEF_VehicleSafetyExtensions_events)
		{
			size_t sz = 0;
			sz = (src->events.numbits + 7) / 8;
			if ((ret->events = Dz1Calloc(sz, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (memcpy(ret->events, src->events.data, sz) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleSafetyExtensions_pathHistory)
		{
			if ((ret->pathHistory = init_PathHistory_from_ASN(src->pathHistory, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleSafetyExtensions_pathPrediction)
		{
			if ((ret->pathPrediction = init_PathPrediction_from_ASN(src->pathPrediction, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleSafetyExtensions_lights)
		{
			size_t sz = 0;
			sz = (src->lights.numbits + 7) / 8;
			if ((ret->lights = Dz1Calloc(sz, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (memcpy(ret->lights, src->lights.data, sz) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}

		// Extension
		if (src->E)
		{
			// ...
		}

		pthread_cleanup_pop(errp->code); // (Gitsn_VehicleSafetyExtensions_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_WiperSet* init_WiperSet_from_ASN(WiperSet* src, Dz1Error* errp)
{
	Gitsn_WiperSet* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_WiperSet_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_WiperSet_delAndSetNull, (void*)&ret);
		if (src->DEF_WiperSet_statusRear)
		{
			if ((ret->statusRear = (Gitsn_WiperStatus)src->statusRear) > Gitsn_WiperStatus_max) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_WiperSet_rateRear)
		{
			ret->rateRear = src->rateRear;
			Dz1Error_set(errp, 0);
		}

		if ((ret->statusFront = (Gitsn_WiperStatus)src->statusFront) > Gitsn_WiperStatus_max) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);
		ret->rateFront = src->rateFront;

		pthread_cleanup_pop(errp->code); // (Gitsn_WiperSet_delAndSetNull, (void*)&ret);
	}

	return ret;
}

static Gitsn_VehicleStatus_steering* init_VehicleStatus_steering_from_ASN(VehicleStatus_steering* src, Dz1Error* errp)
{
	Gitsn_VehicleStatus_steering* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_VehicleStatus_steering_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_VehicleStatus_steering_delAndSetNull, (void*)&ret);
		if (src->DEF_VehicleStatus_steering_confidence)
		{
			if ((ret->confidence = (Gitsn_SteeringWheelAngleConfidence)src->confidence) > Gitsn_SteeringWheelAngleConfidence_max) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_steering_rate)
		{
			ret->rate = src->rate;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_steering_wheels)
		{
			ret->wheels = src->wheels;
			Dz1Error_set(errp, 0);
		}
		ret->angle = src->angle;

		pthread_cleanup_pop(errp->code); // (Gitsn_VehicleStatus_steering_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_AccelSteerYawRateConfidence* init_AccelSteerYawRateConfidence_from_ASN(AccelSteerYawRateConfidence* src, Dz1Error* errp)
{
	Gitsn_AccelSteerYawRateConfidence* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_AccelSteerYawRateConfidence_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_AccelSteerYawRateConfidence_delAndSetNull, (void*)&ret);
		if (0) {}
		else if ((ret->yawRate = (Gitsn_YawRateConfidence)src->yawRate) > Gitsn_YawRateConfidence_max) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->acceleration = (Gitsn_AccelerationConfidence)src->acceleration) > Gitsn_AccelerationConfidence_max) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->steeringWheelAngle = (Gitsn_SteeringWheelAngleConfidence)src->steeringWheelAngle) > Gitsn_SteeringWheelAngleConfidence_max) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Gitsn_AccelSteerYawRateConfidence_delAndSetNull, (void*)&ret);
	}

	return ret;
}

static Gitsn_ConfidenceSet* init_ConfidenceSet_from_ASN(ConfidenceSet* src, Dz1Error* errp)
{
	Gitsn_ConfidenceSet* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_ConfidenceSet_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_ConfidenceSet_delAndSetNull, (void*)&ret);
		if (src->DEF_ConfidenceSet_accelConfidence)
		{
			if ((ret->accelConfidence = init_AccelSteerYawRateConfidence_from_ASN(src->accelConfidence, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_ConfidenceSet_speedConfidence)
		{
			if ((ret->speedConfidence = init_SpeedandHeadingandThrottleConfidence_from_ASN(src->speedConfidence, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_ConfidenceSet_timeConfidence)
		{
			if ((ret->timeConfidence = (Gitsn_TimeConfidence)src->timeConfidence) > Gitsn_TimeConfidence_max) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_ConfidenceSet_posConfidence)
		{
			if ((ret->posConfidence = init_PositionConfidenceSet_from_ASN(src->posConfidence, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_ConfidenceSet_steerConfidence)
		{
			if ((ret->steerConfidence = (Gitsn_SteeringWheelAngleConfidence)src->steerConfidence) > Gitsn_SteeringWheelAngleConfidence_max) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_ConfidenceSet_headingConfidence)
		{
			if ((ret->headingConfidence = (Gitsn_HeadingConfidence)src->headingConfidence) > Gitsn_HeadingConfidence_max) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_ConfidenceSet_throttleConfidence)
		{
			if ((ret->throttleConfidence = (Gitsn_ThrottleConfidence)src->throttleConfidence) > Gitsn_ThrottleConfidence_max) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_ConfidenceSet_delAndSetNull, (void*)&ret);
	}

	return ret;
}

static Gitsn_VehicleStatus_accelSets* init_VehicleStatus_accelSets_from_ASN(VehicleStatus_accelSets* src, Dz1Error* errp)
{
	Gitsn_VehicleStatus_accelSets* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_VehicleStatus_accelSets_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_VehicleStatus_accelSets_delAndSetNull, (void*)&ret);
		if (src->DEF_VehicleStatus_accelSets_accel4way)
		{
			if ((ret->accel4way = init_AccelerationSet4Way_from_ASN(src->accel4way, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_accelSets_vertAccelThres)
		{
			size_t sz = 0;
			sz = (src->vertAccelThres.numbits + 7) / 8;
			if ((ret->vertAccelThres = Dz1Calloc(sz, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (memcpy(ret->vertAccelThres, src->vertAccelThres.data, sz) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_accelSets_yawRateCon)
		{
			if ((ret->yawRateCon = (Gitsn_YawRateConfidence)src->yawRateCon) > Gitsn_YawRateConfidence_max) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_accelSets_hozAccelCon)
		{
			if ((ret->hozAccelCon = (Gitsn_AccelerationConfidence)src->hozAccelCon) > Gitsn_AccelerationConfidence_max) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_accelSets_confidenceSet)
		{
			if ((ret->confidenceSet = init_ConfidenceSet_from_ASN(src->confidenceSet, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_VehicleStatus_accelSets_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_VehicleStatus_object* init_VehicleStatus_object_from_ASN(VehicleStatus_object* src, Dz1Error* errp)
{
	Gitsn_VehicleStatus_object* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_VehicleStatus_object_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_VehicleStatus_object_delAndSetNull, (void*)&ret);
		ret->obDist = src->obDist;
		ret->obDirect = src->obDirect;
		if ((ret->dateTime = init_DDateTime_from_ASN(src->dateTime, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Gitsn_VehicleStatus_object_delAndSetNull, (void*)&ret);
	}

	return ret;
}

static Gitsn_BumperHeights* init_BumperHeights_from_ASN(BumperHeights* src, Dz1Error* errp)
{
	Gitsn_BumperHeights* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_BumperHeights_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_BumperHeights_delAndSetNull, (void*)&ret);
		ret->front = src->front;
		ret->rear = src->rear;
		Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Gitsn_BumperHeights_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_VehicleStatus_vehicleData* init_VehicleStatus_vehicleData_from_ASN(VehicleStatus_vehicleData* src, Dz1Error* errp)
{
	Gitsn_VehicleStatus_vehicleData* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_VehicleStatus_vehicleData_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_VehicleStatus_vehicleData_delAndSetNull, (void*)&ret);
		if (0) {}
		else if ((ret->bumpers = init_BumperHeights_from_ASN(src->bumpers, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->type = (Gitsn_VehicleType)src->type) > Gitsn_VehicleType_max) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);
		ret->height = src->height;
		ret->mass = src->mass;
		ret->trailerWeight = src->trailerWeight;

		pthread_cleanup_pop(errp->code); // (Gitsn_VehicleStatus_vehicleData_delAndSetNull, (void*)&ret);
	}

	return ret;
}


static Gitsn_TireData* init_TireData_from_ASN(TireData* src, Dz1Error* errp)
{
	Gitsn_TireData* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_TireData_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_TireData_delAndSetNull, (void*)&ret);

		if (src->DEF_TireData_location)
		{
			ret->location = src->location;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_TireData_pressure)
		{
			ret->pressure = src->pressure;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_TireData_temp)
		{
			ret->temp = src->temp;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_TireData_wheelSensorStatus)
		{
			if ((ret->wheelSensorStatus = (Gitsn_WheelSensorStatus)src->wheelSensorStatus) > Gitsn_WheelSensorStatus_max) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_TireData_wheelEndElectFault)
		{
			if ((ret->wheelEndElectFault = (Gitsn_WheelEndElectFault)src->wheelEndElectFault) > Gitsn_WheelEndElectFault_max) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_TireData_leakageRate)
		{
			ret->leakageRate = src->leakageRate;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_TireData_detection)
		{
			if ((ret->detection = (Gitsn_TirePressureThresholdDetection)src->detection) > Gitsn_TirePressureThresholdDetection_max) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_TireData_delAndSetNull, (void*)&ret);
	}

	return ret;
}

static Gitsn_TireDataList* init_TireDataList_from_ASN(TireDataList* src, Dz1Error* errp)
{
	Gitsn_TireDataList* ret = NULL;
	if (src == NULL || src->count == 0) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_TireDataList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_TireDataList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			TireData* src_element = ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				Gitsn_TireData* _element = NULL;
				if ((_element = init_TireData_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else
				{
					pthread_cleanup_push(Gitsn_TireData_delAndSetNull, (void*)&_element);
					if (0) {}
					else if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
					else
					{
						_element = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (Gitsn_TireData_delAndSetNull, (void*)&_element);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_TireDataList_delAndSetNull, (void*)&ret);
	}

	return ret;
}

static Gitsn_AxleWeightSet* init_AxleWeightSet_from_ASN(AxleWeightSet* src, Dz1Error* errp)
{
	Gitsn_AxleWeightSet* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_AxleWeightSet_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_AxleWeightSet_delAndSetNull, (void*)&ret);
		if (src->DEF_AxleWeightSet_location)
		{
			ret->location = src->location;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_AxleWeightSet_weight)
		{
			ret->weight = src->weight;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_AxleWeightSet_delAndSetNull, (void*)&ret);
	}

	return ret;
}

static Gitsn_AxleWeightList* init_AxleWeightList_from_ASN(AxleWeightList* src, Dz1Error* errp)
{
	Gitsn_AxleWeightList* ret = NULL;
	if (src == 0 || src->count == 0) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_AxleWeightList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_AxleWeightList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			AxleWeightSet* src_element = ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				Gitsn_AxleWeightSet* _element = NULL;
				if ((_element = init_AxleWeightSet_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else
				{
					pthread_cleanup_push(Gitsn_AxleWeightSet_delAndSetNull, (void*)&_element);
					if (0) {}
					else if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
					else
					{
						_element = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (Gitsn_AxleWeightSet_delAndSetNull, (void*)&_element);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_AxleWeightList_delAndSetNull, (void*)&ret);
	}

	return ret;
}

static Gitsn_J1939DataItems* init_J1939DataItems_from_ASN(J1939DataItems* src, Dz1Error* errp)
{
	Gitsn_J1939DataItems* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_J1939DataItems_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_J1939DataItems_delAndSetNull, (void*)&ret);
		if (src->DEF_J1939DataItems_tires)
		{
			if ((ret->tires = init_TireDataList_from_ASN(&src->tires, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_J1939DataItems_axles)
		{
			if ((ret->axles = init_AxleWeightList_from_ASN(&src->axles, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_J1939DataItems_trailerWeight) { ret->trailerWeight = src->trailerWeight; Dz1Error_set(errp, 0); }
		if (src->DEF_J1939DataItems_cargoWeight) { ret->cargoWeight = src->cargoWeight; Dz1Error_set(errp, 0); }
		if (src->DEF_J1939DataItems_steeringAxleTemperature) { ret->steeringAxleTemperature = src->steeringAxleTemperature; Dz1Error_set(errp, 0); }
		if (src->DEF_J1939DataItems_driveAxleLocation) { ret->driveAxleLocation = src->driveAxleLocation; Dz1Error_set(errp, 0); }
		if (src->DEF_J1939DataItems_driveAxleLiftAirPressure) { ret->driveAxleLiftAirPressure = src->driveAxleLiftAirPressure; Dz1Error_set(errp, 0); }
		if (src->DEF_J1939DataItems_driveAxleTemperature) { ret->driveAxleTemperature = src->driveAxleTemperature; Dz1Error_set(errp, 0); }
		if (src->DEF_J1939DataItems_driveAxleLubePressure) { ret->driveAxleLubePressure = src->driveAxleLubePressure; Dz1Error_set(errp, 0); }
		if (src->DEF_J1939DataItems_steeringAxleLubePressure) { ret->steeringAxleLubePressure = src->steeringAxleLubePressure; Dz1Error_set(errp, 0); }


		pthread_cleanup_pop(errp->code); // (Gitsn_J1939DataItems_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_VehicleStatus_weatherReport* init_VehicleStatus_weatherReport_from_ASN(VehicleStatus_weatherReport* src, Dz1Error* errp)
{
	Gitsn_VehicleStatus_weatherReport* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_VehicleStatus_weatherReport_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_VehicleStatus_weatherReport_delAndSetNull, (void*)&ret);
		if (src->DEF_VehicleStatus_weatherReport_rainRate)
		{
			ret->rainRate = src->rainRate;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_weatherReport_precipSituation)
		{
			if ((ret->precipSituation = (Gitsn_EssPrecipSituation)src->precipSituation) > Gitsn_EssPrecipSituation_max) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_weatherReport_solarRadiation)
		{
			src->solarRadiation = src->solarRadiation;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_weatherReport_friction)
		{
			ret->friction = src->friction;
			Dz1Error_set(errp, 0);
		}

		if ((ret->isRaining = (Gitsn_EssPrecipYesNo)src->isRaining) > Gitsn_EssPrecipYesNo_max) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Gitsn_VehicleStatus_weatherReport_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_VehicleStatus* init_VehicleStatus_from_ASN(VehicleStatus* src, Dz1Error* errp)
{
	Gitsn_VehicleStatus* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_VehicleStatus_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_VehicleStatus_delAndSetNull, (void*)&ret);
		if (src->DEF_VehicleStatus_lights)
		{
			size_t sz = 0;
			sz = (src->lights.numbits + 7) / 8;
			if ((ret->lights = Dz1Calloc(sz, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (memcpy(ret->lights, src->lights.data, sz) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_lightBar)
		{
			if ((ret->lightBar = (Gitsn_LightbarInUse)src->lightBar) > Gitsn_LightbarInUse_max) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_wipers)
		{
			if ((ret->wipers = init_WiperSet_from_ASN(src->wipers, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_brakeStatus)
		{
			if ((ret->brakeStatus = init_BrakeSystemStatus_from_ASN(src->brakeStatus, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_brakePressure)
		{
			if ((ret->brakePressure = (Gitsn_BrakeAppliedPressure)src->brakePressure) > Gitsn_BrakeAppliedPressure_max) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_roadFriction)
		{
			ret->roadFriction = src->roadFriction;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_sunData)
		{
			ret->sunData = src->sunData;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_rainData)
		{
			if ((ret->rainData = (Gitsn_RainSensor)src->rainData) > Gitsn_RainSensor_max) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_airTemp)
		{
			ret->airTemp = src->airTemp;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_airPres)
		{
			ret->airPres = src->airPres;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_steering)
		{
			if ((ret->steering = init_VehicleStatus_steering_from_ASN(src->steering, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_accelSets)
		{
			if ((ret->accelSets = init_VehicleStatus_accelSets_from_ASN(src->accelSets, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_object)
		{
			if ((ret->object = init_VehicleStatus_object_from_ASN(src->object, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_fullPos)
		{
			if ((ret->fullPos = init_FullPositionVector_from_ASN(src->fullPos, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_throttlePos)
		{
			ret->throttlePos = src->throttlePos;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_speedHeadC)
		{
			if ((ret->speedHeadC = init_SpeedandHeadingandThrottleConfidence_from_ASN(src->speedHeadC, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_speedC)
		{
			if ((ret->speedC = (Gitsn_SpeedConfidence)src->speedC) > Gitsn_SpeedConfidence_max) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_vehicleData)
		{
			if ((ret->vehicleData = init_VehicleStatus_vehicleData_from_ASN(src->vehicleData, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_vehicleIdent)
		{
			if ((ret->vehicleIdent = init_VehicleIdent_from_ASN(src->vehicleIdent, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_j1939data)
		{
			if ((ret->j1939DataItems = init_J1939DataItems_from_ASN(src->j1939data, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_weatherReport)
		{
			if ((ret->weatherReport = init_VehicleStatus_weatherReport_from_ASN(src->weatherReport, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleStatus_gnssStatus)
		{
			size_t sz = 0;
			sz = (src->gnssStatus.numbits + 7) / 8;
			if ((ret->gnssStatus = Dz1Calloc(sz, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (memcpy(ret->gnssStatus, src->gnssStatus.data, sz) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_VehicleStatus_delAndSetNull, (void*)&ret);
	}

	return ret;
}

static Gitsn_Snapshot* init_Snapshot_from_ASN(Snapshot* src, Dz1Error* errp)
{
	Gitsn_Snapshot* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Snapshot_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_Snapshot_delAndSetNull, (void*)&ret);
		if (src->DEF_Snapshot_safetyExt)
		{
			if ((ret->safetyExt = init_VehicleSafetyExtensions_from_ASN(src->safetyExt, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_Snapshot_dataSet)
		{
			if ((ret->dataSet = init_VehicleStatus_from_ASN(src->dataSet, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_Snapshot_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_VehicleClassification* init_VehicleClassification_from_ASN(VehicleClassification* src, Dz1Error* errp)
{
	Gitsn_VehicleClassification* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_VehicleClassification_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_VehicleClassification_delAndSetNull, (void*)&ret);

		if (src->DEF_VehicleClassification_keyType)
		{
			ret->keyType = src->keyType;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleClassification_role)
		{
			if ((ret->role = (Gitsn_BasicVehicleRole)src->role) > Gitsn_BasicVehicleRole_max) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleClassification_iso3883)
		{
			ret->iso3883 = src->iso3883;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleClassification_hpmsType)
		{
			if ((ret->hpmsType = (Gitsn_VehicleType)src->hpmsType) > Gitsn_VehicleType_max) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleClassification_vehicleType)
		{
			if ((ret->vehicleType = (Gitsn_VehicleGroupAffected)src->vehicleType) > Gitsn_VehicleGroupAffected_max) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleClassification_responseEquip)
		{
			if ((ret->responseEquip = (Gitsn_IncidentResponseEquipment)src->responseEquip) > Gitsn_IncidentResponseEquipment_max) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleClassification_responderType)
		{
			if ((ret->responderType = (Gitsn_ResponderGroupAffected)src->responderType) > Gitsn_ResponderGroupAffected_max) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleClassification_fuelType)
		{
			ret->fuelType = src->fuelType;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_VehicleClassification_regional) {}

		pthread_cleanup_pop(errp->code); // (Gitsn_VehicleClassification_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_ProbeVehicleData_snapshots* init_ProbeVehicleData_snapshots_from_ASN(ProbeVehicleData_snapshots* src, Dz1Error* errp)
{
	Gitsn_ProbeVehicleData_snapshots* ret = NULL;
	if (src == NULL || src->count == 0) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_ProbeVehicleData_snapshots_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_ProbeVehicleData_snapshots_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			Snapshot* src_element = ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				Gitsn_Snapshot* _element = NULL;
				if ((_element = init_Snapshot_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else
				{
					pthread_cleanup_push(Gitsn_Snapshot_delAndSetNull, (void*)&_element);
					if (0) {}
					else if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
					else
					{
						_element = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (Gitsn_Snapshot_delAndSetNull, (void*)&_element);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_ProbeVehicleData_snapshots_delAndSetNull, (void*)&ret);
	}
	return ret;
}

bool_t GitsnAsnUtil_Gitsn_ProbeVehicleDataFromASN(ProbeVehicleData* src, Gitsn_ProbeVehicleData* dst, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || dst == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		if (src->DEF_ProbeVehicleData_timeStamp)
			dst->timeStamp = src->timeStamp;

		if (src->DEF_ProbeVehicleData_segNum) dst->segNum = src->segNum;

		if (src->DEF_ProbeVehicleData_probeID)
		{
			if ((dst->probeID = init_VehicleIdent_from_ASN(src->probeID, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}

		if (src->DEF_ProbeVehicleData_regional) {}

		if ((dst->startVector = init_FullPositionVector_from_ASN(src->startVector, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((dst->vehicleType = init_VehicleClassification_from_ASN(src->vehicleType, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((dst->snapshots = init_ProbeVehicleData_snapshots_from_ASN(&src->snapshots, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{

			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}


static Gitsn_EnabledLaneList* init_EnabledLaneList_from_ASN(EnabledLaneList* src, Dz1Error* errp)
{
	Gitsn_EnabledLaneList* ret = NULL;
	if (src == NULL || src->count == 0) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_EnabledLaneList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_EnabledLaneList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			LaneID* src_element = ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				LaneID _element = *src_element;
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_EnabledLaneList_delAndSetNull, (void*)&ret)
	}
	return ret;
}

static Gitsn_ConnectionManeuverAssist* init_ConnectionManeuverAssist_from_ASN(ConnectionManeuverAssist* src, Dz1Error* errp)
{
	Gitsn_ConnectionManeuverAssist* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	if ((ret = Gitsn_ConnectionManeuverAssist_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_ConnectionManeuverAssist_delAndSetNull, (void*)&ret);
		if (0) {}
		if (src->DEF_ConnectionManeuverAssist_queueLength)
		{
			ret->queueLength = src->queueLength;
		}
		if (src->DEF_ConnectionManeuverAssist_availableStorageLength)
		{
			ret->availableStorageLength = src->availableStorageLength;
		}
		if (src->DEF_ConnectionManeuverAssist_waitOnStop)
		{
			ret->waitOnStop = src->waitOnStop;
		}
		if (src->DEF_ConnectionManeuverAssist_pedBicycleDetect)
		{
			ret->pedBicycleDetect = src->pedBicycleDetect;
		}
		if (src->DEF_ConnectionManeuverAssist_regional) {}

		ret->connectionID = src->connectionID;
		Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Gitsn_ConnectionManeuverAssist_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_ManeuverAssistList* init_ManeuverAssistList_from_ASN(ManeuverAssistList* src, Dz1Error* errp)
{
	Gitsn_ManeuverAssistList* ret = NULL;
	if (src == NULL || src->count == 0) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_ManeuverAssistList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Gitsn_ConnectionManeuverAssist* _element = NULL;
		pthread_cleanup_push(Gitsn_ManeuverAssistList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			ConnectionManeuverAssist* src_element = ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((_element = init_ConnectionManeuverAssist_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				pthread_cleanup_push(Gitsn_ConnectionManeuverAssist_delAndSetNull, (void*)&_element);
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else
				{
					_element = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (Gitsn_ConnectionManeuverAssist_delAndSetNull, (void*)&_element);
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_ManeuverAssistList_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_IntersectionReferenceID* init_IntersectionReferenceID_from_ASN(IntersectionReferenceID* src, Dz1Error* errp)
{
	Gitsn_IntersectionReferenceID* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_IntersectionReferenceID_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_IntersectionReferenceID_delAndSetNull, (void*)&ret);
		ret->region = src->region;
		ret->id = src->id;
		Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Gitsn_IntersectionReferenceID_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_TimeChangeDetails* init_TimeChangeDetails_from_ASN(TimeChangeDetails* src, Dz1Error* errp)
{
	Gitsn_TimeChangeDetails* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_TimeChangeDetails_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_TimeChangeDetails_delAndSetNull, (void*)&ret);
		if (src->DEF_TimeChangeDetails_startTime) { ret->startTime = src->startTime; }
		if (src->DEF_TimeChangeDetails_maxEndTime) { ret->maxEndTime = src->maxEndTime; }
		if (src->DEF_TimeChangeDetails_likelyTime) { ret->likelyTime = src->likelyTime; }
		if (src->DEF_TimeChangeDetails_confidence) { ret->confidence = src->confidence; }
		if (src->DEF_TimeChangeDetails_nextTime) { ret->nextTime = src->nextTime; }

		ret->minEndTime = src->minEndTime;
		Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Gitsn_TimeChangeDetails_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_AdvisorySpeed* init_AdvisorySpeed_from_ASN(AdvisorySpeed* src, Dz1Error* errp)
{
	Gitsn_AdvisorySpeed* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_AdvisorySpeed_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_AdvisorySpeed_delAndSetNull, (void*)&ret);
		if (0) {}
		if (src->DEF_AdvisorySpeed_speed) { ret->speed = src->speed; }
		if (src->DEF_AdvisorySpeed_confidence) {
			ret->confidence = (Gitsn_SpeedConfidence)src->confidence;
		}
		if (src->DEF_AdvisorySpeed_distance) { ret->distance = src->distance; }
		if (src->DEF_AdvisorySpeed_class) { ret->class = src->class; }
		if (src->DEF_AdvisorySpeed_regional) {}

		if (0) {}
		else
		{
			ret->type = (Gitsn_AdvisorySpeedType)src->type;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Gitsn_AdvisorySpeed_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_AdvisorySpeedList* init_AdvisorySpeedList_from_ASN(AdvisorySpeedList* src, Dz1Error* errp)
{
	Gitsn_AdvisorySpeedList* ret = NULL;
	if (src == NULL || src->count == 0) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_AdvisorySpeedList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_AdvisorySpeedList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			AdvisorySpeed* src_element = ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				Gitsn_AdvisorySpeed* _element = NULL;
				if ((_element = init_AdvisorySpeed_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else
				{
					pthread_cleanup_push(Gitsn_AdvisorySpeed_delAndSetNull, (void*)&_element);
					if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
					else
					{
						_element = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); (Gitsn_AdvisorySpeed_delAndSetNull, (void*)&_element);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_AdvisorySpeedList_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_MovementEvent* init_MovementEvent_from_ASN(MovementEvent* src, Dz1Error* errp)
{
	Gitsn_MovementEvent* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_MovementEvent_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_MovementEvent_delAndSetNull, (void*)&ret);
		if (src->DEF_MovementEvent_timing)
		{
			if ((ret->timing = init_TimeChangeDetails_from_ASN(src->timing, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_MovementEvent_speeds)
		{
			if ((ret->speeds = init_AdvisorySpeedList_from_ASN(&src->speeds, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_MovementEvent_regional) {}

		if (0) {}
		else
		{
			ret->eventState = (Gitsn_MovementPhaseState)src->eventState;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_MovementEvent_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_MovementEventList* init_MovementEventList_from_ASN(MovementEventList* src, Dz1Error* errp)
{
	Gitsn_MovementEventList* ret = NULL;
	if (src == NULL || src->count == 0) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_MovementEventList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_MovementEventList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			MovementEvent* src_element = ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				Gitsn_MovementEvent* _element = NULL;
				if ((_element = init_MovementEvent_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else
				{
					pthread_cleanup_push(Gitsn_MovementEvent_delAndSetNull, (void*)&_element);
					if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
					else
					{
						_element = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (Gitsn_MovementEvent_delAndSetNull, (void*)&_element);
				}
			}
		}
		pthread_cleanup_pop(errp->code);// (Gitsn_MovementEventList_delAndSetNull, (void*)&ret);
	}

	return ret;
}

static Gitsn_MovementState* init_MovementState_from_ASN(MovementState* src, Dz1Error* errp)
{
	Gitsn_MovementState* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_MovementState_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_MovementState_delAndSetNull, (void*)&ret);
		if (0) {}
		if (src->DEF_MovementState_movementName)
		{
			if ((ret->movementName = Dz1Str_ndup(src->movementName.asnstring, src->movementName.nchar, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_MovementState_maneuverAssistList)
		{
			if ((ret->maneuverAssistList = init_ManeuverAssistList_from_ASN(&src->maneuverAssistList, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_MovementState_regional) {}

		if (0) {}
		else if ((ret->state_time_speed = init_MovementEventList_from_ASN(&src->state_time_speed, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			ret->signalGroup = src->signalGroup;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Gitsn_MovementState_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_MovementList* init_MovementList_from_ASN(MovementList* src, Dz1Error* errp)
{
	Gitsn_MovementList* ret = NULL;
	if (src == NULL || src->count == 0) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_MovementList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_MovementList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			MovementState* src_element = ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				Gitsn_MovementState* _element = NULL;
				if ((_element = init_MovementState_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else
				{
					pthread_cleanup_push(Gitsn_MovementState_delAndSetNull, (void*)&_element);
					if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
					else
					{
						_element = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); (Gitsn_MovementState_delAndSetNull, (void*)&_element);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_MovementList_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_IntersectionState* init_IntersectionState_from_ASN(IntersectionState* src, Dz1Error* errp)
{
	Gitsn_IntersectionState* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_IntersectionState_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_IntersectionState_delAndSetNull, (void*)&ret);
		if (0) {}
		if (src->DEF_IntersectionState_name)
		{
			if ((ret->name = Dz1Str_ndup(src->name.asnstring, src->name.nchar, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_IntersectionState_moy)
		{
			ret->moy = src->moy;
		}
		if (src->DEF_IntersectionState_timeStamp)
		{
			ret->timeStamp = src->timeStamp;
		}
		if (src->DEF_IntersectionState_enabledLanes)
		{
			if ((ret->enabledLanes = init_EnabledLaneList_from_ASN(&src->enabledLanes, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_IntersectionState_maneuverAssistList)
		{
			if ((ret->maneuverAssistList = init_ManeuverAssistList_from_ASN(&src->maneuverAssistList, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_IntersectionState_regional)
		{
		}

		if (0) {}
		else if ((ret->id = init_IntersectionReferenceID_from_ASN(src->id, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->states = init_MovementList_from_ASN(&src->states, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			size_t sz = src->status.numbits + 7 / 8;
			if ((ret->status = Dz1Calloc(sz, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (memcpy(ret->status, src->status.data, sz) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Gitsn_IntersectionState_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_IntersectionStateList* init_IntersectionStateList_from_ASN(IntersectionStateList* src, Dz1Error* errp)
{
	Gitsn_IntersectionStateList* ret = NULL;
	if (src == NULL || src->count == 0) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_IntersectionStateList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_IntersectionStateList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			IntersectionState* src_element = ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				Gitsn_IntersectionState* _element = NULL;
				if ((_element = init_IntersectionState_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else
				{
					pthread_cleanup_push(Gitsn_IntersectionState_delAndSetNull, (void*)&_element);
					if (0) {}
					else if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
					else
					{
						_element = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (Gitsn_IntersectionState_DelAndSetNull, (void*)&_element);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_IntersectionStateList_delAndSetNull, (void*)&ret);
	}
	return ret;
}

bool_t GitsnAsnUtil_Gitsn_SPATFromASN(SPAT* src, Gitsn_SPAT* dst, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || dst == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		if (src->DEF_SPAT_timeStamp)
		{
			dst->timeStamp = src->timeStamp;
		}
		if (src->DEF_SPAT_name)
		{
			if ((dst->name = Dz1Str_ndup(src->name.asnstring, src->name.nchar, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);

		}
		if (src->DEF_SPAT_regional) {}

		if (0) {}
		else if ((dst->intersections = init_IntersectionStateList_from_ASN(&src->intersections, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);

	}

	return ERR_IS_SUCCESS(errp);
}



bool_t GitsnAsnUtil_Gitsn_RoadSideAlertFromASN(RoadSideAlert* src, Gitsn_RoadSideAlert* dst, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || dst == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		dst->msgCnt = src->msgCnt;
		dst->typeEvent = src->msgCnt;

		if (src->DEF_RoadSideAlert_timeStamp)
		{
			dst->timeStamp = src->timeStamp;
		}

		if (src->DEF_RoadSideAlert_description)
		{
			Gitsn_RoadSideAlert_description* desc = NULL;
			if ((desc = dst->description = Gitsn_RoadSideAlert_description_new(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				for (int i = 1; i <= (int)src->description.count;i++)
				{
					ITIScodes* node = ASN1_Get_Node_Index((ASN1List*)&src->description, i);
					desc->add(desc, *node);
					Dz1Error_set(errp, 0);
				}
			}
		}
		if (src->DEF_RoadSideAlert_priority)
		{
			if ((dst->priority = Dz1Str_ndup(src->priority.data, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_RoadSideAlert_heading)
		{
			size_t sz = (src->heading.numbits + 7) / 8;
			if ((dst->heading = Dz1Calloc(sz, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((dst->heading = memcpy(dst->heading, src->heading.data, sz)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_RoadSideAlert_extent) {
			dst->extent = (Gitsn_Extent)src->extent;
		}
		if (src->DEF_RoadSideAlert_position)
		{
			if ((dst->position = init_FullPositionVector_from_ASN(src->position, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_RoadSideAlert_furtherInfoID)
		{
			/*if ((dst->furtherInfoID = Dz1Str_ndup(src->furtherInfoID.data, 2, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);*/

			u8_t* dp = src->furtherInfoID.data;
			dst->furtherInfoID = 0;
			dst->furtherInfoID = (dst->furtherInfoID << 8) | (u16_t)(*dp & 0xFF); dp++;
			dst->furtherInfoID = (dst->furtherInfoID << 8) | (u16_t)(*dp & 0xFF); dp++;
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_RoadSideAlert_regional) {}
	}
	if (errp->code == 0)
	{
		Gitsn_RoadSideAlert_dump(dst, 4);

	}
	return ERR_IS_SUCCESS(errp);
}


static Gitsn_Position3D* init_Position3D_from_ASN(Position3D* src, Dz1Error* errp)
{
	Gitsn_Position3D* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Position3D_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_Position3D_delAndSetNull, (void*)&ret);
		ret->lat = src->lat;
		ret->lon = src->lon;
		if (src->DEF_Position3D_elevation)
		{
			ret->elevation = src->elevation;
		}
		if (src->DEF_Position3D_regional)
		{
		}
		Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Gitsn_Position3D_delAndSetNull, (void*)&ret);
	}
	return ret;
}



static Gitsn_RoadSignID* init_RoadSignID_from_ASN(RoadSignID* src, Dz1Error* errp)
{
	Gitsn_RoadSignID* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_RoadSignID_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_RoadSignID_delAndSetNull, (void*)&ret);
		if ((ret->position = init_Position3D_from_ASN((Position3D*)&src->position, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			if ((ret->viewAngle = Dz1Calloc(2, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (memcpy(ret->viewAngle, src->viewAngle.data, 2) == NULL) ERR_SET_OUT(errp, EFAULT);
			Dz1Error_set(errp, 0);
		}
		if (src->DEF_RoadSignID_mutcdCode)
		{
			ret->mutcdCode = (Gitsn_MUTCDCode)src->mutcdCode;
		}
		if (src->DEF_RoadSignID_crc)
		{
			if ((ret->crc = Dz1Str_ndup(src->crc.data, 2, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_RoadSignID_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_TravelerDataFrame_msgId* init_TravelerDataFrame_msgId_from_ASN(TravelerDataFrame_msgId* src, Dz1Error* errp)
{
	Gitsn_TravelerDataFrame_msgId* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_TravelerDataFrame_msgId_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_TravelerDataFrame_msgId_delAndSetNull, (void*)&ret);
		switch (src->M)
		{
		case DEF_TravelerDataFrame_msgId_furtherInfoID:
			{
			u8_t* dp = src->elements.furtherInfoID.data;
			ret->x.furtherInfoID = 0;
			ret->x.furtherInfoID = (ret->x.furtherInfoID << 8) | (u16_t)(*dp & 0xFF); dp++;
			ret->x.furtherInfoID = (ret->x.furtherInfoID << 8) | (u16_t)(*dp & 0xFF); dp++;

				ret->present = Gitsn_TravelerDataFrame_msgIdPresent_furtherInfoID;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_TravelerDataFrame_msgId_roadSignID:
			if ((ret->x.roadSignID = init_RoadSignID_from_ASN((RoadSignID*)&src->elements.roadSignID, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
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

static Gitsn_RoadSegmentReferenceID* init_RoadSegmentReferenceID_from_ASN(RoadSegmentReferenceID* src, Dz1Error* errp)
{
	Gitsn_RoadSegmentReferenceID* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_RoadSegmentReferenceID_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_RoadSegmentReferenceID_delAndSetNull, (void*)&ret);
		ret->id = src->id;
		if (src->DEF_RoadSegmentReferenceID_region)
		{
			ret->region = src->region;
		}
		Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Gitsn_RoadSegmentReferenceID_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_NodeOffsetPointXY* init_NodeOffsetPointXY_from_ASN(NodeOffsetPointXY* src, Dz1Error* errp)
{
	Gitsn_NodeOffsetPointXY* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_NodeOffsetPointXY_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_NodeOffsetPointXY_delAndSetNull, (void*)&ret);
		switch (src->M)
		{
		case DEF_NodeOffsetPointXY_node_XY1:
			if ((ret->x.node_XY1 = Gitsn_Node_XY_20b_new(src->elements.node_XY1->x, src->elements.node_XY1->y, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_NodeOffsetPointXYPresent_node_XY1;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_NodeOffsetPointXY_node_XY2:
			if ((ret->x.node_XY2 = Gitsn_Node_XY_22b_new(src->elements.node_XY2->x, src->elements.node_XY2->y, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_NodeOffsetPointXYPresent_node_XY2;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_NodeOffsetPointXY_node_XY3:
			if ((ret->x.node_XY3 = Gitsn_Node_XY_24b_new(src->elements.node_XY3->x, src->elements.node_XY3->y, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_NodeOffsetPointXYPresent_node_XY3;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_NodeOffsetPointXY_node_XY4:
			if ((ret->x.node_XY4 = Gitsn_Node_XY_26b_new(src->elements.node_XY4->x, src->elements.node_XY4->y, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_NodeOffsetPointXYPresent_node_XY4;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_NodeOffsetPointXY_node_XY5:
			if ((ret->x.node_XY5 = Gitsn_Node_XY_28b_new(src->elements.node_XY5->x, src->elements.node_XY5->y, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_NodeOffsetPointXYPresent_node_XY5;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_NodeOffsetPointXY_node_XY6:
			if ((ret->x.node_XY6 = Gitsn_Node_XY_32b_new(src->elements.node_XY6->x, src->elements.node_XY6->y, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_NodeOffsetPointXYPresent_node_XY6;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_NodeOffsetPointXY_node_LatLon:
			if ((ret->x.node_LatLon = Gitsn_Node_LLmD_64b_new(src->elements.node_LatLon->lon, src->elements.node_LatLon->lat, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_NodeOffsetPointXYPresent_node_LatLon;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_NodeOffsetPointXY_regional:
		{}
		break;
		default:
			ERR_SET_OUT(errp, EPERM);
			break;
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_NodeOffsetPointXY_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_NodeAttributeXYList* init_NodeAttributeXYList_from_ASN(NodeAttributeXYList* src, Dz1Error* errp)
{
	Gitsn_NodeAttributeXYList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_NodeAttributeXYList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_NodeAttributeXYList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			NodeAttributeXY* src_element = (NodeAttributeXY*)ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				Gitsn_NodeAttributeXY _element = (Gitsn_NodeAttributeXY)*src_element;
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else
				{
					// free(src_element);
					Dz1Error_set(errp, 0);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_NodeAttributeXYList_delAndSetNull, (void*)&ret);
	}

	return ret;
}

static Gitsn_SegmentAttributeXYList* init_SegmentAttributeXYList_from_ASN(SegmentAttributeXYList* src, Dz1Error* errp)
{
	Gitsn_SegmentAttributeXYList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_SegmentAttributeXYList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Gitsn_SegmentAttributeXY _element;
		pthread_cleanup_push(Gitsn_SegmentAttributeXYList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			SegmentAttributeXY* src_element = (SegmentAttributeXY*)ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				_element = (Gitsn_SegmentAttributeXY)src_element;
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_SegmentAttributeXYList_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_RegulatorySpeedLimit* init_RegulatorySpeedLimit_from_ASN(RegulatorySpeedLimit* src, Dz1Error* errp)
{
	Gitsn_RegulatorySpeedLimit* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_RegulatorySpeedLimit_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_RegulatorySpeedLimit_delAndSetNull, (void*)&ret);
		ret->type = (Gitsn_SpeedLimitType)src->type;
		ret->speed = src->speed;
		Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Gitsn_RegulatorySpeedLimit_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_SpeedLimitList* init_SpeedLimitList_from_ASN(SpeedLimitList* src, Dz1Error* errp)
{
	Gitsn_SpeedLimitList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_SpeedLimitList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Gitsn_RegulatorySpeedLimit* _element = NULL;
		pthread_cleanup_push(Gitsn_SpeedLimitList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			RegulatorySpeedLimit* src_element = (RegulatorySpeedLimit*)ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((_element = init_RegulatorySpeedLimit_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				pthread_cleanup_push(Gitsn_RegulatorySpeedLimit_delAndSetNull, (void*)&_element);
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else
				{
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

static Gitsn_LaneDataAttribute* init_LaneDataAttribute_from_ASN(LaneDataAttribute* src, Dz1Error* errp)
{
	Gitsn_LaneDataAttribute* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_LaneDataAttribute_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_LaneDataAttribute_delAndSetNull, (void*)&ret);
		switch (src->M)
		{
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
			if ((ret->x.speedLimits = init_SpeedLimitList_from_ASN((SpeedLimitList*)&src->elements.speedLimits, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_LaneDataAttributePresent_speedLimits;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_LaneDataAttribute_regional:
			break;
		default: ERR_SET_OUT(errp, EPERM);break;
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_LaneDataAttribute_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_LaneDataAttributeList* init_LaneDataAttributeList_from_ASN(LaneDataAttributeList* src, Dz1Error* errp)
{
	Gitsn_LaneDataAttributeList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_LaneDataAttributeList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Gitsn_LaneDataAttribute* _element = NULL;
		pthread_cleanup_push(Gitsn_LaneDataAttributeList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			LaneDataAttribute* src_element = (LaneDataAttribute*)ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((_element = init_LaneDataAttribute_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				pthread_cleanup_push(Gitsn_LaneDataAttribute_delAndSetNull, (void*)&_element);
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else
				{
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

static Gitsn_NodeAttributeSetXY* init_NodeAttributeSetXY_from_ASN(NodeAttributeSetXY* src, Dz1Error* errp)
{
	Gitsn_NodeAttributeSetXY* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_NodeAttributeSetXY_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_NodeAttributeSetXY_delAndSetNull, (void*)&ret);
		if (src->DEF_NodeAttributeSetXY_localNode)
		{
			if ((ret->localNode = init_NodeAttributeXYList_from_ASN((NodeAttributeXYList*)&src->localNode, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_NodeAttributeSetXY_disabled)
		{
			if ((ret->disabled = init_SegmentAttributeXYList_from_ASN((SegmentAttributeXYList*)&src->disabled, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_NodeAttributeSetXY_enabled)
		{
			if ((ret->enabled = init_SegmentAttributeXYList_from_ASN((SegmentAttributeXYList*)&src->enabled, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_NodeAttributeSetXY_data)
		{
			if ((ret->data = init_LaneDataAttributeList_from_ASN((LaneDataAttributeList*)&src->data, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_NodeAttributeSetXY_dWidth)
		{
			ret->dWidth = src->dWidth;
		}
		if (src->DEF_NodeAttributeSetXY_dElevation)
		{
			ret->dElevation = src->dElevation;
		}
		if (src->DEF_NodeAttributeSetXY_regional) {}
		pthread_cleanup_pop(errp->code); // (Gitsn_NodeAttributeSetXY_delAndSetNull, (void*)&ret);
	}
	return ret;
}


static Gitsn_NodeXY* init_NodeXY_from_ASN(NodeXY* src, Dz1Error* errp)
{
	Gitsn_NodeXY* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_NodeXY_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_NodeXY_delAndSetNull, (void*)&ret);
		if ((ret->delta = init_NodeOffsetPointXY_from_ASN(src->delta, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			if (src->DEF_NodeXY_attributes)
			{
				if ((ret->attributes = init_NodeAttributeSetXY_from_ASN(src->attributes, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_NodeXY_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_NodeSetXY* init_NodeSetXY_from_ASN(NodeSetXY* src, Dz1Error* errp)
{
	Gitsn_NodeSetXY* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_NodeSetXY_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Gitsn_NodeXY* _element = NULL;
		pthread_cleanup_push(Gitsn_NodeSetXY_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			NodeXY* src_element = (NodeXY*)ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((_element = init_NodeXY_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				pthread_cleanup_push(Gitsn_NodeXY_delAndSetNull, (void*)&_element);
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else
				{
					_element = NULL;
					// free(src_element);
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1);(Gitsn_NodeXY_delAndSetNull, (void*)&_element);
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_NodeSetXY_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_ComputedLane_offsetXaxis* init_ComputedLane_offsetXaxis_from_ASN(ComputedLane_offsetXaxis* src, Dz1Error* errp)
{
	Gitsn_ComputedLane_offsetXaxis* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_ComputedLane_offsetXaxis_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_ComputedLane_offsetXaxis_delAndSetNull, (void*)&ret);
		switch (src->M)
		{
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
		default: ERR_SET_OUT(errp, EPERM); break;

		}
		pthread_cleanup_pop(errp->code); // (Gitsn_ComputedLane_offsetXaxis_delAndSetNull, (void*)&ret);
	}
	return ret;
}


static Gitsn_ComputedLane_offsetYaxis* init_ComputedLane_offsetYaxis_from_ASN(ComputedLane_offsetYaxis* src, Dz1Error* errp)
{
	Gitsn_ComputedLane_offsetYaxis* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_ComputedLane_offsetYaxis_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_ComputedLane_offsetYaxis_delAndSetNull, (void*)&ret);
		switch (src->M)
		{
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
		default: ERR_SET_OUT(errp, EPERM); break;

		}
		pthread_cleanup_pop(errp->code); // (Gitsn_ComputedLane_offsetYaxis_delAndSetNull, (void*)&ret);
	}
	return ret;
}


static Gitsn_ComputedLane* init_ComputedLane_from_ASN(ComputedLane* src, Dz1Error* errp)
{
	Gitsn_ComputedLane* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_ComputedLane_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_ComputedLane_delAndSetNull, (void*)&ret);
		ret->referenceLaneId = src->referenceLaneId;
		if ((ret->offsetXaxis = init_ComputedLane_offsetXaxis_from_ASN(src->offsetXaxis, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->offsetYaxis = init_ComputedLane_offsetYaxis_from_ASN(src->offsetYaxis, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			if (src->DEF_ComputedLane_rotateXY)
			{
				ret->rotateXY = src->rotateXY;
			}
			if (src->DEF_ComputedLane_scaleXaxis)
			{
				ret->scaleXaxis = src->scaleXaxis;
			}
			if (src->DEF_ComputedLane_scaleYaxis)
			{
				ret->scaleYaxis = src->scaleYaxis;
			}
			if (src->DEF_ComputedLane_regional) {}
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_ComputedLane_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_NodeListXY* init_NodeListXY_from_ASN(NodeListXY* src, Dz1Error* errp)
{
	Gitsn_NodeListXY* ret = NULL;

	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_NodeListXY_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_NodeListXY_delAndSetNull, (void*)&ret);
		switch (src->M)
		{
		case DEF_NodeListXY_nodes:
			if ((ret->x.nodes = init_NodeSetXY_from_ASN((NodeSetXY*)&src->elements.nodes, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_NodeListXYPresent_nodes;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_NodeListXY_computed:
			if ((ret->x.computed = init_ComputedLane_from_ASN(src->elements.computed, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_NodeListXYPresent_computed;
				Dz1Error_set(errp, 0);
			}
			break;
		default: ERR_SET_OUT(errp, EPERM); break;
		}

		pthread_cleanup_pop(errp->code); // (Gitsn_NodeListXY_delAndSetNull, (void*)&ret);
	}

	return ret;
}


static Gitsn_NodeOffsetPointLL* init_NodeOffsetPointLL_from_ASN(NodeOffsetPointLL* src, Dz1Error* errp)
{
	Gitsn_NodeOffsetPointLL* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_NodeOffsetPointLL_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_NodeOffsetPointLL_delAndSetNull, (void*)&ret);
		switch (src->M)
		{
		case DEF_NodeOffsetPointLL_node_LL1:
			if ((ret->x.node_LL1 = Gitsn_Node_LL_24B_new(src->elements.node_LL1->lon, src->elements.node_LL1->lat, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_NodeOffsetPointLLPresent_node_LL1;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_NodeOffsetPointLL_node_LL2:
			if ((ret->x.node_LL2 = Gitsn_Node_LL_28B_new(src->elements.node_LL2->lon, src->elements.node_LL2->lat, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_NodeOffsetPointLLPresent_node_LL2;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_NodeOffsetPointLL_node_LL3:
			if ((ret->x.node_LL3 = Gitsn_Node_LL_32B_new(src->elements.node_LL3->lon, src->elements.node_LL3->lat, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_NodeOffsetPointLLPresent_node_LL3;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_NodeOffsetPointLL_node_LL4:
			if ((ret->x.node_LL4 = Gitsn_Node_LL_36B_new(src->elements.node_LL4->lon, src->elements.node_LL4->lat, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_NodeOffsetPointLLPresent_node_LL4;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_NodeOffsetPointLL_node_LL5:
			if ((ret->x.node_LL5 = Gitsn_Node_LL_44B_new(src->elements.node_LL5->lon, src->elements.node_LL5->lat, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_NodeOffsetPointLLPresent_node_LL5;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_NodeOffsetPointLL_node_LL6:
			if ((ret->x.node_LL6 = Gitsn_Node_LL_48B_new(src->elements.node_LL6->lon, src->elements.node_LL6->lat, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_NodeOffsetPointLLPresent_node_LL6;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_NodeOffsetPointLL_node_LatLon:
			if ((ret->x.node_LatLon = Gitsn_Node_LLmD_64b_new(src->elements.node_LatLon->lon, src->elements.node_LatLon->lat, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_NodeOffsetPointLLPresent_node_LatLon;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_NodeOffsetPointLL_regional:
		{}
		break;
		default:
			ERR_SET_OUT(errp, EPERM);
			break;
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_NodeOffsetPointLL_delAndSetNull, (void*)&ret);
	}
	return ret;
}


static Gitsn_NodeAttributeLLList* init_NodeAttributeLLList_from_ASN(NodeAttributeLLList* src, Dz1Error* errp)
{
	Gitsn_NodeAttributeLLList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_NodeAttributeLLList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_NodeAttributeLLList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			NodeAttributeLL* src_element = (NodeAttributeLL*)ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				Gitsn_NodeAttributeLL _element = (Gitsn_NodeAttributeLL)*src_element;
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else
				{
					// free(src_element);
					Dz1Error_set(errp, 0);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_NodeAttributeLLList_delAndSetNull, (void*)&ret);
	}

	return ret;
}

static Gitsn_SegmentAttributeLLList* init_SegmentAttributeLLList_from_ASN(SegmentAttributeLLList* src, Dz1Error* errp)
{
	Gitsn_SegmentAttributeLLList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_SegmentAttributeLLList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Gitsn_SegmentAttributeLL _element;
		pthread_cleanup_push(Gitsn_SegmentAttributeLLList_delAndSetNull, (void*)&ret);
		for (int i = 1; (int)src->count; i++)
		{
			SegmentAttributeLL* src_element = (SegmentAttributeLL*)ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				_element = (Gitsn_SegmentAttributeLL)*src_element;
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_SegmentAttributeLLList_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_NodeAttributeSetLL* init_NodeAttributeSetLL_from_ASN(NodeAttributeSetLL* src, Dz1Error* errp)
{
	Gitsn_NodeAttributeSetLL* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_NodeAttributeSetLL_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_NodeAttributeSetLL_delAndSetNull, (void*)&ret);
		if (src->DEF_NodeAttributeSetLL_localNode)
		{
			if ((ret->localNode = init_NodeAttributeLLList_from_ASN((NodeAttributeLLList*)&src->localNode, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_NodeAttributeSetLL_disabled)
		{
			if ((ret->disabled = init_SegmentAttributeLLList_from_ASN((SegmentAttributeLLList*)&src->disabled, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_NodeAttributeSetLL_enabled)
		{
			if ((ret->enabled = init_SegmentAttributeLLList_from_ASN((SegmentAttributeLLList*)&src->disabled, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_NodeAttributeSetLL_data)
		{
			if ((ret->data = init_LaneDataAttributeList_from_ASN((LaneDataAttributeList*)&src->data, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_NodeAttributeSetLL_dWidth)
		{
			ret->dWidth = src->dWidth;
		}
		if (src->DEF_NodeAttributeSetLL_dElevation)
		{
			ret->dElevation = src->dElevation;
		}
		if (src->DEF_NodeAttributeSetLL_regional) {}
		pthread_cleanup_pop(errp->code); // (Gitsn_NodeAttributeSetLL_delAndSetNull, (void*)&ret);
	}
	return ret;
}


static Gitsn_NodeLL* init_NodeLL_from_ASN(NodeLL* src, Dz1Error* errp)
{
	Gitsn_NodeLL* ret = NULL;

	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_NodeLL_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_NodeLL_delAndSetNull, (void*)&ret);
		// gm
		if ((ret->delta = init_NodeOffsetPointLL_from_ASN(src->delta, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			if (src->DEF_NodeLL_attributes)
			{
				if ((ret->attributes = init_NodeAttributeSetLL_from_ASN(src->attributes, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_NodeLL_delAndSetNull, (void*)&ret);
	}

	return ret;
}

static Gitsn_NodeSetLL* init_NodeSetLL_from_ASN(NodeSetLL* src, Dz1Error* errp)
{
	Gitsn_NodeSetLL* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_NodeSetLL_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Gitsn_NodeLL* _element = NULL;
		pthread_cleanup_push(Gitsn_NodeSetLL_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			NodeLL* src_element = (NodeLL*)ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((_element = init_NodeLL_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				pthread_cleanup_push(Gitsn_NodeLL_delAndSetNull, (void*)&_element);
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else
				{
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

static Gitsn_NodeListLL* init_NodeListLL_from_ASN(NodeListLL* src, Dz1Error* errp)
{
	Gitsn_NodeListLL* ret = NULL;

	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_NodeListLL_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_NodeListLL_delAndSetNull, (void*)&ret);
		switch (src->M)
		{
		case DEF_NodeListLL_nodes:
			if ((ret->x.nodes = init_NodeSetLL_from_ASN((NodeSetLL*)&src->elements.nodes, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_NodeListLLPresent_nodes;
				Dz1Error_set(errp, 0);
			}
			break;
		default: ERR_SET_OUT(errp, EPERM);
			break;
		}

		pthread_cleanup_pop(errp->code); // (Gitsn_NodeListLL_delAndSetNull, (void*)&ret);
	}

	return ret;
}

static Gitsn_OffsetSystem_offset* init_OffsetSystem_offset_from_ASN(OffsetSystem_offset* src, Dz1Error* errp)
{
	Gitsn_OffsetSystem_offset* ret = NULL;

	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_OffsetSystem_offset_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_OffsetSystem_offset_delAndSetNull, (void*)&ret);
		switch (src->M)
		{
		case DEF_OffsetSystem_offset_xy:
			if ((ret->x.xy = init_NodeListXY_from_ASN(src->elements.xy, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_OffsetSystem_offsetPresent_xy;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_OffsetSystem_offset_ll:
			if ((ret->x.ll = init_NodeListLL_from_ASN(src->elements.ll, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
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


static Gitsn_OffsetSystem* init_OffsetSystem_from_ASN(OffsetSystem* src, Dz1Error* errp)
{
	Gitsn_OffsetSystem* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_OffsetSystem_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_OffsetSystem_delAndSetNull, (void*)&ret);
		if ((ret->offset = init_OffsetSystem_offset_from_ASN(src->offset, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			if (src->DEF_OffsetSystem_scale)
				ret->scale = src->scale;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_OffsetSystem_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Circle* init_Circle_from_ASN(Circle* src, Dz1Error* errp)
{
	Gitsn_Circle* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Circle_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_Circle_delAndSetNull, (void*)&ret);
		if ((ret->center = init_Position3D_from_ASN(src->center, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			ret->radius = src->radius;
			ret->units = (Gitsn_DistanceUnits)src->units;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_Circle_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_GeometricProjection* init_GeometricProjection_from_ASN(GeometricProjection* src, Dz1Error* errp)
{
	Gitsn_GeometricProjection* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_GeometricProjection_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_GeometricProjection_delAndSetNull, (void*)&ret);
		if ((ret->direction = Dz1Calloc(2, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (memcpy(ret->direction, src->direction.data, 2) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->circle = init_Circle_from_ASN(src->circle, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			if (src->DEF_GeometricProjection_extent)
			{
				ret->extent = (Gitsn_Extent)src->extent;
			}
			if (src->DEF_GeometricProjection_laneWidth)
			{
				ret->laneWidth = src->laneWidth;
			}
			if (src->DEF_GeometricProjection_regional) {}
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_GeometricProjection_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_ShapePointSet* init_ShapePointSet_from_ASN(ShapePointSet* src, Dz1Error* errp)
{
	Gitsn_ShapePointSet* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_ShapePointSet_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_ShapePointSet_delAndSetNull, (void*)&ret);
		if ((ret->nodeList = init_NodeListXY_from_ASN(src->nodeList, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			if (src->DEF_ShapePointSet_anchor)
			{
				if ((ret->anchor = init_Position3D_from_ASN(src->anchor, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
			if (src->DEF_ShapePointSet_laneWidth)
			{
				ret->laneWidth = src->laneWidth;
			}
			if (src->DEF_ShapePointSet_directionality)
			{
				ret->directionality = (Gitsn_DirectionOfUse)src->directionality;
			}
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_ShapePointSet_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_RegionOffsets* init_RegionOffsets_from_ASN(RegionOffsets* src, Dz1Error* errp)
{
	Gitsn_RegionOffsets* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_RegionOffsets_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_RegionOffsets_delAndSetNull, (void*)&ret);
		ret->xOffset = src->xOffset;
		ret->yOffset = src->yOffset;
		if (src->DEF_RegionOffsets_zOffset) ret->zOffset = src->zOffset;
		Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Gitsn_RegionOffsets_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_RegionList* init_RegionList_from_ASN(RegionList* src, Dz1Error* errp)
{
	Gitsn_RegionList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_RegionList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Gitsn_RegionOffsets* _element = NULL;
		pthread_cleanup_push(Gitsn_RegionList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count;i++)
		{
			RegionOffsets* src_element = (RegionOffsets*)ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((_element = init_RegionOffsets_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				pthread_cleanup_push(Gitsn_RegionOffsets_delAndSetNull, (void*)&_element);
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else
				{
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

static Gitsn_RegionPointSet* init_RegionPointSet_from_ASN(RegionPointSet* src, Dz1Error* errp)
{
	Gitsn_RegionPointSet* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_RegionPointSet_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_RegionPointSet_delAndSetNull, (void*)&ret);
		if ((ret->nodeList = init_RegionList_from_ASN((RegionList*)&src->nodeList, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			if (src->DEF_RegionPointSet_anchor)
			{
				if ((ret->anchor = init_Position3D_from_ASN(src->anchor, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
			if (src->DEF_RegionPointSet_scale)
			{
				ret->scale = src->scale;
			}
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_RegionPointSet_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_ValidRegion_area* init_ValidRegion_area_from_ASN(ValidRegion_area* src, Dz1Error* errp)
{
	Gitsn_ValidRegion_area* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_ValidRegion_area_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_ValidRegion_area_delAndSetNull, (void*)&ret);
		switch (src->M)
		{
		case DEF_ValidRegion_area_shapePointSet:
			if ((ret->x.shapePointSet = init_ShapePointSet_from_ASN(src->elements.shapePointSet, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_ValidRegion_areaPresent_shapePointSet;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_ValidRegion_area_circle:
			if ((ret->x.circle = init_Circle_from_ASN(src->elements.circle, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_ValidRegion_areaPresent_circle;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_ValidRegion_area_regionPointSet:
			if ((ret->x.regionPointSet = init_RegionPointSet_from_ASN(src->elements.regionPointSet, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
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

static Gitsn_ValidRegion* init_ValidRegion_from_ASN(ValidRegion* src, Dz1Error* errp)
{
	Gitsn_ValidRegion* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_ValidRegion_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_ValidRegion_delAndSetNull, (void*)&ret);
		if ((ret->direction = Dz1Calloc(2, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (memcpy(ret->direction, src->direction.data, 2) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->area = init_ValidRegion_area_from_ASN(src->area, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			if (src->DEF_ValidRegion_extent)
			{
				ret->extent = (Gitsn_Extent)ret->extent;
			}
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_ValidRegion_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_GeographicalPath_description* init_GeographicalPath_description_from_ASN(GeographicalPath_description* src, Dz1Error* errp)
{
	Gitsn_GeographicalPath_description* ret = NULL;

	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_GeographicalPath_description_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_GeographicalPath_description_delAndSetNull, (void*)&ret);
		switch (src->M)
		{
		case DEF_GeographicalPath_description_path:
			if ((ret->x.path = init_OffsetSystem_from_ASN(src->elements.path, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_GeographicalPath_descriptionPresent_path;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_GeographicalPath_description_geometry:
			if ((ret->x.geometry = init_GeometricProjection_from_ASN(src->elements.geometry, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_GeographicalPath_descriptionPresent_geometry;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_GeographicalPath_description_oldRegion:
			if ((ret->x.oldRegion = init_ValidRegion_from_ASN(src->elements.oldRegion, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
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

static Gitsn_GeographicalPath* init_GeographicalPath_from_ASN(GeographicalPath* src, Dz1Error* errp)
{
	Gitsn_GeographicalPath* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_GeographicalPath_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_GeographicalPath_delAndSetNull, (void*)&ret);
		if (src->DEF_GeographicalPath_name)
		{
			if ((ret->name = Dz1Str_ndup(src->name.asnstring, src->name.nchar, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}

		if (src->DEF_GeographicalPath_id)
		{
			if ((ret->id = init_RoadSegmentReferenceID_from_ASN((RoadSegmentReferenceID*)&src->id, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_GeographicalPath_anchor)
		{
			if ((ret->anchor = init_Position3D_from_ASN(src->anchor, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_GeographicalPath_laneWidth)
		{
			ret->laneWidth = src->laneWidth;
		}
		if (src->DEF_GeographicalPath_directionality)
		{
			ret->directionality = (Gitsn_DirectionOfUse)src->directionality;
		}
		if (src->DEF_GeographicalPath_closedPath)
		{
			ret->closedPath = src->closedPath;
		}
		if (src->DEF_GeographicalPath_direction)
		{
			if ((ret->direction = Dz1Calloc(2, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (memcpy(ret->direction, src->direction.data, 2) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_GeographicalPath_description)
		{
			if ((ret->description = init_GeographicalPath_description_from_ASN(src->description, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_GeographicalPath_regional) {}
		pthread_cleanup_pop(errp->code); // (Gitsn_GeographicalPath_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_TravelerDataFrame_regions* init_TravelerDataFrame_regions_from_ASN(TravelerDataFrame_regions* src, Dz1Error* errp)
{
	Gitsn_TravelerDataFrame_regions* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_TravelerDataFrame_regions_new(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Gitsn_GeographicalPath* _element = NULL;
		pthread_cleanup_push(Gitsn_TravelerDataFrame_regions_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			GeographicalPath* src_element = (GeographicalPath*)ASN1_Get_Node_Index((ASN1List*)src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((_element = init_GeographicalPath_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				pthread_cleanup_push(Gitsn_GeographicalPath_delAndSetNull, (void*)&_element);
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else
				{
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

static Gitsn_ITIScodesAndText_element_item* init_ITIScodesAndText_element_item_from_ASN(ITIScodesAndText_element_item* src, Dz1Error* errp)
{
	Gitsn_ITIScodesAndText_element_item* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_ITIScodesAndText_element_item_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_ITIScodesAndText_element_item_delAndSetNull, (void*)&ret);
		switch (src->M)
		{
		case DEF_ITIScodesAndText_element_item_itis:
			ret->x.itis = src->elements.itis;
			ret->present = Gitsn_ITIScodesAndText_element_itemPresent_itis;
			Dz1Error_set(errp, 0);
			break;
		case DEF_ITIScodesAndText_element_item_text:
			if ((ret->x.text = Dz1Str_ndup(src->elements.text.asnstring, src->elements.text.nchar, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_ITIScodesAndText_element_itemPresent_text;
				Dz1Error_set(errp, 0);
			}
			break;
		default: ERR_SET_OUT(errp, EPERM);break;
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_ITIScodesAndText_element_item_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_ITIScodesAndText_element* init_ITIScodesAndText_element_from_ASN(ITIScodesAndText_element* src, Dz1Error* errp)
{
	Gitsn_ITIScodesAndText_element* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_ITIScodesAndText_element_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_ITIScodesAndText_element_delAndSetNull, (void*)&ret);
		if ((ret->item = init_ITIScodesAndText_element_item_from_ASN(src->item, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Gitsn_ITIScodesAndText_element_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_ITIScodesAndText* init_ITIScodesAndText_from_ASN(ITIScodesAndText* src, Dz1Error* errp)
{
	Gitsn_ITIScodesAndText* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_ITIScodesAndText_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Gitsn_ITIScodesAndText_element* _element = NULL;
		pthread_cleanup_push(Gitsn_ITIScodesAndText_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count;i++)
		{
			ITIScodesAndText_element* src_element = (ITIScodesAndText_element*)ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((_element = init_ITIScodesAndText_element_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				pthread_cleanup_push(Gitsn_ITIScodesAndText_element_delAndSetNull, (void*)&_element);
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else
				{
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

static Gitsn_WorkZone_element_item* init_WorkZone_element_item_from_ASN(WorkZone_element_item* src, Dz1Error* errp)
{
	Gitsn_WorkZone_element_item* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_WorkZone_element_item_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_WorkZone_element_item_delAndSetNull, (void*)&ret);
		switch (src->M)
		{
		case DEF_WorkZone_element_item_itis:
			ret->x.itis = src->elements.itis;
			ret->present = Gitsn_WorkZone_element_itemPresent_itis;
			Dz1Error_set(errp, 0);
			break;
		case DEF_WorkZone_element_item_text:
			if ((ret->x.text = Dz1Str_ndup(src->elements.text.asnstring, src->elements.text.nchar, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_WorkZone_element_itemPresent_text;
				Dz1Error_set(errp, 0);
			}
			break;
		default: ERR_SET_OUT(errp, EPERM);break;
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_WorkZone_element_item_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_WorkZone_element* init_WorkZone_element_from_ASN(WorkZone_element* src, Dz1Error* errp)
{
	Gitsn_WorkZone_element* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_WorkZone_element_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_WorkZone_element_delAndSetNull, (void*)&ret);
		if ((ret->item = init_WorkZone_element_item_from_ASN(src->item, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Gitsn_WorkZone_element_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_WorkZone* init_WorkZone_from_ASN(WorkZone* src, Dz1Error* errp)
{
	Gitsn_WorkZone* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_WorkZone_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Gitsn_WorkZone_element* _element = NULL;
		pthread_cleanup_push(Gitsn_WorkZone_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count;i++)
		{
			WorkZone_element* src_element = (WorkZone_element*)ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((_element = init_WorkZone_element_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				pthread_cleanup_push(Gitsn_WorkZone_element_delAndSetNull, (void*)&_element);
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else
				{
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

static Gitsn_GenericSignage_element_item* init_GenericSignage_element_item_from_ASN(GenericSignage_element_item* src, Dz1Error* errp)
{
	Gitsn_GenericSignage_element_item* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_GenericSignage_element_item_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_GenericSignage_element_item_delAndSetNull, (void*)&ret);
		switch (src->M)
		{
		case DEF_GenericSignage_element_item_itis:
			ret->x.itis = src->elements.itis;
			ret->present = Gitsn_GenericSignage_element_itemPresent_itis;
			Dz1Error_set(errp, 0);
			break;
		case DEF_GenericSignage_element_item_text:
			if ((ret->x.text = Dz1Str_ndup(src->elements.text.asnstring, src->elements.text.nchar, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_GenericSignage_element_itemPresent_text;
				Dz1Error_set(errp, 0);
			}
			break;
		default: ERR_SET_OUT(errp, EPERM);break;
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_GenericSignage_element_item_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_GenericSignage_element* init_GenericSignage_element_from_ASN(GenericSignage_element* src, Dz1Error* errp)
{
	Gitsn_GenericSignage_element* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_GenericSignage_element_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_GenericSignage_element_delAndSetNull, (void*)&ret);
		if ((ret->item = init_GenericSignage_element_item_from_ASN(src->item, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Gitsn_GenericSignage_element_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_GenericSignage* init_GenericSignage_from_ASN(GenericSignage* src, Dz1Error* errp)
{
	Gitsn_GenericSignage* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_GenericSignage_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Gitsn_GenericSignage_element* _element = NULL;
		pthread_cleanup_push(Gitsn_GenericSignage_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count;i++)
		{
			GenericSignage_element* src_element = (GenericSignage_element*)ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((_element = init_GenericSignage_element_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				pthread_cleanup_push(Gitsn_GenericSignage_element_delAndSetNull, (void*)&_element);
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else
				{
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

static Gitsn_SpeedLimit_element_item* init_SpeedLimit_element_item_from_ASN(SpeedLimit_element_item* src, Dz1Error* errp)
{
	Gitsn_SpeedLimit_element_item* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_SpeedLimit_element_item_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_SpeedLimit_element_item_delAndSetNull, (void*)&ret);
		switch (src->M)
		{
		case DEF_SpeedLimit_element_item_itis:
			ret->x.itis = src->elements.itis;
			ret->present = Gitsn_SpeedLimit_element_itemPresent_itis;
			Dz1Error_set(errp, 0);
			break;
		case DEF_SpeedLimit_element_item_text:
			if ((ret->x.text = Dz1Str_ndup(src->elements.text.asnstring, src->elements.text.nchar, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_SpeedLimit_element_itemPresent_text;
				Dz1Error_set(errp, 0);
			}
			break;
		default: ERR_SET_OUT(errp, EPERM);break;
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_SpeedLimit_element_item_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_SpeedLimit_element* init_SpeedLimit_element_from_ASN(SpeedLimit_element* src, Dz1Error* errp)
{
	Gitsn_SpeedLimit_element* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_SpeedLimit_element_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_SpeedLimit_element_delAndSetNull, (void*)&ret);
		if ((ret->item = init_SpeedLimit_element_item_from_ASN(src->item, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Gitsn_SpeedLimit_element_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_SpeedLimit* init_SpeedLimit_from_ASN(SpeedLimit* src, Dz1Error* errp)
{
	Gitsn_SpeedLimit* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_SpeedLimit_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Gitsn_SpeedLimit_element* _element = NULL;
		pthread_cleanup_push(Gitsn_SpeedLimit_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count;i++)
		{
			SpeedLimit_element* src_element = (SpeedLimit_element*)ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((_element = init_SpeedLimit_element_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				pthread_cleanup_push(Gitsn_SpeedLimit_element_delAndSetNull, (void*)&_element);
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else
				{
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


static Gitsn_ExitService_element_item* init_ExitService_element_item_from_ASN(ExitService_element_item* src, Dz1Error* errp)
{
	Gitsn_ExitService_element_item* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_ExitService_element_item_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_ExitService_element_item_delAndSetNull, (void*)&ret);
		switch (src->M)
		{
		case DEF_ExitService_element_item_itis:
			ret->x.itis = src->elements.itis;
			ret->present = Gitsn_ExitService_element_itemPresent_itis;
			Dz1Error_set(errp, 0);
			break;
		case DEF_ExitService_element_item_text:
			if ((ret->x.text = Dz1Str_ndup(src->elements.text.asnstring, src->elements.text.nchar, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_ExitService_element_itemPresent_text;
				Dz1Error_set(errp, 0);
			}
			break;
		default: ERR_SET_OUT(errp, EPERM);break;
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_ExitService_element_item_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_ExitService_element* init_ExitService_element_from_ASN(ExitService_element* src, Dz1Error* errp)
{
	Gitsn_ExitService_element* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_ExitService_element_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_ExitService_element_delAndSetNull, (void*)&ret);
		if ((ret->item = init_ExitService_element_item_from_ASN(src->item, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Gitsn_ExitService_element_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_ExitService* init_ExitService_from_ASN(ExitService* src, Dz1Error* errp)
{
	Gitsn_ExitService* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_ExitService_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Gitsn_ExitService_element* _element = NULL;
		pthread_cleanup_push(Gitsn_ExitService_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count;i++)
		{
			ExitService_element* src_element = (ExitService_element*)ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((_element = init_ExitService_element_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				pthread_cleanup_push(Gitsn_ExitService_element_delAndSetNull, (void*)&_element);
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else
				{
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



static Gitsn_TravelerDataFrame_content* init_TravelerDataFrame_content_from_ASN(TravelerDataFrame_content* src, Dz1Error* errp)
{
	Gitsn_TravelerDataFrame_content* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_TravelerDataFrame_content_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_TravelerDataFrame_content_delAndSetNull, (void*)&ret);
		switch (src->M)
		{
		case DEF_TravelerDataFrame_content_advisory:
			if ((ret->x.advisory = init_ITIScodesAndText_from_ASN((ITIScodesAndText*)&src->elements.advisory, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_TravelerDataFrame_contentPresent_advisory;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_TravelerDataFrame_content_workZone:
			if ((ret->x.workZone = init_WorkZone_from_ASN((WorkZone*)&src->elements.workZone, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_TravelerDataFrame_contentPresent_workZone;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_TravelerDataFrame_content_genericSign:
			if ((ret->x.genericSign = init_GenericSignage_from_ASN((GenericSignage*)&src->elements.genericSign, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_TravelerDataFrame_contentPresent_genericSign;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_TravelerDataFrame_content_speedLimit:
			if ((ret->x.speedLimit = init_SpeedLimit_from_ASN((SpeedLimit*)&src->elements.speedLimit, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_TravelerDataFrame_contentPresent_speedLimit;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_TravelerDataFrame_content_exitService:
			if ((ret->x.exitService = init_ExitService_from_ASN((ExitService*)&src->elements.exitService, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_TravelerDataFrame_contentPresent_exitService;
				Dz1Error_set(errp, 0);
			}
			break;
		default:
			ERR_SET_OUT(errp, EPERM);break;

		}


		pthread_cleanup_pop(errp->code); // (Gitsn_TravelerDataFrame_content_delAndSetNull, (void*)&ret);
	}
	return ret;
}


static Gitsn_TravelerDataFrame* init_TravelerDataFrame_from_ASN(TravelerDataFrame* src, Dz1Error* errp)
{
	Gitsn_TravelerDataFrame* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_TravelerDataFrame_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_TravelerDataFrame_delAndSetNull, (void*)&ret);
		if ((ret->msgId = init_TravelerDataFrame_msgId_from_ASN(src->msgId, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->regions = init_TravelerDataFrame_regions_from_ASN((TravelerDataFrame_regions*)&src->regions, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->content = init_TravelerDataFrame_content_from_ASN(src->content, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			ret->notUsed = src->notUsed;
			ret->frameType = (Gitsn_TravelerInfoType)src->frameType;
			ret->startTime = src->startTime;
			ret->durationTime = src->durationTime;
			ret->priority = src->priority;
			ret->notUsed1 = src->notUsed1;
			ret->notUsed2 = src->notUsed2;
			ret->notUsed3 = src->notUsed3;

			if (src->DEF_TravelerDataFrame_startYear)
			{
				ret->startYear = src->startYear;
			}
			if (src->DEF_TravelerDataFrame_url)
			{
				if ((ret->url = Dz1Str_ndup(src->url.asnstring, src->url.nchar, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_TravelerDataFrame_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_TravelerDataFrameList* init_TravelerDataFrameList_from_ASN(TravelerDataFrameList* src, Dz1Error* errp)
{
	Gitsn_TravelerDataFrameList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_TravelerDataFrameList_new(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Gitsn_TravelerDataFrame* _element = NULL;
		pthread_cleanup_push(Gitsn_TravelerDataFrameList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			TravelerDataFrame* src_element = ASN1_Get_Node_Index((ASN1List*)src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((_element = init_TravelerDataFrame_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				pthread_cleanup_push(Gitsn_TravelerDataFrame_delAndSetNull, (void*)&_element);
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else
				{
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

bool_t GitsnAsnUtil_Gitsn_TravelerInformationFromASN(TravelerInformation* src, Gitsn_TravelerInformation* dst, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || dst == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst->dataFrames = init_TravelerDataFrameList_from_ASN((TravelerDataFrameList*)&src->dataFrames, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		dst->msgCnt = src->msgCnt;

		if (src->DEF_TravelerInformation_timeStamp)
		{
			dst->timeStamp = src->timeStamp;
		}
		if (src->DEF_TravelerInformation_packetID)
		{


			if ((dst->packetID = Dz1Str_ndup(src->packetID.data, 9, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_TravelerInformation_urlB)
		{
			if ((dst->urlB = Dz1Str_ndup(src->urlB.asnstring, src->urlB.nchar, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_TravelerInformation_regional)
		{
			// region
		}
	}

	if (errp->code == 0)
	{
		
	}
	return ERR_IS_SUCCESS(errp);
}


static Gitsn_PositionOffsetXYZ* init_PositionOffsetXYZ_from_ASN(PositionOffsetXYZ* src, Dz1Error* errp)
{
	Gitsn_PositionOffsetXYZ* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_PositionOffsetXYZ_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_PositionOffsetXYZ_delAndSetNull, (void*)&ret);
		ret->offsetX = src->offsetX;
		ret->offsetY = src->offsetY;
		if (src->DEF_PositionOffsetXYZ_offsetZ)
			ret->offsetZ = src->offsetZ;

		pthread_cleanup_pop(errp->code); // 
	}
	return ret;
}

static Gitsn_DetectedObjectCommonData* init_DetectedObjectCommonData_from_ASN(DetectedObjectCommonData* src, Dz1Error* errp)
{
	Gitsn_DetectedObjectCommonData* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_DetectedObjectCommonData_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_DetectedObjectCommonData_delAndSetNull, (void*)&ret);
		if ((ret->pos = init_PositionOffsetXYZ_from_ASN(src->pos, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->posConfidence = init_PositionConfidenceSet_from_ASN(src->posConfidence, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			ret->objType = (Gitsn_ObjectType)src->objType;
			ret->objTypeCfd = src->objTypeCfd;
			ret->objectID = src->objectID;
			ret->measurementTime = src->measurementTime;
			ret->timeConfidence = (Gitsn_TimeConfidence)src->timeConfidence;
			ret->speed = src->speed;
			ret->speedConfidence = (Gitsn_SpeedConfidence)src->speedConfidence;
			src->heading = src->heading;
			src->headingConf = (Gitsn_HeadingConfidence)src->headingConf;

			if (src->DEF_DetectedObjectCommonData_speedZ)
				ret->speedZ = src->speedZ;
			if (src->DEF_DetectedObjectCommonData_speedConfidenceZ)
				ret->speedConfidenceZ = (Gitsn_SpeedConfidence)src->speedConfidenceZ;
			if (src->DEF_DetectedObjectCommonData_accel4way)
			{
				if ((ret->accel4way = init_AccelerationSet4Way_from_ASN(src->accel4way, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
			if (src->DEF_DetectedObjectCommonData_accCfdX)
				ret->accCfdX = (Gitsn_AccelerationConfidence)src->accCfdX;
			if (src->DEF_DetectedObjectCommonData_accCfdY)
				ret->accCfdY = (Gitsn_AccelerationConfidence)src->accCfdY;
			if (src->DEF_DetectedObjectCommonData_accCfdZ)
				ret->accCfdZ = (Gitsn_AccelerationConfidence)src->accCfdZ;
			if (src->DEF_DetectedObjectCommonData_accCfdYaw)
				ret->accCfdYaw = (Gitsn_YawRateConfidence)src->accCfdYaw;
		}
		pthread_cleanup_pop(errp->code); // 
	}
	return ret;
}

static Gitsn_Attitude* init_Attitude_from_ASN(Attitude* src, Dz1Error* errp)
{
	Gitsn_Attitude* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Attitude_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_Attitude_delAndSetNull, (void*)&ret);
		ret->pitch = src->pitch;
		ret->roll = src->roll;
		ret->yaw = src->yaw;
		pthread_cleanup_pop(errp->code); // 
	}
	return ret;
}

static Gitsn_AttitudeConfidence* init_AttitudeConfidence_from_ASN(AttitudeConfidence* src, Dz1Error* errp)
{
	Gitsn_AttitudeConfidence* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_AttitudeConfidence_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_AttitudeConfidence_delAndSetNull, (void*)&ret);
		ret->pitchConfidence = (HeadingConfidence)src->pitchConfidence;
		ret->rollConfidence = (HeadingConfidence)src->rollConfidence;
		ret->yawConfidence = (HeadingConfidence)src->yawConfidence;

		pthread_cleanup_pop(errp->code); // 
	}
	return ret;
}

static Gitsn_AngularVelocity* init_AngularVelocity_from_ASN(AngularVelocity* src, Dz1Error* errp)
{
	Gitsn_AngularVelocity* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_AngularVelocity_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_AngularVelocity_delAndSetNull, (void*)&ret);
		ret->pitchRate = src->pitchRate;
		ret->rollRate = src->rollRate;
		pthread_cleanup_pop(errp->code); // 
	}
	return ret;
}

static Gitsn_AngularVelocityConfidence* init_AngularVelocityConfidence_from_ASN(AngularVelocityConfidence* src, Dz1Error* errp)
{
	Gitsn_AngularVelocityConfidence* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_AngularVelocityConfidence_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_AngularVelocityConfidence_delAndSetNull, (void*)&ret);

		if (src->DEF_AngularVelocityConfidence_pitchRateConfidence)
			ret->pitchRateConfidence = src->pitchRateConfidence;
		if (src->DEF_AngularVelocityConfidence_rollRateConfidence)
			ret->rollRateConfidence = src->rollRateConfidence;
		pthread_cleanup_pop(errp->code); // 
	}
	return ret;
}

static Gitsn_VehicleSizeConfidence* init_VehicleSizeConfidence_from_ASN(VehicleSizeConfidence* src, Dz1Error* errp)
{
	Gitsn_VehicleSizeConfidence* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_VehicleSizeConfidence_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_VehicleSizeConfidence_delAndSetNull, (void*)&ret);
		ret->vehicleWidthConfidence = (Gitsn_SizeValueConfidence)src->vehicleWidthConfidence;
		ret->vehicleLengthConfidence = (Gitsn_SizeValueConfidence)src->vehicleLengthConfidence;
		if (src->DEF_VehicleSizeConfidence_vehicleHeightConfidence)
			ret->vehicleHeightConfidence = (Gitsn_SizeValueConfidence)src->vehicleHeightConfidence;
		pthread_cleanup_pop(errp->code); // 
	}
	return ret;
}

static Gitsn_DetectedVehicleData* init_DetectedVehicleData_from_ASN(DetectedVehicleData* src, Dz1Error* errp)
{
	Gitsn_DetectedVehicleData* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_DetectedVehicleData_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		size_t sz = 0;
		pthread_cleanup_push(Gitsn_DetectedVehicleData_delAndSetNull, (void*)&ret);
		if (src->DEF_DetectedVehicleData_lights)
		{
			sz = src->lights.numbits + 7 / 8;
			if ((ret->lights = Dz1Calloc(sz, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (memcpy(ret->lights, src->lights.data, sz) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_DetectedVehicleData_vehAttitude)
		{
			if ((ret->vehAttitude = init_Attitude_from_ASN(src->vehAttitude, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_DetectedVehicleData_vehAttitudeConfidence)
		{
			if ((ret->vehAttitudeConfidence = init_AttitudeConfidence_from_ASN(src->vehAttitudeConfidence, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}

		if (src->DEF_DetectedVehicleData_vehAngVel)
		{
			if ((ret->vehAngVel = init_AngularVelocity_from_ASN(src->vehAngVel, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}

		if (src->DEF_DetectedVehicleData_vehAngVelConfidence)
		{
			if ((ret->vehAngleConfidence = init_AngularVelocityConfidence_from_ASN(src->vehAngVelConfidence, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_DetectedVehicleData_size)
		{
			if ((ret->size = init_VehicleSize_from_ASN(src->size, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}

		if (src->DEF_DetectedVehicleData_height)
			ret->height = src->height;
		if (src->DEF_DetectedVehicleData_vehicleSizeConfidence)
		{
			if ((ret->vehicleSizeConfidence = init_VehicleSizeConfidence_from_ASN(src->vehicleSizeConfidence, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_DetectedVehicleData_vehicleClass)
			ret->vehicleClass = src->vehicleClass;
		if (src->DEF_DetectedVehicleData_classConf)
			ret->classConf = src->classConf;

		pthread_cleanup_pop(errp->code); // 
	}
	return ret;
}

static Gitsn_PropelledInformation* init_PropelledInformation_from_ASN(PropelledInformation* src, Dz1Error* errp)
{
	Gitsn_PropelledInformation* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_PropelledInformation_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_PropelledInformation_delAndSetNull, (void*)&ret);
		switch (src->M)
		{
		case DEF_PropelledInformation_human:
			ret->x.human = (Gitsn_HumanPropelledType)src->elements.human;
			ret->present = Gitsn_PropelledInformationPresent_human;
			break;
		case DEF_PropelledInformation_animal:
			ret->x.animal = (Gitsn_AnimalPropelledType)src->elements.animal;
			ret->present = Gitsn_PropelledInformationPresent_animal;
			break;
		case DEF_PropelledInformation_motor:
			ret->x.motor = (Gitsn_MotorizedPropelledType)src->elements.motor;
			ret->present = Gitsn_PropelledInformationPresent_motor;
			break;
		default:ERR_SET_OUT(errp, EPERM);
		}

		pthread_cleanup_pop(errp->code); // 
	}
	return ret;
}

static Gitsn_DetectedVRUData* init_DetectedVRUData_from_ASN(DetectedVRUData* src, Dz1Error* errp)
{
	Gitsn_DetectedVRUData* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_DetectedVRUData_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_DetectedVRUData_delAndSetNull, (void*)&ret);
		if (src->DEF_DetectedVRUData_basicType)
			ret->basicType = (Gitsn_PersonalDeviceUserType)src->basicType;
		if (src->DEF_DetectedVRUData_propulsion)
		{
			if ((ret->propulsion = init_PropelledInformation_from_ASN(src->propulsion, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_DetectedVRUData_attachment)
			ret->attachment = (Gitsn_Attachment)src->attachment;
		if (src->DEF_DetectedVRUData_radius)
			ret->radius = src->radius;

		pthread_cleanup_pop(errp->code); // 
	}
	return ret;
}

static Gitsn_ObstacleSize* init_ObstacleSize_from_ASN(ObstacleSize* src, Dz1Error* errp)
{
	Gitsn_ObstacleSize* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_ObstacleSize_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_ObstacleSize_delAndSetNull, (void*)&ret);
		ret->width = src->width;
		ret->length = src->length;
		if (src->DEF_ObstacleSize_height)
			ret->height = src->height;
		pthread_cleanup_pop(errp->code); // 
	}
	return ret;
}

static Gitsn_ObstacleSizeConfidence* init_ObstacleSizeConfidence_from_ASN(ObstacleSizeConfidence* src, Dz1Error* errp)
{
	Gitsn_ObstacleSizeConfidence* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_ObstacleSizeConfidence_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_ObstacleSizeConfidence_delAndSetNull, (void*)&ret);
		ret->widthConfidence = (Gitsn_SizeValueConfidence)src->widthConfidence;
		ret->lengthConfidence = (Gitsn_SizeValueConfidence)src->lengthConfidence;
		if (src->DEF_ObstacleSizeConfidence_heightConfidence)
			ret->heightConfidence = (Gitsn_SizeValueConfidence)src->heightConfidence;

		pthread_cleanup_pop(errp->code); // 
	}
	return ret;
}

static Gitsn_DetectedObstacleData* init_DetectedObstacleData_from_ASN(DetectedObstacleData* src, Dz1Error* errp)
{
	Gitsn_DetectedObstacleData* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_DetectedObstacleData_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_DetectedObstacleData_delAndSetNull, (void*)&ret);
		if ((ret->obstSize = init_ObstacleSize_from_ASN(src->obstSize, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->obstSizeConfidence = init_ObstacleSizeConfidence_from_ASN(src->obstSizeConfidence, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // 
	}
	return ret;
}

static Gitsn_DetectedObjectOptionalData* init_DetectedObjectOptionalData_from_ASN(DetectedObjectOptionalData* src, Dz1Error* errp)
{
	Gitsn_DetectedObjectOptionalData* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_DetectedObjectOptionalData_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_DetectedObjectOptionalData_delAndSetNull, (void*)&ret);
		switch (src->M)
		{
		case DEF_DetectedObjectOptionalData_detVeh:
			if ((ret->x.detVeh = init_DetectedVehicleData_from_ASN(src->elements.detVeh, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_DetectedObjectOptionalDataPresent_detVeh;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_DetectedObjectOptionalData_detVRU:
			if ((ret->x.detVRU = init_DetectedVRUData_from_ASN(src->elements.detVRU, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_DetectedObjectOptionalDataPresent_detVRU;
				Dz1Error_set(errp, 0);
			}
			break;
		case DEF_DetectedObjectOptionalData_detObst:
			if ((ret->x.detObst = init_DetectedObstacleData_from_ASN(src->elements.detObst, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->present = Gitsn_DetectedObjectOptionalDataPresent_detObst;
				Dz1Error_set(errp, 0);
			}
			break;
		default: ERR_SET_OUT(errp, EPERM);
			break;
		}

		pthread_cleanup_pop(errp->code); // 
	}
	return ret;
}

static Gitsn_DetectedObjectData* init_DetectedObjectData_from_ASN(DetectedObjectData* src, Dz1Error* errp)
{
	Gitsn_DetectedObjectData* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_DetectedObjectData_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_DetectedObjectData_delAndSetNull, (void*)&ret);
		if ((ret->detObjCommon = init_DetectedObjectCommonData_from_ASN(src->detObjCommon, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			if (src->DEF_DetectedObjectData_detObjOptData)
			{
				if ((ret->detObjOptData = init_DetectedObjectOptionalData_from_ASN(src->detObjOptData, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(errp->code); // 
	}
	return ret;
}

static Gitsn_DetectedObjectList* init_DetectedObjectList_from_ASN(DetectedObjectList* src, Dz1Error* errp)
{
	Gitsn_DetectedObjectList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_DetectedObjectList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Gitsn_DetectedObjectData* entry = NULL;
		pthread_cleanup_push(Gitsn_DetectedObjectList_delAndSetNull, (void*)&ret);
		for (int i = 1;i <= (int)src->count;i++)
		{
			DetectedObjectData* src_entry = (DetectedObjectData*)ASN1_Get_Node_Index(src, i);
			if (src_entry == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((entry = init_DetectedObjectData_from_ASN(src_entry, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				pthread_cleanup_push(Gitsn_DetectedObjectData_delAndSetNull, (void*)&entry);
				if ((*errp = ret->add(ret, entry)).code) ERR_SET_OUT(errp, EFAULT);
				else
				{
					entry = NULL;
					// free(src_entry);
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (Gitsn_DetectedObjectData_delAndSetNull, (void*)&entry);
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_DetectedObjectList_delAndSetNull, (void*)&ret);
	}
	return ret;
}


bool_t GitsnAsnUtil_Gitsn_SensorDataSharingMessageFromASN(SensorDataSharingMessage* src, Gitsn_SensorDataSharingMessage* dst, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || dst == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		if ((dst->sourceID = Dz1Str_ndup(src->sourceID.data, src->sourceID.numbits, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((dst->sDSMTimeStamp = init_DDateTime_from_ASN(src->sDSMTimeStamp, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((dst->refPos = init_Position3D_from_ASN(src->refPos, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((dst->refPosXYConf = init_PositionalAccuracy_from_ASN(src->refPosXYConf, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((dst->objects = init_DetectedObjectList_from_ASN((DetectedObjectList*)&src->objects, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			dst->msgCnt = src->msgCnt;
			if (src->DEF_SensorDataSharingMessage_refPosElConf)
				dst->refPosElConf = (Gitsn_ElevationConfidence)src->refPosElConf;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}


// TLS
static Gitsn_TrafficLightID* init_TrafficLightID_from_ASN(TrafficLightID* src, Dz1Error* errp)
{
	Gitsn_TrafficLightID* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_TrafficLightID_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_TrafficLightID_delAndSetNull, (void*)&ret);
		switch (src->M)
		{
		case DEF_TrafficLightID_id:
			ret->x.id = src->elements.id;
			break;
		case DEF_TrafficLightID_oid:
			if ((ret->x.oid = Gitsn_OBJECTIDENTIFIER_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((ret->x.oid->subid = Dz1u32_clone((u32_t*)src->elements.oid.subid, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				ret->x.oid->numids = src->elements.oid.numids;
				Dz1Error_set(errp, 0);
			}
			break;
		default: ERR_SET_OUT(errp, EPERM);
			break;
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_TrafficLightID_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_TrafficLightStatus* init_TrafficLightStatus_from_ASN(TrafficLightStatus* src, Dz1Error* errp)
{
	Gitsn_TrafficLightStatus* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_TrafficLightStatus_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Gitsn_TrafficLightStatus_delAndSetNull, (void*)&ret);
		ret->trafficLightType = src->trafficLightType;
		ret->consecutiveTrafficLight = src->consecutiveTrafficLight;
		ret->trafficLightIntervalType = src->trafficLightIntervalType;
		ret->pedestrianCall = src->pedestrianCall;
		ret->actuatedinterval = src->actuatedinterval;
		ret->permissiveNonProtected = src->permissiveNonProtected;
		ret->lightingStatus = src->lightingStatus;
		ret->maxIntervalLength = src->maxIntervalLength;
		ret->remainingTime = src->remainingTime;
		ret->directionCode = src->directionCode;
		ret->reserved = src->reserved;
		pthread_cleanup_pop(errp->code); // (Gitsn_TrafficLightStatus_delAndSetNull, (void*)&ret);
	}
	return ret;
}


static Gitsn_TrafficLightStatusList* init_TrafficLightStatusList_from_ASN(TrafficLightStatusList *src, Dz1Error* errp)
{
	Gitsn_TrafficLightStatusList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_TrafficLightStatusList_gen(errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Gitsn_TrafficLightStatus* _element;
		pthread_cleanup_push(Gitsn_TrafficLightStatusList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			TrafficLightStatus* src_element = ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((_element = init_TrafficLightStatus_from_ASN(src_element, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				pthread_cleanup_push(Gitsn_TrafficLightStatus_delAndSetNull, (void*)&_element);
				if ((*errp = ret->add(ret, _element)).code) ERR_SET_OUT(errp, EFAULT);
				else
				{
					_element = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (Gitsn_TrafficLightStatus_delAndSetNull, (void*)&_element);
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_TrafficLightStatusList_delAndSetNull, (void*)&ret);
	}
	return ret;
}

bool_t GitsnAsnUtil_Gitsn_TLSFromASN(TLS* src, Gitsn_TLS* dst, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (0) {}
		else if ((dst->trafficLightID = init_TrafficLightID_from_ASN(src->trafficLightID, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((dst->currentTime = init_DDateTime_from_ASN(src->currentTime, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((dst->trafficLightStatus = init_TrafficLightStatusList_from_ASN((TrafficLightStatusList*)&src->trafficLightStatus, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			size_t sz = src->operationStatus.numbits + 7 / 8;
			if ((dst->operationStatus = Dz1Calloc(sz, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (memcpy(dst->operationStatus, src->operationStatus.data, sz) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);

			sz = src->controllerStatus.numbits + 7 / 8;
			if ((dst->controllerStatus = Dz1Calloc(sz, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (memcpy(dst->controllerStatus, src->controllerStatus.data, sz) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);

			dst->lat = src->lat;
			dst->lon = src->lon;
			dst->cyclecounter = src->cyclecounter;
			dst->cycletime = src->cycletime;

		}
	}
	return ERR_IS_SUCCESS(errp);
}


bool_t GitsnAsnUtil_Gitsn_TrafficLightStatusMessageFromASN(TrafficLightStatusMessage* src, Gitsn_TrafficLightStatusMessage* dst, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (0) {}
		else if ((dst->currentTime = init_DDateTime_from_ASN(src->currentTime, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((dst->trafficLightStatus = init_TrafficLightStatusList_from_ASN((TrafficLightStatusList*)&src->trafficLightStatus, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			size_t sz = src->operationStatus.numbits + 7 / 8;
			if ((dst->operationStatus = Dz1Calloc(sz, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (memcpy(dst->operationStatus, src->operationStatus.data, sz) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);

			sz = src->controllerStatus.numbits + 7 / 8;
			if ((dst->controllerStatus = Dz1Calloc(sz, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
			else if (memcpy(dst->controllerStatus, src->controllerStatus.data, sz) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);

			dst->trafficLightID = src->traffiLightID;
			dst->lat = src->lat;
			dst->lon = src->lon;
			dst->cyclecounter = src->cycleCounter;
			dst->cycletime = src->cycleTime;
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static Gitsn_PrivilegedEvents* init_PrivilegedEvents_from_ASN(PrivilegedEvents* src, Dz1Error* errp)
{
	Gitsn_PrivilegedEvents* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_PrivilegedEvents_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_PrivilegedEvents_delAndSetNull, (void*)&ret);
		
		ret->doNotUse = src->doNotUse;

		size_t sz = src->event.numbits + 7 / 8;
		if ((ret->event = Dz1Calloc(sz, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (memcpy(ret->event, src->event.data, sz) == NULL) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Gitsn_PrivilegedEvents_delAndSetNull, (void *)&ret);
	}
	return ret;
}


static Gitsn_EmergencyDetails* init_EmergencyDetails_from_ASN(EmergencyDetails* src, Dz1Error* errp)
{
	Gitsn_EmergencyDetails* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_EmergencyDetails_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_EmergencyDetails_delAndSetNull, (void*)&ret);
		ret->doNotUse = src->doNotUse;
		ret->sirenUse = src->sirenUse;
		ret->lightsUse = src->lightsUse;
		Dz1Error_set(errp, 0);
		if (src->DEF_EmergencyDetails_events)
		{
			if ((ret->events = init_PrivilegedEvents_from_ASN(src->events, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_EmergencyDetails_responseType) { ret->responseType = src->responseType;}
		pthread_cleanup_pop(errp->code); // (Gitsn_EmergencyDetails_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t GitsnAsnUtil_Gitsn_EmergencyVehicleAlertFromASN(EmergencyVehicleAlert* src, Gitsn_EmergencyVehicleAlert* dst, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (0) {}
		else if ((dst->rsaMsg = Gitsn_RoadSideAlert_gen(errp)) == NULL) ERR_OUT(errp);
		else if (GitsnAsnUtil_Gitsn_RoadSideAlertFromASN(src->rsaMsg, dst->rsaMsg, errp) == FALSE) ERR_OUT(errp);
		else
		{
			if (src->DEF_EmergencyVehicleAlert_timeStamp)
			{
				dst->timeStamp = src->timeStamp;
			}
			/*if (src->DEF_EmergencyVehicleAlert_id)
			{

				if ((dst->id = Dz1Str_ndup(src->id.data, src->id.numbits, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}*/
			if (src->DEF_EmergencyVehicleAlert_responseType)
			{
				dst->responderType = src->responderType;
			}
			if(src->DEF_EmergencyVehicleAlert_details)
			{
				if ((dst->details = init_EmergencyDetails_from_ASN(src->details, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			if(src->DEF_EmergencyVehicleAlert_mass)
			{
				dst->mass = src->mass;
			}
			if(src->DEF_EmergencyVehicleAlert_basicType)
			{
				dst->basicType = src->basicType;
			}
			if(src->DEF_EmergencyVehicleAlert_vehicleType)
			{
				dst->vehicleType = src->vehicleType;
			}
			if(src->DEF_EmergencyVehicleAlert_responseEquip)
			{
				dst->responseEquip = src->responseEquip;
			}
			if(src->DEF_EmergencyVehicleAlert_responderType)
			{
				dst->responderType = src->responderType;
			}
			// if(src->DEF_EmergencyVehicleAlert_regional)
			// {
			// }
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static Gitsn_RTCMmessageList* init_RTCMmessageList_from_ASN(RTCMmessageList* src, Dz1Error* errp)
{
	Gitsn_RTCMmessageList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_RTCMmessageList_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Gitsn_RTCMmessage element = NULL;
		pthread_cleanup_push(Gitsn_RTCMmessageList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			RTCMmessage* src_element = (RTCMmessage*)ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((element = Dz1Str_ndup((Dz1Str)src_element->data, src_element->numbits, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Gitsn_RTCMmessage_delAndSetNull, (void*)&element);
				if ((*errp = ret->add(ret, element)).code) ERR_OUT(errp);
				else
				{
					element = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (Gitsn_RTCMmessage_delAndSetNull, (void *)&element);
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_RTCMmessageList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Gitsn_AntennaOffsetSet* init_AntennaOffsetSet_from_ASN(AntennaOffsetSet* src, Dz1Error* errp)
{
	Gitsn_AntennaOffsetSet* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_AntennaOffsetSet_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_AntennaOffsetSet_delAndSetNull, (void*)&ret);
		ret->antOffsetX = src->antOffsetX;
		ret->antOffsetY = src->antOffsetY;
		ret->antOffsetZ = src->antOffsetZ;
		pthread_cleanup_pop(errp->code); // (Gitsn_AntennaOffsetSet_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Gitsn_RTCMheader* init_RTCMheader_from_ASN(RTCMheader* src, Dz1Error* errp)
{
	Gitsn_RTCMheader* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_RTCMheader_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_RTCMheader_delAndSetNull, (void*)&ret);

		size_t sz = src->status.numbits + 7 / 8;
		if ((ret->status = Dz1Calloc(sz, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if (memcpy(ret->status, src->status.data, sz) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->offsetSet = init_AntennaOffsetSet_from_ASN(src->offsetSet, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Gitsn_RTCMheader_delAndSetNull, (void *)&ret);
	}
	return ret;
}


bool_t GitsnAsnUtil_Gitsn_RTCMcorrectionsFromASN(RTCMcorrections* src, Gitsn_RTCMcorrections* dst, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || dst == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		if ((dst->msgs = init_RTCMmessageList_from_ASN((RTCMmessageList*)&src->msgs, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
			dst->msgCnt = src->msgCnt;
			dst->rev = src->rev;
			if (src->DEF_RTCMcorrections_timeStamp) dst->msgCnt = src->msgCnt;
			if (src->DEF_RTCMcorrections_anchorPoint)
			{
				if ((dst->anchorPoint = init_FullPositionVector_from_ASN(src->anchorPoint, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			if (src->DEF_RTCMcorrections_rtcmHeader)
			{
				if ((dst->rtcmHeader = init_RTCMheader_from_ASN(src->rtcmHeader, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			// if(src->DEF_RTCMcorrections_regional) 
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static Gitsn_RequestorType* init_RequestorType_from_ASN(RequestorType* src, Dz1Error* errp)
{
	Gitsn_RequestorType* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_RequestorType_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_RequestorType_delAndSetNull, (void*)&ret);
		ret->role = src->role;
		if (src->DEF_RequestorType_subrole) ret->subrole = src->subrole;
		if (src->DEF_RequestorType_request) ret->request = src->request;
		if (src->DEF_RequestorType_iso3883) ret->iso3883 = src->iso3883;
		if (src->DEF_RequestorType_hpmsType) ret->hpmsType = src->hpmsType;
		// if(src->DEF_RequestorType_regional) {}
		pthread_cleanup_pop(errp->code); // (Gitsn_RequestorType_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Gitsn_RequestorPositionVector* init_RequestorPositionVector_from_ASN(RequestorPositionVector* src, Dz1Error* errp)
{
	Gitsn_RequestorPositionVector* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_RequestorPositionVector_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_RequestorPositionVector_delAndSetNull, (void*)&ret);
		if ((ret->position = init_Position3D_from_ASN(src->position, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
			if (src->DEF_RequestorPositionVector_heading)ret->heading = src->heading;
			if (src->DEF_RequestorPositionVector_speed)
			{
				if ((ret->speed = init_TransmissionAndSpeed_from_ASN(src->speed, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_RequestorPositionVector_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Gitsn_RequestorDescription* init_RequestorDescription_from_ASN(RequestorDescription* src, Dz1Error* errp)
{
	Gitsn_RequestorDescription* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_RequestorDescription_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_RequestorDescription_delAndSetNull, (void*)&ret);
		if ((ret->id = init_VehicleID_from_ASN(src->id, errp)) == NULL) ERR_OUT(errp);
		else
		{
			if (src->DEF_RequestorDescription_type)
			{
				if ((ret->type = init_RequestorType_from_ASN(src->type, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			if(src->DEF_RequestorDescription_position)
			{
				if ((ret->position = init_RequestorPositionVector_from_ASN(src->position, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			if(src->DEF_RequestorDescription_name)
			{
				if ((ret->name = Dz1Str_ndup(src->name.asnstring, src->name.nchar, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			if(src->DEF_RequestorDescription_routeName)
			{
				if ((ret->routeName = Dz1Str_ndup(src->routeName.asnstring, src->routeName.nchar, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			if(src->DEF_RequestorDescription_transitStatus)
			{
				size_t sz = src->transitStatus.numbits + 7 / 8;
				if ((ret->transitStatus = Dz1Calloc(sz, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if (memcpy(ret->transitStatus, src->transitStatus.data, sz) == NULL) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
			if (src->DEF_RequestorDescription_transitOccupancy) ret->transitOccupancy = src->transitOccupancy;
			if (src->DEF_RequestorDescription_transitSchedule) ret->transitSchedule = src->transitSchedule;
			// if(src->DEF_RequestorDescription_regional) {}
		}

		pthread_cleanup_pop(errp->code); // (Gitsn_RequestorDescription_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Gitsn_IntersectionAccessPoint* init_IntersectionAccessPoint_from_ASN(IntersectionAccessPoint* src, Dz1Error* errp)
{
	Gitsn_IntersectionAccessPoint* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_IntersectionAccessPoint_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_IntersectionAccessPoint_delAndSetNull, (void*)&ret);
		switch (src->M)
		{
		case DEF_IntersectionAccessPoint_lane:
			ret->x.lane = src->elements.lane;
			ret->present = Gitsn_IntersectionAccessPointPresent_lane;
			break;
		case DEF_IntersectionAccessPoint_approach:
			ret->x.approach = src->elements.approach;
			ret->present = Gitsn_IntersectionAccessPointPresent_approach;
			break;
		case DEF_IntersectionAccessPoint_connection:
			ret->x.connection = src->elements.connection;
			ret->present = Gitsn_IntersectionAccessPointPresent_connection;
			break;
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_IntersectionAccessPoint_delAndSetNull, (void *)&ret);
	}
	return ret;
}


static Gitsn_SignalRequest* init_SignalRequest_from_ASN(SignalRequest* src, Dz1Error* errp)
{
	Gitsn_SignalRequest* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_SignalRequest_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_SignalRequest_delAndSetNull, (void*)&ret);
		if ((ret->id = init_IntersectionReferenceID_from_ASN(src->id, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->inBoundLane = init_IntersectionAccessPoint_from_ASN(src->inBoundLane, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
			ret->requestID = src->requestID;
			ret->requestType = src->requestType;
			if (src->DEF_SignalRequest_outBoundLane)
			{
				if ((ret->outBoundLane = init_IntersectionAccessPoint_from_ASN(src->outBoundLane, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_SignalRequest_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Gitsn_SignalRequestPackage* init_SignalRequestPackage_from_ASN(SignalRequestPackage* src, Dz1Error* errp)
{
	Gitsn_SignalRequestPackage* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_SignalRequestPackage_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_SignalRequestPackage_delAndSetNull, (void*)&ret);
		if ((ret->request = init_SignalRequest_from_ASN(src->request, errp)) == NULL) ERR_OUT(errp);
		else
		{
			if (src->DEF_SignalRequestPackage_minute) ret->minute = src->minute;
			if (src->DEF_SignalRequestPackage_second) ret->second = src->second;
			if (src->DEF_SignalRequestPackage_duration) ret->duration = src->duration;
			// if(src->DEF_SignalRequestPackage_regional)
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_SignalRequestPackage_delAndSetNull, (void *)&ret);
	}
	return ret;
}



static Gitsn_SignalRequestList* init_SignalRequestList_from_ASN(SignalRequestList* src, Dz1Error* errp)
{
	Gitsn_SignalRequestList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_SignalRequestList_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Gitsn_SignalRequestPackage* element = NULL;
		pthread_cleanup_push(Gitsn_SignalRequestList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			SignalRequestPackage* src_element = (SignalRequestPackage*)ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((element = init_SignalRequestPackage_from_ASN(src_element, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Gitsn_SignalRequestPackage_delAndSetNull, (void*)&element);
				if ((*errp = ret->add(ret, element)).code) ERR_OUT(errp);
				else
				{
					element = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (Gitsn_SignalRequestPackage_delAndSetNull, (void *)&element);
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_SignalRequestList_delAndSetNull, (void *)&ret);
	}
	return ret;
}


bool_t GitsnAsnUtil_Gitsn_SignalRequestMessageFromASN(SignalRequestMessage* src, Gitsn_SignalRequestMessage* dst, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || dst == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		dst->second = src->second;
		if ((dst->requestor = init_RequestorDescription_from_ASN(src->requestor, errp)) == NULL) ERR_OUT(errp);
		else
		{
			if (src->DEF_SignalRequestMessage_timeStamp) dst->timeStamp = src->timeStamp;
			if (src->DEF_SignalRequestMessage_sequenceNumber) dst->sequenceNumber = src->sequenceNumber;
			if (src->DEF_SignalRequestMessage_requests)
			{
				if ((dst->requests = init_SignalRequestList_from_ASN((SignalRequestList*)&src->requests, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			// if(src->DEF_SignalRequestMessage_regional) 
		}
	}
	return ERR_IS_SUCCESS(errp);
}


static Gitsn_SignalRequesterInfo* init_SignalRequesterInfo_from_ASN(SignalRequesterInfo* src, Dz1Error* errp)
{
	Gitsn_SignalRequesterInfo* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_SignalRequesterInfo_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_SignalRequesterInfo_delAndSetNull, (void*)&ret);
		if ((ret->id = init_VehicleID_from_ASN(src->id, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->request = src->request;
			ret->sequenceNumber = src->sequenceNumber;
			if (src->DEF_SignalRequesterInfo_role) ret->role = src->role;
			if (src->DEF_SignalRequesterInfo_typeData)
			{
				if ((ret->typeData = init_RequestorType_from_ASN(src->typeData, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_SignalRequesterInfo_delAndSetNull, (void *)&ret);
	}
	return ret;
}


static Gitsn_SignalStatusPackage* init_SignalStatusPackage_from_ASN(SignalStatusPackage* src, Dz1Error* errp)
{
	Gitsn_SignalStatusPackage* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_SignalStatusPackage_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_SignalStatusPackage_delAndSetNull, (void*)&ret);

		if ((ret->inboundOn = init_IntersectionAccessPoint_from_ASN(src->inboundOn, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->status = src->status;

			if (src->DEF_SignalStatusPackage_requester)
			{
				if ((ret->requester = init_SignalRequesterInfo_from_ASN(src->requester, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			if (src->DEF_SignalStatusPackage_outboundOn)
			{
				if ((ret->outboundOn = init_IntersectionAccessPoint_from_ASN(src->outboundOn, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			if (src->DEF_SignalStatusPackage_minute) ret->minute = src->minute;
			if (src->DEF_SignalStatusPackage_second) ret->second = src->second;
			if (src->DEF_SignalStatusPackage_duration) ret->duration = src->duration;
			// if(src->DEF_SignalStatusPackage_regional)
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_SignalStatusPackage_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Gitsn_SignalStatusPackageList* init_SignalStatusPackageList_from_ASN(SignalStatusPackageList* src, Dz1Error* errp)
{
	Gitsn_SignalStatusPackageList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_SignalStatusPackageList_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Gitsn_SignalStatusPackage* element = NULL;
		pthread_cleanup_push(Gitsn_SignalStatusPackageList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			SignalStatusPackage* src_element = (SignalStatusPackage*)ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((element = init_SignalStatusPackage_from_ASN(src_element, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Gitsn_SignalStatusPackage_delAndSetNull, (void*)&element);
				if ((*errp = ret->add(ret, element)).code) ERR_OUT(errp);
				else
				{
					element = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (Gitsn_SignalStatusPackage_delAndSetNull, (void *)&element);
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_SignalStatusPackageList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Gitsn_SignalStatus* init_SignalStatus_from_ASN(SignalStatus* src, Dz1Error* errp)
{
	Gitsn_SignalStatus* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_SignalStatus_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_SignalStatus_delAndSetNull, (void*)&ret);
		ret->sequenceNumber = src->sequenceNumber;
		if ((ret->id = init_IntersectionReferenceID_from_ASN(src->id, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->sigStatus = init_SignalStatusPackageList_from_ASN((SignalStatusPackageList*)&src->sigStatus, errp)) == NULL) ERR_OUT(errp);
		else
		{
			// regional
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Gitsn_SignalStatus_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Gitsn_SignalStatusList* init_SignalStatusList_from_ASN(SignalStatusList* src, Dz1Error* errp)
{
	Gitsn_SignalStatusList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_SignalStatusList_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Gitsn_SignalStatus* element = NULL;
		pthread_cleanup_push(Gitsn_SignalStatusList_delAndSetNull, (void*)&ret);
		for (int i = 1; i <= (int)src->count; i++)
		{
			SignalStatus* src_element = (SignalStatus*)ASN1_Get_Node_Index(src, i);
			if (src_element == NULL) ERR_SET_OUT(errp, EFAULT);
			else if ((element = init_SignalStatus_from_ASN(src_element, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Gitsn_SignalStatus_delAndSetNull, (void*)&element);
				if ((*errp = ret->add(ret, element)).code) ERR_OUT(errp);
				else
				{
					element = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (Gitsn_SignalStatus_delAndSetNull, (void *)&element);
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_SignalStatusList_delAndSetNull, (void *)&ret);
	}
	return ret;
}


bool_t GitsnAsnUtil_Gitsn_SignalStatusMessageFromASN(SignalStatusMessage* src, Gitsn_SignalStatusMessage* dst, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || dst == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		dst->second = src->second;
		if ((dst->status = init_SignalStatusList_from_ASN((SignalStatusList*)&src->status, errp)) == NULL) ERR_OUT(errp);
		else
		{
			if (src->DEF_SignalStatusMessage_timeStamp) dst->timeStamp = src->timeStamp;
			if (src->DEF_SignalStatusMessage_sequenceNumber) dst->sequenceNumber = src->sequenceNumber;
			// if(src->DEF_SignalStatusMessage_regional) 
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t GitsnAsnUtil_Gitsn_PersonalSafetyMessageFromASN(PersonalSafetyMessage* src, Gitsn_PersonalSafetyMessage* dst, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || dst == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		dst->basicType = src->basicType;
		dst->secMark = src->secMark;
		dst->msgCnt = src->msgCnt;
		dst->speed = src->speed;
		dst->heading = src->heading;

		if ((dst->id = Dz1Str_ndup(src->id.data, 4, errp)) == NULL) ERR_OUT(errp);
		else if ((dst->position = init_Position3D_from_ASN(src->position, errp)) == NULL) ERR_OUT(errp);
		else if ((dst->accuracy = init_PositionalAccuracy_from_ASN(src->accuracy, errp)) == NULL) ERR_OUT(errp);
		else
		{
			if (src->DEF_PersonalSafetyMessage_accelSet)
			{
				if ((dst->accelSet = init_AccelerationSet4Way_from_ASN(src->accelSet, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			if (src->DEF_PersonalSafetyMessage_pathHistory)
			{
				if ((dst->pathHistory = init_PathHistory_from_ASN(src->pathHistory, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			if (src->DEF_PersonalSafetyMessage_pathPrediction)
			{
				if ((dst->pathPrediction = init_PathPrediction_from_ASN(src->pathPrediction, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			if (src->DEF_PersonalSafetyMessage_propulsion)
			{
				if ((dst->propulsion = init_PropelledInformation_from_ASN(src->propulsion, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			if (src->DEF_PersonalSafetyMessage_useState)
			{
				size_t sz = src->useState.numbits + 7 / 8;
				if ((dst->useState = Dz1Calloc(sz, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if (memcpy(dst->useState, src->useState.data, sz) == NULL) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
			if (src->DEF_PersonalSafetyMessage_crossRequest) dst->crossRequest = src->crossRequest;
			if (src->DEF_PersonalSafetyMessage_crossState) dst->crossState = src->crossState;
			if (src->DEF_PersonalSafetyMessage_clusterSize) dst->clusterSize = src->clusterSize;
			if (src->DEF_PersonalSafetyMessage_clusterRadius) dst->clusterRadius = src->clusterRadius;
			if (src->DEF_PersonalSafetyMessage_eventResponderType) dst->eventResponderType = src->eventResponderType;
			if (src->DEF_PersonalSafetyMessage_activityType)
			{
				size_t sz = src->activityType.numbits + 7 / 8;
				if ((dst->activityType = Dz1Calloc(sz, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if (memcpy(dst->activityType, src->activityType.data, sz) == NULL) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
			if (src->DEF_PersonalSafetyMessage_activitySubType)
			{
				size_t sz = src->activitySubType.numbits + 7 / 8;
				if ((dst->activitySubType = Dz1Calloc(sz, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if (memcpy(dst->activitySubType, src->activitySubType.data, sz) == NULL) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
			if (src->DEF_PersonalSafetyMessage_assistType)
			{
				size_t sz = src->assistType.numbits + 7 / 8;
				if ((dst->assistType = Dz1Calloc(sz, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if (memcpy(dst->assistType, src->assistType.data, sz) == NULL) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
			if (src->DEF_PersonalSafetyMessage_sizing)
			{
				size_t sz = src->sizing.numbits + 7 / 8;
				if ((dst->sizing = Dz1Calloc(sz, 1, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
				else if (memcpy(dst->sizing, src->sizing.data, sz) == NULL) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
			if (src->DEF_PersonalSafetyMessage_attachment) dst->attachment = src->attachment;
			if (src->DEF_PersonalSafetyMessage_attachmentRadius) dst->attachmentRadius = src->attachmentRadius;
			if (src->DEF_PersonalSafetyMessage_animalType) dst->animalType = src->animalType;
			// if(src->DEF_PersonalSafetyMessage_regional)
		}
	}
	return ERR_IS_SUCCESS(errp);
}




Dz1Binary* GitsnAsnUtil_getValueFromMessageFrame(Dz1Binary* src, int* msg_id, Dz1Error* errp)
{
	Dz1Binary* ret = NULL;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	MessageFrame asn;
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	size_t consume_sz = 0;
	ASN1_Save_WORKSPACE(&ws, src->data, src->size);
	ws.dataSize = src->size;
	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ MessageFrame decode start...\n"));
	if (ASN1_PER_UNAlign_Dec_MessageFrame(&ws, &asn) < 0) ERR_SET_OUT(errp, EFAULT);
	else
	{
		if ((ret = Dz1Binary_new(asn.value.data, asn.value.numocts, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			*msg_id = (int)asn.messageId;
			Dz1Error_set(errp, 0);
		}
	}
	pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	return ret;
}

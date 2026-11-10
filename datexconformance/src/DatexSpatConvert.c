/* SPaT conversion adapted from the preserved legacy source.
   Release generated default objects before replacement; preserve wire/data rules. */
#include <GitsnAsnUtil.h>
#include <dz1_gasn_support.h>
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
			if ((ret->timing = (Gitsn_TimeChangeDetails_delAndSetNull(&ret->timing), init_TimeChangeDetails_from_ASN(src->timing, errp))) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_MovementEvent_speeds)
		{
			if ((ret->speeds = (Gitsn_AdvisorySpeedList_delAndSetNull(&ret->speeds), init_AdvisorySpeedList_from_ASN(&src->speeds, errp))) == NULL) ERR_SET_OUT(errp, EFAULT);
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
			if ((ret->maneuverAssistList = (Gitsn_ManeuverAssistList_delAndSetNull(&ret->maneuverAssistList), init_ManeuverAssistList_from_ASN(&src->maneuverAssistList, errp))) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_MovementState_regional) {}

		if (0) {}
		else if ((ret->state_time_speed = (Gitsn_MovementEventList_delAndSetNull(&ret->state_time_speed), init_MovementEventList_from_ASN(&src->state_time_speed, errp))) == NULL) ERR_SET_OUT(errp, EFAULT);
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
			if ((ret->enabledLanes = (Gitsn_EnabledLaneList_delAndSetNull(&ret->enabledLanes), init_EnabledLaneList_from_ASN(&src->enabledLanes, errp))) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_IntersectionState_maneuverAssistList)
		{
			if ((ret->maneuverAssistList = (Gitsn_ManeuverAssistList_delAndSetNull(&ret->maneuverAssistList), init_ManeuverAssistList_from_ASN(&src->maneuverAssistList, errp))) == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		}
		if (src->DEF_IntersectionState_regional)
		{
		}

		if (0) {}
		else if ((ret->id = (Gitsn_IntersectionReferenceID_delAndSetNull(&ret->id), init_IntersectionReferenceID_from_ASN(src->id, errp))) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->states = (Gitsn_MovementList_delAndSetNull(&ret->states), init_MovementList_from_ASN(&src->states, errp))) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			size_t sz = (src->status.numbits + 7) / 8;
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

bool_t DatexSpatFromASN(SPAT* src, Gitsn_SPAT* dst, Dz1Error* err)
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
		else if ((dst->intersections = (Gitsn_IntersectionStateList_delAndSetNull(&dst->intersections), init_IntersectionStateList_from_ASN(&src->intersections, errp))) == NULL) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);

	}

	return ERR_IS_SUCCESS(errp);
}




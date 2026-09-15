#include <TechnicalRegulation1Util.h>

static CurrentLinkStateEntry* CurrentLinkStateEntry_fromDimz(Dz1CurrentLinkState* src, Dz1Error* errp)
{
	CurrentLinkStateEntry* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = CurrentLinkStateEntry_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(CurrentLinkStateEntry_delAndSetNull, (void*)&ret);
		if (0) {}
		else if ((ret->link_id = Dz1Str_ndup(src->link_LinkIdNumber->data, src->link_LinkIdNumber->size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->speed_rate = (u16_t)src->link_SpeedRate;

			if (src->link_VolumeRate)
			{
				ret->volume_rate = *src->link_VolumeRate;
			}
			if (src->link_DensityRate) ret->density_rate = *src->link_DensityRate;
			if (src->link_TravelTimeQuantity) ret->ttime_qty = *src->link_TravelTimeQuantity;
			if (src->link_DelayQuantity) ret->delay_qty = *src->link_DelayQuantity;
			if (src->tfdt_VehicleQueueLengthQuantity) ret->veh_q_len_qty = *src->tfdt_VehicleQueueLengthQuantity;
			ret->tfdt_occupy_percent = src->tfdt_OccupancyPercent;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (CurrentLinkStateEntry_delAndSetNull, (void*)&ret);
	}
	return ret;
}

CurrentLinkStateList* CurrentLinkStateList_fromDimz(Dz1CurrentLinkStateResponse* src, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	CurrentLinkStateList* ret = NULL;

	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = CurrentLinkStateList_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1CurrentLinkState** list = NULL;
		int cnt = 0;
		pthread_cleanup_push(CurrentLinkStateList_delAndSetNull, (void*)&ret);
		if ((list = src->get_array(src, &cnt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1CurrentLinkState* src_entry = NULL;
			for (int i = 0; errp->code == 0 && i < cnt; i++)
			{
				src_entry = list[i];
				CurrentLinkStateEntry* entry = NULL;
				if ((entry = CurrentLinkStateEntry_fromDimz(src_entry, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(CurrentLinkStateEntry_delAndSetNull, (void*)&entry);
					if ((*errp = ret->add(ret, entry)).code) ERR_OUT(errp);
					else
					{
						entry = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (CurrentLinkStateEntry_delAndSetNull, (void*)&entry);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (CurrentLinkStateList_delAndSetNull, (void*)&ret);
	}
	return ret;
}


static EventIdentityEntry* EventIdentityEntry_fromDimz(Dz1EventIdentity* src, Dz1Error* errp)
{
	EventIdentityEntry* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = EventIdentityEntry_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(EventIdentityEntry_delAndSetNull, (void*)&ret);
		if (0) {}
		else if ((ret->node_id = Dz1Str_ndup(src->node_NodeIdNumber->data, src->node_NodeIdNumber->size, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->link_id = Dz1Str_ndup(src->link_LinkIdNumber->data, src->link_LinkIdNumber->size, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->loc_jurisdiction_name = Dz1Str_ndup(src->evnt_LocationJurisDictionNameText->data, src->evnt_LocationJurisDictionNameText->size, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->loc_link_id = Dz1Str_ndup(src->evnt_LocationLinkIdNumber->data, src->evnt_LocationLinkIdNumber->size, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->loc_node_id = Dz1Str_ndup(src->evnt_LocationNodeIdNumber->data, src->evnt_LocationNodeIdNumber->size, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->start_time = Dz1Str_ndup(src->evnt_TimelineStartGeneralizedTime->data, src->evnt_TimelineEndGeneralizedTime->size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->lanes_blocked_or_closed_num = src->evnt_LanesBlockedOrClosedNumber;
			// ret->lanes_shoulder_block_code = *src->evnt_LanesShouldersBlockedCode->bits;
			ret->lanes_shoulder_block_code = Dz1Calloc(src->evnt_LanesShouldersBlockedCode->allocByte, 1, errp);
			memcpy(ret->lanes_shoulder_block_code, src->evnt_LanesShouldersBlockedCode->bits, src->evnt_LanesShouldersBlockedCode->allocByte);
			ret->time_duration = src->evnt_TimelineDurationTime;
			
			if (src->evnt_IdentificationNumber) ret->identification_num = *src->evnt_IdentificationNumber;
			if (src->evnt_DescriptionTypeEventCode) ret->evnt_code = *src->evnt_DescriptionTypeEventCode;
			if (src->evnt_DescriptionTypeSpecialEventCode) ret->special_evnt_code = *src->evnt_DescriptionTypeEventCode;
			if (src->evnt_DescriptionPlannedRoadWayClosureCode) ret->planned_road_closure_code = *src->evnt_DescriptionPlannedRoadWayClosureCode;

			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (EventIdentityEntry_delAndSetNull, (void*)&ret);
	}
	return ret;
}

EventIdentityList* EventIdentityList_fromDimz(Dz1EventIdentityResponse* src, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	EventIdentityList* ret = NULL;

	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = EventIdentityList_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1EventIdentity** list = NULL;
		int cnt = 0;
		pthread_cleanup_push(EventIdentityList_delAndSetNull, (void*)&ret);
		if ((list = src->get_array(src, &cnt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1EventIdentity* src_entry = NULL;
			for (int i = 0; errp->code == 0 && i < cnt; i++)
			{
				src_entry = list[i];
				EventIdentityEntry* entry = NULL;
				if ((entry = EventIdentityEntry_fromDimz(src_entry, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(EventIdentityEntry_delAndSetNull, (void*)&entry);
					if ((*errp = ret->add(ret, entry)).code) ERR_OUT(errp);
					else
					{
						entry = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (EventIdentityEntry_delAndSetNull, (void*)&entry);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (EventIdentityList_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static IncidentIdentityEntry* IncidentIdentityEntry_fromDimz(Dz1IncidentIdentity* src, Dz1Error* errp)
{
	IncidentIdentityEntry* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = IncidentIdentityEntry_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(IncidentIdentityEntry_delAndSetNull, (void*)&ret);
		if (0) {}
		else if ((ret->node_id = Dz1Str_ndup(src->node_NodeIdNumber->data, src->node_NodeIdNumber->size, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->link_id = Dz1Str_ndup(src->link_LinkIdNumber->data, src->link_LinkIdNumber->size, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->update_time = Dz1Str_ndup(src->evnt_UpdateGeneralizedTime->data, src->evnt_UpdateGeneralizedTime->size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->property_damage_code = *src->evnt_IncidentPropertyDamageCode->bits;

			if (src->evnt_LocationLinearDistanceOffsetBeginNumber) ret->loc_offset_begin = *src->evnt_LocationLinearDistanceOffsetBeginNumber;
			if (src->evnt_LinearDistanceoffsetEndNumber) ret->loc_offset_end = *src->evnt_LinearDistanceoffsetEndNumber;
			if (src->evnt_IncidentHumanFatalitiesCountQuantity) ret->fatality_cnt = *src->evnt_IncidentHumanFatalitiesCountQuantity;
			if (src->evnt_IncidentHumanInjuriesCountQuantity) ret->injuries_cnt = *src->evnt_IncidentHumanInjuriesCountQuantity;
			if (src->evnt_IncidentPropertyDamageOther)
			{
				if ((ret->property_damage_desc = Dz1Str_ndup(src->evnt_IncidentPropertyDamageOther->data, src->evnt_IncidentPropertyDamageOther->size, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(errp->code); // (IncidentIdentityEntry_delAndSetNull, (void*)&ret);
	}
	return ret;
}

IncidentIdentityList* IncidentIdentityList_fromDimz(Dz1IncidentIdentityResponse* src, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	IncidentIdentityList* ret = NULL;

	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = IncidentIdentityList_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1IncidentIdentity** list = NULL;
		int cnt = 0;
		pthread_cleanup_push(IncidentIdentityList_delAndSetNull, (void*)&ret);
		if ((list = src->get_array(src, &cnt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1IncidentIdentity* src_entry = NULL;
			for (int i = 0; errp->code == 0 && i < cnt; i++)
			{
				src_entry = list[i];
				IncidentIdentityEntry* entry = NULL;
				if ((entry = IncidentIdentityEntry_fromDimz(src_entry, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(IncidentIdentityEntry_delAndSetNull, (void*)&entry);
					if ((*errp = ret->add(ret, entry)).code) ERR_OUT(errp);
					else
					{
						entry = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (IncidentIdentityEntry_delAndSetNull, (void*)&entry);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (IncidentIdentityList_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static IncidentConditionsEntry* IncidentConditionsEntry_fromDimz(Dz1IncidentConditions* src, Dz1Error* errp)
{
	IncidentConditionsEntry* ret = NULL;

	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = IncidentConditionsEntry_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(IncidentConditionsEntry_delAndSetNull, (void*)&ret);

		if (0) {}
		else if ((ret->node_id = Dz1Str_ndup(src->node_NodeIdNumber->data, src->node_NodeIdNumber->size, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->link_id = Dz1Str_ndup(src->link_LinkIdNumber->data, src->link_LinkIdNumber->size, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->contact_org_name = Dz1Str_ndup(src->orgn_ContatOrganizationNameText->data, src->orgn_ContatOrganizationNameText->size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->incident_code = src->evnt_DescriptionTypeIncidentCode;
			ret->veh_invloved_code = *src->evnt_IncidentVehiclesInvolvedCode->bits;
			ret->status_code = src->evnt_IncidentStatusCode;
			ret->update_type_code = src->evnt_UpdateTypeCode;
			if (src->evnt_DescriptionTypeIncidentOther)
			{
				if ((ret->other_incident_desc = Dz1Str_ndup(src->evnt_DescriptionTypeIncidentOther->data, src->evnt_DescriptionTypeIncidentOther->size, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}

			if(src->evnt_IncidentVehiclesInvolvedOther)
			{
				if ((ret->other_veh_invloved_desc = Dz1Str_ndup(src->evnt_IncidentVehiclesInvolvedOther->data, src->evnt_IncidentVehiclesInvolvedOther->size, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}

			if (src->evnt_IncidentStatusOther)
			{
				if ((ret->other_status_desc= Dz1Str_ndup(src->evnt_IncidentStatusOther->data, src->evnt_IncidentStatusOther->size, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			if (src->evnt_UpdateTypeOther)
			{
				if ((ret->other_update_desc = Dz1Str_ndup(src->evnt_UpdateTypeOther->data, src->evnt_UpdateTypeOther->size, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(errp->code); // (IncidentConditionsEntry_delAndSetNull, (void*)&ret);
	}
	return ret;
}


IncidentConditionsList* IncidentConditionsList_fromDimz(Dz1IncidentConditionsResponse* src, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	IncidentConditionsList* ret = NULL;

	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = IncidentConditionsList_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1IncidentConditions** list = NULL;
		int cnt = 0;
		pthread_cleanup_push(IncidentConditionsList_delAndSetNull, (void*)&ret);
		if ((list = src->get_array(src, &cnt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1IncidentConditions* src_entry = NULL;
			for (int i = 0; errp->code == 0 && i < cnt; i++)
			{
				src_entry = list[i];
				IncidentConditionsEntry* entry = NULL;
				if ((entry = IncidentConditionsEntry_fromDimz(src_entry, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(IncidentConditionsEntry_delAndSetNull, (void*)&entry);
					if ((*errp = ret->add(ret, entry)).code) ERR_OUT(errp);
					else
					{
						entry = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (IncidentConditionsEntry_delAndSetNull, (void*)&entry);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (IncidentConditionsList_delAndSetNull, (void*)&ret);
	}
	return ret;
}


static RoadwaySurfaceStatusEntry* RoadwaySurfaceStatusEntry_fromDimz(Dz1RoadwaySurfaceStatus* src, Dz1Error* errp)
{
	RoadwaySurfaceStatusEntry* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = RoadwaySurfaceStatusEntry_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(RoadwaySurfaceStatusEntry_delAndSetNull, (void*)&ret);

		if (0) {}
		else if ((ret->node_id = Dz1Str_ndup(src->node_NodeIdNumber->data, src->node_NodeIdNumber->size, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->link_id = Dz1Str_ndup(src->link_LinkIdNumber->data, src->link_LinkIdNumber->size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->surface_cond_code = *src->link_SurfaceConditionCode->bits;
			ret->land_blocked_or_closed_code = *src->link_LandBlockedOrClosedCode->bits;
			if (src->evsn_DataSurfacePrecipitationDepth) ret->precipitation_depth = *src->evsn_DataSurfacePrecipitationDepth;
			if (src->evsn_DataSurfaceTemperatureQuantity) ret->temperature_qty= *src->evsn_DataSurfaceTemperatureQuantity;

		}
		pthread_cleanup_pop(errp->code); // (RoadwaySurfaceStatusEntry_delAndSetNull, (void*)&ret);
	}
	return ret;
}

RoadwaySurfaceStatusList* RoadwaySurfaceStatusList_fromDimz(Dz1RoadwaySurfaceStatusResponse* src, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	RoadwaySurfaceStatusList* ret = NULL;

	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = RoadwaySurfaceStatusList_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1RoadwaySurfaceStatus** list = NULL;
		int cnt = 0;
		pthread_cleanup_push(RoadwaySurfaceStatusList_delAndSetNull, (void*)&ret);
		if ((list = src->get_array(src, &cnt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1RoadwaySurfaceStatus* src_entry = NULL;
			for (int i = 0; errp->code == 0 && i < cnt; i++)
			{
				src_entry = list[i];
				RoadwaySurfaceStatusEntry* entry = NULL;
				if ((entry = RoadwaySurfaceStatusEntry_fromDimz(src_entry, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(RoadwaySurfaceStatusEntry_delAndSetNull, (void*)&entry);
					if ((*errp = ret->add(ret, entry)).code) ERR_OUT(errp);
					else
					{
						entry = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (RoadwaySurfaceStatusEntry_delAndSetNull, (void*)&entry);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (RoadwaySurfaceStatusList_delAndSetNull, (void*)&ret);
	}
	return ret;
}


static WeatherInformationEntry* WeatherInformationEntry_fromDimz(Dz1WeatherInformation* src, Dz1Error* errp)
{
	WeatherInformationEntry* ret = NULL;

	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = WeatherInformationEntry_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(WeatherInformationEntry_delAndSetNull, (void*)&ret);
		ret->forecast_or_actual = src->wthr_ForecastOrActualCode;
		ret->probability = src->wthr_ProbabilityPercent;

		if (src->wthr_TemperatureQuantity) ret->temperature = *src->wthr_TemperatureQuantity;
		if (src->wthr_HighTemperatureQuantity) ret->high_temperature = *src->wthr_HighTemperatureQuantity;
		if (src->wthr_LowTemperatureQuantity) ret->low_temperature = *src->wthr_LowTemperatureQuantity;
		if (src->wthr_SpecialConditions) ret->special_cond = *src->wthr_SpecialConditions->bits;
		if (src->wthr_SpecialConditionsOther)
		{
			if ((ret->other_cond_desc = Dz1Str_ndup(src->wthr_SpecialConditionsOther->data, src->wthr_SpecialConditionsOther->size, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		if (src->wthr_VisibilityQuantity) ret->visibility = *src->wthr_VisibilityQuantity;
		if (src->wthr_WindSpeedQuantity) ret->wind_speed = *src->wthr_WindSpeedQuantity;
		if (src->wthr_WindDirectionCode) ret->wind_direct_code = *src->wthr_WindDirectionCode;
		if (src->wthr_HumidityQuantity) ret->humidity = *src->wthr_HumidityQuantity;
		if (src->wthr_PressureQuantity) ret->pressure = *src->wthr_PressureQuantity;
		if (src->wthr_SunriseTimeGeneralizedTime)
		{
			if ((ret->sunrise_time = Dz1Str_ndup(src->wthr_SunriseTimeGeneralizedTime->data, src->wthr_SunriseTimeGeneralizedTime->size, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		if(src->wthr_SunsetTimeGeneralizedTime) 
		{
			if ((ret->sunset_time = Dz1Str_ndup(src->wthr_SunsetTimeGeneralizedTime->data, src->wthr_SunsetTimeGeneralizedTime->size, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (WeatherInformationEntry_delAndSetNull, (void*)&ret);
	}
	return ret;
}

WeatherInformationList* WeatherInformationList_fromDimz(Dz1WeatherInformationResponse* src, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	WeatherInformationList* ret = NULL;

	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = WeatherInformationList_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1WeatherInformation** list = NULL;
		int cnt = 0;
		pthread_cleanup_push(WeatherInformationList_delAndSetNull, (void*)&ret);
		if ((list = src->get_array(src, &cnt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1WeatherInformation* src_entry = NULL;
			for (int i = 0; errp->code == 0 && i < cnt; i++)
			{
				src_entry = list[i];
				WeatherInformationEntry* entry = NULL;
				if ((entry = WeatherInformationEntry_fromDimz(src_entry, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(WeatherInformationEntry_delAndSetNull, (void*)&entry);
					if ((*errp = ret->add(ret, entry)).code) ERR_OUT(errp);
					else
					{
						entry = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (WeatherInformationEntry_delAndSetNull, (void*)&entry);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (WeatherInformationList_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static LinkRoadwayGeometryEntry* LinkRoadwayGeometryEntry_fromDimz(Dz1LinkRoadwayGeometry* src, Dz1Error* errp)
{
	LinkRoadwayGeometryEntry* ret = NULL;

	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = LinkRoadwayGeometryEntry_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(LinkRoadwayGeometryEntry_delAndSetNull, (void*)&ret);
		if (0) {}
		else if ((ret->begin_node_id = Dz1Str_ndup(src->link_BeginNodeIdNumber->data, src->link_BeginNodeIdNumber->size, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->end_node_id = Dz1Str_ndup(src->link_EndNodeIdNumber->data, src->link_EndNodeIdNumber->size, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->jurisdiction = Dz1Str_ndup(src->link_JurisdictionText->data, src->link_JurisdictionText->size, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->name = Dz1Str_ndup(src->link_NameText->data, src->link_NameText->size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->type_code = *src->link_TypeCode->bits;
			ret->length = src->link_LengthQuantity;
			ret->pavement_type_code = *src->link_PavementTypeCode->bits;
			ret->median_type_code = src->tfmg_LinkMedianTypeCode;
			ret->num_lanes = src->tfmg_LinkNumLanesNumber;
			ret->num_open_lanes = src->tfmg_LinkNumLanesOpenNumber;

			if (src->link_BiginNodeLatitudeLocation) ret->begin_node_latitude = *src->link_BiginNodeLatitudeLocation;
			if (src->link_BeginNodeLongitudeLocation) ret->begin_node_longitude = *src->link_BeginNodeLongitudeLocation;
			if (src->link_EndNodeLatitudeLocation) ret->end_node_latitude = *src->link_EndNodeLatitudeLocation;
			if (src->link_EndNodeLongitudeLocation) ret->end_node_longitude = *src->link_EndNodeLongitudeLocation;
			if (src->tfmg_LinkHeigthRestrictionQunatity) ret->restriction_height = *src->tfmg_LinkHeigthRestrictionQunatity;
			if (src->tfmg_LinkLeftShoulderWidthQuantity) ret->left_shoulder_width = *src->tfmg_LinkLeftShoulderWidthQuantity;
			if (src->tfmg_LinkLengthRestrictionQuatity) ret->restriction_length = *src->tfmg_LinkLengthRestrictionQuatity;
			if (src->tfmg_LinkRightShoulderWidthQuantity) ret->right_shoulder_width = *src->tfmg_LinkRightShoulderWidthQuantity;
		}
		pthread_cleanup_pop(1); // (LinkRoadwayGeometryEntry_delAndSetNull, (void*)&ret);
	}
	return ret;
}

LinkRoadwayGeometryList* LinkRoadwayGeometryList_fromDimz(Dz1LinkRoadwayGeometryResponse* src, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	LinkRoadwayGeometryList* ret = NULL;

	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = LinkRoadwayGeometryList_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1LinkRoadwayGeometry** list = NULL;
		int cnt = 0;
		pthread_cleanup_push(LinkRoadwayGeometryList_delAndSetNull, (void*)&ret);
		if ((list = src->get_array(src, &cnt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1LinkRoadwayGeometry* src_entry = NULL;
			for (int i = 0; errp->code == 0 && i < cnt; i++)
			{
				src_entry = list[i];
				LinkRoadwayGeometryEntry* entry = NULL;
				if ((entry = LinkRoadwayGeometryEntry_fromDimz(src_entry, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(LinkRoadwayGeometryEntry_delAndSetNull, (void*)&entry);
					if ((*errp = ret->add(ret, entry)).code) ERR_OUT(errp);
					else
					{
						entry = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (LinkRoadwayGeometryEntry_delAndSetNull, (void*)&entry);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (LinkRoadwayGeometryList_delAndSetNull, (void*)&ret);
	}
	return ret;
}


static ProbeVehicleDetectionEntry* ProbeVehicleDetectionEntry_fromDimz(Dz1ProbeVehicleDetection* src, Dz1Error* errp)
{
	ProbeVehicleDetectionEntry* ret = NULL;

	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = ProbeVehicleDetectionEntry_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ProbeVehicleDetectionEntry_delAndSetNull, (void*)&ret);

		if (0) {}
		else if ((ret->veh_id = Dz1Str_ndup(src->vpbd_VehicleIdNumber->data, src->vpbd_VehicleIdNumber->size, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->veh_timein = Dz1Str_ndup(src->vpbd_VehicleTimeInGeneralizedTime->data, src->vpbd_VehicleTimeInGeneralizedTime->size, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->veh_timeout = Dz1Str_ndup(src->vpbd_VehicleTimeOutGeneralizedTime->data, src->vpbd_VehicleTimeOutGeneralizedTime->size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->veh_class = src->vpbd_VehicleClass;
			ret->veh_traveltime = src->vpbd_VehicleTravelTimeTime;

			if (src->vpbd_VehicleAverageSpeedRate) ret->veh_avg_speed = *src->vpbd_VehicleAverageSpeedRate;
			if (src->vpbd_AviReaderIdNumber)
			{
				if ((ret->ref_avi_id = Dz1Str_ndup(src->vpbd_AviReaderIdNumber->data, src->vpbd_AviReaderIdNumber->size, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			if (src->vpbd_AviReaderLocationLatitude) ret->avi_latitude = *src->vpbd_AviReaderLocationLatitude;
			if (src->vpbd_AviReaderLocationLongitude) ret->avi_longitude = *src->vpbd_AviReaderLocationLongitude;
			if (src->vpbd_ReferenceLocatorIdNumber)
			{
				if ((ret->ref_avi_id = Dz1Str_ndup(src->vpbd_ReferenceLocatorIdNumber->data, src->vpbd_ReferenceLocatorIdNumber->size, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			if (src->vpbd_ReferenceLocatorLatitude) ret->ref_avi_latitude = *src->vpbd_ReferenceLocatorLatitude;
			if (src->vpbd_ReferenceLocatorLongitude) ret->ref_avi_longitude = *src->vpbd_ReferenceLocatorLongitude;
		}

		pthread_cleanup_pop(errp->code); // (ProbeVehicleDetectionEntry_delAndSetNull, (void*)&ret);
	}
	return ret;
}

ProbeVehicleDetectionList* ProbeVehicleDetectionList_fromDimz(Dz1ProbeVehicleDetectionResponse* src, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	ProbeVehicleDetectionList* ret = NULL;

	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = ProbeVehicleDetectionList_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1ProbeVehicleDetection** list = NULL;
		int cnt = 0;
		pthread_cleanup_push(ProbeVehicleDetectionList_delAndSetNull, (void*)&ret);
		if ((list = src->get_array(src, &cnt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1ProbeVehicleDetection* src_entry = NULL;
			for (int i = 0; errp->code == 0 && i < cnt; i++)
			{
				src_entry = list[i];
				ProbeVehicleDetectionEntry* entry = NULL;
				if ((entry = ProbeVehicleDetectionEntry_fromDimz(src_entry, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(ProbeVehicleDetectionEntry_delAndSetNull, (void*)&entry);
					if ((*errp = ret->add(ret, entry)).code) ERR_OUT(errp);
					else
					{
						entry = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (ProbeVehicleDetectionEntry_delAndSetNull, (void*)&entry);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (ProbeVehicleDetectionList_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static DetectorCollectionEntry* DetectorCollectionEntry_fromDimz(Dz1DetectorCollection* src, Dz1Error* errp)
{
	DetectorCollectionEntry* ret = NULL;

	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = DetectorCollectionEntry_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(DetectorCollectionEntry_delAndSetNull, (void*)&ret);

		if (0) {}
		else if ((ret->detector_id = Dz1Str_ndup(src->tfdt_DetectorIdNumber->data, src->tfdt_DetectorIdNumber->size, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->detector_time = Dz1Str_ndup(src->tfdt_DetectorTimeGeneralizedTime->data, src->tfdt_DetectorTimeGeneralizedTime->size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->speed_rate = src->tfdt_SpeedRate;
			ret->occupancy_percent = src->tfdt_OccupancyPercent;

			if (src->tfdt_VolumeRate) ret->volume_rate = *src->tfdt_VolumeRate;
			if (src->tfdt_VehicleQueueLengthQuantity) ret->veh_q_len_qty = *src->tfdt_VehicleQueueLengthQuantity;
		}
		pthread_cleanup_pop(errp->code); // (DetectorCollectionEntry_delAndSetNull, (void*)&ret);
	}
	return ret;
}


DetectorCollectionList* DetectorCollectionList_fromDimz(Dz1DetectorCollectionResponse* src, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	DetectorCollectionList* ret = NULL;

	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = DetectorCollectionList_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1DetectorCollection** list = NULL;
		int cnt = 0;
		pthread_cleanup_push(DetectorCollectionList_delAndSetNull, (void*)&ret);
		if ((list = src->get_array(src, &cnt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1DetectorCollection* src_entry = NULL;
			for (int i = 0; errp->code == 0 && i < cnt; i++)
			{
				src_entry = list[i];
				DetectorCollectionEntry* entry = NULL;
				if ((entry = DetectorCollectionEntry_fromDimz(src_entry, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(DetectorCollectionEntry_delAndSetNull, (void*)&entry);
					if ((*errp = ret->add(ret, entry)).code) ERR_OUT(errp);
					else
					{
						entry = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (DetectorCollectionEntry_delAndSetNull, (void*)&entry);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (DetectorCollectionList_delAndSetNull, (void*)&ret);
	}
	return ret;
}


static ExtentionCommPDUEntry* ExtentionCommPDUEntry_fromDimz(Dz1ExtentionCommPDU* src, Dz1Error* errp)
{
	ExtentionCommPDUEntry* ret = NULL;

	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = ExtentionCommPDUEntry_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ExtentionCommPDUEntry_delAndSetNull, (void*)&ret);

		if ((ret->payload = Dz1Binary_new(src->payload->data, src->payload->size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->idx = src->index;
			ret->aid = src->aid;
			ret->delivery_start = src->deliveryStart->tv_sec;
			ret->delivery_stop = src->deliveryStop->tv_sec;
			if (src->signature) ret->signature = *src->signature;
			if (src->payloadType) ret->payload_type = *src->payloadType;
		}

		pthread_cleanup_pop(1); // (ExtentionCommPDUEntry_delAndSetNull, (void*)&ret);
	}
	return ret;
}

ExtentionCommPDUList* ExtentionCommPDUList_fromDimz(Dz1ExtentionCommPDUResponse* src, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	ExtentionCommPDUList* ret = NULL;

	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = ExtentionCommPDUList_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1ExtentionCommPDU** list = NULL;
		int cnt = 0;
		pthread_cleanup_push(ExtentionCommPDUList_delAndSetNull, (void*)&ret);
		if ((list = src->get_array(src, &cnt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1ExtentionCommPDU* src_entry = NULL;
			for (int i = 0; errp->code == 0 && i < cnt; i++)
			{
				src_entry = list[i];
				ExtentionCommPDUEntry* entry = NULL;
				if ((entry = ExtentionCommPDUEntry_fromDimz(src_entry, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(ExtentionCommPDUEntry_delAndSetNull, (void*)&entry);
					if ((*errp = ret->add(ret, entry)).code) ERR_OUT(errp);
					else
					{
						entry = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (ExtentionCommPDUEntry_delAndSetNull, (void*)&entry);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (ExtentionCommPDUList_delAndSetNull, (void*)&ret);
	}
	return ret;
}



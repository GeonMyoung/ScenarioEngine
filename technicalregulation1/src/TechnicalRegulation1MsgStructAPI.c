#include <dz1_gasn_support.h>
#include "TechnicalRegulation1EamDz1.h"

#include "TechnicalRegulation1MsgStructAPI.h"




static void* CurrentLinkStateList_convert(void* db_list_ptr, Dz1Error* errp)
{
	CurrentLinkStateList* list = (CurrentLinkStateList*)db_list_ptr;
	CurrentLinkStateEntry* entry = NULL;

	Dz1CurrentLinkState* data = NULL;
	Dz1CurrentLinkStateResponse* p = NULL;
	if ((p = Dz1CurrentLinkStateResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CurrentLinkStateResponse_delAndSetNull, (void*)&p);
		while ((entry = list->getHead(list)) != NULL)
		{
			list->extract(list, entry);
			pthread_cleanup_push(CurrentLinkStateEntry_delAndSetNull, (void*)&entry);
			if ((data = Dz1CurrentLinkState_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1CurrentLinkState_delAndSetNull, (void*)&data);

				if (0) {}
				else if ((data->link_LinkIdNumber = Dz1Asn1UTF8Str_newFromStr(entry->link_id, errp)) == NULL) ERR_OUT(errp);
				else if ((data->link_VolumeRate = Dz1u32_clone(&(entry->volume_rate), errp)) == NULL) ERR_OUT(errp);
				else if ((data->link_DensityRate = Dz1u16_clone(&(entry->density_rate), errp)) == NULL) ERR_OUT(errp);
				else if ((data->link_TravelTimeQuantity = Dz1u16_clone(&(entry->ttime_qty), errp)) == NULL) ERR_OUT(errp);
				else if ((data->tfdt_VehicleQueueLengthQuantity = Dz1u32_clone(&(entry->veh_q_len_qty), errp)) == NULL) ERR_OUT(errp);
				else
				{
					data->link_SpeedRate = entry->speed_rate;
					data->tfdt_OccupancyPercent = entry->tfdt_occupy_percent;
					if ((*errp = p->add(p, data)).code) ERR_OUT(errp);
					else
					{
						data = NULL;
						Dz1Error_set(errp, 0);
					}
				}
				pthread_cleanup_pop(1); // (Dz1CurrentLinkState_delAndSetNull, (void *)&data);
			}
			pthread_cleanup_pop(1); // (CurrentLinkStateEntry_delAndSetNull, (void*)&entry);
		}
		pthread_cleanup_pop(errp->code); // (Dz1CurrentLinkStateResponse_delAndSetNull, (void *)&p);
	}
	return p;
}
static _encoder_declare_(Dz1CurrentLinkStateResponse, CurrentLinkStateResponse)
static _decoder_declare_(Dz1CurrentLinkStateResponse, CurrentLinkStateResponse)
static _get_eam_list_declare_(TechnicalRegulation1, CurrentLinkStateList, current_link_state, "TechnicalRegulation1_Eam", TECHNICAL_REGULATION1_EAM_PATH_101)


static void* EventIdentityList_convert(void* db_list_ptr, Dz1Error* errp)
{
	EventIdentityList* list = (EventIdentityList*)db_list_ptr;
	EventIdentityEntry* entry = NULL;

	Dz1EventIdentity* data = NULL;
	Dz1EventIdentityResponse* p = NULL;
	if ((p = Dz1EventIdentityResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1EventIdentityResponse_delAndSetNull, (void*)&p);
		while ((entry = list->getHead(list)) != NULL)
		{
			list->extract(list, entry);
			pthread_cleanup_push(EventIdentityEntry_delAndSetNull, (void*)&entry);
			if ((data = Dz1EventIdentity_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode evnt_code = (Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode)entry->evnt_code;
				Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode special_evnt_code = (Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode)entry->special_evnt_code;
				Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode planned_road_closure_code = (Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode)entry->planned_road_closure_code;

				pthread_cleanup_push(Dz1EventIdentity_delAndSetNull, (void*)&data);

				if (0) {}
				else if ((data->node_NodeIdNumber = Dz1Asn1UTF8Str_newFromStr(entry->node_id, errp)) == NULL) ERR_OUT(errp);
				else if ((data->link_LinkIdNumber = Dz1Asn1UTF8Str_newFromStr(entry->link_id, errp)) == NULL) ERR_OUT(errp);
				else if ((data->evnt_LocationJurisDictionNameText = Dz1Asn1UTF8Str_newFromStr(entry->loc_jurisdiction_name, errp)) == NULL) ERR_OUT(errp);
				else if ((data->evnt_LocationLinkIdNumber = Dz1Asn1UTF8Str_newFromStr(entry->loc_link_id, errp)) == NULL) ERR_OUT(errp);
				else if ((data->evnt_LocationNodeIdNumber = Dz1Asn1UTF8Str_newFromStr(entry->loc_node_id, errp)) == NULL) ERR_OUT(errp);
				else if ((data->evnt_LocationRoadwayNameText = Dz1Asn1UTF8Str_newFromStr(entry->loc_roadway_name, errp)) == NULL) ERR_OUT(errp);
				//				else if (!(data->evnt_LanesBlockedOrClosedNumber = *Dz1u8_clone(&(entry->lanes_blocked_or_closed_num), errp))) ERR_OUT(errp);
				else if ((data->evnt_LanesShouldersBlockedCode = Dz1Asn1BitStr_new(entry->lanes_shoulder_block_code, 1, errp)) == NULL) ERR_OUT(errp);
				else if ((data->evnt_TimelineStartGeneralizedTime = Dz1Asn1VisibleStr_newFromStr(entry->start_time, errp)) == NULL) ERR_OUT(errp);
				else if ((data->evnt_TimelineEndGeneralizedTime = Dz1Asn1VisibleStr_newFromStr(entry->end_time, errp)) == NULL) ERR_OUT(errp);
				//				else if (!(data->evnt_TimelineDurationTime = *Dz1u32_clone(&(entry->time_duration), errp))) ERR_OUT(errp);

				else if ((data->evnt_IdentificationNumber = Dz1u32_clone(&entry->identification_num, errp)) == NULL) ERR_OUT(errp);
				else if ((data->evnt_DescriptionTypeEventCode = Dz1EventIdentity_evnt_DescriptionTypeEventCode_new(&evnt_code, errp)) == NULL) ERR_OUT(errp);
				else if ((data->evnt_DescriptionTypeSpecialEventCode = Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_new(&special_evnt_code, errp)) == NULL) ERR_OUT(errp);
				else if ((data->evnt_DescriptionPlannedRoadWayClosureCode = Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_new(&planned_road_closure_code, errp)) == NULL) ERR_OUT(errp);

				else

				{
					data->evnt_LanesBlockedOrClosedNumber = entry->lanes_blocked_or_closed_num;
					data->evnt_TimelineDurationTime = entry->time_duration;

					// 					data->evnt_IdentificationNumber = (u32_t*)(&(entry->identification_num));
					// 					data->evnt_DescriptionTypeEventCode = (Dz1EventIdentity_evnt_DescriptionTypeEventCode*)&(entry->evnt_code);
					// 					data->evnt_DescriptionTypeSpecialEventCode = (Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode*)&(entry->special_evnt_code);
					// 					data->evnt_DescriptionPlannedRoadWayClosureCode = (Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode*)&(entry->planned_road_closure_code);

					if ((*errp = p->add(p, data)).code) ERR_OUT(errp);
					else
					{
						data = NULL;
						Dz1Error_set(errp, 0);
					}
				}
				pthread_cleanup_pop(1); // (Dz1EventIdentity_delAndSetNull, (void *)&data);
			}
			pthread_cleanup_pop(1); // (EventIdentityEntry_delAndSetNull, (void*)&entry);
		}
		pthread_cleanup_pop(errp->code); // (Dz1EventIdentityResponse_delAndSetNull, (void *)&p);
	}
	return p;
}
static _encoder_declare_(Dz1EventIdentityResponse, EventIdentityResponse)
static _decoder_declare_(Dz1EventIdentityResponse, EventIdentityResponse)
static _get_eam_list_declare_(TechnicalRegulation1, EventIdentityList, event_identity, "TechnicalRegulation1_Eam", TECHNICAL_REGULATION1_EAM_PATH_102)

static void* IncidentIdentityList_convert(void* db_list_ptr, Dz1Error* errp)
{
	IncidentIdentityList* list = (IncidentIdentityList*)db_list_ptr;
	IncidentIdentityEntry* entry = NULL;

	Dz1IncidentIdentity* data = NULL;
	Dz1IncidentIdentityResponse* p = NULL;
	if ((p = Dz1IncidentIdentityResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1IncidentIdentityResponse_delAndSetNull, (void*)&p);
		while ((entry = list->getHead(list)) != NULL)
		{
			list->extract(list, entry);
			pthread_cleanup_push(IncidentIdentityEntry_delAndSetNull, (void*)&entry);
			if ((data = Dz1IncidentIdentity_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1IncidentIdentity_delAndSetNull, (void*)&data);

				if (0) {}
				else if ((data->node_NodeIdNumber = Dz1Asn1UTF8Str_newFromStr(entry->node_id, errp)) == NULL) ERR_OUT(errp);
				else if ((data->link_LinkIdNumber = Dz1Asn1UTF8Str_newFromStr(entry->link_id, errp)) == NULL) ERR_OUT(errp);
				else if ((data->evnt_LocationLinearDistanceOffsetBeginNumber = Dz1u16_clone(&(entry->loc_offset_begin), errp)) == NULL) ERR_OUT(errp);
				else if ((data->evnt_LinearDistanceoffsetEndNumber = Dz1u16_clone(&(entry->loc_offset_end), errp)) == NULL) ERR_OUT(errp);
				else if ((data->evnt_UpdateGeneralizedTime = Dz1Asn1VisibleStr_newFromStr(entry->update_time, errp)) == NULL) ERR_OUT(errp);
				else if ((data->evnt_IncidentHumanFatalitiesCountQuantity = Dz1u8_clone(&(entry->fatality_cnt), errp)) == NULL) ERR_OUT(errp);
				else if ((data->evnt_IncidentHumanInjuriesCountQuantity = Dz1u8_clone(&(entry->injuries_cnt), errp)) == NULL) ERR_OUT(errp);
				else if ((data->evnt_IncidentPropertyDamageCode = Dz1Asn1BitStr_new(&(entry->property_damage_code), 7, errp)) == NULL) ERR_OUT(errp);
				else if (Dz1Str_isVoid(entry->property_damage_desc) == FALSE && (data->evnt_IncidentPropertyDamageOther = Dz1Asn1UTF8Str_newFromStr(entry->property_damage_desc, errp)) == NULL) ERR_OUT(errp);	// Fixed
				else
				{
					if ((*errp = p->add(p, data)).code) ERR_OUT(errp);
					else
					{
						data = NULL;
						Dz1Error_set(errp, 0);
					}
				}
				pthread_cleanup_pop(1); // (Dz1IncidentIdentity_delAndSetNull, (void *)&data);
			}
			pthread_cleanup_pop(1); // (IncidentIdentityEntry_delAndSetNull, (void*)&entry);
		}
		pthread_cleanup_pop(errp->code); // (Dz1IncidentIdentityResponse_delAndSetNull, (void *)&p);
	}
	return p;
}
static _encoder_declare_(Dz1IncidentIdentityResponse, IncidentIdentityResponse)
static _decoder_declare_(Dz1IncidentIdentityResponse, IncidentIdentityResponse)
static _get_eam_list_declare_(TechnicalRegulation1, IncidentIdentityList, incident_identity, "TechnicalRegulation1_Eam", TECHNICAL_REGULATION1_EAM_PATH_103)

static void* IncidentConditionsList_convert(void* db_list_ptr, Dz1Error* errp)
{
	IncidentConditionsList* list = (IncidentConditionsList*)db_list_ptr;
	IncidentConditionsEntry* entry = NULL;

	Dz1IncidentConditions* data = NULL;
	Dz1IncidentConditionsResponse* p = NULL;
	if ((p = Dz1IncidentConditionsResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1IncidentConditionsResponse_delAndSetNull, (void*)&p);
		while ((entry = list->getHead(list)) != NULL)
		{
			list->extract(list, entry);
			pthread_cleanup_push(IncidentConditionsEntry_delAndSetNull, (void*)&entry);
			if ((data = Dz1IncidentConditions_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1IncidentConditions_delAndSetNull, (void*)&data);

				if (0) {}
				else if ((data->node_NodeIdNumber = Dz1Asn1UTF8Str_newFromStr(entry->node_id, errp)) == NULL) ERR_OUT(errp);
				else if ((data->link_LinkIdNumber = Dz1Asn1UTF8Str_newFromStr(entry->link_id, errp)) == NULL) ERR_OUT(errp);
				else if ((data->orgn_ContatOrganizationNameText = Dz1Asn1UTF8Str_newFromStr(entry->contact_org_name, errp)) == NULL) ERR_OUT(errp);
				else if (Dz1Str_isVoid(entry->other_incident_desc) == FALSE && (data->evnt_DescriptionTypeIncidentOther = Dz1Asn1UTF8Str_newFromStr(entry->other_incident_desc, errp)) == NULL) ERR_OUT(errp);			// Fixed
				else if ((data->evnt_IncidentVehiclesInvolvedCode = Dz1Asn1BitStr_new(&(entry->veh_invloved_code), 7, errp)) == NULL) ERR_OUT(errp);
				else if (Dz1Str_isVoid(entry->other_veh_invloved_desc) == FALSE && (data->evnt_IncidentVehiclesInvolvedOther = Dz1Asn1UTF8Str_newFromStr(entry->other_veh_invloved_desc, errp)) == NULL) ERR_OUT(errp);	// Fixed
				else if (Dz1Str_isVoid(entry->other_status_desc) == FALSE && (data->evnt_IncidentStatusOther = Dz1Asn1UTF8Str_newFromStr(entry->other_status_desc, errp)) == NULL) ERR_OUT(errp);						// Fixed
				else if (Dz1Str_isVoid(entry->other_update_desc) == FALSE && (data->evnt_UpdateTypeOther = Dz1Asn1UTF8Str_newFromStr(entry->other_update_desc, errp)) == NULL) ERR_OUT(errp);							// Fixed
				else
				{
					data->evnt_DescriptionTypeIncidentCode = (Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode)(entry->incident_code);
					data->evnt_IncidentStatusCode = (Dz1IncidentConditions_evnt_IncidentStatusCode)(entry->status_code);
					data->evnt_UpdateTypeCode = (Dz1IncidentConditions_evnt_UpdateTypeCode)(entry->update_type_code);
					if ((*errp = p->add(p, data)).code) ERR_OUT(errp);
					else
					{
						data = NULL;
						Dz1Error_set(errp, 0);
					}
				}
				pthread_cleanup_pop(1); // (Dz1IncidentConditions_delAndSetNull, (void *)&data);
			}
			pthread_cleanup_pop(1); // (IncidentConditionsEntry_delAndSetNull, (void*)&entry);
		}
		pthread_cleanup_pop(errp->code); // (Dz1IncidentConditionsResponse_delAndSetNull, (void *)&p);
	}
	return p;
}
static _encoder_declare_(Dz1IncidentConditionsResponse, IncidentConditionsResponse)
static _decoder_declare_(Dz1IncidentConditionsResponse, IncidentConditionsResponse)
static _get_eam_list_declare_(TechnicalRegulation1, IncidentConditionsList, incident_conditions, "TechnicalRegulation1_Eam", TECHNICAL_REGULATION1_EAM_PATH_104)

static void* RoadwaySurfaceStatusList_convert(void* db_list_ptr, Dz1Error* errp)
{
	RoadwaySurfaceStatusList* list = (RoadwaySurfaceStatusList*)db_list_ptr;
	RoadwaySurfaceStatusEntry* entry = NULL;

	Dz1RoadwaySurfaceStatus* data = NULL;
	Dz1RoadwaySurfaceStatusResponse* p = NULL;
	if ((p = Dz1RoadwaySurfaceStatusResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1RoadwaySurfaceStatusResponse_delAndSetNull, (void*)&p);
		while ((entry = list->getHead(list)) != NULL)
		{
			list->extract(list, entry);
			pthread_cleanup_push(RoadwaySurfaceStatusEntry_delAndSetNull, (void*)&entry);
			if ((data = Dz1RoadwaySurfaceStatus_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1RoadwaySurfaceStatus_delAndSetNull, (void*)&data);
				if (0) {}
				else if ((data->node_NodeIdNumber = Dz1Asn1UTF8Str_newFromStr(entry->node_id, errp)) == NULL) ERR_OUT(errp);
				else if ((data->link_LinkIdNumber = Dz1Asn1UTF8Str_newFromStr(entry->link_id, errp)) == NULL) ERR_OUT(errp);
				else if ((data->link_SurfaceConditionCode = Dz1Asn1BitStr_new(&(entry->surface_cond_code), 14, errp)) == NULL) ERR_OUT(errp);
				else if ((data->link_LandBlockedOrClosedCode = Dz1Asn1BitStr_new(&(entry->land_blocked_or_closed_code), 5, errp)) == NULL) ERR_OUT(errp);
				else if ((data->evsn_DataSurfacePrecipitationDepth = Dz1u16_clone(&(entry->precipitation_depth), errp)) == NULL) ERR_OUT(errp);
				else if ((data->evsn_DataSurfaceTemperatureQuantity = Dz1u16_clone(&(entry->temperature_qty), errp)) == NULL) ERR_OUT(errp);
				else
				{
					if ((*errp = p->add(p, data)).code) ERR_OUT(errp);
					else
					{
						data = NULL;
						Dz1Error_set(errp, 0);
					}
				}
				pthread_cleanup_pop(1); // (Dz1RoadwaySurfaceStatus_delAndSetNull, (void *)&data);
			}
			pthread_cleanup_pop(1); // (RoadwaySurfaceStatusEntry_delAndSetNull, (void*)&entry);
		}
		pthread_cleanup_pop(errp->code); // (Dz1RoadwaySurfaceStatusResponse_delAndSetNull, (void *)&p);
	}
	return p;
}
static _encoder_declare_(Dz1RoadwaySurfaceStatusResponse, RoadwaySurfaceStatusResponse)
static _decoder_declare_(Dz1RoadwaySurfaceStatusResponse, RoadwaySurfaceStatusResponse)
static _get_eam_list_declare_(TechnicalRegulation1, RoadwaySurfaceStatusList, roadway_surface_status, "TechnicalRegulation1_Eam", TECHNICAL_REGULATION1_EAM_PATH_105)

static void* WeatherInformationList_convert(void* db_list_ptr, Dz1Error* errp)
{
	WeatherInformationList* list = (WeatherInformationList*)db_list_ptr;
	WeatherInformationEntry* entry = NULL;

	Dz1WeatherInformation* data = NULL;
	Dz1WeatherInformationResponse* p = NULL;
	if ((p = Dz1WeatherInformationResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1WeatherInformationResponse_delAndSetNull, (void*)&p);
		while ((entry = list->getHead(list)) != NULL)
		{
			list->extract(list, entry);
			pthread_cleanup_push(WeatherInformationEntry_delAndSetNull, (void*)&entry);
			if ((data = Dz1WeatherInformation_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1WeatherInformation_delAndSetNull, (void*)&data);
				Dz1WeatherInformation_wthr_WindDirectionCode wthr_WindDirectionCode = (Dz1WeatherInformation_wthr_WindDirectionCode)entry->wind_direct_code;
				if (0) {}
				else if ((data->wthr_TemperatureQuantity = Dz1s8_clone(&(entry->temperature), errp)) == NULL) ERR_OUT(errp);
				else if ((data->wthr_HighTemperatureQuantity = Dz1s8_clone(&(entry->high_temperature), errp)) == NULL) ERR_OUT(errp);
				else if ((data->wthr_LowTemperatureQuantity = Dz1s8_clone(&(entry->low_temperature), errp)) == NULL) ERR_OUT(errp);
				else if ((data->wthr_SpecialConditions = Dz1Asn1BitStr_new(&(entry->special_cond), 13, errp)) == NULL) ERR_OUT(errp);
				else if (Dz1Str_isVoid(entry->other_cond_desc) == FALSE && (data->wthr_SpecialConditionsOther = Dz1Asn1UTF8Str_newFromStr(entry->other_cond_desc, errp)) == NULL) ERR_OUT(errp);	// Fixed : Jake LIM
				else if ((data->wthr_VisibilityQuantity = Dz1u8_clone(&(entry->visibility), errp)) == NULL) ERR_OUT(errp);
				else if ((data->wthr_WindSpeedQuantity = Dz1u8_clone(&(entry->wind_speed), errp)) == NULL) ERR_OUT(errp);
				else if ((data->wthr_WindDirectionCode = Dz1WeatherInformation_wthr_WindDirectionCode_new(&wthr_WindDirectionCode, errp)) == NULL) ERR_OUT(errp);
				else if ((data->wthr_HumidityQuantity = Dz1u8_clone(&(entry->humidity), errp)) == NULL) ERR_OUT(errp);
				else if ((data->wthr_PressureQuantity = Dz1u8_clone(&(entry->humidity), errp)) == NULL) ERR_OUT(errp);
				else if (Dz1Str_isVoid(entry->sunrise_time) == FALSE && (data->wthr_SunriseTimeGeneralizedTime = Dz1Asn1VisibleStr_newFromStr(entry->sunrise_time, errp)) == NULL) ERR_OUT(errp);	// Fixed
				else if (Dz1Str_isVoid(entry->sunset_time) == FALSE && (data->wthr_SunsetTimeGeneralizedTime = Dz1Asn1VisibleStr_newFromStr(entry->sunset_time, errp)) == NULL) ERR_OUT(errp);		// Fixed
				else
				{
					data->wthr_ForecastOrActualCode = (Dz1WeatherInformation_wthr_ForecastOrActualCode)(entry->forecast_or_actual);
					data->wthr_ProbabilityPercent = entry->probability;
					if ((*errp = p->add(p, data)).code) ERR_OUT(errp);
					else
					{
						data = NULL;
						Dz1Error_set(errp, 0);
					}
				}
				pthread_cleanup_pop(1); // (Dz1WeatherInformation_delAndSetNull, (void *)&data);
			}
			pthread_cleanup_pop(1); // (WeatherInformationEntry_delAndSetNull, (void*)&entry);
		}
		pthread_cleanup_pop(errp->code); // (Dz1WeatherInformationResponse_delAndSetNull, (void *)&p);
	}
	return p;
}
static _encoder_declare_(Dz1WeatherInformationResponse, WeatherInformationResponse)
static _decoder_declare_(Dz1WeatherInformationResponse, WeatherInformationResponse)
static _get_eam_list_declare_(TechnicalRegulation1, WeatherInformationList, weather_information, "TechnicalRegulation1_Eam", TECHNICAL_REGULATION1_EAM_PATH_106)

static void* LinkRoadwayGeometryList_convert(void* db_list_ptr, Dz1Error* errp)
{
	LinkRoadwayGeometryList* list = (LinkRoadwayGeometryList*)db_list_ptr;
	LinkRoadwayGeometryEntry* entry = NULL;

	Dz1LinkRoadwayGeometry* data = NULL;
	Dz1LinkRoadwayGeometryResponse* p = NULL;
	if ((p = Dz1LinkRoadwayGeometryResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1LinkRoadwayGeometryResponse_delAndSetNull, (void*)&p);
		while ((entry = list->getHead(list)) != NULL)
		{
			list->extract(list, entry);
			pthread_cleanup_push(LinkRoadwayGeometryEntry_delAndSetNull, (void*)&entry);
			if ((data = Dz1LinkRoadwayGeometry_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1LinkRoadwayGeometry_delAndSetNull, (void*)&data);
				Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode tfmg_LinkMedianTypeCode = (Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode)(entry->median_type_code);

				if (0) {}
				else if ((data->link_BeginNodeIdNumber = Dz1Asn1UTF8Str_newFromStr(entry->begin_node_id, errp)) == NULL) ERR_OUT(errp);
				else if ((data->link_BiginNodeLatitudeLocation = Dz1s64_clone(&(entry->begin_node_latitude), errp)) == NULL) ERR_OUT(errp);
				else if ((data->link_BeginNodeLongitudeLocation = Dz1u32_clone(&(entry->begin_node_longitude), errp)) == NULL) ERR_OUT(errp);
				else if ((data->link_EndNodeIdNumber = Dz1Asn1UTF8Str_newFromStr(entry->end_node_id, errp)) == NULL) ERR_OUT(errp);
				else if ((data->link_EndNodeLatitudeLocation = Dz1s64_clone(&(entry->end_node_latitude), errp)) == NULL) ERR_OUT(errp);
				else if ((data->link_EndNodeLongitudeLocation = Dz1u32_clone(&(entry->end_node_longitude), errp)) == NULL) ERR_OUT(errp);
				else if ((data->link_JurisdictionText = Dz1Asn1UTF8Str_newFromStr(entry->jurisdiction, errp)) == NULL) ERR_OUT(errp);
				else if ((data->link_TypeCode = Dz1Asn1BitStr_new(&(entry->type_code), 10, errp)) == NULL) ERR_OUT(errp);
				else if ((data->link_NameText = Dz1Asn1UTF8Str_newFromStr(entry->name, errp)) == NULL) ERR_OUT(errp);
				else if ((data->link_PavementTypeCode = Dz1Asn1BitStr_new(&(entry->pavement_type_code), 9, errp)) == NULL) ERR_OUT(errp);
				else if ((data->tfmg_LinkHeigthRestrictionQunatity = Dz1u16_clone(&(entry->restriction_height), errp)) == NULL) ERR_OUT(errp);
				else if ((data->tfmg_LinkLeftShoulderWidthQuantity = Dz1u16_clone(&(entry->left_shoulder_width), errp)) == NULL) ERR_OUT(errp);
				else if ((data->tfmg_LinkLengthRestrictionQuatity = Dz1u16_clone(&(entry->restriction_length), errp)) == NULL) ERR_OUT(errp);
				else if ((data->tfmg_LinkRightShoulderWidthQuantity = Dz1u16_clone(&(entry->right_shoulder_width), errp)) == NULL) ERR_OUT(errp);
				else
				{
					data->link_LengthQuantity = entry->length;
					data->tfmg_LinkMedianTypeCode = (Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode)(entry->median_type_code);
					data->tfmg_LinkNumLanesNumber = entry->num_lanes;
					data->tfmg_LinkNumLanesOpenNumber = entry->num_open_lanes;
					if ((*errp = p->add(p, data)).code) ERR_OUT(errp);
					else
					{
						data = NULL;
						Dz1Error_set(errp, 0);
					}
				}
				pthread_cleanup_pop(1); // (Dz1LinkRoadwayGeometry_delAndSetNull, (void *)&data);
			}
			pthread_cleanup_pop(1); // (LinkRoadwayGeometryEntry_delAndSetNull, (void*)&entry);
		}
		pthread_cleanup_pop(errp->code); // (Dz1LinkRoadwayGeometryResponse_delAndSetNull, (void *)&p);
	}
	return p;
}
static _encoder_declare_(Dz1LinkRoadwayGeometryResponse, LinkRoadwayGeometryResponse)
static _decoder_declare_(Dz1LinkRoadwayGeometryResponse, LinkRoadwayGeometryResponse)
static _get_eam_list_declare_(TechnicalRegulation1, LinkRoadwayGeometryList, link_roadway_geometry, "TechnicalRegulation1_Eam", TECHNICAL_REGULATION1_EAM_PATH_107)

static void* ProbeVehicleDetectionList_convert(void* db_list_ptr, Dz1Error* errp)
{
	ProbeVehicleDetectionList* list = (ProbeVehicleDetectionList*)db_list_ptr;
	ProbeVehicleDetectionEntry* entry = NULL;

	Dz1ProbeVehicleDetection* data = NULL;
	Dz1ProbeVehicleDetectionResponse* p = NULL;
	if ((p = Dz1ProbeVehicleDetectionResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ProbeVehicleDetectionResponse_delAndSetNull, (void*)&p);
		while ((entry = list->getHead(list)) != NULL)
		{
			list->extract(list, entry);
			pthread_cleanup_push(ProbeVehicleDetectionEntry_delAndSetNull, (void*)&entry);
			if ((data = Dz1ProbeVehicleDetection_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1ProbeVehicleDetection_delAndSetNull, (void*)&data);

				if (0) {}
				else if ((data->vpbd_VehicleIdNumber = Dz1Asn1UTF8Str_newFromStr(entry->veh_id, errp)) == NULL) ERR_OUT(errp);
				else if ((data->vpbd_VehicleTimeInGeneralizedTime = Dz1Asn1VisibleStr_newFromStr(entry->veh_timein, errp)) == NULL) ERR_OUT(errp);
				else if ((data->vpbd_VehicleTimeOutGeneralizedTime = Dz1Asn1VisibleStr_newFromStr(entry->veh_timeout, errp)) == NULL) ERR_OUT(errp);
				else if ((data->vpbd_VehicleAverageSpeedRate = Dz1u16_clone(&(entry->veh_avg_speed), errp)) == NULL) ERR_OUT(errp);
				else if (Dz1Str_isVoid(entry->ref_avi_id) == FALSE && (data->vpbd_AviReaderIdNumber = Dz1Asn1UTF8Str_newFromStr(entry->avi_id, errp)) == NULL) ERR_OUT(errp); // Fixed : Jake Lim
				else if ((data->vpbd_AviReaderLocationLatitude = Dz1s64_clone(&(entry->avi_latitude), errp)) == NULL) ERR_OUT(errp);
				else if ((data->vpbd_AviReaderLocationLongitude = Dz1u32_clone(&(entry->avi_longitude), errp)) == NULL) ERR_OUT(errp);
				else if (Dz1Str_isVoid(entry->ref_avi_id) == FALSE && (data->vpbd_ReferenceLocatorIdNumber = Dz1Asn1UTF8Str_newFromStr(entry->ref_avi_id, errp)) == NULL) ERR_OUT(errp);
				else if ((data->vpbd_ReferenceLocatorLatitude = Dz1s64_clone(&(entry->ref_avi_latitude), errp)) == NULL) ERR_OUT(errp);
				else if ((data->vpbd_ReferenceLocatorLongitude = Dz1u32_clone(&(entry->ref_avi_longitude), errp)) == NULL) ERR_OUT(errp);
				else
				{
					data->vpbd_VehicleClass = (Dz1ProbeVehicleDetection_vpbd_VehicleClass)entry->veh_class;
					data->vpbd_VehicleTravelTimeTime = entry->veh_traveltime;

					if ((*errp = p->add(p, data)).code) ERR_OUT(errp);
					else
					{
						data = NULL;
						Dz1Error_set(errp, 0);
					}
				}
				pthread_cleanup_pop(1); // (Dz1ProbeVehicleDetection_delAndSetNull, (void *)&data);
			}
			pthread_cleanup_pop(1); // (ProbeVehicleDetectionEntry_delAndSetNull, (void*)&entry);
		}
		pthread_cleanup_pop(errp->code); // (Dz1ProbeVehicleDetectionResponse_delAndSetNull, (void *)&p);
	}
	return p;
}
static _encoder_declare_(Dz1ProbeVehicleDetectionResponse, ProbeVehicleDetectionResponse)
static _decoder_declare_(Dz1ProbeVehicleDetectionResponse, ProbeVehicleDetectionResponse)
static _get_eam_list_declare_(TechnicalRegulation1, ProbeVehicleDetectionList, probe_vehicle_detection, "TechnicalRegulation1_Eam", TECHNICAL_REGULATION1_EAM_PATH_108)

static void* DetectorCollectionList_convert(void* db_list_ptr, Dz1Error* errp)
{
	DetectorCollectionList* list = (DetectorCollectionList*)db_list_ptr;
	DetectorCollectionEntry* entry = NULL;

	Dz1DetectorCollection* data = NULL;
	Dz1DetectorCollectionResponse* p = NULL;
	if ((p = Dz1DetectorCollectionResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1DetectorCollectionResponse_delAndSetNull, (void*)&p);
		while ((entry = list->getHead(list)) != NULL)
		{
			list->extract(list, entry);
			pthread_cleanup_push(DetectorCollectionEntry_delAndSetNull, (void*)&entry);
			if ((data = Dz1DetectorCollection_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1DetectorCollection_delAndSetNull, (void*)&data);

				if (0) {}
				else if ((data->tfdt_DetectorIdNumber = Dz1Asn1UTF8Str_newFromStr(entry->detector_id, errp)) == NULL) ERR_OUT(errp);
				else if ((data->tfdt_DetectorTimeGeneralizedTime = Dz1Asn1VisibleStr_newFromStr(entry->detector_time, errp)) == NULL) ERR_OUT(errp);
				else if ((data->tfdt_VolumeRate = Dz1u8_clone(&(entry->volume_rate), errp)) == NULL) ERR_OUT(errp);
				else if ((data->tfdt_VehicleQueueLengthQuantity = Dz1u32_clone(&(entry->veh_q_len_qty), errp)) == NULL) ERR_OUT(errp);
				else
				{
					data->tfdt_SpeedRate = entry->speed_rate;
					data->tfdt_OccupancyPercent = entry->occupancy_percent;
					if ((*errp = p->add(p, data)).code) ERR_OUT(errp);
					else
					{
						data = NULL;
						Dz1Error_set(errp, 0);
					}
				}
				pthread_cleanup_pop(1); // (Dz1DetectorCollection_delAndSetNull, (void *)&data);
			}
			pthread_cleanup_pop(1); // (DetectorCollectionEntry_delAndSetNull, (void*)&entry);
		}
		pthread_cleanup_pop(errp->code); // (Dz1DetectorCollectionResponse_delAndSetNull, (void *)&p);
	}
	return p;
}
static _encoder_declare_(Dz1DetectorCollectionResponse, DetectorCollectionResponse)
static _decoder_declare_(Dz1DetectorCollectionResponse, DetectorCollectionResponse)
static _get_eam_list_declare_(TechnicalRegulation1, DetectorCollectionList, detector_collection, "TechnicalRegulation1_Eam", TECHNICAL_REGULATION1_EAM_PATH_109)


static void* ExtentionCommPDUList_convert(void* db_list_ptr, Dz1Error* errp)
{
	ExtentionCommPDUList* list = (ExtentionCommPDUList*)db_list_ptr;
	ExtentionCommPDUEntry* entry = NULL;

	Dz1ExtentionCommPDU* data = NULL;
	Dz1ExtentionCommPDUResponse* p = NULL;
	if ((p = Dz1ExtentionCommPDUResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ExtentionCommPDUResponse_delAndSetNull, (void*)&p);
		while (errp->code == 0 && (entry = list->getHead(list)) != NULL)
		{
			list->extract(list, entry);
			//pthread_cleanup_push(ExtentionCommPDUEntry_delAndSetNull, (void*)&entry);
			if ((data = Dz1ExtentionCommPDU_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1ExtentionCommPDU_delAndSetNull, (void*)&data);

				if (0) {}
				else if ((data->deliveryStart = Dz1TimeVal_newFromTime(&entry->delivery_start, errp)) == NULL) ERR_OUT(errp);	// fixed : Jake Lim
				else if ((data->deliveryStop = Dz1TimeVal_newFromTime(&entry->delivery_stop, errp)) == NULL) ERR_OUT(errp);		// fixed : Jake Lim
				else if ((data->signature = Dz1Bool_clone(&(entry->signature), errp)) == NULL) ERR_OUT(errp);
				else if ((data->payloadType = Dz1s64_clone(&(entry->payload_type), errp)) == NULL) ERR_OUT(errp);
				// else if (entry->payload != NULL && (data->payload = Dz1Asn1UTF8Str_newFromBuf(entry->payload->data, entry->payload->size, DZ1_SYSTEM_MBCS_CHARSET, errp)) == NULL) ERR_OUT(errp); // fixed : Jake Lim //확인 필요
				else if (entry->payload != NULL && (data->payload = Dz1Asn1UTF8Str_new(entry->payload->data, entry->payload->size, errp)) == NULL) ERR_OUT(errp);
				else
				{
					data->index = entry->idx;
					data->aid = entry->aid;
					if ((*errp = p->add(p, data)).code) ERR_OUT(errp);
					else
					{
						data = NULL;
						Dz1Error_set(errp, 0);
					}
				}
				pthread_cleanup_pop(1); // (Dz1ExtentionCommPDU_delAndSetNull, (void *)&data);
			}
			//pthread_cleanup_pop(1); // (ExtentionCommPDUEntry_delAndSetNull, (void*)&entry);
		}
		pthread_cleanup_pop(errp->code); // (Dz1ExtentionCommPDUResponse_delAndSetNull, (void *)&p);
	}
	return p;
}
static _encoder_declare_(Dz1ExtentionCommPDUResponse, ExtentionCommPDUResponse)
static _decoder_declare_(Dz1ExtentionCommPDUResponse, ExtentionCommPDUResponse)
static _get_eam_list_declare_(TechnicalRegulation1, ExtentionCommPDUList, extention_comm_pdu, "TechnicalRegulation1_Eam", TECHNICAL_REGULATION1_EAM_PATH_110)


static CurrentLinkStateEntry currentlinkstate_arr[] =
{
	{ Dz1T("1"),	1, 1, 1, 1, 1, 1, 1 },
	{ Dz1T("2"),	2, 2, 2, 2, 2, 2, 2 },
	{ Dz1T("3"),	3, 3, 3, 3, 3, 3, 3 },
	{ NULL,			0, 0, 0, 0, 0, 0, 0 }
};

static bool_t CurrentLinkStateList_init_sample_data(CurrentLinkStateList* p, Dz1Error* err) {
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		CurrentLinkStateEntry* i = NULL, * node;
		for (i = currentlinkstate_arr; errp->code == 0 && i->link_id != NULL; i++)
		{
			if ((node = CurrentLinkStateEntry_clone(i, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(CurrentLinkStateEntry_delAndSetNull, (void*)&node);
				if ((*errp = p->add(p, node)).code) ERR_OUT(errp);
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (CurrentLinkStateEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ERR_IS_SUCCESS(errp); 
}

static u8_t sample_block_code = 0b00001010;
static EventIdentityEntry eventidentity_arr[] =
{
	{Dz1T("1"),Dz1T("1"), 1, Dz1T("1"), Dz1T("1"), Dz1T("1"), Dz1T("1"), 1, 1, 1, 1, &sample_block_code, Dz1T("1"), Dz1T("1"), 1},
	{Dz1T("2"),Dz1T("2"), 2, Dz1T("2"), Dz1T("2"), Dz1T("2"), Dz1T("2"), 2, 2, 2, 2, &sample_block_code, Dz1T("2"), Dz1T("2"), 2},
	{Dz1T("3"),Dz1T("3"), 3, Dz1T("3"), Dz1T("3"), Dz1T("3"), Dz1T("3"), 3, 3, 3, 3, &sample_block_code, Dz1T("3"), Dz1T("3"), 3},
	{NULL, NULL, 0, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 0, NULL, NULL, 0}
};
static bool_t EventIdentityList_init_sample_data(EventIdentityList* p, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp,EINVAL);
	else
	{
		EventIdentityEntry* i = NULL, * node;
		pthread_cleanup_push(EventIdentityList_delAndSetNull, (void*)&p);
		for (i = eventidentity_arr; errp->code == 0 && i->link_id != NULL; i++)
		{
			if ((node = EventIdentityEntry_clone(i, errp)) == NULL) ERR_OUT(errp);
			else
			{

				pthread_cleanup_push(EventIdentityEntry_delAndSetNull, (void*)&node);

				/*node->lanes_shoulder_block_code = Dz1Calloc(1, 1, errp);
				memcpy(node->lanes_shoulder_block_code, (void *)sample_block_code, 1);*/

				if ((*errp = p->add(p, node)).code) ERR_OUT(errp);
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (EventIdentityEntry_delAndSetNull, (void *)&node);
			}
		}
		pthread_cleanup_pop(errp->code); // (EventIdentityList_delAndSetNull, (void *)&p);
	}
	return ERR_IS_SUCCESS(errp);
}
static IncidentIdentityEntry incidentidentity_arr[] =
{
	{ Dz1T("1"), Dz1T("1"), 1, 1, Dz1T("1"), 1, 1, 1, Dz1T("1") },
	{ Dz1T("2"), Dz1T("2"), 2, 2, Dz1T("2"), 2, 2, 2, Dz1T("2") },
	{ Dz1T("3"), Dz1T("3"), 3, 3, Dz1T("3"), 3, 3, 3, Dz1T("3") },
	{ NULL,		 NULL,		0, 0, NULL,		 0, 0, 0, NULL}
};
static bool_t IncidentIdentityList_init_sample_data(IncidentIdentityList* p, Dz1Error* err)
{ 
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		IncidentIdentityEntry* i = NULL, * node;
		for (i = incidentidentity_arr; errp->code == 0 && i->link_id != NULL; i++)
		{
			if ((node = IncidentIdentityEntry_clone(i, errp)) == NULL) ERR_OUT(errp);
			else
			{

				pthread_cleanup_push(IncidentIdentityEntry_delAndSetNull, (void*)&node);

				if ((*errp = p->add(p, node)).code) ERR_OUT(errp);
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (IncidentIdentityEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static IncidentConditionsEntry incidentconditions_arr[] =
{
	{ Dz1T("1"), Dz1T("1"), Dz1T("1"), 1, Dz1T("1"), 1, Dz1T("1"), 1, Dz1T("1"), 1, Dz1T("1") },
	{ Dz1T("2"), Dz1T("2"), Dz1T("2"), 2, Dz1T("2"), 2, Dz1T("2"), 2, Dz1T("2"), 2, Dz1T("2") },
	{ Dz1T("3"), Dz1T("3"), Dz1T("3"), 3, Dz1T("3"), 3, Dz1T("3"), 3, Dz1T("3"), 3, Dz1T("3") },
	{ NULL,		 NULL,		NULL,	   0, NULL,		 0, NULL,		0, NULL,	  0, NULL}
};
static bool_t IncidentConditionsList_init_sample_data(IncidentConditionsList* p, Dz1Error* err) 
{ 
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		IncidentConditionsEntry* i = NULL, * node;
		for (i = incidentconditions_arr; errp->code == 0 && i->link_id != NULL; i++)
		{
			if ((node = IncidentConditionsEntry_clone(i, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(IncidentConditionsEntry_delAndSetNull, (void*)&node);
				if ((*errp = p->add(p, node)).code) ERR_OUT(errp);
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (IncidentConditionsEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static RoadwaySurfaceStatusEntry roadwaysurfacestatus_arr[] =
{
	{ Dz1T("1"), Dz1T("1"), 1, 1, 1, 1 },
	{ Dz1T("2"), Dz1T("2"), 2, 2, 2, 2 },
	{ Dz1T("3"), Dz1T("3"), 3, 3, 3, 3 },
	{ NULL,		 NULL,		0, 0, 0, 0 }
};
static bool_t RoadwaySurfaceStatusList_init_sample_data(RoadwaySurfaceStatusList* p, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		RoadwaySurfaceStatusEntry* i = NULL, * node;
		for (i = roadwaysurfacestatus_arr; errp->code == 0 && i->link_id != NULL; i++)
		{
			if ((node = RoadwaySurfaceStatusEntry_clone(i, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(RoadwaySurfaceStatusEntry_delAndSetNull, (void*)&node);
				if ((*errp = p->add(p, node)).code) ERR_OUT(errp);
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (RoadwaySurfaceStatusEntry_delAndSetNull, (void *)&node);
			}
		}
	}


	return ERR_IS_SUCCESS(errp);
}

static WeatherInformationEntry weatherinformation_arr[] =
{
	{ 0, 1, 1, 1, 1, Dz1T("1"), 1, 1, 1, 1, 1, 1, Dz1T("1"), Dz1T("1") },
	{ 1, 2, 2, 2, 2, Dz1T("2"), 2, 2, 2, 2, 2, 2, Dz1T("2"), Dz1T("2") },
	{ 2, 3, 3, 3, 3, Dz1T("3"), 3, 3, 3, 3, 3, 3, Dz1T("3"), Dz1T("3") },
	{ 0, 0, 0, 0, 0, NULL,		0, 0, 0, 0, 0, 0, NULL,		 NULL	   }
};
static bool_t WeatherInformationList_init_sample_data(WeatherInformationList* p, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		WeatherInformationEntry* i = NULL, * node;
		for (i = weatherinformation_arr; errp->code == 0 && i->forecast_or_actual != 2; i++)
		{
			if ((node = WeatherInformationEntry_clone(i, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(WeatherInformationEntry_delAndSetNull, (void*)&node);
				if ((*errp = p->add(p, node)).code) ERR_OUT(errp);
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (WeatherInformationEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ERR_IS_SUCCESS(errp); 
}

static LinkRoadwayGeometryEntry linkroadwaygeometry_arr[] =
{
	{ Dz1T("1"), DZ1INT64(-3000000001), 3000000001, Dz1T("1"), DZ1INT64(-3000000001), 3000000001, Dz1T("1"), 1, Dz1T("1"), 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ Dz1T("2"), DZ1INT64(-3000000002), 3000000002, Dz1T("2"), DZ1INT64(-3000000002), 3000000002, Dz1T("2"), 2, Dz1T("2"), 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ Dz1T("3"), DZ1INT64(-3000000003), 3000000003, Dz1T("3"), DZ1INT64(-3000000003), 3000000003, Dz1T("3"), 3, Dz1T("3"), 3, 3, 3, 3, 3, 3, 3, 3, 3 },
	{ NULL,		 0,						0,			NULL,	   0,					  0,		  NULL,		 0, NULL,	   0, 0, 0, 0, 0, 0, 0, 0, 0 }

};
static bool_t LinkRoadwayGeometryList_init_sample_data(LinkRoadwayGeometryList* p, Dz1Error* err) 
{ 
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		LinkRoadwayGeometryEntry* i = NULL, * node;
		for (i = linkroadwaygeometry_arr; errp->code == 0 && i->begin_node_id != NULL; i++)
		{
			if ((node = LinkRoadwayGeometryEntry_clone(i, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(LinkRoadwayGeometryEntry_delAndSetNull, (void*)&node);
				if ((*errp = p->add(p, node)).code) ERR_OUT(errp);
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (LinkRoadwayGeometryEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static ProbeVehicleDetectionEntry probevehicledetection_arr[] =
{
	{ Dz1T("1"), 1, Dz1T("1"), Dz1T("1"), 1, 1, Dz1T("1"), DZ1INT64(-3000000001), 3000000001, Dz1T("1"), DZ1INT64(-3000000001), 3000000001 },
	{ Dz1T("2"), 2, Dz1T("2"), Dz1T("2"), 2, 2, Dz1T("2"), DZ1INT64(-3000000002), 3000000002, Dz1T("2"), DZ1INT64(-3000000002), 3000000002 },
	{ Dz1T("3"), 3, Dz1T("3"), Dz1T("3"), 3, 3, Dz1T("3"), DZ1INT64(-3000000003), 3000000003, Dz1T("3"), DZ1INT64(-3000000003), 3000000003 },
	{ NULL,		 0, NULL,	   NULL,	  0, 0, NULL,	   0,					  0,		  NULL,		 0,						0		   }
};
static bool_t ProbeVehicleDetectionList_init_sample_data(ProbeVehicleDetectionList* p, Dz1Error* err)
{ 
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		ProbeVehicleDetectionEntry* i = NULL, * node;
		for (i = probevehicledetection_arr; errp->code == 0 && i->veh_id != NULL; i++)
		{
			if ((node = ProbeVehicleDetectionEntry_clone(i, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(ProbeVehicleDetectionEntry_delAndSetNull, (void*)&node);
				if ((*errp = p->add(p, node)).code) ERR_OUT(errp);
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (ProbeVehicleDetectionEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ERR_IS_SUCCESS(errp);
}
static DetectorCollectionEntry detectorcollection_arr[] =
{
	{ Dz1T("1"), Dz1T("1"), 1, 1, 1, 1 },
	{ Dz1T("2"), Dz1T("2"), 2, 2, 2, 2 },
	{ Dz1T("3"), Dz1T("3"), 3, 3, 3, 3 },
	{ NULL,		 NULL,		0, 0, 0, 0 }
};
static bool_t DetectorCollectionList_init_sample_data(DetectorCollectionList* p, Dz1Error* err)
{ 
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		DetectorCollectionEntry* i = NULL, * node;
		for (i = detectorcollection_arr; errp->code == 0 && i->detector_id != NULL; i++)
		{
			if ((node = DetectorCollectionEntry_clone(i, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(DetectorCollectionEntry_delAndSetNull, (void*)&node);
				if ((*errp = p->add(p, node)).code) ERR_OUT(errp);
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (DetectorCollectionEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ERR_IS_SUCCESS(errp); 
}

static u8_t sample_invalid[] = { 0xFF };

static u8_t sample_empty_list[] = {0x30, 0x00};

static u8_t  sample_spat[] =
{
	0x00, 0x13, 0x40,
	0x63, 0xD0, 0xF5, 0x0E, 0x0C, 0x28, 0x71, 0x00, 0xF8, 0x38, 0x30, 0xA1, 0xC4, 0x80, 0x02, 0x80,
	0x32, 0x00, 0xC1, 0x90, 0x3D, 0x0F, 0x50, 0x00, 0x00, 0x00, 0x00, 0x60, 0xE0, 0xC2, 0x87, 0x10,
	0x10, 0x18, 0x7E, 0x60, 0x72, 0x60, 0x72, 0x60, 0x72, 0x60, 0x72, 0x06, 0x07, 0x20, 0xF0, 0x41,
	0x50, 0x07, 0x80, 0x01, 0xE0, 0xF0, 0x07, 0x80, 0x1E, 0x81, 0xE0, 0xF0, 0x07, 0x80, 0x1E, 0x80
};

static u8_t sample_tls[] = {
0x00, 0x32, 0x21, 0x60, 0x20, 0x4D, 0x26, 0xB4, 0x9D, 0x1F, 0xF6, 0xB4, 0x9D, 0x20, 0x05, 0x82,
0xC0, 0x00, 0x80, 0x00, 0x87, 0xF7, 0xE9, 0xB0, 0xAC, 0xB0, 0x00, 0x06, 0x90, 0x00, 0x02, 0x00,
0x04, 0x04, 0x02, 0x80
};

static u8_t sample_tlsm[] = {
0x00, 0x32, 0x21, 0x60, 0x00, 0x00, 0x9A, 0x4D, 0x69, 0x3A, 0x3F, 0xED, 0x69, 0x3A, 0x40, 0x16,
0x16, 0x00, 0x04, 0x00, 0x04, 0x3F, 0xBF, 0x4D, 0x85, 0x65, 0x80, 0x00, 0x34, 0x80, 0x00, 0x08,
0x00, 0x20, 0x20, 0x00
};

static Dz1Binary b_sample_spat = { sample_spat, 67 };
static Dz1Binary b_sample_tls = { sample_tls, 36 };
static Dz1Binary b_sample_tlsm = { sample_tlsm, 36 };
static Dz1Binary b_sample_invalid = { sample_invalid, 2 };
static Dz1Binary b_sample_invalid2 = { sample_empty_list, 2 };


static ExtentionCommPDUEntry extention_comm_pdu_arr[] =
{
	{ 1, 1, 0, 1, TRUE,  82055, &b_sample_spat },
	// { 2, 2, 2, 9, TRUE,	 1234, &b_sample_tls },
	{ 2, 2, 2, 9, TRUE,	 1234, &b_sample_tlsm },
	// { 3, 3, 4, 3, TRUE,	 3, &extentioncommpdu_payload3 },
	// { 9, 9, 4, 3, TRUE,	 9999, &b_sample_invalid},
	 { 9, 9, 4, 3, TRUE,	 9999, &b_sample_invalid2},
	{ 0, 0, 0, 0, FALSE, 0, NULL					   }
};

static u8_t _payload_data_[] = { 0x00 };
static Dz1Binary extentioncommpdu_payload1 = { _payload_data_, sizeof(_payload_data_) };
static Dz1Binary extentioncommpdu_payload2 = { _payload_data_, sizeof(_payload_data_) };
static Dz1Binary extentioncommpdu_payload3 = { _payload_data_, sizeof(_payload_data_) };



static ExtentionCommPDUEntry extentioncommpdu_arr[] =
{
	{ 1, 1, 0, 1, TRUE,  1, &extentioncommpdu_payload1 },
	{ 2, 2, 2, 9, TRUE,	 2, &extentioncommpdu_payload2 },
	{ 3, 3, 4, 3, TRUE,	 3, &extentioncommpdu_payload3 },
	{ 0, 0, 0, 0, FALSE, 0, NULL					   }
};

static bool_t ExtentionCommPDUList_init_sample_data(ExtentionCommPDUList* p, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		time_t t;
		ExtentionCommPDUEntry* i;
		for (i = extentioncommpdu_arr; errp->code == 0 && i->payload != NULL; i++)
		{
			ExtentionCommPDUEntry* e;
			if ((e = ExtentionCommPDUEntry_new(i->idx, i->aid, (t = time(NULL) - i->delivery_stop), t + i->delivery_start, i->payload, errp)) == NULL) ERR_OUT(errp);

			{
				pthread_cleanup_push(ExtentionCommPDUEntry_delAndSetNull, (void*)&e);
				//if ((e->payload = Dz1Binary_clone(i->payload, errp)) == NULL) ERR_OUT(errp);
				if ((p->add(p, e)).code) ERR_OUT(errp);
				else
				{
					e = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1);// (ExtentionCommPDUEntry_delAndSetNull, (void*)&e);
			}
		}
	}
	return TRUE;
}

static bool_t CurrentLinkStateList_init_sample_data_by_psid(CurrentLinkStateList* p, u32_t psid, Dz1Error* err) { return TRUE; }
static bool_t EventIdentityList_init_sample_data_by_psid(EventIdentityList* p, u32_t psid, Dz1Error* err) { return TRUE; }
static bool_t IncidentIdentityList_init_sample_data_by_psid(IncidentIdentityList* p, u32_t psid, Dz1Error* err) { return TRUE; }
static bool_t IncidentConditionsList_init_sample_data_by_psid(IncidentConditionsList* p, u32_t psid, Dz1Error* err) { return TRUE; }
static bool_t RoadwaySurfaceStatusList_init_sample_data_by_psid(RoadwaySurfaceStatusList* p, u32_t psid, Dz1Error* err) { return TRUE; }
static bool_t WeatherInformationList_init_sample_data_by_psid(WeatherInformationList* p, u32_t psid, Dz1Error* err) { return TRUE; }
static bool_t LinkRoadwayGeometryList_init_sample_data_by_psid(LinkRoadwayGeometryList* p, u32_t psid, Dz1Error* err) { return TRUE; }
static bool_t ProbeVehicleDetectionList_init_sample_data_by_psid(ProbeVehicleDetectionList* p, u32_t psid, Dz1Error* err) { return TRUE; }
static bool_t DetectorCollectionList_init_sample_data_by_psid(DetectorCollectionList* p, u32_t psid, Dz1Error* err) { return TRUE; }
static bool_t ExtentionCommPDUList_init_sample_data_by_psid(ExtentionCommPDUList* p, u32_t psid, Dz1Error* err) {
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		ExtentionCommPDUEntry* i;
		for (i = extention_comm_pdu_arr; errp->code == 0 && i->payload != NULL; i++)
		{
			time_t t;
			ExtentionCommPDUEntry* e;
			if (i->payload_type == psid)		/// 우선 psid
			{
				if ((e = ExtentionCommPDUEntry_new(i->idx, i->aid, (t = time(NULL) - i->delivery_stop), t + i->delivery_start, NULL, errp)) == NULL) ERR_OUT(errp);
				{
					pthread_cleanup_push(ExtentionCommPDUEntry_delAndSetNull, (void*)&e);
					if ((e->payload = Dz1Binary_clone(i->payload, errp)) == NULL) ERR_OUT(errp);
					else if ((*errp = p->add(p, e)).code) ERR_OUT(errp);
					else
					{
						e = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1);// (ExtentionCommPDUEntry_delAndSetNull, (void*)&e);
				}
				break;
			}
		}
	}

	return TRUE;
}

static bool_t CurrentLinkStateList_init_sample_data_by_psid_and_payload_type(CurrentLinkStateList* p, u32_t psid, u32_t payloadType, Dz1Error* err) { return TRUE; }
static bool_t EventIdentityList_init_sample_data_by_psid_and_payload_type(EventIdentityList* p, u32_t psid, u32_t payloadType, Dz1Error* err) { return TRUE; }
static bool_t IncidentIdentityList_init_sample_data_by_psid_and_payload_type(IncidentIdentityList* p, u32_t psid, u32_t payloadType, Dz1Error* err) { return TRUE; }
static bool_t IncidentConditionsList_init_sample_data_by_psid_and_payload_type(IncidentConditionsList* p, u32_t psid, u32_t payloadType, Dz1Error* err) { return TRUE; }
static bool_t RoadwaySurfaceStatusList_init_sample_data_by_psid_and_payload_type(RoadwaySurfaceStatusList* p, u32_t psid, u32_t payloadType, Dz1Error* err) { return TRUE; }
static bool_t WeatherInformationList_init_sample_data_by_psid_and_payload_type(WeatherInformationList* p, u32_t psid, u32_t payloadType, Dz1Error* err) { return TRUE; }
static bool_t LinkRoadwayGeometryList_init_sample_data_by_psid_and_payload_type(LinkRoadwayGeometryList* p, u32_t psid, u32_t payloadType, Dz1Error* err) { return TRUE; }
static bool_t ProbeVehicleDetectionList_init_sample_data_by_psid_and_payload_type(ProbeVehicleDetectionList* p, u32_t psid, u32_t payloadType, Dz1Error* err) { return TRUE; }
static bool_t DetectorCollectionList_init_sample_data_by_psid_and_payload_type(DetectorCollectionList* p, u32_t psid, u32_t payloadType, Dz1Error* err) { return TRUE; }
static bool_t ExtentionCommPDUList_init_sample_data_by_psid_and_payload_type(ExtentionCommPDUList* p, u32_t psid, u32_t payloadType, Dz1Error* err) { return TRUE; }

Iso14827TestMsgStructAPI TechnicalRegulation1MsgSet[] =
{	// XXX : gmkim = 각 자료 구조별 변환/인코드 API 등록
	Iso14827TestMsgUtilAPIEntry(Dz1T("1.0.14827.1.0.1"), CurrentLinkStateList, Dz1CurrentLinkStateResponse),
	Iso14827TestMsgUtilAPIEntry(Dz1T("1.0.14827.1.0.2"), EventIdentityList, Dz1EventIdentityResponse),
	Iso14827TestMsgUtilAPIEntry(Dz1T("1.0.14827.1.0.3"), IncidentIdentityList, Dz1IncidentIdentityResponse),
	Iso14827TestMsgUtilAPIEntry(Dz1T("1.0.14827.1.0.4"), IncidentConditionsList, Dz1IncidentConditionsResponse),
	Iso14827TestMsgUtilAPIEntry(Dz1T("1.0.14827.1.0.5"), RoadwaySurfaceStatusList, Dz1RoadwaySurfaceStatusResponse),
	Iso14827TestMsgUtilAPIEntry(Dz1T("1.0.14827.1.0.6"), WeatherInformationList, Dz1WeatherInformationResponse),
	Iso14827TestMsgUtilAPIEntry(Dz1T("1.0.14827.1.0.7"), LinkRoadwayGeometryList, Dz1LinkRoadwayGeometryResponse),
	Iso14827TestMsgUtilAPIEntry(Dz1T("1.0.14827.1.0.8"), ProbeVehicleDetectionList, Dz1ProbeVehicleDetectionResponse),
	Iso14827TestMsgUtilAPIEntry(Dz1T("1.0.14827.1.0.9"), DetectorCollectionList, Dz1DetectorCollectionResponse),
	Iso14827TestMsgUtilAPIEntry(Dz1T("1.0.14827.1.1.0"), ExtentionCommPDUList, Dz1ExtentionCommPDUResponse),
	{ NULL, NULL }
};

Iso14827TestMsgStructAPI TechnicalRegulation1_PolicePrj4C2CMsgSet[] =
{
	Iso14827TestMsgUtilAPIEntry(Dz1T("1.0.14827.1.1.0"), ExtentionCommPDUList, Dz1ExtentionCommPDUResponse),
	{ NULL, NULL }
};


Iso14827TestMsgStructAPI TechnicalRegulation1_PolicePrj4C2CMsgSet2[] =
{
	Iso14827TestMsgUtilAPIEntry(Dz1T("1.0.14827.1.1.0"), ExtentionCommPDUList, Dz1ExtentionCommPDUResponse),
	{ NULL, NULL }
};


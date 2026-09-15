#include <ITSK00100_3Util.h>
#include <Iso14827TestMsgUtil.h>
#include <GitsnAsnUtil.h>


static Dz1NMEACoord_latitude* convert_nmea_coord_latitude(Gitsn_NMEACoord_latitude* src, Dz1Error* errp)
{
	Dz1NMEACoord_latitude* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Dz1NMEACoord_latitude_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1NMEACoord_latitude_delAndSetNull, (void*)&ret);
		ret->integerValue = (u8_t)src->integerValue;
		ret->fractionValue = (u8_t)src->fractionValue;
		ret->fracSize = (u8_t)src->fracSize;
		ret->compass = (Dz1NMEACoord_compass)src->compass;
		Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1NMEACoord_latitude_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Dz1NMEACoord_longitude* convert_nmea_coord_longitude(Gitsn_NMEACoord_longitude* src, Dz1Error* errp)
{
	Dz1NMEACoord_longitude* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Dz1NMEACoord_longitude_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1NMEACoord_longitude_delAndSetNull, (void*)&ret);
		ret->integerValue = (u8_t)src->integerValue;
		ret->fractionValue = (u8_t)src->fractionValue;
		ret->fracSize = (u8_t)src->fracSize;
		ret->compass = (Dz1NMEACoord_compass)src->compass;
		Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1NMEACoord_longitude_delAndSetNull, (void*)&ret);
	}
	return ret;
}


static Dz1NMEACoord* convert_nmea_coord(Gitsn_NMEACoord* src, Dz1Error* errp)
{
	Dz1NMEACoord* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Dz1NMEACoord_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1NMEACoord_delAndSetNull, (void*)&ret);
		if (0) {}
		else if ((ret->latitude = convert_nmea_coord_latitude(src->latitude, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->longitude = convert_nmea_coord_longitude(src->longitude, errp)) == NULL) ERR_OUT(errp);
		else
		{
			if (src->optData != NULL)
			{
				if ((ret->optData = Dz1Asn1OctetStr_new(src->optData->data, src->optData->size, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			else Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1NMEACoord_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static void* Gitsn_IncidentDetectionInfoResponse_convert(void* src, Dz1Error* errp)
{
	Dz1IncidentDetectionInfoResponse* ret = NULL;
	Gitsn_IncidentDetectionInfoResponse* list = NULL;

	if ((list = src) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1IncidentDetectionInfoResponse_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Gitsn_IncidentDetectionInfo* entry = NULL;
		pthread_cleanup_push(Dz1IncidentDetectionInfoResponse_delAndSetNull, (void*)&ret);
		while ((entry = list->getHead(list)) != NULL && errp->code == 0)
		{
			list->extract(list, entry);
			Dz1IncidentDetectionInfo* data = NULL;
			if ((data = Dz1IncidentDetectionInfo_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1IncidentDetectionInfo_delAndSetNull, (void*)&data);
				if (0) {}
				else if ((data->incident_Detected_Time = Dz1Asn1UTF8Str_newFromStr(entry->incident_Detected_Time, errp)) == NULL) ERR_OUT(errp);
				else if ((data->incident_Detected_Site = convert_nmea_coord(entry->incident_Detected_Site, errp)) == NULL) ERR_OUT(errp);
				else
				{
					data->detected_Object_Distance = (u8_t)entry->detected_Object_Distance;
					data->detected_Object_Angle = (u8_t)entry->detected_Object_Angle;
					data->detected_Object_Speed = (u8_t)entry->detected_Object_Speed;
					data->detected_Object_Size = Dz1u8_new((u8_t)entry->detected_Object_Size, NULL);

					if ((*errp = ret->add(ret, data)).code) ERR_OUT(errp);
					else
					{
						data = NULL;
						Dz1Error_set(errp, 0);
					}
				}
				pthread_cleanup_pop(1); // (Dz1IncidentDetectionInfo_delAndSetNull, (void*)&data);
			}
		}
		pthread_cleanup_pop(errp->code); // (Dz1IncidentDetectionInfoResponse_delAndSetNull, (void*)&ret);
	}
	return ret;
}
static _encoder_declare_(Dz1IncidentDetectionInfoResponse, IncidentDetectionInfoResponse)
static _decoder_declare_(Dz1IncidentDetectionInfoResponse, IncidentDetectionInfoResponse)

static Gitsn_NMEACoord_latitude nmea_cooord_latitude [] = {
	{1, 1, 1, Gitsn_NMEACoord_compass_north},
	{2, 2, 2, Gitsn_NMEACoord_compass_south},
	{0, 0, 0, Gitsn_NMEACoord_compass_max}
};


static Gitsn_NMEACoord_longitude nmea_cooord_longitude[] = {
	{1, 1, 1, Gitsn_NMEACoord_compass_north},
	{2, 2, 2, Gitsn_NMEACoord_compass_south},
	{0, 0, 0, Gitsn_NMEACoord_compass_max}
};


static Gitsn_NMEACoord incident_nmea_coord[] = {
	{nmea_cooord_latitude, }
};
static Gitsn_IncidentDetectionInfo incident_detection_info[] =
{
	{Dz1T("20250101"), Gitsn_IncidentDetectionInfo_incident_Detected_Type_roadkill, }

};

static void* Gitsn_IncidentDetectionInfoResponse_get_eam_list(void* struct_ptr, Dz1Error* errp)
{

	return NULL;
}

static bool_t Gitsn_IncidentDetectionInfoResponse_init_sample_data(Gitsn_IncidentDetectionInfoResponse* p, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);


	return ERR_IS_SUCCESS(errp);
}
static bool_t Gitsn_IncidentDetectionInfoResponse_init_sample_data_by_psid(Gitsn_IncidentDetectionInfoResponse* p, u32_t psid, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return ERR_IS_SUCCESS(errp);
}
static bool_t Gitsn_IncidentDetectionInfoResponse_init_sample_data_by_psid_and_payload_type(Gitsn_IncidentDetectionInfoResponse* p, u32_t psid, u32_t payloadType, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return ERR_IS_SUCCESS(errp);
}


// 돌발상황해지정보
static void* Gitsn_IncidentTerminationInfoResponse_convert(void* src, Dz1Error* errp)
{
	Dz1IncidentTerminationInfoResponse* ret = NULL;

	Gitsn_IncidentTerminationInfoResponse* list = (Gitsn_IncidentTerminationInfoResponse*)src;

	if (list == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Dz1IncidentTerminationInfoResponse_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Gitsn_IncidentTerminationInfo* entry = NULL;
		pthread_cleanup_push(Dz1IncidentTerminationInfoResponse_delAndSetNull, (void*)&ret);
		
		while ((entry = list->getHead(list)) != NULL && errp->code == 0)
		{
			list->extract(list, entry);
			Dz1IncidentTerminationInfo* data = NULL;

			if ((data = Dz1IncidentTerminationInfo_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1IncidentTerminationInfo_delAndSetNull, (void*)&data);

				data->terminate_incidentType = entry->terminate_incidentType;

				if ((*errp = ret->add(ret, data)).code) ERR_OUT(errp);
				else
				{
					data = NULL;
					Dz1Error_set(errp, 0);
				}

				pthread_cleanup_pop(1); // (Dz1IncidentTerminationInfo_delAndSetNull, (void*)&data);
			}

		}
		pthread_cleanup_pop(errp->code); // (Dz1IncidentTerminationInfoResponse_delAndSetNull, (void*)&ret);
	}
	return ret;
}	

static void* Gitsn_IncidentTerminationInfoResponse_get_eam_list(void* struct_ptr, Dz1Error* errp)
{

	return NULL;
}

static bool_t Gitsn_IncidentTerminationInfoResponse_init_sample_data(Gitsn_IncidentTerminationInfoResponse* p, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);


	return ERR_IS_SUCCESS(errp);
}
static bool_t Gitsn_IncidentTerminationInfoResponse_init_sample_data_by_psid(Gitsn_IncidentTerminationInfoResponse* p, u32_t psid, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return ERR_IS_SUCCESS(errp);
}
static bool_t Gitsn_IncidentTerminationInfoResponse_init_sample_data_by_psid_and_payload_type(Gitsn_IncidentTerminationInfoResponse* p, u32_t psid, u32_t payloadType, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return ERR_IS_SUCCESS(errp);
}

static _encoder_declare_(Dz1IncidentTerminationInfoResponse, IncidentTerminationInfoResponse)
static _decoder_declare_(Dz1IncidentTerminationInfoResponse, IncidentTerminationInfoResponse)


static void* Gitsn_IncidentDetectionVideoFileInfoProvideResponse_convert(void* src, Dz1Error* errp)
{
	Dz1IncidentDetectionVideoFileInfoProvideResponse* ret = NULL;
	Gitsn_IncidentDetectionVideoFileInfoProvideResponse* list = (Gitsn_IncidentDetectionVideoFileInfoProvideResponse*)src;
	if (list == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Dz1IncidentDetectionVideoFileInfoProvideResponse_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Gitsn_IncidentDetectionVideoFileInfoProvide* entry = NULL;
		pthread_cleanup_push(Dz1IncidentDetectionVideoFileInfoProvideResponse_delAndSetNull, (void*)&ret);
		while ((entry = list->getHead(list)) != NULL && errp->code == 0)
		{
			Dz1IncidentDetectionVideoFileInfoProvide* data = NULL;
			if ((data = Dz1IncidentDetectionVideoFileInfoProvide_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1IncidentDetectionVideoFileInfoProvide_delAndSetNull, (void*)&data);
				data->fileStatus = entry->fileSatatus;

				if (entry->fileName != NULL)
				{
					if ((data->fileName = Dz1Asn1UTF8Str_newFromStr(entry->fileName, errp)) == NULL) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}

				data->fileSize = Dz1s64_new(entry->fileSize, NULL);

				if ((*errp = ret->add(ret, data)).code) ERR_OUT(errp);
				else
				{
					data = NULL;
					Dz1Error_set(errp, 0);
				}

				pthread_cleanup_pop(1); // ((Dz1IncidentDetectionVideoFileInfoProvide_delAndSetNull, (void*)&data);
			}
		}
		pthread_cleanup_pop(errp->code); // (Dz1IncidentDetectionVideoFileInfoProvideResponse_delAndSetNull, (void*)&ret);
	}

	return ret;
}

static void* Gitsn_IncidentDetectionVideoFileInfoProvideResponse_get_eam_list(void* struct_ptr, Dz1Error* errp)
{

	return NULL;
}

static bool_t Gitsn_IncidentDetectionVideoFileInfoProvideResponse_init_sample_data(Gitsn_IncidentDetectionVideoFileInfoProvideResponse* p, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);


	return ERR_IS_SUCCESS(errp);
}
static bool_t Gitsn_IncidentDetectionVideoFileInfoProvideResponse_init_sample_data_by_psid(Gitsn_IncidentDetectionVideoFileInfoProvideResponse* p, u32_t psid, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return ERR_IS_SUCCESS(errp);
}
static bool_t Gitsn_IncidentDetectionVideoFileInfoProvideResponse_init_sample_data_by_psid_and_payload_type(Gitsn_IncidentDetectionVideoFileInfoProvideResponse* p, u32_t psid, u32_t payloadType, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return ERR_IS_SUCCESS(errp);
}

static _encoder_declare_(Dz1IncidentDetectionVideoFileInfoProvideResponse, IncidentDetectionVideoFileInfoProvideResponse)
static _decoder_declare_(Dz1IncidentDetectionVideoFileInfoProvideResponse, IncidentDetectionVideoFileInfoProvideResponse)



static void* Gitsn_ControlStateInfoResponse_convert(void* src, Dz1Error* errp)
{
	Dz1ControlStateInfoResponse* ret = NULL;
	
	Gitsn_ControlStateInfoResponse* list = (Gitsn_ControlStateInfoResponse*)src;
	if (list == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Dz1ControlStateInfoResponse_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Gitsn_ControlStateInfo* entry = NULL;
		pthread_cleanup_push(Dz1ControlStateInfoResponse_delAndSetNull, (void*)&ret);
		while ((entry = list->getHead(list)) != NULL && errp->code == 0)
		{
			list->extract(list, entry);
			Dz1ControlStateInfo* data = NULL;

			if ((data = Dz1ControlStateInfo_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1ControlStateInfo_delAndSetNull, (void*)&data);
				data->cpu = (u8_t)entry->cpu;
				data->ram = (u8_t)entry->ram;
				data->disk = (u8_t)entry->disk;

				if ((*errp = ret->add(ret, data)).code) ERR_OUT(errp);
				else
				{
					data = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (Dz1ControlStateInfo_delAndSetNull, (void*)&data);
			}
		}
		pthread_cleanup_pop(errp->code); // (Dz1ControlStateInfoResponse_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static void* Gitsn_ControlStateInfoResponse_get_eam_list(void* struct_ptr, Dz1Error* errp)
{
	return NULL;
}

static bool_t Gitsn_ControlStateInfoResponse_init_sample_data(Gitsn_ControlStateInfoResponse* p, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);


	return ERR_IS_SUCCESS(errp);
}
static bool_t Gitsn_ControlStateInfoResponse_init_sample_data_by_psid(Gitsn_ControlStateInfoResponse* p, u32_t psid, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return ERR_IS_SUCCESS(errp);
}
static bool_t Gitsn_ControlStateInfoResponse_init_sample_data_by_psid_and_payload_type(Gitsn_ControlStateInfoResponse* p, u32_t psid, u32_t payloadType, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return ERR_IS_SUCCESS(errp);
}

static _encoder_declare_(Dz1ControlStateInfoResponse, ControlStateInfoResponse)
static _decoder_declare_(Dz1ControlStateInfoResponse, ControlStateInfoResponse)


static void* Gitsn_SensorStateInfoResponse_convert(void* src, Dz1Error* errp)
{
	Dz1SensorStateInfoResponse* ret = NULL;

	Gitsn_SensorStateInfoResponse* list = (Gitsn_SensorStateInfoResponse*)src;
	if (list == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Dz1SensorStateInfoResponse_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Gitsn_SensorStateInfo* entry = NULL;
		pthread_cleanup_push(Dz1SensorStateInfoResponse_delAndSetNull, (void*)&ret);
		while ((entry = list->getHead(list)) != NULL && errp->code == 0)
		{
			list->extract(list, entry);
			Dz1SensorStateInfo* data = NULL;

			if ((data = Dz1SensorStateInfo_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1SensorStateInfo_delAndSetNull, (void*)&data);
				data->msm = entry->msm;
				data->txb = entry->txb;
				data->rxb = entry->rxb;
				data->pwr = entry->pwr;

				if ((*errp = ret->add(ret, data)).code) ERR_OUT(errp);
				else
				{
					data = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (Dz1SensorStateInfo_delAndSetNull, (void*)&data);
			}
		}
		pthread_cleanup_pop(errp->code); // (Dz1SensorStateInfoResponse_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static void* Gitsn_SensorStateInfoResponse_get_eam_list(void* struct_ptr, Dz1Error* errp)
{
	return NULL;
}

static bool_t Gitsn_SensorStateInfoResponse_init_sample_data(Gitsn_SensorStateInfoResponse* p, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);


	return ERR_IS_SUCCESS(errp);
}
static bool_t Gitsn_SensorStateInfoResponse_init_sample_data_by_psid(Gitsn_SensorStateInfoResponse* p, u32_t psid, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return ERR_IS_SUCCESS(errp);
}
static bool_t Gitsn_SensorStateInfoResponse_init_sample_data_by_psid_and_payload_type(Gitsn_SensorStateInfoResponse* p, u32_t psid, u32_t payloadType, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return ERR_IS_SUCCESS(errp);
}
static _encoder_declare_(Dz1SensorStateInfoResponse, SensorStateInfoResponse)
static _decoder_declare_(Dz1SensorStateInfoResponse, SensorStateInfoResponse)


static Dz1FullPositionVector_00100* convert_full_position_vector(Gitsn_FullPositionVector* src, Dz1Error* errp)
{
	Dz1FullPositionVector_00100* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Dz1FullPositionVector_00100_new((Dz1Longitude_00100)src->lon, (Dz1Latitude_00100)src->lat, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1FullPositionVector_00100_delAndSetNull, (void*)&ret);
		if (src->utcTime != NULL)
		{
			if ((ret->utcTime = Dz1DDateTime_00100_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
					ret->utcTime-> year = (Dz1DYear_00100*)src->utcTime;
					ret->utcTime->month = (Dz1DMonth_00100*)src->utcTime;
					ret->utcTime->day = (Dz1DDay_00100*)src->utcTime;
					ret->utcTime->hour = (Dz1DHour_00100*)src->utcTime;
					ret->utcTime->minute = (Dz1DMinute_00100*)src->utcTime;
					ret->utcTime->second = (Dz1DSecond_00100*)src->utcTime;
					ret->utcTime->offset = (Dz1DOffset_00100*)src->utcTime;
					Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(errp->code); // (Dz1FullPositionVector_00100_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static void* Gitsn_MovingObjectResponse_convert(void* src, Dz1Error* errp)
{
	Dz1MovingObjectResponse* ret = NULL;
	Gitsn_MovingObjectResponse* list = (Gitsn_MovingObjectResponse*)src;

	if (list == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Dz1MovingObjectResponse_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Gitsn_MovingObject* entry = NULL;
		pthread_cleanup_push(Dz1MovingObjectResponse_delAndSetNull, (void*)&ret);
		while ((entry = list->getHead(list)) != NULL && errp->code == 0)
		{
			list->extract(list, entry);
			Dz1MovingObject* data = NULL;
			if ((data = Dz1MovingObject_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1MovingObject_delAndSetNull, (void*)&data);
				if ((data->fullPositionVector = convert_full_position_vector(entry->fullPositionVector, errp)) == NULL) ERR_OUT(errp);
				else
				{
					data->objectType = entry->objectType;
					data->objectID = entry->objectID;
					data->reliability = (u8_t)entry->reliability;
					data->novelty = Dz1Novelty_new((Dz1Novelty *)entry->novelty, NULL);

					if ((*errp = ret->add(ret, data)).code) ERR_OUT(errp);
					else
					{
						data = NULL;
						Dz1Error_set(errp, 0);
					}
				}
				pthread_cleanup_pop(1); // (Dz1MovingObject_delAndSetNull, (void*)&data);
			}
		}
		pthread_cleanup_pop(errp->code); // (Dz1MovingObjectResponse_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static void* Gitsn_MovingObjectResponse_get_eam_list(void* struct_ptr, Dz1Error* errp)
{
	return NULL;
}

static bool_t Gitsn_MovingObjectResponse_init_sample_data(Gitsn_MovingObjectResponse* p, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);


	return ERR_IS_SUCCESS(errp);
}
static bool_t Gitsn_MovingObjectResponse_init_sample_data_by_psid(Gitsn_MovingObjectResponse* p, u32_t psid, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return ERR_IS_SUCCESS(errp);
}
static bool_t Gitsn_MovingObjectResponse_init_sample_data_by_psid_and_payload_type(Gitsn_MovingObjectResponse* p, u32_t psid, u32_t payloadType, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	return ERR_IS_SUCCESS(errp);
}

static _encoder_declare_(Dz1MovingObjectResponse, MovingObjectResponse)
static _decoder_declare_(Dz1MovingObjectResponse, MovingObjectResponse)



Iso14827TestMsgStructAPI ITSK00100_3MsgSet[] =
{
	Iso14827TestMsgUtilAPIEntry(Dz1T("1.0.14827.1.1.0"), Gitsn_IncidentDetectionInfoResponse, Dz1IncidentDetectionInfoResponse),
	Iso14827TestMsgUtilAPIEntry(Dz1T("1.0.14827.1.1.1"), Gitsn_IncidentTerminationInfoResponse, Dz1IncidentTerminationInfoResponse),
	Iso14827TestMsgUtilAPIEntry(Dz1T("1.0.14827.1.1.2"), Gitsn_IncidentDetectionVideoFileInfoProvideResponse, Dz1IncidentDetectionVideoFileInfoProvideResponse),
	Iso14827TestMsgUtilAPIEntry(Dz1T("1.0.14827.1.1.3"), Gitsn_ControlStateInfoResponse, Dz1ControlStateInfoResponse),
	Iso14827TestMsgUtilAPIEntry(Dz1T("1.0.14827.1.1.4"), Gitsn_SensorStateInfoResponse, Dz1SensorStateInfoResponse),
	Iso14827TestMsgUtilAPIEntry(Dz1T("1.0.14827.1.1.5"), Gitsn_MovingObjectResponse, Dz1MovingObjectResponse),
	{NULL, NULL}
};


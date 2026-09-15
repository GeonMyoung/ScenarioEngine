#include <ITSK00144_2TestMsgSample.h>


I2XTrafficSafetyDeviceLinkUnitStatus* sample_i2x_traffic_safety_device_link_unit_status;
I2XTrafficSafetyDeviceStatusInfo* sample_i2x_traffic_safety_device_status_info;
I2XTrafficSafetyDeviceList* sample_i2x_traffic_safety_device_list;

static bool_t _init_sample_i2x_traffic_safety_device_link_unit_status(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (sample_i2x_traffic_safety_device_link_unit_status != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((sample_i2x_traffic_safety_device_link_unit_status = I2XTrafficSafetyDeviceLinkUnitStatus_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(I2XTrafficSafetyDeviceLinkUnitStatus_delAndSetNull, (void*)&sample_i2x_traffic_safety_device_link_unit_status);
		sample_i2x_traffic_safety_device_link_unit_status->isActive=TRUE;
		sample_i2x_traffic_safety_device_link_unit_status->control_comm=TRUE;
		sample_i2x_traffic_safety_device_link_unit_status->wave_comm=TRUE;
		sample_i2x_traffic_safety_device_link_unit_status->temperature=36;
		sample_i2x_traffic_safety_device_link_unit_status->humidity=60;
		sample_i2x_traffic_safety_device_link_unit_status->isOpen=TRUE;
		sample_i2x_traffic_safety_device_link_unit_status->isFanOn=TRUE;
		sample_i2x_traffic_safety_device_link_unit_status->isHeaterOn=TRUE;
		Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (I2XTrafficSafetyDeviceLinkUnitStatus_delAndSetNull, (void*)&sample_i2x_traffic_safety_device_link_unit_status);
	}
	return ERR_IS_SUCCESS(errp);
}

static I2XTrafficSafetyDeviceStatus* sample_i2x_traffic_safety_device_status1;
static I2XTrafficSafetyDeviceStatus* sample_i2x_traffic_safety_device_status2;

static I2XTrafficSafetyDeviceSerialNo sample_id1 = { 0x4D, 0x00000005 };
static I2XTrafficSafetyDeviceSerialNo sample_id2 = { 0x4D, 0x00000006 };

static bool_t init_sample_i2x_traffic_safety_device_status1(Dz1Error* errp)
{
	if (sample_i2x_traffic_safety_device_status1 != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((sample_i2x_traffic_safety_device_status1 = I2XTrafficSafetyDeviceStatus_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(I2XTrafficSafetyDeviceStatus_delAndSetNull, (void*)&sample_i2x_traffic_safety_device_status1);
		if (0) {}
		else if ((sample_i2x_traffic_safety_device_status1->id = I2XTrafficSafetyDeviceSerialNo_clone(&sample_id1, errp)) == NULL) ERR_OUT(errp);
		else
		{
			sample_i2x_traffic_safety_device_status1->isActive = TRUE;
			sample_i2x_traffic_safety_device_status1->isBatteryOn= TRUE;
			sample_i2x_traffic_safety_device_status1->isPowered= TRUE;
			sample_i2x_traffic_safety_device_status1->isPowerOn= TRUE;
			sample_i2x_traffic_safety_device_status1->isConnected= TRUE;
			sample_i2x_traffic_safety_device_status1->cnt= 1;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (I2XTrafficSafetyDeviceStatus_delAndSetNull, (void*)&sample_i2x_traffic_safety_device_status1);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t init_sample_i2x_traffic_safety_device_status2(Dz1Error* errp)
{
	if (sample_i2x_traffic_safety_device_status2 != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((sample_i2x_traffic_safety_device_status2 = I2XTrafficSafetyDeviceStatus_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(I2XTrafficSafetyDeviceStatus_delAndSetNull, (void*)&sample_i2x_traffic_safety_device_status2);
		if (0) {}
		else if ((sample_i2x_traffic_safety_device_status2->id = I2XTrafficSafetyDeviceSerialNo_clone(&sample_id2, errp)) == NULL) ERR_OUT(errp);
		else
		{
			sample_i2x_traffic_safety_device_status2->isActive = TRUE;
			sample_i2x_traffic_safety_device_status2->isBatteryOn = TRUE;
			sample_i2x_traffic_safety_device_status2->isPowered = TRUE;
			sample_i2x_traffic_safety_device_status2->isPowerOn = TRUE;
			sample_i2x_traffic_safety_device_status2->isConnected = TRUE;
			sample_i2x_traffic_safety_device_status2->cnt = 1;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (I2XTrafficSafetyDeviceStatus_delAndSetNull, (void*)&sample_i2x_traffic_safety_device_status2);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _init_sample_i2x_traffic_safety_device_status_info(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (sample_i2x_traffic_safety_device_status_info != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((sample_i2x_traffic_safety_device_status_info = I2XTrafficSafetyDeviceStatusInfo_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(I2XTrafficSafetyDeviceStatusInfo_delAndSetNull, (void*)&sample_i2x_traffic_safety_device_status_info);
		sample_i2x_traffic_safety_device_status_info->num = 2;
		if ((sample_i2x_traffic_safety_device_status_info->status = I2XTrafficSafetyDeviceStatusList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			if ((*errp = sample_i2x_traffic_safety_device_status_info->status->add(sample_i2x_traffic_safety_device_status_info->status, sample_i2x_traffic_safety_device_status1)).code) ERR_OUT(errp);
			else if ((*errp = sample_i2x_traffic_safety_device_status_info->status->add(sample_i2x_traffic_safety_device_status_info->status, sample_i2x_traffic_safety_device_status2)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (I2XTrafficSafetyDeviceStatusInfo_delAndSetNull, (void*)&sample_i2x_traffic_safety_device_status_info);

	}
	return ERR_IS_SUCCESS(errp);
}


static bool_t _init_sample_i2x_traffic_safety_device_list(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (sample_i2x_traffic_safety_device_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else if ((sample_i2x_traffic_safety_device_list = I2XTrafficSafetyDeviceList_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(I2XTrafficSafetyDeviceList_delAndSetNull, (void*)&sample_i2x_traffic_safety_device_list);
		sample_i2x_traffic_safety_device_list->cnt = 2;
		if ((sample_i2x_traffic_safety_device_list->id = I2XTrafficSafetyDeviceSerialNoList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			I2XTrafficSafetyDeviceSerialNo* entry = NULL;
			if ((entry = I2XTrafficSafetyDeviceSerialNo_clone(&sample_id1, errp)) == NULL) ERR_OUT(errp);
			else if ((*errp = sample_i2x_traffic_safety_device_list->id->add(sample_i2x_traffic_safety_device_list->id, entry)).code) ERR_OUT(errp);
			else if ((entry = I2XTrafficSafetyDeviceSerialNo_clone(&sample_id2, errp)) == NULL) ERR_OUT(errp);
			else if ((*errp = sample_i2x_traffic_safety_device_list->id->add(sample_i2x_traffic_safety_device_list->id, entry)).code) ERR_OUT(errp);
			else
			{
				entry = NULL;
				Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(errp->code); // (I2XTrafficSafetyDeviceList_delAndSetNull, (void*)&sample_i2x_traffic_safety_device_list);
	}

	return ERR_IS_SUCCESS(errp);
}

bool_t ITSK00144_2TestMsg_initSample(Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);


	if (sample_i2x_traffic_safety_device_link_unit_status != NULL || sample_i2x_traffic_safety_device_status_info != NULL || sample_i2x_traffic_safety_device_list != NULL) ERR_SET_OUT(errp, EEXIST);
	else
	{



		if (0) {}
		else if (init_sample_i2x_traffic_safety_device_status1(errp) == FALSE) ERR_OUT(errp);
		else if (init_sample_i2x_traffic_safety_device_status2(errp) == FALSE) ERR_OUT(errp);

		else if (_init_sample_i2x_traffic_safety_device_link_unit_status(errp) == FALSE) ERR_OUT(errp);
		else if (_init_sample_i2x_traffic_safety_device_status_info(errp) == FALSE) ERR_OUT(errp);
		else if (_init_sample_i2x_traffic_safety_device_list(errp) == FALSE) ERR_OUT(errp);
		else
		{
			I2XTrafficSafetyDeviceLinkUnitStatus_dump(sample_i2x_traffic_safety_device_link_unit_status, 4);
			I2XTrafficSafetyDeviceStatusInfo_dump(sample_i2x_traffic_safety_device_status_info, 4);
			I2XTrafficSafetyDeviceList_dump(sample_i2x_traffic_safety_device_list, 4);
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

void ITSK00144_2TestMsg_clearSample(Dz1Error* err)
{
	if (sample_i2x_traffic_safety_device_link_unit_status != NULL)
		I2XTrafficSafetyDeviceLinkUnitStatus_delAndSetNull((void*)&sample_i2x_traffic_safety_device_link_unit_status);
	if (sample_i2x_traffic_safety_device_status_info != NULL)
		I2XTrafficSafetyDeviceStatusInfo_delAndSetNull((void*)&sample_i2x_traffic_safety_device_status_info);
	if (sample_i2x_traffic_safety_device_list != NULL)
		I2XTrafficSafetyDeviceList_delAndSetNull((void*)&sample_i2x_traffic_safety_device_list);
}


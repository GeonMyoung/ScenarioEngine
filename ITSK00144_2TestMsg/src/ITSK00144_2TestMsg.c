#include <ITSK00144_2TestMsg.h>

// implement library functions here



// I2XTrafficSafetyDeviceLinkUnitStatus codec
static bool_t I2XTrafficSafetyDeviceLinkUnitStatus_encode(u8_t* dst, size_t sz, I2XTrafficSafetyDeviceLinkUnitStatus* src, Dz1Error* errp)
{
	if (dst == NULL || sz < 8 || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u8_t* dp = dst;
		*dp = 0x00;
		*dp++ = src->isActive;
		*dp++ = src->control_comm;
		*dp++ = src->wave_comm;
		*dp++ = src->temperature;
		*dp++ = src->humidity;
		*dp++ = src->isOpen;
		*dp++ = src->isFanOn;
		*dp++ = src->isHeaterOn;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

ssize_t I2XTrafficSafetyDeviceLinkUnitStatus_write(Dz1Stream* dst, I2XTrafficSafetyDeviceLinkUnitStatus* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[8] = { 0, };
		if (I2XTrafficSafetyDeviceLinkUnitStatus_encode(data, sizeof(data), src, errp) == FALSE) ERR_OUT(errp);
		else DZ1_STREAM_WRITE(dst, data, sizeof(data), errp, ret);
	}
	return ret;
}

static bool_t I2XTrafficSafetyDeviceLinkUnitStatus_decode(I2XTrafficSafetyDeviceLinkUnitStatus* dst, u8_t* src, size_t sz, Dz1Error* errp)
{
	if (dst == NULL || src == NULL || sz < 8) ERR_SET_OUT(errp, EFAULT);
	else
	{
		u8_t* dp = src;
		dst->isActive = *dp++;
		dst->control_comm = *dp++;
		dst->wave_comm = *dp++;
		dst->temperature = *dp++;
		dst->humidity = *dp++;
		dst->isOpen = *dp++;
		dst->isFanOn = *dp++;
		dst->isHeaterOn = *dp++;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

ssize_t I2XTrafficSafetyDeviceLinkUnitStatus_read(I2XTrafficSafetyDeviceLinkUnitStatus* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[8] = { 0, };
		DZ1_STREAM_READ(data, sizeof(data), src, errp, ret);
		if (I2XTrafficSafetyDeviceLinkUnitStatus_decode(dst, data, sizeof(data), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}

// serial no
static bool_t I2XTrafficSafetyDeviceSerialNo_encode(u8_t* dst, size_t sz, I2XTrafficSafetyDeviceSerialNo* src, Dz1Error* errp)
{
	if (dst == NULL || sz < 5 || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u8_t* dp = dst;
		*dp = 0x00;
		*dp++ = src->type;
		*dp = 0x00;
		*dp++ = (u8_t)((src->id >> 24) & 0xFF);
		*dp++ = (u8_t)((src->id >> 16) & 0xFF);
		*dp++ = (u8_t)((src->id >> 8) & 0xFF);
		*dp++ = (u8_t)((src->id >> 0) & 0xFF);
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

ssize_t I2XTrafficSafetyDeviceSerialNo_write(Dz1Stream* dst, I2XTrafficSafetyDeviceSerialNo* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[5] = { 0, };
		if (I2XTrafficSafetyDeviceSerialNo_encode(data, sizeof(data), src, errp) == FALSE) ERR_OUT(errp);
		else DZ1_STREAM_WRITE(dst, data, sizeof(data), errp, ret);

		return ret;
	}
}

static bool_t I2XTrafficSafetyDeviceSerialNo_decode(I2XTrafficSafetyDeviceSerialNo* dst, u8_t* src, size_t sz, Dz1Error* errp)
{
	if (dst == NULL || src == NULL || sz < 5) ERR_SET_OUT(errp, EFAULT);
	else
	{
		u8_t* dp = src;
		dst->type = *dp++;
		dst->id = 0;
		dst->id = (dst->id << 8) | (u32_t)(*dp & 0xFF); dp++;
		dst->id = (dst->id << 8) | (u32_t)(*dp & 0xFF); dp++;
		dst->id = (dst->id << 8) | (u32_t)(*dp & 0xFF); dp++;
		dst->id = (dst->id << 8) | (u32_t)(*dp & 0xFF); dp++;
	}
	return ERR_IS_SUCCESS(errp);
}

ssize_t I2XTrafficSafetyDeviceSerialNo_read(I2XTrafficSafetyDeviceSerialNo* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	ssize_t ret = 0;

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[5] = { 0, };
		DZ1_STREAM_READ(data, sizeof(data), src, err, ret);
		if (I2XTrafficSafetyDeviceSerialNo_decode(dst, data, sizeof(data), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}

	return ret;
}

static ssize_t I2XTrafficSafetyDeviceSerialNoList_write(Dz1Stream* dst, I2XTrafficSafetyDeviceSerialNoList* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		I2XTrafficSafetyDeviceSerialNoList* list = NULL;
		int cnt = 0;
		if ((list = I2XTrafficSafetyDeviceSerialNoList_clone(src, errp)) == NULL) ERR_OUT(errp);
		else
		{
			I2XTrafficSafetyDeviceSerialNo* entry = NULL;
			pthread_cleanup_push(I2XTrafficSafetyDeviceSerialNoList_delAndSetNull, (void*)&list);

			while ((entry = list->getHead(list)) != NULL && errp->code == 0)
			{
				list->extract(list, entry);
				DZ1_IO_STREAM_FUNC(ret, I2XTrafficSafetyDeviceSerialNo_write(dst, entry, ed, param, errp), errp);
			}

			pthread_cleanup_pop(1); //(I2XTrafficSafetyDeviceSerialNoList_delAndSetNull, (void*)&list);
		}
	}

	return ret;
}


// I2XTrafficSafetyDeviceStatusInfo
static bool_t I2XTrafficSafetyDeviceStatus_encode(u8_t* dst, size_t sz, I2XTrafficSafetyDeviceStatus* src, Dz1Error* errp)
{
	if (dst == NULL || sz < 7 || src == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		u8_t* dp = dst;

		if (I2XTrafficSafetyDeviceSerialNo_encode(dst, 5, src->id, errp) == FALSE) ERR_OUT(errp);
		else
		{
			dp += 5;
			*dp = 0x00;
			*dp |= src->isActive ? 0x80 : 0x00;
			*dp |= src->isBatteryOn ? 0x40 : 0x00;
			*dp |= src->isPowered ? 0x20 : 0x00;
			*dp |= src->isPowerOn ? 0x10 : 0x00;
			*dp |= src->isConnected ? 0x08 : 0x00;
			dp++;

			*dp = src->cnt;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static ssize_t I2XTrafficSafetyDeviceStatus_write(Dz1Stream* dst, I2XTrafficSafetyDeviceStatus* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[7] = { 0, };
		if (I2XTrafficSafetyDeviceStatus_encode(data, sizeof(data), src, errp) == FALSE) ERR_OUT(errp);
		else DZ1_STREAM_WRITE(dst, data, sizeof(data), errp, ret);
	}

	return ret;
}

static bool_t I2XTrafficSafetyDeviceStatus_decode(I2XTrafficSafetyDeviceStatus* dst, u8_t* src, size_t sz, Dz1Error* errp)
{
	if (dst == NULL || src == NULL || sz < 7) ERR_SET_OUT(errp, EFAULT);
	else
	{
		u8_t* dp = src;

		if ((dst->id = I2XTrafficSafetyDeviceSerialNo_gen(errp)) == NULL) ERR_OUT(errp);
		else if (I2XTrafficSafetyDeviceSerialNo_decode(dst->id, dp, 5, errp) == FALSE) ERR_OUT(errp);
		else
		{
			dp += 5;

			dst->isActive = *dp & 0x80 ? TRUE : FALSE;
			dst->isBatteryOn = *dp & 0x40 ? TRUE : FALSE;
			dst->isPowered = *dp & 0x20 ? TRUE : FALSE;
			dst->isPowerOn = *dp & 0x10 ? TRUE : FALSE;
			dst->isConnected = *dp & 0x08 ? TRUE : FALSE;
			dp++;
			dst->cnt = *dp++;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

ssize_t I2XTrafficSafetyDeviceStatus_read(I2XTrafficSafetyDeviceStatus* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[7] = { 0, };
		DZ1_STREAM_READ(data, sizeof(data), src, errp, ret);
		if (I2XTrafficSafetyDeviceStatus_decode(dst, data, sizeof(data), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}

ssize_t I2XTrafficSafetyDeviceStatusList_write(Dz1Stream* dst, I2XTrafficSafetyDeviceStatusList* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		I2XTrafficSafetyDeviceStatusList* list = NULL;
		int cnt = 0;
		if ((list = I2XTrafficSafetyDeviceStatusList_clone(src, errp)) == NULL) ERR_OUT(errp);
		else
		{
			I2XTrafficSafetyDeviceStatus* entry = NULL;
			pthread_cleanup_push(I2XTrafficSafetyDeviceStatusList_delAndSetNull, (void*)&list);

			while ((entry = list->getHead(list)) != NULL && errp->code == 0)
			{
				list->extract(list, entry);
				DZ1_IO_STREAM_FUNC(ret, I2XTrafficSafetyDeviceStatus_write(dst, entry, ed, param, errp), errp);
			}

			pthread_cleanup_pop(1); //(I2XTrafficSafetyDeviceStatusList_delAndSetNull, (void*)&list);
		}
	}

	return ret;
}

ssize_t I2XTrafficSafetyDeviceStatusInfo_write(Dz1Stream* dst, I2XTrafficSafetyDeviceStatusInfo* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_STREAM_WRITE2(dst, (u16_t)(src->num & 0xFF), ed, errp, ret);
		DZ1_IO_STREAM_FUNC(ret, I2XTrafficSafetyDeviceStatusList_write(dst, src->status, ed, param, errp), errp);
	}
	return ret;
}

ssize_t I2XTrafficSafetyDeviceStatusInfo_read(I2XTrafficSafetyDeviceStatusInfo* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_STREAM_READ2(&dst->num, src, ed, errp, ret);

		if ((dst->status = I2XTrafficSafetyDeviceStatusList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			for (int i = 0; i < dst->num; i++)
			{
				I2XTrafficSafetyDeviceStatus* entry = NULL;
				if ((entry = I2XTrafficSafetyDeviceStatus_gen(errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(I2XTrafficSafetyDeviceStatus_delAndSetNull, (void*)&entry);
					DZ1_IO_STREAM_FUNC(ret, I2XTrafficSafetyDeviceStatus_read(entry, src, ed, param, errp), errp);
					if ((*errp = dst->status->add(dst->status, entry)).code) ERR_OUT(errp);
					else
					{
						entry = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); //(I2XTrafficSafetyDeviceStatus_delAndSetNull, (void*)&entry);
				}
			}
		}



		// ret 확인 및 reserved packet 확인
	}
	return ret;
}

// I2XTrafficSafetyDeviceList codec

ssize_t I2XTrafficSafetyDeviceList_write(Dz1Stream* dst, I2XTrafficSafetyDeviceList* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_STREAM_WRITE2(dst, (u16_t)(src->cnt & 0xFF), ed, errp, ret);
		DZ1_IO_STREAM_FUNC(ret, I2XTrafficSafetyDeviceSerialNoList_write(dst, src->id, ed, param, errp), errp);

	}
	return ret;
}

// data codec
ssize_t ITSK00144_2Data_write(Dz1Stream* dst, ITSK00144_2Data* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		switch (src->present)
		{
		case ITSK00144_2DataPresent_req_link_unit_status:
		case ITSK00144_2DataPresent_req_status:
		case ITSK00144_2DataPresent_req_list:
		case ITSK00144_2DataPresent_reset:
		case ITSK00144_2DataPresent_ack:
		case ITSK00144_2DataPresent_nack:
			break;
		case ITSK00144_2DataPresent_req_update_list:
			DZ1_IO_STREAM_FUNC(ret, I2XTrafficSafetyDeviceList_write(dst, src->x.rsp_list, ed, param, errp), errp);
			break;
		case ITSK00144_2DataPresent_rsp_link_unit_status:
			DZ1_IO_STREAM_FUNC(ret, I2XTrafficSafetyDeviceLinkUnitStatus_write(dst, src->x.rsp_link_unit_status, ed, param, errp), errp);
			break;
		case ITSK00144_2DataPresent_rsp_status:
			DZ1_IO_STREAM_FUNC(ret, I2XTrafficSafetyDeviceStatusInfo_write(dst, src->x.rsp_status, ed, param, errp), errp);
			break;
		case ITSK00144_2DataPresent_rsp_list:
			DZ1_IO_STREAM_FUNC(ret, I2XTrafficSafetyDeviceList_write(dst, src->x.rsp_list, ed, param, errp), errp);
			break;
		case ITSK00144_2DataPresent_rsp_update_list:
			DZ1_IO_STREAM_FUNC(ret, I2XTrafficSafetyDeviceList_write(dst, src->x.rsp_list, ed, param, errp), errp);
			break;
		default: ERR_SET_OUT(errp, EFAULT);
			break;
		}
	}
	return ret;
}

Dz1Binary* ITSK00144_2Data_encode(ITSK00144_2Data* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1Binary_new(DZ1_BIN_DATA_ALLOC, 512, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Stream* st = NULL;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&ret);
		if ((st = Dz1Stream_openStaticBuf(ret->data, ret->size, TRUE, 0, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ssize_t sz = 0;
			pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void*)&st);
			if ((sz = ITSK00144_2Data_write(st, src, ed, param, errp)) < 0)  ERR_OUT(errp);
			else
			{


				ret->size = ((u32_t)sz & 0xFFFF);
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); //(Dz1Stream_closeAndSetNull, (void*)&st);
		}
		pthread_cleanup_pop(errp->code); // (Dz1Binary_delAndSetNull, (void*)&ret);
	}
	return ret;
}
// crc
static unsigned int crc16(const void* buf, int len)
{
	int i, n;
	unsigned int crc = 0x0000;
	unsigned int c;
	for (i = 0; i < len; i++)
	{
		c = *((unsigned char*)buf)++;
		for (n = 0; n < 8;n++) {
			if ((c ^ crc) & 0x0001)
				crc = (crc >> 1) ^ 0xa001;
			else
				crc >>= 1;
			crc >>= 1;
		}

	}
	return crc;
}

ssize_t ITSK00144_2ProtocolFrameContext_write(Dz1Stream* dst, ITSK00144_2ProtocolFrameContext* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		// ID write
		DZ1_IO_STREAM_FUNC(ret, I2XTrafficSafetyDeviceSerialNo_write(dst, src->id, ed, param, errp), errp);
		DZ1_STREAM_WRITE1(dst, src->seq, errp, ret);
		DZ1_STREAM_WRITE1(dst, src->opcode, errp, ret);
		if (src->data == NULL)
		{
			DZ1_STREAM_WRITE1(dst, 0xFF, errp, ret);
			DZ1_STREAM_WRITE1(dst, 0xFF, errp, ret);
			DZ1_STREAM_WRITE1(dst, 0xFF, errp, ret);
			DZ1_STREAM_WRITE1(dst, 0xFF, errp, ret);
			DZ1_STREAM_WRITE1(dst, 0xFF, errp, ret);
			DZ1_STREAM_WRITE1(dst, 0xFF, errp, ret);
			DZ1_STREAM_WRITE1(dst, 0xFF, errp, ret);
			DZ1_STREAM_WRITE1(dst, 0xFF, errp, ret);
			DZ1_STREAM_WRITE1(dst, 0xFF, errp, ret);
			Dz1Error_set(errp, 0);
		}
		else
		{
			DZ1_IO_STREAM_FUNC(ret, ITSK00144_2Data_write(dst, src->data, ed, NULL, errp), errp);

			int sz_reserved = 0;
			sz_reserved = 16 - (ret % 16); // reserved packet으로 채워야할 개수 
			for (int i = 0; i < sz_reserved; i++)
			{
				DZ1_STREAM_WRITE1(dst, 0xFF, errp, ret);
			}
			Dz1Error_set(errp, 0);
		}
	}
	return ret;
}

Dz1Binary* ITSK00144_2ProtocolFrameContext_encode(ITSK00144_2ProtocolFrameContext* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary* ret = NULL;
	Dz1ElasticBuf* elb = NULL;
	if ((elb = Dz1ElasticBuf_new(512, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Stream* st = NULL;
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void*)&elb);
		if ((st = Dz1Stream_openRefElasticBuf(elb, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ssize_t sz = 0;
			pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void*)&st);
			if ((sz = ITSK00144_2ProtocolFrameContext_write(st, src, Dz1IOStreamEndian_big, NULL, errp)) < 0) ERR_OUT(errp);
			else if ((ret = Dz1ElasticBuf_flattenAndPurge(elb, errp)) == NULL) ERR_OUT(errp);
			else
			{
				ret->size = ((u32_t)sz & 0xFFFF);
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1Stream_closeAndSetNull, (void*)&st);
		}
		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void*)&elb);
	}
	return ret;
}

ssize_t ITSK00144_2ProtocolFrameContext_read(ITSK00144_2ProtocolFrameContext* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		if ((dst->id = I2XTrafficSafetyDeviceSerialNo_gen(errp)) == NULL) ERR_OUT(errp);
		else DZ1_IO_STREAM_FUNC(ret, I2XTrafficSafetyDeviceSerialNo_read(dst->id, src, ed, param, errp), errp);

		DZ1_STREAM_READ1(&dst->seq, src, errp, ret);

		DZ1_STREAM_READ1(&dst->opcode, src, errp, ret);

		switch (dst->opcode)
		{
		case ITSK00144_2DataPresent_req_link_unit_status:
		case ITSK00144_2DataPresent_req_status:
		case ITSK00144_2DataPresent_req_list:
		case ITSK00144_2DataPresent_reset:
		case ITSK00144_2DataPresent_ack:
		case ITSK00144_2DataPresent_nack:

			break;

		case ITSK00144_2DataPresent_rsp_link_unit_status:
			if ((dst->data = ITSK00144_2Data_new(ITSK00144_2DataPresent_rsp_link_unit_status, NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((dst->data->x.rsp_link_unit_status = I2XTrafficSafetyDeviceLinkUnitStatus_gen(errp)) == NULL) ERR_OUT(errp);
			else DZ1_IO_STREAM_FUNC(ret, I2XTrafficSafetyDeviceLinkUnitStatus_read(dst->data->x.rsp_link_unit_status, src, ed, param, errp), errp);
			break;
		case ITSK00144_2DataPresent_rsp_status:
			if ((dst->data = ITSK00144_2Data_new(ITSK00144_2DataPresent_rsp_status, NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((dst->data->x.rsp_status = I2XTrafficSafetyDeviceStatusInfo_gen(errp)) == NULL) ERR_OUT(errp);
			else DZ1_IO_STREAM_FUNC(ret, I2XTrafficSafetyDeviceStatusInfo_read(dst->data->x.rsp_status, src, ed, param, errp), errp);
			break;
		}

	}

	return ret;
}


ITSK00144_2ProtocolFrameContext* ITSK00144_2ProtocolFrameContext_decode(Dz1Binary* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ITSK00144_2ProtocolFrameContext* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = ITSK00144_2ProtocolFrameContext_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Stream* st = NULL;
		pthread_cleanup_push(ITSK00144_2ProtocolFrameContext_delAndSetNull, (void*)&ret);
		if ((st = Dz1Stream_openStaticBuf(src->data, src->size, TRUE, src->size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ssize_t sz = 0;
			pthread_cleanup_push(Dz1Stream_delAndSetNull, (void*)&st);
			if ((sz = ITSK00144_2ProtocolFrameContext_read(ret, st, ed, param, errp)) < 0) ERR_OUT(errp);		// tbd
			// else if (sz != (ssize_t)src->size) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); //(Dz1Stream_delAndSetNull, (void*)&st);
		}
		pthread_cleanup_pop(errp->code); // (ITSK00144_2ProtocolFrameContext_delAndSetNull, (void*)&ret);
	}
	return ret;
}


// convert
ITSK00144_2ProtocolFrame* ITSK00144_2ProtocolFrame_fromITSK00144_2Reserved0(I2XTrafficSafetyDeviceSerialNo* id, u8_t seq, ITSK00144_2DataPresent present, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ITSK00144_2ProtocolFrame* ret = NULL;
	if ((ret = ITSK00144_2ProtocolFrame_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		ITSK00144_2ProtocolFrameContext* context = NULL;

		if ((context = ITSK00144_2ProtocolFrameContext_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(ITSK00144_2ProtocolFrameContext_delAndSetNull, (void*)&context);
			if ((context->id = I2XTrafficSafetyDeviceSerialNo_clone(id, errp)) == NULL) ERR_OUT(errp);
			else
			{
				context->opcode = present;
				context->seq = seq;
				if ((ret->context = ITSK00144_2ProtocolFrameContext_encode(context, ed, param, errp)) == NULL) ERR_OUT(errp);
				else
				{
					ret->length = 16;
					ret->crc = crc16(ret->context->data, 16);
					Dz1Error_set(errp, 0);
				}
			}
			pthread_cleanup_pop(1); // (ITSK00144_2ProtocolFrameContext_delAndSetNull, (void*)&context);
		}
	}
	return ret;
}

ITSK00144_2ProtocolFrame* ITSK00144_2ProtocolFrame_fromITSK00144_2Data(I2XTrafficSafetyDeviceSerialNo* id, u8_t seq, ITSK00144_2Data* data, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ITSK00144_2ProtocolFrame* ret = NULL;
	if ((ret = ITSK00144_2ProtocolFrame_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		ITSK00144_2ProtocolFrameContext* context = NULL;

		if ((context = ITSK00144_2ProtocolFrameContext_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(ITSK00144_2ProtocolFrameContext_delAndSetNull, (void*)&context);
			if ((context->id = I2XTrafficSafetyDeviceSerialNo_clone(id, errp)) == NULL) ERR_OUT(errp);
			else if ((context->data = ITSK00144_2Data_clone(data, errp)) == NULL) ERR_OUT(errp);
			else
			{
				context->opcode = data->present;
				context->seq = seq;

				Dz1Binary* data = NULL;
				Dz1ElasticBuf* elb = NULL;
				if ((elb = Dz1ElasticBuf_new(512, FALSE, errp)) == NULL) ERR_OUT(errp);
				else
				{
					Dz1Stream* st = NULL;
					pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void*)&elb);
					if ((st = Dz1Stream_openRefElasticBuf(elb, errp)) == NULL) ERR_OUT(errp);
					else
					{
						ssize_t sz = 0;
						pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void*)&st);
						if ((sz = ITSK00144_2ProtocolFrameContext_write(st, context, Dz1IOStreamEndian_big, NULL, errp)) < 0) ERR_OUT(errp);
						else if ((ret->context = data = Dz1ElasticBuf_flattenAndPurge(elb, errp)) == NULL) ERR_OUT(errp);
						else
						{
							ret->crc = crc16(data->data, (int)sz);
							ret->length = (u16_t)sz;
							Dz1Error_set(errp, 0);
						}
						pthread_cleanup_pop(1); // (Dz1Stream_closeAndSetNull, (void*)&st);
					}
					pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void*)&elb);
				}
			}
			pthread_cleanup_pop(1); // (ITSK00144_2ProtocolFrameContext_delAndSetNull, (void*)&context);
		}
	}
	return ret;
}


// frame codec
ssize_t ITSK00144_2ProtocolFrame_write(Dz1Stream* dst, ITSK00144_2ProtocolFrame* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		// header
		DZ1_STREAM_WRITE1(dst, 0x7E, errp, ret);
		DZ1_STREAM_WRITE1(dst, 0xE7, errp, ret);
		// length
		DZ1_STREAM_WRITE2(dst, src->length, ed, errp, ret);
		// context : id / seq / opcode / data
		DZ1_STREAM_WRITE(dst, src->context->data, src->context->size, errp, ret);
		// crc
		DZ1_STREAM_WRITE2(dst, src->crc, ed, errp, ret);
		// tail
		DZ1_STREAM_WRITE1(dst, 0xE7, errp, ret);
		DZ1_STREAM_WRITE1(dst, 0x7E, errp, ret);
	}
	return ret;
}


Dz1Binary* ITSK00144_2ProtocolFrame_encode(ITSK00144_2ProtocolFrame* src, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary* ret = NULL;
	Dz1ElasticBuf* elb = NULL;
	if ((elb = Dz1ElasticBuf_new(512, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Stream* st = NULL;
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void*)&elb);
		if ((st = Dz1Stream_openRefElasticBuf(elb, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ssize_t sz = 0;
			pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void*)&st);
			if ((sz = ITSK00144_2ProtocolFrame_write(st, src, Dz1IOStreamEndian_big, NULL, errp)) < 0) ERR_OUT(errp);
			else if ((ret = Dz1ElasticBuf_flattenAndPurge(elb, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Stream_closeAndSetNull, (void*)&st);
		}
		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void*)&elb);
	}
	return ret;
}

ssize_t ITSK00144_2ProtocolFrame_read(ITSK00144_2ProtocolFrame* dst, Dz1Stream* src, u32_t src_size, Dz1IOStreamEndian ed, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t stx = 0;
		Dz1Binary* ctx = NULL;
		DZ1_STREAM_READ1(&stx, src, errp, ret);
		if (stx != 0x7E) ERR_SET_OUT_RET(errp, EFAULT, -1);

		DZ1_STREAM_READ1(&stx, src, errp, ret);
		if (stx != 0xE7) ERR_SET_OUT_RET(errp, EFAULT, -1);

		// legnth 
		DZ1_STREAM_READ2(&dst->length, src, ed, errp, ret);
		// context

		if ((dst->context = ctx = Dz1Binary_new(DZ1_BIN_DATA_ALLOC, (u32_t)dst->length, errp)) == NULL) ERR_OUT(errp);
		else
		{
			DZ1_STREAM_READ(ctx->data, ctx->size, src, errp, ret);
			Dz1Binary_dump(ctx, 0);
		}
		// crc
		DZ1_STREAM_READ2(&dst->crc, src, ed, errp, ret);

		//  tail
		DZ1_STREAM_READ1(&stx, src, errp, ret);
		if (stx != 0xE7) ERR_SET_OUT_RET(errp, EFAULT, -1);

		DZ1_STREAM_READ1(&stx, src, errp, ret);
		if (stx != 0x7E) ERR_SET_OUT_RET(errp, EFAULT, -1);
	}
	return ret;
}

ITSK00144_2ProtocolFrame* ITSK00144_2ProtocolFrame_decode(Dz1Binary* src, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ITSK00144_2ProtocolFrame* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = ITSK00144_2ProtocolFrame_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Stream* st = NULL;
		pthread_cleanup_push(ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&ret);
		if ((st = Dz1Stream_openStaticBuf(src->data, src->size, TRUE, src->size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ssize_t sz = 0;
			pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void*)&st); // delaNdSetNull 차이?
			if ((sz = ITSK00144_2ProtocolFrame_read(ret, st, src->size, Dz1IOStreamEndian_big, errp)) < 0) ERR_OUT(errp);
			else
			{
				// crc 체크
				u16_t crc = 0;
				if ((crc = crc16(ret->context->data, (int)ret->length)) != ret->crc) ERR_SET_OUT(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1Stream_closeAndSetNull, (void*)&st);
		}
		pthread_cleanup_pop(errp->code); // (ITSK00144_2ProtocolFrame_delAndSetNull, (void*)&ret);
	}
	return ret;
}



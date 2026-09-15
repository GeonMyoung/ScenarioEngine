#include <TrafficSignalControllerTestMsgFrame.h>

#include "TrafficSignalControllerTestMsg.h"


static ssize_t TrafficSignalControllerTestMsgFrame_status_response_write(Dz1Stream* dst, TrafficSignalControllerTestMsgFrame_status_response* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, CrossStatusBasicInfo_write(dst, src->lc_status, ed, param, errp), errp);
		if (src->ex_status != NULL) DZ1_IO_STREAM_FUNC(ret, CrossStatusExtInfo_r27_write(dst, src->ex_status, ed, param, errp), errp);
	}
	return ret;
}

static ssize_t TrafficSignalControllerTestMsgFrame_status_response_read(TrafficSignalControllerTestMsgFrame_status_response* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		if ((dst->lc_status = CrossStatusBasicInfo_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
		else DZ1_IO_STREAM_FUNC(ret, CrossStatusBasicInfo_read(dst->lc_status, src, ed, param, errp), errp);

		if (Dz1Stream_eof(src) == FALSE)
		{
			if ((dst->ex_status = CrossStatusExtInfo_r27_gen(errp)) == NULL) ERR_OUT(errp);
			else DZ1_IO_STREAM_FUNC(ret, CrossStatusExtInfo_r27_read(dst->ex_status, src, ed, param, errp), errp);
		}
	}
	return ret;
}

static ssize_t TrafficSignalControllerTestMsgFrame_detector_info_read(DetectorInfo* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EFAULT, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, DetectorInfo_read(dst, src, ed, param, errp), errp);
	}
	return ret;
}

static ssize_t TrafficSignalControllerTestMsgFrameContext_signal_phase_download_req_read(SignalPhaseInfoDown_r27* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, SignalPhaseInfoDown_r27_read(dst, src, ed, param, errp), errp);
	}
	return ret;
}

static ssize_t TrafficSignalControllerTestMsgFrameContext_signal_phase_upload_rsp_read(SignalPhaseInfoUp* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, SignalPhaseInfoUp_read(dst, src, ed, param, errp), errp);
	}
	return ret;
}

static ssize_t TrafficSignalControllerTestMsgFrameContext_clock_upload_rsp_read(ClockInfo* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, ClockInfo_read(dst, src, ed, param, errp), errp);
	}
	return ret;
}

static ssize_t TrafficSignalControllerTestMsgFrameContext_special_command_req_read(SpecialCommandInfo* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, SpecialCommandInfo_read(dst, src, ed, param, errp), errp);
	}
	return ret;

}

static ssize_t TrafficSignalControllerTestMsgFrameContext_special_command_rsp_read(SpecialCommandPPCNumberList* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, SpecialCommandPPCNumberList_read(dst, src, ed, param, errp), errp);
	}
	return ret;
}

static ssize_t TrafficSignalControllerTestMsgFrameContext_fw_upgrade_req_read(FirmwareUpgradeData* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, FirmwareUpgradeData_read(dst, src, ed, param, errp), errp);
	}
	return ret;
}

static ssize_t TrafficSignalControllerTestMsgFrameContext_fw_upgrade_rsp_read(FirmwareUpgradeError* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, FirmwareUpgradeError_read(dst, src, ed, param, errp), errp);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerTestMsgFrameContext CODEC
ssize_t TrafficSignalControllerTestMsgFrameContext_write(Dz1Stream *dst, TrafficSignalControllerTestMsgFrameContext *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_STREAM_WRITE1(dst, (u8_t)(src->present & 0xFF), errp, ret); // opcode
		switch (src->present)
		{
		case TrafficSignalControllerTestMsgFrameContextPresent_control_req:
			DZ1_IO_STREAM_FUNC(ret, CrossControlCmd_write(dst, src->x.control_req, ed, param, errp), errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_control_rsp:
			break;

		case TrafficSignalControllerTestMsgFrameContextPresent_status_req:
			// void
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_status_rsp:
			DZ1_IO_STREAM_FUNC(ret, TrafficSignalControllerTestMsgFrame_status_response_write(dst, src->x.status_rsp, ed, param, errp), errp);
			break;

		case TrafficSignalControllerTestMsgFrameContextPresent_detector_req:
			// void
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_detector_rsp:
			DZ1_IO_STREAM_FUNC(ret, DetectorInfo_write(dst, src->x.detector_rsp, ed, param, errp), errp);
			break;

		case TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_download_req:
			DZ1_IO_STREAM_FUNC(ret, SignalPhaseInfoDown_r27_write(dst, src->x.signal_phase_download_req, ed, param, errp), errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_download_rsp:
			break;

		case TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_upload_req:
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_upload_rsp:
			DZ1_IO_STREAM_FUNC(ret, SignalPhaseInfoUp_write(dst, src->x.signal_phase_upload_rsp, ed, param, errp), errp);
			break;

		case TrafficSignalControllerTestMsgFrameContextPresent_clock_download_req:
			DZ1_IO_STREAM_FUNC(ret, ClockInfo_write(dst, src->x.clock_download_req, ed, param, errp), errp);
		case TrafficSignalControllerTestMsgFrameContextPresent_clock_download_rsp:
			break;

		case TrafficSignalControllerTestMsgFrameContextPresent_clock_upload_req:
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_clock_upload_rsp:
			DZ1_IO_STREAM_FUNC(ret, ClockInfo_write(dst, src->x.clock_upload_rsp, ed, param, errp), errp);
			break;

		case TrafficSignalControllerTestMsgFrameContextPresent_special_command_req:
			DZ1_IO_STREAM_FUNC(ret, SpecialCommandInfo_write(dst, src->x.special_command_req, ed, param, errp), errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_special_command_rsp:
			DZ1_IO_STREAM_FUNC(ret, SpecialCommandPPCNumberList_write(dst, src->x.special_command_rsp, ed, param, errp), errp);
			break;

		case TrafficSignalControllerTestMsgFrameContextPresent_fw_upgrade_req:
			DZ1_IO_STREAM_FUNC(ret, FirmwareUpgradeData_write(dst, src->x.fw_upgrade_req, ed, param, errp), errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_fw_upgrade_rsp:
			DZ1_IO_STREAM_FUNC(ret, FirmwareUpgradeError_write(dst, src->x.fw_upgrade_rsp, ed, param, errp), errp);
			break;

		default:
			ERR_SET_OUT(errp, EFAULT);
			break;
		}
	}
	return ret;
}

ssize_t TrafficSignalControllerTestMsgFrameContext_read(TrafficSignalControllerTestMsgFrameContext* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t v8;
		DZ1_STREAM_READ1(&v8, src, errp, ret);									// ¾Æ¸¶ opcode
		dst->present = (TrafficSignalControllerTestMsgFrameContextPresent)v8;
		switch (dst->present)
		{
		case TrafficSignalControllerTestMsgFrameContextPresent_control_req:
			if ((dst->x.control_req = CrossControlCmd_gen(errp)) == NULL) ERR_OUT(errp);
			else DZ1_IO_STREAM_FUNC(ret, CrossControlCmd_read(dst->x.control_req, src, ed, param, errp), errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_control_rsp:
			break;

		case TrafficSignalControllerTestMsgFrameContextPresent_status_req:
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_status_rsp:
			if ((dst->x.status_rsp = TrafficSignalControllerTestMsgFrame_status_response_gen(errp)) == NULL) ERR_OUT(errp);
			else DZ1_IO_STREAM_FUNC(ret, TrafficSignalControllerTestMsgFrame_status_response_read(dst->x.status_rsp, src, ed, param, errp), errp);
			break;

		case TrafficSignalControllerTestMsgFrameContextPresent_detector_req:
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_detector_rsp:
			if ((dst->x.detector_rsp = DetectorInfo_gen(errp)) == NULL) ERR_OUT(errp);
			else DZ1_IO_STREAM_FUNC(ret, TrafficSignalControllerTestMsgFrame_detector_info_read(dst->x.detector_rsp, src, ed, param, errp), errp);
			break;

		case TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_download_req:
			if ((dst->x.signal_phase_download_req = SignalPhaseInfoDown_r27_gen(errp)) == NULL) ERR_OUT(errp);
			else DZ1_IO_STREAM_FUNC(ret, TrafficSignalControllerTestMsgFrameContext_signal_phase_download_req_read(dst->x.signal_phase_download_req, src, ed, param, errp), errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_download_rsp:
			break;

		case TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_upload_req:
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_upload_rsp:
			if ((dst->x.signal_phase_upload_rsp = SignalPhaseInfoUp_gen(errp)) == NULL) ERR_OUT(errp);
			else DZ1_IO_STREAM_FUNC(ret, TrafficSignalControllerTestMsgFrameContext_signal_phase_upload_rsp_read(dst->x.signal_phase_upload_rsp, src, ed, param, errp), errp);
			break;

		case TrafficSignalControllerTestMsgFrameContextPresent_clock_download_req:
			if ((dst->x.clock_download_req = ClockInfo_gen(errp)) == NULL) ERR_OUT(errp);
			else DZ1_IO_STREAM_FUNC(ret, ClockInfo_read(dst->x.clock_download_req, src, ed, param, errp), errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_clock_download_rsp:
			break;

		case TrafficSignalControllerTestMsgFrameContextPresent_clock_upload_req:
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_clock_upload_rsp:
			if ((dst->x.clock_upload_rsp = ClockInfo_gen(errp)) == NULL) ERR_OUT(errp);
			else DZ1_IO_STREAM_FUNC(ret, TrafficSignalControllerTestMsgFrameContext_clock_upload_rsp_read(dst->x.clock_upload_rsp, src, ed, param, errp), errp);
			break;

		case TrafficSignalControllerTestMsgFrameContextPresent_special_command_req:
			if ((dst->x.special_command_req = SpecialCommandInfo_gen(errp)) == NULL) ERR_OUT(errp);
			else DZ1_IO_STREAM_FUNC(ret, TrafficSignalControllerTestMsgFrameContext_special_command_req_read(dst->x.special_command_req, src, ed, param, errp), errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_special_command_rsp:
			if ((dst->x.special_command_rsp = SpecialCommandPPCNumberList_gen(errp)) == NULL) ERR_OUT(errp);
			else DZ1_IO_STREAM_FUNC(ret, TrafficSignalControllerTestMsgFrameContext_special_command_rsp_read(dst->x.special_command_rsp, src, ed, param, errp), errp);
			break;

		case TrafficSignalControllerTestMsgFrameContextPresent_fw_upgrade_req:
			if ((dst->x.fw_upgrade_req = FirmwareUpgradeData_gen(errp)) == NULL) ERR_OUT(errp);
			else DZ1_IO_STREAM_FUNC(ret, TrafficSignalControllerTestMsgFrameContext_fw_upgrade_req_read(dst->x.fw_upgrade_req, src, ed, param, errp), errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_fw_upgrade_rsp:
			if ((dst->x.fw_upgrade_rsp = FirmwareUpgradeError_gen(errp)) == NULL) ERR_OUT(errp);
			else DZ1_IO_STREAM_FUNC(ret, TrafficSignalControllerTestMsgFrameContext_fw_upgrade_rsp_read(dst->x.fw_upgrade_rsp, src, ed, param, errp), err);
			break;
		default: ERR_SET_OUT(errp, EFAULT); break;
		}
	}
	return ret;
}


Dz1Binary* TrafficSignalControllerTestMsgFrameContext_encode(TrafficSignalControllerTestMsgFrameContext* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1Binary_new(DZ1_BIN_DATA_ALLOC, 255, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Stream* st = NULL;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&ret);
		if ((st = Dz1Stream_openStaticBuf(ret->data, ret->size, TRUE, 0, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ssize_t sz = 0;
			pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void*)&st);
			if ((sz = TrafficSignalControllerTestMsgFrameContext_write(st, src, ed, param, errp)) < 0) ERR_OUT(errp);
			else
			{
				ret->size = ((u32_t)sz & 0xFFFF);
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1Stream_closeAndSetNull, (void*)&st);
		}
		pthread_cleanup_pop(errp->code);// (Dz1Binary_delAndSetNull, (void*)&ret);
	}
	return ret;
}

TrafficSignalControllerTestMsgFrameContext* TrafficSignalControllerTestMsgFrameContext_decode(Dz1Binary* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TrafficSignalControllerTestMsgFrameContext* ret = NULL;
	if ((ret = TrafficSignalControllerTestMsgFrameContext_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TrafficSignalControllerTestMsgFrameContext_delAndSetNull, (void*)&ret);
		Dz1Stream* st = NULL;
		if ((st = Dz1Stream_openStaticBuf(src->data, src->size, TRUE, src->size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ssize_t sz = 0;
			pthread_cleanup_push(Dz1Stream_delAndSetNull, (void*)&st);
			if ((sz = TrafficSignalControllerTestMsgFrameContext_read(ret, st, ed, param, errp)) < 0) ERR_OUT(errp);
			else if (sz != (ssize_t)src->size) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Stream_delAndSetNull, (void*)&st);
		}
		pthread_cleanup_pop(errp->code); // (TrafficSignalControllerTestMsgFrameContext_delAndSetNull, (void*)&ret);
	}

	return ret;
}


// TrafficSignalControllerTestMsgFrameContext CODEC
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerTestMsgFrame CODEC
static u8_t _lrc_chunk(u8_t initial, u8_t* data, size_t size)
{
	u8_t ret = initial;
	while (size)
	{
		ret ^= *data++;
		size--;
	}
	return ret;
}

ssize_t TrafficSignalControllerTestMsgFrame_write(Dz1Stream* dst, TrafficSignalControllerTestMsgFrame* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	Dz1Binary* ctx = NULL;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if ((ctx = src->context) == NULL || ctx->data == NULL || ctx->size == 0) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t len = 3 + (u8_t)(ctx->size & 0xFF);
		u8_t LRC = 0;
		DZ1_STREAM_WRITE1(dst, 0x7E, errp, ret);
		DZ1_STREAM_WRITE1(dst, 0x7E, errp, ret);
		DZ1_STREAM_WRITE1(dst, len, errp, ret);					LRC ^= len;
		DZ1_STREAM_WRITE1(dst, src->cross_id, errp, ret);		LRC ^= src->cross_id;
		DZ1_STREAM_WRITE(dst, ctx->data, ctx->size, errp, ret); LRC = _lrc_chunk(LRC, ctx->data, ctx->size);
		DZ1_STREAM_WRITE1(dst, LRC, errp, ret);
	}
	return ret;
}

ssize_t TrafficSignalControllerTestMsgFrame_read(TrafficSignalControllerTestMsgFrame* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (dst->context != NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		Dz1Binary* ctx = NULL;
		u8_t len = 0, stx = 0;
		u8_t LRC = 0, lrc = 0;

		DZ1_STREAM_READ1(&stx, src, errp, ret);
		if (stx != 0x7E) ERR_SET_OUT_RET(errp, EFAULT, -1);

		DZ1_STREAM_READ1(&stx, src, errp, ret);
		if (stx != 0x7E) ERR_SET_OUT_RET(errp, EFAULT, -1);

		DZ1_STREAM_READ1(&len, src, errp, ret);					LRC ^= len;
		if (len < 4) ERR_SET_OUT_RET(errp, EFAULT, -1);

		DZ1_STREAM_READ1(&dst->cross_id, src, errp, ret);		LRC ^= dst->cross_id;

		if ((dst->context = ctx = Dz1Binary_new(DZ1_BIN_DATA_ALLOC, (u32_t)(len - 3), errp)) == NULL) ERR_OUT_RET(errp, -1);
		else
		{
			DZ1_STREAM_READ(ctx->data, ctx->size, src, errp, ret);
			LRC = _lrc_chunk(LRC, ctx->data, ctx->size);
		}
		DZ1_STREAM_READ1(&lrc, src, errp, ret);

		if (lrc != LRC) ERR_SET_OUT_RET(errp, EFAULT, -1);
	}
	return ret;
}


Dz1Binary* TrafficSignalControllerTestMsgFrame_encode(TrafficSignalControllerTestMsgFrame* src, Dz1Error* err)
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
			if ((sz = TrafficSignalControllerTestMsgFrame_write(st, src, Dz1IOStreamEndian_big, NULL, errp)) < 0) ERR_OUT(errp);
			else if ((ret = Dz1ElasticBuf_flattenAndPurge(elb, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Stream_closeAndSetNull, (void*)&st);
		}
		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void*)&elb);
	}
	return ret;
}
// TrafficSignalControllerTestMsgFrame CODEC
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
// Converters
TrafficSignalControllerTestMsgFrame* TrafficSignalControllerTestMsgFrame_fromCrossControlInformation(CrossControlInformation* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TrafficSignalControllerTestMsgFrame* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = TrafficSignalControllerTestMsgFrame_new(src->cross_id, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		TrafficSignalControllerTestMsgFrameContext* ctx = NULL;
		pthread_cleanup_push(TrafficSignalControllerTestMsgFrame_delAndSetNull, (void*)&ret);
		if ((ctx = TrafficSignalControllerTestMsgFrameContext_new(TrafficSignalControllerTestMsgFrameContextPresent_control_req, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(TrafficSignalControllerTestMsgFrameContext_delAndSetNull, (void*)&ctx);
			if ((ctx->x.control_req = CrossControlCmd_clone(src->command, errp)) == NULL) ERR_OUT(errp);
			else if ((ret->context = TrafficSignalControllerTestMsgFrameContext_encode(ctx, ed, param, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (TrafficSignalControllerTestMsgFrameContext_delAndSetNull, (void*)&ctx);
		}
		pthread_cleanup_pop(errp->code); // (TrafficSignalControllerTestMsgFrame_delAndSetNull, (void*)&ret);
	}

	return ret;
}

TrafficSignalControllerTestMsgFrame* TrafficSignalControllerTestMsgFrame_fromCrossIndicator(CrossIndicator* src, Dz1IOStreamEndian ed, TrafficSignalControllerRequestPresent present, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TrafficSignalControllerTestMsgFrame* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = TrafficSignalControllerTestMsgFrame_new(src->cross_id, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		TrafficSignalControllerTestMsgFrameContext* ctx = NULL;
		pthread_cleanup_push(TrafficSignalControllerTestMsgFrame_delAndSetNull, (void*)&ret);
		if ((ctx = TrafficSignalControllerTestMsgFrameContext_new((TrafficSignalControllerTestMsgFrameContextPresent)present, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(TrafficSignalControllerTestMsgFrameContext_delAndSetNull, (void*)&ctx);
			if ((ret->context = TrafficSignalControllerTestMsgFrameContext_encode(ctx, ed, param, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (TrafficSignalControllerTestMsgFrameContext_delAndSetNull, (void*)&ctx);
		}
		pthread_cleanup_pop(errp->code); // (TrafficSignalControllerTestMsgFrame_delAndSetNull, (void*)&ret);
	}
	return ret;
}

TrafficSignalControllerTestMsgFrame* TrafficSignalControllerTestMsgFrame_fromSignalPhaseInformationDownload(SignalPhaseInformationDownload* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TrafficSignalControllerTestMsgFrame* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = TrafficSignalControllerTestMsgFrame_new(src->cross_id, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		TrafficSignalControllerTestMsgFrameContext* ctx = NULL;
		pthread_cleanup_push(TrafficSignalControllerTestMsgFrame_delAndSetNull, (void*)&ret);
		if ((ctx = TrafficSignalControllerTestMsgFrameContext_new(TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_download_req, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(TrafficSignalControllerTestMsgFrameContext_delAndSetNull, (void*)&ctx);

			if ((ctx->x.signal_phase_download_req = SignalPhaseInfoDown_r27_clone(src->signal_phase_info_down, errp)) == NULL) ERR_OUT(errp);
			else if ((ret->context = TrafficSignalControllerTestMsgFrameContext_encode(ctx, ed, param, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (TrafficSignalControllerTestMsgFrameContext_delAndSetNull, (void*)&ctx);
		}
		pthread_cleanup_pop(errp->code); // (TrafficSignalControllerTestMsgFrame_delAndSetNull, (void*)&ret);
	}
	return ret;
}

TrafficSignalControllerTestMsgFrame* TrafficSignalControllerTestMsgFrame_fromClockInformationDownload(ClockInformationDownload* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TrafficSignalControllerTestMsgFrame* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = TrafficSignalControllerTestMsgFrame_new(src->cross_id, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		TrafficSignalControllerTestMsgFrameContext* ctx = NULL;
		pthread_cleanup_push(TrafficSignalControllerTestMsgFrame_delAndSetNull, (void*)&ret);
		if ((ctx = TrafficSignalControllerTestMsgFrameContext_new(TrafficSignalControllerTestMsgFrameContextPresent_clock_download_req, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(TrafficSignalControllerTestMsgFrameContext_delAndSetNull, (void*)&ctx);
			if ((ctx->x.clock_download_req = ClockInfo_clone(src->clock_info_down, errp)) == NULL) ERR_OUT(errp);
			else if ((ret->context = TrafficSignalControllerTestMsgFrameContext_encode(ctx, ed, param, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (TrafficSignalControllerTestMsgFrameContext_delAndSetNull, (void*)&ctx);
		}
		pthread_cleanup_pop(errp->code); // (TrafficSignalControllerTestMsgFrame_delAndSetNull, (void*)&ret);
	}
	return ret;
}

TrafficSignalControllerTestMsgFrame* TrafficSignalControllerTestMsgFrame_fromSpecialCommandInformation(SpecialCommandInformation* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TrafficSignalControllerTestMsgFrame* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = TrafficSignalControllerTestMsgFrame_new(src->cross_id, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TrafficSignalControllerTestMsgFrame_delAndSetNull, (void*)&ret);
		TrafficSignalControllerTestMsgFrameContext* ctx = NULL;
		if ((ctx = TrafficSignalControllerTestMsgFrameContext_new(TrafficSignalControllerTestMsgFrameContextPresent_special_command_req, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(TrafficSignalControllerTestMsgFrameContext_delAndSetNull, (void*)&ctx);

			if ((ctx->x.special_command_req = SpecialCommandInfo_clone(src->special_command, errp)) == NULL) ERR_OUT(errp);
			else if ((ret->context = TrafficSignalControllerTestMsgFrameContext_encode(ctx, ed, param, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (TrafficSignalControllerTestMsgFrameContext_delAndSetNull, (void*)&ctx);
		}
		pthread_cleanup_pop(errp->code); // (TrafficSignalControllerTestMsgFrame_delAndSetNull, (void*)&ret);

	}
	return ret;
}

TrafficSignalControllerTestMsgFrame* TrafficSignalControllerTestMsgFrame_fromFirmwareUpgradeCommand(FirmwareUpgradeCommand* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TrafficSignalControllerTestMsgFrame* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = TrafficSignalControllerTestMsgFrame_new(src->cross_id, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TrafficSignalControllerTestMsgFrame_delAndSetNull, (void*)&ret);
		TrafficSignalControllerTestMsgFrameContext* ctx = NULL;
		if ((ctx = TrafficSignalControllerTestMsgFrameContext_new(TrafficSignalControllerTestMsgFrameContextPresent_fw_upgrade_req, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(TrafficSignalControllerTestMsgFrameContext_delAndSetNull, (void*)&ctx);

			if ((ctx->x.fw_upgrade_req = FirmwareUpgradeData_clone(src->fw_upgrade_data, errp)) == NULL) ERR_OUT(errp);
			else if ((ret->context = TrafficSignalControllerTestMsgFrameContext_encode(ctx, ed, param, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (TrafficSignalControllerTestMsgFrameContext_delAndSetNull, (void*)&ctx);
		}
		pthread_cleanup_pop(errp->code); // (TrafficSignalControllerTestMsgFrame_delAndSetNull, (void*)&ret);

	}
	return ret;
}


// Converters
///////////////////////////////////////////////////////////////////////////////
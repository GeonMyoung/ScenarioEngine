#include <TrafficSignalControllerTestMsg.h>
#include <TrafficSignalControllerTestMsgFrame.h>

// implement library functions here



///////////////////////////////////////////////////////////////////////////////
// CrossControlCmd CODEC

static bool_t _cross_control_cmd_encode(u8_t* dst, size_t dst_sz, CrossControlCmd* src, Dz1Error* errp)
{
	if (dst == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		CrossControlSingleCmd* single = NULL;
		CrossControlDualCmd* dual = NULL;

		switch (src->present)
		{
		case CrossControlCmdPresent_single:
			if ((single = src->x.single) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				// 운영모드 | 제어모드 명령
				dst[0] = 0x00 | (u8_t)(single->present & 0x7F);
				switch (single->present)
				{
				case CrossControlSingleCmdPresent_lc_fixed:
					dst[1] = (u8_t)(single->x.lc_fixed & 0xF);
					Dz1Error_set(errp, 0);
					break;
				case CrossControlSingleCmdPresent_lc_control:
					dst[1] = (u8_t)(single->x.lc_control & 0xF);
					Dz1Error_set(errp, 0);
					break;
				case CrossControlSingleCmdPresent_lc_actuation:
					dst[1] = (u8_t)(single->x.lc_actuation & 0xF);
					Dz1Error_set(errp, 0);
					break;
				case CrossControlSingleCmdPresent_rc_actuation:
					dst[1] = (u8_t)(single->x.rc_actuation & 0xF);
					Dz1Error_set(errp, 0);
					break;
				case CrossControlSingleCmdPresent_rc_online:
					dst[1] = (u8_t)(single->x.rc_online & 0xF);
					Dz1Error_set(errp, 0);
					break;
				default:
					ERR_SET_OUT(errp, EFAULT); break;
				}
				dst[2] = 0;		// Reserved
				dst[3] = 0;		// Reserved
			}
			break;
		case CrossControlCmdPresent_dual:
			if ((dual = src->x.dual) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				CrossControlRingLcDualCmd* lc = NULL;
				CrossControlRingRcDualCmd* rc = NULL;
				dst[0] = 0x80 | (u8_t)(dual->present & 0x7F);
				switch (dual->present)
				{
				case CrossControlDualCmdPresent_lc_fixed:
					if ((lc = dual->x.lc_fixed) == NULL) ERR_SET_OUT(errp, EFAULT);
					else
					{
						dst[1] = (u8_t)((dual->x.lc_fixed->ring_b & 0xF) << 4)
							| (u8_t)(dual->x.lc_fixed->ring_a & 0xF);
						Dz1Error_set(errp, 0);
					}
					break;
				case CrossControlDualCmdPresent_lc_control:
					if ((lc = dual->x.lc_control) == NULL) ERR_SET_OUT(errp, EFAULT);
					else
					{
						dst[1] = (u8_t)((dual->x.lc_control->ring_b & 0xF) << 4)
							| (u8_t)(dual->x.lc_control->ring_a & 0xF);
						Dz1Error_set(errp, 0);
					}
					break;
				case CrossControlDualCmdPresent_lc_actuation:
					if ((lc = dual->x.lc_actuation) == NULL) ERR_SET_OUT(errp, EFAULT);
					else
					{
						dst[1] = (u8_t)((dual->x.lc_actuation->ring_b & 0xF) << 4)
							| (u8_t)(dual->x.lc_actuation->ring_a & 0xF);
						Dz1Error_set(errp, 0);
					}
					break;
				case CrossControlDualCmdPresent_rc_actuation:
					if ((rc = dual->x.rc_actuation) == NULL) ERR_SET_OUT(errp, EFAULT);
					else
					{
						dst[1] = (u8_t)((dual->x.rc_actuation->ring_b & 0xF) << 4)
							| (u8_t)(dual->x.rc_actuation->ring_a & 0xF);
						Dz1Error_set(errp, 0);
					}
					break;
				case CrossControlDualCmdPresent_rc_online:
					if ((rc = dual->x.rc_online) == NULL) ERR_SET_OUT(errp, EFAULT);
					else
					{
						dst[1] = (u8_t)((dual->x.rc_online->ring_b & 0xF) << 4)
							| (u8_t)(dual->x.rc_online->ring_a & 0xF);
						Dz1Error_set(errp, 0);
					}
					break;
				default:
					ERR_SET_OUT(errp, EFAULT); break;
				}
				dst[2] = 0;		// Reserved
				dst[3] = 0;		// Reserved
			}
			break;
		default:
			ERR_SET_OUT(errp, EFAULT); break;
			break;
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _cross_control_cmd_decode(CrossControlCmd* dst, u8_t* data, size_t sz, Dz1Error* errp)
{
	if (dst == NULL || data == NULL || sz < 4) ERR_SET_OUT(errp, EFAULT);
	else if ((data[0] & 0x80) == 0x00)
	{
		// single mode
		CrossControlSingleCmd* single = NULL;
		dst->present = CrossControlCmdPresent_single;
		if ((dst->x.single = single = CrossControlSingleCmd_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			single->present = (CrossControlSingleCmdPresent)(data[0] & 0x7F);
			switch (single->present)
			{
			case CrossControlSingleCmdPresent_lc_fixed:
				single->x.lc_fixed = (CrossControlRingLcCmd)(data[1] & 0xF);
				break;
			case CrossControlSingleCmdPresent_lc_control:
				single->x.lc_control = (CrossControlRingLcCmd)(data[1] & 0xF);
				break;
			case CrossControlSingleCmdPresent_lc_actuation:
				single->x.lc_actuation = (CrossControlRingLcCmd)(data[1] & 0xF);
				break;
			case CrossControlSingleCmdPresent_rc_actuation:
				single->x.rc_actuation = (CrossControlRingRcCmd)(data[1] & 0xF);
				break;
			case CrossControlSingleCmdPresent_rc_online:
				single->x.rc_online = (CrossControlRingRcCmd)(data[1] & 0xF);
				break;
				break;
			default:
				ERR_SET_OUT(errp, EFAULT); break;
				break;
			}
		}
	}
	else
	{
		//  Dual mode
		CrossControlDualCmd* dual = NULL;
		dst->present = CrossControlCmdPresent_dual;
		if ((dst->x.dual = dual = CrossControlDualCmd_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			CrossControlRingLcDualCmd* lc = NULL;
			CrossControlRingRcDualCmd* rc = NULL;
			dual->present = (CrossControlDualCmdPresent)(data[0] & 0x7F);
			switch (dual->present)
			{
			case CrossControlDualCmdPresent_lc_fixed:
				if ((dual->x.lc_fixed = lc = CrossControlRingLcDualCmd_gen(errp)) == NULL) ERR_OUT(errp);
				else
				{
					lc->ring_a = (CrossControlRingLcCmd)((data[1] >> 4) & 0x7);
					lc->ring_b = (CrossControlRingLcCmd)((data[1] >> 0) & 0x7);
					Dz1Error_set(errp, 0);
				}
				break;
			case CrossControlDualCmdPresent_lc_control:
				if ((dual->x.lc_control = lc = CrossControlRingLcDualCmd_gen(errp)) == NULL) ERR_OUT(errp);
				else
				{
					lc->ring_a = (CrossControlRingLcCmd)((data[1] >> 4) & 0x7);
					lc->ring_b = (CrossControlRingLcCmd)((data[1] >> 0) & 0x7);
					Dz1Error_set(errp, 0);
				}
				break;
			case CrossControlDualCmdPresent_lc_actuation:
				if ((dual->x.lc_actuation = lc = CrossControlRingLcDualCmd_gen(errp)) == NULL) ERR_OUT(errp);
				else
				{
					lc->ring_a = (CrossControlRingLcCmd)((data[1] >> 4) & 0x7);
					lc->ring_b = (CrossControlRingLcCmd)((data[1] >> 0) & 0x7);
					Dz1Error_set(errp, 0);
				}
				break;
			case CrossControlDualCmdPresent_rc_actuation:
				if ((dual->x.rc_actuation = rc = CrossControlRingRcDualCmd_gen(errp)) == NULL) ERR_OUT(errp);
				else
				{
					rc->ring_a = (CrossControlRingRcCmd)((data[1] >> 4) & 0x7);
					rc->ring_b = (CrossControlRingRcCmd)((data[1] >> 0) & 0x7);
					Dz1Error_set(errp, 0);
				}
				break;
			case CrossControlDualCmdPresent_rc_online:
				if ((dual->x.rc_online = rc = CrossControlRingRcDualCmd_gen(errp)) == NULL) ERR_OUT(errp);
				else
				{
					rc->ring_a = (CrossControlRingRcCmd)((data[1] >> 4) & 0x7);
					rc->ring_b = (CrossControlRingRcCmd)((data[1] >> 0) & 0x7);
					Dz1Error_set(errp, 0);
				}
				break;
			default:
				ERR_SET_OUT(errp, EFAULT); break;
				break;
			}
		}
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

ssize_t CrossControlCmd_write(Dz1Stream* dst, CrossControlCmd* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;

	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[4] = { 0, };
		if (_cross_control_cmd_encode(data, 4, src, errp) == FALSE) ERR_OUT_RET(errp, -1);
		else DZ1_STREAM_WRITE(dst, data, 4, errp, ret);
	}
	return ret;
}

ssize_t CrossControlCmd_read(CrossControlCmd* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[4] = { 0, };
		DZ1_STREAM_READ(data, 4, src, errp, ret);
		if (_cross_control_cmd_decode(dst, data, 4, errp) == FALSE) ERR_OUT_RET(errp, -1);
	}
	return ret;
}

// CrossControlCmd CODEC
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// CrossStatusBasicInfo CODEC
static bool_t CrossStatusBasicInfo_encode(u8_t* dst, size_t sz, CrossStatusBasicInfo* src, Dz1Error* errp)
{
	if (dst == NULL || sz < 25 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = dst;
		/* Byte 1
		bool								power_fail;
		bool								comm_fail;
		bool								lamp_oper;
		bool								is_dual_ring;
		bool								ppc_enabled;
		CrossStatusBasicInfo_OperationMode	oper_mode;					-- 3 bit
		*/
		*dp = 0x00;
		*dp |= src->power_fail ? 0x80 : 0x00;
		*dp |= src->comm_fail ? 0x40 : 0x00;
		*dp |= src->lamp_oper ? 0x20 : 0x00;
		*dp |= src->is_dual_ring ? 0x10 : 0x00;
		*dp |= src->ppc_enabled ? 0x08 : 0x00;
		*dp |= ((u8_t)(src->oper_mode) & 0x07);
		dp++;
		/* Byte 2
		uint8						 ring_a_phase;				-- 3 bit = 0 ~ 7
		uint8						 ring_a_step;				-- 5 bit = 0 ~ 31
		*/
		*dp++ = ((src->ring_a_phase & 0x07) << 5) | (src->ring_a_step & 0x1F);
		/* Byte 3
		uint8						 ring_b_phase;		--3 bit = 0 ~7
		uint8						 ring_b_step;		--5 bit = 0 ~31
		*/
		*dp++ = ((src->ring_b_phase & 0x07) << 5) | (src->ring_b_step & 0x1F);
		/* Byte 4
		bool						 pannel_is_manual;
		bool						 pannel_manual_sw;
		bool						 pannel_blink_sw;
		bool						 pannel_light_out_sw;
		bool						 is_contradiction;
		bool						 is_light_out;
		bool						 is_blink;
		bool						 is_database;*/
		*dp = 0x00;
		*dp |= src->pannel_is_manual ? 0x80 : 0x00;
		*dp |= src->pannel_manual_sw ? 0x40 : 0x00;
		*dp |= src->pannel_blink_sw ? 0x20 : 0x00;
		*dp |= src->pannel_light_out_sw ? 0x10 : 0x00;
		*dp |= src->is_contradiction ? 0x08 : 0x00;
		*dp |= src->is_light_out ? 0x04 : 0x00;
		*dp |= src->is_blink ? 0x02 : 0x00;
		*dp |= src->is_database ? 0x01 : 0x00;
		/*Byte 5
		bool								push_button_enable;
		CrossStatusBasicInfo_BlinkReason	blink_reason;			--3 bit = 0 ~7
		bool								is_timed_left_signal;
		bool								manual_enabled;
		bool								conflict_enabled;
		bool								is_door_opened;*/
		*dp = 0x00;
		*dp |= src->push_button_enable ? 0x80 : 0x00;
		*dp |= ((u8_t)src->blink_reason & 0x7) << 4;
		*dp |= src->is_timed_left_signal ? 0x08 : 0x00;
		*dp |= src->manual_enabled ? 0x04 : 0x00;
		*dp |= src->conflict_enabled ? 0x02 : 0x00;
		*dp |= src->is_door_opened ? 0x01 : 0x00;
		dp++;
		/* -- Byte 6
		uint8						 contradiction_lsu;			-- 4 bit
		bool						 contradiction_from_sw;
		uint8						 contradiction_circuit;		-- 3 bit
		*/
		*dp = 0x00;
		*dp |= ((u8_t)src->contradiction_lsu & 0xF) >> 4;
		*dp |= src->contradiction_from_sw ? 0x08 : 0x00;
		*dp |= src->contradiction_curcuit & 0x07;
		dp++;
		/*-- Byte 7~9
		uint8						 pedestrian_lamp;			-- 8 bit direction flag
		uint8						 push_button_pending;		-- 8 bit direction flag
		uint8						 push_button_status;		-- 8 bit direction flag
		*/
		*dp++ = src->pedestrian_lamp;
		*dp++ = src->push_button_pending;
		*dp++ = src->push_button_status;
		/*-- Byte 10~16
		uint8						 opt_board_status;
		uint8						 period_counter;
		uint8						 total_period;
		uint8						 curr_period;
		uint8						 period_offset;
		uint8						 hold_phease;
		uint8						 omit_phease;
		*/
		*dp++ = src->opt_board_status;
		*dp++ = src->period_counter;
		*dp++ = src->total_period;
		*dp++ = src->curr_period;
		*dp++ = src->period_offset;
		*dp++ = src->hold_phase;
		*dp++ = src->omit_phase;
		/* -- Byte 17
		bool						 is_four_color_lamp;
		uint8						 oper_map_id;				-- 3 bit = 0 ~ 7
		bool						 jam_ctrl_enabled;
		bool						 jam_ctrl_mode;
		bool						 jam_term_early0;
		bool						 jam_term_early1;
		*/
		*dp = 0x00;
		*dp = src->is_four_color_lamp ? 0x80 : 0x00;
		*dp = ((u8_t)src->oper_map_id & 0x7) << 4;
		*dp = src->jam_ctrl_enabled ? 0x08 : 0x00;
		*dp = src->jam_ctrl_mode ? 0x04 : 0x00;
		*dp = src->jam_term_early0 ? 0x02 : 0x00;
		*dp = src->jam_term_early1 ? 0x01 : 0x00;
		dp++;
		/* -- Byte 18~19, 20~21
		uint16						 firmware_id;
		uint16						 firmware_idx;
		*/
		*dp++ = (u8_t)((src->firmware_id >> 8) & 0xFF);
		*dp++ = (u8_t)((src->firmware_id >> 0) & 0xFF);
		*dp++ = (u8_t)((src->firmware_idx >> 8) & 0xFF);
		*dp++ = (u8_t)((src->firmware_idx >> 0) & 0xFF);
		/* -- Byte 22
		uint8						 database_status;
		*/
		*dp++ = src->database_status;
		/*-- Byte 23-24
		uint8						 ppc_control_status;
		uint8						 ups_control_status;
		*/
		*dp++ = src->ppc_control_status;
		*dp++ = src->ups_control_status;
		/* -- Byte 25
		bool						 map_is_dirty;				-- bit 0
		bool						 lock_installed;			-- bit 1
		bool						 lock_is_locked;			-- bit 2
		bool						 db_is_locked;				-- bit 3
		*/
		*dp = 0x00;
		*dp |= src->map_is_dirty ? 0x01 : 0x00;
		*dp |= src->lock_installed ? 0x02 : 0x00;
		*dp |= src->lock_is_locked ? 0x04 : 0x00;
		*dp |= src->db_is_locked ? 0x08 : 0x00;

		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t CrossStatusBasicInfo_decode(CrossStatusBasicInfo* dst, u8_t* src, size_t sz, Dz1Error* errp)
{
	if (dst == NULL || sz < 25 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = src;
		/* Byte 1
		bool								power_fail;
		bool								comm_fail;
		bool								lamp_oper;
		bool								is_dual_ring;
		bool								ppc_enabled;
		CrossStatusBasicInfo_OperationMode	oper_mode;					-- 3 bit
		*/
		dst->power_fail = *dp & 0x80 ? TRUE : FALSE;
		dst->comm_fail = *dp & 0x40 ? TRUE : FALSE;
		dst->lamp_oper = *dp & 0x20 ? TRUE : FALSE;
		dst->is_dual_ring = *dp & 0x10 ? TRUE : FALSE;
		dst->ppc_enabled = *dp & 0x08 ? TRUE : FALSE;
		dst->oper_mode = (CrossStatusBasicInfo_OperationMode)(*dp & 0x07);
		dp++;
		/* Byte 2
		uint8						 ring_a_phase;				-- 3 bit = 0 ~ 7
		uint8						 ring_a_step;				-- 5 bit = 0 ~ 31
		*/
		dst->ring_a_phase = ((*dp >> 5) & 0x7);
		dst->ring_a_step = (*dp & 0x1F);
		dp++;
		/* Byte 3
		uint8						 ring_b_phase;		--3 bit = 0 ~7
		uint8						 ring_b_step;		--5 bit = 0 ~31
		*/
		dst->ring_b_phase = ((*dp >> 5) & 0x7);
		dst->ring_b_step = (*dp & 0x1F);
		dp++;
		/* Byte 4
		bool						 pannel_is_manual;
		bool						 pannel_manual_sw;
		bool						 pannel_blink_sw;
		bool						 pannel_light_out_sw;
		bool						 is_contradiction;
		bool						 is_light_out;
		bool						 is_blink;
		bool						 is_database;*/
		dst->pannel_is_manual = *dp & 0x80 ? TRUE : FALSE;
		dst->pannel_manual_sw = *dp & 0x40 ? TRUE : FALSE;
		dst->pannel_blink_sw = *dp & 0x20 ? TRUE : FALSE;
		dst->pannel_light_out_sw = *dp & 0x10 ? TRUE : FALSE;
		dst->is_contradiction = *dp & 0x08 ? TRUE : FALSE;
		dst->is_light_out = *dp & 0x04 ? TRUE : FALSE;
		dst->is_blink = *dp & 0x02 ? TRUE : FALSE;
		dst->is_database = *dp & 0x01 ? TRUE : FALSE;
		dp++;
		/*Byte 5
		bool								push_button_enable;
		CrossStatusBasicInfo_BlinkReason	blink_reason;			--3 bit = 0 ~7
		bool								is_timed_left_signal;
		bool								manual_enabled;
		bool								conflict_enabled;
		bool								is_door_opened;*/
		dst->push_button_enable = *dp & 0x80 ? TRUE : FALSE;
		dst->blink_reason = (CrossStatusBasicInfo_BlinkReason)((*dp >> 4) & 0x7);
		dst->is_timed_left_signal = *dp & 0x08 ? TRUE : FALSE;
		dst->manual_enabled = *dp & 0x04 ? TRUE : FALSE;
		dst->conflict_enabled = *dp & 0x02 ? TRUE : FALSE;
		dst->is_door_opened = *dp & 0x01 ? TRUE : FALSE;
		dp++;
		/*Byte 6
		uint8						 contradiction_lsu;		-- 4 bit
		bool						 contradiction_from_sw;
		uint8						 contradiction_curcuit;	-- 3 bit*/
		dst->contradiction_lsu = ((*dp >> 4) & 0xF);
		dst->contradiction_from_sw = *dp & 0x08 ? TRUE : FALSE;
		dst->contradiction_curcuit = *dp & 0x7;
		dp++;
		/* Byte 7~9
		uint8						 pedestrian_lamp;		--8 bit direction flag
		uint8						 push_button_pending;
		uint8						 push_button_status;*/
		dst->pedestrian_lamp = *dp++;
		dst->push_button_pending = *dp++;
		dst->push_button_status = *dp++;
		/* Byte 10~16
		uint8						 opt_board_status;
		uint8						 period_counter;
		uint8						 total_period;
		uint8						 curr_period;
		uint8						 period_offset;
		uint8						 hold_phase;
		uint8						 omit_phase;*/
		dst->opt_board_status = *dp++;
		dst->period_counter = *dp++;
		dst->total_period = *dp++;
		dst->curr_period = *dp++;
		dst->period_offset = *dp++;
		dst->hold_phase = *dp++;
		dst->omit_phase = *dp++;
		/* Byte 17
		bool						 is_four_color_lamp;
		uint8						 oper_map_id;		--3 bit = 0 ~7
		bool						 jam_ctrl_enabled;
		bool						 jam_ctrl_mode;
		bool						 jam_term_early0;
		bool						 jam_term_early1;*/
		dst->is_four_color_lamp = *dp & 0x80 ? TRUE : FALSE;
		dst->oper_map_id = ((*dp >> 4) & 0x7);
		dst->jam_ctrl_enabled = *dp & 0x08 ? TRUE : FALSE;
		dst->jam_ctrl_mode = *dp & 0x04 ? TRUE : FALSE;
		dst->jam_term_early0 = *dp & 0x02 ? TRUE : FALSE;
		dst->jam_term_early1 = *dp & 0x01 ? TRUE : FALSE;
		dp++;
		/* Byte 18~19, 20~21
		uint16						 firmware_id;
		uint16						 firmware_idx;*/
		dst->firmware_id = 0;
		dst->firmware_id |= ((u16_t)*dp & 0xFF) << 8; dp++;
		dst->firmware_id |= ((u16_t)*dp & 0xFF) << 0; dp++;

		dst->firmware_idx = 0;
		dst->firmware_idx |= ((u16_t)*dp & 0xFF) << 8; dp++;
		dst->firmware_idx |= ((u16_t)*dp & 0xFF) << 0; dp++;
		/* Byte 22
		uint8						 database_status;*/
		dst->database_status = *dp++;
		/* Byte 23 - 24
		uint8						 ppc_control_status;
		uint8						 ups_control_status;*/
		dst->ppc_control_status = *dp++;
		dst->ups_control_status = *dp++;
		/* Byte 25
		bool						 map_is_dirty;				--bit 0
		bool						 lock_installed;			--bit 1
		bool						 lock_is_locked;			--bit 2
		bool						 db_is_locked;				--bit 3*/
		dst->map_is_dirty = *dp & 0x01 ? TRUE : FALSE;
		dst->lock_installed = *dp & 0x02 ? TRUE : FALSE;
		dst->lock_is_locked = *dp & 0x04 ? TRUE : FALSE;
		dst->db_is_locked = *dp & 0x08 ? TRUE : FALSE;

		Dz1Error_set(errp, 0);
	}

	return ERR_IS_SUCCESS(errp);
}

ssize_t CrossStatusBasicInfo_write(Dz1Stream* dst, CrossStatusBasicInfo* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[25] = { 0, };
		if (CrossStatusBasicInfo_encode(data, sizeof(data), src, errp) == FALSE) ERR_OUT(errp);
		else DZ1_STREAM_WRITE(dst, data, sizeof(data), errp, ret);
	}
	return ret;
}

ssize_t CrossStatusBasicInfo_read(CrossStatusBasicInfo* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[25] = { 0, };
		DZ1_STREAM_READ(data, sizeof(data), src, errp, ret);
		if (CrossStatusBasicInfo_decode(dst, data, sizeof(data), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}


// CrossStatusBasicInfo CODEC
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CrossStatusExtInfo_r27 CODEC
static bool_t CrossStatusExtInfo_r27_encode(u8_t* dst, size_t sz, CrossStatusExtInfo_r27* src, Dz1Error* errp)
{
	Dz1Binary* bin = NULL;
	if (dst == NULL || sz < 50 || src == NULL) ERR_OUT(errp);
	else if ((bin = src->ppc_data) == NULL) ERR_OUT(errp);
	else if (bin->data == NULL || bin->size != 16) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u8_t* dp = dst;
		*dp++ = src->type;
		*dp++ = src->ver;
		memcpy(dp, bin->data, bin->size);
		dp += bin->size;
		*dp++ = (u8_t)((src->detector_status >> 24) & 0xFF);
		*dp++ = (u8_t)((src->detector_status >> 16) & 0xFF);
		*dp++ = (u8_t)((src->detector_status >> 8) & 0xFF);
		*dp++ = (u8_t)((src->detector_status >> 0) & 0xFF);
		*dp++ = src->mlc_slc_comm_fail;
		*dp++ = src->contradiction_slc;
		*dp++ = ((u8_t)(src->contradiction_prove & 0x7) << 5) | (u8_t)(src->contradiction_circuit & 0x1F);
		*dp++ = src->ring_a_phase;
		*dp++ = src->ring_a_step;
		*dp++ = src->ring_b_phase;
		*dp++ = src->ring_b_step;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}


static bool_t CrossStatusExtInfo_r27_decode(CrossStatusExtInfo_r27* dst, u8_t* src, size_t sz, Dz1Error* errp)
{
	if (dst == NULL || sz < 50 || src == NULL) ERR_OUT(errp);
	else if (dst->ppc_data != NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1Binary* bin = NULL;
		u8_t* dp = src;
		dst->type = *dp++;
		dst->ver = *dp++;
		if ((dst->ppc_data = bin = Dz1Binary_new(dp, 16, errp)) == NULL) ERR_OUT(errp);
		else
		{
			dp += bin->size;
			dst->detector_status = 0;
			dst->detector_status = (dst->detector_status << 8) | ((u32_t)*dp & 0xFF); dp++;
			dst->detector_status = (dst->detector_status << 8) | ((u32_t)*dp & 0xFF); dp++;
			dst->detector_status = (dst->detector_status << 8) | ((u32_t)*dp & 0xFF); dp++;
			dst->detector_status = (dst->detector_status << 8) | ((u32_t)*dp & 0xFF); dp++;
			dst->mlc_slc_comm_fail = *dp++;
			dst->contradiction_slc = *dp++;

			dst->contradiction_prove = (CrossStatusExtInfo_ContradictionReason)((*dp >> 5) & 0x7);
			dst->contradiction_circuit = *dp & 0x1F;
			dp++;

			dst->ring_a_phase = *dp++;
			dst->ring_a_step = *dp++;
			dst->ring_b_phase = *dp++;
			dst->ring_b_step = *dp++;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}


ssize_t CrossStatusExtInfo_r27_write(Dz1Stream* dst, CrossStatusExtInfo_r27* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[50] = { 0, };
		if (CrossStatusExtInfo_r27_encode(data, sizeof(data), src, errp) == FALSE) ERR_OUT(errp);
		else DZ1_STREAM_WRITE(dst, data, sizeof(data), errp, ret);
	}
	return ret;
}

ssize_t CrossStatusExtInfo_r27_read(CrossStatusExtInfo_r27* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[50] = { 0, };
		DZ1_STREAM_READ(data, sizeof(data), src, errp, ret);
		if (CrossStatusExtInfo_r27_decode(dst, data, sizeof(data), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}
// CrossStatusExtInfo_r27 CODEC
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// DetectorInfo CODEC
static bool_t DetectorInfoValueMap_encode(u8_t* dst, size_t sz, DetectorInfoValueMap* src, Dz1Error* errp)
{
	if (dst == NULL || sz < 32 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = dst;
		*dp = 0x00;
		*dp++=src->detector1;
		*dp++=src->detector2;
		*dp++=src->detector3;
		*dp++=src->detector4;
		*dp++=src->detector5;
		*dp++=src->detector6;
		*dp++=src->detector7;
		*dp++=src->detector8;
		*dp++=src->detector9;
		*dp++=src->detector10;
		*dp++=src->detector11;
		*dp++=src->detector12;
		*dp++=src->detector13;
		*dp++=src->detector14;
		*dp++=src->detector15;
		*dp++=src->detector16;
		*dp++=src->detector17;
		*dp++=src->detector18;
		*dp++=src->detector19;
		*dp++=src->detector20;
		*dp++=src->detector21;
		*dp++=src->detector22;
		*dp++=src->detector23;
		*dp++=src->detector24;
		*dp++=src->detector25;
		*dp++=src->detector26;
		*dp++=src->detector27;
		*dp++=src->detector28;
		*dp++=src->detector29;
		*dp++=src->detector30;
		*dp++=src->detector31;
		*dp++=src->detector32;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t DetectorInfo_encode(u8_t* dst, size_t sz, DetectorInfo* src, Dz1Error* errp)
{
	if (dst == NULL || sz < 224 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = dst;
		// 1 ~ 32 Byte
		*dp = 0x00;
		*dp |= src->detector_info_flags->detector1->bit6? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector1->bit5? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector1->bit4? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector1->bit3? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector1->bit2? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector1->bit1? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector1->bit0? 0x01 : 0x00;
		dp++;

		*dp = 0x00;
		*dp |= src->detector_info_flags->detector2->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector2->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector2->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector2->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector2->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector2->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector2->bit0 ? 0x01 : 0x00;
		dp++;

		*dp = 0x00;
		*dp |= src->detector_info_flags->detector3->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector3->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector3->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector3->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector3->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector3->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector3->bit0 ? 0x01 : 0x00;
		dp++;

		*dp = 0x00;
		*dp |= src->detector_info_flags->detector4->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector4->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector4->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector4->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector4->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector4->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector4->bit0 ? 0x01 : 0x00;
		dp++;

		*dp = 0x00;
		*dp |= src->detector_info_flags->detector5->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector5->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector5->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector5->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector5->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector5->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector5->bit0 ? 0x01 : 0x00;
		dp++;

		*dp = 0x00;
		*dp |= src->detector_info_flags->detector6->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector6->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector6->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector6->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector6->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector6->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector6->bit0 ? 0x01 : 0x00;
		dp++;

		*dp = 0x00;
		*dp |= src->detector_info_flags->detector7->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector7->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector7->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector7->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector7->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector7->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector7->bit0 ? 0x01 : 0x00;
		dp++;

		*dp = 0x00;
		*dp |= src->detector_info_flags->detector8->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector8->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector8->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector8->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector8->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector8->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector8->bit0 ? 0x01 : 0x00;
		dp++;

		*dp = 0x00;
		*dp |= src->detector_info_flags->detector9->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector9->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector9->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector9->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector9->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector9->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector9->bit0 ? 0x01 : 0x00;
		dp++;

		*dp = 0x00;
		*dp |= src->detector_info_flags->detector10->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector10->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector10->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector10->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector10->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector10->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector10->bit0 ? 0x01 : 0x00;
		dp++;

		*dp = 0x00;
		*dp |= src->detector_info_flags->detector11->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector11->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector11->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector11->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector11->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector11->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector11->bit0 ? 0x01 : 0x00;
		dp++;

		*dp = 0x00;
		*dp |= src->detector_info_flags->detector12->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector12->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector12->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector12->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector12->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector12->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector12->bit0 ? 0x01 : 0x00;
		dp++;

		*dp = 0x00;
		*dp |= src->detector_info_flags->detector13->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector13->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector13->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector13->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector13->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector13->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector13->bit0 ? 0x01 : 0x00;
		dp++;

		*dp = 0x00;
		*dp |= src->detector_info_flags->detector14->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector14->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector14->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector14->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector14->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector14->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector14->bit0 ? 0x01 : 0x00;
		dp++;

		*dp = 0x00;
		*dp |= src->detector_info_flags->detector15->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector15->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector15->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector15->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector15->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector15->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector15->bit0 ? 0x01 : 0x00;
		dp++;

		*dp = 0x00;
		*dp |= src->detector_info_flags->detector16->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector16->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector16->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector16->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector16->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector16->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector16->bit0 ? 0x01 : 0x00;
		dp++;

		*dp = 0x00;
		*dp |= src->detector_info_flags->detector17->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector17->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector17->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector17->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector17->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector17->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector17->bit0 ? 0x01 : 0x00;
		dp++;

		*dp = 0x00;
		*dp |= src->detector_info_flags->detector18->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector18->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector18->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector18->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector18->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector18->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector18->bit0 ? 0x01 : 0x00;
		dp++;

		*dp = 0x00;
		*dp |= src->detector_info_flags->detector19->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector19->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector19->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector19->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector19->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector19->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector19->bit0 ? 0x01 : 0x00;
		dp++;

		*dp = 0x00;
		*dp |= src->detector_info_flags->detector20->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector20->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector20->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector20->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector20->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector20->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector20->bit0 ? 0x01 : 0x00;
		dp++;

		*dp = 0x00;
		*dp |= src->detector_info_flags->detector21->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector21->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector21->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector21->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector21->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector21->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector21->bit0 ? 0x01 : 0x00;
		dp++;

		*dp = 0x00;
		*dp |= src->detector_info_flags->detector22->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector22->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector22->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector22->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector22->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector22->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector22->bit0 ? 0x01 : 0x00;
		dp++;

		*dp = 0x00;
		*dp |= src->detector_info_flags->detector23->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector23->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector23->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector23->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector23->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector23->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector23->bit0 ? 0x01 : 0x00;
		dp++;

		*dp = 0x00;
		*dp |= src->detector_info_flags->detector24->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector24->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector24->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector24->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector24->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector24->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector24->bit0 ? 0x01 : 0x00;
		dp++;

		*dp = 0x00;
		*dp |= src->detector_info_flags->detector25->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector25->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector25->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector25->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector25->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector25->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector25->bit0 ? 0x01 : 0x00;
		dp++;
	
		*dp = 0x00;
		*dp |= src->detector_info_flags->detector26->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector26->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector26->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector26->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector26->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector26->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector26->bit0 ? 0x01 : 0x00;
		dp++;
		
		*dp = 0x00;
		*dp |= src->detector_info_flags->detector27->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector27->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector27->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector27->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector27->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector27->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector27->bit0 ? 0x01 : 0x00;
		dp++;
		
		*dp = 0x00;
		*dp |= src->detector_info_flags->detector28->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector28->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector28->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector28->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector28->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector28->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector28->bit0 ? 0x01 : 0x00;
		dp++;
		
		*dp = 0x00;
		*dp |= src->detector_info_flags->detector29->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector29->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector29->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector29->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector29->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector29->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector29->bit0 ? 0x01 : 0x00;
		dp++;
		
		*dp = 0x00;
		*dp |= src->detector_info_flags->detector30->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector30->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector30->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector30->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector30->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector30->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector30->bit0 ? 0x01 : 0x00;
		dp++;
		
		*dp = 0x00;
		*dp |= src->detector_info_flags->detector31->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector31->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector31->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector31->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector31->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector31->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector31->bit0 ? 0x01 : 0x00;
		dp++;
		
		*dp = 0x00;
		*dp |= src->detector_info_flags->detector32->bit6 ? 0x40 : 0x00;
		*dp |= src->detector_info_flags->detector32->bit5 ? 0x20 : 0x00;
		*dp |= src->detector_info_flags->detector32->bit4 ? 0x10 : 0x00;
		*dp |= src->detector_info_flags->detector32->bit3 ? 0x08 : 0x00;
		*dp |= src->detector_info_flags->detector32->bit2 ? 0x04 : 0x00;
		*dp |= src->detector_info_flags->detector32->bit1 ? 0x02 : 0x00;
		*dp |= src->detector_info_flags->detector32->bit0 ? 0x01 : 0x00;
		dp++;

		if (0) {}
		// Byte 33 ~64
		else if (DetectorInfoValueMap_encode(dp, 32, src->detector_not_occupy_times, errp) == FALSE) ERR_OUT(errp);
		// Byte 65 ~96
		else if (DetectorInfoValueMap_encode(dp, 32, src->detector_occupy_times, errp) == FALSE) ERR_OUT(errp);
		// Byte 97 ~128
		else if (DetectorInfoValueMap_encode(dp, 32, src->detector_traffic_volumes, errp) == FALSE) ERR_OUT(errp);
		// Byte 129 ~160
		else if (DetectorInfoValueMap_encode(dp, 32, src->detector_traffic_saturations, errp) == FALSE) ERR_OUT(errp);
		// Byte 161 ~192
		else if (DetectorInfoValueMap_encode(dp, 32, src->detector_saturation_flow_rate_per_speeds, errp) == FALSE) ERR_OUT(errp);
		// Byte 193 ~224
		else if (DetectorInfoValueMap_encode(dp, 32, src->detector_saturation_not_ocuppy_time, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t DetectorInfoValueMap_decode(DetectorInfoValueMap* dst, u8_t* src, Dz1Error* errp)
{
	if (dst == NULL || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = src;
		dst->detector1 = *dp++;
		dst->detector2 = *dp++;
		dst->detector3 = *dp++;
		dst->detector4 = *dp++;
		dst->detector5 = *dp++;
		dst->detector6 = *dp++;
		dst->detector7 = *dp++;
		dst->detector8 = *dp++;
		dst->detector9 = *dp++;
		dst->detector10 = *dp++;
		dst->detector11 = *dp++;
		dst->detector12 = *dp++;
		dst->detector13 = *dp++;
		dst->detector14 = *dp++;
		dst->detector15 = *dp++;
		dst->detector16 = *dp++;
		dst->detector17 = *dp++;
		dst->detector18 = *dp++;
		dst->detector19 = *dp++;
		dst->detector20 = *dp++;
		dst->detector21 = *dp++;
		dst->detector22 = *dp++;
		dst->detector23 = *dp++;
		dst->detector24 = *dp++;
		dst->detector25 = *dp++;
		dst->detector26 = *dp++;
		dst->detector27 = *dp++;
		dst->detector28 = *dp++;
		dst->detector29 = *dp++;
		dst->detector30 = *dp++;
		dst->detector31 = *dp++;
		dst->detector32 = *dp++;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t DetectorInfo_decode(DetectorInfo* dst, u8_t* src, size_t sz, Dz1Error* errp)
{
	if (dst == NULL || sz < 224 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = src;
		/*--Byte 1 ~32
		DetectorInfoFlagMaps * detector_info_flags;*/
		dst->detector_info_flags = DetectorInfoFlagMaps_gen(errp);
		dst->detector_info_flags->detector1 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector1->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector1->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector1->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector1->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector1->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector1->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector1->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector2 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector2->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector2->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector2->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector2->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector2->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector2->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector2->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector3 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector3->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector3->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector3->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector3->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector3->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector3->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector3->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector4 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector4->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector4->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector4->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector4->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector4->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector4->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector4->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector5 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector5->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector5->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector5->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector5->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector5->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector5->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector5->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector6 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector6->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector6->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector6->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector6->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector6->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector6->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector6->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector7 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector7->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector7->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector7->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector7->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector7->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector7->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector7->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector8 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector8->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector8->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector8->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector8->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector8->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector8->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector8->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector9 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector9->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector9->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector9->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector9->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector9->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector9->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector9->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector10 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector10->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector10->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector10->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector10->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector10->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector10->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector10->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector11 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector11->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector11->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector11->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector11->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector11->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector11->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector11->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector12 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector12->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector13 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector13->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector13->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector13->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector13->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector13->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector13->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector13->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector14 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector14->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector14->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector14->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector14->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector14->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector14->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector14->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector15 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector12->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector16 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector12->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector17 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector12->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector18 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector12->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector19 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector12->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector12->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector21 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector21->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector21->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector21->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector21->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector21->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector21->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector21->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector22 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector22->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector22->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector22->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector22->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector22->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector22->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector22->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector23 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector23->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector23->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector23->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector23->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector23->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector23->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector23->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector24 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector24->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector24->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector24->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector24->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector24->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector24->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector24->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector25 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector25->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector25->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector25->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector25->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector25->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector25->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector25->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector26 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector26->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector26->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector26->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector26->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector26->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector26->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector26->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector27 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector27->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector27->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector27->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector27->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector27->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector27->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector27->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector28 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector28->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector28->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector28->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector28->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector28->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector28->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector28->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector29 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector29->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector29->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector29->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector29->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector29->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector29->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector29->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector30 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector30->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector30->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector30->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector30->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector30->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector30->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector30->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector31 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector31->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector31->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector31->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector31->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector31->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector31->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector31->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_info_flags->detector32 = DetectorInfoFlagMap_gen(errp);
		dst->detector_info_flags->detector32->bit6 = *dp & 0x40 ? TRUE : FALSE;
		dst->detector_info_flags->detector32->bit5 = *dp & 0x20 ? TRUE : FALSE;
		dst->detector_info_flags->detector32->bit4 = *dp & 0x10 ? TRUE : FALSE;
		dst->detector_info_flags->detector32->bit3 = *dp & 0x08 ? TRUE : FALSE;
		dst->detector_info_flags->detector32->bit2 = *dp & 0x04 ? TRUE : FALSE;
		dst->detector_info_flags->detector32->bit1 = *dp & 0x02 ? TRUE : FALSE;
		dst->detector_info_flags->detector32->bit0 = *dp & 0x01 ? TRUE : FALSE;
		dp++;

		dst->detector_not_occupy_times = DetectorInfoValueMap_gen(errp);
		DetectorInfoValueMap_decode(dst->detector_not_occupy_times, dp, errp);
		dp += 32;

		dst->detector_occupy_times = DetectorInfoValueMap_gen(errp);
		DetectorInfoValueMap_decode(dst->detector_occupy_times, dp, errp);
		dp += 32;

		dst->detector_traffic_volumes = DetectorInfoValueMap_gen(errp);
		DetectorInfoValueMap_decode(dst->detector_traffic_volumes, dp, errp);
		dp += 32;

		dst->detector_traffic_saturations = DetectorInfoValueMap_gen(errp);
		DetectorInfoValueMap_decode(dst->detector_traffic_saturations, dp, errp);
		dp += 32;

		dst->detector_saturation_flow_rate_per_speeds = DetectorInfoValueMap_gen(errp);
		DetectorInfoValueMap_decode(dst->detector_saturation_flow_rate_per_speeds, dp, errp);
		dp += 32;

		dst->detector_saturation_not_ocuppy_time = DetectorInfoValueMap_gen(errp);
		DetectorInfoValueMap_decode(dst->detector_saturation_not_ocuppy_time, dp, errp);
		dp += 32;

		Dz1Error_set(errp, 0);
	}

	return ERR_IS_SUCCESS(errp);
}

ssize_t DetectorInfo_write(Dz1Stream* dst, DetectorInfo* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[224] = { 0, };
		if (DetectorInfo_encode(data, sizeof(data), src, errp) == FALSE) ERR_OUT(errp);
		else DZ1_STREAM_WRITE(dst, data, sizeof(data), errp, ret);
	}

	return ret;
}

ssize_t DetectorInfo_read(DetectorInfo* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[224];
		DZ1_STREAM_READ(data, sizeof(data), src, errp, ret);
		if (DetectorInfo_decode(dst, data, sizeof(data), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}
// DetectorInfo CODEC
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// SignalPhaseInfoDown_r27 CODEC
static bool_t SignalPhaseInfoDown_r27_encode(u8_t* dst, size_t sz, SignalPhaseInfoDown_r27* src, u8_t opt, Dz1Error* errp)
{
	if (dst == NULL || src == NULL) ERR_OUT(errp);
	else if (opt == 1 && sz < 17) ERR_OUT(errp);
	else if (opt == 2 && sz < 33) ERR_OUT(errp);
	else if (opt == 3 && sz < 49) ERR_OUT(errp);
	else
	{
		u8_t* dp = dst;
		SignalPhaseInfoPeriodicOperationTime* t1 = NULL;
		SignalPhaseInfoPeriodicOperationTime* t2 = NULL;
		SignalPhaseInfoPeriodicOperationTime* t3 = NULL;
		if ((t1 = src->mandatory->periodic_oper_time1) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			*dp = 0x00;
			*dp++ = (t1->ring_a_phase1 & 0xFF);
			*dp++ = (t1->ring_a_phase2 & 0xFF);
			*dp++ = (t1->ring_a_phase3 & 0xFF);
			*dp++ = (t1->ring_a_phase4 & 0xFF);
			*dp++ = (t1->ring_a_phase5 & 0xFF);
			*dp++ = (t1->ring_a_phase6 & 0xFF);
			*dp++ = (t1->ring_a_phase7 & 0xFF);
			*dp++ = (t1->ring_a_phase8 & 0xFF);
			*dp++ = (t1->ring_b_phase1 & 0xFF);
			*dp++ = (t1->ring_b_phase2 & 0xFF);
			*dp++ = (t1->ring_b_phase3 & 0xFF);
			*dp++ = (t1->ring_b_phase4 & 0xFF);
			*dp++ = (t1->ring_b_phase5 & 0xFF);
			*dp++ = (t1->ring_b_phase6 & 0xFF);
			*dp++ = (t1->ring_b_phase7 & 0xFF);
			*dp++ = (t1->ring_b_phase8 & 0xFF);
			*dp = src->mandatory->offset & 0xFF;
			Dz1Error_set(errp, 0);
		}

		if ((t2 = src->periodic_oper_time2) != NULL)
		{
			*dp = 0x00;
			*dp++ = (t2->ring_a_phase1 & 0xFF);
			*dp++ = (t2->ring_a_phase2 & 0xFF);
			*dp++ = (t2->ring_a_phase3 & 0xFF);
			*dp++ = (t2->ring_a_phase4 & 0xFF);
			*dp++ = (t2->ring_a_phase5 & 0xFF);
			*dp++ = (t2->ring_a_phase6 & 0xFF);
			*dp++ = (t2->ring_a_phase7 & 0xFF);
			*dp++ = (t2->ring_a_phase8 & 0xFF);
			*dp++ = (t2->ring_b_phase1 & 0xFF);
			*dp++ = (t2->ring_b_phase2 & 0xFF);
			*dp++ = (t2->ring_b_phase3 & 0xFF);
			*dp++ = (t2->ring_b_phase4 & 0xFF);
			*dp++ = (t2->ring_b_phase5 & 0xFF);
			*dp++ = (t2->ring_b_phase6 & 0xFF);
			*dp++ = (t2->ring_b_phase7 & 0xFF);
			*dp++ = (t2->ring_b_phase8 & 0xFF);
		}

		if ((t3 = src->periodic_oper_time3) != NULL)
		{
			*dp = 0x00;
			*dp++ = (t3->ring_a_phase1 & 0xFF);
			*dp++ = (t3->ring_a_phase2 & 0xFF);
			*dp++ = (t3->ring_a_phase3 & 0xFF);
			*dp++ = (t3->ring_a_phase4 & 0xFF);
			*dp++ = (t3->ring_a_phase5 & 0xFF);
			*dp++ = (t3->ring_a_phase6 & 0xFF);
			*dp++ = (t3->ring_a_phase7 & 0xFF);
			*dp++ = (t3->ring_a_phase8 & 0xFF);
			*dp++ = (t3->ring_b_phase1 & 0xFF);
			*dp++ = (t3->ring_b_phase2 & 0xFF);
			*dp++ = (t3->ring_b_phase3 & 0xFF);
			*dp++ = (t3->ring_b_phase4 & 0xFF);
			*dp++ = (t3->ring_b_phase5 & 0xFF);
			*dp++ = (t3->ring_b_phase6 & 0xFF);
			*dp++ = (t3->ring_b_phase7 & 0xFF);
			*dp++ = (t3->ring_b_phase8 & 0xFF);
		}

		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t SignalPhaseInfoDownBasic_decode(SignalPhaseInfoDownBasic* dst, u8_t* src, size_t sz, Dz1Error* errp)
{
	if (dst == NULL || sz < 17 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = src;
		SignalPhaseInfoPeriodicOperationTime* t1 = NULL;
		if((t1 = dst->periodic_oper_time1 = SignalPhaseInfoPeriodicOperationTime_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			t1->ring_a_phase1 = *dp++;
			t1->ring_a_phase2 = *dp++;
			t1->ring_a_phase3 = *dp++;
			t1->ring_a_phase4 = *dp++;
			t1->ring_a_phase5 = *dp++;
			t1->ring_a_phase6 = *dp++;
			t1->ring_a_phase7 = *dp++;
			t1->ring_a_phase8 = *dp++;
			t1->ring_b_phase1 = *dp++;
			t1->ring_b_phase2 = *dp++;
			t1->ring_b_phase3 = *dp++;
			t1->ring_b_phase4 = *dp++;
			t1->ring_b_phase5 = *dp++;
			t1->ring_b_phase6 = *dp++;
			t1->ring_b_phase7 = *dp++;
			t1->ring_b_phase8 = *dp++;
			dst->offset = *dp++;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}


static bool_t SignalPhaseInfoPeriodicOperationTime_encode(u8_t* dst, size_t sz, SignalPhaseInfoPeriodicOperationTime* src, Dz1Error* errp)
{
	if (dst == NULL || sz < 16 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = dst;
		*dp++ = src->ring_a_phase1;
		*dp++ = src->ring_a_phase2;
		*dp++ = src->ring_a_phase3;
		*dp++ = src->ring_a_phase4;
		*dp++ = src->ring_a_phase5;
		*dp++ = src->ring_a_phase6;
		*dp++ = src->ring_a_phase7;
		*dp++ = src->ring_a_phase8;
		*dp++ = src->ring_b_phase1;
		*dp++ = src->ring_b_phase2;
		*dp++ = src->ring_b_phase3;
		*dp++ = src->ring_b_phase4;
		*dp++ = src->ring_b_phase5;
		*dp++ = src->ring_b_phase6;
		*dp++ = src->ring_b_phase7;
		*dp++ = src->ring_b_phase8;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t SignalPhaseInfoPeriodicOperationTime_decode(SignalPhaseInfoPeriodicOperationTime* dst, u8_t* src, size_t sz, Dz1Error* errp)
{
	if (dst == NULL || sz < 16 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = src;
		dst->ring_a_phase1 = *dp++;
		dst->ring_a_phase2 = *dp++;
		dst->ring_a_phase3 = *dp++;
		dst->ring_a_phase4 = *dp++;
		dst->ring_a_phase5 = *dp++;
		dst->ring_a_phase6 = *dp++;
		dst->ring_a_phase7 = *dp++;
		dst->ring_a_phase8 = *dp++;
		dst->ring_b_phase1 = *dp++;
		dst->ring_b_phase2 = *dp++;
		dst->ring_b_phase3 = *dp++;
		dst->ring_b_phase4 = *dp++;
		dst->ring_b_phase5 = *dp++;
		dst->ring_b_phase6 = *dp++;
		dst->ring_b_phase7 = *dp++;
		dst->ring_b_phase8 = *dp++;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}


ssize_t SignalPhaseInfoDown_r27_write(Dz1Stream* dst, SignalPhaseInfoDown_r27* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		if ((src->periodic_oper_time2 != NULL) || (src->periodic_oper_time3 != NULL))
		{
			u8_t data[49] = { 0, };
			if (SignalPhaseInfoDown_r27_encode(data, sizeof(data), src, 1, errp) == FALSE) ERR_OUT(errp);
			else DZ1_STREAM_WRITE(dst, data, sizeof(data), errp, ret);
		}
		else if ((src->periodic_oper_time2 != NULL) || (src->periodic_oper_time3 != NULL))
		{
			u8_t data[33] = { 0, };
			if (SignalPhaseInfoDown_r27_encode(data, sizeof(data), src, 2, errp) == FALSE) ERR_OUT(errp);
			else DZ1_STREAM_WRITE(dst, data, sizeof(data), errp, ret);
		}
		else
		{
			u8_t data[17] = { 0, };
			if (SignalPhaseInfoDown_r27_encode(data, sizeof(data), src, 3, errp) == FALSE) ERR_OUT(errp);
			else DZ1_STREAM_WRITE(dst, data, sizeof(data), errp, ret);
		}
	}
	return ret;
}

static ssize_t SignalPhaseInfoDownBasic_read(SignalPhaseInfoDownBasic* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[17] = { 0, };
		DZ1_STREAM_READ(data, sizeof(data), src, errp, ret);
		if (SignalPhaseInfoDownBasic_decode(dst, data, sizeof(data), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}

static ssize_t SignalPhaseInfoPeriodicOperationTime_write(Dz1Stream* dst, SignalPhaseInfoPeriodicOperationTime* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[16] = { 0, };
		if (SignalPhaseInfoPeriodicOperationTime_encode(data, sizeof(data), src, errp) == FALSE) ERR_OUT(errp);
		else DZ1_STREAM_WRITE(dst, data, sizeof(data), errp, ret);
	}
	return ret;
}

static ssize_t SignalPhaseInfoPeriodicOperationTime_read(SignalPhaseInfoPeriodicOperationTime* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[16];
		DZ1_STREAM_READ(data, sizeof(data), src, errp, ret);
		if (SignalPhaseInfoPeriodicOperationTime_decode(dst, data, sizeof(data), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}

ssize_t SignalPhaseInfoDown_r27_read(SignalPhaseInfoDown_r27* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(err, EINVAL, -1);
	else
	{
		if ((dst->mandatory = SignalPhaseInfoDownBasic_gen(errp)) == NULL) ERR_OUT(errp);
		else DZ1_IO_STREAM_FUNC(ret, SignalPhaseInfoDownBasic_read(dst->mandatory, src, ed, param, errp), errp);

		if (Dz1Stream_eof(src) == FALSE)
		{
			if ((dst->periodic_oper_time2 = SignalPhaseInfoPeriodicOperationTime_gen(errp)) == NULL) ERR_OUT(errp);
			else DZ1_IO_STREAM_FUNC(ret, SignalPhaseInfoPeriodicOperationTime_read(dst->periodic_oper_time2, src, ed, param, errp), errp);
		}

		if (Dz1Stream_eof(src) == FALSE)
		{
			if ((dst->periodic_oper_time3 = SignalPhaseInfoPeriodicOperationTime_gen(errp)) == NULL) ERR_OUT(errp);
			else DZ1_IO_STREAM_FUNC(ret, SignalPhaseInfoPeriodicOperationTime_read(dst->periodic_oper_time3, src, ed, param, errp), errp);
		}
	}
	return ret;
}
// SignalPhaseInfoDown_r27 CODEC
///////////////////////////////////////////////////////////////////////////////

static bool_t SignalPhaseInfoUpPPCControl_encode(u8_t* dst, size_t sz, SignalPhaseInfoUpPPCControl* src, Dz1Error* errp)
{
	if (dst == NULL || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = dst;
		*dp++ = src->ppc_blink_time;
		*dp++ = src->ppc_all_red_time;
		*dp++ = src->ppc_priority_signal;
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t SignalPhaseInfoUpPPCControl_decode(SignalPhaseInfoUpPPCControl* dst, u8_t* src, size_t sz, Dz1Error* errp)
{
	if (dst == NULL || sz < 3 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = src;
		dst->ppc_blink_time = *dp++;
		dst->ppc_all_red_time = *dp++;
		dst->ppc_priority_signal = *dp++;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static ssize_t SignalPhaseInfoUpPPCControl_write(Dz1Stream* dst, SignalPhaseInfoUpPPCControl* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[3] = { 0, };
		if (SignalPhaseInfoUpPPCControl_encode(data, sizeof(data), src, errp) == FALSE) ERR_OUT(errp);
		else DZ1_STREAM_WRITE(dst, data, sizeof(data), errp, ret);
	}
	return ret;
}

static ssize_t SignalPhaseInfoUpPPCControl_read(SignalPhaseInfoUpPPCControl* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[3];
		DZ1_STREAM_READ(data, sizeof(data), src, errp, ret);
		if (SignalPhaseInfoUpPPCControl_decode(dst, data, sizeof(data), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}


///////////////////////////////////////////////////////////////////////////////
// SignalPhaseInfoUp CODEC

ssize_t SignalPhaseInfoUp_write(Dz1Stream* dst, SignalPhaseInfoUp* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, SignalPhaseInfoPeriodicOperationTime_write(dst, src->operation_time, ed, param, errp), errp);
		if(src->pedestrianoperation_time) DZ1_IO_STREAM_FUNC(ret, SignalPhaseInfoPeriodicOperationTime_write(dst, src->pedestrianoperation_time, ed, param, errp), errp);
		if (src->ppc_control) DZ1_IO_STREAM_FUNC(ret, SignalPhaseInfoUpPPCControl_write(dst, src->ppc_control, ed, param, errp), errp);
	}
	return ret;
}




ssize_t SignalPhaseInfoUp_read(SignalPhaseInfoUp* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		if ((dst->operation_time = SignalPhaseInfoPeriodicOperationTime_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
		else DZ1_IO_STREAM_FUNC(ret, SignalPhaseInfoPeriodicOperationTime_read(dst->operation_time, src, ed, param, errp), errp);

		if (Dz1Stream_eof(src) == FALSE)
		{
			if ((dst->pedestrianoperation_time = SignalPhaseInfoPeriodicOperationTime_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, SignalPhaseInfoPeriodicOperationTime_read(dst->pedestrianoperation_time, src, ed, param, errp), errp);
		}

		if (Dz1Stream_eof(src) == FALSE)
		{
			if ((dst->ppc_control = SignalPhaseInfoUpPPCControl_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else DZ1_IO_STREAM_FUNC(ret, SignalPhaseInfoUpPPCControl_read(dst->ppc_control, src, ed, param, errp), errp);
		}
	}

	return ret;
}
// SignalPhaseInfoUp CODEC
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ClockInfo CODEC
static bool_t ClockInfo_encode(u8_t* dst, size_t sz, ClockInfo* src, Dz1Error* errp)
{
	if (dst == NULL || sz < 7 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = dst;
		*dp = 0x00;
		*dp++ = src->year;
		*dp++ = src->month;
		*dp++ = src->day;
		*dp++ = src->hour;
		*dp++ = src->minute;
		*dp++ = src->second;
		*dp++ = src->week_index;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t ClockInfo_decode(ClockInfo* dst, u8_t* src, size_t sz, Dz1Error* errp)
{
	if (dst == NULL || sz < 7 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = src;
		dst->year = *dp++;
		dst->month = *dp++;
		dst->day = *dp++;
		dst->hour = *dp++;
		dst->minute = *dp++;
		dst->second = *dp++;
		dst->week_index= *dp++;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

ssize_t ClockInfo_write(Dz1Stream* dst, ClockInfo* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp,EINVAL, -1);
	else
	{
		u8_t data[7] = { 0, };
		if (ClockInfo_encode(data, sizeof(data), src, errp) == FALSE) ERR_OUT(errp);
		else DZ1_STREAM_WRITE(dst, data, sizeof(data), errp, ret);
	}
	return ret;
}

ssize_t ClockInfo_read(ClockInfo* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[7] = { 0, };
		DZ1_STREAM_READ(data, sizeof(data), src, errp, ret);
		if (ClockInfo_decode(dst, data, sizeof(data), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}
// ClockInfo CODEC
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// SpecialCommandInfo CODEC
static bool_t SpecialCommandInfo_encode(u8_t* dst, size_t sz, SpecialCommandInfo* src, Dz1Error* errp)
{
	if (dst == NULL || sz < 20 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = dst;
		*dp = 0x00;
		// 1 Byte
		*dp |= src->is_shut_down ?			0x80 : 0x00;	
		*dp |= src->is_blink_control ?		0x40 : 0x00;	
		*dp |= src->is_lamp_light_control ?	0x20 : 0x00;	
		*dp |= src->is_confilct ?			0x10 : 0x00;	
		*dp |= src->is_manual ?				0x08 : 0x00;	
		*dp |= src->is_confilct_reset ?		0x04 : 0x00;	
		*dp |= src->is_scu_reset ?			0x02 : 0x00;	
		*dp |= src->is_mcu_reset ?			0x01 : 0x00;
		dp++;
		// 2 Byte
		*dp = 0x00;
		*dp |= src->is_ppc_control ?		0x80 : 0x00;	
		*dp |= src->is_pedestrian_button ?	0x40 : 0x00;	
		*dp |= src->is_x_control ?			0x20 : 0x00;	
		*dp |= src->is_spill_back_control ?	0x10 : 0x00;	
		*dp |= src->is_phase_omit ?			0x08 : 0x00;	
		*dp |= src->is_phase_hold ?			0x04 : 0x00;	
		*dp |= src->is_actuation_control ?	0x02 : 0x00;	
		*dp |= src->is_stagger_control ?	0x01 : 0x00;
		dp++;
		// 3 ~ 6 Byte
		*dp++ = src->operation_flag;
		*dp++ = src->hold_omit_phase;
		*dp++ = src->stagger_plan;
		*dp++ = src->spill_back_direction_code  >> 4 ;

		// 7 Byte
		*dp = 0x00;
		*dp |= ((u8_t)src->sub_phase_spill_back & 0xF) >> 4;
		*dp |= ((u8_t)src->main_phase_spill_back & 0xF);

		if (src->is_ppc_control && src->operation_flag == (u8_t)0x2)
		{
			SpecialCommandInfoPPCControlManage* ppc_control_manage = NULL;
			if ((ppc_control_manage = src->ppc_control_manage) == NULL) ERR_OUT(errp);
			else
			{
				dp++;
				*dp = 0x00;
				*dp |= ppc_control_manage->is_org_code_registered_vehicle_request ? 0x20 : 0x00;
				*dp |= ppc_control_manage->is_register_org_code					  ? 0x10 : 0x00;
				*dp |= ppc_control_manage->is_delete_org_code					  ? 0x08 : 0x00;
				*dp |= ppc_control_manage->is_register_org_code					  ? 0x04 : 0x00;
				*dp |= ppc_control_manage->is_delete_vehicle_num				  ? 0x02 : 0x00;
				*dp |= ppc_control_manage->vehicle_code							  ? 0x01 : 0x00;
				dp++;
				*dp++ = ppc_control_manage->org_manage_code;

				SpecialCommandPPCVehicleProperty* vehicle_prooerty = NULL;
				if ((vehicle_prooerty = ppc_control_manage->vehicle_property) == NULL) ERR_OUT(errp);
				else
				{
					*dp++ = (u8_t)((vehicle_prooerty->property >> 24) & 0xFF);
					*dp++ = (u8_t)((vehicle_prooerty->property >> 16) & 0xFF);
					*dp++ = (u8_t)((vehicle_prooerty->property >> 8) & 0xFF);
					*dp++ = (u8_t)((vehicle_prooerty->property >> 0) & 0xFF);
				}

			}
		}
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t SpeicalCommandInfo_decode(SpecialCommandInfo* dst, u8_t* src, size_t sz, Dz1Error* errp)
{
	if (dst == NULL || sz < 20 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = src;
		// 1 Byte
		dst->is_shut_down =				*dp & 0x80 ? TRUE : FALSE;
		dst->is_blink_control =			*dp & 0x40 ? TRUE: FALSE;
		dst->is_lamp_light_control =	*dp & 0x20 ? TRUE: FALSE;
		dst->is_confilct =				*dp & 0x10 ? TRUE: FALSE;
		dst->is_manual =				*dp & 0x08 ? TRUE: FALSE;
		dst->is_confilct_reset =		*dp & 0x04 ? TRUE: FALSE;
		dst->is_scu_reset =				*dp & 0x02 ? TRUE: FALSE;
		dst->is_mcu_reset =				*dp & 0x01 ? TRUE: FALSE;
		dp++;

		// 2 Byte
		dst->is_ppc_control			=	*dp & 0x80 ? TRUE : FALSE;
		dst->is_pedestrian_button	=	*dp & 0x40 ? TRUE: FALSE;
		dst->is_x_control			=	*dp & 0x20 ? TRUE: FALSE;
		dst->is_spill_back_control	=	*dp & 0x10 ? TRUE: FALSE;
		dst->is_phase_omit			=	*dp & 0x08 ? TRUE: FALSE;
		dst->is_phase_hold			=	*dp & 0x04 ? TRUE: FALSE;
		dst->is_actuation_control	=	*dp & 0x02 ? TRUE: FALSE;
		dst->is_stagger_control		=	*dp & 0x01 ? TRUE: FALSE;
		dp++;

		// 3 ~ 6 Byte
		dst->operation_flag = *dp++;
		dst->hold_omit_phase = *dp++;
		dst->stagger_plan = *dp++;
		dst->spill_back_direction_code = *dp++;

		// 7 Byte
		dst->sub_phase_spill_back = (u8_t)((*dp >> 4) & 0xF);
		dst->main_phase_spill_back = (u8_t)((*dp >> 0) & 0xF);
		dp++;

		if (dst->is_ppc_control = TRUE && dst->operation_flag == 2)
		{
			SpecialCommandInfoPPCControlManage* ppc = NULL;
			if ((ppc = dst->ppc_control_manage = SpecialCommandInfoPPCControlManage_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				ppc->is_org_code_registered_vehicle_request = *dp & 0x40 ? TRUE : FALSE;
				ppc->is_register_org_code = *dp & 0x20 ? TRUE : FALSE;
				ppc->is_delete_org_code = *dp & 0x10 ? TRUE : FALSE;
				ppc->is_register_vehicle_num = *dp & 0x08 ? TRUE : FALSE;
				ppc->is_delete_vehicle_num = *dp & 0x04 ? TRUE : FALSE;
				ppc->vehicle_code = *dp & 0x02 ? TRUE : FALSE;
				dp++;
				ppc->org_manage_code = *dp++;
				ppc->vehicle_property = SpecialCommandPPCVehicleProperty_gen(errp);
				memcpy(ppc->vehicle_property, dp, 4);
			}
		}
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

ssize_t SpecialCommandInfo_write(Dz1Stream* dst, SpecialCommandInfo* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[20] = { 0, };
		if (SpecialCommandInfo_encode(data, sizeof(data), src, errp) == FALSE) ERR_OUT(errp);
		else DZ1_STREAM_WRITE(dst, data, sizeof(data), errp, ret);
	}
	return ret;
}


ssize_t SpecialCommandInfo_read(SpecialCommandInfo* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[20] = { 0, };
		DZ1_STREAM_READ(data, sizeof(data), src, errp, ret);
		if (SpeicalCommandInfo_decode(dst, data, sizeof(data), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}
// SpecialCommandInfo CODEC
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// SpecialCommandPPCNumberList CODEC

static bool_t SpecialCommandPPCNumberList_is_emergency_encode(u8_t* dst, size_t sz, SpecialCommandPPCNumberList_is_emergency* src, Dz1Error* errp)
{
	if (dst == NULL || sz < 1 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = dst;
		*dp = 0x00;
		*dp = (u8_t)src->is_emergency;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}
static bool_t SpecialCommandPPCNumberList_org_code_encode(u8_t* dst, size_t sz, SpecialCommandPPCNumberList_org_code* src, Dz1Error* errp)
{
	if (dst == NULL || sz < 1 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = dst;
		*dp = src->org_code;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}
static bool_t SpecialCommandPPCNumberList_org_code_num_encode(u8_t* dst, size_t sz, SpecialCommandPPCNumberList_org_code_num* src, Dz1Error* errp)
{
	if (dst == NULL || sz < 1 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = dst;
		*dp = src->org_code_num;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t SpecialCommandPPCNumberList_org_code_type_encode(u8_t* dst, size_t sz, SpecialCommandPPCNumberList_org_code_type* src, Dz1Error* errp)
{
	if (dst == NULL || sz < 4 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = dst;
		*dp = 0x00;
		*dp |= (u8_t)((src->org_code_type >> 24) & 0xFF);
		*dp |= (u8_t)((src->org_code_type >> 16) & 0xFF);
		*dp |= (u8_t)((src->org_code_type >> 8) & 0xFF);
		*dp |= (u8_t)((src->org_code_type >> 0) & 0xFF);
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t SpecialCommandPPCVehicleProperty_encode(u8_t* dst, size_t sz, SpecialCommandPPCVehicleProperty* src, Dz1Error* errp)
{
	if (dst == NULL || sz < 4 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = dst;
		*dp = 0x00;
		*dp++ = (u8_t)((src->property >> 24) & 0xFF);
		*dp++ = (u8_t)((src->property >> 16) & 0xFF);
		*dp++ = (u8_t)((src->property >> 8) & 0xFF);
		*dp++ = (u8_t)((src->property >> 0) & 0xFF);
	}
	return ERR_IS_SUCCESS(errp);
}

static ssize_t SpecialCommandPPCNumberList_is_emergency_write(Dz1Stream* dst, SpecialCommandPPCNumberList_is_emergency* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[1] = { 0, };
		if (SpecialCommandPPCNumberList_is_emergency_encode(data, sizeof(data), src, errp) == FALSE) ERR_OUT(errp);
		else DZ1_STREAM_WRITE(dst, data, sizeof(data), errp, ret);
	}
	return ret;
}
static ssize_t SpecialCommandPPCNumberList_org_code_write(Dz1Stream* dst, SpecialCommandPPCNumberList_org_code* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[1] = { 0, };
		if (SpecialCommandPPCNumberList_org_code_encode(data, sizeof(data), src, errp) == FALSE) ERR_OUT(errp);
		else DZ1_STREAM_WRITE(dst, data, sizeof(data), errp, ret);
	}
	return ret;
}
static ssize_t SpecialCommandPPCNumberList_org_code_num_write(Dz1Stream* dst, SpecialCommandPPCNumberList_org_code_num* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[1] = { 0, };
		if (SpecialCommandPPCNumberList_org_code_num_encode(data, sizeof(data), src, errp) == FALSE) ERR_OUT(errp);
		else DZ1_STREAM_WRITE(dst, data, sizeof(data), errp, ret);
	}
	return ret;
}

static ssize_t SpecialCommandPPCNumberList_org_code_type_write(Dz1Stream* dst, SpecialCommandPPCNumberList_org_code_type* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[4] = { 0, };
		if (SpecialCommandPPCNumberList_org_code_type_encode(data, sizeof(data), src, errp) == FALSE) ERR_OUT(errp);
		else DZ1_STREAM_WRITE(dst, data, sizeof(data), errp, ret);
	}
	return ret;
}

static ssize_t SpecialCommandPPCVehicleProperty_write(Dz1Stream *dst, SpecialCommandPPCVehicleProperty *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[4] = { 0, };
		if (SpecialCommandPPCVehicleProperty_encode(data, sizeof(data), src, errp) == FALSE) ERR_OUT(errp);
		else DZ1_STREAM_WRITE(dst, data, sizeof(data), errp, ret);
	}

	return ret;
}

static ssize_t SpecialCommandPPCVehicleProperties_write(Dz1Stream* dst, SpecialCommandPPCVehicleProperties* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		SpecialCommandPPCVehicleProperties* list = NULL;
		int cnt = 0;
		if ((list = SpecialCommandPPCVehicleProperties_clone(src, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(SpecialCommandPPCVehicleProperties_delAndSetNull, (void*)&list);
			cnt = list->count(list);

			while (cnt > 0 && errp->code == 0)
			{
				SpecialCommandPPCVehicleProperty* entry = NULL;
				if ((entry = list->extract(list, NULL)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(SpecialCommandPPCVehicleProperty_delAndSetNull, (void*)&entry);
					DZ1_IO_STREAM_FUNC(ret, SpecialCommandPPCVehicleProperty_write(dst, entry, ed, param, errp), errp);
					entry = NULL;
					pthread_cleanup_pop(1); // (SpecialCommandPPCVehicleProperty_delAndSetNull, (void*)&entry);
					cnt = list->count(list);

				}
			}

			pthread_cleanup_pop(1); // (SpecialCommandPPCVehicleProperties_delAndSetNull, (void*)&list);
		}
	}
	return ret;
}


ssize_t SpecialCommandPPCNumberList_write(Dz1Stream* dst, SpecialCommandPPCNumberList* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) Dz1Error_set(errp, 0);
	else
	{
		if (src->is_emergency == NULL) Dz1Error_set(errp, 0);
		else
		{
			DZ1_IO_STREAM_FUNC(ret, SpecialCommandPPCNumberList_is_emergency_write(dst, src->is_emergency, ed, param, errp), errp);
			if (src->org_code == NULL) Dz1Error_set(errp, 0);
			else
			{
				DZ1_IO_STREAM_FUNC(ret, SpecialCommandPPCNumberList_org_code_write(dst, src->org_code, ed, param, errp), errp);
				if (src->org_code_num == NULL) Dz1Error_set(errp, 0);
				else
				{
					DZ1_IO_STREAM_FUNC(ret, SpecialCommandPPCNumberList_org_code_num_write(dst, src->org_code_num, ed, param, errp), errp);
					if (src->org_code_type == NULL) Dz1Error_set(errp, 0);
					else
					{
						DZ1_IO_STREAM_FUNC(ret, SpecialCommandPPCNumberList_org_code_type_write(dst, src->org_code_type, ed, param, errp), errp);
						if (src->vehicle_properties == NULL) Dz1Error_set(errp, 0);
						else
						{
							DZ1_IO_STREAM_FUNC(ret, SpecialCommandPPCVehicleProperties_write(dst, src->vehicle_properties, ed, param, errp), errp);
						}
					}
				}
			}
		}
	}
	return ret;
}

static bool_t SpecialCommandPPCNumberList_is_emergency_decode(SpecialCommandPPCNumberList_is_emergency* dst, u8_t* src, size_t sz, Dz1Error* errp)
{
	if (dst == NULL || sz < 1 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = src;
		dst->is_emergency = *dp;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static ssize_t SpecialCommandPPCNumberList_is_emergency_read(SpecialCommandPPCNumberList_is_emergency* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[1] = { 0, };
		DZ1_STREAM_READ(data, sizeof(data), src, errp, ret);
		if (SpecialCommandPPCNumberList_is_emergency_decode(dst, data, sizeof(data), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}

static bool_t SpecialCommandPPCNumberList_org_code_decode(SpecialCommandPPCNumberList_org_code* dst, u8_t* src, size_t sz, Dz1Error* errp)
{
	if (dst == NULL || sz < 1 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = src;
		dst->org_code = *dp;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static ssize_t SpecialCommandPPCNumberList_org_code_read(SpecialCommandPPCNumberList_org_code* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[1] = { 0, };
		DZ1_STREAM_READ(data, sizeof(data), src, errp, ret);
		if (SpecialCommandPPCNumberList_org_code_decode(dst, data, sizeof(data), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}

static bool_t SpecialCommandPPCNumberList_org_code_num_decode(SpecialCommandPPCNumberList_org_code_num* dst, u8_t* src, size_t sz, Dz1Error* errp)
{
	if (dst == NULL || sz < 1 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = src;
		dst->org_code_num = *dp;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static ssize_t SpecialCommandPPCNumberList_org_code_num_read(SpecialCommandPPCNumberList_org_code_num* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[1] = { 0, };
		DZ1_STREAM_READ(data, sizeof(data), src, errp, ret);
		if (SpecialCommandPPCNumberList_org_code_num_decode(dst, data, sizeof(data), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}

static bool_t SpecialCommandPPCNumberList_org_code_type_decode(SpecialCommandPPCNumberList_org_code_type* dst, u8_t* src, size_t sz, Dz1Error* errp)
{
	if (dst == NULL || sz < 1 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = src;
		dst->org_code_type = *dp;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static ssize_t SpecialCommandPPCNumberList_org_code_type_read(SpecialCommandPPCNumberList_org_code_type* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[1] = { 0, };
		DZ1_STREAM_READ(data, sizeof(data), src, errp, ret);
		if (SpecialCommandPPCNumberList_org_code_type_decode(dst, data, sizeof(data), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}

static bool_t SpecialCommandPPCVehicleProperty_decode(SpecialCommandPPCVehicleProperty* dst, u8_t* src, size_t sz, Dz1Error* errp)
{
	if (dst == NULL || sz < 4 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = src;
		dst->property = 0;
		dst->property = (dst->property << 8) | ((u32_t)*dp & 0xFF); dp++;
		dst->property = (dst->property << 8) | ((u32_t)*dp & 0xFF); dp++;
		dst->property = (dst->property << 8) | ((u32_t)*dp & 0xFF); dp++;
		dst->property = (dst->property << 8) | ((u32_t)*dp & 0xFF); dp++;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static ssize_t SpecialCommandPPCVehicleProperties_read(SpecialCommandPPCVehicleProperties* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		while (errp->code == 0 && Dz1Stream_eof(src) == FALSE && ret < 200)
		{
			SpecialCommandPPCVehicleProperty* entry = NULL;
			if((entry = SpecialCommandPPCVehicleProperty_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(SpecialCommandPPCVehicleProperty_delAndSetNull, (void*)&entry);
				u8_t data[4] = { 0, };
				DZ1_STREAM_READ(data, sizeof(data), src, errp, ret);
				if (SpecialCommandPPCVehicleProperty_decode(entry, data, sizeof(data), errp) == FALSE) ERR_OUT(errp);
				else
				{
					if ((*errp = dst->add(dst, entry)).code) ERR_OUT(errp);
					else
					{
						entry = NULL;
						Dz1Error_set(errp, 0);
					}
				}
				pthread_cleanup_pop(1) ; //(SpecialCommandPPCVehicleProperty_delAndSetNull, (void *)&entry);
			}
		}
	}
	return ret;
}

ssize_t SpecialCommandPPCNumberList_read(SpecialCommandPPCNumberList* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		if (Dz1Stream_eof(src) == FALSE)
		{
			if ((dst->is_emergency = SpecialCommandPPCNumberList_is_emergency_gen(errp)) == NULL);
			else DZ1_IO_STREAM_FUNC(ret, SpecialCommandPPCNumberList_is_emergency_read(dst->is_emergency, src, ed, param, errp), errp);
		}

		if (Dz1Stream_eof(src) == FALSE)
		{
			if ((dst->org_code = SpecialCommandPPCNumberList_org_code_gen(errp)) == NULL);
			else DZ1_IO_STREAM_FUNC(ret, SpecialCommandPPCNumberList_org_code_read(dst->org_code, src, ed, param, errp), errp);
		}

		if (Dz1Stream_eof(src) == FALSE)
		{
			if ((dst->org_code_num = SpecialCommandPPCNumberList_org_code_num_gen(errp)) == NULL);
			else DZ1_IO_STREAM_FUNC(ret, SpecialCommandPPCNumberList_org_code_num_read(dst->org_code_num, src, ed, param, errp), errp);
		}

		if (Dz1Stream_eof(src) == FALSE)
		{
			if ((dst->org_code_type = SpecialCommandPPCNumberList_org_code_type_gen(errp)) == NULL);
			else DZ1_IO_STREAM_FUNC(ret, SpecialCommandPPCNumberList_org_code_type_read(dst->org_code_type, src, ed, param, errp), errp);
		}

		if (Dz1Stream_eof(src) == FALSE)
		{
			if ((dst->vehicle_properties = SpecialCommandPPCVehicleProperties_gen(errp)) == NULL);
			else DZ1_IO_STREAM_FUNC(ret, SpecialCommandPPCVehicleProperties_read(dst->vehicle_properties, src, ed, param, errp), errp);
		}
	}
	return ret;
}
// SpecialCommandPPCNumberList CODEC
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// FirmwareUpgradeData CODEC
static bool_t FirmwareUpgradeData_encode(u8_t* dst, size_t sz, FirmwareUpgradeData* src, Dz1Error* errp)
{
	if (dst == NULL || sz < 32 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = dst;
		// 1 ~ 2 Byte
		*dp = 0x00;
		*dp++ = (u8_t)((src->fw_module_id >> 8) & 0xFF);
		*dp++ = (u8_t)((src->fw_module_id >> 0) & 0xFF);

		// 3 ~ 6 Byte
		*dp = 0x00;
		*dp++ = (u8_t)((src->fw_module_size >> 24) & 0xFF);
		*dp++ = (u8_t)((src->fw_module_size >> 16) & 0xFF);
		*dp++ = (u8_t)((src->fw_module_size >> 8) & 0xFF);
		*dp++ = (u8_t)((src->fw_module_size >> 0) & 0xFF);

		// 7 ~ 21 Byte
		memcpy(dp, src->fname, 15);
		dp += 15;

		// 22 ~ 26 Byte : major.minor.module.revision(2B)
		*dp++ = src->major_version;
		*dp++ = src->minor_version;
		*dp++ = src->module_version;
		*dp++ = (u8_t)((src->revision_version >> 8) & 0xFF);
		*dp++ = (u8_t)((src->revision_version >> 0) & 0xFF);

		// 27 Byte
		*dp++ = src->is_forced_upgrade;

		// 28 Byte;
		*dp++ = src->reboot_option;

		// 29 ~ 32 Byte;
		*dp++ = (u8_t)((src->crc32 >> 24) & 0xFF);
		*dp++ = (u8_t)((src->crc32 >> 16) & 0xFF);
		*dp++ = (u8_t)((src->crc32 >> 8) & 0xFF);
		*dp++ = (u8_t)((src->crc32 >> 0) & 0xFF);
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t FirmwareUpgradeData_decode(FirmwareUpgradeData* dst, u8_t* src, size_t sz, Dz1Error* errp)
{
	if (dst == NULL || sz < 32 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = src;
		// 1 ~ 2 Byte
		dst->fw_module_id = 0;
		dst->fw_module_id = (dst->fw_module_id << 8) | (u16_t)(*dp & 0xFF); dp++;
		dst->fw_module_id = (dst->fw_module_id << 8) | (u16_t)(*dp & 0xFF); dp++;
		// 3 ~ 6 Byte
		dst->fw_module_size = 0;
		dst->fw_module_size = (dst->fw_module_size << 8) | (u32_t)(*dp & 0xFF); dp++;
		dst->fw_module_size = (dst->fw_module_size << 8) | (u32_t)(*dp & 0xFF); dp++;
		dst->fw_module_size = (dst->fw_module_size << 8) | (u32_t)(*dp & 0xFF); dp++;
		dst->fw_module_size = (dst->fw_module_size << 8) | (u32_t)(*dp & 0xFF); dp++;
		
		// 7 ~ 21 Byte
		dst->fname = Dz1Str_ndup(dp, 15, errp);
		//memcpy(dst->fname, dp, 15);
		dp += 15;
		// 22 Byte
		dst->major_version = *dp++;
		// 23 Byte
		dst->minor_version = *dp++;
		// 24 Byte
		dst->module_version = *dp++;
		// 25 ~ 26 Byte
		dst->revision_version = 0;
		dst->revision_version = (dst->revision_version >> 8) | (u16_t)(*dp & 0xFF); dp++;
		dst->revision_version = (dst->revision_version >> 8) | (u16_t)(*dp & 0xFF); dp++;
		// 27 Byte
		dst->is_forced_upgrade = (*dp & 0x01) ? TRUE : FALSE;
		*dp++;
		// 28 Byte
		dst->reboot_option = *dp++;
		// 29 ~ 32 Byte
		dst->crc32 = 0;
		dst->crc32 = (dst->crc32 << 8) | (u32_t)(*dp & 0xFF); dp++;
		dst->crc32 = (dst->crc32 << 8) | (u32_t)(*dp & 0xFF); dp++;
		dst->crc32 = (dst->crc32 << 8) | (u32_t)(*dp & 0xFF); dp++;
		dst->crc32 = (dst->crc32 << 8) | (u32_t)(*dp & 0xFF); dp++;
	}

	return ERR_IS_SUCCESS(errp);
}

ssize_t FirmwareUpgradeData_write(Dz1Stream* dst, FirmwareUpgradeData* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[32] = { 0, };
		if (FirmwareUpgradeData_encode(data, sizeof(data), src, errp) == FALSE) ERR_OUT(errp);
		else DZ1_STREAM_WRITE(dst, data, sizeof(data), errp, ret);
	}
	return ret;
}

ssize_t FirmwareUpgradeData_read(FirmwareUpgradeData* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[32] = { 0, };
		DZ1_STREAM_READ(data, sizeof(data), src, errp, ret);
		if (FirmwareUpgradeData_decode(dst, data, sizeof(data), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}

	return ret;
}
// FirmwareUpgradeData CODEC
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// FirmwareUpgradeError CODEC
static bool_t FirmwareUpgradeError_encode(u8_t* dst, size_t sz, FirmwareUpgradeError* src, Dz1Error* errp)
{
	if (dst == NULL || sz < 1 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = dst;
		*dp = (u8_t)(src->code & 0xFF);
	}
	return ERR_IS_SUCCESS(errp);
}

ssize_t FirmwareUpgradeError_write(Dz1Stream* dst, FirmwareUpgradeError* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[1] = { 0, };
		if (FirmwareUpgradeError_encode(data, sizeof(data), src, errp) == FALSE) ERR_OUT(errp);
		else DZ1_STREAM_WRITE(dst, data, sizeof(data), errp, ret);
	}

	return ret;
}
static bool_t FirmwareUpgradeError_decode(FirmwareUpgradeError* dst, u8_t* src, size_t sz, Dz1Error* errp)
{
	if (dst == NULL || sz < 1 || src == NULL) ERR_OUT(errp);
	else
	{
		u8_t* dp = src;
		dst->code = (FirmwareUpgradeErrorCode)(*dp & 0xFF);
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

ssize_t FirmwareUpgradeError_read(FirmwareUpgradeError* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = 0;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		u8_t data[1] = { 0, };
		DZ1_STREAM_READ(data, sizeof(data), src, errp, ret);
		if (FirmwareUpgradeError_decode(dst, data, sizeof(data), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}
// FirmwareUpgradeError CODEC
///////////////////////////////////////////////////////////////////////////////
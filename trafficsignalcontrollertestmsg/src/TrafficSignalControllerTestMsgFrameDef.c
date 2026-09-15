////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "TrafficSignalControllerTestMsgFrameDef.h"

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerTestMsgFrame_status_response
TrafficSignalControllerTestMsgFrame_status_response *TrafficSignalControllerTestMsgFrame_status_response_new(CrossStatusBasicInfo *lc_status, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerTestMsgFrame_status_response *__internal_ret = (TrafficSignalControllerTestMsgFrame_status_response *)Dz1Calloc(sizeof(TrafficSignalControllerTestMsgFrame_status_response), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerTestMsgFrame_status_response_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->lc_status = lc_status;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerTestMsgFrame_status_response_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t TrafficSignalControllerTestMsgFrame_status_response_copy(TrafficSignalControllerTestMsgFrame_status_response *dst, TrafficSignalControllerTestMsgFrame_status_response *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->lc_status && (dst->lc_status = CrossStatusBasicInfo_clone(src->lc_status, errp)) == NULL) ERR_OUT(errp);
	else if (src->ex_status && (dst->ex_status = CrossStatusExtInfo_r27_clone(src->ex_status, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TrafficSignalControllerTestMsgFrame_status_response *TrafficSignalControllerTestMsgFrame_status_response_clone(TrafficSignalControllerTestMsgFrame_status_response *src, Dz1Error *err)
{
	TrafficSignalControllerTestMsgFrame_status_response *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (TrafficSignalControllerTestMsgFrame_status_response *)Dz1Calloc(sizeof(TrafficSignalControllerTestMsgFrame_status_response), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerTestMsgFrame_status_response_delAndSetNull, (void *)&dst);
		if (TrafficSignalControllerTestMsgFrame_status_response_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerTestMsgFrame_status_response_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void TrafficSignalControllerTestMsgFrame_status_response_purge(TrafficSignalControllerTestMsgFrame_status_response *p)
{
	if (p == NULL) return;
	CrossStatusBasicInfo_del(p->lc_status);
	CrossStatusExtInfo_r27_del(p->ex_status);
}

void TrafficSignalControllerTestMsgFrame_status_response_del(TrafficSignalControllerTestMsgFrame_status_response *p)
{
	if (p == NULL) return;
	TrafficSignalControllerTestMsgFrame_status_response_purge(p);
	Dz1Free(p);
}

void TrafficSignalControllerTestMsgFrame_status_response_dump(TrafficSignalControllerTestMsgFrame_status_response *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("lc_status = ")); CrossStatusBasicInfo_dump(p->lc_status, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("ex_status = ")); CrossStatusExtInfo_r27_dump(p->ex_status, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// TrafficSignalControllerTestMsgFrame_status_response
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerTestMsgFrameContextPresent
static struct TrafficSignalControllerTestMsgFrameContextPresentMapA
{
	str_t str;
	TrafficSignalControllerTestMsgFrameContextPresent v;
} TrafficSignalControllerTestMsgFrameContextPresentMapA[] =
{
	{ (char *)"control_req", TrafficSignalControllerTestMsgFrameContextPresent_control_req },
	{ (char *)"control_rsp", TrafficSignalControllerTestMsgFrameContextPresent_control_rsp },
	{ (char *)"status_req", TrafficSignalControllerTestMsgFrameContextPresent_status_req },
	{ (char *)"status_rsp", TrafficSignalControllerTestMsgFrameContextPresent_status_rsp },
	{ (char *)"detector_req", TrafficSignalControllerTestMsgFrameContextPresent_detector_req },
	{ (char *)"detector_rsp", TrafficSignalControllerTestMsgFrameContextPresent_detector_rsp },
	{ (char *)"signal_phase_download_req", TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_download_req },
	{ (char *)"signal_phase_download_rsp", TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_download_rsp },
	{ (char *)"signal_phase_upload_req", TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_upload_req },
	{ (char *)"signal_phase_upload_rsp", TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_upload_rsp },
	{ (char *)"clock_download_req", TrafficSignalControllerTestMsgFrameContextPresent_clock_download_req },
	{ (char *)"clock_download_rsp", TrafficSignalControllerTestMsgFrameContextPresent_clock_download_rsp },
	{ (char *)"clock_upload_req", TrafficSignalControllerTestMsgFrameContextPresent_clock_upload_req },
	{ (char *)"clock_upload_rsp", TrafficSignalControllerTestMsgFrameContextPresent_clock_upload_rsp },
	{ (char *)"special_command_req", TrafficSignalControllerTestMsgFrameContextPresent_special_command_req },
	{ (char *)"special_command_rsp", TrafficSignalControllerTestMsgFrameContextPresent_special_command_rsp },
	{ (char *)"fw_upgrade_req", TrafficSignalControllerTestMsgFrameContextPresent_fw_upgrade_req },
	{ (char *)"fw_upgrade_rsp", TrafficSignalControllerTestMsgFrameContextPresent_fw_upgrade_rsp },
	{ NULL, TrafficSignalControllerTestMsgFrameContextPresent_max }
};

str_t TrafficSignalControllerTestMsgFrameContextPresentStrA(TrafficSignalControllerTestMsgFrameContextPresent v)
{
	struct TrafficSignalControllerTestMsgFrameContextPresentMapA *i = NULL;
	for (i = TrafficSignalControllerTestMsgFrameContextPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

TrafficSignalControllerTestMsgFrameContextPresent TrafficSignalControllerTestMsgFrameContextPresentFromStrA(str_t str)
{
	struct TrafficSignalControllerTestMsgFrameContextPresentMapA *i = NULL;
	for (i = TrafficSignalControllerTestMsgFrameContextPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return TrafficSignalControllerTestMsgFrameContextPresent_max;
}
#ifndef UNIX_SYSTEM
static struct TrafficSignalControllerTestMsgFrameContextPresentMapW
{
	wstr_t str;
	TrafficSignalControllerTestMsgFrameContextPresent v;
} TrafficSignalControllerTestMsgFrameContextPresentMapW[] =
{
	{ (wchar_t *)L"control_req", TrafficSignalControllerTestMsgFrameContextPresent_control_req },
	{ (wchar_t *)L"control_rsp", TrafficSignalControllerTestMsgFrameContextPresent_control_rsp },
	{ (wchar_t *)L"status_req", TrafficSignalControllerTestMsgFrameContextPresent_status_req },
	{ (wchar_t *)L"status_rsp", TrafficSignalControllerTestMsgFrameContextPresent_status_rsp },
	{ (wchar_t *)L"detector_req", TrafficSignalControllerTestMsgFrameContextPresent_detector_req },
	{ (wchar_t *)L"detector_rsp", TrafficSignalControllerTestMsgFrameContextPresent_detector_rsp },
	{ (wchar_t *)L"signal_phase_download_req", TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_download_req },
	{ (wchar_t *)L"signal_phase_download_rsp", TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_download_rsp },
	{ (wchar_t *)L"signal_phase_upload_req", TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_upload_req },
	{ (wchar_t *)L"signal_phase_upload_rsp", TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_upload_rsp },
	{ (wchar_t *)L"clock_download_req", TrafficSignalControllerTestMsgFrameContextPresent_clock_download_req },
	{ (wchar_t *)L"clock_download_rsp", TrafficSignalControllerTestMsgFrameContextPresent_clock_download_rsp },
	{ (wchar_t *)L"clock_upload_req", TrafficSignalControllerTestMsgFrameContextPresent_clock_upload_req },
	{ (wchar_t *)L"clock_upload_rsp", TrafficSignalControllerTestMsgFrameContextPresent_clock_upload_rsp },
	{ (wchar_t *)L"special_command_req", TrafficSignalControllerTestMsgFrameContextPresent_special_command_req },
	{ (wchar_t *)L"special_command_rsp", TrafficSignalControllerTestMsgFrameContextPresent_special_command_rsp },
	{ (wchar_t *)L"fw_upgrade_req", TrafficSignalControllerTestMsgFrameContextPresent_fw_upgrade_req },
	{ (wchar_t *)L"fw_upgrade_rsp", TrafficSignalControllerTestMsgFrameContextPresent_fw_upgrade_rsp },
	{ NULL, TrafficSignalControllerTestMsgFrameContextPresent_max }
};

wstr_t TrafficSignalControllerTestMsgFrameContextPresentStrW(TrafficSignalControllerTestMsgFrameContextPresent v)
{
	struct TrafficSignalControllerTestMsgFrameContextPresentMapW *i = NULL;
	for (i = TrafficSignalControllerTestMsgFrameContextPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

TrafficSignalControllerTestMsgFrameContextPresent TrafficSignalControllerTestMsgFrameContextPresentFromStrW(wstr_t str)
{
	struct TrafficSignalControllerTestMsgFrameContextPresentMapW *i = NULL;
	for (i = TrafficSignalControllerTestMsgFrameContextPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return TrafficSignalControllerTestMsgFrameContextPresent_max;
}
#endif // UNIX_SYSTEM

TrafficSignalControllerTestMsgFrameContextPresent *TrafficSignalControllerTestMsgFrameContextPresent_new(TrafficSignalControllerTestMsgFrameContextPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerTestMsgFrameContextPresent *__internal_ret = (TrafficSignalControllerTestMsgFrameContextPresent *)Dz1Calloc(sizeof(TrafficSignalControllerTestMsgFrameContextPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void TrafficSignalControllerTestMsgFrameContextPresent_dump(TrafficSignalControllerTestMsgFrameContextPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), TrafficSignalControllerTestMsgFrameContextPresentStr(*v));
}
// TrafficSignalControllerTestMsgFrameContextPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerTestMsgFrameContext
TrafficSignalControllerTestMsgFrameContext *TrafficSignalControllerTestMsgFrameContext_new(TrafficSignalControllerTestMsgFrameContextPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerTestMsgFrameContext *ret = (TrafficSignalControllerTestMsgFrameContext *)Dz1Calloc(sizeof(TrafficSignalControllerTestMsgFrameContext), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerTestMsgFrameContext_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case TrafficSignalControllerTestMsgFrameContextPresent_control_req:
			// _U_cst_clone
			if (ptr != NULL) ret->x.control_req = (CrossControlCmd *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_control_rsp:
			// _U_cst_clone
			if (ptr != NULL) ret->x.control_rsp = (CrossIndicator *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_status_req:
			// _U_cst_clone
			if (ptr != NULL) ret->x.status_req = (CrossIndicator *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_status_rsp:
			// _U_cst_clone
			if (ptr != NULL) ret->x.status_rsp = (TrafficSignalControllerTestMsgFrame_status_response *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_detector_req:
			// _U_cst_clone
			if (ptr != NULL) ret->x.detector_req = (CrossIndicator *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_detector_rsp:
			// _U_cst_clone
			if (ptr != NULL) ret->x.detector_rsp = (DetectorInfo *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_download_req:
			// _U_cst_clone
			if (ptr != NULL) ret->x.signal_phase_download_req = (SignalPhaseInfoDown_r27 *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_download_rsp:
			// _U_cst_clone
			if (ptr != NULL) ret->x.signal_phase_download_rsp = (CrossIndicator *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_upload_req:
			// _U_cst_clone
			if (ptr != NULL) ret->x.signal_phase_upload_req = (CrossIndicator *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_upload_rsp:
			// _U_cst_clone
			if (ptr != NULL) ret->x.signal_phase_upload_rsp = (SignalPhaseInfoUp *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_clock_download_req:
			// _U_cst_clone
			if (ptr != NULL) ret->x.clock_download_req = (ClockInfo *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_clock_download_rsp:
			// _U_cst_clone
			if (ptr != NULL) ret->x.clock_download_rsp = (CrossIndicator *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_clock_upload_req:
			// _U_cst_clone
			if (ptr != NULL) ret->x.clock_upload_req = (CrossIndicator *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_clock_upload_rsp:
			// _U_cst_clone
			if (ptr != NULL) ret->x.clock_upload_rsp = (ClockInfo *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_special_command_req:
			// _U_cst_clone
			if (ptr != NULL) ret->x.special_command_req = (SpecialCommandInfo *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_special_command_rsp:
			// _U_cst_clone
			if (ptr != NULL) ret->x.special_command_rsp = (SpecialCommandPPCNumberList *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_fw_upgrade_req:
			// _U_cst_clone
			if (ptr != NULL) ret->x.fw_upgrade_req = (FirmwareUpgradeData *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_fw_upgrade_rsp:
			// _U_cst_clone
			if (ptr != NULL) ret->x.fw_upgrade_rsp = (FirmwareUpgradeError *)ptr;
			ERR_CLEAR(errp);
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerTestMsgFrameContext_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t TrafficSignalControllerTestMsgFrameContext_copy(TrafficSignalControllerTestMsgFrameContext *ret, TrafficSignalControllerTestMsgFrameContext *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case TrafficSignalControllerTestMsgFrameContextPresent_control_req:
			// _U_cst_clone
			if (src->x.control_req && (ret->x.control_req = CrossControlCmd_clone(src->x.control_req, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_control_rsp:
			// _U_cst_clone
			if (src->x.control_rsp && (ret->x.control_rsp = CrossIndicator_clone(src->x.control_rsp, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_status_req:
			// _U_cst_clone
			if (src->x.status_req && (ret->x.status_req = CrossIndicator_clone(src->x.status_req, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_status_rsp:
			// _U_cst_clone
			if (src->x.status_rsp && (ret->x.status_rsp = TrafficSignalControllerTestMsgFrame_status_response_clone(src->x.status_rsp, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_detector_req:
			// _U_cst_clone
			if (src->x.detector_req && (ret->x.detector_req = CrossIndicator_clone(src->x.detector_req, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_detector_rsp:
			// _U_cst_clone
			if (src->x.detector_rsp && (ret->x.detector_rsp = DetectorInfo_clone(src->x.detector_rsp, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_download_req:
			// _U_cst_clone
			if (src->x.signal_phase_download_req && (ret->x.signal_phase_download_req = SignalPhaseInfoDown_r27_clone(src->x.signal_phase_download_req, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_download_rsp:
			// _U_cst_clone
			if (src->x.signal_phase_download_rsp && (ret->x.signal_phase_download_rsp = CrossIndicator_clone(src->x.signal_phase_download_rsp, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_upload_req:
			// _U_cst_clone
			if (src->x.signal_phase_upload_req && (ret->x.signal_phase_upload_req = CrossIndicator_clone(src->x.signal_phase_upload_req, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_upload_rsp:
			// _U_cst_clone
			if (src->x.signal_phase_upload_rsp && (ret->x.signal_phase_upload_rsp = SignalPhaseInfoUp_clone(src->x.signal_phase_upload_rsp, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_clock_download_req:
			// _U_cst_clone
			if (src->x.clock_download_req && (ret->x.clock_download_req = ClockInfo_clone(src->x.clock_download_req, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_clock_download_rsp:
			// _U_cst_clone
			if (src->x.clock_download_rsp && (ret->x.clock_download_rsp = CrossIndicator_clone(src->x.clock_download_rsp, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_clock_upload_req:
			// _U_cst_clone
			if (src->x.clock_upload_req && (ret->x.clock_upload_req = CrossIndicator_clone(src->x.clock_upload_req, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_clock_upload_rsp:
			// _U_cst_clone
			if (src->x.clock_upload_rsp && (ret->x.clock_upload_rsp = ClockInfo_clone(src->x.clock_upload_rsp, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_special_command_req:
			// _U_cst_clone
			if (src->x.special_command_req && (ret->x.special_command_req = SpecialCommandInfo_clone(src->x.special_command_req, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_special_command_rsp:
			// _U_cst_clone
			if (src->x.special_command_rsp && (ret->x.special_command_rsp = SpecialCommandPPCNumberList_clone(src->x.special_command_rsp, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_fw_upgrade_req:
			// _U_cst_clone
			if (src->x.fw_upgrade_req && (ret->x.fw_upgrade_req = FirmwareUpgradeData_clone(src->x.fw_upgrade_req, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TrafficSignalControllerTestMsgFrameContextPresent_fw_upgrade_rsp:
			// _U_cst_clone
			if (src->x.fw_upgrade_rsp && (ret->x.fw_upgrade_rsp = FirmwareUpgradeError_clone(src->x.fw_upgrade_rsp, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TrafficSignalControllerTestMsgFrameContext *TrafficSignalControllerTestMsgFrameContext_clone(TrafficSignalControllerTestMsgFrameContext *src, Dz1Error *err)
{
	TrafficSignalControllerTestMsgFrameContext *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (TrafficSignalControllerTestMsgFrameContext *)Dz1Calloc(sizeof(TrafficSignalControllerTestMsgFrameContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerTestMsgFrameContext_delAndSetNull, (void *)&ret);
		if (TrafficSignalControllerTestMsgFrameContext_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerTestMsgFrameContext_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void TrafficSignalControllerTestMsgFrameContext_purge(TrafficSignalControllerTestMsgFrameContext *p)
{
	if (!p) return;
	switch(p->present)
	{
	case TrafficSignalControllerTestMsgFrameContextPresent_control_req:
		CrossControlCmd_del(p->x.control_req);
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_control_rsp:
		CrossIndicator_del(p->x.control_rsp);
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_status_req:
		CrossIndicator_del(p->x.status_req);
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_status_rsp:
		TrafficSignalControllerTestMsgFrame_status_response_del(p->x.status_rsp);
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_detector_req:
		CrossIndicator_del(p->x.detector_req);
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_detector_rsp:
		DetectorInfo_del(p->x.detector_rsp);
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_download_req:
		SignalPhaseInfoDown_r27_del(p->x.signal_phase_download_req);
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_download_rsp:
		CrossIndicator_del(p->x.signal_phase_download_rsp);
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_upload_req:
		CrossIndicator_del(p->x.signal_phase_upload_req);
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_upload_rsp:
		SignalPhaseInfoUp_del(p->x.signal_phase_upload_rsp);
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_clock_download_req:
		ClockInfo_del(p->x.clock_download_req);
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_clock_download_rsp:
		CrossIndicator_del(p->x.clock_download_rsp);
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_clock_upload_req:
		CrossIndicator_del(p->x.clock_upload_req);
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_clock_upload_rsp:
		ClockInfo_del(p->x.clock_upload_rsp);
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_special_command_req:
		SpecialCommandInfo_del(p->x.special_command_req);
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_special_command_rsp:
		SpecialCommandPPCNumberList_del(p->x.special_command_rsp);
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_fw_upgrade_req:
		FirmwareUpgradeData_del(p->x.fw_upgrade_req);
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_fw_upgrade_rsp:
		FirmwareUpgradeError_del(p->x.fw_upgrade_rsp);
		break;
	default:
		break;
	}
}

void TrafficSignalControllerTestMsgFrameContext_del(TrafficSignalControllerTestMsgFrameContext *p)
{
	if (!p) return;
	TrafficSignalControllerTestMsgFrameContext_purge(p);
	Dz1Free(p);
}

void TrafficSignalControllerTestMsgFrameContext_dump(TrafficSignalControllerTestMsgFrameContext *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case TrafficSignalControllerTestMsgFrameContextPresent_control_req:
		Dz1Thread_printf(Dz1T("control_req.")); CrossControlCmd_dump(p->x.control_req, tab); 
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_control_rsp:
		Dz1Thread_printf(Dz1T("control_rsp = ")); CrossIndicator_dump(p->x.control_rsp, tab); 
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_status_req:
		Dz1Thread_printf(Dz1T("status_req = ")); CrossIndicator_dump(p->x.status_req, tab); 
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_status_rsp:
		Dz1Thread_printf(Dz1T("status_rsp = ")); TrafficSignalControllerTestMsgFrame_status_response_dump(p->x.status_rsp, tab); 
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_detector_req:
		Dz1Thread_printf(Dz1T("detector_req = ")); CrossIndicator_dump(p->x.detector_req, tab); 
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_detector_rsp:
		Dz1Thread_printf(Dz1T("detector_rsp = ")); DetectorInfo_dump(p->x.detector_rsp, tab); 
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_download_req:
		Dz1Thread_printf(Dz1T("signal_phase_download_req = ")); SignalPhaseInfoDown_r27_dump(p->x.signal_phase_download_req, tab); 
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_download_rsp:
		Dz1Thread_printf(Dz1T("signal_phase_download_rsp = ")); CrossIndicator_dump(p->x.signal_phase_download_rsp, tab); 
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_upload_req:
		Dz1Thread_printf(Dz1T("signal_phase_upload_req = ")); CrossIndicator_dump(p->x.signal_phase_upload_req, tab); 
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_upload_rsp:
		Dz1Thread_printf(Dz1T("signal_phase_upload_rsp = ")); SignalPhaseInfoUp_dump(p->x.signal_phase_upload_rsp, tab); 
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_clock_download_req:
		Dz1Thread_printf(Dz1T("clock_download_req = ")); ClockInfo_dump(p->x.clock_download_req, tab); 
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_clock_download_rsp:
		Dz1Thread_printf(Dz1T("clock_download_rsp = ")); CrossIndicator_dump(p->x.clock_download_rsp, tab); 
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_clock_upload_req:
		Dz1Thread_printf(Dz1T("clock_upload_req = ")); CrossIndicator_dump(p->x.clock_upload_req, tab); 
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_clock_upload_rsp:
		Dz1Thread_printf(Dz1T("clock_upload_rsp = ")); ClockInfo_dump(p->x.clock_upload_rsp, tab); 
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_special_command_req:
		Dz1Thread_printf(Dz1T("special_command_req = ")); SpecialCommandInfo_dump(p->x.special_command_req, tab); 
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_special_command_rsp:
		Dz1Thread_printf(Dz1T("special_command_rsp = ")); SpecialCommandPPCNumberList_dump(p->x.special_command_rsp, tab); 
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_fw_upgrade_req:
		Dz1Thread_printf(Dz1T("fw_upgrade_req = ")); FirmwareUpgradeData_dump(p->x.fw_upgrade_req, tab); 
		break;
	case TrafficSignalControllerTestMsgFrameContextPresent_fw_upgrade_rsp:
		Dz1Thread_printf(Dz1T("fw_upgrade_rsp = ")); FirmwareUpgradeError_dump(p->x.fw_upgrade_rsp, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// TrafficSignalControllerTestMsgFrameContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerTestMsgFrame
TrafficSignalControllerTestMsgFrame *TrafficSignalControllerTestMsgFrame_new(u8_t cross_id, 
																			 Dz1Binary *context, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TrafficSignalControllerTestMsgFrame *__internal_ret = (TrafficSignalControllerTestMsgFrame *)Dz1Calloc(sizeof(TrafficSignalControllerTestMsgFrame), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerTestMsgFrame_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->cross_id = cross_id;
		__internal_ret->context = context;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerTestMsgFrame_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t TrafficSignalControllerTestMsgFrame_copy(TrafficSignalControllerTestMsgFrame *dst, TrafficSignalControllerTestMsgFrame *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = Dz1Binary_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->cross_id = src->cross_id;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TrafficSignalControllerTestMsgFrame *TrafficSignalControllerTestMsgFrame_clone(TrafficSignalControllerTestMsgFrame *src, Dz1Error *err)
{
	TrafficSignalControllerTestMsgFrame *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (TrafficSignalControllerTestMsgFrame *)Dz1Calloc(sizeof(TrafficSignalControllerTestMsgFrame), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TrafficSignalControllerTestMsgFrame_delAndSetNull, (void *)&dst);
		if (TrafficSignalControllerTestMsgFrame_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TrafficSignalControllerTestMsgFrame_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void TrafficSignalControllerTestMsgFrame_purge(TrafficSignalControllerTestMsgFrame *p)
{
	if (p == NULL) return;
	Dz1Binary_del(p->context);
}

void TrafficSignalControllerTestMsgFrame_del(TrafficSignalControllerTestMsgFrame *p)
{
	if (p == NULL) return;
	TrafficSignalControllerTestMsgFrame_purge(p);
	Dz1Free(p);
}

void TrafficSignalControllerTestMsgFrame_dump(TrafficSignalControllerTestMsgFrame *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("cross_id = ")); Dz1u8_dump(&p->cross_id, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("context = ")); Dz1Binary_dump(p->context, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int TrafficSignalControllerTestMsgFrame_cmp(TrafficSignalControllerTestMsgFrame *a, TrafficSignalControllerTestMsgFrame *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u8_cmp(&a->cross_id, &b->cross_id)) != 0) { }
	else if (a->context == NULL && b->context == NULL) ret = 0;
	else if (a->context == NULL /*&& b->context != NULL*/) ret = -1;
	else if (/*a->context != NULL &&*/ b->context == NULL) ret = 1;
	else if ((ret = Dz1Binary_cmp(a->context, b->context)) != 0) { }
	return ret;
}
// TrafficSignalControllerTestMsgFrame
////////////////////////////////////////////////////////////////////////////////


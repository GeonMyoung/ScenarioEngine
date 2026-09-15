#ifndef _DZ1_TDC_TRAFFIC_SIGNAL_CONTROLLER_TEST_MSG_FRAME_DEF_H_
#define _DZ1_TDC_TRAFFIC_SIGNAL_CONTROLLER_TEST_MSG_FRAME_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "TrafficSignalControllerTestMsgDef.h"

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerTestMsgFrame_status_response
typedef struct TrafficSignalControllerTestMsgFrame_status_response
{
	CrossStatusBasicInfo		*lc_status;
	CrossStatusExtInfo_r27		*ex_status;
} TrafficSignalControllerTestMsgFrame_status_response;

DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerTestMsgFrame_status_response *TrafficSignalControllerTestMsgFrame_status_response_new(CrossStatusBasicInfo *lc_status, Dz1Error *err);
static __inline__ TrafficSignalControllerTestMsgFrame_status_response *TrafficSignalControllerTestMsgFrame_status_response_gen(Dz1Error *err) { return TrafficSignalControllerTestMsgFrame_status_response_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t TrafficSignalControllerTestMsgFrame_status_response_copy(TrafficSignalControllerTestMsgFrame_status_response *dst, TrafficSignalControllerTestMsgFrame_status_response *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerTestMsgFrame_status_response *TrafficSignalControllerTestMsgFrame_status_response_clone(TrafficSignalControllerTestMsgFrame_status_response *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerTestMsgFrame_status_response_purge(TrafficSignalControllerTestMsgFrame_status_response *p);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerTestMsgFrame_status_response_del(TrafficSignalControllerTestMsgFrame_status_response *p);
static __inline__ void TrafficSignalControllerTestMsgFrame_status_response_delAndSetNull(void *ptr)
{
	TrafficSignalControllerTestMsgFrame_status_response **p = (TrafficSignalControllerTestMsgFrame_status_response **)ptr;
	if (p) { TrafficSignalControllerTestMsgFrame_status_response_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerTestMsgFrame_status_response_dump(TrafficSignalControllerTestMsgFrame_status_response *p, int tab);
// TrafficSignalControllerTestMsgFrame_status_response
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerTestMsgFrameContextPresent
typedef enum TrafficSignalControllerTestMsgFrameContextPresent
{
	TrafficSignalControllerTestMsgFrameContextPresent_control_req = 16,
	TrafficSignalControllerTestMsgFrameContextPresent_control_rsp = 17,
	TrafficSignalControllerTestMsgFrameContextPresent_status_req = 18,
	TrafficSignalControllerTestMsgFrameContextPresent_status_rsp = 19,
	TrafficSignalControllerTestMsgFrameContextPresent_detector_req = 34,
	TrafficSignalControllerTestMsgFrameContextPresent_detector_rsp = 35,
	TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_download_req = 48,
	TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_download_rsp = 49,
	TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_upload_req = 50,
	TrafficSignalControllerTestMsgFrameContextPresent_signal_phase_upload_rsp = 51,
	TrafficSignalControllerTestMsgFrameContextPresent_clock_download_req = 64,
	TrafficSignalControllerTestMsgFrameContextPresent_clock_download_rsp = 65,
	TrafficSignalControllerTestMsgFrameContextPresent_clock_upload_req = 66,
	TrafficSignalControllerTestMsgFrameContextPresent_clock_upload_rsp = 67,
	TrafficSignalControllerTestMsgFrameContextPresent_special_command_req = 80,
	TrafficSignalControllerTestMsgFrameContextPresent_special_command_rsp = 81,
	TrafficSignalControllerTestMsgFrameContextPresent_fw_upgrade_req = 86,
	TrafficSignalControllerTestMsgFrameContextPresent_fw_upgrade_rsp = 87,
	TrafficSignalControllerTestMsgFrameContextPresent_max
} TrafficSignalControllerTestMsgFrameContextPresent;

DZ1_CPPLINK str_t TrafficSignalControllerTestMsgFrameContextPresentStrA(TrafficSignalControllerTestMsgFrameContextPresent v);
DZ1_CPPLINK TrafficSignalControllerTestMsgFrameContextPresent TrafficSignalControllerTestMsgFrameContextPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t TrafficSignalControllerTestMsgFrameContextPresentStrW(TrafficSignalControllerTestMsgFrameContextPresent v);
DZ1_CPPLINK TrafficSignalControllerTestMsgFrameContextPresent TrafficSignalControllerTestMsgFrameContextPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define TrafficSignalControllerTestMsgFrameContextPresentStr TrafficSignalControllerTestMsgFrameContextPresentStrW
#define TrafficSignalControllerTestMsgFrameContextPresentFromStr TrafficSignalControllerTestMsgFrameContextPresentFromStrW
#else // UNICODE
#define TrafficSignalControllerTestMsgFrameContextPresentStr TrafficSignalControllerTestMsgFrameContextPresentStrA
#define TrafficSignalControllerTestMsgFrameContextPresentFromStr TrafficSignalControllerTestMsgFrameContextPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define TrafficSignalControllerTestMsgFrameContextPresentStr TrafficSignalControllerTestMsgFrameContextPresentStrA
#define TrafficSignalControllerTestMsgFrameContextPresentFromStr TrafficSignalControllerTestMsgFrameContextPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerTestMsgFrameContextPresent *TrafficSignalControllerTestMsgFrameContextPresent_new(TrafficSignalControllerTestMsgFrameContextPresent *src, Dz1Error *err);
static __inline__ TrafficSignalControllerTestMsgFrameContextPresent *TrafficSignalControllerTestMsgFrameContextPresent_gen(Dz1Error *err) { TrafficSignalControllerTestMsgFrameContextPresent v = TrafficSignalControllerTestMsgFrameContextPresent_max; return TrafficSignalControllerTestMsgFrameContextPresent_new(&v, err); }
#define TrafficSignalControllerTestMsgFrameContextPresent_clone             TrafficSignalControllerTestMsgFrameContextPresent_new
static __inline__ void TrafficSignalControllerTestMsgFrameContextPresent_del(TrafficSignalControllerTestMsgFrameContextPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void TrafficSignalControllerTestMsgFrameContextPresent_delAndSetNull(void *ptr)
{
	TrafficSignalControllerTestMsgFrameContextPresent **p = (TrafficSignalControllerTestMsgFrameContextPresent **)ptr;
	if (p != NULL) { TrafficSignalControllerTestMsgFrameContextPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerTestMsgFrameContextPresent_dump(TrafficSignalControllerTestMsgFrameContextPresent *v, int tab);
// TrafficSignalControllerTestMsgFrameContextPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerTestMsgFrameContext
typedef struct TrafficSignalControllerTestMsgFrameContext
{
	TrafficSignalControllerTestMsgFrameContextPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		CrossControlCmd											*control_req;
		CrossIndicator											*control_rsp;
		CrossIndicator											*status_req;
		TrafficSignalControllerTestMsgFrame_status_response		*status_rsp;
		CrossIndicator											*detector_req;
		DetectorInfo											*detector_rsp;
		SignalPhaseInfoDown_r27									*signal_phase_download_req;
		CrossIndicator											*signal_phase_download_rsp;
		CrossIndicator											*signal_phase_upload_req;
		SignalPhaseInfoUp										*signal_phase_upload_rsp;
		ClockInfo												*clock_download_req;
		CrossIndicator											*clock_download_rsp;
		CrossIndicator											*clock_upload_req;
		ClockInfo												*clock_upload_rsp;
		SpecialCommandInfo										*special_command_req;
		SpecialCommandPPCNumberList								*special_command_rsp;
		FirmwareUpgradeData										*fw_upgrade_req;
		FirmwareUpgradeError									*fw_upgrade_rsp;
	} x;
} TrafficSignalControllerTestMsgFrameContext;

DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerTestMsgFrameContext *TrafficSignalControllerTestMsgFrameContext_new(TrafficSignalControllerTestMsgFrameContextPresent present, void *ptr, Dz1Error *err);
static __inline__ TrafficSignalControllerTestMsgFrameContext *TrafficSignalControllerTestMsgFrameContext_gen(Dz1Error *err) { return TrafficSignalControllerTestMsgFrameContext_new(TrafficSignalControllerTestMsgFrameContextPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  TrafficSignalControllerTestMsgFrameContext_copy(TrafficSignalControllerTestMsgFrameContext *dst, TrafficSignalControllerTestMsgFrameContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerTestMsgFrameContext *TrafficSignalControllerTestMsgFrameContext_clone(TrafficSignalControllerTestMsgFrameContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerTestMsgFrameContext_purge(TrafficSignalControllerTestMsgFrameContext *p);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerTestMsgFrameContext_del(TrafficSignalControllerTestMsgFrameContext *p);
static __inline__ void TrafficSignalControllerTestMsgFrameContext_delAndSetNull(void *ptr)
{
	TrafficSignalControllerTestMsgFrameContext **p = (TrafficSignalControllerTestMsgFrameContext **)ptr;
	if (p != NULL) { TrafficSignalControllerTestMsgFrameContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerTestMsgFrameContext_dump(TrafficSignalControllerTestMsgFrameContext *p, int tab);
// TrafficSignalControllerTestMsgFrameContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerTestMsgFrame
typedef struct TrafficSignalControllerTestMsgFrame
{
	u8_t			 cross_id;
	Dz1Binary		*context;
} TrafficSignalControllerTestMsgFrame;

DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerTestMsgFrame *TrafficSignalControllerTestMsgFrame_new(u8_t cross_id, 
																									 Dz1Binary *context, Dz1Error *err);
static __inline__ TrafficSignalControllerTestMsgFrame *TrafficSignalControllerTestMsgFrame_gen(Dz1Error *err) { return TrafficSignalControllerTestMsgFrame_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t TrafficSignalControllerTestMsgFrame_copy(TrafficSignalControllerTestMsgFrame *dst, TrafficSignalControllerTestMsgFrame *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerTestMsgFrame *TrafficSignalControllerTestMsgFrame_clone(TrafficSignalControllerTestMsgFrame *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerTestMsgFrame_purge(TrafficSignalControllerTestMsgFrame *p);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerTestMsgFrame_del(TrafficSignalControllerTestMsgFrame *p);
static __inline__ void TrafficSignalControllerTestMsgFrame_delAndSetNull(void *ptr)
{
	TrafficSignalControllerTestMsgFrame **p = (TrafficSignalControllerTestMsgFrame **)ptr;
	if (p) { TrafficSignalControllerTestMsgFrame_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerTestMsgFrame_dump(TrafficSignalControllerTestMsgFrame *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int TrafficSignalControllerTestMsgFrame_cmp(TrafficSignalControllerTestMsgFrame *a, TrafficSignalControllerTestMsgFrame *b); 
// TrafficSignalControllerTestMsgFrame
////////////////////////////////////////////////////////////////////////////////

#endif

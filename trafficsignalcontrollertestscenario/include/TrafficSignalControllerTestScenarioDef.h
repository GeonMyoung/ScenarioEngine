#ifndef _DZ1_TDC_TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_DEF_H_
#define _DZ1_TDC_TRAFFIC_SIGNAL_CONTROLLER_TEST_SCENARIO_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerTestScenarioException
typedef void (*TrafficSignalControllerTestScenarioException)(void *exceptionArg, Dz1Error *reason);
// TrafficSignalControllerTestScenarioException
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerProcessStatusCode
typedef enum TrafficSignalControllerProcessStatusCode
{
	TrafficSignalControllerProcessStatusCode_OK = 0,
	TrafficSignalControllerProcessStatusCode_FAILURE = 1,
	TrafficSignalControllerProcessStatusCode_AGENT_SYSTEM_ERROR = 11,
	TrafficSignalControllerProcessStatusCode_SERVER_DISCONNECTED = 12,
	TrafficSignalControllerProcessStatusCode_TEST_CONFIGURATION_ERROR = 13,
	TrafficSignalControllerProcessStatusCode_CONNECTION_FAIL = 100,
	TrafficSignalControllerProcessStatusCode_DISCONNECTED = 101,
	TrafficSignalControllerProcessStatusCode_TIMEOUT = 102,
	TrafficSignalControllerProcessStatusCode_OUT_OF_RANGE = 201,
	TrafficSignalControllerProcessStatusCode_INVALID_PROCESS,
	TrafficSignalControllerProcessStatusCode_INVALID_IDENTIFIER,
	TrafficSignalControllerProcessStatusCode_SESSION_DUPLICATE,
	TrafficSignalControllerProcessStatusCode_LOGIN_AUTH_ERROR,
	TrafficSignalControllerProcessStatusCode_DECODE_FAIL = 210,
	TrafficSignalControllerProcessStatusCode_INVALID_ENCODING_RULE = 211,
	TrafficSignalControllerProcessStatusCode_INVALID_OID = 212,
	TrafficSignalControllerProcessStatusCode_INVALID_DSRC_MSG_ID = 213,
	TrafficSignalControllerProcessStatusCode_JSON_PARSE_ERROR = 221,
	TrafficSignalControllerProcessStatusCode_PROTOBUF_DESERAILIZE_ERROR = 231,
	TrafficSignalControllerProcessStatusCode_INVALID_TOPIC = 241,
	TrafficSignalControllerProcessStatusCode_INVALID_REQUEST = 251,
	TrafficSignalControllerProcessStatusCode_UNKNOWN = 300,
	TrafficSignalControllerProcessStatusCode_max
} TrafficSignalControllerProcessStatusCode;

DZ1_CPPLINK str_t TrafficSignalControllerProcessStatusCodeStrA(TrafficSignalControllerProcessStatusCode v);
DZ1_CPPLINK TrafficSignalControllerProcessStatusCode TrafficSignalControllerProcessStatusCodeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t TrafficSignalControllerProcessStatusCodeStrW(TrafficSignalControllerProcessStatusCode v);
DZ1_CPPLINK TrafficSignalControllerProcessStatusCode TrafficSignalControllerProcessStatusCodeFromStrW(wstr_t str);
#ifdef UNICODE
#define TrafficSignalControllerProcessStatusCodeStr TrafficSignalControllerProcessStatusCodeStrW
#define TrafficSignalControllerProcessStatusCodeFromStr TrafficSignalControllerProcessStatusCodeFromStrW
#else // UNICODE
#define TrafficSignalControllerProcessStatusCodeStr TrafficSignalControllerProcessStatusCodeStrA
#define TrafficSignalControllerProcessStatusCodeFromStr TrafficSignalControllerProcessStatusCodeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define TrafficSignalControllerProcessStatusCodeStr TrafficSignalControllerProcessStatusCodeStrA
#define TrafficSignalControllerProcessStatusCodeFromStr TrafficSignalControllerProcessStatusCodeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerProcessStatusCode *TrafficSignalControllerProcessStatusCode_new(TrafficSignalControllerProcessStatusCode *src, Dz1Error *err);
static __inline__ TrafficSignalControllerProcessStatusCode *TrafficSignalControllerProcessStatusCode_gen(Dz1Error *err) { TrafficSignalControllerProcessStatusCode v = TrafficSignalControllerProcessStatusCode_max; return TrafficSignalControllerProcessStatusCode_new(&v, err); }
#define TrafficSignalControllerProcessStatusCode_clone             TrafficSignalControllerProcessStatusCode_new
static __inline__ void TrafficSignalControllerProcessStatusCode_del(TrafficSignalControllerProcessStatusCode *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void TrafficSignalControllerProcessStatusCode_delAndSetNull(void *ptr)
{
	TrafficSignalControllerProcessStatusCode **p = (TrafficSignalControllerProcessStatusCode **)ptr;
	if (p != NULL) { TrafficSignalControllerProcessStatusCode_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerProcessStatusCode_dump(TrafficSignalControllerProcessStatusCode *v, int tab);
// TrafficSignalControllerProcessStatusCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerNotifyStateContext
typedef struct TrafficSignalControllerNotifyStateContext
{
	Dz1Str		testName;
	s64_t		time;
	Dz1Str		state;
} TrafficSignalControllerNotifyStateContext;

DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerNotifyStateContext *TrafficSignalControllerNotifyStateContext_new(Dz1Str testName, 
																												 s64_t time, 
																												 Dz1Str state, Dz1Error *err);
static __inline__ TrafficSignalControllerNotifyStateContext *TrafficSignalControllerNotifyStateContext_gen(Dz1Error *err) { return TrafficSignalControllerNotifyStateContext_new(NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t TrafficSignalControllerNotifyStateContext_copy(TrafficSignalControllerNotifyStateContext *dst, TrafficSignalControllerNotifyStateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerNotifyStateContext *TrafficSignalControllerNotifyStateContext_clone(TrafficSignalControllerNotifyStateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerNotifyStateContext_purge(TrafficSignalControllerNotifyStateContext *p);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerNotifyStateContext_del(TrafficSignalControllerNotifyStateContext *p);
static __inline__ void TrafficSignalControllerNotifyStateContext_delAndSetNull(void *ptr)
{
	TrafficSignalControllerNotifyStateContext **p = (TrafficSignalControllerNotifyStateContext **)ptr;
	if (p) { TrafficSignalControllerNotifyStateContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerNotifyStateContext_dump(TrafficSignalControllerNotifyStateContext *p, int tab);
// TrafficSignalControllerNotifyStateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerNotifyInfoContext
typedef struct TrafficSignalControllerNotifyInfoContext
{
	Dz1Str			 testName;
	s64_t			 time;
	Dz1Str			 sender;
	Dz1Str			 log;
	Dz1Binary		*data;
	Dz1Str			 dataType;
} TrafficSignalControllerNotifyInfoContext;

DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerNotifyInfoContext *TrafficSignalControllerNotifyInfoContext_new(Dz1Str testName, 
																											   s64_t time, 
																											   Dz1Str sender, 
																											   Dz1Str log, 
																											   Dz1Binary *data, 
																											   Dz1Str dataType, Dz1Error *err);
static __inline__ TrafficSignalControllerNotifyInfoContext *TrafficSignalControllerNotifyInfoContext_gen(Dz1Error *err) { return TrafficSignalControllerNotifyInfoContext_new(NULL, 0, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t TrafficSignalControllerNotifyInfoContext_copy(TrafficSignalControllerNotifyInfoContext *dst, TrafficSignalControllerNotifyInfoContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerNotifyInfoContext *TrafficSignalControllerNotifyInfoContext_clone(TrafficSignalControllerNotifyInfoContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerNotifyInfoContext_purge(TrafficSignalControllerNotifyInfoContext *p);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerNotifyInfoContext_del(TrafficSignalControllerNotifyInfoContext *p);
static __inline__ void TrafficSignalControllerNotifyInfoContext_delAndSetNull(void *ptr)
{
	TrafficSignalControllerNotifyInfoContext **p = (TrafficSignalControllerNotifyInfoContext **)ptr;
	if (p) { TrafficSignalControllerNotifyInfoContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerNotifyInfoContext_dump(TrafficSignalControllerNotifyInfoContext *p, int tab);
// TrafficSignalControllerNotifyInfoContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerNotifyErrorContext
typedef struct TrafficSignalControllerNotifyErrorContext
{
	Dz1Str										 testName;
	s64_t										 time;
	TrafficSignalControllerProcessStatusCode	 code;
	Dz1Str										 desc;
	Dz1Str										 log;
	Dz1Binary									*data;
} TrafficSignalControllerNotifyErrorContext;

DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerNotifyErrorContext *TrafficSignalControllerNotifyErrorContext_new(Dz1Str testName, 
																												 s64_t time, 
																												 TrafficSignalControllerProcessStatusCode code, 
																												 Dz1Str desc, 
																												 Dz1Str log, 
																												 Dz1Binary *data, Dz1Error *err);
static __inline__ TrafficSignalControllerNotifyErrorContext *TrafficSignalControllerNotifyErrorContext_gen(Dz1Error *err) { return TrafficSignalControllerNotifyErrorContext_new(NULL, 0, TrafficSignalControllerProcessStatusCode_max, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t TrafficSignalControllerNotifyErrorContext_copy(TrafficSignalControllerNotifyErrorContext *dst, TrafficSignalControllerNotifyErrorContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerNotifyErrorContext *TrafficSignalControllerNotifyErrorContext_clone(TrafficSignalControllerNotifyErrorContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerNotifyErrorContext_purge(TrafficSignalControllerNotifyErrorContext *p);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerNotifyErrorContext_del(TrafficSignalControllerNotifyErrorContext *p);
static __inline__ void TrafficSignalControllerNotifyErrorContext_delAndSetNull(void *ptr)
{
	TrafficSignalControllerNotifyErrorContext **p = (TrafficSignalControllerNotifyErrorContext **)ptr;
	if (p) { TrafficSignalControllerNotifyErrorContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerNotifyErrorContext_dump(TrafficSignalControllerNotifyErrorContext *p, int tab);
// TrafficSignalControllerNotifyErrorContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerNotifyStateArg
typedef struct TrafficSignalControllerNotifyStateArg
{
	u32_t											 testIdx;
	TrafficSignalControllerNotifyStateContext		*context;
} TrafficSignalControllerNotifyStateArg;

DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerNotifyStateArg *TrafficSignalControllerNotifyStateArg_new(u32_t testIdx, 
																										 TrafficSignalControllerNotifyStateContext *context, Dz1Error *err);
static __inline__ TrafficSignalControllerNotifyStateArg *TrafficSignalControllerNotifyStateArg_gen(Dz1Error *err) { return TrafficSignalControllerNotifyStateArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t TrafficSignalControllerNotifyStateArg_copy(TrafficSignalControllerNotifyStateArg *dst, TrafficSignalControllerNotifyStateArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerNotifyStateArg *TrafficSignalControllerNotifyStateArg_clone(TrafficSignalControllerNotifyStateArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerNotifyStateArg_purge(TrafficSignalControllerNotifyStateArg *p);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerNotifyStateArg_del(TrafficSignalControllerNotifyStateArg *p);
static __inline__ void TrafficSignalControllerNotifyStateArg_delAndSetNull(void *ptr)
{
	TrafficSignalControllerNotifyStateArg **p = (TrafficSignalControllerNotifyStateArg **)ptr;
	if (p) { TrafficSignalControllerNotifyStateArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerNotifyStateArg_dump(TrafficSignalControllerNotifyStateArg *p, int tab);
// TrafficSignalControllerNotifyStateArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerNotifyInfoArg
typedef struct TrafficSignalControllerNotifyInfoArg
{
	u32_t										 testIdx;
	TrafficSignalControllerNotifyInfoContext	*context;
} TrafficSignalControllerNotifyInfoArg;

DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerNotifyInfoArg *TrafficSignalControllerNotifyInfoArg_new(u32_t testIdx, 
																									   TrafficSignalControllerNotifyInfoContext *context, Dz1Error *err);
static __inline__ TrafficSignalControllerNotifyInfoArg *TrafficSignalControllerNotifyInfoArg_gen(Dz1Error *err) { return TrafficSignalControllerNotifyInfoArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t TrafficSignalControllerNotifyInfoArg_copy(TrafficSignalControllerNotifyInfoArg *dst, TrafficSignalControllerNotifyInfoArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerNotifyInfoArg *TrafficSignalControllerNotifyInfoArg_clone(TrafficSignalControllerNotifyInfoArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerNotifyInfoArg_purge(TrafficSignalControllerNotifyInfoArg *p);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerNotifyInfoArg_del(TrafficSignalControllerNotifyInfoArg *p);
static __inline__ void TrafficSignalControllerNotifyInfoArg_delAndSetNull(void *ptr)
{
	TrafficSignalControllerNotifyInfoArg **p = (TrafficSignalControllerNotifyInfoArg **)ptr;
	if (p) { TrafficSignalControllerNotifyInfoArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerNotifyInfoArg_dump(TrafficSignalControllerNotifyInfoArg *p, int tab);
// TrafficSignalControllerNotifyInfoArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerNotifyErrorArg
typedef struct TrafficSignalControllerNotifyErrorArg
{
	u32_t											 testIdx;
	TrafficSignalControllerNotifyErrorContext		*context;
} TrafficSignalControllerNotifyErrorArg;

DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerNotifyErrorArg *TrafficSignalControllerNotifyErrorArg_new(u32_t testIdx, 
																										 TrafficSignalControllerNotifyErrorContext *context, Dz1Error *err);
static __inline__ TrafficSignalControllerNotifyErrorArg *TrafficSignalControllerNotifyErrorArg_gen(Dz1Error *err) { return TrafficSignalControllerNotifyErrorArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t TrafficSignalControllerNotifyErrorArg_copy(TrafficSignalControllerNotifyErrorArg *dst, TrafficSignalControllerNotifyErrorArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerNotifyErrorArg *TrafficSignalControllerNotifyErrorArg_clone(TrafficSignalControllerNotifyErrorArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerNotifyErrorArg_purge(TrafficSignalControllerNotifyErrorArg *p);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerNotifyErrorArg_del(TrafficSignalControllerNotifyErrorArg *p);
static __inline__ void TrafficSignalControllerNotifyErrorArg_delAndSetNull(void *ptr)
{
	TrafficSignalControllerNotifyErrorArg **p = (TrafficSignalControllerNotifyErrorArg **)ptr;
	if (p) { TrafficSignalControllerNotifyErrorArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerNotifyErrorArg_dump(TrafficSignalControllerNotifyErrorArg *p, int tab);
// TrafficSignalControllerNotifyErrorArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerNotifyContextPresent
typedef enum TrafficSignalControllerNotifyContextPresent
{
	TrafficSignalControllerNotifyContextPresent_state,
	TrafficSignalControllerNotifyContextPresent_info,
	TrafficSignalControllerNotifyContextPresent_error,
	TrafficSignalControllerNotifyContextPresent_max
} TrafficSignalControllerNotifyContextPresent;

DZ1_CPPLINK str_t TrafficSignalControllerNotifyContextPresentStrA(TrafficSignalControllerNotifyContextPresent v);
DZ1_CPPLINK TrafficSignalControllerNotifyContextPresent TrafficSignalControllerNotifyContextPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t TrafficSignalControllerNotifyContextPresentStrW(TrafficSignalControllerNotifyContextPresent v);
DZ1_CPPLINK TrafficSignalControllerNotifyContextPresent TrafficSignalControllerNotifyContextPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define TrafficSignalControllerNotifyContextPresentStr TrafficSignalControllerNotifyContextPresentStrW
#define TrafficSignalControllerNotifyContextPresentFromStr TrafficSignalControllerNotifyContextPresentFromStrW
#else // UNICODE
#define TrafficSignalControllerNotifyContextPresentStr TrafficSignalControllerNotifyContextPresentStrA
#define TrafficSignalControllerNotifyContextPresentFromStr TrafficSignalControllerNotifyContextPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define TrafficSignalControllerNotifyContextPresentStr TrafficSignalControllerNotifyContextPresentStrA
#define TrafficSignalControllerNotifyContextPresentFromStr TrafficSignalControllerNotifyContextPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerNotifyContextPresent *TrafficSignalControllerNotifyContextPresent_new(TrafficSignalControllerNotifyContextPresent *src, Dz1Error *err);
static __inline__ TrafficSignalControllerNotifyContextPresent *TrafficSignalControllerNotifyContextPresent_gen(Dz1Error *err) { TrafficSignalControllerNotifyContextPresent v = TrafficSignalControllerNotifyContextPresent_max; return TrafficSignalControllerNotifyContextPresent_new(&v, err); }
#define TrafficSignalControllerNotifyContextPresent_clone             TrafficSignalControllerNotifyContextPresent_new
static __inline__ void TrafficSignalControllerNotifyContextPresent_del(TrafficSignalControllerNotifyContextPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void TrafficSignalControllerNotifyContextPresent_delAndSetNull(void *ptr)
{
	TrafficSignalControllerNotifyContextPresent **p = (TrafficSignalControllerNotifyContextPresent **)ptr;
	if (p != NULL) { TrafficSignalControllerNotifyContextPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerNotifyContextPresent_dump(TrafficSignalControllerNotifyContextPresent *v, int tab);
// TrafficSignalControllerNotifyContextPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerNotifyContext
typedef struct TrafficSignalControllerNotifyContext
{
	TrafficSignalControllerNotifyContextPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		TrafficSignalControllerNotifyStateContext		*state;
		TrafficSignalControllerNotifyInfoContext		*info;
		TrafficSignalControllerNotifyErrorContext		*error;
	} x;
} TrafficSignalControllerNotifyContext;

DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerNotifyContext *TrafficSignalControllerNotifyContext_new(TrafficSignalControllerNotifyContextPresent present, void *ptr, Dz1Error *err);
static __inline__ TrafficSignalControllerNotifyContext *TrafficSignalControllerNotifyContext_gen(Dz1Error *err) { return TrafficSignalControllerNotifyContext_new(TrafficSignalControllerNotifyContextPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  TrafficSignalControllerNotifyContext_copy(TrafficSignalControllerNotifyContext *dst, TrafficSignalControllerNotifyContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerNotifyContext *TrafficSignalControllerNotifyContext_clone(TrafficSignalControllerNotifyContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerNotifyContext_purge(TrafficSignalControllerNotifyContext *p);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerNotifyContext_del(TrafficSignalControllerNotifyContext *p);
static __inline__ void TrafficSignalControllerNotifyContext_delAndSetNull(void *ptr)
{
	TrafficSignalControllerNotifyContext **p = (TrafficSignalControllerNotifyContext **)ptr;
	if (p != NULL) { TrafficSignalControllerNotifyContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerNotifyContext_dump(TrafficSignalControllerNotifyContext *p, int tab);
// TrafficSignalControllerNotifyContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerValidateContext
typedef struct TrafficSignalControllerValidateContext
{
	Dz1Str										 testName;
	s64_t										 time;
	Dz1Binary									*raw;
	Dz1Binary									*data;
	TrafficSignalControllerProcessStatusCode	 code;
	Dz1Str										 desc;
} TrafficSignalControllerValidateContext;

DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerValidateContext *TrafficSignalControllerValidateContext_new(Dz1Str testName, 
																										   s64_t time, 
																										   Dz1Binary *raw, 
																										   Dz1Binary *data, 
																										   TrafficSignalControllerProcessStatusCode code, 
																										   Dz1Str desc, Dz1Error *err);
static __inline__ TrafficSignalControllerValidateContext *TrafficSignalControllerValidateContext_gen(Dz1Error *err) { return TrafficSignalControllerValidateContext_new(NULL, 0, NULL, NULL, TrafficSignalControllerProcessStatusCode_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t TrafficSignalControllerValidateContext_copy(TrafficSignalControllerValidateContext *dst, TrafficSignalControllerValidateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerValidateContext *TrafficSignalControllerValidateContext_clone(TrafficSignalControllerValidateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerValidateContext_purge(TrafficSignalControllerValidateContext *p);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerValidateContext_del(TrafficSignalControllerValidateContext *p);
static __inline__ void TrafficSignalControllerValidateContext_delAndSetNull(void *ptr)
{
	TrafficSignalControllerValidateContext **p = (TrafficSignalControllerValidateContext **)ptr;
	if (p) { TrafficSignalControllerValidateContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerValidateContext_dump(TrafficSignalControllerValidateContext *p, int tab);
// TrafficSignalControllerValidateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerValidateContextArg
typedef struct TrafficSignalControllerValidateContextArg
{
	u32_t										 testIdx;
	TrafficSignalControllerValidateContext		*context;
} TrafficSignalControllerValidateContextArg;

DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerValidateContextArg *TrafficSignalControllerValidateContextArg_new(u32_t testIdx, 
																												 TrafficSignalControllerValidateContext *context, Dz1Error *err);
static __inline__ TrafficSignalControllerValidateContextArg *TrafficSignalControllerValidateContextArg_gen(Dz1Error *err) { return TrafficSignalControllerValidateContextArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t TrafficSignalControllerValidateContextArg_copy(TrafficSignalControllerValidateContextArg *dst, TrafficSignalControllerValidateContextArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TrafficSignalControllerValidateContextArg *TrafficSignalControllerValidateContextArg_clone(TrafficSignalControllerValidateContextArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerValidateContextArg_purge(TrafficSignalControllerValidateContextArg *p);
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerValidateContextArg_del(TrafficSignalControllerValidateContextArg *p);
static __inline__ void TrafficSignalControllerValidateContextArg_delAndSetNull(void *ptr)
{
	TrafficSignalControllerValidateContextArg **p = (TrafficSignalControllerValidateContextArg **)ptr;
	if (p) { TrafficSignalControllerValidateContextArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TrafficSignalControllerValidateContextArg_dump(TrafficSignalControllerValidateContextArg *p, int tab);
// TrafficSignalControllerValidateContextArg
////////////////////////////////////////////////////////////////////////////////

#endif

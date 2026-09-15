#ifndef _DZ1_TDC_ITSK00126V2_TEST_SCENARIO_DEF_H_
#define _DZ1_TDC_ITSK00126V2_TEST_SCENARIO_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "Itsk00126v2TestMsgDef.h"

////////////////////////////////////////////////////////////////////////////////
// Itsk00126V2TestScenarioException
typedef void (*Itsk00126V2TestScenarioException)(void *exceptionArg, Dz1Error *reason);
// Itsk00126V2TestScenarioException
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2ProcessStatusCode
typedef enum Itsk00126v2ProcessStatusCode
{
	Itsk00126v2ProcessStatusCode_OK = 0,
	Itsk00126v2ProcessStatusCode_FAILURE = 1,
	Itsk00126v2ProcessStatusCode_AGENT_SYSTEM_ERROR = 11,
	Itsk00126v2ProcessStatusCode_SERVER_DISCONNECTED = 12,
	Itsk00126v2ProcessStatusCode_TEST_CONFIGURATION_ERROR = 13,
	Itsk00126v2ProcessStatusCode_CONNECTION_FAIL = 100,
	Itsk00126v2ProcessStatusCode_DISCONNECTED = 101,
	Itsk00126v2ProcessStatusCode_TIMEOUT = 102,
	Itsk00126v2ProcessStatusCode_OUT_OF_RANGE = 201,
	Itsk00126v2ProcessStatusCode_INVALID_PROCESS,
	Itsk00126v2ProcessStatusCode_INVALID_IDENTIFIER,
	Itsk00126v2ProcessStatusCode_SESSION_DUPLICATE,
	Itsk00126v2ProcessStatusCode_LOGIN_AUTH_ERROR,
	Itsk00126v2ProcessStatusCode_DECODE_FAIL = 210,
	Itsk00126v2ProcessStatusCode_INVALID_ENCODING_RULE = 211,
	Itsk00126v2ProcessStatusCode_INVALID_OID = 212,
	Itsk00126v2ProcessStatusCode_INVALID_DSRC_MSG_ID = 213,
	Itsk00126v2ProcessStatusCode_JSON_PARSE_ERROR = 221,
	Itsk00126v2ProcessStatusCode_PROTOBUF_DESERAILIZE_ERROR = 231,
	Itsk00126v2ProcessStatusCode_INVALID_TOPIC = 241,
	Itsk00126v2ProcessStatusCode_INVALID_REQUEST = 251,
	Itsk00126v2ProcessStatusCode_UNKNOWN = 300,
	Itsk00126v2ProcessStatusCode_max
} Itsk00126v2ProcessStatusCode;

DZ1_CPPLINK str_t Itsk00126v2ProcessStatusCodeStrA(Itsk00126v2ProcessStatusCode v);
DZ1_CPPLINK Itsk00126v2ProcessStatusCode Itsk00126v2ProcessStatusCodeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Itsk00126v2ProcessStatusCodeStrW(Itsk00126v2ProcessStatusCode v);
DZ1_CPPLINK Itsk00126v2ProcessStatusCode Itsk00126v2ProcessStatusCodeFromStrW(wstr_t str);
#ifdef UNICODE
#define Itsk00126v2ProcessStatusCodeStr Itsk00126v2ProcessStatusCodeStrW
#define Itsk00126v2ProcessStatusCodeFromStr Itsk00126v2ProcessStatusCodeFromStrW
#else // UNICODE
#define Itsk00126v2ProcessStatusCodeStr Itsk00126v2ProcessStatusCodeStrA
#define Itsk00126v2ProcessStatusCodeFromStr Itsk00126v2ProcessStatusCodeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Itsk00126v2ProcessStatusCodeStr Itsk00126v2ProcessStatusCodeStrA
#define Itsk00126v2ProcessStatusCodeFromStr Itsk00126v2ProcessStatusCodeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2ProcessStatusCode *Itsk00126v2ProcessStatusCode_new(Itsk00126v2ProcessStatusCode *src, Dz1Error *err);
static __inline__ Itsk00126v2ProcessStatusCode *Itsk00126v2ProcessStatusCode_gen(Dz1Error *err) { Itsk00126v2ProcessStatusCode v = Itsk00126v2ProcessStatusCode_max; return Itsk00126v2ProcessStatusCode_new(&v, err); }
#define Itsk00126v2ProcessStatusCode_clone             Itsk00126v2ProcessStatusCode_new
static __inline__ void Itsk00126v2ProcessStatusCode_del(Itsk00126v2ProcessStatusCode *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Itsk00126v2ProcessStatusCode_delAndSetNull(void *ptr)
{
	Itsk00126v2ProcessStatusCode **p = (Itsk00126v2ProcessStatusCode **)ptr;
	if (p != NULL) { Itsk00126v2ProcessStatusCode_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2ProcessStatusCode_dump(Itsk00126v2ProcessStatusCode *v, int tab);
// Itsk00126v2ProcessStatusCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2NotifyStateContext
typedef struct Itsk00126v2NotifyStateContext
{
	Dz1Str		testName;
	s64_t		time;
	Dz1Str		state;
} Itsk00126v2NotifyStateContext;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2NotifyStateContext *Itsk00126v2NotifyStateContext_new(Dz1Str testName, 
																						 s64_t time, 
																						 Dz1Str state, Dz1Error *err);
static __inline__ Itsk00126v2NotifyStateContext *Itsk00126v2NotifyStateContext_gen(Dz1Error *err) { return Itsk00126v2NotifyStateContext_new(NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v2NotifyStateContext_copy(Itsk00126v2NotifyStateContext *dst, Itsk00126v2NotifyStateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2NotifyStateContext *Itsk00126v2NotifyStateContext_clone(Itsk00126v2NotifyStateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2NotifyStateContext_purge(Itsk00126v2NotifyStateContext *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2NotifyStateContext_del(Itsk00126v2NotifyStateContext *p);
static __inline__ void Itsk00126v2NotifyStateContext_delAndSetNull(void *ptr)
{
	Itsk00126v2NotifyStateContext **p = (Itsk00126v2NotifyStateContext **)ptr;
	if (p) { Itsk00126v2NotifyStateContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2NotifyStateContext_dump(Itsk00126v2NotifyStateContext *p, int tab);
// Itsk00126v2NotifyStateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2NotifyInfoContext
typedef struct Itsk00126v2NotifyInfoContext
{
	Dz1Str			 testName;
	s64_t			 time;
	Dz1Str			 sender;
	Dz1Str			 log;
	Dz1Binary		*data;
	Dz1Str			 dataType;
} Itsk00126v2NotifyInfoContext;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2NotifyInfoContext *Itsk00126v2NotifyInfoContext_new(Dz1Str testName, 
																					   s64_t time, 
																					   Dz1Str sender, 
																					   Dz1Str log, 
																					   Dz1Binary *data, 
																					   Dz1Str dataType, Dz1Error *err);
static __inline__ Itsk00126v2NotifyInfoContext *Itsk00126v2NotifyInfoContext_gen(Dz1Error *err) { return Itsk00126v2NotifyInfoContext_new(NULL, 0, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v2NotifyInfoContext_copy(Itsk00126v2NotifyInfoContext *dst, Itsk00126v2NotifyInfoContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2NotifyInfoContext *Itsk00126v2NotifyInfoContext_clone(Itsk00126v2NotifyInfoContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2NotifyInfoContext_purge(Itsk00126v2NotifyInfoContext *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2NotifyInfoContext_del(Itsk00126v2NotifyInfoContext *p);
static __inline__ void Itsk00126v2NotifyInfoContext_delAndSetNull(void *ptr)
{
	Itsk00126v2NotifyInfoContext **p = (Itsk00126v2NotifyInfoContext **)ptr;
	if (p) { Itsk00126v2NotifyInfoContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2NotifyInfoContext_dump(Itsk00126v2NotifyInfoContext *p, int tab);
// Itsk00126v2NotifyInfoContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2NotifyErrorContext
typedef struct Itsk00126v2NotifyErrorContext
{
	Dz1Str							 testName;
	s64_t							 time;
	Itsk00126v2ProcessStatusCode	 code;
	Dz1Str							 desc;
	Dz1Str							 log;
	Dz1Binary						*data;
} Itsk00126v2NotifyErrorContext;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2NotifyErrorContext *Itsk00126v2NotifyErrorContext_new(Dz1Str testName, 
																						 s64_t time, 
																						 Itsk00126v2ProcessStatusCode code, 
																						 Dz1Str desc, 
																						 Dz1Str log, 
																						 Dz1Binary *data, Dz1Error *err);
static __inline__ Itsk00126v2NotifyErrorContext *Itsk00126v2NotifyErrorContext_gen(Dz1Error *err) { return Itsk00126v2NotifyErrorContext_new(NULL, 0, Itsk00126v2ProcessStatusCode_max, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v2NotifyErrorContext_copy(Itsk00126v2NotifyErrorContext *dst, Itsk00126v2NotifyErrorContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2NotifyErrorContext *Itsk00126v2NotifyErrorContext_clone(Itsk00126v2NotifyErrorContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2NotifyErrorContext_purge(Itsk00126v2NotifyErrorContext *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2NotifyErrorContext_del(Itsk00126v2NotifyErrorContext *p);
static __inline__ void Itsk00126v2NotifyErrorContext_delAndSetNull(void *ptr)
{
	Itsk00126v2NotifyErrorContext **p = (Itsk00126v2NotifyErrorContext **)ptr;
	if (p) { Itsk00126v2NotifyErrorContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2NotifyErrorContext_dump(Itsk00126v2NotifyErrorContext *p, int tab);
// Itsk00126v2NotifyErrorContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2NotifyStateArg
typedef struct Itsk00126v2NotifyStateArg
{
	u32_t								 testIdx;
	Itsk00126v2NotifyStateContext		*context;
} Itsk00126v2NotifyStateArg;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2NotifyStateArg *Itsk00126v2NotifyStateArg_new(u32_t testIdx, 
																				 Itsk00126v2NotifyStateContext *context, Dz1Error *err);
static __inline__ Itsk00126v2NotifyStateArg *Itsk00126v2NotifyStateArg_gen(Dz1Error *err) { return Itsk00126v2NotifyStateArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v2NotifyStateArg_copy(Itsk00126v2NotifyStateArg *dst, Itsk00126v2NotifyStateArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2NotifyStateArg *Itsk00126v2NotifyStateArg_clone(Itsk00126v2NotifyStateArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2NotifyStateArg_purge(Itsk00126v2NotifyStateArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2NotifyStateArg_del(Itsk00126v2NotifyStateArg *p);
static __inline__ void Itsk00126v2NotifyStateArg_delAndSetNull(void *ptr)
{
	Itsk00126v2NotifyStateArg **p = (Itsk00126v2NotifyStateArg **)ptr;
	if (p) { Itsk00126v2NotifyStateArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2NotifyStateArg_dump(Itsk00126v2NotifyStateArg *p, int tab);
// Itsk00126v2NotifyStateArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2NotifyInfoArg
typedef struct Itsk00126v2NotifyInfoArg
{
	u32_t							 testIdx;
	Itsk00126v2NotifyInfoContext	*context;
} Itsk00126v2NotifyInfoArg;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2NotifyInfoArg *Itsk00126v2NotifyInfoArg_new(u32_t testIdx, 
																			   Itsk00126v2NotifyInfoContext *context, Dz1Error *err);
static __inline__ Itsk00126v2NotifyInfoArg *Itsk00126v2NotifyInfoArg_gen(Dz1Error *err) { return Itsk00126v2NotifyInfoArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v2NotifyInfoArg_copy(Itsk00126v2NotifyInfoArg *dst, Itsk00126v2NotifyInfoArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2NotifyInfoArg *Itsk00126v2NotifyInfoArg_clone(Itsk00126v2NotifyInfoArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2NotifyInfoArg_purge(Itsk00126v2NotifyInfoArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2NotifyInfoArg_del(Itsk00126v2NotifyInfoArg *p);
static __inline__ void Itsk00126v2NotifyInfoArg_delAndSetNull(void *ptr)
{
	Itsk00126v2NotifyInfoArg **p = (Itsk00126v2NotifyInfoArg **)ptr;
	if (p) { Itsk00126v2NotifyInfoArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2NotifyInfoArg_dump(Itsk00126v2NotifyInfoArg *p, int tab);
// Itsk00126v2NotifyInfoArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2NotifyErrorArg
typedef struct Itsk00126v2NotifyErrorArg
{
	u32_t								 testIdx;
	Itsk00126v2NotifyErrorContext		*context;
} Itsk00126v2NotifyErrorArg;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2NotifyErrorArg *Itsk00126v2NotifyErrorArg_new(u32_t testIdx, 
																				 Itsk00126v2NotifyErrorContext *context, Dz1Error *err);
static __inline__ Itsk00126v2NotifyErrorArg *Itsk00126v2NotifyErrorArg_gen(Dz1Error *err) { return Itsk00126v2NotifyErrorArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v2NotifyErrorArg_copy(Itsk00126v2NotifyErrorArg *dst, Itsk00126v2NotifyErrorArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2NotifyErrorArg *Itsk00126v2NotifyErrorArg_clone(Itsk00126v2NotifyErrorArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2NotifyErrorArg_purge(Itsk00126v2NotifyErrorArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2NotifyErrorArg_del(Itsk00126v2NotifyErrorArg *p);
static __inline__ void Itsk00126v2NotifyErrorArg_delAndSetNull(void *ptr)
{
	Itsk00126v2NotifyErrorArg **p = (Itsk00126v2NotifyErrorArg **)ptr;
	if (p) { Itsk00126v2NotifyErrorArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2NotifyErrorArg_dump(Itsk00126v2NotifyErrorArg *p, int tab);
// Itsk00126v2NotifyErrorArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2NotifyContextPresent
typedef enum Itsk00126v2NotifyContextPresent
{
	Itsk00126v2NotifyContextPresent_state,
	Itsk00126v2NotifyContextPresent_info,
	Itsk00126v2NotifyContextPresent_error,
	Itsk00126v2NotifyContextPresent_max
} Itsk00126v2NotifyContextPresent;

DZ1_CPPLINK str_t Itsk00126v2NotifyContextPresentStrA(Itsk00126v2NotifyContextPresent v);
DZ1_CPPLINK Itsk00126v2NotifyContextPresent Itsk00126v2NotifyContextPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Itsk00126v2NotifyContextPresentStrW(Itsk00126v2NotifyContextPresent v);
DZ1_CPPLINK Itsk00126v2NotifyContextPresent Itsk00126v2NotifyContextPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Itsk00126v2NotifyContextPresentStr Itsk00126v2NotifyContextPresentStrW
#define Itsk00126v2NotifyContextPresentFromStr Itsk00126v2NotifyContextPresentFromStrW
#else // UNICODE
#define Itsk00126v2NotifyContextPresentStr Itsk00126v2NotifyContextPresentStrA
#define Itsk00126v2NotifyContextPresentFromStr Itsk00126v2NotifyContextPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Itsk00126v2NotifyContextPresentStr Itsk00126v2NotifyContextPresentStrA
#define Itsk00126v2NotifyContextPresentFromStr Itsk00126v2NotifyContextPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2NotifyContextPresent *Itsk00126v2NotifyContextPresent_new(Itsk00126v2NotifyContextPresent *src, Dz1Error *err);
static __inline__ Itsk00126v2NotifyContextPresent *Itsk00126v2NotifyContextPresent_gen(Dz1Error *err) { Itsk00126v2NotifyContextPresent v = Itsk00126v2NotifyContextPresent_max; return Itsk00126v2NotifyContextPresent_new(&v, err); }
#define Itsk00126v2NotifyContextPresent_clone             Itsk00126v2NotifyContextPresent_new
static __inline__ void Itsk00126v2NotifyContextPresent_del(Itsk00126v2NotifyContextPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Itsk00126v2NotifyContextPresent_delAndSetNull(void *ptr)
{
	Itsk00126v2NotifyContextPresent **p = (Itsk00126v2NotifyContextPresent **)ptr;
	if (p != NULL) { Itsk00126v2NotifyContextPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2NotifyContextPresent_dump(Itsk00126v2NotifyContextPresent *v, int tab);
// Itsk00126v2NotifyContextPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2NotifyContext
typedef struct Itsk00126v2NotifyContext
{
	Itsk00126v2NotifyContextPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Itsk00126v2NotifyStateContext		*state;
		Itsk00126v2NotifyInfoContext		*info;
		Itsk00126v2NotifyErrorContext		*error;
	} x;
} Itsk00126v2NotifyContext;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2NotifyContext *Itsk00126v2NotifyContext_new(Itsk00126v2NotifyContextPresent present, void *ptr, Dz1Error *err);
static __inline__ Itsk00126v2NotifyContext *Itsk00126v2NotifyContext_gen(Dz1Error *err) { return Itsk00126v2NotifyContext_new(Itsk00126v2NotifyContextPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Itsk00126v2NotifyContext_copy(Itsk00126v2NotifyContext *dst, Itsk00126v2NotifyContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2NotifyContext *Itsk00126v2NotifyContext_clone(Itsk00126v2NotifyContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2NotifyContext_purge(Itsk00126v2NotifyContext *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2NotifyContext_del(Itsk00126v2NotifyContext *p);
static __inline__ void Itsk00126v2NotifyContext_delAndSetNull(void *ptr)
{
	Itsk00126v2NotifyContext **p = (Itsk00126v2NotifyContext **)ptr;
	if (p != NULL) { Itsk00126v2NotifyContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2NotifyContext_dump(Itsk00126v2NotifyContext *p, int tab);
// Itsk00126v2NotifyContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2ValidateContext
typedef struct Itsk00126v2ValidateContext
{
	Dz1Str							 testName;
	s64_t							 time;
	Dz1Binary						*raw;
	Dz1Binary						*data;
	Itsk00126v2ProcessStatusCode	 code;
	Dz1Str							 desc;
} Itsk00126v2ValidateContext;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2ValidateContext *Itsk00126v2ValidateContext_new(Dz1Str testName, 
																				   s64_t time, 
																				   Dz1Binary *raw, 
																				   Dz1Binary *data, 
																				   Itsk00126v2ProcessStatusCode code, 
																				   Dz1Str desc, Dz1Error *err);
static __inline__ Itsk00126v2ValidateContext *Itsk00126v2ValidateContext_gen(Dz1Error *err) { return Itsk00126v2ValidateContext_new(NULL, 0, NULL, NULL, Itsk00126v2ProcessStatusCode_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v2ValidateContext_copy(Itsk00126v2ValidateContext *dst, Itsk00126v2ValidateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2ValidateContext *Itsk00126v2ValidateContext_clone(Itsk00126v2ValidateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2ValidateContext_purge(Itsk00126v2ValidateContext *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2ValidateContext_del(Itsk00126v2ValidateContext *p);
static __inline__ void Itsk00126v2ValidateContext_delAndSetNull(void *ptr)
{
	Itsk00126v2ValidateContext **p = (Itsk00126v2ValidateContext **)ptr;
	if (p) { Itsk00126v2ValidateContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2ValidateContext_dump(Itsk00126v2ValidateContext *p, int tab);
// Itsk00126v2ValidateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2ValidateContextArg
typedef struct Itsk00126v2ValidateContextArg
{
	u32_t							 testIdx;
	Itsk00126v2ValidateContext		*context;
} Itsk00126v2ValidateContextArg;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2ValidateContextArg *Itsk00126v2ValidateContextArg_new(u32_t testIdx, 
																						 Itsk00126v2ValidateContext *context, Dz1Error *err);
static __inline__ Itsk00126v2ValidateContextArg *Itsk00126v2ValidateContextArg_gen(Dz1Error *err) { return Itsk00126v2ValidateContextArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v2ValidateContextArg_copy(Itsk00126v2ValidateContextArg *dst, Itsk00126v2ValidateContextArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2ValidateContextArg *Itsk00126v2ValidateContextArg_clone(Itsk00126v2ValidateContextArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2ValidateContextArg_purge(Itsk00126v2ValidateContextArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2ValidateContextArg_del(Itsk00126v2ValidateContextArg *p);
static __inline__ void Itsk00126v2ValidateContextArg_delAndSetNull(void *ptr)
{
	Itsk00126v2ValidateContextArg **p = (Itsk00126v2ValidateContextArg **)ptr;
	if (p) { Itsk00126v2ValidateContextArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2ValidateContextArg_dump(Itsk00126v2ValidateContextArg *p, int tab);
// Itsk00126v2ValidateContextArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2TestConfiguration_serverRole
typedef struct Itsk00126v2TestConfiguration_serverRole
{
	s64_t		local_port;
	Dz1Str		iot_im_device_id;
	bool_t		test_iot_im_device_sttus_info;
	bool_t		test_iot_device_list_response_info;
	bool_t		test_iot_device_sttus_info;
	bool_t		test_safety_signal_list_response_info;
} Itsk00126v2TestConfiguration_serverRole;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2TestConfiguration_serverRole *Itsk00126v2TestConfiguration_serverRole_new(s64_t local_port, 
																											 Dz1Str iot_im_device_id, 
																											 bool_t test_iot_im_device_sttus_info, 
																											 bool_t test_iot_device_list_response_info, 
																											 bool_t test_iot_device_sttus_info, 
																											 bool_t test_safety_signal_list_response_info, Dz1Error *err);
static __inline__ Itsk00126v2TestConfiguration_serverRole *Itsk00126v2TestConfiguration_serverRole_gen(Dz1Error *err) { return Itsk00126v2TestConfiguration_serverRole_new(0, NULL, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v2TestConfiguration_serverRole_copy(Itsk00126v2TestConfiguration_serverRole *dst, Itsk00126v2TestConfiguration_serverRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2TestConfiguration_serverRole *Itsk00126v2TestConfiguration_serverRole_clone(Itsk00126v2TestConfiguration_serverRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2TestConfiguration_serverRole_purge(Itsk00126v2TestConfiguration_serverRole *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2TestConfiguration_serverRole_del(Itsk00126v2TestConfiguration_serverRole *p);
static __inline__ void Itsk00126v2TestConfiguration_serverRole_delAndSetNull(void *ptr)
{
	Itsk00126v2TestConfiguration_serverRole **p = (Itsk00126v2TestConfiguration_serverRole **)ptr;
	if (p) { Itsk00126v2TestConfiguration_serverRole_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2TestConfiguration_serverRole_dump(Itsk00126v2TestConfiguration_serverRole *p, int tab);
// Itsk00126v2TestConfiguration_serverRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2TestConfiguration_clientRole
typedef struct Itsk00126v2TestConfiguration_clientRole
{
	Dz1Str		peer_ip;
	bool_t		peer_port;
} Itsk00126v2TestConfiguration_clientRole;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2TestConfiguration_clientRole *Itsk00126v2TestConfiguration_clientRole_new(Dz1Str peer_ip, 
																											 bool_t peer_port, Dz1Error *err);
static __inline__ Itsk00126v2TestConfiguration_clientRole *Itsk00126v2TestConfiguration_clientRole_gen(Dz1Error *err) { return Itsk00126v2TestConfiguration_clientRole_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v2TestConfiguration_clientRole_copy(Itsk00126v2TestConfiguration_clientRole *dst, Itsk00126v2TestConfiguration_clientRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2TestConfiguration_clientRole *Itsk00126v2TestConfiguration_clientRole_clone(Itsk00126v2TestConfiguration_clientRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2TestConfiguration_clientRole_purge(Itsk00126v2TestConfiguration_clientRole *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2TestConfiguration_clientRole_del(Itsk00126v2TestConfiguration_clientRole *p);
static __inline__ void Itsk00126v2TestConfiguration_clientRole_delAndSetNull(void *ptr)
{
	Itsk00126v2TestConfiguration_clientRole **p = (Itsk00126v2TestConfiguration_clientRole **)ptr;
	if (p) { Itsk00126v2TestConfiguration_clientRole_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2TestConfiguration_clientRole_dump(Itsk00126v2TestConfiguration_clientRole *p, int tab);
// Itsk00126v2TestConfiguration_clientRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2TestConfigurationPresent
typedef enum Itsk00126v2TestConfigurationPresent
{
	Itsk00126v2TestConfigurationPresent_serverRole,
	Itsk00126v2TestConfigurationPresent_clientRole,
	Itsk00126v2TestConfigurationPresent_max
} Itsk00126v2TestConfigurationPresent;

DZ1_CPPLINK str_t Itsk00126v2TestConfigurationPresentStrA(Itsk00126v2TestConfigurationPresent v);
DZ1_CPPLINK Itsk00126v2TestConfigurationPresent Itsk00126v2TestConfigurationPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Itsk00126v2TestConfigurationPresentStrW(Itsk00126v2TestConfigurationPresent v);
DZ1_CPPLINK Itsk00126v2TestConfigurationPresent Itsk00126v2TestConfigurationPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Itsk00126v2TestConfigurationPresentStr Itsk00126v2TestConfigurationPresentStrW
#define Itsk00126v2TestConfigurationPresentFromStr Itsk00126v2TestConfigurationPresentFromStrW
#else // UNICODE
#define Itsk00126v2TestConfigurationPresentStr Itsk00126v2TestConfigurationPresentStrA
#define Itsk00126v2TestConfigurationPresentFromStr Itsk00126v2TestConfigurationPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Itsk00126v2TestConfigurationPresentStr Itsk00126v2TestConfigurationPresentStrA
#define Itsk00126v2TestConfigurationPresentFromStr Itsk00126v2TestConfigurationPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2TestConfigurationPresent *Itsk00126v2TestConfigurationPresent_new(Itsk00126v2TestConfigurationPresent *src, Dz1Error *err);
static __inline__ Itsk00126v2TestConfigurationPresent *Itsk00126v2TestConfigurationPresent_gen(Dz1Error *err) { Itsk00126v2TestConfigurationPresent v = Itsk00126v2TestConfigurationPresent_max; return Itsk00126v2TestConfigurationPresent_new(&v, err); }
#define Itsk00126v2TestConfigurationPresent_clone             Itsk00126v2TestConfigurationPresent_new
static __inline__ void Itsk00126v2TestConfigurationPresent_del(Itsk00126v2TestConfigurationPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Itsk00126v2TestConfigurationPresent_delAndSetNull(void *ptr)
{
	Itsk00126v2TestConfigurationPresent **p = (Itsk00126v2TestConfigurationPresent **)ptr;
	if (p != NULL) { Itsk00126v2TestConfigurationPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2TestConfigurationPresent_dump(Itsk00126v2TestConfigurationPresent *v, int tab);
// Itsk00126v2TestConfigurationPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2TestConfiguration
typedef struct Itsk00126v2TestConfiguration
{
	Itsk00126v2TestConfigurationPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Itsk00126v2TestConfiguration_serverRole		*serverRole;
		Itsk00126v2TestConfiguration_clientRole		*clientRole;
	} x;
} Itsk00126v2TestConfiguration;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2TestConfiguration *Itsk00126v2TestConfiguration_new(Itsk00126v2TestConfigurationPresent present, void *ptr, Dz1Error *err);
static __inline__ Itsk00126v2TestConfiguration *Itsk00126v2TestConfiguration_gen(Dz1Error *err) { return Itsk00126v2TestConfiguration_new(Itsk00126v2TestConfigurationPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Itsk00126v2TestConfiguration_copy(Itsk00126v2TestConfiguration *dst, Itsk00126v2TestConfiguration *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v2TestConfiguration *Itsk00126v2TestConfiguration_clone(Itsk00126v2TestConfiguration *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2TestConfiguration_purge(Itsk00126v2TestConfiguration *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2TestConfiguration_del(Itsk00126v2TestConfiguration *p);
static __inline__ void Itsk00126v2TestConfiguration_delAndSetNull(void *ptr)
{
	Itsk00126v2TestConfiguration **p = (Itsk00126v2TestConfiguration **)ptr;
	if (p != NULL) { Itsk00126v2TestConfiguration_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v2TestConfiguration_dump(Itsk00126v2TestConfiguration *p, int tab);
// Itsk00126v2TestConfiguration
////////////////////////////////////////////////////////////////////////////////

#endif

#ifndef _DZ1_TDC_ITSK00126V1_TEST_SCENARIO_DEF_H_
#define _DZ1_TDC_ITSK00126V1_TEST_SCENARIO_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "Itsk00126v1TestMsgDef.h"

////////////////////////////////////////////////////////////////////////////////
// Itsk00126V1TestScenarioException
typedef void (*Itsk00126V1TestScenarioException)(void *exceptionArg, Dz1Error *reason);
// Itsk00126V1TestScenarioException
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1ProcessStatusCode
typedef enum Itsk00126v1ProcessStatusCode
{
	Itsk00126v1ProcessStatusCode_OK = 0,
	Itsk00126v1ProcessStatusCode_FAILURE = 1,
	Itsk00126v1ProcessStatusCode_AGENT_SYSTEM_ERROR = 11,
	Itsk00126v1ProcessStatusCode_SERVER_DISCONNECTED = 12,
	Itsk00126v1ProcessStatusCode_TEST_CONFIGURATION_ERROR = 13,
	Itsk00126v1ProcessStatusCode_CONNECTION_FAIL = 100,
	Itsk00126v1ProcessStatusCode_DISCONNECTED = 101,
	Itsk00126v1ProcessStatusCode_TIMEOUT = 102,
	Itsk00126v1ProcessStatusCode_OUT_OF_RANGE = 201,
	Itsk00126v1ProcessStatusCode_INVALID_PROCESS,
	Itsk00126v1ProcessStatusCode_INVALID_IDENTIFIER,
	Itsk00126v1ProcessStatusCode_SESSION_DUPLICATE,
	Itsk00126v1ProcessStatusCode_LOGIN_AUTH_ERROR,
	Itsk00126v1ProcessStatusCode_DECODE_FAIL = 210,
	Itsk00126v1ProcessStatusCode_INVALID_ENCODING_RULE = 211,
	Itsk00126v1ProcessStatusCode_INVALID_OID = 212,
	Itsk00126v1ProcessStatusCode_INVALID_DSRC_MSG_ID = 213,
	Itsk00126v1ProcessStatusCode_JSON_PARSE_ERROR = 221,
	Itsk00126v1ProcessStatusCode_PROTOBUF_DESERAILIZE_ERROR = 231,
	Itsk00126v1ProcessStatusCode_INVALID_TOPIC = 241,
	Itsk00126v1ProcessStatusCode_INVALID_REQUEST = 251,
	Itsk00126v1ProcessStatusCode_UNKNOWN = 300,
	Itsk00126v1ProcessStatusCode_max
} Itsk00126v1ProcessStatusCode;

DZ1_CPPLINK str_t Itsk00126v1ProcessStatusCodeStrA(Itsk00126v1ProcessStatusCode v);
DZ1_CPPLINK Itsk00126v1ProcessStatusCode Itsk00126v1ProcessStatusCodeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Itsk00126v1ProcessStatusCodeStrW(Itsk00126v1ProcessStatusCode v);
DZ1_CPPLINK Itsk00126v1ProcessStatusCode Itsk00126v1ProcessStatusCodeFromStrW(wstr_t str);
#ifdef UNICODE
#define Itsk00126v1ProcessStatusCodeStr Itsk00126v1ProcessStatusCodeStrW
#define Itsk00126v1ProcessStatusCodeFromStr Itsk00126v1ProcessStatusCodeFromStrW
#else // UNICODE
#define Itsk00126v1ProcessStatusCodeStr Itsk00126v1ProcessStatusCodeStrA
#define Itsk00126v1ProcessStatusCodeFromStr Itsk00126v1ProcessStatusCodeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Itsk00126v1ProcessStatusCodeStr Itsk00126v1ProcessStatusCodeStrA
#define Itsk00126v1ProcessStatusCodeFromStr Itsk00126v1ProcessStatusCodeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1ProcessStatusCode *Itsk00126v1ProcessStatusCode_new(Itsk00126v1ProcessStatusCode *src, Dz1Error *err);
static __inline__ Itsk00126v1ProcessStatusCode *Itsk00126v1ProcessStatusCode_gen(Dz1Error *err) { Itsk00126v1ProcessStatusCode v = Itsk00126v1ProcessStatusCode_max; return Itsk00126v1ProcessStatusCode_new(&v, err); }
#define Itsk00126v1ProcessStatusCode_clone             Itsk00126v1ProcessStatusCode_new
static __inline__ void Itsk00126v1ProcessStatusCode_del(Itsk00126v1ProcessStatusCode *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Itsk00126v1ProcessStatusCode_delAndSetNull(void *ptr)
{
	Itsk00126v1ProcessStatusCode **p = (Itsk00126v1ProcessStatusCode **)ptr;
	if (p != NULL) { Itsk00126v1ProcessStatusCode_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ProcessStatusCode_dump(Itsk00126v1ProcessStatusCode *v, int tab);
// Itsk00126v1ProcessStatusCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1NotifyStateContext
typedef struct Itsk00126v1NotifyStateContext
{
	Dz1Str		testName;
	s64_t		time;
	Dz1Str		state;
} Itsk00126v1NotifyStateContext;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1NotifyStateContext *Itsk00126v1NotifyStateContext_new(Dz1Str testName, 
																						 s64_t time, 
																						 Dz1Str state, Dz1Error *err);
static __inline__ Itsk00126v1NotifyStateContext *Itsk00126v1NotifyStateContext_gen(Dz1Error *err) { return Itsk00126v1NotifyStateContext_new(NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v1NotifyStateContext_copy(Itsk00126v1NotifyStateContext *dst, Itsk00126v1NotifyStateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1NotifyStateContext *Itsk00126v1NotifyStateContext_clone(Itsk00126v1NotifyStateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1NotifyStateContext_purge(Itsk00126v1NotifyStateContext *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1NotifyStateContext_del(Itsk00126v1NotifyStateContext *p);
static __inline__ void Itsk00126v1NotifyStateContext_delAndSetNull(void *ptr)
{
	Itsk00126v1NotifyStateContext **p = (Itsk00126v1NotifyStateContext **)ptr;
	if (p) { Itsk00126v1NotifyStateContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1NotifyStateContext_dump(Itsk00126v1NotifyStateContext *p, int tab);
// Itsk00126v1NotifyStateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1NotifyInfoContext
typedef struct Itsk00126v1NotifyInfoContext
{
	Dz1Str			 testName;
	s64_t			 time;
	Dz1Str			 sender;
	Dz1Str			 log;
	Dz1Binary		*data;
	Dz1Str			 dataType;
} Itsk00126v1NotifyInfoContext;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1NotifyInfoContext *Itsk00126v1NotifyInfoContext_new(Dz1Str testName, 
																					   s64_t time, 
																					   Dz1Str sender, 
																					   Dz1Str log, 
																					   Dz1Binary *data, 
																					   Dz1Str dataType, Dz1Error *err);
static __inline__ Itsk00126v1NotifyInfoContext *Itsk00126v1NotifyInfoContext_gen(Dz1Error *err) { return Itsk00126v1NotifyInfoContext_new(NULL, 0, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v1NotifyInfoContext_copy(Itsk00126v1NotifyInfoContext *dst, Itsk00126v1NotifyInfoContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1NotifyInfoContext *Itsk00126v1NotifyInfoContext_clone(Itsk00126v1NotifyInfoContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1NotifyInfoContext_purge(Itsk00126v1NotifyInfoContext *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1NotifyInfoContext_del(Itsk00126v1NotifyInfoContext *p);
static __inline__ void Itsk00126v1NotifyInfoContext_delAndSetNull(void *ptr)
{
	Itsk00126v1NotifyInfoContext **p = (Itsk00126v1NotifyInfoContext **)ptr;
	if (p) { Itsk00126v1NotifyInfoContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1NotifyInfoContext_dump(Itsk00126v1NotifyInfoContext *p, int tab);
// Itsk00126v1NotifyInfoContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1NotifyErrorContext
typedef struct Itsk00126v1NotifyErrorContext
{
	Dz1Str							 testName;
	s64_t							 time;
	Itsk00126v1ProcessStatusCode	 code;
	Dz1Str							 desc;
	Dz1Str							 log;
	Dz1Binary						*data;
} Itsk00126v1NotifyErrorContext;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1NotifyErrorContext *Itsk00126v1NotifyErrorContext_new(Dz1Str testName, 
																						 s64_t time, 
																						 Itsk00126v1ProcessStatusCode code, 
																						 Dz1Str desc, 
																						 Dz1Str log, 
																						 Dz1Binary *data, Dz1Error *err);
static __inline__ Itsk00126v1NotifyErrorContext *Itsk00126v1NotifyErrorContext_gen(Dz1Error *err) { return Itsk00126v1NotifyErrorContext_new(NULL, 0, Itsk00126v1ProcessStatusCode_max, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v1NotifyErrorContext_copy(Itsk00126v1NotifyErrorContext *dst, Itsk00126v1NotifyErrorContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1NotifyErrorContext *Itsk00126v1NotifyErrorContext_clone(Itsk00126v1NotifyErrorContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1NotifyErrorContext_purge(Itsk00126v1NotifyErrorContext *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1NotifyErrorContext_del(Itsk00126v1NotifyErrorContext *p);
static __inline__ void Itsk00126v1NotifyErrorContext_delAndSetNull(void *ptr)
{
	Itsk00126v1NotifyErrorContext **p = (Itsk00126v1NotifyErrorContext **)ptr;
	if (p) { Itsk00126v1NotifyErrorContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1NotifyErrorContext_dump(Itsk00126v1NotifyErrorContext *p, int tab);
// Itsk00126v1NotifyErrorContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1NotifyStateArg
typedef struct Itsk00126v1NotifyStateArg
{
	u32_t								 testIdx;
	Itsk00126v1NotifyStateContext		*context;
} Itsk00126v1NotifyStateArg;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1NotifyStateArg *Itsk00126v1NotifyStateArg_new(u32_t testIdx, 
																				 Itsk00126v1NotifyStateContext *context, Dz1Error *err);
static __inline__ Itsk00126v1NotifyStateArg *Itsk00126v1NotifyStateArg_gen(Dz1Error *err) { return Itsk00126v1NotifyStateArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v1NotifyStateArg_copy(Itsk00126v1NotifyStateArg *dst, Itsk00126v1NotifyStateArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1NotifyStateArg *Itsk00126v1NotifyStateArg_clone(Itsk00126v1NotifyStateArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1NotifyStateArg_purge(Itsk00126v1NotifyStateArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1NotifyStateArg_del(Itsk00126v1NotifyStateArg *p);
static __inline__ void Itsk00126v1NotifyStateArg_delAndSetNull(void *ptr)
{
	Itsk00126v1NotifyStateArg **p = (Itsk00126v1NotifyStateArg **)ptr;
	if (p) { Itsk00126v1NotifyStateArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1NotifyStateArg_dump(Itsk00126v1NotifyStateArg *p, int tab);
// Itsk00126v1NotifyStateArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1NotifyInfoArg
typedef struct Itsk00126v1NotifyInfoArg
{
	u32_t							 testIdx;
	Itsk00126v1NotifyInfoContext	*context;
} Itsk00126v1NotifyInfoArg;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1NotifyInfoArg *Itsk00126v1NotifyInfoArg_new(u32_t testIdx, 
																			   Itsk00126v1NotifyInfoContext *context, Dz1Error *err);
static __inline__ Itsk00126v1NotifyInfoArg *Itsk00126v1NotifyInfoArg_gen(Dz1Error *err) { return Itsk00126v1NotifyInfoArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v1NotifyInfoArg_copy(Itsk00126v1NotifyInfoArg *dst, Itsk00126v1NotifyInfoArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1NotifyInfoArg *Itsk00126v1NotifyInfoArg_clone(Itsk00126v1NotifyInfoArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1NotifyInfoArg_purge(Itsk00126v1NotifyInfoArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1NotifyInfoArg_del(Itsk00126v1NotifyInfoArg *p);
static __inline__ void Itsk00126v1NotifyInfoArg_delAndSetNull(void *ptr)
{
	Itsk00126v1NotifyInfoArg **p = (Itsk00126v1NotifyInfoArg **)ptr;
	if (p) { Itsk00126v1NotifyInfoArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1NotifyInfoArg_dump(Itsk00126v1NotifyInfoArg *p, int tab);
// Itsk00126v1NotifyInfoArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1NotifyErrorArg
typedef struct Itsk00126v1NotifyErrorArg
{
	u32_t								 testIdx;
	Itsk00126v1NotifyErrorContext		*context;
} Itsk00126v1NotifyErrorArg;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1NotifyErrorArg *Itsk00126v1NotifyErrorArg_new(u32_t testIdx, 
																				 Itsk00126v1NotifyErrorContext *context, Dz1Error *err);
static __inline__ Itsk00126v1NotifyErrorArg *Itsk00126v1NotifyErrorArg_gen(Dz1Error *err) { return Itsk00126v1NotifyErrorArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v1NotifyErrorArg_copy(Itsk00126v1NotifyErrorArg *dst, Itsk00126v1NotifyErrorArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1NotifyErrorArg *Itsk00126v1NotifyErrorArg_clone(Itsk00126v1NotifyErrorArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1NotifyErrorArg_purge(Itsk00126v1NotifyErrorArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1NotifyErrorArg_del(Itsk00126v1NotifyErrorArg *p);
static __inline__ void Itsk00126v1NotifyErrorArg_delAndSetNull(void *ptr)
{
	Itsk00126v1NotifyErrorArg **p = (Itsk00126v1NotifyErrorArg **)ptr;
	if (p) { Itsk00126v1NotifyErrorArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1NotifyErrorArg_dump(Itsk00126v1NotifyErrorArg *p, int tab);
// Itsk00126v1NotifyErrorArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1NotifyContextPresent
typedef enum Itsk00126v1NotifyContextPresent
{
	Itsk00126v1NotifyContextPresent_state,
	Itsk00126v1NotifyContextPresent_info,
	Itsk00126v1NotifyContextPresent_error,
	Itsk00126v1NotifyContextPresent_max
} Itsk00126v1NotifyContextPresent;

DZ1_CPPLINK str_t Itsk00126v1NotifyContextPresentStrA(Itsk00126v1NotifyContextPresent v);
DZ1_CPPLINK Itsk00126v1NotifyContextPresent Itsk00126v1NotifyContextPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Itsk00126v1NotifyContextPresentStrW(Itsk00126v1NotifyContextPresent v);
DZ1_CPPLINK Itsk00126v1NotifyContextPresent Itsk00126v1NotifyContextPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Itsk00126v1NotifyContextPresentStr Itsk00126v1NotifyContextPresentStrW
#define Itsk00126v1NotifyContextPresentFromStr Itsk00126v1NotifyContextPresentFromStrW
#else // UNICODE
#define Itsk00126v1NotifyContextPresentStr Itsk00126v1NotifyContextPresentStrA
#define Itsk00126v1NotifyContextPresentFromStr Itsk00126v1NotifyContextPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Itsk00126v1NotifyContextPresentStr Itsk00126v1NotifyContextPresentStrA
#define Itsk00126v1NotifyContextPresentFromStr Itsk00126v1NotifyContextPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1NotifyContextPresent *Itsk00126v1NotifyContextPresent_new(Itsk00126v1NotifyContextPresent *src, Dz1Error *err);
static __inline__ Itsk00126v1NotifyContextPresent *Itsk00126v1NotifyContextPresent_gen(Dz1Error *err) { Itsk00126v1NotifyContextPresent v = Itsk00126v1NotifyContextPresent_max; return Itsk00126v1NotifyContextPresent_new(&v, err); }
#define Itsk00126v1NotifyContextPresent_clone             Itsk00126v1NotifyContextPresent_new
static __inline__ void Itsk00126v1NotifyContextPresent_del(Itsk00126v1NotifyContextPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Itsk00126v1NotifyContextPresent_delAndSetNull(void *ptr)
{
	Itsk00126v1NotifyContextPresent **p = (Itsk00126v1NotifyContextPresent **)ptr;
	if (p != NULL) { Itsk00126v1NotifyContextPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1NotifyContextPresent_dump(Itsk00126v1NotifyContextPresent *v, int tab);
// Itsk00126v1NotifyContextPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1NotifyContext
typedef struct Itsk00126v1NotifyContext
{
	Itsk00126v1NotifyContextPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Itsk00126v1NotifyStateContext		*state;
		Itsk00126v1NotifyInfoContext		*info;
		Itsk00126v1NotifyErrorContext		*error;
	} x;
} Itsk00126v1NotifyContext;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1NotifyContext *Itsk00126v1NotifyContext_new(Itsk00126v1NotifyContextPresent present, void *ptr, Dz1Error *err);
static __inline__ Itsk00126v1NotifyContext *Itsk00126v1NotifyContext_gen(Dz1Error *err) { return Itsk00126v1NotifyContext_new(Itsk00126v1NotifyContextPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Itsk00126v1NotifyContext_copy(Itsk00126v1NotifyContext *dst, Itsk00126v1NotifyContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1NotifyContext *Itsk00126v1NotifyContext_clone(Itsk00126v1NotifyContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1NotifyContext_purge(Itsk00126v1NotifyContext *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1NotifyContext_del(Itsk00126v1NotifyContext *p);
static __inline__ void Itsk00126v1NotifyContext_delAndSetNull(void *ptr)
{
	Itsk00126v1NotifyContext **p = (Itsk00126v1NotifyContext **)ptr;
	if (p != NULL) { Itsk00126v1NotifyContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1NotifyContext_dump(Itsk00126v1NotifyContext *p, int tab);
// Itsk00126v1NotifyContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1ValidateContext
typedef struct Itsk00126v1ValidateContext
{
	Dz1Str							 testName;
	s64_t							 time;
	Dz1Binary						*raw;
	Dz1Binary						*data;
	Itsk00126v1ProcessStatusCode	 code;
	Dz1Str							 desc;
} Itsk00126v1ValidateContext;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1ValidateContext *Itsk00126v1ValidateContext_new(Dz1Str testName, 
																				   s64_t time, 
																				   Dz1Binary *raw, 
																				   Dz1Binary *data, 
																				   Itsk00126v1ProcessStatusCode code, 
																				   Dz1Str desc, Dz1Error *err);
static __inline__ Itsk00126v1ValidateContext *Itsk00126v1ValidateContext_gen(Dz1Error *err) { return Itsk00126v1ValidateContext_new(NULL, 0, NULL, NULL, Itsk00126v1ProcessStatusCode_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v1ValidateContext_copy(Itsk00126v1ValidateContext *dst, Itsk00126v1ValidateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1ValidateContext *Itsk00126v1ValidateContext_clone(Itsk00126v1ValidateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ValidateContext_purge(Itsk00126v1ValidateContext *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ValidateContext_del(Itsk00126v1ValidateContext *p);
static __inline__ void Itsk00126v1ValidateContext_delAndSetNull(void *ptr)
{
	Itsk00126v1ValidateContext **p = (Itsk00126v1ValidateContext **)ptr;
	if (p) { Itsk00126v1ValidateContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ValidateContext_dump(Itsk00126v1ValidateContext *p, int tab);
// Itsk00126v1ValidateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1ValidateContextArg
typedef struct Itsk00126v1ValidateContextArg
{
	u32_t							 testIdx;
	Itsk00126v1ValidateContext		*context;
} Itsk00126v1ValidateContextArg;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1ValidateContextArg *Itsk00126v1ValidateContextArg_new(u32_t testIdx, 
																						 Itsk00126v1ValidateContext *context, Dz1Error *err);
static __inline__ Itsk00126v1ValidateContextArg *Itsk00126v1ValidateContextArg_gen(Dz1Error *err) { return Itsk00126v1ValidateContextArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v1ValidateContextArg_copy(Itsk00126v1ValidateContextArg *dst, Itsk00126v1ValidateContextArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1ValidateContextArg *Itsk00126v1ValidateContextArg_clone(Itsk00126v1ValidateContextArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ValidateContextArg_purge(Itsk00126v1ValidateContextArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ValidateContextArg_del(Itsk00126v1ValidateContextArg *p);
static __inline__ void Itsk00126v1ValidateContextArg_delAndSetNull(void *ptr)
{
	Itsk00126v1ValidateContextArg **p = (Itsk00126v1ValidateContextArg **)ptr;
	if (p) { Itsk00126v1ValidateContextArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1ValidateContextArg_dump(Itsk00126v1ValidateContextArg *p, int tab);
// Itsk00126v1ValidateContextArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1TestConfiguration_serverRole
typedef struct Itsk00126v1TestConfiguration_serverRole
{
	s64_t		local_port;
	Dz1Str		local_center_id;
	bool_t		test_iot_im_device_sttus_info;
	bool_t		test_iot_device_list_response_info;
	bool_t		test_iot_device_sttus_info;
	bool_t		test_safety_signal_list_response_info;
} Itsk00126v1TestConfiguration_serverRole;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1TestConfiguration_serverRole *Itsk00126v1TestConfiguration_serverRole_new(s64_t local_port, 
																											 Dz1Str local_center_id, 
																											 bool_t test_iot_im_device_sttus_info, 
																											 bool_t test_iot_device_list_response_info, 
																											 bool_t test_iot_device_sttus_info, 
																											 bool_t test_safety_signal_list_response_info, Dz1Error *err);
static __inline__ Itsk00126v1TestConfiguration_serverRole *Itsk00126v1TestConfiguration_serverRole_gen(Dz1Error *err) { return Itsk00126v1TestConfiguration_serverRole_new(0, NULL, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v1TestConfiguration_serverRole_copy(Itsk00126v1TestConfiguration_serverRole *dst, Itsk00126v1TestConfiguration_serverRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1TestConfiguration_serverRole *Itsk00126v1TestConfiguration_serverRole_clone(Itsk00126v1TestConfiguration_serverRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1TestConfiguration_serverRole_purge(Itsk00126v1TestConfiguration_serverRole *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1TestConfiguration_serverRole_del(Itsk00126v1TestConfiguration_serverRole *p);
static __inline__ void Itsk00126v1TestConfiguration_serverRole_delAndSetNull(void *ptr)
{
	Itsk00126v1TestConfiguration_serverRole **p = (Itsk00126v1TestConfiguration_serverRole **)ptr;
	if (p) { Itsk00126v1TestConfiguration_serverRole_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1TestConfiguration_serverRole_dump(Itsk00126v1TestConfiguration_serverRole *p, int tab);
// Itsk00126v1TestConfiguration_serverRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1TestConfiguration_clientRole
typedef struct Itsk00126v1TestConfiguration_clientRole
{
	Dz1Str		peer_ip;
	bool_t		peer_port;
} Itsk00126v1TestConfiguration_clientRole;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1TestConfiguration_clientRole *Itsk00126v1TestConfiguration_clientRole_new(Dz1Str peer_ip, 
																											 bool_t peer_port, Dz1Error *err);
static __inline__ Itsk00126v1TestConfiguration_clientRole *Itsk00126v1TestConfiguration_clientRole_gen(Dz1Error *err) { return Itsk00126v1TestConfiguration_clientRole_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Itsk00126v1TestConfiguration_clientRole_copy(Itsk00126v1TestConfiguration_clientRole *dst, Itsk00126v1TestConfiguration_clientRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1TestConfiguration_clientRole *Itsk00126v1TestConfiguration_clientRole_clone(Itsk00126v1TestConfiguration_clientRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1TestConfiguration_clientRole_purge(Itsk00126v1TestConfiguration_clientRole *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1TestConfiguration_clientRole_del(Itsk00126v1TestConfiguration_clientRole *p);
static __inline__ void Itsk00126v1TestConfiguration_clientRole_delAndSetNull(void *ptr)
{
	Itsk00126v1TestConfiguration_clientRole **p = (Itsk00126v1TestConfiguration_clientRole **)ptr;
	if (p) { Itsk00126v1TestConfiguration_clientRole_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1TestConfiguration_clientRole_dump(Itsk00126v1TestConfiguration_clientRole *p, int tab);
// Itsk00126v1TestConfiguration_clientRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1TestConfigurationPresent
typedef enum Itsk00126v1TestConfigurationPresent
{
	Itsk00126v1TestConfigurationPresent_serverRole,
	Itsk00126v1TestConfigurationPresent_clientRole,
	Itsk00126v1TestConfigurationPresent_max
} Itsk00126v1TestConfigurationPresent;

DZ1_CPPLINK str_t Itsk00126v1TestConfigurationPresentStrA(Itsk00126v1TestConfigurationPresent v);
DZ1_CPPLINK Itsk00126v1TestConfigurationPresent Itsk00126v1TestConfigurationPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Itsk00126v1TestConfigurationPresentStrW(Itsk00126v1TestConfigurationPresent v);
DZ1_CPPLINK Itsk00126v1TestConfigurationPresent Itsk00126v1TestConfigurationPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Itsk00126v1TestConfigurationPresentStr Itsk00126v1TestConfigurationPresentStrW
#define Itsk00126v1TestConfigurationPresentFromStr Itsk00126v1TestConfigurationPresentFromStrW
#else // UNICODE
#define Itsk00126v1TestConfigurationPresentStr Itsk00126v1TestConfigurationPresentStrA
#define Itsk00126v1TestConfigurationPresentFromStr Itsk00126v1TestConfigurationPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Itsk00126v1TestConfigurationPresentStr Itsk00126v1TestConfigurationPresentStrA
#define Itsk00126v1TestConfigurationPresentFromStr Itsk00126v1TestConfigurationPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1TestConfigurationPresent *Itsk00126v1TestConfigurationPresent_new(Itsk00126v1TestConfigurationPresent *src, Dz1Error *err);
static __inline__ Itsk00126v1TestConfigurationPresent *Itsk00126v1TestConfigurationPresent_gen(Dz1Error *err) { Itsk00126v1TestConfigurationPresent v = Itsk00126v1TestConfigurationPresent_max; return Itsk00126v1TestConfigurationPresent_new(&v, err); }
#define Itsk00126v1TestConfigurationPresent_clone             Itsk00126v1TestConfigurationPresent_new
static __inline__ void Itsk00126v1TestConfigurationPresent_del(Itsk00126v1TestConfigurationPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Itsk00126v1TestConfigurationPresent_delAndSetNull(void *ptr)
{
	Itsk00126v1TestConfigurationPresent **p = (Itsk00126v1TestConfigurationPresent **)ptr;
	if (p != NULL) { Itsk00126v1TestConfigurationPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1TestConfigurationPresent_dump(Itsk00126v1TestConfigurationPresent *v, int tab);
// Itsk00126v1TestConfigurationPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1TestConfiguration
typedef struct Itsk00126v1TestConfiguration
{
	Itsk00126v1TestConfigurationPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Itsk00126v1TestConfiguration_serverRole		*serverRole;
		Itsk00126v1TestConfiguration_clientRole		*clientRole;
	} x;
} Itsk00126v1TestConfiguration;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1TestConfiguration *Itsk00126v1TestConfiguration_new(Itsk00126v1TestConfigurationPresent present, void *ptr, Dz1Error *err);
static __inline__ Itsk00126v1TestConfiguration *Itsk00126v1TestConfiguration_gen(Dz1Error *err) { return Itsk00126v1TestConfiguration_new(Itsk00126v1TestConfigurationPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  Itsk00126v1TestConfiguration_copy(Itsk00126v1TestConfiguration *dst, Itsk00126v1TestConfiguration *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Itsk00126v1TestConfiguration *Itsk00126v1TestConfiguration_clone(Itsk00126v1TestConfiguration *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1TestConfiguration_purge(Itsk00126v1TestConfiguration *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1TestConfiguration_del(Itsk00126v1TestConfiguration *p);
static __inline__ void Itsk00126v1TestConfiguration_delAndSetNull(void *ptr)
{
	Itsk00126v1TestConfiguration **p = (Itsk00126v1TestConfiguration **)ptr;
	if (p != NULL) { Itsk00126v1TestConfiguration_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126v1TestConfiguration_dump(Itsk00126v1TestConfiguration *p, int tab);
// Itsk00126v1TestConfiguration
////////////////////////////////////////////////////////////////////////////////

#endif

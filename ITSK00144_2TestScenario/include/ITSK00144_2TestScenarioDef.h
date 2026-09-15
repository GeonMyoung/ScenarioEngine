#ifndef _DZ1_TDC_I_T_S_K00144_2_TEST_SCENARIO_DEF_H_
#define _DZ1_TDC_I_T_S_K00144_2_TEST_SCENARIO_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "ITSK00144_2TestMsgDef.h"
#include "GitsnAsnUtilDef.h"

////////////////////////////////////////////////////////////////////////////////
// ITSK001442TestScenarioException
typedef void (*ITSK001442TestScenarioException)(void *exceptionArg, Dz1Error *reason);
// ITSK001442TestScenarioException
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ProcessStatusCode
typedef enum ITSK00144_2ProcessStatusCode
{
	ITSK00144_2ProcessStatusCode_OK = 0,
	ITSK00144_2ProcessStatusCode_FAILURE = 1,
	ITSK00144_2ProcessStatusCode_AGENT_SYSTEM_ERROR = 11,
	ITSK00144_2ProcessStatusCode_SERVER_DISCONNECTED = 12,
	ITSK00144_2ProcessStatusCode_TEST_CONFIGURATION_ERROR = 13,
	ITSK00144_2ProcessStatusCode_CONNECTION_FAIL = 100,
	ITSK00144_2ProcessStatusCode_DISCONNECTED = 101,
	ITSK00144_2ProcessStatusCode_TIMEOUT = 102,
	ITSK00144_2ProcessStatusCode_OUT_OF_RANGE = 201,
	ITSK00144_2ProcessStatusCode_INVALID_PROCESS,
	ITSK00144_2ProcessStatusCode_INVALID_IDENTIFIER,
	ITSK00144_2ProcessStatusCode_SESSION_DUPLICATE,
	ITSK00144_2ProcessStatusCode_LOGIN_AUTH_ERROR,
	ITSK00144_2ProcessStatusCode_DECODE_FAIL = 210,
	ITSK00144_2ProcessStatusCode_INVALID_ENCODING_RULE = 211,
	ITSK00144_2ProcessStatusCode_INVALID_OID = 212,
	ITSK00144_2ProcessStatusCode_INVALID_DSRC_MSG_ID = 213,
	ITSK00144_2ProcessStatusCode_JSON_PARSE_ERROR = 221,
	ITSK00144_2ProcessStatusCode_PROTOBUF_DESERAILIZE_ERROR = 231,
	ITSK00144_2ProcessStatusCode_INVALID_TOPIC = 241,
	ITSK00144_2ProcessStatusCode_INVALID_REQUEST = 251,
	ITSK00144_2ProcessStatusCode_UNKNOWN = 300,
	ITSK00144_2ProcessStatusCode_max
} ITSK00144_2ProcessStatusCode;

DZ1_CPPLINK str_t ITSK00144_2ProcessStatusCodeStrA(ITSK00144_2ProcessStatusCode v);
DZ1_CPPLINK ITSK00144_2ProcessStatusCode ITSK00144_2ProcessStatusCodeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ITSK00144_2ProcessStatusCodeStrW(ITSK00144_2ProcessStatusCode v);
DZ1_CPPLINK ITSK00144_2ProcessStatusCode ITSK00144_2ProcessStatusCodeFromStrW(wstr_t str);
#ifdef UNICODE
#define ITSK00144_2ProcessStatusCodeStr ITSK00144_2ProcessStatusCodeStrW
#define ITSK00144_2ProcessStatusCodeFromStr ITSK00144_2ProcessStatusCodeFromStrW
#else // UNICODE
#define ITSK00144_2ProcessStatusCodeStr ITSK00144_2ProcessStatusCodeStrA
#define ITSK00144_2ProcessStatusCodeFromStr ITSK00144_2ProcessStatusCodeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ITSK00144_2ProcessStatusCodeStr ITSK00144_2ProcessStatusCodeStrA
#define ITSK00144_2ProcessStatusCodeFromStr ITSK00144_2ProcessStatusCodeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2ProcessStatusCode *ITSK00144_2ProcessStatusCode_new(ITSK00144_2ProcessStatusCode *src, Dz1Error *err);
static __inline__ ITSK00144_2ProcessStatusCode *ITSK00144_2ProcessStatusCode_gen(Dz1Error *err) { ITSK00144_2ProcessStatusCode v = ITSK00144_2ProcessStatusCode_max; return ITSK00144_2ProcessStatusCode_new(&v, err); }
#define ITSK00144_2ProcessStatusCode_clone             ITSK00144_2ProcessStatusCode_new
static __inline__ void ITSK00144_2ProcessStatusCode_del(ITSK00144_2ProcessStatusCode *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ITSK00144_2ProcessStatusCode_delAndSetNull(void *ptr)
{
	ITSK00144_2ProcessStatusCode **p = (ITSK00144_2ProcessStatusCode **)ptr;
	if (p != NULL) { ITSK00144_2ProcessStatusCode_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ProcessStatusCode_dump(ITSK00144_2ProcessStatusCode *v, int tab);
// ITSK00144_2ProcessStatusCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2NotifyStateContext
typedef struct ITSK00144_2NotifyStateContext
{
	Dz1Str		testName;
	s64_t		time;
	Dz1Str		state;
} ITSK00144_2NotifyStateContext;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2NotifyStateContext *ITSK00144_2NotifyStateContext_new(Dz1Str testName, 
																						 s64_t time, 
																						 Dz1Str state, Dz1Error *err);
static __inline__ ITSK00144_2NotifyStateContext *ITSK00144_2NotifyStateContext_gen(Dz1Error *err) { return ITSK00144_2NotifyStateContext_new(NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ITSK00144_2NotifyStateContext_copy(ITSK00144_2NotifyStateContext *dst, ITSK00144_2NotifyStateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2NotifyStateContext *ITSK00144_2NotifyStateContext_clone(ITSK00144_2NotifyStateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2NotifyStateContext_purge(ITSK00144_2NotifyStateContext *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2NotifyStateContext_del(ITSK00144_2NotifyStateContext *p);
static __inline__ void ITSK00144_2NotifyStateContext_delAndSetNull(void *ptr)
{
	ITSK00144_2NotifyStateContext **p = (ITSK00144_2NotifyStateContext **)ptr;
	if (p) { ITSK00144_2NotifyStateContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2NotifyStateContext_dump(ITSK00144_2NotifyStateContext *p, int tab);
// ITSK00144_2NotifyStateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2NotifyInfoContext
typedef struct ITSK00144_2NotifyInfoContext
{
	Dz1Str			 testName;
	s64_t			 time;
	Dz1Str			 sender;
	Dz1Str			 log;
	Dz1Binary		*data;
	Dz1Str			 dataType;
} ITSK00144_2NotifyInfoContext;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2NotifyInfoContext *ITSK00144_2NotifyInfoContext_new(Dz1Str testName, 
																					   s64_t time, 
																					   Dz1Str sender, 
																					   Dz1Str log, 
																					   Dz1Binary *data, 
																					   Dz1Str dataType, Dz1Error *err);
static __inline__ ITSK00144_2NotifyInfoContext *ITSK00144_2NotifyInfoContext_gen(Dz1Error *err) { return ITSK00144_2NotifyInfoContext_new(NULL, 0, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ITSK00144_2NotifyInfoContext_copy(ITSK00144_2NotifyInfoContext *dst, ITSK00144_2NotifyInfoContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2NotifyInfoContext *ITSK00144_2NotifyInfoContext_clone(ITSK00144_2NotifyInfoContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2NotifyInfoContext_purge(ITSK00144_2NotifyInfoContext *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2NotifyInfoContext_del(ITSK00144_2NotifyInfoContext *p);
static __inline__ void ITSK00144_2NotifyInfoContext_delAndSetNull(void *ptr)
{
	ITSK00144_2NotifyInfoContext **p = (ITSK00144_2NotifyInfoContext **)ptr;
	if (p) { ITSK00144_2NotifyInfoContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2NotifyInfoContext_dump(ITSK00144_2NotifyInfoContext *p, int tab);
// ITSK00144_2NotifyInfoContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2NotifyErrorContext
typedef struct ITSK00144_2NotifyErrorContext
{
	Dz1Str							 testName;
	s64_t							 time;
	ITSK00144_2ProcessStatusCode	 code;
	Dz1Str							 desc;
	Dz1Str							 log;
	Dz1Binary						*data;
} ITSK00144_2NotifyErrorContext;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2NotifyErrorContext *ITSK00144_2NotifyErrorContext_new(Dz1Str testName, 
																						 s64_t time, 
																						 ITSK00144_2ProcessStatusCode code, 
																						 Dz1Str desc, 
																						 Dz1Str log, 
																						 Dz1Binary *data, Dz1Error *err);
static __inline__ ITSK00144_2NotifyErrorContext *ITSK00144_2NotifyErrorContext_gen(Dz1Error *err) { return ITSK00144_2NotifyErrorContext_new(NULL, 0, ITSK00144_2ProcessStatusCode_max, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ITSK00144_2NotifyErrorContext_copy(ITSK00144_2NotifyErrorContext *dst, ITSK00144_2NotifyErrorContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2NotifyErrorContext *ITSK00144_2NotifyErrorContext_clone(ITSK00144_2NotifyErrorContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2NotifyErrorContext_purge(ITSK00144_2NotifyErrorContext *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2NotifyErrorContext_del(ITSK00144_2NotifyErrorContext *p);
static __inline__ void ITSK00144_2NotifyErrorContext_delAndSetNull(void *ptr)
{
	ITSK00144_2NotifyErrorContext **p = (ITSK00144_2NotifyErrorContext **)ptr;
	if (p) { ITSK00144_2NotifyErrorContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2NotifyErrorContext_dump(ITSK00144_2NotifyErrorContext *p, int tab);
// ITSK00144_2NotifyErrorContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2NotifyStateArg
typedef struct ITSK00144_2NotifyStateArg
{
	u32_t								 testIdx;
	ITSK00144_2NotifyStateContext		*context;
} ITSK00144_2NotifyStateArg;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2NotifyStateArg *ITSK00144_2NotifyStateArg_new(u32_t testIdx, 
																				 ITSK00144_2NotifyStateContext *context, Dz1Error *err);
static __inline__ ITSK00144_2NotifyStateArg *ITSK00144_2NotifyStateArg_gen(Dz1Error *err) { return ITSK00144_2NotifyStateArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ITSK00144_2NotifyStateArg_copy(ITSK00144_2NotifyStateArg *dst, ITSK00144_2NotifyStateArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2NotifyStateArg *ITSK00144_2NotifyStateArg_clone(ITSK00144_2NotifyStateArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2NotifyStateArg_purge(ITSK00144_2NotifyStateArg *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2NotifyStateArg_del(ITSK00144_2NotifyStateArg *p);
static __inline__ void ITSK00144_2NotifyStateArg_delAndSetNull(void *ptr)
{
	ITSK00144_2NotifyStateArg **p = (ITSK00144_2NotifyStateArg **)ptr;
	if (p) { ITSK00144_2NotifyStateArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2NotifyStateArg_dump(ITSK00144_2NotifyStateArg *p, int tab);
// ITSK00144_2NotifyStateArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2NotifyInfoArg
typedef struct ITSK00144_2NotifyInfoArg
{
	u32_t							 testIdx;
	ITSK00144_2NotifyInfoContext	*context;
} ITSK00144_2NotifyInfoArg;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2NotifyInfoArg *ITSK00144_2NotifyInfoArg_new(u32_t testIdx, 
																			   ITSK00144_2NotifyInfoContext *context, Dz1Error *err);
static __inline__ ITSK00144_2NotifyInfoArg *ITSK00144_2NotifyInfoArg_gen(Dz1Error *err) { return ITSK00144_2NotifyInfoArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ITSK00144_2NotifyInfoArg_copy(ITSK00144_2NotifyInfoArg *dst, ITSK00144_2NotifyInfoArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2NotifyInfoArg *ITSK00144_2NotifyInfoArg_clone(ITSK00144_2NotifyInfoArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2NotifyInfoArg_purge(ITSK00144_2NotifyInfoArg *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2NotifyInfoArg_del(ITSK00144_2NotifyInfoArg *p);
static __inline__ void ITSK00144_2NotifyInfoArg_delAndSetNull(void *ptr)
{
	ITSK00144_2NotifyInfoArg **p = (ITSK00144_2NotifyInfoArg **)ptr;
	if (p) { ITSK00144_2NotifyInfoArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2NotifyInfoArg_dump(ITSK00144_2NotifyInfoArg *p, int tab);
// ITSK00144_2NotifyInfoArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2NotifyErrorArg
typedef struct ITSK00144_2NotifyErrorArg
{
	u32_t								 testIdx;
	ITSK00144_2NotifyErrorContext		*context;
} ITSK00144_2NotifyErrorArg;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2NotifyErrorArg *ITSK00144_2NotifyErrorArg_new(u32_t testIdx, 
																				 ITSK00144_2NotifyErrorContext *context, Dz1Error *err);
static __inline__ ITSK00144_2NotifyErrorArg *ITSK00144_2NotifyErrorArg_gen(Dz1Error *err) { return ITSK00144_2NotifyErrorArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ITSK00144_2NotifyErrorArg_copy(ITSK00144_2NotifyErrorArg *dst, ITSK00144_2NotifyErrorArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2NotifyErrorArg *ITSK00144_2NotifyErrorArg_clone(ITSK00144_2NotifyErrorArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2NotifyErrorArg_purge(ITSK00144_2NotifyErrorArg *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2NotifyErrorArg_del(ITSK00144_2NotifyErrorArg *p);
static __inline__ void ITSK00144_2NotifyErrorArg_delAndSetNull(void *ptr)
{
	ITSK00144_2NotifyErrorArg **p = (ITSK00144_2NotifyErrorArg **)ptr;
	if (p) { ITSK00144_2NotifyErrorArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2NotifyErrorArg_dump(ITSK00144_2NotifyErrorArg *p, int tab);
// ITSK00144_2NotifyErrorArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2NotifyContextPresent
typedef enum ITSK00144_2NotifyContextPresent
{
	ITSK00144_2NotifyContextPresent_state,
	ITSK00144_2NotifyContextPresent_info,
	ITSK00144_2NotifyContextPresent_error,
	ITSK00144_2NotifyContextPresent_max
} ITSK00144_2NotifyContextPresent;

DZ1_CPPLINK str_t ITSK00144_2NotifyContextPresentStrA(ITSK00144_2NotifyContextPresent v);
DZ1_CPPLINK ITSK00144_2NotifyContextPresent ITSK00144_2NotifyContextPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ITSK00144_2NotifyContextPresentStrW(ITSK00144_2NotifyContextPresent v);
DZ1_CPPLINK ITSK00144_2NotifyContextPresent ITSK00144_2NotifyContextPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define ITSK00144_2NotifyContextPresentStr ITSK00144_2NotifyContextPresentStrW
#define ITSK00144_2NotifyContextPresentFromStr ITSK00144_2NotifyContextPresentFromStrW
#else // UNICODE
#define ITSK00144_2NotifyContextPresentStr ITSK00144_2NotifyContextPresentStrA
#define ITSK00144_2NotifyContextPresentFromStr ITSK00144_2NotifyContextPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ITSK00144_2NotifyContextPresentStr ITSK00144_2NotifyContextPresentStrA
#define ITSK00144_2NotifyContextPresentFromStr ITSK00144_2NotifyContextPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2NotifyContextPresent *ITSK00144_2NotifyContextPresent_new(ITSK00144_2NotifyContextPresent *src, Dz1Error *err);
static __inline__ ITSK00144_2NotifyContextPresent *ITSK00144_2NotifyContextPresent_gen(Dz1Error *err) { ITSK00144_2NotifyContextPresent v = ITSK00144_2NotifyContextPresent_max; return ITSK00144_2NotifyContextPresent_new(&v, err); }
#define ITSK00144_2NotifyContextPresent_clone             ITSK00144_2NotifyContextPresent_new
static __inline__ void ITSK00144_2NotifyContextPresent_del(ITSK00144_2NotifyContextPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ITSK00144_2NotifyContextPresent_delAndSetNull(void *ptr)
{
	ITSK00144_2NotifyContextPresent **p = (ITSK00144_2NotifyContextPresent **)ptr;
	if (p != NULL) { ITSK00144_2NotifyContextPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2NotifyContextPresent_dump(ITSK00144_2NotifyContextPresent *v, int tab);
// ITSK00144_2NotifyContextPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2NotifyContext
typedef struct ITSK00144_2NotifyContext
{
	ITSK00144_2NotifyContextPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		ITSK00144_2NotifyStateContext		*state;
		ITSK00144_2NotifyInfoContext		*info;
		ITSK00144_2NotifyErrorContext		*error;
	} x;
} ITSK00144_2NotifyContext;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2NotifyContext *ITSK00144_2NotifyContext_new(ITSK00144_2NotifyContextPresent present, void *ptr, Dz1Error *err);
static __inline__ ITSK00144_2NotifyContext *ITSK00144_2NotifyContext_gen(Dz1Error *err) { return ITSK00144_2NotifyContext_new(ITSK00144_2NotifyContextPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  ITSK00144_2NotifyContext_copy(ITSK00144_2NotifyContext *dst, ITSK00144_2NotifyContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2NotifyContext *ITSK00144_2NotifyContext_clone(ITSK00144_2NotifyContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2NotifyContext_purge(ITSK00144_2NotifyContext *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2NotifyContext_del(ITSK00144_2NotifyContext *p);
static __inline__ void ITSK00144_2NotifyContext_delAndSetNull(void *ptr)
{
	ITSK00144_2NotifyContext **p = (ITSK00144_2NotifyContext **)ptr;
	if (p != NULL) { ITSK00144_2NotifyContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2NotifyContext_dump(ITSK00144_2NotifyContext *p, int tab);
// ITSK00144_2NotifyContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ValidateContext
typedef struct ITSK00144_2ValidateContext
{
	Dz1Str							 testName;
	s64_t							 time;
	Dz1Binary						*raw;
	Dz1Binary						*data;
	ITSK00144_2ProcessStatusCode	 code;
	Dz1Str							 desc;
} ITSK00144_2ValidateContext;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2ValidateContext *ITSK00144_2ValidateContext_new(Dz1Str testName, 
																				   s64_t time, 
																				   Dz1Binary *raw, 
																				   Dz1Binary *data, 
																				   ITSK00144_2ProcessStatusCode code, 
																				   Dz1Str desc, Dz1Error *err);
static __inline__ ITSK00144_2ValidateContext *ITSK00144_2ValidateContext_gen(Dz1Error *err) { return ITSK00144_2ValidateContext_new(NULL, 0, NULL, NULL, ITSK00144_2ProcessStatusCode_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ITSK00144_2ValidateContext_copy(ITSK00144_2ValidateContext *dst, ITSK00144_2ValidateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2ValidateContext *ITSK00144_2ValidateContext_clone(ITSK00144_2ValidateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ValidateContext_purge(ITSK00144_2ValidateContext *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ValidateContext_del(ITSK00144_2ValidateContext *p);
static __inline__ void ITSK00144_2ValidateContext_delAndSetNull(void *ptr)
{
	ITSK00144_2ValidateContext **p = (ITSK00144_2ValidateContext **)ptr;
	if (p) { ITSK00144_2ValidateContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ValidateContext_dump(ITSK00144_2ValidateContext *p, int tab);
// ITSK00144_2ValidateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ValidateContextArg
typedef struct ITSK00144_2ValidateContextArg
{
	u32_t							 testIdx;
	ITSK00144_2ValidateContext		*context;
} ITSK00144_2ValidateContextArg;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2ValidateContextArg *ITSK00144_2ValidateContextArg_new(u32_t testIdx, 
																						 ITSK00144_2ValidateContext *context, Dz1Error *err);
static __inline__ ITSK00144_2ValidateContextArg *ITSK00144_2ValidateContextArg_gen(Dz1Error *err) { return ITSK00144_2ValidateContextArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ITSK00144_2ValidateContextArg_copy(ITSK00144_2ValidateContextArg *dst, ITSK00144_2ValidateContextArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2ValidateContextArg *ITSK00144_2ValidateContextArg_clone(ITSK00144_2ValidateContextArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ValidateContextArg_purge(ITSK00144_2ValidateContextArg *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ValidateContextArg_del(ITSK00144_2ValidateContextArg *p);
static __inline__ void ITSK00144_2ValidateContextArg_delAndSetNull(void *ptr)
{
	ITSK00144_2ValidateContextArg **p = (ITSK00144_2ValidateContextArg **)ptr;
	if (p) { ITSK00144_2ValidateContextArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2ValidateContextArg_dump(ITSK00144_2ValidateContextArg *p, int tab);
// ITSK00144_2ValidateContextArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2TestConfiguration_ServerRole
typedef struct ITSK00144_2TestConfiguration_ServerRole
{
	u64_t		local_port;
	u32_t		serial_no;
	bool_t		test_rsp_link_unit_status;
	bool_t		test_rsp_status;
	bool_t		test_rsp_list;
	bool_t		test_rsp_update_list;
	bool_t		test_rsp_reset;
	bool_t		test_session_maintain;
	s64_t		hb_duration;
} ITSK00144_2TestConfiguration_ServerRole;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2TestConfiguration_ServerRole *ITSK00144_2TestConfiguration_ServerRole_new(u64_t local_port, 
																											 u32_t serial_no, 
																											 bool_t test_rsp_link_unit_status, 
																											 bool_t test_rsp_status, 
																											 bool_t test_rsp_list, 
																											 bool_t test_rsp_update_list, 
																											 bool_t test_rsp_reset, 
																											 bool_t test_session_maintain, 
																											 s64_t hb_duration, Dz1Error *err);
static __inline__ ITSK00144_2TestConfiguration_ServerRole *ITSK00144_2TestConfiguration_ServerRole_gen(Dz1Error *err) { return ITSK00144_2TestConfiguration_ServerRole_new(0, 0, 0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ITSK00144_2TestConfiguration_ServerRole_copy(ITSK00144_2TestConfiguration_ServerRole *dst, ITSK00144_2TestConfiguration_ServerRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2TestConfiguration_ServerRole *ITSK00144_2TestConfiguration_ServerRole_clone(ITSK00144_2TestConfiguration_ServerRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2TestConfiguration_ServerRole_purge(ITSK00144_2TestConfiguration_ServerRole *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2TestConfiguration_ServerRole_del(ITSK00144_2TestConfiguration_ServerRole *p);
static __inline__ void ITSK00144_2TestConfiguration_ServerRole_delAndSetNull(void *ptr)
{
	ITSK00144_2TestConfiguration_ServerRole **p = (ITSK00144_2TestConfiguration_ServerRole **)ptr;
	if (p) { ITSK00144_2TestConfiguration_ServerRole_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2TestConfiguration_ServerRole_dump(ITSK00144_2TestConfiguration_ServerRole *p, int tab);
// ITSK00144_2TestConfiguration_ServerRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2TestConfiguration_LinkUnitRole
typedef struct ITSK00144_2TestConfiguration_LinkUnitRole
{
	Dz1Str		peer_ip;
	u64_t		peer_port;
	u32_t		serial_no;
	bool_t		test_req_link_unit_status;
	bool_t		test_req_status;
	bool_t		test_req_list;
	bool_t		test_req_update_list;
	bool_t		test_req_reset;
	bool_t		test_session_maintain;
	s64_t		hb_duration;
	bool_t		test_tim;
	bool_t		test_map;
} ITSK00144_2TestConfiguration_LinkUnitRole;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2TestConfiguration_LinkUnitRole *ITSK00144_2TestConfiguration_LinkUnitRole_new(Dz1Str peer_ip, 
																												 u64_t peer_port, 
																												 u32_t serial_no, 
																												 bool_t test_req_link_unit_status, 
																												 bool_t test_req_status, 
																												 bool_t test_req_list, 
																												 bool_t test_req_update_list, 
																												 bool_t test_req_reset, 
																												 bool_t test_session_maintain, 
																												 s64_t hb_duration, 
																												 bool_t test_tim, 
																												 bool_t test_map, Dz1Error *err);
static __inline__ ITSK00144_2TestConfiguration_LinkUnitRole *ITSK00144_2TestConfiguration_LinkUnitRole_gen(Dz1Error *err) { return ITSK00144_2TestConfiguration_LinkUnitRole_new(NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ITSK00144_2TestConfiguration_LinkUnitRole_copy(ITSK00144_2TestConfiguration_LinkUnitRole *dst, ITSK00144_2TestConfiguration_LinkUnitRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2TestConfiguration_LinkUnitRole *ITSK00144_2TestConfiguration_LinkUnitRole_clone(ITSK00144_2TestConfiguration_LinkUnitRole *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2TestConfiguration_LinkUnitRole_purge(ITSK00144_2TestConfiguration_LinkUnitRole *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2TestConfiguration_LinkUnitRole_del(ITSK00144_2TestConfiguration_LinkUnitRole *p);
static __inline__ void ITSK00144_2TestConfiguration_LinkUnitRole_delAndSetNull(void *ptr)
{
	ITSK00144_2TestConfiguration_LinkUnitRole **p = (ITSK00144_2TestConfiguration_LinkUnitRole **)ptr;
	if (p) { ITSK00144_2TestConfiguration_LinkUnitRole_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2TestConfiguration_LinkUnitRole_dump(ITSK00144_2TestConfiguration_LinkUnitRole *p, int tab);
// ITSK00144_2TestConfiguration_LinkUnitRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2TestConfigurationPresent
typedef enum ITSK00144_2TestConfigurationPresent
{
	ITSK00144_2TestConfigurationPresent_serverRole,
	ITSK00144_2TestConfigurationPresent_linkUnitRole,
	ITSK00144_2TestConfigurationPresent_max
} ITSK00144_2TestConfigurationPresent;

DZ1_CPPLINK str_t ITSK00144_2TestConfigurationPresentStrA(ITSK00144_2TestConfigurationPresent v);
DZ1_CPPLINK ITSK00144_2TestConfigurationPresent ITSK00144_2TestConfigurationPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ITSK00144_2TestConfigurationPresentStrW(ITSK00144_2TestConfigurationPresent v);
DZ1_CPPLINK ITSK00144_2TestConfigurationPresent ITSK00144_2TestConfigurationPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define ITSK00144_2TestConfigurationPresentStr ITSK00144_2TestConfigurationPresentStrW
#define ITSK00144_2TestConfigurationPresentFromStr ITSK00144_2TestConfigurationPresentFromStrW
#else // UNICODE
#define ITSK00144_2TestConfigurationPresentStr ITSK00144_2TestConfigurationPresentStrA
#define ITSK00144_2TestConfigurationPresentFromStr ITSK00144_2TestConfigurationPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ITSK00144_2TestConfigurationPresentStr ITSK00144_2TestConfigurationPresentStrA
#define ITSK00144_2TestConfigurationPresentFromStr ITSK00144_2TestConfigurationPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2TestConfigurationPresent *ITSK00144_2TestConfigurationPresent_new(ITSK00144_2TestConfigurationPresent *src, Dz1Error *err);
static __inline__ ITSK00144_2TestConfigurationPresent *ITSK00144_2TestConfigurationPresent_gen(Dz1Error *err) { ITSK00144_2TestConfigurationPresent v = ITSK00144_2TestConfigurationPresent_max; return ITSK00144_2TestConfigurationPresent_new(&v, err); }
#define ITSK00144_2TestConfigurationPresent_clone             ITSK00144_2TestConfigurationPresent_new
static __inline__ void ITSK00144_2TestConfigurationPresent_del(ITSK00144_2TestConfigurationPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ITSK00144_2TestConfigurationPresent_delAndSetNull(void *ptr)
{
	ITSK00144_2TestConfigurationPresent **p = (ITSK00144_2TestConfigurationPresent **)ptr;
	if (p != NULL) { ITSK00144_2TestConfigurationPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2TestConfigurationPresent_dump(ITSK00144_2TestConfigurationPresent *v, int tab);
// ITSK00144_2TestConfigurationPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2TestConfiguration
typedef struct ITSK00144_2TestConfiguration
{
	ITSK00144_2TestConfigurationPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		ITSK00144_2TestConfiguration_ServerRole			*serverRole;
		ITSK00144_2TestConfiguration_LinkUnitRole		*linkUnitRole;
	} x;
} ITSK00144_2TestConfiguration;

DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2TestConfiguration *ITSK00144_2TestConfiguration_new(ITSK00144_2TestConfigurationPresent present, void *ptr, Dz1Error *err);
static __inline__ ITSK00144_2TestConfiguration *ITSK00144_2TestConfiguration_gen(Dz1Error *err) { return ITSK00144_2TestConfiguration_new(ITSK00144_2TestConfigurationPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  ITSK00144_2TestConfiguration_copy(ITSK00144_2TestConfiguration *dst, ITSK00144_2TestConfiguration *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ITSK00144_2TestConfiguration *ITSK00144_2TestConfiguration_clone(ITSK00144_2TestConfiguration *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2TestConfiguration_purge(ITSK00144_2TestConfiguration *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2TestConfiguration_del(ITSK00144_2TestConfiguration *p);
static __inline__ void ITSK00144_2TestConfiguration_delAndSetNull(void *ptr)
{
	ITSK00144_2TestConfiguration **p = (ITSK00144_2TestConfiguration **)ptr;
	if (p != NULL) { ITSK00144_2TestConfiguration_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ITSK00144_2TestConfiguration_dump(ITSK00144_2TestConfiguration *p, int tab);
// ITSK00144_2TestConfiguration
////////////////////////////////////////////////////////////////////////////////

#endif

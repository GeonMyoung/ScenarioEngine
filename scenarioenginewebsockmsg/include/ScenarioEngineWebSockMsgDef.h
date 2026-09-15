#ifndef _DZ1_TDC_SCENARIO_ENGINE_WEB_SOCK_MSG_DEF_H_
#define _DZ1_TDC_SCENARIO_ENGINE_WEB_SOCK_MSG_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineWebSocketStatusCode
typedef enum ScenarioEngineWebSocketStatusCode
{
	ScenarioEngineWebSocketStatusCode_Informational = 100,
	ScenarioEngineWebSocketStatusCode_OK = 200,
	ScenarioEngineWebSocketStatusCode_Redirection = 300,
	ScenarioEngineWebSocketStatusCode_ClientError = 400,
	ScenarioEngineWebSocketStatusCode_ServerError = 500,
	ScenarioEngineWebSocketStatusCode_AgentError = 600,
	ScenarioEngineWebSocketStatusCode_max
} ScenarioEngineWebSocketStatusCode;

DZ1_CPPLINK str_t ScenarioEngineWebSocketStatusCodeStrA(ScenarioEngineWebSocketStatusCode v);
DZ1_CPPLINK ScenarioEngineWebSocketStatusCode ScenarioEngineWebSocketStatusCodeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ScenarioEngineWebSocketStatusCodeStrW(ScenarioEngineWebSocketStatusCode v);
DZ1_CPPLINK ScenarioEngineWebSocketStatusCode ScenarioEngineWebSocketStatusCodeFromStrW(wstr_t str);
#ifdef UNICODE
#define ScenarioEngineWebSocketStatusCodeStr ScenarioEngineWebSocketStatusCodeStrW
#define ScenarioEngineWebSocketStatusCodeFromStr ScenarioEngineWebSocketStatusCodeFromStrW
#else // UNICODE
#define ScenarioEngineWebSocketStatusCodeStr ScenarioEngineWebSocketStatusCodeStrA
#define ScenarioEngineWebSocketStatusCodeFromStr ScenarioEngineWebSocketStatusCodeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ScenarioEngineWebSocketStatusCodeStr ScenarioEngineWebSocketStatusCodeStrA
#define ScenarioEngineWebSocketStatusCodeFromStr ScenarioEngineWebSocketStatusCodeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineWebSocketStatusCode *ScenarioEngineWebSocketStatusCode_new(ScenarioEngineWebSocketStatusCode *src, Dz1Error *err);
static __inline__ ScenarioEngineWebSocketStatusCode *ScenarioEngineWebSocketStatusCode_gen(Dz1Error *err) { ScenarioEngineWebSocketStatusCode v = ScenarioEngineWebSocketStatusCode_max; return ScenarioEngineWebSocketStatusCode_new(&v, err); }
static __inline__ void ScenarioEngineWebSocketStatusCode_del(ScenarioEngineWebSocketStatusCode *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ScenarioEngineWebSocketStatusCode_delAndSetNull(void *ptr)
{
	ScenarioEngineWebSocketStatusCode **p = (ScenarioEngineWebSocketStatusCode **)ptr;
	if (p != NULL) { ScenarioEngineWebSocketStatusCode_del(*p); *p = NULL; }
}
// ScenarioEngineWebSocketStatusCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineProcessStatusCode
typedef enum ScenarioEngineProcessStatusCode
{
	ScenarioEngineProcessStatusCode_OK = 0,
	ScenarioEngineProcessStatusCode_FAILURE = 1,
	ScenarioEngineProcessStatusCode_AGENT_SYSTEM_ERROR = 11,
	ScenarioEngineProcessStatusCode_SERVER_DISCONNECTED = 12,
	ScenarioEngineProcessStatusCode_TEST_CONFIGURATION_ERROR = 13,
	ScenarioEngineProcessStatusCode_CONNECTION_FAIL = 100,
	ScenarioEngineProcessStatusCode_DISCONNECTED = 101,
	ScenarioEngineProcessStatusCode_TIMEOUT = 102,
	ScenarioEngineProcessStatusCode_OUT_OF_RANGE = 201,
	ScenarioEngineProcessStatusCode_INVALID_PROCESS,
	ScenarioEngineProcessStatusCode_INVALID_IDENTIFIER,
	ScenarioEngineProcessStatusCode_SESSION_DUPLICATE,
	ScenarioEngineProcessStatusCode_LOGIN_AUTH_ERROR,
	ScenarioEngineProcessStatusCode_DECODE_FAIL = 210,
	ScenarioEngineProcessStatusCode_INVALID_ENCODING_RULE = 211,
	ScenarioEngineProcessStatusCode_INVALID_OID = 212,
	ScenarioEngineProcessStatusCode_INVALID_DSRC_MSG_ID = 213,
	ScenarioEngineProcessStatusCode_JSON_PARSE_ERROR = 221,
	ScenarioEngineProcessStatusCode_PROTOBUF_DESERAILIZE_ERROR = 231,
	ScenarioEngineProcessStatusCode_INVALID_TOPIC = 241,
	ScenarioEngineProcessStatusCode_INVALID_REQUEST = 251,
	ScenarioEngineProcessStatusCode_UNKNOWN = 300,
	ScenarioEngineProcessStatusCode_max
} ScenarioEngineProcessStatusCode;

DZ1_CPPLINK str_t ScenarioEngineProcessStatusCodeStrA(ScenarioEngineProcessStatusCode v);
DZ1_CPPLINK ScenarioEngineProcessStatusCode ScenarioEngineProcessStatusCodeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ScenarioEngineProcessStatusCodeStrW(ScenarioEngineProcessStatusCode v);
DZ1_CPPLINK ScenarioEngineProcessStatusCode ScenarioEngineProcessStatusCodeFromStrW(wstr_t str);
#ifdef UNICODE
#define ScenarioEngineProcessStatusCodeStr ScenarioEngineProcessStatusCodeStrW
#define ScenarioEngineProcessStatusCodeFromStr ScenarioEngineProcessStatusCodeFromStrW
#else // UNICODE
#define ScenarioEngineProcessStatusCodeStr ScenarioEngineProcessStatusCodeStrA
#define ScenarioEngineProcessStatusCodeFromStr ScenarioEngineProcessStatusCodeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ScenarioEngineProcessStatusCodeStr ScenarioEngineProcessStatusCodeStrA
#define ScenarioEngineProcessStatusCodeFromStr ScenarioEngineProcessStatusCodeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineProcessStatusCode *ScenarioEngineProcessStatusCode_new(ScenarioEngineProcessStatusCode *src, Dz1Error *err);
static __inline__ ScenarioEngineProcessStatusCode *ScenarioEngineProcessStatusCode_gen(Dz1Error *err) { ScenarioEngineProcessStatusCode v = ScenarioEngineProcessStatusCode_max; return ScenarioEngineProcessStatusCode_new(&v, err); }
#define ScenarioEngineProcessStatusCode_clone             ScenarioEngineProcessStatusCode_new
static __inline__ void ScenarioEngineProcessStatusCode_del(ScenarioEngineProcessStatusCode *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ScenarioEngineProcessStatusCode_delAndSetNull(void *ptr)
{
	ScenarioEngineProcessStatusCode **p = (ScenarioEngineProcessStatusCode **)ptr;
	if (p != NULL) { ScenarioEngineProcessStatusCode_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineProcessStatusCode_dump(ScenarioEngineProcessStatusCode *v, int tab);
// ScenarioEngineProcessStatusCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageDefault
typedef struct ScenarioEngineRequestMessageDefault
{
	Dz1Str		method;
	u32_t		seq;
} ScenarioEngineRequestMessageDefault;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineRequestMessageDefault *ScenarioEngineRequestMessageDefault_new(Dz1Str method, 
																									 u32_t seq, Dz1Error *err);
static __inline__ ScenarioEngineRequestMessageDefault *ScenarioEngineRequestMessageDefault_gen(Dz1Error *err) { return ScenarioEngineRequestMessageDefault_new(NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ScenarioEngineRequestMessageDefault_copy(ScenarioEngineRequestMessageDefault *dst, ScenarioEngineRequestMessageDefault *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineRequestMessageDefault *ScenarioEngineRequestMessageDefault_clone(ScenarioEngineRequestMessageDefault *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageDefault_purge(ScenarioEngineRequestMessageDefault *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageDefault_del(ScenarioEngineRequestMessageDefault *p);
static __inline__ void ScenarioEngineRequestMessageDefault_delAndSetNull(void *ptr)
{
	ScenarioEngineRequestMessageDefault **p = (ScenarioEngineRequestMessageDefault **)ptr;
	if (p) { ScenarioEngineRequestMessageDefault_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageDefault_dump(ScenarioEngineRequestMessageDefault *p, int tab);
// ScenarioEngineRequestMessageDefault
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageDescribe
typedef struct ScenarioEngineRequestMessageDescribe
{
	Dz1Str		method;
	u32_t		seq;
	Dz1Str		type;
} ScenarioEngineRequestMessageDescribe;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineRequestMessageDescribe *ScenarioEngineRequestMessageDescribe_new(Dz1Str method, 
																									   u32_t seq, 
																									   Dz1Str type, Dz1Error *err);
static __inline__ ScenarioEngineRequestMessageDescribe *ScenarioEngineRequestMessageDescribe_gen(Dz1Error *err) { return ScenarioEngineRequestMessageDescribe_new(NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ScenarioEngineRequestMessageDescribe_copy(ScenarioEngineRequestMessageDescribe *dst, ScenarioEngineRequestMessageDescribe *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineRequestMessageDescribe *ScenarioEngineRequestMessageDescribe_clone(ScenarioEngineRequestMessageDescribe *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageDescribe_purge(ScenarioEngineRequestMessageDescribe *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageDescribe_del(ScenarioEngineRequestMessageDescribe *p);
static __inline__ void ScenarioEngineRequestMessageDescribe_delAndSetNull(void *ptr)
{
	ScenarioEngineRequestMessageDescribe **p = (ScenarioEngineRequestMessageDescribe **)ptr;
	if (p) { ScenarioEngineRequestMessageDescribe_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageDescribe_dump(ScenarioEngineRequestMessageDescribe *p, int tab);
// ScenarioEngineRequestMessageDescribe
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineInitializeContext
typedef struct ScenarioEngineInitializeContext
{
	Dz1Str		category;
	Dz1Str		testScenario;
} ScenarioEngineInitializeContext;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineInitializeContext *ScenarioEngineInitializeContext_new(Dz1Str category, 
																							 Dz1Str testScenario, Dz1Error *err);
static __inline__ ScenarioEngineInitializeContext *ScenarioEngineInitializeContext_gen(Dz1Error *err) { return ScenarioEngineInitializeContext_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ScenarioEngineInitializeContext_copy(ScenarioEngineInitializeContext *dst, ScenarioEngineInitializeContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineInitializeContext *ScenarioEngineInitializeContext_clone(ScenarioEngineInitializeContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineInitializeContext_purge(ScenarioEngineInitializeContext *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineInitializeContext_del(ScenarioEngineInitializeContext *p);
static __inline__ void ScenarioEngineInitializeContext_delAndSetNull(void *ptr)
{
	ScenarioEngineInitializeContext **p = (ScenarioEngineInitializeContext **)ptr;
	if (p) { ScenarioEngineInitializeContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineInitializeContext_dump(ScenarioEngineInitializeContext *p, int tab);
// ScenarioEngineInitializeContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageInitialize
typedef struct ScenarioEngineRequestMessageInitialize
{
	Dz1Str			 method;
	u32_t			 seq;
	Dz1Binary		*testScenario;
} ScenarioEngineRequestMessageInitialize;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineRequestMessageInitialize *ScenarioEngineRequestMessageInitialize_new(Dz1Str method, 
																										   u32_t seq, 
																										   Dz1Binary *testScenario, Dz1Error *err);
static __inline__ ScenarioEngineRequestMessageInitialize *ScenarioEngineRequestMessageInitialize_gen(Dz1Error *err) { return ScenarioEngineRequestMessageInitialize_new(NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ScenarioEngineRequestMessageInitialize_copy(ScenarioEngineRequestMessageInitialize *dst, ScenarioEngineRequestMessageInitialize *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineRequestMessageInitialize *ScenarioEngineRequestMessageInitialize_clone(ScenarioEngineRequestMessageInitialize *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageInitialize_purge(ScenarioEngineRequestMessageInitialize *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageInitialize_del(ScenarioEngineRequestMessageInitialize *p);
static __inline__ void ScenarioEngineRequestMessageInitialize_delAndSetNull(void *ptr)
{
	ScenarioEngineRequestMessageInitialize **p = (ScenarioEngineRequestMessageInitialize **)ptr;
	if (p) { ScenarioEngineRequestMessageInitialize_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageInitialize_dump(ScenarioEngineRequestMessageInitialize *p, int tab);
// ScenarioEngineRequestMessageInitialize
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageUIConfigure
typedef struct ScenarioEngineRequestMessageUIConfigure
{
	Dz1Str			 method;
	u32_t			 seq;
	Dz1Binary		*conf;
} ScenarioEngineRequestMessageUIConfigure;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineRequestMessageUIConfigure *ScenarioEngineRequestMessageUIConfigure_new(Dz1Str method, 
																											 u32_t seq, 
																											 Dz1Binary *conf, Dz1Error *err);
static __inline__ ScenarioEngineRequestMessageUIConfigure *ScenarioEngineRequestMessageUIConfigure_gen(Dz1Error *err) { return ScenarioEngineRequestMessageUIConfigure_new(NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ScenarioEngineRequestMessageUIConfigure_copy(ScenarioEngineRequestMessageUIConfigure *dst, ScenarioEngineRequestMessageUIConfigure *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineRequestMessageUIConfigure *ScenarioEngineRequestMessageUIConfigure_clone(ScenarioEngineRequestMessageUIConfigure *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageUIConfigure_purge(ScenarioEngineRequestMessageUIConfigure *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageUIConfigure_del(ScenarioEngineRequestMessageUIConfigure *p);
static __inline__ void ScenarioEngineRequestMessageUIConfigure_delAndSetNull(void *ptr)
{
	ScenarioEngineRequestMessageUIConfigure **p = (ScenarioEngineRequestMessageUIConfigure **)ptr;
	if (p) { ScenarioEngineRequestMessageUIConfigure_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageUIConfigure_dump(ScenarioEngineRequestMessageUIConfigure *p, int tab);
// ScenarioEngineRequestMessageUIConfigure
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageWithData
typedef struct ScenarioEngineRequestMessageWithData
{
	Dz1Str		method;
	u32_t		seq;
	Dz1Str		data;
} ScenarioEngineRequestMessageWithData;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineRequestMessageWithData *ScenarioEngineRequestMessageWithData_new(Dz1Str method, 
																									   u32_t seq, 
																									   Dz1Str data, Dz1Error *err);
static __inline__ ScenarioEngineRequestMessageWithData *ScenarioEngineRequestMessageWithData_gen(Dz1Error *err) { return ScenarioEngineRequestMessageWithData_new(NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ScenarioEngineRequestMessageWithData_copy(ScenarioEngineRequestMessageWithData *dst, ScenarioEngineRequestMessageWithData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineRequestMessageWithData *ScenarioEngineRequestMessageWithData_clone(ScenarioEngineRequestMessageWithData *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageWithData_purge(ScenarioEngineRequestMessageWithData *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageWithData_del(ScenarioEngineRequestMessageWithData *p);
static __inline__ void ScenarioEngineRequestMessageWithData_delAndSetNull(void *ptr)
{
	ScenarioEngineRequestMessageWithData **p = (ScenarioEngineRequestMessageWithData **)ptr;
	if (p) { ScenarioEngineRequestMessageWithData_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageWithData_dump(ScenarioEngineRequestMessageWithData *p, int tab);
// ScenarioEngineRequestMessageWithData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageSetup
typedef struct ScenarioEngineRequestMessageSetup
{
	Dz1Str		method;
	u32_t		seq;
	Dz1Str		testConfiguration;
} ScenarioEngineRequestMessageSetup;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineRequestMessageSetup *ScenarioEngineRequestMessageSetup_new(Dz1Str method, 
																								 u32_t seq, 
																								 Dz1Str testConfiguration, Dz1Error *err);
static __inline__ ScenarioEngineRequestMessageSetup *ScenarioEngineRequestMessageSetup_gen(Dz1Error *err) { return ScenarioEngineRequestMessageSetup_new(NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ScenarioEngineRequestMessageSetup_copy(ScenarioEngineRequestMessageSetup *dst, ScenarioEngineRequestMessageSetup *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineRequestMessageSetup *ScenarioEngineRequestMessageSetup_clone(ScenarioEngineRequestMessageSetup *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageSetup_purge(ScenarioEngineRequestMessageSetup *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageSetup_del(ScenarioEngineRequestMessageSetup *p);
static __inline__ void ScenarioEngineRequestMessageSetup_delAndSetNull(void *ptr)
{
	ScenarioEngineRequestMessageSetup **p = (ScenarioEngineRequestMessageSetup **)ptr;
	if (p) { ScenarioEngineRequestMessageSetup_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageSetup_dump(ScenarioEngineRequestMessageSetup *p, int tab);
// ScenarioEngineRequestMessageSetup
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineNotifyStateContext
typedef struct ScenarioEngineNotifyStateContext
{
	Dz1Str		testName;
	s64_t		time;
	Dz1Str		state;
} ScenarioEngineNotifyStateContext;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineNotifyStateContext *ScenarioEngineNotifyStateContext_new(Dz1Str testName, 
																							   s64_t time, 
																							   Dz1Str state, Dz1Error *err);
static __inline__ ScenarioEngineNotifyStateContext *ScenarioEngineNotifyStateContext_gen(Dz1Error *err) { return ScenarioEngineNotifyStateContext_new(NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ScenarioEngineNotifyStateContext_copy(ScenarioEngineNotifyStateContext *dst, ScenarioEngineNotifyStateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineNotifyStateContext *ScenarioEngineNotifyStateContext_clone(ScenarioEngineNotifyStateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineNotifyStateContext_purge(ScenarioEngineNotifyStateContext *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineNotifyStateContext_del(ScenarioEngineNotifyStateContext *p);
static __inline__ void ScenarioEngineNotifyStateContext_delAndSetNull(void *ptr)
{
	ScenarioEngineNotifyStateContext **p = (ScenarioEngineNotifyStateContext **)ptr;
	if (p) { ScenarioEngineNotifyStateContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineNotifyStateContext_dump(ScenarioEngineNotifyStateContext *p, int tab);
// ScenarioEngineNotifyStateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineNotifyInfoContext
typedef struct ScenarioEngineNotifyInfoContext
{
	Dz1Str			 testName;
	s64_t			 time;
	Dz1Str			 sender;
	Dz1Str			 log;
	Dz1Binary		*data;
	Dz1Str			 dataType;
} ScenarioEngineNotifyInfoContext;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineNotifyInfoContext *ScenarioEngineNotifyInfoContext_new(Dz1Str testName, 
																							 s64_t time, 
																							 Dz1Str sender, 
																							 Dz1Str log, 
																							 Dz1Binary *data, 
																							 Dz1Str dataType, Dz1Error *err);
static __inline__ ScenarioEngineNotifyInfoContext *ScenarioEngineNotifyInfoContext_gen(Dz1Error *err) { return ScenarioEngineNotifyInfoContext_new(NULL, 0, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ScenarioEngineNotifyInfoContext_copy(ScenarioEngineNotifyInfoContext *dst, ScenarioEngineNotifyInfoContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineNotifyInfoContext *ScenarioEngineNotifyInfoContext_clone(ScenarioEngineNotifyInfoContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineNotifyInfoContext_purge(ScenarioEngineNotifyInfoContext *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineNotifyInfoContext_del(ScenarioEngineNotifyInfoContext *p);
static __inline__ void ScenarioEngineNotifyInfoContext_delAndSetNull(void *ptr)
{
	ScenarioEngineNotifyInfoContext **p = (ScenarioEngineNotifyInfoContext **)ptr;
	if (p) { ScenarioEngineNotifyInfoContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineNotifyInfoContext_dump(ScenarioEngineNotifyInfoContext *p, int tab);
// ScenarioEngineNotifyInfoContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineNotifyErrorContext
typedef struct ScenarioEngineNotifyErrorContext
{
	Dz1Str								 testName;
	s64_t								 time;
	ScenarioEngineProcessStatusCode		 code;
	Dz1Str								 desc;
	Dz1Str								 log;
	Dz1Binary							*data;
} ScenarioEngineNotifyErrorContext;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineNotifyErrorContext *ScenarioEngineNotifyErrorContext_new(Dz1Str testName, 
																							   s64_t time, 
																							   ScenarioEngineProcessStatusCode code, 
																							   Dz1Str desc, 
																							   Dz1Str log, 
																							   Dz1Binary *data, Dz1Error *err);
static __inline__ ScenarioEngineNotifyErrorContext *ScenarioEngineNotifyErrorContext_gen(Dz1Error *err) { return ScenarioEngineNotifyErrorContext_new(NULL, 0, ScenarioEngineProcessStatusCode_max, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ScenarioEngineNotifyErrorContext_copy(ScenarioEngineNotifyErrorContext *dst, ScenarioEngineNotifyErrorContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineNotifyErrorContext *ScenarioEngineNotifyErrorContext_clone(ScenarioEngineNotifyErrorContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineNotifyErrorContext_purge(ScenarioEngineNotifyErrorContext *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineNotifyErrorContext_del(ScenarioEngineNotifyErrorContext *p);
static __inline__ void ScenarioEngineNotifyErrorContext_delAndSetNull(void *ptr)
{
	ScenarioEngineNotifyErrorContext **p = (ScenarioEngineNotifyErrorContext **)ptr;
	if (p) { ScenarioEngineNotifyErrorContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineNotifyErrorContext_dump(ScenarioEngineNotifyErrorContext *p, int tab);
// ScenarioEngineNotifyErrorContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineNotifyStateArg
typedef struct ScenarioEngineNotifyStateArg
{
	u32_t								 testIdx;
	ScenarioEngineNotifyStateContext	*context;
} ScenarioEngineNotifyStateArg;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineNotifyStateArg *ScenarioEngineNotifyStateArg_new(u32_t testIdx, 
																					   ScenarioEngineNotifyStateContext *context, Dz1Error *err);
static __inline__ ScenarioEngineNotifyStateArg *ScenarioEngineNotifyStateArg_gen(Dz1Error *err) { return ScenarioEngineNotifyStateArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ScenarioEngineNotifyStateArg_copy(ScenarioEngineNotifyStateArg *dst, ScenarioEngineNotifyStateArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineNotifyStateArg *ScenarioEngineNotifyStateArg_clone(ScenarioEngineNotifyStateArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineNotifyStateArg_purge(ScenarioEngineNotifyStateArg *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineNotifyStateArg_del(ScenarioEngineNotifyStateArg *p);
static __inline__ void ScenarioEngineNotifyStateArg_delAndSetNull(void *ptr)
{
	ScenarioEngineNotifyStateArg **p = (ScenarioEngineNotifyStateArg **)ptr;
	if (p) { ScenarioEngineNotifyStateArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineNotifyStateArg_dump(ScenarioEngineNotifyStateArg *p, int tab);
// ScenarioEngineNotifyStateArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineNotifyInfoArg
typedef struct ScenarioEngineNotifyInfoArg
{
	u32_t								 testIdx;
	ScenarioEngineNotifyInfoContext		*context;
} ScenarioEngineNotifyInfoArg;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineNotifyInfoArg *ScenarioEngineNotifyInfoArg_new(u32_t testIdx, 
																					 ScenarioEngineNotifyInfoContext *context, Dz1Error *err);
static __inline__ ScenarioEngineNotifyInfoArg *ScenarioEngineNotifyInfoArg_gen(Dz1Error *err) { return ScenarioEngineNotifyInfoArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ScenarioEngineNotifyInfoArg_copy(ScenarioEngineNotifyInfoArg *dst, ScenarioEngineNotifyInfoArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineNotifyInfoArg *ScenarioEngineNotifyInfoArg_clone(ScenarioEngineNotifyInfoArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineNotifyInfoArg_purge(ScenarioEngineNotifyInfoArg *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineNotifyInfoArg_del(ScenarioEngineNotifyInfoArg *p);
static __inline__ void ScenarioEngineNotifyInfoArg_delAndSetNull(void *ptr)
{
	ScenarioEngineNotifyInfoArg **p = (ScenarioEngineNotifyInfoArg **)ptr;
	if (p) { ScenarioEngineNotifyInfoArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineNotifyInfoArg_dump(ScenarioEngineNotifyInfoArg *p, int tab);
// ScenarioEngineNotifyInfoArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineNotifyErrorArg
typedef struct ScenarioEngineNotifyErrorArg
{
	u32_t								 testIdx;
	ScenarioEngineNotifyErrorContext	*context;
} ScenarioEngineNotifyErrorArg;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineNotifyErrorArg *ScenarioEngineNotifyErrorArg_new(u32_t testIdx, 
																					   ScenarioEngineNotifyErrorContext *context, Dz1Error *err);
static __inline__ ScenarioEngineNotifyErrorArg *ScenarioEngineNotifyErrorArg_gen(Dz1Error *err) { return ScenarioEngineNotifyErrorArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ScenarioEngineNotifyErrorArg_copy(ScenarioEngineNotifyErrorArg *dst, ScenarioEngineNotifyErrorArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineNotifyErrorArg *ScenarioEngineNotifyErrorArg_clone(ScenarioEngineNotifyErrorArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineNotifyErrorArg_purge(ScenarioEngineNotifyErrorArg *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineNotifyErrorArg_del(ScenarioEngineNotifyErrorArg *p);
static __inline__ void ScenarioEngineNotifyErrorArg_delAndSetNull(void *ptr)
{
	ScenarioEngineNotifyErrorArg **p = (ScenarioEngineNotifyErrorArg **)ptr;
	if (p) { ScenarioEngineNotifyErrorArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineNotifyErrorArg_dump(ScenarioEngineNotifyErrorArg *p, int tab);
// ScenarioEngineNotifyErrorArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageNotifyState
typedef struct ScenarioEngineRequestMessageNotifyState
{
	Dz1Str								 method;
	u32_t								 seq;
	u32_t								 testIdx;
	Dz1Str								 level;
	ScenarioEngineNotifyStateContext	*data;
} ScenarioEngineRequestMessageNotifyState;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineRequestMessageNotifyState *ScenarioEngineRequestMessageNotifyState_new(Dz1Str method, 
																											 u32_t seq, 
																											 u32_t testIdx, 
																											 Dz1Str level, 
																											 ScenarioEngineNotifyStateContext *data, Dz1Error *err);
static __inline__ ScenarioEngineRequestMessageNotifyState *ScenarioEngineRequestMessageNotifyState_gen(Dz1Error *err) { return ScenarioEngineRequestMessageNotifyState_new(NULL, 0, 0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ScenarioEngineRequestMessageNotifyState_copy(ScenarioEngineRequestMessageNotifyState *dst, ScenarioEngineRequestMessageNotifyState *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineRequestMessageNotifyState *ScenarioEngineRequestMessageNotifyState_clone(ScenarioEngineRequestMessageNotifyState *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageNotifyState_purge(ScenarioEngineRequestMessageNotifyState *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageNotifyState_del(ScenarioEngineRequestMessageNotifyState *p);
static __inline__ void ScenarioEngineRequestMessageNotifyState_delAndSetNull(void *ptr)
{
	ScenarioEngineRequestMessageNotifyState **p = (ScenarioEngineRequestMessageNotifyState **)ptr;
	if (p) { ScenarioEngineRequestMessageNotifyState_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageNotifyState_dump(ScenarioEngineRequestMessageNotifyState *p, int tab);
// ScenarioEngineRequestMessageNotifyState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageNotifyInfo
typedef struct ScenarioEngineRequestMessageNotifyInfo
{
	Dz1Str								 method;
	u32_t								 seq;
	u32_t								 testIdx;
	Dz1Str								 level;
	ScenarioEngineNotifyInfoContext		*data;
} ScenarioEngineRequestMessageNotifyInfo;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineRequestMessageNotifyInfo *ScenarioEngineRequestMessageNotifyInfo_new(Dz1Str method, 
																										   u32_t seq, 
																										   u32_t testIdx, 
																										   Dz1Str level, 
																										   ScenarioEngineNotifyInfoContext *data, Dz1Error *err);
static __inline__ ScenarioEngineRequestMessageNotifyInfo *ScenarioEngineRequestMessageNotifyInfo_gen(Dz1Error *err) { return ScenarioEngineRequestMessageNotifyInfo_new(NULL, 0, 0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ScenarioEngineRequestMessageNotifyInfo_copy(ScenarioEngineRequestMessageNotifyInfo *dst, ScenarioEngineRequestMessageNotifyInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineRequestMessageNotifyInfo *ScenarioEngineRequestMessageNotifyInfo_clone(ScenarioEngineRequestMessageNotifyInfo *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageNotifyInfo_purge(ScenarioEngineRequestMessageNotifyInfo *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageNotifyInfo_del(ScenarioEngineRequestMessageNotifyInfo *p);
static __inline__ void ScenarioEngineRequestMessageNotifyInfo_delAndSetNull(void *ptr)
{
	ScenarioEngineRequestMessageNotifyInfo **p = (ScenarioEngineRequestMessageNotifyInfo **)ptr;
	if (p) { ScenarioEngineRequestMessageNotifyInfo_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageNotifyInfo_dump(ScenarioEngineRequestMessageNotifyInfo *p, int tab);
// ScenarioEngineRequestMessageNotifyInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageNotifyError
typedef struct ScenarioEngineRequestMessageNotifyError
{
	Dz1Str								 method;
	u32_t								 seq;
	u32_t								 testIdx;
	Dz1Str								 level;
	ScenarioEngineNotifyErrorContext	*data;
} ScenarioEngineRequestMessageNotifyError;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineRequestMessageNotifyError *ScenarioEngineRequestMessageNotifyError_new(Dz1Str method, 
																											 u32_t seq, 
																											 u32_t testIdx, 
																											 Dz1Str level, 
																											 ScenarioEngineNotifyErrorContext *data, Dz1Error *err);
static __inline__ ScenarioEngineRequestMessageNotifyError *ScenarioEngineRequestMessageNotifyError_gen(Dz1Error *err) { return ScenarioEngineRequestMessageNotifyError_new(NULL, 0, 0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ScenarioEngineRequestMessageNotifyError_copy(ScenarioEngineRequestMessageNotifyError *dst, ScenarioEngineRequestMessageNotifyError *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineRequestMessageNotifyError *ScenarioEngineRequestMessageNotifyError_clone(ScenarioEngineRequestMessageNotifyError *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageNotifyError_purge(ScenarioEngineRequestMessageNotifyError *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageNotifyError_del(ScenarioEngineRequestMessageNotifyError *p);
static __inline__ void ScenarioEngineRequestMessageNotifyError_delAndSetNull(void *ptr)
{
	ScenarioEngineRequestMessageNotifyError **p = (ScenarioEngineRequestMessageNotifyError **)ptr;
	if (p) { ScenarioEngineRequestMessageNotifyError_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageNotifyError_dump(ScenarioEngineRequestMessageNotifyError *p, int tab);
// ScenarioEngineRequestMessageNotifyError
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageNotifyPresent
typedef enum ScenarioEngineRequestMessageNotifyPresent
{
	ScenarioEngineRequestMessageNotifyPresent_state,
	ScenarioEngineRequestMessageNotifyPresent_info,
	ScenarioEngineRequestMessageNotifyPresent_error,
	ScenarioEngineRequestMessageNotifyPresent_max
} ScenarioEngineRequestMessageNotifyPresent;

DZ1_CPPLINK str_t ScenarioEngineRequestMessageNotifyPresentStrA(ScenarioEngineRequestMessageNotifyPresent v);
DZ1_CPPLINK ScenarioEngineRequestMessageNotifyPresent ScenarioEngineRequestMessageNotifyPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ScenarioEngineRequestMessageNotifyPresentStrW(ScenarioEngineRequestMessageNotifyPresent v);
DZ1_CPPLINK ScenarioEngineRequestMessageNotifyPresent ScenarioEngineRequestMessageNotifyPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define ScenarioEngineRequestMessageNotifyPresentStr ScenarioEngineRequestMessageNotifyPresentStrW
#define ScenarioEngineRequestMessageNotifyPresentFromStr ScenarioEngineRequestMessageNotifyPresentFromStrW
#else // UNICODE
#define ScenarioEngineRequestMessageNotifyPresentStr ScenarioEngineRequestMessageNotifyPresentStrA
#define ScenarioEngineRequestMessageNotifyPresentFromStr ScenarioEngineRequestMessageNotifyPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ScenarioEngineRequestMessageNotifyPresentStr ScenarioEngineRequestMessageNotifyPresentStrA
#define ScenarioEngineRequestMessageNotifyPresentFromStr ScenarioEngineRequestMessageNotifyPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineRequestMessageNotifyPresent *ScenarioEngineRequestMessageNotifyPresent_new(ScenarioEngineRequestMessageNotifyPresent *src, Dz1Error *err);
static __inline__ ScenarioEngineRequestMessageNotifyPresent *ScenarioEngineRequestMessageNotifyPresent_gen(Dz1Error *err) { ScenarioEngineRequestMessageNotifyPresent v = ScenarioEngineRequestMessageNotifyPresent_max; return ScenarioEngineRequestMessageNotifyPresent_new(&v, err); }
#define ScenarioEngineRequestMessageNotifyPresent_clone             ScenarioEngineRequestMessageNotifyPresent_new
static __inline__ void ScenarioEngineRequestMessageNotifyPresent_del(ScenarioEngineRequestMessageNotifyPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ScenarioEngineRequestMessageNotifyPresent_delAndSetNull(void *ptr)
{
	ScenarioEngineRequestMessageNotifyPresent **p = (ScenarioEngineRequestMessageNotifyPresent **)ptr;
	if (p != NULL) { ScenarioEngineRequestMessageNotifyPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageNotifyPresent_dump(ScenarioEngineRequestMessageNotifyPresent *v, int tab);
// ScenarioEngineRequestMessageNotifyPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageNotify
typedef struct ScenarioEngineRequestMessageNotify
{
	ScenarioEngineRequestMessageNotifyPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		ScenarioEngineRequestMessageNotifyState		*state;
		ScenarioEngineRequestMessageNotifyInfo		*info;
		ScenarioEngineRequestMessageNotifyError		*error;
	} x;
} ScenarioEngineRequestMessageNotify;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineRequestMessageNotify *ScenarioEngineRequestMessageNotify_new(ScenarioEngineRequestMessageNotifyPresent present, void *ptr, Dz1Error *err);
static __inline__ ScenarioEngineRequestMessageNotify *ScenarioEngineRequestMessageNotify_gen(Dz1Error *err) { return ScenarioEngineRequestMessageNotify_new(ScenarioEngineRequestMessageNotifyPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  ScenarioEngineRequestMessageNotify_copy(ScenarioEngineRequestMessageNotify *dst, ScenarioEngineRequestMessageNotify *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineRequestMessageNotify *ScenarioEngineRequestMessageNotify_clone(ScenarioEngineRequestMessageNotify *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageNotify_purge(ScenarioEngineRequestMessageNotify *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageNotify_del(ScenarioEngineRequestMessageNotify *p);
static __inline__ void ScenarioEngineRequestMessageNotify_delAndSetNull(void *ptr)
{
	ScenarioEngineRequestMessageNotify **p = (ScenarioEngineRequestMessageNotify **)ptr;
	if (p != NULL) { ScenarioEngineRequestMessageNotify_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageNotify_dump(ScenarioEngineRequestMessageNotify *p, int tab);
// ScenarioEngineRequestMessageNotify
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineValidateContext
typedef struct ScenarioEngineValidateContext
{
	Dz1Str								 testName;
	s64_t								 time;
	Dz1Binary							*raw;
	Dz1Binary							*data;
	ScenarioEngineProcessStatusCode		 code;
	Dz1Str								 desc;
} ScenarioEngineValidateContext;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineValidateContext *ScenarioEngineValidateContext_new(Dz1Str testName, 
																						 s64_t time, 
																						 Dz1Binary *raw, 
																						 Dz1Binary *data, 
																						 ScenarioEngineProcessStatusCode code, 
																						 Dz1Str desc, Dz1Error *err);
static __inline__ ScenarioEngineValidateContext *ScenarioEngineValidateContext_gen(Dz1Error *err) { return ScenarioEngineValidateContext_new(NULL, 0, NULL, NULL, ScenarioEngineProcessStatusCode_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ScenarioEngineValidateContext_copy(ScenarioEngineValidateContext *dst, ScenarioEngineValidateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineValidateContext *ScenarioEngineValidateContext_clone(ScenarioEngineValidateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineValidateContext_purge(ScenarioEngineValidateContext *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineValidateContext_del(ScenarioEngineValidateContext *p);
static __inline__ void ScenarioEngineValidateContext_delAndSetNull(void *ptr)
{
	ScenarioEngineValidateContext **p = (ScenarioEngineValidateContext **)ptr;
	if (p) { ScenarioEngineValidateContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineValidateContext_dump(ScenarioEngineValidateContext *p, int tab);
// ScenarioEngineValidateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageValidate
typedef struct ScenarioEngineRequestMessageValidate
{
	Dz1Str								 method;
	u32_t								 seq;
	u32_t								 testIdx;
	ScenarioEngineValidateContext		*validate;
} ScenarioEngineRequestMessageValidate;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineRequestMessageValidate *ScenarioEngineRequestMessageValidate_new(Dz1Str method, 
																									   u32_t seq, 
																									   u32_t testIdx, 
																									   ScenarioEngineValidateContext *validate, Dz1Error *err);
static __inline__ ScenarioEngineRequestMessageValidate *ScenarioEngineRequestMessageValidate_gen(Dz1Error *err) { return ScenarioEngineRequestMessageValidate_new(NULL, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ScenarioEngineRequestMessageValidate_copy(ScenarioEngineRequestMessageValidate *dst, ScenarioEngineRequestMessageValidate *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineRequestMessageValidate *ScenarioEngineRequestMessageValidate_clone(ScenarioEngineRequestMessageValidate *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageValidate_purge(ScenarioEngineRequestMessageValidate *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageValidate_del(ScenarioEngineRequestMessageValidate *p);
static __inline__ void ScenarioEngineRequestMessageValidate_delAndSetNull(void *ptr)
{
	ScenarioEngineRequestMessageValidate **p = (ScenarioEngineRequestMessageValidate **)ptr;
	if (p) { ScenarioEngineRequestMessageValidate_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineRequestMessageValidate_dump(ScenarioEngineRequestMessageValidate *p, int tab);
// ScenarioEngineRequestMessageValidate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineResponseMessageValidate
typedef struct ScenarioEngineResponseMessageValidate
{
	u32_t								 seq;
	u32_t								 testIdx;
	Dz1Str								 result;
	ScenarioEngineValidateContext		*validate;
} ScenarioEngineResponseMessageValidate;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineResponseMessageValidate *ScenarioEngineResponseMessageValidate_new(u32_t seq, 
																										 u32_t testIdx, 
																										 Dz1Str result, 
																										 ScenarioEngineValidateContext *validate, Dz1Error *err);
static __inline__ ScenarioEngineResponseMessageValidate *ScenarioEngineResponseMessageValidate_gen(Dz1Error *err) { return ScenarioEngineResponseMessageValidate_new(0, 0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ScenarioEngineResponseMessageValidate_copy(ScenarioEngineResponseMessageValidate *dst, ScenarioEngineResponseMessageValidate *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineResponseMessageValidate *ScenarioEngineResponseMessageValidate_clone(ScenarioEngineResponseMessageValidate *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineResponseMessageValidate_purge(ScenarioEngineResponseMessageValidate *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineResponseMessageValidate_del(ScenarioEngineResponseMessageValidate *p);
static __inline__ void ScenarioEngineResponseMessageValidate_delAndSetNull(void *ptr)
{
	ScenarioEngineResponseMessageValidate **p = (ScenarioEngineResponseMessageValidate **)ptr;
	if (p) { ScenarioEngineResponseMessageValidate_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineResponseMessageValidate_dump(ScenarioEngineResponseMessageValidate *p, int tab);
// ScenarioEngineResponseMessageValidate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineValidateContextArg
typedef struct ScenarioEngineValidateContextArg
{
	u32_t								 testIdx;
	ScenarioEngineValidateContext		*context;
} ScenarioEngineValidateContextArg;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineValidateContextArg *ScenarioEngineValidateContextArg_new(u32_t testIdx, 
																							   ScenarioEngineValidateContext *context, Dz1Error *err);
static __inline__ ScenarioEngineValidateContextArg *ScenarioEngineValidateContextArg_gen(Dz1Error *err) { return ScenarioEngineValidateContextArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t ScenarioEngineValidateContextArg_copy(ScenarioEngineValidateContextArg *dst, ScenarioEngineValidateContextArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineValidateContextArg *ScenarioEngineValidateContextArg_clone(ScenarioEngineValidateContextArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineValidateContextArg_purge(ScenarioEngineValidateContextArg *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineValidateContextArg_del(ScenarioEngineValidateContextArg *p);
static __inline__ void ScenarioEngineValidateContextArg_delAndSetNull(void *ptr)
{
	ScenarioEngineValidateContextArg **p = (ScenarioEngineValidateContextArg **)ptr;
	if (p) { ScenarioEngineValidateContextArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineValidateContextArg_dump(ScenarioEngineValidateContextArg *p, int tab);
// ScenarioEngineValidateContextArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineWebSocketResponseMessageContext
typedef struct ScenarioEngineWebSocketResponseMessageContext
{
	ScenarioEngineWebSocketStatusCode		code;
	Dz1Str									reason;
	Dz1Str									data;
} ScenarioEngineWebSocketResponseMessageContext;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineWebSocketResponseMessageContext *ScenarioEngineWebSocketResponseMessageContext_new(ScenarioEngineWebSocketStatusCode code, 
																														 Dz1Str reason, 
																														 Dz1Str data, Dz1Error *err);
static __inline__ ScenarioEngineWebSocketResponseMessageContext *ScenarioEngineWebSocketResponseMessageContext_gen(Dz1Error *err) { return ScenarioEngineWebSocketResponseMessageContext_new(ScenarioEngineWebSocketStatusCode_max, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineWebSocketResponseMessageContext_purge(ScenarioEngineWebSocketResponseMessageContext *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineWebSocketResponseMessageContext_del(ScenarioEngineWebSocketResponseMessageContext *p);
static __inline__ void ScenarioEngineWebSocketResponseMessageContext_delAndSetNull(void *ptr)
{
	ScenarioEngineWebSocketResponseMessageContext **p = (ScenarioEngineWebSocketResponseMessageContext **)ptr;
	if (p) { ScenarioEngineWebSocketResponseMessageContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineWebSocketResponseMessageContext_dump(ScenarioEngineWebSocketResponseMessageContext *p, int tab);
// ScenarioEngineWebSocketResponseMessageContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineResponseMessageDefault
typedef struct ScenarioEngineResponseMessageDefault
{
	u32_t												 seq;
	ScenarioEngineWebSocketResponseMessageContext		*result;
} ScenarioEngineResponseMessageDefault;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineResponseMessageDefault *ScenarioEngineResponseMessageDefault_new(u32_t seq, 
																									   ScenarioEngineWebSocketResponseMessageContext *result, Dz1Error *err);
static __inline__ ScenarioEngineResponseMessageDefault *ScenarioEngineResponseMessageDefault_gen(Dz1Error *err) { return ScenarioEngineResponseMessageDefault_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineResponseMessageDefault_purge(ScenarioEngineResponseMessageDefault *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineResponseMessageDefault_del(ScenarioEngineResponseMessageDefault *p);
static __inline__ void ScenarioEngineResponseMessageDefault_delAndSetNull(void *ptr)
{
	ScenarioEngineResponseMessageDefault **p = (ScenarioEngineResponseMessageDefault **)ptr;
	if (p) { ScenarioEngineResponseMessageDefault_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineResponseMessageDefault_dump(ScenarioEngineResponseMessageDefault *p, int tab);
// ScenarioEngineResponseMessageDefault
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineWebSocketMessageRequestPresent
typedef enum ScenarioEngineWebSocketMessageRequestPresent
{
	ScenarioEngineWebSocketMessageRequestPresent_request,
	ScenarioEngineWebSocketMessageRequestPresent_describe,
	ScenarioEngineWebSocketMessageRequestPresent_initialize,
	ScenarioEngineWebSocketMessageRequestPresent_uiConfigure,
	ScenarioEngineWebSocketMessageRequestPresent_withData,
	ScenarioEngineWebSocketMessageRequestPresent_setup,
	ScenarioEngineWebSocketMessageRequestPresent_notify,
	ScenarioEngineWebSocketMessageRequestPresent_validate,
	ScenarioEngineWebSocketMessageRequestPresent_max
} ScenarioEngineWebSocketMessageRequestPresent;

DZ1_CPPLINK str_t ScenarioEngineWebSocketMessageRequestPresentStrA(ScenarioEngineWebSocketMessageRequestPresent v);
DZ1_CPPLINK ScenarioEngineWebSocketMessageRequestPresent ScenarioEngineWebSocketMessageRequestPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ScenarioEngineWebSocketMessageRequestPresentStrW(ScenarioEngineWebSocketMessageRequestPresent v);
DZ1_CPPLINK ScenarioEngineWebSocketMessageRequestPresent ScenarioEngineWebSocketMessageRequestPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define ScenarioEngineWebSocketMessageRequestPresentStr ScenarioEngineWebSocketMessageRequestPresentStrW
#define ScenarioEngineWebSocketMessageRequestPresentFromStr ScenarioEngineWebSocketMessageRequestPresentFromStrW
#else // UNICODE
#define ScenarioEngineWebSocketMessageRequestPresentStr ScenarioEngineWebSocketMessageRequestPresentStrA
#define ScenarioEngineWebSocketMessageRequestPresentFromStr ScenarioEngineWebSocketMessageRequestPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ScenarioEngineWebSocketMessageRequestPresentStr ScenarioEngineWebSocketMessageRequestPresentStrA
#define ScenarioEngineWebSocketMessageRequestPresentFromStr ScenarioEngineWebSocketMessageRequestPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineWebSocketMessageRequestPresent *ScenarioEngineWebSocketMessageRequestPresent_new(ScenarioEngineWebSocketMessageRequestPresent *src, Dz1Error *err);
static __inline__ ScenarioEngineWebSocketMessageRequestPresent *ScenarioEngineWebSocketMessageRequestPresent_gen(Dz1Error *err) { ScenarioEngineWebSocketMessageRequestPresent v = ScenarioEngineWebSocketMessageRequestPresent_max; return ScenarioEngineWebSocketMessageRequestPresent_new(&v, err); }
static __inline__ void ScenarioEngineWebSocketMessageRequestPresent_del(ScenarioEngineWebSocketMessageRequestPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ScenarioEngineWebSocketMessageRequestPresent_delAndSetNull(void *ptr)
{
	ScenarioEngineWebSocketMessageRequestPresent **p = (ScenarioEngineWebSocketMessageRequestPresent **)ptr;
	if (p != NULL) { ScenarioEngineWebSocketMessageRequestPresent_del(*p); *p = NULL; }
}
// ScenarioEngineWebSocketMessageRequestPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineWebSocketMessageRequest
typedef struct ScenarioEngineWebSocketMessageRequest
{
	ScenarioEngineWebSocketMessageRequestPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		ScenarioEngineRequestMessageDefault			*request;
		ScenarioEngineRequestMessageDescribe		*describe;
		ScenarioEngineRequestMessageInitialize		*initialize;
		ScenarioEngineRequestMessageUIConfigure		*uiConfigure;
		ScenarioEngineRequestMessageWithData		*withData;
		ScenarioEngineRequestMessageSetup			*setup;
		ScenarioEngineRequestMessageNotify			*notify;
		ScenarioEngineRequestMessageValidate		*validate;
	} x;
} ScenarioEngineWebSocketMessageRequest;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineWebSocketMessageRequest *ScenarioEngineWebSocketMessageRequest_new(ScenarioEngineWebSocketMessageRequestPresent present, void *ptr, Dz1Error *err);
static __inline__ ScenarioEngineWebSocketMessageRequest *ScenarioEngineWebSocketMessageRequest_gen(Dz1Error *err) { return ScenarioEngineWebSocketMessageRequest_new(ScenarioEngineWebSocketMessageRequestPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineWebSocketMessageRequest_purge(ScenarioEngineWebSocketMessageRequest *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineWebSocketMessageRequest_del(ScenarioEngineWebSocketMessageRequest *p);
static __inline__ void ScenarioEngineWebSocketMessageRequest_delAndSetNull(void *ptr)
{
	ScenarioEngineWebSocketMessageRequest **p = (ScenarioEngineWebSocketMessageRequest **)ptr;
	if (p != NULL) { ScenarioEngineWebSocketMessageRequest_del(*p); *p = NULL; }
}
// ScenarioEngineWebSocketMessageRequest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineWebSocketMessageResponsePresent
typedef enum ScenarioEngineWebSocketMessageResponsePresent
{
	ScenarioEngineWebSocketMessageResponsePresent_response,
	ScenarioEngineWebSocketMessageResponsePresent_validate,
	ScenarioEngineWebSocketMessageResponsePresent_max
} ScenarioEngineWebSocketMessageResponsePresent;

DZ1_CPPLINK str_t ScenarioEngineWebSocketMessageResponsePresentStrA(ScenarioEngineWebSocketMessageResponsePresent v);
DZ1_CPPLINK ScenarioEngineWebSocketMessageResponsePresent ScenarioEngineWebSocketMessageResponsePresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ScenarioEngineWebSocketMessageResponsePresentStrW(ScenarioEngineWebSocketMessageResponsePresent v);
DZ1_CPPLINK ScenarioEngineWebSocketMessageResponsePresent ScenarioEngineWebSocketMessageResponsePresentFromStrW(wstr_t str);
#ifdef UNICODE
#define ScenarioEngineWebSocketMessageResponsePresentStr ScenarioEngineWebSocketMessageResponsePresentStrW
#define ScenarioEngineWebSocketMessageResponsePresentFromStr ScenarioEngineWebSocketMessageResponsePresentFromStrW
#else // UNICODE
#define ScenarioEngineWebSocketMessageResponsePresentStr ScenarioEngineWebSocketMessageResponsePresentStrA
#define ScenarioEngineWebSocketMessageResponsePresentFromStr ScenarioEngineWebSocketMessageResponsePresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ScenarioEngineWebSocketMessageResponsePresentStr ScenarioEngineWebSocketMessageResponsePresentStrA
#define ScenarioEngineWebSocketMessageResponsePresentFromStr ScenarioEngineWebSocketMessageResponsePresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineWebSocketMessageResponsePresent *ScenarioEngineWebSocketMessageResponsePresent_new(ScenarioEngineWebSocketMessageResponsePresent *src, Dz1Error *err);
static __inline__ ScenarioEngineWebSocketMessageResponsePresent *ScenarioEngineWebSocketMessageResponsePresent_gen(Dz1Error *err) { ScenarioEngineWebSocketMessageResponsePresent v = ScenarioEngineWebSocketMessageResponsePresent_max; return ScenarioEngineWebSocketMessageResponsePresent_new(&v, err); }
static __inline__ void ScenarioEngineWebSocketMessageResponsePresent_del(ScenarioEngineWebSocketMessageResponsePresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ScenarioEngineWebSocketMessageResponsePresent_delAndSetNull(void *ptr)
{
	ScenarioEngineWebSocketMessageResponsePresent **p = (ScenarioEngineWebSocketMessageResponsePresent **)ptr;
	if (p != NULL) { ScenarioEngineWebSocketMessageResponsePresent_del(*p); *p = NULL; }
}
// ScenarioEngineWebSocketMessageResponsePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineWebSocketMessageResponse
typedef struct ScenarioEngineWebSocketMessageResponse
{
	ScenarioEngineWebSocketMessageResponsePresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		ScenarioEngineResponseMessageDefault		*response;
		ScenarioEngineResponseMessageValidate		*validate;
	} x;
} ScenarioEngineWebSocketMessageResponse;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineWebSocketMessageResponse *ScenarioEngineWebSocketMessageResponse_new(ScenarioEngineWebSocketMessageResponsePresent present, void *ptr, Dz1Error *err);
static __inline__ ScenarioEngineWebSocketMessageResponse *ScenarioEngineWebSocketMessageResponse_gen(Dz1Error *err) { return ScenarioEngineWebSocketMessageResponse_new(ScenarioEngineWebSocketMessageResponsePresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineWebSocketMessageResponse_purge(ScenarioEngineWebSocketMessageResponse *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineWebSocketMessageResponse_del(ScenarioEngineWebSocketMessageResponse *p);
static __inline__ void ScenarioEngineWebSocketMessageResponse_delAndSetNull(void *ptr)
{
	ScenarioEngineWebSocketMessageResponse **p = (ScenarioEngineWebSocketMessageResponse **)ptr;
	if (p != NULL) { ScenarioEngineWebSocketMessageResponse_del(*p); *p = NULL; }
}
// ScenarioEngineWebSocketMessageResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineWebSocketMessagePresent
typedef enum ScenarioEngineWebSocketMessagePresent
{
	ScenarioEngineWebSocketMessagePresent_rsp,
	ScenarioEngineWebSocketMessagePresent_req,
	ScenarioEngineWebSocketMessagePresent_max
} ScenarioEngineWebSocketMessagePresent;

DZ1_CPPLINK str_t ScenarioEngineWebSocketMessagePresentStrA(ScenarioEngineWebSocketMessagePresent v);
DZ1_CPPLINK ScenarioEngineWebSocketMessagePresent ScenarioEngineWebSocketMessagePresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t ScenarioEngineWebSocketMessagePresentStrW(ScenarioEngineWebSocketMessagePresent v);
DZ1_CPPLINK ScenarioEngineWebSocketMessagePresent ScenarioEngineWebSocketMessagePresentFromStrW(wstr_t str);
#ifdef UNICODE
#define ScenarioEngineWebSocketMessagePresentStr ScenarioEngineWebSocketMessagePresentStrW
#define ScenarioEngineWebSocketMessagePresentFromStr ScenarioEngineWebSocketMessagePresentFromStrW
#else // UNICODE
#define ScenarioEngineWebSocketMessagePresentStr ScenarioEngineWebSocketMessagePresentStrA
#define ScenarioEngineWebSocketMessagePresentFromStr ScenarioEngineWebSocketMessagePresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define ScenarioEngineWebSocketMessagePresentStr ScenarioEngineWebSocketMessagePresentStrA
#define ScenarioEngineWebSocketMessagePresentFromStr ScenarioEngineWebSocketMessagePresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineWebSocketMessagePresent *ScenarioEngineWebSocketMessagePresent_new(ScenarioEngineWebSocketMessagePresent *src, Dz1Error *err);
static __inline__ ScenarioEngineWebSocketMessagePresent *ScenarioEngineWebSocketMessagePresent_gen(Dz1Error *err) { ScenarioEngineWebSocketMessagePresent v = ScenarioEngineWebSocketMessagePresent_max; return ScenarioEngineWebSocketMessagePresent_new(&v, err); }
static __inline__ void ScenarioEngineWebSocketMessagePresent_del(ScenarioEngineWebSocketMessagePresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void ScenarioEngineWebSocketMessagePresent_delAndSetNull(void *ptr)
{
	ScenarioEngineWebSocketMessagePresent **p = (ScenarioEngineWebSocketMessagePresent **)ptr;
	if (p != NULL) { ScenarioEngineWebSocketMessagePresent_del(*p); *p = NULL; }
}
// ScenarioEngineWebSocketMessagePresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineWebSocketMessage
typedef struct ScenarioEngineWebSocketMessage
{
	ScenarioEngineWebSocketMessagePresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		ScenarioEngineWebSocketMessageResponse		*rsp;
		ScenarioEngineWebSocketMessageRequest		*req;
	} x;
} ScenarioEngineWebSocketMessage;

DZ1_CPPLINK DZ1_DLLPORT ScenarioEngineWebSocketMessage *ScenarioEngineWebSocketMessage_new(ScenarioEngineWebSocketMessagePresent present, void *ptr, Dz1Error *err);
static __inline__ ScenarioEngineWebSocketMessage *ScenarioEngineWebSocketMessage_gen(Dz1Error *err) { return ScenarioEngineWebSocketMessage_new(ScenarioEngineWebSocketMessagePresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineWebSocketMessage_purge(ScenarioEngineWebSocketMessage *p);
DZ1_CPPLINK DZ1_DLLPORT void ScenarioEngineWebSocketMessage_del(ScenarioEngineWebSocketMessage *p);
static __inline__ void ScenarioEngineWebSocketMessage_delAndSetNull(void *ptr)
{
	ScenarioEngineWebSocketMessage **p = (ScenarioEngineWebSocketMessage **)ptr;
	if (p != NULL) { ScenarioEngineWebSocketMessage_del(*p); *p = NULL; }
}
// ScenarioEngineWebSocketMessage
////////////////////////////////////////////////////////////////////////////////

#endif

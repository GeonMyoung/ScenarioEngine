#ifndef _DZ1_TDC_GITSN_D_S_R_C_MSG_TEST_SCENARIO_DEF_H_
#define _DZ1_TDC_GITSN_D_S_R_C_MSG_TEST_SCENARIO_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "GitsnAsnUtilDef.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgTestScenarioException
typedef void (*GitsnDSRCMsgTestScenarioException)(void *exceptionArg, Dz1Error *reason);
// GitsnDSRCMsgTestScenarioException
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgProcessStatusCode
typedef enum GitsnDSRCMsgProcessStatusCode
{
	GitsnDSRCMsgProcessStatusCode_OK = 0,
	GitsnDSRCMsgProcessStatusCode_FAILURE = 1,
	GitsnDSRCMsgProcessStatusCode_AGENT_SYSTEM_ERROR = 11,
	GitsnDSRCMsgProcessStatusCode_SERVER_DISCONNECTED = 12,
	GitsnDSRCMsgProcessStatusCode_TEST_CONFIGURATION_ERROR = 13,
	GitsnDSRCMsgProcessStatusCode_CONNECTION_FAIL = 100,
	GitsnDSRCMsgProcessStatusCode_DISCONNECTED = 101,
	GitsnDSRCMsgProcessStatusCode_TIMEOUT = 102,
	GitsnDSRCMsgProcessStatusCode_OUT_OF_RANGE = 201,
	GitsnDSRCMsgProcessStatusCode_INVALID_PROCESS,
	GitsnDSRCMsgProcessStatusCode_INVALID_IDENTIFIER,
	GitsnDSRCMsgProcessStatusCode_SESSION_DUPLICATE,
	GitsnDSRCMsgProcessStatusCode_LOGIN_AUTH_ERROR,
	GitsnDSRCMsgProcessStatusCode_DECODE_FAIL = 210,
	GitsnDSRCMsgProcessStatusCode_INVALID_ENCODING_RULE = 211,
	GitsnDSRCMsgProcessStatusCode_INVALID_OID = 212,
	GitsnDSRCMsgProcessStatusCode_INVALID_DSRC_MSG_ID = 213,
	GitsnDSRCMsgProcessStatusCode_JSON_PARSE_ERROR = 221,
	GitsnDSRCMsgProcessStatusCode_PROTOBUF_DESERAILIZE_ERROR = 231,
	GitsnDSRCMsgProcessStatusCode_INVALID_TOPIC = 241,
	GitsnDSRCMsgProcessStatusCode_INVALID_REQUEST = 251,
	GitsnDSRCMsgProcessStatusCode_UNKNOWN = 300,
	GitsnDSRCMsgProcessStatusCode_max
} GitsnDSRCMsgProcessStatusCode;

DZ1_CPPLINK str_t GitsnDSRCMsgProcessStatusCodeStrA(GitsnDSRCMsgProcessStatusCode v);
DZ1_CPPLINK GitsnDSRCMsgProcessStatusCode GitsnDSRCMsgProcessStatusCodeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t GitsnDSRCMsgProcessStatusCodeStrW(GitsnDSRCMsgProcessStatusCode v);
DZ1_CPPLINK GitsnDSRCMsgProcessStatusCode GitsnDSRCMsgProcessStatusCodeFromStrW(wstr_t str);
#ifdef UNICODE
#define GitsnDSRCMsgProcessStatusCodeStr GitsnDSRCMsgProcessStatusCodeStrW
#define GitsnDSRCMsgProcessStatusCodeFromStr GitsnDSRCMsgProcessStatusCodeFromStrW
#else // UNICODE
#define GitsnDSRCMsgProcessStatusCodeStr GitsnDSRCMsgProcessStatusCodeStrA
#define GitsnDSRCMsgProcessStatusCodeFromStr GitsnDSRCMsgProcessStatusCodeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define GitsnDSRCMsgProcessStatusCodeStr GitsnDSRCMsgProcessStatusCodeStrA
#define GitsnDSRCMsgProcessStatusCodeFromStr GitsnDSRCMsgProcessStatusCodeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgProcessStatusCode *GitsnDSRCMsgProcessStatusCode_new(GitsnDSRCMsgProcessStatusCode *src, Dz1Error *err);
static __inline__ GitsnDSRCMsgProcessStatusCode *GitsnDSRCMsgProcessStatusCode_gen(Dz1Error *err) { GitsnDSRCMsgProcessStatusCode v = GitsnDSRCMsgProcessStatusCode_max; return GitsnDSRCMsgProcessStatusCode_new(&v, err); }
#define GitsnDSRCMsgProcessStatusCode_clone             GitsnDSRCMsgProcessStatusCode_new
static __inline__ void GitsnDSRCMsgProcessStatusCode_del(GitsnDSRCMsgProcessStatusCode *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void GitsnDSRCMsgProcessStatusCode_delAndSetNull(void *ptr)
{
	GitsnDSRCMsgProcessStatusCode **p = (GitsnDSRCMsgProcessStatusCode **)ptr;
	if (p != NULL) { GitsnDSRCMsgProcessStatusCode_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgProcessStatusCode_dump(GitsnDSRCMsgProcessStatusCode *v, int tab);
// GitsnDSRCMsgProcessStatusCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgNotifyStateContext
typedef struct GitsnDSRCMsgNotifyStateContext
{
	Dz1Str		testName;
	s64_t		time;
	Dz1Str		state;
} GitsnDSRCMsgNotifyStateContext;

DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgNotifyStateContext *GitsnDSRCMsgNotifyStateContext_new(Dz1Str testName, 
																						   s64_t time, 
																						   Dz1Str state, Dz1Error *err);
static __inline__ GitsnDSRCMsgNotifyStateContext *GitsnDSRCMsgNotifyStateContext_gen(Dz1Error *err) { return GitsnDSRCMsgNotifyStateContext_new(NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t GitsnDSRCMsgNotifyStateContext_copy(GitsnDSRCMsgNotifyStateContext *dst, GitsnDSRCMsgNotifyStateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgNotifyStateContext *GitsnDSRCMsgNotifyStateContext_clone(GitsnDSRCMsgNotifyStateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgNotifyStateContext_purge(GitsnDSRCMsgNotifyStateContext *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgNotifyStateContext_del(GitsnDSRCMsgNotifyStateContext *p);
static __inline__ void GitsnDSRCMsgNotifyStateContext_delAndSetNull(void *ptr)
{
	GitsnDSRCMsgNotifyStateContext **p = (GitsnDSRCMsgNotifyStateContext **)ptr;
	if (p) { GitsnDSRCMsgNotifyStateContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgNotifyStateContext_dump(GitsnDSRCMsgNotifyStateContext *p, int tab);
// GitsnDSRCMsgNotifyStateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgNotifyInfoContext
typedef struct GitsnDSRCMsgNotifyInfoContext
{
	Dz1Str			 testName;
	s64_t			 time;
	Dz1Str			 sender;
	Dz1Str			 log;
	Dz1Binary		*data;
	Dz1Str			 dataType;
} GitsnDSRCMsgNotifyInfoContext;

DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgNotifyInfoContext *GitsnDSRCMsgNotifyInfoContext_new(Dz1Str testName, 
																						 s64_t time, 
																						 Dz1Str sender, 
																						 Dz1Str log, 
																						 Dz1Binary *data, 
																						 Dz1Str dataType, Dz1Error *err);
static __inline__ GitsnDSRCMsgNotifyInfoContext *GitsnDSRCMsgNotifyInfoContext_gen(Dz1Error *err) { return GitsnDSRCMsgNotifyInfoContext_new(NULL, 0, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t GitsnDSRCMsgNotifyInfoContext_copy(GitsnDSRCMsgNotifyInfoContext *dst, GitsnDSRCMsgNotifyInfoContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgNotifyInfoContext *GitsnDSRCMsgNotifyInfoContext_clone(GitsnDSRCMsgNotifyInfoContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgNotifyInfoContext_purge(GitsnDSRCMsgNotifyInfoContext *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgNotifyInfoContext_del(GitsnDSRCMsgNotifyInfoContext *p);
static __inline__ void GitsnDSRCMsgNotifyInfoContext_delAndSetNull(void *ptr)
{
	GitsnDSRCMsgNotifyInfoContext **p = (GitsnDSRCMsgNotifyInfoContext **)ptr;
	if (p) { GitsnDSRCMsgNotifyInfoContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgNotifyInfoContext_dump(GitsnDSRCMsgNotifyInfoContext *p, int tab);
// GitsnDSRCMsgNotifyInfoContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgNotifyErrorContext
typedef struct GitsnDSRCMsgNotifyErrorContext
{
	Dz1Str								 testName;
	s64_t								 time;
	GitsnDSRCMsgProcessStatusCode		 code;
	Dz1Str								 desc;
	Dz1Str								 log;
	Dz1Binary							*data;
} GitsnDSRCMsgNotifyErrorContext;

DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgNotifyErrorContext *GitsnDSRCMsgNotifyErrorContext_new(Dz1Str testName, 
																						   s64_t time, 
																						   GitsnDSRCMsgProcessStatusCode code, 
																						   Dz1Str desc, 
																						   Dz1Str log, 
																						   Dz1Binary *data, Dz1Error *err);
static __inline__ GitsnDSRCMsgNotifyErrorContext *GitsnDSRCMsgNotifyErrorContext_gen(Dz1Error *err) { return GitsnDSRCMsgNotifyErrorContext_new(NULL, 0, GitsnDSRCMsgProcessStatusCode_max, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t GitsnDSRCMsgNotifyErrorContext_copy(GitsnDSRCMsgNotifyErrorContext *dst, GitsnDSRCMsgNotifyErrorContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgNotifyErrorContext *GitsnDSRCMsgNotifyErrorContext_clone(GitsnDSRCMsgNotifyErrorContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgNotifyErrorContext_purge(GitsnDSRCMsgNotifyErrorContext *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgNotifyErrorContext_del(GitsnDSRCMsgNotifyErrorContext *p);
static __inline__ void GitsnDSRCMsgNotifyErrorContext_delAndSetNull(void *ptr)
{
	GitsnDSRCMsgNotifyErrorContext **p = (GitsnDSRCMsgNotifyErrorContext **)ptr;
	if (p) { GitsnDSRCMsgNotifyErrorContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgNotifyErrorContext_dump(GitsnDSRCMsgNotifyErrorContext *p, int tab);
// GitsnDSRCMsgNotifyErrorContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgNotifyStateArg
typedef struct GitsnDSRCMsgNotifyStateArg
{
	u32_t								 testIdx;
	GitsnDSRCMsgNotifyStateContext		*context;
} GitsnDSRCMsgNotifyStateArg;

DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgNotifyStateArg *GitsnDSRCMsgNotifyStateArg_new(u32_t testIdx, 
																				   GitsnDSRCMsgNotifyStateContext *context, Dz1Error *err);
static __inline__ GitsnDSRCMsgNotifyStateArg *GitsnDSRCMsgNotifyStateArg_gen(Dz1Error *err) { return GitsnDSRCMsgNotifyStateArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t GitsnDSRCMsgNotifyStateArg_copy(GitsnDSRCMsgNotifyStateArg *dst, GitsnDSRCMsgNotifyStateArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgNotifyStateArg *GitsnDSRCMsgNotifyStateArg_clone(GitsnDSRCMsgNotifyStateArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgNotifyStateArg_purge(GitsnDSRCMsgNotifyStateArg *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgNotifyStateArg_del(GitsnDSRCMsgNotifyStateArg *p);
static __inline__ void GitsnDSRCMsgNotifyStateArg_delAndSetNull(void *ptr)
{
	GitsnDSRCMsgNotifyStateArg **p = (GitsnDSRCMsgNotifyStateArg **)ptr;
	if (p) { GitsnDSRCMsgNotifyStateArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgNotifyStateArg_dump(GitsnDSRCMsgNotifyStateArg *p, int tab);
// GitsnDSRCMsgNotifyStateArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgNotifyInfoArg
typedef struct GitsnDSRCMsgNotifyInfoArg
{
	u32_t								 testIdx;
	GitsnDSRCMsgNotifyInfoContext		*context;
} GitsnDSRCMsgNotifyInfoArg;

DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgNotifyInfoArg *GitsnDSRCMsgNotifyInfoArg_new(u32_t testIdx, 
																				 GitsnDSRCMsgNotifyInfoContext *context, Dz1Error *err);
static __inline__ GitsnDSRCMsgNotifyInfoArg *GitsnDSRCMsgNotifyInfoArg_gen(Dz1Error *err) { return GitsnDSRCMsgNotifyInfoArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t GitsnDSRCMsgNotifyInfoArg_copy(GitsnDSRCMsgNotifyInfoArg *dst, GitsnDSRCMsgNotifyInfoArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgNotifyInfoArg *GitsnDSRCMsgNotifyInfoArg_clone(GitsnDSRCMsgNotifyInfoArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgNotifyInfoArg_purge(GitsnDSRCMsgNotifyInfoArg *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgNotifyInfoArg_del(GitsnDSRCMsgNotifyInfoArg *p);
static __inline__ void GitsnDSRCMsgNotifyInfoArg_delAndSetNull(void *ptr)
{
	GitsnDSRCMsgNotifyInfoArg **p = (GitsnDSRCMsgNotifyInfoArg **)ptr;
	if (p) { GitsnDSRCMsgNotifyInfoArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgNotifyInfoArg_dump(GitsnDSRCMsgNotifyInfoArg *p, int tab);
// GitsnDSRCMsgNotifyInfoArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgNotifyErrorArg
typedef struct GitsnDSRCMsgNotifyErrorArg
{
	u32_t								 testIdx;
	GitsnDSRCMsgNotifyErrorContext		*context;
} GitsnDSRCMsgNotifyErrorArg;

DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgNotifyErrorArg *GitsnDSRCMsgNotifyErrorArg_new(u32_t testIdx, 
																				   GitsnDSRCMsgNotifyErrorContext *context, Dz1Error *err);
static __inline__ GitsnDSRCMsgNotifyErrorArg *GitsnDSRCMsgNotifyErrorArg_gen(Dz1Error *err) { return GitsnDSRCMsgNotifyErrorArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t GitsnDSRCMsgNotifyErrorArg_copy(GitsnDSRCMsgNotifyErrorArg *dst, GitsnDSRCMsgNotifyErrorArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgNotifyErrorArg *GitsnDSRCMsgNotifyErrorArg_clone(GitsnDSRCMsgNotifyErrorArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgNotifyErrorArg_purge(GitsnDSRCMsgNotifyErrorArg *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgNotifyErrorArg_del(GitsnDSRCMsgNotifyErrorArg *p);
static __inline__ void GitsnDSRCMsgNotifyErrorArg_delAndSetNull(void *ptr)
{
	GitsnDSRCMsgNotifyErrorArg **p = (GitsnDSRCMsgNotifyErrorArg **)ptr;
	if (p) { GitsnDSRCMsgNotifyErrorArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgNotifyErrorArg_dump(GitsnDSRCMsgNotifyErrorArg *p, int tab);
// GitsnDSRCMsgNotifyErrorArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgNotifyContextPresent
typedef enum GitsnDSRCMsgNotifyContextPresent
{
	GitsnDSRCMsgNotifyContextPresent_state,
	GitsnDSRCMsgNotifyContextPresent_info,
	GitsnDSRCMsgNotifyContextPresent_error,
	GitsnDSRCMsgNotifyContextPresent_max
} GitsnDSRCMsgNotifyContextPresent;

DZ1_CPPLINK str_t GitsnDSRCMsgNotifyContextPresentStrA(GitsnDSRCMsgNotifyContextPresent v);
DZ1_CPPLINK GitsnDSRCMsgNotifyContextPresent GitsnDSRCMsgNotifyContextPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t GitsnDSRCMsgNotifyContextPresentStrW(GitsnDSRCMsgNotifyContextPresent v);
DZ1_CPPLINK GitsnDSRCMsgNotifyContextPresent GitsnDSRCMsgNotifyContextPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define GitsnDSRCMsgNotifyContextPresentStr GitsnDSRCMsgNotifyContextPresentStrW
#define GitsnDSRCMsgNotifyContextPresentFromStr GitsnDSRCMsgNotifyContextPresentFromStrW
#else // UNICODE
#define GitsnDSRCMsgNotifyContextPresentStr GitsnDSRCMsgNotifyContextPresentStrA
#define GitsnDSRCMsgNotifyContextPresentFromStr GitsnDSRCMsgNotifyContextPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define GitsnDSRCMsgNotifyContextPresentStr GitsnDSRCMsgNotifyContextPresentStrA
#define GitsnDSRCMsgNotifyContextPresentFromStr GitsnDSRCMsgNotifyContextPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgNotifyContextPresent *GitsnDSRCMsgNotifyContextPresent_new(GitsnDSRCMsgNotifyContextPresent *src, Dz1Error *err);
static __inline__ GitsnDSRCMsgNotifyContextPresent *GitsnDSRCMsgNotifyContextPresent_gen(Dz1Error *err) { GitsnDSRCMsgNotifyContextPresent v = GitsnDSRCMsgNotifyContextPresent_max; return GitsnDSRCMsgNotifyContextPresent_new(&v, err); }
#define GitsnDSRCMsgNotifyContextPresent_clone             GitsnDSRCMsgNotifyContextPresent_new
static __inline__ void GitsnDSRCMsgNotifyContextPresent_del(GitsnDSRCMsgNotifyContextPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void GitsnDSRCMsgNotifyContextPresent_delAndSetNull(void *ptr)
{
	GitsnDSRCMsgNotifyContextPresent **p = (GitsnDSRCMsgNotifyContextPresent **)ptr;
	if (p != NULL) { GitsnDSRCMsgNotifyContextPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgNotifyContextPresent_dump(GitsnDSRCMsgNotifyContextPresent *v, int tab);
// GitsnDSRCMsgNotifyContextPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgNotifyContext
typedef struct GitsnDSRCMsgNotifyContext
{
	GitsnDSRCMsgNotifyContextPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		GitsnDSRCMsgNotifyStateContext		*state;
		GitsnDSRCMsgNotifyInfoContext		*info;
		GitsnDSRCMsgNotifyErrorContext		*error;
	} x;
} GitsnDSRCMsgNotifyContext;

DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgNotifyContext *GitsnDSRCMsgNotifyContext_new(GitsnDSRCMsgNotifyContextPresent present, void *ptr, Dz1Error *err);
static __inline__ GitsnDSRCMsgNotifyContext *GitsnDSRCMsgNotifyContext_gen(Dz1Error *err) { return GitsnDSRCMsgNotifyContext_new(GitsnDSRCMsgNotifyContextPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  GitsnDSRCMsgNotifyContext_copy(GitsnDSRCMsgNotifyContext *dst, GitsnDSRCMsgNotifyContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgNotifyContext *GitsnDSRCMsgNotifyContext_clone(GitsnDSRCMsgNotifyContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgNotifyContext_purge(GitsnDSRCMsgNotifyContext *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgNotifyContext_del(GitsnDSRCMsgNotifyContext *p);
static __inline__ void GitsnDSRCMsgNotifyContext_delAndSetNull(void *ptr)
{
	GitsnDSRCMsgNotifyContext **p = (GitsnDSRCMsgNotifyContext **)ptr;
	if (p != NULL) { GitsnDSRCMsgNotifyContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgNotifyContext_dump(GitsnDSRCMsgNotifyContext *p, int tab);
// GitsnDSRCMsgNotifyContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgValidateContext
typedef struct GitsnDSRCMsgValidateContext
{
	Dz1Str								 testName;
	s64_t								 time;
	Dz1Binary							*raw;
	Dz1Binary							*data;
	GitsnDSRCMsgProcessStatusCode		 code;
	Dz1Str								 desc;
} GitsnDSRCMsgValidateContext;

DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgValidateContext *GitsnDSRCMsgValidateContext_new(Dz1Str testName, 
																					 s64_t time, 
																					 Dz1Binary *raw, 
																					 Dz1Binary *data, 
																					 GitsnDSRCMsgProcessStatusCode code, 
																					 Dz1Str desc, Dz1Error *err);
static __inline__ GitsnDSRCMsgValidateContext *GitsnDSRCMsgValidateContext_gen(Dz1Error *err) { return GitsnDSRCMsgValidateContext_new(NULL, 0, NULL, NULL, GitsnDSRCMsgProcessStatusCode_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t GitsnDSRCMsgValidateContext_copy(GitsnDSRCMsgValidateContext *dst, GitsnDSRCMsgValidateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgValidateContext *GitsnDSRCMsgValidateContext_clone(GitsnDSRCMsgValidateContext *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgValidateContext_purge(GitsnDSRCMsgValidateContext *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgValidateContext_del(GitsnDSRCMsgValidateContext *p);
static __inline__ void GitsnDSRCMsgValidateContext_delAndSetNull(void *ptr)
{
	GitsnDSRCMsgValidateContext **p = (GitsnDSRCMsgValidateContext **)ptr;
	if (p) { GitsnDSRCMsgValidateContext_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgValidateContext_dump(GitsnDSRCMsgValidateContext *p, int tab);
// GitsnDSRCMsgValidateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgValidateContextArg
typedef struct GitsnDSRCMsgValidateContextArg
{
	u32_t							 testIdx;
	GitsnDSRCMsgValidateContext		*context;
} GitsnDSRCMsgValidateContextArg;

DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgValidateContextArg *GitsnDSRCMsgValidateContextArg_new(u32_t testIdx, 
																						   GitsnDSRCMsgValidateContext *context, Dz1Error *err);
static __inline__ GitsnDSRCMsgValidateContextArg *GitsnDSRCMsgValidateContextArg_gen(Dz1Error *err) { return GitsnDSRCMsgValidateContextArg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t GitsnDSRCMsgValidateContextArg_copy(GitsnDSRCMsgValidateContextArg *dst, GitsnDSRCMsgValidateContextArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgValidateContextArg *GitsnDSRCMsgValidateContextArg_clone(GitsnDSRCMsgValidateContextArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgValidateContextArg_purge(GitsnDSRCMsgValidateContextArg *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgValidateContextArg_del(GitsnDSRCMsgValidateContextArg *p);
static __inline__ void GitsnDSRCMsgValidateContextArg_delAndSetNull(void *ptr)
{
	GitsnDSRCMsgValidateContextArg **p = (GitsnDSRCMsgValidateContextArg **)ptr;
	if (p) { GitsnDSRCMsgValidateContextArg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgValidateContextArg_dump(GitsnDSRCMsgValidateContextArg *p, int tab);
// GitsnDSRCMsgValidateContextArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgTestConfiguration
typedef struct GitsnDSRCMsgTestConfiguration
{
	s64_t		local_port;
	bool_t		test_map;
	bool_t		test_spat;
	bool_t		test_bsm;
	bool_t		test_eva;
	bool_t		test_pvd;
	bool_t		test_rsa;
	bool_t		test_rtcm;
	bool_t		test_srm;
	bool_t		test_ssm;
	bool_t		test_tim;
	bool_t		test_psm;
	bool_t		test_sdsm;
	bool_t		test_tls;
} GitsnDSRCMsgTestConfiguration;

DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgTestConfiguration *GitsnDSRCMsgTestConfiguration_new(s64_t local_port, 
																						 bool_t test_map, 
																						 bool_t test_spat, 
																						 bool_t test_bsm, 
																						 bool_t test_eva, 
																						 bool_t test_pvd, 
																						 bool_t test_rsa, 
																						 bool_t test_rtcm, 
																						 bool_t test_srm, 
																						 bool_t test_ssm, 
																						 bool_t test_tim, 
																						 bool_t test_psm, 
																						 bool_t test_sdsm, 
																						 bool_t test_tls, Dz1Error *err);
static __inline__ GitsnDSRCMsgTestConfiguration *GitsnDSRCMsgTestConfiguration_gen(Dz1Error *err) { return GitsnDSRCMsgTestConfiguration_new(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t GitsnDSRCMsgTestConfiguration_copy(GitsnDSRCMsgTestConfiguration *dst, GitsnDSRCMsgTestConfiguration *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgTestConfiguration *GitsnDSRCMsgTestConfiguration_clone(GitsnDSRCMsgTestConfiguration *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgTestConfiguration_purge(GitsnDSRCMsgTestConfiguration *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgTestConfiguration_del(GitsnDSRCMsgTestConfiguration *p);
static __inline__ void GitsnDSRCMsgTestConfiguration_delAndSetNull(void *ptr)
{
	GitsnDSRCMsgTestConfiguration **p = (GitsnDSRCMsgTestConfiguration **)ptr;
	if (p) { GitsnDSRCMsgTestConfiguration_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgTestConfiguration_dump(GitsnDSRCMsgTestConfiguration *p, int tab);
// GitsnDSRCMsgTestConfiguration
////////////////////////////////////////////////////////////////////////////////

#endif

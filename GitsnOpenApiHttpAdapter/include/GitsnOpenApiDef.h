#ifndef _DZ1_TDC_GITSN_OPEN_API_DEF_H_
#define _DZ1_TDC_GITSN_OPEN_API_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "dz1_io_stream_support.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiException
typedef void (*GitsnOpenApiException)(void *exceptionArg, Dz1Error *reason);
// GitsnOpenApiException
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiConnectionEventType
typedef enum GitsnOpenApiConnectionEventType
{
	GitsnOpenApiConnectionEventType_response_sent,
	GitsnOpenApiConnectionEventType_peer_closed,
	GitsnOpenApiConnectionEventType_server_idle_timeout,
	GitsnOpenApiConnectionEventType_connection_close,
	GitsnOpenApiConnectionEventType_transport_error,
	GitsnOpenApiConnectionEventType_max
} GitsnOpenApiConnectionEventType;

DZ1_CPPLINK str_t GitsnOpenApiConnectionEventTypeStrA(GitsnOpenApiConnectionEventType v);
DZ1_CPPLINK GitsnOpenApiConnectionEventType GitsnOpenApiConnectionEventTypeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t GitsnOpenApiConnectionEventTypeStrW(GitsnOpenApiConnectionEventType v);
DZ1_CPPLINK GitsnOpenApiConnectionEventType GitsnOpenApiConnectionEventTypeFromStrW(wstr_t str);
#ifdef UNICODE
#define GitsnOpenApiConnectionEventTypeStr GitsnOpenApiConnectionEventTypeStrW
#define GitsnOpenApiConnectionEventTypeFromStr GitsnOpenApiConnectionEventTypeFromStrW
#else // UNICODE
#define GitsnOpenApiConnectionEventTypeStr GitsnOpenApiConnectionEventTypeStrA
#define GitsnOpenApiConnectionEventTypeFromStr GitsnOpenApiConnectionEventTypeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define GitsnOpenApiConnectionEventTypeStr GitsnOpenApiConnectionEventTypeStrA
#define GitsnOpenApiConnectionEventTypeFromStr GitsnOpenApiConnectionEventTypeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiConnectionEventType *GitsnOpenApiConnectionEventType_new(GitsnOpenApiConnectionEventType *src, Dz1Error *err);
static __inline__ GitsnOpenApiConnectionEventType *GitsnOpenApiConnectionEventType_gen(Dz1Error *err) { GitsnOpenApiConnectionEventType v = GitsnOpenApiConnectionEventType_max; return GitsnOpenApiConnectionEventType_new(&v, err); }
static __inline__ void GitsnOpenApiConnectionEventType_del(GitsnOpenApiConnectionEventType *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void GitsnOpenApiConnectionEventType_delAndSetNull(void *ptr)
{
	GitsnOpenApiConnectionEventType **p = (GitsnOpenApiConnectionEventType **)ptr;
	if (p != NULL) { GitsnOpenApiConnectionEventType_del(*p); *p = NULL; }
}
// GitsnOpenApiConnectionEventType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiConnectionEvent
typedef struct GitsnOpenApiConnectionEvent
{
	GitsnOpenApiConnectionEventType		event_type;
	u32_t								session_id;
	u32_t								response_sequence;
	u32_t								configured_timeout_ms;
	u64_t								response_sent_monotonic_ms;
	u64_t								connection_closed_monotonic_ms;
	u64_t								elapsed_ms;
} GitsnOpenApiConnectionEvent;

DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiConnectionEvent *GitsnOpenApiConnectionEvent_new(GitsnOpenApiConnectionEventType event_type, 
																					 u32_t session_id, 
																					 u32_t response_sequence, 
																					 u32_t configured_timeout_ms, 
																					 u64_t response_sent_monotonic_ms, 
																					 u64_t connection_closed_monotonic_ms, 
																					 u64_t elapsed_ms, Dz1Error *err);
static __inline__ GitsnOpenApiConnectionEvent *GitsnOpenApiConnectionEvent_gen(Dz1Error *err) { return GitsnOpenApiConnectionEvent_new(GitsnOpenApiConnectionEventType_max, 0, 0, 0, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t GitsnOpenApiConnectionEvent_copy(GitsnOpenApiConnectionEvent *dst, GitsnOpenApiConnectionEvent *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiConnectionEvent *GitsnOpenApiConnectionEvent_clone(GitsnOpenApiConnectionEvent *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiConnectionEvent_purge(GitsnOpenApiConnectionEvent *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiConnectionEvent_del(GitsnOpenApiConnectionEvent *p);
static __inline__ void GitsnOpenApiConnectionEvent_delAndSetNull(void *ptr)
{
	GitsnOpenApiConnectionEvent **p = (GitsnOpenApiConnectionEvent **)ptr;
	if (p) { GitsnOpenApiConnectionEvent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiConnectionEvent_dump(GitsnOpenApiConnectionEvent *p, int tab);
// GitsnOpenApiConnectionEvent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiConnectionCallback
typedef void (*GitsnOpenApiConnectionCallback)(void *user_ptr, GitsnOpenApiConnectionEvent *event);
// GitsnOpenApiConnectionCallback
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiDataEntry
typedef struct GitsnOpenApiDataEntry
{
	str_t		key_utf8;
	str_t		value_utf8;
} GitsnOpenApiDataEntry;

DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiDataEntry *GitsnOpenApiDataEntry_new(str_t key_utf8, 
																		 str_t value_utf8, Dz1Error *err);
static __inline__ GitsnOpenApiDataEntry *GitsnOpenApiDataEntry_gen(Dz1Error *err) { return GitsnOpenApiDataEntry_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t GitsnOpenApiDataEntry_copy(GitsnOpenApiDataEntry *dst, GitsnOpenApiDataEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiDataEntry *GitsnOpenApiDataEntry_clone(GitsnOpenApiDataEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiDataEntry_purge(GitsnOpenApiDataEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiDataEntry_del(GitsnOpenApiDataEntry *p);
static __inline__ void GitsnOpenApiDataEntry_delAndSetNull(void *ptr)
{
	GitsnOpenApiDataEntry **p = (GitsnOpenApiDataEntry **)ptr;
	if (p) { GitsnOpenApiDataEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiDataEntry_dump(GitsnOpenApiDataEntry *p, int tab);
// GitsnOpenApiDataEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiDataList
typedef struct GitsnOpenApiDataList
{
	void *storage;
	unsigned int (*count)(struct GitsnOpenApiDataList *p);
	Dz1Error (*travel)(struct GitsnOpenApiDataList *p, Dz1Error (*func)(void *ptr, GitsnOpenApiDataEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct GitsnOpenApiDataList *p, Dz1Error (*func)(void *ptr, GitsnOpenApiDataEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct GitsnOpenApiDataList *p, Dz1Error (*func)(void *ptr, GitsnOpenApiDataEntry *entry), void *ptr);
	GitsnOpenApiDataEntry **(*get_array)(struct GitsnOpenApiDataList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct GitsnOpenApiDataList *p, GitsnOpenApiDataEntry *data);
	GitsnOpenApiDataEntry *(*extract)(struct GitsnOpenApiDataList *p, GitsnOpenApiDataEntry *ptr);
} GitsnOpenApiDataList;

DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiDataList *GitsnOpenApiDataList_new(Dz1Error *err);
static __inline__ GitsnOpenApiDataList *GitsnOpenApiDataList_gen(Dz1Error *err) { return GitsnOpenApiDataList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiDataList *GitsnOpenApiDataList_clone(GitsnOpenApiDataList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiDataList_purge(GitsnOpenApiDataList *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiDataList_del(GitsnOpenApiDataList *p);
static __inline__ void GitsnOpenApiDataList_delAndSetNull(void *ptr)
{
	GitsnOpenApiDataList **p = (GitsnOpenApiDataList **)ptr;
	if (p != NULL) { GitsnOpenApiDataList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiDataList_dump(GitsnOpenApiDataList *p, int tab);

// GitsnOpenApiDataList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiDataIndex
typedef struct GitsnOpenApiDataIndex
{
	void *storage;
	unsigned int (*count)(struct GitsnOpenApiDataIndex *p);
	Dz1Error (*travel)(struct GitsnOpenApiDataIndex *p, Dz1Error (*func)(void *ptr, GitsnOpenApiDataEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct GitsnOpenApiDataIndex *p, Dz1Error (*func)(void *ptr, GitsnOpenApiDataEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct GitsnOpenApiDataIndex *p, Dz1Error (*func)(void *ptr, GitsnOpenApiDataEntry *entry), void *ptr);
	GitsnOpenApiDataEntry **(*get_array)(struct GitsnOpenApiDataIndex *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct GitsnOpenApiDataIndex *p, GitsnOpenApiDataEntry *data);
	bool_t (*remove)(struct GitsnOpenApiDataIndex *p, GitsnOpenApiDataEntry *key);
	GitsnOpenApiDataEntry *(*extract)(struct GitsnOpenApiDataIndex *p, GitsnOpenApiDataEntry *key);
	GitsnOpenApiDataEntry *(*find)(struct GitsnOpenApiDataIndex *p, GitsnOpenApiDataEntry *key);
	int (*cmp)(GitsnOpenApiDataEntry *a, GitsnOpenApiDataEntry *b);
} GitsnOpenApiDataIndex;

DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiDataIndex *GitsnOpenApiDataIndex_new(Dz1Error *err);
static __inline__ GitsnOpenApiDataIndex *GitsnOpenApiDataIndex_gen(Dz1Error *err) { return GitsnOpenApiDataIndex_new(err); }
DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiDataIndex *GitsnOpenApiDataIndex_clone(GitsnOpenApiDataIndex *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiDataIndex_purge(GitsnOpenApiDataIndex *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiDataIndex_del(GitsnOpenApiDataIndex *p);
static __inline__ void GitsnOpenApiDataIndex_delAndSetNull(void *ptr)
{
	GitsnOpenApiDataIndex **p = (GitsnOpenApiDataIndex **)ptr;
	if (p != NULL) { GitsnOpenApiDataIndex_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiDataIndex_dump(GitsnOpenApiDataIndex *p, int tab);

// GitsnOpenApiDataIndex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiDatas
typedef struct GitsnOpenApiDatas
{
	GitsnOpenApiDataList		*storage;
	GitsnOpenApiDataIndex		*index;
} GitsnOpenApiDatas;

DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiDatas *GitsnOpenApiDatas_new(Dz1Error *err);
static __inline__ GitsnOpenApiDatas *GitsnOpenApiDatas_gen(Dz1Error *err) { return GitsnOpenApiDatas_new(err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t GitsnOpenApiDatas_copy(GitsnOpenApiDatas *dst, GitsnOpenApiDatas *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiDatas *GitsnOpenApiDatas_clone(GitsnOpenApiDatas *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiDatas_purge(GitsnOpenApiDatas *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiDatas_del(GitsnOpenApiDatas *p);
static __inline__ void GitsnOpenApiDatas_delAndSetNull(void *ptr)
{
	GitsnOpenApiDatas **p = (GitsnOpenApiDatas **)ptr;
	if (p) { GitsnOpenApiDatas_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiDatas_dump(GitsnOpenApiDatas *p, int tab);
// GitsnOpenApiDatas
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiResult
typedef struct GitsnOpenApiResult
{
	s32_t					 code;
	Dz1ElasticBuf			*data;
	Dz1Str					 content_type;
	GitsnOpenApiDatas		*headers;
	GitsnOpenApiDatas		*request_headers;
} GitsnOpenApiResult;

DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiResult *GitsnOpenApiResult_new(s32_t code, 
																   Dz1ElasticBuf *data, Dz1Error *err);
static __inline__ GitsnOpenApiResult *GitsnOpenApiResult_gen(Dz1Error *err) { return GitsnOpenApiResult_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiResult_purge(GitsnOpenApiResult *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiResult_del(GitsnOpenApiResult *p);
static __inline__ void GitsnOpenApiResult_delAndSetNull(void *ptr)
{
	GitsnOpenApiResult **p = (GitsnOpenApiResult **)ptr;
	if (p) { GitsnOpenApiResult_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiResult_dump(GitsnOpenApiResult *p, int tab);
// GitsnOpenApiResult
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiDownloadResult
typedef struct GitsnOpenApiDownloadResult
{
	s32_t		code;
	u64_t		bytes_written;
	Dz1Str		content_type;
	Dz1Str		sha256_hex;
} GitsnOpenApiDownloadResult;

DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiDownloadResult *GitsnOpenApiDownloadResult_new(s32_t code, 
																				   u64_t bytes_written, 
																				   Dz1Str content_type, 
																				   Dz1Str sha256_hex, Dz1Error *err);
static __inline__ GitsnOpenApiDownloadResult *GitsnOpenApiDownloadResult_gen(Dz1Error *err) { return GitsnOpenApiDownloadResult_new(0, 0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiDownloadResult_purge(GitsnOpenApiDownloadResult *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiDownloadResult_del(GitsnOpenApiDownloadResult *p);
static __inline__ void GitsnOpenApiDownloadResult_delAndSetNull(void *ptr)
{
	GitsnOpenApiDownloadResult **p = (GitsnOpenApiDownloadResult **)ptr;
	if (p) { GitsnOpenApiDownloadResult_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiDownloadResult_dump(GitsnOpenApiDownloadResult *p, int tab);
// GitsnOpenApiDownloadResult
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiHttpReqMethod
typedef enum GitsnOpenApiHttpReqMethod
{
	GitsnOpenApiHttpReqMethod_GET,
	GitsnOpenApiHttpReqMethod_POST,
	GitsnOpenApiHttpReqMethod_max
} GitsnOpenApiHttpReqMethod;

DZ1_CPPLINK str_t GitsnOpenApiHttpReqMethodStrA(GitsnOpenApiHttpReqMethod v);
DZ1_CPPLINK GitsnOpenApiHttpReqMethod GitsnOpenApiHttpReqMethodFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t GitsnOpenApiHttpReqMethodStrW(GitsnOpenApiHttpReqMethod v);
DZ1_CPPLINK GitsnOpenApiHttpReqMethod GitsnOpenApiHttpReqMethodFromStrW(wstr_t str);
#ifdef UNICODE
#define GitsnOpenApiHttpReqMethodStr GitsnOpenApiHttpReqMethodStrW
#define GitsnOpenApiHttpReqMethodFromStr GitsnOpenApiHttpReqMethodFromStrW
#else // UNICODE
#define GitsnOpenApiHttpReqMethodStr GitsnOpenApiHttpReqMethodStrA
#define GitsnOpenApiHttpReqMethodFromStr GitsnOpenApiHttpReqMethodFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define GitsnOpenApiHttpReqMethodStr GitsnOpenApiHttpReqMethodStrA
#define GitsnOpenApiHttpReqMethodFromStr GitsnOpenApiHttpReqMethodFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiHttpReqMethod *GitsnOpenApiHttpReqMethod_new(GitsnOpenApiHttpReqMethod *src, Dz1Error *err);
static __inline__ GitsnOpenApiHttpReqMethod *GitsnOpenApiHttpReqMethod_gen(Dz1Error *err) { GitsnOpenApiHttpReqMethod v = GitsnOpenApiHttpReqMethod_max; return GitsnOpenApiHttpReqMethod_new(&v, err); }
static __inline__ void GitsnOpenApiHttpReqMethod_del(GitsnOpenApiHttpReqMethod *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void GitsnOpenApiHttpReqMethod_delAndSetNull(void *ptr)
{
	GitsnOpenApiHttpReqMethod **p = (GitsnOpenApiHttpReqMethod **)ptr;
	if (p != NULL) { GitsnOpenApiHttpReqMethod_del(*p); *p = NULL; }
}
// GitsnOpenApiHttpReqMethod
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiHttpReq
typedef struct GitsnOpenApiHttpReq
{
	GitsnOpenApiHttpReqMethod		 method;
	str_t							 target_utf8;
	GitsnOpenApiDatas				*args;
	str_t							 prot;
	u16_t							 ver_maj;
	u16_t							 ver_min;
	GitsnOpenApiDatas				*header;
	Dz1Binary						*body;
} GitsnOpenApiHttpReq;

DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiHttpReq *GitsnOpenApiHttpReq_new(GitsnOpenApiHttpReqMethod method, 
																	 str_t target_utf8, 
																	 str_t prot, 
																	 u16_t ver_maj, 
																	 u16_t ver_min, 
																	 GitsnOpenApiDatas *header, Dz1Error *err);
static __inline__ GitsnOpenApiHttpReq *GitsnOpenApiHttpReq_gen(Dz1Error *err) { return GitsnOpenApiHttpReq_new(GitsnOpenApiHttpReqMethod_max, NULL, NULL, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t GitsnOpenApiHttpReq_copy(GitsnOpenApiHttpReq *dst, GitsnOpenApiHttpReq *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiHttpReq *GitsnOpenApiHttpReq_clone(GitsnOpenApiHttpReq *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiHttpReq_purge(GitsnOpenApiHttpReq *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiHttpReq_del(GitsnOpenApiHttpReq *p);
static __inline__ void GitsnOpenApiHttpReq_delAndSetNull(void *ptr)
{
	GitsnOpenApiHttpReq **p = (GitsnOpenApiHttpReq **)ptr;
	if (p) { GitsnOpenApiHttpReq_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiHttpReq_dump(GitsnOpenApiHttpReq *p, int tab);
// GitsnOpenApiHttpReq
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiHttpRsp
typedef struct GitsnOpenApiHttpRsp
{
	str_t					 prot;
	u16_t					 ver_maj;
	u16_t					 ver_min;
	u32_t					 code;
	str_t					 code_txt_utf8;
	GitsnOpenApiDatas		*header;
	Dz1ElasticBuf			*body;
} GitsnOpenApiHttpRsp;

DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiHttpRsp *GitsnOpenApiHttpRsp_new(str_t prot, 
																	 u16_t ver_maj, 
																	 u16_t ver_min, 
																	 u32_t code, 
																	 str_t code_txt_utf8, 
																	 GitsnOpenApiDatas *header, 
																	 Dz1ElasticBuf *body, Dz1Error *err);
static __inline__ GitsnOpenApiHttpRsp *GitsnOpenApiHttpRsp_gen(Dz1Error *err) { return GitsnOpenApiHttpRsp_new(NULL, 0, 0, 0, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t GitsnOpenApiHttpRsp_copy(GitsnOpenApiHttpRsp *dst, GitsnOpenApiHttpRsp *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiHttpRsp *GitsnOpenApiHttpRsp_clone(GitsnOpenApiHttpRsp *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiHttpRsp_purge(GitsnOpenApiHttpRsp *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiHttpRsp_del(GitsnOpenApiHttpRsp *p);
static __inline__ void GitsnOpenApiHttpRsp_delAndSetNull(void *ptr)
{
	GitsnOpenApiHttpRsp **p = (GitsnOpenApiHttpRsp **)ptr;
	if (p) { GitsnOpenApiHttpRsp_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiHttpRsp_dump(GitsnOpenApiHttpRsp *p, int tab);
// GitsnOpenApiHttpRsp
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiHttpMsgPresent
typedef enum GitsnOpenApiHttpMsgPresent
{
	GitsnOpenApiHttpMsgPresent_req,
	GitsnOpenApiHttpMsgPresent_rsp,
	GitsnOpenApiHttpMsgPresent_ws_payload,
	GitsnOpenApiHttpMsgPresent_max
} GitsnOpenApiHttpMsgPresent;

DZ1_CPPLINK str_t GitsnOpenApiHttpMsgPresentStrA(GitsnOpenApiHttpMsgPresent v);
DZ1_CPPLINK GitsnOpenApiHttpMsgPresent GitsnOpenApiHttpMsgPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t GitsnOpenApiHttpMsgPresentStrW(GitsnOpenApiHttpMsgPresent v);
DZ1_CPPLINK GitsnOpenApiHttpMsgPresent GitsnOpenApiHttpMsgPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define GitsnOpenApiHttpMsgPresentStr GitsnOpenApiHttpMsgPresentStrW
#define GitsnOpenApiHttpMsgPresentFromStr GitsnOpenApiHttpMsgPresentFromStrW
#else // UNICODE
#define GitsnOpenApiHttpMsgPresentStr GitsnOpenApiHttpMsgPresentStrA
#define GitsnOpenApiHttpMsgPresentFromStr GitsnOpenApiHttpMsgPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define GitsnOpenApiHttpMsgPresentStr GitsnOpenApiHttpMsgPresentStrA
#define GitsnOpenApiHttpMsgPresentFromStr GitsnOpenApiHttpMsgPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiHttpMsgPresent *GitsnOpenApiHttpMsgPresent_new(GitsnOpenApiHttpMsgPresent *src, Dz1Error *err);
static __inline__ GitsnOpenApiHttpMsgPresent *GitsnOpenApiHttpMsgPresent_gen(Dz1Error *err) { GitsnOpenApiHttpMsgPresent v = GitsnOpenApiHttpMsgPresent_max; return GitsnOpenApiHttpMsgPresent_new(&v, err); }
#define GitsnOpenApiHttpMsgPresent_clone             GitsnOpenApiHttpMsgPresent_new
static __inline__ void GitsnOpenApiHttpMsgPresent_del(GitsnOpenApiHttpMsgPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void GitsnOpenApiHttpMsgPresent_delAndSetNull(void *ptr)
{
	GitsnOpenApiHttpMsgPresent **p = (GitsnOpenApiHttpMsgPresent **)ptr;
	if (p != NULL) { GitsnOpenApiHttpMsgPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiHttpMsgPresent_dump(GitsnOpenApiHttpMsgPresent *v, int tab);
// GitsnOpenApiHttpMsgPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiHttpMsg
typedef struct GitsnOpenApiHttpMsg
{
	GitsnOpenApiHttpMsgPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		GitsnOpenApiHttpReq		*req;
		GitsnOpenApiHttpRsp		*rsp;
		Dz1Binary				*ws_payload;
	} x;
} GitsnOpenApiHttpMsg;

DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiHttpMsg *GitsnOpenApiHttpMsg_new(GitsnOpenApiHttpMsgPresent present, void *ptr, Dz1Error *err);
static __inline__ GitsnOpenApiHttpMsg *GitsnOpenApiHttpMsg_gen(Dz1Error *err) { return GitsnOpenApiHttpMsg_new(GitsnOpenApiHttpMsgPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  GitsnOpenApiHttpMsg_copy(GitsnOpenApiHttpMsg *dst, GitsnOpenApiHttpMsg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiHttpMsg *GitsnOpenApiHttpMsg_clone(GitsnOpenApiHttpMsg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiHttpMsg_purge(GitsnOpenApiHttpMsg *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiHttpMsg_del(GitsnOpenApiHttpMsg *p);
static __inline__ void GitsnOpenApiHttpMsg_delAndSetNull(void *ptr)
{
	GitsnOpenApiHttpMsg **p = (GitsnOpenApiHttpMsg **)ptr;
	if (p != NULL) { GitsnOpenApiHttpMsg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiHttpMsg_dump(GitsnOpenApiHttpMsg *p, int tab);
// GitsnOpenApiHttpMsg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiMsg
typedef struct GitsnOpenApiMsg
{
	u32_t					 session_id;
	GitsnOpenApiHttpMsg		*ctx;
} GitsnOpenApiMsg;

DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiMsg *GitsnOpenApiMsg_new(u32_t session_id, 
															 GitsnOpenApiHttpMsg *ctx, Dz1Error *err);
static __inline__ GitsnOpenApiMsg *GitsnOpenApiMsg_gen(Dz1Error *err) { return GitsnOpenApiMsg_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t GitsnOpenApiMsg_copy(GitsnOpenApiMsg *dst, GitsnOpenApiMsg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT GitsnOpenApiMsg *GitsnOpenApiMsg_clone(GitsnOpenApiMsg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiMsg_purge(GitsnOpenApiMsg *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiMsg_del(GitsnOpenApiMsg *p);
static __inline__ void GitsnOpenApiMsg_delAndSetNull(void *ptr)
{
	GitsnOpenApiMsg **p = (GitsnOpenApiMsg **)ptr;
	if (p) { GitsnOpenApiMsg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnOpenApiMsg_dump(GitsnOpenApiMsg *p, int tab);
// GitsnOpenApiMsg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GitsnOpenApiCallback
typedef void (*GitsnOpenApiCallback)(void *user_ptr, GitsnOpenApiMsg **msg);
// GitsnOpenApiCallback
////////////////////////////////////////////////////////////////////////////////

#endif

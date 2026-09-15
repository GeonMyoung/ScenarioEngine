#ifndef _DZ1_TDC_DZ1_WEB_SOCKET_DEF_H_
#define _DZ1_TDC_DZ1_WEB_SOCKET_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "Dz1SockUtilDef.h"
#include "dz1_io_stream_support.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSockOpCode
typedef enum Dz1WebSockOpCode
{
	Dz1WebSockOpCode_unknown = 0,
	Dz1WebSockOpCode_text = 1,
	Dz1WebSockOpCode_binary = 2,
	Dz1WebSockOpCode_terminate = 8,
	Dz1WebSockOpCode_ping = 9,
	Dz1WebSockOpCode_pong = 10,
	Dz1WebSockOpCode_max
} Dz1WebSockOpCode;

DZ1_CPPLINK str_t Dz1WebSockOpCodeStrA(Dz1WebSockOpCode v);
DZ1_CPPLINK Dz1WebSockOpCode Dz1WebSockOpCodeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1WebSockOpCodeStrW(Dz1WebSockOpCode v);
DZ1_CPPLINK Dz1WebSockOpCode Dz1WebSockOpCodeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1WebSockOpCodeStr Dz1WebSockOpCodeStrW
#define Dz1WebSockOpCodeFromStr Dz1WebSockOpCodeFromStrW
#else // UNICODE
#define Dz1WebSockOpCodeStr Dz1WebSockOpCodeStrA
#define Dz1WebSockOpCodeFromStr Dz1WebSockOpCodeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1WebSockOpCodeStr Dz1WebSockOpCodeStrA
#define Dz1WebSockOpCodeFromStr Dz1WebSockOpCodeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1WebSockOpCode *Dz1WebSockOpCode_new(Dz1WebSockOpCode *src, Dz1Error *err);
static __inline__ Dz1WebSockOpCode *Dz1WebSockOpCode_gen(Dz1Error *err) { Dz1WebSockOpCode v = Dz1WebSockOpCode_max; return Dz1WebSockOpCode_new(&v, err); }
static __inline__ void Dz1WebSockOpCode_del(Dz1WebSockOpCode *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1WebSockOpCode_delAndSetNull(void *ptr)
{
	Dz1WebSockOpCode **p = (Dz1WebSockOpCode **)ptr;
	if (p != NULL) { Dz1WebSockOpCode_del(*p); *p = NULL; }
}
// Dz1WebSockOpCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSockMsg
typedef struct Dz1WebSockMsg
{
	Dz1WebSockOpCode	 op;
	Dz1Binary			*payload;
} Dz1WebSockMsg;

DZ1_CPPLINK DZ1_DLLPORT Dz1WebSockMsg *Dz1WebSockMsg_new(Dz1WebSockOpCode op, 
														 Dz1Binary *payload, Dz1Error *err);
static __inline__ Dz1WebSockMsg *Dz1WebSockMsg_gen(Dz1Error *err) { return Dz1WebSockMsg_new(Dz1WebSockOpCode_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSockMsg_purge(Dz1WebSockMsg *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSockMsg_del(Dz1WebSockMsg *p);
static __inline__ void Dz1WebSockMsg_delAndSetNull(void *ptr)
{
	Dz1WebSockMsg **p = (Dz1WebSockMsg **)ptr;
	if (p) { Dz1WebSockMsg_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSockMsgA_dump(Dz1WebSockMsg *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSockMsgW_dump(Dz1WebSockMsg *p, int tab);
#ifdef UNICODE
#define Dz1WebSockMsg_dump Dz1WebSockMsgW_dump
#else //  UNICODE
#define Dz1WebSockMsg_dump Dz1WebSockMsgA_dump
#endif //  UNICODE
static __inline__ void Dz1WebSockMsgX_dump(Dz1WebSockMsg *p, int tab) { DZ1_DUMP(Dz1WebSockMsg, p, tab); }
#else // UNIX_SYSTEM
#define Dz1WebSockMsg_dump Dz1WebSockMsgA_dump
#define Dz1WebSockMsgX_dump Dz1WebSockMsgA_dump
#endif // UNIX_SYSTEM
// Dz1WebSockMsg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSockMsgList
typedef struct Dz1WebSockMsgList
{
	void *storage;
	unsigned int (*count)(struct Dz1WebSockMsgList *p);
	Dz1Error (*travel)(struct Dz1WebSockMsgList *p, Dz1Error (*func)(void *ptr, Dz1WebSockMsg *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1WebSockMsgList *p, Dz1Error (*func)(void *ptr, Dz1WebSockMsg *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1WebSockMsgList *p, Dz1Error (*func)(void *ptr, Dz1WebSockMsg *entry), void *ptr);
	Dz1WebSockMsg **(*get_array)(struct Dz1WebSockMsgList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1WebSockMsgList *p, Dz1WebSockMsg *data);
	Dz1WebSockMsg *(*extract)(struct Dz1WebSockMsgList *p, Dz1WebSockMsg *ptr);
} Dz1WebSockMsgList;

DZ1_CPPLINK DZ1_DLLPORT Dz1WebSockMsgList *Dz1WebSockMsgList_new(Dz1Error *err);
static __inline__ Dz1WebSockMsgList *Dz1WebSockMsgList_gen(Dz1Error *err) { return Dz1WebSockMsgList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSockMsgList_purge(Dz1WebSockMsgList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSockMsgList_del(Dz1WebSockMsgList *p);
static __inline__ void Dz1WebSockMsgList_delAndSetNull(void *ptr)
{
	Dz1WebSockMsgList **p = (Dz1WebSockMsgList **)ptr;
	if (p != NULL) { Dz1WebSockMsgList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSockMsgListA_dump(Dz1WebSockMsgList *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSockMsgListW_dump(Dz1WebSockMsgList *p, int tab);
#ifdef UNICODE
#define Dz1WebSockMsgList_dump Dz1WebSockMsgListW_dump
#else //  UNICODE
#define Dz1WebSockMsgList_dump Dz1WebSockMsgListA_dump
#endif //  UNICODE
static __inline__ void Dz1WebSockMsgListX_dump(Dz1WebSockMsgList *p, int tab) { DZ1_DUMP(Dz1WebSockMsgList, p, tab); }
#else // UNIX_SYSTEM
#define Dz1WebSockMsgList_dump Dz1WebSockMsgListA_dump
#define Dz1WebSockMsgListX_dump Dz1WebSockMsgListA_dump
#endif // UNIX_SYSTEM

// Dz1WebSockMsgList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSocketScheme
typedef enum Dz1WebSocketScheme
{
	Dz1WebSocketScheme_ws,
	Dz1WebSocketScheme_wss,
	Dz1WebSocketScheme_max
} Dz1WebSocketScheme;

DZ1_CPPLINK str_t Dz1WebSocketSchemeStrA(Dz1WebSocketScheme v);
DZ1_CPPLINK Dz1WebSocketScheme Dz1WebSocketSchemeFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1WebSocketSchemeStrW(Dz1WebSocketScheme v);
DZ1_CPPLINK Dz1WebSocketScheme Dz1WebSocketSchemeFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1WebSocketSchemeStr Dz1WebSocketSchemeStrW
#define Dz1WebSocketSchemeFromStr Dz1WebSocketSchemeFromStrW
#else // UNICODE
#define Dz1WebSocketSchemeStr Dz1WebSocketSchemeStrA
#define Dz1WebSocketSchemeFromStr Dz1WebSocketSchemeFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1WebSocketSchemeStr Dz1WebSocketSchemeStrA
#define Dz1WebSocketSchemeFromStr Dz1WebSocketSchemeFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1WebSocketScheme *Dz1WebSocketScheme_new(Dz1WebSocketScheme *src, Dz1Error *err);
static __inline__ Dz1WebSocketScheme *Dz1WebSocketScheme_gen(Dz1Error *err) { Dz1WebSocketScheme v = Dz1WebSocketScheme_max; return Dz1WebSocketScheme_new(&v, err); }
static __inline__ void Dz1WebSocketScheme_del(Dz1WebSocketScheme *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1WebSocketScheme_delAndSetNull(void *ptr)
{
	Dz1WebSocketScheme **p = (Dz1WebSocketScheme **)ptr;
	if (p != NULL) { Dz1WebSocketScheme_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketSchemeA_dump(Dz1WebSocketScheme *v, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketSchemeW_dump(Dz1WebSocketScheme *v, int tab);
#ifdef UNICODE
#define Dz1WebSocketScheme_dump Dz1WebSocketSchemeW_dump
#else //  UNICODE
#define Dz1WebSocketScheme_dump Dz1WebSocketSchemeA_dump
#endif //  UNICODE
static __inline__ void Dz1WebSocketSchemeX_dump(Dz1WebSocketScheme *p, int tab) { DZ1_DUMP(Dz1WebSocketScheme, p, tab); }
#else // UNIX_SYSTEM
#define Dz1WebSocketScheme_dump Dz1WebSocketSchemeA_dump
#define Dz1WebSocketSchemeX_dump Dz1WebSocketSchemeA_dump
#endif // UNIX_SYSTEM
// Dz1WebSocketScheme
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSocketState
typedef enum Dz1WebSocketState
{
	Dz1WebSocketState_init,
	Dz1WebSocketState_requested,
	Dz1WebSocketState_established,
	Dz1WebSocketState_closing,
	Dz1WebSocketState_closed,
	Dz1WebSocketState_max
} Dz1WebSocketState;

DZ1_CPPLINK str_t Dz1WebSocketStateStrA(Dz1WebSocketState v);
DZ1_CPPLINK Dz1WebSocketState Dz1WebSocketStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1WebSocketStateStrW(Dz1WebSocketState v);
DZ1_CPPLINK Dz1WebSocketState Dz1WebSocketStateFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1WebSocketStateStr Dz1WebSocketStateStrW
#define Dz1WebSocketStateFromStr Dz1WebSocketStateFromStrW
#else // UNICODE
#define Dz1WebSocketStateStr Dz1WebSocketStateStrA
#define Dz1WebSocketStateFromStr Dz1WebSocketStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1WebSocketStateStr Dz1WebSocketStateStrA
#define Dz1WebSocketStateFromStr Dz1WebSocketStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1WebSocketState *Dz1WebSocketState_new(Dz1WebSocketState *src, Dz1Error *err);
static __inline__ Dz1WebSocketState *Dz1WebSocketState_gen(Dz1Error *err) { Dz1WebSocketState v = Dz1WebSocketState_max; return Dz1WebSocketState_new(&v, err); }
static __inline__ void Dz1WebSocketState_del(Dz1WebSocketState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1WebSocketState_delAndSetNull(void *ptr)
{
	Dz1WebSocketState **p = (Dz1WebSocketState **)ptr;
	if (p != NULL) { Dz1WebSocketState_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketStateA_dump(Dz1WebSocketState *v, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketStateW_dump(Dz1WebSocketState *v, int tab);
#ifdef UNICODE
#define Dz1WebSocketState_dump Dz1WebSocketStateW_dump
#else //  UNICODE
#define Dz1WebSocketState_dump Dz1WebSocketStateA_dump
#endif //  UNICODE
static __inline__ void Dz1WebSocketStateX_dump(Dz1WebSocketState *p, int tab) { DZ1_DUMP(Dz1WebSocketState, p, tab); }
#else // UNIX_SYSTEM
#define Dz1WebSocketState_dump Dz1WebSocketStateA_dump
#define Dz1WebSocketStateX_dump Dz1WebSocketStateA_dump
#endif // UNIX_SYSTEM
// Dz1WebSocketState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSocketAuth
typedef struct Dz1WebSocketAuth
{
	Dz1Binary		*key_bin;
	Dz1Binary		*cnf_bin;
} Dz1WebSocketAuth;

DZ1_CPPLINK DZ1_DLLPORT Dz1WebSocketAuth *Dz1WebSocketAuth_new(Dz1Binary *key_bin, 
															   Dz1Binary *cnf_bin, Dz1Error *err);
static __inline__ Dz1WebSocketAuth *Dz1WebSocketAuth_gen(Dz1Error *err) { return Dz1WebSocketAuth_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketAuth_purge(Dz1WebSocketAuth *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketAuth_del(Dz1WebSocketAuth *p);
static __inline__ void Dz1WebSocketAuth_delAndSetNull(void *ptr)
{
	Dz1WebSocketAuth **p = (Dz1WebSocketAuth **)ptr;
	if (p) { Dz1WebSocketAuth_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketAuthA_dump(Dz1WebSocketAuth *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketAuthW_dump(Dz1WebSocketAuth *p, int tab);
#ifdef UNICODE
#define Dz1WebSocketAuth_dump Dz1WebSocketAuthW_dump
#else //  UNICODE
#define Dz1WebSocketAuth_dump Dz1WebSocketAuthA_dump
#endif //  UNICODE
static __inline__ void Dz1WebSocketAuthX_dump(Dz1WebSocketAuth *p, int tab) { DZ1_DUMP(Dz1WebSocketAuth, p, tab); }
#else // UNIX_SYSTEM
#define Dz1WebSocketAuth_dump Dz1WebSocketAuthA_dump
#define Dz1WebSocketAuthX_dump Dz1WebSocketAuthA_dump
#endif // UNIX_SYSTEM
// Dz1WebSocketAuth
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSockDecFrame
typedef struct Dz1WebSockDecFrame
{
	bool_t				 is_fin;
	Dz1WebSockOpCode	 op_code;
	u64_t				 payload_len;
	u32_t				*mask;
	Dz1ElasticBuf		*payload;
} Dz1WebSockDecFrame;

DZ1_CPPLINK DZ1_DLLPORT Dz1WebSockDecFrame *Dz1WebSockDecFrame_new(bool_t is_fin, 
																   Dz1WebSockOpCode op_code, 
																   u64_t payload_len, 
																   u32_t *mask, 
																   Dz1ElasticBuf *payload, Dz1Error *err);
static __inline__ Dz1WebSockDecFrame *Dz1WebSockDecFrame_gen(Dz1Error *err) { return Dz1WebSockDecFrame_new(0, Dz1WebSockOpCode_max, 0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSockDecFrame_purge(Dz1WebSockDecFrame *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSockDecFrame_del(Dz1WebSockDecFrame *p);
static __inline__ void Dz1WebSockDecFrame_delAndSetNull(void *ptr)
{
	Dz1WebSockDecFrame **p = (Dz1WebSockDecFrame **)ptr;
	if (p) { Dz1WebSockDecFrame_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSockDecFrameA_dump(Dz1WebSockDecFrame *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSockDecFrameW_dump(Dz1WebSockDecFrame *p, int tab);
#ifdef UNICODE
#define Dz1WebSockDecFrame_dump Dz1WebSockDecFrameW_dump
#else //  UNICODE
#define Dz1WebSockDecFrame_dump Dz1WebSockDecFrameA_dump
#endif //  UNICODE
static __inline__ void Dz1WebSockDecFrameX_dump(Dz1WebSockDecFrame *p, int tab) { DZ1_DUMP(Dz1WebSockDecFrame, p, tab); }
#else // UNIX_SYSTEM
#define Dz1WebSockDecFrame_dump Dz1WebSockDecFrameA_dump
#define Dz1WebSockDecFrameX_dump Dz1WebSockDecFrameA_dump
#endif // UNIX_SYSTEM
// Dz1WebSockDecFrame
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSockDecFrameList
typedef struct Dz1WebSockDecFrameList
{
	void *storage;
	unsigned int (*count)(struct Dz1WebSockDecFrameList *p);
	Dz1Error (*travel)(struct Dz1WebSockDecFrameList *p, Dz1Error (*func)(void *ptr, Dz1WebSockDecFrame *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1WebSockDecFrameList *p, Dz1Error (*func)(void *ptr, Dz1WebSockDecFrame *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1WebSockDecFrameList *p, Dz1Error (*func)(void *ptr, Dz1WebSockDecFrame *entry), void *ptr);
	Dz1WebSockDecFrame **(*get_array)(struct Dz1WebSockDecFrameList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1WebSockDecFrameList *p, Dz1WebSockDecFrame *data);
	Dz1WebSockDecFrame *(*extract)(struct Dz1WebSockDecFrameList *p, Dz1WebSockDecFrame *ptr);
} Dz1WebSockDecFrameList;

DZ1_CPPLINK DZ1_DLLPORT Dz1WebSockDecFrameList *Dz1WebSockDecFrameList_new(Dz1Error *err);
static __inline__ Dz1WebSockDecFrameList *Dz1WebSockDecFrameList_gen(Dz1Error *err) { return Dz1WebSockDecFrameList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSockDecFrameList_purge(Dz1WebSockDecFrameList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSockDecFrameList_del(Dz1WebSockDecFrameList *p);
static __inline__ void Dz1WebSockDecFrameList_delAndSetNull(void *ptr)
{
	Dz1WebSockDecFrameList **p = (Dz1WebSockDecFrameList **)ptr;
	if (p != NULL) { Dz1WebSockDecFrameList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSockDecFrameListA_dump(Dz1WebSockDecFrameList *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSockDecFrameListW_dump(Dz1WebSockDecFrameList *p, int tab);
#ifdef UNICODE
#define Dz1WebSockDecFrameList_dump Dz1WebSockDecFrameListW_dump
#else //  UNICODE
#define Dz1WebSockDecFrameList_dump Dz1WebSockDecFrameListA_dump
#endif //  UNICODE
static __inline__ void Dz1WebSockDecFrameListX_dump(Dz1WebSockDecFrameList *p, int tab) { DZ1_DUMP(Dz1WebSockDecFrameList, p, tab); }
#else // UNIX_SYSTEM
#define Dz1WebSockDecFrameList_dump Dz1WebSockDecFrameListA_dump
#define Dz1WebSockDecFrameListX_dump Dz1WebSockDecFrameListA_dump
#endif // UNIX_SYSTEM

// Dz1WebSockDecFrameList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSockDecState
typedef enum Dz1WebSockDecState
{
	Dz1WebSockDecState_fin_opcode,
	Dz1WebSockDecState_mask_len0,
	Dz1WebSockDecState_ext_len2,
	Dz1WebSockDecState_ext_len8,
	Dz1WebSockDecState_mask,
	Dz1WebSockDecState_payload,
	Dz1WebSockDecState_max
} Dz1WebSockDecState;

DZ1_CPPLINK str_t Dz1WebSockDecStateStrA(Dz1WebSockDecState v);
DZ1_CPPLINK Dz1WebSockDecState Dz1WebSockDecStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1WebSockDecStateStrW(Dz1WebSockDecState v);
DZ1_CPPLINK Dz1WebSockDecState Dz1WebSockDecStateFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1WebSockDecStateStr Dz1WebSockDecStateStrW
#define Dz1WebSockDecStateFromStr Dz1WebSockDecStateFromStrW
#else // UNICODE
#define Dz1WebSockDecStateStr Dz1WebSockDecStateStrA
#define Dz1WebSockDecStateFromStr Dz1WebSockDecStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1WebSockDecStateStr Dz1WebSockDecStateStrA
#define Dz1WebSockDecStateFromStr Dz1WebSockDecStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1WebSockDecState *Dz1WebSockDecState_new(Dz1WebSockDecState *src, Dz1Error *err);
static __inline__ Dz1WebSockDecState *Dz1WebSockDecState_gen(Dz1Error *err) { Dz1WebSockDecState v = Dz1WebSockDecState_max; return Dz1WebSockDecState_new(&v, err); }
static __inline__ void Dz1WebSockDecState_del(Dz1WebSockDecState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1WebSockDecState_delAndSetNull(void *ptr)
{
	Dz1WebSockDecState **p = (Dz1WebSockDecState **)ptr;
	if (p != NULL) { Dz1WebSockDecState_del(*p); *p = NULL; }
}
// Dz1WebSockDecState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSockDecCtx
typedef struct Dz1WebSockDecCtx
{
	Dz1WebSockDecState			 state;
	u64_t						 len_remain;
	Dz1WebSockDecFrame			*wip;
	Dz1WebSockDecFrameList		*wip_list;
	u32_t						 mask_idx;
} Dz1WebSockDecCtx;

DZ1_CPPLINK DZ1_DLLPORT Dz1WebSockDecCtx *Dz1WebSockDecCtx_new(Dz1WebSockDecState state, 
															   u64_t len_remain, 
															   Dz1WebSockDecFrame *wip, Dz1Error *err);
static __inline__ Dz1WebSockDecCtx *Dz1WebSockDecCtx_gen(Dz1Error *err) { return Dz1WebSockDecCtx_new(Dz1WebSockDecState_max, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSockDecCtx_purge(Dz1WebSockDecCtx *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSockDecCtx_del(Dz1WebSockDecCtx *p);
static __inline__ void Dz1WebSockDecCtx_delAndSetNull(void *ptr)
{
	Dz1WebSockDecCtx **p = (Dz1WebSockDecCtx **)ptr;
	if (p) { Dz1WebSockDecCtx_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSockDecCtxA_dump(Dz1WebSockDecCtx *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSockDecCtxW_dump(Dz1WebSockDecCtx *p, int tab);
#ifdef UNICODE
#define Dz1WebSockDecCtx_dump Dz1WebSockDecCtxW_dump
#else //  UNICODE
#define Dz1WebSockDecCtx_dump Dz1WebSockDecCtxA_dump
#endif //  UNICODE
static __inline__ void Dz1WebSockDecCtxX_dump(Dz1WebSockDecCtx *p, int tab) { DZ1_DUMP(Dz1WebSockDecCtx, p, tab); }
#else // UNIX_SYSTEM
#define Dz1WebSockDecCtx_dump Dz1WebSockDecCtxA_dump
#define Dz1WebSockDecCtxX_dump Dz1WebSockDecCtxA_dump
#endif // UNIX_SYSTEM
// Dz1WebSockDecCtx
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSocket
typedef struct Dz1WebSocket
{
	Dz1SockAddr				*peer;
	Dz1SockAddr				*local;
	Dz1TcpClientSocket		*sock;
	Dz1SockUtilTxFifo		*tx_fifo;
	Dz1WebSocketState		 state;
	Dz1WebSocketAuth		*auth;
	bool_t					 masking;
	Dz1WebSockDecCtx		*ctx;
	Dz1WebSockMsgList		*msgs;
} Dz1WebSocket;

DZ1_CPPLINK DZ1_DLLPORT Dz1WebSocket *Dz1WebSocket_new(Dz1SockAddr *peer, 
													   Dz1SockAddr *local, 
													   Dz1TcpClientSocket *sock, 
													   Dz1SockUtilTxFifo *tx_fifo, 
													   bool_t masking, 
													   Dz1WebSockDecCtx *ctx, Dz1Error *err);
static __inline__ Dz1WebSocket *Dz1WebSocket_gen(Dz1Error *err) { return Dz1WebSocket_new(NULL, NULL, NULL, NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocket_purge(Dz1WebSocket *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocket_del(Dz1WebSocket *p);
static __inline__ void Dz1WebSocket_delAndSetNull(void *ptr)
{
	Dz1WebSocket **p = (Dz1WebSocket **)ptr;
	if (p) { Dz1WebSocket_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketA_dump(Dz1WebSocket *p, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketW_dump(Dz1WebSocket *p, int tab);
#ifdef UNICODE
#define Dz1WebSocket_dump Dz1WebSocketW_dump
#else //  UNICODE
#define Dz1WebSocket_dump Dz1WebSocketA_dump
#endif //  UNICODE
static __inline__ void Dz1WebSocketX_dump(Dz1WebSocket *p, int tab) { DZ1_DUMP(Dz1WebSocket, p, tab); }
#else // UNIX_SYSTEM
#define Dz1WebSocket_dump Dz1WebSocketA_dump
#define Dz1WebSocketX_dump Dz1WebSocketA_dump
#endif // UNIX_SYSTEM
// Dz1WebSocket
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSocketCloseReason
typedef enum Dz1WebSocketCloseReason
{
	Dz1WebSocketCloseReason_normal_close = 1000,
	Dz1WebSocketCloseReason_process_shutdown,
	Dz1WebSocketCloseReason_protocol_error,
	Dz1WebSocketCloseReason_unknown_context,
	Dz1WebSocketCloseReason_max
} Dz1WebSocketCloseReason;

DZ1_CPPLINK str_t Dz1WebSocketCloseReasonStrA(Dz1WebSocketCloseReason v);
DZ1_CPPLINK Dz1WebSocketCloseReason Dz1WebSocketCloseReasonFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1WebSocketCloseReasonStrW(Dz1WebSocketCloseReason v);
DZ1_CPPLINK Dz1WebSocketCloseReason Dz1WebSocketCloseReasonFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1WebSocketCloseReasonStr Dz1WebSocketCloseReasonStrW
#define Dz1WebSocketCloseReasonFromStr Dz1WebSocketCloseReasonFromStrW
#else // UNICODE
#define Dz1WebSocketCloseReasonStr Dz1WebSocketCloseReasonStrA
#define Dz1WebSocketCloseReasonFromStr Dz1WebSocketCloseReasonFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1WebSocketCloseReasonStr Dz1WebSocketCloseReasonStrA
#define Dz1WebSocketCloseReasonFromStr Dz1WebSocketCloseReasonFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1WebSocketCloseReason *Dz1WebSocketCloseReason_new(Dz1WebSocketCloseReason *src, Dz1Error *err);
static __inline__ Dz1WebSocketCloseReason *Dz1WebSocketCloseReason_gen(Dz1Error *err) { Dz1WebSocketCloseReason v = Dz1WebSocketCloseReason_max; return Dz1WebSocketCloseReason_new(&v, err); }
static __inline__ void Dz1WebSocketCloseReason_del(Dz1WebSocketCloseReason *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1WebSocketCloseReason_delAndSetNull(void *ptr)
{
	Dz1WebSocketCloseReason **p = (Dz1WebSocketCloseReason **)ptr;
	if (p != NULL) { Dz1WebSocketCloseReason_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketCloseReasonA_dump(Dz1WebSocketCloseReason *v, int tab);
#ifndef UNIX_SYSTEM // dump mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketCloseReasonW_dump(Dz1WebSocketCloseReason *v, int tab);
#ifdef UNICODE
#define Dz1WebSocketCloseReason_dump Dz1WebSocketCloseReasonW_dump
#else //  UNICODE
#define Dz1WebSocketCloseReason_dump Dz1WebSocketCloseReasonA_dump
#endif //  UNICODE
static __inline__ void Dz1WebSocketCloseReasonX_dump(Dz1WebSocketCloseReason *p, int tab) { DZ1_DUMP(Dz1WebSocketCloseReason, p, tab); }
#else // UNIX_SYSTEM
#define Dz1WebSocketCloseReason_dump Dz1WebSocketCloseReasonA_dump
#define Dz1WebSocketCloseReasonX_dump Dz1WebSocketCloseReasonA_dump
#endif // UNIX_SYSTEM
// Dz1WebSocketCloseReason
////////////////////////////////////////////////////////////////////////////////

#endif

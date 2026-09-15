#ifndef _DZ1_TDC_DZ1_WEB_SOCKET_TEST_TASK_DEF_H_
#define _DZ1_TDC_DZ1_WEB_SOCKET_TEST_TASK_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "dz1_asn1_support.h"
#include "dz1_task_support.h"
#include "dz1_web_socket_def.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSocketTaskExceptionCB
typedef void (*Dz1WebSocketTaskExceptionCB)(void *ptr, Dz1Error *reason);
// Dz1WebSocketTaskExceptionCB
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSocketTaskArg
typedef struct Dz1WebSocketTaskArg
{
	Dz1WebSocketTaskExceptionCB  cb;
	void                        *cb_param;
} Dz1WebSocketTaskArg;

DZ1_CPPLINK DZ1_DLLPORT Dz1WebSocketTaskArg *Dz1WebSocketTaskArg_new(Dz1WebSocketTaskExceptionCB cb, void *cb_param, Dz1Error *err);
static __inline__ Dz1WebSocketTaskArg *Dz1WebSocketTaskArg_gen(Dz1Error *err) { return Dz1WebSocketTaskArg_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1WebSocketTaskArg *Dz1WebSocketTaskArg_clone(Dz1WebSocketTaskArg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketTaskArg_del(Dz1WebSocketTaskArg *p);
static __inline__ void Dz1WebSocketTaskArg_delAndSetNull(void *ptr)
{
	Dz1WebSocketTaskArg **p = (Dz1WebSocketTaskArg **)ptr;
	Dz1WebSocketTaskArg_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketTaskArgA_dump(Dz1WebSocketTaskArg *p, int tab);
#ifndef UNIX_SYSTEM // structure mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketTaskArgW_dump(Dz1WebSocketTaskArg *p, int tab);
#ifdef UNICODE
#define Dz1WebSocketTaskArg_dump Dz1WebSocketTaskArgW_dump
#else //  UNICODE
#define Dz1WebSocketTaskArg_dump Dz1WebSocketTaskArgA_dump
#endif //  UNICODE
static __inline__ void Dz1WebSocketTaskArgX_dump(Dz1WebSocketTaskArg *p, int tab) { DZ1_DUMP(Dz1WebSocketTaskArg, p, tab); }
#else // UNIX_SYSTEM
#define Dz1WebSocketTaskArg_dump Dz1WebSocketTaskArgA_dump
#define Dz1WebSocketTaskArgX_dump Dz1WebSocketTaskArgA_dump
#endif // UNIX_SYSTEM
// Dz1WebSocketTaskArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSocketTaskTimer
typedef struct Dz1WebSocketTaskTimer
{
	u32_t  id;
} Dz1WebSocketTaskTimer;

DZ1_CPPLINK DZ1_DLLPORT Dz1WebSocketTaskTimer *Dz1WebSocketTaskTimer_new(u32_t id, Dz1Error *err);
static __inline__ Dz1WebSocketTaskTimer *Dz1WebSocketTaskTimer_gen(Dz1Error *err) { return Dz1WebSocketTaskTimer_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketTaskTimer_del(Dz1WebSocketTaskTimer *p);
static __inline__ void Dz1WebSocketTaskTimer_delAndSetNull(void *ptr)
{
	Dz1WebSocketTaskTimer **p = (Dz1WebSocketTaskTimer **)ptr;
	Dz1WebSocketTaskTimer_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketTaskTimerA_dump(Dz1WebSocketTaskTimer *p, int tab);
#ifndef UNIX_SYSTEM // structure mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketTaskTimerW_dump(Dz1WebSocketTaskTimer *p, int tab);
#ifdef UNICODE
#define Dz1WebSocketTaskTimer_dump Dz1WebSocketTaskTimerW_dump
#else //  UNICODE
#define Dz1WebSocketTaskTimer_dump Dz1WebSocketTaskTimerA_dump
#endif //  UNICODE
static __inline__ void Dz1WebSocketTaskTimerX_dump(Dz1WebSocketTaskTimer *p, int tab) { DZ1_DUMP(Dz1WebSocketTaskTimer, p, tab); }
#else // UNIX_SYSTEM
#define Dz1WebSocketTaskTimer_dump Dz1WebSocketTaskTimerA_dump
#define Dz1WebSocketTaskTimerX_dump Dz1WebSocketTaskTimerA_dump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT int Dz1WebSocketTaskTimer_cmp(Dz1WebSocketTaskTimer *a, Dz1WebSocketTaskTimer *b);
// Dz1WebSocketTaskTimer
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSocketTaskEnv
typedef struct Dz1WebSocketTaskEnv
{
	Dz1Task           *tSelf;
	Dz1WebSocket      *wsock;
	Dz1WebSockMsgList *msgs;
	Dz1TaskSigMsg     *pend_sg;
} Dz1WebSocketTaskEnv;

DZ1_CPPLINK DZ1_DLLPORT Dz1WebSocketTaskEnv *Dz1WebSocketTaskEnv_new(Dz1Task *tSelf_ref, Dz1WebSocket *wsock, Dz1Error *err);
static __inline__ Dz1WebSocketTaskEnv *Dz1WebSocketTaskEnv_gen(Dz1Error *err) { return Dz1WebSocketTaskEnv_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketTaskEnv_del(Dz1WebSocketTaskEnv *p);
static __inline__ void Dz1WebSocketTaskEnv_delAndSetNull(void *ptr)
{
	Dz1WebSocketTaskEnv **p = (Dz1WebSocketTaskEnv **)ptr;
	Dz1WebSocketTaskEnv_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketTaskEnvA_dump(Dz1WebSocketTaskEnv *p, int tab);
#ifndef UNIX_SYSTEM // structure mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketTaskEnvW_dump(Dz1WebSocketTaskEnv *p, int tab);
#ifdef UNICODE
#define Dz1WebSocketTaskEnv_dump Dz1WebSocketTaskEnvW_dump
#else //  UNICODE
#define Dz1WebSocketTaskEnv_dump Dz1WebSocketTaskEnvA_dump
#endif //  UNICODE
static __inline__ void Dz1WebSocketTaskEnvX_dump(Dz1WebSocketTaskEnv *p, int tab) { DZ1_DUMP(Dz1WebSocketTaskEnv, p, tab); }
#else // UNIX_SYSTEM
#define Dz1WebSocketTaskEnv_dump Dz1WebSocketTaskEnvA_dump
#define Dz1WebSocketTaskEnvX_dump Dz1WebSocketTaskEnvA_dump
#endif // UNIX_SYSTEM
// Dz1WebSocketTaskEnv
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSocketTaskMsgOpen
typedef struct Dz1WebSocketTaskMsgOpen
{
	Dz1Asn1UTF8Str *uri;
} Dz1WebSocketTaskMsgOpen;

DZ1_CPPLINK DZ1_DLLPORT Dz1WebSocketTaskMsgOpen *Dz1WebSocketTaskMsgOpen_new(Dz1Asn1UTF8Str *uri, Dz1Error *err);
static __inline__ Dz1WebSocketTaskMsgOpen *Dz1WebSocketTaskMsgOpen_gen(Dz1Error *err) { return Dz1WebSocketTaskMsgOpen_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketTaskMsgOpen_del(Dz1WebSocketTaskMsgOpen *p);
static __inline__ void Dz1WebSocketTaskMsgOpen_delAndSetNull(void *ptr)
{
	Dz1WebSocketTaskMsgOpen **p = (Dz1WebSocketTaskMsgOpen **)ptr;
	Dz1WebSocketTaskMsgOpen_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketTaskMsgOpenA_dump(Dz1WebSocketTaskMsgOpen *p, int tab);
#ifndef UNIX_SYSTEM // structure mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketTaskMsgOpenW_dump(Dz1WebSocketTaskMsgOpen *p, int tab);
#ifdef UNICODE
#define Dz1WebSocketTaskMsgOpen_dump Dz1WebSocketTaskMsgOpenW_dump
#else //  UNICODE
#define Dz1WebSocketTaskMsgOpen_dump Dz1WebSocketTaskMsgOpenA_dump
#endif //  UNICODE
static __inline__ void Dz1WebSocketTaskMsgOpenX_dump(Dz1WebSocketTaskMsgOpen *p, int tab) { DZ1_DUMP(Dz1WebSocketTaskMsgOpen, p, tab); }
#else // UNIX_SYSTEM
#define Dz1WebSocketTaskMsgOpen_dump Dz1WebSocketTaskMsgOpenA_dump
#define Dz1WebSocketTaskMsgOpenX_dump Dz1WebSocketTaskMsgOpenA_dump
#endif // UNIX_SYSTEM
// Dz1WebSocketTaskMsgOpen
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSocketTaskMsgSendPresent
typedef enum Dz1WebSocketTaskMsgSendPresent
{
	Dz1WebSocketTaskMsgSendPresent_text,
	Dz1WebSocketTaskMsgSendPresent_bin,
	Dz1WebSocketTaskMsgSendPresent_ping,
	Dz1WebSocketTaskMsgSendPresent_max
} Dz1WebSocketTaskMsgSendPresent;

DZ1_CPPLINK str_t Dz1WebSocketTaskMsgSendPresentStrA(Dz1WebSocketTaskMsgSendPresent v);
DZ1_CPPLINK Dz1WebSocketTaskMsgSendPresent Dz1WebSocketTaskMsgSendPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1WebSocketTaskMsgSendPresentStrW(Dz1WebSocketTaskMsgSendPresent v);
DZ1_CPPLINK Dz1WebSocketTaskMsgSendPresent Dz1WebSocketTaskMsgSendPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1WebSocketTaskMsgSendPresentStr Dz1WebSocketTaskMsgSendPresentStrW
#define Dz1WebSocketTaskMsgSendPresentFromStr Dz1WebSocketTaskMsgSendPresentFromStrW
#else // UNICODE
#define Dz1WebSocketTaskMsgSendPresentStr Dz1WebSocketTaskMsgSendPresentStrA
#define Dz1WebSocketTaskMsgSendPresentFromStr Dz1WebSocketTaskMsgSendPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1WebSocketTaskMsgSendPresentStr Dz1WebSocketTaskMsgSendPresentStrA
#define Dz1WebSocketTaskMsgSendPresentFromStr Dz1WebSocketTaskMsgSendPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1WebSocketTaskMsgSendPresent *Dz1WebSocketTaskMsgSendPresent_new(Dz1WebSocketTaskMsgSendPresent *src, Dz1Error *err);
static __inline__ Dz1WebSocketTaskMsgSendPresent *Dz1WebSocketTaskMsgSendPresent_gen(Dz1Error *err) { Dz1WebSocketTaskMsgSendPresent v = Dz1WebSocketTaskMsgSendPresent_max; return Dz1WebSocketTaskMsgSendPresent_new(&v, err); }
#define Dz1WebSocketTaskMsgSendPresent_del               Dz1u32_del
#define Dz1WebSocketTaskMsgSendPresent_delAndSetNull     Dz1u32_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketTaskMsgSendPresentA_dump(Dz1WebSocketTaskMsgSendPresent *v, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketTaskMsgSendPresentW_dump(Dz1WebSocketTaskMsgSendPresent *v, int tab);
#ifdef UNICODE
#define Dz1WebSocketTaskMsgSendPresent_dump Dz1WebSocketTaskMsgSendPresentW_dump
#else // UNICODE
#define Dz1WebSocketTaskMsgSendPresent_dump Dz1WebSocketTaskMsgSendPresentA_dump
#endif // UNICODE
static __inline__ void Dz1WebSocketTaskMsgSendPresentX_dump(Dz1WebSocketTaskMsgSendPresent *p, int tab) { DZ1_DUMP(Dz1WebSocketTaskMsgSendPresent, p, tab); }
#else // UNIX_SYSTEM
#define Dz1WebSocketTaskMsgSendPresent_dump Dz1WebSocketTaskMsgSendPresentA_dump
#define Dz1WebSocketTaskMsgSendPresentX_dump Dz1WebSocketTaskMsgSendPresentA_dump
#endif // UNIX_SYSTEM
// Dz1WebSocketTaskMsgSendPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSocketTaskMsgSend
typedef struct Dz1WebSocketTaskMsgSend
{
	Dz1WebSocketTaskMsgSendPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1Asn1UTF8Str *text;
		Dz1Binary *bin;
		Dz1Binary *ping;
	} x;
} Dz1WebSocketTaskMsgSend;

DZ1_CPPLINK DZ1_DLLPORT Dz1WebSocketTaskMsgSend *Dz1WebSocketTaskMsgSend_new(Dz1WebSocketTaskMsgSendPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1WebSocketTaskMsgSend *Dz1WebSocketTaskMsgSend_gen(Dz1Error *err) { return Dz1WebSocketTaskMsgSend_new(Dz1WebSocketTaskMsgSendPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketTaskMsgSend_del(Dz1WebSocketTaskMsgSend *p);
static __inline__ void Dz1WebSocketTaskMsgSend_delAndSetNull(void *ptr)
{
	Dz1WebSocketTaskMsgSend **p = (Dz1WebSocketTaskMsgSend **)ptr;
	Dz1WebSocketTaskMsgSend_del(*p); *p = NULL;
}

DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketTaskMsgSendA_dump(Dz1WebSocketTaskMsgSend *p, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketTaskMsgSendW_dump(Dz1WebSocketTaskMsgSend *p, int tab);
#ifdef UNICODE
#define Dz1WebSocketTaskMsgSend_dump Dz1WebSocketTaskMsgSendW_dump
#else // UNICODE
#define Dz1WebSocketTaskMsgSend_dump Dz1WebSocketTaskMsgSendA_dump
#endif //  UNICODE
static __inline__ void Dz1WebSocketTaskMsgSendX_dump(Dz1WebSocketTaskMsgSend *p, int tab) { DZ1_DUMP(Dz1WebSocketTaskMsgSend, p, tab); }
#else // UNIX_SYSTEM
#define Dz1WebSocketTaskMsgSend_dump Dz1WebSocketTaskMsgSendA_dump
#define Dz1WebSocketTaskMsgSendX_dump Dz1WebSocketTaskMsgSendA_dump
#endif // UNIX_SYSTEM
// Dz1WebSocketTaskMsgSend
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WebSocketTaskMsgClose
typedef struct Dz1WebSocketTaskMsgClose
{
	Dz1Asn1UTF8Str *opt_text;
} Dz1WebSocketTaskMsgClose;

DZ1_CPPLINK DZ1_DLLPORT Dz1WebSocketTaskMsgClose *Dz1WebSocketTaskMsgClose_new(Dz1Asn1UTF8Str *opt_text, Dz1Error *err);
static __inline__ Dz1WebSocketTaskMsgClose *Dz1WebSocketTaskMsgClose_gen(Dz1Error *err) { return Dz1WebSocketTaskMsgClose_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketTaskMsgClose_del(Dz1WebSocketTaskMsgClose *p);
static __inline__ void Dz1WebSocketTaskMsgClose_delAndSetNull(void *ptr)
{
	Dz1WebSocketTaskMsgClose **p = (Dz1WebSocketTaskMsgClose **)ptr;
	Dz1WebSocketTaskMsgClose_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketTaskMsgCloseA_dump(Dz1WebSocketTaskMsgClose *p, int tab);
#ifndef UNIX_SYSTEM // structure mode 3
DZ1_CPPLINK DZ1_DLLPORT void Dz1WebSocketTaskMsgCloseW_dump(Dz1WebSocketTaskMsgClose *p, int tab);
#ifdef UNICODE
#define Dz1WebSocketTaskMsgClose_dump Dz1WebSocketTaskMsgCloseW_dump
#else //  UNICODE
#define Dz1WebSocketTaskMsgClose_dump Dz1WebSocketTaskMsgCloseA_dump
#endif //  UNICODE
static __inline__ void Dz1WebSocketTaskMsgCloseX_dump(Dz1WebSocketTaskMsgClose *p, int tab) { DZ1_DUMP(Dz1WebSocketTaskMsgClose, p, tab); }
#else // UNIX_SYSTEM
#define Dz1WebSocketTaskMsgClose_dump Dz1WebSocketTaskMsgCloseA_dump
#define Dz1WebSocketTaskMsgCloseX_dump Dz1WebSocketTaskMsgCloseA_dump
#endif // UNIX_SYSTEM
// Dz1WebSocketTaskMsgClose
////////////////////////////////////////////////////////////////////////////////

#endif

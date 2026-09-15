#ifndef _DZ1_TDC_DZ1_INET_FTP_FSM_DEF_H_
#define _DZ1_TDC_DZ1_INET_FTP_FSM_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpState
typedef enum Dz1InetFtpState
{
	Dz1InetFtpState_initial,
	Dz1InetFtpState_sentUSER,
	Dz1InetFtpState_sentPASS,
	Dz1InetFtpState_sentACCT,
	Dz1InetFtpState_sentTYPE,
	Dz1InetFtpState_sentCWDd,
	Dz1InetFtpState_sentPASVPORT,
	Dz1InetFtpState_sentRETRSTOR,
	Dz1InetFtpState_waitANY,
	Dz1InetFtpState_sentCWDu,
	Dz1InetFtpState_sentMKD,
	Dz1InetFtpState_sentCWDs,
	Dz1InetFtpState_sentSIZE,
	Dz1InetFtpState_waitDTP,
	Dz1InetFtpState_waitDONE,
	Dz1InetFtpState_sentFEAT,
	Dz1InetFtpState_max
} Dz1InetFtpState;

DZ1_CPPLINK str_t Dz1InetFtpStateStrA(Dz1InetFtpState v);
DZ1_CPPLINK Dz1InetFtpState Dz1InetFtpStateFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1InetFtpStateStrW(Dz1InetFtpState v);
DZ1_CPPLINK Dz1InetFtpState Dz1InetFtpStateFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1InetFtpStateStr Dz1InetFtpStateStrW
#define Dz1InetFtpStateFromStr Dz1InetFtpStateFromStrW
#else // UNICODE
#define Dz1InetFtpStateStr Dz1InetFtpStateStrA
#define Dz1InetFtpStateFromStr Dz1InetFtpStateFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1InetFtpStateStr Dz1InetFtpStateStrA
#define Dz1InetFtpStateFromStr Dz1InetFtpStateFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpState *Dz1InetFtpState_new(Dz1InetFtpState *src, Dz1Error *err);
static __inline__ Dz1InetFtpState *Dz1InetFtpState_gen(Dz1Error *err) { Dz1InetFtpState v = Dz1InetFtpState_max; return Dz1InetFtpState_new(&v, err); }
static __inline__ void Dz1InetFtpState_del(Dz1InetFtpState *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1InetFtpState_delAndSetNull(void *ptr)
{
	Dz1InetFtpState **p = (Dz1InetFtpState **)ptr;
	if (p != NULL) { Dz1InetFtpState_del(*p); *p = NULL; }
}
// Dz1InetFtpState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpEvent
typedef enum Dz1InetFtpEvent
{
	Dz1InetFtpEvent_prepare,
	Dz1InetFtpEvent_success,
	Dz1InetFtpEvent_andNext,
	Dz1InetFtpEvent_error,
	Dz1InetFtpEvent_transferDone,
	Dz1InetFtpEvent_max
} Dz1InetFtpEvent;

DZ1_CPPLINK str_t Dz1InetFtpEventStrA(Dz1InetFtpEvent v);
DZ1_CPPLINK Dz1InetFtpEvent Dz1InetFtpEventFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t Dz1InetFtpEventStrW(Dz1InetFtpEvent v);
DZ1_CPPLINK Dz1InetFtpEvent Dz1InetFtpEventFromStrW(wstr_t str);
#ifdef UNICODE
#define Dz1InetFtpEventStr Dz1InetFtpEventStrW
#define Dz1InetFtpEventFromStr Dz1InetFtpEventFromStrW
#else // UNICODE
#define Dz1InetFtpEventStr Dz1InetFtpEventStrA
#define Dz1InetFtpEventFromStr Dz1InetFtpEventFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1InetFtpEventStr Dz1InetFtpEventStrA
#define Dz1InetFtpEventFromStr Dz1InetFtpEventFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1InetFtpEvent *Dz1InetFtpEvent_new(Dz1InetFtpEvent *src, Dz1Error *err);
static __inline__ Dz1InetFtpEvent *Dz1InetFtpEvent_gen(Dz1Error *err) { Dz1InetFtpEvent v = Dz1InetFtpEvent_max; return Dz1InetFtpEvent_new(&v, err); }
static __inline__ void Dz1InetFtpEvent_del(Dz1InetFtpEvent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void Dz1InetFtpEvent_delAndSetNull(void *ptr)
{
	Dz1InetFtpEvent **p = (Dz1InetFtpEvent **)ptr;
	if (p != NULL) { Dz1InetFtpEvent_del(*p); *p = NULL; }
}
// Dz1InetFtpEvent
////////////////////////////////////////////////////////////////////////////////

#endif

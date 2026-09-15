#ifndef _DZ1_TDC_DZ1_TCP_CALLBACK_SERVER_TIMER_H_
#define _DZ1_TDC_DZ1_TCP_CALLBACK_SERVER_TIMER_H_

#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>

#include "Dz1TcpCallbackServerDef.h"


typedef struct Dz1TcpCallbackServerSessionTimer
{
	Dz1SockAddr *peer;
	Dz1SockAddr *local;
} Dz1TcpCallbackServerSessionTimer;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackServerSessionTimer *Dz1TcpCallbackServerSessionTimer_new(Dz1SockAddr *peer, Dz1SockAddr *local, Dz1Error *err);
static __inline__ Dz1TcpCallbackServerSessionTimer *Dz1TcpCallbackServerSessionTimer_gen(Dz1Error *err) { return Dz1TcpCallbackServerSessionTimer_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackServerSessionTimer_del(Dz1TcpCallbackServerSessionTimer *p);
static __inline__ void Dz1TcpCallbackServerSessionTimer_delAndSetNull(void *ptr)
{
	Dz1TcpCallbackServerSessionTimer **p = (Dz1TcpCallbackServerSessionTimer **)ptr;
	Dz1TcpCallbackServerSessionTimer_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackServerSessionTimer_dump(Dz1TcpCallbackServerSessionTimer *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TcpCallbackServerSessionTimer_cmp(Dz1TcpCallbackServerSessionTimer *a, Dz1TcpCallbackServerSessionTimer *b);


typedef enum Dz1TcpCallbackServerTimerPresent
{
	Dz1TcpCallbackServerTimerPresent_id,
	Dz1TcpCallbackServerTimerPresent_session,
	Dz1TcpCallbackServerTimerPresent_max
} Dz1TcpCallbackServerTimerPresent;

DZ1_CPPLINK str_t Dz1TcpCallbackServerTimerPresentStrA(Dz1TcpCallbackServerTimerPresent v);
DZ1_CPPLINK Dz1TcpCallbackServerTimerPresent Dz1TcpCallbackServerTimerPresentFromStrA(str_t str);

DZ1_CPPLINK wstr_t Dz1TcpCallbackServerTimerPresentStrW(Dz1TcpCallbackServerTimerPresent v);
DZ1_CPPLINK Dz1TcpCallbackServerTimerPresent Dz1TcpCallbackServerTimerPresentFromStrW(wstr_t str);

#ifdef UNICODE
#define Dz1TcpCallbackServerTimerPresentStr Dz1TcpCallbackServerTimerPresentStrW
#define Dz1TcpCallbackServerTimerPresentFromStr Dz1TcpCallbackServerTimerPresentFromStrW
#else // UNICODE
#define Dz1TcpCallbackServerTimerPresentStr Dz1TcpCallbackServerTimerPresentStrA
#define Dz1TcpCallbackServerTimerPresentFromStr Dz1TcpCallbackServerTimerPresentFromStrA
#endif // UNICODE
DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackServerTimerPresent *Dz1TcpCallbackServerTimerPresent_new(Dz1TcpCallbackServerTimerPresent *src, Dz1Error *err);
static __inline__ Dz1TcpCallbackServerTimerPresent *Dz1TcpCallbackServerTimerPresent_gen(Dz1Error *err) { Dz1TcpCallbackServerTimerPresent v = Dz1TcpCallbackServerTimerPresent_max; return Dz1TcpCallbackServerTimerPresent_new(&v, err); }
#define Dz1TcpCallbackServerTimerPresent_del               Dz1u32_del
#define Dz1TcpCallbackServerTimerPresent_delAndSetNull     Dz1u32_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackServerTimerPresent_dump(Dz1TcpCallbackServerTimerPresent *v, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TcpCallbackServerTimerPresent_cmp(Dz1TcpCallbackServerTimerPresent *a, Dz1TcpCallbackServerTimerPresent *b);


typedef struct Dz1TcpCallbackServerTimer
{
	Dz1TcpCallbackServerTimerPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		u32_t id;
		Dz1TcpCallbackServerSessionTimer *session;
	} x;
} Dz1TcpCallbackServerTimer;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackServerTimer *Dz1TcpCallbackServerTimer_new(Dz1TcpCallbackServerTimerPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1TcpCallbackServerTimer *Dz1TcpCallbackServerTimer_gen(Dz1Error *err) { return Dz1TcpCallbackServerTimer_new(Dz1TcpCallbackServerTimerPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackServerTimer_del(Dz1TcpCallbackServerTimer *p);
static __inline__ void Dz1TcpCallbackServerTimer_delAndSetNull(void *ptr)
{
	Dz1TcpCallbackServerTimer **p = (Dz1TcpCallbackServerTimer **)ptr;
	Dz1TcpCallbackServerTimer_del(*p); *p = NULL;
}

DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackServerTimer_dump(Dz1TcpCallbackServerTimer *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TcpCallbackServerTimer_cmp(Dz1TcpCallbackServerTimer *a, Dz1TcpCallbackServerTimer *b);
#endif

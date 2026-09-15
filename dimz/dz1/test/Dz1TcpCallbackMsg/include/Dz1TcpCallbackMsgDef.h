#ifndef _DZ1_TDC_DZ1_TCP_CALLBACK_MSG_DEF_H_
#define _DZ1_TDC_DZ1_TCP_CALLBACK_MSG_DEF_H_

#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>

#include "libdz1_support.h"


typedef struct Dz1TcpCallbackEcho
{
	u32_t       echoID;
	Dz1TimeVal *stamp;
} Dz1TcpCallbackEcho;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackEcho *Dz1TcpCallbackEcho_new(u32_t echoID, Dz1TimeVal *stamp, Dz1Error *err);
static __inline__ Dz1TcpCallbackEcho *Dz1TcpCallbackEcho_gen(Dz1Error *err) { return Dz1TcpCallbackEcho_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackEcho *Dz1TcpCallbackEcho_clone(Dz1TcpCallbackEcho *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackEcho_del(Dz1TcpCallbackEcho *p);
static __inline__ void Dz1TcpCallbackEcho_delAndSetNull(void *ptr)
{
	Dz1TcpCallbackEcho **p = (Dz1TcpCallbackEcho **)ptr;
	Dz1TcpCallbackEcho_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackEcho_dump(Dz1TcpCallbackEcho *p, int tab);


typedef enum Dz1TcpCallbackMsgPresent
{
	Dz1TcpCallbackMsgPresent_echo,
	Dz1TcpCallbackMsgPresent_max
} Dz1TcpCallbackMsgPresent;

DZ1_CPPLINK str_t Dz1TcpCallbackMsgPresentStrA(Dz1TcpCallbackMsgPresent v);
DZ1_CPPLINK Dz1TcpCallbackMsgPresent Dz1TcpCallbackMsgPresentFromStrA(str_t str);

DZ1_CPPLINK wstr_t Dz1TcpCallbackMsgPresentStrW(Dz1TcpCallbackMsgPresent v);
DZ1_CPPLINK Dz1TcpCallbackMsgPresent Dz1TcpCallbackMsgPresentFromStrW(wstr_t str);

#ifdef UNICODE
#define Dz1TcpCallbackMsgPresentStr Dz1TcpCallbackMsgPresentStrW
#define Dz1TcpCallbackMsgPresentFromStr Dz1TcpCallbackMsgPresentFromStrW
#else // UNICODE
#define Dz1TcpCallbackMsgPresentStr Dz1TcpCallbackMsgPresentStrA
#define Dz1TcpCallbackMsgPresentFromStr Dz1TcpCallbackMsgPresentFromStrA
#endif // UNICODE
DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackMsgPresent *Dz1TcpCallbackMsgPresent_new(Dz1TcpCallbackMsgPresent *src, Dz1Error *err);
static __inline__ Dz1TcpCallbackMsgPresent *Dz1TcpCallbackMsgPresent_gen(Dz1Error *err) { Dz1TcpCallbackMsgPresent v = Dz1TcpCallbackMsgPresent_max; return Dz1TcpCallbackMsgPresent_new(&v, err); }
#define Dz1TcpCallbackMsgPresent_clone             Dz1TcpCallbackMsgPresent_new
#define Dz1TcpCallbackMsgPresent_del               Dz1u32_del
#define Dz1TcpCallbackMsgPresent_delAndSetNull     Dz1u32_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackMsgPresent_dump(Dz1TcpCallbackMsgPresent *v, int tab);


typedef struct Dz1TcpCallbackMsg
{
	Dz1TcpCallbackMsgPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1TcpCallbackEcho *echo;
	} x;
} Dz1TcpCallbackMsg;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackMsg *Dz1TcpCallbackMsg_new(Dz1TcpCallbackMsgPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1TcpCallbackMsg *Dz1TcpCallbackMsg_gen(Dz1Error *err) { return Dz1TcpCallbackMsg_new(Dz1TcpCallbackMsgPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackMsg *Dz1TcpCallbackMsg_clone(Dz1TcpCallbackMsg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackMsg_del(Dz1TcpCallbackMsg *p);
static __inline__ void Dz1TcpCallbackMsg_delAndSetNull(void *ptr)
{
	Dz1TcpCallbackMsg **p = (Dz1TcpCallbackMsg **)ptr;
	Dz1TcpCallbackMsg_del(*p); *p = NULL;
}

DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackMsg_dump(Dz1TcpCallbackMsg *p, int tab);
#endif

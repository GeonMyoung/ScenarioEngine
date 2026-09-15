#ifndef _DZ1_TDC_DZ1_TCP_CALLBACK_SERVER_DEF_H_
#define _DZ1_TDC_DZ1_TCP_CALLBACK_SERVER_DEF_H_

#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>

#include "libdz1_support.h"


typedef void (*Dz1TcpCallbackServerException)(void *exceptionArg, Dz1Error *reason);

typedef enum Dz1TcpCallbackServerDef
{
	Dz1TcpCallbackServerDef_pseudo,
	Dz1TcpCallbackServerDef_max
} Dz1TcpCallbackServerDef;

DZ1_CPPLINK str_t Dz1TcpCallbackServerDefStrA(Dz1TcpCallbackServerDef v);
DZ1_CPPLINK Dz1TcpCallbackServerDef Dz1TcpCallbackServerDefFromStrA(str_t str);

DZ1_CPPLINK wstr_t Dz1TcpCallbackServerDefStrW(Dz1TcpCallbackServerDef v);
DZ1_CPPLINK Dz1TcpCallbackServerDef Dz1TcpCallbackServerDefFromStrW(wstr_t str);

#ifdef UNICODE
#define Dz1TcpCallbackServerDefStr Dz1TcpCallbackServerDefStrW
#define Dz1TcpCallbackServerDefFromStr Dz1TcpCallbackServerDefFromStrW
#else // UNICODE
#define Dz1TcpCallbackServerDefStr Dz1TcpCallbackServerDefStrA
#define Dz1TcpCallbackServerDefFromStr Dz1TcpCallbackServerDefFromStrA
#endif // UNICODE
DZ1_CPPLINK DZ1_DLLPORT Dz1TcpCallbackServerDef *Dz1TcpCallbackServerDef_new(Dz1TcpCallbackServerDef *src, Dz1Error *err);
static __inline__ Dz1TcpCallbackServerDef *Dz1TcpCallbackServerDef_gen(Dz1Error *err) { Dz1TcpCallbackServerDef v = Dz1TcpCallbackServerDef_max; return Dz1TcpCallbackServerDef_new(&v, err); }
#define Dz1TcpCallbackServerDef_del               Dz1u32_del
#define Dz1TcpCallbackServerDef_delAndSetNull     Dz1u32_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpCallbackServerDef_dump(Dz1TcpCallbackServerDef *v, int tab);

#endif

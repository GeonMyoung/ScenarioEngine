#ifndef _DZ1_TDC_DZ1_SOCK_UTIL_URI_DEF_H_
#define _DZ1_TDC_DZ1_SOCK_UTIL_URI_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilUriInfoA
typedef struct Dz1SockUtilUriInfoA
{
	str_t		prot;
	str_t		host;
	u16_t		port;
	str_t		path;
} Dz1SockUtilUriInfoA;

DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilUriInfoA *Dz1SockUtilUriInfoA_new(str_t prot, 
																	 str_t host, 
																	 u16_t port, 
																	 str_t path, Dz1Error *err);
static __inline__ Dz1SockUtilUriInfoA *Dz1SockUtilUriInfoA_gen(Dz1Error *err) { return Dz1SockUtilUriInfoA_new(NULL, NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1SockUtilUriInfoA_copy(Dz1SockUtilUriInfoA *dst, Dz1SockUtilUriInfoA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilUriInfoA *Dz1SockUtilUriInfoA_clone(Dz1SockUtilUriInfoA *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilUriInfoA_purge(Dz1SockUtilUriInfoA *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilUriInfoA_del(Dz1SockUtilUriInfoA *p);
static __inline__ void Dz1SockUtilUriInfoA_delAndSetNull(void *ptr)
{
	Dz1SockUtilUriInfoA **p = (Dz1SockUtilUriInfoA **)ptr;
	if (p) { Dz1SockUtilUriInfoA_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilUriInfoA_dump(Dz1SockUtilUriInfoA *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1SockUtilUriInfoA_cmp(Dz1SockUtilUriInfoA *a, Dz1SockUtilUriInfoA *b); 
// Dz1SockUtilUriInfoA
////////////////////////////////////////////////////////////////////////////////

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilUriInfoW
typedef struct Dz1SockUtilUriInfoW
{
	wstr_t		prot;
	wstr_t		host;
	u16_t		port;
	wstr_t		path;
} Dz1SockUtilUriInfoW;

DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilUriInfoW *Dz1SockUtilUriInfoW_new(wstr_t prot, 
																	 wstr_t host, 
																	 u16_t port, 
																	 wstr_t path, Dz1Error *err);
static __inline__ Dz1SockUtilUriInfoW *Dz1SockUtilUriInfoW_gen(Dz1Error *err) { return Dz1SockUtilUriInfoW_new(NULL, NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1SockUtilUriInfoW_copy(Dz1SockUtilUriInfoW *dst, Dz1SockUtilUriInfoW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1SockUtilUriInfoW *Dz1SockUtilUriInfoW_clone(Dz1SockUtilUriInfoW *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilUriInfoW_purge(Dz1SockUtilUriInfoW *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilUriInfoW_del(Dz1SockUtilUriInfoW *p);
static __inline__ void Dz1SockUtilUriInfoW_delAndSetNull(void *ptr)
{
	Dz1SockUtilUriInfoW **p = (Dz1SockUtilUriInfoW **)ptr;
	if (p) { Dz1SockUtilUriInfoW_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1SockUtilUriInfoW_dump(Dz1SockUtilUriInfoW *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1SockUtilUriInfoW_cmp(Dz1SockUtilUriInfoW *a, Dz1SockUtilUriInfoW *b); 
// Dz1SockUtilUriInfoW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

#endif

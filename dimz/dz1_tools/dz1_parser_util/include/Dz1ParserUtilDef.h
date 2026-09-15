#ifndef _DZ1_TDC_DZ1_PARSER_UTIL_DEF_H_
#define _DZ1_TDC_DZ1_PARSER_UTIL_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1ParserUtilEnvEntry
typedef struct Dz1ParserUtilEnvEntry
{
	u32_t		 parserID;
	void		*env;
} Dz1ParserUtilEnvEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1ParserUtilEnvEntry *Dz1ParserUtilEnvEntry_new(u32_t parserID, 
																		 void *env, Dz1Error *err);
static __inline__ Dz1ParserUtilEnvEntry *Dz1ParserUtilEnvEntry_gen(Dz1Error *err) { return Dz1ParserUtilEnvEntry_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t Dz1ParserUtilEnvEntry_copy(Dz1ParserUtilEnvEntry *dst, Dz1ParserUtilEnvEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1ParserUtilEnvEntry *Dz1ParserUtilEnvEntry_clone(Dz1ParserUtilEnvEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ParserUtilEnvEntry_purge(Dz1ParserUtilEnvEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ParserUtilEnvEntry_del(Dz1ParserUtilEnvEntry *p);
static __inline__ void Dz1ParserUtilEnvEntry_delAndSetNull(void *ptr)
{
	Dz1ParserUtilEnvEntry **p = (Dz1ParserUtilEnvEntry **)ptr;
	if (p) { Dz1ParserUtilEnvEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1ParserUtilEnvEntry_dump(Dz1ParserUtilEnvEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1ParserUtilEnvEntry_cmp(Dz1ParserUtilEnvEntry *a, Dz1ParserUtilEnvEntry *b); 
// Dz1ParserUtilEnvEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ParserUtilEnvList
typedef struct Dz1ParserUtilEnvList
{
	void *storage;
	unsigned int (*count)(struct Dz1ParserUtilEnvList *p);
	Dz1Error (*travel)(struct Dz1ParserUtilEnvList *p, Dz1Error (*func)(void *ptr, Dz1ParserUtilEnvEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1ParserUtilEnvList *p, Dz1Error (*func)(void *ptr, Dz1ParserUtilEnvEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1ParserUtilEnvList *p, Dz1Error (*func)(void *ptr, Dz1ParserUtilEnvEntry *entry), void *ptr);
	Dz1ParserUtilEnvEntry **(*get_array)(struct Dz1ParserUtilEnvList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct Dz1ParserUtilEnvList *p, Dz1ParserUtilEnvEntry *data);
	bool_t (*remove)(struct Dz1ParserUtilEnvList *p, Dz1ParserUtilEnvEntry *key);
	Dz1ParserUtilEnvEntry *(*extract)(struct Dz1ParserUtilEnvList *p, Dz1ParserUtilEnvEntry *key);
	Dz1ParserUtilEnvEntry *(*find)(struct Dz1ParserUtilEnvList *p, Dz1ParserUtilEnvEntry *key);
	int (*cmp)(Dz1ParserUtilEnvEntry *a, Dz1ParserUtilEnvEntry *b);
} Dz1ParserUtilEnvList;

DZ1_CPPLINK DZ1_DLLPORT Dz1ParserUtilEnvList *Dz1ParserUtilEnvList_new(Dz1Error *err);
static __inline__ Dz1ParserUtilEnvList *Dz1ParserUtilEnvList_gen(Dz1Error *err) { return Dz1ParserUtilEnvList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1ParserUtilEnvList *Dz1ParserUtilEnvList_clone(Dz1ParserUtilEnvList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ParserUtilEnvList_purge(Dz1ParserUtilEnvList *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ParserUtilEnvList_del(Dz1ParserUtilEnvList *p);
static __inline__ void Dz1ParserUtilEnvList_delAndSetNull(void *ptr)
{
	Dz1ParserUtilEnvList **p = (Dz1ParserUtilEnvList **)ptr;
	if (p != NULL) { Dz1ParserUtilEnvList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1ParserUtilEnvList_dump(Dz1ParserUtilEnvList *p, int tab);

// Dz1ParserUtilEnvList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ParserIPv4Env
typedef struct Dz1ParserIPv4Env
{
	u32_t		dst;
} Dz1ParserIPv4Env;

DZ1_CPPLINK DZ1_DLLPORT Dz1ParserIPv4Env *Dz1ParserIPv4Env_new(u32_t dst, Dz1Error *err);
static __inline__ Dz1ParserIPv4Env *Dz1ParserIPv4Env_gen(Dz1Error *err) { return Dz1ParserIPv4Env_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1ParserIPv4Env_purge(Dz1ParserIPv4Env *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ParserIPv4Env_del(Dz1ParserIPv4Env *p);
static __inline__ void Dz1ParserIPv4Env_delAndSetNull(void *ptr)
{
	Dz1ParserIPv4Env **p = (Dz1ParserIPv4Env **)ptr;
	if (p) { Dz1ParserIPv4Env_del(*p); *p = NULL; }
}
// Dz1ParserIPv4Env
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ParserTcpListenAddrEnv
typedef struct Dz1ParserTcpListenAddrEnv
{
	Dz1SockAddr		addr;
} Dz1ParserTcpListenAddrEnv;

DZ1_CPPLINK DZ1_DLLPORT Dz1ParserTcpListenAddrEnv *Dz1ParserTcpListenAddrEnv_new(Dz1Error *err);
static __inline__ Dz1ParserTcpListenAddrEnv *Dz1ParserTcpListenAddrEnv_gen(Dz1Error *err) { return Dz1ParserTcpListenAddrEnv_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1ParserTcpListenAddrEnv_purge(Dz1ParserTcpListenAddrEnv *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1ParserTcpListenAddrEnv_del(Dz1ParserTcpListenAddrEnv *p);
static __inline__ void Dz1ParserTcpListenAddrEnv_delAndSetNull(void *ptr)
{
	Dz1ParserTcpListenAddrEnv **p = (Dz1ParserTcpListenAddrEnv **)ptr;
	if (p) { Dz1ParserTcpListenAddrEnv_del(*p); *p = NULL; }
}
// Dz1ParserTcpListenAddrEnv
////////////////////////////////////////////////////////////////////////////////

#endif

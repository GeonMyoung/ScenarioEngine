#ifndef _DZ1_TDC_ITS_ISO14827_ENV_H_
#define _DZ1_TDC_ITS_ISO14827_ENV_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827DomainDef.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827Env
typedef struct ItsIso14827Env
{
	void						*tSelf;
	ItsIso14827SessionMgr		*sessionMgr;
	ItsIso14827DomainMgr		*domainMgr;
	u32_t						 pktDumpFlag;
} ItsIso14827Env;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827Env *ItsIso14827Env_new(void *tSelf, 
														   ItsIso14827SessionMgr *sessionMgr, 
														   ItsIso14827DomainMgr *domainMgr, 
														   u32_t pktDumpFlag, Dz1Error *err);
static __inline__ ItsIso14827Env *ItsIso14827Env_gen(Dz1Error *err) { return ItsIso14827Env_new(NULL, NULL, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827Env_purge(ItsIso14827Env *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827Env_del(ItsIso14827Env *p);
static __inline__ void ItsIso14827Env_delAndSetNull(void *ptr)
{
	ItsIso14827Env **p = (ItsIso14827Env **)ptr;
	if (p) { ItsIso14827Env_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827Env_dump(ItsIso14827Env *p, int tab);
// ItsIso14827Env
////////////////////////////////////////////////////////////////////////////////

#endif

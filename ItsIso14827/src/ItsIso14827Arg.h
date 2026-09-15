#ifndef _DZ1_TDC_ITS_ISO14827_ARG_H_
#define _DZ1_TDC_ITS_ISO14827_ARG_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827Def.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827Arg
typedef struct ItsIso14827Arg
{
	ItsIso14827Exception	 exceptionProc;
	void					*exceptionArg;
} ItsIso14827Arg;

DZ1_CPPLINK DZ1_DLLPORT ItsIso14827Arg *ItsIso14827Arg_new(ItsIso14827Exception exceptionProc, 
														   void *exceptionArg, Dz1Error *err);
static __inline__ ItsIso14827Arg *ItsIso14827Arg_gen(Dz1Error *err) { return ItsIso14827Arg_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827Arg_purge(ItsIso14827Arg *p);
DZ1_CPPLINK DZ1_DLLPORT void ItsIso14827Arg_del(ItsIso14827Arg *p);
static __inline__ void ItsIso14827Arg_delAndSetNull(void *ptr)
{
	ItsIso14827Arg **p = (ItsIso14827Arg **)ptr;
	if (p) { ItsIso14827Arg_del(*p); *p = NULL; }
}
// ItsIso14827Arg
////////////////////////////////////////////////////////////////////////////////

#endif

#ifndef _DZ1_TDC_ITSK00126V1_EMULATOR_ARG_H_
#define _DZ1_TDC_ITSK00126V1_EMULATOR_ARG_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "Itsk00126v1EmulatorDef.h"

////////////////////////////////////////////////////////////////////////////////
// Itsk00126V1EmulatorArg
typedef struct Itsk00126V1EmulatorArg
{
	Itsk00126V1EmulatorException	 exceptionProc;
	void							*exceptionArg;
} Itsk00126V1EmulatorArg;

DZ1_CPPLINK DZ1_DLLPORT Itsk00126V1EmulatorArg *Itsk00126V1EmulatorArg_new(Itsk00126V1EmulatorException exceptionProc, 
																		   void *exceptionArg, Dz1Error *err);
static __inline__ Itsk00126V1EmulatorArg *Itsk00126V1EmulatorArg_gen(Dz1Error *err) { return Itsk00126V1EmulatorArg_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V1EmulatorArg_purge(Itsk00126V1EmulatorArg *p);
DZ1_CPPLINK DZ1_DLLPORT void Itsk00126V1EmulatorArg_del(Itsk00126V1EmulatorArg *p);
static __inline__ void Itsk00126V1EmulatorArg_delAndSetNull(void *ptr)
{
	Itsk00126V1EmulatorArg **p = (Itsk00126V1EmulatorArg **)ptr;
	if (p) { Itsk00126V1EmulatorArg_del(*p); *p = NULL; }
}
// Itsk00126V1EmulatorArg
////////////////////////////////////////////////////////////////////////////////

#endif

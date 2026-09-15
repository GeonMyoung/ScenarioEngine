#ifndef _DZ1_TDC_I_T_S_K00144_2_EMULATOR_ARG_H_
#define _DZ1_TDC_I_T_S_K00144_2_EMULATOR_ARG_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "ITSK00144_2EmulatorDef.h"

////////////////////////////////////////////////////////////////////////////////
// ITSK001442EmulatorArg
typedef struct ITSK001442EmulatorArg
{
	ITSK001442EmulatorException		 exceptionProc;
	void							*exceptionArg;
} ITSK001442EmulatorArg;

DZ1_CPPLINK DZ1_DLLPORT ITSK001442EmulatorArg *ITSK001442EmulatorArg_new(ITSK001442EmulatorException exceptionProc, 
																		 void *exceptionArg, Dz1Error *err);
static __inline__ ITSK001442EmulatorArg *ITSK001442EmulatorArg_gen(Dz1Error *err) { return ITSK001442EmulatorArg_new(NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void ITSK001442EmulatorArg_purge(ITSK001442EmulatorArg *p);
DZ1_CPPLINK DZ1_DLLPORT void ITSK001442EmulatorArg_del(ITSK001442EmulatorArg *p);
static __inline__ void ITSK001442EmulatorArg_delAndSetNull(void *ptr)
{
	ITSK001442EmulatorArg **p = (ITSK001442EmulatorArg **)ptr;
	if (p) { ITSK001442EmulatorArg_del(*p); *p = NULL; }
}
// ITSK001442EmulatorArg
////////////////////////////////////////////////////////////////////////////////

#endif

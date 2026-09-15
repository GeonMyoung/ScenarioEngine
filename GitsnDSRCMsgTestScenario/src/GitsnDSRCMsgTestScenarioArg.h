#ifndef _DZ1_TDC_GITSN_D_S_R_C_MSG_TEST_SCENARIO_ARG_H_
#define _DZ1_TDC_GITSN_D_S_R_C_MSG_TEST_SCENARIO_ARG_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "GitsnDSRCMsgTestScenarioDef.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgTestScenarioArg
typedef struct GitsnDSRCMsgTestScenarioArg
{
	void									*tMain;
	Dz1Str									 testScenario;
	GitsnDSRCMsgTestScenarioException		 exceptionProc;
	void									*exceptionArg;
} GitsnDSRCMsgTestScenarioArg;

DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgTestScenarioArg *GitsnDSRCMsgTestScenarioArg_new(void *tMain, 
																					 Dz1Str testScenario, 
																					 GitsnDSRCMsgTestScenarioException exceptionProc, 
																					 void *exceptionArg, Dz1Error *err);
static __inline__ GitsnDSRCMsgTestScenarioArg *GitsnDSRCMsgTestScenarioArg_gen(Dz1Error *err) { return GitsnDSRCMsgTestScenarioArg_new(NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgTestScenarioArg_purge(GitsnDSRCMsgTestScenarioArg *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgTestScenarioArg_del(GitsnDSRCMsgTestScenarioArg *p);
static __inline__ void GitsnDSRCMsgTestScenarioArg_delAndSetNull(void *ptr)
{
	GitsnDSRCMsgTestScenarioArg **p = (GitsnDSRCMsgTestScenarioArg **)ptr;
	if (p) { GitsnDSRCMsgTestScenarioArg_del(*p); *p = NULL; }
}
// GitsnDSRCMsgTestScenarioArg
////////////////////////////////////////////////////////////////////////////////

#endif

#ifndef _DZ1_TDC_GITSN_D_S_R_C_MSG_TEST_SCENARIO_TIMER_H_
#define _DZ1_TDC_GITSN_D_S_R_C_MSG_TEST_SCENARIO_TIMER_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "GitsnDSRCMsgTestScenarioDef.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgTestScenarioTimer
typedef struct GitsnDSRCMsgTestScenarioTimer
{
	u32_t		id;
} GitsnDSRCMsgTestScenarioTimer;

DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgTestScenarioTimer *GitsnDSRCMsgTestScenarioTimer_new(u32_t id, Dz1Error *err);
static __inline__ GitsnDSRCMsgTestScenarioTimer *GitsnDSRCMsgTestScenarioTimer_gen(Dz1Error *err) { return GitsnDSRCMsgTestScenarioTimer_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgTestScenarioTimer_purge(GitsnDSRCMsgTestScenarioTimer *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgTestScenarioTimer_del(GitsnDSRCMsgTestScenarioTimer *p);
static __inline__ void GitsnDSRCMsgTestScenarioTimer_delAndSetNull(void *ptr)
{
	GitsnDSRCMsgTestScenarioTimer **p = (GitsnDSRCMsgTestScenarioTimer **)ptr;
	if (p) { GitsnDSRCMsgTestScenarioTimer_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgTestScenarioTimer_dump(GitsnDSRCMsgTestScenarioTimer *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int GitsnDSRCMsgTestScenarioTimer_cmp(GitsnDSRCMsgTestScenarioTimer *a, GitsnDSRCMsgTestScenarioTimer *b); 
// GitsnDSRCMsgTestScenarioTimer
////////////////////////////////////////////////////////////////////////////////

#endif

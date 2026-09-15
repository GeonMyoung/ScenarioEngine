#ifndef _DZ1_TDC_GITSN_D_S_R_C_MSG_TEST_SCENARIO_MSGS_H_
#define _DZ1_TDC_GITSN_D_S_R_C_MSG_TEST_SCENARIO_MSGS_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "GitsnDSRCMsgTestScenarioDef.h"

////////////////////////////////////////////////////////////////////////////////
// GitsnDSRCMsgTestScenarioMsgDefault
typedef struct GitsnDSRCMsgTestScenarioMsgDefault
{
	u32_t		*dummy;
} GitsnDSRCMsgTestScenarioMsgDefault;

DZ1_CPPLINK DZ1_DLLPORT GitsnDSRCMsgTestScenarioMsgDefault *GitsnDSRCMsgTestScenarioMsgDefault_new(u32_t *dummy, Dz1Error *err);
static __inline__ GitsnDSRCMsgTestScenarioMsgDefault *GitsnDSRCMsgTestScenarioMsgDefault_gen(Dz1Error *err) { return GitsnDSRCMsgTestScenarioMsgDefault_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgTestScenarioMsgDefault_purge(GitsnDSRCMsgTestScenarioMsgDefault *p);
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgTestScenarioMsgDefault_del(GitsnDSRCMsgTestScenarioMsgDefault *p);
static __inline__ void GitsnDSRCMsgTestScenarioMsgDefault_delAndSetNull(void *ptr)
{
	GitsnDSRCMsgTestScenarioMsgDefault **p = (GitsnDSRCMsgTestScenarioMsgDefault **)ptr;
	if (p) { GitsnDSRCMsgTestScenarioMsgDefault_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void GitsnDSRCMsgTestScenarioMsgDefault_dump(GitsnDSRCMsgTestScenarioMsgDefault *p, int tab);
// GitsnDSRCMsgTestScenarioMsgDefault
////////////////////////////////////////////////////////////////////////////////

#endif

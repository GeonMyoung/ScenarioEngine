#ifndef ISO14827_TEST_HELPER_SCENARIO_UTIL_H
#define ISO14827_TEST_HELPER_SCENARIO_UTIL_H

#include "Iso14827TestHelperArg.h"
#include "Iso14827TestHelperEnv.h"

//DZ1_CPPLINK bool_t Iso14827TestClientRole1_init(Iso14827TestHelperEnv *env, Iso14827Test_ScenarioRoleIdx idx, Iso14827TestClientRole1Arg *arg, Dz1Error* errp);
//DZ1_CPPLINK bool_t Iso14827TestClientRole2_init(Iso14827TestHelperEnv* env, Iso14827Test_ScenarioRoleIdx idx, Iso14827TestClientRole2Arg* arg, Dz1Error* errp);
//DZ1_CPPLINK bool_t Iso14827TestServerRole1_init(Iso14827TestHelperEnv* env, Iso14827Test_ScenarioRoleIdx idx, Iso14827TestServerRole1Arg* arg, Dz1Error* errp);
//DZ1_CPPLINK bool_t Iso14827TestServerRole2_init(Iso14827TestHelperEnv* env, Iso14827Test_ScenarioRoleIdx idx, Iso14827TestServerRole2Arg* arg, Dz1Error* errp);
//DZ1_CPPLINK bool_t Iso14827TestDuoClientRole_init(Iso14827TestHelperEnv* env, Iso14827Test_ScenarioRoleIdx idx, Iso14827TestDuoClientRoleArg* arg, Dz1Error* errp);
//DZ1_CPPLINK bool_t Iso14827TestDuoSessionRole_init(Iso14827TestHelperEnv* env, Iso14827Test_ScenarioRoleIdx idx, Iso14827TestDuoSessionRoleArg* arg, Dz1Error* errp);

DZ1_CPPLINK bool_t _client_reset_test_sub(Iso14827TestHelperEnv* env, Dz1Error* errp);
DZ1_CPPLINK bool_t _client_init_test_subs(Iso14827TestHelperEnv* env, SubscribeSpecList* src, Dz1Error* errp);
DZ1_CPPLINK bool_t _client_init_test_sub(Iso14827TestHelperEnv* env, SubscribeSpecEntry* src, Dz1Error* errp);
DZ1_CPPLINK bool_t _client_init_duo_subs(Iso14827TestHelperEnv* env, SubscribeSpecDuo* src, Dz1Error* errp);
DZ1_CPPLINK bool_t _client_init_duo_subs1(Iso14827TestHelperEnv* env, SubscribeSpecDuo* src, Dz1Error* errp);
DZ1_CPPLINK bool_t _client_init_duo_subs2(Iso14827TestHelperEnv* env, SubscribeSpecDuo* src, Dz1Error* errp);
DZ1_CPPLINK bool_t _client_util_subscribe(Iso14827TestHelperArg* arg, Dz1Asn1Codec selected_codec, Dz1Asn1UTF8Str* my_domain, Dz1Asn1UTF8Str* peer_domain, Iso14827TestAccount* acc, SubscribeSpecEntry* entry, Dz1Binary* eam, u32_t* ret_sid, Iso14827RejectSubscription* ret_result, Dz1Error* err);

#endif // !ISO14827_TEST_HELPER_SCENARIO_UTIL_H

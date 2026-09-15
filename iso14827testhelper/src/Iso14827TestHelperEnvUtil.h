#ifndef ISO14827_TEST_HELPER_ENV_UTIL_H
#define ISO14827_TEST_HELPER_ENV_UTIL_H

// #include <Iso14827TestMsg.h>
#include <Iso14827TestMsgUtil.h>
#include "Iso14827TestHelperEnv.h"
//#include "Iso14827TestHelperMsgSet.h"


#define ISO14827_TEST_HELPER_DEFAULT_SCENARIO	Dz1T("MainScenario")
#define ISO14827_TEST_HELPER_SENDER_AGENT		Dz1T("시험시스템")
#define ISO14827_TEST_HELPER_SENDER_SUT			Dz1T("시험대상시스템")

static __inline__ bool_t Iso14827TestConnection_isPassive(Iso14827TestConnection* c)
{
	bool_t ret = FALSE;
	if (c->present == Iso14827TestConnectionPresent_active) ret = TRUE;
	return ret;
}


// DZ1_CPPLINK bool_t Iso14827TestHelperEnv_sendMsgToMain(Iso14827TestHelperEnv* env, Iso14827Test_ScenarioSendMessage* ptr, Dz1Error* err);

DZ1_CPPLINK bool_t SubscribeSpecEntry_isSingle(SubscribeSpecEntry* p);
DZ1_CPPLINK bool_t SubscribeSpecList_cloneAndAppend(SubscribeSpecList* dst, SubscribeSpecEntry* src, Dz1Error* err);
DZ1_CPPLINK SubscribeSpecEntry* SubscribeSpecList_findByOID(SubscribeSpecList* list, Dz1Str oid);

DZ1_CPPLINK Iso14827TestSubType Iso14827TestSubType_getFromSubscribe(SubscribeSpecEntry* src, Dz1Error* err);

static __inline__ void Iso14827TestSubList_addCancel(void* ptr)
{
	Dz1ListAddCancelArg* arg = (Dz1ListAddCancelArg*)ptr;
	Iso14827TestSubList* list = (Iso14827TestSubList*)arg->list;
	Iso14827TestSubEntry** node = (Iso14827TestSubEntry**)arg->node;
	if (list != NULL && node != NULL && *node != NULL)
		list->extract(list, *node);
}

DZ1_CPPLINK Iso14827TestSubEntry* Iso14827TestSubList_insert(Iso14827TestSubList* dst, Iso14827TestSubEntry** _node, Dz1Error* err);
DZ1_CPPLINK Iso14827TestSubEntry* Iso14827TestSubList_append(Iso14827TestSubList* dst, Dz1Asn1UTF8Str* peer, u32_t sid, Dz1Str oidStr, Iso14827TestSubType type, Dz1Error* err);
DZ1_CPPLINK Iso14827TestSubEntry* Iso14827TestSubList_findByID(Iso14827TestSubList* p, Dz1Asn1UTF8Str* peer, u32_t sid);
DZ1_CPPLINK Iso14827TestSubEntry* Iso14827TestSubList_findByOID(Iso14827TestSubList* p, Dz1Str oid);
DZ1_CPPLINK void Iso14827TestSubList_removeByID(Iso14827TestSubList* p, Dz1Asn1UTF8Str* peer, u32_t sid);
DZ1_CPPLINK void Iso14827TestSubList_flush(Iso14827TestSubList* p);

DZ1_CPPLINK void _publication_log_dump_(Iso14827TestMsgStructAPI* msg_api, Dz1Str oidStr, u8_t* encodedEAM, u32_t encodedEAMSize, Dz1Asn1Codec selected_codec);


DZ1_CPPLINK bool_t Iso14827TestHelperEnvUtil_notifyState(Iso14827TestHelperEnv* env, Dz1Str testName, Dz1Str state, Dz1Error* err);
DZ1_CPPLINK bool_t Iso14827TestHelperEnvUtil_notifyInfo(Iso14827TestHelperEnv* env, Dz1Str testName, Dz1Str sender, Dz1Str log, Dz1Binary* data, Dz1Str dataType, Dz1Error* err);
DZ1_CPPLINK bool_t Iso14827TestHelperEnvUtil_notifyError(Iso14827TestHelperEnv* env, Dz1Str testName, Iso14827TestProcessStatusCode code, Dz1Str desc, Dz1Str log, Dz1Binary* data, Dz1Error* err);

DZ1_CPPLINK bool_t Iso14827TestHelperEnvUtil_notifyStateToMain(Iso14827TestHelperEnv* env, Iso14827TestNotifyStateArg *arg, Dz1Error* err);
DZ1_CPPLINK bool_t Iso14827TestHelperEnvUtil_notifyInfoToMain(Iso14827TestHelperEnv* env, Iso14827TestNotifyInfoArg *arg, Dz1Error* err);
DZ1_CPPLINK bool_t Iso14827TestHelperEnvUtil_notifyErrorToMain(Iso14827TestHelperEnv* env, Iso14827TestNotifyErrorArg*arg, Dz1Error* err);

DZ1_CPPLINK bool_t Iso14827TestHelperEnvUtil_sendUIConfigure(Iso14827TestHelperEnv* env, Dz1Str testScenario, Dz1Error* err);

DZ1_CPPLINK bool_t Iso14827TestHelperEnvUtil_validateRequest(Iso14827TestHelperEnv* env, Dz1Str testName, Dz1Binary* raw, Dz1Binary* data, Iso14827TestProcessStatusCode code, Dz1Error* err);
DZ1_CPPLINK bool_t Iso14827TestHelperEnvUtil_validateRequestToMain(Iso14827TestHelperEnv* env, Iso14827TestValidateContextArg* arg, Dz1Error* err);

// DZ1_CPPLINK bool_t Iso14827TestHelperEnvUtil_insertDataFrame(Iso14827TestHelperEnv* env, Dz1Binary* src, bool_t* ret_is_complete_df, Dz1Error* err);


#endif // !ISO14827_TEST_HELPER_ENV_UTIL_H

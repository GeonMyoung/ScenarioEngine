#include "GitsnDSRCMsgTestScenarioProc.h"
#include <GitsnDSRCMsgTestScenarioDefJson.h>
#include <dz1_asn1.h>
#include <dz1_gasn_support.h>
#include <Dz1SockUtil.h>
#include <GitsnTestDataProtocol.h>
#include <GitsnAsnUtil.h>

#define GITSN_DSRC_MSG_TEST_FLAG_CREATED		0x80000000
#define GITSN_DSRC_MSG_TEST_FLAG_CONNECTED		0x40000000
#define GITSN_DSRC_MSG_TEST_FLAG_TEST_DATA		0x20000000



static Dz1Str test_name_test_map = Dz1T("test_map");
static Dz1Str test_name_test_spat = Dz1T("test_spat");
static Dz1Str test_name_test_bsm = Dz1T("test_bsm");
static Dz1Str test_name_test_eva = Dz1T("test_eva");
static Dz1Str test_name_test_pvd = Dz1T("test_pvd");
static Dz1Str test_name_test_rsa = Dz1T("test_rsa");
static Dz1Str test_name_test_rtcm = Dz1T("test_rtcm");
static Dz1Str test_name_test_srm = Dz1T("test_srm");
static Dz1Str test_name_test_ssm = Dz1T("test_ssm");
static Dz1Str test_name_test_tim = Dz1T("test_tim");
static Dz1Str test_name_test_psm = Dz1T("test_psm");
static Dz1Str test_name_test_sdsm = Dz1T("test_sdsm");
static Dz1Str test_name_test_tls = Dz1T("test_tls");

static struct TestCheckList
{
	Dz1Str testName;
	bool_t isDone;
} TestCheckList;

static struct TestCheckList _test_check_list[] = {
	{Dz1T("test_map"), FALSE},
	{Dz1T("test_spat"), FALSE},
	{Dz1T("test_bsm"), FALSE},
	{Dz1T("test_eva"), FALSE},
	{Dz1T("test_pvd"), FALSE},
	{Dz1T("test_rsa"), FALSE},
	{Dz1T("test_rtcm"), FALSE},
	{Dz1T("test_srm"), FALSE},
	{Dz1T("test_ssm"), FALSE},
	{Dz1T("test_tim"), FALSE},
	{Dz1T("test_psm"), FALSE},
	{Dz1T("test_sdsm"), FALSE},
	{Dz1T("test_tls"), FALSE},
	{NULL, FALSE}
};

static void _clear_check_list(struct TestCheckList* p)
{
	struct TestCheckList* i;
	if (p != NULL)
	{
		for (i = p; i->testName != NULL; i++)
		{
			i->isDone = FALSE;
		}
	}
}

static int _get_state_from_check_list(struct TestCheckList* p, Dz1Str testName)
{
	struct TestCheckList* i;
	if (p == NULL || testName == NULL) return FALSE;
	else
	{
		for (i = p; i->testName != NULL; i++)
		{
			if (Dz1STRCMP(i->testName, testName) == 0)
			{
				return i->isDone;
			}
		}
	}
	return -1;
}

static bool_t _mark_done_validate_test(struct TestCheckList* p, Dz1Str testName)
{
	struct TestCheckList* i;
	if (p == NULL || testName == NULL) return FALSE;
	else
	{
		for (i = p; i->testName != NULL; i++)
		{
			if (Dz1STRCMP(i->testName, testName) == 0)
			{
				i->isDone = TRUE;
				return TRUE;
			}
		}
	}
	return FALSE;
}
static bool_t _is_done_check_list(struct TestCheckList* p)
{
	struct TestCheckList* i;
	if (p != NULL)
	{
		for (i = p; i->testName != NULL; i++)
		{
			if (i->isDone == FALSE) return FALSE;
		}
	}
	return TRUE;
}

static Dz1Asn1UTF8Str* _get_stringify_u8(Dz1JsonSpec* spec, Dz1Str struct_name, void* struct_ptr, Dz1Error* errp)
{
	Dz1Asn1UTF8Str* ret = NULL;
	Dz1Json* json = NULL;
	if ((json = Dz1Json_new(DZ1_SYSTEM_CHARSET, spec, struct_name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Json_delAndSetNull, (void*)&json);
		Dz1Str src = NULL;
		if (Dz1Json_stringify(json, struct_name, struct_ptr, Dz1JsonNewLine_continuous, errp) == FALSE) ERR_OUT(errp);
		else if ((src = Dz1Json_stringified(json, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Str_delAndSetNull, (void*)&src);
			if ((ret = Dz1Asn1UTF8Str_newFromStr(src, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void*)&src);
		}
		pthread_cleanup_pop(1); // (Dz1Json_delAndSetNull, (void*)&json);
	}
	return ret;
}

static GitsnDSRCMsgSession* _gen_server_session(GitsnDSRCMsgTestScenarioEnv* env, GitsnDSRCMsgScenario* s, Dz1Error* errp)
{
	GitsnDSRCMsgSession* ret = NULL;

	if ((ret = GitsnDSRCMsgSession_new(GitsnDSRCMsgSessionPresent_server, NULL,errp )) == NULL) ERR_OUT(errp);
	else
	{
		GitsnDSRCMsgServerSession* server = NULL;
		pthread_cleanup_push(GitsnDSRCMsgSession_delAndSetNull, (void*)&ret);
		if ((ret->x.server =server = GitsnDSRCMsgServerSession_new(-1, NULL, NULL, NULL, NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1SockAddr local;
			u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);
			if (0) {}
			else if ((*errp = Dz1SockAddr_setAddrStr(&local, (str_t)"0.0.0.0")).code) ERR_OUT(errp);
			else if ((*errp = Dz1SockAddr_setPort(&local, (u16_t)s->local_port)).code) ERR_OUT(errp);
			else if ((server->local = Dz1SockAddr_clone(&local, errp)) == NULL) ERR_OUT(errp);
			else if ((server->acceptor = Dz1SockUtilAcceptorForTask_start(0, server->local, my_queue_id, errp)) == (u32_t)-1) ERR_OUT(errp);
			else
			{
				char log[128];
				sprintf(log, "포트(%d)를 열었습니다. 클라이언트의 접속 수신을 대기합니다.", (int)s->local_port);

				if (GitsnDSRCMsgTestScenarioEnvUtil_notifyInfo(env, NULL, NULL, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);

				u16_t port;
				Dz1SockAddr_getPort(server->local, &port);
				Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ SERVER : Port Opened(%d)...\n"), port);
				Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(errp->code); // (GitsnDSRCMsgServerSession_delAndSetNull, (void*)&ret);
	}
	return ret;
}


static bool_t _initial(GitsnDSRCMsgTestScenarioArg* arg, GitsnDSRCMsgTestScenarioEnv* env, void* timer, void* _s, int _ev, void* _msg, Dz1Error* errp)
{
	GitsnDSRCMsgScenario* s = (GitsnDSRCMsgScenario*)_s;
	GitsnDSRCMsgScenarioEvent ev = (GitsnDSRCMsgScenarioEvent)_ev;
	u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);

	switch (ev)
	{
	case GitsnDSRCMsgScenarioEvent_start:
		if (env->session != NULL) ERR_SET_OUT(errp, EEXIST);
		else if ((env->session = _gen_server_session(env, s, errp)) == NULL) ERR_OUT(errp);
		else
		{
			env->flags |= GITSN_DSRC_MSG_TEST_FLAG_CREATED;
			Dz1Error_set(errp, 0);
		}
		break;

	case GitsnDSRCMsgScenarioEvent_auth:
		env->flags |= GITSN_DSRC_MSG_TEST_FLAG_CONNECTED;
		Dz1Error_set(errp, 0);
		break;
	default:
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	if (errp->code == 0 && (env->flags & GITSN_DSRC_MSG_TEST_FLAG_CREATED) && (env->flags & GITSN_DSRC_MSG_TEST_FLAG_CONNECTED))
	{
		if (s->test_map == FALSE) _mark_done_validate_test(_test_check_list, test_name_test_map);
		if (s->test_spat == FALSE) _mark_done_validate_test(_test_check_list, test_name_test_spat);
		if (s->test_bsm == FALSE) _mark_done_validate_test(_test_check_list, test_name_test_bsm);
		if (s->test_eva == FALSE) _mark_done_validate_test(_test_check_list, test_name_test_eva);
		if (s->test_pvd == FALSE) _mark_done_validate_test(_test_check_list, test_name_test_pvd);
		if (s->test_rsa == FALSE) _mark_done_validate_test(_test_check_list, test_name_test_rsa);
		if (s->test_rtcm == FALSE) _mark_done_validate_test(_test_check_list, test_name_test_rtcm);
		if (s->test_srm == FALSE) _mark_done_validate_test(_test_check_list, test_name_test_srm);
		if (s->test_ssm == FALSE) _mark_done_validate_test(_test_check_list, test_name_test_ssm);
		if (s->test_tim == FALSE) _mark_done_validate_test(_test_check_list, test_name_test_tim);
		if (s->test_psm == FALSE) _mark_done_validate_test(_test_check_list, test_name_test_psm);
		if (s->test_sdsm == FALSE) _mark_done_validate_test(_test_check_list, test_name_test_sdsm);
		if (s->test_tls == FALSE) _mark_done_validate_test(_test_check_list, test_name_test_tls);

		env->state = GitsnDSRCMsgScenarioState_wait_data;
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static Dz1Binary* value_from_msgFrame(Dz1Binary* src, int* msg_id, Dz1Error* errp)
{
	Dz1Binary* ret = NULL;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	MessageFrame asn;
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	size_t consume_sz = 0;
	ASN1_Save_WORKSPACE(&ws, src->data, src->size);
	ws.dataSize = src->size;
	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ MessageFrame decode start...\n"));
	if (ASN1_PER_UNAlign_Dec_MessageFrame(&ws, &asn) < 0) ERR_SET_OUT(errp, EFAULT);
	else
	{
		if ((ret = Dz1Binary_new(asn.value.data, asn.value.numocts, errp)) == NULL) ERR_OUT(errp);
		else
		{
			*msg_id = (int)asn.messageId;
			Dz1Error_set(errp, 0);
		}
	}
	pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	return ret;
}

static bool_t _validate_req(GitsnDSRCMsgTestScenarioArg* arg, GitsnDSRCMsgTestScenarioEnv* env, void* timer, GitsnDSRCMsgScenario* s, void* _msg, Dz1Error* errp)
{
	GitsnTestDataFrames* dfs = NULL;
	Dz1Binary* src = NULL;
	if ((dfs = env->dfs) == NULL || dfs->count(dfs) == 0)
	{
		ERR_SET_OUT(errp, EFAULT);
	}
	else
	{
		if ((src = GitsnTestDataProtocol_getPayloadFromDataFrames(dfs, errp)) == NULL) ERR_OUT(errp);
		else
		{
			if(GitsnDSRCMsgTestScenarioEnvUtil_notifyInfo(env, GITSN_DSRC_MSG_DEFAULT_SCENARIO, GITSN_DSRC_MSG_SENDER_SUT, Dz1T("시험 대상으로부터 메시지를 수신하였습니다."), src, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			Dz1Binary* value = NULL;
			int msg_id = 0;
			if ((value = GitsnAsnUtil_getValueFromMessageFrame(src, &msg_id, errp)) == NULL)
			{
				if (GitsnDSRCMsgTestScenarioEnvUtil_notifyInfo(env, GITSN_DSRC_MSG_DEFAULT_SCENARIO, NULL, Dz1T("메시지 프레임 디코딩을 실패하였습니다.."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
				else ERR_SET_OUT(errp, EFAULT);
			}
			else
			{
				pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&value);
				if (0) {}
				else
				{
					ASN1WorkSpace ws;
					size_t consume_sz = 0;
					Dz1Asn1UTF8Str* str_u8 = NULL;
					Dz1Binary* data = NULL;
					ASN1_INIT_WS_INFO(&ws);
					pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
					switch (msg_id)
					{
					case 18:
					{
						if (s->test_map && _get_state_from_check_list(_test_check_list, test_name_test_map) == FALSE)
						{
							GitsnDSRCMsgTestScenarioEnvUtil_notifyState(env, test_name_test_map, Dz1T("START"), errp);
						}
						MapData asn;
						memset(&asn, 0, sizeof(MapData));
						if (MapData_uper_decode(&ws, value, &asn, errp) == FALSE)
						{
							if (GitsnDSRCMsgTestScenarioEnvUtil_notifyInfo(env, test_name_test_map, NULL, Dz1T("MAP 디코딩을 실패하였습니다.."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
							else ERR_SET_OUT(errp, EFAULT);
						}
						else
						{
							Gitsn_MapData deser;
							memset(&deser, 0, sizeof(Gitsn_MapData));
							if (GitsnAsnUtil_Gitsn_MapDataFromASN(&asn, &deser, errp) == FALSE) ERR_OUT(errp);
							else
							{
								if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("Gitsn_MapData"), &deser, errp)) == NULL) ERR_OUT(errp);
								else
								{
									pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
									if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
									else
									{
										pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
										if (GitsnDSRCMsgTestScenarioEnvUtil_validateRequest(env, test_name_test_map, value, data, GitsnDSRCMsgProcessStatusCode_OK, errp) == FALSE) ERR_OUT(errp);
										else Dz1Error_set(errp, 0);
										pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
									}
									pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
								}
							}
						}
						break;
					}
					case 19:
					{
						if (s->test_spat && _get_state_from_check_list(_test_check_list, test_name_test_spat) == FALSE)
						{
							GitsnDSRCMsgTestScenarioEnvUtil_notifyState(env, test_name_test_spat, Dz1T("START"), errp);
						}
						SPAT asn;
						memset(&asn, 0, sizeof(SPAT));
						if (SPAT_uper_decode(&ws, value, &asn, errp) == FALSE)
						{
							if (GitsnDSRCMsgTestScenarioEnvUtil_notifyInfo(env, test_name_test_spat, NULL, Dz1T("SPaT 디코딩을 실패하였습니다.."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
							else ERR_SET_OUT(errp, EFAULT);
						}
						else
						{
							Gitsn_SPAT deser;
							memset(&deser, 0, sizeof(Gitsn_SPAT));
							if (GitsnAsnUtil_Gitsn_SPATFromASN(&asn, &deser, errp) == FALSE) ERR_OUT(errp);
							else
							{
								if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("Gitsn_SPAT"), &deser, errp)) == NULL) ERR_OUT(errp);
								else
								{
									pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
									if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
									else
									{
										pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
										if (GitsnDSRCMsgTestScenarioEnvUtil_validateRequest(env, test_name_test_spat, value, data, GitsnDSRCMsgProcessStatusCode_OK, errp) == FALSE) ERR_OUT(errp);
										else Dz1Error_set(errp, 0);
										pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
									}
									pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
								}
							}
						}
						break;
					}
					case 20:
					{
						if (s->test_bsm && _get_state_from_check_list(_test_check_list, test_name_test_bsm) == FALSE)
						{
							GitsnDSRCMsgTestScenarioEnvUtil_notifyState(env, test_name_test_bsm, Dz1T("START"), errp);
						}
						BasicSafetyMessage asn;
						memset(&asn, 0, sizeof(BasicSafetyMessage));
						if (BasicSafetyMessage_uper_decode(&ws, value, &asn, errp) == FALSE)
						{
							if (GitsnDSRCMsgTestScenarioEnvUtil_notifyInfo(env, test_name_test_bsm, NULL, Dz1T("BSM 디코딩을 실패하였습니다.."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
							else ERR_SET_OUT(errp, EFAULT);
						}
						else
						{
							Gitsn_BasicSafetyMessage deser;
							memset(&deser, 0, sizeof(Gitsn_BasicSafetyMessage));
							if (GitsnAsnUtil_Gitsn_BasicSafetyMessageFromASN(&asn, &deser, errp) == FALSE) ERR_OUT(errp);
							else
							{
								if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("Gitsn_BasicSafetyMessage"), &deser, errp)) == NULL) ERR_OUT(errp);
								else
								{
									pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
									if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
									else
									{
										pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
										if (GitsnDSRCMsgTestScenarioEnvUtil_validateRequest(env, test_name_test_bsm, value, data, GitsnDSRCMsgProcessStatusCode_OK, errp) == FALSE) ERR_OUT(errp);
										else Dz1Error_set(errp, 0);
										pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
									}
									pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
								}
							}
						}
						break;
					}
					case 22:
					{
						if (s->test_eva && _get_state_from_check_list(_test_check_list, test_name_test_eva) == FALSE)
						{
							GitsnDSRCMsgTestScenarioEnvUtil_notifyState(env, test_name_test_eva, Dz1T("START"), errp);
						}
						EmergencyVehicleAlert asn;
						memset(&asn, 0, sizeof(EmergencyVehicleAlert));
						if (EmergencyVehicleAlert_uper_decode(&ws, value, &asn, errp) == FALSE)
						{
							if (GitsnDSRCMsgTestScenarioEnvUtil_notifyInfo(env, test_name_test_eva, NULL, Dz1T("EVA 디코딩을 실패하였습니다.."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
							else ERR_SET_OUT(errp, EFAULT);
						}
						else
						{
							Gitsn_EmergencyVehicleAlert deser;
							memset(&deser, 0, sizeof(Gitsn_EmergencyVehicleAlert));
							if (GitsnAsnUtil_Gitsn_EmergencyVehicleAlertFromASN(&asn, &deser, errp) == FALSE) ERR_OUT(errp);
							else
							{
								if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("Gitsn_EmergencyVehicleAlert"), &deser, errp)) == NULL) ERR_OUT(errp);
								else
								{
									pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
									if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
									else
									{
										pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
										if (GitsnDSRCMsgTestScenarioEnvUtil_validateRequest(env, test_name_test_eva, value, data, GitsnDSRCMsgProcessStatusCode_OK, errp) == FALSE) ERR_OUT(errp);
										else Dz1Error_set(errp, 0);
										pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
									}
									pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
								}
							}
						}
						break;
					}
					case 26:
					{
						if (s->test_pvd && _get_state_from_check_list(_test_check_list, test_name_test_pvd) == FALSE)
						{
							GitsnDSRCMsgTestScenarioEnvUtil_notifyState(env, test_name_test_pvd, Dz1T("START"), errp);
						}
						ProbeVehicleData asn;
						memset(&asn, 0, sizeof(ProbeVehicleData));
						if (ProbeVehicleData_uper_decode(&ws, value, &asn, errp) == FALSE)
						{
							if (GitsnDSRCMsgTestScenarioEnvUtil_notifyInfo(env, test_name_test_pvd, NULL, Dz1T("PVD 디코딩을 실패하였습니다.."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
							else ERR_SET_OUT(errp, EFAULT);
						}
						else
						{
							Gitsn_ProbeVehicleData deser;
							memset(&deser, 0, sizeof(Gitsn_ProbeVehicleData));
							if (GitsnAsnUtil_Gitsn_ProbeVehicleDataFromASN(&asn, &deser, errp) == FALSE) ERR_OUT(errp);
							else
							{
								if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("Gitsn_ProbeVehicleData"), &deser, errp)) == NULL) ERR_OUT(errp);
								else
								{
									pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
									if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
									else
									{
										pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
										if (GitsnDSRCMsgTestScenarioEnvUtil_validateRequest(env, test_name_test_pvd, value, data, GitsnDSRCMsgProcessStatusCode_OK, errp) == FALSE) ERR_OUT(errp);
										else Dz1Error_set(errp, 0);
										pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
									}
									pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
								}
							}
						}
						break;
					}
					case 27:
					{
						if (s->test_rsa && _get_state_from_check_list(_test_check_list, test_name_test_rsa) == FALSE)
						{
							GitsnDSRCMsgTestScenarioEnvUtil_notifyState(env, test_name_test_rsa, Dz1T("START"), errp);
						}
						RoadSideAlert asn;
						memset(&asn, 0, sizeof(RoadSideAlert));
						if (RoadSideAlert_uper_decode(&ws, value, &asn, errp) == FALSE)
						{
							if (GitsnDSRCMsgTestScenarioEnvUtil_notifyInfo(env, test_name_test_rsa, NULL, Dz1T("RSA 디코딩을 실패하였습니다.."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
							else ERR_SET_OUT(errp, EFAULT);
						}

						else
						{
							Gitsn_RoadSideAlert deser;
							memset(&deser, 0, sizeof(Gitsn_RoadSideAlert));
							if (GitsnAsnUtil_Gitsn_RoadSideAlertFromASN(&asn, &deser, errp) == FALSE) ERR_OUT(errp);
							else
							{
								if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("Gitsn_RoadSideAlert"), &deser, errp)) == NULL) ERR_OUT(errp);
								else
								{
									pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
									if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
									else
									{
										pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
										if (GitsnDSRCMsgTestScenarioEnvUtil_validateRequest(env, test_name_test_rsa, value, data, GitsnDSRCMsgProcessStatusCode_OK, errp) == FALSE) ERR_OUT(errp);
										else Dz1Error_set(errp, 0);
										pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
									}
									pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
								}
							}
						}
						break;
					}
					case 28:
					{
						if (s->test_rtcm && _get_state_from_check_list(_test_check_list, test_name_test_rtcm) == FALSE)
						{
							GitsnDSRCMsgTestScenarioEnvUtil_notifyState(env, test_name_test_rtcm, Dz1T("START"), errp);
						}
						RTCMcorrections asn;
						memset(&asn, 0, sizeof(RTCMcorrections));
						if (RTCMcorrections_uper_decode(&ws, value, &asn, errp) == FALSE)
						{
							if (GitsnDSRCMsgTestScenarioEnvUtil_notifyInfo(env, test_name_test_rtcm, NULL, Dz1T("RTCM 디코딩을 실패하였습니다.."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
							else ERR_SET_OUT(errp, EFAULT);
						}
						else
						{
							Gitsn_RTCMcorrections deser;
							memset(&deser, 0, sizeof(Gitsn_RTCMcorrections));
							if (GitsnAsnUtil_Gitsn_RTCMcorrectionsFromASN(&asn, &deser, errp) == FALSE) ERR_OUT(errp);
							else
							{
								if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("Gitsn_RTCMcorrections"), &deser, errp)) == NULL) ERR_OUT(errp);
								else
								{
									pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
									if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
									else
									{
										pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
										if (GitsnDSRCMsgTestScenarioEnvUtil_validateRequest(env, test_name_test_rtcm, value, data, GitsnDSRCMsgProcessStatusCode_OK, errp) == FALSE) ERR_OUT(errp);
										else Dz1Error_set(errp, 0);
										pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
									}
									pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
								}
							}
						}
						break;
					}
					case 29:
					{
						if (s->test_srm && _get_state_from_check_list(_test_check_list, test_name_test_srm) == FALSE)
						{
							GitsnDSRCMsgTestScenarioEnvUtil_notifyState(env, test_name_test_srm, Dz1T("START"), errp);
						}
						SignalRequestMessage asn;
						memset(&asn, 0, sizeof(SignalRequestMessage));
						if (SignalRequestMessage_uper_decode(&ws, value, &asn, errp) == FALSE)
						{
							if (GitsnDSRCMsgTestScenarioEnvUtil_notifyInfo(env, test_name_test_srm, NULL, Dz1T("SRM 디코딩을 실패하였습니다.."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
							else ERR_SET_OUT(errp, EFAULT);
						}
						else
						{
							Gitsn_SignalRequestMessage deser;
							memset(&deser, 0, sizeof(Gitsn_SignalRequestMessage));
							if (GitsnAsnUtil_Gitsn_SignalRequestMessageFromASN(&asn, &deser, errp) == FALSE) ERR_OUT(errp);
							else
							{
								if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("Gitsn_SignalRequestMessage"), &deser, errp)) == NULL) ERR_OUT(errp);
								else
								{
									pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
									if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
									else
									{
										pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
										if (GitsnDSRCMsgTestScenarioEnvUtil_validateRequest(env, test_name_test_srm, value, data, GitsnDSRCMsgProcessStatusCode_OK, errp) == FALSE) ERR_OUT(errp);
										else Dz1Error_set(errp, 0);
										pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
									}
									pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
								}
							}
						}
						break;
					}
					case 30:
					{
						if (s->test_ssm && _get_state_from_check_list(_test_check_list, test_name_test_ssm) == FALSE)
						{
							GitsnDSRCMsgTestScenarioEnvUtil_notifyState(env, test_name_test_ssm, Dz1T("START"), errp);
						}
						SignalStatusMessage asn;
						memset(&asn, 0, sizeof(SignalStatusMessage));
						if (SignalStatusMessage_uper_decode(&ws, value, &asn, errp) == FALSE)
						{
							if (GitsnDSRCMsgTestScenarioEnvUtil_notifyInfo(env, test_name_test_ssm, NULL, Dz1T("SSM 디코딩을 실패하였습니다.."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
							else ERR_SET_OUT(errp, EFAULT);
						}
						else
						{
							Gitsn_SignalStatusMessage deser;
							memset(&deser, 0, sizeof(Gitsn_SignalStatusMessage));
							if (GitsnAsnUtil_Gitsn_SignalStatusMessageFromASN(&asn, &deser, errp) == FALSE) ERR_OUT(errp);
							else
							{
								if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("Gitsn_SignalStatusMessage"), &deser, errp)) == NULL) ERR_OUT(errp);
								else
								{
									pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
									if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
									else
									{
										pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
										if (GitsnDSRCMsgTestScenarioEnvUtil_validateRequest(env, test_name_test_ssm, value, data, GitsnDSRCMsgProcessStatusCode_OK, errp) == FALSE) ERR_OUT(errp);
										else Dz1Error_set(errp, 0);
										pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
									}
									pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
								}
							}
						}
						break;
					}
					case 31:
					{
						if (s->test_tim && _get_state_from_check_list(_test_check_list, test_name_test_tim) == FALSE)
						{
							GitsnDSRCMsgTestScenarioEnvUtil_notifyState(env, test_name_test_tim, Dz1T("START"), errp);
						}
						TravelerInformation asn;
						memset(&asn, 0, sizeof(TravelerInformation));
						if (TravelerInformation_uper_decode(&ws, value, &asn, errp) == FALSE)
						{
							if (GitsnDSRCMsgTestScenarioEnvUtil_notifyInfo(env, test_name_test_tim, NULL, Dz1T("TIM 디코딩을 실패하였습니다.."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
							else ERR_SET_OUT(errp, EFAULT);
						}
						else
						{
							Gitsn_TravelerInformation deser;
							memset(&deser, 0, sizeof(Gitsn_TravelerInformation));
							if (GitsnAsnUtil_Gitsn_TravelerInformationFromASN(&asn, &deser, errp) == FALSE) ERR_OUT(errp);
							else
							{
								if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("Gitsn_TravelerInformation"), &deser, errp)) == NULL) ERR_OUT(errp);
								else
								{
									pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
									if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
									else
									{
										pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
										if (GitsnDSRCMsgTestScenarioEnvUtil_validateRequest(env, test_name_test_tim, value, data, GitsnDSRCMsgProcessStatusCode_OK, errp) == FALSE) ERR_OUT(errp);
										else Dz1Error_set(errp, 0);
										pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
									}
									pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
								}
							}
						}
						break;
					}
					case 32:
					{
						if (s->test_psm && _get_state_from_check_list(_test_check_list, test_name_test_psm) == FALSE)
						{
							GitsnDSRCMsgTestScenarioEnvUtil_notifyState(env, test_name_test_psm, Dz1T("START"), errp);
						}
						PersonalSafetyMessage asn;
						memset(&asn, 0, sizeof(PersonalSafetyMessage));
						if (PersonalSafetyMessage_uper_decode(&ws, value, &asn, errp) == FALSE)
						{
							if (GitsnDSRCMsgTestScenarioEnvUtil_notifyInfo(env, test_name_test_psm, NULL, Dz1T("PSM 디코딩을 실패하였습니다.."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
							else ERR_SET_OUT(errp, EFAULT);
						}
						else
						{
							Gitsn_PersonalSafetyMessage deser;
							memset(&deser, 0, sizeof(Gitsn_PersonalSafetyMessage));
							if (GitsnAsnUtil_Gitsn_PersonalSafetyMessageFromASN(&asn, &deser, errp) == FALSE) ERR_OUT(errp);
							else
							{
								if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("Gitsn_PersonalSafetyMessage"), &deser, errp)) == NULL) ERR_OUT(errp);
								else
								{
									pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
									if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
									else
									{
										pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
										if (GitsnDSRCMsgTestScenarioEnvUtil_validateRequest(env, test_name_test_psm, value, data, GitsnDSRCMsgProcessStatusCode_OK, errp) == FALSE) ERR_OUT(errp);
										else Dz1Error_set(errp, 0);
										pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
									}
									pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
								}
							}
						}
						break;
					}
					case 41:
					{
						if (s->test_sdsm && _get_state_from_check_list(_test_check_list, test_name_test_sdsm) == FALSE)
						{
							GitsnDSRCMsgTestScenarioEnvUtil_notifyState(env, test_name_test_sdsm, Dz1T("START"), errp);
						}
						SensorDataSharingMessage asn;
						memset(&asn, 0, sizeof(SensorDataSharingMessage));
						if (SensorDataSharingMessage_uper_decode(&ws, value, &asn, errp) == FALSE)
						{
							if (GitsnDSRCMsgTestScenarioEnvUtil_notifyInfo(env, test_name_test_sdsm, NULL, Dz1T("SDSM 디코딩을 실패하였습니다.."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
							else ERR_SET_OUT(errp, EFAULT);
						}
						else
						{
							Gitsn_SensorDataSharingMessage deser;
							memset(&deser, 0, sizeof(Gitsn_SensorDataSharingMessage));
							if (GitsnAsnUtil_Gitsn_SensorDataSharingMessageFromASN(&asn, &deser, errp) == FALSE) ERR_OUT(errp);
							else
							{
								if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("Gitsn_SensorDataSharingMessage"), &deser, errp)) == NULL) ERR_OUT(errp);
								else
								{
									pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
									if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
									else
									{
										pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
										if (GitsnDSRCMsgTestScenarioEnvUtil_validateRequest(env, test_name_test_sdsm, value, data, GitsnDSRCMsgProcessStatusCode_OK, errp) == FALSE) ERR_OUT(errp);
										else Dz1Error_set(errp, 0);
										pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
									}
									pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
								}
							}
						}
						break;
					}
					case 50:
					{
						if (s->test_tls && _get_state_from_check_list(_test_check_list, test_name_test_tls) == FALSE)
						{
							GitsnDSRCMsgTestScenarioEnvUtil_notifyState(env, test_name_test_tls, Dz1T("START"), errp);
						}
						TLS asn;
						memset(&asn, 0, sizeof(TLS));
						if (TLS_uper_decode(&ws, value, &asn, errp) == FALSE)
						{
							if (GitsnDSRCMsgTestScenarioEnvUtil_notifyInfo(env, test_name_test_tls, NULL, Dz1T("TLS 디코딩을 실패하였습니다.."), NULL, NULL, errp) == FALSE) ERR_OUT(errp);
							else ERR_SET_OUT(errp, EFAULT);
						}
						else
						{
							Gitsn_TLS deser;
							memset(&deser, 0, sizeof(Gitsn_TLS));
							if (GitsnAsnUtil_Gitsn_TLSFromASN(&asn, &deser, errp) == FALSE) ERR_OUT(errp);
							else
							{
								if ((str_u8 = _get_stringify_u8(env->spec, Dz1T("Gitsn_TLS"), &deser, errp)) == NULL) ERR_OUT(errp);
								else
								{
									pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
									if ((data = Dz1Binary_new(str_u8->data, str_u8->size, errp)) == NULL) ERR_OUT(errp);
									else
									{
										pthread_cleanup_push(Dz1Binary_delAndSetNull, (void*)&data);
										if (GitsnDSRCMsgTestScenarioEnvUtil_validateRequest(env, test_name_test_tls, value, data, GitsnDSRCMsgProcessStatusCode_OK, errp) == FALSE) ERR_OUT(errp);
										else Dz1Error_set(errp, 0);
										pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&data);
									}
									pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void*)&str_u8);
								}
							}
						}
						break;
					}
					default:
						// 알수없는 메시지 아이디
						break;
					}
					pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void*)&ws);
				}
				pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void*)&value);
			}

		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _validate_received(GitsnDSRCMsgTestScenarioArg* arg, GitsnDSRCMsgTestScenarioEnv* env, void* timer, GitsnDSRCMsgScenario* s, void* _msg, Dz1Error* errp)
{
	GitsnDSRCMsgValidateContext* msg = (GitsnDSRCMsgValidateContext*)_msg;
	if (msg == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		switch (msg->code)
		{
		case GitsnDSRCMsgProcessStatusCode_OK:
			GitsnDSRCMsgTestScenarioEnvUtil_notifyState(env, msg->testName, Dz1T("SUCCESS"), errp);
			_mark_done_validate_test(_test_check_list, msg->testName);
			break;
		default:
			GitsnDSRCMsgTestScenarioEnvUtil_notifyState(env, msg->testName, Dz1T("FAIL"), errp);
			ERR_SET_OUT(errp, EFAULT);
			break;
		}
		if (errp->code == 0 && _is_done_check_list(_test_check_list))
		{
			env->flags |= GITSN_DSRC_MSG_TEST_FLAG_TEST_DATA;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t _wait_data(GitsnDSRCMsgTestScenarioArg* arg, GitsnDSRCMsgTestScenarioEnv* env, void* timer, void* _s, int _ev, void* _msg, Dz1Error* errp)
{
	GitsnDSRCMsgScenario* s = (GitsnDSRCMsgScenario*)_s;
	GitsnDSRCMsgScenarioEvent ev = (GitsnDSRCMsgScenarioEvent)_ev;

	switch (ev)
	{
		case GitsnDSRCMsgScenarioEvent_data:
			if (_validate_req(arg, env, timer, s, _msg, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case GitsnDSRCMsgScenarioEvent_validate:
			if (_validate_received(arg, env, timer, s, _msg, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
	default:ERR_SET_OUT(errp, EPERM);
		break;
	}
	if (errp->code == 0 && (env->flags & GITSN_DSRC_MSG_TEST_FLAG_TEST_DATA))
	{
		GitsnDSRCMsgTestScenarioEnvUtil_notifyInfo(env, GITSN_DSRC_MSG_DEFAULT_SCENARIO, NULL, Dz1T("선택한 모든 시험의 검증을 완료하였습니다."), NULL, NULL, errp);
		env->state = GitsnDSRCMsgScenarioState_complete;
		Dz1Error_set(errp, 0);
	}

	return ERR_IS_SUCCESS(errp);
}

static GitsnDSRCMsgTestScenarioF _dsrc_msg_test[] =
{
	_initial,
	_wait_data,
	NULL
};


static bool_t GitsnDSRCMsgTestScenarioProc_event(GitsnDSRCMsgTestScenarioArg* arg, GitsnDSRCMsgTestScenarioEnv* env, void* timer, GitsnDSRCMsgScenario* s, GitsnDSRCMsgScenarioEvent ev, void* msg, bool_t* ret_is_complete, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (env->state >= GitsnDSRCMsgScenarioState_complete) ERR_SET_OUT(errp, EPERM);
	else if (_dsrc_msg_test[env->state](arg, env, timer, s, ev, msg, errp) == FALSE)
	{
		GitsnDSRCMsgTestScenarioEnvUtil_notifyState(env, GITSN_DSRC_MSG_DEFAULT_SCENARIO, Dz1T("FAIL"), NULL);
		GitsnDSRCMsgTestScenarioEnvUtil_notifyState(env, GITSN_DSRC_MSG_DEFAULT_SCENARIO, Dz1T("FINISH"), NULL);
		GitsnDSRCMsgTestScenarioProc_release(arg, env, timer, NULL);
		ERR_OUT(errp);
	}
	else
	{
		if (env->state == GitsnDSRCMsgScenarioState_complete)
		{
			*ret_is_complete = TRUE;
			GitsnDSRCMsgTestScenarioEnvUtil_notifyState(env, GITSN_DSRC_MSG_DEFAULT_SCENARIO, Dz1T("SUCCESS"), NULL);
			GitsnDSRCMsgTestScenarioEnvUtil_notifyState(env, GITSN_DSRC_MSG_DEFAULT_SCENARIO, Dz1T("FINISH"), NULL);
			GitsnDSRCMsgTestScenarioProc_release(arg, env, timer, NULL);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

bool_t GitsnDSRCMsgTestScenarioProc_start(GitsnDSRCMsgTestScenarioArg* arg, GitsnDSRCMsgTestScenarioEnv* env, void* timer, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnDSRCMsgScenario* s = NULL;
	if ((s = env->scenario) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (env->is_run == TRUE) ERR_SET_OUT(errp, EPERM);
	else
	{
		bool_t is_complete = FALSE;
		env->is_run = TRUE;
		env->state = GitsnDSRCMsgScenarioState_initial; // state define
		
		GitsnDSRCMsgTestScenarioEnvUtil_notifyState(env, GITSN_DSRC_MSG_DEFAULT_SCENARIO, Dz1T("START"), NULL);

		return GitsnDSRCMsgTestScenarioProc_event(arg, env, timer, s, GitsnDSRCMsgScenarioEvent_start, NULL, &is_complete, errp);
	}
	return ERR_IS_SUCCESS(errp);
}
bool_t GitsnDSRCMsgTestScenarioProc_stop(GitsnDSRCMsgTestScenarioArg* arg, GitsnDSRCMsgTestScenarioEnv* env, void* timer, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (GitsnDSRCMsgTestScenarioEnvUtil_notifyState(env, GITSN_DSRC_MSG_DEFAULT_SCENARIO, Dz1T("STOP"), errp) == FALSE) ERR_OUT(errp);
	else if (GitsnDSRCMsgTestScenarioEnvUtil_notifyState(env, GITSN_DSRC_MSG_DEFAULT_SCENARIO, Dz1T("FINISH"), errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	GitsnDSRCMsgTestScenarioProc_release(arg, env, timer, errp);

	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ DSRC MSG Test Scenario is aborted...\n"));

	return ERR_IS_SUCCESS(errp);
}

void GitsnDSRCMsgTestScenarioProc_release(GitsnDSRCMsgTestScenarioArg* arg, GitsnDSRCMsgTestScenarioEnv* env, void* timer, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	env->is_run = FALSE;
	// GitsnDSRCMsgTestMsg_clearSample(NULL);
	if (env->scenario != NULL)
	{
		GitsnDSRCMsgScenario_delAndSetNull((void*)&env->scenario);
	}
	if (env->session != NULL) GitsnDSRCMsgSession_delAndSetNull((void*)&env->session);

	if (env->dfs != NULL)
	{
		GitsnTestDataFrames_delAndSetNull((void*)&env->dfs);
		env->dfs = GitsnTestDataFrames_gen(errp);
	}
	_clear_check_list(_test_check_list);
	env->state = GitsnDSRCMsgScenarioState_initial;
	env->flags = 0;
	Dz1Thread_printf("$$$ DSRC MSG  Test Scenario is released...\n");
}


bool_t GitsnDSRCMsgTestScenarioProc_sockProc(GitsnDSRCMsgTestScenarioArg* arg, GitsnDSRCMsgTestScenarioEnv* env, void* timer, GitsnDSRCMsgScenario*s,  GitsnDSRCMsgScenarioEvent ev,void *_msg, Dz1Error* err)
{
	bool_t is_complete = FALSE;
	return GitsnDSRCMsgTestScenarioProc_event(arg, env, timer, s, ev, _msg, &is_complete, err);
}



bool_t GitsnDSRCMsgTestScenarioProc_sendToPeer(GitsnDSRCMsgTestScenarioArg* arg, GitsnDSRCMsgTestScenarioEnv* env, void* timer, Dz1Binary* src, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	GitsnDSRCMsgSession* session = NULL;
	if (src == NULL || (session = env->session) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		switch (session->present)
		{
		case GitsnDSRCMsgSessionPresent_server:
		{
			GitsnDSRCMsgServerSession* server = NULL;
			if ((server = session->x.server) == NULL) ERR_SET_OUT(errp, ENOSYS);
			else if (Dz1SockUtilTxFifo_send(server->tx_fifo, server->sock, src->data, src->size, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
			break;
		case GitsnDSRCMsgSessionPresent_client:
		{
			GitsnDSRCMsgClientSession* client = NULL;
			if ((client = session->x.client) == NULL) ERR_SET_OUT(errp, ENOSYS);
			else if (Dz1SockUtilTxFifo_send(client->tx_fifo, client->sock, src->data, src->size, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
			break;
		default: ERR_SET_OUT(errp, EPERM);
			break;
		}
	}
	if (errp->code == 0)
	{
		//if (GitsnDSRCMsgTestScenarioEnvUtil_notifyInfo(env, env->current_test, GITSN_DSRC_MSG_SENDER_AGENT, Dz1T("시험 대상에게 메시지를 전송합니다."), src, Dz1T("BINARY"), errp) == FALSE) ERR_OUT(errp);
		//else Dz1Error_set(errp, 0);
	}
	// seq ++;
	return ERR_IS_SUCCESS(errp);
}





// SOCK MESSAGE
// DZ1_SOCK_UTIL_ACCEPTOR_CONNECTED
static Dz1TaskProcStatus _server_connected(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	GitsnDSRCMsgTestScenarioArg* arg = (GitsnDSRCMsgTestScenarioArg*)uArg;
	GitsnDSRCMsgTestScenarioEnv* env = (GitsnDSRCMsgTestScenarioEnv*)uRsc;

	Dz1SockUtilAcceptorConnected* msg = Dz1TaskSigMsg_getData(*sg);
	//GitsnDSRCMsgScenarioConfig* scenario = NULL;
	GitsnDSRCMsgSession* session = NULL;
	GitsnDSRCMsgServerSession* server = NULL;
	GitsnDSRCMsgScenario* s = NULL;

	u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);
	if ((s = env->scenario) == NULL) ERR_OUT(errp);
	else if ((session = env->session) == NULL) ERR_OUT(errp);
	else if ((server = session->x.server) == NULL) ERR_OUT(errp);
	else if ((server->peer = Dz1SockAddr_clone(msg->peer, errp)) == NULL) ERR_OUT(errp);
	else if ((server->sock = msg->sock) == NULL) ERR_OUT(errp);
	else if ((server->rx_buf = Dz1ElasticBuf_new(1024, FALSE, errp)) == NULL) ERR_OUT(errp);
	else if ((server->rx_stream = Dz1Stream_openRefElasticBuf(server->rx_buf, errp)) == NULL) ERR_OUT(errp);
	else if ((server->tx_fifo = Dz1SockUtilTxFifo_new(errp)) == NULL) ERR_OUT(errp);
	else if ((*errp = Dz1SockUtilTcpClient_modeCallback(server->sock, server->peer, server->local, 1024, my_queue_id)).code) ERR_OUT(errp);
	else
	{

		char str_addr[64] = { 0, };
		Dz1SockAddrA_printable(msg->peer, str_addr, FALSE, NULL);

		if (0) {}
		else
		{
			char log[128] = "클라이언트가 접속하였습니다. 클라이언트 주소 : ";
			strcat(log, str_addr);
			if (GitsnDSRCMsgTestScenarioEnvUtil_notifyInfo(env, NULL, NULL, log, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}


		msg->sock = NULL;
		msg->local = msg->peer = NULL;
		Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("$$$ Session established ] = \n"));
		GitsnDSRCMsgServerSession_dump(server, 0);

		GitsnDSRCMsgTestScenarioProc_sockProc(arg, env, timer, s, GitsnDSRCMsgScenarioEvent_auth, NULL, errp);


		Dz1Error_set(errp, 0);
	}

	return ret;
}

// DZ1_SOCK_UTIL_ACCEPTOR_EXCEPTION
static Dz1TaskProcStatus _server_connect_exception(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	GitsnDSRCMsgTestScenarioArg* arg = (GitsnDSRCMsgTestScenarioArg*)uArg;
	GitsnDSRCMsgTestScenarioEnv* env = (GitsnDSRCMsgTestScenarioEnv*)uRsc;

	if (env->session != NULL) GitsnDSRCMsgSession_delAndSetNull((void*)&env->session);

	Dz1Thread_printf("!!! Server accept error!\n");

	return ret;
}

// DZ1_SOCK_UTIL_RECEIVER_RECEIVED
static Dz1TaskProcStatus _server_received(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	GitsnDSRCMsgTestScenarioArg* arg = (GitsnDSRCMsgTestScenarioArg*)uArg;
	GitsnDSRCMsgTestScenarioEnv* env = (GitsnDSRCMsgTestScenarioEnv*)uRsc;

	GitsnDSRCMsgSession* session = NULL;
	GitsnDSRCMsgServerSession* server = NULL;
	GitsnDSRCMsgScenario* s = NULL;

	Dz1SockUtilReceiverReceived* msg = (Dz1SockUtilReceiverReceived*)Dz1TaskSigMsg_getData(*sg);

	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("Received msg from SUT = \n"));
	Dz1SockUtilReceiverReceived_dump(msg, 0);
	Dz1Thread_log(DZ1_THREAD_LOG_FLOW, Dz1T("\n"));

	if ((s = env->scenario) == NULL) ERR_OUT(errp);
	else if ((session = env->session) == NULL) ERR_OUT(errp);
	else if ((server = session->x.server) == NULL) ERR_OUT(errp);
	else if (Dz1SockAddr_cmp(server->peer, msg->peer) != 0 || Dz1SockAddr_cmp(server->local, msg->local) != 0) ERR_OUT(errp);
	else
	{
		Dz1Binary* stream = msg->stream;
		if (_Dz1ElasticBuf_push(server->rx_buf, stream->data, stream->size, errp) == FALSE) ERR_OUT(errp); // 소켓 버퍼에서 로컬 변수로 데이터 옮김
		else
		{
			Dz1Stream_drain(server->rx_stream, (size_t)stream->size, NULL, errp);

			bool_t is_complete_df = FALSE;
			if (GitsnDSRCMsgTestScenarioEnvUtil_insertDataFrame(env, stream, &is_complete_df, errp) == FALSE) ERR_OUT(errp);
			else
			{
				if (is_complete_df)
					GitsnDSRCMsgTestScenarioProc_sockProc(arg, env, timer, s, GitsnDSRCMsgScenarioEvent_data, NULL, errp);
				else Dz1Error_set(errp, 0);
			}

			stream = NULL;
			Dz1Error_set(errp, 0);
		}
	}

	return ret;
}

// DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED
static Dz1TaskProcStatus _server_client_disconnected(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	GitsnDSRCMsgTestScenarioArg* arg = (GitsnDSRCMsgTestScenarioArg*)uArg;
	GitsnDSRCMsgTestScenarioEnv* env = (GitsnDSRCMsgTestScenarioEnv*)uRsc;

	Dz1SockUtilReceiverReceived* msg = (Dz1SockUtilReceiverReceived*)Dz1TaskSigMsg_getData(*sg);
	Dz1Thread_printf("!!! Server Disconnected ] = \n");
	Dz1SockAddr_dump(msg->peer, 0);
	GitsnDSRCMsgScenario* s = NULL;
	if ((s = env->scenario) == NULL) ERR_OUT(errp);
	else
	{
		GitsnDSRCMsgTestScenarioProc_sockProc(arg, env, timer, s, GitsnDSRCMsgScenarioEvent_disconnected, NULL, errp);
		Dz1Error_set(errp, 0);
	}

	return ret;
}

// DZ1_SOCK_UTIL_TRANSMITER_SENT
static Dz1TaskProcStatus _server_sent(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	GitsnDSRCMsgTestScenarioArg* arg = (GitsnDSRCMsgTestScenarioArg*)uArg;
	GitsnDSRCMsgTestScenarioEnv* env = (GitsnDSRCMsgTestScenarioEnv*)uRsc;


	Dz1SockUtilTransmiterSent* msg = Dz1TaskSigMsg_getData(*sg);
	GitsnDSRCMsgSession* session = NULL;
	GitsnDSRCMsgServerSession* server = NULL;


	GitsnDSRCMsgScenario* s = NULL;
	if ((s = env->scenario) == NULL) ERR_OUT(errp);
	else if ((session = env->session) == NULL) ERR_OUT(errp);
	else if ((server = session->x.server) == NULL) ERR_OUT(errp);
	else if (Dz1SockAddr_cmp(msg->peer, server->peer) != 0 || Dz1SockAddr_cmp(msg->local, server->local) != 0) ERR_SET_OUT(errp, EFAULT);
	else
	{
		if (Dz1SockUtilTxFifo_sentProc(server->tx_fifo, server->sock, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}


bool_t GitsnDSRCMsgTestScenarioObu2Rsu_sockMsgInit(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (0) {}
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_ACCEPTOR_CONNECTED), _server_connected)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_ACCEPTOR_EXCEPTION), _server_connect_exception)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_RECEIVED), _server_received)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED), _server_client_disconnected)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_TRANSMITER_SENT), _server_sent)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

void GitsnDSRCMsgTestScenarioObu2Rsu_sockMsgClear(void* task)
{
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_ACCEPTOR_CONNECTED), _server_connected);
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_ACCEPTOR_EXCEPTION), _server_connect_exception);
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_RECEIVED), _server_received);
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED), _server_client_disconnected);
	Dz1Task_deregMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_TRANSMITER_SENT), _server_sent);
}































bool_t GitsnDSRCMsgTestScenarioProc_triggerPost(void* tSelf, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if ((*errp = Dz1Task_postSimple(tSelf, Dz1Task_getQueueID(tSelf), GITSN_DSRCMSG_TEST_SCENARIO_TRIGGER)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

bool_t GitsnDSRCMsgTestScenarioProc_trigger(GitsnDSRCMsgTestScenarioArg* arg, GitsnDSRCMsgTestScenarioEnv* env, void* timer, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GitsnDSRCMsgScenario* s = NULL;
	if ((s = env->scenario) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if (env->is_run == FALSE) ERR_SET_OUT(errp, EFAULT);
	else
	{
		bool_t is_complete = FALSE;
		/*switch (s->present)
		{
		case GitsnDSRCMsgScenarioPresent_serverRole:
			if (GitsnDSRCMsgTestScenarioProcServerRole_trigger(arg, env, timer, s->x.serverRole, &is_complete, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default: ERR_SET_OUT(errp, EFAULT);
			break;
		}*/
	}
	return ERR_IS_SUCCESS(errp);
}

static Dz1TaskProcStatus _task_scenarioTrigger(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	GitsnDSRCMsgTestScenarioArg* arg = (GitsnDSRCMsgTestScenarioArg*)uArg;
	GitsnDSRCMsgTestScenarioEnv* env = (GitsnDSRCMsgTestScenarioEnv*)uRsc;

	GitsnDSRCMsgScenario* s = env->scenario;
	if (s == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		GitsnDSRCMsgTestScenarioProc_trigger(arg, env, timer, NULL);
		Dz1Error_set(errp, 0);
	}
	return ret;
}

static Dz1TaskProcStatus _notify_info(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;


	GitsnDSRCMsgTestScenarioArg* arg = (GitsnDSRCMsgTestScenarioArg*)uArg;
	GitsnDSRCMsgTestScenarioEnv* env = (GitsnDSRCMsgTestScenarioEnv*)uRsc;

	GitsnDSRCMsgScenario* s = env->scenario;


	GitsnDSRCMsgNotifyInfoArg* msg = (GitsnDSRCMsgNotifyInfoArg*)Dz1TaskSigMsg_getData(*sg);
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (GitsnDSRCMsgTestScenarioEnvUtil_notifyInfoToMain(env, msg, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

static Dz1TaskProcStatus _notify_state(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	GitsnDSRCMsgTestScenarioArg* arg = (GitsnDSRCMsgTestScenarioArg*)uArg;
	GitsnDSRCMsgTestScenarioEnv* env = (GitsnDSRCMsgTestScenarioEnv*)uRsc;

	GitsnDSRCMsgScenario* s = env->scenario;


	GitsnDSRCMsgNotifyStateArg* msg = (GitsnDSRCMsgNotifyStateArg*)Dz1TaskSigMsg_getData(*sg);
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (GitsnDSRCMsgTestScenarioEnvUtil_notifyStateToMain(env, msg, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

static Dz1TaskProcStatus _notify_error(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	GitsnDSRCMsgTestScenarioArg* arg = (GitsnDSRCMsgTestScenarioArg*)uArg;
	GitsnDSRCMsgTestScenarioEnv* env = (GitsnDSRCMsgTestScenarioEnv*)uRsc;

	GitsnDSRCMsgScenario* s = env->scenario;


	GitsnDSRCMsgNotifyErrorArg* msg = (GitsnDSRCMsgNotifyErrorArg*)Dz1TaskSigMsg_getData(*sg);
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (GitsnDSRCMsgTestScenarioEnvUtil_notifyErrorToMain(env, msg, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

static Dz1TaskProcStatus _validate_request(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	GitsnDSRCMsgTestScenarioArg* arg = (GitsnDSRCMsgTestScenarioArg*)uArg;
	GitsnDSRCMsgTestScenarioEnv* env = (GitsnDSRCMsgTestScenarioEnv*)uRsc;

	GitsnDSRCMsgScenario* s = env->scenario;


	GitsnDSRCMsgValidateContextArg* msg = (GitsnDSRCMsgValidateContextArg*)Dz1TaskSigMsg_getData(*sg);
	if (arg == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (GitsnDSRCMsgTestScenarioEnvUtil_validateRequestToMain(env, msg, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

DZ1_CPPLINK bool_t GitsnDSRCMsgTestScenarioProc_msgInit(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (task == NULL) ERR_OUT(errp);
	// else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(GitsnDSRCMsg_TEST_SCENARIO_VALIDATE_RESPONSE), _received_validate_response)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(GITSN_DSRCMSG_TEST_SCENARIO_TRIGGER), _task_scenarioTrigger)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(GITSN_DSRCMSG_TEST_SCENARIO_NOTIFY_STATE), _notify_state)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(GITSN_DSRCMSG_TEST_SCENARIO_NOTIFY_ERROR), _notify_error)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(GITSN_DSRCMSG_TEST_SCENARIO_NOTIFY_INFO), _notify_info)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(GITSN_DSRCMSG_TEST_SCENARIO_VALIDATE_REQUEST), _validate_request)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}
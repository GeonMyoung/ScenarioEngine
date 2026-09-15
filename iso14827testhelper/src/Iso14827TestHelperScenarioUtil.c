#include <ItsIso14827.h>

#include "Iso14827TestHelperEnvUtil.h"
#include "Iso14827TestHelperScenarioUtil.h"


// init 함수 cleanup 시점 확인 필요
static Iso14827TestClientConnection* _init_client_connection(Dz1Str myDomain, Dz1Str ipaddr, u16_t peerport, Dz1Str user, Dz1Str pass, Dz1Error* errp)
{
	Iso14827TestClientConnection* ret = NULL;
	pthread_cleanup_push(Iso14827TestClientConnection_delAndSetNull, (void*)&ret);
	if ((ret = Iso14827TestClientConnection_new(Iso14827TestClientConnectionPresent_active, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active = Iso14827TestClientActive_new(NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->peer = ConfTestSocketAddress_new(ipaddr, peerport, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->account1 = Iso14827TestClientAccount_new(NULL, NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->account1->my_domain = Dz1Asn1UTF8Str_newFromStr(myDomain, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->account1->userid = Dz1Asn1UTF8Str_newFromStr(user, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->account1->passwd = Dz1Asn1UTF8Str_newFromStr(pass, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	pthread_cleanup_pop(errp->code); // (Iso14827TestClientConnection_delAndSetNull, (void*)&ret);
	return ret;
}

static Iso14827TestClientConnection* _init_duo_client_connection(Dz1Str myDomain, Dz1Str myDomain2, Dz1Str ipaddr, u16_t peerport, Dz1Str user, Dz1Str pass, Dz1Str user2, Dz1Str pass2, Dz1Error* errp)
{
	Iso14827TestClientConnection* ret = NULL;
	pthread_cleanup_push(Iso14827TestClientConnection_delAndSetNull, (void*)&ret);
	if ((ret = Iso14827TestClientConnection_new(Iso14827TestClientConnectionPresent_active, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active = Iso14827TestClientActive_new(NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->peer = ConfTestSocketAddress_new(ipaddr, peerport, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->account1 = Iso14827TestClientAccount_new(NULL, NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->account1->my_domain = Dz1Asn1UTF8Str_newFromStr(myDomain, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->account1->userid = Dz1Asn1UTF8Str_newFromStr(user, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->account1->passwd = Dz1Asn1UTF8Str_newFromStr(pass, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->account2 = Iso14827TestClientAccount_new(NULL, NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->account2->my_domain = Dz1Asn1UTF8Str_newFromStr(myDomain2, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->account2->userid = Dz1Asn1UTF8Str_newFromStr(user2, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active->account2->passwd = Dz1Asn1UTF8Str_newFromStr(pass2, errp)) == NULL) ERR_OUT(errp);

	else Dz1Error_set(errp, 0);
	pthread_cleanup_pop(errp->code); // (Iso14827TestClientConnection_delAndSetNull, (void*)&ret);
	return ret;
}
static Iso14827TestConnection* _init_passive_connection(u16_t localport, Dz1Error *errp)
{
	Iso14827TestConnection* ret = NULL;
	pthread_cleanup_push(Iso14827TestConnection_delAndSetNull, (void*)&ret);
	if ((ret = Iso14827TestConnection_new(Iso14827TestConnectionPresent_passive, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.passive = localport) < 0) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	pthread_cleanup_pop(errp->code); // (Iso14827TestConnection_delAndSetNull, (void*)&ret);
	return ret;
}

static Iso14827TestConnection* _init_active_connection(Dz1Str ipaddr, u16_t peerport, Dz1Error *errp)
{
	Iso14827TestConnection* ret = NULL;
	pthread_cleanup_push(Iso14827TestConnection_delAndSetNull, (void*)&ret);
	if ((ret = Iso14827TestConnection_new(Iso14827TestConnectionPresent_active, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->x.active = ConfTestSocketAddress_new(ipaddr, peerport, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	pthread_cleanup_pop(errp->code); // (Iso14827TestConnection_delAndSetNull, (void*)&ret);
	return ret;
}

static Iso14827TestAccount* _init_account(Dz1Str user, Dz1Str pass, Dz1Error* errp)
{
	Iso14827TestAccount* ret = NULL;
	pthread_cleanup_push(Iso14827TestAccount_delAndSetNull, (void*)&ret);
	if ((ret = Iso14827TestAccount_new(NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->authinfo = Dz1Asn1UTF8Str_newFromStr(Dz1T("ex_auth"), errp)) == NULL) ERR_OUT(errp);
	else if ((ret->userid = Dz1Asn1UTF8Str_newFromStr(user, errp)) == NULL) ERR_OUT(errp);
	else if ((ret->passwd = Dz1Asn1UTF8Str_newFromStr(pass, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	pthread_cleanup_pop(errp->code); // (Iso14827TestAccount_delAndSetNull, (void*)&ret);
	return ret;
}
//
//bool_t Iso14827TestClientRole1_init(Iso14827TestHelperEnv* env, Iso14827Test_ScenarioRoleIdx idx, Iso14827TestClientRole1Arg* arg, Dz1Error* errp)
//{
//	Iso14827TestClientConnection* connection = NULL;
//	pthread_cleanup_push(Iso14827TestClientConnection_delAndSetNull, (void*)&connection);
//	if ((connection = _init_client_connection(arg->myDomain, arg->ipaddr, arg->peerport, arg->user, arg->pass, errp)) == NULL) ERR_OUT(errp);
//	else
//	{
//		Iso14827TestClientRole1* ptr = NULL;
//		pthread_cleanup_push(Iso14827TestClientRole1_delAndSetNull, (void*)&ptr);
//		switch (idx)
//		{
//		case Iso14827Test_ScenarioRoleIdx_TechnicalRegulation1_ClientRole1:
//		case Iso14827Test_ScenarioRoleIdx_TechnicalRegulation2_RseToRse_ClientRole1:
//		case Iso14827Test_ScenarioRoleIdx_TechnicalRegulation2_RseToCenter_ClientRole1:
//			if ((ptr = Iso14827TestClientRole1_new(connection, NULL, arg->test_login_invalid, arg->test_login_duplicate, arg->test_session_maintain, NULL, NULL, NULL, NULL, Iso14827SubscriptionCancel_dataNotNeeded, errp)) == NULL) ERR_OUT(errp);
//			else if ((ptr->peer_domain = Dz1Asn1UTF8Str_newFromStr(arg->peerDomain, errp)) == NULL) ERR_OUT(errp);
//			else
//			{
//				if (arg->subs_normal_list != NULL && arg->subs_normal_list->count(arg->subs_normal_list) != 0)
//					ptr->subs_normal_list = SubscribeSpecList_clone(arg->subs_normal_list, errp);
//				if (arg->subs_invalid_list != NULL && arg->subs_invalid_list->count(arg->subs_invalid_list) != 0)
//					ptr->subs_invalid_list = SubscribeSpecList_clone(arg->subs_invalid_list, errp);
//				if (arg->subs_cancel != NULL)
//					ptr->subs_cancel = SubscribeSpecEntry_clone(arg->subs_cancel, errp);
//				if (arg->subs_pub_retry != NULL)
//					ptr->subs_pub_retry = SubscribeSpecEntry_clone(arg->subs_pub_retry, errp);
//
//				if ((env->config->scenario = Iso14827TestScenario_new(Iso14827TestScenarioPresent_client1, NULL, errp)) == NULL) ERR_OUT(errp);
//				else if ((env->config->scenario->x.client1 = Iso14827TestClientRole1_clone(ptr, errp)) == NULL) ERR_OUT(errp);
//				else
//				{
//					connection = NULL;
//					ptr = NULL;
//					Dz1Error_set(errp, 0);
//					Dz1Thread_printf("scenario initialize finish!!!!!\n");
//					Iso14827TestScenario_dump(env->config->scenario, 0);
//				}
//			}
//			break;
//		case Iso14827Test_ScenarioRoleIdx_TechnicalRegulation2_CenterToRse_ClientRole1:
//			if ((ptr = Iso14827TestClientRole1_new(connection, NULL, FALSE, FALSE, FALSE, NULL, NULL, NULL, NULL, Iso14827SubscriptionCancel_dataNotNeeded, errp)) == NULL) ERR_OUT(errp);
//			else if ((ptr->peer_domain = Dz1Asn1UTF8Str_newFromStr(arg->peerDomain, errp)) == NULL) ERR_OUT(errp);
//			else if ((ptr->subs_normal_list = SubscribeSpecList_clone(arg->subs_normal_list, errp)) == NULL) ERR_OUT(errp);
//			else if ((env->config->scenario = Iso14827TestScenario_new(Iso14827TestScenarioPresent_client1, NULL, errp)) == NULL) ERR_OUT(errp);
//			else if ((env->config->scenario->x.client1 = Iso14827TestClientRole1_clone(ptr, errp)) == NULL) ERR_OUT(errp);
//			else
//			{
//				connection = NULL;
//				ptr = NULL;
//				Dz1Error_set(errp, 0);
//			}
//			break;
//			default: ERR_SET_OUT(errp, EFAULT);  break;
//		}
//		pthread_cleanup_pop(1);// (Iso14827TestClientRole1_delAndSetNull, (void*)&ptr);
//	}
//	pthread_cleanup_pop(1); // (Iso14827TestClientConnection_delAndSetNull, (void*)&connection);
//
//	return ERR_IS_SUCCESS(errp);
//}
//
//bool_t Iso14827TestClientRole2_init(Iso14827TestHelperEnv* env, Iso14827Test_ScenarioRoleIdx idx, Iso14827TestClientRole2Arg* arg, Dz1Error* errp)
//{
//	Iso14827TestClientConnection* connection = NULL;
//	pthread_cleanup_push(Iso14827TestClientConnection_delAndSetNull, (void*)&connection);
//	if ((connection = _init_client_connection(arg->myDomain, arg->ipaddr, arg->peerport, arg->user, arg->pass, errp)) == NULL) ERR_OUT(errp);
//	else
//	{
//		Iso14827TestClientRole2* ptr = NULL;
//		pthread_cleanup_push(Iso14827TestClientRole2_delAndSetNull, (void*)&ptr);
//		switch (idx)
//		{
//		case Iso14827Test_ScenarioRoleIdx_TechnicalRegulation1_ClientRole2:
//		case Iso14827Test_ScenarioRoleIdx_TechnicalRegulation2_RseToRse_ClientRole2:
//			if ((ptr = Iso14827TestClientRole2_new(connection, NULL, NULL, arg->expireTime, Iso14827SubscriptionCancel_dataNotNeeded, errp)) == NULL) ERR_OUT(errp);
//			else if ((ptr->peer_domain = Dz1Asn1UTF8Str_newFromStr(arg->peerDomain, errp)) == NULL) ERR_OUT(errp);
//			else
//			{
//				if (arg->subs_total_list != NULL && arg->subs_total_list->count(arg->subs_total_list) != 0)
//					ptr->subs_total_list = SubscribeSpecList_clone(arg->subs_total_list, errp);
//
//				if ((env->config->scenario = Iso14827TestScenario_new(Iso14827TestScenarioPresent_client2, NULL, errp)) == NULL) ERR_OUT(errp);
//				else if ((env->config->scenario->x.client2 = Iso14827TestClientRole2_clone(ptr, errp)) == NULL) ERR_OUT(errp);
//				else
//				{
//					connection = NULL;
//					ptr = NULL;
//					Dz1Error_set(errp, 0);
//					Dz1Thread_printf("scenario initialize finish!!!!!\n");
//					Iso14827TestScenario_dump(env->config->scenario, 0);
//				}
//			}
//			break;
//		default:break;
//		}
//		pthread_cleanup_pop(1); // (Iso14827TestClientRole2_delAndSetNull, (void*)&ptr);
//	}
//	pthread_cleanup_pop(1); // (Iso14827TestClientConnection_delAndSetNull, (void*)&connection);
//	return ERR_IS_SUCCESS(errp);
//}
//
//bool_t Iso14827TestServerRole1_init(Iso14827TestHelperEnv* env, Iso14827Test_ScenarioRoleIdx idx, Iso14827TestServerRole1Arg* arg, Dz1Error* errp)
//{
//	Iso14827TestConnection* connection = NULL;
//	pthread_cleanup_push(Iso14827TestConnection_delAndSetNull, (void*)&connection);
//	if ((env->config->scenario = Iso14827TestScenario_new(Iso14827TestScenarioPresent_server1, NULL, errp)) == NULL) ERR_OUT(errp);
//	else if ((connection = _init_passive_connection(arg->localport, errp)) == NULL) ERR_OUT(errp);
//	else
//	{
//		Iso14827TestServerRole1* ptr = NULL;
//		pthread_cleanup_push(Iso14827TestServerRole1_delAndSetNull, (void*)&ptr);
//		switch (idx)
//		{
//		case Iso14827Test_ScenarioRoleIdx_TechnicalRegulation1_ServerRole1:
//		case Iso14827Test_ScenarioRoleIdx_TechnicalRegulation2_RseToRse_ServerRole1:
//		case Iso14827Test_ScenarioRoleIdx_TechnicalRegulation2_RseToCenter_ServerRole1:
//		case Iso14827Test_ScenarioRoleIdx_TechnicalRegulation2_CenterToRse_ServerRole1:
//			if ((ptr = Iso14827TestServerRole1_new(NULL, NULL, connection, arg->test_login_retry, NULL, arg->test_request_retry, arg->test_invalid_pub, NULL, errp)) == NULL) ERR_OUT(errp);
//			else if ((ptr->my_domain = Dz1Asn1UTF8Str_newFromStr(arg->myDomain, errp)) == NULL) ERR_OUT(errp);
//			else if ((ptr->peer_domain = Dz1Asn1UTF8Str_newFromStr(arg->peerDomain, errp)) == NULL) ERR_OUT(errp);
//			else
//			{
//				if (arg->test_subs != NULL)
//					ptr->test_subs = Iso14827TestServerRoleSubsList_clone(arg->test_subs, errp);
//
//				if ((env->config->scenario = Iso14827TestScenario_new(Iso14827TestScenarioPresent_server1, NULL, errp)) == NULL) ERR_OUT(errp);
//				else if ((env->config->scenario->x.server1 = Iso14827TestServerRole1_clone(ptr, errp)) == NULL) ERR_OUT(errp);
//				else
//				{
//					connection = NULL;
//					ptr = NULL;
//					Dz1Thread_printf("scenario initialize finish!!!!!\n");
//					Dz1Error_set(errp, 0);
//				}
//			}
//			break;
//		}
//		pthread_cleanup_pop(1); // (Iso14827TestServerRole1_delAndSetNull, (void*)&ptr);
//	}
//	pthread_cleanup_pop(1);// (Iso14827TestConnection_delAndSetNull, (void*)&connection);
//
//	return ERR_IS_SUCCESS(errp);
//}
//
//bool_t Iso14827TestServerRole2_init(Iso14827TestHelperEnv* env, Iso14827Test_ScenarioRoleIdx idx, Iso14827TestServerRole2Arg* arg, Dz1Error* errp)
//{
//	Iso14827TestConnection* connection = NULL;
//	pthread_cleanup_push(Iso14827TestConnection_delAndSetNull, (void*)&connection);
//	if ((connection = _init_passive_connection(arg->localport, errp)) == NULL) ERR_OUT(errp);
//	else
//	{
//		Iso14827TestServerRole2* ptr = NULL;
//		pthread_cleanup_push(Iso14827TestServerRole2_delAndSetNull, (void*)&ptr);
//		switch (idx)
//		{
//		case Iso14827Test_ScenarioRoleIdx_TechnicalRegulation1_ServerRole2:
//		case Iso14827Test_ScenarioRoleIdx_TechnicalRegulation2_RseToRse_ServerRole2:
//		case Iso14827Test_ScenarioRoleIdx_TechnicalRegulation2_CenterToRse_ServerRole2:
//		{
//			if ((ptr = Iso14827TestServerRole2_new(NULL, NULL, connection, arg->expireTime, Iso14827PublicationMgmt_terminateDataNoLongerAvailable, errp)) == NULL) ERR_OUT(errp);
//			else if ((ptr->my_domain = Dz1Asn1UTF8Str_newFromStr(arg->myDomain, errp)) == NULL) ERR_OUT(errp);
//			else if ((ptr->peer_domain = Dz1Asn1UTF8Str_newFromStr(arg->peerDomain, errp)) == NULL) ERR_OUT(errp);
//			else if ((env->config->scenario = Iso14827TestScenario_new(Iso14827TestScenarioPresent_server2, NULL, errp)) == NULL) ERR_OUT(errp);
//			else if ((env->config->scenario->x.server2 = Iso14827TestServerRole2_clone(ptr, errp)) == NULL) ERR_OUT(errp);
//			else
//			{
//				connection = NULL;
//				ptr = NULL;
//				Dz1Error_set(errp, 0);
//			}
//			break;
//		}
//		default:
//			break;
//		}
//		pthread_cleanup_pop(1); // (Iso14827TestServerRole2_delAndSetNull, (void*)&ptr);
//	}
//	pthread_cleanup_pop(1); // (Iso14827TestConnection_delAndSetNull, (void*)&connection);
//	return ERR_IS_SUCCESS(errp);
//}
//
//bool_t Iso14827TestDuoClientRole_init(Iso14827TestHelperEnv* env, Iso14827Test_ScenarioRoleIdx idx, Iso14827TestDuoClientRoleArg* arg, Dz1Error* errp)
//{
//	Iso14827TestClientConnection* connection = NULL;
//	pthread_cleanup_push(Iso14827TestClientConnection_delAndSetNull, (void*)&connection);
//	if ((connection = _init_duo_client_connection(arg->myDomain1, arg->myDomain2, arg->ipaddr, arg->peerport, arg->user, arg->pass, arg->user2, arg->pass2, errp)) == NULL) ERR_OUT(errp);
//	else
//	{
//		Iso14827TestDuoClientRole* ptr = NULL;
//		pthread_cleanup_push(Iso14827TestDuoClientRole_delAndSetNull, (void*)&ptr);
//		switch(idx)
//		{
//		case Iso14827Test_ScenarioRoleIdx_TechnicalRegulation1_DuoClientRole:
//		case Iso14827Test_ScenarioRoleIdx_TechnicalRegulation2_RseToRse_DuoClientRole:
//			if ((ptr = Iso14827TestDuoClientRole_new(connection, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
//			else if ((ptr->peer_domain = Dz1Asn1UTF8Str_newFromStr(arg->peerDomain, errp)) == NULL) ERR_OUT(errp);
//			else if ((ptr->subs_duo = SubscribeSpecDuo_clone(arg->subs_duo, errp)) == NULL) ERR_OUT(errp);
//			else if ((env->config->scenario = Iso14827TestScenario_new(Iso14827TestScenarioPresent_duo_client, NULL, errp)) == NULL) ERR_OUT(errp);
//			else if ((env->config->scenario->x.duo_client = Iso14827TestDuoClientRole_clone(ptr, errp)) == NULL) ERR_OUT(errp);
//			else
//			{
//				connection = NULL;
//				ptr = NULL;
//				Dz1Error_set(errp, 0);
//			}
//		}
//		pthread_cleanup_pop(1); // (Iso14827TestDuoClientRole_delAndSetNull, (void*)&ptr);
//	}
//	pthread_cleanup_pop(1); // (Iso14827TestClientConnection_delAndSetNull, (void*)&connection);
//	return ERR_IS_SUCCESS(errp);
//}
//
//bool_t Iso14827TestDuoSessionRole_init(Iso14827TestHelperEnv* env, Iso14827Test_ScenarioRoleIdx idx, Iso14827TestDuoSessionRoleArg* arg, Dz1Error* errp)
//{
//	Iso14827TestConnection* c_peer_server = NULL;
//	Iso14827TestConnection* s_peer_client = NULL;
//	Iso14827TestAccount* c_account = NULL;
//
//	pthread_cleanup_push(Iso14827TestConnection_delAndSetNull, (void*)&c_peer_server);
//	pthread_cleanup_push(Iso14827TestConnection_delAndSetNull, (void*)&s_peer_client);
//	pthread_cleanup_push(Iso14827TestAccount_delAndSetNull, (void*)&c_account);
//	if (0) {}
//	else if ((c_peer_server = _init_active_connection(arg->ipaddr, arg->peerport, errp)) == NULL) ERR_OUT(errp);
//	else if ((s_peer_client = _init_active_connection(arg->ipaddr, arg->peerport, errp)) == NULL) ERR_OUT(errp);
//	else if ((c_account = _init_account(arg->user, arg->pass, errp)) == NULL) ERR_OUT(errp);
//	else
//	{
//		Iso14827TestDuoSessionRole* ptr = NULL;
//		pthread_cleanup_push(Iso14827TestDuoSessionRole_delAndSetNull, (void*)&ptr);
//		switch (idx)
//		{
//		case Iso14827Test_ScenarioRoleIdx_TechnicalRegulation1_DuoSessionRole:
//		case Iso14827Test_ScenarioRoleIdx_TechnicalRegulation2_RseToRse_DuoSessionRole:
//		{
//			if ((ptr = Iso14827TestDuoSessionRole_new(NULL, NULL, c_peer_server, c_account, NULL, s_peer_client, errp)) == NULL) ERR_OUT(errp);
//			else if ((ptr->my_domain = Dz1Asn1UTF8Str_newFromStr(arg->myDomain, errp)) == NULL) ERR_OUT(errp);
//			else if ((ptr->peer_domain = Dz1Asn1UTF8Str_newFromStr(arg->peerClientDomain, errp)) == NULL) ERR_OUT(errp);
//			else if ((ptr->c_sub = SubscribeSpecEntry_clone(arg->c_sub, errp)) == NULL) ERR_OUT(errp);
//			else if ((env->config->scenario = Iso14827TestScenario_new(Iso14827TestScenarioPresent_duo_session, NULL, errp)) == NULL) ERR_OUT(errp);
//			else if ((env->config->scenario->x.duo_session = Iso14827TestDuoSessionRole_clone(ptr, errp)) == NULL) ERR_OUT(errp);
//			else
//			{
//				c_peer_server = NULL;
//				s_peer_client = NULL;
//				c_account = NULL;
//				ptr = NULL;
//				Dz1Error_set(errp, 0);
//			}
//			break;
//		}
//		default: break;
//		}
//		pthread_cleanup_pop(1); // (Iso14827TestDuoSessionRole_delAndSetNull, (void*)&ptr);
//	}
//	pthread_cleanup_pop(1); //(Iso14827TestAccount_delAndSetNull, (void*)&c_account);
//	pthread_cleanup_pop(1); //(Iso14827TestConnection_delAndSetNull, (void*)&s_peer_client);
//	pthread_cleanup_pop(1); //(Iso14827TestConnection_delAndSetNull, (void*)&c_peer_server);
//
//	return ERR_IS_SUCCESS(errp);
//}

///////////////////////////////////////////////////////////////////////////////
// misc utility
bool_t _client_reset_test_sub(Iso14827TestHelperEnv* env, Dz1Error* errp)
{
	SubscribeSpecList* temp = SubscribeSpecList_new(errp);
	if (temp == NULL) ERR_OUT(errp);
	else
	{
		SubscribeSpecList_delAndSetNull(&env->test_subs);
		env->test_subs = temp;
		temp = NULL;
	}
	return ERR_IS_SUCCESS(errp);
}
bool_t _client_init_test_subs(Iso14827TestHelperEnv* env, SubscribeSpecList* src, Dz1Error* errp)
{
	SubscribeSpecList* temp = SubscribeSpecList_clone(src, errp);
	if (temp == NULL) ERR_OUT(errp);
	else
	{
		SubscribeSpecList_delAndSetNull(&env->test_subs);
		env->test_subs = temp;
		temp = NULL;
	}
	return ERR_IS_SUCCESS(errp);
}
bool_t _client_init_test_sub(Iso14827TestHelperEnv* env, SubscribeSpecEntry* src, Dz1Error* errp)
{
	SubscribeSpecList* temp = SubscribeSpecList_new(errp);
	if (temp == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(SubscribeSpecList_delAndSetNull, (void*)&temp);
		if (SubscribeSpecList_cloneAndAppend(temp, src, errp) == FALSE) ERR_OUT(errp);
		else
		{
			SubscribeSpecList_delAndSetNull(&env->test_subs);
			env->test_subs = temp;
			temp = NULL;
		}
		pthread_cleanup_pop(1); // (SubscribeSpecList_delAndSetNull, (void*)&temp);
	}
	return ERR_IS_SUCCESS(errp);
}
bool_t _client_init_duo_subs(Iso14827TestHelperEnv* env, SubscribeSpecDuo* src, Dz1Error* errp)
{
	SubscribeSpecList* temp = SubscribeSpecList_new(errp);
	if (temp == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(SubscribeSpecList_delAndSetNull, (void*)&temp);
		if (0) {}
		else if (SubscribeSpecList_cloneAndAppend(temp, src->session1, errp) == FALSE) ERR_OUT(errp);
		else if (SubscribeSpecList_cloneAndAppend(temp, src->session2, errp) == FALSE) ERR_OUT(errp);
		else
		{
			SubscribeSpecList_delAndSetNull(&env->test_subs);
			env->test_subs = temp;
			temp = NULL;
		}
		pthread_cleanup_pop(1); // (SubscribeSpecList_delAndSetNull, (void*)&temp);
	}
	return ERR_IS_SUCCESS(errp);
}
// misc utility
///////////////////////////////////////////////////////////////////////////////
bool_t _client_init_duo_subs1(Iso14827TestHelperEnv* env, SubscribeSpecDuo* src, Dz1Error* errp)
{
	SubscribeSpecList* temp = SubscribeSpecList_new(errp);
	if (temp == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(SubscribeSpecList_delAndSetNull, (void*)&temp);
		if (0) {}
		else if (SubscribeSpecList_cloneAndAppend(temp, src->session1, errp) == FALSE) ERR_OUT(errp);
		else
		{
			SubscribeSpecList_delAndSetNull(&env->test_subs);
			env->test_subs = temp;
			temp = NULL;
		}
		pthread_cleanup_pop(1); // (SubscribeSpecList_delAndSetNull, (void*)&temp);
	}
	return ERR_IS_SUCCESS(errp);
}
bool_t _client_init_duo_subs2(Iso14827TestHelperEnv* env, SubscribeSpecDuo* src, Dz1Error* errp)
{
	SubscribeSpecList* temp = SubscribeSpecList_new(errp);
	if (temp == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(SubscribeSpecList_delAndSetNull, (void*)&temp);
		if (0) {}
		else if (SubscribeSpecList_cloneAndAppend(temp, src->session2, errp) == FALSE) ERR_OUT(errp);
		else
		{
			if (env->test_subs2 != NULL)
				SubscribeSpecList_delAndSetNull(&env->test_subs2);
			env->test_subs2 = temp;
			temp = NULL;
		}
		pthread_cleanup_pop(1); // (SubscribeSpecList_delAndSetNull, (void*)&temp);
	}
	return ERR_IS_SUCCESS(errp);
}
bool_t _client_util_subscribe(Iso14827TestHelperArg* arg, Dz1Asn1Codec selected_codec, Dz1Asn1UTF8Str* my_domain, Dz1Asn1UTF8Str* peer_domain, Iso14827TestAccount* acc, SubscribeSpecEntry* entry, Dz1Binary* eam, u32_t* ret_sid, Iso14827RejectSubscription* ret_result, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SubscribeSpecType* type = NULL;
	if ((type = entry->type) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		SubscribeSpecTypeRegistered* r = NULL;
		SubscribeSpecTypeReg* r_info = NULL;
		switch (type->present)
		{
		case SubscribeSpecTypePresent_single:
			if ((*errp = ItsIso14827_singleRequest(arg->t14827, ItsIso14827DomainType_client, my_domain, peer_domain, acc->userid, entry->priority, TRUE, entry->oid, eam->data, eam->size, ret_sid, ret_result)).code)
			{
				if (errp->code != EPERM || *ret_result == Iso14827RejectSubscription_max) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			else *ret_result = Iso14827RejectSubscription_max;
			break;
		case SubscribeSpecTypePresent_registered:
			if ((r = type->x.registered) == NULL || (r_info = r->reg_info) == NULL) ERR_SET_OUT(errp, EFAULT);
			else
			{
				switch (r_info->present)
				{
				case SubscribeSpecTypeRegPresent_continuous:
					if ((*errp = ItsIso14827_continuousRequest(arg->t14827, ItsIso14827DomainType_client, my_domain, peer_domain, acc->userid, FALSE, entry->priority, TRUE, r->is_periodic, r_info->x.continuous, entry->oid, eam->data, eam->size, ret_sid, ret_result)).code)
					{
						if (errp->code != EPERM || *ret_result == Iso14827RejectSubscription_max) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}
					else *ret_result = Iso14827RejectSubscription_max;
					break;
				case SubscribeSpecTypeRegPresent_daily:
					if ((*errp = ItsIso14827_dailyRequest(arg->t14827, ItsIso14827DomainType_client, my_domain, peer_domain, acc->userid, FALSE, entry->priority, TRUE, r->is_periodic, r_info->x.daily, entry->oid, eam->data, eam->size, ret_sid, ret_result)).code)
					{
						if (errp->code != EPERM || *ret_result == Iso14827RejectSubscription_max) ERR_OUT(errp);
						else Dz1Error_set(errp, 0);
					}
					else *ret_result = Iso14827RejectSubscription_max;
					break;
				default: ERR_SET_OUT(errp, EFAULT); break;
				}
			}
			break;
		default: ERR_SET_OUT(errp, EFAULT);
			break;
		}
	}

	return ERR_IS_SUCCESS(errp);
}

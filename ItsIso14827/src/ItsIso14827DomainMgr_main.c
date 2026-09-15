#include <dz1_gasn_support.h>
#include <ItsIso14827.h>

#include "ItsIso14827Env.h"
#include "ItsIso14827Timer.h"
#include "ItsIso14827Msg.h"
#include "ItsIso14827ServerDomain_main.h"
#include "ItsIso14827ClientDomain_main.h"
#include "ItsIso14827SessionMgr_main.h"
#include "ItsIso14827DomainMgr_main.h"
#include "ItsIso14827DomainMsg.h"

#ifdef __BORLANDC__
#pragma warn -8006
#endif

static void ItsIso14827DomainMgr_removeDomainMap(ItsIso14827DomainMgr *mgr, ItsIso14827SessionKey *skey)
{
	ItsIso14827DomainSessionEntry key = { skey };
	mgr->sessions->remove(mgr->sessions, &key);
}

///////////////////////////////////////////////////////////////////////////////
// Find API
ItsIso14827Domain *ItsIso14827DomainMgr_findByKey(ItsIso14827DomainMgr *mgr, ItsIso14827DomainKey *key)
{
	ItsIso14827Domain *ret = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (key == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ItsIso14827DomainPresent present = (ItsIso14827DomainPresent)key->type;
		if (present == ItsIso14827DomainPresent_server)
		{
			ItsIso14827ServerDomain _key = { key->name };
			ItsIso14827Domain dkey = { present, { &_key } };
			if ((ret = mgr->domains->find(mgr->domains, &dkey)) == NULL)
			{
				Dz1Thread_printf("Key = "); ItsIso14827DomainKey_dump(key, 0);
				Dz1Thread_printf("Domains = "); ItsIso14827DomainList_dump(mgr->domains, 0);
				ERR_SET_OUT(&err, ENOENT);
			}
		}
		else if (present == ItsIso14827DomainPresent_client)
		{
			ItsIso14827ClientDomain _key = { key->name };
			ItsIso14827Domain dkey = { present, { &_key } };
			if ((ret = mgr->domains->find(mgr->domains, &dkey)) == NULL)
			{
				Dz1Thread_printf("Key = "); ItsIso14827DomainKey_dump(key, 0);
				Dz1Thread_printf("Domains = "); ItsIso14827DomainList_dump(mgr->domains, 0);
				ERR_SET_OUT(&err, ENOENT);
			}
		}
		else ERR_SET_OUT(&err, EFAULT);
	}
	return ret;
}
/*
static ItsIso14827Domain *ItsIso14827DomainMgr_findBySession(ItsIso14827DomainMgr *mgr, ItsIso14827SessionKey *skey)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ItsIso14827Domain *ret = NULL;
	if (skey == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ItsIso14827DomainSessionEntry key = { skey }, *node = mgr->sessions->find(mgr->sessions, &key);
		if (node != NULL)
		{
			ItsIso14827DomainKey *dkey = node->domain;
			ret = ItsIso14827DomainMgr_findByKey(mgr, dkey);
		}
	}
	return ret;
}
*/
// Find API
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO_14827_DOMAIN_CREATE_SERVER
static Dz1Error ItsIso14827DomainMgr_createServer(ItsIso14827DomainMgr *mgr,
												  Dz1Asn1UTF8Str *name, u32_t maxClients,
												  ItsIso14827CodecOIDMapList **list,
												  ItsIso14827ServerDomainCallback *cbs)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827Domain *node = ItsIso14827Domain_new(ItsIso14827DomainPresent_server, NULL, &err);
	if (node == NULL) ERR_OUT(&err);
	else
	{
		ItsIso14827ServerDomain *server = NULL;
		pthread_cleanup_push(ItsIso14827Domain_delAndSetNull, (void *)&node);
		if ((node->x.server = server = ItsIso14827ServerDomain_new(NULL, maxClients, (*list), NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((server->name = Dz1Asn1UTF8Str_clone(name, &err)) == NULL) ERR_OUT(&err);
		else if ((server->callback = ItsIso14827ServerDomainCallback_clone(cbs, &err)) == NULL) ERR_OUT(&err);
		else if ((err = mgr->domains->add(mgr->domains, node)).code) ERR_OUT(&err);
		else
		{
			server->codecOidMap = (*list); (*list) = NULL;
			node = NULL;
		}
		pthread_cleanup_pop(err.code); // (ItsIso14827Domain_delAndSetNull, (void *)&node);
	}
	return err;
}

static Dz1TaskProcStatus _domainCreateServer(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainCreateServer *msg = (ItsIso14827DomainCreateServer *)Dz1TaskSigMsg_getData(*sg);

	if ((*errp = ItsIso14827DomainMgr_createServer(env->domainMgr, msg->name, msg->maxClient, &msg->codecOIDMap, msg->cbs)).code) ERR_OUT(errp);

	return ret;
}

static Dz1Error _createCodecOIDMapList(ItsIso14827DomainCreateServer *dst, ItsIso14827CodecOIDInfo userOIDMap[], size_t numOfMap)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (userOIDMap != NULL && numOfMap != 0)
	{
		size_t i;
		if ((dst->codecOIDMap = ItsIso14827CodecOIDMapList_new(&err)) == NULL) ERR_OUT(&err);
		else
		{
			ItsIso14827CodecOIDMap *node = NULL;
			pthread_cleanup_push(ItsIso14827CodecOIDMapList_delAndSetNull, (void *)&dst->codecOIDMap);
			for (i = 0; err.code == 0 && i < numOfMap; i++)
			{
				if ((node = ItsIso14827CodecOIDMap_new(NULL, userOIDMap[i].mean, &err)) == NULL) ERR_OUT(&err);
				else
				{
					pthread_cleanup_push(ItsIso14827CodecOIDMap_delAndSetNull, (void *)&node);
					if ((node->oid = Dz1Asn1OID_newFromStr(userOIDMap[i].oidStr, &err)) == NULL) ERR_OUT(&err);
					else if ((err = dst->codecOIDMap->add(dst->codecOIDMap, node)).code) ERR_OUT(&err);
					else node = NULL;
					pthread_cleanup_pop(1); // (ItsIso14827CodecOIDMap_delAndSetNull, (void *)&node);
				}
			}
			pthread_cleanup_pop(err.code); // (ItsIso14827CodecOIDMapList_delAndSetNull, (void *)&dst->codecOIDMap);
		}
	}
	return err;
}

Dz1Error ItsIso14827_createServer(void *t14827, Dz1Asn1UTF8Str *name, u32_t maxClient,
								  ItsIso14827CodecOIDInfo userOIDMap[], size_t numOfMap,
								  ItsIso14827ServerDomainCallback *cbs)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (t14827 == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (name == NULL || name->data == NULL || name->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (userOIDMap == NULL && numOfMap != 0) ERR_SET_OUT(&err, EINVAL);
	else if (maxClient == 0) ERR_SET_OUT(&err, EINVAL);
	else if (cbs == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ItsIso14827DomainCreateServer *msg = ItsIso14827DomainCreateServer_new(NULL, maxClient, NULL, NULL, &err);
		if (msg == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(ItsIso14827DomainCreateServer_delAndSetNull, (void *)&msg);
			if ((msg->name = Dz1Asn1UTF8Str_clone(name, &err)) == NULL) ERR_OUT(&err);
			else if ((err = _createCodecOIDMapList(msg, userOIDMap, numOfMap)).code) ERR_OUT(&err);
			else if ((msg->cbs = ItsIso14827ServerDomainCallback_clone(cbs, &err)) == NULL) ERR_OUT(&err);
			else if ((err = Dz1Task_call(t14827, DZ1_TASK_QUEUE_NONE, ITS_ISO_14827_DOMAIN_CREATE_SERVER, (void *)msg,
										(Dz1DumpFunc)ItsIso14827DomainCreateServer_dump, NULL, NULL)).code) ERR_OUT(&err);
			pthread_cleanup_pop(1); // (ItsIso14827DomainCreateServer_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}
// ITS_ISO_14827_DOMAIN_CREATE_SERVER
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO_14827_DOMAIN_DELETE_SERVER
static Dz1Error _ItsIso14827DomainMgr_deleteServer(void *ptr, ItsIso14827ServerDomainClientEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827SessionMgr *mgr = (ItsIso14827SessionMgr *)ptr;
	ItsIso14827SessionMgr_sessionDisconnect(mgr, p->key);
	return err;
}

static void ItsIso14827DomainMgr_deleteServer(ItsIso14827DomainMgr *mgr, Dz1Asn1UTF8Str *name, ItsIso14827SessionMgr *sessionMgr)
{
	ItsIso14827ServerDomain _key = { name }, *domain = NULL;
	ItsIso14827Domain key = { ItsIso14827DomainPresent_server, { &_key } }, *node = mgr->domains->extract(mgr->domains, &key);
	if (node)
	{
		pthread_cleanup_push(ItsIso14827Domain_delAndSetNull, (void *)&node);

		// Session 처리만 하면 Domain_del이 처리
		domain = node->x.server;
		domain->clients->travel(domain->clients, _ItsIso14827DomainMgr_deleteServer, (void *)sessionMgr);

		pthread_cleanup_pop(1); // (ItsIso14827Domain_del, (void *)node);
	}
}

static Dz1TaskProcStatus _domainDeleteServer(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	Dz1Asn1UTF8Str *name = (Dz1Asn1UTF8Str *)Dz1TaskSigMsg_getData(*sg);

	ItsIso14827DomainMgr_deleteServer(env->domainMgr, name, env->sessionMgr);

	return ret;
}

Dz1Error ItsIso14827_deleteServer(void *t14827, Dz1Asn1UTF8Str *name)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (t14827 == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Dz1Asn1UTF8Str *msg = Dz1Asn1UTF8Str_clone(name, &err);
		if (msg == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&msg);
			if ((err = Dz1Task_call(t14827, DZ1_TASK_QUEUE_NONE, ITS_ISO_14827_DOMAIN_DELETE_SERVER, (void *)msg,
									(Dz1DumpFunc)Dz1Asn1UTF8Str_dump, NULL, NULL)).code) ERR_OUT(&err);
			pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}
// ITS_ISO_14827_DOMAIN_DELETE_SERVER
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO_14827_DOMAIN_CREATE_CLIENT
static Dz1Error ItsIso14827DomainMgr_createClient(ItsIso14827DomainMgr *mgr,
												  Dz1Asn1UTF8Str *name,
												  ItsIso14827ClientDomainCallback *cbs)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827Domain *node = ItsIso14827Domain_new(ItsIso14827DomainPresent_client, NULL, &err);
	if (node == NULL) ERR_OUT(&err);
	else
	{
		ItsIso14827ClientDomain *client = NULL;
		pthread_cleanup_push(ItsIso14827Domain_delAndSetNull, (void *)&node);
		if ((node->x.client = client = ItsIso14827ClientDomain_new(NULL, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((client->name = Dz1Asn1UTF8Str_clone(name, &err)) == NULL) ERR_OUT(&err);
		else if ((client->callback = ItsIso14827ClientDomainCallback_clone(cbs, &err)) == NULL) ERR_OUT(&err);
		else if ((err = mgr->domains->add(mgr->domains, node)).code) ERR_OUT(&err);
		else node = NULL;
		pthread_cleanup_pop(err.code); // (ItsIso14827Domain_delAndSetNull, (void *)&node);
	}
	return err;
}

static Dz1TaskProcStatus _domainCreateClient(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainCreateClient *msg = (ItsIso14827DomainCreateClient *)Dz1TaskSigMsg_getData(*sg);

	if ((*errp = ItsIso14827DomainMgr_createClient(env->domainMgr, msg->name, msg->cbs)).code) ERR_OUT(errp);

	return ret;
}

Dz1Error ItsIso14827_createClient(void *t14827, Dz1Asn1UTF8Str *name, ItsIso14827ClientDomainCallback *cbs)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (t14827 == NULL || cbs == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (name == NULL || name->data == NULL || name->size == 0) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ItsIso14827DomainCreateClient *msg = ItsIso14827DomainCreateClient_new(NULL, NULL, &err);
		if (msg == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(ItsIso14827DomainCreateClient_delAndSetNull, (void *)&msg);
			if ((msg->name = Dz1Asn1UTF8Str_clone(name, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->cbs = ItsIso14827ClientDomainCallback_clone(cbs, &err)) == NULL) ERR_OUT(&err);
			else if ((err = Dz1Task_call(t14827, DZ1_TASK_QUEUE_NONE, ITS_ISO_14827_DOMAIN_CREATE_CLIENT, (void *)msg,
										(Dz1DumpFunc)ItsIso14827DomainCreateClient_dump, NULL, NULL)).code) ERR_OUT(&err);
			pthread_cleanup_pop(1); // (ItsIso14827DomainCreateClient_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}
// ITS_ISO_14827_DOMAIN_CREATE_CLIENT
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO_14827_DOMAIN_DELETE_CLIENT
static Dz1Error _ItsIso14827DomainMgr_deleteClient(void *ptr, ItsIso14827ClientDomainServerEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827SessionMgr *mgr = (ItsIso14827SessionMgr *)ptr;
	ItsIso14827SessionMgr_sessionDisconnect(mgr, p->key);
	return err;
}

static void ItsIso14827DomainMgr_deleteClient(ItsIso14827DomainMgr *mgr, Dz1Asn1UTF8Str *name, ItsIso14827SessionMgr *sessionMgr)
{
	ItsIso14827ClientDomain _key = { name }, *domain = NULL;
	ItsIso14827Domain key = { ItsIso14827DomainPresent_client, { &_key } }, *node = mgr->domains->extract(mgr->domains, &key);
	if (node)
	{
		pthread_cleanup_push(ItsIso14827Domain_delAndSetNull, (void *)&node);
		// Session 처리만 하면 Domain_del이 처리
		domain = node->x.client;
		domain->servers->travel(domain->servers, _ItsIso14827DomainMgr_deleteClient, (void *)sessionMgr);
		pthread_cleanup_pop(1); // (ItsIso14827Domain_del, (void *)node);
	}
}

static Dz1TaskProcStatus _domainDeleteClient(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	Dz1Asn1UTF8Str *name = (Dz1Asn1UTF8Str *)Dz1TaskSigMsg_getData(*sg);

	ItsIso14827DomainMgr_deleteClient(env->domainMgr, name, env->sessionMgr);

	return ret;
}

Dz1Error ItsIso14827_deleteClient(void *t14827, Dz1Asn1UTF8Str *name)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (t14827 == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (name == NULL || name->data == NULL || name->size == 0) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Dz1Asn1UTF8Str *msg = Dz1Asn1UTF8Str_clone(name, &err);		
		if (msg == NULL)
		{
			ERR_OUT(&err);
		}
		else
		{
			pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&msg);
			if ((err = Dz1Task_call(t14827, DZ1_TASK_QUEUE_NONE,
									ITS_ISO_14827_DOMAIN_DELETE_CLIENT, (void *)msg,
									(Dz1DumpFunc)Dz1Asn1UTF8Str_dump, NULL, NULL)).code) ERR_OUT(&err);
			pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}
// ITS_ISO_14827_DOMAIN_DELETE_CLIENT
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO14827_DOMAIN_LOGIN_ACCEPT
static Dz1Error ItsIso14827DomainMgr_loginAccept(ItsIso14827DomainMgr *mgr,
												 Dz1Asn1UTF8Str *domainName,
												 Dz1Asn1UTF8Str *peerName, Dz1Asn1OctetStr *user,
												 Dz1Asn1Codec selectedCodec, ItsIso14827CRCCheck CRCMode,
												 ItsIso14827ServerDomainViolatedPublication *violatedPub,
												 void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827DomainKey key = { ItsIso14827DomainType_server, domainName };
	ItsIso14827Domain *domain = ItsIso14827DomainMgr_findByKey(mgr, &key);
	if (domain == NULL) ERR_SET_OUT(&err, ENOENT);
	else if ((err = ItsIso14827ServerDomain_loginAccept(domain->x.server, peerName, user,
														selectedCodec, CRCMode, violatedPub,
														uArg, uRsc, timer)).code) ERR_OUT(&err);
	return err;
}

static Dz1TaskProcStatus _loginAccept(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainLoginAccept *msg = (ItsIso14827DomainLoginAccept *)Dz1TaskSigMsg_getData(*sg);

	if ((*errp = ItsIso14827DomainMgr_loginAccept(env->domainMgr, msg->domainName,
												msg->peerName, msg->user,
												msg->selectedCodec, msg->CRCMode,
												msg->violatedPub,
												uArg, uRsc, timer)).code) ERR_OUT(errp);
	return ret;
}

Dz1Error _ItsIso14827_loginAccept(void *t14827, Dz1Asn1UTF8Str *domainName,
								 Dz1Asn1UTF8Str *peerName, Dz1Asn1OctetStr *user,
								 Dz1Asn1Codec selectedCodec, ItsIso14827CRCCheck CRCMode,
								 ItsIso14827CallbackPublication violatedPubRecv, void *violatedPubRecvParam)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827DomainLoginAccept *msg = NULL;
	if (t14827 == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (domainName == NULL || domainName->data == NULL || domainName->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (peerName == NULL || peerName->data == NULL || peerName->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (user == NULL || user->data == NULL || user->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (selectedCodec <= 0 || selectedCodec >= Dz1Asn1Codec_max) ERR_SET_OUT(&err, EINVAL);
	else if (CRCMode < 0 || CRCMode >= ItsIso14827CRCCheck_max) ERR_SET_OUT(&err, EINVAL);
	else if ((msg = ItsIso14827DomainLoginAccept_new(NULL, NULL, NULL, selectedCodec, CRCMode, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(ItsIso14827DomainLoginAccept_delAndSetNull, (void *)&msg);
		if ((msg->domainName = Dz1Asn1UTF8Str_clone(domainName, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->peerName = Dz1Asn1UTF8Str_clone(peerName, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->user = Dz1Asn1OctetStr_clone(user, &err)) == NULL) ERR_OUT(&err);
		else if (violatedPubRecv != NULL && (msg->violatedPub = ItsIso14827ServerDomainViolatedPublication_new(violatedPubRecv, violatedPubRecvParam, &err)) == NULL) ERR_OUT(&err);
		else if ((err = Dz1Task_post(t14827, DZ1_TASK_QUEUE_NONE,
									ITS_ISO14827_DOMAIN_LOGIN_ACCEPT, (void **)&msg,
									(Dz1DelFunc)ItsIso14827DomainLoginAccept_del,
									(Dz1DumpFunc)ItsIso14827DomainLoginAccept_dump,
									NULL, NULL, NULL)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (ItsIso14827DomainLoginAccept_delAndSetNull, (void *)&msg);
	}
	return err;
}
// ITS_ISO14827_DOMAIN_LOGIN_ACCEPT
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO14827_DOMAIN_LOGIN_REJECT
static Dz1Error ItsIso14827DomainMgr_loginReject(ItsIso14827DomainMgr *mgr, ItsIso14827SessionMgr *sessionMgr,
												 Dz1Asn1UTF8Str *domainName,
												 Dz1Asn1UTF8Str *peerName, Dz1Asn1OctetStr *user,
												 Iso14827RejectLogin reason,
												 void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827DomainKey key = { ItsIso14827DomainType_server, domainName };
	ItsIso14827Domain *domain = ItsIso14827DomainMgr_findByKey(mgr, &key);
	ItsIso14827SessionKey *skey = NULL;
	if (domain == NULL) ERR_SET_OUT(&err, ENOENT);
	else if ((skey = ItsIso14827ServerDomain_loginReject(domain->x.server, peerName, user,
														reason, uArg, uRsc, timer, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(ItsIso14827SessionKey_delAndSetNull, (void *)&skey);

		ItsIso14827DomainMgr_removeDomainMap(mgr, skey);
		ItsIso14827SessionMgr_sessionDisconnect(sessionMgr, skey);

		pthread_cleanup_pop(1); // (ItsIso14827SessionKey_delAndSetNull, (void *)&skey);
	}
	return err;
}

static Dz1TaskProcStatus _loginReject(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainLoginReject *msg = (ItsIso14827DomainLoginReject *)Dz1TaskSigMsg_getData(*sg);

	if ((*errp = ItsIso14827DomainMgr_loginReject(env->domainMgr, env->sessionMgr,
												  msg->domainName,
												  msg->peerName, msg->user,
												  msg->reason,
												  uArg, uRsc, timer)).code) ERR_OUT(errp);
	return ret;
}

Dz1Error ItsIso14827_loginReject(void *t14827, Dz1Asn1UTF8Str *domainName,
								 Dz1Asn1UTF8Str *peerName, Dz1Asn1OctetStr *user,
								 Iso14827RejectLogin reason)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827DomainLoginReject *msg = NULL;
	if (t14827 == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (domainName == NULL || domainName->data == NULL || domainName->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (peerName == NULL || peerName->data == NULL || peerName->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (user == NULL || user->data == NULL || user->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (reason < 0 || reason >= Iso14827RejectLogin_max) ERR_SET_OUT(&err, EINVAL);
	else if ((msg = ItsIso14827DomainLoginReject_new(NULL, NULL, NULL, reason, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(ItsIso14827DomainLoginReject_delAndSetNull, (void *)&msg);
		if ((msg->domainName = Dz1Asn1UTF8Str_clone(domainName, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->peerName = Dz1Asn1UTF8Str_clone(peerName, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->user = Dz1Asn1OctetStr_clone(user, &err)) == NULL) ERR_OUT(&err);
		else if ((err = Dz1Task_post(t14827, DZ1_TASK_QUEUE_NONE,
									ITS_ISO14827_DOMAIN_LOGIN_REJECT, (void **)&msg,
									(Dz1DelFunc)ItsIso14827DomainLoginReject_del,
									(Dz1DumpFunc)ItsIso14827DomainLoginReject_dump,
									NULL, NULL, NULL)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (ItsIso14827DomainLoginReject_delAndSetNull, (void *)&msg);
	}
	return err;
}
// ITS_ISO14827_DOMAIN_LOGIN_REJECT
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO14827_DOMAIN_ECHO_REPLY
Dz1Error ItsIso14827DomainMgr_echoReply(ItsIso14827DomainMgr *mgr,
										Dz1Asn1UTF8Str *domainName,
										Dz1Asn1UTF8Str *peerName, Dz1Asn1OctetStr *user,
										u32_t confirmPktNbr,
										void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827DomainKey key = { ItsIso14827DomainType_server, domainName };
	ItsIso14827Domain *domain = ItsIso14827DomainMgr_findByKey(mgr, &key);
	if (domain == NULL) ERR_SET_OUT(&err, ENOENT);
	else if ((err = ItsIso14827ServerDomain_echoReply(domain->x.server, peerName, user,
													confirmPktNbr, uArg, uRsc, timer)).code) ERR_OUT(&err);
	return err;
}

static Dz1TaskProcStatus _echoReply(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainEchoReply *msg = (ItsIso14827DomainEchoReply *)Dz1TaskSigMsg_getData(*sg);

	if ((*errp = ItsIso14827DomainMgr_echoReply(env->domainMgr, msg->domainName,
												msg->peerName, msg->user,
												msg->confirmPktNbr,
												uArg, uRsc, timer)).code) ERR_OUT(errp);
	return ret;
}

Dz1Error ItsIso14827_echoReply(void *t14827, Dz1Asn1UTF8Str *domainName,
							   Dz1Asn1UTF8Str *peerName, Dz1Asn1OctetStr *user,
							   u32_t confirmPktNbr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827DomainEchoReply *msg = NULL;
	if (t14827 == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (domainName == NULL || domainName->data == NULL || domainName->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (peerName == NULL || peerName->data == NULL || peerName->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (user == NULL || user->data == NULL || user->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if ((msg = ItsIso14827DomainEchoReply_new(NULL, NULL, NULL, confirmPktNbr, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(ItsIso14827DomainEchoReply_delAndSetNull, (void *)&msg);
		if ((msg->domainName = Dz1Asn1UTF8Str_clone(domainName, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->peerName = Dz1Asn1UTF8Str_clone(peerName, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->user = Dz1Asn1OctetStr_clone(user, &err)) == NULL) ERR_OUT(&err);
		else if ((err = Dz1Task_post(t14827, DZ1_TASK_QUEUE_NONE,
									ITS_ISO14827_DOMAIN_ECHO_REPLY, (void **)&msg,
									(Dz1DelFunc)ItsIso14827DomainEchoReply_del,
									(Dz1DumpFunc)ItsIso14827DomainEchoReply_dump,
									NULL, NULL, NULL)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (ItsIso14827DomainEchoReply_delAndSetNull, (void *)&msg);
	}
	return err;
}
// ITS_ISO14827_DOMAIN_ECHO_REPLY
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO14827_DOMAIN_PREPARE_ACCEPT
static Dz1Error ItsIso14827DomainMgr_prepareAccept(ItsIso14827DomainMgr *mgr,ItsIso14827DomainType domainType, Dz1Asn1UTF8Str *domainName,
												   Dz1Asn1UTF8Str *peerName, Dz1Asn1OctetStr *user, u32_t serial,
												   void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827DomainKey key = { domainType, domainName };
	ItsIso14827Domain *domain = ItsIso14827DomainMgr_findByKey(mgr, &key);
	if (domain == NULL) ERR_SET_OUT(&err, ENOENT);
	else
	{
		switch(domain->present)
		{
		case ItsIso14827DomainPresent_server:
			if ((err = ItsIso14827ServerDomain_prepareAccept(domain->x.server, peerName, user, serial, uArg, uRsc, timer)).code) ERR_OUT(&err);
			break;
		case ItsIso14827DomainPresent_client:
			break;
		default:
			ERR_SET_OUT(&err, EINVAL);
			break;
		}
	}
	return err;
}

static Dz1TaskProcStatus _prepareAccept(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainPrepareAccept *msg = (ItsIso14827DomainPrepareAccept *)Dz1TaskSigMsg_getData(*sg);

	if ((*errp = ItsIso14827DomainMgr_prepareAccept(env->domainMgr, msg->domainType, msg->domainName,
													msg->peerName, msg->user,
													msg->serial,
													uArg, uRsc, timer)).code) ERR_OUT(errp);
	return ret;
}

Dz1Error ItsIso14827_prepareAccept(void *t14827, ItsIso14827DomainType domainType, Dz1Asn1UTF8Str *domainName, Dz1Asn1UTF8Str *peerName, Dz1Asn1OctetStr *user, u32_t serial)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827DomainPrepareAccept *msg = NULL;
	if (t14827 == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (domainName == NULL || domainName->data == NULL || domainName->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (peerName == NULL || peerName->data == NULL || peerName->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (user == NULL || user->data == NULL || user->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if ((msg = ItsIso14827DomainPrepareAccept_new(domainType, NULL, NULL, NULL, serial, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(ItsIso14827DomainPrepareAccept_delAndSetNull, (void *)&msg);
		if ((msg->domainName = Dz1Asn1UTF8Str_clone(domainName, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->peerName = Dz1Asn1UTF8Str_clone(peerName, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->user = Dz1Asn1OctetStr_clone(user, &err)) == NULL) ERR_OUT(&err);
		else if ((err = Dz1Task_post(t14827, DZ1_TASK_QUEUE_NONE,
									ITS_ISO14827_DOMAIN_PREPARE_ACCEPT, (void **)&msg,
									(Dz1DelFunc)ItsIso14827DomainPrepareAccept_del,
									(Dz1DumpFunc)ItsIso14827DomainPrepareAccept_dump,
									NULL, NULL, NULL)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (ItsIso14827DomainPrepareAccept_delAndSetNull, (void *)&msg);
	}
	return err;
}
// ITS_ISO14827_DOMAIN_PREPARE_ACCEPT
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO14827_DOMAIN_PREPARE_REJECT
static Dz1Error ItsIso14827DomainMgr_prepareReject(ItsIso14827DomainMgr *mgr,
												   ItsIso14827DomainType domainType, Dz1Asn1UTF8Str *domainName,
												   Dz1Asn1UTF8Str *peerName, Dz1Asn1OctetStr *user,
												   u32_t serial, Iso14827RejectSubscription reason,
												   void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827DomainKey key = { domainType, domainName };
	ItsIso14827Domain *domain = ItsIso14827DomainMgr_findByKey(mgr, &key);
	if (domain == NULL) ERR_SET_OUT(&err, ENOENT);
	else
	{
		switch(domain->present)
		{
		case ItsIso14827DomainPresent_server:
			if ((err = ItsIso14827ServerDomain_prepareReject(domain->x.server, peerName, user,
															serial, reason,
															uArg, uRsc, timer)).code) ERR_OUT(&err);
			break;
		case ItsIso14827DomainPresent_client:
			break;
		default:
			ERR_SET_OUT(&err, EINVAL);
			break;
		}
	}
	return err;
}

static Dz1TaskProcStatus _prepareReject(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainPrepareReject *msg = (ItsIso14827DomainPrepareReject *)Dz1TaskSigMsg_getData(*sg);

	if ((*errp = ItsIso14827DomainMgr_prepareReject(env->domainMgr, msg->domainType, msg->domainName,
													msg->peerName, msg->user,
													msg->serial, msg->reason,
													uArg, uRsc, timer)).code) ERR_OUT(errp);
	return ret;
}

Dz1Error ItsIso14827_prepareReject(void *t14827,
								   ItsIso14827DomainType domainType, Dz1Asn1UTF8Str *domainName,
								   Dz1Asn1UTF8Str *peerName,
								   Dz1Asn1OctetStr *user,
								   u32_t serial,
								   Iso14827RejectSubscription reason)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827DomainPrepareReject *msg = NULL;
	if (t14827 == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (domainName == NULL || domainName->data == NULL || domainName->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (peerName == NULL || peerName->data == NULL || peerName->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (user == NULL || user->data == NULL || user->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (reason < 0 || reason >= Iso14827RejectSubscription_max) ERR_SET_OUT(&err, EINVAL);
	else if ((msg = ItsIso14827DomainPrepareReject_new(domainType, NULL, NULL, NULL, serial, reason, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(ItsIso14827DomainPrepareReject_delAndSetNull, (void *)&msg);
		if ((msg->domainName = Dz1Asn1UTF8Str_clone(domainName, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->peerName = Dz1Asn1UTF8Str_clone(peerName, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->user = Dz1Asn1OctetStr_clone(user, &err)) == NULL) ERR_OUT(&err);
		else if ((err = Dz1Task_post(t14827, DZ1_TASK_QUEUE_NONE,
									ITS_ISO14827_DOMAIN_PREPARE_REJECT, (void **)&msg,
									(Dz1DelFunc)ItsIso14827DomainPrepareReject_del,
									(Dz1DumpFunc)ItsIso14827DomainPrepareReject_dump,
									NULL, NULL, NULL)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (ItsIso14827DomainPrepareReject_delAndSetNull, (void *)&msg);
	}
	return err;
}
// ITS_ISO14827_DOMAIN_PREPARE_REJECT
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO14827_DOMAIN_DATA_PROVIDE
static Dz1Error ItsIso14827DomainMgr_dataProvide(ItsIso14827DomainMgr *mgr,
												 ItsIso14827DomainType domainType, Dz1Asn1UTF8Str *domainName,
												 Dz1Asn1UTF8Str *peerName, Dz1Asn1OctetStr *user,
												 u32_t serial, Iso14827EndAppMsg **eam,
												 void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827DomainKey key = { domainType, domainName };
	ItsIso14827Domain *domain = ItsIso14827DomainMgr_findByKey(mgr, &key);
	if (domain == NULL) ERR_SET_OUT(&err, ENOENT);
	else
	{
		switch(domain->present)
		{
		case ItsIso14827DomainPresent_server:
			if ((err = ItsIso14827ServerDomain_dataProvide(domain->x.server, peerName, user, serial, eam, uArg, uRsc, timer)).code) ERR_OUT(&err);
			break;
		case ItsIso14827DomainPresent_client:
			break;
		default:
			ERR_SET_OUT(&err, EINVAL);
			break;
		}
	}
	return err;
}

static Dz1TaskProcStatus _dataProvide(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainDataProvide *msg = (ItsIso14827DomainDataProvide *)Dz1TaskSigMsg_getData(*sg);

	if ((*errp = ItsIso14827DomainMgr_dataProvide(env->domainMgr, msg->domainType, msg->domainName,
												msg->peerName, msg->user,
												msg->serial, &msg->eam,
												uArg, uRsc, timer)).code) ERR_OUT(errp);
	return ret;
}

Dz1Error ItsIso14827_dataProvide(void *t14827, ItsIso14827DomainType domainType,
								 Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerName,
								 Dz1Asn1OctetStr *user, u32_t subSerial,
								 str_t oidStr, u8_t *encoddedEndAppMsg, size_t encoddedEndAppMsgSize)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827DomainDataProvide *msg = NULL;
	if (t14827 == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (myDomain == NULL || myDomain->data == NULL || myDomain->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (peerName == NULL || peerName->data == NULL || peerName->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (user == NULL || user->data == NULL || user->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if ((msg = ItsIso14827DomainDataProvide_new(domainType, NULL, NULL, NULL, subSerial, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		Iso14827EndAppMsg *eam = NULL;
		pthread_cleanup_push(ItsIso14827DomainDataProvide_delAndSetNull, (void *)&msg);
		if ((msg->domainName = Dz1Asn1UTF8Str_clone(myDomain, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->peerName = Dz1Asn1UTF8Str_clone(peerName, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->user = Dz1Asn1OctetStr_clone(user, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->eam = eam = Iso14827EndAppMsg_new(NULL, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((eam->oid = Dz1Asn1OID_newFromStr(oidStr, &err)) == NULL) ERR_OUT(&err);
		else if ((eam->data = Dz1Asn1Any_new(encoddedEndAppMsg, (u32_t)encoddedEndAppMsgSize, &err)) == NULL) ERR_OUT(&err);
		else if ((err = Dz1Task_post(t14827, DZ1_TASK_QUEUE_NONE,
									ITS_ISO14827_DOMAIN_DATA_PROVIDE, (void **)&msg,
									(Dz1DelFunc)ItsIso14827DomainDataProvide_del,
									(Dz1DumpFunc)ItsIso14827DomainDataProvide_dump,
									NULL, NULL, NULL)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (ItsIso14827DomainDataProvide_delAndSetNull, (void *)&msg);
	}
	return err;
}
// ITS_ISO14827_DOMAIN_DATA_PROVIDE
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO14827_DOMAIN_VIOLOTED_PUB
static Dz1TaskProcStatus _violatedPub(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainMgr *domainMgr = env->domainMgr;

	ItsIso14827ViolatedPublication *msg = (ItsIso14827ViolatedPublication *)Dz1TaskSigMsg_getData(*sg);

	ItsIso14827DomainKey key = { msg->domainType, msg->myDomain };
	ItsIso14827Domain *domain = ItsIso14827DomainMgr_findByKey(domainMgr, &key);
	if (domain == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		switch(domain->present)
		{
		case ItsIso14827DomainPresent_server:
			if ((*errp = ItsIso14827ServerDomain_violatedPub(domain->x.server, msg->peerDomain, msg->user, &msg->pub, uArg, uRsc, timer)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case ItsIso14827DomainPresent_client:
			if ((*errp = ItsIso14827ClientDomain_violatedPub(domain->x.client, msg->peerDomain, msg->user, &msg->pub, uArg, uRsc, timer)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}

	return ret;
}

static Iso14827Publication *_generatePublication(bool_t guaranteed, u32_t subsSerial, u32_t pubSerial, bool_t isLated,
												 str_t oidStr, u8_t *msgBody, size_t msgSize, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	Iso14827Publication *pub = NULL;
	if ((pub = Iso14827Publication_new(guaranteed, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Iso14827PublishFormat *fmt = NULL;
		Iso14827PublicationDataList *dataList = NULL;
		Iso14827PublicationData *node = NULL;
		pthread_cleanup_push(Iso14827Publication_delAndSetNull, (void *)&pub);
		if ((pub->fmt = fmt = Iso14827PublishFormat_new(Iso14827PublishFormatPresent_dataList, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((fmt->x.dataList = dataList = Iso14827PublicationDataList_new(errp)) == NULL) ERR_OUT(errp);
		else if ((node = Iso14827PublicationData_new(subsSerial, pubSerial, isLated, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Iso14827PublicationType *type = NULL;
			Iso14827EndAppMsg *eam = NULL;
			pthread_cleanup_push(Iso14827PublicationData_delAndSetNull, (void *)&node);
			if ((node->type = type = Iso14827PublicationType_new(Iso14827PublicationTypePresent_msg, NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((type->x.msg = eam = Iso14827EndAppMsg_new(NULL, NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((eam->oid = Dz1Asn1OID_newFromStr(oidStr, errp)) == NULL) ERR_OUT(errp);
			else if ((eam->data = Dz1Asn1Any_new(msgBody, (u32_t)msgSize, errp)) == NULL) ERR_OUT(errp);
			else if ((*errp = dataList->add(dataList, node)).code) ERR_OUT(errp);
			else node = NULL;
			pthread_cleanup_pop(1); // (Iso14827PublicationData_delAndSetNull, (boid *)&node);
		}
		pthread_cleanup_pop(errp->code); // (Iso14827Publication_delAndSetNull, (void *)&pub);
	}
	return pub;
}

Dz1Error ItsIso14827_violatedPub(void *t14827, ItsIso14827DomainType domainType,
								 Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user,
								 bool_t guaranteed, u32_t subSerial, u32_t pubSerial, bool_t isLated,
								 str_t oidStr, u8_t *msgBody, size_t msgSize)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (t14827 == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (myDomain == NULL || myDomain->data == NULL || myDomain->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (peerDomain == NULL || peerDomain->data == NULL || peerDomain->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (user == NULL || user->data == NULL || user->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (oidStr == NULL || strlen(oidStr) == 0) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ItsIso14827ViolatedPublication *msg = ItsIso14827ViolatedPublication_new(domainType, NULL, NULL, NULL, NULL, &err);
		if (msg == NULL) ERR_OUT(&err);
		else
		{
			// Iso14827Publication *pub = NULL;
			pthread_cleanup_push(ItsIso14827ViolatedPublication_delAndSetNull, (void *)&msg);
			if ((msg->myDomain = Dz1Asn1UTF8Str_clone(myDomain, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->peerDomain = Dz1Asn1UTF8Str_clone(peerDomain, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->user = Dz1Asn1OctetStr_clone(user, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->pub = _generatePublication(guaranteed, subSerial, pubSerial, isLated, oidStr, msgBody, msgSize, &err)) == NULL) ERR_OUT(&err);
			else if ((err = Dz1Task_post(t14827, DZ1_TASK_QUEUE_NONE,
										ITS_ISO14827_DOMAIN_VIOLOTED_PUB, (void **)&msg,
										(Dz1DelFunc)ItsIso14827ViolatedPublication_del,
										(Dz1DumpFunc)ItsIso14827ViolatedPublication_dump,
										NULL, NULL, NULL)).code) ERR_OUT(&err);
			pthread_cleanup_pop(1); // (ItsIso14827ViolatedPublication_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}
// ITS_ISO14827_DOMAIN_VIOLOTED_PUB
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO14827_DOMAIN_VIOLOTED_SUB
static Dz1TaskProcStatus _violatedSub(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827ViolatedSubscription *msg = (ItsIso14827ViolatedSubscription *)Dz1TaskSigMsg_getData(*sg);

	ItsIso14827DomainKey key = { msg->domainType, msg->myDomain };
	ItsIso14827Domain *domain = ItsIso14827DomainMgr_findByKey(env->domainMgr, &key);
	if (domain == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		switch(domain->present)
		{
		case ItsIso14827DomainPresent_server:
			if ((*errp = ItsIso14827ServerDomain_violatedSub(domain->x.server, msg->peerDomain, msg->user,
															 &msg->sub, uArg, uRsc, timer)).code) ERR_OUT(errp);
			break;
		case ItsIso14827DomainPresent_client:
			ERR_SET_OUT(errp, EPERM);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ret;
}
static Iso14827Subscription *_generateSubscription(u32_t subSerial, bool_t guaranteed, str_t oidStr, u8_t *msgBody, size_t msgSize, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	Iso14827Subscription *ret = NULL;
	if ((ret = Iso14827Subscription_new(subSerial, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Iso14827SubscriptionType *type = NULL;
		Iso14827SubscriptionData *data = NULL;
		Iso14827EndAppMsg *eam = NULL;
		pthread_cleanup_push(Iso14827Subscription_delAndSetNull, (void *)&ret);

		if ((ret->type = type = Iso14827SubscriptionType_new(Iso14827SubscriptionTypePresent_data, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((type->x.data = data = Iso14827SubscriptionData_new(FALSE, Iso14827SubscriptionDataStatus_NEW, NULL,
																	 Iso14827SubscriptionDataFormat_dataPacket, 1,
																	 guaranteed, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((data->mode = Iso14827SubscriptionDataMode_new(Iso14827SubscriptionDataModePresent_single, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((data->msg = eam = Iso14827EndAppMsg_new(NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((eam->oid = Dz1Asn1OID_newFromStr(oidStr, errp)) == NULL) ERR_OUT(errp);
		else if ((eam->data = Dz1Asn1Any_new(msgBody, (u32_t)msgSize, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Iso14827Subscription_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Error ItsIso14827_violatedSub(void *t14827, Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user,
								 u32_t subSerial, bool_t guaranteed, str_t oidStr, u8_t *msgBody, size_t msgSize)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (t14827 == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (myDomain == NULL || myDomain->data == NULL || myDomain->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (peerDomain == NULL || peerDomain->data == NULL || peerDomain->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (user == NULL || user->data == NULL || user->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (oidStr == NULL || strlen(oidStr) == 0) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ItsIso14827ViolatedSubscription *msg = ItsIso14827ViolatedSubscription_new(ItsIso14827DomainType_server, NULL, NULL, NULL, NULL, &err);
		if (msg == NULL) ERR_OUT(&err);
		else
		{
			Iso14827Publication *pub = NULL;
			pthread_cleanup_push(ItsIso14827ViolatedPublication_delAndSetNull, (void *)&msg);
			if (0) { }
			else if ((msg->myDomain = Dz1Asn1UTF8Str_clone(myDomain, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->peerDomain = Dz1Asn1UTF8Str_clone(peerDomain, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->user = Dz1Asn1OctetStr_clone(user, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->sub = _generateSubscription(subSerial, guaranteed, oidStr, msgBody, msgSize, &err)) == NULL) ERR_OUT(&err);
			else if ((err = Dz1Task_post(t14827, DZ1_TASK_QUEUE_NONE,
										ITS_ISO14827_DOMAIN_VIOLOTED_SUB, (void **)&msg,
										(Dz1DelFunc)ItsIso14827ViolatedPublication_del,
										(Dz1DumpFunc)ItsIso14827ViolatedPublication_dump,
										NULL, NULL, NULL)).code) ERR_OUT(&err);
			pthread_cleanup_pop(1); // (ItsIso14827ViolatedPublication_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}
// ITS_ISO14827_DOMAIN_VIOLOTED_SUB
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO14827_DOMAIN_DATA_CONTROL
static Dz1Error ItsIso14827DomainMgr_dataControl(ItsIso14827DomainMgr *mgr,
												 ItsIso14827DomainType domainType, Dz1Asn1UTF8Str *domainName,
												 Dz1Asn1UTF8Str *peerName, Dz1Asn1OctetStr *user,
												 u32_t serial, Iso14827PublicationMgmt cmd,
												 void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827DomainKey key = { domainType, domainName };
	ItsIso14827Domain *domain = ItsIso14827DomainMgr_findByKey(mgr, &key);
	if (domain == NULL) ERR_SET_OUT(&err, ENOENT);
	else
	{
		switch(domain->present)
		{
		case ItsIso14827DomainPresent_server:
			if ((err = ItsIso14827ServerDomain_dataControl(domain->x.server, peerName, user,
														serial, cmd,
														uArg, uRsc, timer)).code) ERR_OUT(&err);
			break;
		case ItsIso14827DomainPresent_client:
			break;
		default:
			ERR_SET_OUT(&err, EINVAL);
			break;
		}
	}
	return err;
}

static Dz1TaskProcStatus _dataControl(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainDataControl *msg = (ItsIso14827DomainDataControl *)Dz1TaskSigMsg_getData(*sg);

	if ((*errp = ItsIso14827DomainMgr_dataControl(env->domainMgr, msg->domainType, msg->domainName,
												msg->peerName, msg->user,
												msg->serial, msg->cmd,
												uArg, uRsc, timer)).code) ERR_OUT(errp);
	return ret;
}

Dz1Error ItsIso14827_dataControl(void *t14827,
								 ItsIso14827DomainType domainType, Dz1Asn1UTF8Str *domainName,
								 Dz1Asn1UTF8Str *peerName,
								 Dz1Asn1OctetStr *user,
								 u32_t serial,
								 Iso14827PublicationMgmt cmd)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827DomainDataControl *msg = NULL;
	if (t14827 == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (domainName == NULL || domainName->data == NULL || domainName->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (peerName == NULL || peerName->data == NULL || peerName->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (user == NULL || user->data == NULL || user->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (cmd < 0 || cmd >= Iso14827PublicationMgmt_max) ERR_SET_OUT(&err, EINVAL);
	else if ((msg = ItsIso14827DomainDataControl_new(domainType, NULL, NULL, NULL, serial, cmd, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(ItsIso14827DomainDataControl_delAndSetNull, (void *)&msg);
		if ((msg->domainName = Dz1Asn1UTF8Str_clone(domainName, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->peerName = Dz1Asn1UTF8Str_clone(peerName, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->user = Dz1Asn1OctetStr_clone(user, &err)) == NULL) ERR_OUT(&err);
		else if ((err = Dz1Task_post(t14827, DZ1_TASK_QUEUE_NONE,
									ITS_ISO14827_DOMAIN_DATA_CONTROL, (void **)&msg,
									(Dz1DelFunc)ItsIso14827DomainDataControl_del,
									(Dz1DumpFunc)ItsIso14827DomainDataControl_dump,
									NULL, NULL, NULL)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (ItsIso14827DomainDataControl_delAndSetNull, (void *)&msg);
	}
	return err;
}
// ITS_ISO14827_DOMAIN_DATA_CONTROL
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO14827_DOMAIN_TERMINATE_CLIENT
static Dz1Error ItsIso14827DomainMgr_terminateClient(ItsIso14827DomainMgr *mgr, 
													 Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain,
													 Dz1Asn1OctetStr *user, Iso14827Terminate reason,
													 void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827DomainKey key = { ItsIso14827DomainType_server, myDomain };
	ItsIso14827Domain *domain = ItsIso14827DomainMgr_findByKey(mgr, &key);
	if (domain == NULL) ERR_SET_OUT(&err, ENOENT);
	else
	{
		switch(domain->present)
		{
		case ItsIso14827DomainPresent_server:
			if ((err = ItsIso14827ServerDomain_terminateClient(domain->x.server, peerDomain, user, reason,
															   uArg, uRsc, timer)).code) ERR_OUT(&err);
			break;
		case ItsIso14827DomainPresent_client:
			break;
		default:
			ERR_SET_OUT(&err, EINVAL);
			break;
		}
	}
	return err;
}

static Dz1TaskProcStatus _terminateClient(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainTerminateClient *msg = (ItsIso14827DomainTerminateClient *)Dz1TaskSigMsg_getData(*sg);

	if ((*errp = ItsIso14827DomainMgr_terminateClient(env->domainMgr,
													  msg->myDomain, msg->peerDomain, msg->user,
													  msg->reason,
													  uArg, uRsc, timer)).code) ERR_OUT(errp);
	return ret;
}

Dz1Error ItsIso14827_terminateClient(void *t14827,
									 Dz1Asn1UTF8Str *domainName,
									 Dz1Asn1UTF8Str *peerName,
									 Dz1Asn1OctetStr *user)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (t14827 == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (domainName == NULL || domainName->data == NULL || domainName->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (peerName == NULL || peerName->data == NULL || peerName->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (user == NULL || user->data == NULL || user->size == 0) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ItsIso14827DomainTerminateClient *msg = ItsIso14827DomainTerminateClient_new(NULL, NULL, NULL, Iso14827Terminate_serverRequested, &err);
		if (msg == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(ItsIso14827DomainTerminateClient_delAndSetNull, (void *)&msg);
			if ((msg->myDomain = Dz1Asn1UTF8Str_clone(domainName, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->peerDomain = Dz1Asn1UTF8Str_clone(peerName, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->user = Dz1Asn1OctetStr_clone(user, &err)) == NULL) ERR_OUT(&err);
			else if ((err = Dz1Task_post(t14827, DZ1_TASK_QUEUE_NONE,
										ITS_ISO14827_DOMAIN_TERMINATE_CLIENT, (void **)&msg,
										(Dz1DelFunc)ItsIso14827DomainTerminateClient_del,
										(Dz1DumpFunc)ItsIso14827DomainTerminateClient_dump,
										NULL, NULL, NULL)).code) ERR_OUT(&err);
			pthread_cleanup_pop(1); // (ItsIso14827DomainTerminateClient_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}
// ITS_ISO14827_DOMAIN_TERMINATE_CLIENT
///////////////////////////////////////////////////////////////////////////////

typedef struct ConnectToCancelArg
{
	ItsIso14827SessionMgr *sessionMgr;
	ItsIso14827SessionEntry *session;
} ConnectToCancelArg;

static void _connectToCancel(void *ptr)
{
	ConnectToCancelArg *arg = (ConnectToCancelArg *)ptr;
	ItsIso14827SessionEntry *session = arg->session;;
	ItsIso14827SessionMgr_sessionDisconnect(arg->sessionMgr, session->key);
}

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO14827_DOMAIN_INITIATE : ItsIso14827_connectToClient
static Dz1TaskProcStatus _connectToClient(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainMgr *domainMgr = env->domainMgr;
	ItsIso14827SessionMgr *sessionMgr = env->sessionMgr;

	ItsIso14827DomainInitiate *msg = (ItsIso14827DomainInitiate *)Dz1TaskSigMsg_getData(*sg);
	Iso14827Initiate *initiate = msg->data;

	ItsIso14827Domain *domain = NULL;
	ItsIso14827DomainKey key = { ItsIso14827DomainType_server, initiate->sender };	
	if ((domain = ItsIso14827DomainMgr_findByKey(domainMgr, &key)) == NULL) ERR_SET_OUT(errp, ENOENT);	// 없는 도메인에 요청하면 에러
	else
	{	// connect socket
		Dz1SockAddr local;
		Dz1TcpClientSocket *sock = NULL;
		struct timeval to = { 3, 0 };
		if ((*errp = Dz1SockAddr_setAddrStr(&local, (str_t)"0.0.0.0")).code) ERR_OUT(errp);
		else if ((*errp = Dz1SockAddr_setPort(&local, 0)).code) ERR_OUT(errp);
		else if ((sock = Dz1TcpClientSocket_open(msg->peerAddr, &local, &to, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ItsIso14827SessionEntry *session = NULL;
			pthread_cleanup_push(Dz1TcpClientSocket_closeAndSetNull, (void *)&sock);
			// 세션 엔트리 등록/리시버 시작/Session Alive Timer 등록
			if ((session = ItsIso14827SessionMgr_connected(sessionMgr, msg->peerAddr, &local, &sock, msg->initialCodec, msg->initialCRCMode, sg, uArg, uRsc, timer, errp)) == NULL) ERR_OUT(errp);
			else if ((*errp = ItsIso14827SessionEntry_sendInitiate(session, initiate, NULL, 0, NULL, NULL, env->pktDumpFlag)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1TcpClientSocket_closeAndSetNull, (void *)&sock);
		}
	}

	return ret;
}

Dz1Error ItsIso14827_connectToClient(void *t14827, Dz1SockAddr *dst, 
									 Dz1Asn1UTF8Str *domainName, Dz1Asn1UTF8Str *peerName,
									 Dz1Asn1Codec initialCodec, ItsIso14827CRCCheck initialCRCMode)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (t14827 == NULL || dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (domainName == NULL || domainName->data == NULL || domainName->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (peerName == NULL || peerName->data == NULL || peerName->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (initialCodec <= 0 || initialCodec >= Dz1Asn1Codec_max) ERR_SET_OUT(&err, EINVAL);
	else if (initialCRCMode < 0 || initialCRCMode >= ItsIso14827CRCCheck_max) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ItsIso14827DomainInitiate *msg = NULL;
		if ((msg = ItsIso14827DomainInitiate_new(NULL, NULL, NULL, NULL, initialCodec, initialCRCMode, &err)) == NULL) ERR_OUT(&err);
		else
		{
			Iso14827Initiate *p;
			pthread_cleanup_push(ItsIso14827DomainInitiate_delAndSetNull, (void *)&msg);
			if ((msg->peerAddr = Dz1SockAddr_clone(dst, &err)) == NULL) ERR_OUT(&err);
			if ((msg->data = p = Iso14827Initiate_new(NULL, NULL, &err)) == NULL) ERR_OUT(&err);
			else if ((p->sender = Dz1Asn1UTF8Str_clone(domainName, &err)) == NULL) ERR_OUT(&err);
			else if ((p->dest = Dz1Asn1UTF8Str_clone(peerName, &err)) == NULL) ERR_OUT(&err);
			else if ((err = Dz1Task_call(t14827, DZ1_TASK_QUEUE_NONE, ITS_ISO14827_DOMAIN_INITIATE, (void *)msg,
										 (Dz1DumpFunc)ItsIso14827DomainInitiate_dump, NULL, NULL)).code) ERR_OUT(&err);
			pthread_cleanup_pop(1); // (ItsIso14827DomainInitiate_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}
// ITS_ISO14827_DOMAIN_INITIATE : ItsIso14827_connectToClient
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO14827_DOMAIN_INITIATED : ItsIso14827_connectedToClient
static Dz1TaskProcStatus _connectedToClient(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainMgr *domainMgr = env->domainMgr;
	ItsIso14827SessionMgr *sessionMgr = env->sessionMgr;

	ItsIso14827DomainInitiate *msg = (ItsIso14827DomainInitiate *)Dz1TaskSigMsg_getData(*sg);
	Iso14827Initiate *initiate = msg->data;

	ItsIso14827DomainKey key = { ItsIso14827DomainType_server, initiate->sender };
	ItsIso14827Domain *domain = NULL;
	// 없는 도메인에 요청하면 에러
	if ((domain = ItsIso14827DomainMgr_findByKey(domainMgr, &key)) == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		ItsIso14827SessionEntry *session = NULL;
		// 세션 엔트리 등록/리시버 시작/Session Alive Timer 등록
		if ((session = ItsIso14827SessionMgr_connected(sessionMgr, msg->peerAddr, msg->localAddr, &msg->sock, msg->initialCodec, msg->initialCRCMode, sg, uArg, uRsc, timer, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = ItsIso14827SessionEntry_sendInitiate(session, initiate, NULL, 0, NULL, NULL, env->pktDumpFlag)).code) ERR_OUT(errp);
	}

	return ret;
}

Dz1Error ItsIso14827_connectedToClient(void *t14827, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket **sock,
									 Dz1Asn1UTF8Str *domainName, Dz1Asn1UTF8Str *peerName,
									 Dz1Asn1Codec initialCodec, ItsIso14827CRCCheck initialCRCMode)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (t14827 == NULL || peer == NULL || local == NULL || sock == NULL || *sock == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (domainName == NULL || domainName->data == NULL || domainName->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (peerName == NULL || peerName->data == NULL || peerName->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (initialCodec <= 0 || initialCodec >= Dz1Asn1Codec_max) ERR_SET_OUT(&err, EINVAL);
	else if (initialCRCMode < 0 || initialCRCMode >= ItsIso14827CRCCheck_max) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ItsIso14827DomainInitiate *msg = NULL;
		if ((msg = ItsIso14827DomainInitiate_new(NULL, NULL, (*sock), NULL, initialCodec, initialCRCMode, &err)) == NULL) ERR_OUT(&err);
		else
		{
			Iso14827Initiate *p;
			(*sock) = NULL;
			pthread_cleanup_push(ItsIso14827DomainInitiate_delAndSetNull, (void *)&msg);
			if ((msg->peerAddr = Dz1SockAddr_clone(peer, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->localAddr = Dz1SockAddr_clone(local, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->data = p = Iso14827Initiate_new(NULL, NULL, &err)) == NULL) ERR_OUT(&err);
			else if ((p->sender = Dz1Asn1UTF8Str_clone(domainName, &err)) == NULL) ERR_OUT(&err);
			else if ((p->dest = Dz1Asn1UTF8Str_clone(peerName, &err)) == NULL) ERR_OUT(&err);
			else if ((err = Dz1Task_call(t14827, DZ1_TASK_QUEUE_NONE, ITS_ISO14827_DOMAIN_INITIATED, (void *)msg,
										(Dz1DumpFunc)ItsIso14827DomainInitiate_dump, NULL, NULL)).code) ERR_OUT(&err);
			pthread_cleanup_pop(1); // (ItsIso14827DomainInitiate_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}
// ITS_ISO14827_DOMAIN_INITIATED : ItsIso14827_connectedToClient
///////////////////////////////////////////////////////////////////////////////

static Dz1Error _addCodecOid(Dz1OIDList *dst, Dz1Asn1Codec c)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1OID *oid = Dz1Asn1Codec2OID(c, &err);
	if (oid == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1Asn1OID_delAndSetNull, (void *)&oid);
		if ((err = dst->add(dst, oid)).code) ERR_OUT(&err);
		else oid = NULL;
		pthread_cleanup_pop(1); // (Dz1Asn1OID_delAndSetNull, (void *)&oid);
	}
	return err;
}

static Dz1Error _loginCodecListInit(Dz1OIDList *dst, u8_t bits)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	int i;
	for (i = 1; err.code == 0 && i < Dz1Asn1Codec_max; i++)
	{
		if (bits & Dz1GASN_codec2Bit((Dz1Asn1Codec)i))
		{
			if ((err = _addCodecOid(dst, (Dz1Asn1Codec)i)).code) ERR_OUT(&err);
		}
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO14827_DOMAIN_CONNECT : ItsIso14827_connectToServer
static Dz1TaskProcStatus _connectToServer(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainMgr *domainMgr = env->domainMgr;
	ItsIso14827SessionMgr *sessionMgr = env->sessionMgr;

	ItsIso14827DomainLogin *msg = (ItsIso14827DomainLogin *)Dz1TaskSigMsg_getData(*sg);
	Iso14827Login *login = msg->data;

	ItsIso14827Domain *domain = NULL;
	ItsIso14827SessionEntry *session = NULL;
	ItsIso14827DomainKey key = { ItsIso14827DomainType_client, login->sender };
	
	if ((domain = ItsIso14827DomainMgr_findByKey(domainMgr, &key)) == NULL) ERR_SET_OUT(errp, ENOENT);		// 없는 도메인에 요청하면 에러
	// 접속 한다 -> Session Manager에 Session이 등록된다.
	else if ((session = ItsISo14827SessionMgr_connect(sessionMgr, msg->peerAddr, login->datagramSize, msg->initialCodec, msg->initialCRCMode, uRsc, timer, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ItsIso14827DomainKey *dk = NULL;
		ItsIso14827DomainSessionEntry *sd_map = NULL;
		ConnectToCancelArg _arg = { sessionMgr, session };
		pthread_cleanup_push(_connectToCancel, (void *)&_arg);

		if ((sd_map = ItsIso14827DomainSessionEntry_new(NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(ItsIso14827DomainSessionEntry_delAndSetNull, (void *)&sd_map);
			// Session Mapping Entry를 준비한다.
			if ((sd_map->session = ItsIso14827SessionKey_clone(session->key, errp)) == NULL) ERR_OUT(errp);
			else if ((sd_map->domain = dk = ItsIso14827DomainKey_new(ItsIso14827DomainType_client, NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((dk->name = Dz1Asn1UTF8Str_clone(login->sender, errp)) == NULL) ERR_OUT(errp);

			// Login 전송 처리를 한다.
			else if ((*errp = ItsISo14827Clientdomain_connectToServer(domain->x.client, session, msg->authInfo, &msg->data, &msg->violatedSub, sg, uArg, uRsc, timer)).code) ERR_OUT(errp);
			// 성공 했으면 Session Mapping Entry를 등록한다.
			else if ((*errp = domainMgr->sessions->add(domainMgr->sessions, sd_map)).code) ERR_OUT(errp);
			else sd_map = NULL;

			pthread_cleanup_pop(1); // (ItsIso14827DomainSessionEntry_delAndSetNull, (void *)&sd_map);
		}
		pthread_cleanup_pop(errp->code); // (_connectToServerCancel, (void *)&_arg);
	}
	return ret;
}

Dz1Error _ItsIso14827_connectToServer(void *t14827, Dz1SockAddr *dst, 
									 Dz1Asn1UTF8Str *domainName, Dz1Asn1UTF8Str *peerName,
									 Dz1Asn1OctetStr *authInfo, Dz1Asn1OctetStr *user, Dz1Asn1OctetStr *pass,
									 u8_t codecRuleBits, u16_t heartBeatDuration,
									 u8_t responseWaitTime, u16_t datagramSize,
									 Dz1Asn1Codec *in_out_codec, ItsIso14827CRCCheck initialCRCMode,
									 ItsIso14827CallbackViolatedSubRcvd violatedSubRecv, void *violatedSubRecvParam,
									 Iso14827RejectLogin *retReason)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Iso14827RejectLogin _reason, *rp = retReason ? retReason : &_reason;

	if (t14827 == NULL || dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (domainName == NULL || domainName->data == NULL || domainName->size == 0) ERR_SET_OUT(errp, EINVAL);
	else if (peerName == NULL || peerName->data == NULL || peerName->size == 0) ERR_SET_OUT(errp, EINVAL);
	else if (user == NULL || user->data == NULL || user->size == 0) ERR_SET_OUT(errp, EINVAL);
	else if (codecRuleBits == 0) ERR_SET_OUT(errp, EINVAL);
	else if (in_out_codec == NULL || (*in_out_codec) <= 0 || (*in_out_codec) >= Dz1Asn1Codec_max) ERR_SET_OUT(errp, EINVAL);
	else if (initialCRCMode < 0 || initialCRCMode >= ItsIso14827CRCCheck_max) ERR_SET_OUT(errp, EINVAL);
	else
	{
		ItsIso14827DomainLogin *msg = NULL;

		*rp = Iso14827RejectLogin_other;

		if ((msg = ItsIso14827DomainLogin_new(*in_out_codec, (Iso14827RejectLogin)-1, NULL, NULL, NULL, NULL, NULL, initialCRCMode, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Iso14827Login *p;
			pthread_cleanup_push(ItsIso14827DomainLogin_delAndSetNull, (void *)&msg);

			if (violatedSubRecv != NULL && (msg->violatedSub = ItsIso14827ClientDomainViolatedSubscription_new(violatedSubRecv, violatedSubRecvParam, errp)) == NULL) ERR_OUT(errp);
			else if ((msg->peerAddr = Dz1SockAddr_clone(dst, errp)) == NULL) ERR_OUT(errp);
			else if (authInfo != NULL && (msg->authInfo = Dz1Asn1OctetStr_clone(authInfo, errp)) == NULL) ERR_OUT(errp);
			if ((msg->data = p = Iso14827Login_new(NULL, NULL, NULL, NULL,
												heartBeatDuration, responseWaitTime,
												Iso14827LoginInitiator_clientInitiated,
												datagramSize, &err)) == NULL) ERR_OUT(&err);
			else if ((p->sender = Dz1Asn1UTF8Str_clone(domainName, &err)) == NULL) ERR_OUT(&err);
			else if ((p->dest = Dz1Asn1UTF8Str_clone(peerName, &err)) == NULL) ERR_OUT(&err);
			else if ((p->user = Dz1Asn1OctetStr_clone(user, &err)) == NULL) ERR_OUT(&err);
			else if ((p->pass = Dz1Asn1OctetStr_clone(pass, &err)) == NULL) ERR_OUT(&err);
			else if ((err = _loginCodecListInit(p->encRules, codecRuleBits)).code) ERR_OUT(&err);
			else if ((err = Dz1Task_call(t14827, DZ1_TASK_QUEUE_NONE,
										ITS_ISO14827_DOMAIN_CONNECT, (void *)msg,
										(Dz1DumpFunc)ItsIso14827DomainLogin_dump,
										NULL, NULL)).code)
			{
				if (msg->reason != (Iso14827RejectLogin)-1)
				{
					(*rp) = msg->reason;
					ERR_SET_OUT(&err, EPERM);
				}
				ERR_OUT(&err);
			}
			else (*in_out_codec) = msg->initialCodec;

			pthread_cleanup_pop(1); // (ItsIso14827DomainLogin_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}
// ITS_ISO14827_DOMAIN_CONNECT : ItsIso14827_connectToServer
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO14827_DOMAIN_CONNECTED : ItsIso14827_connectedToServer
static Dz1TaskProcStatus _connectedToServer(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainMgr *domainMgr = env->domainMgr;
	ItsIso14827SessionMgr *sessionMgr = env->sessionMgr;

	ItsIso14827DomainLogin *msg = (ItsIso14827DomainLogin *)Dz1TaskSigMsg_getData(*sg);
	Iso14827Login *login = msg->data;

	ItsIso14827Domain *domain = NULL;
	ItsIso14827SessionEntry *session = NULL;
	ItsIso14827DomainKey key = { ItsIso14827DomainType_client, login->sender };
	
	if ((domain = ItsIso14827DomainMgr_findByKey(domainMgr, &key)) == NULL) ERR_SET_OUT(errp, ENOENT);		// 없는 도메인에 요청하면 에러
	// Session 이 등록된다.
	else if ((session = ItsIso14827SessionMgr_connected(sessionMgr, msg->peerAddr, msg->localAddr, &msg->sock, msg->initialCodec, msg->initialCRCMode, NULL, uArg, uRsc, timer, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ItsIso14827DomainKey *dk = NULL;
		ItsIso14827DomainSessionEntry *sd_map = NULL;
		ConnectToCancelArg _arg = { sessionMgr, session };
		pthread_cleanup_push(_connectToCancel, (void *)&_arg);

		if ((sd_map = ItsIso14827DomainSessionEntry_new(NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(ItsIso14827DomainSessionEntry_delAndSetNull, (void *)&sd_map);
			// Session Mapping Entry를 준비한다.
			if ((sd_map->session = ItsIso14827SessionKey_clone(session->key, errp)) == NULL) ERR_OUT(errp);
			else if ((sd_map->domain = dk = ItsIso14827DomainKey_new(ItsIso14827DomainType_client, NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((dk->name = Dz1Asn1UTF8Str_clone(login->sender, errp)) == NULL) ERR_OUT(errp);

			// Login 전송 처리를 한다.
			else if ((*errp = ItsISo14827Clientdomain_connectToServer(domain->x.client, session, msg->authInfo, &msg->data, &msg->violatedSub, sg, uArg, uRsc, timer)).code) ERR_OUT(errp);
			// 성공 했으면 Session Mapping Entry를 등록한다.
			else if ((*errp = domainMgr->sessions->add(domainMgr->sessions, sd_map)).code) ERR_OUT(errp);
			else sd_map = NULL;

			pthread_cleanup_pop(1); // (ItsIso14827DomainSessionEntry_delAndSetNull, (void *)&sd_map);
		}
		pthread_cleanup_pop(errp->code); // (_connectToServerCancel, (void *)&_arg);
	}

	return ret;
}

Dz1Error _ItsIso14827_connectedToServer(void *t14827, Dz1SockAddr *peer,  Dz1SockAddr *local, Dz1TcpClientSocket **sock,
									    Dz1Asn1UTF8Str *domainName, Dz1Asn1UTF8Str *peerName,
									    Dz1Asn1OctetStr *authInfo, Dz1Asn1OctetStr *user, Dz1Asn1OctetStr *pass,
									    u8_t codecRuleBits, u16_t heartBeatDuration,
									    u8_t responseWaitTime, u16_t datagramSize,
									    Dz1Asn1Codec *in_out_codec, ItsIso14827CRCCheck initialCRCMode,
									    ItsIso14827CallbackViolatedSubRcvd violatedSubRecv, void *violatedSubRecvParam,
									    Iso14827RejectLogin *retReason)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Iso14827RejectLogin _reason, *rp = retReason ? retReason : &_reason;

	if (t14827 == NULL || peer == NULL || local == NULL || sock == NULL || *sock == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (domainName == NULL || domainName->data == NULL || domainName->size == 0) ERR_SET_OUT(errp, EINVAL);
	else if (peerName == NULL || peerName->data == NULL || peerName->size == 0) ERR_SET_OUT(errp, EINVAL);
	else if (user == NULL || user->data == NULL || user->size == 0) ERR_SET_OUT(errp, EINVAL);
	else if (codecRuleBits == 0 || datagramSize == 0) ERR_SET_OUT(errp, EINVAL);
	else if (in_out_codec == NULL || (*in_out_codec) <= 0 || (*in_out_codec) >= Dz1Asn1Codec_max) ERR_SET_OUT(errp, EINVAL);
	else if (initialCRCMode < 0 || initialCRCMode >= ItsIso14827CRCCheck_max) ERR_SET_OUT(errp, EINVAL);
	else
	{
		ItsIso14827DomainLogin *msg = NULL;

		*rp = Iso14827RejectLogin_other;

		if ((msg = ItsIso14827DomainLogin_new(*in_out_codec, (Iso14827RejectLogin)-1, NULL, NULL, (*sock), NULL, NULL, initialCRCMode, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Iso14827Login *p;
			(*sock) = NULL;
			pthread_cleanup_push(ItsIso14827DomainLogin_delAndSetNull, (void *)&msg);
			if (violatedSubRecv != NULL && (msg->violatedSub = ItsIso14827ClientDomainViolatedSubscription_new(violatedSubRecv, violatedSubRecvParam, errp)) == NULL) ERR_OUT(errp);
			else if ((msg->peerAddr = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
			else if ((msg->localAddr = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
			else if (authInfo != NULL && (msg->authInfo = Dz1Asn1OctetStr_clone(authInfo, errp)) == NULL) ERR_OUT(errp);
			if ((msg->data = p = Iso14827Login_new(NULL, NULL, NULL, NULL,
												heartBeatDuration, responseWaitTime,
												Iso14827LoginInitiator_clientInitiated,
												datagramSize, errp)) == NULL) ERR_OUT(errp);
			else if ((p->sender = Dz1Asn1UTF8Str_clone(domainName, errp)) == NULL) ERR_OUT(errp);
			else if ((p->dest = Dz1Asn1UTF8Str_clone(peerName, errp)) == NULL) ERR_OUT(errp);
			else if ((p->user = Dz1Asn1OctetStr_clone(user, errp)) == NULL) ERR_OUT(errp);
			else if ((p->pass = Dz1Asn1OctetStr_clone(pass, errp)) == NULL) ERR_OUT(errp);
			else if ((err = _loginCodecListInit(p->encRules, codecRuleBits)).code) ERR_OUT(errp);
			else if ((err = Dz1Task_call(t14827, DZ1_TASK_QUEUE_NONE,
										ITS_ISO14827_DOMAIN_CONNECTED, (void *)msg,
										(Dz1DumpFunc)ItsIso14827DomainLogin_dump,
										NULL, NULL)).code)
			{
				if (msg->reason != (Iso14827RejectLogin)-1)
				{
					(*rp) = msg->reason;
					ERR_SET_OUT(errp, EPERM);
				}
				ERR_OUT(errp);
			}
			else (*in_out_codec) = msg->initialCodec;

			pthread_cleanup_pop(1); // (ItsIso14827DomainLogin_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}
// ITS_ISO14827_DOMAIN_CONNECTED : ItsIso14827_connectedToServer
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO14827_DOMAIN_BIND
static Dz1TaskProcStatus _bindWithServer(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainMgr *domainMgr = env->domainMgr;

	ItsIso14827DomainBind *msg = (ItsIso14827DomainBind *)Dz1TaskSigMsg_getData(*sg);
	Iso14827Login *login = msg->data;

	ItsIso14827Domain *domain = NULL;
	ItsIso14827SessionEntry *session = NULL;
	ItsIso14827DomainKey key = { ItsIso14827DomainType_client, login->sender };

	if ((session = ItsIso14827SessionMgr_find(env->sessionMgr, msg->bindKey)) == NULL) ERR_SET_OUT(errp, ENOENT);	// 없는 세션에 요청하면 에러
	else if ((domain = ItsIso14827DomainMgr_findByKey(domainMgr, &key)) == NULL) ERR_SET_OUT(errp, ENOENT);	// 없는 도메인에 요청하면 에러
	else
	{	// 접속 한다 -> Session Manager에 Session이 등록된다.
		ItsIso14827DomainKey *dk = NULL;
		ItsIso14827DomainSessionEntry *sd_map = NULL;
		ConnectToCancelArg _arg = { env->sessionMgr, session };
		pthread_cleanup_push(_connectToCancel, (void *)&_arg);

		if ((sd_map = ItsIso14827DomainSessionEntry_new(NULL, NULL, errp)) == NULL) ERR_OUT(errp);					// Session Mapping Entry 준비
		else
		{
			pthread_cleanup_push(ItsIso14827DomainSessionEntry_delAndSetNull, (void *)&sd_map);
			
			if (0) { }
			else if ((sd_map->session = ItsIso14827SessionKey_clone(session->key, errp)) == NULL) ERR_OUT(errp);
			else if ((sd_map->domain = dk = ItsIso14827DomainKey_new(ItsIso14827DomainType_client, NULL, errp)) == NULL) ERR_OUT(errp);
			else if ((dk->name = Dz1Asn1UTF8Str_clone(login->sender, errp)) == NULL) ERR_OUT(errp);

			// Login 전송 처리를 한다.
			else if ((*errp = ItsISo14827Clientdomain_connectToServer(domain->x.client, session, msg->authInfo, &msg->data, &msg->violatedSub, sg, uArg, uRsc, timer)).code) ERR_OUT(errp);

			// 성공 했으면 Session Mapping Entry를 등록한다.
			else if ((*errp = domainMgr->sessions->add(domainMgr->sessions, sd_map)).code) ERR_OUT(errp);
			else sd_map = NULL;

			pthread_cleanup_pop(1); // (ItsIso14827DomainSessionEntry_delAndSetNull, (void *)&sd_map);
		}
		pthread_cleanup_pop(errp->code); // (_connectToServerCancel, (void *)&_arg);
	}
	return ret;
}

Dz1Error _ItsIso14827_bindWithServer(void *t14827, ItsIso14827SessionKey *bindKey,
									 Dz1Asn1UTF8Str *domainName, Dz1Asn1UTF8Str *peerName,
									 Dz1Asn1OctetStr *authInfo, Dz1Asn1OctetStr *user, Dz1Asn1OctetStr *pass,
									 u8_t codecRuleBits, u16_t heartBeatDuration,
									 u8_t responseWaitTime, u16_t datagramSize,
									 Dz1Asn1Codec *selected,
									 ItsIso14827CallbackViolatedSubRcvd violatedSubRecv, void *violatedSubRecvParam,
									 Iso14827RejectLogin *retReason)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (t14827 == NULL || bindKey == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (domainName == NULL || domainName->data == NULL || domainName->size == 0) ERR_SET_OUT(errp, EINVAL);
	else if (peerName == NULL || peerName->data == NULL || peerName->size == 0) ERR_SET_OUT(errp, EINVAL);
	else if (user == NULL || user->data == NULL || user->size == 0) ERR_SET_OUT(errp, EINVAL);
	else if (codecRuleBits == 0) ERR_SET_OUT(errp, EINVAL);
	else if (selected == NULL || (*selected) <= 0 || (*selected) >= Dz1Asn1Codec_max) ERR_SET_OUT(errp, EINVAL);
	else
	{
		ItsIso14827DomainBind *msg = NULL;
		Iso14827RejectLogin _reason, *rp = retReason ? retReason : &_reason;

		*rp = Iso14827RejectLogin_other;

		if ((msg = ItsIso14827DomainBind_new((*selected), (Iso14827RejectLogin)-1, NULL, NULL, NULL, NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Iso14827Login *p;
			pthread_cleanup_push(ItsIso14827DomainBind_delAndSetNull, (void *)&msg);
			if (violatedSubRecv != NULL && (msg->violatedSub = ItsIso14827ClientDomainViolatedSubscription_new(violatedSubRecv, violatedSubRecvParam, errp)) == NULL) ERR_OUT(errp);
			else if ((msg->myDomain = Dz1Asn1UTF8Str_clone(domainName, errp)) == NULL) ERR_OUT(errp);
			else if ((msg->peerDomain = Dz1Asn1UTF8Str_clone(peerName, errp)) == NULL) ERR_OUT(errp);
			else if ((msg->bindKey = ItsIso14827SessionKey_clone(bindKey, errp)) == NULL) ERR_OUT(errp);
			else if (authInfo != NULL && (msg->authInfo = Dz1Asn1OctetStr_clone(authInfo, errp)) == NULL) ERR_OUT(errp);
			else if ((msg->data = p = Iso14827Login_new(NULL, NULL, NULL, NULL,
														heartBeatDuration, responseWaitTime,
														Iso14827LoginInitiator_serverInitiated,
														datagramSize, errp)) == NULL) ERR_OUT(errp);
			else if ((p->sender = Dz1Asn1UTF8Str_clone(domainName, errp)) == NULL) ERR_OUT(errp);
			else if ((p->dest = Dz1Asn1UTF8Str_clone(peerName, errp)) == NULL) ERR_OUT(errp);
			else if ((p->user = Dz1Asn1OctetStr_clone(user, errp)) == NULL) ERR_OUT(errp);
			else if ((p->pass = Dz1Asn1OctetStr_clone(pass, errp)) == NULL) ERR_OUT(errp);
			else if ((err = _loginCodecListInit(p->encRules, codecRuleBits)).code) ERR_OUT(errp);
			else if ((err = Dz1Task_call(t14827, DZ1_TASK_QUEUE_NONE, ITS_ISO14827_DOMAIN_BIND, (void *)msg,
										(Dz1DumpFunc)ItsIso14827DomainBind_dump, NULL, NULL)).code) ERR_OUT(errp);
			else if (msg->reason != (Iso14827RejectLogin)-1)
			{
				(*rp) = msg->reason;
				ERR_SET_OUT(errp, EPERM);
			}
			pthread_cleanup_pop(1); // (ItsIso14827DomainBind_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}
// ITS_ISO14827_DOMAIN_BIND
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO14827_DOMAIN_REJECT_INITIATE
static Dz1TaskProcStatus _rejectInitiate(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainBind *msg = (ItsIso14827DomainBind *)Dz1TaskSigMsg_getData(*sg);

	ItsIso14827SessionMgr_sessionDisconnect(env->sessionMgr, msg->bindKey);

	return ret;
}

Dz1Error ItsIso14827_rejectInitiate(void *t14827, ItsIso14827SessionKey *bindKey)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (t14827 == NULL || bindKey == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ItsIso14827DomainBind *msg = NULL;
		if ((msg = ItsIso14827DomainBind_new(Dz1Asn1Codec_unknown, (Iso14827RejectLogin)-1, NULL, NULL, NULL, NULL, NULL, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(ItsIso14827DomainBind_delAndSetNull, (void *)&msg);
			if ((msg->bindKey = ItsIso14827SessionKey_clone(bindKey, &err)) == NULL) ERR_OUT(&err);
			else if ((err = Dz1Task_call(t14827, DZ1_TASK_QUEUE_NONE, ITS_ISO14827_DOMAIN_REJECT_INITIATE, (void *)msg,
										(Dz1DumpFunc)ItsIso14827DomainBind_dump, NULL, NULL)).code) ERR_OUT(&err);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (ItsIso14827DomainBind_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}
// ITS_ISO14827_DOMAIN_REJECT_INITIATE
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO14827_DOMAIN_DISCONNECT
static Dz1Error ItsIso14827DomainMgr_disconnectFromServer(ItsIso14827DomainMgr *mgr,
														  Dz1Asn1UTF8Str *domainName,
														  Dz1Asn1UTF8Str *peerName, Dz1Asn1OctetStr *user,
														  Iso14827Logout reason, Dz1TaskSigMsg **sg,
														  void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827DomainKey key = { ItsIso14827DomainType_client, domainName };
	ItsIso14827Domain *domain = ItsIso14827DomainMgr_findByKey(mgr, &key);
	if (domain == NULL) ERR_SET_OUT(&err, ENOENT);
	// 단지 Logout만 날린다. (하지만 Application은 기다린다)
	else if ((err = ItsIso14827ClientDomain_disconnectFromServer(domain->x.client,
															peerName, user, reason, sg,
															uArg, uRsc, timer)).code) ERR_OUT(&err);
	// 뒷정리는 FrED를 받았을 때
	return err;
}

static Dz1TaskProcStatus _disconnectFromServer(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainLogout *msg = (ItsIso14827DomainLogout *)Dz1TaskSigMsg_getData(*sg);

	if ((*errp = ItsIso14827DomainMgr_disconnectFromServer(env->domainMgr,
														msg->domainName, msg->peerName, msg->user,
														msg->reason, sg, uArg, uRsc, timer)).code) ERR_OUT(errp);
	return ret;
}

Dz1Error ItsIso14827_disconnectFromServer(void *t14827,
										  Dz1Asn1UTF8Str *domainName,
										  Dz1Asn1UTF8Str *peerName,
										  Dz1Asn1OctetStr *user,
										  Iso14827Logout reason)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (t14827 == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (domainName == NULL || domainName->data == NULL || domainName->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (peerName == NULL || peerName->data == NULL || peerName->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (user == NULL || user->data == NULL || user->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (reason < 0 || reason >= Iso14827Logout_max) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ItsIso14827DomainLogout *msg = ItsIso14827DomainLogout_new(NULL, NULL, NULL, reason, &err);
		if (msg == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(ItsIso14827DomainLogout_delAndSetNull, (void *)&msg);
			if ((msg->domainName = Dz1Asn1UTF8Str_clone(domainName, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->peerName = Dz1Asn1UTF8Str_clone(peerName, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->user = Dz1Asn1OctetStr_clone(user, &err)) == NULL) ERR_OUT(&err);
			else if ((err = Dz1Task_call(t14827, DZ1_TASK_QUEUE_NONE, ITS_ISO14827_DOMAIN_DISCONNECT, (void *)msg,
										(Dz1DumpFunc)ItsIso14827DomainLogout_dump, NULL, NULL)).code) ERR_OUT(&err);
			pthread_cleanup_pop(1); // (ItsIso14827DomainLogout_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}
// ITS_ISO14827_DOMAIN_DISCONNECT
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO_14827_DOMAIN_CONTROL
static bool_t _domainControlCloent(ItsIso14827Env *env, ItsIso14827DomainCtrl *msg, Dz1Error *errp)
{
	ItsIso14827ClientDomainServerEntry *server = NULL;
	ItsIso14827ClientDomain *client = NULL;
	ItsIso14827DomainMgr *domainMgr = env->domainMgr;
	ItsIso14827DomainKey key = { msg->myDomainType, msg->domainName };
	ItsIso14827Domain *dom = ItsIso14827DomainMgr_findByKey(env->domainMgr, &key);
	if (dom == NULL) ERR_SET_OUT(errp, ENOENT);
	else if (dom->present != ItsIso14827DomainPresent_client) ERR_SET_OUT(errp, EFAULT);
	else if ((client = dom->x.client) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((server = ItsIso14827ClientDomain_findServerByPeerUser(client, msg->peerName, msg->user)) == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		u32_t flag = msg->flag;
		if (msg->on_off)
		{	// on
			server->ctrl_flags |= flag;
		}
		else
		{	// off
			server->ctrl_flags &= ~flag;
		}
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1TaskProcStatus _domainControl(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainCtrl *msg = (ItsIso14827DomainCtrl *)Dz1TaskSigMsg_getData(*sg);

	switch(msg->myDomainType)
	{
	case ItsIso14827DomainType_server: ERR_SET_OUT(errp, ENOSYS); break;
	case ItsIso14827DomainType_client:
		if (_domainControlCloent(env, msg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	}
	return ret;
}

Dz1Error _ItsIso14827_controlClient(void *t14827, Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user, u32_t ItsIso14827ClientCtrlFlag_flags, bool_t on_off)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ItsIso14827DomainCtrl *msg = NULL;
	if (t14827 == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (myDomain == NULL || peerDomain == NULL || user == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (ItsIso14827ClientCtrlFlag_flags == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((msg = ItsIso14827DomainCtrl_new(ItsIso14827DomainType_client, NULL, NULL, NULL, ItsIso14827ClientCtrlFlag_flags, on_off, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827DomainCtrl_delAndSetNull, (void *)&msg);

		if ((msg->domainName = Dz1Asn1UTF8Str_clone(myDomain, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->peerName = Dz1Asn1UTF8Str_clone(peerDomain, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->user = Dz1Asn1OctetStr_clone(user, &err)) == NULL) ERR_OUT(&err);
		else if ((err = Dz1Task_call(t14827, DZ1_TASK_QUEUE_NONE,
									ITS_ISO_14827_DOMAIN_CONTROL, (void *)msg,
									(Dz1DumpFunc)ItsIso14827DomainCtrl_dump,
									NULL, NULL)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (ItsIso14827DomainCtrl_delAndSetNull, (void *)&msg);
	}
	return err;
}

Dz1Error ItsIso14827_controlClient(void *t14827, Dz1Str domainName, Dz1Str peerName, str_t user, u32_t ItsIso14827ClientCtrlFlag_flags, bool_t on_off)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ItsIso14827DomainCtrl *msg = NULL;
	if (t14827 == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (Dz1Str_isVoid(domainName) || Dz1Str_isVoid(peerName) || Dz1Str_isVoid(user)) ERR_SET_OUT(errp, EINVAL);
	else if (ItsIso14827ClientCtrlFlag_flags == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((msg = ItsIso14827DomainCtrl_new(ItsIso14827DomainType_client, NULL, NULL, NULL, ItsIso14827ClientCtrlFlag_flags, on_off, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827DomainCtrl_delAndSetNull, (void *)&msg);

		if ((msg->domainName = Dz1Asn1UTF8Str_newFromStr(domainName, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->peerName = Dz1Asn1UTF8Str_newFromStr(peerName, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->user = Dz1Asn1UTF8StrA_newFromStr(user, &err)) == NULL) ERR_OUT(&err);
		else if ((err = Dz1Task_call(t14827, DZ1_TASK_QUEUE_NONE, ITS_ISO_14827_DOMAIN_CONTROL, (void *)msg,
									(Dz1DumpFunc)ItsIso14827DomainCtrl_dump, NULL, NULL)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (ItsIso14827DomainCtrl_delAndSetNull, (void *)&msg);
	}
	return err;
}
// ITS_ISO_14827_DOMAIN_CONTROL
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO14827_DOMAIN_SUBSCRIPTION
static Dz1TaskProcStatus _domainSubscription(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainMgr *domainMgr = env->domainMgr;

	ItsIso14827DomainSubscription *msg = (ItsIso14827DomainSubscription *)Dz1TaskSigMsg_getData(*sg);

	ItsIso14827DomainKey key = { msg->domainType, msg->domainName };
	ItsIso14827Domain *domain = ItsIso14827DomainMgr_findByKey(domainMgr, &key);
	if (domain == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		switch(domain->present)
		{
		case ItsIso14827DomainPresent_server:
			break;
		case ItsIso14827DomainPresent_client:
			if ((*errp = ItsIso14827ClientDomain_subscription(domain->x.client, msg->peerName, msg->user, &msg->data, sg, uArg, uRsc, timer)).code) ERR_OUT(errp);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ret;
}

Dz1Error ItsIso14827_singleRequest(void *t14827, ItsIso14827DomainType domainType,
								   Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain,
								   Dz1Asn1OctetStr *user, u32_t priority, bool_t guarantee,
								   str_t oidStr, u8_t *encoddedEndAppMsg, size_t encoddedEndAppMsgSize,
								   u32_t *retSerial, Iso14827RejectSubscription* retErr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (t14827 == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (myDomain == NULL || myDomain->data == NULL || myDomain->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (peerDomain == NULL || peerDomain->data == NULL || peerDomain->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (user == NULL || user->data == NULL || user->size == 0) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ItsIso14827DomainSubscription *msg = ItsIso14827DomainSubscription_new(domainType, NULL, NULL, NULL, NULL, &err);
		if (msg == NULL) ERR_OUT(&err);
		else
		{
			Iso14827EndAppMsg *eam = NULL;
			Iso14827SubscriptionData *data = NULL;
			pthread_cleanup_push(ItsIso14827DomainSubscription_delAndSetNull, (void *)&msg);
			if ((msg->domainName = Dz1Asn1UTF8Str_clone(myDomain, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->peerName = Dz1Asn1UTF8Str_clone(peerDomain, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->user = Dz1Asn1OctetStr_clone(user, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->data = data = Iso14827SubscriptionData_new(FALSE,
																	Iso14827SubscriptionDataStatus_NEW, NULL,
																	Iso14827SubscriptionDataFormat_dataPacket,
																	priority, guarantee, NULL, &err)) == NULL) ERR_OUT(&err);
			else if ((data->mode = Iso14827SubscriptionDataMode_new(Iso14827SubscriptionDataModePresent_single, NULL, &err)) == NULL) ERR_OUT(&err);
			else if ((data->msg = eam = Iso14827EndAppMsg_new(NULL, NULL, &err)) == NULL) ERR_OUT(&err);
			else if ((eam->oid = Dz1Asn1OID_newFromStr(oidStr, &err)) == NULL) ERR_OUT(&err);
			else if ((eam->data = Dz1Asn1Any_new(encoddedEndAppMsg, (u32_t)encoddedEndAppMsgSize, &err)) == NULL) ERR_OUT(&err);
			else if ((err = Dz1Task_call(t14827, DZ1_TASK_QUEUE_NONE,
										ITS_ISO14827_DOMAIN_SUBSCRIPTION, (void *)msg,
										(Dz1DumpFunc)ItsIso14827DomainSubscription_dump,
										NULL, NULL)).code) ERR_OUT(&err);
			else
			{
				if (retSerial != NULL) (*retSerial) = msg->retSerial;
				if (retErr != NULL) *retErr = msg->retError;
			}
			pthread_cleanup_pop(1); // (ItsIso14827DomainSubscription_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}

static Iso14827RegisteredContinuous _iso14827EvUnlimited = { 0, NULL, NULL };
Iso14827RegisteredContinuous *iso14827EvUnlimited = &_iso14827EvUnlimited;

Dz1Error ItsIso14827_continuousRequest(void *t14827, ItsIso14827DomainType domainType,
									   Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain,
									   Dz1Asn1OctetStr *user, bool_t isPersistent, u32_t priority,
									   bool_t guarantee, bool_t isPeriodic, Iso14827RegisteredContinuous *schedule,
									   str_t oidStr, u8_t *encoddedEndAppMsg, size_t encoddedEndAppMsgSize,
									   u32_t *retSerial, Iso14827RejectSubscription* retErr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (t14827 == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (myDomain == NULL || myDomain->data == NULL || myDomain->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (peerDomain == NULL || peerDomain->data == NULL || peerDomain->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (user == NULL || user->data == NULL || user->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (schedule == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (oidStr == NULL || strlen(oidStr) == 0) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ItsIso14827DomainSubscription *msg = ItsIso14827DomainSubscription_new(domainType, NULL, NULL, NULL, NULL, &err);
		if (msg == NULL) ERR_OUT(&err);
		else
		{
			Iso14827EndAppMsg *eam = NULL;
			Iso14827SubscriptionData *data = NULL;
			Iso14827SubscriptionDataMode *mode = NULL;
			Iso14827Registered *sch = NULL;
			Iso14827SubscriptionDataModePresent present = isPeriodic ? Iso14827SubscriptionDataModePresent_periodic:
																	   Iso14827SubscriptionDataModePresent_eventDriven;
			pthread_cleanup_push(ItsIso14827DomainSubscription_delAndSetNull, (void *)&msg);
			if ((msg->domainName = Dz1Asn1UTF8Str_clone(myDomain, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->peerName = Dz1Asn1UTF8Str_clone(peerDomain, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->user = Dz1Asn1OctetStr_clone(user, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->data = data = Iso14827SubscriptionData_new(isPersistent,
																	Iso14827SubscriptionDataStatus_NEW, NULL,
																	Iso14827SubscriptionDataFormat_dataPacket,
																	priority, guarantee, NULL, &err)) == NULL) ERR_OUT(&err);
			else if ((data->mode = mode = Iso14827SubscriptionDataMode_new(present, NULL, &err)) == NULL) ERR_OUT(&err);
			else if ((mode->x.__ptr__ = sch = Iso14827Registered_new(Iso14827RegisteredPresent_continuous, NULL, &err)) == NULL) ERR_OUT(&err);
			else if ((sch->x.continuous = Iso14827RegisteredContinuous_clone(schedule, &err)) == NULL) ERR_OUT(&err);
			else if ((data->msg = eam = Iso14827EndAppMsg_new(NULL, NULL, &err)) == NULL) ERR_OUT(&err);
			else if ((eam->oid = Dz1Asn1OID_newFromStr(oidStr, &err)) == NULL) ERR_OUT(&err);
			else if ((eam->data = Dz1Asn1Any_new(encoddedEndAppMsg, (u32_t)encoddedEndAppMsgSize, &err)) == NULL) ERR_OUT(&err);
			else if ((err = Dz1Task_call(t14827, DZ1_TASK_QUEUE_NONE,
										ITS_ISO14827_DOMAIN_SUBSCRIPTION, (void *)msg,
										(Dz1DumpFunc)ItsIso14827DomainSubscription_dump,
										NULL, NULL)).code) ERR_OUT(&err);
			else
			{
				if (retSerial != NULL) (*retSerial) = msg->retSerial;
				if (retErr != NULL) *retErr = msg->retError;
			}
			pthread_cleanup_pop(1); // (ItsIso14827DomainSubscription_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}

Dz1Error ItsIso14827_dailyRequest(void *t14827, ItsIso14827DomainType domainType,
								  Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain,
								  Dz1Asn1OctetStr *user, bool_t isPersistent, u32_t priority,
								  bool_t guarantee, bool_t isPeriodic, Iso14827RegisteredDaily *schedule,
								  str_t oidStr, u8_t *encoddedEndAppMsg, size_t encoddedEndAppMsgSize,
								  u32_t *retSerial, Iso14827RejectSubscription* retErr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (myDomain == NULL || myDomain->data == NULL || myDomain->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (peerDomain == NULL || peerDomain->data == NULL || peerDomain->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (user == NULL || user->data == NULL || user->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (schedule == NULL || schedule->daysOfWeek == 0) ERR_SET_OUT(&err, EINVAL);
	else if (oidStr == NULL || strlen(oidStr) == 0) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ItsIso14827DomainSubscription *msg = ItsIso14827DomainSubscription_new(domainType, NULL, NULL, NULL, NULL, &err);
		if (msg == NULL) ERR_OUT(&err);
		else
		{
			Iso14827EndAppMsg *eam = NULL;
			Iso14827SubscriptionData *data = NULL;
			Iso14827SubscriptionDataMode *mode = NULL;
			Iso14827Registered *sch = NULL;
			Iso14827SubscriptionDataModePresent present = isPeriodic ? Iso14827SubscriptionDataModePresent_periodic:
																	   Iso14827SubscriptionDataModePresent_eventDriven;
			pthread_cleanup_push(ItsIso14827DomainSubscription_delAndSetNull, (void *)&msg);
			if ((msg->domainName = Dz1Asn1UTF8Str_clone(myDomain, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->peerName = Dz1Asn1UTF8Str_clone(peerDomain, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->user = Dz1Asn1OctetStr_clone(user, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->data = data = Iso14827SubscriptionData_new(isPersistent,
																	Iso14827SubscriptionDataStatus_NEW, NULL,
																	Iso14827SubscriptionDataFormat_dataPacket,
																	priority, guarantee, NULL, &err)) == NULL) ERR_OUT(&err);
			else if ((data->mode = mode = Iso14827SubscriptionDataMode_new(present, NULL, &err)) == NULL) ERR_OUT(&err);
			else if ((mode->x.__ptr__ = sch = Iso14827Registered_new(Iso14827RegisteredPresent_daily, NULL, &err)) == NULL) ERR_OUT(&err);
			else if ((sch->x.daily = Iso14827RegisteredDaily_clone(schedule, &err)) == NULL) ERR_OUT(&err);
			else if ((data->msg = eam = Iso14827EndAppMsg_new(NULL, NULL, &err)) == NULL) ERR_OUT(&err);
			else if ((eam->oid = Dz1Asn1OID_newFromStr(oidStr, &err)) == NULL) ERR_OUT(&err);
			else if ((eam->data = Dz1Asn1Any_new(encoddedEndAppMsg, (u32_t)encoddedEndAppMsgSize, &err)) == NULL) ERR_OUT(&err);
			else if ((err = Dz1Task_call(t14827, DZ1_TASK_QUEUE_NONE,
										ITS_ISO14827_DOMAIN_SUBSCRIPTION, (void *)msg,
										(Dz1DumpFunc)ItsIso14827DomainSubscription_dump,
										NULL, NULL)).code) ERR_OUT(&err);
			else
			{
				if (retSerial != NULL) (*retSerial) = msg->retSerial;
				if (retErr != NULL) *retErr = msg->retError;
			}
			pthread_cleanup_pop(1); // (ItsIso14827DomainSubscription_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}
// ITS_ISO14827_DOMAIN_SUBSCRIPTION
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO14827_DOMAIN_SUB_CANCEL
static Dz1TaskProcStatus _domainSubCancel(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainMgr *domainMgr = env->domainMgr;

	ItsIso14827DomainSubCancel *msg = (ItsIso14827DomainSubCancel *)Dz1TaskSigMsg_getData(*sg);

	ItsIso14827DomainKey key = { msg->domainType, msg->domainName };
	ItsIso14827Domain *domain = ItsIso14827DomainMgr_findByKey(domainMgr, &key);
	if (domain == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		switch(domain->present)
		{
		case ItsIso14827DomainPresent_server:
			break;
		case ItsIso14827DomainPresent_client:
			if ((*errp = ItsIso14827ClientDomain_subCancel(domain->x.client, msg->peerName, msg->user, msg->serial, msg->reason, sg, uArg, uRsc, timer)).code) ERR_OUT(errp);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}

	return ret;
}

Dz1Error ItsIso14827_requestCancel(void *t14827, ItsIso14827DomainType domainType,
								   Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain,
								   Dz1Asn1OctetStr *user, u32_t serial, Iso14827SubscriptionCancel reason)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (t14827 == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (myDomain == NULL || myDomain->data == NULL || myDomain->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (peerDomain == NULL || peerDomain->data == NULL || peerDomain->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (user == NULL || user->data == NULL || user->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (reason < 0 || reason >= Iso14827SubscriptionCancel_max) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ItsIso14827DomainSubCancel *msg = ItsIso14827DomainSubCancel_new(domainType, NULL, NULL, NULL, serial, reason, &err);
		if (msg == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(ItsIso14827DomainSubCancel_delAndSetNull, (void *)&msg);
			if ((msg->domainName = Dz1Asn1UTF8Str_clone(myDomain, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->peerName = Dz1Asn1UTF8Str_clone(peerDomain, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->user = Dz1Asn1OctetStr_clone(user, &err)) == NULL) ERR_OUT(&err);
			else if ((err = Dz1Task_call(t14827, DZ1_TASK_QUEUE_NONE, ITS_ISO14827_DOMAIN_SUB_CANCEL, (void *)msg,
										(Dz1DumpFunc)ItsIso14827DomainSubCancel_dump, NULL, NULL)).code) ERR_OUT(&err);
			pthread_cleanup_pop(1); // (ItsIso14827DomainSubCancel_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}
// ITS_ISO14827_DOMAIN_SUB_CANCEL
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ITS_ISO14827_DOMAIN_REJECT_PUB_DATA
static Dz1TaskProcStatus _domainRejectPubData(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainMgr *domainMgr = env->domainMgr;
	ItsIso14827DomainRejectPubData *msg = (ItsIso14827DomainRejectPubData *)Dz1TaskSigMsg_getData(*sg);

	ItsIso14827DomainKey key = { msg->domainType, msg->domainName };
	ItsIso14827Domain *domain = ItsIso14827DomainMgr_findByKey(domainMgr, &key);
	if (domain == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		switch(domain->present)
		{
		case ItsIso14827DomainPresent_server:
			break;
		case ItsIso14827DomainPresent_client:
			if ((*errp = ItsIso14827ClientDomain_rejectPubData(domain->x.client, msg->peerName, msg->user, msg->serial, msg->pubSerial, msg->reason, sg, uArg, uRsc, timer)).code) ERR_OUT(errp);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ret;
}

Dz1Error ItsIso14827_rejectPubData(void *t14827, ItsIso14827DomainType domainType,
								   Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain,
								   Dz1Asn1OctetStr *user, u32_t subSerial, u32_t pubSerial, Iso14827RejectPubDataReason reason)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (t14827 == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (myDomain == NULL || myDomain->data == NULL || myDomain->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (peerDomain == NULL || peerDomain->data == NULL || peerDomain->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (user == NULL || user->data == NULL || user->size == 0) ERR_SET_OUT(&err, EINVAL);
	else if (reason < 0 || reason >= Iso14827RejectPubDataReason_max) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ItsIso14827DomainRejectPubData *msg = ItsIso14827DomainRejectPubData_new(domainType, NULL, NULL, NULL, subSerial, pubSerial, reason, &err);
		if (msg == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(ItsIso14827DomainRejectPubData_delAndSetNull, (void *)&msg);
			if ((msg->domainName = Dz1Asn1UTF8Str_clone(myDomain, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->peerName = Dz1Asn1UTF8Str_clone(peerDomain, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->user = Dz1Asn1OctetStr_clone(user, &err)) == NULL) ERR_OUT(&err);
			else if ((err = Dz1Task_call(t14827, DZ1_TASK_QUEUE_NONE, ITS_ISO14827_DOMAIN_REJECT_PUB_DATA, (void *)msg,
										(Dz1DumpFunc)ItsIso14827DomainRejectPubData_dump, NULL, NULL)).code) ERR_OUT(&err);
			pthread_cleanup_pop(1); // (ItsIso14827DomainRejectPubData_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}
// ITS_ISO14827_DOMAIN_REJECT_PUB_DATA
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Domain Manager Init
ItsIso14827DomainMgr *ItsIso14827DomainMgr_init(void *tSelf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ItsIso14827DomainMgr *ret = ItsIso14827DomainMgr_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827DomainMgr_delAndSetNull, (void *)&ret);
		if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_DOMAIN_CREATE_SERVER), _domainCreateServer)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_DOMAIN_DELETE_SERVER), _domainDeleteServer)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_DOMAIN_CREATE_CLIENT), _domainCreateClient)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_DOMAIN_DELETE_CLIENT), _domainDeleteClient)).code) ERR_OUT(errp);

		else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(ITS_ISO14827_DOMAIN_INITIATE), _connectToClient)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(ITS_ISO14827_DOMAIN_INITIATED), _connectedToClient)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(ITS_ISO14827_DOMAIN_LOGIN_ACCEPT), _loginAccept)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(ITS_ISO14827_DOMAIN_LOGIN_REJECT), _loginReject)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(ITS_ISO14827_DOMAIN_ECHO_REPLY), _echoReply)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(ITS_ISO14827_DOMAIN_PREPARE_ACCEPT), _prepareAccept)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(ITS_ISO14827_DOMAIN_PREPARE_REJECT), _prepareReject)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(ITS_ISO14827_DOMAIN_DATA_PROVIDE), _dataProvide)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(ITS_ISO14827_DOMAIN_DATA_CONTROL), _dataControl)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(ITS_ISO14827_DOMAIN_TERMINATE_CLIENT), _terminateClient)).code) ERR_OUT(errp);

		else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(ITS_ISO14827_DOMAIN_BIND), _bindWithServer)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(ITS_ISO14827_DOMAIN_REJECT_INITIATE), _rejectInitiate)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(ITS_ISO14827_DOMAIN_CONNECT), _connectToServer)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(ITS_ISO14827_DOMAIN_CONNECTED), _connectedToServer)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(ITS_ISO14827_DOMAIN_DISCONNECT), _disconnectFromServer)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(ITS_ISO14827_DOMAIN_SUBSCRIPTION), _domainSubscription)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(ITS_ISO14827_DOMAIN_SUB_CANCEL), _domainSubCancel)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(ITS_ISO14827_DOMAIN_REJECT_PUB_DATA), _domainRejectPubData)).code) ERR_OUT(errp);

		else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(ITS_ISO14827_DOMAIN_VIOLOTED_PUB), _violatedPub)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(ITS_ISO14827_DOMAIN_VIOLOTED_SUB), _violatedSub)).code) ERR_OUT(errp);
		else if ((*errp = Dz1Task_regMsg(tSelf, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_DOMAIN_CONTROL), _domainControl)).code) ERR_OUT(errp);
		Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ItsIso14827DomainMgr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Heart-Beat Duration Timeout
// Heart-Beat Duration 이 지나서 user@PEER를 제거하는 경우
Dz1TaskProcStatus ItsIso14827DomainMgr_heartBeatDurationTimeout(void *uArg, void *uRsc, void *timer, void **tData, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainMgr *mgr = env->domainMgr;

	ItsIso14827Timer *tmr = (ItsIso14827Timer *)(*tData);
	ItsIso14827DomainTimer *dTmr = tmr->x.domain;

	ItsIso14827Domain *domain = ItsIso14827DomainMgr_findByKey(env->domainMgr, dTmr->key);
	ItsIso14827SessionKey *skey = NULL;
	if (domain)
	{
		switch(domain->present)
		{
		case ItsIso14827DomainPresent_server:
			if ((skey = ItsIso14827ServerDomain_expireSession(domain->x.server, dTmr->peer, dTmr->user, timer)) != NULL)
			{
				pthread_cleanup_push(ItsIso14827SessionKey_delAndSetNull, (void *)&skey);
				ItsIso14827SessionMgr_sessionDisconnect(env->sessionMgr, skey);
				ItsIso14827DomainMgr_removeDomainMap(mgr, skey);
				pthread_cleanup_pop(1); // (ItsIso14827SessionKey_delAndSetNull, (void *)&skey);
			}
			break;
		case ItsIso14827DomainPresent_client:
			if ((skey = ItsIso14827ClientDomain_expireSession(domain->x.client, dTmr->peer, dTmr->user, timer)) != NULL)
			{
				ItsIso14827SessionMgr_sessionDisconnect(env->sessionMgr, skey);
				ItsIso14827DomainMgr_removeDomainMap(mgr, skey);
			}
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}

	return ret;
}
// Heart-Beat Duration Timeout
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Session Shutdown
// Session 이 끊어져서 user@PEER만 사라지는 경우
void ItsIso14827DomainMgr_sessionDisconnected(ItsIso14827DomainMgr *mgr, ItsIso14827SessionKey *skey, void *timer)
{
	ItsIso14827DomainSessionEntry key = { skey }, *node = mgr->sessions->extract(mgr->sessions, &key);
	if (node)
	{
		ItsIso14827Domain *domain = NULL;
		pthread_cleanup_push(ItsIso14827DomainSessionEntry_delAndSetNull, (void *)&node);
		if ((domain = ItsIso14827DomainMgr_findByKey(mgr, node->domain)) != NULL)
		{
			switch(domain->present)
			{
			case ItsIso14827DomainPresent_server:
				ItsIso14827ServerDomain_sessionDisconnected(domain->x.server, skey, timer);
				ItsIso14827DomainMgr_removeDomainMap(mgr, skey);
				break;
			case ItsIso14827DomainPresent_client:
				ItsIso14827ClientDomain_sessionDisconnected(domain->x.client, skey, timer);
				ItsIso14827DomainMgr_removeDomainMap(mgr, skey);
				break;
			default:
				break;
			}
		}
		pthread_cleanup_pop(1); // (ItsIso14827DomainSessionEntry_delAndSetNull, (void *)&node);
	}
}
// Session Shutdown
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Terminate
// Task가 종료 할 때
static void ItsIso14827Domain_terminate(ItsIso14827Domain *p)
{
	if (p == NULL) return;
	switch(p->present)
	{
	case ItsIso14827DomainPresent_server:
		ItsIso14827ServerDomain_terminate(p->x.server);
		break;
	case ItsIso14827DomainPresent_client:
		ItsIso14827ClientDomain_terminate(p->x.client);
		break;
	default:
		break;
	}
}

static Dz1Error _ItsIso14827DomainMgr_terminate(void *ptr, ItsIso14827Domain *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827Domain_terminate(p);
	return err;
}

void ItsIso14827DomainMgr_terminate(ItsIso14827DomainMgr *mgr)
{
	if (mgr == NULL) return;
	mgr->domains->travel(mgr->domains, _ItsIso14827DomainMgr_terminate, NULL);
	// mgr->sessions는 신경 쓸 필요가 없다. ItsIso14827DomainMgr_del에 의해 지워진다.
	ItsIso14827DomainMgr_del(mgr);
}
// Terminate
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Initiate Received : Client Application 으로 통보만 한다.
static Dz1Error ItsIso14827DomainMgr_receivedInitiate(ItsIso14827DomainMgr *mgr,
													  ItsIso14827SessionEntry *session,
													  Dz1Asn1OctetStr *authInfo,
													  u32_t pktNbr, s32_t priority,
													  Iso14827PDUs *pdu, bool_t isRetried,
													  void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Iso14827Initiate *p = pdu->x.initiate;

	ItsIso14827Domain *domain = NULL;
	ItsIso14827DomainKey domainKey = { ItsIso14827DomainType_client, p->dest };

	if ((domain = ItsIso14827DomainMgr_findByKey(mgr, &domainKey)) == NULL)
	{
		Dz1Thread_printf("### ItsIso14827DomainMgr_receivedInitiate() Unknown Domain = "); Dz1Asn1UTF8Str_dump(p->dest, 0);
		ERR_SET_OUT(&err, ENOENT);
	}
	else if ((err = ItsIso14827ClientDomain_received(domain->x.client, session,
													 authInfo, pktNbr, priority,
													 pdu, isRetried, uArg, uRsc, timer)).code) ERR_OUT(&err);

	return err;
}
// Initiate Received : Client Application 으로 통보만 한다.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Login Received : Login->dest로 Domain을 찾아서 Server Domain Receive를 호출
// 결과가 정상이면 Session Map 등록
static Dz1Error ItsIso14827DomainMgr_receivedLogin(ItsIso14827DomainMgr *mgr, ItsIso14827SessionEntry *session,
												   Dz1Asn1OctetStr *authInfo, u32_t pktNbr, s32_t priority,
												   Iso14827PDUs *pdu, bool_t isRetried, void *uArg, void *uRsc, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827Env *env = (ItsIso14827Env *)uRsc;
	ItsIso14827DomainSessionEntry *entry = ItsIso14827DomainSessionEntry_new(NULL, NULL, &err);
	if (entry == NULL) ERR_OUT(&err);
	else
	{
		Iso14827Login *p = pdu->x.login;

		ItsIso14827Domain *domain = NULL;
		ItsIso14827DomainKey *domainKey = NULL;
		
		pthread_cleanup_push(ItsIso14827DomainSessionEntry_delAndSetNull, (void *)&entry);
		if ((entry->session = ItsIso14827SessionKey_clone(session->key, &err)) == NULL) ERR_OUT(&err);
		else if ((entry->domain = domainKey = ItsIso14827DomainKey_new(ItsIso14827DomainType_server, NULL, &err)) == NULL) ERR_OUT(&err);
		else if ((domainKey->name = Dz1Asn1UTF8Str_clone(p->dest, &err)) == NULL) ERR_OUT(&err);
		else if ((domain = ItsIso14827DomainMgr_findByKey(mgr, domainKey)) == NULL)
		{
			Dz1Error status = DZ1_ERROR_INITIALIZER;
			if ((status = ItsIso14827SessionEntry_sendRejectLogin(session, pktNbr, Iso14827RejectLogin_unknownDomainName,
																  0, NULL, NULL, env->pktDumpFlag)).code) ERR_OUT(&status);
			ERR_SET_OUT(&err, ENOENT);
		}
		else if ((err = ItsIso14827ServerDomain_received(domain->x.server, session, authInfo, pktNbr, priority, pdu, isRetried, uArg, uRsc, timer)).code) ERR_OUT(&err);
		else if ((err = mgr->sessions->add(mgr->sessions, entry)).code) ERR_OUT(&err);
		else entry = NULL;

		pthread_cleanup_pop(1); // (ItsIso14827DomainSessionEntry_delAndSetNull, (void *)&entry);
	}
	return err;
}
// Login Received
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PDUs Received
static Dz1Error _ItsIso14827DomainMgr_received(ItsIso14827Domain *domain, ItsIso14827SessionEntry *src,
											   Dz1Asn1OctetStr *authInfo, u32_t pktNbr, s32_t priority,
											   Iso14827PDUs *pdu, bool_t isRetried,
											   void *uArg, void *uRsc, void *timer)
{
	// ItsIso14827SessionMgr_received  = 오류 시 Session Entry 삭제
	//   -> _ItsIso14827SessionMgr_received = C2C Message 삭제
	//     -> ItsIso14827DomainMgr_received = 오류 시 Domain-Session Map 삭제
	//	     -> _ItsIso14827DomainMgr_received = Server/Client에 따라 분기
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	switch(domain->present)
	{
	case ItsIso14827DomainPresent_server:
		if ((err = ItsIso14827ServerDomain_received(domain->x.server, src, authInfo, pktNbr, priority, pdu, isRetried, uArg, uRsc, timer)).code) ERR_OUT(&err);
		break;
	case ItsIso14827DomainPresent_client:
		if ((err = ItsIso14827ClientDomain_received(domain->x.client, src, authInfo, pktNbr, priority, pdu, isRetried, uArg, uRsc, timer)).code) ERR_OUT(&err);
		break;
	default:
		ERR_SET_OUT(&err, EINVAL);
		break;
	}
	return err;
}

Dz1Error ItsIso14827DomainMgr_received(ItsIso14827DomainMgr *mgr,
									   ItsIso14827SessionEntry *session,
									   Dz1Asn1OctetStr *authInfo,
									   u32_t pktNbr, s32_t priority,
									   Iso14827PDUs *pdu, bool_t isRetried,
									   void *uArg, void *uRsc, void *timer)
{	// session 은 일시적으로 Session Manager 로 부터 apart 되어 호출됨
	// ItsIso14827SessionMgr_received = 오류 시 Session Entry 삭제
	//   -> _ItsIso14827SessionMgr_received = C2C Message 삭제
	//     -> ItsIso14827DomainMgr_received = 오류 시 Domain-Session Map 삭제
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ItsIso14827DomainSessionEntry mapKey = { session->key }, *map = mgr->sessions->extract(mgr->sessions, &mapKey);
	if (map == NULL)
	{	// No Mapping Domain -> Check Login or initiate
		switch(pdu->present)
		{
		case Iso14827PDUsPresent_initiate:
			// Client Only
			Dz1Thread_printf("ItsIso14827DomainMgr_received() : ### Initiate\n");
			if ((err = ItsIso14827DomainMgr_receivedInitiate(mgr, session, authInfo, pktNbr, priority, pdu, isRetried, uArg, uRsc, timer)).code) ERR_OUT(&err);
			break;
		case Iso14827PDUsPresent_login:
			// Server Only
			Dz1Thread_printf("ItsIso14827DomainMgr_received() : ### Login\n");
			if ((err = ItsIso14827DomainMgr_receivedLogin(mgr, session, authInfo, pktNbr, priority, pdu, isRetried, uArg, uRsc, timer)).code) ERR_OUT(&err);
			break;
		default:
			ERR_SET_OUT(&err, EINVAL);
			break;
		}
	}
	else
	{	// Mapping Domain exist
		ItsIso14827Domain *domain = NULL;
		pthread_cleanup_push(ItsIso14827DomainSessionEntry_delAndSetNull, (void *)&map);
		// Domain-Session MAP으로 실제 Domain을 찾는다.
		if ((domain = ItsIso14827DomainMgr_findByKey(mgr, map->domain)) == NULL) ERR_SET_OUT(&err, EFAULT);
		// Domain Receiver 호출
		else if ((err = _ItsIso14827DomainMgr_received(domain, session, authInfo, pktNbr, priority, pdu, isRetried, uArg, uRsc, timer)).code) ERR_OUT(&err);
		// 이상없으면 Domain-Session MAP 복구
		else if ((err = mgr->sessions->add(mgr->sessions, map)).code) ERR_OUT(&err);
		else map = NULL;
		pthread_cleanup_pop(1); // (ItsIso14827DomainSessionEntry_delAndSetNull, (void *)&map);
	}
	return err;
}
// PDUs Received
///////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827TaskSupport.h"
///////////////////////////////////////////////////////////////////////////////
// Server Disconnected
static void _logout(void *param, Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t dst_queue_id = (u32_t)DZ1_PTR2VAL32(param);
	ItsIso14827EventDisconnected *msg = ItsIso14827EventDisconnected_new(NULL, NULL, NULL, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827EventDisconnected_delAndSetNull, (void *)&msg);
		if ((msg->myDomain = Dz1Asn1UTF8Str_clone(myDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->peerDomain = Dz1Asn1UTF8Str_clone(peerDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->user = Dz1Asn1OctetStr_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dst_queue_id, -1, ITS_ISO_14827_EVENT4TASK_LOGOUT, (void **)&msg,
											(Dz1DelFunc)ItsIso14827EventDisconnected_del,
											(Dz1DumpFunc)ItsIso14827EventDisconnected_dump,
											NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ItsIso14827EventDisconnected_delAndSetNull, (void *)&msg);
	}
}
// Server Disconnected
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Client Disconnect
static void _disconnected(void *param, Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t dst_queue_id = (u32_t)DZ1_PTR2VAL32(param);
	ItsIso14827EventDisconnected *msg = ItsIso14827EventDisconnected_new(NULL, NULL, NULL, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827EventDisconnected_delAndSetNull, (void *)&msg);
		if ((msg->myDomain = Dz1Asn1UTF8Str_clone(myDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->peerDomain = Dz1Asn1UTF8Str_clone(peerDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->user = Dz1Asn1OctetStr_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dst_queue_id, -1, ITS_ISO_14827_EVENT4TASK_DISCONNECTED, (void **)&msg,
											(Dz1DelFunc)ItsIso14827EventDisconnected_del,
											(Dz1DumpFunc)ItsIso14827EventDisconnected_dump,
											NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ItsIso14827EventDisconnected_delAndSetNull, (void *)&msg);
	}
}
// Client Disconnect
///////////////////////////////////////////////////////////////////////////////

static void _authenticate(void *param, Dz1Asn1UTF8Str *myDomain,
						  Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user,
						  Dz1Asn1OctetStr *pass, Dz1Asn1OctetStr *authInfo,
						  s32_t hbDur, s32_t timeout, u8_t codecBits, bool_t is_retried)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t dst_queue_id = (u32_t)DZ1_PTR2VAL32(param);
	ItsIso14827ServerEventAuth *msg = ItsIso14827ServerEventAuth_new(NULL, NULL, NULL, NULL, NULL, hbDur, timeout, codecBits, is_retried, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventAuth_delAndSetNull, (void *)&msg);
		if ((msg->myDomain = Dz1Asn1UTF8Str_clone(myDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->peerDomain = Dz1Asn1UTF8Str_clone(peerDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->user = Dz1Asn1OctetStr_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->pass = Dz1Asn1OctetStr_clone(pass, errp)) == NULL) ERR_OUT(errp);
		else if (authInfo != NULL && (msg->authInfo = Dz1Asn1OctetStr_clone(authInfo, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dst_queue_id, -1, ITS_ISO_14827_EVENT4TASK_SERVER_AUTH, (void **)&msg,
											(Dz1DelFunc)ItsIso14827ServerEventAuth_del,
											(Dz1DumpFunc)ItsIso14827ServerEventAuth_dump,
											NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ItsIso14827ServerEventAuth_delAndSetNull, (void *)&msg);
	}
}

static void _established(void *param, Dz1Asn1UTF8Str *myDomain,
						 Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user,
						 Dz1Asn1Codec selected)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t dst_queue_id = (u32_t)DZ1_PTR2VAL32(param);
	ItsIso14827ServerEventConnected *msg = ItsIso14827ServerEventConnected_new(NULL, NULL, NULL, selected, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventConnected_delAndSetNull, (void *)&msg);
		if ((msg->myDomain = Dz1Asn1UTF8Str_clone(myDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->peerDomain = Dz1Asn1UTF8Str_clone(peerDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->user = Dz1Asn1OctetStr_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dst_queue_id, -1, ITS_ISO_14827_EVENT4TASK_SERVER_CONNECTED, (void **)&msg,
											(Dz1DelFunc)ItsIso14827ServerEventConnected_del,
											(Dz1DumpFunc)ItsIso14827ServerEventConnected_dump,
											NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ItsIso14827ServerEventConnected_delAndSetNull, (void *)&msg);
	}
}
												
static void _echoRequest(void *param, Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user, u32_t echoID)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t dst_queue_id = (u32_t)DZ1_PTR2VAL32(param);
	ItsIso14827ServerEventEcho *msg = ItsIso14827ServerEventEcho_new(NULL, NULL, NULL, echoID, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventEcho_delAndSetNull, (void *)&msg);
		if ((msg->myDomain = Dz1Asn1UTF8Str_clone(myDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->peerDomain = Dz1Asn1UTF8Str_clone(peerDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->user = Dz1Asn1OctetStr_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dst_queue_id, -1, ITS_ISO_14827_EVENT4TASK_SERVER_ECHO, (void **)&msg,
											(Dz1DelFunc)ItsIso14827ServerEventEcho_del,
											(Dz1DumpFunc)ItsIso14827ServerEventEcho_dump,
											NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ItsIso14827ServerEventEcho_delAndSetNull, (void *)&msg);
	}
}

static void _singleRequest(void *param, Dz1Asn1UTF8Str *myDomain,
						   Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user,
						   u32_t subID, str_t oidStr, u8_t *encodedEAM, u32_t encodedEAMSize)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t dst_queue_id = (u32_t)DZ1_PTR2VAL32(param);
	ItsIso14827ServerEventSubSignle *msg = ItsIso14827ServerEventSubSignle_new(NULL, NULL, NULL, subID, oidStr, NULL, encodedEAMSize, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventSubSignle_delAndSetNull, (void *)&msg);
		if ((msg->myDomain = Dz1Asn1UTF8Str_clone(myDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->peerDomain = Dz1Asn1UTF8Str_clone(peerDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->user = Dz1Asn1OctetStr_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if (encodedEAM != NULL && encodedEAMSize != 0 && (msg->encodedEAM = (u8_t *)Dz1Memory_clone(encodedEAM, encodedEAMSize, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dst_queue_id, -1, ITS_ISO_14827_EVENT4TASK_SERVER_PUB_SINGLE, (void **)&msg,
											(Dz1DelFunc)ItsIso14827ServerEventSubSignle_del,
											(Dz1DumpFunc)ItsIso14827ServerEventSubSignle_dump,
											NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ItsIso14827ServerEventSubSignle_delAndSetNull, (void *)&msg);
	}
}

static void _eventPrepare(void *param, Dz1Asn1UTF8Str *myDomain,
						  Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user,
						  u32_t subID, u32_t latency_sec,
						  str_t oidStr, u8_t *encodedEAM, u32_t encodedEAMSize)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t dst_queue_id = (u32_t)DZ1_PTR2VAL32(param);
	ItsIso14827ServerEventSubPrepareED *msg = ItsIso14827ServerEventSubPrepareED_new(NULL, NULL, NULL, subID, latency_sec, oidStr, NULL, encodedEAMSize,  errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventSubPrepareED_delAndSetNull, (void *)&msg);
		if ((msg->myDomain = Dz1Asn1UTF8Str_clone(myDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->peerDomain = Dz1Asn1UTF8Str_clone(peerDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->user = Dz1Asn1OctetStr_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if (encodedEAM != NULL && encodedEAMSize != 0 && (msg->encodedEAM = (u8_t *)Dz1Memory_clone(encodedEAM, encodedEAMSize, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dst_queue_id, -1, ITS_ISO_14827_EVENT4TASK_SERVER_PUB_ED_PREPARE, (void **)&msg,
											(Dz1DelFunc)ItsIso14827ServerEventSubPrepareED_del,
											(Dz1DumpFunc)ItsIso14827ServerEventSubPrepareED_dump,
											NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ItsIso14827ServerEventSubPrepareED_delAndSetNull, (void *)&msg);
	}
}

static void _periodicPreapre(void *param, Dz1Asn1UTF8Str *myDomain,
							 Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user,
							 u32_t subID, u32_t period_sec,
							 str_t oidStr, u8_t *encodedEAM, u32_t encodedEAMSize)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t dst_queue_id = (u32_t)DZ1_PTR2VAL32(param);
	ItsIso14827ServerEventSubPrepareP *msg = ItsIso14827ServerEventSubPrepareP_new(NULL, NULL, NULL, subID, period_sec, oidStr, NULL, encodedEAMSize, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventSubPrepareP_delAndSetNull, (void *)&msg);
		if ((msg->myDomain = Dz1Asn1UTF8Str_clone(myDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->peerDomain = Dz1Asn1UTF8Str_clone(peerDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->user = Dz1Asn1OctetStr_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if (encodedEAM != NULL && encodedEAMSize != 0 && (msg->encodedEAM = (u8_t *)Dz1Memory_clone(encodedEAM, encodedEAMSize, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dst_queue_id, -1, ITS_ISO_14827_EVENT4TASK_SERVER_PUB_PR_PREPARE, (void **)&msg,
											(Dz1DelFunc)ItsIso14827ServerEventSubPrepareP_del,
											(Dz1DumpFunc)ItsIso14827ServerEventSubPrepareP_dump,
											NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ItsIso14827ServerEventSubPrepareP_delAndSetNull, (void *)&msg);
	}
}

static Dz1Error _post_pub_start(u32_t dst_queue_id, u32_t msg_id,
								Dz1Asn1UTF8Str *myDomain,
								Dz1Asn1UTF8Str *peerDomain,
								Dz1Asn1OctetStr *user,
								u32_t subID, str_t oidStr, u8_t *encodedEAM, u32_t encodedEAMSize)

{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ItsIso14827ServerEventPubStart *msg = ItsIso14827ServerEventPubStart_new(NULL, NULL, NULL, subID, oidStr, NULL, encodedEAMSize, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventPubStart_delAndSetNull, (void *)&msg);
		if ((msg->myDomain = Dz1Asn1UTF8Str_clone(myDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->peerDomain = Dz1Asn1UTF8Str_clone(peerDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->user = Dz1Asn1OctetStr_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if (encodedEAM != NULL && encodedEAMSize != 0 && (msg->encodedEAM = (u8_t *)Dz1Memory_clone(encodedEAM, encodedEAMSize, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dst_queue_id, -1, msg_id, (void **)&msg,
											(Dz1DelFunc)ItsIso14827ServerEventPubStart_del,
											(Dz1DumpFunc)ItsIso14827ServerEventPubStart_dump,
											NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ItsIso14827ServerEventPubStart_delAndSetNull, (void *)&msg);
	}
	return err;
}
static void _pubStart(void *param,
					  Dz1Asn1UTF8Str *myDomain,
					  Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user,
					  u32_t subID, str_t oidStr, u8_t *encodedEAM, u32_t encodedEAMSize)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t dst_queue_id = (u32_t)DZ1_PTR2VAL32(param);
	if ((*errp = _post_pub_start(dst_queue_id, ITS_ISO_14827_EVENT4TASK_SERVER_PUB_START, myDomain, peerDomain, user, subID, oidStr, encodedEAM, encodedEAMSize)).code) ERR_OUT(errp);
}
													
static void _periodicInvoke(void *param, Dz1Asn1UTF8Str *myDomain,
							Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user,
							u32_t subID, str_t oidStr, u8_t *encodedEAM, u32_t encodedEAMSize)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t dst_queue_id = (u32_t)DZ1_PTR2VAL32(param);
	if ((*errp = _post_pub_start(dst_queue_id, ITS_ISO_14827_EVENT4TASK_SERVER_PUB_INVOKE, myDomain, peerDomain, user, subID, oidStr, encodedEAM, encodedEAMSize)).code) ERR_OUT(errp);
}

static void _pubErrorInform(void *param, Dz1Asn1UTF8Str *myDomain,
							Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user,
							u32_t subID, ItsIso14827PublicarionError *reason)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t dst_queue_id = (u32_t)DZ1_PTR2VAL32(param);
	ItsIso14827ServerEventPubInform *msg = ItsIso14827ServerEventPubInform_new(NULL, NULL, NULL, subID, NULL, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventPubInform_delAndSetNull, (void *)&msg);
		if ((msg->myDomain = Dz1Asn1UTF8Str_clone(myDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->peerDomain = Dz1Asn1UTF8Str_clone(peerDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->user = Dz1Asn1OctetStr_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if (reason != NULL && (msg->reason = ItsIso14827PublicarionError_clone(reason, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dst_queue_id, -1, ITS_ISO_14827_EVENT4TASK_SERVER_PUB_INFORM, (void **)&msg,
											(Dz1DelFunc)ItsIso14827ServerEventPubInform_del,
											(Dz1DumpFunc)ItsIso14827ServerEventPubInform_dump,
											NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ItsIso14827ServerEventPubInform_delAndSetNull, (void *)&msg);
	}
}

static void _stopped(void *param, Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user, u32_t subID)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t dst_queue_id = (u32_t)DZ1_PTR2VAL32(param);
	ItsIso14827ServerEventPubStop *msg = ItsIso14827ServerEventPubStop_new(NULL, NULL, NULL, subID, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventPubStop_delAndSetNull, (void *)&msg);
		if ((msg->myDomain = Dz1Asn1UTF8Str_clone(myDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->peerDomain = Dz1Asn1UTF8Str_clone(peerDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->user = Dz1Asn1OctetStr_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dst_queue_id, -1, ITS_ISO_14827_EVENT4TASK_SERVER_PUB_STOPPED, (void **)&msg,
											(Dz1DelFunc)ItsIso14827ServerEventPubStop_del,
											(Dz1DumpFunc)ItsIso14827ServerEventPubStop_dump,
											NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ItsIso14827ServerEventPubStop_delAndSetNull, (void *)&msg);
	}
}

static void _expired(void *param, Dz1Asn1UTF8Str *myDomain,
					 Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user,
					 u32_t subID, ItsIso14827SubscriptionExpireReason *reason)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t dst_queue_id = (u32_t)DZ1_PTR2VAL32(param);
	ItsIso14827ServerEventPubExpire *msg = ItsIso14827ServerEventPubExpire_new(NULL, NULL, NULL, subID, NULL, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827ServerEventPubExpire_delAndSetNull, (void *)&msg);
		if ((msg->myDomain = Dz1Asn1UTF8Str_clone(myDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->peerDomain = Dz1Asn1UTF8Str_clone(peerDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->user = Dz1Asn1OctetStr_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if (reason != NULL && (msg->reason = ItsIso14827SubscriptionExpireReason_clone(reason, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dst_queue_id, -1, ITS_ISO_14827_EVENT4TASK_SERVER_PUB_EXPIRED, (void **)&msg,
											(Dz1DelFunc)ItsIso14827ServerEventPubExpire_del,
											(Dz1DumpFunc)ItsIso14827ServerEventPubExpire_dump,
											NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ItsIso14827ServerEventPubExpire_delAndSetNull, (void *)&msg);
	}
}

static void _sysHealthWarning(void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t dst_queue_id = (u32_t)DZ1_PTR2VAL32(param);
	if ((*errp = Dz1Task_queuePostSimple(dst_queue_id, -1, ITS_ISO_14827_EVENT4TASK_SERVER_OVERLOAD)).code) ERR_OUT(errp);
}

Dz1Error ItsIso14827_createServer4Task(u32_t task_queue_id, void *t14827,
									   Dz1Asn1UTF8Str *my_domain, u32_t max_clients,
									   ItsIso14827CodecOIDInfo user_oid_map_arr[], size_t user_oid_map_arr_cnt)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ItsIso14827ServerDomainCallback server_cbs_task =
	{
		_authenticate,
		_established,
		_logout,
		_echoRequest,
		_singleRequest,
		_eventPrepare,
		_pubStart,
		_periodicPreapre,
		_pubStart,
		_periodicInvoke,
		_pubErrorInform,
		_stopped,
		_expired,
		_sysHealthWarning,
		(void *)DZ1_VAL2PTR32(task_queue_id)
	};

	if ((*errp = ItsIso14827_createServer(t14827,  my_domain, max_clients, user_oid_map_arr, user_oid_map_arr_cnt, &server_cbs_task)).code) ERR_OUT(errp);
	
	return err;
}

Dz1Error ItsIso14827_serverTaskMsgInit(void *task, ItsIso14827ServerTaskHandler *h)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (0) { }
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_SERVER_AUTH), h->auth)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_SERVER_CONNECTED), h->connected)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_SERVER_ECHO), h->echo)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_SERVER_PUB_SINGLE), h->single)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_SERVER_PUB_ED_PREPARE), h->ed_prepare)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_SERVER_PUB_PR_PREPARE), h->pr_prepare)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_SERVER_PUB_START), h->pub_start)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_SERVER_PUB_INVOKE), h->pub_invoke)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_SERVER_PUB_INFORM), h->pub_inform)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_SERVER_PUB_STOPPED), h->pub_stopped)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_SERVER_PUB_EXPIRED), h->pub_expired)).code) ERR_OUT(errp);
	else if (h->overload != NULL && (*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_SERVER_OVERLOAD), h->overload)).code) ERR_OUT(errp);
	else if (h->disconnected != NULL && (*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_LOGOUT), h->disconnected)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Client Initiated
static void _initiated(void *param, Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain, Dz1Asn1Codec initial_codec, ItsIso14827SessionKey *key)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t dst_queue_id = (u32_t)DZ1_PTR2VAL32(param);
	ItsIso14827ClientEventInitiate *msg = ItsIso14827ClientEventInitiate_new(NULL, NULL, initial_codec, NULL, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827ClientEventInitiate_delAndSetNull, (void *)&msg);
		if ((msg->myDomain = Dz1Asn1UTF8Str_clone(myDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->peerDomain = Dz1Asn1UTF8Str_clone(peerDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->key = ItsIso14827SessionKey_clone(key, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dst_queue_id, -1, ITS_ISO_14827_EVENT4TASK_CLIENT_INITIATE, (void **)&msg,
											(Dz1DelFunc)ItsIso14827ClientEventInitiate_del,
											(Dz1DumpFunc)ItsIso14827ClientEventInitiate_dump,
											NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ItsIso14827ClientEventInitiate_delAndSetNull, (void *)&msg);
	}
}
// Client Initiated
///////////////////////////////////////////////////////////////////////////////

static void _echoResponsed(void *param, Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t dst_queue_id = (u32_t)DZ1_PTR2VAL32(param);
	ItsIso14827EventDisconnected *msg = ItsIso14827EventDisconnected_new(NULL, NULL, NULL, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827EventDisconnected_delAndSetNull, (void *)&msg);
		if ((msg->myDomain = Dz1Asn1UTF8Str_clone(myDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->peerDomain = Dz1Asn1UTF8Str_clone(peerDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->user = Dz1Asn1OctetStr_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dst_queue_id, -1, ITS_ISO_14827_EVENT4TASK_CLIENT_ECHO, (void **)&msg,
											(Dz1DelFunc)ItsIso14827EventDisconnected_del,
											(Dz1DumpFunc)ItsIso14827EventDisconnected_dump,
											NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ItsIso14827EventDisconnected_delAndSetNull, (void *)&msg);
	}
}

static void _terminate(void *param, Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user, Iso14827Terminate reason)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t dst_queue_id = (u32_t)DZ1_PTR2VAL32(param);
	ItsIso14827ClientEventTerminate *msg = ItsIso14827ClientEventTerminate_new(NULL, NULL, NULL, reason, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827ClientEventTerminate_delAndSetNull, (void *)&msg);
		if ((msg->myDomain = Dz1Asn1UTF8Str_clone(myDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->peerDomain = Dz1Asn1UTF8Str_clone(peerDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->user = Dz1Asn1OctetStr_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dst_queue_id, -1, ITS_ISO_14827_EVENT4TASK_CLIENT_TERMINATE, (void **)&msg,
											(Dz1DelFunc)ItsIso14827ClientEventTerminate_del,
											(Dz1DumpFunc)ItsIso14827ClientEventTerminate_dump,
											NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ItsIso14827ClientEventTerminate_delAndSetNull, (void *)&msg);
	}
}


static void _publication(void *param, Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user, 
						 u32_t sid, u32_t pubSerial, str_t oidStr, u8_t *encodedEAM, u32_t encodedEAMSize)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t dst_queue_id = (u32_t)DZ1_PTR2VAL32(param);
	ItsIso14827ClientEventPublication *msg = ItsIso14827ClientEventPublication_new(NULL, NULL, NULL, sid, pubSerial, oidStr, NULL, encodedEAMSize, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827ClientEventPublication_delAndSetNull, (void *)&msg);
		if ((msg->myDomain = Dz1Asn1UTF8Str_clone(myDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->peerDomain = Dz1Asn1UTF8Str_clone(peerDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->user = Dz1Asn1OctetStr_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if (encodedEAM != NULL && encodedEAMSize != 0 && (msg->encodedEAM = (u8_t *)Dz1Memory_clone(encodedEAM, encodedEAMSize, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dst_queue_id, -1, ITS_ISO_14827_EVENT4TASK_CLIENT_PUBLICATION, (void **)&msg,
											(Dz1DelFunc)ItsIso14827ClientEventPublication_del,
											(Dz1DumpFunc)ItsIso14827ClientEventPublication_dump,
											NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ItsIso14827ClientEventPublication_delAndSetNull, (void *)&msg);
	}
}


static void _pubControl(void *param, Dz1Asn1UTF8Str *myDomain, Dz1Asn1UTF8Str *peerDomain, Dz1Asn1OctetStr *user, 
						u32_t sid, u32_t pubSerial, Iso14827PublicationMgmt cmd)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t dst_queue_id = (u32_t)DZ1_PTR2VAL32(param);
	ItsIso14827ClientEventPubControl *msg = ItsIso14827ClientEventPubControl_new(NULL, NULL, NULL, sid, pubSerial, cmd, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827ClientEventPubControl_delAndSetNull, (void *)&msg);
		if ((msg->myDomain = Dz1Asn1UTF8Str_clone(myDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->peerDomain = Dz1Asn1UTF8Str_clone(peerDomain, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->user = Dz1Asn1OctetStr_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dst_queue_id, -1, ITS_ISO_14827_EVENT4TASK_CLIENT_PUB_CONTROL, (void **)&msg,
											(Dz1DelFunc)ItsIso14827ClientEventPubControl_del,
											(Dz1DumpFunc)ItsIso14827ClientEventPubControl_dump,
											NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ItsIso14827ClientEventPubControl_delAndSetNull, (void *)&msg);
	}
}

Dz1Error ItsIso14827_createClient4Task(u32_t dst_queue_id, void *t14827, Dz1Asn1UTF8Str *myDomain)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ItsIso14827ClientDomainCallback client_cbs_task =
	{
		_initiated,
		_echoResponsed,
		_terminate,
		_publication,
		_pubControl,
		_disconnected,
		(void *)DZ1_VAL2PTR32(dst_queue_id)
	};

	if ((*errp = ItsIso14827_createClient(t14827, myDomain, &client_cbs_task)).code) ERR_OUT(errp);
	return err;
}

Dz1Error ItsIso14827_clientTaskMsgInit(void *task, ItsIso14827ClientTaskHandler *h)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (0) { }
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_CLIENT_INITIATE), h->initiate)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_CLIENT_ECHO), h->echo_responsed)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_CLIENT_TERMINATE), h->terminate)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_CLIENT_PUBLICATION), h->publication)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_CLIENT_PUB_CONTROL), h->pub_control)).code) ERR_OUT(errp);
	else if (h->disconnected != NULL && (*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_DISCONNECTED), h->disconnected)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

Dz1Error ItsIso14827_bothTaskMsgInit(void *task, ItsIso14827ServerTaskHandler *h_server, ItsIso14827ClientTaskHandler *h_client)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (0) { }
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_CLIENT_INITIATE), h_client->initiate)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_CLIENT_ECHO), h_client->echo_responsed)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_CLIENT_TERMINATE), h_client->terminate)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_CLIENT_PUBLICATION), h_client->publication)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_CLIENT_PUB_CONTROL), h_client->pub_control)).code) ERR_OUT(errp);

	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_SERVER_AUTH), h_server->auth)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_SERVER_CONNECTED), h_server->connected)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_SERVER_ECHO), h_server->echo)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_SERVER_PUB_SINGLE), h_server->single)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_SERVER_PUB_ED_PREPARE), h_server->ed_prepare)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_SERVER_PUB_PR_PREPARE), h_server->pr_prepare)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_SERVER_PUB_START), h_server->pub_start)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_SERVER_PUB_INVOKE), h_server->pub_invoke)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_SERVER_PUB_INFORM), h_server->pub_inform)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_SERVER_PUB_STOPPED), h_server->pub_stopped)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_SERVER_PUB_EXPIRED), h_server->pub_expired)).code) ERR_OUT(errp);
	else if (h_server->overload != NULL && (*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_SERVER_OVERLOAD), h_server->overload)).code) ERR_OUT(errp);
	else if (h_client->disconnected != NULL && (*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_DISCONNECTED), h_client->disconnected)).code) ERR_OUT(errp);
	else if (h_server->disconnected != NULL && (*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITS_ISO_14827_EVENT4TASK_LOGOUT), h_server->disconnected)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}

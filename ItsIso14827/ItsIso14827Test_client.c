#include <dz1_gasn_support.h>
#include <ItsIso14827TaskSupport.h>
#include "ItsIso14827Test.h"

///////////////////////////////////////////////////////////////////////////////
// Test Message Client
static ssize_t _TestMessage_encode(void *ptr, u8_t **ret_buf, Dz1Asn1Codec codec, Dz1Str *ret_oid, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = -1;
	TestMessage *src = (TestMessage *)ptr;
	Dz1Binary *bin = TestMessage_encode(src, codec, ret_oid, errp);
	if (bin == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

		(*ret_buf) = bin->data;
		bin->data = NULL;

		ret = (ssize_t)bin->size;
		bin->size = 0;

		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return ret;
}

static ssize_t _TestMessage_decode(Dz1Str oid, void **ret, u8_t *data, size_t sz, Dz1Asn1Codec codec, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (( *ret = TestMessage_decode(oid, data, sz, codec, errp)) == NULL) return -1;
	else return (ssize_t)sz;
}
// Test Message Client
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Client List
static ClientModeMap clientModeMap[] =
{
	{ "TEST", CLIENT_DOMAIN_DEFAULT, SERVER_DOMAIN_DEFAULT, "127.0.0.1", DEFAULT_TEST_PORT_NUMBER, DEFAULT_USER_NAME, DEFAULT_USER_PASS,
			  testMessageGenerator, (Dz1DelFunc)TestMessage_del, (Dz1DumpFunc)TestMessage_dump,
			  _TestMessage_encode, _TestMessage_decode },
	{ NULL }
};
ClientModeMap *selectedClient = NULL;

ClientModeMap *ClientModeMap_find(str_t name)
{
	ClientModeMap *i;
	for (i = clientModeMap; i->name != NULL; i++)
		if (strcmp(name, i->name) == 0) return i;
	return NULL;
}

// Client List
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestClientArg API
typedef ssize_t (*TestClientEncodeF)(void *src, u8_t **dst, Dz1Asn1Codec codec, str_t *retOID, Dz1Error *err);
typedef ssize_t (*TestClientDecodeF)(str_t oidStr, void **dst, u8_t *src, size_t size, Dz1Asn1Codec codec, Dz1Error *err);
typedef struct TestClientArg
{
	Dz1Asn1UTF8Str				*myDomain;
	TestClientEncodeF			 eam_enc;
	TestClientDecodeF			 eam_dec;
	Dz1DelFunc					 eam_del;
	Dz1DumpFunc					 eam_dump;

	MsgGenerator				*generator;

	Dz1Asn1UTF8Str				*peerDomain;
	Dz1Asn1OctetStr				*user;
	Dz1Asn1OctetStr				*pass;
	Dz1Asn1Codec				 codec;
} TestClientArg;

static void TestClientArg_del(TestClientArg *p)
{
	if (p != NULL)
	{
		Dz1Asn1UTF8Str_delAndSetNull(&p->myDomain);
		Dz1Asn1UTF8Str_delAndSetNull(&p->peerDomain);
		Dz1Asn1OctetStr_delAndSetNull(&p->user);
		Dz1Asn1OctetStr_delAndSetNull(&p->pass);
		Dz1Free(p);
	}
}

static void TestClientArg_delAndSetNull(void *pptr)
{
	TestClientArg **p = (TestClientArg **)pptr;
	TestClientArg_del(*p);
	*p = NULL;
}

static TestClientArg *TestClientArg_new(Dz1Str myDomainStr, 
										TestClientEncodeF eam_enc, TestClientDecodeF eam_dec, 
										Dz1DelFunc eam_del, Dz1DumpFunc eam_dump, 
										MsgGenerator *generator,
										Dz1Str peerDomainStr, Dz1Str userStr, Dz1Str passStr, Dz1Asn1Codec codec, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestClientArg *ret = NULL;
	int codec_support = eam_enc != NULL && eam_dec != NULL ? 1 :
						eam_enc == NULL && eam_dec == NULL ? 0 : -1;
	if (codec_support == -1) ERR_SET_OUT(errp, EINVAL);
	else if	(codec_support == 1 && (eam_del == NULL || eam_dump == NULL)) ERR_SET_OUT(errp, EINVAL);
	else if (codec_support == 1 && generator == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (TestClientArg *)Dz1Calloc(sizeof(TestClientArg), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestClientArg_delAndSetNull, (void *)&ret);

		if (0) { }
		else if ((ret->myDomain = Dz1Asn1UTF8Str_newFromStr(myDomainStr, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->peerDomain = Dz1Asn1UTF8Str_newFromStr(peerDomainStr, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->user = Dz1Asn1UTF8Str_newFromStr(userStr, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->pass = Dz1Asn1UTF8Str_newFromStr(passStr, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->eam_enc = eam_enc;
			ret->eam_dec = eam_dec;
			ret->eam_del = eam_del;
			ret->eam_dump = eam_dump;

			ret->generator = generator;

			ret->codec = codec;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (TestClientArg_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// TestClientArg API
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestClientSession API
typedef struct TestClientSession
{
	Dz1Asn1UTF8Str			*peerDomain;			// session
	Dz1Asn1OctetStr			*user;					// session
	Dz1Asn1OctetStr			*pass;					// session
	Dz1Asn1Codec			 selected_codec;		// session
	u32_t					 periodic_sid;
} TestClientSession;

static void TestClientSession_del(TestClientSession *p)
{
	if (p != NULL)
	{
		Dz1Asn1UTF8Str_delAndSetNull(&p->peerDomain);
		Dz1Asn1OctetStr_delAndSetNull(&p->user);
		Dz1Asn1OctetStr_delAndSetNull(&p->pass);
		Dz1Free(p);
	}
}

static void TestClientSession_delAndSetNull(void *pptr)
{
	TestClientSession **p = (TestClientSession **)pptr;
	TestClientSession_del(*p);
	*p = NULL;
}

typedef struct SessionDumpInfo
{
	Dz1Str peerDomain;
	Dz1Str user;
	Dz1Str pass;
} SessionDumpInfo;

static void SessionDumpInfo_cleanup(void *ptr)
{
	SessionDumpInfo *p = (SessionDumpInfo *)ptr;
	if (p != NULL)
	{
		Dz1Str_delAndSetNull(&p->peerDomain);
		Dz1Str_delAndSetNull(&p->user);
		Dz1Str_delAndSetNull(&p->pass);
	}
}

static bool_t SessionDumpInfo_init(SessionDumpInfo *dst, TestClientSession *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	pthread_cleanup_push(SessionDumpInfo_cleanup, (void *)dst);

	if ((dst->peerDomain = Dz1Asn1UTF8Str_toStr(src->peerDomain, errp)) == NULL) { }
	else if ((dst->user = Dz1Asn1UTF8Str_toStr(src->user, errp)) == NULL) { }
	else if ((dst->pass = Dz1Asn1UTF8Str_toStr(src->pass, errp)) == NULL) { }
	else Dz1Error_set(errp, 0);

	pthread_cleanup_pop(errp->code); // (SessionDumpInfo_cleanup, (void *)dst);

	return errp->code == 0 ? TRUE : FALSE;
}

static void TestClientSession_dump(TestClientSession *p, int tab)
{
	SessionDumpInfo info = { NULL, NULL, NULL };
	if (p == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else if (SessionDumpInfo_init(&info, p, NULL) == FALSE)
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("peerDomain = ")); Dz1Asn1UTF8Str_dump(p->peerDomain, tab);
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab);
		Dz1Thread_tprintf(tab, Dz1T("pass = ")); Dz1Asn1OctetStr_dump(p->pass, tab);
		Dz1Thread_tprintf(tab, Dz1T("codec = %s\n"), Dz1Asn1CodecStr(p->selected_codec));
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
	else
	{
		pthread_cleanup_push(SessionDumpInfo_cleanup, (void *)&info);
		Dz1Thread_printf(Dz1T("%s:%s@%s(%s)\n"), info.user, info.pass, info.peerDomain, Dz1Asn1CodecStr(p->selected_codec));
		pthread_cleanup_pop(1); // (SessionDumpInfo_cleanup, (void *)&info);
	}
}

static int TestClientSession_cmp(TestClientSession *a, TestClientSession *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL) return -1;
	else if (b == NULL) return 1;
	else return Dz1Asn1UTF8Str_cmp(a->peerDomain, b->peerDomain);
}

static TestClientSession *TestClientSession_new(Dz1Str peerDomainStr, Dz1Str userStr, Dz1Str passStr, Dz1Asn1Codec selected_codec, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestClientSession *ret = (TestClientSession *)Dz1Calloc(sizeof(TestClientSession), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestClientSession_delAndSetNull, (void *)&ret);
		if (0) { }
		else if (Dz1Str_isVoid(peerDomainStr) == FALSE && (ret->peerDomain = Dz1Asn1UTF8Str_newFromStr(peerDomainStr, errp)) == NULL) ERR_OUT(errp);
		else if (Dz1Str_isVoid(userStr) == FALSE && (ret->user = Dz1Asn1UTF8Str_newFromStr(userStr, errp)) == NULL) ERR_OUT(errp);
		else if (Dz1Str_isVoid(passStr) == FALSE && (ret->pass = Dz1Asn1UTF8Str_newFromStr(passStr, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->periodic_sid = (u32_t)-1;
			ret->selected_codec = selected_codec;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (TestClientSession_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// TestClientSession API
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestClientSessionList API
typedef Dz1AATree TestClientSessionList;
static TestClientSessionList *TestClientSessionList_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestClientSessionList *ret = Dz1AATree_new((Dz1CmpFunc)TestClientSession_cmp, (Dz1DelFunc)TestClientSession_del, (Dz1DumpFunc)TestClientSession_dump, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}
#define TestClientSessionList_del				Dz1AATree_del
#define TestClientSessionList_delAndSetNull		Dz1AATree_delAndSetNull
#define TestClientSessionList_dump				Dz1AATree_dump

static TestClientSession *TestClientSessionList_find(TestClientSessionList *list, Dz1Asn1UTF8Str *peerDomain)
{
	TestClientSession *ret = NULL;
	if (list != NULL && peerDomain != NULL)
	{
		TestClientSession key; // = { peerDomain };
		key.peerDomain = peerDomain;
		ret = (TestClientSession *)Dz1AATree_find(list, (void *)&key);
	}
	return ret;
}

static TestClientSession *TestClientSessionList_extract(TestClientSessionList *list, Dz1Asn1UTF8Str *peerDomain)
{
	TestClientSession *ret = NULL;
	if (list != NULL && peerDomain != NULL)
	{
		TestClientSession key; //  = { peerDomain };
		key.peerDomain = peerDomain;
		ret = (TestClientSession *)Dz1AATree_extract(list, (void *)&key);
	}
	return ret;
}

static bool_t TestClientSessionList_add(TestClientSessionList *dst, TestClientSession *session, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || session == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = Dz1AATree_insert(dst, (void *)session)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static void TestClientSessionList_addCancel(void *ptr)
{
	Dz1ListAddCancelArg *arg = (Dz1ListAddCancelArg *)ptr;
	TestClientSessionList *list = (TestClientSessionList *)arg->list;
	TestClientSession **_session = (TestClientSession **)arg->node;
	if (list != NULL && _session != NULL && *_session != NULL)
		Dz1AATree_extract(list, (void *)(*_session));
}
// TestClientSessionList API
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestClientEnv API
typedef struct TestClientEnv
{
	void					*tSelf;
	Dz1Asn1UTF8Str			*myDomain;	// is ref
	TestClientSessionList	*sessions;
} TestClientEnv;

static void TestClientEnv_del(TestClientEnv *p)
{
	if (p != NULL)
	{
		TestClientSessionList_delAndSetNull(&p->sessions);
		Dz1Free(p);
	}
}

static void TestClientEnv_delAndSetNull(void *pptr)
{
	TestClientEnv **p = (TestClientEnv **)pptr;
	TestClientEnv_del(*p);
	*p = NULL;
}

static TestClientEnv *TestClientEnv_new(void *tSelf, Dz1Asn1UTF8Str *myDomain_ref, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestClientEnv *ret = (TestClientEnv *)Dz1Calloc(sizeof(TestClientEnv), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestClientEnv_delAndSetNull, (void *)&ret);
		if ((ret->sessions = TestClientSessionList_new(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->tSelf = tSelf;
			ret->myDomain = myDomain_ref;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (TestClientEnv_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// TestClientEnv API
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestClientTimer API
typedef struct TestClientTimer
{
	u32_t					id;
} TestClientTimer;

static void TestClientTimer_del(TestClientTimer *p)
{
	if (!p) return;
	Dz1Free(p);
}

static void TestClientTimer_delAndSetNull(void *pptr)
{
	TestClientTimer **p = (TestClientTimer **)pptr;
	TestClientTimer_del(*p);
	*p = NULL;
}

static TestClientTimer *TestClientTimer_new(u32_t id, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestClientTimer *ret = (TestClientTimer *)Dz1Calloc(sizeof(TestClientTimer), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->id = id;
		ERR_CLEAR(errp);
	}
	return ret;
}

void TestClientTimer_dump(TestClientTimer *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1Text("NULL\n"));
	else Dz1Thread_printf(Dz1Text("%u\n"), p->id);
}

int TestClientTimer_cmp(TestClientTimer *a, TestClientTimer *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL) ret = -1;
	else if (b == NULL) ret = 1;
	else if (a->id < b->id) ret = -1;
	else if (a->id > b->id) ret = -1;
	else ret = 0;
	return ret;
}
// TestClientTimer API
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestClient Init
#define TEST_CLIENT_MSG_DO_DEFAULT				0x00000001
#define TEST_CLIENT_MSG_DO_CONNECT				0x00000002
#define TEST_CLIENT_MSG_DO_DISCONNECT			0x00000003
#define TEST_CLIENT_MSG_DO_SINGLE				0x00000004
#define TEST_CLIENT_MSG_DO_PERIODIC				0x00000005

static Dz1Error TestClient_init(void **uRsc, void *tSelf, str_t name, u32_t my_queue_id, void *uArg, void *timer)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TestClientArg *arg = (TestClientArg *)uArg;
	TestClientEnv *env = NULL;
	if (( (*uRsc) = env = TestClientEnv_new(tSelf, arg->myDomain, errp)) == NULL) ERR_OUT(errp);
	else
	{

		pthread_cleanup_push(TestClientEnv_delAndSetNull, (void *)uRsc);

		if ((*errp = Dz1Task_post(tSelf, my_queue_id, TEST_CLIENT_MSG_DO_DEFAULT, NULL, NULL, NULL, NULL, NULL, NULL)).code) ERR_OUT(errp);
		else if ((*errp = ItsIso14827_createClient4Task(my_queue_id, t14827, arg->myDomain)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (TestClientEnv_delAndSetNull, (void *)uRsc);
	}
	return err;
}
// TestClient Init
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestClient Cleanup
static void TestClient_cleanup(void *uRsc)
{
	TestClientEnv *env = (TestClientEnv *)uRsc;
	pthread_cleanup_push(TestClientEnv_delAndSetNull, (void *)&env);

	ItsIso14827_deleteServer(t14827, env->myDomain);

	pthread_cleanup_pop(1); // (TestClientEnv_delAndSetNull, (void *)&env);
}
// TestClient Cleanup
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestClient Exception
static void TestClient_exception(void *uArg, void *uRsc, void *timer, Dz1Error *reason)
{
	Dz1Thread_printf(Dz1Text("!!! Test Server Exception\n"));
	ERR_OUT(reason);
}
// TestClient Exception
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestClient : Default Message Process
static Dz1TaskProcStatus _test_client_do_default(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	return ret;
}
// TestClient : Default Message Process
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestClient : Initiated
static void _initiate_response_fail(void *ptr)
{
	ItsIso14827SessionKey *key = (ItsIso14827SessionKey *)ptr;
	ItsIso14827_rejectInitiate(t14827, key);
}

static Dz1TaskProcStatus _test_client_initiate(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

 	TestClientArg *arg = (TestClientArg *)uArg;
 	TestClientEnv *env = (TestClientEnv *)uRsc;

	ItsIso14827ClientEventInitiate *msg = (ItsIso14827ClientEventInitiate *)Dz1TaskSigMsg_getData(*sg);

	Dz1Thread_printf("!!! Initiated\n");
	if (Dz1Asn1UTF8Str_cmp(arg->peerDomain, msg->peerDomain) != 0)
	{
		Dz1Thread_printf("!!! Expect Domain   = "); Dz1Asn1UTF8Str_dump(arg->peerDomain, 0);
		Dz1Thread_printf("!!! Initiate Domain = "); Dz1Asn1UTF8Str_dump(msg->peerDomain, 0);
	}
	else if (TestClientSessionList_find(env->sessions, msg->peerDomain) != NULL)
	{
		ERR_SET_OUT(errp, EEXIST);
		ItsIso14827_rejectInitiate(t14827, msg->key);
	}
	else
	{
		TestClientSession *session = NULL;
		pthread_cleanup_push(_initiate_response_fail, (void *)msg->key);
		if ((session = TestClientSession_new(NULL, NULL, NULL, arg->codec, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Iso14827RejectLogin bind_result = Iso14827RejectLogin_max;
			u8_t possible_codec = DZ1_ASN1_CODEC_BIT_BER;
			pthread_cleanup_push(TestClientSession_delAndSetNull, (void *)&session);

			session->peerDomain = msg->peerDomain;
			msg->peerDomain = NULL;
			if (TestClientSessionList_add(env->sessions, session, errp) == FALSE) ERR_OUT(errp);
			else
			{
				Dz1ListAddCancelArg add_cancel_arg; // = { (void *)env->sessions, (void **)&session };
				add_cancel_arg.list = (void *)env->sessions;
				add_cancel_arg.node = (void **)&session;

				pthread_cleanup_push(TestClientSessionList_addCancel, (void *)&add_cancel_arg);

				if ((session->user = Dz1Asn1OctetStr_clone(arg->user, errp)) == NULL) ERR_OUT(errp);
				else if ((session->pass = Dz1Asn1OctetStr_clone(arg->pass, errp)) == NULL) ERR_OUT(errp);
				else if ((*errp = ItsIso14827_bindWithServer(t14827, msg->key, env->myDomain, session->peerDomain, 
															 NULL, session->user, session->pass, possible_codec, 
															 CLIENT_HEARTBEAT_DURATION, CLIENT_RESPONSE_TIMEOUT, 0,
															 &session->selected_codec, &bind_result)).code)
				{
					Dz1Thread_printf(Dz1T("!!! Initiate Response Fail = %s\n"), Iso14827RejectLoginStr(bind_result));
					ERR_OUT(errp);
				}
				else
				{
					Dz1Error_set(errp, 0);
					session = NULL;
				}
				pthread_cleanup_pop(1); // (TestClientSessionList_addCancel, (void *)&add_cancel_arg);
			}
			pthread_cleanup_pop(1); // (TestClientSession_delAndSetNull, (void *)&session);
		}
		pthread_cleanup_pop(errp->code); // (_initiate_response_fail, (void *)msg->key);
	}
	return ret;
}
// TestClient : Initiated
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestClient : Terminated
static Dz1TaskProcStatus _test_client_terminate(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

 	TestClientArg *arg = (TestClientArg *)uArg;
 	TestClientEnv *env = (TestClientEnv *)uRsc;

	ItsIso14827ClientEventTerminate *msg = (ItsIso14827ClientEventTerminate *)Dz1TaskSigMsg_getData(*sg);
	TestClientSession *session = NULL;

	Dz1Thread_printf("Terminated = "); ItsIso14827ClientEventTerminate_dump(msg, 0);

	if ((session = TestClientSessionList_extract(env->sessions, msg->peerDomain)) != NULL)
	{
		pthread_cleanup_push(TestClientSession_delAndSetNull, (void *)&session);

		Dz1Thread_printf(Dz1T("Terminate Session = ")); TestClientSession_dump(session, 0);

		pthread_cleanup_pop(1); // (TestClientSession_delAndSetNull, (void *)&session);
	}

	return ret;
}
// TestClient : Terminated
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestClient : Publication
static Dz1TaskProcStatus _test_client_publication(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

 	TestClientArg *arg = (TestClientArg *)uArg;
 	TestClientEnv *env = (TestClientEnv *)uRsc;

	ItsIso14827ClientEventPublication *msg = (ItsIso14827ClientEventPublication *)Dz1TaskSigMsg_getData(*sg);
	TestClientSession *session = NULL;

	Dz1Thread_printf("<<< Publication(%u:%u) = %s\n", msg->sid, msg->pubSerial, msg->oidStr);
	Dz1Thread_tprintb(1, msg->encodedEAM, msg->encodedEAMSize, 16, FALSE);

	if ((session = TestClientSessionList_find(env->sessions, msg->peerDomain)) == NULL)
		Dz1Thread_printf(Dz1T("Session Not Found\n")); 
	else
	{
		void *dst = NULL;

		if (arg->eam_dec != NULL && arg->eam_dec(msg->oidStr, (void **)&dst, msg->encodedEAM, msg->encodedEAMSize, session->selected_codec, errp) < 0) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(arg->eam_del, (void *)dst);

			Dz1Thread_printf("Decoded = "); arg->eam_dump(dst, 0);

			pthread_cleanup_pop(1); // (arg->eam_del, (void *)dst);
		}
	}
	return ret;
}
// TestClient : Publication
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestClient : Publication Control
static Dz1TaskProcStatus _test_client_pub_control(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

 	TestClientArg *arg = (TestClientArg *)uArg;
 	TestClientEnv *env = (TestClientEnv *)uRsc;

	ItsIso14827ClientEventPubControl *msg = (ItsIso14827ClientEventPubControl *)Dz1TaskSigMsg_getData(*sg);
	TestClientSession *session = NULL;

	Dz1Thread_printf("<< Pub Control(%u:%u) = %s(%d)\n", msg->sid, msg->pubSerial, Iso14827PublicationMgmtStr(msg->cmd), msg->cmd);

	if ((session = TestClientSessionList_find(env->sessions, msg->peerDomain)) == NULL)
		Dz1Thread_printf(Dz1T("Session Not Found\n")); 
	else
	{
		if (msg->sid == session->periodic_sid)
			session->periodic_sid = (u32_t)-1;
	}
	return ret;
}
// TestClient : Publication Control
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestClient : Disconnected
static Dz1TaskProcStatus _test_client_disconnected(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

 	TestClientArg *arg = (TestClientArg *)uArg;
 	TestClientEnv *env = (TestClientEnv *)uRsc;

	ItsIso14827EventDisconnected *msg = (ItsIso14827EventDisconnected *)Dz1TaskSigMsg_getData(*sg);
	TestClientSession *session = NULL;

	Dz1Thread_printf("Disconnected = "); ItsIso14827EventDisconnected_dump(msg, 0);

	if ((session = TestClientSessionList_extract(env->sessions, msg->peerDomain)) != NULL)
	{
		pthread_cleanup_push(TestClientSession_delAndSetNull, (void *)&session);

		Dz1Thread_printf(Dz1T("Terminate Session = ")); TestClientSession_dump(session, 0);

		pthread_cleanup_pop(1); // (TestClientSession_delAndSetNull, (void *)&session);
	}
	return ret;
}
// TestClient : Disconnected
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestClient : Connect Message API
typedef struct TestClientMsgConnect
{
	Dz1SockAddr				*dst_addr;
	Dz1Str					 peerDomainStr;
	Dz1Str					 userStr;
	Dz1Str					 passStr;
} TestClientMsgConnect;

static void TestClientMsgConnect_del(TestClientMsgConnect *p)
{
	if (p != NULL)
	{
		Dz1SockAddr_delAndSetNull(&p->dst_addr);
		Dz1Str_delAndSetNull(&p->peerDomainStr);
		Dz1Str_delAndSetNull(&p->userStr);
		Dz1Str_delAndSetNull(&p->passStr);
		Dz1Free(p);
	}
}

static void TestClientMsgConnect_delAndSetNull(void *pptr)
{
	TestClientMsgConnect **p = (TestClientMsgConnect **)pptr;
	TestClientMsgConnect_del(*p);
	*p = NULL;
}

static TestClientMsgConnect *TestClientMsgConnect_new(Dz1SockAddr *dst_addr, Dz1Str peerDomainStr, Dz1Str userStr, Dz1Str passStr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestClientMsgConnect *ret = NULL;
	
	if (dst_addr == NULL || Dz1Str_isVoid(peerDomainStr) || Dz1Str_isVoid(userStr) || Dz1Str_isVoid(passStr)) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (TestClientMsgConnect *)Dz1Calloc(sizeof(TestClientMsgConnect), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestClientMsgConnect_delAndSetNull, (void *)&ret);
		if ((ret->dst_addr = Dz1SockAddr_clone(dst_addr, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->peerDomainStr = Dz1Str_clone(peerDomainStr, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->userStr = Dz1Str_clone(userStr, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->passStr = Dz1Str_clone(passStr, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (TestClientMsgConnect_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static void TestClientMsgConnect_dump(TestClientMsgConnect *p, int tab)
{
	if (p == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		TCHAR addrStr[64];
		Dz1SockAddr_printable(p->dst_addr, addrStr, FALSE, NULL);
		Dz1Thread_printf(Dz1T("%s:%s@%s to %s\n"), p->userStr, p->passStr, p->peerDomainStr, addrStr);
	}
}
// TestClient : Connect Message API
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestClient : Connect
static Dz1TaskProcStatus _TestClient_connect(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

 	TestClientArg *arg = (TestClientArg *)uArg;
 	TestClientEnv *env = (TestClientEnv *)uRsc;

	TestClientMsgConnect *msg = (TestClientMsgConnect *)Dz1TaskSigMsg_getData(*sg);
	TestClientSession *session = NULL;

	Dz1Thread_printf(Dz1T("@@@ Connect = ")); TestClientMsgConnect_dump(msg, 0);

	if ((session = TestClientSession_new(msg->peerDomainStr, msg->userStr, msg->passStr, Dz1Asn1Codec_ber, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestClientSession_delAndSetNull, (void *)&session);
		if (TestClientSessionList_add(env->sessions, session, errp) == FALSE) ERR_OUT(errp);
		else
		{
			u8_t possible_codec = DZ1_ASN1_CODEC_BIT_BER;
			Iso14827RejectLogin result = Iso14827RejectLogin_max;
			Dz1ListAddCancelArg add_cancel_arg; // = { env->sessions, (void **)&session };
			add_cancel_arg.list = (void *)env->sessions;
			add_cancel_arg.node = (void **)&session;

			pthread_cleanup_push(TestClientSessionList_addCancel, (void *)&add_cancel_arg);

			if ((*errp = ItsIso14827_connectToServer(t14827, msg->dst_addr, env->myDomain, session->peerDomain, 
													 NULL, session->user, session->pass, possible_codec,
													 CLIENT_HEARTBEAT_DURATION, CLIENT_RESPONSE_TIMEOUT, 0, 
													 &session->selected_codec, ItsIso14827CRCCheck_warning, &result)).code) ERR_OUT(errp);
			else
			{
				session = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (TestClientSessionList_addCancel, (void *)&add_cancel_arg);
		}
		pthread_cleanup_pop(1); // (TestClientSession_delAndSetNull, (void *)&session);
	}
	return ret;
}

bool_t TestClient_connect(void *tClient, Dz1SockAddr *dst_addr, Dz1Str peerDomainStr, Dz1Str userStr, Dz1Str passStr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestClientMsgConnect *msg = TestClientMsgConnect_new(dst_addr, peerDomainStr, userStr, passStr, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestClientMsgConnect_delAndSetNull, (void *)&msg);
		if ((*errp = Dz1Task_post(tClient, DZ1_TASK_QUEUE_NONE,
								  TEST_CLIENT_MSG_DO_CONNECT, (void **)&msg,
								  (Dz1DelFunc)TestClientMsgConnect_del,
								  (Dz1DumpFunc)TestClientMsgConnect_dump,
								  NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (TestClientMsgConnect_delAndSetNull, (void *)&msg);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// TestClient : Connect
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestClient : Disconnect Message API
typedef struct TestClientMsgDisconnect
{
	Dz1Str					 peerDomain;
} TestClientMsgDisconnect;

static void TestClientMsgDisconnect_del(TestClientMsgDisconnect *p)
{
	if (p != NULL)
	{
		Dz1Str_delAndSetNull(&p->peerDomain);
		Dz1Free(p);
	}
}

static void TestClientMsgDisconnect_delAndSetNull(void *pptr)
{
	TestClientMsgDisconnect **p = (TestClientMsgDisconnect **)pptr;
	TestClientMsgDisconnect_del(*p);
	*p = NULL;
}

static TestClientMsgDisconnect *TestClientMsgDisconnect_new(Dz1Str peerDomain, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestClientMsgDisconnect *ret = NULL;
	if (Dz1Str_isVoid(peerDomain)) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (TestClientMsgDisconnect *)Dz1Calloc(sizeof(TestClientMsgDisconnect), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestClientMsgDisconnect_delAndSetNull, (void *)&ret);
		if ((ret->peerDomain = Dz1Str_clone(peerDomain, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (TestClientMsgDisconnect_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static void TestClientMsgDisconnect_dump(TestClientMsgDisconnect *p, int tab)
{
	if (p == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("peerDomain = %s\n"), p->peerDomain);
}
// TestClient : Disconnect Message API
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestClient : Disconnect
static Dz1TaskProcStatus _TestClient_disconnect(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

 	TestClientArg *arg = (TestClientArg *)uArg;
 	TestClientEnv *env = (TestClientEnv *)uRsc;

	TestClientMsgDisconnect *msg = (TestClientMsgDisconnect *)Dz1TaskSigMsg_getData(*sg);
	TestClientSession *session = NULL;

	Dz1Asn1UTF8Str *peerDomain = NULL;

	Dz1Thread_printf(Dz1T("@@@ Disconnect = ")); TestClientMsgDisconnect_dump(msg, 0);

	if ((peerDomain = Dz1Asn1UTF8Str_newFromStr(msg->peerDomain, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&peerDomain);
		if ((session = TestClientSessionList_extract(env->sessions, peerDomain)) != NULL)
		{
			pthread_cleanup_push(TestClientSession_delAndSetNull, (void *)&session);

			Dz1Thread_printf(Dz1T("Terminate Session = ")); TestClientSession_dump(session, 0);
			ItsIso14827_disconnectFromServer(t14827, env->myDomain, session->peerDomain, session->user, Iso14827Logout_clientRequested);

			pthread_cleanup_pop(1); // (TestClientSession_delAndSetNull, (void *)&session);
		}
		pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&peerDomain);
	}
	return ret;
}

bool_t TestClient_disconnect(void *tClient, Dz1Str peerDomainStr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestClientMsgDisconnect *msg = TestClientMsgDisconnect_new(peerDomainStr, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestClientMsgDisconnect_delAndSetNull, (void *)&msg);
		if ((*errp = Dz1Task_post(tClient, DZ1_TASK_QUEUE_NONE, TEST_CLIENT_MSG_DO_DISCONNECT, (void **)&msg,
								  (Dz1DelFunc)TestClientMsgDisconnect_del,
								  (Dz1DumpFunc)TestClientMsgDisconnect_dump,
								  NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (TestClientMsgDisconnect_delAndSetNull, (void *)&msg);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// TestClient : Disconnect
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestClientSubscribe API
typedef struct TestClientSubscribe
{
	Dz1Str					 peerDomain;
	u32_t					 req_code;
} TestClientSubscribe;

static void TestClientSubscribe_del(TestClientSubscribe *p)
{
	if (!p) return;
	Dz1Str_delAndSetNull(&p->peerDomain);
	Dz1Free(p);
}

static void TestClientSubscribe_delAndSetNull(void *pptr)
{
	TestClientSubscribe **p = (TestClientSubscribe **)pptr;
	TestClientSubscribe_del(*p);
	*p = NULL;
}

TestClientSubscribe *TestClientSubscribe_new(Dz1Str peerDomain, u32_t req_code, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestClientSubscribe *ret = (TestClientSubscribe *)Dz1Calloc(sizeof(TestClientSubscribe), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestClientSubscribe_delAndSetNull, (void *)&ret);

		if (0) { }
		// additional initialize code here
		else if ((ret->peerDomain = Dz1Str_clone(peerDomain, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->req_code = req_code;
			ERR_CLEAR(errp);
		}

		pthread_cleanup_pop(errp->code); // (TestClientSubscribe_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void TestClientSubscribe_dump(TestClientSubscribe *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1Text("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s(%u)\n"), p->peerDomain, p->req_code);
}
// TestClientSubscribe API
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestClient : Single Subscription
static Dz1TaskProcStatus _TestClient_single(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

 	TestClientArg *arg = (TestClientArg *)uArg;
 	TestClientEnv *env = (TestClientEnv *)uRsc;

	TestClientSubscribe *msg = (TestClientSubscribe *)Dz1TaskSigMsg_getData(*sg);
	TestClientSession *session = NULL;

	Dz1Asn1UTF8Str *peerDomain = NULL;

	Dz1Thread_printf(Dz1T("@@@ Single Subscription = ")); TestClientSubscribe_dump(msg, 0);

	if ((peerDomain = Dz1Asn1UTF8Str_newFromStr(msg->peerDomain, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&peerDomain);
		if ((session = TestClientSessionList_find(env->sessions, peerDomain)) != NULL)
		{
			MsgGenerator *api = NULL;
			void *sub_req = NULL;
			if ((api = MsgGenerator_find(msg->req_code, arg->generator)) == NULL) ERR_SET_OUT(errp, ENOSYS);
			else if ((sub_req = api->gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				u8_t *buf = NULL;
				Dz1Str oidStr = NULL;
				ssize_t size = 0;
				pthread_cleanup_push(api->delAndSetNull, (void *)&sub_req);

				if ((size = arg->eam_enc(sub_req, &buf, session->selected_codec, &oidStr, errp)) < 0) ERR_OUT(errp);
				else
				{
					u32_t subID = 0;
					pthread_cleanup_push(Dz1Memory_cancel, (void *)buf);

					if ((*errp = ItsIso14827_singleRequest(t14827, ItsIso14827DomainType_client, env->myDomain, session->peerDomain, session->user, 
														   1, FALSE, oidStr, buf, size, &subID, NULL)).code) ERR_OUT(errp);
					else Dz1Thread_printf("Subscription ID = %u\n", subID);

					pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)buf);
				}
				pthread_cleanup_pop(1); // (api->delAndSetNull, (void *)&sub_req);
			}
		}
		pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&peerDomain);
	}
	return ret;
}

bool_t TestClient_single(void *tClient, Dz1Str peerDomainStr, u32_t req_code, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestClientSubscribe *msg = TestClientSubscribe_new(peerDomainStr, req_code, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestClientSubscribe_delAndSetNull, (void *)&msg);

		if ((*errp = Dz1Task_post(tClient, DZ1_TASK_QUEUE_NONE, TEST_CLIENT_MSG_DO_SINGLE, (void **)&msg,
								  (Dz1DelFunc)TestClientSubscribe_del,
								  (Dz1DumpFunc)TestClientSubscribe_dump,
								  NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(1); // (TestClientSubscribe_delAndSetNull, (void *)&msg);
	}
	return errp->code == 0 ? TRUE : FALSE;;
}
// TestClient : Single Subscription
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TestClient : Registered Subscription(Periodic)
static Dz1TaskProcStatus _TestClient_periodic(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

 	TestClientArg *arg = (TestClientArg *)uArg;
 	TestClientEnv *env = (TestClientEnv *)uRsc;

	TestClientSubscribe *msg = (TestClientSubscribe *)Dz1TaskSigMsg_getData(*sg);
	TestClientSession *session = NULL;

	Dz1Asn1UTF8Str *peerDomain = NULL;

	Dz1Thread_printf(Dz1T("@@@ Periodic Subscription = ")); TestClientSubscribe_dump(msg, 0);
	if ((peerDomain = Dz1Asn1UTF8Str_newFromStr(msg->peerDomain, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&peerDomain);
		if ((session = TestClientSessionList_find(env->sessions, peerDomain)) != NULL)
		{
			if (msg->req_code == (u32_t)-1)
			{
				if (session->periodic_sid == (u32_t)-1) ERR_SET_OUT(errp, ENOENT);
				else if ((*errp = ItsIso14827_requestCancel(t14827, ItsIso14827DomainType_client,
															env->myDomain, session->peerDomain, session->user, 
															session->periodic_sid, Iso14827SubscriptionCancel_dataNotNeeded)).code) ERR_OUT(errp);
				else
				{
					session->periodic_sid = (u32_t)-1;
					Dz1Error_set(errp, 0);
				}
			}
			else if (session->periodic_sid != (u32_t)-1) ERR_SET_OUT(errp, EEXIST);
			else
			{
				void *sub_req = NULL;
				MsgGenerator *api = NULL;
				
				if ((api = MsgGenerator_find(msg->req_code, arg->generator)) == NULL) ERR_SET_OUT(errp, ENOSYS);
				else if ((sub_req = api->gen(errp)) == NULL) ERR_OUT(errp);
				else
				{
					u8_t *buf = NULL;
					Dz1Str oidStr = NULL;
					ssize_t size = 0;
					pthread_cleanup_push(api->delAndSetNull, (void *)&sub_req);

					if ((size = arg->eam_enc(sub_req, &buf, session->selected_codec, &oidStr, errp)) < 0) ERR_OUT(errp);
					else
					{
						Iso14827RegisteredContinuous sch = { 10, NULL, NULL };
						pthread_cleanup_push(Dz1Memory_cancel, (void *)buf);
						if ((*errp = ItsIso14827_continuousRequest(t14827, ItsIso14827DomainType_client, 
																   env->myDomain, session->peerDomain, session->user, 
																   FALSE, 1, FALSE, TRUE, &sch, oidStr, buf, size, &session->periodic_sid, NULL)).code) ERR_OUT(errp);
						else Dz1Thread_printf("Subscription ID = %u\n", session->periodic_sid);
						pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)buf);
					}
					pthread_cleanup_pop(1); // (api->delAndSetNull, (void *)&sub_req);
				}
			}
		}
		pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&peerDomain);
	}
	return ret;
}

bool_t TestClient_periodic(void *tClient, Dz1Str peerDomainStr, u32_t req_code, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TestClientSubscribe *msg = TestClientSubscribe_new(peerDomainStr, req_code, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(TestClientSubscribe_delAndSetNull, (void *)&msg);

		if ((*errp = Dz1Task_post(tClient, DZ1_TASK_QUEUE_NONE, TEST_CLIENT_MSG_DO_PERIODIC, (void **)&msg,
								  (Dz1DelFunc)TestClientSubscribe_del,
								  (Dz1DumpFunc)TestClientSubscribe_dump,
								  NULL, NULL, NULL)).code) ERR_OUT(errp);
		else
		{
			msg = NULL;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(1); // (TestClientSubscribe_delAndSetNull, (void *)&msg);
	}
	return errp->code == 0 ? TRUE : FALSE;;
}
// TestClient : Registered Subscription(Periodic)
////////////////////////////////////////////////////////////////////////////////

void *TestClientTask_new(Dz1Str client_mode_str, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	void *ret = NULL;

	if ((selectedClient = ClientModeMap_find(client_mode_str)) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		TestClientArg *arg = TestClientArg_new(selectedClient->myDomainStr,
											   selectedClient->enc, selectedClient->dec,
											   selectedClient->del, selectedClient->dump,
											   selectedClient->genTable,
											   selectedClient->peerDomainStr, 
											   selectedClient->userStr, selectedClient->passStr, Dz1Asn1Codec_ber, errp);
		if (arg == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(TestClientArg_delAndSetNull, (void *)&arg);
			if ((ret = Dz1Task_new("TestClient", 1024, (void **)&arg, (Dz1DelFunc)TestClientArg_del, (Dz1CmpFunc)TestClientTimer_cmp, 
									TestClient_init, TestClient_exception, TestClient_cleanup, errp)) == NULL) ERR_OUT(errp);
			else
			{
				ItsIso14827ClientTaskHandler handle = 
				{
					_test_client_initiate,
					_test_client_terminate,
					_test_client_publication,
					_test_client_pub_control,
					_test_client_disconnected
				};
				pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&ret);
				if (0) { }
				else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(TEST_CLIENT_MSG_DO_DEFAULT), _test_client_do_default)).code) ERR_OUT(errp);
				else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(TEST_CLIENT_MSG_DO_CONNECT), _TestClient_connect)).code) ERR_OUT(errp);
				else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(TEST_CLIENT_MSG_DO_DISCONNECT), _TestClient_disconnect)).code) ERR_OUT(errp);
				else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(TEST_CLIENT_MSG_DO_SINGLE), _TestClient_single)).code) ERR_OUT(errp);
				else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(TEST_CLIENT_MSG_DO_PERIODIC), _TestClient_periodic)).code) ERR_OUT(errp);
				else if ((*errp = ItsIso14827_clientTaskMsgInit(ret, &handle)).code) ERR_OUT(errp);
				else
				{
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(errp->code); // (Dz1Task_delAndSetNull, (void *)&ret);
			}
			pthread_cleanup_pop(1); // (TestServerArg_delAndSetNull, (void *)&arg);
		}
	}
	return ret;
}


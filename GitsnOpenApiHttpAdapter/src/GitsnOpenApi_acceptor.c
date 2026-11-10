#include <Dz1SockUtil.h>

#include "GitsnOpenApiEnv.h"
#include "GitsnOpenApi_acceptor.h"

/* Large multipart uploads are part of the PRJ1 conformance tests.  A 2 KiB
 * callback buffer turns a 30 MiB upload into more than fifteen thousand task
 * messages and can delay the HTTP response beyond the test timeout. */
#define GITSN_OPEN_API_SERVER_RX_CHUNK_SIZE (64U * 1024U)

///////////////////////////////////////////////////////////////////////////////
// Acceptor
static Dz1TaskProcStatus _acceptor_connected(void *uArv, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	// GitsnOpenApiArg *arg = (GitsnOpenApiArg *)uArg;
	GitsnOpenApiEnv *env = (GitsnOpenApiEnv *)uRsc;
	u32_t my_queue_id = Dz1Task_getQueueID(env->tSelf);
	GitsnOpenApiSessions *sessions = env->sessions;
	GitsnOpenApiSession *session = NULL;

	Dz1SockUtilAcceptorConnected *msg = (Dz1SockUtilAcceptorConnected *)Dz1TaskSigMsg_getData(*sg);
	
	if ((session = GitsnOpenApiSession_new(sessions->alloc_id, msg->peer, msg->local, msg->sock, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		GitsnOpenApiHttpParser *parser = NULL;
		session->peer = msg->peer; msg->peer = NULL;
		session->local = msg->local; msg->local = NULL;
		session->sock = msg->sock; msg->sock = NULL;
		pthread_cleanup_push(GitsnOpenApiSession_delAndSetNull, (void *)&session);
		if (0) { }
		else if ((session->tx_fifo = Dz1SockUtilTxFifo_new(errp)) == NULL) ERR_OUT(errp);
		else if ((session->parser = parser = GitsnOpenApiHttpParser_new(NULL, -1, errp)) == NULL) ERR_OUT(errp);
		else if ((parser->rx_buf = Dz1ElasticBuf_new(GITSN_OPEN_API_SERVER_RX_CHUNK_SIZE, FALSE, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1SockUtilTcpClient_mode2Callback(session->id, session->sock, session->peer, session->local,
		                                                   GITSN_OPEN_API_SERVER_RX_CHUNK_SIZE, my_queue_id)).code) ERR_OUT(errp);
		else if ((*errp = sessions->table->add(sessions->table, session)).code) ERR_OUT(errp);
		else
		{
			sessions->alloc_id++;
			session = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (GitsnOpenApiSession_delAndSetNull, (void *)&session);
	}
	return ret;
}

static Dz1TaskProcStatus _acceptor_exception(void *uArv, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{
	Dz1Error *reason = Dz1TaskSigMsg_getErrPtr(*sg);
	memcpy(errp, reason, sizeof(Dz1Error));
	Dz1Thread_printf(Dz1T("!!! Acceptor exception\n"));
	ERR_OUT(errp);
	return Dz1TaskProcStatus_error;
}
// Acceptor
///////////////////////////////////////////////////////////////////////////////

bool_t GitsnOpenApi_acceptorMsgInit(Dz1Task *task, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (task == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_ACCEPTOR_CONNECTED), _acceptor_connected)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(DZ1_SOCK_UTIL_ACCEPTOR_EXCEPTION), _acceptor_exception)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}

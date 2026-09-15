#include "ItsIso14827SocketReceiverDef.h"
#include "ItsIso14827SocketReceiver.h"
#include "ItsIso14827SocketReceiverMsg.h"

static Dz1SocketReceierBehavior ItsIsoSocketReceiver_forward(void *uArg, void *uRsc, 
																   Dz1SockAddr *peer, Dz1SockAddr *local,
																   Dz1TcpClientSocket *s,
																   u8_t *data, size_t size, Dz1Error *errp)
{
	Dz1SocketReceierBehavior ret = Dz1SocketReceierBehavior_continue;

	ItsIso14827SocketReceiverArg *arg = (ItsIso14827SocketReceiverArg *)uArg;
	u32_t dstQueueID = arg->parentQueueID;

	ItsIsoSocketReceiverReceived *msg = ItsIsoSocketReceiverReceived_new(NULL, NULL, time(NULL), errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		ItsIso14827SessionKey *key = NULL;
		pthread_cleanup_push(ItsIsoSocketReceiverReceived_delAndSetNull, (void *)&msg);
		if ((msg->key = key = ItsIso14827SessionKey_new(NULL, NULL, arg->sid, errp)) == NULL) ERR_OUT(errp);
		else if ((key->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((key->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->packet = Dz1Binary_new(data, (u32_t)size, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dstQueueID, DZ1_TASK_QUEUE_NONE,
										ITS_ISO_SERVER_RECEIVER_RECEIVED, (void **)&msg,
										(Dz1DelFunc)ItsIsoSocketReceiverReceived_del,
										(Dz1DumpFunc)ItsIsoSocketReceiverReceived_dump,
										NULL, NULL, NULL)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (ItsIsoSocketReceiverReceived_delAndSetNull, (void *)&msg);
	}
	return ret;
}

static void ItsIsoSocketReceiver_exception(void *uArg, void *uRsc,
												 Dz1SockAddr *peer, Dz1SockAddr *local,
												 Dz1TcpClientSocket *s, Dz1Error *reason)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ItsIso14827SocketReceiverArg *arg = (ItsIso14827SocketReceiverArg *)uArg;
	u32_t dstQueueID = arg->parentQueueID;

	ItsIso14827SessionKey *msg = NULL;
	
	Dz1Thread_printf("ItsIsoSocketReceiver_exception() : Exception Catch!!!\n");
	ERR_OUT(reason);

	if ((msg = ItsIso14827SessionKey_new(NULL, NULL, arg->sid, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(ItsIso14827SessionKey_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(peer, &err)) == NULL) ERR_OUT(&err);
		else if ((msg->local = Dz1SockAddr_clone(local, &err)) == NULL) ERR_OUT(&err);
		else if ((err = Dz1Task_queuePost(dstQueueID, DZ1_TASK_QUEUE_NONE,
										ITS_ISO_SERVER_RECEIVER_EXCEPTION, (void **)&msg,
										(Dz1DelFunc)ItsIso14827SessionKey_del,
										(Dz1DumpFunc)ItsIso14827SessionKey_dump,
										reason, NULL, NULL)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (ItsIso14827SessionKey_delAndSetNull, (void *)&msg);
	}
}

u32_t ItsIsoSocketReceiver_start(void *tParent, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket *sock, u32_t sid, Dz1Error *err)
{
	u32_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	u32_t dstQueueID = Dz1Task_getQueueID(tParent);
	ItsIso14827SocketReceiverArg *arg = ItsIso14827SocketReceiverArg_new(dstQueueID, sid, errp);
	if (arg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIso14827SocketReceiverArg_delAndSetNull, (void *)&arg);

		if ((ret = Dz1TcpSocketReceiver_start(peer, local, 4096, 0, &sock, FALSE,
											NULL,
											ItsIsoSocketReceiver_forward,
											ItsIsoSocketReceiver_exception,
											NULL,
											NULL,
											(void **)&arg, (Dz1DelFunc)ItsIso14827SocketReceiverArg_del,
											errp)) == -1) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (ItsIso14827SocketReceiverArg_delAndSetNull, (void *)&arg);
	}
	return ret;
}

void ItsIsoSocketReceiver_stop(u32_t thID)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = Dz1TcpSocketReceiver_stop(thID)).code) ERR_OUT(&err);
}

#include <dz1_socket_acceptor.h>

#include "ItsIso14827Env.h"

#include "ItsIso14827SocketAcceptorMsg.h"
#include "ItsIso14827SocketAcceptor.h"
#include "ItsIso14827SocketAcceptorDef.h"
#include "ItsIso14827SessionMgr_main.h"

static Dz1TcpSocketAcceptorBehavior ItsIosSocketAcceptor_forward(void *uArg, void *uRsc,
																 Dz1TcpClientSocket **s,
																 Dz1SockAddr *local,
																 Dz1SockAddr *peer,
																 Dz1Error *errp)
{
	ItsIsoAcceptor *arg = (ItsIsoAcceptor *)uArg;
	u32_t dstQueueID = arg->dstQueueID;

	Dz1TcpSocketAcceptorBehavior ret = Dz1TcpSocketAcceptorBehavior_continue;
	ItsIsoAcceptorConnected *msg = ItsIsoAcceptorConnected_new(NULL, NULL, (*s),
															   arg->initialCodec,
															   arg->CRCCheck, errp);
	if (msg == NULL) ERR_OUT(errp);
	else
	{
		Dz1Thread_printf("!!!!!!! Connected ID = %08X\n", ITS_ISO_SERVER_ACCEPTOR_CONNECTED);
		(*s) = NULL;
		pthread_cleanup_push(ItsIsoAcceptorConnected_delAndSetNull, (void *)&msg);
		if ((msg->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((msg->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1Task_queuePost(dstQueueID, DZ1_TASK_QUEUE_NONE,
											ITS_ISO_SERVER_ACCEPTOR_CONNECTED, (void **)&msg,
											(Dz1DelFunc)ItsIsoAcceptorConnected_del,
											(Dz1DumpFunc)ItsIsoAcceptorConnected_dump,
											NULL, NULL, NULL)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (ItsIsoAcceptorConnected_delAndSetNull, (void *)&msg);
	}
	return ret;
}

static void ItsIosSocketAcceptor_exception(void *uArg, void *uRsc, Dz1TcpServerSocket *s, Dz1Error *reason)
{
	ItsIsoAcceptor *arg = (ItsIsoAcceptor *)uArg;
	u32_t dstQueueID = arg->dstQueueID;
	Dz1Thread_printf("ItsIosServerSocketAcceptor_exception() : EXCEPTION!!!\n");
	ERR_OUT(reason);
	Dz1Task_queuePostSimpleErr(dstQueueID, DZ1_TASK_QUEUE_NONE, ITS_ISO_SERVER_ACCEPTOR_EXCEPTION, reason);
}

u32_t ItsIosSocketAcceptor_start(u32_t dstQueueID, Dz1SockAddr *addr,
								 Dz1Asn1Codec initialCodec,
								 ItsIso14827CRCCheck CRCCheck,
								 Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	u32_t ret = -1;
	Dz1TcpServerSocket *sock = NULL;
	
	ItsIsoAcceptor *arg = ItsIsoAcceptor_new(dstQueueID, initialCodec, CRCCheck, errp);
	if (arg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ItsIsoAcceptor_delAndSetNull, (void *)&arg);

		if ((sock = Dz1TcpServerSocket_open(addr, NULL, 5, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1TcpClientSocket_closeAndSetNull, (void *)&sock);
			if ((ret = Dz1TcpSocketAcceptor_start(sock, TRUE, 0, 10000,
												NULL,
												ItsIosSocketAcceptor_forward,
												ItsIosSocketAcceptor_exception,
												NULL,
												NULL,
												(void **)&arg, (Dz1DelFunc)ItsIsoAcceptor_del,
												errp)) == -1) ERR_OUT(errp);
			else sock = NULL;
			pthread_cleanup_pop(1); // (Dz1TcpClientSocket_closeAndSetNull, (void *)&sock);
		}
		pthread_cleanup_pop(1); // (ItsIsoAcceptor_delAndSetNull, (void *)&arg);
	}
	return ret;
}

void ItsIosSocketAcceptor_stop(u32_t thID)
{
	Dz1TcpSocketAcceptor_stop(thID);
}

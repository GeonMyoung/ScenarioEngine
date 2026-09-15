#include "dz1_inet_ftp_env_util.h"
#include "dz1_inet_ftp_msg.h"
#include "dz1_inet_ftp_dtp.h"
#include "dz1_inet_ftp_timer_util.h"
#include "dz1_inet_ftp_message.h"
#include "dz1_inet_ftp_fsm.h"
Dz1TaskProcStatus Dz1InetFtp_disconnected(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Dz1InetFtpEnv *env = (Dz1InetFtpEnv *)uRsc;

	Dz1InetFtpRcvrMsgException *msg = (Dz1InetFtpRcvrMsgException *)Dz1TaskSigMsg_getData(*sg);

	Dz1InetFtpSession key = { msg->peer, msg->local }, *session = NULL;
	if ((session = env->sessionList->extract(env->sessionList, &key)) != NULL)
	{
		Dz1InetFtpSessionCleanupRuntimeArg cleanupArg = { session, timer };
		pthread_cleanup_push(Dz1InetFtpSession_cleanupRunTime, (void *)&cleanupArg);

		Dz1Thread_printf("Dz1InetFtp_disconnected() : Session Terminate = ");
		Dz1InetFtpSession_dump(session, 0);

		pthread_cleanup_pop(1); // (Dz1InetFtpSession_cleanupRunTime, (void *)&cleanupArg);
	}

	return ret;
}

Dz1TaskProcStatus Dz1InetFtp_trasferDone(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Dz1InetFtpEnv *env = (Dz1InetFtpEnv *)uRsc;

	Dz1InetFtpMsgFileDone *msg = (Dz1InetFtpMsgFileDone *)Dz1TaskSigMsg_getData(*sg);

	Dz1InetFtpSession key = { msg->peer, msg->local }, *session = NULL;
	
	Dz1Thread_printf("Dz1InetFtp_trasferDone() : Message = "); Dz1InetFtpMsgFileDone_dump(msg, 0);

	if ((session = env->sessionList->find(env->sessionList, &key)) != NULL)
	{
		if (session->dtp != (u32_t)-1) Dz1InetFtpDTP_stop(session->dtp);
		session->dtp = -1;

		if (session->dataSock != NULL) Dz1TcpClientSocket_closeAndSetNull(&session->dataSock);
		if (session->portSock != NULL) Dz1TcpServerSocket_closeAndSetNull(&session->portSock);

		ret = Dz1InetFtpFsm_replyMsgProc2(session, uArg, uRsc, timer, Dz1InetFtpEvent_transferDone, NULL, errp);
	}

	return ret;
}

Dz1TaskProcStatus Dz1InetFtp_trasferFail(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Dz1InetFtpEnv *env = (Dz1InetFtpEnv *)uRsc;

	Dz1InetFtpMsgFileDone *msg = (Dz1InetFtpMsgFileDone *)Dz1TaskSigMsg_getData(*sg);

	Dz1InetFtpSession key = { msg->peer, msg->local }, *session = NULL;
	
	Dz1Thread_printf("Dz1InetFtp_trasferFail() : Message = "); Dz1InetFtpMsgFileDone_dump(msg, 0);

	if ((session = env->sessionList->find(env->sessionList, &key)) != NULL)
	{
		if (session->dtp != (u32_t)-1) Dz1InetFtpDTP_stop(session->dtp);
		session->dtp = -1;

		if (session->dataSock != NULL) Dz1TcpClientSocket_closeAndSetNull(&session->dataSock);
		if (session->portSock != NULL) Dz1TcpServerSocket_closeAndSetNull(&session->portSock);

		ret = Dz1InetFtpFsm_replyMsgProc2(session, uArg, uRsc, timer, Dz1InetFtpEvent_error, NULL, errp);
	}
	return ret;
}

Dz1TaskProcStatus Dz1InetFtp_extendTimeout(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;
	Dz1InetFtpEnv *env = (Dz1InetFtpEnv *)uRsc;

	Dz1InetFtpBasicMsg *msg = (Dz1InetFtpBasicMsg *)Dz1TaskSigMsg_getData(*sg);

	Dz1InetFtpSession key = { msg->peer, msg->local }, *session = NULL;
	
	//Dz1Thread_printf("Dz1InetFtp_extendTimeout() : Message = "); Dz1InetFtpBasicMsg_dump(msg, 0);

	if ((session = env->sessionList->find(env->sessionList, &key)) != NULL)
	{
		Dz1InetFtpTransferNode *curJob = session->curJob;
		Dz1InetFtpTransfer *target = curJob->target;
		Dz1InetFtpFileName *remote = target->remote;
		if (target->direction == Dz1InetFtpDirection_upload)
		{
			Dz1InetFtpFileInfo *local = target->local;
			if (local->present == Dz1InetFtpFileInfoPresent_file)
			{
				Dz1InetFtpFileName *file = local->x.file;
				if (file->size == -1) Dz1Thread_printf("### FTP : upload %s - %u Byte\n", remote->name, msg->size);
				else Dz1Thread_printf("### FTP : upload %s - %u/%u Byte\n", remote->name, msg->size, file->size);
			}
			else if (local->present == Dz1InetFtpFileInfoPresent_buffer)
			{
				Dz1Binary *bin = local->x.buffer;
				Dz1Thread_printf("### FTP : upload %s - %u/%u Byte\n", remote->name, msg->size, bin->size);
			}
		}
		else
		{
			Dz1Thread_printf("### FTP : download %s - %u/%u Byte\n", remote->name, msg->size, remote->size);
		}

		Dz1InetFtpTimer_resetMsgWait(timer, msg->peer, msg->local);
	}

	return ret;
}


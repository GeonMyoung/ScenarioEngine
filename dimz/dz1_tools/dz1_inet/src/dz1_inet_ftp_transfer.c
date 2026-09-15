#include <dz1_inet_ftp.h>
#include "dz1_inet_ftp_env_util.h"
#include "dz1_inet_ftp_arg.h"
#include "dz1_inet_ftp_timer.h"
#include "dz1_inet_ftp_fsm.h"
#include "dz1_inet_ftp_msg.h"
#include "dz1_inet_ftp_receiver.h"
#include "dz1_inet_ftp_def_util.h"
#include "dz1_inet_ftp_transfer.h"

static Dz1Error _Dz1InetFtp_transferFail(void *ptr, Dz1InetFtpTransfer *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpMsgTransfer *msg = (Dz1InetFtpMsgTransfer *)ptr;
	p->result = Dz1InetFtpCmdResult_unknown;
	// XXX: 상대방 Ftp 서버가 없을 경우 메모리릭 발생 우선은 단순하게 msg->fileDone체크하게 함 min
	if ( msg->fileDone)
	{
		msg->fileDone(msg->fileDoneParam, msg->peer, p);
	}
	return err;
}

static void Dz1InetFtp_transferFail(void *ptr)
{
	Dz1InetFtpMsgTransfer *msg = (Dz1InetFtpMsgTransfer *)ptr;
	Dz1InetFtpTransferList *files = msg->files;
	files->travel(files, _Dz1InetFtp_transferFail, (void *)msg);
}

Dz1TaskProcStatus Dz1InetFtp_transfer(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1InetFtpArg *arg = (Dz1InetFtpArg *)uArg;
	Dz1InetFtpEnv *env = (Dz1InetFtpEnv *)uRsc;

	Dz1InetFtpMsgTransfer *msg = (Dz1InetFtpMsgTransfer *)Dz1TaskSigMsg_getData(*sg);

	Dz1InetFtpSession *session = NULL;

	pthread_cleanup_push(Dz1InetFtp_transferFail, (void *)msg);

	if ((session = Dz1InetFtpSession_new(NULL, NULL, NULL, -1,
										msg->user, msg->pass, msg->account, msg->isPassive,
										arg->localCharSetName,
										NULL, -1, msg->fileDone, msg->fileDoneParam,
										NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1SockAddr local;
		struct timeval to = { 30, 0 };
		pthread_cleanup_push(Dz1InetFtpSession_delAndSetNull, (void *)&session);

		Dz1Thread_printf("Dz1InetFtp_transfer() : Try to "); Dz1SockAddr_dump(msg->peer, 0);

		memset(&local, 0, sizeof(Dz1SockAddr));
		if ((session->peer = Dz1SockAddr_clone(msg->peer, errp)) == NULL) ERR_OUT(errp);
		else if ((session->local = Dz1SockAddr_clone(&local, errp)) == NULL) ERR_OUT(errp);
		else if ((session->dtpSpec = Dz1InetFtpDTPSpec_new(NULL, Dz1InetFtpDTPStruct_file, Dz1InetFtpDTPMode_stream, errp)) == NULL) ERR_OUT(errp);
		else if ((session->dtpSpec->type = Dz1InetFtpDTPType_new(Dz1InetFtpDTPTypePresent_image, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((session->jobs = Dz1InetFtpTransferJobs_new(errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1InetFtpTransferJobs_build(session, msg->files)).code) ERR_OUT(errp);
		else if ((session->fsm = Dz1InetFtpFsm_new(session, errp)) == NULL) ERR_OUT(errp);
		else if ((session->sock = Dz1TcpClientSocket_open(session->peer, session->local, &to, errp)) == NULL) ERR_OUT(errp);
		else if ((session->rcvr = Dz1InetFtpReceiver_start(env->tSelf, session->peer, session->local, session->sock, errp)) == -1) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1InetFtpReceiver_startCancel, (void *)&session->rcvr);
			if ((*errp = env->sessionList->add(env->sessionList, session)).code) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
				session->sg = (*sg); *sg = NULL;
				session = NULL;
			}
			pthread_cleanup_pop(errp->code); // (Dz1Task_startCancel, (void *)&session->rcvr);
		}
		pthread_cleanup_pop(1); // (Dz1InetFtpSession_delAndSetNull, (void *)&session);
	}
	pthread_cleanup_pop(errp->code); // (Dz1InetFtp_transferFail, (void *)msg);
	return ret;
}

Dz1Error Dz1InetFtpCall_transfer(void *tFTP, Dz1SockAddr *peer, str_t user, str_t pass, str_t account, bool_t isPassive,
								 Dz1InetFtpTransferList *files, Dz1InetFtpFileDoneInform cb, void *cbParam,
								 Dz1InetFtpTransferList **ret)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (files->count(files) == 0) ERR_SET_OUT(&err, EINVAL);
	else if ((err = Dz1InetFtpTransferList_validate(files)).code) ERR_OUT(&err);
	else
	{
		Dz1InetFtpMsgTransfer *msg = Dz1InetFtpMsgTransfer_new(NULL, user, pass, account, isPassive, NULL, cb, cbParam, &err);
		if (msg == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Dz1InetFtpMsgTransfer_delAndSetNull, (void *)&msg);

			if ((msg->peer = Dz1SockAddr_clone(peer, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->files = Dz1InetFtpTransferList_clone(files, &err)) == NULL) ERR_OUT(&err);
			else if ((err = Dz1Task_call(tFTP, DZ1_TASK_QUEUE_NONE, DZ1_INET_FTP_TRANSFER, (void *)msg,
											(Dz1DumpFunc)Dz1InetFtpMsgTransfer_dump, NULL, NULL)).code) ERR_OUT(&err);
			else { (*ret) = msg->files; msg->files = NULL; }

			pthread_cleanup_pop(1); // (Dz1InetFtpMsgTransfer_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}

static void _Dz1InetFrpPost_transfer(void *param, void **sg, bool_t isAbnormal)
{
	Dz1InetFtpMsgTransferArg *arg = (Dz1InetFtpMsgTransferArg *)param;
	pthread_cleanup_push((Dz1DelFunc)Dz1InetFtpMsgTransferArg_del, (void *)arg);
	if (arg->cb)
	{
		Dz1InetFtpMsgTransfer *msg = (Dz1InetFtpMsgTransfer *)Dz1TaskSigMsg_getData(*sg);
		//Dz1Error *status = Dz1TaskSigMsg_getErrPtr(*sg);
		/*
		if (isAbnormal)
		{
			ERR_SET_OUT(status, EINTR);
			//if (msg->result != NULL) Dz1InetFtpTransferResult_del(msg->result);
			//msg->result = NULL;
		}
		*/
		arg->cb(arg->cbParam, msg->peer, &msg->files);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1InetFtpMsgTransferArg_del, (void *)arg);
}

Dz1Error Dz1InetFtpPost_transfer(void *tFTP, Dz1SockAddr *peer, str_t user, str_t pass, str_t account, bool_t isPassive,
								 Dz1InetFtpTransferList *files, Dz1InetFtpFileDoneInform cb, void *cbParam,
								 Dz1InetFtpMsgTransferDoneInform doneInform, void *doneInformParam)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (files->count(files) == 0) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Dz1InetFtpMsgTransfer *msg = Dz1InetFtpMsgTransfer_new(NULL, user, pass, account, isPassive, NULL, cb, cbParam, &err);
		if (msg == NULL) ERR_OUT(&err);
		else
		{
			Dz1InetFtpMsgTransferArg *arg = NULL;
			pthread_cleanup_push(Dz1InetFtpMsgTransfer_delAndSetNull, (void *)&msg);

			if ((msg->peer = Dz1SockAddr_clone(peer, &err)) == NULL) ERR_OUT(&err);
			else if ((msg->files = Dz1InetFtpTransferList_clone(files, &err)) == NULL) ERR_OUT(&err);
			else if ((arg = Dz1InetFtpMsgTransferArg_new(doneInform, doneInformParam, &err)) == NULL) ERR_OUT(&err);
			else
			{
				pthread_cleanup_push(Dz1InetFtpMsgTransferArg_delAndSetNull, (void *)&arg);
				if ((err = Dz1Task_post(tFTP, DZ1_TASK_QUEUE_NONE, DZ1_INET_FTP_TRANSFER, (void **)&msg,
										(Dz1DelFunc)Dz1InetFtpMsgTransfer_del,
										(Dz1DumpFunc)Dz1InetFtpMsgTransfer_dump, NULL,
										_Dz1InetFrpPost_transfer, (void *)arg)).code) ERR_OUT(&err);
				else { arg = NULL; }
				pthread_cleanup_pop(1); // (Dz1InetFtpMsgTransferArg_delAndSetNull, (void *)&arg);
			}

			pthread_cleanup_pop(1); // (Dz1InetFtpMsgTransfer_delAndSetNull, (void *)&msg);
		}
	}
	return err;
}


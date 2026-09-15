#include <dz1_task.h>
#include <dz1_inet_ftp.h>

#include "dz1_inet_ftp_env_util.h"
#include "dz1_inet_ftp_arg.h"
#include "dz1_inet_ftp_msg.h"
#include "dz1_inet_ftp_timer.h"
#include "dz1_inet_ftp_transfer.h"
#include "dz1_inet_ftp_message.h"
#include "dz1_inet_ftp_fsm.h"

//static Dz1TaskProcStatus func(void *user_arg, void *user_resource, void *timer, void **sig_msg, Dz1Error *errp);

//static Dz1TaskProcStatus timeout(void *user_arg, void *user_resource, void *timer, void **timer_data, Dz1Error *errp);

static Dz1Error Dz1InetFtp_init(void **user_resource, void *tSelf, str_t name, u32_t my_queue_id, void *user_arg, void *timer)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpEnv *env = NULL;

	if ((env = (*user_resource) = Dz1InetFtpEnv_new(tSelf, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static void Dz1InetFtp_exception(void *user_arg, void *user_resource, void *timer, Dz1Error *reason)
{
	Dz1InetFtpArg *arg = (Dz1InetFtpArg *)user_arg;
	if (arg->func) arg->func(arg->ptr, reason);
}

static void Dz1InetFtp_cleanup(void *ptr)
{
	Dz1InetFtpEnv *env = (Dz1InetFtpEnv *)ptr;
	Dz1InetFtpEnv_cleanup(env);
}

void *Dz1InetFtp_new(str_t localCharSetName, Dz1InetFtpException exceptionFunc, void *exceptionArg, Dz1Error *err)
{
	void *ret = NULL;
	Dz1Error _err, *errp = err ? err : &_err;
	Dz1InetFtpArg *arg = Dz1InetFtpArg_new(localCharSetName, exceptionFunc, exceptionArg, errp);
	if (arg == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1InetFtpArg_delAndSetNull, (void *)&arg);
		if ((ret = Dz1Task_new("Dz1InetFtp", 64, (void **)&arg, (Dz1DelFunc)Dz1InetFtpArg_del,
							   (Dz1CmpFunc)Dz1InetFtpTimer_cmp,
							   Dz1InetFtp_init, Dz1InetFtp_exception, Dz1InetFtp_cleanup, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Task_delAndSetNull, (void *)&ret);

			if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_INET_FTP_TRANSFER), Dz1InetFtp_transfer)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_INET_FTP_RCVE_REPLY), Dz1InetFtpFsm_replyMsgProc)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_INET_FTP_DTP_TRANSFER_DONE), Dz1InetFtp_trasferDone)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_INET_FTP_DTP_TRANSFER_FAIL), Dz1InetFtp_trasferFail)).code) ERR_OUT(errp);
			//else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_INET_FTP_DTP_TRANSFER_TIMEOUT), Dz1InetFtp_trasferTimeout)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_INET_FTP_DTP_TRANSFER_PKT), Dz1InetFtp_extendTimeout)).code) ERR_OUT(errp);
			else if ((*errp = Dz1Task_regMsg(ret, DZ1_TASK_MSG_EXACT(DZ1_INET_FTP_RCVE_EXCEPTION), Dz1InetFtp_disconnected)).code) ERR_OUT(errp);

			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(errp->code); // (Dz1Task_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (Dz1InetFtpArg_delAndSetNull, (void *)&arg);
	}
	return ret;
}


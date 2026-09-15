#include "dz1_inet_ftp_env_util.h"
#include "dz1_inet_ftp_timer_util.h"

Dz1Error Dz1InetFtpTimer_reg(void *timer, Dz1SockAddr *peer, Dz1SockAddr *local, u32_t timerID, u64_t duration_us, Dz1TaskTimeoutProcFunc timeout)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpTimer *tmr = Dz1InetFtpTimer_new(NULL, NULL, timerID, &err);
	if (tmr == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1InetFtpTimer_delAndSetNull, (void *)&tmr);

		if ((tmr->peer = Dz1SockAddr_clone(peer, &err)) == NULL) ERR_OUT(&err);
		else if ((tmr->local = Dz1SockAddr_clone(local, &err)) == NULL) ERR_OUT(&err);
		else if ((err = Dz1TaskTimer_reg(timer, duration_us, (void **)&tmr,
										(Dz1DelFunc)Dz1InetFtpTimer_del,
										timeout, TRUE)).code) ERR_OUT(&err);

		pthread_cleanup_pop(1); // (Dz1InetFtpTimer_delAndSetNull, (void *)&tmr);
	}
	return err;
}

void Dz1InetFtpTimer_dereg(void *timer, Dz1InetFtpSession *session, u32_t timerID)
{
	Dz1InetFtpTimer tmr = { session->peer, session->local, timerID };
	Dz1TaskTimer_dereg(timer, &tmr);
}

static Dz1TaskProcStatus Dz1InetFtpTimer_pktWaitTimeout(void *uArg, void *uRsc, void *timer, void **timer_data, Dz1Error *errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	Dz1InetFtpEnv *env = (Dz1InetFtpEnv *)uRsc;
	Dz1InetFtpSessionList *list = env->sessionList;

	Dz1InetFtpTimer *tmr = (Dz1InetFtpTimer *)(*timer_data);

	Dz1InetFtpSession key = { tmr->peer, tmr->local }, *session = NULL;

	Dz1Thread_printf("Dz1InetFtpTimer_pktWaitTimeout() : in\n");
	if ((session = list->extract(list, &key)) != NULL)
	{
		Dz1InetFtpSessionCleanupRuntimeArg cleanupArg = { session, timer };
		pthread_cleanup_push(Dz1InetFtpSession_cleanupRunTime, (void *)&cleanupArg);

		session->curStatus = Dz1InetFtpCmdResult_serverBusy;
		Dz1Thread_printf("FTP Session Terminate: Packet Wait Timeout = ");
		Dz1InetFtpSession_dump(session, 0);

		pthread_cleanup_pop(1); // (Dz1InetFtpSession_cleanupRunTime, (void *)cleanupArg);
	}
	Dz1Thread_printf("Dz1InetFtpTimer_pktWaitTimeout() : out\n");

	return ret;
}

Dz1Error Dz1InetFtpTimer_resetMsgWait(void *timer, Dz1SockAddr *peer, Dz1SockAddr *local)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = Dz1InetFtpTimer_reg(timer, peer, local, DZ1_INET_FTP_PKT_WAIT,
								  (u64_t)60 * 5 * 1000000, Dz1InetFtpTimer_pktWaitTimeout)).code) ERR_OUT(&err);
	return err;
}

void Dz1InetFtpTimer_clearMsgWait(void *timer, Dz1SockAddr *peer, Dz1SockAddr *local)
{
	Dz1InetFtpTimer tmr = { peer, local, DZ1_INET_FTP_PKT_WAIT };
	Dz1TaskTimer_dereg(timer, &tmr);
}


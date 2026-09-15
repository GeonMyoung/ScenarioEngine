#include <dz1_str.h>
#include <dz1_socket_receiver.h>
#include "dz1_inet_ftp_env_util.h"
#include "dz1_inet_ftp_receiver.h"
#include "dz1_inet_ftp_dtp.h"
#include "dz1_inet_ftp_timer_util.h"

static Dz1Error _Dz1InetFtpEnv_sessionListCleanup(void *ptr, Dz1InetFtpSession *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (p->rcvr != -1) Dz1TcpSocketReceiver_stop(p->rcvr);
	if (p->dtp != -1) Dz1TcpSocketReceiver_stop(p->dtp);
	if (p->sg != NULL)
	{
		Dz1TaskSigMsg_termInterruptedAndDel(p->sg);
		p->sg = NULL;
	}
	return err;
}

void Dz1InetFtpEnv_cleanup(Dz1InetFtpEnv *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (p == NULL) return;
	if ((err = p->sessionList->travel(p->sessionList, _Dz1InetFtpEnv_sessionListCleanup, NULL)).code) ERR_OUT(&err);
	Dz1InetFtpEnv_del(p);
}

void Dz1InetFtpSession_cleanupRunTime(void *ptr)
{
	Dz1InetFtpSessionCleanupRuntimeArg *arg = (Dz1InetFtpSessionCleanupRuntimeArg *)ptr;

	Dz1InetFtpSession *session = arg->session;

	if (session->dtp != (u32_t)-1) Dz1InetFtpDTP_stop(session->dtp);
	session->dtp = -1;

	if (session->rcvr != (u32_t)-1) Dz1InetFtpReceiver_stop(session->rcvr);
	session->rcvr = -1;

	if (session->fileDone != NULL)
	{
		Dz1InetFtpTransfer *target = NULL;
		for (;session->curJob != NULL; session->curJob = session->curJob->next)
		{
			target = session->curJob->target;
			target->result = session->curStatus;
			session->fileDone(session->fileDoneParam, session->peer, target);
		}
	}
	if (session->sg != NULL) Dz1TaskSigMsg_termDelAndSetNull(&session->sg);
	Dz1InetFtpTimer_dereg(arg->timer, session, DZ1_INET_FTP_PKT_WAIT);
	Dz1InetFtpSession_del(session);
}

static void Dz1InetFtpPathList_append(Dz1InetFtpPathList *list, Dz1InetFtpPathNode *node)
{
	if (list->head == NULL) list->head = list->tail = node;
	else
	{
		list->tail->next = node;
		list->tail = node;
	}
}

static Dz1Error Dz1InetFtpPathList_build(Dz1InetFtpPathList *dst, str_t src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	str_t temp = Dz1Str_dup(src, &err);
	if (temp == NULL) ERR_OUT(&err);
	else
	{
		Dz1InetFtpPathNode *node = NULL;
		char *cp = temp, *start = NULL;
		pthread_cleanup_push((Dz1DelFunc)Dz1Str_del, (void *)temp);

		if (*cp == DIR_SEP || *cp == '/') cp++;

		while(err.code == 0 && *cp != '\0')
		{
			while(*cp == DIR_SEP) cp++;	// skip front separator

			start = cp;									// set start pointer
			while(*cp != DIR_SEP  && *cp != '/' && *cp != '\0') cp++;	// find end of word

			if (*cp == DIR_SEP || *cp == '/') *cp++ = '\0';			// make ASCIIZ string to middle word

			// create node and link it
			if ((node = Dz1InetFtpPathNode_new(start, &err)) == NULL) ERR_OUT(&err);
			else Dz1InetFtpPathList_append(dst, node);
		}

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Str_del, (void *)temp);
	}
	return err;
}

static void Dz1InetFtpTransferJobs_append(Dz1InetFtpTransferJobs *list, Dz1InetFtpTransferNode *node)
{
	if (list->head == NULL) list->head = list->tail = node;
	else
	{
		list->tail->next = node;
		list->tail = node;
	}
}

static Dz1Error _Dz1InetFtpTransferJobs_build(void *ptr, Dz1InetFtpTransfer *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpTransferJobs *dst = (Dz1InetFtpTransferJobs *)ptr;
	Dz1InetFtpTransferNode *node = Dz1InetFtpTransferNode_new(p, &err);
	if (node == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1InetFtpTransferNode_delAndSetNull, (void *)&node);
		if (p->direction == Dz1InetFtpDirection_upload)
		{
			Dz1InetFtpPathInfo *pathInfo = NULL;
			Dz1InetFtpPathList *pathList = NULL;
			if ((pathInfo = node->pathInfo = Dz1InetFtpPathInfo_new(&err)) == NULL) ERR_OUT(&err);
			else if ((pathList = pathInfo->list = Dz1InetFtpPathList_new(&err)) == NULL) ERR_OUT(&err);
			else if (p->remote->path != NULL && (err = Dz1InetFtpPathList_build(pathList, p->remote->path)).code) ERR_OUT(&err);
			else
			{
				pathInfo->current = pathInfo->list->head;
				Dz1InetFtpTransferJobs_append(dst, node);
				node = NULL;
			}
		}
		else
		{
			Dz1InetFtpTransferJobs_append(dst, node);
			node = NULL;
		}
		pthread_cleanup_pop(1); // (Dz1InetFtpTransferNode_delAndSetNull, (void *)&node);
	}
	return err;
}

Dz1Error Dz1InetFtpTransferJobs_build(Dz1InetFtpSession *dst, Dz1InetFtpTransferList *files)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = files->travel(files, _Dz1InetFtpTransferJobs_build, (void *)dst->jobs)).code) ERR_OUT(&err);
	else
	{
		dst->curJob = dst->jobs->head;
		//Dz1Thread_printf("Dz1InetFtpTransferJobs_build() : Jobs =");
		//Dz1InetFtpTransferJobs_dump(dst, 0);
	}
	return err;
}


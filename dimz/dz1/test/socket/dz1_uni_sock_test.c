// dz1_uni_sock_test.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//
#ifndef UNIX_SYSTEM
#include "stdafx.h"
#endif

#include <dz1_cleanup.h>
#include <dz1_str.h>
#include <dz1_socket_acceptor.h>
#include <dz1_socket_receiver.h>
#include <dz1_shell.h>
#include <dz1_usleep.h>
//#include <dz1_malloc.h>

typedef struct SessionEntry
{
	Dz1SockAddr			*peer;
	Dz1SockAddr			*local;
	Dz1UniClientSocket	*sock;
	u32_t				 rcvr;
} SessionEntry;	

static Dz1Error _session_init(void **ret, void *uArg, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1UniClientSocket *s)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	return err;
}

static Dz1SocketReceierBehavior _session_fwd(void *uArg, void *uRsc, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1UniClientSocket *s, u8_t *data, size_t size, Dz1Error *status)
{
	Dz1SocketReceierBehavior ret = Dz1SocketReceierBehavior_continue;
	if (status->code == 0)
	{
		s->send(s, data, size, 0, NULL, NULL);
	}
	return ret;
}

static void _session_err(void *uArg, void *uRsc, Dz1SockAddr *peer, Dz1SockAddr *local, Dz1UniClientSocket *s, Dz1Error *reason)
{
	Dz1Thread_printf(Dz1Text("Session Entry get error\n"));
	ERR_OUT(reason);
}

////////////////////////////////////////////////////////////////////////////////
// SessionEntry API
static void SessionEntry_del(SessionEntry *p)
{
	if (!p) return;
	// Additional delete code here
	Dz1SockAddr_delAndSetNull(&p->peer);
	Dz1SockAddr_delAndSetNull(&p->local);
	Dz1UniClientSocket_delAndSetNull(&p->sock);
	if (p->rcvr != -1)
	{
		Dz1UniSocketReceiver_stop(p->rcvr);
		p->rcvr = -1;
	}
	Dz1Free(p);
}

static void SessionEntry_delAndSetNull(void *pptr)
{
	SessionEntry **p = (SessionEntry **)pptr;
	SessionEntry_del(*p); 
	*p = NULL;
}

static SessionEntry *SessionEntry_new(Dz1SockAddr *peer, Dz1SockAddr *local, Dz1UniClientSocket **_sock, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SessionEntry *ret = NULL;
	
	if (peer == NULL || local == NULL || _sock == NULL || *_sock == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (SessionEntry *)Dz1Calloc(sizeof(SessionEntry), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(SessionEntry_delAndSetNull, (void *)&ret);

		if (0) { }
		// additional initialize code here
		else if ((ret->peer = Dz1SockAddr_clone(peer, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->local = Dz1SockAddr_clone(local, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->rcvr = Dz1UniSocketReceiver_start(_sock, FALSE, peer, local, 4096, 0, _session_init, _session_fwd, _session_err, NULL, NULL, NULL, NULL, errp)) == -1) ERR_OUT(errp);
		else
		{
			ret->sock = *_sock;
			*_sock = NULL;
			ERR_CLEAR(errp);
		}

		pthread_cleanup_pop(errp->code); // (SessionEntry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static void SessionEntry_dump(SessionEntry *p, int tab)
{
	if (p == 0) Dz1Thread_printf(Dz1Text("NULL\n"));
	else
	{
		TCHAR strP[53], strL[53];
		if (Dz1SockAddr_printable(p->local, strL, FALSE, NULL) == NULL) Dz1STRCPY(strL, Dz1Text("#err"));
		if (Dz1SockAddr_printable(p->peer, strP, FALSE, NULL) == NULL) Dz1STRCPY(strP, Dz1Text("#err"));
		Dz1Thread_printf(Dz1Text("%s-%s, %p, %u\n"), strP, strL, p->sock, p->rcvr);
	}
}

static int SessionEntry_cmp(SessionEntry *a, SessionEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else if ((ret = Dz1SockAddr_cmp(a->peer, b->peer)) != 0) return ret;
	else return Dz1SockAddr_cmp(a->local, b->local);
}
// SessionEntry API
////////////////////////////////////////////////////////////////////////////////


static Dz1AATree *SessionList_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1AATree *ret = Dz1AATree_new(SessionEntry_cmp, SessionEntry_del, SessionEntry_dump, errp);
	if (ret == NULL) ERR_OUT(errp);
	return ret;
}

static void SessionList_del(Dz1AATree *p)
{
	Dz1AATree_del(p);
}

static Dz1Error _acceptor_init(void **ret, void *userParam, Dz1SockAddr *local, Dz1UniServerSocket *s)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (( (*ret) = SessionList_new(errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}

static Dz1TcpSocketAcceptorBehavior _acceptor_fwd(void *uArg, void *uRsc, Dz1UniClientSocket **s, Dz1SockAddr *local, Dz1SockAddr *peer, Dz1Error *status)
{
	Dz1TcpSocketAcceptorBehavior ret = Dz1TcpSocketAcceptorBehavior_continue;
	Dz1AATree *list = (Dz1AATree *)uRsc;
	if (status->code == 0)
	{
		DZ1_ERROR_SAFE_VAR(errp, err);
		SessionEntry *node = SessionEntry_new(peer, local, s, errp);
		if (node == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(SessionEntry_delAndSetNull, (void *)&node);
			if ((*errp = Dz1AATree_insert(list, node)).code) ERR_OUT(errp);
			else
			{
				node = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (SessionEntry_delAndSetNull, (void *)&node);
		}
	}
	return ret;
}

static void _acceptor_err(void *uArg, void *uRsc, Dz1UniServerSocket *s, Dz1Error *reason)
{
	Dz1Thread_printf("_acceptor_err() : Got Exception\n");
	ERR_OUT(reason);
}

static void _acceptor_cleanup(void *uRsc)
{
	Dz1AATree_del((Dz1AATree *)uRsc);
}

static FILE *logFP = NULL;
static void _memoryExport(void *ptr)
{
	if (logFP != NULL)
	{
		Dz1Mem_export(logFP, TRUE);
		fflush(logFP);
	}
}

static void _outputHook(void *ptr, unsigned char *data, size_t size)
{
	if (logFP != NULL)
	{
		fwrite(data, size, 1, logFP);
		fflush(logFP);
	}
}

typedef struct ProcessEnv
{
	u32_t					 acceptor;
} ProcessEnv;

static void ProcessEnv_cleanup(void *ptr)
{
	ProcessEnv *p = (ProcessEnv *)ptr;
	if (p->acceptor != -1)
	{
		Dz1UniSocketAcceptor_stop(p->acceptor);
		p->acceptor = -1;
	}
}

static bool_t _main_thread_prepare(ProcessEnv *env, Dz1Error *errp)
{
	Dz1SockAddr local;
	Dz1UniServerSocket *sock = NULL;
	struct timeval to = { 10, 0 };

	if ((*errp = Dz1SockAddr_setAddrStr(&local, Dz1Text("0.0.0.0") )).code) ERR_OUT(errp);
	else if ((*errp = Dz1SockAddr_setPort(&local, 39978)).code) ERR_OUT(errp);
	else if ((sock = Dz1UniServerSocket_open(&local, NULL, Dz1UniSocketType_dgram, 5, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1UniServerSocket_closeAndSetNull, (void *)&sock);

		Dz1Thread_printf("LOCAL = "); Dz1SockAddr_dump(&local, 1);
		if ((env->acceptor = Dz1UniSocketAcceptor_start(&sock, TRUE, &local, 0, 0, _acceptor_init, _acceptor_fwd, _acceptor_err, NULL, _acceptor_cleanup, NULL, NULL, errp)) == -1) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1UniSocketAcceptor_startCancel, (void *)&sock);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void _start_shell(ProcessEnv *env, Dz1Error *errp)
{
	void *sh = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

#ifdef WIN32
	if ((sh = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 16, "root", "TcpEchoServer", &err)) == NULL) Dz1Error_print(&err, 0);
#else
	if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 16, "root", "TcpProxy", &err)) == NULL) ERR_OUT(&err);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);
		if (0) { }
//		else if ((err = Dz1Shell_cmdReg(sh, "port", _cmd_port, task, "TCP Server port management")).code) ERR_OUT(&err);
		else
		{
			Dz1Shell_start(sh, NULL);
		}

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Shell_del, (void *)sh);
	}
}

static void _process_prepare(void *ptr, bool_t is_daemon, Dz1Error *errp)
{
	Dz1Cleanup_init();
	if ((logFP = Dz1FileStream_open(Dz1Text("dz1_uni_sock.log.txt"), Dz1Text("wb"), errp)) == NULL) ERR_OUT(errp);
	else
	{
		ProcessEnv env = { -1 };
		Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
		Dz1OutputHook_set(_outputHook, NULL);

		if (Dz1Socket_init() == FALSE) ERR_SET_OUT(errp, EFAULT);
		else
		{
			pthread_cleanup_push(Dz1Socket_initCancel, NULL);
			if (_main_thread_prepare(&env, errp) == FALSE) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(ProcessEnv_cleanup, (void *)&env);
				if (is_daemon)
				{
					while(1) Dz1Thread_usleep(1000000);
				}
				else _start_shell(&env, errp);
				pthread_cleanup_pop(1); // (ProcessEnv_cleanup, (void *)&env);
			}
			pthread_cleanup_pop(1); // (Dz1Socket_initCancel, NULL);
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{	// argument process, fork ot shell
	DZ1_ERROR_SAFE_VAR(errp, err);

	_process_prepare(NULL, FALSE, errp);

	return errp->code;
}


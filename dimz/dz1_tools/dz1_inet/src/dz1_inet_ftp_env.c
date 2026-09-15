////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_inet_ftp_env.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpDTPSpec
Dz1InetFtpDTPSpec *Dz1InetFtpDTPSpec_new(Dz1InetFtpDTPType *type, 
										 Dz1InetFtpDTPStruct stru, 
										 Dz1InetFtpDTPMode mode, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpDTPSpec *__internal_ret = (Dz1InetFtpDTPSpec *)Dz1Calloc(sizeof(Dz1InetFtpDTPSpec), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpDTPSpec_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->type = type;
		__internal_ret->stru = stru;
		__internal_ret->mode = mode;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpDTPSpec_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1InetFtpDTPSpec_purge(Dz1InetFtpDTPSpec *p)
{
	if (p == NULL) return;
	Dz1InetFtpDTPType_del(p->type);
}

void Dz1InetFtpDTPSpec_del(Dz1InetFtpDTPSpec *p)
{
	if (p == NULL) return;
	Dz1InetFtpDTPSpec_purge(p);
	Dz1Free(p);
}

void Dz1InetFtpDTPSpec_dump(Dz1InetFtpDTPSpec *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("type.")); Dz1InetFtpDTPType_dump(p->type, tab); 
		Dz1Thread_tprintf(tab, Dz1T("stru = %s(%d)\n"), Dz1InetFtpDTPStructStr(p->stru), p->stru);
		Dz1Thread_tprintf(tab, Dz1T("mode = %s(%d)\n"), Dz1InetFtpDTPModeStr(p->mode), p->mode);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1InetFtpDTPSpec
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpPathNode
Dz1InetFtpPathNode *Dz1InetFtpPathNode_new(str_t path, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpPathNode *__internal_ret = (Dz1InetFtpPathNode *)Dz1Calloc(sizeof(Dz1InetFtpPathNode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpPathNode_delAndSetNull, (void *)&__internal_ret);
		
		if (path && (__internal_ret->path = dz1_built_in_str_clone(path, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpPathNode_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1InetFtpPathNode_purge(Dz1InetFtpPathNode *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->path);
}

void Dz1InetFtpPathNode_del(Dz1InetFtpPathNode *p)
{
	if (p == NULL) return;
	Dz1InetFtpPathNode_purge(p);
	Dz1Free(p);
}

void Dz1InetFtpPathNode_dump(Dz1InetFtpPathNode *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("path = ")); dz1_built_in_str_dump(p->path, tab); 
	}
}
// Dz1InetFtpPathNode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpPathList
Dz1InetFtpPathList *Dz1InetFtpPathList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpPathList *__internal_ret = (Dz1InetFtpPathList *)Dz1Calloc(sizeof(Dz1InetFtpPathList), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpPathList_delAndSetNull, (void *)&__internal_ret);
		
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpPathList_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1InetFtpPathList_purge(Dz1InetFtpPathList *p)
{
	if (p == NULL) return;
	Dz1InetFtpPathNode_del(p->head);
}

void Dz1InetFtpPathList_del(Dz1InetFtpPathList *p)
{
	if (p == NULL) return;
	Dz1InetFtpPathList_purge(p);
	Dz1Free(p);
}

void Dz1InetFtpPathList_dump(Dz1InetFtpPathList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		// Normal member
		Dz1Thread_printf(Dz1T("head = ")); Dz1InetFtpPathNode_dump(p->head, tab); 
	}
}
// Dz1InetFtpPathList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpPathInfo
Dz1InetFtpPathInfo *Dz1InetFtpPathInfo_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpPathInfo *__internal_ret = (Dz1InetFtpPathInfo *)Dz1Calloc(sizeof(Dz1InetFtpPathInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpPathInfo_delAndSetNull, (void *)&__internal_ret);
		
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpPathInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1InetFtpPathInfo_purge(Dz1InetFtpPathInfo *p)
{
	if (p == NULL) return;
	Dz1InetFtpPathList_del(p->list);
}

void Dz1InetFtpPathInfo_del(Dz1InetFtpPathInfo *p)
{
	if (p == NULL) return;
	Dz1InetFtpPathInfo_purge(p);
	Dz1Free(p);
}

void Dz1InetFtpPathInfo_dump(Dz1InetFtpPathInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("list = ")); Dz1InetFtpPathList_dump(p->list, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("current = ")); Dz1InetFtpPathNode_dump(p->current, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1InetFtpPathInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpTransferNode
Dz1InetFtpTransferNode *Dz1InetFtpTransferNode_new(Dz1InetFtpTransfer *target/*_ref*/, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpTransferNode *__internal_ret = (Dz1InetFtpTransferNode *)Dz1Calloc(sizeof(Dz1InetFtpTransferNode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpTransferNode_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->target = target;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpTransferNode_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1InetFtpTransferNode_purge(Dz1InetFtpTransferNode *p)
{
	if (p == NULL) return;
	Dz1InetFtpPathInfo_del(p->pathInfo);
}

void Dz1InetFtpTransferNode_del(Dz1InetFtpTransferNode *p)
{
	if (p == NULL) return;
	Dz1InetFtpTransferNode_purge(p);
	Dz1Free(p);
}

void Dz1InetFtpTransferNode_dump(Dz1InetFtpTransferNode *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("target = ")); Dz1InetFtpTransfer_dump(p->target, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("pathInfo = ")); Dz1InetFtpPathInfo_dump(p->pathInfo, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1InetFtpTransferNode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpTransferJobs
Dz1InetFtpTransferJobs *Dz1InetFtpTransferJobs_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpTransferJobs *__internal_ret = (Dz1InetFtpTransferJobs *)Dz1Calloc(sizeof(Dz1InetFtpTransferJobs), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpTransferJobs_delAndSetNull, (void *)&__internal_ret);
		
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpTransferJobs_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1InetFtpTransferJobs_purge(Dz1InetFtpTransferJobs *p)
{
	if (p == NULL) return;
	Dz1InetFtpTransferNode_del(p->head);
}

void Dz1InetFtpTransferJobs_del(Dz1InetFtpTransferJobs *p)
{
	if (p == NULL) return;
	Dz1InetFtpTransferJobs_purge(p);
	Dz1Free(p);
}

void Dz1InetFtpTransferJobs_dump(Dz1InetFtpTransferJobs *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		// Normal member
		Dz1Thread_printf(Dz1T("head = ")); Dz1InetFtpTransferNode_dump(p->head, tab); 
	}
}
// Dz1InetFtpTransferJobs
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpSession
Dz1InetFtpSession *Dz1InetFtpSession_new(Dz1SockAddr *peer, 
										 Dz1SockAddr *local, 
										 Dz1TcpClientSocket *sock, 
										 u32_t rcvr, 
										 str_t user, 
										 str_t password, 
										 str_t account, 
										 bool_t isPassive, 
										 str_t remoteCharSetName, 
										 Dz1InetFtpDTPSpec *dtpSpec, 
										 u32_t dtp, 
										 Dz1InetFtpFileDoneInform fileDone, 
										 void *fileDoneParam, 
										 void *sg, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpSession *__internal_ret = (Dz1InetFtpSession *)Dz1Calloc(sizeof(Dz1InetFtpSession), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpSession_delAndSetNull, (void *)&__internal_ret);
		
		if (user && (__internal_ret->user = dz1_built_in_str_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if (password && (__internal_ret->password = dz1_built_in_str_clone(password, errp)) == NULL) ERR_OUT(errp);
		else if (account && (__internal_ret->account = dz1_built_in_str_clone(account, errp)) == NULL) ERR_OUT(errp);
		else if (remoteCharSetName && (__internal_ret->remoteCharSetName = dz1_built_in_str_clone(remoteCharSetName, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->peer = peer;
			__internal_ret->local = local;
			__internal_ret->sock = sock;
			__internal_ret->rcvr = rcvr;
			__internal_ret->isPassive = isPassive;
			__internal_ret->dtpSpec = dtpSpec;
			__internal_ret->dtp = dtp;
			__internal_ret->fileDone = fileDone;
			__internal_ret->fileDoneParam = fileDoneParam;
			__internal_ret->sg = sg;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpSession_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1InetFtpSession_purge(Dz1InetFtpSession *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1SockAddr_del(p->local);
	Dz1TcpClientSocket_del(p->sock);
	dz1_built_in_str_del(p->user);
	dz1_built_in_str_del(p->password);
	dz1_built_in_str_del(p->account);
	dz1_built_in_str_del(p->remoteCharSetName);
	Dz1TcpServerSocket_del(p->portSock);
	Dz1TcpClientSocket_del(p->dataSock);
	Dz1InetFtpTransferJobs_del(p->jobs);
	Dz1Fsm2_del(p->fsm);
	Dz1InetFtpDTPSpec_del(p->dtpSpec);
}

void Dz1InetFtpSession_del(Dz1InetFtpSession *p)
{
	if (p == NULL) return;
	Dz1InetFtpSession_purge(p);
	Dz1Free(p);
}

void Dz1InetFtpSession_dump(Dz1InetFtpSession *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peer = ")); Dz1SockAddr_dump(p->peer, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("local = ")); Dz1SockAddr_dump(p->local, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1Thread_tprintf(tab, Dz1T("sock = %p\n"), p->sock);
		Dz1Thread_tprintf(tab, Dz1T("rcvr = ")); Dz1u32_dump(&p->rcvr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("user = ")); dz1_built_in_str_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("password = ")); dz1_built_in_str_dump(p->password, tab); 
		Dz1Thread_tprintf(tab, Dz1T("account = ")); dz1_built_in_str_dump(p->account, tab); 
		Dz1Thread_tprintf(tab, Dz1T("isPassive = ")); Dz1Bool_dump(&p->isPassive, tab); 
		Dz1Thread_tprintf(tab, Dz1T("remoteCharSetName = ")); dz1_built_in_str_dump(p->remoteCharSetName, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1Thread_tprintf(tab, Dz1T("portSock = %p\n"), p->portSock);
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1Thread_tprintf(tab, Dz1T("dataSock = %p\n"), p->dataSock);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("jobs = ")); Dz1InetFtpTransferJobs_dump(p->jobs, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("curJob = ")); Dz1InetFtpTransferNode_dump(p->curJob, tab); 
		Dz1Thread_tprintf(tab, Dz1T("curStatus = %s(%d)\n"), Dz1InetFtpCmdResultStr(p->curStatus), p->curStatus);
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1Thread_tprintf(tab, Dz1T("fsm = %p\n"), p->fsm);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("dtpSpec = ")); Dz1InetFtpDTPSpec_dump(p->dtpSpec, tab); 
		Dz1Thread_tprintf(tab, Dz1T("dtp = ")); Dz1u32_dump(&p->dtp, tab); 
		Dz1Thread_tprintf(tab, Dz1T("fileDone = %p\n"), p->fileDone);
		Dz1Thread_tprintf(tab, Dz1T("fileDoneParam = %p\n"), p->fileDoneParam);
		Dz1Thread_tprintf(tab, Dz1T("sg = %p\n"), p->sg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int Dz1InetFtpSession_cmp(Dz1InetFtpSession *a, Dz1InetFtpSession *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->peer == NULL && b->peer == NULL) ret = 0;
	else if (a->peer == NULL /*&& b->peer != NULL*/) ret = -1;
	else if (/*a->peer != NULL &&*/ b->peer == NULL) ret = 1;
	else if ((ret = Dz1SockAddr_cmp(a->peer, b->peer)) != 0) { }
	else if (a->local == NULL && b->local == NULL) ret = 0;
	else if (a->local == NULL /*&& b->local != NULL*/) ret = -1;
	else if (/*a->local != NULL &&*/ b->local == NULL) ret = 1;
	else if ((ret = Dz1SockAddr_cmp(a->local, b->local)) != 0) { }
	return ret;
}
// Dz1InetFtpSession
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpSessionList
static Dz1Error Dz1InetFtpSessionList_add(Dz1InetFtpSessionList *p, Dz1InetFtpSession *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static bool_t Dz1InetFtpSessionList_remove(Dz1InetFtpSessionList *p, Dz1InetFtpSession *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1InetFtpSession *Dz1InetFtpSessionList_extract(Dz1InetFtpSessionList *p, Dz1InetFtpSession *key)
{
	return (Dz1InetFtpSession *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1InetFtpSessionListMkArrArg
{
	Dz1InetFtpSession **arr;
	unsigned int idx;
} Dz1InetFtpSessionListMkArrArg;

static Dz1Error _Dz1InetFtpSessionList_get_array(void *ptr, Dz1InetFtpSession *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpSessionListMkArrArg *arg = (Dz1InetFtpSessionListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1InetFtpSession **Dz1InetFtpSessionList_get_array(Dz1InetFtpSessionList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1InetFtpSession **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1InetFtpSession **)Dz1Calloc(sizeof(Dz1InetFtpSession *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1InetFtpSessionListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1InetFtpSessionList_get_array, (void *)&arg);
		if (ERR_PROBE(errp)) ERR_OUT(errp);
		else
		{
			if (ret_cnt) (*ret_cnt) = cnt;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Memory_cancel, (void *)ret);
	}
	if (ERR_PROBE(errp)) ret = NULL;
	return ret;
}

static Dz1Error Dz1InetFtpSessionList_travelForward(Dz1InetFtpSessionList *p, Dz1Error (*func)(void *ptr, Dz1InetFtpSession *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1InetFtpSessionList_travelBackward(Dz1InetFtpSessionList *p, Dz1Error (*func)(void *ptr, Dz1InetFtpSession *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1InetFtpSession *Dz1InetFtpSessionList_find(Dz1InetFtpSessionList *p, Dz1InetFtpSession *key)
{
	return (Dz1InetFtpSession *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1InetFtpSessionList_count(Dz1InetFtpSessionList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1InetFtpSessionList *Dz1InetFtpSessionList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpSessionList *ret = (Dz1InetFtpSessionList *)Dz1Calloc(sizeof(Dz1InetFtpSessionList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1InetFtpSessionList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1InetFtpSession_cmp,
				(Dz1DelFunc)Dz1InetFtpSession_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1InetFtpSessionList_count;
			ret->travel = Dz1InetFtpSessionList_travelForward;
			ret->travelForward = Dz1InetFtpSessionList_travelForward;
			ret->travelBackward = Dz1InetFtpSessionList_travelBackward;
			ret->get_array = Dz1InetFtpSessionList_get_array;
			ret->add = Dz1InetFtpSessionList_add;
			ret->remove = Dz1InetFtpSessionList_remove;
			ret->find = Dz1InetFtpSessionList_find;
			ret->extract = Dz1InetFtpSessionList_extract;
			ret->cmp = Dz1InetFtpSession_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpSessionList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1InetFtpSessionList_purge(Dz1InetFtpSessionList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1InetFtpSessionList_del(Dz1InetFtpSessionList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1InetFtpSessionList_dump(void *ptr, Dz1InetFtpSession *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1InetFtpSession_dump(p, tab);
	return err;
}

void Dz1InetFtpSessionList_dump(Dz1InetFtpSessionList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1InetFtpSessionList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1InetFtpSessionList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpEnv
Dz1InetFtpEnv *Dz1InetFtpEnv_new(void *tSelf, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpEnv *__internal_ret = (Dz1InetFtpEnv *)Dz1Calloc(sizeof(Dz1InetFtpEnv), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpEnv_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->sessionList = Dz1InetFtpSessionList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->tSelf = tSelf;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpEnv_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1InetFtpEnv_purge(Dz1InetFtpEnv *p)
{
	if (p == NULL) return;
	Dz1InetFtpSessionList_del(p->sessionList);
}

void Dz1InetFtpEnv_del(Dz1InetFtpEnv *p)
{
	if (p == NULL) return;
	Dz1InetFtpEnv_purge(p);
	Dz1Free(p);
}

void Dz1InetFtpEnv_dump(Dz1InetFtpEnv *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("tSelf = %p\n"), p->tSelf);
		Dz1Thread_tprintf(tab, Dz1T("sessionList = ")); Dz1InetFtpSessionList_dump(p->sessionList, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1InetFtpEnv
////////////////////////////////////////////////////////////////////////////////


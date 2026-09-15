////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_inet_ftp_msgs.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpMsgTransfer
Dz1InetFtpMsgTransfer *Dz1InetFtpMsgTransfer_new(Dz1SockAddr *peer, 
												 str_t user, 
												 str_t pass, 
												 str_t account, 
												 bool_t isPassive, 
												 Dz1InetFtpTransferList *files, 
												 Dz1InetFtpFileDoneInform fileDone, 
												 void *fileDoneParam, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpMsgTransfer *__internal_ret = (Dz1InetFtpMsgTransfer *)Dz1Calloc(sizeof(Dz1InetFtpMsgTransfer), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpMsgTransfer_delAndSetNull, (void *)&__internal_ret);
		
		if (user && (__internal_ret->user = dz1_built_in_str_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if (pass && (__internal_ret->pass = dz1_built_in_str_clone(pass, errp)) == NULL) ERR_OUT(errp);
		else if (account && (__internal_ret->account = dz1_built_in_str_clone(account, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->peer = peer;
			__internal_ret->isPassive = isPassive;
			__internal_ret->files = files;
			__internal_ret->fileDone = fileDone;
			__internal_ret->fileDoneParam = fileDoneParam;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpMsgTransfer_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1InetFtpMsgTransfer_purge(Dz1InetFtpMsgTransfer *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	dz1_built_in_str_del(p->user);
	dz1_built_in_str_del(p->pass);
	dz1_built_in_str_del(p->account);
	Dz1InetFtpTransferList_del(p->files);
}

void Dz1InetFtpMsgTransfer_del(Dz1InetFtpMsgTransfer *p)
{
	if (p == NULL) return;
	Dz1InetFtpMsgTransfer_purge(p);
	Dz1Free(p);
}

void Dz1InetFtpMsgTransfer_dump(Dz1InetFtpMsgTransfer *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peer = ")); Dz1SockAddr_dump(p->peer, tab); 
		Dz1Thread_tprintf(tab, Dz1T("user = ")); dz1_built_in_str_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pass = ")); dz1_built_in_str_dump(p->pass, tab); 
		Dz1Thread_tprintf(tab, Dz1T("account = ")); dz1_built_in_str_dump(p->account, tab); 
		Dz1Thread_tprintf(tab, Dz1T("isPassive = ")); Dz1Bool_dump(&p->isPassive, tab); 
		Dz1Thread_tprintf(tab, Dz1T("files = ")); Dz1InetFtpTransferList_dump(p->files, tab); 
		Dz1Thread_tprintf(tab, Dz1T("fileDone = %p\n"), p->fileDone);
		Dz1Thread_tprintf(tab, Dz1T("fileDoneParam = %p\n"), p->fileDoneParam);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1InetFtpMsgTransfer
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpMsgTransferArg
Dz1InetFtpMsgTransferArg *Dz1InetFtpMsgTransferArg_new(Dz1InetFtpMsgTransferDoneInform cb, 
													   void *cbParam, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpMsgTransferArg *__internal_ret = (Dz1InetFtpMsgTransferArg *)Dz1Calloc(sizeof(Dz1InetFtpMsgTransferArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpMsgTransferArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->cb = cb;
		__internal_ret->cbParam = cbParam;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpMsgTransferArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1InetFtpMsgTransferArg_purge(Dz1InetFtpMsgTransferArg *p)
{
	if (p == NULL) return;
}

void Dz1InetFtpMsgTransferArg_del(Dz1InetFtpMsgTransferArg *p)
{
	if (p == NULL) return;
	Dz1InetFtpMsgTransferArg_purge(p);
	Dz1Free(p);
}

void Dz1InetFtpMsgTransferArg_dump(Dz1InetFtpMsgTransferArg *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("cb = %p\n"), p->cb);
		Dz1Thread_tprintf(tab, Dz1T("cbParam = %p\n"), p->cbParam);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1InetFtpMsgTransferArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpMsgFileDone
Dz1InetFtpMsgFileDone *Dz1InetFtpMsgFileDone_new(Dz1SockAddr *peer, 
												 Dz1SockAddr *local, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpMsgFileDone *__internal_ret = (Dz1InetFtpMsgFileDone *)Dz1Calloc(sizeof(Dz1InetFtpMsgFileDone), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpMsgFileDone_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->peer = peer;
		__internal_ret->local = local;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpMsgFileDone_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1InetFtpMsgFileDone_purge(Dz1InetFtpMsgFileDone *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1SockAddr_del(p->local);
}

void Dz1InetFtpMsgFileDone_del(Dz1InetFtpMsgFileDone *p)
{
	if (p == NULL) return;
	Dz1InetFtpMsgFileDone_purge(p);
	Dz1Free(p);
}

void Dz1InetFtpMsgFileDone_dump(Dz1InetFtpMsgFileDone *p, int tab)
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
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1InetFtpMsgFileDone
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpBasicMsg
Dz1InetFtpBasicMsg *Dz1InetFtpBasicMsg_new(Dz1SockAddr *peer, 
										   Dz1SockAddr *local, 
										   u32_t size, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpBasicMsg *__internal_ret = (Dz1InetFtpBasicMsg *)Dz1Calloc(sizeof(Dz1InetFtpBasicMsg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpBasicMsg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->size = size;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpBasicMsg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1InetFtpBasicMsg_purge(Dz1InetFtpBasicMsg *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1SockAddr_del(p->local);
}

void Dz1InetFtpBasicMsg_del(Dz1InetFtpBasicMsg *p)
{
	if (p == NULL) return;
	Dz1InetFtpBasicMsg_purge(p);
	Dz1Free(p);
}

void Dz1InetFtpBasicMsg_dump(Dz1InetFtpBasicMsg *p, int tab)
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
		Dz1Thread_tprintf(tab, Dz1T("size = ")); Dz1u32_dump(&p->size, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1InetFtpBasicMsg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpRcvrMsgReply
Dz1InetFtpRcvrMsgReply *Dz1InetFtpRcvrMsgReply_new(Dz1SockAddr *peer, 
												   Dz1SockAddr *local, 
												   Dz1InetFtpCPIMsgReply *reply, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpRcvrMsgReply *__internal_ret = (Dz1InetFtpRcvrMsgReply *)Dz1Calloc(sizeof(Dz1InetFtpRcvrMsgReply), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpRcvrMsgReply_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->reply = reply;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpRcvrMsgReply_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1InetFtpRcvrMsgReply_purge(Dz1InetFtpRcvrMsgReply *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1SockAddr_del(p->local);
	Dz1InetFtpCPIMsgReply_del(p->reply);
	Dz1Binary_del(p->pkt);
}

void Dz1InetFtpRcvrMsgReply_del(Dz1InetFtpRcvrMsgReply *p)
{
	if (p == NULL) return;
	Dz1InetFtpRcvrMsgReply_purge(p);
	Dz1Free(p);
}

void Dz1InetFtpRcvrMsgReply_dump(Dz1InetFtpRcvrMsgReply *p, int tab)
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
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("reply = ")); Dz1InetFtpCPIMsgReply_dump(p->reply, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1InetFtpRcvrMsgReply
////////////////////////////////////////////////////////////////////////////////


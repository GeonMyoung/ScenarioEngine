////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827DomainMsgs.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainCreateServer
ItsIso14827DomainCreateServer *ItsIso14827DomainCreateServer_new(Dz1Asn1UTF8Str *name, 
																 u32_t maxClient, 
																 ItsIso14827CodecOIDMapList *codecOIDMap, 
																 ItsIso14827ServerDomainCallback *cbs, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainCreateServer *__internal_ret = (ItsIso14827DomainCreateServer *)Dz1Calloc(sizeof(ItsIso14827DomainCreateServer), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DomainCreateServer_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->name = name;
		__internal_ret->maxClient = maxClient;
		__internal_ret->codecOIDMap = codecOIDMap;
		__internal_ret->cbs = cbs;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainCreateServer_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827DomainCreateServer_purge(ItsIso14827DomainCreateServer *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->name);
	ItsIso14827CodecOIDMapList_del(p->codecOIDMap);
	ItsIso14827ServerDomainCallback_del(p->cbs);
}

void ItsIso14827DomainCreateServer_del(ItsIso14827DomainCreateServer *p)
{
	if (p == NULL) return;
	ItsIso14827DomainCreateServer_purge(p);
	Dz1Free(p);
}

void ItsIso14827DomainCreateServer_dump(ItsIso14827DomainCreateServer *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("name = ")); Dz1Asn1UTF8Str_dump(p->name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("maxClient = ")); Dz1u32_dump(&p->maxClient, tab); 
		Dz1Thread_tprintf(tab, Dz1T("codecOIDMap = ")); ItsIso14827CodecOIDMapList_dump(p->codecOIDMap, tab); 
		// Normal member
		// ItsIso14827ServerDomainCallback : api = F0800000, ds = 08008000
		Dz1Thread_tprintf(tab, Dz1T("cbs = %p\n"), p->cbs);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827DomainCreateServer
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainCreateClient
ItsIso14827DomainCreateClient *ItsIso14827DomainCreateClient_new(Dz1Asn1UTF8Str *name, 
																 ItsIso14827ClientDomainCallback *cbs, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainCreateClient *__internal_ret = (ItsIso14827DomainCreateClient *)Dz1Calloc(sizeof(ItsIso14827DomainCreateClient), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DomainCreateClient_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->name = name;
		__internal_ret->cbs = cbs;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainCreateClient_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827DomainCreateClient_purge(ItsIso14827DomainCreateClient *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->name);
	ItsIso14827ClientDomainCallback_del(p->cbs);
}

void ItsIso14827DomainCreateClient_del(ItsIso14827DomainCreateClient *p)
{
	if (p == NULL) return;
	ItsIso14827DomainCreateClient_purge(p);
	Dz1Free(p);
}

void ItsIso14827DomainCreateClient_dump(ItsIso14827DomainCreateClient *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("name = ")); Dz1Asn1UTF8Str_dump(p->name, tab); 
		// Normal member
		// ItsIso14827ClientDomainCallback : api = F0800000, ds = 08008000
		Dz1Thread_tprintf(tab, Dz1T("cbs = %p\n"), p->cbs);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827DomainCreateClient
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainInitiate
ItsIso14827DomainInitiate *ItsIso14827DomainInitiate_new(Dz1SockAddr *peerAddr, 
														 Dz1SockAddr *localAddr, 
														 Dz1TcpClientSocket *sock, 
														 Iso14827Initiate *data, 
														 Dz1Asn1Codec initialCodec, 
														 ItsIso14827CRCCheck initialCRCMode, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainInitiate *__internal_ret = (ItsIso14827DomainInitiate *)Dz1Calloc(sizeof(ItsIso14827DomainInitiate), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DomainInitiate_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->peerAddr = peerAddr;
		__internal_ret->localAddr = localAddr;
		__internal_ret->sock = sock;
		__internal_ret->data = data;
		__internal_ret->initialCodec = initialCodec;
		__internal_ret->initialCRCMode = initialCRCMode;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainInitiate_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827DomainInitiate_purge(ItsIso14827DomainInitiate *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peerAddr);
	Dz1SockAddr_del(p->localAddr);
	Dz1TcpClientSocket_del(p->sock);
	Iso14827Initiate_del(p->data);
}

void ItsIso14827DomainInitiate_del(ItsIso14827DomainInitiate *p)
{
	if (p == NULL) return;
	ItsIso14827DomainInitiate_purge(p);
	Dz1Free(p);
}

void ItsIso14827DomainInitiate_dump(ItsIso14827DomainInitiate *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerAddr = ")); Dz1SockAddr_dump(p->peerAddr, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("localAddr = ")); Dz1SockAddr_dump(p->localAddr, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1Thread_tprintf(tab, Dz1T("sock = %p\n"), p->sock);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("data = ")); Iso14827Initiate_dump(p->data, tab); 
		Dz1Thread_tprintf(tab, Dz1T("initialCodec = %s(%d)\n"), Dz1Asn1CodecStr(p->initialCodec), p->initialCodec);
		Dz1Thread_tprintf(tab, Dz1T("initialCRCMode = %s(%d)\n"), ItsIso14827CRCCheckStr(p->initialCRCMode), p->initialCRCMode);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827DomainInitiate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainLogin
ItsIso14827DomainLogin *ItsIso14827DomainLogin_new(Dz1Asn1Codec initialCodec, 
												   Iso14827RejectLogin reason, 
												   Dz1SockAddr *peerAddr, 
												   Dz1SockAddr *localAddr, 
												   Dz1TcpClientSocket *sock, 
												   Dz1Asn1OctetStr *authInfo, 
												   Iso14827Login *data, 
												   ItsIso14827CRCCheck initialCRCMode, 
												   ItsIso14827ClientDomainViolatedSubscription *violatedSub, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainLogin *__internal_ret = (ItsIso14827DomainLogin *)Dz1Calloc(sizeof(ItsIso14827DomainLogin), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DomainLogin_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->initialCodec = initialCodec;
		__internal_ret->reason = reason;
		__internal_ret->peerAddr = peerAddr;
		__internal_ret->localAddr = localAddr;
		__internal_ret->sock = sock;
		__internal_ret->authInfo = authInfo;
		__internal_ret->data = data;
		__internal_ret->initialCRCMode = initialCRCMode;
		__internal_ret->violatedSub = violatedSub;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainLogin_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827DomainLogin_purge(ItsIso14827DomainLogin *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peerAddr);
	Dz1SockAddr_del(p->localAddr);
	Dz1TcpClientSocket_del(p->sock);
	Dz1Asn1OctetStr_del(p->authInfo);
	Iso14827Login_del(p->data);
	ItsIso14827ClientDomainViolatedSubscription_del(p->violatedSub);
}

void ItsIso14827DomainLogin_del(ItsIso14827DomainLogin *p)
{
	if (p == NULL) return;
	ItsIso14827DomainLogin_purge(p);
	Dz1Free(p);
}

void ItsIso14827DomainLogin_dump(ItsIso14827DomainLogin *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("initialCodec = %s(%d)\n"), Dz1Asn1CodecStr(p->initialCodec), p->initialCodec);
		Dz1Thread_tprintf(tab, Dz1T("reason = %s(%d)\n"), Iso14827RejectLoginStr(p->reason), p->reason);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerAddr = ")); Dz1SockAddr_dump(p->peerAddr, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("localAddr = ")); Dz1SockAddr_dump(p->localAddr, tab); 
		// _imp_dump
		// _imp_dump : pointer
		// _imp_dump : pointer : prim/construct : no dump api
		Dz1Thread_tprintf(tab, Dz1T("sock = %p\n"), p->sock);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("authInfo = ")); Dz1Asn1OctetStr_dump(p->authInfo, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("data = ")); Iso14827Login_dump(p->data, tab); 
		Dz1Thread_tprintf(tab, Dz1T("initialCRCMode = %s(%d)\n"), ItsIso14827CRCCheckStr(p->initialCRCMode), p->initialCRCMode);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("violatedSub = ")); ItsIso14827ClientDomainViolatedSubscription_dump(p->violatedSub, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827DomainLogin
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainBind
ItsIso14827DomainBind *ItsIso14827DomainBind_new(Dz1Asn1Codec initialCodec, 
												 Iso14827RejectLogin reason, 
												 Dz1Asn1UTF8Str *myDomain, 
												 Dz1Asn1UTF8Str *peerDomain, 
												 ItsIso14827SessionKey *bindKey, 
												 Dz1Asn1OctetStr *authInfo, 
												 Iso14827Login *data, 
												 ItsIso14827ClientDomainViolatedSubscription *violatedSub, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainBind *__internal_ret = (ItsIso14827DomainBind *)Dz1Calloc(sizeof(ItsIso14827DomainBind), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DomainBind_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->initialCodec = initialCodec;
		__internal_ret->reason = reason;
		__internal_ret->myDomain = myDomain;
		__internal_ret->peerDomain = peerDomain;
		__internal_ret->bindKey = bindKey;
		__internal_ret->authInfo = authInfo;
		__internal_ret->data = data;
		__internal_ret->violatedSub = violatedSub;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainBind_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827DomainBind_purge(ItsIso14827DomainBind *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->myDomain);
	Dz1Asn1UTF8Str_del(p->peerDomain);
	ItsIso14827SessionKey_del(p->bindKey);
	Dz1Asn1OctetStr_del(p->authInfo);
	Iso14827Login_del(p->data);
	ItsIso14827ClientDomainViolatedSubscription_del(p->violatedSub);
}

void ItsIso14827DomainBind_del(ItsIso14827DomainBind *p)
{
	if (p == NULL) return;
	ItsIso14827DomainBind_purge(p);
	Dz1Free(p);
}

void ItsIso14827DomainBind_dump(ItsIso14827DomainBind *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("initialCodec = %s(%d)\n"), Dz1Asn1CodecStr(p->initialCodec), p->initialCodec);
		Dz1Thread_tprintf(tab, Dz1T("reason = %s(%d)\n"), Iso14827RejectLoginStr(p->reason), p->reason);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("myDomain = ")); Dz1Asn1UTF8Str_dump(p->myDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerDomain = ")); Dz1Asn1UTF8Str_dump(p->peerDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("bindKey = ")); ItsIso14827SessionKey_dump(p->bindKey, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("authInfo = ")); Dz1Asn1OctetStr_dump(p->authInfo, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("data = ")); Iso14827Login_dump(p->data, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("violatedSub = ")); ItsIso14827ClientDomainViolatedSubscription_dump(p->violatedSub, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827DomainBind
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainLoginAccept
ItsIso14827DomainLoginAccept *ItsIso14827DomainLoginAccept_new(Dz1Asn1UTF8Str *domainName, 
															   Dz1Asn1UTF8Str *peerName, 
															   Dz1Asn1OctetStr *user, 
															   Dz1Asn1Codec selectedCodec, 
															   ItsIso14827CRCCheck CRCMode, 
															   ItsIso14827ServerDomainViolatedPublication *violatedPub, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainLoginAccept *__internal_ret = (ItsIso14827DomainLoginAccept *)Dz1Calloc(sizeof(ItsIso14827DomainLoginAccept), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DomainLoginAccept_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->domainName = domainName;
		__internal_ret->peerName = peerName;
		__internal_ret->user = user;
		__internal_ret->selectedCodec = selectedCodec;
		__internal_ret->CRCMode = CRCMode;
		__internal_ret->violatedPub = violatedPub;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainLoginAccept_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827DomainLoginAccept_purge(ItsIso14827DomainLoginAccept *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->domainName);
	Dz1Asn1UTF8Str_del(p->peerName);
	Dz1Asn1OctetStr_del(p->user);
	ItsIso14827ServerDomainViolatedPublication_del(p->violatedPub);
}

void ItsIso14827DomainLoginAccept_del(ItsIso14827DomainLoginAccept *p)
{
	if (p == NULL) return;
	ItsIso14827DomainLoginAccept_purge(p);
	Dz1Free(p);
}

void ItsIso14827DomainLoginAccept_dump(ItsIso14827DomainLoginAccept *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("domainName = ")); Dz1Asn1UTF8Str_dump(p->domainName, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerName = ")); Dz1Asn1UTF8Str_dump(p->peerName, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("selectedCodec = %s(%d)\n"), Dz1Asn1CodecStr(p->selectedCodec), p->selectedCodec);
		Dz1Thread_tprintf(tab, Dz1T("CRCMode = %s(%d)\n"), ItsIso14827CRCCheckStr(p->CRCMode), p->CRCMode);
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("violatedPub = ")); ItsIso14827ServerDomainViolatedPublication_dump(p->violatedPub, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827DomainLoginAccept
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainLoginReject
ItsIso14827DomainLoginReject *ItsIso14827DomainLoginReject_new(Dz1Asn1UTF8Str *domainName, 
															   Dz1Asn1UTF8Str *peerName, 
															   Dz1Asn1OctetStr *user, 
															   Iso14827RejectLogin reason, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainLoginReject *__internal_ret = (ItsIso14827DomainLoginReject *)Dz1Calloc(sizeof(ItsIso14827DomainLoginReject), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DomainLoginReject_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->domainName = domainName;
		__internal_ret->peerName = peerName;
		__internal_ret->user = user;
		__internal_ret->reason = reason;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainLoginReject_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827DomainLoginReject_purge(ItsIso14827DomainLoginReject *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->domainName);
	Dz1Asn1UTF8Str_del(p->peerName);
	Dz1Asn1OctetStr_del(p->user);
}

void ItsIso14827DomainLoginReject_del(ItsIso14827DomainLoginReject *p)
{
	if (p == NULL) return;
	ItsIso14827DomainLoginReject_purge(p);
	Dz1Free(p);
}

void ItsIso14827DomainLoginReject_dump(ItsIso14827DomainLoginReject *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("domainName = ")); Dz1Asn1UTF8Str_dump(p->domainName, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerName = ")); Dz1Asn1UTF8Str_dump(p->peerName, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reason = %s(%d)\n"), Iso14827RejectLoginStr(p->reason), p->reason);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827DomainLoginReject
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainTerminateClient
ItsIso14827DomainTerminateClient *ItsIso14827DomainTerminateClient_new(Dz1Asn1UTF8Str *myDomain, 
																	   Dz1Asn1UTF8Str *peerDomain, 
																	   Dz1Asn1OctetStr *user, 
																	   Iso14827Terminate reason, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainTerminateClient *__internal_ret = (ItsIso14827DomainTerminateClient *)Dz1Calloc(sizeof(ItsIso14827DomainTerminateClient), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DomainTerminateClient_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->myDomain = myDomain;
		__internal_ret->peerDomain = peerDomain;
		__internal_ret->user = user;
		__internal_ret->reason = reason;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainTerminateClient_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827DomainTerminateClient_purge(ItsIso14827DomainTerminateClient *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->myDomain);
	Dz1Asn1UTF8Str_del(p->peerDomain);
	Dz1Asn1OctetStr_del(p->user);
}

void ItsIso14827DomainTerminateClient_del(ItsIso14827DomainTerminateClient *p)
{
	if (p == NULL) return;
	ItsIso14827DomainTerminateClient_purge(p);
	Dz1Free(p);
}

void ItsIso14827DomainTerminateClient_dump(ItsIso14827DomainTerminateClient *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("myDomain = ")); Dz1Asn1UTF8Str_dump(p->myDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerDomain = ")); Dz1Asn1UTF8Str_dump(p->peerDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reason = %s(%d)\n"), Iso14827TerminateStr(p->reason), p->reason);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827DomainTerminateClient
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainLogout
ItsIso14827DomainLogout *ItsIso14827DomainLogout_new(Dz1Asn1UTF8Str *domainName, 
													 Dz1Asn1UTF8Str *peerName, 
													 Dz1Asn1OctetStr *user, 
													 Iso14827Logout reason, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainLogout *__internal_ret = (ItsIso14827DomainLogout *)Dz1Calloc(sizeof(ItsIso14827DomainLogout), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DomainLogout_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->domainName = domainName;
		__internal_ret->peerName = peerName;
		__internal_ret->user = user;
		__internal_ret->reason = reason;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainLogout_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827DomainLogout_purge(ItsIso14827DomainLogout *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->domainName);
	Dz1Asn1UTF8Str_del(p->peerName);
	Dz1Asn1OctetStr_del(p->user);
}

void ItsIso14827DomainLogout_del(ItsIso14827DomainLogout *p)
{
	if (p == NULL) return;
	ItsIso14827DomainLogout_purge(p);
	Dz1Free(p);
}

void ItsIso14827DomainLogout_dump(ItsIso14827DomainLogout *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("domainName = ")); Dz1Asn1UTF8Str_dump(p->domainName, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerName = ")); Dz1Asn1UTF8Str_dump(p->peerName, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reason = %s(%d)\n"), Iso14827LogoutStr(p->reason), p->reason);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827DomainLogout
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainEchoReply
ItsIso14827DomainEchoReply *ItsIso14827DomainEchoReply_new(Dz1Asn1UTF8Str *domainName, 
														   Dz1Asn1UTF8Str *peerName, 
														   Dz1Asn1OctetStr *user, 
														   u32_t confirmPktNbr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainEchoReply *__internal_ret = (ItsIso14827DomainEchoReply *)Dz1Calloc(sizeof(ItsIso14827DomainEchoReply), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DomainEchoReply_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->domainName = domainName;
		__internal_ret->peerName = peerName;
		__internal_ret->user = user;
		__internal_ret->confirmPktNbr = confirmPktNbr;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainEchoReply_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827DomainEchoReply_purge(ItsIso14827DomainEchoReply *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->domainName);
	Dz1Asn1UTF8Str_del(p->peerName);
	Dz1Asn1OctetStr_del(p->user);
}

void ItsIso14827DomainEchoReply_del(ItsIso14827DomainEchoReply *p)
{
	if (p == NULL) return;
	ItsIso14827DomainEchoReply_purge(p);
	Dz1Free(p);
}

void ItsIso14827DomainEchoReply_dump(ItsIso14827DomainEchoReply *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("domainName = ")); Dz1Asn1UTF8Str_dump(p->domainName, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerName = ")); Dz1Asn1UTF8Str_dump(p->peerName, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("confirmPktNbr = ")); Dz1u32_dump(&p->confirmPktNbr, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827DomainEchoReply
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainPrepareAccept
ItsIso14827DomainPrepareAccept *ItsIso14827DomainPrepareAccept_new(ItsIso14827DomainType domainType, 
																   Dz1Asn1UTF8Str *domainName, 
																   Dz1Asn1UTF8Str *peerName, 
																   Dz1Asn1OctetStr *user, 
																   u32_t serial, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainPrepareAccept *__internal_ret = (ItsIso14827DomainPrepareAccept *)Dz1Calloc(sizeof(ItsIso14827DomainPrepareAccept), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DomainPrepareAccept_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->domainType = domainType;
		__internal_ret->domainName = domainName;
		__internal_ret->peerName = peerName;
		__internal_ret->user = user;
		__internal_ret->serial = serial;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainPrepareAccept_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827DomainPrepareAccept_purge(ItsIso14827DomainPrepareAccept *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->domainName);
	Dz1Asn1UTF8Str_del(p->peerName);
	Dz1Asn1OctetStr_del(p->user);
}

void ItsIso14827DomainPrepareAccept_del(ItsIso14827DomainPrepareAccept *p)
{
	if (p == NULL) return;
	ItsIso14827DomainPrepareAccept_purge(p);
	Dz1Free(p);
}

void ItsIso14827DomainPrepareAccept_dump(ItsIso14827DomainPrepareAccept *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("domainType = %s(%d)\n"), ItsIso14827DomainTypeStr(p->domainType), p->domainType);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("domainName = ")); Dz1Asn1UTF8Str_dump(p->domainName, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerName = ")); Dz1Asn1UTF8Str_dump(p->peerName, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("serial = ")); Dz1u32_dump(&p->serial, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827DomainPrepareAccept
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainPrepareReject
ItsIso14827DomainPrepareReject *ItsIso14827DomainPrepareReject_new(ItsIso14827DomainType domainType, 
																   Dz1Asn1UTF8Str *domainName, 
																   Dz1Asn1UTF8Str *peerName, 
																   Dz1Asn1OctetStr *user, 
																   u32_t serial, 
																   Iso14827RejectSubscription reason, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainPrepareReject *__internal_ret = (ItsIso14827DomainPrepareReject *)Dz1Calloc(sizeof(ItsIso14827DomainPrepareReject), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DomainPrepareReject_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->domainType = domainType;
		__internal_ret->domainName = domainName;
		__internal_ret->peerName = peerName;
		__internal_ret->user = user;
		__internal_ret->serial = serial;
		__internal_ret->reason = reason;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainPrepareReject_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827DomainPrepareReject_purge(ItsIso14827DomainPrepareReject *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->domainName);
	Dz1Asn1UTF8Str_del(p->peerName);
	Dz1Asn1OctetStr_del(p->user);
}

void ItsIso14827DomainPrepareReject_del(ItsIso14827DomainPrepareReject *p)
{
	if (p == NULL) return;
	ItsIso14827DomainPrepareReject_purge(p);
	Dz1Free(p);
}

void ItsIso14827DomainPrepareReject_dump(ItsIso14827DomainPrepareReject *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("domainType = %s(%d)\n"), ItsIso14827DomainTypeStr(p->domainType), p->domainType);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("domainName = ")); Dz1Asn1UTF8Str_dump(p->domainName, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerName = ")); Dz1Asn1UTF8Str_dump(p->peerName, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("serial = ")); Dz1u32_dump(&p->serial, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reason = %s(%d)\n"), Iso14827RejectSubscriptionStr(p->reason), p->reason);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827DomainPrepareReject
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainDataProvide
ItsIso14827DomainDataProvide *ItsIso14827DomainDataProvide_new(ItsIso14827DomainType domainType, 
															   Dz1Asn1UTF8Str *domainName, 
															   Dz1Asn1UTF8Str *peerName, 
															   Dz1Asn1OctetStr *user, 
															   u32_t serial, 
															   Iso14827EndAppMsg *eam, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainDataProvide *__internal_ret = (ItsIso14827DomainDataProvide *)Dz1Calloc(sizeof(ItsIso14827DomainDataProvide), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DomainDataProvide_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->domainType = domainType;
		__internal_ret->domainName = domainName;
		__internal_ret->peerName = peerName;
		__internal_ret->user = user;
		__internal_ret->serial = serial;
		__internal_ret->eam = eam;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainDataProvide_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827DomainDataProvide_purge(ItsIso14827DomainDataProvide *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->domainName);
	Dz1Asn1UTF8Str_del(p->peerName);
	Dz1Asn1OctetStr_del(p->user);
	Iso14827EndAppMsg_del(p->eam);
}

void ItsIso14827DomainDataProvide_del(ItsIso14827DomainDataProvide *p)
{
	if (p == NULL) return;
	ItsIso14827DomainDataProvide_purge(p);
	Dz1Free(p);
}

void ItsIso14827DomainDataProvide_dump(ItsIso14827DomainDataProvide *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("domainType = %s(%d)\n"), ItsIso14827DomainTypeStr(p->domainType), p->domainType);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("domainName = ")); Dz1Asn1UTF8Str_dump(p->domainName, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerName = ")); Dz1Asn1UTF8Str_dump(p->peerName, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("serial = ")); Dz1u32_dump(&p->serial, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("eam = ")); Iso14827EndAppMsg_dump(p->eam, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827DomainDataProvide
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainDataControl
ItsIso14827DomainDataControl *ItsIso14827DomainDataControl_new(ItsIso14827DomainType domainType, 
															   Dz1Asn1UTF8Str *domainName, 
															   Dz1Asn1UTF8Str *peerName, 
															   Dz1Asn1OctetStr *user, 
															   u32_t serial, 
															   Iso14827PublicationMgmt cmd, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainDataControl *__internal_ret = (ItsIso14827DomainDataControl *)Dz1Calloc(sizeof(ItsIso14827DomainDataControl), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DomainDataControl_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->domainType = domainType;
		__internal_ret->domainName = domainName;
		__internal_ret->peerName = peerName;
		__internal_ret->user = user;
		__internal_ret->serial = serial;
		__internal_ret->cmd = cmd;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainDataControl_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827DomainDataControl_purge(ItsIso14827DomainDataControl *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->domainName);
	Dz1Asn1UTF8Str_del(p->peerName);
	Dz1Asn1OctetStr_del(p->user);
}

void ItsIso14827DomainDataControl_del(ItsIso14827DomainDataControl *p)
{
	if (p == NULL) return;
	ItsIso14827DomainDataControl_purge(p);
	Dz1Free(p);
}

void ItsIso14827DomainDataControl_dump(ItsIso14827DomainDataControl *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("domainType = %s(%d)\n"), ItsIso14827DomainTypeStr(p->domainType), p->domainType);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("domainName = ")); Dz1Asn1UTF8Str_dump(p->domainName, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerName = ")); Dz1Asn1UTF8Str_dump(p->peerName, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("serial = ")); Dz1u32_dump(&p->serial, tab); 
		Dz1Thread_tprintf(tab, Dz1T("cmd = %s(%d)\n"), Iso14827PublicationMgmtStr(p->cmd), p->cmd);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827DomainDataControl
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainSubscription
ItsIso14827DomainSubscription *ItsIso14827DomainSubscription_new(ItsIso14827DomainType domainType, 
																 Dz1Asn1UTF8Str *domainName, 
																 Dz1Asn1UTF8Str *peerName, 
																 Dz1Asn1OctetStr *user, 
																 Iso14827SubscriptionData *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainSubscription *__internal_ret = (ItsIso14827DomainSubscription *)Dz1Calloc(sizeof(ItsIso14827DomainSubscription), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DomainSubscription_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->domainType = domainType;
		__internal_ret->domainName = domainName;
		__internal_ret->peerName = peerName;
		__internal_ret->user = user;
		__internal_ret->data = data;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainSubscription_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827DomainSubscription_purge(ItsIso14827DomainSubscription *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->domainName);
	Dz1Asn1UTF8Str_del(p->peerName);
	Dz1Asn1OctetStr_del(p->user);
	Iso14827SubscriptionData_del(p->data);
}

void ItsIso14827DomainSubscription_del(ItsIso14827DomainSubscription *p)
{
	if (p == NULL) return;
	ItsIso14827DomainSubscription_purge(p);
	Dz1Free(p);
}

void ItsIso14827DomainSubscription_dump(ItsIso14827DomainSubscription *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("domainType = %s(%d)\n"), ItsIso14827DomainTypeStr(p->domainType), p->domainType);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("domainName = ")); Dz1Asn1UTF8Str_dump(p->domainName, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerName = ")); Dz1Asn1UTF8Str_dump(p->peerName, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("data = ")); Iso14827SubscriptionData_dump(p->data, tab); 
		Dz1Thread_tprintf(tab, Dz1T("retSerial = ")); Dz1u32_dump(&p->retSerial, tab); 
		Dz1Thread_tprintf(tab, Dz1T("retError = %s(%d)\n"), Iso14827RejectSubscriptionStr(p->retError), p->retError);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827DomainSubscription
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainSubCancel
ItsIso14827DomainSubCancel *ItsIso14827DomainSubCancel_new(ItsIso14827DomainType domainType, 
														   Dz1Asn1UTF8Str *domainName, 
														   Dz1Asn1UTF8Str *peerName, 
														   Dz1Asn1OctetStr *user, 
														   u32_t serial, 
														   Iso14827SubscriptionCancel reason, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainSubCancel *__internal_ret = (ItsIso14827DomainSubCancel *)Dz1Calloc(sizeof(ItsIso14827DomainSubCancel), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DomainSubCancel_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->domainType = domainType;
		__internal_ret->domainName = domainName;
		__internal_ret->peerName = peerName;
		__internal_ret->user = user;
		__internal_ret->serial = serial;
		__internal_ret->reason = reason;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainSubCancel_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827DomainSubCancel_purge(ItsIso14827DomainSubCancel *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->domainName);
	Dz1Asn1UTF8Str_del(p->peerName);
	Dz1Asn1OctetStr_del(p->user);
}

void ItsIso14827DomainSubCancel_del(ItsIso14827DomainSubCancel *p)
{
	if (p == NULL) return;
	ItsIso14827DomainSubCancel_purge(p);
	Dz1Free(p);
}

void ItsIso14827DomainSubCancel_dump(ItsIso14827DomainSubCancel *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("domainType = %s(%d)\n"), ItsIso14827DomainTypeStr(p->domainType), p->domainType);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("domainName = ")); Dz1Asn1UTF8Str_dump(p->domainName, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerName = ")); Dz1Asn1UTF8Str_dump(p->peerName, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("serial = ")); Dz1u32_dump(&p->serial, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reason = %s(%d)\n"), Iso14827SubscriptionCancelStr(p->reason), p->reason);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827DomainSubCancel
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainRejectPubData
ItsIso14827DomainRejectPubData *ItsIso14827DomainRejectPubData_new(ItsIso14827DomainType domainType, 
																   Dz1Asn1UTF8Str *domainName, 
																   Dz1Asn1UTF8Str *peerName, 
																   Dz1Asn1OctetStr *user, 
																   u32_t serial, 
																   u32_t pubSerial, 
																   Iso14827RejectPubDataReason reason, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainRejectPubData *__internal_ret = (ItsIso14827DomainRejectPubData *)Dz1Calloc(sizeof(ItsIso14827DomainRejectPubData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DomainRejectPubData_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->domainType = domainType;
		__internal_ret->domainName = domainName;
		__internal_ret->peerName = peerName;
		__internal_ret->user = user;
		__internal_ret->serial = serial;
		__internal_ret->pubSerial = pubSerial;
		__internal_ret->reason = reason;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainRejectPubData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827DomainRejectPubData_purge(ItsIso14827DomainRejectPubData *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->domainName);
	Dz1Asn1UTF8Str_del(p->peerName);
	Dz1Asn1OctetStr_del(p->user);
}

void ItsIso14827DomainRejectPubData_del(ItsIso14827DomainRejectPubData *p)
{
	if (p == NULL) return;
	ItsIso14827DomainRejectPubData_purge(p);
	Dz1Free(p);
}

void ItsIso14827DomainRejectPubData_dump(ItsIso14827DomainRejectPubData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("domainType = %s(%d)\n"), ItsIso14827DomainTypeStr(p->domainType), p->domainType);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("domainName = ")); Dz1Asn1UTF8Str_dump(p->domainName, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerName = ")); Dz1Asn1UTF8Str_dump(p->peerName, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("serial = ")); Dz1u32_dump(&p->serial, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pubSerial = ")); Dz1u32_dump(&p->pubSerial, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reason = %s(%d)\n"), Iso14827RejectPubDataReasonStr(p->reason), p->reason);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827DomainRejectPubData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ViolatedPublication
ItsIso14827ViolatedPublication *ItsIso14827ViolatedPublication_new(ItsIso14827DomainType domainType, 
																   Dz1Asn1UTF8Str *myDomain, 
																   Dz1Asn1UTF8Str *peerDomain, 
																   Dz1Asn1OctetStr *user, 
																   Iso14827Publication *pub, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ViolatedPublication *__internal_ret = (ItsIso14827ViolatedPublication *)Dz1Calloc(sizeof(ItsIso14827ViolatedPublication), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ViolatedPublication_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->domainType = domainType;
		__internal_ret->myDomain = myDomain;
		__internal_ret->peerDomain = peerDomain;
		__internal_ret->user = user;
		__internal_ret->pub = pub;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ViolatedPublication_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827ViolatedPublication_purge(ItsIso14827ViolatedPublication *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->myDomain);
	Dz1Asn1UTF8Str_del(p->peerDomain);
	Dz1Asn1OctetStr_del(p->user);
	Iso14827Publication_del(p->pub);
}

void ItsIso14827ViolatedPublication_del(ItsIso14827ViolatedPublication *p)
{
	if (p == NULL) return;
	ItsIso14827ViolatedPublication_purge(p);
	Dz1Free(p);
}

void ItsIso14827ViolatedPublication_dump(ItsIso14827ViolatedPublication *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("domainType = %s(%d)\n"), ItsIso14827DomainTypeStr(p->domainType), p->domainType);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("myDomain = ")); Dz1Asn1UTF8Str_dump(p->myDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerDomain = ")); Dz1Asn1UTF8Str_dump(p->peerDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("pub = ")); Iso14827Publication_dump(p->pub, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827ViolatedPublication
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ViolatedSubscription
ItsIso14827ViolatedSubscription *ItsIso14827ViolatedSubscription_new(ItsIso14827DomainType domainType, 
																	 Dz1Asn1UTF8Str *myDomain, 
																	 Dz1Asn1UTF8Str *peerDomain, 
																	 Dz1Asn1OctetStr *user, 
																	 Iso14827Subscription *sub, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ViolatedSubscription *__internal_ret = (ItsIso14827ViolatedSubscription *)Dz1Calloc(sizeof(ItsIso14827ViolatedSubscription), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ViolatedSubscription_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->domainType = domainType;
		__internal_ret->myDomain = myDomain;
		__internal_ret->peerDomain = peerDomain;
		__internal_ret->user = user;
		__internal_ret->sub = sub;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ViolatedSubscription_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827ViolatedSubscription_purge(ItsIso14827ViolatedSubscription *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->myDomain);
	Dz1Asn1UTF8Str_del(p->peerDomain);
	Dz1Asn1OctetStr_del(p->user);
	Iso14827Subscription_del(p->sub);
}

void ItsIso14827ViolatedSubscription_del(ItsIso14827ViolatedSubscription *p)
{
	if (p == NULL) return;
	ItsIso14827ViolatedSubscription_purge(p);
	Dz1Free(p);
}

void ItsIso14827ViolatedSubscription_dump(ItsIso14827ViolatedSubscription *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("domainType = %s(%d)\n"), ItsIso14827DomainTypeStr(p->domainType), p->domainType);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("myDomain = ")); Dz1Asn1UTF8Str_dump(p->myDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerDomain = ")); Dz1Asn1UTF8Str_dump(p->peerDomain, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("sub = ")); Iso14827Subscription_dump(p->sub, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827ViolatedSubscription
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ItsIso14827Msgs.h"

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827MsgDefault
ItsIso14827MsgDefault *ItsIso14827MsgDefault_new(u32_t *dummy, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827MsgDefault *__internal_ret = (ItsIso14827MsgDefault *)Dz1Calloc(sizeof(ItsIso14827MsgDefault), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827MsgDefault_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->dummy = dummy;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827MsgDefault_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827MsgDefault_purge(ItsIso14827MsgDefault *p)
{
	if (p == NULL) return;
	Dz1u32_del(p->dummy);
}

void ItsIso14827MsgDefault_del(ItsIso14827MsgDefault *p)
{
	if (p == NULL) return;
	ItsIso14827MsgDefault_purge(p);
	Dz1Free(p);
}

void ItsIso14827MsgDefault_dump(ItsIso14827MsgDefault *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("dummy = ")); Dz1u32_dump(p->dummy, tab); 
	}
}
// ItsIso14827MsgDefault
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827OpenPort
ItsIso14827OpenPort *ItsIso14827OpenPort_new(u16_t port, 
											 Dz1Asn1Codec initialCodec, 
											 ItsIso14827CRCCheck initialCRCMode, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827OpenPort *__internal_ret = (ItsIso14827OpenPort *)Dz1Calloc(sizeof(ItsIso14827OpenPort), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827OpenPort_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->port = port;
		__internal_ret->initialCodec = initialCodec;
		__internal_ret->initialCRCMode = initialCRCMode;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827OpenPort_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827OpenPort_purge(ItsIso14827OpenPort *p)
{
	if (p == NULL) return;
}

void ItsIso14827OpenPort_del(ItsIso14827OpenPort *p)
{
	if (p == NULL) return;
	ItsIso14827OpenPort_purge(p);
	Dz1Free(p);
}

void ItsIso14827OpenPort_dump(ItsIso14827OpenPort *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("port = ")); Dz1u16_dump(&p->port, tab); 
		Dz1Thread_tprintf(tab, Dz1T("initialCodec = %s(%d)\n"), Dz1Asn1CodecStr(p->initialCodec), p->initialCodec);
		Dz1Thread_tprintf(tab, Dz1T("initialCRCMode = %s(%d)\n"), ItsIso14827CRCCheckStr(p->initialCRCMode), p->initialCRCMode);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827OpenPort
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827ClosePort
ItsIso14827ClosePort *ItsIso14827ClosePort_new(u16_t port, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827ClosePort *__internal_ret = (ItsIso14827ClosePort *)Dz1Calloc(sizeof(ItsIso14827ClosePort), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827ClosePort_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->port = port;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827ClosePort_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827ClosePort_purge(ItsIso14827ClosePort *p)
{
	if (p == NULL) return;
}

void ItsIso14827ClosePort_del(ItsIso14827ClosePort *p)
{
	if (p == NULL) return;
	ItsIso14827ClosePort_purge(p);
	Dz1Free(p);
}

void ItsIso14827ClosePort_dump(ItsIso14827ClosePort *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("port = ")); Dz1u16_dump(&p->port, tab); 
	}
}
// ItsIso14827ClosePort
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DebugStatus
ItsIso14827DebugStatus *ItsIso14827DebugStatus_new(ItsIso14827DomainType type, 
												   Dz1Asn1UTF8Str *myDomain, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DebugStatus *__internal_ret = (ItsIso14827DebugStatus *)Dz1Calloc(sizeof(ItsIso14827DebugStatus), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DebugStatus_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->type = type;
		__internal_ret->myDomain = myDomain;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DebugStatus_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827DebugStatus_purge(ItsIso14827DebugStatus *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->myDomain);
}

void ItsIso14827DebugStatus_del(ItsIso14827DebugStatus *p)
{
	if (p == NULL) return;
	ItsIso14827DebugStatus_purge(p);
	Dz1Free(p);
}

void ItsIso14827DebugStatus_dump(ItsIso14827DebugStatus *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("type = %s(%d)\n"), ItsIso14827DomainTypeStr(p->type), p->type);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("myDomain = ")); Dz1Asn1UTF8Str_dump(p->myDomain, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827DebugStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DebugPktDump
ItsIso14827DebugPktDump *ItsIso14827DebugPktDump_new(u32_t flag, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DebugPktDump *__internal_ret = (ItsIso14827DebugPktDump *)Dz1Calloc(sizeof(ItsIso14827DebugPktDump), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DebugPktDump_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->flag = flag;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DebugPktDump_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827DebugPktDump_purge(ItsIso14827DebugPktDump *p)
{
	if (p == NULL) return;
}

void ItsIso14827DebugPktDump_del(ItsIso14827DebugPktDump *p)
{
	if (p == NULL) return;
	ItsIso14827DebugPktDump_purge(p);
	Dz1Free(p);
}

void ItsIso14827DebugPktDump_dump(ItsIso14827DebugPktDump *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("flag = ")); Dz1u32_dump(&p->flag, tab); 
	}
}
// ItsIso14827DebugPktDump
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ItsIso14827DomainCtrl
ItsIso14827DomainCtrl *ItsIso14827DomainCtrl_new(ItsIso14827DomainType myDomainType, 
												 Dz1Asn1UTF8Str *domainName, 
												 Dz1Asn1UTF8Str *peerName, 
												 Dz1Asn1OctetStr *user, 
												 u32_t flag, 
												 bool_t on_off, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827DomainCtrl *__internal_ret = (ItsIso14827DomainCtrl *)Dz1Calloc(sizeof(ItsIso14827DomainCtrl), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827DomainCtrl_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->myDomainType = myDomainType;
		__internal_ret->domainName = domainName;
		__internal_ret->peerName = peerName;
		__internal_ret->user = user;
		__internal_ret->flag = flag;
		__internal_ret->on_off = on_off;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827DomainCtrl_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void ItsIso14827DomainCtrl_purge(ItsIso14827DomainCtrl *p)
{
	if (p == NULL) return;
	Dz1Asn1UTF8Str_del(p->domainName);
	Dz1Asn1UTF8Str_del(p->peerName);
	Dz1Asn1OctetStr_del(p->user);
}

void ItsIso14827DomainCtrl_del(ItsIso14827DomainCtrl *p)
{
	if (p == NULL) return;
	ItsIso14827DomainCtrl_purge(p);
	Dz1Free(p);
}

void ItsIso14827DomainCtrl_dump(ItsIso14827DomainCtrl *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("myDomainType = %s(%d)\n"), ItsIso14827DomainTypeStr(p->myDomainType), p->myDomainType);
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("domainName = ")); Dz1Asn1UTF8Str_dump(p->domainName, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("peerName = ")); Dz1Asn1UTF8Str_dump(p->peerName, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("user = ")); Dz1Asn1OctetStr_dump(p->user, tab); 
		Dz1Thread_tprintf(tab, Dz1T("flag = ")); Dz1u32_dump(&p->flag, tab); 
		Dz1Thread_tprintf(tab, Dz1T("on_off = ")); Dz1Bool_dump(&p->on_off, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ItsIso14827DomainCtrl
////////////////////////////////////////////////////////////////////////////////


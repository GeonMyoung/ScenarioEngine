#include <dz1_thread_stdio.h>
#include "ItsIso14827Types.h"
////////////////////////////////////////////////////////////////////////////////
// ItsIso14827SessionKey
ItsIso14827SessionKey *_ItsIso14827SessionKey_new(Dz1SockAddr *peer, Dz1SockAddr *local, u32_t sid, Dz1Error *err, const char *__file, int __line)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ItsIso14827SessionKey *__internal_ret = (ItsIso14827SessionKey *)_Dz1Calloc(sizeof(ItsIso14827SessionKey), 1, errp, __file, __line);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ItsIso14827SessionKey_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->sid = sid;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827SessionKey_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

ItsIso14827SessionKey *_ItsIso14827SessionKey_clone(ItsIso14827SessionKey *src, Dz1Error *err, const char *__file, int __line)
{
	ItsIso14827SessionKey *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (ItsIso14827SessionKey *)_Dz1Calloc(sizeof(ItsIso14827SessionKey), 1, errp, __file, __line)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ItsIso14827SessionKey_delAndSetNull, (void *)&ret);

		if (src->peer && (ret->peer = _Dz1SockAddr_clone(src->peer, errp, __file, __line)) == NULL) ERR_OUT(errp);
		else if (src->local && (ret->local = _Dz1SockAddr_clone(src->local, errp, __file, __line)) == NULL) ERR_OUT(errp);
		else
		{
			ret->sid = src->sid;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ItsIso14827SessionKey_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ItsIso14827SessionKey_del(ItsIso14827SessionKey *p)
{
	if (p == NULL) return;
	if (p->peer) Dz1SockAddr_del(p->peer);
	if (p->local) Dz1SockAddr_del(p->local);
	Dz1Free(p);
}

void ItsIso14827SessionKey_dump(ItsIso14827SessionKey *p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	if (p->peer == NULL) Dz1Thread_tprintf(tab, Dz1T("peer = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("peer = ")); Dz1SockAddr_dump(p->peer, tab); /* using dump func */ }

	if (p->local == NULL) Dz1Thread_tprintf(tab, Dz1T("local = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("local = ")); Dz1SockAddr_dump(p->local, tab); /* using dump func */ }

	Dz1Thread_tprintf(tab, Dz1T("sid = ")); Dz1u32_dump(&p->sid, tab);

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}

int ItsIso14827SessionKey_cmp(ItsIso14827SessionKey *a, ItsIso14827SessionKey *b)
{
	int ret = 0;
	if ((ret = Dz1SockAddr_cmp(a->peer, b->peer)) != 0) return ret;
	else if ((ret = Dz1SockAddr_cmp(a->local, b->local)) != 0) return ret;
	else if ((ret = Dz1u32_cmp(&a->sid, &b->sid)) != 0) return ret;
	else return ret;
}
// ItsIso14827SessionKey
////////////////////////////////////////////////////////////////////////////////

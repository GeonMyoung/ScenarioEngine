////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Dz1SockUtilUriDef.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilUriInfoA
Dz1SockUtilUriInfoA *Dz1SockUtilUriInfoA_new(str_t prot, 
											 str_t host, 
											 u16_t port, 
											 str_t path, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SockUtilUriInfoA *__internal_ret = (Dz1SockUtilUriInfoA *)Dz1Calloc(sizeof(Dz1SockUtilUriInfoA), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SockUtilUriInfoA_delAndSetNull, (void *)&__internal_ret);
		
		if (prot && (__internal_ret->prot = dz1_built_in_str_clone(prot, errp)) == NULL) ERR_OUT(errp);
		else if (host && (__internal_ret->host = dz1_built_in_str_clone(host, errp)) == NULL) ERR_OUT(errp);
		else if (path && (__internal_ret->path = dz1_built_in_str_clone(path, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->port = port;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilUriInfoA_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1SockUtilUriInfoA_copy(Dz1SockUtilUriInfoA *dst, Dz1SockUtilUriInfoA *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->prot && (dst->prot = dz1_built_in_str_clone(src->prot, errp)) == NULL) ERR_OUT(errp);
	else if (src->host && (dst->host = dz1_built_in_str_clone(src->host, errp)) == NULL) ERR_OUT(errp);
	else if (src->path && (dst->path = dz1_built_in_str_clone(src->path, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->port = src->port;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1SockUtilUriInfoA *Dz1SockUtilUriInfoA_clone(Dz1SockUtilUriInfoA *src, Dz1Error *err)
{
	Dz1SockUtilUriInfoA *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1SockUtilUriInfoA *)Dz1Calloc(sizeof(Dz1SockUtilUriInfoA), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1SockUtilUriInfoA_delAndSetNull, (void *)&dst);
		if (Dz1SockUtilUriInfoA_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilUriInfoA_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1SockUtilUriInfoA_purge(Dz1SockUtilUriInfoA *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->prot);
	dz1_built_in_str_del(p->host);
	dz1_built_in_str_del(p->path);
}

void Dz1SockUtilUriInfoA_del(Dz1SockUtilUriInfoA *p)
{
	if (p == NULL) return;
	Dz1SockUtilUriInfoA_purge(p);
	Dz1Free(p);
}

void Dz1SockUtilUriInfoA_dump(Dz1SockUtilUriInfoA *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n"); tab++;
		Dz1ThreadA_tprintf(tab, "prot = "); dz1_built_in_str_dump(p->prot, tab); 
		Dz1ThreadA_tprintf(tab, "host = "); dz1_built_in_str_dump(p->host, tab); 
		Dz1ThreadA_tprintf(tab, "port = "); Dz1u16_dump(&p->port, tab); 
		Dz1ThreadA_tprintf(tab, "path = "); dz1_built_in_str_dump(p->path, tab); 
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
int Dz1SockUtilUriInfoA_cmp(Dz1SockUtilUriInfoA *a, Dz1SockUtilUriInfoA *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->prot == NULL && b->prot == NULL) ret = 0;
	else if (a->prot == NULL /*&& b->prot != NULL*/) ret = -1;
	else if (/*a->prot != NULL &&*/ b->prot == NULL) ret = 1;
	else if ((ret = dz1_built_in_str_cmp(a->prot, b->prot)) != 0) { }
	else if (a->host == NULL && b->host == NULL) ret = 0;
	else if (a->host == NULL /*&& b->host != NULL*/) ret = -1;
	else if (/*a->host != NULL &&*/ b->host == NULL) ret = 1;
	else if ((ret = dz1_built_in_str_cmp(a->host, b->host)) != 0) { }
	else if ((ret = Dz1u16_cmp(&a->port, &b->port)) != 0) { }
	else if (a->path == NULL && b->path == NULL) ret = 0;
	else if (a->path == NULL /*&& b->path != NULL*/) ret = -1;
	else if (/*a->path != NULL &&*/ b->path == NULL) ret = 1;
	else if ((ret = dz1_built_in_str_cmp(a->path, b->path)) != 0) { }
	return ret;
}
// Dz1SockUtilUriInfoA
////////////////////////////////////////////////////////////////////////////////

#ifndef UNIX_SYSTEM
////////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilUriInfoW
Dz1SockUtilUriInfoW *Dz1SockUtilUriInfoW_new(wstr_t prot, 
											 wstr_t host, 
											 u16_t port, 
											 wstr_t path, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1SockUtilUriInfoW *__internal_ret = (Dz1SockUtilUriInfoW *)Dz1Calloc(sizeof(Dz1SockUtilUriInfoW), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1SockUtilUriInfoW_delAndSetNull, (void *)&__internal_ret);
		
		if (prot && (__internal_ret->prot = dz1_built_in_wstr_clone(prot, errp)) == NULL) ERR_OUT(errp);
		else if (host && (__internal_ret->host = dz1_built_in_wstr_clone(host, errp)) == NULL) ERR_OUT(errp);
		else if (path && (__internal_ret->path = dz1_built_in_wstr_clone(path, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->port = port;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilUriInfoW_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1SockUtilUriInfoW_copy(Dz1SockUtilUriInfoW *dst, Dz1SockUtilUriInfoW *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->prot && (dst->prot = dz1_built_in_wstr_clone(src->prot, errp)) == NULL) ERR_OUT(errp);
	else if (src->host && (dst->host = dz1_built_in_wstr_clone(src->host, errp)) == NULL) ERR_OUT(errp);
	else if (src->path && (dst->path = dz1_built_in_wstr_clone(src->path, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->port = src->port;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1SockUtilUriInfoW *Dz1SockUtilUriInfoW_clone(Dz1SockUtilUriInfoW *src, Dz1Error *err)
{
	Dz1SockUtilUriInfoW *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1SockUtilUriInfoW *)Dz1Calloc(sizeof(Dz1SockUtilUriInfoW), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1SockUtilUriInfoW_delAndSetNull, (void *)&dst);
		if (Dz1SockUtilUriInfoW_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1SockUtilUriInfoW_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1SockUtilUriInfoW_purge(Dz1SockUtilUriInfoW *p)
{
	if (p == NULL) return;
	dz1_built_in_wstr_del(p->prot);
	dz1_built_in_wstr_del(p->host);
	dz1_built_in_wstr_del(p->path);
}

void Dz1SockUtilUriInfoW_del(Dz1SockUtilUriInfoW *p)
{
	if (p == NULL) return;
	Dz1SockUtilUriInfoW_purge(p);
	Dz1Free(p);
}

void Dz1SockUtilUriInfoW_dump(Dz1SockUtilUriInfoW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n"); tab++;
		Dz1ThreadW_tprintf(tab, L"prot = "); dz1_built_in_wstr_dump(p->prot, tab); 
		Dz1ThreadW_tprintf(tab, L"host = "); dz1_built_in_wstr_dump(p->host, tab); 
		Dz1ThreadW_tprintf(tab, L"port = "); Dz1u16_dump(&p->port, tab); 
		Dz1ThreadW_tprintf(tab, L"path = "); dz1_built_in_wstr_dump(p->path, tab); 
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
int Dz1SockUtilUriInfoW_cmp(Dz1SockUtilUriInfoW *a, Dz1SockUtilUriInfoW *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->prot == NULL && b->prot == NULL) ret = 0;
	else if (a->prot == NULL /*&& b->prot != NULL*/) ret = -1;
	else if (/*a->prot != NULL &&*/ b->prot == NULL) ret = 1;
	else if ((ret = dz1_built_in_wstr_cmp(a->prot, b->prot)) != 0) { }
	else if (a->host == NULL && b->host == NULL) ret = 0;
	else if (a->host == NULL /*&& b->host != NULL*/) ret = -1;
	else if (/*a->host != NULL &&*/ b->host == NULL) ret = 1;
	else if ((ret = dz1_built_in_wstr_cmp(a->host, b->host)) != 0) { }
	else if ((ret = Dz1u16_cmp(&a->port, &b->port)) != 0) { }
	else if (a->path == NULL && b->path == NULL) ret = 0;
	else if (a->path == NULL /*&& b->path != NULL*/) ret = -1;
	else if (/*a->path != NULL &&*/ b->path == NULL) ret = 1;
	else if ((ret = dz1_built_in_wstr_cmp(a->path, b->path)) != 0) { }
	return ret;
}
// Dz1SockUtilUriInfoW
////////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM


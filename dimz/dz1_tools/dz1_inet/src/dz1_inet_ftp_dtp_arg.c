////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_inet_ftp_dtp_arg.h"

////////////////////////////////////////////////////////////////////////////////
// DataFragmentList
static Dz1Error DataFragmentList_add(DataFragmentList *p, Dz1Binary *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct DataFragmentListMkArrArg
{
	Dz1Binary **arr;
	unsigned int idx;
} DataFragmentListMkArrArg;

static Dz1Error _DataFragmentList_get_array(void *ptr, Dz1Binary *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	DataFragmentListMkArrArg *arg = (DataFragmentListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1Binary **DataFragmentList_get_array(DataFragmentList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1Binary **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1Binary **)Dz1Calloc(sizeof(Dz1Binary *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		DataFragmentListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _DataFragmentList_get_array, (void *)&arg);
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

static Dz1Error DataFragmentList_travelForward(DataFragmentList *p, Dz1Error (*func)(void *ptr, Dz1Binary *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error DataFragmentList_travelBackward(DataFragmentList *p, Dz1Error (*func)(void *ptr, Dz1Binary *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int DataFragmentList_count(DataFragmentList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

DataFragmentList *DataFragmentList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	DataFragmentList *ret = (DataFragmentList *)Dz1Calloc(sizeof(DataFragmentList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(DataFragmentList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)Dz1Binary_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = DataFragmentList_count;
			ret->travel = DataFragmentList_travelForward;
			ret->travelForward = DataFragmentList_travelForward;
			ret->travelBackward = DataFragmentList_travelBackward;
			ret->get_array = DataFragmentList_get_array;
			ret->add = DataFragmentList_add;
			ret->cmp = Dz1Binary_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (DataFragmentList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _DataFragmentList_clone(void *ptr, Dz1Binary *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	DataFragmentList *p = (DataFragmentList *)ptr;
	Dz1Binary *cloned = Dz1Binary_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

DataFragmentList *DataFragmentList_clone(DataFragmentList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	DataFragmentList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = DataFragmentList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(DataFragmentList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_DataFragmentList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (DataFragmentList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void DataFragmentList_purge(DataFragmentList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void DataFragmentList_del(DataFragmentList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _DataFragmentListA_dump(void *ptr, Dz1Binary *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_tprintf(tab, "entry = "); Dz1BinaryA_dump(p, tab);
	return err;
}

void DataFragmentListA_dump(DataFragmentList *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadA_tprintf(tab, "{\n"); tab++;
		p->travel(p, _DataFragmentListA_dump, (void *)&arg);
		Dz1ThreadA_tprintf(--tab, "}\n");
	}
}
static Dz1Error _DataFragmentListA_fdump(void *ptr, Dz1Binary *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadA_ftprintf(arg->fp, tab, "entry = "); Dz1BinaryA_fdump(arg->fp, p, tab);
	return err;
}

void DataFragmentListA_fdump(FILE *fp, DataFragmentList *p, int tab)
{
	if (!p) Dz1ThreadA_fprintf(fp, "NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadA_ftprintf(fp, tab, "{\n"); tab++;
		p->travel(p, _DataFragmentListA_fdump, (void *)&arg);
		Dz1ThreadA_ftprintf(fp, --tab, "}\n");
	}
}
#ifndef UNIX_SYSTEM
static Dz1Error _DataFragmentListW_dump(void *ptr, Dz1Binary *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_tprintf(tab, L"entry = "); Dz1BinaryW_dump(p, tab);
	return err;
}

void DataFragmentListW_dump(DataFragmentList *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1ThreadW_tprintf(tab, L"{\n"); tab++;
		p->travel(p, _DataFragmentListW_dump, (void *)&arg);
		Dz1ThreadW_tprintf(--tab, L"}\n");
	}
}
static Dz1Error _DataFragmentListW_fdump(void *ptr, Dz1Binary *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	FILE *fp = arg->fp;
	int tab = *(int *)arg->tab;
	Dz1ThreadW_ftprintf(arg->fp, tab, L"entry = "); Dz1BinaryW_fdump(arg->fp, p, tab);
	return err;
}

void DataFragmentListW_fdump(FILE *fp, DataFragmentList *p, int tab)
{
	if (!p) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else
	{
		Dz1ListFDumpArg2 arg = { fp,  &tab };
		Dz1ThreadW_ftprintf(fp, tab, L"{\n"); tab++;
		p->travel(p, _DataFragmentListW_fdump, (void *)&arg);
		Dz1ThreadW_ftprintf(fp, --tab, L"}\n");
	}
}
#endif // UNIX_SYSTEM
// DataFragmentList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpRXDTPDestPresent
static struct Dz1InetFtpRXDTPDestPresentMapA
{
	str_t str;
	Dz1InetFtpRXDTPDestPresent v;
} Dz1InetFtpRXDTPDestPresentMapA[] =
{
	{ (char *)"fp", Dz1InetFtpRXDTPDestPresent_fp },
	{ (char *)"list", Dz1InetFtpRXDTPDestPresent_list },
	{ NULL, Dz1InetFtpRXDTPDestPresent_max }
};

str_t Dz1InetFtpRXDTPDestPresentStrA(Dz1InetFtpRXDTPDestPresent v)
{
	struct Dz1InetFtpRXDTPDestPresentMapA *i = NULL;
	for (i = Dz1InetFtpRXDTPDestPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetFtpRXDTPDestPresent Dz1InetFtpRXDTPDestPresentFromStrA(str_t str)
{
	struct Dz1InetFtpRXDTPDestPresentMapA *i = NULL;
	for (i = Dz1InetFtpRXDTPDestPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1InetFtpRXDTPDestPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1InetFtpRXDTPDestPresentMapW
{
	wstr_t str;
	Dz1InetFtpRXDTPDestPresent v;
} Dz1InetFtpRXDTPDestPresentMapW[] =
{
	{ (wchar_t *)L"fp", Dz1InetFtpRXDTPDestPresent_fp },
	{ (wchar_t *)L"list", Dz1InetFtpRXDTPDestPresent_list },
	{ NULL, Dz1InetFtpRXDTPDestPresent_max }
};

wstr_t Dz1InetFtpRXDTPDestPresentStrW(Dz1InetFtpRXDTPDestPresent v)
{
	struct Dz1InetFtpRXDTPDestPresentMapW *i = NULL;
	for (i = Dz1InetFtpRXDTPDestPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1InetFtpRXDTPDestPresent Dz1InetFtpRXDTPDestPresentFromStrW(wstr_t str)
{
	struct Dz1InetFtpRXDTPDestPresentMapW *i = NULL;
	for (i = Dz1InetFtpRXDTPDestPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1InetFtpRXDTPDestPresent_max;
}
#endif // UNIX_SYSTEM

Dz1InetFtpRXDTPDestPresent *Dz1InetFtpRXDTPDestPresent_new(Dz1InetFtpRXDTPDestPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpRXDTPDestPresent *__internal_ret = (Dz1InetFtpRXDTPDestPresent *)Dz1Calloc(sizeof(Dz1InetFtpRXDTPDestPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1InetFtpRXDTPDestPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpRXDTPDest
Dz1InetFtpRXDTPDest *Dz1InetFtpRXDTPDest_new(Dz1InetFtpRXDTPDestPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpRXDTPDest *ret = (Dz1InetFtpRXDTPDest *)Dz1Calloc(sizeof(Dz1InetFtpRXDTPDest), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpRXDTPDest_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1InetFtpRXDTPDestPresent_fp:
			// _U_imp_clone
			if (ptr != NULL) ret->x.fp = (FILE *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetFtpRXDTPDestPresent_list:
			// _U_cst_clone
			if (ptr != NULL) ret->x.list = (DataFragmentList *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1InetFtpRXDTPDestPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpRXDTPDest_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1InetFtpRXDTPDest_purge(Dz1InetFtpRXDTPDest *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1InetFtpRXDTPDestPresent_fp:
		FILE_del(p->x.fp);
		break;
	case Dz1InetFtpRXDTPDestPresent_list:
		DataFragmentList_del(p->x.list);
		break;
	default:
		break;
	}
}

void Dz1InetFtpRXDTPDest_del(Dz1InetFtpRXDTPDest *p)
{
	if (!p) return;
	Dz1InetFtpRXDTPDest_purge(p);
	Dz1Free(p);
}

// Dz1InetFtpRXDTPDest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpRXDTPArg
Dz1InetFtpRXDTPArg *Dz1InetFtpRXDTPArg_new(void *tFTP, 
										   Dz1InetFtpDTPSpec *spec/*_ref*/, 
										   Dz1InetFtpTransfer *job/*_ref*/, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpRXDTPArg *__internal_ret = (Dz1InetFtpRXDTPArg *)Dz1Calloc(sizeof(Dz1InetFtpRXDTPArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpRXDTPArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->tFTP = tFTP;
		__internal_ret->spec = spec;
		__internal_ret->job = job;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpRXDTPArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1InetFtpRXDTPArg_purge(Dz1InetFtpRXDTPArg *p)
{
	if (p == NULL) return;
}

void Dz1InetFtpRXDTPArg_del(Dz1InetFtpRXDTPArg *p)
{
	if (p == NULL) return;
	Dz1InetFtpRXDTPArg_purge(p);
	Dz1Free(p);
}

// Dz1InetFtpRXDTPArg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1InetFtpTXDTPArg
Dz1InetFtpTXDTPArg *Dz1InetFtpTXDTPArg_new(void *tFTP, 
										   Dz1SockAddr *peer, 
										   Dz1SockAddr *local, 
										   Dz1TcpClientSocket *sock/*_ref*/, 
										   Dz1InetFtpDTPSpec *spec/*_ref*/, 
										   Dz1InetFtpTransfer *job/*_ref*/, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1InetFtpTXDTPArg *__internal_ret = (Dz1InetFtpTXDTPArg *)Dz1Calloc(sizeof(Dz1InetFtpTXDTPArg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1InetFtpTXDTPArg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->tFTP = tFTP;
		__internal_ret->peer = peer;
		__internal_ret->local = local;
		__internal_ret->sock = sock;
		__internal_ret->spec = spec;
		__internal_ret->job = job;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1InetFtpTXDTPArg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1InetFtpTXDTPArg_purge(Dz1InetFtpTXDTPArg *p)
{
	if (p == NULL) return;
	Dz1SockAddr_del(p->peer);
	Dz1SockAddr_del(p->local);
}

void Dz1InetFtpTXDTPArg_del(Dz1InetFtpTXDTPArg *p)
{
	if (p == NULL) return;
	Dz1InetFtpTXDTPArg_purge(p);
	Dz1Free(p);
}

// Dz1InetFtpTXDTPArg
////////////////////////////////////////////////////////////////////////////////


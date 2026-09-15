////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "ITSK00144_2TestMsgDef.h"

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2Reserved0
ITSK00144_2Reserved0 *ITSK00144_2Reserved0_new(u8_t reserved1, 
											   u8_t reserved2, 
											   u8_t reserved3, 
											   u8_t reserved4, 
											   u8_t reserved5, 
											   u8_t reserved6, 
											   u8_t reserved7, 
											   u8_t reserved8, 
											   u8_t reserved9, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2Reserved0 *__internal_ret = (ITSK00144_2Reserved0 *)Dz1Calloc(sizeof(ITSK00144_2Reserved0), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00144_2Reserved0_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->reserved1 = reserved1;
		__internal_ret->reserved2 = reserved2;
		__internal_ret->reserved3 = reserved3;
		__internal_ret->reserved4 = reserved4;
		__internal_ret->reserved5 = reserved5;
		__internal_ret->reserved6 = reserved6;
		__internal_ret->reserved7 = reserved7;
		__internal_ret->reserved8 = reserved8;
		__internal_ret->reserved9 = reserved9;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2Reserved0_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ITSK00144_2Reserved0_copy(ITSK00144_2Reserved0 *dst, ITSK00144_2Reserved0 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->reserved1 = src->reserved1;
		dst->reserved2 = src->reserved2;
		dst->reserved3 = src->reserved3;
		dst->reserved4 = src->reserved4;
		dst->reserved5 = src->reserved5;
		dst->reserved6 = src->reserved6;
		dst->reserved7 = src->reserved7;
		dst->reserved8 = src->reserved8;
		dst->reserved9 = src->reserved9;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ITSK00144_2Reserved0 *ITSK00144_2Reserved0_clone(ITSK00144_2Reserved0 *src, Dz1Error *err)
{
	ITSK00144_2Reserved0 *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ITSK00144_2Reserved0 *)Dz1Calloc(sizeof(ITSK00144_2Reserved0), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ITSK00144_2Reserved0_delAndSetNull, (void *)&dst);
		if (ITSK00144_2Reserved0_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2Reserved0_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ITSK00144_2Reserved0_purge(ITSK00144_2Reserved0 *p)
{
	if (p == NULL) return;
}

void ITSK00144_2Reserved0_del(ITSK00144_2Reserved0 *p)
{
	if (p == NULL) return;
	ITSK00144_2Reserved0_purge(p);
	Dz1Free(p);
}

void ITSK00144_2Reserved0_dump(ITSK00144_2Reserved0 *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("reserved1 = ")); Dz1u8_dump(&p->reserved1, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reserved2 = ")); Dz1u8_dump(&p->reserved2, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reserved3 = ")); Dz1u8_dump(&p->reserved3, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reserved4 = ")); Dz1u8_dump(&p->reserved4, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reserved5 = ")); Dz1u8_dump(&p->reserved5, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reserved6 = ")); Dz1u8_dump(&p->reserved6, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reserved7 = ")); Dz1u8_dump(&p->reserved7, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reserved8 = ")); Dz1u8_dump(&p->reserved8, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reserved9 = ")); Dz1u8_dump(&p->reserved9, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ITSK00144_2Reserved0
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2Reserved18
ITSK00144_2Reserved18 *ITSK00144_2Reserved18_new(u8_t reserved1, 
												 u8_t reserved2, 
												 u8_t reserved3, 
												 u8_t reserved4, 
												 u8_t reserved5, 
												 u8_t reserved6, 
												 u8_t reserved7, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2Reserved18 *__internal_ret = (ITSK00144_2Reserved18 *)Dz1Calloc(sizeof(ITSK00144_2Reserved18), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00144_2Reserved18_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->reserved1 = reserved1;
		__internal_ret->reserved2 = reserved2;
		__internal_ret->reserved3 = reserved3;
		__internal_ret->reserved4 = reserved4;
		__internal_ret->reserved5 = reserved5;
		__internal_ret->reserved6 = reserved6;
		__internal_ret->reserved7 = reserved7;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2Reserved18_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ITSK00144_2Reserved18_copy(ITSK00144_2Reserved18 *dst, ITSK00144_2Reserved18 *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->reserved1 = src->reserved1;
		dst->reserved2 = src->reserved2;
		dst->reserved3 = src->reserved3;
		dst->reserved4 = src->reserved4;
		dst->reserved5 = src->reserved5;
		dst->reserved6 = src->reserved6;
		dst->reserved7 = src->reserved7;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ITSK00144_2Reserved18 *ITSK00144_2Reserved18_clone(ITSK00144_2Reserved18 *src, Dz1Error *err)
{
	ITSK00144_2Reserved18 *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ITSK00144_2Reserved18 *)Dz1Calloc(sizeof(ITSK00144_2Reserved18), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ITSK00144_2Reserved18_delAndSetNull, (void *)&dst);
		if (ITSK00144_2Reserved18_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2Reserved18_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ITSK00144_2Reserved18_purge(ITSK00144_2Reserved18 *p)
{
	if (p == NULL) return;
}

void ITSK00144_2Reserved18_del(ITSK00144_2Reserved18 *p)
{
	if (p == NULL) return;
	ITSK00144_2Reserved18_purge(p);
	Dz1Free(p);
}

void ITSK00144_2Reserved18_dump(ITSK00144_2Reserved18 *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("reserved1 = ")); Dz1u8_dump(&p->reserved1, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reserved2 = ")); Dz1u8_dump(&p->reserved2, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reserved3 = ")); Dz1u8_dump(&p->reserved3, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reserved4 = ")); Dz1u8_dump(&p->reserved4, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reserved5 = ")); Dz1u8_dump(&p->reserved5, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reserved6 = ")); Dz1u8_dump(&p->reserved6, tab); 
		Dz1Thread_tprintf(tab, Dz1T("reserved7 = ")); Dz1u8_dump(&p->reserved7, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ITSK00144_2Reserved18
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// I2XTrafficSafetyDeviceSerialNo
I2XTrafficSafetyDeviceSerialNo *I2XTrafficSafetyDeviceSerialNo_new(u8_t type, 
																   u32_t id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	I2XTrafficSafetyDeviceSerialNo *__internal_ret = (I2XTrafficSafetyDeviceSerialNo *)Dz1Calloc(sizeof(I2XTrafficSafetyDeviceSerialNo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(I2XTrafficSafetyDeviceSerialNo_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->type = type;
		__internal_ret->id = id;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (I2XTrafficSafetyDeviceSerialNo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t I2XTrafficSafetyDeviceSerialNo_copy(I2XTrafficSafetyDeviceSerialNo *dst, I2XTrafficSafetyDeviceSerialNo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->type = src->type;
		dst->id = src->id;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

I2XTrafficSafetyDeviceSerialNo *I2XTrafficSafetyDeviceSerialNo_clone(I2XTrafficSafetyDeviceSerialNo *src, Dz1Error *err)
{
	I2XTrafficSafetyDeviceSerialNo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (I2XTrafficSafetyDeviceSerialNo *)Dz1Calloc(sizeof(I2XTrafficSafetyDeviceSerialNo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(I2XTrafficSafetyDeviceSerialNo_delAndSetNull, (void *)&dst);
		if (I2XTrafficSafetyDeviceSerialNo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (I2XTrafficSafetyDeviceSerialNo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void I2XTrafficSafetyDeviceSerialNo_purge(I2XTrafficSafetyDeviceSerialNo *p)
{
	if (p == NULL) return;
}

void I2XTrafficSafetyDeviceSerialNo_del(I2XTrafficSafetyDeviceSerialNo *p)
{
	if (p == NULL) return;
	I2XTrafficSafetyDeviceSerialNo_purge(p);
	Dz1Free(p);
}

void I2XTrafficSafetyDeviceSerialNo_dump(I2XTrafficSafetyDeviceSerialNo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("type = ")); Dz1u8_dump(&p->type, tab); 
		Dz1Thread_tprintf(tab, Dz1T("id = ")); Dz1u32_dump(&p->id, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// I2XTrafficSafetyDeviceSerialNo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// I2XTrafficSafetyDeviceSerialNoList
static Dz1Error I2XTrafficSafetyDeviceSerialNoList_add(I2XTrafficSafetyDeviceSerialNoList *p, I2XTrafficSafetyDeviceSerialNo *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static I2XTrafficSafetyDeviceSerialNo *I2XTrafficSafetyDeviceSerialNoList_extract(I2XTrafficSafetyDeviceSerialNoList *p, I2XTrafficSafetyDeviceSerialNo *ptr)
{
	return (I2XTrafficSafetyDeviceSerialNo *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct I2XTrafficSafetyDeviceSerialNoListMkArrArg
{
	I2XTrafficSafetyDeviceSerialNo **arr;
	unsigned int idx;
} I2XTrafficSafetyDeviceSerialNoListMkArrArg;

static Dz1Error _I2XTrafficSafetyDeviceSerialNoList_get_array(void *ptr, I2XTrafficSafetyDeviceSerialNo *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	I2XTrafficSafetyDeviceSerialNoListMkArrArg *arg = (I2XTrafficSafetyDeviceSerialNoListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static I2XTrafficSafetyDeviceSerialNo **I2XTrafficSafetyDeviceSerialNoList_get_array(I2XTrafficSafetyDeviceSerialNoList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	I2XTrafficSafetyDeviceSerialNo **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (I2XTrafficSafetyDeviceSerialNo **)Dz1Calloc(sizeof(I2XTrafficSafetyDeviceSerialNo *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		I2XTrafficSafetyDeviceSerialNoListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _I2XTrafficSafetyDeviceSerialNoList_get_array, (void *)&arg);
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

static Dz1Error I2XTrafficSafetyDeviceSerialNoList_travelForward(I2XTrafficSafetyDeviceSerialNoList *p, Dz1Error (*func)(void *ptr, I2XTrafficSafetyDeviceSerialNo *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error I2XTrafficSafetyDeviceSerialNoList_travelBackward(I2XTrafficSafetyDeviceSerialNoList *p, Dz1Error (*func)(void *ptr, I2XTrafficSafetyDeviceSerialNo *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static I2XTrafficSafetyDeviceSerialNo *I2XTrafficSafetyDeviceSerialNoList_getHead(I2XTrafficSafetyDeviceSerialNoList *p)
{
	return (I2XTrafficSafetyDeviceSerialNo *)Dz1Fifo_getFirst(p->storage);
}

static unsigned int I2XTrafficSafetyDeviceSerialNoList_count(I2XTrafficSafetyDeviceSerialNoList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

I2XTrafficSafetyDeviceSerialNoList *I2XTrafficSafetyDeviceSerialNoList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	I2XTrafficSafetyDeviceSerialNoList *ret = (I2XTrafficSafetyDeviceSerialNoList *)Dz1Calloc(sizeof(I2XTrafficSafetyDeviceSerialNoList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(I2XTrafficSafetyDeviceSerialNoList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)I2XTrafficSafetyDeviceSerialNo_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = I2XTrafficSafetyDeviceSerialNoList_count;
			ret->travel = I2XTrafficSafetyDeviceSerialNoList_travelForward;
			ret->travelForward = I2XTrafficSafetyDeviceSerialNoList_travelForward;
			ret->travelBackward = I2XTrafficSafetyDeviceSerialNoList_travelBackward;
			ret->get_array = I2XTrafficSafetyDeviceSerialNoList_get_array;
			ret->add = I2XTrafficSafetyDeviceSerialNoList_add;
			ret->extract = I2XTrafficSafetyDeviceSerialNoList_extract;
			ret->getHead = I2XTrafficSafetyDeviceSerialNoList_getHead;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (I2XTrafficSafetyDeviceSerialNoList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _I2XTrafficSafetyDeviceSerialNoList_clone(void *ptr, I2XTrafficSafetyDeviceSerialNo *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	I2XTrafficSafetyDeviceSerialNoList *p = (I2XTrafficSafetyDeviceSerialNoList *)ptr;
	I2XTrafficSafetyDeviceSerialNo *cloned = I2XTrafficSafetyDeviceSerialNo_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

I2XTrafficSafetyDeviceSerialNoList *I2XTrafficSafetyDeviceSerialNoList_clone(I2XTrafficSafetyDeviceSerialNoList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	I2XTrafficSafetyDeviceSerialNoList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = I2XTrafficSafetyDeviceSerialNoList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(I2XTrafficSafetyDeviceSerialNoList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_I2XTrafficSafetyDeviceSerialNoList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (I2XTrafficSafetyDeviceSerialNoList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void I2XTrafficSafetyDeviceSerialNoList_purge(I2XTrafficSafetyDeviceSerialNoList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void I2XTrafficSafetyDeviceSerialNoList_del(I2XTrafficSafetyDeviceSerialNoList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _I2XTrafficSafetyDeviceSerialNoList_dump(void *ptr, I2XTrafficSafetyDeviceSerialNo *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); I2XTrafficSafetyDeviceSerialNo_dump(p, tab);
	return err;
}

void I2XTrafficSafetyDeviceSerialNoList_dump(I2XTrafficSafetyDeviceSerialNoList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _I2XTrafficSafetyDeviceSerialNoList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// I2XTrafficSafetyDeviceSerialNoList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// I2XTrafficSafetyDeviceList
I2XTrafficSafetyDeviceList *I2XTrafficSafetyDeviceList_new(u16_t cnt, 
														   I2XTrafficSafetyDeviceSerialNoList *id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	I2XTrafficSafetyDeviceList *__internal_ret = (I2XTrafficSafetyDeviceList *)Dz1Calloc(sizeof(I2XTrafficSafetyDeviceList), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(I2XTrafficSafetyDeviceList_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->cnt = cnt;
		__internal_ret->id = id;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (I2XTrafficSafetyDeviceList_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t I2XTrafficSafetyDeviceList_copy(I2XTrafficSafetyDeviceList *dst, I2XTrafficSafetyDeviceList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->id && (dst->id = I2XTrafficSafetyDeviceSerialNoList_clone(src->id, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->cnt = src->cnt;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

I2XTrafficSafetyDeviceList *I2XTrafficSafetyDeviceList_clone(I2XTrafficSafetyDeviceList *src, Dz1Error *err)
{
	I2XTrafficSafetyDeviceList *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (I2XTrafficSafetyDeviceList *)Dz1Calloc(sizeof(I2XTrafficSafetyDeviceList), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(I2XTrafficSafetyDeviceList_delAndSetNull, (void *)&dst);
		if (I2XTrafficSafetyDeviceList_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (I2XTrafficSafetyDeviceList_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void I2XTrafficSafetyDeviceList_purge(I2XTrafficSafetyDeviceList *p)
{
	if (p == NULL) return;
	I2XTrafficSafetyDeviceSerialNoList_del(p->id);
}

void I2XTrafficSafetyDeviceList_del(I2XTrafficSafetyDeviceList *p)
{
	if (p == NULL) return;
	I2XTrafficSafetyDeviceList_purge(p);
	Dz1Free(p);
}

void I2XTrafficSafetyDeviceList_dump(I2XTrafficSafetyDeviceList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("cnt = ")); Dz1u16_dump(&p->cnt, tab); 
		Dz1Thread_tprintf(tab, Dz1T("id = ")); I2XTrafficSafetyDeviceSerialNoList_dump(p->id, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// I2XTrafficSafetyDeviceList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// I2XTrafficSafetyDeviceLinkUnitStatus
I2XTrafficSafetyDeviceLinkUnitStatus *I2XTrafficSafetyDeviceLinkUnitStatus_new(bool_t isActive, 
																			   bool_t control_comm, 
																			   bool_t wave_comm, 
																			   u8_t temperature, 
																			   u8_t humidity, 
																			   bool_t isOpen, 
																			   bool_t isFanOn, 
																			   bool_t isHeaterOn, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	I2XTrafficSafetyDeviceLinkUnitStatus *__internal_ret = (I2XTrafficSafetyDeviceLinkUnitStatus *)Dz1Calloc(sizeof(I2XTrafficSafetyDeviceLinkUnitStatus), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(I2XTrafficSafetyDeviceLinkUnitStatus_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->isActive = isActive;
		__internal_ret->control_comm = control_comm;
		__internal_ret->wave_comm = wave_comm;
		__internal_ret->temperature = temperature;
		__internal_ret->humidity = humidity;
		__internal_ret->isOpen = isOpen;
		__internal_ret->isFanOn = isFanOn;
		__internal_ret->isHeaterOn = isHeaterOn;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (I2XTrafficSafetyDeviceLinkUnitStatus_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t I2XTrafficSafetyDeviceLinkUnitStatus_copy(I2XTrafficSafetyDeviceLinkUnitStatus *dst, I2XTrafficSafetyDeviceLinkUnitStatus *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->isActive = src->isActive;
		dst->control_comm = src->control_comm;
		dst->wave_comm = src->wave_comm;
		dst->temperature = src->temperature;
		dst->humidity = src->humidity;
		dst->isOpen = src->isOpen;
		dst->isFanOn = src->isFanOn;
		dst->isHeaterOn = src->isHeaterOn;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

I2XTrafficSafetyDeviceLinkUnitStatus *I2XTrafficSafetyDeviceLinkUnitStatus_clone(I2XTrafficSafetyDeviceLinkUnitStatus *src, Dz1Error *err)
{
	I2XTrafficSafetyDeviceLinkUnitStatus *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (I2XTrafficSafetyDeviceLinkUnitStatus *)Dz1Calloc(sizeof(I2XTrafficSafetyDeviceLinkUnitStatus), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(I2XTrafficSafetyDeviceLinkUnitStatus_delAndSetNull, (void *)&dst);
		if (I2XTrafficSafetyDeviceLinkUnitStatus_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (I2XTrafficSafetyDeviceLinkUnitStatus_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void I2XTrafficSafetyDeviceLinkUnitStatus_purge(I2XTrafficSafetyDeviceLinkUnitStatus *p)
{
	if (p == NULL) return;
}

void I2XTrafficSafetyDeviceLinkUnitStatus_del(I2XTrafficSafetyDeviceLinkUnitStatus *p)
{
	if (p == NULL) return;
	I2XTrafficSafetyDeviceLinkUnitStatus_purge(p);
	Dz1Free(p);
}

void I2XTrafficSafetyDeviceLinkUnitStatus_dump(I2XTrafficSafetyDeviceLinkUnitStatus *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("isActive = ")); Dz1Bool_dump(&p->isActive, tab); 
		Dz1Thread_tprintf(tab, Dz1T("control_comm = ")); Dz1Bool_dump(&p->control_comm, tab); 
		Dz1Thread_tprintf(tab, Dz1T("wave_comm = ")); Dz1Bool_dump(&p->wave_comm, tab); 
		Dz1Thread_tprintf(tab, Dz1T("temperature = ")); Dz1u8_dump(&p->temperature, tab); 
		Dz1Thread_tprintf(tab, Dz1T("humidity = ")); Dz1u8_dump(&p->humidity, tab); 
		Dz1Thread_tprintf(tab, Dz1T("isOpen = ")); Dz1Bool_dump(&p->isOpen, tab); 
		Dz1Thread_tprintf(tab, Dz1T("isFanOn = ")); Dz1Bool_dump(&p->isFanOn, tab); 
		Dz1Thread_tprintf(tab, Dz1T("isHeaterOn = ")); Dz1Bool_dump(&p->isHeaterOn, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// I2XTrafficSafetyDeviceLinkUnitStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// I2XTrafficSafetyDeviceStatus
I2XTrafficSafetyDeviceStatus *I2XTrafficSafetyDeviceStatus_new(I2XTrafficSafetyDeviceSerialNo *id, 
															   bool_t isActive, 
															   bool_t isBatteryOn, 
															   bool_t isPowered, 
															   bool_t isPowerOn, 
															   bool_t isConnected, 
															   u8_t cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	I2XTrafficSafetyDeviceStatus *__internal_ret = (I2XTrafficSafetyDeviceStatus *)Dz1Calloc(sizeof(I2XTrafficSafetyDeviceStatus), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(I2XTrafficSafetyDeviceStatus_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->id = id;
		__internal_ret->isActive = isActive;
		__internal_ret->isBatteryOn = isBatteryOn;
		__internal_ret->isPowered = isPowered;
		__internal_ret->isPowerOn = isPowerOn;
		__internal_ret->isConnected = isConnected;
		__internal_ret->cnt = cnt;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (I2XTrafficSafetyDeviceStatus_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t I2XTrafficSafetyDeviceStatus_copy(I2XTrafficSafetyDeviceStatus *dst, I2XTrafficSafetyDeviceStatus *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->id && (dst->id = I2XTrafficSafetyDeviceSerialNo_clone(src->id, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->isActive = src->isActive;
		dst->isBatteryOn = src->isBatteryOn;
		dst->isPowered = src->isPowered;
		dst->isPowerOn = src->isPowerOn;
		dst->isConnected = src->isConnected;
		dst->cnt = src->cnt;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

I2XTrafficSafetyDeviceStatus *I2XTrafficSafetyDeviceStatus_clone(I2XTrafficSafetyDeviceStatus *src, Dz1Error *err)
{
	I2XTrafficSafetyDeviceStatus *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (I2XTrafficSafetyDeviceStatus *)Dz1Calloc(sizeof(I2XTrafficSafetyDeviceStatus), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(I2XTrafficSafetyDeviceStatus_delAndSetNull, (void *)&dst);
		if (I2XTrafficSafetyDeviceStatus_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (I2XTrafficSafetyDeviceStatus_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void I2XTrafficSafetyDeviceStatus_purge(I2XTrafficSafetyDeviceStatus *p)
{
	if (p == NULL) return;
	I2XTrafficSafetyDeviceSerialNo_del(p->id);
}

void I2XTrafficSafetyDeviceStatus_del(I2XTrafficSafetyDeviceStatus *p)
{
	if (p == NULL) return;
	I2XTrafficSafetyDeviceStatus_purge(p);
	Dz1Free(p);
}

void I2XTrafficSafetyDeviceStatus_dump(I2XTrafficSafetyDeviceStatus *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("id = ")); I2XTrafficSafetyDeviceSerialNo_dump(p->id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("isActive = ")); Dz1Bool_dump(&p->isActive, tab); 
		Dz1Thread_tprintf(tab, Dz1T("isBatteryOn = ")); Dz1Bool_dump(&p->isBatteryOn, tab); 
		Dz1Thread_tprintf(tab, Dz1T("isPowered = ")); Dz1Bool_dump(&p->isPowered, tab); 
		Dz1Thread_tprintf(tab, Dz1T("isPowerOn = ")); Dz1Bool_dump(&p->isPowerOn, tab); 
		Dz1Thread_tprintf(tab, Dz1T("isConnected = ")); Dz1Bool_dump(&p->isConnected, tab); 
		Dz1Thread_tprintf(tab, Dz1T("cnt = ")); Dz1u8_dump(&p->cnt, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// I2XTrafficSafetyDeviceStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// I2XTrafficSafetyDeviceStatusList
static Dz1Error I2XTrafficSafetyDeviceStatusList_add(I2XTrafficSafetyDeviceStatusList *p, I2XTrafficSafetyDeviceStatus *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static I2XTrafficSafetyDeviceStatus *I2XTrafficSafetyDeviceStatusList_extract(I2XTrafficSafetyDeviceStatusList *p, I2XTrafficSafetyDeviceStatus *ptr)
{
	return (I2XTrafficSafetyDeviceStatus *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct I2XTrafficSafetyDeviceStatusListMkArrArg
{
	I2XTrafficSafetyDeviceStatus **arr;
	unsigned int idx;
} I2XTrafficSafetyDeviceStatusListMkArrArg;

static Dz1Error _I2XTrafficSafetyDeviceStatusList_get_array(void *ptr, I2XTrafficSafetyDeviceStatus *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	I2XTrafficSafetyDeviceStatusListMkArrArg *arg = (I2XTrafficSafetyDeviceStatusListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static I2XTrafficSafetyDeviceStatus **I2XTrafficSafetyDeviceStatusList_get_array(I2XTrafficSafetyDeviceStatusList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	I2XTrafficSafetyDeviceStatus **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (I2XTrafficSafetyDeviceStatus **)Dz1Calloc(sizeof(I2XTrafficSafetyDeviceStatus *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		I2XTrafficSafetyDeviceStatusListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _I2XTrafficSafetyDeviceStatusList_get_array, (void *)&arg);
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

static Dz1Error I2XTrafficSafetyDeviceStatusList_travelForward(I2XTrafficSafetyDeviceStatusList *p, Dz1Error (*func)(void *ptr, I2XTrafficSafetyDeviceStatus *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error I2XTrafficSafetyDeviceStatusList_travelBackward(I2XTrafficSafetyDeviceStatusList *p, Dz1Error (*func)(void *ptr, I2XTrafficSafetyDeviceStatus *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static I2XTrafficSafetyDeviceStatus *I2XTrafficSafetyDeviceStatusList_getHead(I2XTrafficSafetyDeviceStatusList *p)
{
	return (I2XTrafficSafetyDeviceStatus *)Dz1Fifo_getFirst(p->storage);
}

static unsigned int I2XTrafficSafetyDeviceStatusList_count(I2XTrafficSafetyDeviceStatusList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

I2XTrafficSafetyDeviceStatusList *I2XTrafficSafetyDeviceStatusList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	I2XTrafficSafetyDeviceStatusList *ret = (I2XTrafficSafetyDeviceStatusList *)Dz1Calloc(sizeof(I2XTrafficSafetyDeviceStatusList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(I2XTrafficSafetyDeviceStatusList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)I2XTrafficSafetyDeviceStatus_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = I2XTrafficSafetyDeviceStatusList_count;
			ret->travel = I2XTrafficSafetyDeviceStatusList_travelForward;
			ret->travelForward = I2XTrafficSafetyDeviceStatusList_travelForward;
			ret->travelBackward = I2XTrafficSafetyDeviceStatusList_travelBackward;
			ret->get_array = I2XTrafficSafetyDeviceStatusList_get_array;
			ret->add = I2XTrafficSafetyDeviceStatusList_add;
			ret->extract = I2XTrafficSafetyDeviceStatusList_extract;
			ret->getHead = I2XTrafficSafetyDeviceStatusList_getHead;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (I2XTrafficSafetyDeviceStatusList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _I2XTrafficSafetyDeviceStatusList_clone(void *ptr, I2XTrafficSafetyDeviceStatus *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	I2XTrafficSafetyDeviceStatusList *p = (I2XTrafficSafetyDeviceStatusList *)ptr;
	I2XTrafficSafetyDeviceStatus *cloned = I2XTrafficSafetyDeviceStatus_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

I2XTrafficSafetyDeviceStatusList *I2XTrafficSafetyDeviceStatusList_clone(I2XTrafficSafetyDeviceStatusList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	I2XTrafficSafetyDeviceStatusList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = I2XTrafficSafetyDeviceStatusList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(I2XTrafficSafetyDeviceStatusList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_I2XTrafficSafetyDeviceStatusList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (I2XTrafficSafetyDeviceStatusList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void I2XTrafficSafetyDeviceStatusList_purge(I2XTrafficSafetyDeviceStatusList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void I2XTrafficSafetyDeviceStatusList_del(I2XTrafficSafetyDeviceStatusList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _I2XTrafficSafetyDeviceStatusList_dump(void *ptr, I2XTrafficSafetyDeviceStatus *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); I2XTrafficSafetyDeviceStatus_dump(p, tab);
	return err;
}

void I2XTrafficSafetyDeviceStatusList_dump(I2XTrafficSafetyDeviceStatusList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _I2XTrafficSafetyDeviceStatusList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// I2XTrafficSafetyDeviceStatusList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// I2XTrafficSafetyDeviceStatusInfo
I2XTrafficSafetyDeviceStatusInfo *I2XTrafficSafetyDeviceStatusInfo_new(u16_t num, 
																	   I2XTrafficSafetyDeviceStatusList *status, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	I2XTrafficSafetyDeviceStatusInfo *__internal_ret = (I2XTrafficSafetyDeviceStatusInfo *)Dz1Calloc(sizeof(I2XTrafficSafetyDeviceStatusInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(I2XTrafficSafetyDeviceStatusInfo_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->num = num;
		__internal_ret->status = status;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (I2XTrafficSafetyDeviceStatusInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t I2XTrafficSafetyDeviceStatusInfo_copy(I2XTrafficSafetyDeviceStatusInfo *dst, I2XTrafficSafetyDeviceStatusInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->status && (dst->status = I2XTrafficSafetyDeviceStatusList_clone(src->status, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->num = src->num;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

I2XTrafficSafetyDeviceStatusInfo *I2XTrafficSafetyDeviceStatusInfo_clone(I2XTrafficSafetyDeviceStatusInfo *src, Dz1Error *err)
{
	I2XTrafficSafetyDeviceStatusInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (I2XTrafficSafetyDeviceStatusInfo *)Dz1Calloc(sizeof(I2XTrafficSafetyDeviceStatusInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(I2XTrafficSafetyDeviceStatusInfo_delAndSetNull, (void *)&dst);
		if (I2XTrafficSafetyDeviceStatusInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (I2XTrafficSafetyDeviceStatusInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void I2XTrafficSafetyDeviceStatusInfo_purge(I2XTrafficSafetyDeviceStatusInfo *p)
{
	if (p == NULL) return;
	I2XTrafficSafetyDeviceStatusList_del(p->status);
}

void I2XTrafficSafetyDeviceStatusInfo_del(I2XTrafficSafetyDeviceStatusInfo *p)
{
	if (p == NULL) return;
	I2XTrafficSafetyDeviceStatusInfo_purge(p);
	Dz1Free(p);
}

void I2XTrafficSafetyDeviceStatusInfo_dump(I2XTrafficSafetyDeviceStatusInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("num = ")); Dz1u16_dump(&p->num, tab); 
		Dz1Thread_tprintf(tab, Dz1T("status = ")); I2XTrafficSafetyDeviceStatusList_dump(p->status, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// I2XTrafficSafetyDeviceStatusInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2DataPresent
static struct ITSK00144_2DataPresentMapA
{
	str_t str;
	ITSK00144_2DataPresent v;
} ITSK00144_2DataPresentMapA[] =
{
	{ (char *)"req_link_unit_status", ITSK00144_2DataPresent_req_link_unit_status },
	{ (char *)"rsp_link_unit_status", ITSK00144_2DataPresent_rsp_link_unit_status },
	{ (char *)"req_status", ITSK00144_2DataPresent_req_status },
	{ (char *)"rsp_status", ITSK00144_2DataPresent_rsp_status },
	{ (char *)"req_list", ITSK00144_2DataPresent_req_list },
	{ (char *)"rsp_list", ITSK00144_2DataPresent_rsp_list },
	{ (char *)"req_update_list", ITSK00144_2DataPresent_req_update_list },
	{ (char *)"rsp_update_list", ITSK00144_2DataPresent_rsp_update_list },
	{ (char *)"reset", ITSK00144_2DataPresent_reset },
	{ (char *)"hb", ITSK00144_2DataPresent_hb },
	{ (char *)"ack", ITSK00144_2DataPresent_ack },
	{ (char *)"nack", ITSK00144_2DataPresent_nack },
	{ NULL, ITSK00144_2DataPresent_max }
};

str_t ITSK00144_2DataPresentStrA(ITSK00144_2DataPresent v)
{
	struct ITSK00144_2DataPresentMapA *i = NULL;
	for (i = ITSK00144_2DataPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ITSK00144_2DataPresent ITSK00144_2DataPresentFromStrA(str_t str)
{
	struct ITSK00144_2DataPresentMapA *i = NULL;
	for (i = ITSK00144_2DataPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ITSK00144_2DataPresent_max;
}
#ifndef UNIX_SYSTEM
static struct ITSK00144_2DataPresentMapW
{
	wstr_t str;
	ITSK00144_2DataPresent v;
} ITSK00144_2DataPresentMapW[] =
{
	{ (wchar_t *)L"req_link_unit_status", ITSK00144_2DataPresent_req_link_unit_status },
	{ (wchar_t *)L"rsp_link_unit_status", ITSK00144_2DataPresent_rsp_link_unit_status },
	{ (wchar_t *)L"req_status", ITSK00144_2DataPresent_req_status },
	{ (wchar_t *)L"rsp_status", ITSK00144_2DataPresent_rsp_status },
	{ (wchar_t *)L"req_list", ITSK00144_2DataPresent_req_list },
	{ (wchar_t *)L"rsp_list", ITSK00144_2DataPresent_rsp_list },
	{ (wchar_t *)L"req_update_list", ITSK00144_2DataPresent_req_update_list },
	{ (wchar_t *)L"rsp_update_list", ITSK00144_2DataPresent_rsp_update_list },
	{ (wchar_t *)L"reset", ITSK00144_2DataPresent_reset },
	{ (wchar_t *)L"hb", ITSK00144_2DataPresent_hb },
	{ (wchar_t *)L"ack", ITSK00144_2DataPresent_ack },
	{ (wchar_t *)L"nack", ITSK00144_2DataPresent_nack },
	{ NULL, ITSK00144_2DataPresent_max }
};

wstr_t ITSK00144_2DataPresentStrW(ITSK00144_2DataPresent v)
{
	struct ITSK00144_2DataPresentMapW *i = NULL;
	for (i = ITSK00144_2DataPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ITSK00144_2DataPresent ITSK00144_2DataPresentFromStrW(wstr_t str)
{
	struct ITSK00144_2DataPresentMapW *i = NULL;
	for (i = ITSK00144_2DataPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ITSK00144_2DataPresent_max;
}
#endif // UNIX_SYSTEM

ITSK00144_2DataPresent *ITSK00144_2DataPresent_new(ITSK00144_2DataPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2DataPresent *__internal_ret = (ITSK00144_2DataPresent *)Dz1Calloc(sizeof(ITSK00144_2DataPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void ITSK00144_2DataPresent_dump(ITSK00144_2DataPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), ITSK00144_2DataPresentStr(*v));
}
// ITSK00144_2DataPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2Data
ITSK00144_2Data *ITSK00144_2Data_new(ITSK00144_2DataPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2Data *ret = (ITSK00144_2Data *)Dz1Calloc(sizeof(ITSK00144_2Data), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00144_2Data_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case ITSK00144_2DataPresent_req_link_unit_status:
			// _U_cst_clone
			if (ptr != NULL) ret->x.req_link_unit_status = (ITSK00144_2Reserved0 *)ptr;
			ERR_CLEAR(errp);
			break;
		case ITSK00144_2DataPresent_rsp_link_unit_status:
			// _U_cst_clone
			if (ptr != NULL) ret->x.rsp_link_unit_status = (I2XTrafficSafetyDeviceLinkUnitStatus *)ptr;
			ERR_CLEAR(errp);
			break;
		case ITSK00144_2DataPresent_req_status:
			// _U_cst_clone
			if (ptr != NULL) ret->x.req_status = (ITSK00144_2Reserved0 *)ptr;
			ERR_CLEAR(errp);
			break;
		case ITSK00144_2DataPresent_rsp_status:
			// _U_cst_clone
			if (ptr != NULL) ret->x.rsp_status = (I2XTrafficSafetyDeviceStatusInfo *)ptr;
			ERR_CLEAR(errp);
			break;
		case ITSK00144_2DataPresent_req_list:
			// _U_cst_clone
			if (ptr != NULL) ret->x.req_list = (ITSK00144_2Reserved0 *)ptr;
			ERR_CLEAR(errp);
			break;
		case ITSK00144_2DataPresent_rsp_list:
			// _U_cst_clone
			if (ptr != NULL) ret->x.rsp_list = (I2XTrafficSafetyDeviceList *)ptr;
			ERR_CLEAR(errp);
			break;
		case ITSK00144_2DataPresent_req_update_list:
			// _U_cst_clone
			if (ptr != NULL) ret->x.req_update_list = (I2XTrafficSafetyDeviceList *)ptr;
			ERR_CLEAR(errp);
			break;
		case ITSK00144_2DataPresent_rsp_update_list:
			// _U_cst_clone
			if (ptr != NULL) ret->x.rsp_update_list = (I2XTrafficSafetyDeviceList *)ptr;
			ERR_CLEAR(errp);
			break;
		case ITSK00144_2DataPresent_reset:
			// _U_cst_clone
			if (ptr != NULL) ret->x.reset = (ITSK00144_2Reserved0 *)ptr;
			ERR_CLEAR(errp);
			break;
		case ITSK00144_2DataPresent_hb:
			// _U_cst_clone
			if (ptr != NULL) ret->x.hb = (ITSK00144_2Reserved0 *)ptr;
			ERR_CLEAR(errp);
			break;
		case ITSK00144_2DataPresent_ack:
			// _U_cst_clone
			if (ptr != NULL) ret->x.ack = (ITSK00144_2Reserved0 *)ptr;
			ERR_CLEAR(errp);
			break;
		case ITSK00144_2DataPresent_nack:
			// _U_cst_clone
			if (ptr != NULL) ret->x.nack = (ITSK00144_2Reserved0 *)ptr;
			ERR_CLEAR(errp);
			break;
		case ITSK00144_2DataPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2Data_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t ITSK00144_2Data_copy(ITSK00144_2Data *ret, ITSK00144_2Data *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case ITSK00144_2DataPresent_req_link_unit_status:
			// _U_cst_clone
			if (src->x.req_link_unit_status && (ret->x.req_link_unit_status = ITSK00144_2Reserved0_clone(src->x.req_link_unit_status, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case ITSK00144_2DataPresent_rsp_link_unit_status:
			// _U_cst_clone
			if (src->x.rsp_link_unit_status && (ret->x.rsp_link_unit_status = I2XTrafficSafetyDeviceLinkUnitStatus_clone(src->x.rsp_link_unit_status, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case ITSK00144_2DataPresent_req_status:
			// _U_cst_clone
			if (src->x.req_status && (ret->x.req_status = ITSK00144_2Reserved0_clone(src->x.req_status, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case ITSK00144_2DataPresent_rsp_status:
			// _U_cst_clone
			if (src->x.rsp_status && (ret->x.rsp_status = I2XTrafficSafetyDeviceStatusInfo_clone(src->x.rsp_status, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case ITSK00144_2DataPresent_req_list:
			// _U_cst_clone
			if (src->x.req_list && (ret->x.req_list = ITSK00144_2Reserved0_clone(src->x.req_list, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case ITSK00144_2DataPresent_rsp_list:
			// _U_cst_clone
			if (src->x.rsp_list && (ret->x.rsp_list = I2XTrafficSafetyDeviceList_clone(src->x.rsp_list, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case ITSK00144_2DataPresent_req_update_list:
			// _U_cst_clone
			if (src->x.req_update_list && (ret->x.req_update_list = I2XTrafficSafetyDeviceList_clone(src->x.req_update_list, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case ITSK00144_2DataPresent_rsp_update_list:
			// _U_cst_clone
			if (src->x.rsp_update_list && (ret->x.rsp_update_list = I2XTrafficSafetyDeviceList_clone(src->x.rsp_update_list, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case ITSK00144_2DataPresent_reset:
			// _U_cst_clone
			if (src->x.reset && (ret->x.reset = ITSK00144_2Reserved0_clone(src->x.reset, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case ITSK00144_2DataPresent_hb:
			// _U_cst_clone
			if (src->x.hb && (ret->x.hb = ITSK00144_2Reserved0_clone(src->x.hb, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case ITSK00144_2DataPresent_ack:
			// _U_cst_clone
			if (src->x.ack && (ret->x.ack = ITSK00144_2Reserved0_clone(src->x.ack, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case ITSK00144_2DataPresent_nack:
			// _U_cst_clone
			if (src->x.nack && (ret->x.nack = ITSK00144_2Reserved0_clone(src->x.nack, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ITSK00144_2Data *ITSK00144_2Data_clone(ITSK00144_2Data *src, Dz1Error *err)
{
	ITSK00144_2Data *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (ITSK00144_2Data *)Dz1Calloc(sizeof(ITSK00144_2Data), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ITSK00144_2Data_delAndSetNull, (void *)&ret);
		if (ITSK00144_2Data_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2Data_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ITSK00144_2Data_purge(ITSK00144_2Data *p)
{
	if (!p) return;
	switch(p->present)
	{
	case ITSK00144_2DataPresent_req_link_unit_status:
		ITSK00144_2Reserved0_del(p->x.req_link_unit_status);
		break;
	case ITSK00144_2DataPresent_rsp_link_unit_status:
		I2XTrafficSafetyDeviceLinkUnitStatus_del(p->x.rsp_link_unit_status);
		break;
	case ITSK00144_2DataPresent_req_status:
		ITSK00144_2Reserved0_del(p->x.req_status);
		break;
	case ITSK00144_2DataPresent_rsp_status:
		I2XTrafficSafetyDeviceStatusInfo_del(p->x.rsp_status);
		break;
	case ITSK00144_2DataPresent_req_list:
		ITSK00144_2Reserved0_del(p->x.req_list);
		break;
	case ITSK00144_2DataPresent_rsp_list:
		I2XTrafficSafetyDeviceList_del(p->x.rsp_list);
		break;
	case ITSK00144_2DataPresent_req_update_list:
		I2XTrafficSafetyDeviceList_del(p->x.req_update_list);
		break;
	case ITSK00144_2DataPresent_rsp_update_list:
		I2XTrafficSafetyDeviceList_del(p->x.rsp_update_list);
		break;
	case ITSK00144_2DataPresent_reset:
		ITSK00144_2Reserved0_del(p->x.reset);
		break;
	case ITSK00144_2DataPresent_hb:
		ITSK00144_2Reserved0_del(p->x.hb);
		break;
	case ITSK00144_2DataPresent_ack:
		ITSK00144_2Reserved0_del(p->x.ack);
		break;
	case ITSK00144_2DataPresent_nack:
		ITSK00144_2Reserved0_del(p->x.nack);
		break;
	default:
		break;
	}
}

void ITSK00144_2Data_del(ITSK00144_2Data *p)
{
	if (!p) return;
	ITSK00144_2Data_purge(p);
	Dz1Free(p);
}

void ITSK00144_2Data_dump(ITSK00144_2Data *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case ITSK00144_2DataPresent_req_link_unit_status:
		Dz1Thread_printf(Dz1T("req_link_unit_status = ")); ITSK00144_2Reserved0_dump(p->x.req_link_unit_status, tab); 
		break;
	case ITSK00144_2DataPresent_rsp_link_unit_status:
		Dz1Thread_printf(Dz1T("rsp_link_unit_status = ")); I2XTrafficSafetyDeviceLinkUnitStatus_dump(p->x.rsp_link_unit_status, tab); 
		break;
	case ITSK00144_2DataPresent_req_status:
		Dz1Thread_printf(Dz1T("req_status = ")); ITSK00144_2Reserved0_dump(p->x.req_status, tab); 
		break;
	case ITSK00144_2DataPresent_rsp_status:
		Dz1Thread_printf(Dz1T("rsp_status = ")); I2XTrafficSafetyDeviceStatusInfo_dump(p->x.rsp_status, tab); 
		break;
	case ITSK00144_2DataPresent_req_list:
		Dz1Thread_printf(Dz1T("req_list = ")); ITSK00144_2Reserved0_dump(p->x.req_list, tab); 
		break;
	case ITSK00144_2DataPresent_rsp_list:
		Dz1Thread_printf(Dz1T("rsp_list = ")); I2XTrafficSafetyDeviceList_dump(p->x.rsp_list, tab); 
		break;
	case ITSK00144_2DataPresent_req_update_list:
		Dz1Thread_printf(Dz1T("req_update_list = ")); I2XTrafficSafetyDeviceList_dump(p->x.req_update_list, tab); 
		break;
	case ITSK00144_2DataPresent_rsp_update_list:
		Dz1Thread_printf(Dz1T("rsp_update_list = ")); I2XTrafficSafetyDeviceList_dump(p->x.rsp_update_list, tab); 
		break;
	case ITSK00144_2DataPresent_reset:
		Dz1Thread_printf(Dz1T("reset = ")); ITSK00144_2Reserved0_dump(p->x.reset, tab); 
		break;
	case ITSK00144_2DataPresent_hb:
		Dz1Thread_printf(Dz1T("hb = ")); ITSK00144_2Reserved0_dump(p->x.hb, tab); 
		break;
	case ITSK00144_2DataPresent_ack:
		Dz1Thread_printf(Dz1T("ack = ")); ITSK00144_2Reserved0_dump(p->x.ack, tab); 
		break;
	case ITSK00144_2DataPresent_nack:
		Dz1Thread_printf(Dz1T("nack = ")); ITSK00144_2Reserved0_dump(p->x.nack, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// ITSK00144_2Data
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ProtocolFrameContext
ITSK00144_2ProtocolFrameContext *ITSK00144_2ProtocolFrameContext_new(I2XTrafficSafetyDeviceSerialNo *id, 
																	 u8_t seq, 
																	 u8_t opcode, 
																	 ITSK00144_2Data *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2ProtocolFrameContext *__internal_ret = (ITSK00144_2ProtocolFrameContext *)Dz1Calloc(sizeof(ITSK00144_2ProtocolFrameContext), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00144_2ProtocolFrameContext_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->id = id;
		__internal_ret->seq = seq;
		__internal_ret->opcode = opcode;
		__internal_ret->data = data;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2ProtocolFrameContext_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ITSK00144_2ProtocolFrameContext_copy(ITSK00144_2ProtocolFrameContext *dst, ITSK00144_2ProtocolFrameContext *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->id && (dst->id = I2XTrafficSafetyDeviceSerialNo_clone(src->id, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = ITSK00144_2Data_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->seq = src->seq;
		dst->opcode = src->opcode;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ITSK00144_2ProtocolFrameContext *ITSK00144_2ProtocolFrameContext_clone(ITSK00144_2ProtocolFrameContext *src, Dz1Error *err)
{
	ITSK00144_2ProtocolFrameContext *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ITSK00144_2ProtocolFrameContext *)Dz1Calloc(sizeof(ITSK00144_2ProtocolFrameContext), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ITSK00144_2ProtocolFrameContext_delAndSetNull, (void *)&dst);
		if (ITSK00144_2ProtocolFrameContext_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2ProtocolFrameContext_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ITSK00144_2ProtocolFrameContext_purge(ITSK00144_2ProtocolFrameContext *p)
{
	if (p == NULL) return;
	I2XTrafficSafetyDeviceSerialNo_del(p->id);
	ITSK00144_2Data_del(p->data);
}

void ITSK00144_2ProtocolFrameContext_del(ITSK00144_2ProtocolFrameContext *p)
{
	if (p == NULL) return;
	ITSK00144_2ProtocolFrameContext_purge(p);
	Dz1Free(p);
}

void ITSK00144_2ProtocolFrameContext_dump(ITSK00144_2ProtocolFrameContext *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("id = ")); I2XTrafficSafetyDeviceSerialNo_dump(p->id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("seq = ")); Dz1u8_dump(&p->seq, tab); 
		Dz1Thread_tprintf(tab, Dz1T("opcode = ")); Dz1u8_dump(&p->opcode, tab); 
		Dz1Thread_tprintf(tab, Dz1T("data.")); ITSK00144_2Data_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ITSK00144_2ProtocolFrameContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ProtocolFrame
ITSK00144_2ProtocolFrame *ITSK00144_2ProtocolFrame_new(u16_t length, 
													   Dz1Binary *context, 
													   u16_t crc, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ITSK00144_2ProtocolFrame *__internal_ret = (ITSK00144_2ProtocolFrame *)Dz1Calloc(sizeof(ITSK00144_2ProtocolFrame), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ITSK00144_2ProtocolFrame_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->length = length;
		__internal_ret->context = context;
		__internal_ret->crc = crc;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2ProtocolFrame_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ITSK00144_2ProtocolFrame_copy(ITSK00144_2ProtocolFrame *dst, ITSK00144_2ProtocolFrame *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->context && (dst->context = Dz1Binary_clone(src->context, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->length = src->length;
		dst->crc = src->crc;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ITSK00144_2ProtocolFrame *ITSK00144_2ProtocolFrame_clone(ITSK00144_2ProtocolFrame *src, Dz1Error *err)
{
	ITSK00144_2ProtocolFrame *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ITSK00144_2ProtocolFrame *)Dz1Calloc(sizeof(ITSK00144_2ProtocolFrame), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ITSK00144_2ProtocolFrame_delAndSetNull, (void *)&dst);
		if (ITSK00144_2ProtocolFrame_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ITSK00144_2ProtocolFrame_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ITSK00144_2ProtocolFrame_purge(ITSK00144_2ProtocolFrame *p)
{
	if (p == NULL) return;
	Dz1Binary_del(p->context);
}

void ITSK00144_2ProtocolFrame_del(ITSK00144_2ProtocolFrame *p)
{
	if (p == NULL) return;
	ITSK00144_2ProtocolFrame_purge(p);
	Dz1Free(p);
}

void ITSK00144_2ProtocolFrame_dump(ITSK00144_2ProtocolFrame *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("length = ")); Dz1u16_dump(&p->length, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("context = ")); Dz1Binary_dump(p->context, tab); 
		Dz1Thread_tprintf(tab, Dz1T("crc = ")); Dz1u16_dump(&p->crc, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ITSK00144_2ProtocolFrame
////////////////////////////////////////////////////////////////////////////////


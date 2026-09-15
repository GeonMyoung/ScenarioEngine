////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Itsk00126v2TestMsgDef.h"

////////////////////////////////////////////////////////////////////////////////
// F2CIoTImDeviceSttusInfoData
F2CIoTImDeviceSttusInfoData *F2CIoTImDeviceSttusInfoData_new(Dz1Str iot_im_device_id, 
															 Dz1Str iot_im_device_link_sttus_code, 
															 Dz1Str creat_dt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	F2CIoTImDeviceSttusInfoData *__internal_ret = (F2CIoTImDeviceSttusInfoData *)Dz1Calloc(sizeof(F2CIoTImDeviceSttusInfoData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(F2CIoTImDeviceSttusInfoData_delAndSetNull, (void *)&__internal_ret);
		
		if (iot_im_device_id && (__internal_ret->iot_im_device_id = Dz1Str_clone(iot_im_device_id, errp)) == NULL) ERR_OUT(errp);
		else if (iot_im_device_link_sttus_code && (__internal_ret->iot_im_device_link_sttus_code = Dz1Str_clone(iot_im_device_link_sttus_code, errp)) == NULL) ERR_OUT(errp);
		else if (creat_dt && (__internal_ret->creat_dt = Dz1Str_clone(creat_dt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (F2CIoTImDeviceSttusInfoData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t F2CIoTImDeviceSttusInfoData_copy(F2CIoTImDeviceSttusInfoData *dst, F2CIoTImDeviceSttusInfoData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->iot_im_device_id && (dst->iot_im_device_id = Dz1Str_clone(src->iot_im_device_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->iot_im_device_link_sttus_code && (dst->iot_im_device_link_sttus_code = Dz1Str_clone(src->iot_im_device_link_sttus_code, errp)) == NULL) ERR_OUT(errp);
	else if (src->creat_dt && (dst->creat_dt = Dz1Str_clone(src->creat_dt, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

F2CIoTImDeviceSttusInfoData *F2CIoTImDeviceSttusInfoData_clone(F2CIoTImDeviceSttusInfoData *src, Dz1Error *err)
{
	F2CIoTImDeviceSttusInfoData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (F2CIoTImDeviceSttusInfoData *)Dz1Calloc(sizeof(F2CIoTImDeviceSttusInfoData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(F2CIoTImDeviceSttusInfoData_delAndSetNull, (void *)&dst);
		if (F2CIoTImDeviceSttusInfoData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (F2CIoTImDeviceSttusInfoData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void F2CIoTImDeviceSttusInfoData_purge(F2CIoTImDeviceSttusInfoData *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->iot_im_device_id);
	Dz1Str_del(p->iot_im_device_link_sttus_code);
	Dz1Str_del(p->creat_dt);
}

void F2CIoTImDeviceSttusInfoData_del(F2CIoTImDeviceSttusInfoData *p)
{
	if (p == NULL) return;
	F2CIoTImDeviceSttusInfoData_purge(p);
	Dz1Free(p);
}

void F2CIoTImDeviceSttusInfoData_dump(F2CIoTImDeviceSttusInfoData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("iot_im_device_id = ")); Dz1Str_dump(p->iot_im_device_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("iot_im_device_link_sttus_code = ")); Dz1Str_dump(p->iot_im_device_link_sttus_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("creat_dt = ")); Dz1Str_dump(p->creat_dt, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// F2CIoTImDeviceSttusInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTImDeviceSttusInfo
F2CIoTImDeviceSttusInfo *F2CIoTImDeviceSttusInfo_new(Dz1Str command, 
													 F2CIoTImDeviceSttusInfoData *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	F2CIoTImDeviceSttusInfo *__internal_ret = (F2CIoTImDeviceSttusInfo *)Dz1Calloc(sizeof(F2CIoTImDeviceSttusInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(F2CIoTImDeviceSttusInfo_delAndSetNull, (void *)&__internal_ret);
		
		if (command && (__internal_ret->command = Dz1Str_clone(command, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->data = data;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (F2CIoTImDeviceSttusInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t F2CIoTImDeviceSttusInfo_copy(F2CIoTImDeviceSttusInfo *dst, F2CIoTImDeviceSttusInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->command && (dst->command = Dz1Str_clone(src->command, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = F2CIoTImDeviceSttusInfoData_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

F2CIoTImDeviceSttusInfo *F2CIoTImDeviceSttusInfo_clone(F2CIoTImDeviceSttusInfo *src, Dz1Error *err)
{
	F2CIoTImDeviceSttusInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (F2CIoTImDeviceSttusInfo *)Dz1Calloc(sizeof(F2CIoTImDeviceSttusInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(F2CIoTImDeviceSttusInfo_delAndSetNull, (void *)&dst);
		if (F2CIoTImDeviceSttusInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (F2CIoTImDeviceSttusInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void F2CIoTImDeviceSttusInfo_purge(F2CIoTImDeviceSttusInfo *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->command);
	F2CIoTImDeviceSttusInfoData_del(p->data);
}

void F2CIoTImDeviceSttusInfo_del(F2CIoTImDeviceSttusInfo *p)
{
	if (p == NULL) return;
	F2CIoTImDeviceSttusInfo_purge(p);
	Dz1Free(p);
}

void F2CIoTImDeviceSttusInfo_dump(F2CIoTImDeviceSttusInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("command = ")); Dz1Str_dump(p->command, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("data = ")); F2CIoTImDeviceSttusInfoData_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// F2CIoTImDeviceSttusInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTDeviceEntry
F2CIoTDeviceEntry *F2CIoTDeviceEntry_new(Dz1Str iot_device_id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	F2CIoTDeviceEntry *__internal_ret = (F2CIoTDeviceEntry *)Dz1Calloc(sizeof(F2CIoTDeviceEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(F2CIoTDeviceEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (iot_device_id && (__internal_ret->iot_device_id = Dz1Str_clone(iot_device_id, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (F2CIoTDeviceEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t F2CIoTDeviceEntry_copy(F2CIoTDeviceEntry *dst, F2CIoTDeviceEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->iot_device_id && (dst->iot_device_id = Dz1Str_clone(src->iot_device_id, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

F2CIoTDeviceEntry *F2CIoTDeviceEntry_clone(F2CIoTDeviceEntry *src, Dz1Error *err)
{
	F2CIoTDeviceEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (F2CIoTDeviceEntry *)Dz1Calloc(sizeof(F2CIoTDeviceEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(F2CIoTDeviceEntry_delAndSetNull, (void *)&dst);
		if (F2CIoTDeviceEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (F2CIoTDeviceEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void F2CIoTDeviceEntry_purge(F2CIoTDeviceEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->iot_device_id);
}

void F2CIoTDeviceEntry_del(F2CIoTDeviceEntry *p)
{
	if (p == NULL) return;
	F2CIoTDeviceEntry_purge(p);
	Dz1Free(p);
}

void F2CIoTDeviceEntry_dump(F2CIoTDeviceEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("iot_device_id = ")); Dz1Str_dump(p->iot_device_id, tab); 
	}
}
// F2CIoTDeviceEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTDeviceList
static Dz1Error F2CIoTDeviceList_add(F2CIoTDeviceList *p, F2CIoTDeviceEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static F2CIoTDeviceEntry *F2CIoTDeviceList_extract(F2CIoTDeviceList *p, F2CIoTDeviceEntry *ptr)
{
	return (F2CIoTDeviceEntry *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct F2CIoTDeviceListMkArrArg
{
	F2CIoTDeviceEntry **arr;
	unsigned int idx;
} F2CIoTDeviceListMkArrArg;

static Dz1Error _F2CIoTDeviceList_get_array(void *ptr, F2CIoTDeviceEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	F2CIoTDeviceListMkArrArg *arg = (F2CIoTDeviceListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static F2CIoTDeviceEntry **F2CIoTDeviceList_get_array(F2CIoTDeviceList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	F2CIoTDeviceEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (F2CIoTDeviceEntry **)Dz1Calloc(sizeof(F2CIoTDeviceEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		F2CIoTDeviceListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _F2CIoTDeviceList_get_array, (void *)&arg);
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

static Dz1Error F2CIoTDeviceList_travelForward(F2CIoTDeviceList *p, Dz1Error (*func)(void *ptr, F2CIoTDeviceEntry *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error F2CIoTDeviceList_travelBackward(F2CIoTDeviceList *p, Dz1Error (*func)(void *ptr, F2CIoTDeviceEntry *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static F2CIoTDeviceEntry *F2CIoTDeviceList_getHead(F2CIoTDeviceList *p)
{
	return (F2CIoTDeviceEntry *)Dz1Fifo_getFirst(p->storage);
}

static unsigned int F2CIoTDeviceList_count(F2CIoTDeviceList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

F2CIoTDeviceList *F2CIoTDeviceList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	F2CIoTDeviceList *ret = (F2CIoTDeviceList *)Dz1Calloc(sizeof(F2CIoTDeviceList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(F2CIoTDeviceList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)F2CIoTDeviceEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = F2CIoTDeviceList_count;
			ret->travel = F2CIoTDeviceList_travelForward;
			ret->travelForward = F2CIoTDeviceList_travelForward;
			ret->travelBackward = F2CIoTDeviceList_travelBackward;
			ret->get_array = F2CIoTDeviceList_get_array;
			ret->add = F2CIoTDeviceList_add;
			ret->extract = F2CIoTDeviceList_extract;
			ret->getHead = F2CIoTDeviceList_getHead;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (F2CIoTDeviceList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _F2CIoTDeviceList_clone(void *ptr, F2CIoTDeviceEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	F2CIoTDeviceList *p = (F2CIoTDeviceList *)ptr;
	F2CIoTDeviceEntry *cloned = F2CIoTDeviceEntry_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

F2CIoTDeviceList *F2CIoTDeviceList_clone(F2CIoTDeviceList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	F2CIoTDeviceList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = F2CIoTDeviceList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(F2CIoTDeviceList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_F2CIoTDeviceList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (F2CIoTDeviceList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void F2CIoTDeviceList_purge(F2CIoTDeviceList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void F2CIoTDeviceList_del(F2CIoTDeviceList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _F2CIoTDeviceList_dump(void *ptr, F2CIoTDeviceEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); F2CIoTDeviceEntry_dump(p, tab);
	return err;
}

void F2CIoTDeviceList_dump(F2CIoTDeviceList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _F2CIoTDeviceList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// F2CIoTDeviceList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTDeviceListResponseInfoData
F2CIoTDeviceListResponseInfoData *F2CIoTDeviceListResponseInfoData_new(Dz1Str iot_im_device_id, 
																	   Dz1Str event_name, 
																	   Dz1Str event_type, 
																	   Dz1Str iot_device_id_qty, 
																	   F2CIoTDeviceList *iot_device_list, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	F2CIoTDeviceListResponseInfoData *__internal_ret = (F2CIoTDeviceListResponseInfoData *)Dz1Calloc(sizeof(F2CIoTDeviceListResponseInfoData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(F2CIoTDeviceListResponseInfoData_delAndSetNull, (void *)&__internal_ret);
		
		if (iot_im_device_id && (__internal_ret->iot_im_device_id = Dz1Str_clone(iot_im_device_id, errp)) == NULL) ERR_OUT(errp);
		else if (event_name && (__internal_ret->event_name = Dz1Str_clone(event_name, errp)) == NULL) ERR_OUT(errp);
		else if (event_type && (__internal_ret->event_type = Dz1Str_clone(event_type, errp)) == NULL) ERR_OUT(errp);
		else if (iot_device_id_qty && (__internal_ret->iot_device_id_qty = Dz1Str_clone(iot_device_id_qty, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->iot_device_list = iot_device_list;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (F2CIoTDeviceListResponseInfoData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t F2CIoTDeviceListResponseInfoData_copy(F2CIoTDeviceListResponseInfoData *dst, F2CIoTDeviceListResponseInfoData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->iot_im_device_id && (dst->iot_im_device_id = Dz1Str_clone(src->iot_im_device_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->event_name && (dst->event_name = Dz1Str_clone(src->event_name, errp)) == NULL) ERR_OUT(errp);
	else if (src->event_type && (dst->event_type = Dz1Str_clone(src->event_type, errp)) == NULL) ERR_OUT(errp);
	else if (src->iot_device_id_qty && (dst->iot_device_id_qty = Dz1Str_clone(src->iot_device_id_qty, errp)) == NULL) ERR_OUT(errp);
	else if (src->iot_device_list && (dst->iot_device_list = F2CIoTDeviceList_clone(src->iot_device_list, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

F2CIoTDeviceListResponseInfoData *F2CIoTDeviceListResponseInfoData_clone(F2CIoTDeviceListResponseInfoData *src, Dz1Error *err)
{
	F2CIoTDeviceListResponseInfoData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (F2CIoTDeviceListResponseInfoData *)Dz1Calloc(sizeof(F2CIoTDeviceListResponseInfoData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(F2CIoTDeviceListResponseInfoData_delAndSetNull, (void *)&dst);
		if (F2CIoTDeviceListResponseInfoData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (F2CIoTDeviceListResponseInfoData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void F2CIoTDeviceListResponseInfoData_purge(F2CIoTDeviceListResponseInfoData *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->iot_im_device_id);
	Dz1Str_del(p->event_name);
	Dz1Str_del(p->event_type);
	Dz1Str_del(p->iot_device_id_qty);
	F2CIoTDeviceList_del(p->iot_device_list);
}

void F2CIoTDeviceListResponseInfoData_del(F2CIoTDeviceListResponseInfoData *p)
{
	if (p == NULL) return;
	F2CIoTDeviceListResponseInfoData_purge(p);
	Dz1Free(p);
}

void F2CIoTDeviceListResponseInfoData_dump(F2CIoTDeviceListResponseInfoData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("iot_im_device_id = ")); Dz1Str_dump(p->iot_im_device_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("event_name = ")); Dz1Str_dump(p->event_name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("event_type = ")); Dz1Str_dump(p->event_type, tab); 
		Dz1Thread_tprintf(tab, Dz1T("iot_device_id_qty = ")); Dz1Str_dump(p->iot_device_id_qty, tab); 
		Dz1Thread_tprintf(tab, Dz1T("iot_device_list = ")); F2CIoTDeviceList_dump(p->iot_device_list, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// F2CIoTDeviceListResponseInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTDeviceListResponseInfo
F2CIoTDeviceListResponseInfo *F2CIoTDeviceListResponseInfo_new(Dz1Str command, 
															   F2CIoTDeviceListResponseInfoData *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	F2CIoTDeviceListResponseInfo *__internal_ret = (F2CIoTDeviceListResponseInfo *)Dz1Calloc(sizeof(F2CIoTDeviceListResponseInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(F2CIoTDeviceListResponseInfo_delAndSetNull, (void *)&__internal_ret);
		
		if (command && (__internal_ret->command = Dz1Str_clone(command, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->data = data;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (F2CIoTDeviceListResponseInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t F2CIoTDeviceListResponseInfo_copy(F2CIoTDeviceListResponseInfo *dst, F2CIoTDeviceListResponseInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->command && (dst->command = Dz1Str_clone(src->command, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = F2CIoTDeviceListResponseInfoData_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

F2CIoTDeviceListResponseInfo *F2CIoTDeviceListResponseInfo_clone(F2CIoTDeviceListResponseInfo *src, Dz1Error *err)
{
	F2CIoTDeviceListResponseInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (F2CIoTDeviceListResponseInfo *)Dz1Calloc(sizeof(F2CIoTDeviceListResponseInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(F2CIoTDeviceListResponseInfo_delAndSetNull, (void *)&dst);
		if (F2CIoTDeviceListResponseInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (F2CIoTDeviceListResponseInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void F2CIoTDeviceListResponseInfo_purge(F2CIoTDeviceListResponseInfo *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->command);
	F2CIoTDeviceListResponseInfoData_del(p->data);
}

void F2CIoTDeviceListResponseInfo_del(F2CIoTDeviceListResponseInfo *p)
{
	if (p == NULL) return;
	F2CIoTDeviceListResponseInfo_purge(p);
	Dz1Free(p);
}

void F2CIoTDeviceListResponseInfo_dump(F2CIoTDeviceListResponseInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("command = ")); Dz1Str_dump(p->command, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("data = ")); F2CIoTDeviceListResponseInfoData_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// F2CIoTDeviceListResponseInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIotDeviceListResetInfoData
F2CIotDeviceListResetInfoData *F2CIotDeviceListResetInfoData_new(Dz1Str iot_im_device_id, 
																 Dz1Str iot_device_id_qty, 
																 F2CIoTDeviceList *iot_device_update_list, 
																 Dz1Str creat_dt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	F2CIotDeviceListResetInfoData *__internal_ret = (F2CIotDeviceListResetInfoData *)Dz1Calloc(sizeof(F2CIotDeviceListResetInfoData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(F2CIotDeviceListResetInfoData_delAndSetNull, (void *)&__internal_ret);
		
		if (iot_im_device_id && (__internal_ret->iot_im_device_id = Dz1Str_clone(iot_im_device_id, errp)) == NULL) ERR_OUT(errp);
		else if (iot_device_id_qty && (__internal_ret->iot_device_id_qty = Dz1Str_clone(iot_device_id_qty, errp)) == NULL) ERR_OUT(errp);
		else if (creat_dt && (__internal_ret->creat_dt = Dz1Str_clone(creat_dt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->iot_device_update_list = iot_device_update_list;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (F2CIotDeviceListResetInfoData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t F2CIotDeviceListResetInfoData_copy(F2CIotDeviceListResetInfoData *dst, F2CIotDeviceListResetInfoData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->iot_im_device_id && (dst->iot_im_device_id = Dz1Str_clone(src->iot_im_device_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->iot_device_id_qty && (dst->iot_device_id_qty = Dz1Str_clone(src->iot_device_id_qty, errp)) == NULL) ERR_OUT(errp);
	else if (src->iot_device_update_list && (dst->iot_device_update_list = F2CIoTDeviceList_clone(src->iot_device_update_list, errp)) == NULL) ERR_OUT(errp);
	else if (src->creat_dt && (dst->creat_dt = Dz1Str_clone(src->creat_dt, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

F2CIotDeviceListResetInfoData *F2CIotDeviceListResetInfoData_clone(F2CIotDeviceListResetInfoData *src, Dz1Error *err)
{
	F2CIotDeviceListResetInfoData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (F2CIotDeviceListResetInfoData *)Dz1Calloc(sizeof(F2CIotDeviceListResetInfoData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(F2CIotDeviceListResetInfoData_delAndSetNull, (void *)&dst);
		if (F2CIotDeviceListResetInfoData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (F2CIotDeviceListResetInfoData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void F2CIotDeviceListResetInfoData_purge(F2CIotDeviceListResetInfoData *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->iot_im_device_id);
	Dz1Str_del(p->iot_device_id_qty);
	F2CIoTDeviceList_del(p->iot_device_update_list);
	Dz1Str_del(p->creat_dt);
}

void F2CIotDeviceListResetInfoData_del(F2CIotDeviceListResetInfoData *p)
{
	if (p == NULL) return;
	F2CIotDeviceListResetInfoData_purge(p);
	Dz1Free(p);
}

void F2CIotDeviceListResetInfoData_dump(F2CIotDeviceListResetInfoData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("iot_im_device_id = ")); Dz1Str_dump(p->iot_im_device_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("iot_device_id_qty = ")); Dz1Str_dump(p->iot_device_id_qty, tab); 
		Dz1Thread_tprintf(tab, Dz1T("iot_device_update_list = ")); F2CIoTDeviceList_dump(p->iot_device_update_list, tab); 
		Dz1Thread_tprintf(tab, Dz1T("creat_dt = ")); Dz1Str_dump(p->creat_dt, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// F2CIotDeviceListResetInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIotDeviceListResetInfo
F2CIotDeviceListResetInfo *F2CIotDeviceListResetInfo_new(Dz1Str command, 
														 F2CIotDeviceListResetInfoData *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	F2CIotDeviceListResetInfo *__internal_ret = (F2CIotDeviceListResetInfo *)Dz1Calloc(sizeof(F2CIotDeviceListResetInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(F2CIotDeviceListResetInfo_delAndSetNull, (void *)&__internal_ret);
		
		if (command && (__internal_ret->command = Dz1Str_clone(command, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->data = data;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (F2CIotDeviceListResetInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t F2CIotDeviceListResetInfo_copy(F2CIotDeviceListResetInfo *dst, F2CIotDeviceListResetInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->command && (dst->command = Dz1Str_clone(src->command, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = F2CIotDeviceListResetInfoData_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

F2CIotDeviceListResetInfo *F2CIotDeviceListResetInfo_clone(F2CIotDeviceListResetInfo *src, Dz1Error *err)
{
	F2CIotDeviceListResetInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (F2CIotDeviceListResetInfo *)Dz1Calloc(sizeof(F2CIotDeviceListResetInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(F2CIotDeviceListResetInfo_delAndSetNull, (void *)&dst);
		if (F2CIotDeviceListResetInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (F2CIotDeviceListResetInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void F2CIotDeviceListResetInfo_purge(F2CIotDeviceListResetInfo *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->command);
	F2CIotDeviceListResetInfoData_del(p->data);
}

void F2CIotDeviceListResetInfo_del(F2CIotDeviceListResetInfo *p)
{
	if (p == NULL) return;
	F2CIotDeviceListResetInfo_purge(p);
	Dz1Free(p);
}

void F2CIotDeviceListResetInfo_dump(F2CIotDeviceListResetInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("command = ")); Dz1Str_dump(p->command, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("data = ")); F2CIotDeviceListResetInfoData_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// F2CIotDeviceListResetInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTDeviceSttusInfoEntry
F2CIoTDeviceSttusInfoEntry *F2CIoTDeviceSttusInfoEntry_new(Dz1Str iot_device_id, 
														   Dz1Str iot_device_sttus_code, 
														   Dz1Str btry_sttus_code, 
														   Dz1Str link_sttus_code, 
														   s64_t data_trnsmis_cont, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	F2CIoTDeviceSttusInfoEntry *__internal_ret = (F2CIoTDeviceSttusInfoEntry *)Dz1Calloc(sizeof(F2CIoTDeviceSttusInfoEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(F2CIoTDeviceSttusInfoEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (iot_device_id && (__internal_ret->iot_device_id = Dz1Str_clone(iot_device_id, errp)) == NULL) ERR_OUT(errp);
		else if (iot_device_sttus_code && (__internal_ret->iot_device_sttus_code = Dz1Str_clone(iot_device_sttus_code, errp)) == NULL) ERR_OUT(errp);
		else if (btry_sttus_code && (__internal_ret->btry_sttus_code = Dz1Str_clone(btry_sttus_code, errp)) == NULL) ERR_OUT(errp);
		else if (link_sttus_code && (__internal_ret->link_sttus_code = Dz1Str_clone(link_sttus_code, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->data_trnsmis_cont = data_trnsmis_cont;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (F2CIoTDeviceSttusInfoEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t F2CIoTDeviceSttusInfoEntry_copy(F2CIoTDeviceSttusInfoEntry *dst, F2CIoTDeviceSttusInfoEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->iot_device_id && (dst->iot_device_id = Dz1Str_clone(src->iot_device_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->iot_device_sttus_code && (dst->iot_device_sttus_code = Dz1Str_clone(src->iot_device_sttus_code, errp)) == NULL) ERR_OUT(errp);
	else if (src->btry_sttus_code && (dst->btry_sttus_code = Dz1Str_clone(src->btry_sttus_code, errp)) == NULL) ERR_OUT(errp);
	else if (src->link_sttus_code && (dst->link_sttus_code = Dz1Str_clone(src->link_sttus_code, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->data_trnsmis_cont = src->data_trnsmis_cont;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

F2CIoTDeviceSttusInfoEntry *F2CIoTDeviceSttusInfoEntry_clone(F2CIoTDeviceSttusInfoEntry *src, Dz1Error *err)
{
	F2CIoTDeviceSttusInfoEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (F2CIoTDeviceSttusInfoEntry *)Dz1Calloc(sizeof(F2CIoTDeviceSttusInfoEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(F2CIoTDeviceSttusInfoEntry_delAndSetNull, (void *)&dst);
		if (F2CIoTDeviceSttusInfoEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (F2CIoTDeviceSttusInfoEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void F2CIoTDeviceSttusInfoEntry_purge(F2CIoTDeviceSttusInfoEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->iot_device_id);
	Dz1Str_del(p->iot_device_sttus_code);
	Dz1Str_del(p->btry_sttus_code);
	Dz1Str_del(p->link_sttus_code);
}

void F2CIoTDeviceSttusInfoEntry_del(F2CIoTDeviceSttusInfoEntry *p)
{
	if (p == NULL) return;
	F2CIoTDeviceSttusInfoEntry_purge(p);
	Dz1Free(p);
}

void F2CIoTDeviceSttusInfoEntry_dump(F2CIoTDeviceSttusInfoEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("iot_device_id = ")); Dz1Str_dump(p->iot_device_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("iot_device_sttus_code = ")); Dz1Str_dump(p->iot_device_sttus_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("btry_sttus_code = ")); Dz1Str_dump(p->btry_sttus_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("link_sttus_code = ")); Dz1Str_dump(p->link_sttus_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("data_trnsmis_cont = ")); Dz1s64_dump(&p->data_trnsmis_cont, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// F2CIoTDeviceSttusInfoEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTDeviceSttusInfoList
static Dz1Error F2CIoTDeviceSttusInfoList_add(F2CIoTDeviceSttusInfoList *p, F2CIoTDeviceSttusInfoEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static F2CIoTDeviceSttusInfoEntry *F2CIoTDeviceSttusInfoList_extract(F2CIoTDeviceSttusInfoList *p, F2CIoTDeviceSttusInfoEntry *ptr)
{
	return (F2CIoTDeviceSttusInfoEntry *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct F2CIoTDeviceSttusInfoListMkArrArg
{
	F2CIoTDeviceSttusInfoEntry **arr;
	unsigned int idx;
} F2CIoTDeviceSttusInfoListMkArrArg;

static Dz1Error _F2CIoTDeviceSttusInfoList_get_array(void *ptr, F2CIoTDeviceSttusInfoEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	F2CIoTDeviceSttusInfoListMkArrArg *arg = (F2CIoTDeviceSttusInfoListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static F2CIoTDeviceSttusInfoEntry **F2CIoTDeviceSttusInfoList_get_array(F2CIoTDeviceSttusInfoList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	F2CIoTDeviceSttusInfoEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (F2CIoTDeviceSttusInfoEntry **)Dz1Calloc(sizeof(F2CIoTDeviceSttusInfoEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		F2CIoTDeviceSttusInfoListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _F2CIoTDeviceSttusInfoList_get_array, (void *)&arg);
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

static Dz1Error F2CIoTDeviceSttusInfoList_travelForward(F2CIoTDeviceSttusInfoList *p, Dz1Error (*func)(void *ptr, F2CIoTDeviceSttusInfoEntry *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error F2CIoTDeviceSttusInfoList_travelBackward(F2CIoTDeviceSttusInfoList *p, Dz1Error (*func)(void *ptr, F2CIoTDeviceSttusInfoEntry *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static F2CIoTDeviceSttusInfoEntry *F2CIoTDeviceSttusInfoList_getHead(F2CIoTDeviceSttusInfoList *p)
{
	return (F2CIoTDeviceSttusInfoEntry *)Dz1Fifo_getFirst(p->storage);
}

static unsigned int F2CIoTDeviceSttusInfoList_count(F2CIoTDeviceSttusInfoList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

F2CIoTDeviceSttusInfoList *F2CIoTDeviceSttusInfoList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	F2CIoTDeviceSttusInfoList *ret = (F2CIoTDeviceSttusInfoList *)Dz1Calloc(sizeof(F2CIoTDeviceSttusInfoList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(F2CIoTDeviceSttusInfoList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)F2CIoTDeviceSttusInfoEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = F2CIoTDeviceSttusInfoList_count;
			ret->travel = F2CIoTDeviceSttusInfoList_travelForward;
			ret->travelForward = F2CIoTDeviceSttusInfoList_travelForward;
			ret->travelBackward = F2CIoTDeviceSttusInfoList_travelBackward;
			ret->get_array = F2CIoTDeviceSttusInfoList_get_array;
			ret->add = F2CIoTDeviceSttusInfoList_add;
			ret->extract = F2CIoTDeviceSttusInfoList_extract;
			ret->getHead = F2CIoTDeviceSttusInfoList_getHead;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (F2CIoTDeviceSttusInfoList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _F2CIoTDeviceSttusInfoList_clone(void *ptr, F2CIoTDeviceSttusInfoEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	F2CIoTDeviceSttusInfoList *p = (F2CIoTDeviceSttusInfoList *)ptr;
	F2CIoTDeviceSttusInfoEntry *cloned = F2CIoTDeviceSttusInfoEntry_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

F2CIoTDeviceSttusInfoList *F2CIoTDeviceSttusInfoList_clone(F2CIoTDeviceSttusInfoList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	F2CIoTDeviceSttusInfoList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = F2CIoTDeviceSttusInfoList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(F2CIoTDeviceSttusInfoList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_F2CIoTDeviceSttusInfoList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (F2CIoTDeviceSttusInfoList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void F2CIoTDeviceSttusInfoList_purge(F2CIoTDeviceSttusInfoList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void F2CIoTDeviceSttusInfoList_del(F2CIoTDeviceSttusInfoList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _F2CIoTDeviceSttusInfoList_dump(void *ptr, F2CIoTDeviceSttusInfoEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); F2CIoTDeviceSttusInfoEntry_dump(p, tab);
	return err;
}

void F2CIoTDeviceSttusInfoList_dump(F2CIoTDeviceSttusInfoList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _F2CIoTDeviceSttusInfoList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// F2CIoTDeviceSttusInfoList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTDeviceSttusInfoData
F2CIoTDeviceSttusInfoData *F2CIoTDeviceSttusInfoData_new(Dz1Str iot_im_device_id, 
														 Dz1Str iot_device_id_qty, 
														 F2CIoTDeviceSttusInfoList *iot_device_sttus_info_list, 
														 Dz1Str creat_dt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	F2CIoTDeviceSttusInfoData *__internal_ret = (F2CIoTDeviceSttusInfoData *)Dz1Calloc(sizeof(F2CIoTDeviceSttusInfoData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(F2CIoTDeviceSttusInfoData_delAndSetNull, (void *)&__internal_ret);
		
		if (iot_im_device_id && (__internal_ret->iot_im_device_id = Dz1Str_clone(iot_im_device_id, errp)) == NULL) ERR_OUT(errp);
		else if (iot_device_id_qty && (__internal_ret->iot_device_id_qty = Dz1Str_clone(iot_device_id_qty, errp)) == NULL) ERR_OUT(errp);
		else if (creat_dt && (__internal_ret->creat_dt = Dz1Str_clone(creat_dt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->iot_device_sttus_info_list = iot_device_sttus_info_list;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (F2CIoTDeviceSttusInfoData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t F2CIoTDeviceSttusInfoData_copy(F2CIoTDeviceSttusInfoData *dst, F2CIoTDeviceSttusInfoData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->iot_im_device_id && (dst->iot_im_device_id = Dz1Str_clone(src->iot_im_device_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->iot_device_id_qty && (dst->iot_device_id_qty = Dz1Str_clone(src->iot_device_id_qty, errp)) == NULL) ERR_OUT(errp);
	else if (src->iot_device_sttus_info_list && (dst->iot_device_sttus_info_list = F2CIoTDeviceSttusInfoList_clone(src->iot_device_sttus_info_list, errp)) == NULL) ERR_OUT(errp);
	else if (src->creat_dt && (dst->creat_dt = Dz1Str_clone(src->creat_dt, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

F2CIoTDeviceSttusInfoData *F2CIoTDeviceSttusInfoData_clone(F2CIoTDeviceSttusInfoData *src, Dz1Error *err)
{
	F2CIoTDeviceSttusInfoData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (F2CIoTDeviceSttusInfoData *)Dz1Calloc(sizeof(F2CIoTDeviceSttusInfoData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(F2CIoTDeviceSttusInfoData_delAndSetNull, (void *)&dst);
		if (F2CIoTDeviceSttusInfoData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (F2CIoTDeviceSttusInfoData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void F2CIoTDeviceSttusInfoData_purge(F2CIoTDeviceSttusInfoData *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->iot_im_device_id);
	Dz1Str_del(p->iot_device_id_qty);
	F2CIoTDeviceSttusInfoList_del(p->iot_device_sttus_info_list);
	Dz1Str_del(p->creat_dt);
}

void F2CIoTDeviceSttusInfoData_del(F2CIoTDeviceSttusInfoData *p)
{
	if (p == NULL) return;
	F2CIoTDeviceSttusInfoData_purge(p);
	Dz1Free(p);
}

void F2CIoTDeviceSttusInfoData_dump(F2CIoTDeviceSttusInfoData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("iot_im_device_id = ")); Dz1Str_dump(p->iot_im_device_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("iot_device_id_qty = ")); Dz1Str_dump(p->iot_device_id_qty, tab); 
		Dz1Thread_tprintf(tab, Dz1T("iot_device_sttus_info_list = ")); F2CIoTDeviceSttusInfoList_dump(p->iot_device_sttus_info_list, tab); 
		Dz1Thread_tprintf(tab, Dz1T("creat_dt = ")); Dz1Str_dump(p->creat_dt, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// F2CIoTDeviceSttusInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTDeviceSttusInfo
F2CIoTDeviceSttusInfo *F2CIoTDeviceSttusInfo_new(Dz1Str command, 
												 F2CIoTDeviceSttusInfoData *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	F2CIoTDeviceSttusInfo *__internal_ret = (F2CIoTDeviceSttusInfo *)Dz1Calloc(sizeof(F2CIoTDeviceSttusInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(F2CIoTDeviceSttusInfo_delAndSetNull, (void *)&__internal_ret);
		
		if (command && (__internal_ret->command = Dz1Str_clone(command, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->data = data;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (F2CIoTDeviceSttusInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t F2CIoTDeviceSttusInfo_copy(F2CIoTDeviceSttusInfo *dst, F2CIoTDeviceSttusInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->command && (dst->command = Dz1Str_clone(src->command, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = F2CIoTDeviceSttusInfoData_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

F2CIoTDeviceSttusInfo *F2CIoTDeviceSttusInfo_clone(F2CIoTDeviceSttusInfo *src, Dz1Error *err)
{
	F2CIoTDeviceSttusInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (F2CIoTDeviceSttusInfo *)Dz1Calloc(sizeof(F2CIoTDeviceSttusInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(F2CIoTDeviceSttusInfo_delAndSetNull, (void *)&dst);
		if (F2CIoTDeviceSttusInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (F2CIoTDeviceSttusInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void F2CIoTDeviceSttusInfo_purge(F2CIoTDeviceSttusInfo *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->command);
	F2CIoTDeviceSttusInfoData_del(p->data);
}

void F2CIoTDeviceSttusInfo_del(F2CIoTDeviceSttusInfo *p)
{
	if (p == NULL) return;
	F2CIoTDeviceSttusInfo_purge(p);
	Dz1Free(p);
}

void F2CIoTDeviceSttusInfo_dump(F2CIoTDeviceSttusInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("command = ")); Dz1Str_dump(p->command, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("data = ")); F2CIoTDeviceSttusInfoData_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// F2CIoTDeviceSttusInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2RequestData
Itsk00126v2RequestData *Itsk00126v2RequestData_new(Dz1Str iot_im_device_id, 
												   Dz1Str event_name, 
												   Dz1Str event_type, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2RequestData *__internal_ret = (Itsk00126v2RequestData *)Dz1Calloc(sizeof(Itsk00126v2RequestData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v2RequestData_delAndSetNull, (void *)&__internal_ret);
		
		if (iot_im_device_id && (__internal_ret->iot_im_device_id = Dz1Str_clone(iot_im_device_id, errp)) == NULL) ERR_OUT(errp);
		else if (event_name && (__internal_ret->event_name = Dz1Str_clone(event_name, errp)) == NULL) ERR_OUT(errp);
		else if (event_type && (__internal_ret->event_type = Dz1Str_clone(event_type, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2RequestData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Itsk00126v2RequestData_copy(Itsk00126v2RequestData *dst, Itsk00126v2RequestData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->iot_im_device_id && (dst->iot_im_device_id = Dz1Str_clone(src->iot_im_device_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->event_name && (dst->event_name = Dz1Str_clone(src->event_name, errp)) == NULL) ERR_OUT(errp);
	else if (src->event_type && (dst->event_type = Dz1Str_clone(src->event_type, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Itsk00126v2RequestData *Itsk00126v2RequestData_clone(Itsk00126v2RequestData *src, Dz1Error *err)
{
	Itsk00126v2RequestData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Itsk00126v2RequestData *)Dz1Calloc(sizeof(Itsk00126v2RequestData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Itsk00126v2RequestData_delAndSetNull, (void *)&dst);
		if (Itsk00126v2RequestData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2RequestData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Itsk00126v2RequestData_purge(Itsk00126v2RequestData *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->iot_im_device_id);
	Dz1Str_del(p->event_name);
	Dz1Str_del(p->event_type);
}

void Itsk00126v2RequestData_del(Itsk00126v2RequestData *p)
{
	if (p == NULL) return;
	Itsk00126v2RequestData_purge(p);
	Dz1Free(p);
}

void Itsk00126v2RequestData_dump(Itsk00126v2RequestData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("iot_im_device_id = ")); Dz1Str_dump(p->iot_im_device_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("event_name = ")); Dz1Str_dump(p->event_name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("event_type = ")); Dz1Str_dump(p->event_type, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Itsk00126v2RequestData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2Request
Itsk00126v2Request *Itsk00126v2Request_new(Dz1Str command, 
										   Itsk00126v2RequestData *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2Request *__internal_ret = (Itsk00126v2Request *)Dz1Calloc(sizeof(Itsk00126v2Request), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v2Request_delAndSetNull, (void *)&__internal_ret);
		
		if (command && (__internal_ret->command = Dz1Str_clone(command, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->data = data;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2Request_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Itsk00126v2Request_copy(Itsk00126v2Request *dst, Itsk00126v2Request *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->command && (dst->command = Dz1Str_clone(src->command, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = Itsk00126v2RequestData_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Itsk00126v2Request *Itsk00126v2Request_clone(Itsk00126v2Request *src, Dz1Error *err)
{
	Itsk00126v2Request *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Itsk00126v2Request *)Dz1Calloc(sizeof(Itsk00126v2Request), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Itsk00126v2Request_delAndSetNull, (void *)&dst);
		if (Itsk00126v2Request_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2Request_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Itsk00126v2Request_purge(Itsk00126v2Request *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->command);
	Itsk00126v2RequestData_del(p->data);
}

void Itsk00126v2Request_del(Itsk00126v2Request *p)
{
	if (p == NULL) return;
	Itsk00126v2Request_purge(p);
	Dz1Free(p);
}

void Itsk00126v2Request_dump(Itsk00126v2Request *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("command = ")); Dz1Str_dump(p->command, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("data = ")); Itsk00126v2RequestData_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Itsk00126v2Request
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2EAMPresent
static struct Itsk00126v2EAMPresentMapA
{
	str_t str;
	Itsk00126v2EAMPresent v;
} Itsk00126v2EAMPresentMapA[] =
{
	{ (char *)"f2c_iot_im_device_sttus_info", Itsk00126v2EAMPresent_f2c_iot_im_device_sttus_info },
	{ (char *)"fc2_iot_device_list_request_info", Itsk00126v2EAMPresent_fc2_iot_device_list_request_info },
	{ (char *)"fc2_iot_device_list_response_info", Itsk00126v2EAMPresent_fc2_iot_device_list_response_info },
	{ (char *)"fc2_iot_device_list_reset_info", Itsk00126v2EAMPresent_fc2_iot_device_list_reset_info },
	{ (char *)"fc2_iot_device_sttus_info", Itsk00126v2EAMPresent_fc2_iot_device_sttus_info },
	{ NULL, Itsk00126v2EAMPresent_max }
};

str_t Itsk00126v2EAMPresentStrA(Itsk00126v2EAMPresent v)
{
	struct Itsk00126v2EAMPresentMapA *i = NULL;
	for (i = Itsk00126v2EAMPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Itsk00126v2EAMPresent Itsk00126v2EAMPresentFromStrA(str_t str)
{
	struct Itsk00126v2EAMPresentMapA *i = NULL;
	for (i = Itsk00126v2EAMPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Itsk00126v2EAMPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Itsk00126v2EAMPresentMapW
{
	wstr_t str;
	Itsk00126v2EAMPresent v;
} Itsk00126v2EAMPresentMapW[] =
{
	{ (wchar_t *)L"f2c_iot_im_device_sttus_info", Itsk00126v2EAMPresent_f2c_iot_im_device_sttus_info },
	{ (wchar_t *)L"fc2_iot_device_list_request_info", Itsk00126v2EAMPresent_fc2_iot_device_list_request_info },
	{ (wchar_t *)L"fc2_iot_device_list_response_info", Itsk00126v2EAMPresent_fc2_iot_device_list_response_info },
	{ (wchar_t *)L"fc2_iot_device_list_reset_info", Itsk00126v2EAMPresent_fc2_iot_device_list_reset_info },
	{ (wchar_t *)L"fc2_iot_device_sttus_info", Itsk00126v2EAMPresent_fc2_iot_device_sttus_info },
	{ NULL, Itsk00126v2EAMPresent_max }
};

wstr_t Itsk00126v2EAMPresentStrW(Itsk00126v2EAMPresent v)
{
	struct Itsk00126v2EAMPresentMapW *i = NULL;
	for (i = Itsk00126v2EAMPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Itsk00126v2EAMPresent Itsk00126v2EAMPresentFromStrW(wstr_t str)
{
	struct Itsk00126v2EAMPresentMapW *i = NULL;
	for (i = Itsk00126v2EAMPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Itsk00126v2EAMPresent_max;
}
#endif // UNIX_SYSTEM

Itsk00126v2EAMPresent *Itsk00126v2EAMPresent_new(Itsk00126v2EAMPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2EAMPresent *__internal_ret = (Itsk00126v2EAMPresent *)Dz1Calloc(sizeof(Itsk00126v2EAMPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Itsk00126v2EAMPresent_dump(Itsk00126v2EAMPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Itsk00126v2EAMPresentStr(*v));
}
// Itsk00126v2EAMPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2EAM
Itsk00126v2EAM *Itsk00126v2EAM_new(Itsk00126v2EAMPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v2EAM *ret = (Itsk00126v2EAM *)Dz1Calloc(sizeof(Itsk00126v2EAM), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v2EAM_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Itsk00126v2EAMPresent_f2c_iot_im_device_sttus_info:
			// _U_cst_clone
			if (ptr != NULL) ret->x.f2c_iot_im_device_sttus_info = (F2CIoTImDeviceSttusInfo *)ptr;
			ERR_CLEAR(errp);
			break;
		case Itsk00126v2EAMPresent_fc2_iot_device_list_request_info:
			// _U_cst_clone
			if (ptr != NULL) ret->x.fc2_iot_device_list_request_info = (Itsk00126v2Request *)ptr;
			ERR_CLEAR(errp);
			break;
		case Itsk00126v2EAMPresent_fc2_iot_device_list_response_info:
			// _U_cst_clone
			if (ptr != NULL) ret->x.fc2_iot_device_list_response_info = (F2CIoTDeviceListResponseInfo *)ptr;
			ERR_CLEAR(errp);
			break;
		case Itsk00126v2EAMPresent_fc2_iot_device_list_reset_info:
			// _U_cst_clone
			if (ptr != NULL) ret->x.fc2_iot_device_list_reset_info = (F2CIoTDeviceListResponseInfo *)ptr;
			ERR_CLEAR(errp);
			break;
		case Itsk00126v2EAMPresent_fc2_iot_device_sttus_info:
			// _U_cst_clone
			if (ptr != NULL) ret->x.fc2_iot_device_sttus_info = (F2CIoTDeviceSttusInfo *)ptr;
			ERR_CLEAR(errp);
			break;
		case Itsk00126v2EAMPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2EAM_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Itsk00126v2EAM_copy(Itsk00126v2EAM *ret, Itsk00126v2EAM *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Itsk00126v2EAMPresent_f2c_iot_im_device_sttus_info:
			// _U_cst_clone
			if (src->x.f2c_iot_im_device_sttus_info && (ret->x.f2c_iot_im_device_sttus_info = F2CIoTImDeviceSttusInfo_clone(src->x.f2c_iot_im_device_sttus_info, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Itsk00126v2EAMPresent_fc2_iot_device_list_request_info:
			// _U_cst_clone
			if (src->x.fc2_iot_device_list_request_info && (ret->x.fc2_iot_device_list_request_info = Itsk00126v2Request_clone(src->x.fc2_iot_device_list_request_info, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Itsk00126v2EAMPresent_fc2_iot_device_list_response_info:
			// _U_cst_clone
			if (src->x.fc2_iot_device_list_response_info && (ret->x.fc2_iot_device_list_response_info = F2CIoTDeviceListResponseInfo_clone(src->x.fc2_iot_device_list_response_info, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Itsk00126v2EAMPresent_fc2_iot_device_list_reset_info:
			// _U_cst_clone
			if (src->x.fc2_iot_device_list_reset_info && (ret->x.fc2_iot_device_list_reset_info = F2CIoTDeviceListResponseInfo_clone(src->x.fc2_iot_device_list_reset_info, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Itsk00126v2EAMPresent_fc2_iot_device_sttus_info:
			// _U_cst_clone
			if (src->x.fc2_iot_device_sttus_info && (ret->x.fc2_iot_device_sttus_info = F2CIoTDeviceSttusInfo_clone(src->x.fc2_iot_device_sttus_info, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Itsk00126v2EAM *Itsk00126v2EAM_clone(Itsk00126v2EAM *src, Dz1Error *err)
{
	Itsk00126v2EAM *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Itsk00126v2EAM *)Dz1Calloc(sizeof(Itsk00126v2EAM), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Itsk00126v2EAM_delAndSetNull, (void *)&ret);
		if (Itsk00126v2EAM_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v2EAM_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Itsk00126v2EAM_purge(Itsk00126v2EAM *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Itsk00126v2EAMPresent_f2c_iot_im_device_sttus_info:
		F2CIoTImDeviceSttusInfo_del(p->x.f2c_iot_im_device_sttus_info);
		break;
	case Itsk00126v2EAMPresent_fc2_iot_device_list_request_info:
		Itsk00126v2Request_del(p->x.fc2_iot_device_list_request_info);
		break;
	case Itsk00126v2EAMPresent_fc2_iot_device_list_response_info:
		F2CIoTDeviceListResponseInfo_del(p->x.fc2_iot_device_list_response_info);
		break;
	case Itsk00126v2EAMPresent_fc2_iot_device_list_reset_info:
		F2CIoTDeviceListResponseInfo_del(p->x.fc2_iot_device_list_reset_info);
		break;
	case Itsk00126v2EAMPresent_fc2_iot_device_sttus_info:
		F2CIoTDeviceSttusInfo_del(p->x.fc2_iot_device_sttus_info);
		break;
	default:
		break;
	}
}

void Itsk00126v2EAM_del(Itsk00126v2EAM *p)
{
	if (!p) return;
	Itsk00126v2EAM_purge(p);
	Dz1Free(p);
}

void Itsk00126v2EAM_dump(Itsk00126v2EAM *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Itsk00126v2EAMPresent_f2c_iot_im_device_sttus_info:
		Dz1Thread_printf(Dz1T("f2c_iot_im_device_sttus_info = ")); F2CIoTImDeviceSttusInfo_dump(p->x.f2c_iot_im_device_sttus_info, tab); 
		break;
	case Itsk00126v2EAMPresent_fc2_iot_device_list_request_info:
		Dz1Thread_printf(Dz1T("fc2_iot_device_list_request_info = ")); Itsk00126v2Request_dump(p->x.fc2_iot_device_list_request_info, tab); 
		break;
	case Itsk00126v2EAMPresent_fc2_iot_device_list_response_info:
		Dz1Thread_printf(Dz1T("fc2_iot_device_list_response_info = ")); F2CIoTDeviceListResponseInfo_dump(p->x.fc2_iot_device_list_response_info, tab); 
		break;
	case Itsk00126v2EAMPresent_fc2_iot_device_list_reset_info:
		Dz1Thread_printf(Dz1T("fc2_iot_device_list_reset_info = ")); F2CIoTDeviceListResponseInfo_dump(p->x.fc2_iot_device_list_reset_info, tab); 
		break;
	case Itsk00126v2EAMPresent_fc2_iot_device_sttus_info:
		Dz1Thread_printf(Dz1T("fc2_iot_device_sttus_info = ")); F2CIoTDeviceSttusInfo_dump(p->x.fc2_iot_device_sttus_info, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Itsk00126v2EAM
////////////////////////////////////////////////////////////////////////////////


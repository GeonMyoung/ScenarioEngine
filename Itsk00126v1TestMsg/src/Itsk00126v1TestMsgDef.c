////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Itsk00126v1TestMsgDef.h"

////////////////////////////////////////////////////////////////////////////////
// IoTImDeviceSttusInfo
IoTImDeviceSttusInfo *IoTImDeviceSttusInfo_new(Dz1Str iot_im_device_id, 
											   Dz1Str iot_im_device_link_sttus_code, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	IoTImDeviceSttusInfo *__internal_ret = (IoTImDeviceSttusInfo *)Dz1Calloc(sizeof(IoTImDeviceSttusInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(IoTImDeviceSttusInfo_delAndSetNull, (void *)&__internal_ret);
		
		if (iot_im_device_id && (__internal_ret->iot_im_device_id = Dz1Str_clone(iot_im_device_id, errp)) == NULL) ERR_OUT(errp);
		else if (iot_im_device_link_sttus_code && (__internal_ret->iot_im_device_link_sttus_code = Dz1Str_clone(iot_im_device_link_sttus_code, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (IoTImDeviceSttusInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t IoTImDeviceSttusInfo_copy(IoTImDeviceSttusInfo *dst, IoTImDeviceSttusInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->iot_im_device_id && (dst->iot_im_device_id = Dz1Str_clone(src->iot_im_device_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->iot_im_device_link_sttus_code && (dst->iot_im_device_link_sttus_code = Dz1Str_clone(src->iot_im_device_link_sttus_code, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

IoTImDeviceSttusInfo *IoTImDeviceSttusInfo_clone(IoTImDeviceSttusInfo *src, Dz1Error *err)
{
	IoTImDeviceSttusInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (IoTImDeviceSttusInfo *)Dz1Calloc(sizeof(IoTImDeviceSttusInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(IoTImDeviceSttusInfo_delAndSetNull, (void *)&dst);
		if (IoTImDeviceSttusInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (IoTImDeviceSttusInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void IoTImDeviceSttusInfo_purge(IoTImDeviceSttusInfo *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->iot_im_device_id);
	Dz1Str_del(p->iot_im_device_link_sttus_code);
}

void IoTImDeviceSttusInfo_del(IoTImDeviceSttusInfo *p)
{
	if (p == NULL) return;
	IoTImDeviceSttusInfo_purge(p);
	Dz1Free(p);
}

void IoTImDeviceSttusInfo_dump(IoTImDeviceSttusInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("iot_im_device_id = ")); Dz1Str_dump(p->iot_im_device_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("iot_im_device_link_sttus_code = ")); Dz1Str_dump(p->iot_im_device_link_sttus_code, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// IoTImDeviceSttusInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// IoTImDeviceSttusInfoList
static Dz1Error IoTImDeviceSttusInfoList_add(IoTImDeviceSttusInfoList *p, IoTImDeviceSttusInfo *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static IoTImDeviceSttusInfo *IoTImDeviceSttusInfoList_extract(IoTImDeviceSttusInfoList *p, IoTImDeviceSttusInfo *ptr)
{
	return (IoTImDeviceSttusInfo *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct IoTImDeviceSttusInfoListMkArrArg
{
	IoTImDeviceSttusInfo **arr;
	unsigned int idx;
} IoTImDeviceSttusInfoListMkArrArg;

static Dz1Error _IoTImDeviceSttusInfoList_get_array(void *ptr, IoTImDeviceSttusInfo *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	IoTImDeviceSttusInfoListMkArrArg *arg = (IoTImDeviceSttusInfoListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static IoTImDeviceSttusInfo **IoTImDeviceSttusInfoList_get_array(IoTImDeviceSttusInfoList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	IoTImDeviceSttusInfo **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (IoTImDeviceSttusInfo **)Dz1Calloc(sizeof(IoTImDeviceSttusInfo *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		IoTImDeviceSttusInfoListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _IoTImDeviceSttusInfoList_get_array, (void *)&arg);
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

static Dz1Error IoTImDeviceSttusInfoList_travelForward(IoTImDeviceSttusInfoList *p, Dz1Error (*func)(void *ptr, IoTImDeviceSttusInfo *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error IoTImDeviceSttusInfoList_travelBackward(IoTImDeviceSttusInfoList *p, Dz1Error (*func)(void *ptr, IoTImDeviceSttusInfo *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static IoTImDeviceSttusInfo *IoTImDeviceSttusInfoList_getHead(IoTImDeviceSttusInfoList *p)
{
	return (IoTImDeviceSttusInfo *)Dz1Fifo_getFirst(p->storage);
}

static unsigned int IoTImDeviceSttusInfoList_count(IoTImDeviceSttusInfoList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

IoTImDeviceSttusInfoList *IoTImDeviceSttusInfoList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	IoTImDeviceSttusInfoList *ret = (IoTImDeviceSttusInfoList *)Dz1Calloc(sizeof(IoTImDeviceSttusInfoList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(IoTImDeviceSttusInfoList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)IoTImDeviceSttusInfo_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = IoTImDeviceSttusInfoList_count;
			ret->travel = IoTImDeviceSttusInfoList_travelForward;
			ret->travelForward = IoTImDeviceSttusInfoList_travelForward;
			ret->travelBackward = IoTImDeviceSttusInfoList_travelBackward;
			ret->get_array = IoTImDeviceSttusInfoList_get_array;
			ret->add = IoTImDeviceSttusInfoList_add;
			ret->extract = IoTImDeviceSttusInfoList_extract;
			ret->getHead = IoTImDeviceSttusInfoList_getHead;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (IoTImDeviceSttusInfoList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _IoTImDeviceSttusInfoList_clone(void *ptr, IoTImDeviceSttusInfo *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	IoTImDeviceSttusInfoList *p = (IoTImDeviceSttusInfoList *)ptr;
	IoTImDeviceSttusInfo *cloned = IoTImDeviceSttusInfo_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

IoTImDeviceSttusInfoList *IoTImDeviceSttusInfoList_clone(IoTImDeviceSttusInfoList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	IoTImDeviceSttusInfoList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = IoTImDeviceSttusInfoList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(IoTImDeviceSttusInfoList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_IoTImDeviceSttusInfoList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (IoTImDeviceSttusInfoList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void IoTImDeviceSttusInfoList_purge(IoTImDeviceSttusInfoList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void IoTImDeviceSttusInfoList_del(IoTImDeviceSttusInfoList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _IoTImDeviceSttusInfoList_dump(void *ptr, IoTImDeviceSttusInfo *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); IoTImDeviceSttusInfo_dump(p, tab);
	return err;
}

void IoTImDeviceSttusInfoList_dump(IoTImDeviceSttusInfoList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _IoTImDeviceSttusInfoList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// IoTImDeviceSttusInfoList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTImDeviceSttusInfoData
C2CIoTImDeviceSttusInfoData *C2CIoTImDeviceSttusInfoData_new(Dz1Str local_center_id, 
															 Dz1Str iot_im_device_id_qty, 
															 IoTImDeviceSttusInfoList *iot_im_device_sttus_info_list, 
															 Dz1Str creat_dt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CIoTImDeviceSttusInfoData *__internal_ret = (C2CIoTImDeviceSttusInfoData *)Dz1Calloc(sizeof(C2CIoTImDeviceSttusInfoData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(C2CIoTImDeviceSttusInfoData_delAndSetNull, (void *)&__internal_ret);
		
		if (local_center_id && (__internal_ret->local_center_id = Dz1Str_clone(local_center_id, errp)) == NULL) ERR_OUT(errp);
		else if (iot_im_device_id_qty && (__internal_ret->iot_im_device_id_qty = Dz1Str_clone(iot_im_device_id_qty, errp)) == NULL) ERR_OUT(errp);
		else if (creat_dt && (__internal_ret->creat_dt = Dz1Str_clone(creat_dt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->iot_im_device_sttus_info_list = iot_im_device_sttus_info_list;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIoTImDeviceSttusInfoData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t C2CIoTImDeviceSttusInfoData_copy(C2CIoTImDeviceSttusInfoData *dst, C2CIoTImDeviceSttusInfoData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->local_center_id && (dst->local_center_id = Dz1Str_clone(src->local_center_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->iot_im_device_id_qty && (dst->iot_im_device_id_qty = Dz1Str_clone(src->iot_im_device_id_qty, errp)) == NULL) ERR_OUT(errp);
	else if (src->iot_im_device_sttus_info_list && (dst->iot_im_device_sttus_info_list = IoTImDeviceSttusInfoList_clone(src->iot_im_device_sttus_info_list, errp)) == NULL) ERR_OUT(errp);
	else if (src->creat_dt && (dst->creat_dt = Dz1Str_clone(src->creat_dt, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

C2CIoTImDeviceSttusInfoData *C2CIoTImDeviceSttusInfoData_clone(C2CIoTImDeviceSttusInfoData *src, Dz1Error *err)
{
	C2CIoTImDeviceSttusInfoData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (C2CIoTImDeviceSttusInfoData *)Dz1Calloc(sizeof(C2CIoTImDeviceSttusInfoData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(C2CIoTImDeviceSttusInfoData_delAndSetNull, (void *)&dst);
		if (C2CIoTImDeviceSttusInfoData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIoTImDeviceSttusInfoData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void C2CIoTImDeviceSttusInfoData_purge(C2CIoTImDeviceSttusInfoData *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->local_center_id);
	Dz1Str_del(p->iot_im_device_id_qty);
	IoTImDeviceSttusInfoList_del(p->iot_im_device_sttus_info_list);
	Dz1Str_del(p->creat_dt);
}

void C2CIoTImDeviceSttusInfoData_del(C2CIoTImDeviceSttusInfoData *p)
{
	if (p == NULL) return;
	C2CIoTImDeviceSttusInfoData_purge(p);
	Dz1Free(p);
}

void C2CIoTImDeviceSttusInfoData_dump(C2CIoTImDeviceSttusInfoData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("local_center_id = ")); Dz1Str_dump(p->local_center_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("iot_im_device_id_qty = ")); Dz1Str_dump(p->iot_im_device_id_qty, tab); 
		Dz1Thread_tprintf(tab, Dz1T("iot_im_device_sttus_info_list = ")); IoTImDeviceSttusInfoList_dump(p->iot_im_device_sttus_info_list, tab); 
		Dz1Thread_tprintf(tab, Dz1T("creat_dt = ")); Dz1Str_dump(p->creat_dt, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// C2CIoTImDeviceSttusInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTImDeviceSttusInfo
C2CIoTImDeviceSttusInfo *C2CIoTImDeviceSttusInfo_new(Dz1Str command, 
													 Dz1Str event_name, 
													 Dz1Str event_type, 
													 C2CIoTImDeviceSttusInfoData *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CIoTImDeviceSttusInfo *__internal_ret = (C2CIoTImDeviceSttusInfo *)Dz1Calloc(sizeof(C2CIoTImDeviceSttusInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(C2CIoTImDeviceSttusInfo_delAndSetNull, (void *)&__internal_ret);
		
		if (command && (__internal_ret->command = Dz1Str_clone(command, errp)) == NULL) ERR_OUT(errp);
		else if (event_name && (__internal_ret->event_name = Dz1Str_clone(event_name, errp)) == NULL) ERR_OUT(errp);
		else if (event_type && (__internal_ret->event_type = Dz1Str_clone(event_type, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->data = data;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIoTImDeviceSttusInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t C2CIoTImDeviceSttusInfo_copy(C2CIoTImDeviceSttusInfo *dst, C2CIoTImDeviceSttusInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->command && (dst->command = Dz1Str_clone(src->command, errp)) == NULL) ERR_OUT(errp);
	else if (src->event_name && (dst->event_name = Dz1Str_clone(src->event_name, errp)) == NULL) ERR_OUT(errp);
	else if (src->event_type && (dst->event_type = Dz1Str_clone(src->event_type, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = C2CIoTImDeviceSttusInfoData_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

C2CIoTImDeviceSttusInfo *C2CIoTImDeviceSttusInfo_clone(C2CIoTImDeviceSttusInfo *src, Dz1Error *err)
{
	C2CIoTImDeviceSttusInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (C2CIoTImDeviceSttusInfo *)Dz1Calloc(sizeof(C2CIoTImDeviceSttusInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(C2CIoTImDeviceSttusInfo_delAndSetNull, (void *)&dst);
		if (C2CIoTImDeviceSttusInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIoTImDeviceSttusInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void C2CIoTImDeviceSttusInfo_purge(C2CIoTImDeviceSttusInfo *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->command);
	Dz1Str_del(p->event_name);
	Dz1Str_del(p->event_type);
	C2CIoTImDeviceSttusInfoData_del(p->data);
}

void C2CIoTImDeviceSttusInfo_del(C2CIoTImDeviceSttusInfo *p)
{
	if (p == NULL) return;
	C2CIoTImDeviceSttusInfo_purge(p);
	Dz1Free(p);
}

void C2CIoTImDeviceSttusInfo_dump(C2CIoTImDeviceSttusInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("command = ")); Dz1Str_dump(p->command, tab); 
		Dz1Thread_tprintf(tab, Dz1T("event_name = ")); Dz1Str_dump(p->event_name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("event_type = ")); Dz1Str_dump(p->event_type, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("data = ")); C2CIoTImDeviceSttusInfoData_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// C2CIoTImDeviceSttusInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceListRequestInfoData
C2CIoTDeviceListRequestInfoData *C2CIoTDeviceListRequestInfoData_new(Dz1Str local_center_id, 
																	 Dz1Str event_name, 
																	 Dz1Str event_type, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CIoTDeviceListRequestInfoData *__internal_ret = (C2CIoTDeviceListRequestInfoData *)Dz1Calloc(sizeof(C2CIoTDeviceListRequestInfoData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(C2CIoTDeviceListRequestInfoData_delAndSetNull, (void *)&__internal_ret);
		
		if (local_center_id && (__internal_ret->local_center_id = Dz1Str_clone(local_center_id, errp)) == NULL) ERR_OUT(errp);
		else if (event_name && (__internal_ret->event_name = Dz1Str_clone(event_name, errp)) == NULL) ERR_OUT(errp);
		else if (event_type && (__internal_ret->event_type = Dz1Str_clone(event_type, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIoTDeviceListRequestInfoData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t C2CIoTDeviceListRequestInfoData_copy(C2CIoTDeviceListRequestInfoData *dst, C2CIoTDeviceListRequestInfoData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->local_center_id && (dst->local_center_id = Dz1Str_clone(src->local_center_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->event_name && (dst->event_name = Dz1Str_clone(src->event_name, errp)) == NULL) ERR_OUT(errp);
	else if (src->event_type && (dst->event_type = Dz1Str_clone(src->event_type, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

C2CIoTDeviceListRequestInfoData *C2CIoTDeviceListRequestInfoData_clone(C2CIoTDeviceListRequestInfoData *src, Dz1Error *err)
{
	C2CIoTDeviceListRequestInfoData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (C2CIoTDeviceListRequestInfoData *)Dz1Calloc(sizeof(C2CIoTDeviceListRequestInfoData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(C2CIoTDeviceListRequestInfoData_delAndSetNull, (void *)&dst);
		if (C2CIoTDeviceListRequestInfoData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIoTDeviceListRequestInfoData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void C2CIoTDeviceListRequestInfoData_purge(C2CIoTDeviceListRequestInfoData *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->local_center_id);
	Dz1Str_del(p->event_name);
	Dz1Str_del(p->event_type);
}

void C2CIoTDeviceListRequestInfoData_del(C2CIoTDeviceListRequestInfoData *p)
{
	if (p == NULL) return;
	C2CIoTDeviceListRequestInfoData_purge(p);
	Dz1Free(p);
}

void C2CIoTDeviceListRequestInfoData_dump(C2CIoTDeviceListRequestInfoData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("local_center_id = ")); Dz1Str_dump(p->local_center_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("event_name = ")); Dz1Str_dump(p->event_name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("event_type = ")); Dz1Str_dump(p->event_type, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// C2CIoTDeviceListRequestInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceListRequestInfo
C2CIoTDeviceListRequestInfo *C2CIoTDeviceListRequestInfo_new(Dz1Str command, 
															 C2CIoTDeviceListRequestInfoData *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CIoTDeviceListRequestInfo *__internal_ret = (C2CIoTDeviceListRequestInfo *)Dz1Calloc(sizeof(C2CIoTDeviceListRequestInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(C2CIoTDeviceListRequestInfo_delAndSetNull, (void *)&__internal_ret);
		
		if (command && (__internal_ret->command = Dz1Str_clone(command, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->data = data;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIoTDeviceListRequestInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t C2CIoTDeviceListRequestInfo_copy(C2CIoTDeviceListRequestInfo *dst, C2CIoTDeviceListRequestInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->command && (dst->command = Dz1Str_clone(src->command, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = C2CIoTDeviceListRequestInfoData_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

C2CIoTDeviceListRequestInfo *C2CIoTDeviceListRequestInfo_clone(C2CIoTDeviceListRequestInfo *src, Dz1Error *err)
{
	C2CIoTDeviceListRequestInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (C2CIoTDeviceListRequestInfo *)Dz1Calloc(sizeof(C2CIoTDeviceListRequestInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(C2CIoTDeviceListRequestInfo_delAndSetNull, (void *)&dst);
		if (C2CIoTDeviceListRequestInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIoTDeviceListRequestInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void C2CIoTDeviceListRequestInfo_purge(C2CIoTDeviceListRequestInfo *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->command);
	C2CIoTDeviceListRequestInfoData_del(p->data);
}

void C2CIoTDeviceListRequestInfo_del(C2CIoTDeviceListRequestInfo *p)
{
	if (p == NULL) return;
	C2CIoTDeviceListRequestInfo_purge(p);
	Dz1Free(p);
}

void C2CIoTDeviceListRequestInfo_dump(C2CIoTDeviceListRequestInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("command = ")); Dz1Str_dump(p->command, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("data = ")); C2CIoTDeviceListRequestInfoData_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// C2CIoTDeviceListRequestInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceEntry
C2CIoTDeviceEntry *C2CIoTDeviceEntry_new(Dz1Str iot_device_id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CIoTDeviceEntry *__internal_ret = (C2CIoTDeviceEntry *)Dz1Calloc(sizeof(C2CIoTDeviceEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(C2CIoTDeviceEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (iot_device_id && (__internal_ret->iot_device_id = Dz1Str_clone(iot_device_id, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIoTDeviceEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t C2CIoTDeviceEntry_copy(C2CIoTDeviceEntry *dst, C2CIoTDeviceEntry *src, Dz1Error *err)
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

C2CIoTDeviceEntry *C2CIoTDeviceEntry_clone(C2CIoTDeviceEntry *src, Dz1Error *err)
{
	C2CIoTDeviceEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (C2CIoTDeviceEntry *)Dz1Calloc(sizeof(C2CIoTDeviceEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(C2CIoTDeviceEntry_delAndSetNull, (void *)&dst);
		if (C2CIoTDeviceEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIoTDeviceEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void C2CIoTDeviceEntry_purge(C2CIoTDeviceEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->iot_device_id);
}

void C2CIoTDeviceEntry_del(C2CIoTDeviceEntry *p)
{
	if (p == NULL) return;
	C2CIoTDeviceEntry_purge(p);
	Dz1Free(p);
}

void C2CIoTDeviceEntry_dump(C2CIoTDeviceEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("iot_device_id = ")); Dz1Str_dump(p->iot_device_id, tab); 
	}
}
// C2CIoTDeviceEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceList
static Dz1Error C2CIoTDeviceList_add(C2CIoTDeviceList *p, C2CIoTDeviceEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static C2CIoTDeviceEntry *C2CIoTDeviceList_extract(C2CIoTDeviceList *p, C2CIoTDeviceEntry *ptr)
{
	return (C2CIoTDeviceEntry *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct C2CIoTDeviceListMkArrArg
{
	C2CIoTDeviceEntry **arr;
	unsigned int idx;
} C2CIoTDeviceListMkArrArg;

static Dz1Error _C2CIoTDeviceList_get_array(void *ptr, C2CIoTDeviceEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	C2CIoTDeviceListMkArrArg *arg = (C2CIoTDeviceListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static C2CIoTDeviceEntry **C2CIoTDeviceList_get_array(C2CIoTDeviceList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	C2CIoTDeviceEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (C2CIoTDeviceEntry **)Dz1Calloc(sizeof(C2CIoTDeviceEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		C2CIoTDeviceListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _C2CIoTDeviceList_get_array, (void *)&arg);
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

static Dz1Error C2CIoTDeviceList_travelForward(C2CIoTDeviceList *p, Dz1Error (*func)(void *ptr, C2CIoTDeviceEntry *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error C2CIoTDeviceList_travelBackward(C2CIoTDeviceList *p, Dz1Error (*func)(void *ptr, C2CIoTDeviceEntry *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static C2CIoTDeviceEntry *C2CIoTDeviceList_getHead(C2CIoTDeviceList *p)
{
	return (C2CIoTDeviceEntry *)Dz1Fifo_getFirst(p->storage);
}

static unsigned int C2CIoTDeviceList_count(C2CIoTDeviceList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

C2CIoTDeviceList *C2CIoTDeviceList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CIoTDeviceList *ret = (C2CIoTDeviceList *)Dz1Calloc(sizeof(C2CIoTDeviceList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(C2CIoTDeviceList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)C2CIoTDeviceEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = C2CIoTDeviceList_count;
			ret->travel = C2CIoTDeviceList_travelForward;
			ret->travelForward = C2CIoTDeviceList_travelForward;
			ret->travelBackward = C2CIoTDeviceList_travelBackward;
			ret->get_array = C2CIoTDeviceList_get_array;
			ret->add = C2CIoTDeviceList_add;
			ret->extract = C2CIoTDeviceList_extract;
			ret->getHead = C2CIoTDeviceList_getHead;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIoTDeviceList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _C2CIoTDeviceList_clone(void *ptr, C2CIoTDeviceEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	C2CIoTDeviceList *p = (C2CIoTDeviceList *)ptr;
	C2CIoTDeviceEntry *cloned = C2CIoTDeviceEntry_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

C2CIoTDeviceList *C2CIoTDeviceList_clone(C2CIoTDeviceList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CIoTDeviceList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = C2CIoTDeviceList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(C2CIoTDeviceList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_C2CIoTDeviceList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIoTDeviceList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void C2CIoTDeviceList_purge(C2CIoTDeviceList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void C2CIoTDeviceList_del(C2CIoTDeviceList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _C2CIoTDeviceList_dump(void *ptr, C2CIoTDeviceEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); C2CIoTDeviceEntry_dump(p, tab);
	return err;
}

void C2CIoTDeviceList_dump(C2CIoTDeviceList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _C2CIoTDeviceList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// C2CIoTDeviceList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CImDeviceEntry
C2CImDeviceEntry *C2CImDeviceEntry_new(Dz1Str iot_im_device_id, 
									   Dz1Str iot_device_id_qty, 
									   C2CIoTDeviceList *iot_device_list, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CImDeviceEntry *__internal_ret = (C2CImDeviceEntry *)Dz1Calloc(sizeof(C2CImDeviceEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(C2CImDeviceEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (iot_im_device_id && (__internal_ret->iot_im_device_id = Dz1Str_clone(iot_im_device_id, errp)) == NULL) ERR_OUT(errp);
		else if (iot_device_id_qty && (__internal_ret->iot_device_id_qty = Dz1Str_clone(iot_device_id_qty, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->iot_device_list = iot_device_list;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CImDeviceEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t C2CImDeviceEntry_copy(C2CImDeviceEntry *dst, C2CImDeviceEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->iot_im_device_id && (dst->iot_im_device_id = Dz1Str_clone(src->iot_im_device_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->iot_device_id_qty && (dst->iot_device_id_qty = Dz1Str_clone(src->iot_device_id_qty, errp)) == NULL) ERR_OUT(errp);
	else if (src->iot_device_list && (dst->iot_device_list = C2CIoTDeviceList_clone(src->iot_device_list, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

C2CImDeviceEntry *C2CImDeviceEntry_clone(C2CImDeviceEntry *src, Dz1Error *err)
{
	C2CImDeviceEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (C2CImDeviceEntry *)Dz1Calloc(sizeof(C2CImDeviceEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(C2CImDeviceEntry_delAndSetNull, (void *)&dst);
		if (C2CImDeviceEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CImDeviceEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void C2CImDeviceEntry_purge(C2CImDeviceEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->iot_im_device_id);
	Dz1Str_del(p->iot_device_id_qty);
	C2CIoTDeviceList_del(p->iot_device_list);
}

void C2CImDeviceEntry_del(C2CImDeviceEntry *p)
{
	if (p == NULL) return;
	C2CImDeviceEntry_purge(p);
	Dz1Free(p);
}

void C2CImDeviceEntry_dump(C2CImDeviceEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("iot_im_device_id = ")); Dz1Str_dump(p->iot_im_device_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("iot_device_id_qty = ")); Dz1Str_dump(p->iot_device_id_qty, tab); 
		Dz1Thread_tprintf(tab, Dz1T("iot_device_list = ")); C2CIoTDeviceList_dump(p->iot_device_list, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// C2CImDeviceEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CImDeviceList
static Dz1Error C2CImDeviceList_add(C2CImDeviceList *p, C2CImDeviceEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static C2CImDeviceEntry *C2CImDeviceList_extract(C2CImDeviceList *p, C2CImDeviceEntry *ptr)
{
	return (C2CImDeviceEntry *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct C2CImDeviceListMkArrArg
{
	C2CImDeviceEntry **arr;
	unsigned int idx;
} C2CImDeviceListMkArrArg;

static Dz1Error _C2CImDeviceList_get_array(void *ptr, C2CImDeviceEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	C2CImDeviceListMkArrArg *arg = (C2CImDeviceListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static C2CImDeviceEntry **C2CImDeviceList_get_array(C2CImDeviceList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	C2CImDeviceEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (C2CImDeviceEntry **)Dz1Calloc(sizeof(C2CImDeviceEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		C2CImDeviceListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _C2CImDeviceList_get_array, (void *)&arg);
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

static Dz1Error C2CImDeviceList_travelForward(C2CImDeviceList *p, Dz1Error (*func)(void *ptr, C2CImDeviceEntry *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error C2CImDeviceList_travelBackward(C2CImDeviceList *p, Dz1Error (*func)(void *ptr, C2CImDeviceEntry *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static C2CImDeviceEntry *C2CImDeviceList_getHead(C2CImDeviceList *p)
{
	return (C2CImDeviceEntry *)Dz1Fifo_getFirst(p->storage);
}

static unsigned int C2CImDeviceList_count(C2CImDeviceList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

C2CImDeviceList *C2CImDeviceList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CImDeviceList *ret = (C2CImDeviceList *)Dz1Calloc(sizeof(C2CImDeviceList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(C2CImDeviceList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)C2CImDeviceEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = C2CImDeviceList_count;
			ret->travel = C2CImDeviceList_travelForward;
			ret->travelForward = C2CImDeviceList_travelForward;
			ret->travelBackward = C2CImDeviceList_travelBackward;
			ret->get_array = C2CImDeviceList_get_array;
			ret->add = C2CImDeviceList_add;
			ret->extract = C2CImDeviceList_extract;
			ret->getHead = C2CImDeviceList_getHead;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CImDeviceList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _C2CImDeviceList_clone(void *ptr, C2CImDeviceEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	C2CImDeviceList *p = (C2CImDeviceList *)ptr;
	C2CImDeviceEntry *cloned = C2CImDeviceEntry_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

C2CImDeviceList *C2CImDeviceList_clone(C2CImDeviceList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CImDeviceList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = C2CImDeviceList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(C2CImDeviceList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_C2CImDeviceList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CImDeviceList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void C2CImDeviceList_purge(C2CImDeviceList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void C2CImDeviceList_del(C2CImDeviceList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _C2CImDeviceList_dump(void *ptr, C2CImDeviceEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); C2CImDeviceEntry_dump(p, tab);
	return err;
}

void C2CImDeviceList_dump(C2CImDeviceList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _C2CImDeviceList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// C2CImDeviceList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceListResponseInfoData
C2CIoTDeviceListResponseInfoData *C2CIoTDeviceListResponseInfoData_new(Dz1Str local_center_id, 
																	   Dz1Str event_name, 
																	   Dz1Str event_type, 
																	   Dz1Str iot_im_device_id_qty, 
																	   C2CImDeviceList *c2c_im_device_list, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CIoTDeviceListResponseInfoData *__internal_ret = (C2CIoTDeviceListResponseInfoData *)Dz1Calloc(sizeof(C2CIoTDeviceListResponseInfoData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(C2CIoTDeviceListResponseInfoData_delAndSetNull, (void *)&__internal_ret);
		
		if (local_center_id && (__internal_ret->local_center_id = Dz1Str_clone(local_center_id, errp)) == NULL) ERR_OUT(errp);
		else if (event_name && (__internal_ret->event_name = Dz1Str_clone(event_name, errp)) == NULL) ERR_OUT(errp);
		else if (event_type && (__internal_ret->event_type = Dz1Str_clone(event_type, errp)) == NULL) ERR_OUT(errp);
		else if (iot_im_device_id_qty && (__internal_ret->iot_im_device_id_qty = Dz1Str_clone(iot_im_device_id_qty, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->c2c_im_device_list = c2c_im_device_list;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIoTDeviceListResponseInfoData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t C2CIoTDeviceListResponseInfoData_copy(C2CIoTDeviceListResponseInfoData *dst, C2CIoTDeviceListResponseInfoData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->local_center_id && (dst->local_center_id = Dz1Str_clone(src->local_center_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->event_name && (dst->event_name = Dz1Str_clone(src->event_name, errp)) == NULL) ERR_OUT(errp);
	else if (src->event_type && (dst->event_type = Dz1Str_clone(src->event_type, errp)) == NULL) ERR_OUT(errp);
	else if (src->iot_im_device_id_qty && (dst->iot_im_device_id_qty = Dz1Str_clone(src->iot_im_device_id_qty, errp)) == NULL) ERR_OUT(errp);
	else if (src->c2c_im_device_list && (dst->c2c_im_device_list = C2CImDeviceList_clone(src->c2c_im_device_list, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

C2CIoTDeviceListResponseInfoData *C2CIoTDeviceListResponseInfoData_clone(C2CIoTDeviceListResponseInfoData *src, Dz1Error *err)
{
	C2CIoTDeviceListResponseInfoData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (C2CIoTDeviceListResponseInfoData *)Dz1Calloc(sizeof(C2CIoTDeviceListResponseInfoData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(C2CIoTDeviceListResponseInfoData_delAndSetNull, (void *)&dst);
		if (C2CIoTDeviceListResponseInfoData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIoTDeviceListResponseInfoData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void C2CIoTDeviceListResponseInfoData_purge(C2CIoTDeviceListResponseInfoData *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->local_center_id);
	Dz1Str_del(p->event_name);
	Dz1Str_del(p->event_type);
	Dz1Str_del(p->iot_im_device_id_qty);
	C2CImDeviceList_del(p->c2c_im_device_list);
}

void C2CIoTDeviceListResponseInfoData_del(C2CIoTDeviceListResponseInfoData *p)
{
	if (p == NULL) return;
	C2CIoTDeviceListResponseInfoData_purge(p);
	Dz1Free(p);
}

void C2CIoTDeviceListResponseInfoData_dump(C2CIoTDeviceListResponseInfoData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("local_center_id = ")); Dz1Str_dump(p->local_center_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("event_name = ")); Dz1Str_dump(p->event_name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("event_type = ")); Dz1Str_dump(p->event_type, tab); 
		Dz1Thread_tprintf(tab, Dz1T("iot_im_device_id_qty = ")); Dz1Str_dump(p->iot_im_device_id_qty, tab); 
		Dz1Thread_tprintf(tab, Dz1T("c2c_im_device_list = ")); C2CImDeviceList_dump(p->c2c_im_device_list, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// C2CIoTDeviceListResponseInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceListResponseInfo
C2CIoTDeviceListResponseInfo *C2CIoTDeviceListResponseInfo_new(Dz1Str command, 
															   C2CIoTDeviceListResponseInfoData *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CIoTDeviceListResponseInfo *__internal_ret = (C2CIoTDeviceListResponseInfo *)Dz1Calloc(sizeof(C2CIoTDeviceListResponseInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(C2CIoTDeviceListResponseInfo_delAndSetNull, (void *)&__internal_ret);
		
		if (command && (__internal_ret->command = Dz1Str_clone(command, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->data = data;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIoTDeviceListResponseInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t C2CIoTDeviceListResponseInfo_copy(C2CIoTDeviceListResponseInfo *dst, C2CIoTDeviceListResponseInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->command && (dst->command = Dz1Str_clone(src->command, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = C2CIoTDeviceListResponseInfoData_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

C2CIoTDeviceListResponseInfo *C2CIoTDeviceListResponseInfo_clone(C2CIoTDeviceListResponseInfo *src, Dz1Error *err)
{
	C2CIoTDeviceListResponseInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (C2CIoTDeviceListResponseInfo *)Dz1Calloc(sizeof(C2CIoTDeviceListResponseInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(C2CIoTDeviceListResponseInfo_delAndSetNull, (void *)&dst);
		if (C2CIoTDeviceListResponseInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIoTDeviceListResponseInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void C2CIoTDeviceListResponseInfo_purge(C2CIoTDeviceListResponseInfo *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->command);
	C2CIoTDeviceListResponseInfoData_del(p->data);
}

void C2CIoTDeviceListResponseInfo_del(C2CIoTDeviceListResponseInfo *p)
{
	if (p == NULL) return;
	C2CIoTDeviceListResponseInfo_purge(p);
	Dz1Free(p);
}

void C2CIoTDeviceListResponseInfo_dump(C2CIoTDeviceListResponseInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("command = ")); Dz1Str_dump(p->command, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("data = ")); C2CIoTDeviceListResponseInfoData_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// C2CIoTDeviceListResponseInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceSttusInfoEntry
C2CIoTDeviceSttusInfoEntry *C2CIoTDeviceSttusInfoEntry_new(Dz1Str iot_device_id, 
														   Dz1Str iot_device_sttus_code, 
														   Dz1Str btry_sttus_code, 
														   Dz1Str link_sttus_code, 
														   s64_t data_trnsmis_cont, 
														   Dz1Str iot_im_device_id, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CIoTDeviceSttusInfoEntry *__internal_ret = (C2CIoTDeviceSttusInfoEntry *)Dz1Calloc(sizeof(C2CIoTDeviceSttusInfoEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(C2CIoTDeviceSttusInfoEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (iot_device_id && (__internal_ret->iot_device_id = Dz1Str_clone(iot_device_id, errp)) == NULL) ERR_OUT(errp);
		else if (iot_device_sttus_code && (__internal_ret->iot_device_sttus_code = Dz1Str_clone(iot_device_sttus_code, errp)) == NULL) ERR_OUT(errp);
		else if (btry_sttus_code && (__internal_ret->btry_sttus_code = Dz1Str_clone(btry_sttus_code, errp)) == NULL) ERR_OUT(errp);
		else if (link_sttus_code && (__internal_ret->link_sttus_code = Dz1Str_clone(link_sttus_code, errp)) == NULL) ERR_OUT(errp);
		else if (iot_im_device_id && (__internal_ret->iot_im_device_id = Dz1Str_clone(iot_im_device_id, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->data_trnsmis_cont = data_trnsmis_cont;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIoTDeviceSttusInfoEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t C2CIoTDeviceSttusInfoEntry_copy(C2CIoTDeviceSttusInfoEntry *dst, C2CIoTDeviceSttusInfoEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->iot_device_id && (dst->iot_device_id = Dz1Str_clone(src->iot_device_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->iot_device_sttus_code && (dst->iot_device_sttus_code = Dz1Str_clone(src->iot_device_sttus_code, errp)) == NULL) ERR_OUT(errp);
	else if (src->btry_sttus_code && (dst->btry_sttus_code = Dz1Str_clone(src->btry_sttus_code, errp)) == NULL) ERR_OUT(errp);
	else if (src->link_sttus_code && (dst->link_sttus_code = Dz1Str_clone(src->link_sttus_code, errp)) == NULL) ERR_OUT(errp);
	else if (src->iot_im_device_id && (dst->iot_im_device_id = Dz1Str_clone(src->iot_im_device_id, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->data_trnsmis_cont = src->data_trnsmis_cont;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

C2CIoTDeviceSttusInfoEntry *C2CIoTDeviceSttusInfoEntry_clone(C2CIoTDeviceSttusInfoEntry *src, Dz1Error *err)
{
	C2CIoTDeviceSttusInfoEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (C2CIoTDeviceSttusInfoEntry *)Dz1Calloc(sizeof(C2CIoTDeviceSttusInfoEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(C2CIoTDeviceSttusInfoEntry_delAndSetNull, (void *)&dst);
		if (C2CIoTDeviceSttusInfoEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIoTDeviceSttusInfoEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void C2CIoTDeviceSttusInfoEntry_purge(C2CIoTDeviceSttusInfoEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->iot_device_id);
	Dz1Str_del(p->iot_device_sttus_code);
	Dz1Str_del(p->btry_sttus_code);
	Dz1Str_del(p->link_sttus_code);
	Dz1Str_del(p->iot_im_device_id);
}

void C2CIoTDeviceSttusInfoEntry_del(C2CIoTDeviceSttusInfoEntry *p)
{
	if (p == NULL) return;
	C2CIoTDeviceSttusInfoEntry_purge(p);
	Dz1Free(p);
}

void C2CIoTDeviceSttusInfoEntry_dump(C2CIoTDeviceSttusInfoEntry *p, int tab)
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
		Dz1Thread_tprintf(tab, Dz1T("iot_im_device_id = ")); Dz1Str_dump(p->iot_im_device_id, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// C2CIoTDeviceSttusInfoEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceSttusInfoList
static Dz1Error C2CIoTDeviceSttusInfoList_add(C2CIoTDeviceSttusInfoList *p, C2CIoTDeviceSttusInfoEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static C2CIoTDeviceSttusInfoEntry *C2CIoTDeviceSttusInfoList_extract(C2CIoTDeviceSttusInfoList *p, C2CIoTDeviceSttusInfoEntry *ptr)
{
	return (C2CIoTDeviceSttusInfoEntry *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct C2CIoTDeviceSttusInfoListMkArrArg
{
	C2CIoTDeviceSttusInfoEntry **arr;
	unsigned int idx;
} C2CIoTDeviceSttusInfoListMkArrArg;

static Dz1Error _C2CIoTDeviceSttusInfoList_get_array(void *ptr, C2CIoTDeviceSttusInfoEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	C2CIoTDeviceSttusInfoListMkArrArg *arg = (C2CIoTDeviceSttusInfoListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static C2CIoTDeviceSttusInfoEntry **C2CIoTDeviceSttusInfoList_get_array(C2CIoTDeviceSttusInfoList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	C2CIoTDeviceSttusInfoEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (C2CIoTDeviceSttusInfoEntry **)Dz1Calloc(sizeof(C2CIoTDeviceSttusInfoEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		C2CIoTDeviceSttusInfoListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _C2CIoTDeviceSttusInfoList_get_array, (void *)&arg);
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

static Dz1Error C2CIoTDeviceSttusInfoList_travelForward(C2CIoTDeviceSttusInfoList *p, Dz1Error (*func)(void *ptr, C2CIoTDeviceSttusInfoEntry *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error C2CIoTDeviceSttusInfoList_travelBackward(C2CIoTDeviceSttusInfoList *p, Dz1Error (*func)(void *ptr, C2CIoTDeviceSttusInfoEntry *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static C2CIoTDeviceSttusInfoEntry *C2CIoTDeviceSttusInfoList_getHead(C2CIoTDeviceSttusInfoList *p)
{
	return (C2CIoTDeviceSttusInfoEntry *)Dz1Fifo_getFirst(p->storage);
}

static unsigned int C2CIoTDeviceSttusInfoList_count(C2CIoTDeviceSttusInfoList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

C2CIoTDeviceSttusInfoList *C2CIoTDeviceSttusInfoList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CIoTDeviceSttusInfoList *ret = (C2CIoTDeviceSttusInfoList *)Dz1Calloc(sizeof(C2CIoTDeviceSttusInfoList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(C2CIoTDeviceSttusInfoList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)C2CIoTDeviceSttusInfoEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = C2CIoTDeviceSttusInfoList_count;
			ret->travel = C2CIoTDeviceSttusInfoList_travelForward;
			ret->travelForward = C2CIoTDeviceSttusInfoList_travelForward;
			ret->travelBackward = C2CIoTDeviceSttusInfoList_travelBackward;
			ret->get_array = C2CIoTDeviceSttusInfoList_get_array;
			ret->add = C2CIoTDeviceSttusInfoList_add;
			ret->extract = C2CIoTDeviceSttusInfoList_extract;
			ret->getHead = C2CIoTDeviceSttusInfoList_getHead;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIoTDeviceSttusInfoList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _C2CIoTDeviceSttusInfoList_clone(void *ptr, C2CIoTDeviceSttusInfoEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	C2CIoTDeviceSttusInfoList *p = (C2CIoTDeviceSttusInfoList *)ptr;
	C2CIoTDeviceSttusInfoEntry *cloned = C2CIoTDeviceSttusInfoEntry_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

C2CIoTDeviceSttusInfoList *C2CIoTDeviceSttusInfoList_clone(C2CIoTDeviceSttusInfoList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CIoTDeviceSttusInfoList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = C2CIoTDeviceSttusInfoList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(C2CIoTDeviceSttusInfoList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_C2CIoTDeviceSttusInfoList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIoTDeviceSttusInfoList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void C2CIoTDeviceSttusInfoList_purge(C2CIoTDeviceSttusInfoList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void C2CIoTDeviceSttusInfoList_del(C2CIoTDeviceSttusInfoList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _C2CIoTDeviceSttusInfoList_dump(void *ptr, C2CIoTDeviceSttusInfoEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); C2CIoTDeviceSttusInfoEntry_dump(p, tab);
	return err;
}

void C2CIoTDeviceSttusInfoList_dump(C2CIoTDeviceSttusInfoList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _C2CIoTDeviceSttusInfoList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// C2CIoTDeviceSttusInfoList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceSttusInfoData
C2CIoTDeviceSttusInfoData *C2CIoTDeviceSttusInfoData_new(Dz1Str local_center_id, 
														 Dz1Str iot_device_id_qty, 
														 C2CIoTDeviceSttusInfoList *iot_device_sttus_info_list, 
														 Dz1Str creat_dt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CIoTDeviceSttusInfoData *__internal_ret = (C2CIoTDeviceSttusInfoData *)Dz1Calloc(sizeof(C2CIoTDeviceSttusInfoData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(C2CIoTDeviceSttusInfoData_delAndSetNull, (void *)&__internal_ret);
		
		if (local_center_id && (__internal_ret->local_center_id = Dz1Str_clone(local_center_id, errp)) == NULL) ERR_OUT(errp);
		else if (iot_device_id_qty && (__internal_ret->iot_device_id_qty = Dz1Str_clone(iot_device_id_qty, errp)) == NULL) ERR_OUT(errp);
		else if (creat_dt && (__internal_ret->creat_dt = Dz1Str_clone(creat_dt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->iot_device_sttus_info_list = iot_device_sttus_info_list;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIoTDeviceSttusInfoData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t C2CIoTDeviceSttusInfoData_copy(C2CIoTDeviceSttusInfoData *dst, C2CIoTDeviceSttusInfoData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->local_center_id && (dst->local_center_id = Dz1Str_clone(src->local_center_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->iot_device_id_qty && (dst->iot_device_id_qty = Dz1Str_clone(src->iot_device_id_qty, errp)) == NULL) ERR_OUT(errp);
	else if (src->iot_device_sttus_info_list && (dst->iot_device_sttus_info_list = C2CIoTDeviceSttusInfoList_clone(src->iot_device_sttus_info_list, errp)) == NULL) ERR_OUT(errp);
	else if (src->creat_dt && (dst->creat_dt = Dz1Str_clone(src->creat_dt, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

C2CIoTDeviceSttusInfoData *C2CIoTDeviceSttusInfoData_clone(C2CIoTDeviceSttusInfoData *src, Dz1Error *err)
{
	C2CIoTDeviceSttusInfoData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (C2CIoTDeviceSttusInfoData *)Dz1Calloc(sizeof(C2CIoTDeviceSttusInfoData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(C2CIoTDeviceSttusInfoData_delAndSetNull, (void *)&dst);
		if (C2CIoTDeviceSttusInfoData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIoTDeviceSttusInfoData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void C2CIoTDeviceSttusInfoData_purge(C2CIoTDeviceSttusInfoData *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->local_center_id);
	Dz1Str_del(p->iot_device_id_qty);
	C2CIoTDeviceSttusInfoList_del(p->iot_device_sttus_info_list);
	Dz1Str_del(p->creat_dt);
}

void C2CIoTDeviceSttusInfoData_del(C2CIoTDeviceSttusInfoData *p)
{
	if (p == NULL) return;
	C2CIoTDeviceSttusInfoData_purge(p);
	Dz1Free(p);
}

void C2CIoTDeviceSttusInfoData_dump(C2CIoTDeviceSttusInfoData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("local_center_id = ")); Dz1Str_dump(p->local_center_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("iot_device_id_qty = ")); Dz1Str_dump(p->iot_device_id_qty, tab); 
		Dz1Thread_tprintf(tab, Dz1T("iot_device_sttus_info_list = ")); C2CIoTDeviceSttusInfoList_dump(p->iot_device_sttus_info_list, tab); 
		Dz1Thread_tprintf(tab, Dz1T("creat_dt = ")); Dz1Str_dump(p->creat_dt, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// C2CIoTDeviceSttusInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceSttusInfo
C2CIoTDeviceSttusInfo *C2CIoTDeviceSttusInfo_new(Dz1Str command, 
												 C2CIoTDeviceSttusInfoData *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CIoTDeviceSttusInfo *__internal_ret = (C2CIoTDeviceSttusInfo *)Dz1Calloc(sizeof(C2CIoTDeviceSttusInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(C2CIoTDeviceSttusInfo_delAndSetNull, (void *)&__internal_ret);
		
		if (command && (__internal_ret->command = Dz1Str_clone(command, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->data = data;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIoTDeviceSttusInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t C2CIoTDeviceSttusInfo_copy(C2CIoTDeviceSttusInfo *dst, C2CIoTDeviceSttusInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->command && (dst->command = Dz1Str_clone(src->command, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = C2CIoTDeviceSttusInfoData_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

C2CIoTDeviceSttusInfo *C2CIoTDeviceSttusInfo_clone(C2CIoTDeviceSttusInfo *src, Dz1Error *err)
{
	C2CIoTDeviceSttusInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (C2CIoTDeviceSttusInfo *)Dz1Calloc(sizeof(C2CIoTDeviceSttusInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(C2CIoTDeviceSttusInfo_delAndSetNull, (void *)&dst);
		if (C2CIoTDeviceSttusInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIoTDeviceSttusInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void C2CIoTDeviceSttusInfo_purge(C2CIoTDeviceSttusInfo *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->command);
	C2CIoTDeviceSttusInfoData_del(p->data);
}

void C2CIoTDeviceSttusInfo_del(C2CIoTDeviceSttusInfo *p)
{
	if (p == NULL) return;
	C2CIoTDeviceSttusInfo_purge(p);
	Dz1Free(p);
}

void C2CIoTDeviceSttusInfo_dump(C2CIoTDeviceSttusInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("command = ")); Dz1Str_dump(p->command, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("data = ")); C2CIoTDeviceSttusInfoData_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// C2CIoTDeviceSttusInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CSafetySignalListRequestInfoData
C2CSafetySignalListRequestInfoData *C2CSafetySignalListRequestInfoData_new(Dz1Str local_center_id, 
																		   Dz1Str event_name, 
																		   Dz1Str event_type, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CSafetySignalListRequestInfoData *__internal_ret = (C2CSafetySignalListRequestInfoData *)Dz1Calloc(sizeof(C2CSafetySignalListRequestInfoData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(C2CSafetySignalListRequestInfoData_delAndSetNull, (void *)&__internal_ret);
		
		if (local_center_id && (__internal_ret->local_center_id = Dz1Str_clone(local_center_id, errp)) == NULL) ERR_OUT(errp);
		else if (event_name && (__internal_ret->event_name = Dz1Str_clone(event_name, errp)) == NULL) ERR_OUT(errp);
		else if (event_type && (__internal_ret->event_type = Dz1Str_clone(event_type, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CSafetySignalListRequestInfoData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t C2CSafetySignalListRequestInfoData_copy(C2CSafetySignalListRequestInfoData *dst, C2CSafetySignalListRequestInfoData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->local_center_id && (dst->local_center_id = Dz1Str_clone(src->local_center_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->event_name && (dst->event_name = Dz1Str_clone(src->event_name, errp)) == NULL) ERR_OUT(errp);
	else if (src->event_type && (dst->event_type = Dz1Str_clone(src->event_type, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

C2CSafetySignalListRequestInfoData *C2CSafetySignalListRequestInfoData_clone(C2CSafetySignalListRequestInfoData *src, Dz1Error *err)
{
	C2CSafetySignalListRequestInfoData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (C2CSafetySignalListRequestInfoData *)Dz1Calloc(sizeof(C2CSafetySignalListRequestInfoData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(C2CSafetySignalListRequestInfoData_delAndSetNull, (void *)&dst);
		if (C2CSafetySignalListRequestInfoData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CSafetySignalListRequestInfoData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void C2CSafetySignalListRequestInfoData_purge(C2CSafetySignalListRequestInfoData *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->local_center_id);
	Dz1Str_del(p->event_name);
	Dz1Str_del(p->event_type);
}

void C2CSafetySignalListRequestInfoData_del(C2CSafetySignalListRequestInfoData *p)
{
	if (p == NULL) return;
	C2CSafetySignalListRequestInfoData_purge(p);
	Dz1Free(p);
}

void C2CSafetySignalListRequestInfoData_dump(C2CSafetySignalListRequestInfoData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("local_center_id = ")); Dz1Str_dump(p->local_center_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("event_name = ")); Dz1Str_dump(p->event_name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("event_type = ")); Dz1Str_dump(p->event_type, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// C2CSafetySignalListRequestInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CSafetySignalListRequestInfo
C2CSafetySignalListRequestInfo *C2CSafetySignalListRequestInfo_new(Dz1Str command, 
																   C2CSafetySignalListRequestInfoData *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CSafetySignalListRequestInfo *__internal_ret = (C2CSafetySignalListRequestInfo *)Dz1Calloc(sizeof(C2CSafetySignalListRequestInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(C2CSafetySignalListRequestInfo_delAndSetNull, (void *)&__internal_ret);
		
		if (command && (__internal_ret->command = Dz1Str_clone(command, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->data = data;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CSafetySignalListRequestInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t C2CSafetySignalListRequestInfo_copy(C2CSafetySignalListRequestInfo *dst, C2CSafetySignalListRequestInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->command && (dst->command = Dz1Str_clone(src->command, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = C2CSafetySignalListRequestInfoData_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

C2CSafetySignalListRequestInfo *C2CSafetySignalListRequestInfo_clone(C2CSafetySignalListRequestInfo *src, Dz1Error *err)
{
	C2CSafetySignalListRequestInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (C2CSafetySignalListRequestInfo *)Dz1Calloc(sizeof(C2CSafetySignalListRequestInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(C2CSafetySignalListRequestInfo_delAndSetNull, (void *)&dst);
		if (C2CSafetySignalListRequestInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CSafetySignalListRequestInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void C2CSafetySignalListRequestInfo_purge(C2CSafetySignalListRequestInfo *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->command);
	C2CSafetySignalListRequestInfoData_del(p->data);
}

void C2CSafetySignalListRequestInfo_del(C2CSafetySignalListRequestInfo *p)
{
	if (p == NULL) return;
	C2CSafetySignalListRequestInfo_purge(p);
	Dz1Free(p);
}

void C2CSafetySignalListRequestInfo_dump(C2CSafetySignalListRequestInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("command = ")); Dz1Str_dump(p->command, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("data = ")); C2CSafetySignalListRequestInfoData_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// C2CSafetySignalListRequestInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CSafetySignalInfo
C2CSafetySignalInfo *C2CSafetySignalInfo_new(Dz1Str safety_signal_id, 
											 Dz1Str administ_zone_code, 
											 Dz1Str road_code, 
											 real64_t lc_lat, 
											 real64_t lc_lng, 
											 Dz1Str safety_signal_ty_code, 
											 Dz1Str safety_signal_sttus_code, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CSafetySignalInfo *__internal_ret = (C2CSafetySignalInfo *)Dz1Calloc(sizeof(C2CSafetySignalInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(C2CSafetySignalInfo_delAndSetNull, (void *)&__internal_ret);
		
		if (safety_signal_id && (__internal_ret->safety_signal_id = Dz1Str_clone(safety_signal_id, errp)) == NULL) ERR_OUT(errp);
		else if (administ_zone_code && (__internal_ret->administ_zone_code = Dz1Str_clone(administ_zone_code, errp)) == NULL) ERR_OUT(errp);
		else if (road_code && (__internal_ret->road_code = Dz1Str_clone(road_code, errp)) == NULL) ERR_OUT(errp);
		else if (safety_signal_ty_code && (__internal_ret->safety_signal_ty_code = Dz1Str_clone(safety_signal_ty_code, errp)) == NULL) ERR_OUT(errp);
		else if (safety_signal_sttus_code && (__internal_ret->safety_signal_sttus_code = Dz1Str_clone(safety_signal_sttus_code, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->lc_lat = lc_lat;
			__internal_ret->lc_lng = lc_lng;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CSafetySignalInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t C2CSafetySignalInfo_copy(C2CSafetySignalInfo *dst, C2CSafetySignalInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->safety_signal_id && (dst->safety_signal_id = Dz1Str_clone(src->safety_signal_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->administ_zone_code && (dst->administ_zone_code = Dz1Str_clone(src->administ_zone_code, errp)) == NULL) ERR_OUT(errp);
	else if (src->road_code && (dst->road_code = Dz1Str_clone(src->road_code, errp)) == NULL) ERR_OUT(errp);
	else if (src->safety_signal_ty_code && (dst->safety_signal_ty_code = Dz1Str_clone(src->safety_signal_ty_code, errp)) == NULL) ERR_OUT(errp);
	else if (src->safety_signal_sttus_code && (dst->safety_signal_sttus_code = Dz1Str_clone(src->safety_signal_sttus_code, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->lc_lat = src->lc_lat;
		dst->lc_lng = src->lc_lng;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

C2CSafetySignalInfo *C2CSafetySignalInfo_clone(C2CSafetySignalInfo *src, Dz1Error *err)
{
	C2CSafetySignalInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (C2CSafetySignalInfo *)Dz1Calloc(sizeof(C2CSafetySignalInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(C2CSafetySignalInfo_delAndSetNull, (void *)&dst);
		if (C2CSafetySignalInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CSafetySignalInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void C2CSafetySignalInfo_purge(C2CSafetySignalInfo *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->safety_signal_id);
	Dz1Str_del(p->administ_zone_code);
	Dz1Str_del(p->road_code);
	Dz1Str_del(p->safety_signal_ty_code);
	Dz1Str_del(p->safety_signal_sttus_code);
}

void C2CSafetySignalInfo_del(C2CSafetySignalInfo *p)
{
	if (p == NULL) return;
	C2CSafetySignalInfo_purge(p);
	Dz1Free(p);
}

void C2CSafetySignalInfo_dump(C2CSafetySignalInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("safety_signal_id = ")); Dz1Str_dump(p->safety_signal_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("administ_zone_code = ")); Dz1Str_dump(p->administ_zone_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("road_code = ")); Dz1Str_dump(p->road_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("lc_lat = ")); Dz1Real64_dump(&p->lc_lat, tab); 
		Dz1Thread_tprintf(tab, Dz1T("lc_lng = ")); Dz1Real64_dump(&p->lc_lng, tab); 
		Dz1Thread_tprintf(tab, Dz1T("safety_signal_ty_code = ")); Dz1Str_dump(p->safety_signal_ty_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("safety_signal_sttus_code = ")); Dz1Str_dump(p->safety_signal_sttus_code, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// C2CSafetySignalInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CSafetySignalInfoList
static Dz1Error C2CSafetySignalInfoList_add(C2CSafetySignalInfoList *p, C2CSafetySignalInfo *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static C2CSafetySignalInfo *C2CSafetySignalInfoList_extract(C2CSafetySignalInfoList *p, C2CSafetySignalInfo *ptr)
{
	return (C2CSafetySignalInfo *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct C2CSafetySignalInfoListMkArrArg
{
	C2CSafetySignalInfo **arr;
	unsigned int idx;
} C2CSafetySignalInfoListMkArrArg;

static Dz1Error _C2CSafetySignalInfoList_get_array(void *ptr, C2CSafetySignalInfo *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	C2CSafetySignalInfoListMkArrArg *arg = (C2CSafetySignalInfoListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static C2CSafetySignalInfo **C2CSafetySignalInfoList_get_array(C2CSafetySignalInfoList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	C2CSafetySignalInfo **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (C2CSafetySignalInfo **)Dz1Calloc(sizeof(C2CSafetySignalInfo *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		C2CSafetySignalInfoListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _C2CSafetySignalInfoList_get_array, (void *)&arg);
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

static Dz1Error C2CSafetySignalInfoList_travelForward(C2CSafetySignalInfoList *p, Dz1Error (*func)(void *ptr, C2CSafetySignalInfo *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error C2CSafetySignalInfoList_travelBackward(C2CSafetySignalInfoList *p, Dz1Error (*func)(void *ptr, C2CSafetySignalInfo *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static C2CSafetySignalInfo *C2CSafetySignalInfoList_getHead(C2CSafetySignalInfoList *p)
{
	return (C2CSafetySignalInfo *)Dz1Fifo_getFirst(p->storage);
}

static unsigned int C2CSafetySignalInfoList_count(C2CSafetySignalInfoList *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

C2CSafetySignalInfoList *C2CSafetySignalInfoList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CSafetySignalInfoList *ret = (C2CSafetySignalInfoList *)Dz1Calloc(sizeof(C2CSafetySignalInfoList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(C2CSafetySignalInfoList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)C2CSafetySignalInfo_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = C2CSafetySignalInfoList_count;
			ret->travel = C2CSafetySignalInfoList_travelForward;
			ret->travelForward = C2CSafetySignalInfoList_travelForward;
			ret->travelBackward = C2CSafetySignalInfoList_travelBackward;
			ret->get_array = C2CSafetySignalInfoList_get_array;
			ret->add = C2CSafetySignalInfoList_add;
			ret->extract = C2CSafetySignalInfoList_extract;
			ret->getHead = C2CSafetySignalInfoList_getHead;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CSafetySignalInfoList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _C2CSafetySignalInfoList_clone(void *ptr, C2CSafetySignalInfo *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	C2CSafetySignalInfoList *p = (C2CSafetySignalInfoList *)ptr;
	C2CSafetySignalInfo *cloned = C2CSafetySignalInfo_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

C2CSafetySignalInfoList *C2CSafetySignalInfoList_clone(C2CSafetySignalInfoList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CSafetySignalInfoList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = C2CSafetySignalInfoList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(C2CSafetySignalInfoList_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_C2CSafetySignalInfoList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CSafetySignalInfoList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void C2CSafetySignalInfoList_purge(C2CSafetySignalInfoList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void C2CSafetySignalInfoList_del(C2CSafetySignalInfoList *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _C2CSafetySignalInfoList_dump(void *ptr, C2CSafetySignalInfo *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); C2CSafetySignalInfo_dump(p, tab);
	return err;
}

void C2CSafetySignalInfoList_dump(C2CSafetySignalInfoList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _C2CSafetySignalInfoList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// C2CSafetySignalInfoList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIotDeviceListSignalEntry
C2CIotDeviceListSignalEntry *C2CIotDeviceListSignalEntry_new(Dz1Str iot_device_id, 
															 Dz1Str safety_signal_id_qty, 
															 C2CSafetySignalInfoList *c2c_safety_signal_info_list, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CIotDeviceListSignalEntry *__internal_ret = (C2CIotDeviceListSignalEntry *)Dz1Calloc(sizeof(C2CIotDeviceListSignalEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(C2CIotDeviceListSignalEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (iot_device_id && (__internal_ret->iot_device_id = Dz1Str_clone(iot_device_id, errp)) == NULL) ERR_OUT(errp);
		else if (safety_signal_id_qty && (__internal_ret->safety_signal_id_qty = Dz1Str_clone(safety_signal_id_qty, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->c2c_safety_signal_info_list = c2c_safety_signal_info_list;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIotDeviceListSignalEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t C2CIotDeviceListSignalEntry_copy(C2CIotDeviceListSignalEntry *dst, C2CIotDeviceListSignalEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->iot_device_id && (dst->iot_device_id = Dz1Str_clone(src->iot_device_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->safety_signal_id_qty && (dst->safety_signal_id_qty = Dz1Str_clone(src->safety_signal_id_qty, errp)) == NULL) ERR_OUT(errp);
	else if (src->c2c_safety_signal_info_list && (dst->c2c_safety_signal_info_list = C2CSafetySignalInfoList_clone(src->c2c_safety_signal_info_list, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

C2CIotDeviceListSignalEntry *C2CIotDeviceListSignalEntry_clone(C2CIotDeviceListSignalEntry *src, Dz1Error *err)
{
	C2CIotDeviceListSignalEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (C2CIotDeviceListSignalEntry *)Dz1Calloc(sizeof(C2CIotDeviceListSignalEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(C2CIotDeviceListSignalEntry_delAndSetNull, (void *)&dst);
		if (C2CIotDeviceListSignalEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIotDeviceListSignalEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void C2CIotDeviceListSignalEntry_purge(C2CIotDeviceListSignalEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->iot_device_id);
	Dz1Str_del(p->safety_signal_id_qty);
	C2CSafetySignalInfoList_del(p->c2c_safety_signal_info_list);
}

void C2CIotDeviceListSignalEntry_del(C2CIotDeviceListSignalEntry *p)
{
	if (p == NULL) return;
	C2CIotDeviceListSignalEntry_purge(p);
	Dz1Free(p);
}

void C2CIotDeviceListSignalEntry_dump(C2CIotDeviceListSignalEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("iot_device_id = ")); Dz1Str_dump(p->iot_device_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("safety_signal_id_qty = ")); Dz1Str_dump(p->safety_signal_id_qty, tab); 
		Dz1Thread_tprintf(tab, Dz1T("c2c_safety_signal_info_list = ")); C2CSafetySignalInfoList_dump(p->c2c_safety_signal_info_list, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// C2CIotDeviceListSignalEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIotDeviceListSignal
static Dz1Error C2CIotDeviceListSignal_add(C2CIotDeviceListSignal *p, C2CIotDeviceListSignalEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static C2CIotDeviceListSignalEntry *C2CIotDeviceListSignal_extract(C2CIotDeviceListSignal *p, C2CIotDeviceListSignalEntry *ptr)
{
	return (C2CIotDeviceListSignalEntry *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct C2CIotDeviceListSignalMkArrArg
{
	C2CIotDeviceListSignalEntry **arr;
	unsigned int idx;
} C2CIotDeviceListSignalMkArrArg;

static Dz1Error _C2CIotDeviceListSignal_get_array(void *ptr, C2CIotDeviceListSignalEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	C2CIotDeviceListSignalMkArrArg *arg = (C2CIotDeviceListSignalMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static C2CIotDeviceListSignalEntry **C2CIotDeviceListSignal_get_array(C2CIotDeviceListSignal *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	C2CIotDeviceListSignalEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (C2CIotDeviceListSignalEntry **)Dz1Calloc(sizeof(C2CIotDeviceListSignalEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		C2CIotDeviceListSignalMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _C2CIotDeviceListSignal_get_array, (void *)&arg);
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

static Dz1Error C2CIotDeviceListSignal_travelForward(C2CIotDeviceListSignal *p, Dz1Error (*func)(void *ptr, C2CIotDeviceListSignalEntry *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error C2CIotDeviceListSignal_travelBackward(C2CIotDeviceListSignal *p, Dz1Error (*func)(void *ptr, C2CIotDeviceListSignalEntry *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static C2CIotDeviceListSignalEntry *C2CIotDeviceListSignal_getHead(C2CIotDeviceListSignal *p)
{
	return (C2CIotDeviceListSignalEntry *)Dz1Fifo_getFirst(p->storage);
}

static unsigned int C2CIotDeviceListSignal_count(C2CIotDeviceListSignal *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

C2CIotDeviceListSignal *C2CIotDeviceListSignal_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CIotDeviceListSignal *ret = (C2CIotDeviceListSignal *)Dz1Calloc(sizeof(C2CIotDeviceListSignal), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(C2CIotDeviceListSignal_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)C2CIotDeviceListSignalEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = C2CIotDeviceListSignal_count;
			ret->travel = C2CIotDeviceListSignal_travelForward;
			ret->travelForward = C2CIotDeviceListSignal_travelForward;
			ret->travelBackward = C2CIotDeviceListSignal_travelBackward;
			ret->get_array = C2CIotDeviceListSignal_get_array;
			ret->add = C2CIotDeviceListSignal_add;
			ret->extract = C2CIotDeviceListSignal_extract;
			ret->getHead = C2CIotDeviceListSignal_getHead;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIotDeviceListSignal_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _C2CIotDeviceListSignal_clone(void *ptr, C2CIotDeviceListSignalEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	C2CIotDeviceListSignal *p = (C2CIotDeviceListSignal *)ptr;
	C2CIotDeviceListSignalEntry *cloned = C2CIotDeviceListSignalEntry_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

C2CIotDeviceListSignal *C2CIotDeviceListSignal_clone(C2CIotDeviceListSignal *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CIotDeviceListSignal *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = C2CIotDeviceListSignal_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(C2CIotDeviceListSignal_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_C2CIotDeviceListSignal_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CIotDeviceListSignal_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void C2CIotDeviceListSignal_purge(C2CIotDeviceListSignal *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void C2CIotDeviceListSignal_del(C2CIotDeviceListSignal *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _C2CIotDeviceListSignal_dump(void *ptr, C2CIotDeviceListSignalEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); C2CIotDeviceListSignalEntry_dump(p, tab);
	return err;
}

void C2CIotDeviceListSignal_dump(C2CIotDeviceListSignal *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _C2CIotDeviceListSignal_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// C2CIotDeviceListSignal
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CImDeviceListSignalEntry
C2CImDeviceListSignalEntry *C2CImDeviceListSignalEntry_new(Dz1Str iot_im_device_id, 
														   Dz1Str iot_device_id_qty, 
														   C2CIotDeviceListSignal *c2c_iot_device_list, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CImDeviceListSignalEntry *__internal_ret = (C2CImDeviceListSignalEntry *)Dz1Calloc(sizeof(C2CImDeviceListSignalEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(C2CImDeviceListSignalEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (iot_im_device_id && (__internal_ret->iot_im_device_id = Dz1Str_clone(iot_im_device_id, errp)) == NULL) ERR_OUT(errp);
		else if (iot_device_id_qty && (__internal_ret->iot_device_id_qty = Dz1Str_clone(iot_device_id_qty, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->c2c_iot_device_list = c2c_iot_device_list;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CImDeviceListSignalEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t C2CImDeviceListSignalEntry_copy(C2CImDeviceListSignalEntry *dst, C2CImDeviceListSignalEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->iot_im_device_id && (dst->iot_im_device_id = Dz1Str_clone(src->iot_im_device_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->iot_device_id_qty && (dst->iot_device_id_qty = Dz1Str_clone(src->iot_device_id_qty, errp)) == NULL) ERR_OUT(errp);
	else if (src->c2c_iot_device_list && (dst->c2c_iot_device_list = C2CIotDeviceListSignal_clone(src->c2c_iot_device_list, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

C2CImDeviceListSignalEntry *C2CImDeviceListSignalEntry_clone(C2CImDeviceListSignalEntry *src, Dz1Error *err)
{
	C2CImDeviceListSignalEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (C2CImDeviceListSignalEntry *)Dz1Calloc(sizeof(C2CImDeviceListSignalEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(C2CImDeviceListSignalEntry_delAndSetNull, (void *)&dst);
		if (C2CImDeviceListSignalEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CImDeviceListSignalEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void C2CImDeviceListSignalEntry_purge(C2CImDeviceListSignalEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->iot_im_device_id);
	Dz1Str_del(p->iot_device_id_qty);
	C2CIotDeviceListSignal_del(p->c2c_iot_device_list);
}

void C2CImDeviceListSignalEntry_del(C2CImDeviceListSignalEntry *p)
{
	if (p == NULL) return;
	C2CImDeviceListSignalEntry_purge(p);
	Dz1Free(p);
}

void C2CImDeviceListSignalEntry_dump(C2CImDeviceListSignalEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("iot_im_device_id = ")); Dz1Str_dump(p->iot_im_device_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("iot_device_id_qty = ")); Dz1Str_dump(p->iot_device_id_qty, tab); 
		Dz1Thread_tprintf(tab, Dz1T("c2c_iot_device_list = ")); C2CIotDeviceListSignal_dump(p->c2c_iot_device_list, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// C2CImDeviceListSignalEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CImDeviceListSignal
static Dz1Error C2CImDeviceListSignal_add(C2CImDeviceListSignal *p, C2CImDeviceListSignalEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

static C2CImDeviceListSignalEntry *C2CImDeviceListSignal_extract(C2CImDeviceListSignal *p, C2CImDeviceListSignalEntry *ptr)
{
	return (C2CImDeviceListSignalEntry *)Dz1Fifo_extract(p->storage, ptr);
}

typedef struct C2CImDeviceListSignalMkArrArg
{
	C2CImDeviceListSignalEntry **arr;
	unsigned int idx;
} C2CImDeviceListSignalMkArrArg;

static Dz1Error _C2CImDeviceListSignal_get_array(void *ptr, C2CImDeviceListSignalEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	C2CImDeviceListSignalMkArrArg *arg = (C2CImDeviceListSignalMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static C2CImDeviceListSignalEntry **C2CImDeviceListSignal_get_array(C2CImDeviceListSignal *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	C2CImDeviceListSignalEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (C2CImDeviceListSignalEntry **)Dz1Calloc(sizeof(C2CImDeviceListSignalEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		C2CImDeviceListSignalMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _C2CImDeviceListSignal_get_array, (void *)&arg);
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

static Dz1Error C2CImDeviceListSignal_travelForward(C2CImDeviceListSignal *p, Dz1Error (*func)(void *ptr, C2CImDeviceListSignalEntry *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error C2CImDeviceListSignal_travelBackward(C2CImDeviceListSignal *p, Dz1Error (*func)(void *ptr, C2CImDeviceListSignalEntry *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static C2CImDeviceListSignalEntry *C2CImDeviceListSignal_getHead(C2CImDeviceListSignal *p)
{
	return (C2CImDeviceListSignalEntry *)Dz1Fifo_getFirst(p->storage);
}

static unsigned int C2CImDeviceListSignal_count(C2CImDeviceListSignal *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

C2CImDeviceListSignal *C2CImDeviceListSignal_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CImDeviceListSignal *ret = (C2CImDeviceListSignal *)Dz1Calloc(sizeof(C2CImDeviceListSignal), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(C2CImDeviceListSignal_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)C2CImDeviceListSignalEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = C2CImDeviceListSignal_count;
			ret->travel = C2CImDeviceListSignal_travelForward;
			ret->travelForward = C2CImDeviceListSignal_travelForward;
			ret->travelBackward = C2CImDeviceListSignal_travelBackward;
			ret->get_array = C2CImDeviceListSignal_get_array;
			ret->add = C2CImDeviceListSignal_add;
			ret->extract = C2CImDeviceListSignal_extract;
			ret->getHead = C2CImDeviceListSignal_getHead;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CImDeviceListSignal_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _C2CImDeviceListSignal_clone(void *ptr, C2CImDeviceListSignalEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	C2CImDeviceListSignal *p = (C2CImDeviceListSignal *)ptr;
	C2CImDeviceListSignalEntry *cloned = C2CImDeviceListSignalEntry_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

C2CImDeviceListSignal *C2CImDeviceListSignal_clone(C2CImDeviceListSignal *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CImDeviceListSignal *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = C2CImDeviceListSignal_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(C2CImDeviceListSignal_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_C2CImDeviceListSignal_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CImDeviceListSignal_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void C2CImDeviceListSignal_purge(C2CImDeviceListSignal *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void C2CImDeviceListSignal_del(C2CImDeviceListSignal *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _C2CImDeviceListSignal_dump(void *ptr, C2CImDeviceListSignalEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); C2CImDeviceListSignalEntry_dump(p, tab);
	return err;
}

void C2CImDeviceListSignal_dump(C2CImDeviceListSignal *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _C2CImDeviceListSignal_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// C2CImDeviceListSignal
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CSafetySignalListResponseInfoData
C2CSafetySignalListResponseInfoData *C2CSafetySignalListResponseInfoData_new(Dz1Str local_center_id, 
																			 Dz1Str event_name, 
																			 Dz1Str event_type, 
																			 Dz1Str iot_im_device_id_qty, 
																			 C2CImDeviceListSignal *c2c_im_device_list, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CSafetySignalListResponseInfoData *__internal_ret = (C2CSafetySignalListResponseInfoData *)Dz1Calloc(sizeof(C2CSafetySignalListResponseInfoData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(C2CSafetySignalListResponseInfoData_delAndSetNull, (void *)&__internal_ret);
		
		if (local_center_id && (__internal_ret->local_center_id = Dz1Str_clone(local_center_id, errp)) == NULL) ERR_OUT(errp);
		else if (event_name && (__internal_ret->event_name = Dz1Str_clone(event_name, errp)) == NULL) ERR_OUT(errp);
		else if (event_type && (__internal_ret->event_type = Dz1Str_clone(event_type, errp)) == NULL) ERR_OUT(errp);
		else if (iot_im_device_id_qty && (__internal_ret->iot_im_device_id_qty = Dz1Str_clone(iot_im_device_id_qty, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->c2c_im_device_list = c2c_im_device_list;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CSafetySignalListResponseInfoData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t C2CSafetySignalListResponseInfoData_copy(C2CSafetySignalListResponseInfoData *dst, C2CSafetySignalListResponseInfoData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->local_center_id && (dst->local_center_id = Dz1Str_clone(src->local_center_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->event_name && (dst->event_name = Dz1Str_clone(src->event_name, errp)) == NULL) ERR_OUT(errp);
	else if (src->event_type && (dst->event_type = Dz1Str_clone(src->event_type, errp)) == NULL) ERR_OUT(errp);
	else if (src->iot_im_device_id_qty && (dst->iot_im_device_id_qty = Dz1Str_clone(src->iot_im_device_id_qty, errp)) == NULL) ERR_OUT(errp);
	else if (src->c2c_im_device_list && (dst->c2c_im_device_list = C2CImDeviceListSignal_clone(src->c2c_im_device_list, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

C2CSafetySignalListResponseInfoData *C2CSafetySignalListResponseInfoData_clone(C2CSafetySignalListResponseInfoData *src, Dz1Error *err)
{
	C2CSafetySignalListResponseInfoData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (C2CSafetySignalListResponseInfoData *)Dz1Calloc(sizeof(C2CSafetySignalListResponseInfoData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(C2CSafetySignalListResponseInfoData_delAndSetNull, (void *)&dst);
		if (C2CSafetySignalListResponseInfoData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CSafetySignalListResponseInfoData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void C2CSafetySignalListResponseInfoData_purge(C2CSafetySignalListResponseInfoData *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->local_center_id);
	Dz1Str_del(p->event_name);
	Dz1Str_del(p->event_type);
	Dz1Str_del(p->iot_im_device_id_qty);
	C2CImDeviceListSignal_del(p->c2c_im_device_list);
}

void C2CSafetySignalListResponseInfoData_del(C2CSafetySignalListResponseInfoData *p)
{
	if (p == NULL) return;
	C2CSafetySignalListResponseInfoData_purge(p);
	Dz1Free(p);
}

void C2CSafetySignalListResponseInfoData_dump(C2CSafetySignalListResponseInfoData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("local_center_id = ")); Dz1Str_dump(p->local_center_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("event_name = ")); Dz1Str_dump(p->event_name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("event_type = ")); Dz1Str_dump(p->event_type, tab); 
		Dz1Thread_tprintf(tab, Dz1T("iot_im_device_id_qty = ")); Dz1Str_dump(p->iot_im_device_id_qty, tab); 
		Dz1Thread_tprintf(tab, Dz1T("c2c_im_device_list = ")); C2CImDeviceListSignal_dump(p->c2c_im_device_list, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// C2CSafetySignalListResponseInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CSafetySignalListResponseInfo
C2CSafetySignalListResponseInfo *C2CSafetySignalListResponseInfo_new(Dz1Str command, 
																	 C2CSafetySignalListResponseInfoData *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	C2CSafetySignalListResponseInfo *__internal_ret = (C2CSafetySignalListResponseInfo *)Dz1Calloc(sizeof(C2CSafetySignalListResponseInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(C2CSafetySignalListResponseInfo_delAndSetNull, (void *)&__internal_ret);
		
		if (command && (__internal_ret->command = Dz1Str_clone(command, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->data = data;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CSafetySignalListResponseInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t C2CSafetySignalListResponseInfo_copy(C2CSafetySignalListResponseInfo *dst, C2CSafetySignalListResponseInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->command && (dst->command = Dz1Str_clone(src->command, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = C2CSafetySignalListResponseInfoData_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

C2CSafetySignalListResponseInfo *C2CSafetySignalListResponseInfo_clone(C2CSafetySignalListResponseInfo *src, Dz1Error *err)
{
	C2CSafetySignalListResponseInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (C2CSafetySignalListResponseInfo *)Dz1Calloc(sizeof(C2CSafetySignalListResponseInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(C2CSafetySignalListResponseInfo_delAndSetNull, (void *)&dst);
		if (C2CSafetySignalListResponseInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (C2CSafetySignalListResponseInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void C2CSafetySignalListResponseInfo_purge(C2CSafetySignalListResponseInfo *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->command);
	C2CSafetySignalListResponseInfoData_del(p->data);
}

void C2CSafetySignalListResponseInfo_del(C2CSafetySignalListResponseInfo *p)
{
	if (p == NULL) return;
	C2CSafetySignalListResponseInfo_purge(p);
	Dz1Free(p);
}

void C2CSafetySignalListResponseInfo_dump(C2CSafetySignalListResponseInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("command = ")); Dz1Str_dump(p->command, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("data = ")); C2CSafetySignalListResponseInfoData_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// C2CSafetySignalListResponseInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1RequestData
Itsk00126v1RequestData *Itsk00126v1RequestData_new(Dz1Str local_center_id, 
												   Dz1Str event_name, 
												   Dz1Str event_type, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v1RequestData *__internal_ret = (Itsk00126v1RequestData *)Dz1Calloc(sizeof(Itsk00126v1RequestData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v1RequestData_delAndSetNull, (void *)&__internal_ret);
		
		if (local_center_id && (__internal_ret->local_center_id = Dz1Str_clone(local_center_id, errp)) == NULL) ERR_OUT(errp);
		else if (event_name && (__internal_ret->event_name = Dz1Str_clone(event_name, errp)) == NULL) ERR_OUT(errp);
		else if (event_type && (__internal_ret->event_type = Dz1Str_clone(event_type, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v1RequestData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Itsk00126v1RequestData_copy(Itsk00126v1RequestData *dst, Itsk00126v1RequestData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->local_center_id && (dst->local_center_id = Dz1Str_clone(src->local_center_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->event_name && (dst->event_name = Dz1Str_clone(src->event_name, errp)) == NULL) ERR_OUT(errp);
	else if (src->event_type && (dst->event_type = Dz1Str_clone(src->event_type, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Itsk00126v1RequestData *Itsk00126v1RequestData_clone(Itsk00126v1RequestData *src, Dz1Error *err)
{
	Itsk00126v1RequestData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Itsk00126v1RequestData *)Dz1Calloc(sizeof(Itsk00126v1RequestData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Itsk00126v1RequestData_delAndSetNull, (void *)&dst);
		if (Itsk00126v1RequestData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v1RequestData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Itsk00126v1RequestData_purge(Itsk00126v1RequestData *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->local_center_id);
	Dz1Str_del(p->event_name);
	Dz1Str_del(p->event_type);
}

void Itsk00126v1RequestData_del(Itsk00126v1RequestData *p)
{
	if (p == NULL) return;
	Itsk00126v1RequestData_purge(p);
	Dz1Free(p);
}

void Itsk00126v1RequestData_dump(Itsk00126v1RequestData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("local_center_id = ")); Dz1Str_dump(p->local_center_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("event_name = ")); Dz1Str_dump(p->event_name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("event_type = ")); Dz1Str_dump(p->event_type, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Itsk00126v1RequestData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1Request
Itsk00126v1Request *Itsk00126v1Request_new(Dz1Str command, 
										   Itsk00126v1RequestData *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v1Request *__internal_ret = (Itsk00126v1Request *)Dz1Calloc(sizeof(Itsk00126v1Request), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v1Request_delAndSetNull, (void *)&__internal_ret);
		
		if (command && (__internal_ret->command = Dz1Str_clone(command, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->data = data;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v1Request_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Itsk00126v1Request_copy(Itsk00126v1Request *dst, Itsk00126v1Request *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->command && (dst->command = Dz1Str_clone(src->command, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = Itsk00126v1RequestData_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Itsk00126v1Request *Itsk00126v1Request_clone(Itsk00126v1Request *src, Dz1Error *err)
{
	Itsk00126v1Request *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Itsk00126v1Request *)Dz1Calloc(sizeof(Itsk00126v1Request), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Itsk00126v1Request_delAndSetNull, (void *)&dst);
		if (Itsk00126v1Request_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v1Request_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Itsk00126v1Request_purge(Itsk00126v1Request *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->command);
	Itsk00126v1RequestData_del(p->data);
}

void Itsk00126v1Request_del(Itsk00126v1Request *p)
{
	if (p == NULL) return;
	Itsk00126v1Request_purge(p);
	Dz1Free(p);
}

void Itsk00126v1Request_dump(Itsk00126v1Request *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("command = ")); Dz1Str_dump(p->command, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("data = ")); Itsk00126v1RequestData_dump(p->data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Itsk00126v1Request
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1EAMPresent
static struct Itsk00126v1EAMPresentMapA
{
	str_t str;
	Itsk00126v1EAMPresent v;
} Itsk00126v1EAMPresentMapA[] =
{
	{ (char *)"c2c_iot_im_device_sttus_info", Itsk00126v1EAMPresent_c2c_iot_im_device_sttus_info },
	{ (char *)"c2c_iot_device_list_request_info", Itsk00126v1EAMPresent_c2c_iot_device_list_request_info },
	{ (char *)"c2c_iot_device_list_response_info", Itsk00126v1EAMPresent_c2c_iot_device_list_response_info },
	{ (char *)"c2c_iot_device_sttus_info", Itsk00126v1EAMPresent_c2c_iot_device_sttus_info },
	{ (char *)"c2c_safety_signal_list_request_info", Itsk00126v1EAMPresent_c2c_safety_signal_list_request_info },
	{ (char *)"c2c_safety_signal_list_response_info", Itsk00126v1EAMPresent_c2c_safety_signal_list_response_info },
	{ NULL, Itsk00126v1EAMPresent_max }
};

str_t Itsk00126v1EAMPresentStrA(Itsk00126v1EAMPresent v)
{
	struct Itsk00126v1EAMPresentMapA *i = NULL;
	for (i = Itsk00126v1EAMPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Itsk00126v1EAMPresent Itsk00126v1EAMPresentFromStrA(str_t str)
{
	struct Itsk00126v1EAMPresentMapA *i = NULL;
	for (i = Itsk00126v1EAMPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Itsk00126v1EAMPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Itsk00126v1EAMPresentMapW
{
	wstr_t str;
	Itsk00126v1EAMPresent v;
} Itsk00126v1EAMPresentMapW[] =
{
	{ (wchar_t *)L"c2c_iot_im_device_sttus_info", Itsk00126v1EAMPresent_c2c_iot_im_device_sttus_info },
	{ (wchar_t *)L"c2c_iot_device_list_request_info", Itsk00126v1EAMPresent_c2c_iot_device_list_request_info },
	{ (wchar_t *)L"c2c_iot_device_list_response_info", Itsk00126v1EAMPresent_c2c_iot_device_list_response_info },
	{ (wchar_t *)L"c2c_iot_device_sttus_info", Itsk00126v1EAMPresent_c2c_iot_device_sttus_info },
	{ (wchar_t *)L"c2c_safety_signal_list_request_info", Itsk00126v1EAMPresent_c2c_safety_signal_list_request_info },
	{ (wchar_t *)L"c2c_safety_signal_list_response_info", Itsk00126v1EAMPresent_c2c_safety_signal_list_response_info },
	{ NULL, Itsk00126v1EAMPresent_max }
};

wstr_t Itsk00126v1EAMPresentStrW(Itsk00126v1EAMPresent v)
{
	struct Itsk00126v1EAMPresentMapW *i = NULL;
	for (i = Itsk00126v1EAMPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Itsk00126v1EAMPresent Itsk00126v1EAMPresentFromStrW(wstr_t str)
{
	struct Itsk00126v1EAMPresentMapW *i = NULL;
	for (i = Itsk00126v1EAMPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Itsk00126v1EAMPresent_max;
}
#endif // UNIX_SYSTEM

Itsk00126v1EAMPresent *Itsk00126v1EAMPresent_new(Itsk00126v1EAMPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v1EAMPresent *__internal_ret = (Itsk00126v1EAMPresent *)Dz1Calloc(sizeof(Itsk00126v1EAMPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Itsk00126v1EAMPresent_dump(Itsk00126v1EAMPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Itsk00126v1EAMPresentStr(*v));
}
// Itsk00126v1EAMPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1EAM
Itsk00126v1EAM *Itsk00126v1EAM_new(Itsk00126v1EAMPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Itsk00126v1EAM *ret = (Itsk00126v1EAM *)Dz1Calloc(sizeof(Itsk00126v1EAM), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Itsk00126v1EAM_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Itsk00126v1EAMPresent_c2c_iot_im_device_sttus_info:
			// _U_cst_clone
			if (ptr != NULL) ret->x.c2c_iot_im_device_sttus_info = (C2CIoTImDeviceSttusInfo *)ptr;
			ERR_CLEAR(errp);
			break;
		case Itsk00126v1EAMPresent_c2c_iot_device_list_request_info:
			// _U_cst_clone
			if (ptr != NULL) ret->x.c2c_iot_device_list_request_info = (Itsk00126v1Request *)ptr;
			ERR_CLEAR(errp);
			break;
		case Itsk00126v1EAMPresent_c2c_iot_device_list_response_info:
			// _U_cst_clone
			if (ptr != NULL) ret->x.c2c_iot_device_list_response_info = (C2CIoTDeviceListResponseInfo *)ptr;
			ERR_CLEAR(errp);
			break;
		case Itsk00126v1EAMPresent_c2c_iot_device_sttus_info:
			// _U_cst_clone
			if (ptr != NULL) ret->x.c2c_iot_device_sttus_info = (C2CIoTDeviceSttusInfo *)ptr;
			ERR_CLEAR(errp);
			break;
		case Itsk00126v1EAMPresent_c2c_safety_signal_list_request_info:
			// _U_cst_clone
			if (ptr != NULL) ret->x.c2c_safety_signal_list_request_info = (Itsk00126v1Request *)ptr;
			ERR_CLEAR(errp);
			break;
		case Itsk00126v1EAMPresent_c2c_safety_signal_list_response_info:
			// _U_cst_clone
			if (ptr != NULL) ret->x.c2c_safety_signal_list_response_info = (C2CSafetySignalListResponseInfo *)ptr;
			ERR_CLEAR(errp);
			break;
		case Itsk00126v1EAMPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v1EAM_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Itsk00126v1EAM_copy(Itsk00126v1EAM *ret, Itsk00126v1EAM *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Itsk00126v1EAMPresent_c2c_iot_im_device_sttus_info:
			// _U_cst_clone
			if (src->x.c2c_iot_im_device_sttus_info && (ret->x.c2c_iot_im_device_sttus_info = C2CIoTImDeviceSttusInfo_clone(src->x.c2c_iot_im_device_sttus_info, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Itsk00126v1EAMPresent_c2c_iot_device_list_request_info:
			// _U_cst_clone
			if (src->x.c2c_iot_device_list_request_info && (ret->x.c2c_iot_device_list_request_info = Itsk00126v1Request_clone(src->x.c2c_iot_device_list_request_info, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Itsk00126v1EAMPresent_c2c_iot_device_list_response_info:
			// _U_cst_clone
			if (src->x.c2c_iot_device_list_response_info && (ret->x.c2c_iot_device_list_response_info = C2CIoTDeviceListResponseInfo_clone(src->x.c2c_iot_device_list_response_info, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Itsk00126v1EAMPresent_c2c_iot_device_sttus_info:
			// _U_cst_clone
			if (src->x.c2c_iot_device_sttus_info && (ret->x.c2c_iot_device_sttus_info = C2CIoTDeviceSttusInfo_clone(src->x.c2c_iot_device_sttus_info, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Itsk00126v1EAMPresent_c2c_safety_signal_list_request_info:
			// _U_cst_clone
			if (src->x.c2c_safety_signal_list_request_info && (ret->x.c2c_safety_signal_list_request_info = Itsk00126v1Request_clone(src->x.c2c_safety_signal_list_request_info, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Itsk00126v1EAMPresent_c2c_safety_signal_list_response_info:
			// _U_cst_clone
			if (src->x.c2c_safety_signal_list_response_info && (ret->x.c2c_safety_signal_list_response_info = C2CSafetySignalListResponseInfo_clone(src->x.c2c_safety_signal_list_response_info, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Itsk00126v1EAM *Itsk00126v1EAM_clone(Itsk00126v1EAM *src, Dz1Error *err)
{
	Itsk00126v1EAM *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Itsk00126v1EAM *)Dz1Calloc(sizeof(Itsk00126v1EAM), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Itsk00126v1EAM_delAndSetNull, (void *)&ret);
		if (Itsk00126v1EAM_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Itsk00126v1EAM_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Itsk00126v1EAM_purge(Itsk00126v1EAM *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Itsk00126v1EAMPresent_c2c_iot_im_device_sttus_info:
		C2CIoTImDeviceSttusInfo_del(p->x.c2c_iot_im_device_sttus_info);
		break;
	case Itsk00126v1EAMPresent_c2c_iot_device_list_request_info:
		Itsk00126v1Request_del(p->x.c2c_iot_device_list_request_info);
		break;
	case Itsk00126v1EAMPresent_c2c_iot_device_list_response_info:
		C2CIoTDeviceListResponseInfo_del(p->x.c2c_iot_device_list_response_info);
		break;
	case Itsk00126v1EAMPresent_c2c_iot_device_sttus_info:
		C2CIoTDeviceSttusInfo_del(p->x.c2c_iot_device_sttus_info);
		break;
	case Itsk00126v1EAMPresent_c2c_safety_signal_list_request_info:
		Itsk00126v1Request_del(p->x.c2c_safety_signal_list_request_info);
		break;
	case Itsk00126v1EAMPresent_c2c_safety_signal_list_response_info:
		C2CSafetySignalListResponseInfo_del(p->x.c2c_safety_signal_list_response_info);
		break;
	default:
		break;
	}
}

void Itsk00126v1EAM_del(Itsk00126v1EAM *p)
{
	if (!p) return;
	Itsk00126v1EAM_purge(p);
	Dz1Free(p);
}

void Itsk00126v1EAM_dump(Itsk00126v1EAM *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Itsk00126v1EAMPresent_c2c_iot_im_device_sttus_info:
		Dz1Thread_printf(Dz1T("c2c_iot_im_device_sttus_info = ")); C2CIoTImDeviceSttusInfo_dump(p->x.c2c_iot_im_device_sttus_info, tab); 
		break;
	case Itsk00126v1EAMPresent_c2c_iot_device_list_request_info:
		Dz1Thread_printf(Dz1T("c2c_iot_device_list_request_info = ")); Itsk00126v1Request_dump(p->x.c2c_iot_device_list_request_info, tab); 
		break;
	case Itsk00126v1EAMPresent_c2c_iot_device_list_response_info:
		Dz1Thread_printf(Dz1T("c2c_iot_device_list_response_info = ")); C2CIoTDeviceListResponseInfo_dump(p->x.c2c_iot_device_list_response_info, tab); 
		break;
	case Itsk00126v1EAMPresent_c2c_iot_device_sttus_info:
		Dz1Thread_printf(Dz1T("c2c_iot_device_sttus_info = ")); C2CIoTDeviceSttusInfo_dump(p->x.c2c_iot_device_sttus_info, tab); 
		break;
	case Itsk00126v1EAMPresent_c2c_safety_signal_list_request_info:
		Dz1Thread_printf(Dz1T("c2c_safety_signal_list_request_info = ")); Itsk00126v1Request_dump(p->x.c2c_safety_signal_list_request_info, tab); 
		break;
	case Itsk00126v1EAMPresent_c2c_safety_signal_list_response_info:
		Dz1Thread_printf(Dz1T("c2c_safety_signal_list_response_info = ")); C2CSafetySignalListResponseInfo_dump(p->x.c2c_safety_signal_list_response_info, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Itsk00126v1EAM
////////////////////////////////////////////////////////////////////////////////


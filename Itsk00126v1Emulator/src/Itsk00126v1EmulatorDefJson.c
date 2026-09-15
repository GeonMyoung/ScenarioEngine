#include "Itsk00126v1EmulatorDefJson.h"

////////////////////////////////////////////////////////////////////////////////
// IoTImDeviceSttusInfo
static bool_t IoTImDeviceSttusInfo_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	IoTImDeviceSttusInfo *p = (IoTImDeviceSttusInfo *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->iot_im_device_id); p->iot_im_device_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->iot_im_device_link_sttus_code); p->iot_im_device_link_sttus_code = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *IoTImDeviceSttusInfo_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	IoTImDeviceSttusInfo *p = (IoTImDeviceSttusInfo *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->iot_im_device_id;
	case 1: return p->iot_im_device_link_sttus_code;
	default: return NULL;
	}
}

static Dz1JsonSpecChild IoTImDeviceSttusInfo_membs[] =
{
	{ Dz1Text("iot_im_device_id"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("iot_im_device_link_sttus_code"), Dz1Text("Dz1Str"), 1 },
	{ NULL, NULL, -1 }
};
// IoTImDeviceSttusInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// IoTImDeviceSttusInfoList
static bool_t IoTImDeviceSttusInfoList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	IoTImDeviceSttusInfoList *dst = (IoTImDeviceSttusInfoList *)dst_ptr;
	IoTImDeviceSttusInfo *node = NULL;
	if (dst == NULL || var == NULL || (node = (IoTImDeviceSttusInfo *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t IoTImDeviceSttusInfoList_cnt(void *ptr)
{
	u32_t ret = 0;
	IoTImDeviceSttusInfoList *list = (IoTImDeviceSttusInfoList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error IoTImDeviceSttusInfoList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	IoTImDeviceSttusInfoList *list = (IoTImDeviceSttusInfoList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// IoTImDeviceSttusInfoList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTImDeviceSttusInfoData
static bool_t C2CIoTImDeviceSttusInfoData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	C2CIoTImDeviceSttusInfoData *p = (C2CIoTImDeviceSttusInfoData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->local_center_id); p->local_center_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->iot_im_device_id_qty); p->iot_im_device_id_qty = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: IoTImDeviceSttusInfoList_delAndSetNull(&p->iot_im_device_sttus_info_list); p->iot_im_device_sttus_info_list = (IoTImDeviceSttusInfoList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: Dz1Str_delAndSetNull(&p->creat_dt); p->creat_dt = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *C2CIoTImDeviceSttusInfoData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	C2CIoTImDeviceSttusInfoData *p = (C2CIoTImDeviceSttusInfoData *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->local_center_id;
	case 1: return p->iot_im_device_id_qty;
	case 2: return p->iot_im_device_sttus_info_list;
	case 3: return p->creat_dt;
	default: return NULL;
	}
}

static Dz1JsonSpecChild C2CIoTImDeviceSttusInfoData_membs[] =
{
	{ Dz1Text("local_center_id"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("iot_im_device_id_qty"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("iot_im_device_sttus_info_list"), Dz1Text("IoTImDeviceSttusInfoList"), 2 },
	{ Dz1Text("creat_dt"), Dz1Text("Dz1Str"), 3 },
	{ NULL, NULL, -1 }
};
// C2CIoTImDeviceSttusInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTImDeviceSttusInfo
static bool_t C2CIoTImDeviceSttusInfo_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	C2CIoTImDeviceSttusInfo *p = (C2CIoTImDeviceSttusInfo *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->command); p->command = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->event_name); p->event_name = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->event_type); p->event_type = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 3: C2CIoTImDeviceSttusInfoData_delAndSetNull(&p->data); p->data = (C2CIoTImDeviceSttusInfoData *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *C2CIoTImDeviceSttusInfo_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	C2CIoTImDeviceSttusInfo *p = (C2CIoTImDeviceSttusInfo *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->command;
	case 1: return p->event_name;
	case 2: return p->event_type;
	case 3: return p->data;
	default: return NULL;
	}
}

static Dz1JsonSpecChild C2CIoTImDeviceSttusInfo_membs[] =
{
	{ Dz1Text("command"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("event_name"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("event_type"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("data"), Dz1Text("C2CIoTImDeviceSttusInfoData"), 3 },
	{ NULL, NULL, -1 }
};
// C2CIoTImDeviceSttusInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1RequestData
static bool_t Itsk00126v1RequestData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Itsk00126v1RequestData *p = (Itsk00126v1RequestData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->local_center_id); p->local_center_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->event_name); p->event_name = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->event_type); p->event_type = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Itsk00126v1RequestData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Itsk00126v1RequestData *p = (Itsk00126v1RequestData *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->local_center_id;
	case 1: return p->event_name;
	case 2: return p->event_type;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Itsk00126v1RequestData_membs[] =
{
	{ Dz1Text("local_center_id"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("event_name"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("event_type"), Dz1Text("Dz1Str"), 2 },
	{ NULL, NULL, -1 }
};
// Itsk00126v1RequestData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1Request
static bool_t Itsk00126v1Request_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Itsk00126v1Request *p = (Itsk00126v1Request *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->command); p->command = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Itsk00126v1RequestData_delAndSetNull(&p->data); p->data = (Itsk00126v1RequestData *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Itsk00126v1Request_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Itsk00126v1Request *p = (Itsk00126v1Request *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->command;
	case 1: return p->data;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Itsk00126v1Request_membs[] =
{
	{ Dz1Text("command"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("data"), Dz1Text("Itsk00126v1RequestData"), 1 },
	{ NULL, NULL, -1 }
};
// Itsk00126v1Request
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceEntry
static bool_t C2CIoTDeviceEntry_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	C2CIoTDeviceEntry *p = (C2CIoTDeviceEntry *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->iot_device_id); p->iot_device_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *C2CIoTDeviceEntry_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	C2CIoTDeviceEntry *p = (C2CIoTDeviceEntry *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->iot_device_id;
	default: return NULL;
	}
}

static Dz1JsonSpecChild C2CIoTDeviceEntry_membs[] =
{
	{ Dz1Text("iot_device_id"), Dz1Text("Dz1Str"), 0 },
	{ NULL, NULL, -1 }
};
// C2CIoTDeviceEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceList
static bool_t C2CIoTDeviceList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	C2CIoTDeviceList *dst = (C2CIoTDeviceList *)dst_ptr;
	C2CIoTDeviceEntry *node = NULL;
	if (dst == NULL || var == NULL || (node = (C2CIoTDeviceEntry *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t C2CIoTDeviceList_cnt(void *ptr)
{
	u32_t ret = 0;
	C2CIoTDeviceList *list = (C2CIoTDeviceList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error C2CIoTDeviceList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	C2CIoTDeviceList *list = (C2CIoTDeviceList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// C2CIoTDeviceList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CImDeviceEntry
static bool_t C2CImDeviceEntry_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	C2CImDeviceEntry *p = (C2CImDeviceEntry *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->iot_im_device_id); p->iot_im_device_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->iot_device_id_qty); p->iot_device_id_qty = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: C2CIoTDeviceList_delAndSetNull(&p->iot_device_list); p->iot_device_list = (C2CIoTDeviceList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *C2CImDeviceEntry_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	C2CImDeviceEntry *p = (C2CImDeviceEntry *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->iot_im_device_id;
	case 1: return p->iot_device_id_qty;
	case 2: return p->iot_device_list;
	default: return NULL;
	}
}

static Dz1JsonSpecChild C2CImDeviceEntry_membs[] =
{
	{ Dz1Text("iot_im_device_id"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("iot_device_id_qty"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("iot_device_list"), Dz1Text("C2CIoTDeviceList"), 2 },
	{ NULL, NULL, -1 }
};
// C2CImDeviceEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CImDeviceList
static bool_t C2CImDeviceList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	C2CImDeviceList *dst = (C2CImDeviceList *)dst_ptr;
	C2CImDeviceEntry *node = NULL;
	if (dst == NULL || var == NULL || (node = (C2CImDeviceEntry *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t C2CImDeviceList_cnt(void *ptr)
{
	u32_t ret = 0;
	C2CImDeviceList *list = (C2CImDeviceList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error C2CImDeviceList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	C2CImDeviceList *list = (C2CImDeviceList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// C2CImDeviceList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceListResponseInfoData
static bool_t C2CIoTDeviceListResponseInfoData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	C2CIoTDeviceListResponseInfoData *p = (C2CIoTDeviceListResponseInfoData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->local_center_id); p->local_center_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->event_name); p->event_name = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->event_type); p->event_type = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 3: Dz1Str_delAndSetNull(&p->iot_im_device_id_qty); p->iot_im_device_id_qty = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 4: C2CImDeviceList_delAndSetNull(&p->c2c_im_device_list); p->c2c_im_device_list = (C2CImDeviceList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *C2CIoTDeviceListResponseInfoData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	C2CIoTDeviceListResponseInfoData *p = (C2CIoTDeviceListResponseInfoData *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->local_center_id;
	case 1: return p->event_name;
	case 2: return p->event_type;
	case 3: return p->iot_im_device_id_qty;
	case 4: return p->c2c_im_device_list;
	default: return NULL;
	}
}

static Dz1JsonSpecChild C2CIoTDeviceListResponseInfoData_membs[] =
{
	{ Dz1Text("local_center_id"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("event_name"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("event_type"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("iot_im_device_id_qty"), Dz1Text("Dz1Str"), 3 },
	{ Dz1Text("c2c_im_device_list"), Dz1Text("C2CImDeviceList"), 4 },
	{ NULL, NULL, -1 }
};
// C2CIoTDeviceListResponseInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceListResponseInfo
static bool_t C2CIoTDeviceListResponseInfo_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	C2CIoTDeviceListResponseInfo *p = (C2CIoTDeviceListResponseInfo *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->command); p->command = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: C2CIoTDeviceListResponseInfoData_delAndSetNull(&p->data); p->data = (C2CIoTDeviceListResponseInfoData *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *C2CIoTDeviceListResponseInfo_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	C2CIoTDeviceListResponseInfo *p = (C2CIoTDeviceListResponseInfo *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->command;
	case 1: return p->data;
	default: return NULL;
	}
}

static Dz1JsonSpecChild C2CIoTDeviceListResponseInfo_membs[] =
{
	{ Dz1Text("command"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("data"), Dz1Text("C2CIoTDeviceListResponseInfoData"), 1 },
	{ NULL, NULL, -1 }
};
// C2CIoTDeviceListResponseInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceSttusInfoEntry
static bool_t C2CIoTDeviceSttusInfoEntry_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	C2CIoTDeviceSttusInfoEntry *p = (C2CIoTDeviceSttusInfoEntry *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->iot_device_id); p->iot_device_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->iot_device_sttus_code); p->iot_device_sttus_code = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->btry_sttus_code); p->btry_sttus_code = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 3: Dz1Str_delAndSetNull(&p->link_sttus_code); p->link_sttus_code = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 4: p->data_trnsmis_cont =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: Dz1Str_delAndSetNull(&p->iot_im_device_id); p->iot_im_device_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *C2CIoTDeviceSttusInfoEntry_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	C2CIoTDeviceSttusInfoEntry *p = (C2CIoTDeviceSttusInfoEntry *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->iot_device_id;
	case 1: return p->iot_device_sttus_code;
	case 2: return p->btry_sttus_code;
	case 3: return p->link_sttus_code;
	case 4: return &p->data_trnsmis_cont;
	case 5: return p->iot_im_device_id;
	default: return NULL;
	}
}

static Dz1JsonSpecChild C2CIoTDeviceSttusInfoEntry_membs[] =
{
	{ Dz1Text("iot_device_id"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("iot_device_sttus_code"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("btry_sttus_code"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("link_sttus_code"), Dz1Text("Dz1Str"), 3 },
	{ Dz1Text("data_trnsmis_cont"), Dz1Text("s64_t"), 4 },
	{ Dz1Text("iot_im_device_id"), Dz1Text("Dz1Str"), 5 },
	{ NULL, NULL, -1 }
};
// C2CIoTDeviceSttusInfoEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceSttusInfoList
static bool_t C2CIoTDeviceSttusInfoList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	C2CIoTDeviceSttusInfoList *dst = (C2CIoTDeviceSttusInfoList *)dst_ptr;
	C2CIoTDeviceSttusInfoEntry *node = NULL;
	if (dst == NULL || var == NULL || (node = (C2CIoTDeviceSttusInfoEntry *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t C2CIoTDeviceSttusInfoList_cnt(void *ptr)
{
	u32_t ret = 0;
	C2CIoTDeviceSttusInfoList *list = (C2CIoTDeviceSttusInfoList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error C2CIoTDeviceSttusInfoList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	C2CIoTDeviceSttusInfoList *list = (C2CIoTDeviceSttusInfoList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// C2CIoTDeviceSttusInfoList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceSttusInfoData
static bool_t C2CIoTDeviceSttusInfoData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	C2CIoTDeviceSttusInfoData *p = (C2CIoTDeviceSttusInfoData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->local_center_id); p->local_center_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->iot_device_id_qty); p->iot_device_id_qty = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: C2CIoTDeviceSttusInfoList_delAndSetNull(&p->iot_device_sttus_info_list); p->iot_device_sttus_info_list = (C2CIoTDeviceSttusInfoList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: Dz1Str_delAndSetNull(&p->creat_dt); p->creat_dt = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *C2CIoTDeviceSttusInfoData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	C2CIoTDeviceSttusInfoData *p = (C2CIoTDeviceSttusInfoData *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->local_center_id;
	case 1: return p->iot_device_id_qty;
	case 2: return p->iot_device_sttus_info_list;
	case 3: return p->creat_dt;
	default: return NULL;
	}
}

static Dz1JsonSpecChild C2CIoTDeviceSttusInfoData_membs[] =
{
	{ Dz1Text("local_center_id"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("iot_device_id_qty"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("iot_device_sttus_info_list"), Dz1Text("C2CIoTDeviceSttusInfoList"), 2 },
	{ Dz1Text("creat_dt"), Dz1Text("Dz1Str"), 3 },
	{ NULL, NULL, -1 }
};
// C2CIoTDeviceSttusInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIoTDeviceSttusInfo
static bool_t C2CIoTDeviceSttusInfo_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	C2CIoTDeviceSttusInfo *p = (C2CIoTDeviceSttusInfo *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->command); p->command = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: C2CIoTDeviceSttusInfoData_delAndSetNull(&p->data); p->data = (C2CIoTDeviceSttusInfoData *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *C2CIoTDeviceSttusInfo_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	C2CIoTDeviceSttusInfo *p = (C2CIoTDeviceSttusInfo *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->command;
	case 1: return p->data;
	default: return NULL;
	}
}

static Dz1JsonSpecChild C2CIoTDeviceSttusInfo_membs[] =
{
	{ Dz1Text("command"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("data"), Dz1Text("C2CIoTDeviceSttusInfoData"), 1 },
	{ NULL, NULL, -1 }
};
// C2CIoTDeviceSttusInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CSafetySignalInfo
static bool_t C2CSafetySignalInfo_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	C2CSafetySignalInfo *p = (C2CSafetySignalInfo *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->safety_signal_id); p->safety_signal_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->administ_zone_code); p->administ_zone_code = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->road_code); p->road_code = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 3: p->lc_lat =  *(real64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->lc_lng =  *(real64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: Dz1Str_delAndSetNull(&p->safety_signal_ty_code); p->safety_signal_ty_code = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 6: Dz1Str_delAndSetNull(&p->safety_signal_sttus_code); p->safety_signal_sttus_code = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *C2CSafetySignalInfo_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	C2CSafetySignalInfo *p = (C2CSafetySignalInfo *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->safety_signal_id;
	case 1: return p->administ_zone_code;
	case 2: return p->road_code;
	case 3: return &p->lc_lat;
	case 4: return &p->lc_lng;
	case 5: return p->safety_signal_ty_code;
	case 6: return p->safety_signal_sttus_code;
	default: return NULL;
	}
}

static Dz1JsonSpecChild C2CSafetySignalInfo_membs[] =
{
	{ Dz1Text("safety_signal_id"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("administ_zone_code"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("road_code"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("lc_lat"), Dz1Text("real64_t"), 3 },
	{ Dz1Text("lc_lng"), Dz1Text("real64_t"), 4 },
	{ Dz1Text("safety_signal_ty_code"), Dz1Text("Dz1Str"), 5 },
	{ Dz1Text("safety_signal_sttus_code"), Dz1Text("Dz1Str"), 6 },
	{ NULL, NULL, -1 }
};
// C2CSafetySignalInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CSafetySignalInfoList
static bool_t C2CSafetySignalInfoList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	C2CSafetySignalInfoList *dst = (C2CSafetySignalInfoList *)dst_ptr;
	C2CSafetySignalInfo *node = NULL;
	if (dst == NULL || var == NULL || (node = (C2CSafetySignalInfo *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t C2CSafetySignalInfoList_cnt(void *ptr)
{
	u32_t ret = 0;
	C2CSafetySignalInfoList *list = (C2CSafetySignalInfoList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error C2CSafetySignalInfoList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	C2CSafetySignalInfoList *list = (C2CSafetySignalInfoList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// C2CSafetySignalInfoList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIotDeviceListSignalEntry
static bool_t C2CIotDeviceListSignalEntry_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	C2CIotDeviceListSignalEntry *p = (C2CIotDeviceListSignalEntry *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->iot_device_id); p->iot_device_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->safety_signal_id_qty); p->safety_signal_id_qty = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: C2CSafetySignalInfoList_delAndSetNull(&p->c2c_safety_signal_info_list); p->c2c_safety_signal_info_list = (C2CSafetySignalInfoList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *C2CIotDeviceListSignalEntry_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	C2CIotDeviceListSignalEntry *p = (C2CIotDeviceListSignalEntry *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->iot_device_id;
	case 1: return p->safety_signal_id_qty;
	case 2: return p->c2c_safety_signal_info_list;
	default: return NULL;
	}
}

static Dz1JsonSpecChild C2CIotDeviceListSignalEntry_membs[] =
{
	{ Dz1Text("iot_device_id"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("safety_signal_id_qty"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("c2c_safety_signal_info_list"), Dz1Text("C2CSafetySignalInfoList"), 2 },
	{ NULL, NULL, -1 }
};
// C2CIotDeviceListSignalEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CIotDeviceListSignal
static bool_t C2CIotDeviceListSignal_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	C2CIotDeviceListSignal *dst = (C2CIotDeviceListSignal *)dst_ptr;
	C2CIotDeviceListSignalEntry *node = NULL;
	if (dst == NULL || var == NULL || (node = (C2CIotDeviceListSignalEntry *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t C2CIotDeviceListSignal_cnt(void *ptr)
{
	u32_t ret = 0;
	C2CIotDeviceListSignal *list = (C2CIotDeviceListSignal *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error C2CIotDeviceListSignal_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	C2CIotDeviceListSignal *list = (C2CIotDeviceListSignal *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// C2CIotDeviceListSignal
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CImDeviceListSignalEntry
static bool_t C2CImDeviceListSignalEntry_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	C2CImDeviceListSignalEntry *p = (C2CImDeviceListSignalEntry *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->iot_im_device_id); p->iot_im_device_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->iot_device_id_qty); p->iot_device_id_qty = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: C2CIotDeviceListSignal_delAndSetNull(&p->c2c_iot_device_list); p->c2c_iot_device_list = (C2CIotDeviceListSignal *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *C2CImDeviceListSignalEntry_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	C2CImDeviceListSignalEntry *p = (C2CImDeviceListSignalEntry *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->iot_im_device_id;
	case 1: return p->iot_device_id_qty;
	case 2: return p->c2c_iot_device_list;
	default: return NULL;
	}
}

static Dz1JsonSpecChild C2CImDeviceListSignalEntry_membs[] =
{
	{ Dz1Text("iot_im_device_id"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("iot_device_id_qty"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("c2c_iot_device_list"), Dz1Text("C2CIotDeviceListSignal"), 2 },
	{ NULL, NULL, -1 }
};
// C2CImDeviceListSignalEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CImDeviceListSignal
static bool_t C2CImDeviceListSignal_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	C2CImDeviceListSignal *dst = (C2CImDeviceListSignal *)dst_ptr;
	C2CImDeviceListSignalEntry *node = NULL;
	if (dst == NULL || var == NULL || (node = (C2CImDeviceListSignalEntry *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t C2CImDeviceListSignal_cnt(void *ptr)
{
	u32_t ret = 0;
	C2CImDeviceListSignal *list = (C2CImDeviceListSignal *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error C2CImDeviceListSignal_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	C2CImDeviceListSignal *list = (C2CImDeviceListSignal *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// C2CImDeviceListSignal
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CSafetySignalListResponseInfoData
static bool_t C2CSafetySignalListResponseInfoData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	C2CSafetySignalListResponseInfoData *p = (C2CSafetySignalListResponseInfoData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->local_center_id); p->local_center_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->event_name); p->event_name = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->event_type); p->event_type = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 3: Dz1Str_delAndSetNull(&p->iot_im_device_id_qty); p->iot_im_device_id_qty = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 4: C2CImDeviceListSignal_delAndSetNull(&p->c2c_im_device_list); p->c2c_im_device_list = (C2CImDeviceListSignal *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *C2CSafetySignalListResponseInfoData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	C2CSafetySignalListResponseInfoData *p = (C2CSafetySignalListResponseInfoData *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->local_center_id;
	case 1: return p->event_name;
	case 2: return p->event_type;
	case 3: return p->iot_im_device_id_qty;
	case 4: return p->c2c_im_device_list;
	default: return NULL;
	}
}

static Dz1JsonSpecChild C2CSafetySignalListResponseInfoData_membs[] =
{
	{ Dz1Text("local_center_id"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("event_name"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("event_type"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("iot_im_device_id_qty"), Dz1Text("Dz1Str"), 3 },
	{ Dz1Text("c2c_im_device_list"), Dz1Text("C2CImDeviceListSignal"), 4 },
	{ NULL, NULL, -1 }
};
// C2CSafetySignalListResponseInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// C2CSafetySignalListResponseInfo
static bool_t C2CSafetySignalListResponseInfo_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	C2CSafetySignalListResponseInfo *p = (C2CSafetySignalListResponseInfo *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->command); p->command = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: C2CSafetySignalListResponseInfoData_delAndSetNull(&p->data); p->data = (C2CSafetySignalListResponseInfoData *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *C2CSafetySignalListResponseInfo_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	C2CSafetySignalListResponseInfo *p = (C2CSafetySignalListResponseInfo *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->command;
	case 1: return p->data;
	default: return NULL;
	}
}

static Dz1JsonSpecChild C2CSafetySignalListResponseInfo_membs[] =
{
	{ Dz1Text("command"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("data"), Dz1Text("C2CSafetySignalListResponseInfoData"), 1 },
	{ NULL, NULL, -1 }
};
// C2CSafetySignalListResponseInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v1EAM
static bool_t Itsk00126v1EAM_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Itsk00126v1EAM *p = (Itsk00126v1EAM *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Itsk00126v1EAMPresent_c2c_iot_im_device_sttus_info: C2CIoTImDeviceSttusInfo_delAndSetNull(&p->x.c2c_iot_im_device_sttus_info); p->x.c2c_iot_im_device_sttus_info =(C2CIoTImDeviceSttusInfo *)info->data; info->data = NULL; break;
	case Itsk00126v1EAMPresent_c2c_iot_device_list_request_info: Itsk00126v1Request_delAndSetNull(&p->x.c2c_iot_device_list_request_info); p->x.c2c_iot_device_list_request_info =(Itsk00126v1Request *)info->data; info->data = NULL; break;
	case Itsk00126v1EAMPresent_c2c_iot_device_list_response_info: C2CIoTDeviceListResponseInfo_delAndSetNull(&p->x.c2c_iot_device_list_response_info); p->x.c2c_iot_device_list_response_info =(C2CIoTDeviceListResponseInfo *)info->data; info->data = NULL; break;
	case Itsk00126v1EAMPresent_c2c_iot_device_sttus_info: C2CIoTDeviceSttusInfo_delAndSetNull(&p->x.c2c_iot_device_sttus_info); p->x.c2c_iot_device_sttus_info =(C2CIoTDeviceSttusInfo *)info->data; info->data = NULL; break;
	case Itsk00126v1EAMPresent_c2c_safety_signal_list_request_info: Itsk00126v1Request_delAndSetNull(&p->x.c2c_safety_signal_list_request_info); p->x.c2c_safety_signal_list_request_info =(Itsk00126v1Request *)info->data; info->data = NULL; break;
	case Itsk00126v1EAMPresent_c2c_safety_signal_list_response_info: C2CSafetySignalListResponseInfo_delAndSetNull(&p->x.c2c_safety_signal_list_response_info); p->x.c2c_safety_signal_list_response_info =(C2CSafetySignalListResponseInfo *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Itsk00126v1EAMPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Itsk00126v1EAM_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Itsk00126v1EAM *p = (Itsk00126v1EAM *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Itsk00126v1EAMPresent_c2c_iot_im_device_sttus_info: return p->x.c2c_iot_im_device_sttus_info;
		case Itsk00126v1EAMPresent_c2c_iot_device_list_request_info: return p->x.c2c_iot_device_list_request_info;
		case Itsk00126v1EAMPresent_c2c_iot_device_list_response_info: return p->x.c2c_iot_device_list_response_info;
		case Itsk00126v1EAMPresent_c2c_iot_device_sttus_info: return p->x.c2c_iot_device_sttus_info;
		case Itsk00126v1EAMPresent_c2c_safety_signal_list_request_info: return p->x.c2c_safety_signal_list_request_info;
		case Itsk00126v1EAMPresent_c2c_safety_signal_list_response_info: return p->x.c2c_safety_signal_list_response_info;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Itsk00126v1EAM_membs[] =
{
	{ Dz1Text("c2c_iot_im_device_sttus_info"), Dz1Text("C2CIoTImDeviceSttusInfo"), Itsk00126v1EAMPresent_c2c_iot_im_device_sttus_info },
	{ Dz1Text("c2c_iot_device_list_request_info"), Dz1Text("Itsk00126v1Request"), Itsk00126v1EAMPresent_c2c_iot_device_list_request_info },
	{ Dz1Text("c2c_iot_device_list_response_info"), Dz1Text("C2CIoTDeviceListResponseInfo"), Itsk00126v1EAMPresent_c2c_iot_device_list_response_info },
	{ Dz1Text("c2c_iot_device_sttus_info"), Dz1Text("C2CIoTDeviceSttusInfo"), Itsk00126v1EAMPresent_c2c_iot_device_sttus_info },
	{ Dz1Text("c2c_safety_signal_list_request_info"), Dz1Text("Itsk00126v1Request"), Itsk00126v1EAMPresent_c2c_safety_signal_list_request_info },
	{ Dz1Text("c2c_safety_signal_list_response_info"), Dz1Text("C2CSafetySignalListResponseInfo"), Itsk00126v1EAMPresent_c2c_safety_signal_list_response_info },
	{ NULL, NULL, -1 }
};
// Itsk00126v1EAM
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpec Initializer
bool_t Itsk00126v1EmulatorDef_initJsonSpec(Dz1JsonSpec *dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (0) { }
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("IoTImDeviceSttusInfo"), IoTImDeviceSttusInfo_gen, IoTImDeviceSttusInfo_del, IoTImDeviceSttusInfo_setChild, IoTImDeviceSttusInfo_getChild, IoTImDeviceSttusInfo_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("C2CIoTImDeviceSttusInfoData"), C2CIoTImDeviceSttusInfoData_gen, C2CIoTImDeviceSttusInfoData_del, C2CIoTImDeviceSttusInfoData_setChild, C2CIoTImDeviceSttusInfoData_getChild, C2CIoTImDeviceSttusInfoData_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("C2CIoTImDeviceSttusInfo"), C2CIoTImDeviceSttusInfo_gen, C2CIoTImDeviceSttusInfo_del, C2CIoTImDeviceSttusInfo_setChild, C2CIoTImDeviceSttusInfo_getChild, C2CIoTImDeviceSttusInfo_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Itsk00126v1RequestData"), Itsk00126v1RequestData_gen, Itsk00126v1RequestData_del, Itsk00126v1RequestData_setChild, Itsk00126v1RequestData_getChild, Itsk00126v1RequestData_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Itsk00126v1Request"), Itsk00126v1Request_gen, Itsk00126v1Request_del, Itsk00126v1Request_setChild, Itsk00126v1Request_getChild, Itsk00126v1Request_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("C2CIoTDeviceEntry"), C2CIoTDeviceEntry_gen, C2CIoTDeviceEntry_del, C2CIoTDeviceEntry_setChild, C2CIoTDeviceEntry_getChild, C2CIoTDeviceEntry_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("C2CImDeviceEntry"), C2CImDeviceEntry_gen, C2CImDeviceEntry_del, C2CImDeviceEntry_setChild, C2CImDeviceEntry_getChild, C2CImDeviceEntry_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("C2CIoTDeviceListResponseInfoData"), C2CIoTDeviceListResponseInfoData_gen, C2CIoTDeviceListResponseInfoData_del, C2CIoTDeviceListResponseInfoData_setChild, C2CIoTDeviceListResponseInfoData_getChild, C2CIoTDeviceListResponseInfoData_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("C2CIoTDeviceListResponseInfo"), C2CIoTDeviceListResponseInfo_gen, C2CIoTDeviceListResponseInfo_del, C2CIoTDeviceListResponseInfo_setChild, C2CIoTDeviceListResponseInfo_getChild, C2CIoTDeviceListResponseInfo_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("C2CIoTDeviceSttusInfoEntry"), C2CIoTDeviceSttusInfoEntry_gen, C2CIoTDeviceSttusInfoEntry_del, C2CIoTDeviceSttusInfoEntry_setChild, C2CIoTDeviceSttusInfoEntry_getChild, C2CIoTDeviceSttusInfoEntry_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("C2CIoTDeviceSttusInfoData"), C2CIoTDeviceSttusInfoData_gen, C2CIoTDeviceSttusInfoData_del, C2CIoTDeviceSttusInfoData_setChild, C2CIoTDeviceSttusInfoData_getChild, C2CIoTDeviceSttusInfoData_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("C2CIoTDeviceSttusInfo"), C2CIoTDeviceSttusInfo_gen, C2CIoTDeviceSttusInfo_del, C2CIoTDeviceSttusInfo_setChild, C2CIoTDeviceSttusInfo_getChild, C2CIoTDeviceSttusInfo_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("C2CSafetySignalInfo"), C2CSafetySignalInfo_gen, C2CSafetySignalInfo_del, C2CSafetySignalInfo_setChild, C2CSafetySignalInfo_getChild, C2CSafetySignalInfo_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("C2CIotDeviceListSignalEntry"), C2CIotDeviceListSignalEntry_gen, C2CIotDeviceListSignalEntry_del, C2CIotDeviceListSignalEntry_setChild, C2CIotDeviceListSignalEntry_getChild, C2CIotDeviceListSignalEntry_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("C2CImDeviceListSignalEntry"), C2CImDeviceListSignalEntry_gen, C2CImDeviceListSignalEntry_del, C2CImDeviceListSignalEntry_setChild, C2CImDeviceListSignalEntry_getChild, C2CImDeviceListSignalEntry_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("C2CSafetySignalListResponseInfoData"), C2CSafetySignalListResponseInfoData_gen, C2CSafetySignalListResponseInfoData_del, C2CSafetySignalListResponseInfoData_setChild, C2CSafetySignalListResponseInfoData_getChild, C2CSafetySignalListResponseInfoData_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("C2CSafetySignalListResponseInfo"), C2CSafetySignalListResponseInfo_gen, C2CSafetySignalListResponseInfo_del, C2CSafetySignalListResponseInfo_setChild, C2CSafetySignalListResponseInfo_getChild, C2CSafetySignalListResponseInfo_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Itsk00126v1EAM"), Itsk00126v1EAM_gen, Itsk00126v1EAM_del, Itsk00126v1EAM_setChild, Itsk00126v1EAM_getChild, Itsk00126v1EAM_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("IoTImDeviceSttusInfoList"), IoTImDeviceSttusInfoList_gen, IoTImDeviceSttusInfoList_del, IoTImDeviceSttusInfoList_append, IoTImDeviceSttusInfoList_cnt, IoTImDeviceSttusInfoList_tlv, Dz1Text("IoTImDeviceSttusInfo") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("C2CIoTDeviceList"), C2CIoTDeviceList_gen, C2CIoTDeviceList_del, C2CIoTDeviceList_append, C2CIoTDeviceList_cnt, C2CIoTDeviceList_tlv, Dz1Text("C2CIoTDeviceEntry") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("C2CImDeviceList"), C2CImDeviceList_gen, C2CImDeviceList_del, C2CImDeviceList_append, C2CImDeviceList_cnt, C2CImDeviceList_tlv, Dz1Text("C2CImDeviceEntry") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("C2CIoTDeviceSttusInfoList"), C2CIoTDeviceSttusInfoList_gen, C2CIoTDeviceSttusInfoList_del, C2CIoTDeviceSttusInfoList_append, C2CIoTDeviceSttusInfoList_cnt, C2CIoTDeviceSttusInfoList_tlv, Dz1Text("C2CIoTDeviceSttusInfoEntry") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("C2CSafetySignalInfoList"), C2CSafetySignalInfoList_gen, C2CSafetySignalInfoList_del, C2CSafetySignalInfoList_append, C2CSafetySignalInfoList_cnt, C2CSafetySignalInfoList_tlv, Dz1Text("C2CSafetySignalInfo") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("C2CIotDeviceListSignal"), C2CIotDeviceListSignal_gen, C2CIotDeviceListSignal_del, C2CIotDeviceListSignal_append, C2CIotDeviceListSignal_cnt, C2CIotDeviceListSignal_tlv, Dz1Text("C2CIotDeviceListSignalEntry") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("C2CImDeviceListSignal"), C2CImDeviceListSignal_gen, C2CImDeviceListSignal_del, C2CImDeviceListSignal_append, C2CImDeviceListSignal_cnt, C2CImDeviceListSignal_tlv, Dz1Text("C2CImDeviceListSignalEntry") )).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
Dz1JsonSpec *Itsk00126v1EmulatorDef_genJsonSpec(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonSpec *ret = Dz1JsonSpec_generate(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonSpec_delAndSetNull, (void *)&ret);

		if (Itsk00126v1EmulatorDef_initJsonSpec(ret, errp) == FALSE) ERR_OUT(errp);
		else if (Dz1JsonSpec_check(ret, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1JsonSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Dz1JsonSpec Initializer
////////////////////////////////////////////////////////////////////////////////

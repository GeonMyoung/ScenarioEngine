#include "Itsk00126v2TestScenarioDefJson.h"

////////////////////////////////////////////////////////////////////////////////
// F2CIoTImDeviceSttusInfoData
static bool_t F2CIoTImDeviceSttusInfoData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	F2CIoTImDeviceSttusInfoData *p = (F2CIoTImDeviceSttusInfoData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->iot_im_device_id); p->iot_im_device_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->iot_im_device_link_sttus_code); p->iot_im_device_link_sttus_code = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->creat_dt); p->creat_dt = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *F2CIoTImDeviceSttusInfoData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	F2CIoTImDeviceSttusInfoData *p = (F2CIoTImDeviceSttusInfoData *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->iot_im_device_id;
	case 1: return p->iot_im_device_link_sttus_code;
	case 2: return p->creat_dt;
	default: return NULL;
	}
}

static Dz1JsonSpecChild F2CIoTImDeviceSttusInfoData_membs[] =
{
	{ Dz1Text("iot_im_device_id"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("iot_im_device_link_sttus_code"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("creat_dt"), Dz1Text("Dz1Str"), 2 },
	{ NULL, NULL, -1 }
};
// F2CIoTImDeviceSttusInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTImDeviceSttusInfo
static bool_t F2CIoTImDeviceSttusInfo_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	F2CIoTImDeviceSttusInfo *p = (F2CIoTImDeviceSttusInfo *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->command); p->command = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: F2CIoTImDeviceSttusInfoData_delAndSetNull(&p->data); p->data = (F2CIoTImDeviceSttusInfoData *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *F2CIoTImDeviceSttusInfo_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	F2CIoTImDeviceSttusInfo *p = (F2CIoTImDeviceSttusInfo *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->command;
	case 1: return p->data;
	default: return NULL;
	}
}

static Dz1JsonSpecChild F2CIoTImDeviceSttusInfo_membs[] =
{
	{ Dz1Text("command"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("data"), Dz1Text("F2CIoTImDeviceSttusInfoData"), 1 },
	{ NULL, NULL, -1 }
};
// F2CIoTImDeviceSttusInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2RequestData
static bool_t Itsk00126v2RequestData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Itsk00126v2RequestData *p = (Itsk00126v2RequestData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->iot_im_device_id); p->iot_im_device_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->event_name); p->event_name = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->event_type); p->event_type = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Itsk00126v2RequestData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Itsk00126v2RequestData *p = (Itsk00126v2RequestData *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->iot_im_device_id;
	case 1: return p->event_name;
	case 2: return p->event_type;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Itsk00126v2RequestData_membs[] =
{
	{ Dz1Text("iot_im_device_id"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("event_name"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("event_type"), Dz1Text("Dz1Str"), 2 },
	{ NULL, NULL, -1 }
};
// Itsk00126v2RequestData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2Request
static bool_t Itsk00126v2Request_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Itsk00126v2Request *p = (Itsk00126v2Request *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->command); p->command = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Itsk00126v2RequestData_delAndSetNull(&p->data); p->data = (Itsk00126v2RequestData *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Itsk00126v2Request_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Itsk00126v2Request *p = (Itsk00126v2Request *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->command;
	case 1: return p->data;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Itsk00126v2Request_membs[] =
{
	{ Dz1Text("command"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("data"), Dz1Text("Itsk00126v2RequestData"), 1 },
	{ NULL, NULL, -1 }
};
// Itsk00126v2Request
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTDeviceEntry
static bool_t F2CIoTDeviceEntry_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	F2CIoTDeviceEntry *p = (F2CIoTDeviceEntry *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->iot_device_id); p->iot_device_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *F2CIoTDeviceEntry_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	F2CIoTDeviceEntry *p = (F2CIoTDeviceEntry *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->iot_device_id;
	default: return NULL;
	}
}

static Dz1JsonSpecChild F2CIoTDeviceEntry_membs[] =
{
	{ Dz1Text("iot_device_id"), Dz1Text("Dz1Str"), 0 },
	{ NULL, NULL, -1 }
};
// F2CIoTDeviceEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTDeviceList
static bool_t F2CIoTDeviceList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	F2CIoTDeviceList *dst = (F2CIoTDeviceList *)dst_ptr;
	F2CIoTDeviceEntry *node = NULL;
	if (dst == NULL || var == NULL || (node = (F2CIoTDeviceEntry *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t F2CIoTDeviceList_cnt(void *ptr)
{
	u32_t ret = 0;
	F2CIoTDeviceList *list = (F2CIoTDeviceList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error F2CIoTDeviceList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	F2CIoTDeviceList *list = (F2CIoTDeviceList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// F2CIoTDeviceList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTDeviceListResponseInfoData
static bool_t F2CIoTDeviceListResponseInfoData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	F2CIoTDeviceListResponseInfoData *p = (F2CIoTDeviceListResponseInfoData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->iot_im_device_id); p->iot_im_device_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->event_name); p->event_name = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->event_type); p->event_type = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 3: Dz1Str_delAndSetNull(&p->iot_device_id_qty); p->iot_device_id_qty = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 4: F2CIoTDeviceList_delAndSetNull(&p->iot_device_list); p->iot_device_list = (F2CIoTDeviceList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *F2CIoTDeviceListResponseInfoData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	F2CIoTDeviceListResponseInfoData *p = (F2CIoTDeviceListResponseInfoData *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->iot_im_device_id;
	case 1: return p->event_name;
	case 2: return p->event_type;
	case 3: return p->iot_device_id_qty;
	case 4: return p->iot_device_list;
	default: return NULL;
	}
}

static Dz1JsonSpecChild F2CIoTDeviceListResponseInfoData_membs[] =
{
	{ Dz1Text("iot_im_device_id"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("event_name"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("event_type"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("iot_device_id_qty"), Dz1Text("Dz1Str"), 3 },
	{ Dz1Text("iot_device_list"), Dz1Text("F2CIoTDeviceList"), 4 },
	{ NULL, NULL, -1 }
};
// F2CIoTDeviceListResponseInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTDeviceListResponseInfo
static bool_t F2CIoTDeviceListResponseInfo_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	F2CIoTDeviceListResponseInfo *p = (F2CIoTDeviceListResponseInfo *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->command); p->command = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: F2CIoTDeviceListResponseInfoData_delAndSetNull(&p->data); p->data = (F2CIoTDeviceListResponseInfoData *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *F2CIoTDeviceListResponseInfo_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	F2CIoTDeviceListResponseInfo *p = (F2CIoTDeviceListResponseInfo *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->command;
	case 1: return p->data;
	default: return NULL;
	}
}

static Dz1JsonSpecChild F2CIoTDeviceListResponseInfo_membs[] =
{
	{ Dz1Text("command"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("data"), Dz1Text("F2CIoTDeviceListResponseInfoData"), 1 },
	{ NULL, NULL, -1 }
};
// F2CIoTDeviceListResponseInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTDeviceSttusInfoEntry
static bool_t F2CIoTDeviceSttusInfoEntry_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	F2CIoTDeviceSttusInfoEntry *p = (F2CIoTDeviceSttusInfoEntry *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->iot_device_id); p->iot_device_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->iot_device_sttus_code); p->iot_device_sttus_code = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->btry_sttus_code); p->btry_sttus_code = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 3: Dz1Str_delAndSetNull(&p->link_sttus_code); p->link_sttus_code = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 4: p->data_trnsmis_cont =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *F2CIoTDeviceSttusInfoEntry_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	F2CIoTDeviceSttusInfoEntry *p = (F2CIoTDeviceSttusInfoEntry *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->iot_device_id;
	case 1: return p->iot_device_sttus_code;
	case 2: return p->btry_sttus_code;
	case 3: return p->link_sttus_code;
	case 4: return &p->data_trnsmis_cont;
	default: return NULL;
	}
}

static Dz1JsonSpecChild F2CIoTDeviceSttusInfoEntry_membs[] =
{
	{ Dz1Text("iot_device_id"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("iot_device_sttus_code"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("btry_sttus_code"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("link_sttus_code"), Dz1Text("Dz1Str"), 3 },
	{ Dz1Text("data_trnsmis_cont"), Dz1Text("s64_t"), 4 },
	{ NULL, NULL, -1 }
};
// F2CIoTDeviceSttusInfoEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTDeviceSttusInfoList
static bool_t F2CIoTDeviceSttusInfoList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	F2CIoTDeviceSttusInfoList *dst = (F2CIoTDeviceSttusInfoList *)dst_ptr;
	F2CIoTDeviceSttusInfoEntry *node = NULL;
	if (dst == NULL || var == NULL || (node = (F2CIoTDeviceSttusInfoEntry *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t F2CIoTDeviceSttusInfoList_cnt(void *ptr)
{
	u32_t ret = 0;
	F2CIoTDeviceSttusInfoList *list = (F2CIoTDeviceSttusInfoList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error F2CIoTDeviceSttusInfoList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	F2CIoTDeviceSttusInfoList *list = (F2CIoTDeviceSttusInfoList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// F2CIoTDeviceSttusInfoList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTDeviceSttusInfoData
static bool_t F2CIoTDeviceSttusInfoData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	F2CIoTDeviceSttusInfoData *p = (F2CIoTDeviceSttusInfoData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->iot_im_device_id); p->iot_im_device_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->iot_device_id_qty); p->iot_device_id_qty = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: F2CIoTDeviceSttusInfoList_delAndSetNull(&p->iot_device_sttus_info_list); p->iot_device_sttus_info_list = (F2CIoTDeviceSttusInfoList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: Dz1Str_delAndSetNull(&p->creat_dt); p->creat_dt = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *F2CIoTDeviceSttusInfoData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	F2CIoTDeviceSttusInfoData *p = (F2CIoTDeviceSttusInfoData *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->iot_im_device_id;
	case 1: return p->iot_device_id_qty;
	case 2: return p->iot_device_sttus_info_list;
	case 3: return p->creat_dt;
	default: return NULL;
	}
}

static Dz1JsonSpecChild F2CIoTDeviceSttusInfoData_membs[] =
{
	{ Dz1Text("iot_im_device_id"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("iot_device_id_qty"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("iot_device_sttus_info_list"), Dz1Text("F2CIoTDeviceSttusInfoList"), 2 },
	{ Dz1Text("creat_dt"), Dz1Text("Dz1Str"), 3 },
	{ NULL, NULL, -1 }
};
// F2CIoTDeviceSttusInfoData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// F2CIoTDeviceSttusInfo
static bool_t F2CIoTDeviceSttusInfo_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	F2CIoTDeviceSttusInfo *p = (F2CIoTDeviceSttusInfo *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->command); p->command = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: F2CIoTDeviceSttusInfoData_delAndSetNull(&p->data); p->data = (F2CIoTDeviceSttusInfoData *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *F2CIoTDeviceSttusInfo_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	F2CIoTDeviceSttusInfo *p = (F2CIoTDeviceSttusInfo *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->command;
	case 1: return p->data;
	default: return NULL;
	}
}

static Dz1JsonSpecChild F2CIoTDeviceSttusInfo_membs[] =
{
	{ Dz1Text("command"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("data"), Dz1Text("F2CIoTDeviceSttusInfoData"), 1 },
	{ NULL, NULL, -1 }
};
// F2CIoTDeviceSttusInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2EAM
static bool_t Itsk00126v2EAM_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Itsk00126v2EAM *p = (Itsk00126v2EAM *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Itsk00126v2EAMPresent_f2c_iot_im_device_sttus_info: F2CIoTImDeviceSttusInfo_delAndSetNull(&p->x.f2c_iot_im_device_sttus_info); p->x.f2c_iot_im_device_sttus_info =(F2CIoTImDeviceSttusInfo *)info->data; info->data = NULL; break;
	case Itsk00126v2EAMPresent_fc2_iot_device_list_request_info: Itsk00126v2Request_delAndSetNull(&p->x.fc2_iot_device_list_request_info); p->x.fc2_iot_device_list_request_info =(Itsk00126v2Request *)info->data; info->data = NULL; break;
	case Itsk00126v2EAMPresent_fc2_iot_device_list_response_info: F2CIoTDeviceListResponseInfo_delAndSetNull(&p->x.fc2_iot_device_list_response_info); p->x.fc2_iot_device_list_response_info =(F2CIoTDeviceListResponseInfo *)info->data; info->data = NULL; break;
	case Itsk00126v2EAMPresent_fc2_iot_device_list_reset_info: F2CIoTDeviceListResponseInfo_delAndSetNull(&p->x.fc2_iot_device_list_reset_info); p->x.fc2_iot_device_list_reset_info =(F2CIoTDeviceListResponseInfo *)info->data; info->data = NULL; break;
	case Itsk00126v2EAMPresent_fc2_iot_device_sttus_info: F2CIoTDeviceSttusInfo_delAndSetNull(&p->x.fc2_iot_device_sttus_info); p->x.fc2_iot_device_sttus_info =(F2CIoTDeviceSttusInfo *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Itsk00126v2EAMPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Itsk00126v2EAM_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Itsk00126v2EAM *p = (Itsk00126v2EAM *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Itsk00126v2EAMPresent_f2c_iot_im_device_sttus_info: return p->x.f2c_iot_im_device_sttus_info;
		case Itsk00126v2EAMPresent_fc2_iot_device_list_request_info: return p->x.fc2_iot_device_list_request_info;
		case Itsk00126v2EAMPresent_fc2_iot_device_list_response_info: return p->x.fc2_iot_device_list_response_info;
		case Itsk00126v2EAMPresent_fc2_iot_device_list_reset_info: return p->x.fc2_iot_device_list_reset_info;
		case Itsk00126v2EAMPresent_fc2_iot_device_sttus_info: return p->x.fc2_iot_device_sttus_info;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Itsk00126v2EAM_membs[] =
{
	{ Dz1Text("f2c_iot_im_device_sttus_info"), Dz1Text("F2CIoTImDeviceSttusInfo"), Itsk00126v2EAMPresent_f2c_iot_im_device_sttus_info },
	{ Dz1Text("fc2_iot_device_list_request_info"), Dz1Text("Itsk00126v2Request"), Itsk00126v2EAMPresent_fc2_iot_device_list_request_info },
	{ Dz1Text("fc2_iot_device_list_response_info"), Dz1Text("F2CIoTDeviceListResponseInfo"), Itsk00126v2EAMPresent_fc2_iot_device_list_response_info },
	{ Dz1Text("fc2_iot_device_list_reset_info"), Dz1Text("F2CIoTDeviceListResponseInfo"), Itsk00126v2EAMPresent_fc2_iot_device_list_reset_info },
	{ Dz1Text("fc2_iot_device_sttus_info"), Dz1Text("F2CIoTDeviceSttusInfo"), Itsk00126v2EAMPresent_fc2_iot_device_sttus_info },
	{ NULL, NULL, -1 }
};
// Itsk00126v2EAM
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2TestConfiguration_serverRole
static bool_t Itsk00126v2TestConfiguration_serverRole_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Itsk00126v2TestConfiguration_serverRole *p = (Itsk00126v2TestConfiguration_serverRole *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->local_port =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->iot_im_device_id); p->iot_im_device_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: p->test_iot_im_device_sttus_info =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->test_iot_device_list_response_info =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->test_iot_device_sttus_info =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->test_safety_signal_list_response_info =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Itsk00126v2TestConfiguration_serverRole_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Itsk00126v2TestConfiguration_serverRole *p = (Itsk00126v2TestConfiguration_serverRole *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->local_port;
	case 1: return p->iot_im_device_id;
	case 2: return &p->test_iot_im_device_sttus_info;
	case 3: return &p->test_iot_device_list_response_info;
	case 4: return &p->test_iot_device_sttus_info;
	case 5: return &p->test_safety_signal_list_response_info;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Itsk00126v2TestConfiguration_serverRole_membs[] =
{
	{ Dz1Text("local_port"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("iot_im_device_id"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("test_iot_im_device_sttus_info"), Dz1Text("bool_t"), 2 },
	{ Dz1Text("test_iot_device_list_response_info"), Dz1Text("bool_t"), 3 },
	{ Dz1Text("test_iot_device_sttus_info"), Dz1Text("bool_t"), 4 },
	{ Dz1Text("test_safety_signal_list_response_info"), Dz1Text("bool_t"), 5 },
	{ NULL, NULL, -1 }
};
// Itsk00126v2TestConfiguration_serverRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2TestConfiguration_clientRole
static bool_t Itsk00126v2TestConfiguration_clientRole_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Itsk00126v2TestConfiguration_clientRole *p = (Itsk00126v2TestConfiguration_clientRole *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->peer_ip); p->peer_ip = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->peer_port =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Itsk00126v2TestConfiguration_clientRole_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Itsk00126v2TestConfiguration_clientRole *p = (Itsk00126v2TestConfiguration_clientRole *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->peer_ip;
	case 1: return &p->peer_port;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Itsk00126v2TestConfiguration_clientRole_membs[] =
{
	{ Dz1Text("peer_ip"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("peer_port"), Dz1Text("bool_t"), 1 },
	{ NULL, NULL, -1 }
};
// Itsk00126v2TestConfiguration_clientRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Itsk00126v2TestConfiguration
static bool_t Itsk00126v2TestConfiguration_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Itsk00126v2TestConfiguration *p = (Itsk00126v2TestConfiguration *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Itsk00126v2TestConfigurationPresent_serverRole: Itsk00126v2TestConfiguration_serverRole_delAndSetNull(&p->x.serverRole); p->x.serverRole =(Itsk00126v2TestConfiguration_serverRole *)info->data; info->data = NULL; break;
	case Itsk00126v2TestConfigurationPresent_clientRole: Itsk00126v2TestConfiguration_clientRole_delAndSetNull(&p->x.clientRole); p->x.clientRole =(Itsk00126v2TestConfiguration_clientRole *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Itsk00126v2TestConfigurationPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Itsk00126v2TestConfiguration_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Itsk00126v2TestConfiguration *p = (Itsk00126v2TestConfiguration *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Itsk00126v2TestConfigurationPresent_serverRole: return p->x.serverRole;
		case Itsk00126v2TestConfigurationPresent_clientRole: return p->x.clientRole;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Itsk00126v2TestConfiguration_membs[] =
{
	{ Dz1Text("serverRole"), Dz1Text("Itsk00126v2TestConfiguration_serverRole"), Itsk00126v2TestConfigurationPresent_serverRole },
	{ Dz1Text("clientRole"), Dz1Text("Itsk00126v2TestConfiguration_clientRole"), Itsk00126v2TestConfigurationPresent_clientRole },
	{ NULL, NULL, -1 }
};
// Itsk00126v2TestConfiguration
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpec Initializer
bool_t Itsk00126v2TestScenarioDef_initJsonSpec(Dz1JsonSpec *dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (0) { }
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("F2CIoTImDeviceSttusInfoData"), F2CIoTImDeviceSttusInfoData_gen, F2CIoTImDeviceSttusInfoData_del, F2CIoTImDeviceSttusInfoData_setChild, F2CIoTImDeviceSttusInfoData_getChild, F2CIoTImDeviceSttusInfoData_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("F2CIoTImDeviceSttusInfo"), F2CIoTImDeviceSttusInfo_gen, F2CIoTImDeviceSttusInfo_del, F2CIoTImDeviceSttusInfo_setChild, F2CIoTImDeviceSttusInfo_getChild, F2CIoTImDeviceSttusInfo_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Itsk00126v2RequestData"), Itsk00126v2RequestData_gen, Itsk00126v2RequestData_del, Itsk00126v2RequestData_setChild, Itsk00126v2RequestData_getChild, Itsk00126v2RequestData_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Itsk00126v2Request"), Itsk00126v2Request_gen, Itsk00126v2Request_del, Itsk00126v2Request_setChild, Itsk00126v2Request_getChild, Itsk00126v2Request_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("F2CIoTDeviceEntry"), F2CIoTDeviceEntry_gen, F2CIoTDeviceEntry_del, F2CIoTDeviceEntry_setChild, F2CIoTDeviceEntry_getChild, F2CIoTDeviceEntry_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("F2CIoTDeviceListResponseInfoData"), F2CIoTDeviceListResponseInfoData_gen, F2CIoTDeviceListResponseInfoData_del, F2CIoTDeviceListResponseInfoData_setChild, F2CIoTDeviceListResponseInfoData_getChild, F2CIoTDeviceListResponseInfoData_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("F2CIoTDeviceListResponseInfo"), F2CIoTDeviceListResponseInfo_gen, F2CIoTDeviceListResponseInfo_del, F2CIoTDeviceListResponseInfo_setChild, F2CIoTDeviceListResponseInfo_getChild, F2CIoTDeviceListResponseInfo_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("F2CIoTDeviceSttusInfoEntry"), F2CIoTDeviceSttusInfoEntry_gen, F2CIoTDeviceSttusInfoEntry_del, F2CIoTDeviceSttusInfoEntry_setChild, F2CIoTDeviceSttusInfoEntry_getChild, F2CIoTDeviceSttusInfoEntry_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("F2CIoTDeviceSttusInfoData"), F2CIoTDeviceSttusInfoData_gen, F2CIoTDeviceSttusInfoData_del, F2CIoTDeviceSttusInfoData_setChild, F2CIoTDeviceSttusInfoData_getChild, F2CIoTDeviceSttusInfoData_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("F2CIoTDeviceSttusInfo"), F2CIoTDeviceSttusInfo_gen, F2CIoTDeviceSttusInfo_del, F2CIoTDeviceSttusInfo_setChild, F2CIoTDeviceSttusInfo_getChild, F2CIoTDeviceSttusInfo_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Itsk00126v2EAM"), Itsk00126v2EAM_gen, Itsk00126v2EAM_del, Itsk00126v2EAM_setChild, Itsk00126v2EAM_getChild, Itsk00126v2EAM_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Itsk00126v2TestConfiguration_serverRole"), Itsk00126v2TestConfiguration_serverRole_gen, Itsk00126v2TestConfiguration_serverRole_del, Itsk00126v2TestConfiguration_serverRole_setChild, Itsk00126v2TestConfiguration_serverRole_getChild, Itsk00126v2TestConfiguration_serverRole_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Itsk00126v2TestConfiguration_clientRole"), Itsk00126v2TestConfiguration_clientRole_gen, Itsk00126v2TestConfiguration_clientRole_del, Itsk00126v2TestConfiguration_clientRole_setChild, Itsk00126v2TestConfiguration_clientRole_getChild, Itsk00126v2TestConfiguration_clientRole_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Itsk00126v2TestConfiguration"), Itsk00126v2TestConfiguration_gen, Itsk00126v2TestConfiguration_del, Itsk00126v2TestConfiguration_setChild, Itsk00126v2TestConfiguration_getChild, Itsk00126v2TestConfiguration_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("F2CIoTDeviceList"), F2CIoTDeviceList_gen, F2CIoTDeviceList_del, F2CIoTDeviceList_append, F2CIoTDeviceList_cnt, F2CIoTDeviceList_tlv, Dz1Text("F2CIoTDeviceEntry") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("F2CIoTDeviceSttusInfoList"), F2CIoTDeviceSttusInfoList_gen, F2CIoTDeviceSttusInfoList_del, F2CIoTDeviceSttusInfoList_append, F2CIoTDeviceSttusInfoList_cnt, F2CIoTDeviceSttusInfoList_tlv, Dz1Text("F2CIoTDeviceSttusInfoEntry") )).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
Dz1JsonSpec *Itsk00126v2TestScenarioDef_genJsonSpec(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonSpec *ret = Dz1JsonSpec_generate(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonSpec_delAndSetNull, (void *)&ret);

		if (Itsk00126v2TestScenarioDef_initJsonSpec(ret, errp) == FALSE) ERR_OUT(errp);
		else if (Dz1JsonSpec_check(ret, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1JsonSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Dz1JsonSpec Initializer
////////////////////////////////////////////////////////////////////////////////

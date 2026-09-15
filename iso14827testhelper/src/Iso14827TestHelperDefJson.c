#include "Iso14827TestHelperDefJson.h"

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestNotifyStateContext
static bool_t Iso14827TestNotifyStateContext_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TestNotifyStateContext *p = (Iso14827TestNotifyStateContext *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->testName); p->testName = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->time =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->state); p->state = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Iso14827TestNotifyStateContext_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Iso14827TestNotifyStateContext *p = (Iso14827TestNotifyStateContext *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->testName;
	case 1: return &p->time;
	case 2: return p->state;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Iso14827TestNotifyStateContext_membs[] =
{
	{ Dz1Text("testName"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("time"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("state"), Dz1Text("Dz1Str"), 2 },
	{ NULL, NULL, -1 }
};
// Iso14827TestNotifyStateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Binary
// extern type
// Dz1Binary
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestNotifyInfoContext
static bool_t Iso14827TestNotifyInfoContext_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TestNotifyInfoContext *p = (Iso14827TestNotifyInfoContext *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->testName); p->testName = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->time =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->sender); p->sender = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 3: Dz1Str_delAndSetNull(&p->log); p->log = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 4: Dz1Binary_delAndSetNull(&p->data); p->data = (Dz1Binary *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 5: Dz1Str_delAndSetNull(&p->dataType); p->dataType = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Iso14827TestNotifyInfoContext_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Iso14827TestNotifyInfoContext *p = (Iso14827TestNotifyInfoContext *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->testName;
	case 1: return &p->time;
	case 2: return p->sender;
	case 3: return p->log;
	case 4: return p->data;
	case 5: return p->dataType;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Iso14827TestNotifyInfoContext_membs[] =
{
	{ Dz1Text("testName"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("time"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("sender"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("log"), Dz1Text("Dz1Str"), 3 },
	{ Dz1Text("data"), Dz1Text("Dz1Binary"), 4 },
	{ Dz1Text("dataType"), Dz1Text("Dz1Str"), 5 },
	{ NULL, NULL, -1 }
};
// Iso14827TestNotifyInfoContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestProcessStatusCode
static bool_t Iso14827TestProcessStatusCode_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TestProcessStatusCode v = Iso14827TestProcessStatusCode_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Iso14827TestProcessStatusCode)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Iso14827TestProcessStatusCodeFromStr(tok->v)) == Iso14827TestProcessStatusCode_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Iso14827TestProcessStatusCode_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Iso14827TestProcessStatusCode_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Iso14827TestProcessStatusCode v = *(Iso14827TestProcessStatusCode *)obj;
		Dz1Str str_v = Iso14827TestProcessStatusCodeStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Iso14827TestProcessStatusCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestNotifyErrorContext
static bool_t Iso14827TestNotifyErrorContext_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TestNotifyErrorContext *p = (Iso14827TestNotifyErrorContext *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->testName); p->testName = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->time =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->code =  *(Iso14827TestProcessStatusCode *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: Dz1Str_delAndSetNull(&p->desc); p->desc = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 4: Dz1Str_delAndSetNull(&p->log); p->log = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 5: Dz1Binary_delAndSetNull(&p->data); p->data = (Dz1Binary *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Iso14827TestNotifyErrorContext_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Iso14827TestNotifyErrorContext *p = (Iso14827TestNotifyErrorContext *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->testName;
	case 1: return &p->time;
	case 2: return &p->code;
	case 3: return p->desc;
	case 4: return p->log;
	case 5: return p->data;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Iso14827TestNotifyErrorContext_membs[] =
{
	{ Dz1Text("testName"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("time"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("code"), Dz1Text("Iso14827TestProcessStatusCode"), 2 },
	{ Dz1Text("desc"), Dz1Text("Dz1Str"), 3 },
	{ Dz1Text("log"), Dz1Text("Dz1Str"), 4 },
	{ Dz1Text("data"), Dz1Text("Dz1Binary"), 5 },
	{ NULL, NULL, -1 }
};
// Iso14827TestNotifyErrorContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestNotifyContext
static bool_t Iso14827TestNotifyContext_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TestNotifyContext *p = (Iso14827TestNotifyContext *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Iso14827TestNotifyContextPresent_state: Iso14827TestNotifyStateContext_delAndSetNull(&p->x.state); p->x.state =(Iso14827TestNotifyStateContext *)info->data; info->data = NULL; break;
	case Iso14827TestNotifyContextPresent_info: Iso14827TestNotifyInfoContext_delAndSetNull(&p->x.info); p->x.info =(Iso14827TestNotifyInfoContext *)info->data; info->data = NULL; break;
	case Iso14827TestNotifyContextPresent_error: Iso14827TestNotifyErrorContext_delAndSetNull(&p->x.error); p->x.error =(Iso14827TestNotifyErrorContext *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Iso14827TestNotifyContextPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Iso14827TestNotifyContext_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Iso14827TestNotifyContext *p = (Iso14827TestNotifyContext *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Iso14827TestNotifyContextPresent_state: return p->x.state;
		case Iso14827TestNotifyContextPresent_info: return p->x.info;
		case Iso14827TestNotifyContextPresent_error: return p->x.error;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Iso14827TestNotifyContext_membs[] =
{
	{ Dz1Text("state"), Dz1Text("Iso14827TestNotifyStateContext"), Iso14827TestNotifyContextPresent_state },
	{ Dz1Text("info"), Dz1Text("Iso14827TestNotifyInfoContext"), Iso14827TestNotifyContextPresent_info },
	{ Dz1Text("error"), Dz1Text("Iso14827TestNotifyErrorContext"), Iso14827TestNotifyContextPresent_error },
	{ NULL, NULL, -1 }
};
// Iso14827TestNotifyContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestValidateContext
static bool_t Iso14827TestValidateContext_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TestValidateContext *p = (Iso14827TestValidateContext *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->testName); p->testName = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->time =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: Dz1Binary_delAndSetNull(&p->raw); p->raw = (Dz1Binary *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: Dz1Binary_delAndSetNull(&p->data); p->data = (Dz1Binary *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 4: p->code =  *(Iso14827TestProcessStatusCode *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: Dz1Str_delAndSetNull(&p->desc); p->desc = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Iso14827TestValidateContext_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Iso14827TestValidateContext *p = (Iso14827TestValidateContext *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->testName;
	case 1: return &p->time;
	case 2: return p->raw;
	case 3: return p->data;
	case 4: return &p->code;
	case 5: return p->desc;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Iso14827TestValidateContext_membs[] =
{
	{ Dz1Text("testName"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("time"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("raw"), Dz1Text("Dz1Binary"), 2 },
	{ Dz1Text("data"), Dz1Text("Dz1Binary"), 3 },
	{ Dz1Text("code"), Dz1Text("Iso14827TestProcessStatusCode"), 4 },
	{ Dz1Text("desc"), Dz1Text("Dz1Str"), 5 },
	{ NULL, NULL, -1 }
};
// Iso14827TestValidateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PositionalAccuracy
static bool_t Gitsn_PositionalAccuracy_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_PositionalAccuracy *p = (Gitsn_PositionalAccuracy *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->semiMajor =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->semiMinor =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->orientation =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_PositionalAccuracy_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_PositionalAccuracy *p = (Gitsn_PositionalAccuracy *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->semiMajor;
	case 1: return &p->semiMinor;
	case 2: return &p->orientation;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_PositionalAccuracy_membs[] =
{
	{ Dz1Text("semiMajor"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("semiMinor"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("orientation"), Dz1Text("s64_t"), 2 },
	{ NULL, NULL, -1 }
};
// Gitsn_PositionalAccuracy
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TransmissionState
static bool_t Gitsn_TransmissionState_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_TransmissionState v = Gitsn_TransmissionState_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_TransmissionState)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_TransmissionStateFromStr(tok->v)) == Gitsn_TransmissionState_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_TransmissionState_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_TransmissionState_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_TransmissionState v = *(Gitsn_TransmissionState *)obj;
		Dz1Str str_v = Gitsn_TransmissionStateStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_TransmissionState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AccelerationSet4Way
static bool_t Gitsn_AccelerationSet4Way_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_AccelerationSet4Way *p = (Gitsn_AccelerationSet4Way *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->lon =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->lat =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->vert =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->yaw =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_AccelerationSet4Way_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_AccelerationSet4Way *p = (Gitsn_AccelerationSet4Way *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->lon;
	case 1: return &p->lat;
	case 2: return &p->vert;
	case 3: return &p->yaw;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_AccelerationSet4Way_membs[] =
{
	{ Dz1Text("lon"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("lat"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("vert"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("yaw"), Dz1Text("s64_t"), 3 },
	{ NULL, NULL, -1 }
};
// Gitsn_AccelerationSet4Way
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TractionControlStatus
static bool_t Gitsn_TractionControlStatus_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_TractionControlStatus v = Gitsn_TractionControlStatus_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_TractionControlStatus)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_TractionControlStatusFromStr(tok->v)) == Gitsn_TractionControlStatus_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_TractionControlStatus_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_TractionControlStatus_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_TractionControlStatus v = *(Gitsn_TractionControlStatus *)obj;
		Dz1Str str_v = Gitsn_TractionControlStatusStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_TractionControlStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AntiLockBrakeStatus
static bool_t Gitsn_AntiLockBrakeStatus_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_AntiLockBrakeStatus v = Gitsn_AntiLockBrakeStatus_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_AntiLockBrakeStatus)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_AntiLockBrakeStatusFromStr(tok->v)) == Gitsn_AntiLockBrakeStatus_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_AntiLockBrakeStatus_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_AntiLockBrakeStatus_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_AntiLockBrakeStatus v = *(Gitsn_AntiLockBrakeStatus *)obj;
		Dz1Str str_v = Gitsn_AntiLockBrakeStatusStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_AntiLockBrakeStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_StabilityControlStatus
static bool_t Gitsn_StabilityControlStatus_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_StabilityControlStatus v = Gitsn_StabilityControlStatus_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_StabilityControlStatus)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_StabilityControlStatusFromStr(tok->v)) == Gitsn_StabilityControlStatus_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_StabilityControlStatus_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_StabilityControlStatus_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_StabilityControlStatus v = *(Gitsn_StabilityControlStatus *)obj;
		Dz1Str str_v = Gitsn_StabilityControlStatusStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_StabilityControlStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_BrakeBoostApplied
static bool_t Gitsn_BrakeBoostApplied_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_BrakeBoostApplied v = Gitsn_BrakeBoostApplied_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_BrakeBoostApplied)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_BrakeBoostAppliedFromStr(tok->v)) == Gitsn_BrakeBoostApplied_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_BrakeBoostApplied_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_BrakeBoostApplied_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_BrakeBoostApplied v = *(Gitsn_BrakeBoostApplied *)obj;
		Dz1Str str_v = Gitsn_BrakeBoostAppliedStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_BrakeBoostApplied
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AuxiliaryBrakeStatus
static bool_t Gitsn_AuxiliaryBrakeStatus_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_AuxiliaryBrakeStatus v = Gitsn_AuxiliaryBrakeStatus_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_AuxiliaryBrakeStatus)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_AuxiliaryBrakeStatusFromStr(tok->v)) == Gitsn_AuxiliaryBrakeStatus_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_AuxiliaryBrakeStatus_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_AuxiliaryBrakeStatus_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_AuxiliaryBrakeStatus v = *(Gitsn_AuxiliaryBrakeStatus *)obj;
		Dz1Str str_v = Gitsn_AuxiliaryBrakeStatusStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_AuxiliaryBrakeStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_BrakeSystemStatus
static bool_t Gitsn_BrakeSystemStatus_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_BrakeSystemStatus *p = (Gitsn_BrakeSystemStatus *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: u8_t_delAndSetNull(&p->wheelBrakes); p->wheelBrakes = (u8_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: p->traction =  *(Gitsn_TractionControlStatus *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->abs =  *(Gitsn_AntiLockBrakeStatus *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->scs =  *(Gitsn_StabilityControlStatus *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->brakeBoost =  *(Gitsn_BrakeBoostApplied *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->auxBrakes =  *(Gitsn_AuxiliaryBrakeStatus *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_BrakeSystemStatus_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_BrakeSystemStatus *p = (Gitsn_BrakeSystemStatus *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->wheelBrakes;
	case 1: return &p->traction;
	case 2: return &p->abs;
	case 3: return &p->scs;
	case 4: return &p->brakeBoost;
	case 5: return &p->auxBrakes;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_BrakeSystemStatus_membs[] =
{
	{ Dz1Text("wheelBrakes"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("traction"), Dz1Text("Gitsn_TractionControlStatus"), 1 },
	{ Dz1Text("abs"), Dz1Text("Gitsn_AntiLockBrakeStatus"), 2 },
	{ Dz1Text("scs"), Dz1Text("Gitsn_StabilityControlStatus"), 3 },
	{ Dz1Text("brakeBoost"), Dz1Text("Gitsn_BrakeBoostApplied"), 4 },
	{ Dz1Text("auxBrakes"), Dz1Text("Gitsn_AuxiliaryBrakeStatus"), 5 },
	{ NULL, NULL, -1 }
};
// Gitsn_BrakeSystemStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleSize
static bool_t Gitsn_VehicleSize_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_VehicleSize *p = (Gitsn_VehicleSize *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->width =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->length =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_VehicleSize_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_VehicleSize *p = (Gitsn_VehicleSize *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->width;
	case 1: return &p->length;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_VehicleSize_membs[] =
{
	{ Dz1Text("width"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("length"), Dz1Text("s64_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_VehicleSize
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_BSMCoreData
static bool_t Gitsn_BSMCoreData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_BSMCoreData *p = (Gitsn_BSMCoreData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->msgCnt =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->id); p->id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: p->secMark =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->lat =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->lon =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->elev =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: Gitsn_PositionalAccuracy_delAndSetNull(&p->accuracy); p->accuracy = (Gitsn_PositionalAccuracy *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 7: p->transmission =  *(Gitsn_TransmissionState *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->speed =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 9: p->heading =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 10: p->angle =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 11: Gitsn_AccelerationSet4Way_delAndSetNull(&p->accelSet); p->accelSet = (Gitsn_AccelerationSet4Way *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 12: Gitsn_BrakeSystemStatus_delAndSetNull(&p->brakes); p->brakes = (Gitsn_BrakeSystemStatus *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 13: Gitsn_VehicleSize_delAndSetNull(&p->size); p->size = (Gitsn_VehicleSize *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_BSMCoreData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_BSMCoreData *p = (Gitsn_BSMCoreData *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->msgCnt;
	case 1: return p->id;
	case 2: return &p->secMark;
	case 3: return &p->lat;
	case 4: return &p->lon;
	case 5: return &p->elev;
	case 6: return p->accuracy;
	case 7: return &p->transmission;
	case 8: return &p->speed;
	case 9: return &p->heading;
	case 10: return &p->angle;
	case 11: return p->accelSet;
	case 12: return p->brakes;
	case 13: return p->size;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_BSMCoreData_membs[] =
{
	{ Dz1Text("msgCnt"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("id"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("secMark"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("lat"), Dz1Text("s64_t"), 3 },
	{ Dz1Text("lon"), Dz1Text("s64_t"), 4 },
	{ Dz1Text("elev"), Dz1Text("s64_t"), 5 },
	{ Dz1Text("accuracy"), Dz1Text("Gitsn_PositionalAccuracy"), 6 },
	{ Dz1Text("transmission"), Dz1Text("Gitsn_TransmissionState"), 7 },
	{ Dz1Text("speed"), Dz1Text("s64_t"), 8 },
	{ Dz1Text("heading"), Dz1Text("s64_t"), 9 },
	{ Dz1Text("angle"), Dz1Text("s64_t"), 10 },
	{ Dz1Text("accelSet"), Dz1Text("Gitsn_AccelerationSet4Way"), 11 },
	{ Dz1Text("brakes"), Dz1Text("Gitsn_BrakeSystemStatus"), 12 },
	{ Dz1Text("size"), Dz1Text("Gitsn_VehicleSize"), 13 },
	{ NULL, NULL, -1 }
};
// Gitsn_BSMCoreData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_BasicSafetyMessage
static bool_t Gitsn_BasicSafetyMessage_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_BasicSafetyMessage *p = (Gitsn_BasicSafetyMessage *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Gitsn_BSMCoreData_delAndSetNull(&p->coreData); p->coreData = (Gitsn_BSMCoreData *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_BasicSafetyMessage_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_BasicSafetyMessage *p = (Gitsn_BasicSafetyMessage *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->coreData;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_BasicSafetyMessage_membs[] =
{
	{ Dz1Text("coreData"), Dz1Text("Gitsn_BSMCoreData"), 0 },
	{ NULL, NULL, -1 }
};
// Gitsn_BasicSafetyMessage
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LayerType
static bool_t Gitsn_LayerType_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_LayerType v = Gitsn_LayerType_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_LayerType)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_LayerTypeFromStr(tok->v)) == Gitsn_LayerType_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_LayerType_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_LayerType_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_LayerType v = *(Gitsn_LayerType *)obj;
		Dz1Str str_v = Gitsn_LayerTypeStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_LayerType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IntersectionReferenceID
static bool_t Gitsn_IntersectionReferenceID_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_IntersectionReferenceID *p = (Gitsn_IntersectionReferenceID *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->region =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->id =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_IntersectionReferenceID_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_IntersectionReferenceID *p = (Gitsn_IntersectionReferenceID *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->region;
	case 1: return &p->id;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_IntersectionReferenceID_membs[] =
{
	{ Dz1Text("region"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("id"), Dz1Text("s64_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_IntersectionReferenceID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Position3D
static bool_t Gitsn_Position3D_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Position3D *p = (Gitsn_Position3D *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->lat =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->lon =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->elevation =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Position3D_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Position3D *p = (Gitsn_Position3D *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->lat;
	case 1: return &p->lon;
	case 2: return &p->elevation;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Position3D_membs[] =
{
	{ Dz1Text("lat"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("lon"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("elevation"), Dz1Text("s64_t"), 2 },
	{ NULL, NULL, -1 }
};
// Gitsn_Position3D
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SpeedLimitType
static bool_t Gitsn_SpeedLimitType_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_SpeedLimitType v = Gitsn_SpeedLimitType_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_SpeedLimitType)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_SpeedLimitTypeFromStr(tok->v)) == Gitsn_SpeedLimitType_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_SpeedLimitType_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_SpeedLimitType_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_SpeedLimitType v = *(Gitsn_SpeedLimitType *)obj;
		Dz1Str str_v = Gitsn_SpeedLimitTypeStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_SpeedLimitType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RegulatorySpeedLimit
static bool_t Gitsn_RegulatorySpeedLimit_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_RegulatorySpeedLimit *p = (Gitsn_RegulatorySpeedLimit *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->type =  *(Gitsn_SpeedLimitType *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->speed =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_RegulatorySpeedLimit_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_RegulatorySpeedLimit *p = (Gitsn_RegulatorySpeedLimit *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->type;
	case 1: return &p->speed;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_RegulatorySpeedLimit_membs[] =
{
	{ Dz1Text("type"), Dz1Text("Gitsn_SpeedLimitType"), 0 },
	{ Dz1Text("speed"), Dz1Text("s64_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_RegulatorySpeedLimit
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SpeedLimitList
static bool_t Gitsn_SpeedLimitList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_SpeedLimitList *dst = (Gitsn_SpeedLimitList *)dst_ptr;
	Gitsn_RegulatorySpeedLimit *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_RegulatorySpeedLimit *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_SpeedLimitList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_SpeedLimitList *list = (Gitsn_SpeedLimitList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_SpeedLimitList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_SpeedLimitList *list = (Gitsn_SpeedLimitList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_SpeedLimitList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LaneTypeAttributes
static bool_t Gitsn_LaneTypeAttributes_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_LaneTypeAttributes *p = (Gitsn_LaneTypeAttributes *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_LaneTypeAttributesPresent_vehicle: u8_t_delAndSetNull(&p->x.vehicle); p->x.vehicle =(u8_t *)info->data; info->data = NULL; break;
	case Gitsn_LaneTypeAttributesPresent_crosswalk: u8_t_delAndSetNull(&p->x.crosswalk); p->x.crosswalk =(u8_t *)info->data; info->data = NULL; break;
	case Gitsn_LaneTypeAttributesPresent_bikeLane: u8_t_delAndSetNull(&p->x.bikeLane); p->x.bikeLane =(u8_t *)info->data; info->data = NULL; break;
	case Gitsn_LaneTypeAttributesPresent_sidewalk: u8_t_delAndSetNull(&p->x.sidewalk); p->x.sidewalk =(u8_t *)info->data; info->data = NULL; break;
	case Gitsn_LaneTypeAttributesPresent_median: u8_t_delAndSetNull(&p->x.median); p->x.median =(u8_t *)info->data; info->data = NULL; break;
	case Gitsn_LaneTypeAttributesPresent_striping: u8_t_delAndSetNull(&p->x.striping); p->x.striping =(u8_t *)info->data; info->data = NULL; break;
	case Gitsn_LaneTypeAttributesPresent_trackedVehicle: u8_t_delAndSetNull(&p->x.trackedVehicle); p->x.trackedVehicle =(u8_t *)info->data; info->data = NULL; break;
	case Gitsn_LaneTypeAttributesPresent_parking: u8_t_delAndSetNull(&p->x.parking); p->x.parking =(u8_t *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_LaneTypeAttributesPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_LaneTypeAttributes_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_LaneTypeAttributes *p = (Gitsn_LaneTypeAttributes *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_LaneTypeAttributesPresent_vehicle: return p->x.vehicle;
		case Gitsn_LaneTypeAttributesPresent_crosswalk: return p->x.crosswalk;
		case Gitsn_LaneTypeAttributesPresent_bikeLane: return p->x.bikeLane;
		case Gitsn_LaneTypeAttributesPresent_sidewalk: return p->x.sidewalk;
		case Gitsn_LaneTypeAttributesPresent_median: return p->x.median;
		case Gitsn_LaneTypeAttributesPresent_striping: return p->x.striping;
		case Gitsn_LaneTypeAttributesPresent_trackedVehicle: return p->x.trackedVehicle;
		case Gitsn_LaneTypeAttributesPresent_parking: return p->x.parking;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_LaneTypeAttributes_membs[] =
{
	{ Dz1Text("vehicle"), Dz1Text("u8_t"), Gitsn_LaneTypeAttributesPresent_vehicle },
	{ Dz1Text("crosswalk"), Dz1Text("u8_t"), Gitsn_LaneTypeAttributesPresent_crosswalk },
	{ Dz1Text("bikeLane"), Dz1Text("u8_t"), Gitsn_LaneTypeAttributesPresent_bikeLane },
	{ Dz1Text("sidewalk"), Dz1Text("u8_t"), Gitsn_LaneTypeAttributesPresent_sidewalk },
	{ Dz1Text("median"), Dz1Text("u8_t"), Gitsn_LaneTypeAttributesPresent_median },
	{ Dz1Text("striping"), Dz1Text("u8_t"), Gitsn_LaneTypeAttributesPresent_striping },
	{ Dz1Text("trackedVehicle"), Dz1Text("u8_t"), Gitsn_LaneTypeAttributesPresent_trackedVehicle },
	{ Dz1Text("parking"), Dz1Text("u8_t"), Gitsn_LaneTypeAttributesPresent_parking },
	{ NULL, NULL, -1 }
};
// Gitsn_LaneTypeAttributes
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LaneAttributes
static bool_t Gitsn_LaneAttributes_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_LaneAttributes *p = (Gitsn_LaneAttributes *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: u8_t_delAndSetNull(&p->directionalUse); p->directionalUse = (u8_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: u8_t_delAndSetNull(&p->sharedWith); p->sharedWith = (u8_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: Gitsn_LaneTypeAttributes_delAndSetNull(&p->laneType); p->laneType = (Gitsn_LaneTypeAttributes *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_LaneAttributes_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_LaneAttributes *p = (Gitsn_LaneAttributes *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->directionalUse;
	case 1: return p->sharedWith;
	case 2: return p->laneType;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_LaneAttributes_membs[] =
{
	{ Dz1Text("directionalUse"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("sharedWith"), Dz1Text("u8_t"), 1 },
	{ Dz1Text("laneType"), Dz1Text("Gitsn_LaneTypeAttributes"), 2 },
	{ NULL, NULL, -1 }
};
// Gitsn_LaneAttributes
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_XY_20b
static bool_t Gitsn_Node_XY_20b_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Node_XY_20b *p = (Gitsn_Node_XY_20b *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->x =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->y =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Node_XY_20b_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Node_XY_20b *p = (Gitsn_Node_XY_20b *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->x;
	case 1: return &p->y;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Node_XY_20b_membs[] =
{
	{ Dz1Text("x"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("y"), Dz1Text("s64_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_Node_XY_20b
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_XY_22b
static bool_t Gitsn_Node_XY_22b_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Node_XY_22b *p = (Gitsn_Node_XY_22b *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->x =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->y =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Node_XY_22b_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Node_XY_22b *p = (Gitsn_Node_XY_22b *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->x;
	case 1: return &p->y;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Node_XY_22b_membs[] =
{
	{ Dz1Text("x"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("y"), Dz1Text("s64_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_Node_XY_22b
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_XY_24b
static bool_t Gitsn_Node_XY_24b_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Node_XY_24b *p = (Gitsn_Node_XY_24b *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->x =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->y =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Node_XY_24b_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Node_XY_24b *p = (Gitsn_Node_XY_24b *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->x;
	case 1: return &p->y;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Node_XY_24b_membs[] =
{
	{ Dz1Text("x"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("y"), Dz1Text("s64_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_Node_XY_24b
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_XY_26b
static bool_t Gitsn_Node_XY_26b_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Node_XY_26b *p = (Gitsn_Node_XY_26b *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->x =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->y =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Node_XY_26b_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Node_XY_26b *p = (Gitsn_Node_XY_26b *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->x;
	case 1: return &p->y;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Node_XY_26b_membs[] =
{
	{ Dz1Text("x"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("y"), Dz1Text("s64_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_Node_XY_26b
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_XY_28b
static bool_t Gitsn_Node_XY_28b_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Node_XY_28b *p = (Gitsn_Node_XY_28b *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->x =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->y =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Node_XY_28b_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Node_XY_28b *p = (Gitsn_Node_XY_28b *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->x;
	case 1: return &p->y;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Node_XY_28b_membs[] =
{
	{ Dz1Text("x"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("y"), Dz1Text("s64_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_Node_XY_28b
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_XY_32b
static bool_t Gitsn_Node_XY_32b_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Node_XY_32b *p = (Gitsn_Node_XY_32b *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->x =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->y =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Node_XY_32b_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Node_XY_32b *p = (Gitsn_Node_XY_32b *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->x;
	case 1: return &p->y;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Node_XY_32b_membs[] =
{
	{ Dz1Text("x"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("y"), Dz1Text("s64_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_Node_XY_32b
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_LLmD_64b
static bool_t Gitsn_Node_LLmD_64b_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Node_LLmD_64b *p = (Gitsn_Node_LLmD_64b *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->lon =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->lat =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Node_LLmD_64b_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Node_LLmD_64b *p = (Gitsn_Node_LLmD_64b *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->lon;
	case 1: return &p->lat;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Node_LLmD_64b_membs[] =
{
	{ Dz1Text("lon"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("lat"), Dz1Text("s64_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_Node_LLmD_64b
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeOffsetPointXY
static bool_t Gitsn_NodeOffsetPointXY_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_NodeOffsetPointXY *p = (Gitsn_NodeOffsetPointXY *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_NodeOffsetPointXYPresent_node_XY1: Gitsn_Node_XY_20b_delAndSetNull(&p->x.node_XY1); p->x.node_XY1 =(Gitsn_Node_XY_20b *)info->data; info->data = NULL; break;
	case Gitsn_NodeOffsetPointXYPresent_node_XY2: Gitsn_Node_XY_22b_delAndSetNull(&p->x.node_XY2); p->x.node_XY2 =(Gitsn_Node_XY_22b *)info->data; info->data = NULL; break;
	case Gitsn_NodeOffsetPointXYPresent_node_XY3: Gitsn_Node_XY_24b_delAndSetNull(&p->x.node_XY3); p->x.node_XY3 =(Gitsn_Node_XY_24b *)info->data; info->data = NULL; break;
	case Gitsn_NodeOffsetPointXYPresent_node_XY4: Gitsn_Node_XY_26b_delAndSetNull(&p->x.node_XY4); p->x.node_XY4 =(Gitsn_Node_XY_26b *)info->data; info->data = NULL; break;
	case Gitsn_NodeOffsetPointXYPresent_node_XY5: Gitsn_Node_XY_28b_delAndSetNull(&p->x.node_XY5); p->x.node_XY5 =(Gitsn_Node_XY_28b *)info->data; info->data = NULL; break;
	case Gitsn_NodeOffsetPointXYPresent_node_XY6: Gitsn_Node_XY_32b_delAndSetNull(&p->x.node_XY6); p->x.node_XY6 =(Gitsn_Node_XY_32b *)info->data; info->data = NULL; break;
	case Gitsn_NodeOffsetPointXYPresent_node_LatLon: Gitsn_Node_LLmD_64b_delAndSetNull(&p->x.node_LatLon); p->x.node_LatLon =(Gitsn_Node_LLmD_64b *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_NodeOffsetPointXYPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_NodeOffsetPointXY_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_NodeOffsetPointXY *p = (Gitsn_NodeOffsetPointXY *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_NodeOffsetPointXYPresent_node_XY1: return p->x.node_XY1;
		case Gitsn_NodeOffsetPointXYPresent_node_XY2: return p->x.node_XY2;
		case Gitsn_NodeOffsetPointXYPresent_node_XY3: return p->x.node_XY3;
		case Gitsn_NodeOffsetPointXYPresent_node_XY4: return p->x.node_XY4;
		case Gitsn_NodeOffsetPointXYPresent_node_XY5: return p->x.node_XY5;
		case Gitsn_NodeOffsetPointXYPresent_node_XY6: return p->x.node_XY6;
		case Gitsn_NodeOffsetPointXYPresent_node_LatLon: return p->x.node_LatLon;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_NodeOffsetPointXY_membs[] =
{
	{ Dz1Text("node_XY1"), Dz1Text("Gitsn_Node_XY_20b"), Gitsn_NodeOffsetPointXYPresent_node_XY1 },
	{ Dz1Text("node_XY2"), Dz1Text("Gitsn_Node_XY_22b"), Gitsn_NodeOffsetPointXYPresent_node_XY2 },
	{ Dz1Text("node_XY3"), Dz1Text("Gitsn_Node_XY_24b"), Gitsn_NodeOffsetPointXYPresent_node_XY3 },
	{ Dz1Text("node_XY4"), Dz1Text("Gitsn_Node_XY_26b"), Gitsn_NodeOffsetPointXYPresent_node_XY4 },
	{ Dz1Text("node_XY5"), Dz1Text("Gitsn_Node_XY_28b"), Gitsn_NodeOffsetPointXYPresent_node_XY5 },
	{ Dz1Text("node_XY6"), Dz1Text("Gitsn_Node_XY_32b"), Gitsn_NodeOffsetPointXYPresent_node_XY6 },
	{ Dz1Text("node_LatLon"), Dz1Text("Gitsn_Node_LLmD_64b"), Gitsn_NodeOffsetPointXYPresent_node_LatLon },
	{ NULL, NULL, -1 }
};
// Gitsn_NodeOffsetPointXY
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeAttributeXY
static bool_t Gitsn_NodeAttributeXY_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_NodeAttributeXY v = Gitsn_NodeAttributeXY_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_NodeAttributeXY)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_NodeAttributeXYFromStr(tok->v)) == Gitsn_NodeAttributeXY_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_NodeAttributeXY_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_NodeAttributeXY_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_NodeAttributeXY v = *(Gitsn_NodeAttributeXY *)obj;
		Dz1Str str_v = Gitsn_NodeAttributeXYStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_NodeAttributeXY
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeAttributeXYList
static bool_t Gitsn_NodeAttributeXYList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_NodeAttributeXYList *dst = (Gitsn_NodeAttributeXYList *)dst_ptr;
	Gitsn_NodeAttributeXY *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_NodeAttributeXY *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, *node)).code) ERR_OUT(errp);
	else
	{
		// var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_NodeAttributeXYList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_NodeAttributeXYList *list = (Gitsn_NodeAttributeXYList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_NodeAttributeXYList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_NodeAttributeXYList *list = (Gitsn_NodeAttributeXYList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_NodeAttributeXYList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SegmentAttributeXY
static bool_t Gitsn_SegmentAttributeXY_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_SegmentAttributeXY v = Gitsn_SegmentAttributeXY_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_SegmentAttributeXY)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_SegmentAttributeXYFromStr(tok->v)) == Gitsn_SegmentAttributeXY_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_SegmentAttributeXY_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_SegmentAttributeXY_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_SegmentAttributeXY v = *(Gitsn_SegmentAttributeXY *)obj;
		Dz1Str str_v = Gitsn_SegmentAttributeXYStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_SegmentAttributeXY
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SegmentAttributeXYList
static bool_t Gitsn_SegmentAttributeXYList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_SegmentAttributeXYList *dst = (Gitsn_SegmentAttributeXYList *)dst_ptr;
	Gitsn_SegmentAttributeXY *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_SegmentAttributeXY *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, *node)).code) ERR_OUT(errp);
	else
	{
		// var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_SegmentAttributeXYList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_SegmentAttributeXYList *list = (Gitsn_SegmentAttributeXYList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_SegmentAttributeXYList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_SegmentAttributeXYList *list = (Gitsn_SegmentAttributeXYList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_SegmentAttributeXYList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LaneDataAttribute
static bool_t Gitsn_LaneDataAttribute_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_LaneDataAttribute *p = (Gitsn_LaneDataAttribute *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_LaneDataAttributePresent_pathEndPointAngle: p->x.pathEndPointAngle = *(s64_t *)info->data; break;
	case Gitsn_LaneDataAttributePresent_laneCrownPointCenter: p->x.laneCrownPointCenter = *(s64_t *)info->data; break;
	case Gitsn_LaneDataAttributePresent_laneCrownPointLeft: p->x.laneCrownPointLeft = *(s64_t *)info->data; break;
	case Gitsn_LaneDataAttributePresent_laneCrownPointRight: p->x.laneCrownPointRight = *(s64_t *)info->data; break;
	case Gitsn_LaneDataAttributePresent_laneAngle: p->x.laneAngle = *(s64_t *)info->data; break;
	case Gitsn_LaneDataAttributePresent_speedLimits: Gitsn_SpeedLimitList_delAndSetNull(&p->x.speedLimits); p->x.speedLimits =(Gitsn_SpeedLimitList *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_LaneDataAttributePresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_LaneDataAttribute_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_LaneDataAttribute *p = (Gitsn_LaneDataAttribute *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_LaneDataAttributePresent_pathEndPointAngle: return &p->x.pathEndPointAngle;
		case Gitsn_LaneDataAttributePresent_laneCrownPointCenter: return &p->x.laneCrownPointCenter;
		case Gitsn_LaneDataAttributePresent_laneCrownPointLeft: return &p->x.laneCrownPointLeft;
		case Gitsn_LaneDataAttributePresent_laneCrownPointRight: return &p->x.laneCrownPointRight;
		case Gitsn_LaneDataAttributePresent_laneAngle: return &p->x.laneAngle;
		case Gitsn_LaneDataAttributePresent_speedLimits: return p->x.speedLimits;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_LaneDataAttribute_membs[] =
{
	{ Dz1Text("pathEndPointAngle"), Dz1Text("s64_t"), Gitsn_LaneDataAttributePresent_pathEndPointAngle },
	{ Dz1Text("laneCrownPointCenter"), Dz1Text("s64_t"), Gitsn_LaneDataAttributePresent_laneCrownPointCenter },
	{ Dz1Text("laneCrownPointLeft"), Dz1Text("s64_t"), Gitsn_LaneDataAttributePresent_laneCrownPointLeft },
	{ Dz1Text("laneCrownPointRight"), Dz1Text("s64_t"), Gitsn_LaneDataAttributePresent_laneCrownPointRight },
	{ Dz1Text("laneAngle"), Dz1Text("s64_t"), Gitsn_LaneDataAttributePresent_laneAngle },
	{ Dz1Text("speedLimits"), Dz1Text("Gitsn_SpeedLimitList"), Gitsn_LaneDataAttributePresent_speedLimits },
	{ NULL, NULL, -1 }
};
// Gitsn_LaneDataAttribute
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LaneDataAttributeList
static bool_t Gitsn_LaneDataAttributeList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_LaneDataAttributeList *dst = (Gitsn_LaneDataAttributeList *)dst_ptr;
	Gitsn_LaneDataAttribute *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_LaneDataAttribute *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_LaneDataAttributeList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_LaneDataAttributeList *list = (Gitsn_LaneDataAttributeList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_LaneDataAttributeList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_LaneDataAttributeList *list = (Gitsn_LaneDataAttributeList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_LaneDataAttributeList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeAttributeSetXY
static bool_t Gitsn_NodeAttributeSetXY_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_NodeAttributeSetXY *p = (Gitsn_NodeAttributeSetXY *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Gitsn_NodeAttributeXYList_delAndSetNull(&p->localNode); p->localNode = (Gitsn_NodeAttributeXYList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: Gitsn_SegmentAttributeXYList_delAndSetNull(&p->disabled); p->disabled = (Gitsn_SegmentAttributeXYList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: Gitsn_SegmentAttributeXYList_delAndSetNull(&p->enabled); p->enabled = (Gitsn_SegmentAttributeXYList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: Gitsn_LaneDataAttributeList_delAndSetNull(&p->data); p->data = (Gitsn_LaneDataAttributeList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 4: p->dWidth =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->dElevation =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_NodeAttributeSetXY_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_NodeAttributeSetXY *p = (Gitsn_NodeAttributeSetXY *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->localNode;
	case 1: return p->disabled;
	case 2: return p->enabled;
	case 3: return p->data;
	case 4: return &p->dWidth;
	case 5: return &p->dElevation;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_NodeAttributeSetXY_membs[] =
{
	{ Dz1Text("localNode"), Dz1Text("Gitsn_NodeAttributeXYList"), 0 },
	{ Dz1Text("disabled"), Dz1Text("Gitsn_SegmentAttributeXYList"), 1 },
	{ Dz1Text("enabled"), Dz1Text("Gitsn_SegmentAttributeXYList"), 2 },
	{ Dz1Text("data"), Dz1Text("Gitsn_LaneDataAttributeList"), 3 },
	{ Dz1Text("dWidth"), Dz1Text("s64_t"), 4 },
	{ Dz1Text("dElevation"), Dz1Text("s64_t"), 5 },
	{ NULL, NULL, -1 }
};
// Gitsn_NodeAttributeSetXY
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeXY
static bool_t Gitsn_NodeXY_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_NodeXY *p = (Gitsn_NodeXY *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Gitsn_NodeOffsetPointXY_delAndSetNull(&p->delta); p->delta = (Gitsn_NodeOffsetPointXY *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: Gitsn_NodeAttributeSetXY_delAndSetNull(&p->attributes); p->attributes = (Gitsn_NodeAttributeSetXY *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_NodeXY_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_NodeXY *p = (Gitsn_NodeXY *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->delta;
	case 1: return p->attributes;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_NodeXY_membs[] =
{
	{ Dz1Text("delta"), Dz1Text("Gitsn_NodeOffsetPointXY"), 0 },
	{ Dz1Text("attributes"), Dz1Text("Gitsn_NodeAttributeSetXY"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_NodeXY
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeSetXY
static bool_t Gitsn_NodeSetXY_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_NodeSetXY *dst = (Gitsn_NodeSetXY *)dst_ptr;
	Gitsn_NodeXY *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_NodeXY *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_NodeSetXY_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_NodeSetXY *list = (Gitsn_NodeSetXY *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_NodeSetXY_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_NodeSetXY *list = (Gitsn_NodeSetXY *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_NodeSetXY
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ComputedLane_offsetXaxis
static bool_t Gitsn_ComputedLane_offsetXaxis_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ComputedLane_offsetXaxis *p = (Gitsn_ComputedLane_offsetXaxis *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_ComputedLane_offsetXaxisPresent_small: p->x.small = *(s64_t *)info->data; break;
	case Gitsn_ComputedLane_offsetXaxisPresent_large: p->x.large = *(s64_t *)info->data; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_ComputedLane_offsetXaxisPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_ComputedLane_offsetXaxis_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_ComputedLane_offsetXaxis *p = (Gitsn_ComputedLane_offsetXaxis *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_ComputedLane_offsetXaxisPresent_small: return &p->x.small;
		case Gitsn_ComputedLane_offsetXaxisPresent_large: return &p->x.large;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_ComputedLane_offsetXaxis_membs[] =
{
	{ Dz1Text("small"), Dz1Text("s64_t"), Gitsn_ComputedLane_offsetXaxisPresent_small },
	{ Dz1Text("large"), Dz1Text("s64_t"), Gitsn_ComputedLane_offsetXaxisPresent_large },
	{ NULL, NULL, -1 }
};
// Gitsn_ComputedLane_offsetXaxis
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ComputedLane_offsetYaxis
static bool_t Gitsn_ComputedLane_offsetYaxis_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ComputedLane_offsetYaxis *p = (Gitsn_ComputedLane_offsetYaxis *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_ComputedLane_offsetYaxisPresent_small: p->x.small = *(s64_t *)info->data; break;
	case Gitsn_ComputedLane_offsetYaxisPresent_large: p->x.large = *(s64_t *)info->data; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_ComputedLane_offsetYaxisPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_ComputedLane_offsetYaxis_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_ComputedLane_offsetYaxis *p = (Gitsn_ComputedLane_offsetYaxis *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_ComputedLane_offsetYaxisPresent_small: return &p->x.small;
		case Gitsn_ComputedLane_offsetYaxisPresent_large: return &p->x.large;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_ComputedLane_offsetYaxis_membs[] =
{
	{ Dz1Text("small"), Dz1Text("s64_t"), Gitsn_ComputedLane_offsetYaxisPresent_small },
	{ Dz1Text("large"), Dz1Text("s64_t"), Gitsn_ComputedLane_offsetYaxisPresent_large },
	{ NULL, NULL, -1 }
};
// Gitsn_ComputedLane_offsetYaxis
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ComputedLane
static bool_t Gitsn_ComputedLane_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ComputedLane *p = (Gitsn_ComputedLane *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->referenceLaneId =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: Gitsn_ComputedLane_offsetXaxis_delAndSetNull(&p->offsetXaxis); p->offsetXaxis = (Gitsn_ComputedLane_offsetXaxis *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: Gitsn_ComputedLane_offsetYaxis_delAndSetNull(&p->offsetYaxis); p->offsetYaxis = (Gitsn_ComputedLane_offsetYaxis *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: p->rotateXY =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->scaleXaxis =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->scaleYaxis =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_ComputedLane_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_ComputedLane *p = (Gitsn_ComputedLane *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->referenceLaneId;
	case 1: return p->offsetXaxis;
	case 2: return p->offsetYaxis;
	case 3: return &p->rotateXY;
	case 4: return &p->scaleXaxis;
	case 5: return &p->scaleYaxis;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_ComputedLane_membs[] =
{
	{ Dz1Text("referenceLaneId"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("offsetXaxis"), Dz1Text("Gitsn_ComputedLane_offsetXaxis"), 1 },
	{ Dz1Text("offsetYaxis"), Dz1Text("Gitsn_ComputedLane_offsetYaxis"), 2 },
	{ Dz1Text("rotateXY"), Dz1Text("s64_t"), 3 },
	{ Dz1Text("scaleXaxis"), Dz1Text("s64_t"), 4 },
	{ Dz1Text("scaleYaxis"), Dz1Text("s64_t"), 5 },
	{ NULL, NULL, -1 }
};
// Gitsn_ComputedLane
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeListXY
static bool_t Gitsn_NodeListXY_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_NodeListXY *p = (Gitsn_NodeListXY *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_NodeListXYPresent_nodes: Gitsn_NodeSetXY_delAndSetNull(&p->x.nodes); p->x.nodes =(Gitsn_NodeSetXY *)info->data; info->data = NULL; break;
	case Gitsn_NodeListXYPresent_computed: Gitsn_ComputedLane_delAndSetNull(&p->x.computed); p->x.computed =(Gitsn_ComputedLane *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_NodeListXYPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_NodeListXY_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_NodeListXY *p = (Gitsn_NodeListXY *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_NodeListXYPresent_nodes: return p->x.nodes;
		case Gitsn_NodeListXYPresent_computed: return p->x.computed;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_NodeListXY_membs[] =
{
	{ Dz1Text("nodes"), Dz1Text("Gitsn_NodeSetXY"), Gitsn_NodeListXYPresent_nodes },
	{ Dz1Text("computed"), Dz1Text("Gitsn_ComputedLane"), Gitsn_NodeListXYPresent_computed },
	{ NULL, NULL, -1 }
};
// Gitsn_NodeListXY
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ConnectingLane
static bool_t Gitsn_ConnectingLane_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ConnectingLane *p = (Gitsn_ConnectingLane *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->lane =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: u8_t_delAndSetNull(&p->maneuver); p->maneuver = (u8_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_ConnectingLane_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_ConnectingLane *p = (Gitsn_ConnectingLane *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->lane;
	case 1: return p->maneuver;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_ConnectingLane_membs[] =
{
	{ Dz1Text("lane"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("maneuver"), Dz1Text("u8_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_ConnectingLane
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Connection
static bool_t Gitsn_Connection_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Connection *p = (Gitsn_Connection *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Gitsn_ConnectingLane_delAndSetNull(&p->connecctingLnae); p->connecctingLnae = (Gitsn_ConnectingLane *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: Gitsn_IntersectionReferenceID_delAndSetNull(&p->remoteIntersection); p->remoteIntersection = (Gitsn_IntersectionReferenceID *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: p->signalGroup =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->userClass =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->connectionID =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Connection_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Connection *p = (Gitsn_Connection *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->connecctingLnae;
	case 1: return p->remoteIntersection;
	case 2: return &p->signalGroup;
	case 3: return &p->userClass;
	case 4: return &p->connectionID;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Connection_membs[] =
{
	{ Dz1Text("connecctingLnae"), Dz1Text("Gitsn_ConnectingLane"), 0 },
	{ Dz1Text("remoteIntersection"), Dz1Text("Gitsn_IntersectionReferenceID"), 1 },
	{ Dz1Text("signalGroup"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("userClass"), Dz1Text("s64_t"), 3 },
	{ Dz1Text("connectionID"), Dz1Text("s64_t"), 4 },
	{ NULL, NULL, -1 }
};
// Gitsn_Connection
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ConnectsToList
static bool_t Gitsn_ConnectsToList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ConnectsToList *dst = (Gitsn_ConnectsToList *)dst_ptr;
	Gitsn_Connection *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_Connection *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_ConnectsToList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_ConnectsToList *list = (Gitsn_ConnectsToList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_ConnectsToList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_ConnectsToList *list = (Gitsn_ConnectsToList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_ConnectsToList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_OverlayLaneList
static bool_t Gitsn_OverlayLaneList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_OverlayLaneList *dst = (Gitsn_OverlayLaneList *)dst_ptr;
	s64_t *node = NULL;
	if (dst == NULL || var == NULL || (node = (s64_t *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, *node)).code) ERR_OUT(errp);
	else
	{
		// var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_OverlayLaneList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_OverlayLaneList *list = (Gitsn_OverlayLaneList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_OverlayLaneList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_OverlayLaneList *list = (Gitsn_OverlayLaneList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_OverlayLaneList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_GenericLane
static bool_t Gitsn_GenericLane_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_GenericLane *p = (Gitsn_GenericLane *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->laneID =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->name); p->name = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: p->ingressApproach =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->egressApproach =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: Gitsn_LaneAttributes_delAndSetNull(&p->laneAttributes); p->laneAttributes = (Gitsn_LaneAttributes *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 5: u8_t_delAndSetNull(&p->maneuvers); p->maneuvers = (u8_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 6: Gitsn_NodeListXY_delAndSetNull(&p->nodeList); p->nodeList = (Gitsn_NodeListXY *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 7: Gitsn_ConnectsToList_delAndSetNull(&p->connectsTo); p->connectsTo = (Gitsn_ConnectsToList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 8: Gitsn_OverlayLaneList_delAndSetNull(&p->overlays); p->overlays = (Gitsn_OverlayLaneList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_GenericLane_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_GenericLane *p = (Gitsn_GenericLane *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->laneID;
	case 1: return p->name;
	case 2: return &p->ingressApproach;
	case 3: return &p->egressApproach;
	case 4: return p->laneAttributes;
	case 5: return p->maneuvers;
	case 6: return p->nodeList;
	case 7: return p->connectsTo;
	case 8: return p->overlays;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_GenericLane_membs[] =
{
	{ Dz1Text("laneID"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("name"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("ingressApproach"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("egressApproach"), Dz1Text("s64_t"), 3 },
	{ Dz1Text("laneAttributes"), Dz1Text("Gitsn_LaneAttributes"), 4 },
	{ Dz1Text("maneuvers"), Dz1Text("u8_t"), 5 },
	{ Dz1Text("nodeList"), Dz1Text("Gitsn_NodeListXY"), 6 },
	{ Dz1Text("connectsTo"), Dz1Text("Gitsn_ConnectsToList"), 7 },
	{ Dz1Text("overlays"), Dz1Text("Gitsn_OverlayLaneList"), 8 },
	{ NULL, NULL, -1 }
};
// Gitsn_GenericLane
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LaneList
static bool_t Gitsn_LaneList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_LaneList *dst = (Gitsn_LaneList *)dst_ptr;
	Gitsn_GenericLane *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_GenericLane *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_LaneList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_LaneList *list = (Gitsn_LaneList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_LaneList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_LaneList *list = (Gitsn_LaneList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_LaneList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SignalControlZone
static bool_t Gitsn_SignalControlZone_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_SignalControlZone *p = (Gitsn_SignalControlZone *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: u8_t_delAndSetNull(&p->zone); p->zone = (u8_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_SignalControlZone_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_SignalControlZone *p = (Gitsn_SignalControlZone *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->zone;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_SignalControlZone_membs[] =
{
	{ Dz1Text("zone"), Dz1Text("u8_t"), 0 },
	{ NULL, NULL, -1 }
};
// Gitsn_SignalControlZone
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PreemptPriorityList
static bool_t Gitsn_PreemptPriorityList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_PreemptPriorityList *dst = (Gitsn_PreemptPriorityList *)dst_ptr;
	Gitsn_SignalControlZone *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_SignalControlZone *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_PreemptPriorityList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_PreemptPriorityList *list = (Gitsn_PreemptPriorityList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_PreemptPriorityList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_PreemptPriorityList *list = (Gitsn_PreemptPriorityList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_PreemptPriorityList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IntersectionGeometry
static bool_t Gitsn_IntersectionGeometry_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_IntersectionGeometry *p = (Gitsn_IntersectionGeometry *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->name); p->name = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Gitsn_IntersectionReferenceID_delAndSetNull(&p->id); p->id = (Gitsn_IntersectionReferenceID *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: p->revision =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: Gitsn_Position3D_delAndSetNull(&p->refPoint); p->refPoint = (Gitsn_Position3D *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 4: p->laneWidth =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: Gitsn_SpeedLimitList_delAndSetNull(&p->speedLimits); p->speedLimits = (Gitsn_SpeedLimitList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 6: Gitsn_LaneList_delAndSetNull(&p->laneSet); p->laneSet = (Gitsn_LaneList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 7: Gitsn_PreemptPriorityList_delAndSetNull(&p->preemptPriorityData); p->preemptPriorityData = (Gitsn_PreemptPriorityList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_IntersectionGeometry_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_IntersectionGeometry *p = (Gitsn_IntersectionGeometry *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->name;
	case 1: return p->id;
	case 2: return &p->revision;
	case 3: return p->refPoint;
	case 4: return &p->laneWidth;
	case 5: return p->speedLimits;
	case 6: return p->laneSet;
	case 7: return p->preemptPriorityData;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_IntersectionGeometry_membs[] =
{
	{ Dz1Text("name"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("id"), Dz1Text("Gitsn_IntersectionReferenceID"), 1 },
	{ Dz1Text("revision"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("refPoint"), Dz1Text("Gitsn_Position3D"), 3 },
	{ Dz1Text("laneWidth"), Dz1Text("s64_t"), 4 },
	{ Dz1Text("speedLimits"), Dz1Text("Gitsn_SpeedLimitList"), 5 },
	{ Dz1Text("laneSet"), Dz1Text("Gitsn_LaneList"), 6 },
	{ Dz1Text("preemptPriorityData"), Dz1Text("Gitsn_PreemptPriorityList"), 7 },
	{ NULL, NULL, -1 }
};
// Gitsn_IntersectionGeometry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IntersectionGeometryList
static bool_t Gitsn_IntersectionGeometryList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_IntersectionGeometryList *dst = (Gitsn_IntersectionGeometryList *)dst_ptr;
	Gitsn_IntersectionGeometry *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_IntersectionGeometry *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_IntersectionGeometryList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_IntersectionGeometryList *list = (Gitsn_IntersectionGeometryList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_IntersectionGeometryList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_IntersectionGeometryList *list = (Gitsn_IntersectionGeometryList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_IntersectionGeometryList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RoadSegmentReferenceID
static bool_t Gitsn_RoadSegmentReferenceID_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_RoadSegmentReferenceID *p = (Gitsn_RoadSegmentReferenceID *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->region =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->id =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_RoadSegmentReferenceID_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_RoadSegmentReferenceID *p = (Gitsn_RoadSegmentReferenceID *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->region;
	case 1: return &p->id;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_RoadSegmentReferenceID_membs[] =
{
	{ Dz1Text("region"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("id"), Dz1Text("s64_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_RoadSegmentReferenceID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RoadLaneSetList
static bool_t Gitsn_RoadLaneSetList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_RoadLaneSetList *dst = (Gitsn_RoadLaneSetList *)dst_ptr;
	Gitsn_GenericLane *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_GenericLane *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_RoadLaneSetList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_RoadLaneSetList *list = (Gitsn_RoadLaneSetList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_RoadLaneSetList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_RoadLaneSetList *list = (Gitsn_RoadLaneSetList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_RoadLaneSetList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RoadSegment
static bool_t Gitsn_RoadSegment_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_RoadSegment *p = (Gitsn_RoadSegment *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->name); p->name = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Gitsn_RoadSegmentReferenceID_delAndSetNull(&p->id); p->id = (Gitsn_RoadSegmentReferenceID *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: p->revision =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: Gitsn_Position3D_delAndSetNull(&p->refPoint); p->refPoint = (Gitsn_Position3D *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 4: p->laneWidth =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: Gitsn_SpeedLimitList_delAndSetNull(&p->speedLimits); p->speedLimits = (Gitsn_SpeedLimitList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 6: Gitsn_RoadLaneSetList_delAndSetNull(&p->roadLaneSet); p->roadLaneSet = (Gitsn_RoadLaneSetList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_RoadSegment_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_RoadSegment *p = (Gitsn_RoadSegment *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->name;
	case 1: return p->id;
	case 2: return &p->revision;
	case 3: return p->refPoint;
	case 4: return &p->laneWidth;
	case 5: return p->speedLimits;
	case 6: return p->roadLaneSet;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_RoadSegment_membs[] =
{
	{ Dz1Text("name"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("id"), Dz1Text("Gitsn_RoadSegmentReferenceID"), 1 },
	{ Dz1Text("revision"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("refPoint"), Dz1Text("Gitsn_Position3D"), 3 },
	{ Dz1Text("laneWidth"), Dz1Text("s64_t"), 4 },
	{ Dz1Text("speedLimits"), Dz1Text("Gitsn_SpeedLimitList"), 5 },
	{ Dz1Text("roadLaneSet"), Dz1Text("Gitsn_RoadLaneSetList"), 6 },
	{ NULL, NULL, -1 }
};
// Gitsn_RoadSegment
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RoadSegmentList
static bool_t Gitsn_RoadSegmentList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_RoadSegmentList *dst = (Gitsn_RoadSegmentList *)dst_ptr;
	Gitsn_RoadSegment *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_RoadSegment *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_RoadSegmentList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_RoadSegmentList *list = (Gitsn_RoadSegmentList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_RoadSegmentList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_RoadSegmentList *list = (Gitsn_RoadSegmentList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_RoadSegmentList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DataParameters
static bool_t Gitsn_DataParameters_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_DataParameters *p = (Gitsn_DataParameters *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->processMethod); p->processMethod = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->processAgency); p->processAgency = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->lastCheckedDate); p->lastCheckedDate = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 3: Dz1Str_delAndSetNull(&p->geoidUsed); p->geoidUsed = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_DataParameters_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_DataParameters *p = (Gitsn_DataParameters *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->processMethod;
	case 1: return p->processAgency;
	case 2: return p->lastCheckedDate;
	case 3: return p->geoidUsed;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_DataParameters_membs[] =
{
	{ Dz1Text("processMethod"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("processAgency"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("lastCheckedDate"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("geoidUsed"), Dz1Text("Dz1Str"), 3 },
	{ NULL, NULL, -1 }
};
// Gitsn_DataParameters
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RestrictionAppliesTo
static bool_t Gitsn_RestrictionAppliesTo_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_RestrictionAppliesTo v = Gitsn_RestrictionAppliesTo_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_RestrictionAppliesTo)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_RestrictionAppliesToFromStr(tok->v)) == Gitsn_RestrictionAppliesTo_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_RestrictionAppliesTo_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_RestrictionAppliesTo_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_RestrictionAppliesTo v = *(Gitsn_RestrictionAppliesTo *)obj;
		Dz1Str str_v = Gitsn_RestrictionAppliesToStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_RestrictionAppliesTo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RestrictionUserType
static bool_t Gitsn_RestrictionUserType_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_RestrictionUserType *p = (Gitsn_RestrictionUserType *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_RestrictionUserTypePresent_basicType: p->x.basicType = *(Gitsn_RestrictionAppliesTo *)info->data; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_RestrictionUserTypePresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_RestrictionUserType_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_RestrictionUserType *p = (Gitsn_RestrictionUserType *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_RestrictionUserTypePresent_basicType: return &p->x.basicType;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_RestrictionUserType_membs[] =
{
	{ Dz1Text("basicType"), Dz1Text("Gitsn_RestrictionAppliesTo"), Gitsn_RestrictionUserTypePresent_basicType },
	{ NULL, NULL, -1 }
};
// Gitsn_RestrictionUserType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RestrictionUserTypeList
static bool_t Gitsn_RestrictionUserTypeList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_RestrictionUserTypeList *dst = (Gitsn_RestrictionUserTypeList *)dst_ptr;
	Gitsn_RestrictionUserType *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_RestrictionUserType *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_RestrictionUserTypeList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_RestrictionUserTypeList *list = (Gitsn_RestrictionUserTypeList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_RestrictionUserTypeList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_RestrictionUserTypeList *list = (Gitsn_RestrictionUserTypeList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_RestrictionUserTypeList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RestrictionClassAssignment
static bool_t Gitsn_RestrictionClassAssignment_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_RestrictionClassAssignment *p = (Gitsn_RestrictionClassAssignment *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->id =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: Gitsn_RestrictionUserTypeList_delAndSetNull(&p->users); p->users = (Gitsn_RestrictionUserTypeList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_RestrictionClassAssignment_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_RestrictionClassAssignment *p = (Gitsn_RestrictionClassAssignment *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->id;
	case 1: return p->users;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_RestrictionClassAssignment_membs[] =
{
	{ Dz1Text("id"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("users"), Dz1Text("Gitsn_RestrictionUserTypeList"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_RestrictionClassAssignment
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RestrictionClassList
static bool_t Gitsn_RestrictionClassList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_RestrictionClassList *dst = (Gitsn_RestrictionClassList *)dst_ptr;
	Gitsn_RestrictionClassAssignment *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_RestrictionClassAssignment *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_RestrictionClassList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_RestrictionClassList *list = (Gitsn_RestrictionClassList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_RestrictionClassList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_RestrictionClassList *list = (Gitsn_RestrictionClassList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_RestrictionClassList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MapData
static bool_t Gitsn_MapData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_MapData *p = (Gitsn_MapData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->timeStamp =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->msgIssueRevision =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->layerType =  *(Gitsn_LayerType *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->layerID =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: Gitsn_IntersectionGeometryList_delAndSetNull(&p->intersections); p->intersections = (Gitsn_IntersectionGeometryList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 5: Gitsn_RoadSegmentList_delAndSetNull(&p->roadSegments); p->roadSegments = (Gitsn_RoadSegmentList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 6: Gitsn_DataParameters_delAndSetNull(&p->dataParameters); p->dataParameters = (Gitsn_DataParameters *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 7: Gitsn_RestrictionClassList_delAndSetNull(&p->restrictionList); p->restrictionList = (Gitsn_RestrictionClassList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_MapData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_MapData *p = (Gitsn_MapData *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->timeStamp;
	case 1: return &p->msgIssueRevision;
	case 2: return &p->layerType;
	case 3: return &p->layerID;
	case 4: return p->intersections;
	case 5: return p->roadSegments;
	case 6: return p->dataParameters;
	case 7: return p->restrictionList;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_MapData_membs[] =
{
	{ Dz1Text("timeStamp"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("msgIssueRevision"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("layerType"), Dz1Text("Gitsn_LayerType"), 2 },
	{ Dz1Text("layerID"), Dz1Text("s64_t"), 3 },
	{ Dz1Text("intersections"), Dz1Text("Gitsn_IntersectionGeometryList"), 4 },
	{ Dz1Text("roadSegments"), Dz1Text("Gitsn_RoadSegmentList"), 5 },
	{ Dz1Text("dataParameters"), Dz1Text("Gitsn_DataParameters"), 6 },
	{ Dz1Text("restrictionList"), Dz1Text("Gitsn_RestrictionClassList"), 7 },
	{ NULL, NULL, -1 }
};
// Gitsn_MapData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_EnabledLaneList
static bool_t Gitsn_EnabledLaneList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_EnabledLaneList *dst = (Gitsn_EnabledLaneList *)dst_ptr;
	s64_t *node = NULL;
	if (dst == NULL || var == NULL || (node = (s64_t *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, *node)).code) ERR_OUT(errp);
	else
	{
		// var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_EnabledLaneList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_EnabledLaneList *list = (Gitsn_EnabledLaneList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_EnabledLaneList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_EnabledLaneList *list = (Gitsn_EnabledLaneList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_EnabledLaneList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MovementPhaseState
static bool_t Gitsn_MovementPhaseState_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_MovementPhaseState v = Gitsn_MovementPhaseState_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_MovementPhaseState)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_MovementPhaseStateFromStr(tok->v)) == Gitsn_MovementPhaseState_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_MovementPhaseState_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_MovementPhaseState_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_MovementPhaseState v = *(Gitsn_MovementPhaseState *)obj;
		Dz1Str str_v = Gitsn_MovementPhaseStateStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_MovementPhaseState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TimeChangeDetails
static bool_t Gitsn_TimeChangeDetails_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_TimeChangeDetails *p = (Gitsn_TimeChangeDetails *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->startTime =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->minEndTime =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->maxEndTime =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->likelyTime =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->confidence =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->nextTime =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_TimeChangeDetails_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_TimeChangeDetails *p = (Gitsn_TimeChangeDetails *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->startTime;
	case 1: return &p->minEndTime;
	case 2: return &p->maxEndTime;
	case 3: return &p->likelyTime;
	case 4: return &p->confidence;
	case 5: return &p->nextTime;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_TimeChangeDetails_membs[] =
{
	{ Dz1Text("startTime"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("minEndTime"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("maxEndTime"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("likelyTime"), Dz1Text("s64_t"), 3 },
	{ Dz1Text("confidence"), Dz1Text("s64_t"), 4 },
	{ Dz1Text("nextTime"), Dz1Text("s64_t"), 5 },
	{ NULL, NULL, -1 }
};
// Gitsn_TimeChangeDetails
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AdvisorySpeedType
static bool_t Gitsn_AdvisorySpeedType_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_AdvisorySpeedType v = Gitsn_AdvisorySpeedType_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_AdvisorySpeedType)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_AdvisorySpeedTypeFromStr(tok->v)) == Gitsn_AdvisorySpeedType_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_AdvisorySpeedType_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_AdvisorySpeedType_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_AdvisorySpeedType v = *(Gitsn_AdvisorySpeedType *)obj;
		Dz1Str str_v = Gitsn_AdvisorySpeedTypeStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_AdvisorySpeedType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SpeedConfidence
static bool_t Gitsn_SpeedConfidence_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_SpeedConfidence v = Gitsn_SpeedConfidence_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_SpeedConfidence)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_SpeedConfidenceFromStr(tok->v)) == Gitsn_SpeedConfidence_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_SpeedConfidence_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_SpeedConfidence_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_SpeedConfidence v = *(Gitsn_SpeedConfidence *)obj;
		Dz1Str str_v = Gitsn_SpeedConfidenceStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_SpeedConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AdvisorySpeed
static bool_t Gitsn_AdvisorySpeed_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_AdvisorySpeed *p = (Gitsn_AdvisorySpeed *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->type =  *(Gitsn_AdvisorySpeedType *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->speed =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->confidence =  *(Gitsn_SpeedConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->distance =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->class =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_AdvisorySpeed_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_AdvisorySpeed *p = (Gitsn_AdvisorySpeed *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->type;
	case 1: return &p->speed;
	case 2: return &p->confidence;
	case 3: return &p->distance;
	case 4: return &p->class;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_AdvisorySpeed_membs[] =
{
	{ Dz1Text("type"), Dz1Text("Gitsn_AdvisorySpeedType"), 0 },
	{ Dz1Text("speed"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("confidence"), Dz1Text("Gitsn_SpeedConfidence"), 2 },
	{ Dz1Text("distance"), Dz1Text("s64_t"), 3 },
	{ Dz1Text("class"), Dz1Text("s64_t"), 4 },
	{ NULL, NULL, -1 }
};
// Gitsn_AdvisorySpeed
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AdvisorySpeedList
static bool_t Gitsn_AdvisorySpeedList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_AdvisorySpeedList *dst = (Gitsn_AdvisorySpeedList *)dst_ptr;
	Gitsn_AdvisorySpeed *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_AdvisorySpeed *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_AdvisorySpeedList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_AdvisorySpeedList *list = (Gitsn_AdvisorySpeedList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_AdvisorySpeedList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_AdvisorySpeedList *list = (Gitsn_AdvisorySpeedList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_AdvisorySpeedList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MovementEvent
static bool_t Gitsn_MovementEvent_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_MovementEvent *p = (Gitsn_MovementEvent *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->eventState =  *(Gitsn_MovementPhaseState *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: Gitsn_TimeChangeDetails_delAndSetNull(&p->timing); p->timing = (Gitsn_TimeChangeDetails *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: Gitsn_AdvisorySpeedList_delAndSetNull(&p->speeds); p->speeds = (Gitsn_AdvisorySpeedList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_MovementEvent_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_MovementEvent *p = (Gitsn_MovementEvent *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->eventState;
	case 1: return p->timing;
	case 2: return p->speeds;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_MovementEvent_membs[] =
{
	{ Dz1Text("eventState"), Dz1Text("Gitsn_MovementPhaseState"), 0 },
	{ Dz1Text("timing"), Dz1Text("Gitsn_TimeChangeDetails"), 1 },
	{ Dz1Text("speeds"), Dz1Text("Gitsn_AdvisorySpeedList"), 2 },
	{ NULL, NULL, -1 }
};
// Gitsn_MovementEvent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MovementEventList
static bool_t Gitsn_MovementEventList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_MovementEventList *dst = (Gitsn_MovementEventList *)dst_ptr;
	Gitsn_MovementEvent *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_MovementEvent *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_MovementEventList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_MovementEventList *list = (Gitsn_MovementEventList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_MovementEventList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_MovementEventList *list = (Gitsn_MovementEventList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_MovementEventList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ConnectionManeuverAssist
static bool_t Gitsn_ConnectionManeuverAssist_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ConnectionManeuverAssist *p = (Gitsn_ConnectionManeuverAssist *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->connectionID =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->queueLength =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->availableStorageLength =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->waitOnStop =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->pedBicycleDetect =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_ConnectionManeuverAssist_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_ConnectionManeuverAssist *p = (Gitsn_ConnectionManeuverAssist *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->connectionID;
	case 1: return &p->queueLength;
	case 2: return &p->availableStorageLength;
	case 3: return &p->waitOnStop;
	case 4: return &p->pedBicycleDetect;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_ConnectionManeuverAssist_membs[] =
{
	{ Dz1Text("connectionID"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("queueLength"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("availableStorageLength"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("waitOnStop"), Dz1Text("bool_t"), 3 },
	{ Dz1Text("pedBicycleDetect"), Dz1Text("bool_t"), 4 },
	{ NULL, NULL, -1 }
};
// Gitsn_ConnectionManeuverAssist
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ManeuverAssistList
static bool_t Gitsn_ManeuverAssistList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ManeuverAssistList *dst = (Gitsn_ManeuverAssistList *)dst_ptr;
	Gitsn_ConnectionManeuverAssist *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_ConnectionManeuverAssist *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_ManeuverAssistList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_ManeuverAssistList *list = (Gitsn_ManeuverAssistList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_ManeuverAssistList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_ManeuverAssistList *list = (Gitsn_ManeuverAssistList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_ManeuverAssistList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MovementState
static bool_t Gitsn_MovementState_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_MovementState *p = (Gitsn_MovementState *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->movementName); p->movementName = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->signalGroup =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: Gitsn_MovementEventList_delAndSetNull(&p->state_time_speed); p->state_time_speed = (Gitsn_MovementEventList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: Gitsn_ManeuverAssistList_delAndSetNull(&p->maneuverAssistList); p->maneuverAssistList = (Gitsn_ManeuverAssistList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_MovementState_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_MovementState *p = (Gitsn_MovementState *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->movementName;
	case 1: return &p->signalGroup;
	case 2: return p->state_time_speed;
	case 3: return p->maneuverAssistList;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_MovementState_membs[] =
{
	{ Dz1Text("movementName"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("signalGroup"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("state_time_speed"), Dz1Text("Gitsn_MovementEventList"), 2 },
	{ Dz1Text("maneuverAssistList"), Dz1Text("Gitsn_ManeuverAssistList"), 3 },
	{ NULL, NULL, -1 }
};
// Gitsn_MovementState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MovementList
static bool_t Gitsn_MovementList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_MovementList *dst = (Gitsn_MovementList *)dst_ptr;
	Gitsn_MovementState *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_MovementState *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_MovementList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_MovementList *list = (Gitsn_MovementList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_MovementList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_MovementList *list = (Gitsn_MovementList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_MovementList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IntersectionState
static bool_t Gitsn_IntersectionState_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_IntersectionState *p = (Gitsn_IntersectionState *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->name); p->name = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Gitsn_IntersectionReferenceID_delAndSetNull(&p->id); p->id = (Gitsn_IntersectionReferenceID *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: p->revision =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: u8_t_delAndSetNull(&p->status); p->status = (u8_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 4: p->moy =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->timeStamp =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: Gitsn_EnabledLaneList_delAndSetNull(&p->enabledLanes); p->enabledLanes = (Gitsn_EnabledLaneList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 7: Gitsn_MovementList_delAndSetNull(&p->states); p->states = (Gitsn_MovementList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 8: Gitsn_ManeuverAssistList_delAndSetNull(&p->maneuverAssistList); p->maneuverAssistList = (Gitsn_ManeuverAssistList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_IntersectionState_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_IntersectionState *p = (Gitsn_IntersectionState *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->name;
	case 1: return p->id;
	case 2: return &p->revision;
	case 3: return p->status;
	case 4: return &p->moy;
	case 5: return &p->timeStamp;
	case 6: return p->enabledLanes;
	case 7: return p->states;
	case 8: return p->maneuverAssistList;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_IntersectionState_membs[] =
{
	{ Dz1Text("name"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("id"), Dz1Text("Gitsn_IntersectionReferenceID"), 1 },
	{ Dz1Text("revision"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("status"), Dz1Text("u8_t"), 3 },
	{ Dz1Text("moy"), Dz1Text("s64_t"), 4 },
	{ Dz1Text("timeStamp"), Dz1Text("s64_t"), 5 },
	{ Dz1Text("enabledLanes"), Dz1Text("Gitsn_EnabledLaneList"), 6 },
	{ Dz1Text("states"), Dz1Text("Gitsn_MovementList"), 7 },
	{ Dz1Text("maneuverAssistList"), Dz1Text("Gitsn_ManeuverAssistList"), 8 },
	{ NULL, NULL, -1 }
};
// Gitsn_IntersectionState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IntersectionStateList
static bool_t Gitsn_IntersectionStateList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_IntersectionStateList *dst = (Gitsn_IntersectionStateList *)dst_ptr;
	Gitsn_IntersectionState *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_IntersectionState *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_IntersectionStateList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_IntersectionStateList *list = (Gitsn_IntersectionStateList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_IntersectionStateList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_IntersectionStateList *list = (Gitsn_IntersectionStateList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_IntersectionStateList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SPAT
static bool_t Gitsn_SPAT_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_SPAT *p = (Gitsn_SPAT *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->timeStamp =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->name); p->name = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: Gitsn_IntersectionStateList_delAndSetNull(&p->intersections); p->intersections = (Gitsn_IntersectionStateList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_SPAT_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_SPAT *p = (Gitsn_SPAT *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->timeStamp;
	case 1: return p->name;
	case 2: return p->intersections;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_SPAT_membs[] =
{
	{ Dz1Text("timeStamp"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("name"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("intersections"), Dz1Text("Gitsn_IntersectionStateList"), 2 },
	{ NULL, NULL, -1 }
};
// Gitsn_SPAT
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleID
static bool_t Gitsn_VehicleID_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_VehicleID *p = (Gitsn_VehicleID *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_VehicleIDPresent_entityID: Dz1Str_delAndSetNull(&p->x.entityID); p->x.entityID =(Dz1Str)info->data; info->data = NULL; break;
	case Gitsn_VehicleIDPresent_stationID: p->x.stationID = *(s64_t *)info->data; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_VehicleIDPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_VehicleID_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_VehicleID *p = (Gitsn_VehicleID *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_VehicleIDPresent_entityID: return p->x.entityID;
		case Gitsn_VehicleIDPresent_stationID: return &p->x.stationID;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_VehicleID_membs[] =
{
	{ Dz1Text("entityID"), Dz1Text("Dz1Str"), Gitsn_VehicleIDPresent_entityID },
	{ Dz1Text("stationID"), Dz1Text("s64_t"), Gitsn_VehicleIDPresent_stationID },
	{ NULL, NULL, -1 }
};
// Gitsn_VehicleID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleType
static bool_t Gitsn_VehicleType_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_VehicleType v = Gitsn_VehicleType_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_VehicleType)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_VehicleTypeFromStr(tok->v)) == Gitsn_VehicleType_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_VehicleType_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_VehicleType_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_VehicleType v = *(Gitsn_VehicleType *)obj;
		Dz1Str str_v = Gitsn_VehicleTypeStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_VehicleType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleGroupAffected
static bool_t Gitsn_VehicleGroupAffected_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_VehicleGroupAffected v = Gitsn_VehicleGroupAffected_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_VehicleGroupAffected)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_VehicleGroupAffectedFromStr(tok->v)) == Gitsn_VehicleGroupAffected_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_VehicleGroupAffected_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_VehicleGroupAffected_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_VehicleGroupAffected v = *(Gitsn_VehicleGroupAffected *)obj;
		Dz1Str str_v = Gitsn_VehicleGroupAffectedStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_VehicleGroupAffected
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ResponderGroupAffected
static bool_t Gitsn_ResponderGroupAffected_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ResponderGroupAffected v = Gitsn_ResponderGroupAffected_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_ResponderGroupAffected)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_ResponderGroupAffectedFromStr(tok->v)) == Gitsn_ResponderGroupAffected_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_ResponderGroupAffected_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_ResponderGroupAffected_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_ResponderGroupAffected v = *(Gitsn_ResponderGroupAffected *)obj;
		Dz1Str str_v = Gitsn_ResponderGroupAffectedStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_ResponderGroupAffected
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_IncidentResponseEquipment
static bool_t Gitsn_IncidentResponseEquipment_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_IncidentResponseEquipment v = Gitsn_IncidentResponseEquipment_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_IncidentResponseEquipment)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_IncidentResponseEquipmentFromStr(tok->v)) == Gitsn_IncidentResponseEquipment_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_IncidentResponseEquipment_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_IncidentResponseEquipment_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_IncidentResponseEquipment v = *(Gitsn_IncidentResponseEquipment *)obj;
		Dz1Str str_v = Gitsn_IncidentResponseEquipmentStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_IncidentResponseEquipment
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleIdent_vehicleClass
static bool_t Gitsn_VehicleIdent_vehicleClass_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_VehicleIdent_vehicleClass *p = (Gitsn_VehicleIdent_vehicleClass *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_VehicleIdent_vehicleClassPresent_vGroup: p->x.vGroup = *(Gitsn_VehicleGroupAffected *)info->data; break;
	case Gitsn_VehicleIdent_vehicleClassPresent_rGroup: p->x.rGroup = *(Gitsn_ResponderGroupAffected *)info->data; break;
	case Gitsn_VehicleIdent_vehicleClassPresent_rEquip: p->x.rEquip = *(Gitsn_IncidentResponseEquipment *)info->data; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_VehicleIdent_vehicleClassPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_VehicleIdent_vehicleClass_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_VehicleIdent_vehicleClass *p = (Gitsn_VehicleIdent_vehicleClass *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_VehicleIdent_vehicleClassPresent_vGroup: return &p->x.vGroup;
		case Gitsn_VehicleIdent_vehicleClassPresent_rGroup: return &p->x.rGroup;
		case Gitsn_VehicleIdent_vehicleClassPresent_rEquip: return &p->x.rEquip;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_VehicleIdent_vehicleClass_membs[] =
{
	{ Dz1Text("vGroup"), Dz1Text("Gitsn_VehicleGroupAffected"), Gitsn_VehicleIdent_vehicleClassPresent_vGroup },
	{ Dz1Text("rGroup"), Dz1Text("Gitsn_ResponderGroupAffected"), Gitsn_VehicleIdent_vehicleClassPresent_rGroup },
	{ Dz1Text("rEquip"), Dz1Text("Gitsn_IncidentResponseEquipment"), Gitsn_VehicleIdent_vehicleClassPresent_rEquip },
	{ NULL, NULL, -1 }
};
// Gitsn_VehicleIdent_vehicleClass
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleIdent
static bool_t Gitsn_VehicleIdent_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_VehicleIdent *p = (Gitsn_VehicleIdent *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->name); p->name = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->vin); p->vin = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->ownerCode); p->ownerCode = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 3: Gitsn_VehicleID_delAndSetNull(&p->id); p->id = (Gitsn_VehicleID *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 4: p->vehicleType =  *(Gitsn_VehicleType *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: Gitsn_VehicleIdent_vehicleClass_delAndSetNull(&p->vehicleClass); p->vehicleClass = (Gitsn_VehicleIdent_vehicleClass *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_VehicleIdent_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_VehicleIdent *p = (Gitsn_VehicleIdent *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->name;
	case 1: return p->vin;
	case 2: return p->ownerCode;
	case 3: return p->id;
	case 4: return &p->vehicleType;
	case 5: return p->vehicleClass;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_VehicleIdent_membs[] =
{
	{ Dz1Text("name"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("vin"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("ownerCode"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("id"), Dz1Text("Gitsn_VehicleID"), 3 },
	{ Dz1Text("vehicleType"), Dz1Text("Gitsn_VehicleType"), 4 },
	{ Dz1Text("vehicleClass"), Dz1Text("Gitsn_VehicleIdent_vehicleClass"), 5 },
	{ NULL, NULL, -1 }
};
// Gitsn_VehicleIdent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DDateTime
static bool_t Gitsn_DDateTime_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_DDateTime *p = (Gitsn_DDateTime *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->year =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->month =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->day =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->hour =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->minute =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->second =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->offset =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_DDateTime_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_DDateTime *p = (Gitsn_DDateTime *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->year;
	case 1: return &p->month;
	case 2: return &p->day;
	case 3: return &p->hour;
	case 4: return &p->minute;
	case 5: return &p->second;
	case 6: return &p->offset;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_DDateTime_membs[] =
{
	{ Dz1Text("year"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("month"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("day"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("hour"), Dz1Text("s64_t"), 3 },
	{ Dz1Text("minute"), Dz1Text("s64_t"), 4 },
	{ Dz1Text("second"), Dz1Text("s64_t"), 5 },
	{ Dz1Text("offset"), Dz1Text("s64_t"), 6 },
	{ NULL, NULL, -1 }
};
// Gitsn_DDateTime
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TransmissionAndSpeed
static bool_t Gitsn_TransmissionAndSpeed_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_TransmissionAndSpeed *p = (Gitsn_TransmissionAndSpeed *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->transmission =  *(Gitsn_TransmissionState *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->speed =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_TransmissionAndSpeed_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_TransmissionAndSpeed *p = (Gitsn_TransmissionAndSpeed *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->transmission;
	case 1: return &p->speed;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_TransmissionAndSpeed_membs[] =
{
	{ Dz1Text("transmission"), Dz1Text("Gitsn_TransmissionState"), 0 },
	{ Dz1Text("speed"), Dz1Text("s64_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_TransmissionAndSpeed
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TimeConfidence
static bool_t Gitsn_TimeConfidence_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_TimeConfidence v = Gitsn_TimeConfidence_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_TimeConfidence)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_TimeConfidenceFromStr(tok->v)) == Gitsn_TimeConfidence_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_TimeConfidence_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_TimeConfidence_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_TimeConfidence v = *(Gitsn_TimeConfidence *)obj;
		Dz1Str str_v = Gitsn_TimeConfidenceStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_TimeConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PositionConfidence
static bool_t Gitsn_PositionConfidence_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_PositionConfidence v = Gitsn_PositionConfidence_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_PositionConfidence)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_PositionConfidenceFromStr(tok->v)) == Gitsn_PositionConfidence_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_PositionConfidence_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_PositionConfidence_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_PositionConfidence v = *(Gitsn_PositionConfidence *)obj;
		Dz1Str str_v = Gitsn_PositionConfidenceStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_PositionConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ElevationConfidence
static bool_t Gitsn_ElevationConfidence_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ElevationConfidence v = Gitsn_ElevationConfidence_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_ElevationConfidence)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_ElevationConfidenceFromStr(tok->v)) == Gitsn_ElevationConfidence_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_ElevationConfidence_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_ElevationConfidence_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_ElevationConfidence v = *(Gitsn_ElevationConfidence *)obj;
		Dz1Str str_v = Gitsn_ElevationConfidenceStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_ElevationConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PositionConfidenceSet
static bool_t Gitsn_PositionConfidenceSet_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_PositionConfidenceSet *p = (Gitsn_PositionConfidenceSet *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->pos =  *(Gitsn_PositionConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->elevation =  *(Gitsn_ElevationConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_PositionConfidenceSet_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_PositionConfidenceSet *p = (Gitsn_PositionConfidenceSet *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->pos;
	case 1: return &p->elevation;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_PositionConfidenceSet_membs[] =
{
	{ Dz1Text("pos"), Dz1Text("Gitsn_PositionConfidence"), 0 },
	{ Dz1Text("elevation"), Dz1Text("Gitsn_ElevationConfidence"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_PositionConfidenceSet
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_HeadingConfidence
static bool_t Gitsn_HeadingConfidence_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_HeadingConfidence v = Gitsn_HeadingConfidence_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_HeadingConfidence)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_HeadingConfidenceFromStr(tok->v)) == Gitsn_HeadingConfidence_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_HeadingConfidence_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_HeadingConfidence_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_HeadingConfidence v = *(Gitsn_HeadingConfidence *)obj;
		Dz1Str str_v = Gitsn_HeadingConfidenceStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_HeadingConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ThrottleConfidence
static bool_t Gitsn_ThrottleConfidence_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ThrottleConfidence v = Gitsn_ThrottleConfidence_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_ThrottleConfidence)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_ThrottleConfidenceFromStr(tok->v)) == Gitsn_ThrottleConfidence_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_ThrottleConfidence_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_ThrottleConfidence_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_ThrottleConfidence v = *(Gitsn_ThrottleConfidence *)obj;
		Dz1Str str_v = Gitsn_ThrottleConfidenceStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_ThrottleConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SpeedandHeadingandThrottleConfidence
static bool_t Gitsn_SpeedandHeadingandThrottleConfidence_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_SpeedandHeadingandThrottleConfidence *p = (Gitsn_SpeedandHeadingandThrottleConfidence *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->heading =  *(Gitsn_HeadingConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->speed =  *(Gitsn_SpeedConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->throttle =  *(Gitsn_ThrottleConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_SpeedandHeadingandThrottleConfidence_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_SpeedandHeadingandThrottleConfidence *p = (Gitsn_SpeedandHeadingandThrottleConfidence *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->heading;
	case 1: return &p->speed;
	case 2: return &p->throttle;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_SpeedandHeadingandThrottleConfidence_membs[] =
{
	{ Dz1Text("heading"), Dz1Text("Gitsn_HeadingConfidence"), 0 },
	{ Dz1Text("speed"), Dz1Text("Gitsn_SpeedConfidence"), 1 },
	{ Dz1Text("throttle"), Dz1Text("Gitsn_ThrottleConfidence"), 2 },
	{ NULL, NULL, -1 }
};
// Gitsn_SpeedandHeadingandThrottleConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_FullPositionVector
static bool_t Gitsn_FullPositionVector_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_FullPositionVector *p = (Gitsn_FullPositionVector *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Gitsn_DDateTime_delAndSetNull(&p->utcTime); p->utcTime = (Gitsn_DDateTime *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: p->lon =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->lat =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->elevation =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->heading =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: Gitsn_TransmissionAndSpeed_delAndSetNull(&p->speed); p->speed = (Gitsn_TransmissionAndSpeed *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 6: Gitsn_PositionalAccuracy_delAndSetNull(&p->posAccuracy); p->posAccuracy = (Gitsn_PositionalAccuracy *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 7: p->timeConfidence =  *(Gitsn_TimeConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: Gitsn_PositionConfidenceSet_delAndSetNull(&p->posConfidence); p->posConfidence = (Gitsn_PositionConfidenceSet *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 9: Gitsn_SpeedandHeadingandThrottleConfidence_delAndSetNull(&p->speedConfidence); p->speedConfidence = (Gitsn_SpeedandHeadingandThrottleConfidence *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_FullPositionVector_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_FullPositionVector *p = (Gitsn_FullPositionVector *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->utcTime;
	case 1: return &p->lon;
	case 2: return &p->lat;
	case 3: return &p->elevation;
	case 4: return &p->heading;
	case 5: return p->speed;
	case 6: return p->posAccuracy;
	case 7: return &p->timeConfidence;
	case 8: return p->posConfidence;
	case 9: return p->speedConfidence;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_FullPositionVector_membs[] =
{
	{ Dz1Text("utcTime"), Dz1Text("Gitsn_DDateTime"), 0 },
	{ Dz1Text("lon"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("lat"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("elevation"), Dz1Text("s64_t"), 3 },
	{ Dz1Text("heading"), Dz1Text("s64_t"), 4 },
	{ Dz1Text("speed"), Dz1Text("Gitsn_TransmissionAndSpeed"), 5 },
	{ Dz1Text("posAccuracy"), Dz1Text("Gitsn_PositionalAccuracy"), 6 },
	{ Dz1Text("timeConfidence"), Dz1Text("Gitsn_TimeConfidence"), 7 },
	{ Dz1Text("posConfidence"), Dz1Text("Gitsn_PositionConfidenceSet"), 8 },
	{ Dz1Text("speedConfidence"), Dz1Text("Gitsn_SpeedandHeadingandThrottleConfidence"), 9 },
	{ NULL, NULL, -1 }
};
// Gitsn_FullPositionVector
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_BasicVehicleRole
static bool_t Gitsn_BasicVehicleRole_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_BasicVehicleRole v = Gitsn_BasicVehicleRole_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_BasicVehicleRole)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_BasicVehicleRoleFromStr(tok->v)) == Gitsn_BasicVehicleRole_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_BasicVehicleRole_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_BasicVehicleRole_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_BasicVehicleRole v = *(Gitsn_BasicVehicleRole *)obj;
		Dz1Str str_v = Gitsn_BasicVehicleRoleStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_BasicVehicleRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleClassification
static bool_t Gitsn_VehicleClassification_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_VehicleClassification *p = (Gitsn_VehicleClassification *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->keyType =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->role =  *(Gitsn_BasicVehicleRole *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->iso3883 =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->hpmsType =  *(Gitsn_VehicleType *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->vehicleType =  *(Gitsn_VehicleGroupAffected *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->responseEquip =  *(Gitsn_IncidentResponseEquipment *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->responderType =  *(Gitsn_ResponderGroupAffected *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->fuelType =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_VehicleClassification_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_VehicleClassification *p = (Gitsn_VehicleClassification *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->keyType;
	case 1: return &p->role;
	case 2: return &p->iso3883;
	case 3: return &p->hpmsType;
	case 4: return &p->vehicleType;
	case 5: return &p->responseEquip;
	case 6: return &p->responderType;
	case 7: return &p->fuelType;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_VehicleClassification_membs[] =
{
	{ Dz1Text("keyType"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("role"), Dz1Text("Gitsn_BasicVehicleRole"), 1 },
	{ Dz1Text("iso3883"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("hpmsType"), Dz1Text("Gitsn_VehicleType"), 3 },
	{ Dz1Text("vehicleType"), Dz1Text("Gitsn_VehicleGroupAffected"), 4 },
	{ Dz1Text("responseEquip"), Dz1Text("Gitsn_IncidentResponseEquipment"), 5 },
	{ Dz1Text("responderType"), Dz1Text("Gitsn_ResponderGroupAffected"), 6 },
	{ Dz1Text("fuelType"), Dz1Text("s64_t"), 7 },
	{ NULL, NULL, -1 }
};
// Gitsn_VehicleClassification
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PathHistoryPoint
static bool_t Gitsn_PathHistoryPoint_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_PathHistoryPoint *p = (Gitsn_PathHistoryPoint *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->latOffset =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->lonOffset =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->elevationOffset =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->timeOffset =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->speed =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: Gitsn_PositionalAccuracy_delAndSetNull(&p->posAccuracy); p->posAccuracy = (Gitsn_PositionalAccuracy *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 6: p->heading =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_PathHistoryPoint_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_PathHistoryPoint *p = (Gitsn_PathHistoryPoint *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->latOffset;
	case 1: return &p->lonOffset;
	case 2: return &p->elevationOffset;
	case 3: return &p->timeOffset;
	case 4: return &p->speed;
	case 5: return p->posAccuracy;
	case 6: return &p->heading;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_PathHistoryPoint_membs[] =
{
	{ Dz1Text("latOffset"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("lonOffset"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("elevationOffset"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("timeOffset"), Dz1Text("s64_t"), 3 },
	{ Dz1Text("speed"), Dz1Text("s64_t"), 4 },
	{ Dz1Text("posAccuracy"), Dz1Text("Gitsn_PositionalAccuracy"), 5 },
	{ Dz1Text("heading"), Dz1Text("s64_t"), 6 },
	{ NULL, NULL, -1 }
};
// Gitsn_PathHistoryPoint
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PathHistoryPointList
static bool_t Gitsn_PathHistoryPointList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_PathHistoryPointList *dst = (Gitsn_PathHistoryPointList *)dst_ptr;
	Gitsn_PathHistoryPoint *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_PathHistoryPoint *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_PathHistoryPointList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_PathHistoryPointList *list = (Gitsn_PathHistoryPointList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_PathHistoryPointList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_PathHistoryPointList *list = (Gitsn_PathHistoryPointList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_PathHistoryPointList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PathHistory
static bool_t Gitsn_PathHistory_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_PathHistory *p = (Gitsn_PathHistory *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Gitsn_FullPositionVector_delAndSetNull(&p->initialPosition); p->initialPosition = (Gitsn_FullPositionVector *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: u8_t_delAndSetNull(&p->currGNSSstatus); p->currGNSSstatus = (u8_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: Gitsn_PathHistoryPointList_delAndSetNull(&p->crumbData); p->crumbData = (Gitsn_PathHistoryPointList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_PathHistory_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_PathHistory *p = (Gitsn_PathHistory *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->initialPosition;
	case 1: return p->currGNSSstatus;
	case 2: return p->crumbData;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_PathHistory_membs[] =
{
	{ Dz1Text("initialPosition"), Dz1Text("Gitsn_FullPositionVector"), 0 },
	{ Dz1Text("currGNSSstatus"), Dz1Text("u8_t"), 1 },
	{ Dz1Text("crumbData"), Dz1Text("Gitsn_PathHistoryPointList"), 2 },
	{ NULL, NULL, -1 }
};
// Gitsn_PathHistory
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PathPrediction
static bool_t Gitsn_PathPrediction_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_PathPrediction *p = (Gitsn_PathPrediction *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->radiusOfCurve =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->confidence =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_PathPrediction_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_PathPrediction *p = (Gitsn_PathPrediction *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->radiusOfCurve;
	case 1: return &p->confidence;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_PathPrediction_membs[] =
{
	{ Dz1Text("radiusOfCurve"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("confidence"), Dz1Text("s64_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_PathPrediction
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleSafetyExtensions
static bool_t Gitsn_VehicleSafetyExtensions_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_VehicleSafetyExtensions *p = (Gitsn_VehicleSafetyExtensions *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: u8_t_delAndSetNull(&p->events); p->events = (u8_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: Gitsn_PathHistory_delAndSetNull(&p->pathHistory); p->pathHistory = (Gitsn_PathHistory *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: Gitsn_PathPrediction_delAndSetNull(&p->pathPrediction); p->pathPrediction = (Gitsn_PathPrediction *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: u8_t_delAndSetNull(&p->lights); p->lights = (u8_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_VehicleSafetyExtensions_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_VehicleSafetyExtensions *p = (Gitsn_VehicleSafetyExtensions *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->events;
	case 1: return p->pathHistory;
	case 2: return p->pathPrediction;
	case 3: return p->lights;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_VehicleSafetyExtensions_membs[] =
{
	{ Dz1Text("events"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("pathHistory"), Dz1Text("Gitsn_PathHistory"), 1 },
	{ Dz1Text("pathPrediction"), Dz1Text("Gitsn_PathPrediction"), 2 },
	{ Dz1Text("lights"), Dz1Text("u8_t"), 3 },
	{ NULL, NULL, -1 }
};
// Gitsn_VehicleSafetyExtensions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_LightbarInUse
static bool_t Gitsn_LightbarInUse_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_LightbarInUse v = Gitsn_LightbarInUse_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_LightbarInUse)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_LightbarInUseFromStr(tok->v)) == Gitsn_LightbarInUse_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_LightbarInUse_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_LightbarInUse_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_LightbarInUse v = *(Gitsn_LightbarInUse *)obj;
		Dz1Str str_v = Gitsn_LightbarInUseStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_LightbarInUse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_WiperStatus
static bool_t Gitsn_WiperStatus_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_WiperStatus v = Gitsn_WiperStatus_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_WiperStatus)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_WiperStatusFromStr(tok->v)) == Gitsn_WiperStatus_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_WiperStatus_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_WiperStatus_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_WiperStatus v = *(Gitsn_WiperStatus *)obj;
		Dz1Str str_v = Gitsn_WiperStatusStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_WiperStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_WiperSet
static bool_t Gitsn_WiperSet_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_WiperSet *p = (Gitsn_WiperSet *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->statusFront =  *(Gitsn_WiperStatus *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->rateFront =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->statusRear =  *(Gitsn_WiperStatus *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->rateRear =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_WiperSet_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_WiperSet *p = (Gitsn_WiperSet *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->statusFront;
	case 1: return &p->rateFront;
	case 2: return &p->statusRear;
	case 3: return &p->rateRear;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_WiperSet_membs[] =
{
	{ Dz1Text("statusFront"), Dz1Text("Gitsn_WiperStatus"), 0 },
	{ Dz1Text("rateFront"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("statusRear"), Dz1Text("Gitsn_WiperStatus"), 2 },
	{ Dz1Text("rateRear"), Dz1Text("s64_t"), 3 },
	{ NULL, NULL, -1 }
};
// Gitsn_WiperSet
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_BrakeAppliedPressure
static bool_t Gitsn_BrakeAppliedPressure_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_BrakeAppliedPressure v = Gitsn_BrakeAppliedPressure_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_BrakeAppliedPressure)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_BrakeAppliedPressureFromStr(tok->v)) == Gitsn_BrakeAppliedPressure_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_BrakeAppliedPressure_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_BrakeAppliedPressure_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_BrakeAppliedPressure v = *(Gitsn_BrakeAppliedPressure *)obj;
		Dz1Str str_v = Gitsn_BrakeAppliedPressureStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_BrakeAppliedPressure
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RainSensor
static bool_t Gitsn_RainSensor_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_RainSensor v = Gitsn_RainSensor_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_RainSensor)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_RainSensorFromStr(tok->v)) == Gitsn_RainSensor_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_RainSensor_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_RainSensor_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_RainSensor v = *(Gitsn_RainSensor *)obj;
		Dz1Str str_v = Gitsn_RainSensorStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_RainSensor
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SteeringWheelAngleConfidence
static bool_t Gitsn_SteeringWheelAngleConfidence_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_SteeringWheelAngleConfidence v = Gitsn_SteeringWheelAngleConfidence_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_SteeringWheelAngleConfidence)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_SteeringWheelAngleConfidenceFromStr(tok->v)) == Gitsn_SteeringWheelAngleConfidence_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_SteeringWheelAngleConfidence_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_SteeringWheelAngleConfidence_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_SteeringWheelAngleConfidence v = *(Gitsn_SteeringWheelAngleConfidence *)obj;
		Dz1Str str_v = Gitsn_SteeringWheelAngleConfidenceStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_SteeringWheelAngleConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleStatus_steering
static bool_t Gitsn_VehicleStatus_steering_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_VehicleStatus_steering *p = (Gitsn_VehicleStatus_steering *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->angle =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->confidence =  *(Gitsn_SteeringWheelAngleConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->rate =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->wheels =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_VehicleStatus_steering_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_VehicleStatus_steering *p = (Gitsn_VehicleStatus_steering *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->angle;
	case 1: return &p->confidence;
	case 2: return &p->rate;
	case 3: return &p->wheels;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_VehicleStatus_steering_membs[] =
{
	{ Dz1Text("angle"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("confidence"), Dz1Text("Gitsn_SteeringWheelAngleConfidence"), 1 },
	{ Dz1Text("rate"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("wheels"), Dz1Text("s64_t"), 3 },
	{ NULL, NULL, -1 }
};
// Gitsn_VehicleStatus_steering
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_YawRateConfidence
static bool_t Gitsn_YawRateConfidence_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_YawRateConfidence v = Gitsn_YawRateConfidence_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_YawRateConfidence)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_YawRateConfidenceFromStr(tok->v)) == Gitsn_YawRateConfidence_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_YawRateConfidence_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_YawRateConfidence_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_YawRateConfidence v = *(Gitsn_YawRateConfidence *)obj;
		Dz1Str str_v = Gitsn_YawRateConfidenceStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_YawRateConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AccelerationConfidence
static bool_t Gitsn_AccelerationConfidence_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_AccelerationConfidence v = Gitsn_AccelerationConfidence_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_AccelerationConfidence)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_AccelerationConfidenceFromStr(tok->v)) == Gitsn_AccelerationConfidence_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_AccelerationConfidence_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_AccelerationConfidence_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_AccelerationConfidence v = *(Gitsn_AccelerationConfidence *)obj;
		Dz1Str str_v = Gitsn_AccelerationConfidenceStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_AccelerationConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AccelSteerYawRateConfidence
static bool_t Gitsn_AccelSteerYawRateConfidence_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_AccelSteerYawRateConfidence *p = (Gitsn_AccelSteerYawRateConfidence *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->yawRate =  *(Gitsn_YawRateConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->acceleration =  *(Gitsn_AccelerationConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->steeringWheelAngle =  *(Gitsn_SteeringWheelAngleConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_AccelSteerYawRateConfidence_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_AccelSteerYawRateConfidence *p = (Gitsn_AccelSteerYawRateConfidence *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->yawRate;
	case 1: return &p->acceleration;
	case 2: return &p->steeringWheelAngle;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_AccelSteerYawRateConfidence_membs[] =
{
	{ Dz1Text("yawRate"), Dz1Text("Gitsn_YawRateConfidence"), 0 },
	{ Dz1Text("acceleration"), Dz1Text("Gitsn_AccelerationConfidence"), 1 },
	{ Dz1Text("steeringWheelAngle"), Dz1Text("Gitsn_SteeringWheelAngleConfidence"), 2 },
	{ NULL, NULL, -1 }
};
// Gitsn_AccelSteerYawRateConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ConfidenceSet
static bool_t Gitsn_ConfidenceSet_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ConfidenceSet *p = (Gitsn_ConfidenceSet *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Gitsn_AccelSteerYawRateConfidence_delAndSetNull(&p->accelConfidence); p->accelConfidence = (Gitsn_AccelSteerYawRateConfidence *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: Gitsn_SpeedandHeadingandThrottleConfidence_delAndSetNull(&p->speedConfidence); p->speedConfidence = (Gitsn_SpeedandHeadingandThrottleConfidence *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: p->timeConfidence =  *(Gitsn_TimeConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: Gitsn_PositionConfidenceSet_delAndSetNull(&p->posConfidence); p->posConfidence = (Gitsn_PositionConfidenceSet *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 4: p->steerConfidence =  *(Gitsn_SteeringWheelAngleConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->headingConfidence =  *(Gitsn_HeadingConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->throttleConfidence =  *(Gitsn_ThrottleConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_ConfidenceSet_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_ConfidenceSet *p = (Gitsn_ConfidenceSet *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->accelConfidence;
	case 1: return p->speedConfidence;
	case 2: return &p->timeConfidence;
	case 3: return p->posConfidence;
	case 4: return &p->steerConfidence;
	case 5: return &p->headingConfidence;
	case 6: return &p->throttleConfidence;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_ConfidenceSet_membs[] =
{
	{ Dz1Text("accelConfidence"), Dz1Text("Gitsn_AccelSteerYawRateConfidence"), 0 },
	{ Dz1Text("speedConfidence"), Dz1Text("Gitsn_SpeedandHeadingandThrottleConfidence"), 1 },
	{ Dz1Text("timeConfidence"), Dz1Text("Gitsn_TimeConfidence"), 2 },
	{ Dz1Text("posConfidence"), Dz1Text("Gitsn_PositionConfidenceSet"), 3 },
	{ Dz1Text("steerConfidence"), Dz1Text("Gitsn_SteeringWheelAngleConfidence"), 4 },
	{ Dz1Text("headingConfidence"), Dz1Text("Gitsn_HeadingConfidence"), 5 },
	{ Dz1Text("throttleConfidence"), Dz1Text("Gitsn_ThrottleConfidence"), 6 },
	{ NULL, NULL, -1 }
};
// Gitsn_ConfidenceSet
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleStatus_accelSets
static bool_t Gitsn_VehicleStatus_accelSets_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_VehicleStatus_accelSets *p = (Gitsn_VehicleStatus_accelSets *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Gitsn_AccelerationSet4Way_delAndSetNull(&p->accel4way); p->accel4way = (Gitsn_AccelerationSet4Way *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: u8_t_delAndSetNull(&p->vertAccelThres); p->vertAccelThres = (u8_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: p->yawRateCon =  *(Gitsn_YawRateConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->hozAccelCon =  *(Gitsn_AccelerationConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: Gitsn_ConfidenceSet_delAndSetNull(&p->confidenceSet); p->confidenceSet = (Gitsn_ConfidenceSet *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_VehicleStatus_accelSets_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_VehicleStatus_accelSets *p = (Gitsn_VehicleStatus_accelSets *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->accel4way;
	case 1: return p->vertAccelThres;
	case 2: return &p->yawRateCon;
	case 3: return &p->hozAccelCon;
	case 4: return p->confidenceSet;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_VehicleStatus_accelSets_membs[] =
{
	{ Dz1Text("accel4way"), Dz1Text("Gitsn_AccelerationSet4Way"), 0 },
	{ Dz1Text("vertAccelThres"), Dz1Text("u8_t"), 1 },
	{ Dz1Text("yawRateCon"), Dz1Text("Gitsn_YawRateConfidence"), 2 },
	{ Dz1Text("hozAccelCon"), Dz1Text("Gitsn_AccelerationConfidence"), 3 },
	{ Dz1Text("confidenceSet"), Dz1Text("Gitsn_ConfidenceSet"), 4 },
	{ NULL, NULL, -1 }
};
// Gitsn_VehicleStatus_accelSets
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleStatus_object
static bool_t Gitsn_VehicleStatus_object_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_VehicleStatus_object *p = (Gitsn_VehicleStatus_object *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->obDist =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->obDirect =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: Gitsn_DDateTime_delAndSetNull(&p->dateTime); p->dateTime = (Gitsn_DDateTime *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_VehicleStatus_object_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_VehicleStatus_object *p = (Gitsn_VehicleStatus_object *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->obDist;
	case 1: return &p->obDirect;
	case 2: return p->dateTime;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_VehicleStatus_object_membs[] =
{
	{ Dz1Text("obDist"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("obDirect"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("dateTime"), Dz1Text("Gitsn_DDateTime"), 2 },
	{ NULL, NULL, -1 }
};
// Gitsn_VehicleStatus_object
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_BumperHeights
static bool_t Gitsn_BumperHeights_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_BumperHeights *p = (Gitsn_BumperHeights *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->front =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->rear =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_BumperHeights_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_BumperHeights *p = (Gitsn_BumperHeights *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->front;
	case 1: return &p->rear;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_BumperHeights_membs[] =
{
	{ Dz1Text("front"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("rear"), Dz1Text("s64_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_BumperHeights
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleStatus_vehicleData
static bool_t Gitsn_VehicleStatus_vehicleData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_VehicleStatus_vehicleData *p = (Gitsn_VehicleStatus_vehicleData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->height =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: Gitsn_BumperHeights_delAndSetNull(&p->bumpers); p->bumpers = (Gitsn_BumperHeights *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: p->mass =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->trailerWeight =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->type =  *(Gitsn_VehicleType *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_VehicleStatus_vehicleData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_VehicleStatus_vehicleData *p = (Gitsn_VehicleStatus_vehicleData *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->height;
	case 1: return p->bumpers;
	case 2: return &p->mass;
	case 3: return &p->trailerWeight;
	case 4: return &p->type;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_VehicleStatus_vehicleData_membs[] =
{
	{ Dz1Text("height"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("bumpers"), Dz1Text("Gitsn_BumperHeights"), 1 },
	{ Dz1Text("mass"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("trailerWeight"), Dz1Text("s64_t"), 3 },
	{ Dz1Text("type"), Dz1Text("Gitsn_VehicleType"), 4 },
	{ NULL, NULL, -1 }
};
// Gitsn_VehicleStatus_vehicleData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_WheelSensorStatus
static bool_t Gitsn_WheelSensorStatus_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_WheelSensorStatus v = Gitsn_WheelSensorStatus_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_WheelSensorStatus)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_WheelSensorStatusFromStr(tok->v)) == Gitsn_WheelSensorStatus_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_WheelSensorStatus_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_WheelSensorStatus_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_WheelSensorStatus v = *(Gitsn_WheelSensorStatus *)obj;
		Dz1Str str_v = Gitsn_WheelSensorStatusStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_WheelSensorStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_WheelEndElectFault
static bool_t Gitsn_WheelEndElectFault_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_WheelEndElectFault v = Gitsn_WheelEndElectFault_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_WheelEndElectFault)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_WheelEndElectFaultFromStr(tok->v)) == Gitsn_WheelEndElectFault_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_WheelEndElectFault_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_WheelEndElectFault_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_WheelEndElectFault v = *(Gitsn_WheelEndElectFault *)obj;
		Dz1Str str_v = Gitsn_WheelEndElectFaultStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_WheelEndElectFault
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TirePressureThresholdDetection
static bool_t Gitsn_TirePressureThresholdDetection_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_TirePressureThresholdDetection v = Gitsn_TirePressureThresholdDetection_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_TirePressureThresholdDetection)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_TirePressureThresholdDetectionFromStr(tok->v)) == Gitsn_TirePressureThresholdDetection_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_TirePressureThresholdDetection_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_TirePressureThresholdDetection_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_TirePressureThresholdDetection v = *(Gitsn_TirePressureThresholdDetection *)obj;
		Dz1Str str_v = Gitsn_TirePressureThresholdDetectionStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_TirePressureThresholdDetection
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TireData
static bool_t Gitsn_TireData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_TireData *p = (Gitsn_TireData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->location =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->pressure =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->temp =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->wheelSensorStatus =  *(Gitsn_WheelSensorStatus *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->wheelEndElectFault =  *(Gitsn_WheelEndElectFault *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->leakageRate =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->detection =  *(Gitsn_TirePressureThresholdDetection *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_TireData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_TireData *p = (Gitsn_TireData *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->location;
	case 1: return &p->pressure;
	case 2: return &p->temp;
	case 3: return &p->wheelSensorStatus;
	case 4: return &p->wheelEndElectFault;
	case 5: return &p->leakageRate;
	case 6: return &p->detection;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_TireData_membs[] =
{
	{ Dz1Text("location"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("pressure"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("temp"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("wheelSensorStatus"), Dz1Text("Gitsn_WheelSensorStatus"), 3 },
	{ Dz1Text("wheelEndElectFault"), Dz1Text("Gitsn_WheelEndElectFault"), 4 },
	{ Dz1Text("leakageRate"), Dz1Text("s64_t"), 5 },
	{ Dz1Text("detection"), Dz1Text("Gitsn_TirePressureThresholdDetection"), 6 },
	{ NULL, NULL, -1 }
};
// Gitsn_TireData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TireDataList
static bool_t Gitsn_TireDataList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_TireDataList *dst = (Gitsn_TireDataList *)dst_ptr;
	Gitsn_TireData *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_TireData *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_TireDataList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_TireDataList *list = (Gitsn_TireDataList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_TireDataList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_TireDataList *list = (Gitsn_TireDataList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_TireDataList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AxleWeightSet
static bool_t Gitsn_AxleWeightSet_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_AxleWeightSet *p = (Gitsn_AxleWeightSet *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->location =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->weight =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_AxleWeightSet_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_AxleWeightSet *p = (Gitsn_AxleWeightSet *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->location;
	case 1: return &p->weight;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_AxleWeightSet_membs[] =
{
	{ Dz1Text("location"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("weight"), Dz1Text("s64_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_AxleWeightSet
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AxleWeightList
static bool_t Gitsn_AxleWeightList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_AxleWeightList *dst = (Gitsn_AxleWeightList *)dst_ptr;
	Gitsn_AxleWeightSet *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_AxleWeightSet *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_AxleWeightList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_AxleWeightList *list = (Gitsn_AxleWeightList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_AxleWeightList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_AxleWeightList *list = (Gitsn_AxleWeightList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_AxleWeightList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_J1939DataItems
static bool_t Gitsn_J1939DataItems_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_J1939DataItems *p = (Gitsn_J1939DataItems *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Gitsn_TireDataList_delAndSetNull(&p->tires); p->tires = (Gitsn_TireDataList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: Gitsn_AxleWeightList_delAndSetNull(&p->axles); p->axles = (Gitsn_AxleWeightList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: p->trailerWeight =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->cargoWeight =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->steeringAxleTemperature =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->driveAxleLocation =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->driveAxleLiftAirPressure =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->driveAxleTemperature =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->driveAxleLubePressure =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 9: p->steeringAxleLubePressure =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_J1939DataItems_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_J1939DataItems *p = (Gitsn_J1939DataItems *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->tires;
	case 1: return p->axles;
	case 2: return &p->trailerWeight;
	case 3: return &p->cargoWeight;
	case 4: return &p->steeringAxleTemperature;
	case 5: return &p->driveAxleLocation;
	case 6: return &p->driveAxleLiftAirPressure;
	case 7: return &p->driveAxleTemperature;
	case 8: return &p->driveAxleLubePressure;
	case 9: return &p->steeringAxleLubePressure;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_J1939DataItems_membs[] =
{
	{ Dz1Text("tires"), Dz1Text("Gitsn_TireDataList"), 0 },
	{ Dz1Text("axles"), Dz1Text("Gitsn_AxleWeightList"), 1 },
	{ Dz1Text("trailerWeight"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("cargoWeight"), Dz1Text("s64_t"), 3 },
	{ Dz1Text("steeringAxleTemperature"), Dz1Text("s64_t"), 4 },
	{ Dz1Text("driveAxleLocation"), Dz1Text("s64_t"), 5 },
	{ Dz1Text("driveAxleLiftAirPressure"), Dz1Text("s64_t"), 6 },
	{ Dz1Text("driveAxleTemperature"), Dz1Text("s64_t"), 7 },
	{ Dz1Text("driveAxleLubePressure"), Dz1Text("s64_t"), 8 },
	{ Dz1Text("steeringAxleLubePressure"), Dz1Text("s64_t"), 9 },
	{ NULL, NULL, -1 }
};
// Gitsn_J1939DataItems
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_EssPrecipYesNo
static bool_t Gitsn_EssPrecipYesNo_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_EssPrecipYesNo v = Gitsn_EssPrecipYesNo_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_EssPrecipYesNo)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_EssPrecipYesNoFromStr(tok->v)) == Gitsn_EssPrecipYesNo_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_EssPrecipYesNo_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_EssPrecipYesNo_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_EssPrecipYesNo v = *(Gitsn_EssPrecipYesNo *)obj;
		Dz1Str str_v = Gitsn_EssPrecipYesNoStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_EssPrecipYesNo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_EssPrecipSituation
static bool_t Gitsn_EssPrecipSituation_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_EssPrecipSituation v = Gitsn_EssPrecipSituation_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_EssPrecipSituation)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_EssPrecipSituationFromStr(tok->v)) == Gitsn_EssPrecipSituation_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_EssPrecipSituation_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_EssPrecipSituation_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_EssPrecipSituation v = *(Gitsn_EssPrecipSituation *)obj;
		Dz1Str str_v = Gitsn_EssPrecipSituationStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_EssPrecipSituation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleStatus_weatherReport
static bool_t Gitsn_VehicleStatus_weatherReport_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_VehicleStatus_weatherReport *p = (Gitsn_VehicleStatus_weatherReport *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->isRaining =  *(Gitsn_EssPrecipYesNo *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->rainRate =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->precipSituation =  *(Gitsn_EssPrecipSituation *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->solarRadiation =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->friction =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_VehicleStatus_weatherReport_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_VehicleStatus_weatherReport *p = (Gitsn_VehicleStatus_weatherReport *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->isRaining;
	case 1: return &p->rainRate;
	case 2: return &p->precipSituation;
	case 3: return &p->solarRadiation;
	case 4: return &p->friction;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_VehicleStatus_weatherReport_membs[] =
{
	{ Dz1Text("isRaining"), Dz1Text("Gitsn_EssPrecipYesNo"), 0 },
	{ Dz1Text("rainRate"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("precipSituation"), Dz1Text("Gitsn_EssPrecipSituation"), 2 },
	{ Dz1Text("solarRadiation"), Dz1Text("s64_t"), 3 },
	{ Dz1Text("friction"), Dz1Text("s64_t"), 4 },
	{ NULL, NULL, -1 }
};
// Gitsn_VehicleStatus_weatherReport
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleStatus
static bool_t Gitsn_VehicleStatus_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_VehicleStatus *p = (Gitsn_VehicleStatus *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: u8_t_delAndSetNull(&p->lights); p->lights = (u8_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: p->lightBar =  *(Gitsn_LightbarInUse *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: Gitsn_WiperSet_delAndSetNull(&p->wipers); p->wipers = (Gitsn_WiperSet *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: Gitsn_BrakeSystemStatus_delAndSetNull(&p->brakeStatus); p->brakeStatus = (Gitsn_BrakeSystemStatus *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 4: p->brakePressure =  *(Gitsn_BrakeAppliedPressure *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->roadFriction =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->sunData =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->rainData =  *(Gitsn_RainSensor *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->airTemp =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 9: p->airPres =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 10: Gitsn_VehicleStatus_steering_delAndSetNull(&p->steering); p->steering = (Gitsn_VehicleStatus_steering *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 11: Gitsn_VehicleStatus_accelSets_delAndSetNull(&p->accelSets); p->accelSets = (Gitsn_VehicleStatus_accelSets *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 12: Gitsn_VehicleStatus_object_delAndSetNull(&p->object); p->object = (Gitsn_VehicleStatus_object *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 13: Gitsn_FullPositionVector_delAndSetNull(&p->fullPos); p->fullPos = (Gitsn_FullPositionVector *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 14: p->throttlePos =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 15: Gitsn_SpeedandHeadingandThrottleConfidence_delAndSetNull(&p->speedHeadC); p->speedHeadC = (Gitsn_SpeedandHeadingandThrottleConfidence *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 16: p->speedC =  *(Gitsn_SpeedConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 17: Gitsn_VehicleStatus_vehicleData_delAndSetNull(&p->vehicleData); p->vehicleData = (Gitsn_VehicleStatus_vehicleData *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 18: Gitsn_VehicleIdent_delAndSetNull(&p->vehicleIdent); p->vehicleIdent = (Gitsn_VehicleIdent *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 19: Gitsn_J1939DataItems_delAndSetNull(&p->j1939DataItems); p->j1939DataItems = (Gitsn_J1939DataItems *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 20: Gitsn_VehicleStatus_weatherReport_delAndSetNull(&p->weatherReport); p->weatherReport = (Gitsn_VehicleStatus_weatherReport *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 21: u8_t_delAndSetNull(&p->gnssStatus); p->gnssStatus = (u8_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_VehicleStatus_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_VehicleStatus *p = (Gitsn_VehicleStatus *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->lights;
	case 1: return &p->lightBar;
	case 2: return p->wipers;
	case 3: return p->brakeStatus;
	case 4: return &p->brakePressure;
	case 5: return &p->roadFriction;
	case 6: return &p->sunData;
	case 7: return &p->rainData;
	case 8: return &p->airTemp;
	case 9: return &p->airPres;
	case 10: return p->steering;
	case 11: return p->accelSets;
	case 12: return p->object;
	case 13: return p->fullPos;
	case 14: return &p->throttlePos;
	case 15: return p->speedHeadC;
	case 16: return &p->speedC;
	case 17: return p->vehicleData;
	case 18: return p->vehicleIdent;
	case 19: return p->j1939DataItems;
	case 20: return p->weatherReport;
	case 21: return p->gnssStatus;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_VehicleStatus_membs[] =
{
	{ Dz1Text("lights"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("lightBar"), Dz1Text("Gitsn_LightbarInUse"), 1 },
	{ Dz1Text("wipers"), Dz1Text("Gitsn_WiperSet"), 2 },
	{ Dz1Text("brakeStatus"), Dz1Text("Gitsn_BrakeSystemStatus"), 3 },
	{ Dz1Text("brakePressure"), Dz1Text("Gitsn_BrakeAppliedPressure"), 4 },
	{ Dz1Text("roadFriction"), Dz1Text("s64_t"), 5 },
	{ Dz1Text("sunData"), Dz1Text("s64_t"), 6 },
	{ Dz1Text("rainData"), Dz1Text("Gitsn_RainSensor"), 7 },
	{ Dz1Text("airTemp"), Dz1Text("s64_t"), 8 },
	{ Dz1Text("airPres"), Dz1Text("s64_t"), 9 },
	{ Dz1Text("steering"), Dz1Text("Gitsn_VehicleStatus_steering"), 10 },
	{ Dz1Text("accelSets"), Dz1Text("Gitsn_VehicleStatus_accelSets"), 11 },
	{ Dz1Text("object"), Dz1Text("Gitsn_VehicleStatus_object"), 12 },
	{ Dz1Text("fullPos"), Dz1Text("Gitsn_FullPositionVector"), 13 },
	{ Dz1Text("throttlePos"), Dz1Text("s64_t"), 14 },
	{ Dz1Text("speedHeadC"), Dz1Text("Gitsn_SpeedandHeadingandThrottleConfidence"), 15 },
	{ Dz1Text("speedC"), Dz1Text("Gitsn_SpeedConfidence"), 16 },
	{ Dz1Text("vehicleData"), Dz1Text("Gitsn_VehicleStatus_vehicleData"), 17 },
	{ Dz1Text("vehicleIdent"), Dz1Text("Gitsn_VehicleIdent"), 18 },
	{ Dz1Text("j1939DataItems"), Dz1Text("Gitsn_J1939DataItems"), 19 },
	{ Dz1Text("weatherReport"), Dz1Text("Gitsn_VehicleStatus_weatherReport"), 20 },
	{ Dz1Text("gnssStatus"), Dz1Text("u8_t"), 21 },
	{ NULL, NULL, -1 }
};
// Gitsn_VehicleStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Snapshot
static bool_t Gitsn_Snapshot_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Snapshot *p = (Gitsn_Snapshot *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Gitsn_FullPositionVector_delAndSetNull(&p->thePosition); p->thePosition = (Gitsn_FullPositionVector *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: Gitsn_VehicleSafetyExtensions_delAndSetNull(&p->safetyExt); p->safetyExt = (Gitsn_VehicleSafetyExtensions *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: Gitsn_VehicleStatus_delAndSetNull(&p->dataSet); p->dataSet = (Gitsn_VehicleStatus *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Snapshot_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Snapshot *p = (Gitsn_Snapshot *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->thePosition;
	case 1: return p->safetyExt;
	case 2: return p->dataSet;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Snapshot_membs[] =
{
	{ Dz1Text("thePosition"), Dz1Text("Gitsn_FullPositionVector"), 0 },
	{ Dz1Text("safetyExt"), Dz1Text("Gitsn_VehicleSafetyExtensions"), 1 },
	{ Dz1Text("dataSet"), Dz1Text("Gitsn_VehicleStatus"), 2 },
	{ NULL, NULL, -1 }
};
// Gitsn_Snapshot
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ProbeVehicleData_snapshots
static bool_t Gitsn_ProbeVehicleData_snapshots_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ProbeVehicleData_snapshots *dst = (Gitsn_ProbeVehicleData_snapshots *)dst_ptr;
	Gitsn_Snapshot *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_Snapshot *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_ProbeVehicleData_snapshots_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_ProbeVehicleData_snapshots *list = (Gitsn_ProbeVehicleData_snapshots *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_ProbeVehicleData_snapshots_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_ProbeVehicleData_snapshots *list = (Gitsn_ProbeVehicleData_snapshots *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_ProbeVehicleData_snapshots
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ProbeVehicleData
static bool_t Gitsn_ProbeVehicleData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ProbeVehicleData *p = (Gitsn_ProbeVehicleData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->timeStamp =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->segNum =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: Gitsn_VehicleIdent_delAndSetNull(&p->probeID); p->probeID = (Gitsn_VehicleIdent *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: Gitsn_FullPositionVector_delAndSetNull(&p->startVector); p->startVector = (Gitsn_FullPositionVector *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 4: Gitsn_VehicleClassification_delAndSetNull(&p->vehicleType); p->vehicleType = (Gitsn_VehicleClassification *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 5: Gitsn_ProbeVehicleData_snapshots_delAndSetNull(&p->snapshots); p->snapshots = (Gitsn_ProbeVehicleData_snapshots *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_ProbeVehicleData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_ProbeVehicleData *p = (Gitsn_ProbeVehicleData *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->timeStamp;
	case 1: return &p->segNum;
	case 2: return p->probeID;
	case 3: return p->startVector;
	case 4: return p->vehicleType;
	case 5: return p->snapshots;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_ProbeVehicleData_membs[] =
{
	{ Dz1Text("timeStamp"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("segNum"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("probeID"), Dz1Text("Gitsn_VehicleIdent"), 2 },
	{ Dz1Text("startVector"), Dz1Text("Gitsn_FullPositionVector"), 3 },
	{ Dz1Text("vehicleType"), Dz1Text("Gitsn_VehicleClassification"), 4 },
	{ Dz1Text("snapshots"), Dz1Text("Gitsn_ProbeVehicleData_snapshots"), 5 },
	{ NULL, NULL, -1 }
};
// Gitsn_ProbeVehicleData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RoadSideAlert_description
static bool_t Gitsn_RoadSideAlert_description_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_RoadSideAlert_description *dst = (Gitsn_RoadSideAlert_description *)dst_ptr;
	s64_t *node = NULL;
	if (dst == NULL || var == NULL || (node = (s64_t *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, *node)).code) ERR_OUT(errp);
	else
	{
		// var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_RoadSideAlert_description_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_RoadSideAlert_description *list = (Gitsn_RoadSideAlert_description *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_RoadSideAlert_description_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_RoadSideAlert_description *list = (Gitsn_RoadSideAlert_description *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_RoadSideAlert_description
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Extent
static bool_t Gitsn_Extent_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Extent v = Gitsn_Extent_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_Extent)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_ExtentFromStr(tok->v)) == Gitsn_Extent_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_Extent_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_Extent_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_Extent v = *(Gitsn_Extent *)obj;
		Dz1Str str_v = Gitsn_ExtentStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_Extent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RoadSideAlert
static bool_t Gitsn_RoadSideAlert_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_RoadSideAlert *p = (Gitsn_RoadSideAlert *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->msgCnt =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->timeStamp =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->typeEvent =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: Gitsn_RoadSideAlert_description_delAndSetNull(&p->description); p->description = (Gitsn_RoadSideAlert_description *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 4: Dz1Str_delAndSetNull(&p->priority); p->priority = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 5: u8_t_delAndSetNull(&p->heading); p->heading = (u8_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 6: p->extent =  *(Gitsn_Extent *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: Gitsn_FullPositionVector_delAndSetNull(&p->position); p->position = (Gitsn_FullPositionVector *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 8: p->furtherInfoID =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_RoadSideAlert_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_RoadSideAlert *p = (Gitsn_RoadSideAlert *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->msgCnt;
	case 1: return &p->timeStamp;
	case 2: return &p->typeEvent;
	case 3: return p->description;
	case 4: return p->priority;
	case 5: return p->heading;
	case 6: return &p->extent;
	case 7: return p->position;
	case 8: return &p->furtherInfoID;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_RoadSideAlert_membs[] =
{
	{ Dz1Text("msgCnt"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("timeStamp"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("typeEvent"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("description"), Dz1Text("Gitsn_RoadSideAlert_description"), 3 },
	{ Dz1Text("priority"), Dz1Text("Dz1Str"), 4 },
	{ Dz1Text("heading"), Dz1Text("u8_t"), 5 },
	{ Dz1Text("extent"), Dz1Text("Gitsn_Extent"), 6 },
	{ Dz1Text("position"), Dz1Text("Gitsn_FullPositionVector"), 7 },
	{ Dz1Text("furtherInfoID"), Dz1Text("u16_t"), 8 },
	{ NULL, NULL, -1 }
};
// Gitsn_RoadSideAlert
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TravelerInfoType
static bool_t Gitsn_TravelerInfoType_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_TravelerInfoType v = Gitsn_TravelerInfoType_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_TravelerInfoType)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_TravelerInfoTypeFromStr(tok->v)) == Gitsn_TravelerInfoType_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_TravelerInfoType_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_TravelerInfoType_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_TravelerInfoType v = *(Gitsn_TravelerInfoType *)obj;
		Dz1Str str_v = Gitsn_TravelerInfoTypeStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_TravelerInfoType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MUTCDCode
static bool_t Gitsn_MUTCDCode_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_MUTCDCode v = Gitsn_MUTCDCode_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_MUTCDCode)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_MUTCDCodeFromStr(tok->v)) == Gitsn_MUTCDCode_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_MUTCDCode_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_MUTCDCode_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_MUTCDCode v = *(Gitsn_MUTCDCode *)obj;
		Dz1Str str_v = Gitsn_MUTCDCodeStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_MUTCDCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RoadSignID
static bool_t Gitsn_RoadSignID_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_RoadSignID *p = (Gitsn_RoadSignID *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Gitsn_Position3D_delAndSetNull(&p->position); p->position = (Gitsn_Position3D *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: u8_t_delAndSetNull(&p->viewAngle); p->viewAngle = (u8_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: p->mutcdCode =  *(Gitsn_MUTCDCode *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: Dz1Str_delAndSetNull(&p->crc); p->crc = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_RoadSignID_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_RoadSignID *p = (Gitsn_RoadSignID *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->position;
	case 1: return p->viewAngle;
	case 2: return &p->mutcdCode;
	case 3: return p->crc;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_RoadSignID_membs[] =
{
	{ Dz1Text("position"), Dz1Text("Gitsn_Position3D"), 0 },
	{ Dz1Text("viewAngle"), Dz1Text("u8_t"), 1 },
	{ Dz1Text("mutcdCode"), Dz1Text("Gitsn_MUTCDCode"), 2 },
	{ Dz1Text("crc"), Dz1Text("Dz1Str"), 3 },
	{ NULL, NULL, -1 }
};
// Gitsn_RoadSignID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TravelerDataFrame_msgId
static bool_t Gitsn_TravelerDataFrame_msgId_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_TravelerDataFrame_msgId *p = (Gitsn_TravelerDataFrame_msgId *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_TravelerDataFrame_msgIdPresent_furtherInfoID: p->x.furtherInfoID = *(u16_t *)info->data; break;
	case Gitsn_TravelerDataFrame_msgIdPresent_roadSignID: Gitsn_RoadSignID_delAndSetNull(&p->x.roadSignID); p->x.roadSignID =(Gitsn_RoadSignID *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_TravelerDataFrame_msgIdPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_TravelerDataFrame_msgId_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_TravelerDataFrame_msgId *p = (Gitsn_TravelerDataFrame_msgId *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_TravelerDataFrame_msgIdPresent_furtherInfoID: return &p->x.furtherInfoID;
		case Gitsn_TravelerDataFrame_msgIdPresent_roadSignID: return p->x.roadSignID;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_TravelerDataFrame_msgId_membs[] =
{
	{ Dz1Text("furtherInfoID"), Dz1Text("u16_t"), Gitsn_TravelerDataFrame_msgIdPresent_furtherInfoID },
	{ Dz1Text("roadSignID"), Dz1Text("Gitsn_RoadSignID"), Gitsn_TravelerDataFrame_msgIdPresent_roadSignID },
	{ NULL, NULL, -1 }
};
// Gitsn_TravelerDataFrame_msgId
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DirectionOfUse
static bool_t Gitsn_DirectionOfUse_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_DirectionOfUse v = Gitsn_DirectionOfUse_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_DirectionOfUse)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_DirectionOfUseFromStr(tok->v)) == Gitsn_DirectionOfUse_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_DirectionOfUse_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_DirectionOfUse_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_DirectionOfUse v = *(Gitsn_DirectionOfUse *)obj;
		Dz1Str str_v = Gitsn_DirectionOfUseStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_DirectionOfUse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_LL_24B
static bool_t Gitsn_Node_LL_24B_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Node_LL_24B *p = (Gitsn_Node_LL_24B *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->lon =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->lat =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Node_LL_24B_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Node_LL_24B *p = (Gitsn_Node_LL_24B *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->lon;
	case 1: return &p->lat;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Node_LL_24B_membs[] =
{
	{ Dz1Text("lon"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("lat"), Dz1Text("s64_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_Node_LL_24B
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_LL_28B
static bool_t Gitsn_Node_LL_28B_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Node_LL_28B *p = (Gitsn_Node_LL_28B *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->lon =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->lat =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Node_LL_28B_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Node_LL_28B *p = (Gitsn_Node_LL_28B *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->lon;
	case 1: return &p->lat;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Node_LL_28B_membs[] =
{
	{ Dz1Text("lon"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("lat"), Dz1Text("s64_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_Node_LL_28B
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_LL_32B
static bool_t Gitsn_Node_LL_32B_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Node_LL_32B *p = (Gitsn_Node_LL_32B *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->lon =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->lat =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Node_LL_32B_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Node_LL_32B *p = (Gitsn_Node_LL_32B *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->lon;
	case 1: return &p->lat;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Node_LL_32B_membs[] =
{
	{ Dz1Text("lon"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("lat"), Dz1Text("s64_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_Node_LL_32B
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_LL_36B
static bool_t Gitsn_Node_LL_36B_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Node_LL_36B *p = (Gitsn_Node_LL_36B *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->lon =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->lat =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Node_LL_36B_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Node_LL_36B *p = (Gitsn_Node_LL_36B *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->lon;
	case 1: return &p->lat;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Node_LL_36B_membs[] =
{
	{ Dz1Text("lon"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("lat"), Dz1Text("s64_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_Node_LL_36B
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_LL_44B
static bool_t Gitsn_Node_LL_44B_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Node_LL_44B *p = (Gitsn_Node_LL_44B *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->lon =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->lat =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Node_LL_44B_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Node_LL_44B *p = (Gitsn_Node_LL_44B *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->lon;
	case 1: return &p->lat;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Node_LL_44B_membs[] =
{
	{ Dz1Text("lon"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("lat"), Dz1Text("s64_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_Node_LL_44B
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Node_LL_48B
static bool_t Gitsn_Node_LL_48B_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Node_LL_48B *p = (Gitsn_Node_LL_48B *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->lon =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->lat =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Node_LL_48B_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Node_LL_48B *p = (Gitsn_Node_LL_48B *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->lon;
	case 1: return &p->lat;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Node_LL_48B_membs[] =
{
	{ Dz1Text("lon"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("lat"), Dz1Text("s64_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_Node_LL_48B
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeOffsetPointLL
static bool_t Gitsn_NodeOffsetPointLL_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_NodeOffsetPointLL *p = (Gitsn_NodeOffsetPointLL *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_NodeOffsetPointLLPresent_node_LL1: Gitsn_Node_LL_24B_delAndSetNull(&p->x.node_LL1); p->x.node_LL1 =(Gitsn_Node_LL_24B *)info->data; info->data = NULL; break;
	case Gitsn_NodeOffsetPointLLPresent_node_LL2: Gitsn_Node_LL_28B_delAndSetNull(&p->x.node_LL2); p->x.node_LL2 =(Gitsn_Node_LL_28B *)info->data; info->data = NULL; break;
	case Gitsn_NodeOffsetPointLLPresent_node_LL3: Gitsn_Node_LL_32B_delAndSetNull(&p->x.node_LL3); p->x.node_LL3 =(Gitsn_Node_LL_32B *)info->data; info->data = NULL; break;
	case Gitsn_NodeOffsetPointLLPresent_node_LL4: Gitsn_Node_LL_36B_delAndSetNull(&p->x.node_LL4); p->x.node_LL4 =(Gitsn_Node_LL_36B *)info->data; info->data = NULL; break;
	case Gitsn_NodeOffsetPointLLPresent_node_LL5: Gitsn_Node_LL_44B_delAndSetNull(&p->x.node_LL5); p->x.node_LL5 =(Gitsn_Node_LL_44B *)info->data; info->data = NULL; break;
	case Gitsn_NodeOffsetPointLLPresent_node_LL6: Gitsn_Node_LL_48B_delAndSetNull(&p->x.node_LL6); p->x.node_LL6 =(Gitsn_Node_LL_48B *)info->data; info->data = NULL; break;
	case Gitsn_NodeOffsetPointLLPresent_node_LatLon: Gitsn_Node_LLmD_64b_delAndSetNull(&p->x.node_LatLon); p->x.node_LatLon =(Gitsn_Node_LLmD_64b *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_NodeOffsetPointLLPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_NodeOffsetPointLL_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_NodeOffsetPointLL *p = (Gitsn_NodeOffsetPointLL *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_NodeOffsetPointLLPresent_node_LL1: return p->x.node_LL1;
		case Gitsn_NodeOffsetPointLLPresent_node_LL2: return p->x.node_LL2;
		case Gitsn_NodeOffsetPointLLPresent_node_LL3: return p->x.node_LL3;
		case Gitsn_NodeOffsetPointLLPresent_node_LL4: return p->x.node_LL4;
		case Gitsn_NodeOffsetPointLLPresent_node_LL5: return p->x.node_LL5;
		case Gitsn_NodeOffsetPointLLPresent_node_LL6: return p->x.node_LL6;
		case Gitsn_NodeOffsetPointLLPresent_node_LatLon: return p->x.node_LatLon;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_NodeOffsetPointLL_membs[] =
{
	{ Dz1Text("node_LL1"), Dz1Text("Gitsn_Node_LL_24B"), Gitsn_NodeOffsetPointLLPresent_node_LL1 },
	{ Dz1Text("node_LL2"), Dz1Text("Gitsn_Node_LL_28B"), Gitsn_NodeOffsetPointLLPresent_node_LL2 },
	{ Dz1Text("node_LL3"), Dz1Text("Gitsn_Node_LL_32B"), Gitsn_NodeOffsetPointLLPresent_node_LL3 },
	{ Dz1Text("node_LL4"), Dz1Text("Gitsn_Node_LL_36B"), Gitsn_NodeOffsetPointLLPresent_node_LL4 },
	{ Dz1Text("node_LL5"), Dz1Text("Gitsn_Node_LL_44B"), Gitsn_NodeOffsetPointLLPresent_node_LL5 },
	{ Dz1Text("node_LL6"), Dz1Text("Gitsn_Node_LL_48B"), Gitsn_NodeOffsetPointLLPresent_node_LL6 },
	{ Dz1Text("node_LatLon"), Dz1Text("Gitsn_Node_LLmD_64b"), Gitsn_NodeOffsetPointLLPresent_node_LatLon },
	{ NULL, NULL, -1 }
};
// Gitsn_NodeOffsetPointLL
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeAttributeLL
static bool_t Gitsn_NodeAttributeLL_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_NodeAttributeLL v = Gitsn_NodeAttributeLL_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_NodeAttributeLL)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_NodeAttributeLLFromStr(tok->v)) == Gitsn_NodeAttributeLL_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_NodeAttributeLL_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_NodeAttributeLL_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_NodeAttributeLL v = *(Gitsn_NodeAttributeLL *)obj;
		Dz1Str str_v = Gitsn_NodeAttributeLLStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_NodeAttributeLL
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeAttributeLLList
static bool_t Gitsn_NodeAttributeLLList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_NodeAttributeLLList *dst = (Gitsn_NodeAttributeLLList *)dst_ptr;
	Gitsn_NodeAttributeLL *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_NodeAttributeLL *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, *node)).code) ERR_OUT(errp);
	else
	{
		// var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_NodeAttributeLLList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_NodeAttributeLLList *list = (Gitsn_NodeAttributeLLList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_NodeAttributeLLList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_NodeAttributeLLList *list = (Gitsn_NodeAttributeLLList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_NodeAttributeLLList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SegmentAttributeLL
static bool_t Gitsn_SegmentAttributeLL_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_SegmentAttributeLL v = Gitsn_SegmentAttributeLL_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_SegmentAttributeLL)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_SegmentAttributeLLFromStr(tok->v)) == Gitsn_SegmentAttributeLL_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_SegmentAttributeLL_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_SegmentAttributeLL_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_SegmentAttributeLL v = *(Gitsn_SegmentAttributeLL *)obj;
		Dz1Str str_v = Gitsn_SegmentAttributeLLStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_SegmentAttributeLL
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SegmentAttributeLLList
static bool_t Gitsn_SegmentAttributeLLList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_SegmentAttributeLLList *dst = (Gitsn_SegmentAttributeLLList *)dst_ptr;
	Gitsn_SegmentAttributeLL *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_SegmentAttributeLL *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, *node)).code) ERR_OUT(errp);
	else
	{
		// var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_SegmentAttributeLLList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_SegmentAttributeLLList *list = (Gitsn_SegmentAttributeLLList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_SegmentAttributeLLList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_SegmentAttributeLLList *list = (Gitsn_SegmentAttributeLLList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_SegmentAttributeLLList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeAttributeSetLL
static bool_t Gitsn_NodeAttributeSetLL_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_NodeAttributeSetLL *p = (Gitsn_NodeAttributeSetLL *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Gitsn_NodeAttributeLLList_delAndSetNull(&p->localNode); p->localNode = (Gitsn_NodeAttributeLLList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: Gitsn_SegmentAttributeLLList_delAndSetNull(&p->disabled); p->disabled = (Gitsn_SegmentAttributeLLList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: Gitsn_SegmentAttributeLLList_delAndSetNull(&p->enabled); p->enabled = (Gitsn_SegmentAttributeLLList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: Gitsn_LaneDataAttributeList_delAndSetNull(&p->data); p->data = (Gitsn_LaneDataAttributeList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 4: p->dWidth =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->dElevation =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_NodeAttributeSetLL_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_NodeAttributeSetLL *p = (Gitsn_NodeAttributeSetLL *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->localNode;
	case 1: return p->disabled;
	case 2: return p->enabled;
	case 3: return p->data;
	case 4: return &p->dWidth;
	case 5: return &p->dElevation;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_NodeAttributeSetLL_membs[] =
{
	{ Dz1Text("localNode"), Dz1Text("Gitsn_NodeAttributeLLList"), 0 },
	{ Dz1Text("disabled"), Dz1Text("Gitsn_SegmentAttributeLLList"), 1 },
	{ Dz1Text("enabled"), Dz1Text("Gitsn_SegmentAttributeLLList"), 2 },
	{ Dz1Text("data"), Dz1Text("Gitsn_LaneDataAttributeList"), 3 },
	{ Dz1Text("dWidth"), Dz1Text("s64_t"), 4 },
	{ Dz1Text("dElevation"), Dz1Text("s64_t"), 5 },
	{ NULL, NULL, -1 }
};
// Gitsn_NodeAttributeSetLL
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeLL
static bool_t Gitsn_NodeLL_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_NodeLL *p = (Gitsn_NodeLL *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Gitsn_NodeOffsetPointLL_delAndSetNull(&p->delta); p->delta = (Gitsn_NodeOffsetPointLL *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: Gitsn_NodeAttributeSetLL_delAndSetNull(&p->attributes); p->attributes = (Gitsn_NodeAttributeSetLL *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_NodeLL_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_NodeLL *p = (Gitsn_NodeLL *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->delta;
	case 1: return p->attributes;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_NodeLL_membs[] =
{
	{ Dz1Text("delta"), Dz1Text("Gitsn_NodeOffsetPointLL"), 0 },
	{ Dz1Text("attributes"), Dz1Text("Gitsn_NodeAttributeSetLL"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_NodeLL
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeSetLL
static bool_t Gitsn_NodeSetLL_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_NodeSetLL *dst = (Gitsn_NodeSetLL *)dst_ptr;
	Gitsn_NodeLL *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_NodeLL *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_NodeSetLL_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_NodeSetLL *list = (Gitsn_NodeSetLL *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_NodeSetLL_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_NodeSetLL *list = (Gitsn_NodeSetLL *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_NodeSetLL
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_NodeListLL
static bool_t Gitsn_NodeListLL_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_NodeListLL *p = (Gitsn_NodeListLL *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_NodeListLLPresent_nodes: Gitsn_NodeSetLL_delAndSetNull(&p->x.nodes); p->x.nodes =(Gitsn_NodeSetLL *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_NodeListLLPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_NodeListLL_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_NodeListLL *p = (Gitsn_NodeListLL *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_NodeListLLPresent_nodes: return p->x.nodes;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_NodeListLL_membs[] =
{
	{ Dz1Text("nodes"), Dz1Text("Gitsn_NodeSetLL"), Gitsn_NodeListLLPresent_nodes },
	{ NULL, NULL, -1 }
};
// Gitsn_NodeListLL
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_OffsetSystem_offset
static bool_t Gitsn_OffsetSystem_offset_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_OffsetSystem_offset *p = (Gitsn_OffsetSystem_offset *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_OffsetSystem_offsetPresent_xy: Gitsn_NodeListXY_delAndSetNull(&p->x.xy); p->x.xy =(Gitsn_NodeListXY *)info->data; info->data = NULL; break;
	case Gitsn_OffsetSystem_offsetPresent_ll: Gitsn_NodeListLL_delAndSetNull(&p->x.ll); p->x.ll =(Gitsn_NodeListLL *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_OffsetSystem_offsetPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_OffsetSystem_offset_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_OffsetSystem_offset *p = (Gitsn_OffsetSystem_offset *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_OffsetSystem_offsetPresent_xy: return p->x.xy;
		case Gitsn_OffsetSystem_offsetPresent_ll: return p->x.ll;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_OffsetSystem_offset_membs[] =
{
	{ Dz1Text("xy"), Dz1Text("Gitsn_NodeListXY"), Gitsn_OffsetSystem_offsetPresent_xy },
	{ Dz1Text("ll"), Dz1Text("Gitsn_NodeListLL"), Gitsn_OffsetSystem_offsetPresent_ll },
	{ NULL, NULL, -1 }
};
// Gitsn_OffsetSystem_offset
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_OffsetSystem
static bool_t Gitsn_OffsetSystem_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_OffsetSystem *p = (Gitsn_OffsetSystem *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->scale =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: Gitsn_OffsetSystem_offset_delAndSetNull(&p->offset); p->offset = (Gitsn_OffsetSystem_offset *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_OffsetSystem_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_OffsetSystem *p = (Gitsn_OffsetSystem *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->scale;
	case 1: return p->offset;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_OffsetSystem_membs[] =
{
	{ Dz1Text("scale"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("offset"), Dz1Text("Gitsn_OffsetSystem_offset"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_OffsetSystem
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DistanceUnits
static bool_t Gitsn_DistanceUnits_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_DistanceUnits v = Gitsn_DistanceUnits_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_DistanceUnits)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_DistanceUnitsFromStr(tok->v)) == Gitsn_DistanceUnits_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_DistanceUnits_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_DistanceUnits_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_DistanceUnits v = *(Gitsn_DistanceUnits *)obj;
		Dz1Str str_v = Gitsn_DistanceUnitsStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_DistanceUnits
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Circle
static bool_t Gitsn_Circle_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Circle *p = (Gitsn_Circle *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Gitsn_Position3D_delAndSetNull(&p->center); p->center = (Gitsn_Position3D *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: p->radius =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->units =  *(Gitsn_DistanceUnits *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Circle_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Circle *p = (Gitsn_Circle *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->center;
	case 1: return &p->radius;
	case 2: return &p->units;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Circle_membs[] =
{
	{ Dz1Text("center"), Dz1Text("Gitsn_Position3D"), 0 },
	{ Dz1Text("radius"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("units"), Dz1Text("Gitsn_DistanceUnits"), 2 },
	{ NULL, NULL, -1 }
};
// Gitsn_Circle
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_GeometricProjection
static bool_t Gitsn_GeometricProjection_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_GeometricProjection *p = (Gitsn_GeometricProjection *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: u8_t_delAndSetNull(&p->direction); p->direction = (u8_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: p->extent =  *(Gitsn_Extent *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->laneWidth =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: Gitsn_Circle_delAndSetNull(&p->circle); p->circle = (Gitsn_Circle *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_GeometricProjection_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_GeometricProjection *p = (Gitsn_GeometricProjection *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->direction;
	case 1: return &p->extent;
	case 2: return &p->laneWidth;
	case 3: return p->circle;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_GeometricProjection_membs[] =
{
	{ Dz1Text("direction"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("extent"), Dz1Text("Gitsn_Extent"), 1 },
	{ Dz1Text("laneWidth"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("circle"), Dz1Text("Gitsn_Circle"), 3 },
	{ NULL, NULL, -1 }
};
// Gitsn_GeometricProjection
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ShapePointSet
static bool_t Gitsn_ShapePointSet_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ShapePointSet *p = (Gitsn_ShapePointSet *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Gitsn_Position3D_delAndSetNull(&p->anchor); p->anchor = (Gitsn_Position3D *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: p->laneWidth =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->directionality =  *(Gitsn_DirectionOfUse *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: Gitsn_NodeListXY_delAndSetNull(&p->nodeList); p->nodeList = (Gitsn_NodeListXY *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_ShapePointSet_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_ShapePointSet *p = (Gitsn_ShapePointSet *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->anchor;
	case 1: return &p->laneWidth;
	case 2: return &p->directionality;
	case 3: return p->nodeList;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_ShapePointSet_membs[] =
{
	{ Dz1Text("anchor"), Dz1Text("Gitsn_Position3D"), 0 },
	{ Dz1Text("laneWidth"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("directionality"), Dz1Text("Gitsn_DirectionOfUse"), 2 },
	{ Dz1Text("nodeList"), Dz1Text("Gitsn_NodeListXY"), 3 },
	{ NULL, NULL, -1 }
};
// Gitsn_ShapePointSet
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RegionOffsets
static bool_t Gitsn_RegionOffsets_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_RegionOffsets *p = (Gitsn_RegionOffsets *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->xOffset =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->yOffset =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->zOffset =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_RegionOffsets_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_RegionOffsets *p = (Gitsn_RegionOffsets *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->xOffset;
	case 1: return &p->yOffset;
	case 2: return &p->zOffset;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_RegionOffsets_membs[] =
{
	{ Dz1Text("xOffset"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("yOffset"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("zOffset"), Dz1Text("s64_t"), 2 },
	{ NULL, NULL, -1 }
};
// Gitsn_RegionOffsets
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RegionList
static bool_t Gitsn_RegionList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_RegionList *dst = (Gitsn_RegionList *)dst_ptr;
	Gitsn_RegionOffsets *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_RegionOffsets *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_RegionList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_RegionList *list = (Gitsn_RegionList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_RegionList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_RegionList *list = (Gitsn_RegionList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_RegionList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RegionPointSet
static bool_t Gitsn_RegionPointSet_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_RegionPointSet *p = (Gitsn_RegionPointSet *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Gitsn_Position3D_delAndSetNull(&p->anchor); p->anchor = (Gitsn_Position3D *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: p->scale =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: Gitsn_RegionList_delAndSetNull(&p->nodeList); p->nodeList = (Gitsn_RegionList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_RegionPointSet_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_RegionPointSet *p = (Gitsn_RegionPointSet *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->anchor;
	case 1: return &p->scale;
	case 2: return p->nodeList;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_RegionPointSet_membs[] =
{
	{ Dz1Text("anchor"), Dz1Text("Gitsn_Position3D"), 0 },
	{ Dz1Text("scale"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("nodeList"), Dz1Text("Gitsn_RegionList"), 2 },
	{ NULL, NULL, -1 }
};
// Gitsn_RegionPointSet
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ValidRegion_area
static bool_t Gitsn_ValidRegion_area_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ValidRegion_area *p = (Gitsn_ValidRegion_area *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_ValidRegion_areaPresent_shapePointSet: Gitsn_ShapePointSet_delAndSetNull(&p->x.shapePointSet); p->x.shapePointSet =(Gitsn_ShapePointSet *)info->data; info->data = NULL; break;
	case Gitsn_ValidRegion_areaPresent_circle: Gitsn_Circle_delAndSetNull(&p->x.circle); p->x.circle =(Gitsn_Circle *)info->data; info->data = NULL; break;
	case Gitsn_ValidRegion_areaPresent_regionPointSet: Gitsn_RegionPointSet_delAndSetNull(&p->x.regionPointSet); p->x.regionPointSet =(Gitsn_RegionPointSet *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_ValidRegion_areaPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_ValidRegion_area_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_ValidRegion_area *p = (Gitsn_ValidRegion_area *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_ValidRegion_areaPresent_shapePointSet: return p->x.shapePointSet;
		case Gitsn_ValidRegion_areaPresent_circle: return p->x.circle;
		case Gitsn_ValidRegion_areaPresent_regionPointSet: return p->x.regionPointSet;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_ValidRegion_area_membs[] =
{
	{ Dz1Text("shapePointSet"), Dz1Text("Gitsn_ShapePointSet"), Gitsn_ValidRegion_areaPresent_shapePointSet },
	{ Dz1Text("circle"), Dz1Text("Gitsn_Circle"), Gitsn_ValidRegion_areaPresent_circle },
	{ Dz1Text("regionPointSet"), Dz1Text("Gitsn_RegionPointSet"), Gitsn_ValidRegion_areaPresent_regionPointSet },
	{ NULL, NULL, -1 }
};
// Gitsn_ValidRegion_area
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ValidRegion
static bool_t Gitsn_ValidRegion_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ValidRegion *p = (Gitsn_ValidRegion *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: u8_t_delAndSetNull(&p->direction); p->direction = (u8_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: p->extent =  *(Gitsn_Extent *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: Gitsn_ValidRegion_area_delAndSetNull(&p->area); p->area = (Gitsn_ValidRegion_area *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_ValidRegion_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_ValidRegion *p = (Gitsn_ValidRegion *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->direction;
	case 1: return &p->extent;
	case 2: return p->area;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_ValidRegion_membs[] =
{
	{ Dz1Text("direction"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("extent"), Dz1Text("Gitsn_Extent"), 1 },
	{ Dz1Text("area"), Dz1Text("Gitsn_ValidRegion_area"), 2 },
	{ NULL, NULL, -1 }
};
// Gitsn_ValidRegion
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_GeographicalPath_description
static bool_t Gitsn_GeographicalPath_description_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_GeographicalPath_description *p = (Gitsn_GeographicalPath_description *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_GeographicalPath_descriptionPresent_path: Gitsn_OffsetSystem_delAndSetNull(&p->x.path); p->x.path =(Gitsn_OffsetSystem *)info->data; info->data = NULL; break;
	case Gitsn_GeographicalPath_descriptionPresent_geometry: Gitsn_GeometricProjection_delAndSetNull(&p->x.geometry); p->x.geometry =(Gitsn_GeometricProjection *)info->data; info->data = NULL; break;
	case Gitsn_GeographicalPath_descriptionPresent_oldRegion: Gitsn_ValidRegion_delAndSetNull(&p->x.oldRegion); p->x.oldRegion =(Gitsn_ValidRegion *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_GeographicalPath_descriptionPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_GeographicalPath_description_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_GeographicalPath_description *p = (Gitsn_GeographicalPath_description *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_GeographicalPath_descriptionPresent_path: return p->x.path;
		case Gitsn_GeographicalPath_descriptionPresent_geometry: return p->x.geometry;
		case Gitsn_GeographicalPath_descriptionPresent_oldRegion: return p->x.oldRegion;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_GeographicalPath_description_membs[] =
{
	{ Dz1Text("path"), Dz1Text("Gitsn_OffsetSystem"), Gitsn_GeographicalPath_descriptionPresent_path },
	{ Dz1Text("geometry"), Dz1Text("Gitsn_GeometricProjection"), Gitsn_GeographicalPath_descriptionPresent_geometry },
	{ Dz1Text("oldRegion"), Dz1Text("Gitsn_ValidRegion"), Gitsn_GeographicalPath_descriptionPresent_oldRegion },
	{ NULL, NULL, -1 }
};
// Gitsn_GeographicalPath_description
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_GeographicalPath
static bool_t Gitsn_GeographicalPath_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_GeographicalPath *p = (Gitsn_GeographicalPath *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->name); p->name = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Gitsn_RoadSegmentReferenceID_delAndSetNull(&p->id); p->id = (Gitsn_RoadSegmentReferenceID *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: Gitsn_Position3D_delAndSetNull(&p->anchor); p->anchor = (Gitsn_Position3D *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: p->laneWidth =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->directionality =  *(Gitsn_DirectionOfUse *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->closedPath =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: u8_t_delAndSetNull(&p->direction); p->direction = (u8_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 7: Gitsn_GeographicalPath_description_delAndSetNull(&p->description); p->description = (Gitsn_GeographicalPath_description *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_GeographicalPath_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_GeographicalPath *p = (Gitsn_GeographicalPath *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->name;
	case 1: return p->id;
	case 2: return p->anchor;
	case 3: return &p->laneWidth;
	case 4: return &p->directionality;
	case 5: return &p->closedPath;
	case 6: return p->direction;
	case 7: return p->description;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_GeographicalPath_membs[] =
{
	{ Dz1Text("name"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("id"), Dz1Text("Gitsn_RoadSegmentReferenceID"), 1 },
	{ Dz1Text("anchor"), Dz1Text("Gitsn_Position3D"), 2 },
	{ Dz1Text("laneWidth"), Dz1Text("s64_t"), 3 },
	{ Dz1Text("directionality"), Dz1Text("Gitsn_DirectionOfUse"), 4 },
	{ Dz1Text("closedPath"), Dz1Text("bool_t"), 5 },
	{ Dz1Text("direction"), Dz1Text("u8_t"), 6 },
	{ Dz1Text("description"), Dz1Text("Gitsn_GeographicalPath_description"), 7 },
	{ NULL, NULL, -1 }
};
// Gitsn_GeographicalPath
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TravelerDataFrame_regions
static bool_t Gitsn_TravelerDataFrame_regions_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_TravelerDataFrame_regions *dst = (Gitsn_TravelerDataFrame_regions *)dst_ptr;
	Gitsn_GeographicalPath *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_GeographicalPath *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_TravelerDataFrame_regions_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_TravelerDataFrame_regions *list = (Gitsn_TravelerDataFrame_regions *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_TravelerDataFrame_regions_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_TravelerDataFrame_regions *list = (Gitsn_TravelerDataFrame_regions *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_TravelerDataFrame_regions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ITIScodesAndText_element_item
static bool_t Gitsn_ITIScodesAndText_element_item_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ITIScodesAndText_element_item *p = (Gitsn_ITIScodesAndText_element_item *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_ITIScodesAndText_element_itemPresent_itis: p->x.itis = *(s64_t *)info->data; break;
	case Gitsn_ITIScodesAndText_element_itemPresent_text: Dz1Str_delAndSetNull(&p->x.text); p->x.text =(Dz1Str)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_ITIScodesAndText_element_itemPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_ITIScodesAndText_element_item_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_ITIScodesAndText_element_item *p = (Gitsn_ITIScodesAndText_element_item *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_ITIScodesAndText_element_itemPresent_itis: return &p->x.itis;
		case Gitsn_ITIScodesAndText_element_itemPresent_text: return p->x.text;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_ITIScodesAndText_element_item_membs[] =
{
	{ Dz1Text("itis"), Dz1Text("s64_t"), Gitsn_ITIScodesAndText_element_itemPresent_itis },
	{ Dz1Text("text"), Dz1Text("Dz1Str"), Gitsn_ITIScodesAndText_element_itemPresent_text },
	{ NULL, NULL, -1 }
};
// Gitsn_ITIScodesAndText_element_item
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ITIScodesAndText_element
static bool_t Gitsn_ITIScodesAndText_element_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ITIScodesAndText_element *p = (Gitsn_ITIScodesAndText_element *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Gitsn_ITIScodesAndText_element_item_delAndSetNull(&p->item); p->item = (Gitsn_ITIScodesAndText_element_item *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_ITIScodesAndText_element_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_ITIScodesAndText_element *p = (Gitsn_ITIScodesAndText_element *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->item;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_ITIScodesAndText_element_membs[] =
{
	{ Dz1Text("item"), Dz1Text("Gitsn_ITIScodesAndText_element_item"), 0 },
	{ NULL, NULL, -1 }
};
// Gitsn_ITIScodesAndText_element
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ITIScodesAndText
static bool_t Gitsn_ITIScodesAndText_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ITIScodesAndText *dst = (Gitsn_ITIScodesAndText *)dst_ptr;
	Gitsn_ITIScodesAndText_element *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_ITIScodesAndText_element *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_ITIScodesAndText_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_ITIScodesAndText *list = (Gitsn_ITIScodesAndText *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_ITIScodesAndText_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_ITIScodesAndText *list = (Gitsn_ITIScodesAndText *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_ITIScodesAndText
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_WorkZone_element_item
static bool_t Gitsn_WorkZone_element_item_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_WorkZone_element_item *p = (Gitsn_WorkZone_element_item *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_WorkZone_element_itemPresent_itis: p->x.itis = *(s64_t *)info->data; break;
	case Gitsn_WorkZone_element_itemPresent_text: Dz1Str_delAndSetNull(&p->x.text); p->x.text =(Dz1Str)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_WorkZone_element_itemPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_WorkZone_element_item_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_WorkZone_element_item *p = (Gitsn_WorkZone_element_item *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_WorkZone_element_itemPresent_itis: return &p->x.itis;
		case Gitsn_WorkZone_element_itemPresent_text: return p->x.text;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_WorkZone_element_item_membs[] =
{
	{ Dz1Text("itis"), Dz1Text("s64_t"), Gitsn_WorkZone_element_itemPresent_itis },
	{ Dz1Text("text"), Dz1Text("Dz1Str"), Gitsn_WorkZone_element_itemPresent_text },
	{ NULL, NULL, -1 }
};
// Gitsn_WorkZone_element_item
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_WorkZone_element
static bool_t Gitsn_WorkZone_element_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_WorkZone_element *p = (Gitsn_WorkZone_element *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Gitsn_WorkZone_element_item_delAndSetNull(&p->item); p->item = (Gitsn_WorkZone_element_item *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_WorkZone_element_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_WorkZone_element *p = (Gitsn_WorkZone_element *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->item;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_WorkZone_element_membs[] =
{
	{ Dz1Text("item"), Dz1Text("Gitsn_WorkZone_element_item"), 0 },
	{ NULL, NULL, -1 }
};
// Gitsn_WorkZone_element
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_WorkZone
static bool_t Gitsn_WorkZone_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_WorkZone *dst = (Gitsn_WorkZone *)dst_ptr;
	Gitsn_WorkZone_element *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_WorkZone_element *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_WorkZone_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_WorkZone *list = (Gitsn_WorkZone *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_WorkZone_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_WorkZone *list = (Gitsn_WorkZone *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_WorkZone
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_GenericSignage_element_item
static bool_t Gitsn_GenericSignage_element_item_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_GenericSignage_element_item *p = (Gitsn_GenericSignage_element_item *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_GenericSignage_element_itemPresent_itis: p->x.itis = *(s64_t *)info->data; break;
	case Gitsn_GenericSignage_element_itemPresent_text: Dz1Str_delAndSetNull(&p->x.text); p->x.text =(Dz1Str)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_GenericSignage_element_itemPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_GenericSignage_element_item_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_GenericSignage_element_item *p = (Gitsn_GenericSignage_element_item *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_GenericSignage_element_itemPresent_itis: return &p->x.itis;
		case Gitsn_GenericSignage_element_itemPresent_text: return p->x.text;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_GenericSignage_element_item_membs[] =
{
	{ Dz1Text("itis"), Dz1Text("s64_t"), Gitsn_GenericSignage_element_itemPresent_itis },
	{ Dz1Text("text"), Dz1Text("Dz1Str"), Gitsn_GenericSignage_element_itemPresent_text },
	{ NULL, NULL, -1 }
};
// Gitsn_GenericSignage_element_item
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_GenericSignage_element
static bool_t Gitsn_GenericSignage_element_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_GenericSignage_element *p = (Gitsn_GenericSignage_element *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Gitsn_GenericSignage_element_item_delAndSetNull(&p->item); p->item = (Gitsn_GenericSignage_element_item *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_GenericSignage_element_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_GenericSignage_element *p = (Gitsn_GenericSignage_element *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->item;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_GenericSignage_element_membs[] =
{
	{ Dz1Text("item"), Dz1Text("Gitsn_GenericSignage_element_item"), 0 },
	{ NULL, NULL, -1 }
};
// Gitsn_GenericSignage_element
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_GenericSignage
static bool_t Gitsn_GenericSignage_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_GenericSignage *dst = (Gitsn_GenericSignage *)dst_ptr;
	Gitsn_GenericSignage_element *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_GenericSignage_element *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_GenericSignage_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_GenericSignage *list = (Gitsn_GenericSignage *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_GenericSignage_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_GenericSignage *list = (Gitsn_GenericSignage *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_GenericSignage
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SpeedLimit_element_item
static bool_t Gitsn_SpeedLimit_element_item_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_SpeedLimit_element_item *p = (Gitsn_SpeedLimit_element_item *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_SpeedLimit_element_itemPresent_itis: p->x.itis = *(s64_t *)info->data; break;
	case Gitsn_SpeedLimit_element_itemPresent_text: Dz1Str_delAndSetNull(&p->x.text); p->x.text =(Dz1Str)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_SpeedLimit_element_itemPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_SpeedLimit_element_item_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_SpeedLimit_element_item *p = (Gitsn_SpeedLimit_element_item *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_SpeedLimit_element_itemPresent_itis: return &p->x.itis;
		case Gitsn_SpeedLimit_element_itemPresent_text: return p->x.text;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_SpeedLimit_element_item_membs[] =
{
	{ Dz1Text("itis"), Dz1Text("s64_t"), Gitsn_SpeedLimit_element_itemPresent_itis },
	{ Dz1Text("text"), Dz1Text("Dz1Str"), Gitsn_SpeedLimit_element_itemPresent_text },
	{ NULL, NULL, -1 }
};
// Gitsn_SpeedLimit_element_item
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SpeedLimit_element
static bool_t Gitsn_SpeedLimit_element_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_SpeedLimit_element *p = (Gitsn_SpeedLimit_element *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Gitsn_SpeedLimit_element_item_delAndSetNull(&p->item); p->item = (Gitsn_SpeedLimit_element_item *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_SpeedLimit_element_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_SpeedLimit_element *p = (Gitsn_SpeedLimit_element *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->item;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_SpeedLimit_element_membs[] =
{
	{ Dz1Text("item"), Dz1Text("Gitsn_SpeedLimit_element_item"), 0 },
	{ NULL, NULL, -1 }
};
// Gitsn_SpeedLimit_element
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SpeedLimit
static bool_t Gitsn_SpeedLimit_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_SpeedLimit *dst = (Gitsn_SpeedLimit *)dst_ptr;
	Gitsn_SpeedLimit_element *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_SpeedLimit_element *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_SpeedLimit_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_SpeedLimit *list = (Gitsn_SpeedLimit *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_SpeedLimit_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_SpeedLimit *list = (Gitsn_SpeedLimit *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_SpeedLimit
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ExitService_element_item
static bool_t Gitsn_ExitService_element_item_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ExitService_element_item *p = (Gitsn_ExitService_element_item *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_ExitService_element_itemPresent_itis: p->x.itis = *(s64_t *)info->data; break;
	case Gitsn_ExitService_element_itemPresent_text: Dz1Str_delAndSetNull(&p->x.text); p->x.text =(Dz1Str)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_ExitService_element_itemPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_ExitService_element_item_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_ExitService_element_item *p = (Gitsn_ExitService_element_item *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_ExitService_element_itemPresent_itis: return &p->x.itis;
		case Gitsn_ExitService_element_itemPresent_text: return p->x.text;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_ExitService_element_item_membs[] =
{
	{ Dz1Text("itis"), Dz1Text("s64_t"), Gitsn_ExitService_element_itemPresent_itis },
	{ Dz1Text("text"), Dz1Text("Dz1Str"), Gitsn_ExitService_element_itemPresent_text },
	{ NULL, NULL, -1 }
};
// Gitsn_ExitService_element_item
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ExitService_element
static bool_t Gitsn_ExitService_element_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ExitService_element *p = (Gitsn_ExitService_element *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Gitsn_ExitService_element_item_delAndSetNull(&p->item); p->item = (Gitsn_ExitService_element_item *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_ExitService_element_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_ExitService_element *p = (Gitsn_ExitService_element *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->item;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_ExitService_element_membs[] =
{
	{ Dz1Text("item"), Dz1Text("Gitsn_ExitService_element_item"), 0 },
	{ NULL, NULL, -1 }
};
// Gitsn_ExitService_element
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ExitService
static bool_t Gitsn_ExitService_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ExitService *dst = (Gitsn_ExitService *)dst_ptr;
	Gitsn_ExitService_element *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_ExitService_element *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_ExitService_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_ExitService *list = (Gitsn_ExitService *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_ExitService_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_ExitService *list = (Gitsn_ExitService *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_ExitService
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TravelerDataFrame_content
static bool_t Gitsn_TravelerDataFrame_content_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_TravelerDataFrame_content *p = (Gitsn_TravelerDataFrame_content *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_TravelerDataFrame_contentPresent_advisory: Gitsn_ITIScodesAndText_delAndSetNull(&p->x.advisory); p->x.advisory =(Gitsn_ITIScodesAndText *)info->data; info->data = NULL; break;
	case Gitsn_TravelerDataFrame_contentPresent_workZone: Gitsn_WorkZone_delAndSetNull(&p->x.workZone); p->x.workZone =(Gitsn_WorkZone *)info->data; info->data = NULL; break;
	case Gitsn_TravelerDataFrame_contentPresent_genericSign: Gitsn_GenericSignage_delAndSetNull(&p->x.genericSign); p->x.genericSign =(Gitsn_GenericSignage *)info->data; info->data = NULL; break;
	case Gitsn_TravelerDataFrame_contentPresent_speedLimit: Gitsn_SpeedLimit_delAndSetNull(&p->x.speedLimit); p->x.speedLimit =(Gitsn_SpeedLimit *)info->data; info->data = NULL; break;
	case Gitsn_TravelerDataFrame_contentPresent_exitService: Gitsn_ExitService_delAndSetNull(&p->x.exitService); p->x.exitService =(Gitsn_ExitService *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_TravelerDataFrame_contentPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_TravelerDataFrame_content_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_TravelerDataFrame_content *p = (Gitsn_TravelerDataFrame_content *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_TravelerDataFrame_contentPresent_advisory: return p->x.advisory;
		case Gitsn_TravelerDataFrame_contentPresent_workZone: return p->x.workZone;
		case Gitsn_TravelerDataFrame_contentPresent_genericSign: return p->x.genericSign;
		case Gitsn_TravelerDataFrame_contentPresent_speedLimit: return p->x.speedLimit;
		case Gitsn_TravelerDataFrame_contentPresent_exitService: return p->x.exitService;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_TravelerDataFrame_content_membs[] =
{
	{ Dz1Text("advisory"), Dz1Text("Gitsn_ITIScodesAndText"), Gitsn_TravelerDataFrame_contentPresent_advisory },
	{ Dz1Text("workZone"), Dz1Text("Gitsn_WorkZone"), Gitsn_TravelerDataFrame_contentPresent_workZone },
	{ Dz1Text("genericSign"), Dz1Text("Gitsn_GenericSignage"), Gitsn_TravelerDataFrame_contentPresent_genericSign },
	{ Dz1Text("speedLimit"), Dz1Text("Gitsn_SpeedLimit"), Gitsn_TravelerDataFrame_contentPresent_speedLimit },
	{ Dz1Text("exitService"), Dz1Text("Gitsn_ExitService"), Gitsn_TravelerDataFrame_contentPresent_exitService },
	{ NULL, NULL, -1 }
};
// Gitsn_TravelerDataFrame_content
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TravelerDataFrame
static bool_t Gitsn_TravelerDataFrame_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_TravelerDataFrame *p = (Gitsn_TravelerDataFrame *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->notUsed =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->frameType =  *(Gitsn_TravelerInfoType *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: Gitsn_TravelerDataFrame_msgId_delAndSetNull(&p->msgId); p->msgId = (Gitsn_TravelerDataFrame_msgId *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: p->startYear =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->startTime =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->durationTime =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->priority =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->notUsed1 =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: Gitsn_TravelerDataFrame_regions_delAndSetNull(&p->regions); p->regions = (Gitsn_TravelerDataFrame_regions *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 9: p->notUsed2 =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 10: p->notUsed3 =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 11: Gitsn_TravelerDataFrame_content_delAndSetNull(&p->content); p->content = (Gitsn_TravelerDataFrame_content *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 12: Dz1Str_delAndSetNull(&p->url); p->url = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_TravelerDataFrame_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_TravelerDataFrame *p = (Gitsn_TravelerDataFrame *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->notUsed;
	case 1: return &p->frameType;
	case 2: return p->msgId;
	case 3: return &p->startYear;
	case 4: return &p->startTime;
	case 5: return &p->durationTime;
	case 6: return &p->priority;
	case 7: return &p->notUsed1;
	case 8: return p->regions;
	case 9: return &p->notUsed2;
	case 10: return &p->notUsed3;
	case 11: return p->content;
	case 12: return p->url;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_TravelerDataFrame_membs[] =
{
	{ Dz1Text("notUsed"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("frameType"), Dz1Text("Gitsn_TravelerInfoType"), 1 },
	{ Dz1Text("msgId"), Dz1Text("Gitsn_TravelerDataFrame_msgId"), 2 },
	{ Dz1Text("startYear"), Dz1Text("s64_t"), 3 },
	{ Dz1Text("startTime"), Dz1Text("s64_t"), 4 },
	{ Dz1Text("durationTime"), Dz1Text("s64_t"), 5 },
	{ Dz1Text("priority"), Dz1Text("s64_t"), 6 },
	{ Dz1Text("notUsed1"), Dz1Text("s64_t"), 7 },
	{ Dz1Text("regions"), Dz1Text("Gitsn_TravelerDataFrame_regions"), 8 },
	{ Dz1Text("notUsed2"), Dz1Text("s64_t"), 9 },
	{ Dz1Text("notUsed3"), Dz1Text("s64_t"), 10 },
	{ Dz1Text("content"), Dz1Text("Gitsn_TravelerDataFrame_content"), 11 },
	{ Dz1Text("url"), Dz1Text("Dz1Str"), 12 },
	{ NULL, NULL, -1 }
};
// Gitsn_TravelerDataFrame
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TravelerDataFrameList
static bool_t Gitsn_TravelerDataFrameList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_TravelerDataFrameList *dst = (Gitsn_TravelerDataFrameList *)dst_ptr;
	Gitsn_TravelerDataFrame *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_TravelerDataFrame *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_TravelerDataFrameList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_TravelerDataFrameList *list = (Gitsn_TravelerDataFrameList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_TravelerDataFrameList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_TravelerDataFrameList *list = (Gitsn_TravelerDataFrameList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_TravelerDataFrameList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TravelerInformation
static bool_t Gitsn_TravelerInformation_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_TravelerInformation *p = (Gitsn_TravelerInformation *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->msgCnt =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->timeStamp =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->packetID); p->packetID = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 3: Dz1Str_delAndSetNull(&p->urlB); p->urlB = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 4: Gitsn_TravelerDataFrameList_delAndSetNull(&p->dataFrames); p->dataFrames = (Gitsn_TravelerDataFrameList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_TravelerInformation_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_TravelerInformation *p = (Gitsn_TravelerInformation *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->msgCnt;
	case 1: return &p->timeStamp;
	case 2: return p->packetID;
	case 3: return p->urlB;
	case 4: return p->dataFrames;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_TravelerInformation_membs[] =
{
	{ Dz1Text("msgCnt"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("timeStamp"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("packetID"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("urlB"), Dz1Text("Dz1Str"), 3 },
	{ Dz1Text("dataFrames"), Dz1Text("Gitsn_TravelerDataFrameList"), 4 },
	{ NULL, NULL, -1 }
};
// Gitsn_TravelerInformation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_EquipmentType
static bool_t Gitsn_EquipmentType_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_EquipmentType v = Gitsn_EquipmentType_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_EquipmentType)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_EquipmentTypeFromStr(tok->v)) == Gitsn_EquipmentType_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_EquipmentType_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_EquipmentType_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_EquipmentType v = *(Gitsn_EquipmentType *)obj;
		Dz1Str str_v = Gitsn_EquipmentTypeStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_EquipmentType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ObjectType
static bool_t Gitsn_ObjectType_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ObjectType v = Gitsn_ObjectType_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_ObjectType)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_ObjectTypeFromStr(tok->v)) == Gitsn_ObjectType_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_ObjectType_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_ObjectType_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_ObjectType v = *(Gitsn_ObjectType *)obj;
		Dz1Str str_v = Gitsn_ObjectTypeStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_ObjectType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PositionOffsetXYZ
static bool_t Gitsn_PositionOffsetXYZ_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_PositionOffsetXYZ *p = (Gitsn_PositionOffsetXYZ *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->offsetX =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->offsetY =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->offsetZ =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_PositionOffsetXYZ_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_PositionOffsetXYZ *p = (Gitsn_PositionOffsetXYZ *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->offsetX;
	case 1: return &p->offsetY;
	case 2: return &p->offsetZ;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_PositionOffsetXYZ_membs[] =
{
	{ Dz1Text("offsetX"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("offsetY"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("offsetZ"), Dz1Text("s64_t"), 2 },
	{ NULL, NULL, -1 }
};
// Gitsn_PositionOffsetXYZ
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DetectedObjectCommonData
static bool_t Gitsn_DetectedObjectCommonData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_DetectedObjectCommonData *p = (Gitsn_DetectedObjectCommonData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->objType =  *(Gitsn_ObjectType *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->objTypeCfd =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->objectID =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->measurementTime =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->timeConfidence =  *(Gitsn_TimeConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: Gitsn_PositionOffsetXYZ_delAndSetNull(&p->pos); p->pos = (Gitsn_PositionOffsetXYZ *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 6: Gitsn_PositionConfidenceSet_delAndSetNull(&p->posConfidence); p->posConfidence = (Gitsn_PositionConfidenceSet *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 7: p->speed =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->speedConfidence =  *(Gitsn_SpeedConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 9: p->speedZ =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 10: p->speedConfidenceZ =  *(Gitsn_SpeedConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 11: p->heading =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 12: p->headingConf =  *(Gitsn_HeadingConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 13: Gitsn_AccelerationSet4Way_delAndSetNull(&p->accel4way); p->accel4way = (Gitsn_AccelerationSet4Way *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 14: p->accCfdX =  *(Gitsn_AccelerationConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 15: p->accCfdY =  *(Gitsn_AccelerationConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 16: p->accCfdZ =  *(Gitsn_AccelerationConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 17: p->accCfdYaw =  *(Gitsn_YawRateConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_DetectedObjectCommonData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_DetectedObjectCommonData *p = (Gitsn_DetectedObjectCommonData *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->objType;
	case 1: return &p->objTypeCfd;
	case 2: return &p->objectID;
	case 3: return &p->measurementTime;
	case 4: return &p->timeConfidence;
	case 5: return p->pos;
	case 6: return p->posConfidence;
	case 7: return &p->speed;
	case 8: return &p->speedConfidence;
	case 9: return &p->speedZ;
	case 10: return &p->speedConfidenceZ;
	case 11: return &p->heading;
	case 12: return &p->headingConf;
	case 13: return p->accel4way;
	case 14: return &p->accCfdX;
	case 15: return &p->accCfdY;
	case 16: return &p->accCfdZ;
	case 17: return &p->accCfdYaw;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_DetectedObjectCommonData_membs[] =
{
	{ Dz1Text("objType"), Dz1Text("Gitsn_ObjectType"), 0 },
	{ Dz1Text("objTypeCfd"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("objectID"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("measurementTime"), Dz1Text("s64_t"), 3 },
	{ Dz1Text("timeConfidence"), Dz1Text("Gitsn_TimeConfidence"), 4 },
	{ Dz1Text("pos"), Dz1Text("Gitsn_PositionOffsetXYZ"), 5 },
	{ Dz1Text("posConfidence"), Dz1Text("Gitsn_PositionConfidenceSet"), 6 },
	{ Dz1Text("speed"), Dz1Text("s64_t"), 7 },
	{ Dz1Text("speedConfidence"), Dz1Text("Gitsn_SpeedConfidence"), 8 },
	{ Dz1Text("speedZ"), Dz1Text("s64_t"), 9 },
	{ Dz1Text("speedConfidenceZ"), Dz1Text("Gitsn_SpeedConfidence"), 10 },
	{ Dz1Text("heading"), Dz1Text("s64_t"), 11 },
	{ Dz1Text("headingConf"), Dz1Text("Gitsn_HeadingConfidence"), 12 },
	{ Dz1Text("accel4way"), Dz1Text("Gitsn_AccelerationSet4Way"), 13 },
	{ Dz1Text("accCfdX"), Dz1Text("Gitsn_AccelerationConfidence"), 14 },
	{ Dz1Text("accCfdY"), Dz1Text("Gitsn_AccelerationConfidence"), 15 },
	{ Dz1Text("accCfdZ"), Dz1Text("Gitsn_AccelerationConfidence"), 16 },
	{ Dz1Text("accCfdYaw"), Dz1Text("Gitsn_YawRateConfidence"), 17 },
	{ NULL, NULL, -1 }
};
// Gitsn_DetectedObjectCommonData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Attitude
static bool_t Gitsn_Attitude_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Attitude *p = (Gitsn_Attitude *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->pitch =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->roll =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->yaw =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Attitude_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Attitude *p = (Gitsn_Attitude *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->pitch;
	case 1: return &p->roll;
	case 2: return &p->yaw;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Attitude_membs[] =
{
	{ Dz1Text("pitch"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("roll"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("yaw"), Dz1Text("s64_t"), 2 },
	{ NULL, NULL, -1 }
};
// Gitsn_Attitude
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AttitudeConfidence
static bool_t Gitsn_AttitudeConfidence_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_AttitudeConfidence *p = (Gitsn_AttitudeConfidence *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->pitchConfidence =  *(Gitsn_HeadingConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->rollConfidence =  *(Gitsn_HeadingConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->yawConfidence =  *(Gitsn_HeadingConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_AttitudeConfidence_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_AttitudeConfidence *p = (Gitsn_AttitudeConfidence *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->pitchConfidence;
	case 1: return &p->rollConfidence;
	case 2: return &p->yawConfidence;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_AttitudeConfidence_membs[] =
{
	{ Dz1Text("pitchConfidence"), Dz1Text("Gitsn_HeadingConfidence"), 0 },
	{ Dz1Text("rollConfidence"), Dz1Text("Gitsn_HeadingConfidence"), 1 },
	{ Dz1Text("yawConfidence"), Dz1Text("Gitsn_HeadingConfidence"), 2 },
	{ NULL, NULL, -1 }
};
// Gitsn_AttitudeConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AngularVelocity
static bool_t Gitsn_AngularVelocity_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_AngularVelocity *p = (Gitsn_AngularVelocity *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->pitchRate =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->rollRate =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_AngularVelocity_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_AngularVelocity *p = (Gitsn_AngularVelocity *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->pitchRate;
	case 1: return &p->rollRate;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_AngularVelocity_membs[] =
{
	{ Dz1Text("pitchRate"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("rollRate"), Dz1Text("s64_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_AngularVelocity
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PitchRateConfidence
static bool_t Gitsn_PitchRateConfidence_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_PitchRateConfidence v = Gitsn_PitchRateConfidence_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_PitchRateConfidence)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_PitchRateConfidenceFromStr(tok->v)) == Gitsn_PitchRateConfidence_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_PitchRateConfidence_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_PitchRateConfidence_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_PitchRateConfidence v = *(Gitsn_PitchRateConfidence *)obj;
		Dz1Str str_v = Gitsn_PitchRateConfidenceStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_PitchRateConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_RollRateConfidence
static bool_t Gitsn_RollRateConfidence_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_RollRateConfidence v = Gitsn_RollRateConfidence_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_RollRateConfidence)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_RollRateConfidenceFromStr(tok->v)) == Gitsn_RollRateConfidence_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_RollRateConfidence_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_RollRateConfidence_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_RollRateConfidence v = *(Gitsn_RollRateConfidence *)obj;
		Dz1Str str_v = Gitsn_RollRateConfidenceStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_RollRateConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AngularVelocityConfidence
static bool_t Gitsn_AngularVelocityConfidence_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_AngularVelocityConfidence *p = (Gitsn_AngularVelocityConfidence *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->pitchRateConfidence =  *(Gitsn_PitchRateConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->rollRateConfidence =  *(Gitsn_RollRateConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_AngularVelocityConfidence_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_AngularVelocityConfidence *p = (Gitsn_AngularVelocityConfidence *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->pitchRateConfidence;
	case 1: return &p->rollRateConfidence;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_AngularVelocityConfidence_membs[] =
{
	{ Dz1Text("pitchRateConfidence"), Dz1Text("Gitsn_PitchRateConfidence"), 0 },
	{ Dz1Text("rollRateConfidence"), Dz1Text("Gitsn_RollRateConfidence"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_AngularVelocityConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SizeValueConfidence
static bool_t Gitsn_SizeValueConfidence_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_SizeValueConfidence v = Gitsn_SizeValueConfidence_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_SizeValueConfidence)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_SizeValueConfidenceFromStr(tok->v)) == Gitsn_SizeValueConfidence_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_SizeValueConfidence_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_SizeValueConfidence_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_SizeValueConfidence v = *(Gitsn_SizeValueConfidence *)obj;
		Dz1Str str_v = Gitsn_SizeValueConfidenceStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_SizeValueConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_VehicleSizeConfidence
static bool_t Gitsn_VehicleSizeConfidence_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_VehicleSizeConfidence *p = (Gitsn_VehicleSizeConfidence *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->vehicleWidthConfidence =  *(Gitsn_SizeValueConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->vehicleLengthConfidence =  *(Gitsn_SizeValueConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->vehicleHeightConfidence =  *(Gitsn_SizeValueConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_VehicleSizeConfidence_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_VehicleSizeConfidence *p = (Gitsn_VehicleSizeConfidence *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->vehicleWidthConfidence;
	case 1: return &p->vehicleLengthConfidence;
	case 2: return &p->vehicleHeightConfidence;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_VehicleSizeConfidence_membs[] =
{
	{ Dz1Text("vehicleWidthConfidence"), Dz1Text("Gitsn_SizeValueConfidence"), 0 },
	{ Dz1Text("vehicleLengthConfidence"), Dz1Text("Gitsn_SizeValueConfidence"), 1 },
	{ Dz1Text("vehicleHeightConfidence"), Dz1Text("Gitsn_SizeValueConfidence"), 2 },
	{ NULL, NULL, -1 }
};
// Gitsn_VehicleSizeConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DetectedVehicleData
static bool_t Gitsn_DetectedVehicleData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_DetectedVehicleData *p = (Gitsn_DetectedVehicleData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: u8_t_delAndSetNull(&p->lights); p->lights = (u8_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: Gitsn_Attitude_delAndSetNull(&p->vehAttitude); p->vehAttitude = (Gitsn_Attitude *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: Gitsn_AttitudeConfidence_delAndSetNull(&p->vehAttitudeConfidence); p->vehAttitudeConfidence = (Gitsn_AttitudeConfidence *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: Gitsn_AngularVelocity_delAndSetNull(&p->vehAngVel); p->vehAngVel = (Gitsn_AngularVelocity *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 4: Gitsn_AngularVelocityConfidence_delAndSetNull(&p->vehAngleConfidence); p->vehAngleConfidence = (Gitsn_AngularVelocityConfidence *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 5: Gitsn_VehicleSize_delAndSetNull(&p->size); p->size = (Gitsn_VehicleSize *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 6: p->height =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: Gitsn_VehicleSizeConfidence_delAndSetNull(&p->vehicleSizeConfidence); p->vehicleSizeConfidence = (Gitsn_VehicleSizeConfidence *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 8: p->vehicleClass =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 9: p->classConf =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_DetectedVehicleData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_DetectedVehicleData *p = (Gitsn_DetectedVehicleData *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->lights;
	case 1: return p->vehAttitude;
	case 2: return p->vehAttitudeConfidence;
	case 3: return p->vehAngVel;
	case 4: return p->vehAngleConfidence;
	case 5: return p->size;
	case 6: return &p->height;
	case 7: return p->vehicleSizeConfidence;
	case 8: return &p->vehicleClass;
	case 9: return &p->classConf;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_DetectedVehicleData_membs[] =
{
	{ Dz1Text("lights"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("vehAttitude"), Dz1Text("Gitsn_Attitude"), 1 },
	{ Dz1Text("vehAttitudeConfidence"), Dz1Text("Gitsn_AttitudeConfidence"), 2 },
	{ Dz1Text("vehAngVel"), Dz1Text("Gitsn_AngularVelocity"), 3 },
	{ Dz1Text("vehAngleConfidence"), Dz1Text("Gitsn_AngularVelocityConfidence"), 4 },
	{ Dz1Text("size"), Dz1Text("Gitsn_VehicleSize"), 5 },
	{ Dz1Text("height"), Dz1Text("s64_t"), 6 },
	{ Dz1Text("vehicleSizeConfidence"), Dz1Text("Gitsn_VehicleSizeConfidence"), 7 },
	{ Dz1Text("vehicleClass"), Dz1Text("s64_t"), 8 },
	{ Dz1Text("classConf"), Dz1Text("s64_t"), 9 },
	{ NULL, NULL, -1 }
};
// Gitsn_DetectedVehicleData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PersonalDeviceUserType
static bool_t Gitsn_PersonalDeviceUserType_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_PersonalDeviceUserType v = Gitsn_PersonalDeviceUserType_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_PersonalDeviceUserType)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_PersonalDeviceUserTypeFromStr(tok->v)) == Gitsn_PersonalDeviceUserType_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_PersonalDeviceUserType_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_PersonalDeviceUserType_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_PersonalDeviceUserType v = *(Gitsn_PersonalDeviceUserType *)obj;
		Dz1Str str_v = Gitsn_PersonalDeviceUserTypeStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_PersonalDeviceUserType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_HumanPropelledType
static bool_t Gitsn_HumanPropelledType_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_HumanPropelledType v = Gitsn_HumanPropelledType_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_HumanPropelledType)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_HumanPropelledTypeFromStr(tok->v)) == Gitsn_HumanPropelledType_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_HumanPropelledType_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_HumanPropelledType_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_HumanPropelledType v = *(Gitsn_HumanPropelledType *)obj;
		Dz1Str str_v = Gitsn_HumanPropelledTypeStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_HumanPropelledType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_AnimalPropelledType
static bool_t Gitsn_AnimalPropelledType_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_AnimalPropelledType v = Gitsn_AnimalPropelledType_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_AnimalPropelledType)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_AnimalPropelledTypeFromStr(tok->v)) == Gitsn_AnimalPropelledType_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_AnimalPropelledType_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_AnimalPropelledType_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_AnimalPropelledType v = *(Gitsn_AnimalPropelledType *)obj;
		Dz1Str str_v = Gitsn_AnimalPropelledTypeStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_AnimalPropelledType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_MotorizedPropelledType
static bool_t Gitsn_MotorizedPropelledType_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_MotorizedPropelledType v = Gitsn_MotorizedPropelledType_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_MotorizedPropelledType)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_MotorizedPropelledTypeFromStr(tok->v)) == Gitsn_MotorizedPropelledType_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_MotorizedPropelledType_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_MotorizedPropelledType_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_MotorizedPropelledType v = *(Gitsn_MotorizedPropelledType *)obj;
		Dz1Str str_v = Gitsn_MotorizedPropelledTypeStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_MotorizedPropelledType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PropelledInformation
static bool_t Gitsn_PropelledInformation_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_PropelledInformation *p = (Gitsn_PropelledInformation *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_PropelledInformationPresent_human: p->x.human = *(Gitsn_HumanPropelledType *)info->data; break;
	case Gitsn_PropelledInformationPresent_animal: p->x.animal = *(Gitsn_AnimalPropelledType *)info->data; break;
	case Gitsn_PropelledInformationPresent_motor: p->x.motor = *(Gitsn_MotorizedPropelledType *)info->data; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_PropelledInformationPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_PropelledInformation_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_PropelledInformation *p = (Gitsn_PropelledInformation *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_PropelledInformationPresent_human: return &p->x.human;
		case Gitsn_PropelledInformationPresent_animal: return &p->x.animal;
		case Gitsn_PropelledInformationPresent_motor: return &p->x.motor;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_PropelledInformation_membs[] =
{
	{ Dz1Text("human"), Dz1Text("Gitsn_HumanPropelledType"), Gitsn_PropelledInformationPresent_human },
	{ Dz1Text("animal"), Dz1Text("Gitsn_AnimalPropelledType"), Gitsn_PropelledInformationPresent_animal },
	{ Dz1Text("motor"), Dz1Text("Gitsn_MotorizedPropelledType"), Gitsn_PropelledInformationPresent_motor },
	{ NULL, NULL, -1 }
};
// Gitsn_PropelledInformation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Attachment
static bool_t Gitsn_Attachment_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Attachment v = Gitsn_Attachment_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_Attachment)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_AttachmentFromStr(tok->v)) == Gitsn_Attachment_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_Attachment_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_Attachment_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_Attachment v = *(Gitsn_Attachment *)obj;
		Dz1Str str_v = Gitsn_AttachmentStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_Attachment
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DetectedVRUData
static bool_t Gitsn_DetectedVRUData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_DetectedVRUData *p = (Gitsn_DetectedVRUData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->basicType =  *(Gitsn_PersonalDeviceUserType *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: Gitsn_PropelledInformation_delAndSetNull(&p->propulsion); p->propulsion = (Gitsn_PropelledInformation *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: p->attachment =  *(Gitsn_Attachment *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->radius =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_DetectedVRUData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_DetectedVRUData *p = (Gitsn_DetectedVRUData *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->basicType;
	case 1: return p->propulsion;
	case 2: return &p->attachment;
	case 3: return &p->radius;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_DetectedVRUData_membs[] =
{
	{ Dz1Text("basicType"), Dz1Text("Gitsn_PersonalDeviceUserType"), 0 },
	{ Dz1Text("propulsion"), Dz1Text("Gitsn_PropelledInformation"), 1 },
	{ Dz1Text("attachment"), Dz1Text("Gitsn_Attachment"), 2 },
	{ Dz1Text("radius"), Dz1Text("s64_t"), 3 },
	{ NULL, NULL, -1 }
};
// Gitsn_DetectedVRUData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ObstacleSize
static bool_t Gitsn_ObstacleSize_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ObstacleSize *p = (Gitsn_ObstacleSize *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->width =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->length =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->height =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_ObstacleSize_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_ObstacleSize *p = (Gitsn_ObstacleSize *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->width;
	case 1: return &p->length;
	case 2: return &p->height;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_ObstacleSize_membs[] =
{
	{ Dz1Text("width"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("length"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("height"), Dz1Text("s64_t"), 2 },
	{ NULL, NULL, -1 }
};
// Gitsn_ObstacleSize
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ObstacleSizeConfidence
static bool_t Gitsn_ObstacleSizeConfidence_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ObstacleSizeConfidence *p = (Gitsn_ObstacleSizeConfidence *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->widthConfidence =  *(Gitsn_SizeValueConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->lengthConfidence =  *(Gitsn_SizeValueConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->heightConfidence =  *(Gitsn_SizeValueConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_ObstacleSizeConfidence_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_ObstacleSizeConfidence *p = (Gitsn_ObstacleSizeConfidence *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->widthConfidence;
	case 1: return &p->lengthConfidence;
	case 2: return &p->heightConfidence;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_ObstacleSizeConfidence_membs[] =
{
	{ Dz1Text("widthConfidence"), Dz1Text("Gitsn_SizeValueConfidence"), 0 },
	{ Dz1Text("lengthConfidence"), Dz1Text("Gitsn_SizeValueConfidence"), 1 },
	{ Dz1Text("heightConfidence"), Dz1Text("Gitsn_SizeValueConfidence"), 2 },
	{ NULL, NULL, -1 }
};
// Gitsn_ObstacleSizeConfidence
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DetectedObstacleData
static bool_t Gitsn_DetectedObstacleData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_DetectedObstacleData *p = (Gitsn_DetectedObstacleData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Gitsn_ObstacleSize_delAndSetNull(&p->obstSize); p->obstSize = (Gitsn_ObstacleSize *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: Gitsn_ObstacleSizeConfidence_delAndSetNull(&p->obstSizeConfidence); p->obstSizeConfidence = (Gitsn_ObstacleSizeConfidence *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_DetectedObstacleData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_DetectedObstacleData *p = (Gitsn_DetectedObstacleData *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->obstSize;
	case 1: return p->obstSizeConfidence;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_DetectedObstacleData_membs[] =
{
	{ Dz1Text("obstSize"), Dz1Text("Gitsn_ObstacleSize"), 0 },
	{ Dz1Text("obstSizeConfidence"), Dz1Text("Gitsn_ObstacleSizeConfidence"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_DetectedObstacleData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DetectedObjectOptionalData
static bool_t Gitsn_DetectedObjectOptionalData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_DetectedObjectOptionalData *p = (Gitsn_DetectedObjectOptionalData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_DetectedObjectOptionalDataPresent_detVeh: Gitsn_DetectedVehicleData_delAndSetNull(&p->x.detVeh); p->x.detVeh =(Gitsn_DetectedVehicleData *)info->data; info->data = NULL; break;
	case Gitsn_DetectedObjectOptionalDataPresent_detVRU: Gitsn_DetectedVRUData_delAndSetNull(&p->x.detVRU); p->x.detVRU =(Gitsn_DetectedVRUData *)info->data; info->data = NULL; break;
	case Gitsn_DetectedObjectOptionalDataPresent_detObst: Gitsn_DetectedObstacleData_delAndSetNull(&p->x.detObst); p->x.detObst =(Gitsn_DetectedObstacleData *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_DetectedObjectOptionalDataPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_DetectedObjectOptionalData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_DetectedObjectOptionalData *p = (Gitsn_DetectedObjectOptionalData *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_DetectedObjectOptionalDataPresent_detVeh: return p->x.detVeh;
		case Gitsn_DetectedObjectOptionalDataPresent_detVRU: return p->x.detVRU;
		case Gitsn_DetectedObjectOptionalDataPresent_detObst: return p->x.detObst;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_DetectedObjectOptionalData_membs[] =
{
	{ Dz1Text("detVeh"), Dz1Text("Gitsn_DetectedVehicleData"), Gitsn_DetectedObjectOptionalDataPresent_detVeh },
	{ Dz1Text("detVRU"), Dz1Text("Gitsn_DetectedVRUData"), Gitsn_DetectedObjectOptionalDataPresent_detVRU },
	{ Dz1Text("detObst"), Dz1Text("Gitsn_DetectedObstacleData"), Gitsn_DetectedObjectOptionalDataPresent_detObst },
	{ NULL, NULL, -1 }
};
// Gitsn_DetectedObjectOptionalData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DetectedObjectData
static bool_t Gitsn_DetectedObjectData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_DetectedObjectData *p = (Gitsn_DetectedObjectData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Gitsn_DetectedObjectCommonData_delAndSetNull(&p->detObjCommon); p->detObjCommon = (Gitsn_DetectedObjectCommonData *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: Gitsn_DetectedObjectOptionalData_delAndSetNull(&p->detObjOptData); p->detObjOptData = (Gitsn_DetectedObjectOptionalData *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_DetectedObjectData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_DetectedObjectData *p = (Gitsn_DetectedObjectData *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->detObjCommon;
	case 1: return p->detObjOptData;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_DetectedObjectData_membs[] =
{
	{ Dz1Text("detObjCommon"), Dz1Text("Gitsn_DetectedObjectCommonData"), 0 },
	{ Dz1Text("detObjOptData"), Dz1Text("Gitsn_DetectedObjectOptionalData"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_DetectedObjectData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_DetectedObjectList
static bool_t Gitsn_DetectedObjectList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_DetectedObjectList *dst = (Gitsn_DetectedObjectList *)dst_ptr;
	Gitsn_DetectedObjectData *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_DetectedObjectData *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_DetectedObjectList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_DetectedObjectList *list = (Gitsn_DetectedObjectList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_DetectedObjectList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_DetectedObjectList *list = (Gitsn_DetectedObjectList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_DetectedObjectList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_SensorDataSharingMessage
static bool_t Gitsn_SensorDataSharingMessage_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_SensorDataSharingMessage *p = (Gitsn_SensorDataSharingMessage *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->msgCnt =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->sourceID); p->sourceID = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: p->equipmentType =  *(Gitsn_EquipmentType *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: Gitsn_DDateTime_delAndSetNull(&p->sDSMTimeStamp); p->sDSMTimeStamp = (Gitsn_DDateTime *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 4: Gitsn_Position3D_delAndSetNull(&p->refPos); p->refPos = (Gitsn_Position3D *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 5: Gitsn_PositionalAccuracy_delAndSetNull(&p->refPosXYConf); p->refPosXYConf = (Gitsn_PositionalAccuracy *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 6: p->refPosElConf =  *(Gitsn_ElevationConfidence *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: Gitsn_DetectedObjectList_delAndSetNull(&p->objects); p->objects = (Gitsn_DetectedObjectList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_SensorDataSharingMessage_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_SensorDataSharingMessage *p = (Gitsn_SensorDataSharingMessage *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->msgCnt;
	case 1: return p->sourceID;
	case 2: return &p->equipmentType;
	case 3: return p->sDSMTimeStamp;
	case 4: return p->refPos;
	case 5: return p->refPosXYConf;
	case 6: return &p->refPosElConf;
	case 7: return p->objects;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_SensorDataSharingMessage_membs[] =
{
	{ Dz1Text("msgCnt"), Dz1Text("s64_t"), 0 },
	{ Dz1Text("sourceID"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("equipmentType"), Dz1Text("Gitsn_EquipmentType"), 2 },
	{ Dz1Text("sDSMTimeStamp"), Dz1Text("Gitsn_DDateTime"), 3 },
	{ Dz1Text("refPos"), Dz1Text("Gitsn_Position3D"), 4 },
	{ Dz1Text("refPosXYConf"), Dz1Text("Gitsn_PositionalAccuracy"), 5 },
	{ Dz1Text("refPosElConf"), Dz1Text("Gitsn_ElevationConfidence"), 6 },
	{ Dz1Text("objects"), Dz1Text("Gitsn_DetectedObjectList"), 7 },
	{ NULL, NULL, -1 }
};
// Gitsn_SensorDataSharingMessage
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_OBJECTIDENTIFIER
static bool_t Gitsn_OBJECTIDENTIFIER_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_OBJECTIDENTIFIER *p = (Gitsn_OBJECTIDENTIFIER *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->numids =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: u32_t_delAndSetNull(&p->subid); p->subid = (u32_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_OBJECTIDENTIFIER_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_OBJECTIDENTIFIER *p = (Gitsn_OBJECTIDENTIFIER *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->numids;
	case 1: return p->subid;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_OBJECTIDENTIFIER_membs[] =
{
	{ Dz1Text("numids"), Dz1Text("u32_t"), 0 },
	{ Dz1Text("subid"), Dz1Text("u32_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_OBJECTIDENTIFIER
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TrafficLightID
static bool_t Gitsn_TrafficLightID_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_TrafficLightID *p = (Gitsn_TrafficLightID *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_TrafficLightIDPresent_id: p->x.id = *(s64_t *)info->data; break;
	case Gitsn_TrafficLightIDPresent_oid: Gitsn_OBJECTIDENTIFIER_delAndSetNull(&p->x.oid); p->x.oid =(Gitsn_OBJECTIDENTIFIER *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_TrafficLightIDPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_TrafficLightID_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_TrafficLightID *p = (Gitsn_TrafficLightID *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_TrafficLightIDPresent_id: return &p->x.id;
		case Gitsn_TrafficLightIDPresent_oid: return p->x.oid;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_TrafficLightID_membs[] =
{
	{ Dz1Text("id"), Dz1Text("s64_t"), Gitsn_TrafficLightIDPresent_id },
	{ Dz1Text("oid"), Dz1Text("Gitsn_OBJECTIDENTIFIER"), Gitsn_TrafficLightIDPresent_oid },
	{ NULL, NULL, -1 }
};
// Gitsn_TrafficLightID
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TrafficLightType
static bool_t Gitsn_TrafficLightType_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_TrafficLightType v = Gitsn_TrafficLightType_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_TrafficLightType)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_TrafficLightTypeFromStr(tok->v)) == Gitsn_TrafficLightType_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_TrafficLightType_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_TrafficLightType_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_TrafficLightType v = *(Gitsn_TrafficLightType *)obj;
		Dz1Str str_v = Gitsn_TrafficLightTypeStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_TrafficLightType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_ConsecutiveTrafficLight
static bool_t Gitsn_ConsecutiveTrafficLight_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_ConsecutiveTrafficLight v = Gitsn_ConsecutiveTrafficLight_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_ConsecutiveTrafficLight)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_ConsecutiveTrafficLightFromStr(tok->v)) == Gitsn_ConsecutiveTrafficLight_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_ConsecutiveTrafficLight_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_ConsecutiveTrafficLight_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_ConsecutiveTrafficLight v = *(Gitsn_ConsecutiveTrafficLight *)obj;
		Dz1Str str_v = Gitsn_ConsecutiveTrafficLightStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_ConsecutiveTrafficLight
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TrafficLightIntervalType
static bool_t Gitsn_TrafficLightIntervalType_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_TrafficLightIntervalType v = Gitsn_TrafficLightIntervalType_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_TrafficLightIntervalType)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_TrafficLightIntervalTypeFromStr(tok->v)) == Gitsn_TrafficLightIntervalType_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_TrafficLightIntervalType_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_TrafficLightIntervalType_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_TrafficLightIntervalType v = *(Gitsn_TrafficLightIntervalType *)obj;
		Dz1Str str_v = Gitsn_TrafficLightIntervalTypeStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_TrafficLightIntervalType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_PermissiveNonProtected
static bool_t Gitsn_PermissiveNonProtected_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_PermissiveNonProtected v = Gitsn_PermissiveNonProtected_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_PermissiveNonProtected)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_PermissiveNonProtectedFromStr(tok->v)) == Gitsn_PermissiveNonProtected_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_PermissiveNonProtected_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_PermissiveNonProtected_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_PermissiveNonProtected v = *(Gitsn_PermissiveNonProtected *)obj;
		Dz1Str str_v = Gitsn_PermissiveNonProtectedStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_PermissiveNonProtected
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TrafficLightingStatus
static bool_t Gitsn_TrafficLightingStatus_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_TrafficLightingStatus v = Gitsn_TrafficLightingStatus_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_TrafficLightingStatus)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_TrafficLightingStatusFromStr(tok->v)) == Gitsn_TrafficLightingStatus_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_TrafficLightingStatus_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_TrafficLightingStatus_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_TrafficLightingStatus v = *(Gitsn_TrafficLightingStatus *)obj;
		Dz1Str str_v = Gitsn_TrafficLightingStatusStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_TrafficLightingStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TrafficLightStatus
static bool_t Gitsn_TrafficLightStatus_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_TrafficLightStatus *p = (Gitsn_TrafficLightStatus *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->trafficLightType =  *(Gitsn_TrafficLightType *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->consecutiveTrafficLight =  *(Gitsn_ConsecutiveTrafficLight *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->trafficLightIntervalType =  *(Gitsn_TrafficLightIntervalType *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->pedestrianCall =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->actuatedinterval =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->permissiveNonProtected =  *(Gitsn_PermissiveNonProtected *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->lightingStatus =  *(Gitsn_TrafficLightingStatus *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->maxIntervalLength =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->remainingTime =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 9: p->directionCode =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 10: p->reserved =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_TrafficLightStatus_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_TrafficLightStatus *p = (Gitsn_TrafficLightStatus *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->trafficLightType;
	case 1: return &p->consecutiveTrafficLight;
	case 2: return &p->trafficLightIntervalType;
	case 3: return &p->pedestrianCall;
	case 4: return &p->actuatedinterval;
	case 5: return &p->permissiveNonProtected;
	case 6: return &p->lightingStatus;
	case 7: return &p->maxIntervalLength;
	case 8: return &p->remainingTime;
	case 9: return &p->directionCode;
	case 10: return &p->reserved;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_TrafficLightStatus_membs[] =
{
	{ Dz1Text("trafficLightType"), Dz1Text("Gitsn_TrafficLightType"), 0 },
	{ Dz1Text("consecutiveTrafficLight"), Dz1Text("Gitsn_ConsecutiveTrafficLight"), 1 },
	{ Dz1Text("trafficLightIntervalType"), Dz1Text("Gitsn_TrafficLightIntervalType"), 2 },
	{ Dz1Text("pedestrianCall"), Dz1Text("bool_t"), 3 },
	{ Dz1Text("actuatedinterval"), Dz1Text("bool_t"), 4 },
	{ Dz1Text("permissiveNonProtected"), Dz1Text("Gitsn_PermissiveNonProtected"), 5 },
	{ Dz1Text("lightingStatus"), Dz1Text("Gitsn_TrafficLightingStatus"), 6 },
	{ Dz1Text("maxIntervalLength"), Dz1Text("s64_t"), 7 },
	{ Dz1Text("remainingTime"), Dz1Text("s64_t"), 8 },
	{ Dz1Text("directionCode"), Dz1Text("s64_t"), 9 },
	{ Dz1Text("reserved"), Dz1Text("bool_t"), 10 },
	{ NULL, NULL, -1 }
};
// Gitsn_TrafficLightStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TrafficLightStatusList
static bool_t Gitsn_TrafficLightStatusList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_TrafficLightStatusList *dst = (Gitsn_TrafficLightStatusList *)dst_ptr;
	Gitsn_TrafficLightStatus *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_TrafficLightStatus *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_TrafficLightStatusList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_TrafficLightStatusList *list = (Gitsn_TrafficLightStatusList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_TrafficLightStatusList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_TrafficLightStatusList *list = (Gitsn_TrafficLightStatusList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_TrafficLightStatusList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_TLS
static bool_t Gitsn_TLS_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_TLS *p = (Gitsn_TLS *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Gitsn_TrafficLightID_delAndSetNull(&p->trafficLightID); p->trafficLightID = (Gitsn_TrafficLightID *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: p->lat =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->lon =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: u8_t_delAndSetNull(&p->operationStatus); p->operationStatus = (u8_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 4: u8_t_delAndSetNull(&p->controllerStatus); p->controllerStatus = (u8_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 5: p->cyclecounter =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->cycletime =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: Gitsn_DDateTime_delAndSetNull(&p->currentTime); p->currentTime = (Gitsn_DDateTime *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 8: Gitsn_TrafficLightStatusList_delAndSetNull(&p->trafficLightStatus); p->trafficLightStatus = (Gitsn_TrafficLightStatusList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_TLS_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_TLS *p = (Gitsn_TLS *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->trafficLightID;
	case 1: return &p->lat;
	case 2: return &p->lon;
	case 3: return p->operationStatus;
	case 4: return p->controllerStatus;
	case 5: return &p->cyclecounter;
	case 6: return &p->cycletime;
	case 7: return p->currentTime;
	case 8: return p->trafficLightStatus;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_TLS_membs[] =
{
	{ Dz1Text("trafficLightID"), Dz1Text("Gitsn_TrafficLightID"), 0 },
	{ Dz1Text("lat"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("lon"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("operationStatus"), Dz1Text("u8_t"), 3 },
	{ Dz1Text("controllerStatus"), Dz1Text("u8_t"), 4 },
	{ Dz1Text("cyclecounter"), Dz1Text("s64_t"), 5 },
	{ Dz1Text("cycletime"), Dz1Text("s64_t"), 6 },
	{ Dz1Text("currentTime"), Dz1Text("Gitsn_DDateTime"), 7 },
	{ Dz1Text("trafficLightStatus"), Dz1Text("Gitsn_TrafficLightStatusList"), 8 },
	{ NULL, NULL, -1 }
};
// Gitsn_TLS
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Cost
static bool_t Gitsn_Iso14827Cost_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827Cost *p = (Gitsn_Iso14827Cost *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->currency); p->currency = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->factor =  *(s32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->qty =  *(s32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827Cost_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827Cost *p = (Gitsn_Iso14827Cost *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->currency;
	case 1: return &p->factor;
	case 2: return &p->qty;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Iso14827Cost_membs[] =
{
	{ Dz1Text("currency"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("factor"), Dz1Text("s32_t"), 1 },
	{ Dz1Text("qty"), Dz1Text("s32_t"), 2 },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827Cost
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827TimeFrac
static bool_t Gitsn_Iso14827TimeFrac_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827TimeFrac *p = (Gitsn_Iso14827TimeFrac *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_Iso14827TimeFracPresent_deci: p->x.deci = *(s32_t *)info->data; break;
	case Gitsn_Iso14827TimeFracPresent_centi: p->x.centi = *(s32_t *)info->data; break;
	case Gitsn_Iso14827TimeFracPresent_milli: p->x.milli = *(s32_t *)info->data; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_Iso14827TimeFracPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827TimeFrac_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827TimeFrac *p = (Gitsn_Iso14827TimeFrac *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_Iso14827TimeFracPresent_deci: return &p->x.deci;
		case Gitsn_Iso14827TimeFracPresent_centi: return &p->x.centi;
		case Gitsn_Iso14827TimeFracPresent_milli: return &p->x.milli;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_Iso14827TimeFrac_membs[] =
{
	{ Dz1Text("deci"), Dz1Text("s32_t"), Gitsn_Iso14827TimeFracPresent_deci },
	{ Dz1Text("centi"), Dz1Text("s32_t"), Gitsn_Iso14827TimeFracPresent_centi },
	{ Dz1Text("milli"), Dz1Text("s32_t"), Gitsn_Iso14827TimeFracPresent_milli },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827TimeFrac
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827TimeZone
static bool_t Gitsn_Iso14827TimeZone_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827TimeZone *p = (Gitsn_Iso14827TimeZone *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->modH =  *(s32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->modM =  *(s32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827TimeZone_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827TimeZone *p = (Gitsn_Iso14827TimeZone *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->modH;
	case 1: return &p->modM;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Iso14827TimeZone_membs[] =
{
	{ Dz1Text("modH"), Dz1Text("s32_t"), 0 },
	{ Dz1Text("modM"), Dz1Text("s32_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827TimeZone
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Time
static bool_t Gitsn_Iso14827Time_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827Time *p = (Gitsn_Iso14827Time *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: s32_t_delAndSetNull(&p->year); p->year = (s32_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: s32_t_delAndSetNull(&p->month); p->month = (s32_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: s32_t_delAndSetNull(&p->day); p->day = (s32_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: p->h =  *(s32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->m =  *(s32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->s =  *(s32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: Gitsn_Iso14827TimeFrac_delAndSetNull(&p->frac); p->frac = (Gitsn_Iso14827TimeFrac *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 7: Gitsn_Iso14827TimeZone_delAndSetNull(&p->zone); p->zone = (Gitsn_Iso14827TimeZone *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827Time_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827Time *p = (Gitsn_Iso14827Time *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->year;
	case 1: return p->month;
	case 2: return p->day;
	case 3: return &p->h;
	case 4: return &p->m;
	case 5: return &p->s;
	case 6: return p->frac;
	case 7: return p->zone;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Iso14827Time_membs[] =
{
	{ Dz1Text("year"), Dz1Text("s32_t"), 0 },
	{ Dz1Text("month"), Dz1Text("s32_t"), 1 },
	{ Dz1Text("day"), Dz1Text("s32_t"), 2 },
	{ Dz1Text("h"), Dz1Text("s32_t"), 3 },
	{ Dz1Text("m"), Dz1Text("s32_t"), 4 },
	{ Dz1Text("s"), Dz1Text("s32_t"), 5 },
	{ Dz1Text("frac"), Dz1Text("Gitsn_Iso14827TimeFrac"), 6 },
	{ Dz1Text("zone"), Dz1Text("Gitsn_Iso14827TimeZone"), 7 },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827Time
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827HdrOpt
static bool_t Gitsn_Iso14827HdrOpt_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827HdrOpt *p = (Gitsn_Iso14827HdrOpt *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->origin); p->origin = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->originAddr); p->originAddr = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->sender); p->sender = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 3: Dz1Str_delAndSetNull(&p->senderAddr); p->senderAddr = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 4: Dz1Str_delAndSetNull(&p->dest); p->dest = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 5: Dz1Str_delAndSetNull(&p->destAddr); p->destAddr = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 6: Gitsn_Iso14827Cost_delAndSetNull(&p->cost); p->cost = (Gitsn_Iso14827Cost *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 7: Gitsn_Iso14827Time_delAndSetNull(&p->t); p->t = (Gitsn_Iso14827Time *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827HdrOpt_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827HdrOpt *p = (Gitsn_Iso14827HdrOpt *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->origin;
	case 1: return p->originAddr;
	case 2: return p->sender;
	case 3: return p->senderAddr;
	case 4: return p->dest;
	case 5: return p->destAddr;
	case 6: return p->cost;
	case 7: return p->t;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Iso14827HdrOpt_membs[] =
{
	{ Dz1Text("origin"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("originAddr"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("sender"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("senderAddr"), Dz1Text("Dz1Str"), 3 },
	{ Dz1Text("dest"), Dz1Text("Dz1Str"), 4 },
	{ Dz1Text("destAddr"), Dz1Text("Dz1Str"), 5 },
	{ Dz1Text("cost"), Dz1Text("Gitsn_Iso14827Cost"), 6 },
	{ Dz1Text("t"), Dz1Text("Gitsn_Iso14827Time"), 7 },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827HdrOpt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Initiate
static bool_t Gitsn_Iso14827Initiate_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827Initiate *p = (Gitsn_Iso14827Initiate *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->sender); p->sender = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->dest); p->dest = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827Initiate_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827Initiate *p = (Gitsn_Iso14827Initiate *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->sender;
	case 1: return p->dest;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Iso14827Initiate_membs[] =
{
	{ Dz1Text("sender"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("dest"), Dz1Text("Dz1Str"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827Initiate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Dz1OIDList
static bool_t Gitsn_Dz1OIDList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Dz1OIDList *dst = (Gitsn_Dz1OIDList *)dst_ptr;
	Dz1Str node = NULL;
	if (dst == NULL || var == NULL || (node = (Dz1Str )var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_Dz1OIDList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_Dz1OIDList *list = (Gitsn_Dz1OIDList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_Dz1OIDList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_Dz1OIDList *list = (Gitsn_Dz1OIDList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_Dz1OIDList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827LoginInitiator
static bool_t Gitsn_Iso14827LoginInitiator_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827LoginInitiator v = Gitsn_Iso14827LoginInitiator_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_Iso14827LoginInitiator)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_Iso14827LoginInitiatorFromStr(tok->v)) == Gitsn_Iso14827LoginInitiator_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_Iso14827LoginInitiator_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_Iso14827LoginInitiator_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_Iso14827LoginInitiator v = *(Gitsn_Iso14827LoginInitiator *)obj;
		Dz1Str str_v = Gitsn_Iso14827LoginInitiatorStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_Iso14827LoginInitiator
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Login
static bool_t Gitsn_Iso14827Login_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827Login *p = (Gitsn_Iso14827Login *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->sender); p->sender = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->dest); p->dest = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->user); p->user = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 3: Dz1Str_delAndSetNull(&p->pass); p->pass = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 4: Gitsn_Dz1OIDList_delAndSetNull(&p->encRules); p->encRules = (Gitsn_Dz1OIDList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 5: p->hbDur =  *(s32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->timeout =  *(s32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->initiator =  *(Gitsn_Iso14827LoginInitiator *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->datagramSize =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827Login_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827Login *p = (Gitsn_Iso14827Login *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->sender;
	case 1: return p->dest;
	case 2: return p->user;
	case 3: return p->pass;
	case 4: return p->encRules;
	case 5: return &p->hbDur;
	case 6: return &p->timeout;
	case 7: return &p->initiator;
	case 8: return &p->datagramSize;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Iso14827Login_membs[] =
{
	{ Dz1Text("sender"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("dest"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("user"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("pass"), Dz1Text("Dz1Str"), 3 },
	{ Dz1Text("encRules"), Dz1Text("Gitsn_Dz1OIDList"), 4 },
	{ Dz1Text("hbDur"), Dz1Text("s32_t"), 5 },
	{ Dz1Text("timeout"), Dz1Text("s32_t"), 6 },
	{ Dz1Text("initiator"), Dz1Text("Gitsn_Iso14827LoginInitiator"), 7 },
	{ Dz1Text("datagramSize"), Dz1Text("u16_t"), 8 },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827Login
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Terminate
static bool_t Gitsn_Iso14827Terminate_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827Terminate v = Gitsn_Iso14827Terminate_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_Iso14827Terminate)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_Iso14827TerminateFromStr(tok->v)) == Gitsn_Iso14827Terminate_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_Iso14827Terminate_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_Iso14827Terminate_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_Iso14827Terminate v = *(Gitsn_Iso14827Terminate *)obj;
		Dz1Str str_v = Gitsn_Iso14827TerminateStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_Iso14827Terminate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Logout
static bool_t Gitsn_Iso14827Logout_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827Logout v = Gitsn_Iso14827Logout_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_Iso14827Logout)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_Iso14827LogoutFromStr(tok->v)) == Gitsn_Iso14827Logout_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_Iso14827Logout_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_Iso14827Logout_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_Iso14827Logout v = *(Gitsn_Iso14827Logout *)obj;
		Dz1Str str_v = Gitsn_Iso14827LogoutStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_Iso14827Logout
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827SubscriptionDataStatus
static bool_t Gitsn_Iso14827SubscriptionDataStatus_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827SubscriptionDataStatus v = Gitsn_Iso14827SubscriptionDataStatus_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_Iso14827SubscriptionDataStatus)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_Iso14827SubscriptionDataStatusFromStr(tok->v)) == Gitsn_Iso14827SubscriptionDataStatus_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_Iso14827SubscriptionDataStatus_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_Iso14827SubscriptionDataStatus_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_Iso14827SubscriptionDataStatus v = *(Gitsn_Iso14827SubscriptionDataStatus *)obj;
		Dz1Str str_v = Gitsn_Iso14827SubscriptionDataStatusStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_Iso14827SubscriptionDataStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RegisteredContinuous
static bool_t Gitsn_Iso14827RegisteredContinuous_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827RegisteredContinuous *p = (Gitsn_Iso14827RegisteredContinuous *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->updateDelay =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: Gitsn_Iso14827Time_delAndSetNull(&p->start); p->start = (Gitsn_Iso14827Time *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: Gitsn_Iso14827Time_delAndSetNull(&p->end); p->end = (Gitsn_Iso14827Time *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827RegisteredContinuous_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827RegisteredContinuous *p = (Gitsn_Iso14827RegisteredContinuous *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->updateDelay;
	case 1: return p->start;
	case 2: return p->end;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Iso14827RegisteredContinuous_membs[] =
{
	{ Dz1Text("updateDelay"), Dz1Text("u32_t"), 0 },
	{ Dz1Text("start"), Dz1Text("Gitsn_Iso14827Time"), 1 },
	{ Dz1Text("end"), Dz1Text("Gitsn_Iso14827Time"), 2 },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827RegisteredContinuous
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RegisteredDaily
static bool_t Gitsn_Iso14827RegisteredDaily_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827RegisteredDaily *p = (Gitsn_Iso14827RegisteredDaily *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->updateDelay =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->daysOfWeek =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: Gitsn_Iso14827Time_delAndSetNull(&p->startDate); p->startDate = (Gitsn_Iso14827Time *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: Gitsn_Iso14827Time_delAndSetNull(&p->endDate); p->endDate = (Gitsn_Iso14827Time *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 4: Gitsn_Iso14827Time_delAndSetNull(&p->startTime); p->startTime = (Gitsn_Iso14827Time *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 5: u16_t_delAndSetNull(&p->duration); p->duration = (u16_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827RegisteredDaily_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827RegisteredDaily *p = (Gitsn_Iso14827RegisteredDaily *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->updateDelay;
	case 1: return &p->daysOfWeek;
	case 2: return p->startDate;
	case 3: return p->endDate;
	case 4: return p->startTime;
	case 5: return p->duration;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Iso14827RegisteredDaily_membs[] =
{
	{ Dz1Text("updateDelay"), Dz1Text("u32_t"), 0 },
	{ Dz1Text("daysOfWeek"), Dz1Text("u8_t"), 1 },
	{ Dz1Text("startDate"), Dz1Text("Gitsn_Iso14827Time"), 2 },
	{ Dz1Text("endDate"), Dz1Text("Gitsn_Iso14827Time"), 3 },
	{ Dz1Text("startTime"), Dz1Text("Gitsn_Iso14827Time"), 4 },
	{ Dz1Text("duration"), Dz1Text("u16_t"), 5 },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827RegisteredDaily
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Registered
static bool_t Gitsn_Iso14827Registered_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827Registered *p = (Gitsn_Iso14827Registered *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_Iso14827RegisteredPresent_continuous: Gitsn_Iso14827RegisteredContinuous_delAndSetNull(&p->x.continuous); p->x.continuous =(Gitsn_Iso14827RegisteredContinuous *)info->data; info->data = NULL; break;
	case Gitsn_Iso14827RegisteredPresent_daily: Gitsn_Iso14827RegisteredDaily_delAndSetNull(&p->x.daily); p->x.daily =(Gitsn_Iso14827RegisteredDaily *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_Iso14827RegisteredPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827Registered_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827Registered *p = (Gitsn_Iso14827Registered *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_Iso14827RegisteredPresent_continuous: return p->x.continuous;
		case Gitsn_Iso14827RegisteredPresent_daily: return p->x.daily;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_Iso14827Registered_membs[] =
{
	{ Dz1Text("continuous"), Dz1Text("Gitsn_Iso14827RegisteredContinuous"), Gitsn_Iso14827RegisteredPresent_continuous },
	{ Dz1Text("daily"), Dz1Text("Gitsn_Iso14827RegisteredDaily"), Gitsn_Iso14827RegisteredPresent_daily },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827Registered
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827SubscriptionDataMode
static bool_t Gitsn_Iso14827SubscriptionDataMode_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827SubscriptionDataMode *p = (Gitsn_Iso14827SubscriptionDataMode *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_Iso14827SubscriptionDataModePresent_single: s32_t_delAndSetNull(&p->x.single); p->x.single =(s32_t *)info->data; info->data = NULL; break;
	case Gitsn_Iso14827SubscriptionDataModePresent_eventDriven: Gitsn_Iso14827Registered_delAndSetNull(&p->x.eventDriven); p->x.eventDriven =(Gitsn_Iso14827Registered *)info->data; info->data = NULL; break;
	case Gitsn_Iso14827SubscriptionDataModePresent_periodic: Gitsn_Iso14827Registered_delAndSetNull(&p->x.periodic); p->x.periodic =(Gitsn_Iso14827Registered *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_Iso14827SubscriptionDataModePresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827SubscriptionDataMode_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827SubscriptionDataMode *p = (Gitsn_Iso14827SubscriptionDataMode *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_Iso14827SubscriptionDataModePresent_single: return p->x.single;
		case Gitsn_Iso14827SubscriptionDataModePresent_eventDriven: return p->x.eventDriven;
		case Gitsn_Iso14827SubscriptionDataModePresent_periodic: return p->x.periodic;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_Iso14827SubscriptionDataMode_membs[] =
{
	{ Dz1Text("single"), Dz1Text("s32_t"), Gitsn_Iso14827SubscriptionDataModePresent_single },
	{ Dz1Text("eventDriven"), Dz1Text("Gitsn_Iso14827Registered"), Gitsn_Iso14827SubscriptionDataModePresent_eventDriven },
	{ Dz1Text("periodic"), Dz1Text("Gitsn_Iso14827Registered"), Gitsn_Iso14827SubscriptionDataModePresent_periodic },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827SubscriptionDataMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827SubscriptionDataFormat
static bool_t Gitsn_Iso14827SubscriptionDataFormat_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827SubscriptionDataFormat v = Gitsn_Iso14827SubscriptionDataFormat_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_Iso14827SubscriptionDataFormat)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_Iso14827SubscriptionDataFormatFromStr(tok->v)) == Gitsn_Iso14827SubscriptionDataFormat_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_Iso14827SubscriptionDataFormat_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_Iso14827SubscriptionDataFormat_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_Iso14827SubscriptionDataFormat v = *(Gitsn_Iso14827SubscriptionDataFormat *)obj;
		Dz1Str str_v = Gitsn_Iso14827SubscriptionDataFormatStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_Iso14827SubscriptionDataFormat
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827EndAppMsg
static bool_t Gitsn_Iso14827EndAppMsg_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827EndAppMsg *p = (Gitsn_Iso14827EndAppMsg *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->oid); p->oid = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Binary_delAndSetNull(&p->data); p->data = (Dz1Binary *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827EndAppMsg_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827EndAppMsg *p = (Gitsn_Iso14827EndAppMsg *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->oid;
	case 1: return p->data;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Iso14827EndAppMsg_membs[] =
{
	{ Dz1Text("oid"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("data"), Dz1Text("Dz1Binary"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827EndAppMsg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827SubscriptionData
static bool_t Gitsn_Iso14827SubscriptionData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827SubscriptionData *p = (Gitsn_Iso14827SubscriptionData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->persistent =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->status =  *(Gitsn_Iso14827SubscriptionDataStatus *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: Gitsn_Iso14827SubscriptionDataMode_delAndSetNull(&p->mode); p->mode = (Gitsn_Iso14827SubscriptionDataMode *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: p->fmt =  *(Gitsn_Iso14827SubscriptionDataFormat *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->priority =  *(s32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->guarantee =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: Gitsn_Iso14827EndAppMsg_delAndSetNull(&p->msg); p->msg = (Gitsn_Iso14827EndAppMsg *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827SubscriptionData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827SubscriptionData *p = (Gitsn_Iso14827SubscriptionData *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->persistent;
	case 1: return &p->status;
	case 2: return p->mode;
	case 3: return &p->fmt;
	case 4: return &p->priority;
	case 5: return &p->guarantee;
	case 6: return p->msg;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Iso14827SubscriptionData_membs[] =
{
	{ Dz1Text("persistent"), Dz1Text("bool_t"), 0 },
	{ Dz1Text("status"), Dz1Text("Gitsn_Iso14827SubscriptionDataStatus"), 1 },
	{ Dz1Text("mode"), Dz1Text("Gitsn_Iso14827SubscriptionDataMode"), 2 },
	{ Dz1Text("fmt"), Dz1Text("Gitsn_Iso14827SubscriptionDataFormat"), 3 },
	{ Dz1Text("priority"), Dz1Text("s32_t"), 4 },
	{ Dz1Text("guarantee"), Dz1Text("bool_t"), 5 },
	{ Dz1Text("msg"), Dz1Text("Gitsn_Iso14827EndAppMsg"), 6 },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827SubscriptionData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827SubscriptionCancel
static bool_t Gitsn_Iso14827SubscriptionCancel_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827SubscriptionCancel v = Gitsn_Iso14827SubscriptionCancel_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_Iso14827SubscriptionCancel)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_Iso14827SubscriptionCancelFromStr(tok->v)) == Gitsn_Iso14827SubscriptionCancel_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_Iso14827SubscriptionCancel_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_Iso14827SubscriptionCancel_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_Iso14827SubscriptionCancel v = *(Gitsn_Iso14827SubscriptionCancel *)obj;
		Dz1Str str_v = Gitsn_Iso14827SubscriptionCancelStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_Iso14827SubscriptionCancel
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827SubscriptionType
static bool_t Gitsn_Iso14827SubscriptionType_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827SubscriptionType *p = (Gitsn_Iso14827SubscriptionType *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_Iso14827SubscriptionTypePresent_data: Gitsn_Iso14827SubscriptionData_delAndSetNull(&p->x.data); p->x.data =(Gitsn_Iso14827SubscriptionData *)info->data; info->data = NULL; break;
	case Gitsn_Iso14827SubscriptionTypePresent_reason: p->x.reason = *(Gitsn_Iso14827SubscriptionCancel *)info->data; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_Iso14827SubscriptionTypePresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827SubscriptionType_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827SubscriptionType *p = (Gitsn_Iso14827SubscriptionType *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_Iso14827SubscriptionTypePresent_data: return p->x.data;
		case Gitsn_Iso14827SubscriptionTypePresent_reason: return &p->x.reason;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_Iso14827SubscriptionType_membs[] =
{
	{ Dz1Text("data"), Dz1Text("Gitsn_Iso14827SubscriptionData"), Gitsn_Iso14827SubscriptionTypePresent_data },
	{ Dz1Text("reason"), Dz1Text("Gitsn_Iso14827SubscriptionCancel"), Gitsn_Iso14827SubscriptionTypePresent_reason },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827SubscriptionType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Subscription
static bool_t Gitsn_Iso14827Subscription_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827Subscription *p = (Gitsn_Iso14827Subscription *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->serial =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: Gitsn_Iso14827SubscriptionType_delAndSetNull(&p->type); p->type = (Gitsn_Iso14827SubscriptionType *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827Subscription_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827Subscription *p = (Gitsn_Iso14827Subscription *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->serial;
	case 1: return p->type;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Iso14827Subscription_membs[] =
{
	{ Dz1Text("serial"), Dz1Text("u32_t"), 0 },
	{ Dz1Text("type"), Dz1Text("Gitsn_Iso14827SubscriptionType"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827Subscription
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827PublicationMgmt
static bool_t Gitsn_Iso14827PublicationMgmt_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827PublicationMgmt v = Gitsn_Iso14827PublicationMgmt_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_Iso14827PublicationMgmt)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_Iso14827PublicationMgmtFromStr(tok->v)) == Gitsn_Iso14827PublicationMgmt_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_Iso14827PublicationMgmt_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_Iso14827PublicationMgmt_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_Iso14827PublicationMgmt v = *(Gitsn_Iso14827PublicationMgmt *)obj;
		Dz1Str str_v = Gitsn_Iso14827PublicationMgmtStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_Iso14827PublicationMgmt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827PublicationType
static bool_t Gitsn_Iso14827PublicationType_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827PublicationType *p = (Gitsn_Iso14827PublicationType *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_Iso14827PublicationTypePresent_mgmt: p->x.mgmt = *(Gitsn_Iso14827PublicationMgmt *)info->data; break;
	case Gitsn_Iso14827PublicationTypePresent_msg: Gitsn_Iso14827EndAppMsg_delAndSetNull(&p->x.msg); p->x.msg =(Gitsn_Iso14827EndAppMsg *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_Iso14827PublicationTypePresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827PublicationType_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827PublicationType *p = (Gitsn_Iso14827PublicationType *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_Iso14827PublicationTypePresent_mgmt: return &p->x.mgmt;
		case Gitsn_Iso14827PublicationTypePresent_msg: return p->x.msg;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_Iso14827PublicationType_membs[] =
{
	{ Dz1Text("mgmt"), Dz1Text("Gitsn_Iso14827PublicationMgmt"), Gitsn_Iso14827PublicationTypePresent_mgmt },
	{ Dz1Text("msg"), Dz1Text("Gitsn_Iso14827EndAppMsg"), Gitsn_Iso14827PublicationTypePresent_msg },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827PublicationType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827PublicationData
static bool_t Gitsn_Iso14827PublicationData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827PublicationData *p = (Gitsn_Iso14827PublicationData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->subscriptionSerial =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->serial =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->isLated =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: Gitsn_Iso14827PublicationType_delAndSetNull(&p->type); p->type = (Gitsn_Iso14827PublicationType *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827PublicationData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827PublicationData *p = (Gitsn_Iso14827PublicationData *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->subscriptionSerial;
	case 1: return &p->serial;
	case 2: return &p->isLated;
	case 3: return p->type;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Iso14827PublicationData_membs[] =
{
	{ Dz1Text("subscriptionSerial"), Dz1Text("u32_t"), 0 },
	{ Dz1Text("serial"), Dz1Text("u32_t"), 1 },
	{ Dz1Text("isLated"), Dz1Text("bool_t"), 2 },
	{ Dz1Text("type"), Dz1Text("Gitsn_Iso14827PublicationType"), 3 },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827PublicationData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827PublicationDataList
static bool_t Gitsn_Iso14827PublicationDataList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827PublicationDataList *dst = (Gitsn_Iso14827PublicationDataList *)dst_ptr;
	Gitsn_Iso14827PublicationData *node = NULL;
	if (dst == NULL || var == NULL || (node = (Gitsn_Iso14827PublicationData *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t Gitsn_Iso14827PublicationDataList_cnt(void *ptr)
{
	u32_t ret = 0;
	Gitsn_Iso14827PublicationDataList *list = (Gitsn_Iso14827PublicationDataList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error Gitsn_Iso14827PublicationDataList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Gitsn_Iso14827PublicationDataList *list = (Gitsn_Iso14827PublicationDataList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// Gitsn_Iso14827PublicationDataList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827PublishFormat
static bool_t Gitsn_Iso14827PublishFormat_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827PublishFormat *p = (Gitsn_Iso14827PublishFormat *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_Iso14827PublishFormatPresent_dataList: Gitsn_Iso14827PublicationDataList_delAndSetNull(&p->x.dataList); p->x.dataList =(Gitsn_Iso14827PublicationDataList *)info->data; info->data = NULL; break;
	case Gitsn_Iso14827PublishFormatPresent_filename: Dz1Str_delAndSetNull(&p->x.filename); p->x.filename =(Dz1Str)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_Iso14827PublishFormatPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827PublishFormat_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827PublishFormat *p = (Gitsn_Iso14827PublishFormat *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_Iso14827PublishFormatPresent_dataList: return p->x.dataList;
		case Gitsn_Iso14827PublishFormatPresent_filename: return p->x.filename;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_Iso14827PublishFormat_membs[] =
{
	{ Dz1Text("dataList"), Dz1Text("Gitsn_Iso14827PublicationDataList"), Gitsn_Iso14827PublishFormatPresent_dataList },
	{ Dz1Text("filename"), Dz1Text("Dz1Str"), Gitsn_Iso14827PublishFormatPresent_filename },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827PublishFormat
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Publication
static bool_t Gitsn_Iso14827Publication_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827Publication *p = (Gitsn_Iso14827Publication *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->guaranteed =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: Gitsn_Iso14827PublishFormat_delAndSetNull(&p->fmt); p->fmt = (Gitsn_Iso14827PublishFormat *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827Publication_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827Publication *p = (Gitsn_Iso14827Publication *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->guaranteed;
	case 1: return p->fmt;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Iso14827Publication_membs[] =
{
	{ Dz1Text("guaranteed"), Dz1Text("bool_t"), 0 },
	{ Dz1Text("fmt"), Dz1Text("Gitsn_Iso14827PublishFormat"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827Publication
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827TransferDone
static bool_t Gitsn_Iso14827TransferDone_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827TransferDone *p = (Gitsn_Iso14827TransferDone *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->filename); p->filename = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->isSuccess =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827TransferDone_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827TransferDone *p = (Gitsn_Iso14827TransferDone *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->filename;
	case 1: return &p->isSuccess;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Iso14827TransferDone_membs[] =
{
	{ Dz1Text("filename"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("isSuccess"), Dz1Text("bool_t"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827TransferDone
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827AcceptType
static bool_t Gitsn_Iso14827AcceptType_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827AcceptType *p = (Gitsn_Iso14827AcceptType *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_Iso14827AcceptTypePresent_login: Dz1Str_delAndSetNull(&p->x.login); p->x.login =(Dz1Str)info->data; info->data = NULL; break;
	case Gitsn_Iso14827AcceptTypePresent_singleSubscription: s32_t_delAndSetNull(&p->x.singleSubscription); p->x.singleSubscription =(s32_t *)info->data; info->data = NULL; break;
	case Gitsn_Iso14827AcceptTypePresent_registeredSubscription: p->x.registeredSubscription = *(u32_t *)info->data; break;
	case Gitsn_Iso14827AcceptTypePresent_publication: s32_t_delAndSetNull(&p->x.publication); p->x.publication =(s32_t *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_Iso14827AcceptTypePresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827AcceptType_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827AcceptType *p = (Gitsn_Iso14827AcceptType *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_Iso14827AcceptTypePresent_login: return p->x.login;
		case Gitsn_Iso14827AcceptTypePresent_singleSubscription: return p->x.singleSubscription;
		case Gitsn_Iso14827AcceptTypePresent_registeredSubscription: return &p->x.registeredSubscription;
		case Gitsn_Iso14827AcceptTypePresent_publication: return p->x.publication;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_Iso14827AcceptType_membs[] =
{
	{ Dz1Text("login"), Dz1Text("Dz1Str"), Gitsn_Iso14827AcceptTypePresent_login },
	{ Dz1Text("singleSubscription"), Dz1Text("s32_t"), Gitsn_Iso14827AcceptTypePresent_singleSubscription },
	{ Dz1Text("registeredSubscription"), Dz1Text("u32_t"), Gitsn_Iso14827AcceptTypePresent_registeredSubscription },
	{ Dz1Text("publication"), Dz1Text("s32_t"), Gitsn_Iso14827AcceptTypePresent_publication },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827AcceptType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Accept
static bool_t Gitsn_Iso14827Accept_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827Accept *p = (Gitsn_Iso14827Accept *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->pktNbr =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: Gitsn_Iso14827AcceptType_delAndSetNull(&p->acceptType); p->acceptType = (Gitsn_Iso14827AcceptType *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827Accept_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827Accept *p = (Gitsn_Iso14827Accept *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->pktNbr;
	case 1: return p->acceptType;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Iso14827Accept_membs[] =
{
	{ Dz1Text("pktNbr"), Dz1Text("u32_t"), 0 },
	{ Dz1Text("acceptType"), Dz1Text("Gitsn_Iso14827AcceptType"), 1 },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827Accept
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RejectLogin
static bool_t Gitsn_Iso14827RejectLogin_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827RejectLogin v = Gitsn_Iso14827RejectLogin_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_Iso14827RejectLogin)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_Iso14827RejectLoginFromStr(tok->v)) == Gitsn_Iso14827RejectLogin_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_Iso14827RejectLogin_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_Iso14827RejectLogin_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_Iso14827RejectLogin v = *(Gitsn_Iso14827RejectLogin *)obj;
		Dz1Str str_v = Gitsn_Iso14827RejectLoginStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_Iso14827RejectLogin
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RejectSubscription
static bool_t Gitsn_Iso14827RejectSubscription_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827RejectSubscription v = Gitsn_Iso14827RejectSubscription_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_Iso14827RejectSubscription)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_Iso14827RejectSubscriptionFromStr(tok->v)) == Gitsn_Iso14827RejectSubscription_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_Iso14827RejectSubscription_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_Iso14827RejectSubscription_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_Iso14827RejectSubscription v = *(Gitsn_Iso14827RejectSubscription *)obj;
		Dz1Str str_v = Gitsn_Iso14827RejectSubscriptionStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_Iso14827RejectSubscription
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RejectPublication
static bool_t Gitsn_Iso14827RejectPublication_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827RejectPublication v = Gitsn_Iso14827RejectPublication_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_Iso14827RejectPublication)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_Iso14827RejectPublicationFromStr(tok->v)) == Gitsn_Iso14827RejectPublication_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_Iso14827RejectPublication_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_Iso14827RejectPublication_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_Iso14827RejectPublication v = *(Gitsn_Iso14827RejectPublication *)obj;
		Dz1Str str_v = Gitsn_Iso14827RejectPublicationStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_Iso14827RejectPublication
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RejectPubDataReason
static bool_t Gitsn_Iso14827RejectPubDataReason_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827RejectPubDataReason v = Gitsn_Iso14827RejectPubDataReason_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Gitsn_Iso14827RejectPubDataReason)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Gitsn_Iso14827RejectPubDataReasonFromStr(tok->v)) == Gitsn_Iso14827RejectPubDataReason_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Gitsn_Iso14827RejectPubDataReason_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Gitsn_Iso14827RejectPubDataReason_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Gitsn_Iso14827RejectPubDataReason v = *(Gitsn_Iso14827RejectPubDataReason *)obj;
		Dz1Str str_v = Gitsn_Iso14827RejectPubDataReasonStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Gitsn_Iso14827RejectPubDataReason
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RejectPubData
static bool_t Gitsn_Iso14827RejectPubData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827RejectPubData *p = (Gitsn_Iso14827RejectPubData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->subSerial =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->pubSerial =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->reason =  *(Gitsn_Iso14827RejectPubDataReason *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827RejectPubData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827RejectPubData *p = (Gitsn_Iso14827RejectPubData *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->subSerial;
	case 1: return &p->pubSerial;
	case 2: return &p->reason;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Iso14827RejectPubData_membs[] =
{
	{ Dz1Text("subSerial"), Dz1Text("u32_t"), 0 },
	{ Dz1Text("pubSerial"), Dz1Text("u32_t"), 1 },
	{ Dz1Text("reason"), Dz1Text("Gitsn_Iso14827RejectPubDataReason"), 2 },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827RejectPubData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827RejectType
static bool_t Gitsn_Iso14827RejectType_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827RejectType *p = (Gitsn_Iso14827RejectType *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_Iso14827RejectTypePresent_login: p->x.login = *(Gitsn_Iso14827RejectLogin *)info->data; break;
	case Gitsn_Iso14827RejectTypePresent_subscription: p->x.subscription = *(Gitsn_Iso14827RejectSubscription *)info->data; break;
	case Gitsn_Iso14827RejectTypePresent_publication: p->x.publication = *(Gitsn_Iso14827RejectPublication *)info->data; break;
	case Gitsn_Iso14827RejectTypePresent_pubData: Gitsn_Iso14827RejectPubData_delAndSetNull(&p->x.pubData); p->x.pubData =(Gitsn_Iso14827RejectPubData *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_Iso14827RejectTypePresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827RejectType_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827RejectType *p = (Gitsn_Iso14827RejectType *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_Iso14827RejectTypePresent_login: return &p->x.login;
		case Gitsn_Iso14827RejectTypePresent_subscription: return &p->x.subscription;
		case Gitsn_Iso14827RejectTypePresent_publication: return &p->x.publication;
		case Gitsn_Iso14827RejectTypePresent_pubData: return p->x.pubData;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_Iso14827RejectType_membs[] =
{
	{ Dz1Text("login"), Dz1Text("Gitsn_Iso14827RejectLogin"), Gitsn_Iso14827RejectTypePresent_login },
	{ Dz1Text("subscription"), Dz1Text("Gitsn_Iso14827RejectSubscription"), Gitsn_Iso14827RejectTypePresent_subscription },
	{ Dz1Text("publication"), Dz1Text("Gitsn_Iso14827RejectPublication"), Gitsn_Iso14827RejectTypePresent_publication },
	{ Dz1Text("pubData"), Dz1Text("Gitsn_Iso14827RejectPubData"), Gitsn_Iso14827RejectTypePresent_pubData },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827RejectType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827Reject
static bool_t Gitsn_Iso14827Reject_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827Reject *p = (Gitsn_Iso14827Reject *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->pktNbr =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: Gitsn_Iso14827RejectType_delAndSetNull(&p->type); p->type = (Gitsn_Iso14827RejectType *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: Gitsn_Iso14827SubscriptionType_delAndSetNull(&p->altReq); p->altReq = (Gitsn_Iso14827SubscriptionType *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827Reject_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827Reject *p = (Gitsn_Iso14827Reject *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->pktNbr;
	case 1: return p->type;
	case 2: return p->altReq;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Iso14827Reject_membs[] =
{
	{ Dz1Text("pktNbr"), Dz1Text("u32_t"), 0 },
	{ Dz1Text("type"), Dz1Text("Gitsn_Iso14827RejectType"), 1 },
	{ Dz1Text("altReq"), Dz1Text("Gitsn_Iso14827SubscriptionType"), 2 },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827Reject
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827PDUs
static bool_t Gitsn_Iso14827PDUs_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827PDUs *p = (Gitsn_Iso14827PDUs *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Gitsn_Iso14827PDUsPresent_initiate: Gitsn_Iso14827Initiate_delAndSetNull(&p->x.initiate); p->x.initiate =(Gitsn_Iso14827Initiate *)info->data; info->data = NULL; break;
	case Gitsn_Iso14827PDUsPresent_login: Gitsn_Iso14827Login_delAndSetNull(&p->x.login); p->x.login =(Gitsn_Iso14827Login *)info->data; info->data = NULL; break;
	case Gitsn_Iso14827PDUsPresent_fred: p->x.fred = *(u32_t *)info->data; break;
	case Gitsn_Iso14827PDUsPresent_term: p->x.term = *(Gitsn_Iso14827Terminate *)info->data; break;
	case Gitsn_Iso14827PDUsPresent_logout: p->x.logout = *(Gitsn_Iso14827Logout *)info->data; break;
	case Gitsn_Iso14827PDUsPresent_subscription: Gitsn_Iso14827Subscription_delAndSetNull(&p->x.subscription); p->x.subscription =(Gitsn_Iso14827Subscription *)info->data; info->data = NULL; break;
	case Gitsn_Iso14827PDUsPresent_publication: Gitsn_Iso14827Publication_delAndSetNull(&p->x.publication); p->x.publication =(Gitsn_Iso14827Publication *)info->data; info->data = NULL; break;
	case Gitsn_Iso14827PDUsPresent_transferDone: Gitsn_Iso14827TransferDone_delAndSetNull(&p->x.transferDone); p->x.transferDone =(Gitsn_Iso14827TransferDone *)info->data; info->data = NULL; break;
	case Gitsn_Iso14827PDUsPresent_ack: Gitsn_Iso14827Accept_delAndSetNull(&p->x.ack); p->x.ack =(Gitsn_Iso14827Accept *)info->data; info->data = NULL; break;
	case Gitsn_Iso14827PDUsPresent_nak: Gitsn_Iso14827Reject_delAndSetNull(&p->x.nak); p->x.nak =(Gitsn_Iso14827Reject *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Gitsn_Iso14827PDUsPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827PDUs_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827PDUs *p = (Gitsn_Iso14827PDUs *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Gitsn_Iso14827PDUsPresent_initiate: return p->x.initiate;
		case Gitsn_Iso14827PDUsPresent_login: return p->x.login;
		case Gitsn_Iso14827PDUsPresent_fred: return &p->x.fred;
		case Gitsn_Iso14827PDUsPresent_term: return &p->x.term;
		case Gitsn_Iso14827PDUsPresent_logout: return &p->x.logout;
		case Gitsn_Iso14827PDUsPresent_subscription: return p->x.subscription;
		case Gitsn_Iso14827PDUsPresent_publication: return p->x.publication;
		case Gitsn_Iso14827PDUsPresent_transferDone: return p->x.transferDone;
		case Gitsn_Iso14827PDUsPresent_ack: return p->x.ack;
		case Gitsn_Iso14827PDUsPresent_nak: return p->x.nak;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Gitsn_Iso14827PDUs_membs[] =
{
	{ Dz1Text("initiate"), Dz1Text("Gitsn_Iso14827Initiate"), Gitsn_Iso14827PDUsPresent_initiate },
	{ Dz1Text("login"), Dz1Text("Gitsn_Iso14827Login"), Gitsn_Iso14827PDUsPresent_login },
	{ Dz1Text("fred"), Dz1Text("u32_t"), Gitsn_Iso14827PDUsPresent_fred },
	{ Dz1Text("term"), Dz1Text("Gitsn_Iso14827Terminate"), Gitsn_Iso14827PDUsPresent_term },
	{ Dz1Text("logout"), Dz1Text("Gitsn_Iso14827Logout"), Gitsn_Iso14827PDUsPresent_logout },
	{ Dz1Text("subscription"), Dz1Text("Gitsn_Iso14827Subscription"), Gitsn_Iso14827PDUsPresent_subscription },
	{ Dz1Text("publication"), Dz1Text("Gitsn_Iso14827Publication"), Gitsn_Iso14827PDUsPresent_publication },
	{ Dz1Text("transferDone"), Dz1Text("Gitsn_Iso14827TransferDone"), Gitsn_Iso14827PDUsPresent_transferDone },
	{ Dz1Text("ack"), Dz1Text("Gitsn_Iso14827Accept"), Gitsn_Iso14827PDUsPresent_ack },
	{ Dz1Text("nak"), Dz1Text("Gitsn_Iso14827Reject"), Gitsn_Iso14827PDUsPresent_nak },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827PDUs
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Gitsn_Iso14827C2CAuthMsg
static bool_t Gitsn_Iso14827C2CAuthMsg_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Gitsn_Iso14827C2CAuthMsg *p = (Gitsn_Iso14827C2CAuthMsg *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->authInfo); p->authInfo = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->pktNbr =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->priority =  *(s32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: Gitsn_Iso14827HdrOpt_delAndSetNull(&p->hdrOpt); p->hdrOpt = (Gitsn_Iso14827HdrOpt *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 4: Gitsn_Iso14827PDUs_delAndSetNull(&p->pdu); p->pdu = (Gitsn_Iso14827PDUs *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Gitsn_Iso14827C2CAuthMsg_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Gitsn_Iso14827C2CAuthMsg *p = (Gitsn_Iso14827C2CAuthMsg *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->authInfo;
	case 1: return &p->pktNbr;
	case 2: return &p->priority;
	case 3: return p->hdrOpt;
	case 4: return p->pdu;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Gitsn_Iso14827C2CAuthMsg_membs[] =
{
	{ Dz1Text("authInfo"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("pktNbr"), Dz1Text("u32_t"), 1 },
	{ Dz1Text("priority"), Dz1Text("s32_t"), 2 },
	{ Dz1Text("hdrOpt"), Dz1Text("Gitsn_Iso14827HdrOpt"), 3 },
	{ Dz1Text("pdu"), Dz1Text("Gitsn_Iso14827PDUs"), 4 },
	{ NULL, NULL, -1 }
};
// Gitsn_Iso14827C2CAuthMsg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PolicePrj4TestConfiguration_centerClient2rse
static bool_t PolicePrj4TestConfiguration_centerClient2rse_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	PolicePrj4TestConfiguration_centerClient2rse *p = (PolicePrj4TestConfiguration_centerClient2rse *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->my_domain); p->my_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->peer_domain); p->peer_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->peer_ip); p->peer_ip = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 3: p->peer_port =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: Dz1Str_delAndSetNull(&p->user); p->user = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 5: Dz1Str_delAndSetNull(&p->pass); p->pass = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 6: p->test_session =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->test_login_invalid =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->test_session_maintain =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 9: p->test_normal_pub =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 10: p->test_bsm =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 11: p->test_login_duplicate =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 12: p->test_invalid_sub =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 13: p->test_subs_cancel =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 14: p->test_pub_retry =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *PolicePrj4TestConfiguration_centerClient2rse_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	PolicePrj4TestConfiguration_centerClient2rse *p = (PolicePrj4TestConfiguration_centerClient2rse *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->my_domain;
	case 1: return p->peer_domain;
	case 2: return p->peer_ip;
	case 3: return &p->peer_port;
	case 4: return p->user;
	case 5: return p->pass;
	case 6: return &p->test_session;
	case 7: return &p->test_login_invalid;
	case 8: return &p->test_session_maintain;
	case 9: return &p->test_normal_pub;
	case 10: return &p->test_bsm;
	case 11: return &p->test_login_duplicate;
	case 12: return &p->test_invalid_sub;
	case 13: return &p->test_subs_cancel;
	case 14: return &p->test_pub_retry;
	default: return NULL;
	}
}

static Dz1JsonSpecChild PolicePrj4TestConfiguration_centerClient2rse_membs[] =
{
	{ Dz1Text("my_domain"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("peer_domain"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("peer_ip"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("peer_port"), Dz1Text("s64_t"), 3 },
	{ Dz1Text("user"), Dz1Text("Dz1Str"), 4 },
	{ Dz1Text("pass"), Dz1Text("Dz1Str"), 5 },
	{ Dz1Text("test_session"), Dz1Text("bool_t"), 6 },
	{ Dz1Text("test_login_invalid"), Dz1Text("bool_t"), 7 },
	{ Dz1Text("test_session_maintain"), Dz1Text("bool_t"), 8 },
	{ Dz1Text("test_normal_pub"), Dz1Text("bool_t"), 9 },
	{ Dz1Text("test_bsm"), Dz1Text("bool_t"), 10 },
	{ Dz1Text("test_login_duplicate"), Dz1Text("bool_t"), 11 },
	{ Dz1Text("test_invalid_sub"), Dz1Text("bool_t"), 12 },
	{ Dz1Text("test_subs_cancel"), Dz1Text("bool_t"), 13 },
	{ Dz1Text("test_pub_retry"), Dz1Text("bool_t"), 14 },
	{ NULL, NULL, -1 }
};
// PolicePrj4TestConfiguration_centerClient2rse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PolicePrj4TestConfiguration_rseServer2center
static bool_t PolicePrj4TestConfiguration_rseServer2center_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	PolicePrj4TestConfiguration_rseServer2center *p = (PolicePrj4TestConfiguration_rseServer2center *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->my_domain); p->my_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->peer_domain); p->peer_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: p->local_port =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->test_session =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->test_login_retry =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->subs_timeout_s =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->test_bsm =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->test_sub_retry =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->test_invalid_pub =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *PolicePrj4TestConfiguration_rseServer2center_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	PolicePrj4TestConfiguration_rseServer2center *p = (PolicePrj4TestConfiguration_rseServer2center *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->my_domain;
	case 1: return p->peer_domain;
	case 2: return &p->local_port;
	case 3: return &p->test_session;
	case 4: return &p->test_login_retry;
	case 5: return &p->subs_timeout_s;
	case 6: return &p->test_bsm;
	case 7: return &p->test_sub_retry;
	case 8: return &p->test_invalid_pub;
	default: return NULL;
	}
}

static Dz1JsonSpecChild PolicePrj4TestConfiguration_rseServer2center_membs[] =
{
	{ Dz1Text("my_domain"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("peer_domain"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("local_port"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("test_session"), Dz1Text("bool_t"), 3 },
	{ Dz1Text("test_login_retry"), Dz1Text("bool_t"), 4 },
	{ Dz1Text("subs_timeout_s"), Dz1Text("s64_t"), 5 },
	{ Dz1Text("test_bsm"), Dz1Text("bool_t"), 6 },
	{ Dz1Text("test_sub_retry"), Dz1Text("bool_t"), 7 },
	{ Dz1Text("test_invalid_pub"), Dz1Text("bool_t"), 8 },
	{ NULL, NULL, -1 }
};
// PolicePrj4TestConfiguration_rseServer2center
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PolicePrj4TestConfiguration_rseClient2center
static bool_t PolicePrj4TestConfiguration_rseClient2center_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	PolicePrj4TestConfiguration_rseClient2center *p = (PolicePrj4TestConfiguration_rseClient2center *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->my_domain); p->my_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->peer_domain); p->peer_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->peer_ip); p->peer_ip = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 3: p->peer_port =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: Dz1Str_delAndSetNull(&p->user); p->user = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 5: Dz1Str_delAndSetNull(&p->pass); p->pass = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 6: p->test_session =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->test_login_invalid =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->test_session_maintain =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 9: p->test_normal_pub =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 10: p->test_map =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 11: p->test_rsa =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 12: p->test_tim =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 13: p->test_login_duplicate =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 14: p->test_invalid_sub =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 15: p->test_subs_cancel =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 16: p->test_pub_retry =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *PolicePrj4TestConfiguration_rseClient2center_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	PolicePrj4TestConfiguration_rseClient2center *p = (PolicePrj4TestConfiguration_rseClient2center *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->my_domain;
	case 1: return p->peer_domain;
	case 2: return p->peer_ip;
	case 3: return &p->peer_port;
	case 4: return p->user;
	case 5: return p->pass;
	case 6: return &p->test_session;
	case 7: return &p->test_login_invalid;
	case 8: return &p->test_session_maintain;
	case 9: return &p->test_normal_pub;
	case 10: return &p->test_map;
	case 11: return &p->test_rsa;
	case 12: return &p->test_tim;
	case 13: return &p->test_login_duplicate;
	case 14: return &p->test_invalid_sub;
	case 15: return &p->test_subs_cancel;
	case 16: return &p->test_pub_retry;
	default: return NULL;
	}
}

static Dz1JsonSpecChild PolicePrj4TestConfiguration_rseClient2center_membs[] =
{
	{ Dz1Text("my_domain"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("peer_domain"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("peer_ip"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("peer_port"), Dz1Text("s64_t"), 3 },
	{ Dz1Text("user"), Dz1Text("Dz1Str"), 4 },
	{ Dz1Text("pass"), Dz1Text("Dz1Str"), 5 },
	{ Dz1Text("test_session"), Dz1Text("bool_t"), 6 },
	{ Dz1Text("test_login_invalid"), Dz1Text("bool_t"), 7 },
	{ Dz1Text("test_session_maintain"), Dz1Text("bool_t"), 8 },
	{ Dz1Text("test_normal_pub"), Dz1Text("bool_t"), 9 },
	{ Dz1Text("test_map"), Dz1Text("bool_t"), 10 },
	{ Dz1Text("test_rsa"), Dz1Text("bool_t"), 11 },
	{ Dz1Text("test_tim"), Dz1Text("bool_t"), 12 },
	{ Dz1Text("test_login_duplicate"), Dz1Text("bool_t"), 13 },
	{ Dz1Text("test_invalid_sub"), Dz1Text("bool_t"), 14 },
	{ Dz1Text("test_subs_cancel"), Dz1Text("bool_t"), 15 },
	{ Dz1Text("test_pub_retry"), Dz1Text("bool_t"), 16 },
	{ NULL, NULL, -1 }
};
// PolicePrj4TestConfiguration_rseClient2center
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PolicePrj4TestConfiguration_centerServer2rse
static bool_t PolicePrj4TestConfiguration_centerServer2rse_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	PolicePrj4TestConfiguration_centerServer2rse *p = (PolicePrj4TestConfiguration_centerServer2rse *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->my_domain); p->my_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->peer_domain); p->peer_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: p->local_port =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->test_session =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->test_login_retry =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->subs_timeout_s =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->test_map =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->test_rsa =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->test_tim =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 9: p->test_sub_retry =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 10: p->test_invalid_pub =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *PolicePrj4TestConfiguration_centerServer2rse_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	PolicePrj4TestConfiguration_centerServer2rse *p = (PolicePrj4TestConfiguration_centerServer2rse *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->my_domain;
	case 1: return p->peer_domain;
	case 2: return &p->local_port;
	case 3: return &p->test_session;
	case 4: return &p->test_login_retry;
	case 5: return &p->subs_timeout_s;
	case 6: return &p->test_map;
	case 7: return &p->test_rsa;
	case 8: return &p->test_tim;
	case 9: return &p->test_sub_retry;
	case 10: return &p->test_invalid_pub;
	default: return NULL;
	}
}

static Dz1JsonSpecChild PolicePrj4TestConfiguration_centerServer2rse_membs[] =
{
	{ Dz1Text("my_domain"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("peer_domain"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("local_port"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("test_session"), Dz1Text("bool_t"), 3 },
	{ Dz1Text("test_login_retry"), Dz1Text("bool_t"), 4 },
	{ Dz1Text("subs_timeout_s"), Dz1Text("s64_t"), 5 },
	{ Dz1Text("test_map"), Dz1Text("bool_t"), 6 },
	{ Dz1Text("test_rsa"), Dz1Text("bool_t"), 7 },
	{ Dz1Text("test_tim"), Dz1Text("bool_t"), 8 },
	{ Dz1Text("test_sub_retry"), Dz1Text("bool_t"), 9 },
	{ Dz1Text("test_invalid_pub"), Dz1Text("bool_t"), 10 },
	{ NULL, NULL, -1 }
};
// PolicePrj4TestConfiguration_centerServer2rse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PolicePrj4TestConfiguration_signalserverServer2center
static bool_t PolicePrj4TestConfiguration_signalserverServer2center_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	PolicePrj4TestConfiguration_signalserverServer2center *p = (PolicePrj4TestConfiguration_signalserverServer2center *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->my_domain); p->my_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->peer_domain); p->peer_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: p->local_port =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->test_session =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->test_login_retry =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->subs_timeout_s =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->test_spat =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->test_tls =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->test_sub_retry =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 9: p->test_invalid_pub =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *PolicePrj4TestConfiguration_signalserverServer2center_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	PolicePrj4TestConfiguration_signalserverServer2center *p = (PolicePrj4TestConfiguration_signalserverServer2center *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->my_domain;
	case 1: return p->peer_domain;
	case 2: return &p->local_port;
	case 3: return &p->test_session;
	case 4: return &p->test_login_retry;
	case 5: return &p->subs_timeout_s;
	case 6: return &p->test_spat;
	case 7: return &p->test_tls;
	case 8: return &p->test_sub_retry;
	case 9: return &p->test_invalid_pub;
	default: return NULL;
	}
}

static Dz1JsonSpecChild PolicePrj4TestConfiguration_signalserverServer2center_membs[] =
{
	{ Dz1Text("my_domain"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("peer_domain"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("local_port"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("test_session"), Dz1Text("bool_t"), 3 },
	{ Dz1Text("test_login_retry"), Dz1Text("bool_t"), 4 },
	{ Dz1Text("subs_timeout_s"), Dz1Text("s64_t"), 5 },
	{ Dz1Text("test_spat"), Dz1Text("bool_t"), 6 },
	{ Dz1Text("test_tls"), Dz1Text("bool_t"), 7 },
	{ Dz1Text("test_sub_retry"), Dz1Text("bool_t"), 8 },
	{ Dz1Text("test_invalid_pub"), Dz1Text("bool_t"), 9 },
	{ NULL, NULL, -1 }
};
// PolicePrj4TestConfiguration_signalserverServer2center
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00100_3TestConfigurationClientRole
static bool_t ITSK00100_3TestConfigurationClientRole_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ITSK00100_3TestConfigurationClientRole *p = (ITSK00100_3TestConfigurationClientRole *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->my_domain); p->my_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->peer_domain); p->peer_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->peer_ip); p->peer_ip = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 3: p->peer_port =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: Dz1Str_delAndSetNull(&p->user); p->user = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 5: Dz1Str_delAndSetNull(&p->pass); p->pass = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 6: p->test_session =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->test_login_invalid =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->test_session_maintain =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 9: p->test_normal_pub =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 10: p->test_pub_incident_detection_info =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 11: p->test_pub_incident_termination_info =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 12: p->test_pub_incident_detection_video_file_info_provide =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 13: p->test_pub_control_state_info =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 14: p->test_pub_sensor_state_info =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 15: p->test_pub_moving_object =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 16: p->test_login_duplicate =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 17: p->test_invalid_sub =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 18: p->test_subs_cancel =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 19: p->test_pub_retry =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ITSK00100_3TestConfigurationClientRole_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ITSK00100_3TestConfigurationClientRole *p = (ITSK00100_3TestConfigurationClientRole *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->my_domain;
	case 1: return p->peer_domain;
	case 2: return p->peer_ip;
	case 3: return &p->peer_port;
	case 4: return p->user;
	case 5: return p->pass;
	case 6: return &p->test_session;
	case 7: return &p->test_login_invalid;
	case 8: return &p->test_session_maintain;
	case 9: return &p->test_normal_pub;
	case 10: return &p->test_pub_incident_detection_info;
	case 11: return &p->test_pub_incident_termination_info;
	case 12: return &p->test_pub_incident_detection_video_file_info_provide;
	case 13: return &p->test_pub_control_state_info;
	case 14: return &p->test_pub_sensor_state_info;
	case 15: return &p->test_pub_moving_object;
	case 16: return &p->test_login_duplicate;
	case 17: return &p->test_invalid_sub;
	case 18: return &p->test_subs_cancel;
	case 19: return &p->test_pub_retry;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ITSK00100_3TestConfigurationClientRole_membs[] =
{
	{ Dz1Text("my_domain"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("peer_domain"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("peer_ip"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("peer_port"), Dz1Text("s64_t"), 3 },
	{ Dz1Text("user"), Dz1Text("Dz1Str"), 4 },
	{ Dz1Text("pass"), Dz1Text("Dz1Str"), 5 },
	{ Dz1Text("test_session"), Dz1Text("bool_t"), 6 },
	{ Dz1Text("test_login_invalid"), Dz1Text("bool_t"), 7 },
	{ Dz1Text("test_session_maintain"), Dz1Text("bool_t"), 8 },
	{ Dz1Text("test_normal_pub"), Dz1Text("bool_t"), 9 },
	{ Dz1Text("test_pub_incident_detection_info"), Dz1Text("bool_t"), 10 },
	{ Dz1Text("test_pub_incident_termination_info"), Dz1Text("bool_t"), 11 },
	{ Dz1Text("test_pub_incident_detection_video_file_info_provide"), Dz1Text("bool_t"), 12 },
	{ Dz1Text("test_pub_control_state_info"), Dz1Text("bool_t"), 13 },
	{ Dz1Text("test_pub_sensor_state_info"), Dz1Text("bool_t"), 14 },
	{ Dz1Text("test_pub_moving_object"), Dz1Text("bool_t"), 15 },
	{ Dz1Text("test_login_duplicate"), Dz1Text("bool_t"), 16 },
	{ Dz1Text("test_invalid_sub"), Dz1Text("bool_t"), 17 },
	{ Dz1Text("test_subs_cancel"), Dz1Text("bool_t"), 18 },
	{ Dz1Text("test_pub_retry"), Dz1Text("bool_t"), 19 },
	{ NULL, NULL, -1 }
};
// ITSK00100_3TestConfigurationClientRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00100_3TestConfigurationServerRole
static bool_t ITSK00100_3TestConfigurationServerRole_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ITSK00100_3TestConfigurationServerRole *p = (ITSK00100_3TestConfigurationServerRole *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->my_domain); p->my_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->peer_domain); p->peer_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: p->local_port =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->test_session =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->test_login_retry =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->test_sub_incident_detection_info =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->test_sub_incident_termination_info =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->test_sub_incident_detection_video_file_info_provide =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->test_sub_control_state_info =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 9: p->test_sub_sensor_state_info =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 10: p->test_sub_moving_object =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 11: p->test_sub_retry =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 12: p->test_invalid_pub =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ITSK00100_3TestConfigurationServerRole_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ITSK00100_3TestConfigurationServerRole *p = (ITSK00100_3TestConfigurationServerRole *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->my_domain;
	case 1: return p->peer_domain;
	case 2: return &p->local_port;
	case 3: return &p->test_session;
	case 4: return &p->test_login_retry;
	case 5: return &p->test_sub_incident_detection_info;
	case 6: return &p->test_sub_incident_termination_info;
	case 7: return &p->test_sub_incident_detection_video_file_info_provide;
	case 8: return &p->test_sub_control_state_info;
	case 9: return &p->test_sub_sensor_state_info;
	case 10: return &p->test_sub_moving_object;
	case 11: return &p->test_sub_retry;
	case 12: return &p->test_invalid_pub;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ITSK00100_3TestConfigurationServerRole_membs[] =
{
	{ Dz1Text("my_domain"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("peer_domain"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("local_port"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("test_session"), Dz1Text("bool_t"), 3 },
	{ Dz1Text("test_login_retry"), Dz1Text("bool_t"), 4 },
	{ Dz1Text("test_sub_incident_detection_info"), Dz1Text("bool_t"), 5 },
	{ Dz1Text("test_sub_incident_termination_info"), Dz1Text("bool_t"), 6 },
	{ Dz1Text("test_sub_incident_detection_video_file_info_provide"), Dz1Text("bool_t"), 7 },
	{ Dz1Text("test_sub_control_state_info"), Dz1Text("bool_t"), 8 },
	{ Dz1Text("test_sub_sensor_state_info"), Dz1Text("bool_t"), 9 },
	{ Dz1Text("test_sub_moving_object"), Dz1Text("bool_t"), 10 },
	{ Dz1Text("test_sub_retry"), Dz1Text("bool_t"), 11 },
	{ Dz1Text("test_invalid_pub"), Dz1Text("bool_t"), 12 },
	{ NULL, NULL, -1 }
};
// ITSK00100_3TestConfigurationServerRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation1TestConfiguration_clientRole1
static bool_t TechnicalRegulation1TestConfiguration_clientRole1_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TechnicalRegulation1TestConfiguration_clientRole1 *p = (TechnicalRegulation1TestConfiguration_clientRole1 *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->my_domain); p->my_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->peer_domain); p->peer_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->peer_ip); p->peer_ip = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 3: p->peer_port =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: Dz1Str_delAndSetNull(&p->user); p->user = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 5: Dz1Str_delAndSetNull(&p->pass); p->pass = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 6: p->test_session =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->test_login_invalid =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->test_session_maintain =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 9: p->test_normal_pub =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 10: p->test_pub_current_link_state =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 11: p->test_pub_event_identity =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 12: p->test_pub_incident_identity =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 13: p->test_pub_incident_conditions =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 14: p->test_pub_roadway_surface_status =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 15: p->test_pub_weather_information =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 16: p->test_pub_link_roadway_geometry =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 17: p->test_pub_probe_vehicle_detection =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 18: p->test_pub_detector_collection =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 19: p->test_pub_extention_comm_pdu =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 20: p->test_login_duplicate =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 21: p->test_invalid_sub =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 22: p->test_subs_cancel =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 23: p->test_pub_retry =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *TechnicalRegulation1TestConfiguration_clientRole1_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	TechnicalRegulation1TestConfiguration_clientRole1 *p = (TechnicalRegulation1TestConfiguration_clientRole1 *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->my_domain;
	case 1: return p->peer_domain;
	case 2: return p->peer_ip;
	case 3: return &p->peer_port;
	case 4: return p->user;
	case 5: return p->pass;
	case 6: return &p->test_session;
	case 7: return &p->test_login_invalid;
	case 8: return &p->test_session_maintain;
	case 9: return &p->test_normal_pub;
	case 10: return &p->test_pub_current_link_state;
	case 11: return &p->test_pub_event_identity;
	case 12: return &p->test_pub_incident_identity;
	case 13: return &p->test_pub_incident_conditions;
	case 14: return &p->test_pub_roadway_surface_status;
	case 15: return &p->test_pub_weather_information;
	case 16: return &p->test_pub_link_roadway_geometry;
	case 17: return &p->test_pub_probe_vehicle_detection;
	case 18: return &p->test_pub_detector_collection;
	case 19: return &p->test_pub_extention_comm_pdu;
	case 20: return &p->test_login_duplicate;
	case 21: return &p->test_invalid_sub;
	case 22: return &p->test_subs_cancel;
	case 23: return &p->test_pub_retry;
	default: return NULL;
	}
}

static Dz1JsonSpecChild TechnicalRegulation1TestConfiguration_clientRole1_membs[] =
{
	{ Dz1Text("my_domain"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("peer_domain"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("peer_ip"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("peer_port"), Dz1Text("s64_t"), 3 },
	{ Dz1Text("user"), Dz1Text("Dz1Str"), 4 },
	{ Dz1Text("pass"), Dz1Text("Dz1Str"), 5 },
	{ Dz1Text("test_session"), Dz1Text("bool_t"), 6 },
	{ Dz1Text("test_login_invalid"), Dz1Text("bool_t"), 7 },
	{ Dz1Text("test_session_maintain"), Dz1Text("bool_t"), 8 },
	{ Dz1Text("test_normal_pub"), Dz1Text("bool_t"), 9 },
	{ Dz1Text("test_pub_current_link_state"), Dz1Text("bool_t"), 10 },
	{ Dz1Text("test_pub_event_identity"), Dz1Text("bool_t"), 11 },
	{ Dz1Text("test_pub_incident_identity"), Dz1Text("bool_t"), 12 },
	{ Dz1Text("test_pub_incident_conditions"), Dz1Text("bool_t"), 13 },
	{ Dz1Text("test_pub_roadway_surface_status"), Dz1Text("bool_t"), 14 },
	{ Dz1Text("test_pub_weather_information"), Dz1Text("bool_t"), 15 },
	{ Dz1Text("test_pub_link_roadway_geometry"), Dz1Text("bool_t"), 16 },
	{ Dz1Text("test_pub_probe_vehicle_detection"), Dz1Text("bool_t"), 17 },
	{ Dz1Text("test_pub_detector_collection"), Dz1Text("bool_t"), 18 },
	{ Dz1Text("test_pub_extention_comm_pdu"), Dz1Text("bool_t"), 19 },
	{ Dz1Text("test_login_duplicate"), Dz1Text("bool_t"), 20 },
	{ Dz1Text("test_invalid_sub"), Dz1Text("bool_t"), 21 },
	{ Dz1Text("test_subs_cancel"), Dz1Text("bool_t"), 22 },
	{ Dz1Text("test_pub_retry"), Dz1Text("bool_t"), 23 },
	{ NULL, NULL, -1 }
};
// TechnicalRegulation1TestConfiguration_clientRole1
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation1TestConfiguration_serverRole1
static bool_t TechnicalRegulation1TestConfiguration_serverRole1_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TechnicalRegulation1TestConfiguration_serverRole1 *p = (TechnicalRegulation1TestConfiguration_serverRole1 *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->my_domain); p->my_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->peer_domain); p->peer_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: p->local_port =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->test_session =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->test_login_retry =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->test_normal_sub =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->test_sub_retry =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->test_invalid_pub =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *TechnicalRegulation1TestConfiguration_serverRole1_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	TechnicalRegulation1TestConfiguration_serverRole1 *p = (TechnicalRegulation1TestConfiguration_serverRole1 *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->my_domain;
	case 1: return p->peer_domain;
	case 2: return &p->local_port;
	case 3: return &p->test_session;
	case 4: return &p->test_login_retry;
	case 5: return &p->test_normal_sub;
	case 6: return &p->test_sub_retry;
	case 7: return &p->test_invalid_pub;
	default: return NULL;
	}
}

static Dz1JsonSpecChild TechnicalRegulation1TestConfiguration_serverRole1_membs[] =
{
	{ Dz1Text("my_domain"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("peer_domain"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("local_port"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("test_session"), Dz1Text("bool_t"), 3 },
	{ Dz1Text("test_login_retry"), Dz1Text("bool_t"), 4 },
	{ Dz1Text("test_normal_sub"), Dz1Text("bool_t"), 5 },
	{ Dz1Text("test_sub_retry"), Dz1Text("bool_t"), 6 },
	{ Dz1Text("test_invalid_pub"), Dz1Text("bool_t"), 7 },
	{ NULL, NULL, -1 }
};
// TechnicalRegulation1TestConfiguration_serverRole1
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation2TestConfiguration_clientRole1
static bool_t TechnicalRegulation2TestConfiguration_clientRole1_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TechnicalRegulation2TestConfiguration_clientRole1 *p = (TechnicalRegulation2TestConfiguration_clientRole1 *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->my_domain); p->my_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->peer_domain); p->peer_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->peer_ip); p->peer_ip = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 3: p->peer_port =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: Dz1Str_delAndSetNull(&p->user); p->user = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 5: Dz1Str_delAndSetNull(&p->pass); p->pass = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 6: p->test_session =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->test_login_invalid =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->test_session_maintain =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 9: p->test_normal_pub =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 10: p->test_pub_comm_tx_pdu =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 11: p->test_pub_comm_rx_pdu =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 12: p->test_login_duplicate =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 13: p->test_invalid_sub =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 14: p->test_subs_cancel =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 15: p->test_pub_retry =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *TechnicalRegulation2TestConfiguration_clientRole1_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	TechnicalRegulation2TestConfiguration_clientRole1 *p = (TechnicalRegulation2TestConfiguration_clientRole1 *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->my_domain;
	case 1: return p->peer_domain;
	case 2: return p->peer_ip;
	case 3: return &p->peer_port;
	case 4: return p->user;
	case 5: return p->pass;
	case 6: return &p->test_session;
	case 7: return &p->test_login_invalid;
	case 8: return &p->test_session_maintain;
	case 9: return &p->test_normal_pub;
	case 10: return &p->test_pub_comm_tx_pdu;
	case 11: return &p->test_pub_comm_rx_pdu;
	case 12: return &p->test_login_duplicate;
	case 13: return &p->test_invalid_sub;
	case 14: return &p->test_subs_cancel;
	case 15: return &p->test_pub_retry;
	default: return NULL;
	}
}

static Dz1JsonSpecChild TechnicalRegulation2TestConfiguration_clientRole1_membs[] =
{
	{ Dz1Text("my_domain"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("peer_domain"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("peer_ip"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("peer_port"), Dz1Text("s64_t"), 3 },
	{ Dz1Text("user"), Dz1Text("Dz1Str"), 4 },
	{ Dz1Text("pass"), Dz1Text("Dz1Str"), 5 },
	{ Dz1Text("test_session"), Dz1Text("bool_t"), 6 },
	{ Dz1Text("test_login_invalid"), Dz1Text("bool_t"), 7 },
	{ Dz1Text("test_session_maintain"), Dz1Text("bool_t"), 8 },
	{ Dz1Text("test_normal_pub"), Dz1Text("bool_t"), 9 },
	{ Dz1Text("test_pub_comm_tx_pdu"), Dz1Text("bool_t"), 10 },
	{ Dz1Text("test_pub_comm_rx_pdu"), Dz1Text("bool_t"), 11 },
	{ Dz1Text("test_login_duplicate"), Dz1Text("bool_t"), 12 },
	{ Dz1Text("test_invalid_sub"), Dz1Text("bool_t"), 13 },
	{ Dz1Text("test_subs_cancel"), Dz1Text("bool_t"), 14 },
	{ Dz1Text("test_pub_retry"), Dz1Text("bool_t"), 15 },
	{ NULL, NULL, -1 }
};
// TechnicalRegulation2TestConfiguration_clientRole1
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulationTestConfiguration_clientRole2
static bool_t TechnicalRegulationTestConfiguration_clientRole2_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TechnicalRegulationTestConfiguration_clientRole2 *p = (TechnicalRegulationTestConfiguration_clientRole2 *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->my_domain); p->my_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->peer_domain); p->peer_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->peer_ip); p->peer_ip = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 3: p->peer_port =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: Dz1Str_delAndSetNull(&p->user); p->user = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 5: Dz1Str_delAndSetNull(&p->pass); p->pass = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 6: p->test_total =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->expire_time =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *TechnicalRegulationTestConfiguration_clientRole2_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	TechnicalRegulationTestConfiguration_clientRole2 *p = (TechnicalRegulationTestConfiguration_clientRole2 *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->my_domain;
	case 1: return p->peer_domain;
	case 2: return p->peer_ip;
	case 3: return &p->peer_port;
	case 4: return p->user;
	case 5: return p->pass;
	case 6: return &p->test_total;
	case 7: return &p->expire_time;
	default: return NULL;
	}
}

static Dz1JsonSpecChild TechnicalRegulationTestConfiguration_clientRole2_membs[] =
{
	{ Dz1Text("my_domain"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("peer_domain"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("peer_ip"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("peer_port"), Dz1Text("s64_t"), 3 },
	{ Dz1Text("user"), Dz1Text("Dz1Str"), 4 },
	{ Dz1Text("pass"), Dz1Text("Dz1Str"), 5 },
	{ Dz1Text("test_total"), Dz1Text("bool_t"), 6 },
	{ Dz1Text("expire_time"), Dz1Text("s64_t"), 7 },
	{ NULL, NULL, -1 }
};
// TechnicalRegulationTestConfiguration_clientRole2
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulationTestConfiguration_serverRole2
static bool_t TechnicalRegulationTestConfiguration_serverRole2_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TechnicalRegulationTestConfiguration_serverRole2 *p = (TechnicalRegulationTestConfiguration_serverRole2 *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->my_domain); p->my_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->peer_domain); p->peer_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: p->local_port =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->test_total =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->subs_timeout_s =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *TechnicalRegulationTestConfiguration_serverRole2_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	TechnicalRegulationTestConfiguration_serverRole2 *p = (TechnicalRegulationTestConfiguration_serverRole2 *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->my_domain;
	case 1: return p->peer_domain;
	case 2: return &p->local_port;
	case 3: return &p->test_total;
	case 4: return &p->subs_timeout_s;
	default: return NULL;
	}
}

static Dz1JsonSpecChild TechnicalRegulationTestConfiguration_serverRole2_membs[] =
{
	{ Dz1Text("my_domain"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("peer_domain"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("local_port"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("test_total"), Dz1Text("bool_t"), 3 },
	{ Dz1Text("subs_timeout_s"), Dz1Text("s64_t"), 4 },
	{ NULL, NULL, -1 }
};
// TechnicalRegulationTestConfiguration_serverRole2
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulationTestConfiguration_duoClientRole
static bool_t TechnicalRegulationTestConfiguration_duoClientRole_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TechnicalRegulationTestConfiguration_duoClientRole *p = (TechnicalRegulationTestConfiguration_duoClientRole *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->peer_domain); p->peer_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->peer_ip); p->peer_ip = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: p->peer_port =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: Dz1Str_delAndSetNull(&p->my_domain1); p->my_domain1 = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 4: Dz1Str_delAndSetNull(&p->user1); p->user1 = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 5: Dz1Str_delAndSetNull(&p->pass1); p->pass1 = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 6: Dz1Str_delAndSetNull(&p->my_domain2); p->my_domain2 = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 7: Dz1Str_delAndSetNull(&p->user2); p->user2 = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 8: Dz1Str_delAndSetNull(&p->pass2); p->pass2 = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 9: p->test_duo_client =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *TechnicalRegulationTestConfiguration_duoClientRole_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	TechnicalRegulationTestConfiguration_duoClientRole *p = (TechnicalRegulationTestConfiguration_duoClientRole *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->peer_domain;
	case 1: return p->peer_ip;
	case 2: return &p->peer_port;
	case 3: return p->my_domain1;
	case 4: return p->user1;
	case 5: return p->pass1;
	case 6: return p->my_domain2;
	case 7: return p->user2;
	case 8: return p->pass2;
	case 9: return &p->test_duo_client;
	default: return NULL;
	}
}

static Dz1JsonSpecChild TechnicalRegulationTestConfiguration_duoClientRole_membs[] =
{
	{ Dz1Text("peer_domain"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("peer_ip"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("peer_port"), Dz1Text("s64_t"), 2 },
	{ Dz1Text("my_domain1"), Dz1Text("Dz1Str"), 3 },
	{ Dz1Text("user1"), Dz1Text("Dz1Str"), 4 },
	{ Dz1Text("pass1"), Dz1Text("Dz1Str"), 5 },
	{ Dz1Text("my_domain2"), Dz1Text("Dz1Str"), 6 },
	{ Dz1Text("user2"), Dz1Text("Dz1Str"), 7 },
	{ Dz1Text("pass2"), Dz1Text("Dz1Str"), 8 },
	{ Dz1Text("test_duo_client"), Dz1Text("bool_t"), 9 },
	{ NULL, NULL, -1 }
};
// TechnicalRegulationTestConfiguration_duoClientRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulationTestConfiguration_duoSessionRole
static bool_t TechnicalRegulationTestConfiguration_duoSessionRole_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TechnicalRegulationTestConfiguration_duoSessionRole *p = (TechnicalRegulationTestConfiguration_duoSessionRole *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->test_duo_session =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->my_domain); p->my_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->peer_ip); p->peer_ip = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 3: Dz1Str_delAndSetNull(&p->peer_server_domain); p->peer_server_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 4: p->peer_server_port =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: Dz1Str_delAndSetNull(&p->user); p->user = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 6: Dz1Str_delAndSetNull(&p->pass); p->pass = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 7: Dz1Str_delAndSetNull(&p->peer_client_domain); p->peer_client_domain = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 8: p->peer_client_port =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *TechnicalRegulationTestConfiguration_duoSessionRole_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	TechnicalRegulationTestConfiguration_duoSessionRole *p = (TechnicalRegulationTestConfiguration_duoSessionRole *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->test_duo_session;
	case 1: return p->my_domain;
	case 2: return p->peer_ip;
	case 3: return p->peer_server_domain;
	case 4: return &p->peer_server_port;
	case 5: return p->user;
	case 6: return p->pass;
	case 7: return p->peer_client_domain;
	case 8: return &p->peer_client_port;
	default: return NULL;
	}
}

static Dz1JsonSpecChild TechnicalRegulationTestConfiguration_duoSessionRole_membs[] =
{
	{ Dz1Text("test_duo_session"), Dz1Text("bool_t"), 0 },
	{ Dz1Text("my_domain"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("peer_ip"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("peer_server_domain"), Dz1Text("Dz1Str"), 3 },
	{ Dz1Text("peer_server_port"), Dz1Text("s64_t"), 4 },
	{ Dz1Text("user"), Dz1Text("Dz1Str"), 5 },
	{ Dz1Text("pass"), Dz1Text("Dz1Str"), 6 },
	{ Dz1Text("peer_client_domain"), Dz1Text("Dz1Str"), 7 },
	{ Dz1Text("peer_client_port"), Dz1Text("s64_t"), 8 },
	{ NULL, NULL, -1 }
};
// TechnicalRegulationTestConfiguration_duoSessionRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TestConfiguration
static bool_t Iso14827TestConfiguration_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TestConfiguration *p = (Iso14827TestConfiguration *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Iso14827TestConfigurationPresent_centerClient2rse: PolicePrj4TestConfiguration_centerClient2rse_delAndSetNull(&p->x.centerClient2rse); p->x.centerClient2rse =(PolicePrj4TestConfiguration_centerClient2rse *)info->data; info->data = NULL; break;
	case Iso14827TestConfigurationPresent_rseServer2center: PolicePrj4TestConfiguration_rseServer2center_delAndSetNull(&p->x.rseServer2center); p->x.rseServer2center =(PolicePrj4TestConfiguration_rseServer2center *)info->data; info->data = NULL; break;
	case Iso14827TestConfigurationPresent_rseClient2center: PolicePrj4TestConfiguration_rseClient2center_delAndSetNull(&p->x.rseClient2center); p->x.rseClient2center =(PolicePrj4TestConfiguration_rseClient2center *)info->data; info->data = NULL; break;
	case Iso14827TestConfigurationPresent_centerServer2rse: PolicePrj4TestConfiguration_centerServer2rse_delAndSetNull(&p->x.centerServer2rse); p->x.centerServer2rse =(PolicePrj4TestConfiguration_centerServer2rse *)info->data; info->data = NULL; break;
	case Iso14827TestConfigurationPresent_signalserver2center: PolicePrj4TestConfiguration_signalserverServer2center_delAndSetNull(&p->x.signalserver2center); p->x.signalserver2center =(PolicePrj4TestConfiguration_signalserverServer2center *)info->data; info->data = NULL; break;
	case Iso14827TestConfigurationPresent_itsk00100_3c2cClient: ITSK00100_3TestConfigurationClientRole_delAndSetNull(&p->x.itsk00100_3c2cClient); p->x.itsk00100_3c2cClient =(ITSK00100_3TestConfigurationClientRole *)info->data; info->data = NULL; break;
	case Iso14827TestConfigurationPresent_itsk00100_3c2cServer: ITSK00100_3TestConfigurationServerRole_delAndSetNull(&p->x.itsk00100_3c2cServer); p->x.itsk00100_3c2cServer =(ITSK00100_3TestConfigurationServerRole *)info->data; info->data = NULL; break;
	case Iso14827TestConfigurationPresent_technical_regulation1_clientRole1: TechnicalRegulation1TestConfiguration_clientRole1_delAndSetNull(&p->x.technical_regulation1_clientRole1); p->x.technical_regulation1_clientRole1 =(TechnicalRegulation1TestConfiguration_clientRole1 *)info->data; info->data = NULL; break;
	case Iso14827TestConfigurationPresent_technical_regulation1_serverRole1: TechnicalRegulation1TestConfiguration_serverRole1_delAndSetNull(&p->x.technical_regulation1_serverRole1); p->x.technical_regulation1_serverRole1 =(TechnicalRegulation1TestConfiguration_serverRole1 *)info->data; info->data = NULL; break;
	case Iso14827TestConfigurationPresent_technical_regulation2_clientRole: TechnicalRegulation2TestConfiguration_clientRole1_delAndSetNull(&p->x.technical_regulation2_clientRole); p->x.technical_regulation2_clientRole =(TechnicalRegulation2TestConfiguration_clientRole1 *)info->data; info->data = NULL; break;
	case Iso14827TestConfigurationPresent_technical_regulation1_clientRole2: TechnicalRegulationTestConfiguration_clientRole2_delAndSetNull(&p->x.technical_regulation1_clientRole2); p->x.technical_regulation1_clientRole2 =(TechnicalRegulationTestConfiguration_clientRole2 *)info->data; info->data = NULL; break;
	case Iso14827TestConfigurationPresent_technical_regulation1_serverRole2: TechnicalRegulationTestConfiguration_serverRole2_delAndSetNull(&p->x.technical_regulation1_serverRole2); p->x.technical_regulation1_serverRole2 =(TechnicalRegulationTestConfiguration_serverRole2 *)info->data; info->data = NULL; break;
	case Iso14827TestConfigurationPresent_technical_regulation1_duoClientRole: TechnicalRegulationTestConfiguration_duoClientRole_delAndSetNull(&p->x.technical_regulation1_duoClientRole); p->x.technical_regulation1_duoClientRole =(TechnicalRegulationTestConfiguration_duoClientRole *)info->data; info->data = NULL; break;
	case Iso14827TestConfigurationPresent_technical_regulation1_duoSessionRole: TechnicalRegulationTestConfiguration_duoSessionRole_delAndSetNull(&p->x.technical_regulation1_duoSessionRole); p->x.technical_regulation1_duoSessionRole =(TechnicalRegulationTestConfiguration_duoSessionRole *)info->data; info->data = NULL; break;
	case Iso14827TestConfigurationPresent_technical_regulation2_clientRole2: TechnicalRegulationTestConfiguration_clientRole2_delAndSetNull(&p->x.technical_regulation2_clientRole2); p->x.technical_regulation2_clientRole2 =(TechnicalRegulationTestConfiguration_clientRole2 *)info->data; info->data = NULL; break;
	case Iso14827TestConfigurationPresent_technical_regulation2_serverRole2: TechnicalRegulationTestConfiguration_serverRole2_delAndSetNull(&p->x.technical_regulation2_serverRole2); p->x.technical_regulation2_serverRole2 =(TechnicalRegulationTestConfiguration_serverRole2 *)info->data; info->data = NULL; break;
	case Iso14827TestConfigurationPresent_technical_regulation2_duoClientRole: TechnicalRegulationTestConfiguration_duoClientRole_delAndSetNull(&p->x.technical_regulation2_duoClientRole); p->x.technical_regulation2_duoClientRole =(TechnicalRegulationTestConfiguration_duoClientRole *)info->data; info->data = NULL; break;
	case Iso14827TestConfigurationPresent_technical_regulation2_duoSessionRole: TechnicalRegulationTestConfiguration_duoSessionRole_delAndSetNull(&p->x.technical_regulation2_duoSessionRole); p->x.technical_regulation2_duoSessionRole =(TechnicalRegulationTestConfiguration_duoSessionRole *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Iso14827TestConfigurationPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Iso14827TestConfiguration_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Iso14827TestConfiguration *p = (Iso14827TestConfiguration *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Iso14827TestConfigurationPresent_centerClient2rse: return p->x.centerClient2rse;
		case Iso14827TestConfigurationPresent_rseServer2center: return p->x.rseServer2center;
		case Iso14827TestConfigurationPresent_rseClient2center: return p->x.rseClient2center;
		case Iso14827TestConfigurationPresent_centerServer2rse: return p->x.centerServer2rse;
		case Iso14827TestConfigurationPresent_signalserver2center: return p->x.signalserver2center;
		case Iso14827TestConfigurationPresent_itsk00100_3c2cClient: return p->x.itsk00100_3c2cClient;
		case Iso14827TestConfigurationPresent_itsk00100_3c2cServer: return p->x.itsk00100_3c2cServer;
		case Iso14827TestConfigurationPresent_technical_regulation1_clientRole1: return p->x.technical_regulation1_clientRole1;
		case Iso14827TestConfigurationPresent_technical_regulation1_serverRole1: return p->x.technical_regulation1_serverRole1;
		case Iso14827TestConfigurationPresent_technical_regulation2_clientRole: return p->x.technical_regulation2_clientRole;
		case Iso14827TestConfigurationPresent_technical_regulation1_clientRole2: return p->x.technical_regulation1_clientRole2;
		case Iso14827TestConfigurationPresent_technical_regulation1_serverRole2: return p->x.technical_regulation1_serverRole2;
		case Iso14827TestConfigurationPresent_technical_regulation1_duoClientRole: return p->x.technical_regulation1_duoClientRole;
		case Iso14827TestConfigurationPresent_technical_regulation1_duoSessionRole: return p->x.technical_regulation1_duoSessionRole;
		case Iso14827TestConfigurationPresent_technical_regulation2_clientRole2: return p->x.technical_regulation2_clientRole2;
		case Iso14827TestConfigurationPresent_technical_regulation2_serverRole2: return p->x.technical_regulation2_serverRole2;
		case Iso14827TestConfigurationPresent_technical_regulation2_duoClientRole: return p->x.technical_regulation2_duoClientRole;
		case Iso14827TestConfigurationPresent_technical_regulation2_duoSessionRole: return p->x.technical_regulation2_duoSessionRole;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Iso14827TestConfiguration_membs[] =
{
	{ Dz1Text("centerClient2rse"), Dz1Text("PolicePrj4TestConfiguration_centerClient2rse"), Iso14827TestConfigurationPresent_centerClient2rse },
	{ Dz1Text("rseServer2center"), Dz1Text("PolicePrj4TestConfiguration_rseServer2center"), Iso14827TestConfigurationPresent_rseServer2center },
	{ Dz1Text("rseClient2center"), Dz1Text("PolicePrj4TestConfiguration_rseClient2center"), Iso14827TestConfigurationPresent_rseClient2center },
	{ Dz1Text("centerServer2rse"), Dz1Text("PolicePrj4TestConfiguration_centerServer2rse"), Iso14827TestConfigurationPresent_centerServer2rse },
	{ Dz1Text("signalserver2center"), Dz1Text("PolicePrj4TestConfiguration_signalserverServer2center"), Iso14827TestConfigurationPresent_signalserver2center },
	{ Dz1Text("itsk00100_3c2cClient"), Dz1Text("ITSK00100_3TestConfigurationClientRole"), Iso14827TestConfigurationPresent_itsk00100_3c2cClient },
	{ Dz1Text("itsk00100_3c2cServer"), Dz1Text("ITSK00100_3TestConfigurationServerRole"), Iso14827TestConfigurationPresent_itsk00100_3c2cServer },
	{ Dz1Text("technical_regulation1_clientRole1"), Dz1Text("TechnicalRegulation1TestConfiguration_clientRole1"), Iso14827TestConfigurationPresent_technical_regulation1_clientRole1 },
	{ Dz1Text("technical_regulation1_serverRole1"), Dz1Text("TechnicalRegulation1TestConfiguration_serverRole1"), Iso14827TestConfigurationPresent_technical_regulation1_serverRole1 },
	{ Dz1Text("technical_regulation2_clientRole"), Dz1Text("TechnicalRegulation2TestConfiguration_clientRole1"), Iso14827TestConfigurationPresent_technical_regulation2_clientRole },
	{ Dz1Text("technical_regulation1_clientRole2"), Dz1Text("TechnicalRegulationTestConfiguration_clientRole2"), Iso14827TestConfigurationPresent_technical_regulation1_clientRole2 },
	{ Dz1Text("technical_regulation1_serverRole2"), Dz1Text("TechnicalRegulationTestConfiguration_serverRole2"), Iso14827TestConfigurationPresent_technical_regulation1_serverRole2 },
	{ Dz1Text("technical_regulation1_duoClientRole"), Dz1Text("TechnicalRegulationTestConfiguration_duoClientRole"), Iso14827TestConfigurationPresent_technical_regulation1_duoClientRole },
	{ Dz1Text("technical_regulation1_duoSessionRole"), Dz1Text("TechnicalRegulationTestConfiguration_duoSessionRole"), Iso14827TestConfigurationPresent_technical_regulation1_duoSessionRole },
	{ Dz1Text("technical_regulation2_clientRole2"), Dz1Text("TechnicalRegulationTestConfiguration_clientRole2"), Iso14827TestConfigurationPresent_technical_regulation2_clientRole2 },
	{ Dz1Text("technical_regulation2_serverRole2"), Dz1Text("TechnicalRegulationTestConfiguration_serverRole2"), Iso14827TestConfigurationPresent_technical_regulation2_serverRole2 },
	{ Dz1Text("technical_regulation2_duoClientRole"), Dz1Text("TechnicalRegulationTestConfiguration_duoClientRole"), Iso14827TestConfigurationPresent_technical_regulation2_duoClientRole },
	{ Dz1Text("technical_regulation2_duoSessionRole"), Dz1Text("TechnicalRegulationTestConfiguration_duoSessionRole"), Iso14827TestConfigurationPresent_technical_regulation2_duoSessionRole },
	{ NULL, NULL, -1 }
};
// Iso14827TestConfiguration
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TimeFrac
static bool_t Iso14827TimeFrac_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TimeFrac *p = (Iso14827TimeFrac *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case Iso14827TimeFracPresent_deci: p->x.deci = *(s32_t *)info->data; break;
	case Iso14827TimeFracPresent_centi: p->x.centi = *(s32_t *)info->data; break;
	case Iso14827TimeFracPresent_milli: p->x.milli = *(s32_t *)info->data; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (Iso14827TimeFracPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Iso14827TimeFrac_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Iso14827TimeFrac *p = (Iso14827TimeFrac *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case Iso14827TimeFracPresent_deci: return &p->x.deci;
		case Iso14827TimeFracPresent_centi: return &p->x.centi;
		case Iso14827TimeFracPresent_milli: return &p->x.milli;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild Iso14827TimeFrac_membs[] =
{
	{ Dz1Text("deci"), Dz1Text("s32_t"), Iso14827TimeFracPresent_deci },
	{ Dz1Text("centi"), Dz1Text("s32_t"), Iso14827TimeFracPresent_centi },
	{ Dz1Text("milli"), Dz1Text("s32_t"), Iso14827TimeFracPresent_milli },
	{ NULL, NULL, -1 }
};
// Iso14827TimeFrac
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827TimeZone
static bool_t Iso14827TimeZone_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827TimeZone *p = (Iso14827TimeZone *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->modH =  *(s32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->modM =  *(s32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Iso14827TimeZone_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Iso14827TimeZone *p = (Iso14827TimeZone *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->modH;
	case 1: return &p->modM;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Iso14827TimeZone_membs[] =
{
	{ Dz1Text("modH"), Dz1Text("s32_t"), 0 },
	{ Dz1Text("modM"), Dz1Text("s32_t"), 1 },
	{ NULL, NULL, -1 }
};
// Iso14827TimeZone
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827Time
static bool_t Iso14827Time_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827Time *p = (Iso14827Time *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: s32_t_delAndSetNull(&p->year); p->year = (s32_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: s32_t_delAndSetNull(&p->month); p->month = (s32_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: s32_t_delAndSetNull(&p->day); p->day = (s32_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: p->h =  *(s32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->m =  *(s32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->s =  *(s32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: Iso14827TimeFrac_delAndSetNull(&p->frac); p->frac = (Iso14827TimeFrac *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 7: Iso14827TimeZone_delAndSetNull(&p->zone); p->zone = (Iso14827TimeZone *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Iso14827Time_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Iso14827Time *p = (Iso14827Time *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->year;
	case 1: return p->month;
	case 2: return p->day;
	case 3: return &p->h;
	case 4: return &p->m;
	case 5: return &p->s;
	case 6: return p->frac;
	case 7: return p->zone;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Iso14827Time_membs[] =
{
	{ Dz1Text("year"), Dz1Text("s32_t"), 0 },
	{ Dz1Text("month"), Dz1Text("s32_t"), 1 },
	{ Dz1Text("day"), Dz1Text("s32_t"), 2 },
	{ Dz1Text("h"), Dz1Text("s32_t"), 3 },
	{ Dz1Text("m"), Dz1Text("s32_t"), 4 },
	{ Dz1Text("s"), Dz1Text("s32_t"), 5 },
	{ Dz1Text("frac"), Dz1Text("Iso14827TimeFrac"), 6 },
	{ Dz1Text("zone"), Dz1Text("Iso14827TimeZone"), 7 },
	{ NULL, NULL, -1 }
};
// Iso14827Time
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827RegisteredContinuous
static bool_t Iso14827RegisteredContinuous_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827RegisteredContinuous *p = (Iso14827RegisteredContinuous *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->updateDelay =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: Iso14827Time_delAndSetNull(&p->start); p->start = (Iso14827Time *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: Iso14827Time_delAndSetNull(&p->end); p->end = (Iso14827Time *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Iso14827RegisteredContinuous_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Iso14827RegisteredContinuous *p = (Iso14827RegisteredContinuous *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->updateDelay;
	case 1: return p->start;
	case 2: return p->end;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Iso14827RegisteredContinuous_membs[] =
{
	{ Dz1Text("updateDelay"), Dz1Text("u32_t"), 0 },
	{ Dz1Text("start"), Dz1Text("Iso14827Time"), 1 },
	{ Dz1Text("end"), Dz1Text("Iso14827Time"), 2 },
	{ NULL, NULL, -1 }
};
// Iso14827RegisteredContinuous
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827RegisteredDaily
static bool_t Iso14827RegisteredDaily_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827RegisteredDaily *p = (Iso14827RegisteredDaily *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->updateDelay =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->daysOfWeek =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: Iso14827Time_delAndSetNull(&p->startDate); p->startDate = (Iso14827Time *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: Iso14827Time_delAndSetNull(&p->endDate); p->endDate = (Iso14827Time *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 4: Iso14827Time_delAndSetNull(&p->startTime); p->startTime = (Iso14827Time *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 5: u16_t_delAndSetNull(&p->duration); p->duration = (u16_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *Iso14827RegisteredDaily_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	Iso14827RegisteredDaily *p = (Iso14827RegisteredDaily *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->updateDelay;
	case 1: return &p->daysOfWeek;
	case 2: return p->startDate;
	case 3: return p->endDate;
	case 4: return p->startTime;
	case 5: return p->duration;
	default: return NULL;
	}
}

static Dz1JsonSpecChild Iso14827RegisteredDaily_membs[] =
{
	{ Dz1Text("updateDelay"), Dz1Text("u32_t"), 0 },
	{ Dz1Text("daysOfWeek"), Dz1Text("u8_t"), 1 },
	{ Dz1Text("startDate"), Dz1Text("Iso14827Time"), 2 },
	{ Dz1Text("endDate"), Dz1Text("Iso14827Time"), 3 },
	{ Dz1Text("startTime"), Dz1Text("Iso14827Time"), 4 },
	{ Dz1Text("duration"), Dz1Text("u16_t"), 5 },
	{ NULL, NULL, -1 }
};
// Iso14827RegisteredDaily
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SubscribeSpecTypeReg
static bool_t SubscribeSpecTypeReg_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SubscribeSpecTypeReg *p = (SubscribeSpecTypeReg *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case SubscribeSpecTypeRegPresent_continuous: Iso14827RegisteredContinuous_delAndSetNull(&p->x.continuous); p->x.continuous =(Iso14827RegisteredContinuous *)info->data; info->data = NULL; break;
	case SubscribeSpecTypeRegPresent_daily: Iso14827RegisteredDaily_delAndSetNull(&p->x.daily); p->x.daily =(Iso14827RegisteredDaily *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (SubscribeSpecTypeRegPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *SubscribeSpecTypeReg_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	SubscribeSpecTypeReg *p = (SubscribeSpecTypeReg *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case SubscribeSpecTypeRegPresent_continuous: return p->x.continuous;
		case SubscribeSpecTypeRegPresent_daily: return p->x.daily;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild SubscribeSpecTypeReg_membs[] =
{
	{ Dz1Text("continuous"), Dz1Text("Iso14827RegisteredContinuous"), SubscribeSpecTypeRegPresent_continuous },
	{ Dz1Text("daily"), Dz1Text("Iso14827RegisteredDaily"), SubscribeSpecTypeRegPresent_daily },
	{ NULL, NULL, -1 }
};
// SubscribeSpecTypeReg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Iso14827SubscriptionCancel
static bool_t Iso14827SubscriptionCancel_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Iso14827SubscriptionCancel v = Iso14827SubscriptionCancel_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (Iso14827SubscriptionCancel)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = Iso14827SubscriptionCancelFromStr(tok->v)) == Iso14827SubscriptionCancel_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = Iso14827SubscriptionCancel_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Iso14827SubscriptionCancel_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Iso14827SubscriptionCancel v = *(Iso14827SubscriptionCancel *)obj;
		Dz1Str str_v = Iso14827SubscriptionCancelStr(v);
		if (str_v == NULL)
		{
			if (Dz1JsonUtil_stringify_u32(buf, (u32_t)v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1JsonUtil_stringify_quotstr(buf, str_v, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Iso14827SubscriptionCancel
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SubscribeSpecTypeRegistered
static bool_t SubscribeSpecTypeRegistered_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SubscribeSpecTypeRegistered *p = (SubscribeSpecTypeRegistered *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->is_periodic =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: SubscribeSpecTypeReg_delAndSetNull(&p->reg_info); p->reg_info = (SubscribeSpecTypeReg *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: p->when_cancel =  *(Iso14827SubscriptionCancel *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *SubscribeSpecTypeRegistered_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	SubscribeSpecTypeRegistered *p = (SubscribeSpecTypeRegistered *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->is_periodic;
	case 1: return p->reg_info;
	case 2: return &p->when_cancel;
	default: return NULL;
	}
}

static Dz1JsonSpecChild SubscribeSpecTypeRegistered_membs[] =
{
	{ Dz1Text("is_periodic"), Dz1Text("bool_t"), 0 },
	{ Dz1Text("reg_info"), Dz1Text("SubscribeSpecTypeReg"), 1 },
	{ Dz1Text("when_cancel"), Dz1Text("Iso14827SubscriptionCancel"), 2 },
	{ NULL, NULL, -1 }
};
// SubscribeSpecTypeRegistered
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SubscribeSpecType
static bool_t SubscribeSpecType_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SubscribeSpecType *p = (SubscribeSpecType *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case SubscribeSpecTypePresent_single: p->x.single = *(u32_t *)info->data; break;
	case SubscribeSpecTypePresent_registered: SubscribeSpecTypeRegistered_delAndSetNull(&p->x.registered); p->x.registered =(SubscribeSpecTypeRegistered *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (SubscribeSpecTypePresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *SubscribeSpecType_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	SubscribeSpecType *p = (SubscribeSpecType *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case SubscribeSpecTypePresent_single: return &p->x.single;
		case SubscribeSpecTypePresent_registered: return p->x.registered;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild SubscribeSpecType_membs[] =
{
	{ Dz1Text("single"), Dz1Text("u32_t"), SubscribeSpecTypePresent_single },
	{ Dz1Text("registered"), Dz1Text("SubscribeSpecTypeRegistered"), SubscribeSpecTypePresent_registered },
	{ NULL, NULL, -1 }
};
// SubscribeSpecType
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SubscribeSpecEntry
static bool_t SubscribeSpecEntry_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SubscribeSpecEntry *p = (SubscribeSpecEntry *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->oid); p->oid = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->priority =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: SubscribeSpecType_delAndSetNull(&p->type); p->type = (SubscribeSpecType *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *SubscribeSpecEntry_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	SubscribeSpecEntry *p = (SubscribeSpecEntry *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->oid;
	case 1: return &p->priority;
	case 2: return p->type;
	default: return NULL;
	}
}

static Dz1JsonSpecChild SubscribeSpecEntry_membs[] =
{
	{ Dz1Text("oid"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("priority"), Dz1Text("u8_t"), 1 },
	{ Dz1Text("type"), Dz1Text("SubscribeSpecType"), 2 },
	{ NULL, NULL, -1 }
};
// SubscribeSpecEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SubscribeSpecList
static bool_t SubscribeSpecList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SubscribeSpecList *dst = (SubscribeSpecList *)dst_ptr;
	SubscribeSpecEntry *node = NULL;
	if (dst == NULL || var == NULL || (node = (SubscribeSpecEntry *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t SubscribeSpecList_cnt(void *ptr)
{
	u32_t ret = 0;
	SubscribeSpecList *list = (SubscribeSpecList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error SubscribeSpecList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	SubscribeSpecList *list = (SubscribeSpecList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// SubscribeSpecList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CurrentLinkStateEntry
static bool_t CurrentLinkStateEntry_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CurrentLinkStateEntry *p = (CurrentLinkStateEntry *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->link_id); p->link_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->speed_rate =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->volume_rate =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->density_rate =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->ttime_qty =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->delay_qty =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->veh_q_len_qty =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->tfdt_occupy_percent =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *CurrentLinkStateEntry_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	CurrentLinkStateEntry *p = (CurrentLinkStateEntry *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->link_id;
	case 1: return &p->speed_rate;
	case 2: return &p->volume_rate;
	case 3: return &p->density_rate;
	case 4: return &p->ttime_qty;
	case 5: return &p->delay_qty;
	case 6: return &p->veh_q_len_qty;
	case 7: return &p->tfdt_occupy_percent;
	default: return NULL;
	}
}

static Dz1JsonSpecChild CurrentLinkStateEntry_membs[] =
{
	{ Dz1Text("link_id"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("speed_rate"), Dz1Text("u16_t"), 1 },
	{ Dz1Text("volume_rate"), Dz1Text("u32_t"), 2 },
	{ Dz1Text("density_rate"), Dz1Text("u16_t"), 3 },
	{ Dz1Text("ttime_qty"), Dz1Text("u16_t"), 4 },
	{ Dz1Text("delay_qty"), Dz1Text("u16_t"), 5 },
	{ Dz1Text("veh_q_len_qty"), Dz1Text("u32_t"), 6 },
	{ Dz1Text("tfdt_occupy_percent"), Dz1Text("u8_t"), 7 },
	{ NULL, NULL, -1 }
};
// CurrentLinkStateEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CurrentLinkStateList
static bool_t CurrentLinkStateList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CurrentLinkStateList *dst = (CurrentLinkStateList *)dst_ptr;
	CurrentLinkStateEntry *node = NULL;
	if (dst == NULL || var == NULL || (node = (CurrentLinkStateEntry *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t CurrentLinkStateList_cnt(void *ptr)
{
	u32_t ret = 0;
	CurrentLinkStateList *list = (CurrentLinkStateList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error CurrentLinkStateList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CurrentLinkStateList *list = (CurrentLinkStateList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// CurrentLinkStateList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// EventIdentityEntry
static bool_t EventIdentityEntry_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	EventIdentityEntry *p = (EventIdentityEntry *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->node_id); p->node_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->link_id); p->link_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: p->identification_num =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: Dz1Str_delAndSetNull(&p->loc_jurisdiction_name); p->loc_jurisdiction_name = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 4: Dz1Str_delAndSetNull(&p->loc_link_id); p->loc_link_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 5: Dz1Str_delAndSetNull(&p->loc_node_id); p->loc_node_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 6: Dz1Str_delAndSetNull(&p->loc_roadway_name); p->loc_roadway_name = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 7: p->evnt_code =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->special_evnt_code =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 9: p->planned_road_closure_code =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 10: p->lanes_blocked_or_closed_num =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 11: u8_t_delAndSetNull(&p->lanes_shoulder_block_code); p->lanes_shoulder_block_code = (u8_t *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 12: Dz1Str_delAndSetNull(&p->start_time); p->start_time = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 13: Dz1Str_delAndSetNull(&p->end_time); p->end_time = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 14: p->time_duration =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *EventIdentityEntry_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	EventIdentityEntry *p = (EventIdentityEntry *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->node_id;
	case 1: return p->link_id;
	case 2: return &p->identification_num;
	case 3: return p->loc_jurisdiction_name;
	case 4: return p->loc_link_id;
	case 5: return p->loc_node_id;
	case 6: return p->loc_roadway_name;
	case 7: return &p->evnt_code;
	case 8: return &p->special_evnt_code;
	case 9: return &p->planned_road_closure_code;
	case 10: return &p->lanes_blocked_or_closed_num;
	case 11: return p->lanes_shoulder_block_code;
	case 12: return p->start_time;
	case 13: return p->end_time;
	case 14: return &p->time_duration;
	default: return NULL;
	}
}

static Dz1JsonSpecChild EventIdentityEntry_membs[] =
{
	{ Dz1Text("node_id"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("link_id"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("identification_num"), Dz1Text("u32_t"), 2 },
	{ Dz1Text("loc_jurisdiction_name"), Dz1Text("Dz1Str"), 3 },
	{ Dz1Text("loc_link_id"), Dz1Text("Dz1Str"), 4 },
	{ Dz1Text("loc_node_id"), Dz1Text("Dz1Str"), 5 },
	{ Dz1Text("loc_roadway_name"), Dz1Text("Dz1Str"), 6 },
	{ Dz1Text("evnt_code"), Dz1Text("u8_t"), 7 },
	{ Dz1Text("special_evnt_code"), Dz1Text("u8_t"), 8 },
	{ Dz1Text("planned_road_closure_code"), Dz1Text("u8_t"), 9 },
	{ Dz1Text("lanes_blocked_or_closed_num"), Dz1Text("u8_t"), 10 },
	{ Dz1Text("lanes_shoulder_block_code"), Dz1Text("u8_t"), 11 },
	{ Dz1Text("start_time"), Dz1Text("Dz1Str"), 12 },
	{ Dz1Text("end_time"), Dz1Text("Dz1Str"), 13 },
	{ Dz1Text("time_duration"), Dz1Text("u32_t"), 14 },
	{ NULL, NULL, -1 }
};
// EventIdentityEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// EventIdentityList
static bool_t EventIdentityList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	EventIdentityList *dst = (EventIdentityList *)dst_ptr;
	EventIdentityEntry *node = NULL;
	if (dst == NULL || var == NULL || (node = (EventIdentityEntry *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t EventIdentityList_cnt(void *ptr)
{
	u32_t ret = 0;
	EventIdentityList *list = (EventIdentityList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error EventIdentityList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	EventIdentityList *list = (EventIdentityList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// EventIdentityList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// IncidentIdentityEntry
static bool_t IncidentIdentityEntry_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	IncidentIdentityEntry *p = (IncidentIdentityEntry *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->node_id); p->node_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->link_id); p->link_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: p->loc_offset_begin =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->loc_offset_end =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: Dz1Str_delAndSetNull(&p->update_time); p->update_time = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 5: p->fatality_cnt =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->injuries_cnt =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->property_damage_code =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: Dz1Str_delAndSetNull(&p->property_damage_desc); p->property_damage_desc = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *IncidentIdentityEntry_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	IncidentIdentityEntry *p = (IncidentIdentityEntry *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->node_id;
	case 1: return p->link_id;
	case 2: return &p->loc_offset_begin;
	case 3: return &p->loc_offset_end;
	case 4: return p->update_time;
	case 5: return &p->fatality_cnt;
	case 6: return &p->injuries_cnt;
	case 7: return &p->property_damage_code;
	case 8: return p->property_damage_desc;
	default: return NULL;
	}
}

static Dz1JsonSpecChild IncidentIdentityEntry_membs[] =
{
	{ Dz1Text("node_id"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("link_id"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("loc_offset_begin"), Dz1Text("u16_t"), 2 },
	{ Dz1Text("loc_offset_end"), Dz1Text("u16_t"), 3 },
	{ Dz1Text("update_time"), Dz1Text("Dz1Str"), 4 },
	{ Dz1Text("fatality_cnt"), Dz1Text("u8_t"), 5 },
	{ Dz1Text("injuries_cnt"), Dz1Text("u8_t"), 6 },
	{ Dz1Text("property_damage_code"), Dz1Text("u8_t"), 7 },
	{ Dz1Text("property_damage_desc"), Dz1Text("Dz1Str"), 8 },
	{ NULL, NULL, -1 }
};
// IncidentIdentityEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// IncidentIdentityList
static bool_t IncidentIdentityList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	IncidentIdentityList *dst = (IncidentIdentityList *)dst_ptr;
	IncidentIdentityEntry *node = NULL;
	if (dst == NULL || var == NULL || (node = (IncidentIdentityEntry *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t IncidentIdentityList_cnt(void *ptr)
{
	u32_t ret = 0;
	IncidentIdentityList *list = (IncidentIdentityList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error IncidentIdentityList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	IncidentIdentityList *list = (IncidentIdentityList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// IncidentIdentityList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// IncidentConditionsEntry
static bool_t IncidentConditionsEntry_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	IncidentConditionsEntry *p = (IncidentConditionsEntry *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->node_id); p->node_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->link_id); p->link_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->contact_org_name); p->contact_org_name = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 3: p->incident_code =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: Dz1Str_delAndSetNull(&p->other_incident_desc); p->other_incident_desc = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 5: p->veh_invloved_code =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: Dz1Str_delAndSetNull(&p->other_veh_invloved_desc); p->other_veh_invloved_desc = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 7: p->status_code =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: Dz1Str_delAndSetNull(&p->other_status_desc); p->other_status_desc = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 9: p->update_type_code =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 10: Dz1Str_delAndSetNull(&p->other_update_desc); p->other_update_desc = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *IncidentConditionsEntry_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	IncidentConditionsEntry *p = (IncidentConditionsEntry *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->node_id;
	case 1: return p->link_id;
	case 2: return p->contact_org_name;
	case 3: return &p->incident_code;
	case 4: return p->other_incident_desc;
	case 5: return &p->veh_invloved_code;
	case 6: return p->other_veh_invloved_desc;
	case 7: return &p->status_code;
	case 8: return p->other_status_desc;
	case 9: return &p->update_type_code;
	case 10: return p->other_update_desc;
	default: return NULL;
	}
}

static Dz1JsonSpecChild IncidentConditionsEntry_membs[] =
{
	{ Dz1Text("node_id"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("link_id"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("contact_org_name"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("incident_code"), Dz1Text("u8_t"), 3 },
	{ Dz1Text("other_incident_desc"), Dz1Text("Dz1Str"), 4 },
	{ Dz1Text("veh_invloved_code"), Dz1Text("u8_t"), 5 },
	{ Dz1Text("other_veh_invloved_desc"), Dz1Text("Dz1Str"), 6 },
	{ Dz1Text("status_code"), Dz1Text("u8_t"), 7 },
	{ Dz1Text("other_status_desc"), Dz1Text("Dz1Str"), 8 },
	{ Dz1Text("update_type_code"), Dz1Text("u8_t"), 9 },
	{ Dz1Text("other_update_desc"), Dz1Text("Dz1Str"), 10 },
	{ NULL, NULL, -1 }
};
// IncidentConditionsEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// IncidentConditionsList
static bool_t IncidentConditionsList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	IncidentConditionsList *dst = (IncidentConditionsList *)dst_ptr;
	IncidentConditionsEntry *node = NULL;
	if (dst == NULL || var == NULL || (node = (IncidentConditionsEntry *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t IncidentConditionsList_cnt(void *ptr)
{
	u32_t ret = 0;
	IncidentConditionsList *list = (IncidentConditionsList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error IncidentConditionsList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	IncidentConditionsList *list = (IncidentConditionsList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// IncidentConditionsList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// RoadwaySurfaceStatusEntry
static bool_t RoadwaySurfaceStatusEntry_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	RoadwaySurfaceStatusEntry *p = (RoadwaySurfaceStatusEntry *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->node_id); p->node_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->link_id); p->link_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: p->surface_cond_code =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->land_blocked_or_closed_code =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->precipitation_depth =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->temperature_qty =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *RoadwaySurfaceStatusEntry_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	RoadwaySurfaceStatusEntry *p = (RoadwaySurfaceStatusEntry *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->node_id;
	case 1: return p->link_id;
	case 2: return &p->surface_cond_code;
	case 3: return &p->land_blocked_or_closed_code;
	case 4: return &p->precipitation_depth;
	case 5: return &p->temperature_qty;
	default: return NULL;
	}
}

static Dz1JsonSpecChild RoadwaySurfaceStatusEntry_membs[] =
{
	{ Dz1Text("node_id"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("link_id"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("surface_cond_code"), Dz1Text("u8_t"), 2 },
	{ Dz1Text("land_blocked_or_closed_code"), Dz1Text("u8_t"), 3 },
	{ Dz1Text("precipitation_depth"), Dz1Text("u16_t"), 4 },
	{ Dz1Text("temperature_qty"), Dz1Text("u16_t"), 5 },
	{ NULL, NULL, -1 }
};
// RoadwaySurfaceStatusEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// RoadwaySurfaceStatusList
static bool_t RoadwaySurfaceStatusList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	RoadwaySurfaceStatusList *dst = (RoadwaySurfaceStatusList *)dst_ptr;
	RoadwaySurfaceStatusEntry *node = NULL;
	if (dst == NULL || var == NULL || (node = (RoadwaySurfaceStatusEntry *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t RoadwaySurfaceStatusList_cnt(void *ptr)
{
	u32_t ret = 0;
	RoadwaySurfaceStatusList *list = (RoadwaySurfaceStatusList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error RoadwaySurfaceStatusList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	RoadwaySurfaceStatusList *list = (RoadwaySurfaceStatusList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// RoadwaySurfaceStatusList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// WeatherInformationEntry
static bool_t WeatherInformationEntry_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	WeatherInformationEntry *p = (WeatherInformationEntry *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->forecast_or_actual =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->temperature =  *(s8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->high_temperature =  *(s8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->low_temperature =  *(s8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->special_cond =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: Dz1Str_delAndSetNull(&p->other_cond_desc); p->other_cond_desc = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 6: p->probability =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->visibility =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->wind_speed =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 9: p->wind_direct_code =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 10: p->humidity =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 11: p->pressure =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 12: Dz1Str_delAndSetNull(&p->sunrise_time); p->sunrise_time = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 13: Dz1Str_delAndSetNull(&p->sunset_time); p->sunset_time = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *WeatherInformationEntry_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	WeatherInformationEntry *p = (WeatherInformationEntry *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->forecast_or_actual;
	case 1: return &p->temperature;
	case 2: return &p->high_temperature;
	case 3: return &p->low_temperature;
	case 4: return &p->special_cond;
	case 5: return p->other_cond_desc;
	case 6: return &p->probability;
	case 7: return &p->visibility;
	case 8: return &p->wind_speed;
	case 9: return &p->wind_direct_code;
	case 10: return &p->humidity;
	case 11: return &p->pressure;
	case 12: return p->sunrise_time;
	case 13: return p->sunset_time;
	default: return NULL;
	}
}

static Dz1JsonSpecChild WeatherInformationEntry_membs[] =
{
	{ Dz1Text("forecast_or_actual"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("temperature"), Dz1Text("s8_t"), 1 },
	{ Dz1Text("high_temperature"), Dz1Text("s8_t"), 2 },
	{ Dz1Text("low_temperature"), Dz1Text("s8_t"), 3 },
	{ Dz1Text("special_cond"), Dz1Text("u8_t"), 4 },
	{ Dz1Text("other_cond_desc"), Dz1Text("Dz1Str"), 5 },
	{ Dz1Text("probability"), Dz1Text("u8_t"), 6 },
	{ Dz1Text("visibility"), Dz1Text("u8_t"), 7 },
	{ Dz1Text("wind_speed"), Dz1Text("u8_t"), 8 },
	{ Dz1Text("wind_direct_code"), Dz1Text("u8_t"), 9 },
	{ Dz1Text("humidity"), Dz1Text("u8_t"), 10 },
	{ Dz1Text("pressure"), Dz1Text("u8_t"), 11 },
	{ Dz1Text("sunrise_time"), Dz1Text("Dz1Str"), 12 },
	{ Dz1Text("sunset_time"), Dz1Text("Dz1Str"), 13 },
	{ NULL, NULL, -1 }
};
// WeatherInformationEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// WeatherInformationList
static bool_t WeatherInformationList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	WeatherInformationList *dst = (WeatherInformationList *)dst_ptr;
	WeatherInformationEntry *node = NULL;
	if (dst == NULL || var == NULL || (node = (WeatherInformationEntry *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t WeatherInformationList_cnt(void *ptr)
{
	u32_t ret = 0;
	WeatherInformationList *list = (WeatherInformationList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error WeatherInformationList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	WeatherInformationList *list = (WeatherInformationList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// WeatherInformationList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// LinkRoadwayGeometryEntry
static bool_t LinkRoadwayGeometryEntry_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	LinkRoadwayGeometryEntry *p = (LinkRoadwayGeometryEntry *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->begin_node_id); p->begin_node_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->begin_node_latitude =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->begin_node_longitude =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: Dz1Str_delAndSetNull(&p->end_node_id); p->end_node_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 4: p->end_node_latitude =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->end_node_longitude =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: Dz1Str_delAndSetNull(&p->jurisdiction); p->jurisdiction = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 7: p->type_code =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: Dz1Str_delAndSetNull(&p->name); p->name = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 9: p->length =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 10: p->pavement_type_code =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 11: p->restriction_height =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 12: p->left_shoulder_width =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 13: p->restriction_length =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 14: p->median_type_code =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 15: p->num_lanes =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 16: p->num_open_lanes =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 17: p->right_shoulder_width =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *LinkRoadwayGeometryEntry_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	LinkRoadwayGeometryEntry *p = (LinkRoadwayGeometryEntry *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->begin_node_id;
	case 1: return &p->begin_node_latitude;
	case 2: return &p->begin_node_longitude;
	case 3: return p->end_node_id;
	case 4: return &p->end_node_latitude;
	case 5: return &p->end_node_longitude;
	case 6: return p->jurisdiction;
	case 7: return &p->type_code;
	case 8: return p->name;
	case 9: return &p->length;
	case 10: return &p->pavement_type_code;
	case 11: return &p->restriction_height;
	case 12: return &p->left_shoulder_width;
	case 13: return &p->restriction_length;
	case 14: return &p->median_type_code;
	case 15: return &p->num_lanes;
	case 16: return &p->num_open_lanes;
	case 17: return &p->right_shoulder_width;
	default: return NULL;
	}
}

static Dz1JsonSpecChild LinkRoadwayGeometryEntry_membs[] =
{
	{ Dz1Text("begin_node_id"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("begin_node_latitude"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("begin_node_longitude"), Dz1Text("u32_t"), 2 },
	{ Dz1Text("end_node_id"), Dz1Text("Dz1Str"), 3 },
	{ Dz1Text("end_node_latitude"), Dz1Text("s64_t"), 4 },
	{ Dz1Text("end_node_longitude"), Dz1Text("u32_t"), 5 },
	{ Dz1Text("jurisdiction"), Dz1Text("Dz1Str"), 6 },
	{ Dz1Text("type_code"), Dz1Text("u8_t"), 7 },
	{ Dz1Text("name"), Dz1Text("Dz1Str"), 8 },
	{ Dz1Text("length"), Dz1Text("u32_t"), 9 },
	{ Dz1Text("pavement_type_code"), Dz1Text("u8_t"), 10 },
	{ Dz1Text("restriction_height"), Dz1Text("u16_t"), 11 },
	{ Dz1Text("left_shoulder_width"), Dz1Text("u16_t"), 12 },
	{ Dz1Text("restriction_length"), Dz1Text("u16_t"), 13 },
	{ Dz1Text("median_type_code"), Dz1Text("u8_t"), 14 },
	{ Dz1Text("num_lanes"), Dz1Text("u16_t"), 15 },
	{ Dz1Text("num_open_lanes"), Dz1Text("u8_t"), 16 },
	{ Dz1Text("right_shoulder_width"), Dz1Text("u16_t"), 17 },
	{ NULL, NULL, -1 }
};
// LinkRoadwayGeometryEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// LinkRoadwayGeometryList
static bool_t LinkRoadwayGeometryList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	LinkRoadwayGeometryList *dst = (LinkRoadwayGeometryList *)dst_ptr;
	LinkRoadwayGeometryEntry *node = NULL;
	if (dst == NULL || var == NULL || (node = (LinkRoadwayGeometryEntry *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t LinkRoadwayGeometryList_cnt(void *ptr)
{
	u32_t ret = 0;
	LinkRoadwayGeometryList *list = (LinkRoadwayGeometryList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error LinkRoadwayGeometryList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	LinkRoadwayGeometryList *list = (LinkRoadwayGeometryList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// LinkRoadwayGeometryList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ProbeVehicleDetectionEntry
static bool_t ProbeVehicleDetectionEntry_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ProbeVehicleDetectionEntry *p = (ProbeVehicleDetectionEntry *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->veh_id); p->veh_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->veh_class =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->veh_timein); p->veh_timein = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 3: Dz1Str_delAndSetNull(&p->veh_timeout); p->veh_timeout = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 4: p->veh_traveltime =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->veh_avg_speed =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: Dz1Str_delAndSetNull(&p->avi_id); p->avi_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 7: p->avi_latitude =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->avi_longitude =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 9: Dz1Str_delAndSetNull(&p->ref_avi_id); p->ref_avi_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 10: p->ref_avi_latitude =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 11: p->ref_avi_longitude =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ProbeVehicleDetectionEntry_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ProbeVehicleDetectionEntry *p = (ProbeVehicleDetectionEntry *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->veh_id;
	case 1: return &p->veh_class;
	case 2: return p->veh_timein;
	case 3: return p->veh_timeout;
	case 4: return &p->veh_traveltime;
	case 5: return &p->veh_avg_speed;
	case 6: return p->avi_id;
	case 7: return &p->avi_latitude;
	case 8: return &p->avi_longitude;
	case 9: return p->ref_avi_id;
	case 10: return &p->ref_avi_latitude;
	case 11: return &p->ref_avi_longitude;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ProbeVehicleDetectionEntry_membs[] =
{
	{ Dz1Text("veh_id"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("veh_class"), Dz1Text("u8_t"), 1 },
	{ Dz1Text("veh_timein"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("veh_timeout"), Dz1Text("Dz1Str"), 3 },
	{ Dz1Text("veh_traveltime"), Dz1Text("u16_t"), 4 },
	{ Dz1Text("veh_avg_speed"), Dz1Text("u16_t"), 5 },
	{ Dz1Text("avi_id"), Dz1Text("Dz1Str"), 6 },
	{ Dz1Text("avi_latitude"), Dz1Text("s64_t"), 7 },
	{ Dz1Text("avi_longitude"), Dz1Text("u32_t"), 8 },
	{ Dz1Text("ref_avi_id"), Dz1Text("Dz1Str"), 9 },
	{ Dz1Text("ref_avi_latitude"), Dz1Text("s64_t"), 10 },
	{ Dz1Text("ref_avi_longitude"), Dz1Text("u32_t"), 11 },
	{ NULL, NULL, -1 }
};
// ProbeVehicleDetectionEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ProbeVehicleDetectionList
static bool_t ProbeVehicleDetectionList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ProbeVehicleDetectionList *dst = (ProbeVehicleDetectionList *)dst_ptr;
	ProbeVehicleDetectionEntry *node = NULL;
	if (dst == NULL || var == NULL || (node = (ProbeVehicleDetectionEntry *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t ProbeVehicleDetectionList_cnt(void *ptr)
{
	u32_t ret = 0;
	ProbeVehicleDetectionList *list = (ProbeVehicleDetectionList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error ProbeVehicleDetectionList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ProbeVehicleDetectionList *list = (ProbeVehicleDetectionList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// ProbeVehicleDetectionList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DetectorCollectionEntry
static bool_t DetectorCollectionEntry_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	DetectorCollectionEntry *p = (DetectorCollectionEntry *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->detector_id); p->detector_id = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->detector_time); p->detector_time = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: p->speed_rate =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->volume_rate =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->occupancy_percent =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->veh_q_len_qty =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *DetectorCollectionEntry_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	DetectorCollectionEntry *p = (DetectorCollectionEntry *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->detector_id;
	case 1: return p->detector_time;
	case 2: return &p->speed_rate;
	case 3: return &p->volume_rate;
	case 4: return &p->occupancy_percent;
	case 5: return &p->veh_q_len_qty;
	default: return NULL;
	}
}

static Dz1JsonSpecChild DetectorCollectionEntry_membs[] =
{
	{ Dz1Text("detector_id"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("detector_time"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("speed_rate"), Dz1Text("u16_t"), 2 },
	{ Dz1Text("volume_rate"), Dz1Text("u8_t"), 3 },
	{ Dz1Text("occupancy_percent"), Dz1Text("u8_t"), 4 },
	{ Dz1Text("veh_q_len_qty"), Dz1Text("u32_t"), 5 },
	{ NULL, NULL, -1 }
};
// DetectorCollectionEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DetectorCollectionList
static bool_t DetectorCollectionList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	DetectorCollectionList *dst = (DetectorCollectionList *)dst_ptr;
	DetectorCollectionEntry *node = NULL;
	if (dst == NULL || var == NULL || (node = (DetectorCollectionEntry *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t DetectorCollectionList_cnt(void *ptr)
{
	u32_t ret = 0;
	DetectorCollectionList *list = (DetectorCollectionList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error DetectorCollectionList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	DetectorCollectionList *list = (DetectorCollectionList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// DetectorCollectionList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ExtentionCommPDUEntry
static bool_t ExtentionCommPDUEntry_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ExtentionCommPDUEntry *p = (ExtentionCommPDUEntry *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->idx =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->aid =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->delivery_start =  *(time_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->delivery_stop =  *(time_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->signature =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->payload_type =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: Dz1Binary_delAndSetNull(&p->payload); p->payload = (Dz1Binary *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ExtentionCommPDUEntry_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ExtentionCommPDUEntry *p = (ExtentionCommPDUEntry *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->idx;
	case 1: return &p->aid;
	case 2: return &p->delivery_start;
	case 3: return &p->delivery_stop;
	case 4: return &p->signature;
	case 5: return &p->payload_type;
	case 6: return p->payload;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ExtentionCommPDUEntry_membs[] =
{
	{ Dz1Text("idx"), Dz1Text("u32_t"), 0 },
	{ Dz1Text("aid"), Dz1Text("u32_t"), 1 },
	{ Dz1Text("delivery_start"), Dz1Text("time_t"), 2 },
	{ Dz1Text("delivery_stop"), Dz1Text("time_t"), 3 },
	{ Dz1Text("signature"), Dz1Text("bool_t"), 4 },
	{ Dz1Text("payload_type"), Dz1Text("s64_t"), 5 },
	{ Dz1Text("payload"), Dz1Text("Dz1Binary"), 6 },
	{ NULL, NULL, -1 }
};
// ExtentionCommPDUEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ExtentionCommPDUList
static bool_t ExtentionCommPDUList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ExtentionCommPDUList *dst = (ExtentionCommPDUList *)dst_ptr;
	ExtentionCommPDUEntry *node = NULL;
	if (dst == NULL || var == NULL || (node = (ExtentionCommPDUEntry *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t ExtentionCommPDUList_cnt(void *ptr)
{
	u32_t ret = 0;
	ExtentionCommPDUList *list = (ExtentionCommPDUList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error ExtentionCommPDUList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	ExtentionCommPDUList *list = (ExtentionCommPDUList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// ExtentionCommPDUList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation1_Eam
static bool_t TechnicalRegulation1_Eam_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TechnicalRegulation1_Eam *p = (TechnicalRegulation1_Eam *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case TechnicalRegulation1_EamPresent_current_link_state: CurrentLinkStateList_delAndSetNull(&p->x.current_link_state); p->x.current_link_state =(CurrentLinkStateList *)info->data; info->data = NULL; break;
	case TechnicalRegulation1_EamPresent_event_identity: EventIdentityList_delAndSetNull(&p->x.event_identity); p->x.event_identity =(EventIdentityList *)info->data; info->data = NULL; break;
	case TechnicalRegulation1_EamPresent_incident_identity: IncidentIdentityList_delAndSetNull(&p->x.incident_identity); p->x.incident_identity =(IncidentIdentityList *)info->data; info->data = NULL; break;
	case TechnicalRegulation1_EamPresent_incident_conditions: IncidentConditionsList_delAndSetNull(&p->x.incident_conditions); p->x.incident_conditions =(IncidentConditionsList *)info->data; info->data = NULL; break;
	case TechnicalRegulation1_EamPresent_roadway_surface_status: RoadwaySurfaceStatusList_delAndSetNull(&p->x.roadway_surface_status); p->x.roadway_surface_status =(RoadwaySurfaceStatusList *)info->data; info->data = NULL; break;
	case TechnicalRegulation1_EamPresent_weather_information: WeatherInformationList_delAndSetNull(&p->x.weather_information); p->x.weather_information =(WeatherInformationList *)info->data; info->data = NULL; break;
	case TechnicalRegulation1_EamPresent_link_roadway_geometry: LinkRoadwayGeometryList_delAndSetNull(&p->x.link_roadway_geometry); p->x.link_roadway_geometry =(LinkRoadwayGeometryList *)info->data; info->data = NULL; break;
	case TechnicalRegulation1_EamPresent_probe_vehicle_detection: ProbeVehicleDetectionList_delAndSetNull(&p->x.probe_vehicle_detection); p->x.probe_vehicle_detection =(ProbeVehicleDetectionList *)info->data; info->data = NULL; break;
	case TechnicalRegulation1_EamPresent_detector_collection: DetectorCollectionList_delAndSetNull(&p->x.detector_collection); p->x.detector_collection =(DetectorCollectionList *)info->data; info->data = NULL; break;
	case TechnicalRegulation1_EamPresent_extention_comm_pdu: ExtentionCommPDUList_delAndSetNull(&p->x.extention_comm_pdu); p->x.extention_comm_pdu =(ExtentionCommPDUList *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (TechnicalRegulation1_EamPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *TechnicalRegulation1_Eam_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	TechnicalRegulation1_Eam *p = (TechnicalRegulation1_Eam *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case TechnicalRegulation1_EamPresent_current_link_state: return p->x.current_link_state;
		case TechnicalRegulation1_EamPresent_event_identity: return p->x.event_identity;
		case TechnicalRegulation1_EamPresent_incident_identity: return p->x.incident_identity;
		case TechnicalRegulation1_EamPresent_incident_conditions: return p->x.incident_conditions;
		case TechnicalRegulation1_EamPresent_roadway_surface_status: return p->x.roadway_surface_status;
		case TechnicalRegulation1_EamPresent_weather_information: return p->x.weather_information;
		case TechnicalRegulation1_EamPresent_link_roadway_geometry: return p->x.link_roadway_geometry;
		case TechnicalRegulation1_EamPresent_probe_vehicle_detection: return p->x.probe_vehicle_detection;
		case TechnicalRegulation1_EamPresent_detector_collection: return p->x.detector_collection;
		case TechnicalRegulation1_EamPresent_extention_comm_pdu: return p->x.extention_comm_pdu;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild TechnicalRegulation1_Eam_membs[] =
{
	{ Dz1Text("current_link_state"), Dz1Text("CurrentLinkStateList"), TechnicalRegulation1_EamPresent_current_link_state },
	{ Dz1Text("event_identity"), Dz1Text("EventIdentityList"), TechnicalRegulation1_EamPresent_event_identity },
	{ Dz1Text("incident_identity"), Dz1Text("IncidentIdentityList"), TechnicalRegulation1_EamPresent_incident_identity },
	{ Dz1Text("incident_conditions"), Dz1Text("IncidentConditionsList"), TechnicalRegulation1_EamPresent_incident_conditions },
	{ Dz1Text("roadway_surface_status"), Dz1Text("RoadwaySurfaceStatusList"), TechnicalRegulation1_EamPresent_roadway_surface_status },
	{ Dz1Text("weather_information"), Dz1Text("WeatherInformationList"), TechnicalRegulation1_EamPresent_weather_information },
	{ Dz1Text("link_roadway_geometry"), Dz1Text("LinkRoadwayGeometryList"), TechnicalRegulation1_EamPresent_link_roadway_geometry },
	{ Dz1Text("probe_vehicle_detection"), Dz1Text("ProbeVehicleDetectionList"), TechnicalRegulation1_EamPresent_probe_vehicle_detection },
	{ Dz1Text("detector_collection"), Dz1Text("DetectorCollectionList"), TechnicalRegulation1_EamPresent_detector_collection },
	{ Dz1Text("extention_comm_pdu"), Dz1Text("ExtentionCommPDUList"), TechnicalRegulation1_EamPresent_extention_comm_pdu },
	{ NULL, NULL, -1 }
};
// TechnicalRegulation1_Eam
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpec Initializer
bool_t Iso14827TestHelperDef_initJsonSpec(Dz1JsonSpec *dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (0) { }
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Iso14827TestProcessStatusCode"), Iso14827TestProcessStatusCode_gen, Iso14827TestProcessStatusCode_del, Iso14827TestProcessStatusCode_load, Iso14827TestProcessStatusCode_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_TransmissionState"), Gitsn_TransmissionState_gen, Gitsn_TransmissionState_del, Gitsn_TransmissionState_load, Gitsn_TransmissionState_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_TractionControlStatus"), Gitsn_TractionControlStatus_gen, Gitsn_TractionControlStatus_del, Gitsn_TractionControlStatus_load, Gitsn_TractionControlStatus_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_AntiLockBrakeStatus"), Gitsn_AntiLockBrakeStatus_gen, Gitsn_AntiLockBrakeStatus_del, Gitsn_AntiLockBrakeStatus_load, Gitsn_AntiLockBrakeStatus_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_StabilityControlStatus"), Gitsn_StabilityControlStatus_gen, Gitsn_StabilityControlStatus_del, Gitsn_StabilityControlStatus_load, Gitsn_StabilityControlStatus_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_BrakeBoostApplied"), Gitsn_BrakeBoostApplied_gen, Gitsn_BrakeBoostApplied_del, Gitsn_BrakeBoostApplied_load, Gitsn_BrakeBoostApplied_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_AuxiliaryBrakeStatus"), Gitsn_AuxiliaryBrakeStatus_gen, Gitsn_AuxiliaryBrakeStatus_del, Gitsn_AuxiliaryBrakeStatus_load, Gitsn_AuxiliaryBrakeStatus_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_LayerType"), Gitsn_LayerType_gen, Gitsn_LayerType_del, Gitsn_LayerType_load, Gitsn_LayerType_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_SpeedLimitType"), Gitsn_SpeedLimitType_gen, Gitsn_SpeedLimitType_del, Gitsn_SpeedLimitType_load, Gitsn_SpeedLimitType_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_NodeAttributeXY"), Gitsn_NodeAttributeXY_gen, Gitsn_NodeAttributeXY_del, Gitsn_NodeAttributeXY_load, Gitsn_NodeAttributeXY_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_SegmentAttributeXY"), Gitsn_SegmentAttributeXY_gen, Gitsn_SegmentAttributeXY_del, Gitsn_SegmentAttributeXY_load, Gitsn_SegmentAttributeXY_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_RestrictionAppliesTo"), Gitsn_RestrictionAppliesTo_gen, Gitsn_RestrictionAppliesTo_del, Gitsn_RestrictionAppliesTo_load, Gitsn_RestrictionAppliesTo_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_MovementPhaseState"), Gitsn_MovementPhaseState_gen, Gitsn_MovementPhaseState_del, Gitsn_MovementPhaseState_load, Gitsn_MovementPhaseState_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_AdvisorySpeedType"), Gitsn_AdvisorySpeedType_gen, Gitsn_AdvisorySpeedType_del, Gitsn_AdvisorySpeedType_load, Gitsn_AdvisorySpeedType_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_SpeedConfidence"), Gitsn_SpeedConfidence_gen, Gitsn_SpeedConfidence_del, Gitsn_SpeedConfidence_load, Gitsn_SpeedConfidence_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_VehicleType"), Gitsn_VehicleType_gen, Gitsn_VehicleType_del, Gitsn_VehicleType_load, Gitsn_VehicleType_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_VehicleGroupAffected"), Gitsn_VehicleGroupAffected_gen, Gitsn_VehicleGroupAffected_del, Gitsn_VehicleGroupAffected_load, Gitsn_VehicleGroupAffected_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_ResponderGroupAffected"), Gitsn_ResponderGroupAffected_gen, Gitsn_ResponderGroupAffected_del, Gitsn_ResponderGroupAffected_load, Gitsn_ResponderGroupAffected_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_IncidentResponseEquipment"), Gitsn_IncidentResponseEquipment_gen, Gitsn_IncidentResponseEquipment_del, Gitsn_IncidentResponseEquipment_load, Gitsn_IncidentResponseEquipment_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_TimeConfidence"), Gitsn_TimeConfidence_gen, Gitsn_TimeConfidence_del, Gitsn_TimeConfidence_load, Gitsn_TimeConfidence_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_PositionConfidence"), Gitsn_PositionConfidence_gen, Gitsn_PositionConfidence_del, Gitsn_PositionConfidence_load, Gitsn_PositionConfidence_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_ElevationConfidence"), Gitsn_ElevationConfidence_gen, Gitsn_ElevationConfidence_del, Gitsn_ElevationConfidence_load, Gitsn_ElevationConfidence_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_HeadingConfidence"), Gitsn_HeadingConfidence_gen, Gitsn_HeadingConfidence_del, Gitsn_HeadingConfidence_load, Gitsn_HeadingConfidence_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_ThrottleConfidence"), Gitsn_ThrottleConfidence_gen, Gitsn_ThrottleConfidence_del, Gitsn_ThrottleConfidence_load, Gitsn_ThrottleConfidence_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_BasicVehicleRole"), Gitsn_BasicVehicleRole_gen, Gitsn_BasicVehicleRole_del, Gitsn_BasicVehicleRole_load, Gitsn_BasicVehicleRole_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_LightbarInUse"), Gitsn_LightbarInUse_gen, Gitsn_LightbarInUse_del, Gitsn_LightbarInUse_load, Gitsn_LightbarInUse_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_WiperStatus"), Gitsn_WiperStatus_gen, Gitsn_WiperStatus_del, Gitsn_WiperStatus_load, Gitsn_WiperStatus_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_BrakeAppliedPressure"), Gitsn_BrakeAppliedPressure_gen, Gitsn_BrakeAppliedPressure_del, Gitsn_BrakeAppliedPressure_load, Gitsn_BrakeAppliedPressure_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_RainSensor"), Gitsn_RainSensor_gen, Gitsn_RainSensor_del, Gitsn_RainSensor_load, Gitsn_RainSensor_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_SteeringWheelAngleConfidence"), Gitsn_SteeringWheelAngleConfidence_gen, Gitsn_SteeringWheelAngleConfidence_del, Gitsn_SteeringWheelAngleConfidence_load, Gitsn_SteeringWheelAngleConfidence_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_YawRateConfidence"), Gitsn_YawRateConfidence_gen, Gitsn_YawRateConfidence_del, Gitsn_YawRateConfidence_load, Gitsn_YawRateConfidence_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_AccelerationConfidence"), Gitsn_AccelerationConfidence_gen, Gitsn_AccelerationConfidence_del, Gitsn_AccelerationConfidence_load, Gitsn_AccelerationConfidence_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_WheelSensorStatus"), Gitsn_WheelSensorStatus_gen, Gitsn_WheelSensorStatus_del, Gitsn_WheelSensorStatus_load, Gitsn_WheelSensorStatus_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_WheelEndElectFault"), Gitsn_WheelEndElectFault_gen, Gitsn_WheelEndElectFault_del, Gitsn_WheelEndElectFault_load, Gitsn_WheelEndElectFault_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_TirePressureThresholdDetection"), Gitsn_TirePressureThresholdDetection_gen, Gitsn_TirePressureThresholdDetection_del, Gitsn_TirePressureThresholdDetection_load, Gitsn_TirePressureThresholdDetection_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_EssPrecipYesNo"), Gitsn_EssPrecipYesNo_gen, Gitsn_EssPrecipYesNo_del, Gitsn_EssPrecipYesNo_load, Gitsn_EssPrecipYesNo_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_EssPrecipSituation"), Gitsn_EssPrecipSituation_gen, Gitsn_EssPrecipSituation_del, Gitsn_EssPrecipSituation_load, Gitsn_EssPrecipSituation_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_Extent"), Gitsn_Extent_gen, Gitsn_Extent_del, Gitsn_Extent_load, Gitsn_Extent_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_TravelerInfoType"), Gitsn_TravelerInfoType_gen, Gitsn_TravelerInfoType_del, Gitsn_TravelerInfoType_load, Gitsn_TravelerInfoType_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_MUTCDCode"), Gitsn_MUTCDCode_gen, Gitsn_MUTCDCode_del, Gitsn_MUTCDCode_load, Gitsn_MUTCDCode_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_DirectionOfUse"), Gitsn_DirectionOfUse_gen, Gitsn_DirectionOfUse_del, Gitsn_DirectionOfUse_load, Gitsn_DirectionOfUse_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_NodeAttributeLL"), Gitsn_NodeAttributeLL_gen, Gitsn_NodeAttributeLL_del, Gitsn_NodeAttributeLL_load, Gitsn_NodeAttributeLL_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_SegmentAttributeLL"), Gitsn_SegmentAttributeLL_gen, Gitsn_SegmentAttributeLL_del, Gitsn_SegmentAttributeLL_load, Gitsn_SegmentAttributeLL_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_DistanceUnits"), Gitsn_DistanceUnits_gen, Gitsn_DistanceUnits_del, Gitsn_DistanceUnits_load, Gitsn_DistanceUnits_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_EquipmentType"), Gitsn_EquipmentType_gen, Gitsn_EquipmentType_del, Gitsn_EquipmentType_load, Gitsn_EquipmentType_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_ObjectType"), Gitsn_ObjectType_gen, Gitsn_ObjectType_del, Gitsn_ObjectType_load, Gitsn_ObjectType_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_PitchRateConfidence"), Gitsn_PitchRateConfidence_gen, Gitsn_PitchRateConfidence_del, Gitsn_PitchRateConfidence_load, Gitsn_PitchRateConfidence_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_RollRateConfidence"), Gitsn_RollRateConfidence_gen, Gitsn_RollRateConfidence_del, Gitsn_RollRateConfidence_load, Gitsn_RollRateConfidence_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_SizeValueConfidence"), Gitsn_SizeValueConfidence_gen, Gitsn_SizeValueConfidence_del, Gitsn_SizeValueConfidence_load, Gitsn_SizeValueConfidence_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_PersonalDeviceUserType"), Gitsn_PersonalDeviceUserType_gen, Gitsn_PersonalDeviceUserType_del, Gitsn_PersonalDeviceUserType_load, Gitsn_PersonalDeviceUserType_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_HumanPropelledType"), Gitsn_HumanPropelledType_gen, Gitsn_HumanPropelledType_del, Gitsn_HumanPropelledType_load, Gitsn_HumanPropelledType_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_AnimalPropelledType"), Gitsn_AnimalPropelledType_gen, Gitsn_AnimalPropelledType_del, Gitsn_AnimalPropelledType_load, Gitsn_AnimalPropelledType_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_MotorizedPropelledType"), Gitsn_MotorizedPropelledType_gen, Gitsn_MotorizedPropelledType_del, Gitsn_MotorizedPropelledType_load, Gitsn_MotorizedPropelledType_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_Attachment"), Gitsn_Attachment_gen, Gitsn_Attachment_del, Gitsn_Attachment_load, Gitsn_Attachment_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_TrafficLightType"), Gitsn_TrafficLightType_gen, Gitsn_TrafficLightType_del, Gitsn_TrafficLightType_load, Gitsn_TrafficLightType_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_ConsecutiveTrafficLight"), Gitsn_ConsecutiveTrafficLight_gen, Gitsn_ConsecutiveTrafficLight_del, Gitsn_ConsecutiveTrafficLight_load, Gitsn_ConsecutiveTrafficLight_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_TrafficLightIntervalType"), Gitsn_TrafficLightIntervalType_gen, Gitsn_TrafficLightIntervalType_del, Gitsn_TrafficLightIntervalType_load, Gitsn_TrafficLightIntervalType_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_PermissiveNonProtected"), Gitsn_PermissiveNonProtected_gen, Gitsn_PermissiveNonProtected_del, Gitsn_PermissiveNonProtected_load, Gitsn_PermissiveNonProtected_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_TrafficLightingStatus"), Gitsn_TrafficLightingStatus_gen, Gitsn_TrafficLightingStatus_del, Gitsn_TrafficLightingStatus_load, Gitsn_TrafficLightingStatus_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_Iso14827LoginInitiator"), Gitsn_Iso14827LoginInitiator_gen, Gitsn_Iso14827LoginInitiator_del, Gitsn_Iso14827LoginInitiator_load, Gitsn_Iso14827LoginInitiator_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_Iso14827Terminate"), Gitsn_Iso14827Terminate_gen, Gitsn_Iso14827Terminate_del, Gitsn_Iso14827Terminate_load, Gitsn_Iso14827Terminate_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_Iso14827Logout"), Gitsn_Iso14827Logout_gen, Gitsn_Iso14827Logout_del, Gitsn_Iso14827Logout_load, Gitsn_Iso14827Logout_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_Iso14827SubscriptionDataStatus"), Gitsn_Iso14827SubscriptionDataStatus_gen, Gitsn_Iso14827SubscriptionDataStatus_del, Gitsn_Iso14827SubscriptionDataStatus_load, Gitsn_Iso14827SubscriptionDataStatus_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_Iso14827SubscriptionDataFormat"), Gitsn_Iso14827SubscriptionDataFormat_gen, Gitsn_Iso14827SubscriptionDataFormat_del, Gitsn_Iso14827SubscriptionDataFormat_load, Gitsn_Iso14827SubscriptionDataFormat_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_Iso14827SubscriptionCancel"), Gitsn_Iso14827SubscriptionCancel_gen, Gitsn_Iso14827SubscriptionCancel_del, Gitsn_Iso14827SubscriptionCancel_load, Gitsn_Iso14827SubscriptionCancel_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_Iso14827PublicationMgmt"), Gitsn_Iso14827PublicationMgmt_gen, Gitsn_Iso14827PublicationMgmt_del, Gitsn_Iso14827PublicationMgmt_load, Gitsn_Iso14827PublicationMgmt_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_Iso14827RejectLogin"), Gitsn_Iso14827RejectLogin_gen, Gitsn_Iso14827RejectLogin_del, Gitsn_Iso14827RejectLogin_load, Gitsn_Iso14827RejectLogin_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_Iso14827RejectSubscription"), Gitsn_Iso14827RejectSubscription_gen, Gitsn_Iso14827RejectSubscription_del, Gitsn_Iso14827RejectSubscription_load, Gitsn_Iso14827RejectSubscription_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_Iso14827RejectPublication"), Gitsn_Iso14827RejectPublication_gen, Gitsn_Iso14827RejectPublication_del, Gitsn_Iso14827RejectPublication_load, Gitsn_Iso14827RejectPublication_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_Iso14827RejectPubDataReason"), Gitsn_Iso14827RejectPubDataReason_gen, Gitsn_Iso14827RejectPubDataReason_del, Gitsn_Iso14827RejectPubDataReason_load, Gitsn_Iso14827RejectPubDataReason_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Iso14827SubscriptionCancel"), Iso14827SubscriptionCancel_gen, Iso14827SubscriptionCancel_del, Iso14827SubscriptionCancel_load, Iso14827SubscriptionCancel_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Iso14827TestNotifyStateContext"), Iso14827TestNotifyStateContext_gen, Iso14827TestNotifyStateContext_del, Iso14827TestNotifyStateContext_setChild, Iso14827TestNotifyStateContext_getChild, Iso14827TestNotifyStateContext_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Iso14827TestNotifyInfoContext"), Iso14827TestNotifyInfoContext_gen, Iso14827TestNotifyInfoContext_del, Iso14827TestNotifyInfoContext_setChild, Iso14827TestNotifyInfoContext_getChild, Iso14827TestNotifyInfoContext_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Iso14827TestNotifyErrorContext"), Iso14827TestNotifyErrorContext_gen, Iso14827TestNotifyErrorContext_del, Iso14827TestNotifyErrorContext_setChild, Iso14827TestNotifyErrorContext_getChild, Iso14827TestNotifyErrorContext_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Iso14827TestNotifyContext"), Iso14827TestNotifyContext_gen, Iso14827TestNotifyContext_del, Iso14827TestNotifyContext_setChild, Iso14827TestNotifyContext_getChild, Iso14827TestNotifyContext_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Iso14827TestValidateContext"), Iso14827TestValidateContext_gen, Iso14827TestValidateContext_del, Iso14827TestValidateContext_setChild, Iso14827TestValidateContext_getChild, Iso14827TestValidateContext_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_PositionalAccuracy"), Gitsn_PositionalAccuracy_gen, Gitsn_PositionalAccuracy_del, Gitsn_PositionalAccuracy_setChild, Gitsn_PositionalAccuracy_getChild, Gitsn_PositionalAccuracy_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_AccelerationSet4Way"), Gitsn_AccelerationSet4Way_gen, Gitsn_AccelerationSet4Way_del, Gitsn_AccelerationSet4Way_setChild, Gitsn_AccelerationSet4Way_getChild, Gitsn_AccelerationSet4Way_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_BrakeSystemStatus"), Gitsn_BrakeSystemStatus_gen, Gitsn_BrakeSystemStatus_del, Gitsn_BrakeSystemStatus_setChild, Gitsn_BrakeSystemStatus_getChild, Gitsn_BrakeSystemStatus_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_VehicleSize"), Gitsn_VehicleSize_gen, Gitsn_VehicleSize_del, Gitsn_VehicleSize_setChild, Gitsn_VehicleSize_getChild, Gitsn_VehicleSize_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_BSMCoreData"), Gitsn_BSMCoreData_gen, Gitsn_BSMCoreData_del, Gitsn_BSMCoreData_setChild, Gitsn_BSMCoreData_getChild, Gitsn_BSMCoreData_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_BasicSafetyMessage"), Gitsn_BasicSafetyMessage_gen, Gitsn_BasicSafetyMessage_del, Gitsn_BasicSafetyMessage_setChild, Gitsn_BasicSafetyMessage_getChild, Gitsn_BasicSafetyMessage_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_IntersectionReferenceID"), Gitsn_IntersectionReferenceID_gen, Gitsn_IntersectionReferenceID_del, Gitsn_IntersectionReferenceID_setChild, Gitsn_IntersectionReferenceID_getChild, Gitsn_IntersectionReferenceID_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Position3D"), Gitsn_Position3D_gen, Gitsn_Position3D_del, Gitsn_Position3D_setChild, Gitsn_Position3D_getChild, Gitsn_Position3D_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_RegulatorySpeedLimit"), Gitsn_RegulatorySpeedLimit_gen, Gitsn_RegulatorySpeedLimit_del, Gitsn_RegulatorySpeedLimit_setChild, Gitsn_RegulatorySpeedLimit_getChild, Gitsn_RegulatorySpeedLimit_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_LaneTypeAttributes"), Gitsn_LaneTypeAttributes_gen, Gitsn_LaneTypeAttributes_del, Gitsn_LaneTypeAttributes_setChild, Gitsn_LaneTypeAttributes_getChild, Gitsn_LaneTypeAttributes_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_LaneAttributes"), Gitsn_LaneAttributes_gen, Gitsn_LaneAttributes_del, Gitsn_LaneAttributes_setChild, Gitsn_LaneAttributes_getChild, Gitsn_LaneAttributes_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Node_XY_20b"), Gitsn_Node_XY_20b_gen, Gitsn_Node_XY_20b_del, Gitsn_Node_XY_20b_setChild, Gitsn_Node_XY_20b_getChild, Gitsn_Node_XY_20b_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Node_XY_22b"), Gitsn_Node_XY_22b_gen, Gitsn_Node_XY_22b_del, Gitsn_Node_XY_22b_setChild, Gitsn_Node_XY_22b_getChild, Gitsn_Node_XY_22b_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Node_XY_24b"), Gitsn_Node_XY_24b_gen, Gitsn_Node_XY_24b_del, Gitsn_Node_XY_24b_setChild, Gitsn_Node_XY_24b_getChild, Gitsn_Node_XY_24b_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Node_XY_26b"), Gitsn_Node_XY_26b_gen, Gitsn_Node_XY_26b_del, Gitsn_Node_XY_26b_setChild, Gitsn_Node_XY_26b_getChild, Gitsn_Node_XY_26b_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Node_XY_28b"), Gitsn_Node_XY_28b_gen, Gitsn_Node_XY_28b_del, Gitsn_Node_XY_28b_setChild, Gitsn_Node_XY_28b_getChild, Gitsn_Node_XY_28b_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Node_XY_32b"), Gitsn_Node_XY_32b_gen, Gitsn_Node_XY_32b_del, Gitsn_Node_XY_32b_setChild, Gitsn_Node_XY_32b_getChild, Gitsn_Node_XY_32b_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Node_LLmD_64b"), Gitsn_Node_LLmD_64b_gen, Gitsn_Node_LLmD_64b_del, Gitsn_Node_LLmD_64b_setChild, Gitsn_Node_LLmD_64b_getChild, Gitsn_Node_LLmD_64b_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_NodeOffsetPointXY"), Gitsn_NodeOffsetPointXY_gen, Gitsn_NodeOffsetPointXY_del, Gitsn_NodeOffsetPointXY_setChild, Gitsn_NodeOffsetPointXY_getChild, Gitsn_NodeOffsetPointXY_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_LaneDataAttribute"), Gitsn_LaneDataAttribute_gen, Gitsn_LaneDataAttribute_del, Gitsn_LaneDataAttribute_setChild, Gitsn_LaneDataAttribute_getChild, Gitsn_LaneDataAttribute_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_NodeAttributeSetXY"), Gitsn_NodeAttributeSetXY_gen, Gitsn_NodeAttributeSetXY_del, Gitsn_NodeAttributeSetXY_setChild, Gitsn_NodeAttributeSetXY_getChild, Gitsn_NodeAttributeSetXY_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_NodeXY"), Gitsn_NodeXY_gen, Gitsn_NodeXY_del, Gitsn_NodeXY_setChild, Gitsn_NodeXY_getChild, Gitsn_NodeXY_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_ComputedLane_offsetXaxis"), Gitsn_ComputedLane_offsetXaxis_gen, Gitsn_ComputedLane_offsetXaxis_del, Gitsn_ComputedLane_offsetXaxis_setChild, Gitsn_ComputedLane_offsetXaxis_getChild, Gitsn_ComputedLane_offsetXaxis_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_ComputedLane_offsetYaxis"), Gitsn_ComputedLane_offsetYaxis_gen, Gitsn_ComputedLane_offsetYaxis_del, Gitsn_ComputedLane_offsetYaxis_setChild, Gitsn_ComputedLane_offsetYaxis_getChild, Gitsn_ComputedLane_offsetYaxis_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_ComputedLane"), Gitsn_ComputedLane_gen, Gitsn_ComputedLane_del, Gitsn_ComputedLane_setChild, Gitsn_ComputedLane_getChild, Gitsn_ComputedLane_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_NodeListXY"), Gitsn_NodeListXY_gen, Gitsn_NodeListXY_del, Gitsn_NodeListXY_setChild, Gitsn_NodeListXY_getChild, Gitsn_NodeListXY_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_ConnectingLane"), Gitsn_ConnectingLane_gen, Gitsn_ConnectingLane_del, Gitsn_ConnectingLane_setChild, Gitsn_ConnectingLane_getChild, Gitsn_ConnectingLane_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Connection"), Gitsn_Connection_gen, Gitsn_Connection_del, Gitsn_Connection_setChild, Gitsn_Connection_getChild, Gitsn_Connection_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_GenericLane"), Gitsn_GenericLane_gen, Gitsn_GenericLane_del, Gitsn_GenericLane_setChild, Gitsn_GenericLane_getChild, Gitsn_GenericLane_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_SignalControlZone"), Gitsn_SignalControlZone_gen, Gitsn_SignalControlZone_del, Gitsn_SignalControlZone_setChild, Gitsn_SignalControlZone_getChild, Gitsn_SignalControlZone_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_IntersectionGeometry"), Gitsn_IntersectionGeometry_gen, Gitsn_IntersectionGeometry_del, Gitsn_IntersectionGeometry_setChild, Gitsn_IntersectionGeometry_getChild, Gitsn_IntersectionGeometry_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_RoadSegmentReferenceID"), Gitsn_RoadSegmentReferenceID_gen, Gitsn_RoadSegmentReferenceID_del, Gitsn_RoadSegmentReferenceID_setChild, Gitsn_RoadSegmentReferenceID_getChild, Gitsn_RoadSegmentReferenceID_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_RoadSegment"), Gitsn_RoadSegment_gen, Gitsn_RoadSegment_del, Gitsn_RoadSegment_setChild, Gitsn_RoadSegment_getChild, Gitsn_RoadSegment_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_DataParameters"), Gitsn_DataParameters_gen, Gitsn_DataParameters_del, Gitsn_DataParameters_setChild, Gitsn_DataParameters_getChild, Gitsn_DataParameters_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_RestrictionUserType"), Gitsn_RestrictionUserType_gen, Gitsn_RestrictionUserType_del, Gitsn_RestrictionUserType_setChild, Gitsn_RestrictionUserType_getChild, Gitsn_RestrictionUserType_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_RestrictionClassAssignment"), Gitsn_RestrictionClassAssignment_gen, Gitsn_RestrictionClassAssignment_del, Gitsn_RestrictionClassAssignment_setChild, Gitsn_RestrictionClassAssignment_getChild, Gitsn_RestrictionClassAssignment_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_MapData"), Gitsn_MapData_gen, Gitsn_MapData_del, Gitsn_MapData_setChild, Gitsn_MapData_getChild, Gitsn_MapData_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_TimeChangeDetails"), Gitsn_TimeChangeDetails_gen, Gitsn_TimeChangeDetails_del, Gitsn_TimeChangeDetails_setChild, Gitsn_TimeChangeDetails_getChild, Gitsn_TimeChangeDetails_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_AdvisorySpeed"), Gitsn_AdvisorySpeed_gen, Gitsn_AdvisorySpeed_del, Gitsn_AdvisorySpeed_setChild, Gitsn_AdvisorySpeed_getChild, Gitsn_AdvisorySpeed_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_MovementEvent"), Gitsn_MovementEvent_gen, Gitsn_MovementEvent_del, Gitsn_MovementEvent_setChild, Gitsn_MovementEvent_getChild, Gitsn_MovementEvent_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_ConnectionManeuverAssist"), Gitsn_ConnectionManeuverAssist_gen, Gitsn_ConnectionManeuverAssist_del, Gitsn_ConnectionManeuverAssist_setChild, Gitsn_ConnectionManeuverAssist_getChild, Gitsn_ConnectionManeuverAssist_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_MovementState"), Gitsn_MovementState_gen, Gitsn_MovementState_del, Gitsn_MovementState_setChild, Gitsn_MovementState_getChild, Gitsn_MovementState_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_IntersectionState"), Gitsn_IntersectionState_gen, Gitsn_IntersectionState_del, Gitsn_IntersectionState_setChild, Gitsn_IntersectionState_getChild, Gitsn_IntersectionState_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_SPAT"), Gitsn_SPAT_gen, Gitsn_SPAT_del, Gitsn_SPAT_setChild, Gitsn_SPAT_getChild, Gitsn_SPAT_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_VehicleID"), Gitsn_VehicleID_gen, Gitsn_VehicleID_del, Gitsn_VehicleID_setChild, Gitsn_VehicleID_getChild, Gitsn_VehicleID_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_VehicleIdent_vehicleClass"), Gitsn_VehicleIdent_vehicleClass_gen, Gitsn_VehicleIdent_vehicleClass_del, Gitsn_VehicleIdent_vehicleClass_setChild, Gitsn_VehicleIdent_vehicleClass_getChild, Gitsn_VehicleIdent_vehicleClass_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_VehicleIdent"), Gitsn_VehicleIdent_gen, Gitsn_VehicleIdent_del, Gitsn_VehicleIdent_setChild, Gitsn_VehicleIdent_getChild, Gitsn_VehicleIdent_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_DDateTime"), Gitsn_DDateTime_gen, Gitsn_DDateTime_del, Gitsn_DDateTime_setChild, Gitsn_DDateTime_getChild, Gitsn_DDateTime_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_TransmissionAndSpeed"), Gitsn_TransmissionAndSpeed_gen, Gitsn_TransmissionAndSpeed_del, Gitsn_TransmissionAndSpeed_setChild, Gitsn_TransmissionAndSpeed_getChild, Gitsn_TransmissionAndSpeed_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_PositionConfidenceSet"), Gitsn_PositionConfidenceSet_gen, Gitsn_PositionConfidenceSet_del, Gitsn_PositionConfidenceSet_setChild, Gitsn_PositionConfidenceSet_getChild, Gitsn_PositionConfidenceSet_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_SpeedandHeadingandThrottleConfidence"), Gitsn_SpeedandHeadingandThrottleConfidence_gen, Gitsn_SpeedandHeadingandThrottleConfidence_del, Gitsn_SpeedandHeadingandThrottleConfidence_setChild, Gitsn_SpeedandHeadingandThrottleConfidence_getChild, Gitsn_SpeedandHeadingandThrottleConfidence_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_FullPositionVector"), Gitsn_FullPositionVector_gen, Gitsn_FullPositionVector_del, Gitsn_FullPositionVector_setChild, Gitsn_FullPositionVector_getChild, Gitsn_FullPositionVector_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_VehicleClassification"), Gitsn_VehicleClassification_gen, Gitsn_VehicleClassification_del, Gitsn_VehicleClassification_setChild, Gitsn_VehicleClassification_getChild, Gitsn_VehicleClassification_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_PathHistoryPoint"), Gitsn_PathHistoryPoint_gen, Gitsn_PathHistoryPoint_del, Gitsn_PathHistoryPoint_setChild, Gitsn_PathHistoryPoint_getChild, Gitsn_PathHistoryPoint_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_PathHistory"), Gitsn_PathHistory_gen, Gitsn_PathHistory_del, Gitsn_PathHistory_setChild, Gitsn_PathHistory_getChild, Gitsn_PathHistory_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_PathPrediction"), Gitsn_PathPrediction_gen, Gitsn_PathPrediction_del, Gitsn_PathPrediction_setChild, Gitsn_PathPrediction_getChild, Gitsn_PathPrediction_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_VehicleSafetyExtensions"), Gitsn_VehicleSafetyExtensions_gen, Gitsn_VehicleSafetyExtensions_del, Gitsn_VehicleSafetyExtensions_setChild, Gitsn_VehicleSafetyExtensions_getChild, Gitsn_VehicleSafetyExtensions_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_WiperSet"), Gitsn_WiperSet_gen, Gitsn_WiperSet_del, Gitsn_WiperSet_setChild, Gitsn_WiperSet_getChild, Gitsn_WiperSet_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_VehicleStatus_steering"), Gitsn_VehicleStatus_steering_gen, Gitsn_VehicleStatus_steering_del, Gitsn_VehicleStatus_steering_setChild, Gitsn_VehicleStatus_steering_getChild, Gitsn_VehicleStatus_steering_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_AccelSteerYawRateConfidence"), Gitsn_AccelSteerYawRateConfidence_gen, Gitsn_AccelSteerYawRateConfidence_del, Gitsn_AccelSteerYawRateConfidence_setChild, Gitsn_AccelSteerYawRateConfidence_getChild, Gitsn_AccelSteerYawRateConfidence_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_ConfidenceSet"), Gitsn_ConfidenceSet_gen, Gitsn_ConfidenceSet_del, Gitsn_ConfidenceSet_setChild, Gitsn_ConfidenceSet_getChild, Gitsn_ConfidenceSet_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_VehicleStatus_accelSets"), Gitsn_VehicleStatus_accelSets_gen, Gitsn_VehicleStatus_accelSets_del, Gitsn_VehicleStatus_accelSets_setChild, Gitsn_VehicleStatus_accelSets_getChild, Gitsn_VehicleStatus_accelSets_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_VehicleStatus_object"), Gitsn_VehicleStatus_object_gen, Gitsn_VehicleStatus_object_del, Gitsn_VehicleStatus_object_setChild, Gitsn_VehicleStatus_object_getChild, Gitsn_VehicleStatus_object_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_BumperHeights"), Gitsn_BumperHeights_gen, Gitsn_BumperHeights_del, Gitsn_BumperHeights_setChild, Gitsn_BumperHeights_getChild, Gitsn_BumperHeights_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_VehicleStatus_vehicleData"), Gitsn_VehicleStatus_vehicleData_gen, Gitsn_VehicleStatus_vehicleData_del, Gitsn_VehicleStatus_vehicleData_setChild, Gitsn_VehicleStatus_vehicleData_getChild, Gitsn_VehicleStatus_vehicleData_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_TireData"), Gitsn_TireData_gen, Gitsn_TireData_del, Gitsn_TireData_setChild, Gitsn_TireData_getChild, Gitsn_TireData_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_AxleWeightSet"), Gitsn_AxleWeightSet_gen, Gitsn_AxleWeightSet_del, Gitsn_AxleWeightSet_setChild, Gitsn_AxleWeightSet_getChild, Gitsn_AxleWeightSet_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_J1939DataItems"), Gitsn_J1939DataItems_gen, Gitsn_J1939DataItems_del, Gitsn_J1939DataItems_setChild, Gitsn_J1939DataItems_getChild, Gitsn_J1939DataItems_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_VehicleStatus_weatherReport"), Gitsn_VehicleStatus_weatherReport_gen, Gitsn_VehicleStatus_weatherReport_del, Gitsn_VehicleStatus_weatherReport_setChild, Gitsn_VehicleStatus_weatherReport_getChild, Gitsn_VehicleStatus_weatherReport_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_VehicleStatus"), Gitsn_VehicleStatus_gen, Gitsn_VehicleStatus_del, Gitsn_VehicleStatus_setChild, Gitsn_VehicleStatus_getChild, Gitsn_VehicleStatus_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Snapshot"), Gitsn_Snapshot_gen, Gitsn_Snapshot_del, Gitsn_Snapshot_setChild, Gitsn_Snapshot_getChild, Gitsn_Snapshot_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_ProbeVehicleData"), Gitsn_ProbeVehicleData_gen, Gitsn_ProbeVehicleData_del, Gitsn_ProbeVehicleData_setChild, Gitsn_ProbeVehicleData_getChild, Gitsn_ProbeVehicleData_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_RoadSideAlert"), Gitsn_RoadSideAlert_gen, Gitsn_RoadSideAlert_del, Gitsn_RoadSideAlert_setChild, Gitsn_RoadSideAlert_getChild, Gitsn_RoadSideAlert_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_RoadSignID"), Gitsn_RoadSignID_gen, Gitsn_RoadSignID_del, Gitsn_RoadSignID_setChild, Gitsn_RoadSignID_getChild, Gitsn_RoadSignID_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_TravelerDataFrame_msgId"), Gitsn_TravelerDataFrame_msgId_gen, Gitsn_TravelerDataFrame_msgId_del, Gitsn_TravelerDataFrame_msgId_setChild, Gitsn_TravelerDataFrame_msgId_getChild, Gitsn_TravelerDataFrame_msgId_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Node_LL_24B"), Gitsn_Node_LL_24B_gen, Gitsn_Node_LL_24B_del, Gitsn_Node_LL_24B_setChild, Gitsn_Node_LL_24B_getChild, Gitsn_Node_LL_24B_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Node_LL_28B"), Gitsn_Node_LL_28B_gen, Gitsn_Node_LL_28B_del, Gitsn_Node_LL_28B_setChild, Gitsn_Node_LL_28B_getChild, Gitsn_Node_LL_28B_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Node_LL_32B"), Gitsn_Node_LL_32B_gen, Gitsn_Node_LL_32B_del, Gitsn_Node_LL_32B_setChild, Gitsn_Node_LL_32B_getChild, Gitsn_Node_LL_32B_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Node_LL_36B"), Gitsn_Node_LL_36B_gen, Gitsn_Node_LL_36B_del, Gitsn_Node_LL_36B_setChild, Gitsn_Node_LL_36B_getChild, Gitsn_Node_LL_36B_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Node_LL_44B"), Gitsn_Node_LL_44B_gen, Gitsn_Node_LL_44B_del, Gitsn_Node_LL_44B_setChild, Gitsn_Node_LL_44B_getChild, Gitsn_Node_LL_44B_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Node_LL_48B"), Gitsn_Node_LL_48B_gen, Gitsn_Node_LL_48B_del, Gitsn_Node_LL_48B_setChild, Gitsn_Node_LL_48B_getChild, Gitsn_Node_LL_48B_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_NodeOffsetPointLL"), Gitsn_NodeOffsetPointLL_gen, Gitsn_NodeOffsetPointLL_del, Gitsn_NodeOffsetPointLL_setChild, Gitsn_NodeOffsetPointLL_getChild, Gitsn_NodeOffsetPointLL_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_NodeAttributeSetLL"), Gitsn_NodeAttributeSetLL_gen, Gitsn_NodeAttributeSetLL_del, Gitsn_NodeAttributeSetLL_setChild, Gitsn_NodeAttributeSetLL_getChild, Gitsn_NodeAttributeSetLL_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_NodeLL"), Gitsn_NodeLL_gen, Gitsn_NodeLL_del, Gitsn_NodeLL_setChild, Gitsn_NodeLL_getChild, Gitsn_NodeLL_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_NodeListLL"), Gitsn_NodeListLL_gen, Gitsn_NodeListLL_del, Gitsn_NodeListLL_setChild, Gitsn_NodeListLL_getChild, Gitsn_NodeListLL_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_OffsetSystem_offset"), Gitsn_OffsetSystem_offset_gen, Gitsn_OffsetSystem_offset_del, Gitsn_OffsetSystem_offset_setChild, Gitsn_OffsetSystem_offset_getChild, Gitsn_OffsetSystem_offset_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_OffsetSystem"), Gitsn_OffsetSystem_gen, Gitsn_OffsetSystem_del, Gitsn_OffsetSystem_setChild, Gitsn_OffsetSystem_getChild, Gitsn_OffsetSystem_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Circle"), Gitsn_Circle_gen, Gitsn_Circle_del, Gitsn_Circle_setChild, Gitsn_Circle_getChild, Gitsn_Circle_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_GeometricProjection"), Gitsn_GeometricProjection_gen, Gitsn_GeometricProjection_del, Gitsn_GeometricProjection_setChild, Gitsn_GeometricProjection_getChild, Gitsn_GeometricProjection_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_ShapePointSet"), Gitsn_ShapePointSet_gen, Gitsn_ShapePointSet_del, Gitsn_ShapePointSet_setChild, Gitsn_ShapePointSet_getChild, Gitsn_ShapePointSet_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_RegionOffsets"), Gitsn_RegionOffsets_gen, Gitsn_RegionOffsets_del, Gitsn_RegionOffsets_setChild, Gitsn_RegionOffsets_getChild, Gitsn_RegionOffsets_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_RegionPointSet"), Gitsn_RegionPointSet_gen, Gitsn_RegionPointSet_del, Gitsn_RegionPointSet_setChild, Gitsn_RegionPointSet_getChild, Gitsn_RegionPointSet_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_ValidRegion_area"), Gitsn_ValidRegion_area_gen, Gitsn_ValidRegion_area_del, Gitsn_ValidRegion_area_setChild, Gitsn_ValidRegion_area_getChild, Gitsn_ValidRegion_area_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_ValidRegion"), Gitsn_ValidRegion_gen, Gitsn_ValidRegion_del, Gitsn_ValidRegion_setChild, Gitsn_ValidRegion_getChild, Gitsn_ValidRegion_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_GeographicalPath_description"), Gitsn_GeographicalPath_description_gen, Gitsn_GeographicalPath_description_del, Gitsn_GeographicalPath_description_setChild, Gitsn_GeographicalPath_description_getChild, Gitsn_GeographicalPath_description_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_GeographicalPath"), Gitsn_GeographicalPath_gen, Gitsn_GeographicalPath_del, Gitsn_GeographicalPath_setChild, Gitsn_GeographicalPath_getChild, Gitsn_GeographicalPath_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_ITIScodesAndText_element_item"), Gitsn_ITIScodesAndText_element_item_gen, Gitsn_ITIScodesAndText_element_item_del, Gitsn_ITIScodesAndText_element_item_setChild, Gitsn_ITIScodesAndText_element_item_getChild, Gitsn_ITIScodesAndText_element_item_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_ITIScodesAndText_element"), Gitsn_ITIScodesAndText_element_gen, Gitsn_ITIScodesAndText_element_del, Gitsn_ITIScodesAndText_element_setChild, Gitsn_ITIScodesAndText_element_getChild, Gitsn_ITIScodesAndText_element_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_WorkZone_element_item"), Gitsn_WorkZone_element_item_gen, Gitsn_WorkZone_element_item_del, Gitsn_WorkZone_element_item_setChild, Gitsn_WorkZone_element_item_getChild, Gitsn_WorkZone_element_item_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_WorkZone_element"), Gitsn_WorkZone_element_gen, Gitsn_WorkZone_element_del, Gitsn_WorkZone_element_setChild, Gitsn_WorkZone_element_getChild, Gitsn_WorkZone_element_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_GenericSignage_element_item"), Gitsn_GenericSignage_element_item_gen, Gitsn_GenericSignage_element_item_del, Gitsn_GenericSignage_element_item_setChild, Gitsn_GenericSignage_element_item_getChild, Gitsn_GenericSignage_element_item_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_GenericSignage_element"), Gitsn_GenericSignage_element_gen, Gitsn_GenericSignage_element_del, Gitsn_GenericSignage_element_setChild, Gitsn_GenericSignage_element_getChild, Gitsn_GenericSignage_element_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_SpeedLimit_element_item"), Gitsn_SpeedLimit_element_item_gen, Gitsn_SpeedLimit_element_item_del, Gitsn_SpeedLimit_element_item_setChild, Gitsn_SpeedLimit_element_item_getChild, Gitsn_SpeedLimit_element_item_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_SpeedLimit_element"), Gitsn_SpeedLimit_element_gen, Gitsn_SpeedLimit_element_del, Gitsn_SpeedLimit_element_setChild, Gitsn_SpeedLimit_element_getChild, Gitsn_SpeedLimit_element_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_ExitService_element_item"), Gitsn_ExitService_element_item_gen, Gitsn_ExitService_element_item_del, Gitsn_ExitService_element_item_setChild, Gitsn_ExitService_element_item_getChild, Gitsn_ExitService_element_item_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_ExitService_element"), Gitsn_ExitService_element_gen, Gitsn_ExitService_element_del, Gitsn_ExitService_element_setChild, Gitsn_ExitService_element_getChild, Gitsn_ExitService_element_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_TravelerDataFrame_content"), Gitsn_TravelerDataFrame_content_gen, Gitsn_TravelerDataFrame_content_del, Gitsn_TravelerDataFrame_content_setChild, Gitsn_TravelerDataFrame_content_getChild, Gitsn_TravelerDataFrame_content_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_TravelerDataFrame"), Gitsn_TravelerDataFrame_gen, Gitsn_TravelerDataFrame_del, Gitsn_TravelerDataFrame_setChild, Gitsn_TravelerDataFrame_getChild, Gitsn_TravelerDataFrame_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_TravelerInformation"), Gitsn_TravelerInformation_gen, Gitsn_TravelerInformation_del, Gitsn_TravelerInformation_setChild, Gitsn_TravelerInformation_getChild, Gitsn_TravelerInformation_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_PositionOffsetXYZ"), Gitsn_PositionOffsetXYZ_gen, Gitsn_PositionOffsetXYZ_del, Gitsn_PositionOffsetXYZ_setChild, Gitsn_PositionOffsetXYZ_getChild, Gitsn_PositionOffsetXYZ_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_DetectedObjectCommonData"), Gitsn_DetectedObjectCommonData_gen, Gitsn_DetectedObjectCommonData_del, Gitsn_DetectedObjectCommonData_setChild, Gitsn_DetectedObjectCommonData_getChild, Gitsn_DetectedObjectCommonData_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Attitude"), Gitsn_Attitude_gen, Gitsn_Attitude_del, Gitsn_Attitude_setChild, Gitsn_Attitude_getChild, Gitsn_Attitude_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_AttitudeConfidence"), Gitsn_AttitudeConfidence_gen, Gitsn_AttitudeConfidence_del, Gitsn_AttitudeConfidence_setChild, Gitsn_AttitudeConfidence_getChild, Gitsn_AttitudeConfidence_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_AngularVelocity"), Gitsn_AngularVelocity_gen, Gitsn_AngularVelocity_del, Gitsn_AngularVelocity_setChild, Gitsn_AngularVelocity_getChild, Gitsn_AngularVelocity_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_AngularVelocityConfidence"), Gitsn_AngularVelocityConfidence_gen, Gitsn_AngularVelocityConfidence_del, Gitsn_AngularVelocityConfidence_setChild, Gitsn_AngularVelocityConfidence_getChild, Gitsn_AngularVelocityConfidence_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_VehicleSizeConfidence"), Gitsn_VehicleSizeConfidence_gen, Gitsn_VehicleSizeConfidence_del, Gitsn_VehicleSizeConfidence_setChild, Gitsn_VehicleSizeConfidence_getChild, Gitsn_VehicleSizeConfidence_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_DetectedVehicleData"), Gitsn_DetectedVehicleData_gen, Gitsn_DetectedVehicleData_del, Gitsn_DetectedVehicleData_setChild, Gitsn_DetectedVehicleData_getChild, Gitsn_DetectedVehicleData_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_PropelledInformation"), Gitsn_PropelledInformation_gen, Gitsn_PropelledInformation_del, Gitsn_PropelledInformation_setChild, Gitsn_PropelledInformation_getChild, Gitsn_PropelledInformation_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_DetectedVRUData"), Gitsn_DetectedVRUData_gen, Gitsn_DetectedVRUData_del, Gitsn_DetectedVRUData_setChild, Gitsn_DetectedVRUData_getChild, Gitsn_DetectedVRUData_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_ObstacleSize"), Gitsn_ObstacleSize_gen, Gitsn_ObstacleSize_del, Gitsn_ObstacleSize_setChild, Gitsn_ObstacleSize_getChild, Gitsn_ObstacleSize_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_ObstacleSizeConfidence"), Gitsn_ObstacleSizeConfidence_gen, Gitsn_ObstacleSizeConfidence_del, Gitsn_ObstacleSizeConfidence_setChild, Gitsn_ObstacleSizeConfidence_getChild, Gitsn_ObstacleSizeConfidence_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_DetectedObstacleData"), Gitsn_DetectedObstacleData_gen, Gitsn_DetectedObstacleData_del, Gitsn_DetectedObstacleData_setChild, Gitsn_DetectedObstacleData_getChild, Gitsn_DetectedObstacleData_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_DetectedObjectOptionalData"), Gitsn_DetectedObjectOptionalData_gen, Gitsn_DetectedObjectOptionalData_del, Gitsn_DetectedObjectOptionalData_setChild, Gitsn_DetectedObjectOptionalData_getChild, Gitsn_DetectedObjectOptionalData_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_DetectedObjectData"), Gitsn_DetectedObjectData_gen, Gitsn_DetectedObjectData_del, Gitsn_DetectedObjectData_setChild, Gitsn_DetectedObjectData_getChild, Gitsn_DetectedObjectData_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_SensorDataSharingMessage"), Gitsn_SensorDataSharingMessage_gen, Gitsn_SensorDataSharingMessage_del, Gitsn_SensorDataSharingMessage_setChild, Gitsn_SensorDataSharingMessage_getChild, Gitsn_SensorDataSharingMessage_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_OBJECTIDENTIFIER"), Gitsn_OBJECTIDENTIFIER_gen, Gitsn_OBJECTIDENTIFIER_del, Gitsn_OBJECTIDENTIFIER_setChild, Gitsn_OBJECTIDENTIFIER_getChild, Gitsn_OBJECTIDENTIFIER_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_TrafficLightID"), Gitsn_TrafficLightID_gen, Gitsn_TrafficLightID_del, Gitsn_TrafficLightID_setChild, Gitsn_TrafficLightID_getChild, Gitsn_TrafficLightID_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_TrafficLightStatus"), Gitsn_TrafficLightStatus_gen, Gitsn_TrafficLightStatus_del, Gitsn_TrafficLightStatus_setChild, Gitsn_TrafficLightStatus_getChild, Gitsn_TrafficLightStatus_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_TLS"), Gitsn_TLS_gen, Gitsn_TLS_del, Gitsn_TLS_setChild, Gitsn_TLS_getChild, Gitsn_TLS_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827Cost"), Gitsn_Iso14827Cost_gen, Gitsn_Iso14827Cost_del, Gitsn_Iso14827Cost_setChild, Gitsn_Iso14827Cost_getChild, Gitsn_Iso14827Cost_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827TimeFrac"), Gitsn_Iso14827TimeFrac_gen, Gitsn_Iso14827TimeFrac_del, Gitsn_Iso14827TimeFrac_setChild, Gitsn_Iso14827TimeFrac_getChild, Gitsn_Iso14827TimeFrac_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827TimeZone"), Gitsn_Iso14827TimeZone_gen, Gitsn_Iso14827TimeZone_del, Gitsn_Iso14827TimeZone_setChild, Gitsn_Iso14827TimeZone_getChild, Gitsn_Iso14827TimeZone_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827Time"), Gitsn_Iso14827Time_gen, Gitsn_Iso14827Time_del, Gitsn_Iso14827Time_setChild, Gitsn_Iso14827Time_getChild, Gitsn_Iso14827Time_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827HdrOpt"), Gitsn_Iso14827HdrOpt_gen, Gitsn_Iso14827HdrOpt_del, Gitsn_Iso14827HdrOpt_setChild, Gitsn_Iso14827HdrOpt_getChild, Gitsn_Iso14827HdrOpt_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827Initiate"), Gitsn_Iso14827Initiate_gen, Gitsn_Iso14827Initiate_del, Gitsn_Iso14827Initiate_setChild, Gitsn_Iso14827Initiate_getChild, Gitsn_Iso14827Initiate_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827Login"), Gitsn_Iso14827Login_gen, Gitsn_Iso14827Login_del, Gitsn_Iso14827Login_setChild, Gitsn_Iso14827Login_getChild, Gitsn_Iso14827Login_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827RegisteredContinuous"), Gitsn_Iso14827RegisteredContinuous_gen, Gitsn_Iso14827RegisteredContinuous_del, Gitsn_Iso14827RegisteredContinuous_setChild, Gitsn_Iso14827RegisteredContinuous_getChild, Gitsn_Iso14827RegisteredContinuous_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827RegisteredDaily"), Gitsn_Iso14827RegisteredDaily_gen, Gitsn_Iso14827RegisteredDaily_del, Gitsn_Iso14827RegisteredDaily_setChild, Gitsn_Iso14827RegisteredDaily_getChild, Gitsn_Iso14827RegisteredDaily_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827Registered"), Gitsn_Iso14827Registered_gen, Gitsn_Iso14827Registered_del, Gitsn_Iso14827Registered_setChild, Gitsn_Iso14827Registered_getChild, Gitsn_Iso14827Registered_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827SubscriptionDataMode"), Gitsn_Iso14827SubscriptionDataMode_gen, Gitsn_Iso14827SubscriptionDataMode_del, Gitsn_Iso14827SubscriptionDataMode_setChild, Gitsn_Iso14827SubscriptionDataMode_getChild, Gitsn_Iso14827SubscriptionDataMode_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827EndAppMsg"), Gitsn_Iso14827EndAppMsg_gen, Gitsn_Iso14827EndAppMsg_del, Gitsn_Iso14827EndAppMsg_setChild, Gitsn_Iso14827EndAppMsg_getChild, Gitsn_Iso14827EndAppMsg_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827SubscriptionData"), Gitsn_Iso14827SubscriptionData_gen, Gitsn_Iso14827SubscriptionData_del, Gitsn_Iso14827SubscriptionData_setChild, Gitsn_Iso14827SubscriptionData_getChild, Gitsn_Iso14827SubscriptionData_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827SubscriptionType"), Gitsn_Iso14827SubscriptionType_gen, Gitsn_Iso14827SubscriptionType_del, Gitsn_Iso14827SubscriptionType_setChild, Gitsn_Iso14827SubscriptionType_getChild, Gitsn_Iso14827SubscriptionType_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827Subscription"), Gitsn_Iso14827Subscription_gen, Gitsn_Iso14827Subscription_del, Gitsn_Iso14827Subscription_setChild, Gitsn_Iso14827Subscription_getChild, Gitsn_Iso14827Subscription_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827PublicationType"), Gitsn_Iso14827PublicationType_gen, Gitsn_Iso14827PublicationType_del, Gitsn_Iso14827PublicationType_setChild, Gitsn_Iso14827PublicationType_getChild, Gitsn_Iso14827PublicationType_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827PublicationData"), Gitsn_Iso14827PublicationData_gen, Gitsn_Iso14827PublicationData_del, Gitsn_Iso14827PublicationData_setChild, Gitsn_Iso14827PublicationData_getChild, Gitsn_Iso14827PublicationData_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827PublishFormat"), Gitsn_Iso14827PublishFormat_gen, Gitsn_Iso14827PublishFormat_del, Gitsn_Iso14827PublishFormat_setChild, Gitsn_Iso14827PublishFormat_getChild, Gitsn_Iso14827PublishFormat_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827Publication"), Gitsn_Iso14827Publication_gen, Gitsn_Iso14827Publication_del, Gitsn_Iso14827Publication_setChild, Gitsn_Iso14827Publication_getChild, Gitsn_Iso14827Publication_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827TransferDone"), Gitsn_Iso14827TransferDone_gen, Gitsn_Iso14827TransferDone_del, Gitsn_Iso14827TransferDone_setChild, Gitsn_Iso14827TransferDone_getChild, Gitsn_Iso14827TransferDone_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827AcceptType"), Gitsn_Iso14827AcceptType_gen, Gitsn_Iso14827AcceptType_del, Gitsn_Iso14827AcceptType_setChild, Gitsn_Iso14827AcceptType_getChild, Gitsn_Iso14827AcceptType_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827Accept"), Gitsn_Iso14827Accept_gen, Gitsn_Iso14827Accept_del, Gitsn_Iso14827Accept_setChild, Gitsn_Iso14827Accept_getChild, Gitsn_Iso14827Accept_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827RejectPubData"), Gitsn_Iso14827RejectPubData_gen, Gitsn_Iso14827RejectPubData_del, Gitsn_Iso14827RejectPubData_setChild, Gitsn_Iso14827RejectPubData_getChild, Gitsn_Iso14827RejectPubData_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827RejectType"), Gitsn_Iso14827RejectType_gen, Gitsn_Iso14827RejectType_del, Gitsn_Iso14827RejectType_setChild, Gitsn_Iso14827RejectType_getChild, Gitsn_Iso14827RejectType_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827Reject"), Gitsn_Iso14827Reject_gen, Gitsn_Iso14827Reject_del, Gitsn_Iso14827Reject_setChild, Gitsn_Iso14827Reject_getChild, Gitsn_Iso14827Reject_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827PDUs"), Gitsn_Iso14827PDUs_gen, Gitsn_Iso14827PDUs_del, Gitsn_Iso14827PDUs_setChild, Gitsn_Iso14827PDUs_getChild, Gitsn_Iso14827PDUs_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Iso14827C2CAuthMsg"), Gitsn_Iso14827C2CAuthMsg_gen, Gitsn_Iso14827C2CAuthMsg_del, Gitsn_Iso14827C2CAuthMsg_setChild, Gitsn_Iso14827C2CAuthMsg_getChild, Gitsn_Iso14827C2CAuthMsg_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("PolicePrj4TestConfiguration_centerClient2rse"), PolicePrj4TestConfiguration_centerClient2rse_gen, PolicePrj4TestConfiguration_centerClient2rse_del, PolicePrj4TestConfiguration_centerClient2rse_setChild, PolicePrj4TestConfiguration_centerClient2rse_getChild, PolicePrj4TestConfiguration_centerClient2rse_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("PolicePrj4TestConfiguration_rseServer2center"), PolicePrj4TestConfiguration_rseServer2center_gen, PolicePrj4TestConfiguration_rseServer2center_del, PolicePrj4TestConfiguration_rseServer2center_setChild, PolicePrj4TestConfiguration_rseServer2center_getChild, PolicePrj4TestConfiguration_rseServer2center_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("PolicePrj4TestConfiguration_rseClient2center"), PolicePrj4TestConfiguration_rseClient2center_gen, PolicePrj4TestConfiguration_rseClient2center_del, PolicePrj4TestConfiguration_rseClient2center_setChild, PolicePrj4TestConfiguration_rseClient2center_getChild, PolicePrj4TestConfiguration_rseClient2center_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("PolicePrj4TestConfiguration_centerServer2rse"), PolicePrj4TestConfiguration_centerServer2rse_gen, PolicePrj4TestConfiguration_centerServer2rse_del, PolicePrj4TestConfiguration_centerServer2rse_setChild, PolicePrj4TestConfiguration_centerServer2rse_getChild, PolicePrj4TestConfiguration_centerServer2rse_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("PolicePrj4TestConfiguration_signalserverServer2center"), PolicePrj4TestConfiguration_signalserverServer2center_gen, PolicePrj4TestConfiguration_signalserverServer2center_del, PolicePrj4TestConfiguration_signalserverServer2center_setChild, PolicePrj4TestConfiguration_signalserverServer2center_getChild, PolicePrj4TestConfiguration_signalserverServer2center_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ITSK00100_3TestConfigurationClientRole"), ITSK00100_3TestConfigurationClientRole_gen, ITSK00100_3TestConfigurationClientRole_del, ITSK00100_3TestConfigurationClientRole_setChild, ITSK00100_3TestConfigurationClientRole_getChild, ITSK00100_3TestConfigurationClientRole_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ITSK00100_3TestConfigurationServerRole"), ITSK00100_3TestConfigurationServerRole_gen, ITSK00100_3TestConfigurationServerRole_del, ITSK00100_3TestConfigurationServerRole_setChild, ITSK00100_3TestConfigurationServerRole_getChild, ITSK00100_3TestConfigurationServerRole_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("TechnicalRegulation1TestConfiguration_clientRole1"), TechnicalRegulation1TestConfiguration_clientRole1_gen, TechnicalRegulation1TestConfiguration_clientRole1_del, TechnicalRegulation1TestConfiguration_clientRole1_setChild, TechnicalRegulation1TestConfiguration_clientRole1_getChild, TechnicalRegulation1TestConfiguration_clientRole1_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("TechnicalRegulation1TestConfiguration_serverRole1"), TechnicalRegulation1TestConfiguration_serverRole1_gen, TechnicalRegulation1TestConfiguration_serverRole1_del, TechnicalRegulation1TestConfiguration_serverRole1_setChild, TechnicalRegulation1TestConfiguration_serverRole1_getChild, TechnicalRegulation1TestConfiguration_serverRole1_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("TechnicalRegulation2TestConfiguration_clientRole1"), TechnicalRegulation2TestConfiguration_clientRole1_gen, TechnicalRegulation2TestConfiguration_clientRole1_del, TechnicalRegulation2TestConfiguration_clientRole1_setChild, TechnicalRegulation2TestConfiguration_clientRole1_getChild, TechnicalRegulation2TestConfiguration_clientRole1_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("TechnicalRegulationTestConfiguration_clientRole2"), TechnicalRegulationTestConfiguration_clientRole2_gen, TechnicalRegulationTestConfiguration_clientRole2_del, TechnicalRegulationTestConfiguration_clientRole2_setChild, TechnicalRegulationTestConfiguration_clientRole2_getChild, TechnicalRegulationTestConfiguration_clientRole2_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("TechnicalRegulationTestConfiguration_serverRole2"), TechnicalRegulationTestConfiguration_serverRole2_gen, TechnicalRegulationTestConfiguration_serverRole2_del, TechnicalRegulationTestConfiguration_serverRole2_setChild, TechnicalRegulationTestConfiguration_serverRole2_getChild, TechnicalRegulationTestConfiguration_serverRole2_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("TechnicalRegulationTestConfiguration_duoClientRole"), TechnicalRegulationTestConfiguration_duoClientRole_gen, TechnicalRegulationTestConfiguration_duoClientRole_del, TechnicalRegulationTestConfiguration_duoClientRole_setChild, TechnicalRegulationTestConfiguration_duoClientRole_getChild, TechnicalRegulationTestConfiguration_duoClientRole_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("TechnicalRegulationTestConfiguration_duoSessionRole"), TechnicalRegulationTestConfiguration_duoSessionRole_gen, TechnicalRegulationTestConfiguration_duoSessionRole_del, TechnicalRegulationTestConfiguration_duoSessionRole_setChild, TechnicalRegulationTestConfiguration_duoSessionRole_getChild, TechnicalRegulationTestConfiguration_duoSessionRole_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Iso14827TestConfiguration"), Iso14827TestConfiguration_gen, Iso14827TestConfiguration_del, Iso14827TestConfiguration_setChild, Iso14827TestConfiguration_getChild, Iso14827TestConfiguration_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Iso14827TimeFrac"), Iso14827TimeFrac_gen, Iso14827TimeFrac_del, Iso14827TimeFrac_setChild, Iso14827TimeFrac_getChild, Iso14827TimeFrac_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Iso14827TimeZone"), Iso14827TimeZone_gen, Iso14827TimeZone_del, Iso14827TimeZone_setChild, Iso14827TimeZone_getChild, Iso14827TimeZone_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Iso14827Time"), Iso14827Time_gen, Iso14827Time_del, Iso14827Time_setChild, Iso14827Time_getChild, Iso14827Time_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Iso14827RegisteredContinuous"), Iso14827RegisteredContinuous_gen, Iso14827RegisteredContinuous_del, Iso14827RegisteredContinuous_setChild, Iso14827RegisteredContinuous_getChild, Iso14827RegisteredContinuous_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Iso14827RegisteredDaily"), Iso14827RegisteredDaily_gen, Iso14827RegisteredDaily_del, Iso14827RegisteredDaily_setChild, Iso14827RegisteredDaily_getChild, Iso14827RegisteredDaily_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("SubscribeSpecTypeReg"), SubscribeSpecTypeReg_gen, SubscribeSpecTypeReg_del, SubscribeSpecTypeReg_setChild, SubscribeSpecTypeReg_getChild, SubscribeSpecTypeReg_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("SubscribeSpecTypeRegistered"), SubscribeSpecTypeRegistered_gen, SubscribeSpecTypeRegistered_del, SubscribeSpecTypeRegistered_setChild, SubscribeSpecTypeRegistered_getChild, SubscribeSpecTypeRegistered_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("SubscribeSpecType"), SubscribeSpecType_gen, SubscribeSpecType_del, SubscribeSpecType_setChild, SubscribeSpecType_getChild, SubscribeSpecType_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("SubscribeSpecEntry"), SubscribeSpecEntry_gen, SubscribeSpecEntry_del, SubscribeSpecEntry_setChild, SubscribeSpecEntry_getChild, SubscribeSpecEntry_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("CurrentLinkStateEntry"), CurrentLinkStateEntry_gen, CurrentLinkStateEntry_del, CurrentLinkStateEntry_setChild, CurrentLinkStateEntry_getChild, CurrentLinkStateEntry_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("EventIdentityEntry"), EventIdentityEntry_gen, EventIdentityEntry_del, EventIdentityEntry_setChild, EventIdentityEntry_getChild, EventIdentityEntry_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("IncidentIdentityEntry"), IncidentIdentityEntry_gen, IncidentIdentityEntry_del, IncidentIdentityEntry_setChild, IncidentIdentityEntry_getChild, IncidentIdentityEntry_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("IncidentConditionsEntry"), IncidentConditionsEntry_gen, IncidentConditionsEntry_del, IncidentConditionsEntry_setChild, IncidentConditionsEntry_getChild, IncidentConditionsEntry_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("RoadwaySurfaceStatusEntry"), RoadwaySurfaceStatusEntry_gen, RoadwaySurfaceStatusEntry_del, RoadwaySurfaceStatusEntry_setChild, RoadwaySurfaceStatusEntry_getChild, RoadwaySurfaceStatusEntry_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("WeatherInformationEntry"), WeatherInformationEntry_gen, WeatherInformationEntry_del, WeatherInformationEntry_setChild, WeatherInformationEntry_getChild, WeatherInformationEntry_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("LinkRoadwayGeometryEntry"), LinkRoadwayGeometryEntry_gen, LinkRoadwayGeometryEntry_del, LinkRoadwayGeometryEntry_setChild, LinkRoadwayGeometryEntry_getChild, LinkRoadwayGeometryEntry_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ProbeVehicleDetectionEntry"), ProbeVehicleDetectionEntry_gen, ProbeVehicleDetectionEntry_del, ProbeVehicleDetectionEntry_setChild, ProbeVehicleDetectionEntry_getChild, ProbeVehicleDetectionEntry_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("DetectorCollectionEntry"), DetectorCollectionEntry_gen, DetectorCollectionEntry_del, DetectorCollectionEntry_setChild, DetectorCollectionEntry_getChild, DetectorCollectionEntry_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ExtentionCommPDUEntry"), ExtentionCommPDUEntry_gen, ExtentionCommPDUEntry_del, ExtentionCommPDUEntry_setChild, ExtentionCommPDUEntry_getChild, ExtentionCommPDUEntry_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("TechnicalRegulation1_Eam"), TechnicalRegulation1_Eam_gen, TechnicalRegulation1_Eam_del, TechnicalRegulation1_Eam_setChild, TechnicalRegulation1_Eam_getChild, TechnicalRegulation1_Eam_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_SpeedLimitList"), Gitsn_SpeedLimitList_gen, Gitsn_SpeedLimitList_del, Gitsn_SpeedLimitList_append, Gitsn_SpeedLimitList_cnt, Gitsn_SpeedLimitList_tlv, Dz1Text("Gitsn_RegulatorySpeedLimit") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_NodeAttributeXYList"), Gitsn_NodeAttributeXYList_gen, Gitsn_NodeAttributeXYList_del, Gitsn_NodeAttributeXYList_append, Gitsn_NodeAttributeXYList_cnt, Gitsn_NodeAttributeXYList_tlv, Dz1Text("Gitsn_NodeAttributeXY") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_SegmentAttributeXYList"), Gitsn_SegmentAttributeXYList_gen, Gitsn_SegmentAttributeXYList_del, Gitsn_SegmentAttributeXYList_append, Gitsn_SegmentAttributeXYList_cnt, Gitsn_SegmentAttributeXYList_tlv, Dz1Text("Gitsn_SegmentAttributeXY") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_LaneDataAttributeList"), Gitsn_LaneDataAttributeList_gen, Gitsn_LaneDataAttributeList_del, Gitsn_LaneDataAttributeList_append, Gitsn_LaneDataAttributeList_cnt, Gitsn_LaneDataAttributeList_tlv, Dz1Text("Gitsn_LaneDataAttribute") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_NodeSetXY"), Gitsn_NodeSetXY_gen, Gitsn_NodeSetXY_del, Gitsn_NodeSetXY_append, Gitsn_NodeSetXY_cnt, Gitsn_NodeSetXY_tlv, Dz1Text("Gitsn_NodeXY") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_ConnectsToList"), Gitsn_ConnectsToList_gen, Gitsn_ConnectsToList_del, Gitsn_ConnectsToList_append, Gitsn_ConnectsToList_cnt, Gitsn_ConnectsToList_tlv, Dz1Text("Gitsn_Connection") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_OverlayLaneList"), Gitsn_OverlayLaneList_gen, Gitsn_OverlayLaneList_del, Gitsn_OverlayLaneList_append, Gitsn_OverlayLaneList_cnt, Gitsn_OverlayLaneList_tlv, Dz1Text("s64_t") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_LaneList"), Gitsn_LaneList_gen, Gitsn_LaneList_del, Gitsn_LaneList_append, Gitsn_LaneList_cnt, Gitsn_LaneList_tlv, Dz1Text("Gitsn_GenericLane") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_PreemptPriorityList"), Gitsn_PreemptPriorityList_gen, Gitsn_PreemptPriorityList_del, Gitsn_PreemptPriorityList_append, Gitsn_PreemptPriorityList_cnt, Gitsn_PreemptPriorityList_tlv, Dz1Text("Gitsn_SignalControlZone") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_IntersectionGeometryList"), Gitsn_IntersectionGeometryList_gen, Gitsn_IntersectionGeometryList_del, Gitsn_IntersectionGeometryList_append, Gitsn_IntersectionGeometryList_cnt, Gitsn_IntersectionGeometryList_tlv, Dz1Text("Gitsn_IntersectionGeometry") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_RoadLaneSetList"), Gitsn_RoadLaneSetList_gen, Gitsn_RoadLaneSetList_del, Gitsn_RoadLaneSetList_append, Gitsn_RoadLaneSetList_cnt, Gitsn_RoadLaneSetList_tlv, Dz1Text("Gitsn_GenericLane") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_RoadSegmentList"), Gitsn_RoadSegmentList_gen, Gitsn_RoadSegmentList_del, Gitsn_RoadSegmentList_append, Gitsn_RoadSegmentList_cnt, Gitsn_RoadSegmentList_tlv, Dz1Text("Gitsn_RoadSegment") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_RestrictionUserTypeList"), Gitsn_RestrictionUserTypeList_gen, Gitsn_RestrictionUserTypeList_del, Gitsn_RestrictionUserTypeList_append, Gitsn_RestrictionUserTypeList_cnt, Gitsn_RestrictionUserTypeList_tlv, Dz1Text("Gitsn_RestrictionUserType") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_RestrictionClassList"), Gitsn_RestrictionClassList_gen, Gitsn_RestrictionClassList_del, Gitsn_RestrictionClassList_append, Gitsn_RestrictionClassList_cnt, Gitsn_RestrictionClassList_tlv, Dz1Text("Gitsn_RestrictionClassAssignment") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_EnabledLaneList"), Gitsn_EnabledLaneList_gen, Gitsn_EnabledLaneList_del, Gitsn_EnabledLaneList_append, Gitsn_EnabledLaneList_cnt, Gitsn_EnabledLaneList_tlv, Dz1Text("s64_t") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_AdvisorySpeedList"), Gitsn_AdvisorySpeedList_gen, Gitsn_AdvisorySpeedList_del, Gitsn_AdvisorySpeedList_append, Gitsn_AdvisorySpeedList_cnt, Gitsn_AdvisorySpeedList_tlv, Dz1Text("Gitsn_AdvisorySpeed") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_MovementEventList"), Gitsn_MovementEventList_gen, Gitsn_MovementEventList_del, Gitsn_MovementEventList_append, Gitsn_MovementEventList_cnt, Gitsn_MovementEventList_tlv, Dz1Text("Gitsn_MovementEvent") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_ManeuverAssistList"), Gitsn_ManeuverAssistList_gen, Gitsn_ManeuverAssistList_del, Gitsn_ManeuverAssistList_append, Gitsn_ManeuverAssistList_cnt, Gitsn_ManeuverAssistList_tlv, Dz1Text("Gitsn_ConnectionManeuverAssist") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_MovementList"), Gitsn_MovementList_gen, Gitsn_MovementList_del, Gitsn_MovementList_append, Gitsn_MovementList_cnt, Gitsn_MovementList_tlv, Dz1Text("Gitsn_MovementState") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_IntersectionStateList"), Gitsn_IntersectionStateList_gen, Gitsn_IntersectionStateList_del, Gitsn_IntersectionStateList_append, Gitsn_IntersectionStateList_cnt, Gitsn_IntersectionStateList_tlv, Dz1Text("Gitsn_IntersectionState") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_PathHistoryPointList"), Gitsn_PathHistoryPointList_gen, Gitsn_PathHistoryPointList_del, Gitsn_PathHistoryPointList_append, Gitsn_PathHistoryPointList_cnt, Gitsn_PathHistoryPointList_tlv, Dz1Text("Gitsn_PathHistoryPoint") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_TireDataList"), Gitsn_TireDataList_gen, Gitsn_TireDataList_del, Gitsn_TireDataList_append, Gitsn_TireDataList_cnt, Gitsn_TireDataList_tlv, Dz1Text("Gitsn_TireData") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_AxleWeightList"), Gitsn_AxleWeightList_gen, Gitsn_AxleWeightList_del, Gitsn_AxleWeightList_append, Gitsn_AxleWeightList_cnt, Gitsn_AxleWeightList_tlv, Dz1Text("Gitsn_AxleWeightSet") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_ProbeVehicleData_snapshots"), Gitsn_ProbeVehicleData_snapshots_gen, Gitsn_ProbeVehicleData_snapshots_del, Gitsn_ProbeVehicleData_snapshots_append, Gitsn_ProbeVehicleData_snapshots_cnt, Gitsn_ProbeVehicleData_snapshots_tlv, Dz1Text("Gitsn_Snapshot") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_RoadSideAlert_description"), Gitsn_RoadSideAlert_description_gen, Gitsn_RoadSideAlert_description_del, Gitsn_RoadSideAlert_description_append, Gitsn_RoadSideAlert_description_cnt, Gitsn_RoadSideAlert_description_tlv, Dz1Text("s64_t") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_NodeAttributeLLList"), Gitsn_NodeAttributeLLList_gen, Gitsn_NodeAttributeLLList_del, Gitsn_NodeAttributeLLList_append, Gitsn_NodeAttributeLLList_cnt, Gitsn_NodeAttributeLLList_tlv, Dz1Text("Gitsn_NodeAttributeLL") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_SegmentAttributeLLList"), Gitsn_SegmentAttributeLLList_gen, Gitsn_SegmentAttributeLLList_del, Gitsn_SegmentAttributeLLList_append, Gitsn_SegmentAttributeLLList_cnt, Gitsn_SegmentAttributeLLList_tlv, Dz1Text("Gitsn_SegmentAttributeLL") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_NodeSetLL"), Gitsn_NodeSetLL_gen, Gitsn_NodeSetLL_del, Gitsn_NodeSetLL_append, Gitsn_NodeSetLL_cnt, Gitsn_NodeSetLL_tlv, Dz1Text("Gitsn_NodeLL") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_RegionList"), Gitsn_RegionList_gen, Gitsn_RegionList_del, Gitsn_RegionList_append, Gitsn_RegionList_cnt, Gitsn_RegionList_tlv, Dz1Text("Gitsn_RegionOffsets") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_TravelerDataFrame_regions"), Gitsn_TravelerDataFrame_regions_gen, Gitsn_TravelerDataFrame_regions_del, Gitsn_TravelerDataFrame_regions_append, Gitsn_TravelerDataFrame_regions_cnt, Gitsn_TravelerDataFrame_regions_tlv, Dz1Text("Gitsn_GeographicalPath") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_ITIScodesAndText"), Gitsn_ITIScodesAndText_gen, Gitsn_ITIScodesAndText_del, Gitsn_ITIScodesAndText_append, Gitsn_ITIScodesAndText_cnt, Gitsn_ITIScodesAndText_tlv, Dz1Text("Gitsn_ITIScodesAndText_element") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_WorkZone"), Gitsn_WorkZone_gen, Gitsn_WorkZone_del, Gitsn_WorkZone_append, Gitsn_WorkZone_cnt, Gitsn_WorkZone_tlv, Dz1Text("Gitsn_WorkZone_element") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_GenericSignage"), Gitsn_GenericSignage_gen, Gitsn_GenericSignage_del, Gitsn_GenericSignage_append, Gitsn_GenericSignage_cnt, Gitsn_GenericSignage_tlv, Dz1Text("Gitsn_GenericSignage_element") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_SpeedLimit"), Gitsn_SpeedLimit_gen, Gitsn_SpeedLimit_del, Gitsn_SpeedLimit_append, Gitsn_SpeedLimit_cnt, Gitsn_SpeedLimit_tlv, Dz1Text("Gitsn_SpeedLimit_element") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_ExitService"), Gitsn_ExitService_gen, Gitsn_ExitService_del, Gitsn_ExitService_append, Gitsn_ExitService_cnt, Gitsn_ExitService_tlv, Dz1Text("Gitsn_ExitService_element") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_TravelerDataFrameList"), Gitsn_TravelerDataFrameList_gen, Gitsn_TravelerDataFrameList_del, Gitsn_TravelerDataFrameList_append, Gitsn_TravelerDataFrameList_cnt, Gitsn_TravelerDataFrameList_tlv, Dz1Text("Gitsn_TravelerDataFrame") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_DetectedObjectList"), Gitsn_DetectedObjectList_gen, Gitsn_DetectedObjectList_del, Gitsn_DetectedObjectList_append, Gitsn_DetectedObjectList_cnt, Gitsn_DetectedObjectList_tlv, Dz1Text("Gitsn_DetectedObjectData") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_TrafficLightStatusList"), Gitsn_TrafficLightStatusList_gen, Gitsn_TrafficLightStatusList_del, Gitsn_TrafficLightStatusList_append, Gitsn_TrafficLightStatusList_cnt, Gitsn_TrafficLightStatusList_tlv, Dz1Text("Gitsn_TrafficLightStatus") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_Dz1OIDList"), Gitsn_Dz1OIDList_gen, Gitsn_Dz1OIDList_del, Gitsn_Dz1OIDList_append, Gitsn_Dz1OIDList_cnt, Gitsn_Dz1OIDList_tlv, Dz1Text("Dz1Str") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_Iso14827PublicationDataList"), Gitsn_Iso14827PublicationDataList_gen, Gitsn_Iso14827PublicationDataList_del, Gitsn_Iso14827PublicationDataList_append, Gitsn_Iso14827PublicationDataList_cnt, Gitsn_Iso14827PublicationDataList_tlv, Dz1Text("Gitsn_Iso14827PublicationData") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("SubscribeSpecList"), SubscribeSpecList_gen, SubscribeSpecList_del, SubscribeSpecList_append, SubscribeSpecList_cnt, SubscribeSpecList_tlv, Dz1Text("SubscribeSpecEntry") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("CurrentLinkStateList"), CurrentLinkStateList_gen, CurrentLinkStateList_del, CurrentLinkStateList_append, CurrentLinkStateList_cnt, CurrentLinkStateList_tlv, Dz1Text("CurrentLinkStateEntry") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("EventIdentityList"), EventIdentityList_gen, EventIdentityList_del, EventIdentityList_append, EventIdentityList_cnt, EventIdentityList_tlv, Dz1Text("EventIdentityEntry") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("IncidentIdentityList"), IncidentIdentityList_gen, IncidentIdentityList_del, IncidentIdentityList_append, IncidentIdentityList_cnt, IncidentIdentityList_tlv, Dz1Text("IncidentIdentityEntry") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("IncidentConditionsList"), IncidentConditionsList_gen, IncidentConditionsList_del, IncidentConditionsList_append, IncidentConditionsList_cnt, IncidentConditionsList_tlv, Dz1Text("IncidentConditionsEntry") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("RoadwaySurfaceStatusList"), RoadwaySurfaceStatusList_gen, RoadwaySurfaceStatusList_del, RoadwaySurfaceStatusList_append, RoadwaySurfaceStatusList_cnt, RoadwaySurfaceStatusList_tlv, Dz1Text("RoadwaySurfaceStatusEntry") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("WeatherInformationList"), WeatherInformationList_gen, WeatherInformationList_del, WeatherInformationList_append, WeatherInformationList_cnt, WeatherInformationList_tlv, Dz1Text("WeatherInformationEntry") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("LinkRoadwayGeometryList"), LinkRoadwayGeometryList_gen, LinkRoadwayGeometryList_del, LinkRoadwayGeometryList_append, LinkRoadwayGeometryList_cnt, LinkRoadwayGeometryList_tlv, Dz1Text("LinkRoadwayGeometryEntry") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("ProbeVehicleDetectionList"), ProbeVehicleDetectionList_gen, ProbeVehicleDetectionList_del, ProbeVehicleDetectionList_append, ProbeVehicleDetectionList_cnt, ProbeVehicleDetectionList_tlv, Dz1Text("ProbeVehicleDetectionEntry") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("DetectorCollectionList"), DetectorCollectionList_gen, DetectorCollectionList_del, DetectorCollectionList_append, DetectorCollectionList_cnt, DetectorCollectionList_tlv, Dz1Text("DetectorCollectionEntry") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("ExtentionCommPDUList"), ExtentionCommPDUList_gen, ExtentionCommPDUList_del, ExtentionCommPDUList_append, ExtentionCommPDUList_cnt, ExtentionCommPDUList_tlv, Dz1Text("ExtentionCommPDUEntry") )).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
Dz1JsonSpec *Iso14827TestHelperDef_genJsonSpec(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonSpec *ret = Dz1JsonSpec_generate(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonSpec_delAndSetNull, (void *)&ret);

		if (Iso14827TestHelperDef_initJsonSpec(ret, errp) == FALSE) ERR_OUT(errp);
		else if (Dz1JsonSpec_check(ret, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1JsonSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Dz1JsonSpec Initializer
////////////////////////////////////////////////////////////////////////////////

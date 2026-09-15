#include "ITSK00144_2TestScenarioDefJson.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1Binary
// extern type
// Dz1Binary
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ProtocolFrame
static bool_t ITSK00144_2ProtocolFrame_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ITSK00144_2ProtocolFrame *p = (ITSK00144_2ProtocolFrame *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->length =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: Dz1Binary_delAndSetNull(&p->context); p->context = (Dz1Binary *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: p->crc =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ITSK00144_2ProtocolFrame_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ITSK00144_2ProtocolFrame *p = (ITSK00144_2ProtocolFrame *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->length;
	case 1: return p->context;
	case 2: return &p->crc;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ITSK00144_2ProtocolFrame_membs[] =
{
	{ Dz1Text("length"), Dz1Text("u16_t"), 0 },
	{ Dz1Text("context"), Dz1Text("Dz1Binary"), 1 },
	{ Dz1Text("crc"), Dz1Text("u16_t"), 2 },
	{ NULL, NULL, -1 }
};
// ITSK00144_2ProtocolFrame
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2NotifyStateContext
static bool_t ITSK00144_2NotifyStateContext_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ITSK00144_2NotifyStateContext *p = (ITSK00144_2NotifyStateContext *)ptr;

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

static void *ITSK00144_2NotifyStateContext_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ITSK00144_2NotifyStateContext *p = (ITSK00144_2NotifyStateContext *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->testName;
	case 1: return &p->time;
	case 2: return p->state;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ITSK00144_2NotifyStateContext_membs[] =
{
	{ Dz1Text("testName"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("time"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("state"), Dz1Text("Dz1Str"), 2 },
	{ NULL, NULL, -1 }
};
// ITSK00144_2NotifyStateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2NotifyInfoContext
static bool_t ITSK00144_2NotifyInfoContext_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ITSK00144_2NotifyInfoContext *p = (ITSK00144_2NotifyInfoContext *)ptr;

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

static void *ITSK00144_2NotifyInfoContext_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ITSK00144_2NotifyInfoContext *p = (ITSK00144_2NotifyInfoContext *)ptr;
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

static Dz1JsonSpecChild ITSK00144_2NotifyInfoContext_membs[] =
{
	{ Dz1Text("testName"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("time"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("sender"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("log"), Dz1Text("Dz1Str"), 3 },
	{ Dz1Text("data"), Dz1Text("Dz1Binary"), 4 },
	{ Dz1Text("dataType"), Dz1Text("Dz1Str"), 5 },
	{ NULL, NULL, -1 }
};
// ITSK00144_2NotifyInfoContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ProcessStatusCode
static bool_t ITSK00144_2ProcessStatusCode_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ITSK00144_2ProcessStatusCode v = ITSK00144_2ProcessStatusCode_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (ITSK00144_2ProcessStatusCode)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = ITSK00144_2ProcessStatusCodeFromStr(tok->v)) == ITSK00144_2ProcessStatusCode_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = ITSK00144_2ProcessStatusCode_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t ITSK00144_2ProcessStatusCode_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		ITSK00144_2ProcessStatusCode v = *(ITSK00144_2ProcessStatusCode *)obj;
		Dz1Str str_v = ITSK00144_2ProcessStatusCodeStr(v);
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
// ITSK00144_2ProcessStatusCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2NotifyErrorContext
static bool_t ITSK00144_2NotifyErrorContext_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ITSK00144_2NotifyErrorContext *p = (ITSK00144_2NotifyErrorContext *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->testName); p->testName = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->time =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->code =  *(ITSK00144_2ProcessStatusCode *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: Dz1Str_delAndSetNull(&p->desc); p->desc = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 4: Dz1Str_delAndSetNull(&p->log); p->log = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 5: Dz1Binary_delAndSetNull(&p->data); p->data = (Dz1Binary *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ITSK00144_2NotifyErrorContext_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ITSK00144_2NotifyErrorContext *p = (ITSK00144_2NotifyErrorContext *)ptr;
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

static Dz1JsonSpecChild ITSK00144_2NotifyErrorContext_membs[] =
{
	{ Dz1Text("testName"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("time"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("code"), Dz1Text("ITSK00144_2ProcessStatusCode"), 2 },
	{ Dz1Text("desc"), Dz1Text("Dz1Str"), 3 },
	{ Dz1Text("log"), Dz1Text("Dz1Str"), 4 },
	{ Dz1Text("data"), Dz1Text("Dz1Binary"), 5 },
	{ NULL, NULL, -1 }
};
// ITSK00144_2NotifyErrorContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2NotifyContext
static bool_t ITSK00144_2NotifyContext_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ITSK00144_2NotifyContext *p = (ITSK00144_2NotifyContext *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case ITSK00144_2NotifyContextPresent_state: ITSK00144_2NotifyStateContext_delAndSetNull(&p->x.state); p->x.state =(ITSK00144_2NotifyStateContext *)info->data; info->data = NULL; break;
	case ITSK00144_2NotifyContextPresent_info: ITSK00144_2NotifyInfoContext_delAndSetNull(&p->x.info); p->x.info =(ITSK00144_2NotifyInfoContext *)info->data; info->data = NULL; break;
	case ITSK00144_2NotifyContextPresent_error: ITSK00144_2NotifyErrorContext_delAndSetNull(&p->x.error); p->x.error =(ITSK00144_2NotifyErrorContext *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (ITSK00144_2NotifyContextPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ITSK00144_2NotifyContext_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ITSK00144_2NotifyContext *p = (ITSK00144_2NotifyContext *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case ITSK00144_2NotifyContextPresent_state: return p->x.state;
		case ITSK00144_2NotifyContextPresent_info: return p->x.info;
		case ITSK00144_2NotifyContextPresent_error: return p->x.error;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild ITSK00144_2NotifyContext_membs[] =
{
	{ Dz1Text("state"), Dz1Text("ITSK00144_2NotifyStateContext"), ITSK00144_2NotifyContextPresent_state },
	{ Dz1Text("info"), Dz1Text("ITSK00144_2NotifyInfoContext"), ITSK00144_2NotifyContextPresent_info },
	{ Dz1Text("error"), Dz1Text("ITSK00144_2NotifyErrorContext"), ITSK00144_2NotifyContextPresent_error },
	{ NULL, NULL, -1 }
};
// ITSK00144_2NotifyContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ValidateContext
static bool_t ITSK00144_2ValidateContext_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ITSK00144_2ValidateContext *p = (ITSK00144_2ValidateContext *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->testName); p->testName = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->time =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: Dz1Binary_delAndSetNull(&p->raw); p->raw = (Dz1Binary *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: Dz1Binary_delAndSetNull(&p->data); p->data = (Dz1Binary *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 4: p->code =  *(ITSK00144_2ProcessStatusCode *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: Dz1Str_delAndSetNull(&p->desc); p->desc = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ITSK00144_2ValidateContext_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ITSK00144_2ValidateContext *p = (ITSK00144_2ValidateContext *)ptr;
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

static Dz1JsonSpecChild ITSK00144_2ValidateContext_membs[] =
{
	{ Dz1Text("testName"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("time"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("raw"), Dz1Text("Dz1Binary"), 2 },
	{ Dz1Text("data"), Dz1Text("Dz1Binary"), 3 },
	{ Dz1Text("code"), Dz1Text("ITSK00144_2ProcessStatusCode"), 4 },
	{ Dz1Text("desc"), Dz1Text("Dz1Str"), 5 },
	{ NULL, NULL, -1 }
};
// ITSK00144_2ValidateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2TestConfiguration_ServerRole
static bool_t ITSK00144_2TestConfiguration_ServerRole_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ITSK00144_2TestConfiguration_ServerRole *p = (ITSK00144_2TestConfiguration_ServerRole *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->local_port =  *(u64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->serial_no =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->test_rsp_link_unit_status =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->test_rsp_status =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->test_rsp_list =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->test_rsp_update_list =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->test_rsp_reset =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->test_session_maintain =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->hb_duration =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ITSK00144_2TestConfiguration_ServerRole_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ITSK00144_2TestConfiguration_ServerRole *p = (ITSK00144_2TestConfiguration_ServerRole *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->local_port;
	case 1: return &p->serial_no;
	case 2: return &p->test_rsp_link_unit_status;
	case 3: return &p->test_rsp_status;
	case 4: return &p->test_rsp_list;
	case 5: return &p->test_rsp_update_list;
	case 6: return &p->test_rsp_reset;
	case 7: return &p->test_session_maintain;
	case 8: return &p->hb_duration;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ITSK00144_2TestConfiguration_ServerRole_membs[] =
{
	{ Dz1Text("local_port"), Dz1Text("u64_t"), 0 },
	{ Dz1Text("serial_no"), Dz1Text("u32_t"), 1 },
	{ Dz1Text("test_rsp_link_unit_status"), Dz1Text("bool_t"), 2 },
	{ Dz1Text("test_rsp_status"), Dz1Text("bool_t"), 3 },
	{ Dz1Text("test_rsp_list"), Dz1Text("bool_t"), 4 },
	{ Dz1Text("test_rsp_update_list"), Dz1Text("bool_t"), 5 },
	{ Dz1Text("test_rsp_reset"), Dz1Text("bool_t"), 6 },
	{ Dz1Text("test_session_maintain"), Dz1Text("bool_t"), 7 },
	{ Dz1Text("hb_duration"), Dz1Text("s64_t"), 8 },
	{ NULL, NULL, -1 }
};
// ITSK00144_2TestConfiguration_ServerRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2TestConfiguration_LinkUnitRole
static bool_t ITSK00144_2TestConfiguration_LinkUnitRole_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ITSK00144_2TestConfiguration_LinkUnitRole *p = (ITSK00144_2TestConfiguration_LinkUnitRole *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->peer_ip); p->peer_ip = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->peer_port =  *(u64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->serial_no =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->test_req_link_unit_status =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->test_req_status =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->test_req_list =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->test_req_update_list =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->test_req_reset =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->test_session_maintain =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 9: p->hb_duration =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 10: p->test_tim =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 11: p->test_map =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ITSK00144_2TestConfiguration_LinkUnitRole_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ITSK00144_2TestConfiguration_LinkUnitRole *p = (ITSK00144_2TestConfiguration_LinkUnitRole *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->peer_ip;
	case 1: return &p->peer_port;
	case 2: return &p->serial_no;
	case 3: return &p->test_req_link_unit_status;
	case 4: return &p->test_req_status;
	case 5: return &p->test_req_list;
	case 6: return &p->test_req_update_list;
	case 7: return &p->test_req_reset;
	case 8: return &p->test_session_maintain;
	case 9: return &p->hb_duration;
	case 10: return &p->test_tim;
	case 11: return &p->test_map;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ITSK00144_2TestConfiguration_LinkUnitRole_membs[] =
{
	{ Dz1Text("peer_ip"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("peer_port"), Dz1Text("u64_t"), 1 },
	{ Dz1Text("serial_no"), Dz1Text("u32_t"), 2 },
	{ Dz1Text("test_req_link_unit_status"), Dz1Text("bool_t"), 3 },
	{ Dz1Text("test_req_status"), Dz1Text("bool_t"), 4 },
	{ Dz1Text("test_req_list"), Dz1Text("bool_t"), 5 },
	{ Dz1Text("test_req_update_list"), Dz1Text("bool_t"), 6 },
	{ Dz1Text("test_req_reset"), Dz1Text("bool_t"), 7 },
	{ Dz1Text("test_session_maintain"), Dz1Text("bool_t"), 8 },
	{ Dz1Text("hb_duration"), Dz1Text("s64_t"), 9 },
	{ Dz1Text("test_tim"), Dz1Text("bool_t"), 10 },
	{ Dz1Text("test_map"), Dz1Text("bool_t"), 11 },
	{ NULL, NULL, -1 }
};
// ITSK00144_2TestConfiguration_LinkUnitRole
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2TestConfiguration
static bool_t ITSK00144_2TestConfiguration_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ITSK00144_2TestConfiguration *p = (ITSK00144_2TestConfiguration *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case ITSK00144_2TestConfigurationPresent_serverRole: ITSK00144_2TestConfiguration_ServerRole_delAndSetNull(&p->x.serverRole); p->x.serverRole =(ITSK00144_2TestConfiguration_ServerRole *)info->data; info->data = NULL; break;
	case ITSK00144_2TestConfigurationPresent_linkUnitRole: ITSK00144_2TestConfiguration_LinkUnitRole_delAndSetNull(&p->x.linkUnitRole); p->x.linkUnitRole =(ITSK00144_2TestConfiguration_LinkUnitRole *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (ITSK00144_2TestConfigurationPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ITSK00144_2TestConfiguration_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ITSK00144_2TestConfiguration *p = (ITSK00144_2TestConfiguration *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case ITSK00144_2TestConfigurationPresent_serverRole: return p->x.serverRole;
		case ITSK00144_2TestConfigurationPresent_linkUnitRole: return p->x.linkUnitRole;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild ITSK00144_2TestConfiguration_membs[] =
{
	{ Dz1Text("serverRole"), Dz1Text("ITSK00144_2TestConfiguration_ServerRole"), ITSK00144_2TestConfigurationPresent_serverRole },
	{ Dz1Text("linkUnitRole"), Dz1Text("ITSK00144_2TestConfiguration_LinkUnitRole"), ITSK00144_2TestConfigurationPresent_linkUnitRole },
	{ NULL, NULL, -1 }
};
// ITSK00144_2TestConfiguration
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// I2XTrafficSafetyDeviceSerialNo
static bool_t I2XTrafficSafetyDeviceSerialNo_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	I2XTrafficSafetyDeviceSerialNo *p = (I2XTrafficSafetyDeviceSerialNo *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->type =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->id =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *I2XTrafficSafetyDeviceSerialNo_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	I2XTrafficSafetyDeviceSerialNo *p = (I2XTrafficSafetyDeviceSerialNo *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->type;
	case 1: return &p->id;
	default: return NULL;
	}
}

static Dz1JsonSpecChild I2XTrafficSafetyDeviceSerialNo_membs[] =
{
	{ Dz1Text("type"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("id"), Dz1Text("u32_t"), 1 },
	{ NULL, NULL, -1 }
};
// I2XTrafficSafetyDeviceSerialNo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2Reserved0
static bool_t ITSK00144_2Reserved0_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ITSK00144_2Reserved0 *p = (ITSK00144_2Reserved0 *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->reserved1 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->reserved2 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->reserved3 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->reserved4 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->reserved5 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->reserved6 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->reserved7 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->reserved8 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->reserved9 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ITSK00144_2Reserved0_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ITSK00144_2Reserved0 *p = (ITSK00144_2Reserved0 *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->reserved1;
	case 1: return &p->reserved2;
	case 2: return &p->reserved3;
	case 3: return &p->reserved4;
	case 4: return &p->reserved5;
	case 5: return &p->reserved6;
	case 6: return &p->reserved7;
	case 7: return &p->reserved8;
	case 8: return &p->reserved9;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ITSK00144_2Reserved0_membs[] =
{
	{ Dz1Text("reserved1"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("reserved2"), Dz1Text("u8_t"), 1 },
	{ Dz1Text("reserved3"), Dz1Text("u8_t"), 2 },
	{ Dz1Text("reserved4"), Dz1Text("u8_t"), 3 },
	{ Dz1Text("reserved5"), Dz1Text("u8_t"), 4 },
	{ Dz1Text("reserved6"), Dz1Text("u8_t"), 5 },
	{ Dz1Text("reserved7"), Dz1Text("u8_t"), 6 },
	{ Dz1Text("reserved8"), Dz1Text("u8_t"), 7 },
	{ Dz1Text("reserved9"), Dz1Text("u8_t"), 8 },
	{ NULL, NULL, -1 }
};
// ITSK00144_2Reserved0
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// I2XTrafficSafetyDeviceLinkUnitStatus
static bool_t I2XTrafficSafetyDeviceLinkUnitStatus_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	I2XTrafficSafetyDeviceLinkUnitStatus *p = (I2XTrafficSafetyDeviceLinkUnitStatus *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->isActive =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->control_comm =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->wave_comm =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->temperature =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->humidity =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->isOpen =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->isFanOn =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->isHeaterOn =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *I2XTrafficSafetyDeviceLinkUnitStatus_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	I2XTrafficSafetyDeviceLinkUnitStatus *p = (I2XTrafficSafetyDeviceLinkUnitStatus *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->isActive;
	case 1: return &p->control_comm;
	case 2: return &p->wave_comm;
	case 3: return &p->temperature;
	case 4: return &p->humidity;
	case 5: return &p->isOpen;
	case 6: return &p->isFanOn;
	case 7: return &p->isHeaterOn;
	default: return NULL;
	}
}

static Dz1JsonSpecChild I2XTrafficSafetyDeviceLinkUnitStatus_membs[] =
{
	{ Dz1Text("isActive"), Dz1Text("bool_t"), 0 },
	{ Dz1Text("control_comm"), Dz1Text("bool_t"), 1 },
	{ Dz1Text("wave_comm"), Dz1Text("bool_t"), 2 },
	{ Dz1Text("temperature"), Dz1Text("u8_t"), 3 },
	{ Dz1Text("humidity"), Dz1Text("u8_t"), 4 },
	{ Dz1Text("isOpen"), Dz1Text("bool_t"), 5 },
	{ Dz1Text("isFanOn"), Dz1Text("bool_t"), 6 },
	{ Dz1Text("isHeaterOn"), Dz1Text("bool_t"), 7 },
	{ NULL, NULL, -1 }
};
// I2XTrafficSafetyDeviceLinkUnitStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// I2XTrafficSafetyDeviceStatus
static bool_t I2XTrafficSafetyDeviceStatus_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	I2XTrafficSafetyDeviceStatus *p = (I2XTrafficSafetyDeviceStatus *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: I2XTrafficSafetyDeviceSerialNo_delAndSetNull(&p->id); p->id = (I2XTrafficSafetyDeviceSerialNo *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: p->isActive =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->isBatteryOn =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->isPowered =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->isPowerOn =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->isConnected =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->cnt =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *I2XTrafficSafetyDeviceStatus_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	I2XTrafficSafetyDeviceStatus *p = (I2XTrafficSafetyDeviceStatus *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->id;
	case 1: return &p->isActive;
	case 2: return &p->isBatteryOn;
	case 3: return &p->isPowered;
	case 4: return &p->isPowerOn;
	case 5: return &p->isConnected;
	case 6: return &p->cnt;
	default: return NULL;
	}
}

static Dz1JsonSpecChild I2XTrafficSafetyDeviceStatus_membs[] =
{
	{ Dz1Text("id"), Dz1Text("I2XTrafficSafetyDeviceSerialNo"), 0 },
	{ Dz1Text("isActive"), Dz1Text("bool_t"), 1 },
	{ Dz1Text("isBatteryOn"), Dz1Text("bool_t"), 2 },
	{ Dz1Text("isPowered"), Dz1Text("bool_t"), 3 },
	{ Dz1Text("isPowerOn"), Dz1Text("bool_t"), 4 },
	{ Dz1Text("isConnected"), Dz1Text("bool_t"), 5 },
	{ Dz1Text("cnt"), Dz1Text("u8_t"), 6 },
	{ NULL, NULL, -1 }
};
// I2XTrafficSafetyDeviceStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// I2XTrafficSafetyDeviceStatusList
static bool_t I2XTrafficSafetyDeviceStatusList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	I2XTrafficSafetyDeviceStatusList *dst = (I2XTrafficSafetyDeviceStatusList *)dst_ptr;
	I2XTrafficSafetyDeviceStatus *node = NULL;
	if (dst == NULL || var == NULL || (node = (I2XTrafficSafetyDeviceStatus *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t I2XTrafficSafetyDeviceStatusList_cnt(void *ptr)
{
	u32_t ret = 0;
	I2XTrafficSafetyDeviceStatusList *list = (I2XTrafficSafetyDeviceStatusList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error I2XTrafficSafetyDeviceStatusList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	I2XTrafficSafetyDeviceStatusList *list = (I2XTrafficSafetyDeviceStatusList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// I2XTrafficSafetyDeviceStatusList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// I2XTrafficSafetyDeviceStatusInfo
static bool_t I2XTrafficSafetyDeviceStatusInfo_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	I2XTrafficSafetyDeviceStatusInfo *p = (I2XTrafficSafetyDeviceStatusInfo *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->num =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: I2XTrafficSafetyDeviceStatusList_delAndSetNull(&p->status); p->status = (I2XTrafficSafetyDeviceStatusList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *I2XTrafficSafetyDeviceStatusInfo_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	I2XTrafficSafetyDeviceStatusInfo *p = (I2XTrafficSafetyDeviceStatusInfo *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->num;
	case 1: return p->status;
	default: return NULL;
	}
}

static Dz1JsonSpecChild I2XTrafficSafetyDeviceStatusInfo_membs[] =
{
	{ Dz1Text("num"), Dz1Text("u16_t"), 0 },
	{ Dz1Text("status"), Dz1Text("I2XTrafficSafetyDeviceStatusList"), 1 },
	{ NULL, NULL, -1 }
};
// I2XTrafficSafetyDeviceStatusInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// I2XTrafficSafetyDeviceSerialNoList
static bool_t I2XTrafficSafetyDeviceSerialNoList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	I2XTrafficSafetyDeviceSerialNoList *dst = (I2XTrafficSafetyDeviceSerialNoList *)dst_ptr;
	I2XTrafficSafetyDeviceSerialNo *node = NULL;
	if (dst == NULL || var == NULL || (node = (I2XTrafficSafetyDeviceSerialNo *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t I2XTrafficSafetyDeviceSerialNoList_cnt(void *ptr)
{
	u32_t ret = 0;
	I2XTrafficSafetyDeviceSerialNoList *list = (I2XTrafficSafetyDeviceSerialNoList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error I2XTrafficSafetyDeviceSerialNoList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	I2XTrafficSafetyDeviceSerialNoList *list = (I2XTrafficSafetyDeviceSerialNoList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// I2XTrafficSafetyDeviceSerialNoList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// I2XTrafficSafetyDeviceList
static bool_t I2XTrafficSafetyDeviceList_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	I2XTrafficSafetyDeviceList *p = (I2XTrafficSafetyDeviceList *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->cnt =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: I2XTrafficSafetyDeviceSerialNoList_delAndSetNull(&p->id); p->id = (I2XTrafficSafetyDeviceSerialNoList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *I2XTrafficSafetyDeviceList_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	I2XTrafficSafetyDeviceList *p = (I2XTrafficSafetyDeviceList *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->cnt;
	case 1: return p->id;
	default: return NULL;
	}
}

static Dz1JsonSpecChild I2XTrafficSafetyDeviceList_membs[] =
{
	{ Dz1Text("cnt"), Dz1Text("u16_t"), 0 },
	{ Dz1Text("id"), Dz1Text("I2XTrafficSafetyDeviceSerialNoList"), 1 },
	{ NULL, NULL, -1 }
};
// I2XTrafficSafetyDeviceList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2Data
static bool_t ITSK00144_2Data_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ITSK00144_2Data *p = (ITSK00144_2Data *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case ITSK00144_2DataPresent_req_link_unit_status: ITSK00144_2Reserved0_delAndSetNull(&p->x.req_link_unit_status); p->x.req_link_unit_status =(ITSK00144_2Reserved0 *)info->data; info->data = NULL; break;
	case ITSK00144_2DataPresent_rsp_link_unit_status: I2XTrafficSafetyDeviceLinkUnitStatus_delAndSetNull(&p->x.rsp_link_unit_status); p->x.rsp_link_unit_status =(I2XTrafficSafetyDeviceLinkUnitStatus *)info->data; info->data = NULL; break;
	case ITSK00144_2DataPresent_req_status: ITSK00144_2Reserved0_delAndSetNull(&p->x.req_status); p->x.req_status =(ITSK00144_2Reserved0 *)info->data; info->data = NULL; break;
	case ITSK00144_2DataPresent_rsp_status: I2XTrafficSafetyDeviceStatusInfo_delAndSetNull(&p->x.rsp_status); p->x.rsp_status =(I2XTrafficSafetyDeviceStatusInfo *)info->data; info->data = NULL; break;
	case ITSK00144_2DataPresent_req_list: ITSK00144_2Reserved0_delAndSetNull(&p->x.req_list); p->x.req_list =(ITSK00144_2Reserved0 *)info->data; info->data = NULL; break;
	case ITSK00144_2DataPresent_rsp_list: I2XTrafficSafetyDeviceList_delAndSetNull(&p->x.rsp_list); p->x.rsp_list =(I2XTrafficSafetyDeviceList *)info->data; info->data = NULL; break;
	case ITSK00144_2DataPresent_req_update_list: I2XTrafficSafetyDeviceList_delAndSetNull(&p->x.req_update_list); p->x.req_update_list =(I2XTrafficSafetyDeviceList *)info->data; info->data = NULL; break;
	case ITSK00144_2DataPresent_rsp_update_list: I2XTrafficSafetyDeviceList_delAndSetNull(&p->x.rsp_update_list); p->x.rsp_update_list =(I2XTrafficSafetyDeviceList *)info->data; info->data = NULL; break;
	case ITSK00144_2DataPresent_reset: ITSK00144_2Reserved0_delAndSetNull(&p->x.reset); p->x.reset =(ITSK00144_2Reserved0 *)info->data; info->data = NULL; break;
	case ITSK00144_2DataPresent_hb: ITSK00144_2Reserved0_delAndSetNull(&p->x.hb); p->x.hb =(ITSK00144_2Reserved0 *)info->data; info->data = NULL; break;
	case ITSK00144_2DataPresent_ack: ITSK00144_2Reserved0_delAndSetNull(&p->x.ack); p->x.ack =(ITSK00144_2Reserved0 *)info->data; info->data = NULL; break;
	case ITSK00144_2DataPresent_nack: ITSK00144_2Reserved0_delAndSetNull(&p->x.nack); p->x.nack =(ITSK00144_2Reserved0 *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (ITSK00144_2DataPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ITSK00144_2Data_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ITSK00144_2Data *p = (ITSK00144_2Data *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case ITSK00144_2DataPresent_req_link_unit_status: return p->x.req_link_unit_status;
		case ITSK00144_2DataPresent_rsp_link_unit_status: return p->x.rsp_link_unit_status;
		case ITSK00144_2DataPresent_req_status: return p->x.req_status;
		case ITSK00144_2DataPresent_rsp_status: return p->x.rsp_status;
		case ITSK00144_2DataPresent_req_list: return p->x.req_list;
		case ITSK00144_2DataPresent_rsp_list: return p->x.rsp_list;
		case ITSK00144_2DataPresent_req_update_list: return p->x.req_update_list;
		case ITSK00144_2DataPresent_rsp_update_list: return p->x.rsp_update_list;
		case ITSK00144_2DataPresent_reset: return p->x.reset;
		case ITSK00144_2DataPresent_hb: return p->x.hb;
		case ITSK00144_2DataPresent_ack: return p->x.ack;
		case ITSK00144_2DataPresent_nack: return p->x.nack;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild ITSK00144_2Data_membs[] =
{
	{ Dz1Text("req_link_unit_status"), Dz1Text("ITSK00144_2Reserved0"), ITSK00144_2DataPresent_req_link_unit_status },
	{ Dz1Text("rsp_link_unit_status"), Dz1Text("I2XTrafficSafetyDeviceLinkUnitStatus"), ITSK00144_2DataPresent_rsp_link_unit_status },
	{ Dz1Text("req_status"), Dz1Text("ITSK00144_2Reserved0"), ITSK00144_2DataPresent_req_status },
	{ Dz1Text("rsp_status"), Dz1Text("I2XTrafficSafetyDeviceStatusInfo"), ITSK00144_2DataPresent_rsp_status },
	{ Dz1Text("req_list"), Dz1Text("ITSK00144_2Reserved0"), ITSK00144_2DataPresent_req_list },
	{ Dz1Text("rsp_list"), Dz1Text("I2XTrafficSafetyDeviceList"), ITSK00144_2DataPresent_rsp_list },
	{ Dz1Text("req_update_list"), Dz1Text("I2XTrafficSafetyDeviceList"), ITSK00144_2DataPresent_req_update_list },
	{ Dz1Text("rsp_update_list"), Dz1Text("I2XTrafficSafetyDeviceList"), ITSK00144_2DataPresent_rsp_update_list },
	{ Dz1Text("reset"), Dz1Text("ITSK00144_2Reserved0"), ITSK00144_2DataPresent_reset },
	{ Dz1Text("hb"), Dz1Text("ITSK00144_2Reserved0"), ITSK00144_2DataPresent_hb },
	{ Dz1Text("ack"), Dz1Text("ITSK00144_2Reserved0"), ITSK00144_2DataPresent_ack },
	{ Dz1Text("nack"), Dz1Text("ITSK00144_2Reserved0"), ITSK00144_2DataPresent_nack },
	{ NULL, NULL, -1 }
};
// ITSK00144_2Data
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ITSK00144_2ProtocolFrameContext
static bool_t ITSK00144_2ProtocolFrameContext_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ITSK00144_2ProtocolFrameContext *p = (ITSK00144_2ProtocolFrameContext *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: I2XTrafficSafetyDeviceSerialNo_delAndSetNull(&p->id); p->id = (I2XTrafficSafetyDeviceSerialNo *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: p->seq =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->opcode =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: ITSK00144_2Data_delAndSetNull(&p->data); p->data = (ITSK00144_2Data *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ITSK00144_2ProtocolFrameContext_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ITSK00144_2ProtocolFrameContext *p = (ITSK00144_2ProtocolFrameContext *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->id;
	case 1: return &p->seq;
	case 2: return &p->opcode;
	case 3: return p->data;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ITSK00144_2ProtocolFrameContext_membs[] =
{
	{ Dz1Text("id"), Dz1Text("I2XTrafficSafetyDeviceSerialNo"), 0 },
	{ Dz1Text("seq"), Dz1Text("u8_t"), 1 },
	{ Dz1Text("opcode"), Dz1Text("u8_t"), 2 },
	{ Dz1Text("data"), Dz1Text("ITSK00144_2Data"), 3 },
	{ NULL, NULL, -1 }
};
// ITSK00144_2ProtocolFrameContext
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
// Dz1JsonSpec Initializer
bool_t ITSK00144_2TestScenarioDef_initJsonSpec(Dz1JsonSpec *dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (0) { }
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("ITSK00144_2ProcessStatusCode"), ITSK00144_2ProcessStatusCode_gen, ITSK00144_2ProcessStatusCode_del, ITSK00144_2ProcessStatusCode_load, ITSK00144_2ProcessStatusCode_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_LayerType"), Gitsn_LayerType_gen, Gitsn_LayerType_del, Gitsn_LayerType_load, Gitsn_LayerType_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_SpeedLimitType"), Gitsn_SpeedLimitType_gen, Gitsn_SpeedLimitType_del, Gitsn_SpeedLimitType_load, Gitsn_SpeedLimitType_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_NodeAttributeXY"), Gitsn_NodeAttributeXY_gen, Gitsn_NodeAttributeXY_del, Gitsn_NodeAttributeXY_load, Gitsn_NodeAttributeXY_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_SegmentAttributeXY"), Gitsn_SegmentAttributeXY_gen, Gitsn_SegmentAttributeXY_del, Gitsn_SegmentAttributeXY_load, Gitsn_SegmentAttributeXY_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_RestrictionAppliesTo"), Gitsn_RestrictionAppliesTo_gen, Gitsn_RestrictionAppliesTo_del, Gitsn_RestrictionAppliesTo_load, Gitsn_RestrictionAppliesTo_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_TravelerInfoType"), Gitsn_TravelerInfoType_gen, Gitsn_TravelerInfoType_del, Gitsn_TravelerInfoType_load, Gitsn_TravelerInfoType_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_MUTCDCode"), Gitsn_MUTCDCode_gen, Gitsn_MUTCDCode_del, Gitsn_MUTCDCode_load, Gitsn_MUTCDCode_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_DirectionOfUse"), Gitsn_DirectionOfUse_gen, Gitsn_DirectionOfUse_del, Gitsn_DirectionOfUse_load, Gitsn_DirectionOfUse_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_NodeAttributeLL"), Gitsn_NodeAttributeLL_gen, Gitsn_NodeAttributeLL_del, Gitsn_NodeAttributeLL_load, Gitsn_NodeAttributeLL_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_SegmentAttributeLL"), Gitsn_SegmentAttributeLL_gen, Gitsn_SegmentAttributeLL_del, Gitsn_SegmentAttributeLL_load, Gitsn_SegmentAttributeLL_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_Extent"), Gitsn_Extent_gen, Gitsn_Extent_del, Gitsn_Extent_load, Gitsn_Extent_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_DistanceUnits"), Gitsn_DistanceUnits_gen, Gitsn_DistanceUnits_del, Gitsn_DistanceUnits_load, Gitsn_DistanceUnits_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ITSK00144_2ProtocolFrame"), ITSK00144_2ProtocolFrame_gen, ITSK00144_2ProtocolFrame_del, ITSK00144_2ProtocolFrame_setChild, ITSK00144_2ProtocolFrame_getChild, ITSK00144_2ProtocolFrame_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ITSK00144_2NotifyStateContext"), ITSK00144_2NotifyStateContext_gen, ITSK00144_2NotifyStateContext_del, ITSK00144_2NotifyStateContext_setChild, ITSK00144_2NotifyStateContext_getChild, ITSK00144_2NotifyStateContext_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ITSK00144_2NotifyInfoContext"), ITSK00144_2NotifyInfoContext_gen, ITSK00144_2NotifyInfoContext_del, ITSK00144_2NotifyInfoContext_setChild, ITSK00144_2NotifyInfoContext_getChild, ITSK00144_2NotifyInfoContext_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ITSK00144_2NotifyErrorContext"), ITSK00144_2NotifyErrorContext_gen, ITSK00144_2NotifyErrorContext_del, ITSK00144_2NotifyErrorContext_setChild, ITSK00144_2NotifyErrorContext_getChild, ITSK00144_2NotifyErrorContext_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ITSK00144_2NotifyContext"), ITSK00144_2NotifyContext_gen, ITSK00144_2NotifyContext_del, ITSK00144_2NotifyContext_setChild, ITSK00144_2NotifyContext_getChild, ITSK00144_2NotifyContext_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ITSK00144_2ValidateContext"), ITSK00144_2ValidateContext_gen, ITSK00144_2ValidateContext_del, ITSK00144_2ValidateContext_setChild, ITSK00144_2ValidateContext_getChild, ITSK00144_2ValidateContext_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ITSK00144_2TestConfiguration_ServerRole"), ITSK00144_2TestConfiguration_ServerRole_gen, ITSK00144_2TestConfiguration_ServerRole_del, ITSK00144_2TestConfiguration_ServerRole_setChild, ITSK00144_2TestConfiguration_ServerRole_getChild, ITSK00144_2TestConfiguration_ServerRole_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ITSK00144_2TestConfiguration_LinkUnitRole"), ITSK00144_2TestConfiguration_LinkUnitRole_gen, ITSK00144_2TestConfiguration_LinkUnitRole_del, ITSK00144_2TestConfiguration_LinkUnitRole_setChild, ITSK00144_2TestConfiguration_LinkUnitRole_getChild, ITSK00144_2TestConfiguration_LinkUnitRole_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ITSK00144_2TestConfiguration"), ITSK00144_2TestConfiguration_gen, ITSK00144_2TestConfiguration_del, ITSK00144_2TestConfiguration_setChild, ITSK00144_2TestConfiguration_getChild, ITSK00144_2TestConfiguration_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("I2XTrafficSafetyDeviceSerialNo"), I2XTrafficSafetyDeviceSerialNo_gen, I2XTrafficSafetyDeviceSerialNo_del, I2XTrafficSafetyDeviceSerialNo_setChild, I2XTrafficSafetyDeviceSerialNo_getChild, I2XTrafficSafetyDeviceSerialNo_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ITSK00144_2Reserved0"), ITSK00144_2Reserved0_gen, ITSK00144_2Reserved0_del, ITSK00144_2Reserved0_setChild, ITSK00144_2Reserved0_getChild, ITSK00144_2Reserved0_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("I2XTrafficSafetyDeviceLinkUnitStatus"), I2XTrafficSafetyDeviceLinkUnitStatus_gen, I2XTrafficSafetyDeviceLinkUnitStatus_del, I2XTrafficSafetyDeviceLinkUnitStatus_setChild, I2XTrafficSafetyDeviceLinkUnitStatus_getChild, I2XTrafficSafetyDeviceLinkUnitStatus_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("I2XTrafficSafetyDeviceStatus"), I2XTrafficSafetyDeviceStatus_gen, I2XTrafficSafetyDeviceStatus_del, I2XTrafficSafetyDeviceStatus_setChild, I2XTrafficSafetyDeviceStatus_getChild, I2XTrafficSafetyDeviceStatus_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("I2XTrafficSafetyDeviceStatusInfo"), I2XTrafficSafetyDeviceStatusInfo_gen, I2XTrafficSafetyDeviceStatusInfo_del, I2XTrafficSafetyDeviceStatusInfo_setChild, I2XTrafficSafetyDeviceStatusInfo_getChild, I2XTrafficSafetyDeviceStatusInfo_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("I2XTrafficSafetyDeviceList"), I2XTrafficSafetyDeviceList_gen, I2XTrafficSafetyDeviceList_del, I2XTrafficSafetyDeviceList_setChild, I2XTrafficSafetyDeviceList_getChild, I2XTrafficSafetyDeviceList_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ITSK00144_2Data"), ITSK00144_2Data_gen, ITSK00144_2Data_del, ITSK00144_2Data_setChild, ITSK00144_2Data_getChild, ITSK00144_2Data_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ITSK00144_2ProtocolFrameContext"), ITSK00144_2ProtocolFrameContext_gen, ITSK00144_2ProtocolFrameContext_del, ITSK00144_2ProtocolFrameContext_setChild, ITSK00144_2ProtocolFrameContext_getChild, ITSK00144_2ProtocolFrameContext_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
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
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("I2XTrafficSafetyDeviceStatusList"), I2XTrafficSafetyDeviceStatusList_gen, I2XTrafficSafetyDeviceStatusList_del, I2XTrafficSafetyDeviceStatusList_append, I2XTrafficSafetyDeviceStatusList_cnt, I2XTrafficSafetyDeviceStatusList_tlv, Dz1Text("I2XTrafficSafetyDeviceStatus") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("I2XTrafficSafetyDeviceSerialNoList"), I2XTrafficSafetyDeviceSerialNoList_gen, I2XTrafficSafetyDeviceSerialNoList_del, I2XTrafficSafetyDeviceSerialNoList_append, I2XTrafficSafetyDeviceSerialNoList_cnt, I2XTrafficSafetyDeviceSerialNoList_tlv, Dz1Text("I2XTrafficSafetyDeviceSerialNo") )).code) ERR_OUT(errp);
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
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
Dz1JsonSpec *ITSK00144_2TestScenarioDef_genJsonSpec(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonSpec *ret = Dz1JsonSpec_generate(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonSpec_delAndSetNull, (void *)&ret);

		if (ITSK00144_2TestScenarioDef_initJsonSpec(ret, errp) == FALSE) ERR_OUT(errp);
		else if (Dz1JsonSpec_check(ret, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1JsonSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Dz1JsonSpec Initializer
////////////////////////////////////////////////////////////////////////////////

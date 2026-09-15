#include "ScenarioEngineWebSockMsgDefJson.h"

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineInitializeContext
static bool_t ScenarioEngineInitializeContext_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ScenarioEngineInitializeContext *p = (ScenarioEngineInitializeContext *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->category); p->category = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->testScenario); p->testScenario = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ScenarioEngineInitializeContext_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ScenarioEngineInitializeContext *p = (ScenarioEngineInitializeContext *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->category;
	case 1: return p->testScenario;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ScenarioEngineInitializeContext_membs[] =
{
	{ Dz1Text("category"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("testScenario"), Dz1Text("Dz1Str"), 1 },
	{ NULL, NULL, -1 }
};
// ScenarioEngineInitializeContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineWebSocketStatusCode
static bool_t ScenarioEngineWebSocketStatusCode_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ScenarioEngineWebSocketStatusCode v = ScenarioEngineWebSocketStatusCode_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (ScenarioEngineWebSocketStatusCode)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = ScenarioEngineWebSocketStatusCodeFromStr(tok->v)) == ScenarioEngineWebSocketStatusCode_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = ScenarioEngineWebSocketStatusCode_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t ScenarioEngineWebSocketStatusCode_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		ScenarioEngineWebSocketStatusCode v = *(ScenarioEngineWebSocketStatusCode *)obj;
		Dz1Str str_v = ScenarioEngineWebSocketStatusCodeStr(v);
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
// ScenarioEngineWebSocketStatusCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineWebSocketResponseMessageContext
static bool_t ScenarioEngineWebSocketResponseMessageContext_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ScenarioEngineWebSocketResponseMessageContext *p = (ScenarioEngineWebSocketResponseMessageContext *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->code =  *(ScenarioEngineWebSocketStatusCode *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: Dz1Str_delAndSetNull(&p->reason); p->reason = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->data); p->data = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ScenarioEngineWebSocketResponseMessageContext_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ScenarioEngineWebSocketResponseMessageContext *p = (ScenarioEngineWebSocketResponseMessageContext *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->code;
	case 1: return p->reason;
	case 2: return p->data;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ScenarioEngineWebSocketResponseMessageContext_membs[] =
{
	{ Dz1Text("code"), Dz1Text("ScenarioEngineWebSocketStatusCode"), 0 },
	{ Dz1Text("reason"), Dz1Text("Dz1Str"), 1 },
	{ Dz1Text("data"), Dz1Text("Dz1Str"), 2 },
	{ NULL, NULL, -1 }
};
// ScenarioEngineWebSocketResponseMessageContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineResponseMessageDefault
static bool_t ScenarioEngineResponseMessageDefault_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ScenarioEngineResponseMessageDefault *p = (ScenarioEngineResponseMessageDefault *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->seq =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: ScenarioEngineWebSocketResponseMessageContext_delAndSetNull(&p->result); p->result = (ScenarioEngineWebSocketResponseMessageContext *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ScenarioEngineResponseMessageDefault_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ScenarioEngineResponseMessageDefault *p = (ScenarioEngineResponseMessageDefault *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->seq;
	case 1: return p->result;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ScenarioEngineResponseMessageDefault_membs[] =
{
	{ Dz1Text("seq"), Dz1Text("u32_t"), 0 },
	{ Dz1Text("result"), Dz1Text("ScenarioEngineWebSocketResponseMessageContext"), 1 },
	{ NULL, NULL, -1 }
};
// ScenarioEngineResponseMessageDefault
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Binary
// extern type
// Dz1Binary
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineProcessStatusCode
static bool_t ScenarioEngineProcessStatusCode_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ScenarioEngineProcessStatusCode v = ScenarioEngineProcessStatusCode_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (ScenarioEngineProcessStatusCode)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = ScenarioEngineProcessStatusCodeFromStr(tok->v)) == ScenarioEngineProcessStatusCode_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = ScenarioEngineProcessStatusCode_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t ScenarioEngineProcessStatusCode_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		ScenarioEngineProcessStatusCode v = *(ScenarioEngineProcessStatusCode *)obj;
		Dz1Str str_v = ScenarioEngineProcessStatusCodeStr(v);
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
// ScenarioEngineProcessStatusCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineValidateContext
static bool_t ScenarioEngineValidateContext_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ScenarioEngineValidateContext *p = (ScenarioEngineValidateContext *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->testName); p->testName = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->time =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: Dz1Binary_delAndSetNull(&p->raw); p->raw = (Dz1Binary *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: Dz1Binary_delAndSetNull(&p->data); p->data = (Dz1Binary *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 4: p->code =  *(ScenarioEngineProcessStatusCode *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: Dz1Str_delAndSetNull(&p->desc); p->desc = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ScenarioEngineValidateContext_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ScenarioEngineValidateContext *p = (ScenarioEngineValidateContext *)ptr;
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

static Dz1JsonSpecChild ScenarioEngineValidateContext_membs[] =
{
	{ Dz1Text("testName"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("time"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("raw"), Dz1Text("Dz1Binary"), 2 },
	{ Dz1Text("data"), Dz1Text("Dz1Binary"), 3 },
	{ Dz1Text("code"), Dz1Text("ScenarioEngineProcessStatusCode"), 4 },
	{ Dz1Text("desc"), Dz1Text("Dz1Str"), 5 },
	{ NULL, NULL, -1 }
};
// ScenarioEngineValidateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineResponseMessageValidate
static bool_t ScenarioEngineResponseMessageValidate_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ScenarioEngineResponseMessageValidate *p = (ScenarioEngineResponseMessageValidate *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->seq =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->testIdx =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->result); p->result = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 3: ScenarioEngineValidateContext_delAndSetNull(&p->validate); p->validate = (ScenarioEngineValidateContext *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ScenarioEngineResponseMessageValidate_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ScenarioEngineResponseMessageValidate *p = (ScenarioEngineResponseMessageValidate *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->seq;
	case 1: return &p->testIdx;
	case 2: return p->result;
	case 3: return p->validate;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ScenarioEngineResponseMessageValidate_membs[] =
{
	{ Dz1Text("seq"), Dz1Text("u32_t"), 0 },
	{ Dz1Text("testIdx"), Dz1Text("u32_t"), 1 },
	{ Dz1Text("result"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("validate"), Dz1Text("ScenarioEngineValidateContext"), 3 },
	{ NULL, NULL, -1 }
};
// ScenarioEngineResponseMessageValidate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineWebSocketMessageResponse
static bool_t ScenarioEngineWebSocketMessageResponse_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ScenarioEngineWebSocketMessageResponse *p = (ScenarioEngineWebSocketMessageResponse *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case ScenarioEngineWebSocketMessageResponsePresent_response: ScenarioEngineResponseMessageDefault_delAndSetNull(&p->x.response); p->x.response =(ScenarioEngineResponseMessageDefault *)info->data; info->data = NULL; break;
	case ScenarioEngineWebSocketMessageResponsePresent_validate: ScenarioEngineResponseMessageValidate_delAndSetNull(&p->x.validate); p->x.validate =(ScenarioEngineResponseMessageValidate *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (ScenarioEngineWebSocketMessageResponsePresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ScenarioEngineWebSocketMessageResponse_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ScenarioEngineWebSocketMessageResponse *p = (ScenarioEngineWebSocketMessageResponse *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case ScenarioEngineWebSocketMessageResponsePresent_response: return p->x.response;
		case ScenarioEngineWebSocketMessageResponsePresent_validate: return p->x.validate;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild ScenarioEngineWebSocketMessageResponse_membs[] =
{
	{ Dz1Text("response"), Dz1Text("ScenarioEngineResponseMessageDefault"), ScenarioEngineWebSocketMessageResponsePresent_response },
	{ Dz1Text("validate"), Dz1Text("ScenarioEngineResponseMessageValidate"), ScenarioEngineWebSocketMessageResponsePresent_validate },
	{ NULL, NULL, -1 }
};
// ScenarioEngineWebSocketMessageResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageDefault
static bool_t ScenarioEngineRequestMessageDefault_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ScenarioEngineRequestMessageDefault *p = (ScenarioEngineRequestMessageDefault *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->method); p->method = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->seq =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ScenarioEngineRequestMessageDefault_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ScenarioEngineRequestMessageDefault *p = (ScenarioEngineRequestMessageDefault *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->method;
	case 1: return &p->seq;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ScenarioEngineRequestMessageDefault_membs[] =
{
	{ Dz1Text("method"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("seq"), Dz1Text("u32_t"), 1 },
	{ NULL, NULL, -1 }
};
// ScenarioEngineRequestMessageDefault
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageDescribe
static bool_t ScenarioEngineRequestMessageDescribe_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ScenarioEngineRequestMessageDescribe *p = (ScenarioEngineRequestMessageDescribe *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->method); p->method = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->seq =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->type); p->type = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ScenarioEngineRequestMessageDescribe_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ScenarioEngineRequestMessageDescribe *p = (ScenarioEngineRequestMessageDescribe *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->method;
	case 1: return &p->seq;
	case 2: return p->type;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ScenarioEngineRequestMessageDescribe_membs[] =
{
	{ Dz1Text("method"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("seq"), Dz1Text("u32_t"), 1 },
	{ Dz1Text("type"), Dz1Text("Dz1Str"), 2 },
	{ NULL, NULL, -1 }
};
// ScenarioEngineRequestMessageDescribe
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageInitialize
static bool_t ScenarioEngineRequestMessageInitialize_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ScenarioEngineRequestMessageInitialize *p = (ScenarioEngineRequestMessageInitialize *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->method); p->method = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->seq =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: Dz1Binary_delAndSetNull(&p->testScenario); p->testScenario = (Dz1Binary *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ScenarioEngineRequestMessageInitialize_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ScenarioEngineRequestMessageInitialize *p = (ScenarioEngineRequestMessageInitialize *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->method;
	case 1: return &p->seq;
	case 2: return p->testScenario;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ScenarioEngineRequestMessageInitialize_membs[] =
{
	{ Dz1Text("method"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("seq"), Dz1Text("u32_t"), 1 },
	{ Dz1Text("testScenario"), Dz1Text("Dz1Binary"), 2 },
	{ NULL, NULL, -1 }
};
// ScenarioEngineRequestMessageInitialize
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageUIConfigure
static bool_t ScenarioEngineRequestMessageUIConfigure_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ScenarioEngineRequestMessageUIConfigure *p = (ScenarioEngineRequestMessageUIConfigure *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->method); p->method = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->seq =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: Dz1Binary_delAndSetNull(&p->conf); p->conf = (Dz1Binary *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ScenarioEngineRequestMessageUIConfigure_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ScenarioEngineRequestMessageUIConfigure *p = (ScenarioEngineRequestMessageUIConfigure *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->method;
	case 1: return &p->seq;
	case 2: return p->conf;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ScenarioEngineRequestMessageUIConfigure_membs[] =
{
	{ Dz1Text("method"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("seq"), Dz1Text("u32_t"), 1 },
	{ Dz1Text("conf"), Dz1Text("Dz1Binary"), 2 },
	{ NULL, NULL, -1 }
};
// ScenarioEngineRequestMessageUIConfigure
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageWithData
static bool_t ScenarioEngineRequestMessageWithData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ScenarioEngineRequestMessageWithData *p = (ScenarioEngineRequestMessageWithData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->method); p->method = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->seq =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->data); p->data = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ScenarioEngineRequestMessageWithData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ScenarioEngineRequestMessageWithData *p = (ScenarioEngineRequestMessageWithData *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->method;
	case 1: return &p->seq;
	case 2: return p->data;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ScenarioEngineRequestMessageWithData_membs[] =
{
	{ Dz1Text("method"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("seq"), Dz1Text("u32_t"), 1 },
	{ Dz1Text("data"), Dz1Text("Dz1Str"), 2 },
	{ NULL, NULL, -1 }
};
// ScenarioEngineRequestMessageWithData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageSetup
static bool_t ScenarioEngineRequestMessageSetup_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ScenarioEngineRequestMessageSetup *p = (ScenarioEngineRequestMessageSetup *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->method); p->method = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->seq =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->testConfiguration); p->testConfiguration = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ScenarioEngineRequestMessageSetup_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ScenarioEngineRequestMessageSetup *p = (ScenarioEngineRequestMessageSetup *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->method;
	case 1: return &p->seq;
	case 2: return p->testConfiguration;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ScenarioEngineRequestMessageSetup_membs[] =
{
	{ Dz1Text("method"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("seq"), Dz1Text("u32_t"), 1 },
	{ Dz1Text("testConfiguration"), Dz1Text("Dz1Str"), 2 },
	{ NULL, NULL, -1 }
};
// ScenarioEngineRequestMessageSetup
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineNotifyStateContext
static bool_t ScenarioEngineNotifyStateContext_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ScenarioEngineNotifyStateContext *p = (ScenarioEngineNotifyStateContext *)ptr;

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

static void *ScenarioEngineNotifyStateContext_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ScenarioEngineNotifyStateContext *p = (ScenarioEngineNotifyStateContext *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->testName;
	case 1: return &p->time;
	case 2: return p->state;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ScenarioEngineNotifyStateContext_membs[] =
{
	{ Dz1Text("testName"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("time"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("state"), Dz1Text("Dz1Str"), 2 },
	{ NULL, NULL, -1 }
};
// ScenarioEngineNotifyStateContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageNotifyState
static bool_t ScenarioEngineRequestMessageNotifyState_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ScenarioEngineRequestMessageNotifyState *p = (ScenarioEngineRequestMessageNotifyState *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->method); p->method = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->seq =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->testIdx =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: Dz1Str_delAndSetNull(&p->level); p->level = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 4: ScenarioEngineNotifyStateContext_delAndSetNull(&p->data); p->data = (ScenarioEngineNotifyStateContext *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ScenarioEngineRequestMessageNotifyState_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ScenarioEngineRequestMessageNotifyState *p = (ScenarioEngineRequestMessageNotifyState *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->method;
	case 1: return &p->seq;
	case 2: return &p->testIdx;
	case 3: return p->level;
	case 4: return p->data;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ScenarioEngineRequestMessageNotifyState_membs[] =
{
	{ Dz1Text("method"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("seq"), Dz1Text("u32_t"), 1 },
	{ Dz1Text("testIdx"), Dz1Text("u32_t"), 2 },
	{ Dz1Text("level"), Dz1Text("Dz1Str"), 3 },
	{ Dz1Text("data"), Dz1Text("ScenarioEngineNotifyStateContext"), 4 },
	{ NULL, NULL, -1 }
};
// ScenarioEngineRequestMessageNotifyState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineNotifyInfoContext
static bool_t ScenarioEngineNotifyInfoContext_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ScenarioEngineNotifyInfoContext *p = (ScenarioEngineNotifyInfoContext *)ptr;

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

static void *ScenarioEngineNotifyInfoContext_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ScenarioEngineNotifyInfoContext *p = (ScenarioEngineNotifyInfoContext *)ptr;
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

static Dz1JsonSpecChild ScenarioEngineNotifyInfoContext_membs[] =
{
	{ Dz1Text("testName"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("time"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("sender"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("log"), Dz1Text("Dz1Str"), 3 },
	{ Dz1Text("data"), Dz1Text("Dz1Binary"), 4 },
	{ Dz1Text("dataType"), Dz1Text("Dz1Str"), 5 },
	{ NULL, NULL, -1 }
};
// ScenarioEngineNotifyInfoContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageNotifyInfo
static bool_t ScenarioEngineRequestMessageNotifyInfo_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ScenarioEngineRequestMessageNotifyInfo *p = (ScenarioEngineRequestMessageNotifyInfo *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->method); p->method = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->seq =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->testIdx =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: Dz1Str_delAndSetNull(&p->level); p->level = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 4: ScenarioEngineNotifyInfoContext_delAndSetNull(&p->data); p->data = (ScenarioEngineNotifyInfoContext *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ScenarioEngineRequestMessageNotifyInfo_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ScenarioEngineRequestMessageNotifyInfo *p = (ScenarioEngineRequestMessageNotifyInfo *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->method;
	case 1: return &p->seq;
	case 2: return &p->testIdx;
	case 3: return p->level;
	case 4: return p->data;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ScenarioEngineRequestMessageNotifyInfo_membs[] =
{
	{ Dz1Text("method"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("seq"), Dz1Text("u32_t"), 1 },
	{ Dz1Text("testIdx"), Dz1Text("u32_t"), 2 },
	{ Dz1Text("level"), Dz1Text("Dz1Str"), 3 },
	{ Dz1Text("data"), Dz1Text("ScenarioEngineNotifyInfoContext"), 4 },
	{ NULL, NULL, -1 }
};
// ScenarioEngineRequestMessageNotifyInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineNotifyErrorContext
static bool_t ScenarioEngineNotifyErrorContext_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ScenarioEngineNotifyErrorContext *p = (ScenarioEngineNotifyErrorContext *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->testName); p->testName = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->time =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->code =  *(ScenarioEngineProcessStatusCode *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: Dz1Str_delAndSetNull(&p->desc); p->desc = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 4: Dz1Str_delAndSetNull(&p->log); p->log = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 5: Dz1Binary_delAndSetNull(&p->data); p->data = (Dz1Binary *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ScenarioEngineNotifyErrorContext_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ScenarioEngineNotifyErrorContext *p = (ScenarioEngineNotifyErrorContext *)ptr;
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

static Dz1JsonSpecChild ScenarioEngineNotifyErrorContext_membs[] =
{
	{ Dz1Text("testName"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("time"), Dz1Text("s64_t"), 1 },
	{ Dz1Text("code"), Dz1Text("ScenarioEngineProcessStatusCode"), 2 },
	{ Dz1Text("desc"), Dz1Text("Dz1Str"), 3 },
	{ Dz1Text("log"), Dz1Text("Dz1Str"), 4 },
	{ Dz1Text("data"), Dz1Text("Dz1Binary"), 5 },
	{ NULL, NULL, -1 }
};
// ScenarioEngineNotifyErrorContext
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageNotifyError
static bool_t ScenarioEngineRequestMessageNotifyError_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ScenarioEngineRequestMessageNotifyError *p = (ScenarioEngineRequestMessageNotifyError *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->method); p->method = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->seq =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->testIdx =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: Dz1Str_delAndSetNull(&p->level); p->level = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 4: ScenarioEngineNotifyErrorContext_delAndSetNull(&p->data); p->data = (ScenarioEngineNotifyErrorContext *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ScenarioEngineRequestMessageNotifyError_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ScenarioEngineRequestMessageNotifyError *p = (ScenarioEngineRequestMessageNotifyError *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->method;
	case 1: return &p->seq;
	case 2: return &p->testIdx;
	case 3: return p->level;
	case 4: return p->data;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ScenarioEngineRequestMessageNotifyError_membs[] =
{
	{ Dz1Text("method"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("seq"), Dz1Text("u32_t"), 1 },
	{ Dz1Text("testIdx"), Dz1Text("u32_t"), 2 },
	{ Dz1Text("level"), Dz1Text("Dz1Str"), 3 },
	{ Dz1Text("data"), Dz1Text("ScenarioEngineNotifyErrorContext"), 4 },
	{ NULL, NULL, -1 }
};
// ScenarioEngineRequestMessageNotifyError
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageNotify
static bool_t ScenarioEngineRequestMessageNotify_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ScenarioEngineRequestMessageNotify *p = (ScenarioEngineRequestMessageNotify *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case ScenarioEngineRequestMessageNotifyPresent_state: ScenarioEngineRequestMessageNotifyState_delAndSetNull(&p->x.state); p->x.state =(ScenarioEngineRequestMessageNotifyState *)info->data; info->data = NULL; break;
	case ScenarioEngineRequestMessageNotifyPresent_info: ScenarioEngineRequestMessageNotifyInfo_delAndSetNull(&p->x.info); p->x.info =(ScenarioEngineRequestMessageNotifyInfo *)info->data; info->data = NULL; break;
	case ScenarioEngineRequestMessageNotifyPresent_error: ScenarioEngineRequestMessageNotifyError_delAndSetNull(&p->x.error); p->x.error =(ScenarioEngineRequestMessageNotifyError *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (ScenarioEngineRequestMessageNotifyPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ScenarioEngineRequestMessageNotify_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ScenarioEngineRequestMessageNotify *p = (ScenarioEngineRequestMessageNotify *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case ScenarioEngineRequestMessageNotifyPresent_state: return p->x.state;
		case ScenarioEngineRequestMessageNotifyPresent_info: return p->x.info;
		case ScenarioEngineRequestMessageNotifyPresent_error: return p->x.error;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild ScenarioEngineRequestMessageNotify_membs[] =
{
	{ Dz1Text("state"), Dz1Text("ScenarioEngineRequestMessageNotifyState"), ScenarioEngineRequestMessageNotifyPresent_state },
	{ Dz1Text("info"), Dz1Text("ScenarioEngineRequestMessageNotifyInfo"), ScenarioEngineRequestMessageNotifyPresent_info },
	{ Dz1Text("error"), Dz1Text("ScenarioEngineRequestMessageNotifyError"), ScenarioEngineRequestMessageNotifyPresent_error },
	{ NULL, NULL, -1 }
};
// ScenarioEngineRequestMessageNotify
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineRequestMessageValidate
static bool_t ScenarioEngineRequestMessageValidate_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ScenarioEngineRequestMessageValidate *p = (ScenarioEngineRequestMessageValidate *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: Dz1Str_delAndSetNull(&p->method); p->method = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 1: p->seq =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->testIdx =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: ScenarioEngineValidateContext_delAndSetNull(&p->validate); p->validate = (ScenarioEngineValidateContext *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ScenarioEngineRequestMessageValidate_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ScenarioEngineRequestMessageValidate *p = (ScenarioEngineRequestMessageValidate *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->method;
	case 1: return &p->seq;
	case 2: return &p->testIdx;
	case 3: return p->validate;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ScenarioEngineRequestMessageValidate_membs[] =
{
	{ Dz1Text("method"), Dz1Text("Dz1Str"), 0 },
	{ Dz1Text("seq"), Dz1Text("u32_t"), 1 },
	{ Dz1Text("testIdx"), Dz1Text("u32_t"), 2 },
	{ Dz1Text("validate"), Dz1Text("ScenarioEngineValidateContext"), 3 },
	{ NULL, NULL, -1 }
};
// ScenarioEngineRequestMessageValidate
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineWebSocketMessageRequest
static bool_t ScenarioEngineWebSocketMessageRequest_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ScenarioEngineWebSocketMessageRequest *p = (ScenarioEngineWebSocketMessageRequest *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case ScenarioEngineWebSocketMessageRequestPresent_request: ScenarioEngineRequestMessageDefault_delAndSetNull(&p->x.request); p->x.request =(ScenarioEngineRequestMessageDefault *)info->data; info->data = NULL; break;
	case ScenarioEngineWebSocketMessageRequestPresent_describe: ScenarioEngineRequestMessageDescribe_delAndSetNull(&p->x.describe); p->x.describe =(ScenarioEngineRequestMessageDescribe *)info->data; info->data = NULL; break;
	case ScenarioEngineWebSocketMessageRequestPresent_initialize: ScenarioEngineRequestMessageInitialize_delAndSetNull(&p->x.initialize); p->x.initialize =(ScenarioEngineRequestMessageInitialize *)info->data; info->data = NULL; break;
	case ScenarioEngineWebSocketMessageRequestPresent_uiConfigure: ScenarioEngineRequestMessageUIConfigure_delAndSetNull(&p->x.uiConfigure); p->x.uiConfigure =(ScenarioEngineRequestMessageUIConfigure *)info->data; info->data = NULL; break;
	case ScenarioEngineWebSocketMessageRequestPresent_withData: ScenarioEngineRequestMessageWithData_delAndSetNull(&p->x.withData); p->x.withData =(ScenarioEngineRequestMessageWithData *)info->data; info->data = NULL; break;
	case ScenarioEngineWebSocketMessageRequestPresent_setup: ScenarioEngineRequestMessageSetup_delAndSetNull(&p->x.setup); p->x.setup =(ScenarioEngineRequestMessageSetup *)info->data; info->data = NULL; break;
	case ScenarioEngineWebSocketMessageRequestPresent_notify: ScenarioEngineRequestMessageNotify_delAndSetNull(&p->x.notify); p->x.notify =(ScenarioEngineRequestMessageNotify *)info->data; info->data = NULL; break;
	case ScenarioEngineWebSocketMessageRequestPresent_validate: ScenarioEngineRequestMessageValidate_delAndSetNull(&p->x.validate); p->x.validate =(ScenarioEngineRequestMessageValidate *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (ScenarioEngineWebSocketMessageRequestPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ScenarioEngineWebSocketMessageRequest_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ScenarioEngineWebSocketMessageRequest *p = (ScenarioEngineWebSocketMessageRequest *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case ScenarioEngineWebSocketMessageRequestPresent_request: return p->x.request;
		case ScenarioEngineWebSocketMessageRequestPresent_describe: return p->x.describe;
		case ScenarioEngineWebSocketMessageRequestPresent_initialize: return p->x.initialize;
		case ScenarioEngineWebSocketMessageRequestPresent_uiConfigure: return p->x.uiConfigure;
		case ScenarioEngineWebSocketMessageRequestPresent_withData: return p->x.withData;
		case ScenarioEngineWebSocketMessageRequestPresent_setup: return p->x.setup;
		case ScenarioEngineWebSocketMessageRequestPresent_notify: return p->x.notify;
		case ScenarioEngineWebSocketMessageRequestPresent_validate: return p->x.validate;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild ScenarioEngineWebSocketMessageRequest_membs[] =
{
	{ Dz1Text("request"), Dz1Text("ScenarioEngineRequestMessageDefault"), ScenarioEngineWebSocketMessageRequestPresent_request },
	{ Dz1Text("describe"), Dz1Text("ScenarioEngineRequestMessageDescribe"), ScenarioEngineWebSocketMessageRequestPresent_describe },
	{ Dz1Text("initialize"), Dz1Text("ScenarioEngineRequestMessageInitialize"), ScenarioEngineWebSocketMessageRequestPresent_initialize },
	{ Dz1Text("uiConfigure"), Dz1Text("ScenarioEngineRequestMessageUIConfigure"), ScenarioEngineWebSocketMessageRequestPresent_uiConfigure },
	{ Dz1Text("withData"), Dz1Text("ScenarioEngineRequestMessageWithData"), ScenarioEngineWebSocketMessageRequestPresent_withData },
	{ Dz1Text("setup"), Dz1Text("ScenarioEngineRequestMessageSetup"), ScenarioEngineWebSocketMessageRequestPresent_setup },
	{ Dz1Text("notify"), Dz1Text("ScenarioEngineRequestMessageNotify"), ScenarioEngineWebSocketMessageRequestPresent_notify },
	{ Dz1Text("validate"), Dz1Text("ScenarioEngineRequestMessageValidate"), ScenarioEngineWebSocketMessageRequestPresent_validate },
	{ NULL, NULL, -1 }
};
// ScenarioEngineWebSocketMessageRequest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ScenarioEngineWebSocketMessage
static bool_t ScenarioEngineWebSocketMessage_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ScenarioEngineWebSocketMessage *p = (ScenarioEngineWebSocketMessage *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case ScenarioEngineWebSocketMessagePresent_rsp: ScenarioEngineWebSocketMessageResponse_delAndSetNull(&p->x.rsp); p->x.rsp =(ScenarioEngineWebSocketMessageResponse *)info->data; info->data = NULL; break;
	case ScenarioEngineWebSocketMessagePresent_req: ScenarioEngineWebSocketMessageRequest_delAndSetNull(&p->x.req); p->x.req =(ScenarioEngineWebSocketMessageRequest *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (ScenarioEngineWebSocketMessagePresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ScenarioEngineWebSocketMessage_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ScenarioEngineWebSocketMessage *p = (ScenarioEngineWebSocketMessage *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case ScenarioEngineWebSocketMessagePresent_rsp: return p->x.rsp;
		case ScenarioEngineWebSocketMessagePresent_req: return p->x.req;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild ScenarioEngineWebSocketMessage_membs[] =
{
	{ Dz1Text("rsp"), Dz1Text("ScenarioEngineWebSocketMessageResponse"), ScenarioEngineWebSocketMessagePresent_rsp },
	{ Dz1Text("req"), Dz1Text("ScenarioEngineWebSocketMessageRequest"), ScenarioEngineWebSocketMessagePresent_req },
	{ NULL, NULL, -1 }
};
// ScenarioEngineWebSocketMessage
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpec Initializer
bool_t ScenarioEngineWebSockMsgDef_initJsonSpec(Dz1JsonSpec *dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (0) { }
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("ScenarioEngineWebSocketStatusCode"), ScenarioEngineWebSocketStatusCode_gen, ScenarioEngineWebSocketStatusCode_del, ScenarioEngineWebSocketStatusCode_load, ScenarioEngineWebSocketStatusCode_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("ScenarioEngineProcessStatusCode"), ScenarioEngineProcessStatusCode_gen, ScenarioEngineProcessStatusCode_del, ScenarioEngineProcessStatusCode_load, ScenarioEngineProcessStatusCode_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ScenarioEngineInitializeContext"), ScenarioEngineInitializeContext_gen, ScenarioEngineInitializeContext_del, ScenarioEngineInitializeContext_setChild, ScenarioEngineInitializeContext_getChild, ScenarioEngineInitializeContext_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ScenarioEngineWebSocketResponseMessageContext"), ScenarioEngineWebSocketResponseMessageContext_gen, ScenarioEngineWebSocketResponseMessageContext_del, ScenarioEngineWebSocketResponseMessageContext_setChild, ScenarioEngineWebSocketResponseMessageContext_getChild, ScenarioEngineWebSocketResponseMessageContext_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ScenarioEngineResponseMessageDefault"), ScenarioEngineResponseMessageDefault_gen, ScenarioEngineResponseMessageDefault_del, ScenarioEngineResponseMessageDefault_setChild, ScenarioEngineResponseMessageDefault_getChild, ScenarioEngineResponseMessageDefault_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ScenarioEngineValidateContext"), ScenarioEngineValidateContext_gen, ScenarioEngineValidateContext_del, ScenarioEngineValidateContext_setChild, ScenarioEngineValidateContext_getChild, ScenarioEngineValidateContext_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ScenarioEngineResponseMessageValidate"), ScenarioEngineResponseMessageValidate_gen, ScenarioEngineResponseMessageValidate_del, ScenarioEngineResponseMessageValidate_setChild, ScenarioEngineResponseMessageValidate_getChild, ScenarioEngineResponseMessageValidate_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ScenarioEngineWebSocketMessageResponse"), ScenarioEngineWebSocketMessageResponse_gen, ScenarioEngineWebSocketMessageResponse_del, ScenarioEngineWebSocketMessageResponse_setChild, ScenarioEngineWebSocketMessageResponse_getChild, ScenarioEngineWebSocketMessageResponse_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ScenarioEngineRequestMessageDefault"), ScenarioEngineRequestMessageDefault_gen, ScenarioEngineRequestMessageDefault_del, ScenarioEngineRequestMessageDefault_setChild, ScenarioEngineRequestMessageDefault_getChild, ScenarioEngineRequestMessageDefault_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ScenarioEngineRequestMessageDescribe"), ScenarioEngineRequestMessageDescribe_gen, ScenarioEngineRequestMessageDescribe_del, ScenarioEngineRequestMessageDescribe_setChild, ScenarioEngineRequestMessageDescribe_getChild, ScenarioEngineRequestMessageDescribe_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ScenarioEngineRequestMessageInitialize"), ScenarioEngineRequestMessageInitialize_gen, ScenarioEngineRequestMessageInitialize_del, ScenarioEngineRequestMessageInitialize_setChild, ScenarioEngineRequestMessageInitialize_getChild, ScenarioEngineRequestMessageInitialize_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ScenarioEngineRequestMessageUIConfigure"), ScenarioEngineRequestMessageUIConfigure_gen, ScenarioEngineRequestMessageUIConfigure_del, ScenarioEngineRequestMessageUIConfigure_setChild, ScenarioEngineRequestMessageUIConfigure_getChild, ScenarioEngineRequestMessageUIConfigure_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ScenarioEngineRequestMessageWithData"), ScenarioEngineRequestMessageWithData_gen, ScenarioEngineRequestMessageWithData_del, ScenarioEngineRequestMessageWithData_setChild, ScenarioEngineRequestMessageWithData_getChild, ScenarioEngineRequestMessageWithData_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ScenarioEngineRequestMessageSetup"), ScenarioEngineRequestMessageSetup_gen, ScenarioEngineRequestMessageSetup_del, ScenarioEngineRequestMessageSetup_setChild, ScenarioEngineRequestMessageSetup_getChild, ScenarioEngineRequestMessageSetup_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ScenarioEngineNotifyStateContext"), ScenarioEngineNotifyStateContext_gen, ScenarioEngineNotifyStateContext_del, ScenarioEngineNotifyStateContext_setChild, ScenarioEngineNotifyStateContext_getChild, ScenarioEngineNotifyStateContext_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ScenarioEngineRequestMessageNotifyState"), ScenarioEngineRequestMessageNotifyState_gen, ScenarioEngineRequestMessageNotifyState_del, ScenarioEngineRequestMessageNotifyState_setChild, ScenarioEngineRequestMessageNotifyState_getChild, ScenarioEngineRequestMessageNotifyState_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ScenarioEngineNotifyInfoContext"), ScenarioEngineNotifyInfoContext_gen, ScenarioEngineNotifyInfoContext_del, ScenarioEngineNotifyInfoContext_setChild, ScenarioEngineNotifyInfoContext_getChild, ScenarioEngineNotifyInfoContext_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ScenarioEngineRequestMessageNotifyInfo"), ScenarioEngineRequestMessageNotifyInfo_gen, ScenarioEngineRequestMessageNotifyInfo_del, ScenarioEngineRequestMessageNotifyInfo_setChild, ScenarioEngineRequestMessageNotifyInfo_getChild, ScenarioEngineRequestMessageNotifyInfo_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ScenarioEngineNotifyErrorContext"), ScenarioEngineNotifyErrorContext_gen, ScenarioEngineNotifyErrorContext_del, ScenarioEngineNotifyErrorContext_setChild, ScenarioEngineNotifyErrorContext_getChild, ScenarioEngineNotifyErrorContext_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ScenarioEngineRequestMessageNotifyError"), ScenarioEngineRequestMessageNotifyError_gen, ScenarioEngineRequestMessageNotifyError_del, ScenarioEngineRequestMessageNotifyError_setChild, ScenarioEngineRequestMessageNotifyError_getChild, ScenarioEngineRequestMessageNotifyError_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ScenarioEngineRequestMessageNotify"), ScenarioEngineRequestMessageNotify_gen, ScenarioEngineRequestMessageNotify_del, ScenarioEngineRequestMessageNotify_setChild, ScenarioEngineRequestMessageNotify_getChild, ScenarioEngineRequestMessageNotify_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ScenarioEngineRequestMessageValidate"), ScenarioEngineRequestMessageValidate_gen, ScenarioEngineRequestMessageValidate_del, ScenarioEngineRequestMessageValidate_setChild, ScenarioEngineRequestMessageValidate_getChild, ScenarioEngineRequestMessageValidate_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ScenarioEngineWebSocketMessageRequest"), ScenarioEngineWebSocketMessageRequest_gen, ScenarioEngineWebSocketMessageRequest_del, ScenarioEngineWebSocketMessageRequest_setChild, ScenarioEngineWebSocketMessageRequest_getChild, ScenarioEngineWebSocketMessageRequest_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ScenarioEngineWebSocketMessage"), ScenarioEngineWebSocketMessage_gen, ScenarioEngineWebSocketMessage_del, ScenarioEngineWebSocketMessage_setChild, ScenarioEngineWebSocketMessage_getChild, ScenarioEngineWebSocketMessage_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
Dz1JsonSpec *ScenarioEngineWebSockMsgDef_genJsonSpec(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonSpec *ret = Dz1JsonSpec_generate(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonSpec_delAndSetNull, (void *)&ret);

		if (ScenarioEngineWebSockMsgDef_initJsonSpec(ret, errp) == FALSE) ERR_OUT(errp);
		else if (Dz1JsonSpec_check(ret, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1JsonSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Dz1JsonSpec Initializer
////////////////////////////////////////////////////////////////////////////////

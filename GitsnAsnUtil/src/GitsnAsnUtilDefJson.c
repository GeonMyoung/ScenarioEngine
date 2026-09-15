#include "GitsnAsnUtilDefJson.h"

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
bool_t GitsnAsnUtilDef_initJsonSpec(Dz1JsonSpec *dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (0) { }
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_TravelerInfoType"), Gitsn_TravelerInfoType_gen, Gitsn_TravelerInfoType_del, Gitsn_TravelerInfoType_load, Gitsn_TravelerInfoType_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_MUTCDCode"), Gitsn_MUTCDCode_gen, Gitsn_MUTCDCode_del, Gitsn_MUTCDCode_load, Gitsn_MUTCDCode_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_DirectionOfUse"), Gitsn_DirectionOfUse_gen, Gitsn_DirectionOfUse_del, Gitsn_DirectionOfUse_load, Gitsn_DirectionOfUse_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_NodeAttributeXY"), Gitsn_NodeAttributeXY_gen, Gitsn_NodeAttributeXY_del, Gitsn_NodeAttributeXY_load, Gitsn_NodeAttributeXY_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_SegmentAttributeXY"), Gitsn_SegmentAttributeXY_gen, Gitsn_SegmentAttributeXY_del, Gitsn_SegmentAttributeXY_load, Gitsn_SegmentAttributeXY_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_SpeedLimitType"), Gitsn_SpeedLimitType_gen, Gitsn_SpeedLimitType_del, Gitsn_SpeedLimitType_load, Gitsn_SpeedLimitType_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_NodeAttributeLL"), Gitsn_NodeAttributeLL_gen, Gitsn_NodeAttributeLL_del, Gitsn_NodeAttributeLL_load, Gitsn_NodeAttributeLL_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_SegmentAttributeLL"), Gitsn_SegmentAttributeLL_gen, Gitsn_SegmentAttributeLL_del, Gitsn_SegmentAttributeLL_load, Gitsn_SegmentAttributeLL_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_Extent"), Gitsn_Extent_gen, Gitsn_Extent_del, Gitsn_Extent_load, Gitsn_Extent_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("Gitsn_DistanceUnits"), Gitsn_DistanceUnits_gen, Gitsn_DistanceUnits_del, Gitsn_DistanceUnits_load, Gitsn_DistanceUnits_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Position3D"), Gitsn_Position3D_gen, Gitsn_Position3D_del, Gitsn_Position3D_setChild, Gitsn_Position3D_getChild, Gitsn_Position3D_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_RoadSignID"), Gitsn_RoadSignID_gen, Gitsn_RoadSignID_del, Gitsn_RoadSignID_setChild, Gitsn_RoadSignID_getChild, Gitsn_RoadSignID_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_TravelerDataFrame_msgId"), Gitsn_TravelerDataFrame_msgId_gen, Gitsn_TravelerDataFrame_msgId_del, Gitsn_TravelerDataFrame_msgId_setChild, Gitsn_TravelerDataFrame_msgId_getChild, Gitsn_TravelerDataFrame_msgId_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_RoadSegmentReferenceID"), Gitsn_RoadSegmentReferenceID_gen, Gitsn_RoadSegmentReferenceID_del, Gitsn_RoadSegmentReferenceID_setChild, Gitsn_RoadSegmentReferenceID_getChild, Gitsn_RoadSegmentReferenceID_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Node_XY_20b"), Gitsn_Node_XY_20b_gen, Gitsn_Node_XY_20b_del, Gitsn_Node_XY_20b_setChild, Gitsn_Node_XY_20b_getChild, Gitsn_Node_XY_20b_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Node_XY_22b"), Gitsn_Node_XY_22b_gen, Gitsn_Node_XY_22b_del, Gitsn_Node_XY_22b_setChild, Gitsn_Node_XY_22b_getChild, Gitsn_Node_XY_22b_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Node_XY_24b"), Gitsn_Node_XY_24b_gen, Gitsn_Node_XY_24b_del, Gitsn_Node_XY_24b_setChild, Gitsn_Node_XY_24b_getChild, Gitsn_Node_XY_24b_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Node_XY_26b"), Gitsn_Node_XY_26b_gen, Gitsn_Node_XY_26b_del, Gitsn_Node_XY_26b_setChild, Gitsn_Node_XY_26b_getChild, Gitsn_Node_XY_26b_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Node_XY_28b"), Gitsn_Node_XY_28b_gen, Gitsn_Node_XY_28b_del, Gitsn_Node_XY_28b_setChild, Gitsn_Node_XY_28b_getChild, Gitsn_Node_XY_28b_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Node_XY_32b"), Gitsn_Node_XY_32b_gen, Gitsn_Node_XY_32b_del, Gitsn_Node_XY_32b_setChild, Gitsn_Node_XY_32b_getChild, Gitsn_Node_XY_32b_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_Node_LLmD_64b"), Gitsn_Node_LLmD_64b_gen, Gitsn_Node_LLmD_64b_del, Gitsn_Node_LLmD_64b_setChild, Gitsn_Node_LLmD_64b_getChild, Gitsn_Node_LLmD_64b_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_NodeOffsetPointXY"), Gitsn_NodeOffsetPointXY_gen, Gitsn_NodeOffsetPointXY_del, Gitsn_NodeOffsetPointXY_setChild, Gitsn_NodeOffsetPointXY_getChild, Gitsn_NodeOffsetPointXY_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_RegulatorySpeedLimit"), Gitsn_RegulatorySpeedLimit_gen, Gitsn_RegulatorySpeedLimit_del, Gitsn_RegulatorySpeedLimit_setChild, Gitsn_RegulatorySpeedLimit_getChild, Gitsn_RegulatorySpeedLimit_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_LaneDataAttribute"), Gitsn_LaneDataAttribute_gen, Gitsn_LaneDataAttribute_del, Gitsn_LaneDataAttribute_setChild, Gitsn_LaneDataAttribute_getChild, Gitsn_LaneDataAttribute_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_NodeAttributeSetXY"), Gitsn_NodeAttributeSetXY_gen, Gitsn_NodeAttributeSetXY_del, Gitsn_NodeAttributeSetXY_setChild, Gitsn_NodeAttributeSetXY_getChild, Gitsn_NodeAttributeSetXY_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_NodeXY"), Gitsn_NodeXY_gen, Gitsn_NodeXY_del, Gitsn_NodeXY_setChild, Gitsn_NodeXY_getChild, Gitsn_NodeXY_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_ComputedLane_offsetXaxis"), Gitsn_ComputedLane_offsetXaxis_gen, Gitsn_ComputedLane_offsetXaxis_del, Gitsn_ComputedLane_offsetXaxis_setChild, Gitsn_ComputedLane_offsetXaxis_getChild, Gitsn_ComputedLane_offsetXaxis_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_ComputedLane_offsetYaxis"), Gitsn_ComputedLane_offsetYaxis_gen, Gitsn_ComputedLane_offsetYaxis_del, Gitsn_ComputedLane_offsetYaxis_setChild, Gitsn_ComputedLane_offsetYaxis_getChild, Gitsn_ComputedLane_offsetYaxis_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_ComputedLane"), Gitsn_ComputedLane_gen, Gitsn_ComputedLane_del, Gitsn_ComputedLane_setChild, Gitsn_ComputedLane_getChild, Gitsn_ComputedLane_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("Gitsn_NodeListXY"), Gitsn_NodeListXY_gen, Gitsn_NodeListXY_del, Gitsn_NodeListXY_setChild, Gitsn_NodeListXY_getChild, Gitsn_NodeListXY_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
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
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_NodeAttributeXYList"), Gitsn_NodeAttributeXYList_gen, Gitsn_NodeAttributeXYList_del, Gitsn_NodeAttributeXYList_append, Gitsn_NodeAttributeXYList_cnt, Gitsn_NodeAttributeXYList_tlv, Dz1Text("Gitsn_NodeAttributeXY") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_SegmentAttributeXYList"), Gitsn_SegmentAttributeXYList_gen, Gitsn_SegmentAttributeXYList_del, Gitsn_SegmentAttributeXYList_append, Gitsn_SegmentAttributeXYList_cnt, Gitsn_SegmentAttributeXYList_tlv, Dz1Text("Gitsn_SegmentAttributeXY") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_SpeedLimitList"), Gitsn_SpeedLimitList_gen, Gitsn_SpeedLimitList_del, Gitsn_SpeedLimitList_append, Gitsn_SpeedLimitList_cnt, Gitsn_SpeedLimitList_tlv, Dz1Text("Gitsn_RegulatorySpeedLimit") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_LaneDataAttributeList"), Gitsn_LaneDataAttributeList_gen, Gitsn_LaneDataAttributeList_del, Gitsn_LaneDataAttributeList_append, Gitsn_LaneDataAttributeList_cnt, Gitsn_LaneDataAttributeList_tlv, Dz1Text("Gitsn_LaneDataAttribute") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("Gitsn_NodeSetXY"), Gitsn_NodeSetXY_gen, Gitsn_NodeSetXY_del, Gitsn_NodeSetXY_append, Gitsn_NodeSetXY_cnt, Gitsn_NodeSetXY_tlv, Dz1Text("Gitsn_NodeXY") )).code) ERR_OUT(errp);
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
Dz1JsonSpec *GitsnAsnUtilDef_genJsonSpec(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonSpec *ret = Dz1JsonSpec_generate(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonSpec_delAndSetNull, (void *)&ret);

		if (GitsnAsnUtilDef_initJsonSpec(ret, errp) == FALSE) ERR_OUT(errp);
		else if (Dz1JsonSpec_check(ret, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1JsonSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Dz1JsonSpec Initializer
////////////////////////////////////////////////////////////////////////////////

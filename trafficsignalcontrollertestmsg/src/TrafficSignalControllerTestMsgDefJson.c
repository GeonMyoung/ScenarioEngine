#include "TrafficSignalControllerTestMsgDefJson.h"

////////////////////////////////////////////////////////////////////////////////
// CrossControlRingLcCmd
static bool_t CrossControlRingLcCmd_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CrossControlRingLcCmd v = CrossControlRingLcCmd_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (CrossControlRingLcCmd)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = CrossControlRingLcCmdFromStr(tok->v)) == CrossControlRingLcCmd_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = CrossControlRingLcCmd_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t CrossControlRingLcCmd_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		CrossControlRingLcCmd v = *(CrossControlRingLcCmd *)obj;
		Dz1Str str_v = CrossControlRingLcCmdStr(v);
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
// CrossControlRingLcCmd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlRingRcCmd
static bool_t CrossControlRingRcCmd_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CrossControlRingRcCmd v = CrossControlRingRcCmd_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (CrossControlRingRcCmd)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = CrossControlRingRcCmdFromStr(tok->v)) == CrossControlRingRcCmd_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = CrossControlRingRcCmd_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t CrossControlRingRcCmd_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		CrossControlRingRcCmd v = *(CrossControlRingRcCmd *)obj;
		Dz1Str str_v = CrossControlRingRcCmdStr(v);
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
// CrossControlRingRcCmd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlSingleCmd
static bool_t CrossControlSingleCmd_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CrossControlSingleCmd *p = (CrossControlSingleCmd *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case CrossControlSingleCmdPresent_lc_fixed: p->x.lc_fixed = *(CrossControlRingLcCmd *)info->data; break;
	case CrossControlSingleCmdPresent_lc_control: p->x.lc_control = *(CrossControlRingLcCmd *)info->data; break;
	case CrossControlSingleCmdPresent_lc_actuation: p->x.lc_actuation = *(CrossControlRingLcCmd *)info->data; break;
	case CrossControlSingleCmdPresent_rc_actuation: p->x.rc_actuation = *(CrossControlRingRcCmd *)info->data; break;
	case CrossControlSingleCmdPresent_rc_online: p->x.rc_online = *(CrossControlRingRcCmd *)info->data; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (CrossControlSingleCmdPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *CrossControlSingleCmd_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	CrossControlSingleCmd *p = (CrossControlSingleCmd *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case CrossControlSingleCmdPresent_lc_fixed: return &p->x.lc_fixed;
		case CrossControlSingleCmdPresent_lc_control: return &p->x.lc_control;
		case CrossControlSingleCmdPresent_lc_actuation: return &p->x.lc_actuation;
		case CrossControlSingleCmdPresent_rc_actuation: return &p->x.rc_actuation;
		case CrossControlSingleCmdPresent_rc_online: return &p->x.rc_online;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild CrossControlSingleCmd_membs[] =
{
	{ Dz1Text("lc_fixed"), Dz1Text("CrossControlRingLcCmd"), CrossControlSingleCmdPresent_lc_fixed },
	{ Dz1Text("lc_control"), Dz1Text("CrossControlRingLcCmd"), CrossControlSingleCmdPresent_lc_control },
	{ Dz1Text("lc_actuation"), Dz1Text("CrossControlRingLcCmd"), CrossControlSingleCmdPresent_lc_actuation },
	{ Dz1Text("rc_actuation"), Dz1Text("CrossControlRingRcCmd"), CrossControlSingleCmdPresent_rc_actuation },
	{ Dz1Text("rc_online"), Dz1Text("CrossControlRingRcCmd"), CrossControlSingleCmdPresent_rc_online },
	{ NULL, NULL, -1 }
};
// CrossControlSingleCmd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlRingLcDualCmd
static bool_t CrossControlRingLcDualCmd_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CrossControlRingLcDualCmd *p = (CrossControlRingLcDualCmd *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->ring_b =  *(CrossControlRingLcCmd *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->ring_a =  *(CrossControlRingLcCmd *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *CrossControlRingLcDualCmd_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	CrossControlRingLcDualCmd *p = (CrossControlRingLcDualCmd *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->ring_b;
	case 1: return &p->ring_a;
	default: return NULL;
	}
}

static Dz1JsonSpecChild CrossControlRingLcDualCmd_membs[] =
{
	{ Dz1Text("ring_b"), Dz1Text("CrossControlRingLcCmd"), 0 },
	{ Dz1Text("ring_a"), Dz1Text("CrossControlRingLcCmd"), 1 },
	{ NULL, NULL, -1 }
};
// CrossControlRingLcDualCmd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlRingRcDualCmd
static bool_t CrossControlRingRcDualCmd_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CrossControlRingRcDualCmd *p = (CrossControlRingRcDualCmd *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->ring_b =  *(CrossControlRingRcCmd *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->ring_a =  *(CrossControlRingRcCmd *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *CrossControlRingRcDualCmd_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	CrossControlRingRcDualCmd *p = (CrossControlRingRcDualCmd *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->ring_b;
	case 1: return &p->ring_a;
	default: return NULL;
	}
}

static Dz1JsonSpecChild CrossControlRingRcDualCmd_membs[] =
{
	{ Dz1Text("ring_b"), Dz1Text("CrossControlRingRcCmd"), 0 },
	{ Dz1Text("ring_a"), Dz1Text("CrossControlRingRcCmd"), 1 },
	{ NULL, NULL, -1 }
};
// CrossControlRingRcDualCmd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlDualCmd
static bool_t CrossControlDualCmd_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CrossControlDualCmd *p = (CrossControlDualCmd *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case CrossControlDualCmdPresent_lc_fixed: CrossControlRingLcDualCmd_delAndSetNull(&p->x.lc_fixed); p->x.lc_fixed =(CrossControlRingLcDualCmd *)info->data; info->data = NULL; break;
	case CrossControlDualCmdPresent_lc_control: CrossControlRingLcDualCmd_delAndSetNull(&p->x.lc_control); p->x.lc_control =(CrossControlRingLcDualCmd *)info->data; info->data = NULL; break;
	case CrossControlDualCmdPresent_lc_actuation: CrossControlRingLcDualCmd_delAndSetNull(&p->x.lc_actuation); p->x.lc_actuation =(CrossControlRingLcDualCmd *)info->data; info->data = NULL; break;
	case CrossControlDualCmdPresent_rc_actuation: CrossControlRingRcDualCmd_delAndSetNull(&p->x.rc_actuation); p->x.rc_actuation =(CrossControlRingRcDualCmd *)info->data; info->data = NULL; break;
	case CrossControlDualCmdPresent_rc_online: CrossControlRingRcDualCmd_delAndSetNull(&p->x.rc_online); p->x.rc_online =(CrossControlRingRcDualCmd *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (CrossControlDualCmdPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *CrossControlDualCmd_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	CrossControlDualCmd *p = (CrossControlDualCmd *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case CrossControlDualCmdPresent_lc_fixed: return p->x.lc_fixed;
		case CrossControlDualCmdPresent_lc_control: return p->x.lc_control;
		case CrossControlDualCmdPresent_lc_actuation: return p->x.lc_actuation;
		case CrossControlDualCmdPresent_rc_actuation: return p->x.rc_actuation;
		case CrossControlDualCmdPresent_rc_online: return p->x.rc_online;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild CrossControlDualCmd_membs[] =
{
	{ Dz1Text("lc_fixed"), Dz1Text("CrossControlRingLcDualCmd"), CrossControlDualCmdPresent_lc_fixed },
	{ Dz1Text("lc_control"), Dz1Text("CrossControlRingLcDualCmd"), CrossControlDualCmdPresent_lc_control },
	{ Dz1Text("lc_actuation"), Dz1Text("CrossControlRingLcDualCmd"), CrossControlDualCmdPresent_lc_actuation },
	{ Dz1Text("rc_actuation"), Dz1Text("CrossControlRingRcDualCmd"), CrossControlDualCmdPresent_rc_actuation },
	{ Dz1Text("rc_online"), Dz1Text("CrossControlRingRcDualCmd"), CrossControlDualCmdPresent_rc_online },
	{ NULL, NULL, -1 }
};
// CrossControlDualCmd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlCmd
static bool_t CrossControlCmd_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CrossControlCmd *p = (CrossControlCmd *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case CrossControlCmdPresent_single: CrossControlSingleCmd_delAndSetNull(&p->x.single); p->x.single =(CrossControlSingleCmd *)info->data; info->data = NULL; break;
	case CrossControlCmdPresent_dual: CrossControlDualCmd_delAndSetNull(&p->x.dual); p->x.dual =(CrossControlDualCmd *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (CrossControlCmdPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *CrossControlCmd_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	CrossControlCmd *p = (CrossControlCmd *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case CrossControlCmdPresent_single: return p->x.single;
		case CrossControlCmdPresent_dual: return p->x.dual;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild CrossControlCmd_membs[] =
{
	{ Dz1Text("single"), Dz1Text("CrossControlSingleCmd"), CrossControlCmdPresent_single },
	{ Dz1Text("dual"), Dz1Text("CrossControlDualCmd"), CrossControlCmdPresent_dual },
	{ NULL, NULL, -1 }
};
// CrossControlCmd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossControlInformation
static bool_t CrossControlInformation_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CrossControlInformation *p = (CrossControlInformation *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->cross_id =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: CrossControlCmd_delAndSetNull(&p->command); p->command = (CrossControlCmd *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *CrossControlInformation_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	CrossControlInformation *p = (CrossControlInformation *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->cross_id;
	case 1: return p->command;
	default: return NULL;
	}
}

static Dz1JsonSpecChild CrossControlInformation_membs[] =
{
	{ Dz1Text("cross_id"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("command"), Dz1Text("CrossControlCmd"), 1 },
	{ NULL, NULL, -1 }
};
// CrossControlInformation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossIndicator
static bool_t CrossIndicator_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CrossIndicator *p = (CrossIndicator *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->cross_id =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *CrossIndicator_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	CrossIndicator *p = (CrossIndicator *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->cross_id;
	default: return NULL;
	}
}

static Dz1JsonSpecChild CrossIndicator_membs[] =
{
	{ Dz1Text("cross_id"), Dz1Text("u8_t"), 0 },
	{ NULL, NULL, -1 }
};
// CrossIndicator
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SignalPhaseInfoPeriodicOperationTime
static bool_t SignalPhaseInfoPeriodicOperationTime_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SignalPhaseInfoPeriodicOperationTime *p = (SignalPhaseInfoPeriodicOperationTime *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->ring_a_phase1 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->ring_a_phase2 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->ring_a_phase3 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->ring_a_phase4 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->ring_a_phase5 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->ring_a_phase6 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->ring_a_phase7 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->ring_a_phase8 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->ring_b_phase1 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 9: p->ring_b_phase2 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 10: p->ring_b_phase3 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 11: p->ring_b_phase4 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 12: p->ring_b_phase5 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 13: p->ring_b_phase6 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 14: p->ring_b_phase7 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 15: p->ring_b_phase8 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *SignalPhaseInfoPeriodicOperationTime_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	SignalPhaseInfoPeriodicOperationTime *p = (SignalPhaseInfoPeriodicOperationTime *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->ring_a_phase1;
	case 1: return &p->ring_a_phase2;
	case 2: return &p->ring_a_phase3;
	case 3: return &p->ring_a_phase4;
	case 4: return &p->ring_a_phase5;
	case 5: return &p->ring_a_phase6;
	case 6: return &p->ring_a_phase7;
	case 7: return &p->ring_a_phase8;
	case 8: return &p->ring_b_phase1;
	case 9: return &p->ring_b_phase2;
	case 10: return &p->ring_b_phase3;
	case 11: return &p->ring_b_phase4;
	case 12: return &p->ring_b_phase5;
	case 13: return &p->ring_b_phase6;
	case 14: return &p->ring_b_phase7;
	case 15: return &p->ring_b_phase8;
	default: return NULL;
	}
}

static Dz1JsonSpecChild SignalPhaseInfoPeriodicOperationTime_membs[] =
{
	{ Dz1Text("ring_a_phase1"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("ring_a_phase2"), Dz1Text("u8_t"), 1 },
	{ Dz1Text("ring_a_phase3"), Dz1Text("u8_t"), 2 },
	{ Dz1Text("ring_a_phase4"), Dz1Text("u8_t"), 3 },
	{ Dz1Text("ring_a_phase5"), Dz1Text("u8_t"), 4 },
	{ Dz1Text("ring_a_phase6"), Dz1Text("u8_t"), 5 },
	{ Dz1Text("ring_a_phase7"), Dz1Text("u8_t"), 6 },
	{ Dz1Text("ring_a_phase8"), Dz1Text("u8_t"), 7 },
	{ Dz1Text("ring_b_phase1"), Dz1Text("u8_t"), 8 },
	{ Dz1Text("ring_b_phase2"), Dz1Text("u8_t"), 9 },
	{ Dz1Text("ring_b_phase3"), Dz1Text("u8_t"), 10 },
	{ Dz1Text("ring_b_phase4"), Dz1Text("u8_t"), 11 },
	{ Dz1Text("ring_b_phase5"), Dz1Text("u8_t"), 12 },
	{ Dz1Text("ring_b_phase6"), Dz1Text("u8_t"), 13 },
	{ Dz1Text("ring_b_phase7"), Dz1Text("u8_t"), 14 },
	{ Dz1Text("ring_b_phase8"), Dz1Text("u8_t"), 15 },
	{ NULL, NULL, -1 }
};
// SignalPhaseInfoPeriodicOperationTime
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SignalPhaseInfoDownBasic
static bool_t SignalPhaseInfoDownBasic_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SignalPhaseInfoDownBasic *p = (SignalPhaseInfoDownBasic *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: SignalPhaseInfoPeriodicOperationTime_delAndSetNull(&p->periodic_oper_time1); p->periodic_oper_time1 = (SignalPhaseInfoPeriodicOperationTime *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: p->offset =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *SignalPhaseInfoDownBasic_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	SignalPhaseInfoDownBasic *p = (SignalPhaseInfoDownBasic *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->periodic_oper_time1;
	case 1: return &p->offset;
	default: return NULL;
	}
}

static Dz1JsonSpecChild SignalPhaseInfoDownBasic_membs[] =
{
	{ Dz1Text("periodic_oper_time1"), Dz1Text("SignalPhaseInfoPeriodicOperationTime"), 0 },
	{ Dz1Text("offset"), Dz1Text("u8_t"), 1 },
	{ NULL, NULL, -1 }
};
// SignalPhaseInfoDownBasic
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SignalPhaseInfoDown_r27
static bool_t SignalPhaseInfoDown_r27_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SignalPhaseInfoDown_r27 *p = (SignalPhaseInfoDown_r27 *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: SignalPhaseInfoDownBasic_delAndSetNull(&p->mandatory); p->mandatory = (SignalPhaseInfoDownBasic *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: SignalPhaseInfoPeriodicOperationTime_delAndSetNull(&p->periodic_oper_time2); p->periodic_oper_time2 = (SignalPhaseInfoPeriodicOperationTime *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: SignalPhaseInfoPeriodicOperationTime_delAndSetNull(&p->periodic_oper_time3); p->periodic_oper_time3 = (SignalPhaseInfoPeriodicOperationTime *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *SignalPhaseInfoDown_r27_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	SignalPhaseInfoDown_r27 *p = (SignalPhaseInfoDown_r27 *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->mandatory;
	case 1: return p->periodic_oper_time2;
	case 2: return p->periodic_oper_time3;
	default: return NULL;
	}
}

static Dz1JsonSpecChild SignalPhaseInfoDown_r27_membs[] =
{
	{ Dz1Text("mandatory"), Dz1Text("SignalPhaseInfoDownBasic"), 0 },
	{ Dz1Text("periodic_oper_time2"), Dz1Text("SignalPhaseInfoPeriodicOperationTime"), 1 },
	{ Dz1Text("periodic_oper_time3"), Dz1Text("SignalPhaseInfoPeriodicOperationTime"), 2 },
	{ NULL, NULL, -1 }
};
// SignalPhaseInfoDown_r27
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SignalPhaseInformationDownload
static bool_t SignalPhaseInformationDownload_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SignalPhaseInformationDownload *p = (SignalPhaseInformationDownload *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->cross_id =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: SignalPhaseInfoDown_r27_delAndSetNull(&p->signal_phase_info_down); p->signal_phase_info_down = (SignalPhaseInfoDown_r27 *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *SignalPhaseInformationDownload_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	SignalPhaseInformationDownload *p = (SignalPhaseInformationDownload *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->cross_id;
	case 1: return p->signal_phase_info_down;
	default: return NULL;
	}
}

static Dz1JsonSpecChild SignalPhaseInformationDownload_membs[] =
{
	{ Dz1Text("cross_id"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("signal_phase_info_down"), Dz1Text("SignalPhaseInfoDown_r27"), 1 },
	{ NULL, NULL, -1 }
};
// SignalPhaseInformationDownload
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ClockInfoWeekIndex
static bool_t ClockInfoWeekIndex_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ClockInfoWeekIndex v = ClockInfoWeekIndex_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (ClockInfoWeekIndex)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = ClockInfoWeekIndexFromStr(tok->v)) == ClockInfoWeekIndex_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = ClockInfoWeekIndex_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t ClockInfoWeekIndex_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		ClockInfoWeekIndex v = *(ClockInfoWeekIndex *)obj;
		Dz1Str str_v = ClockInfoWeekIndexStr(v);
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
// ClockInfoWeekIndex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ClockInfo
static bool_t ClockInfo_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ClockInfo *p = (ClockInfo *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->year =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->month =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->day =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->hour =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->minute =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->second =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->week_index =  *(ClockInfoWeekIndex *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ClockInfo_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ClockInfo *p = (ClockInfo *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->year;
	case 1: return &p->month;
	case 2: return &p->day;
	case 3: return &p->hour;
	case 4: return &p->minute;
	case 5: return &p->second;
	case 6: return &p->week_index;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ClockInfo_membs[] =
{
	{ Dz1Text("year"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("month"), Dz1Text("u8_t"), 1 },
	{ Dz1Text("day"), Dz1Text("u8_t"), 2 },
	{ Dz1Text("hour"), Dz1Text("u8_t"), 3 },
	{ Dz1Text("minute"), Dz1Text("u8_t"), 4 },
	{ Dz1Text("second"), Dz1Text("u8_t"), 5 },
	{ Dz1Text("week_index"), Dz1Text("ClockInfoWeekIndex"), 6 },
	{ NULL, NULL, -1 }
};
// ClockInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ClockInformationDownload
static bool_t ClockInformationDownload_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ClockInformationDownload *p = (ClockInformationDownload *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->cross_id =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: ClockInfo_delAndSetNull(&p->clock_info_down); p->clock_info_down = (ClockInfo *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ClockInformationDownload_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ClockInformationDownload *p = (ClockInformationDownload *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->cross_id;
	case 1: return p->clock_info_down;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ClockInformationDownload_membs[] =
{
	{ Dz1Text("cross_id"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("clock_info_down"), Dz1Text("ClockInfo"), 1 },
	{ NULL, NULL, -1 }
};
// ClockInformationDownload
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandPPCVehicleProperty
static bool_t SpecialCommandPPCVehicleProperty_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SpecialCommandPPCVehicleProperty *p = (SpecialCommandPPCVehicleProperty *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->property =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *SpecialCommandPPCVehicleProperty_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	SpecialCommandPPCVehicleProperty *p = (SpecialCommandPPCVehicleProperty *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->property;
	default: return NULL;
	}
}

static Dz1JsonSpecChild SpecialCommandPPCVehicleProperty_membs[] =
{
	{ Dz1Text("property"), Dz1Text("u32_t"), 0 },
	{ NULL, NULL, -1 }
};
// SpecialCommandPPCVehicleProperty
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandInfoPPCControlManage
static bool_t SpecialCommandInfoPPCControlManage_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SpecialCommandInfoPPCControlManage *p = (SpecialCommandInfoPPCControlManage *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->is_org_code_registered_vehicle_request =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->is_register_org_code =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->is_delete_org_code =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->is_register_vehicle_num =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->is_delete_vehicle_num =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->vehicle_code =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->org_manage_code =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: SpecialCommandPPCVehicleProperty_delAndSetNull(&p->vehicle_property); p->vehicle_property = (SpecialCommandPPCVehicleProperty *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *SpecialCommandInfoPPCControlManage_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	SpecialCommandInfoPPCControlManage *p = (SpecialCommandInfoPPCControlManage *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->is_org_code_registered_vehicle_request;
	case 1: return &p->is_register_org_code;
	case 2: return &p->is_delete_org_code;
	case 3: return &p->is_register_vehicle_num;
	case 4: return &p->is_delete_vehicle_num;
	case 5: return &p->vehicle_code;
	case 6: return &p->org_manage_code;
	case 7: return p->vehicle_property;
	default: return NULL;
	}
}

static Dz1JsonSpecChild SpecialCommandInfoPPCControlManage_membs[] =
{
	{ Dz1Text("is_org_code_registered_vehicle_request"), Dz1Text("bool_t"), 0 },
	{ Dz1Text("is_register_org_code"), Dz1Text("bool_t"), 1 },
	{ Dz1Text("is_delete_org_code"), Dz1Text("bool_t"), 2 },
	{ Dz1Text("is_register_vehicle_num"), Dz1Text("bool_t"), 3 },
	{ Dz1Text("is_delete_vehicle_num"), Dz1Text("bool_t"), 4 },
	{ Dz1Text("vehicle_code"), Dz1Text("bool_t"), 5 },
	{ Dz1Text("org_manage_code"), Dz1Text("u8_t"), 6 },
	{ Dz1Text("vehicle_property"), Dz1Text("SpecialCommandPPCVehicleProperty"), 7 },
	{ NULL, NULL, -1 }
};
// SpecialCommandInfoPPCControlManage
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandInfo
static bool_t SpecialCommandInfo_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SpecialCommandInfo *p = (SpecialCommandInfo *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->is_shut_down =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->is_blink_control =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->is_lamp_light_control =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->is_confilct =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->is_manual =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->is_confilct_reset =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->is_scu_reset =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->is_mcu_reset =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->is_ppc_control =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 9: p->is_pedestrian_button =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 10: p->is_x_control =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 11: p->is_spill_back_control =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 12: p->is_phase_omit =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 13: p->is_phase_hold =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 14: p->is_actuation_control =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 15: p->is_stagger_control =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 16: p->operation_flag =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 17: p->hold_omit_phase =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 18: p->stagger_plan =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 19: p->spill_back_direction_code =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 20: p->sub_phase_spill_back =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 21: p->main_phase_spill_back =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 22: SpecialCommandInfoPPCControlManage_delAndSetNull(&p->ppc_control_manage); p->ppc_control_manage = (SpecialCommandInfoPPCControlManage *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *SpecialCommandInfo_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	SpecialCommandInfo *p = (SpecialCommandInfo *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->is_shut_down;
	case 1: return &p->is_blink_control;
	case 2: return &p->is_lamp_light_control;
	case 3: return &p->is_confilct;
	case 4: return &p->is_manual;
	case 5: return &p->is_confilct_reset;
	case 6: return &p->is_scu_reset;
	case 7: return &p->is_mcu_reset;
	case 8: return &p->is_ppc_control;
	case 9: return &p->is_pedestrian_button;
	case 10: return &p->is_x_control;
	case 11: return &p->is_spill_back_control;
	case 12: return &p->is_phase_omit;
	case 13: return &p->is_phase_hold;
	case 14: return &p->is_actuation_control;
	case 15: return &p->is_stagger_control;
	case 16: return &p->operation_flag;
	case 17: return &p->hold_omit_phase;
	case 18: return &p->stagger_plan;
	case 19: return &p->spill_back_direction_code;
	case 20: return &p->sub_phase_spill_back;
	case 21: return &p->main_phase_spill_back;
	case 22: return p->ppc_control_manage;
	default: return NULL;
	}
}

static Dz1JsonSpecChild SpecialCommandInfo_membs[] =
{
	{ Dz1Text("is_shut_down"), Dz1Text("bool_t"), 0 },
	{ Dz1Text("is_blink_control"), Dz1Text("bool_t"), 1 },
	{ Dz1Text("is_lamp_light_control"), Dz1Text("bool_t"), 2 },
	{ Dz1Text("is_confilct"), Dz1Text("bool_t"), 3 },
	{ Dz1Text("is_manual"), Dz1Text("bool_t"), 4 },
	{ Dz1Text("is_confilct_reset"), Dz1Text("bool_t"), 5 },
	{ Dz1Text("is_scu_reset"), Dz1Text("bool_t"), 6 },
	{ Dz1Text("is_mcu_reset"), Dz1Text("bool_t"), 7 },
	{ Dz1Text("is_ppc_control"), Dz1Text("bool_t"), 8 },
	{ Dz1Text("is_pedestrian_button"), Dz1Text("bool_t"), 9 },
	{ Dz1Text("is_x_control"), Dz1Text("bool_t"), 10 },
	{ Dz1Text("is_spill_back_control"), Dz1Text("bool_t"), 11 },
	{ Dz1Text("is_phase_omit"), Dz1Text("bool_t"), 12 },
	{ Dz1Text("is_phase_hold"), Dz1Text("bool_t"), 13 },
	{ Dz1Text("is_actuation_control"), Dz1Text("bool_t"), 14 },
	{ Dz1Text("is_stagger_control"), Dz1Text("bool_t"), 15 },
	{ Dz1Text("operation_flag"), Dz1Text("u8_t"), 16 },
	{ Dz1Text("hold_omit_phase"), Dz1Text("u8_t"), 17 },
	{ Dz1Text("stagger_plan"), Dz1Text("u8_t"), 18 },
	{ Dz1Text("spill_back_direction_code"), Dz1Text("u8_t"), 19 },
	{ Dz1Text("sub_phase_spill_back"), Dz1Text("u8_t"), 20 },
	{ Dz1Text("main_phase_spill_back"), Dz1Text("u8_t"), 21 },
	{ Dz1Text("ppc_control_manage"), Dz1Text("SpecialCommandInfoPPCControlManage"), 22 },
	{ NULL, NULL, -1 }
};
// SpecialCommandInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandInformation
static bool_t SpecialCommandInformation_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SpecialCommandInformation *p = (SpecialCommandInformation *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->cross_id =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: SpecialCommandInfo_delAndSetNull(&p->special_command); p->special_command = (SpecialCommandInfo *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *SpecialCommandInformation_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	SpecialCommandInformation *p = (SpecialCommandInformation *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->cross_id;
	case 1: return p->special_command;
	default: return NULL;
	}
}

static Dz1JsonSpecChild SpecialCommandInformation_membs[] =
{
	{ Dz1Text("cross_id"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("special_command"), Dz1Text("SpecialCommandInfo"), 1 },
	{ NULL, NULL, -1 }
};
// SpecialCommandInformation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// FirmwareUpgradeData
static bool_t FirmwareUpgradeData_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	FirmwareUpgradeData *p = (FirmwareUpgradeData *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->fw_module_id =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->fw_module_size =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: Dz1Str_delAndSetNull(&p->fname); p->fname = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 3: p->major_version =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->minor_version =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->module_version =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->revision_version =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->is_forced_upgrade =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->reboot_option =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 9: p->crc32 =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *FirmwareUpgradeData_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	FirmwareUpgradeData *p = (FirmwareUpgradeData *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->fw_module_id;
	case 1: return &p->fw_module_size;
	case 2: return p->fname;
	case 3: return &p->major_version;
	case 4: return &p->minor_version;
	case 5: return &p->module_version;
	case 6: return &p->revision_version;
	case 7: return &p->is_forced_upgrade;
	case 8: return &p->reboot_option;
	case 9: return &p->crc32;
	default: return NULL;
	}
}

static Dz1JsonSpecChild FirmwareUpgradeData_membs[] =
{
	{ Dz1Text("fw_module_id"), Dz1Text("u16_t"), 0 },
	{ Dz1Text("fw_module_size"), Dz1Text("u32_t"), 1 },
	{ Dz1Text("fname"), Dz1Text("Dz1Str"), 2 },
	{ Dz1Text("major_version"), Dz1Text("u8_t"), 3 },
	{ Dz1Text("minor_version"), Dz1Text("u8_t"), 4 },
	{ Dz1Text("module_version"), Dz1Text("u8_t"), 5 },
	{ Dz1Text("revision_version"), Dz1Text("u16_t"), 6 },
	{ Dz1Text("is_forced_upgrade"), Dz1Text("bool_t"), 7 },
	{ Dz1Text("reboot_option"), Dz1Text("u8_t"), 8 },
	{ Dz1Text("crc32"), Dz1Text("u32_t"), 9 },
	{ NULL, NULL, -1 }
};
// FirmwareUpgradeData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// FirmwareUpgradeCommand
static bool_t FirmwareUpgradeCommand_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	FirmwareUpgradeCommand *p = (FirmwareUpgradeCommand *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->cross_id =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: FirmwareUpgradeData_delAndSetNull(&p->fw_upgrade_data); p->fw_upgrade_data = (FirmwareUpgradeData *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *FirmwareUpgradeCommand_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	FirmwareUpgradeCommand *p = (FirmwareUpgradeCommand *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->cross_id;
	case 1: return p->fw_upgrade_data;
	default: return NULL;
	}
}

static Dz1JsonSpecChild FirmwareUpgradeCommand_membs[] =
{
	{ Dz1Text("cross_id"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("fw_upgrade_data"), Dz1Text("FirmwareUpgradeData"), 1 },
	{ NULL, NULL, -1 }
};
// FirmwareUpgradeCommand
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerRequest
static bool_t TrafficSignalControllerRequest_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TrafficSignalControllerRequest *p = (TrafficSignalControllerRequest *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case TrafficSignalControllerRequestPresent_control: CrossControlInformation_delAndSetNull(&p->x.control); p->x.control =(CrossControlInformation *)info->data; info->data = NULL; break;
	case TrafficSignalControllerRequestPresent_status: CrossIndicator_delAndSetNull(&p->x.status); p->x.status =(CrossIndicator *)info->data; info->data = NULL; break;
	case TrafficSignalControllerRequestPresent_detector: CrossIndicator_delAndSetNull(&p->x.detector); p->x.detector =(CrossIndicator *)info->data; info->data = NULL; break;
	case TrafficSignalControllerRequestPresent_signal_phase_down: SignalPhaseInformationDownload_delAndSetNull(&p->x.signal_phase_down); p->x.signal_phase_down =(SignalPhaseInformationDownload *)info->data; info->data = NULL; break;
	case TrafficSignalControllerRequestPresent_signal_phase_up: CrossIndicator_delAndSetNull(&p->x.signal_phase_up); p->x.signal_phase_up =(CrossIndicator *)info->data; info->data = NULL; break;
	case TrafficSignalControllerRequestPresent_clock_down: ClockInformationDownload_delAndSetNull(&p->x.clock_down); p->x.clock_down =(ClockInformationDownload *)info->data; info->data = NULL; break;
	case TrafficSignalControllerRequestPresent_clock_up: CrossIndicator_delAndSetNull(&p->x.clock_up); p->x.clock_up =(CrossIndicator *)info->data; info->data = NULL; break;
	case TrafficSignalControllerRequestPresent_special_cmd: SpecialCommandInformation_delAndSetNull(&p->x.special_cmd); p->x.special_cmd =(SpecialCommandInformation *)info->data; info->data = NULL; break;
	case TrafficSignalControllerRequestPresent_fw_upgrade_cmd: FirmwareUpgradeCommand_delAndSetNull(&p->x.fw_upgrade_cmd); p->x.fw_upgrade_cmd =(FirmwareUpgradeCommand *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (TrafficSignalControllerRequestPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *TrafficSignalControllerRequest_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	TrafficSignalControllerRequest *p = (TrafficSignalControllerRequest *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case TrafficSignalControllerRequestPresent_control: return p->x.control;
		case TrafficSignalControllerRequestPresent_status: return p->x.status;
		case TrafficSignalControllerRequestPresent_detector: return p->x.detector;
		case TrafficSignalControllerRequestPresent_signal_phase_down: return p->x.signal_phase_down;
		case TrafficSignalControllerRequestPresent_signal_phase_up: return p->x.signal_phase_up;
		case TrafficSignalControllerRequestPresent_clock_down: return p->x.clock_down;
		case TrafficSignalControllerRequestPresent_clock_up: return p->x.clock_up;
		case TrafficSignalControllerRequestPresent_special_cmd: return p->x.special_cmd;
		case TrafficSignalControllerRequestPresent_fw_upgrade_cmd: return p->x.fw_upgrade_cmd;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild TrafficSignalControllerRequest_membs[] =
{
	{ Dz1Text("control"), Dz1Text("CrossControlInformation"), TrafficSignalControllerRequestPresent_control },
	{ Dz1Text("status"), Dz1Text("CrossIndicator"), TrafficSignalControllerRequestPresent_status },
	{ Dz1Text("detector"), Dz1Text("CrossIndicator"), TrafficSignalControllerRequestPresent_detector },
	{ Dz1Text("signal_phase_down"), Dz1Text("SignalPhaseInformationDownload"), TrafficSignalControllerRequestPresent_signal_phase_down },
	{ Dz1Text("signal_phase_up"), Dz1Text("CrossIndicator"), TrafficSignalControllerRequestPresent_signal_phase_up },
	{ Dz1Text("clock_down"), Dz1Text("ClockInformationDownload"), TrafficSignalControllerRequestPresent_clock_down },
	{ Dz1Text("clock_up"), Dz1Text("CrossIndicator"), TrafficSignalControllerRequestPresent_clock_up },
	{ Dz1Text("special_cmd"), Dz1Text("SpecialCommandInformation"), TrafficSignalControllerRequestPresent_special_cmd },
	{ Dz1Text("fw_upgrade_cmd"), Dz1Text("FirmwareUpgradeCommand"), TrafficSignalControllerRequestPresent_fw_upgrade_cmd },
	{ NULL, NULL, -1 }
};
// TrafficSignalControllerRequest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossStatusBasicInfo_OperationMode
static bool_t CrossStatusBasicInfo_OperationMode_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CrossStatusBasicInfo_OperationMode v = CrossStatusBasicInfo_OperationMode_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (CrossStatusBasicInfo_OperationMode)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = CrossStatusBasicInfo_OperationModeFromStr(tok->v)) == CrossStatusBasicInfo_OperationMode_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = CrossStatusBasicInfo_OperationMode_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t CrossStatusBasicInfo_OperationMode_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		CrossStatusBasicInfo_OperationMode v = *(CrossStatusBasicInfo_OperationMode *)obj;
		Dz1Str str_v = CrossStatusBasicInfo_OperationModeStr(v);
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
// CrossStatusBasicInfo_OperationMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossStatusBasicInfo_BlinkReason
static bool_t CrossStatusBasicInfo_BlinkReason_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CrossStatusBasicInfo_BlinkReason v = CrossStatusBasicInfo_BlinkReason_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (CrossStatusBasicInfo_BlinkReason)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = CrossStatusBasicInfo_BlinkReasonFromStr(tok->v)) == CrossStatusBasicInfo_BlinkReason_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = CrossStatusBasicInfo_BlinkReason_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t CrossStatusBasicInfo_BlinkReason_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		CrossStatusBasicInfo_BlinkReason v = *(CrossStatusBasicInfo_BlinkReason *)obj;
		Dz1Str str_v = CrossStatusBasicInfo_BlinkReasonStr(v);
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
// CrossStatusBasicInfo_BlinkReason
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossStatusBasicInfo
static bool_t CrossStatusBasicInfo_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CrossStatusBasicInfo *p = (CrossStatusBasicInfo *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->power_fail =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->comm_fail =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->lamp_oper =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->is_dual_ring =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->ppc_enabled =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->oper_mode =  *(CrossStatusBasicInfo_OperationMode *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->ring_a_phase =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->ring_a_step =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->ring_b_phase =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 9: p->ring_b_step =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 10: p->pannel_is_manual =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 11: p->pannel_manual_sw =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 12: p->pannel_blink_sw =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 13: p->pannel_light_out_sw =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 14: p->is_contradiction =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 15: p->is_light_out =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 16: p->is_blink =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 17: p->is_database =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 18: p->push_button_enable =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 19: p->blink_reason =  *(CrossStatusBasicInfo_BlinkReason *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 20: p->is_timed_left_signal =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 21: p->manual_enabled =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 22: p->conflict_enabled =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 23: p->is_door_opened =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 24: p->contradiction_lsu =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 25: p->contradiction_from_sw =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 26: p->contradiction_curcuit =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 27: p->pedestrian_lamp =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 28: p->push_button_pending =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 29: p->push_button_status =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 30: p->opt_board_status =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 31: p->period_counter =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 32: p->total_period =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 33: p->curr_period =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 34: p->period_offset =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 35: p->hold_phase =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 36: p->omit_phase =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 37: p->is_four_color_lamp =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 38: p->oper_map_id =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 39: p->jam_ctrl_enabled =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 40: p->jam_ctrl_mode =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 41: p->jam_term_early0 =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 42: p->jam_term_early1 =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 43: p->firmware_id =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 44: p->firmware_idx =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 45: p->database_status =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 46: p->ppc_control_status =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 47: p->ups_control_status =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 48: p->map_is_dirty =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 49: p->lock_installed =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 50: p->lock_is_locked =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 51: p->db_is_locked =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *CrossStatusBasicInfo_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	CrossStatusBasicInfo *p = (CrossStatusBasicInfo *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->power_fail;
	case 1: return &p->comm_fail;
	case 2: return &p->lamp_oper;
	case 3: return &p->is_dual_ring;
	case 4: return &p->ppc_enabled;
	case 5: return &p->oper_mode;
	case 6: return &p->ring_a_phase;
	case 7: return &p->ring_a_step;
	case 8: return &p->ring_b_phase;
	case 9: return &p->ring_b_step;
	case 10: return &p->pannel_is_manual;
	case 11: return &p->pannel_manual_sw;
	case 12: return &p->pannel_blink_sw;
	case 13: return &p->pannel_light_out_sw;
	case 14: return &p->is_contradiction;
	case 15: return &p->is_light_out;
	case 16: return &p->is_blink;
	case 17: return &p->is_database;
	case 18: return &p->push_button_enable;
	case 19: return &p->blink_reason;
	case 20: return &p->is_timed_left_signal;
	case 21: return &p->manual_enabled;
	case 22: return &p->conflict_enabled;
	case 23: return &p->is_door_opened;
	case 24: return &p->contradiction_lsu;
	case 25: return &p->contradiction_from_sw;
	case 26: return &p->contradiction_curcuit;
	case 27: return &p->pedestrian_lamp;
	case 28: return &p->push_button_pending;
	case 29: return &p->push_button_status;
	case 30: return &p->opt_board_status;
	case 31: return &p->period_counter;
	case 32: return &p->total_period;
	case 33: return &p->curr_period;
	case 34: return &p->period_offset;
	case 35: return &p->hold_phase;
	case 36: return &p->omit_phase;
	case 37: return &p->is_four_color_lamp;
	case 38: return &p->oper_map_id;
	case 39: return &p->jam_ctrl_enabled;
	case 40: return &p->jam_ctrl_mode;
	case 41: return &p->jam_term_early0;
	case 42: return &p->jam_term_early1;
	case 43: return &p->firmware_id;
	case 44: return &p->firmware_idx;
	case 45: return &p->database_status;
	case 46: return &p->ppc_control_status;
	case 47: return &p->ups_control_status;
	case 48: return &p->map_is_dirty;
	case 49: return &p->lock_installed;
	case 50: return &p->lock_is_locked;
	case 51: return &p->db_is_locked;
	default: return NULL;
	}
}

static Dz1JsonSpecChild CrossStatusBasicInfo_membs[] =
{
	{ Dz1Text("power_fail"), Dz1Text("bool_t"), 0 },
	{ Dz1Text("comm_fail"), Dz1Text("bool_t"), 1 },
	{ Dz1Text("lamp_oper"), Dz1Text("bool_t"), 2 },
	{ Dz1Text("is_dual_ring"), Dz1Text("bool_t"), 3 },
	{ Dz1Text("ppc_enabled"), Dz1Text("bool_t"), 4 },
	{ Dz1Text("oper_mode"), Dz1Text("CrossStatusBasicInfo_OperationMode"), 5 },
	{ Dz1Text("ring_a_phase"), Dz1Text("u8_t"), 6 },
	{ Dz1Text("ring_a_step"), Dz1Text("u8_t"), 7 },
	{ Dz1Text("ring_b_phase"), Dz1Text("u8_t"), 8 },
	{ Dz1Text("ring_b_step"), Dz1Text("u8_t"), 9 },
	{ Dz1Text("pannel_is_manual"), Dz1Text("bool_t"), 10 },
	{ Dz1Text("pannel_manual_sw"), Dz1Text("bool_t"), 11 },
	{ Dz1Text("pannel_blink_sw"), Dz1Text("bool_t"), 12 },
	{ Dz1Text("pannel_light_out_sw"), Dz1Text("bool_t"), 13 },
	{ Dz1Text("is_contradiction"), Dz1Text("bool_t"), 14 },
	{ Dz1Text("is_light_out"), Dz1Text("bool_t"), 15 },
	{ Dz1Text("is_blink"), Dz1Text("bool_t"), 16 },
	{ Dz1Text("is_database"), Dz1Text("bool_t"), 17 },
	{ Dz1Text("push_button_enable"), Dz1Text("bool_t"), 18 },
	{ Dz1Text("blink_reason"), Dz1Text("CrossStatusBasicInfo_BlinkReason"), 19 },
	{ Dz1Text("is_timed_left_signal"), Dz1Text("bool_t"), 20 },
	{ Dz1Text("manual_enabled"), Dz1Text("bool_t"), 21 },
	{ Dz1Text("conflict_enabled"), Dz1Text("bool_t"), 22 },
	{ Dz1Text("is_door_opened"), Dz1Text("bool_t"), 23 },
	{ Dz1Text("contradiction_lsu"), Dz1Text("u8_t"), 24 },
	{ Dz1Text("contradiction_from_sw"), Dz1Text("bool_t"), 25 },
	{ Dz1Text("contradiction_curcuit"), Dz1Text("u8_t"), 26 },
	{ Dz1Text("pedestrian_lamp"), Dz1Text("u8_t"), 27 },
	{ Dz1Text("push_button_pending"), Dz1Text("u8_t"), 28 },
	{ Dz1Text("push_button_status"), Dz1Text("u8_t"), 29 },
	{ Dz1Text("opt_board_status"), Dz1Text("u8_t"), 30 },
	{ Dz1Text("period_counter"), Dz1Text("u8_t"), 31 },
	{ Dz1Text("total_period"), Dz1Text("u8_t"), 32 },
	{ Dz1Text("curr_period"), Dz1Text("u8_t"), 33 },
	{ Dz1Text("period_offset"), Dz1Text("u8_t"), 34 },
	{ Dz1Text("hold_phase"), Dz1Text("u8_t"), 35 },
	{ Dz1Text("omit_phase"), Dz1Text("u8_t"), 36 },
	{ Dz1Text("is_four_color_lamp"), Dz1Text("bool_t"), 37 },
	{ Dz1Text("oper_map_id"), Dz1Text("u8_t"), 38 },
	{ Dz1Text("jam_ctrl_enabled"), Dz1Text("bool_t"), 39 },
	{ Dz1Text("jam_ctrl_mode"), Dz1Text("bool_t"), 40 },
	{ Dz1Text("jam_term_early0"), Dz1Text("bool_t"), 41 },
	{ Dz1Text("jam_term_early1"), Dz1Text("bool_t"), 42 },
	{ Dz1Text("firmware_id"), Dz1Text("u16_t"), 43 },
	{ Dz1Text("firmware_idx"), Dz1Text("u16_t"), 44 },
	{ Dz1Text("database_status"), Dz1Text("u8_t"), 45 },
	{ Dz1Text("ppc_control_status"), Dz1Text("u8_t"), 46 },
	{ Dz1Text("ups_control_status"), Dz1Text("u8_t"), 47 },
	{ Dz1Text("map_is_dirty"), Dz1Text("bool_t"), 48 },
	{ Dz1Text("lock_installed"), Dz1Text("bool_t"), 49 },
	{ Dz1Text("lock_is_locked"), Dz1Text("bool_t"), 50 },
	{ Dz1Text("db_is_locked"), Dz1Text("bool_t"), 51 },
	{ NULL, NULL, -1 }
};
// CrossStatusBasicInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Binary
// extern type
// Dz1Binary
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossStatusExtInfo_ContradictionReason
static bool_t CrossStatusExtInfo_ContradictionReason_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CrossStatusExtInfo_ContradictionReason v = CrossStatusExtInfo_ContradictionReason_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (CrossStatusExtInfo_ContradictionReason)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = CrossStatusExtInfo_ContradictionReasonFromStr(tok->v)) == CrossStatusExtInfo_ContradictionReason_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = CrossStatusExtInfo_ContradictionReason_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t CrossStatusExtInfo_ContradictionReason_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		CrossStatusExtInfo_ContradictionReason v = *(CrossStatusExtInfo_ContradictionReason *)obj;
		Dz1Str str_v = CrossStatusExtInfo_ContradictionReasonStr(v);
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
// CrossStatusExtInfo_ContradictionReason
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossStatusExtInfo_r27
static bool_t CrossStatusExtInfo_r27_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CrossStatusExtInfo_r27 *p = (CrossStatusExtInfo_r27 *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->type =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->ver =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: Dz1Binary_delAndSetNull(&p->ppc_data); p->ppc_data = (Dz1Binary *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: p->detector_status =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->mlc_slc_comm_fail =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->contradiction_slc =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->contradiction_prove =  *(CrossStatusExtInfo_ContradictionReason *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->contradiction_circuit =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->ring_a_phase =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 9: p->ring_a_step =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 10: p->ring_b_phase =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 11: p->ring_b_step =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *CrossStatusExtInfo_r27_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	CrossStatusExtInfo_r27 *p = (CrossStatusExtInfo_r27 *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->type;
	case 1: return &p->ver;
	case 2: return p->ppc_data;
	case 3: return &p->detector_status;
	case 4: return &p->mlc_slc_comm_fail;
	case 5: return &p->contradiction_slc;
	case 6: return &p->contradiction_prove;
	case 7: return &p->contradiction_circuit;
	case 8: return &p->ring_a_phase;
	case 9: return &p->ring_a_step;
	case 10: return &p->ring_b_phase;
	case 11: return &p->ring_b_step;
	default: return NULL;
	}
}

static Dz1JsonSpecChild CrossStatusExtInfo_r27_membs[] =
{
	{ Dz1Text("type"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("ver"), Dz1Text("u8_t"), 1 },
	{ Dz1Text("ppc_data"), Dz1Text("Dz1Binary"), 2 },
	{ Dz1Text("detector_status"), Dz1Text("u32_t"), 3 },
	{ Dz1Text("mlc_slc_comm_fail"), Dz1Text("u8_t"), 4 },
	{ Dz1Text("contradiction_slc"), Dz1Text("u8_t"), 5 },
	{ Dz1Text("contradiction_prove"), Dz1Text("CrossStatusExtInfo_ContradictionReason"), 6 },
	{ Dz1Text("contradiction_circuit"), Dz1Text("u8_t"), 7 },
	{ Dz1Text("ring_a_phase"), Dz1Text("u8_t"), 8 },
	{ Dz1Text("ring_a_step"), Dz1Text("u8_t"), 9 },
	{ Dz1Text("ring_b_phase"), Dz1Text("u8_t"), 10 },
	{ Dz1Text("ring_b_step"), Dz1Text("u8_t"), 11 },
	{ NULL, NULL, -1 }
};
// CrossStatusExtInfo_r27
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CrossStatusInformation
static bool_t CrossStatusInformation_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CrossStatusInformation *p = (CrossStatusInformation *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->cross_id =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: CrossStatusBasicInfo_delAndSetNull(&p->lc_status); p->lc_status = (CrossStatusBasicInfo *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: CrossStatusExtInfo_r27_delAndSetNull(&p->ex_status); p->ex_status = (CrossStatusExtInfo_r27 *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *CrossStatusInformation_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	CrossStatusInformation *p = (CrossStatusInformation *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->cross_id;
	case 1: return p->lc_status;
	case 2: return p->ex_status;
	default: return NULL;
	}
}

static Dz1JsonSpecChild CrossStatusInformation_membs[] =
{
	{ Dz1Text("cross_id"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("lc_status"), Dz1Text("CrossStatusBasicInfo"), 1 },
	{ Dz1Text("ex_status"), Dz1Text("CrossStatusExtInfo_r27"), 2 },
	{ NULL, NULL, -1 }
};
// CrossStatusInformation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DetectorInfoFlagMap
static bool_t DetectorInfoFlagMap_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	DetectorInfoFlagMap *p = (DetectorInfoFlagMap *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->bit6 =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->bit5 =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->bit4 =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->bit3 =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->bit2 =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->bit1 =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->bit0 =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *DetectorInfoFlagMap_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	DetectorInfoFlagMap *p = (DetectorInfoFlagMap *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->bit6;
	case 1: return &p->bit5;
	case 2: return &p->bit4;
	case 3: return &p->bit3;
	case 4: return &p->bit2;
	case 5: return &p->bit1;
	case 6: return &p->bit0;
	default: return NULL;
	}
}

static Dz1JsonSpecChild DetectorInfoFlagMap_membs[] =
{
	{ Dz1Text("bit6"), Dz1Text("bool_t"), 0 },
	{ Dz1Text("bit5"), Dz1Text("bool_t"), 1 },
	{ Dz1Text("bit4"), Dz1Text("bool_t"), 2 },
	{ Dz1Text("bit3"), Dz1Text("bool_t"), 3 },
	{ Dz1Text("bit2"), Dz1Text("bool_t"), 4 },
	{ Dz1Text("bit1"), Dz1Text("bool_t"), 5 },
	{ Dz1Text("bit0"), Dz1Text("bool_t"), 6 },
	{ NULL, NULL, -1 }
};
// DetectorInfoFlagMap
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DetectorInfoFlagMaps
static bool_t DetectorInfoFlagMaps_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	DetectorInfoFlagMaps *p = (DetectorInfoFlagMaps *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: DetectorInfoFlagMap_delAndSetNull(&p->detector1); p->detector1 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: DetectorInfoFlagMap_delAndSetNull(&p->detector2); p->detector2 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: DetectorInfoFlagMap_delAndSetNull(&p->detector3); p->detector3 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: DetectorInfoFlagMap_delAndSetNull(&p->detector4); p->detector4 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 4: DetectorInfoFlagMap_delAndSetNull(&p->detector5); p->detector5 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 5: DetectorInfoFlagMap_delAndSetNull(&p->detector6); p->detector6 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 6: DetectorInfoFlagMap_delAndSetNull(&p->detector7); p->detector7 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 7: DetectorInfoFlagMap_delAndSetNull(&p->detector8); p->detector8 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 8: DetectorInfoFlagMap_delAndSetNull(&p->detector9); p->detector9 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 9: DetectorInfoFlagMap_delAndSetNull(&p->detector10); p->detector10 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 10: DetectorInfoFlagMap_delAndSetNull(&p->detector11); p->detector11 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 11: DetectorInfoFlagMap_delAndSetNull(&p->detector12); p->detector12 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 12: DetectorInfoFlagMap_delAndSetNull(&p->detector13); p->detector13 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 13: DetectorInfoFlagMap_delAndSetNull(&p->detector14); p->detector14 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 14: DetectorInfoFlagMap_delAndSetNull(&p->detector15); p->detector15 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 15: DetectorInfoFlagMap_delAndSetNull(&p->detector16); p->detector16 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 16: DetectorInfoFlagMap_delAndSetNull(&p->detector17); p->detector17 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 17: DetectorInfoFlagMap_delAndSetNull(&p->detector18); p->detector18 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 18: DetectorInfoFlagMap_delAndSetNull(&p->detector19); p->detector19 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 19: DetectorInfoFlagMap_delAndSetNull(&p->detector20); p->detector20 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 20: DetectorInfoFlagMap_delAndSetNull(&p->detector21); p->detector21 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 21: DetectorInfoFlagMap_delAndSetNull(&p->detector22); p->detector22 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 22: DetectorInfoFlagMap_delAndSetNull(&p->detector23); p->detector23 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 23: DetectorInfoFlagMap_delAndSetNull(&p->detector24); p->detector24 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 24: DetectorInfoFlagMap_delAndSetNull(&p->detector25); p->detector25 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 25: DetectorInfoFlagMap_delAndSetNull(&p->detector26); p->detector26 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 26: DetectorInfoFlagMap_delAndSetNull(&p->detector27); p->detector27 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 27: DetectorInfoFlagMap_delAndSetNull(&p->detector28); p->detector28 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 28: DetectorInfoFlagMap_delAndSetNull(&p->detector29); p->detector29 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 29: DetectorInfoFlagMap_delAndSetNull(&p->detector30); p->detector30 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 30: DetectorInfoFlagMap_delAndSetNull(&p->detector31); p->detector31 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 31: DetectorInfoFlagMap_delAndSetNull(&p->detector32); p->detector32 = (DetectorInfoFlagMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *DetectorInfoFlagMaps_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	DetectorInfoFlagMaps *p = (DetectorInfoFlagMaps *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->detector1;
	case 1: return p->detector2;
	case 2: return p->detector3;
	case 3: return p->detector4;
	case 4: return p->detector5;
	case 5: return p->detector6;
	case 6: return p->detector7;
	case 7: return p->detector8;
	case 8: return p->detector9;
	case 9: return p->detector10;
	case 10: return p->detector11;
	case 11: return p->detector12;
	case 12: return p->detector13;
	case 13: return p->detector14;
	case 14: return p->detector15;
	case 15: return p->detector16;
	case 16: return p->detector17;
	case 17: return p->detector18;
	case 18: return p->detector19;
	case 19: return p->detector20;
	case 20: return p->detector21;
	case 21: return p->detector22;
	case 22: return p->detector23;
	case 23: return p->detector24;
	case 24: return p->detector25;
	case 25: return p->detector26;
	case 26: return p->detector27;
	case 27: return p->detector28;
	case 28: return p->detector29;
	case 29: return p->detector30;
	case 30: return p->detector31;
	case 31: return p->detector32;
	default: return NULL;
	}
}

static Dz1JsonSpecChild DetectorInfoFlagMaps_membs[] =
{
	{ Dz1Text("detector1"), Dz1Text("DetectorInfoFlagMap"), 0 },
	{ Dz1Text("detector2"), Dz1Text("DetectorInfoFlagMap"), 1 },
	{ Dz1Text("detector3"), Dz1Text("DetectorInfoFlagMap"), 2 },
	{ Dz1Text("detector4"), Dz1Text("DetectorInfoFlagMap"), 3 },
	{ Dz1Text("detector5"), Dz1Text("DetectorInfoFlagMap"), 4 },
	{ Dz1Text("detector6"), Dz1Text("DetectorInfoFlagMap"), 5 },
	{ Dz1Text("detector7"), Dz1Text("DetectorInfoFlagMap"), 6 },
	{ Dz1Text("detector8"), Dz1Text("DetectorInfoFlagMap"), 7 },
	{ Dz1Text("detector9"), Dz1Text("DetectorInfoFlagMap"), 8 },
	{ Dz1Text("detector10"), Dz1Text("DetectorInfoFlagMap"), 9 },
	{ Dz1Text("detector11"), Dz1Text("DetectorInfoFlagMap"), 10 },
	{ Dz1Text("detector12"), Dz1Text("DetectorInfoFlagMap"), 11 },
	{ Dz1Text("detector13"), Dz1Text("DetectorInfoFlagMap"), 12 },
	{ Dz1Text("detector14"), Dz1Text("DetectorInfoFlagMap"), 13 },
	{ Dz1Text("detector15"), Dz1Text("DetectorInfoFlagMap"), 14 },
	{ Dz1Text("detector16"), Dz1Text("DetectorInfoFlagMap"), 15 },
	{ Dz1Text("detector17"), Dz1Text("DetectorInfoFlagMap"), 16 },
	{ Dz1Text("detector18"), Dz1Text("DetectorInfoFlagMap"), 17 },
	{ Dz1Text("detector19"), Dz1Text("DetectorInfoFlagMap"), 18 },
	{ Dz1Text("detector20"), Dz1Text("DetectorInfoFlagMap"), 19 },
	{ Dz1Text("detector21"), Dz1Text("DetectorInfoFlagMap"), 20 },
	{ Dz1Text("detector22"), Dz1Text("DetectorInfoFlagMap"), 21 },
	{ Dz1Text("detector23"), Dz1Text("DetectorInfoFlagMap"), 22 },
	{ Dz1Text("detector24"), Dz1Text("DetectorInfoFlagMap"), 23 },
	{ Dz1Text("detector25"), Dz1Text("DetectorInfoFlagMap"), 24 },
	{ Dz1Text("detector26"), Dz1Text("DetectorInfoFlagMap"), 25 },
	{ Dz1Text("detector27"), Dz1Text("DetectorInfoFlagMap"), 26 },
	{ Dz1Text("detector28"), Dz1Text("DetectorInfoFlagMap"), 27 },
	{ Dz1Text("detector29"), Dz1Text("DetectorInfoFlagMap"), 28 },
	{ Dz1Text("detector30"), Dz1Text("DetectorInfoFlagMap"), 29 },
	{ Dz1Text("detector31"), Dz1Text("DetectorInfoFlagMap"), 30 },
	{ Dz1Text("detector32"), Dz1Text("DetectorInfoFlagMap"), 31 },
	{ NULL, NULL, -1 }
};
// DetectorInfoFlagMaps
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DetectorInfoValueMap
static bool_t DetectorInfoValueMap_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	DetectorInfoValueMap *p = (DetectorInfoValueMap *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->detector1 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->detector2 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->detector3 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->detector4 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->detector5 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->detector6 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: p->detector7 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: p->detector8 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 8: p->detector9 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 9: p->detector10 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 10: p->detector11 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 11: p->detector12 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 12: p->detector13 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 13: p->detector14 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 14: p->detector15 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 15: p->detector16 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 16: p->detector17 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 17: p->detector18 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 18: p->detector19 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 19: p->detector20 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 20: p->detector21 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 21: p->detector22 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 22: p->detector23 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 23: p->detector24 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 24: p->detector25 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 25: p->detector26 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 26: p->detector27 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 27: p->detector28 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 28: p->detector29 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 29: p->detector30 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 30: p->detector31 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 31: p->detector32 =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *DetectorInfoValueMap_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	DetectorInfoValueMap *p = (DetectorInfoValueMap *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->detector1;
	case 1: return &p->detector2;
	case 2: return &p->detector3;
	case 3: return &p->detector4;
	case 4: return &p->detector5;
	case 5: return &p->detector6;
	case 6: return &p->detector7;
	case 7: return &p->detector8;
	case 8: return &p->detector9;
	case 9: return &p->detector10;
	case 10: return &p->detector11;
	case 11: return &p->detector12;
	case 12: return &p->detector13;
	case 13: return &p->detector14;
	case 14: return &p->detector15;
	case 15: return &p->detector16;
	case 16: return &p->detector17;
	case 17: return &p->detector18;
	case 18: return &p->detector19;
	case 19: return &p->detector20;
	case 20: return &p->detector21;
	case 21: return &p->detector22;
	case 22: return &p->detector23;
	case 23: return &p->detector24;
	case 24: return &p->detector25;
	case 25: return &p->detector26;
	case 26: return &p->detector27;
	case 27: return &p->detector28;
	case 28: return &p->detector29;
	case 29: return &p->detector30;
	case 30: return &p->detector31;
	case 31: return &p->detector32;
	default: return NULL;
	}
}

static Dz1JsonSpecChild DetectorInfoValueMap_membs[] =
{
	{ Dz1Text("detector1"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("detector2"), Dz1Text("u8_t"), 1 },
	{ Dz1Text("detector3"), Dz1Text("u8_t"), 2 },
	{ Dz1Text("detector4"), Dz1Text("u8_t"), 3 },
	{ Dz1Text("detector5"), Dz1Text("u8_t"), 4 },
	{ Dz1Text("detector6"), Dz1Text("u8_t"), 5 },
	{ Dz1Text("detector7"), Dz1Text("u8_t"), 6 },
	{ Dz1Text("detector8"), Dz1Text("u8_t"), 7 },
	{ Dz1Text("detector9"), Dz1Text("u8_t"), 8 },
	{ Dz1Text("detector10"), Dz1Text("u8_t"), 9 },
	{ Dz1Text("detector11"), Dz1Text("u8_t"), 10 },
	{ Dz1Text("detector12"), Dz1Text("u8_t"), 11 },
	{ Dz1Text("detector13"), Dz1Text("u8_t"), 12 },
	{ Dz1Text("detector14"), Dz1Text("u8_t"), 13 },
	{ Dz1Text("detector15"), Dz1Text("u8_t"), 14 },
	{ Dz1Text("detector16"), Dz1Text("u8_t"), 15 },
	{ Dz1Text("detector17"), Dz1Text("u8_t"), 16 },
	{ Dz1Text("detector18"), Dz1Text("u8_t"), 17 },
	{ Dz1Text("detector19"), Dz1Text("u8_t"), 18 },
	{ Dz1Text("detector20"), Dz1Text("u8_t"), 19 },
	{ Dz1Text("detector21"), Dz1Text("u8_t"), 20 },
	{ Dz1Text("detector22"), Dz1Text("u8_t"), 21 },
	{ Dz1Text("detector23"), Dz1Text("u8_t"), 22 },
	{ Dz1Text("detector24"), Dz1Text("u8_t"), 23 },
	{ Dz1Text("detector25"), Dz1Text("u8_t"), 24 },
	{ Dz1Text("detector26"), Dz1Text("u8_t"), 25 },
	{ Dz1Text("detector27"), Dz1Text("u8_t"), 26 },
	{ Dz1Text("detector28"), Dz1Text("u8_t"), 27 },
	{ Dz1Text("detector29"), Dz1Text("u8_t"), 28 },
	{ Dz1Text("detector30"), Dz1Text("u8_t"), 29 },
	{ Dz1Text("detector31"), Dz1Text("u8_t"), 30 },
	{ Dz1Text("detector32"), Dz1Text("u8_t"), 31 },
	{ NULL, NULL, -1 }
};
// DetectorInfoValueMap
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DetectorInfo
static bool_t DetectorInfo_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	DetectorInfo *p = (DetectorInfo *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: DetectorInfoFlagMaps_delAndSetNull(&p->detector_info_flags); p->detector_info_flags = (DetectorInfoFlagMaps *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: DetectorInfoValueMap_delAndSetNull(&p->detector_not_occupy_times); p->detector_not_occupy_times = (DetectorInfoValueMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: DetectorInfoValueMap_delAndSetNull(&p->detector_occupy_times); p->detector_occupy_times = (DetectorInfoValueMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: DetectorInfoValueMap_delAndSetNull(&p->detector_traffic_volumes); p->detector_traffic_volumes = (DetectorInfoValueMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 4: DetectorInfoValueMap_delAndSetNull(&p->detector_traffic_saturations); p->detector_traffic_saturations = (DetectorInfoValueMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 5: DetectorInfoValueMap_delAndSetNull(&p->detector_saturation_flow_rate_per_speeds); p->detector_saturation_flow_rate_per_speeds = (DetectorInfoValueMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 6: DetectorInfoValueMap_delAndSetNull(&p->detector_saturation_not_ocuppy_time); p->detector_saturation_not_ocuppy_time = (DetectorInfoValueMap *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *DetectorInfo_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	DetectorInfo *p = (DetectorInfo *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->detector_info_flags;
	case 1: return p->detector_not_occupy_times;
	case 2: return p->detector_occupy_times;
	case 3: return p->detector_traffic_volumes;
	case 4: return p->detector_traffic_saturations;
	case 5: return p->detector_saturation_flow_rate_per_speeds;
	case 6: return p->detector_saturation_not_ocuppy_time;
	default: return NULL;
	}
}

static Dz1JsonSpecChild DetectorInfo_membs[] =
{
	{ Dz1Text("detector_info_flags"), Dz1Text("DetectorInfoFlagMaps"), 0 },
	{ Dz1Text("detector_not_occupy_times"), Dz1Text("DetectorInfoValueMap"), 1 },
	{ Dz1Text("detector_occupy_times"), Dz1Text("DetectorInfoValueMap"), 2 },
	{ Dz1Text("detector_traffic_volumes"), Dz1Text("DetectorInfoValueMap"), 3 },
	{ Dz1Text("detector_traffic_saturations"), Dz1Text("DetectorInfoValueMap"), 4 },
	{ Dz1Text("detector_saturation_flow_rate_per_speeds"), Dz1Text("DetectorInfoValueMap"), 5 },
	{ Dz1Text("detector_saturation_not_ocuppy_time"), Dz1Text("DetectorInfoValueMap"), 6 },
	{ NULL, NULL, -1 }
};
// DetectorInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DetectorInformation
static bool_t DetectorInformation_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	DetectorInformation *p = (DetectorInformation *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->cross_id =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: DetectorInfo_delAndSetNull(&p->detector_info); p->detector_info = (DetectorInfo *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *DetectorInformation_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	DetectorInformation *p = (DetectorInformation *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->cross_id;
	case 1: return p->detector_info;
	default: return NULL;
	}
}

static Dz1JsonSpecChild DetectorInformation_membs[] =
{
	{ Dz1Text("cross_id"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("detector_info"), Dz1Text("DetectorInfo"), 1 },
	{ NULL, NULL, -1 }
};
// DetectorInformation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SignalPhaseInfoUpPPCControl
static bool_t SignalPhaseInfoUpPPCControl_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SignalPhaseInfoUpPPCControl *p = (SignalPhaseInfoUpPPCControl *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->ppc_blink_time =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->ppc_all_red_time =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->ppc_priority_signal =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *SignalPhaseInfoUpPPCControl_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	SignalPhaseInfoUpPPCControl *p = (SignalPhaseInfoUpPPCControl *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->ppc_blink_time;
	case 1: return &p->ppc_all_red_time;
	case 2: return &p->ppc_priority_signal;
	default: return NULL;
	}
}

static Dz1JsonSpecChild SignalPhaseInfoUpPPCControl_membs[] =
{
	{ Dz1Text("ppc_blink_time"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("ppc_all_red_time"), Dz1Text("u8_t"), 1 },
	{ Dz1Text("ppc_priority_signal"), Dz1Text("u8_t"), 2 },
	{ NULL, NULL, -1 }
};
// SignalPhaseInfoUpPPCControl
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SignalPhaseInfoUp
static bool_t SignalPhaseInfoUp_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SignalPhaseInfoUp *p = (SignalPhaseInfoUp *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: SignalPhaseInfoPeriodicOperationTime_delAndSetNull(&p->operation_time); p->operation_time = (SignalPhaseInfoPeriodicOperationTime *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: SignalPhaseInfoPeriodicOperationTime_delAndSetNull(&p->pedestrianoperation_time); p->pedestrianoperation_time = (SignalPhaseInfoPeriodicOperationTime *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: SignalPhaseInfoUpPPCControl_delAndSetNull(&p->ppc_control); p->ppc_control = (SignalPhaseInfoUpPPCControl *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *SignalPhaseInfoUp_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	SignalPhaseInfoUp *p = (SignalPhaseInfoUp *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->operation_time;
	case 1: return p->pedestrianoperation_time;
	case 2: return p->ppc_control;
	default: return NULL;
	}
}

static Dz1JsonSpecChild SignalPhaseInfoUp_membs[] =
{
	{ Dz1Text("operation_time"), Dz1Text("SignalPhaseInfoPeriodicOperationTime"), 0 },
	{ Dz1Text("pedestrianoperation_time"), Dz1Text("SignalPhaseInfoPeriodicOperationTime"), 1 },
	{ Dz1Text("ppc_control"), Dz1Text("SignalPhaseInfoUpPPCControl"), 2 },
	{ NULL, NULL, -1 }
};
// SignalPhaseInfoUp
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SignalPhaseInformationUpload
static bool_t SignalPhaseInformationUpload_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SignalPhaseInformationUpload *p = (SignalPhaseInformationUpload *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->cross_id =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: SignalPhaseInfoUp_delAndSetNull(&p->signal_phase_info_up); p->signal_phase_info_up = (SignalPhaseInfoUp *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *SignalPhaseInformationUpload_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	SignalPhaseInformationUpload *p = (SignalPhaseInformationUpload *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->cross_id;
	case 1: return p->signal_phase_info_up;
	default: return NULL;
	}
}

static Dz1JsonSpecChild SignalPhaseInformationUpload_membs[] =
{
	{ Dz1Text("cross_id"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("signal_phase_info_up"), Dz1Text("SignalPhaseInfoUp"), 1 },
	{ NULL, NULL, -1 }
};
// SignalPhaseInformationUpload
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ClockInformationUpload
static bool_t ClockInformationUpload_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ClockInformationUpload *p = (ClockInformationUpload *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->cross_id =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: ClockInfo_delAndSetNull(&p->clock_info_up); p->clock_info_up = (ClockInfo *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *ClockInformationUpload_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	ClockInformationUpload *p = (ClockInformationUpload *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->cross_id;
	case 1: return p->clock_info_up;
	default: return NULL;
	}
}

static Dz1JsonSpecChild ClockInformationUpload_membs[] =
{
	{ Dz1Text("cross_id"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("clock_info_up"), Dz1Text("ClockInfo"), 1 },
	{ NULL, NULL, -1 }
};
// ClockInformationUpload
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandPPCNumberList_is_emergency
static bool_t SpecialCommandPPCNumberList_is_emergency_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SpecialCommandPPCNumberList_is_emergency *p = (SpecialCommandPPCNumberList_is_emergency *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->is_emergency =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *SpecialCommandPPCNumberList_is_emergency_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	SpecialCommandPPCNumberList_is_emergency *p = (SpecialCommandPPCNumberList_is_emergency *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->is_emergency;
	default: return NULL;
	}
}

static Dz1JsonSpecChild SpecialCommandPPCNumberList_is_emergency_membs[] =
{
	{ Dz1Text("is_emergency"), Dz1Text("bool_t"), 0 },
	{ NULL, NULL, -1 }
};
// SpecialCommandPPCNumberList_is_emergency
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandPPCNumberList_org_code
static bool_t SpecialCommandPPCNumberList_org_code_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SpecialCommandPPCNumberList_org_code *p = (SpecialCommandPPCNumberList_org_code *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->org_code =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *SpecialCommandPPCNumberList_org_code_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	SpecialCommandPPCNumberList_org_code *p = (SpecialCommandPPCNumberList_org_code *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->org_code;
	default: return NULL;
	}
}

static Dz1JsonSpecChild SpecialCommandPPCNumberList_org_code_membs[] =
{
	{ Dz1Text("org_code"), Dz1Text("u8_t"), 0 },
	{ NULL, NULL, -1 }
};
// SpecialCommandPPCNumberList_org_code
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandPPCNumberList_org_code_num
static bool_t SpecialCommandPPCNumberList_org_code_num_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SpecialCommandPPCNumberList_org_code_num *p = (SpecialCommandPPCNumberList_org_code_num *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->org_code_num =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *SpecialCommandPPCNumberList_org_code_num_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	SpecialCommandPPCNumberList_org_code_num *p = (SpecialCommandPPCNumberList_org_code_num *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->org_code_num;
	default: return NULL;
	}
}

static Dz1JsonSpecChild SpecialCommandPPCNumberList_org_code_num_membs[] =
{
	{ Dz1Text("org_code_num"), Dz1Text("u8_t"), 0 },
	{ NULL, NULL, -1 }
};
// SpecialCommandPPCNumberList_org_code_num
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandPPCNumberList_org_code_type
static bool_t SpecialCommandPPCNumberList_org_code_type_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SpecialCommandPPCNumberList_org_code_type *p = (SpecialCommandPPCNumberList_org_code_type *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->org_code_type =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *SpecialCommandPPCNumberList_org_code_type_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	SpecialCommandPPCNumberList_org_code_type *p = (SpecialCommandPPCNumberList_org_code_type *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->org_code_type;
	default: return NULL;
	}
}

static Dz1JsonSpecChild SpecialCommandPPCNumberList_org_code_type_membs[] =
{
	{ Dz1Text("org_code_type"), Dz1Text("u32_t"), 0 },
	{ NULL, NULL, -1 }
};
// SpecialCommandPPCNumberList_org_code_type
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandPPCVehicleProperties
static bool_t SpecialCommandPPCVehicleProperties_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SpecialCommandPPCVehicleProperties *dst = (SpecialCommandPPCVehicleProperties *)dst_ptr;
	SpecialCommandPPCVehicleProperty *node = NULL;
	if (dst == NULL || var == NULL || (node = (SpecialCommandPPCVehicleProperty *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t SpecialCommandPPCVehicleProperties_cnt(void *ptr)
{
	u32_t ret = 0;
	SpecialCommandPPCVehicleProperties *list = (SpecialCommandPPCVehicleProperties *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error SpecialCommandPPCVehicleProperties_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	SpecialCommandPPCVehicleProperties *list = (SpecialCommandPPCVehicleProperties *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// SpecialCommandPPCVehicleProperties
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandPPCNumberList
static bool_t SpecialCommandPPCNumberList_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SpecialCommandPPCNumberList *p = (SpecialCommandPPCNumberList *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: SpecialCommandPPCNumberList_is_emergency_delAndSetNull(&p->is_emergency); p->is_emergency = (SpecialCommandPPCNumberList_is_emergency *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 1: SpecialCommandPPCNumberList_org_code_delAndSetNull(&p->org_code); p->org_code = (SpecialCommandPPCNumberList_org_code *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 2: SpecialCommandPPCNumberList_org_code_num_delAndSetNull(&p->org_code_num); p->org_code_num = (SpecialCommandPPCNumberList_org_code_num *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 3: SpecialCommandPPCNumberList_org_code_type_delAndSetNull(&p->org_code_type); p->org_code_type = (SpecialCommandPPCNumberList_org_code_type *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 4: SpecialCommandPPCVehicleProperties_delAndSetNull(&p->vehicle_properties); p->vehicle_properties = (SpecialCommandPPCVehicleProperties *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *SpecialCommandPPCNumberList_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	SpecialCommandPPCNumberList *p = (SpecialCommandPPCNumberList *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return p->is_emergency;
	case 1: return p->org_code;
	case 2: return p->org_code_num;
	case 3: return p->org_code_type;
	case 4: return p->vehicle_properties;
	default: return NULL;
	}
}

static Dz1JsonSpecChild SpecialCommandPPCNumberList_membs[] =
{
	{ Dz1Text("is_emergency"), Dz1Text("SpecialCommandPPCNumberList_is_emergency"), 0 },
	{ Dz1Text("org_code"), Dz1Text("SpecialCommandPPCNumberList_org_code"), 1 },
	{ Dz1Text("org_code_num"), Dz1Text("SpecialCommandPPCNumberList_org_code_num"), 2 },
	{ Dz1Text("org_code_type"), Dz1Text("SpecialCommandPPCNumberList_org_code_type"), 3 },
	{ Dz1Text("vehicle_properties"), Dz1Text("SpecialCommandPPCVehicleProperties"), 4 },
	{ NULL, NULL, -1 }
};
// SpecialCommandPPCNumberList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SpecialCommandInformationResponse
static bool_t SpecialCommandInformationResponse_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	SpecialCommandInformationResponse *p = (SpecialCommandInformationResponse *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->cross_id =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: SpecialCommandPPCNumberList_delAndSetNull(&p->ppc_register_num_list); p->ppc_register_num_list = (SpecialCommandPPCNumberList *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *SpecialCommandInformationResponse_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	SpecialCommandInformationResponse *p = (SpecialCommandInformationResponse *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->cross_id;
	case 1: return p->ppc_register_num_list;
	default: return NULL;
	}
}

static Dz1JsonSpecChild SpecialCommandInformationResponse_membs[] =
{
	{ Dz1Text("cross_id"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("ppc_register_num_list"), Dz1Text("SpecialCommandPPCNumberList"), 1 },
	{ NULL, NULL, -1 }
};
// SpecialCommandInformationResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// FirmwareUpgradeErrorCode
static bool_t FirmwareUpgradeErrorCode_load(struct Dz1JsonVarBind *dst_obj, Dz1JsonToken *tok, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	FirmwareUpgradeErrorCode v = FirmwareUpgradeErrorCode_max;
	switch(tok->t)
	{
	case Dz1JsonTokenType_number:
		v = (FirmwareUpgradeErrorCode)Dz1StrTo32(tok->v);
		break;
	case Dz1JsonTokenType_string:
		if ((v = FirmwareUpgradeErrorCodeFromStr(tok->v)) == FirmwareUpgradeErrorCode_max) ERR_SET_OUT_RET(errp, EPERM, FALSE);
		break;
	default: ERR_SET_RET(errp, EPERM, FALSE);
	}

	if ((dst_obj->data = FirmwareUpgradeErrorCode_new(&v, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t FirmwareUpgradeErrorCode_stringify(void *obj, Dz1ElasticBuf *buf, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (obj == NULL)
	{
		if (Dz1JsonUtil_stringify_null(buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		FirmwareUpgradeErrorCode v = *(FirmwareUpgradeErrorCode *)obj;
		Dz1Str str_v = FirmwareUpgradeErrorCodeStr(v);
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
// FirmwareUpgradeErrorCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// FirmwareUpgradeError
static bool_t FirmwareUpgradeError_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	FirmwareUpgradeError *p = (FirmwareUpgradeError *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->code =  *(FirmwareUpgradeErrorCode *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *FirmwareUpgradeError_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	FirmwareUpgradeError *p = (FirmwareUpgradeError *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->code;
	default: return NULL;
	}
}

static Dz1JsonSpecChild FirmwareUpgradeError_membs[] =
{
	{ Dz1Text("code"), Dz1Text("FirmwareUpgradeErrorCode"), 0 },
	{ NULL, NULL, -1 }
};
// FirmwareUpgradeError
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// FirmwareUpgradeResponse
static bool_t FirmwareUpgradeResponse_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	FirmwareUpgradeResponse *p = (FirmwareUpgradeResponse *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->cross_id =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: FirmwareUpgradeError_delAndSetNull(&p->error); p->error = (FirmwareUpgradeError *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *FirmwareUpgradeResponse_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	FirmwareUpgradeResponse *p = (FirmwareUpgradeResponse *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->cross_id;
	case 1: return p->error;
	default: return NULL;
	}
}

static Dz1JsonSpecChild FirmwareUpgradeResponse_membs[] =
{
	{ Dz1Text("cross_id"), Dz1Text("u8_t"), 0 },
	{ Dz1Text("error"), Dz1Text("FirmwareUpgradeError"), 1 },
	{ NULL, NULL, -1 }
};
// FirmwareUpgradeResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerResponse
static bool_t TrafficSignalControllerResponse_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TrafficSignalControllerResponse *p = (TrafficSignalControllerResponse *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case TrafficSignalControllerResponsePresent_control: CrossIndicator_delAndSetNull(&p->x.control); p->x.control =(CrossIndicator *)info->data; info->data = NULL; break;
	case TrafficSignalControllerResponsePresent_status: CrossStatusInformation_delAndSetNull(&p->x.status); p->x.status =(CrossStatusInformation *)info->data; info->data = NULL; break;
	case TrafficSignalControllerResponsePresent_detector: DetectorInformation_delAndSetNull(&p->x.detector); p->x.detector =(DetectorInformation *)info->data; info->data = NULL; break;
	case TrafficSignalControllerResponsePresent_signal_phase_down: CrossIndicator_delAndSetNull(&p->x.signal_phase_down); p->x.signal_phase_down =(CrossIndicator *)info->data; info->data = NULL; break;
	case TrafficSignalControllerResponsePresent_signal_phase_up: SignalPhaseInformationUpload_delAndSetNull(&p->x.signal_phase_up); p->x.signal_phase_up =(SignalPhaseInformationUpload *)info->data; info->data = NULL; break;
	case TrafficSignalControllerResponsePresent_clock_down: CrossIndicator_delAndSetNull(&p->x.clock_down); p->x.clock_down =(CrossIndicator *)info->data; info->data = NULL; break;
	case TrafficSignalControllerResponsePresent_clock_up: ClockInformationUpload_delAndSetNull(&p->x.clock_up); p->x.clock_up =(ClockInformationUpload *)info->data; info->data = NULL; break;
	case TrafficSignalControllerResponsePresent_special_cmd: SpecialCommandInformationResponse_delAndSetNull(&p->x.special_cmd); p->x.special_cmd =(SpecialCommandInformationResponse *)info->data; info->data = NULL; break;
	case TrafficSignalControllerResponsePresent_fw_upgrade_cmd: FirmwareUpgradeResponse_delAndSetNull(&p->x.fw_upgrade_cmd); p->x.fw_upgrade_cmd =(FirmwareUpgradeResponse *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (TrafficSignalControllerResponsePresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *TrafficSignalControllerResponse_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	TrafficSignalControllerResponse *p = (TrafficSignalControllerResponse *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case TrafficSignalControllerResponsePresent_control: return p->x.control;
		case TrafficSignalControllerResponsePresent_status: return p->x.status;
		case TrafficSignalControllerResponsePresent_detector: return p->x.detector;
		case TrafficSignalControllerResponsePresent_signal_phase_down: return p->x.signal_phase_down;
		case TrafficSignalControllerResponsePresent_signal_phase_up: return p->x.signal_phase_up;
		case TrafficSignalControllerResponsePresent_clock_down: return p->x.clock_down;
		case TrafficSignalControllerResponsePresent_clock_up: return p->x.clock_up;
		case TrafficSignalControllerResponsePresent_special_cmd: return p->x.special_cmd;
		case TrafficSignalControllerResponsePresent_fw_upgrade_cmd: return p->x.fw_upgrade_cmd;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild TrafficSignalControllerResponse_membs[] =
{
	{ Dz1Text("control"), Dz1Text("CrossIndicator"), TrafficSignalControllerResponsePresent_control },
	{ Dz1Text("status"), Dz1Text("CrossStatusInformation"), TrafficSignalControllerResponsePresent_status },
	{ Dz1Text("detector"), Dz1Text("DetectorInformation"), TrafficSignalControllerResponsePresent_detector },
	{ Dz1Text("signal_phase_down"), Dz1Text("CrossIndicator"), TrafficSignalControllerResponsePresent_signal_phase_down },
	{ Dz1Text("signal_phase_up"), Dz1Text("SignalPhaseInformationUpload"), TrafficSignalControllerResponsePresent_signal_phase_up },
	{ Dz1Text("clock_down"), Dz1Text("CrossIndicator"), TrafficSignalControllerResponsePresent_clock_down },
	{ Dz1Text("clock_up"), Dz1Text("ClockInformationUpload"), TrafficSignalControllerResponsePresent_clock_up },
	{ Dz1Text("special_cmd"), Dz1Text("SpecialCommandInformationResponse"), TrafficSignalControllerResponsePresent_special_cmd },
	{ Dz1Text("fw_upgrade_cmd"), Dz1Text("FirmwareUpgradeResponse"), TrafficSignalControllerResponsePresent_fw_upgrade_cmd },
	{ NULL, NULL, -1 }
};
// TrafficSignalControllerResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TrafficSignalControllerTestConfiguration
static bool_t TrafficSignalControllerTestConfiguration_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TrafficSignalControllerTestConfiguration *p = (TrafficSignalControllerTestConfiguration *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->port =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->test_data =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->cross_id =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: Dz1Str_delAndSetNull(&p->req_str); p->req_str = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *TrafficSignalControllerTestConfiguration_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	TrafficSignalControllerTestConfiguration *p = (TrafficSignalControllerTestConfiguration *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->port;
	case 1: return &p->test_data;
	case 2: return &p->cross_id;
	case 3: return p->req_str;
	default: return NULL;
	}
}

static Dz1JsonSpecChild TrafficSignalControllerTestConfiguration_membs[] =
{
	{ Dz1Text("port"), Dz1Text("u16_t"), 0 },
	{ Dz1Text("test_data"), Dz1Text("bool_t"), 1 },
	{ Dz1Text("cross_id"), Dz1Text("u8_t"), 2 },
	{ Dz1Text("req_str"), Dz1Text("Dz1Str"), 3 },
	{ NULL, NULL, -1 }
};
// TrafficSignalControllerTestConfiguration
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpec Initializer
bool_t TrafficSignalControllerTestMsgDef_initJsonSpec(Dz1JsonSpec *dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (0) { }
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("CrossControlRingLcCmd"), CrossControlRingLcCmd_gen, CrossControlRingLcCmd_del, CrossControlRingLcCmd_load, CrossControlRingLcCmd_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("CrossControlRingRcCmd"), CrossControlRingRcCmd_gen, CrossControlRingRcCmd_del, CrossControlRingRcCmd_load, CrossControlRingRcCmd_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("ClockInfoWeekIndex"), ClockInfoWeekIndex_gen, ClockInfoWeekIndex_del, ClockInfoWeekIndex_load, ClockInfoWeekIndex_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("CrossStatusBasicInfo_OperationMode"), CrossStatusBasicInfo_OperationMode_gen, CrossStatusBasicInfo_OperationMode_del, CrossStatusBasicInfo_OperationMode_load, CrossStatusBasicInfo_OperationMode_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("CrossStatusBasicInfo_BlinkReason"), CrossStatusBasicInfo_BlinkReason_gen, CrossStatusBasicInfo_BlinkReason_del, CrossStatusBasicInfo_BlinkReason_load, CrossStatusBasicInfo_BlinkReason_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("CrossStatusExtInfo_ContradictionReason"), CrossStatusExtInfo_ContradictionReason_gen, CrossStatusExtInfo_ContradictionReason_del, CrossStatusExtInfo_ContradictionReason_load, CrossStatusExtInfo_ContradictionReason_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JsonSpec_add_primitive(dst, Dz1Text("FirmwareUpgradeErrorCode"), FirmwareUpgradeErrorCode_gen, FirmwareUpgradeErrorCode_del, FirmwareUpgradeErrorCode_load, FirmwareUpgradeErrorCode_stringify)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("CrossControlSingleCmd"), CrossControlSingleCmd_gen, CrossControlSingleCmd_del, CrossControlSingleCmd_setChild, CrossControlSingleCmd_getChild, CrossControlSingleCmd_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("CrossControlRingLcDualCmd"), CrossControlRingLcDualCmd_gen, CrossControlRingLcDualCmd_del, CrossControlRingLcDualCmd_setChild, CrossControlRingLcDualCmd_getChild, CrossControlRingLcDualCmd_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("CrossControlRingRcDualCmd"), CrossControlRingRcDualCmd_gen, CrossControlRingRcDualCmd_del, CrossControlRingRcDualCmd_setChild, CrossControlRingRcDualCmd_getChild, CrossControlRingRcDualCmd_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("CrossControlDualCmd"), CrossControlDualCmd_gen, CrossControlDualCmd_del, CrossControlDualCmd_setChild, CrossControlDualCmd_getChild, CrossControlDualCmd_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("CrossControlCmd"), CrossControlCmd_gen, CrossControlCmd_del, CrossControlCmd_setChild, CrossControlCmd_getChild, CrossControlCmd_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("CrossControlInformation"), CrossControlInformation_gen, CrossControlInformation_del, CrossControlInformation_setChild, CrossControlInformation_getChild, CrossControlInformation_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("CrossIndicator"), CrossIndicator_gen, CrossIndicator_del, CrossIndicator_setChild, CrossIndicator_getChild, CrossIndicator_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("SignalPhaseInfoPeriodicOperationTime"), SignalPhaseInfoPeriodicOperationTime_gen, SignalPhaseInfoPeriodicOperationTime_del, SignalPhaseInfoPeriodicOperationTime_setChild, SignalPhaseInfoPeriodicOperationTime_getChild, SignalPhaseInfoPeriodicOperationTime_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("SignalPhaseInfoDownBasic"), SignalPhaseInfoDownBasic_gen, SignalPhaseInfoDownBasic_del, SignalPhaseInfoDownBasic_setChild, SignalPhaseInfoDownBasic_getChild, SignalPhaseInfoDownBasic_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("SignalPhaseInfoDown_r27"), SignalPhaseInfoDown_r27_gen, SignalPhaseInfoDown_r27_del, SignalPhaseInfoDown_r27_setChild, SignalPhaseInfoDown_r27_getChild, SignalPhaseInfoDown_r27_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("SignalPhaseInformationDownload"), SignalPhaseInformationDownload_gen, SignalPhaseInformationDownload_del, SignalPhaseInformationDownload_setChild, SignalPhaseInformationDownload_getChild, SignalPhaseInformationDownload_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ClockInfo"), ClockInfo_gen, ClockInfo_del, ClockInfo_setChild, ClockInfo_getChild, ClockInfo_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ClockInformationDownload"), ClockInformationDownload_gen, ClockInformationDownload_del, ClockInformationDownload_setChild, ClockInformationDownload_getChild, ClockInformationDownload_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("SpecialCommandPPCVehicleProperty"), SpecialCommandPPCVehicleProperty_gen, SpecialCommandPPCVehicleProperty_del, SpecialCommandPPCVehicleProperty_setChild, SpecialCommandPPCVehicleProperty_getChild, SpecialCommandPPCVehicleProperty_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("SpecialCommandInfoPPCControlManage"), SpecialCommandInfoPPCControlManage_gen, SpecialCommandInfoPPCControlManage_del, SpecialCommandInfoPPCControlManage_setChild, SpecialCommandInfoPPCControlManage_getChild, SpecialCommandInfoPPCControlManage_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("SpecialCommandInfo"), SpecialCommandInfo_gen, SpecialCommandInfo_del, SpecialCommandInfo_setChild, SpecialCommandInfo_getChild, SpecialCommandInfo_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("SpecialCommandInformation"), SpecialCommandInformation_gen, SpecialCommandInformation_del, SpecialCommandInformation_setChild, SpecialCommandInformation_getChild, SpecialCommandInformation_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("FirmwareUpgradeData"), FirmwareUpgradeData_gen, FirmwareUpgradeData_del, FirmwareUpgradeData_setChild, FirmwareUpgradeData_getChild, FirmwareUpgradeData_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("FirmwareUpgradeCommand"), FirmwareUpgradeCommand_gen, FirmwareUpgradeCommand_del, FirmwareUpgradeCommand_setChild, FirmwareUpgradeCommand_getChild, FirmwareUpgradeCommand_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("TrafficSignalControllerRequest"), TrafficSignalControllerRequest_gen, TrafficSignalControllerRequest_del, TrafficSignalControllerRequest_setChild, TrafficSignalControllerRequest_getChild, TrafficSignalControllerRequest_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("CrossStatusBasicInfo"), CrossStatusBasicInfo_gen, CrossStatusBasicInfo_del, CrossStatusBasicInfo_setChild, CrossStatusBasicInfo_getChild, CrossStatusBasicInfo_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("CrossStatusExtInfo_r27"), CrossStatusExtInfo_r27_gen, CrossStatusExtInfo_r27_del, CrossStatusExtInfo_r27_setChild, CrossStatusExtInfo_r27_getChild, CrossStatusExtInfo_r27_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("CrossStatusInformation"), CrossStatusInformation_gen, CrossStatusInformation_del, CrossStatusInformation_setChild, CrossStatusInformation_getChild, CrossStatusInformation_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("DetectorInfoFlagMap"), DetectorInfoFlagMap_gen, DetectorInfoFlagMap_del, DetectorInfoFlagMap_setChild, DetectorInfoFlagMap_getChild, DetectorInfoFlagMap_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("DetectorInfoFlagMaps"), DetectorInfoFlagMaps_gen, DetectorInfoFlagMaps_del, DetectorInfoFlagMaps_setChild, DetectorInfoFlagMaps_getChild, DetectorInfoFlagMaps_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("DetectorInfoValueMap"), DetectorInfoValueMap_gen, DetectorInfoValueMap_del, DetectorInfoValueMap_setChild, DetectorInfoValueMap_getChild, DetectorInfoValueMap_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("DetectorInfo"), DetectorInfo_gen, DetectorInfo_del, DetectorInfo_setChild, DetectorInfo_getChild, DetectorInfo_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("DetectorInformation"), DetectorInformation_gen, DetectorInformation_del, DetectorInformation_setChild, DetectorInformation_getChild, DetectorInformation_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("SignalPhaseInfoUpPPCControl"), SignalPhaseInfoUpPPCControl_gen, SignalPhaseInfoUpPPCControl_del, SignalPhaseInfoUpPPCControl_setChild, SignalPhaseInfoUpPPCControl_getChild, SignalPhaseInfoUpPPCControl_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("SignalPhaseInfoUp"), SignalPhaseInfoUp_gen, SignalPhaseInfoUp_del, SignalPhaseInfoUp_setChild, SignalPhaseInfoUp_getChild, SignalPhaseInfoUp_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("SignalPhaseInformationUpload"), SignalPhaseInformationUpload_gen, SignalPhaseInformationUpload_del, SignalPhaseInformationUpload_setChild, SignalPhaseInformationUpload_getChild, SignalPhaseInformationUpload_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("ClockInformationUpload"), ClockInformationUpload_gen, ClockInformationUpload_del, ClockInformationUpload_setChild, ClockInformationUpload_getChild, ClockInformationUpload_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("SpecialCommandPPCNumberList_is_emergency"), SpecialCommandPPCNumberList_is_emergency_gen, SpecialCommandPPCNumberList_is_emergency_del, SpecialCommandPPCNumberList_is_emergency_setChild, SpecialCommandPPCNumberList_is_emergency_getChild, SpecialCommandPPCNumberList_is_emergency_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("SpecialCommandPPCNumberList_org_code"), SpecialCommandPPCNumberList_org_code_gen, SpecialCommandPPCNumberList_org_code_del, SpecialCommandPPCNumberList_org_code_setChild, SpecialCommandPPCNumberList_org_code_getChild, SpecialCommandPPCNumberList_org_code_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("SpecialCommandPPCNumberList_org_code_num"), SpecialCommandPPCNumberList_org_code_num_gen, SpecialCommandPPCNumberList_org_code_num_del, SpecialCommandPPCNumberList_org_code_num_setChild, SpecialCommandPPCNumberList_org_code_num_getChild, SpecialCommandPPCNumberList_org_code_num_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("SpecialCommandPPCNumberList_org_code_type"), SpecialCommandPPCNumberList_org_code_type_gen, SpecialCommandPPCNumberList_org_code_type_del, SpecialCommandPPCNumberList_org_code_type_setChild, SpecialCommandPPCNumberList_org_code_type_getChild, SpecialCommandPPCNumberList_org_code_type_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("SpecialCommandPPCNumberList"), SpecialCommandPPCNumberList_gen, SpecialCommandPPCNumberList_del, SpecialCommandPPCNumberList_setChild, SpecialCommandPPCNumberList_getChild, SpecialCommandPPCNumberList_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("SpecialCommandInformationResponse"), SpecialCommandInformationResponse_gen, SpecialCommandInformationResponse_del, SpecialCommandInformationResponse_setChild, SpecialCommandInformationResponse_getChild, SpecialCommandInformationResponse_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("FirmwareUpgradeError"), FirmwareUpgradeError_gen, FirmwareUpgradeError_del, FirmwareUpgradeError_setChild, FirmwareUpgradeError_getChild, FirmwareUpgradeError_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("FirmwareUpgradeResponse"), FirmwareUpgradeResponse_gen, FirmwareUpgradeResponse_del, FirmwareUpgradeResponse_setChild, FirmwareUpgradeResponse_getChild, FirmwareUpgradeResponse_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("TrafficSignalControllerResponse"), TrafficSignalControllerResponse_gen, TrafficSignalControllerResponse_del, TrafficSignalControllerResponse_setChild, TrafficSignalControllerResponse_getChild, TrafficSignalControllerResponse_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("TrafficSignalControllerTestConfiguration"), TrafficSignalControllerTestConfiguration_gen, TrafficSignalControllerTestConfiguration_del, TrafficSignalControllerTestConfiguration_setChild, TrafficSignalControllerTestConfiguration_getChild, TrafficSignalControllerTestConfiguration_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("SpecialCommandPPCVehicleProperties"), SpecialCommandPPCVehicleProperties_gen, SpecialCommandPPCVehicleProperties_del, SpecialCommandPPCVehicleProperties_append, SpecialCommandPPCVehicleProperties_cnt, SpecialCommandPPCVehicleProperties_tlv, Dz1Text("SpecialCommandPPCVehicleProperty") )).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
Dz1JsonSpec *TrafficSignalControllerTestMsgDef_genJsonSpec(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonSpec *ret = Dz1JsonSpec_generate(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonSpec_delAndSetNull, (void *)&ret);

		if (TrafficSignalControllerTestMsgDef_initJsonSpec(ret, errp) == FALSE) ERR_OUT(errp);
		else if (Dz1JsonSpec_check(ret, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1JsonSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Dz1JsonSpec Initializer
////////////////////////////////////////////////////////////////////////////////

#include "TechnicalRegulation1DefJson.h"

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
// Dz1Binary
// extern type
// Dz1Binary
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
bool_t TechnicalRegulation1Def_initJsonSpec(Dz1JsonSpec *dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (0) { }
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
Dz1JsonSpec *TechnicalRegulation1Def_genJsonSpec(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonSpec *ret = Dz1JsonSpec_generate(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonSpec_delAndSetNull, (void *)&ret);

		if (TechnicalRegulation1Def_initJsonSpec(ret, errp) == FALSE) ERR_OUT(errp);
		else if (Dz1JsonSpec_check(ret, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1JsonSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Dz1JsonSpec Initializer
////////////////////////////////////////////////////////////////////////////////

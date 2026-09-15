////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "TechnicalRegulation1Def.h"

////////////////////////////////////////////////////////////////////////////////
// CurrentLinkStateEntry
CurrentLinkStateEntry *CurrentLinkStateEntry_new(Dz1Str link_id, 
												 u16_t speed_rate, 
												 u8_t tfdt_occupy_percent, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CurrentLinkStateEntry *__internal_ret = (CurrentLinkStateEntry *)Dz1Calloc(sizeof(CurrentLinkStateEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(CurrentLinkStateEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (link_id && (__internal_ret->link_id = Dz1Str_clone(link_id, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->speed_rate = speed_rate;
			__internal_ret->tfdt_occupy_percent = tfdt_occupy_percent;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CurrentLinkStateEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t CurrentLinkStateEntry_copy(CurrentLinkStateEntry *dst, CurrentLinkStateEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->link_id && (dst->link_id = Dz1Str_clone(src->link_id, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->speed_rate = src->speed_rate;
		dst->volume_rate = src->volume_rate;
		dst->density_rate = src->density_rate;
		dst->ttime_qty = src->ttime_qty;
		dst->delay_qty = src->delay_qty;
		dst->veh_q_len_qty = src->veh_q_len_qty;
		dst->tfdt_occupy_percent = src->tfdt_occupy_percent;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

CurrentLinkStateEntry *CurrentLinkStateEntry_clone(CurrentLinkStateEntry *src, Dz1Error *err)
{
	CurrentLinkStateEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (CurrentLinkStateEntry *)Dz1Calloc(sizeof(CurrentLinkStateEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(CurrentLinkStateEntry_delAndSetNull, (void *)&dst);
		if (CurrentLinkStateEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CurrentLinkStateEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void CurrentLinkStateEntry_purge(CurrentLinkStateEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->link_id);
}

void CurrentLinkStateEntry_del(CurrentLinkStateEntry *p)
{
	if (p == NULL) return;
	CurrentLinkStateEntry_purge(p);
	Dz1Free(p);
}

void CurrentLinkStateEntry_dump(CurrentLinkStateEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("link_id = ")); Dz1Str_dump(p->link_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("speed_rate = ")); Dz1u16_dump(&p->speed_rate, tab); 
		Dz1Thread_tprintf(tab, Dz1T("volume_rate = ")); Dz1u32_dump(&p->volume_rate, tab); 
		Dz1Thread_tprintf(tab, Dz1T("density_rate = ")); Dz1u16_dump(&p->density_rate, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ttime_qty = ")); Dz1u16_dump(&p->ttime_qty, tab); 
		Dz1Thread_tprintf(tab, Dz1T("delay_qty = ")); Dz1u16_dump(&p->delay_qty, tab); 
		Dz1Thread_tprintf(tab, Dz1T("veh_q_len_qty = ")); Dz1u32_dump(&p->veh_q_len_qty, tab); 
		Dz1Thread_tprintf(tab, Dz1T("tfdt_occupy_percent = ")); Dz1u8_dump(&p->tfdt_occupy_percent, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int CurrentLinkStateEntry_cmp(CurrentLinkStateEntry *a, CurrentLinkStateEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->link_id == NULL && b->link_id == NULL) ret = 0;
	else if (a->link_id == NULL /*&& b->link_id != NULL*/) ret = -1;
	else if (/*a->link_id != NULL &&*/ b->link_id == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->link_id, b->link_id)) != 0) { }
	return ret;
}
// CurrentLinkStateEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CurrentLinkStateList
static Dz1Error CurrentLinkStateList_add(CurrentLinkStateList *p, CurrentLinkStateEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static bool_t CurrentLinkStateList_remove(CurrentLinkStateList *p, CurrentLinkStateEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static CurrentLinkStateEntry *CurrentLinkStateList_extract(CurrentLinkStateList *p, CurrentLinkStateEntry *key)
{
	return (CurrentLinkStateEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct CurrentLinkStateListMkArrArg
{
	CurrentLinkStateEntry **arr;
	unsigned int idx;
} CurrentLinkStateListMkArrArg;

static Dz1Error _CurrentLinkStateList_get_array(void *ptr, CurrentLinkStateEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	CurrentLinkStateListMkArrArg *arg = (CurrentLinkStateListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static CurrentLinkStateEntry **CurrentLinkStateList_get_array(CurrentLinkStateList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	CurrentLinkStateEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (CurrentLinkStateEntry **)Dz1Calloc(sizeof(CurrentLinkStateEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		CurrentLinkStateListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _CurrentLinkStateList_get_array, (void *)&arg);
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

static Dz1Error CurrentLinkStateList_travelForward(CurrentLinkStateList *p, Dz1Error (*func)(void *ptr, CurrentLinkStateEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error CurrentLinkStateList_travelBackward(CurrentLinkStateList *p, Dz1Error (*func)(void *ptr, CurrentLinkStateEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static CurrentLinkStateEntry *CurrentLinkStateList_find(CurrentLinkStateList *p, CurrentLinkStateEntry *key)
{
	return (CurrentLinkStateEntry *)Dz1AATree_find(p->storage, key);
}

static CurrentLinkStateEntry *CurrentLinkStateList_getHead(CurrentLinkStateList *p)
{
	return (CurrentLinkStateEntry *)Dz1AATree_getHead(p->storage);
}

static unsigned int CurrentLinkStateList_count(CurrentLinkStateList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

CurrentLinkStateList *CurrentLinkStateList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CurrentLinkStateList *ret = (CurrentLinkStateList *)Dz1Calloc(sizeof(CurrentLinkStateList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(CurrentLinkStateList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)CurrentLinkStateEntry_cmp,
				(Dz1DelFunc)CurrentLinkStateEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = CurrentLinkStateList_count;
			ret->travel = CurrentLinkStateList_travelForward;
			ret->travelForward = CurrentLinkStateList_travelForward;
			ret->travelBackward = CurrentLinkStateList_travelBackward;
			ret->get_array = CurrentLinkStateList_get_array;
			ret->add = CurrentLinkStateList_add;
			ret->remove = CurrentLinkStateList_remove;
			ret->find = CurrentLinkStateList_find;
			ret->extract = CurrentLinkStateList_extract;
			ret->getHead = CurrentLinkStateList_getHead;
			ret->cmp = CurrentLinkStateEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (CurrentLinkStateList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _CurrentLinkStateList_clone(void *ptr, CurrentLinkStateEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	CurrentLinkStateList *p = (CurrentLinkStateList *)ptr;
	CurrentLinkStateEntry *cloned = CurrentLinkStateEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

CurrentLinkStateList *CurrentLinkStateList_clone(CurrentLinkStateList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	CurrentLinkStateList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = CurrentLinkStateList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(CurrentLinkStateList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_CurrentLinkStateList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (CurrentLinkStateList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void CurrentLinkStateList_purge(CurrentLinkStateList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void CurrentLinkStateList_del(CurrentLinkStateList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _CurrentLinkStateList_dump(void *ptr, CurrentLinkStateEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); CurrentLinkStateEntry_dump(p, tab);
	return err;
}

void CurrentLinkStateList_dump(CurrentLinkStateList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _CurrentLinkStateList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// CurrentLinkStateList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// EventIdentityEntry
EventIdentityEntry *EventIdentityEntry_new(Dz1Str node_id, 
										   Dz1Str link_id, 
										   Dz1Str loc_jurisdiction_name, 
										   Dz1Str loc_link_id, 
										   Dz1Str loc_node_id, 
										   Dz1Str loc_roadway_name, 
										   u8_t lanes_blocked_or_closed_num, 
										   u8_t *lanes_shoulder_block_code, 
										   Dz1Str start_time, 
										   Dz1Str end_time, 
										   u32_t time_duration, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	EventIdentityEntry *__internal_ret = (EventIdentityEntry *)Dz1Calloc(sizeof(EventIdentityEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(EventIdentityEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (node_id && (__internal_ret->node_id = Dz1Str_clone(node_id, errp)) == NULL) ERR_OUT(errp);
		else if (link_id && (__internal_ret->link_id = Dz1Str_clone(link_id, errp)) == NULL) ERR_OUT(errp);
		else if (loc_jurisdiction_name && (__internal_ret->loc_jurisdiction_name = Dz1Str_clone(loc_jurisdiction_name, errp)) == NULL) ERR_OUT(errp);
		else if (loc_link_id && (__internal_ret->loc_link_id = Dz1Str_clone(loc_link_id, errp)) == NULL) ERR_OUT(errp);
		else if (loc_node_id && (__internal_ret->loc_node_id = Dz1Str_clone(loc_node_id, errp)) == NULL) ERR_OUT(errp);
		else if (loc_roadway_name && (__internal_ret->loc_roadway_name = Dz1Str_clone(loc_roadway_name, errp)) == NULL) ERR_OUT(errp);
		else if (start_time && (__internal_ret->start_time = Dz1Str_clone(start_time, errp)) == NULL) ERR_OUT(errp);
		else if (end_time && (__internal_ret->end_time = Dz1Str_clone(end_time, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->lanes_blocked_or_closed_num = lanes_blocked_or_closed_num;
			__internal_ret->lanes_shoulder_block_code = lanes_shoulder_block_code;
			__internal_ret->time_duration = time_duration;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (EventIdentityEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t EventIdentityEntry_copy(EventIdentityEntry *dst, EventIdentityEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->node_id && (dst->node_id = Dz1Str_clone(src->node_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->link_id && (dst->link_id = Dz1Str_clone(src->link_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->loc_jurisdiction_name && (dst->loc_jurisdiction_name = Dz1Str_clone(src->loc_jurisdiction_name, errp)) == NULL) ERR_OUT(errp);
	else if (src->loc_link_id && (dst->loc_link_id = Dz1Str_clone(src->loc_link_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->loc_node_id && (dst->loc_node_id = Dz1Str_clone(src->loc_node_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->loc_roadway_name && (dst->loc_roadway_name = Dz1Str_clone(src->loc_roadway_name, errp)) == NULL) ERR_OUT(errp);
	else if (src->lanes_shoulder_block_code && (dst->lanes_shoulder_block_code = Dz1u8_clone(src->lanes_shoulder_block_code, errp)) == NULL) ERR_OUT(errp);
	else if (src->start_time && (dst->start_time = Dz1Str_clone(src->start_time, errp)) == NULL) ERR_OUT(errp);
	else if (src->end_time && (dst->end_time = Dz1Str_clone(src->end_time, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->identification_num = src->identification_num;
		dst->evnt_code = src->evnt_code;
		dst->special_evnt_code = src->special_evnt_code;
		dst->planned_road_closure_code = src->planned_road_closure_code;
		dst->lanes_blocked_or_closed_num = src->lanes_blocked_or_closed_num;
		dst->time_duration = src->time_duration;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

EventIdentityEntry *EventIdentityEntry_clone(EventIdentityEntry *src, Dz1Error *err)
{
	EventIdentityEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (EventIdentityEntry *)Dz1Calloc(sizeof(EventIdentityEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(EventIdentityEntry_delAndSetNull, (void *)&dst);
		if (EventIdentityEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (EventIdentityEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void EventIdentityEntry_purge(EventIdentityEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->node_id);
	Dz1Str_del(p->link_id);
	Dz1Str_del(p->loc_jurisdiction_name);
	Dz1Str_del(p->loc_link_id);
	Dz1Str_del(p->loc_node_id);
	Dz1Str_del(p->loc_roadway_name);
	Dz1u8_del(p->lanes_shoulder_block_code);
	Dz1Str_del(p->start_time);
	Dz1Str_del(p->end_time);
}

void EventIdentityEntry_del(EventIdentityEntry *p)
{
	if (p == NULL) return;
	EventIdentityEntry_purge(p);
	Dz1Free(p);
}

void EventIdentityEntry_dump(EventIdentityEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("node_id = ")); Dz1Str_dump(p->node_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("link_id = ")); Dz1Str_dump(p->link_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("identification_num = ")); Dz1u32_dump(&p->identification_num, tab); 
		Dz1Thread_tprintf(tab, Dz1T("loc_jurisdiction_name = ")); Dz1Str_dump(p->loc_jurisdiction_name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("loc_link_id = ")); Dz1Str_dump(p->loc_link_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("loc_node_id = ")); Dz1Str_dump(p->loc_node_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("loc_roadway_name = ")); Dz1Str_dump(p->loc_roadway_name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("evnt_code = ")); Dz1u8_dump(&p->evnt_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("special_evnt_code = ")); Dz1u8_dump(&p->special_evnt_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("planned_road_closure_code = ")); Dz1u8_dump(&p->planned_road_closure_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("lanes_blocked_or_closed_num = ")); Dz1u8_dump(&p->lanes_blocked_or_closed_num, tab); 
		Dz1Thread_tprintf(tab, Dz1T("lanes_shoulder_block_code = ")); Dz1u8_dump(p->lanes_shoulder_block_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("start_time = ")); Dz1Str_dump(p->start_time, tab); 
		Dz1Thread_tprintf(tab, Dz1T("end_time = ")); Dz1Str_dump(p->end_time, tab); 
		Dz1Thread_tprintf(tab, Dz1T("time_duration = ")); Dz1u32_dump(&p->time_duration, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int EventIdentityEntry_cmp(EventIdentityEntry *a, EventIdentityEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->node_id == NULL && b->node_id == NULL) ret = 0;
	else if (a->node_id == NULL /*&& b->node_id != NULL*/) ret = -1;
	else if (/*a->node_id != NULL &&*/ b->node_id == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->node_id, b->node_id)) != 0) { }
	else if (a->link_id == NULL && b->link_id == NULL) ret = 0;
	else if (a->link_id == NULL /*&& b->link_id != NULL*/) ret = -1;
	else if (/*a->link_id != NULL &&*/ b->link_id == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->link_id, b->link_id)) != 0) { }
	return ret;
}
// EventIdentityEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// EventIdentityList
static Dz1Error EventIdentityList_add(EventIdentityList *p, EventIdentityEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static bool_t EventIdentityList_remove(EventIdentityList *p, EventIdentityEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static EventIdentityEntry *EventIdentityList_extract(EventIdentityList *p, EventIdentityEntry *key)
{
	return (EventIdentityEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct EventIdentityListMkArrArg
{
	EventIdentityEntry **arr;
	unsigned int idx;
} EventIdentityListMkArrArg;

static Dz1Error _EventIdentityList_get_array(void *ptr, EventIdentityEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	EventIdentityListMkArrArg *arg = (EventIdentityListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static EventIdentityEntry **EventIdentityList_get_array(EventIdentityList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	EventIdentityEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (EventIdentityEntry **)Dz1Calloc(sizeof(EventIdentityEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		EventIdentityListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _EventIdentityList_get_array, (void *)&arg);
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

static Dz1Error EventIdentityList_travelForward(EventIdentityList *p, Dz1Error (*func)(void *ptr, EventIdentityEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error EventIdentityList_travelBackward(EventIdentityList *p, Dz1Error (*func)(void *ptr, EventIdentityEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static EventIdentityEntry *EventIdentityList_find(EventIdentityList *p, EventIdentityEntry *key)
{
	return (EventIdentityEntry *)Dz1AATree_find(p->storage, key);
}

static EventIdentityEntry *EventIdentityList_getHead(EventIdentityList *p)
{
	return (EventIdentityEntry *)Dz1AATree_getHead(p->storage);
}

static unsigned int EventIdentityList_count(EventIdentityList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

EventIdentityList *EventIdentityList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	EventIdentityList *ret = (EventIdentityList *)Dz1Calloc(sizeof(EventIdentityList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(EventIdentityList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)EventIdentityEntry_cmp,
				(Dz1DelFunc)EventIdentityEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = EventIdentityList_count;
			ret->travel = EventIdentityList_travelForward;
			ret->travelForward = EventIdentityList_travelForward;
			ret->travelBackward = EventIdentityList_travelBackward;
			ret->get_array = EventIdentityList_get_array;
			ret->add = EventIdentityList_add;
			ret->remove = EventIdentityList_remove;
			ret->find = EventIdentityList_find;
			ret->extract = EventIdentityList_extract;
			ret->getHead = EventIdentityList_getHead;
			ret->cmp = EventIdentityEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (EventIdentityList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _EventIdentityList_clone(void *ptr, EventIdentityEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	EventIdentityList *p = (EventIdentityList *)ptr;
	EventIdentityEntry *cloned = EventIdentityEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

EventIdentityList *EventIdentityList_clone(EventIdentityList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	EventIdentityList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = EventIdentityList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(EventIdentityList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_EventIdentityList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (EventIdentityList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void EventIdentityList_purge(EventIdentityList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void EventIdentityList_del(EventIdentityList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _EventIdentityList_dump(void *ptr, EventIdentityEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); EventIdentityEntry_dump(p, tab);
	return err;
}

void EventIdentityList_dump(EventIdentityList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _EventIdentityList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// EventIdentityList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// IncidentIdentityEntry
IncidentIdentityEntry *IncidentIdentityEntry_new(Dz1Str node_id, 
												 Dz1Str link_id, 
												 Dz1Str update_time, 
												 u8_t property_damage_code, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	IncidentIdentityEntry *__internal_ret = (IncidentIdentityEntry *)Dz1Calloc(sizeof(IncidentIdentityEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(IncidentIdentityEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (node_id && (__internal_ret->node_id = Dz1Str_clone(node_id, errp)) == NULL) ERR_OUT(errp);
		else if (link_id && (__internal_ret->link_id = Dz1Str_clone(link_id, errp)) == NULL) ERR_OUT(errp);
		else if (update_time && (__internal_ret->update_time = Dz1Str_clone(update_time, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->property_damage_code = property_damage_code;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (IncidentIdentityEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t IncidentIdentityEntry_copy(IncidentIdentityEntry *dst, IncidentIdentityEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->node_id && (dst->node_id = Dz1Str_clone(src->node_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->link_id && (dst->link_id = Dz1Str_clone(src->link_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->update_time && (dst->update_time = Dz1Str_clone(src->update_time, errp)) == NULL) ERR_OUT(errp);
	else if (src->property_damage_desc && (dst->property_damage_desc = Dz1Str_clone(src->property_damage_desc, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->loc_offset_begin = src->loc_offset_begin;
		dst->loc_offset_end = src->loc_offset_end;
		dst->fatality_cnt = src->fatality_cnt;
		dst->injuries_cnt = src->injuries_cnt;
		dst->property_damage_code = src->property_damage_code;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

IncidentIdentityEntry *IncidentIdentityEntry_clone(IncidentIdentityEntry *src, Dz1Error *err)
{
	IncidentIdentityEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (IncidentIdentityEntry *)Dz1Calloc(sizeof(IncidentIdentityEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(IncidentIdentityEntry_delAndSetNull, (void *)&dst);
		if (IncidentIdentityEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (IncidentIdentityEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void IncidentIdentityEntry_purge(IncidentIdentityEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->node_id);
	Dz1Str_del(p->link_id);
	Dz1Str_del(p->update_time);
	Dz1Str_del(p->property_damage_desc);
}

void IncidentIdentityEntry_del(IncidentIdentityEntry *p)
{
	if (p == NULL) return;
	IncidentIdentityEntry_purge(p);
	Dz1Free(p);
}

void IncidentIdentityEntry_dump(IncidentIdentityEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("node_id = ")); Dz1Str_dump(p->node_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("link_id = ")); Dz1Str_dump(p->link_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("loc_offset_begin = ")); Dz1u16_dump(&p->loc_offset_begin, tab); 
		Dz1Thread_tprintf(tab, Dz1T("loc_offset_end = ")); Dz1u16_dump(&p->loc_offset_end, tab); 
		Dz1Thread_tprintf(tab, Dz1T("update_time = ")); Dz1Str_dump(p->update_time, tab); 
		Dz1Thread_tprintf(tab, Dz1T("fatality_cnt = ")); Dz1u8_dump(&p->fatality_cnt, tab); 
		Dz1Thread_tprintf(tab, Dz1T("injuries_cnt = ")); Dz1u8_dump(&p->injuries_cnt, tab); 
		Dz1Thread_tprintf(tab, Dz1T("property_damage_code = ")); Dz1u8_dump(&p->property_damage_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("property_damage_desc = ")); Dz1Str_dump(p->property_damage_desc, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int IncidentIdentityEntry_cmp(IncidentIdentityEntry *a, IncidentIdentityEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->node_id == NULL && b->node_id == NULL) ret = 0;
	else if (a->node_id == NULL /*&& b->node_id != NULL*/) ret = -1;
	else if (/*a->node_id != NULL &&*/ b->node_id == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->node_id, b->node_id)) != 0) { }
	else if (a->link_id == NULL && b->link_id == NULL) ret = 0;
	else if (a->link_id == NULL /*&& b->link_id != NULL*/) ret = -1;
	else if (/*a->link_id != NULL &&*/ b->link_id == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->link_id, b->link_id)) != 0) { }
	return ret;
}
// IncidentIdentityEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// IncidentIdentityList
static Dz1Error IncidentIdentityList_add(IncidentIdentityList *p, IncidentIdentityEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static bool_t IncidentIdentityList_remove(IncidentIdentityList *p, IncidentIdentityEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static IncidentIdentityEntry *IncidentIdentityList_extract(IncidentIdentityList *p, IncidentIdentityEntry *key)
{
	return (IncidentIdentityEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct IncidentIdentityListMkArrArg
{
	IncidentIdentityEntry **arr;
	unsigned int idx;
} IncidentIdentityListMkArrArg;

static Dz1Error _IncidentIdentityList_get_array(void *ptr, IncidentIdentityEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	IncidentIdentityListMkArrArg *arg = (IncidentIdentityListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static IncidentIdentityEntry **IncidentIdentityList_get_array(IncidentIdentityList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	IncidentIdentityEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (IncidentIdentityEntry **)Dz1Calloc(sizeof(IncidentIdentityEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		IncidentIdentityListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _IncidentIdentityList_get_array, (void *)&arg);
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

static Dz1Error IncidentIdentityList_travelForward(IncidentIdentityList *p, Dz1Error (*func)(void *ptr, IncidentIdentityEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error IncidentIdentityList_travelBackward(IncidentIdentityList *p, Dz1Error (*func)(void *ptr, IncidentIdentityEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static IncidentIdentityEntry *IncidentIdentityList_find(IncidentIdentityList *p, IncidentIdentityEntry *key)
{
	return (IncidentIdentityEntry *)Dz1AATree_find(p->storage, key);
}

static IncidentIdentityEntry *IncidentIdentityList_getHead(IncidentIdentityList *p)
{
	return (IncidentIdentityEntry *)Dz1AATree_getHead(p->storage);
}

static unsigned int IncidentIdentityList_count(IncidentIdentityList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

IncidentIdentityList *IncidentIdentityList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	IncidentIdentityList *ret = (IncidentIdentityList *)Dz1Calloc(sizeof(IncidentIdentityList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(IncidentIdentityList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)IncidentIdentityEntry_cmp,
				(Dz1DelFunc)IncidentIdentityEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = IncidentIdentityList_count;
			ret->travel = IncidentIdentityList_travelForward;
			ret->travelForward = IncidentIdentityList_travelForward;
			ret->travelBackward = IncidentIdentityList_travelBackward;
			ret->get_array = IncidentIdentityList_get_array;
			ret->add = IncidentIdentityList_add;
			ret->remove = IncidentIdentityList_remove;
			ret->find = IncidentIdentityList_find;
			ret->extract = IncidentIdentityList_extract;
			ret->getHead = IncidentIdentityList_getHead;
			ret->cmp = IncidentIdentityEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (IncidentIdentityList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _IncidentIdentityList_clone(void *ptr, IncidentIdentityEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	IncidentIdentityList *p = (IncidentIdentityList *)ptr;
	IncidentIdentityEntry *cloned = IncidentIdentityEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

IncidentIdentityList *IncidentIdentityList_clone(IncidentIdentityList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	IncidentIdentityList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = IncidentIdentityList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(IncidentIdentityList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_IncidentIdentityList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (IncidentIdentityList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void IncidentIdentityList_purge(IncidentIdentityList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void IncidentIdentityList_del(IncidentIdentityList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _IncidentIdentityList_dump(void *ptr, IncidentIdentityEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); IncidentIdentityEntry_dump(p, tab);
	return err;
}

void IncidentIdentityList_dump(IncidentIdentityList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _IncidentIdentityList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// IncidentIdentityList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// IncidentConditionsEntry
IncidentConditionsEntry *IncidentConditionsEntry_new(Dz1Str node_id, 
													 Dz1Str link_id, 
													 Dz1Str contact_org_name, 
													 u8_t incident_code, 
													 u8_t veh_invloved_code, 
													 u8_t status_code, 
													 u8_t update_type_code, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	IncidentConditionsEntry *__internal_ret = (IncidentConditionsEntry *)Dz1Calloc(sizeof(IncidentConditionsEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(IncidentConditionsEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (node_id && (__internal_ret->node_id = Dz1Str_clone(node_id, errp)) == NULL) ERR_OUT(errp);
		else if (link_id && (__internal_ret->link_id = Dz1Str_clone(link_id, errp)) == NULL) ERR_OUT(errp);
		else if (contact_org_name && (__internal_ret->contact_org_name = Dz1Str_clone(contact_org_name, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->incident_code = incident_code;
			__internal_ret->veh_invloved_code = veh_invloved_code;
			__internal_ret->status_code = status_code;
			__internal_ret->update_type_code = update_type_code;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (IncidentConditionsEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t IncidentConditionsEntry_copy(IncidentConditionsEntry *dst, IncidentConditionsEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->node_id && (dst->node_id = Dz1Str_clone(src->node_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->link_id && (dst->link_id = Dz1Str_clone(src->link_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->contact_org_name && (dst->contact_org_name = Dz1Str_clone(src->contact_org_name, errp)) == NULL) ERR_OUT(errp);
	else if (src->other_incident_desc && (dst->other_incident_desc = Dz1Str_clone(src->other_incident_desc, errp)) == NULL) ERR_OUT(errp);
	else if (src->other_veh_invloved_desc && (dst->other_veh_invloved_desc = Dz1Str_clone(src->other_veh_invloved_desc, errp)) == NULL) ERR_OUT(errp);
	else if (src->other_status_desc && (dst->other_status_desc = Dz1Str_clone(src->other_status_desc, errp)) == NULL) ERR_OUT(errp);
	else if (src->other_update_desc && (dst->other_update_desc = Dz1Str_clone(src->other_update_desc, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->incident_code = src->incident_code;
		dst->veh_invloved_code = src->veh_invloved_code;
		dst->status_code = src->status_code;
		dst->update_type_code = src->update_type_code;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

IncidentConditionsEntry *IncidentConditionsEntry_clone(IncidentConditionsEntry *src, Dz1Error *err)
{
	IncidentConditionsEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (IncidentConditionsEntry *)Dz1Calloc(sizeof(IncidentConditionsEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(IncidentConditionsEntry_delAndSetNull, (void *)&dst);
		if (IncidentConditionsEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (IncidentConditionsEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void IncidentConditionsEntry_purge(IncidentConditionsEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->node_id);
	Dz1Str_del(p->link_id);
	Dz1Str_del(p->contact_org_name);
	Dz1Str_del(p->other_incident_desc);
	Dz1Str_del(p->other_veh_invloved_desc);
	Dz1Str_del(p->other_status_desc);
	Dz1Str_del(p->other_update_desc);
}

void IncidentConditionsEntry_del(IncidentConditionsEntry *p)
{
	if (p == NULL) return;
	IncidentConditionsEntry_purge(p);
	Dz1Free(p);
}

void IncidentConditionsEntry_dump(IncidentConditionsEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("node_id = ")); Dz1Str_dump(p->node_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("link_id = ")); Dz1Str_dump(p->link_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("contact_org_name = ")); Dz1Str_dump(p->contact_org_name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("incident_code = ")); Dz1u8_dump(&p->incident_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("other_incident_desc = ")); Dz1Str_dump(p->other_incident_desc, tab); 
		Dz1Thread_tprintf(tab, Dz1T("veh_invloved_code = ")); Dz1u8_dump(&p->veh_invloved_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("other_veh_invloved_desc = ")); Dz1Str_dump(p->other_veh_invloved_desc, tab); 
		Dz1Thread_tprintf(tab, Dz1T("status_code = ")); Dz1u8_dump(&p->status_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("other_status_desc = ")); Dz1Str_dump(p->other_status_desc, tab); 
		Dz1Thread_tprintf(tab, Dz1T("update_type_code = ")); Dz1u8_dump(&p->update_type_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("other_update_desc = ")); Dz1Str_dump(p->other_update_desc, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int IncidentConditionsEntry_cmp(IncidentConditionsEntry *a, IncidentConditionsEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->node_id == NULL && b->node_id == NULL) ret = 0;
	else if (a->node_id == NULL /*&& b->node_id != NULL*/) ret = -1;
	else if (/*a->node_id != NULL &&*/ b->node_id == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->node_id, b->node_id)) != 0) { }
	else if (a->link_id == NULL && b->link_id == NULL) ret = 0;
	else if (a->link_id == NULL /*&& b->link_id != NULL*/) ret = -1;
	else if (/*a->link_id != NULL &&*/ b->link_id == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->link_id, b->link_id)) != 0) { }
	else if (a->contact_org_name == NULL && b->contact_org_name == NULL) ret = 0;
	else if (a->contact_org_name == NULL /*&& b->contact_org_name != NULL*/) ret = -1;
	else if (/*a->contact_org_name != NULL &&*/ b->contact_org_name == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->contact_org_name, b->contact_org_name)) != 0) { }
	else if ((ret = Dz1u8_cmp(&a->incident_code, &b->incident_code)) != 0) { }
	return ret;
}
// IncidentConditionsEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// IncidentConditionsList
static Dz1Error IncidentConditionsList_add(IncidentConditionsList *p, IncidentConditionsEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static bool_t IncidentConditionsList_remove(IncidentConditionsList *p, IncidentConditionsEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static IncidentConditionsEntry *IncidentConditionsList_extract(IncidentConditionsList *p, IncidentConditionsEntry *key)
{
	return (IncidentConditionsEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct IncidentConditionsListMkArrArg
{
	IncidentConditionsEntry **arr;
	unsigned int idx;
} IncidentConditionsListMkArrArg;

static Dz1Error _IncidentConditionsList_get_array(void *ptr, IncidentConditionsEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	IncidentConditionsListMkArrArg *arg = (IncidentConditionsListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static IncidentConditionsEntry **IncidentConditionsList_get_array(IncidentConditionsList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	IncidentConditionsEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (IncidentConditionsEntry **)Dz1Calloc(sizeof(IncidentConditionsEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		IncidentConditionsListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _IncidentConditionsList_get_array, (void *)&arg);
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

static Dz1Error IncidentConditionsList_travelForward(IncidentConditionsList *p, Dz1Error (*func)(void *ptr, IncidentConditionsEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error IncidentConditionsList_travelBackward(IncidentConditionsList *p, Dz1Error (*func)(void *ptr, IncidentConditionsEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static IncidentConditionsEntry *IncidentConditionsList_find(IncidentConditionsList *p, IncidentConditionsEntry *key)
{
	return (IncidentConditionsEntry *)Dz1AATree_find(p->storage, key);
}

static IncidentConditionsEntry *IncidentConditionsList_getHead(IncidentConditionsList *p)
{
	return (IncidentConditionsEntry *)Dz1AATree_getHead(p->storage);
}

static unsigned int IncidentConditionsList_count(IncidentConditionsList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

IncidentConditionsList *IncidentConditionsList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	IncidentConditionsList *ret = (IncidentConditionsList *)Dz1Calloc(sizeof(IncidentConditionsList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(IncidentConditionsList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)IncidentConditionsEntry_cmp,
				(Dz1DelFunc)IncidentConditionsEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = IncidentConditionsList_count;
			ret->travel = IncidentConditionsList_travelForward;
			ret->travelForward = IncidentConditionsList_travelForward;
			ret->travelBackward = IncidentConditionsList_travelBackward;
			ret->get_array = IncidentConditionsList_get_array;
			ret->add = IncidentConditionsList_add;
			ret->remove = IncidentConditionsList_remove;
			ret->find = IncidentConditionsList_find;
			ret->extract = IncidentConditionsList_extract;
			ret->getHead = IncidentConditionsList_getHead;
			ret->cmp = IncidentConditionsEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (IncidentConditionsList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _IncidentConditionsList_clone(void *ptr, IncidentConditionsEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	IncidentConditionsList *p = (IncidentConditionsList *)ptr;
	IncidentConditionsEntry *cloned = IncidentConditionsEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

IncidentConditionsList *IncidentConditionsList_clone(IncidentConditionsList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	IncidentConditionsList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = IncidentConditionsList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(IncidentConditionsList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_IncidentConditionsList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (IncidentConditionsList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void IncidentConditionsList_purge(IncidentConditionsList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void IncidentConditionsList_del(IncidentConditionsList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _IncidentConditionsList_dump(void *ptr, IncidentConditionsEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); IncidentConditionsEntry_dump(p, tab);
	return err;
}

void IncidentConditionsList_dump(IncidentConditionsList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _IncidentConditionsList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// IncidentConditionsList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// RoadwaySurfaceStatusEntry
RoadwaySurfaceStatusEntry *RoadwaySurfaceStatusEntry_new(Dz1Str node_id, 
														 Dz1Str link_id, 
														 u8_t surface_cond_code, 
														 u8_t land_blocked_or_closed_code, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	RoadwaySurfaceStatusEntry *__internal_ret = (RoadwaySurfaceStatusEntry *)Dz1Calloc(sizeof(RoadwaySurfaceStatusEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(RoadwaySurfaceStatusEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (node_id && (__internal_ret->node_id = Dz1Str_clone(node_id, errp)) == NULL) ERR_OUT(errp);
		else if (link_id && (__internal_ret->link_id = Dz1Str_clone(link_id, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->surface_cond_code = surface_cond_code;
			__internal_ret->land_blocked_or_closed_code = land_blocked_or_closed_code;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (RoadwaySurfaceStatusEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t RoadwaySurfaceStatusEntry_copy(RoadwaySurfaceStatusEntry *dst, RoadwaySurfaceStatusEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->node_id && (dst->node_id = Dz1Str_clone(src->node_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->link_id && (dst->link_id = Dz1Str_clone(src->link_id, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->surface_cond_code = src->surface_cond_code;
		dst->land_blocked_or_closed_code = src->land_blocked_or_closed_code;
		dst->precipitation_depth = src->precipitation_depth;
		dst->temperature_qty = src->temperature_qty;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

RoadwaySurfaceStatusEntry *RoadwaySurfaceStatusEntry_clone(RoadwaySurfaceStatusEntry *src, Dz1Error *err)
{
	RoadwaySurfaceStatusEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (RoadwaySurfaceStatusEntry *)Dz1Calloc(sizeof(RoadwaySurfaceStatusEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(RoadwaySurfaceStatusEntry_delAndSetNull, (void *)&dst);
		if (RoadwaySurfaceStatusEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (RoadwaySurfaceStatusEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void RoadwaySurfaceStatusEntry_purge(RoadwaySurfaceStatusEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->node_id);
	Dz1Str_del(p->link_id);
}

void RoadwaySurfaceStatusEntry_del(RoadwaySurfaceStatusEntry *p)
{
	if (p == NULL) return;
	RoadwaySurfaceStatusEntry_purge(p);
	Dz1Free(p);
}

void RoadwaySurfaceStatusEntry_dump(RoadwaySurfaceStatusEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("node_id = ")); Dz1Str_dump(p->node_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("link_id = ")); Dz1Str_dump(p->link_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("surface_cond_code = ")); Dz1u8_dump(&p->surface_cond_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("land_blocked_or_closed_code = ")); Dz1u8_dump(&p->land_blocked_or_closed_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("precipitation_depth = ")); Dz1u16_dump(&p->precipitation_depth, tab); 
		Dz1Thread_tprintf(tab, Dz1T("temperature_qty = ")); Dz1u16_dump(&p->temperature_qty, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int RoadwaySurfaceStatusEntry_cmp(RoadwaySurfaceStatusEntry *a, RoadwaySurfaceStatusEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->node_id == NULL && b->node_id == NULL) ret = 0;
	else if (a->node_id == NULL /*&& b->node_id != NULL*/) ret = -1;
	else if (/*a->node_id != NULL &&*/ b->node_id == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->node_id, b->node_id)) != 0) { }
	else if (a->link_id == NULL && b->link_id == NULL) ret = 0;
	else if (a->link_id == NULL /*&& b->link_id != NULL*/) ret = -1;
	else if (/*a->link_id != NULL &&*/ b->link_id == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->link_id, b->link_id)) != 0) { }
	return ret;
}
// RoadwaySurfaceStatusEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// RoadwaySurfaceStatusList
static Dz1Error RoadwaySurfaceStatusList_add(RoadwaySurfaceStatusList *p, RoadwaySurfaceStatusEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static bool_t RoadwaySurfaceStatusList_remove(RoadwaySurfaceStatusList *p, RoadwaySurfaceStatusEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static RoadwaySurfaceStatusEntry *RoadwaySurfaceStatusList_extract(RoadwaySurfaceStatusList *p, RoadwaySurfaceStatusEntry *key)
{
	return (RoadwaySurfaceStatusEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct RoadwaySurfaceStatusListMkArrArg
{
	RoadwaySurfaceStatusEntry **arr;
	unsigned int idx;
} RoadwaySurfaceStatusListMkArrArg;

static Dz1Error _RoadwaySurfaceStatusList_get_array(void *ptr, RoadwaySurfaceStatusEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	RoadwaySurfaceStatusListMkArrArg *arg = (RoadwaySurfaceStatusListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static RoadwaySurfaceStatusEntry **RoadwaySurfaceStatusList_get_array(RoadwaySurfaceStatusList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	RoadwaySurfaceStatusEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (RoadwaySurfaceStatusEntry **)Dz1Calloc(sizeof(RoadwaySurfaceStatusEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		RoadwaySurfaceStatusListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _RoadwaySurfaceStatusList_get_array, (void *)&arg);
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

static Dz1Error RoadwaySurfaceStatusList_travelForward(RoadwaySurfaceStatusList *p, Dz1Error (*func)(void *ptr, RoadwaySurfaceStatusEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error RoadwaySurfaceStatusList_travelBackward(RoadwaySurfaceStatusList *p, Dz1Error (*func)(void *ptr, RoadwaySurfaceStatusEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static RoadwaySurfaceStatusEntry *RoadwaySurfaceStatusList_find(RoadwaySurfaceStatusList *p, RoadwaySurfaceStatusEntry *key)
{
	return (RoadwaySurfaceStatusEntry *)Dz1AATree_find(p->storage, key);
}

static RoadwaySurfaceStatusEntry *RoadwaySurfaceStatusList_getHead(RoadwaySurfaceStatusList *p)
{
	return (RoadwaySurfaceStatusEntry *)Dz1AATree_getHead(p->storage);
}

static unsigned int RoadwaySurfaceStatusList_count(RoadwaySurfaceStatusList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

RoadwaySurfaceStatusList *RoadwaySurfaceStatusList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	RoadwaySurfaceStatusList *ret = (RoadwaySurfaceStatusList *)Dz1Calloc(sizeof(RoadwaySurfaceStatusList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(RoadwaySurfaceStatusList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)RoadwaySurfaceStatusEntry_cmp,
				(Dz1DelFunc)RoadwaySurfaceStatusEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = RoadwaySurfaceStatusList_count;
			ret->travel = RoadwaySurfaceStatusList_travelForward;
			ret->travelForward = RoadwaySurfaceStatusList_travelForward;
			ret->travelBackward = RoadwaySurfaceStatusList_travelBackward;
			ret->get_array = RoadwaySurfaceStatusList_get_array;
			ret->add = RoadwaySurfaceStatusList_add;
			ret->remove = RoadwaySurfaceStatusList_remove;
			ret->find = RoadwaySurfaceStatusList_find;
			ret->extract = RoadwaySurfaceStatusList_extract;
			ret->getHead = RoadwaySurfaceStatusList_getHead;
			ret->cmp = RoadwaySurfaceStatusEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (RoadwaySurfaceStatusList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _RoadwaySurfaceStatusList_clone(void *ptr, RoadwaySurfaceStatusEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	RoadwaySurfaceStatusList *p = (RoadwaySurfaceStatusList *)ptr;
	RoadwaySurfaceStatusEntry *cloned = RoadwaySurfaceStatusEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

RoadwaySurfaceStatusList *RoadwaySurfaceStatusList_clone(RoadwaySurfaceStatusList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	RoadwaySurfaceStatusList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = RoadwaySurfaceStatusList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(RoadwaySurfaceStatusList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_RoadwaySurfaceStatusList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (RoadwaySurfaceStatusList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void RoadwaySurfaceStatusList_purge(RoadwaySurfaceStatusList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void RoadwaySurfaceStatusList_del(RoadwaySurfaceStatusList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _RoadwaySurfaceStatusList_dump(void *ptr, RoadwaySurfaceStatusEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); RoadwaySurfaceStatusEntry_dump(p, tab);
	return err;
}

void RoadwaySurfaceStatusList_dump(RoadwaySurfaceStatusList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _RoadwaySurfaceStatusList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// RoadwaySurfaceStatusList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// WeatherInformationEntry
WeatherInformationEntry *WeatherInformationEntry_new(u8_t forecast_or_actual, 
													 u8_t probability, 
													 u8_t visibility, 
													 u8_t wind_speed, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	WeatherInformationEntry *__internal_ret = (WeatherInformationEntry *)Dz1Calloc(sizeof(WeatherInformationEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(WeatherInformationEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->forecast_or_actual = forecast_or_actual;
		__internal_ret->probability = probability;
		__internal_ret->visibility = visibility;
		__internal_ret->wind_speed = wind_speed;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (WeatherInformationEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t WeatherInformationEntry_copy(WeatherInformationEntry *dst, WeatherInformationEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->other_cond_desc && (dst->other_cond_desc = Dz1Str_clone(src->other_cond_desc, errp)) == NULL) ERR_OUT(errp);
	else if (src->sunrise_time && (dst->sunrise_time = Dz1Str_clone(src->sunrise_time, errp)) == NULL) ERR_OUT(errp);
	else if (src->sunset_time && (dst->sunset_time = Dz1Str_clone(src->sunset_time, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->forecast_or_actual = src->forecast_or_actual;
		dst->temperature = src->temperature;
		dst->high_temperature = src->high_temperature;
		dst->low_temperature = src->low_temperature;
		dst->special_cond = src->special_cond;
		dst->probability = src->probability;
		dst->visibility = src->visibility;
		dst->wind_speed = src->wind_speed;
		dst->wind_direct_code = src->wind_direct_code;
		dst->humidity = src->humidity;
		dst->pressure = src->pressure;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

WeatherInformationEntry *WeatherInformationEntry_clone(WeatherInformationEntry *src, Dz1Error *err)
{
	WeatherInformationEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (WeatherInformationEntry *)Dz1Calloc(sizeof(WeatherInformationEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(WeatherInformationEntry_delAndSetNull, (void *)&dst);
		if (WeatherInformationEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (WeatherInformationEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void WeatherInformationEntry_purge(WeatherInformationEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->other_cond_desc);
	Dz1Str_del(p->sunrise_time);
	Dz1Str_del(p->sunset_time);
}

void WeatherInformationEntry_del(WeatherInformationEntry *p)
{
	if (p == NULL) return;
	WeatherInformationEntry_purge(p);
	Dz1Free(p);
}

void WeatherInformationEntry_dump(WeatherInformationEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("forecast_or_actual = ")); Dz1u8_dump(&p->forecast_or_actual, tab); 
		Dz1Thread_tprintf(tab, Dz1T("temperature = ")); Dz1s8_dump(&p->temperature, tab); 
		Dz1Thread_tprintf(tab, Dz1T("high_temperature = ")); Dz1s8_dump(&p->high_temperature, tab); 
		Dz1Thread_tprintf(tab, Dz1T("low_temperature = ")); Dz1s8_dump(&p->low_temperature, tab); 
		Dz1Thread_tprintf(tab, Dz1T("special_cond = ")); Dz1u8_dump(&p->special_cond, tab); 
		Dz1Thread_tprintf(tab, Dz1T("other_cond_desc = ")); Dz1Str_dump(p->other_cond_desc, tab); 
		Dz1Thread_tprintf(tab, Dz1T("probability = ")); Dz1u8_dump(&p->probability, tab); 
		Dz1Thread_tprintf(tab, Dz1T("visibility = ")); Dz1u8_dump(&p->visibility, tab); 
		Dz1Thread_tprintf(tab, Dz1T("wind_speed = ")); Dz1u8_dump(&p->wind_speed, tab); 
		Dz1Thread_tprintf(tab, Dz1T("wind_direct_code = ")); Dz1u8_dump(&p->wind_direct_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("humidity = ")); Dz1u8_dump(&p->humidity, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pressure = ")); Dz1u8_dump(&p->pressure, tab); 
		Dz1Thread_tprintf(tab, Dz1T("sunrise_time = ")); Dz1Str_dump(p->sunrise_time, tab); 
		Dz1Thread_tprintf(tab, Dz1T("sunset_time = ")); Dz1Str_dump(p->sunset_time, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int WeatherInformationEntry_cmp(WeatherInformationEntry *a, WeatherInformationEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u8_cmp(&a->forecast_or_actual, &b->forecast_or_actual)) != 0) { }
	return ret;
}
// WeatherInformationEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// WeatherInformationList
static Dz1Error WeatherInformationList_add(WeatherInformationList *p, WeatherInformationEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static bool_t WeatherInformationList_remove(WeatherInformationList *p, WeatherInformationEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static WeatherInformationEntry *WeatherInformationList_extract(WeatherInformationList *p, WeatherInformationEntry *key)
{
	return (WeatherInformationEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct WeatherInformationListMkArrArg
{
	WeatherInformationEntry **arr;
	unsigned int idx;
} WeatherInformationListMkArrArg;

static Dz1Error _WeatherInformationList_get_array(void *ptr, WeatherInformationEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	WeatherInformationListMkArrArg *arg = (WeatherInformationListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static WeatherInformationEntry **WeatherInformationList_get_array(WeatherInformationList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	WeatherInformationEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (WeatherInformationEntry **)Dz1Calloc(sizeof(WeatherInformationEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		WeatherInformationListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _WeatherInformationList_get_array, (void *)&arg);
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

static Dz1Error WeatherInformationList_travelForward(WeatherInformationList *p, Dz1Error (*func)(void *ptr, WeatherInformationEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error WeatherInformationList_travelBackward(WeatherInformationList *p, Dz1Error (*func)(void *ptr, WeatherInformationEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static WeatherInformationEntry *WeatherInformationList_find(WeatherInformationList *p, WeatherInformationEntry *key)
{
	return (WeatherInformationEntry *)Dz1AATree_find(p->storage, key);
}

static WeatherInformationEntry *WeatherInformationList_getHead(WeatherInformationList *p)
{
	return (WeatherInformationEntry *)Dz1AATree_getHead(p->storage);
}

static unsigned int WeatherInformationList_count(WeatherInformationList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

WeatherInformationList *WeatherInformationList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	WeatherInformationList *ret = (WeatherInformationList *)Dz1Calloc(sizeof(WeatherInformationList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(WeatherInformationList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)WeatherInformationEntry_cmp,
				(Dz1DelFunc)WeatherInformationEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = WeatherInformationList_count;
			ret->travel = WeatherInformationList_travelForward;
			ret->travelForward = WeatherInformationList_travelForward;
			ret->travelBackward = WeatherInformationList_travelBackward;
			ret->get_array = WeatherInformationList_get_array;
			ret->add = WeatherInformationList_add;
			ret->remove = WeatherInformationList_remove;
			ret->find = WeatherInformationList_find;
			ret->extract = WeatherInformationList_extract;
			ret->getHead = WeatherInformationList_getHead;
			ret->cmp = WeatherInformationEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (WeatherInformationList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _WeatherInformationList_clone(void *ptr, WeatherInformationEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	WeatherInformationList *p = (WeatherInformationList *)ptr;
	WeatherInformationEntry *cloned = WeatherInformationEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

WeatherInformationList *WeatherInformationList_clone(WeatherInformationList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	WeatherInformationList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = WeatherInformationList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(WeatherInformationList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_WeatherInformationList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (WeatherInformationList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void WeatherInformationList_purge(WeatherInformationList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void WeatherInformationList_del(WeatherInformationList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _WeatherInformationList_dump(void *ptr, WeatherInformationEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); WeatherInformationEntry_dump(p, tab);
	return err;
}

void WeatherInformationList_dump(WeatherInformationList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _WeatherInformationList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// WeatherInformationList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// LinkRoadwayGeometryEntry
LinkRoadwayGeometryEntry *LinkRoadwayGeometryEntry_new(Dz1Str begin_node_id, 
													   Dz1Str end_node_id, 
													   Dz1Str jurisdiction, 
													   u8_t type_code, 
													   Dz1Str name, 
													   u32_t length, 
													   u8_t pavement_type_code, 
													   u8_t median_type_code, 
													   u16_t num_lanes, 
													   u8_t num_open_lanes, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	LinkRoadwayGeometryEntry *__internal_ret = (LinkRoadwayGeometryEntry *)Dz1Calloc(sizeof(LinkRoadwayGeometryEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(LinkRoadwayGeometryEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (begin_node_id && (__internal_ret->begin_node_id = Dz1Str_clone(begin_node_id, errp)) == NULL) ERR_OUT(errp);
		else if (end_node_id && (__internal_ret->end_node_id = Dz1Str_clone(end_node_id, errp)) == NULL) ERR_OUT(errp);
		else if (jurisdiction && (__internal_ret->jurisdiction = Dz1Str_clone(jurisdiction, errp)) == NULL) ERR_OUT(errp);
		else if (name && (__internal_ret->name = Dz1Str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->type_code = type_code;
			__internal_ret->length = length;
			__internal_ret->pavement_type_code = pavement_type_code;
			__internal_ret->median_type_code = median_type_code;
			__internal_ret->num_lanes = num_lanes;
			__internal_ret->num_open_lanes = num_open_lanes;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (LinkRoadwayGeometryEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t LinkRoadwayGeometryEntry_copy(LinkRoadwayGeometryEntry *dst, LinkRoadwayGeometryEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->begin_node_id && (dst->begin_node_id = Dz1Str_clone(src->begin_node_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->end_node_id && (dst->end_node_id = Dz1Str_clone(src->end_node_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->jurisdiction && (dst->jurisdiction = Dz1Str_clone(src->jurisdiction, errp)) == NULL) ERR_OUT(errp);
	else if (src->name && (dst->name = Dz1Str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->begin_node_latitude = src->begin_node_latitude;
		dst->begin_node_longitude = src->begin_node_longitude;
		dst->end_node_latitude = src->end_node_latitude;
		dst->end_node_longitude = src->end_node_longitude;
		dst->type_code = src->type_code;
		dst->length = src->length;
		dst->pavement_type_code = src->pavement_type_code;
		dst->restriction_height = src->restriction_height;
		dst->left_shoulder_width = src->left_shoulder_width;
		dst->restriction_length = src->restriction_length;
		dst->median_type_code = src->median_type_code;
		dst->num_lanes = src->num_lanes;
		dst->num_open_lanes = src->num_open_lanes;
		dst->right_shoulder_width = src->right_shoulder_width;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

LinkRoadwayGeometryEntry *LinkRoadwayGeometryEntry_clone(LinkRoadwayGeometryEntry *src, Dz1Error *err)
{
	LinkRoadwayGeometryEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (LinkRoadwayGeometryEntry *)Dz1Calloc(sizeof(LinkRoadwayGeometryEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(LinkRoadwayGeometryEntry_delAndSetNull, (void *)&dst);
		if (LinkRoadwayGeometryEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (LinkRoadwayGeometryEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void LinkRoadwayGeometryEntry_purge(LinkRoadwayGeometryEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->begin_node_id);
	Dz1Str_del(p->end_node_id);
	Dz1Str_del(p->jurisdiction);
	Dz1Str_del(p->name);
}

void LinkRoadwayGeometryEntry_del(LinkRoadwayGeometryEntry *p)
{
	if (p == NULL) return;
	LinkRoadwayGeometryEntry_purge(p);
	Dz1Free(p);
}

void LinkRoadwayGeometryEntry_dump(LinkRoadwayGeometryEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("begin_node_id = ")); Dz1Str_dump(p->begin_node_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("begin_node_latitude = ")); Dz1s64_dump(&p->begin_node_latitude, tab); 
		Dz1Thread_tprintf(tab, Dz1T("begin_node_longitude = ")); Dz1u32_dump(&p->begin_node_longitude, tab); 
		Dz1Thread_tprintf(tab, Dz1T("end_node_id = ")); Dz1Str_dump(p->end_node_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("end_node_latitude = ")); Dz1s64_dump(&p->end_node_latitude, tab); 
		Dz1Thread_tprintf(tab, Dz1T("end_node_longitude = ")); Dz1u32_dump(&p->end_node_longitude, tab); 
		Dz1Thread_tprintf(tab, Dz1T("jurisdiction = ")); Dz1Str_dump(p->jurisdiction, tab); 
		Dz1Thread_tprintf(tab, Dz1T("type_code = ")); Dz1u8_dump(&p->type_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("name = ")); Dz1Str_dump(p->name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("length = ")); Dz1u32_dump(&p->length, tab); 
		Dz1Thread_tprintf(tab, Dz1T("pavement_type_code = ")); Dz1u8_dump(&p->pavement_type_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("restriction_height = ")); Dz1u16_dump(&p->restriction_height, tab); 
		Dz1Thread_tprintf(tab, Dz1T("left_shoulder_width = ")); Dz1u16_dump(&p->left_shoulder_width, tab); 
		Dz1Thread_tprintf(tab, Dz1T("restriction_length = ")); Dz1u16_dump(&p->restriction_length, tab); 
		Dz1Thread_tprintf(tab, Dz1T("median_type_code = ")); Dz1u8_dump(&p->median_type_code, tab); 
		Dz1Thread_tprintf(tab, Dz1T("num_lanes = ")); Dz1u16_dump(&p->num_lanes, tab); 
		Dz1Thread_tprintf(tab, Dz1T("num_open_lanes = ")); Dz1u8_dump(&p->num_open_lanes, tab); 
		Dz1Thread_tprintf(tab, Dz1T("right_shoulder_width = ")); Dz1u16_dump(&p->right_shoulder_width, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int LinkRoadwayGeometryEntry_cmp(LinkRoadwayGeometryEntry *a, LinkRoadwayGeometryEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->begin_node_id == NULL && b->begin_node_id == NULL) ret = 0;
	else if (a->begin_node_id == NULL /*&& b->begin_node_id != NULL*/) ret = -1;
	else if (/*a->begin_node_id != NULL &&*/ b->begin_node_id == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->begin_node_id, b->begin_node_id)) != 0) { }
	else if (a->end_node_id == NULL && b->end_node_id == NULL) ret = 0;
	else if (a->end_node_id == NULL /*&& b->end_node_id != NULL*/) ret = -1;
	else if (/*a->end_node_id != NULL &&*/ b->end_node_id == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->end_node_id, b->end_node_id)) != 0) { }
	return ret;
}
// LinkRoadwayGeometryEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// LinkRoadwayGeometryList
static Dz1Error LinkRoadwayGeometryList_add(LinkRoadwayGeometryList *p, LinkRoadwayGeometryEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static bool_t LinkRoadwayGeometryList_remove(LinkRoadwayGeometryList *p, LinkRoadwayGeometryEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static LinkRoadwayGeometryEntry *LinkRoadwayGeometryList_extract(LinkRoadwayGeometryList *p, LinkRoadwayGeometryEntry *key)
{
	return (LinkRoadwayGeometryEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct LinkRoadwayGeometryListMkArrArg
{
	LinkRoadwayGeometryEntry **arr;
	unsigned int idx;
} LinkRoadwayGeometryListMkArrArg;

static Dz1Error _LinkRoadwayGeometryList_get_array(void *ptr, LinkRoadwayGeometryEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	LinkRoadwayGeometryListMkArrArg *arg = (LinkRoadwayGeometryListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static LinkRoadwayGeometryEntry **LinkRoadwayGeometryList_get_array(LinkRoadwayGeometryList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	LinkRoadwayGeometryEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (LinkRoadwayGeometryEntry **)Dz1Calloc(sizeof(LinkRoadwayGeometryEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		LinkRoadwayGeometryListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _LinkRoadwayGeometryList_get_array, (void *)&arg);
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

static Dz1Error LinkRoadwayGeometryList_travelForward(LinkRoadwayGeometryList *p, Dz1Error (*func)(void *ptr, LinkRoadwayGeometryEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error LinkRoadwayGeometryList_travelBackward(LinkRoadwayGeometryList *p, Dz1Error (*func)(void *ptr, LinkRoadwayGeometryEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static LinkRoadwayGeometryEntry *LinkRoadwayGeometryList_find(LinkRoadwayGeometryList *p, LinkRoadwayGeometryEntry *key)
{
	return (LinkRoadwayGeometryEntry *)Dz1AATree_find(p->storage, key);
}

static LinkRoadwayGeometryEntry *LinkRoadwayGeometryList_getHead(LinkRoadwayGeometryList *p)
{
	return (LinkRoadwayGeometryEntry *)Dz1AATree_getHead(p->storage);
}

static unsigned int LinkRoadwayGeometryList_count(LinkRoadwayGeometryList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

LinkRoadwayGeometryList *LinkRoadwayGeometryList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	LinkRoadwayGeometryList *ret = (LinkRoadwayGeometryList *)Dz1Calloc(sizeof(LinkRoadwayGeometryList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(LinkRoadwayGeometryList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)LinkRoadwayGeometryEntry_cmp,
				(Dz1DelFunc)LinkRoadwayGeometryEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = LinkRoadwayGeometryList_count;
			ret->travel = LinkRoadwayGeometryList_travelForward;
			ret->travelForward = LinkRoadwayGeometryList_travelForward;
			ret->travelBackward = LinkRoadwayGeometryList_travelBackward;
			ret->get_array = LinkRoadwayGeometryList_get_array;
			ret->add = LinkRoadwayGeometryList_add;
			ret->remove = LinkRoadwayGeometryList_remove;
			ret->find = LinkRoadwayGeometryList_find;
			ret->extract = LinkRoadwayGeometryList_extract;
			ret->getHead = LinkRoadwayGeometryList_getHead;
			ret->cmp = LinkRoadwayGeometryEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (LinkRoadwayGeometryList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _LinkRoadwayGeometryList_clone(void *ptr, LinkRoadwayGeometryEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	LinkRoadwayGeometryList *p = (LinkRoadwayGeometryList *)ptr;
	LinkRoadwayGeometryEntry *cloned = LinkRoadwayGeometryEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

LinkRoadwayGeometryList *LinkRoadwayGeometryList_clone(LinkRoadwayGeometryList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	LinkRoadwayGeometryList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = LinkRoadwayGeometryList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(LinkRoadwayGeometryList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_LinkRoadwayGeometryList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (LinkRoadwayGeometryList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void LinkRoadwayGeometryList_purge(LinkRoadwayGeometryList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void LinkRoadwayGeometryList_del(LinkRoadwayGeometryList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _LinkRoadwayGeometryList_dump(void *ptr, LinkRoadwayGeometryEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); LinkRoadwayGeometryEntry_dump(p, tab);
	return err;
}

void LinkRoadwayGeometryList_dump(LinkRoadwayGeometryList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _LinkRoadwayGeometryList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// LinkRoadwayGeometryList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ProbeVehicleDetectionEntry
ProbeVehicleDetectionEntry *ProbeVehicleDetectionEntry_new(Dz1Str veh_id, 
														   u8_t veh_class, 
														   Dz1Str veh_timein, 
														   Dz1Str veh_timeout, 
														   u16_t veh_traveltime, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ProbeVehicleDetectionEntry *__internal_ret = (ProbeVehicleDetectionEntry *)Dz1Calloc(sizeof(ProbeVehicleDetectionEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ProbeVehicleDetectionEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (veh_id && (__internal_ret->veh_id = Dz1Str_clone(veh_id, errp)) == NULL) ERR_OUT(errp);
		else if (veh_timein && (__internal_ret->veh_timein = Dz1Str_clone(veh_timein, errp)) == NULL) ERR_OUT(errp);
		else if (veh_timeout && (__internal_ret->veh_timeout = Dz1Str_clone(veh_timeout, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->veh_class = veh_class;
			__internal_ret->veh_traveltime = veh_traveltime;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ProbeVehicleDetectionEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ProbeVehicleDetectionEntry_copy(ProbeVehicleDetectionEntry *dst, ProbeVehicleDetectionEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->veh_id && (dst->veh_id = Dz1Str_clone(src->veh_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->veh_timein && (dst->veh_timein = Dz1Str_clone(src->veh_timein, errp)) == NULL) ERR_OUT(errp);
	else if (src->veh_timeout && (dst->veh_timeout = Dz1Str_clone(src->veh_timeout, errp)) == NULL) ERR_OUT(errp);
	else if (src->avi_id && (dst->avi_id = Dz1Str_clone(src->avi_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->ref_avi_id && (dst->ref_avi_id = Dz1Str_clone(src->ref_avi_id, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->veh_class = src->veh_class;
		dst->veh_traveltime = src->veh_traveltime;
		dst->veh_avg_speed = src->veh_avg_speed;
		dst->avi_latitude = src->avi_latitude;
		dst->avi_longitude = src->avi_longitude;
		dst->ref_avi_latitude = src->ref_avi_latitude;
		dst->ref_avi_longitude = src->ref_avi_longitude;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ProbeVehicleDetectionEntry *ProbeVehicleDetectionEntry_clone(ProbeVehicleDetectionEntry *src, Dz1Error *err)
{
	ProbeVehicleDetectionEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ProbeVehicleDetectionEntry *)Dz1Calloc(sizeof(ProbeVehicleDetectionEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ProbeVehicleDetectionEntry_delAndSetNull, (void *)&dst);
		if (ProbeVehicleDetectionEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ProbeVehicleDetectionEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ProbeVehicleDetectionEntry_purge(ProbeVehicleDetectionEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->veh_id);
	Dz1Str_del(p->veh_timein);
	Dz1Str_del(p->veh_timeout);
	Dz1Str_del(p->avi_id);
	Dz1Str_del(p->ref_avi_id);
}

void ProbeVehicleDetectionEntry_del(ProbeVehicleDetectionEntry *p)
{
	if (p == NULL) return;
	ProbeVehicleDetectionEntry_purge(p);
	Dz1Free(p);
}

void ProbeVehicleDetectionEntry_dump(ProbeVehicleDetectionEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("veh_id = ")); Dz1Str_dump(p->veh_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("veh_class = ")); Dz1u8_dump(&p->veh_class, tab); 
		Dz1Thread_tprintf(tab, Dz1T("veh_timein = ")); Dz1Str_dump(p->veh_timein, tab); 
		Dz1Thread_tprintf(tab, Dz1T("veh_timeout = ")); Dz1Str_dump(p->veh_timeout, tab); 
		Dz1Thread_tprintf(tab, Dz1T("veh_traveltime = ")); Dz1u16_dump(&p->veh_traveltime, tab); 
		Dz1Thread_tprintf(tab, Dz1T("veh_avg_speed = ")); Dz1u16_dump(&p->veh_avg_speed, tab); 
		Dz1Thread_tprintf(tab, Dz1T("avi_id = ")); Dz1Str_dump(p->avi_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("avi_latitude = ")); Dz1s64_dump(&p->avi_latitude, tab); 
		Dz1Thread_tprintf(tab, Dz1T("avi_longitude = ")); Dz1u32_dump(&p->avi_longitude, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ref_avi_id = ")); Dz1Str_dump(p->ref_avi_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ref_avi_latitude = ")); Dz1s64_dump(&p->ref_avi_latitude, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ref_avi_longitude = ")); Dz1u32_dump(&p->ref_avi_longitude, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int ProbeVehicleDetectionEntry_cmp(ProbeVehicleDetectionEntry *a, ProbeVehicleDetectionEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->veh_id == NULL && b->veh_id == NULL) ret = 0;
	else if (a->veh_id == NULL /*&& b->veh_id != NULL*/) ret = -1;
	else if (/*a->veh_id != NULL &&*/ b->veh_id == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->veh_id, b->veh_id)) != 0) { }
	else if ((ret = Dz1u8_cmp(&a->veh_class, &b->veh_class)) != 0) { }
	return ret;
}
// ProbeVehicleDetectionEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ProbeVehicleDetectionList
static Dz1Error ProbeVehicleDetectionList_add(ProbeVehicleDetectionList *p, ProbeVehicleDetectionEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static bool_t ProbeVehicleDetectionList_remove(ProbeVehicleDetectionList *p, ProbeVehicleDetectionEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static ProbeVehicleDetectionEntry *ProbeVehicleDetectionList_extract(ProbeVehicleDetectionList *p, ProbeVehicleDetectionEntry *key)
{
	return (ProbeVehicleDetectionEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct ProbeVehicleDetectionListMkArrArg
{
	ProbeVehicleDetectionEntry **arr;
	unsigned int idx;
} ProbeVehicleDetectionListMkArrArg;

static Dz1Error _ProbeVehicleDetectionList_get_array(void *ptr, ProbeVehicleDetectionEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ProbeVehicleDetectionListMkArrArg *arg = (ProbeVehicleDetectionListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static ProbeVehicleDetectionEntry **ProbeVehicleDetectionList_get_array(ProbeVehicleDetectionList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	ProbeVehicleDetectionEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (ProbeVehicleDetectionEntry **)Dz1Calloc(sizeof(ProbeVehicleDetectionEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ProbeVehicleDetectionListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _ProbeVehicleDetectionList_get_array, (void *)&arg);
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

static Dz1Error ProbeVehicleDetectionList_travelForward(ProbeVehicleDetectionList *p, Dz1Error (*func)(void *ptr, ProbeVehicleDetectionEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error ProbeVehicleDetectionList_travelBackward(ProbeVehicleDetectionList *p, Dz1Error (*func)(void *ptr, ProbeVehicleDetectionEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static ProbeVehicleDetectionEntry *ProbeVehicleDetectionList_find(ProbeVehicleDetectionList *p, ProbeVehicleDetectionEntry *key)
{
	return (ProbeVehicleDetectionEntry *)Dz1AATree_find(p->storage, key);
}

static ProbeVehicleDetectionEntry *ProbeVehicleDetectionList_getHead(ProbeVehicleDetectionList *p)
{
	return (ProbeVehicleDetectionEntry *)Dz1AATree_getHead(p->storage);
}

static unsigned int ProbeVehicleDetectionList_count(ProbeVehicleDetectionList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

ProbeVehicleDetectionList *ProbeVehicleDetectionList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ProbeVehicleDetectionList *ret = (ProbeVehicleDetectionList *)Dz1Calloc(sizeof(ProbeVehicleDetectionList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ProbeVehicleDetectionList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)ProbeVehicleDetectionEntry_cmp,
				(Dz1DelFunc)ProbeVehicleDetectionEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = ProbeVehicleDetectionList_count;
			ret->travel = ProbeVehicleDetectionList_travelForward;
			ret->travelForward = ProbeVehicleDetectionList_travelForward;
			ret->travelBackward = ProbeVehicleDetectionList_travelBackward;
			ret->get_array = ProbeVehicleDetectionList_get_array;
			ret->add = ProbeVehicleDetectionList_add;
			ret->remove = ProbeVehicleDetectionList_remove;
			ret->find = ProbeVehicleDetectionList_find;
			ret->extract = ProbeVehicleDetectionList_extract;
			ret->getHead = ProbeVehicleDetectionList_getHead;
			ret->cmp = ProbeVehicleDetectionEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ProbeVehicleDetectionList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _ProbeVehicleDetectionList_clone(void *ptr, ProbeVehicleDetectionEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ProbeVehicleDetectionList *p = (ProbeVehicleDetectionList *)ptr;
	ProbeVehicleDetectionEntry *cloned = ProbeVehicleDetectionEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

ProbeVehicleDetectionList *ProbeVehicleDetectionList_clone(ProbeVehicleDetectionList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ProbeVehicleDetectionList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = ProbeVehicleDetectionList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ProbeVehicleDetectionList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_ProbeVehicleDetectionList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (ProbeVehicleDetectionList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ProbeVehicleDetectionList_purge(ProbeVehicleDetectionList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void ProbeVehicleDetectionList_del(ProbeVehicleDetectionList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _ProbeVehicleDetectionList_dump(void *ptr, ProbeVehicleDetectionEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); ProbeVehicleDetectionEntry_dump(p, tab);
	return err;
}

void ProbeVehicleDetectionList_dump(ProbeVehicleDetectionList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _ProbeVehicleDetectionList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ProbeVehicleDetectionList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DetectorCollectionEntry
DetectorCollectionEntry *DetectorCollectionEntry_new(Dz1Str detector_id, 
													 Dz1Str detector_time, 
													 u16_t speed_rate, 
													 u8_t occupancy_percent, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	DetectorCollectionEntry *__internal_ret = (DetectorCollectionEntry *)Dz1Calloc(sizeof(DetectorCollectionEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(DetectorCollectionEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (detector_id && (__internal_ret->detector_id = Dz1Str_clone(detector_id, errp)) == NULL) ERR_OUT(errp);
		else if (detector_time && (__internal_ret->detector_time = Dz1Str_clone(detector_time, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->speed_rate = speed_rate;
			__internal_ret->occupancy_percent = occupancy_percent;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (DetectorCollectionEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t DetectorCollectionEntry_copy(DetectorCollectionEntry *dst, DetectorCollectionEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->detector_id && (dst->detector_id = Dz1Str_clone(src->detector_id, errp)) == NULL) ERR_OUT(errp);
	else if (src->detector_time && (dst->detector_time = Dz1Str_clone(src->detector_time, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->speed_rate = src->speed_rate;
		dst->volume_rate = src->volume_rate;
		dst->occupancy_percent = src->occupancy_percent;
		dst->veh_q_len_qty = src->veh_q_len_qty;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

DetectorCollectionEntry *DetectorCollectionEntry_clone(DetectorCollectionEntry *src, Dz1Error *err)
{
	DetectorCollectionEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (DetectorCollectionEntry *)Dz1Calloc(sizeof(DetectorCollectionEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(DetectorCollectionEntry_delAndSetNull, (void *)&dst);
		if (DetectorCollectionEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (DetectorCollectionEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void DetectorCollectionEntry_purge(DetectorCollectionEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->detector_id);
	Dz1Str_del(p->detector_time);
}

void DetectorCollectionEntry_del(DetectorCollectionEntry *p)
{
	if (p == NULL) return;
	DetectorCollectionEntry_purge(p);
	Dz1Free(p);
}

void DetectorCollectionEntry_dump(DetectorCollectionEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("detector_id = ")); Dz1Str_dump(p->detector_id, tab); 
		Dz1Thread_tprintf(tab, Dz1T("detector_time = ")); Dz1Str_dump(p->detector_time, tab); 
		Dz1Thread_tprintf(tab, Dz1T("speed_rate = ")); Dz1u16_dump(&p->speed_rate, tab); 
		Dz1Thread_tprintf(tab, Dz1T("volume_rate = ")); Dz1u8_dump(&p->volume_rate, tab); 
		Dz1Thread_tprintf(tab, Dz1T("occupancy_percent = ")); Dz1u8_dump(&p->occupancy_percent, tab); 
		Dz1Thread_tprintf(tab, Dz1T("veh_q_len_qty = ")); Dz1u32_dump(&p->veh_q_len_qty, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int DetectorCollectionEntry_cmp(DetectorCollectionEntry *a, DetectorCollectionEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->detector_id == NULL && b->detector_id == NULL) ret = 0;
	else if (a->detector_id == NULL /*&& b->detector_id != NULL*/) ret = -1;
	else if (/*a->detector_id != NULL &&*/ b->detector_id == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->detector_id, b->detector_id)) != 0) { }
	return ret;
}
// DetectorCollectionEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DetectorCollectionList
static Dz1Error DetectorCollectionList_add(DetectorCollectionList *p, DetectorCollectionEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static bool_t DetectorCollectionList_remove(DetectorCollectionList *p, DetectorCollectionEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static DetectorCollectionEntry *DetectorCollectionList_extract(DetectorCollectionList *p, DetectorCollectionEntry *key)
{
	return (DetectorCollectionEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct DetectorCollectionListMkArrArg
{
	DetectorCollectionEntry **arr;
	unsigned int idx;
} DetectorCollectionListMkArrArg;

static Dz1Error _DetectorCollectionList_get_array(void *ptr, DetectorCollectionEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	DetectorCollectionListMkArrArg *arg = (DetectorCollectionListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static DetectorCollectionEntry **DetectorCollectionList_get_array(DetectorCollectionList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	DetectorCollectionEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (DetectorCollectionEntry **)Dz1Calloc(sizeof(DetectorCollectionEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		DetectorCollectionListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _DetectorCollectionList_get_array, (void *)&arg);
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

static Dz1Error DetectorCollectionList_travelForward(DetectorCollectionList *p, Dz1Error (*func)(void *ptr, DetectorCollectionEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error DetectorCollectionList_travelBackward(DetectorCollectionList *p, Dz1Error (*func)(void *ptr, DetectorCollectionEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static DetectorCollectionEntry *DetectorCollectionList_find(DetectorCollectionList *p, DetectorCollectionEntry *key)
{
	return (DetectorCollectionEntry *)Dz1AATree_find(p->storage, key);
}

static DetectorCollectionEntry *DetectorCollectionList_getHead(DetectorCollectionList *p)
{
	return (DetectorCollectionEntry *)Dz1AATree_getHead(p->storage);
}

static unsigned int DetectorCollectionList_count(DetectorCollectionList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

DetectorCollectionList *DetectorCollectionList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	DetectorCollectionList *ret = (DetectorCollectionList *)Dz1Calloc(sizeof(DetectorCollectionList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(DetectorCollectionList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)DetectorCollectionEntry_cmp,
				(Dz1DelFunc)DetectorCollectionEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = DetectorCollectionList_count;
			ret->travel = DetectorCollectionList_travelForward;
			ret->travelForward = DetectorCollectionList_travelForward;
			ret->travelBackward = DetectorCollectionList_travelBackward;
			ret->get_array = DetectorCollectionList_get_array;
			ret->add = DetectorCollectionList_add;
			ret->remove = DetectorCollectionList_remove;
			ret->find = DetectorCollectionList_find;
			ret->extract = DetectorCollectionList_extract;
			ret->getHead = DetectorCollectionList_getHead;
			ret->cmp = DetectorCollectionEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (DetectorCollectionList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _DetectorCollectionList_clone(void *ptr, DetectorCollectionEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	DetectorCollectionList *p = (DetectorCollectionList *)ptr;
	DetectorCollectionEntry *cloned = DetectorCollectionEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

DetectorCollectionList *DetectorCollectionList_clone(DetectorCollectionList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	DetectorCollectionList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = DetectorCollectionList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(DetectorCollectionList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_DetectorCollectionList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (DetectorCollectionList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void DetectorCollectionList_purge(DetectorCollectionList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void DetectorCollectionList_del(DetectorCollectionList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _DetectorCollectionList_dump(void *ptr, DetectorCollectionEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); DetectorCollectionEntry_dump(p, tab);
	return err;
}

void DetectorCollectionList_dump(DetectorCollectionList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _DetectorCollectionList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// DetectorCollectionList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ExtentionCommPDUEntry
ExtentionCommPDUEntry *ExtentionCommPDUEntry_new(u32_t idx, 
												 u32_t aid, 
												 time_t delivery_start, 
												 time_t delivery_stop, 
												 Dz1Binary *payload, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ExtentionCommPDUEntry *__internal_ret = (ExtentionCommPDUEntry *)Dz1Calloc(sizeof(ExtentionCommPDUEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(ExtentionCommPDUEntry_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->idx = idx;
		__internal_ret->aid = aid;
		__internal_ret->delivery_start = delivery_start;
		__internal_ret->delivery_stop = delivery_stop;
		__internal_ret->payload = payload;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ExtentionCommPDUEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t ExtentionCommPDUEntry_copy(ExtentionCommPDUEntry *dst, ExtentionCommPDUEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->payload && (dst->payload = Dz1Binary_clone(src->payload, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->idx = src->idx;
		dst->aid = src->aid;
		dst->delivery_start = src->delivery_start;
		dst->delivery_stop = src->delivery_stop;
		dst->signature = src->signature;
		dst->payload_type = src->payload_type;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

ExtentionCommPDUEntry *ExtentionCommPDUEntry_clone(ExtentionCommPDUEntry *src, Dz1Error *err)
{
	ExtentionCommPDUEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (ExtentionCommPDUEntry *)Dz1Calloc(sizeof(ExtentionCommPDUEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(ExtentionCommPDUEntry_delAndSetNull, (void *)&dst);
		if (ExtentionCommPDUEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ExtentionCommPDUEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void ExtentionCommPDUEntry_purge(ExtentionCommPDUEntry *p)
{
	if (p == NULL) return;
	Dz1Binary_del(p->payload);
}

void ExtentionCommPDUEntry_del(ExtentionCommPDUEntry *p)
{
	if (p == NULL) return;
	ExtentionCommPDUEntry_purge(p);
	Dz1Free(p);
}

void ExtentionCommPDUEntry_dump(ExtentionCommPDUEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("idx = ")); Dz1u32_dump(&p->idx, tab); 
		Dz1Thread_tprintf(tab, Dz1T("aid = ")); Dz1u32_dump(&p->aid, tab); 
		Dz1Thread_tprintf(tab, Dz1T("delivery_start = ")); time_dump(&p->delivery_start, tab); 
		Dz1Thread_tprintf(tab, Dz1T("delivery_stop = ")); time_dump(&p->delivery_stop, tab); 
		Dz1Thread_tprintf(tab, Dz1T("signature = ")); Dz1Bool_dump(&p->signature, tab); 
		Dz1Thread_tprintf(tab, Dz1T("payload_type = ")); Dz1s64_dump(&p->payload_type, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("payload = ")); Dz1Binary_dump(p->payload, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int ExtentionCommPDUEntry_cmp(ExtentionCommPDUEntry *a, ExtentionCommPDUEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->idx, &b->idx)) != 0) { }
	else if ((ret = Dz1u32_cmp(&a->aid, &b->aid)) != 0) { }
	return ret;
}
// ExtentionCommPDUEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ExtentionCommPDUList
static Dz1Error ExtentionCommPDUList_add(ExtentionCommPDUList *p, ExtentionCommPDUEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static bool_t ExtentionCommPDUList_remove(ExtentionCommPDUList *p, ExtentionCommPDUEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static ExtentionCommPDUEntry *ExtentionCommPDUList_extract(ExtentionCommPDUList *p, ExtentionCommPDUEntry *key)
{
	return (ExtentionCommPDUEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct ExtentionCommPDUListMkArrArg
{
	ExtentionCommPDUEntry **arr;
	unsigned int idx;
} ExtentionCommPDUListMkArrArg;

static Dz1Error _ExtentionCommPDUList_get_array(void *ptr, ExtentionCommPDUEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ExtentionCommPDUListMkArrArg *arg = (ExtentionCommPDUListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static ExtentionCommPDUEntry **ExtentionCommPDUList_get_array(ExtentionCommPDUList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	ExtentionCommPDUEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (ExtentionCommPDUEntry **)Dz1Calloc(sizeof(ExtentionCommPDUEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ExtentionCommPDUListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _ExtentionCommPDUList_get_array, (void *)&arg);
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

static Dz1Error ExtentionCommPDUList_travelForward(ExtentionCommPDUList *p, Dz1Error (*func)(void *ptr, ExtentionCommPDUEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error ExtentionCommPDUList_travelBackward(ExtentionCommPDUList *p, Dz1Error (*func)(void *ptr, ExtentionCommPDUEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static ExtentionCommPDUEntry *ExtentionCommPDUList_find(ExtentionCommPDUList *p, ExtentionCommPDUEntry *key)
{
	return (ExtentionCommPDUEntry *)Dz1AATree_find(p->storage, key);
}

static ExtentionCommPDUEntry *ExtentionCommPDUList_getHead(ExtentionCommPDUList *p)
{
	return (ExtentionCommPDUEntry *)Dz1AATree_getHead(p->storage);
}

static unsigned int ExtentionCommPDUList_count(ExtentionCommPDUList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

ExtentionCommPDUList *ExtentionCommPDUList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ExtentionCommPDUList *ret = (ExtentionCommPDUList *)Dz1Calloc(sizeof(ExtentionCommPDUList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ExtentionCommPDUList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)ExtentionCommPDUEntry_cmp,
				(Dz1DelFunc)ExtentionCommPDUEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = ExtentionCommPDUList_count;
			ret->travel = ExtentionCommPDUList_travelForward;
			ret->travelForward = ExtentionCommPDUList_travelForward;
			ret->travelBackward = ExtentionCommPDUList_travelBackward;
			ret->get_array = ExtentionCommPDUList_get_array;
			ret->add = ExtentionCommPDUList_add;
			ret->remove = ExtentionCommPDUList_remove;
			ret->find = ExtentionCommPDUList_find;
			ret->extract = ExtentionCommPDUList_extract;
			ret->getHead = ExtentionCommPDUList_getHead;
			ret->cmp = ExtentionCommPDUEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (ExtentionCommPDUList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _ExtentionCommPDUList_clone(void *ptr, ExtentionCommPDUEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ExtentionCommPDUList *p = (ExtentionCommPDUList *)ptr;
	ExtentionCommPDUEntry *cloned = ExtentionCommPDUEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

ExtentionCommPDUList *ExtentionCommPDUList_clone(ExtentionCommPDUList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ExtentionCommPDUList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = ExtentionCommPDUList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ExtentionCommPDUList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_ExtentionCommPDUList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (ExtentionCommPDUList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ExtentionCommPDUList_purge(ExtentionCommPDUList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void ExtentionCommPDUList_del(ExtentionCommPDUList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _ExtentionCommPDUList_dump(void *ptr, ExtentionCommPDUEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); ExtentionCommPDUEntry_dump(p, tab);
	return err;
}

void ExtentionCommPDUList_dump(ExtentionCommPDUList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _ExtentionCommPDUList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// ExtentionCommPDUList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation1_EamPresent
static struct TechnicalRegulation1_EamPresentMapA
{
	str_t str;
	TechnicalRegulation1_EamPresent v;
} TechnicalRegulation1_EamPresentMapA[] =
{
	{ (char *)"current_link_state", TechnicalRegulation1_EamPresent_current_link_state },
	{ (char *)"event_identity", TechnicalRegulation1_EamPresent_event_identity },
	{ (char *)"incident_identity", TechnicalRegulation1_EamPresent_incident_identity },
	{ (char *)"incident_conditions", TechnicalRegulation1_EamPresent_incident_conditions },
	{ (char *)"roadway_surface_status", TechnicalRegulation1_EamPresent_roadway_surface_status },
	{ (char *)"weather_information", TechnicalRegulation1_EamPresent_weather_information },
	{ (char *)"link_roadway_geometry", TechnicalRegulation1_EamPresent_link_roadway_geometry },
	{ (char *)"probe_vehicle_detection", TechnicalRegulation1_EamPresent_probe_vehicle_detection },
	{ (char *)"detector_collection", TechnicalRegulation1_EamPresent_detector_collection },
	{ (char *)"extention_comm_pdu", TechnicalRegulation1_EamPresent_extention_comm_pdu },
	{ NULL, TechnicalRegulation1_EamPresent_max }
};

str_t TechnicalRegulation1_EamPresentStrA(TechnicalRegulation1_EamPresent v)
{
	struct TechnicalRegulation1_EamPresentMapA *i = NULL;
	for (i = TechnicalRegulation1_EamPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

TechnicalRegulation1_EamPresent TechnicalRegulation1_EamPresentFromStrA(str_t str)
{
	struct TechnicalRegulation1_EamPresentMapA *i = NULL;
	for (i = TechnicalRegulation1_EamPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return TechnicalRegulation1_EamPresent_max;
}
#ifndef UNIX_SYSTEM
static struct TechnicalRegulation1_EamPresentMapW
{
	wstr_t str;
	TechnicalRegulation1_EamPresent v;
} TechnicalRegulation1_EamPresentMapW[] =
{
	{ (wchar_t *)L"current_link_state", TechnicalRegulation1_EamPresent_current_link_state },
	{ (wchar_t *)L"event_identity", TechnicalRegulation1_EamPresent_event_identity },
	{ (wchar_t *)L"incident_identity", TechnicalRegulation1_EamPresent_incident_identity },
	{ (wchar_t *)L"incident_conditions", TechnicalRegulation1_EamPresent_incident_conditions },
	{ (wchar_t *)L"roadway_surface_status", TechnicalRegulation1_EamPresent_roadway_surface_status },
	{ (wchar_t *)L"weather_information", TechnicalRegulation1_EamPresent_weather_information },
	{ (wchar_t *)L"link_roadway_geometry", TechnicalRegulation1_EamPresent_link_roadway_geometry },
	{ (wchar_t *)L"probe_vehicle_detection", TechnicalRegulation1_EamPresent_probe_vehicle_detection },
	{ (wchar_t *)L"detector_collection", TechnicalRegulation1_EamPresent_detector_collection },
	{ (wchar_t *)L"extention_comm_pdu", TechnicalRegulation1_EamPresent_extention_comm_pdu },
	{ NULL, TechnicalRegulation1_EamPresent_max }
};

wstr_t TechnicalRegulation1_EamPresentStrW(TechnicalRegulation1_EamPresent v)
{
	struct TechnicalRegulation1_EamPresentMapW *i = NULL;
	for (i = TechnicalRegulation1_EamPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

TechnicalRegulation1_EamPresent TechnicalRegulation1_EamPresentFromStrW(wstr_t str)
{
	struct TechnicalRegulation1_EamPresentMapW *i = NULL;
	for (i = TechnicalRegulation1_EamPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return TechnicalRegulation1_EamPresent_max;
}
#endif // UNIX_SYSTEM

TechnicalRegulation1_EamPresent *TechnicalRegulation1_EamPresent_new(TechnicalRegulation1_EamPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TechnicalRegulation1_EamPresent *__internal_ret = (TechnicalRegulation1_EamPresent *)Dz1Calloc(sizeof(TechnicalRegulation1_EamPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void TechnicalRegulation1_EamPresent_dump(TechnicalRegulation1_EamPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), TechnicalRegulation1_EamPresentStr(*v));
}
// TechnicalRegulation1_EamPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation1_Eam
TechnicalRegulation1_Eam *TechnicalRegulation1_Eam_new(TechnicalRegulation1_EamPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	TechnicalRegulation1_Eam *ret = (TechnicalRegulation1_Eam *)Dz1Calloc(sizeof(TechnicalRegulation1_Eam), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(TechnicalRegulation1_Eam_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case TechnicalRegulation1_EamPresent_current_link_state:
			// _U_cst_clone
			if (ptr != NULL) ret->x.current_link_state = (CurrentLinkStateList *)ptr;
			ERR_CLEAR(errp);
			break;
		case TechnicalRegulation1_EamPresent_event_identity:
			// _U_cst_clone
			if (ptr != NULL) ret->x.event_identity = (EventIdentityList *)ptr;
			ERR_CLEAR(errp);
			break;
		case TechnicalRegulation1_EamPresent_incident_identity:
			// _U_cst_clone
			if (ptr != NULL) ret->x.incident_identity = (IncidentIdentityList *)ptr;
			ERR_CLEAR(errp);
			break;
		case TechnicalRegulation1_EamPresent_incident_conditions:
			// _U_cst_clone
			if (ptr != NULL) ret->x.incident_conditions = (IncidentConditionsList *)ptr;
			ERR_CLEAR(errp);
			break;
		case TechnicalRegulation1_EamPresent_roadway_surface_status:
			// _U_cst_clone
			if (ptr != NULL) ret->x.roadway_surface_status = (RoadwaySurfaceStatusList *)ptr;
			ERR_CLEAR(errp);
			break;
		case TechnicalRegulation1_EamPresent_weather_information:
			// _U_cst_clone
			if (ptr != NULL) ret->x.weather_information = (WeatherInformationList *)ptr;
			ERR_CLEAR(errp);
			break;
		case TechnicalRegulation1_EamPresent_link_roadway_geometry:
			// _U_cst_clone
			if (ptr != NULL) ret->x.link_roadway_geometry = (LinkRoadwayGeometryList *)ptr;
			ERR_CLEAR(errp);
			break;
		case TechnicalRegulation1_EamPresent_probe_vehicle_detection:
			// _U_cst_clone
			if (ptr != NULL) ret->x.probe_vehicle_detection = (ProbeVehicleDetectionList *)ptr;
			ERR_CLEAR(errp);
			break;
		case TechnicalRegulation1_EamPresent_detector_collection:
			// _U_cst_clone
			if (ptr != NULL) ret->x.detector_collection = (DetectorCollectionList *)ptr;
			ERR_CLEAR(errp);
			break;
		case TechnicalRegulation1_EamPresent_extention_comm_pdu:
			// _U_cst_clone
			if (ptr != NULL) ret->x.extention_comm_pdu = (ExtentionCommPDUList *)ptr;
			ERR_CLEAR(errp);
			break;
		case TechnicalRegulation1_EamPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulation1_Eam_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t TechnicalRegulation1_Eam_copy(TechnicalRegulation1_Eam *ret, TechnicalRegulation1_Eam *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case TechnicalRegulation1_EamPresent_current_link_state:
			// _U_cst_clone
			if (src->x.current_link_state && (ret->x.current_link_state = CurrentLinkStateList_clone(src->x.current_link_state, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TechnicalRegulation1_EamPresent_event_identity:
			// _U_cst_clone
			if (src->x.event_identity && (ret->x.event_identity = EventIdentityList_clone(src->x.event_identity, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TechnicalRegulation1_EamPresent_incident_identity:
			// _U_cst_clone
			if (src->x.incident_identity && (ret->x.incident_identity = IncidentIdentityList_clone(src->x.incident_identity, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TechnicalRegulation1_EamPresent_incident_conditions:
			// _U_cst_clone
			if (src->x.incident_conditions && (ret->x.incident_conditions = IncidentConditionsList_clone(src->x.incident_conditions, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TechnicalRegulation1_EamPresent_roadway_surface_status:
			// _U_cst_clone
			if (src->x.roadway_surface_status && (ret->x.roadway_surface_status = RoadwaySurfaceStatusList_clone(src->x.roadway_surface_status, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TechnicalRegulation1_EamPresent_weather_information:
			// _U_cst_clone
			if (src->x.weather_information && (ret->x.weather_information = WeatherInformationList_clone(src->x.weather_information, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TechnicalRegulation1_EamPresent_link_roadway_geometry:
			// _U_cst_clone
			if (src->x.link_roadway_geometry && (ret->x.link_roadway_geometry = LinkRoadwayGeometryList_clone(src->x.link_roadway_geometry, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TechnicalRegulation1_EamPresent_probe_vehicle_detection:
			// _U_cst_clone
			if (src->x.probe_vehicle_detection && (ret->x.probe_vehicle_detection = ProbeVehicleDetectionList_clone(src->x.probe_vehicle_detection, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TechnicalRegulation1_EamPresent_detector_collection:
			// _U_cst_clone
			if (src->x.detector_collection && (ret->x.detector_collection = DetectorCollectionList_clone(src->x.detector_collection, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case TechnicalRegulation1_EamPresent_extention_comm_pdu:
			// _U_cst_clone
			if (src->x.extention_comm_pdu && (ret->x.extention_comm_pdu = ExtentionCommPDUList_clone(src->x.extention_comm_pdu, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

TechnicalRegulation1_Eam *TechnicalRegulation1_Eam_clone(TechnicalRegulation1_Eam *src, Dz1Error *err)
{
	TechnicalRegulation1_Eam *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (TechnicalRegulation1_Eam *)Dz1Calloc(sizeof(TechnicalRegulation1_Eam), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(TechnicalRegulation1_Eam_delAndSetNull, (void *)&ret);
		if (TechnicalRegulation1_Eam_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (TechnicalRegulation1_Eam_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void TechnicalRegulation1_Eam_purge(TechnicalRegulation1_Eam *p)
{
	if (!p) return;
	switch(p->present)
	{
	case TechnicalRegulation1_EamPresent_current_link_state:
		CurrentLinkStateList_del(p->x.current_link_state);
		break;
	case TechnicalRegulation1_EamPresent_event_identity:
		EventIdentityList_del(p->x.event_identity);
		break;
	case TechnicalRegulation1_EamPresent_incident_identity:
		IncidentIdentityList_del(p->x.incident_identity);
		break;
	case TechnicalRegulation1_EamPresent_incident_conditions:
		IncidentConditionsList_del(p->x.incident_conditions);
		break;
	case TechnicalRegulation1_EamPresent_roadway_surface_status:
		RoadwaySurfaceStatusList_del(p->x.roadway_surface_status);
		break;
	case TechnicalRegulation1_EamPresent_weather_information:
		WeatherInformationList_del(p->x.weather_information);
		break;
	case TechnicalRegulation1_EamPresent_link_roadway_geometry:
		LinkRoadwayGeometryList_del(p->x.link_roadway_geometry);
		break;
	case TechnicalRegulation1_EamPresent_probe_vehicle_detection:
		ProbeVehicleDetectionList_del(p->x.probe_vehicle_detection);
		break;
	case TechnicalRegulation1_EamPresent_detector_collection:
		DetectorCollectionList_del(p->x.detector_collection);
		break;
	case TechnicalRegulation1_EamPresent_extention_comm_pdu:
		ExtentionCommPDUList_del(p->x.extention_comm_pdu);
		break;
	default:
		break;
	}
}

void TechnicalRegulation1_Eam_del(TechnicalRegulation1_Eam *p)
{
	if (!p) return;
	TechnicalRegulation1_Eam_purge(p);
	Dz1Free(p);
}

void TechnicalRegulation1_Eam_dump(TechnicalRegulation1_Eam *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case TechnicalRegulation1_EamPresent_current_link_state:
		Dz1Thread_printf(Dz1T("current_link_state = ")); CurrentLinkStateList_dump(p->x.current_link_state, tab); 
		break;
	case TechnicalRegulation1_EamPresent_event_identity:
		Dz1Thread_printf(Dz1T("event_identity = ")); EventIdentityList_dump(p->x.event_identity, tab); 
		break;
	case TechnicalRegulation1_EamPresent_incident_identity:
		Dz1Thread_printf(Dz1T("incident_identity = ")); IncidentIdentityList_dump(p->x.incident_identity, tab); 
		break;
	case TechnicalRegulation1_EamPresent_incident_conditions:
		Dz1Thread_printf(Dz1T("incident_conditions = ")); IncidentConditionsList_dump(p->x.incident_conditions, tab); 
		break;
	case TechnicalRegulation1_EamPresent_roadway_surface_status:
		Dz1Thread_printf(Dz1T("roadway_surface_status = ")); RoadwaySurfaceStatusList_dump(p->x.roadway_surface_status, tab); 
		break;
	case TechnicalRegulation1_EamPresent_weather_information:
		Dz1Thread_printf(Dz1T("weather_information = ")); WeatherInformationList_dump(p->x.weather_information, tab); 
		break;
	case TechnicalRegulation1_EamPresent_link_roadway_geometry:
		Dz1Thread_printf(Dz1T("link_roadway_geometry = ")); LinkRoadwayGeometryList_dump(p->x.link_roadway_geometry, tab); 
		break;
	case TechnicalRegulation1_EamPresent_probe_vehicle_detection:
		Dz1Thread_printf(Dz1T("probe_vehicle_detection = ")); ProbeVehicleDetectionList_dump(p->x.probe_vehicle_detection, tab); 
		break;
	case TechnicalRegulation1_EamPresent_detector_collection:
		Dz1Thread_printf(Dz1T("detector_collection = ")); DetectorCollectionList_dump(p->x.detector_collection, tab); 
		break;
	case TechnicalRegulation1_EamPresent_extention_comm_pdu:
		Dz1Thread_printf(Dz1T("extention_comm_pdu = ")); ExtentionCommPDUList_dump(p->x.extention_comm_pdu, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// TechnicalRegulation1_Eam
////////////////////////////////////////////////////////////////////////////////


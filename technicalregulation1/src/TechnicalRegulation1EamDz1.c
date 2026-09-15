////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////
#include <dz1_gasn_support.h>
#include "TechnicalRegulation1EamDz1.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1CurrentLinkState
Dz1CurrentLinkState* Dz1CurrentLinkState_new(Dz1Asn1UTF8Str* link_LinkIdNumber,
	u16_t link_SpeedRate,
	u8_t tfdt_OccupancyPercent, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1CurrentLinkState* __internal_ret = (Dz1CurrentLinkState*)Dz1Calloc(sizeof(Dz1CurrentLinkState), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1CurrentLinkState_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->link_LinkIdNumber = link_LinkIdNumber;
		__internal_ret->link_SpeedRate = link_SpeedRate;
		__internal_ret->tfdt_OccupancyPercent = tfdt_OccupancyPercent;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1CurrentLinkState_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1CurrentLinkState* Dz1CurrentLinkState_clone(Dz1CurrentLinkState* src, Dz1Error* err)
{
	Dz1CurrentLinkState* ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1CurrentLinkState*)Dz1Calloc(sizeof(Dz1CurrentLinkState), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1CurrentLinkState_delAndSetNull, (void*)&ret);

		if (src->link_LinkIdNumber && (ret->link_LinkIdNumber = Dz1Asn1UTF8Str_clone(src->link_LinkIdNumber, errp)) == NULL) ERR_OUT(errp);
		else if (src->link_VolumeRate && (ret->link_VolumeRate = (u32_t*)Dz1Calloc(sizeof(u32_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->link_DensityRate && (ret->link_DensityRate = (u16_t*)Dz1Calloc(sizeof(u16_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->link_TravelTimeQuantity && (ret->link_TravelTimeQuantity = (u16_t*)Dz1Calloc(sizeof(u16_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->link_DelayQuantity && (ret->link_DelayQuantity = (u16_t*)Dz1Calloc(sizeof(u16_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->tfdt_VehicleQueueLengthQuantity && (ret->tfdt_VehicleQueueLengthQuantity = (u32_t*)Dz1Calloc(sizeof(u32_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			ret->link_SpeedRate = src->link_SpeedRate;
			if (src->link_VolumeRate != NULL && ret->link_VolumeRate != NULL) *ret->link_VolumeRate = *src->link_VolumeRate;
			if (src->link_DensityRate != NULL && ret->link_DensityRate != NULL) *ret->link_DensityRate = *src->link_DensityRate;
			if (src->link_TravelTimeQuantity != NULL && ret->link_TravelTimeQuantity != NULL) *ret->link_TravelTimeQuantity = *src->link_TravelTimeQuantity;
			if (src->link_DelayQuantity != NULL && ret->link_DelayQuantity != NULL) *ret->link_DelayQuantity = *src->link_DelayQuantity;
			if (src->tfdt_VehicleQueueLengthQuantity != NULL && ret->tfdt_VehicleQueueLengthQuantity != NULL) *ret->tfdt_VehicleQueueLengthQuantity = *src->tfdt_VehicleQueueLengthQuantity;
			ret->tfdt_OccupancyPercent = src->tfdt_OccupancyPercent;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1CurrentLinkState_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1CurrentLinkState_del(Dz1CurrentLinkState* p)
{
	if (p == NULL) return;
	if (p->link_LinkIdNumber) Dz1Asn1UTF8Str_del(p->link_LinkIdNumber);
	if (p->link_VolumeRate) Dz1Free(p->link_VolumeRate);
	if (p->link_DensityRate) Dz1Free(p->link_DensityRate);
	if (p->link_TravelTimeQuantity) Dz1Free(p->link_TravelTimeQuantity);
	if (p->link_DelayQuantity) Dz1Free(p->link_DelayQuantity);
	if (p->tfdt_VehicleQueueLengthQuantity) Dz1Free(p->tfdt_VehicleQueueLengthQuantity);
	Dz1Free(p);
}

void Dz1CurrentLinkState_dump(Dz1CurrentLinkState* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	if (p->link_LinkIdNumber == NULL) Dz1Thread_tprintf(tab, Dz1T("link_LinkIdNumber = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("link_LinkIdNumber = ")); Dz1Asn1UTF8Str_dump(p->link_LinkIdNumber, tab); /* using dump func */ }

	Dz1Thread_tprintf(tab, Dz1T("link_SpeedRate = ")); Dz1u16_dump(&p->link_SpeedRate, tab);

	if (p->link_VolumeRate == NULL) Dz1Thread_tprintf(tab, Dz1T("link_VolumeRate = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("link_VolumeRate = ")); Dz1u32_dump(p->link_VolumeRate, tab); }

	if (p->link_DensityRate == NULL) Dz1Thread_tprintf(tab, Dz1T("link_DensityRate = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("link_DensityRate = ")); Dz1u16_dump(p->link_DensityRate, tab); }

	if (p->link_TravelTimeQuantity == NULL) Dz1Thread_tprintf(tab, Dz1T("link_TravelTimeQuantity = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("link_TravelTimeQuantity = ")); Dz1u16_dump(p->link_TravelTimeQuantity, tab); }

	if (p->link_DelayQuantity == NULL) Dz1Thread_tprintf(tab, Dz1T("link_DelayQuantity = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("link_DelayQuantity = ")); Dz1u16_dump(p->link_DelayQuantity, tab); }

	if (p->tfdt_VehicleQueueLengthQuantity == NULL) Dz1Thread_tprintf(tab, Dz1T("tfdt_VehicleQueueLengthQuantity = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("tfdt_VehicleQueueLengthQuantity = ")); Dz1u32_dump(p->tfdt_VehicleQueueLengthQuantity, tab); }

	Dz1Thread_tprintf(tab, Dz1T("tfdt_OccupancyPercent = ")); Dz1u8_dump(&p->tfdt_OccupancyPercent, tab);

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
void Dz1CurrentLinkState_fdump(FILE* fp, Dz1CurrentLinkState* p, int tab)
{
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;

	if (p->link_LinkIdNumber == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("link_LinkIdNumber = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("link_LinkIdNumber = ")); Dz1Asn1UTF8Str_fdump(fp, p->link_LinkIdNumber, tab); }

	Dz1Thread_ftprintf(fp, tab, Dz1T("link_SpeedRate = ")); Dz1u16_fdump(fp, &p->link_SpeedRate, tab);

	if (p->link_VolumeRate == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("link_VolumeRate = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("link_VolumeRate = ")); Dz1u32_fdump(fp, p->link_VolumeRate, tab); }

	if (p->link_DensityRate == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("link_DensityRate = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("link_DensityRate = ")); Dz1u16_fdump(fp, p->link_DensityRate, tab); }

	if (p->link_TravelTimeQuantity == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("link_TravelTimeQuantity = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("link_TravelTimeQuantity = ")); Dz1u16_fdump(fp, p->link_TravelTimeQuantity, tab); }

	if (p->link_DelayQuantity == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("link_DelayQuantity = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("link_DelayQuantity = ")); Dz1u16_fdump(fp, p->link_DelayQuantity, tab); }

	if (p->tfdt_VehicleQueueLengthQuantity == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("tfdt_VehicleQueueLengthQuantity = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("tfdt_VehicleQueueLengthQuantity = ")); Dz1u32_fdump(fp, p->tfdt_VehicleQueueLengthQuantity, tab); }

	Dz1Thread_ftprintf(fp, tab, Dz1T("tfdt_OccupancyPercent = ")); Dz1u8_fdump(fp, &p->tfdt_OccupancyPercent, tab);

	Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
}
Dz1Error Dz1CurrentLinkState_fromASN(Dz1CurrentLinkState* dst, CurrentLinkState* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((dst->link_LinkIdNumber = Dz1Asn1UTF8Str_newFromASN(&src->link_LinkIdNumber, &err)) == NULL) { Dz1Thread_printf("link_LinkIdNumber : "); ERR_OUT(&err); }
		else if ((err = u16_t_fromASN(&dst->link_SpeedRate, &src->link_SpeedRate)).code) { Dz1Thread_printf("link_SpeedRate : "); ERR_OUT(&err); }
		else if (src->DEF_CurrentLinkState_link_VolumeRate && (dst->link_VolumeRate = u32_t_newFromASN(&src->link_VolumeRate, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_CurrentLinkState_link_DensityRate && (dst->link_DensityRate = u16_t_newFromASN(&src->link_DensityRate, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_CurrentLinkState_link_TravelTimeQuantity && (dst->link_TravelTimeQuantity = u16_t_newFromASN(&src->link_TravelTimeQuantity, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_CurrentLinkState_link_DelayQuantity && (dst->link_DelayQuantity = u16_t_newFromASN(&src->link_DelayQuantity, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_CurrentLinkState_tfdt_VehicleQueueLengthQuantity && (dst->tfdt_VehicleQueueLengthQuantity = u32_t_newFromASN(&src->tfdt_VehicleQueueLengthQuantity, &err)) == NULL) ERR_OUT(&err);
		else if ((err = u8_t_fromASN(&dst->tfdt_OccupancyPercent, &src->tfdt_OccupancyPercent)).code) { Dz1Thread_printf("tfdt_OccupancyPercent : "); ERR_OUT(&err); }
		else
		{
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1CurrentLinkState, CurrentLinkState)

Dz1Error Dz1CurrentLinkState_toASN(CurrentLinkState* dst, Dz1CurrentLinkState* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = Dz1Asn1UTF8Str_toASN(&dst->link_LinkIdNumber, src->link_LinkIdNumber, ws)).code) { Dz1Thread_printf("link_LinkIdNumber : "); ERR_OUT(&err); }
		else if ((err = u16_t_toASN(&dst->link_SpeedRate, &src->link_SpeedRate, ws)).code) { Dz1Thread_printf("link_SpeedRate : "); ERR_OUT(&err); }
		else if ((dst->DEF_CurrentLinkState_link_VolumeRate = src->link_VolumeRate ? 1 : 0) == 1 && (err = u32_t_toASN(&dst->link_VolumeRate, src->link_VolumeRate, ws)).code) { Dz1Thread_printf("link_VolumeRate : "); ERR_OUT(&err); }
		else if ((dst->DEF_CurrentLinkState_link_DensityRate = src->link_DensityRate ? 1 : 0) == 1 && (err = u16_t_toASN(&dst->link_DensityRate, src->link_DensityRate, ws)).code) { Dz1Thread_printf("link_DensityRate : "); ERR_OUT(&err); }
		else if ((dst->DEF_CurrentLinkState_link_TravelTimeQuantity = src->link_TravelTimeQuantity ? 1 : 0) == 1 && (err = u16_t_toASN(&dst->link_TravelTimeQuantity, src->link_TravelTimeQuantity, ws)).code) { Dz1Thread_printf("link_TravelTimeQuantity : "); ERR_OUT(&err); }
		else if ((dst->DEF_CurrentLinkState_link_DelayQuantity = src->link_DelayQuantity ? 1 : 0) == 1 && (err = u16_t_toASN(&dst->link_DelayQuantity, src->link_DelayQuantity, ws)).code) { Dz1Thread_printf("link_DelayQuantity : "); ERR_OUT(&err); }
		else if ((dst->DEF_CurrentLinkState_tfdt_VehicleQueueLengthQuantity = src->tfdt_VehicleQueueLengthQuantity ? 1 : 0) == 1 && (err = u32_t_toASN(&dst->tfdt_VehicleQueueLengthQuantity, src->tfdt_VehicleQueueLengthQuantity, ws)).code) { Dz1Thread_printf("tfdt_VehicleQueueLengthQuantity : "); ERR_OUT(&err); }
		else if ((err = u8_t_toASN(&dst->tfdt_OccupancyPercent, &src->tfdt_OccupancyPercent, ws)).code) { Dz1Thread_printf("tfdt_OccupancyPercent : "); ERR_OUT(&err); }
		else
		{
		}
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1CurrentLinkState, CurrentLinkState)
// Dz1CurrentLinkState
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CurrentLinkStateResponse
static Dz1Error Dz1CurrentLinkStateResponse_add(Dz1CurrentLinkStateResponse* p, Dz1CurrentLinkState* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1CurrentLinkStateResponseMkArrArg
{
	Dz1CurrentLinkState** arr;
	unsigned int idx;
} Dz1CurrentLinkStateResponseMkArrArg;

static Dz1Error _Dz1CurrentLinkStateResponse_get_array(void* ptr, Dz1CurrentLinkState* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1CurrentLinkStateResponseMkArrArg* arg = (Dz1CurrentLinkStateResponseMkArrArg*)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1CurrentLinkState** Dz1CurrentLinkStateResponse_get_array(Dz1CurrentLinkStateResponse* p, unsigned int* ret_cnt, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err == NULL ? &_err : err;
	Dz1CurrentLinkState** ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1CurrentLinkState**)Dz1Calloc(sizeof(Dz1CurrentLinkState*), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1CurrentLinkStateResponseMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void*)ret);

		*errp = p->travel(p, _Dz1CurrentLinkStateResponse_get_array, (void*)&arg);
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

static Dz1Error Dz1CurrentLinkStateResponse_travelForward(Dz1CurrentLinkStateResponse* p, Dz1Error(*func)(void* ptr, Dz1CurrentLinkState* data), void* ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1CurrentLinkStateResponse_travelBackward(Dz1CurrentLinkStateResponse* p, Dz1Error(*func)(void* ptr, Dz1CurrentLinkState* data), void* ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1CurrentLinkStateResponse_count(Dz1CurrentLinkStateResponse* p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1CurrentLinkStateResponse* Dz1CurrentLinkStateResponse_new(Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1CurrentLinkStateResponse* ret = (Dz1CurrentLinkStateResponse*)Dz1Calloc(sizeof(Dz1CurrentLinkStateResponse), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CurrentLinkStateResponse_delAndSetNull, (void*)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
			(Dz1DelFunc)Dz1CurrentLinkState_del,
			NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = Dz1CurrentLinkStateResponse_add;
			ret->get_array = Dz1CurrentLinkStateResponse_get_array;
			ret->travel = Dz1CurrentLinkStateResponse_travelForward;
			ret->travelForward = Dz1CurrentLinkStateResponse_travelForward;
			ret->travelBackward = Dz1CurrentLinkStateResponse_travelBackward;
			ret->count = Dz1CurrentLinkStateResponse_count;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1CurrentLinkStateResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1CurrentLinkStateResponse_clone(void* ptr, Dz1CurrentLinkState* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1CurrentLinkStateResponse* p = (Dz1CurrentLinkStateResponse*)ptr;
	Dz1CurrentLinkState* cloned = Dz1CurrentLinkState_clone(data, &err);
	err = Dz1Fifo_push(p->storage, cloned);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1CurrentLinkStateResponse* Dz1CurrentLinkStateResponse_clone(Dz1CurrentLinkStateResponse* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1CurrentLinkStateResponse* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1CurrentLinkStateResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CurrentLinkStateResponse_delAndSetNull, (void*)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1CurrentLinkStateResponse_clone, (void*)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1CurrentLinkStateResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1CurrentLinkStateResponse_del(Dz1CurrentLinkStateResponse* p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1CurrentLinkStateResponse_dump(void* ptr, Dz1CurrentLinkState* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	int tab = *(int*)ptr;
	Dz1Thread_tprintf(tab, Dz1T("entry = "));
	Dz1CurrentLinkState_dump(p, tab);
	return err;
}

void Dz1CurrentLinkStateResponse_dump(Dz1CurrentLinkStateResponse* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;
	p->travel(p, _Dz1CurrentLinkStateResponse_dump, (void*)&tab);
	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
typedef struct Dz1CurrentLinkStateResponseFDumpArg
{
	FILE* fp;
	int tab;
} Dz1CurrentLinkStateResponseFDumpArg;

static Dz1Error _Dz1CurrentLinkStateResponse_fdump(void* ptr, Dz1CurrentLinkState* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1CurrentLinkStateResponseFDumpArg* arg = (Dz1CurrentLinkStateResponseFDumpArg*)ptr;
	Dz1Thread_ftprintf(arg->fp, arg->tab, Dz1T("entry = "));
	Dz1CurrentLinkState_fdump(arg->fp, p, arg->tab);
	return err;
}

void Dz1CurrentLinkStateResponse_fdump(FILE* fp, Dz1CurrentLinkStateResponse* p, int tab)
{
	Dz1CurrentLinkStateResponseFDumpArg arg = { fp, tab };
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
	p->travel(p, _Dz1CurrentLinkStateResponse_fdump, (void*)&arg);
	Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
}
PSEUDO_LIST_FROM_ASN(Dz1CurrentLinkStateResponse, Dz1CurrentLinkState, CurrentLinkState)
DZ1_NEW_LIST_FROM_ASN(Dz1CurrentLinkStateResponse, ASN1List)

PSEUDO_ENTRY_TO_ASN(Dz1CurrentLinkStateResponse, Dz1CurrentLinkState, CurrentLinkState)
PSEUDO_LIST_TO_ASN(Dz1CurrentLinkStateResponse)
DZ1_TO_NEW_ASN_LIST(Dz1CurrentLinkStateResponse, ASN1List)

// Dz1CurrentLinkStateResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1EventIdentity_evnt_DescriptionTypeEventCode
static struct Dz1EventIdentity_evnt_DescriptionTypeEventCodeMapA
{
	str_t str;
	Dz1EventIdentity_evnt_DescriptionTypeEventCode v;
} Dz1EventIdentity_evnt_DescriptionTypeEventCodeMapA[] =
{
	{ (char*)"none", Dz1EventIdentity_evnt_DescriptionTypeEventCode_none },
	{ (char*)"other", Dz1EventIdentity_evnt_DescriptionTypeEventCode_other },
	{ (char*)"constructions", Dz1EventIdentity_evnt_DescriptionTypeEventCode_constructions },
	{ (char*)"planned_roadway_closure", Dz1EventIdentity_evnt_DescriptionTypeEventCode_planned_roadway_closure },
	{ (char*)"special_event", Dz1EventIdentity_evnt_DescriptionTypeEventCode_special_event },
	{ NULL, Dz1EventIdentity_evnt_DescriptionTypeEventCode_max }
};

str_t Dz1EventIdentity_evnt_DescriptionTypeEventCodeStrA(Dz1EventIdentity_evnt_DescriptionTypeEventCode v)
{
	struct Dz1EventIdentity_evnt_DescriptionTypeEventCodeMapA* i = NULL;
	for (i = Dz1EventIdentity_evnt_DescriptionTypeEventCodeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1EventIdentity_evnt_DescriptionTypeEventCode Dz1EventIdentity_evnt_DescriptionTypeEventCodeFromStrA(str_t str)
{
	struct Dz1EventIdentity_evnt_DescriptionTypeEventCodeMapA* i = NULL;
	for (i = Dz1EventIdentity_evnt_DescriptionTypeEventCodeMapA; i->str; i++)
		if (strcmp(i->str, str) == 0) return i->v;
	return Dz1EventIdentity_evnt_DescriptionTypeEventCode_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1EventIdentity_evnt_DescriptionTypeEventCodeMapW
{
	wstr_t str;
	Dz1EventIdentity_evnt_DescriptionTypeEventCode v;
} Dz1EventIdentity_evnt_DescriptionTypeEventCodeMapW[] =
{
	{ (wchar_t*)L"none", Dz1EventIdentity_evnt_DescriptionTypeEventCode_none },
	{ (wchar_t*)L"other", Dz1EventIdentity_evnt_DescriptionTypeEventCode_other },
	{ (wchar_t*)L"constructions", Dz1EventIdentity_evnt_DescriptionTypeEventCode_constructions },
	{ (wchar_t*)L"planned_roadway_closure", Dz1EventIdentity_evnt_DescriptionTypeEventCode_planned_roadway_closure },
	{ (wchar_t*)L"special_event", Dz1EventIdentity_evnt_DescriptionTypeEventCode_special_event },
	{ NULL, Dz1EventIdentity_evnt_DescriptionTypeEventCode_max }
};

wstr_t Dz1EventIdentity_evnt_DescriptionTypeEventCodeStrW(Dz1EventIdentity_evnt_DescriptionTypeEventCode v)
{
	struct Dz1EventIdentity_evnt_DescriptionTypeEventCodeMapW* i = NULL;
	for (i = Dz1EventIdentity_evnt_DescriptionTypeEventCodeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1EventIdentity_evnt_DescriptionTypeEventCode Dz1EventIdentity_evnt_DescriptionTypeEventCodeFromStrW(wstr_t str)
{
	struct Dz1EventIdentity_evnt_DescriptionTypeEventCodeMapW* i = NULL;
	for (i = Dz1EventIdentity_evnt_DescriptionTypeEventCodeMapW; i->str; i++)
		if (wcscmp(i->str, str) == 0) return i->v;
	return Dz1EventIdentity_evnt_DescriptionTypeEventCode_max;
}
#endif // UNIX_SYSTEM

Dz1EventIdentity_evnt_DescriptionTypeEventCode* Dz1EventIdentity_evnt_DescriptionTypeEventCode_new(Dz1EventIdentity_evnt_DescriptionTypeEventCode* src, Dz1Error* err) {
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1EventIdentity_evnt_DescriptionTypeEventCode* __internal_ret = (Dz1EventIdentity_evnt_DescriptionTypeEventCode*)Dz1Calloc(sizeof(Dz1EventIdentity_evnt_DescriptionTypeEventCode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
	}
	return __internal_ret;
}

void Dz1EventIdentity_evnt_DescriptionTypeEventCode_dump(Dz1EventIdentity_evnt_DescriptionTypeEventCode* v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1EventIdentity_evnt_DescriptionTypeEventCodeStr(*v));
}
void Dz1EventIdentity_evnt_DescriptionTypeEventCode_fdump(FILE* fp, Dz1EventIdentity_evnt_DescriptionTypeEventCode* v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), Dz1EventIdentity_evnt_DescriptionTypeEventCodeStr(*v));
}
// Dz1EventIdentity_evnt_DescriptionTypeEventCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode
static struct Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeMapA
{
	str_t str;
	Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode v;
} Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeMapA[] =
{
	{ (char*)"none", Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_none },
	{ (char*)"other", Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_other },
	{ (char*)"parade", Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_parade },
	{ (char*)"sporting_event", Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_sporting_event },
	{ (char*)"demonstration", Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_demonstration },
	{ (char*)"festival", Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_festival },
	{ (char*)"performing_arts", Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_performing_arts },
	{ (char*)"dignitary_visit", Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_dignitary_visit },
	{ NULL, Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_max }
};

str_t Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeStrA(Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode v)
{
	struct Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeMapA* i = NULL;
	for (i = Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeFromStrA(str_t str)
{
	struct Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeMapA* i = NULL;
	for (i = Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeMapA; i->str; i++)
		if (strcmp(i->str, str) == 0) return i->v;
	return Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeMapW
{
	wstr_t str;
	Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode v;
} Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeMapW[] =
{
	{ (wchar_t*)L"none", Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_none },
	{ (wchar_t*)L"other", Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_other },
	{ (wchar_t*)L"parade", Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_parade },
	{ (wchar_t*)L"sporting_event", Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_sporting_event },
	{ (wchar_t*)L"demonstration", Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_demonstration },
	{ (wchar_t*)L"festival", Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_festival },
	{ (wchar_t*)L"performing_arts", Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_performing_arts },
	{ (wchar_t*)L"dignitary_visit", Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_dignitary_visit },
	{ NULL, Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_max }
};

wstr_t Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeStrW(Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode v)
{
	struct Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeMapW* i = NULL;
	for (i = Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeFromStrW(wstr_t str)
{
	struct Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeMapW* i = NULL;
	for (i = Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeMapW; i->str; i++)
		if (wcscmp(i->str, str) == 0) return i->v;
	return Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_max;
}
#endif // UNIX_SYSTEM

Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode* Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_new(Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode* src, Dz1Error* err) {
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode* __internal_ret = (Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode*)Dz1Calloc(sizeof(Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
	}
	return __internal_ret;
}

void Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_dump(Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode* v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeStr(*v));
}
void Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_fdump(FILE* fp, Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode* v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeStr(*v));
}
// Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode
static struct Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeMapA
{
	str_t str;
	Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode v;
} Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeMapA[] =
{
	{ (char*)"none", Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_none },
	{ (char*)"other", Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_other },
	{ (char*)"long_term_construction", Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_long_term_construction },
	{ (char*)"short_term_construction", Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_short_term_construction },
	{ (char*)"maintenance", Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_maintenance },
	{ (char*)"emergency_maintenance", Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_emergency_maintenance },
	{ NULL, Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_max }
};

str_t Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeStrA(Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode v)
{
	struct Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeMapA* i = NULL;
	for (i = Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeFromStrA(str_t str)
{
	struct Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeMapA* i = NULL;
	for (i = Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeMapA; i->str; i++)
		if (strcmp(i->str, str) == 0) return i->v;
	return Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeMapW
{
	wstr_t str;
	Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode v;
} Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeMapW[] =
{
	{ (wchar_t*)L"none", Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_none },
	{ (wchar_t*)L"other", Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_other },
	{ (wchar_t*)L"long_term_construction", Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_long_term_construction },
	{ (wchar_t*)L"short_term_construction", Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_short_term_construction },
	{ (wchar_t*)L"maintenance", Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_maintenance },
	{ (wchar_t*)L"emergency_maintenance", Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_emergency_maintenance },
	{ NULL, Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_max }
};

wstr_t Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeStrW(Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode v)
{
	struct Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeMapW* i = NULL;
	for (i = Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeFromStrW(wstr_t str)
{
	struct Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeMapW* i = NULL;
	for (i = Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeMapW; i->str; i++)
		if (wcscmp(i->str, str) == 0) return i->v;
	return Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_max;
}
#endif // UNIX_SYSTEM

Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode* Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_new(Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode* src, Dz1Error* err) {
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode* __internal_ret = (Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode*)Dz1Calloc(sizeof(Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
	}
	return __internal_ret;
}

void Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_dump(Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode* v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeStr(*v));
}
void Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_fdump(FILE* fp, Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode* v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeStr(*v));
}
// Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1EventIdentity
Dz1EventIdentity* Dz1EventIdentity_new(Dz1Asn1UTF8Str* node_NodeIdNumber,
	Dz1Asn1UTF8Str* link_LinkIdNumber,
	Dz1Asn1UTF8Str* evnt_LocationJurisDictionNameText,
	Dz1Asn1UTF8Str* evnt_LocationLinkIdNumber,
	Dz1Asn1UTF8Str* evnt_LocationNodeIdNumber,
	Dz1Asn1UTF8Str* evnt_LocationRoadwayNameText,
	u8_t evnt_LanesBlockedOrClosedNumber,
	Dz1Asn1BitStr* evnt_LanesShouldersBlockedCode,
	Dz1Asn1VisibleStr* evnt_TimelineStartGeneralizedTime,
	Dz1Asn1VisibleStr* evnt_TimelineEndGeneralizedTime,
	u32_t evnt_TimelineDurationTime, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1EventIdentity* __internal_ret = (Dz1EventIdentity*)Dz1Calloc(sizeof(Dz1EventIdentity), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1EventIdentity_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->node_NodeIdNumber = node_NodeIdNumber;
		__internal_ret->link_LinkIdNumber = link_LinkIdNumber;
		__internal_ret->evnt_LocationJurisDictionNameText = evnt_LocationJurisDictionNameText;
		__internal_ret->evnt_LocationLinkIdNumber = evnt_LocationLinkIdNumber;
		__internal_ret->evnt_LocationNodeIdNumber = evnt_LocationNodeIdNumber;
		__internal_ret->evnt_LocationRoadwayNameText = evnt_LocationRoadwayNameText;
		__internal_ret->evnt_LanesBlockedOrClosedNumber = evnt_LanesBlockedOrClosedNumber;
		__internal_ret->evnt_LanesShouldersBlockedCode = evnt_LanesShouldersBlockedCode;
		__internal_ret->evnt_TimelineStartGeneralizedTime = evnt_TimelineStartGeneralizedTime;
		__internal_ret->evnt_TimelineEndGeneralizedTime = evnt_TimelineEndGeneralizedTime;
		__internal_ret->evnt_TimelineDurationTime = evnt_TimelineDurationTime;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1EventIdentity_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1EventIdentity* Dz1EventIdentity_clone(Dz1EventIdentity* src, Dz1Error* err)
{
	Dz1EventIdentity* ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1EventIdentity*)Dz1Calloc(sizeof(Dz1EventIdentity), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1EventIdentity_delAndSetNull, (void*)&ret);

		if (src->node_NodeIdNumber && (ret->node_NodeIdNumber = Dz1Asn1UTF8Str_clone(src->node_NodeIdNumber, errp)) == NULL) ERR_OUT(errp);
		else if (src->link_LinkIdNumber && (ret->link_LinkIdNumber = Dz1Asn1UTF8Str_clone(src->link_LinkIdNumber, errp)) == NULL) ERR_OUT(errp);
		else if (src->evnt_IdentificationNumber && (ret->evnt_IdentificationNumber = (u32_t*)Dz1Calloc(sizeof(u32_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->evnt_LocationJurisDictionNameText && (ret->evnt_LocationJurisDictionNameText = Dz1Asn1UTF8Str_clone(src->evnt_LocationJurisDictionNameText, errp)) == NULL) ERR_OUT(errp);
		else if (src->evnt_LocationLinkIdNumber && (ret->evnt_LocationLinkIdNumber = Dz1Asn1UTF8Str_clone(src->evnt_LocationLinkIdNumber, errp)) == NULL) ERR_OUT(errp);
		else if (src->evnt_LocationNodeIdNumber && (ret->evnt_LocationNodeIdNumber = Dz1Asn1UTF8Str_clone(src->evnt_LocationNodeIdNumber, errp)) == NULL) ERR_OUT(errp);
		else if (src->evnt_LocationRoadwayNameText && (ret->evnt_LocationRoadwayNameText = Dz1Asn1UTF8Str_clone(src->evnt_LocationRoadwayNameText, errp)) == NULL) ERR_OUT(errp);
		else if (src->evnt_DescriptionTypeEventCode && (ret->evnt_DescriptionTypeEventCode = (Dz1EventIdentity_evnt_DescriptionTypeEventCode*)Dz1Calloc(sizeof(Dz1EventIdentity_evnt_DescriptionTypeEventCode), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->evnt_DescriptionTypeSpecialEventCode && (ret->evnt_DescriptionTypeSpecialEventCode = (Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode*)Dz1Calloc(sizeof(Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->evnt_DescriptionPlannedRoadWayClosureCode && (ret->evnt_DescriptionPlannedRoadWayClosureCode = (Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode*)Dz1Calloc(sizeof(Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->evnt_LanesShouldersBlockedCode && (ret->evnt_LanesShouldersBlockedCode = Dz1Asn1BitStr_clone(src->evnt_LanesShouldersBlockedCode, errp)) == NULL) ERR_OUT(errp);
		else if (src->evnt_TimelineStartGeneralizedTime && (ret->evnt_TimelineStartGeneralizedTime = Dz1Asn1VisibleStr_clone(src->evnt_TimelineStartGeneralizedTime, errp)) == NULL) ERR_OUT(errp);
		else if (src->evnt_TimelineEndGeneralizedTime && (ret->evnt_TimelineEndGeneralizedTime = Dz1Asn1VisibleStr_clone(src->evnt_TimelineEndGeneralizedTime, errp)) == NULL) ERR_OUT(errp);
		else
		{
			if (src->evnt_IdentificationNumber != NULL && ret->evnt_IdentificationNumber != NULL) *ret->evnt_IdentificationNumber = *src->evnt_IdentificationNumber;
			if (src->evnt_DescriptionTypeEventCode != NULL && ret->evnt_DescriptionTypeEventCode != NULL) *ret->evnt_DescriptionTypeEventCode = *src->evnt_DescriptionTypeEventCode;
			if (src->evnt_DescriptionTypeSpecialEventCode != NULL && ret->evnt_DescriptionTypeSpecialEventCode != NULL) *ret->evnt_DescriptionTypeSpecialEventCode = *src->evnt_DescriptionTypeSpecialEventCode;
			if (src->evnt_DescriptionPlannedRoadWayClosureCode != NULL && ret->evnt_DescriptionPlannedRoadWayClosureCode != NULL) *ret->evnt_DescriptionPlannedRoadWayClosureCode = *src->evnt_DescriptionPlannedRoadWayClosureCode;
			ret->evnt_LanesBlockedOrClosedNumber = src->evnt_LanesBlockedOrClosedNumber;
			ret->evnt_TimelineDurationTime = src->evnt_TimelineDurationTime;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1EventIdentity_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1EventIdentity_del(Dz1EventIdentity* p)
{
	if (p == NULL) return;
	if (p->node_NodeIdNumber) Dz1Asn1UTF8Str_del(p->node_NodeIdNumber);
	if (p->link_LinkIdNumber) Dz1Asn1UTF8Str_del(p->link_LinkIdNumber);
	if (p->evnt_IdentificationNumber) Dz1Free(p->evnt_IdentificationNumber);
	if (p->evnt_LocationJurisDictionNameText) Dz1Asn1UTF8Str_del(p->evnt_LocationJurisDictionNameText);
	if (p->evnt_LocationLinkIdNumber) Dz1Asn1UTF8Str_del(p->evnt_LocationLinkIdNumber);
	if (p->evnt_LocationNodeIdNumber) Dz1Asn1UTF8Str_del(p->evnt_LocationNodeIdNumber);
	if (p->evnt_LocationRoadwayNameText) Dz1Asn1UTF8Str_del(p->evnt_LocationRoadwayNameText);
	if (p->evnt_DescriptionTypeEventCode) Dz1Free(p->evnt_DescriptionTypeEventCode);
	if (p->evnt_DescriptionTypeSpecialEventCode) Dz1Free(p->evnt_DescriptionTypeSpecialEventCode);
	if (p->evnt_DescriptionPlannedRoadWayClosureCode) Dz1Free(p->evnt_DescriptionPlannedRoadWayClosureCode);
	if (p->evnt_LanesShouldersBlockedCode) Dz1Asn1BitStr_del(p->evnt_LanesShouldersBlockedCode);
	if (p->evnt_TimelineStartGeneralizedTime) Dz1Asn1VisibleStr_del(p->evnt_TimelineStartGeneralizedTime);
	if (p->evnt_TimelineEndGeneralizedTime) Dz1Asn1VisibleStr_del(p->evnt_TimelineEndGeneralizedTime);
	Dz1Free(p);
}

void Dz1EventIdentity_dump(Dz1EventIdentity* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	if (p->node_NodeIdNumber == NULL) Dz1Thread_tprintf(tab, Dz1T("node_NodeIdNumber = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("node_NodeIdNumber = ")); Dz1Asn1UTF8Str_dump(p->node_NodeIdNumber, tab); /* using dump func */ }

	if (p->link_LinkIdNumber == NULL) Dz1Thread_tprintf(tab, Dz1T("link_LinkIdNumber = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("link_LinkIdNumber = ")); Dz1Asn1UTF8Str_dump(p->link_LinkIdNumber, tab); /* using dump func */ }

	if (p->evnt_IdentificationNumber == NULL) Dz1Thread_tprintf(tab, Dz1T("evnt_IdentificationNumber = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("evnt_IdentificationNumber = ")); Dz1u32_dump(p->evnt_IdentificationNumber, tab); }

	if (p->evnt_LocationJurisDictionNameText == NULL) Dz1Thread_tprintf(tab, Dz1T("evnt_LocationJurisDictionNameText = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("evnt_LocationJurisDictionNameText = ")); Dz1Asn1UTF8Str_dump(p->evnt_LocationJurisDictionNameText, tab); /* using dump func */ }

	if (p->evnt_LocationLinkIdNumber == NULL) Dz1Thread_tprintf(tab, Dz1T("evnt_LocationLinkIdNumber = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("evnt_LocationLinkIdNumber = ")); Dz1Asn1UTF8Str_dump(p->evnt_LocationLinkIdNumber, tab); /* using dump func */ }

	if (p->evnt_LocationNodeIdNumber == NULL) Dz1Thread_tprintf(tab, Dz1T("evnt_LocationNodeIdNumber = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("evnt_LocationNodeIdNumber = ")); Dz1Asn1UTF8Str_dump(p->evnt_LocationNodeIdNumber, tab); /* using dump func */ }

	if (p->evnt_LocationRoadwayNameText == NULL) Dz1Thread_tprintf(tab, Dz1T("evnt_LocationRoadwayNameText = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("evnt_LocationRoadwayNameText = ")); Dz1Asn1UTF8Str_dump(p->evnt_LocationRoadwayNameText, tab); /* using dump func */ }

	if (p->evnt_DescriptionTypeEventCode == NULL) Dz1Thread_tprintf(tab, Dz1T("evnt_DescriptionTypeEventCode = NULL\n"));
	else Dz1Thread_tprintf(tab, Dz1T("evnt_DescriptionTypeEventCode = %s(%d)\n"), Dz1EventIdentity_evnt_DescriptionTypeEventCodeStr(*p->evnt_DescriptionTypeEventCode), *p->evnt_DescriptionTypeEventCode);

	if (p->evnt_DescriptionTypeSpecialEventCode == NULL) Dz1Thread_tprintf(tab, Dz1T("evnt_DescriptionTypeSpecialEventCode = NULL\n"));
	else Dz1Thread_tprintf(tab, Dz1T("evnt_DescriptionTypeSpecialEventCode = %s(%d)\n"), Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeStr(*p->evnt_DescriptionTypeSpecialEventCode), *p->evnt_DescriptionTypeSpecialEventCode);

	if (p->evnt_DescriptionPlannedRoadWayClosureCode == NULL) Dz1Thread_tprintf(tab, Dz1T("evnt_DescriptionPlannedRoadWayClosureCode = NULL\n"));
	else Dz1Thread_tprintf(tab, Dz1T("evnt_DescriptionPlannedRoadWayClosureCode = %s(%d)\n"), Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeStr(*p->evnt_DescriptionPlannedRoadWayClosureCode), *p->evnt_DescriptionPlannedRoadWayClosureCode);

	Dz1Thread_tprintf(tab, Dz1T("evnt_LanesBlockedOrClosedNumber = ")); Dz1u8_dump(&p->evnt_LanesBlockedOrClosedNumber, tab);

	if (p->evnt_LanesShouldersBlockedCode == NULL) Dz1Thread_tprintf(tab, Dz1T("evnt_LanesShouldersBlockedCode = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("evnt_LanesShouldersBlockedCode = ")); Dz1Asn1BitStr_dump(p->evnt_LanesShouldersBlockedCode, tab); /* using dump func */ }

	if (p->evnt_TimelineStartGeneralizedTime == NULL) Dz1Thread_tprintf(tab, Dz1T("evnt_TimelineStartGeneralizedTime = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("evnt_TimelineStartGeneralizedTime = ")); Dz1Asn1VisibleStr_dump(p->evnt_TimelineStartGeneralizedTime, tab); /* using dump func */ }

	if (p->evnt_TimelineEndGeneralizedTime == NULL) Dz1Thread_tprintf(tab, Dz1T("evnt_TimelineEndGeneralizedTime = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("evnt_TimelineEndGeneralizedTime = ")); Dz1Asn1VisibleStr_dump(p->evnt_TimelineEndGeneralizedTime, tab); /* using dump func */ }

	Dz1Thread_tprintf(tab, Dz1T("evnt_TimelineDurationTime = ")); Dz1u32_dump(&p->evnt_TimelineDurationTime, tab);

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
void Dz1EventIdentity_fdump(FILE* fp, Dz1EventIdentity* p, int tab)
{
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;

	if (p->node_NodeIdNumber == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("node_NodeIdNumber = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("node_NodeIdNumber = ")); Dz1Asn1UTF8Str_fdump(fp, p->node_NodeIdNumber, tab); }

	if (p->link_LinkIdNumber == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("link_LinkIdNumber = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("link_LinkIdNumber = ")); Dz1Asn1UTF8Str_fdump(fp, p->link_LinkIdNumber, tab); }

	if (p->evnt_IdentificationNumber == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_IdentificationNumber = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_IdentificationNumber = ")); Dz1u32_fdump(fp, p->evnt_IdentificationNumber, tab); }

	if (p->evnt_LocationJurisDictionNameText == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_LocationJurisDictionNameText = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_LocationJurisDictionNameText = ")); Dz1Asn1UTF8Str_fdump(fp, p->evnt_LocationJurisDictionNameText, tab); }

	if (p->evnt_LocationLinkIdNumber == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_LocationLinkIdNumber = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_LocationLinkIdNumber = ")); Dz1Asn1UTF8Str_fdump(fp, p->evnt_LocationLinkIdNumber, tab); }

	if (p->evnt_LocationNodeIdNumber == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_LocationNodeIdNumber = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_LocationNodeIdNumber = ")); Dz1Asn1UTF8Str_fdump(fp, p->evnt_LocationNodeIdNumber, tab); }

	if (p->evnt_LocationRoadwayNameText == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_LocationRoadwayNameText = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_LocationRoadwayNameText = ")); Dz1Asn1UTF8Str_fdump(fp, p->evnt_LocationRoadwayNameText, tab); }

	if (p->evnt_DescriptionTypeEventCode == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_DescriptionTypeEventCode = NULL\n"));
	else Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_DescriptionTypeEventCode = %s(%d)\n"), Dz1EventIdentity_evnt_DescriptionTypeEventCodeStr(*p->evnt_DescriptionTypeEventCode), *p->evnt_DescriptionTypeEventCode);

	if (p->evnt_DescriptionTypeSpecialEventCode == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_DescriptionTypeSpecialEventCode = NULL\n"));
	else Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_DescriptionTypeSpecialEventCode = %s(%d)\n"), Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCodeStr(*p->evnt_DescriptionTypeSpecialEventCode), *p->evnt_DescriptionTypeSpecialEventCode);

	if (p->evnt_DescriptionPlannedRoadWayClosureCode == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_DescriptionPlannedRoadWayClosureCode = NULL\n"));
	else Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_DescriptionPlannedRoadWayClosureCode = %s(%d)\n"), Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCodeStr(*p->evnt_DescriptionPlannedRoadWayClosureCode), *p->evnt_DescriptionPlannedRoadWayClosureCode);

	Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_LanesBlockedOrClosedNumber = ")); Dz1u8_fdump(fp, &p->evnt_LanesBlockedOrClosedNumber, tab);

	if (p->evnt_LanesShouldersBlockedCode == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_LanesShouldersBlockedCode = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_LanesShouldersBlockedCode = ")); Dz1Asn1BitStr_fdump(fp, p->evnt_LanesShouldersBlockedCode, tab); }

	if (p->evnt_TimelineStartGeneralizedTime == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_TimelineStartGeneralizedTime = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_TimelineStartGeneralizedTime = ")); Dz1Asn1VisibleStr_fdump(fp, p->evnt_TimelineStartGeneralizedTime, tab); }

	if (p->evnt_TimelineEndGeneralizedTime == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_TimelineEndGeneralizedTime = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_TimelineEndGeneralizedTime = ")); Dz1Asn1VisibleStr_fdump(fp, p->evnt_TimelineEndGeneralizedTime, tab); }

	Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_TimelineDurationTime = ")); Dz1u32_fdump(fp, &p->evnt_TimelineDurationTime, tab);

	Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
}
Dz1Error Dz1EventIdentity_fromASN(Dz1EventIdentity* dst, EventIdentity* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Dz1EventIdentity_evnt_DescriptionTypeEventCode evnt_DescriptionTypeEventCode = (Dz1EventIdentity_evnt_DescriptionTypeEventCode)(src->DEF_EventIdentity_evnt_DescriptionTypeEventCode ? src->evnt_DescriptionTypeEventCode : 0);
		Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode evnt_DescriptionTypeSpecialEventCode = (Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode)(src->DEF_EventIdentity_evnt_DescriptionTypeSpecialEventCode ? src->evnt_DescriptionTypeSpecialEventCode : 0);
		Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode evnt_DescriptionPlannedRoadWayClosureCode = (Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode)(src->DEF_EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode ? src->evnt_DescriptionPlannedRoadWayClosureCode : 0);
		if ((dst->node_NodeIdNumber = Dz1Asn1UTF8Str_newFromASN(&src->node_NodeIdNumber, &err)) == NULL) { Dz1Thread_printf("node_NodeIdNumber : "); ERR_OUT(&err); }
		else if ((dst->link_LinkIdNumber = Dz1Asn1UTF8Str_newFromASN(&src->link_LinkIdNumber, &err)) == NULL) { Dz1Thread_printf("link_LinkIdNumber : "); ERR_OUT(&err); }
		else if (src->DEF_EventIdentity_evnt_IdentificationNumber && (dst->evnt_IdentificationNumber = u32_t_newFromASN(&src->evnt_IdentificationNumber, &err)) == NULL) ERR_OUT(&err);
		else if ((dst->evnt_LocationJurisDictionNameText = Dz1Asn1UTF8Str_newFromASN(&src->evnt_LocationJurisDictionNameText, &err)) == NULL) { Dz1Thread_printf("evnt_LocationJurisDictionNameText : "); ERR_OUT(&err); }
		else if ((dst->evnt_LocationLinkIdNumber = Dz1Asn1UTF8Str_newFromASN(&src->evnt_LocationLinkIdNumber, &err)) == NULL) { Dz1Thread_printf("evnt_LocationLinkIdNumber : "); ERR_OUT(&err); }
		else if ((dst->evnt_LocationNodeIdNumber = Dz1Asn1UTF8Str_newFromASN(&src->evnt_LocationNodeIdNumber, &err)) == NULL) { Dz1Thread_printf("evnt_LocationNodeIdNumber : "); ERR_OUT(&err); }
		else if ((dst->evnt_LocationRoadwayNameText = Dz1Asn1UTF8Str_newFromASN(&src->evnt_LocationRoadwayNameText, &err)) == NULL) { Dz1Thread_printf("evnt_LocationRoadwayNameText : "); ERR_OUT(&err); }
		else if (src->DEF_EventIdentity_evnt_DescriptionTypeEventCode && (dst->evnt_DescriptionTypeEventCode = Dz1EventIdentity_evnt_DescriptionTypeEventCode_new(&evnt_DescriptionTypeEventCode, &err)) == NULL) { Dz1Thread_printf("evnt_DescriptionTypeEventCode : "); ERR_OUT(&err); }
		else if (src->DEF_EventIdentity_evnt_DescriptionTypeSpecialEventCode && (dst->evnt_DescriptionTypeSpecialEventCode = Dz1EventIdentity_evnt_DescriptionTypeSpecialEventCode_new(&evnt_DescriptionTypeSpecialEventCode, &err)) == NULL) { Dz1Thread_printf("evnt_DescriptionTypeSpecialEventCode : "); ERR_OUT(&err); }
		else if (src->DEF_EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode && (dst->evnt_DescriptionPlannedRoadWayClosureCode = Dz1EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode_new(&evnt_DescriptionPlannedRoadWayClosureCode, &err)) == NULL) { Dz1Thread_printf("evnt_DescriptionPlannedRoadWayClosureCode : "); ERR_OUT(&err); }
		else if ((err = u8_t_fromASN(&dst->evnt_LanesBlockedOrClosedNumber, &src->evnt_LanesBlockedOrClosedNumber)).code) { Dz1Thread_printf("evnt_LanesBlockedOrClosedNumber : "); ERR_OUT(&err); }
		else if ((dst->evnt_LanesShouldersBlockedCode = Dz1Asn1BitStr_newFromASN(&src->evnt_LanesShouldersBlockedCode, &err)) == NULL) { Dz1Thread_printf("evnt_LanesShouldersBlockedCode : "); ERR_OUT(&err); }
		else if ((dst->evnt_TimelineStartGeneralizedTime = Dz1Asn1VisibleStr_newFromASN(&src->evnt_TimelineStartGeneralizedTime, &err)) == NULL) { Dz1Thread_printf("evnt_TimelineStartGeneralizedTime : "); ERR_OUT(&err); }
		else if ((dst->evnt_TimelineEndGeneralizedTime = Dz1Asn1VisibleStr_newFromASN(&src->evnt_TimelineEndGeneralizedTime, &err)) == NULL) { Dz1Thread_printf("evnt_TimelineEndGeneralizedTime : "); ERR_OUT(&err); }
		else if ((err = u32_t_fromASN(&dst->evnt_TimelineDurationTime, &src->evnt_TimelineDurationTime)).code) { Dz1Thread_printf("evnt_TimelineDurationTime : "); ERR_OUT(&err); }
		else
		{
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1EventIdentity, EventIdentity)

Dz1Error Dz1EventIdentity_toASN(EventIdentity* dst, Dz1EventIdentity* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = Dz1Asn1UTF8Str_toASN(&dst->node_NodeIdNumber, src->node_NodeIdNumber, ws)).code) { Dz1Thread_printf("node_NodeIdNumber : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1UTF8Str_toASN(&dst->link_LinkIdNumber, src->link_LinkIdNumber, ws)).code) { Dz1Thread_printf("link_LinkIdNumber : "); ERR_OUT(&err); }
		else if ((dst->DEF_EventIdentity_evnt_IdentificationNumber = src->evnt_IdentificationNumber ? 1 : 0) == 1 && (err = u32_t_toASN(&dst->evnt_IdentificationNumber, src->evnt_IdentificationNumber, ws)).code) { Dz1Thread_printf("evnt_IdentificationNumber : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1UTF8Str_toASN(&dst->evnt_LocationJurisDictionNameText, src->evnt_LocationJurisDictionNameText, ws)).code) { Dz1Thread_printf("evnt_LocationJurisDictionNameText : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1UTF8Str_toASN(&dst->evnt_LocationLinkIdNumber, src->evnt_LocationLinkIdNumber, ws)).code) { Dz1Thread_printf("evnt_LocationLinkIdNumber : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1UTF8Str_toASN(&dst->evnt_LocationNodeIdNumber, src->evnt_LocationNodeIdNumber, ws)).code) { Dz1Thread_printf("evnt_LocationNodeIdNumber : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1UTF8Str_toASN(&dst->evnt_LocationRoadwayNameText, src->evnt_LocationRoadwayNameText, ws)).code) { Dz1Thread_printf("evnt_LocationRoadwayNameText : "); ERR_OUT(&err); }
		else if ((err = u8_t_toASN(&dst->evnt_LanesBlockedOrClosedNumber, &src->evnt_LanesBlockedOrClosedNumber, ws)).code) { Dz1Thread_printf("evnt_LanesBlockedOrClosedNumber : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1BitStr_toASN(&dst->evnt_LanesShouldersBlockedCode, src->evnt_LanesShouldersBlockedCode, ws)).code) { Dz1Thread_printf("evnt_LanesShouldersBlockedCode : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1VisibleStr_toASN(&dst->evnt_TimelineStartGeneralizedTime, src->evnt_TimelineStartGeneralizedTime, ws)).code) { Dz1Thread_printf("evnt_TimelineStartGeneralizedTime : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1VisibleStr_toASN(&dst->evnt_TimelineEndGeneralizedTime, src->evnt_TimelineEndGeneralizedTime, ws)).code) { Dz1Thread_printf("evnt_TimelineEndGeneralizedTime : "); ERR_OUT(&err); }
		else if ((err = u32_t_toASN(&dst->evnt_TimelineDurationTime, &src->evnt_TimelineDurationTime, ws)).code) { Dz1Thread_printf("evnt_TimelineDurationTime : "); ERR_OUT(&err); }
		else
		{
			if ((dst->DEF_EventIdentity_evnt_DescriptionTypeEventCode = src->evnt_DescriptionTypeEventCode ? 1 : 0) == 1) dst->evnt_DescriptionTypeEventCode = *src->evnt_DescriptionTypeEventCode;
			if ((dst->DEF_EventIdentity_evnt_DescriptionTypeSpecialEventCode = src->evnt_DescriptionTypeSpecialEventCode ? 1 : 0) == 1) dst->evnt_DescriptionTypeSpecialEventCode = *src->evnt_DescriptionTypeSpecialEventCode;
			if ((dst->DEF_EventIdentity_evnt_DescriptionPlannedRoadWayClosureCode = src->evnt_DescriptionPlannedRoadWayClosureCode ? 1 : 0) == 1) dst->evnt_DescriptionPlannedRoadWayClosureCode = *src->evnt_DescriptionPlannedRoadWayClosureCode;
		}
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1EventIdentity, EventIdentity)
// Dz1EventIdentity
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1EventIdentityResponse
static Dz1Error Dz1EventIdentityResponse_add(Dz1EventIdentityResponse* p, Dz1EventIdentity* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1EventIdentityResponseMkArrArg
{
	Dz1EventIdentity** arr;
	unsigned int idx;
} Dz1EventIdentityResponseMkArrArg;

static Dz1Error _Dz1EventIdentityResponse_get_array(void* ptr, Dz1EventIdentity* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1EventIdentityResponseMkArrArg* arg = (Dz1EventIdentityResponseMkArrArg*)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1EventIdentity** Dz1EventIdentityResponse_get_array(Dz1EventIdentityResponse* p, unsigned int* ret_cnt, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err == NULL ? &_err : err;
	Dz1EventIdentity** ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1EventIdentity**)Dz1Calloc(sizeof(Dz1EventIdentity*), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1EventIdentityResponseMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void*)ret);

		*errp = p->travel(p, _Dz1EventIdentityResponse_get_array, (void*)&arg);
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

static Dz1Error Dz1EventIdentityResponse_travelForward(Dz1EventIdentityResponse* p, Dz1Error(*func)(void* ptr, Dz1EventIdentity* data), void* ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1EventIdentityResponse_travelBackward(Dz1EventIdentityResponse* p, Dz1Error(*func)(void* ptr, Dz1EventIdentity* data), void* ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1EventIdentityResponse_count(Dz1EventIdentityResponse* p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1EventIdentityResponse* Dz1EventIdentityResponse_new(Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1EventIdentityResponse* ret = (Dz1EventIdentityResponse*)Dz1Calloc(sizeof(Dz1EventIdentityResponse), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1EventIdentityResponse_delAndSetNull, (void*)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
			(Dz1DelFunc)Dz1EventIdentity_del,
			NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = Dz1EventIdentityResponse_add;
			ret->get_array = Dz1EventIdentityResponse_get_array;
			ret->travel = Dz1EventIdentityResponse_travelForward;
			ret->travelForward = Dz1EventIdentityResponse_travelForward;
			ret->travelBackward = Dz1EventIdentityResponse_travelBackward;
			ret->count = Dz1EventIdentityResponse_count;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1EventIdentityResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1EventIdentityResponse_clone(void* ptr, Dz1EventIdentity* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1EventIdentityResponse* p = (Dz1EventIdentityResponse*)ptr;
	Dz1EventIdentity* cloned = Dz1EventIdentity_clone(data, &err);
	err = Dz1Fifo_push(p->storage, cloned);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1EventIdentityResponse* Dz1EventIdentityResponse_clone(Dz1EventIdentityResponse* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1EventIdentityResponse* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1EventIdentityResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1EventIdentityResponse_delAndSetNull, (void*)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1EventIdentityResponse_clone, (void*)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1EventIdentityResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1EventIdentityResponse_del(Dz1EventIdentityResponse* p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1EventIdentityResponse_dump(void* ptr, Dz1EventIdentity* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	int tab = *(int*)ptr;
	Dz1Thread_tprintf(tab, Dz1T("entry = "));
	Dz1EventIdentity_dump(p, tab);
	return err;
}

void Dz1EventIdentityResponse_dump(Dz1EventIdentityResponse* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;
	p->travel(p, _Dz1EventIdentityResponse_dump, (void*)&tab);
	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
typedef struct Dz1EventIdentityResponseFDumpArg
{
	FILE* fp;
	int tab;
} Dz1EventIdentityResponseFDumpArg;

static Dz1Error _Dz1EventIdentityResponse_fdump(void* ptr, Dz1EventIdentity* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1EventIdentityResponseFDumpArg* arg = (Dz1EventIdentityResponseFDumpArg*)ptr;
	Dz1Thread_ftprintf(arg->fp, arg->tab, Dz1T("entry = "));
	Dz1EventIdentity_fdump(arg->fp, p, arg->tab);
	return err;
}

void Dz1EventIdentityResponse_fdump(FILE* fp, Dz1EventIdentityResponse* p, int tab)
{
	Dz1EventIdentityResponseFDumpArg arg = { fp, tab };
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
	p->travel(p, _Dz1EventIdentityResponse_fdump, (void*)&arg);
	Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
}
PSEUDO_LIST_FROM_ASN(Dz1EventIdentityResponse, Dz1EventIdentity, EventIdentity)
DZ1_NEW_LIST_FROM_ASN(Dz1EventIdentityResponse, ASN1List)

PSEUDO_ENTRY_TO_ASN(Dz1EventIdentityResponse, Dz1EventIdentity, EventIdentity)
PSEUDO_LIST_TO_ASN(Dz1EventIdentityResponse)
DZ1_TO_NEW_ASN_LIST(Dz1EventIdentityResponse, ASN1List)

// Dz1EventIdentityResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentIdentity
Dz1IncidentIdentity* Dz1IncidentIdentity_new(Dz1Asn1UTF8Str* node_NodeIdNumber,
	Dz1Asn1UTF8Str* link_LinkIdNumber,
	Dz1Asn1VisibleStr* evnt_UpdateGeneralizedTime,
	Dz1Asn1BitStr* evnt_IncidentPropertyDamageCode, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1IncidentIdentity* __internal_ret = (Dz1IncidentIdentity*)Dz1Calloc(sizeof(Dz1IncidentIdentity), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1IncidentIdentity_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->node_NodeIdNumber = node_NodeIdNumber;
		__internal_ret->link_LinkIdNumber = link_LinkIdNumber;
		__internal_ret->evnt_UpdateGeneralizedTime = evnt_UpdateGeneralizedTime;
		__internal_ret->evnt_IncidentPropertyDamageCode = evnt_IncidentPropertyDamageCode;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1IncidentIdentity_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1IncidentIdentity* Dz1IncidentIdentity_clone(Dz1IncidentIdentity* src, Dz1Error* err)
{
	Dz1IncidentIdentity* ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1IncidentIdentity*)Dz1Calloc(sizeof(Dz1IncidentIdentity), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1IncidentIdentity_delAndSetNull, (void*)&ret);

		if (src->node_NodeIdNumber && (ret->node_NodeIdNumber = Dz1Asn1UTF8Str_clone(src->node_NodeIdNumber, errp)) == NULL) ERR_OUT(errp);
		else if (src->link_LinkIdNumber && (ret->link_LinkIdNumber = Dz1Asn1UTF8Str_clone(src->link_LinkIdNumber, errp)) == NULL) ERR_OUT(errp);
		else if (src->evnt_LocationLinearDistanceOffsetBeginNumber && (ret->evnt_LocationLinearDistanceOffsetBeginNumber = (u16_t*)Dz1Calloc(sizeof(u16_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->evnt_LinearDistanceoffsetEndNumber && (ret->evnt_LinearDistanceoffsetEndNumber = (u16_t*)Dz1Calloc(sizeof(u16_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->evnt_UpdateGeneralizedTime && (ret->evnt_UpdateGeneralizedTime = Dz1Asn1VisibleStr_clone(src->evnt_UpdateGeneralizedTime, errp)) == NULL) ERR_OUT(errp);
		else if (src->evnt_IncidentHumanFatalitiesCountQuantity && (ret->evnt_IncidentHumanFatalitiesCountQuantity = (u8_t*)Dz1Calloc(sizeof(u8_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->evnt_IncidentHumanInjuriesCountQuantity && (ret->evnt_IncidentHumanInjuriesCountQuantity = (u8_t*)Dz1Calloc(sizeof(u8_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->evnt_IncidentPropertyDamageCode && (ret->evnt_IncidentPropertyDamageCode = Dz1Asn1BitStr_clone(src->evnt_IncidentPropertyDamageCode, errp)) == NULL) ERR_OUT(errp);
		else if (src->evnt_IncidentPropertyDamageOther && (ret->evnt_IncidentPropertyDamageOther = Dz1Asn1UTF8Str_clone(src->evnt_IncidentPropertyDamageOther, errp)) == NULL) ERR_OUT(errp);
		else
		{
			if (src->evnt_LocationLinearDistanceOffsetBeginNumber != NULL && ret->evnt_LocationLinearDistanceOffsetBeginNumber != NULL) *ret->evnt_LocationLinearDistanceOffsetBeginNumber = *src->evnt_LocationLinearDistanceOffsetBeginNumber;
			if (src->evnt_LinearDistanceoffsetEndNumber != NULL && ret->evnt_LinearDistanceoffsetEndNumber != NULL) *ret->evnt_LinearDistanceoffsetEndNumber = *src->evnt_LinearDistanceoffsetEndNumber;
			if (src->evnt_IncidentHumanFatalitiesCountQuantity != NULL && ret->evnt_IncidentHumanFatalitiesCountQuantity != NULL) *ret->evnt_IncidentHumanFatalitiesCountQuantity = *src->evnt_IncidentHumanFatalitiesCountQuantity;
			if (src->evnt_IncidentHumanInjuriesCountQuantity != NULL && ret->evnt_IncidentHumanInjuriesCountQuantity != NULL) *ret->evnt_IncidentHumanInjuriesCountQuantity = *src->evnt_IncidentHumanInjuriesCountQuantity;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1IncidentIdentity_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1IncidentIdentity_del(Dz1IncidentIdentity* p)
{
	if (p == NULL) return;
	if (p->node_NodeIdNumber) Dz1Asn1UTF8Str_del(p->node_NodeIdNumber);
	if (p->link_LinkIdNumber) Dz1Asn1UTF8Str_del(p->link_LinkIdNumber);
	if (p->evnt_LocationLinearDistanceOffsetBeginNumber) Dz1Free(p->evnt_LocationLinearDistanceOffsetBeginNumber);
	if (p->evnt_LinearDistanceoffsetEndNumber) Dz1Free(p->evnt_LinearDistanceoffsetEndNumber);
	if (p->evnt_UpdateGeneralizedTime) Dz1Asn1VisibleStr_del(p->evnt_UpdateGeneralizedTime);
	if (p->evnt_IncidentHumanFatalitiesCountQuantity) Dz1Free(p->evnt_IncidentHumanFatalitiesCountQuantity);
	if (p->evnt_IncidentHumanInjuriesCountQuantity) Dz1Free(p->evnt_IncidentHumanInjuriesCountQuantity);
	if (p->evnt_IncidentPropertyDamageCode) Dz1Asn1BitStr_del(p->evnt_IncidentPropertyDamageCode);
	if (p->evnt_IncidentPropertyDamageOther) Dz1Asn1UTF8Str_del(p->evnt_IncidentPropertyDamageOther);
	Dz1Free(p);
}

void Dz1IncidentIdentity_dump(Dz1IncidentIdentity* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	if (p->node_NodeIdNumber == NULL) Dz1Thread_tprintf(tab, Dz1T("node_NodeIdNumber = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("node_NodeIdNumber = ")); Dz1Asn1UTF8Str_dump(p->node_NodeIdNumber, tab); /* using dump func */ }

	if (p->link_LinkIdNumber == NULL) Dz1Thread_tprintf(tab, Dz1T("link_LinkIdNumber = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("link_LinkIdNumber = ")); Dz1Asn1UTF8Str_dump(p->link_LinkIdNumber, tab); /* using dump func */ }

	if (p->evnt_LocationLinearDistanceOffsetBeginNumber == NULL) Dz1Thread_tprintf(tab, Dz1T("evnt_LocationLinearDistanceOffsetBeginNumber = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("evnt_LocationLinearDistanceOffsetBeginNumber = ")); Dz1u16_dump(p->evnt_LocationLinearDistanceOffsetBeginNumber, tab); }

	if (p->evnt_LinearDistanceoffsetEndNumber == NULL) Dz1Thread_tprintf(tab, Dz1T("evnt_LinearDistanceoffsetEndNumber = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("evnt_LinearDistanceoffsetEndNumber = ")); Dz1u16_dump(p->evnt_LinearDistanceoffsetEndNumber, tab); }

	if (p->evnt_UpdateGeneralizedTime == NULL) Dz1Thread_tprintf(tab, Dz1T("evnt_UpdateGeneralizedTime = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("evnt_UpdateGeneralizedTime = ")); Dz1Asn1VisibleStr_dump(p->evnt_UpdateGeneralizedTime, tab); /* using dump func */ }

	if (p->evnt_IncidentHumanFatalitiesCountQuantity == NULL) Dz1Thread_tprintf(tab, Dz1T("evnt_IncidentHumanFatalitiesCountQuantity = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("evnt_IncidentHumanFatalitiesCountQuantity = ")); Dz1u8_dump(p->evnt_IncidentHumanFatalitiesCountQuantity, tab); }

	if (p->evnt_IncidentHumanInjuriesCountQuantity == NULL) Dz1Thread_tprintf(tab, Dz1T("evnt_IncidentHumanInjuriesCountQuantity = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("evnt_IncidentHumanInjuriesCountQuantity = ")); Dz1u8_dump(p->evnt_IncidentHumanInjuriesCountQuantity, tab); }

	if (p->evnt_IncidentPropertyDamageCode == NULL) Dz1Thread_tprintf(tab, Dz1T("evnt_IncidentPropertyDamageCode = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("evnt_IncidentPropertyDamageCode = ")); Dz1Asn1BitStr_dump(p->evnt_IncidentPropertyDamageCode, tab); /* using dump func */ }

	if (p->evnt_IncidentPropertyDamageOther == NULL) Dz1Thread_tprintf(tab, Dz1T("evnt_IncidentPropertyDamageOther = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("evnt_IncidentPropertyDamageOther = ")); Dz1Asn1UTF8Str_dump(p->evnt_IncidentPropertyDamageOther, tab); /* using dump func */ }

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
void Dz1IncidentIdentity_fdump(FILE* fp, Dz1IncidentIdentity* p, int tab)
{
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;

	if (p->node_NodeIdNumber == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("node_NodeIdNumber = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("node_NodeIdNumber = ")); Dz1Asn1UTF8Str_fdump(fp, p->node_NodeIdNumber, tab); }

	if (p->link_LinkIdNumber == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("link_LinkIdNumber = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("link_LinkIdNumber = ")); Dz1Asn1UTF8Str_fdump(fp, p->link_LinkIdNumber, tab); }

	if (p->evnt_LocationLinearDistanceOffsetBeginNumber == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_LocationLinearDistanceOffsetBeginNumber = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_LocationLinearDistanceOffsetBeginNumber = ")); Dz1u16_fdump(fp, p->evnt_LocationLinearDistanceOffsetBeginNumber, tab); }

	if (p->evnt_LinearDistanceoffsetEndNumber == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_LinearDistanceoffsetEndNumber = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_LinearDistanceoffsetEndNumber = ")); Dz1u16_fdump(fp, p->evnt_LinearDistanceoffsetEndNumber, tab); }

	if (p->evnt_UpdateGeneralizedTime == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_UpdateGeneralizedTime = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_UpdateGeneralizedTime = ")); Dz1Asn1VisibleStr_fdump(fp, p->evnt_UpdateGeneralizedTime, tab); }

	if (p->evnt_IncidentHumanFatalitiesCountQuantity == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_IncidentHumanFatalitiesCountQuantity = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_IncidentHumanFatalitiesCountQuantity = ")); Dz1u8_fdump(fp, p->evnt_IncidentHumanFatalitiesCountQuantity, tab); }

	if (p->evnt_IncidentHumanInjuriesCountQuantity == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_IncidentHumanInjuriesCountQuantity = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_IncidentHumanInjuriesCountQuantity = ")); Dz1u8_fdump(fp, p->evnt_IncidentHumanInjuriesCountQuantity, tab); }

	if (p->evnt_IncidentPropertyDamageCode == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_IncidentPropertyDamageCode = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_IncidentPropertyDamageCode = ")); Dz1Asn1BitStr_fdump(fp, p->evnt_IncidentPropertyDamageCode, tab); }

	if (p->evnt_IncidentPropertyDamageOther == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_IncidentPropertyDamageOther = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_IncidentPropertyDamageOther = ")); Dz1Asn1UTF8Str_fdump(fp, p->evnt_IncidentPropertyDamageOther, tab); }

	Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
}
Dz1Error Dz1IncidentIdentity_fromASN(Dz1IncidentIdentity* dst, IncidentIdentity* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((dst->node_NodeIdNumber = Dz1Asn1UTF8Str_newFromASN(&src->node_NodeIdNumber, &err)) == NULL) { Dz1Thread_printf("node_NodeIdNumber : "); ERR_OUT(&err); }
		else if ((dst->link_LinkIdNumber = Dz1Asn1UTF8Str_newFromASN(&src->link_LinkIdNumber, &err)) == NULL) { Dz1Thread_printf("link_LinkIdNumber : "); ERR_OUT(&err); }
		else if (src->DEF_IncidentIdentity_evnt_LocationLinearDistanceOffsetBeginNumber && (dst->evnt_LocationLinearDistanceOffsetBeginNumber = u16_t_newFromASN(&src->evnt_LocationLinearDistanceOffsetBeginNumber, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_IncidentIdentity_evnt_LinearDistanceoffsetEndNumber && (dst->evnt_LinearDistanceoffsetEndNumber = u16_t_newFromASN(&src->evnt_LinearDistanceoffsetEndNumber, &err)) == NULL) ERR_OUT(&err);
		else if ((dst->evnt_UpdateGeneralizedTime = Dz1Asn1VisibleStr_newFromASN(&src->evnt_UpdateGeneralizedTime, &err)) == NULL) { Dz1Thread_printf("evnt_UpdateGeneralizedTime : "); ERR_OUT(&err); }
		else if (src->DEF_IncidentIdentity_evnt_IncidentHumanFatalitiesCountQuantity && (dst->evnt_IncidentHumanFatalitiesCountQuantity = u8_t_newFromASN(&src->evnt_IncidentHumanFatalitiesCountQuantity, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_IncidentIdentity_evnt_IncidentHumanInjuriesCountQuantity && (dst->evnt_IncidentHumanInjuriesCountQuantity = u8_t_newFromASN(&src->evnt_IncidentHumanInjuriesCountQuantity, &err)) == NULL) ERR_OUT(&err);
		else if ((dst->evnt_IncidentPropertyDamageCode = Dz1Asn1BitStr_newFromASN(&src->evnt_IncidentPropertyDamageCode, &err)) == NULL) { Dz1Thread_printf("evnt_IncidentPropertyDamageCode : "); ERR_OUT(&err); }
		else if (src->DEF_IncidentIdentity_evnt_IncidentPropertyDamageOther && (dst->evnt_IncidentPropertyDamageOther = Dz1Asn1UTF8Str_newFromASN(&src->evnt_IncidentPropertyDamageOther, &err)) == NULL) ERR_OUT(&err);
		else
		{
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1IncidentIdentity, IncidentIdentity)

Dz1Error Dz1IncidentIdentity_toASN(IncidentIdentity* dst, Dz1IncidentIdentity* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = Dz1Asn1UTF8Str_toASN(&dst->node_NodeIdNumber, src->node_NodeIdNumber, ws)).code) { Dz1Thread_printf("node_NodeIdNumber : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1UTF8Str_toASN(&dst->link_LinkIdNumber, src->link_LinkIdNumber, ws)).code) { Dz1Thread_printf("link_LinkIdNumber : "); ERR_OUT(&err); }
		else if ((dst->DEF_IncidentIdentity_evnt_LocationLinearDistanceOffsetBeginNumber = src->evnt_LocationLinearDistanceOffsetBeginNumber ? 1 : 0) == 1 && (err = u16_t_toASN(&dst->evnt_LocationLinearDistanceOffsetBeginNumber, src->evnt_LocationLinearDistanceOffsetBeginNumber, ws)).code) { Dz1Thread_printf("evnt_LocationLinearDistanceOffsetBeginNumber : "); ERR_OUT(&err); }
		else if ((dst->DEF_IncidentIdentity_evnt_LinearDistanceoffsetEndNumber = src->evnt_LinearDistanceoffsetEndNumber ? 1 : 0) == 1 && (err = u16_t_toASN(&dst->evnt_LinearDistanceoffsetEndNumber, src->evnt_LinearDistanceoffsetEndNumber, ws)).code) { Dz1Thread_printf("evnt_LinearDistanceoffsetEndNumber : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1VisibleStr_toASN(&dst->evnt_UpdateGeneralizedTime, src->evnt_UpdateGeneralizedTime, ws)).code) { Dz1Thread_printf("evnt_UpdateGeneralizedTime : "); ERR_OUT(&err); }
		else if ((dst->DEF_IncidentIdentity_evnt_IncidentHumanFatalitiesCountQuantity = src->evnt_IncidentHumanFatalitiesCountQuantity ? 1 : 0) == 1 && (err = u8_t_toASN(&dst->evnt_IncidentHumanFatalitiesCountQuantity, src->evnt_IncidentHumanFatalitiesCountQuantity, ws)).code) { Dz1Thread_printf("evnt_IncidentHumanFatalitiesCountQuantity : "); ERR_OUT(&err); }
		else if ((dst->DEF_IncidentIdentity_evnt_IncidentHumanInjuriesCountQuantity = src->evnt_IncidentHumanInjuriesCountQuantity ? 1 : 0) == 1 && (err = u8_t_toASN(&dst->evnt_IncidentHumanInjuriesCountQuantity, src->evnt_IncidentHumanInjuriesCountQuantity, ws)).code) { Dz1Thread_printf("evnt_IncidentHumanInjuriesCountQuantity : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1BitStr_toASN(&dst->evnt_IncidentPropertyDamageCode, src->evnt_IncidentPropertyDamageCode, ws)).code) { Dz1Thread_printf("evnt_IncidentPropertyDamageCode : "); ERR_OUT(&err); }
		else if ((dst->DEF_IncidentIdentity_evnt_IncidentPropertyDamageOther = src->evnt_IncidentPropertyDamageOther ? 1 : 0) == 1 && (err = Dz1Asn1UTF8Str_toASN(&dst->evnt_IncidentPropertyDamageOther, src->evnt_IncidentPropertyDamageOther, ws)).code) { Dz1Thread_printf("evnt_IncidentPropertyDamageOther : "); ERR_OUT(&err); }
		else
		{
		}
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1IncidentIdentity, IncidentIdentity)
// Dz1IncidentIdentity
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentIdentityResponse
static Dz1Error Dz1IncidentIdentityResponse_add(Dz1IncidentIdentityResponse* p, Dz1IncidentIdentity* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1IncidentIdentityResponseMkArrArg
{
	Dz1IncidentIdentity** arr;
	unsigned int idx;
} Dz1IncidentIdentityResponseMkArrArg;

static Dz1Error _Dz1IncidentIdentityResponse_get_array(void* ptr, Dz1IncidentIdentity* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1IncidentIdentityResponseMkArrArg* arg = (Dz1IncidentIdentityResponseMkArrArg*)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1IncidentIdentity** Dz1IncidentIdentityResponse_get_array(Dz1IncidentIdentityResponse* p, unsigned int* ret_cnt, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err == NULL ? &_err : err;
	Dz1IncidentIdentity** ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1IncidentIdentity**)Dz1Calloc(sizeof(Dz1IncidentIdentity*), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1IncidentIdentityResponseMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void*)ret);

		*errp = p->travel(p, _Dz1IncidentIdentityResponse_get_array, (void*)&arg);
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

static Dz1Error Dz1IncidentIdentityResponse_travelForward(Dz1IncidentIdentityResponse* p, Dz1Error(*func)(void* ptr, Dz1IncidentIdentity* data), void* ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1IncidentIdentityResponse_travelBackward(Dz1IncidentIdentityResponse* p, Dz1Error(*func)(void* ptr, Dz1IncidentIdentity* data), void* ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1IncidentIdentityResponse_count(Dz1IncidentIdentityResponse* p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1IncidentIdentityResponse* Dz1IncidentIdentityResponse_new(Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1IncidentIdentityResponse* ret = (Dz1IncidentIdentityResponse*)Dz1Calloc(sizeof(Dz1IncidentIdentityResponse), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1IncidentIdentityResponse_delAndSetNull, (void*)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
			(Dz1DelFunc)Dz1IncidentIdentity_del,
			NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = Dz1IncidentIdentityResponse_add;
			ret->get_array = Dz1IncidentIdentityResponse_get_array;
			ret->travel = Dz1IncidentIdentityResponse_travelForward;
			ret->travelForward = Dz1IncidentIdentityResponse_travelForward;
			ret->travelBackward = Dz1IncidentIdentityResponse_travelBackward;
			ret->count = Dz1IncidentIdentityResponse_count;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1IncidentIdentityResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1IncidentIdentityResponse_clone(void* ptr, Dz1IncidentIdentity* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1IncidentIdentityResponse* p = (Dz1IncidentIdentityResponse*)ptr;
	Dz1IncidentIdentity* cloned = Dz1IncidentIdentity_clone(data, &err);
	err = Dz1Fifo_push(p->storage, cloned);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1IncidentIdentityResponse* Dz1IncidentIdentityResponse_clone(Dz1IncidentIdentityResponse* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1IncidentIdentityResponse* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1IncidentIdentityResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1IncidentIdentityResponse_delAndSetNull, (void*)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1IncidentIdentityResponse_clone, (void*)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1IncidentIdentityResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1IncidentIdentityResponse_del(Dz1IncidentIdentityResponse* p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1IncidentIdentityResponse_dump(void* ptr, Dz1IncidentIdentity* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	int tab = *(int*)ptr;
	Dz1Thread_tprintf(tab, Dz1T("entry = "));
	Dz1IncidentIdentity_dump(p, tab);
	return err;
}

void Dz1IncidentIdentityResponse_dump(Dz1IncidentIdentityResponse* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;
	p->travel(p, _Dz1IncidentIdentityResponse_dump, (void*)&tab);
	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
typedef struct Dz1IncidentIdentityResponseFDumpArg
{
	FILE* fp;
	int tab;
} Dz1IncidentIdentityResponseFDumpArg;

static Dz1Error _Dz1IncidentIdentityResponse_fdump(void* ptr, Dz1IncidentIdentity* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1IncidentIdentityResponseFDumpArg* arg = (Dz1IncidentIdentityResponseFDumpArg*)ptr;
	Dz1Thread_ftprintf(arg->fp, arg->tab, Dz1T("entry = "));
	Dz1IncidentIdentity_fdump(arg->fp, p, arg->tab);
	return err;
}

void Dz1IncidentIdentityResponse_fdump(FILE* fp, Dz1IncidentIdentityResponse* p, int tab)
{
	Dz1IncidentIdentityResponseFDumpArg arg = { fp, tab };
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
	p->travel(p, _Dz1IncidentIdentityResponse_fdump, (void*)&arg);
	Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
}
PSEUDO_LIST_FROM_ASN(Dz1IncidentIdentityResponse, Dz1IncidentIdentity, IncidentIdentity)
DZ1_NEW_LIST_FROM_ASN(Dz1IncidentIdentityResponse, ASN1List)

PSEUDO_ENTRY_TO_ASN(Dz1IncidentIdentityResponse, Dz1IncidentIdentity, IncidentIdentity)
PSEUDO_LIST_TO_ASN(Dz1IncidentIdentityResponse)
DZ1_TO_NEW_ASN_LIST(Dz1IncidentIdentityResponse, ASN1List)

// Dz1IncidentIdentityResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode
static struct Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeMapA
{
	str_t str;
	Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode v;
} Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeMapA[] =
{
	{ (char*)"other_no_additional_information_required", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_other_no_additional_information_required },
	{ (char*)"other_additional_information_required", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_other_additional_information_required },
	{ (char*)"vehicular_accident", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_vehicular_accident },
	{ (char*)"weather_related_incident", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_weather_related_incident },
	{ (char*)"stalled_vehicle", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_stalled_vehicle },
	{ (char*)"vehicle_fire", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_vehicle_fire },
	{ (char*)"roadway_debris", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_roadway_debris },
	{ (char*)"hazmat_spill", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_hazmat_spill },
	{ (char*)"earthquake", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_earthquake },
	{ (char*)"landslide", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_landslide },
	{ (char*)"flood", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_flood },
	{ (char*)"typhoon", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_typhoon },
	{ (char*)"unplanned_demonstration", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_unplanned_demonstration },
	{ (char*)"increased_traffice_volume", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_increased_traffice_volume },
	{ NULL, Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_max }
};

str_t Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeStrA(Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode v)
{
	struct Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeMapA* i = NULL;
	for (i = Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeFromStrA(str_t str)
{
	struct Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeMapA* i = NULL;
	for (i = Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeMapA; i->str; i++)
		if (strcmp(i->str, str) == 0) return i->v;
	return Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeMapW
{
	wstr_t str;
	Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode v;
} Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeMapW[] =
{
	{ (wchar_t*)L"other_no_additional_information_required", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_other_no_additional_information_required },
	{ (wchar_t*)L"other_additional_information_required", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_other_additional_information_required },
	{ (wchar_t*)L"vehicular_accident", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_vehicular_accident },
	{ (wchar_t*)L"weather_related_incident", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_weather_related_incident },
	{ (wchar_t*)L"stalled_vehicle", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_stalled_vehicle },
	{ (wchar_t*)L"vehicle_fire", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_vehicle_fire },
	{ (wchar_t*)L"roadway_debris", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_roadway_debris },
	{ (wchar_t*)L"hazmat_spill", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_hazmat_spill },
	{ (wchar_t*)L"earthquake", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_earthquake },
	{ (wchar_t*)L"landslide", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_landslide },
	{ (wchar_t*)L"flood", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_flood },
	{ (wchar_t*)L"typhoon", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_typhoon },
	{ (wchar_t*)L"unplanned_demonstration", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_unplanned_demonstration },
	{ (wchar_t*)L"increased_traffice_volume", Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_increased_traffice_volume },
	{ NULL, Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_max }
};

wstr_t Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeStrW(Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode v)
{
	struct Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeMapW* i = NULL;
	for (i = Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeFromStrW(wstr_t str)
{
	struct Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeMapW* i = NULL;
	for (i = Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeMapW; i->str; i++)
		if (wcscmp(i->str, str) == 0) return i->v;
	return Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_max;
}
#endif // UNIX_SYSTEM

Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode* Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_new(Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode* src, Dz1Error* err) {
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode* __internal_ret = (Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode*)Dz1Calloc(sizeof(Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
	}
	return __internal_ret;
}

void Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_dump(Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode* v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeStr(*v));
}
void Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode_fdump(FILE* fp, Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode* v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeStr(*v));
}
// Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentConditions_evnt_IncidentStatusCode
static struct Dz1IncidentConditions_evnt_IncidentStatusCodeMapA
{
	str_t str;
	Dz1IncidentConditions_evnt_IncidentStatusCode v;
} Dz1IncidentConditions_evnt_IncidentStatusCodeMapA[] =
{
	{ (char*)"other_no_additional_information_required", Dz1IncidentConditions_evnt_IncidentStatusCode_other_no_additional_information_required },
	{ (char*)"other_additional_information_required", Dz1IncidentConditions_evnt_IncidentStatusCode_other_additional_information_required },
	{ (char*)"incident_detected", Dz1IncidentConditions_evnt_IncidentStatusCode_incident_detected },
	{ (char*)"confirmed_and_responding", Dz1IncidentConditions_evnt_IncidentStatusCode_confirmed_and_responding },
	{ (char*)"cleared_and_recovering", Dz1IncidentConditions_evnt_IncidentStatusCode_cleared_and_recovering },
	{ (char*)"over_and_done", Dz1IncidentConditions_evnt_IncidentStatusCode_over_and_done },
	{ (char*)"other", Dz1IncidentConditions_evnt_IncidentStatusCode_other },
	{ NULL, Dz1IncidentConditions_evnt_IncidentStatusCode_max }
};

str_t Dz1IncidentConditions_evnt_IncidentStatusCodeStrA(Dz1IncidentConditions_evnt_IncidentStatusCode v)
{
	struct Dz1IncidentConditions_evnt_IncidentStatusCodeMapA* i = NULL;
	for (i = Dz1IncidentConditions_evnt_IncidentStatusCodeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1IncidentConditions_evnt_IncidentStatusCode Dz1IncidentConditions_evnt_IncidentStatusCodeFromStrA(str_t str)
{
	struct Dz1IncidentConditions_evnt_IncidentStatusCodeMapA* i = NULL;
	for (i = Dz1IncidentConditions_evnt_IncidentStatusCodeMapA; i->str; i++)
		if (strcmp(i->str, str) == 0) return i->v;
	return Dz1IncidentConditions_evnt_IncidentStatusCode_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1IncidentConditions_evnt_IncidentStatusCodeMapW
{
	wstr_t str;
	Dz1IncidentConditions_evnt_IncidentStatusCode v;
} Dz1IncidentConditions_evnt_IncidentStatusCodeMapW[] =
{
	{ (wchar_t*)L"other_no_additional_information_required", Dz1IncidentConditions_evnt_IncidentStatusCode_other_no_additional_information_required },
	{ (wchar_t*)L"other_additional_information_required", Dz1IncidentConditions_evnt_IncidentStatusCode_other_additional_information_required },
	{ (wchar_t*)L"incident_detected", Dz1IncidentConditions_evnt_IncidentStatusCode_incident_detected },
	{ (wchar_t*)L"confirmed_and_responding", Dz1IncidentConditions_evnt_IncidentStatusCode_confirmed_and_responding },
	{ (wchar_t*)L"cleared_and_recovering", Dz1IncidentConditions_evnt_IncidentStatusCode_cleared_and_recovering },
	{ (wchar_t*)L"over_and_done", Dz1IncidentConditions_evnt_IncidentStatusCode_over_and_done },
	{ (wchar_t*)L"other", Dz1IncidentConditions_evnt_IncidentStatusCode_other },
	{ NULL, Dz1IncidentConditions_evnt_IncidentStatusCode_max }
};

wstr_t Dz1IncidentConditions_evnt_IncidentStatusCodeStrW(Dz1IncidentConditions_evnt_IncidentStatusCode v)
{
	struct Dz1IncidentConditions_evnt_IncidentStatusCodeMapW* i = NULL;
	for (i = Dz1IncidentConditions_evnt_IncidentStatusCodeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1IncidentConditions_evnt_IncidentStatusCode Dz1IncidentConditions_evnt_IncidentStatusCodeFromStrW(wstr_t str)
{
	struct Dz1IncidentConditions_evnt_IncidentStatusCodeMapW* i = NULL;
	for (i = Dz1IncidentConditions_evnt_IncidentStatusCodeMapW; i->str; i++)
		if (wcscmp(i->str, str) == 0) return i->v;
	return Dz1IncidentConditions_evnt_IncidentStatusCode_max;
}
#endif // UNIX_SYSTEM

Dz1IncidentConditions_evnt_IncidentStatusCode* Dz1IncidentConditions_evnt_IncidentStatusCode_new(Dz1IncidentConditions_evnt_IncidentStatusCode* src, Dz1Error* err) {
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1IncidentConditions_evnt_IncidentStatusCode* __internal_ret = (Dz1IncidentConditions_evnt_IncidentStatusCode*)Dz1Calloc(sizeof(Dz1IncidentConditions_evnt_IncidentStatusCode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
	}
	return __internal_ret;
}

void Dz1IncidentConditions_evnt_IncidentStatusCode_dump(Dz1IncidentConditions_evnt_IncidentStatusCode* v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1IncidentConditions_evnt_IncidentStatusCodeStr(*v));
}
void Dz1IncidentConditions_evnt_IncidentStatusCode_fdump(FILE* fp, Dz1IncidentConditions_evnt_IncidentStatusCode* v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), Dz1IncidentConditions_evnt_IncidentStatusCodeStr(*v));
}
// Dz1IncidentConditions_evnt_IncidentStatusCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentConditions_evnt_UpdateTypeCode
static struct Dz1IncidentConditions_evnt_UpdateTypeCodeMapA
{
	str_t str;
	Dz1IncidentConditions_evnt_UpdateTypeCode v;
} Dz1IncidentConditions_evnt_UpdateTypeCodeMapA[] =
{
	{ (char*)"other_no_additional_information_required", Dz1IncidentConditions_evnt_UpdateTypeCode_other_no_additional_information_required },
	{ (char*)"other_additional_information_required", Dz1IncidentConditions_evnt_UpdateTypeCode_other_additional_information_required },
	{ (char*)"new", Dz1IncidentConditions_evnt_UpdateTypeCode_new_code },
	{ (char*)"update", Dz1IncidentConditions_evnt_UpdateTypeCode_update },
	{ (char*)"delete", Dz1IncidentConditions_evnt_UpdateTypeCode_delete },
	{ (char*)"clear_or_closed", Dz1IncidentConditions_evnt_UpdateTypeCode_clear_or_closed },
	{ NULL, Dz1IncidentConditions_evnt_UpdateTypeCode_max }
};

str_t Dz1IncidentConditions_evnt_UpdateTypeCodeStrA(Dz1IncidentConditions_evnt_UpdateTypeCode v)
{
	struct Dz1IncidentConditions_evnt_UpdateTypeCodeMapA* i = NULL;
	for (i = Dz1IncidentConditions_evnt_UpdateTypeCodeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1IncidentConditions_evnt_UpdateTypeCode Dz1IncidentConditions_evnt_UpdateTypeCodeFromStrA(str_t str)
{
	struct Dz1IncidentConditions_evnt_UpdateTypeCodeMapA* i = NULL;
	for (i = Dz1IncidentConditions_evnt_UpdateTypeCodeMapA; i->str; i++)
		if (strcmp(i->str, str) == 0) return i->v;
	return Dz1IncidentConditions_evnt_UpdateTypeCode_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1IncidentConditions_evnt_UpdateTypeCodeMapW
{
	wstr_t str;
	Dz1IncidentConditions_evnt_UpdateTypeCode v;
} Dz1IncidentConditions_evnt_UpdateTypeCodeMapW[] =
{
	{ (wchar_t*)L"other_no_additional_information_required", Dz1IncidentConditions_evnt_UpdateTypeCode_other_no_additional_information_required },
	{ (wchar_t*)L"other_additional_information_required", Dz1IncidentConditions_evnt_UpdateTypeCode_other_additional_information_required },
	{ (wchar_t*)L"new", Dz1IncidentConditions_evnt_UpdateTypeCode_new_code },
	{ (wchar_t*)L"update", Dz1IncidentConditions_evnt_UpdateTypeCode_update },
	{ (wchar_t*)L"delete", Dz1IncidentConditions_evnt_UpdateTypeCode_delete },
	{ (wchar_t*)L"clear_or_closed", Dz1IncidentConditions_evnt_UpdateTypeCode_clear_or_closed },
	{ NULL, Dz1IncidentConditions_evnt_UpdateTypeCode_max }
};

wstr_t Dz1IncidentConditions_evnt_UpdateTypeCodeStrW(Dz1IncidentConditions_evnt_UpdateTypeCode v)
{
	struct Dz1IncidentConditions_evnt_UpdateTypeCodeMapW* i = NULL;
	for (i = Dz1IncidentConditions_evnt_UpdateTypeCodeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1IncidentConditions_evnt_UpdateTypeCode Dz1IncidentConditions_evnt_UpdateTypeCodeFromStrW(wstr_t str)
{
	struct Dz1IncidentConditions_evnt_UpdateTypeCodeMapW* i = NULL;
	for (i = Dz1IncidentConditions_evnt_UpdateTypeCodeMapW; i->str; i++)
		if (wcscmp(i->str, str) == 0) return i->v;
	return Dz1IncidentConditions_evnt_UpdateTypeCode_max;
}
#endif // UNIX_SYSTEM

Dz1IncidentConditions_evnt_UpdateTypeCode* Dz1IncidentConditions_evnt_UpdateTypeCode_new(Dz1IncidentConditions_evnt_UpdateTypeCode* src, Dz1Error* err) {
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1IncidentConditions_evnt_UpdateTypeCode* __internal_ret = (Dz1IncidentConditions_evnt_UpdateTypeCode*)Dz1Calloc(sizeof(Dz1IncidentConditions_evnt_UpdateTypeCode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
	}
	return __internal_ret;
}

void Dz1IncidentConditions_evnt_UpdateTypeCode_dump(Dz1IncidentConditions_evnt_UpdateTypeCode* v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1IncidentConditions_evnt_UpdateTypeCodeStr(*v));
}
void Dz1IncidentConditions_evnt_UpdateTypeCode_fdump(FILE* fp, Dz1IncidentConditions_evnt_UpdateTypeCode* v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), Dz1IncidentConditions_evnt_UpdateTypeCodeStr(*v));
}
// Dz1IncidentConditions_evnt_UpdateTypeCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentConditions
Dz1IncidentConditions* Dz1IncidentConditions_new(Dz1Asn1UTF8Str* node_NodeIdNumber,
	Dz1Asn1UTF8Str* link_LinkIdNumber,
	Dz1Asn1UTF8Str* orgn_ContatOrganizationNameText,
	Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode evnt_DescriptionTypeIncidentCode,
	Dz1Asn1BitStr* evnt_IncidentVehiclesInvolvedCode,
	Dz1IncidentConditions_evnt_IncidentStatusCode evnt_IncidentStatusCode,
	Dz1IncidentConditions_evnt_UpdateTypeCode evnt_UpdateTypeCode, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1IncidentConditions* __internal_ret = (Dz1IncidentConditions*)Dz1Calloc(sizeof(Dz1IncidentConditions), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1IncidentConditions_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->node_NodeIdNumber = node_NodeIdNumber;
		__internal_ret->link_LinkIdNumber = link_LinkIdNumber;
		__internal_ret->orgn_ContatOrganizationNameText = orgn_ContatOrganizationNameText;
		__internal_ret->evnt_DescriptionTypeIncidentCode = evnt_DescriptionTypeIncidentCode;
		__internal_ret->evnt_IncidentVehiclesInvolvedCode = evnt_IncidentVehiclesInvolvedCode;
		__internal_ret->evnt_IncidentStatusCode = evnt_IncidentStatusCode;
		__internal_ret->evnt_UpdateTypeCode = evnt_UpdateTypeCode;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1IncidentConditions_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1IncidentConditions* Dz1IncidentConditions_clone(Dz1IncidentConditions* src, Dz1Error* err)
{
	Dz1IncidentConditions* ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1IncidentConditions*)Dz1Calloc(sizeof(Dz1IncidentConditions), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1IncidentConditions_delAndSetNull, (void*)&ret);

		if (src->node_NodeIdNumber && (ret->node_NodeIdNumber = Dz1Asn1UTF8Str_clone(src->node_NodeIdNumber, errp)) == NULL) ERR_OUT(errp);
		else if (src->link_LinkIdNumber && (ret->link_LinkIdNumber = Dz1Asn1UTF8Str_clone(src->link_LinkIdNumber, errp)) == NULL) ERR_OUT(errp);
		else if (src->orgn_ContatOrganizationNameText && (ret->orgn_ContatOrganizationNameText = Dz1Asn1UTF8Str_clone(src->orgn_ContatOrganizationNameText, errp)) == NULL) ERR_OUT(errp);
		else if (src->evnt_DescriptionTypeIncidentOther && (ret->evnt_DescriptionTypeIncidentOther = Dz1Asn1UTF8Str_clone(src->evnt_DescriptionTypeIncidentOther, errp)) == NULL) ERR_OUT(errp);
		else if (src->evnt_IncidentVehiclesInvolvedCode && (ret->evnt_IncidentVehiclesInvolvedCode = Dz1Asn1BitStr_clone(src->evnt_IncidentVehiclesInvolvedCode, errp)) == NULL) ERR_OUT(errp);
		else if (src->evnt_IncidentVehiclesInvolvedOther && (ret->evnt_IncidentVehiclesInvolvedOther = Dz1Asn1UTF8Str_clone(src->evnt_IncidentVehiclesInvolvedOther, errp)) == NULL) ERR_OUT(errp);
		else if (src->evnt_IncidentStatusOther && (ret->evnt_IncidentStatusOther = Dz1Asn1UTF8Str_clone(src->evnt_IncidentStatusOther, errp)) == NULL) ERR_OUT(errp);
		else if (src->evnt_UpdateTypeOther && (ret->evnt_UpdateTypeOther = Dz1Asn1UTF8Str_clone(src->evnt_UpdateTypeOther, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->evnt_DescriptionTypeIncidentCode = src->evnt_DescriptionTypeIncidentCode;
			ret->evnt_IncidentStatusCode = src->evnt_IncidentStatusCode;
			ret->evnt_UpdateTypeCode = src->evnt_UpdateTypeCode;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1IncidentConditions_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1IncidentConditions_del(Dz1IncidentConditions* p)
{
	if (p == NULL) return;
	if (p->node_NodeIdNumber) Dz1Asn1UTF8Str_del(p->node_NodeIdNumber);
	if (p->link_LinkIdNumber) Dz1Asn1UTF8Str_del(p->link_LinkIdNumber);
	if (p->orgn_ContatOrganizationNameText) Dz1Asn1UTF8Str_del(p->orgn_ContatOrganizationNameText);
	if (p->evnt_DescriptionTypeIncidentOther) Dz1Asn1UTF8Str_del(p->evnt_DescriptionTypeIncidentOther);
	if (p->evnt_IncidentVehiclesInvolvedCode) Dz1Asn1BitStr_del(p->evnt_IncidentVehiclesInvolvedCode);
	if (p->evnt_IncidentVehiclesInvolvedOther) Dz1Asn1UTF8Str_del(p->evnt_IncidentVehiclesInvolvedOther);
	if (p->evnt_IncidentStatusOther) Dz1Asn1UTF8Str_del(p->evnt_IncidentStatusOther);
	if (p->evnt_UpdateTypeOther) Dz1Asn1UTF8Str_del(p->evnt_UpdateTypeOther);
	Dz1Free(p);
}

void Dz1IncidentConditions_dump(Dz1IncidentConditions* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	if (p->node_NodeIdNumber == NULL) Dz1Thread_tprintf(tab, Dz1T("node_NodeIdNumber = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("node_NodeIdNumber = ")); Dz1Asn1UTF8Str_dump(p->node_NodeIdNumber, tab); /* using dump func */ }

	if (p->link_LinkIdNumber == NULL) Dz1Thread_tprintf(tab, Dz1T("link_LinkIdNumber = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("link_LinkIdNumber = ")); Dz1Asn1UTF8Str_dump(p->link_LinkIdNumber, tab); /* using dump func */ }

	if (p->orgn_ContatOrganizationNameText == NULL) Dz1Thread_tprintf(tab, Dz1T("orgn_ContatOrganizationNameText = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("orgn_ContatOrganizationNameText = ")); Dz1Asn1UTF8Str_dump(p->orgn_ContatOrganizationNameText, tab); /* using dump func */ }

	Dz1Thread_tprintf(tab, Dz1T("evnt_DescriptionTypeIncidentCode = %s(%d)\n"), Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeStr(p->evnt_DescriptionTypeIncidentCode), p->evnt_DescriptionTypeIncidentCode);

	if (p->evnt_DescriptionTypeIncidentOther == NULL) Dz1Thread_tprintf(tab, Dz1T("evnt_DescriptionTypeIncidentOther = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("evnt_DescriptionTypeIncidentOther = ")); Dz1Asn1UTF8Str_dump(p->evnt_DescriptionTypeIncidentOther, tab); /* using dump func */ }

	if (p->evnt_IncidentVehiclesInvolvedCode == NULL) Dz1Thread_tprintf(tab, Dz1T("evnt_IncidentVehiclesInvolvedCode = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("evnt_IncidentVehiclesInvolvedCode = ")); Dz1Asn1BitStr_dump(p->evnt_IncidentVehiclesInvolvedCode, tab); /* using dump func */ }

	if (p->evnt_IncidentVehiclesInvolvedOther == NULL) Dz1Thread_tprintf(tab, Dz1T("evnt_IncidentVehiclesInvolvedOther = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("evnt_IncidentVehiclesInvolvedOther = ")); Dz1Asn1UTF8Str_dump(p->evnt_IncidentVehiclesInvolvedOther, tab); /* using dump func */ }

	Dz1Thread_tprintf(tab, Dz1T("evnt_IncidentStatusCode = %s(%d)\n"), Dz1IncidentConditions_evnt_IncidentStatusCodeStr(p->evnt_IncidentStatusCode), p->evnt_IncidentStatusCode);

	if (p->evnt_IncidentStatusOther == NULL) Dz1Thread_tprintf(tab, Dz1T("evnt_IncidentStatusOther = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("evnt_IncidentStatusOther = ")); Dz1Asn1UTF8Str_dump(p->evnt_IncidentStatusOther, tab); /* using dump func */ }

	Dz1Thread_tprintf(tab, Dz1T("evnt_UpdateTypeCode = %s(%d)\n"), Dz1IncidentConditions_evnt_UpdateTypeCodeStr(p->evnt_UpdateTypeCode), p->evnt_UpdateTypeCode);

	if (p->evnt_UpdateTypeOther == NULL) Dz1Thread_tprintf(tab, Dz1T("evnt_UpdateTypeOther = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("evnt_UpdateTypeOther = ")); Dz1Asn1UTF8Str_dump(p->evnt_UpdateTypeOther, tab); /* using dump func */ }

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
void Dz1IncidentConditions_fdump(FILE* fp, Dz1IncidentConditions* p, int tab)
{
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;

	if (p->node_NodeIdNumber == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("node_NodeIdNumber = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("node_NodeIdNumber = ")); Dz1Asn1UTF8Str_fdump(fp, p->node_NodeIdNumber, tab); }

	if (p->link_LinkIdNumber == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("link_LinkIdNumber = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("link_LinkIdNumber = ")); Dz1Asn1UTF8Str_fdump(fp, p->link_LinkIdNumber, tab); }

	if (p->orgn_ContatOrganizationNameText == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("orgn_ContatOrganizationNameText = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("orgn_ContatOrganizationNameText = ")); Dz1Asn1UTF8Str_fdump(fp, p->orgn_ContatOrganizationNameText, tab); }

	Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_DescriptionTypeIncidentCode = %s(%d)\n"), Dz1IncidentConditions_evnt_DescriptionTypeIncidentCodeStr(p->evnt_DescriptionTypeIncidentCode), p->evnt_DescriptionTypeIncidentCode);

	if (p->evnt_DescriptionTypeIncidentOther == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_DescriptionTypeIncidentOther = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_DescriptionTypeIncidentOther = ")); Dz1Asn1UTF8Str_fdump(fp, p->evnt_DescriptionTypeIncidentOther, tab); }

	if (p->evnt_IncidentVehiclesInvolvedCode == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_IncidentVehiclesInvolvedCode = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_IncidentVehiclesInvolvedCode = ")); Dz1Asn1BitStr_fdump(fp, p->evnt_IncidentVehiclesInvolvedCode, tab); }

	if (p->evnt_IncidentVehiclesInvolvedOther == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_IncidentVehiclesInvolvedOther = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_IncidentVehiclesInvolvedOther = ")); Dz1Asn1UTF8Str_fdump(fp, p->evnt_IncidentVehiclesInvolvedOther, tab); }

	Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_IncidentStatusCode = %s(%d)\n"), Dz1IncidentConditions_evnt_IncidentStatusCodeStr(p->evnt_IncidentStatusCode), p->evnt_IncidentStatusCode);

	if (p->evnt_IncidentStatusOther == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_IncidentStatusOther = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_IncidentStatusOther = ")); Dz1Asn1UTF8Str_fdump(fp, p->evnt_IncidentStatusOther, tab); }

	Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_UpdateTypeCode = %s(%d)\n"), Dz1IncidentConditions_evnt_UpdateTypeCodeStr(p->evnt_UpdateTypeCode), p->evnt_UpdateTypeCode);

	if (p->evnt_UpdateTypeOther == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_UpdateTypeOther = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("evnt_UpdateTypeOther = ")); Dz1Asn1UTF8Str_fdump(fp, p->evnt_UpdateTypeOther, tab); }

	Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
}
Dz1Error Dz1IncidentConditions_fromASN(Dz1IncidentConditions* dst, IncidentConditions* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((dst->node_NodeIdNumber = Dz1Asn1UTF8Str_newFromASN(&src->node_NodeIdNumber, &err)) == NULL) { Dz1Thread_printf("node_NodeIdNumber : "); ERR_OUT(&err); }
		else if ((dst->link_LinkIdNumber = Dz1Asn1UTF8Str_newFromASN(&src->link_LinkIdNumber, &err)) == NULL) { Dz1Thread_printf("link_LinkIdNumber : "); ERR_OUT(&err); }
		else if ((dst->orgn_ContatOrganizationNameText = Dz1Asn1UTF8Str_newFromASN(&src->orgn_ContatOrganizationNameText, &err)) == NULL) { Dz1Thread_printf("orgn_ContatOrganizationNameText : "); ERR_OUT(&err); }
		else if (src->DEF_IncidentConditions_evnt_DescriptionTypeIncidentOther && (dst->evnt_DescriptionTypeIncidentOther = Dz1Asn1UTF8Str_newFromASN(&src->evnt_DescriptionTypeIncidentOther, &err)) == NULL) ERR_OUT(&err);
		else if ((dst->evnt_IncidentVehiclesInvolvedCode = Dz1Asn1BitStr_newFromASN(&src->evnt_IncidentVehiclesInvolvedCode, &err)) == NULL) { Dz1Thread_printf("evnt_IncidentVehiclesInvolvedCode : "); ERR_OUT(&err); }
		else if (src->DEF_IncidentConditions_evnt_IncidentVehiclesInvolvedOther && (dst->evnt_IncidentVehiclesInvolvedOther = Dz1Asn1UTF8Str_newFromASN(&src->evnt_IncidentVehiclesInvolvedOther, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_IncidentConditions_evnt_IncidentStatusOther && (dst->evnt_IncidentStatusOther = Dz1Asn1UTF8Str_newFromASN(&src->evnt_IncidentStatusOther, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_IncidentConditions_evnt_UpdateTypeOther && (dst->evnt_UpdateTypeOther = Dz1Asn1UTF8Str_newFromASN(&src->evnt_UpdateTypeOther, &err)) == NULL) ERR_OUT(&err);
		else
		{
			dst->evnt_DescriptionTypeIncidentCode = (Dz1IncidentConditions_evnt_DescriptionTypeIncidentCode)src->evnt_DescriptionTypeIncidentCode;
			dst->evnt_IncidentStatusCode = (Dz1IncidentConditions_evnt_IncidentStatusCode)src->evnt_IncidentStatusCode;
			dst->evnt_UpdateTypeCode = (Dz1IncidentConditions_evnt_UpdateTypeCode)src->evnt_UpdateTypeCode;
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1IncidentConditions, IncidentConditions)

Dz1Error Dz1IncidentConditions_toASN(IncidentConditions* dst, Dz1IncidentConditions* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = Dz1Asn1UTF8Str_toASN(&dst->node_NodeIdNumber, src->node_NodeIdNumber, ws)).code) { Dz1Thread_printf("node_NodeIdNumber : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1UTF8Str_toASN(&dst->link_LinkIdNumber, src->link_LinkIdNumber, ws)).code) { Dz1Thread_printf("link_LinkIdNumber : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1UTF8Str_toASN(&dst->orgn_ContatOrganizationNameText, src->orgn_ContatOrganizationNameText, ws)).code) { Dz1Thread_printf("orgn_ContatOrganizationNameText : "); ERR_OUT(&err); }
		else if ((dst->DEF_IncidentConditions_evnt_DescriptionTypeIncidentOther = src->evnt_DescriptionTypeIncidentOther ? 1 : 0) == 1 && (err = Dz1Asn1UTF8Str_toASN(&dst->evnt_DescriptionTypeIncidentOther, src->evnt_DescriptionTypeIncidentOther, ws)).code) { Dz1Thread_printf("evnt_DescriptionTypeIncidentOther : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1BitStr_toASN(&dst->evnt_IncidentVehiclesInvolvedCode, src->evnt_IncidentVehiclesInvolvedCode, ws)).code) { Dz1Thread_printf("evnt_IncidentVehiclesInvolvedCode : "); ERR_OUT(&err); }
		else if ((dst->DEF_IncidentConditions_evnt_IncidentVehiclesInvolvedOther = src->evnt_IncidentVehiclesInvolvedOther ? 1 : 0) == 1 && (err = Dz1Asn1UTF8Str_toASN(&dst->evnt_IncidentVehiclesInvolvedOther, src->evnt_IncidentVehiclesInvolvedOther, ws)).code) { Dz1Thread_printf("evnt_IncidentVehiclesInvolvedOther : "); ERR_OUT(&err); }
		else if ((dst->DEF_IncidentConditions_evnt_IncidentStatusOther = src->evnt_IncidentStatusOther ? 1 : 0) == 1 && (err = Dz1Asn1UTF8Str_toASN(&dst->evnt_IncidentStatusOther, src->evnt_IncidentStatusOther, ws)).code) { Dz1Thread_printf("evnt_IncidentStatusOther : "); ERR_OUT(&err); }
		else if ((dst->DEF_IncidentConditions_evnt_UpdateTypeOther = src->evnt_UpdateTypeOther ? 1 : 0) == 1 && (err = Dz1Asn1UTF8Str_toASN(&dst->evnt_UpdateTypeOther, src->evnt_UpdateTypeOther, ws)).code) { Dz1Thread_printf("evnt_UpdateTypeOther : "); ERR_OUT(&err); }
		else
		{
			dst->evnt_DescriptionTypeIncidentCode = src->evnt_DescriptionTypeIncidentCode;
			dst->evnt_IncidentStatusCode = src->evnt_IncidentStatusCode;
			dst->evnt_UpdateTypeCode = src->evnt_UpdateTypeCode;
		}
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1IncidentConditions, IncidentConditions)
// Dz1IncidentConditions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1IncidentConditionsResponse
static Dz1Error Dz1IncidentConditionsResponse_add(Dz1IncidentConditionsResponse* p, Dz1IncidentConditions* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1IncidentConditionsResponseMkArrArg
{
	Dz1IncidentConditions** arr;
	unsigned int idx;
} Dz1IncidentConditionsResponseMkArrArg;

static Dz1Error _Dz1IncidentConditionsResponse_get_array(void* ptr, Dz1IncidentConditions* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1IncidentConditionsResponseMkArrArg* arg = (Dz1IncidentConditionsResponseMkArrArg*)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1IncidentConditions** Dz1IncidentConditionsResponse_get_array(Dz1IncidentConditionsResponse* p, unsigned int* ret_cnt, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err == NULL ? &_err : err;
	Dz1IncidentConditions** ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1IncidentConditions**)Dz1Calloc(sizeof(Dz1IncidentConditions*), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1IncidentConditionsResponseMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void*)ret);

		*errp = p->travel(p, _Dz1IncidentConditionsResponse_get_array, (void*)&arg);
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

static Dz1Error Dz1IncidentConditionsResponse_travelForward(Dz1IncidentConditionsResponse* p, Dz1Error(*func)(void* ptr, Dz1IncidentConditions* data), void* ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1IncidentConditionsResponse_travelBackward(Dz1IncidentConditionsResponse* p, Dz1Error(*func)(void* ptr, Dz1IncidentConditions* data), void* ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1IncidentConditionsResponse_count(Dz1IncidentConditionsResponse* p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1IncidentConditionsResponse* Dz1IncidentConditionsResponse_new(Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1IncidentConditionsResponse* ret = (Dz1IncidentConditionsResponse*)Dz1Calloc(sizeof(Dz1IncidentConditionsResponse), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1IncidentConditionsResponse_delAndSetNull, (void*)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
			(Dz1DelFunc)Dz1IncidentConditions_del,
			NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = Dz1IncidentConditionsResponse_add;
			ret->get_array = Dz1IncidentConditionsResponse_get_array;
			ret->travel = Dz1IncidentConditionsResponse_travelForward;
			ret->travelForward = Dz1IncidentConditionsResponse_travelForward;
			ret->travelBackward = Dz1IncidentConditionsResponse_travelBackward;
			ret->count = Dz1IncidentConditionsResponse_count;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1IncidentConditionsResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1IncidentConditionsResponse_clone(void* ptr, Dz1IncidentConditions* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1IncidentConditionsResponse* p = (Dz1IncidentConditionsResponse*)ptr;
	Dz1IncidentConditions* cloned = Dz1IncidentConditions_clone(data, &err);
	err = Dz1Fifo_push(p->storage, cloned);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1IncidentConditionsResponse* Dz1IncidentConditionsResponse_clone(Dz1IncidentConditionsResponse* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1IncidentConditionsResponse* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1IncidentConditionsResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1IncidentConditionsResponse_delAndSetNull, (void*)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1IncidentConditionsResponse_clone, (void*)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1IncidentConditionsResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1IncidentConditionsResponse_del(Dz1IncidentConditionsResponse* p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1IncidentConditionsResponse_dump(void* ptr, Dz1IncidentConditions* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	int tab = *(int*)ptr;
	Dz1Thread_tprintf(tab, Dz1T("entry = "));
	Dz1IncidentConditions_dump(p, tab);
	return err;
}

void Dz1IncidentConditionsResponse_dump(Dz1IncidentConditionsResponse* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;
	p->travel(p, _Dz1IncidentConditionsResponse_dump, (void*)&tab);
	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
typedef struct Dz1IncidentConditionsResponseFDumpArg
{
	FILE* fp;
	int tab;
} Dz1IncidentConditionsResponseFDumpArg;

static Dz1Error _Dz1IncidentConditionsResponse_fdump(void* ptr, Dz1IncidentConditions* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1IncidentConditionsResponseFDumpArg* arg = (Dz1IncidentConditionsResponseFDumpArg*)ptr;
	Dz1Thread_ftprintf(arg->fp, arg->tab, Dz1T("entry = "));
	Dz1IncidentConditions_fdump(arg->fp, p, arg->tab);
	return err;
}

void Dz1IncidentConditionsResponse_fdump(FILE* fp, Dz1IncidentConditionsResponse* p, int tab)
{
	Dz1IncidentConditionsResponseFDumpArg arg = { fp, tab };
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
	p->travel(p, _Dz1IncidentConditionsResponse_fdump, (void*)&arg);
	Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
}
PSEUDO_LIST_FROM_ASN(Dz1IncidentConditionsResponse, Dz1IncidentConditions, IncidentConditions)
DZ1_NEW_LIST_FROM_ASN(Dz1IncidentConditionsResponse, ASN1List)

PSEUDO_ENTRY_TO_ASN(Dz1IncidentConditionsResponse, Dz1IncidentConditions, IncidentConditions)
PSEUDO_LIST_TO_ASN(Dz1IncidentConditionsResponse)
DZ1_TO_NEW_ASN_LIST(Dz1IncidentConditionsResponse, ASN1List)

// Dz1IncidentConditionsResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1RoadwaySurfaceStatus
Dz1RoadwaySurfaceStatus* Dz1RoadwaySurfaceStatus_new(Dz1Asn1UTF8Str* node_NodeIdNumber,
	Dz1Asn1UTF8Str* link_LinkIdNumber,
	Dz1Asn1BitStr* link_SurfaceConditionCode,
	Dz1Asn1BitStr* link_LandBlockedOrClosedCode, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1RoadwaySurfaceStatus* __internal_ret = (Dz1RoadwaySurfaceStatus*)Dz1Calloc(sizeof(Dz1RoadwaySurfaceStatus), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1RoadwaySurfaceStatus_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->node_NodeIdNumber = node_NodeIdNumber;
		__internal_ret->link_LinkIdNumber = link_LinkIdNumber;
		__internal_ret->link_SurfaceConditionCode = link_SurfaceConditionCode;
		__internal_ret->link_LandBlockedOrClosedCode = link_LandBlockedOrClosedCode;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1RoadwaySurfaceStatus_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1RoadwaySurfaceStatus* Dz1RoadwaySurfaceStatus_clone(Dz1RoadwaySurfaceStatus* src, Dz1Error* err)
{
	Dz1RoadwaySurfaceStatus* ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1RoadwaySurfaceStatus*)Dz1Calloc(sizeof(Dz1RoadwaySurfaceStatus), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1RoadwaySurfaceStatus_delAndSetNull, (void*)&ret);

		if (src->node_NodeIdNumber && (ret->node_NodeIdNumber = Dz1Asn1UTF8Str_clone(src->node_NodeIdNumber, errp)) == NULL) ERR_OUT(errp);
		else if (src->link_LinkIdNumber && (ret->link_LinkIdNumber = Dz1Asn1UTF8Str_clone(src->link_LinkIdNumber, errp)) == NULL) ERR_OUT(errp);
		else if (src->link_SurfaceConditionCode && (ret->link_SurfaceConditionCode = Dz1Asn1BitStr_clone(src->link_SurfaceConditionCode, errp)) == NULL) ERR_OUT(errp);
		else if (src->link_LandBlockedOrClosedCode && (ret->link_LandBlockedOrClosedCode = Dz1Asn1BitStr_clone(src->link_LandBlockedOrClosedCode, errp)) == NULL) ERR_OUT(errp);
		else if (src->evsn_DataSurfacePrecipitationDepth && (ret->evsn_DataSurfacePrecipitationDepth = (u16_t*)Dz1Calloc(sizeof(u16_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->evsn_DataSurfaceTemperatureQuantity && (ret->evsn_DataSurfaceTemperatureQuantity = (u16_t*)Dz1Calloc(sizeof(u16_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			if (src->evsn_DataSurfacePrecipitationDepth != NULL && ret->evsn_DataSurfacePrecipitationDepth != NULL) *ret->evsn_DataSurfacePrecipitationDepth = *src->evsn_DataSurfacePrecipitationDepth;
			if (src->evsn_DataSurfaceTemperatureQuantity != NULL && ret->evsn_DataSurfaceTemperatureQuantity != NULL) *ret->evsn_DataSurfaceTemperatureQuantity = *src->evsn_DataSurfaceTemperatureQuantity;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1RoadwaySurfaceStatus_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1RoadwaySurfaceStatus_del(Dz1RoadwaySurfaceStatus* p)
{
	if (p == NULL) return;
	if (p->node_NodeIdNumber) Dz1Asn1UTF8Str_del(p->node_NodeIdNumber);
	if (p->link_LinkIdNumber) Dz1Asn1UTF8Str_del(p->link_LinkIdNumber);
	if (p->link_SurfaceConditionCode) Dz1Asn1BitStr_del(p->link_SurfaceConditionCode);
	if (p->link_LandBlockedOrClosedCode) Dz1Asn1BitStr_del(p->link_LandBlockedOrClosedCode);
	if (p->evsn_DataSurfacePrecipitationDepth) Dz1Free(p->evsn_DataSurfacePrecipitationDepth);
	if (p->evsn_DataSurfaceTemperatureQuantity) Dz1Free(p->evsn_DataSurfaceTemperatureQuantity);
	Dz1Free(p);
}

void Dz1RoadwaySurfaceStatus_dump(Dz1RoadwaySurfaceStatus* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	if (p->node_NodeIdNumber == NULL) Dz1Thread_tprintf(tab, Dz1T("node_NodeIdNumber = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("node_NodeIdNumber = ")); Dz1Asn1UTF8Str_dump(p->node_NodeIdNumber, tab); /* using dump func */ }

	if (p->link_LinkIdNumber == NULL) Dz1Thread_tprintf(tab, Dz1T("link_LinkIdNumber = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("link_LinkIdNumber = ")); Dz1Asn1UTF8Str_dump(p->link_LinkIdNumber, tab); /* using dump func */ }

	if (p->link_SurfaceConditionCode == NULL) Dz1Thread_tprintf(tab, Dz1T("link_SurfaceConditionCode = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("link_SurfaceConditionCode = ")); Dz1Asn1BitStr_dump(p->link_SurfaceConditionCode, tab); /* using dump func */ }

	if (p->link_LandBlockedOrClosedCode == NULL) Dz1Thread_tprintf(tab, Dz1T("link_LandBlockedOrClosedCode = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("link_LandBlockedOrClosedCode = ")); Dz1Asn1BitStr_dump(p->link_LandBlockedOrClosedCode, tab); /* using dump func */ }

	if (p->evsn_DataSurfacePrecipitationDepth == NULL) Dz1Thread_tprintf(tab, Dz1T("evsn_DataSurfacePrecipitationDepth = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("evsn_DataSurfacePrecipitationDepth = ")); Dz1u16_dump(p->evsn_DataSurfacePrecipitationDepth, tab); }

	if (p->evsn_DataSurfaceTemperatureQuantity == NULL) Dz1Thread_tprintf(tab, Dz1T("evsn_DataSurfaceTemperatureQuantity = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("evsn_DataSurfaceTemperatureQuantity = ")); Dz1u16_dump(p->evsn_DataSurfaceTemperatureQuantity, tab); }

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
void Dz1RoadwaySurfaceStatus_fdump(FILE* fp, Dz1RoadwaySurfaceStatus* p, int tab)
{
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;

	if (p->node_NodeIdNumber == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("node_NodeIdNumber = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("node_NodeIdNumber = ")); Dz1Asn1UTF8Str_fdump(fp, p->node_NodeIdNumber, tab); }

	if (p->link_LinkIdNumber == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("link_LinkIdNumber = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("link_LinkIdNumber = ")); Dz1Asn1UTF8Str_fdump(fp, p->link_LinkIdNumber, tab); }

	if (p->link_SurfaceConditionCode == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("link_SurfaceConditionCode = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("link_SurfaceConditionCode = ")); Dz1Asn1BitStr_fdump(fp, p->link_SurfaceConditionCode, tab); }

	if (p->link_LandBlockedOrClosedCode == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("link_LandBlockedOrClosedCode = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("link_LandBlockedOrClosedCode = ")); Dz1Asn1BitStr_fdump(fp, p->link_LandBlockedOrClosedCode, tab); }

	if (p->evsn_DataSurfacePrecipitationDepth == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("evsn_DataSurfacePrecipitationDepth = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("evsn_DataSurfacePrecipitationDepth = ")); Dz1u16_fdump(fp, p->evsn_DataSurfacePrecipitationDepth, tab); }

	if (p->evsn_DataSurfaceTemperatureQuantity == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("evsn_DataSurfaceTemperatureQuantity = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("evsn_DataSurfaceTemperatureQuantity = ")); Dz1u16_fdump(fp, p->evsn_DataSurfaceTemperatureQuantity, tab); }

	Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
}
Dz1Error Dz1RoadwaySurfaceStatus_fromASN(Dz1RoadwaySurfaceStatus* dst, RoadwaySurfaceStatus* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((dst->node_NodeIdNumber = Dz1Asn1UTF8Str_newFromASN(&src->node_NodeIdNumber, &err)) == NULL) { Dz1Thread_printf("node_NodeIdNumber : "); ERR_OUT(&err); }
		else if ((dst->link_LinkIdNumber = Dz1Asn1UTF8Str_newFromASN(&src->link_LinkIdNumber, &err)) == NULL) { Dz1Thread_printf("link_LinkIdNumber : "); ERR_OUT(&err); }
		else if ((dst->link_SurfaceConditionCode = Dz1Asn1BitStr_newFromASN(&src->link_SurfaceConditionCode, &err)) == NULL) { Dz1Thread_printf("link_SurfaceConditionCode : "); ERR_OUT(&err); }
		else if ((dst->link_LandBlockedOrClosedCode = Dz1Asn1BitStr_newFromASN(&src->link_LandBlockedOrClosedCode, &err)) == NULL) { Dz1Thread_printf("link_LandBlockedOrClosedCode : "); ERR_OUT(&err); }
		else if (src->DEF_RoadwaySurfaceStatus_evsn_DataSurfacePrecipitationDepth && (dst->evsn_DataSurfacePrecipitationDepth = u16_t_newFromASN(&src->evsn_DataSurfacePrecipitationDepth, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_RoadwaySurfaceStatus_evsn_DataSurfaceTemperatureQuantity && (dst->evsn_DataSurfaceTemperatureQuantity = u16_t_newFromASN(&src->evsn_DataSurfaceTemperatureQuantity, &err)) == NULL) ERR_OUT(&err);
		else
		{
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1RoadwaySurfaceStatus, RoadwaySurfaceStatus)

Dz1Error Dz1RoadwaySurfaceStatus_toASN(RoadwaySurfaceStatus* dst, Dz1RoadwaySurfaceStatus* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = Dz1Asn1UTF8Str_toASN(&dst->node_NodeIdNumber, src->node_NodeIdNumber, ws)).code) { Dz1Thread_printf("node_NodeIdNumber : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1UTF8Str_toASN(&dst->link_LinkIdNumber, src->link_LinkIdNumber, ws)).code) { Dz1Thread_printf("link_LinkIdNumber : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1BitStr_toASN(&dst->link_SurfaceConditionCode, src->link_SurfaceConditionCode, ws)).code) { Dz1Thread_printf("link_SurfaceConditionCode : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1BitStr_toASN(&dst->link_LandBlockedOrClosedCode, src->link_LandBlockedOrClosedCode, ws)).code) { Dz1Thread_printf("link_LandBlockedOrClosedCode : "); ERR_OUT(&err); }
		else if ((dst->DEF_RoadwaySurfaceStatus_evsn_DataSurfacePrecipitationDepth = src->evsn_DataSurfacePrecipitationDepth ? 1 : 0) == 1 && (err = u16_t_toASN(&dst->evsn_DataSurfacePrecipitationDepth, src->evsn_DataSurfacePrecipitationDepth, ws)).code) { Dz1Thread_printf("evsn_DataSurfacePrecipitationDepth : "); ERR_OUT(&err); }
		else if ((dst->DEF_RoadwaySurfaceStatus_evsn_DataSurfaceTemperatureQuantity = src->evsn_DataSurfaceTemperatureQuantity ? 1 : 0) == 1 && (err = u16_t_toASN(&dst->evsn_DataSurfaceTemperatureQuantity, src->evsn_DataSurfaceTemperatureQuantity, ws)).code) { Dz1Thread_printf("evsn_DataSurfaceTemperatureQuantity : "); ERR_OUT(&err); }
		else
		{
		}
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1RoadwaySurfaceStatus, RoadwaySurfaceStatus)
// Dz1RoadwaySurfaceStatus
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1RoadwaySurfaceStatusResponse
static Dz1Error Dz1RoadwaySurfaceStatusResponse_add(Dz1RoadwaySurfaceStatusResponse* p, Dz1RoadwaySurfaceStatus* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1RoadwaySurfaceStatusResponseMkArrArg
{
	Dz1RoadwaySurfaceStatus** arr;
	unsigned int idx;
} Dz1RoadwaySurfaceStatusResponseMkArrArg;

static Dz1Error _Dz1RoadwaySurfaceStatusResponse_get_array(void* ptr, Dz1RoadwaySurfaceStatus* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1RoadwaySurfaceStatusResponseMkArrArg* arg = (Dz1RoadwaySurfaceStatusResponseMkArrArg*)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1RoadwaySurfaceStatus** Dz1RoadwaySurfaceStatusResponse_get_array(Dz1RoadwaySurfaceStatusResponse* p, unsigned int* ret_cnt, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err == NULL ? &_err : err;
	Dz1RoadwaySurfaceStatus** ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1RoadwaySurfaceStatus**)Dz1Calloc(sizeof(Dz1RoadwaySurfaceStatus*), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1RoadwaySurfaceStatusResponseMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void*)ret);

		*errp = p->travel(p, _Dz1RoadwaySurfaceStatusResponse_get_array, (void*)&arg);
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

static Dz1Error Dz1RoadwaySurfaceStatusResponse_travelForward(Dz1RoadwaySurfaceStatusResponse* p, Dz1Error(*func)(void* ptr, Dz1RoadwaySurfaceStatus* data), void* ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1RoadwaySurfaceStatusResponse_travelBackward(Dz1RoadwaySurfaceStatusResponse* p, Dz1Error(*func)(void* ptr, Dz1RoadwaySurfaceStatus* data), void* ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1RoadwaySurfaceStatusResponse_count(Dz1RoadwaySurfaceStatusResponse* p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1RoadwaySurfaceStatusResponse* Dz1RoadwaySurfaceStatusResponse_new(Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1RoadwaySurfaceStatusResponse* ret = (Dz1RoadwaySurfaceStatusResponse*)Dz1Calloc(sizeof(Dz1RoadwaySurfaceStatusResponse), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1RoadwaySurfaceStatusResponse_delAndSetNull, (void*)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
			(Dz1DelFunc)Dz1RoadwaySurfaceStatus_del,
			NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = Dz1RoadwaySurfaceStatusResponse_add;
			ret->get_array = Dz1RoadwaySurfaceStatusResponse_get_array;
			ret->travel = Dz1RoadwaySurfaceStatusResponse_travelForward;
			ret->travelForward = Dz1RoadwaySurfaceStatusResponse_travelForward;
			ret->travelBackward = Dz1RoadwaySurfaceStatusResponse_travelBackward;
			ret->count = Dz1RoadwaySurfaceStatusResponse_count;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1RoadwaySurfaceStatusResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1RoadwaySurfaceStatusResponse_clone(void* ptr, Dz1RoadwaySurfaceStatus* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1RoadwaySurfaceStatusResponse* p = (Dz1RoadwaySurfaceStatusResponse*)ptr;
	Dz1RoadwaySurfaceStatus* cloned = Dz1RoadwaySurfaceStatus_clone(data, &err);
	err = Dz1Fifo_push(p->storage, cloned);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1RoadwaySurfaceStatusResponse* Dz1RoadwaySurfaceStatusResponse_clone(Dz1RoadwaySurfaceStatusResponse* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1RoadwaySurfaceStatusResponse* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1RoadwaySurfaceStatusResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1RoadwaySurfaceStatusResponse_delAndSetNull, (void*)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1RoadwaySurfaceStatusResponse_clone, (void*)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1RoadwaySurfaceStatusResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1RoadwaySurfaceStatusResponse_del(Dz1RoadwaySurfaceStatusResponse* p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1RoadwaySurfaceStatusResponse_dump(void* ptr, Dz1RoadwaySurfaceStatus* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	int tab = *(int*)ptr;
	Dz1Thread_tprintf(tab, Dz1T("entry = "));
	Dz1RoadwaySurfaceStatus_dump(p, tab);
	return err;
}

void Dz1RoadwaySurfaceStatusResponse_dump(Dz1RoadwaySurfaceStatusResponse* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;
	p->travel(p, _Dz1RoadwaySurfaceStatusResponse_dump, (void*)&tab);
	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
typedef struct Dz1RoadwaySurfaceStatusResponseFDumpArg
{
	FILE* fp;
	int tab;
} Dz1RoadwaySurfaceStatusResponseFDumpArg;

static Dz1Error _Dz1RoadwaySurfaceStatusResponse_fdump(void* ptr, Dz1RoadwaySurfaceStatus* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1RoadwaySurfaceStatusResponseFDumpArg* arg = (Dz1RoadwaySurfaceStatusResponseFDumpArg*)ptr;
	Dz1Thread_ftprintf(arg->fp, arg->tab, Dz1T("entry = "));
	Dz1RoadwaySurfaceStatus_fdump(arg->fp, p, arg->tab);
	return err;
}

void Dz1RoadwaySurfaceStatusResponse_fdump(FILE* fp, Dz1RoadwaySurfaceStatusResponse* p, int tab)
{
	Dz1RoadwaySurfaceStatusResponseFDumpArg arg = { fp, tab };
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
	p->travel(p, _Dz1RoadwaySurfaceStatusResponse_fdump, (void*)&arg);
	Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
}
PSEUDO_LIST_FROM_ASN(Dz1RoadwaySurfaceStatusResponse, Dz1RoadwaySurfaceStatus, RoadwaySurfaceStatus)
DZ1_NEW_LIST_FROM_ASN(Dz1RoadwaySurfaceStatusResponse, ASN1List)

PSEUDO_ENTRY_TO_ASN(Dz1RoadwaySurfaceStatusResponse, Dz1RoadwaySurfaceStatus, RoadwaySurfaceStatus)
PSEUDO_LIST_TO_ASN(Dz1RoadwaySurfaceStatusResponse)
DZ1_TO_NEW_ASN_LIST(Dz1RoadwaySurfaceStatusResponse, ASN1List)

// Dz1RoadwaySurfaceStatusResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WeatherInformation_wthr_ForecastOrActualCode
static struct Dz1WeatherInformation_wthr_ForecastOrActualCodeMapA
{
	str_t str;
	Dz1WeatherInformation_wthr_ForecastOrActualCode v;
} Dz1WeatherInformation_wthr_ForecastOrActualCodeMapA[] =
{
	{ (char*)"actual", Dz1WeatherInformation_wthr_ForecastOrActualCode_actual },
	{ (char*)"forecast", Dz1WeatherInformation_wthr_ForecastOrActualCode_forecast },
	{ NULL, Dz1WeatherInformation_wthr_ForecastOrActualCode_max }
};

str_t Dz1WeatherInformation_wthr_ForecastOrActualCodeStrA(Dz1WeatherInformation_wthr_ForecastOrActualCode v)
{
	struct Dz1WeatherInformation_wthr_ForecastOrActualCodeMapA* i = NULL;
	for (i = Dz1WeatherInformation_wthr_ForecastOrActualCodeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1WeatherInformation_wthr_ForecastOrActualCode Dz1WeatherInformation_wthr_ForecastOrActualCodeFromStrA(str_t str)
{
	struct Dz1WeatherInformation_wthr_ForecastOrActualCodeMapA* i = NULL;
	for (i = Dz1WeatherInformation_wthr_ForecastOrActualCodeMapA; i->str; i++)
		if (strcmp(i->str, str) == 0) return i->v;
	return Dz1WeatherInformation_wthr_ForecastOrActualCode_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1WeatherInformation_wthr_ForecastOrActualCodeMapW
{
	wstr_t str;
	Dz1WeatherInformation_wthr_ForecastOrActualCode v;
} Dz1WeatherInformation_wthr_ForecastOrActualCodeMapW[] =
{
	{ (wchar_t*)L"actual", Dz1WeatherInformation_wthr_ForecastOrActualCode_actual },
	{ (wchar_t*)L"forecast", Dz1WeatherInformation_wthr_ForecastOrActualCode_forecast },
	{ NULL, Dz1WeatherInformation_wthr_ForecastOrActualCode_max }
};

wstr_t Dz1WeatherInformation_wthr_ForecastOrActualCodeStrW(Dz1WeatherInformation_wthr_ForecastOrActualCode v)
{
	struct Dz1WeatherInformation_wthr_ForecastOrActualCodeMapW* i = NULL;
	for (i = Dz1WeatherInformation_wthr_ForecastOrActualCodeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1WeatherInformation_wthr_ForecastOrActualCode Dz1WeatherInformation_wthr_ForecastOrActualCodeFromStrW(wstr_t str)
{
	struct Dz1WeatherInformation_wthr_ForecastOrActualCodeMapW* i = NULL;
	for (i = Dz1WeatherInformation_wthr_ForecastOrActualCodeMapW; i->str; i++)
		if (wcscmp(i->str, str) == 0) return i->v;
	return Dz1WeatherInformation_wthr_ForecastOrActualCode_max;
}
#endif // UNIX_SYSTEM

Dz1WeatherInformation_wthr_ForecastOrActualCode* Dz1WeatherInformation_wthr_ForecastOrActualCode_new(Dz1WeatherInformation_wthr_ForecastOrActualCode* src, Dz1Error* err) {
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1WeatherInformation_wthr_ForecastOrActualCode* __internal_ret = (Dz1WeatherInformation_wthr_ForecastOrActualCode*)Dz1Calloc(sizeof(Dz1WeatherInformation_wthr_ForecastOrActualCode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
	}
	return __internal_ret;
}

void Dz1WeatherInformation_wthr_ForecastOrActualCode_dump(Dz1WeatherInformation_wthr_ForecastOrActualCode* v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1WeatherInformation_wthr_ForecastOrActualCodeStr(*v));
}
void Dz1WeatherInformation_wthr_ForecastOrActualCode_fdump(FILE* fp, Dz1WeatherInformation_wthr_ForecastOrActualCode* v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), Dz1WeatherInformation_wthr_ForecastOrActualCodeStr(*v));
}
// Dz1WeatherInformation_wthr_ForecastOrActualCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WeatherInformation_wthr_WindDirectionCode
static struct Dz1WeatherInformation_wthr_WindDirectionCodeMapA
{
	str_t str;
	Dz1WeatherInformation_wthr_WindDirectionCode v;
} Dz1WeatherInformation_wthr_WindDirectionCodeMapA[] =
{
	{ (char*)"north", Dz1WeatherInformation_wthr_WindDirectionCode_north },
	{ (char*)"south", Dz1WeatherInformation_wthr_WindDirectionCode_south },
	{ (char*)"west", Dz1WeatherInformation_wthr_WindDirectionCode_west },
	{ (char*)"east", Dz1WeatherInformation_wthr_WindDirectionCode_east },
	{ (char*)"northwest", Dz1WeatherInformation_wthr_WindDirectionCode_northwest },
	{ (char*)"northeast", Dz1WeatherInformation_wthr_WindDirectionCode_northeast },
	{ (char*)"southwest", Dz1WeatherInformation_wthr_WindDirectionCode_southwest },
	{ (char*)"southeast", Dz1WeatherInformation_wthr_WindDirectionCode_southeast },
	{ NULL, Dz1WeatherInformation_wthr_WindDirectionCode_max }
};

str_t Dz1WeatherInformation_wthr_WindDirectionCodeStrA(Dz1WeatherInformation_wthr_WindDirectionCode v)
{
	struct Dz1WeatherInformation_wthr_WindDirectionCodeMapA* i = NULL;
	for (i = Dz1WeatherInformation_wthr_WindDirectionCodeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1WeatherInformation_wthr_WindDirectionCode Dz1WeatherInformation_wthr_WindDirectionCodeFromStrA(str_t str)
{
	struct Dz1WeatherInformation_wthr_WindDirectionCodeMapA* i = NULL;
	for (i = Dz1WeatherInformation_wthr_WindDirectionCodeMapA; i->str; i++)
		if (strcmp(i->str, str) == 0) return i->v;
	return Dz1WeatherInformation_wthr_WindDirectionCode_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1WeatherInformation_wthr_WindDirectionCodeMapW
{
	wstr_t str;
	Dz1WeatherInformation_wthr_WindDirectionCode v;
} Dz1WeatherInformation_wthr_WindDirectionCodeMapW[] =
{
	{ (wchar_t*)L"north", Dz1WeatherInformation_wthr_WindDirectionCode_north },
	{ (wchar_t*)L"south", Dz1WeatherInformation_wthr_WindDirectionCode_south },
	{ (wchar_t*)L"west", Dz1WeatherInformation_wthr_WindDirectionCode_west },
	{ (wchar_t*)L"east", Dz1WeatherInformation_wthr_WindDirectionCode_east },
	{ (wchar_t*)L"northwest", Dz1WeatherInformation_wthr_WindDirectionCode_northwest },
	{ (wchar_t*)L"northeast", Dz1WeatherInformation_wthr_WindDirectionCode_northeast },
	{ (wchar_t*)L"southwest", Dz1WeatherInformation_wthr_WindDirectionCode_southwest },
	{ (wchar_t*)L"southeast", Dz1WeatherInformation_wthr_WindDirectionCode_southeast },
	{ NULL, Dz1WeatherInformation_wthr_WindDirectionCode_max }
};

wstr_t Dz1WeatherInformation_wthr_WindDirectionCodeStrW(Dz1WeatherInformation_wthr_WindDirectionCode v)
{
	struct Dz1WeatherInformation_wthr_WindDirectionCodeMapW* i = NULL;
	for (i = Dz1WeatherInformation_wthr_WindDirectionCodeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1WeatherInformation_wthr_WindDirectionCode Dz1WeatherInformation_wthr_WindDirectionCodeFromStrW(wstr_t str)
{
	struct Dz1WeatherInformation_wthr_WindDirectionCodeMapW* i = NULL;
	for (i = Dz1WeatherInformation_wthr_WindDirectionCodeMapW; i->str; i++)
		if (wcscmp(i->str, str) == 0) return i->v;
	return Dz1WeatherInformation_wthr_WindDirectionCode_max;
}
#endif // UNIX_SYSTEM

Dz1WeatherInformation_wthr_WindDirectionCode* Dz1WeatherInformation_wthr_WindDirectionCode_new(Dz1WeatherInformation_wthr_WindDirectionCode* src, Dz1Error* err) {
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1WeatherInformation_wthr_WindDirectionCode* __internal_ret = (Dz1WeatherInformation_wthr_WindDirectionCode*)Dz1Calloc(sizeof(Dz1WeatherInformation_wthr_WindDirectionCode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
	}
	return __internal_ret;
}

void Dz1WeatherInformation_wthr_WindDirectionCode_dump(Dz1WeatherInformation_wthr_WindDirectionCode* v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1WeatherInformation_wthr_WindDirectionCodeStr(*v));
}
void Dz1WeatherInformation_wthr_WindDirectionCode_fdump(FILE* fp, Dz1WeatherInformation_wthr_WindDirectionCode* v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), Dz1WeatherInformation_wthr_WindDirectionCodeStr(*v));
}
// Dz1WeatherInformation_wthr_WindDirectionCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WeatherInformation
Dz1WeatherInformation* Dz1WeatherInformation_new(Dz1WeatherInformation_wthr_ForecastOrActualCode wthr_ForecastOrActualCode, u8_t wthr_ProbabilityPercent, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1WeatherInformation* __internal_ret = (Dz1WeatherInformation*)Dz1Calloc(sizeof(Dz1WeatherInformation), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1WeatherInformation_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->wthr_ForecastOrActualCode = wthr_ForecastOrActualCode;
		__internal_ret->wthr_ProbabilityPercent = wthr_ProbabilityPercent;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1WeatherInformation_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1WeatherInformation* Dz1WeatherInformation_clone(Dz1WeatherInformation* src, Dz1Error* err)
{
	Dz1WeatherInformation* ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1WeatherInformation*)Dz1Calloc(sizeof(Dz1WeatherInformation), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1WeatherInformation_delAndSetNull, (void*)&ret);

		if (src->wthr_TemperatureQuantity && (ret->wthr_TemperatureQuantity = (s8_t*)Dz1Calloc(sizeof(s8_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->wthr_HighTemperatureQuantity && (ret->wthr_HighTemperatureQuantity = (s8_t*)Dz1Calloc(sizeof(s8_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->wthr_LowTemperatureQuantity && (ret->wthr_LowTemperatureQuantity = (s8_t*)Dz1Calloc(sizeof(s8_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->wthr_SpecialConditions && (ret->wthr_SpecialConditions = Dz1Asn1BitStr_clone(src->wthr_SpecialConditions, errp)) == NULL) ERR_OUT(errp);
		else if (src->wthr_SpecialConditionsOther && (ret->wthr_SpecialConditionsOther = Dz1Asn1UTF8Str_clone(src->wthr_SpecialConditionsOther, errp)) == NULL) ERR_OUT(errp);
		else if (src->wthr_VisibilityQuantity && (ret->wthr_VisibilityQuantity = (u8_t*)Dz1Calloc(sizeof(u8_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->wthr_WindSpeedQuantity && (ret->wthr_WindSpeedQuantity = (u8_t*)Dz1Calloc(sizeof(u8_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->wthr_WindDirectionCode && (ret->wthr_WindDirectionCode = (Dz1WeatherInformation_wthr_WindDirectionCode*)Dz1Calloc(sizeof(Dz1WeatherInformation_wthr_WindDirectionCode), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->wthr_HumidityQuantity && (ret->wthr_HumidityQuantity = (u8_t*)Dz1Calloc(sizeof(u8_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->wthr_PressureQuantity && (ret->wthr_PressureQuantity = (u8_t*)Dz1Calloc(sizeof(u8_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->wthr_SunriseTimeGeneralizedTime && (ret->wthr_SunriseTimeGeneralizedTime = Dz1Asn1VisibleStr_clone(src->wthr_SunriseTimeGeneralizedTime, errp)) == NULL) ERR_OUT(errp);
		else if (src->wthr_SunsetTimeGeneralizedTime && (ret->wthr_SunsetTimeGeneralizedTime = Dz1Asn1VisibleStr_clone(src->wthr_SunsetTimeGeneralizedTime, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->wthr_ForecastOrActualCode = src->wthr_ForecastOrActualCode;
			if (src->wthr_TemperatureQuantity != NULL && ret->wthr_TemperatureQuantity != NULL) *ret->wthr_TemperatureQuantity = *src->wthr_TemperatureQuantity;
			if (src->wthr_HighTemperatureQuantity != NULL && ret->wthr_HighTemperatureQuantity != NULL) *ret->wthr_HighTemperatureQuantity = *src->wthr_HighTemperatureQuantity;
			if (src->wthr_LowTemperatureQuantity != NULL && ret->wthr_LowTemperatureQuantity != NULL) *ret->wthr_LowTemperatureQuantity = *src->wthr_LowTemperatureQuantity;
			ret->wthr_ProbabilityPercent = src->wthr_ProbabilityPercent;
			if (src->wthr_VisibilityQuantity != NULL && ret->wthr_VisibilityQuantity != NULL) *ret->wthr_VisibilityQuantity = *src->wthr_VisibilityQuantity;
			if (src->wthr_WindSpeedQuantity != NULL && ret->wthr_WindSpeedQuantity != NULL) *ret->wthr_WindSpeedQuantity = *src->wthr_WindSpeedQuantity;
			if (src->wthr_WindDirectionCode != NULL && ret->wthr_WindDirectionCode != NULL) *ret->wthr_WindDirectionCode = *src->wthr_WindDirectionCode;
			if (src->wthr_HumidityQuantity != NULL && ret->wthr_HumidityQuantity != NULL) *ret->wthr_HumidityQuantity = *src->wthr_HumidityQuantity;
			if (src->wthr_PressureQuantity != NULL && ret->wthr_PressureQuantity != NULL) *ret->wthr_PressureQuantity = *src->wthr_PressureQuantity;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1WeatherInformation_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1WeatherInformation_del(Dz1WeatherInformation* p)
{
	if (p == NULL) return;
	if (p->wthr_TemperatureQuantity) Dz1Free(p->wthr_TemperatureQuantity);
	if (p->wthr_HighTemperatureQuantity) Dz1Free(p->wthr_HighTemperatureQuantity);
	if (p->wthr_LowTemperatureQuantity) Dz1Free(p->wthr_LowTemperatureQuantity);
	if (p->wthr_SpecialConditions) Dz1Asn1BitStr_del(p->wthr_SpecialConditions);
	if (p->wthr_SpecialConditionsOther) Dz1Asn1UTF8Str_del(p->wthr_SpecialConditionsOther);
	if (p->wthr_VisibilityQuantity) Dz1Free(p->wthr_VisibilityQuantity);
	if (p->wthr_WindSpeedQuantity) Dz1Free(p->wthr_WindSpeedQuantity);
	if (p->wthr_WindDirectionCode) Dz1Free(p->wthr_WindDirectionCode);
	if (p->wthr_HumidityQuantity) Dz1Free(p->wthr_HumidityQuantity);
	if (p->wthr_PressureQuantity) Dz1Free(p->wthr_PressureQuantity);
	if (p->wthr_SunriseTimeGeneralizedTime) Dz1Asn1VisibleStr_del(p->wthr_SunriseTimeGeneralizedTime);
	if (p->wthr_SunsetTimeGeneralizedTime) Dz1Asn1VisibleStr_del(p->wthr_SunsetTimeGeneralizedTime);
	Dz1Free(p);
}

void Dz1WeatherInformation_dump(Dz1WeatherInformation* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	Dz1Thread_tprintf(tab, Dz1T("wthr_ForecastOrActualCode = %s(%d)\n"), Dz1WeatherInformation_wthr_ForecastOrActualCodeStr(p->wthr_ForecastOrActualCode), p->wthr_ForecastOrActualCode);

	if (p->wthr_TemperatureQuantity == NULL) Dz1Thread_tprintf(tab, Dz1T("wthr_TemperatureQuantity = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("wthr_TemperatureQuantity = ")); Dz1s8_dump(p->wthr_TemperatureQuantity, tab); }

	if (p->wthr_HighTemperatureQuantity == NULL) Dz1Thread_tprintf(tab, Dz1T("wthr_HighTemperatureQuantity = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("wthr_HighTemperatureQuantity = ")); Dz1s8_dump(p->wthr_HighTemperatureQuantity, tab); }

	if (p->wthr_LowTemperatureQuantity == NULL) Dz1Thread_tprintf(tab, Dz1T("wthr_LowTemperatureQuantity = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("wthr_LowTemperatureQuantity = ")); Dz1s8_dump(p->wthr_LowTemperatureQuantity, tab); }

	if (p->wthr_SpecialConditions == NULL) Dz1Thread_tprintf(tab, Dz1T("wthr_SpecialConditions = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("wthr_SpecialConditions = ")); Dz1Asn1BitStr_dump(p->wthr_SpecialConditions, tab); /* using dump func */ }

	if (p->wthr_SpecialConditionsOther == NULL) Dz1Thread_tprintf(tab, Dz1T("wthr_SpecialConditionsOther = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("wthr_SpecialConditionsOther = ")); Dz1Asn1UTF8Str_dump(p->wthr_SpecialConditionsOther, tab); /* using dump func */ }

	Dz1Thread_tprintf(tab, Dz1T("wthr_ProbabilityPercent = ")); Dz1u8_dump(&p->wthr_ProbabilityPercent, tab);

	if (p->wthr_VisibilityQuantity == NULL) Dz1Thread_tprintf(tab, Dz1T("wthr_VisibilityQuantity = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("wthr_VisibilityQuantity = ")); Dz1u8_dump(p->wthr_VisibilityQuantity, tab); }

	if (p->wthr_WindSpeedQuantity == NULL) Dz1Thread_tprintf(tab, Dz1T("wthr_WindSpeedQuantity = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("wthr_WindSpeedQuantity = ")); Dz1u8_dump(p->wthr_WindSpeedQuantity, tab); }

	if (p->wthr_WindDirectionCode == NULL) Dz1Thread_tprintf(tab, Dz1T("wthr_WindDirectionCode = NULL\n"));
	else Dz1Thread_tprintf(tab, Dz1T("wthr_WindDirectionCode = %s(%d)\n"), Dz1WeatherInformation_wthr_WindDirectionCodeStr(*p->wthr_WindDirectionCode), *p->wthr_WindDirectionCode);

	if (p->wthr_HumidityQuantity == NULL) Dz1Thread_tprintf(tab, Dz1T("wthr_HumidityQuantity = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("wthr_HumidityQuantity = ")); Dz1u8_dump(p->wthr_HumidityQuantity, tab); }

	if (p->wthr_PressureQuantity == NULL) Dz1Thread_tprintf(tab, Dz1T("wthr_PressureQuantity = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("wthr_PressureQuantity = ")); Dz1u8_dump(p->wthr_PressureQuantity, tab); }

	if (p->wthr_SunriseTimeGeneralizedTime == NULL) Dz1Thread_tprintf(tab, Dz1T("wthr_SunriseTimeGeneralizedTime = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("wthr_SunriseTimeGeneralizedTime = ")); Dz1Asn1VisibleStr_dump(p->wthr_SunriseTimeGeneralizedTime, tab); /* using dump func */ }

	if (p->wthr_SunsetTimeGeneralizedTime == NULL) Dz1Thread_tprintf(tab, Dz1T("wthr_SunsetTimeGeneralizedTime = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("wthr_SunsetTimeGeneralizedTime = ")); Dz1Asn1VisibleStr_dump(p->wthr_SunsetTimeGeneralizedTime, tab); /* using dump func */ }

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
void Dz1WeatherInformation_fdump(FILE* fp, Dz1WeatherInformation* p, int tab)
{
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;

	Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_ForecastOrActualCode = %s(%d)\n"), Dz1WeatherInformation_wthr_ForecastOrActualCodeStr(p->wthr_ForecastOrActualCode), p->wthr_ForecastOrActualCode);

	if (p->wthr_TemperatureQuantity == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_TemperatureQuantity = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_TemperatureQuantity = ")); Dz1s8_fdump(fp, p->wthr_TemperatureQuantity, tab); }

	if (p->wthr_HighTemperatureQuantity == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_HighTemperatureQuantity = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_HighTemperatureQuantity = ")); Dz1s8_fdump(fp, p->wthr_HighTemperatureQuantity, tab); }

	if (p->wthr_LowTemperatureQuantity == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_LowTemperatureQuantity = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_LowTemperatureQuantity = ")); Dz1s8_fdump(fp, p->wthr_LowTemperatureQuantity, tab); }

	if (p->wthr_SpecialConditions == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_SpecialConditions = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_SpecialConditions = ")); Dz1Asn1BitStr_fdump(fp, p->wthr_SpecialConditions, tab); }

	if (p->wthr_SpecialConditionsOther == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_SpecialConditionsOther = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_SpecialConditionsOther = ")); Dz1Asn1UTF8Str_fdump(fp, p->wthr_SpecialConditionsOther, tab); }

	Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_ProbabilityPercent = ")); Dz1u8_fdump(fp, &p->wthr_ProbabilityPercent, tab);

	if (p->wthr_VisibilityQuantity == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_VisibilityQuantity = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_VisibilityQuantity = ")); Dz1u8_fdump(fp, p->wthr_VisibilityQuantity, tab); }

	if (p->wthr_WindSpeedQuantity == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_WindSpeedQuantity = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_WindSpeedQuantity = ")); Dz1u8_fdump(fp, p->wthr_WindSpeedQuantity, tab); }

	if (p->wthr_WindDirectionCode == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_WindDirectionCode = NULL\n"));
	else Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_WindDirectionCode = %s(%d)\n"), Dz1WeatherInformation_wthr_WindDirectionCodeStr(*p->wthr_WindDirectionCode), *p->wthr_WindDirectionCode);

	if (p->wthr_HumidityQuantity == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_HumidityQuantity = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_HumidityQuantity = ")); Dz1u8_fdump(fp, p->wthr_HumidityQuantity, tab); }

	if (p->wthr_PressureQuantity == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_PressureQuantity = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_PressureQuantity = ")); Dz1u8_fdump(fp, p->wthr_PressureQuantity, tab); }

	if (p->wthr_SunriseTimeGeneralizedTime == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_SunriseTimeGeneralizedTime = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_SunriseTimeGeneralizedTime = ")); Dz1Asn1VisibleStr_fdump(fp, p->wthr_SunriseTimeGeneralizedTime, tab); }

	if (p->wthr_SunsetTimeGeneralizedTime == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_SunsetTimeGeneralizedTime = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("wthr_SunsetTimeGeneralizedTime = ")); Dz1Asn1VisibleStr_fdump(fp, p->wthr_SunsetTimeGeneralizedTime, tab); }

	Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
}
Dz1Error Dz1WeatherInformation_fromASN(Dz1WeatherInformation* dst, WeatherInformation* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		Dz1WeatherInformation_wthr_WindDirectionCode wthr_WindDirectionCode = (Dz1WeatherInformation_wthr_WindDirectionCode)(src->DEF_WeatherInformation_wthr_WindDirectionCode ? src->wthr_WindDirectionCode : 0);
		if (src->DEF_WeatherInformation_wthr_TemperatureQuantity && (dst->wthr_TemperatureQuantity = s8_t_newFromASN(&src->wthr_TemperatureQuantity, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_WeatherInformation_wthr_HighTemperatureQuantity && (dst->wthr_HighTemperatureQuantity = s8_t_newFromASN(&src->wthr_HighTemperatureQuantity, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_WeatherInformation_wthr_LowTemperatureQuantity && (dst->wthr_LowTemperatureQuantity = s8_t_newFromASN(&src->wthr_LowTemperatureQuantity, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_WeatherInformation_wthr_SpecialConditions && (dst->wthr_SpecialConditions = Dz1Asn1BitStr_newFromASN(&src->wthr_SpecialConditions, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_WeatherInformation_wthr_SpecialConditionsOther && (dst->wthr_SpecialConditionsOther = Dz1Asn1UTF8Str_newFromASN(&src->wthr_SpecialConditionsOther, &err)) == NULL) ERR_OUT(&err);
		else if ((err = u8_t_fromASN(&dst->wthr_ProbabilityPercent, &src->wthr_ProbabilityPercent)).code) { Dz1Thread_printf("wthr_ProbabilityPercent : "); ERR_OUT(&err); }
		else if (src->DEF_WeatherInformation_wthr_VisibilityQuantity && (dst->wthr_VisibilityQuantity = u8_t_newFromASN(&src->wthr_VisibilityQuantity, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_WeatherInformation_wthr_WindSpeedQuantity && (dst->wthr_WindSpeedQuantity = u8_t_newFromASN(&src->wthr_WindSpeedQuantity, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_WeatherInformation_wthr_WindDirectionCode && (dst->wthr_WindDirectionCode = Dz1WeatherInformation_wthr_WindDirectionCode_new(&wthr_WindDirectionCode, &err)) == NULL) { Dz1Thread_printf("wthr_WindDirectionCode : "); ERR_OUT(&err); }
		else if (src->DEF_WeatherInformation_wthr_HumidityQuantity && (dst->wthr_HumidityQuantity = u8_t_newFromASN(&src->wthr_HumidityQuantity, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_WeatherInformation_wthr_PressureQuantity && (dst->wthr_PressureQuantity = u8_t_newFromASN(&src->wthr_PressureQuantity, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_WeatherInformation_wthr_SunriseTimeGeneralizedTime && (dst->wthr_SunriseTimeGeneralizedTime = Dz1Asn1VisibleStr_newFromASN(&src->wthr_SunriseTimeGeneralizedTime, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_WeatherInformation_wthr_SunsetTimeGeneralizedTime && (dst->wthr_SunsetTimeGeneralizedTime = Dz1Asn1VisibleStr_newFromASN(&src->wthr_SunsetTimeGeneralizedTime, &err)) == NULL) ERR_OUT(&err);
		else
		{
			dst->wthr_ForecastOrActualCode = (Dz1WeatherInformation_wthr_ForecastOrActualCode)src->wthr_ForecastOrActualCode;
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1WeatherInformation, WeatherInformation)

Dz1Error Dz1WeatherInformation_toASN(WeatherInformation* dst, Dz1WeatherInformation* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((dst->DEF_WeatherInformation_wthr_TemperatureQuantity = src->wthr_TemperatureQuantity ? 1 : 0) == 1 && (err = s8_t_toASN(&dst->wthr_TemperatureQuantity, src->wthr_TemperatureQuantity, ws)).code) { Dz1Thread_printf("wthr_TemperatureQuantity : "); ERR_OUT(&err); }
		else if ((dst->DEF_WeatherInformation_wthr_HighTemperatureQuantity = src->wthr_HighTemperatureQuantity ? 1 : 0) == 1 && (err = s8_t_toASN(&dst->wthr_HighTemperatureQuantity, src->wthr_HighTemperatureQuantity, ws)).code) { Dz1Thread_printf("wthr_HighTemperatureQuantity : "); ERR_OUT(&err); }
		else if ((dst->DEF_WeatherInformation_wthr_LowTemperatureQuantity = src->wthr_LowTemperatureQuantity ? 1 : 0) == 1 && (err = s8_t_toASN(&dst->wthr_LowTemperatureQuantity, src->wthr_LowTemperatureQuantity, ws)).code) { Dz1Thread_printf("wthr_LowTemperatureQuantity : "); ERR_OUT(&err); }
		else if ((dst->DEF_WeatherInformation_wthr_SpecialConditions = src->wthr_SpecialConditions ? 1 : 0) == 1 && (err = Dz1Asn1BitStr_toASN(&dst->wthr_SpecialConditions, src->wthr_SpecialConditions, ws)).code) { Dz1Thread_printf("wthr_SpecialConditions : "); ERR_OUT(&err); }
		else if ((dst->DEF_WeatherInformation_wthr_SpecialConditionsOther = src->wthr_SpecialConditionsOther ? 1 : 0) == 1 && (err = Dz1Asn1UTF8Str_toASN(&dst->wthr_SpecialConditionsOther, src->wthr_SpecialConditionsOther, ws)).code) { Dz1Thread_printf("wthr_SpecialConditionsOther : "); ERR_OUT(&err); }
		else if ((err = u8_t_toASN(&dst->wthr_ProbabilityPercent, &src->wthr_ProbabilityPercent, ws)).code) { Dz1Thread_printf("wthr_ProbabilityPercent : "); ERR_OUT(&err); }
		else if ((dst->DEF_WeatherInformation_wthr_VisibilityQuantity = src->wthr_VisibilityQuantity ? 1 : 0) == 1 && (err = u8_t_toASN(&dst->wthr_VisibilityQuantity, src->wthr_VisibilityQuantity, ws)).code) { Dz1Thread_printf("wthr_VisibilityQuantity : "); ERR_OUT(&err); }
		else if ((dst->DEF_WeatherInformation_wthr_WindSpeedQuantity = src->wthr_WindSpeedQuantity ? 1 : 0) == 1 && (err = u8_t_toASN(&dst->wthr_WindSpeedQuantity, src->wthr_WindSpeedQuantity, ws)).code) { Dz1Thread_printf("wthr_WindSpeedQuantity : "); ERR_OUT(&err); }
		else if ((dst->DEF_WeatherInformation_wthr_HumidityQuantity = src->wthr_HumidityQuantity ? 1 : 0) == 1 && (err = u8_t_toASN(&dst->wthr_HumidityQuantity, src->wthr_HumidityQuantity, ws)).code) { Dz1Thread_printf("wthr_HumidityQuantity : "); ERR_OUT(&err); }
		else if ((dst->DEF_WeatherInformation_wthr_PressureQuantity = src->wthr_PressureQuantity ? 1 : 0) == 1 && (err = u8_t_toASN(&dst->wthr_PressureQuantity, src->wthr_PressureQuantity, ws)).code) { Dz1Thread_printf("wthr_PressureQuantity : "); ERR_OUT(&err); }
		else if ((dst->DEF_WeatherInformation_wthr_SunriseTimeGeneralizedTime = src->wthr_SunriseTimeGeneralizedTime ? 1 : 0) == 1 && (err = Dz1Asn1VisibleStr_toASN(&dst->wthr_SunriseTimeGeneralizedTime, src->wthr_SunriseTimeGeneralizedTime, ws)).code) { Dz1Thread_printf("wthr_SunriseTimeGeneralizedTime : "); ERR_OUT(&err); }
		else if ((dst->DEF_WeatherInformation_wthr_SunsetTimeGeneralizedTime = src->wthr_SunsetTimeGeneralizedTime ? 1 : 0) == 1 && (err = Dz1Asn1VisibleStr_toASN(&dst->wthr_SunsetTimeGeneralizedTime, src->wthr_SunsetTimeGeneralizedTime, ws)).code) { Dz1Thread_printf("wthr_SunsetTimeGeneralizedTime : "); ERR_OUT(&err); }
		else
		{
			dst->wthr_ForecastOrActualCode = src->wthr_ForecastOrActualCode;
			if ((dst->DEF_WeatherInformation_wthr_WindDirectionCode = src->wthr_WindDirectionCode ? 1 : 0) == 1) dst->wthr_WindDirectionCode = *src->wthr_WindDirectionCode;
		}
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1WeatherInformation, WeatherInformation)
// Dz1WeatherInformation
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1WeatherInformationResponse
static Dz1Error Dz1WeatherInformationResponse_add(Dz1WeatherInformationResponse* p, Dz1WeatherInformation* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1WeatherInformationResponseMkArrArg
{
	Dz1WeatherInformation** arr;
	unsigned int idx;
} Dz1WeatherInformationResponseMkArrArg;

static Dz1Error _Dz1WeatherInformationResponse_get_array(void* ptr, Dz1WeatherInformation* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1WeatherInformationResponseMkArrArg* arg = (Dz1WeatherInformationResponseMkArrArg*)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1WeatherInformation** Dz1WeatherInformationResponse_get_array(Dz1WeatherInformationResponse* p, unsigned int* ret_cnt, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err == NULL ? &_err : err;
	Dz1WeatherInformation** ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1WeatherInformation**)Dz1Calloc(sizeof(Dz1WeatherInformation*), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1WeatherInformationResponseMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void*)ret);

		*errp = p->travel(p, _Dz1WeatherInformationResponse_get_array, (void*)&arg);
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

static Dz1Error Dz1WeatherInformationResponse_travelForward(Dz1WeatherInformationResponse* p, Dz1Error(*func)(void* ptr, Dz1WeatherInformation* data), void* ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1WeatherInformationResponse_travelBackward(Dz1WeatherInformationResponse* p, Dz1Error(*func)(void* ptr, Dz1WeatherInformation* data), void* ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1WeatherInformationResponse_count(Dz1WeatherInformationResponse* p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1WeatherInformationResponse* Dz1WeatherInformationResponse_new(Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1WeatherInformationResponse* ret = (Dz1WeatherInformationResponse*)Dz1Calloc(sizeof(Dz1WeatherInformationResponse), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1WeatherInformationResponse_delAndSetNull, (void*)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
			(Dz1DelFunc)Dz1WeatherInformation_del,
			NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = Dz1WeatherInformationResponse_add;
			ret->get_array = Dz1WeatherInformationResponse_get_array;
			ret->travel = Dz1WeatherInformationResponse_travelForward;
			ret->travelForward = Dz1WeatherInformationResponse_travelForward;
			ret->travelBackward = Dz1WeatherInformationResponse_travelBackward;
			ret->count = Dz1WeatherInformationResponse_count;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1WeatherInformationResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1WeatherInformationResponse_clone(void* ptr, Dz1WeatherInformation* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1WeatherInformationResponse* p = (Dz1WeatherInformationResponse*)ptr;
	Dz1WeatherInformation* cloned = Dz1WeatherInformation_clone(data, &err);
	err = Dz1Fifo_push(p->storage, cloned);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1WeatherInformationResponse* Dz1WeatherInformationResponse_clone(Dz1WeatherInformationResponse* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1WeatherInformationResponse* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1WeatherInformationResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1WeatherInformationResponse_delAndSetNull, (void*)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1WeatherInformationResponse_clone, (void*)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1WeatherInformationResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1WeatherInformationResponse_del(Dz1WeatherInformationResponse* p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1WeatherInformationResponse_dump(void* ptr, Dz1WeatherInformation* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	int tab = *(int*)ptr;
	Dz1Thread_tprintf(tab, Dz1T("entry = "));
	Dz1WeatherInformation_dump(p, tab);
	return err;
}

void Dz1WeatherInformationResponse_dump(Dz1WeatherInformationResponse* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;
	p->travel(p, _Dz1WeatherInformationResponse_dump, (void*)&tab);
	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
typedef struct Dz1WeatherInformationResponseFDumpArg
{
	FILE* fp;
	int tab;
} Dz1WeatherInformationResponseFDumpArg;

static Dz1Error _Dz1WeatherInformationResponse_fdump(void* ptr, Dz1WeatherInformation* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1WeatherInformationResponseFDumpArg* arg = (Dz1WeatherInformationResponseFDumpArg*)ptr;
	Dz1Thread_ftprintf(arg->fp, arg->tab, Dz1T("entry = "));
	Dz1WeatherInformation_fdump(arg->fp, p, arg->tab);
	return err;
}

void Dz1WeatherInformationResponse_fdump(FILE* fp, Dz1WeatherInformationResponse* p, int tab)
{
	Dz1WeatherInformationResponseFDumpArg arg = { fp, tab };
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
	p->travel(p, _Dz1WeatherInformationResponse_fdump, (void*)&arg);
	Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
}
PSEUDO_LIST_FROM_ASN(Dz1WeatherInformationResponse, Dz1WeatherInformation, WeatherInformation)
DZ1_NEW_LIST_FROM_ASN(Dz1WeatherInformationResponse, ASN1List)

PSEUDO_ENTRY_TO_ASN(Dz1WeatherInformationResponse, Dz1WeatherInformation, WeatherInformation)
PSEUDO_LIST_TO_ASN(Dz1WeatherInformationResponse)
DZ1_TO_NEW_ASN_LIST(Dz1WeatherInformationResponse, ASN1List)

// Dz1WeatherInformationResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode
static struct Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeMapA
{
	str_t str;
	Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode v;
} Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeMapA[] =
{
	{ (char*)"opengrass", Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_opengrass },
	{ (char*)"opensand", Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_opensand },
	{ (char*)"concrete_barrier_with_visibility_screens", Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_concrete_barrier_with_visibility_screens },
	{ (char*)"separate_roadways", Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_separate_roadways },
	{ (char*)"no_separation", Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_no_separation },
	{ (char*)"painted_median_no_access", Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_painted_median_no_access },
	{ (char*)"painted_MedianLeft_Turns", Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_painted_MedianLeft_Turns },
	{ (char*)"concrete_barrier", Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_concrete_barrier },
	{ (char*)"guardrail", Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_guardrail },
	{ NULL, Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_max }
};

str_t Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeStrA(Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode v)
{
	struct Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeMapA* i = NULL;
	for (i = Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeFromStrA(str_t str)
{
	struct Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeMapA* i = NULL;
	for (i = Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeMapA; i->str; i++)
		if (strcmp(i->str, str) == 0) return i->v;
	return Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeMapW
{
	wstr_t str;
	Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode v;
} Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeMapW[] =
{
	{ (wchar_t*)L"opengrass", Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_opengrass },
	{ (wchar_t*)L"opensand", Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_opensand },
	{ (wchar_t*)L"concrete_barrier_with_visibility_screens", Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_concrete_barrier_with_visibility_screens },
	{ (wchar_t*)L"separate_roadways", Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_separate_roadways },
	{ (wchar_t*)L"no_separation", Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_no_separation },
	{ (wchar_t*)L"painted_median_no_access", Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_painted_median_no_access },
	{ (wchar_t*)L"painted_MedianLeft_Turns", Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_painted_MedianLeft_Turns },
	{ (wchar_t*)L"concrete_barrier", Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_concrete_barrier },
	{ (wchar_t*)L"guardrail", Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_guardrail },
	{ NULL, Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_max }
};

wstr_t Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeStrW(Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode v)
{
	struct Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeMapW* i = NULL;
	for (i = Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeFromStrW(wstr_t str)
{
	struct Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeMapW* i = NULL;
	for (i = Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeMapW; i->str; i++)
		if (wcscmp(i->str, str) == 0) return i->v;
	return Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_max;
}
#endif // UNIX_SYSTEM

Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode* Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_new(Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode* src, Dz1Error* err) {
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode* __internal_ret = (Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode*)Dz1Calloc(sizeof(Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
	}
	return __internal_ret;
}

void Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_dump(Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode* v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeStr(*v));
}
void Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode_fdump(FILE* fp, Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode* v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeStr(*v));
}
// Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LinkRoadwayGeometry
Dz1LinkRoadwayGeometry* Dz1LinkRoadwayGeometry_new(Dz1Asn1UTF8Str* link_BeginNodeIdNumber,
	Dz1Asn1UTF8Str* link_EndNodeIdNumber,
	Dz1Asn1UTF8Str* link_JurisdictionText,
	Dz1Asn1BitStr* link_TypeCode,
	Dz1Asn1UTF8Str* link_NameText,
	u32_t link_LengthQuantity,
	Dz1Asn1BitStr* link_PavementTypeCode,
	Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode tfmg_LinkMedianTypeCode,
	u16_t tfmg_LinkNumLanesNumber,
	u8_t tfmg_LinkNumLanesOpenNumber, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1LinkRoadwayGeometry* __internal_ret = (Dz1LinkRoadwayGeometry*)Dz1Calloc(sizeof(Dz1LinkRoadwayGeometry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1LinkRoadwayGeometry_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->link_BeginNodeIdNumber = link_BeginNodeIdNumber;
		__internal_ret->link_EndNodeIdNumber = link_EndNodeIdNumber;
		__internal_ret->link_JurisdictionText = link_JurisdictionText;
		__internal_ret->link_TypeCode = link_TypeCode;
		__internal_ret->link_NameText = link_NameText;
		__internal_ret->link_LengthQuantity = link_LengthQuantity;
		__internal_ret->link_PavementTypeCode = link_PavementTypeCode;
		__internal_ret->tfmg_LinkMedianTypeCode = tfmg_LinkMedianTypeCode;
		__internal_ret->tfmg_LinkNumLanesNumber = tfmg_LinkNumLanesNumber;
		__internal_ret->tfmg_LinkNumLanesOpenNumber = tfmg_LinkNumLanesOpenNumber;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LinkRoadwayGeometry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1LinkRoadwayGeometry* Dz1LinkRoadwayGeometry_clone(Dz1LinkRoadwayGeometry* src, Dz1Error* err)
{
	Dz1LinkRoadwayGeometry* ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1LinkRoadwayGeometry*)Dz1Calloc(sizeof(Dz1LinkRoadwayGeometry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1LinkRoadwayGeometry_delAndSetNull, (void*)&ret);

		if (src->link_BeginNodeIdNumber && (ret->link_BeginNodeIdNumber = Dz1Asn1UTF8Str_clone(src->link_BeginNodeIdNumber, errp)) == NULL) ERR_OUT(errp);
		else if (src->link_BiginNodeLatitudeLocation && (ret->link_BiginNodeLatitudeLocation = (s64_t*)Dz1Calloc(sizeof(s64_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->link_BeginNodeLongitudeLocation && (ret->link_BeginNodeLongitudeLocation = (u32_t*)Dz1Calloc(sizeof(u32_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->link_EndNodeIdNumber && (ret->link_EndNodeIdNumber = Dz1Asn1UTF8Str_clone(src->link_EndNodeIdNumber, errp)) == NULL) ERR_OUT(errp);
		else if (src->link_EndNodeLatitudeLocation && (ret->link_EndNodeLatitudeLocation = (s64_t*)Dz1Calloc(sizeof(s64_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->link_EndNodeLongitudeLocation && (ret->link_EndNodeLongitudeLocation = (u32_t*)Dz1Calloc(sizeof(u32_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->link_JurisdictionText && (ret->link_JurisdictionText = Dz1Asn1UTF8Str_clone(src->link_JurisdictionText, errp)) == NULL) ERR_OUT(errp);
		else if (src->link_TypeCode && (ret->link_TypeCode = Dz1Asn1BitStr_clone(src->link_TypeCode, errp)) == NULL) ERR_OUT(errp);
		else if (src->link_NameText && (ret->link_NameText = Dz1Asn1UTF8Str_clone(src->link_NameText, errp)) == NULL) ERR_OUT(errp);
		else if (src->link_PavementTypeCode && (ret->link_PavementTypeCode = Dz1Asn1BitStr_clone(src->link_PavementTypeCode, errp)) == NULL) ERR_OUT(errp);
		else if (src->tfmg_LinkHeigthRestrictionQunatity && (ret->tfmg_LinkHeigthRestrictionQunatity = (u16_t*)Dz1Calloc(sizeof(u16_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->tfmg_LinkLeftShoulderWidthQuantity && (ret->tfmg_LinkLeftShoulderWidthQuantity = (u16_t*)Dz1Calloc(sizeof(u16_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->tfmg_LinkLengthRestrictionQuatity && (ret->tfmg_LinkLengthRestrictionQuatity = (u16_t*)Dz1Calloc(sizeof(u16_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->tfmg_LinkRightShoulderWidthQuantity && (ret->tfmg_LinkRightShoulderWidthQuantity = (u16_t*)Dz1Calloc(sizeof(u16_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			if (src->link_BiginNodeLatitudeLocation != NULL && ret->link_BiginNodeLatitudeLocation != NULL) *ret->link_BiginNodeLatitudeLocation = *src->link_BiginNodeLatitudeLocation;
			if (src->link_BeginNodeLongitudeLocation != NULL && ret->link_BeginNodeLongitudeLocation != NULL) *ret->link_BeginNodeLongitudeLocation = *src->link_BeginNodeLongitudeLocation;
			if (src->link_EndNodeLatitudeLocation != NULL && ret->link_EndNodeLatitudeLocation != NULL) *ret->link_EndNodeLatitudeLocation = *src->link_EndNodeLatitudeLocation;
			if (src->link_EndNodeLongitudeLocation != NULL && ret->link_EndNodeLongitudeLocation != NULL) *ret->link_EndNodeLongitudeLocation = *src->link_EndNodeLongitudeLocation;
			ret->link_LengthQuantity = src->link_LengthQuantity;
			if (src->tfmg_LinkHeigthRestrictionQunatity != NULL && ret->tfmg_LinkHeigthRestrictionQunatity != NULL) *ret->tfmg_LinkHeigthRestrictionQunatity = *src->tfmg_LinkHeigthRestrictionQunatity;
			if (src->tfmg_LinkLeftShoulderWidthQuantity != NULL && ret->tfmg_LinkLeftShoulderWidthQuantity != NULL) *ret->tfmg_LinkLeftShoulderWidthQuantity = *src->tfmg_LinkLeftShoulderWidthQuantity;
			if (src->tfmg_LinkLengthRestrictionQuatity != NULL && ret->tfmg_LinkLengthRestrictionQuatity != NULL) *ret->tfmg_LinkLengthRestrictionQuatity = *src->tfmg_LinkLengthRestrictionQuatity;
			ret->tfmg_LinkMedianTypeCode = src->tfmg_LinkMedianTypeCode;
			ret->tfmg_LinkNumLanesNumber = src->tfmg_LinkNumLanesNumber;
			ret->tfmg_LinkNumLanesOpenNumber = src->tfmg_LinkNumLanesOpenNumber;
			if (src->tfmg_LinkRightShoulderWidthQuantity != NULL && ret->tfmg_LinkRightShoulderWidthQuantity != NULL) *ret->tfmg_LinkRightShoulderWidthQuantity = *src->tfmg_LinkRightShoulderWidthQuantity;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LinkRoadwayGeometry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1LinkRoadwayGeometry_del(Dz1LinkRoadwayGeometry* p)
{
	if (p == NULL) return;
	if (p->link_BeginNodeIdNumber) Dz1Asn1UTF8Str_del(p->link_BeginNodeIdNumber);
	if (p->link_BiginNodeLatitudeLocation) Dz1Free(p->link_BiginNodeLatitudeLocation);
	if (p->link_BeginNodeLongitudeLocation) Dz1Free(p->link_BeginNodeLongitudeLocation);
	if (p->link_EndNodeIdNumber) Dz1Asn1UTF8Str_del(p->link_EndNodeIdNumber);
	if (p->link_EndNodeLatitudeLocation) Dz1Free(p->link_EndNodeLatitudeLocation);
	if (p->link_EndNodeLongitudeLocation) Dz1Free(p->link_EndNodeLongitudeLocation);
	if (p->link_JurisdictionText) Dz1Asn1UTF8Str_del(p->link_JurisdictionText);
	if (p->link_TypeCode) Dz1Asn1BitStr_del(p->link_TypeCode);
	if (p->link_NameText) Dz1Asn1UTF8Str_del(p->link_NameText);
	if (p->link_PavementTypeCode) Dz1Asn1BitStr_del(p->link_PavementTypeCode);
	if (p->tfmg_LinkHeigthRestrictionQunatity) Dz1Free(p->tfmg_LinkHeigthRestrictionQunatity);
	if (p->tfmg_LinkLeftShoulderWidthQuantity) Dz1Free(p->tfmg_LinkLeftShoulderWidthQuantity);
	if (p->tfmg_LinkLengthRestrictionQuatity) Dz1Free(p->tfmg_LinkLengthRestrictionQuatity);
	if (p->tfmg_LinkRightShoulderWidthQuantity) Dz1Free(p->tfmg_LinkRightShoulderWidthQuantity);
	Dz1Free(p);
}

void Dz1LinkRoadwayGeometry_dump(Dz1LinkRoadwayGeometry* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	if (p->link_BeginNodeIdNumber == NULL) Dz1Thread_tprintf(tab, Dz1T("link_BeginNodeIdNumber = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("link_BeginNodeIdNumber = ")); Dz1Asn1UTF8Str_dump(p->link_BeginNodeIdNumber, tab); /* using dump func */ }

	if (p->link_BiginNodeLatitudeLocation == NULL) Dz1Thread_tprintf(tab, Dz1T("link_BiginNodeLatitudeLocation = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("link_BiginNodeLatitudeLocation = ")); Dz1s64_dump(p->link_BiginNodeLatitudeLocation, tab); }

	if (p->link_BeginNodeLongitudeLocation == NULL) Dz1Thread_tprintf(tab, Dz1T("link_BeginNodeLongitudeLocation = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("link_BeginNodeLongitudeLocation = ")); Dz1u32_dump(p->link_BeginNodeLongitudeLocation, tab); }

	if (p->link_EndNodeIdNumber == NULL) Dz1Thread_tprintf(tab, Dz1T("link_EndNodeIdNumber = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("link_EndNodeIdNumber = ")); Dz1Asn1UTF8Str_dump(p->link_EndNodeIdNumber, tab); /* using dump func */ }

	if (p->link_EndNodeLatitudeLocation == NULL) Dz1Thread_tprintf(tab, Dz1T("link_EndNodeLatitudeLocation = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("link_EndNodeLatitudeLocation = ")); Dz1s64_dump(p->link_EndNodeLatitudeLocation, tab); }

	if (p->link_EndNodeLongitudeLocation == NULL) Dz1Thread_tprintf(tab, Dz1T("link_EndNodeLongitudeLocation = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("link_EndNodeLongitudeLocation = ")); Dz1u32_dump(p->link_EndNodeLongitudeLocation, tab); }

	if (p->link_JurisdictionText == NULL) Dz1Thread_tprintf(tab, Dz1T("link_JurisdictionText = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("link_JurisdictionText = ")); Dz1Asn1UTF8Str_dump(p->link_JurisdictionText, tab); /* using dump func */ }

	if (p->link_TypeCode == NULL) Dz1Thread_tprintf(tab, Dz1T("link_TypeCode = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("link_TypeCode = ")); Dz1Asn1BitStr_dump(p->link_TypeCode, tab); /* using dump func */ }

	if (p->link_NameText == NULL) Dz1Thread_tprintf(tab, Dz1T("link_NameText = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("link_NameText = ")); Dz1Asn1UTF8Str_dump(p->link_NameText, tab); /* using dump func */ }

	Dz1Thread_tprintf(tab, Dz1T("link_LengthQuantity = ")); Dz1u32_dump(&p->link_LengthQuantity, tab);

	if (p->link_PavementTypeCode == NULL) Dz1Thread_tprintf(tab, Dz1T("link_PavementTypeCode = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("link_PavementTypeCode = ")); Dz1Asn1BitStr_dump(p->link_PavementTypeCode, tab); /* using dump func */ }

	if (p->tfmg_LinkHeigthRestrictionQunatity == NULL) Dz1Thread_tprintf(tab, Dz1T("tfmg_LinkHeigthRestrictionQunatity = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("tfmg_LinkHeigthRestrictionQunatity = ")); Dz1u16_dump(p->tfmg_LinkHeigthRestrictionQunatity, tab); }

	if (p->tfmg_LinkLeftShoulderWidthQuantity == NULL) Dz1Thread_tprintf(tab, Dz1T("tfmg_LinkLeftShoulderWidthQuantity = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("tfmg_LinkLeftShoulderWidthQuantity = ")); Dz1u16_dump(p->tfmg_LinkLeftShoulderWidthQuantity, tab); }

	if (p->tfmg_LinkLengthRestrictionQuatity == NULL) Dz1Thread_tprintf(tab, Dz1T("tfmg_LinkLengthRestrictionQuatity = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("tfmg_LinkLengthRestrictionQuatity = ")); Dz1u16_dump(p->tfmg_LinkLengthRestrictionQuatity, tab); }

	Dz1Thread_tprintf(tab, Dz1T("tfmg_LinkMedianTypeCode = %s(%d)\n"), Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeStr(p->tfmg_LinkMedianTypeCode), p->tfmg_LinkMedianTypeCode);

	Dz1Thread_tprintf(tab, Dz1T("tfmg_LinkNumLanesNumber = ")); Dz1u16_dump(&p->tfmg_LinkNumLanesNumber, tab);

	Dz1Thread_tprintf(tab, Dz1T("tfmg_LinkNumLanesOpenNumber = ")); Dz1u8_dump(&p->tfmg_LinkNumLanesOpenNumber, tab);

	if (p->tfmg_LinkRightShoulderWidthQuantity == NULL) Dz1Thread_tprintf(tab, Dz1T("tfmg_LinkRightShoulderWidthQuantity = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("tfmg_LinkRightShoulderWidthQuantity = ")); Dz1u16_dump(p->tfmg_LinkRightShoulderWidthQuantity, tab); }

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
void Dz1LinkRoadwayGeometry_fdump(FILE* fp, Dz1LinkRoadwayGeometry* p, int tab)
{
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;

	if (p->link_BeginNodeIdNumber == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("link_BeginNodeIdNumber = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("link_BeginNodeIdNumber = ")); Dz1Asn1UTF8Str_fdump(fp, p->link_BeginNodeIdNumber, tab); }

	if (p->link_BiginNodeLatitudeLocation == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("link_BiginNodeLatitudeLocation = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("link_BiginNodeLatitudeLocation = ")); Dz1s64_fdump(fp, p->link_BiginNodeLatitudeLocation, tab); }

	if (p->link_BeginNodeLongitudeLocation == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("link_BeginNodeLongitudeLocation = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("link_BeginNodeLongitudeLocation = ")); Dz1u32_fdump(fp, p->link_BeginNodeLongitudeLocation, tab); }

	if (p->link_EndNodeIdNumber == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("link_EndNodeIdNumber = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("link_EndNodeIdNumber = ")); Dz1Asn1UTF8Str_fdump(fp, p->link_EndNodeIdNumber, tab); }

	if (p->link_EndNodeLatitudeLocation == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("link_EndNodeLatitudeLocation = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("link_EndNodeLatitudeLocation = ")); Dz1s64_fdump(fp, p->link_EndNodeLatitudeLocation, tab); }

	if (p->link_EndNodeLongitudeLocation == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("link_EndNodeLongitudeLocation = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("link_EndNodeLongitudeLocation = ")); Dz1u32_fdump(fp, p->link_EndNodeLongitudeLocation, tab); }

	if (p->link_JurisdictionText == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("link_JurisdictionText = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("link_JurisdictionText = ")); Dz1Asn1UTF8Str_fdump(fp, p->link_JurisdictionText, tab); }

	if (p->link_TypeCode == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("link_TypeCode = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("link_TypeCode = ")); Dz1Asn1BitStr_fdump(fp, p->link_TypeCode, tab); }

	if (p->link_NameText == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("link_NameText = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("link_NameText = ")); Dz1Asn1UTF8Str_fdump(fp, p->link_NameText, tab); }

	Dz1Thread_ftprintf(fp, tab, Dz1T("link_LengthQuantity = ")); Dz1u32_fdump(fp, &p->link_LengthQuantity, tab);

	if (p->link_PavementTypeCode == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("link_PavementTypeCode = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("link_PavementTypeCode = ")); Dz1Asn1BitStr_fdump(fp, p->link_PavementTypeCode, tab); }

	if (p->tfmg_LinkHeigthRestrictionQunatity == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("tfmg_LinkHeigthRestrictionQunatity = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("tfmg_LinkHeigthRestrictionQunatity = ")); Dz1u16_fdump(fp, p->tfmg_LinkHeigthRestrictionQunatity, tab); }

	if (p->tfmg_LinkLeftShoulderWidthQuantity == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("tfmg_LinkLeftShoulderWidthQuantity = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("tfmg_LinkLeftShoulderWidthQuantity = ")); Dz1u16_fdump(fp, p->tfmg_LinkLeftShoulderWidthQuantity, tab); }

	if (p->tfmg_LinkLengthRestrictionQuatity == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("tfmg_LinkLengthRestrictionQuatity = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("tfmg_LinkLengthRestrictionQuatity = ")); Dz1u16_fdump(fp, p->tfmg_LinkLengthRestrictionQuatity, tab); }

	Dz1Thread_ftprintf(fp, tab, Dz1T("tfmg_LinkMedianTypeCode = %s(%d)\n"), Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCodeStr(p->tfmg_LinkMedianTypeCode), p->tfmg_LinkMedianTypeCode);

	Dz1Thread_ftprintf(fp, tab, Dz1T("tfmg_LinkNumLanesNumber = ")); Dz1u16_fdump(fp, &p->tfmg_LinkNumLanesNumber, tab);

	Dz1Thread_ftprintf(fp, tab, Dz1T("tfmg_LinkNumLanesOpenNumber = ")); Dz1u8_fdump(fp, &p->tfmg_LinkNumLanesOpenNumber, tab);

	if (p->tfmg_LinkRightShoulderWidthQuantity == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("tfmg_LinkRightShoulderWidthQuantity = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("tfmg_LinkRightShoulderWidthQuantity = ")); Dz1u16_fdump(fp, p->tfmg_LinkRightShoulderWidthQuantity, tab); }

	Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
}
Dz1Error Dz1LinkRoadwayGeometry_fromASN(Dz1LinkRoadwayGeometry* dst, LinkRoadwayGeometry* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((dst->link_BeginNodeIdNumber = Dz1Asn1UTF8Str_newFromASN(&src->link_BeginNodeIdNumber, &err)) == NULL) { Dz1Thread_printf("link_BeginNodeIdNumber : "); ERR_OUT(&err); }
		else if (src->DEF_LinkRoadwayGeometry_link_BiginNodeLatitudeLocation && (dst->link_BiginNodeLatitudeLocation = s64_t_newFromASN(&src->link_BiginNodeLatitudeLocation, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_LinkRoadwayGeometry_link_BeginNodeLongitudeLocation && (dst->link_BeginNodeLongitudeLocation = u32_t_newFromASN(&src->link_BeginNodeLongitudeLocation, &err)) == NULL) ERR_OUT(&err);
		else if ((dst->link_EndNodeIdNumber = Dz1Asn1UTF8Str_newFromASN(&src->link_EndNodeIdNumber, &err)) == NULL) { Dz1Thread_printf("link_EndNodeIdNumber : "); ERR_OUT(&err); }
		else if (src->DEF_LinkRoadwayGeometry_link_EndNodeLatitudeLocation && (dst->link_EndNodeLatitudeLocation = s64_t_newFromASN(&src->link_EndNodeLatitudeLocation, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_LinkRoadwayGeometry_link_EndNodeLongitudeLocation && (dst->link_EndNodeLongitudeLocation = u32_t_newFromASN(&src->link_EndNodeLongitudeLocation, &err)) == NULL) ERR_OUT(&err);
		else if ((dst->link_JurisdictionText = Dz1Asn1UTF8Str_newFromASN(&src->link_JurisdictionText, &err)) == NULL) { Dz1Thread_printf("link_JurisdictionText : "); ERR_OUT(&err); }
		else if ((dst->link_TypeCode = Dz1Asn1BitStr_newFromASN(&src->link_TypeCode, &err)) == NULL) { Dz1Thread_printf("link_TypeCode : "); ERR_OUT(&err); }
		else if ((dst->link_NameText = Dz1Asn1UTF8Str_newFromASN(&src->link_NameText, &err)) == NULL) { Dz1Thread_printf("link_NameText : "); ERR_OUT(&err); }
		else if ((err = u32_t_fromASN(&dst->link_LengthQuantity, &src->link_LengthQuantity)).code) { Dz1Thread_printf("link_LengthQuantity : "); ERR_OUT(&err); }
		else if ((dst->link_PavementTypeCode = Dz1Asn1BitStr_newFromASN(&src->link_PavementTypeCode, &err)) == NULL) { Dz1Thread_printf("link_PavementTypeCode : "); ERR_OUT(&err); }
		else if (src->DEF_LinkRoadwayGeometry_tfmg_LinkHeigthRestrictionQunatity && (dst->tfmg_LinkHeigthRestrictionQunatity = u16_t_newFromASN(&src->tfmg_LinkHeigthRestrictionQunatity, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_LinkRoadwayGeometry_tfmg_LinkLeftShoulderWidthQuantity && (dst->tfmg_LinkLeftShoulderWidthQuantity = u16_t_newFromASN(&src->tfmg_LinkLeftShoulderWidthQuantity, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_LinkRoadwayGeometry_tfmg_LinkLengthRestrictionQuatity && (dst->tfmg_LinkLengthRestrictionQuatity = u16_t_newFromASN(&src->tfmg_LinkLengthRestrictionQuatity, &err)) == NULL) ERR_OUT(&err);
		else if ((err = u16_t_fromASN(&dst->tfmg_LinkNumLanesNumber, &src->tfmg_LinkNumLanesNumber)).code) { Dz1Thread_printf("tfmg_LinkNumLanesNumber : "); ERR_OUT(&err); }
		else if ((err = u8_t_fromASN(&dst->tfmg_LinkNumLanesOpenNumber, &src->tfmg_LinkNumLanesOpenNumber)).code) { Dz1Thread_printf("tfmg_LinkNumLanesOpenNumber : "); ERR_OUT(&err); }
		else if (src->DEF_LinkRoadwayGeometry_tfmg_LinkRightShoulderWidthQuantity && (dst->tfmg_LinkRightShoulderWidthQuantity = u16_t_newFromASN(&src->tfmg_LinkRightShoulderWidthQuantity, &err)) == NULL) ERR_OUT(&err);
		else
		{
			dst->tfmg_LinkMedianTypeCode = (Dz1LinkRoadwayGeometry_tfmg_LinkMedianTypeCode)src->tfmg_LinkMedianTypeCode;
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1LinkRoadwayGeometry, LinkRoadwayGeometry)

Dz1Error Dz1LinkRoadwayGeometry_toASN(LinkRoadwayGeometry* dst, Dz1LinkRoadwayGeometry* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = Dz1Asn1UTF8Str_toASN(&dst->link_BeginNodeIdNumber, src->link_BeginNodeIdNumber, ws)).code) { Dz1Thread_printf("link_BeginNodeIdNumber : "); ERR_OUT(&err); }
		else if ((dst->DEF_LinkRoadwayGeometry_link_BiginNodeLatitudeLocation = src->link_BiginNodeLatitudeLocation ? 1 : 0) == 1 && (err = s64_t_toASN(&dst->link_BiginNodeLatitudeLocation, src->link_BiginNodeLatitudeLocation, ws)).code) { Dz1Thread_printf("link_BiginNodeLatitudeLocation : "); ERR_OUT(&err); }
		else if ((dst->DEF_LinkRoadwayGeometry_link_BeginNodeLongitudeLocation = src->link_BeginNodeLongitudeLocation ? 1 : 0) == 1 && (err = u32_t_toASN(&dst->link_BeginNodeLongitudeLocation, src->link_BeginNodeLongitudeLocation, ws)).code) { Dz1Thread_printf("link_BeginNodeLongitudeLocation : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1UTF8Str_toASN(&dst->link_EndNodeIdNumber, src->link_EndNodeIdNumber, ws)).code) { Dz1Thread_printf("link_EndNodeIdNumber : "); ERR_OUT(&err); }
		else if ((dst->DEF_LinkRoadwayGeometry_link_EndNodeLatitudeLocation = src->link_EndNodeLatitudeLocation ? 1 : 0) == 1 && (err = s64_t_toASN(&dst->link_EndNodeLatitudeLocation, src->link_EndNodeLatitudeLocation, ws)).code) { Dz1Thread_printf("link_EndNodeLatitudeLocation : "); ERR_OUT(&err); }
		else if ((dst->DEF_LinkRoadwayGeometry_link_EndNodeLongitudeLocation = src->link_EndNodeLongitudeLocation ? 1 : 0) == 1 && (err = u32_t_toASN(&dst->link_EndNodeLongitudeLocation, src->link_EndNodeLongitudeLocation, ws)).code) { Dz1Thread_printf("link_EndNodeLongitudeLocation : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1UTF8Str_toASN(&dst->link_JurisdictionText, src->link_JurisdictionText, ws)).code) { Dz1Thread_printf("link_JurisdictionText : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1BitStr_toASN(&dst->link_TypeCode, src->link_TypeCode, ws)).code) { Dz1Thread_printf("link_TypeCode : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1UTF8Str_toASN(&dst->link_NameText, src->link_NameText, ws)).code) { Dz1Thread_printf("link_NameText : "); ERR_OUT(&err); }
		else if ((err = u32_t_toASN(&dst->link_LengthQuantity, &src->link_LengthQuantity, ws)).code) { Dz1Thread_printf("link_LengthQuantity : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1BitStr_toASN(&dst->link_PavementTypeCode, src->link_PavementTypeCode, ws)).code) { Dz1Thread_printf("link_PavementTypeCode : "); ERR_OUT(&err); }
		else if ((dst->DEF_LinkRoadwayGeometry_tfmg_LinkHeigthRestrictionQunatity = src->tfmg_LinkHeigthRestrictionQunatity ? 1 : 0) == 1 && (err = u16_t_toASN(&dst->tfmg_LinkHeigthRestrictionQunatity, src->tfmg_LinkHeigthRestrictionQunatity, ws)).code) { Dz1Thread_printf("tfmg_LinkHeigthRestrictionQunatity : "); ERR_OUT(&err); }
		else if ((dst->DEF_LinkRoadwayGeometry_tfmg_LinkLeftShoulderWidthQuantity = src->tfmg_LinkLeftShoulderWidthQuantity ? 1 : 0) == 1 && (err = u16_t_toASN(&dst->tfmg_LinkLeftShoulderWidthQuantity, src->tfmg_LinkLeftShoulderWidthQuantity, ws)).code) { Dz1Thread_printf("tfmg_LinkLeftShoulderWidthQuantity : "); ERR_OUT(&err); }
		else if ((dst->DEF_LinkRoadwayGeometry_tfmg_LinkLengthRestrictionQuatity = src->tfmg_LinkLengthRestrictionQuatity ? 1 : 0) == 1 && (err = u16_t_toASN(&dst->tfmg_LinkLengthRestrictionQuatity, src->tfmg_LinkLengthRestrictionQuatity, ws)).code) { Dz1Thread_printf("tfmg_LinkLengthRestrictionQuatity : "); ERR_OUT(&err); }
		else if ((err = u16_t_toASN(&dst->tfmg_LinkNumLanesNumber, &src->tfmg_LinkNumLanesNumber, ws)).code) { Dz1Thread_printf("tfmg_LinkNumLanesNumber : "); ERR_OUT(&err); }
		else if ((err = u8_t_toASN(&dst->tfmg_LinkNumLanesOpenNumber, &src->tfmg_LinkNumLanesOpenNumber, ws)).code) { Dz1Thread_printf("tfmg_LinkNumLanesOpenNumber : "); ERR_OUT(&err); }
		else if ((dst->DEF_LinkRoadwayGeometry_tfmg_LinkRightShoulderWidthQuantity = src->tfmg_LinkRightShoulderWidthQuantity ? 1 : 0) == 1 && (err = u16_t_toASN(&dst->tfmg_LinkRightShoulderWidthQuantity, src->tfmg_LinkRightShoulderWidthQuantity, ws)).code) { Dz1Thread_printf("tfmg_LinkRightShoulderWidthQuantity : "); ERR_OUT(&err); }
		else
		{
			dst->tfmg_LinkMedianTypeCode = src->tfmg_LinkMedianTypeCode;
		}
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1LinkRoadwayGeometry, LinkRoadwayGeometry)
// Dz1LinkRoadwayGeometry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1LinkRoadwayGeometryResponse
static Dz1Error Dz1LinkRoadwayGeometryResponse_add(Dz1LinkRoadwayGeometryResponse* p, Dz1LinkRoadwayGeometry* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1LinkRoadwayGeometryResponseMkArrArg
{
	Dz1LinkRoadwayGeometry** arr;
	unsigned int idx;
} Dz1LinkRoadwayGeometryResponseMkArrArg;

static Dz1Error _Dz1LinkRoadwayGeometryResponse_get_array(void* ptr, Dz1LinkRoadwayGeometry* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1LinkRoadwayGeometryResponseMkArrArg* arg = (Dz1LinkRoadwayGeometryResponseMkArrArg*)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1LinkRoadwayGeometry** Dz1LinkRoadwayGeometryResponse_get_array(Dz1LinkRoadwayGeometryResponse* p, unsigned int* ret_cnt, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err == NULL ? &_err : err;
	Dz1LinkRoadwayGeometry** ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1LinkRoadwayGeometry**)Dz1Calloc(sizeof(Dz1LinkRoadwayGeometry*), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1LinkRoadwayGeometryResponseMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void*)ret);

		*errp = p->travel(p, _Dz1LinkRoadwayGeometryResponse_get_array, (void*)&arg);
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

static Dz1Error Dz1LinkRoadwayGeometryResponse_travelForward(Dz1LinkRoadwayGeometryResponse* p, Dz1Error(*func)(void* ptr, Dz1LinkRoadwayGeometry* data), void* ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1LinkRoadwayGeometryResponse_travelBackward(Dz1LinkRoadwayGeometryResponse* p, Dz1Error(*func)(void* ptr, Dz1LinkRoadwayGeometry* data), void* ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1LinkRoadwayGeometryResponse_count(Dz1LinkRoadwayGeometryResponse* p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1LinkRoadwayGeometryResponse* Dz1LinkRoadwayGeometryResponse_new(Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1LinkRoadwayGeometryResponse* ret = (Dz1LinkRoadwayGeometryResponse*)Dz1Calloc(sizeof(Dz1LinkRoadwayGeometryResponse), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1LinkRoadwayGeometryResponse_delAndSetNull, (void*)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
			(Dz1DelFunc)Dz1LinkRoadwayGeometry_del,
			NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = Dz1LinkRoadwayGeometryResponse_add;
			ret->get_array = Dz1LinkRoadwayGeometryResponse_get_array;
			ret->travel = Dz1LinkRoadwayGeometryResponse_travelForward;
			ret->travelForward = Dz1LinkRoadwayGeometryResponse_travelForward;
			ret->travelBackward = Dz1LinkRoadwayGeometryResponse_travelBackward;
			ret->count = Dz1LinkRoadwayGeometryResponse_count;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LinkRoadwayGeometryResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1LinkRoadwayGeometryResponse_clone(void* ptr, Dz1LinkRoadwayGeometry* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1LinkRoadwayGeometryResponse* p = (Dz1LinkRoadwayGeometryResponse*)ptr;
	Dz1LinkRoadwayGeometry* cloned = Dz1LinkRoadwayGeometry_clone(data, &err);
	err = Dz1Fifo_push(p->storage, cloned);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1LinkRoadwayGeometryResponse* Dz1LinkRoadwayGeometryResponse_clone(Dz1LinkRoadwayGeometryResponse* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1LinkRoadwayGeometryResponse* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1LinkRoadwayGeometryResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1LinkRoadwayGeometryResponse_delAndSetNull, (void*)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1LinkRoadwayGeometryResponse_clone, (void*)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1LinkRoadwayGeometryResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1LinkRoadwayGeometryResponse_del(Dz1LinkRoadwayGeometryResponse* p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1LinkRoadwayGeometryResponse_dump(void* ptr, Dz1LinkRoadwayGeometry* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	int tab = *(int*)ptr;
	Dz1Thread_tprintf(tab, Dz1T("entry = "));
	Dz1LinkRoadwayGeometry_dump(p, tab);
	return err;
}

void Dz1LinkRoadwayGeometryResponse_dump(Dz1LinkRoadwayGeometryResponse* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;
	p->travel(p, _Dz1LinkRoadwayGeometryResponse_dump, (void*)&tab);
	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
typedef struct Dz1LinkRoadwayGeometryResponseFDumpArg
{
	FILE* fp;
	int tab;
} Dz1LinkRoadwayGeometryResponseFDumpArg;

static Dz1Error _Dz1LinkRoadwayGeometryResponse_fdump(void* ptr, Dz1LinkRoadwayGeometry* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1LinkRoadwayGeometryResponseFDumpArg* arg = (Dz1LinkRoadwayGeometryResponseFDumpArg*)ptr;
	Dz1Thread_ftprintf(arg->fp, arg->tab, Dz1T("entry = "));
	Dz1LinkRoadwayGeometry_fdump(arg->fp, p, arg->tab);
	return err;
}

void Dz1LinkRoadwayGeometryResponse_fdump(FILE* fp, Dz1LinkRoadwayGeometryResponse* p, int tab)
{
	Dz1LinkRoadwayGeometryResponseFDumpArg arg = { fp, tab };
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
	p->travel(p, _Dz1LinkRoadwayGeometryResponse_fdump, (void*)&arg);
	Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
}
PSEUDO_LIST_FROM_ASN(Dz1LinkRoadwayGeometryResponse, Dz1LinkRoadwayGeometry, LinkRoadwayGeometry)
DZ1_NEW_LIST_FROM_ASN(Dz1LinkRoadwayGeometryResponse, ASN1List)

PSEUDO_ENTRY_TO_ASN(Dz1LinkRoadwayGeometryResponse, Dz1LinkRoadwayGeometry, LinkRoadwayGeometry)
PSEUDO_LIST_TO_ASN(Dz1LinkRoadwayGeometryResponse)
DZ1_TO_NEW_ASN_LIST(Dz1LinkRoadwayGeometryResponse, ASN1List)

// Dz1LinkRoadwayGeometryResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ProbeVehicleDetection_vpbd_VehicleClass
static struct Dz1ProbeVehicleDetection_vpbd_VehicleClassMapA
{
	str_t str;
	Dz1ProbeVehicleDetection_vpbd_VehicleClass v;
} Dz1ProbeVehicleDetection_vpbd_VehicleClassMapA[] =
{
	{ (char*)"other_no_additional_information_required", Dz1ProbeVehicleDetection_vpbd_VehicleClass_other_no_additional_information_required },
	{ (char*)"other_additional_information_required", Dz1ProbeVehicleDetection_vpbd_VehicleClass_other_additional_information_required },
	{ (char*)"bus_vehicle", Dz1ProbeVehicleDetection_vpbd_VehicleClass_bus_vehicle },
	{ (char*)"taxi_vehicle", Dz1ProbeVehicleDetection_vpbd_VehicleClass_taxi_vehicle },
	{ (char*)"passenger_cars", Dz1ProbeVehicleDetection_vpbd_VehicleClass_passenger_cars },
	{ (char*)"emergency_vehicles", Dz1ProbeVehicleDetection_vpbd_VehicleClass_emergency_vehicles },
	{ (char*)"official_vehicle", Dz1ProbeVehicleDetection_vpbd_VehicleClass_official_vehicle },
	{ NULL, Dz1ProbeVehicleDetection_vpbd_VehicleClass_max }
};

str_t Dz1ProbeVehicleDetection_vpbd_VehicleClassStrA(Dz1ProbeVehicleDetection_vpbd_VehicleClass v)
{
	struct Dz1ProbeVehicleDetection_vpbd_VehicleClassMapA* i = NULL;
	for (i = Dz1ProbeVehicleDetection_vpbd_VehicleClassMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1ProbeVehicleDetection_vpbd_VehicleClass Dz1ProbeVehicleDetection_vpbd_VehicleClassFromStrA(str_t str)
{
	struct Dz1ProbeVehicleDetection_vpbd_VehicleClassMapA* i = NULL;
	for (i = Dz1ProbeVehicleDetection_vpbd_VehicleClassMapA; i->str; i++)
		if (strcmp(i->str, str) == 0) return i->v;
	return Dz1ProbeVehicleDetection_vpbd_VehicleClass_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1ProbeVehicleDetection_vpbd_VehicleClassMapW
{
	wstr_t str;
	Dz1ProbeVehicleDetection_vpbd_VehicleClass v;
} Dz1ProbeVehicleDetection_vpbd_VehicleClassMapW[] =
{
	{ (wchar_t*)L"other_no_additional_information_required", Dz1ProbeVehicleDetection_vpbd_VehicleClass_other_no_additional_information_required },
	{ (wchar_t*)L"other_additional_information_required", Dz1ProbeVehicleDetection_vpbd_VehicleClass_other_additional_information_required },
	{ (wchar_t*)L"bus_vehicle", Dz1ProbeVehicleDetection_vpbd_VehicleClass_bus_vehicle },
	{ (wchar_t*)L"taxi_vehicle", Dz1ProbeVehicleDetection_vpbd_VehicleClass_taxi_vehicle },
	{ (wchar_t*)L"passenger_cars", Dz1ProbeVehicleDetection_vpbd_VehicleClass_passenger_cars },
	{ (wchar_t*)L"emergency_vehicles", Dz1ProbeVehicleDetection_vpbd_VehicleClass_emergency_vehicles },
	{ (wchar_t*)L"official_vehicle", Dz1ProbeVehicleDetection_vpbd_VehicleClass_official_vehicle },
	{ NULL, Dz1ProbeVehicleDetection_vpbd_VehicleClass_max }
};

wstr_t Dz1ProbeVehicleDetection_vpbd_VehicleClassStrW(Dz1ProbeVehicleDetection_vpbd_VehicleClass v)
{
	struct Dz1ProbeVehicleDetection_vpbd_VehicleClassMapW* i = NULL;
	for (i = Dz1ProbeVehicleDetection_vpbd_VehicleClassMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1ProbeVehicleDetection_vpbd_VehicleClass Dz1ProbeVehicleDetection_vpbd_VehicleClassFromStrW(wstr_t str)
{
	struct Dz1ProbeVehicleDetection_vpbd_VehicleClassMapW* i = NULL;
	for (i = Dz1ProbeVehicleDetection_vpbd_VehicleClassMapW; i->str; i++)
		if (wcscmp(i->str, str) == 0) return i->v;
	return Dz1ProbeVehicleDetection_vpbd_VehicleClass_max;
}
#endif // UNIX_SYSTEM

Dz1ProbeVehicleDetection_vpbd_VehicleClass* Dz1ProbeVehicleDetection_vpbd_VehicleClass_new(Dz1ProbeVehicleDetection_vpbd_VehicleClass* src, Dz1Error* err) {
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1ProbeVehicleDetection_vpbd_VehicleClass* __internal_ret = (Dz1ProbeVehicleDetection_vpbd_VehicleClass*)Dz1Calloc(sizeof(Dz1ProbeVehicleDetection_vpbd_VehicleClass), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
	}
	return __internal_ret;
}

void Dz1ProbeVehicleDetection_vpbd_VehicleClass_dump(Dz1ProbeVehicleDetection_vpbd_VehicleClass* v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1ProbeVehicleDetection_vpbd_VehicleClassStr(*v));
}
void Dz1ProbeVehicleDetection_vpbd_VehicleClass_fdump(FILE* fp, Dz1ProbeVehicleDetection_vpbd_VehicleClass* v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), Dz1ProbeVehicleDetection_vpbd_VehicleClassStr(*v));
}
// Dz1ProbeVehicleDetection_vpbd_VehicleClass
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ProbeVehicleDetection
Dz1ProbeVehicleDetection* Dz1ProbeVehicleDetection_new(Dz1Asn1UTF8Str* vpbd_VehicleIdNumber,
	Dz1ProbeVehicleDetection_vpbd_VehicleClass vpbd_VehicleClass,
	Dz1Asn1VisibleStr* vpbd_VehicleTimeInGeneralizedTime,
	Dz1Asn1VisibleStr* vpbd_VehicleTimeOutGeneralizedTime,
	u16_t vpbd_VehicleTravelTimeTime, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1ProbeVehicleDetection* __internal_ret = (Dz1ProbeVehicleDetection*)Dz1Calloc(sizeof(Dz1ProbeVehicleDetection), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1ProbeVehicleDetection_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->vpbd_VehicleIdNumber = vpbd_VehicleIdNumber;
		__internal_ret->vpbd_VehicleClass = vpbd_VehicleClass;
		__internal_ret->vpbd_VehicleTimeInGeneralizedTime = vpbd_VehicleTimeInGeneralizedTime;
		__internal_ret->vpbd_VehicleTimeOutGeneralizedTime = vpbd_VehicleTimeOutGeneralizedTime;
		__internal_ret->vpbd_VehicleTravelTimeTime = vpbd_VehicleTravelTimeTime;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1ProbeVehicleDetection_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1ProbeVehicleDetection* Dz1ProbeVehicleDetection_clone(Dz1ProbeVehicleDetection* src, Dz1Error* err)
{
	Dz1ProbeVehicleDetection* ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1ProbeVehicleDetection*)Dz1Calloc(sizeof(Dz1ProbeVehicleDetection), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1ProbeVehicleDetection_delAndSetNull, (void*)&ret);

		if (src->vpbd_VehicleIdNumber && (ret->vpbd_VehicleIdNumber = Dz1Asn1UTF8Str_clone(src->vpbd_VehicleIdNumber, errp)) == NULL) ERR_OUT(errp);
		else if (src->vpbd_VehicleTimeInGeneralizedTime && (ret->vpbd_VehicleTimeInGeneralizedTime = Dz1Asn1VisibleStr_clone(src->vpbd_VehicleTimeInGeneralizedTime, errp)) == NULL) ERR_OUT(errp);
		else if (src->vpbd_VehicleTimeOutGeneralizedTime && (ret->vpbd_VehicleTimeOutGeneralizedTime = Dz1Asn1VisibleStr_clone(src->vpbd_VehicleTimeOutGeneralizedTime, errp)) == NULL) ERR_OUT(errp);
		else if (src->vpbd_VehicleAverageSpeedRate && (ret->vpbd_VehicleAverageSpeedRate = (u16_t*)Dz1Calloc(sizeof(u16_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->vpbd_AviReaderIdNumber && (ret->vpbd_AviReaderIdNumber = Dz1Asn1UTF8Str_clone(src->vpbd_AviReaderIdNumber, errp)) == NULL) ERR_OUT(errp);
		else if (src->vpbd_AviReaderLocationLatitude && (ret->vpbd_AviReaderLocationLatitude = (s64_t*)Dz1Calloc(sizeof(s64_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->vpbd_AviReaderLocationLongitude && (ret->vpbd_AviReaderLocationLongitude = (u32_t*)Dz1Calloc(sizeof(u32_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->vpbd_ReferenceLocatorIdNumber && (ret->vpbd_ReferenceLocatorIdNumber = Dz1Asn1UTF8Str_clone(src->vpbd_ReferenceLocatorIdNumber, errp)) == NULL) ERR_OUT(errp);
		else if (src->vpbd_ReferenceLocatorLatitude && (ret->vpbd_ReferenceLocatorLatitude = (s64_t*)Dz1Calloc(sizeof(s64_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->vpbd_ReferenceLocatorLongitude && (ret->vpbd_ReferenceLocatorLongitude = (u32_t*)Dz1Calloc(sizeof(u32_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			ret->vpbd_VehicleClass = src->vpbd_VehicleClass;
			ret->vpbd_VehicleTravelTimeTime = src->vpbd_VehicleTravelTimeTime;
			if (src->vpbd_VehicleAverageSpeedRate != NULL && ret->vpbd_VehicleAverageSpeedRate != NULL) *ret->vpbd_VehicleAverageSpeedRate = *src->vpbd_VehicleAverageSpeedRate;
			if (src->vpbd_AviReaderLocationLatitude != NULL && ret->vpbd_AviReaderLocationLatitude != NULL) *ret->vpbd_AviReaderLocationLatitude = *src->vpbd_AviReaderLocationLatitude;
			if (src->vpbd_AviReaderLocationLongitude != NULL && ret->vpbd_AviReaderLocationLongitude != NULL) *ret->vpbd_AviReaderLocationLongitude = *src->vpbd_AviReaderLocationLongitude;
			if (src->vpbd_ReferenceLocatorLatitude != NULL && ret->vpbd_ReferenceLocatorLatitude != NULL) *ret->vpbd_ReferenceLocatorLatitude = *src->vpbd_ReferenceLocatorLatitude;
			if (src->vpbd_ReferenceLocatorLongitude != NULL && ret->vpbd_ReferenceLocatorLongitude != NULL) *ret->vpbd_ReferenceLocatorLongitude = *src->vpbd_ReferenceLocatorLongitude;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1ProbeVehicleDetection_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1ProbeVehicleDetection_del(Dz1ProbeVehicleDetection* p)
{
	if (p == NULL) return;
	if (p->vpbd_VehicleIdNumber) Dz1Asn1UTF8Str_del(p->vpbd_VehicleIdNumber);
	if (p->vpbd_VehicleTimeInGeneralizedTime) Dz1Asn1VisibleStr_del(p->vpbd_VehicleTimeInGeneralizedTime);
	if (p->vpbd_VehicleTimeOutGeneralizedTime) Dz1Asn1VisibleStr_del(p->vpbd_VehicleTimeOutGeneralizedTime);
	if (p->vpbd_VehicleAverageSpeedRate) Dz1Free(p->vpbd_VehicleAverageSpeedRate);
	if (p->vpbd_AviReaderIdNumber) Dz1Asn1UTF8Str_del(p->vpbd_AviReaderIdNumber);
	if (p->vpbd_AviReaderLocationLatitude) Dz1Free(p->vpbd_AviReaderLocationLatitude);
	if (p->vpbd_AviReaderLocationLongitude) Dz1Free(p->vpbd_AviReaderLocationLongitude);
	if (p->vpbd_ReferenceLocatorIdNumber) Dz1Asn1UTF8Str_del(p->vpbd_ReferenceLocatorIdNumber);
	if (p->vpbd_ReferenceLocatorLatitude) Dz1Free(p->vpbd_ReferenceLocatorLatitude);
	if (p->vpbd_ReferenceLocatorLongitude) Dz1Free(p->vpbd_ReferenceLocatorLongitude);
	Dz1Free(p);
}

void Dz1ProbeVehicleDetection_dump(Dz1ProbeVehicleDetection* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	if (p->vpbd_VehicleIdNumber == NULL) Dz1Thread_tprintf(tab, Dz1T("vpbd_VehicleIdNumber = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("vpbd_VehicleIdNumber = ")); Dz1Asn1UTF8Str_dump(p->vpbd_VehicleIdNumber, tab); /* using dump func */ }

	Dz1Thread_tprintf(tab, Dz1T("vpbd_VehicleClass = %s(%d)\n"), Dz1ProbeVehicleDetection_vpbd_VehicleClassStr(p->vpbd_VehicleClass), p->vpbd_VehicleClass);

	if (p->vpbd_VehicleTimeInGeneralizedTime == NULL) Dz1Thread_tprintf(tab, Dz1T("vpbd_VehicleTimeInGeneralizedTime = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("vpbd_VehicleTimeInGeneralizedTime = ")); Dz1Asn1VisibleStr_dump(p->vpbd_VehicleTimeInGeneralizedTime, tab); /* using dump func */ }

	if (p->vpbd_VehicleTimeOutGeneralizedTime == NULL) Dz1Thread_tprintf(tab, Dz1T("vpbd_VehicleTimeOutGeneralizedTime = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("vpbd_VehicleTimeOutGeneralizedTime = ")); Dz1Asn1VisibleStr_dump(p->vpbd_VehicleTimeOutGeneralizedTime, tab); /* using dump func */ }

	Dz1Thread_tprintf(tab, Dz1T("vpbd_VehicleTravelTimeTime = ")); Dz1u16_dump(&p->vpbd_VehicleTravelTimeTime, tab);

	if (p->vpbd_VehicleAverageSpeedRate == NULL) Dz1Thread_tprintf(tab, Dz1T("vpbd_VehicleAverageSpeedRate = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("vpbd_VehicleAverageSpeedRate = ")); Dz1u16_dump(p->vpbd_VehicleAverageSpeedRate, tab); }

	if (p->vpbd_AviReaderIdNumber == NULL) Dz1Thread_tprintf(tab, Dz1T("vpbd_AviReaderIdNumber = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("vpbd_AviReaderIdNumber = ")); Dz1Asn1UTF8Str_dump(p->vpbd_AviReaderIdNumber, tab); /* using dump func */ }

	if (p->vpbd_AviReaderLocationLatitude == NULL) Dz1Thread_tprintf(tab, Dz1T("vpbd_AviReaderLocationLatitude = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("vpbd_AviReaderLocationLatitude = ")); Dz1s64_dump(p->vpbd_AviReaderLocationLatitude, tab); }

	if (p->vpbd_AviReaderLocationLongitude == NULL) Dz1Thread_tprintf(tab, Dz1T("vpbd_AviReaderLocationLongitude = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("vpbd_AviReaderLocationLongitude = ")); Dz1u32_dump(p->vpbd_AviReaderLocationLongitude, tab); }

	if (p->vpbd_ReferenceLocatorIdNumber == NULL) Dz1Thread_tprintf(tab, Dz1T("vpbd_ReferenceLocatorIdNumber = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("vpbd_ReferenceLocatorIdNumber = ")); Dz1Asn1UTF8Str_dump(p->vpbd_ReferenceLocatorIdNumber, tab); /* using dump func */ }

	if (p->vpbd_ReferenceLocatorLatitude == NULL) Dz1Thread_tprintf(tab, Dz1T("vpbd_ReferenceLocatorLatitude = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("vpbd_ReferenceLocatorLatitude = ")); Dz1s64_dump(p->vpbd_ReferenceLocatorLatitude, tab); }

	if (p->vpbd_ReferenceLocatorLongitude == NULL) Dz1Thread_tprintf(tab, Dz1T("vpbd_ReferenceLocatorLongitude = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("vpbd_ReferenceLocatorLongitude = ")); Dz1u32_dump(p->vpbd_ReferenceLocatorLongitude, tab); }

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
void Dz1ProbeVehicleDetection_fdump(FILE* fp, Dz1ProbeVehicleDetection* p, int tab)
{
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;

	if (p->vpbd_VehicleIdNumber == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("vpbd_VehicleIdNumber = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("vpbd_VehicleIdNumber = ")); Dz1Asn1UTF8Str_fdump(fp, p->vpbd_VehicleIdNumber, tab); }

	Dz1Thread_ftprintf(fp, tab, Dz1T("vpbd_VehicleClass = %s(%d)\n"), Dz1ProbeVehicleDetection_vpbd_VehicleClassStr(p->vpbd_VehicleClass), p->vpbd_VehicleClass);

	if (p->vpbd_VehicleTimeInGeneralizedTime == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("vpbd_VehicleTimeInGeneralizedTime = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("vpbd_VehicleTimeInGeneralizedTime = ")); Dz1Asn1VisibleStr_fdump(fp, p->vpbd_VehicleTimeInGeneralizedTime, tab); }

	if (p->vpbd_VehicleTimeOutGeneralizedTime == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("vpbd_VehicleTimeOutGeneralizedTime = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("vpbd_VehicleTimeOutGeneralizedTime = ")); Dz1Asn1VisibleStr_fdump(fp, p->vpbd_VehicleTimeOutGeneralizedTime, tab); }

	Dz1Thread_ftprintf(fp, tab, Dz1T("vpbd_VehicleTravelTimeTime = ")); Dz1u16_fdump(fp, &p->vpbd_VehicleTravelTimeTime, tab);

	if (p->vpbd_VehicleAverageSpeedRate == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("vpbd_VehicleAverageSpeedRate = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("vpbd_VehicleAverageSpeedRate = ")); Dz1u16_fdump(fp, p->vpbd_VehicleAverageSpeedRate, tab); }

	if (p->vpbd_AviReaderIdNumber == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("vpbd_AviReaderIdNumber = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("vpbd_AviReaderIdNumber = ")); Dz1Asn1UTF8Str_fdump(fp, p->vpbd_AviReaderIdNumber, tab); }

	if (p->vpbd_AviReaderLocationLatitude == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("vpbd_AviReaderLocationLatitude = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("vpbd_AviReaderLocationLatitude = ")); Dz1s64_fdump(fp, p->vpbd_AviReaderLocationLatitude, tab); }

	if (p->vpbd_AviReaderLocationLongitude == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("vpbd_AviReaderLocationLongitude = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("vpbd_AviReaderLocationLongitude = ")); Dz1u32_fdump(fp, p->vpbd_AviReaderLocationLongitude, tab); }

	if (p->vpbd_ReferenceLocatorIdNumber == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("vpbd_ReferenceLocatorIdNumber = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("vpbd_ReferenceLocatorIdNumber = ")); Dz1Asn1UTF8Str_fdump(fp, p->vpbd_ReferenceLocatorIdNumber, tab); }

	if (p->vpbd_ReferenceLocatorLatitude == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("vpbd_ReferenceLocatorLatitude = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("vpbd_ReferenceLocatorLatitude = ")); Dz1s64_fdump(fp, p->vpbd_ReferenceLocatorLatitude, tab); }

	if (p->vpbd_ReferenceLocatorLongitude == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("vpbd_ReferenceLocatorLongitude = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("vpbd_ReferenceLocatorLongitude = ")); Dz1u32_fdump(fp, p->vpbd_ReferenceLocatorLongitude, tab); }

	Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
}
Dz1Error Dz1ProbeVehicleDetection_fromASN(Dz1ProbeVehicleDetection* dst, ProbeVehicleDetection* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((dst->vpbd_VehicleIdNumber = Dz1Asn1UTF8Str_newFromASN(&src->vpbd_VehicleIdNumber, &err)) == NULL) { Dz1Thread_printf("vpbd_VehicleIdNumber : "); ERR_OUT(&err); }
		else if ((dst->vpbd_VehicleTimeInGeneralizedTime = Dz1Asn1VisibleStr_newFromASN(&src->vpbd_VehicleTimeInGeneralizedTime, &err)) == NULL) { Dz1Thread_printf("vpbd_VehicleTimeInGeneralizedTime : "); ERR_OUT(&err); }
		else if ((dst->vpbd_VehicleTimeOutGeneralizedTime = Dz1Asn1VisibleStr_newFromASN(&src->vpbd_VehicleTimeOutGeneralizedTime, &err)) == NULL) { Dz1Thread_printf("vpbd_VehicleTimeOutGeneralizedTime : "); ERR_OUT(&err); }
		else if ((err = u16_t_fromASN(&dst->vpbd_VehicleTravelTimeTime, &src->vpbd_VehicleTravelTimeTime)).code) { Dz1Thread_printf("vpbd_VehicleTravelTimeTime : "); ERR_OUT(&err); }
		else if (src->DEF_ProbeVehicleDetection_vpbd_VehicleAverageSpeedRate && (dst->vpbd_VehicleAverageSpeedRate = u16_t_newFromASN(&src->vpbd_VehicleAverageSpeedRate, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_ProbeVehicleDetection_vpbd_AviReaderIdNumber && (dst->vpbd_AviReaderIdNumber = Dz1Asn1UTF8Str_newFromASN(&src->vpbd_AviReaderIdNumber, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_ProbeVehicleDetection_vpbd_AviReaderLocationLatitude && (dst->vpbd_AviReaderLocationLatitude = s64_t_newFromASN(&src->vpbd_AviReaderLocationLatitude, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_ProbeVehicleDetection_vpbd_AviReaderLocationLongitude && (dst->vpbd_AviReaderLocationLongitude = u32_t_newFromASN(&src->vpbd_AviReaderLocationLongitude, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorIdNumber && (dst->vpbd_ReferenceLocatorIdNumber = Dz1Asn1UTF8Str_newFromASN(&src->vpbd_ReferenceLocatorIdNumber, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorLatitude && (dst->vpbd_ReferenceLocatorLatitude = s64_t_newFromASN(&src->vpbd_ReferenceLocatorLatitude, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorLongitude && (dst->vpbd_ReferenceLocatorLongitude = u32_t_newFromASN(&src->vpbd_ReferenceLocatorLongitude, &err)) == NULL) ERR_OUT(&err);
		else
		{
			dst->vpbd_VehicleClass = (Dz1ProbeVehicleDetection_vpbd_VehicleClass)src->vpbd_VehicleClass;
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1ProbeVehicleDetection, ProbeVehicleDetection)

Dz1Error Dz1ProbeVehicleDetection_toASN(ProbeVehicleDetection* dst, Dz1ProbeVehicleDetection* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = Dz1Asn1UTF8Str_toASN(&dst->vpbd_VehicleIdNumber, src->vpbd_VehicleIdNumber, ws)).code) { Dz1Thread_printf("vpbd_VehicleIdNumber : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1VisibleStr_toASN(&dst->vpbd_VehicleTimeInGeneralizedTime, src->vpbd_VehicleTimeInGeneralizedTime, ws)).code) { Dz1Thread_printf("vpbd_VehicleTimeInGeneralizedTime : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1VisibleStr_toASN(&dst->vpbd_VehicleTimeOutGeneralizedTime, src->vpbd_VehicleTimeOutGeneralizedTime, ws)).code) { Dz1Thread_printf("vpbd_VehicleTimeOutGeneralizedTime : "); ERR_OUT(&err); }
		else if ((err = u16_t_toASN(&dst->vpbd_VehicleTravelTimeTime, &src->vpbd_VehicleTravelTimeTime, ws)).code) { Dz1Thread_printf("vpbd_VehicleTravelTimeTime : "); ERR_OUT(&err); }
		else if ((dst->DEF_ProbeVehicleDetection_vpbd_VehicleAverageSpeedRate = src->vpbd_VehicleAverageSpeedRate ? 1 : 0) == 1 && (err = u16_t_toASN(&dst->vpbd_VehicleAverageSpeedRate, src->vpbd_VehicleAverageSpeedRate, ws)).code) { Dz1Thread_printf("vpbd_VehicleAverageSpeedRate : "); ERR_OUT(&err); }
		else if ((dst->DEF_ProbeVehicleDetection_vpbd_AviReaderIdNumber = src->vpbd_AviReaderIdNumber ? 1 : 0) == 1 && (err = Dz1Asn1UTF8Str_toASN(&dst->vpbd_AviReaderIdNumber, src->vpbd_AviReaderIdNumber, ws)).code) { Dz1Thread_printf("vpbd_AviReaderIdNumber : "); ERR_OUT(&err); }
		else if ((dst->DEF_ProbeVehicleDetection_vpbd_AviReaderLocationLatitude = src->vpbd_AviReaderLocationLatitude ? 1 : 0) == 1 && (err = s64_t_toASN(&dst->vpbd_AviReaderLocationLatitude, src->vpbd_AviReaderLocationLatitude, ws)).code) { Dz1Thread_printf("vpbd_AviReaderLocationLatitude : "); ERR_OUT(&err); }
		else if ((dst->DEF_ProbeVehicleDetection_vpbd_AviReaderLocationLongitude = src->vpbd_AviReaderLocationLongitude ? 1 : 0) == 1 && (err = u32_t_toASN(&dst->vpbd_AviReaderLocationLongitude, src->vpbd_AviReaderLocationLongitude, ws)).code) { Dz1Thread_printf("vpbd_AviReaderLocationLongitude : "); ERR_OUT(&err); }
		else if ((dst->DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorIdNumber = src->vpbd_ReferenceLocatorIdNumber ? 1 : 0) == 1 && (err = Dz1Asn1UTF8Str_toASN(&dst->vpbd_ReferenceLocatorIdNumber, src->vpbd_ReferenceLocatorIdNumber, ws)).code) { Dz1Thread_printf("vpbd_ReferenceLocatorIdNumber : "); ERR_OUT(&err); }
		else if ((dst->DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorLatitude = src->vpbd_ReferenceLocatorLatitude ? 1 : 0) == 1 && (err = s64_t_toASN(&dst->vpbd_ReferenceLocatorLatitude, src->vpbd_ReferenceLocatorLatitude, ws)).code) { Dz1Thread_printf("vpbd_ReferenceLocatorLatitude : "); ERR_OUT(&err); }
		else if ((dst->DEF_ProbeVehicleDetection_vpbd_ReferenceLocatorLongitude = src->vpbd_ReferenceLocatorLongitude ? 1 : 0) == 1 && (err = u32_t_toASN(&dst->vpbd_ReferenceLocatorLongitude, src->vpbd_ReferenceLocatorLongitude, ws)).code) { Dz1Thread_printf("vpbd_ReferenceLocatorLongitude : "); ERR_OUT(&err); }
		else
		{
			dst->vpbd_VehicleClass = src->vpbd_VehicleClass;
		}
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1ProbeVehicleDetection, ProbeVehicleDetection)
// Dz1ProbeVehicleDetection
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ProbeVehicleDetectionResponse
static Dz1Error Dz1ProbeVehicleDetectionResponse_add(Dz1ProbeVehicleDetectionResponse* p, Dz1ProbeVehicleDetection* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1ProbeVehicleDetectionResponseMkArrArg
{
	Dz1ProbeVehicleDetection** arr;
	unsigned int idx;
} Dz1ProbeVehicleDetectionResponseMkArrArg;

static Dz1Error _Dz1ProbeVehicleDetectionResponse_get_array(void* ptr, Dz1ProbeVehicleDetection* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ProbeVehicleDetectionResponseMkArrArg* arg = (Dz1ProbeVehicleDetectionResponseMkArrArg*)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1ProbeVehicleDetection** Dz1ProbeVehicleDetectionResponse_get_array(Dz1ProbeVehicleDetectionResponse* p, unsigned int* ret_cnt, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err == NULL ? &_err : err;
	Dz1ProbeVehicleDetection** ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1ProbeVehicleDetection**)Dz1Calloc(sizeof(Dz1ProbeVehicleDetection*), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1ProbeVehicleDetectionResponseMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void*)ret);

		*errp = p->travel(p, _Dz1ProbeVehicleDetectionResponse_get_array, (void*)&arg);
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

static Dz1Error Dz1ProbeVehicleDetectionResponse_travelForward(Dz1ProbeVehicleDetectionResponse* p, Dz1Error(*func)(void* ptr, Dz1ProbeVehicleDetection* data), void* ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1ProbeVehicleDetectionResponse_travelBackward(Dz1ProbeVehicleDetectionResponse* p, Dz1Error(*func)(void* ptr, Dz1ProbeVehicleDetection* data), void* ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1ProbeVehicleDetectionResponse_count(Dz1ProbeVehicleDetectionResponse* p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1ProbeVehicleDetectionResponse* Dz1ProbeVehicleDetectionResponse_new(Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1ProbeVehicleDetectionResponse* ret = (Dz1ProbeVehicleDetectionResponse*)Dz1Calloc(sizeof(Dz1ProbeVehicleDetectionResponse), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ProbeVehicleDetectionResponse_delAndSetNull, (void*)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
			(Dz1DelFunc)Dz1ProbeVehicleDetection_del,
			NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = Dz1ProbeVehicleDetectionResponse_add;
			ret->get_array = Dz1ProbeVehicleDetectionResponse_get_array;
			ret->travel = Dz1ProbeVehicleDetectionResponse_travelForward;
			ret->travelForward = Dz1ProbeVehicleDetectionResponse_travelForward;
			ret->travelBackward = Dz1ProbeVehicleDetectionResponse_travelBackward;
			ret->count = Dz1ProbeVehicleDetectionResponse_count;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1ProbeVehicleDetectionResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1ProbeVehicleDetectionResponse_clone(void* ptr, Dz1ProbeVehicleDetection* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ProbeVehicleDetectionResponse* p = (Dz1ProbeVehicleDetectionResponse*)ptr;
	Dz1ProbeVehicleDetection* cloned = Dz1ProbeVehicleDetection_clone(data, &err);
	err = Dz1Fifo_push(p->storage, cloned);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1ProbeVehicleDetectionResponse* Dz1ProbeVehicleDetectionResponse_clone(Dz1ProbeVehicleDetectionResponse* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1ProbeVehicleDetectionResponse* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1ProbeVehicleDetectionResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ProbeVehicleDetectionResponse_delAndSetNull, (void*)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1ProbeVehicleDetectionResponse_clone, (void*)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1ProbeVehicleDetectionResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1ProbeVehicleDetectionResponse_del(Dz1ProbeVehicleDetectionResponse* p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1ProbeVehicleDetectionResponse_dump(void* ptr, Dz1ProbeVehicleDetection* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	int tab = *(int*)ptr;
	Dz1Thread_tprintf(tab, Dz1T("entry = "));
	Dz1ProbeVehicleDetection_dump(p, tab);
	return err;
}

void Dz1ProbeVehicleDetectionResponse_dump(Dz1ProbeVehicleDetectionResponse* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;
	p->travel(p, _Dz1ProbeVehicleDetectionResponse_dump, (void*)&tab);
	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
typedef struct Dz1ProbeVehicleDetectionResponseFDumpArg
{
	FILE* fp;
	int tab;
} Dz1ProbeVehicleDetectionResponseFDumpArg;

static Dz1Error _Dz1ProbeVehicleDetectionResponse_fdump(void* ptr, Dz1ProbeVehicleDetection* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ProbeVehicleDetectionResponseFDumpArg* arg = (Dz1ProbeVehicleDetectionResponseFDumpArg*)ptr;
	Dz1Thread_ftprintf(arg->fp, arg->tab, Dz1T("entry = "));
	Dz1ProbeVehicleDetection_fdump(arg->fp, p, arg->tab);
	return err;
}

void Dz1ProbeVehicleDetectionResponse_fdump(FILE* fp, Dz1ProbeVehicleDetectionResponse* p, int tab)
{
	Dz1ProbeVehicleDetectionResponseFDumpArg arg = { fp, tab };
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
	p->travel(p, _Dz1ProbeVehicleDetectionResponse_fdump, (void*)&arg);
	Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
}
PSEUDO_LIST_FROM_ASN(Dz1ProbeVehicleDetectionResponse, Dz1ProbeVehicleDetection, ProbeVehicleDetection)
DZ1_NEW_LIST_FROM_ASN(Dz1ProbeVehicleDetectionResponse, ASN1List)

PSEUDO_ENTRY_TO_ASN(Dz1ProbeVehicleDetectionResponse, Dz1ProbeVehicleDetection, ProbeVehicleDetection)
PSEUDO_LIST_TO_ASN(Dz1ProbeVehicleDetectionResponse)
DZ1_TO_NEW_ASN_LIST(Dz1ProbeVehicleDetectionResponse, ASN1List)

// Dz1ProbeVehicleDetectionResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1DetectorCollection
Dz1DetectorCollection* Dz1DetectorCollection_new(Dz1Asn1UTF8Str* tfdt_DetectorIdNumber,
	Dz1Asn1VisibleStr* tfdt_DetectorTimeGeneralizedTime,
	u16_t tfdt_SpeedRate,
	u8_t tfdt_OccupancyPercent, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1DetectorCollection* __internal_ret = (Dz1DetectorCollection*)Dz1Calloc(sizeof(Dz1DetectorCollection), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1DetectorCollection_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->tfdt_DetectorIdNumber = tfdt_DetectorIdNumber;
		__internal_ret->tfdt_DetectorTimeGeneralizedTime = tfdt_DetectorTimeGeneralizedTime;
		__internal_ret->tfdt_SpeedRate = tfdt_SpeedRate;
		__internal_ret->tfdt_OccupancyPercent = tfdt_OccupancyPercent;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1DetectorCollection_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1DetectorCollection* Dz1DetectorCollection_clone(Dz1DetectorCollection* src, Dz1Error* err)
{
	Dz1DetectorCollection* ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1DetectorCollection*)Dz1Calloc(sizeof(Dz1DetectorCollection), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1DetectorCollection_delAndSetNull, (void*)&ret);

		if (src->tfdt_DetectorIdNumber && (ret->tfdt_DetectorIdNumber = Dz1Asn1UTF8Str_clone(src->tfdt_DetectorIdNumber, errp)) == NULL) ERR_OUT(errp);
		else if (src->tfdt_DetectorTimeGeneralizedTime && (ret->tfdt_DetectorTimeGeneralizedTime = Dz1Asn1VisibleStr_clone(src->tfdt_DetectorTimeGeneralizedTime, errp)) == NULL) ERR_OUT(errp);
		else if (src->tfdt_VolumeRate && (ret->tfdt_VolumeRate = (u8_t*)Dz1Calloc(sizeof(u8_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->tfdt_VehicleQueueLengthQuantity && (ret->tfdt_VehicleQueueLengthQuantity = (u32_t*)Dz1Calloc(sizeof(u32_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			ret->tfdt_SpeedRate = src->tfdt_SpeedRate;
			if (src->tfdt_VolumeRate != NULL && ret->tfdt_VolumeRate != NULL) *ret->tfdt_VolumeRate = *src->tfdt_VolumeRate;
			ret->tfdt_OccupancyPercent = src->tfdt_OccupancyPercent;
			if (src->tfdt_VehicleQueueLengthQuantity != NULL && ret->tfdt_VehicleQueueLengthQuantity != NULL) *ret->tfdt_VehicleQueueLengthQuantity = *src->tfdt_VehicleQueueLengthQuantity;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1DetectorCollection_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1DetectorCollection_del(Dz1DetectorCollection* p)
{
	if (p == NULL) return;
	if (p->tfdt_DetectorIdNumber) Dz1Asn1UTF8Str_del(p->tfdt_DetectorIdNumber);
	if (p->tfdt_DetectorTimeGeneralizedTime) Dz1Asn1VisibleStr_del(p->tfdt_DetectorTimeGeneralizedTime);
	if (p->tfdt_VolumeRate) Dz1Free(p->tfdt_VolumeRate);
	if (p->tfdt_VehicleQueueLengthQuantity) Dz1Free(p->tfdt_VehicleQueueLengthQuantity);
	Dz1Free(p);
}

void Dz1DetectorCollection_dump(Dz1DetectorCollection* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	if (p->tfdt_DetectorIdNumber == NULL) Dz1Thread_tprintf(tab, Dz1T("tfdt_DetectorIdNumber = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("tfdt_DetectorIdNumber = ")); Dz1Asn1UTF8Str_dump(p->tfdt_DetectorIdNumber, tab); /* using dump func */ }

	if (p->tfdt_DetectorTimeGeneralizedTime == NULL) Dz1Thread_tprintf(tab, Dz1T("tfdt_DetectorTimeGeneralizedTime = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("tfdt_DetectorTimeGeneralizedTime = ")); Dz1Asn1VisibleStr_dump(p->tfdt_DetectorTimeGeneralizedTime, tab); /* using dump func */ }

	Dz1Thread_tprintf(tab, Dz1T("tfdt_SpeedRate = ")); Dz1u16_dump(&p->tfdt_SpeedRate, tab);

	if (p->tfdt_VolumeRate == NULL) Dz1Thread_tprintf(tab, Dz1T("tfdt_VolumeRate = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("tfdt_VolumeRate = ")); Dz1u8_dump(p->tfdt_VolumeRate, tab); }

	Dz1Thread_tprintf(tab, Dz1T("tfdt_OccupancyPercent = ")); Dz1u8_dump(&p->tfdt_OccupancyPercent, tab);

	if (p->tfdt_VehicleQueueLengthQuantity == NULL) Dz1Thread_tprintf(tab, Dz1T("tfdt_VehicleQueueLengthQuantity = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("tfdt_VehicleQueueLengthQuantity = ")); Dz1u32_dump(p->tfdt_VehicleQueueLengthQuantity, tab); }

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
void Dz1DetectorCollection_fdump(FILE* fp, Dz1DetectorCollection* p, int tab)
{
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;

	if (p->tfdt_DetectorIdNumber == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("tfdt_DetectorIdNumber = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("tfdt_DetectorIdNumber = ")); Dz1Asn1UTF8Str_fdump(fp, p->tfdt_DetectorIdNumber, tab); }

	if (p->tfdt_DetectorTimeGeneralizedTime == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("tfdt_DetectorTimeGeneralizedTime = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("tfdt_DetectorTimeGeneralizedTime = ")); Dz1Asn1VisibleStr_fdump(fp, p->tfdt_DetectorTimeGeneralizedTime, tab); }

	Dz1Thread_ftprintf(fp, tab, Dz1T("tfdt_SpeedRate = ")); Dz1u16_fdump(fp, &p->tfdt_SpeedRate, tab);

	if (p->tfdt_VolumeRate == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("tfdt_VolumeRate = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("tfdt_VolumeRate = ")); Dz1u8_fdump(fp, p->tfdt_VolumeRate, tab); }

	Dz1Thread_ftprintf(fp, tab, Dz1T("tfdt_OccupancyPercent = ")); Dz1u8_fdump(fp, &p->tfdt_OccupancyPercent, tab);

	if (p->tfdt_VehicleQueueLengthQuantity == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("tfdt_VehicleQueueLengthQuantity = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("tfdt_VehicleQueueLengthQuantity = ")); Dz1u32_fdump(fp, p->tfdt_VehicleQueueLengthQuantity, tab); }

	Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
}
Dz1Error Dz1DetectorCollection_fromASN(Dz1DetectorCollection* dst, DetectorCollection* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((dst->tfdt_DetectorIdNumber = Dz1Asn1UTF8Str_newFromASN(&src->tfdt_DetectorIdNumber, &err)) == NULL) { Dz1Thread_printf("tfdt_DetectorIdNumber : "); ERR_OUT(&err); }
		else if ((dst->tfdt_DetectorTimeGeneralizedTime = Dz1Asn1VisibleStr_newFromASN(&src->tfdt_DetectorTimeGeneralizedTime, &err)) == NULL) { Dz1Thread_printf("tfdt_DetectorTimeGeneralizedTime : "); ERR_OUT(&err); }
		else if ((err = u16_t_fromASN(&dst->tfdt_SpeedRate, &src->tfdt_SpeedRate)).code) { Dz1Thread_printf("tfdt_SpeedRate : "); ERR_OUT(&err); }
		else if (src->DEF_DetectorCollection_tfdt_VolumeRate && (dst->tfdt_VolumeRate = u8_t_newFromASN(&src->tfdt_VolumeRate, &err)) == NULL) ERR_OUT(&err);
		else if ((err = u8_t_fromASN(&dst->tfdt_OccupancyPercent, &src->tfdt_OccupancyPercent)).code) { Dz1Thread_printf("tfdt_OccupancyPercent : "); ERR_OUT(&err); }
		else if (src->DEF_DetectorCollection_tfdt_VehicleQueueLengthQuantity && (dst->tfdt_VehicleQueueLengthQuantity = u32_t_newFromASN(&src->tfdt_VehicleQueueLengthQuantity, &err)) == NULL) ERR_OUT(&err);
		else
		{
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1DetectorCollection, DetectorCollection)

Dz1Error Dz1DetectorCollection_toASN(DetectorCollection* dst, Dz1DetectorCollection* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = Dz1Asn1UTF8Str_toASN(&dst->tfdt_DetectorIdNumber, src->tfdt_DetectorIdNumber, ws)).code) { Dz1Thread_printf("tfdt_DetectorIdNumber : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1VisibleStr_toASN(&dst->tfdt_DetectorTimeGeneralizedTime, src->tfdt_DetectorTimeGeneralizedTime, ws)).code) { Dz1Thread_printf("tfdt_DetectorTimeGeneralizedTime : "); ERR_OUT(&err); }
		else if ((err = u16_t_toASN(&dst->tfdt_SpeedRate, &src->tfdt_SpeedRate, ws)).code) { Dz1Thread_printf("tfdt_SpeedRate : "); ERR_OUT(&err); }
		else if ((dst->DEF_DetectorCollection_tfdt_VolumeRate = src->tfdt_VolumeRate ? 1 : 0) == 1 && (err = u8_t_toASN(&dst->tfdt_VolumeRate, src->tfdt_VolumeRate, ws)).code) { Dz1Thread_printf("tfdt_VolumeRate : "); ERR_OUT(&err); }
		else if ((err = u8_t_toASN(&dst->tfdt_OccupancyPercent, &src->tfdt_OccupancyPercent, ws)).code) { Dz1Thread_printf("tfdt_OccupancyPercent : "); ERR_OUT(&err); }
		else if ((dst->DEF_DetectorCollection_tfdt_VehicleQueueLengthQuantity = src->tfdt_VehicleQueueLengthQuantity ? 1 : 0) == 1 && (err = u32_t_toASN(&dst->tfdt_VehicleQueueLengthQuantity, src->tfdt_VehicleQueueLengthQuantity, ws)).code) { Dz1Thread_printf("tfdt_VehicleQueueLengthQuantity : "); ERR_OUT(&err); }
		else
		{
		}
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1DetectorCollection, DetectorCollection)
// Dz1DetectorCollection
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1DetectorCollectionResponse
static Dz1Error Dz1DetectorCollectionResponse_add(Dz1DetectorCollectionResponse* p, Dz1DetectorCollection* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1DetectorCollectionResponseMkArrArg
{
	Dz1DetectorCollection** arr;
	unsigned int idx;
} Dz1DetectorCollectionResponseMkArrArg;

static Dz1Error _Dz1DetectorCollectionResponse_get_array(void* ptr, Dz1DetectorCollection* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1DetectorCollectionResponseMkArrArg* arg = (Dz1DetectorCollectionResponseMkArrArg*)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1DetectorCollection** Dz1DetectorCollectionResponse_get_array(Dz1DetectorCollectionResponse* p, unsigned int* ret_cnt, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err == NULL ? &_err : err;
	Dz1DetectorCollection** ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1DetectorCollection**)Dz1Calloc(sizeof(Dz1DetectorCollection*), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1DetectorCollectionResponseMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void*)ret);

		*errp = p->travel(p, _Dz1DetectorCollectionResponse_get_array, (void*)&arg);
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

static Dz1Error Dz1DetectorCollectionResponse_travelForward(Dz1DetectorCollectionResponse* p, Dz1Error(*func)(void* ptr, Dz1DetectorCollection* data), void* ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1DetectorCollectionResponse_travelBackward(Dz1DetectorCollectionResponse* p, Dz1Error(*func)(void* ptr, Dz1DetectorCollection* data), void* ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1DetectorCollectionResponse_count(Dz1DetectorCollectionResponse* p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1DetectorCollectionResponse* Dz1DetectorCollectionResponse_new(Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1DetectorCollectionResponse* ret = (Dz1DetectorCollectionResponse*)Dz1Calloc(sizeof(Dz1DetectorCollectionResponse), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1DetectorCollectionResponse_delAndSetNull, (void*)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
			(Dz1DelFunc)Dz1DetectorCollection_del,
			NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = Dz1DetectorCollectionResponse_add;
			ret->get_array = Dz1DetectorCollectionResponse_get_array;
			ret->travel = Dz1DetectorCollectionResponse_travelForward;
			ret->travelForward = Dz1DetectorCollectionResponse_travelForward;
			ret->travelBackward = Dz1DetectorCollectionResponse_travelBackward;
			ret->count = Dz1DetectorCollectionResponse_count;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1DetectorCollectionResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1DetectorCollectionResponse_clone(void* ptr, Dz1DetectorCollection* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1DetectorCollectionResponse* p = (Dz1DetectorCollectionResponse*)ptr;
	Dz1DetectorCollection* cloned = Dz1DetectorCollection_clone(data, &err);
	err = Dz1Fifo_push(p->storage, cloned);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1DetectorCollectionResponse* Dz1DetectorCollectionResponse_clone(Dz1DetectorCollectionResponse* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1DetectorCollectionResponse* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1DetectorCollectionResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1DetectorCollectionResponse_delAndSetNull, (void*)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1DetectorCollectionResponse_clone, (void*)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1DetectorCollectionResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1DetectorCollectionResponse_del(Dz1DetectorCollectionResponse* p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1DetectorCollectionResponse_dump(void* ptr, Dz1DetectorCollection* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	int tab = *(int*)ptr;
	Dz1Thread_tprintf(tab, Dz1T("entry = "));
	Dz1DetectorCollection_dump(p, tab);
	return err;
}

void Dz1DetectorCollectionResponse_dump(Dz1DetectorCollectionResponse* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;
	p->travel(p, _Dz1DetectorCollectionResponse_dump, (void*)&tab);
	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
typedef struct Dz1DetectorCollectionResponseFDumpArg
{
	FILE* fp;
	int tab;
} Dz1DetectorCollectionResponseFDumpArg;

static Dz1Error _Dz1DetectorCollectionResponse_fdump(void* ptr, Dz1DetectorCollection* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1DetectorCollectionResponseFDumpArg* arg = (Dz1DetectorCollectionResponseFDumpArg*)ptr;
	Dz1Thread_ftprintf(arg->fp, arg->tab, Dz1T("entry = "));
	Dz1DetectorCollection_fdump(arg->fp, p, arg->tab);
	return err;
}

void Dz1DetectorCollectionResponse_fdump(FILE* fp, Dz1DetectorCollectionResponse* p, int tab)
{
	Dz1DetectorCollectionResponseFDumpArg arg = { fp, tab };
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
	p->travel(p, _Dz1DetectorCollectionResponse_fdump, (void*)&arg);
	Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
}
PSEUDO_LIST_FROM_ASN(Dz1DetectorCollectionResponse, Dz1DetectorCollection, DetectorCollection)
DZ1_NEW_LIST_FROM_ASN(Dz1DetectorCollectionResponse, ASN1List)

PSEUDO_ENTRY_TO_ASN(Dz1DetectorCollectionResponse, Dz1DetectorCollection, DetectorCollection)
PSEUDO_LIST_TO_ASN(Dz1DetectorCollectionResponse)
DZ1_TO_NEW_ASN_LIST(Dz1DetectorCollectionResponse, ASN1List)

// Dz1DetectorCollectionResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ExtentionCommPDU
Dz1ExtentionCommPDU* Dz1ExtentionCommPDU_new(u32_t index,
	u32_t aid,
	Dz1TimeVal* deliveryStart,
	Dz1TimeVal* deliveryStop,
	Dz1Asn1OctetStr* payload, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1ExtentionCommPDU* __internal_ret = (Dz1ExtentionCommPDU*)Dz1Calloc(sizeof(Dz1ExtentionCommPDU), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1ExtentionCommPDU_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->index = index;
		__internal_ret->aid = aid;
		__internal_ret->deliveryStart = deliveryStart;
		__internal_ret->deliveryStop = deliveryStop;
		__internal_ret->payload = payload;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1ExtentionCommPDU_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1ExtentionCommPDU* Dz1ExtentionCommPDU_clone(Dz1ExtentionCommPDU* src, Dz1Error* err)
{
	Dz1ExtentionCommPDU* ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1ExtentionCommPDU*)Dz1Calloc(sizeof(Dz1ExtentionCommPDU), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1ExtentionCommPDU_delAndSetNull, (void*)&ret);

		if (src->deliveryStart && (ret->deliveryStart = Dz1TimeVal_clone(src->deliveryStart, errp)) == NULL) ERR_OUT(errp);
		else if (src->deliveryStop && (ret->deliveryStop = Dz1TimeVal_clone(src->deliveryStop, errp)) == NULL) ERR_OUT(errp);
		else if (src->signature && (ret->signature = (bool_t*)Dz1Calloc(sizeof(bool_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->payloadType && (ret->payloadType = (s64_t*)Dz1Calloc(sizeof(s64_t), 1, errp)) == NULL) { ERR_OUT(errp); }
		else if (src->payload && (ret->payload = Dz1Asn1OctetStr_clone(src->payload, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->index = src->index;
			ret->aid = src->aid;
			if (src->signature != NULL && ret->signature != NULL) *ret->signature = *src->signature;
			if (src->payloadType != NULL && ret->payloadType != NULL) *ret->payloadType = *src->payloadType;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1ExtentionCommPDU_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1ExtentionCommPDU_del(Dz1ExtentionCommPDU* p)
{
	if (p == NULL) return;
	if (p->deliveryStart) Dz1TimeVal_del(p->deliveryStart);
	if (p->deliveryStop) Dz1TimeVal_del(p->deliveryStop);
	if (p->signature) Dz1Free(p->signature);
	if (p->payloadType) Dz1Free(p->payloadType);
	if (p->payload) Dz1Asn1OctetStr_del(p->payload);
	Dz1Free(p);
}

void Dz1ExtentionCommPDU_dump(Dz1ExtentionCommPDU* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;

	Dz1Thread_tprintf(tab, Dz1T("index = ")); Dz1u32_dump(&p->index, tab);

	Dz1Thread_tprintf(tab, Dz1T("aid = ")); Dz1u32_dump(&p->aid, tab);

	if (p->deliveryStart == NULL) Dz1Thread_tprintf(tab, Dz1T("deliveryStart = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("deliveryStart = ")); Dz1TimeVal_dump(p->deliveryStart, tab); /* using dump func */ }

	if (p->deliveryStop == NULL) Dz1Thread_tprintf(tab, Dz1T("deliveryStop = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("deliveryStop = ")); Dz1TimeVal_dump(p->deliveryStop, tab); /* using dump func */ }

	if (p->signature == NULL) Dz1Thread_tprintf(tab, Dz1T("signature = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("signature = ")); Dz1Bool_dump(p->signature, tab); }

	if (p->payloadType == NULL) Dz1Thread_tprintf(tab, Dz1T("payloadType = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("payloadType = ")); Dz1s64_dump(p->payloadType, tab); }

	if (p->payload == NULL) Dz1Thread_tprintf(tab, Dz1T("payload = NULL\n"));
	else { Dz1Thread_tprintf(tab, Dz1T("payload = ")); Dz1Asn1OctetStr_dump(p->payload, tab); /* using dump func */ }

	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
void Dz1ExtentionCommPDU_fdump(FILE* fp, Dz1ExtentionCommPDU* p, int tab)
{
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;

	Dz1Thread_ftprintf(fp, tab, Dz1T("index = ")); Dz1u32_fdump(fp, &p->index, tab);

	Dz1Thread_ftprintf(fp, tab, Dz1T("aid = ")); Dz1u32_fdump(fp, &p->aid, tab);

	if (p->deliveryStart == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("deliveryStart = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("deliveryStart = %p\n"), p->deliveryStart); }

	if (p->deliveryStop == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("deliveryStop = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("deliveryStop = %p\n"), p->deliveryStop); }

	if (p->signature == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("signature = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("signature = ")); Dz1Bool_fdump(fp, p->signature, tab); }

	if (p->payloadType == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("payloadType = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("payloadType = ")); Dz1s64_fdump(fp, p->payloadType, tab); }

	if (p->payload == NULL) Dz1Thread_ftprintf(fp, tab, Dz1T("payload = NULL\n"));
	else { Dz1Thread_ftprintf(fp, tab, Dz1T("payload = ")); Dz1Asn1OctetStr_fdump(fp, p->payload, tab); }

	Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
}
Dz1Error Dz1ExtentionCommPDU_fromASN(Dz1ExtentionCommPDU* dst, ExtentionCommPDU* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = u32_t_fromASN(&dst->index, &src->index)).code) { Dz1Thread_printf("index : "); ERR_OUT(&err); }
		else if ((err = u32_t_fromASN(&dst->aid, &src->aid)).code) { Dz1Thread_printf("aid : "); ERR_OUT(&err); }
		else if ((dst->deliveryStart = Dz1TimeVal_newFromGeneralizedTime(&src->deliveryStart, &err)) == NULL) { Dz1Thread_printf("deliveryStart : "); ERR_OUT(&err); }
		else if ((dst->deliveryStop = Dz1TimeVal_newFromGeneralizedTime(&src->deliveryStop, &err)) == NULL) { Dz1Thread_printf("deliveryStop : "); ERR_OUT(&err); }
		else if (src->DEF_ExtentionCommPDU_signature && (dst->signature = bool_t_newFromASN(&src->signature, &err)) == NULL) ERR_OUT(&err);
		else if (src->DEF_ExtentionCommPDU_payloadType && (dst->payloadType = s64_t_newFromASN(&src->payloadType, &err)) == NULL) ERR_OUT(&err);
		else if ((dst->payload = Dz1Asn1OctetStr_newFromASN(&src->payload, &err)) == NULL) { Dz1Thread_printf("payload : "); ERR_OUT(&err); }
		else
		{
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1ExtentionCommPDU, ExtentionCommPDU)

Dz1Error Dz1ExtentionCommPDU_toASN(ExtentionCommPDU* dst, Dz1ExtentionCommPDU* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = u32_t_toASN(&dst->index, &src->index, ws)).code) { Dz1Thread_printf("index : "); ERR_OUT(&err); }
		else if ((err = u32_t_toASN(&dst->aid, &src->aid, ws)).code) { Dz1Thread_printf("aid : "); ERR_OUT(&err); }
		else if ((err = Dz1TimeVal_toGeneralizedTime(&dst->deliveryStart, src->deliveryStart, ws)).code) { Dz1Thread_printf("deliveryStart : "); ERR_OUT(&err); }
		else if ((err = Dz1TimeVal_toGeneralizedTime(&dst->deliveryStop, src->deliveryStop, ws)).code) { Dz1Thread_printf("deliveryStop : "); ERR_OUT(&err); }
		else if ((dst->DEF_ExtentionCommPDU_signature = src->signature ? 1 : 0) == 1 && (err = bool_t_toASN(&dst->signature, src->signature, ws)).code) { Dz1Thread_printf("signature : "); ERR_OUT(&err); }
		else if ((dst->DEF_ExtentionCommPDU_payloadType = src->payloadType ? 1 : 0) == 1 && (err = s64_t_toASN(&dst->payloadType, src->payloadType, ws)).code) { Dz1Thread_printf("payloadType : "); ERR_OUT(&err); }
		else if ((err = Dz1Asn1OctetStr_toASN(&dst->payload, src->payload, ws)).code) { Dz1Thread_printf("payload : "); ERR_OUT(&err); }
		else
		{
		}
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1ExtentionCommPDU, ExtentionCommPDU)
// Dz1ExtentionCommPDU
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ExtentionCommPDUResponse
static Dz1Error Dz1ExtentionCommPDUResponse_add(Dz1ExtentionCommPDUResponse* p, Dz1ExtentionCommPDU* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1ExtentionCommPDUResponseMkArrArg
{
	Dz1ExtentionCommPDU** arr;
	unsigned int idx;
} Dz1ExtentionCommPDUResponseMkArrArg;

static Dz1Error _Dz1ExtentionCommPDUResponse_get_array(void* ptr, Dz1ExtentionCommPDU* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ExtentionCommPDUResponseMkArrArg* arg = (Dz1ExtentionCommPDUResponseMkArrArg*)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1ExtentionCommPDU** Dz1ExtentionCommPDUResponse_get_array(Dz1ExtentionCommPDUResponse* p, unsigned int* ret_cnt, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err == NULL ? &_err : err;
	Dz1ExtentionCommPDU** ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1ExtentionCommPDU**)Dz1Calloc(sizeof(Dz1ExtentionCommPDU*), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1ExtentionCommPDUResponseMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void*)ret);

		*errp = p->travel(p, _Dz1ExtentionCommPDUResponse_get_array, (void*)&arg);
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

static Dz1Error Dz1ExtentionCommPDUResponse_travelForward(Dz1ExtentionCommPDUResponse* p, Dz1Error(*func)(void* ptr, Dz1ExtentionCommPDU* data), void* ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1ExtentionCommPDUResponse_travelBackward(Dz1ExtentionCommPDUResponse* p, Dz1Error(*func)(void* ptr, Dz1ExtentionCommPDU* data), void* ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1ExtentionCommPDUResponse_count(Dz1ExtentionCommPDUResponse* p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1ExtentionCommPDUResponse* Dz1ExtentionCommPDUResponse_new(Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1ExtentionCommPDUResponse* ret = (Dz1ExtentionCommPDUResponse*)Dz1Calloc(sizeof(Dz1ExtentionCommPDUResponse), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ExtentionCommPDUResponse_delAndSetNull, (void*)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
			(Dz1DelFunc)Dz1ExtentionCommPDU_del,
			NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = Dz1ExtentionCommPDUResponse_add;
			ret->get_array = Dz1ExtentionCommPDUResponse_get_array;
			ret->travel = Dz1ExtentionCommPDUResponse_travelForward;
			ret->travelForward = Dz1ExtentionCommPDUResponse_travelForward;
			ret->travelBackward = Dz1ExtentionCommPDUResponse_travelBackward;
			ret->count = Dz1ExtentionCommPDUResponse_count;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1ExtentionCommPDUResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1ExtentionCommPDUResponse_clone(void* ptr, Dz1ExtentionCommPDU* data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ExtentionCommPDUResponse* p = (Dz1ExtentionCommPDUResponse*)ptr;
	Dz1ExtentionCommPDU* cloned = Dz1ExtentionCommPDU_clone(data, &err);
	err = Dz1Fifo_push(p->storage, cloned);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1ExtentionCommPDUResponse* Dz1ExtentionCommPDUResponse_clone(Dz1ExtentionCommPDUResponse* src, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1ExtentionCommPDUResponse* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1ExtentionCommPDUResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ExtentionCommPDUResponse_delAndSetNull, (void*)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1ExtentionCommPDUResponse_clone, (void*)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1ExtentionCommPDUResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1ExtentionCommPDUResponse_del(Dz1ExtentionCommPDUResponse* p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1ExtentionCommPDUResponse_dump(void* ptr, Dz1ExtentionCommPDU* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	int tab = *(int*)ptr;
	Dz1Thread_tprintf(tab, Dz1T("entry = "));
	Dz1ExtentionCommPDU_dump(p, tab);
	return err;
}

void Dz1ExtentionCommPDUResponse_dump(Dz1ExtentionCommPDUResponse* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("{\n")); tab++;
	p->travel(p, _Dz1ExtentionCommPDUResponse_dump, (void*)&tab);
	Dz1Thread_tprintf(--tab, Dz1T("}\n"));
}
typedef struct Dz1ExtentionCommPDUResponseFDumpArg
{
	FILE* fp;
	int tab;
} Dz1ExtentionCommPDUResponseFDumpArg;

static Dz1Error _Dz1ExtentionCommPDUResponse_fdump(void* ptr, Dz1ExtentionCommPDU* p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ExtentionCommPDUResponseFDumpArg* arg = (Dz1ExtentionCommPDUResponseFDumpArg*)ptr;
	Dz1Thread_ftprintf(arg->fp, arg->tab, Dz1T("entry = "));
	Dz1ExtentionCommPDU_fdump(arg->fp, p, arg->tab);
	return err;
}

void Dz1ExtentionCommPDUResponse_fdump(FILE* fp, Dz1ExtentionCommPDUResponse* p, int tab)
{
	Dz1ExtentionCommPDUResponseFDumpArg arg = { fp, tab };
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("{\n")); tab++;
	p->travel(p, _Dz1ExtentionCommPDUResponse_fdump, (void*)&arg);
	Dz1Thread_ftprintf(fp, --tab, Dz1T("}\n"));
}
PSEUDO_LIST_FROM_ASN(Dz1ExtentionCommPDUResponse, Dz1ExtentionCommPDU, ExtentionCommPDU)
DZ1_NEW_LIST_FROM_ASN(Dz1ExtentionCommPDUResponse, ASN1List)

PSEUDO_ENTRY_TO_ASN(Dz1ExtentionCommPDUResponse, Dz1ExtentionCommPDU, ExtentionCommPDU)
PSEUDO_LIST_TO_ASN(Dz1ExtentionCommPDUResponse)
DZ1_TO_NEW_ASN_LIST(Dz1ExtentionCommPDUResponse, ASN1List)

// Dz1ExtentionCommPDUResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ItsIso14827TestTimeFormat
static struct Dz1ItsIso14827TestTimeFormatMapA
{
	str_t str;
	Dz1ItsIso14827TestTimeFormat v;
} Dz1ItsIso14827TestTimeFormatMapA[] =
{
	{ (char*)"full", Dz1ItsIso14827TestTimeFormat_full },
	{ (char*)"hhmmss", Dz1ItsIso14827TestTimeFormat_hhmmss },
	{ (char*)"hhmm", Dz1ItsIso14827TestTimeFormat_hhmm },
	{ NULL, Dz1ItsIso14827TestTimeFormat_max }
};

str_t Dz1ItsIso14827TestTimeFormatStrA(Dz1ItsIso14827TestTimeFormat v)
{
	struct Dz1ItsIso14827TestTimeFormatMapA* i = NULL;
	for (i = Dz1ItsIso14827TestTimeFormatMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1ItsIso14827TestTimeFormat Dz1ItsIso14827TestTimeFormatFromStrA(str_t str)
{
	struct Dz1ItsIso14827TestTimeFormatMapA* i = NULL;
	for (i = Dz1ItsIso14827TestTimeFormatMapA; i->str; i++)
		if (strcmp(i->str, str) == 0) return i->v;
	return Dz1ItsIso14827TestTimeFormat_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1ItsIso14827TestTimeFormatMapW
{
	wstr_t str;
	Dz1ItsIso14827TestTimeFormat v;
} Dz1ItsIso14827TestTimeFormatMapW[] =
{
	{ (wchar_t*)L"full", Dz1ItsIso14827TestTimeFormat_full },
	{ (wchar_t*)L"hhmmss", Dz1ItsIso14827TestTimeFormat_hhmmss },
	{ (wchar_t*)L"hhmm", Dz1ItsIso14827TestTimeFormat_hhmm },
	{ NULL, Dz1ItsIso14827TestTimeFormat_max }
};

wstr_t Dz1ItsIso14827TestTimeFormatStrW(Dz1ItsIso14827TestTimeFormat v)
{
	struct Dz1ItsIso14827TestTimeFormatMapW* i = NULL;
	for (i = Dz1ItsIso14827TestTimeFormatMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1ItsIso14827TestTimeFormat Dz1ItsIso14827TestTimeFormatFromStrW(wstr_t str)
{
	struct Dz1ItsIso14827TestTimeFormatMapW* i = NULL;
	for (i = Dz1ItsIso14827TestTimeFormatMapW; i->str; i++)
		if (wcscmp(i->str, str) == 0) return i->v;
	return Dz1ItsIso14827TestTimeFormat_max;
}
#endif // UNIX_SYSTEM

Dz1ItsIso14827TestTimeFormat* Dz1ItsIso14827TestTimeFormat_new(Dz1ItsIso14827TestTimeFormat* src, Dz1Error* err) {
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1ItsIso14827TestTimeFormat* __internal_ret = (Dz1ItsIso14827TestTimeFormat*)Dz1Calloc(sizeof(Dz1ItsIso14827TestTimeFormat), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
	}
	return __internal_ret;
}

void Dz1ItsIso14827TestTimeFormat_dump(Dz1ItsIso14827TestTimeFormat* v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1ItsIso14827TestTimeFormatStr(*v));
}
void Dz1ItsIso14827TestTimeFormat_fdump(FILE* fp, Dz1ItsIso14827TestTimeFormat* v, int tab)
{
	if (v == NULL) Dz1Thread_fprintf(fp, Dz1T("NULL\n"));
	else Dz1Thread_fprintf(fp, Dz1T("%s\n"), Dz1ItsIso14827TestTimeFormatStr(*v));
}
Dz1Error Dz1ItsIso14827TestTimeFormat_fromASN(Dz1ItsIso14827TestTimeFormat* dst, ItsIso14827TestTimeFormat* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (Dz1ItsIso14827TestTimeFormat)(*src);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1ItsIso14827TestTimeFormat, ItsIso14827TestTimeFormat)

Dz1Error Dz1ItsIso14827TestTimeFormat_toASN(ItsIso14827TestTimeFormat* dst, Dz1ItsIso14827TestTimeFormat* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		(*dst) = (ItsIso14827TestTimeFormat)(*src);
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1ItsIso14827TestTimeFormat, ItsIso14827TestTimeFormat)
// Dz1ItsIso14827TestTimeFormat
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ItsIso14827TestTimeRequest
Dz1ItsIso14827TestTimeRequest* Dz1ItsIso14827TestTimeRequest_new(Dz1ItsIso14827TestTimeFormat fmt, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1ItsIso14827TestTimeRequest* __internal_ret = (Dz1ItsIso14827TestTimeRequest*)Dz1Calloc(sizeof(Dz1ItsIso14827TestTimeRequest), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1ItsIso14827TestTimeRequest_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->fmt = fmt;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1ItsIso14827TestTimeRequest_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1ItsIso14827TestTimeRequest* Dz1ItsIso14827TestTimeRequest_clone(Dz1ItsIso14827TestTimeRequest* src, Dz1Error* err)
{
	Dz1ItsIso14827TestTimeRequest* ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1ItsIso14827TestTimeRequest*)Dz1Calloc(sizeof(Dz1ItsIso14827TestTimeRequest), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1ItsIso14827TestTimeRequest_delAndSetNull, (void*)&ret);

		ret->fmt = src->fmt;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1ItsIso14827TestTimeRequest_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1ItsIso14827TestTimeRequest_del(Dz1ItsIso14827TestTimeRequest* p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

void Dz1ItsIso14827TestTimeRequest_dump(Dz1ItsIso14827TestTimeRequest* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	Dz1Thread_printf(Dz1T("fmt = %s(%d)\n"), Dz1ItsIso14827TestTimeFormatStr(p->fmt), p->fmt);
}
void Dz1ItsIso14827TestTimeRequest_fdump(FILE* fp, Dz1ItsIso14827TestTimeRequest* p, int tab)
{
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	Dz1Thread_fprintf(fp, Dz1T("fmt = %s(%d)\n"), Dz1ItsIso14827TestTimeFormatStr(p->fmt), p->fmt);
}
Dz1Error Dz1ItsIso14827TestTimeRequest_fromASN(Dz1ItsIso14827TestTimeRequest* dst, ItsIso14827TestTimeRequest* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		dst->fmt = (Dz1ItsIso14827TestTimeFormat)src->fmt;
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1ItsIso14827TestTimeRequest, ItsIso14827TestTimeRequest)

Dz1Error Dz1ItsIso14827TestTimeRequest_toASN(ItsIso14827TestTimeRequest* dst, Dz1ItsIso14827TestTimeRequest* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		dst->fmt = src->fmt;
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1ItsIso14827TestTimeRequest, ItsIso14827TestTimeRequest)
// Dz1ItsIso14827TestTimeRequest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1ItsIso14827TestTimeResponse
Dz1ItsIso14827TestTimeResponse* Dz1ItsIso14827TestTimeResponse_new(Dz1Asn1UTF8Str* str, Dz1Error* err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	Dz1ItsIso14827TestTimeResponse* __internal_ret = (Dz1ItsIso14827TestTimeResponse*)Dz1Calloc(sizeof(Dz1ItsIso14827TestTimeResponse), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1ItsIso14827TestTimeResponse_delAndSetNull, (void*)&__internal_ret);

		__internal_ret->str = str;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1ItsIso14827TestTimeResponse_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1ItsIso14827TestTimeResponse* Dz1ItsIso14827TestTimeResponse_clone(Dz1ItsIso14827TestTimeResponse* src, Dz1Error* err)
{
	Dz1ItsIso14827TestTimeResponse* ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, * errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = (Dz1ItsIso14827TestTimeResponse*)Dz1Calloc(sizeof(Dz1ItsIso14827TestTimeResponse), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1ItsIso14827TestTimeResponse_delAndSetNull, (void*)&ret);

		if (src->str && (ret->str = Dz1Asn1UTF8Str_clone(src->str, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1ItsIso14827TestTimeResponse_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1ItsIso14827TestTimeResponse_del(Dz1ItsIso14827TestTimeResponse* p)
{
	if (p == NULL) return;
	if (p->str) Dz1Asn1UTF8Str_del(p->str);
	Dz1Free(p);
}

void Dz1ItsIso14827TestTimeResponse_dump(Dz1ItsIso14827TestTimeResponse* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	if (p->str == NULL) Dz1Thread_printf(Dz1T("str = NULL\n"));
	else { Dz1Thread_printf(Dz1T("str = ")); Dz1Asn1UTF8Str_dump(p->str, tab); }
}
void Dz1ItsIso14827TestTimeResponse_fdump(FILE* fp, Dz1ItsIso14827TestTimeResponse* p, int tab)
{
	if (!p) { Dz1Thread_fprintf(fp, Dz1T("NULL\n")); return; }
	if (p->str == NULL) Dz1Thread_fprintf(fp, Dz1T("str = NULL\n"));
	else { Dz1Thread_fprintf(fp, Dz1T("str = ")); Dz1Asn1UTF8Str_fdump(fp, p->str, tab); }
}
Dz1Error Dz1ItsIso14827TestTimeResponse_fromASN(Dz1ItsIso14827TestTimeResponse* dst, ItsIso14827TestTimeResponse* src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void*)&ws);
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((dst->str = Dz1Asn1UTF8Str_newFromASN(&src->str, &err)) == NULL) { Dz1Thread_printf("str : "); ERR_OUT(&err); }
		else
		{
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}

DZ1_NEW_FROM_ASN(Dz1ItsIso14827TestTimeResponse, ItsIso14827TestTimeResponse)

Dz1Error Dz1ItsIso14827TestTimeResponse_toASN(ItsIso14827TestTimeResponse* dst, Dz1ItsIso14827TestTimeResponse* src, ASN1WorkSpace* ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if ((err = Dz1Asn1UTF8Str_toASN(&dst->str, src->str, ws)).code) { Dz1Thread_printf("str : "); ERR_OUT(&err); }
		else
		{
		}
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1ItsIso14827TestTimeResponse, ItsIso14827TestTimeResponse)
// Dz1ItsIso14827TestTimeResponse
////////////////////////////////////////////////////////////////////////////////


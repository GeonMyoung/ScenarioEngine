#include "Iso14827TestHelperEnv.h"
#include <Iso14827TestHelperDefUtil.h>

void SubscribeSpecEntry_dump(SubscribeSpecEntry* p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	else
	{
		u32_t latency = 0;
		SubscribeSpecTypeReg* info = NULL;
		SubscribeSpecTypeRegistered* r = NULL;
		SubscribeSpecType* type = p->type;
		Dz1Str mode = NULL, dur = Dz1T("Unknown");

		switch (type->present)
		{
		case SubscribeSpecTypePresent_single:
			Dz1Thread_printf(Dz1T("%s / %u / single\n"), p->oid, p->priority);
			break;
		case SubscribeSpecTypePresent_registered:
			r = type->x.registered;
			info = r->reg_info;

			mode = r->is_periodic ? Dz1T("periodic") : Dz1T("event-driven");
			switch (info->present)
			{
			case SubscribeSpecTypeRegPresent_continuous:
				latency = info->x.continuous->updateDelay;
				dur = Dz1T("continuous");
				break;
			case SubscribeSpecTypeRegPresent_daily:
				latency = info->x.daily->updateDelay;
				dur = Dz1T("daily");
				break;
			default:
				break;
			}
			Dz1Thread_printf(Dz1T("%s / %u / %s / %s / %u s / %s\n"), p->oid, p->priority, mode, dur, latency, Iso14827SubscriptionCancelStr(r->when_cancel));
			break;
		default:
			Dz1Thread_printf(Dz1T("%s / %u / unknown\n"), p->oid, p->priority);
			break;
		}
	}
}





void ConfTestSocketAddress_dump(ConfTestSocketAddress* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	else Dz1Thread_printf(Dz1T("%s : %u\n"), p->addr, p->port);
}

typedef struct LocalAmountDumpData
{
	Dz1Str domain;
	Dz1Str user;
} LocalAmountDumpData;
static void LocalAmountDumpData_cleanup(void* ptr)
{
	LocalAmountDumpData* p = (LocalAmountDumpData*)ptr;
	if (p != NULL)
	{
		Dz1Str_delAndSetNull(&p->domain);
		Dz1Str_delAndSetNull(&p->user);
	}
}
void Iso14827TestClientAccount_dump(Iso14827TestClientAccount* p, int tab)
{
	if (!p) { Dz1Thread_printf(Dz1T("NULL\n")); return; }
	else
	{
		LocalAmountDumpData data = { NULL, NULL };
		Dz1Str domain, user;
		int auth_size = (int)(p->authinfo != NULL ? p->authinfo->size : -1);
		//int auth_size = (int)(p->authinfo != NULL ? Dz1Str_len(p->authinfo) : -1);

		pthread_cleanup_push(LocalAmountDumpData_cleanup, (void*)&data);
		if ((data.domain = Dz1Asn1UTF8Str_toStr(p->my_domain, NULL)) == NULL) domain = Dz1T("#error"); else domain = data.domain;
		if ((data.user = Dz1Asn1UTF8Str_toStr(p->userid, NULL)) == NULL) user = Dz1T("#error"); else user = data.user;
		//if ((data.domain = p->my_domain) == NULL) domain = Dz1T("#error"); else domain = data.domain;
		//if ((data.user = p->userid) == NULL) user = Dz1T("#error"); else user = data.user;

		if (auth_size < 0) Dz1Thread_printf(Dz1T("%s : %s ]\n"), domain, user);
		else Dz1Thread_printf(Dz1T("%s : %s : %d byte auth ]\n"), domain, user, auth_size);
		pthread_cleanup_pop(1); // (LocalAmountDumpData_cleanup, (void*)&data);
	}
}

void Gitsn_Iso14827Time_dump(Gitsn_Iso14827Time* p, int tab)
{
	if (p == NULL) Dz1Thread_printf("NULL\n");
	else
	{
		char temp[32] = { 0, }, * cp = temp;
		if (p->year)
		{
			sprintf(cp, "%04d", (*p->year) % 10000);
			cp += 4;
		}
		if (p->month)
		{
			if (cp != temp) *cp++ = '-';
			sprintf(cp, "%02d", (*p->month) % 100);
			cp += 2;
		}
		if (p->day)
		{
			if (cp != temp) *cp++ = '-';
			sprintf(cp, "%02d", (*p->day) % 100);
			cp += 2;
		}

		if (cp != temp) *cp++ = ' ';

		sprintf(cp, "%02u:%02u:%02u", p->h, p->m, p->s);
		cp += 8;

		if (p->frac)
		{
			Gitsn_Iso14827TimeFrac* frac = p->frac;
			switch (frac->present)
			{
			case Gitsn_Iso14827TimeFracPresent_deci:
				sprintf(cp, ".%1u", frac->x.deci % 10);
				cp += 2;
				break;
			case Gitsn_Iso14827TimeFracPresent_centi:
				sprintf(cp, ".%02u", frac->x.centi % 100);
				cp += 3;
				break;
			case Gitsn_Iso14827TimeFracPresent_milli:
				sprintf(cp, ".%03u", frac->x.milli % 1000);
				cp += 4;
				break;
			default:
				break;
			}
		}
		if (p->zone)
		{
			Gitsn_Iso14827TimeZone* zone = p->zone;
			sprintf(cp, "+%02d:%02d", zone->modH % 100, zone->modM % 100);
			cp += 6;
		}
		*cp++ = '\0';
		Dz1Thread_printf("%s\n", temp);
	}
}


//Dz1Str					 authInfo;
//u32_t					 pktNbr;
//s32_t					 priority;
//Gitsn_Iso14827HdrOpt* hdrOpt;
//Gitsn_Iso14827PDUs* pdu;


static Gitsn_Iso14827Cost* Iso14827Cost_To_Prj22(Iso14827Cost* src, Dz1Error* errp)
{
	Gitsn_Iso14827Cost* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827Cost_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Cost_delAndSetNull, (void*)&ret);
		if ((ret->currency = Dz1Str_ndup(src->currency->data, src->currency->size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->factor = src->factor;
			ret->qty = src->qty;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827Cost_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Iso14827TimeFrac* Iso14827TimeFrac_To_Prj22(Iso14827TimeFrac* src, Dz1Error* errp)
{
	Gitsn_Iso14827TimeFrac* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827TimeFrac_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827TimeFrac_delAndSetNull, (void*)&ret);
		switch (src->present)
		{
		case Iso14827TimeFracPresent_deci:
			ret->present = Gitsn_Iso14827TimeFracPresent_deci;
			ret->x.deci = src->x.deci;
			break;
		case Iso14827TimeFracPresent_centi:
			ret->present = Gitsn_Iso14827TimeFracPresent_centi;
			ret->x.centi = src->x.centi;
			break;
		case Iso14827TimeFracPresent_milli:
			ret->present = Gitsn_Iso14827TimeFracPresent_milli;
			ret->x.milli = src->x.milli;
			break;
		default:
			break;
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827TimeFrac_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Iso14827TimeZone* Iso14827TimeZone_To_Prj22(Iso14827TimeZone* src, Dz1Error* errp)
{
	Gitsn_Iso14827TimeZone* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827TimeZone_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827TimeZone_delAndSetNull, (void*)&ret);
		ret->modH = src->modH;
		ret->modM = src->modM;
		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827TimeZone_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Iso14827Time* Iso14827Time_To_Prj22(Iso14827Time* src, Dz1Error* errp)
{
	Gitsn_Iso14827Time* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827Time_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Time_delAndSetNull, (void*)&ret);

		if ((ret->frac = Iso14827TimeFrac_To_Prj22(src->frac, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->zone = Iso14827TimeZone_To_Prj22(src->zone, errp)) == NULL) ERR_OUT(errp);
		else
		{
			if (src->year)	ret->year = src->year;
			if (src->month)	ret->month = src->month;
			if (src->day)	ret->day = src->day;
			ret->h = src->h;
			ret->m = src->m;
			ret->s = src->s;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827Time_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Iso14827HdrOpt* Iso14827HdrOpt_To_Prj22(Iso14827HdrOpt* src, Dz1Error* errp)
{
	Gitsn_Iso14827HdrOpt* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827HdrOpt_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827HdrOpt_delAndSetNull, (void*)&ret);
		
		if (src->origin)
		{
			if ((ret->origin = Dz1Str_ndup(src->origin->data, src->origin->size, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		if (src->originAddr)
		{
			if ((ret->originAddr = Dz1Str_ndup(src->originAddr->data, src->originAddr->size, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		if (src->sender)
		{
			if ((ret->sender = Dz1Str_ndup(src->sender->data, src->sender->size, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		if (src->senderAddr)
		{
			if ((ret->senderAddr = Dz1Str_ndup(src->senderAddr->data, src->senderAddr->size, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		if (src->dest)
		{
			if ((ret->dest = Dz1Str_ndup(src->dest->data, src->dest->size, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		if (src->destAddr)
		{
			if ((ret->destAddr = Dz1Str_ndup(src->destAddr->data, src->destAddr->size, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		if (src->cost)
		{
			if ((ret->cost = Iso14827Cost_To_Prj22(src->cost, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		if (src->t)
		{
			if ((ret->t = Iso14827Time_To_Prj22(src->t, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827HdrOpt_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Iso14827Initiate* Iso14827Initiate_To_Prj22(Iso14827Initiate* src, Dz1Error* errp)
{
	Gitsn_Iso14827Initiate* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827Initiate_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Initiate_delAndSetNull, (void*)&ret);
		if ((ret->sender = Dz1Str_ndup(src->sender->data, src->sender->size, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->dest = Dz1Str_ndup(src->dest->data, src->dest->size, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827Initiate_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Dz1OIDList* Dz1OIDList_To_Prj22(Dz1OIDList* src, Dz1Error* errp)
{
	Gitsn_Dz1OIDList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Dz1OIDList_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Asn1OID** entries = NULL;
		int idx;
		pthread_cleanup_push(Gitsn_Dz1OIDList_delAndSetNull, (void*)&ret);
		if ((entries = src->get_array(src, &idx, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Str e = NULL;
			for (int i = 0; i < idx; i++)
			{
				char oidStr[128];
				size_t sz;
				if ((sz = Dz1Asn1OID_printable(entries[i], oidStr, 128, errp)) < 0) ERR_OUT(errp);
				else if ((e = Dz1Str_ndup(oidStr, sz, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(Dz1Str_delAndSetNull, (void*)&e);
					if ((*errp = ret->add(ret, e)).code) ERR_OUT(errp);
					else
					{
						e = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void*)&e);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_Dz1OIDList_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Iso14827Login* Iso14827Login_To_Prj22(Iso14827Login* src, Dz1Error* errp)
{
	Gitsn_Iso14827Login* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827Login_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Login_delAndSetNull, (void*)&ret);
		if ((ret->sender = Dz1Str_ndup(src->sender->data, src->sender->size, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->dest = Dz1Str_ndup(src->dest->data, src->dest->size, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->user = Dz1Str_ndup(src->user->data, src->user->size, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->pass = Dz1Str_ndup(src->pass->data, src->pass->size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			if (src->encRules != NULL)
			{
				if ((ret->encRules = Dz1OIDList_To_Prj22(src->encRules, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			ret->hbDur = src->hbDur;
			ret->timeout = src->timeout;
			ret->initiator = (Gitsn_Iso14827LoginInitiator)src->initiator;
			ret->datagramSize = src->datagramSize;
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827Login_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Iso14827RegisteredContinuous* Iso14827RegisteredContinuous_To_Prj22(Iso14827RegisteredContinuous* src, Dz1Error* errp)
{
	Gitsn_Iso14827RegisteredContinuous* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827RegisteredContinuous_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827RegisteredContinuous_delAndSetNull, (void*)&ret);
		ret->updateDelay = src->updateDelay;
		if (src->start)
		{
			if ((ret->start = Iso14827Time_To_Prj22(src->start, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		if (src->end)
		{
			if ((ret->end = Iso14827Time_To_Prj22(src->end, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827RegisteredContinuous_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Iso14827RegisteredDaily* Iso14827RegisteredDaily_To_Prj22(Iso14827RegisteredDaily* src, Dz1Error* errp)
{
	Gitsn_Iso14827RegisteredDaily* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827RegisteredDaily_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827RegisteredDaily_delAndSetNull, (void*)&ret);
		ret->updateDelay = src->updateDelay;
		ret->daysOfWeek = src->daysOfWeek;
		Dz1Error_set(errp, 0);
		if (src->startDate)
		{
			if ((ret->startDate = Iso14827Time_To_Prj22(src->startDate, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		if (src->endDate)
		{
			if ((ret->endDate = Iso14827Time_To_Prj22(src->endDate, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		if (src->startTime)
		{
			if ((ret->startTime = Iso14827Time_To_Prj22(src->startTime, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		if (src->duration)
		{
			ret->duration = src->duration;
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827RegisteredDaily_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Iso14827Registered* Iso14827Registered_To_Prj22(Iso14827Registered* src, Dz1Error* errp)
{
	Gitsn_Iso14827Registered* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827Registered_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Registered_delAndSetNull, (void*)&ret);
		switch (src->present)
		{
		case Iso14827RegisteredPresent_continuous:
			ret->present = Gitsn_Iso14827RegisteredPresent_continuous;
			if ((ret->x.continuous = Iso14827RegisteredContinuous_To_Prj22(src->x.continuous, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827RegisteredPresent_daily:
			ret->present = Gitsn_Iso14827RegisteredPresent_daily;
			if ((ret->x.daily = Iso14827RegisteredDaily_To_Prj22(src->x.daily, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827RegisteredPresent_max:
			ret->present = Gitsn_Iso14827RegisteredPresent_max;
			break;
		default: ERR_SET_OUT(errp, EFAULT);
			break;
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827Registered_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Iso14827SubscriptionDataMode* Iso14827SubscriptionDataMode_To_Prj22(Iso14827SubscriptionDataMode* src, Dz1Error* errp)
{
	Gitsn_Iso14827SubscriptionDataMode* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827SubscriptionDataMode_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827SubscriptionDataMode_delAndSetNull, (void*)&ret);
		switch (src->present)
		{
		case Iso14827SubscriptionDataModePresent_single:
			ret->present = Gitsn_Iso14827SubscriptionDataModePresent_single;
			ret->x.single = src->x.single;
			break;
		case Iso14827SubscriptionDataModePresent_eventDriven:
			ret->present = Gitsn_Iso14827SubscriptionDataModePresent_eventDriven;
			if ((ret->x.eventDriven = Iso14827Registered_To_Prj22(src->x.eventDriven, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827SubscriptionDataModePresent_periodic:
			ret->present = Gitsn_Iso14827SubscriptionDataModePresent_periodic;
			if ((ret->x.periodic = Iso14827Registered_To_Prj22(src->x.periodic, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827SubscriptionDataModePresent_max:
			ret->present = Gitsn_Iso14827SubscriptionDataModePresent_max;
			break;
		default:ERR_SET_OUT(errp, EFAULT);
			break;
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827SubscriptionDataMode_delAndSetNull, (void*)&ret);
	}
	return ret;
}


static Gitsn_Iso14827EndAppMsg* Iso14827EndAppMsg_To_Prj22(Iso14827EndAppMsg* src, Dz1Error* errp)
{
	Gitsn_Iso14827EndAppMsg* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827EndAppMsg_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827EndAppMsg_delAndSetNull, (void*)&ret);

		char oidStr[128];
		size_t sz;
		if ((sz = Dz1Asn1OID_printable(src->oid, oidStr, 128, errp)) < 0) ERR_OUT(errp);
		else if ((ret->oid = Dz1Str_ndup(oidStr, sz, errp)) == NULL) ERR_OUT(errp);
		//if ((ret->oid = Dz1Str_clone(Dz1Asn1OID_printable(), errp)) == NULL) ERR_OUT(errp);
		//if ((ret->oid = Dz1Asn1OID_clone(src->oid, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->data = Dz1Binary_new(src->data->data, src->data->size, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827EndAppMsg_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Iso14827SubscriptionData* Iso14827SubscriptionData_To_Prj22(Iso14827SubscriptionData* src, Dz1Error* errp)
{
	Gitsn_Iso14827SubscriptionData* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827SubscriptionData_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827SubscriptionData_delAndSetNull, (void*)&ret);

		if ((ret->mode = Iso14827SubscriptionDataMode_To_Prj22(src->mode, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->msg = Iso14827EndAppMsg_To_Prj22(src->msg, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->persistent = src->persistent;
			ret->status = (Gitsn_Iso14827SubscriptionDataStatus)src->status;
			ret->fmt = (Gitsn_Iso14827SubscriptionDataFormat)src->fmt;
			ret->priority = src->priority;
			ret->guarantee = src->guarantee;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827SubscriptionData_delAndSetNull, (void*)&ret);
	}
	return ret;
}



static Gitsn_Iso14827SubscriptionType* Iso14827SubscriptionType_To_Prj22(Iso14827SubscriptionType* src, Dz1Error* errp)
{
	Gitsn_Iso14827SubscriptionType* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827SubscriptionType_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827SubscriptionType_delAndSetNull, (void*)&ret);
		switch (src->present)
		{
		case Iso14827SubscriptionTypePresent_data:
			ret->present = Gitsn_Iso14827SubscriptionTypePresent_data;
			if ((ret->x.data = Iso14827SubscriptionData_To_Prj22(src->x.data, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827SubscriptionTypePresent_reason:
			ret->present = Gitsn_Iso14827SubscriptionTypePresent_reason;
			ret->x.reason = (Gitsn_Iso14827SubscriptionCancel)src->x.reason;
			Dz1Error_set(errp, 0);
			break;
		default:
			ERR_SET_OUT(errp, EFAULT);
			break;
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827SubscriptionType_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Iso14827Subscription* Iso14827Subscription_To_Prj22(Iso14827Subscription* src, Dz1Error* errp)
{
	Gitsn_Iso14827Subscription* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827Subscription_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Subscription_delAndSetNull, (void*)&ret);
		if ((ret->type = Iso14827SubscriptionType_To_Prj22(src->type, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->serial = src->serial;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827Subscription_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Iso14827PublicationType* Iso14827PublicationType_To_Prj22(Iso14827PublicationType* src, Dz1Error* errp)
{
	Gitsn_Iso14827PublicationType* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827PublicationType_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827PublicationType_delAndSetNull, (void*)&ret);
		switch (src->present)
		{
		case Iso14827PublicationTypePresent_mgmt:
			ret->present = Gitsn_Iso14827PublicationTypePresent_mgmt;
			ret->x.mgmt = (Gitsn_Iso14827PublicationMgmt)src->x.mgmt;
			Dz1Error_set(errp, 0);
			break;
		case Iso14827PublicationTypePresent_msg:
			ret->present = Gitsn_Iso14827PublicationTypePresent_msg;
			if ((ret->x.msg = Iso14827EndAppMsg_To_Prj22(src->x.msg, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default: ERR_SET_OUT(errp, EFAULT);
			break;
		}

		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827PublicationType_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Iso14827PublicationData* Iso14827PublicationData_To_Prj22(Iso14827PublicationData* src, Dz1Error* errp)
{
	Gitsn_Iso14827PublicationData* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827PublicationData_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827PublicationData_delAndSetNull, (void*)&ret);
		if ((ret->type = Iso14827PublicationType_To_Prj22(src->type, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->subscriptionSerial = src->subscriptionSerial;
			ret->serial = src->serial;
			ret->isLated = src->isLated;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827PublicationData_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Iso14827PublicationDataList* Iso14827PublicationDataList_To_Prj22(Iso14827PublicationDataList* src, Dz1Error* errp)
{
	Gitsn_Iso14827PublicationDataList* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827PublicationDataList_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Iso14827PublicationData* src_entry = NULL;
		pthread_cleanup_push(Gitsn_Iso14827PublicationDataList_delAndSetNull, (void*)&ret);
		while ((src_entry = src->getHead(src)) != NULL && errp->code == 0)
		{
			src->extract(src, src_entry);
			Gitsn_Iso14827PublicationData* entry = NULL;
			if ((entry = Iso14827PublicationData_To_Prj22(src_entry, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Gitsn_Iso14827PublicationData_delAndSetNull, (void*)&entry);
				if ((*errp = ret->add(ret, entry)).code) ERR_OUT(errp);
				else
				{
					entry = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); //(Gitsn_Iso14827PublicationData_delAndSetNull, (void*)&entry);
			}
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827PublicationDataList_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Iso14827PublishFormat* Iso14827PublishFormat_To_Prj22(Iso14827PublishFormat* src, Dz1Error* errp)
{
	Gitsn_Iso14827PublishFormat* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827PublishFormat_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827PublishFormat_delAndSetNull, (void*)&ret);
		switch (src->present)
		{
		case Iso14827PublishFormatPresent_dataList:

			ret->present = Gitsn_Iso14827PublishFormatPresent_dataList;
			if ((ret->x.dataList = Iso14827PublicationDataList_To_Prj22(src->x.dataList, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827PublishFormatPresent_filename:
			ret->present = Gitsn_Iso14827PublishFormatPresent_filename;
			if ((ret->x.filename = Dz1Str_ndup(src->x.filename->data, src->x.filename->size, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default: ERR_SET_OUT(errp, EFAULT);
			break;
		}

		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827PublishFormat_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Iso14827Publication* Iso14827Publication_To_Prj22(Iso14827Publication* src, Dz1Error* errp)
{
	Gitsn_Iso14827Publication* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827Publication_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Publication_delAndSetNull, (void*)&ret);
		if ((ret->fmt = Iso14827PublishFormat_To_Prj22(src->fmt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->guaranteed = src->guaranteed;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827Publication_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Iso14827TransferDone* Iso14827TransferDone_To_Prj22(Iso14827TransferDone* src, Dz1Error* errp)
{
	Gitsn_Iso14827TransferDone* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827TransferDone_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827TransferDone_delAndSetNull, (void*)&ret);
		if ((ret->filename = Dz1Str_ndup(src->filename->data, src->filename->size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->isSuccess = src->isSuccess;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827TransferDone_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Iso14827AcceptType* Iso14827AcceptType_To_Prj22(Iso14827AcceptType* src, Dz1Error* errp)
{
	Gitsn_Iso14827AcceptType* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827AcceptType_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827AcceptType_delAndSetNull, (void*)&ret);
		switch (src->present)
		{
		case Iso14827AcceptTypePresent_login:
			ret->present = Gitsn_Iso14827AcceptTypePresent_login;
			char oidStr[128];
			size_t sz;
			if ((sz = Dz1Asn1OID_printable(src->x.login, oidStr, 128, errp)) < 0) ERR_OUT(errp);
			else if ((ret->x.login = Dz1Str_ndup(oidStr, sz, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827AcceptTypePresent_singleSubscription:
			ret->present = Gitsn_Iso14827AcceptTypePresent_singleSubscription;
			ret->x.singleSubscription = NULL;
			Dz1Error_set(errp, 0);
			break;
		case Iso14827AcceptTypePresent_registeredSubscription:
			ret->present = Gitsn_Iso14827AcceptTypePresent_registeredSubscription;
			ret->x.registeredSubscription = src->x.registeredSubscription;
			Dz1Error_set(errp, 0);
			break;
		case Iso14827AcceptTypePresent_publication:
			ret->present = Gitsn_Iso14827AcceptTypePresent_publication;
			ret->x.publication = NULL;
			Dz1Error_set(errp, 0);
			break;
		default: ERR_SET_OUT(errp, EFAULT);
			break;
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827AcceptType_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Iso14827Accept* Iso14827Accept_To_Prj22(Iso14827Accept* src, Dz1Error* errp)
{
	Gitsn_Iso14827Accept* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827Accept_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Accept_delAndSetNull, (void*)&ret);
		if ((ret->acceptType = Iso14827AcceptType_To_Prj22(src->acceptType, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->pktNbr = src->pktNbr;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827Accept_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Iso14827RejectPubData* Iso14827RejectPubData_To_Prj22(Iso14827RejectPubData* src, Dz1Error* errp)
{
	Gitsn_Iso14827RejectPubData* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827RejectPubData_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827RejectPubData_delAndSetNull, (void*)&ret);

		ret->subSerial = src->subSerial;
			ret->pubSerial = src->pubSerial;
			ret->reason = (Gitsn_Iso14827RejectPubDataReason)src->reason;
		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827RejectPubData_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Iso14827RejectType* Iso14827RejectType_To_Prj22(Iso14827RejectType* src, Dz1Error* errp)
{
	Gitsn_Iso14827RejectType* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827RejectType_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827RejectType_delAndSetNull, (void*)&ret);
		switch (src->present)
		{
		case Iso14827RejectTypePresent_login:
			ret->present = Gitsn_Iso14827RejectTypePresent_login;
			ret->x.login = (Gitsn_Iso14827RejectLogin)src->x.login;
			Dz1Error_set(errp, 0);
			break;
		case Iso14827RejectTypePresent_subscription:
			ret->present = Gitsn_Iso14827RejectTypePresent_subscription;
			ret->x.subscription = (Gitsn_Iso14827RejectSubscription)src->x.subscription;
			Dz1Error_set(errp, 0);
			break;
		case Iso14827RejectTypePresent_publication:
			ret->present = Gitsn_Iso14827RejectTypePresent_publication;
			ret->x.publication = (Gitsn_Iso14827RejectPublication)src->x.publication;
			Dz1Error_set(errp, 0);
			break;
		case Iso14827RejectTypePresent_pubData:
			ret->present = Gitsn_Iso14827RejectTypePresent_pubData;
			if ((ret->x.pubData = Iso14827RejectPubData_To_Prj22(src->x.pubData, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default:
			ERR_SET_OUT(errp, EFAULT);
				break;
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827RejectType_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Iso14827Reject* Iso14827Reject_To_Prj22(Iso14827Reject* src, Dz1Error* errp)
{
	Gitsn_Iso14827Reject* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827Reject_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827Reject_delAndSetNull, (void*)&ret);
		if ((ret->type = Iso14827RejectType_To_Prj22(src->type, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->pktNbr = src->pktNbr;
			Dz1Error_set(errp, 0);
			if (src->altReq)
			{
				if ((ret->altReq = Iso14827SubscriptionType_To_Prj22(src->altReq, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			} 
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827Reject_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Gitsn_Iso14827PDUs* Iso14827PDUs_To_Prj22(Iso14827PDUs* src, Dz1Error* errp)
{
	Gitsn_Iso14827PDUs* ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = Gitsn_Iso14827PDUs_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Gitsn_Iso14827PDUs_delAndSetNull, (void*)&ret);
		switch (src->present)
		{
		case Iso14827PDUsPresent_initiate:
			ret->present = Gitsn_Iso14827PDUsPresent_initiate;
			if ((ret->x.initiate = Iso14827Initiate_To_Prj22(src->x.initiate, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827PDUsPresent_login:
			ret->present = Gitsn_Iso14827PDUsPresent_login;
			if ((ret->x.login = Iso14827Login_To_Prj22(src->x.login, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827PDUsPresent_fred:
			ret->present = Gitsn_Iso14827PDUsPresent_fred;
			ret->x.fred = src->x.fred;
			Dz1Error_set(errp, 0);
			break;
		case Iso14827PDUsPresent_term:
			ret->present = Gitsn_Iso14827PDUsPresent_term;
			ret->x.term = (Gitsn_Iso14827Terminate)src->x.term;
			Dz1Error_set(errp, 0);
			break;
		case Iso14827PDUsPresent_logout:
			ret->present = Gitsn_Iso14827PDUsPresent_logout;
			ret->x.logout = (Gitsn_Iso14827Logout)src->x.logout;
			Dz1Error_set(errp, 0);
			break;
		case Iso14827PDUsPresent_subscription:
			ret->present = Gitsn_Iso14827PDUsPresent_subscription;
			if ((ret->x.subscription = Iso14827Subscription_To_Prj22(src->x.subscription, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827PDUsPresent_publication:
			ret->present = Gitsn_Iso14827PDUsPresent_publication;
			if ((ret->x.publication = Iso14827Publication_To_Prj22(src->x.publication, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827PDUsPresent_transferDone:
			ret->present = Gitsn_Iso14827PDUsPresent_transferDone;
			if ((ret->x.transferDone = Iso14827TransferDone_To_Prj22(src->x.transferDone, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827PDUsPresent_ack:
			ret->present = Gitsn_Iso14827PDUsPresent_ack;
			if ((ret->x.ack = Iso14827Accept_To_Prj22(src->x.ack, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827PDUsPresent_nak:
			ret->present = Gitsn_Iso14827PDUsPresent_nak;
			if ((ret->x.nak = Iso14827Reject_To_Prj22(src->x.nak, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Iso14827PDUsPresent_max:
			ret->present = Gitsn_Iso14827PDUsPresent_max;
			break;
		default: ERR_SET_OUT(errp, EFAULT);
			break;
		}
		pthread_cleanup_pop(errp->code); // (Gitsn_Iso14827PDUs_delAndSetNull, (void*)&ret);
	}
	return ret;
}

bool_t Iso14827C2CAuthMsg_To_Gitsn(Gitsn_Iso14827C2CAuthMsg* dst, Iso14827C2CAuthMsg* src, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || src == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		if (0) {}
		else if ((dst->hdrOpt = Iso14827HdrOpt_To_Prj22(src->hdrOpt, errp)) == NULL) ERR_OUT(errp);
		else if ((dst->pdu = Iso14827PDUs_To_Prj22(src->pdu, errp)) == NULL) ERR_OUT(errp);
		else
		{
			if (src->authInfo != NULL && src->authInfo->size > 0)
			{
				if ((dst->authInfo = Dz1Str_ndup(src->authInfo->data, src->authInfo->size, errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			dst->pktNbr = src->pktNbr;
			dst->priority = src->priority;
			Dz1Error_set(errp, 0);
		}
	}
	return ERR_IS_SUCCESS(errp);
}

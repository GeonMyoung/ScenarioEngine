#include <dz1_gasn_support.h>
#include "TechnicalRegulation1EamDz1.h"

#include "TechnicalRegulation1MsgStructAPI.h"



static void* ExtentionCommPDUList_convert(void* db_list_ptr, Dz1Error* errp)
{
	ExtentionCommPDUList* list = (ExtentionCommPDUList*)db_list_ptr;
	ExtentionCommPDUEntry* entry = NULL;

	Dz1ExtentionCommPDU* data = NULL;
	Dz1ExtentionCommPDUResponse* p = NULL;
	if ((p = Dz1ExtentionCommPDUResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ExtentionCommPDUResponse_delAndSetNull, (void*)&p);
		while ((entry = list->getHead(list)) != NULL)
		{
			list->extract(list, entry);
			pthread_cleanup_push(ExtentionCommPDUEntry_delAndSetNull, (void*)&entry);
			if ((data = Dz1ExtentionCommPDU_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1ExtentionCommPDU_delAndSetNull, (void*)&data);

				if (0) {}
				else if ((data->deliveryStart = Dz1TimeVal_newFromTime(&entry->delivery_start, errp)) == NULL) ERR_OUT(errp);	// fixed : Jake Lim
				else if ((data->deliveryStop = Dz1TimeVal_newFromTime(&entry->delivery_stop, errp)) == NULL) ERR_OUT(errp);		// fixed : Jake Lim
				else if ((data->signature = Dz1Bool_clone(&(entry->signature), errp)) == NULL) ERR_OUT(errp);
				else if ((data->payloadType = Dz1s64_clone(&(entry->payload_type), errp)) == NULL) ERR_OUT(errp);
				// else if (entry->payload != NULL && (data->payload = Dz1Asn1UTF8Str_newFromBuf(entry->payload->data, entry->payload->size, DZ1_SYSTEM_MBCS_CHARSET, errp)) == NULL) ERR_OUT(errp); // fixed : Jake Lim //확인 필요
				else if (entry->payload != NULL && (data->payload = Dz1Asn1UTF8Str_new(entry->payload->data, entry->payload->size, errp)) == NULL) ERR_OUT(errp);
				else
				{
					data->index = entry->idx;
					data->aid = entry->aid;
					if ((*errp = p->add(p, data)).code) ERR_OUT(errp);
					else
					{
						data = NULL;
						Dz1Error_set(errp, 0);
					}
				}
				pthread_cleanup_pop(1); // (Dz1ExtentionCommPDU_delAndSetNull, (void *)&data);
			}
			pthread_cleanup_pop(1); // (ExtentionCommPDUEntry_delAndSetNull, (void*)&entry);
		}
		pthread_cleanup_pop(errp->code); // (Dz1ExtentionCommPDUResponse_delAndSetNull, (void *)&p);
	}
	return p;
}
static _encoder_declare_(Dz1ExtentionCommPDUResponse, ExtentionCommPDUResponse)
static _decoder_declare_(Dz1ExtentionCommPDUResponse, ExtentionCommPDUResponse)
static _get_eam_list_declare_(TechnicalRegulation1, ExtentionCommPDUList, extention_comm_pdu, "TechnicalRegulation1_Eam", TECHNICAL_REGULATION1_EAM_PATH_110)

static ExtentionCommPDUEntry extention_comm_pdu_arr[] =
{

	{ 0, 0, 0, 0, FALSE, 0, NULL}
};

static bool_t ExtentionCommPDUList_init_sample_data(ExtentionCommPDUList* p, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		time_t t;
		ExtentionCommPDUEntry* i;
		for (i = extention_comm_pdu_arr; errp->code == 0 && i->payload != NULL; i++)
		{
			ExtentionCommPDUEntry* e;
			if ((e = ExtentionCommPDUEntry_new(i->idx, i->aid, (t = time(NULL) - i->delivery_stop), t + i->delivery_start, i->payload, errp)) == NULL) ERR_OUT(errp);

			{
				pthread_cleanup_push(ExtentionCommPDUEntry_delAndSetNull, (void*)&e);
				//if ((e->payload = Dz1Binary_clone(i->payload, errp)) == NULL) ERR_OUT(errp);
				if ((p->add(p, e)).code) ERR_OUT(errp);
				else
				{
					e = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1);// (ExtentionCommPDUEntry_delAndSetNull, (void*)&e);
			}
		}
	}
	return TRUE;
}

static bool_t ExtentionCommPDUList_init_sample_data_by_psid(ExtentionCommPDUList* p, u32_t psid, Dz1Error* err) {
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		ExtentionCommPDUEntry* i;
		for (i = extention_comm_pdu_arr; errp->code == 0 && i->payload != NULL; i++)
		{
			time_t t;
			ExtentionCommPDUEntry* e;
			if (i->payload_type == psid)		/// 우선 psid
			{
				if ((e = ExtentionCommPDUEntry_new(i->idx, i->aid, (t = time(NULL) - i->delivery_stop), t + i->delivery_start, NULL, errp)) == NULL) ERR_OUT(errp);
				{
					pthread_cleanup_push(ExtentionCommPDUEntry_delAndSetNull, (void*)&e);
					if ((e->payload = Dz1Binary_clone(i->payload, errp)) == NULL) ERR_OUT(errp);
					else if ((*errp = p->add(p, e)).code) ERR_OUT(errp);
					else
					{
						e = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1);// (ExtentionCommPDUEntry_delAndSetNull, (void*)&e);
				}
				break;
			}
		}
	}

	return TRUE;
}

static bool_t ExtentionCommPDUList_init_sample_data_by_psid_and_payload_type(ExtentionCommPDUList* p, u32_t psid, u32_t payloadType, Dz1Error* err) { return TRUE; }



Iso14827TestMsgStructAPI ITSK00100_3MsgSet[] = {
	Iso14827TestMsgUtilAPIEntry(Dz1T("1.0.14827.1.1.0"), ExtentionCommPDUList, Dz1ExtentionCommPDUResponse),
	{ NULL, NULL }
};

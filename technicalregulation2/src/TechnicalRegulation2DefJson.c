#include "TechnicalRegulation2DefJson.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1Binary
// extern type
// Dz1Binary
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CommTxPDUEntry
static bool_t CommTxPDUEntry_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CommTxPDUEntry *p = (CommTxPDUEntry *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->idx =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->psid =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->priority =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: p->channel =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 4: p->txInterval =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: Dz1Str_delAndSetNull(&p->ipAddress); p->ipAddress = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 6: p->servicePort =  *(u16_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 7: Dz1Str_delAndSetNull(&p->provideServiceContext); p->provideServiceContext = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 8: p->deliveryStart =  *(time_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 9: p->deliveryStop =  *(time_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 10: p->signature =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 11: p->payloadType =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 12: Dz1Binary_delAndSetNull(&p->payload); p->payload = (Dz1Binary *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	case 13: p->txPower =  *(s8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 14: p->txDataRate =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 15: p->channelNumberHdrExt =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 16: p->dataRateHdrExt =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 17: p->txPowerHdrExt =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *CommTxPDUEntry_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	CommTxPDUEntry *p = (CommTxPDUEntry *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->idx;
	case 1: return &p->psid;
	case 2: return &p->priority;
	case 3: return &p->channel;
	case 4: return &p->txInterval;
	case 5: return p->ipAddress;
	case 6: return &p->servicePort;
	case 7: return p->provideServiceContext;
	case 8: return &p->deliveryStart;
	case 9: return &p->deliveryStop;
	case 10: return &p->signature;
	case 11: return &p->payloadType;
	case 12: return p->payload;
	case 13: return &p->txPower;
	case 14: return &p->txDataRate;
	case 15: return &p->channelNumberHdrExt;
	case 16: return &p->dataRateHdrExt;
	case 17: return &p->txPowerHdrExt;
	default: return NULL;
	}
}

static Dz1JsonSpecChild CommTxPDUEntry_membs[] =
{
	{ Dz1Text("idx"), Dz1Text("u32_t"), 0 },
	{ Dz1Text("psid"), Dz1Text("u32_t"), 1 },
	{ Dz1Text("priority"), Dz1Text("u8_t"), 2 },
	{ Dz1Text("channel"), Dz1Text("u8_t"), 3 },
	{ Dz1Text("txInterval"), Dz1Text("u16_t"), 4 },
	{ Dz1Text("ipAddress"), Dz1Text("Dz1Str"), 5 },
	{ Dz1Text("servicePort"), Dz1Text("u16_t"), 6 },
	{ Dz1Text("provideServiceContext"), Dz1Text("Dz1Str"), 7 },
	{ Dz1Text("deliveryStart"), Dz1Text("time_t"), 8 },
	{ Dz1Text("deliveryStop"), Dz1Text("time_t"), 9 },
	{ Dz1Text("signature"), Dz1Text("bool_t"), 10 },
	{ Dz1Text("payloadType"), Dz1Text("s64_t"), 11 },
	{ Dz1Text("payload"), Dz1Text("Dz1Binary"), 12 },
	{ Dz1Text("txPower"), Dz1Text("s8_t"), 13 },
	{ Dz1Text("txDataRate"), Dz1Text("u8_t"), 14 },
	{ Dz1Text("channelNumberHdrExt"), Dz1Text("bool_t"), 15 },
	{ Dz1Text("dataRateHdrExt"), Dz1Text("bool_t"), 16 },
	{ Dz1Text("txPowerHdrExt"), Dz1Text("bool_t"), 17 },
	{ NULL, NULL, -1 }
};
// CommTxPDUEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CommTxPDUList
static bool_t CommTxPDUList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CommTxPDUList *dst = (CommTxPDUList *)dst_ptr;
	CommTxPDUEntry *node = NULL;
	if (dst == NULL || var == NULL || (node = (CommTxPDUEntry *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t CommTxPDUList_cnt(void *ptr)
{
	u32_t ret = 0;
	CommTxPDUList *list = (CommTxPDUList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error CommTxPDUList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CommTxPDUList *list = (CommTxPDUList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// CommTxPDUList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CommRxPDUEntry
static bool_t CommRxPDUEntry_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CommRxPDUEntry *p = (CommRxPDUEntry *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case 0: p->psid =  *(u32_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 1: p->channel =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 2: p->rcpi =  *(u8_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 3: Dz1Str_delAndSetNull(&p->peerAddress); p->peerAddress = (Dz1Str)info->data; info->data = NULL; break; // type_scalar = 0, ptr_instance = 0
	case 4: p->sign =  *(bool_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 5: p->payloadType =  *(s64_t *)info->data; break; // type_scalar = 1, ptr_instance = 0
	case 6: Dz1Binary_delAndSetNull(&p->payload); p->payload = (Dz1Binary *)info->data; info->data = NULL; break; // type_scalar = 1, ptr_instance = 1
	default: ERR_SET_OUT(errp, ENOENT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void *CommRxPDUEntry_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	CommRxPDUEntry *p = (CommRxPDUEntry *)ptr;
	Dz1JsonSpecChild *id = *(Dz1JsonSpecChild **)info;
	switch(id->index)
	{
	case 0: return &p->psid;
	case 1: return &p->channel;
	case 2: return &p->rcpi;
	case 3: return p->peerAddress;
	case 4: return &p->sign;
	case 5: return &p->payloadType;
	case 6: return p->payload;
	default: return NULL;
	}
}

static Dz1JsonSpecChild CommRxPDUEntry_membs[] =
{
	{ Dz1Text("psid"), Dz1Text("u32_t"), 0 },
	{ Dz1Text("channel"), Dz1Text("u8_t"), 1 },
	{ Dz1Text("rcpi"), Dz1Text("u8_t"), 2 },
	{ Dz1Text("peerAddress"), Dz1Text("Dz1Str"), 3 },
	{ Dz1Text("sign"), Dz1Text("bool_t"), 4 },
	{ Dz1Text("payloadType"), Dz1Text("s64_t"), 5 },
	{ Dz1Text("payload"), Dz1Text("Dz1Binary"), 6 },
	{ NULL, NULL, -1 }
};
// CommRxPDUEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CommRxPDUList
static bool_t CommRxPDUList_append(void *dst_ptr, Dz1JsonVarBind *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	CommRxPDUList *dst = (CommRxPDUList *)dst_ptr;
	CommRxPDUEntry *node = NULL;
	if (dst == NULL || var == NULL || (node = (CommRxPDUEntry *)var->data) == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
	else
	{
		var->data = NULL;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static u32_t CommRxPDUList_cnt(void *ptr)
{
	u32_t ret = 0;
	CommRxPDUList *list = (CommRxPDUList *)ptr;
	if (list != NULL) ret = list->count(list);
	return ret;
}

static Dz1Error CommRxPDUList_tlv(void *obj, Dz1JsonArrayEntryF f, void *arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CommRxPDUList *list = (CommRxPDUList *)obj;
	if (list == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = list->travel(list, f, arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
// CommRxPDUList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation2_Eam
static bool_t TechnicalRegulation2_Eam_setChild(void *ptr, Dz1JsonVarBind *info, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TechnicalRegulation2_Eam *p = (TechnicalRegulation2_Eam *)ptr;

	Dz1JsonSpecChild *id = info->id;
	switch(id->index)
	{
	case TechnicalRegulation2_EamPresent_comm_tx_pdu: CommTxPDUList_delAndSetNull(&p->x.comm_tx_pdu); p->x.comm_tx_pdu =(CommTxPDUList *)info->data; info->data = NULL; break;
	case TechnicalRegulation2_EamPresent_comm_rx_pdu: CommRxPDUList_delAndSetNull(&p->x.comm_rx_pdu); p->x.comm_rx_pdu =(CommRxPDUList *)info->data; info->data = NULL; break;
	default: ERR_SET_OUT_RET(errp, ENOENT, FALSE);
	}
	p->present = (TechnicalRegulation2_EamPresent)id->index;
	return errp->code == 0 ? TRUE : FALSE;
}

static void *TechnicalRegulation2_Eam_getChild(void *ptr, Dz1JsonSpecChild **info, Dz1JsonSpecChilds *lists)
{
	TechnicalRegulation2_Eam *p = (TechnicalRegulation2_Eam *)ptr;
	Dz1JsonSpecChild *id = (*info) = Dz1JsonSpecChilds_findByIdx(lists, p->present);
	if (id != NULL)
	{
		switch(p->present)
		{
		case TechnicalRegulation2_EamPresent_comm_tx_pdu: return p->x.comm_tx_pdu;
		case TechnicalRegulation2_EamPresent_comm_rx_pdu: return p->x.comm_rx_pdu;
		default: return NULL;
		}
	}
	else return NULL;
}

static Dz1JsonSpecChild TechnicalRegulation2_Eam_membs[] =
{
	{ Dz1Text("comm_tx_pdu"), Dz1Text("CommTxPDUList"), TechnicalRegulation2_EamPresent_comm_tx_pdu },
	{ Dz1Text("comm_rx_pdu"), Dz1Text("CommRxPDUList"), TechnicalRegulation2_EamPresent_comm_rx_pdu },
	{ NULL, NULL, -1 }
};
// TechnicalRegulation2_Eam
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1JsonSpec Initializer
bool_t TechnicalRegulation2Def_initJsonSpec(Dz1JsonSpec *dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (0) { }
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("CommTxPDUEntry"), CommTxPDUEntry_gen, CommTxPDUEntry_del, CommTxPDUEntry_setChild, CommTxPDUEntry_getChild, CommTxPDUEntry_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("CommRxPDUEntry"), CommRxPDUEntry_gen, CommRxPDUEntry_del, CommRxPDUEntry_setChild, CommRxPDUEntry_getChild, CommRxPDUEntry_membs, Dz1JsonConstructType_struct)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_construct(dst, Dz1Text("TechnicalRegulation2_Eam"), TechnicalRegulation2_Eam_gen, TechnicalRegulation2_Eam_del, TechnicalRegulation2_Eam_setChild, TechnicalRegulation2_Eam_getChild, TechnicalRegulation2_Eam_membs, Dz1JsonConstructType_union)).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("CommTxPDUList"), CommTxPDUList_gen, CommTxPDUList_del, CommTxPDUList_append, CommTxPDUList_cnt, CommTxPDUList_tlv, Dz1Text("CommTxPDUEntry") )).code) ERR_OUT(errp);
		else if ((*errp = Dz1JSonSpec_add_array(dst, Dz1Text("CommRxPDUList"), CommRxPDUList_gen, CommRxPDUList_del, CommRxPDUList_append, CommRxPDUList_cnt, CommRxPDUList_tlv, Dz1Text("CommRxPDUEntry") )).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
Dz1JsonSpec *TechnicalRegulation2Def_genJsonSpec(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonSpec *ret = Dz1JsonSpec_generate(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonSpec_delAndSetNull, (void *)&ret);

		if (TechnicalRegulation2Def_initJsonSpec(ret, errp) == FALSE) ERR_OUT(errp);
		else if (Dz1JsonSpec_check(ret, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1JsonSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Dz1JsonSpec Initializer
////////////////////////////////////////////////////////////////////////////////

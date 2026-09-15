#include <dz1_gasn_support.h>
#include <Iso14827TestMsgUtil.h>




Dz1Binary* Iso14827TestMsgStructAPI_convert(Iso14827TestMsgStructAPI* api, void* eam_list_ptr, Dz1Asn1Codec codec, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary* ret = NULL;

	void* struct_ptr = NULL;

	if (api == NULL || eam_list_ptr == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((struct_ptr = api->struct_convert_from_eam(eam_list_ptr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		api->struct_dump(struct_ptr, 4);
		pthread_cleanup_push(api->struct_delAndSetNull, (void*)&struct_ptr);
		if ((ret = Iso14827TestMsgStructAPI_encode(api, struct_ptr, codec, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1);// (api->struct_delAndSetNull, (void*)&struct_ptr);
	}
	Dz1Thread_printf("in StructAPI convert() :\n");
	Dz1Binary_dump(ret, 0);
	return ret;
}


Dz1Binary* Iso14827TestMsgStructAPI_encode(Iso14827TestMsgStructAPI* api, void* struct_ptr, Dz1Asn1Codec codec, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary* ret = NULL;
	if (api == NULL || struct_ptr == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (api->struct_encode == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = api->struct_encode(struct_ptr, codec, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	Dz1Thread_printf("in StructAPI encode() : \n");
	Dz1Binary_dump(ret, 0);
	return ret;
}

void Iso14827TestMsgStructAPI_dump(Iso14827TestMsgStructAPI* api, void* struct_ptr, int tab)
{
	if (api == NULL || struct_ptr == NULL)
	{
		if (struct_ptr == NULL) Dz1Thread_printf(Dz1T("(!) NULL\n"));
		else Dz1Thread_printf(Dz1T("(!)%p\n"), struct_ptr);
	}
	else if (struct_ptr == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else api->struct_dump(struct_ptr, tab);
}



Iso14827TestMsgStructAPI* Iso14827TestMsgSet_findAPI(Iso14827TestMsgStructAPI* tbl, Dz1Str oidStr, u32_t* ret_oid_idx)
{
	if (tbl != NULL && Dz1Str_isVoid(oidStr) == FALSE)
	{
		Iso14827TestMsgStructAPI* i = NULL;
		u32_t idx = 0;
		for (i = tbl, idx = 0; i->oid != NULL; i++, idx++)
		{
			if (Dz1STRCMP(i->oid, oidStr) == 0)
			{
				if (ret_oid_idx) *ret_oid_idx = idx;
				return i;
			}
		}
	}
	return NULL;
}

Iso14827TestMsgStructAPI* Iso14827TestMsgSet_findByIDX(Iso14827TestMsgStructAPI* tbl, u32_t tgt)
{
	if (tbl != NULL)
	{
		u32_t idx = 0;
		Iso14827TestMsgStructAPI* i = NULL;
		for (i = tbl, idx = 0; i->oid != NULL; i++, idx++)
			if (idx == tgt) return i;
	}
	return NULL;
}


Dz1Binary* Iso14827TestMsgSet_getPublicationData(Iso14827TestMsgStructAPI* tbl, Dz1Str oidStr, Dz1Asn1Codec codec, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	// TBD
	Dz1Binary* ret = NULL;

	void* eam_list_ptr;
	Iso14827TestMsgStructAPI* struct_api = NULL;


	if ((struct_api = Iso14827TestMsgSet_findAPI(tbl, oidStr, NULL)) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((eam_list_ptr = struct_api->eam_gen_empty(errp)) == NULL) ERR_OUT(errp);
	else if ((eam_list_ptr = struct_api->get_eam_list(eam_list_ptr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(tbl->struct_delAndSetNull, (void*)&eam_list_ptr);
		if ((ret = Iso14827TestMsgStructAPI_convert(struct_api, eam_list_ptr, codec, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		Dz1Thread_printf("in getPublicationData() : \n");
		Dz1Binary_dump(ret, 0);
		pthread_cleanup_pop(1); // (tbl->struct_delAndSetNull, (void*)&eam_list_ptr);
	}
	return ret;
}

Dz1Binary* Iso14827TestMsgSet_getPublicationSampleData(Iso14827TestMsgStructAPI* tbl, Dz1Str oidStr,Dz1Asn1Codec codec, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary* ret = NULL;

	void* eam_list_ptr;
	Iso14827TestMsgStructAPI* struct_api = NULL;
	if ((struct_api = Iso14827TestMsgSet_findAPI(tbl, oidStr, NULL)) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((eam_list_ptr = struct_api->eam_gen_empty(errp)) == NULL) ERR_OUT(errp);
	else if (struct_api->init_sample_data(eam_list_ptr, errp) == FALSE) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(struct_api->eam_delAndSetNull, (void*)&eam_list_ptr);
		if ((ret = Iso14827TestMsgStructAPI_convert(struct_api, eam_list_ptr, codec, errp)) == NULL) ERR_OUT(errp);
		else
		{

			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (struct_api->eam_delAndSetNull, (void*)&eam_list_ptr);
	}
	return ret;
}

Dz1Binary* Iso14827TestMsgSet_getPublicationSampleDataByPsid(Iso14827TestMsgStructAPI* tbl, Dz1Str oidStr, u32_t psid, Dz1Asn1Codec codec, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary* ret = NULL;

	if (psid == 9999)
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);

		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		switch (codec)
		{
		case Dz1Asn1Codec_ber:
			if (ASN1_BER_Enc_NULL(&ws, ASN1EXPL) < 0) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		case Dz1Asn1Codec_uper:
		case Dz1Asn1Codec_aper:
			break;
		default: ERR_SET_OUT(errp, ENOSYS); break;
		}

		if (errp->code == 0)
		{
			if ((ret = Dz1Binary_new(ASN1WorkSpace_getEncodePtr(&ws), ASN1WorkSpace_getEncodedSize(&ws, codec), errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void * )&ws);
	}
	else
	{
		void* eam_list_ptr;
		Iso14827TestMsgStructAPI* struct_api = NULL;
		if ((struct_api = Iso14827TestMsgSet_findAPI(tbl, oidStr, NULL)) == NULL) ERR_SET_OUT(errp, ENOSYS);
		else if ((eam_list_ptr = struct_api->eam_gen_empty(errp)) == NULL) ERR_OUT(errp);
		else if (struct_api->init_sample_data_by_psid(eam_list_ptr, psid, errp) == FALSE) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(struct_api->eam_delAndSetNull, (void*)&eam_list_ptr);
			if ((ret = Iso14827TestMsgStructAPI_convert(struct_api, eam_list_ptr, codec, errp)) == NULL) ERR_OUT(errp);
			else
			{

				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (struct_api->eam_delAndSetNull, (void*)&eam_list_ptr);
		}
	}
	return ret;
}


Dz1Binary* Iso14827TestMsgSet_getPublicationSampleDataByPsidAndPayloadType(Iso14827TestMsgStructAPI* tbl, Dz1Str oidStr, u32_t psid, u32_t payloadType, Dz1Asn1Codec codec, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary* ret = NULL;

	if (psid == 9999)
	{
		ASN1WorkSpace ws;
		ASN1_INIT_WS_INFO(&ws);

		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
		switch (codec)
		{
		case Dz1Asn1Codec_ber:
			if (ASN1_BER_Enc_NULL(&ws, ASN1EXPL) < 0) ERR_SET_OUT(errp, EFAULT);
			else Dz1Error_set(errp, 0);
		case Dz1Asn1Codec_uper:
		case Dz1Asn1Codec_aper:
			break;
		default: ERR_SET_OUT(errp, ENOSYS); break;
		}

		if (errp->code == 0)
		{
			if ((ret = Dz1Binary_new(ASN1WorkSpace_getEncodePtr(&ws), ASN1WorkSpace_getEncodedSize(&ws, codec), errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void * )&ws);
	}
	else
	{
		void* eam_list_ptr;
		Iso14827TestMsgStructAPI* struct_api = NULL;
		if ((struct_api = Iso14827TestMsgSet_findAPI(tbl, oidStr, NULL)) == NULL) ERR_SET_OUT(errp, ENOSYS);
		else if ((eam_list_ptr = struct_api->eam_gen_empty(errp)) == NULL) ERR_OUT(errp);
		else if (struct_api->init_sample_data_by_psid_and_payload_type(eam_list_ptr, psid, payloadType, errp) == FALSE) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(struct_api->eam_delAndSetNull, (void*)&eam_list_ptr);
			if ((ret = Iso14827TestMsgStructAPI_convert(struct_api, eam_list_ptr, codec, errp)) == NULL) ERR_OUT(errp);
			else
			{

				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (struct_api->eam_delAndSetNull, (void*)&eam_list_ptr);
		}
	}
	return ret;
}

Dz1Binary* Iso14827TestMsgSet_getNullData(Dz1Asn1Codec codec, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1Binary* ret = NULL;

	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);

	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);
	switch (codec)
	{
	case Dz1Asn1Codec_ber:
		if (ASN1_BER_Enc_NULL(&ws, ASN1EXPL) < 0) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);
	case Dz1Asn1Codec_uper:
	case Dz1Asn1Codec_aper:
		break;
	default: ERR_SET_OUT(errp, ENOSYS); break;
	}

	if (errp->code == 0)
	{
		if ((ret = Dz1Binary_new(ASN1WorkSpace_getEncodePtr(&ws), ASN1WorkSpace_getEncodedSize(&ws, codec), errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void * )&ws);

	return ret;
}

static u8_t sample_empty_list[] = { 0x30, 0x00 };
static Dz1Binary b_sample_empty_list = { sample_empty_list, 2 };

Dz1Binary* Iso14827TestMsgSet_getEmptyList(Dz1Asn1Codec codec, Dz1Error* err)
{

	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1Binary* ret = NULL;
	if ((ret = Dz1Binary_clone(&b_sample_empty_list, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	
	return ret;
}
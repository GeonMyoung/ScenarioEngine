#include "dz1_asn1_types.h"
#include "dz1_asn1_typedescr.h"

///////////////////////////////////////////////////////////////////////////////
// Finalize
DZ1_CPPLINK bool_t			 Dz1Asn1Any_BER_initFromWIP(Dz1Asn1Any *dst, Dz1Asn1WipOpenType *src, Dz1Error *err);
bool_t Dz1Asn1Any_finalize(void *_dst, Dz1Asn1WipValue *_src, Dz1Asn1TypeDescr *descr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1Any *dst = (Dz1Asn1Any *)_dst;
	if (dst == NULL || _src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (_src->present != Dz1Asn1WipValuePresent_any) ERR_SET_OUT(errp, EFAULT);
	else if (dst->data != NULL || dst->size != 0) ERR_SET_OUT(errp, EINVAL);
	else if (Dz1Asn1Any_BER_initFromWIP(dst, _src->x.any, errp) == FALSE) ERR_OUT(errp);
	else
	{
		if (Dz1Asn1TypeDescr_chkConformance(descr, dst, NULL) == FALSE)
		{
			char str_name[64];
			Dz1Asn1UTF8StrA_printable(descr->name, str_name, 64, NULL);
			Dz1Thread_log(DZ1_THREAD_LOG_WARN, "!!! Conformance Check Fail : %s\n", str_name);
		}
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

Dz1Asn1DataTypeFinalizeF_announce(Dz1Asn1Bool)			// bool_t Dz1Asn1Bool_finalize(void *_dst, Dz1Asn1WipValue *_src, Dz1Asn1TypeComformance *conformance, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1Bool *dst = (Dz1Asn1Bool *)_dst;
	if (dst == NULL || _src == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		*dst = _src->x.boolean;
		if (Dz1Asn1TypeDescr_chkConformance(descr, dst, NULL) == FALSE)
		{
			char str_name[64];
			Dz1Asn1UTF8StrA_printable(descr->name, str_name, 64, NULL);
			Dz1Thread_log(DZ1_THREAD_LOG_WARN, "!!! Conformance Check Fail : %s\n", str_name);
		}
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

Dz1Asn1DataTypeFinalizeF_announce(Dz1Asn1Int)	// bool_t Dz1Asn1Int_finalize(void *_dst, Dz1Asn1WipValue *_src, Dz1Asn1TypeComformance *conformance, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1Int *dst = (Dz1Asn1Int *)_dst;
	if (dst == NULL || _src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (_src->present != Dz1Asn1WipValuePresent_number) ERR_SET_OUT(errp, EFAULT);
	else
	{
		(*dst) = _src->x.number;
		if (Dz1Asn1TypeDescr_chkConformance(descr, dst, NULL) == FALSE)
		{
			char str_name[64];
			Dz1Asn1UTF8StrA_printable(descr->name, str_name, 64, NULL);
			Dz1Thread_log(DZ1_THREAD_LOG_WARN, "!!! Conformance Check Fail : %s\n", str_name);
		}
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

Dz1Asn1DataTypeFinalizeF_announce(Dz1Asn1BitStr)		// bool_t Dz1Asn1BitStr_finalize(void *_dst, Dz1Asn1WipValue *_src, Dz1Asn1TypeComformance *conformance, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1BitStr *dst = (Dz1Asn1BitStr *)_dst;
	Dz1ElasticBuf *elb = NULL;
	Dz1Binary *bin = NULL;
	u8_t first_octet = 0;
	Dz1Asn1WipBitString *src = NULL;
	if (_src == NULL || dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (_src->present != Dz1Asn1WipValuePresent_bit_str) ERR_SET_OUT(errp, EFAULT);
	else if ((src = _src->x.bit_str) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((elb = src->elb) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1ElasticBuf_pop(elb, &first_octet, 1, errp) < 0) ERR_OUT(errp);
	else if ((bin = Dz1ElasticBuf_flattenAndPurge(elb, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

		dst->bits = bin->data;
		bin->data = NULL;

		dst->allocByte = bin->size;
		bin->size = 0;

		src->trim_bits = 0;

		if (dst->bits != NULL && dst->allocByte > 0)
			Dz1Asn1BitStr_setMaxBit(dst, NULL);

		if (Dz1Asn1TypeDescr_chkConformance(descr, dst, NULL) == FALSE)
		{
			char str_name[64];
			Dz1Asn1UTF8StrA_printable(descr->name, str_name, 64, NULL);
			Dz1Thread_log(DZ1_THREAD_LOG_WARN, "!!! Conformance Check Fail : %s\n", str_name);
		}
		Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Asn1OctetStr_finalize(Dz1Asn1DataTypeFinalizeF_args)		// (void *_dst, Dz1Asn1WipValue *_src, Dz1Asn1TypeDescr *descr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *bin = NULL;
	Dz1ElasticBuf *elb = NULL;
	Dz1Asn1OctetStr *dst = (Dz1Asn1OctetStr *)_dst;
	if (dst == NULL || _src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (dst->data != NULL || dst->size != 0) ERR_SET_OUT(errp, EINVAL);
	else if (_src->present != Dz1Asn1WipValuePresent_octet_str) ERR_SET_OUT(errp, EFAULT);
	else if ((elb = _src->x.octet_str) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((bin = (Dz1Binary *)Dz1ElasticBuf_flattenAndPurge(_src->x.octet_str, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

		dst->data = bin->data;
		bin->data = NULL;

		dst->size = bin->size;
		bin->size = 0;

		if (Dz1Asn1TypeDescr_chkConformance(descr, dst, NULL) == FALSE)
		{
			char str_name[64];
			Dz1Asn1UTF8StrA_printable(descr->name, str_name, 64, NULL);
			Dz1Thread_log(DZ1_THREAD_LOG_WARN, "!!! Conformance Check Fail : %s\n", str_name);
		}
		Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

Dz1Asn1DataTypeFinalizeF_announce(Dz1Asn1Null)	// bool_t Dz1Asn1Null_finalize(void *_dst, Dz1Asn1WipValue *_src, Dz1Asn1TypeComformance *conformance, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1Null *dst = (Dz1Asn1Null *)_dst;
	if (dst == NULL || _src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (_src->present != Dz1Asn1WipValuePresent_nul) ERR_SET_OUT(errp, EFAULT);
	else
	{
		(*dst) = _src->x.nul;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Asn1OID_finalize(Dz1Asn1DataTypeFinalizeF_args)	// (void *_dst, Dz1Asn1WipValue *_src, Dz1Asn1TypeComformance *conformance, Dz1Error *err)
{	
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1OID *dst = (Dz1Asn1OID*)_dst;
	Dz1Asn1WipOid *src = NULL;
	if (dst == NULL || _src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (dst->data != NULL || dst->cnt != 0) ERR_SET_OUT(errp, EINVAL);
	else if (_src->present != Dz1Asn1WipValuePresent_oid) ERR_SET_OUT(errp, EFAULT);
	else if ((src = _src->x.oid) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1Asn1OID_initFromWIP(dst, src, errp) == FALSE) ERR_OUT(errp);
	else
	{
		if (Dz1Asn1TypeDescr_chkConformance(descr, dst, NULL) == FALSE)
		{
			char str_name[64];
			Dz1Asn1UTF8StrA_printable(descr->name, str_name, 64, NULL);
			Dz1Thread_log(DZ1_THREAD_LOG_WARN, "!!! Conformance Check Fail : %s\n", str_name);
		}
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

Dz1Asn1DataTypeFinalizeF_announce(Dz1Asn1External)					// bool_t Dz1Asn1External_finalize(void *_dst, Dz1Asn1WipValue *_src, Dz1Asn1TypeDescr *descr, Dz1Error *err)
{	// decoding path, _dst is Dz1Asn1External
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1WipCst *src_cst = NULL;
	Dz1Asn1Custom *src_sto = NULL;
	Dz1Asn1WipExtOrInst *src = NULL;

	Dz1Asn1External *dst = (Dz1Asn1External *)_dst;

	if (dst == NULL || _src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (_src->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((src_cst = _src->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((src_sto = src_cst->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((src = (Dz1Asn1WipExtOrInst *)src_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (src->present != Dz1Asn1WipExtOrInstPresent_external) ERR_SET_OUT(errp, EFAULT);
	else
	{
		memcpy(dst, src->x.external, sizeof(Dz1Asn1External));
		memset(src->x.external, 0, sizeof(Dz1Asn1External));
		if (Dz1Asn1TypeDescr_chkConformance(descr, dst, NULL) == FALSE)
		{
			char str_name[64];
			Dz1Asn1UTF8StrA_printable(descr->name, str_name, 64, NULL);
			Dz1Thread_log(DZ1_THREAD_LOG_WARN, "!!! Conformance Check Fail : %s\n", str_name);
		}
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

Dz1Asn1DataTypeFinalizeF_announce(Dz1Asn1InstanceOf) // bool_t _internal_api_Dz1Asn1InstanceOf_finalize(void *_dst, Dz1Asn1WipValue *_src, Dz1Asn1TypeDescr *descr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1WipCst *src_cst = NULL;
	Dz1Asn1Custom *src_sto = NULL;
	Dz1Asn1InstanceOf *dst = (Dz1Asn1InstanceOf *)_dst;
	Dz1Asn1WipExtOrInst *src = NULL;
	if (dst == NULL || _src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (_src->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((src_cst = _src->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((src_sto = src_cst->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((src = (Dz1Asn1WipExtOrInst *)src_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (src->present != Dz1Asn1WipExtOrInstPresent_instance_of) ERR_SET_OUT(errp, EFAULT);
	else
	{
		memcpy(dst, src->x.instance_of, sizeof(Dz1Asn1InstanceOf));
		memset(src->x.instance_of, 0, sizeof(Dz1Asn1InstanceOf));
		if (Dz1Asn1TypeDescr_chkConformance(descr, dst, NULL) == FALSE)
		{
			char str_name[64];
			Dz1Asn1UTF8StrA_printable(descr->name, str_name, 64, NULL);
			Dz1Thread_log(DZ1_THREAD_LOG_WARN, "!!! Conformance Check Fail : %s\n", str_name);
		}
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

Dz1Asn1DataTypeFinalizeF_announce(Dz1Asn1Real)			// bool_t Dz1Asn1Real_finalize(void *_dst, Dz1Asn1WipValue *_src, Dz1Asn1TypeComformance *conformance, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1WipReal *src = NULL;
	Dz1Asn1Real *dst = (Dz1Asn1Real *)_dst;
	if (dst == NULL || _src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (_src->present != Dz1Asn1WipValuePresent_realnum) ERR_SET_OUT(errp, EFAULT);
	else if ((src = _src->x.realnum) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		(*dst) = src->value;
		if (Dz1Asn1TypeDescr_chkConformance(descr, dst, NULL) == FALSE)
		{
			char str_name[64];
			Dz1Asn1UTF8StrA_printable(descr->name, str_name, 64, NULL);
			Dz1Thread_log(DZ1_THREAD_LOG_WARN, "!!! Conformance Check Fail : %s\n", str_name);
		}
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1Asn1Enum_finalize(void *_dst, Dz1Asn1WipValue *_src, Dz1Asn1TypeDescr *descr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
//	Dz1Asn1Enum *dst = (Dz1Asn1Enum *)_dst;
	tag_Dz1Asn1Enum *dst = (tag_Dz1Asn1Enum *)_dst;
	if (dst == NULL || _src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (_src->present != Dz1Asn1WipValuePresent_number) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1Asn1TypeDescr_chkConformance(descr, &_src->x.number, NULL) == FALSE)
	{
		u32_t log_lv = 0;
		Dz1Thread_getLogLevel(Dz1Thread_self(), &log_lv);
		if (log_lv & DZ1_THREAD_LOG_WARN)
		{
			char str_name[128];
			Dz1Asn1UTF8StrA_printable(descr->name, str_name, sizeof(str_name), NULL);
			_Dz1Thread_log("!!! Conformance Check Fail : %s\n", str_name);
		}
	}
	else
	{
		(*dst) = _src->x.number;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

Dz1Asn1DataTypeFinalizeF_declare(Dz1Asn1EmbPdv)			// FINALIZE

Dz1Asn1DataTypeFinalizeF_announce(Dz1Asn1UniversalStr)					// bool_t Dz1Asn1UniversalStr_finalize(void *_dst, Dz1Asn1WipValue *_src, Dz1Asn1TypeComformance *conformance, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1Binary *bin = NULL;
	Dz1ElasticBuf *elb = NULL;
	Dz1Asn1UniversalStr *dst = (Dz1Asn1UniversalStr *)_dst;
	if (dst == NULL || _src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (dst->data != NULL || dst->size != 0) ERR_SET_OUT(errp, EINVAL);
	else if (_src->present != Dz1Asn1WipValuePresent_octet_str) ERR_SET_OUT(errp, EFAULT);
	else if ((elb = _src->x.octet_str) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((bin = (Dz1Binary *)Dz1ElasticBuf_flattenAndPurge(_src->x.octet_str, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

		dst->data = bin->data;
		bin->data = NULL;

		dst->size = bin->size;
		bin->size = 0;

		if (Dz1Asn1TypeDescr_chkConformance(descr, dst, NULL) == FALSE)
		{
			char str_name[64];
			Dz1Asn1UTF8StrA_printable(descr->name, str_name, 64, NULL);
			Dz1Thread_log(DZ1_THREAD_LOG_WARN, "!!! Conformance Check Fail : %s\n", str_name);
		}
		Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

Dz1Asn1DataTypeFinalizeF_declare(Dz1Asn1CharStr)		// FINALIZE

Dz1Asn1DataTypeFinalizeF_announce(Dz1Asn1BMPStr)						// bool_t Dz1Asn1BMPStr_finalize(void *_dst, Dz1Asn1WipValue *_src, Dz1Asn1TypeComformance *conformance, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1Binary *bin = NULL;
	Dz1ElasticBuf *elb = NULL;
	Dz1Asn1BMPStr *dst = (Dz1Asn1BMPStr *)_dst;
	if (dst == NULL || _src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (dst->data != NULL || dst->size != 0) ERR_SET_OUT(errp, EINVAL);
	else if (_src->present != Dz1Asn1WipValuePresent_octet_str) ERR_SET_OUT(errp, EFAULT);
	else if ((elb = _src->x.octet_str) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((bin = (Dz1Binary *)Dz1ElasticBuf_flattenAndPurge(_src->x.octet_str, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

		dst->data = bin->data;
		bin->data = NULL;

		dst->size = bin->size;
		bin->size = 0;

		if (Dz1Asn1TypeDescr_chkConformance(descr, dst, NULL) == FALSE)
		{
			char str_name[64];
			Dz1Asn1UTF8StrA_printable(descr->name, str_name, 64, NULL);
			Dz1Thread_log(DZ1_THREAD_LOG_WARN, "!!! Conformance Check Fail : %s\n", str_name);
		}
		Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Finalize
///////////////////////////////////////////////////////////////////////////////


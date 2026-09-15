#include "dz1_asn1_codec_ber.h"


Dz1Asn1Any *Dz1Asn1Any_newFromBER(Dz1Asn1TypeDescr *descr, void *ptr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1Any *ret = NULL;
	if (descr == NULL || ptr == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1Asn1Any_new(NULL, 0, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1ElasticBuf *elb = NULL;
		Dz1Asn1BerEncoderArg param = { Dz1Asn1BerEncoderOpt_der };
		pthread_cleanup_push(Dz1Asn1Any_delAndSetNull, (void *)&ret);
		if ((elb = Dz1ElasticBuf_new(512, FALSE, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Binary *bin = NULL;
			pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);
			if (Dz1Asn1BerEncoder_enc(elb, descr, ptr, Dz1Asn1TagOpt_explicit, NULL, &param, errp) == FALSE) ERR_OUT(errp);
			else if ((bin = Dz1ElasticBuf_flattenAndPurge(elb, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

				ret->data = bin->data; bin->data = NULL;
				ret->size = bin->size;
				Dz1Error_set(errp, 0);

				pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
			}
			pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
		}
		pthread_cleanup_pop(errp->code); // (Dz1Asn1Any_delAndSetNull, (void *)&ret);
	}
	return ret;
}


///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipOpenData
static bool_t Dz1Asn1WipOpenData_getInfo(Dz1Asn1WipOpenData *src, bool_t *ret_flag, u64_t *ret_len, Dz1Error *errp)
{
	switch(src->present)
	{
	case Dz1Asn1WipOpenDataPresent_primitive: 
		*ret_flag = FALSE; 
		if (ret_len)
		{
			ssize_t sz = 0;
			if ((sz = Dz1ElasticBuf_getDataSize(src->x.primitive, errp)) < 0) ERR_OUT(errp);
			else
			{
				*ret_len = (u64_t)sz;
				Dz1Error_set(errp, 0);
			}
		}
		else Dz1Error_set(errp, 0);
		break;
	case Dz1Asn1WipOpenDataPresent_construct:
		*ret_flag = TRUE; 
		break;
	default: ERR_SET_OUT(errp, EFAULT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1Asn1WipOpenType_BER_flattern(Dz1Asn1WipOpenType *src, Dz1ElasticBuf *elb, Dz1Error *err);
static Dz1Error _Dz1Asn1WipOpenTypeList_BER_flattern(void *ptr, Dz1Asn1WipOpenTypeEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1ElasticBuf *elb = (Dz1ElasticBuf *)ptr;
	if (Dz1Asn1WipOpenType_BER_flattern(p->data, elb, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
static bool_t Dz1Asn1WipOpenTypeList_BER_flattern(Dz1Asn1WipOpenTypeList *src, Dz1ElasticBuf *elb, Dz1Error *errp)
{
	if (src == NULL || elb == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = src->travel(src, _Dz1Asn1WipOpenTypeList_BER_flattern, (void *)elb)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1Asn1WipOpenData_BER_flattern(Dz1Asn1WipOpenData *src, Dz1ElasticBuf *elb, Dz1Error *errp)
{
	ssize_t sz = 0;
	Dz1Binary *bin = NULL;
	switch(src->present)
	{
	case Dz1Asn1WipOpenDataPresent_primitive: 
		if ((bin = (Dz1Binary *)Dz1ElasticBuf_flatten(src->x.primitive, errp)) == NULL)
		{	// maybe NULL?
			Dz1Error_set(errp, 0);
		}
//		else if ((sz = Dz1Stream_write(st, bin->data, bin->size, errp)) < 0) ERR_OUT(errp);
		else if (_Dz1ElasticBuf_push(elb, bin->data, bin->size, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Dz1Asn1WipOpenDataPresent_construct:
		if (Dz1Asn1WipOpenTypeList_BER_flattern(src->x.construct, elb, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default: ERR_SET_OUT(errp, EFAULT); break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Dz1Asn1WipOpenData
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1WipOpenType
static bool_t _push_tag(Dz1ElasticBuf *elb, Dz1Asn1TagClass cls, bool_t is_construct, u64_t number, Dz1Error *errp)
{
	ssize_t sz = 0;

	Dz1Asn1Tag tag = { cls, is_construct, number };
	if ((sz = Dz1Asn1Tag_enc_BER(elb, &tag, is_construct, NULL, errp)) < 0) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _push_len(Dz1ElasticBuf *elb, /*bool_t is_construct,*/ u64_t len, Dz1Error *errp)
{
	ssize_t sz = 0;

// 	u64_t len = (u64_t)length;
// 	if (is_construct) len = Dz1Asn1BerLength_soc;

	if ((sz = Dz1Asn1BerLength_enc_BER(elb, len, NULL, errp)) < 0) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _push_eoc(Dz1ElasticBuf *elb, /*bool_t is_construct,*/ u64_t length, Dz1Error *errp)
{
//	if (is_construct)
	if (length == Dz1Asn1BerLength_soc)
	{
		ssize_t sz = 0;
		u8_t eoc[] = { 0x00, 0x00 };
		if (_Dz1ElasticBuf_push(elb, eoc, sizeof(eoc), errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t Dz1Asn1WipOpenType_BER_flattern(Dz1Asn1WipOpenType *src, Dz1ElasticBuf *elb, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || elb == NULL) ERR_OUT(errp);
	else
	{
		bool_t is_construct = FALSE;
		ssize_t sz = 0;
//		u32_t prim_size = 0;
		if (Dz1Asn1WipOpenData_getInfo(src->contents, &is_construct, /*&prim_size,*/ NULL, errp) == FALSE) ERR_OUT(errp);
		else if (_push_tag(elb, src->cls, is_construct, src->number, errp) == FALSE) ERR_OUT(errp);
//		else if (_push_len(elb, is_construct, prim_size, errp) == FALSE) ERR_OUT(errp);
		else if (_push_len(elb, src->len, errp) == FALSE) ERR_OUT(errp);
		else if (Dz1Asn1WipOpenData_BER_flattern(src->contents, elb, errp) == FALSE) ERR_OUT(errp);
//		else if (_push_eoc(elb, is_construct, prim_size, errp) == FALSE) ERR_OUT(errp);
		else if (_push_eoc(elb, src->len, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Dz1Asn1WipOpenType
///////////////////////////////////////////////////////////////////////////////

bool_t Dz1Asn1Any_BER_initFromWIP(Dz1Asn1Any *dst, Dz1Asn1WipOpenType *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ElasticBuf *elb = NULL;
	if (dst == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (dst->data != NULL || dst->size != 0) ERR_SET_OUT(errp, EINVAL);
	else if ((elb = Dz1ElasticBuf_new(512, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Binary *bin = NULL;
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);

		if (Dz1Asn1WipOpenType_BER_flattern(src, elb, errp) == FALSE) ERR_OUT(errp);
		else if ((bin = Dz1ElasticBuf_flattenAndPurge(elb, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

			dst->data = bin->data;
			bin->data = NULL;

			dst->size = bin->size;
			bin->size = 0;

			pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

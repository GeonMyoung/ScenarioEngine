#include "dz1_gasn_support.h"

#ifdef __BORLANDC__
#pragma warn -8056
#endif

///////////////////////////////////////////////////////////////////////////////
// PER Constraint(UNCONS)
Asn1ConsInfo dz1GasnPerNoConstraint = { DZ1INT64(0x8000000000000000), DZ1INT64(0x7FFFFFFFFFFFFFFF), NULL, FALSE, UNCONS, FALSE, FALSE };
// PER Constraint(UNCONS)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ASN1WorkSapce support
ASN1WorkSpace *ASN1WorkSpace_new(int *err_status)
{
	int _err_status = 0, *errp = err_status == NULL ? &_err_status : err_status;

	ASN1WorkSpace *ret = (ASN1WorkSpace *)malloc(sizeof(ASN1WorkSpace));
	if (ret == NULL) *errp = errno;
	else if (ASN1_INIT_WS_INFO(ret) < 0)
	{
		free(ret);
		ret = NULL;
		*errp = ENOMEM;
	}
	else *errp = 0;

	return ret;
}

void ASN1WorkSpace_del(ASN1WorkSpace *p)
{
	if (p != NULL)
	{
		ASN1_Destroy_WORKSPACE(p);
		free(p);
	}
}

ASNUINT8 *ASN1WorkSpace_getEncodePtr(ASN1WorkSpace *p)
{
	ASNUINT8 *ret = NULL;
	if (p != NULL)
	{
		ret = p->buffer.data;
	}
	return ret;
}

ASNUINT32 ASN1WorkSpace_getEncodedSize(ASN1WorkSpace *p, Dz1Asn1Codec codec)
{
	ASNUINT32 ret = 0;
	if (p != NULL)
	{
		ret = (ASNUINT32)(p->buffer.current - p->buffer.data);
		switch(codec)
		{
		default:
		case Dz1Asn1Codec_ber:
		case Dz1Asn1Codec_xer:
			break;
		case Dz1Asn1Codec_uper:
		case Dz1Asn1Codec_aper:
			if (p->buffer.byteIndex) ret++;
			break;
		}
	}
	return ret;
}
// ASN1WorkSapce support
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1Codec
u8_t Dz1GASN_getSupportedCodec(void)
{
#if defined(GITSN_GENERAL_ASN_TOOL)
	return ISO14827CODEC_BER;
#elif defined (GITSN_NEW_ASN_TOOL)
	return DZ1_ASN1_CODEC_BIT_BER | DZ1_ASN1_CODEC_BIT_APER | DZ1_ASN1_CODEC_BIT_UPER;
#endif
}

u8_t Dz1GASN_codec2Bit(Dz1Asn1Codec codec)
{
	u8_t ret = 0;
	switch(codec)
	{
		case Dz1Asn1Codec_ber:
			ret = DZ1_ASN1_CODEC_BIT_BER;
			break;
		case Dz1Asn1Codec_aper:
			ret = DZ1_ASN1_CODEC_BIT_APER;
			break;
		case Dz1Asn1Codec_uper:
			ret = DZ1_ASN1_CODEC_BIT_UPER;
			break;
		case Dz1Asn1Codec_xer:
			ret = DZ1_ASN1_CODEC_BIT_XER;
			break;
		case Dz1Asn1Codec_cxer:
			ret = DZ1_ASN1_CODEC_BIT_CXER;
			break;
		case Dz1Asn1Codec_unknown:
		default:
			break;

	}
	return ret;
}

static u32_t CodecOID_ber[] =	{ 2, 1, 1 };
static u32_t CodecOID_aper[] =	{ 2, 1, 3, 0, 0 };
static u32_t CodecOID_uper[] =	{ 2, 1, 3, 0, 1 };
static u32_t CodecOID_xer[] =	{ 2, 1, 5, 0 };
static u32_t CodecOID_cxer[] =	{ 2, 1, 5, 1 };

static Dz1Asn1OID OID_ber =		{ CodecOID_ber,	3 };
static Dz1Asn1OID OID_aper =	{ CodecOID_aper,5 };
static Dz1Asn1OID OID_uper =	{ CodecOID_uper,5 };
static Dz1Asn1OID OID_xer =		{ CodecOID_xer,	4 };
static Dz1Asn1OID OID_cxer =	{ CodecOID_cxer,4 };

struct CodecOIDMap
{
	Dz1Asn1OID *oid;
	Dz1Asn1Codec codec;
} CodecOIDMap[] = 
{
	{ &OID_ber, Dz1Asn1Codec_ber },
	{ &OID_aper, Dz1Asn1Codec_aper },
	{ &OID_uper, Dz1Asn1Codec_uper },
	{ &OID_xer, Dz1Asn1Codec_xer },
	{ &OID_cxer, Dz1Asn1Codec_cxer },
	{ NULL, Dz1Asn1Codec_unknown }
};

Dz1Asn1Codec Dz1GASN_oid2Codec(Dz1Asn1OID *oid)
{
	struct CodecOIDMap *i;
	if (oid == NULL) return Dz1Asn1Codec_unknown;

	for (i = CodecOIDMap; i->oid != NULL; i++)
		if (Dz1Asn1OID_cmp(i->oid, oid) == 0) break;
	return i->codec;
}

Dz1Asn1OID *Dz1GASN_codec2OID(Dz1Asn1Codec codec)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1Asn1OID *ret = NULL;
	struct CodecOIDMap *i;
	for (i = CodecOIDMap; i->oid != NULL; i++)
	{
		if (i->codec == codec)
		{
			if ((ret = Dz1Asn1OID_clone(i->oid, &err)) == NULL) ERR_OUT(&err);
			break;
		}
	}
	return ret;
}
// Dz1Asn1Codec
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// GasnStructPkg utility
GasnStructPkg *_GasnStructPkg_gen(Dz1Error *err, char *__file__, int __line__)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GasnStructPkg *ret = (GasnStructPkg *)_Dz1Calloc(sizeof(GasnStructPkg), 1, errp, __file__, __line__);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

GasnStructPkg *_GasnStructPkg_gen2(Dz1Error *err, char *__file__, int __line__)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GasnStructPkg *ret = (GasnStructPkg *)_Dz1Calloc(sizeof(GasnStructPkg), 1, errp, __file__, __line__);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		int status = 0;
		pthread_cleanup_push(GasnStructPkg_delAndSetNull, (void *)&ret);
		if ((ret->storage = ASN1WorkSpace_new(&status)) == NULL) ERR_SET_OUT(errp, status);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (GasnStructPkg_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void GasnStructPkg_del(GasnStructPkg *p)
{
	if (p != NULL)
	{
		ASN1WorkSpace_delAndSetNull(&p->storage);
		Dz1Free(p);
	}
}
// GasnStructPkg utility
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1OctetStr Support
///////////////////////////////////////////////////////////////////////////////
Dz1Error Dz1Asn1OctetStr_fromASN(Dz1Asn1OctetStr *dst, OCTETSTRING *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (src->data != NULL && src->numbits != 0)
	{
		if ((dst->data = (u8_t *)Dz1Memory_clone(src->data, src->numbits, &err)) == NULL) ERR_OUT(&err);
		else dst->size = src->numbits;
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}
DZ1_NEW_FROM_ASN(Dz1Asn1OctetStr, OCTETSTRING)
/*
// OCTET STRING : BER Decode
DECODE_BER_FUNC_IMPL_NODUMP(Dz1Asn1OctetStr, OCTETSTRING)
///////////////////////////////////////////////////////////////////////////////
// OCTET STRING : uPER Decode
///////////////////////////////////////////////////////////////////////////////
static ssize_t Dz1Asn1OctetStr_decodeUPer(Dz1Asn1OctetStr **dst, u8_t *src, size_t size, Dz1Error *errp)
{
	ssize_t _ret = -1;
	OCTETSTRING temp;
	Asn1ConsInfo cons = {
		-9223372036854775807,
		9223372036854775807,
		NULL,
		0,
		UNCONS,
		0,
		0
	};
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	
	memset(&temp, 0, sizeof(OCTETSTRING));
	
	ASN1_Save_WORKSPACE(&ws, src, (ASNINT32)size);
	ws.dataSize = (ASNINT32)size;
	
	if (ASN1_PER_UNAlign_Dec_OCTETSTRING(&ws, &temp, &cons) < 0) ERR_SET_OUT(errp, EFAULT);
	else
	{
		_ret = (ssize_t)(ws.buffer.current - ws.buffer.data + (ws.buffer.bitOffset != 8 ? 1 : 0));
		if ((*dst = Dz1Asn1OctetStr_new(temp.data, temp.numbits, errp)) == NULL) ERR_OUT(errp);
	}
	
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return _ret;
}
// OCTET STRING : Total Decode
DECODE_FUNC_IMPL(Dz1Asn1OctetStr)
*/
Dz1Error Dz1Asn1OctetStr_toASN(OCTETSTRING *dst, Dz1Asn1OctetStr *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (src->size > 0 && src->data == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ASNUINT8 *cp = (src->data == NULL || src->size == 0) ? (ASNUINT8 *)1 : (ASNUINT8 *)src->data;
		if (ASN1_SET_OCTETSTRING(ws, dst, cp, (ASNINT32)src->size) < 0) ERR_SET_OUT(&err, EFAULT);
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1Asn1OctetStr, OCTETSTRING)
/*
// OCTET STRING : BER Encode
ENCODE_BER_FUNC_IMPL_NODUMP(Dz1Asn1OctetStr, OCTETSTRING)

// OCTET STRING : uPER Encode
static ssize_t Dz1Asn1OctetStr_encodeUPer(OCTETSTRING *src, u8_t **dst, ASN1WorkSpace *ws, Dz1Error *errp)
{
	ssize_t _ret = -1;
	struct Asn1ConsInfo cons = {-9223372036854775807, 9223372036854775807, NULL, 0, UNCONS, 0, 0};
	
	if (ASN1_PER_UNAlign_Enc_OCTETSTRING(ws, src, &cons) < 0) ERR_SET_OUT(errp, EFAULT);
	else
	{
		_ret = (ssize_t)(ws->buffer.current - ws->buffer.data + (ws->buffer.bitOffset != 8 ? 1 : 0));
		if (((*dst) = (u8_t *)Dz1Malloc(_ret, errp)) == NULL) ERR_OUT(errp);
		else memcpy((*dst), ws->buffer.data, _ret);
	}
	return _ret;
}


// OCTET STRING : Total Encode
ENCODE_FUNC_IMPL_NODUMP(Dz1Asn1OctetStr, OCTETSTRING)
*/
///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1OID
///////////////////////////////////////////////////////////////////////////////
Dz1Error Dz1Asn1OID_fromASN(Dz1Asn1OID *dst, OBJECTIDENTIFIER *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	 
	else
	{
		//ASNUINT32 *oids = NULL;
		ASNUINT32 cnt, idx = 0;
		OBJECTIDENTIFIER temp;
		if (ASN1_GET_OBJECTIDENTIFIER(&ws, src, temp.subid, &temp.numids) < 0) ERR_OUT(&err);
		else
		{
			if (dst->data != NULL) { Dz1Free(dst->data); dst->data = NULL; }

			dst->cnt = temp.numids;
			cnt = (ASNUINT32)dst->cnt;
			if ((dst->data = (u32_t *)Dz1Calloc(sizeof(u32_t), (cnt = (ASNUINT32)dst->cnt), &err)) == NULL) ERR_OUT(&err);
			else
			{
				while(cnt--)
				{
					dst->data[idx] = temp.subid[idx];
					idx++;
				}
			}
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}
DZ1_NEW_FROM_ASN(Dz1Asn1OID, OBJECTIDENTIFIER)
/*
DECODE_BER_FUNC_IMPL_NODUMP(Dz1Asn1OID, OBJECTIDENTIFIER)
static ssize_t Dz1Asn1OID_decodeUPer(Dz1Asn1OID **dst, u8_t *buf, size_t size, Dz1Error *errp)
{
	ssize_t ret = -1;
	if (dst == NULL || buf == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		OBJECTIDENTIFIER msg;

 		ASN1WorkSpace ws;
 		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

		ASN1_Save_WORKSPACE(&ws, buf, (ASNINT32)size);
		ws.dataSize = (ASNINT32)size;

		if (( ASN1_PER_UNAlign_Dec_OBJECTIDENTIFIER(&ws, &msg, NULL)) < 0) {ERR_SET_OUT(errp, EFAULT);}
 		else if (((*dst) = Dz1Asn1OID_newFromASN(&msg, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else ret = (ssize_t)(ws.buffer.current - ws.buffer.data + (ws.buffer.bitOffset != 8 ? 1 : 0));

		pthread_cleanup_pop(1);
	}
	return ret;
}
DECODE_FUNC_IMPL(Dz1Asn1OID)
*/
Dz1Error Dz1Asn1OID_toASN(OBJECTIDENTIFIER *dst, Dz1Asn1OID *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	 
	else if (( ASN1_SET_OBJECTIDENTIFIER(ws, dst, src->data, (int)src->cnt)) < 0) {ERR_SET_OUT(&err, EFAULT);}

	return err;
}
DZ1_TO_NEW_ASN(Dz1Asn1OID, OBJECTIDENTIFIER)
/*
ENCODE_BER_FUNC_IMPL(Dz1Asn1OID, OBJECTIDENTIFIER)
ssize_t Dz1Asn1OID_encodeUPer(OBJECTIDENTIFIER *src, u8_t **dst, ASN1WorkSpace *ws, Dz1Error *errp)
{
	ssize_t ret = 0;
	if ((ASN1_PER_UNAlign_Enc_OBJECTIDENTIFIER(ws, src, NULL)) < 0) { ERR_SET_OUT(errp, EFAULT); ret = -1; }
	else
	{
		ret = (ssize_t)(ws->buffer.current - ws->buffer.data + (ws->buffer.bitOffset != 8 ? 1 : 0));
		if (((*dst) = (u8_t *)Dz1Malloc(ret, errp)) == NULL) { ERR_SET_OUT(errp, EFAULT); ret = -1; }
		else
		{
			memcpy((*dst), ws->buffer.data, ret);
			Dz1Thread_printf("Dz1Asn1OID_encodeBer() : Encoded\n");
			Dz1Thread_tprintb(1, (*dst), ret, 16);
		}
	}
	return ret;
}
ENCODE_FUNC_IMPL_NODUMP(Dz1Asn1OID, OBJECTIDENTIFIER)
*/
///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1BitStr
///////////////////////////////////////////////////////////////////////////////
Dz1Error Dz1Asn1BitStr_fromASN(Dz1Asn1BitStr *dst, BITSTRING *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ASNUINT8 *temp = NULL;
		ASNUINT32L temp_len = 0;
		if (ASN1_GET_BITSTRING(&ws, src, &temp, &temp_len) < 0) { ERR_SET_OUT(&err, EFAULT); }
		else if ((err = Dz1Asn1BitStr_assign(dst, temp, temp_len)).code) { ERR_OUT(&err); }
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}
DZ1_NEW_FROM_ASN(Dz1Asn1BitStr, BITSTRING)
/*
DECODE_BER_FUNC_IMPL_NODUMP(Dz1Asn1BitStr, BITSTRING)
ssize_t Dz1Asn1BitStr_decodeUPer(Dz1Asn1BitStr **dst, u8_t *buf, size_t size, Dz1Error *errp)
{
	ssize_t ret = -1;
	if (dst == NULL || buf == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		BITSTRING msg;
 		ASN1WorkSpace ws;
 		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
		ASN1_Save_WORKSPACE(&ws, buf, (ASNINT32)size);
		ws.dataSize = (ASNINT32)size;
		if (( ASN1_PER_UNAlign_Dec_BITSTRING(&ws, &msg)) < 0) {ERR_SET_OUT(errp, EFAULT);}
 		else if (((*dst) = Dz1Asn1BitStr_newFromASN(&msg, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else ret = (ssize_t)(ws.buffer.current - ws.buffer.data + (ws.buffer.bitOffset != 8 ? 1 : 0));
		pthread_cleanup_pop(1);
	}
	return ret;
}
DECODE_FUNC_IMPL(Dz1Asn1BitStr)
*/

Dz1Error Dz1Asn1BitStr_toASN(BITSTRING *dst, Dz1Asn1BitStr *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (ASN1_SET_BITSTRING(ws, dst, src->bits, (ASNINT32L)src->maxBit) < 0) { ERR_OUT(&err); }
	return err;
}
DZ1_TO_NEW_ASN(Dz1Asn1BitStr, BITSTRING)
/*
ENCODE_BER_FUNC_IMPL(Dz1Asn1BitStr, BITSTRING)
ENCODE_UPER_FUNC_IMPL(Dz1Asn1BitStr, BITSTRING)
ENCODE_FUNC_IMPL_NODUMP(Dz1Asn1BitStr, BITSTRING)
*/

///////////////////////////////////////////////////////////////////////////////
// u64_t
///////////////////////////////////////////////////////////////////////////////
Dz1Error u64_t_fromASN(u64_t *dst, INTEGER *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		INTEGER v;
		if (ASN1_GET_INTEGER(&ws, src, &v) < 0) ERR_SET_OUT(&err, EFAULT);
		else (*dst) = (u64_t)v;
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}
DZ1_NEW_FROM_ASN(u64_t, INTEGER)

/*
DECODE_BER_FUNC_IMPL_NODUMP(u64_t, INTEGER)
DECODE_UPER_FUNC_IMPL_NODUMP(u64_t, INTEGER)
DECODE_FUNC_IMPL(u64_t)
*/

Dz1Error u64_t_toASN(INTEGER *dst, u64_t *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		INTEGER v = (INTEGER)(*src);
		if (ASN1_SET_INTEGER(ws, dst, v) < 0) ERR_SET_OUT(&err, EFAULT);
	}
	return err;
}
DZ1_TO_NEW_ASN(u64_t, INTEGER)
/*
ENCODE_BER_FUNC_IMPL(u64_t, INTEGER)
ENCODE_FUNC_IMPL_NODUMP(u64_t, INTEGER)
*/

///////////////////////////////////////////////////////////////////////////////
// s64_t
///////////////////////////////////////////////////////////////////////////////
Dz1Error s64_t_fromASN(s64_t *dst, INTEGER *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		INTEGER v;
		if (ASN1_GET_INTEGER(&ws, src, &v) < 0) ERR_SET_OUT(&err, EFAULT);
		else (*dst) = (s64_t)v;
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}
DZ1_NEW_FROM_ASN(s64_t, INTEGER)
/*
DECODE_BER_FUNC_IMPL_NODUMP(s64_t, INTEGER)
DECODE_FUNC_IMPL(s64_t)
*/
Dz1Error s64_t_toASN(INTEGER *dst, s64_t *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		INTEGER v = (INTEGER)(*src);
		if (ASN1_SET_INTEGER(ws, dst, v) < 0) ERR_SET_OUT(&err, EFAULT);
	}
	return err;
}
DZ1_TO_NEW_ASN(s64_t, INTEGER)
/*
static ENCODE_BER_FUNC_IMPL(s32_t, INTEGER)
ENCODE_FUNC_IMPL_NODUMP(s32_t, INTEGER)
*/
///////////////////////////////////////////////////////////////////////////////
// u32_t
///////////////////////////////////////////////////////////////////////////////
Dz1Error u32_t_fromASN(u32_t *dst, INTEGER *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		INTEGER v;
		if (ASN1_GET_INTEGER(&ws, src, &v) < 0) ERR_SET_OUT(&err, EFAULT);
		else (*dst) = (u32_t)(v & 0xFFFFFFFF);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}
DZ1_NEW_FROM_ASN(u32_t, INTEGER)

/*
DECODE_BER_FUNC_IMPL_NODUMP(u32_t, INTEGER)
DECODE_UPER_FUNC_IMPL_NODUMP(u32_t, INTEGER)
DECODE_FUNC_IMPL(u32_t)
*/

Dz1Error u32_t_toASN(INTEGER *dst, u32_t *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		INTEGER v = (INTEGER)(*src);
		if (ASN1_SET_INTEGER(ws, dst, v) < 0) ERR_SET_OUT(&err, EFAULT);
	}
	return err;
}
DZ1_TO_NEW_ASN(u32_t, INTEGER)
/*
ENCODE_BER_FUNC_IMPL(u32_t, INTEGER)
ENCODE_FUNC_IMPL_NODUMP(u32_t, INTEGER)
*/
///////////////////////////////////////////////////////////////////////////////
// s32_t
///////////////////////////////////////////////////////////////////////////////
Dz1Error s32_t_fromASN(s32_t *dst, INTEGER *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		INTEGER v;
		if (ASN1_GET_INTEGER(&ws, src, &v) < 0) ERR_SET_OUT(&err, EFAULT);
		else (*dst) = (s32_t)(v & 0xFFFFFFFF);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}
DZ1_NEW_FROM_ASN(s32_t, INTEGER)
/*
DECODE_BER_FUNC_IMPL_NODUMP(s32_t, INTEGER)
DECODE_FUNC_IMPL(s32_t)
*/
Dz1Error s32_t_toASN(INTEGER *dst, s32_t *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		INTEGER v = (INTEGER)(*src);
		if (ASN1_SET_INTEGER(ws, dst, v) < 0) ERR_SET_OUT(&err, EFAULT);
	}
	return err;
}
DZ1_TO_NEW_ASN(s32_t, INTEGER)
/*
static ENCODE_BER_FUNC_IMPL(s32_t, INTEGER)
ENCODE_FUNC_IMPL_NODUMP(s32_t, INTEGER)
*/
///////////////////////////////////////////////////////////////////////////////
// u16_t
///////////////////////////////////////////////////////////////////////////////
Dz1Error u16_t_fromASN(u16_t *dst, INTEGER *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		INTEGER v;
		if (ASN1_GET_INTEGER(&ws, src, &v) < 0) ERR_SET_OUT(&err, EFAULT);
		else (*dst) = (u16_t)(v & 0xFFFF);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}
DZ1_NEW_FROM_ASN(u16_t, INTEGER)
/*
DECODE_BER_FUNC_IMPL_NODUMP(u16_t, INTEGER)
DECODE_FUNC_IMPL(u16_t)
*/
Dz1Error u16_t_toASN(INTEGER *dst, u16_t *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		INTEGER v = (INTEGER)(*src);
		if (ASN1_SET_INTEGER(ws, dst, v) < 0) ERR_SET_OUT(&err, EFAULT);
	}
	return err;
}
DZ1_TO_NEW_ASN(u16_t, INTEGER)
/*
ENCODE_BER_FUNC_IMPL(u16_t, INTEGER)
ENCODE_FUNC_IMPL_NODUMP(u16_t, INTEGER)
*/
///////////////////////////////////////////////////////////////////////////////
// s16_t
///////////////////////////////////////////////////////////////////////////////
Dz1Error s16_t_fromASN(s16_t *dst, INTEGER *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		INTEGER v;
		if (ASN1_GET_INTEGER(&ws, src, &v) < 0) ERR_SET_OUT(&err, EFAULT);
		else (*dst) = (u16_t)(v & 0xFFFF);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}
DZ1_NEW_FROM_ASN(s16_t, INTEGER)
/*
DECODE_BER_FUNC_IMPL_NODUMP(s16_t, INTEGER)
DECODE_FUNC_IMPL(s16_t)
*/
Dz1Error s16_t_toASN(INTEGER *dst, s16_t *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		INTEGER v = (INTEGER)(*src);
		if (ASN1_SET_INTEGER(ws, dst, v) < 0) ERR_SET_OUT(&err, EFAULT);
	}
	return err;
}
DZ1_TO_NEW_ASN(s16_t, INTEGER)
/*
ENCODE_BER_FUNC_IMPL(s16_t, INTEGER)
ENCODE_FUNC_IMPL_NODUMP(s16_t, INTEGER)
*/
///////////////////////////////////////////////////////////////////////////////
// u8_t
///////////////////////////////////////////////////////////////////////////////
Dz1Error u8_t_fromASN(u8_t *dst, INTEGER *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		INTEGER v;
		if (ASN1_GET_INTEGER(&ws, src, &v) < 0) ERR_SET_OUT(&err, EFAULT);
		else (*dst) = (u8_t)(v & 0xFF);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}
DZ1_NEW_FROM_ASN(u8_t, INTEGER)
/*
DECODE_BER_FUNC_IMPL_NODUMP(u8_t, INTEGER)
DECODE_FUNC_IMPL(u8_t)
*/
Dz1Error u8_t_toASN(INTEGER *dst, u8_t *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		INTEGER v = (INTEGER)(*src);
		if (ASN1_SET_INTEGER(ws, dst, v) < 0) ERR_SET_OUT(&err, EFAULT);
	}
	return err;
}
DZ1_TO_NEW_ASN(u8_t, INTEGER)
/*
ENCODE_BER_FUNC_IMPL(u8_t, INTEGER)
ENCODE_FUNC_IMPL_NODUMP(u8_t, INTEGER)
*/

///////////////////////////////////////////////////////////////////////////////
// s8_t
///////////////////////////////////////////////////////////////////////////////
Dz1Error s8_t_fromASN(s8_t *dst, INTEGER *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		INTEGER v;
		if (ASN1_GET_INTEGER(&ws, src, &v) < 0) ERR_SET_OUT(&err, EFAULT);
		else (*dst) = (s8_t)(v & 0xFF);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}
DZ1_NEW_FROM_ASN(s8_t, INTEGER)
/*
DECODE_BER_FUNC_IMPL_NODUMP(u8_t, INTEGER)
DECODE_FUNC_IMPL(u8_t)
*/
Dz1Error s8_t_toASN(INTEGER *dst, s8_t *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		INTEGER v = (INTEGER)(*src);
		if (ASN1_SET_INTEGER(ws, dst, v) < 0) ERR_SET_OUT(&err, EFAULT);
	}
	return err;
}
DZ1_TO_NEW_ASN(s8_t, INTEGER)
/*
ENCODE_BER_FUNC_IMPL(u8_t, INTEGER)
ENCODE_FUNC_IMPL_NODUMP(u8_t, INTEGER)
*/







///////////////////////////////////////////////////////////////////////////////
// bool_t
///////////////////////////////////////////////////////////////////////////////
Dz1Error bool_t_fromASN(bool_t *dst, BOOLEAN *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		BOOLEAN v;
		if (ASN1_GET_BOOLEAN(&ws, src, &v) < 0) ERR_SET_OUT(&err, EFAULT);
		else (*dst) = v ? TRUE : FALSE;
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}
DZ1_NEW_FROM_ASN(bool_t, BOOLEAN)
/*
DECODE_BER_FUNC_IMPL_NODUMP(u8_t, INTEGER)
DECODE_FUNC_IMPL(u8_t)
*/

Dz1Error bool_t_toASN(BOOLEAN *dst, bool_t *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		BOOLEAN v = (*src) ? 1 : 0;
		if (ASN1_SET_BOOLEAN(ws, dst, v) < 0) ERR_SET_OUT(&err, EFAULT);
	}
	return err;
}
DZ1_TO_NEW_ASN(bool_t, BOOLEAN)


///////////////////////////////////////////////////////////////////////////////
// real_t
///////////////////////////////////////////////////////////////////////////////
Dz1Error real_t_fromASN(real_t *dst, REAL *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (ASN1_GET_REAL(&ws, src, dst) < 0) ERR_SET_OUT(&err, EFAULT);

	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}
DZ1_NEW_FROM_ASN(real_t, REAL)
/*
DECODE_BER_FUNC_IMPL_NODUMP(u8_t, INTEGER)
DECODE_FUNC_IMPL(u8_t)
*/

Dz1Error real_t_toASN(REAL *dst, real_t *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (ASN1_SET_REAL(ws, dst, *src) < 0) ERR_SET_OUT(&err, EFAULT);

	return err;
}
DZ1_TO_NEW_ASN(real_t, REAL)













///////////////////////////////////////////////////////////////////////////////
// Dz1TimeVal
///////////////////////////////////////////////////////////////////////////////
Dz1Error Dz1TimeVal_fromGeneralizedTime(Dz1TimeVal *dst, GeneralizedTime *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		struct tm tmVal;
		ASNINT32 diffsec = 0, fraction = 0, exponent = 0;
		if (ASN1_GET_GeneralizedTime(&ws, src, &tmVal, &diffsec, &fraction, &exponent) < 0) ERR_SET_OUT(&err, EFAULT);
			//                             tmVal = YYYYMMDDHHMMSS
			//							   diffsec = (+|-)seconds
			//							   fraction = fff
			//							   exponent = 10^(-exp)
		else
		{
			int e = 6 - exponent;
			time_t t = mktime(&tmVal) + diffsec;
			dst->tv_sec = (long)t;
			dst->tv_usec = (long)fraction;
			if (e < 0) while(e++) dst->tv_usec /= 10;
			else if (e > 0) while(e--) dst->tv_usec *= 10;
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}
DZ1_NEW_FROM_ASN_NAME(Dz1TimeVal, GeneralizedTime)
/*
DECODE_BER_FUNC_IMPL_NODUMP(Dz1TimeVal, GeneralizedTime)
DECODE_FUNC_IMPL(Dz1TimeVal)
*/
Dz1Error Dz1TimeVal_toGeneralizedTime(GeneralizedTime *dst, Dz1TimeVal *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		time_t tTemp = (time_t)src->tv_sec;
		struct tm *tm_p = gmtime((const time_t *)&tTemp), tmVal = (*tm_p);
		ASNINT32 diffsec = 9 * 3600;
		if (ASN1_SET_GeneralizedTime(ws, dst, &tmVal, diffsec, src->tv_usec, 6) < 0) ERR_SET_OUT(&err, EFAULT);
	}
	return err;
}
DZ1_TO_NEW_ASN_NAME(Dz1TimeVal, GeneralizedTime)
/*
ENCODE_BER_FUNC_IMPL(Dz1TimeVal, GeneralizedTime)
ENCODE_FUNC_IMPL_NODUMP(Dz1TimeVal, GeneralizedTime)
*/
///////////////////////////////////////////////////////////////////////////////
// str_t
///////////////////////////////////////////////////////////////////////////////
str_t str_t_newFromVisibleString(VisibleString *src, Dz1Error *err)
{
	str_t dst = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		ASNUINT8 *data;
		ASNINT32 size = 0;
		if (ASN1_GET_VisibleString(&ws, src, &data, &size) < 0) ERR_SET_OUT(errp, EFAULT);
		else if ((dst = (str_t)Dz1Calloc(sizeof(char), size + 1, errp)) == NULL) ERR_OUT(errp);
		else memcpy(dst, data, size);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return dst;
}

Dz1Error str_t_toVisibleString(VisibleString *dst, str_t src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ASNINT32 size = (ASNINT32)strlen(src);
		if (ASN1_SET_VisibleString(ws, dst, (ASNUINT8 *)src, size) < 0) ERR_SET_OUT(&err, EFAULT);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1UTF8Str
///////////////////////////////////////////////////////////////////////////////
#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
Dz1Error Dz1Asn1UTF8Str_fromASN(Dz1Asn1UTF8Str *dst, UTF8Str *src)
#else
Dz1Error Dz1Asn1UTF8Str_fromASN(Dz1Asn1UTF8Str *dst, UTF8String *src)
#endif
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ASNUINT8 *data = NULL;
		ASNINT32 size = 0;
#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
		if (ASN1_GET_UTF8Str(&ws, src, &data, &size) < 0) ERR_SET_OUT(&err, EFAULT);
#else
		if (ASN1_GET_UTF8String(&ws, src, &data, &size) < 0) ERR_SET_OUT(&err, EFAULT);
#endif
		else if ((dst->data = (u8_t *)Dz1Memory_clone(data, (dst->size = size), &err)) == NULL) ERR_OUT(&err);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}
#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
DZ1_NEW_FROM_ASN(Dz1Asn1UTF8Str, UTF8Str)
#else
DZ1_NEW_FROM_ASN(Dz1Asn1UTF8Str, UTF8String)
#endif
/*
DECODE_BER_FUNC_IMPL_NODUMP(Dz1Asn1UTF8Str, UTF8String)
DECODE_UPER_FUNC_IMPL_NODUMP(Dz1Asn1UTF8Str, UTF8String)
DECODE_FUNC_IMPL(Dz1Asn1UTF8Str)
*/
#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
Dz1Error Dz1Asn1UTF8Str_toASN(UTF8Str *dst, Dz1Asn1UTF8Str *src, ASN1WorkSpace *ws)
#else
Dz1Error Dz1Asn1UTF8Str_toASN(UTF8String *dst, Dz1Asn1UTF8Str *src, ASN1WorkSpace *ws)
#endif
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
		if (ASN1_SET_UTF8Str(ws, dst, src->data, (ASNINT32)src->size) < 0) ERR_SET_OUT(&err, EFAULT);
#else
		if (ASN1_SET_UTF8String(ws, dst, src->data, (ASNINT32)src->size) < 0) ERR_SET_OUT(&err, EFAULT);
#endif
	}
	return err;
}
#ifdef AVIOD_NAME_COLLISION_UTF8_STRING
DZ1_TO_NEW_ASN(Dz1Asn1UTF8Str, UTF8Str)
#else
DZ1_TO_NEW_ASN(Dz1Asn1UTF8Str, UTF8String)
#endif
/*
ENCODE_BER_FUNC_IMPL(Dz1Asn1UTF8Str, UTF8String)
ENCODE_UPER_FUNC_IMPL(Dz1Asn1UTF8Str, UTF8String)
ENCODE_FUNC_IMPL_NODUMP(Dz1Asn1UTF8Str, UTF8String)
*/
///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1UniversalStr
///////////////////////////////////////////////////////////////////////////////
Dz1Error Dz1Asn1UniversalStr_fromASN(Dz1Asn1UniversalStr *dst, UniversalString *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ASNUINT32 *data = NULL;
		ASNUINT32 size = 0;
		if (ASN1_GET_UniversalString(&ws, src, &data, &size) < 0) ERR_SET_OUT(&err, EFAULT);
		else if ((dst->data = (u8_t *)Dz1Memory_clone((u8_t *)data, (dst->size = (size << 2)), &err)) == NULL) ERR_OUT(&err);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}
DZ1_NEW_FROM_ASN(Dz1Asn1UniversalStr, UniversalString)
/*
DECODE_BER_FUNC_IMPL_NODUMP(Dz1Asn1UniversalStr, UniversalString)
DECODE_UPER_FUNC_IMPL_NODUMP(Dz1Asn1UniversalStr, UniversalString)
DECODE_FUNC_IMPL(Dz1Asn1UniversalStr)
*/
Dz1Error Dz1Asn1UniversalStr_toASN(UniversalString *dst, Dz1Asn1UniversalStr *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if (ASN1_SET_UniversalString(ws, dst, (ASNUINT32 *)src->data, (ASNINT32)(src->size >> 2)) < 0) ERR_SET_OUT(&err, EFAULT);
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1Asn1UniversalStr, UniversalString)

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1VisibleStr
///////////////////////////////////////////////////////////////////////////////
Dz1Error Dz1Asn1VisibleStr_fromASN(Dz1Asn1VisibleStr *dst, VisibleString *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		ASNUINT8 *data = NULL;
		ASNINT32 size = 0;
		if (ASN1_GET_VisibleString(&ws, src, &data, &size) < 0) ERR_SET_OUT(&err, EFAULT);
		else
		{
			dst->size = size;
			if ((dst->data = (u8_t *)Dz1Calloc(sizeof(u8_t), dst->size + 1, &err)) == NULL) ERR_OUT(&err);
			else memcpy(dst->data, data, dst->size);
		}
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}
DZ1_NEW_FROM_ASN(Dz1Asn1VisibleStr, VisibleString)
/*
DECODE_BER_FUNC_IMPL_NODUMP(Dz1Asn1UniversalStr, UniversalString)
DECODE_UPER_FUNC_IMPL_NODUMP(Dz1Asn1UniversalStr, UniversalString)
DECODE_FUNC_IMPL(Dz1Asn1UniversalStr)
*/
Dz1Error Dz1Asn1VisibleStr_toASN(VisibleString *dst, Dz1Asn1VisibleStr *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
		if (ASN1_SET_VisibleString(ws, dst, (ASNUINT8 *)src->data, (ASNINT32)src->size) < 0) ERR_SET_OUT(&err, EFAULT);
	}
	return err;
}
DZ1_TO_NEW_ASN(Dz1Asn1VisibleStr, VisibleString)
/*
ENCODE_BER_FUNC_IMPL(Dz1Asn1UniversalStr, UniversalString)
ENCODE_FUNC_IMPL_NODUMP(Dz1Asn1UniversalStr, UniversalString)
*/
/*
static Dz1Error _fromASN(dz1type *dst, asn1type *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);

	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)ASN1_Destroy_WORKSPACE, (void *)&ws);
	return err;
}
static DZ1_NEW_FROM_ASN(dz1type, asn1type)
static DECODE_BER_FUNC_IMPL(dz1type, asn1type)
DECODE_FUNC_IMPL(dz1type)

static Dz1Error _toASN(asn1type *dst, dz1type *src, ASN1WorkSpace *ws)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (dst == NULL || src == NULL) ERR_SET_OUT(&err, EINVAL);
	else
	{
	}
	return err;
}
static DZ1_TO_NEW_ASN(dz1type, asn1type)
static ENCODE_BER_FUNC_IMPL(dz1type, asn1type)
ENCODE_FUNC_IMPL(dz1type, asn1type)

*/
static Dz1GasnMsgCodecApi *Dz1GasnMsgCodecApi_findByPresent(Dz1GasnMsgCodecApi table[], int present)
{
	Dz1GasnMsgCodecApi *i;
	for (i = table; i->present != -1; i++)
		if (i->present == present) return i;
	return NULL;
}

static Dz1GasnMsgCodecApi *Dz1GasnMsgCodecApi_findByOIDStr(Dz1GasnMsgCodecApi table[], str_t oidStr)
{
	Dz1GasnMsgCodecApi *i;
	for (i = table; i->present != -1; i++)
		if (strcmp(i->oidStr, oidStr) == 0) return i;
	return NULL;
}

typedef enum GAsnStructMaskPresent
{
	GAsnStructMaskPresent_max
} GAsnStructMaskPresent;

typedef struct GAsnStructCaster
{
	GAsnStructMaskPresent		present;
	union
	{
		void *__ptr__;
		u8_t var[0];
	} x;
} GAsnStructCaster;

ssize_t Dz1GasnSupport_asn_encode(void *srcptr, u8_t **dstbuf, Dz1Asn1Codec codec, str_t *retOID, Dz1GasnMsgCodecApi table[], Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ssize_t ret = 0;
	GAsnStructCaster *src = (GAsnStructCaster *)srcptr;
	Dz1GasnMsgCodecApi *api = NULL;
	if (src == NULL || dstbuf == NULL || retOID == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if ((api = Dz1GasnMsgCodecApi_findByPresent(table, src->present)) == NULL) 
	{
		ERR_SET_OUT_RET(errp, ENOSYS, -1);
	}
	else
	{
		*retOID = api->oidStr;
		if (api->enc != NULL && (ret = api->enc((void *)src->x.__ptr__, dstbuf, codec, errp)) < 0) ERR_OUT(errp);
	}
	return ret;
}

ssize_t Dz1GasnSupport_asn_decode(str_t oidStr, void **dstptr, u8_t *srcbuf, size_t size, Dz1Asn1Codec codec, Dz1GasnMsgCodecApi table[],
								  Dz1GasnUnionNewFunc _new, Dz1CancelFunc _delAndSetNull, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	GAsnStructCaster *msg = NULL;
	ssize_t ret = 0;
	Dz1GasnMsgCodecApi *api = NULL;
	if (oidStr == NULL || dstptr == NULL || _new == NULL || _delAndSetNull == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if ((api = Dz1GasnMsgCodecApi_findByOIDStr(table, oidStr)) == NULL) ERR_SET_OUT_RET(errp, ENOSYS, -1);
	else if (((*dstptr) = msg = (GAsnStructCaster *)_new(api->present, NULL, errp)) == NULL) ERR_OUT_RET(errp, -1);
	else
	{
		pthread_cleanup_push(_delAndSetNull, (void *)dstptr);
		if (api->dec != NULL && (ret = api->dec(&msg->x.__ptr__, srcbuf, size, codec, errp)) < 0) ERR_OUT(errp);
		pthread_cleanup_pop(errp->code); // (_delAndSetNull, (void *)dst);
	}
	return ret;
}


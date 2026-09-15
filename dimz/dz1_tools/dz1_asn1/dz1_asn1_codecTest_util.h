#ifndef DZ1_ASN1_CODEC_TEST_UTIL_H_LOCAL
#define DZ1_ASN1_CODEC_TEST_UTIL_H_LOCAL

#include <dz1_gasn_support.h>
#include <dz1_asn1_codec.h>

typedef enum Dz1Asn1DecoderMode
{
	Dz1Asn1DecoderMode_chunk,
	Dz1Asn1DecoderMode_stream
} Dz1Asn1DecoderMode;
DZ1_CPPLINK_VAR Dz1Asn1DecoderMode test_dec_opt;

DZ1_CPPLINK_VAR bool_t				 flag_verbose;
DZ1_CPPLINK_VAR Dz1Asn1BerEncoderOpt test_enc_opt;

DZ1_CPPLINK_VAR u32_t	abstract_syntax_oid_arr[];
DZ1_CPPLINK_VAR u32_t	abstract_syntax_oid_arr_cnt;

DZ1_CPPLINK_VAR u32_t	transfer_syntax_oid_arr[];
DZ1_CPPLINK_VAR u32_t	transfer_syntax_oid_arr_cnt;

DZ1_CPPLINK_VAR s64_t	presentation_context_id;

DZ1_CPPLINK_VAR u8_t	str_text[];
DZ1_CPPLINK_VAR u32_t	str_text_sz;

///////////////////////////////////////////////////////////////////////////////
// Misc : GASN Cleanup
static __inline__ void _ptr_set_null_from_pprt(void *pptr)
{
	void **p = (void **)pptr;
	if (p != NULL) (*p) = NULL;
}
// Misc : GASN Cleanup
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Compare Utility
static __inline__ int _integer_cmp(INTEGER *a, Dz1Asn1Int *b)
{
	if (*a < *b) return -1;
	if (*a > *b) return 1;
	return 0;
}

static __inline__ int _string_cmp(ASNSTRING *a, Dz1Asn1OctetStr *b)
{
	if (a->nchar < (int)b->size) return -1;
	else if (a->nchar > (int)b->size) return 1;
	else if (a->nchar == 0) return 0;
	else return memcmp(a->asnstring, b->data, b->size);
}

static __inline__ int _octetstr_cmp(OCTETSTRING *a, Dz1Asn1OctetStr *b)
{
	if (a->numbits < b->size) return -1;
	else if (a->numbits > b->size) return 1;
	else if (a->numbits == 0) return 0;
	else return memcmp(a->data, b->data, b->size);
}

static __inline__ bool_t _oid_cmp(OBJECTIDENTIFIER *a, Dz1Asn1OID *b)
{
	if (a->numids < b->cnt) return -1;
	else if (a->numids > b->cnt) return 1;
	else if (a->numids == 0) return 0;
	else
	{
		u32_t i;
		for (i = 0; i < a->numids; i++)
		{
			if (a->subid[i] < b->data[i]) return -1;
			else if (a->subid[i] > b->data[i]) return 1;
		}
		return 0;
	}
}
// Compare Utility
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Useful Macro
#define GASN_DEC_DECLARE(struct_name, func_name)\
struct_name *func_name(Dz1Binary *bin, ASN1WorkSpace *ws, Dz1Error *err)\
{\
	DZ1_ERROR_SAFE_PTR(errp, err);\
	struct_name *ret = NULL;\
	if (ASN1_Save_WORKSPACE(ws, bin->data, bin->size) < 0) ERR_SET_OUT(errp, EFAULT);\
	else if ((ret = mpool_calloc(ws->Pmemory, sizeof(struct_name), 1)) == NULL) ERR_SET_OUT(errp, ENOMEM);\
	else\
	{\
		pthread_cleanup_push(_ptr_set_null_from_pprt, (void *)&ret);\
		if (ASN1_BER_Dec_##struct_name(ws, ret, bin->size, ASN1EXPL) < 0) ERR_SET_OUT(errp, EFAULT);\
		else Dz1Error_set(errp, 0);\
		pthread_cleanup_pop(errp->code);\
	}\
	return ret;\
}

#define GASN_ENC_DECLARE(struct_name, func_name)\
Dz1Binary *func_name(struct_name *v, Dz1Error *err)\
{\
	DZ1_ERROR_SAFE_PTR(errp, err);\
	Dz1Binary *ret = NULL;\
	int status = 0;\
	ASN1WorkSpace ws;\
	ASN1_INIT_WS_INFO(&ws);\
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);\
	if ((status = ASN1_BER_Enc_##struct_name(&ws, v, ASN1EXPL)) < 0) { Dz1Thread_printf(Dz1T("err_code = %d\n"), status); ERR_SET_OUT(errp, EFAULT); }\
	else if ((ret = Dz1Binary_new(ASN1WorkSpace_getEncodePtr(&ws), ASN1WorkSpace_getEncodedSize(&ws, Dz1Asn1Codec_ber), errp)) == NULL) ERR_OUT(errp);\
	else Dz1Error_set(errp, 0);\
	pthread_cleanup_pop(1);\
	return ret;\
}

#define GASN_DUMP_SIMPLE_DECLARE(struct_name, func_name, var_name)\
void func_name(void *ptr, int tab)\
{\
	struct_name *p = (struct_name *)ptr;\
	ASN1_Print_##struct_name(#var_name, p);\
}

#define GASN_DUMP_TAB_DECLARE(struct_name, func_name, var_name)\
void func_name(void *ptr, int tab)\
{\
	struct_name *p = (struct_name *)ptr;\
	ASN1_Print_##struct_name(#var_name, p, tab);\
}
// Useful Macro
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// GASN CHARACTERSTRING Utility
// GASN CHARACTERSTRING Utility
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Test Functions
DZ1_CPPLINK void	*dz1_asn1_ber_deocde(Dz1Asn1TypeDescr *descr, Dz1Binary *bin, void *param, Dz1Error *err);

typedef int			 (*data_compareF)(void *gasn_ptr, void *dz1asn_ptr);

typedef Dz1Binary	*(*gasn_ber_encF)(void *import_ptr, Dz1Error *err);
typedef void		*(*gasn_ber_decF)(Dz1Binary *bin, ASN1WorkSpace *ws, Dz1Error *err);

DZ1_CPPLINK bool_t	 dz1_asn1_ber_ingress_test(		Dz1Asn1TypeDescr *descr, void *gasn_src,	gasn_ber_encF gasn_enc, Dz1DumpFunc gasn_dump, data_compareF data_cmp,	Dz1Error *err);
DZ1_CPPLINK bool_t	 dz1_asn1_ber_egress_test(		Dz1Asn1TypeDescr *descr, void *dz1asn_src,	gasn_ber_decF gasn_dec, Dz1DumpFunc gasn_dump, data_compareF data_cmp,	Dz1Error *err);
DZ1_CPPLINK bool_t	 dz1_asn1_ber_self_test(		Dz1Asn1TypeDescr *descr, void *dz1asn_src,																			Dz1Error *err);
DZ1_CPPLINK bool_t	 dz1_asn1_ber_construct_test(	Dz1Asn1TypeDescr *descr, Dz1Binary *ber,	gasn_ber_decF gasn_dec, Dz1DumpFunc gasn_dump, data_compareF data_cmp,	Dz1Error *err);
// Test Functions
///////////////////////////////////////////////////////////////////////////////

DZ1_CPPLINK bool_t				 _init_gasn_charstring_identification(CHARACTERSTRING *dst, ASN1WorkSpace *ws, Dz1Asn1EmbPdvIDPresent present, Dz1Error *errp);

DZ1_CPPLINK Dz1Asn1CharStr		*_charstr_gen(Dz1Asn1EmbPdvIDPresent id_mode, Dz1Str str_value_descr, Dz1Error *errp);
DZ1_CPPLINK Dz1Asn1EmbPdv		*_pdv_gen(Dz1Asn1EmbPdvIDPresent id_mode, Dz1Str str_value_descr, Dz1Error *errp);

DZ1_CPPLINK Dz1Asn1External		*_external_gen(Dz1Str strOID, s64_t *indirect, str_t strDescr, Dz1Asn1ExternalEncodingPresent mode, u8_t *data, size_t sz, Dz1Error *err);
DZ1_CPPLINK Dz1Asn1InstanceOf	*_instance_of_gen(Dz1Str strOID, u8_t *data, size_t sz, Dz1Error *err);

#endif

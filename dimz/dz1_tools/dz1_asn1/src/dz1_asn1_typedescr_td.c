#include "dz1_asn1_types.h"
#include "dz1_asn1_typedescr.h"
#include "dz1_asn1_codec_ber.h"

static Dz1Asn1TypeDescrNameDecl(Dz1Asn1TagEOC);	// Dz1Asn1UTF8Str	__Dz1Asn1TagEOC_u8_ = { (u8_t *)"Dz1Asn1TagEOC", sizeof("Dz1Asn1TagEOC") - 1 }
static Dz1Asn1Tag dz1Asn1BerTagEOC = { Dz1Asn1TagClass_universal, Dz1Asn1TagFlag_primitive, 0 };
Dz1Asn1TypeDescr dz1Asn1TypeDescrEOC = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1TagEOC),
	&dz1Asn1BerTagEOC,							// tag
	NULL,										// no child
	NULL,										// no conformance
	NULL,										// wip_api
	Dz1Asn1BerDecoderDataCtx_enc_EOC,			// ber_enc
	Dz1Asn1BerDecoderDataCtx_dec_EOC,			// ber_dec
	NULL,										// finalize
	NULL										// user_api
};

static Dz1Asn1TypeDescrNameDecl(Dz1Asn1Any);	// Dz1Asn1UTF8Str	__Dz1Asn1Any_u8_ = { (u8_t *)"Dz1Asn1Any", sizeof("Dz1Asn1Any") - 1 }
Dz1Asn1TypeDescr dz1Asn1TypeDescrOpenType = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1Any),			// name
	NULL,										// tag			: OpenType is similar with CHOICE
	NULL,										// childs		: OpenType has no childs
	NULL,										// conformance	: OpenType has no conformance
	NULL,										// wip_api
	Dz1Asn1Any_enc_BER,							// ber_enc		: pass through data
	Dz1Asn1Any_dec_BER,							// ber_dec
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1Any),	// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1Any)			// user_api
};

static Dz1Asn1TypeDescrNameDecl(Dz1Asn1Bool);	// Dz1Asn1UTF8Str	__Dz1Asn1Bool_u8_ = { (u8_t *)"Dz1Asn1Bool", sizeof("Dz1Asn1Bool") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1Bool);		// Dz1Asn1Tag	berTagDz1Dz1Asn1Bool = BerTagValueDz1Dz1Asn1Bool
Dz1Asn1TypeDescr dz1Asn1TypeDescrBool = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1Bool),			// name
	&Dz1Asn1TagVarName(Dz1Asn1Bool),			// tag
	NULL,										// childs
	NULL,										// no conformance
	NULL,										// wip_api
	Dz1Asn1Bool_enc_BER,						// ber_enc
	Dz1Asn1Bool_dec_BER,						// ber_dec
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1Bool),	// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1Bool)			// wip_api
};

static Dz1Asn1TypeDescrNameDecl(Dz1Asn1Int);	// Dz1Asn1UTF8Str	__Dz1Asn1Int_u8_ = { (u8_t *)"Dz1Asn1Int", sizeof("Dz1Asn1Int") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1Int);		// Dz1Asn1Tag	berTagDz1Asn1Int = BerTagValueDz1Asn1Int
Dz1Asn1TypeDescr dz1Asn1TypeDescrInt = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1Int),			// name
	&Dz1Asn1TagVarName(Dz1Asn1Int),				// tag
	NULL,										// childs
	NULL,										// no constraints
	NULL,										// wip_api
	Dz1Asn1Int_enc_BER,							// ber_enc
	Dz1Asn1Int_dec_BER,							// ber_dec
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1Int),	// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1Int)			// user_api
};

static Dz1Asn1TypeDescrNameDecl(Dz1Asn1BitStr);	// Dz1Asn1UTF8Str	__Dz1Asn1BitStr_u8_ = { (u8_t *)"Dz1Asn1BitStr", sizeof("Dz1Asn1BitStr") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1BitStr);		// Dz1Asn1Tag	berTagDz1Asn1BitStr = BerTagValueDz1Asn1BitStr
Dz1Asn1TypeDescr dz1Asn1TypeDescrBitStr = 
{ 
	&Dz1Asn1TypeDescrName(Dz1Asn1BitStr),			// name
	&Dz1Asn1TagVarName(Dz1Asn1BitStr),				// tag
	NULL,											// childs
	NULL,											// conformance : no constraints
	NULL,											// wip_api
	Dz1Asn1BitStr_enc_BER,							// ber_enc
	Dz1Asn1BitStr_dec_BER,							// ber_dec
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1BitStr),	// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1BitStr)				// user_api
};

static Dz1Asn1TypeDescrNameDecl(Dz1Asn1OctetStr);	// Dz1Asn1UTF8Str	__Dz1Asn1OctetStr_u8_ = { (u8_t *)"Dz1Asn1OctetStr", sizeof("Dz1Asn1OctetStr") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1OctetStr);		// Dz1Asn1Tag	berTagDz1Asn1OctetStr = BerTagValueDz1Asn1OctetStr
Dz1Asn1TypeDescr dz1Asn1TypeDescrOctetStr = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1OctetStr),
	&Dz1Asn1TagVarName(Dz1Asn1OctetStr), 
	NULL, 
	NULL,											// no conformance
	NULL,											// wip_api
	Dz1Asn1OctetStr_enc_BER, 
	Dz1Asn1OctetStr_dec_BER, 
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1OctetStr),
	&Dz1Asn1TypeAPI_name(Dz1Asn1OctetStr)			// user_api
};

static Dz1Asn1TypeDescrNameDecl(Dz1Asn1Null);		// Dz1Asn1UTF8Str	__Dz1Asn1Null_u8_ = { (u8_t *)"Dz1Asn1Null", sizeof("Dz1Asn1Null") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1Null);			// Dz1Asn1Tag	berTagDz1Asn1Null = BerTagValueDz1Asn1Null
Dz1Asn1TypeDescr dz1Asn1TypeDescrNull = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1Null),
	&Dz1Asn1TagVarName(Dz1Asn1Null), 
	NULL, 
	NULL,											// no conformance
	NULL,											// wip_api
	Dz1Asn1Null_enc_BER, 
	Dz1Asn1Null_dec_BER, 
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1Null),		// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1Null)				// user_api
};

static Dz1Asn1TypeDescrNameDecl(Dz1Asn1OID);		// Dz1Asn1UTF8Str	__Dz1Asn1OID_u8_ = { (u8_t *)"Dz1Asn1OID", sizeof("Dz1Asn1OID") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1OID);			// Dz1Asn1Tag	berTagDz1Asn1OID = BerTagValueDz1Asn1OID
Dz1Asn1TypeDescr dz1Asn1TypeDescrOID = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1OID),
	&Dz1Asn1TagVarName(Dz1Asn1OID), 
	NULL,
	NULL,											// no conformance
	NULL,											// wip_api
	Dz1Asn1OID_enc_BER, 
	Dz1Asn1OID_dec_BER, 
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1OID),
	&Dz1Asn1TypeAPI_name(Dz1Asn1OID)				// user_api
};

///////////////////////////////////////////////////////////////////////////////
// ObjectDescriptor : [UNIVERSAL 7] IMPLICIT GraphicString
static Dz1Asn1TypeDescrNameDecl(Dz1Asn1ObjDescr);				// Dz1Asn1UTF8Str	__Dz1Asn1ObjDescr_u8_ = { (u8_t *)"Dz1Asn1ObjDescr", sizeof("Dz1Asn1ObjDescr") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1ObjDescr);					// Dz1Asn1Tag	berTagDz1Asn1ObjDescr = BerTagValueDz1Asn1ObjDescr
Dz1Asn1TypeDescr dz1Asn1TypeDescrObjDescr = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1ObjDescr),						// name
	&Dz1Asn1TagVarName(Dz1Asn1ObjDescr),						// tag
	NULL,														// childs
	NULL, // &Dz1Asn1TypeComformance_name(Dz1Asn1GraphicStr),	// conformance
	NULL,														// wip_api
	Dz1Asn1OctetStr_enc_BER, 
	Dz1Asn1OctetStr_dec_BER, 
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1OctetStr),				// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1ObjDescr)						// user api
};
// ObjectDescriptor
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1ExternalEncoding->x.single_ASN1_type
static bool_t Dz1Asn1ExternalEncoding_apply_single_ASN1_type(Dz1Asn1WipValue *parent_data, Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *my_data, u32_t order, Dz1Error *errp)
{	// decoding path, Parent UNION vs. Chile PRIMITIVE STRUCT
	Dz1Asn1WipCst *dst_seq = NULL;
	Dz1Asn1Custom *dst_sto = NULL;
	Dz1Asn1ExternalEncoding *dst = NULL;

	Dz1Asn1Any *temp = NULL;
	Dz1Asn1TypeAPI *user_api = NULL;

	if (parent_data == NULL || my_descr == NULL || my_data == NULL) ERR_SET_OUT(errp, EINVAL);
	// resolve destination
	else if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_sto = dst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = (Dz1Asn1ExternalEncoding *)dst_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	// check status
	else if (dst->present != Dz1Asn1ExternalEncodingPresent_max)
		ERR_SET_OUT(errp, EFAULT);
	// actual apply
	else if ((user_api = my_descr->user_api) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((temp = (Dz1Asn1Any *)user_api->gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1Any_delAndSetNull, (void *)&temp);
		if (my_descr->finalize((void *)temp, my_data, my_descr, errp) == FALSE) ERR_OUT(errp);
		else
		{
			dst->present = Dz1Asn1ExternalEncodingPresent_single_ASN1_type;

			dst->x.single_ASN1_type = temp;
			temp = NULL;

			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Asn1Any_delAndSetNull, (void *)&temp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
static Dz1Asn1GetChildF_ChoiceMembPtr(Dz1Asn1ExternalEncoding, single_ASN1_type)
// Dz1Asn1ExternalEncoding->x.single_ASN1_type
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1ExternalEncoding->x.octet_aligned
static bool_t Dz1Asn1ExternalEncoding_apply_octet_aligned(Dz1Asn1WipValue *parent_data, Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *my_data, u32_t order, Dz1Error *errp)
{	// Parent UNION vs. Chile PRIMITIVE STRUCT
	Dz1Asn1WipCst *dst_seq = NULL;
	Dz1Asn1Custom *dst_sto = NULL;
	Dz1Asn1ExternalEncoding *dst = NULL;

	Dz1Asn1OctetStr *temp = NULL;
	Dz1Asn1TypeAPI *user_api = NULL;

	if (parent_data == NULL || my_descr == NULL || my_data == NULL) ERR_SET_OUT(errp, EINVAL);
	// resolve destination
	else if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_sto = dst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = (Dz1Asn1ExternalEncoding *)dst_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	// check status
	else if (dst->present != Dz1Asn1ExternalEncodingPresent_max) ERR_SET_OUT(errp, EFAULT);
	// actual apply
	else if ((user_api = my_descr->user_api) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((temp = (Dz1Asn1OctetStr *)user_api->gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1Any_delAndSetNull, (void *)&temp);
		if (my_descr->finalize((void *)temp, my_data, my_descr, errp) == FALSE) ERR_OUT(errp);
		else
		{
			dst->present = Dz1Asn1ExternalEncodingPresent_octet_aligned;

			dst->x.octet_aligned = temp;
			temp = NULL;

			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Asn1Any_delAndSetNull, (void *)&temp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
static Dz1Asn1GetChildF_ChoiceMembPtr(Dz1Asn1ExternalEncoding, octet_aligned)
// Dz1Asn1ExternalEncoding->x.octet_aligned
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1ExternalEncoding->x.arbitrary
static bool_t Dz1Asn1ExternalEncoding_apply_arbitrary(Dz1Asn1WipValue *parent_data, Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *my_data, u32_t order, Dz1Error *errp)
{
	Dz1Asn1WipCst *dst_seq = NULL;
	Dz1Asn1Custom *dst_sto = NULL;
	Dz1Asn1ExternalEncoding *dst = NULL;

	Dz1Asn1BitStr *temp = NULL;
	Dz1Asn1TypeAPI *user_api = NULL;

	if (parent_data == NULL || my_descr == NULL || my_data == NULL) ERR_SET_OUT(errp, EINVAL);
	// resolve destination
	else if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_sto = dst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = (Dz1Asn1ExternalEncoding *)dst_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	// check status
	else if (dst->present != Dz1Asn1ExternalEncodingPresent_max) 
		ERR_SET_OUT(errp, EFAULT);
	// actual apply
	else if ((user_api = my_descr->user_api) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((temp = (Dz1Asn1BitStr *)user_api->gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1Any_delAndSetNull, (void *)&temp);
		if (my_descr->finalize((void *)temp, my_data, my_descr, errp) == FALSE) ERR_OUT(errp);
		else
		{
			dst->present = Dz1Asn1ExternalEncodingPresent_arbitrary;

			dst->x.arbitrary = temp;
			temp = NULL;

			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Asn1Any_delAndSetNull, (void *)&temp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
static Dz1Asn1GetChildF_ChoiceMembPtr(Dz1Asn1ExternalEncoding, arbitrary)
// Dz1Asn1ExternalEncoding->x.arbitrary
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1ExternalEncoding Childes
static Dz1Asn1TypeDescrChild Dz1Asn1ExternalEncodingArr[] =
{
	{	// single-ASN1-type
		{ Dz1Asn1TagClass_context_specific, Dz1Asn1TagFlag_construct,  0 },		// tag
		Dz1Asn1TagOpt_explicit,													// descr_tag
		&dz1Asn1TypeDescrOpenType,												// descr
		Dz1Asn1ExternalEncoding_apply_single_ASN1_type,							// apply
		Dz1Asn1GetChildF_func_name(Dz1Asn1ExternalEncoding, single_ASN1_type),	// getChild
		NULL																	// presence
	},
	{	// octet-aligned
		{ Dz1Asn1TagClass_context_specific, Dz1Asn1TagFlag_primitive, 1 },		// tag
		Dz1Asn1TagOpt_implicit,													// descr_tag
		&dz1Asn1TypeDescrOctetStr,												// descr
		Dz1Asn1ExternalEncoding_apply_octet_aligned,							// apply
		Dz1Asn1GetChildF_func_name(Dz1Asn1ExternalEncoding, octet_aligned),		// getChild
		NULL																	// presence
	},
	{	// arbitrary
		{ Dz1Asn1TagClass_context_specific, Dz1Asn1TagFlag_primitive, 2 },		// tag
		Dz1Asn1TagOpt_implicit,													// descr_tag
		&dz1Asn1TypeDescrBitStr,												// descr
		Dz1Asn1ExternalEncoding_apply_arbitrary,								// apply
		Dz1Asn1GetChildF_func_name(Dz1Asn1ExternalEncoding, arbitrary),			// getChild
		NULL																	// presence
	},
	Dz1Asn1TypeDescrChild_last
};
// Dz1Asn1ExternalEncoding Childes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1ExternalEncoding
static Dz1Asn1TypeDescrNameDecl(Dz1Asn1ExternalEncoding);
static Dz1Asn1DataTypeFinalizeF_declare(Dz1Asn1ExternalEncoding)
static Dz1Asn1TypeAPI_declare(Dz1Asn1ExternalEncoding);
static Dz1Asn1TypeDescr dz1Asn1TypeDescrExternalEncoding = 
{ 
	&Dz1Asn1TypeDescrName(Dz1Asn1ExternalEncoding),			// name
	NULL,													// tag : CHOICE
	Dz1Asn1ExternalEncodingArr,								// childes
	NULL,													// conformance
	&Dz1Asn1TypeAPI_name(Dz1Asn1ExternalEncoding),			// wip_api
	Dz1Asn1Choice_enc_BER,									// ber_enc
	Dz1Asn1Choice_dec_BER,									// ber_dec
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1ExternalEncoding),	// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1ExternalEncoding)			// user_api
};
// Dz1Asn1ExternalEncoding
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1External->direct_reference
static bool_t Dz1Asn1WipExtOrInst_external_apply_direct_reference(Dz1Asn1WipValue *parent_data, Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *my_data, u32_t order, Dz1Error *errp)
{	// decode path, Parent STRUCT vs. Child PRIMITIVE STRUCT
	Dz1Asn1WipCst *dst_seq = NULL;
	Dz1Asn1Custom *dst_sto = NULL;
	Dz1Asn1WipExtOrInst *dst_union = NULL;
	Dz1Asn1External *dst = NULL;

	Dz1Asn1OID *temp = NULL;
	Dz1Asn1TypeAPI *user_api = NULL;

	if (parent_data == NULL || my_descr == NULL || my_data == NULL) ERR_SET_OUT(errp, EINVAL);
	// resolve destination
	else if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_sto = dst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_union = (Dz1Asn1WipExtOrInst *)dst_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (dst_union->present != Dz1Asn1WipExtOrInstPresent_external) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = dst_union->x.external) == NULL) ERR_SET_OUT(errp, EFAULT);
	// check status
	else if (dst->direct_reference != NULL) ERR_SET_OUT(errp, EFAULT);
	// actual apply
	else if ((user_api = my_descr->user_api) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((temp = (Dz1Asn1OID *)user_api->gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1Any_delAndSetNull, (void *)&temp);
		if (my_descr->finalize((void *)temp, my_data, my_descr, errp) == FALSE) ERR_OUT(errp);
		else
		{
			dst->direct_reference = temp;
			temp = NULL;

			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Asn1Any_delAndSetNull, (void *)&temp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
static void *Dz1Asn1WipExtOrInst_external_get_direct_reference(void *_src, Dz1Asn1TypeDescr **opt_ret_descr)
{	// encode path, _src is Dz1Asn1External
	void *ret = NULL;
	Dz1Asn1External *p = (Dz1Asn1External *)_src;
	if (p != NULL) ret = (void *)p->direct_reference;
	return ret;
}
// Dz1Asn1External->direct_reference
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1External->indirect_reference
static bool_t Dz1Asn1WipExtOrInst_external_apply_indirect_reference(Dz1Asn1WipValue *parent_data, Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *my_data, u32_t order, Dz1Error *errp)
{	// decode path, Parent STRUCT vs. Child PRIMITIVE OPTIONAL
	Dz1Asn1WipCst *dst_seq = NULL;
	Dz1Asn1Custom *dst_sto = NULL;
	Dz1Asn1WipExtOrInst *dst_union = NULL;
	Dz1Asn1External *dst = NULL;

	Dz1Asn1Int *temp = NULL;	// Primitive OPTIONAL
	Dz1Asn1TypeAPI *user_api = NULL;

	if (parent_data == NULL || my_descr == NULL || my_data == NULL) ERR_SET_OUT(errp, EINVAL);
	// resolve destination
	else if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_sto = dst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_union = (Dz1Asn1WipExtOrInst *)dst_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (dst_union->present != Dz1Asn1WipExtOrInstPresent_external) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = dst_union->x.external) == NULL) ERR_SET_OUT(errp, EFAULT);
	// check status
	else if (dst->indirect_reference != NULL) ERR_SET_OUT(errp, EFAULT);
	// actual apply
	else if ((user_api = my_descr->user_api) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((temp = (Dz1Asn1Int *)user_api->gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1Int_delAndSetNull, (void *)&temp);

		if (my_descr->finalize(temp, my_data, my_descr, errp) == FALSE) ERR_OUT(errp);
		else
		{
			dst->indirect_reference = temp;
			temp = NULL;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(1); // (Dz1Asn1Int_delAndSetNull, (void *)&temp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
static void *Dz1Asn1WipExtOrInst_external_get_indirect_reference(void *_src, Dz1Asn1TypeDescr **opt_ret_descr)
{	// encode path, _src is Dz1Asn1External
	void *ret = NULL;
	Dz1Asn1External *p = (Dz1Asn1External *)_src;
	if (p != NULL) ret = (void *)p->indirect_reference;
	return ret;
}
// Dz1Asn1External->indirect_reference
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1External->data_value_descriptor
static bool_t Dz1Asn1WipExtOrInst_external_apply_data_value_descriptor(Dz1Asn1WipValue *parent_data, Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *my_data, u32_t order, Dz1Error *errp)
{	// decode path, Parent STRUCT vs. Child PRIMITIVE STRUCT
	Dz1Asn1WipCst *dst_seq = NULL;
	Dz1Asn1Custom *dst_sto = NULL;
	Dz1Asn1WipExtOrInst *dst_union = NULL;
	Dz1Asn1External *dst = NULL;

	Dz1Asn1ObjDescr *temp = NULL;
	Dz1Asn1TypeAPI *user_api = NULL;

	if (parent_data == NULL || my_descr == NULL || my_data == NULL) ERR_SET_OUT(errp, EINVAL);
	// resolve destination
	else if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_sto = dst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_union = (Dz1Asn1WipExtOrInst *)dst_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (dst_union->present != Dz1Asn1WipExtOrInstPresent_external) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = dst_union->x.external) == NULL) ERR_SET_OUT(errp, EFAULT);
	// check status
	else if (dst->data_value_descriptor != NULL) ERR_SET_OUT(errp, EFAULT);
	// actual apply
	else if ((user_api = my_descr->user_api) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((temp = (Dz1Asn1ObjDescr *)user_api->gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1Int_delAndSetNull, (void *)&temp);

		if (my_descr->finalize(temp, my_data, my_descr, errp) == FALSE) ERR_OUT(errp);
		else
		{
			dst->data_value_descriptor = temp;
			temp = NULL;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(1); // (Dz1Asn1Int_delAndSetNull, (void *)&temp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
static void *Dz1Asn1WipExtOrInst_external_get_data_value_descriptor(void *_src, Dz1Asn1TypeDescr **opt_ret_descr)
{	// encode path, _src is Dz1Asn1External
	void *ret = NULL;
	Dz1Asn1External *p = (Dz1Asn1External *)_src;
	if (p != NULL) ret = (void *)p->data_value_descriptor;
	return ret;
}
// Dz1Asn1External->data_value_descriptor
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1External->encoding
static bool_t Dz1Asn1WipExtOrInst_external_apply_encoding(Dz1Asn1WipValue *parent_data, Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *my_data, u32_t order, Dz1Error *errp)
{	// decode path, Parent STRUCT vs Child STRUCT
	Dz1Asn1WipCst *dst_seq = NULL;
	Dz1Asn1Custom *dst_sto = NULL;
	Dz1Asn1WipExtOrInst *dst_union = NULL;
	Dz1Asn1External *dst = NULL;

	if (parent_data == NULL || my_descr == NULL || my_data == NULL) ERR_SET_OUT(errp, EINVAL);
	// resolve destination
	else if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_sto = dst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_union = (Dz1Asn1WipExtOrInst *)dst_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (dst_union->present != Dz1Asn1WipExtOrInstPresent_external) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = dst_union->x.external) == NULL) ERR_SET_OUT(errp, EFAULT);
	// check status
	else if (dst->encoding != NULL) ERR_SET_OUT(errp, EFAULT);
	// actual apply
	else if (Dz1Asn1ApplyUtil_pointer_toss((void **)&dst->encoding, my_data, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
static void *Dz1Asn1WipExtOrInst_external_get_encoding(void *_src, Dz1Asn1TypeDescr **opt_ret_descr)
{	// encode path, _src is Dz1Asn1External
	void *ret = NULL;
	Dz1Asn1External *p = (Dz1Asn1External *)_src;
	if (p != NULL) ret = (void *)p->encoding;
	return ret;
}
// Dz1Asn1External->encoding
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1External Childes
static Dz1Asn1TypeDescrPresence _basic_optional = { Dz1Asn1TypeDescrPresencePresent_opt, { NULL } };
static Dz1Asn1TypeDescrChild dz1Asn1TypeDescrExternalArr[] =
{
	{	// direct-reference : OPTIONAL
		Dz1Asn1TagVOID,												// tag
		Dz1Asn1TagOpt_explicit,										// descr_tag
		&dz1Asn1TypeDescrOID,										// descr
		Dz1Asn1WipExtOrInst_external_apply_direct_reference,		// apply
		Dz1Asn1WipExtOrInst_external_get_direct_reference,			// get_child
		&dz1Asn1TypeDescrChildPresence_optional						// presence
	},
	{	// indirect-reference : OPTIONAL
		Dz1Asn1TagVOID,												// tag
		Dz1Asn1TagOpt_explicit,										// descr tag
		&dz1Asn1TypeDescrInt,										// descr
		Dz1Asn1WipExtOrInst_external_apply_indirect_reference,		// apply
		Dz1Asn1WipExtOrInst_external_get_indirect_reference,		// get_child
		&dz1Asn1TypeDescrChildPresence_optional						// presence
	},	
	{	// data-value-descriptor : OPTIONAL
		Dz1Asn1TagVOID,												// tag
		Dz1Asn1TagOpt_explicit,										// descr_tag
		&dz1Asn1TypeDescrObjDescr,									// descr
		Dz1Asn1WipExtOrInst_external_apply_data_value_descriptor,	// apply
		Dz1Asn1WipExtOrInst_external_get_data_value_descriptor,		// get_child
		&dz1Asn1TypeDescrChildPresence_optional						// presence
	},
	{	// encoding : MANDATORY
		Dz1Asn1TagVOID,												// tag
		Dz1Asn1TagOpt_explicit,										// descr_tag
		&dz1Asn1TypeDescrExternalEncoding,							// descr
		Dz1Asn1WipExtOrInst_external_apply_encoding,				// apply
		Dz1Asn1WipExtOrInst_external_get_encoding,					// get_child
		NULL														// presence
	},
	Dz1Asn1TypeDescrChild_last
};
// Dz1Asn1External Childes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1External
static Dz1Asn1TypeDescrNameDecl(Dz1Asn1External);
static Dz1Asn1TagVarDeclare(Dz1Asn1External);
static Dz1Asn1WipExtOrInst *_Dz1Asn1WipExtOrInst_genExternal(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1WipExtOrInst *ret = Dz1Asn1WipExtOrInst_new(Dz1Asn1WipExtOrInstPresent_external, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1WipExtOrInst_delAndSetNull, (void *)&ret);
		if ((ret->x.external = Dz1Asn1External_gen(errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1Asn1WipExtOrInst_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Asn1TypeAPI Dz1Asn1ExternalWipAPI =
{
	_Dz1Asn1WipExtOrInst_genExternal,				// gen
	Dz1Asn1WipExtOrInst_clone,						// clone
	Dz1Asn1WipExtOrInst_del,						// del
	Dz1Asn1WipExtOrInst_delAndSetNull,				// delAndSetNull
	Dz1Asn1WipExtOrInst_cmp,						// cmp

	Dz1Asn1WipExtOrInstA_dump,						// dunpA
	Dz1Asn1WipExtOrInstA_fdump,						// fdunpA
#ifndef UNIX_SYSTEM
	Dz1Asn1WipExtOrInstW_dump,						// dumpW
	Dz1Asn1WipExtOrInstW_fdump,						// fdumpW
#else
	NULL,											// dumpW
	NULL											// fdumpW
#endif
};

Dz1Asn1TypeDescr dz1Asn1TypeDescrExternal = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1External),			// name
	&Dz1Asn1TagVarName(Dz1Asn1External),			// tag
	dz1Asn1TypeDescrExternalArr,					// childs
	NULL,											// conformance
	&Dz1Asn1ExternalWipAPI,							// wip_api
	Dz1Asn1Sequence_enc_BER,						// ber_enc
	Dz1Asn1Sequence_dec_BER,						// ber_dec
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1External),	// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1External)			// user_api
};
// Dz1Asn1External
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1InstanceOf->type_id
static bool_t Dz1Asn1WipExtOrInst_instanceof_apply_type_id(Dz1Asn1WipValue *parent_data, Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *my_data, u32_t order, Dz1Error *errp)
{	// decode path. Parent STRUCT vs. Child PRIMITIVE STRUCT
	Dz1Asn1WipCst *dst_seq = NULL;
	Dz1Asn1Custom *dst_sto = NULL;
	Dz1Asn1WipExtOrInst *dst_union = NULL;
	Dz1Asn1InstanceOf *dst = NULL;

	Dz1Asn1OID *temp = NULL;
	Dz1Asn1TypeAPI *user_api = NULL;

	if (parent_data == NULL || my_descr == NULL || my_data == NULL) ERR_SET_OUT(errp, EINVAL);
	// resolve destination
	else if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_sto = dst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_union = (Dz1Asn1WipExtOrInst *)dst_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (dst_union->present != Dz1Asn1WipExtOrInstPresent_instance_of) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = dst_union->x.instance_of) == NULL) ERR_SET_OUT(errp, EFAULT);
	// check status
	else if (dst->type_id != NULL) ERR_SET_OUT(errp, EFAULT);
	// actual apply
	else if ((user_api = my_descr->user_api) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((temp = (Dz1Asn1OID *)user_api->gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1Any_delAndSetNull, (void *)&temp);
		if (my_descr->finalize((void *)temp, my_data, my_descr, errp) == FALSE) ERR_OUT(errp);
		else
		{
			dst->type_id = temp;
			temp = NULL;

			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Asn1Any_delAndSetNull, (void *)&temp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1Asn1GetChildF_SeqMembPtr(Dz1Asn1InstanceOf, type_id)
// Dz1Asn1InstanceOf->type_id
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1InstanceOf->value
static bool_t Dz1Asn1WipExtOrInst_instanceof_apply_value(Dz1Asn1WipValue *parent_data, Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *my_data, u32_t order, Dz1Error *errp)
{	// Parent STRUCT vs. Child PRIMITIVE STRUCT
	Dz1Asn1WipCst *dst_seq = NULL;
	Dz1Asn1Custom *dst_sto = NULL;
	Dz1Asn1WipExtOrInst *dst_union = NULL;
	Dz1Asn1InstanceOf *dst = NULL;

	Dz1Asn1Any *temp = NULL;
	Dz1Asn1TypeAPI *user_api = NULL;

	if (parent_data == NULL || my_descr == NULL || my_data == NULL) ERR_SET_OUT(errp, EINVAL);
	// resolve destination
	else if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_sto = dst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_union = (Dz1Asn1WipExtOrInst *)dst_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (dst_union->present != Dz1Asn1WipExtOrInstPresent_instance_of) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = dst_union->x.instance_of) == NULL) ERR_SET_OUT(errp, EFAULT);
	// check status
	else if (dst->value != NULL) ERR_SET_OUT(errp, EFAULT);
	// actual apply
	else if ((user_api = my_descr->user_api) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((temp = (Dz1Asn1Any *)user_api->gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1Any_delAndSetNull, (void *)&temp);
		if (my_descr->finalize((void *)temp, my_data, my_descr, errp) == FALSE) ERR_OUT(errp);
		else
		{
			dst->value = temp;
			temp = NULL;

			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Asn1Any_delAndSetNull, (void *)&temp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
static Dz1Asn1GetChildF_SeqMembPtr(Dz1Asn1InstanceOf, value)
// Dz1Asn1InstanceOf->value
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1InstanceOf Childes
static Dz1Asn1TypeDescrChild dz1Asn1TypeDescrInstanceOfArr[] =
{
	{	// type-id
		Dz1Asn1TagVOID,														// tag
		Dz1Asn1TagOpt_explicit,												// descr_tag
		&dz1Asn1TypeDescrOID,												// descr
		Dz1Asn1WipExtOrInst_instanceof_apply_type_id,						// apply
		Dz1Asn1GetChildF_func_name(Dz1Asn1InstanceOf, type_id),				// getChild
		NULL																// presence
	},
	{	// value
		{ Dz1Asn1TagClass_context_specific, Dz1Asn1TagFlag_variable,  0 },	// tag
		Dz1Asn1TagOpt_explicit,												// descr_tag
		&dz1Asn1TypeDescrOpenType,											// descr
		Dz1Asn1WipExtOrInst_instanceof_apply_value,							// apply
		Dz1Asn1GetChildF_func_name(Dz1Asn1InstanceOf, value),				// getChild
		NULL																// presence
	},	
	Dz1Asn1TypeDescrChild_last
};
// Dz1Asn1InstanceOf Childes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1InstanceOf
static Dz1Asn1TypeDescrNameDecl(Dz1Asn1InstanceOf);		// NAME
static Dz1Asn1TagVarDeclare(Dz1Asn1InstanceOf);			// TAG
static Dz1Asn1WipExtOrInst *_Dz1Asn1WipExtOrInst_genInstanceOf(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1WipExtOrInst *ret = Dz1Asn1WipExtOrInst_new(Dz1Asn1WipExtOrInstPresent_instance_of, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1WipExtOrInst_delAndSetNull, (void *)&ret);
		if ((ret->x.instance_of = Dz1Asn1InstanceOf_gen(errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1Asn1WipExtOrInst_delAndSetNull, (void *)&ret);
	}
	return ret;
}
static Dz1Asn1TypeAPI Dz1Asn1InstanceOfWipAPI =			// WIP API
{
 	_Dz1Asn1WipExtOrInst_genInstanceOf,					// alloc
 	Dz1Asn1WipExtOrInst_clone,							// clone
 	Dz1Asn1WipExtOrInst_del,							// del
 	Dz1Asn1WipExtOrInst_delAndSetNull,					// delAndSetNull
 	Dz1Asn1WipExtOrInst_cmp,							// cmp

	Dz1Asn1WipExtOrInstA_dump,							// dumpA
	Dz1Asn1WipExtOrInstA_fdump,							// fdumpA
#ifndef UNIX_SYSTEM
	Dz1Asn1WipExtOrInstW_dump,							// dumpW
	Dz1Asn1WipExtOrInstW_fdump,							// fdumpW
#else
	NULL,												// dumpW
	NULL												// fdumpW
#endif
};
Dz1Asn1TypeDescr dz1Asn1TypeDescrInstanceOf = 
{ 
	&Dz1Asn1TypeDescrName(Dz1Asn1InstanceOf),			// name
	&Dz1Asn1TagVarName(Dz1Asn1InstanceOf),				// tag
	dz1Asn1TypeDescrInstanceOfArr,						// childes
	NULL,												// conformance
	&Dz1Asn1InstanceOfWipAPI,							// wip_api
	Dz1Asn1Sequence_enc_BER,							// ber_enc
	Dz1Asn1Sequence_dec_BER,							// ber_dec
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1InstanceOf),	// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1InstanceOf)	// user_api
};
// Dz1Asn1InstanceOf
///////////////////////////////////////////////////////////////////////////////

static Dz1Asn1TypeDescrNameDecl(Dz1Asn1Real);			// Dz1Asn1UTF8Str	__Dz1Asn1Real_u8_ = { (u8_t *)"Dz1Asn1Real", sizeof("Dz1Asn1Real") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1Real);				// Dz1Asn1Tag	berTagDz1Asn1Real = BerTagValueDz1Asn1Real
Dz1Asn1TypeDescr dz1Asn1TypeDescrReal = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1Real),					// name
	&Dz1Asn1TagVarName(Dz1Asn1Real),					// tag
	NULL,												// childs
	NULL,												// no conformance
	NULL,												// wip_api
	Dz1Asn1Real_enc_BER,
	Dz1Asn1Real_dec_BER, 
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1Real),			// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1Real)					// user_api
};

static Dz1Asn1TypeDescrNameDecl(Dz1Asn1Enum);			// Dz1Asn1UTF8Str	__Dz1Asn1Enum_u8_ = { (u8_t *)"Dz1Asn1Enum", sizeof("Dz1Asn1Enum") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1Enum);				// Dz1Asn1Tag	berTagDz1Asn1Enum = BerTagValueDz1Asn1Enum
Dz1Asn1TypeDescr dz1Asn1TypeDescrEnum = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1Enum),					// name
	&Dz1Asn1TagVarName(Dz1Asn1Enum),					// tag
	NULL,												// no childs
	NULL,												// no conformance
	NULL,												// wip_api
	Dz1Asn1Int_enc_BER,
	Dz1Asn1Int_dec_BER, 
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1Enum),
	&Dz1Asn1TypeAPI_name(Dz1Asn1Enum)					// user_api
};

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdvSyntaxes->abstract
static bool_t Dz1Asn1EmbPdvSyntaxes_apply_abstract(Dz1Asn1WipValue *parent_data, Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *my_data, u32_t order, Dz1Error *errp)
{	// Parent STRUCT vs. Child PRIMITIVE STRUCT
	Dz1Asn1WipCst *dst_seq = NULL;
	Dz1Asn1Custom *dst_sto = NULL;

	Dz1Asn1EmbPdvSyntaxes *dst = NULL;

	Dz1Asn1OID *temp = NULL;	// destination's target type TEMP pointer(target is structure)
	Dz1Asn1TypeAPI *user_api = NULL;

	if (parent_data == NULL || my_descr == NULL || my_data == NULL) ERR_SET_OUT(errp, EINVAL);
	// resolve destination
	else if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_sto = dst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = (Dz1Asn1EmbPdvSyntaxes *)dst_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	// check status
	else if (dst->abstract != NULL) ERR_SET_OUT(errp, EFAULT);
	// actual apply
	else if ((user_api = my_descr->user_api) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((temp = (Dz1Asn1OID *)user_api->gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1OID_delAndSetNull, (void *)&temp);
		if (my_descr->finalize((void *)temp, my_data, my_descr, errp) == FALSE) ERR_OUT(errp);
		else
		{
			dst->abstract = temp;
			temp = NULL;

			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Asn1OID_delAndSetNull, (void *)&temp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
static Dz1Asn1GetChildF_SeqMembPtr(Dz1Asn1EmbPdvSyntaxes, abstract)
// Dz1Asn1EmbPdvSyntaxes->abstract
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdvSyntaxes->transfer
static bool_t Dz1Asn1EmbPdvSyntaxes_apply_transfer(Dz1Asn1WipValue *parent_data, Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *my_data, u32_t order, Dz1Error *errp)
{	// Parent STRUCT vs. Child PRIMITIVE STRUCT
	Dz1Asn1WipCst *dst_seq = NULL;
	Dz1Asn1Custom *dst_sto = NULL;

	Dz1Asn1EmbPdvSyntaxes *dst = NULL;

	Dz1Asn1OID *temp = NULL;	// destination's target type TEMP pointer(target is primitive optional)
	Dz1Asn1TypeAPI *user_api = NULL;

	if (parent_data == NULL || my_descr == NULL || my_data == NULL) ERR_SET_OUT(errp, EINVAL);
	// resolve destination
	else if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_sto = dst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = (Dz1Asn1EmbPdvSyntaxes *)dst_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	// check status
	else if (dst->transfer != NULL) ERR_SET_OUT(errp, EFAULT);	// target pointer check
	// actual apply
	else if ((user_api = my_descr->user_api) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((temp = (Dz1Asn1OID *)user_api->gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1OID_delAndSetNull, (void *)&temp);
		if (my_descr->finalize((void *)temp, my_data, my_descr, errp) == FALSE) ERR_OUT(errp);
		else
		{
			dst->transfer = temp;
			temp = NULL;

			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Asn1OID_delAndSetNull, (void *)&temp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
static Dz1Asn1GetChildF_SeqMembPtr(Dz1Asn1EmbPdvSyntaxes, transfer)
// Dz1Asn1EmbPdvSyntaxes->transfer
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdvSyntaxes Childes
static Dz1Asn1TypeDescrChild dz1Asn1TypeDz1Asn1EmbPdvSyntaxesArr[] =
{
	{	// abstract
		{ Dz1Asn1TagClass_context_specific, Dz1Asn1TagFlag_primitive, 0 },	// tag
		Dz1Asn1TagOpt_implicit,												// descr_tag
		&dz1Asn1TypeDescrOID,												// descr
		Dz1Asn1EmbPdvSyntaxes_apply_abstract,								// apply
		Dz1Asn1GetChildF_func_name(Dz1Asn1EmbPdvSyntaxes, abstract),		// getChild
		NULL																// presence : mandatory
	},
	{	// transfer
		{ Dz1Asn1TagClass_context_specific, Dz1Asn1TagFlag_primitive, 1 },	// tag
		Dz1Asn1TagOpt_implicit,												// descr_tag
		&dz1Asn1TypeDescrOID,												// descr
		Dz1Asn1EmbPdvSyntaxes_apply_transfer,								// apply
		Dz1Asn1GetChildF_func_name(Dz1Asn1EmbPdvSyntaxes, transfer),		// getChild
		NULL																// presence : mandatory
	},
	Dz1Asn1TypeDescrChild_last
};
// Dz1Asn1EmbPdvSyntaxes Childes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdvSyntaxes
static Dz1Asn1TypeDescrNameDecl(Dz1Asn1EmbPdvSyntaxes);						// NAME
static Dz1Asn1DataTypeFinalizeF_declare(Dz1Asn1EmbPdvSyntaxes)				// FINALIZE
static Dz1Asn1TypeAPI_declare(Dz1Asn1EmbPdvSyntaxes);						// USER API
static Dz1Asn1TypeDescr dz1Asn1TypeDz1Asn1EmbPdvSyntaxes = 
{ 
	&Dz1Asn1TypeDescrName(Dz1Asn1EmbPdvSyntaxes),							// name
	&dz1Asn1BerTagSequence,													// tag
	dz1Asn1TypeDz1Asn1EmbPdvSyntaxesArr,									// childs
	NULL,																	// conformance
	&Dz1Asn1TypeAPI_name(Dz1Asn1EmbPdvSyntaxes),							// wip_api
	Dz1Asn1Sequence_enc_BER,
	Dz1Asn1Sequence_dec_BER,
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1EmbPdvSyntaxes),					// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1EmbPdvSyntaxes)								// user_api
};
// Dz1Asn1EmbPdvSyntaxes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdvCtxNego->presentation_context_id
static bool_t Dz1Asn1EmbPdvCtxNego_apply_presentation_context_id(Dz1Asn1WipValue *parent_data, Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *my_data, u32_t order, Dz1Error *errp)
{	// Parent STRUCT vs. Child PRIMITIVE
	Dz1Asn1WipCst *dst_seq = NULL;
	Dz1Asn1Custom *dst_sto = NULL;

	Dz1Asn1EmbPdvCtxNego *dst = NULL;

	if (parent_data == NULL || my_descr == NULL || my_data == NULL) ERR_SET_OUT(errp, EINVAL);
	// resolve destination
	else if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_sto = dst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = (Dz1Asn1EmbPdvCtxNego *)dst_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	// check status : no need check to primitive variable
//	else if (dst->presentation_context_id != NULL) ERR_SET_OUT(errp, EFAULT);
	// actual apply
	else if (my_descr->finalize((void *)&dst->presentation_context_id, my_data, my_descr, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}
static Dz1Asn1GetChildF_SeqMembVar(Dz1Asn1EmbPdvCtxNego, presentation_context_id)
// Dz1Asn1EmbPdvCtxNego->presentation_context_id
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdvCtxNego->transfer_syntax
static bool_t Dz1Asn1EmbPdvCtxNego_apply_transfer_syntax(Dz1Asn1WipValue *parent_data, Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *my_data, u32_t order, Dz1Error *errp)
{	// Parent STRUCT vs. Child PRIMITIVE STRUCT
	Dz1Asn1WipCst *dst_seq = NULL;
	Dz1Asn1Custom *dst_sto = NULL;

	Dz1Asn1EmbPdvCtxNego *dst = NULL;

	Dz1Asn1OID *temp = NULL;				// destination's target type TEMP pointer(target is structure)
	Dz1Asn1TypeAPI *user_api = NULL;

	if (parent_data == NULL || my_descr == NULL || my_data == NULL) ERR_SET_OUT(errp, EINVAL);
	// resolve destination
	else if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_sto = dst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = (Dz1Asn1EmbPdvCtxNego *)dst_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	// check status
	else if (dst->transfer_syntax != NULL) ERR_SET_OUT(errp, EFAULT);	// target pointer check
	// actual apply
	else if ((user_api = my_descr->user_api) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((temp = (Dz1Asn1OID *)user_api->gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1OID_delAndSetNull, (void *)&temp);
		if (my_descr->finalize((void *)temp, my_data, my_descr, errp) == FALSE) ERR_OUT(errp);
		else
		{
			dst->transfer_syntax = temp;	// pointer toss
			temp = NULL;

			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Asn1OID_delAndSetNull, (void *)&temp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
static Dz1Asn1GetChildF_SeqMembPtr(Dz1Asn1EmbPdvCtxNego, transfer_syntax)
// Dz1Asn1EmbPdvCtxNego->transfer_syntax
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdvCtxNego Childes
static Dz1Asn1TypeDescrChild Dz1Asn1EmbPdvCtxNegoArr[] =
{
	{	// presentation-context-id
		{ Dz1Asn1TagClass_context_specific, Dz1Asn1TagFlag_primitive, 0 },			// tag
		Dz1Asn1TagOpt_implicit,														// descr_tag
		&dz1Asn1TypeDescrInt,														// descr
		Dz1Asn1EmbPdvCtxNego_apply_presentation_context_id,							// apply
		Dz1Asn1GetChildF_func_name(Dz1Asn1EmbPdvCtxNego, presentation_context_id),	// getChild
		NULL,																		// presence : mandatory
	},
	{	// transfer-syntax
		{ Dz1Asn1TagClass_context_specific, Dz1Asn1TagFlag_primitive, 1 },			// tag
		Dz1Asn1TagOpt_implicit,														// descr_tag
		&dz1Asn1TypeDescrOID,														// descr
		Dz1Asn1EmbPdvCtxNego_apply_transfer_syntax,									// apply
		Dz1Asn1GetChildF_func_name(Dz1Asn1EmbPdvCtxNego, transfer_syntax),			// getChild
		NULL,																		// presence : mandatory
	},
	Dz1Asn1TypeDescrChild_last
};
// Dz1Asn1EmbPdvCtxNego Childes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdvCtxNego
static Dz1Asn1TypeDescrNameDecl(Dz1Asn1EmbPdvCtxNego);			// NAME
static Dz1Asn1DataTypeFinalizeF_declare(Dz1Asn1EmbPdvCtxNego)	// FINALIZE
static Dz1Asn1TypeAPI_declare(Dz1Asn1EmbPdvCtxNego);			// API
static Dz1Asn1TypeDescr dz1Asn1TypeDescrDz1Asn1EmbPdvCtxNego = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1EmbPdvCtxNego),				// name
	&dz1Asn1BerTagSequence,										// tag
	Dz1Asn1EmbPdvCtxNegoArr,									// childs
	NULL,														// conformance
	&Dz1Asn1TypeAPI_name(Dz1Asn1EmbPdvCtxNego),					// wip_api
	Dz1Asn1Sequence_enc_BER,
	Dz1Asn1Sequence_dec_BER,
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1EmbPdvCtxNego),		// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1EmbPdvCtxNego)					// user_api
};
// Dz1Asn1EmbPdvCtxNego
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdvID->x.syntaxes
static bool_t Dz1Asn1EmbPdvID_apply_syntaxes(Dz1Asn1WipValue *parent_data, Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *my_data, u32_t order, Dz1Error *errp)
{	// Parent UNION vs. Child STRUCT
	Dz1Asn1WipCst *dst_seq = NULL;
	Dz1Asn1Custom *dst_sto = NULL;

	Dz1Asn1EmbPdvID *dst = NULL;

	if (parent_data == NULL || my_descr == NULL || my_data == NULL) ERR_SET_OUT(errp, EINVAL);
	// resolve destination
	else if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_sto = dst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = (Dz1Asn1EmbPdvID *)dst_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	// check status
	else if (dst->present != Dz1Asn1EmbPdvIDPresent_max) ERR_SET_OUT(errp, EFAULT);
	// actual apply
	else if (Dz1Asn1ApplyUtil_pointer_toss((void **)&dst->x.syntaxes, my_data, errp) == FALSE) ERR_OUT(errp);
	else
	{
		dst->present = Dz1Asn1EmbPdvIDPresent_syntaxes;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
static Dz1Asn1GetChildF_ChoiceMembPtr(Dz1Asn1EmbPdvID, syntaxes)
// Dz1Asn1EmbPdvID->x.syntaxes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdvID->x.syntax
static bool_t Dz1Asn1EmbPdvID_apply_syntax(Dz1Asn1WipValue *parent_data, Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *my_data, u32_t order, Dz1Error *errp)
{	// Parent UNION vs. Chile PRIMITIVE STRUCT
	Dz1Asn1WipCst *dst_seq = NULL;
	Dz1Asn1Custom *dst_sto = NULL;

	Dz1Asn1EmbPdvID *dst = NULL;

	Dz1Asn1OID *temp = NULL;
	Dz1Asn1TypeAPI *user_api = NULL;

	if (parent_data == NULL || my_descr == NULL || my_data == NULL) ERR_SET_OUT(errp, EINVAL);
	// resolve destination
	else if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_sto = dst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = (Dz1Asn1EmbPdvID *)dst_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	// check status
	else if (dst->present != Dz1Asn1EmbPdvIDPresent_max) ERR_SET_OUT(errp, EFAULT);
	// actual apply
	else if ((user_api = my_descr->user_api) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((temp = (Dz1Asn1OID *)user_api->gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1OID_delAndSetNull, (void *)&temp);
		if (my_descr->finalize((void *)temp, my_data, my_descr, errp) == FALSE) ERR_OUT(errp);
		else
		{
			dst->present = Dz1Asn1EmbPdvIDPresent_syntax;

			dst->x.syntax = temp;	// pointer toss
			temp = NULL;

			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Asn1OID_delAndSetNull, (void *)&temp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
static Dz1Asn1GetChildF_ChoiceMembPtr(Dz1Asn1EmbPdvID, syntax)
// Dz1Asn1EmbPdvID->x.syntax
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdvID->x.presentation_context_id
static bool_t Dz1Asn1EmbPdvID_apply_presentation_context_id(Dz1Asn1WipValue *parent_data, Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *my_data, u32_t order, Dz1Error *errp)
{	// Parent UNION vs. Child PRIMITIVE
	Dz1Asn1WipCst *dst_seq = NULL;
	Dz1Asn1Custom *dst_sto = NULL;
	Dz1Asn1EmbPdvID *dst = NULL;

	if (parent_data == NULL || my_descr == NULL || my_data == NULL) ERR_SET_OUT(errp, EINVAL);
	// resolve destination
	else if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_sto = dst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = (Dz1Asn1EmbPdvID *)dst_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	// check status
	else if (dst->present != Dz1Asn1EmbPdvIDPresent_max) ERR_SET_OUT(errp, EFAULT);
	// actual apply
	else if (my_descr->finalize((void *)&dst->x.presentation_context_id, my_data, my_descr, errp) == FALSE) ERR_OUT(errp);
	else
	{
		dst->present = Dz1Asn1EmbPdvIDPresent_presentation_context_id;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
static Dz1Asn1GetChildF_ChoiceMembVar(Dz1Asn1EmbPdvID, presentation_context_id)
// Dz1Asn1EmbPdvID->x.presentation_context_id
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdvID->x.context_negotiation
static bool_t Dz1Asn1EmbPdvID_apply_context_negotiation(Dz1Asn1WipValue *parent_data, Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *my_data, u32_t order, Dz1Error *errp)
{	// Parent UNION vs. Child STRUCT
	Dz1Asn1WipCst *dst_seq = NULL;
	Dz1Asn1Custom *dst_sto = NULL;
	Dz1Asn1EmbPdvID *dst = NULL;

	if (parent_data == NULL || my_descr == NULL || my_data == NULL) ERR_SET_OUT(errp, EINVAL);
	// resolve destination
	else if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_sto = dst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = (Dz1Asn1EmbPdvID *)dst_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	// check status
	else if (dst->present != Dz1Asn1EmbPdvIDPresent_max) ERR_SET_OUT(errp, EFAULT);
	// actual apply
	else if (Dz1Asn1ApplyUtil_pointer_toss((void **)&dst->x.context_negotiation, my_data, errp) == FALSE) ERR_OUT(errp);
	else
	{
		dst->present = Dz1Asn1EmbPdvIDPresent_context_negotiation;
		Dz1Error_set(errp, 0);
	}

	return errp->code == 0 ? TRUE : FALSE;
}
static Dz1Asn1GetChildF_ChoiceMembPtr(Dz1Asn1EmbPdvID, context_negotiation)
// Dz1Asn1EmbPdvID->x.context_negotiation
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdvID->x.transfer_syntax
static bool_t Dz1Asn1EmbPdvID_apply_transfer_syntax(Dz1Asn1WipValue *parent_data, Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *my_data, u32_t order, Dz1Error *errp)
{	// Parent UNION vs. Child PRIMITIVE STRUCT
	Dz1Asn1WipCst *dst_seq = NULL;
	Dz1Asn1Custom *dst_sto = NULL;

	Dz1Asn1EmbPdvID *dst = NULL;

	Dz1Asn1OID *temp = NULL;
	Dz1Asn1TypeAPI *user_api = NULL;

	if (parent_data == NULL || my_descr == NULL || my_data == NULL) ERR_SET_OUT(errp, EINVAL);
	// resolve destination
	else if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_sto = dst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = (Dz1Asn1EmbPdvID *)dst_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	// check status
	else if (dst->present != Dz1Asn1EmbPdvIDPresent_max) ERR_SET_OUT(errp, EFAULT);
	// actual apply
	else if ((user_api = my_descr->user_api) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((temp = (Dz1Asn1OID *)user_api->gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1OID_delAndSetNull, (void *)&temp);
		if (my_descr->finalize((void *)temp, my_data, my_descr, errp) == FALSE) ERR_OUT(errp);
		else
		{
			dst->present = Dz1Asn1EmbPdvIDPresent_transfer_syntax;
			dst->x.transfer_syntax = temp;	// pointer toss
			temp = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Asn1OID_delAndSetNull, (void *)&temp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
static Dz1Asn1GetChildF_ChoiceMembPtr(Dz1Asn1EmbPdvID, transfer_syntax)
// Dz1Asn1EmbPdvID->x.transfer_syntax
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdvID->x.fixed
static bool_t Dz1Asn1EmbPdvID_apply_fixed(Dz1Asn1WipValue *parent_data, Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *my_data, u32_t order, Dz1Error *errp)
{	// Parent UNION vs. Child PRIMITIVE
	Dz1Asn1WipCst *dst_seq = NULL;
	Dz1Asn1Custom *dst_sto = NULL;

	Dz1Asn1EmbPdvID *dst = NULL;

	if (parent_data == NULL || my_descr == NULL || my_data == NULL) ERR_SET_OUT(errp, EINVAL);
	// resolve destination
	else if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_sto = dst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = (Dz1Asn1EmbPdvID *)dst_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	// check status
	else if (dst->present != Dz1Asn1EmbPdvIDPresent_max) ERR_SET_OUT(errp, EFAULT);
	// actual apply
	else if (my_descr->finalize((void *)&dst->x.fixed, my_data, my_descr, errp) == FALSE) ERR_OUT(errp);
	else
	{
		dst->present = Dz1Asn1EmbPdvIDPresent_fixed;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
static Dz1Asn1GetChildF_ChoiceMembVar(Dz1Asn1EmbPdvID, fixed)
// Dz1Asn1EmbPdvID->x.fixed
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdvID Childes
static Dz1Asn1TypeDescrChild Dz1Asn1EmbPdvIDArr[] =
{
	{	// syntaxes
		{ Dz1Asn1TagClass_context_specific, Dz1Asn1TagFlag_construct, 0 },		// tag
		Dz1Asn1TagOpt_implicit,													// descr_tag
		&dz1Asn1TypeDz1Asn1EmbPdvSyntaxes,										// descr
		Dz1Asn1EmbPdvID_apply_syntaxes,											// apply
		Dz1Asn1GetChildF_func_name(Dz1Asn1EmbPdvID, syntaxes),					// getChild
		NULL																	// presence : member of CHOICE always mandatory
	},
	{	// syntax
		{ Dz1Asn1TagClass_context_specific, Dz1Asn1TagFlag_primitive, 1 },		// tag
		Dz1Asn1TagOpt_implicit,													// descr_tag
		&dz1Asn1TypeDescrOID,													// descr
		Dz1Asn1EmbPdvID_apply_syntax,											// apply
		Dz1Asn1GetChildF_func_name(Dz1Asn1EmbPdvID, syntax),					// getChild
		NULL																	// presence : member of CHOICE always mandatory
	},
	{	// presentation-context-id
		{ Dz1Asn1TagClass_context_specific, Dz1Asn1TagFlag_primitive, 2 },		// tag
		Dz1Asn1TagOpt_implicit,													// descr_tag
		&dz1Asn1TypeDescrInt,													// descr
		Dz1Asn1EmbPdvID_apply_presentation_context_id,							// apply
		Dz1Asn1GetChildF_func_name(Dz1Asn1EmbPdvID, presentation_context_id),	// getChild
		NULL																	// presence : member of CHOICE always mandatory
	},
	{	// context-negotiation
		{ Dz1Asn1TagClass_context_specific, Dz1Asn1TagFlag_construct, 3 },		// tag
		Dz1Asn1TagOpt_implicit,													// descr_tag
		&dz1Asn1TypeDescrDz1Asn1EmbPdvCtxNego,									// descr
		Dz1Asn1EmbPdvID_apply_context_negotiation,								// apply
		Dz1Asn1GetChildF_func_name(Dz1Asn1EmbPdvID, context_negotiation),		// getChild
		NULL																	// presence : member of CHOICE always mandatory
	},
	{	// transfer-syntax
		{ Dz1Asn1TagClass_context_specific, Dz1Asn1TagFlag_primitive, 4 },		// tag
		Dz1Asn1TagOpt_implicit,													// descr_tag
		&dz1Asn1TypeDescrOID,													// descr
		Dz1Asn1EmbPdvID_apply_transfer_syntax,									// apply
		Dz1Asn1GetChildF_func_name(Dz1Asn1EmbPdvID, transfer_syntax),			// getChild
		NULL																	// presence : member of CHOICE always mandatory
	},
	{	// fixed
		{ Dz1Asn1TagClass_context_specific, Dz1Asn1TagFlag_primitive, 5 },		// tag
		Dz1Asn1TagOpt_implicit,													// descr_tag
		&dz1Asn1TypeDescrNull,													// descr
		Dz1Asn1EmbPdvID_apply_fixed,											// apply
		Dz1Asn1GetChildF_func_name(Dz1Asn1EmbPdvID, fixed),						// getChild
		NULL																	// presence : member of CHOICE always mandatory
	},
	Dz1Asn1TypeDescrChild_last
};
// Dz1Asn1EmbPdvID Childes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdvID
static Dz1Asn1TypeDescrNameDecl(Dz1Asn1EmbPdvID);			// NAME
static Dz1Asn1DataTypeFinalizeF_declare(Dz1Asn1EmbPdvID)	// FINALIZE
static Dz1Asn1TypeAPI_declare(Dz1Asn1EmbPdvID);				// API
Dz1Asn1TypeDescr dz1Asn1TypeDescrDz1Asn1EmbPdvID = 
{ 
	&Dz1Asn1TypeDescrName(Dz1Asn1EmbPdvID),					// name
	NULL,													// tag : NULL mean it is CHOICE
	Dz1Asn1EmbPdvIDArr,										// childs
	NULL,													// conformance
	&Dz1Asn1TypeAPI_name(Dz1Asn1EmbPdvID),					// wip_api
	Dz1Asn1Choice_enc_BER,
	Dz1Asn1Choice_dec_BER,
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1EmbPdvID),			// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1EmbPdvID)					// user_api
};
// Dz1Asn1EmbPdvID
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdv->identifier
static bool_t Dz1Asn1EmbPdv_apply_identifier(Dz1Asn1WipValue *parent_data, Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *my_data, u32_t order, Dz1Error *errp)
{	// Parent STRUCT vs. Child STRUCT
	Dz1Asn1WipCst *dst_seq = NULL;
	Dz1Asn1Custom *dst_sto = NULL;

	Dz1Asn1EmbPdv *dst = NULL;

	if (parent_data == NULL || my_descr == NULL || my_data == NULL) ERR_SET_OUT(errp, EINVAL);
	// resolve destination
	if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_sto = dst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = (Dz1Asn1EmbPdv *)dst_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	// check status
	else if (dst->identifier != NULL) ERR_SET_OUT(errp, EFAULT);
	// actual apply
	else if (Dz1Asn1ApplyUtil_pointer_toss((void **)&dst->identifier, my_data, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
static Dz1Asn1GetChildF_SeqMembPtr(Dz1Asn1EmbPdv, identifier)
// Dz1Asn1EmbPdv->identifier
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdv->data_value_descriptor
static bool_t Dz1Asn1EmbPdv_apply_data_value_descriptor(Dz1Asn1WipValue *parent_data, Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *my_data, u32_t order, Dz1Error *errp)
{	// Parent STRUCT vs. Child PRIMITIVE STRUCT
	Dz1Asn1WipCst *dst_seq = NULL;
	Dz1Asn1Custom *dst_sto = NULL;
	Dz1Asn1EmbPdv *dst = NULL;

	Dz1Asn1ObjDescr *temp = NULL;
	Dz1Asn1TypeAPI *user_api = NULL;

	if (parent_data == NULL || my_descr == NULL || my_data == NULL) ERR_SET_OUT(errp, EINVAL);
	// resolve destination
	else if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_sto = dst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = (Dz1Asn1EmbPdv *)dst_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	// check status
	else if (dst->data_value_descriptor != NULL) ERR_SET_OUT(errp, EFAULT);
	// actual apply
	else if ((user_api = my_descr->user_api) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((temp = (Dz1Asn1ObjDescr *)user_api->gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1ObjDescr_delAndSetNull, (void *)&temp);

		if (my_descr->finalize((void *)temp, my_data, my_descr, errp) == FALSE) ERR_OUT(errp);
		else
		{
			dst->data_value_descriptor = temp;
			temp = NULL;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(1); // (Dz1Asn1ObjDescr_delAndSetNull, (void *)&temp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
static Dz1Asn1GetChildF_SeqMembPtr(Dz1Asn1EmbPdv, data_value_descriptor)
// Dz1Asn1EmbPdv->data_value_descriptor
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdv->data_value
static bool_t Dz1Asn1EmbPdv_apply_data_value(Dz1Asn1WipValue *parent_data, Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *my_data, u32_t order, Dz1Error *errp)
{	// Parent STRUCT vs. Child PRIMITIVE STRUCT
	Dz1Asn1WipCst *dst_seq = NULL;
	Dz1Asn1Custom *dst_sto = NULL;
	Dz1Asn1EmbPdv *dst = NULL;

	Dz1Asn1OctetStr *temp = NULL;
	Dz1Asn1TypeAPI *user_api = NULL;

	if (parent_data == NULL || my_descr == NULL || my_data == NULL) ERR_SET_OUT(errp, EINVAL);
	// resolve destination
	if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_sto = dst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = (Dz1Asn1EmbPdv *)dst_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	// check status
	else if (dst->data_value != NULL) ERR_SET_OUT(errp, EFAULT);
	// actual apply
	else if ((user_api = my_descr->user_api) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((temp = (Dz1Asn1OctetStr *)user_api->gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1OctetStr_delAndSetNull, (void *)&temp);

		if (my_descr->finalize((void *)temp, my_data, my_descr, errp) == FALSE) ERR_OUT(errp);
		else
		{
			dst->data_value = temp;
			temp = NULL;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(1); // (Dz1Asn1OctetStr_delAndSetNull, (void *)&temp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
static Dz1Asn1GetChildF_SeqMembPtr(Dz1Asn1EmbPdv, data_value)
// Dz1Asn1EmbPdv->data_value
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdv Childes
/*
SEQUENCE
{
	identification				[0]		CHOICE	{ ... }
	data-value-descriptor		[1]		ObjectDescriptor  OPTIONAL,
	data-value					[2]		OCTET STRING
}
(WITH COMPONENTS {
	... ,
	data-value-descriptor  ABSENT
})
*/
static Dz1Asn1TypeDescrPresence Dz1Asn1EmbPdv_presence_data_value_descriptor = { Dz1Asn1TypeDescrPresencePresent_opt, { NULL } };
static Dz1Asn1TypeDescrChild Dz1Asn1EmbPdvArr[] =
{
	{	// identification
		{ Dz1Asn1TagClass_context_specific, Dz1Asn1TagFlag_construct, 0 },	// tag
		Dz1Asn1TagOpt_explicit,												// descr_tag : choice child is always EXPLICIT
		&dz1Asn1TypeDescrDz1Asn1EmbPdvID,									// descr
		Dz1Asn1EmbPdv_apply_identifier,										// apply
		Dz1Asn1GetChildF_func_name(Dz1Asn1EmbPdv, identifier),				// getChild
		NULL																// presence : mandatory
	},
	{	// data-value-descriptor
		{ Dz1Asn1TagClass_context_specific, Dz1Asn1TagFlag_variable,  1 },	// tag
		Dz1Asn1TagOpt_implicit,												// descr_tag : AUTOMATIC -> IMPLICIT
		&dz1Asn1TypeDescrObjDescr,											// descr
		Dz1Asn1EmbPdv_apply_data_value_descriptor,							// apply
		Dz1Asn1GetChildF_func_name(Dz1Asn1EmbPdv, data_value_descriptor),	// getChild
		&Dz1Asn1EmbPdv_presence_data_value_descriptor						// presence : OPTIONAL
	},
	{	// data-value
		{ Dz1Asn1TagClass_context_specific, Dz1Asn1TagFlag_variable,  2 },	// tag
		Dz1Asn1TagOpt_implicit,												// descr_tag : AUTOMATIC -> IMPLICIT
		&dz1Asn1TypeDescrOctetStr,											// descr
		Dz1Asn1EmbPdv_apply_data_value,										// apply
		Dz1Asn1GetChildF_func_name(Dz1Asn1EmbPdv, data_value),				// getChild
		NULL																// mandatory
	},
	Dz1Asn1TypeDescrChild_last
};
// Dz1Asn1EmbPdv Childes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdv Conformance
static Dz1Asn1ConstructChildConstraint dz1Asn1EmbPdv_constraintArr[] =
{
	{ &dz1Asn1TypeDescrObjDescr, Dz1Asn1EmbPdv_get_data_value_descriptor, NULL, Dz1Asn1ConstructChildPresence_abssent }
};

static Dz1Asn1ConstructConstraintEntry dz1Asn1EmbPdv_constraint =
{
	dz1Asn1EmbPdv_constraintArr,
	sizeof(dz1Asn1EmbPdv_constraintArr) / sizeof(Dz1Asn1ConstructChildConstraint)
};

static Dz1Asn1ConstructConstraintTreeNode dz1Asn1EmbPdv_inner_subtype = { Dz1Asn1ConstructConstraintTreeNodePresent_constraints, { &dz1Asn1EmbPdv_constraint } };

/*
typedef struct Dz1Asn1Constraint
{
	void                               *value;
	Dz1Asn1MetaDataRangeInfo           *i_ranges;
	Dz1Asn1MetaDataRealRangeInfo       *f_ranges;
	Dz1Asn1MetaDataRange               *size;
	struct Dz1Asn1TypeDescr            *type_of_any;
	struct Dz1Asn1Constraint           *component;
	Dz1Asn1ConstructConstraintTreeNode *components;
	Dz1Asn1KnownMultiplerConstraints   *str_conf;
} Dz1Asn1Constraint;
*/
static Dz1Asn1Constraint dz1Asn1EmbPdvConstraints =
{
	NULL,								// value
	NULL,								// i_ranges
	NULL,								// f_rances
	NULL,								// size
	NULL,								// type of ANY
	NULL,								// component
	&dz1Asn1EmbPdv_inner_subtype,		// components
	NULL								// str_conf
	// Property setting -> TBD
	// Duration range -> TBD
	// Time point range -> TBD
	// Recurrence range -> TBD
};

static Dz1Asn1TypeComformance Dz1Asn1EmbPdvConformance =
{
	&dz1Asn1EmbPdvConstraints,
	Dz1Asn1Sequence_conformance
};
// Conformance
///////////////////////////////////////////////////////////////////////////////

static Dz1Asn1TypeDescrNameDecl(Dz1Asn1EmbPdv);		// NAME
static Dz1Asn1TagVarDeclare(Dz1Asn1EmbPdv);			// TAG

Dz1Asn1TypeDescr dz1Asn1TypeDescrEmbPdv = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1EmbPdv),			// name
	&Dz1Asn1TagVarName(Dz1Asn1EmbPdv),				// tag
	Dz1Asn1EmbPdvArr,								// childes
	&Dz1Asn1EmbPdvConformance,						// conformance
	&Dz1Asn1TypeAPI_name(Dz1Asn1EmbPdv),			// wip_api
	Dz1Asn1Sequence_enc_BER,						// ber_enc
	Dz1Asn1Sequence_dec_BER,						// ber_dec
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1EmbPdv),	// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1EmbPdv)				// user_api
};
// Dz1Asn1EmbPdv
///////////////////////////////////////////////////////////////////////////////

static Dz1Asn1TypeDescrNameDecl(Dz1Asn1UTF8Str);	// Dz1Asn1UTF8Str	__Dz1Asn1UTF8Str_u8_ = { (u8_t *)"Dz1Asn1UTF8Str", sizeof("Dz1Asn1UTF8Str") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1UTF8Str);		// Dz1Asn1Tag	berTagDz1Asn1UTF8Str = BerTagValueDz1Asn1UTF8Str
Dz1Asn1TypeDescr dz1Asn1TypeDescrUTF8Str = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1UTF8Str),			// name
	&Dz1Asn1TagVarName(Dz1Asn1UTF8Str),				// tag
	NULL,											// childs
	NULL,											// XXX : no conformance		-> Value Range
	NULL,											// wip_api
	Dz1Asn1OctetStr_enc_BER, 
	Dz1Asn1OctetStr_dec_BER, 
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1OctetStr),	// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1UTF8Str)			// user api
};

static Dz1Asn1TypeDescrNameDecl(Dz1Asn1RelOID);		// Dz1Asn1UTF8Str	__Dz1Asn1RelOID_u8_ = { (u8_t *)"Dz1Asn1RelOID", sizeof("Dz1Asn1RelOID") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1RelOID);			// Dz1Asn1Tag	berTagDz1Asn1RelOID = BerTagValueDz1Asn1RelOID
Dz1Asn1TypeDescr dz1Asn1TypeDescrRelOID = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1RelOID),			// name
	&Dz1Asn1TagVarName(Dz1Asn1RelOID),				// tag
	NULL,											// childs
	NULL,											// no conformance
	NULL,											// wip_api
	Dz1Asn1RelOID_enc_BER,
	Dz1Asn1RelOID_dec_BER, 
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1OID),		// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1OID)				// user_api
};

static Dz1Asn1TypeDescrNameDecl(Dz1Asn1Time);		// Dz1Asn1UTF8Str	__Dz1Asn1Time_u8_ = { (u8_t *)"Dz1Asn1Time", sizeof("Dz1Asn1Time") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1Time);			// Dz1Asn1Tag	berTagDz1Asn1Time = BerTagValueDz1Asn1Time
Dz1Asn1TypeDescr dz1Asn1TypeDescrTime = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1Time),				// name
	&Dz1Asn1TagVarName(Dz1Asn1Time),				// tag
	NULL,											// childs
	NULL,											// XXX : no conformance
	NULL,											// wip_api
	Dz1Asn1PrimitiveStr_enc_BER, 
	Dz1Asn1PrimitiveStr_dec_BER, 
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1OctetStr),	// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1UTF8Str)			// user api
};

// Known Multiplier String
static Dz1Asn1TypeDescrNameDecl(Dz1Asn1DigitStr);		// Dz1Asn1UTF8Str	__Dz1Asn1DigitStr_u8_ = { (u8_t *)"Dz1Asn1DigitStr", sizeof("Dz1Asn1DigitStr") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1DigitStr);			// Dz1Asn1Tag	berTagDz1Asn1DigitStr = BerTagValueDz1Asn1DigitStr
static_Dz1Asn1TypeComformance_declare(Dz1Asn1DigitStr);	// static Dz1Asn1TypeComformance dz1Asn1TypeComformanceDz1Asn1DigitStr
Dz1Asn1TypeDescr dz1Asn1TypeDescrDigitStr = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1DigitStr),				// name
	&Dz1Asn1TagVarName(Dz1Asn1DigitStr),				// tag
	NULL,												// childs
	&Dz1Asn1TypeComformance_name(Dz1Asn1DigitStr),		// conformance
	NULL,												// wip_api
	Dz1Asn1OctetStr_enc_BER, 
	Dz1Asn1OctetStr_dec_BER, 
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1OctetStr),		// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1DigitStr)				// user api
};

// Known Multiplier String
static Dz1Asn1TypeDescrNameDecl(Dz1Asn1PrintStr);		// Dz1Asn1UTF8Str	__Dz1Asn1PrintStr_u8_ = { (u8_t *)"Dz1Asn1PrintStr", sizeof("Dz1Asn1PrintStr") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1PrintStr);			// Dz1Asn1Tag	berTagDz1Asn1PrintStr = BerTagValueDz1Asn1PrintStr
static_Dz1Asn1TypeComformance_declare(Dz1Asn1PrintStr);	// static Dz1Asn1TypeComformance dz1Asn1TypeComformanceDz1Asn1PrintStr
Dz1Asn1TypeDescr dz1Asn1TypeDescrPrintStr = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1PrintStr),				// tag
	&Dz1Asn1TagVarName(Dz1Asn1PrintStr),				// name
	NULL,												// childs
	&Dz1Asn1TypeComformance_name(Dz1Asn1PrintStr),		// conformance
	NULL,												// wip_api
	Dz1Asn1OctetStr_enc_BER, 
	Dz1Asn1OctetStr_dec_BER, 
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1OctetStr),		// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1PrintStr)				// user api
};

// Unknown Multiplier String
static Dz1Asn1TypeDescrNameDecl(Dz1Asn1TeletexStr);			// Dz1Asn1UTF8Str	__Dz1Asn1TeletexStr_u8_ = { (u8_t *)"Dz1Asn1TeletexStr", sizeof("Dz1Asn1TeletexStr") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1TeletexStr);				// Dz1Asn1Tag	berTagDz1Asn1TeletexStr = BerTagValueDz1Asn1TeletexStr
static_Dz1Asn1TypeComformance_declare(Dz1Asn1TeletexStr);	// static Dz1Asn1TypeComformance dz1Asn1TypeComformanceDz1Asn1TeletexStr
Dz1Asn1TypeDescr dz1Asn1TypeDescrTeletexStr = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1TeletexStr),				// name
	&Dz1Asn1TagVarName(Dz1Asn1TeletexStr),					// tag
	NULL,													// childs
	&Dz1Asn1TypeComformance_name(Dz1Asn1TeletexStr),		// conformance
	NULL,													// wip_api
	Dz1Asn1OctetStr_enc_BER, 
	Dz1Asn1OctetStr_dec_BER, 
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1OctetStr),			// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1TeletexStr)					// user api
};

// Unknown Multiplier String
static Dz1Asn1TypeDescrNameDecl(Dz1Asn1VideotexStr);			// Dz1Asn1UTF8Str	__Dz1Asn1VideotexStr_u8_ = { (u8_t *)"Dz1Asn1VideotexStr", sizeof("Dz1Asn1VideotexStr") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1VideotexStr);				// Dz1Asn1Tag	berTagDz1Asn1VideotexStr = BerTagValueDz1Asn1VideotexStr
Dz1Asn1TypeDescr dz1Asn1TypeDescrVideotexStr = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1VideotexStr),					// name
	&Dz1Asn1TagVarName(Dz1Asn1VideotexStr),						// tag
	NULL,														// childs
	NULL,//	&Dz1Asn1TypeComformance_name(Dz1Asn1VideotexStr),	// conformance
	NULL,														// wip_api
	Dz1Asn1OctetStr_enc_BER, 
	Dz1Asn1OctetStr_dec_BER, 
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1OctetStr),				// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1VideotexStr)					// user api
};

// Known Multiplier String
static Dz1Asn1TypeDescrNameDecl(Dz1Asn1IA5Str);					// Dz1Asn1UTF8Str	__Dz1Asn1IA5Str_u8_ = { (u8_t *)"Dz1Asn1IA5Str", sizeof("Dz1Asn1IA5Str") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1IA5Str);						// Dz1Asn1Tag	berTagDz1Asn1IA5Str = BerTagValueDz1Asn1IA5Str
static_Dz1Asn1TypeComformance_declare(Dz1Asn1IA5Str);			// static Dz1Asn1TypeComformance dz1Asn1TypeComformanceDz1Asn1IA5Str
Dz1Asn1TypeDescr dz1Asn1TypeDescrIA5Str = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1IA5Str),						// name
	&Dz1Asn1TagVarName(Dz1Asn1IA5Str),							// tag
	NULL,														// childs
	&Dz1Asn1TypeComformance_name(Dz1Asn1IA5Str),				// conformance
	NULL,														// wip_api
	Dz1Asn1OctetStr_enc_BER, 
	Dz1Asn1OctetStr_dec_BER, 
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1OctetStr),				// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1IA5Str)							// user api
};

static Dz1Asn1TypeDescrNameDecl(Dz1Asn1UTCTime);				// Dz1Asn1UTF8Str	__###_u8_ = { (u8_t *)"###", sizeof("###") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1UTCTime);					// Dz1Asn1Tag	berTag### = BerTagValue###
Dz1Asn1TypeDescr dz1Asn1TypeDescrUTCTime = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1UTCTime),						// name
	&Dz1Asn1TagVarName(Dz1Asn1UTCTime),							// tag
	NULL,														// childs
	NULL,														// XXX : no conformance
	NULL,														// wip_api
	Dz1Asn1OctetStr_enc_BER, 
	Dz1Asn1OctetStr_dec_BER, 
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1OctetStr),				// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1UTCTime)						// user api
};

static Dz1Asn1TypeDescrNameDecl(Dz1Asn1GeneralTime);			// Dz1Asn1UTF8Str	__###_u8_ = { (u8_t *)"###", sizeof("###") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1GeneralTime);				// Dz1Asn1Tag	berTag### = BerTagValue###
Dz1Asn1TypeDescr dz1Asn1TypeDescrGeneralTime = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1GeneralTime),					// tag
	&Dz1Asn1TagVarName(Dz1Asn1GeneralTime),						// name
	NULL,														// childs
	NULL,														// XXX : no conformance
	NULL,														// wip_api
	Dz1Asn1OctetStr_enc_BER, 
	Dz1Asn1OctetStr_dec_BER, 
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1OctetStr),				// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1GeneralTime)					// user api
};

// Unknown Multiplier String
static Dz1Asn1TypeDescrNameDecl(Dz1Asn1GraphicStr);				// Dz1Asn1UTF8Str	__Dz1Asn1GraphicStr_u8_ = { (u8_t *)"Dz1Asn1GraphicStr", sizeof("Dz1Asn1GraphicStr") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1GraphicStr);					// Dz1Asn1Tag	berTagDz1Asn1GraphicStr = BerTagValueDz1Asn1GraphicStr
Dz1Asn1TypeDescr dz1Asn1TypeDescrGraphicStr = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1GraphicStr),					// name
	&Dz1Asn1TagVarName(Dz1Asn1GraphicStr),						// tag
	NULL,														// childs
	NULL, // &Dz1Asn1TypeComformance_name(Dz1Asn1GraphicStr),	// conformance
	NULL,														// wip_api
	Dz1Asn1OctetStr_enc_BER, 
	Dz1Asn1OctetStr_dec_BER, 
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1OctetStr),				// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1GraphicStr)						// user api
};


// Known Multiplier String
static Dz1Asn1TypeDescrNameDecl(Dz1Asn1VisibleStr);				// Dz1Asn1UTF8Str	__Dz1Asn1VisibleStr_u8_ = { (u8_t *)"Dz1Asn1VisibleStr", sizeof("Dz1Asn1VisibleStr") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1VisibleStr);					// Dz1Asn1Tag	berTagDz1Asn1VisibleStr = BerTagValueDz1Asn1VisibleStr
static_Dz1Asn1TypeComformance_declare(Dz1Asn1VisibleStr);		// static Dz1Asn1TypeComformance dz1Asn1TypeComformanceDz1Asn1VisibleStr
Dz1Asn1TypeDescr dz1Asn1TypeDescrVisibleStr = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1VisibleStr),					// name
	&Dz1Asn1TagVarName(Dz1Asn1VisibleStr),						// tag
	NULL,														// childs
	&Dz1Asn1TypeComformance_name(Dz1Asn1VisibleStr),			// conformance
	NULL,														// wip_api
	Dz1Asn1OctetStr_enc_BER, 
	Dz1Asn1OctetStr_dec_BER, 
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1OctetStr),				// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1VisibleStr)						// user api
};

// Unknown Multiplier String
static Dz1Asn1TypeDescrNameDecl(Dz1Asn1GeneralStr);				// Dz1Asn1UTF8Str	__Dz1Asn1GeneralStr_u8_ = { (u8_t *)"Dz1Asn1GeneralStr", sizeof("Dz1Asn1GeneralStr") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1GeneralStr);					// Dz1Asn1Tag	berTagDz1Asn1GeneralStr = BerTagValueDz1Asn1GeneralStr
Dz1Asn1TypeDescr dz1Asn1TypeDescrGeneralStr = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1GeneralStr),					// name
	&Dz1Asn1TagVarName(Dz1Asn1GeneralStr),						// tag
	NULL,														// childs
	NULL, // &Dz1Asn1TypeComformance_name(Dz1Asn1GeneralStr),	// conformance
	NULL,														// wip_api
	Dz1Asn1OctetStr_enc_BER, 
	Dz1Asn1OctetStr_dec_BER, 
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1OctetStr),				// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1GeneralStr)						// user api
};

// Known Multiplier UNICODE String
static Dz1Asn1TypeDescrNameDecl(Dz1Asn1UniversalStr);			// Dz1Asn1UTF8Str	__Dz1Asn1UniversalStr_u8_ = { (u8_t *)"Dz1Asn1UniversalStr", sizeof("Dz1Asn1UniversalStr") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1UniversalStr);				// Dz1Asn1Tag	berTagDz1Asn1UniversalStr = BerTagValueDz1Asn1UniversalStr
Dz1Asn1TypeDescr dz1Asn1TypeDescrUniversalStr = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1UniversalStr),					// name
	&Dz1Asn1TagVarName(Dz1Asn1UniversalStr),					// tag
	NULL,														// childs
	NULL,														// XXX : no conformance		-> Value Range
	NULL,														// wip_api
	Dz1Asn1OctetStr_enc_BER, 
	Dz1Asn1OctetStr_dec_BER, 
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1UniversalStr),			// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1UniversalStr)					// user api
};

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1CharStr->identifier
static bool_t Dz1Asn1CharStr_apply_identification(Dz1Asn1WipValue *parent_data, struct Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *my_data, u32_t order, Dz1Error *errp)
{	// Parent STRUCT vs. Child STRUCT
	Dz1Asn1WipCst *dst_seq = NULL;
	Dz1Asn1Custom *dst_sto = NULL;

	Dz1Asn1CharStr *dst = NULL;

	if (parent_data == NULL || my_descr == NULL || my_data == NULL) ERR_SET_OUT(errp, EINVAL);
	// resolve destination : destination is SEQUENCE
	else if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_sto = dst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = (Dz1Asn1CharStr *)dst_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	// check status
	else if (dst->identifier != NULL) ERR_SET_OUT(errp, EFAULT);
	// actual apply
	else if (Dz1Asn1ApplyUtil_pointer_toss((void **)&dst->identifier, my_data, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
static Dz1Asn1GetChildF_SeqMembPtr(Dz1Asn1CharStr, identifier)
// Dz1Asn1CharStr->identifier
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1CharStr->str_value_descriptor
static bool_t Dz1Asn1CharStr_apply_str_value_descriptor(Dz1Asn1WipValue *parent_data, Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *my_data, u32_t order, Dz1Error *errp)
{	// Parent STRUCT vs. Child PRIMITIVE STRUCT
	Dz1Asn1WipCst *dst_seq = NULL;
	Dz1Asn1Custom *dst_sto = NULL;
	Dz1Asn1CharStr *dst = NULL;

	Dz1Asn1ObjDescr *temp = NULL;
	Dz1Asn1TypeAPI *user_api = NULL;

	if (parent_data == NULL || my_descr == NULL || my_data == NULL) ERR_SET_OUT(errp, EINVAL);
	// resolve destination
	else if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_sto = dst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = (Dz1Asn1CharStr *)dst_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	// check status
	else if (dst->str_value_descriptor != NULL) ERR_SET_OUT(errp, EFAULT);
	// actual apply
	else if ((user_api = my_descr->user_api) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((temp = (Dz1Asn1ObjDescr *)user_api->gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1ObjDescr_delAndSetNull, (void *)&temp);

		if (my_descr->finalize((void *)temp, my_data, my_descr, errp) == FALSE) ERR_OUT(errp);
		else
		{
			dst->str_value_descriptor = temp;
			temp = NULL;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(1); // (Dz1Asn1ObjDescr_delAndSetNull, (void *)&temp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
static Dz1Asn1GetChildF_SeqMembPtr(Dz1Asn1CharStr, str_value_descriptor)
// Dz1Asn1CharStr->str_value_descriptor
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1CharStr->str_value
static bool_t Dz1Asn1CharStr_apply_str_value(Dz1Asn1WipValue *parent_data, struct Dz1Asn1TypeDescr *my_descr, Dz1Asn1WipValue *my_data, u32_t order, Dz1Error *errp)
{	// Parent STRUCT vs. Child PRIMITIVE STRUCT
	Dz1Asn1WipCst *dst_seq = NULL;
	Dz1Asn1Custom *dst_sto = NULL;

	Dz1Asn1CharStr *dst = NULL;

	Dz1Asn1OctetStr *temp = NULL;
	Dz1Asn1TypeAPI *user_api = NULL;

	// resolve destination
	if (parent_data->present != Dz1Asn1WipValuePresent_cst_seq) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_seq = parent_data->x.cst_seq) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst_sto = dst_seq->storage) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((dst = (Dz1Asn1CharStr *)dst_sto->data) == NULL) ERR_SET_OUT(errp, EFAULT);
	// check status
	else if (dst->str_value != NULL) ERR_SET_OUT(errp, EFAULT);
	// actual apply
	else if ((user_api = my_descr->user_api) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if ((temp = (Dz1Asn1OctetStr *)user_api->gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1OctetStr_delAndSetNull, (void *)&temp);
		if (my_descr->finalize(temp, my_data, my_descr, errp) == FALSE) ERR_OUT(errp);
		else 
		{
			dst->str_value = temp;
			temp = NULL;

			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Asn1OctetStr_delAndSetNull, (void *)&temp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
static Dz1Asn1GetChildF_SeqMembPtr(Dz1Asn1CharStr, str_value)
// Dz1Asn1CharStr->str_value
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1CharStr Childes
static Dz1Asn1TypeDescrChild Dz1Asn1CharStrArr[] =
{
	{	// identifier
		{ Dz1Asn1TagClass_context_specific, Dz1Asn1TagFlag_construct, 0 },	// tag
		Dz1Asn1TagOpt_explicit,												// descr_tag
		&dz1Asn1TypeDescrDz1Asn1EmbPdvID,									// descr
		Dz1Asn1CharStr_apply_identification,								// apply
		Dz1Asn1GetChildF_func_name(Dz1Asn1CharStr, identifier),				// getChild
		NULL,																// presence
	},
	{	// str_value_descriptor
		{ Dz1Asn1TagClass_context_specific, Dz1Asn1TagFlag_variable,  1 },	// tag
		Dz1Asn1TagOpt_implicit,												// descr_tag
		&dz1Asn1TypeDescrObjDescr,											// descr
		Dz1Asn1CharStr_apply_str_value_descriptor,							// apply
		Dz1Asn1GetChildF_func_name(Dz1Asn1CharStr, str_value_descriptor),	// getChild
		&dz1Asn1TypeDescrChildPresence_optional								// presence
	},	
	{	// str_value
		{ Dz1Asn1TagClass_context_specific, Dz1Asn1TagFlag_variable,  2 },	// tag
		Dz1Asn1TagOpt_implicit,												// descr_tag
		&dz1Asn1TypeDescrOctetStr,											// descr
		Dz1Asn1CharStr_apply_str_value,										// apply
		Dz1Asn1GetChildF_func_name(Dz1Asn1CharStr, str_value),				// getChild
		NULL,																// presence
	},				
	Dz1Asn1TypeDescrChild_last
};
// Dz1Asn1CharStr Childes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1CharStr Conformance
static Dz1Asn1ConstructChildConstraint Dz1Asn1CharStr_constraintArr[] =
{
	{ &dz1Asn1TypeDescrObjDescr, Dz1Asn1CharStr_get_str_value_descriptor, NULL, Dz1Asn1ConstructChildPresence_abssent }
};
static Dz1Asn1ConstructConstraintEntry dz1Asn1CharStr_constraint =
{
	Dz1Asn1CharStr_constraintArr,
	sizeof(Dz1Asn1CharStr_constraintArr) / sizeof(Dz1Asn1ConstructChildConstraint)
};
static Dz1Asn1ConstructConstraintTreeNode dz1Asn1CharStr_inner_subtype = { Dz1Asn1ConstructConstraintTreeNodePresent_constraints, { &dz1Asn1CharStr_constraint } };

static Dz1Asn1Constraint dz1Asn1CharStrConstraints =
{
	NULL,								// value
	NULL,								// i_ranges
	NULL,								// f_rances
	NULL,								// size
	// Permitted Alphabet -> TBD
	NULL,								// type of ANY
	NULL,								// component
	&dz1Asn1CharStr_inner_subtype
	// Property setting -> TBD
	// Duration range -> TBD
	// Time point range -> TBD
	// Recurrence range -> TBD
};

static Dz1Asn1TypeComformance dz1Asn1CharStrConformance =
{
	&dz1Asn1CharStrConstraints,
	Dz1Asn1Sequence_conformance
};
// Dz1Asn1CharStr
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1CharStr
static Dz1Asn1TypeDescrNameDecl(Dz1Asn1CharStr);	// NAME
static Dz1Asn1TagVarDeclare(Dz1Asn1CharStr);		// TAG
Dz1Asn1TypeDescr dz1Asn1TypeDescrCharStr = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1CharStr),			// name
	&Dz1Asn1TagVarName(Dz1Asn1CharStr),				// tag
	Dz1Asn1CharStrArr,								// childs
	&dz1Asn1CharStrConformance,						// conformance
	&Dz1Asn1TypeAPI_name(Dz1Asn1CharStr),			// wip_api
	Dz1Asn1Sequence_enc_BER,						// ber_enc
	Dz1Asn1Sequence_dec_BER,						// ber_dec
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1CharStr),	// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1CharStr)	// user_api
};
// Dz1Asn1CharStr
///////////////////////////////////////////////////////////////////////////////

// Known Multiplier UNICODE String
static Dz1Asn1TypeDescrNameDecl(Dz1Asn1BMPStr);		// Dz1Asn1UTF8Str	__Dz1Asn1BMPStr_u8_ = { (u8_t *)"Dz1Asn1BMPStr", sizeof("Dz1Asn1BMPStr") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1BMPStr);			// Dz1Asn1Tag	berTagDz1Asn1BMPStr = BerTagValueDz1Asn1BMPStr
Dz1Asn1TypeDescr dz1Asn1TypeDescrBMPStr = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1BMPStr),			// name
	&Dz1Asn1TagVarName(Dz1Asn1BMPStr),				// tag
	NULL,											// childs
	NULL,											// XXX : no conformance		-> Value Range
	NULL,											// wip_api
	Dz1Asn1OctetStr_enc_BER, 
	Dz1Asn1OctetStr_dec_BER, 
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1BMPStr),	// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1BMPStr)				// user api
};

// date1 DATE ::= "1985-04-12"						-- Basic=Date Date=YMD Year=Basic
// => 19850402
static Dz1Asn1TypeDescrNameDecl(Dz1Asn1Date);		// Dz1Asn1UTF8Str	__###_u8_ = { (u8_t *)"###", sizeof("###") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1Date);			// Dz1Asn1Tag	berTag### = BerTagValue###
Dz1Asn1TypeDescr dz1Asn1TypeDescrDate = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1Date),				// name
	&Dz1Asn1TagVarName(Dz1Asn1Date),				// tag
	NULL,											// childs
	NULL,											// XXX : no conformance
	NULL,											// wip_api
	Dz1Asn1PrimitiveStr_enc_BER, 
	Dz1Asn1PrimitiveStr_dec_BER, 
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1OctetStr),	// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1UTF8Str)			// user api
};

// time1 TIME-OF-DAY ::= "15:27:46"					-- Basic=Time Time=HMS Local-or-UTC=L
// => 152746
static Dz1Asn1TypeDescrNameDecl(Dz1Asn1TimeOfDay);	// Dz1Asn1UTF8Str	__###_u8_ = { (u8_t *)"###", sizeof("###") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1TimeOfDay);		// Dz1Asn1Tag	berTag### = BerTagValue###
Dz1Asn1TypeDescr dz1Asn1TypeDescrTimeOfDay = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1TimeOfDay),		// name
	&Dz1Asn1TagVarName(Dz1Asn1TimeOfDay),			// tag
	NULL,											// childs
	NULL,											// XXX : no conformance
	NULL,											// wip_api
	Dz1Asn1PrimitiveStr_enc_BER, 
	Dz1Asn1PrimitiveStr_dec_BER, 
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1OctetStr),	// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1UTF8Str)			// user api
};

// date-time1 DATE-TIME ::= "1985-04-12T10:15:30"	-- Basic=Date-Time Date=YMD Year=Basic Time=HMS Local-or-UTC=L
// => 19850412101530
static Dz1Asn1TypeDescrNameDecl(Dz1Asn1DateTime);	// Dz1Asn1UTF8Str	__###_u8_ = { (u8_t *)"###", sizeof("###") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1DateTime);		// Dz1Asn1Tag	berTag### = BerTagValue###
Dz1Asn1TypeDescr dz1Asn1TypeDescrDateTime = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1DateTime),			// name
	&Dz1Asn1TagVarName(Dz1Asn1DateTime),			// tag
	NULL,											// childs
	NULL,											// XXX : no conformance
	NULL,											// wip_api
	Dz1Asn1PrimitiveStr_enc_BER, 
	Dz1Asn1PrimitiveStr_dec_BER, 
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1OctetStr),	// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1UTF8Str)			// user api
};

// duration1 DURATION ::= "P2Y10M15DT10H20M30S"		-- Basic=Interval Interval-type=D	=> 2Y10M15DT10H20M30S
// duration2 DURATION ::= "P1Y6M"					-- Basic=Interval Interval-type=D	=> 1Y6M
// duration3 DURATION ::= "PT72H"					-- Basic=Interval Interval-type=D	=> T72H
static Dz1Asn1TypeDescrNameDecl(Dz1Asn1Duration);	// Dz1Asn1UTF8Str	__###_u8_ = { (u8_t *)"###", sizeof("###") - 1 }
static Dz1Asn1TagVarDeclare(Dz1Asn1Duration);		// Dz1Asn1Tag	berTag### = BerTagValue###
Dz1Asn1TypeDescr dz1Asn1TypeDescrDuration = 
{
	&Dz1Asn1TypeDescrName(Dz1Asn1Duration),			// name
	&Dz1Asn1TagVarName(Dz1Asn1Duration),			// tag
	NULL,											// childs
	NULL,											// XXX : no conformance
	NULL,											// wip_api
	Dz1Asn1PrimitiveStr_enc_BER, 
	Dz1Asn1PrimitiveStr_dec_BER, 
	Dz1Asn1DataTypeFinalizeF_name(Dz1Asn1OctetStr),	// finalize
	&Dz1Asn1TypeAPI_name(Dz1Asn1UTF8Str)			// user api
};


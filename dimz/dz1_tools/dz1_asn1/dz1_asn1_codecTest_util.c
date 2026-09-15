#include "dz1_asn1_codecTest_util.h"

bool_t				 flag_verbose = TRUE;

Dz1Asn1BerEncoderOpt test_enc_opt = Dz1Asn1BerEncoderOpt_cer;
Dz1Asn1DecoderMode	 test_dec_opt = Dz1Asn1DecoderMode_chunk;

u32_t	abstract_syntax_oid_arr[] = { 1, 0, 999, 1, 2, 3 };
u32_t	abstract_syntax_oid_arr_cnt = sizeof(abstract_syntax_oid_arr) / sizeof(u32_t);

u32_t	transfer_syntax_oid_arr[] = { 1, 0, 999, 1, 2, 3, 9, 8, 7 };
u32_t	transfer_syntax_oid_arr_cnt = sizeof(transfer_syntax_oid_arr) / sizeof(u32_t);

s64_t	presentation_context_id = 0xCAFE;

u8_t	str_text[] = { 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54 };
u32_t	str_text_sz = sizeof(str_text) / sizeof(u8_t);


///////////////////////////////////////////////////////////////////////////////
// Decode Test
static void *dz1_asn1_codecTest_BER2(Dz1Asn1TypeDescr *descr, Dz1Binary *bin, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	void *ret = NULL;
	Dz1Asn1BerDecoder *decoder = NULL;
	if ((decoder = Dz1Asn1BerDecoder_generate(descr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Asn1Stream *st = NULL;
		pthread_cleanup_push(Dz1Asn1BerDecoder_delAndSetNull, (void *)&decoder);

		if ((st = Dz1Asn1Stream_new(1024, errp)) == NULL) ERR_OUT(errp);
		else
		{
			u32_t dot_printed = 0;
			u8_t *cp = bin->data;
			size_t remain = bin->size;
			ssize_t sz;
			pthread_cleanup_push(Dz1Asn1Stream_delAndSetNull, (void *)&st);
			while(errp->code == 0 && ret == NULL && remain > 0)
			{
//				if (_Dz1ElasticBuf_push(elb, cp, 1, errp) == FALSE) ERR_OUT(errp);
				if (Dz1Asn1Stream_pushOctet(st, *cp, errp) == FALSE) ERR_OUT(errp);
				else 
				{
					cp++;
					remain--;

					if ((sz = Dz1Asn1BerDecoder_dec(decoder, st, param, errp)) < 0) ERR_OUT(errp);
					else if ((ret = Dz1Asn1BerDecoder_retrive(decoder, errp)) == NULL)
					{
						if (errp->code != EAGAIN) ERR_OUT(errp);
						else 
						{
							Dz1Error_set(errp, 0);
							if (flag_verbose)
							{
								Dz1Thread_putc(Dz1T('.'), NULL);
								dot_printed++;
								if ((dot_printed % 16) == 0)
								{
									Dz1Thread_putc(Dz1T('\n'), NULL);
									dot_printed = 0;
								}
							}
						}
					}
					else
					{
						Dz1Error_set(errp, 0);
						if (flag_verbose)
						{
							if (dot_printed)
								Dz1Thread_putc(Dz1T('\n'), NULL);
						}
					}
				}
			}
			pthread_cleanup_pop(1); // (Dz1Asn1Stream_delAndSetNull, (void *)&st);
		}
		pthread_cleanup_pop(1); // (Dz1Asn1BerDecoder_delAndSetNull, (void *)&decoder);
	}
	return ret;
}

static void *dz1_asn1_codecTest_BER(Dz1Asn1TypeDescr *descr, Dz1Binary *bin, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	void *ret = NULL;
	Dz1Asn1BerDecoder *decoder = NULL;
	if ((decoder = Dz1Asn1BerDecoder_generate(descr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Asn1Stream *st = NULL;
		pthread_cleanup_push(Dz1Asn1BerDecoder_delAndSetNull, (void *)&decoder);

		if ((st = Dz1Asn1Stream_new(1024, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ssize_t sz = 0;
			bool_t done = FALSE;
			pthread_cleanup_push(Dz1Asn1Stream_delAndSetNull, (void *)&st);

			if (Dz1Asn1Stream_pushOctets(st, bin->data, bin->size, errp) == FALSE) ERR_OUT(errp);
			else if ((sz = Dz1Asn1BerDecoder_dec(decoder, st, param, errp)) < 0) ERR_OUT(errp);
			else if ((ret = Dz1Asn1BerDecoder_retrive(decoder, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(1); // (Dz1Asn1Stream_delAndSetNull, (void *)&st);
		}
		pthread_cleanup_pop(1); // (Dz1Asn1BerDecoder_delAndSetNull, (void *)&decoder);
	}
	return ret;
}

typedef void *(*DecoderTestFunc)(Dz1Asn1TypeDescr *descr, Dz1Binary *bin, void *param, Dz1Error *err);
static DecoderTestFunc decode_test[] =
{
	dz1_asn1_codecTest_BER,
	dz1_asn1_codecTest_BER2
};

void *dz1_asn1_ber_deocde(Dz1Asn1TypeDescr *descr, Dz1Binary *bin, void *param, Dz1Error *err)
{
	return decode_test[test_dec_opt](descr, bin, param, err);
}
// Decode Test
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Ingress Test : encode(GASN) -> decode(Dz1Asn1)
bool_t dz1_asn1_ber_ingress_test(Dz1Asn1TypeDescr *descr, void *gasn_src, gasn_ber_encF gasn_enc, Dz1DumpFunc gasn_dump, data_compareF data_cmp, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *bin = NULL;

	char str_name[64];
	Dz1Asn1UTF8StrA_printable(descr->name, str_name, 64, NULL);
	Dz1Thread_printf(Dz1T("========================================\n"));
	Dz1Thread_printf(Dz1T("%s Ingress Test\n"), str_name);
	Dz1Thread_printf(Dz1T("========================================\n"));

	if (flag_verbose) gasn_dump(gasn_src, 0);

	if ((bin = gasn_enc(gasn_src, errp)) == NULL) ERR_OUT(errp);
	else
	{
		void *v_ptr = NULL;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

		if (flag_verbose)
		{
			Dz1Thread_printf("@@@ BER Stream = ");
			Dz1Binary_dump(bin, 0);
		}

		if ((v_ptr = decode_test[test_dec_opt](descr, bin, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Asn1TypeAPI *user_api = descr->user_api;
			pthread_cleanup_push(user_api->delAndSetNull, (void *)&v_ptr);
			if (data_cmp(gasn_src, v_ptr) == 0)
				Dz1Thread_printf(Dz1T(">>> Result : Same Value\n"));
			else
			{
				Dz1Thread_printf(Dz1T("!!! Test Fail\n"));
				ERR_SET_OUT(errp, EFAULT);
			}
			
			if (flag_verbose) { Dz1Thread_tprintf(0, Dz1T("v_ptr = ")); Dz1Asn1TypeDescrData_dump(v_ptr, 1, descr); }

			pthread_cleanup_pop(1); // (user_api->delAndSetNull, (void *)&v_ptr);
		}
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Ingress Test
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Egress Test : encode(Dz1Asn1) -> decode(GASN)
bool_t dz1_asn1_ber_egress_test(Dz1Asn1TypeDescr *descr, void *dz1asn_src, gasn_ber_decF gasn_dec, Dz1DumpFunc gasn_dump, data_compareF data_cmp, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ElasticBuf *elb = NULL;

	char str_name[64];
	Dz1Asn1UTF8StrA_printable(descr->name, str_name, 64, NULL);
	Dz1Thread_printf(Dz1T("========================================\n"));
	Dz1Thread_printf(Dz1T("%s Egress Test\n"), str_name);
	Dz1Thread_printf(Dz1T("========================================\n"));

	if (flag_verbose) { Dz1Thread_printf(Dz1T("src = ")); Dz1Asn1TypeDescrData_dump(dz1asn_src, 0, descr); }

	if ((elb = Dz1ElasticBuf_new(512, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Binary *bin = NULL;
		Dz1Asn1BerEncoderArg param = { test_enc_opt };
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);
		if (Dz1Asn1BerEncoder_enc(elb, descr, dz1asn_src, Dz1Asn1TagOpt_explicit, NULL, &param, errp) == FALSE) ERR_OUT(errp);
		else if ((bin = Dz1ElasticBuf_flattenAndPurge(elb, errp)) == NULL) ERR_OUT(errp);
		else
		{
			void *v_ptr;
			ASN1WorkSpace ws;

			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

			if (flag_verbose)
			{
				Dz1Thread_printf("@@@ BER Stream = ");
				Dz1Binary_dump(bin, 0);
			}

			ASN1_INIT_WS_INFO(&ws);
			pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

			if ((v_ptr = gasn_dec(bin, &ws, errp)) == NULL) ERR_OUT(errp);
			else if (data_cmp(v_ptr, dz1asn_src) == 0)
				Dz1Thread_printf(Dz1T(">>> Result : Same Value\n"));
			else
			{
				Dz1Thread_printf(Dz1T("!!! Test Fail\n"));
				ERR_SET_OUT(errp, EFAULT);
			}

			if (flag_verbose) gasn_dump(v_ptr, 0);

			pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);

			pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
		}
		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Egress Test : encode(Dz1Asn1) -> decode(GASN)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Self Test : encode(Dz1Asn1) -> decode(Dz1Asn1)
bool_t dz1_asn1_ber_self_test(Dz1Asn1TypeDescr *descr, void *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ElasticBuf *elb = NULL;

	char str_name[64];
	Dz1Asn1UTF8StrA_printable(descr->name, str_name, 64, NULL);
	Dz1Thread_printf(Dz1T("========================================\n"));
	Dz1Thread_printf(Dz1T("%s Self Test\n"), str_name);
	Dz1Thread_printf(Dz1T("========================================\n"));
	if ((elb = Dz1ElasticBuf_new(512, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Binary *bin = NULL;
		Dz1Asn1BerEncoderArg param = { test_enc_opt };
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);

		if (flag_verbose) { Dz1Thread_printf(Dz1T("src = ")); Dz1Asn1TypeDescrData_dump(src, 0, descr); }

		if (Dz1Asn1BerEncoder_enc(elb, descr, src, Dz1Asn1TagOpt_explicit, NULL, &param, errp) == FALSE) ERR_OUT(errp);
		else if ((bin = Dz1ElasticBuf_flattenAndPurge(elb, errp)) == NULL) ERR_OUT(errp);
		else
		{
			void *v_ptr;
			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

			if (flag_verbose)
			{
				Dz1Thread_printf("@@@ BER Stream = ");
				Dz1Binary_dump(bin, 0);
			}

			if ((v_ptr = decode_test[test_dec_opt](descr, bin, NULL, errp)) == NULL) ERR_OUT(errp);
			else
			{
				Dz1Asn1TypeAPI *user_api = descr->user_api;
				pthread_cleanup_push(user_api->delAndSetNull, (void *)&v_ptr);
				if (user_api->cmp(src, v_ptr) == 0)
					Dz1Thread_printf(Dz1T(">>> Result : Same Value\n"));
				else
				{
					Dz1Thread_printf(Dz1T("!!! Test Fail\n"));
					ERR_SET_OUT(errp, EFAULT);
				}
				if (flag_verbose) { Dz1Thread_tprintf(0, Dz1T("v_ptr = ")); Dz1Asn1TypeDescrData_dump(v_ptr, 0, descr); }
				pthread_cleanup_pop(1); // (user_api->delAndSetNull, (void *)&v_ptr);
			}
			pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
		}
		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Self Test : encode(Dz1Asn1) -> decode(Dz1Asn1)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Constructed BER Stream Decode Test : compare(decode(GASN), decode(Dz1Asn1)
bool_t dz1_asn1_ber_construct_test(Dz1Asn1TypeDescr *descr, Dz1Binary *ber, gasn_ber_decF gasn_dec, Dz1DumpFunc gasn_dump, data_compareF data_cmp, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ASN1WorkSpace ws;
	void *gasn_ptr = NULL;

	char str_name[64];
	Dz1Asn1UTF8StrA_printable(descr->name, str_name, 64, NULL);
	Dz1Thread_printf(Dz1T("========================================\n"));
	Dz1Thread_printf(Dz1T("%s Constructed Form Test\n"), str_name);
	Dz1Thread_printf(Dz1T("========================================\n"));

	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

	if ((gasn_ptr = gasn_dec(ber, &ws, errp)) == NULL) ERR_OUT(errp);
	else
	{
		void *dz1asn_ptr = NULL;
		if (flag_verbose) 
		{
			Dz1Thread_printf(Dz1T("It's correct BER Data\n"));
			gasn_dump(gasn_ptr, 1);
		}

		if ((dz1asn_ptr = decode_test[test_dec_opt](descr, ber, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Asn1TypeAPI *user_api = descr->user_api;
			pthread_cleanup_push(user_api->delAndSetNull, (void *)&dz1asn_ptr);

			if (flag_verbose)
			{
				Dz1Thread_printf(Dz1T(">>> Result : "));
				Dz1Asn1TypeDescrData_dump(dz1asn_ptr, 0, descr);
			}

			if (data_cmp != NULL && data_cmp(gasn_ptr, dz1asn_ptr) != 0)
			{
				ERR_SET_OUT(errp, EFAULT);
				Dz1Thread_printf(Dz1T("!!! : Different\n"));
			}
			pthread_cleanup_pop(1); // (user_api->delAndSetNull, (void *)&dz1asn_ptr);
		}
	}
	pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);

	return errp->code == 0 ? TRUE : FALSE;
}
// Constructed BER Stream Decode Test : compare(decode(GASN), decode(Dz1Asn1)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CHARACTER STRING identification
static bool_t _init_gasn_charstring_syntaxes(CHARACTERSTRING *dst, ASN1WorkSpace *ws, Dz1Error *errp)
{
	if (ASN1_SET_CHARACTERSTRING_CHOICE_syntaxes(ws, dst, abstract_syntax_oid_arr, abstract_syntax_oid_arr_cnt, transfer_syntax_oid_arr, transfer_syntax_oid_arr_cnt) < 0) ERR_SET_OUT(errp, EFAULT);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _init_gasn_charstring_abstract(CHARACTERSTRING *dst, ASN1WorkSpace *ws, Dz1Error *errp)
{
	if (ASN1_SET_CHARACTERSTRING_CHOICE_syntax(ws, dst, abstract_syntax_oid_arr, abstract_syntax_oid_arr_cnt) < 0) ERR_SET_OUT(errp, EFAULT);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _init_gasn_charstring_presentation(CHARACTERSTRING *dst, ASN1WorkSpace *ws, Dz1Error *errp)
{
	if (ASN1_SET_CHARACTERSTRING_CHOICE_presentation_context_id(ws, dst, presentation_context_id) < 0) ERR_SET_OUT(errp, EFAULT);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _init_gasn_charstring_negotiation(CHARACTERSTRING *dst, ASN1WorkSpace *ws, Dz1Error *errp)
{
	if (ASN1_SET_CHARACTERSTRING_CHOICE_context_negotiation(ws, dst, presentation_context_id, transfer_syntax_oid_arr, transfer_syntax_oid_arr_cnt) < 0) ERR_SET_OUT(errp, EFAULT);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _init_gasn_charstring_transfer(CHARACTERSTRING *dst, ASN1WorkSpace *ws, Dz1Error *errp)
{
	if (ASN1_SET_CHARACTERSTRING_CHOICE_transfer_syntax(ws, dst, transfer_syntax_oid_arr, transfer_syntax_oid_arr_cnt) < 0) ERR_SET_OUT(errp, EFAULT);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _init_gasn_charstring_fixed(CHARACTERSTRING *dst, ASN1WorkSpace *ws, Dz1Error *errp)
{
	if (ASN1_SET_CHARACTERSTRING_CHOICE_fixed(ws, dst, 0) < 0) ERR_SET_OUT(errp, EFAULT);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

//bool_t _init_gasn_charstring_identification(CHARACTERSTRING *dst, ASN1WorkSpace *ws, Dz1Str str_id_mode, Dz1Error *errp)
bool_t _init_gasn_charstring_identification(CHARACTERSTRING *dst, ASN1WorkSpace *ws, Dz1Asn1EmbPdvIDPresent present, Dz1Error *errp)
{
	switch(present)
	{
	case Dz1Asn1EmbPdvIDPresent_syntaxes:					return _init_gasn_charstring_syntaxes(dst, ws, errp);
	case Dz1Asn1EmbPdvIDPresent_syntax:						return _init_gasn_charstring_abstract(dst, ws, errp);
	case Dz1Asn1EmbPdvIDPresent_presentation_context_id:	return _init_gasn_charstring_presentation(dst, ws, errp);
	case Dz1Asn1EmbPdvIDPresent_context_negotiation:		return _init_gasn_charstring_negotiation(dst, ws, errp);
	case Dz1Asn1EmbPdvIDPresent_transfer_syntax:			return _init_gasn_charstring_transfer(dst, ws, errp);
	case Dz1Asn1EmbPdvIDPresent_fixed:						return _init_gasn_charstring_fixed(dst, ws, errp);
	default:												Dz1Error_set(errp, EINVAL); return FALSE;
	}
}
// CHARACTER STRING identification
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1Asn1EmbPdvID generator
static Dz1Asn1EmbPdvID *_init_Dz1Asn1EmbPdvID_syntaxes(Dz1Error *errp)
{
	Dz1Asn1EmbPdvID *id = Dz1Asn1EmbPdvID_new(Dz1Asn1EmbPdvIDPresent_syntaxes, NULL, errp);
	if (id == NULL) ERR_OUT(errp);
	else
	{
		Dz1Asn1EmbPdvSyntaxes *p = NULL;
		pthread_cleanup_push(Dz1Asn1EmbPdvID_delAndSetNull, (void *)&id);

		if ((p = id->x.syntaxes = Dz1Asn1EmbPdvSyntaxes_new(NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((p->abstract = Dz1Asn1OID_new(abstract_syntax_oid_arr, abstract_syntax_oid_arr_cnt, errp)) == NULL) ERR_OUT(errp);
		else if ((p->transfer = Dz1Asn1OID_new(transfer_syntax_oid_arr, transfer_syntax_oid_arr_cnt, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Asn1EmbPdvID_delAndSetNull, (void *)&id);
	}
	return id;
}

static Dz1Asn1EmbPdvID *_init_Dz1Asn1EmbPdvID_abstract(Dz1Error *errp)
{
	Dz1Asn1EmbPdvID *id = Dz1Asn1EmbPdvID_new(Dz1Asn1EmbPdvIDPresent_syntax, NULL, errp);
	if (id == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1EmbPdvID_delAndSetNull, (void *)&id);

		if ((id->x.syntax = Dz1Asn1OID_new(abstract_syntax_oid_arr, abstract_syntax_oid_arr_cnt, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Asn1EmbPdvID_delAndSetNull, (void *)&id);
	}
	return id;
}

static Dz1Asn1EmbPdvID *_init_Dz1Asn1EmbPdvID_presentation(Dz1Error *errp)
{
	Dz1Asn1EmbPdvID *id = Dz1Asn1EmbPdvID_new(Dz1Asn1EmbPdvIDPresent_presentation_context_id, NULL, errp);
	if (id == NULL) ERR_OUT(errp);
	else
	{
		id->x.presentation_context_id = presentation_context_id;
		Dz1Error_set(errp, 0);
	}
	return id;
}

static Dz1Asn1EmbPdvID *_init_Dz1Asn1EmbPdvID_negotiation(Dz1Error *errp)
{
	Dz1Asn1EmbPdvID *id = Dz1Asn1EmbPdvID_new(Dz1Asn1EmbPdvIDPresent_context_negotiation, NULL, errp);
	if (id == NULL) ERR_OUT(errp);
	else
	{
		Dz1Asn1EmbPdvCtxNego *p = NULL;
		pthread_cleanup_push(Dz1Asn1EmbPdvID_delAndSetNull, (void *)&id);

		if ((p = id->x.context_negotiation = Dz1Asn1EmbPdvCtxNego_new(presentation_context_id, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((p->transfer_syntax = Dz1Asn1OID_new(transfer_syntax_oid_arr, transfer_syntax_oid_arr_cnt, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Asn1EmbPdvID_delAndSetNull, (void *)&id);
	}
	return id;
}

static Dz1Asn1EmbPdvID *_init_Dz1Asn1EmbPdvID_transfer(Dz1Error *errp)
{
	Dz1Asn1EmbPdvID *id = Dz1Asn1EmbPdvID_new(Dz1Asn1EmbPdvIDPresent_transfer_syntax, NULL, errp);
	if (id == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1EmbPdvID_delAndSetNull, (void *)&id);

		if ((id->x.transfer_syntax = Dz1Asn1OID_new(transfer_syntax_oid_arr, transfer_syntax_oid_arr_cnt, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Asn1EmbPdvID_delAndSetNull, (void *)&id);
	}
	return id;
}

static Dz1Asn1EmbPdvID *_init_Dz1Asn1EmbPdvID_fixed(Dz1Error *errp)
{
	Dz1Asn1EmbPdvID *id = Dz1Asn1EmbPdvID_new(Dz1Asn1EmbPdvIDPresent_fixed, NULL, errp);
	if (id == NULL) ERR_OUT(errp);
	else
	{
		id->x.fixed = Dz1Asn1Null_initializer;
		Dz1Error_set(errp, 0);
	}
	return id;
}

static Dz1Asn1EmbPdvID *_init_Dz1Asn1EmbPdvID(Dz1Asn1EmbPdvIDPresent id_mode, Dz1Error *errp)
{
	Dz1Asn1EmbPdvID *ret = NULL;
	switch(id_mode)
	{
	case Dz1Asn1EmbPdvIDPresent_syntaxes:					if ((ret = _init_Dz1Asn1EmbPdvID_syntaxes(errp)) == NULL) ERR_OUT(errp); else Dz1Error_set(errp, 0); break;
	case Dz1Asn1EmbPdvIDPresent_syntax:						if ((ret = _init_Dz1Asn1EmbPdvID_abstract(errp)) == NULL) ERR_OUT(errp); else Dz1Error_set(errp, 0); break;
	case Dz1Asn1EmbPdvIDPresent_presentation_context_id:	if ((ret = _init_Dz1Asn1EmbPdvID_presentation(errp)) == NULL) ERR_OUT(errp); else Dz1Error_set(errp, 0); break;
	case Dz1Asn1EmbPdvIDPresent_context_negotiation:		if ((ret = _init_Dz1Asn1EmbPdvID_negotiation(errp)) == NULL) ERR_OUT(errp); else Dz1Error_set(errp, 0); break;
	case Dz1Asn1EmbPdvIDPresent_transfer_syntax:			if ((ret = _init_Dz1Asn1EmbPdvID_transfer(errp)) == NULL) ERR_OUT(errp); else Dz1Error_set(errp, 0); break;
	case Dz1Asn1EmbPdvIDPresent_fixed:						if ((ret = _init_Dz1Asn1EmbPdvID_fixed(errp)) == NULL) ERR_OUT(errp); else Dz1Error_set(errp, 0); break;
	default:												ERR_SET_OUT(errp, EINVAL); break;
	}
	return ret;
}
// Dz1Asn1EmbPdvID generator
///////////////////////////////////////////////////////////////////////////////

Dz1Asn1CharStr *_charstr_gen(Dz1Asn1EmbPdvIDPresent id_mode, Dz1Str str_value_descr, Dz1Error *errp)
{
	Dz1Asn1CharStr *ret = Dz1Asn1CharStr_new(NULL, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		int status = 0;
		pthread_cleanup_push(Dz1Asn1CharStr_delAndSetNull, (void *)&ret);
		if ((ret->identifier = _init_Dz1Asn1EmbPdvID(id_mode, errp)) == FALSE)
		{
			if (errp->code == EINVAL) { }
			else ERR_OUT(errp);
		}
		else if (Dz1Str_isVoid(str_value_descr) == FALSE && (ret->str_value_descriptor = Dz1Asn1UTF8Str_newFromStr(str_value_descr, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->str_value = Dz1Asn1OctetStr_new(str_text, str_text_sz, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1Asn1CharStr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Asn1EmbPdv *_pdv_gen(Dz1Asn1EmbPdvIDPresent id_mode, Dz1Str str_value_descr, Dz1Error *errp)
{
	Dz1Asn1EmbPdv *ret = Dz1Asn1EmbPdv_new(NULL, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		int status = 0;
		pthread_cleanup_push(Dz1Asn1EmbPdv_delAndSetNull, (void *)&ret);
		if ((ret->identifier = _init_Dz1Asn1EmbPdvID(id_mode, errp)) == FALSE)
		{
			if (errp->code == EINVAL) { }
			else ERR_OUT(errp);
		}
		else if (Dz1Str_isVoid(str_value_descr) == FALSE && (ret->data_value_descriptor = Dz1Asn1UTF8Str_newFromStr(str_value_descr, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->data_value = Dz1Asn1OctetStr_new(str_text, str_text_sz, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1Asn1EmbPdv_delAndSetNull, (void *)&ret);
	}
	return ret;
}


/*
typedef struct Dz1Asn1External
{
	Dz1Asn1OID					    *direct_reference;					// OPTIONAL
	Dz1Asn1Int					    *indirect_reference;				// OPTIONAL
	Dz1Asn1ObjDescr				    *data_value_descriptor;				// OPTIONAL
	Dz1Asn1ExternalEncoding			*encoding;
} Dz1Asn1External;
*/
Dz1Asn1External *_external_gen(Dz1Str strOID, s64_t *indirect, str_t strDescr, Dz1Asn1ExternalEncodingPresent mode, u8_t *data, size_t sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1ExternalEncoding *enc = NULL;
	Dz1Asn1External *ret = Dz1Asn1External_new(NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		Dz1Asn1Any *asn_any = NULL;

		pthread_cleanup_push(Dz1Asn1External_delAndSetNull, (void *)&ret);
		if (0) { }
		else if (Dz1Str_isVoid(strOID) == FALSE && (ret->direct_reference = Dz1Asn1OID_newFromStr(strOID, errp)) == NULL) ERR_OUT(errp);
		else if (indirect != NULL && (ret->indirect_reference = Dz1Asn1Int_new(indirect, errp)) == NULL) ERR_OUT(errp);
		else if (Dz1Str_isVoid(strDescr) == FALSE && (ret->data_value_descriptor = Dz1Asn1ObjDescr_new((u8_t *)strDescr, (u32_t)strlen(strDescr), errp)) == NULL) ERR_OUT(errp);
		else if ((ret->encoding = enc = Dz1Asn1ExternalEncoding_new(Dz1Asn1ExternalEncodingPresent_max, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Asn1OctetStr octet = { data, (u32_t)sz & 0xFFFF };
			switch(mode)
			{
			case Dz1Asn1ExternalEncodingPresent_arbitrary:
				if ((enc->x.arbitrary = Dz1Asn1BitStr_new(data, sz, errp)) == NULL) ERR_OUT(errp);
				else
				{
					enc->present = Dz1Asn1ExternalEncodingPresent_arbitrary;
					Dz1Error_set(errp, 0);
				}
				break;
			case Dz1Asn1ExternalEncodingPresent_octet_aligned:
				if ((enc->x.octet_aligned = Dz1Asn1OctetStr_new(data, (u32_t)sz, errp)) == NULL) ERR_OUT(errp);
				else
				{
					enc->present = Dz1Asn1ExternalEncodingPresent_octet_aligned;
					Dz1Error_set(errp, 0);
				}
				break;
			case Dz1Asn1ExternalEncodingPresent_single_ASN1_type:
				if ((enc->x.single_ASN1_type = asn_any = Dz1Asn1Any_newFromBER(&dz1Asn1TypeDescrOctetStr, &octet, errp)) == NULL) ERR_OUT(errp);
				else
				{
					enc->present = Dz1Asn1ExternalEncodingPresent_single_ASN1_type;
					Dz1Error_set(errp, 0);
				}
				break;
			default: ERR_SET_OUT(errp, EINVAL); break;
			}
		}
		pthread_cleanup_pop(errp->code); // (Dz1Asn1External_delAndSetNull, (void *)&ret);
	}
	return ret;
}

/*
typedef struct Dz1Asn1InstanceOf
{
	Dz1Asn1OID	*type_id;
	Dz1Asn1Any	*value;
} Dz1Asn1InstanceOf;
*/
Dz1Asn1InstanceOf *_instance_of_gen(Dz1Str strOID, u8_t *data, size_t sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Asn1ExternalEncoding *enc = NULL;
	Dz1Asn1InstanceOf *ret = Dz1Asn1InstanceOf_new(NULL, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		Dz1Asn1OctetStr octet = { data, (u32_t)sz & 0xFFFFFFFF };
		pthread_cleanup_push(Dz1Asn1External_delAndSetNull, (void *)&ret);
		if (0) { }
		else if ((ret->type_id = Dz1Asn1OID_newFromStr(strOID, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->value = Dz1Asn1Any_newFromBER(&dz1Asn1TypeDescrOctetStr, &octet, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(errp->code); // (Dz1Asn1External_delAndSetNull, (void *)&ret);
	}
	return ret;
}

#include <BER/ASN1_BER_CHARACTERSTRING.h>
#include "dz1_asn1_codecTest.h"

static GASN_ENC_DECLARE(CHARACTERSTRING, dz1_charstring_ber_enc_gasn)
static GASN_DEC_DECLARE(CHARACTERSTRING, dz1_charstring_ber_dec_gasn)
static GASN_DUMP_TAB_DECLARE(CHARACTERSTRING, dz1_charstring_dump_gasn, v)

static int _charstring_id_syntaxes_cmp(ASN1CHARACTERSTRING_identification_syntaxes *a, Dz1Asn1EmbPdvSyntaxes *b)
{
	int ret = 0;
	if ((ret = _oid_cmp(&a->abstract, b->abstract)) != 0) return ret;
	else return _oid_cmp(&a->transfer, b->transfer);
}

static int _charstring_id_negotiation_cmp(ASN1CHARACTERSTRING_identification_context_negotiation *a, Dz1Asn1EmbPdvCtxNego *b)
{
	int ret = 0;
	if ((ret = _integer_cmp(&a->presentation_context_id, &b->presentation_context_id)) != 0) return ret;
	else return _oid_cmp(&a->transfer_syntax, b->transfer_syntax);
}

static int _charstring_id_cmp(ASN1CHARACTERSTRING_identification *a, Dz1Asn1EmbPdvID *b)
{
	u32_t b_M = (u32_t)b->present;
	if (a->M < b_M) return -1;
	else if (a->M > b_M) return 1;
	else
	{
		switch(b->present)
		{
		case Dz1Asn1EmbPdvIDPresent_syntaxes:					return _charstring_id_syntaxes_cmp(a->elements.syntaxes, b->x.syntaxes);
		case Dz1Asn1EmbPdvIDPresent_syntax:						return _oid_cmp(&a->elements.syntax, b->x.syntax);
		case Dz1Asn1EmbPdvIDPresent_presentation_context_id:	return _integer_cmp(&a->elements.presentation_context_id, &b->x.presentation_context_id);
		case Dz1Asn1EmbPdvIDPresent_context_negotiation:		return _charstring_id_negotiation_cmp(a->elements.context_negotiation, b->x.context_negotiation);
		case Dz1Asn1EmbPdvIDPresent_transfer_syntax:			return _oid_cmp(&a->elements.transfer_syntax, b->x.transfer_syntax);
		case Dz1Asn1EmbPdvIDPresent_fixed:
		default: return 0;
		}
	}
}

static int _charstring_cmp(CHARACTERSTRING *a, Dz1Asn1CharStr *b)
{
	int ret = 0;
	if ((ret = _charstring_id_cmp(a->identification, b->identifier)) != 0) return ret;
	else return _octetstr_cmp(&a->string_value, b->str_value);
}

////////////////////////////////////////////////////////////////////////////////
// CHARACTERSTRING Export Test
static bool_t _charstr_imp_test(Dz1Asn1EmbPdvIDPresent present, Dz1Error *errp)
{
	ASN1WorkSpace ws;
	CHARACTERSTRING *v = NULL;

	Dz1Thread_printf(Dz1T("================================================================================\n"));
	Dz1Thread_printf(Dz1T("CHARACTER STRING Ingress Test\n"));
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

	if ((v = (CHARACTERSTRING *)mpool_calloc(ws.Pmemory, sizeof(CHARACTERSTRING), 1)) == NULL) ERR_SET_OUT(errp, ENOMEM);
	else if (_init_gasn_charstring_identification(v, &ws, present, errp) == FALSE) ERR_OUT(errp);
	else if (ASN1_SET_CHARACTERSTRING_SEQUENCE_string_value(&ws, v, str_text, str_text_sz) < 0) ERR_SET_OUT(errp, EFAULT);
	else if (dz1_asn1_ber_ingress_test(&dz1Asn1TypeDescrCharStr, v, dz1_charstring_ber_enc_gasn, dz1_charstring_dump_gasn, _charstring_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _charstr_exp_test(Dz1Asn1EmbPdvIDPresent id_mode, Dz1Str str_value_descr, Dz1Error *errp)
{
	Dz1Asn1CharStr *v = NULL;
	
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	Dz1Thread_printf(Dz1T("CHARACTER STRING Egress Test\n"));
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	if ((v = _charstr_gen(id_mode, str_value_descr, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1CharStr_delAndSetNull, (void *)&v);

		if (dz1_asn1_ber_egress_test(&dz1Asn1TypeDescrCharStr, v, dz1_charstring_ber_dec_gasn, dz1_charstring_dump_gasn, _charstring_cmp, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Asn1CharStr_delAndSetNull, (void *)&v);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _charstr_test(Dz1Asn1EmbPdvIDPresent id_mode, Dz1Str str_value_descr, Dz1Error *errp)
{
	if (0) { }
	else if (_charstr_imp_test(id_mode, errp) == FALSE) ERR_OUT(errp);
	else if (_charstr_exp_test(id_mode, str_value_descr,errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1Asn1EmbPdvIDPresent _parse_id_mode(Dz1Str str_id_mode)
{
	Dz1Asn1EmbPdvIDPresent ret = Dz1Asn1EmbPdvIDPresent_max;
	if (0) { }
	else if (Dz1STRCMP(str_id_mode, Dz1T("syntaxes")) == 0		|| Dz1STRCMP(str_id_mode, Dz1T("s")) == 0) ret = Dz1Asn1EmbPdvIDPresent_syntaxes;
	else if (Dz1STRCMP(str_id_mode, Dz1T("abstract")) == 0		|| Dz1STRCMP(str_id_mode, Dz1T("a")) == 0) ret = Dz1Asn1EmbPdvIDPresent_syntax;
	else if (Dz1STRCMP(str_id_mode, Dz1T("presentation")) == 0	|| Dz1STRCMP(str_id_mode, Dz1T("p")) == 0) ret = Dz1Asn1EmbPdvIDPresent_presentation_context_id;
	else if (Dz1STRCMP(str_id_mode, Dz1T("negotiation")) == 0	|| Dz1STRCMP(str_id_mode, Dz1T("n")) == 0) ret = Dz1Asn1EmbPdvIDPresent_context_negotiation;
	else if (Dz1STRCMP(str_id_mode, Dz1T("transfer")) == 0		|| Dz1STRCMP(str_id_mode, Dz1T("t")) == 0) ret = Dz1Asn1EmbPdvIDPresent_transfer_syntax;
	else if (Dz1STRCMP(str_id_mode, Dz1T("fixed")) == 0			|| Dz1STRCMP(str_id_mode, Dz1T("f")) == 0) ret = Dz1Asn1EmbPdvIDPresent_fixed;
	return ret;
}

static void cmd_ber_exp_charstring_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <syntaxes | abstract | presentation | negotiation | transfer | fixed> <obj_descr_str>\n"), n); }
void cmd_ber_exp_charstring(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	Dz1Asn1EmbPdvIDPresent id_mode = Dz1Asn1EmbPdvIDPresent_max;
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("chsrstr"));
	if (argc != 2 && argc != 3) cmd_ber_exp_charstring_usage(n);
	else if ((id_mode = _parse_id_mode(argv[1])) == Dz1Asn1EmbPdvIDPresent_max) cmd_ber_exp_charstring_usage(n);
	else
	{
		// Command Code Here
		Dz1Str obj_descr_str = argc >= 3 ? argv[2] : NULL;
		if (_charstr_test(id_mode, obj_descr_str, errp) == FALSE) ERR_OUT(errp);
		else Dz1Thread_printf(Dz1T("Test Success\n"));
	}
}
// CHARACTERSTRING Export Test
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// cmd_exp_external_native Sub Command
static void cmd_exp_external_native_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <bits | octet | asn> [-d] [-i] [-s]\n"), n); }
void cmd_exp_external_native(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;

	void (*_print_usage)(Dz1Str n) = cmd_exp_external_native_usage;
	TCHAR n[64];
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("native"));

	if (argc < 2 || argc > 5) _print_usage(n);
	else
	{
		int i;
		Dz1Str strOID = NULL;
		str_t strDescr = NULL;
		s64_t _indirect = 0, *indirect = NULL;
		u8_t data[] = { 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xCD, 0xEF, 0xF0 };

		Dz1Asn1ExternalEncodingPresent mode = Dz1Asn1ExternalEncodingPresent_max;
		Dz1Asn1External *v = NULL;

		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1T("bits")) == 0 || Dz1STRCMP(argv[1], Dz1T("b")) == 0) mode = Dz1Asn1ExternalEncodingPresent_arbitrary;
		else if (Dz1STRCMP(argv[1], Dz1T("octet")) == 0 || Dz1STRCMP(argv[1], Dz1T("o")) == 0) mode = Dz1Asn1ExternalEncodingPresent_octet_aligned;
		else if (Dz1STRCMP(argv[1], Dz1T("asn")) == 0 || Dz1STRCMP(argv[1], Dz1T("a")) == 0) mode = Dz1Asn1ExternalEncodingPresent_single_ASN1_type;
		else { _print_usage(n); return; }

		for (i = 2; i < argc; i++)
		{
			if (Dz1STRCMP(argv[i], Dz1T("-d")) == 0)
			{
				if (strOID != NULL) { _print_usage(n); return; }
				else strOID = Dz1T("1.0.34.1.1.1.1");
			}
			else if (Dz1STRCMP(argv[i], Dz1T("-i")) == 0)
			{
				if (indirect != NULL) { _print_usage(n); return; }
				else
				{
					_indirect = 9999;
					indirect = &_indirect;
				}
			}
			else if (Dz1STRCMP(argv[i], Dz1T("-s")) == 0)
			{
				if (strDescr != NULL) { _print_usage(n); return; }
				else strDescr = "data_value_descriptor";
			}
		}

		if ((v = _external_gen(strOID, indirect, strDescr, mode, data, sizeof(data), errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Asn1External_delAndSetNull, (void *)&v);
			if (dz1_asn1_ber_self_test(&dz1Asn1TypeDescrExternal, v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Asn1External_delAndSetNull, (void *)&v);
		}
	}
}
// cmd_exp_external_native Sub Command
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// cmd_exp_external_instance Sub Command
static void cmd_exp_external_instance_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
void cmd_exp_external_instance(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;

	void (*_print_usage)(Dz1Str n) = cmd_exp_external_native_usage;
	TCHAR n[64];
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("native"));

	if (argc != 1) _print_usage(n);
	else
	{
		u8_t data[] = { 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xCD, 0xEF, 0xF0 };
		Dz1Asn1InstanceOf *v = NULL;
		if ((v = _instance_of_gen(Dz1T("1.0.34.1.1.1.1"), data, sizeof(data), errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Asn1InstanceOf_delAndSetNull, (void *)&v);

			if (dz1_asn1_ber_self_test(&dz1Asn1TypeDescrInstanceOf, v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(1); // (Dz1Asn1InstanceOf_delAndSetNull, (void *)&v);
		}
	}
}
// cmd_exp_external_instance Sub Command
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CHARACTERSTRING Export Test
static void cmd_ber_exp_pdv_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <syntaxes | abstract | presentation | negotiation | transfer | fixed> [<obj_descr_str>]\n"), n); }
void cmd_ber_exp_pdv(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	Dz1Asn1EmbPdvIDPresent id_mode = Dz1Asn1EmbPdvIDPresent_max;
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("chsrstr"));
	if (argc != 2 && argc != 3) cmd_ber_exp_pdv_usage(n);
	else if ((id_mode = _parse_id_mode(argv[1])) == Dz1Asn1EmbPdvIDPresent_max) cmd_ber_exp_pdv_usage(n);
	else
	{
		// Command Code Here
		Dz1Str obj_descr_str = argc >= 3 ? argv[2] : NULL;
		Dz1Asn1EmbPdv *v = _pdv_gen(id_mode, obj_descr_str, errp);
		if (v == NULL)
		{
			if (errp->code == EINVAL) cmd_ber_exp_pdv_usage(n);
			else ERR_OUT(errp);
		}
		else
		{
			pthread_cleanup_push(Dz1Asn1CharStr_delAndSetNull, (void *)&v);
			if (dz1_asn1_ber_self_test(&dz1Asn1TypeDescrEmbPdv, v, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(1); // (Dz1Asn1CharStr_delAndSetNull, (void *)&v);
		}
	}
}
// CHARACTERSTRING Export Test
////////////////////////////////////////////////////////////////////////////////
